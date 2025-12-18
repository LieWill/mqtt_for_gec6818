# MQTT消息获取库使用说明

## 概述

本库提供了一个基于 `mosquitto_sub` 的MQTT消息订阅和解析功能，专门为GEC6818开发板的LVGL项目设计。

## 文件结构

```
custom/
├── mqtt_client.h    # MQTT库头文件
├── mqtt_client.c    # MQTT库实现
├── custom.h         # 自定义头文件（已包含MQTT集成函数）
└── custom.c         # 自定义实现（已包含MQTT集成示例）
```

## 前提条件

- 开发板需要安装 `mosquitto-clients` 包（包含 `mosquitto_sub` 命令）
- 开发板需要连接到网络

## 快速开始

### 方式1：在 main.c 中初始化

```c
#include "custom/custom.h"

int main(void)
{
    // ... LVGL初始化代码 ...
    
    setup_ui(&guider_ui);
    events_init(&guider_ui);
    
    // 启动MQTT客户端
    mqtt_init_and_start(&guider_ui);
    
    while(1) {
        lv_timer_handler();
        usleep(5000);
    }
    
    // 程序退出前停止MQTT
    mqtt_stop_and_deinit();
    
    return 0;
}
```

### 方式2：在 custom_init 中初始化

取消 `custom.c` 中 `custom_init()` 函数里的注释：

```c
void custom_init(lv_ui *ui)
{
    /* 初始化MQTT客户端 */
    mqtt_init_and_start(ui);
}
```

## API 详解

### 1. 初始化客户端

```c
mqtt_client_t client;
mqtt_client_init(&client);
```

### 2. 配置Broker（可选，有默认值）

```c
// 默认值: 47.107.34.158:1883, 主题: stm32/sensor/data
mqtt_client_set_broker(&client, "192.168.1.100", 1883, "sensor/data");
```

### 3. 配置认证（可选）

```c
// 默认值: 用户名=stm32, 密码=123456
mqtt_client_set_auth(&client, "username", "password");

// 禁用认证
mqtt_client_set_auth(&client, NULL, NULL);
```

### 4. 注册回调函数

```c
// 原始数据回调
void my_raw_callback(const char *data, void *user_data) {
    printf("收到原始数据: %s\n", data);
}
mqtt_client_set_raw_callback(&client, my_raw_callback, NULL);

// 传感器数据回调（已解析JSON）
void my_sensor_callback(const mqtt_sensor_data_t *sensor_data, void *user_data) {
    printf("温度: %.1f℃, 湿度: %.1f%%\n", sensor_data->temp, sensor_data->humi);
}
mqtt_client_set_sensor_callback(&client, my_sensor_callback, NULL);
```

### 5. 启动/停止

```c
mqtt_client_start(&client);   // 启动订阅线程
mqtt_client_stop(&client);    // 停止订阅线程
mqtt_client_deinit(&client);  // 反初始化
```

### 6. 获取状态和数据

```c
mqtt_state_t state = mqtt_client_get_state(&client);

mqtt_sensor_data_t data;
mqtt_client_get_last_data(&client, &data);
if (data.valid) {
    printf("最新温度: %.1f\n", data.temp);
}
```

## 支持的JSON格式

库自动解析以下JSON格式：

```json
{"temp":25.5,"humi":60.0,"light":500.0}
{"temperature":25.5,"humidity":60.0,"lux":500.0}
{"temp":25.5,"humi":60.0}
{"temp":25.5}
25.5  // 纯数字也支持
```

## 修改默认配置

在 `mqtt_client.h` 中修改以下宏定义：

```c
#define MQTT_DEFAULT_HOST       "47.107.34.158"
#define MQTT_DEFAULT_PORT       1883
#define MQTT_DEFAULT_TOPIC      "stm32/sensor/data"
#define MQTT_DEFAULT_USERNAME   "stm32"
#define MQTT_DEFAULT_PASSWORD   "123456"
```

## 调试开关

在 `mqtt_client.c` 中修改：

```c
#define MQTT_DEBUG_ENABLE   1  // 1=开启调试输出, 0=关闭
```

## 注意事项

1. **线程安全**: 回调函数在独立线程中执行，如需更新UI，请确保在LVGL主循环中处理
2. **网络连接**: 确保开发板能访问MQTT Broker
3. **mosquitto安装**: 确保开发板已安装 `mosquitto-clients`

## 测试命令

在PC上发布测试数据：

```bash
mosquitto_pub -h 47.107.34.158 -p 1883 -t stm32/sensor/data -u stm32 -P 123456 -m '{"temp":25.5,"humi":60.0,"light":500.0}'
```
