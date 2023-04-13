#include "../../src/at85_gpio.h"
#include <util/delay.h>

int main()
{
	AT85_GPIO_SetDirection(AT85_GPIO_OUTPUT, AT85_GPIO_PORTB1);

	while(1)
	{
		AT85_GPIO_TogglePin(AT85_GPIO_PORTB1);
		_delay_ms(100);
	}
}