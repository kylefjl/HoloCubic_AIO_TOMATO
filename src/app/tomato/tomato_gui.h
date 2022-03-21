#ifndef APP_TOMATO_GUI_H
#define APP_TOMATO_GUI_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "lvgl.h"
#define ANIEND                      \
    while (lv_anim_count_running()) \
        lv_task_handler(); //等待动画完成

    void tomato_gui_init(void);
    void display_tomato(const char *cur_ver, const char *new_ver, lv_scr_load_anim_t anim_type);
    void tomato_gui_del(void);

#ifdef __cplusplus
} /* extern "C" */
#endif


#ifdef __cplusplus
extern "C"
{
#endif

#include "lvgl.h"
    extern const lv_img_dsc_t app_tomato;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif