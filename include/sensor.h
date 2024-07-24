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