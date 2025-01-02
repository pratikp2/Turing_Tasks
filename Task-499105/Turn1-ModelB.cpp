// Source file: pwm_control.cpp

#include <iostream>
#include <cstdint>    // For uint16_t
#include "pwm_config.h"

int main() {
    // Using the abstract timing constants
    uint16_t dutyCyclePercentage = 75;  // Example duty cycle
    uint16_t dutyCycleValue = static_cast<uint16_t>(dutyCyclePercentage * PWM_PERIOD_US / 100);

    std::cout << "PWM Frequency: " << PWM_FREQUENCY_HZ << " Hz" << std::endl;
    std::cout << "PWM Period: " << PWM_PERIOD_US << " microseconds" << std::endl;
    std::cout << "Set Duty Cycle: " << dutyCyclePercentage << "%" << std::endl;
    std::cout << "Calculated Duty Cycle Value: " << dutyCycleValue << std::endl;

    return 0;
}
