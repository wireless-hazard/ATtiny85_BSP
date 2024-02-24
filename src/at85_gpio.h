#ifndef AT85_GPIO_H_
#define AT85_GPIO_H_

#if __cplusplus < 201402L 
#error "C++14 or better required\n"
#endif

#include <avr/io.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

namespace AT85::GPIO
{

typedef enum : uint8_t {
    PORTB_0 = 0U,
    PORTB_1 = 1U,
    PORTB_2 = 2U,
    PORTB_3 = 3U,
    PORTB_4 = 4U,
    PORTB_5 = 5U
} port_t;

typedef enum : uint8_t {
    INPUT  = 0U,
    OUTPUT = 1U
} direction_t;

static inline void SetDirection(direction_t direction, port_t pin)
{
    DDRB = ((uint8_t)(direction << pin) | (DDRB & (~(uint8_t)(1U << pin))));
}

static inline direction_t GetDirection(port_t pin)
{
    return (direction_t)((DDRB >> (uint8_t)pin) & 0b00000001U);
}

static inline void SetLevel(bool level, port_t pin)
{
    PORTB = ((uint8_t)((uint8_t)level << pin) | (PORTB & (~(uint8_t)(1U << pin))));
}

static inline bool GetLevel(port_t pin)
{
    return (bool)((PINB >> pin) & 0b00000001U);
}

static inline void TogglePin(port_t pin)
{
    PINB = (1U << pin);
}

}//namespace AT85::GPIO

#ifdef __cplusplus
}
#endif

#endif /*AT85_GPIO_H_*/
