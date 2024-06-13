#include "../../src/at85_gpio.h"
#include "../../src/at85_timer0.h"

#include <util/delay.h>

int main()
{
    AT85::GPIO::SetDirection(AT85::GPIO::OUTPUT, AT85::GPIO::PORTB_0);
    AT85::GPIO::SetDirection(AT85::GPIO::OUTPUT, AT85::GPIO::PORTB_1);
    AT85_TMR0_SetWaveGenerationMode(AT85_TMR0_NON_PWM);

    at85_port_operation_t port_OC0A = {.non_pwm = AT85_TOGGLE_ON_MATCH};
    at85_port_operation_t port_OC0B = {.non_pwm = AT85_TOGGLE_ON_MATCH};
    AT85_TMR0_PWM_SetPortOperationMode(port_OC0A, port_OC0B);

    AT85_TMR0_SetCompareValue(100, AT85_TMR0_PORT_OC0A);
    AT85_TMR0_SetCompareValue(200, AT85_TMR0_PORT_OC0B);
    AT85_TMR0_SetClockSource(AT85_TMR0_CLK_IO);

    while(1)
    {
        _delay_ms(100);
	}
}