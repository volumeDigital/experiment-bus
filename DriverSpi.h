#pragma once
#include "BusSpi.h"

/*  DriverSpi declares its dependency on an IBusChannelSpi&. This
    is used to create an BusDeviceSpi utility class, which is then
    used to create a BusWriter utility class. The use of utility
    classes is completely at the driver author's discretion.
*/

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

