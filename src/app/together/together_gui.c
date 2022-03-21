#include "together_gui.h"
#include <stdio.h>
#include "driver/lv_port_indev.h"
#include "lvgl.h"
#include "gif/bottom_left.h"
#include "gif/love_7.h"
#include "gif/love.h"
#include "gif/twinkle.h"
#include "gif/fanli1.h"
#include "gif/fanli2.h"
#include "gif/pp1.h"
#include "gif/pp2.h"
#include "gif/pp3.h"
#include "gif/yangbaobao3.h"
#include "gif/yangbaobao4.h"
LV_FONT_DECLARE(lv_font_ibmplex_115);
LV_FONT_DECLARE(lv_font_ibmplex_64);
LV_FONT_DECLARE(lv_font_ibmplex_200);
LV_FONT_DECLARE(tomato_chFont_20);
LV_FONT_DECLARE(lcNameFont);
LV_FONT_DECLARE(lcTimeFont);
LV_IMG_DECLARE(we)
LV_IMG_DECLARE(rainbow)
LV_IMG_DECLARE(flowers_5)
LV_IMG_DECLARE(note)
LV_IMG_DECLARE(transparent)
LV_IMG_DECLARE(photo_frame)
LV_IMG_DECLARE(we_0)
LV_IMG_DECLARE(we_1)
LV_IMG_DECLARE(we_2)

#define PIC_FILENAME_MAX_LEN 100

const long long fall_in_love_time_stamp = 1523113200000;
const long long cute_emoji_change_interval = 16000;

static lv_style_t default_style;
static lv_style_t name_style;
static lv_style_t time_style;
static lv_style_t chFont_style;
static lv_obj_t *chart, *txtLabel;
static lv_style_t numberSmall_style;
static lv_style_t numberBig_style;
static lv_obj_t *together_scr = NULL;
static lv_obj_t *la_name = NULL;
static lv_obj_t *la_sec = NULL;
static lv_obj_t *la_day = NULL;
static lv_obj_t *clockLabel_1 = NULL, *clockLabel_2 = NULL;
static lv_obj_t *img_we = NULL;
// static lv_obj_t* img_heart  = NULL;
static lv_obj_t *img_bottom_left = NULL;
static lv_obj_t *img_photo_frame = NULL;
// static lv_obj_t* img_top_left  = NULL;
// static lv_obj_t* img_top_right  = NULL;
static lv_obj_t *img_rainbow = NULL;
static lv_obj_t *img_flowers_5 = NULL;
static lv_obj_t *img_love_7 = NULL;
static lv_obj_t *img_love = NULL;
static lv_obj_t *img_note = NULL;
static lv_obj_t *img_twinkle = NULL;
static lv_obj_t *img_cute_emoji = NULL;


const int cuteEmojisNum = 7;
struct Gif *cuteEmojis[] = {
    &gif_obj_fanli1,
    &gif_obj_fanli2,
    &gif_obj_pp1,
    &gif_obj_pp2,
    &gif_obj_pp3,
    &gif_obj_yangbaobao3,
    &gif_obj_yangbaobao4,
};

const int our_photo_num = 3;
const void *our_photo[] = {&we_0, &we_1, &we_2};

