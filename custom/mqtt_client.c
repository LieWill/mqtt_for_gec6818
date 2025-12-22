/**
 * @file mqtt_client.c
 * @brief MQTT客户端库实现 - 基于mosquitto_sub的消息获取库
 * 
 * 本实现使用mosquitto_sub命令行工具通过popen来订阅MQTT主题，
 * 适用于Linux嵌入式系统（如GEC6818开发板）。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <signal.h>

#include "mqtt_client.h"

/*********************
 *      DEFINES
 *********************/

/* 调试开关 */
#ifndef MQTT_DEBUG_ENABLE
#define MQTT_DEBUG_ENABLE   1
#endif

#if MQTT_DEBUG_ENABLE
#define MQTT_LOG(fmt, ...)  printf("[MQTT] " fmt "\n", ##__VA_ARGS__)
#define MQTT_ERR(fmt, ...)  printf("[MQTT ERR] [%s:%d] " fmt ": %s\n", __FILE__, __LINE__, ##__VA_ARGS__, strerror(errno))
#else
#define MQTT_LOG(fmt, ...)
#define MQTT_ERR(fmt, ...)
#endif

/* 重连延迟（微秒） */
#define MQTT_RECONNECT_DELAY_US     1000000     /* 1秒 */
#define MQTT_READ_TIMEOUT_US        100000      /* 100毫秒 */

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void *mqtt_subscribe_thread(void *arg);
static void *mqtt_zigbee_subscribe_thread(void *arg);
static bool mqtt_build_subscribe_cmd(mqtt_client_t *client, char *cmd_buf, size_t buf_size);
static bool mqtt_build_zigbee_subscribe_cmd(mqtt_client_t *client, char *cmd_buf, size_t buf_size);

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * @brief 初始化MQTT客户端
 */
int mqtt_client_init(mqtt_client_t *client)
{
    if (client == NULL) {
        return MQTT_ERR_INVALID_PARAM;
    }

    /* 清零所有成员 */
    memset(client, 0, sizeof(mqtt_client_t));

    /* 设置默认配置 */
    strncpy(client->config.host, MQTT_DEFAULT_HOST, sizeof(client->config.host) - 1);
    client->config.port = MQTT_DEFAULT_PORT;
    strncpy(client->config.topic, MQTT_DEFAULT_TOPIC, sizeof(client->config.topic) - 1);
    strncpy(client->config.username, MQTT_DEFAULT_USERNAME, sizeof(client->config.username) - 1);
    strncpy(client->config.password, MQTT_DEFAULT_PASSWORD, sizeof(client->config.password) - 1);
    client->config.use_auth = true;

    /* 初始化状态 */
    client->state = MQTT_STATE_IDLE;
    client->running = false;
    client->last_data.valid = false;
    client->last_zigbee_data.valid = false;

    MQTT_LOG("客户端初始化完成 (默认Broker: %s:%d, 主题: %s)", 
             client->config.host, client->config.port, client->config.topic);

    return MQTT_OK;
}

/**
 * @brief 配置MQTT连接参数
 */
int mqtt_client_set_broker(mqtt_client_t *client, const char *host, uint16_t port, const char *topic)
{
    if (client == NULL || host == NULL || topic == NULL) {
        return MQTT_ERR_INVALID_PARAM;
    }

    if (client->running) {
        MQTT_LOG("警告: 客户端正在运行，修改配置后需要重启");
    }

    strncpy(client->config.host, host, sizeof(client->config.host) - 1);
    client->config.port = port;
    strncpy(client->config.topic, topic, sizeof(client->config.topic) - 1);

    MQTT_LOG("Broker配置更新: %s:%d, 主题: %s", host, port, topic);

    return MQTT_OK;
}

/**
 * @brief 配置MQTT认证信息
 */
