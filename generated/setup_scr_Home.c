/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



int Home_digital_clock_time_min_value = 25;
int Home_digital_clock_time_hour_value = 11;
int Home_digital_clock_time_sec_value = 50;
void setup_scr_Home(lv_ui *ui)
{
    //Write codes Home
    ui->Home = lv_obj_create(NULL);
    lv_obj_set_size(ui->Home, 800, 480);
    lv_obj_set_scrollbar_mode(ui->Home, LV_SCROLLBAR_MODE_OFF);

    //Write style for Home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->Home, &_sub_page_bak_800x480, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->Home, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->Home, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Home_cont_dev_control
    ui->Home_cont_dev_control = lv_obj_create(ui->Home);
    lv_obj_set_pos(ui->Home_cont_dev_control, 296, 55);
    lv_obj_set_size(ui->Home_cont_dev_control, 495, 407);
    lv_obj_set_scrollbar_mode(ui->Home_cont_dev_control, LV_SCROLLBAR_MODE_OFF);

    //Write style for Home_cont_dev_control, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Home_cont_dev_control, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_cont_dev_control, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Home_cont_dev_control, 181, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Home_cont_dev_control, lv_color_hex(0x154870), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Home_cont_dev_control, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_cont_dev_control, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_cont_dev_control, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_cont_dev_control, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_cont_dev_control, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_cont_dev_control, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Home_label_dev
    ui->Home_label_dev = lv_label_create(ui->Home_cont_dev_control);
    lv_label_set_text(ui->Home_label_dev, "log数据\n");
    lv_label_set_long_mode(ui->Home_label_dev, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Home_label_dev, 0, 1);
    lv_obj_set_size(ui->Home_label_dev, 460, 40);

    //Write style for Home_label_dev, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Home_label_dev, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_label_dev, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_label_dev, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_label_dev, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Home_label_dev, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Home_label_dev, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Home_label_dev, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_label_dev, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Home_label_dev, 59, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Home_label_dev, lv_color_hex(0x1e1e1e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Home_label_dev, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_label_dev, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_label_dev, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_label_dev, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_label_dev, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_label_dev, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Home_chart_temp
    ui->Home_chart_temp = lv_chart_create(ui->Home_cont_dev_control);
    lv_chart_set_type(ui->Home_chart_temp, LV_CHART_TYPE_LINE);
    lv_chart_set_div_line_count(ui->Home_chart_temp, 2, 2);
    lv_chart_set_point_count(ui->Home_chart_temp, 16);
    lv_chart_set_range(ui->Home_chart_temp, LV_CHART_AXIS_PRIMARY_Y, 10, 100);
    lv_chart_set_axis_tick(ui->Home_chart_temp, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 11, 1, true, 33);
    lv_chart_set_range(ui->Home_chart_temp, LV_CHART_AXIS_SECONDARY_Y, 0, 4000);
    lv_chart_set_axis_tick(ui->Home_chart_temp, LV_CHART_AXIS_SECONDARY_Y, 10, 5, 9, 1, true, 44);
    lv_chart_set_zoom_x(ui->Home_chart_temp, 256);
    lv_chart_set_zoom_y(ui->Home_chart_temp, 256);
    lv_obj_set_style_size(ui->Home_chart_temp, 0, LV_PART_INDICATOR);
    ui->Home_chart_temp_0 = lv_chart_add_series(ui->Home_chart_temp, lv_color_hex(0xff6500), LV_CHART_AXIS_PRIMARY_Y);
#if LV_USE_FREEMASTER == 0
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_0, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_0, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_0, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_0, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_0, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_0, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_0, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_0, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_0, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_0, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_0, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_0, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_0, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_0, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_0, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_0, 0);
#endif
    ui->Home_chart_temp_1 = lv_chart_add_series(ui->Home_chart_temp, lv_color_hex(0x00c4ff), LV_CHART_AXIS_PRIMARY_Y);
#if LV_USE_FREEMASTER == 0
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_1, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_1, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_1, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_1, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_1, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_1, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_1, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_1, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_1, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_1, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_1, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_1, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_1, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_1, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_1, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_1, 0);
#endif
    ui->Home_chart_temp_2 = lv_chart_add_series(ui->Home_chart_temp, lv_color_hex(0xebff00), LV_CHART_AXIS_SECONDARY_Y);
