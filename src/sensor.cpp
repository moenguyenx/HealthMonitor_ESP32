#include "sensor.h"
#include "buzzer.h"

HeartRateSensor::HeartRateSensor() {}

sensorStatus HeartRateSensor::begin() {
    sensorStatus status;
    status = SENSOR_OK;
    if (particleSensor.begin() == false) {
        Serial.println("MAX30102 was not found. Please check wiring/power.");
        beepBuzzer(ERR_BEEP);
        status = SENSOR_ERR;
        while (1);
    }
    beepBuzzer(OK_BEEP);
    particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange);

    return status;
}

