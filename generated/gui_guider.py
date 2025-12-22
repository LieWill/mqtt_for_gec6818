# Copyright 2025 NXP
# NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
# accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
# activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
# comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
# terms, then you may not retain, install, activate or otherwise use the software.

import SDL
import utime as time
import usys as sys
import lvgl as lv
import lodepng as png
import ustruct
import fs_driver

lv.init()
SDL.init(w=800,h=480)

# Register SDL display driver.
disp_buf1 = lv.disp_draw_buf_t()
buf1_1 = bytearray(800*480*4)
disp_buf1.init(buf1_1, None, len(buf1_1)//4)
disp_drv = lv.disp_drv_t()
disp_drv.init()
disp_drv.draw_buf = disp_buf1
disp_drv.flush_cb = SDL.monitor_flush
disp_drv.hor_res = 800
disp_drv.ver_res = 480
disp_drv.register()

# Regsiter SDL mouse driver
indev_drv = lv.indev_drv_t()
indev_drv.init()
indev_drv.type = lv.INDEV_TYPE.POINTER
indev_drv.read_cb = SDL.mouse_read
indev_drv.register()

fs_drv = lv.fs_drv_t()
fs_driver.fs_register(fs_drv, 'Z')

# Below: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

COLOR_SIZE = lv.color_t.__SIZE__
COLOR_IS_SWAPPED = hasattr(lv.color_t().ch,'green_h')

class lodepng_error(RuntimeError):
    def __init__(self, err):
        if type(err) is int:
            super().__init__(png.error_text(err))
        else:
            super().__init__(err)

# Parse PNG file header
# Taken from https://github.com/shibukawa/imagesize_py/blob/ffef30c1a4715c5acf90e8945ceb77f4a2ed2d45/imagesize.py#L63-L85

def get_png_info(decoder, src, header):
    # Only handle variable image types

    if lv.img.src_get_type(src) != lv.img.SRC.VARIABLE:
        return lv.RES.INV

    data = lv.img_dsc_t.__cast__(src).data
    if data == None:
        return lv.RES.INV

    png_header = bytes(data.__dereference__(24))

    if png_header.startswith(b'\211PNG\r\n\032\n'):
        if png_header[12:16] == b'IHDR':
            start = 16
        # Maybe this is for an older PNG version.
        else:
            start = 8
        try:
            width, height = ustruct.unpack(">LL", png_header[start:start+8])
        except ustruct.error:
            return lv.RES.INV
    else:
        return lv.RES.INV

    header.always_zero = 0
    header.w = width
    header.h = height
    header.cf = lv.img.CF.TRUE_COLOR_ALPHA

    return lv.RES.OK

def convert_rgba8888_to_bgra8888(img_view):
    for i in range(0, len(img_view), lv.color_t.__SIZE__):
        ch = lv.color_t.__cast__(img_view[i:i]).ch
        ch.red, ch.blue = ch.blue, ch.red

# Read and parse PNG file

def open_png(decoder, dsc):
    img_dsc = lv.img_dsc_t.__cast__(dsc.src)
    png_data = img_dsc.data
    png_size = img_dsc.data_size
    png_decoded = png.C_Pointer()
    png_width = png.C_Pointer()
    png_height = png.C_Pointer()
    error = png.decode32(png_decoded, png_width, png_height, png_data, png_size)
    if error:
        raise lodepng_error(error)
    img_size = png_width.int_val * png_height.int_val * 4
    img_data = png_decoded.ptr_val
    img_view = img_data.__dereference__(img_size)

    if COLOR_SIZE == 4:
        convert_rgba8888_to_bgra8888(img_view)
    else:
        raise lodepng_error("Error: Color mode not supported yet!")

    dsc.img_data = img_data
    return lv.RES.OK

# Above: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

decoder = lv.img.decoder_create()
decoder.info_cb = get_png_info
decoder.open_cb = open_png

def anim_x_cb(obj, v):
    obj.set_x(v)

def anim_y_cb(obj, v):
    obj.set_y(v)

def anim_width_cb(obj, v):
    obj.set_width(v)

def anim_height_cb(obj, v):
    obj.set_height(v)

def anim_img_zoom_cb(obj, v):
    obj.set_zoom(v)

def anim_img_rotate_cb(obj, v):
    obj.set_angle(v)

global_font_cache = {}
def test_font(font_family, font_size):
    global global_font_cache
    if font_family + str(font_size) in global_font_cache:
        return global_font_cache[font_family + str(font_size)]
    if font_size % 2:
        candidates = [
            (font_family, font_size),
            (font_family, font_size-font_size%2),
            (font_family, font_size+font_size%2),
            ("montserrat", font_size-font_size%2),
            ("montserrat", font_size+font_size%2),
            ("montserrat", 16)
        ]
    else:
        candidates = [
            (font_family, font_size),
            ("montserrat", font_size),
            ("montserrat", 16)
        ]
    for (family, size) in candidates:
        try:
            if eval(f'lv.font_{family}_{size}'):
                global_font_cache[font_family + str(font_size)] = eval(f'lv.font_{family}_{size}')
                if family != font_family or size != font_size:
                    print(f'WARNING: lv.font_{family}_{size} is used!')
                return eval(f'lv.font_{family}_{size}')
        except AttributeError:
            try:
                load_font = lv.font_load(f"Z:MicroPython/lv_font_{family}_{size}.fnt")
                global_font_cache[font_family + str(font_size)] = load_font
                return load_font
            except:
                if family == font_family and size == font_size:
                    print(f'WARNING: lv.font_{family}_{size} is NOT supported!')

global_image_cache = {}
def load_image(file):
    global global_image_cache
    if file in global_image_cache:
        return global_image_cache[file]
    try:
        with open(file,'rb') as f:
            data = f.read()
    except:
        print(f'Could not open {file}')
        sys.exit()

    img = lv.img_dsc_t({
        'data_size': len(data),
        'data': data
    })
    global_image_cache[file] = img
    return img

def calendar_event_handler(e,obj):
    code = e.get_code()

    if code == lv.EVENT.VALUE_CHANGED:
        source = e.get_current_target()
        date = lv.calendar_date_t()
        if source.get_pressed_date(date) == lv.RES.OK:
            source.set_highlighted_dates([date], 1)

def spinbox_increment_event_cb(e, obj):
    code = e.get_code()
    if code == lv.EVENT.SHORT_CLICKED or code == lv.EVENT.LONG_PRESSED_REPEAT:
        obj.increment()
def spinbox_decrement_event_cb(e, obj):
    code = e.get_code()
    if code == lv.EVENT.SHORT_CLICKED or code == lv.EVENT.LONG_PRESSED_REPEAT:
        obj.decrement()

def digital_clock_cb(timer, obj, current_time, show_second, use_ampm):
    hour = int(current_time[0])
    minute = int(current_time[1])
    second = int(current_time[2])
    ampm = current_time[3]
    second = second + 1
    if second == 60:
        second = 0
        minute = minute + 1
        if minute == 60:
            minute = 0
            hour = hour + 1
            if use_ampm:
                if hour == 12:
                    if ampm == 'AM':
                        ampm = 'PM'
                    elif ampm == 'PM':
                        ampm = 'AM'
                if hour > 12:
                    hour = hour % 12
    hour = hour % 24
    if use_ampm:
        if show_second:
            obj.set_text("%d:%02d:%02d %s" %(hour, minute, second, ampm))
        else:
            obj.set_text("%d:%02d %s" %(hour, minute, ampm))
    else:
        if show_second:
            obj.set_text("%d:%02d:%02d" %(hour, minute, second))
        else:
            obj.set_text("%d:%02d" %(hour, minute))
    current_time[0] = hour
    current_time[1] = minute
    current_time[2] = second
    current_time[3] = ampm

def analog_clock_cb(timer, obj):
    datetime = time.localtime()
    hour = datetime[3]
    if hour >= 12: hour = hour - 12
    obj.set_time(hour, datetime[4], datetime[5])

def datetext_event_handler(e, obj):
    code = e.get_code()
    target = e.get_target()
    if code == lv.EVENT.FOCUSED:
        if obj is None:
            bg = lv.layer_top()
            bg.add_flag(lv.obj.FLAG.CLICKABLE)
            obj = lv.calendar(bg)
            scr = target.get_screen()
            scr_height = scr.get_height()
            scr_width = scr.get_width()
            obj.set_size(int(scr_width * 0.8), int(scr_height * 0.8))
            datestring = target.get_text()
            year = int(datestring.split('/')[0])
            month = int(datestring.split('/')[1])
            day = int(datestring.split('/')[2])
            obj.set_showed_date(year, month)
            highlighted_days=[lv.calendar_date_t({'year':year, 'month':month, 'day':day})]
            obj.set_highlighted_dates(highlighted_days, 1)
            obj.align(lv.ALIGN.CENTER, 0, 0)
            lv.calendar_header_arrow(obj)
            obj.add_event_cb(lambda e: datetext_calendar_event_handler(e, target), lv.EVENT.ALL, None)
            scr.update_layout()

def datetext_calendar_event_handler(e, obj):
    code = e.get_code()
    target = e.get_current_target()
    if code == lv.EVENT.VALUE_CHANGED:
        date = lv.calendar_date_t()
        if target.get_pressed_date(date) == lv.RES.OK:
            obj.set_text(f"{date.year}/{date.month}/{date.day}")
            bg = lv.layer_top()
            bg.clear_flag(lv.obj.FLAG.CLICKABLE)
            bg.set_style_bg_opa(lv.OPA.TRANSP, 0)
            target.delete()

# Create Home
Home = lv.obj()
Home.set_size(800, 480)
Home.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for Home, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home.set_style_bg_img_src("B:MicroPython/_sub_page_bak_800x480.bin", lv.PART.MAIN|lv.STATE.DEFAULT)
Home.set_style_bg_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home.set_style_bg_img_recolor_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Home_cont_dev_control
Home_cont_dev_control = lv.obj(Home)
Home_cont_dev_control.set_pos(296, 55)
Home_cont_dev_control.set_size(495, 407)
Home_cont_dev_control.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for Home_cont_dev_control, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_cont_dev_control.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_cont_dev_control.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_cont_dev_control.set_style_bg_opa(181, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_cont_dev_control.set_style_bg_color(lv.color_hex(0x154870), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_cont_dev_control.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_cont_dev_control.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_cont_dev_control.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_cont_dev_control.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_cont_dev_control.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_cont_dev_control.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create Home_label_dev
Home_label_dev = lv.label(Home_cont_dev_control)
Home_label_dev.set_text("设备控制\n")
Home_label_dev.set_long_mode(lv.label.LONG.WRAP)
Home_label_dev.set_width(lv.pct(100))
Home_label_dev.set_pos(0, 1)
Home_label_dev.set_size(460, 40)
# Set style for Home_label_dev, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_label_dev.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_dev.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_dev.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_dev.set_style_text_font(test_font("SourceHanSerifSC_Regular", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_dev.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_dev.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_dev.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_dev.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_dev.set_style_bg_opa(59, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_dev.set_style_bg_color(lv.color_hex(0x1e1e1e), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_dev.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_dev.set_style_pad_top(10, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_dev.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_dev.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_dev.set_style_pad_left(10, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_dev.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Home_chart_temp
Home_chart_temp = lv.chart(Home_cont_dev_control)
Home_chart_temp.set_type(lv.chart.TYPE.LINE)
Home_chart_temp.set_div_line_count(2, 2)
Home_chart_temp.set_point_count(16)
Home_chart_temp.set_range(lv.chart.AXIS.PRIMARY_Y, 10, 100)
Home_chart_temp.set_axis_tick(lv.chart.AXIS.PRIMARY_Y, 10, 5, 11, 1, True, 33)
Home_chart_temp.set_range(lv.chart.AXIS.SECONDARY_Y, 0, 4000)
Home_chart_temp.set_axis_tick(lv.chart.AXIS.SECONDARY_Y, 10, 5, 9, 1, True, 44)
Home_chart_temp.set_zoom_x(256)
Home_chart_temp.set_zoom_y(256)
Home_chart_temp.set_style_size(0, lv.PART.INDICATOR)
Home_chart_temp_series_0 = Home_chart_temp.add_series(lv.color_hex(0xff6500), lv.chart.AXIS.PRIMARY_Y)
Home_chart_temp.set_next_value(Home_chart_temp_series_0, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_0, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_0, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_0, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_0, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_0, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_0, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_0, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_0, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_0, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_0, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_0, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_0, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_0, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_0, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_0, 0)
Home_chart_temp_series_1 = Home_chart_temp.add_series(lv.color_hex(0x00c4ff), lv.chart.AXIS.PRIMARY_Y)
Home_chart_temp.set_next_value(Home_chart_temp_series_1, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_1, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_1, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_1, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_1, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_1, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_1, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_1, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_1, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_1, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_1, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_1, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_1, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_1, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_1, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_1, 0)
Home_chart_temp_series_2 = Home_chart_temp.add_series(lv.color_hex(0xebff00), lv.chart.AXIS.SECONDARY_Y)
Home_chart_temp.set_next_value(Home_chart_temp_series_2, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_2, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_2, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_2, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_2, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_2, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_2, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_2, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_2, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_2, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_2, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_2, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_2, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_2, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_2, 0)
Home_chart_temp.set_next_value(Home_chart_temp_series_2, 0)
Home_chart_temp.set_pos(50, 94)
Home_chart_temp.set_size(392, 297)
Home_chart_temp.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for Home_chart_temp, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_chart_temp.set_style_bg_opa(58, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_chart_temp.set_style_bg_color(lv.color_hex(0x00a8ff), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_chart_temp.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_chart_temp.set_style_border_width(1, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_chart_temp.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_chart_temp.set_style_border_color(lv.color_hex(0xe8e8e8), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_chart_temp.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_chart_temp.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_chart_temp.set_style_line_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_chart_temp.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for Home_chart_temp, Part: lv.PART.TICKS, State: lv.STATE.DEFAULT.
Home_chart_temp.set_style_text_color(lv.color_hex(0x77dfff), lv.PART.TICKS|lv.STATE.DEFAULT)
Home_chart_temp.set_style_text_font(test_font("montserratMedium", 16), lv.PART.TICKS|lv.STATE.DEFAULT)
Home_chart_temp.set_style_text_opa(255, lv.PART.TICKS|lv.STATE.DEFAULT)
Home_chart_temp.set_style_line_width(2, lv.PART.TICKS|lv.STATE.DEFAULT)
Home_chart_temp.set_style_line_color(lv.color_hex(0xe8e8e8), lv.PART.TICKS|lv.STATE.DEFAULT)
Home_chart_temp.set_style_line_opa(255, lv.PART.TICKS|lv.STATE.DEFAULT)

# Create Home_btn_temp_
Home_btn_temp_ = lv.btn(Home_cont_dev_control)
Home_btn_temp__label = lv.label(Home_btn_temp_)
Home_btn_temp__label.set_text("温度")
Home_btn_temp__label.set_long_mode(lv.label.LONG.WRAP)
Home_btn_temp__label.set_width(lv.pct(100))
Home_btn_temp__label.align(lv.ALIGN.CENTER, 0, 0)
Home_btn_temp_.set_style_pad_all(0, lv.STATE.DEFAULT)
Home_btn_temp_.set_pos(48, 54)
Home_btn_temp_.set_size(94, 32)
# Set style for Home_btn_temp_, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_btn_temp_.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_temp_.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_temp_.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_temp_.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_temp_.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_temp_.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_temp_.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_temp_.set_style_text_font(test_font("SourceHanSerifSC_Regular", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_temp_.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_temp_.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Home_btn_humi_
Home_btn_humi_ = lv.btn(Home_cont_dev_control)
Home_btn_humi__label = lv.label(Home_btn_humi_)
Home_btn_humi__label.set_text("湿度")
Home_btn_humi__label.set_long_mode(lv.label.LONG.WRAP)
Home_btn_humi__label.set_width(lv.pct(100))
Home_btn_humi__label.align(lv.ALIGN.CENTER, 0, 0)
Home_btn_humi_.set_style_pad_all(0, lv.STATE.DEFAULT)
Home_btn_humi_.set_pos(176, 53)
Home_btn_humi_.set_size(94, 32)
# Set style for Home_btn_humi_, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_btn_humi_.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_humi_.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_humi_.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_humi_.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_humi_.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_humi_.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_humi_.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_humi_.set_style_text_font(test_font("SourceHanSerifSC_Regular", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_humi_.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_humi_.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Home_btn_light_
Home_btn_light_ = lv.btn(Home_cont_dev_control)
Home_btn_light__label = lv.label(Home_btn_light_)
Home_btn_light__label.set_text("光照")
Home_btn_light__label.set_long_mode(lv.label.LONG.WRAP)
Home_btn_light__label.set_width(lv.pct(100))
Home_btn_light__label.align(lv.ALIGN.CENTER, 0, 0)
Home_btn_light_.set_style_pad_all(0, lv.STATE.DEFAULT)
Home_btn_light_.set_pos(312, 54)
Home_btn_light_.set_size(94, 32)
# Set style for Home_btn_light_, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_btn_light_.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_light_.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_light_.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_light_.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_light_.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_light_.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_light_.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_light_.set_style_text_font(test_font("SourceHanSerifSC_Regular", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_light_.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_light_.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Home_cont_temp
Home_cont_temp = lv.obj(Home)
Home_cont_temp.set_pos(60, 62)
Home_cont_temp.set_size(225, 289)
Home_cont_temp.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for Home_cont_temp, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_cont_temp.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_cont_temp.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_cont_temp.set_style_bg_opa(181, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_cont_temp.set_style_bg_color(lv.color_hex(0x154870), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_cont_temp.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_cont_temp.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_cont_temp.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_cont_temp.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_cont_temp.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_cont_temp.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create Home_label_temp_tit
Home_label_temp_tit = lv.label(Home_cont_temp)
Home_label_temp_tit.set_text("温湿度监控")
Home_label_temp_tit.set_long_mode(lv.label.LONG.WRAP)
Home_label_temp_tit.set_width(lv.pct(100))
Home_label_temp_tit.set_pos(-2, 3)
Home_label_temp_tit.set_size(240, 40)
# Set style for Home_label_temp_tit, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_label_temp_tit.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_tit.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_tit.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_tit.set_style_text_font(test_font("SourceHanSerifSC_Regular", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_tit.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_tit.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_tit.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_tit.set_style_text_align(lv.TEXT_ALIGN.LEFT, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_tit.set_style_bg_opa(59, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_tit.set_style_bg_color(lv.color_hex(0x1e1e1e), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_tit.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_tit.set_style_pad_top(10, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_tit.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_tit.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_tit.set_style_pad_left(10, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_tit.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Home_arc_temp
Home_arc_temp = lv.arc(Home_cont_temp)
Home_arc_temp.set_mode(lv.arc.MODE.NORMAL)
Home_arc_temp.set_range(0, 40)
Home_arc_temp.set_bg_angles(0, 360)
Home_arc_temp.set_value(20)
Home_arc_temp.set_rotation(90)
Home_arc_temp.set_pos(11, 56)
Home_arc_temp.set_size(100, 100)
# Set style for Home_arc_temp, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_arc_temp.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_arc_temp.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_arc_temp.set_style_arc_width(8, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_arc_temp.set_style_arc_opa(45, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_arc_temp.set_style_arc_color(lv.color_hex(0xe7e8e8), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_arc_temp.set_style_radius(6, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_arc_temp.set_style_pad_top(5, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_arc_temp.set_style_pad_bottom(5, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_arc_temp.set_style_pad_left(5, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_arc_temp.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_arc_temp.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for Home_arc_temp, Part: lv.PART.INDICATOR, State: lv.STATE.DEFAULT.
Home_arc_temp.set_style_arc_width(8, lv.PART.INDICATOR|lv.STATE.DEFAULT)
Home_arc_temp.set_style_arc_opa(255, lv.PART.INDICATOR|lv.STATE.DEFAULT)
Home_arc_temp.set_style_arc_color(lv.color_hex(0x0eff85), lv.PART.INDICATOR|lv.STATE.DEFAULT)

# Set style for Home_arc_temp, Part: lv.PART.KNOB, State: lv.STATE.DEFAULT.
Home_arc_temp.set_style_bg_opa(255, lv.PART.KNOB|lv.STATE.DEFAULT)
Home_arc_temp.set_style_bg_color(lv.color_hex(0x0eff85), lv.PART.KNOB|lv.STATE.DEFAULT)
Home_arc_temp.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.KNOB|lv.STATE.DEFAULT)
Home_arc_temp.set_style_pad_all(4, lv.PART.KNOB|lv.STATE.DEFAULT)

# Create Home_arc_humi
Home_arc_humi = lv.arc(Home_cont_temp)
Home_arc_humi.set_mode(lv.arc.MODE.NORMAL)
Home_arc_humi.set_range(0, 40)
Home_arc_humi.set_bg_angles(0, 360)
Home_arc_humi.set_value(10)
Home_arc_humi.set_rotation(90)
Home_arc_humi.set_pos(126, 56)
Home_arc_humi.set_size(100, 100)
# Set style for Home_arc_humi, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_arc_humi.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_arc_humi.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_arc_humi.set_style_arc_width(8, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_arc_humi.set_style_arc_opa(45, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_arc_humi.set_style_arc_color(lv.color_hex(0xe7e8e8), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_arc_humi.set_style_radius(6, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_arc_humi.set_style_pad_top(5, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_arc_humi.set_style_pad_bottom(5, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_arc_humi.set_style_pad_left(5, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_arc_humi.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_arc_humi.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for Home_arc_humi, Part: lv.PART.INDICATOR, State: lv.STATE.DEFAULT.
Home_arc_humi.set_style_arc_width(8, lv.PART.INDICATOR|lv.STATE.DEFAULT)
Home_arc_humi.set_style_arc_opa(255, lv.PART.INDICATOR|lv.STATE.DEFAULT)
Home_arc_humi.set_style_arc_color(lv.color_hex(0x00c8eb), lv.PART.INDICATOR|lv.STATE.DEFAULT)

# Set style for Home_arc_humi, Part: lv.PART.KNOB, State: lv.STATE.DEFAULT.
Home_arc_humi.set_style_bg_opa(255, lv.PART.KNOB|lv.STATE.DEFAULT)
Home_arc_humi.set_style_bg_color(lv.color_hex(0x00c8eb), lv.PART.KNOB|lv.STATE.DEFAULT)
Home_arc_humi.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.KNOB|lv.STATE.DEFAULT)
Home_arc_humi.set_style_pad_all(4, lv.PART.KNOB|lv.STATE.DEFAULT)

# Create Home_label_temp_val
Home_label_temp_val = lv.label(Home_cont_temp)
Home_label_temp_val.set_text("28")
Home_label_temp_val.set_long_mode(lv.label.LONG.WRAP)
Home_label_temp_val.set_width(lv.pct(100))
Home_label_temp_val.set_pos(35, 119)
Home_label_temp_val.set_size(37, 21)
# Set style for Home_label_temp_val, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_label_temp_val.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_val.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_val.set_style_text_color(lv.color_hex(0xa8cb11), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_val.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_val.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_val.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_val.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_val.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_val.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_val.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_val.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_val.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_val.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_val.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Home_label_wet_val
Home_label_wet_val = lv.label(Home_cont_temp)
Home_label_wet_val.set_text("50")
Home_label_wet_val.set_long_mode(lv.label.LONG.WRAP)
Home_label_wet_val.set_width(lv.pct(100))
Home_label_wet_val.set_pos(151, 113)
Home_label_wet_val.set_size(34, 22)
# Set style for Home_label_wet_val, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_label_wet_val.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_wet_val.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_wet_val.set_style_text_color(lv.color_hex(0xa8cb11), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_wet_val.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_wet_val.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_wet_val.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_wet_val.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_wet_val.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_wet_val.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_wet_val.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_wet_val.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_wet_val.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_wet_val.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_wet_val.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Home_img_temp
Home_img_temp = lv.img(Home_cont_temp)
Home_img_temp.set_src("B:MicroPython/_temp_alpha_43x43.bin")
Home_img_temp.add_flag(lv.obj.FLAG.CLICKABLE)
Home_img_temp.set_pivot(50,50)
Home_img_temp.set_angle(0)
Home_img_temp.set_pos(40, 77)
Home_img_temp.set_size(43, 43)
# Set style for Home_img_temp, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_img_temp.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_img_temp.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_img_temp.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Home_img_humidity
Home_img_humidity = lv.img(Home_cont_temp)
Home_img_humidity.set_src("B:MicroPython/_Humidity_alpha_33x36.bin")
Home_img_humidity.add_flag(lv.obj.FLAG.CLICKABLE)
Home_img_humidity.set_pivot(50,50)
Home_img_humidity.set_angle(0)
Home_img_humidity.set_pos(160, 75)
Home_img_humidity.set_size(33, 36)
# Set style for Home_img_humidity, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_img_humidity.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_img_humidity.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_img_humidity.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Home_label_temp_unit2
Home_label_temp_unit2 = lv.label(Home_cont_temp)
Home_label_temp_unit2.set_text("℃")
Home_label_temp_unit2.set_long_mode(lv.label.LONG.WRAP)
Home_label_temp_unit2.set_width(lv.pct(100))
Home_label_temp_unit2.set_pos(58, 118)
Home_label_temp_unit2.set_size(26, 19)
# Set style for Home_label_temp_unit2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_label_temp_unit2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_unit2.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_unit2.set_style_text_color(lv.color_hex(0xdbff54), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_unit2.set_style_text_font(test_font("SourceHanSerifSC_Regular", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_unit2.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_unit2.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_unit2.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_unit2.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_unit2.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_unit2.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_unit2.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_unit2.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_unit2.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_unit2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Home_label_temp_unit1
Home_label_temp_unit1 = lv.label(Home_cont_temp)
Home_label_temp_unit1.set_text("%")
Home_label_temp_unit1.set_long_mode(lv.label.LONG.WRAP)
Home_label_temp_unit1.set_width(lv.pct(100))
Home_label_temp_unit1.set_pos(172, 113)
Home_label_temp_unit1.set_size(36, 23)
# Set style for Home_label_temp_unit1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_label_temp_unit1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_unit1.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_unit1.set_style_text_color(lv.color_hex(0xa8cb11), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_unit1.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_unit1.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_unit1.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_unit1.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_unit1.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_unit1.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_unit1.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_unit1.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_unit1.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_unit1.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_temp_unit1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Home_arc_light
Home_arc_light = lv.arc(Home_cont_temp)
Home_arc_light.set_mode(lv.arc.MODE.NORMAL)
Home_arc_light.set_range(0, 4000)
Home_arc_light.set_bg_angles(0, 360)
Home_arc_light.set_value(15)
Home_arc_light.set_rotation(90)
Home_arc_light.set_pos(10, 173)
Home_arc_light.set_size(100, 100)
# Set style for Home_arc_light, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_arc_light.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_arc_light.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_arc_light.set_style_arc_width(20, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_arc_light.set_style_arc_opa(100, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_arc_light.set_style_arc_color(lv.color_hex(0xb2bb00), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_arc_light.set_style_radius(6, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_arc_light.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_arc_light.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_arc_light.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_arc_light.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_arc_light.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for Home_arc_light, Part: lv.PART.INDICATOR, State: lv.STATE.DEFAULT.
Home_arc_light.set_style_arc_width(12, lv.PART.INDICATOR|lv.STATE.DEFAULT)
Home_arc_light.set_style_arc_opa(255, lv.PART.INDICATOR|lv.STATE.DEFAULT)
Home_arc_light.set_style_arc_color(lv.color_hex(0xc6f300), lv.PART.INDICATOR|lv.STATE.DEFAULT)

# Set style for Home_arc_light, Part: lv.PART.KNOB, State: lv.STATE.DEFAULT.
Home_arc_light.set_style_bg_opa(255, lv.PART.KNOB|lv.STATE.DEFAULT)
Home_arc_light.set_style_bg_color(lv.color_hex(0xd0ff00), lv.PART.KNOB|lv.STATE.DEFAULT)
Home_arc_light.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.KNOB|lv.STATE.DEFAULT)
Home_arc_light.set_style_pad_all(5, lv.PART.KNOB|lv.STATE.DEFAULT)

# Create Home_label_home_title
Home_label_home_title = lv.label(Home)
Home_label_home_title.set_text("MQTT智能监控系统")
Home_label_home_title.set_long_mode(lv.label.LONG.WRAP)
Home_label_home_title.set_width(lv.pct(100))
Home_label_home_title.set_pos(226, 17)
Home_label_home_title.set_size(350, 31)
# Set style for Home_label_home_title, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_label_home_title.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_home_title.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_home_title.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_home_title.set_style_text_font(test_font("SourceHanSerifSC_Regular", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_home_title.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_home_title.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_home_title.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_home_title.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_home_title.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_home_title.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_home_title.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_home_title.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_home_title.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_home_title.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Home_btn_menu
Home_btn_menu = lv.btn(Home)
Home_btn_menu_label = lv.label(Home_btn_menu)
Home_btn_menu_label.set_text(""+lv.SYMBOL.RIGHT+"  ")
Home_btn_menu_label.set_long_mode(lv.label.LONG.WRAP)
Home_btn_menu_label.set_width(lv.pct(100))
Home_btn_menu_label.align(lv.ALIGN.CENTER, 0, 0)
Home_btn_menu.set_style_pad_all(0, lv.STATE.DEFAULT)
Home_btn_menu.set_pos(0, 196)
Home_btn_menu.set_size(45, 84)
# Set style for Home_btn_menu, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_btn_menu.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_menu.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_menu.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_menu.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_menu.set_style_bg_img_src("B:MicroPython/_home_bak_45x84.bin", lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_menu.set_style_bg_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_menu.set_style_bg_img_recolor_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_menu.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_menu.set_style_text_font(test_font("montserratMedium", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_menu.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_menu.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Home_datetext_date
Home_datetext_date = lv.label(Home)
Home_datetext_date.set_text("2026/12/18")
Home_datetext_date.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
Home_datetext_date.add_flag(lv.obj.FLAG.CLICKABLE)
Home_datetext_date_calendar = None
Home_datetext_date.add_event_cb(lambda e: datetext_event_handler(e, Home_datetext_date_calendar), lv.EVENT.ALL, None)
Home_datetext_date.set_pos(628, 10)
Home_datetext_date.set_size(98, 36)
# Set style for Home_datetext_date, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_datetext_date.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_datetext_date.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_datetext_date.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_datetext_date.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_datetext_date.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_datetext_date.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_datetext_date.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_datetext_date.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_datetext_date.set_style_pad_top(7, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_datetext_date.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_datetext_date.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_datetext_date.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Home_digital_clock_time
Home_digital_clock_time_time = [int(11), int(25), int(50), ""]
Home_digital_clock_time = lv.dclock(Home, "11:25:50")
Home_digital_clock_time_timer = lv.timer_create_basic()
Home_digital_clock_time_timer.set_period(1000)
Home_digital_clock_time_timer.set_cb(lambda src: digital_clock_cb(Home_digital_clock_time_timer, Home_digital_clock_time, Home_digital_clock_time_time, True, False ))
Home_digital_clock_time.set_pos(691, 10)
Home_digital_clock_time.set_size(98, 31)
# Set style for Home_digital_clock_time, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_digital_clock_time.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_digital_clock_time.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_digital_clock_time.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_digital_clock_time.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_digital_clock_time.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_digital_clock_time.set_style_text_align(lv.TEXT_ALIGN.RIGHT, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_digital_clock_time.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_digital_clock_time.set_style_pad_top(7, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_digital_clock_time.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_digital_clock_time.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_digital_clock_time.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_digital_clock_time.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Home_img_light
Home_img_light = lv.img(Home)
Home_img_light.set_src("B:MicroPython/_menu_light_alpha_64x61.bin")
Home_img_light.add_flag(lv.obj.FLAG.CLICKABLE)
Home_img_light.set_pivot(50,50)
Home_img_light.set_angle(0)
Home_img_light.set_pos(88, 255)
Home_img_light.set_size(64, 61)
# Set style for Home_img_light, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_img_light.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_img_light.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_img_light.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Home_label_light_val
Home_label_light_val = lv.label(Home)
Home_label_light_val.set_text("8888")
Home_label_light_val.set_long_mode(lv.label.LONG.WRAP)
Home_label_light_val.set_width(lv.pct(100))
Home_label_light_val.set_pos(179, 292)
Home_label_light_val.set_size(79, 23)
# Set style for Home_label_light_val, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_label_light_val.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_light_val.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_light_val.set_style_text_color(lv.color_hex(0xFFFFFF), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_light_val.set_style_text_font(test_font("SourceHanSerifSC_Regular", 20), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_light_val.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_light_val.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_light_val.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_light_val.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_light_val.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_light_val.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_light_val.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_light_val.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_light_val.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_light_val.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Home_label_22
Home_label_22 = lv.label(Home)
Home_label_22.set_text("光照")
Home_label_22.set_long_mode(lv.label.LONG.WRAP)
Home_label_22.set_width(lv.pct(100))
Home_label_22.set_pos(176, 250)
Home_label_22.set_size(100, 32)
# Set style for Home_label_22, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_label_22.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_22.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_22.set_style_text_color(lv.color_hex(0xf3ff00), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_22.set_style_text_font(test_font("SourceHanSerifSC_Regular", 20), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_22.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_22.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_22.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_22.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_22.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_22.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_22.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_22.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_22.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_22.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Home_label_23
Home_label_23 = lv.label(Home)
Home_label_23.set_text("Lux")
Home_label_23.set_long_mode(lv.label.LONG.WRAP)
Home_label_23.set_width(lv.pct(100))
Home_label_23.set_pos(234, 295)
Home_label_23.set_size(52, 23)
# Set style for Home_label_23, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_label_23.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_23.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_23.set_style_text_color(lv.color_hex(0xcfff00), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_23.set_style_text_font(test_font("montserratMedium", 18), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_23.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_23.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_23.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_23.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_23.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_23.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_23.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_23.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_23.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_23.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Home_cont_menu
Home_cont_menu = lv.obj(Home)
Home_cont_menu.set_pos(0, 0)
Home_cont_menu.set_size(800, 480)
Home_cont_menu.add_flag(lv.obj.FLAG.HIDDEN)
Home_cont_menu.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for Home_cont_menu, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_cont_menu.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_cont_menu.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_cont_menu.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_cont_menu.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_cont_menu.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_cont_menu.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_cont_menu.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_cont_menu.set_style_bg_img_src("B:MicroPython/_menu_bak_800x480.bin", lv.PART.MAIN|lv.STATE.DEFAULT)
Home_cont_menu.set_style_bg_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_cont_menu.set_style_bg_img_recolor_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_cont_menu.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create Home_img_tick
Home_img_tick = lv.img(Home_cont_menu)
Home_img_tick.set_src("B:MicroPython/_menu_bal_alpha_320x320.bin")
Home_img_tick.add_flag(lv.obj.FLAG.CLICKABLE)
Home_img_tick.set_pivot(50,50)
Home_img_tick.set_angle(0)
Home_img_tick.set_pos(-159, 80)
Home_img_tick.set_size(320, 320)
# Set style for Home_img_tick, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_img_tick.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_img_tick.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_img_tick.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Home_btn_phone
Home_btn_phone = lv.btn(Home_cont_menu)
Home_btn_phone_label = lv.label(Home_btn_phone)
Home_btn_phone_label.set_text("")
Home_btn_phone_label.set_long_mode(lv.label.LONG.WRAP)
Home_btn_phone_label.set_width(lv.pct(100))
Home_btn_phone_label.align(lv.ALIGN.CENTER, 0, 0)
Home_btn_phone.set_style_pad_all(0, lv.STATE.DEFAULT)
Home_btn_phone.set_pos(14, 2)
Home_btn_phone.set_size(90, 90)
# Set style for Home_btn_phone, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_btn_phone.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_phone.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_phone.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_phone.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_phone.set_style_bg_img_src("B:MicroPython/_menu_air_90x90.bin", lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_phone.set_style_bg_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_phone.set_style_bg_img_recolor_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_phone.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_phone.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_phone.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_phone.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Home_btn_warning
Home_btn_warning = lv.btn(Home_cont_menu)
Home_btn_warning_label = lv.label(Home_btn_warning)
Home_btn_warning_label.set_text("")
Home_btn_warning_label.set_long_mode(lv.label.LONG.WRAP)
Home_btn_warning_label.set_width(lv.pct(100))
Home_btn_warning_label.align(lv.ALIGN.CENTER, 0, 0)
Home_btn_warning.set_style_pad_all(0, lv.STATE.DEFAULT)
Home_btn_warning.set_pos(85, 43)
Home_btn_warning.set_size(90, 90)
# Set style for Home_btn_warning, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_btn_warning.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_warning.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_warning.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_warning.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_warning.set_style_bg_img_src("B:MicroPython/_menu_anfang_90x90.bin", lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_warning.set_style_bg_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_warning.set_style_bg_img_recolor_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_warning.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_warning.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_warning.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_warning.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Home_btn_power
Home_btn_power = lv.btn(Home_cont_menu)
Home_btn_power_label = lv.label(Home_btn_power)
Home_btn_power_label.set_text("")
Home_btn_power_label.set_long_mode(lv.label.LONG.WRAP)
Home_btn_power_label.set_width(lv.pct(100))
Home_btn_power_label.align(lv.ALIGN.CENTER, 0, 0)
Home_btn_power.set_style_pad_all(0, lv.STATE.DEFAULT)
Home_btn_power.set_pos(141, 113)
Home_btn_power.set_size(90, 90)
# Set style for Home_btn_power, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_btn_power.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_power.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_power.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_power.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_power.set_style_bg_img_src("B:MicroPython/_menu_elevator_90x90.bin", lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_power.set_style_bg_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_power.set_style_bg_img_recolor_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_power.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_power.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_power.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_power.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Home_btn_temp
Home_btn_temp = lv.btn(Home_cont_menu)
Home_btn_temp_label = lv.label(Home_btn_temp)
Home_btn_temp_label.set_text("")
Home_btn_temp_label.set_long_mode(lv.label.LONG.WRAP)
Home_btn_temp_label.set_width(lv.pct(100))
Home_btn_temp_label.align(lv.ALIGN.CENTER, 0, 0)
Home_btn_temp.set_style_pad_all(0, lv.STATE.DEFAULT)
Home_btn_temp.set_pos(160, 198)
Home_btn_temp.set_size(90, 90)
# Set style for Home_btn_temp, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_btn_temp.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_temp.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_temp.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_temp.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_temp.set_style_bg_img_src("B:MicroPython/_menu_tem_90x90.bin", lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_temp.set_style_bg_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_temp.set_style_bg_img_recolor(lv.color_hex(0xe5ff00), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_temp.set_style_bg_img_recolor_opa(216, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_temp.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_temp.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_temp.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_temp.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Home_btn_link
Home_btn_link = lv.btn(Home_cont_menu)
Home_btn_link_label = lv.label(Home_btn_link)
Home_btn_link_label.set_text("")
Home_btn_link_label.set_long_mode(lv.label.LONG.WRAP)
Home_btn_link_label.set_width(lv.pct(100))
Home_btn_link_label.align(lv.ALIGN.CENTER, 0, 0)
Home_btn_link.set_style_pad_all(0, lv.STATE.DEFAULT)
Home_btn_link.set_pos(14, 381)
Home_btn_link.set_size(90, 90)
# Set style for Home_btn_link, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_btn_link.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_link.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_link.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_link.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_link.set_style_bg_img_src("B:MicroPython/_menu_xiaofang_90x90.bin", lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_link.set_style_bg_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_link.set_style_bg_img_recolor_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_link.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_link.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_link.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_link.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Home_btn_safe
Home_btn_safe = lv.btn(Home_cont_menu)
Home_btn_safe_label = lv.label(Home_btn_safe)
Home_btn_safe_label.set_text("")
Home_btn_safe_label.set_long_mode(lv.label.LONG.WRAP)
Home_btn_safe_label.set_width(lv.pct(100))
Home_btn_safe_label.align(lv.ALIGN.CENTER, 0, 0)
Home_btn_safe.set_style_pad_all(0, lv.STATE.DEFAULT)
Home_btn_safe.set_pos(94, 347)
Home_btn_safe.set_size(90, 90)
# Set style for Home_btn_safe, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_btn_safe.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_safe.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_safe.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_safe.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_safe.set_style_bg_img_src("B:MicroPython/_menu_electricity_90x90.bin", lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_safe.set_style_bg_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_safe.set_style_bg_img_recolor_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_safe.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_safe.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_safe.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_safe.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Home_btn_light
Home_btn_light = lv.btn(Home_cont_menu)
Home_btn_light_label = lv.label(Home_btn_light)
Home_btn_light_label.set_text("")
Home_btn_light_label.set_long_mode(lv.label.LONG.WRAP)
Home_btn_light_label.set_width(lv.pct(100))
Home_btn_light_label.align(lv.ALIGN.CENTER, 0, 0)
Home_btn_light.set_style_pad_all(0, lv.STATE.DEFAULT)
Home_btn_light.set_pos(141, 277)
Home_btn_light.set_size(90, 90)
# Set style for Home_btn_light, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_btn_light.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_light.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_light.set_style_radius(5, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_light.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_light.set_style_bg_img_src("B:MicroPython/_menu_light_90x90.bin", lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_light.set_style_bg_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_light.set_style_bg_img_recolor_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_light.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_light.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_light.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_btn_light.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Home_label_monitor
Home_label_monitor = lv.label(Home_cont_menu)
Home_label_monitor.set_text("控制界面")
Home_label_monitor.set_long_mode(lv.label.LONG.WRAP)
Home_label_monitor.set_width(lv.pct(100))
Home_label_monitor.set_pos(8, 229)
Home_label_monitor.set_size(121, 42)
# Set style for Home_label_monitor, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_label_monitor.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_monitor.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_monitor.set_style_text_color(lv.color_hex(0xbbff00), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_monitor.set_style_text_font(test_font("SourceHanSerifSC_Regular", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_monitor.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_monitor.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_monitor.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_monitor.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_monitor.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_monitor.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_monitor.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_monitor.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_monitor.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_label_monitor.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create Home_sw_led2
Home_sw_led2 = lv.switch(Home_cont_menu)
Home_sw_led2.set_pos(280, 202)
Home_sw_led2.set_size(75, 37)
# Set style for Home_sw_led2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_sw_led2.set_style_bg_opa(83, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_sw_led2.set_style_bg_color(lv.color_hex(0xe6e2e6), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_sw_led2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_sw_led2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_sw_led2.set_style_radius(10, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_sw_led2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for Home_sw_led2, Part: lv.PART.INDICATOR, State: lv.STATE.CHECKED.
Home_sw_led2.set_style_bg_opa(255, lv.PART.INDICATOR|lv.STATE.CHECKED)
Home_sw_led2.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.INDICATOR|lv.STATE.CHECKED)
Home_sw_led2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.INDICATOR|lv.STATE.CHECKED)
Home_sw_led2.set_style_border_width(0, lv.PART.INDICATOR|lv.STATE.CHECKED)

# Set style for Home_sw_led2, Part: lv.PART.KNOB, State: lv.STATE.DEFAULT.
Home_sw_led2.set_style_bg_opa(255, lv.PART.KNOB|lv.STATE.DEFAULT)
Home_sw_led2.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.KNOB|lv.STATE.DEFAULT)
Home_sw_led2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.KNOB|lv.STATE.DEFAULT)
Home_sw_led2.set_style_border_width(0, lv.PART.KNOB|lv.STATE.DEFAULT)
Home_sw_led2.set_style_radius(10, lv.PART.KNOB|lv.STATE.DEFAULT)

# Create Home_sw_1
Home_sw_1 = lv.switch(Home_cont_menu)
Home_sw_1.set_pos(279, 252)
Home_sw_1.set_size(75, 37)
# Set style for Home_sw_1, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_sw_1.set_style_bg_opa(83, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_sw_1.set_style_bg_color(lv.color_hex(0xe6e2e6), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_sw_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_sw_1.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_sw_1.set_style_radius(10, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_sw_1.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for Home_sw_1, Part: lv.PART.INDICATOR, State: lv.STATE.CHECKED.
Home_sw_1.set_style_bg_opa(255, lv.PART.INDICATOR|lv.STATE.CHECKED)
Home_sw_1.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.INDICATOR|lv.STATE.CHECKED)
Home_sw_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.INDICATOR|lv.STATE.CHECKED)
Home_sw_1.set_style_border_width(0, lv.PART.INDICATOR|lv.STATE.CHECKED)

