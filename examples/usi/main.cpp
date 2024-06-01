#include "../../src/at85_gpio.h"
#include "../../src/at85_usi.h"
#include <util/delay.h>

int main()
{
	AT85::GPIO::SetDirection(AT85::GPIO::OUTPUT, AT85::GPIO::PORTB_1); /*DO*/
	AT85::GPIO::SetDirection(AT85::GPIO::OUTPUT, AT85::GPIO::PORTB_2); /*USCLK*/

    //No std::array :(
	const uint8_t data[5U] = {200U, 100U, 3U, 22U, 8U};

	AT85_USI_SendDataRoutine(data, sizeof(data)/sizeof(uint8_t), AT85_USI_THREE_WIRE_MODE, AT85_USI_EXTERNAL_POSITIVE_EDGE);

	AT85_USI_ClearCounterOverflowFlag();

	while(true)
	{
		_delay_ms(100);
	}

}