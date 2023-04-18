#ifndef AT85_ANALOG_CMP_H_
#define AT85_ANALOG_CMP_H_

#include <avr/io.h>
#include <stdbool.h>

typedef enum {
	AT85_NEG_IN_AIN1 = 0b0000U,
	AT85_NEG_IN_ADC0 = 0b1000U,
	AT85_NEG_IN_ADC1 = 0b1001U,
	AT85_NEG_IN_ADC2 = 0b1010U,
	AT85_NEG_IN_ADC3 = 0b1011U
} at85_negative_input_t;

typedef enum {
	AT85_POS_IN_AIN0        = 0U,
	AT85_POS_IN_BANDGAP_REF = 1U
} at85_positive_input_t;

typedef enum {
	AT85_COMP_INT_OUTPUT_TOGGLE       = 0b00U,
	AT85_COMP_INT_OUTPUT_FALLING_EDGE = 0b10U,
	AT85_COMP_INT_OUTPUT_RISING_EDGE  = 0b11U
} at85_analog_cmp_int_mode_t;

typedef enum {
	AT85_ADC0D = 5U,
	AT85_ADC2D = 4U,
	AT85_ADC3D = 3U,
	AT85_ADC1D = 2U,
	AT85_AIN1D = 1U,
	AT85_AIN0D = 0U
} at85_digital_input_t;

static inline void AT85_AnalogCmp_SetNegativeInput(at85_negative_input_t input)
{
	ADCSRA = (((input >> 2U) & 1U) << ADEN) | (ADCSRA & 0b01111111U);
	ADCSRB = (((input >> 3U) & 1U) << ACME) | (ADCSRB & 0b10100111U);
	ADMUX =  (input & 0b11U) | (ADMUX & 0b11110000U);
}

static inline at85_negative_input_t AT85_AnalogCmp_GetNegativeInput(void)
{
	return (at85_negative_input_t)(
			((ADCSRB & 0b01000000U) >> 3U) | 
			((ADCSRA & 0b10000000U) >> 5U) | 
			(( ADMUX & 0b00001111U)));
}

static inline void AT85_AnalogCmp_SetPositiveInput(at85_positive_input_t input)
{
	ACSR = (input << ACBG) | (ACSR & 0b10011011);
}

static inline at85_positive_input_t AT85_AnalogCmp_GetPositiveInput(void)
{
	return (at85_positive_input_t)((ACSR & 0b01000000U) >> ACBG);
}

static inline void AT85_EnableAnalogComparator(bool enable)
{
	ACSR = ((uint8_t)(!enable) << ACD) | (ACSR & 0b01011011);
}

static inline bool AT85_isAnalogComparatorEnabled(void)
{
	return (!(bool)((ACSR & 0b10000000U) >> ACD));
}

static inline bool AT85_AnalogCompOutputSyncedToACO(void)
{
	return (bool)((ACSR >> ACO) & 1U);
}

static inline bool AT85_GetAnalogCompInterruptFlag(void)
{
	return (bool)((ACSR >> ACI) & 1U);
}

static inline void AT85_ClearAnalogCompInterruptFlag(void)
{
	ACSR = (1U << ACI) | (ACSR & 0b11001011U);
}

static inline void AT85_EnableAnalogCompInterrupt(bool enable)
{
	ACSR = ((uint8_t)enable << ACIE) | (ACSR & 0b11010011U);
}

static inline bool AT85_isAnalogCompInterruptEnabled(void)
{
	return (bool)((ACSR >> ACIE) & 1U);
}

static inline void AT85_SetAnalogCompInterruptMode(at85_analog_cmp_int_mode_t mode)
{
	ACSR = (uint8_t)mode | (ACSR & 0b11011000U);
}

static inline at85_analog_cmp_int_mode_t AT85_GetAnalogCompInterruptMode(void)
{
	return (at85_analog_cmp_int_mode_t)(ACSR & 0b11);
}

static inline void AT85_EnableDigitalInput(bool enable, at85_digital_input_t input)
{
	DIDR0 = ((uint8_t)enable << input) | (DIDR0 & (~(uint8_t)(1U << input)));
}

static inline bool AT85_isDigitalInputEnabled(at85_digital_input_t input)
{
	return (bool)((DIDR0 >> input) & 1U);
}

#endif /*AT85_ANALOG_CMP_H_*/