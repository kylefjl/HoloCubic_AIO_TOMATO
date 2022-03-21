#include "tomato.h"
#include "message.h"
#include "sys/app_controller.h"
#include "common.h"
#include "tomato_gui.h"

#define SETTINGS_APP_NAME "Tomato"
#define RECV_BUF_LEN 128

struct SettingsAppRunData
{
    uint8_t *recv_buf;
    uint16_t recv_len;
};


static SettingsAppRunData *run_data = NULL;
/*
 *  解析串口数据
 *  帧格式为 帧头（2字节）+ 帧长度（2字节）+ 发送者（2字节）+ 接收者（2字节）+ 消息类型（2字节）+ 消息数据（帧长度-10）+ 帧尾/r/n（2字节）
 *
 */

static int tomato_init(void)
{
    // 初始化运行时的参数
    tomato_gui_init();

    display_tomato(AIO_VERSION, "v 2.0.0", LV_SCR_LOAD_ANIM_NONE);

    // 初始化运行时参数
    run_data = (SettingsAppRunData *)calloc(1, sizeof(SettingsAppRunData));
    run_data->recv_buf = (uint8_t *)malloc(RECV_BUF_LEN);
    run_data->recv_len = 0;
}

static void tomato_process(AppController *sys,
                      const Imu_Action *act_info)
{
    if (RETURN == act_info->active)
    {
        sys->app_exit(); // 退出APP
        return;
    }

    // if (Serial.available())
    // {
    //     uint16_t len = Serial.read(run_data->recv_buf + run_data->recv_len,
    //                                RECV_BUF_LEN - run_data->recv_len);

    //     run_data->recv_len += len;
    //     if (run_data->recv_len > 0)
    //     {
    //         Serial.print("rev = ");

    //         Serial.write(run_data->recv_buf, len);
    //      //   analysis_uart_data(run_data->recv_len, run_data->recv_buf);
    //     }
    //     delay(50);
    // }
    // else
    // {
    //     delay(200);
    // }

    // 发送请求，当请求完成后自动会调用 tomato_event_notification 函数
    // sys->req_event(&tomato_app, APP_MESSAGE_WIFI_CONN, run_data->val1);
    // 程序需要时可以适当加延时
    // delay(200);
}

static int tomato_exit_callback(void *param)
{
    tomato_gui_del();
    // 释放资源
    free(run_data);
    run_data = NULL;
}

static void tomato_message_handle(const char *from, const char *to,
                             APP_MESSAGE_TYPE type, void *message,
                             void *ext_info)
{
    // 目前事件主要是wifi开关类事件（用于功耗控制）
    switch (type)
    {
    case APP_MESSAGE_WIFI_CONN:
    {
        // todo
    }
    break;
    case APP_MESSAGE_WIFI_AP:
    {
        // todo
    }
    break;
    case APP_MESSAGE_WIFI_ALIVE:
    {
        // wifi心跳维持的响应 可以不做任何处理
    }
    break;
    case APP_MESSAGE_GET_PARAM:
    {
        char *param_key = (char *)message;
    }
    break;
    case APP_MESSAGE_SET_PARAM:
    {
        char *param_key = (char *)message;
        char *param_val = (char *)ext_info;
    }
    break;
    default:
        break;
    }
}

APP_OBJ tomato_app = {SETTINGS_APP_NAME, &app_tomato, "",
                        tomato_init, tomato_process,
                        tomato_exit_callback, tomato_message_handle};
