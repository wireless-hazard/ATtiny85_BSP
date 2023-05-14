#ifndef AT85_USI_H
#define AT85_USI_H

#include <avr/io.h>
#include <stddef.h>

typedef enum {
	AT85_USI_DISABLED        = 0b00U,
	AT85_USI_THREE_WIRE_MODE = 0b01U,
	AT85_USI_TWO_WIRE_MODE_1 = 0b10U,
	AT85_USI_TWO_WIRE_MODE_2 = 0b11U
} at85_usi_wire_mode_t;

typedef enum {
	AT85_USI_SOFTWARE_CLOCK_STROBE    = 0b00U,
	AT85_USI_TIMER_COUNTER0_CMP_MATCH = 0b01U,
	AT85_USI_EXTERNAL_POSITIVE_EDGE   = 0b10U,
	AT85_USI_EXTERNAL_NEGATIVE_EDGE   = 0b11U
} at85_usi_clock_src_t;

static inline void AT85_USI_SetDataToTransmit(uint8_t value)
{
	USIDR = value;
}

static inline uint8_t AT85_USI_GetReceivedData(void)
{
	return USIBR;
}

static inline void AT85_USI_SetStartConditionFlag(bool enable)
{
	USISR = ((uint8_t)enable << USISIF) | (USISR & 0b01101111U);
}

static inline bool AT85_USI_GetStartConditionFlag(void)
{
	return (bool)((USISR >> USISIF) & 1U);
}

static inline void AT85_USI_ClearCounterOverflowFlag(void)
{
	USISR = (1U << USIOIF) | (USISR & 0b10101111U);
}

static inline bool AT85_USI_GetCounterOverflowFlag(void)
{
	return (bool)((USISR >> USIOIF) & 1U);
}

static inline void AT85_USI_SetStopConditionFlag(bool state)
{
	USISR = ((uint8_t)state << USIPF) | (USISR & 0b11001111U);
}

static inline bool AT85_USI_GetStopConditionFlag(void)
{
	return (bool)((USISR >> USIPF) & 1U);
}

static inline bool AT85_USI_GetDataOutputCollisionFlag(void)
{
	return (bool)((USISR >> USIDC) & 1U);
}

static inline void AT85_USI_SetCounterValue(uint8_t value)
{
	USISR = (value & 0b00001111U) | (USISR & 0b11100000U);
}

static inline uint8_t AT85_USI_GetCounterValue(void)
{
	return (USISR & 0b00001111U);
}

static inline void AT85_USI_EnableStartConditionInterrupt(bool enable)
{
	USICR = ((uint8_t)enable << USISIE) | (USICR & 0b01111100U);
}

static inline bool AT85_USI_GetStartConditionInterruptEnabled(void)
{
	return (bool)((USICR >> USISIE) & 1U);
}

static inline void AT85_USI_EnableCounterOverflowInterrupt(bool enable)
{
	USICR = ((uint8_t)enable << USIOIE) | (USICR & 0b10111100U);	
}

static inline bool AT85_USI_GetCounterOverflowInterruptEnabled(void)
{
	return (bool)((USICR >> USIOIE) & 1U);
}

static inline void AT85_USI_SetMode(at85_usi_wire_mode_t mode)
{
	USICR = ((uint8_t)mode << USIWM0) | (USICR & 0b11001100U);
}

static inline at85_usi_wire_mode_t AT85_USI_GetMode(void)
{
	return (at85_usi_wire_mode_t)((USICR >> USIWM0) & 0b11U);
}

static inline void AT85_USI_SetClockSource(at85_usi_clock_src_t clock)
{
	USICR = ((uint8_t)clock << USICS0) | (USICR & 0b11110000);
}

static inline at85_usi_clock_src_t AT85_USI_GetClockSource(void)
{
	return (at85_usi_clock_src_t)((USICR >> USICS0) & 0b11U);
}

static inline void AT85_USI_TriggerClockStrobe(void)
{
	USICR = (1U << USICLK) | (USICR & 0b11111100U);
}

static inline void AT85_USI_ToggleClockPin(void)
{
	USICR = (1U << USITC) | (USICR & 0b11111100U);
}

/*High Level API*/

static inline void AT85_USI_PerformClockOperations(void)
{
	USICR = (0b11U) | (USICR & 0b11111100U);
}

static inline void AT85_USI_SendDataRoutine(const uint8_t *data, size_t length, at85_usi_wire_mode_t mode, at85_usi_clock_src_t clock_src)
{
	if (data != NULL)
	{
		const uint8_t usicr_data = ((uint8_t)mode << USIWM0) |	((uint8_t)clock_src << USICS0) | (0b11U);

		for (size_t i = 0U; i < length; i++)
		{
			AT85_USI_SetDataToTransmit(data[i]);
			AT85_USI_ClearCounterOverflowFlag();
			AT85_USI_SetCounterValue(0U);

			while(!AT85_USI_GetCounterOverflowFlag())
			{
				USICR = usicr_data;
			}
		}
	}
}

#endif /*AT85_USI_H*/