# Set style for Home_sw_1, Part: lv.PART.KNOB, State: lv.STATE.DEFAULT.
Home_sw_1.set_style_bg_opa(255, lv.PART.KNOB|lv.STATE.DEFAULT)
Home_sw_1.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.KNOB|lv.STATE.DEFAULT)
Home_sw_1.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.KNOB|lv.STATE.DEFAULT)
Home_sw_1.set_style_border_width(0, lv.PART.KNOB|lv.STATE.DEFAULT)
Home_sw_1.set_style_radius(10, lv.PART.KNOB|lv.STATE.DEFAULT)

# Create Home_sw_2
Home_sw_2 = lv.switch(Home_cont_menu)
Home_sw_2.set_pos(277, 300)
Home_sw_2.set_size(75, 37)
# Set style for Home_sw_2, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_sw_2.set_style_bg_opa(83, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_sw_2.set_style_bg_color(lv.color_hex(0xe6e2e6), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_sw_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_sw_2.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_sw_2.set_style_radius(10, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_sw_2.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for Home_sw_2, Part: lv.PART.INDICATOR, State: lv.STATE.CHECKED.
Home_sw_2.set_style_bg_opa(255, lv.PART.INDICATOR|lv.STATE.CHECKED)
Home_sw_2.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.INDICATOR|lv.STATE.CHECKED)
Home_sw_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.INDICATOR|lv.STATE.CHECKED)
Home_sw_2.set_style_border_width(0, lv.PART.INDICATOR|lv.STATE.CHECKED)

