#ifndef _SDMMC_SDCARD_H
#define _SDMMC_SDCARD_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F746开发板
//SD卡驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2016/1/6
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

#define SD_TIMEOUT ((uint32_t)100000000)            //超时时间

#define SD_DMA_MODE    		0	//1：DMA模式，0：查询模式   

extern SD_HandleTypeDef        SDCARD_Handler;     //SD卡句柄
extern HAL_SD_CardInfoTypedef  SDCardInfo;         //SD卡信息结构体

u8 SD_Init(void);
u8 SD_GetCardInfo(HAL_SD_CardInfoTypedef *cardinfo);
u8 SD_ReadDisk(u8* buf,u32 sector,u32 cnt);
u8 SD_WriteDisk(u8 *buf,u32 sector,u8 cnt);
u8 SD_ReadBlocks_DMA(uint32_t *buf,uint64_t sector,uint32_t blocksize,uint32_t cnt);
u8 SD_WriteBlocks_DMA(uint32_t *buf,uint64_t sector,uint32_t blocksize,uint32_t cnt);
#endif
