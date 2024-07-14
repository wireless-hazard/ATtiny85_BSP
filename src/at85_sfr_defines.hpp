#ifndef AT85_SFR_DEF_H_
#define AT85_SFR_DEF_H_

#if __cplusplus < 201402L 
#error "C++14 or better required\n"
#endif

#include <stdint.h>
#include <stdbool.h>

// GPIO DEFINES

// PORTB - Port B Data Register
static inline constexpr uint8_t PORTB0_POS = 0U;
static inline constexpr uint8_t PORTB0_MSK = 1U << PORTB0_POS;
static inline constexpr uint8_t PORTB1_POS = 1U;
static inline constexpr uint8_t PORTB1_MSK = 1U << PORTB1_POS;
static inline constexpr uint8_t PORTB2_POS = 2U;
static inline constexpr uint8_t PORTB2_MSK = 1U << PORTB2_POS;
static inline constexpr uint8_t PORTB3_POS = 3U;
static inline constexpr uint8_t PORTB3_MSK = 1U << PORTB3_POS;
static inline constexpr uint8_t PORTB4_POS = 4U;
static inline constexpr uint8_t PORTB4_MSK = 1U << PORTB4_POS;
static inline constexpr uint8_t PORTB5_POS = 5U;
static inline constexpr uint8_t PORTB5_MSK = 1U << PORTB5_POS;

// USI - Universal Serial Interface

// USIDR - USI Data Register
static inline constexpr uint8_t USICNT_MSK = 0b00001111U;

// USICR - USI Control Register
static inline constexpr uint8_t USIWM_MSK     = 0b00110000U;
static inline constexpr uint8_t USICS_MSK     = 0b00001100U;
static inline constexpr uint8_t ALL_USICS_MSK = 0b00001110U;


#endif /*AT85_SFR_DEF_H_*/