#pragma once
#include "Spi.h"

class DriverSpi
{
public:
        DriverSpi(IBusChannelSpi& aBusChannelSpi)
        : iParamsSpi(1000, false, false)
        , iBusDeviceSpi(aBusChannelSpi, iParamsSpi)
        , iBusWriter(iBusDeviceSpi)
        {}
private:
    ParamsSpi       iParamsSpi;
    BusDeviceSpi    iBusDeviceSpi;
    BusWriter       iBusWriter;
};
