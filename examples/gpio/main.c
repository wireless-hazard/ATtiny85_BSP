#include "../../src/at85_gpio.h"
#include <util/delay.h>

int main()
{
	AT85_GPIO_SetDirection(AT85_GPIO_OUTPUT, AT85_GPIO_PORTB1);
	AT85_GPIO_SetDirection(AT85_GPIO_OUTPUT, AT85_GPIO_PORTB2);
	AT85_GPIO_SetDirection(AT85_GPIO_OUTPUT, AT85_GPIO_PORTB3);

	bool level = false;

	while(1)
	{
		level = !level;

		AT85_GPIO_SetLevel(level, AT85_GPIO_PORTB1);
		AT85_GPIO_TogglePin(AT85_GPIO_PORTB2);
		AT85_GPIO_SetLevel(!level, AT85_GPIO_PORTB3);
		_delay_ms(1000);
	}
}