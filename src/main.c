/*
 *@Note
 *USART1_Tx(PB10) is used as a print debug port output
 *GPIO pins PA0 and PA1 are toggling
 *
 */

#include "ch32x035.h"
#include "debug.h"

void LED1_BLINK_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = { 0 };
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
    Delay_Init();
    USART_Printf_Init(115200);

    printf("SystemClk:%d\r\n", SystemCoreClock);
    printf( "ChipID:%08x\r\n", DBGMCU_GetCHIPID() );
    printf("This is printf example\r\n");

    u8 i = 0;
    u8 j = 1;
    LED1_BLINK_INIT();
    GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1);

    while(1)
    {
        Delay_Ms(250);
        GPIO_WriteBit(GPIOA, GPIO_Pin_0, (i == 0) ? (i = Bit_SET) : (i = Bit_RESET));
        Delay_Ms(250);
        GPIO_WriteBit(GPIOA, GPIO_Pin_1, (j == 0) ? (j = Bit_SET) : (j = Bit_RESET));
    }
}