#include "../../src/at85_gpio.h"
#include "../../src/at85_isr.h"
#include <util/delay_basic.h>
#include <util/delay.h>

static constexpr float period_us{1000000.0/float{F_CPU}};

namespace JSN
{

typedef struct
{
    AT85::GPIO::port_t echo;
    AT85::GPIO::port_t trigger;
} pin_config_t;

template<AT85::GPIO::port_t echo, AT85::GPIO::port_t trigger>
void ValidatePins(void)
{
    static_assert(echo == AT85::GPIO::PORTB_2, "Currently, only PORTB_2 is supported as echo!");
    static_assert(echo != trigger,"Input and Output point to the same Port pin");
}

static inline void ConfigSensorPins(const pin_config_t& config)
{
    using namespace AT85::GPIO;

    SetDirection(OUTPUT, config.trigger);
    SetDirection(INPUT, config.echo);
}

[[nodiscard]] static inline uint32_t ReadDistance(const pin_config_t& config)
{
    using AT85::GPIO::SetLevel;
    using namespace AT85::ISR;

    /* generates the pulse for 10us */
    SetLevel(false, config.trigger);
    _delay_us(2U);
    SetLevel(true, config.trigger);
    _delay_us(10U);
    SetLevel(false, config.trigger);

    uint32_t counter{0U};
 
    while(!GetLevel(config.echo));

    do
    {
        counter++;
    } while(GetLevel(config.echo));

    return counter;
}
}

int main()
{
    constexpr JSN::pin_config_t config {
        .echo    = AT85::GPIO::PORTB_2,
        .trigger = AT85::GPIO::PORTB_1 
    };

    static_assert(sizeof(config) <= sizeof(uint16_t));
    static_assert(period_us > 0.062f);

    JSN::ValidatePins<config.echo,config.trigger>();

    JSN::ConfigSensorPins(config);

    while(true)
    {
        _delay_ms(10U);
        uint32_t distance = JSN::ReadDistance(config);
    }
}