#pragma once

#include <linux/i2c-dev.h> // For SMBus commands
#include <sys/ioctl.h>     // For ioctl()
#include <fcntl.h>         // For O_RDWR
#include <unistd.h>        // For open()

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

    void setPWMFreq(const unsigned int freq);
    void setMotorPWM(const unsigned int channel, const unsigned int duty);

    void setServoPulse(const unsigned int channel, const unsigned int pulse);

    void setPWM(const unsigned int channel, const unsigned int on, const unsigned int off);


    int _address;
    int _handle;

    signed int write(const unsigned int reg, const unsigned char value);
    __s32 read(const unsigned int reg);
};

class Servo
{
    public:

    Servo(PCA9685* pca9685, unsigned int angleMin = 18, unsigned int angleMax = 162);

    void setServoAngle(unsigned int channel, unsigned int angle);

    private:

    PCA9685* _pca9685;
    unsigned int _angleMin;
    unsigned int _angleMax;

    unsigned int mapAngle(unsigned int value,
                            unsigned int fromLow,
                            unsigned int fromHigh,
                            unsigned int toLow,
                            unsigned int toHigh);
};