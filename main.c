
/* Standard includes. */
#include <assert.h>
#include <stdio.h>
#include <string.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"

#include "pin_mux.h"
#include "clock_config.h"

#include "DataTypeDefinitions.h"
#include "GPIO.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* The software timer period. */
#define TASK_DELAY_1 ((5 / portTICK_PERIOD_MS) / 10)
#define TASK_DELAY_2 ((5 / portTICK_PERIOD_MS) / 10)
#define TASK_DELAY_PHASE_120 (35 / portTICK_PERIOD_MS)
#define TASK_DELAY_PHASE_240 (66 / portTICK_PERIOD_MS)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
uint8_t status = 0;
uint8_t status_2 = 0;
uint8_t status_3 = 0;

void task_signal_1(void* args)
{
	for(;;)
	{
		GPIO_PinWrite (GPIOC, BIT1, status);
		GPIO_PinWrite (GPIOB, BIT9, (1 & ~(status)));
		if(status)
		{
			vTaskDelay(TASK_DELAY_1);
		}
		else
		{
			vTaskDelay(TASK_DELAY_2);
		}
		status = (status) ? 0 : 1;
	}
}

void task_signal_2(void* args)
{
	vTaskDelay(TASK_DELAY_PHASE_120);
	for(;;)
	{
		GPIO_PinWrite (GPIOB, BIT19, status_2);
		GPIO_PinWrite (GPIOC, BIT17, (1 & ~(status_2)));
		if(status)
		{
			vTaskDelay(TASK_DELAY_1);
		}
		else
		{
			vTaskDelay(TASK_DELAY_2);
		}
		status_2 = (status_2) ? 0 : 1;
	}
}

void task_signal_3(void* args)
{
	vTaskDelay(TASK_DELAY_PHASE_240);
	for(;;)
	{
		GPIO_PinWrite (GPIOB, BIT18, status_3);
		GPIO_PinWrite (GPIOC, BIT16, (1 & ~(status_3)));
		if(status)
		{
			vTaskDelay(TASK_DELAY_1);
		}
		else
		{
			vTaskDelay(TASK_DELAY_2);
		}
		status_3 = (status_3) ? 0 : 1;
	}
}

int main(void)
{
    GPIO_clockGating(GPIO_A);
    GPIO_clockGating(GPIO_B);
    GPIO_clockGating(GPIO_C);
    GPIO_clockGating(GPIO_D);

	/*FTM0_CH0*/
	PORTC->PCR[1]   = PORT_PCR_MUX(0x4);
	/*FTM0_CH1*/
   	PORTC->PCR[2] = PORT_PCR_MUX(0x4);
	/*FTM3_CH4 */
	PORTC->PCR[8] = PORT_PCR_MUX(0x3);


    /* Init board hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    SystemCoreClockUpdate();

    GPIO_pinControlRegisterType pinControlRegisterMux1 = GPIO_MUX1;

    GPIO_pinControlRegister(GPIO_C,BIT1,&pinControlRegisterMux1);
    GPIO_dataDirectionPIN(GPIO_C,GPIO_OUTPUT,BIT1);
    GPIO_pinControlRegister(GPIO_B,BIT19,&pinControlRegisterMux1);
    GPIO_dataDirectionPIN(GPIO_B,GPIO_OUTPUT,BIT19);
    GPIO_pinControlRegister(GPIO_B,BIT18,&pinControlRegisterMux1);
    GPIO_dataDirectionPIN(GPIO_B,GPIO_OUTPUT,BIT18);

	GPIO_pinControlRegister(GPIO_B,BIT9,&pinControlRegisterMux1);
	GPIO_dataDirectionPIN(GPIO_B,GPIO_OUTPUT,BIT9);
	GPIO_pinControlRegister(GPIO_C,BIT17,&pinControlRegisterMux1);
	GPIO_dataDirectionPIN(GPIO_C,GPIO_OUTPUT,BIT17);
	GPIO_pinControlRegister(GPIO_C,BIT16,&pinControlRegisterMux1);
	GPIO_dataDirectionPIN(GPIO_C,GPIO_OUTPUT,BIT16);

    xTaskCreate(task_signal_1, "task_signal", 100, NULL, 3, NULL);
    xTaskCreate(task_signal_2, "task_signal_2", 100, NULL, 3, NULL);
    xTaskCreate(task_signal_3, "task_signal_3", 100, NULL, 3, NULL);

        /* Start scheduling. */
    vTaskStartScheduler();
    for (;;) {}
}
