/*======================================================================================================================
 *                                                  INCLUDE FILES
 * 1) system and project includes
 * 2) needed interfaces from external units
 * 3) internal and external interfaces from this unit
======================================================================================================================*/
#include <Arduino.h>
#include "MAX30105.h"
#include "heartRate.h"
/*======================================================================================================================
 *                                                  CONSTANTS
======================================================================================================================*/
/*======================================================================================================================
 *                                              DEFINES AND MACROS
======================================================================================================================*/
/*======================================================================================================================
 *                                                      ENUMS
======================================================================================================================*/

/*======================================================================================================================
 *                                              STRUCTURES AND OTHER TYPEDEFS
======================================================================================================================*/

/*======================================================================================================================
 *                                              GLOBAL VARIABLE DECLARATIONS
======================================================================================================================*/
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
// Arduino Uno doesn't have enough SRAM to store 100 samples of IR led data and red led data in 32-bit format
// To solve this problem, 16-bit MSB of the sampled data will be truncated. Samples become 16-bit data.
uint16_t irBuffer[50];
uint16_t redBuffer[50];
#else
// For ESP Chips
uint32_t irBuffer[100];
uint32_t redBuffer[100];
#endif

byte ledBrightness = 60;
byte sampleAverage = 4;
byte ledMode = 2;
byte sampleRate = 100;
int pulseWidth = 411;
int adcRange = 4096;
/*======================================================================================================================
 *                                                  FUNCTION PROTOTYPES
======================================================================================================================*/

class HeartRateSensor 
{
    public:
        HeartRateSensor();
        /**
         * @brief Initialize MAX3010x Sensor
         * 
         */
        void begin();

        /**
         * @brief Get Constant Update of BPM and SPO2
         * 
         */
        void update();

        /**
         * @brief Get the Beats Per Minute object
         * 
         * @return Float
         */
        float getBeatsPerMinute() const;

        /**
         * @brief Get the Beat Avg object
         * 
         * @return int
         */
        int getBeatAvg() const;

    private:
        MAX30105 particleSensor;
        const byte RATE_SIZE = 4; // Increase this for more averaging. 4 is good.
        byte rates[4]; // Array of heart rates
        byte rateSpot = 0;
        long lastBeat = 0; // Time at which the last beat occurred

        float beatsPerMinute;
        int beatAvg;
};