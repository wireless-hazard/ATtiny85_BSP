#include "../../src/at85_analog_cmp.h"
#include <util/delay.h>

int main()
{
	AT85_AnalogCmp_SetNegativeInput(AT85_NEG_IN_ADC3);
	volatile at85_negative_input_t negative_input = AT85_AnalogCmp_GetNegativeInput();
	AT85_AnalogCmp_SetPositiveInput(AT85_POS_IN_AIN0);
	volatile at85_positive_input_t positive_input = AT85_AnalogCmp_GetPositiveInput();

	while(1)
	{
		_delay_ms(100);
	}
}