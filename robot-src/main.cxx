#include <iostream>
#include<ws2811.h>
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
            .strip_type = WS2811_STRIP_RGB,
            .brightness = 255,
        },
    },
};

ws2811_led_t color = 0x00200000;

int main()
{
    std::cout << "Testing, testing" << std::endl;
    while (true)
    {
        ledstring.channel[0].leds[0] = color;
        ws2811_render(&ledstring);
        usleep(500000);
        ledstring.channel[0].leds[0] = 0;
        ws2811_render(&ledstring);
        usleep(500000);
    }
}