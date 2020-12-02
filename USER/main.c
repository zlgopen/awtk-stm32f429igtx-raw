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

#include "tkc/mem.h"
#include "base/lcd.h"
#include "lcd/lcd_mem_bgr565.h"
#include "lcd/lcd_mem_bgra8888.h"

extern int gui_app_start(int lcd_w, int lcd_h);

void LTDC_IRQHandler(void) {
  HAL_LTDC_IRQHandler(&LTDC_Handler);
}

static uint8_t* s_next_fb = NULL;
static uint8_t* s_online_fb = NULL;
static uint8_t* s_framebuffers[3];

static lcd_begin_frame_t org_begin_frame;

ret_t lcd_stmf429_begin_frame(lcd_t* lcd, const rect_t* dirty_rect) {
  if (lcd_is_swappable(lcd)) {
    uint32_t i = 0;
    lcd_mem_t* mem = (lcd_mem_t*)lcd;

    mem->next_fb = NULL;		
    mem->online_fb = NULL;
    mem->offline_fb = NULL;
    for (i = 0; i < ARRAY_SIZE(s_framebuffers); i++) {
      uint8_t* iter = s_framebuffers[i];
      if (iter != s_online_fb && iter != s_next_fb) {
        mem->offline_fb = iter;
        break;
      }
    }
		
		org_begin_frame(lcd, dirty_rect);
  }

  return RET_OK;
}

ret_t lcd_stmf429_swap(lcd_t* lcd) {
  lcd_mem_t* mem = (lcd_mem_t*)lcd;

  s_next_fb = mem->offline_fb;

  return RET_OK;
}

void HAL_LTDC_LineEvenCallback(LTDC_HandleTypeDef* LTDC_Handler) {
  if (s_next_fb != NULL) {
    HAL_LTDC_SetAddress(LTDC_Handler, (uint32_t)s_next_fb, 0);
    __HAL_LTDC_RELOAD_CONFIG(LTDC_Handler);
    s_online_fb = s_next_fb;
    s_next_fb = NULL;
  }

  HAL_LTDC_ProgramLineEvent(LTDC_Handler, 0);
}

#define FB_ADDR (uint8_t*)0XC0000000

lcd_t* stm32f429_create_lcd(wh_t w, wh_t h) {
  lcd_t* lcd = NULL;
  uint32_t size = w * h * lcdltdc.pixsize;
  s_framebuffers[0] = FB_ADDR;
  s_framebuffers[1] = FB_ADDR + size;
  s_framebuffers[2] = FB_ADDR + 2 * size;

#if LCD_PIXFORMAT == LCD_PIXFORMAT_ARGB8888 || LCD_PIXFORMAT == LCD_PIXFORMAT_RGB888
  lcd = lcd_mem_bgra8888_create_three_fb(w, h, s_framebuffers[0], s_framebuffers[1],
                                         s_framebuffers[2]);
#else
  lcd = lcd_mem_bgr565_create_three_fb(w, h, s_framebuffers[0], s_framebuffers[1], s_framebuffers[2]);
#endif /*LCD_PIXFORMAT*/
	
	org_begin_frame = lcd->begin_frame;
  lcd->swap = lcd_stmf429_swap;
  lcd->begin_frame = lcd_stmf429_begin_frame;

  HAL_NVIC_SetPriority(LTDC_IRQn, 1, 1);
  HAL_NVIC_EnableIRQ(LTDC_IRQn);
  HAL_LTDC_ProgramLineEvent(&LTDC_Handler, 0);
  HAL_LTDC_SetAddress(&LTDC_Handler, (uint32_t)s_framebuffers[0], 0);
  __HAL_LTDC_RELOAD_CONFIG(&LTDC_Handler);

  return lcd;
}

/*
lcd_t* stm32f429_create_lcd(wh_t w, wh_t h) {
  lcd_t* lcd = NULL;
  uint32_t size = w * h * lcdltdc.pixsize;
  s_framebuffers[0] = FB_ADDR;
  s_framebuffers[1] = FB_ADDR + size;

#if LCD_PIXFORMAT == LCD_PIXFORMAT_ARGB8888 
  lcd = lcd_mem_bgra8888_create_double_fb(w, h, s_framebuffers[0], s_framebuffers[1]);
#else
  lcd = lcd_mem_bgr565_create_double_fb(w, h, s_framebuffers[0], s_framebuffers[1]);
#endif 
	
  return lcd;
}
*/

int main(void) {
  HAL_Init();                       //初始化HAL库
  Stm32_Clock_Init(360, 25, 2, 8);  //设置时钟,180Mhz
  delay_init(180);                  //初始化延时函数
  uart_init(115200);                //初始化USART
  LED_Init();                       //初始化LED
  KEY_Init();                       //初始化按键
  SDRAM_Init();                     // SDRAM初始化
  LCD_Init();                       // LCD初始化
  //W25QXX_Init();                    //初始化W25Q256

  tp_dev.init();

  return gui_app_start(lcdltdc.pwidth, lcdltdc.pheight);
}
