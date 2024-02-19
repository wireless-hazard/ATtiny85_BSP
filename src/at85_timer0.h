#ifndef AT85_TMR0_H
#define AT85_TMR0_H

#include <avr/io.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	AT85_TMR0_NON_PWM           = 0b00U,
	AT85_TMR0_PHASE_CORRECT_PWM = 0b01U,
	ATM85_TMR0_FAST_PWM         = 0b11U
} at85_wave_gen_mode_t;

typedef enum {
	AT85_NON_PWM_OFF     = 0U,
	AT85_TOGGLE_ON_MATCH = 1U,
	AT85_CLEAR_ON_MATCH  = 2U,
	AT85_SET_ON_MATCH    = 3U
} at85_non_pwm_t;

typedef enum {
	AT85_FAST_PWM_OFF                 = 0U,
	AT85_CLEAR_ON_MATCH_SET_ON_BOTTON = 2U,
	AT85_SET_ON_MATCH_CLEAR_ON_BOTTON = 3U	
} at85_fast_pwm_t;

typedef enum {
	AT85_PHASE_PWM_OFF                 = 0U,
	AT85_CLEAR_UP_MATCH_SET_DOWN_MATCH = 2U,
	AT85_SET_UP_MATCH_CLEAR_DOWN_MATCH = 3U
} at85_phase_pwm_t;

typedef union {
	uint8_t _raw_value;
	at85_non_pwm_t non_pwm;
	at85_phase_pwm_t phase_pwm;
	at85_fast_pwm_t fast_pwm;
} at85_port_operation_t;

typedef enum {
	AT85_TMR0_CLK_OFF          = 0U,
	AT85_TMR0_CLK_IO           = 1U,
	AT85_TMR0_CLK_IO_DIV_8     = 2U,
	AT85_TMR0_CLK_IO_DIV_64    = 3U,
	AT85_TMR0_CLK_IO_DIV_256   = 4U,
	AT85_TMR0_CLK_IO_DIV_1024  = 5U,
	AT85_TMR0_T0_FALLING_EDGE  = 6U,
	AT85_TMR0_T0_RISING_EDGE   = 7U
} at85_tmr0_clock_t;

typedef enum {
	AT85_TMR0_PORT_OC0A = 6U,
	AT85_TMR0_PORT_OC0B = 4U
} at85_tmr0_port_t;


static inline void AT85_TMR0_SetCompareOutputMode(at85_wave_gen_mode_t mode)
{
	TCCR0A = ((uint8_t)mode) | (TCCR0A & (0b11110000U));
}

static inline at85_wave_gen_mode_t AT85_TMR0_GetWaveGenerationMode(void)
{
	return (at85_wave_gen_mode_t)(TCCR0A & 0b00000011);
}

static inline void AT85_TMR0_PWM_SetPortOperationMode(at85_port_operation_t port_OC0A, at85_port_operation_t port_OC0B)
{
	TCCR0A = ((port_OC0A._raw_value << 6U) | (port_OC0B._raw_value << 4U)) | (TCCR0A & (0b11110000U));
}

static inline uint8_t AT85_TMR0_PWM_GetRawPortOperationMode(at85_tmr0_port_t port)
{
	return (TCCR0A >> port) & (0b00000011);
}

static inline void AT85_TMR0_SetClockSource(at85_tmr0_clock_t source)
{
	TCCR0B = ((uint8_t)source) | (TCCR0B & (0b11001000U));
}

static inline at85_tmr0_clock_t AT85_TMR0_GetClockSource(void)
{
	return (at85_tmr0_clock_t)(TCCR0B & 0b00000111);
}

static inline void AT85_TMR0_SetCompareValue(uint8_t value, at85_tmr0_port_t port)
{
	(port == AT85_TMR0_PORT_OC0A) ? (OCR0A = value) : (OCR0B = value);
}

static inline uint8_t AT85_TMR0_GetCompareValue(at85_tmr0_port_t port)
{
	return (port == AT85_TMR0_PORT_OC0A) ? (OCR0A) : (OCR0B);
}

#ifdef __cplusplus
}
#endif

#endif /*AT85_TMR0_H*/