#include "tomato_gui.h"
#include <stdio.h>
#include "driver/lv_port_indev.h"
#include "lvgl.h"

LV_FONT_DECLARE(lv_font_ibmplex_115);
LV_FONT_DECLARE(lv_font_ibmplex_64);
LV_FONT_DECLARE(lv_font_ibmplex_200);
LV_FONT_DECLARE(tomato_chFont_20);


#define PIC_FILENAME_MAX_LEN 100

static lv_style_t *tomato_scr;
static lv_obj_t *clockLabel_1 = NULL, *clockLabel_2 = NULL;
static lv_style_t default_style;
static lv_style_t name_style;
static lv_style_t time_style;
static lv_style_t chFont_style;
static lv_obj_t *chart, *txtLabel;
static lv_style_t numberSmall_style;
static lv_style_t numberBig_style;



void tomato_gui_init(void) // style init
{
    if (tomato_scr == lv_scr_act())
        return;
    tomato_scr = lv_obj_create(NULL, NULL);

    lv_style_init(&default_style);//背景
    lv_style_set_bg_color(&default_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_style_set_bg_color(&default_style, LV_STATE_PRESSED, LV_COLOR_GRAY);
    lv_style_set_bg_color(&default_style, LV_STATE_FOCUSED, LV_COLOR_BLACK);
    lv_style_set_bg_color(&default_style, LV_STATE_FOCUSED | LV_STATE_PRESSED, lv_color_hex(0xf88));
    lv_obj_add_style(tomato_scr, LV_BTN_PART_MAIN, &default_style);

    lv_style_init(&chFont_style);
    lv_style_set_text_opa(&chFont_style, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_text_color(&chFont_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_text_font(&chFont_style, LV_STATE_DEFAULT, &tomato_chFont_20);


    lv_style_init(&numberSmall_style);
    lv_style_set_text_opa(&numberSmall_style, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_text_color(&numberSmall_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_text_font(&numberSmall_style, LV_STATE_DEFAULT, &lv_font_ibmplex_64);
    lv_style_init(&numberBig_style);
    lv_style_set_text_opa(&numberBig_style, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_text_color(&numberBig_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_text_font(&numberBig_style, LV_STATE_DEFAULT, &lv_font_ibmplex_200);
}

void UIInit()
{ // ui init
    if (tomato_scr == NULL)
    {
        tomato_scr = lv_obj_create(NULL, NULL);
    }
    if (tomato_scr == lv_scr_act())
        return;
    else
        lv_obj_clean(lv_scr_act());

    txtLabel = lv_label_create(tomato_scr, NULL);
    lv_obj_add_style(txtLabel, LV_LABEL_PART_MAIN, &chFont_style);
    lv_label_set_recolor(txtLabel, true);
    lv_label_set_text(txtLabel, "专注中");
    lv_obj_set_pos(txtLabel, 45, 190);


    clockLabel_1 = lv_label_create(tomato_scr, NULL);//分钟
    lv_obj_add_style(clockLabel_1, LV_LABEL_PART_MAIN, &numberBig_style);
    lv_label_set_recolor(clockLabel_1, true);
    lv_label_set_text_fmt(clockLabel_1, "#ffa500 %02d# ", 25);
    lv_obj_set_pos(clockLabel_1, 30, 40);
    clockLabel_2 = lv_label_create(tomato_scr, NULL);
    lv_obj_add_style(clockLabel_2, LV_LABEL_PART_MAIN, &numberSmall_style);
    lv_label_set_recolor(clockLabel_2, true);
    lv_label_set_text_fmt(clockLabel_2, "%02d", 00);
    lv_obj_align(clockLabel_2, clockLabel_1, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    lv_scr_load(tomato_scr);
}

void display_tomato(struct TimeStr t,int mode)
{
    UIInit();
    lv_label_set_text_fmt(clockLabel_1, "#ffa500 %02d#", t.minute); //#ffa500
    lv_label_set_text_fmt(clockLabel_2, "%02d", t.second);
    if(mode==0)
        lv_label_set_text(txtLabel, "专注中");
    else
    {
        lv_label_set_text(txtLabel, "休息中");
    }

}

void tomato_gui_del(void)
{
    if (NULL != tomato_scr)
    {
        lv_obj_clean(tomato_scr);
        tomato_scr = NULL;
    }
    // 手动清除样式，防止内存泄漏
    // lv_style_reset(&default_style);
}