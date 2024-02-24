#include "../../src/at85_gpio.h"
#include "../../src/at85_isr.h"
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

//PB2 output - PWM with a frequency of 14.8kHz, 
//PB1 turns ON/OFF the device (2 sec. hold to turn on and 2 sec. hold to turn off)

static constexpr AT85::GPIO::port_t INPUT_PORT = AT85::GPIO::PORTB_4;
static constexpr AT85::GPIO::port_t OUTPUT_PORT = AT85::GPIO::PORTB_1;

ISR(PCINT0_vect)
{
    TogglePin(OUTPUT_PORT);
}

int main()
{
    using namespace AT85::GPIO;
    using namespace AT85::ISR;

    SetDirection(INPUT, INPUT_PORT);
    SetDirection(OUTPUT, OUTPUT_PORT);

    /*Enable interrupts on PORTB4*/
    sei();
    EnablePinChangeInterrupt(true);
    EnablePinChangeInterruptMask(ENABLE_INT_PORTB_4);

    while(1);
}