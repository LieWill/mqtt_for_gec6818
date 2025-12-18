/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *Home;
	bool Home_del;
	lv_obj_t *Home_cont_dev_control;
	lv_obj_t *Home_label_dev;
	lv_obj_t *Home_cont_temp;
	lv_obj_t *Home_label_temp_tit;
	lv_obj_t *Home_arc_temp;
	lv_obj_t *Home_arc_humi;
	lv_obj_t *Home_label_temp_val;
	lv_obj_t *Home_label_wet_val;
	lv_obj_t *Home_img_temp;
	lv_obj_t *Home_img_humidity;
	lv_obj_t *Home_label_temp_unit2;
	lv_obj_t *Home_label_temp_unit1;
	lv_obj_t *Home_arc_light;
	lv_obj_t *Home_cont_electricity;
	lv_obj_t *Home_label_ele_monitor_title;
	lv_obj_t *Home_label_home_title;
	lv_obj_t *Home_btn_menu;
	lv_obj_t *Home_btn_menu_label;
	lv_obj_t *Home_sw_1;
	lv_obj_t *Home_datetext_date;
	lv_obj_t *Home_digital_clock_time;
	lv_obj_t *Home_chart_temp;
	lv_chart_series_t *Home_chart_temp_0;
	lv_chart_series_t *Home_chart_temp_1;
	lv_chart_series_t *Home_chart_temp_2;
	lv_obj_t *Home_sw_2;
	lv_obj_t *Home_sw_3;
	lv_obj_t *Home_sw_4;
	lv_obj_t *Home_label_temp;
	lv_obj_t *Home_cont_menu;
	lv_obj_t *Home_img_tick;
	lv_obj_t *Home_btn_phone;
	lv_obj_t *Home_btn_phone_label;
	lv_obj_t *Home_btn_warning;
	lv_obj_t *Home_btn_warning_label;
	lv_obj_t *Home_btn_power;
	lv_obj_t *Home_btn_power_label;
	lv_obj_t *Home_btn_temp;
	lv_obj_t *Home_btn_temp_label;
	lv_obj_t *Home_btn_link;
	lv_obj_t *Home_btn_link_label;
	lv_obj_t *Home_btn_safe;
	lv_obj_t *Home_btn_safe_label;
	lv_obj_t *Home_btn_light;
	lv_obj_t *Home_btn_light_label;
	lv_obj_t *Home_label_monitor;
	lv_obj_t *Home_img_light;
	lv_obj_t *Home_label_light_val;
	lv_obj_t *Home_label_22;
	lv_obj_t *Home_label_23;
	lv_obj_t *Home_label_humi;
	lv_obj_t *Home_label_light;
	lv_obj_t *Home_line_1;
	lv_obj_t *Home_line_2;
	lv_obj_t *Home_line_3;
	lv_obj_t *Electricity;
	bool Electricity_del;
	lv_obj_t *Electricity_btn_home;
	lv_obj_t *Electricity_btn_home_label;
	lv_obj_t *Electricity_label_tit;
	lv_obj_t *Electricity_cont_1;
	lv_obj_t *Electricity_label_1_value;
	lv_obj_t *Electricity_label_1_NO;
	lv_obj_t *Electricity_cont_2;
	lv_obj_t *Electricity_label_2_value;
	lv_obj_t *Electricity_label_2_NO;
	lv_obj_t *Electricity_cont_3;
	lv_obj_t *Electricity_label_3_value;
	lv_obj_t *Electricity_label_3_NO;
	lv_obj_t *Electricity_cont_4;
	lv_obj_t *Electricity_label_4_value;
	lv_obj_t *Electricity_label_4_NO;
	lv_obj_t *Electricity_cont_5;
	lv_obj_t *Electricity_label_5_value;
	lv_obj_t *Electricity_label_5_NO;
	lv_obj_t *Electricity_digital_clock_time;
	lv_obj_t *Electricity_datetext_date;
	lv_obj_t *Electricity_cont_info_box;
	lv_obj_t *Electricity_cont_info;
	lv_obj_t *Electricity_label_23;
	lv_obj_t *Electricity_cont_conditioner;
	lv_obj_t *Electricity_label_cond_title;
	lv_obj_t *Electricity_arc_cond;
	lv_obj_t *Electricity_label_cond_NO;
	lv_obj_t *Electricity_label_cond_num;
	lv_obj_t *Electricity_img_cond;
	lv_obj_t *Electricity_label_cond_unit;
	lv_obj_t *Electricity_label_cond_proportion;
	lv_obj_t *Electricity_label_cond_pro_num;
	lv_obj_t *Electricity_label_cond_power;
	lv_obj_t *Electricity_label_cond_power_num;
	lv_obj_t *Electricity_cont_light;
	lv_obj_t *Electricity_label_light_title;
	lv_obj_t *Electricity_arc_light;
	lv_obj_t *Electricity_label_light_NO;
	lv_obj_t *Electricity_label_light_num;
	lv_obj_t *Electricity_img_light;
	lv_obj_t *Electricity_label_light_unit;
	lv_obj_t *Electricity_label_light_proportion;
	lv_obj_t *Electricity_label_light_pro_num;
	lv_obj_t *Electricity_label_light_power;
	lv_obj_t *Electricity_label_light_power_num;
	lv_obj_t *Electricity_cont_elevator;
	lv_obj_t *Electricity_label_elevator_title;
	lv_obj_t *Electricity_arc_elevator;
	lv_obj_t *Electricity_label_elevator_NO;
	lv_obj_t *Electricity_label_elevator_num;
	lv_obj_t *Electricity_img_elevator;
	lv_obj_t *Electricity_label_elevator_unit;
	lv_obj_t *Electricity_label_elevator_proportion;
	lv_obj_t *Electricity_label_elevator_pro_num;
	lv_obj_t *Electricity_label_elevator_power;
	lv_obj_t *Electricity_label_elevator_power_num;
	lv_obj_t *Firefighting;
	bool Firefighting_del;
	lv_obj_t *Firefighting_cont_smoke;
	lv_obj_t *Firefighting_label_smoke_tit;
	lv_obj_t *Firefighting_label_status;
	lv_obj_t *Firefighting_led_status;
	lv_obj_t *Firefighting_img_smoke;
	lv_obj_t *Firefighting_label_desc;
	lv_obj_t *Firefighting_line_1;
	lv_obj_t *Firefighting_label_warning;
	lv_obj_t *Firefighting_label_warning_tit;
	lv_obj_t *Firefighting_label_alert_tit;
	lv_obj_t *Firefighting_label_alert;
	lv_obj_t *Firefighting_cont_temp;
	lv_obj_t *Firefighting_label_7;
	lv_obj_t *Firefighting_label_6;
	lv_obj_t *Firefighting_led_1;
	lv_obj_t *Firefighting_img_1;
	lv_obj_t *Firefighting_label_5;
	lv_obj_t *Firefighting_line_2;
	lv_obj_t *Firefighting_label_heigh;
	lv_obj_t *Firefighting_label_3;
	lv_obj_t *Firefighting_label_2;
	lv_obj_t *Firefighting_label_low;
	lv_obj_t *Firefighting_cont_alert;
	lv_obj_t *Firefighting_label_security;
	lv_obj_t *Firefighting_label_temp_alert;
	lv_obj_t *Firefighting_bar_temp;
	lv_obj_t *Firefighting_bar_smoke;
	lv_obj_t *Firefighting_label_smoke_alert;
	lv_obj_t *Firefighting_label_auto_alert;
	lv_obj_t *Firefighting_bar_alert;
	lv_obj_t *Firefighting_bar_other;
	lv_obj_t *Firefighting_label_other;
	lv_obj_t *Firefighting_label_monitor;
	lv_obj_t *Firefighting_chart_power;
	lv_chart_series_t *Firefighting_chart_power_0;
	lv_chart_series_t *Firefighting_chart_power_1;
	lv_chart_series_t *Firefighting_chart_power_2;
	lv_obj_t *Firefighting_btn_home;
	lv_obj_t *Firefighting_btn_home_label;
	lv_obj_t *Firefighting_label_title;
	lv_obj_t *Firefighting_digital_clock_time;
	lv_obj_t *Firefighting_datetext_date;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, int32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                       uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                       lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);

