#include "../../src/at85_gpio.h"
#include "../../src/at85_isr.h"
#include <util/delay_basic.h>
#include <util/delay.h>

volatile uint16_t distance = 0U;
volatile float actual_distance = 0.0f;

static constexpr float period_us{1000000.0/float{F_CPU}};

static constexpr float nano_seconds{1000000000.0f};
static constexpr uint16_t uptime_counter_ratio{434}; // Measured value

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

[[nodiscard]] static inline uint16_t ReadDistance(const pin_config_t& config)
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

[[nodiscard]] static float ConvertDistance(uint32_t counter)
{
    const uint32_t uptime_ns{uptime_counter_ratio*counter};
    const uint64_t distance_int{uptime_ns*170U};
    
    const float distance = static_cast<float>(distance_int)/nano_seconds;

    return distance;
}

/**
 * It will return "true" if the test passes, "false" otherwise
*/
[[nodiscard]] static bool TestEqual(float expected, float actual, float accepted_delta)
{
    const float positive_difference = ((expected - actual) >= 0.0f) ? (expected - actual) : (actual - expected);

    return (positive_difference <= accepted_delta);
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
        distance = JSN::ReadDistance(config);
        actual_distance = ConvertDistance(distance);
    }
}