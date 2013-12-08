#pragma once
#include "Bus.h"

// SPI bus stuff, using helper templates
class ParamsSpi
{
public:
    ParamsSpi(unsigned int aClockMaxHz, bool aPhase, bool aPolarity)
    : iClockMaxHz(aClockMaxHz)
    , iPhase(aPhase)
    , iPolarity(aPolarity)
    {}
    unsigned int GetClockMaxHz() { return iClockMaxHz; }
    bool GetPhase() const { return iPhase; }
    bool GetPolarity() const { return iPolarity; }
private:
    const unsigned int    iClockMaxHz;
    const bool            iPhase;
    const bool            iPolarity;
};

typedef IBus<ParamsSpi>         IBusSpi;
typedef IBusChannel<ParamsSpi>  IBusChannelSpi;
typedef BusDevice<ParamsSpi>    BusDeviceSpi;