int mqtt_client_set_auth(mqtt_client_t *client, const char *username, const char *password)
{
    if (client == NULL) {
        return MQTT_ERR_INVALID_PARAM;
    }

    if (username != NULL && password != NULL) {
        strncpy(client->config.username, username, sizeof(client->config.username) - 1);
        strncpy(client->config.password, password, sizeof(client->config.password) - 1);
        client->config.use_auth = true;
        MQTT_LOG("认证配置更新: 用户名=%s", username);
    } else {
        client->config.use_auth = false;
        MQTT_LOG("已禁用认证");
    }

    return MQTT_OK;
}

/**
 * @brief 注册原始数据回调函数
 */
int mqtt_client_set_raw_callback(mqtt_client_t *client, mqtt_raw_data_cb_t callback, void *user_data)
{
    if (client == NULL) {
        return MQTT_ERR_INVALID_PARAM;
    }

    client->raw_cb = callback;
    client->user_data = user_data;

    return MQTT_OK;
}

/**
 * @brief 注册传感器数据回调函数
 */
int mqtt_client_set_sensor_callback(mqtt_client_t *client, mqtt_sensor_data_cb_t callback, void *user_data)
{
    if (client == NULL) {
        return MQTT_ERR_INVALID_PARAM;
    }

    client->sensor_cb = callback;
    client->user_data = user_data;

    return MQTT_OK;
}

/**
 * @brief 启动MQTT订阅线程
 */
int mqtt_client_start(mqtt_client_t *client)
{
    if (client == NULL) {
        return MQTT_ERR_INVALID_PARAM;
    }

    if (client->running) {
        MQTT_LOG("客户端已在运行");
        return MQTT_ERR_ALREADY_RUNNING;
    }

    client->running = true;
    client->state = MQTT_STATE_CONNECTING;

    /* 创建分离属性的订阅线程 */
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    
    int ret = pthread_create(&tid, &attr, mqtt_subscribe_thread, client);
    pthread_attr_destroy(&attr);
    
    if (ret != 0) {
        MQTT_ERR("创建订阅线程失败");
        client->running = false;
        client->state = MQTT_STATE_ERROR;
        return MQTT_ERR_THREAD_FAILED;
    }

    client->thread_handle = (void *)(uintptr_t)tid;
    MQTT_LOG("STM32传感器订阅线程已启动");

    /* 创建ZigBee订阅线程 */
    pthread_t zigbee_tid;
    pthread_attr_t zigbee_attr;
    pthread_attr_init(&zigbee_attr);
    pthread_attr_setdetachstate(&zigbee_attr, PTHREAD_CREATE_DETACHED);
    
    ret = pthread_create(&zigbee_tid, &zigbee_attr, mqtt_zigbee_subscribe_thread, client);
    pthread_attr_destroy(&zigbee_attr);
    
    if (ret != 0) {
        MQTT_ERR("创建ZigBee订阅线程失败");
        /* ZigBee线程失败不影响主线程，仅记录警告 */
    } else {
        client->zigbee_thread_handle = (void *)(uintptr_t)zigbee_tid;
        MQTT_LOG("ZigBee传感器订阅线程已启动");
    }

    return MQTT_OK;
}

/**
 * @brief 停止MQTT订阅线程
 */
int mqtt_client_stop(mqtt_client_t *client)
{
    if (client == NULL) {
        return MQTT_ERR_INVALID_PARAM;
    }

    if (!client->running) {
        return MQTT_ERR_NOT_RUNNING;
    }

    MQTT_LOG("正在停止订阅线程...");
    client->running = false;

    /* 等待线程退出（给予足够时间） */
    usleep(500000);  /* 500ms */

    client->state = MQTT_STATE_STOPPED;
    MQTT_LOG("订阅线程已停止");

    return MQTT_OK;
}

/**
 * @brief 获取客户端当前状态
 */
mqtt_state_t mqtt_client_get_state(mqtt_client_t *client)
{
    if (client == NULL) {
        return MQTT_STATE_ERROR;
    }
    return client->state;
}

