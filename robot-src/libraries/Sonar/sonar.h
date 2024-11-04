#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <chrono>

#define TRIGGER_PIN 27
#define ECHO_PIN 22

class Sonar
{
    public:
    Sonar();
    float GetDistance();
    ~Sonar();
};