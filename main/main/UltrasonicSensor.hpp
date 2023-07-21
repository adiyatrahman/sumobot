#pragma once

#include <Arduino.h>

namespace mtrn3100 {

class UltrasonicSensor {
public:
    // COMPLETE THIS CONSTRUCTOR.
    UltrasonicSensor(uint8_t trigger_pin, uint8_t echo_pin) 
        : trigger_pin(trigger_pin), echo_pin(echo_pin) {
            pinMode(trigger_pin, OUTPUT);
            pinMode(echo_pin, INPUT);
    }

    float echo() const {
        // Send the trigger pulse
        digitalWrite(trigger_pin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigger_pin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigger_pin, LOW);

        // Measure the duration of the echo pulse
        long duration = pulseIn(echo_pin, HIGH);

        // Calculate the distance based on the speed of sound
        float distance = duration * 0.343 / 2;

        return distance;
    }

private:
    const uint8_t trigger_pin;
    const uint8_t echo_pin;
};

}  // namespace mtrn3100