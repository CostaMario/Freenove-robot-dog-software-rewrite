#include <iostream>
#include <ws2811.h>
#include "MPU6050.h"
#include "PCA9685.h"
#include "sonar.h"
#include <unistd.h>

ws2811_t ledstring =
{
    .freq = 800000,
    .dmanum = 10,
    .channel =
    {
        [0] =
        {
            .gpionum = 18,
            .invert = 0,
            .count = 7,
            .strip_type = WS2811_STRIP_GRB,
            .brightness = 255,
        },
    },
};

ws2811_led_t red = 0x00200000;
ws2811_led_t green = 0x00002000;
ws2811_led_t blue = 0x00000020;

int main()
{
    std::cout << "Testing, testing" << std::endl;
    
    ws2811_return_t ret;
    if ((ret = ws2811_init(&ledstring)) != WS2811_SUCCESS)
    {
        fprintf(stderr, "ws2811_init failed: %s\n", ws2811_get_return_t_str(ret));
        return ret;
    }

    MPU6050 gyro;
    std::cout << gyro << std::endl;

    PCA9685 pca9685;
    Servo servo(&pca9685);

    Sonar sonar;
    
    while (true)
    {
        gyro.updateData();
        //std::cout << "X: " << gyro.getGyroX() << std::endl;
        //std::cout << "Y: " << gyro.getGyroY() << std::endl;
        //std::cout << "Z: " << gyro.getGyroZ() << std::endl;

        ledstring.channel[0].leds[0] = red;
        ws2811_render(&ledstring);
        usleep(500000);

        //ledstring.channel[0].leds[0] = green;
        //ws2811_render(&ledstring);
        //usleep(500000);

        //ledstring.channel[0].leds[0] = blue;
        //ws2811_render(&ledstring);
        //usleep(500000);

        ledstring.channel[0].leds[0] = 0;
        ws2811_render(&ledstring);
        usleep(500000);

        for(unsigned char i = 0; i<16; i++)
        {
            usleep(10);
            servo.setServoAngle(i, 90);
        }
    }
}