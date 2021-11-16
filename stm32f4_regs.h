#ifndef _STM32F4_REGS_H
#define _STM32F4_REGS_H

/* NOTE: not all the bits are defined/used in all microcontrollers, some belong
 * to a different family and may have more/less hardware resources.
 * Use these definitions with care! Follow the documentation!
 *
 * Documentation taken from STMicroelectronics.
 */


/* RCC_BASE: starting address of all the configuration registers related to 
 * Reset and Clock Control 
 */
#define RCC_BASE	0x40023800


/* RCC_CR: Reset and Clock Control mapping register ############################
 *
 * 29 - PLLSAIRDY: PLLSAI clock ready flag (set by HW when PLLSAI is locked)
 * 	0: PLLSAI unlocked
 * 	1: PLLSAI locked
 * 28 - PLLSAION: PLLSAI enable (set/clr by SW to enable PLLSAI, clr by HW on 
 * 	Stop or Standby mode)
 * 	0: PLLSAI OFF
 * 	1: PLLSAI ON
 * 25 - PLLRDY: Main PLL (PLL) clock ready flag (set by HW when PLL is locked)
 * 	0: unlocked
 * 	1: locked
 * 24 - PLLON: Main PLL (PLL) enable (set/clr by SW to enable PLL, clr by HW 
 * 	on Stop or Standby mode. This pin cannot be reset if PLL clock is used
 * 	as the system clock!)
 * 	0: PLL OFF
 * 	1: PLL ON
 * 17 - HSERDY: HSE clock ready flag (set by HW)
 * 	0: HSE oscillator not ready
 * 	1: HSE oscillator ready
 * 16 - HSEON: HSE clock enable (set/clr by SW)
 * 	0: HSE oscillator OFF
 * 	1: HSE oscillator ON
 */
#define RCC_CR_OFFSET 0x00
#define RCC_CR_ADDRESS (RCC_BASE + RCC_CR_OFFSET)
#define RCC_CR_HSEON	(1 << 16)
#define RCC_CR_HSERDY	(1 << 17)
#define RCC_CR_PLLON	(1 << 24)
#define RCC_CR_PLLRDY	(1 << 25)
#define RCC_CR_SAION	(1 << 28) // not on 401
#define RCC_CR_SAIRDY	(1 << 29) // not on 401


/* RCC_PLLCFGR: PLL configuration register #####################################
 *
 * 22 - PLLSRC: Main PLL and audio PLL (PLLI2S) entry clock source. Writable 
 * 	only when both PLL and PLLI2S are disabled.
 * 	0: HSI clock selected as PLL and PLLI2S clock entry
 * 	1: HSE oscillator clock selected as PLL and PLLI2S clock entry
 */
#define RCC_PLLCFGR_OFFSET 0x04
#define RCC_PLLCFGR_ADDRESS (RCC_BASE + RCC_PLLCFGR_OFFSET)
#define RCC_PLLCFGR_PLLSRC_HSE	(1 << 22)


/* RCC_CFGR: RCC clock and configuration register ##############################
 * 
 * [15:13]-PPRE2: APB2 high-speed prescaler (Set and cleared by software to 
 * 	control APB high-speed clock division factor. The software has to set 
 * 	these bits correctly not to exceed 84 MHz on this domain. The clocks are
 * 	divided with the new prescaler factor from 1 to 16 AHB cycles after 
 * 	PPRE2 write)
 * 	0x0: AHB clock not divided
 * 	...
 * 	0x3: AHB clock not divided
 * 	0x4: AHB clock divided by 2
 * 	0x5: AHB clock divided by 4
 * 	0x6: AHB clock divided by 8
 * 	0x7: AHB clock divided by 16
 * [12:10]-PPRE1: APB1 low speed prescaler (Set and cleared by software to 
 * 	control APB low-speed clock division factor. The software has to set 
 * 	these bits correctly not to exceed 42 MHz on this domain. The clocks are
 * 	divided with the new prescaler factor from 1 to 16 AHB cycles after 
 * 	PPRE1 write)
 * 	0x0: AHB clock not divided
 * 	...
 * 	0x3: AHB clock not divided
 * 	0x4: AHB clock divided by 2
 * 	0x5: AHB clock divided by 4
 * 	0x6: AHB clock divided by 8
 * 	0x7: AHB clock divided by 16
 * [7:4] - HPRE: AHB prescaler (Set and cleared by software to control AHB clock
 * 	division factor. The clocks are divided with the new prescaler factor 
 * 	from 1 to 16 AHB cycles after HPRE write)
 * 	0x0: system clock not divided
 * 	...
 * 	0x7: system clock not divided
 * 	0x8: system clock divided by 2
 * 	0x9: system clock divided by 4
 * 	0xA: system clock divided by 8
 * 	0xB: system clock divided by 16
 * 	0xC: system clock divided by 64
 * 	0xD: system clock divided by 128
 * 	0xE: system clock divided by 256
 * 	0xF: system clock divided by 512
 * [3:2] - SWS: System clock switch status (Set and cleared by hardware to 
 * 	indicate which clock source is used as the system clock)
 * 	0x0: HSI oscillator used as the system clock
 * 	0x1: HSE oscillator used as the system clock
 * 	0x2: PLL used as the system clock
 * 	0x3: not applicable
 * [1:0] - SW: System clock switch (Set and cleared by software to select the 
 * 	system clock source. Set by hardware to force the HSI selection when 
 * 	leaving the Stop or Standby mode or in case of failure of the HSE  
 * 	oscillator used directly or indirectly as the system clock)
 * 	0x0: HSI oscillator selected as system clock
 * 	0x1: HSE oscillator selected as system clock
 * 	0x2: PLL selected as system clock
 * 	0x3: not allowed
 */
