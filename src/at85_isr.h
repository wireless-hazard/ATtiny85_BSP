#ifndef AT85_ISR_H_
#define AT85_ISR_H_

#if __cplusplus < 201402L 
#error "C++14 or better required\n"
#endif

#include <avr/io.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ENABLE_INT_PORTB_0 (1U << PCINT0)
#define ENABLE_INT_PORTB_1 (1U << PCINT1)
#define ENABLE_INT_PORTB_2 (1U << PCINT2)
#define ENABLE_INT_PORTB_3 (1U << PCINT3)
#define ENABLE_INT_PORTB_4 (1U << PCINT4)
#define ENABLE_INT_PORTB_5 (1U << PCINT5)

namespace AT85::ISR
{

typedef enum {
    INT0_LOW_LEVEL    = 0b00U,
    INT0_ANY_CHANGE   = 0b01U,
    INT0_FALLING_EDGE = 0b10U,
    INT0_RISING_EDGE  = 0b11U
} int0_src_t;

static inline void EnableExternalInterruptRequest0(bool enable)
{
    GIMSK = (((uint8_t)enable << INT0) | (GIMSK & 0b10111111U));
}

static inline void EnablePinChangeInterrupt(bool enable)
{
    GIMSK = (((uint8_t)enable << PCIF) | (GIMSK & 0b11011111U));
}

static inline void EnablePinChangeInterruptMask(uint8_t pinbitmask)
{
    PCMSK = pinbitmask;
}

static inline void SetExternalInterruptSource(int0_src_t src)
{
    MCUCR = ((uint8_t)src) | (MCUCR & 0b11111100U);
}

} /*namespace AT85::ISR*/

#ifdef __cplusplus
}
#endif

#endif
