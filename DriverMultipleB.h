#pragma once
#include "Spi.h"
#include "I2c.h"

class DriverMultipleB
{
public:
    DriverMultipleB()
    {}
    virtual IBusDevice& BusDevice() = 0;
    void DoWork()
    {
        BusDevice().Write(Data());
    }
};

class DriverMultipleBSpi : public DriverMultipleB
{
public:
    DriverMultipleBSpi(IBusChannelSpi* aBusChannelSpi)
    : iBusChannelSpi(aBusChannelSpi)
    , iParamsSpi(kSpiClockMax, kSpiPhase, kSpiPolarity)
    , iBusDeviceSpi(new BusDeviceSpi(*iBusChannelSpi, iParamsSpi))
    {}
    virtual IBusDevice& BusDevice()
    {
        return *iBusDeviceSpi;
    }
    ~DriverMultipleBSpi()
    {
        delete iBusDeviceSpi;
        delete iBusChannelSpi;
    }
private:
    static const int    kSpiClockMax    = 1000000;
    static const bool   kSpiPhase       = false;
    static const bool   kSpiPolarity    = false;
private:
    IBusChannelSpi* iBusChannelSpi;
    ParamsSpi       iParamsSpi;
    BusDeviceSpi*   iBusDeviceSpi;
};

class DriverMultipleBI2c : public DriverMultipleB
{
public:
    DriverMultipleBI2c(IBusChannelI2c* aBusChannel)
    : iBusChannel(aBusChannel)
    , iParams()
    , iBusDevice(new BusDeviceI2c(*iBusChannel, iParams))
    {}
    virtual IBusDevice& BusDevice()
    {
        return *iBusDevice;
    }
    ~DriverMultipleBI2c()
    {
        delete iBusDevice;
        delete iBusChannel;
    }
private:
    IBusChannelI2c* iBusChannel;
    ParamsI2c       iParams;
    BusDeviceI2c*   iBusDevice;
};

