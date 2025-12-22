/*
* Copyright 2024 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/


/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"
#include "mqtt_client.h"

/*********************
 *      DEFINES
 *********************/
#define CHART_POINTS 40
/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void mqtt_sensor_data_callback(const mqtt_sensor_data_t *sensor_data, void *user_data);
static void mqtt_zigbee_data_callback(const mqtt_zigbee_data_t *zigbee_data, void *user_data);

/**********************
 *  STATIC VARIABLES
 **********************/
static mqtt_client_t g_mqtt_client;
static mqtt_sensor_data_t g_sensor_data = {0};
static mqtt_zigbee_data_t g_zigbee_data = {0};
static lv_ui *g_ui = NULL;

/**
 * Create a demo application
 */

static int32_t temperature = 5;
static int32_t power = 40;
static bool is_increase = true;
static int32_t point = 0;

void home_timer_cb(lv_timer_t * t)
{
    lv_ui * gui = t->user_data;

}

void firefighting_timer_cb(lv_timer_t * t)
{
    lv_ui * gui = t->user_data;
    
}

void chart_line_timer_cb (lv_timer_t * t) {

    lv_ui * gui = t->user_data;
}

void custom_init(lv_ui *ui)
{
    /* Add your codes here */
    
    /* 初始化MQTT客户端（可选：在此处自动启动MQTT） */
    mqtt_init_and_start(ui);
}

/**********************
 *  MQTT集成函数实现
 **********************/

/**
 * @brief MQTT传感器数据回调函数
 * 当接收到传感器数据时，此函数被调用，用于更新LVGL界面
 */
