#include "together.h"
#include "together_gui.h"
#include "sys/app_controller.h"
#include "common.h"
#include "ESP32Time.h"
#define TOGETHER_APP_NAME "Tomato"

// 动态数据，APP的生命周期结束也需要释放它
struct TogetherAppRunData
{
    long long time_start; //开始毫秒数
    long long time_ms;    //毫秒数
    TimeStr t;            //时间结构体
    TimeStr t_start;      //倒计时结构体
    RgbConfig rgb_cfg;    //灯效
    bool rgb_fast;        //使能
    bool rgb_fast_update; //标志位
    RgbParam rgb_setting; // rgb参数
    int time_mode;        //倒计时种类
    uint8_t switch_count; //切换次数，用于消抖
};

// 常驻数据，可以不随APP的生命周期而释放或删除
struct TogetherAppForeverData
{
};

static bool hadOpened = false;

// 保存APP运行时的参数信息，理论上关闭APP时推荐在 xxx_exit_callback 中释放掉
static TogetherAppRunData *run_data = NULL;

// 当然你也可以添加恒定在内存中的少量变量（退出时不用释放，实现第二次启动时可以读取）
// 考虑到所有的APP公用内存，尽量减少 forever_data 的数据占用
static TogetherAppForeverData forever_data;

static int together_init(void)
{
    // 初始化运行时的参数
    together_gui_init();
    // 初始化运行时参数
    run_data = (TogetherAppRunData *)calloc(1, sizeof(TogetherAppRunData));
    run_data->time_start = millis();
    run_data->t_start.second = 59; //专注时间，初始化一次
    run_data->t_start.minute = 24;
    run_data->t = run_data->t_start;
    run_data->rgb_fast = 0;
    run_data->rgb_fast_update = 0;
    run_data->switch_count = 0;

    run_data->rgb_cfg.mode = 1;
    run_data->rgb_cfg.min_value_0 = 1;
    run_data->rgb_cfg.min_value_1 = 32;
    run_data->rgb_cfg.min_value_2 = 255;
    run_data->rgb_cfg.max_value_0 = 255;
    run_data->rgb_cfg.max_value_1 = 255;
    run_data->rgb_cfg.max_value_2 = 255;
    run_data->rgb_cfg.step_0 = 1;
    run_data->rgb_cfg.step_1 = 1;
    run_data->rgb_cfg.step_2 = 1;
    run_data->rgb_cfg.min_brightness = 0.15;
    run_data->rgb_cfg.max_brightness = 0.25;
    run_data->rgb_cfg.brightness_step = 0.001;
    run_data->rgb_cfg.time = 30;

    run_data->rgb_setting = {LED_MODE_HSV,
                             run_data->rgb_cfg.min_value_0, run_data->rgb_cfg.min_value_1, run_data->rgb_cfg.min_value_2,
                             run_data->rgb_cfg.max_value_0, run_data->rgb_cfg.max_value_1, run_data->rgb_cfg.max_value_2,
                             run_data->rgb_cfg.step_0, run_data->rgb_cfg.step_1, run_data->rgb_cfg.step_2,
                             run_data->rgb_cfg.min_brightness, run_data->rgb_cfg.max_brightness,
                             run_data->rgb_cfg.brightness_step, run_data->rgb_cfg.time};
}
static void time_switch()
{
    switch (run_data->time_mode)
    {
    case -1:
        run_data->time_start = millis();
        run_data->t_start.second = 59;
        run_data->t_start.minute = 4;
        run_data->t = run_data->t_start;
        run_data->rgb_fast = 0;
        run_data->rgb_fast_update = 0;
        return;
        break;
    case 0:
        run_data->time_start = millis();
        run_data->t_start.second = 59;
        run_data->t_start.minute = 24;
        run_data->t = run_data->t_start;
        run_data->rgb_fast = 0;
        run_data->rgb_fast_update = 0;
        break;
    case 1:
        run_data->time_start = millis();
        run_data->t_start.second = 59;
        run_data->t_start.minute = 14;
        run_data->t = run_data->t_start;
        run_data->rgb_fast = 0;
        run_data->rgb_fast_update = 0;
        break;

    default:
        break;
    }
}
/*********************************************************************************
 *Function:     rgb 控制
 *Description： 用来提醒
 *Calls:
 *Called By:
 *Input:
 *Output:
 *Return:
 *Others:       调快了速度和最低亮度
 **********************************************************************************/
