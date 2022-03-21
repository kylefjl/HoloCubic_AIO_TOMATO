#include "together.h"
#include "together_gui.h"
#include "sys/app_controller.h"
#include "common.h"
#include "ESP32Time.h"
#define TOGETHER_APP_NAME "Tomato"

// 动态数据，APP的生命周期结束也需要释放它
struct TogetherAppRunData
{
    long long time_start; //
    long long time_ms;    //毫秒数
    TimeStr t;            //时间结构体
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
    run_data->t.second = 59; //专注时间，初始化一次
    run_data->t.minute = 24;
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
    if (run_data->t.minute == 0 && run_data->t.second == 0)
    {
        if (TURN_LEFT == act_info->active) //休息时间，初始化一次
        {
            run_data->time_start = millis();
            run_data->t.second = 59;
            run_data->t.minute = 4;
            return;
        }
        if (TURN_RIGHT == act_info->active) //休息时间，初始化一次
        {
            run_data->time_start = millis();
            run_data->t.second = 59;
            run_data->t.minute = 14;
            return;
        }
    }
    else
    {
        run_data->time_ms = millis() - run_data->time_start; //换算
        run_data->t.second = 59 - (int)(run_data->time_ms / 1000) % 60;
        run_data->t.minute = 24 - (int)(run_data->time_ms / 60000) % 60;
        run_data->t.hour = 0;
    }

    display_together(forever_data.networkTime, run_data->t);
    delay(300);
}

static int together_exit_callback(void *param)
{
    together_gui_del();
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
