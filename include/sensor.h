/*======================================================================================================================
 *                                                  INCLUDE FILES
 * 1) system and project includes
 * 2) needed interfaces from external units
 * 3) internal and external interfaces from this unit
======================================================================================================================*/
#include <Arduino.h>
#include "MAX30105.h"
#include "spo2_algorithm.h"
#include "lcd.h"
/*======================================================================================================================
 *                                                  CONSTANTS
======================================================================================================================*/
/*======================================================================================================================
 *                                              DEFINES AND MACROS
======================================================================================================================*/
/*======================================================================================================================
 *                                                      ENUMS
======================================================================================================================*/
typedef enum
{
    SENSOR_OK,
    SENSOR_ERR
}sensorStatus;
/*======================================================================================================================
 *                                              STRUCTURES AND OTHER TYPEDEFS
======================================================================================================================*/

/*======================================================================================================================
 *                                              GLOBAL VARIABLE DECLARATIONS
======================================================================================================================*/

/*======================================================================================================================
 *                                                  FUNCTION PROTOTYPES
======================================================================================================================*/

class HeartRateSensor 
{
public:
    HeartRateSensor();
    /**
     * @brief Initialize sensor
     * 
     * @return sensorStatus 
     */
    sensorStatus begin();

    /**
     * @brief Read 100 first samples
     * 
     * @param int32_t bufferLength 
     */
    void readSamples(int32_t bufferLength, LCD &lcd);

    /**
     * @brief Continuous samples reading
     * 
     */
    void continuousSampling();

    /**
     * @brief Calculate BPM and SPO2
     * 
     * @param int32_t bufferLength 
     * @param int32_t &spo2 
     * @param int8_t &validSPO2 
     * @param int32_t &heartRate 
     * @param int8_t &validHeartRate 
     */
    void calculate(int32_t bufferLength, int32_t* spo2, int8_t* validSPO2, int32_t* heartRate, int8_t* validHeartRate);
    
    /**
     * @brief ReadIR from Sensor
     * 
     * @return Long IR value
     */
    long readIR();

private:
    MAX30105 particleSensor;

    #if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
    // Arduino Uno doesn't have enough SRAM to store 100 samples of IR led data and red led data in 32-bit format
    // To solve this problem, 16-bit MSB of the sampled data will be truncated. Samples become 16-bit data.
    uint16_t irBuffer[100];
    uint16_t redBuffer[100];
    #else
    // For ESP Chips
    uint32_t irBuffer[100];     // IR Buffer for ESP32
    uint32_t redBuffer[100];    // Red Buffer for ESP32
    #endif
};