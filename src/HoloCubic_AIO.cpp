/***************************************************
  HoloCubic多功能固件源码

  聚合多种APP，内置天气、时钟、相册、特效动画、视频播放、视频投影、
  浏览器文件修改。（各APP具体使用参考说明书）

  Github repositories：https://github.com/ClimbSnail/HoloCubic_AIO

  Last review/edit by ClimbSnail: 2021/08/21
 ****************************************************/

#include "driver/lv_port_indev.h"
#include "driver/lv_port_fatfs.h"
#include "common.h"

#include "sys/app_controller.h"

#include "app/weather/weather.h"
#include "app/bilibili_fans/bilibili.h"
#include "app/tomato/tomato.h"
//#include "app/together/together.h"
#include "app/server/server.h"
#include "app/idea_anim/idea.h"
#include "app/settings/settings.h"
#include "app/game_2048/game_2048.h"
#include "app/picture/picture.h"
#include "app/media_player/media_player.h"
#include "app/screen_share/screen_share.h"
#include "app/file_manager/file_manager.h"
#include "app/weather_old/weather_old.h"

#include <SPIFFS.h>
#include <esp32-hal.h>

/*** Component objects **7*/
ImuAction *act_info;          // 存放mpu6050返回的数据
AppController *app_controller; // APP控制器

void setup()
{
    Serial.begin(115200);

    Serial.println(F("\nAIO (All in one) version " AIO_VERSION "\n"));
    app_controller = new AppController(); // APP控制器

    // 需要放在Setup里初始化
    if (!SPIFFS.begin(true))
    {
        Serial.println("SPIFFS Mount Failed");
        return;
    }

#ifdef PEAK
    pinMode(CONFIG_BAT_CHG_DET_PIN, INPUT);
    pinMode(CONFIG_ENCODER_PUSH_PIN, INPUT_PULLUP);
    /*电源使能保持*/
    Serial.println("Power: Waiting...");
    pinMode(CONFIG_POWER_EN_PIN, OUTPUT);
    digitalWrite(CONFIG_POWER_EN_PIN, LOW);
    digitalWrite(CONFIG_POWER_EN_PIN, HIGH);
    Serial.println("Power: ON");
    log_e("Power: ON");
#endif

    // config_read(NULL, &g_cfg);   // 旧的配置文件读取方式
    app_controller->read_config(&app_controller->sys_cfg);
    app_controller->read_config(&app_controller->mpu_cfg);
    app_controller->read_config(&app_controller->rgb_cfg);

    /*** Init screen ***/
    screen.init(app_controller->sys_cfg.rotation,
                app_controller->sys_cfg.backLight);

    /*** Init on-board RGB ***/
    rgb.init();
    rgb.setBrightness(0.05).setRGB(0, 64, 64);

    /*** Init ambient-light sensor ***/
    ambLight.init(ONE_TIME_H_RESOLUTION_MODE);

    /*** Init micro SD-Card ***/
    tf.init();
    lv_fs_if_init();

    app_controller->init();
    app_controller->app_install(&weather_app);
    //app_controller->app_install(&tomato_app);
    //app_controller->app_install(&together_app);
    app_controller->app_install(&tomato_app);
    app_controller->app_install(&weather_old_app);
    app_controller->app_install(&picture_app);
    app_controller->app_install(&media_app);
    app_controller->app_install(&screen_share_app);
    app_controller->app_install(&file_manager_app);
    app_controller->app_install(&server_app);
    app_controller->app_install(&idea_app);
    app_controller->app_install(&bilibili_app);
    app_controller->app_install(&settings_app);
    app_controller->app_install(&game_2048_app);

    // 优先显示屏幕 加快视觉上的开机时间
    app_controller->main_process(&mpu.action_info);

    /*** Init IMU as input device ***/
    lv_port_indev_init();
    mpu.init(app_controller->sys_cfg.mpu_order,
             app_controller->sys_cfg.auto_calibration_mpu,
             &app_controller->mpu_cfg); // 初始化比较耗时

    /*** 以此作为MPU6050初始化完成的标志 ***/
    RgbConfig *rgb_cfg = &app_controller->rgb_cfg;
    // 初始化RGB灯 HSV色彩模式
    RgbParam rgb_setting = {LED_MODE_HSV,
                            rgb_cfg->min_value_0, rgb_cfg->min_value_1, rgb_cfg->min_value_2,
                            rgb_cfg->max_value_0, rgb_cfg->max_value_1, rgb_cfg->max_value_2,
                            rgb_cfg->step_0, rgb_cfg->step_1, rgb_cfg->step_2,
                            rgb_cfg->min_brightness, rgb_cfg->max_brightness,
                            rgb_cfg->brightness_step, rgb_cfg->time};
    // 初始化RGB任务
    rgb_thread_init(&rgb_setting);
}

void loop()
{
    screen.routine();
    act_info = mpu.update(200);

#ifdef PEAK
    if (!mpu.Encoder_GetIsPush())
    {
        Serial.println("mpu.Encoder_GetIsPush()1");
        delay(1000);
        if (!mpu.Encoder_GetIsPush())
        {
            Serial.println("mpu.Encoder_GetIsPush()2");
            // 适配Peak的关机功能
            digitalWrite(CONFIG_POWER_EN_PIN, LOW);
        }
    }
#endif
    app_controller->main_process(act_info); // 运行当前进程
    // Serial.println(ambLight.getLux() / 50.0);
    // rgb.setBrightness(ambLight.getLux() / 500.0);
}