#define RCC_CFGR_OFFSET 0x08
#define RCC_CFGR_ADDRESS (RCC_BASE + RCC_CFGR_OFFSET)
#define RCC_CFGR_SW_PLL		(0x2 << 0)
#define RCC_CFGR_SW_MASK	(0x3 << 0) // used to clear by ... &= ~(...)
#define RCC_CFGR_SWS_PLL	(0x2 << 2)
#define RCC_CFGR_SWS_MASK	(0x3 << 2) // used to clear
#define RCC_CFGR_HPRE_MASK	(0xf << 4) // used to clear
#define RCC_CFGR_PPRE1_MASK	(0x7 << 10)
#define RCC_CFGR_PPRE2_MASK	(0x7 << 13)


/* RCC_DCKCFGR: Dedicated Clocks Configuration Register ########################
 *
 * 28 - SDIOSEL: SDIO clock source selection (Set and reset by software)
 *	0: 48 MHz clock is selected as SDIO clock
 *	1: System clock is selected  as SDIO clock
 * 27 - 48MSEL: 48 MHz clock source selection (Set and reset by software)
 *	0: 48 MHz clock from PLL is selected
 *	1: 48 MHz clock from PLLSAI is selected
 */
#define RCC_DCKCFGR_OFFSET 0x8C
#define RCC_DCKCFGR_ADDRESS (RCC_BASE + RCC_DCKCFGR_OFFSET)
#define RCC_DCKCFGR_48SRC_SAI	(1 << 27) // not on 401
#define RCC_DCKCFGR_SDIO48	(1 << 28) // not on 401


/* RCC_AHB1ENR: AHB1 peripheral clock enable register ##########################
 *  6 - GPIOGEN: IO port G clock enable (Set and cleared by software)
 *	0: IO port G clock disabled
 *	1: IO port G clock enabled
 */
#define RCC_AHB1ENR_OFFSET 0x30
#define RCC_AHB1ENR_ADDRESS (RCC_BASE + RCC_AHB1ENR_OFFSET)
#define RCC_AHB1ENR_GPIOGEN	(1 << 6) // not on 401


/* RCC_AHB1LPENR: AHB1 peripheral clock enable in low power mode register ######
 *
 * 30 - OTGHSULPILPEN: USB OTG HS ULPI clock enable during Sleep mode (Set and
 * 	cleared by software. This bit must be cleared when the OTG_HS is used in
 * 	FS mode)
 * 	0: USB OTG HS ULPI clock disabled during Sleep mode
 * 	1: USB OTG HS ULPI clock enabled during Sleep mode
 */
#define RCC_AHB1LPENR_OFFSET 0x50
#define RCC_AHB1LPENR_ADDRESS (RCC_BASE + RCC_AHB1LPENR_OFFSET)
#define RCC_AHB1LPENR_OTGHSULPILPEN	(1 << 30) // not on 401


/* RCC_AHB2ENR: AHB2 peripheral clock enable register ##########################
 *
 *  7 - OTGFSEN: USB OTG FS enable
 */
#define RCC_AHB2ENR_OFFSET 0x34
#define RCC_AHB2ENR_ADDRESS (RCC_BASE + RCC_AHB2ENR_OFFSET)
#define RCC_AHB2ENR_OTGFSEN_EN (1 << 7)

/* RCC_AHB3ENR: AHB3 peripheral clock enable register ##########################
 *
 *  0 - FMCEN: Flexible memory controller module clock enable (This bit is set 
 *  	and cleared by software)
 *  	0: FMC module clock disabled
 *  	1: FMC module clock enabled
 */
#define RCC_AHB3ENR_OFFSET 0x38
#define RCC_AHB3ENR_ADDRESS (RCC_BASE + RCC_AHB3ENR_OFFSET)
#define RCC_AHB3ENR_FMC		(1 << 0) // not on 401


