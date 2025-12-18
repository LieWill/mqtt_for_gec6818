/**
 * @file mqtt_client.h
 * @brief MQTT客户端库 - 基于mosquitto_sub的消息获取库
 * 
 * 本库提供了一个简单的MQTT消息订阅和解析功能，
 * 使用mosquitto_sub命令行工具通过popen来实现MQTT订阅。
 * 
 * 使用示例:
 * 1. 初始化MQTT配置
 * 2. 注册数据回调函数
 * 3. 启动订阅线程
 * 4. 在回调中处理接收到的数据
 */

#ifndef __MQTT_CLIENT_H__
#define __MQTT_CLIENT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/*********************
 *      DEFINES
 *********************/

/* MQTT配置默认值 */
#define MQTT_DEFAULT_HOST       "47.107.34.158"
#define MQTT_DEFAULT_PORT       1883
#define MQTT_DEFAULT_TOPIC      "stm32/sensor/data"
#define MQTT_DEFAULT_USERNAME   "stm32"
#define MQTT_DEFAULT_PASSWORD   "123456"

/* 缓冲区大小 */
#define MQTT_CMD_BUF_SIZE       512
#define MQTT_DATA_BUF_SIZE      1024

/* 错误码 */
#define MQTT_OK                 0
#define MQTT_ERR_INVALID_PARAM  -1
#define MQTT_ERR_POPEN_FAILED   -2
#define MQTT_ERR_THREAD_FAILED  -3
#define MQTT_ERR_ALREADY_RUNNING -4
#define MQTT_ERR_NOT_RUNNING    -5

/**********************
 *      TYPEDEFS
 **********************/

/**
 * @brief 传感器数据结构体
 */
typedef struct {
    float temp;     /**< 温度值 (摄氏度) */
    float humi;     /**< 湿度值 (百分比) */
    float light;    /**< 光照值 (Lux) */
    uint32_t timestamp; /**< 时间戳 */
    bool valid;     /**< 数据有效标志 */
} mqtt_sensor_data_t;

/**
 * @brief MQTT配置结构体
 */
typedef struct {
    char host[64];          /**< MQTT Broker地址 */
    uint16_t port;          /**< MQTT Broker端口 */
    char topic[128];        /**< 订阅主题 */
    char username[64];      /**< 用户名 (可选) */
    char password[64];      /**< 密码 (可选) */
    bool use_auth;          /**< 是否使用认证 */
} mqtt_config_t;

/**
 * @brief MQTT原始数据回调函数类型
 * @param data 接收到的原始数据字符串
 * @param user_data 用户自定义数据
 */
typedef void (*mqtt_raw_data_cb_t)(const char *data, void *user_data);

/**
 * @brief MQTT传感器数据回调函数类型
 * @param sensor_data 解析后的传感器数据
 * @param user_data 用户自定义数据
 */
typedef void (*mqtt_sensor_data_cb_t)(const mqtt_sensor_data_t *sensor_data, void *user_data);

/**
 * @brief MQTT客户端状态枚举
 */
typedef enum {
    MQTT_STATE_IDLE = 0,        /**< 空闲状态 */
    MQTT_STATE_CONNECTING,      /**< 正在连接 */
    MQTT_STATE_CONNECTED,       /**< 已连接并订阅 */
    MQTT_STATE_RECONNECTING,    /**< 正在重连 */
    MQTT_STATE_ERROR,           /**< 错误状态 */
    MQTT_STATE_STOPPED          /**< 已停止 */
} mqtt_state_t;

/**
 * @brief MQTT客户端句柄结构体
 */
typedef struct {
    mqtt_config_t config;               /**< MQTT配置 */
    mqtt_state_t state;                 /**< 客户端状态 */
    mqtt_raw_data_cb_t raw_cb;          /**< 原始数据回调 */
    mqtt_sensor_data_cb_t sensor_cb;    /**< 传感器数据回调 */
    void *user_data;                    /**< 用户自定义数据 */
    mqtt_sensor_data_t last_data;       /**< 最新的传感器数据 */
    volatile bool running;              /**< 运行标志 */
    void *thread_handle;                /**< 线程句柄 (内部使用) */
} mqtt_client_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * @brief 初始化MQTT客户端
 * @param client 客户端句柄指针
 * @return MQTT_OK成功，其他表示错误
 */
int mqtt_client_init(mqtt_client_t *client);

/**
 * @brief 配置MQTT连接参数
 * @param client 客户端句柄指针
 * @param host MQTT Broker地址
 * @param port MQTT Broker端口
 * @param topic 订阅主题
 * @return MQTT_OK成功，其他表示错误
 */
int mqtt_client_set_broker(mqtt_client_t *client, const char *host, uint16_t port, const char *topic);

/**
 * @brief 配置MQTT认证信息
 * @param client 客户端句柄指针
 * @param username 用户名
 * @param password 密码
 * @return MQTT_OK成功，其他表示错误
 */
int mqtt_client_set_auth(mqtt_client_t *client, const char *username, const char *password);

/**
 * @brief 注册原始数据回调函数
 * @param client 客户端句柄指针
 * @param callback 回调函数
 * @param user_data 用户自定义数据
 * @return MQTT_OK成功，其他表示错误
 */
int mqtt_client_set_raw_callback(mqtt_client_t *client, mqtt_raw_data_cb_t callback, void *user_data);

/**
 * @brief 注册传感器数据回调函数
 * @param client 客户端句柄指针
 * @param callback 回调函数
 * @param user_data 用户自定义数据
 * @return MQTT_OK成功，其他表示错误
 */
int mqtt_client_set_sensor_callback(mqtt_client_t *client, mqtt_sensor_data_cb_t callback, void *user_data);

/**
 * @brief 启动MQTT订阅线程
 * @param client 客户端句柄指针
 * @return MQTT_OK成功，其他表示错误
 */
int mqtt_client_start(mqtt_client_t *client);

/**
 * @brief 停止MQTT订阅线程
 * @param client 客户端句柄指针
 * @return MQTT_OK成功，其他表示错误
 */
int mqtt_client_stop(mqtt_client_t *client);

/**
 * @brief 获取客户端当前状态
 * @param client 客户端句柄指针
 * @return 客户端状态
 */
mqtt_state_t mqtt_client_get_state(mqtt_client_t *client);

/**
 * @brief 获取最新的传感器数据
 * @param client 客户端句柄指针
 * @param data 数据输出指针
 * @return MQTT_OK成功，其他表示错误
 */
int mqtt_client_get_last_data(mqtt_client_t *client, mqtt_sensor_data_t *data);

/**
 * @brief 解析JSON格式的传感器数据
 * @param json_str JSON字符串
 * @param data 解析结果输出指针
 * @return true解析成功，false解析失败
 */
bool mqtt_parse_sensor_json(const char *json_str, mqtt_sensor_data_t *data);

/**
 * @brief 反初始化MQTT客户端
 * @param client 客户端句柄指针
 */
void mqtt_client_deinit(mqtt_client_t *client);

#ifdef __cplusplus
}
#endif

#endif /* __MQTT_CLIENT_H__ */
