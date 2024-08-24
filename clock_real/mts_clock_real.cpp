#include "clock_real_api.h"
#include "ClockReal.h"
#include "mts_core/enums.h"

extern "C"{
    MTS_CLOCK_REAL_API mts::Clock* createClock(mts::EnvironmentMode mode){
        if(mode != mts::ENVIR_REAL){
            return nullptr;
        }
        return new mts::ClockReal();
    }
    MTS_CLOCK_REAL_API void releaseClock(mts::Clock* clock){
        delete clock;
    }
}