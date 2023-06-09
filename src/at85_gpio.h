#ifndef AT85_GPIO_H_
#define AT85_GPIO_H_

#include <avr/io.h>
#include <stdbool.h>

typedef enum{
	AT85_GPIO_PORTB0 = 0U,
	AT85_GPIO_PORTB1 = 1U,
	AT85_GPIO_PORTB2 = 2U,
	AT85_GPIO_PORTB3 = 3U,
	AT85_GPIO_PORTB4 = 4U,
	AT85_GPIO_PORTB5 = 5U
} at85_gpio_num_t;

typedef enum{
	AT85_GPIO_INPUT = 0U,
	AT85_GPIO_OUTPUT = 1U
} at85_gpio_direction_t;

static inline void AT85_GPIO_SetDirection(at85_gpio_direction_t direction, at85_gpio_num_t pin)
{
	DDRB = ((uint8_t)(direction << pin) | (DDRB & (~(uint8_t)(1U << pin))));
}

static inline at85_gpio_direction_t AT85_GPIO_GetDirection(at85_gpio_num_t pin)
{
	return ((DDRB >> pin) & 0b00000001U);
}

static inline void AT85_GPIO_SetLevel(bool level, at85_gpio_num_t pin)
{
	PORTB = ((uint8_t)((uint8_t)level << pin) | (PORTB & (~(uint8_t)(1U << pin))));
}

static inline bool AT85_GPIO_GetLevel(at85_gpio_num_t pin)
{
	return (bool)((PORTB >> pin) & 0b00000001U);
}

static inline void AT85_GPIO_TogglePin(at85_gpio_num_t pin)
{
	PINB = (1U << pin);
}

#endif /*AT85_GPIO_H_*/