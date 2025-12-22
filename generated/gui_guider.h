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
	lv_obj_t *Home_chart_temp;
	lv_chart_series_t *Home_chart_temp_0;
	lv_chart_series_t *Home_chart_temp_1;
	lv_chart_series_t *Home_chart_temp_2;
	lv_obj_t *Home_btn_temp_;
	lv_obj_t *Home_btn_temp__label;
	lv_obj_t *Home_btn_humi_;
	lv_obj_t *Home_btn_humi__label;
	lv_obj_t *Home_btn_light_;
	lv_obj_t *Home_btn_light__label;
	lv_obj_t *Home_cont_temp;
	lv_obj_t *Home_label_temp_tit;
	lv_obj_t *Home_arc_temp;
	lv_obj_t *Home_arc_humi;
	lv_obj_t *Home_label_temp_val;
	lv_obj_t *Home_label_wet_val;
	lv_obj_t *Home_img_temp;
	lv_obj_t *Home_img_humidity;
	lv_obj_t *Home_label_temp_unit2;
	lv_obj_t *Home_label_gz;
	lv_obj_t *Home_label_temp_unit1;
	lv_obj_t *Home_arc_light;
	lv_obj_t *Home_label_lux;
	lv_obj_t *Home_label_1;
	lv_obj_t *Home_label_2;
	lv_obj_t *Home_label_home_title;
	lv_obj_t *Home_btn_menu;
	lv_obj_t *Home_btn_menu_label;
	lv_obj_t *Home_datetext_date;
	lv_obj_t *Home_digital_clock_time;
	lv_obj_t *Home_img_light;
	lv_obj_t *Home_label_light_val;
	lv_obj_t *Home_cont_menu;
	lv_obj_t *Home_img_tick;
	lv_obj_t *Home_label_monitor;
	lv_obj_t *Home_sw_led1;
	lv_obj_t *Home_sw_led2;
	lv_obj_t *Home_sw_led3;
	lv_obj_t *Home_sw_beep;
	lv_obj_t *Home_sw_led4;
	lv_obj_t *Home_label_3;
	lv_obj_t *Home_label_4;
	lv_obj_t *Home_label_5;
	lv_obj_t *Home_label_6;
	lv_obj_t *Home_label_7;
	lv_obj_t *Home_imgbtn_1;
	lv_obj_t *Home_imgbtn_1_label;
	lv_obj_t *zigbee;
	bool zigbee_del;
	lv_obj_t *zigbee_cont_dev_control;
	lv_obj_t *zigbee_label_23;
	lv_obj_t *zigbee_img_7;
	lv_obj_t *zigbee_label_31;
	lv_obj_t *zigbee_label_32;
	lv_obj_t *zigbee_label_33;
	lv_obj_t *zigbee_label_temperature_val;
	lv_obj_t *zigbee_cont_temp;
	lv_obj_t *zigbee_label_22;
	lv_obj_t *zigbee_label_21;
	lv_obj_t *zigbee_label_humidity_val;
	lv_obj_t *zigbee_label_19;
	lv_obj_t *zigbee_label_18;
	lv_obj_t *zigbee_label_17;
	lv_obj_t *zigbee_label_16;
	lv_obj_t *zigbee_label_15;
	lv_obj_t *zigbee_label_14;
	lv_obj_t *zigbee_img_4;
	lv_obj_t *zigbee_label_24;
	lv_obj_t *zigbee_label_dew_point_val;
	lv_obj_t *zigbee_label_26;
	lv_obj_t *zigbee_img_5;
	lv_obj_t *zigbee_img_6;
	lv_obj_t *zigbee_label_27;
	lv_obj_t *zigbee_label_human_detected_val;
	lv_obj_t *zigbee_label_29;
	lv_obj_t *zigbee_label_vibration_val;
	lv_obj_t *zigbee_img_8;
	lv_obj_t *zigbee_img_9;
	lv_obj_t *zigbee_img_10;
	lv_obj_t *zigbee_label_home_title;
	lv_obj_t *zigbee_btn_menu;
	lv_obj_t *zigbee_btn_menu_label;
	lv_obj_t *zigbee_datetext_date;
	lv_obj_t *zigbee_digital_clock_time;
	lv_obj_t *zigbee_label_illumination_val;
	lv_obj_t *zigbee_cont_menu;
	lv_obj_t *zigbee_img_1;
	lv_obj_t *zigbee_label_13;
	lv_obj_t *zigbee_sw_5;
	lv_obj_t *zigbee_sw_4;
	lv_obj_t *zigbee_sw_3;
	lv_obj_t *zigbee_sw_2;
	lv_obj_t *zigbee_sw_1;
	lv_obj_t *zigbee_label_12;
	lv_obj_t *zigbee_label_11;
	lv_obj_t *zigbee_label_10;
	lv_obj_t *zigbee_label_9;
	lv_obj_t *zigbee_label_8;
	lv_obj_t *zigbee_imgbtn_2;
	lv_obj_t *zigbee_imgbtn_2_label;
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
void setup_scr_zigbee(lv_ui *ui);

LV_IMG_DECLARE(_sub_page_bak_800x480);
LV_IMG_DECLARE(_temp_alpha_92x98);
LV_IMG_DECLARE(_Humidity_alpha_56x68);

LV_IMG_DECLARE(_home_bak_45x84);
LV_IMG_DECLARE(_menu_light_alpha_64x61);

LV_IMG_DECLARE(_menu_bak_800x480);
LV_IMG_DECLARE(_menu_bal_alpha_320x320);
LV_IMG_DECLARE(_menu_elevator_alpha_95x89);
LV_IMG_DECLARE(_menu_icon_bak_alpha_95x89);
LV_IMG_DECLARE(_menu_elevator_alpha_95x89);
LV_IMG_DECLARE(_menu_icon_bak_alpha_95x89);

LV_IMG_DECLARE(_sub_page_bak_800x480);
LV_IMG_DECLARE(_8b5dcb72c7df5a77d99214e174d2ec0b_alpha_79x76);
LV_IMG_DECLARE(_dew_alpha_79x76);
LV_IMG_DECLARE(_human_alpha_77x80);
LV_IMG_DECLARE(_6a12a02693d60ca0cd70491351de2d54_alpha_79x82);
LV_IMG_DECLARE(_ddf538df72b089004cf457c6bcde0026_alpha_79x76);
LV_IMG_DECLARE(_272e830a3df8262600a6efa6550e374d_alpha_79x76);
LV_IMG_DECLARE(_15ddc8832c1a305680d536dddc738589_alpha_79x76);

LV_IMG_DECLARE(_home_bak_45x84);

LV_IMG_DECLARE(_menu_bak_800x480);
LV_IMG_DECLARE(_menu_bal_alpha_320x320);
LV_IMG_DECLARE(_menu_elevator_alpha_95x89);
LV_IMG_DECLARE(_menu_icon_bak_alpha_95x89);
LV_IMG_DECLARE(_menu_elevator_alpha_95x89);
LV_IMG_DECLARE(_menu_icon_bak_alpha_95x89);

LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_16)
LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_montserratMedium_25)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_25)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_20)
LV_FONT_DECLARE(lv_font_montserratMedium_18)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_18)
LV_FONT_DECLARE(lv_font_montserratMedium_30)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_24)
LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_montserratMedium_20)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_28)


#ifdef __cplusplus
}
#endif
#endif
