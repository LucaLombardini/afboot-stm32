#include <stdlib.h>
#include <stdint.h>

#include "stm32f4_regs.h"
#include "usart.h"
#include "gpio.h"
#include "start_kernel.h"
// CONTROLLA 
#define CONFIG_HSE_HZ	8000000
#define CONFIG_PLL_M	8
#define CONFIG_PLL_N	336
#define CONFIG_PLL_P	4
#define CONFIG_PLL_Q	7
#define PLLCLK_HZ (((CONFIG_HSE_HZ / CONFIG_PLL_M) * CONFIG_PLL_N) / CONFIG_PLL_P)
#if PLLCLK_HZ == 84000000
#define FLASH_LATENCY	2	// @ 84MHz FLASH_LATENCY = 2
#else
#error PLL clock does not match 84 MHz
#endif

static void *usart_base = (void *)USART2_BASE;
static void *gpio_base = (void *)GPIOA_BASE;

static void clock_setup(void)
{
	volatile uint32_t *RCC_CR = (void *)(RCC_CR_ADDRESS);
	volatile uint32_t *RCC_PLLCFGR = (void *)(RCC_PLLCFGR_ADDRESS);
	volatile uint32_t *RCC_CFGR = (void *)(RCC_CFGR_ADDRESS);
	volatile uint32_t *FLASH_ACR = (void *)(FLASH_ACR_ADDRESS);
	volatile uint32_t *RCC_AHB1ENR = (void *)(RCC_AHB1ENR_ADDRESS);
	volatile uint32_t *RCC_AHB2ENR = (void *)(RCC_AHB2ENR_ADDRESS);
	volatile uint32_t *RCC_APB1ENR = (void *)(RCC_APB1ENR_ADDRESS);
	volatile uint32_t *RCC_APB2ENR = (void *)(RCC_APB2ENR_ADDRESS);
	//volatile uint32_t *RCC_AHB1LPENR= (void *)(RCC_AHB1LPENR_ADDRESS);
	uint32_t val;

	*RCC_CR |= RCC_CR_HSEON;
	while (!(*RCC_CR & RCC_CR_HSERDY)) {
	}

	val = *RCC_CFGR;
	val &= ~RCC_CFGR_HPRE_MASK;
	//val |= 0 << 4; // not divided
	val &= ~RCC_CFGR_PPRE1_MASK;
	val |= 0x4 << 10; // divided by 2
	val &= ~RCC_CFGR_PPRE2_MASK;
	//val |= 0x4 << 13; // not divided
	*RCC_CFGR = val;

	val = 0;
	val |= RCC_PLLCFGR_PLLSRC_HSE;
	val |= CONFIG_PLL_M;
	val |= CONFIG_PLL_N << 6;
	val |= ((CONFIG_PLL_P >> 1) - 1) << 16;
	val |= CONFIG_PLL_Q << 24;
	*RCC_PLLCFGR = val;

	*RCC_CR |= RCC_CR_PLLON;
	while (!(*RCC_CR & RCC_CR_PLLRDY));

	*FLASH_ACR = FLASH_ACR_ICEN | FLASH_ACR_PRFTEN | FLASH_LATENCY;

	*RCC_CFGR &= ~RCC_CFGR_SW_MASK;
	*RCC_CFGR |= RCC_CFGR_SW_PLL;
	while ((*RCC_CFGR & RCC_CFGR_SWS_MASK) != RCC_CFGR_SWS_PLL) {
	}

	/*  Enable all clocks, unused ones will be gated at end of kernel boot */
	*RCC_AHB1ENR |= 0x0060109f;
	// STM32 has no random number, hash nor crypto units (0xf1)
	*RCC_AHB2ENR |= 0x80;	
	*RCC_APB1ENR |= 0x10e2c80f;
	*RCC_APB2ENR |= 0x00077931;

}


// not on 401
static void fmc_wait_busy(void)
{
	volatile uint32_t *FMC_SDSR = (void *)(FMC_BASE + 0x158);

	while ((*FMC_SDSR & FMC_SDSR_BUSY)) {
	}
}

