#include "ArtronShop_SHT45.h"

ArtronShop_SHT45::ArtronShop_SHT45(TwoWire *wire, uint8_t addr) {
    this->_wire = wire;
    this->_addr = addr;
}

bool ArtronShop_SHT45::begin() {
    this->_wire->beginTransmission(this->_addr);
    return this->_wire->endTransmission() == 0;
}

bool ArtronShop_SHT45::measure() {
    this->_wire->beginTransmission(this->_addr);
    this->_wire->write(0xFD);
    if (this->_wire->endTransmission() != 0) {
        this->_t = -99;
        this->_h = -99;
        return false;
    }

    delay(10);  // wait measuring

    if (this->_wire->requestFrom(this->_addr, (uint8_t)6) != 6) {
        this->_t = -99;
        this->_h = -99;
        return false;
    }

    uint8_t rx_bytes[6];
    memset(rx_bytes, 0, 6);
    this->_wire->readBytes(rx_bytes, 6);

    uint16_t t_ticks = ((uint16_t)rx_bytes[0] << 8) | rx_bytes[1];
    // checksum_t = rx_bytes[2];
    uint16_t rh_ticks = ((uint16_t)rx_bytes[3] << 8) | rx_bytes[4];
    // checksum_rh = rx_bytes[5];
    this->_t = -45.0f + (175.0f * (t_ticks / 65535.0f));
    this->_h = -6.0f + (125.0f * (rh_ticks / 65535.0f));
    if (this->_h > 100) {
        this->_h = 100;
    }
    if (this->_h < 0) {
        this->_h = 0;
    }

    return true;
}

float ArtronShop_SHT45::temperature() {
    return this->_t;
}

float ArtronShop_SHT45::humidity() {
    return this->_h;
}
