#include "DriverSpi.h"
#include "DriverMultipleA.h"
#include "DriverMultipleB.h"
#include "DriverSpiMultiParams.h"

#include <iostream>

int gValidations = 0;
int gReads = 0;
int gWrites = 0;

class BusSpiTest : public IBusSpi
{
private:
    class BusChannelSpiTest : public IBusChannelSpi
    {
    public:
        BusChannelSpiTest(BusSpiTest& aBusSpiTest)
        : iBusSpiTest(aBusSpiTest)
        {}
        bool ValidateParams(const ParamsSpi& aParams)
        {
            return iBusSpiTest.ValidateParams(aParams);
        }
        Data Read(const ParamsSpi& aParams)
        {
            return iBusSpiTest.Read(aParams);
        }
        void Write(const ParamsSpi& aParams, Data aData)
        {
            iBusSpiTest.Write(aParams, aData);
        }
    private:
        BusSpiTest& iBusSpiTest;
    };
public:
    IBusChannelSpi* Create(Address)
    {
        return new BusChannelSpiTest(*this);
    }
private:
    Data Read(const ParamsSpi&)
    {
        gReads++;
        return Data();
    }
    void Write(const ParamsSpi&, Data)
    {
        gWrites++;
    }
    bool ValidateParams(const ParamsSpi&)
    {
        gValidations++;
        return true;
    }
};

using namespace std;

int main()
{
    BusSpiTest bus1;

    DriverSpi d1(bus1.Create(Address()));
    d1.DoWork();

    DriverMultipleA d2(bus1.Create(Address()));
    d2.DoWork();

    DriverMultipleBSpi d3(bus1.Create(Address()));
    d3.DoWork();

    cout << "gValidations=" << gValidations << endl;
    cout << "gWrites=" << gWrites << endl;
    cout << "gReads=" << gReads << endl;

    if ( gValidations != 3 || gWrites != 3 || gReads != 0 )
        return -1;

    return 0;
}