static void rgb_ctrl()
{
    if (run_data->t.minute == 0 && run_data->t.second == 0 && run_data->rgb_fast == 0)
    {
        run_data->rgb_fast = 1;
        run_data->rgb_fast_update = 0;
    }
    // Serial.print(run_data->rgb_fast);
    // Serial.println("     rgb_fast");
    // Serial.print(run_data->rgb_fast_update);
    // Serial.println("     rgb_fast_update");
    if (run_data->rgb_fast_update == 0)
    {
        if (run_data->rgb_fast == 1)
        {
            run_data->rgb_cfg.time = 10;
            run_data->rgb_cfg.min_brightness = 0.01;
            run_data->rgb_cfg.brightness_step = 0.05;
            run_data->rgb_cfg.max_brightness = 0.95;
            run_data->rgb_cfg.step_0 = 0;
            run_data->rgb_cfg.step_1 = 0;
            run_data->rgb_cfg.step_2 = 0;
            //  Serial.println("set fast");
        }
        else
        {
            run_data->rgb_cfg.mode = 1;
            run_data->rgb_cfg.min_value_0 = 1;
            run_data->rgb_cfg.min_value_1 = 32;
            run_data->rgb_cfg.min_value_2 = 255;
            run_data->rgb_cfg.max_value_0 = 255;
            run_data->rgb_cfg.max_value_1 = 255;
            run_data->rgb_cfg.max_value_2 = 255;
            //  Serial.println("set low");
            run_data->rgb_cfg.step_0 = 1;
            run_data->rgb_cfg.step_1 = 1;
            run_data->rgb_cfg.step_2 = 1;
            run_data->rgb_cfg.min_brightness = 0.15;
            run_data->rgb_cfg.max_brightness = 0.25;
            run_data->rgb_cfg.brightness_step = 0.001;
            run_data->rgb_cfg.time = 50;
        }
        run_data->rgb_setting = {LED_MODE_HSV,
                                 run_data->rgb_cfg.min_value_0, run_data->rgb_cfg.min_value_1, run_data->rgb_cfg.min_value_2,
                                 run_data->rgb_cfg.max_value_0, run_data->rgb_cfg.max_value_1, run_data->rgb_cfg.max_value_2,
                                 run_data->rgb_cfg.step_0, run_data->rgb_cfg.step_1, run_data->rgb_cfg.step_2,
                                 run_data->rgb_cfg.min_brightness, run_data->rgb_cfg.max_brightness,
                                 run_data->rgb_cfg.brightness_step, run_data->rgb_cfg.time};
        set_rgb(&(run_data->rgb_setting));
        run_data->rgb_fast_update = 1;
    }
}
static void rgb_reset()
{

    run_data->rgb_cfg.mode = 1;
    run_data->rgb_cfg.min_value_0 = 1;
    run_data->rgb_cfg.min_value_1 = 32;
    run_data->rgb_cfg.min_value_2 = 255;
    run_data->rgb_cfg.max_value_0 = 255;
    run_data->rgb_cfg.max_value_1 = 255;
    run_data->rgb_cfg.max_value_2 = 255;
    //  Serial.println("set low");
    run_data->rgb_cfg.step_0 = 1;
    run_data->rgb_cfg.step_1 = 1;
    run_data->rgb_cfg.step_2 = 1;
    run_data->rgb_cfg.min_brightness = 0.15;
    run_data->rgb_cfg.max_brightness = 0.25;
    run_data->rgb_cfg.brightness_step = 0.001;
    run_data->rgb_cfg.time = 50;
    run_data->rgb_setting = {LED_MODE_HSV,
                             run_data->rgb_cfg.min_value_0, run_data->rgb_cfg.min_value_1, run_data->rgb_cfg.min_value_2,
                             run_data->rgb_cfg.max_value_0, run_data->rgb_cfg.max_value_1, run_data->rgb_cfg.max_value_2,
                             run_data->rgb_cfg.step_0, run_data->rgb_cfg.step_1, run_data->rgb_cfg.step_2,
                             run_data->rgb_cfg.min_brightness, run_data->rgb_cfg.max_brightness,
                             run_data->rgb_cfg.brightness_step, run_data->rgb_cfg.time};
    set_rgb(&(run_data->rgb_setting));
}

static void together_process(AppController *sys,
                             const Imu_Action *act_info)
{
    //  struct tm tt;
    if (RETURN == act_info->active)
    {
        sys->app_exit(); // 退出APP
        return;
    }
    if (GO_FORWORD == act_info->active)
    {
        return;
    }

    if (TURN_LEFT == act_info->active || TURN_RIGHT == act_info->active && 1 == act_info->active_update)
    {
        run_data->switch_count <<= 2;
        run_data->switch_count |= 3;
        if (run_data->switch_count > 0xf)
        {
            if (TURN_LEFT == act_info->active)
            {
                run_data->switch_count = 0X00;
                run_data->time_mode -= 1; //
            }
            else if (TURN_RIGHT == act_info->active)
            {
                run_data->switch_count = 0X00;
                run_data->time_mode += 1;
            }
            if (run_data->time_mode > 1) //限幅
                run_data->time_mode = 1;
            if (run_data->time_mode < -1)
                run_data->time_mode = -1;
            time_switch();
        }
    }
    else if (1 == act_info->active_update) //消抖
    {
        run_data->switch_count <<= 2;
        run_data->switch_count &= ~3;
    }

    rgb_ctrl();
    if (run_data->rgb_fast == 0)
    {
        run_data->time_ms = millis() - run_data->time_start; //换算
        run_data->t.second = run_data->t_start.second - (int)(run_data->time_ms / 1000) % 60;
        run_data->t.minute = run_data->t_start.minute - (int)(run_data->time_ms / 60000) % 60;
    }
    display_together(run_data->t, run_data->time_mode);
}

static int together_exit_callback(void *param)
{
    together_gui_del();
    rgb_reset();
    if (run_data != NULL)
    {
        // 释放资源
        free(run_data);
        run_data = NULL;
        Serial.println("EXIT\n");
    }
}
static void together_message_handle(const char *from, const char *to, APP_MESSAGE_TYPE type, void *message, void *ext_info)
{
    switch (type)
    {
    case APP_MESSAGE_WIFI_CONN:
    {
        //  get_timestamp(TIME_API);
    }
    }
}

APP_OBJ together_app = {TOGETHER_APP_NAME, &app_together_icon, "Author LC\nVersion 1.0.0\n",
                        together_init, together_process,
                        together_exit_callback, together_message_handle};
