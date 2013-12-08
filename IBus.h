#pragma once

class Data;
class Address;

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
	BusWriter(IBusDevice&);
};

// SPI-specific stuff

class ParamsSpi
{};

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

