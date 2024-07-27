#include "sensor.h"
#include "buzzer.h"

HeartRateSensor::HeartRateSensor() {}

sensorStatus HeartRateSensor::begin() 
{   
    byte ledBrightness = 60;
    byte sampleAverage = 4;
    byte ledMode = 2;
    byte sampleRate = 100;
    int pulseWidth = 411;
    int adcRange = 4096;

    sensorStatus status;
    status = SENSOR_OK;
    if (particleSensor.begin() == false) {
        Serial.println("MAX30102 was not found. Please check wiring/power.");
        beepBuzzer(ERR_BEEP);
        status = SENSOR_ERR;
        return status;
    }
    particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange);
    beepBuzzer(OK_BEEP);
    
    return status;
}

void HeartRateSensor::readSamples(int32_t bufferLength, LCD &lcd) 
{
  for (int i = 0; i < bufferLength; i++) 
  {
    while (!particleSensor.available()) 
    {
      particleSensor.check();
    }
    redBuffer[i] = particleSensor.getRed();
    irBuffer[i] = particleSensor.getIR();
    if (irBuffer[i] <= 7000) {
      Serial.println("Finger removed. Exiting measurement loop.");
      break;
    }

    float percentage = ((float)(i + 1) / bufferLength) * 100;
    lcd.displayPercentage(percentage);

    particleSensor.nextSample();
  }
}

void HeartRateSensor::continuousSampling()
{
	//dumping the first 25 sets of samples in the memory and shift the last 75 sets of samples to the top
	for (byte i = 25; i < 100; i++)
	{
	  redBuffer[i - 25] = redBuffer[i];
	  irBuffer[i - 25] = irBuffer[i];
	}
	//take 25 sets of samples before calculating the heart rate.
	for (byte i = 75; i < 100; i++)
	{
	  while (particleSensor.available() == false) //do we have new data?
	    particleSensor.check(); //Check the sensor for new data
	  redBuffer[i] = particleSensor.getRed();
	  irBuffer[i] = particleSensor.getIR();
	  particleSensor.nextSample(); //We're finished with this sample so move to next sample
	}
}

long HeartRateSensor::readIR()
{
    long irValue = particleSensor.getIR();
    return irValue;
}

void HeartRateSensor::calculate(int32_t bufferLength, int32_t* spo2, int8_t* validSPO2, int32_t* heartRate, int8_t* validHeartRate) 
{
  maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, spo2, validSPO2, heartRate, validHeartRate);
}

