#pragma once

// Registers/etc.
#define __SUBADR1            0x02
#define __SUBADR2            0x03
#define __SUBADR3            0x04
#define __MODE1              0x00
#define __PRESCALE           0xFE
#define __LED0_ON_L          0x06
#define __LED0_ON_H          0x07
#define __LED0_OFF_L         0x08
#define __LED0_OFF_H         0x09
#define __ALLLED_ON_L        0xFA
#define __ALLLED_ON_H        0xFB
#define __ALLLED_OFF_L       0xFC
#define __ALLLED_OFF_H       0xFD

class PCA9685
{
    public:

    PCA9685(int address=0x40);

    void setPWMFreq(const unsigned char freq);
    void setMotorPWM(const unsigned char channel, const unsigned char duty);

    void setServoPulse(const unsigned char channel, const unsigned char pulse);

    private:

    int _address;

    void write(const unsigned char reg, const unsigned char value);
    __s32 read(const unsigned char reg);

    void setPWM(const unsigned char channel, const unsigned char on, const unsigned char off);
};