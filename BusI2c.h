#pragma once
#include "Bus.h"

/*  Definition of the I2C bus classes, utiliising the helper templates in Bus.h.

    In this case, I2C has no params (although maybe it should). Drivers still
    depend on IBusChannel of some find, and combine it with a Params to build
    the BusDevice utility class, just like any other driver.
*/

class ParamsI2c {};
typedef IBus<ParamsI2c>         IBusI2c;
typedef IBusChannel<ParamsI2c>  IBusChannelI2c;
typedef BusDevice<ParamsI2c>    BusDeviceI2c;
