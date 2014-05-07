#include "initial.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_misc.h"
#include "stdlib.h"

uint16_t value;
uint8_t f;
int a, i;

//Matrix of switching on and off RGB LEDS - 9 RGB LEDs; 7 different colors
int raspored [9][7] = {{GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9, GPIO_Pin_7, GPIO_Pin_8, GPIO_Pin_7|GPIO_Pin_8, GPIO_Pin_8|GPIO_Pin_9, GPIO_Pin_7|GPIO_Pin_9, GPIO_Pin_9},
                       {GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6, GPIO_Pin_4, GPIO_Pin_5, GPIO_Pin_4|GPIO_Pin_5, GPIO_Pin_5|GPIO_Pin_6, GPIO_Pin_4|GPIO_Pin_6, GPIO_Pin_6},
											 {GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12, GPIO_Pin_10, GPIO_Pin_11, GPIO_Pin_10|GPIO_Pin_11, GPIO_Pin_11|GPIO_Pin_12, GPIO_Pin_10|GPIO_Pin_12, GPIO_Pin_12},
											 {GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12, GPIO_Pin_10, GPIO_Pin_11, GPIO_Pin_10|GPIO_Pin_11, GPIO_Pin_11|GPIO_Pin_12, GPIO_Pin_10|GPIO_Pin_12, GPIO_Pin_12},
											 {GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15, GPIO_Pin_13, GPIO_Pin_14, GPIO_Pin_13|GPIO_Pin_14, GPIO_Pin_14|GPIO_Pin_15, GPIO_Pin_13|GPIO_Pin_15, GPIO_Pin_15},
											 {GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9, GPIO_Pin_7, GPIO_Pin_8, GPIO_Pin_7|GPIO_Pin_8, GPIO_Pin_8|GPIO_Pin_9, GPIO_Pin_7|GPIO_Pin_9, GPIO_Pin_9},
											 {GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5, GPIO_Pin_3, GPIO_Pin_4, GPIO_Pin_3|GPIO_Pin_4, GPIO_Pin_4|GPIO_Pin_5, GPIO_Pin_3|GPIO_Pin_5, GPIO_Pin_5},
											 {GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15, GPIO_Pin_13, GPIO_Pin_14, GPIO_Pin_13|GPIO_Pin_14, GPIO_Pin_14|GPIO_Pin_15, GPIO_Pin_13|GPIO_Pin_15, GPIO_Pin_15},
											 {GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2, GPIO_Pin_0, GPIO_Pin_1, GPIO_Pin_0|GPIO_Pin_1, GPIO_Pin_1|GPIO_Pin_2, GPIO_Pin_0|GPIO_Pin_2, GPIO_Pin_2}};

//***********************************************
//Delay function - dummy way
//***********************************************
void delay(int broj) {
	
	int i;
	for(i=0; i<broj; i++);
	}

//***********************************************
//Resolving debounce from button
//***********************************************
int debounce() {
	
	uint8_t stanje = 0;
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3)) {
		delay(250);
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3))
			stanje = 1;
		}
	return stanje;
	}


//***********************************************
//RGB LEDs switching different colors function
//***********************************************
void pali_ledicu(GPIO_TypeDef* GPIOx, uint8_t led) {
	
	a = rand() % 128;
	if(a>=1 && a<=73) {
		GPIO_ResetBits(GPIOx, raspored[led][0]);
		GPIO_SetBits(GPIOx, raspored[led][0]);
	}
	else if(a>=74 && a<=78){
		GPIO_ResetBits(GPIOx, raspored[led][0]);
		GPIO_SetBits(GPIOx, raspored[led][1]);
	}
	else if(a>=79 && a<=94){
		GPIO_ResetBits(GPIOx, raspored[led][0]);
		GPIO_SetBits(GPIOx, raspored[led][2]);
	}
	else if(a>=95 && a<=107) {
		GPIO_ResetBits(GPIOx, raspored[led][0]);
		GPIO_SetBits(GPIOx, raspored[led][3]);
	}
	else if(a>=108 && a<=118) {
		GPIO_ResetBits(GPIOx, raspored[led][0]);
		GPIO_SetBits(GPIOx, raspored[led][4]);
	}
	else if(a>=119 && a<=126){
		GPIO_ResetBits(GPIOx, raspored[led][0]);
		GPIO_SetBits(GPIOx, raspored[led][5]);
	}
	else if(a==127 || a==0){
		GPIO_ResetBits(GPIOx, raspored[led][0]);
		GPIO_SetBits(GPIOx, raspored[led][6]);
	}
}

int main() {
	
	f = 0;  //flag
	i = 0;
	
	//Initialise LEDs, button and interrupts
	init_rgb();
	init_tipka();
	init_inttipka();
	
	//Check if all LEDs are connected correctly
	GPIO_SetBits(GPIOB, GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9
	                    |GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
	GPIO_SetBits(GPIOC, GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|
	                    GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|
											GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
	delay(5000000);
	GPIO_ResetBits(GPIOB, GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9
	                    |GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
	GPIO_ResetBits(GPIOC, GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|
	                      GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|
											  GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
	
	while(1) {
		
		//i - for seting the seed of rand function; 
		if(!f)
			i++;
		
		}
	}

//Interrupt vector for button
void EXTI2_3_IRQHandler(void) {
		
		if (EXTI_GetITStatus(EXTI_Line3) != RESET) {
			
			//Is it really on
			if(debounce()) {
				
				//set seed for function rand(); sets only once, the first time button is pressed
				//
				if(!f) {
					srand(i);
					f=1;
				}	
				
				//Visual effect - turn LEDs all off and turn on column by column
				GPIO_ResetBits(GPIOB, GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9
	                    |GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
				GPIO_ResetBits(GPIOC, GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|
	                    GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|
											GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
				delay(2000000);
				//turn on first column
				pali_ledicu(GPIOB, 0);
				pali_ledicu(GPIOB, 1);
				pali_ledicu(GPIOC, 2);
				delay(2000000);
				//turn on second column
				pali_ledicu(GPIOB, 3);
				pali_ledicu(GPIOB, 4);
				pali_ledicu(GPIOC, 5);
				delay(2000000);
				//turn on third column
				pali_ledicu(GPIOC, 6);
				pali_ledicu(GPIOC, 7);
				pali_ledicu(GPIOC, 8);
				
			}
			//clear interrupt bit
			EXTI_ClearITPendingBit(EXTI_Line3);
	}
}
