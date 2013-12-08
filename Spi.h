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
    int GetClockMaxHz() const { return iClockMaxHz; }
    bool GetPhase()     const { return iPhase; }
    bool GetPolarity()  const { return iPolarity; }
private:
    int   iClockMaxHz;
    bool  iPhase;
    bool  iPolarity;
};

typedef IBus<ParamsSpi>         IBusSpi;
typedef IBusChannel<ParamsSpi>  IBusChannelSpi;
typedef BusDevice<ParamsSpi>    BusDeviceSpi;