/* RCC_APB1ENR: APB1 peripheral clock enable register ##########################
 */
#define RCC_APB1ENR_OFFSET 0x40
#define RCC_APB1ENR_ADDRESS (RCC_BASE + RCC_APB1ENR_OFFSET)


/* RCC_APB2ENR: APB2 peripheral clock enable register ##########################
 *
 * 14 - SYSCFGEN: System configuration controller clock enable (Set and cleared
 * 	by software)
 * 	0: System configuration controller clock disabled
 * 	1: System configuration controller clock enabled
 *  4 - USART1EN: USART1 clock enable (Set and cleared by software)
 *  	0: USART1 clock disabled
 *  	1: USART1 clock enabled
 */
#define RCC_APB2ENR_OFFSET 0X44
#define RCC_APB2ENR_ADDRESS (RCC_BASE + RCC_APB2ENR_OFFSET)
#define RCC_APB2ENR_USART1EN	(1 << 4)
#define RCC_APB2ENR_SYSCFGEN	(1 << 14)


/* FLASH_BASE: starting address of all the configuration registers related to 
 * the flash interface
 */
#define FLASH_BASE	0x40023C00


/* FLASH_ACR: Flash access control register ####################################
 *
 *  9 - ICEN: Instruction cache enable
 *  	0: Instruction cache is disabled
 *  	1: Instruction cache is enabled
 *  8 - PRFTEN: Prefetch enable
 *  	0: Prefetch is disabled
 *  	1: Prefetch is enabled
 */
#define FLASH_ACR_OFFSET 0x0
#define FLASH_ACR_ADDRESS (FLASH_BASE + FLASH_ACR_OFFSET)
#define FLASH_ACR_PRFTEN	(1 << 8)
#define FLASH_ACR_ICEN		(1 << 9)


/* FLASH_KEYR: Flash key register ##############################################
 */
#define FLASH_KEYR_OFFSET 0x04
#define FLASH_KEYR_ADDRESS (FLASH_BASE + FLASH_KEYR_OFFSET)


/* FLASH_CR: Flash control register ############################################
 *
 * 31 - LOCK: lock (Write to 1 only. When it is set, this bit indicates that the
 * 	FLASH_CR register is locked. It is cleared by hardware after detecting
 * 	the unlock sequence. In the event of an unsuccessful unlock operation, 
 * 	this bit remains set until the next reset)
 * 25 - ERRIE: Error interrupt enable (This bit enables the interrupt generation
 * 	when the OPERR bit in the FLASH_SR register is set to 1)
 * 	0: Error interrupt generation disabled
 * 	1: Error interrupt generation enable
 * 24 - EOPIE: End of operation interrupt enable (This bit enables the interrupt
 * 	generation when the EOP bit in the FLASH_SR register goes to 1)
 * 	0: Interrupt generation disabled
 * 	1: Interrupt generation enabled
 * [9:8]PSIZE: Program size (program parallelism)
 * 	0x0: program x8
 * 	0x1: program x16
 * 	0x2: program x32
 * 	0x0: program x64
 */
#define FLASH_CR_OFFSET 0x10
#define FLASH_CR_ADDRESS (FLASH_BASE + FLASH_CR_OFFSET)
#define FLASH_CR_PSIZE_X32	0x2
#define FLASH_CR_PSIZE_MASK	0x3
#define FLASH_CR_EOPIE		(1 << 24)
#define FLASH_CR_ERRIE		(1 << 25)
#define FLASH_CR_LOCK		(1UL << 31)


/* USART3_BASE: starting address of all the configuration registers related to 
 * the usart3 peripheral
 */
#define USART3_BASE	0x40004800 // not on 401



/* USART1_BASE: starting address of all the configuration registers related to 
 * the usart1 peripheral
 */
#define USART1_BASE	0x40011000
#define USART2_BASE	0x40004400



/* GPIOA_BASE: starting address of all the configuration registers related to 
 * the gpioa peripheral
 */
#define GPIOA_BASE	0x40020000



/* FMC_BASE: starting address of all the configuration registers related to 
 * the FSMC peripheral
 */
#define FMC_BASE	0xA0000000 // not on 401



/* QUADSPI_BASE: starting address of all the configuration registers related to 
 * the 	QUAD-SPI peripheral
 */
#define QUADSPI_BASE	0xA0001000 // not on 401

#define FMC_SDSR_BUSY	(1 << 5) // not on 401



/* SYSCFG_BASE: starting address of all the configuration registers related to 
 * the system configurations
 */
#define SYSCFG_BASE	0x40013800

#define SYSCFG_MEMRMP_ADDRESS SYSCFG_BASE
#define SYSCFG_MEMRMP_MAIN_FLASH_MEM 0x0
#define SYSCFG_MEMRMP_SWP_FMC	0x1


#endif /* _STM32F4_REGS_H */
