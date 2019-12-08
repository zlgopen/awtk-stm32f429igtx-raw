# AWTK 针对 STM32f429igtx 的移植。

[AWTK](https://github.com/zlgopen/awtk) 是为嵌入式系统开发的 GUI 引擎库。

[awtk-stm32f429igtx-raw](https://github.com/zlgopen/awtk-stm32f429igtx-raw) 是 AWTK 在 stm32f429igtx 上的移植。

本项目以 [正点原子阿波罗 STM32F429IGT 开发板](https://item.taobao.com/item.htm?spm=a1z10.1-c-s.w11877762-18401048725.10.145a2276IsywTF&id=534585837612) 为载体移植，其它开发板可能要做些修改，有问题请请创建 issue。

## 编译

1. 获取源码

```
git clone https://github.com/zlgopen/awtk-stm32f429igtx-raw.git
cd awtk-stm32f429igtx-raw
git clone https://github.com/zlgopen/awtk.git
```

2. 用 keil 打开 user/awtk.uvproj

> 本项目采用的 3framebuffer，如果希望使用 2framebuffer 请参考 767 的移植。

## 注意事项

> 由于 1 M 无法放下 demoui 完整的资源，所以部分功能无法展示。
