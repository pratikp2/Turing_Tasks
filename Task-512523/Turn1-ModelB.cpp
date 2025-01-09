#include <stdbool.h>

// PWM timer configuration template
template <unsigned int TIMER_ID, unsigned int PRESCALER, unsigned int PERIOD>
struct PWMConfig {
    static constexpr unsigned int timer_id = TIMER_ID;
    static constexpr unsigned int prescaler = PRESCALER;
    static constexpr unsigned int period = PERIOD;

    // Inline function to calculate the duty cycle value
    static inline unsigned int calculateDutyCycle(unsigned int dutyCyclePercent) {
        return (dutyCyclePercent * period) / 100;
    }
};

// Sample usage for two different PWM timers
constexpr auto PWM1_CONFIG = PWMConfig<1, 80, 1000>(); // Timer 1, Prescaler 80, Period 1000
constexpr auto PWM2_CONFIG = PWMConfig<2, 160, 2000>(); // Timer 2, Prescaler 160, Period 2000

// Function to initialize the PWM timer (placeholder, actual implementation depends on the hardware)
template <typename PWM_T>
void initializePWM() {
    // Access timer registers using PWM_T::timer_id, PWM_T::prescaler, PWM_T::period, etc.
}

// Function to set the PWM duty cycle (placeholder, actual implementation depends on the hardware)
template <typename PWM_T>
void setPWMDutyCycle(unsigned int dutyCyclePercent) {
    unsigned int dutyCycleValue = PWM_T::calculateDutyCycle(dutyCyclePercent);
    // Set the duty cycle register using dutyCycleValue
}

int main() {
    // Initialize PWM timers
    initializePWM<decltype(PWM1_CONFIG)>();
    initializePWM<decltype(PWM2_CONFIG)>();

    // Set duty cycles
    setPWMDutyCycle<decltype(PWM1_CONFIG)>(75); // Set 75% duty cycle for PWM1
    setPWMDutyCycle<decltype(PWM2_CONFIG)>(30); // Set 30% duty cycle for PWM2

    while (true) {
        // Your main application loop here
    }

    return 0;
}
