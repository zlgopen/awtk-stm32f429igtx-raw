#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "string.h"
#include "sdram.h"
#include "malloc.h"
#include "w25qxx.h"
#include "ff.h"
#include "exfuns.h"
#include "string.h"
#include "sdio_sdcard.h"
#include "fontupd.h"
#include "text.h"
#include "ltdc.h"
#include "base/g2d.h"
#include "touch.h"

/************************************************
 ALIENTEK 阿波罗STM32F429开发板实验42
 汉字显示实验-HAL库函数版
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com	
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司	
 作者：正点原子 @ALIENTEK
************************************************/
		
#include "base/lcd.h"
#include "base/mem.h"

extern int gui_app_start(int lcd_w, int lcd_h);

int main(void)
{	
	HAL_Init();										 //初始化HAL库	 
	Stm32_Clock_Init(360,25,2,8);	 //设置时钟,180Mhz
	delay_init(180);							 //初始化延时函数
	uart_init(115200);						 //初始化USART
	LED_Init();										 //初始化LED 
	KEY_Init();										 //初始化按键
	SDRAM_Init();									 //SDRAM初始化
	LCD_Init();										 //LCD初始化
	W25QXX_Init();						     //初始化W25Q256

  tp_dev.init();
		
	return gui_app_start(lcdltdc.pwidth, lcdltdc.pheight);
}
