#include "../../src/at85_gpio.h"
#include <util/delay.h>

namespace JSN
{

typedef struct
{
    AT85::GPIO::port_t input;
    AT85::GPIO::port_t output;
} pin_config_t;

template<AT85::GPIO::port_t input, AT85::GPIO::port_t output>
void ValidatePins(void)
{
    static_assert(input != output,"Input and Output point to the same Port pin");
}

static inline void ConfigSensorPins(const pin_config_t& config)
{
    using namespace AT85::GPIO;

    SetDirection(OUTPUT, config.output);
    SetDirection(INPUT, config.input);
}

[[nodiscard]] static inline uint16_t ReadDistance(const pin_config_t& config)
{
    using AT85::GPIO::SetLevel;

    /* generates the pulse for 10us */
    SetLevel(false, config.output);
    _delay_us(2U);
    SetLevel(true, config.output);
    _delay_us(10U);
    SetLevel(false, config.output);

    return 0U;
}
}

int main()
{
    constexpr JSN::pin_config_t config {
        .input  = AT85::GPIO::PORTB_2,
        .output = AT85::GPIO::PORTB_1 
    };

    JSN::ValidatePins<config.input,config.output>();

    JSN::ConfigSensorPins(config);

    auto distance = JSN::ReadDistance(config);

    while(1)
    {
        _delay_us(500);        
    }
}