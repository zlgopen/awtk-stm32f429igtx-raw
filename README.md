# AWTK针对STM32f429igtx的移植。

[AWTK](https://github.com/xianjimli/awtk)是针对低端嵌入式设备开发的嵌入式GUI库。awtk-stm32f429igtx-raw是AWTK在stm32f429igtx上的移植。

第一版以[正点原子的开发实验板]()https://item.taobao.com/item.htm?spm=a1z10.1-c-s.w11877762-18401048725.10.145a2276IsywTF&id=534585837612为载体移植(该开发板性价比不错，推荐一下:))。

## 编译

1. 将awtk取到当前目录

```
git clone https://github.com/xianjimli/awtk.git
```

2. 用keil打开user/awtk.uvproj

## 已知问题

由于目前没有实现获取当前时间的(毫秒)函数，所以不支持窗口动画和定时器。