# Set style for Home_sw_2, Part: lv.PART.KNOB, State: lv.STATE.DEFAULT.
Home_sw_2.set_style_bg_opa(255, lv.PART.KNOB|lv.STATE.DEFAULT)
Home_sw_2.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.KNOB|lv.STATE.DEFAULT)
Home_sw_2.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.KNOB|lv.STATE.DEFAULT)
Home_sw_2.set_style_border_width(0, lv.PART.KNOB|lv.STATE.DEFAULT)
Home_sw_2.set_style_radius(10, lv.PART.KNOB|lv.STATE.DEFAULT)

# Create Home_sw_3
Home_sw_3 = lv.switch(Home_cont_menu)
Home_sw_3.set_pos(281, 148)
Home_sw_3.set_size(75, 37)
# Set style for Home_sw_3, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
Home_sw_3.set_style_bg_opa(83, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_sw_3.set_style_bg_color(lv.color_hex(0xe6e2e6), lv.PART.MAIN|lv.STATE.DEFAULT)
Home_sw_3.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_sw_3.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_sw_3.set_style_radius(10, lv.PART.MAIN|lv.STATE.DEFAULT)
Home_sw_3.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for Home_sw_3, Part: lv.PART.INDICATOR, State: lv.STATE.CHECKED.
Home_sw_3.set_style_bg_opa(255, lv.PART.INDICATOR|lv.STATE.CHECKED)
Home_sw_3.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.INDICATOR|lv.STATE.CHECKED)
Home_sw_3.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.INDICATOR|lv.STATE.CHECKED)
Home_sw_3.set_style_border_width(0, lv.PART.INDICATOR|lv.STATE.CHECKED)