/**
 * @brief 获取最新的传感器数据
 */
int mqtt_client_get_last_data(mqtt_client_t *client, mqtt_sensor_data_t *data)
{
    if (client == NULL || data == NULL) {
        return MQTT_ERR_INVALID_PARAM;
    }

    memcpy(data, &client->last_data, sizeof(mqtt_sensor_data_t));
    return MQTT_OK;
}

/**
 * @brief 解析JSON格式的传感器数据
 * 支持格式: {"temp":25.5,"humi":60.0,"light":500.0}
 */
bool mqtt_parse_sensor_json(const char *json_str, mqtt_sensor_data_t *data)
{
    if (json_str == NULL || data == NULL) {
        return false;
    }

    /* 清零数据 */
    memset(data, 0, sizeof(mqtt_sensor_data_t));

    /* 尝试解析多种JSON格式 */
    int parsed = 0;
    
    /* 格式1: {"temp":xx,"humi":xx,"light":xx} */
    parsed = sscanf(json_str, "{\"temp\":%f,\"humi\":%f,\"light\":%f}", 
                    &data->temp, &data->humi, &data->light);
    
    if (parsed == 3) {
        data->timestamp = (uint32_t)time(NULL);
        data->valid = true;
        return true;
    }

    /* 格式2: {"temperature":xx,"humidity":xx,"lux":xx} */
    parsed = sscanf(json_str, "{\"temperature\":%f,\"humidity\":%f,\"lux\":%f}", 
                    &data->temp, &data->humi, &data->light);
    
    if (parsed == 3) {
        data->timestamp = (uint32_t)time(NULL);
        data->valid = true;
        return true;
    }

    /* 格式3: 只有温度和湿度 {"temp":xx,"humi":xx} */
    parsed = sscanf(json_str, "{\"temp\":%f,\"humi\":%f}", 
                    &data->temp, &data->humi);
    
    if (parsed == 2) {
        data->light = 0.0f;
        data->timestamp = (uint32_t)time(NULL);
        data->valid = true;
        return true;
    }

    /* 格式4: 单独温度值 {"temp":xx} 或纯数字 */
    parsed = sscanf(json_str, "{\"temp\":%f}", &data->temp);
    if (parsed == 1) {
        data->humi = 0.0f;
        data->light = 0.0f;
        data->timestamp = (uint32_t)time(NULL);
        data->valid = true;
        return true;
    }

    /* 尝试解析纯数字 */
    parsed = sscanf(json_str, "%f", &data->temp);
    if (parsed == 1) {
        data->humi = 0.0f;
        data->light = 0.0f;
        data->timestamp = (uint32_t)time(NULL);
        data->valid = true;
        return true;
    }

    return false;
}

/**
 * @brief 发布MQTT消息
 * 使用mosquitto_pub命令行工具发布消息
 */
int mqtt_client_publish(mqtt_client_t *client, const char *topic, const char *message)
{
    if (client == NULL || message == NULL) {
        return MQTT_ERR_INVALID_PARAM;
    }

    /* 使用默认控制主题或指定主题 */
    const char *pub_topic = (topic != NULL) ? topic : MQTT_DEFAULT_CONTROL_TOPIC;

    /* 构建mosquitto_pub命令 */
    char pub_cmd[MQTT_CMD_BUF_SIZE] = {0};
    int ret;

    if (client->config.use_auth) {
        ret = snprintf(pub_cmd, sizeof(pub_cmd),
                      "mosquitto_pub -h %s -p %d -t \"%s\" -u %s -P %s -m '%s'",
                      client->config.host,
                      client->config.port,
                      pub_topic,
                      client->config.username,
                      client->config.password,
                      message);
    } else {
        ret = snprintf(pub_cmd, sizeof(pub_cmd),
                      "mosquitto_pub -h %s -p %d -t \"%s\" -m '%s'",
                      client->config.host,
                      client->config.port,
                      pub_topic,
                      message);
    }

    if (ret < 0 || (size_t)ret >= sizeof(pub_cmd)) {
        MQTT_ERR("构建发布命令失败（缓冲区不足）");
        return MQTT_ERR_INVALID_PARAM;
    }

    MQTT_LOG("执行发布命令: %s", pub_cmd);

    /* 执行发布命令 */
    ret = system(pub_cmd);
    if (ret != 0) {
        MQTT_ERR("发布消息失败 (返回码: %d)", ret);
        return MQTT_ERR_POPEN_FAILED;
    }

    MQTT_LOG("消息发布成功 - 主题: %s, 内容: %s", pub_topic, message);
    return MQTT_OK;
}

