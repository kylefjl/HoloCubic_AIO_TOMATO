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
static lv_style_t numberSmall_style;
static lv_style_t numberBig_style;
static lv_obj_t *together_scr = NULL;
static lv_obj_t* la_name  = NULL;
static lv_obj_t* la_sec  = NULL;
static lv_obj_t* la_day  = NULL;
static lv_obj_t *clockLabel_1 = NULL, *clockLabel_2 = NULL;
static lv_obj_t* img_we  = NULL;
// static lv_obj_t* img_heart  = NULL;
static lv_obj_t* img_bottom_left  = NULL;
static lv_obj_t* img_photo_frame  = NULL;
// static lv_obj_t* img_top_left  = NULL;
// static lv_obj_t* img_top_right  = NULL;
static lv_obj_t* img_rainbow  = NULL;
static lv_obj_t* img_flowers_5  = NULL;
static lv_obj_t* img_love_7  = NULL;
static lv_obj_t* img_love  = NULL;
static lv_obj_t* img_note  = NULL;
static lv_obj_t* img_twinkle  = NULL;
static lv_obj_t* img_cute_emoji  = NULL;

const int cuteEmojisNum = 7;
struct Gif* cuteEmojis[] = {
    &gif_obj_fanli1, &gif_obj_fanli2, 
    &gif_obj_pp1, &gif_obj_pp2, &gif_obj_pp3,
    &gif_obj_yangbaobao3, &gif_obj_yangbaobao4,
};


const int our_photo_num = 3;
const void *our_photo[] = {&we_0,&we_1,&we_2};

