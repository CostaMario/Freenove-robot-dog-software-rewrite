#include "../smbus.c"
#include "PCA9685.h"

PCA9685::PCA9685(int address)
{
    _address = address;
    write(__MODE1, 0x00);
}

void PCA9685::setPWMFreq(const unsigned char freq)
{
    // The python implementation of this method deeply confuses me, so I'll leave
    // the translation to another day
}

void PCA9685::setMotorPWM(const unsigned char channel, const unsigned char duty)
{
    setPWM(channel, 0, duty);
}

void PCA9685::setServoPulse(const unsigned char channel, const unsigned char pulse)
{
    char pulse_f = (char)(pulse*4096/20000);
    setPWM(channel, 0, pulse_f);
}

void PCA9685::write(const unsigned char reg, const unsigned char value)
{
    i2c_smbus_write_byte_data(_address, reg, value);
}

__s32 PCA9685::read(const unsigned char reg)
{
    i2c_smbus_read_byte_data(_address, reg);
}

void PCA9685::setPWM(const unsigned char channel, const unsigned char on, const unsigned char off)
{
    write(__LED0_ON_L+4*channel, on & 0xFF);
    write(__LED0_ON_H+4*channel, on >> 8);
    write(__LED0_OFF_L+4*channel, off & 0xFF);
    write(__LED0_OFF_H+4*channel, off >> 8);
}