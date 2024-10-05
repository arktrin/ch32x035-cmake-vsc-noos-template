#include "ch32x035.h"
#include "debug.h"

u16 TxData[] = { 0x0101, 0x0202, 0x0303, 0x0404, 0x0505, 0x0606,
                     0x1111, 0x1212, 0x1313, 0x1414, 0x1515, 0x1616,
                     0x2121, 0x2222, 0x2323, 0x2424, 0x2525, 0x2626 };

void LED1_BLINK_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = { 0 };
    SPI_InitTypeDef SPI_InitStructure={0};
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE );

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIOA, &GPIO_InitStructure );

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init( GPIOA, &GPIO_InitStructure );

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIOA, &GPIO_InitStructure );

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;

    SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init( SPI1, &SPI_InitStructure );

	SPI_Cmd( SPI1, ENABLE );
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
    // NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
    Delay_Init();
    USART_Printf_Init(115200);

    printf("SystemClk:%d\r\n", SystemCoreClock);
    printf( "ChipID:%08x\r\n", DBGMCU_GetCHIPID() );
    printf("This is printf example\r\n");

    u8 i = 0;
    u8 j = 1;
    LED1_BLINK_INIT();
    GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_2);

    while(1)
    {
        // Delay_Ms(10);
        GPIO_WriteBit(GPIOA, GPIO_Pin_0, (i == 0) ? (i = Bit_SET) : (i = Bit_RESET));
        // Delay_Ms(250);
        // GPIO_WriteBit(GPIOA, GPIO_Pin_2, (j == 0) ? (j = Bit_SET) : (j = Bit_RESET));
        
        if( SPI_I2S_GetFlagStatus( SPI1, SPI_I2S_FLAG_TXE ) != RESET )
        {
            GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_RESET); 
            SPI_I2S_SendData( SPI1, TxData[0] );
            while ( SPI_I2S_GetFlagStatus( SPI1, SPI_I2S_FLAG_BSY ) == SET );
            GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_SET);
        }
		// 
        Delay_Ms(10);
        
    }
}