/**
 * @brief 发布LED控制JSON消息
 * 格式: {"led1":true} 或 {"led2":false} 等
 */
int mqtt_client_publish_led(mqtt_client_t *client, const char *led_name, bool state)
{
    if (client == NULL || led_name == NULL) {
        return MQTT_ERR_INVALID_PARAM;
    }

    /* 构建JSON消息 */
    char json_msg[64] = {0};
    snprintf(json_msg, sizeof(json_msg), "{\"%s\":%s}", led_name, state ? "true" : "false");

    /* 发布到控制主题 */
    return mqtt_client_publish(client, MQTT_DEFAULT_CONTROL_TOPIC, json_msg);
}

/**
 * @brief 反初始化MQTT客户端
 */
void mqtt_client_deinit(mqtt_client_t *client)
{
    if (client == NULL) {
        return;
    }

    /* 停止运行中的线程 */
    if (client->running) {
        mqtt_client_stop(client);
    }

    /* 清零所有成员 */
    memset(client, 0, sizeof(mqtt_client_t));
    
    MQTT_LOG("客户端已反初始化");
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * @brief 构建mosquitto_sub订阅命令
 */
static bool mqtt_build_subscribe_cmd(mqtt_client_t *client, char *cmd_buf, size_t buf_size)
{
    if (client == NULL || cmd_buf == NULL || buf_size == 0) {
        return false;
    }

    int ret;
    if (client->config.use_auth) {
        ret = snprintf(cmd_buf, buf_size,
                      "mosquitto_sub -h %s -p %d -t \"%s\" -u %s -P %s",
                      client->config.host,
                      client->config.port,
                      client->config.topic,
                      client->config.username,
                      client->config.password);
    } else {
        ret = snprintf(cmd_buf, buf_size,
                      "mosquitto_sub -h %s -p %d -t \"%s\"",
                      client->config.host,
                      client->config.port,
                      client->config.topic);
    }

    if (ret < 0 || (size_t)ret >= buf_size) {
        MQTT_ERR("构建订阅命令失败（缓冲区不足）");
        return false;
    }

    return true;
}

/**
 * @brief 订阅线程函数
 */
static void *mqtt_subscribe_thread(void *arg)
{
    mqtt_client_t *client = (mqtt_client_t *)arg;
    
    if (client == NULL) {
        return NULL;
    }

    /* 构建订阅命令 */
    char sub_cmd[MQTT_CMD_BUF_SIZE] = {0};
    if (!mqtt_build_subscribe_cmd(client, sub_cmd, sizeof(sub_cmd))) {
        client->state = MQTT_STATE_ERROR;
        client->running = false;
        return NULL;
    }

    MQTT_LOG("执行订阅命令: %s", sub_cmd);

    /* 启动订阅进程 */
    FILE *fp = popen(sub_cmd, "r");
    if (fp == NULL) {
        MQTT_ERR("订阅主题失败（popen创建管道失败）");
        client->state = MQTT_STATE_ERROR;
        client->running = false;
        return NULL;
    }

    client->state = MQTT_STATE_CONNECTED;
    MQTT_LOG("订阅成功，开始接收数据（主题：%s，Broker：%s:%d）",
             client->config.topic, client->config.host, client->config.port);

    /* 循环读取数据 */
    char buf[MQTT_DATA_BUF_SIZE] = {0};
    
    while (client->running) {
        memset(buf, 0, sizeof(buf));
        char *ret = fgets(buf, sizeof(buf) - 1, fp);
        
        if (ret != NULL) {
            /* 过滤空行，处理有效数据 */
            size_t len = strlen(buf);
            
            /* 去除尾部换行符 */
            while (len > 0 && (buf[len-1] == '\n' || buf[len-1] == '\r')) {
                buf[--len] = '\0';
            }
            
            if (len > 0) {
                MQTT_LOG("[%ld] 收到订阅数据：%s", (long)time(NULL), buf);
                
                /* 调用原始数据回调 */
                if (client->raw_cb != NULL) {
                    client->raw_cb(buf, client->user_data);
                }
                
                /* 尝试解析传感器数据 */
                mqtt_sensor_data_t sensor_data;
                if (mqtt_parse_sensor_json(buf, &sensor_data)) {
                    MQTT_LOG("解析成功 - 温度：%.1f℃，湿度：%.1f%%，光照：%.1fLux",
                             sensor_data.temp, sensor_data.humi, sensor_data.light);
                    
                    /* 保存最新数据 */
                    memcpy(&client->last_data, &sensor_data, sizeof(mqtt_sensor_data_t));
                    
                    /* 调用传感器数据回调 */
                    if (client->sensor_cb != NULL) {
                        client->sensor_cb(&sensor_data, client->user_data);
                    }
                }
            }
        } else {
            /* 处理读取失败 */
            if (feof(fp)) {
                MQTT_ERR("订阅进程异常退出（EOF），尝试重启订阅...");
                pclose(fp);
                
                client->state = MQTT_STATE_RECONNECTING;
                
                /* 等待一段时间后重连 */
                usleep(MQTT_RECONNECT_DELAY_US);
                
                if (!client->running) {
                    break;
                }
                
                fp = popen(sub_cmd, "r");
                if (fp == NULL) {
                    MQTT_ERR("重启订阅失败");
                    client->state = MQTT_STATE_ERROR;
                    client->running = false;
                    break;
                }
                
                client->state = MQTT_STATE_CONNECTED;
                MQTT_LOG("订阅进程重启成功");
            } else if (ferror(fp)) {
                MQTT_ERR("读取订阅数据失败（管道错误）");
                clearerr(fp);
            }
            
            /* 避免CPU空转 */
            usleep(MQTT_READ_TIMEOUT_US);
        }
    }

    /* 清理资源 */
    if (fp) {
        pclose(fp);
    }
    
    client->state = MQTT_STATE_STOPPED;
    MQTT_LOG("订阅线程退出");
    
    return NULL;
}

/**
 * @brief 解析ZigBee传感器JSON数据
 * 格式: {"mac":"00124B0004284E1E","illumination":1081,"temperature":21.43,
 *        "humidity":77.32,"dew_point":17.29,"human_detected":false,"vibration":false,"count":95}
 */
bool mqtt_parse_zigbee_json(const char *json_str, mqtt_zigbee_data_t *data)
{
    if (json_str == NULL || data == NULL) {
        return false;
    }

    /* 清零数据 */
    memset(data, 0, sizeof(mqtt_zigbee_data_t));

    /* 查找各个字段 */
    char *ptr;
    
    /* 解析 mac */
    ptr = strstr(json_str, "\"mac\":\"");
    if (ptr != NULL) {
        ptr += 7;  /* 跳过 "mac":" */
        char *end = strchr(ptr, '"');
        if (end != NULL) {
            size_t len = end - ptr;
            if (len < sizeof(data->mac)) {
                strncpy(data->mac, ptr, len);
                data->mac[len] = '\0';
            }
        }
    }

    /* 解析 illumination */
    ptr = strstr(json_str, "\"illumination\":");
    if (ptr != NULL) {
        ptr += 15;  /* 跳过 "illumination": */
        data->illumination = (uint32_t)atoi(ptr);
    }

    /* 解析 temperature */
    ptr = strstr(json_str, "\"temperature\":");
    if (ptr != NULL) {
        ptr += 14;  /* 跳过 "temperature": */
        data->temperature = (float)atof(ptr);
    }

    /* 解析 humidity */
    ptr = strstr(json_str, "\"humidity\":");
    if (ptr != NULL) {
        ptr += 11;  /* 跳过 "humidity": */
        data->humidity = (float)atof(ptr);
    }

    /* 解析 dew_point */
    ptr = strstr(json_str, "\"dew_point\":");
    if (ptr != NULL) {
        ptr += 12;  /* 跳过 "dew_point": */
        data->dew_point = (float)atof(ptr);
    }

    /* 解析 human_detected */
    ptr = strstr(json_str, "\"human_detected\":");
    if (ptr != NULL) {
        ptr += 17;  /* 跳过 "human_detected": */
        data->human_detected = (strncmp(ptr, "true", 4) == 0);
    }

    /* 解析 vibration */
    ptr = strstr(json_str, "\"vibration\":");
    if (ptr != NULL) {
        ptr += 12;  /* 跳过 "vibration": */
        data->vibration = (strncmp(ptr, "true", 4) == 0);
    }

    /* 解析 count */
    ptr = strstr(json_str, "\"count\":");
    if (ptr != NULL) {
        ptr += 8;  /* 跳过 "count": */
        data->count = (uint32_t)atoi(ptr);
    }

    /* 设置时间戳和有效标志 */
    data->timestamp = (uint32_t)time(NULL);
    
    /* 如果至少解析到一些关键数据，则认为有效 */
    if (data->mac[0] != '\0' || data->temperature != 0.0f || data->humidity != 0.0f) {
        data->valid = true;
        return true;
    }

    return false;
}

/**
 * @brief 注册ZigBee传感器数据回调函数
 */
int mqtt_client_set_zigbee_callback(mqtt_client_t *client, mqtt_zigbee_data_cb_t callback, void *user_data)
{
    if (client == NULL) {
        return MQTT_ERR_INVALID_PARAM;
    }

    client->zigbee_cb = callback;
    client->user_data = user_data;

    return MQTT_OK;
}

/**
 * @brief 获取最新的ZigBee传感器数据
 */
int mqtt_client_get_last_zigbee_data(mqtt_client_t *client, mqtt_zigbee_data_t *data)
{
    if (client == NULL || data == NULL) {
        return MQTT_ERR_INVALID_PARAM;
    }

    memcpy(data, &client->last_zigbee_data, sizeof(mqtt_zigbee_data_t));
    return MQTT_OK;
}

/**
 * @brief 构建ZigBee mosquitto_sub订阅命令
 */
static bool mqtt_build_zigbee_subscribe_cmd(mqtt_client_t *client, char *cmd_buf, size_t buf_size)
{
    if (client == NULL || cmd_buf == NULL || buf_size == 0) {
        return false;
    }

    int ret;
    if (client->config.use_auth) {
        ret = snprintf(cmd_buf, buf_size,
                      "mosquitto_sub -h %s -p %d -t \"%s\" -u %s -P %s",
                      client->config.host,
                      client->config.port,
                      MQTT_ZIGBEE_TOPIC,
                      client->config.username,
                      client->config.password);
    } else {
        ret = snprintf(cmd_buf, buf_size,
                      "mosquitto_sub -h %s -p %d -t \"%s\"",
                      client->config.host,
                      client->config.port,
                      MQTT_ZIGBEE_TOPIC);
    }

    if (ret < 0 || (size_t)ret >= buf_size) {
        MQTT_ERR("构建ZigBee订阅命令失败（缓冲区不足）");
        return false;
    }

    return true;
}

/**
 * @brief ZigBee订阅线程函数
 */
static void *mqtt_zigbee_subscribe_thread(void *arg)
{
    mqtt_client_t *client = (mqtt_client_t *)arg;
    
    if (client == NULL) {
        return NULL;
    }

    /* 构建订阅命令 */
    char sub_cmd[MQTT_CMD_BUF_SIZE] = {0};
    if (!mqtt_build_zigbee_subscribe_cmd(client, sub_cmd, sizeof(sub_cmd))) {
        MQTT_ERR("构建ZigBee订阅命令失败");
        return NULL;
    }

    MQTT_LOG("执行ZigBee订阅命令: %s", sub_cmd);

    /* 启动订阅进程 */
    FILE *fp = popen(sub_cmd, "r");
    if (fp == NULL) {
        MQTT_ERR("ZigBee订阅主题失败（popen创建管道失败）");
        return NULL;
    }

    MQTT_LOG("ZigBee订阅成功，开始接收数据（主题：%s）", MQTT_ZIGBEE_TOPIC);

    /* 循环读取数据 */
    char buf[MQTT_DATA_BUF_SIZE] = {0};
    
    while (client->running) {
        memset(buf, 0, sizeof(buf));
        char *ret = fgets(buf, sizeof(buf) - 1, fp);
        
        if (ret != NULL) {
            /* 过滤空行，处理有效数据 */
            size_t len = strlen(buf);
            
            /* 去除尾部换行符 */
            while (len > 0 && (buf[len-1] == '\n' || buf[len-1] == '\r')) {
                buf[--len] = '\0';
            }
            
            if (len > 0) {
                MQTT_LOG("[ZigBee][%ld] 收到数据：%s", (long)time(NULL), buf);
                
                /* 尝试解析ZigBee传感器数据 */
                mqtt_zigbee_data_t zigbee_data;
                if (mqtt_parse_zigbee_json(buf, &zigbee_data)) {
                    MQTT_LOG("[ZigBee] 解析成功 - MAC:%s 温度:%.2f℃ 湿度:%.2f%% 光照:%u 人体:%s 震动:%s 序号:%u",
                             zigbee_data.mac, zigbee_data.temperature, zigbee_data.humidity,
                             zigbee_data.illumination, 
                             zigbee_data.human_detected ? "是" : "否",
                             zigbee_data.vibration ? "是" : "否",
                             zigbee_data.count);
                    
                    /* 保存最新数据 */
                    memcpy(&client->last_zigbee_data, &zigbee_data, sizeof(mqtt_zigbee_data_t));
                    
                    /* 调用ZigBee数据回调 */
                    if (client->zigbee_cb != NULL) {
                        client->zigbee_cb(&zigbee_data, client->user_data);
                    }
                }
            }
        } else {
            /* 处理读取失败 */
            if (feof(fp)) {
                MQTT_ERR("ZigBee订阅进程异常退出（EOF），尝试重启订阅...");
                pclose(fp);
                
                /* 等待一段时间后重连 */
                usleep(MQTT_RECONNECT_DELAY_US);
                
                if (!client->running) {
                    break;
                }
                
                fp = popen(sub_cmd, "r");
                if (fp == NULL) {
                    MQTT_ERR("重启ZigBee订阅失败");
                    break;
                }
                
                MQTT_LOG("ZigBee订阅进程重启成功");
            } else if (ferror(fp)) {
                MQTT_ERR("读取ZigBee订阅数据失败（管道错误）");
                clearerr(fp);
            }
            
            /* 避免CPU空转 */
            usleep(MQTT_READ_TIMEOUT_US);
        }
    }

    /* 清理资源 */
    if (fp) {
        pclose(fp);
    }
    
    MQTT_LOG("ZigBee订阅线程退出");
    
    return NULL;
}
