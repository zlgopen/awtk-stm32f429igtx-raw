/**
 * file:   main_loop_stm32_raw.c
 * author: li xianjing <xianjimli@hotmail.com>
 * brief:  main loop for stm32
 *
 * copyright (c) 2018 - 2018 Guangzhou ZHIYUAN Electronics Co.,Ltd.
 *
 * this program is distributed in the hope that it will be useful,
 * but without any warranty; without even the implied warranty of
 * merchantability or fitness for a particular purpose.  see the
 * license file for more details.
 *
 */

/**
 * history:
 * ================================================================
 * 2018-05-11 li xianjing <xianjimli@hotmail.com> created
 *
 */

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
#include "touch.h"

#include "base/g2d.h"
#include "base/idle.h"
#include "base/timer.h"
#include "lcd/lcd_mem_rgb565.h"
#include "main_loop/main_loop_simple.h"

extern u32* ltdc_framebuf[2];
#define online_fb_addr (uint8_t*)ltdc_framebuf[0]
#define offline_fb_addr (uint8_t*)ltdc_framebuf[1]

uint8_t platform_disaptch_input(main_loop_t* loop) {
  int x = 0;
  int y = 0;
  uint8_t key = KEY_Scan(0);

  tp_dev.scan(0);

  x = tp_dev.x[0];
  y = tp_dev.y[0];

  y = lcdltdc.pheight - tp_dev.x[0];
  x = tp_dev.y[0];

  if (tp_dev.sta & TP_PRES_DOWN) {
    main_loop_post_pointer_event(loop, TRUE, x, y);
  } else {
    main_loop_post_pointer_event(loop, FALSE, x, y);
  }

  return 0;
}

extern lcd_t* stm32f429_create_lcd(wh_t w, wh_t h);

lcd_t* platform_create_lcd(wh_t w, wh_t h) {
  return stm32f429_create_lcd(w, h);
}

#include "main_loop/main_loop_raw.inc"
