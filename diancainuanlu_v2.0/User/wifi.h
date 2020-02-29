 #include <usart.h>

extern char *Set_Mode;
extern char *RST;
extern char *Set_Name;
extern char *Set_Parameter;
extern char *Mult_Mode;
extern char *Open_Server;

extern u16 Wifi_TimuOut_Num;
extern u8 Send_START;
extern u8 Send_Again_Num;
extern u8 Send_Again;
extern u8 FLAG;
extern u16 Send_Num;
extern  void Second_AT_Command(char *b,char *a,u8 flag)  ;

extern void Send_AT_Data_INIT(char *b,char *a,u8 flag);

#define UART1_SendLR() UART1_SendString("\r\n")