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
    
    ws2811_return_t ret;
    if ((ret = ws2811_init(&ledstring)) != WS2811_SUCCESS)
    {
        fprintf(stderr, "ws2811_init failed: %s\n", ws2811_get_return_t_str(ret));
        return ret;
    }
    
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