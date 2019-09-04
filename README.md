# AWTK针对STM32f429igtx的移植。

[AWTK](https://github.com/zlgopen/awtk)是为嵌入式系统开发的GUI引擎库。

[awtk-stm32f429igtx-raw](https://github.com/zlgopen/awtk-stm32f429igtx-raw)是AWTK在stm32f429igtx上的移植。

本项目以[正点原子阿波罗STM32F429IGT开发板](https://item.taobao.com/item.htm?spm=a1z10.1-c-s.w11877762-18401048725.10.145a2276IsywTF&id=534585837612)为载体移植，其它开发板可能要做些修改，有问题请请创建issue。

## 编译

1. 获取源码

```
git clone https://github.com/zlgopen/awtk-stm32f429igtx-raw.git
cd awtk-stm32f429igtx-raw
git clone https://github.com/zlgopen/awtk.git
```

2. 用keil打开user/awtk.uvproj

> 本项目采用的3framebuffer，如果希望使用2framebuffer请参考767的移植。

