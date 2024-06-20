#include "../../src/at85_gpio.h"
#include "../../src/at85_timer0.h"
#include <util/delay_basic.h>
#include <util/delay.h>

volatile float distance{0.0f};

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
    static_assert(echo != trigger,"Echo and Trigger point to the same Port pin");
}

static inline void ConfigSensorPins(const pin_config_t& config)
{
    using namespace AT85::GPIO;

    SetDirection(OUTPUT, config.trigger);
    SetDirection(INPUT, config.echo);
}

[[nodiscard]] static float ConvertDistance(uint32_t counter)
{
    const uint32_t uptime_ns{uptime_counter_ratio*counter};
    const uint64_t distance_int{uptime_ns*170U};
    
    const float distance = static_cast<float>(distance_int)/nano_seconds;

    return distance;
}

[[nodiscard]] static inline float ReadDistance(const pin_config_t& config)
{
    using AT85::GPIO::SetLevel;

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

    return ConvertDistance(counter);
}
}

/**
 * It will return "true" if the test passes, "false" otherwise
*/
[[nodiscard]] static bool TestEqual(float expected, float actual, float accepted_delta)
{
    const float positive_difference = ((expected - actual) >= 0.0f) ? (expected - actual) : (actual - expected);

    return (positive_difference <= accepted_delta);
}

namespace GPIO
{
static void ProduceAlertSignal(float current_distance, AT85::GPIO::port_t port)
{
    constexpr uint8_t delay_per_cycle{50};
    uint8_t number_of_rounds{0U};

    if ((current_distance >= 0) && (current_distance < 0.25))
    {
        number_of_rounds = static_cast<uint8_t>(current_distance*100.0);
    }

    // If number_of_rounds is equal to 0, does not generate the ON signal
    AT85::GPIO::SetLevel(static_cast<bool>(number_of_rounds), port);
    _delay_ms(100);

    AT85::GPIO::SetLevel(false, port);
    for(uint8_t current_round = 0U; current_round < number_of_rounds; current_round++)
    {
        _delay_ms(delay_per_cycle);
    }

    return;
}
}

int main()
{
    // Pin outputing the Alert Signal 
    // distance between device and object
    AT85::GPIO::SetDirection(AT85::GPIO::OUTPUT, AT85::GPIO::PORTB_3);

    // Configures the Ultrasonic sensor
    constexpr JSN::pin_config_t config {
        .echo    = AT85::GPIO::PORTB_2,
        .trigger = AT85::GPIO::PORTB_1 
    };

    JSN::ConfigSensorPins(config);

    // Compile time checks
    static_assert(sizeof(config) <= sizeof(uint16_t));
    static_assert(period_us > 0.062f);
    JSN::ValidatePins<config.echo,config.trigger>();

    // 
    while(true)
    {
        distance = JSN::ReadDistance(config);
        GPIO::ProduceAlertSignal(distance, AT85::GPIO::PORTB_3);
    }
}