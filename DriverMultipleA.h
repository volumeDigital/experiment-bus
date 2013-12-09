#pragma once
#include "BusSpi.h"
#include "BusI2c.h"

/*  When hardware supports multiple bus types, the driver can present
    multiple ctors, each of which constructs the driver appropriately.

    This model allows you to have a single class, if that's important
    to you.

    The IBusDevice* is initialised differently by each ctor. It's a
    /little/ wasteful to have both Params initialised: We could hide
    these behind a void* and static cast when creating the BusDevice.
*/

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
    ~DriverMultipleA()
    {
        delete iBusDevice;
    }
private:
    static const int    kSpiClockMax    = 1000000;
    static const bool   kSpiPhase       = false;
    static const bool   kSpiPolarity    = false;
private:
    ParamsSpi       iParamsSpi;
    ParamsI2c       iParamsI2c;
    IBusDevice*     iBusDevice;
};
