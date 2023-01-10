# HoloCubic_ALO_TOMATO

原作者的项目链接 https://github.com/peng-zhihui/HoloCubic

~~本项目基于的代码 https://github.com/ClimbSnail/HoloCubic_AIO （v2.0）（2022 3月份）~~

本项目基于的代码 https://github.com/ClimbSnail/HoloCubic_AIO （**2022 12月份** [commit](https://github.com/ClimbSnail/HoloCubic_AIO/commit/1f6689bb6bf8ddf0f0987923ab9b3303df948217))

在以上基础上增加了**番茄时钟**功能，在了解本代码之前**一定**要了解一下[HoloCubic_AIO](https://github.com/ClimbSnail/HoloCubic_AIO)，本项目主要是对HoloCubic_AIO/AIO_Firmware_PIO文件夹中的代码进行修改。

## 更改记录
- 2022年12月：移植最新的AIO代码，更新lvgl版本，修改时钟偶尔自动切换的问题，倒计时变为从x分00秒开始，统一框架，方便移植单独的app
- 2022年3月：编写番茄钟初始代码

## 代码说明

- AIO_Firmware_PIO文件夹对应[HoloCubic_AIO/AIO_Firmware_PIO at main · ClimbSnail/HoloCubic_AIO (github.com)](https://github.com/ClimbSnail/HoloCubic_AIO/tree/main/AIO_Firmware_PIO)，在原基础上添加了番茄钟

  > 具体修改的内容可以查看[commit1](https://github.com/kylefjl/HoloCubic_AIO_TOMATO/commit/9b5b07cda18b455d1b70f644c281a7ecefa1fccd)和 [commit2](https://github.com/kylefjl/HoloCubic_AIO_TOMATO/commit/961c12c0781c4c33c79f16a19ecbab1c641726aa)，如果只想移植tomato app的话照着这两个commit操作就可以了

- bin 文件夹包含firmware_time.bin 固件，利用HoloCubic_AIO的上位机选择该固件烧录即可（即替换HoloCubic_AIO固件_vxxx.bin）
## 番茄钟功能演示
b站视频：https://www.bilibili.com/video/BV1E44y1N7U6/

<img src="https://user-images.githubusercontent.com/79000745/159287773-5d5ef2a2-62e6-406c-9cc6-ce78fc788908.jpg" alt="IMG_20220321_225312" width="250px" style="zoom: 10%;"  />     <img src="https://user-images.githubusercontent.com/79000745/159287987-08e874f1-d6d3-47cb-a404-f5a922429249.jpg" alt="IMG_20220321_225306" style="zoom:10%;" width="250px" />     <img src="https://user-images.githubusercontent.com/79000745/159288016-e63b55b2-52c1-42f1-95c9-e5e82b0726fb.jpg" alt="IMG_20220321_225257" style="zoom:10%;" width="250px" />