#if LV_USE_FREEMASTER == 0
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_2, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_2, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_2, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_2, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_2, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_2, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_2, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_2, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_2, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_2, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_2, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_2, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_2, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_2, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_2, 0);
    lv_chart_set_next_value(ui->Home_chart_temp, ui->Home_chart_temp_2, 0);
#endif
    lv_obj_set_pos(ui->Home_chart_temp, 50, 93);
    lv_obj_set_size(ui->Home_chart_temp, 392, 297);
    lv_obj_set_scrollbar_mode(ui->Home_chart_temp, LV_SCROLLBAR_MODE_OFF);

    //Write style for Home_chart_temp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Home_chart_temp, 58, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Home_chart_temp, lv_color_hex(0x00a8ff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Home_chart_temp, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Home_chart_temp, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->Home_chart_temp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->Home_chart_temp, lv_color_hex(0xe8e8e8), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->Home_chart_temp, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_chart_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->Home_chart_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_chart_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for Home_chart_temp, Part: LV_PART_TICKS, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->Home_chart_temp, lv_color_hex(0x77dfff), LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_chart_temp, &lv_font_montserratMedium_16, LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Home_chart_temp, 255, LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_line_width(ui->Home_chart_temp, 2, LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->Home_chart_temp, lv_color_hex(0xe8e8e8), LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->Home_chart_temp, 255, LV_PART_TICKS|LV_STATE_DEFAULT);

    //Write codes Home_btn_temp_
    ui->Home_btn_temp_ = lv_btn_create(ui->Home_cont_dev_control);
    ui->Home_btn_temp__label = lv_label_create(ui->Home_btn_temp_);
    lv_label_set_text(ui->Home_btn_temp__label, "温度");
    lv_label_set_long_mode(ui->Home_btn_temp__label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Home_btn_temp__label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Home_btn_temp_, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->Home_btn_temp__label, LV_PCT(100));
    lv_obj_set_pos(ui->Home_btn_temp_, 52, 53);
    lv_obj_set_size(ui->Home_btn_temp_, 94, 32);

    //Write style for Home_btn_temp_, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Home_btn_temp_, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Home_btn_temp_, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Home_btn_temp_, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Home_btn_temp_, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_btn_temp_, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_btn_temp_, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_btn_temp_, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_btn_temp_, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Home_btn_temp_, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_btn_temp_, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Home_btn_humi_
    ui->Home_btn_humi_ = lv_btn_create(ui->Home_cont_dev_control);
    ui->Home_btn_humi__label = lv_label_create(ui->Home_btn_humi_);
    lv_label_set_text(ui->Home_btn_humi__label, "湿度");
    lv_label_set_long_mode(ui->Home_btn_humi__label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Home_btn_humi__label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Home_btn_humi_, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->Home_btn_humi__label, LV_PCT(100));
    lv_obj_set_pos(ui->Home_btn_humi_, 176, 53);
    lv_obj_set_size(ui->Home_btn_humi_, 94, 32);

    //Write style for Home_btn_humi_, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Home_btn_humi_, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Home_btn_humi_, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Home_btn_humi_, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Home_btn_humi_, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_btn_humi_, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_btn_humi_, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_btn_humi_, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_btn_humi_, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Home_btn_humi_, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_btn_humi_, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Home_btn_light_
    ui->Home_btn_light_ = lv_btn_create(ui->Home_cont_dev_control);
    ui->Home_btn_light__label = lv_label_create(ui->Home_btn_light_);
    lv_label_set_text(ui->Home_btn_light__label, "光照");
    lv_label_set_long_mode(ui->Home_btn_light__label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Home_btn_light__label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Home_btn_light_, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->Home_btn_light__label, LV_PCT(100));
    lv_obj_set_pos(ui->Home_btn_light_, 312, 54);
    lv_obj_set_size(ui->Home_btn_light_, 94, 32);

    //Write style for Home_btn_light_, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Home_btn_light_, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Home_btn_light_, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Home_btn_light_, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Home_btn_light_, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_btn_light_, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_btn_light_, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_btn_light_, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_btn_light_, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Home_btn_light_, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_btn_light_, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Home_cont_temp
    ui->Home_cont_temp = lv_obj_create(ui->Home);
    lv_obj_set_pos(ui->Home_cont_temp, 63, 62);
    lv_obj_set_size(ui->Home_cont_temp, 222, 395);
    lv_obj_set_scrollbar_mode(ui->Home_cont_temp, LV_SCROLLBAR_MODE_OFF);

    //Write style for Home_cont_temp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Home_cont_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_cont_temp, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Home_cont_temp, 181, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Home_cont_temp, lv_color_hex(0x154870), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Home_cont_temp, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_cont_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_cont_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_cont_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_cont_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_cont_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Home_label_temp_tit
    ui->Home_label_temp_tit = lv_label_create(ui->Home_cont_temp);
    lv_label_set_text(ui->Home_label_temp_tit, "监控消息");
    lv_label_set_long_mode(ui->Home_label_temp_tit, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Home_label_temp_tit, -2, 3);
    lv_obj_set_size(ui->Home_label_temp_tit, 240, 40);

    //Write style for Home_label_temp_tit, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Home_label_temp_tit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_label_temp_tit, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_label_temp_tit, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_label_temp_tit, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Home_label_temp_tit, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Home_label_temp_tit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Home_label_temp_tit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_label_temp_tit, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Home_label_temp_tit, 59, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Home_label_temp_tit, lv_color_hex(0x1e1e1e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Home_label_temp_tit, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_label_temp_tit, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_label_temp_tit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_label_temp_tit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_label_temp_tit, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_label_temp_tit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Home_arc_temp
    ui->Home_arc_temp = lv_arc_create(ui->Home_cont_temp);
    lv_arc_set_mode(ui->Home_arc_temp, LV_ARC_MODE_NORMAL);
    lv_arc_set_range(ui->Home_arc_temp, 0, 40);
    lv_arc_set_bg_angles(ui->Home_arc_temp, 0, 360);
    lv_arc_set_value(ui->Home_arc_temp, 20);
    lv_arc_set_rotation(ui->Home_arc_temp, 90);
    lv_obj_set_pos(ui->Home_arc_temp, 11, 56);
    lv_obj_set_size(ui->Home_arc_temp, 102, 117);

    //Write style for Home_arc_temp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Home_arc_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Home_arc_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui->Home_arc_temp, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->Home_arc_temp, 45, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->Home_arc_temp, lv_color_hex(0xe7e8e8), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_arc_temp, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_arc_temp, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_arc_temp, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_arc_temp, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_arc_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_arc_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for Home_arc_temp, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_arc_width(ui->Home_arc_temp, 8, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->Home_arc_temp, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->Home_arc_temp, lv_color_hex(0x0eff85), LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for Home_arc_temp, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Home_arc_temp, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Home_arc_temp, lv_color_hex(0x0eff85), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Home_arc_temp, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->Home_arc_temp, 4, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes Home_arc_humi
    ui->Home_arc_humi = lv_arc_create(ui->Home_cont_temp);
    lv_arc_set_mode(ui->Home_arc_humi, LV_ARC_MODE_NORMAL);
    lv_arc_set_range(ui->Home_arc_humi, 0, 40);
    lv_arc_set_bg_angles(ui->Home_arc_humi, 0, 360);
    lv_arc_set_value(ui->Home_arc_humi, 10);
    lv_arc_set_rotation(ui->Home_arc_humi, 90);
    lv_obj_set_pos(ui->Home_arc_humi, 113, 172);
    lv_obj_set_size(ui->Home_arc_humi, 100, 100);

    //Write style for Home_arc_humi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Home_arc_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Home_arc_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui->Home_arc_humi, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->Home_arc_humi, 45, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->Home_arc_humi, lv_color_hex(0xe7e8e8), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_arc_humi, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_arc_humi, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_arc_humi, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_arc_humi, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_arc_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_arc_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for Home_arc_humi, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_arc_width(ui->Home_arc_humi, 8, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->Home_arc_humi, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->Home_arc_humi, lv_color_hex(0x00c8eb), LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for Home_arc_humi, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Home_arc_humi, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Home_arc_humi, lv_color_hex(0x00c8eb), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Home_arc_humi, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->Home_arc_humi, 4, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes Home_label_temp_val
    ui->Home_label_temp_val = lv_label_create(ui->Home_cont_temp);
    lv_label_set_text(ui->Home_label_temp_val, "28");
    lv_label_set_long_mode(ui->Home_label_temp_val, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Home_label_temp_val, 125, 121);
    lv_obj_set_size(ui->Home_label_temp_val, 37, 21);

    //Write style for Home_label_temp_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Home_label_temp_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_label_temp_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_label_temp_val, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_label_temp_val, &lv_font_montserratMedium_25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Home_label_temp_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Home_label_temp_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Home_label_temp_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_label_temp_val, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Home_label_temp_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_label_temp_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_label_temp_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_label_temp_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_label_temp_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_label_temp_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Home_label_wet_val
    ui->Home_label_wet_val = lv_label_create(ui->Home_cont_temp);
    lv_label_set_text(ui->Home_label_wet_val, "50");
    lv_label_set_long_mode(ui->Home_label_wet_val, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Home_label_wet_val, 26, 227);
    lv_obj_set_size(ui->Home_label_wet_val, 38, 24);

    //Write style for Home_label_wet_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Home_label_wet_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_label_wet_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_label_wet_val, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_label_wet_val, &lv_font_montserratMedium_25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Home_label_wet_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Home_label_wet_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Home_label_wet_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_label_wet_val, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Home_label_wet_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_label_wet_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_label_wet_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_label_wet_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_label_wet_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_label_wet_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Home_img_temp
    ui->Home_img_temp = lv_img_create(ui->Home_cont_temp);
    lv_obj_add_flag(ui->Home_img_temp, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Home_img_temp, &_temp_alpha_92x98);
    lv_img_set_pivot(ui->Home_img_temp, 50,50);
    lv_img_set_angle(ui->Home_img_temp, 0);
    lv_obj_set_pos(ui->Home_img_temp, 18, 62);
    lv_obj_set_size(ui->Home_img_temp, 92, 98);

    //Write style for Home_img_temp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Home_img_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Home_img_temp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_img_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Home_img_temp, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Home_img_humidity
    ui->Home_img_humidity = lv_img_create(ui->Home_cont_temp);
    lv_obj_add_flag(ui->Home_img_humidity, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Home_img_humidity, &_Humidity_alpha_56x68);
    lv_img_set_pivot(ui->Home_img_humidity, 50,50);
    lv_img_set_angle(ui->Home_img_humidity, 0);
    lv_obj_set_pos(ui->Home_img_humidity, 133, 186);
    lv_obj_set_size(ui->Home_img_humidity, 56, 68);

    //Write style for Home_img_humidity, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Home_img_humidity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Home_img_humidity, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_img_humidity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Home_img_humidity, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Home_label_temp_unit2
    ui->Home_label_temp_unit2 = lv_label_create(ui->Home_cont_temp);
    lv_label_set_text(ui->Home_label_temp_unit2, "℃");
    lv_label_set_long_mode(ui->Home_label_temp_unit2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Home_label_temp_unit2, 162, 119);
    lv_obj_set_size(ui->Home_label_temp_unit2, 28, 29);

    //Write style for Home_label_temp_unit2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Home_label_temp_unit2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_label_temp_unit2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_label_temp_unit2, lv_color_hex(0xdbff54), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_label_temp_unit2, &lv_font_SourceHanSerifSC_Regular_25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Home_label_temp_unit2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Home_label_temp_unit2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Home_label_temp_unit2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_label_temp_unit2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Home_label_temp_unit2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_label_temp_unit2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_label_temp_unit2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_label_temp_unit2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_label_temp_unit2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_label_temp_unit2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Home_label_gz
    ui->Home_label_gz = lv_label_create(ui->Home_cont_temp);
    lv_label_set_text(ui->Home_label_gz, "温度");
    lv_label_set_long_mode(ui->Home_label_gz, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Home_label_gz, 108, 80);
    lv_obj_set_size(ui->Home_label_gz, 100, 32);

    //Write style for Home_label_gz, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Home_label_gz, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_label_gz, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_label_gz, lv_color_hex(0xff6500), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_label_gz, &lv_font_SourceHanSerifSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Home_label_gz, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Home_label_gz, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Home_label_gz, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_label_gz, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Home_label_gz, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_label_gz, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_label_gz, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_label_gz, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_label_gz, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_label_gz, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Home_label_temp_unit1
    ui->Home_label_temp_unit1 = lv_label_create(ui->Home_cont_temp);
    lv_label_set_text(ui->Home_label_temp_unit1, "%");
    lv_label_set_long_mode(ui->Home_label_temp_unit1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Home_label_temp_unit1, 58, 227);
    lv_obj_set_size(ui->Home_label_temp_unit1, 40, 29);

    //Write style for Home_label_temp_unit1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Home_label_temp_unit1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_label_temp_unit1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_label_temp_unit1, lv_color_hex(0xa8cb11), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_label_temp_unit1, &lv_font_montserratMedium_25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Home_label_temp_unit1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Home_label_temp_unit1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Home_label_temp_unit1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_label_temp_unit1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Home_label_temp_unit1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_label_temp_unit1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_label_temp_unit1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_label_temp_unit1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_label_temp_unit1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_label_temp_unit1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Home_arc_light
    ui->Home_arc_light = lv_arc_create(ui->Home_cont_temp);
    lv_arc_set_mode(ui->Home_arc_light, LV_ARC_MODE_NORMAL);
    lv_arc_set_range(ui->Home_arc_light, 0, 4000);
    lv_arc_set_bg_angles(ui->Home_arc_light, 0, 360);
    lv_arc_set_value(ui->Home_arc_light, 15);
    lv_arc_set_rotation(ui->Home_arc_light, 90);
    lv_obj_set_pos(ui->Home_arc_light, 13, 280);
    lv_obj_set_size(ui->Home_arc_light, 97, 103);

    //Write style for Home_arc_light, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Home_arc_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Home_arc_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui->Home_arc_light, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->Home_arc_light, 100, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->Home_arc_light, lv_color_hex(0xb2bb00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_arc_light, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_arc_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_arc_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_arc_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_arc_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_arc_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for Home_arc_light, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_arc_width(ui->Home_arc_light, 12, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->Home_arc_light, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->Home_arc_light, lv_color_hex(0xc6f300), LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for Home_arc_light, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Home_arc_light, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Home_arc_light, lv_color_hex(0xd0ff00), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Home_arc_light, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->Home_arc_light, 5, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes Home_label_lux
    ui->Home_label_lux = lv_label_create(ui->Home_cont_temp);
    lv_label_set_text(ui->Home_label_lux, "lux");
    lv_label_set_long_mode(ui->Home_label_lux, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Home_label_lux, 158, 353);
    lv_obj_set_size(ui->Home_label_lux, 52, 23);

    //Write style for Home_label_lux, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Home_label_lux, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_label_lux, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_label_lux, lv_color_hex(0xcfff00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_label_lux, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Home_label_lux, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Home_label_lux, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Home_label_lux, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_label_lux, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Home_label_lux, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_label_lux, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_label_lux, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_label_lux, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_label_lux, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_label_lux, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Home_label_1
    ui->Home_label_1 = lv_label_create(ui->Home_cont_temp);
    lv_label_set_text(ui->Home_label_1, "光照");
    lv_label_set_long_mode(ui->Home_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Home_label_1, 109, 304);
    lv_obj_set_size(ui->Home_label_1, 100, 32);

    //Write style for Home_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Home_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_label_1, lv_color_hex(0xf3ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_label_1, &lv_font_SourceHanSerifSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Home_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Home_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Home_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Home_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Home_label_2
    ui->Home_label_2 = lv_label_create(ui->Home_cont_temp);
    lv_label_set_text(ui->Home_label_2, "湿度");
    lv_label_set_long_mode(ui->Home_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Home_label_2, 10, 194);
    lv_obj_set_size(ui->Home_label_2, 100, 32);

    //Write style for Home_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Home_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_label_2, lv_color_hex(0x00c4ff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_label_2, &lv_font_SourceHanSerifSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Home_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Home_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Home_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Home_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Home_label_home_title
    ui->Home_label_home_title = lv_label_create(ui->Home);
    lv_label_set_text(ui->Home_label_home_title, "MQTT智能监控系统stm32");
    lv_label_set_long_mode(ui->Home_label_home_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Home_label_home_title, 226, 17);
    lv_obj_set_size(ui->Home_label_home_title, 350, 31);

    //Write style for Home_label_home_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Home_label_home_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_label_home_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_label_home_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_label_home_title, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Home_label_home_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Home_label_home_title, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Home_label_home_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_label_home_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Home_label_home_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_label_home_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_label_home_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_label_home_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_label_home_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_label_home_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Home_btn_menu
    ui->Home_btn_menu = lv_btn_create(ui->Home);
    ui->Home_btn_menu_label = lv_label_create(ui->Home_btn_menu);
    lv_label_set_text(ui->Home_btn_menu_label, "" LV_SYMBOL_RIGHT "  ");
    lv_label_set_long_mode(ui->Home_btn_menu_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Home_btn_menu_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Home_btn_menu, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->Home_btn_menu_label, LV_PCT(100));
    lv_obj_set_pos(ui->Home_btn_menu, 0, 196);
    lv_obj_set_size(ui->Home_btn_menu, 45, 84);

    //Write style for Home_btn_menu, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Home_btn_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Home_btn_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_btn_menu, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_btn_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->Home_btn_menu, &_home_bak_45x84, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->Home_btn_menu, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->Home_btn_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_btn_menu, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_btn_menu, &lv_font_montserratMedium_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Home_btn_menu, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_btn_menu, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Home_datetext_date
    ui->Home_datetext_date = lv_label_create(ui->Home);
    lv_label_set_text(ui->Home_datetext_date, "2026/12/18");
    lv_obj_set_style_text_align(ui->Home_datetext_date, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_add_flag(ui->Home_datetext_date, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(ui->Home_datetext_date, Home_datetext_date_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_set_pos(ui->Home_datetext_date, 628, 10);
    lv_obj_set_size(ui->Home_datetext_date, 98, 36);

    //Write style for Home_datetext_date, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->Home_datetext_date, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_datetext_date, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Home_datetext_date, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Home_datetext_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_datetext_date, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Home_datetext_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Home_datetext_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_datetext_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_datetext_date, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_datetext_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_datetext_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_datetext_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Home_digital_clock_time
    static bool Home_digital_clock_time_timer_enabled = false;
    ui->Home_digital_clock_time = lv_dclock_create(ui->Home, "11:25:50");
    if (!Home_digital_clock_time_timer_enabled) {
        lv_timer_create(Home_digital_clock_time_timer, 1000, NULL);
        Home_digital_clock_time_timer_enabled = true;
    }
    lv_obj_set_pos(ui->Home_digital_clock_time, 691, 10);
    lv_obj_set_size(ui->Home_digital_clock_time, 98, 31);

    //Write style for Home_digital_clock_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->Home_digital_clock_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_digital_clock_time, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_digital_clock_time, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Home_digital_clock_time, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Home_digital_clock_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_digital_clock_time, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Home_digital_clock_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_digital_clock_time, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_digital_clock_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_digital_clock_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_digital_clock_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_digital_clock_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Home_img_light
    ui->Home_img_light = lv_img_create(ui->Home);
    lv_obj_add_flag(ui->Home_img_light, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Home_img_light, &_menu_light_alpha_64x61);
    lv_img_set_pivot(ui->Home_img_light, 50,50);
    lv_img_set_angle(ui->Home_img_light, 0);
    lv_obj_set_pos(ui->Home_img_light, 92, 362);
    lv_obj_set_size(ui->Home_img_light, 64, 61);

    //Write style for Home_img_light, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Home_img_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Home_img_light, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_img_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Home_img_light, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Home_label_light_val
    ui->Home_label_light_val = lv_label_create(ui->Home);
    lv_label_set_text(ui->Home_label_light_val, "null");
    lv_label_set_long_mode(ui->Home_label_light_val, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Home_label_light_val, 168, 412);
    lv_obj_set_size(ui->Home_label_light_val, 79, 23);

    //Write style for Home_label_light_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Home_label_light_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_label_light_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_label_light_val, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_label_light_val, &lv_font_SourceHanSerifSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Home_label_light_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Home_label_light_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Home_label_light_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_label_light_val, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Home_label_light_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_label_light_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_label_light_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_label_light_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_label_light_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_label_light_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Home_cont_menu
    ui->Home_cont_menu = lv_obj_create(ui->Home);
    lv_obj_set_pos(ui->Home_cont_menu, 0, 0);
    lv_obj_set_size(ui->Home_cont_menu, 800, 480);
    lv_obj_set_scrollbar_mode(ui->Home_cont_menu, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->Home_cont_menu, LV_OBJ_FLAG_HIDDEN);

    //Write style for Home_cont_menu, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Home_cont_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_cont_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Home_cont_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_cont_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_cont_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_cont_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_cont_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->Home_cont_menu, &_menu_bak_800x480, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->Home_cont_menu, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->Home_cont_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_cont_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Home_img_tick
    ui->Home_img_tick = lv_img_create(ui->Home_cont_menu);
    lv_obj_add_flag(ui->Home_img_tick, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Home_img_tick, &_menu_bal_alpha_320x320);
    lv_img_set_pivot(ui->Home_img_tick, 50,50);
    lv_img_set_angle(ui->Home_img_tick, 0);
    lv_obj_set_pos(ui->Home_img_tick, -159, 80);
    lv_obj_set_size(ui->Home_img_tick, 320, 320);

    //Write style for Home_img_tick, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Home_img_tick, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Home_img_tick, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_img_tick, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Home_img_tick, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Home_label_monitor
    ui->Home_label_monitor = lv_label_create(ui->Home_cont_menu);
    lv_label_set_text(ui->Home_label_monitor, "控制界面");
    lv_label_set_long_mode(ui->Home_label_monitor, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Home_label_monitor, 155, 37);
    lv_obj_set_size(ui->Home_label_monitor, 121, 42);

    //Write style for Home_label_monitor, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Home_label_monitor, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_label_monitor, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_label_monitor, lv_color_hex(0xbbff00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_label_monitor, &lv_font_SourceHanSerifSC_Regular_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Home_label_monitor, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Home_label_monitor, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Home_label_monitor, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_label_monitor, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Home_label_monitor, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_label_monitor, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_label_monitor, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_label_monitor, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_label_monitor, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_label_monitor, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Home_sw_led1
    ui->Home_sw_led1 = lv_switch_create(ui->Home_cont_menu);
    lv_obj_set_pos(ui->Home_sw_led1, 169, 158);
    lv_obj_set_size(ui->Home_sw_led1, 75, 37);

    //Write style for Home_sw_led1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Home_sw_led1, 83, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Home_sw_led1, lv_color_hex(0xe6e2e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Home_sw_led1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Home_sw_led1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_sw_led1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_sw_led1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for Home_sw_led1, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->Home_sw_led1, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->Home_sw_led1, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->Home_sw_led1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->Home_sw_led1, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

    //Write style for Home_sw_led1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Home_sw_led1, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Home_sw_led1, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Home_sw_led1, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Home_sw_led1, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_sw_led1, 10, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes Home_sw_led2
    ui->Home_sw_led2 = lv_switch_create(ui->Home_cont_menu);
    lv_obj_set_pos(ui->Home_sw_led2, 169, 216);
    lv_obj_set_size(ui->Home_sw_led2, 75, 37);

    //Write style for Home_sw_led2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Home_sw_led2, 83, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Home_sw_led2, lv_color_hex(0xe6e2e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Home_sw_led2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Home_sw_led2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_sw_led2, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_sw_led2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for Home_sw_led2, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->Home_sw_led2, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->Home_sw_led2, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->Home_sw_led2, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->Home_sw_led2, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

    //Write style for Home_sw_led2, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Home_sw_led2, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Home_sw_led2, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Home_sw_led2, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Home_sw_led2, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_sw_led2, 10, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes Home_sw_led3
    ui->Home_sw_led3 = lv_switch_create(ui->Home_cont_menu);
    lv_obj_set_pos(ui->Home_sw_led3, 170, 276);
    lv_obj_set_size(ui->Home_sw_led3, 75, 37);

    //Write style for Home_sw_led3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Home_sw_led3, 83, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Home_sw_led3, lv_color_hex(0xe6e2e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Home_sw_led3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Home_sw_led3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_sw_led3, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_sw_led3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for Home_sw_led3, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->Home_sw_led3, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->Home_sw_led3, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->Home_sw_led3, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->Home_sw_led3, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

    //Write style for Home_sw_led3, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Home_sw_led3, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Home_sw_led3, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Home_sw_led3, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Home_sw_led3, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_sw_led3, 10, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes Home_sw_beep
    ui->Home_sw_beep = lv_switch_create(ui->Home_cont_menu);
    lv_obj_set_pos(ui->Home_sw_beep, 169, 104);
    lv_obj_set_size(ui->Home_sw_beep, 75, 37);

    //Write style for Home_sw_beep, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Home_sw_beep, 83, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Home_sw_beep, lv_color_hex(0xe6e2e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Home_sw_beep, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Home_sw_beep, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_sw_beep, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_sw_beep, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for Home_sw_beep, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->Home_sw_beep, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->Home_sw_beep, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->Home_sw_beep, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->Home_sw_beep, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

    //Write style for Home_sw_beep, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Home_sw_beep, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Home_sw_beep, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Home_sw_beep, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Home_sw_beep, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_sw_beep, 10, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes Home_sw_led4
    ui->Home_sw_led4 = lv_switch_create(ui->Home_cont_menu);
    lv_obj_set_pos(ui->Home_sw_led4, 166, 334);
    lv_obj_set_size(ui->Home_sw_led4, 75, 37);

    //Write style for Home_sw_led4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Home_sw_led4, 83, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Home_sw_led4, lv_color_hex(0xe6e2e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Home_sw_led4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Home_sw_led4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_sw_led4, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_sw_led4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for Home_sw_led4, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->Home_sw_led4, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->Home_sw_led4, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->Home_sw_led4, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->Home_sw_led4, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

    //Write style for Home_sw_led4, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Home_sw_led4, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Home_sw_led4, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Home_sw_led4, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Home_sw_led4, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_sw_led4, 10, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes Home_label_3
    ui->Home_label_3 = lv_label_create(ui->Home_cont_menu);
    lv_label_set_text(ui->Home_label_3, "蜂鸣器");
    lv_label_set_long_mode(ui->Home_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Home_label_3, 242, 110);
    lv_obj_set_size(ui->Home_label_3, 100, 32);

    //Write style for Home_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Home_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_label_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_label_3, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Home_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Home_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Home_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Home_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Home_label_4
    ui->Home_label_4 = lv_label_create(ui->Home_cont_menu);
    lv_label_set_text(ui->Home_label_4, "LED1");
    lv_label_set_long_mode(ui->Home_label_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Home_label_4, 246, 165);
    lv_obj_set_size(ui->Home_label_4, 100, 32);

    //Write style for Home_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Home_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_label_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_label_4, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Home_label_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Home_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Home_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_label_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Home_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Home_label_5
    ui->Home_label_5 = lv_label_create(ui->Home_cont_menu);
    lv_label_set_text(ui->Home_label_5, "LED2");
    lv_label_set_long_mode(ui->Home_label_5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Home_label_5, 246, 220);
    lv_obj_set_size(ui->Home_label_5, 100, 32);

    //Write style for Home_label_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Home_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_label_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_label_5, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Home_label_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Home_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Home_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_label_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Home_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Home_label_6
    ui->Home_label_6 = lv_label_create(ui->Home_cont_menu);
    lv_label_set_text(ui->Home_label_6, "LED3");
    lv_label_set_long_mode(ui->Home_label_6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Home_label_6, 245, 279);
    lv_obj_set_size(ui->Home_label_6, 100, 32);

    //Write style for Home_label_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Home_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_label_6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_label_6, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Home_label_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Home_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Home_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_label_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Home_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Home_label_7
    ui->Home_label_7 = lv_label_create(ui->Home_cont_menu);
    lv_label_set_text(ui->Home_label_7, "LED4");
    lv_label_set_long_mode(ui->Home_label_7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Home_label_7, 248, 338);
    lv_obj_set_size(ui->Home_label_7, 100, 22);

    //Write style for Home_label_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Home_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_label_7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_label_7, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Home_label_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Home_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Home_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_label_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Home_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Home_imgbtn_1
    ui->Home_imgbtn_1 = lv_imgbtn_create(ui->Home_cont_menu);
    lv_obj_add_flag(ui->Home_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->Home_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, &_menu_elevator_alpha_95x89, NULL);
    lv_imgbtn_set_src(ui->Home_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, &_menu_icon_bak_alpha_95x89, NULL);
    lv_imgbtn_set_src(ui->Home_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_menu_elevator_alpha_95x89, NULL);
    lv_imgbtn_set_src(ui->Home_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_menu_icon_bak_alpha_95x89, NULL);
    ui->Home_imgbtn_1_label = lv_label_create(ui->Home_imgbtn_1);
    lv_label_set_text(ui->Home_imgbtn_1_label, "");
    lv_label_set_long_mode(ui->Home_imgbtn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Home_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Home_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->Home_imgbtn_1, 14, 196);
    lv_obj_set_size(ui->Home_imgbtn_1, 95, 89);

    //Write style for Home_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->Home_imgbtn_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Home_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Home_imgbtn_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for Home_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->Home_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->Home_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->Home_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->Home_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->Home_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->Home_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for Home_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->Home_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->Home_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->Home_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->Home_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->Home_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->Home_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for Home_imgbtn_1, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->Home_imgbtn_1, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->Home_imgbtn_1, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //The custom code of Home.


    //Update current screen layout.
    lv_obj_update_layout(ui->Home);

    //Init events for screen.
    events_init_Home(ui);
}