int main(void)
{
	volatile uint32_t *FLASH_KEYR = (void *)(FLASH_KEYR_ADDRESS);
	volatile uint32_t *FLASH_CR = (void *)(FLASH_CR_ADDRESS);
	//volatile uint32_t *FMC_SDCR1 = (void *)(FMC_BASE + 0x140);
	//volatile uint32_t *FMC_SDCR2 = (void *)(FMC_BASE + 0x144);
	//volatile uint32_t *FMC_SDTR1 = (void *)(FMC_BASE + 0x148);
	//volatile uint32_t *FMC_SDTR2 = (void *)(FMC_BASE + 0x14C);
	//volatile uint32_t *FMC_SDCMR = (void *)(FMC_BASE + 0x150);
	//volatile uint32_t *FMC_SDRTR = (void *)(FMC_BASE + 0x154);
	volatile uint32_t *SYSCFG_MEMRMP = (void *)(SYSCFG_BASE + 0x00);
	int i;

	if (*FLASH_CR & FLASH_CR_LOCK) {
		*FLASH_KEYR = 0x45670123;
		*FLASH_KEYR = 0xCDEF89AB;
	}
	*FLASH_CR &= ~(FLASH_CR_ERRIE | FLASH_CR_EOPIE | FLASH_CR_PSIZE_MASK);
	*FLASH_CR |= FLASH_CR_PSIZE_X32;
	*FLASH_CR |= FLASH_CR_LOCK;

	clock_setup();

	//gpio_set_fmc(gpio_base, 'B', 5);
	//gpio_set_fmc(gpio_base, 'B', 6);
	//gpio_set_fmc(gpio_base, 'C', 0);
	//gpio_set_fmc(gpio_base, 'D', 0);
	//gpio_set_fmc(gpio_base, 'D', 1);
	//gpio_set_fmc(gpio_base, 'D', 8);
	//gpio_set_fmc(gpio_base, 'D', 9);
	//gpio_set_fmc(gpio_base, 'D', 10);
	//gpio_set_fmc(gpio_base, 'D', 14);
	//gpio_set_fmc(gpio_base, 'D', 15);
	//gpio_set_fmc(gpio_base, 'E', 0);
	//gpio_set_fmc(gpio_base, 'E', 1);
	//gpio_set_fmc(gpio_base, 'E', 7);
	//gpio_set_fmc(gpio_base, 'E', 8);
	//gpio_set_fmc(gpio_base, 'E', 9);
	//gpio_set_fmc(gpio_base, 'E', 10);
	//gpio_set_fmc(gpio_base, 'E', 11);
	//gpio_set_fmc(gpio_base, 'E', 12);
	//gpio_set_fmc(gpio_base, 'E', 13);
	//gpio_set_fmc(gpio_base, 'E', 14);
	//gpio_set_fmc(gpio_base, 'E', 15);
	//gpio_set_fmc(gpio_base, 'F', 0);
	//gpio_set_fmc(gpio_base, 'F', 1);
	//gpio_set_fmc(gpio_base, 'F', 2);
	//gpio_set_fmc(gpio_base, 'F', 3);
	//gpio_set_fmc(gpio_base, 'F', 4);
	//gpio_set_fmc(gpio_base, 'F', 5);
	//gpio_set_fmc(gpio_base, 'F', 11);
	//gpio_set_fmc(gpio_base, 'F', 12);
	//gpio_set_fmc(gpio_base, 'F', 13);
	//gpio_set_fmc(gpio_base, 'F', 14);
	//gpio_set_fmc(gpio_base, 'F', 15);
	//gpio_set_fmc(gpio_base, 'G', 0);
	//gpio_set_fmc(gpio_base, 'G', 1);
	//gpio_set_fmc(gpio_base, 'G', 4);
	//gpio_set_fmc(gpio_base, 'G', 5);
	//gpio_set_fmc(gpio_base, 'G', 8);
	//gpio_set_fmc(gpio_base, 'G', 15);
	//*FMC_SDCR1 = 0x00001800;
	//*FMC_SDCR2 = 0x000019D4;
	//*FMC_SDTR1 = 0x00106000;
	//*FMC_SDTR2 = 0x00010361;

	//fmc_wait_busy();
	//*FMC_SDCMR = 0x00000009; // clock
	//for (i = 0; i < 50000000; i++) { // 10 ms
	//	asm volatile ("nop");
	//}
	//fmc_wait_busy();
	//*FMC_SDCMR = 0x0000000A; // PALL
	//fmc_wait_busy();
	//*FMC_SDCMR = 0x000000EB; // auto-refresh
	//fmc_wait_busy();
	//*FMC_SDCMR = 0x0004600C; // external memory mode
	//*FMC_SDRTR = 1386 << 1; // refresh rate
	//fmc_wait_busy();

	//*SYSCFG_MEMRMP = SYSCFG_MEMRMP_SWP_FMC << 10;

	//gpio_set_usart(gpio_base, 'A', 9, 7);
	//gpio_set_usart(gpio_base, 'A', 10, 7);

	gpio_set_usart(gpio_base, 'A', 2, 7);
	gpio_set_usart(gpio_base, 'A', 3, 7);
	
	usart_setup(usart_base, PLLCLK_HZ/2);
	usart_putch(usart_base, '.');

	start_kernel();

	return 0;
}

static void noop(void)
{
	usart_putch(usart_base, 'E');
	while (1) {
	}
}

extern unsigned int _end_text;
extern unsigned int _start_data;
extern unsigned int _end_data;
extern unsigned int _start_bss;
extern unsigned int _end_bss;

void reset(void)
{
	unsigned int *src, *dst;

	asm volatile ("cpsid i");

	src = &_end_text;
	dst = &_start_data;
	while (dst < &_end_data) {
		*dst++ = *src++;
	}

	dst = &_start_bss;
	while (dst < &_end_bss) {
		*dst++ = 0;
	}

	main();
}

extern unsigned long _stack_top;

__attribute__((section(".vector_table")))
void (*vector_table[16 + 91])(void) = {
	(void (*))&_stack_top,
	reset,
	noop,
	noop,
	noop,
	noop,
	noop,
	NULL,
	NULL,
	NULL,
	NULL,
	noop,
	noop,
	NULL,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
	noop,
};
