#include "../smbus.h"
#include "PCA9685.h"
#include <math.h>
#include <unistd.h>
#include <iostream>

PCA9685::PCA9685(int address)
{
    _handle = open("/dev/i2c-1", O_RDWR);
    _address = address;
    
    if (ioctl(_handle, I2C_SLAVE, _address) < 0) {
        std::cout << std::endl << "The I2C Device couldn't be assigned a slave address." << std::endl;
        exit(2);
    }
    
    reset();
}

void PCA9685::reset()
{
    write(__MODE1, (char)__MODE1_RESTART);
    usleep(10000);
}

void PCA9685::setPWMFreq(const unsigned int freq)
{
    // The python implementation of this method deeply confuses me, so I'll leave
    // the translation to another day

    float prescaleval = 25000000.0;
    prescaleval /= 4096.0;
    prescaleval /= (float)freq;
    prescaleval -= 1.0;
    unsigned int prescale = (unsigned int)std::floor(prescaleval + 0.5);

    __s32 oldmode = read(__MODE1);
    __s32 newmode = (oldmode & __MODE1_RESTART) | 0x10;
    //std::cout << "oldmode "<< oldmode << " newmode " << (int)newmode << "newmode float" << newmode << " prescale " << prescale << std::endl;
    write(__MODE1, (char)newmode);
    write(__PRESCALE, (char)prescale);
    write(__MODE1, (char)oldmode);
    usleep(50000);
    write(__MODE1, (char)oldmode / 0x80);
}

void PCA9685::setMotorPWM(const unsigned int channel, const unsigned int duty)
{
    setPWM(channel, 0, duty);
}

void PCA9685::setServoPulse(const unsigned int channel, const unsigned int pulse)
{
    int pulse_f = (int)(pulse*4096/20000);
    setPWM(channel, 0, pulse_f);
}

signed int PCA9685::write(const unsigned int reg, const unsigned char value)
{
    return i2c_smbus_write_byte_data(_handle, reg, value);
}

__s32 PCA9685::read(const unsigned int reg)
{
    return i2c_smbus_read_byte_data(_handle, reg);
}

void PCA9685::setPWM(const unsigned int channel, const unsigned int on, const unsigned int off)
{
    //std::cout << "WRITIN " << (on & 0xFF) << " " << (on >> 8) << " " << (off & 0xFF) << " " << (off >> 8) << '\n';
    write(__LED0_ON_L+4*channel, (char)(on & 0xFF));
    write(__LED0_ON_H+4*channel, (char)(on >> 8));
    write(__LED0_OFF_L+4*channel, (char)(off & 0xFF));
    write(__LED0_OFF_H+4*channel, (char)(off >> 8));
}


Servo::Servo(PCA9685* pca9685, unsigned int angleMin, unsigned int angleMax)
{
    _pca9685 = pca9685;
    _angleMin = angleMin;
    _angleMax = angleMax;
    pca9685->setPWMFreq(50);
}

void Servo::setServoAngle(unsigned int channel, unsigned int angle)
{
    if(angle < _angleMin)
    {
        angle = _angleMin;
    }
    else if(angle > _angleMax)
    {
        angle = _angleMax;
    }

    unsigned int mapped = mapAngle(angle, 0, 180, 102, 512);
    //std::cout << (int)mapped << std::endl;
    _pca9685->setPWM(channel, 0, mapped);
    //std::cout << _pca9685->read(__LED0_OFF_L+4*channel) << "  " << (int)(mapped & 0xFF) << std::endl;
}

unsigned int Servo::mapAngle(unsigned int value,
                            unsigned int fromLow,
                            unsigned int fromHigh,
                            unsigned int toLow,
                            unsigned int toHigh)
{
    return (unsigned int)((toHigh-toLow)*(value-fromLow) / (fromHigh-fromLow) + toLow);
}