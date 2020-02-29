#include "stm32f10x_flash.h"
//#include "flash.h"
#include "stm32f10x_it.h"
#define WriteFlashAddress    ((u32)0x08010000)//��д��ʼ��ַ���ڲ�flash�����洢���ַ��0x08000000��ʼ��


/*******************************************************************************
* ��������Write_Flash
*����    ��дSTM32ָ����ַ��Flash
*����    ��buff:д�����ݻ�������len:д�����ݳ���
*���    ����
*����ֵ    ��u8��д�ɹ�����1��ʧ�ܷ���0
*˵��    ����
*******************************************************************************/
u8 Write_Flash(u16 *buff, u8 len)
{    
    volatile FLASH_Status FLASHStatus;
    u8 k=0;
    u32 Address;

    Address = WriteFlashAddress;
    FLASHStatus = FLASH_COMPLETE;
    FLASH_Unlock();//����
    FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);//������б�־
    FLASHStatus = FLASH_ErasePage(WriteFlashAddress);//��������
    if(FLASHStatus == FLASH_COMPLETE)
    {
        for(k=0;(k<len) && (FLASHStatus == FLASH_COMPLETE);k++)
        {
            //FLASHStatus = FLASH_ProgramWord(Address, buff[k]);//д��һ���֣�32λ����������ָ����ַ
          FLASHStatus =  FLASH_ProgramHalfWord(Address, buff[k]);  
					Address = Address + 2;//��ַƫ��4���ֽ�
        }        
        FLASH_Lock();//������������ֹ��д��
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
* ��������Read_Flash
*����    ����STM32ָ����ַ��Flash
*����    ��buff:�������ݻ�������len:�������ݳ���
*���    ����
*����ֵ    ����
*˵��    ����
*******************************************************************************/
void Read_Flash(u16 *buff, u8 len)
{
    u8 k;
    u32 Address;
    
    Address = WriteFlashAddress;
    for(k=0;k<len;k++)
    {
        buff[k] =  (*(vu16*) Address);//��ָ����ַ��һ���ֵ�����
			//buff[k] =(*(uint16_t *)Address);
        Address += 2;//��ַƫ��4���ֽ�        
    }
} 