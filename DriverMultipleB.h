#pragma once
#include "Spi.h"
#include "I2c.h"

class DriverMultipleB
{
public:
    DriverMultipleB();
    virtual IBusDevice& BusDevice() = 0;
    void DoWork()
    {
        // access BusDevice();
    }
};

class DriverMultipleBSpi : public DriverMultipleB
{
public:
    DriverMultipleBSpi(IBusChannelSpi& aBusChannelSpi)
    : iParamsSpi(kSpiClockMax, kSpiPhase, kSpiPolarity)
    , iBusDeviceSpi(aBusChannelSpi, iParamsSpi)
    {}
    virtual IBusDevice& BusDevice()
    {
        return iBusDeviceSpi;
    }
private:
    static const unsigned int   kSpiClockMax    = 1000000;
    static const bool           kSpiPhase       = false;
    static const bool           kSpiPolarity    = false;
private:
    ParamsSpi       iParamsSpi;
    BusDeviceSpi    iBusDeviceSpi;
};

class DriverMultipleBI2c : public DriverMultipleB
{
public:
    DriverMultipleBI2c(IBusChannelI2c& aBusChannel)
    : iParams()
    , iBusDevice(aBusChannel, iParams)
    {}
    virtual IBusDevice& BusDevice()
    {
        return iBusDevice;
    }
private:
    ParamsI2c      iParams;
    BusDeviceI2c   iBusDevice;
};
