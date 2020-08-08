#include <iostream>

enum Temperature_Unit { kCELSIUS = 1, kKELVIN = 2, kFAHRENHEIT = 3 };

/**
 * Checks if unit value is valid
 *
 * @param temperature unit value
 * @returns validation bool
 */
bool IsUnitTypeValid(int unit_value) { return (unit_value > 0 && unit_value < 4); };

/**
 * Returns a unit name for given value
 *
 * @param temperature unit value
 * @returns unit name
 */
std::string ConvertTemperatureUnitToScaleName(int unit_value) {
    switch (unit_value) {
        case kCELSIUS:
            return "Celsius";
        case kKELVIN:
            return "Kelvin";
        case kFAHRENHEIT:
            return "Fahrenheit";
        default:
            return "Unknown value";
    }
}

int main() {
    std::cout << "Pick input and output temperature unit (eg. 1 3)" << std::endl;
    std::cout << "1) Celsius" << std::endl;
    std::cout << "2) Kelvin" << std::endl;
    std::cout << "3) Fahrenheit" << std::endl;

    int input_unit_value {}, output_unit_value {};
    std::cin >> input_unit_value >> output_unit_value;

    // Input validation
    if(!(IsUnitTypeValid(input_unit_value) || IsUnitTypeValid(output_unit_value))) {
        return 1; // Bad input value
    }

    std::cout << "Enter temperature value to convert" << std::endl;

    float temperature_input_value {};
    std::cin >> temperature_input_value;

    float temperature_output_value {};

    if(input_unit_value == output_unit_value) {
        temperature_output_value = temperature_input_value;
    } else {
        float slope_value {};
        double intercept_value {};
        const float kCelsiusToKelvinDifference = 273.15;

        if(input_unit_value != kFAHRENHEIT && output_unit_value != kFAHRENHEIT) {
            /* Celsius to Kelvin or Kelvin to Celsius */

            slope_value = 1;
            intercept_value = kCelsiusToKelvinDifference;

            if(input_unit_value == 2) {
                /* Kelvin to Celsius */

                intercept_value *= -1;
            }
        } else if (input_unit_value == kFAHRENHEIT) {
            /* Fahrenheit to Celsius or Kelvin */

            slope_value = (float)5/(float)9;
            intercept_value = -(17 + (float)7/(float)9);

            if(output_unit_value == kKELVIN) {
                /* Fahrenheit Kelvin */

                intercept_value += kCelsiusToKelvinDifference;
            }
        } else {
            /* Celsius or Kelvin to Fahrenheit */
            slope_value = 1.8;
            intercept_value = 32;


            if(input_unit_value == kKELVIN) {
                /* Kelvin to Fahrenheit*/
                intercept_value -= 491.67;
            }
        }

        temperature_output_value = slope_value * temperature_input_value + intercept_value;
    }

    std::cout << "Convert ";
    std::cout << ConvertTemperatureUnitToScaleName(input_unit_value) << " (" << temperature_input_value << " deg)";
    std::cout << " to ";
    std::cout << ConvertTemperatureUnitToScaleName(output_unit_value) << " -> " << temperature_output_value;

    return 0;
}
