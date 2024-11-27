#include <stdint.h>

// Generic Draft for how to access registers

static inline uint8_t GetRegisterField(uint8_t* reg, uint8_t position, uint8_t mask)
{
    return (((*reg) & mask) >> position);
}

static inline void SetRegisterField(uint8_t* reg, uint8_t position, uint8_t mask, uint8_t value)
{
    (*reg) &= ~mask;
    (*reg) |= (value << position);
}

static inline void ToggleRegisterBit(uint8_t* reg, uint8_t position)
{
    (*reg) ^= (1 << position);
}
