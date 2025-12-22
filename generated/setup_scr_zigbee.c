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



int zigbee_digital_clock_time_min_value = 25;
int zigbee_digital_clock_time_hour_value = 11;
int zigbee_digital_clock_time_sec_value = 50;
void setup_scr_zigbee(lv_ui *ui)
{
    //Write codes zigbee
    ui->zigbee = lv_obj_create(NULL);
    lv_obj_set_size(ui->zigbee, 800, 480);
    lv_obj_set_scrollbar_mode(ui->zigbee, LV_SCROLLBAR_MODE_OFF);

    //Write style for zigbee, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->zigbee, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->zigbee, &_sub_page_bak_800x480, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->zigbee, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->zigbee, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_cont_dev_control
    ui->zigbee_cont_dev_control = lv_obj_create(ui->zigbee);
    lv_obj_set_pos(ui->zigbee_cont_dev_control, 531, 61);
    lv_obj_set_size(ui->zigbee_cont_dev_control, 241, 254);
    lv_obj_set_scrollbar_mode(ui->zigbee_cont_dev_control, LV_SCROLLBAR_MODE_OFF);

    //Write style for zigbee_cont_dev_control, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->zigbee_cont_dev_control, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_cont_dev_control, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_cont_dev_control, 181, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->zigbee_cont_dev_control, lv_color_hex(0x154870), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->zigbee_cont_dev_control, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_cont_dev_control, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->zigbee_cont_dev_control, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_cont_dev_control, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_cont_dev_control, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_cont_dev_control, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_label_23
    ui->zigbee_label_23 = lv_label_create(ui->zigbee_cont_dev_control);
    lv_label_set_text(ui->zigbee_label_23, "设备信息\n");
    lv_label_set_long_mode(ui->zigbee_label_23, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->zigbee_label_23, 0, 1);
    lv_obj_set_size(ui->zigbee_label_23, 238, 32);

    //Write style for zigbee_label_23, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->zigbee_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_label_23, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->zigbee_label_23, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->zigbee_label_23, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->zigbee_label_23, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->zigbee_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->zigbee_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->zigbee_label_23, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_label_23, 59, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->zigbee_label_23, lv_color_hex(0x1e1e1e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->zigbee_label_23, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_label_23, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->zigbee_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_label_23, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_label_23, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_img_7
    ui->zigbee_img_7 = lv_img_create(ui->zigbee_cont_dev_control);
    lv_obj_add_flag(ui->zigbee_img_7, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->zigbee_img_7, &_8b5dcb72c7df5a77d99214e174d2ec0b_alpha_79x76);
    lv_img_set_pivot(ui->zigbee_img_7, 50,50);
    lv_img_set_angle(ui->zigbee_img_7, 0);
    lv_obj_set_pos(ui->zigbee_img_7, 16, 53);
    lv_obj_set_size(ui->zigbee_img_7, 79, 76);

    //Write style for zigbee_img_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->zigbee_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->zigbee_img_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->zigbee_img_7, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_label_31
    ui->zigbee_label_31 = lv_label_create(ui->zigbee_cont_dev_control);
    lv_label_set_text(ui->zigbee_label_31, "数据包序列");
    lv_label_set_long_mode(ui->zigbee_label_31, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->zigbee_label_31, 114, 55);
    lv_obj_set_size(ui->zigbee_label_31, 100, 32);

    //Write style for zigbee_label_31, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->zigbee_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->zigbee_label_31, lv_color_hex(0x098D6B), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->zigbee_label_31, &lv_font_SourceHanSerifSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->zigbee_label_31, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->zigbee_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->zigbee_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->zigbee_label_31, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->zigbee_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_label_31, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_label_32
    ui->zigbee_label_32 = lv_label_create(ui->zigbee_cont_dev_control);
    lv_label_set_text(ui->zigbee_label_32, "0");
    lv_label_set_long_mode(ui->zigbee_label_32, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->zigbee_label_32, 144, 92);
    lv_obj_set_size(ui->zigbee_label_32, 38, 27);

    //Write style for zigbee_label_32, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->zigbee_label_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_label_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->zigbee_label_32, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->zigbee_label_32, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->zigbee_label_32, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->zigbee_label_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->zigbee_label_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->zigbee_label_32, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_label_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_label_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_label_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->zigbee_label_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_label_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_label_32, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_label_33
    ui->zigbee_label_33 = lv_label_create(ui->zigbee_cont_dev_control);
    lv_label_set_text(ui->zigbee_label_33, "MAC地址");
    lv_label_set_long_mode(ui->zigbee_label_33, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->zigbee_label_33, 51, 156);
    lv_obj_set_size(ui->zigbee_label_33, 143, 35);

    //Write style for zigbee_label_33, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->zigbee_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->zigbee_label_33, lv_color_hex(0xBEAF14), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->zigbee_label_33, &lv_font_SourceHanSerifSC_Regular_28, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->zigbee_label_33, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->zigbee_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->zigbee_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->zigbee_label_33, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->zigbee_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_label_33, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_label_temperature_val
    ui->zigbee_label_temperature_val = lv_label_create(ui->zigbee_cont_dev_control);
    lv_label_set_text(ui->zigbee_label_temperature_val, "SIM:UL:AT:ED:DE:V1");
    lv_label_set_long_mode(ui->zigbee_label_temperature_val, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->zigbee_label_temperature_val, 2, 210);
    lv_obj_set_size(ui->zigbee_label_temperature_val, 237, 18);

    //Write style for zigbee_label_temperature_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->zigbee_label_temperature_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_label_temperature_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->zigbee_label_temperature_val, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->zigbee_label_temperature_val, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->zigbee_label_temperature_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->zigbee_label_temperature_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->zigbee_label_temperature_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->zigbee_label_temperature_val, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_label_temperature_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_label_temperature_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_label_temperature_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->zigbee_label_temperature_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_label_temperature_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_label_temperature_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_cont_temp
    ui->zigbee_cont_temp = lv_obj_create(ui->zigbee);
    lv_obj_set_pos(ui->zigbee_cont_temp, 69, 61);
    lv_obj_set_size(ui->zigbee_cont_temp, 447, 395);
    lv_obj_set_scrollbar_mode(ui->zigbee_cont_temp, LV_SCROLLBAR_MODE_OFF);

    //Write style for zigbee_cont_temp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->zigbee_cont_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_cont_temp, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_cont_temp, 181, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->zigbee_cont_temp, lv_color_hex(0x154870), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->zigbee_cont_temp, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_cont_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->zigbee_cont_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_cont_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_cont_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_cont_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_label_22
    ui->zigbee_label_22 = lv_label_create(ui->zigbee_cont_temp);
    lv_label_set_text(ui->zigbee_label_22, "监控消息");
    lv_label_set_long_mode(ui->zigbee_label_22, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->zigbee_label_22, -2, 3);
    lv_obj_set_size(ui->zigbee_label_22, 487, 36);

    //Write style for zigbee_label_22, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->zigbee_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_label_22, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->zigbee_label_22, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->zigbee_label_22, &lv_font_SourceHanSerifSC_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->zigbee_label_22, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->zigbee_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->zigbee_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->zigbee_label_22, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_label_22, 59, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->zigbee_label_22, lv_color_hex(0x1e1e1e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->zigbee_label_22, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_label_22, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->zigbee_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_label_22, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_label_22, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_label_21
    ui->zigbee_label_21 = lv_label_create(ui->zigbee_cont_temp);
    lv_label_set_text(ui->zigbee_label_21, "28");
    lv_label_set_long_mode(ui->zigbee_label_21, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->zigbee_label_21, 125, 121);
    lv_obj_set_size(ui->zigbee_label_21, 37, 21);

    //Write style for zigbee_label_21, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->zigbee_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->zigbee_label_21, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->zigbee_label_21, &lv_font_montserratMedium_25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->zigbee_label_21, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->zigbee_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->zigbee_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->zigbee_label_21, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->zigbee_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_label_21, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_label_humidity_val
    ui->zigbee_label_humidity_val = lv_label_create(ui->zigbee_cont_temp);
    lv_label_set_text(ui->zigbee_label_humidity_val, "50");
    lv_label_set_long_mode(ui->zigbee_label_humidity_val, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->zigbee_label_humidity_val, 26, 227);
    lv_obj_set_size(ui->zigbee_label_humidity_val, 38, 24);

    //Write style for zigbee_label_humidity_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->zigbee_label_humidity_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_label_humidity_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->zigbee_label_humidity_val, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->zigbee_label_humidity_val, &lv_font_montserratMedium_25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->zigbee_label_humidity_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->zigbee_label_humidity_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->zigbee_label_humidity_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->zigbee_label_humidity_val, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_label_humidity_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_label_humidity_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_label_humidity_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->zigbee_label_humidity_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_label_humidity_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_label_humidity_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_label_19
    ui->zigbee_label_19 = lv_label_create(ui->zigbee_cont_temp);
    lv_label_set_text(ui->zigbee_label_19, "℃");
    lv_label_set_long_mode(ui->zigbee_label_19, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->zigbee_label_19, 162, 119);
    lv_obj_set_size(ui->zigbee_label_19, 28, 29);

    //Write style for zigbee_label_19, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->zigbee_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->zigbee_label_19, lv_color_hex(0xdbff54), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->zigbee_label_19, &lv_font_SourceHanSerifSC_Regular_25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->zigbee_label_19, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->zigbee_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->zigbee_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->zigbee_label_19, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->zigbee_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_label_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_label_18
    ui->zigbee_label_18 = lv_label_create(ui->zigbee_cont_temp);
    lv_label_set_text(ui->zigbee_label_18, "温度");
    lv_label_set_long_mode(ui->zigbee_label_18, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->zigbee_label_18, 108, 80);
    lv_obj_set_size(ui->zigbee_label_18, 100, 32);

    //Write style for zigbee_label_18, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->zigbee_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->zigbee_label_18, lv_color_hex(0xff6500), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->zigbee_label_18, &lv_font_SourceHanSerifSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->zigbee_label_18, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->zigbee_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->zigbee_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->zigbee_label_18, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->zigbee_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_label_18, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_label_17
    ui->zigbee_label_17 = lv_label_create(ui->zigbee_cont_temp);
    lv_label_set_text(ui->zigbee_label_17, "%");
    lv_label_set_long_mode(ui->zigbee_label_17, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->zigbee_label_17, 58, 227);
    lv_obj_set_size(ui->zigbee_label_17, 40, 29);

    //Write style for zigbee_label_17, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->zigbee_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->zigbee_label_17, lv_color_hex(0xa8cb11), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->zigbee_label_17, &lv_font_montserratMedium_25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->zigbee_label_17, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->zigbee_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->zigbee_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->zigbee_label_17, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->zigbee_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_label_17, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_label_16
    ui->zigbee_label_16 = lv_label_create(ui->zigbee_cont_temp);
    lv_label_set_text(ui->zigbee_label_16, "lux");
    lv_label_set_long_mode(ui->zigbee_label_16, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->zigbee_label_16, 158, 353);
    lv_obj_set_size(ui->zigbee_label_16, 52, 23);

    //Write style for zigbee_label_16, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->zigbee_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->zigbee_label_16, lv_color_hex(0xcfff00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->zigbee_label_16, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->zigbee_label_16, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->zigbee_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->zigbee_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->zigbee_label_16, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->zigbee_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_label_16, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_label_15
    ui->zigbee_label_15 = lv_label_create(ui->zigbee_cont_temp);
    lv_label_set_text(ui->zigbee_label_15, "光照");
    lv_label_set_long_mode(ui->zigbee_label_15, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->zigbee_label_15, 109, 304);
    lv_obj_set_size(ui->zigbee_label_15, 100, 32);

    //Write style for zigbee_label_15, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->zigbee_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->zigbee_label_15, lv_color_hex(0xf3ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->zigbee_label_15, &lv_font_SourceHanSerifSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->zigbee_label_15, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->zigbee_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->zigbee_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->zigbee_label_15, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->zigbee_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_label_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_label_14
    ui->zigbee_label_14 = lv_label_create(ui->zigbee_cont_temp);
    lv_label_set_text(ui->zigbee_label_14, "湿度");
    lv_label_set_long_mode(ui->zigbee_label_14, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->zigbee_label_14, 10, 194);
    lv_obj_set_size(ui->zigbee_label_14, 100, 32);

    //Write style for zigbee_label_14, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->zigbee_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->zigbee_label_14, lv_color_hex(0x00c4ff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->zigbee_label_14, &lv_font_SourceHanSerifSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->zigbee_label_14, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->zigbee_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->zigbee_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->zigbee_label_14, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->zigbee_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_label_14, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_img_4
    ui->zigbee_img_4 = lv_img_create(ui->zigbee_cont_temp);
    lv_obj_add_flag(ui->zigbee_img_4, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->zigbee_img_4, &_dew_alpha_79x76);
    lv_img_set_pivot(ui->zigbee_img_4, 50,50);
    lv_img_set_angle(ui->zigbee_img_4, 0);
    lv_obj_set_pos(ui->zigbee_img_4, 232, 66);
    lv_obj_set_size(ui->zigbee_img_4, 79, 76);

    //Write style for zigbee_img_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->zigbee_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->zigbee_img_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->zigbee_img_4, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_label_24
    ui->zigbee_label_24 = lv_label_create(ui->zigbee_cont_temp);
    lv_label_set_text(ui->zigbee_label_24, "露点");
    lv_label_set_long_mode(ui->zigbee_label_24, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->zigbee_label_24, 312, 69);
    lv_obj_set_size(ui->zigbee_label_24, 100, 32);

    //Write style for zigbee_label_24, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->zigbee_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->zigbee_label_24, lv_color_hex(0x20b12d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->zigbee_label_24, &lv_font_SourceHanSerifSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->zigbee_label_24, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->zigbee_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->zigbee_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->zigbee_label_24, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->zigbee_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_label_24, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_label_dew_point_val
    ui->zigbee_label_dew_point_val = lv_label_create(ui->zigbee_cont_temp);
    lv_label_set_text(ui->zigbee_label_dew_point_val, "28");
    lv_label_set_long_mode(ui->zigbee_label_dew_point_val, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->zigbee_label_dew_point_val, 336, 117);
    lv_obj_set_size(ui->zigbee_label_dew_point_val, 37, 21);

    //Write style for zigbee_label_dew_point_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->zigbee_label_dew_point_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_label_dew_point_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->zigbee_label_dew_point_val, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->zigbee_label_dew_point_val, &lv_font_montserratMedium_25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->zigbee_label_dew_point_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->zigbee_label_dew_point_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->zigbee_label_dew_point_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->zigbee_label_dew_point_val, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_label_dew_point_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_label_dew_point_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_label_dew_point_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->zigbee_label_dew_point_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_label_dew_point_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_label_dew_point_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_label_26
    ui->zigbee_label_26 = lv_label_create(ui->zigbee_cont_temp);
    lv_label_set_text(ui->zigbee_label_26, "℃");
    lv_label_set_long_mode(ui->zigbee_label_26, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->zigbee_label_26, 370, 113);
    lv_obj_set_size(ui->zigbee_label_26, 28, 29);

    //Write style for zigbee_label_26, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->zigbee_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->zigbee_label_26, lv_color_hex(0xdbff54), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->zigbee_label_26, &lv_font_SourceHanSerifSC_Regular_25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->zigbee_label_26, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->zigbee_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->zigbee_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->zigbee_label_26, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->zigbee_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_label_26, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_img_5
    ui->zigbee_img_5 = lv_img_create(ui->zigbee_cont_temp);
    lv_obj_add_flag(ui->zigbee_img_5, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->zigbee_img_5, &_human_alpha_77x80);
    lv_img_set_pivot(ui->zigbee_img_5, 50,50);
    lv_img_set_angle(ui->zigbee_img_5, 0);
    lv_obj_set_pos(ui->zigbee_img_5, 239, 293);
    lv_obj_set_size(ui->zigbee_img_5, 77, 80);

    //Write style for zigbee_img_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->zigbee_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->zigbee_img_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->zigbee_img_5, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_img_6
    ui->zigbee_img_6 = lv_img_create(ui->zigbee_cont_temp);
    lv_obj_add_flag(ui->zigbee_img_6, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->zigbee_img_6, &_6a12a02693d60ca0cd70491351de2d54_alpha_79x82);
    lv_img_set_pivot(ui->zigbee_img_6, 50,50);
    lv_img_set_angle(ui->zigbee_img_6, 0);
    lv_obj_set_pos(ui->zigbee_img_6, 334, 177);
    lv_obj_set_size(ui->zigbee_img_6, 79, 82);

    //Write style for zigbee_img_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->zigbee_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->zigbee_img_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->zigbee_img_6, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_label_27
    ui->zigbee_label_27 = lv_label_create(ui->zigbee_cont_temp);
    lv_label_set_text(ui->zigbee_label_27, "振动检测");
    lv_label_set_long_mode(ui->zigbee_label_27, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->zigbee_label_27, 333, 297);
    lv_obj_set_size(ui->zigbee_label_27, 100, 32);

    //Write style for zigbee_label_27, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->zigbee_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->zigbee_label_27, lv_color_hex(0xD01FBB), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->zigbee_label_27, &lv_font_SourceHanSerifSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->zigbee_label_27, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->zigbee_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->zigbee_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->zigbee_label_27, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->zigbee_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_label_27, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_label_human_detected_val
    ui->zigbee_label_human_detected_val = lv_label_create(ui->zigbee_cont_temp);
    lv_label_set_text(ui->zigbee_label_human_detected_val, "无人");
    lv_label_set_long_mode(ui->zigbee_label_human_detected_val, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->zigbee_label_human_detected_val, 251, 223);
    lv_obj_set_size(ui->zigbee_label_human_detected_val, 56, 24);

    //Write style for zigbee_label_human_detected_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->zigbee_label_human_detected_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_label_human_detected_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->zigbee_label_human_detected_val, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->zigbee_label_human_detected_val, &lv_font_SourceHanSerifSC_Regular_25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->zigbee_label_human_detected_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->zigbee_label_human_detected_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->zigbee_label_human_detected_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->zigbee_label_human_detected_val, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_label_human_detected_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_label_human_detected_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_label_human_detected_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->zigbee_label_human_detected_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_label_human_detected_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_label_human_detected_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_label_29
    ui->zigbee_label_29 = lv_label_create(ui->zigbee_cont_temp);
    lv_label_set_text(ui->zigbee_label_29, "人体检测");
    lv_label_set_long_mode(ui->zigbee_label_29, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->zigbee_label_29, 228, 190);
    lv_obj_set_size(ui->zigbee_label_29, 100, 32);

    //Write style for zigbee_label_29, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->zigbee_label_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_label_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->zigbee_label_29, lv_color_hex(0x00cbff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->zigbee_label_29, &lv_font_SourceHanSerifSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->zigbee_label_29, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->zigbee_label_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->zigbee_label_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->zigbee_label_29, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_label_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_label_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_label_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->zigbee_label_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_label_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_label_29, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_label_vibration_val
    ui->zigbee_label_vibration_val = lv_label_create(ui->zigbee_cont_temp);
    lv_label_set_text(ui->zigbee_label_vibration_val, "无振动");
    lv_label_set_long_mode(ui->zigbee_label_vibration_val, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->zigbee_label_vibration_val, 336, 334);
    lv_obj_set_size(ui->zigbee_label_vibration_val, 90, 30);

    //Write style for zigbee_label_vibration_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->zigbee_label_vibration_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_label_vibration_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->zigbee_label_vibration_val, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->zigbee_label_vibration_val, &lv_font_SourceHanSerifSC_Regular_25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->zigbee_label_vibration_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->zigbee_label_vibration_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->zigbee_label_vibration_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->zigbee_label_vibration_val, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_label_vibration_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_label_vibration_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_label_vibration_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->zigbee_label_vibration_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_label_vibration_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_label_vibration_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_img_8
    ui->zigbee_img_8 = lv_img_create(ui->zigbee_cont_temp);
    lv_obj_add_flag(ui->zigbee_img_8, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->zigbee_img_8, &_ddf538df72b089004cf457c6bcde0026_alpha_79x76);
    lv_img_set_pivot(ui->zigbee_img_8, 50,50);
    lv_img_set_angle(ui->zigbee_img_8, 0);
    lv_obj_set_pos(ui->zigbee_img_8, 125, 189);
    lv_obj_set_size(ui->zigbee_img_8, 79, 76);

    //Write style for zigbee_img_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->zigbee_img_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->zigbee_img_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_img_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->zigbee_img_8, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_img_9
    ui->zigbee_img_9 = lv_img_create(ui->zigbee_cont_temp);
    lv_obj_add_flag(ui->zigbee_img_9, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->zigbee_img_9, &_272e830a3df8262600a6efa6550e374d_alpha_79x76);
    lv_img_set_pivot(ui->zigbee_img_9, 50,50);
    lv_img_set_angle(ui->zigbee_img_9, 0);
    lv_obj_set_pos(ui->zigbee_img_9, 26, 80);
    lv_obj_set_size(ui->zigbee_img_9, 79, 76);

    //Write style for zigbee_img_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->zigbee_img_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->zigbee_img_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_img_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->zigbee_img_9, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_img_10
    ui->zigbee_img_10 = lv_img_create(ui->zigbee_cont_temp);
    lv_obj_add_flag(ui->zigbee_img_10, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->zigbee_img_10, &_15ddc8832c1a305680d536dddc738589_alpha_79x76);
    lv_img_set_pivot(ui->zigbee_img_10, 50,50);
    lv_img_set_angle(ui->zigbee_img_10, 0);
    lv_obj_set_pos(ui->zigbee_img_10, 22, 292);
    lv_obj_set_size(ui->zigbee_img_10, 79, 76);

    //Write style for zigbee_img_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->zigbee_img_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->zigbee_img_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_img_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->zigbee_img_10, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_label_home_title
    ui->zigbee_label_home_title = lv_label_create(ui->zigbee);
    lv_label_set_text(ui->zigbee_label_home_title, "MQTT智能监控系统zigbee");
    lv_label_set_long_mode(ui->zigbee_label_home_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->zigbee_label_home_title, 226, 17);
    lv_obj_set_size(ui->zigbee_label_home_title, 350, 31);

    //Write style for zigbee_label_home_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->zigbee_label_home_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_label_home_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->zigbee_label_home_title, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->zigbee_label_home_title, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->zigbee_label_home_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->zigbee_label_home_title, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->zigbee_label_home_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->zigbee_label_home_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_label_home_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_label_home_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_label_home_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->zigbee_label_home_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_label_home_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_label_home_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_btn_menu
    ui->zigbee_btn_menu = lv_btn_create(ui->zigbee);
    ui->zigbee_btn_menu_label = lv_label_create(ui->zigbee_btn_menu);
    lv_label_set_text(ui->zigbee_btn_menu_label, "" LV_SYMBOL_RIGHT "  ");
    lv_label_set_long_mode(ui->zigbee_btn_menu_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->zigbee_btn_menu_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->zigbee_btn_menu, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->zigbee_btn_menu_label, LV_PCT(100));
    lv_obj_set_pos(ui->zigbee_btn_menu, 0, 196);
    lv_obj_set_size(ui->zigbee_btn_menu, 45, 84);

    //Write style for zigbee_btn_menu, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->zigbee_btn_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->zigbee_btn_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_btn_menu, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_btn_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->zigbee_btn_menu, &_home_bak_45x84, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->zigbee_btn_menu, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->zigbee_btn_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->zigbee_btn_menu, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->zigbee_btn_menu, &lv_font_montserratMedium_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->zigbee_btn_menu, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->zigbee_btn_menu, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_datetext_date
    ui->zigbee_datetext_date = lv_label_create(ui->zigbee);
    lv_label_set_text(ui->zigbee_datetext_date, "2026/12/18");
    lv_obj_set_style_text_align(ui->zigbee_datetext_date, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_add_flag(ui->zigbee_datetext_date, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(ui->zigbee_datetext_date, zigbee_datetext_date_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_set_pos(ui->zigbee_datetext_date, 628, 10);
    lv_obj_set_size(ui->zigbee_datetext_date, 98, 36);

    //Write style for zigbee_datetext_date, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->zigbee_datetext_date, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->zigbee_datetext_date, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->zigbee_datetext_date, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->zigbee_datetext_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->zigbee_datetext_date, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_datetext_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->zigbee_datetext_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_datetext_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_datetext_date, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_datetext_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_datetext_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_datetext_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_digital_clock_time
    static bool zigbee_digital_clock_time_timer_enabled = false;
    ui->zigbee_digital_clock_time = lv_dclock_create(ui->zigbee, "11:25:50");
    if (!zigbee_digital_clock_time_timer_enabled) {
        lv_timer_create(zigbee_digital_clock_time_timer, 1000, NULL);
        zigbee_digital_clock_time_timer_enabled = true;
    }
    lv_obj_set_pos(ui->zigbee_digital_clock_time, 691, 10);
    lv_obj_set_size(ui->zigbee_digital_clock_time, 98, 31);

    //Write style for zigbee_digital_clock_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->zigbee_digital_clock_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->zigbee_digital_clock_time, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->zigbee_digital_clock_time, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->zigbee_digital_clock_time, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->zigbee_digital_clock_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->zigbee_digital_clock_time, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_digital_clock_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_digital_clock_time, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_digital_clock_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->zigbee_digital_clock_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_digital_clock_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_digital_clock_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_label_illumination_val
    ui->zigbee_label_illumination_val = lv_label_create(ui->zigbee);
    lv_label_set_text(ui->zigbee_label_illumination_val, "1000");
    lv_label_set_long_mode(ui->zigbee_label_illumination_val, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->zigbee_label_illumination_val, 171, 411);
    lv_obj_set_size(ui->zigbee_label_illumination_val, 79, 23);

    //Write style for zigbee_label_illumination_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->zigbee_label_illumination_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_label_illumination_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->zigbee_label_illumination_val, lv_color_hex(0xFFFFFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->zigbee_label_illumination_val, &lv_font_SourceHanSerifSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->zigbee_label_illumination_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->zigbee_label_illumination_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->zigbee_label_illumination_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->zigbee_label_illumination_val, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_label_illumination_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_label_illumination_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_label_illumination_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->zigbee_label_illumination_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_label_illumination_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_label_illumination_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_cont_menu
    ui->zigbee_cont_menu = lv_obj_create(ui->zigbee);
    lv_obj_set_pos(ui->zigbee_cont_menu, 0, 0);
    lv_obj_set_size(ui->zigbee_cont_menu, 800, 480);
    lv_obj_set_scrollbar_mode(ui->zigbee_cont_menu, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->zigbee_cont_menu, LV_OBJ_FLAG_HIDDEN);

    //Write style for zigbee_cont_menu, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->zigbee_cont_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_cont_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_cont_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_cont_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->zigbee_cont_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_cont_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_cont_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->zigbee_cont_menu, &_menu_bak_800x480, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->zigbee_cont_menu, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->zigbee_cont_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_cont_menu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_img_1
    ui->zigbee_img_1 = lv_img_create(ui->zigbee_cont_menu);
    lv_obj_add_flag(ui->zigbee_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->zigbee_img_1, &_menu_bal_alpha_320x320);
    lv_img_set_pivot(ui->zigbee_img_1, 50,50);
    lv_img_set_angle(ui->zigbee_img_1, 0);
    lv_obj_set_pos(ui->zigbee_img_1, -159, 80);
    lv_obj_set_size(ui->zigbee_img_1, 320, 320);

    //Write style for zigbee_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->zigbee_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->zigbee_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->zigbee_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_label_13
    ui->zigbee_label_13 = lv_label_create(ui->zigbee_cont_menu);
    lv_label_set_text(ui->zigbee_label_13, "控制界面");
    lv_label_set_long_mode(ui->zigbee_label_13, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->zigbee_label_13, 155, 37);
    lv_obj_set_size(ui->zigbee_label_13, 121, 42);

    //Write style for zigbee_label_13, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->zigbee_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->zigbee_label_13, lv_color_hex(0xbbff00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->zigbee_label_13, &lv_font_SourceHanSerifSC_Regular_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->zigbee_label_13, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->zigbee_label_13, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->zigbee_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->zigbee_label_13, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->zigbee_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_label_13, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_sw_5
    ui->zigbee_sw_5 = lv_switch_create(ui->zigbee_cont_menu);
    lv_obj_set_pos(ui->zigbee_sw_5, 169, 158);
    lv_obj_set_size(ui->zigbee_sw_5, 75, 37);

    //Write style for zigbee_sw_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->zigbee_sw_5, 83, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->zigbee_sw_5, lv_color_hex(0xe6e2e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->zigbee_sw_5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->zigbee_sw_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_sw_5, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_sw_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for zigbee_sw_5, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->zigbee_sw_5, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->zigbee_sw_5, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->zigbee_sw_5, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->zigbee_sw_5, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

    //Write style for zigbee_sw_5, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->zigbee_sw_5, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->zigbee_sw_5, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->zigbee_sw_5, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->zigbee_sw_5, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_sw_5, 10, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes zigbee_sw_4
    ui->zigbee_sw_4 = lv_switch_create(ui->zigbee_cont_menu);
    lv_obj_set_pos(ui->zigbee_sw_4, 169, 216);
    lv_obj_set_size(ui->zigbee_sw_4, 75, 37);

    //Write style for zigbee_sw_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->zigbee_sw_4, 83, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->zigbee_sw_4, lv_color_hex(0xe6e2e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->zigbee_sw_4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->zigbee_sw_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_sw_4, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_sw_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for zigbee_sw_4, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->zigbee_sw_4, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->zigbee_sw_4, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->zigbee_sw_4, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->zigbee_sw_4, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

    //Write style for zigbee_sw_4, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->zigbee_sw_4, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->zigbee_sw_4, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->zigbee_sw_4, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->zigbee_sw_4, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_sw_4, 10, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes zigbee_sw_3
    ui->zigbee_sw_3 = lv_switch_create(ui->zigbee_cont_menu);
    lv_obj_set_pos(ui->zigbee_sw_3, 170, 276);
    lv_obj_set_size(ui->zigbee_sw_3, 75, 37);

    //Write style for zigbee_sw_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->zigbee_sw_3, 83, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->zigbee_sw_3, lv_color_hex(0xe6e2e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->zigbee_sw_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->zigbee_sw_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_sw_3, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_sw_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for zigbee_sw_3, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->zigbee_sw_3, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->zigbee_sw_3, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->zigbee_sw_3, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->zigbee_sw_3, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

    //Write style for zigbee_sw_3, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->zigbee_sw_3, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->zigbee_sw_3, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->zigbee_sw_3, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->zigbee_sw_3, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_sw_3, 10, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes zigbee_sw_2
    ui->zigbee_sw_2 = lv_switch_create(ui->zigbee_cont_menu);
    lv_obj_set_pos(ui->zigbee_sw_2, 169, 104);
    lv_obj_set_size(ui->zigbee_sw_2, 75, 37);

    //Write style for zigbee_sw_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->zigbee_sw_2, 83, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->zigbee_sw_2, lv_color_hex(0xe6e2e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->zigbee_sw_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->zigbee_sw_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_sw_2, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_sw_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for zigbee_sw_2, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->zigbee_sw_2, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->zigbee_sw_2, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->zigbee_sw_2, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->zigbee_sw_2, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

    //Write style for zigbee_sw_2, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->zigbee_sw_2, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->zigbee_sw_2, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->zigbee_sw_2, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->zigbee_sw_2, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_sw_2, 10, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes zigbee_sw_1
    ui->zigbee_sw_1 = lv_switch_create(ui->zigbee_cont_menu);
    lv_obj_set_pos(ui->zigbee_sw_1, 166, 334);
    lv_obj_set_size(ui->zigbee_sw_1, 75, 37);

    //Write style for zigbee_sw_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->zigbee_sw_1, 83, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->zigbee_sw_1, lv_color_hex(0xe6e2e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->zigbee_sw_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->zigbee_sw_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_sw_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_sw_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for zigbee_sw_1, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->zigbee_sw_1, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->zigbee_sw_1, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->zigbee_sw_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->zigbee_sw_1, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

    //Write style for zigbee_sw_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->zigbee_sw_1, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->zigbee_sw_1, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->zigbee_sw_1, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->zigbee_sw_1, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_sw_1, 10, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes zigbee_label_12
    ui->zigbee_label_12 = lv_label_create(ui->zigbee_cont_menu);
    lv_label_set_text(ui->zigbee_label_12, "蜂鸣器");
    lv_label_set_long_mode(ui->zigbee_label_12, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->zigbee_label_12, 242, 110);
    lv_obj_set_size(ui->zigbee_label_12, 100, 32);

    //Write style for zigbee_label_12, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->zigbee_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->zigbee_label_12, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->zigbee_label_12, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->zigbee_label_12, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->zigbee_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->zigbee_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->zigbee_label_12, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->zigbee_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_label_12, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_label_11
    ui->zigbee_label_11 = lv_label_create(ui->zigbee_cont_menu);
    lv_label_set_text(ui->zigbee_label_11, "LED1");
    lv_label_set_long_mode(ui->zigbee_label_11, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->zigbee_label_11, 246, 165);
    lv_obj_set_size(ui->zigbee_label_11, 100, 32);

    //Write style for zigbee_label_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->zigbee_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->zigbee_label_11, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->zigbee_label_11, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->zigbee_label_11, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->zigbee_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->zigbee_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->zigbee_label_11, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->zigbee_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_label_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_label_10
    ui->zigbee_label_10 = lv_label_create(ui->zigbee_cont_menu);
    lv_label_set_text(ui->zigbee_label_10, "LED2");
    lv_label_set_long_mode(ui->zigbee_label_10, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->zigbee_label_10, 246, 220);
    lv_obj_set_size(ui->zigbee_label_10, 100, 32);

    //Write style for zigbee_label_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->zigbee_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->zigbee_label_10, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->zigbee_label_10, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->zigbee_label_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->zigbee_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->zigbee_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->zigbee_label_10, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->zigbee_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_label_9
    ui->zigbee_label_9 = lv_label_create(ui->zigbee_cont_menu);
    lv_label_set_text(ui->zigbee_label_9, "LED3");
    lv_label_set_long_mode(ui->zigbee_label_9, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->zigbee_label_9, 245, 279);
    lv_obj_set_size(ui->zigbee_label_9, 100, 32);

    //Write style for zigbee_label_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->zigbee_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->zigbee_label_9, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->zigbee_label_9, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->zigbee_label_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->zigbee_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->zigbee_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->zigbee_label_9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->zigbee_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_label_8
    ui->zigbee_label_8 = lv_label_create(ui->zigbee_cont_menu);
    lv_label_set_text(ui->zigbee_label_8, "LED4");
    lv_label_set_long_mode(ui->zigbee_label_8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->zigbee_label_8, 248, 338);
    lv_obj_set_size(ui->zigbee_label_8, 100, 22);

    //Write style for zigbee_label_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->zigbee_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->zigbee_label_8, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->zigbee_label_8, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->zigbee_label_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->zigbee_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->zigbee_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->zigbee_label_8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->zigbee_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->zigbee_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->zigbee_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->zigbee_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->zigbee_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes zigbee_imgbtn_2
    ui->zigbee_imgbtn_2 = lv_imgbtn_create(ui->zigbee_cont_menu);
    lv_obj_add_flag(ui->zigbee_imgbtn_2, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->zigbee_imgbtn_2, LV_IMGBTN_STATE_RELEASED, NULL, &_menu_elevator_alpha_95x89, NULL);
    lv_imgbtn_set_src(ui->zigbee_imgbtn_2, LV_IMGBTN_STATE_PRESSED, NULL, &_menu_icon_bak_alpha_95x89, NULL);
    lv_imgbtn_set_src(ui->zigbee_imgbtn_2, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_menu_elevator_alpha_95x89, NULL);
    lv_imgbtn_set_src(ui->zigbee_imgbtn_2, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_menu_icon_bak_alpha_95x89, NULL);
    ui->zigbee_imgbtn_2_label = lv_label_create(ui->zigbee_imgbtn_2);
    lv_label_set_text(ui->zigbee_imgbtn_2_label, "");
    lv_label_set_long_mode(ui->zigbee_imgbtn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->zigbee_imgbtn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->zigbee_imgbtn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->zigbee_imgbtn_2, 14, 196);
    lv_obj_set_size(ui->zigbee_imgbtn_2, 95, 89);

    //Write style for zigbee_imgbtn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->zigbee_imgbtn_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->zigbee_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->zigbee_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->zigbee_imgbtn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->zigbee_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->zigbee_imgbtn_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->zigbee_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for zigbee_imgbtn_2, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->zigbee_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->zigbee_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->zigbee_imgbtn_2, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->zigbee_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->zigbee_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->zigbee_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for zigbee_imgbtn_2, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->zigbee_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->zigbee_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->zigbee_imgbtn_2, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->zigbee_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->zigbee_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->zigbee_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for zigbee_imgbtn_2, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->zigbee_imgbtn_2, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->zigbee_imgbtn_2, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //The custom code of zigbee.


    //Update current screen layout.
    lv_obj_update_layout(ui->zigbee);

    //Init events for screen.
    events_init_zigbee(ui);
}
