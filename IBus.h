#pragma once

class Data {};
class Address {};

// IBusDevice is what we will use to instantiate BusWriter classes
class IBusDevice
{
public:
	virtual Data Read() = 0;
	virtual void Write(Data) = 0;
};

// This utility class is what drivers might use to do work.
class BusWriter
{
public:
	BusWriter(IBusDevice& aBusDevice)
	: iBusDevice(aBusDevice)
	{}
private:
	IBusDevice& iBusDevice;
};

// SPI-specific stuff

class ParamsSpi {};

class IBusChannelSpi
{
public:
	virtual Data Read(const ParamsSpi&);
	virtual void Write(const ParamsSpi&, Data);
};

class IBusSpi
{
	virtual IBusChannelSpi* Create(Address);
};

class BusDeviceSpi : public IBusDevice
{
public:
	BusDeviceSpi(IBusChannelSpi&, const ParamsSpi&);
	virtual Data Read();
	virtual void Write(Data);
};

// Templated bus stuff.

template<typename Params>
class IBusChannel
{
public:
	virtual Data Read(const Params&);
	virtual void Write(const Params&, Data);
};

template<typename Params>
class IBus
{
	virtual IBusChannel<Params>* Create(Address);
};

template<typename Params>
class BusDevice : public IBusDevice
{
public:
	BusDevice(IBusChannel<Params> aChannel, const Params& aParams)
	: iChannel(aChannel)
	, iParams(aParams)
	{}
	virtual Data Read()
	{
		return iChannel.Read(iParams);
	}
	virtual void Write(Data aData)
	{
		iChannel.Write(iParams, aData);
	}
private:
	IBusChannel<Params> iChannel;
	const Params& 		iParams;
};

// I2C bus stuff, using helper templates

class ParamsI2c {};

// I2c bus drivers implements IBusI2c:
typedef IBus<ParamsI2c>         IBusI2c;
// and the implementation Create()s these:
typedef IBusChannel<ParamsI2c> 	IBusChannelI2c;
// which are received in a driver dtor and combined with ParamsI2c to make:
typedef BusDevice<ParamsI2c> 	BusDeviceI2c;

// Driver stuff

class DriverSpi
{
public:
		DriverSpi(IBusChannelSpi& aBusChannelSpi)
		: iParamsSpi()
		, iBusDeviceSpi(aBusChannelSpi, iParamsSpi)
		, iBusWriter(iBusDeviceSpi)
		{}
private:
	ParamsSpi 		iParamsSpi;
	BusDeviceSpi 	iBusDeviceSpi;
	BusWriter		iBusWriter;
};

class DriverMultipleA
{
public:
	DriverMultipleA(IBusChannelSpi& aBusChannelSpi)
	: iParamsSpi()
	, iParamsI2c()
	, iBusDevice(new BusDeviceSpi(aBusChannelSpi, iParamsSpi))
	{}
	DriverMultipleA(IBusChannelI2c& aBusChannelI2c)
	: iParamsSpi()
	, iParamsI2c()
	, iBusDevice(new BusDeviceI2c(aBusChannelI2c, iParamsI2c))
	{}
private:
	ParamsSpi		iParamsSpi;
	ParamsI2c		iParamsI2c;
	IBusDevice*		iBusDevice;
};

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
	: iParamsSpi()
	, iBusDeviceSpi(aBusChannelSpi, iParamsSpi)
	{}
	virtual IBusDevice& BusDevice()
	{
		return iBusDeviceSpi;
	}
private:
	ParamsSpi		iParamsSpi;
	BusDeviceSpi	iBusDeviceSpi;
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