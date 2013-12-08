#pragma once
#include "Bus.h"

/*  Definition of the I2C bus classes, utiliising the helper templates in Bus.h.

    Please read I2c.h first.

    In contrast to ParamsI2c, ParamsSpi is a busy class. In this implementation,
    the driver will only use the ctor, and the IBusSpi implementer will use the
    getter functions to setup the SPI controller, for each transaction.
*/

class ParamsSpi
{
public:
    ParamsSpi(unsigned int aClockMaxHz, bool aPhase, bool aPolarity, int aWidth = 1)
    : iClockMaxHz(aClockMaxHz)
    , iPhase(aPhase)
    , iPolarity(aPolarity)
    , iWidth(aWidth)
    {}
    int  GetClockMaxHz()    const { return iClockMaxHz; }
    bool GetPhase()         const { return iPhase; }
    bool GetPolarity()      const { return iPolarity; }
    int  GetWidth()         const { return iWidth; }
private:
    int     iClockMaxHz;
    bool    iPhase;
    bool    iPolarity;
    int     iWidth;
};

typedef IBus<ParamsSpi>         IBusSpi;
typedef IBusChannel<ParamsSpi>  IBusChannelSpi;
typedef BusDevice<ParamsSpi>    BusDeviceSpi;
