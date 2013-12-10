#pragma once
#include "Spi.h"

/*  DriverSpi declares its dependency on an IBusChannelSpi&. This
    is used to create an BusDeviceSpi utility class, which is then
    used to create a BusWriter utility class. The use of utility
    classes is completely at the driver author's discretion.
*/

class DriverSpi
{
public:
    DriverSpi(IBusChannelSpi* aBusChannelSpi)
    : iBusChannelSpi(aBusChannelSpi)
    , iParamsSpi(kSpiClockMax, kSpiPhase, kSpiPolarity)
    , iBusDeviceSpi(*iBusChannelSpi, iParamsSpi)
    , iBusWriter(iBusDeviceSpi)
    {}
    void DoWork()
    {
        // We avoid the BusWriter here as its interface is empty :)
        iBusDeviceSpi.Write(Data());
    }
private:
    static const int    kSpiClockMax    = 1000000;
    static const bool   kSpiPhase       = false;
    static const bool   kSpiPolarity    = false;
private:
    IBusChannelSpi* iBusChannelSpi;
    ParamsSpi       iParamsSpi;
    BusDeviceSpi    iBusDeviceSpi;
    BusWriter       iBusWriter;
};

