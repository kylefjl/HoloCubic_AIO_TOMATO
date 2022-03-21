#include "app_controller_gui.h"
// #include "lvgl.h"

// 必须定义为全局或者静态
static lv_obj_t *app_scr = NULL;
static lv_obj_t *pre_app_image = NULL;
static lv_obj_t *pre_app_name = NULL;
static lv_obj_t *now_app_image = NULL;
static lv_obj_t *now_app_name = NULL;
const void *pre_img_path = NULL;

static lv_style_t default_style;
static lv_style_t app_name_style;

LV_FONT_DECLARE(lv_font_montserrat_24);

void app_control_gui_init(void)
{
    if (NULL != app_scr)
    {
        lv_obj_clean(app_scr);
        app_scr = NULL;
    }

    lv_style_init(&default_style);
    lv_style_set_bg_color(&default_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_style_set_bg_color(&default_style, LV_STATE_PRESSED, LV_COLOR_GRAY);
    lv_style_set_bg_color(&default_style, LV_STATE_FOCUSED, LV_COLOR_BLACK);
    lv_style_set_bg_color(&default_style, LV_STATE_FOCUSED | LV_STATE_PRESSED, lv_color_hex(0xf88));

    lv_style_init(&app_name_style);
    lv_style_set_text_opa(&app_name_style, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_text_color(&app_name_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_text_font(&app_name_style, LV_STATE_DEFAULT, &lv_font_montserrat_24);

    // APP图标页
    app_scr = lv_obj_create(NULL, NULL);
    lv_obj_add_style(app_scr, LV_BTN_PART_MAIN, &default_style);
}

void app_control_gui_release(void)
{
    if (NULL != app_scr)
    {
        lv_obj_clean(app_scr);
        app_scr = NULL;
    }
}

void display_app_scr_init(const void *src_img_path, const char *app_name)
{
    lv_obj_t *act_obj = lv_scr_act(); // 获取当前活动页
    if (act_obj == app_scr)
    {
        // 防止一些不适用lvgl的APP退出 造成画面在无其他动作情况下无法绘制更新
        lv_scr_load_anim(app_scr, LV_SCR_LOAD_ANIM_NONE, 300, 300, false);
        return;
    }

    lv_obj_clean(act_obj); // 清空此前页面
    pre_app_image = lv_img_create(app_scr, NULL);
    lv_img_set_src(pre_app_image, src_img_path);
    pre_img_path = src_img_path;

    lv_obj_align(pre_app_image, NULL, LV_ALIGN_CENTER, 0, -20);

    // 添加APP的名字
    pre_app_name = lv_label_create(app_scr, NULL);
    lv_obj_add_style(pre_app_name, LV_LABEL_PART_MAIN, &app_name_style);
    // lv_label_set_recolor(pre_app_name, true); //先得使能文本重绘色功能
    lv_label_set_text(pre_app_name, app_name);
    lv_obj_align(pre_app_name, pre_app_image, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

    lv_scr_load_anim(app_scr, LV_SCR_LOAD_ANIM_NONE, 300, 300, false);
    // lv_scr_load(app_scr);    // 加载屏幕
}

void app_control_display_scr(const void *src_img, const char *app_name, lv_scr_load_anim_t anim_type, bool force)
{
    // force为是否强制刷新页面 true为强制刷新
    if (true == force)
    {
        display_app_scr_init(src_img, app_name);
        return;
    }

    if (src_img == pre_img_path)
    {
        return;
    }

    pre_img_path = src_img;
    int now_start_x;
    int now_end_x;
    int old_start_x;
    int old_end_x;

    if (LV_SCR_LOAD_ANIM_MOVE_LEFT == anim_type)
    {
        now_start_x = -128;
        now_end_x = 56;
        old_start_x = 56;
        old_end_x = 240;
    }
    else
    {
        now_start_x = 240;
        now_end_x = 56;
        old_start_x = 56;
        old_end_x = -128;
    }

    now_app_image = lv_img_create(app_scr, NULL);
    lv_img_set_src(now_app_image, src_img);
    lv_obj_align(now_app_image, NULL, LV_ALIGN_CENTER, 0, -20);
    // 添加APP的名字
    now_app_name = lv_label_create(app_scr, NULL);
    lv_obj_add_style(now_app_name, LV_LABEL_PART_MAIN, &app_name_style);
    // lv_label_set_recolor(now_app_name, true); //先得使能文本重绘色功能
    lv_label_set_text(now_app_name, app_name);
    // 删除原先的APP name
    lv_obj_del(pre_app_name);
    pre_app_name = now_app_name;
    lv_obj_align(now_app_name, now_app_image, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

    lv_anim_path_t path;
    lv_anim_path_init(&path);
    /*
    lv_anim_path_linear lv_anim_path_bounce
    lv_anim_path_overshoot lv_anim_path_ease_out
    lv_anim_path_step
    */
    lv_anim_path_set_cb(&path, lv_anim_path_ease_out);
    /*Optional for custom functions*/
    // lv_anim_path_set_user_data(&path, &foo);

    lv_anim_t now_app;
    lv_anim_init(&now_app);
    lv_anim_set_exec_cb(&now_app, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_var(&now_app, now_app_image);
    lv_anim_set_values(&now_app, now_start_x, now_end_x);
    uint32_t duration = lv_anim_speed_to_time(300, now_start_x, now_end_x); // 计算时间
    lv_anim_set_time(&now_app, duration);
    lv_anim_set_path(&now_app, &path); // Default is linear

    lv_anim_t pre_app;
    lv_anim_init(&pre_app);
    lv_anim_set_exec_cb(&pre_app, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_var(&pre_app, pre_app_image);
    lv_anim_set_values(&pre_app, old_start_x, old_end_x);
    duration = lv_anim_speed_to_time(300, old_start_x, old_end_x); // 计算时间
    lv_anim_set_time(&pre_app, duration);
    lv_anim_set_path(&pre_app, &path); // Default is linear

    lv_anim_start(&now_app);
    lv_anim_start(&pre_app);
    ANIEND

    lv_obj_del(pre_app_image); // 删除原先的图像
    pre_app_image = now_app_image;
}