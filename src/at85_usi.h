#ifndef AT85_USI_H
#define AT85_USI_H

#include <avr/io.h>
#include <stddef.h>
#include "at85_sfr_defines.hpp"

namespace AT85::USI
{

typedef enum {
	DISABLED        = 0b00U,
	THREE_WIRE_MODE = 0b01U,
	TWO_WIRE_MODE_1 = 0b10U,
	TWO_WIRE_MODE_2 = 0b11U
} wire_mode_t;

typedef enum {
	SOFTWARE_CLOCK_STROBE    = 0b00U,
	TIMER_COUNTER0_CMP_MATCH = 0b01U,
	EXTERNAL_POSITIVE_EDGE   = 0b10U,
	EXTERNAL_NEGATIVE_EDGE   = 0b11U
} clock_src_t;

static inline void SetDataToTransmit(uint8_t value)
{
	USIDR = value;
}

static inline uint8_t GetReceivedData(void)
{
	return USIBR;
}

static inline void SetStartConditionFlag(bool enable)
{
	USISR = (static_cast<uint8_t>(enable) << USISIF) | (USISR & 0b01101111U);
}

static inline bool GetStartConditionFlag(void)
{
	return (bool)((USISR >> USISIF) & 1U);
}

static inline void ClearCounterOverflowFlag(void)
{
	USISR = (1U << USIOIF) | (USISR & 0b10101111U);
}

static inline bool GetCounterOverflowFlag(void)
{
	return (bool)((USISR >> USIOIF) & 1U);
}

static inline void SetStopConditionFlag(bool state)
{
	USISR = (static_cast<uint8_t>(state) << USIPF) | (USISR & 0b11001111U);
}

static inline bool GetStopConditionFlag(void)
{
	return (bool)((USISR >> USIPF) & 1U);
}

static inline bool GetDataOutputCollisionFlag(void)
{
	return (bool)((USISR >> USIDC) & 1U);
}

static inline void SetCounterValue(uint8_t value)
{
	USISR = (value & USICNT_MSK) | (USISR & (~USICNT_MSK));
}

static inline uint8_t GetCounterValue(void)
{
	return (USISR & USICNT_MSK);
}

static inline void EnableStartConditionInterrupt(bool enable)
{
	USICR = (static_cast<uint8_t>(enable) << USISIE) | (USICR & 0b01111100U);
}

static inline bool GetStartConditionInterruptEnabled(void)
{
	return (bool)((USICR >> USISIE) & 1U);
}

static inline void EnableCounterOverflowInterrupt(bool enable)
{
	USICR = (static_cast<uint8_t>(enable) << USIOIE) | (USICR & 0b10111100U);	
}

static inline bool GetCounterOverflowInterruptEnabled(void)
{
	return (bool)((USICR >> USIOIE) & 1U);
}

static inline void SetMode(wire_mode_t mode)
{
	USICR = (static_cast<uint8_t>(mode) << USIWM0) | (USICR & 0b11001100U);
}

static inline wire_mode_t GetMode(void)
{
	return (wire_mode_t)((USICR >> USIWM0) & 0b11U);
}

static inline void SetClockSource(clock_src_t clock)
{
	USICR = (static_cast<uint8_t>(clock) << USICS0) | (USICR & 0b11110000);
}

static inline clock_src_t GetClockSource(void)
{
	return (clock_src_t)((USICR >> USICS0) & 0b11U);
}

static inline void TriggerClockStrobe(void)
{
	USICR = (1U << USICLK) | (USICR & 0b11111100U);
}

static inline void ToggleClockPin(void)
{
	USICR = (1U << USITC) | (USICR & 0b11111100U);
}

/*High Level API*/

static inline void PerformClockOperations(void)
{
	USICR = (0b11U) | (USICR & 0b11111100U);
}

static inline void SendDataRoutine(const uint8_t *data, size_t length, wire_mode_t mode, clock_src_t clock_src)
{
	if (data != nullptr)
    {
        const uint8_t usicr_data = (static_cast<uint8_t>(mode)      << USIWM0) |	
                                   (static_cast<uint8_t>(clock_src) << USICS0) | (0b11U);

        for (size_t i = 0U; i < length; i++)
        {
            SetDataToTransmit(data[i]);
            ClearCounterOverflowFlag();
            SetCounterValue(0U);

            while(!GetCounterOverflowFlag())
            {
                USICR = usicr_data;
            }
        }
    }
}

} //namespace AT85::USI

#endif /*AT85_USI_H*/