void together_gui_init(void) // style init
{
    if (together_scr == lv_scr_act())
        return;
    together_scr = lv_obj_create(NULL, NULL);

    lv_style_init(&default_style);
    lv_style_set_bg_color(&default_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_style_set_bg_color(&default_style, LV_STATE_PRESSED, LV_COLOR_GRAY);
    lv_style_set_bg_color(&default_style, LV_STATE_FOCUSED, LV_COLOR_BLACK);
    lv_style_set_bg_color(&default_style, LV_STATE_FOCUSED | LV_STATE_PRESSED, lv_color_hex(0xf88));
    lv_obj_add_style(together_scr, LV_BTN_PART_MAIN, &default_style);

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
    if (together_scr == NULL)
    {
        together_scr = lv_obj_create(NULL, NULL);
    }
    if (together_scr == lv_scr_act())
        return;
    else
        lv_obj_clean(lv_scr_act());

    // chFont_style = lv_label_create(together_scr, NULL);
    // lv_obj_add_style(chFont_style, LV_LABEL_PART_MAIN, &chFont_style);
    // lv_label_set_recolor(chFont_style, true); //先得使能文本重绘色功能
    //  lv_label_set_text(chFont_style, "专注中");
    // lv_obj_set_pos(chFont_style, 30, 120);

    txtLabel = lv_label_create(together_scr, NULL);
    lv_obj_add_style(txtLabel, LV_LABEL_PART_MAIN, &chFont_style);
    lv_label_set_recolor(txtLabel, true);
    lv_label_set_text(txtLabel, "专注中");
    lv_obj_set_pos(txtLabel, 45, 190);

    // lv_obj_add_style(title_label, LV_LABEL_PART_MAIN, &title_style);
    // lv_label_set_recolor(title_label, true); //先得使能文本重绘色功能
    // lv_label_set_text(title_label, "#00ff00 All\tin\tone#");
    // lv_obj_align(title_label, NULL, LV_ALIGN_OUT_BOTTOM_MID, 0, -220);



    clockLabel_1 = lv_label_create(together_scr, NULL);
    lv_obj_add_style(clockLabel_1, LV_LABEL_PART_MAIN, &numberBig_style);
    lv_label_set_recolor(clockLabel_1, true);
    lv_label_set_text_fmt(clockLabel_1, "#ffa500 %02d# ", 25);
    lv_obj_set_pos(clockLabel_1, 30, 40);
    clockLabel_2 = lv_label_create(together_scr, NULL);
    lv_obj_add_style(clockLabel_2, LV_LABEL_PART_MAIN, &numberSmall_style);
    lv_label_set_recolor(clockLabel_2, true);
    lv_label_set_text_fmt(clockLabel_2, "%02d", 00);
    lv_obj_align(clockLabel_2, clockLabel_1, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    lv_scr_load(together_scr);
}

void displayGif(lv_obj_t *img, struct Gif *gif)
{
    uint32_t t = lv_tick_get();
    if (t - gif->last_tick >= gif->speed)
    {
        lv_img_set_src(img, gif->frames[++gif->curr_frame % gif->frame_num]);
        gif->last_tick = t;
    }
}

void displayPic(lv_obj_t *img, struct Gif *gif)
{
    lv_img_set_src(img, gif->frames[++gif->curr_frame % gif->frame_num]);
}

void stopGif(lv_obj_t *img)
{
    lv_img_set_src(img, &transparent);
}

void display_time_ani(long long networkTime, uint32_t t)
{

}

void display_us(const char *file_name)
{
    char lv_file_name[PIC_FILENAME_MAX_LEN] = {0};
    sprintf(lv_file_name, "S:%s", file_name);
    lv_img_set_src(img_we, lv_file_name);
}

void display_our_photo()
{
    static long long last_tick = 0;
    uint32_t t = lv_tick_get();
    if (t - last_tick > 30000)
    {
        static unsigned short page = 0;
        last_tick = t;
        lv_img_set_src(img_we, our_photo[page++ % our_photo_num]);
    }
}

void display_cute_emoji()
{
    static long long last_tick = 0;
    static struct Gif *currGif = NULL;
    uint32_t t = lv_tick_get();
    if (currGif == NULL || t - last_tick > cute_emoji_change_interval)
    {
        last_tick = t;
        currGif = cuteEmojis[t % cuteEmojisNum];
    }

    displayGif(img_cute_emoji, currGif);
}

void display_together(struct TimeStr t,int mode)
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

void together_gui_del(void)
{

    if (NULL != la_name)
    {
        lv_obj_clean(la_name);
        la_name = NULL;
    }
    if (NULL != la_sec)
    {
        lv_obj_clean(la_sec);
        la_sec = NULL;
    }
    if (NULL != la_day)
    {
        lv_obj_clean(la_day);
        la_day = NULL;
    }
    if (NULL != la_sec)
    {
        lv_obj_clean(la_sec);
        la_sec = NULL;
    }
    if (NULL != la_day)
    {
        lv_obj_clean(la_day);
        la_day = NULL;
    }
    if (NULL != img_we)
    {
        lv_obj_clean(img_we);
        img_we = NULL;
    }
    // if (NULL != img_heart) {
    //     lv_obj_clean( img_heart );
    //     img_heart = NULL;
    // }
    if (NULL != img_bottom_left)
    {
        lv_obj_clean(img_bottom_left);
        img_bottom_left = NULL;
    }
    if (NULL != img_photo_frame)
    {
        lv_obj_clean(img_photo_frame);
        img_photo_frame = NULL;
    }
    // if (NULL != img_top_left) {
    //     lv_obj_clean( img_top_left );
    //     img_top_left = NULL;
    // }
    // if (NULL != img_top_right) {
    //     lv_obj_clean( img_top_right );
    //     img_top_right = NULL;
    // }
    if (NULL != img_rainbow)
    {
        lv_obj_clean(img_rainbow);
        img_rainbow = NULL;
    }
    if (NULL != img_flowers_5)
    {
        lv_obj_clean(img_flowers_5);
        img_flowers_5 = NULL;
    }
    if (NULL != img_love_7)
    {
        lv_obj_clean(img_love_7);
        img_love_7 = NULL;
    }
    if (NULL != img_love)
    {
        lv_obj_clean(img_love);
        img_love = NULL;
    }
    if (NULL != img_note)
    {
        lv_obj_clean(img_note);
        img_note = NULL;
    }

    if (NULL != together_scr)
    {
        lv_obj_clean(together_scr);
        together_scr = NULL;
    }
    // 手动清除样式，防止内存泄漏
    // lv_style_reset(&default_style);
}