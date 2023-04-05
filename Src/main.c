#include <stm32l0xx.h>
#include <stm32l0xx_ll_bus.h>
#include <stm32l0xx_ll_gpio.h>
#include <stm32l0xx_ll_rcc.h>
#include <stm32l0xx_ll_utils.h>

#include <stdio.h>
#include <stdbool.h>

#define PLL_MULTIPLIER LL_RCC_PLL_MUL_6
#define PLL_DIVIDER LL_RCC_PLL_DIV_2



int main(void)
{
	uint32_t timeout = 3000U;
	uint32_t frequency = __LL_RCC_CALC_PLLCLK_FREQ(16000000U, PLL_MULTIPLIER, PLL_DIVIDER);

	/* Use HSI at 16MHz, times 6 = 96, lowest divider is 2 = 48MHz */
	LL_UTILS_PLLInitTypeDef pll = {
		.PLLMul = PLL_MULTIPLIER,
		.PLLDiv = PLL_DIVIDER,
	};

	LL_UTILS_ClkInitTypeDef clk = {
		.AHBCLKDivider = LL_RCC_SYSCLK_DIV_1,
		.APB1CLKDivider = LL_RCC_APB1_DIV_2,
		.APB2CLKDivider = LL_RCC_APB2_DIV_2, /* 32MHz max. */
	};

	/* Enables HSI and PLL, and switches to the PLL Clock */
	if (LL_PLL_ConfigSystemClock_HSI(&pll, &clk) != SUCCESS)
	{
		/* SHIT */
	}

	LL_SetSystemCoreClock(frequency);

	/* Set systick timer to tick every 1ms */
	LL_Init1msTick(frequency);

	LL_RCC_LSI_Enable();

	do
	{
		LL_mDelay(1U);
		timeout--;
	}
	while((LL_RCC_LSI_IsReady() == false) && (timeout > 0U));

	if (timeout == 0U)
	{
		/* SHIT */
	}

	/* LSI_VALUE (macro) is 37kHz, div 16 is 2.3kHz */
	LL_RCC_ConfigMCO(LL_RCC_MCO1SOURCE_LSI, LL_RCC_MCO1_DIV_16);

	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_8, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_8, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetAFPin_8_15(GPIOA, LL_GPIO_PIN_8, LL_GPIO_AF_0);

	printf("Hello, world!\n");

	return 0;
}