static void mqtt_sensor_data_callback(const mqtt_sensor_data_t *sensor_data, void *user_data)
{
    lv_ui *ui = (lv_ui *)user_data;
    
    if (sensor_data == NULL || ui == NULL) {
        return;
    }
    
    /* 保存传感器数据到全局变量 */
    g_sensor_data = *sensor_data;
    
    printf("[MQTT UI] 更新界面 - 温度:%.1f℃ 湿度:%.1f%% 光照:%.1fLux\n",
           sensor_data->temp, sensor_data->humi, sensor_data->light);
    
    /* 检查 Home 页面是否存在且有效，避免访问已删除的组件导致段错误 */
    /* 使用 lv_obj_is_valid() 检查对象有效性，并确认当前活动屏幕是 Home */
    if (ui->Home == NULL || !lv_obj_is_valid(ui->Home) || lv_scr_act() != ui->Home) {
        printf("[MQTT UI] Home页面未激活，跳过UI更新\n");
        return;
    }
    
    /* 更新温度显示 - 使用整数方式避免浮点格式化问题 */
    if (ui->Home_label_temp_val != NULL) {
        int temp_int = (int)sensor_data->temp;
        int temp_dec = (int)((sensor_data->temp - temp_int) * 10);
        if (temp_dec < 0) temp_dec = -temp_dec;
        lv_label_set_text_fmt(ui->Home_label_temp_val, "%d.%d", temp_int, temp_dec);
    }
    
    /* 更新湿度显示 - 使用整数方式避免浮点格式化问题 */
    if (ui->Home_label_wet_val != NULL) {
        int humi_int = (int)sensor_data->humi;
        int humi_dec = (int)((sensor_data->humi - humi_int) * 10);
        if (humi_dec < 0) humi_dec = -humi_dec;
        lv_label_set_text_fmt(ui->Home_label_wet_val, "%d.%d", humi_int, humi_dec);
    }

    /* 更新光照显示 - 使用整数方式避免浮点格式化问题 */
    if (ui->Home_label_light_val != NULL) {
        lv_label_set_text_fmt(ui->Home_label_light_val, "%d", (int)sensor_data->light);
    }
    
    /* 更新温度弧形进度条 (假设温度范围 0-50℃) */
    if (ui->Home_arc_temp != NULL) {
        int16_t arc_value = (int16_t)(sensor_data->temp);  /* 0-100映射 */
        if (arc_value < 0) arc_value = 0;
        if (arc_value > 100) arc_value = 100;
        lv_arc_set_value(ui->Home_arc_temp, arc_value);
    }
    
    /* 更新湿度弧形进度条 (湿度范围 0-100%) */
    if (ui->Home_arc_humi != NULL) {
        int16_t arc_value = (int16_t)(sensor_data->humi * 0.4);
        if (arc_value < 0) arc_value = 0;
        if (arc_value > 100) arc_value = 100;
        lv_arc_set_value(ui->Home_arc_humi, arc_value);
    }

     /* 更新光照弧形进度条 (湿度范围 0-4000) */
    if (ui->Home_arc_light != NULL) {
        lv_arc_set_value(ui->Home_arc_light, (int16_t)(sensor_data->light));
    }
    
    /* 根据温度设置颜色 */
    lv_color_t temp_color;
    if (sensor_data->temp <= 15.0f) {
        temp_color = lv_color_hex(0x16cfa1);  /* 低温 - 绿色 */
    } else if (sensor_data->temp <= 28.0f) {
        temp_color = lv_color_hex(0xc2dd0a);  /* 常温 - 黄绿色 */
    } else {
        temp_color = lv_color_hex(0xe4400d);  /* 高温 - 红色 */
    }
    
    /* 应用颜色到UI组件 */
    if (ui->Home_arc_temp != NULL) {
        lv_obj_set_style_arc_color(ui->Home_arc_temp, temp_color, LV_PART_INDICATOR|LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(ui->Home_arc_temp, temp_color, LV_PART_KNOB|LV_STATE_DEFAULT);
    }
    if (ui->Home_label_temp_val != NULL) {
        lv_obj_set_style_text_color(ui->Home_label_temp_val, temp_color, LV_PART_MAIN|LV_STATE_DEFAULT);
    }

    lv_chart_series_t * ser = lv_chart_get_series_next(ui->Home_chart_temp, NULL);
    lv_coord_t * ser_array = lv_chart_get_y_array(ui->Home_chart_temp, ser);

    lv_chart_series_t * ser1 = lv_chart_get_series_next(ui->Home_chart_temp, ser);
    lv_coord_t * ser_array_1 = lv_chart_get_y_array(ui->Home_chart_temp, ser1);

    lv_chart_series_t * ser2 = lv_chart_get_series_next(ui->Home_chart_temp, ser1);
    lv_coord_t * ser_array_2 = lv_chart_get_y_array(ui->Home_chart_temp, ser2);


    for (int i = 0; i < 16 - 1; i++) {
        ser_array[i] = ser_array[i+1];
        ser_array_1[i] = ser_array_1[i+1];
        ser_array_2[i] = ser_array_2[i+1];
    }

    ser_array[16 - 1] = sensor_data->light;
    ser_array_1[16 - 1] = sensor_data->humi;
    ser_array_2[16 - 1] = sensor_data->temp;

    lv_chart_refresh(ui->Home_chart_temp);
}

/**
 * @brief 初始化并启动MQTT客户端
 * @param ui LVGL UI句柄
 * @return 0成功，其他失败
 */
int mqtt_init_and_start(lv_ui *ui)
{
    int ret;
    
    if (ui == NULL) {
        printf("[MQTT] 错误: UI句柄为空\n");
        return -1;
    }
    
    g_ui = ui;
    
    /* 初始化MQTT客户端 */
    ret = mqtt_client_init(&g_mqtt_client);
    if (ret != MQTT_OK) {
        printf("[MQTT] 初始化失败: %d\n", ret);
        return ret;
    }
    
    /* 配置Broker（使用默认值或自定义） */
    // mqtt_client_set_broker(&g_mqtt_client, "47.107.34.158", 1883, "stm32/sensor/data");
    
    /* 配置认证（使用默认值或自定义） */
    // mqtt_client_set_auth(&g_mqtt_client, "stm32", "123456");
    
    /* 注册传感器数据回调，传入UI句柄 */
    mqtt_client_set_sensor_callback(&g_mqtt_client, mqtt_sensor_data_callback, ui);
    
    /* 注册ZigBee传感器数据回调 */
    mqtt_client_set_zigbee_callback(&g_mqtt_client, mqtt_zigbee_data_callback, ui);
    
    /* 启动MQTT订阅 */
    ret = mqtt_client_start(&g_mqtt_client);
    if (ret != MQTT_OK) {
        printf("[MQTT] 启动失败: %d\n", ret);
        return ret;
    }
    
    printf("[MQTT] 客户端已启动，等待数据...\n");
    return 0;
}

/**
 * @brief 停止并反初始化MQTT客户端
 */
void mqtt_stop_and_deinit(void)
{
    mqtt_client_stop(&g_mqtt_client);
    mqtt_client_deinit(&g_mqtt_client);
    g_ui = NULL;
    printf("[MQTT] 客户端已停止\n");
}

/**
 * @brief 获取最新的传感器数据指针
 * @return 传感器数据指针
 */
mqtt_sensor_data_t* mqtt_get_sensor_data(void)
{
    return &g_sensor_data;
}

/**
 * @brief 获取MQTT客户端句柄
 * @return MQTT客户端句柄指针
 */
mqtt_client_t* mqtt_get_client(void)
{
    return &g_mqtt_client;
}

/**
 * @brief 获取最新的ZigBee传感器数据指针
 * @return ZigBee传感器数据指针
 */
mqtt_zigbee_data_t* mqtt_get_zigbee_data(void)
{
    return &g_zigbee_data;
}

/**
 * @brief ZigBee传感器数据回调函数
 * 当接收到ZigBee传感器数据时，此函数被调用，用于更新LVGL界面
 */
static void mqtt_zigbee_data_callback(const mqtt_zigbee_data_t *zigbee_data, void *user_data)
{
    lv_ui *ui = (lv_ui *)user_data;
    
    if (zigbee_data == NULL || ui == NULL) {
        return;
    }
    
    /* 保存ZigBee传感器数据到全局变量 */
    g_zigbee_data = *zigbee_data;
    
    /* 检查 ZigBee 页面是否存在且有效，避免访问已删除的组件导致段错误 */
    /* 使用 lv_obj_is_valid() 检查对象有效性，并确认当前活动屏幕是 ZigBee */
    if (ui->zigbee == NULL || !lv_obj_is_valid(ui->zigbee) || lv_scr_act() != ui->zigbee) {
        printf("[MQTT UI] ZigBee页面未激活，跳过UI更新\n");
        return;
    }
    
    /* 更新温度显示 - zigbee_label_temperature_val */
    if (ui->zigbee_label_temperature_val != NULL) {
        int temp_int = (int)zigbee_data->temperature;
        int temp_dec = (int)((zigbee_data->temperature - temp_int) * 100);
        if (temp_dec < 0) temp_dec = -temp_dec;
        lv_label_set_text_fmt(ui->zigbee_label_temperature_val, "%d.%02d", temp_int, temp_dec);
    }
    
    /* 更新湿度显示 - zigbee_label_humidity_val */
    if (ui->zigbee_label_humidity_val != NULL) {
        int humi_int = (int)zigbee_data->humidity;
        int humi_dec = (int)((zigbee_data->humidity - humi_int) * 100);
        if (humi_dec < 0) humi_dec = -humi_dec;
        lv_label_set_text_fmt(ui->zigbee_label_humidity_val, "%d.%02d", humi_int, humi_dec);
    }
    
    /* 更新光照强度显示 - zigbee_label_illumination_val */
    if (ui->zigbee_label_illumination_val != NULL) {
        lv_label_set_text_fmt(ui->zigbee_label_illumination_val, "%u", zigbee_data->illumination);
    }
    
    /* 更新露点温度显示 - zigbee_label_dew_point_val */
    if (ui->zigbee_label_dew_point_val != NULL) {
        int dp_int = (int)zigbee_data->dew_point;
        int dp_dec = (int)((zigbee_data->dew_point - dp_int) * 100);
        if (dp_dec < 0) dp_dec = -dp_dec;
        lv_label_set_text_fmt(ui->zigbee_label_dew_point_val, "%d.%02d", dp_int, dp_dec);
    }
    
    /* 更新人体检测显示 - zigbee_label_human_detected_val */
    if (ui->zigbee_label_human_detected_val != NULL) {
        lv_label_set_text(ui->zigbee_label_human_detected_val, 
                          zigbee_data->human_detected ? "有人" : "无人");
        /* 根据检测结果设置颜色 */
        lv_color_t color = zigbee_data->human_detected ? 
                           lv_color_hex(0xFF4444) : lv_color_hex(0x44FF44);
        lv_obj_set_style_text_color(ui->zigbee_label_human_detected_val, color, LV_PART_MAIN|LV_STATE_DEFAULT);
    }
    
    /* 更新震动检测显示 - zigbee_label_vibration_val */
    if (ui->zigbee_label_vibration_val != NULL) {
        lv_label_set_text(ui->zigbee_label_vibration_val, 
                          zigbee_data->vibration ? "检测到" : "无震动");
        /* 根据检测结果设置颜色 */
        lv_color_t color = zigbee_data->vibration ? 
                           lv_color_hex(0xFF8800) : lv_color_hex(0x44FF44);
        lv_obj_set_style_text_color(ui->zigbee_label_vibration_val, color, LV_PART_MAIN|LV_STATE_DEFAULT);
    }
    
    /* 更新数据包序列号显示 - zigbee_label_32 */
    if (ui->zigbee_label_32 != NULL) {
        lv_label_set_text_fmt(ui->zigbee_label_32, "%u", zigbee_data->count);
    }
}
