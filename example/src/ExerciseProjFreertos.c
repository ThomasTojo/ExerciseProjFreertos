/*
 * @brief FreeRTOS exercise example
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2013
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "chip.h"
#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <string.h>

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
#define UARTNum 3

#if (UARTNum == 3)
#define LPC_UART LPC_USART3
#define UARTx_IRQn  USART3_IRQn
#define UARTx_IRQHandler UART3_IRQHandler
#define _GPDMA_CONN_UART_Tx GPDMA_CONN_UART3_Tx
#define _GPDMA_CONN_UART_Rx GPDMA_CONN_UART3_Rx
#endif


char speed;
SemaphoreHandle_t xSemaphore = NULL;

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

void LED_Display()
{
	Board_LED_Set(0, false);
	Board_LED_Set(1, false);
	Board_LED_Set(2, false);
	Board_LED_Set(3, false);
	Board_LED_Set(4, false);
	Board_LED_Set(5, false);
	Board_LED_Set(6, false);
	Board_LED_Set(7, false);

	switch(speed)
	{
	case 'a':Board_LED_Set(3, true);
			 break;
	case 'b':Board_LED_Set(2, true);
			 break;
	case 'c':Board_LED_Set(2, true);
			 Board_LED_Set(3, true);
			 break;
	case 'd':Board_LED_Set(1, true);
			 break;
	case 'e':Board_LED_Set(1, true);
			 Board_LED_Set(3, true);
			 break;
	default :Board_LED_Set(0, true);
			 Board_LED_Set(1, true);
			 Board_LED_Set(2, true);
			 Board_LED_Set(3, true);
			 Board_LED_Set(4, true);
			 Board_LED_Set(5, true);
			 Board_LED_Set(6, true);
			 Board_LED_Set(7, true);

	}
}


/* LED1 toggle thread */
static void vSerialReadTask1(void *pvParameters) {
	bool LedState = false;
	if((xSemaphore = xSemaphoreCreateBinary())==NULL)
    	DEBUGOUT("FAiled to create the binary semaphore");
	xSemaphoreGive(xSemaphore);

	while (1) {
	    if( xSemaphore != NULL )
	    {
	        if( xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE )
	        {
	        	//while(!(Chip_UART_Read(LPC_UART, &speed, 1)));
	        	//speed = InputByte;
	        	Chip_UART_Read(LPC_UART, &speed, 1);
	        	xSemaphoreGive(xSemaphore);
	        }
        	for(uint8_t i=0;i<2;i++)
        	{
        		Board_LED_Set(0, LedState);
        		LedState = (bool) !LedState;

        		/* About a 5Hz on/off toggle rate */
        		vTaskDelay(configTICK_RATE_HZ / 10);
        	}
	    }
	}
}

/* LED2 toggle thread */
static void vSerialWriteTask2(void *pvParameters) {
	bool LedState = false;
	static char InputByte=0;
	char str[]="\n\rYour Speed is:";
	uint8_t speed0,speed1;
	while(xSemaphore == NULL)
		vTaskDelay(100);

	while (1) {
	    if( xSemaphore != NULL )
	    {
	        if(InputByte!=speed)
	        {
	        	if( xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE )
	        	{
		        	switch(speed)
		        	{
		        	case 'a':speed0='1';
		        			 speed1='0';
		        			 break;
		        	case 'b':speed0='2';
		        			 speed1='0';
		        			 break;
		        	case 'c':speed0='3';
		        			 speed1='0';
		        			 break;
		        	case 'd':speed0='4';
		        			 speed1='0';
		        			 break;
		        	case 'e':speed0='5';
		        			 speed1='0';
		        			 break;
		        	default :speed0='H';
		        			 speed1='S';
		        	}
		        	Chip_UART_SendBlocking(LPC_UART,str,strlen(str));
		        	Chip_UART_SendByte(LPC_UART,speed0);
		        	Chip_UART_SendByte(LPC_UART,speed1);
		        	Chip_UART_SendBlocking(LPC_UART,"\n\r",strlen("\n\r"));
	        		InputByte=speed;
		        	xSemaphoreGive(xSemaphore);
		        }
	        		Board_LED_Set(7, LedState);
	        		LedState = (bool) !LedState;

	        		/* About a 10Hz on/off toggle rate */
	        		vTaskDelay(configTICK_RATE_HZ / 20);
	        }
	    }
	}
}

static void vLED_OutTask3(void *pvParameters) {
	static char InputByte=0;

	while (1) {
	    if( xSemaphore != NULL )
	    {
	        if(InputByte!=speed)
	        {
	        	if( xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE )
	        	{
		        	LED_Display();
		        	InputByte=speed;
		        	xSemaphoreGive(xSemaphore);
	        	}
	        }
        	vTaskDelay(configTICK_RATE_HZ / 1);
	    }
	}
}


/* Sets up system hardware */
static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();

	/* Initial LED0 state is off */
	Board_LED_Set(0, false);


}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief	main routine for FreeRTOS blinky example
 * @return	Nothing, function should not exit
 */
int main(void)
{

	prvSetupHardware();


#if !((defined(CHIP_LPC43XX) && defined(BOARD_KEIL_MCB_18574357) && UARTNum==3) || ((!(defined(CHIP_LPC43XX) && defined(BOARD_KEIL_MCB_18574357))) && UARTNum==0))
	Chip_UART_Init(LPC_UART);
	Chip_UART_SetBaud(LPC_UART, 115200);
	Chip_UART_ConfigData(LPC_UART, UART_LCR_WLEN8 | UART_LCR_SBS_1BIT); /* Default 8-N-1 */

	/* Enable UART Transmit */
	Chip_UART_TXEnable(LPC_UART);
#endif
	Chip_UART_SetupFIFOS(LPC_UART, (UART_FCR_FIFO_EN | UART_FCR_RX_RS |
						UART_FCR_TX_RS | UART_FCR_TRG_LEV0));



	/* vSerialRead thread */
	xTaskCreate(vSerialReadTask1, "vSerialReadTask1", configMINIMAL_STACK_SIZE,
			NULL, (tskIDLE_PRIORITY + 1UL), (TaskHandle_t *) NULL);

	/* vSerialWrite thread */
	xTaskCreate(vSerialWriteTask2, "vSerialWriteTask2", configMINIMAL_STACK_SIZE,
			NULL, (tskIDLE_PRIORITY + 1UL), (TaskHandle_t *) NULL);

	/* LED Out thread */
	xTaskCreate(vLED_OutTask3, "vLED_OutTask3", configMINIMAL_STACK_SIZE,
			NULL, (tskIDLE_PRIORITY + 1UL), (TaskHandle_t *) NULL);

	/* Start the scheduler */
	vTaskStartScheduler();

	/* Should never arrive here */
	return 1;
}
