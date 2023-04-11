

#include "stm32f10x.h"
#include "mfmc_io_leds.h"

#ifdef DEBUGGING
#include <stdio.h>
#endif

/* Системное время в мс. */
volatile uint32_t SysTime = 0;

void RCC_Init(void);
void SysTick_Init(void);
void HardFault_Handler(void) __attribute__((naked));
extern void initialise_monitor_handles(void);

int main()
{
	#ifdef DEBUGGING
	initialise_monitor_handles();
	#endif;
	RCC_Init();
	SysTick_Init();
	MFMC_IO_LEDS_Init();

	MFMC_IO_LEDS_SetMode(MFMC_IO_LEDS_D1, MFMC_IO_LEDS_MODE_OFF);
	MFMC_IO_LEDS_SetMode(MFMC_IO_LEDS_D2, MFMC_IO_LEDS_MODE_ON);
	MFMC_IO_LEDS_SetMode(MFMC_IO_LEDS_D3, MFMC_IO_LEDS_MODE_ONE_BLINK);
	MFMC_IO_LEDS_SetMode(MFMC_IO_LEDS_D4, MFMC_IO_LEDS_MODE_TWO_BLINK);
	MFMC_IO_LEDS_SetMode(MFMC_IO_LEDS_D5, MFMC_IO_LEDS_MODE_THREE_BLINK);
	MFMC_IO_LEDS_SetMode(MFMC_IO_LEDS_D6, MFMC_IO_LEDS_MODE_FOUR_BLINK);
	MFMC_IO_LEDS_SetMode(MFMC_IO_LEDS_D7, MFMC_IO_LEDS_MODE_LONG_BLINK);

	while (1)
	{
		MFMC_IO_LEDS_Control();
	}
}

void RCC_Init(void)
{
	RCC_HSEConfig(RCC_HSE_ON);
	RCC_PLLConfig(RCC_PLLSource_HSE_Div2, RCC_PLLMul_9);
	//RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
	RCC_PLLCmd(ENABLE);
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK1Config(RCC_HCLK_Div2);
	RCC_PCLK2Config(RCC_HCLK_Div1);
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

	uint8_t SysClkSource = RCC_GetSYSCLKSource();

	#ifdef DEBUGGING
	printf("System clock = %d", SysClkSource);
	#endif

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
}

void SysTick_Init(void)
{
	/* SysTick->LOAD = 72000UL;
	SysTick->CTRL = (SysTick_CTRL_ENABLE | SysTick_CTRL_TICKINT | SysTick_CTRL_CLKSOURCE);
	NVIC_EnableIRQ(SysTick_IRQn); */
	SysTick_Config(72000UL);
	// NVIC_SetPriority (SysTick_IRQn, 0);
	__enable_irq();
	//__disable_irq();
}
void millisCount(void)
{
	SysTime++;
}
uint32_t MFMC_IO_LEDS_GetMs(void)
{
	return SysTime;
}

/** ---------------------------------------------------------------------------
 * @brief prvGetRegistersFromStack
 * @param pulFaultStackAddress
 */

void prvGetRegistersFromStack(uint32_t *pulFaultStackAddress)
{
	/* These are volatile to try and prevent the compiler/linker optimising them
	away as the variables never actually get used.  If the debugger won't show the
	values of the variables, make them global my moving their declaration outside
	of this function. */
	volatile uint32_t cfsr = SCB->CFSR;
	volatile uint32_t hfsr = SCB->HFSR;
	volatile uint32_t mmfar = SCB->MMFAR;
	volatile uint32_t bfar = SCB->BFAR;

	volatile uint32_t r0;
	volatile uint32_t r1;
	volatile uint32_t r2;
	volatile uint32_t r3;
	volatile uint32_t r12;
	volatile uint32_t lr;  // Link register.
	volatile uint32_t pc;  // Program counter.
	volatile uint32_t psr; // Program status register.
	// volatile uint32_t counter;

	r0 = pulFaultStackAddress[0];
	r1 = pulFaultStackAddress[1];
	r2 = pulFaultStackAddress[2];
	r3 = pulFaultStackAddress[3];

	r12 = pulFaultStackAddress[4];
	lr = pulFaultStackAddress[5];
	pc = pulFaultStackAddress[6];
	psr = pulFaultStackAddress[7];

	#ifdef DEBUGGING
	printf("\n> Hard Error ");
	printf("\n    SCB->CFSR=0x%08lX SCB->HFSR=0x%08lX SCB->MMFAR=0x%08lX SCB->BFAR=0x%08lX", cfsr, hfsr, mmfar, bfar);
	printf("   r0=0x%08lX r1=0x%08lX r2=0x%08lX r3=0x%08lX r12=0x%08lX", r0, r1, r2, r3, r12);
	printf("\n    lr=0x%08lX pc=0x%08lX psr=0x%08lX", lr, pc, psr);
	// printf("\n    pc=0x%08lX", pc);

	// printf("Просто какой-то текст");

	#endif

	volatile uint32_t cycleCounter = 0;

	// When the following line is hit, the variables contain the register values.
	for (;;)
	{
		// digital_io_write(GPIO_TypeDef *port, uint32_t pin, uint32_t val);
		cycleCounter++;
		/* digitalWrite (LED_STATUS, 1);
		digitalWrite (CPU, 0);
		for (counter = 0; counter < 1000000; counter++) {};
		digitalWrite (LED_STATUS, 0);
		digitalWrite (CPU, 1);
		for (counter = 0; counter < 1000000; counter++) {}; */
	}
}
/** ---------------------------------------------------------------------------
 * @brief HardFault_Handler  The fault handler implementation calls a
 * function called prvGetRegistersFromStack().
 */
void HardFault_Handler(void)
{
	__asm volatile(
		" tst lr, #4                                                \n"
		" ite eq                                                    \n"
		" mrseq r0, msp                                             \n"
		" mrsne r0, psp                                             \n"
		" ldr r1, [r0, #24]                                         \n"
		" ldr r2, handler2_address_const                            \n"
		" bx r2                                                     \n"
		" handler2_address_const: .word prvGetRegistersFromStack    \n");
}
