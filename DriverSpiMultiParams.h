#pragma once
#include "Spi.h"

/*  This Driver allows SPI quadread for reading data. The ctor validates its params,
    and records the possibility for quadread in a bool member to be checked at runtime.
*/

class DriverSpiMultiParams
{
public:
    DriverSpiMultiParams(IBusChannelSpi& aBusChannelSpi)
    : iParamsSpiNormal(kSpiClockMax, kSpiPhase, kSpiPolarity, kSpiWidthNormal)
    , iParamsSpiQuadRead(kSpiClockMax, kSpiPhase, kSpiPolarity, kSpiWidthQuadRead)
    , iBusChannelSpi(aBusChannelSpi)
    {
        iUseQuadRead = aBusChannelSpi.ValidateParams(iParamsSpiQuadRead);   // bonus if true!
    }
private:
    void SetData(Data aData) const
    {
        // Hardware requires that we always use normal params for write.
        iBusChannelSpi.Write(iParamsSpiNormal, aData);
    }
    Data GetData() const
    {
        // Hardware allows us to Use quadread params for read, if possible.
        return iBusChannelSpi.Read(iUseQuadRead ? iParamsSpiQuadRead : iParamsSpiNormal); 
    }

private:
    static const int    kSpiClockMax    = 1000000; // max clock rate == 1MHz
    static const bool   kSpiPhase       = false;
    static const bool   kSpiPolarity    = false;
    static const int    kSpiWidthNormal = 1;
    static const int    kSpiWidthQuadRead = 4;
private:
    ParamsSpi       iParamsSpiNormal;
    ParamsSpi       iParamsSpiQuadRead;
    IBusChannelSpi& iBusChannelSpi;
    bool            iUseQuadRead;
};