# Set style for Home_sw_3, Part: lv.PART.KNOB, State: lv.STATE.DEFAULT.
Home_sw_3.set_style_bg_opa(255, lv.PART.KNOB|lv.STATE.DEFAULT)
Home_sw_3.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.KNOB|lv.STATE.DEFAULT)
Home_sw_3.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.KNOB|lv.STATE.DEFAULT)
Home_sw_3.set_style_border_width(0, lv.PART.KNOB|lv.STATE.DEFAULT)
Home_sw_3.set_style_radius(10, lv.PART.KNOB|lv.STATE.DEFAULT)

Home.update_layout()

def Home_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.SCREEN_LOADED):
        pass
        

    if (code == lv.EVENT.SCREEN_UNLOADED):
        pass
        

Home.add_event_cb(lambda e: Home_event_handler(e), lv.EVENT.ALL, None)

def Home_chart_temp_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        Home_btn_humi_.set_style_text_color(lv.color_hex(0xff0000), 0)
        Home_btn_light_.set_style_text_color(lv.color_hex(0xffffff), 0)
        Home_btn_temp_.set_style_text_color(lv.color_hex(0xffffff), 0)
Home_chart_temp.add_event_cb(lambda e: Home_chart_temp_event_handler(e), lv.EVENT.ALL, None)

