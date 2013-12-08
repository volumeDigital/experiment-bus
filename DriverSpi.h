#pragma once
#include "Spi.h"

class DriverSpi
{
public:
        DriverSpi(IBusChannelSpi& aBusChannelSpi)
        : iParamsSpi(kSpiClockMax, kSpiPhase, kSpiPolarity)
        , iBusDeviceSpi(aBusChannelSpi, iParamsSpi)
        , iBusWriter(iBusDeviceSpi)
        {}
private:
    static const int    kSpiClockMax    = 1000000;
    static const bool   kSpiPhase       = false;
    static const bool   kSpiPolarity    = false;
private:
    ParamsSpi       iParamsSpi;
    BusDeviceSpi    iBusDeviceSpi;
    BusWriter       iBusWriter;
};
