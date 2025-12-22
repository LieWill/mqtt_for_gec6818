/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif

#include "custom.h"
static lv_timer_t  * home_task;
static lv_timer_t * chart_timer;
static lv_timer_t * firefighting_timer;

static void Home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        home_task = lv_timer_create(home_timer_cb, 80, &guider_ui);
        chart_timer = lv_timer_create(chart_line_timer_cb, 1000, &guider_ui);
        break;
    }
    case LV_EVENT_SCREEN_UNLOADED:
    {
        lv_timer_del(home_task);
        lv_timer_del(chart_timer);
        break;
    }
    default:
        break;
    }
}

static void Home_chart_temp_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_set_style_text_color(guider_ui.Home_btn_humi_, lv_color_hex(0xff0000), LV_PART_MAIN|LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(guider_ui.Home_btn_light_, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(guider_ui.Home_btn_temp_, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
        break;
    }
    default:
        break;
    }
}

static void Home_btn_temp__event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_set_style_text_color(guider_ui.Home_btn_temp_, lv_color_hex(0xff0000), LV_PART_MAIN|LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(guider_ui.Home_btn_humi_, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(guider_ui.Home_btn_light_, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
        // 仅显示第一个系列（橙色）的折线，其他保持隐藏
        lv_obj_set_style_line_opa(guider_ui.Home_chart_temp, 0, LV_PART_INDICATOR);
        break;
    }
    default:
        break;
    }
}

static void Home_btn_humi__event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_set_style_text_color(guider_ui.Home_btn_humi_, lv_color_hex(0xff0000), LV_PART_MAIN|LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(guider_ui.Home_btn_temp_, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(guider_ui.Home_btn_light_, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
        break;
    }
    default:
        break;
    }
}

static void Home_btn_light__event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_set_style_text_color(guider_ui.Home_btn_light_, lv_color_hex(0xff0000), LV_PART_MAIN|LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(guider_ui.Home_btn_humi_, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(guider_ui.Home_btn_humi_, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
        break;
    }
    default:
        break;
    }
}

static void Home_btn_menu_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_clear_flag(guider_ui.Home_cont_menu, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void Home_cont_menu_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_add_flag(guider_ui.Home_cont_menu, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void Home_sw_led1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        lv_obj_t * status_obj = lv_event_get_target(e);
        int status = lv_obj_has_state(status_obj, LV_STATE_CHECKED) ? true : false;

        switch (status) {
        case (true):
        {
            //LED1打开
            mqtt_client_t *client = mqtt_get_client();
            if (client != NULL) {
                mqtt_client_publish_led(client, "led1", true);
            }
            break;
        }
        case (false):
        {
            //LED1关闭
            mqtt_client_t *client = mqtt_get_client();
            if (client != NULL) {
                mqtt_client_publish_led(client, "led1", false);
            }
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void Home_sw_led2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        lv_obj_t * status_obj = lv_event_get_target(e);
        int status = lv_obj_has_state(status_obj, LV_STATE_CHECKED) ? true : false;

        switch (status) {
        case (true):
        {
            //LED2打开
            mqtt_client_t *client = mqtt_get_client();
            if (client != NULL) {
                mqtt_client_publish_led(client, "led2", true);
            }
            break;
        }
        case (false):
        {
            //LED2关闭
            mqtt_client_t *client = mqtt_get_client();
            if (client != NULL) {
                mqtt_client_publish_led(client, "led2", false);
            }
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void Home_sw_led3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        lv_obj_t * status_obj = lv_event_get_target(e);
        int status = lv_obj_has_state(status_obj, LV_STATE_CHECKED) ? true : false;

        switch (status) {
        case (true):
        {
            //LED3打开
            mqtt_client_t *client = mqtt_get_client();
            if (client != NULL) {
                mqtt_client_publish_led(client, "led3", true);
            }
            break;
        }
        case (false):
        {
            //LED3关闭
            mqtt_client_t *client = mqtt_get_client();
            if (client != NULL) {
                mqtt_client_publish_led(client, "led3", false);
            }
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void Home_sw_beep_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        lv_obj_t * status_obj = lv_event_get_target(e);
        int status = lv_obj_has_state(status_obj, LV_STATE_CHECKED) ? true : false;

        switch (status) {
        case (true):
        {
            //蜂鸣器打开
            mqtt_client_t *client = mqtt_get_client();
            if (client != NULL) {
                mqtt_client_publish_led(client, "beep", true);
            }
            break;
        }
        case (false):
        {
            //蜂鸣器关闭
            mqtt_client_t *client = mqtt_get_client();
            if (client != NULL) {
                mqtt_client_publish_led(client, "beep", false);
            }
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void Home_sw_led4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        lv_obj_t * status_obj = lv_event_get_target(e);
        int status = lv_obj_has_state(status_obj, LV_STATE_CHECKED) ? true : false;

        switch (status) {
        case (true):
        {
            //LED4打开
            mqtt_client_t *client = mqtt_get_client();
            if (client != NULL) {
                mqtt_client_publish_led(client, "led4", true);
            }
            break;
        }
        case (false):
        {
            //LED4关闭
            mqtt_client_t *client = mqtt_get_client();
            if (client != NULL) {
                mqtt_client_publish_led(client, "led4", false);
            }
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void Home_imgbtn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.zigbee, guider_ui.zigbee_del, &guider_ui.Home_del, setup_scr_zigbee, LV_SCR_LOAD_ANIM_OVER_RIGHT, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_Home (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->Home, Home_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Home_chart_temp, Home_chart_temp_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Home_btn_temp_, Home_btn_temp__event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Home_btn_humi_, Home_btn_humi__event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Home_btn_light_, Home_btn_light__event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Home_btn_menu, Home_btn_menu_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Home_cont_menu, Home_cont_menu_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Home_sw_led1, Home_sw_led1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Home_sw_led2, Home_sw_led2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Home_sw_led3, Home_sw_led3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Home_sw_beep, Home_sw_beep_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Home_sw_led4, Home_sw_led4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Home_imgbtn_1, Home_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
}

static void zigbee_btn_menu_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_clear_flag(guider_ui.zigbee_cont_menu, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void zigbee_cont_menu_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_add_flag(guider_ui.zigbee_cont_menu, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void zigbee_imgbtn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.Home, guider_ui.Home_del, &guider_ui.zigbee_del, setup_scr_Home, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_zigbee (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->zigbee_btn_menu, zigbee_btn_menu_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->zigbee_cont_menu, zigbee_cont_menu_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->zigbee_imgbtn_2, zigbee_imgbtn_2_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
