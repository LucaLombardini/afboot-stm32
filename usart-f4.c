#include <stdint.h>


/* USART_SR: Usart status register #############################################
 *  7 - TXE: Transmit data register empty
 */
#define USART_SR_TXE	(1 << 7)


/* USART_CR1: Usart control register 1 #########################################
 * 13 - UE: Usart enable
 *  3 - TE: Transmitter enable
 *  2 - RE: Receiver enable
 */
#define USART_CR1_RE	(1 << 2)
#define USART_CR1_TE	(1 << 3)
#define USART_CR1_UE	(1 << 13)

void usart_setup(void *base, uint32_t clk_freq)
{
	// Baud rate register
	volatile uint32_t *USART_BRR = base + 0x08;
	// Usart control registers
	volatile uint32_t *USART_CR1 = base + 0x0C;
	volatile uint32_t *USART_CR2 = base + 0x10;
	volatile uint32_t *USART_CR3 = base + 0x14;
	uint32_t int_div, frac_div, val;

	// Configure USART to be bidirectional
	*USART_CR1 = USART_CR1_TE | USART_CR1_RE;
	// Multiple configs done, see Reference manual
	*USART_CR2 = 0;
	*USART_CR3 = 0;


	// Baud rate setting
	// DIV_mantissa setting
	int_div = (25 * clk_freq) / (4 * 115200);
	val = (int_div / 100) << 4;
	// DIV_fraction setting
	frac_div = int_div - 100 * (val >> 4);
	val |= ((frac_div * 16 + 50) / 100) & 0xf;
	// load
	*USART_BRR = val;

	// Enable the USART peripheral
	*USART_CR1 |= USART_CR1_UE;
}

void usart_putch(void *base, char ch)
{
	volatile uint32_t *USART_SR  = base + 0x00;
	volatile uint32_t *USART_DR  = base + 0x04;

	while (!(*USART_SR & USART_SR_TXE)) {
	}
	*USART_DR = ch;
}

