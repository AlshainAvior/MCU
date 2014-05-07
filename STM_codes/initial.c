#include "stm32f0xx_gpio.h"
#include "initial.h"
#include "stm32f0xx_exti.h"
#include "stm32f0xx_misc.h"

//********************************************
// Initialise GPIO for LEDS
//********************************************
void init_rgb(void) {
	
	GPIO_InitTypeDef ledice;
	
	//Peripheral clock enable
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC, ENABLE);
	
	GPIO_StructInit(&ledice);
	ledice.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 |    //LED1
	                  GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 |    //LED2
										GPIO_Pin_10| GPIO_Pin_11| GPIO_Pin_12|    //LED4
										GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;    //LED5
	ledice.GPIO_Mode = GPIO_Mode_OUT;
	ledice.GPIO_Speed = GPIO_Speed_Level_3;
	ledice.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOB, &ledice);
	
	ledice.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|       //LED9
	                  GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|       //LED7
										GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|       //LED6
										GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|    //LED3
										GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;    //LED8
	GPIO_Init(GPIOC, &ledice);
	
	}

//********************************************
//Initialise GPIO for button
//********************************************
void init_tipka(void) {
	
	GPIO_InitTypeDef tipka;
	
	//Peripheral clock enable
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	GPIO_StructInit(&tipka);
	tipka.GPIO_Pin = GPIO_Pin_3;
	tipka.GPIO_Mode = GPIO_Mode_IN;
	tipka.GPIO_Speed = GPIO_Speed_Level_2;
	tipka.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &tipka);
	}

//********************************************
//Initialise extern interrupt from button
//********************************************
void init_inttipka(void) {
	
	NVIC_InitTypeDef nvic_inttipka;
	EXTI_InitTypeDef interr_tipka;
	
	//Peripheral clock enable
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	//PB3 interrupt enable
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource3);
	
	//PB3 external interrupt configuration
	EXTI_StructInit(&interr_tipka);
	interr_tipka.EXTI_Line = EXTI_Line3;
	interr_tipka.EXTI_Mode = EXTI_Mode_Interrupt;
	interr_tipka.EXTI_Trigger = EXTI_Trigger_Rising;
	interr_tipka.EXTI_LineCmd = ENABLE;
	EXTI_Init(&interr_tipka);
	
	//NVIC configuration for PB3
	nvic_inttipka.NVIC_IRQChannel = EXTI2_3_IRQn;
	nvic_inttipka.NVIC_IRQChannelPriority = 0;
	nvic_inttipka.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_inttipka);
	}
