# 🏠 智能家居物联网控制系统

基于 **LVGL** 图形库和 **MQTT** 通信协议的智能家居物联网控制系统，运行于 **GEC6818** 开发板（ARM Linux 嵌入式平台）。

![Platform](https://img.shields.io/badge/Platform-GEC6818-blue)
![LVGL](https://img.shields.io/badge/LVGL-v8.3-green)
![Protocol](https://img.shields.io/badge/Protocol-MQTT-orange)
![License](https://img.shields.io/badge/License-MIT-brightgreen)

---

## 📋 项目简介

本项目是一个功能完整的智能家居物联网控制系统，具有以下特点：

- 🎨 **精美的图形界面**：基于 LVGL 图形库，提供 800x480 分辨率的触摸屏交互界面
- 📡 **MQTT 物联网通信**：通过 MQTT 协议实现设备间的实时数据传输
- 🌡️ **多传感器数据展示**：支持温度、湿度、光照等环境传感器数据的实时显示
- 📊 **数据可视化**：使用图表展示传感器数据的历史趋势
- 💡 **设备远程控制**：支持 LED、蜂鸣器等设备的远程开关控制
- 🔗 **ZigBee 设备集成**：支持 ZigBee 无线传感器网络的数据接入

---

## 🗂️ 项目结构

```
lvgl/
├── main.c                  # 主程序入口
├── Makefile                # 编译配置文件
├── lv_conf.h               # LVGL 配置文件
├── lv_drv_conf.h           # LVGL 驱动配置
│
├── custom/                 # 自定义功能模块
│   ├── custom.c/h          # 自定义初始化和业务逻辑
│   ├── mqtt_client.c/h     # MQTT 客户端库
│   └── custom.mk           # 自定义模块编译配置
│
├── generated/              # GUI Guider 生成的代码
│   ├── gui_guider.c/h      # UI 界面定义
│   ├── events_init.c/h     # 事件处理
│   ├── setup_scr_Home.c    # 主页界面布局
│   ├── setup_scr_zigbee.c  # ZigBee 界面布局
│   ├── widgets_init.c/h    # 控件初始化
│   ├── images/             # 图片资源
│   └── guider_fonts/       # 字体资源
│
├── lvgl/                   # LVGL 图形库源码
├── lv_drivers/             # LVGL 驱动 (fbdev, evdev)
└── dclock/                 # 数字时钟组件
```

---

## ✨ 功能特性

### 🏠 主页 (Home)

| 功能 | 描述 |
|------|------|
| 温度显示 | 实时显示环境温度，带弧形进度条和颜色指示 |
| 湿度显示 | 实时显示环境湿度百分比 |
| 光照显示 | 实时显示光照强度 (Lux) |
| 数据图表 | 折线图展示传感器数据历史趋势 |
| LED 控制 | 4 路 LED 开关控制 |
| 蜂鸣器控制 | 蜂鸣器开关控制 |
| 菜单导航 | 滑动式菜单，快速切换页面 |

### 📡 ZigBee 传感器页面

| 功能 | 描述 |
|------|------|
| 温度 | ZigBee 传感器温度数据 |
| 湿度 | ZigBee 传感器湿度数据 |
| 光照强度 | 光照传感器数据 (Lux) |
| 露点温度 | 计算得出的露点温度 |
| 人体检测 | 红外人体检测状态 |
| 震动检测 | 震动传感器状态 |
| 数据包计数 | 接收到的数据包序列号 |

---

## 📡 MQTT 通信

### 订阅主题

| 主题 | 说明 | 数据格式 |
|------|------|----------|
| `stm32/sensor/data` | STM32 传感器数据 | `{"temp":25.5, "humi":60.0, "light":1000}` |
| `zigbee/sensor/data` | ZigBee 传感器数据 | `{"mac":"...", "temperature":21.43, "humidity":77.32, ...}` |

### 发布主题

| 主题 | 说明 | 数据格式 |
|------|------|----------|
| `stm32/control` | 设备控制命令 | `{"led1":true}` 或 `{"beep":false}` |

### 默认配置

```c
#define MQTT_DEFAULT_HOST     "47.107.34.158"
#define MQTT_DEFAULT_PORT     1883
#define MQTT_DEFAULT_USERNAME "stm32"
#define MQTT_DEFAULT_PASSWORD "123456"
```

---

## 🛠️ 编译与运行

### 环境要求

- **交叉编译工具链**：`arm-linux-gcc`
- **目标平台**：GEC6818 开发板 (ARM Cortex-A53)
- **显示设备**：800x480 触摸屏 (Framebuffer: `/dev/fb0`)
- **依赖库**：
  - `libfreetype` (FreeType 字体库)
  - `libpthread` (POSIX 线程库)
  - `mosquitto_sub/mosquitto_pub` (MQTT 工具)

### 编译步骤

```bash
# 1. 克隆项目（包含子模块）
git clone --recursive <repository_url>
cd lvgl

# 2. 编译项目
make

# 3. 清理编译产物
make clean
```

### 运行

```bash
# 将编译生成的 lvgl_demo2 复制到开发板
scp lvgl_demo2 root@<board_ip>:/root/

# 在开发板上运行
./lvgl_demo2
```

---

## 📚 核心 API

### MQTT 客户端 API

```c
// 初始化 MQTT 客户端
int mqtt_client_init(mqtt_client_t *client);

// 配置 Broker 连接参数
int mqtt_client_set_broker(mqtt_client_t *client, 
    const char *host, uint16_t port, const char *topic);

// 配置认证信息
int mqtt_client_set_auth(mqtt_client_t *client, 
    const char *username, const char *password);

// 注册传感器数据回调
int mqtt_client_set_sensor_callback(mqtt_client_t *client, 
    mqtt_sensor_data_cb_t callback, void *user_data);

// 注册 ZigBee 数据回调
int mqtt_client_set_zigbee_callback(mqtt_client_t *client, 
    mqtt_zigbee_data_cb_t callback, void *user_data);

// 启动订阅
int mqtt_client_start(mqtt_client_t *client);

// 发布消息
int mqtt_client_publish(mqtt_client_t *client, 
    const char *topic, const char *message);

// 发布 LED 控制命令
int mqtt_client_publish_led(mqtt_client_t *client, 
    const char *led_name, bool state);
```

### UI 集成函数

```c
// 初始化并启动 MQTT
int mqtt_init_and_start(lv_ui *ui);

// 停止 MQTT
void mqtt_stop_and_deinit(void);

// 获取传感器数据
mqtt_sensor_data_t* mqtt_get_sensor_data(void);

// 获取 ZigBee 数据
mqtt_zigbee_data_t* mqtt_get_zigbee_data(void);

// 获取 MQTT 客户端句柄
mqtt_client_t* mqtt_get_client(void);
```

---

## 💻 核心代码示例

本节展示项目中的核心技术实现，帮助理解系统架构和关键代码。

### 1. 系统初始化流程

```c
/* main.c - 主程序入口 */
int main(void)
{
    /* LittlevGL 初始化 */
    lv_init();

    /* Linux Framebuffer 设备初始化 */
    fbdev_init();

    /* 创建显示缓冲区 */
    static lv_color_t buf[128 * 1024];
    static lv_disp_draw_buf_t disp_buf;
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, 128 * 1024);

    /* 注册显示驱动 (800x480) */
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf   = &disp_buf;
    disp_drv.flush_cb   = fbdev_flush;
    disp_drv.hor_res    = 800;
    disp_drv.ver_res    = 480;
    lv_disp_drv_register(&disp_drv);

    /* 初始化触摸输入设备 */
    evdev_init();
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = evdev_read;
    lv_indev_drv_register(&indev_drv);

    /* 设置 UI 并初始化自定义逻辑 */
    setup_ui(&guider_ui);
    custom_init(&guider_ui);   /* 启动 MQTT */
    events_init(&guider_ui);

    /* 主循环 */
    while(1) {
        lv_timer_handler();
        usleep(5000);  /* 5ms 刷新周期 */
    }

    return 0;
}
```

### 2. MQTT 客户端初始化与回调注册

```c
/* custom.c - MQTT 初始化与启动 */
static mqtt_client_t g_mqtt_client;
static lv_ui *g_ui = NULL;

int mqtt_init_and_start(lv_ui *ui)
{
    int ret;
    
    if (ui == NULL) {
        printf("[MQTT] 错误: UI句柄为空\n");
        return -1;
    }
    
    g_ui = ui;
    
    /* 1. 初始化 MQTT 客户端 */
    ret = mqtt_client_init(&g_mqtt_client);
    if (ret != MQTT_OK) {
        printf("[MQTT] 初始化失败: %d\n", ret);
        return ret;
    }
    
    /* 2. 可选：自定义 Broker 配置 */
    // mqtt_client_set_broker(&g_mqtt_client, "192.168.1.100", 1883, "sensor/data");
    // mqtt_client_set_auth(&g_mqtt_client, "user", "password");
    
    /* 3. 注册传感器数据回调 */
    mqtt_client_set_sensor_callback(&g_mqtt_client, mqtt_sensor_data_callback, ui);
    
    /* 4. 注册 ZigBee 传感器数据回调 */
    mqtt_client_set_zigbee_callback(&g_mqtt_client, mqtt_zigbee_data_callback, ui);
    
    /* 5. 启动 MQTT 订阅线程 */
    ret = mqtt_client_start(&g_mqtt_client);
    if (ret != MQTT_OK) {
        printf("[MQTT] 启动失败: %d\n", ret);
        return ret;
    }
    
    printf("[MQTT] 客户端已启动，等待数据...\n");
    return 0;
}
```

### 3. 传感器数据回调与 UI 更新

```c
/* 当收到 MQTT 传感器数据时，自动更新 LVGL 界面 */
static void mqtt_sensor_data_callback(const mqtt_sensor_data_t *sensor_data, void *user_data)
{
    lv_ui *ui = (lv_ui *)user_data;
    
    if (sensor_data == NULL || ui == NULL) return;
    
    /* 安全检查：确保当前页面是 Home 且对象有效 */
    if (ui->Home == NULL || !lv_obj_is_valid(ui->Home) || lv_scr_act() != ui->Home) {
        printf("[MQTT UI] Home页面未激活，跳过UI更新\n");
        return;
    }
    
    /* 更新温度标签 (使用整数避免浮点格式化问题) */
    if (ui->Home_label_temp_val != NULL) {
        int temp_int = (int)sensor_data->temp;
        int temp_dec = (int)((sensor_data->temp - temp_int) * 10);
        lv_label_set_text_fmt(ui->Home_label_temp_val, "%d.%d", temp_int, temp_dec);
    }
    
    /* 更新湿度标签 */
    if (ui->Home_label_wet_val != NULL) {
        int humi_int = (int)sensor_data->humi;
        int humi_dec = (int)((sensor_data->humi - humi_int) * 10);
        lv_label_set_text_fmt(ui->Home_label_wet_val, "%d.%d", humi_int, humi_dec);
    }
    
    /* 更新弧形进度条 */
    if (ui->Home_arc_temp != NULL) {
        int16_t arc_value = (int16_t)(sensor_data->temp);
        if (arc_value < 0) arc_value = 0;
        if (arc_value > 100) arc_value = 100;
        lv_arc_set_value(ui->Home_arc_temp, arc_value);
    }
    
    /* 根据温度设置动态颜色 */
    lv_color_t temp_color;
    if (sensor_data->temp <= 15.0f) {
        temp_color = lv_color_hex(0x16cfa1);  /* 低温 - 绿色 */
    } else if (sensor_data->temp <= 28.0f) {
        temp_color = lv_color_hex(0xc2dd0a);  /* 常温 - 黄绿色 */
    } else {
        temp_color = lv_color_hex(0xe4400d);  /* 高温 - 红色 */
    }
    
    /* 应用颜色到弧形进度条 */
    if (ui->Home_arc_temp != NULL) {
        lv_obj_set_style_arc_color(ui->Home_arc_temp, temp_color, LV_PART_INDICATOR);
        lv_obj_set_style_bg_color(ui->Home_arc_temp, temp_color, LV_PART_KNOB);
    }
}
```

### 4. 图表数据实时更新

```c
/* 更新折线图数据 - 滚动式数据展示 */
void update_chart_data(lv_ui *ui, const mqtt_sensor_data_t *sensor_data)
{
    /* 获取图表的三个数据系列 */
    lv_chart_series_t *ser_light = lv_chart_get_series_next(ui->Home_chart_temp, NULL);
    lv_chart_series_t *ser_humi  = lv_chart_get_series_next(ui->Home_chart_temp, ser_light);
    lv_chart_series_t *ser_temp  = lv_chart_get_series_next(ui->Home_chart_temp, ser_humi);
    
    /* 获取数据数组 */
    lv_coord_t *arr_light = lv_chart_get_y_array(ui->Home_chart_temp, ser_light);
    lv_coord_t *arr_humi  = lv_chart_get_y_array(ui->Home_chart_temp, ser_humi);
    lv_coord_t *arr_temp  = lv_chart_get_y_array(ui->Home_chart_temp, ser_temp);
    
    /* 滚动：将所有数据点向左移动一位 */
    for (int i = 0; i < 16 - 1; i++) {
        arr_light[i] = arr_light[i + 1];
        arr_humi[i]  = arr_humi[i + 1];
        arr_temp[i]  = arr_temp[i + 1];
    }
    
    /* 在末尾添加最新数据 */
    arr_light[15] = (lv_coord_t)sensor_data->light;
    arr_humi[15]  = (lv_coord_t)sensor_data->humi;
    arr_temp[15]  = (lv_coord_t)sensor_data->temp;
    
    /* 刷新图表显示 */
    lv_chart_refresh(ui->Home_chart_temp);
}
```

### 5. LED 控制事件处理

```c
/* events_init.c - LED 开关事件处理示例 */
static void Home_sw_led1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    
    if (code == LV_EVENT_VALUE_CHANGED) {
        /* 获取开关状态 */
        lv_obj_t *sw = lv_event_get_target(e);
        bool state = lv_obj_has_state(sw, LV_STATE_CHECKED);
        
        /* 通过 MQTT 发送控制命令 */
        mqtt_client_t *client = mqtt_get_client();
        if (client != NULL) {
            mqtt_client_publish_led(client, "led1", state);
            /* 发送的 JSON: {"led1":true} 或 {"led1":false} */
        }
    }
}
```

### 6. MQTT 消息发布

```c
/* mqtt_client.c - 发布 LED 控制消息 */
int mqtt_client_publish_led(mqtt_client_t *client, const char *led_name, bool state)
{
    if (client == NULL || led_name == NULL) {
        return MQTT_ERR_INVALID_PARAM;
    }

    /* 构建 JSON 消息 */
    char json_msg[64] = {0};
    snprintf(json_msg, sizeof(json_msg), 
             "{\"%s\":%s}", led_name, state ? "true" : "false");

    /* 使用 mosquitto_pub 发布到控制主题 */
    char pub_cmd[512] = {0};
    snprintf(pub_cmd, sizeof(pub_cmd),
             "mosquitto_pub -h %s -p %d -t \"%s\" -u %s -P %s -m '%s'",
             client->config.host,
             client->config.port,
             MQTT_DEFAULT_CONTROL_TOPIC,  /* stm32/control */
             client->config.username,
             client->config.password,
             json_msg);
    
    /* 执行发布命令 */
    int ret = system(pub_cmd);
    if (ret != 0) {
        printf("[MQTT] 发布失败 (返回码: %d)\n", ret);
        return MQTT_ERR_POPEN_FAILED;
    }
    
    printf("[MQTT] 发布成功: %s -> %s\n", MQTT_DEFAULT_CONTROL_TOPIC, json_msg);
    return MQTT_OK;
}
```

### 7. JSON 数据解析

```c
/* mqtt_client.c - 解析传感器 JSON 数据 */
bool mqtt_parse_sensor_json(const char *json_str, mqtt_sensor_data_t *data)
{
    if (json_str == NULL || data == NULL) return false;
    
    memset(data, 0, sizeof(mqtt_sensor_data_t));
    
    /* 使用 sscanf 解析简单 JSON 格式 */
    /* 格式: {"temp":25.5,"humi":60.0,"light":500.0} */
    int parsed = sscanf(json_str, 
                        "{\"temp\":%f,\"humi\":%f,\"light\":%f}", 
                        &data->temp, &data->humi, &data->light);
    
    if (parsed == 3) {
        data->timestamp = (uint32_t)time(NULL);
        data->valid = true;
        return true;
    }
    
    return false;
}

/* 解析 ZigBee 传感器复杂 JSON */
bool mqtt_parse_zigbee_json(const char *json_str, mqtt_zigbee_data_t *data)
{
    if (json_str == NULL || data == NULL) return false;
    
    memset(data, 0, sizeof(mqtt_zigbee_data_t));
    
    /* 使用字符串查找解析各字段 */
    char *ptr;
    
    /* 解析 temperature */
    ptr = strstr(json_str, "\"temperature\":");
    if (ptr != NULL) {
        data->temperature = (float)atof(ptr + 14);
    }
    
    /* 解析 humidity */
    ptr = strstr(json_str, "\"humidity\":");
    if (ptr != NULL) {
        data->humidity = (float)atof(ptr + 11);
    }
    
    /* 解析 illumination */
    ptr = strstr(json_str, "\"illumination\":");
    if (ptr != NULL) {
        data->illumination = (uint32_t)atoi(ptr + 15);
    }
    
    /* 解析 human_detected (布尔值) */
    ptr = strstr(json_str, "\"human_detected\":");
    if (ptr != NULL) {
        data->human_detected = (strncmp(ptr + 17, "true", 4) == 0);
    }
    
    data->timestamp = (uint32_t)time(NULL);
    data->valid = true;
    return true;
}
```

### 8. MQTT 订阅线程

```c
/* mqtt_client.c - 使用 popen 订阅 MQTT 主题 */
static void *mqtt_subscribe_thread(void *arg)
{
    mqtt_client_t *client = (mqtt_client_t *)arg;
    
    /* 构建 mosquitto_sub 命令 */
    char sub_cmd[512] = {0};
    snprintf(sub_cmd, sizeof(sub_cmd),
             "mosquitto_sub -h %s -p %d -t \"%s\" -u %s -P %s",
             client->config.host,      /* 47.107.34.158 */
             client->config.port,      /* 1883 */
             client->config.topic,     /* stm32/sensor/data */
             client->config.username,  /* stm32 */
             client->config.password); /* 123456 */
    
    /* 启动订阅进程 */
    FILE *fp = popen(sub_cmd, "r");
    if (fp == NULL) {
        printf("[MQTT] 订阅失败\n");
        return NULL;
    }
    
    client->state = MQTT_STATE_CONNECTED;
    char buf[1024] = {0};
    
    /* 循环读取订阅数据 */
    while (client->running) {
        if (fgets(buf, sizeof(buf) - 1, fp) != NULL) {
            /* 去除换行符 */
            size_t len = strlen(buf);
            while (len > 0 && buf[len-1] == '\n') buf[--len] = '\0';
            
            if (len > 0) {
                printf("[MQTT] 收到: %s\n", buf);
                
                /* 解析并回调 */
                mqtt_sensor_data_t sensor_data;
                if (mqtt_parse_sensor_json(buf, &sensor_data)) {
                    if (client->sensor_cb != NULL) {
                        client->sensor_cb(&sensor_data, client->user_data);
                    }
                }
            }
        }
    }
    
    pclose(fp);
    return NULL;
}
```

### 9. 页面切换动画

```c
/* events_init.c - 带动画的页面切换 */
static void Home_imgbtn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    
    if (code == LV_EVENT_CLICKED) {
        /* 加载 ZigBee 页面，带右滑动画效果 */
        ui_load_scr_animation(
            &guider_ui,               /* UI 句柄 */
            &guider_ui.zigbee,        /* 目标页面 */
            guider_ui.zigbee_del,     /* 目标页面删除标志 */
            &guider_ui.Home_del,      /* 当前页面删除标志 */
            setup_scr_zigbee,         /* 页面初始化函数 */
            LV_SCR_LOAD_ANIM_OVER_RIGHT,  /* 动画效果 */
            200,                      /* 动画时长 (ms) */
            200,                      /* 延迟时间 (ms) */
            false,                    /* 自动删除旧页面 */
            true                      /* 在后台创建页面 */
        );
    }
}
```

---

## 🎨 界面预览

系统提供两个主要页面：

### 主页 (Home Screen)
- 传感器数据实时显示（温度、湿度、光照）
- 弧形进度条可视化
- 实时数据趋势图表
- 设备控制开关（LED1-4, 蜂鸣器）
- 菜单导航

### ZigBee 页面
- ZigBee 无线传感器数据展示
- 人体检测和震动检测状态
- MAC 地址和数据包计数显示

---

## 🔧 配置说明

### LVGL 配置 (`lv_conf.h`)

主要配置项：
- `LV_HOR_RES_MAX`: 水平分辨率 (800)
- `LV_VER_RES_MAX`: 垂直分辨率 (480)
- `LV_COLOR_DEPTH`: 颜色深度 (32)
- `LV_USE_FREETYPE`: FreeType 字体支持

### 驱动配置 (`lv_drv_conf.h`)

- `USE_FBDEV`: 启用 Framebuffer 驱动
- `USE_EVDEV`: 启用触摸输入驱动
- `EVDEV_NAME`: 触摸屏设备路径

---

## 🤝 相关项目

本系统通常与以下项目配合使用：

- **STM32 传感器节点**：采集 DHT11 温湿度、光照传感器数据并通过 ESP8266 上传到 MQTT Broker
- **ZigBee 协调器**：收集 ZigBee 网络内传感器节点数据

---

## 📄 许可证

本项目采用 [MIT License](LICENSE) 开源许可证。

LVGL 图形库版权归 Littlev Graphics Library 所有。

部分代码由 NXP GUI Guider 工具生成，遵循 NXP 软件许可协议。

---

## 📞 联系方式

如有问题或建议，欢迎提交 Issue 或 Pull Request。

---

<p align="center">
  <i>使用 ❤️ 和 LVGL 构建</i>
</p>
