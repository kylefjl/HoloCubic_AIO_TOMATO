#include "screen_share_gui.h"
#include "lvgl.h"

lv_obj_t *share_main_scr = NULL;

lv_obj_t *title_label;
lv_obj_t *local_ip_label;
lv_obj_t *local_port_label;
lv_obj_t *info_label;

static lv_style_t default_style;
static lv_style_t label_style;

LV_FONT_DECLARE(lv_font_montserrat_24);

void screen_share_gui_init(void)
{
    share_main_scr = NULL;
    title_label = NULL;
    local_ip_label = NULL;
    local_port_label = NULL;
    info_label = NULL;

    lv_style_init(&default_style);
    lv_style_set_bg_color(&default_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_style_set_bg_color(&default_style, LV_STATE_PRESSED, LV_COLOR_GRAY);
    lv_style_set_bg_color(&default_style, LV_STATE_FOCUSED, LV_COLOR_BLACK);
    lv_style_set_bg_color(&default_style, LV_STATE_FOCUSED | LV_STATE_PRESSED, lv_color_hex(0xf88));
    // 本地的ip地址
    share_main_scr = lv_obj_create(NULL, NULL);
    lv_obj_add_style(share_main_scr, LV_BTN_PART_MAIN, &default_style);
    lv_style_init(&label_style);
    lv_style_set_text_opa(&label_style, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_text_color(&label_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_text_font(&label_style, LV_STATE_DEFAULT, &lv_font_montserrat_24);
}

void display_share_init(void)
{
    lv_obj_t *act_obj = lv_scr_act(); // 获取当前活动页
    if (act_obj == share_main_scr)
        return;
    if (NULL != local_ip_label)
    {
        lv_obj_clean(title_label);
        lv_obj_clean(local_ip_label);
        lv_obj_clean(local_port_label);
        lv_obj_clean(info_label);
    }
    lv_obj_clean(act_obj); // 清空此前页面
    title_label = lv_label_create(share_main_scr, NULL);
    local_ip_label = lv_label_create(share_main_scr, NULL);
    local_port_label = lv_label_create(share_main_scr, NULL);
    info_label = lv_label_create(share_main_scr, NULL);
}

void display_screen_share(const char *title, const char *ip,
                          const char *port, const char *info,
                          lv_scr_load_anim_t anim_type)
{
    display_share_init();

    lv_obj_add_style(title_label, LV_LABEL_PART_MAIN, &label_style);
    lv_label_set_text(title_label, title);
    lv_obj_align(title_label, NULL, LV_ALIGN_OUT_BOTTOM_MID, 0, -220);

    lv_obj_add_style(local_ip_label, LV_LABEL_PART_MAIN, &label_style);
    lv_label_set_text(local_ip_label, ip);
    lv_obj_align(local_ip_label, NULL, LV_ALIGN_OUT_BOTTOM_LEFT, 5, -160);

    lv_obj_add_style(local_port_label, LV_LABEL_PART_MAIN, &label_style);
    lv_label_set_text(local_port_label, port);
    lv_obj_align(local_port_label, NULL, LV_ALIGN_OUT_BOTTOM_LEFT, 5, -120);

    lv_obj_add_style(info_label, LV_LABEL_PART_MAIN, &label_style);
    lv_label_set_text(info_label, info);
    lv_obj_align(info_label, NULL, LV_ALIGN_OUT_BOTTOM_LEFT, 5, -80);

    // lv_scr_load_anim(share_main_scr, anim_type, 300, 300, false);
    lv_scr_load(share_main_scr);
}

void screen_share_gui_del(void)
{

    if (NULL != local_ip_label)
    {
        lv_obj_clean(title_label);
        lv_obj_clean(local_ip_label);
        lv_obj_clean(local_port_label);
        lv_obj_clean(info_label);
        title_label = NULL;
        local_ip_label = NULL;
        local_port_label = NULL;
        info_label = NULL;
    }

    if (NULL != share_main_scr)
    {
        lv_obj_clean(share_main_scr); // 清空此前页面
        share_main_scr = NULL;
    }

    // 手动清除样式，防止内存泄漏
    // lv_style_reset(&default_style);
    // lv_style_reset(&label_style);
}