#ifndef __ARTRONSHOP_SHT45_H__
#define __ARTRONSHOP_SHT45_H__

#include <Arduino.h>
#include <Wire.h>

class ArtronShop_SHT45 {
    private:
        uint8_t _addr;
        TwoWire *_wire = NULL;
        float _t, _h;

    public:
        ArtronShop_SHT45(TwoWire *wire = &Wire, uint8_t addr = 0x44) ;
        bool begin() ;
        bool measure() ;
        float temperature() ;
        float humidity() ;

};

#endif