def Home_btn_temp__event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        Home_btn_temp_.set_style_text_color(lv.color_hex(0xff0000), 0)
        Home_btn_humi_.set_style_text_color(lv.color_hex(0xffffff), 0)
        Home_btn_light_.set_style_text_color(lv.color_hex(0xffffff), 0)
        

Home_btn_temp_.add_event_cb(lambda e: Home_btn_temp__event_handler(e), lv.EVENT.ALL, None)

def Home_btn_humi__event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        Home_btn_humi_.set_style_text_color(lv.color_hex(0xff0000), 0)
        Home_btn_temp_.set_style_text_color(lv.color_hex(0xffffff), 0)
        Home_btn_light_.set_style_text_color(lv.color_hex(0xffffff), 0)
Home_btn_humi_.add_event_cb(lambda e: Home_btn_humi__event_handler(e), lv.EVENT.ALL, None)

def Home_btn_light__event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        Home_btn_light_.set_style_text_color(lv.color_hex(0xff0000), 0)
        Home_btn_humi_.set_style_text_color(lv.color_hex(0xffffff), 0)
        Home_btn_humi_.set_style_text_color(lv.color_hex(0xffffff), 0)
Home_btn_light_.add_event_cb(lambda e: Home_btn_light__event_handler(e), lv.EVENT.ALL, None)

def Home_btn_menu_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        Home_cont_menu.clear_flag(lv.obj.FLAG.HIDDEN)
        
Home_btn_menu.add_event_cb(lambda e: Home_btn_menu_event_handler(e), lv.EVENT.ALL, None)

def Home_cont_menu_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        Home_cont_menu.add_flag(lv.obj.FLAG.HIDDEN)
        
Home_cont_menu.add_event_cb(lambda e: Home_cont_menu_event_handler(e), lv.EVENT.ALL, None)

def Home_btn_power_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.KEY):
        pass
Home_btn_power.add_event_cb(lambda e: Home_btn_power_event_handler(e), lv.EVENT.ALL, None)

# content from custom.py

# Load the default screen
lv.scr_load(Home)

while SDL.check():
    time.sleep_ms(5)

