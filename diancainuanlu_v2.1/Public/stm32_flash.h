#ifndef _stm32_flash_H
#define _stm32_flash_H

#include "system.h"

extern u8 Write_Flash(u32 addr,u16 *buff, u8 len);
extern void Read_Flash(u32 addr,u16 *buff, u8 len);

#endif
