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

typedef union
{
    uint8_t reg;
    struct 
    {   
        uint8_t USICNT_ : 4; // Counter Value
        uint8_t USIDC_  : 1; // Data Output Collision
        uint8_t USIPF_  : 1; // Stop Condition Flag
        uint8_t USIOIF_ : 1; // Counter Overflow Interrupt Flag
        uint8_t USISIF_ : 1; // Start Condition Interrupt Flag
    } bit;
} USISR_t;

static volatile USISR_t *USISR_reg = (volatile USISR_t *)(0x0E + 0x20);
static_assert(sizeof(USISR_t) == sizeof(uint8_t));

typedef union
{
    uint8_t reg;
    struct
    {
        uint8_t USITC_  : 1; // Toggle Clock Port Pin
        uint8_t USICLK_ : 1; // Clock Strobe
        uint8_t USICS_  : 2; // Clock Source Select
        uint8_t USIWM_  : 2; // Wire Mode
        uint8_t USIOIE_ : 1; // Counter Overflow Interrupt Enable
        uint8_t USISIE_ : 1; // Start Condition Interrupt Enable
    } bit;
} USICR_t;

static volatile USICR_t *USICR_reg = (volatile USICR_t *)(0x0D + 0x20);
static_assert(sizeof(USICR_t)==sizeof(uint8_t));

typedef union
{
    uint8_t reg;
    struct
    {
        uint8_t PORTB0_  : 1;
        uint8_t PORTB1_  : 1;
        uint8_t PORTB2_  : 1;
        uint8_t PORTB3_  : 1;
        uint8_t PORTB4_  : 1;
        uint8_t PORTB5_  : 1;
        uint8_t reserved : 2;
    } bit;
} PORTB_t;
static volatile PORTB_t *PORTB_reg = (volatile PORTB_t *)(0x18 + 0x20);
static_assert(sizeof(PORTB_t)==sizeof(uint8_t));

#endif /*AT85_SFR_DEF_H_*/