void together_gui_init(void) // style init
{ 
    if(together_scr == lv_scr_act())
        return;
    together_scr = lv_obj_create(NULL, NULL);

    lv_style_init(&default_style);
    lv_style_set_bg_color(&default_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_style_set_bg_color(&default_style, LV_STATE_PRESSED, LV_COLOR_GRAY);
    lv_style_set_bg_color(&default_style, LV_STATE_FOCUSED, LV_COLOR_BLACK);
    lv_style_set_bg_color(&default_style, LV_STATE_FOCUSED | LV_STATE_PRESSED, lv_color_hex(0xf88));
    lv_obj_add_style(together_scr, LV_BTN_PART_MAIN, &default_style);

  	// lv_style_init(&name_style);
    // lv_style_set_text_opa(&name_style, LV_STATE_DEFAULT, LV_OPA_COVER);
    // lv_style_set_text_color(&name_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    // lv_style_set_text_font(&name_style, LV_STATE_DEFAULT, &lcNameFont);

	lv_style_init(&time_style);
    lv_style_set_text_opa(&time_style, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_text_color(&time_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_style_set_text_font(&time_style, LV_STATE_DEFAULT, &lcTimeFont);
    lv_style_init(&numberSmall_style);
    lv_style_set_text_opa(&numberSmall_style, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_text_color(&numberSmall_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_text_font(&numberSmall_style, LV_STATE_DEFAULT, &lv_font_ibmplex_64);
    lv_style_init(&numberBig_style);
    lv_style_set_text_opa(&numberBig_style, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_text_color(&numberBig_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_text_font(&numberBig_style, LV_STATE_DEFAULT, &lv_font_ibmplex_115);

}

void UIInit(){ // ui init
    if(together_scr == NULL) {
        together_scr = lv_obj_create(NULL, NULL);
    }
    if(together_scr == lv_scr_act())
        return;
    else
        lv_obj_clean(lv_scr_act());
    
	// la_name = lv_label_create(together_scr, NULL);
    // lv_obj_add_style(la_name, LV_LABEL_PART_MAIN, &name_style);
    // lv_label_set_recolor(la_name , true);
    // lv_label_set_text_fmt(la_name , "#4246dd LC#   #ffae95 ZY#");//#ffae95 ZY#     #4246dd LC#
	// // lv_obj_align(la_name, NULL, LV_ALIGN_IN_TOP_LEFT, 0, LV_DPI / 20);
    // lv_obj_set_pos(la_name, 40, 20);

    // img_flowers_5= lv_img_create(together_scr, NULL);
	// lv_obj_align(img_flowers_5, la_name, LV_ALIGN_OUT_BOTTOM_MID, 0, -5);
    // lv_img_set_src(img_flowers_5, &flowers_5);

    // img_note= lv_img_create(together_scr, NULL);
	// lv_obj_align(img_note, img_flowers_5, LV_ALIGN_OUT_BOTTOM_MID, -65, -5);
    // lv_img_set_src(img_note, &note);

	// la_day = lv_label_create(together_scr, NULL);
	// lv_obj_add_style(la_day, LV_LABEL_PART_MAIN, &time_style);
    // lv_label_set_recolor(la_day , true);
    // lv_label_set_text_fmt(la_day , "已营业%04d天", 1439);
	// lv_obj_align(la_day, img_note, LV_ALIGN_IN_LEFT_MID, 35, 2);

	// la_sec = lv_label_create(together_scr, NULL);
	// lv_obj_add_style(la_sec, LV_LABEL_PART_MAIN, &time_style);
    // lv_label_set_recolor(la_sec , true);
    // lv_label_set_text_fmt(la_sec , "%10d秒", 123904400);
	// lv_obj_align(la_sec, la_day, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    clockLabel_1 = lv_label_create(together_scr, NULL);
    lv_obj_add_style(clockLabel_1, LV_LABEL_PART_MAIN, &numberBig_style);
    lv_label_set_recolor(clockLabel_1, true);
    lv_label_set_text_fmt(clockLabel_1, "#ffa500 %02d# ", 25);
     lv_obj_set_pos(clockLabel_1, 50, 80);
    clockLabel_2 = lv_label_create(together_scr, NULL);
    lv_obj_add_style(clockLabel_2, LV_LABEL_PART_MAIN, &numberSmall_style);
    lv_label_set_recolor(clockLabel_2, true);
    lv_label_set_text_fmt(clockLabel_2, "%02d", 00);
    lv_obj_align(clockLabel_2, clockLabel_1, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    
  
// 	img_heart = lv_img_create(together_scr, NULL);
//    // lv_img_set_src(img_heart, heart1.frames[0]);
// 	lv_obj_align(img_heart, la_name, LV_ALIGN_IN_TOP_MID, 0, LV_DPI / 20);
//     lv_img_set_src(img_heart, &transparent);

    // img_bottom_left= lv_img_create(together_scr, NULL);
	// lv_obj_align(img_bottom_left, together_scr, LV_ALIGN_IN_BOTTOM_LEFT, 0, -25);


    // img_love_7= lv_img_create(together_scr, NULL);
	// lv_obj_align(img_love_7, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 0);

    // img_love= lv_img_create(together_scr, NULL);
	// // lv_obj_align(img_love, NULL, LV_ALIGN_IN_TOP_LEFT, 10, -8);
    // // lv_obj_set_pos(img_love, 190, 90);
	// lv_obj_align(img_love, la_name, LV_ALIGN_CENTER, 16, 0);

    // img_rainbow = lv_img_create(together_scr, NULL);
	// lv_obj_align(img_rainbow, la_name, LV_ALIGN_OUT_TOP_RIGHT, 60, 25);
    // lv_img_set_src(img_rainbow, &rainbow);

    // // img_top_left= lv_img_create(together_scr, NULL);
	// // lv_obj_align(img_top_left, together_scr, LV_ALIGN_IN_TOP_LEFT, 0, 0);

    // // img_top_right= lv_img_create(together_scr, NULL);
	// // lv_obj_align(img_top_right, together_scr, LV_ALIGN_IN_TOP_RIGHT, 0, -25);

    // img_we = lv_img_create(together_scr, NULL);
	// lv_obj_align(img_we, together_scr, LV_ALIGN_IN_BOTTOM_RIGHT, 10, -50);
    // lv_img_set_src(img_we, our_photo[our_photo_num-1]);
    
    // img_photo_frame= lv_img_create(together_scr, NULL);
	// lv_obj_align(img_photo_frame, img_we, LV_ALIGN_CENTER, 2, -15);
    // lv_img_set_src(img_photo_frame, &photo_frame);

    // img_twinkle = lv_img_create(together_scr, NULL);
	// lv_obj_align(img_twinkle, img_note, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 5);

    // img_cute_emoji = lv_img_create(together_scr, NULL);
	// lv_obj_align(img_cute_emoji, img_photo_frame, LV_ALIGN_OUT_LEFT_MID, -10, -20);

  //  lv_scr_load_anim(together_scr, LV_SCR_LOAD_ANIM_NONE, 300, 300, false);
     // or   
    lv_scr_load(together_scr);
}

void displayGif(lv_obj_t* img, struct Gif* gif){
    uint32_t t = lv_tick_get();
    if(t - gif->last_tick >= gif->speed){
        lv_img_set_src(img, gif->frames[++gif->curr_frame%gif->frame_num]);
        gif->last_tick = t;
    }
}

void displayPic(lv_obj_t* img, struct Gif* gif){
    lv_img_set_src(img, gif->frames[++gif->curr_frame%gif->frame_num]);
}

void stopGif(lv_obj_t* img){
    lv_img_set_src(img, &transparent);
}

void display_time_ani(long long networkTime, uint32_t t){
    // static unsigned int last_tick = 0;
    // uint32_t now = lv_tick_get();
    // if(now - last_tick >= 1000){
    //     long long totalSec = (networkTime + lv_tick_get() - t - fall_in_love_time_stamp)/1000;
    //     lv_label_set_text_fmt(la_sec , "%10d秒", totalSec);
    //     last_tick = now;
    //     static unsigned int totalDay = 1461;
    //     unsigned int day = totalSec/86400;
    //     if(totalDay != day){
    //          totalDay = day;
    //          lv_label_set_text_fmt(la_day , "已营业%04d天", totalDay);
    //     }
    // }t
    // lv_label_set_text_fmt(clockLabel_1, "%02d#ffa500 %02d#", t.hour, t.minute);
    // lv_label_set_text_fmt(clockLabel_2, "%02d", t.second);
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
    if ( t - last_tick > 30000) {
        static unsigned short page = 0;
        last_tick = t;
        lv_img_set_src(img_we, our_photo[page++%our_photo_num]);
    }
    
}

void display_cute_emoji()
{
    static long long last_tick = 0;
    static struct Gif* currGif = NULL;
    uint32_t t = lv_tick_get();
    if (currGif == NULL || t - last_tick > cute_emoji_change_interval) {
        last_tick = t;
        currGif = cuteEmojis[t%cuteEmojisNum];
    }
    
    displayGif(img_cute_emoji, currGif);
}

void display_together(long long networkTime,struct TimeStr t) {
    UIInit();
    // displayGif(img_bottom_left, &gif_obj_bottom_left);
    // // displayGif(img_top_left, &gif_obj_top_left);
    // // displayGif(img_top_right, &gif_obj_top_right);
    // displayGif(img_love_7, &gif_obj_love_7);
    // displayGif(img_love, &gif_obj_love);
    // displayGif(img_twinkle, &gif_obj_twinkle);
   // display_time_ani(networkTime, t);
    // display_cute_emoji();
    // display_our_photo();
    lv_label_set_text_fmt(clockLabel_1, "#ffa500 %02d#", t.minute);//#ffa500 
    lv_label_set_text_fmt(clockLabel_2, "%02d", t.second);
}


void together_gui_del(void)
{
    
    
    if (NULL != la_name) {
        lv_obj_clean( la_name );
        la_name = NULL;
    }
    if (NULL != la_sec) {
        lv_obj_clean( la_sec );
       la_sec  = NULL;
    }
    if (NULL != la_day) {
        lv_obj_clean( la_day );
       la_day  = NULL;
    }
        if (NULL != la_sec) {
        lv_obj_clean( la_sec );
       la_sec  = NULL;
    }
    if (NULL != la_day) {
        lv_obj_clean( la_day );
       la_day  = NULL;
    }
    if (NULL != img_we) {
        lv_obj_clean( img_we );
       img_we  = NULL;
    }
    // if (NULL != img_heart) {
    //     lv_obj_clean( img_heart );
    //     img_heart = NULL;
    // }
    if (NULL != img_bottom_left) {
        lv_obj_clean( img_bottom_left );
        img_bottom_left = NULL;
    }
    if (NULL != img_photo_frame) {
        lv_obj_clean( img_photo_frame );
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
    if (NULL != img_rainbow) {
        lv_obj_clean( img_rainbow );
        img_rainbow = NULL;
    }
    if (NULL != img_flowers_5) {
        lv_obj_clean( img_flowers_5 );
        img_flowers_5 = NULL;
    }
    if (NULL != img_love_7) {
        lv_obj_clean( img_love_7 );
        img_love_7 = NULL;
    }
    if (NULL != img_love) {
        lv_obj_clean( img_love );
        img_love = NULL;
    }
    if (NULL != img_note) {
        lv_obj_clean( img_note );
        img_note = NULL;
    }

    if (NULL != together_scr) {
        lv_obj_clean( together_scr );
       together_scr  = NULL;
    }
    // 手动清除样式，防止内存泄漏
    // lv_style_reset(&default_style);
}