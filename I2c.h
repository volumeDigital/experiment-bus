#pragma once
#include "Bus.h"

// I2C bus stuff, using helper templates
class ParamsI2c {};
typedef IBus<ParamsI2c>         IBusI2c;
typedef IBusChannel<ParamsI2c>  IBusChannelI2c;
typedef BusDevice<ParamsI2c>    BusDeviceI2c;

