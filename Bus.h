#pragma once

class Data {};
class Address {};

// IBusDevice is what we will use to instantiate BusWriter classes
// It can be used on its own, but it is a utility class, and is non-essential.
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

// Templated bus stuff.

template<typename Params>
class IBusChannel
{
public:
	virtual Data Read(const Params&) = 0;
	virtual void Write(const Params&, Data) = 0;
};

template<typename Params>
class IBus
{
public:
	virtual IBusChannel<Params>* Create(Address) = 0;
};

template<typename Params>
class BusDevice : public IBusDevice
{
public:
	BusDevice(IBusChannel<Params>& aChannel, const Params& aParams)
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
	IBusChannel<Params>&   iChannel;
	const Params& 		   iParams;
};
