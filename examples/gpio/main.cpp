#include "../../src/at85_gpio.h"
#include <util/delay.h>

int main()
{
	using namespace AT85::GPIO;

	SetDirection(OUTPUT, PORTB_1);
	SetDirection(OUTPUT, PORTB_2);
	SetDirection(OUTPUT, PORTB_3);

	bool level = false;

	while(1)
	{
		level = !level;

		SetLevel(level, PORTB_1);
		TogglePin(PORTB_2);
		SetLevel(!level, PORTB_3);
		_delay_ms(1000);
	}
}