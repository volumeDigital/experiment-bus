#pragma once
#include "Spi.h"
#include "I2c.h"

class DriverMultipleA
{
public:
    DriverMultipleA(IBusChannelSpi& aBusChannelSpi)
    : iParamsSpi(kSpiClockMax, kSpiPhase, kSpiPolarity)
    , iParamsI2c()
    , iBusDevice(new BusDeviceSpi(aBusChannelSpi, iParamsSpi))
    {}
    DriverMultipleA(IBusChannelI2c& aBusChannelI2c)
    : iParamsSpi(kSpiClockMax, kSpiPhase, kSpiPolarity)
    , iParamsI2c()
    , iBusDevice(new BusDeviceI2c(aBusChannelI2c, iParamsI2c))
    {}
private:
    static const unsigned int   kSpiClockMax    = 1000000;
    static const bool           kSpiPhase       = false;
    static const bool           kSpiPolarity    = false;

private:
    ParamsSpi       iParamsSpi;
    ParamsI2c       iParamsI2c;
    IBusDevice*     iBusDevice;
};
