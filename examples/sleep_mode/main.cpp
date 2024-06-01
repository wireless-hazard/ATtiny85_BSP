#include "../../src/at85_gpio.h"
#include "../../src/at85_isr.h"
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include "../../src/at85_timer0.h"

//PB2 output - PWM with a frequency of 14.8kHz, 
//PB1 turns ON/OFF the device (2 sec. hold to turn on and 2 sec. hold to turn off)

static constexpr AT85::GPIO::port_t INPUT_PORT  = AT85::GPIO::PORTB_1;
static constexpr AT85::GPIO::port_t OUTPUT_PORT = AT85::GPIO::PORTB_2;

static constexpr uint8_t timer0_compare_value = 69U;

ISR(PCINT0_vect)
{
    
}

ISR(TIM0_COMPA_vect)
{
    TogglePin(OUTPUT_PORT);
}

int main()
{
    using namespace AT85::GPIO;
    using namespace AT85::ISR;

    SetDirection(INPUT, INPUT_PORT);
    SetDirection(OUTPUT, OUTPUT_PORT);

    /*Enable interrupts on PORTB1*/
    sei();
    EnablePinChangeInterrupt(true);
    EnablePinChangeInterruptMask(ENABLE_INT_PORTB_1);

    TCCR0A = (1U << COM0B0) | (2U);
    OCR0A = timer0_compare_value;
    TCCR0B = 1U << CS01;

    /*Enable Interrupts*/
    TIMSK = (1U << OCIE0A);

    while(1);
}