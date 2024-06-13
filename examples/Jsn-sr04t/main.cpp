#include "../../src/at85_gpio.h"
#include "../../src/at85_timer0.h"
#include <util/delay_basic.h>
#include <util/delay.h>

volatile float distance = 0.0f;

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
    static_assert(echo != trigger,"Input and Output point to the same Port pin");
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

int main()
{
    // Configures OC0A
    AT85::GPIO::SetDirection(AT85::GPIO::OUTPUT, AT85::GPIO::PORTB_0);

    // Pin just to mark the correctness of the calculation
    AT85::GPIO::SetDirection(AT85::GPIO::OUTPUT, AT85::GPIO::PORTB_3);

    // Configures the PWM generation on OC0A (aka PORTB0)
    AT85_TMR0_SetWaveGenerationMode(AT85_TMR0_CLEAR_TIMER_ON_MATCH);

    at85_port_operation_t port_OC0A = {.non_pwm = AT85_TOGGLE_ON_MATCH};
    at85_port_operation_t port_OC0B = {.non_pwm = AT85_NON_PWM_OFF};
    AT85_TMR0_PWM_SetPortOperationMode(port_OC0A, port_OC0B);
    
    AT85_TMR0_SetCompareValue(5, AT85_TMR0_PORT_OC0A);

    AT85_TMR0_SetClockSource(AT85_TMR0_CLK_IO_DIV_1024);

    // Configures the Ultrasonic sensor

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

        bool pass_test = TestEqual(0.20f, distance, 0.02f);
        if (pass_test)
        {
            AT85_TMR0_SetCompareValue(100, AT85_TMR0_PORT_OC0A);
        }
        AT85::GPIO::SetLevel(pass_test, AT85::GPIO::PORTB_3);
    }
}