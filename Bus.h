#pragma once

/*  I've conciously modelled devices on a bus as having a pure read/write interface.
    This specifically to avoid discussion/confusion about what that API should look
    like: I don't attempt to address that here.

    The focus is on how best to capture the relationship between an IBus, and the 
    IBusDevice that accesses it. Some classes are about encapsulation, while some
    are utility classes that aid the driver author.
*/

/*  Data and Address are used in this API so we can avoid naming parameters, while
    remaining clear.
*/

class Data {};
class Address {};

/*  IBusDevice, as before, is a utility interface that hides the details of the
    physical connection to the device.
*/

class IBusDevice
{
public:
    virtual ~IBusDevice() {}
    virtual Data Read() = 0;
    virtual void Write(Data) = 0;
};

/*  Subordinate concrete utility classes may use the IBusDevice to implement
    some common access patterns (endianess, address/data width). This is intended
    to be the same as GD's model.
*/

class BusWriter
{
public:
    BusWriter(IBusDevice& aBusDevice)
    : iBusDevice(aBusDevice)
    {}
private:
    IBusDevice& iBusDevice;
};

/*  Here's the controversial part. We model the problem space as though busses are
    /not/ interchangeable. In other words, there is no IBus interface, and each bus
    returns its own type of channel. There is definitely no IBusParams interface.

    I'll stick my neck out here and suggest that /every/ driver that receives a
    bus-like object /cares/ about what type of bus it is, and that in every case,
    the hardware would like to advertise the constraints upon its channel.

    This is certainly the case for both SPI, I2C and SDIO. Very probably 1-wire too.

    The cleanest way to achieve this is for drivers to declare their dependencies
    in the ctor, with the highest degree of abstraction possible: IBusChannel is
    too abstract, but IBusChannelSpi is perfect.

    IBusChannel and IBus are interfaces templated on some Params type. The templates
    provide a consistent, well-defined model for bus relationships that require
    parameters.

    - IBus implementations use the Create() pattern.
    - IBusChannel implementations pass a Params ref as context for each transaction.

    Please refer to Spi.h and I2c.h to see how they're used.

    ValidateParams() allows a driver to propose params to the channel and see whether
    they're supported. The definition of 'supported' should be documented in the params
    class definition, for example Polarity is non-negotiable, but ClockMaxHz can be silently
    downgraded by the controller (because SPI is a synchronous bus).

    This seems to resolve the Capabilities() issue, but in a more generic way: It might
    not be possible for a controller to support arbitrary combinations of bus parameters,
    so a system where params are validated (rather than individual capabilities) is both
    safer and more convenient (for now).

    Also note that drivers are not /required/ to use ValidateParams() - if they wish, the
    author can choose for the driver to fail on first bus access rather than the ctor.
*/

template<typename Params>
class IBusChannel
{
public:
    virtual ~IBusChannel() {}
    virtual bool ValidateParams(const Params&) = 0;
    virtual Data Read(const Params&) = 0;
    virtual void Write(const Params&, Data) = 0;
};

template<typename Params>
class IBus
{
public:
    virtual ~IBus() {}
    virtual IBusChannel<Params>* Create(Address) = 0;
};

/*  BusDevice is a templated utility class that implements IBusDevice.

    The implementation here bundles the channel and params, obviating
    the need to use the IBusChannel and params for every transaction.

    The ctor also validates the params on your behalf, removing more
    boilerplate from driver ctors.
*/

class ExceptionInvalidParams {};

template<typename Params>
class BusDevice : public IBusDevice
{
public:
    BusDevice(IBusChannel<Params>& aChannel, const Params& aParams)
    : iChannel(aChannel)
    , iParams(aParams)
    {
        // Automatically validate params on construction
        if ( ! iChannel.ValidateParams(iParams) )
            throw new ExceptionInvalidParams();
    }
    virtual Data Read()
    {
        // Forward params.
        return iChannel.Read(iParams);
    }
    virtual void Write(Data aData)
    {
        // Forward params.
        iChannel.Write(iParams, aData);
    }
private:
    IBusChannel<Params>&   iChannel;
    const Params&          iParams;
};