void init_keyboard(lv_ui *ui);

extern lv_ui guider_ui;


void setup_scr_Home(lv_ui *ui);
void setup_scr_Electricity(lv_ui *ui);
void setup_scr_Firefighting(lv_ui *ui);

LV_IMG_DECLARE(_sub_page_bak_800x480);
LV_IMG_DECLARE(_temp_alpha_43x43);
LV_IMG_DECLARE(_Humidity_alpha_33x36);

LV_IMG_DECLARE(_home_bak_45x84);

LV_IMG_DECLARE(_menu_bak_800x480);
LV_IMG_DECLARE(_menu_bal_alpha_320x320);

LV_IMG_DECLARE(_menu_air_90x90);

LV_IMG_DECLARE(_menu_anfang_90x90);

LV_IMG_DECLARE(_menu_elevator_90x90);

LV_IMG_DECLARE(_menu_tem_90x90);

LV_IMG_DECLARE(_menu_xiaofang_90x90);

LV_IMG_DECLARE(_menu_electricity_90x90);

LV_IMG_DECLARE(_menu_light_90x90);
LV_IMG_DECLARE(_menu_light_alpha_64x61);

LV_IMG_DECLARE(_sub_page_bak_800x480);

LV_IMG_DECLARE(_home_bak_43x84);

LV_IMG_DECLARE(_pos_200x64);

LV_IMG_DECLARE(_pos_200x64);

LV_IMG_DECLARE(_pos_200x64);

LV_IMG_DECLARE(_pos_200x64);

LV_IMG_DECLARE(_pos_200x64);

LV_IMG_DECLARE(_rect_bak_480x320);
LV_IMG_DECLARE(_temp_alpha_43x43);
LV_IMG_DECLARE(_temp_alpha_43x43);
LV_IMG_DECLARE(_temp_alpha_43x43);

LV_IMG_DECLARE(_sub_page_bak_800x480);
LV_IMG_DECLARE(_menu_electricity_alpha_90x90);
LV_IMG_DECLARE(_menu_tem_alpha_90x90);

LV_IMG_DECLARE(_home_bak_43x84);

LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_16)
LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_18)
LV_FONT_DECLARE(lv_font_montserratMedium_30)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_20)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_14)
LV_FONT_DECLARE(lv_font_AguafinaScript_Regular_22)
LV_FONT_DECLARE(lv_font_montserratMedium_20)
LV_FONT_DECLARE(lv_font_montserratMedium_18)
LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_montserratMedium_14)
LV_FONT_DECLARE(lv_font_montserratMedium_13)
LV_FONT_DECLARE(lv_font_arial_12)


#ifdef __cplusplus
}
#endif
#endif
