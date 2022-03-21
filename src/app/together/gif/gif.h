#ifndef GIF_H
#define GIF_H

#ifdef LV_CONF_INCLUDE_SIMPLE
#include <lvgl.h>
#else
#include "../../../lvgl/lvgl.h"
#endif


#ifdef __cplusplus
extern "C" {
#endif

typedef void (*my_loop_func)(void);

struct Gif
{
    /* data */
    const void** frames;
    short frame_num;
    short speed; // ms
    unsigned int last_tick;
    unsigned short curr_frame;
};

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*GIF_H*/
