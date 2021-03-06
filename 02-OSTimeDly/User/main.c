#include "main.h"

#define LED_BLINK_STK_SIZE		64
#define LED_RED_PRIO			10
#define LED_GREEN_PRIO			9

OS_STK led_red_task_stk[LED_BLINK_STK_SIZE];
OS_STK led_green_task_stk[LED_BLINK_STK_SIZE];

void task_led_red(void *pdata);
void task_led_green(void *pdata);

int main(void)
{
	CPU_IntDis();
	OSInit();
	BSP_Init();
	
	USART_Puts(USART1, "OSTaskCreate\r\n");
	
	OSTaskCreate(task_led_red, 0, &led_red_task_stk[LED_BLINK_STK_SIZE-1],LED_RED_PRIO);
	OSTaskCreate(task_led_green, 0, &led_green_task_stk[LED_BLINK_STK_SIZE-1],LED_GREEN_PRIO);
	
	OSStart();
}

/* delay led red 1s */
void task_led_red(void *pdata)
{
	char SentData[20];
	uint8_t index = 0;
	while(1)
	{
		sprintf(SentData,"uC/OS-II Blink LED RED: %03d\r\n", index++);
		USART_Puts(USART1, SentData);
		BSP_LED_Toggle(LED_RED);
		OSTimeDly(10);
	}
}

/* delay led green 500ms */
void task_led_green(void *pdata)
{
	char SentData[20];
	uint8_t index = 0;
	while(1)
	{
		sprintf(SentData,"uC/OS-II Blink LED GREEN: %03d\r\n", index++);
		USART_Puts(USART1, SentData);
		BSP_LED_Toggle(LED_GREEN);
		OSTimeDlyHMSM(0u, 0u, 0u, 500u);
	}
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
