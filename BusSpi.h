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
    ParamsSpi(unsigned int aClockMaxHz, bool aPhase, bool aPolarity, int aReadWidth = 1)
    : iClockMaxHz(aClockMaxHz)
    , iPhase(aPhase)
    , iPolarity(aPolarity)
    , iReadWidth(aReadWidth)
    {}
    int  GetClockMaxHz()    const { return iClockMaxHz; }   // The controller is allowed to downgrade this, all the way to DC
    bool GetPhase()         const { return iPhase; }        // Controller must respect this.
    bool GetPolarity()      const { return iPolarity; }     // Controller must respect this.
    int  GetReadWidth()     const { return iReadWidth; }    // Controller must respect this.
private:
    int     iClockMaxHz;
    bool    iPhase;
    bool    iPolarity;
    int     iReadWidth;
};

typedef IBus<ParamsSpi>         IBusSpi;
typedef IBusChannel<ParamsSpi>  IBusChannelSpi;
typedef BusDevice<ParamsSpi>    BusDeviceSpi;

