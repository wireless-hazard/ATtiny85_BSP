#include "../../src/at85_gpio.h"
#include "../../src/at85_usi.h"
#include <util/delay.h>

int main()
{
	using namespace AT85;

	GPIO::SetDirection(GPIO::OUTPUT, GPIO::PORTB_1); /*DO*/
	GPIO::SetDirection(GPIO::OUTPUT, GPIO::PORTB_2); /*USCLK*/

    //No std::array :(
	const uint8_t data[5U] = {200U, 100U, 3U, 22U, 8U};

	USI::SendDataRoutine(data, sizeof(data)/sizeof(uint8_t), USI::THREE_WIRE_MODE, USI::EXTERNAL_POSITIVE_EDGE);

	USI::ClearCounterOverflowFlag();

	while(true)
	{
		_delay_ms(100);
	}

}