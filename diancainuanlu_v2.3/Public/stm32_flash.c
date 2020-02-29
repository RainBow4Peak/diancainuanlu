#include "stm32f10x_flash.h"
//#include "flash.h"
#include "stm32f10x_it.h"
#define WriteFlashAddress    ((u32)0x08010000)//读写起始地址（内部flash的主存储块地址从0x08000000开始）

/*******************************************************************************
* 函数名：Write_Flash
*描述    ：写STM32指定地址的Flash
*输入    ：buff:写入数据缓冲区，len:写入数据长度
*输出    ：无
*返回值    ：u8：写成功返回1，失败返回0
*说明    ：无
*******************************************************************************/
u8 Write_Flash(u32 addr,u16 *buff, u8 len)
{    
    volatile FLASH_Status FLASHStatus;
    u8 k=0;
    u32 Address;

    Address = addr;
    FLASHStatus = FLASH_COMPLETE;
    FLASH_Unlock();//解锁
    FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);//清除所有标志
		FLASHStatus = FLASH_ErasePage(WriteFlashAddress);//扇区擦除
    if(FLASHStatus == FLASH_COMPLETE)
    {
        for(k=0;(k<len) && (FLASHStatus == FLASH_COMPLETE);k++)
        {
            //FLASHStatus = FLASH_ProgramWord(Address, buff[k]);//写入一个字（32位）的数据入指定地址
          FLASHStatus =  FLASH_ProgramHalfWord(Address, buff[k]);  
					Address = Address + 2;//地址偏移4个字节
        }        
        FLASH_Lock();//重新上锁，防止误写入
    }
    else
    {
        return 0;
    }
    if(FLASHStatus == FLASH_COMPLETE)
    {
        return 1;
    }
    return 0;
}
/*******************************************************************************
* 函数名：Read_Flash
*描述    ：读STM32指定地址的Flash
*输入    ：buff:读出数据缓冲区，len:读出数据长度
*输出    ：无
*返回值    ：无
*说明    ：无
*******************************************************************************/
void Read_Flash(u32 addr,u16 *buff, u8 len)
{
    u8 k;
    u32 Address;
    Address = addr;
		for(k=0;k<len;k++)
    {
        buff[k] =  (*(vu16*) Address);//读指定地址的一个字的数据
			//buff[k] =(*(uint16_t *)Address);
        Address += 2;//地址偏移4个字节        
    }
} 