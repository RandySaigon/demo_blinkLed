// where is the led connected?
// port:A
// pin: 5
#define PERIPH_BASE				(0X40000000UL) // initial address from memory map
#define AHB1PERIPH_OFFSET		(0X00020000UL) //
#define AHB1PERIPH_BASE			(PERIPH_BASE + AHB1PERIPH_OFFSET) // 0X4000 0000 + 0X0002 0000 = 0X4002 0000

#define GPIOA_OFFSET			(0x0000UL) //0x 0000 0000
										//because the starting point of GPIOA is the same as AHB1

#define GPIOA_BASE 				(AHB1PERIPH_BASE + GPIOA_OFFSET)//0X4002 0000 + 0x0000 0000 = 0X4002 0000
																//because the starting point of GPIOA is the same as AHB1

#define RCC_OFFSET				(0x3800UL) // 0x0000 3800
#define RCC_BASE				(AHB1PERIPH_BASE + RCC_OFFSET) //0X4002 0000 +  0x0000 3800 = 0X4002 3800

#define AHB1EN_R_OFFSET        (0x30UL)
#define RCC_AHB1EN_R            (*(volatile unsigned int *)(RCC_BASE + AHB1EN_R_OFFSET))

#define MODE_R_OFFSET			(0x00UL)
#define GPIOA_MODE_R			(*(volatile unsigned int *)(GPIOA_BASE + MODE_R_OFFSET))

#define OD_R_OFFSET             (0x14UL)
#define GPIOA_OD_R              (*(volatile unsigned int *)(GPIOA_BASE + OD_R_OFFSET))

#define GPIOAEN					(1U<<0) //0b 0000 0000 0000 0000 0000 0000 0000 0001

#define PIN5					(1U<<5)
#define LED_PIN					PIN5



/*
 * (1u<<10) set bit 10 to 1
 * &=~(1U<<11) clear bit 11 to 0 */
int main(void)
{
	/*1. Enable clock access to GPIOA*/
	RCC_AHB1EN_R |= GPIOAEN;
	/*2. Set PA5 as output pin*/
	GPIOA_MODE_R |= (1u<<10); //set bit 10 to 1
	GPIOA_MODE_R &=~(1U<<11);// clear bit 11 to 0
	while(1)
	{
		/*3. set PA5 high*/
		//GPIOA_OD_R |= LED_PIN;
        /*4. Experiment: toggle PA5*/
		GPIOA_OD_R ^= LED_PIN;
		int i;
		for( i =0; i<100000; i++){}
	}
}
