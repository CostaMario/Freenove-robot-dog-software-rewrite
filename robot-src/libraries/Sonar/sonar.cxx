#include "sonar.h"

Sonar::Sonar()
{
    std::cout << "SETUP WIRING: " << wiringPiSetupGpio() << std::endl;
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    digitalWrite(TRIGGER_PIN, LOW);
    usleep(30);
}

float Sonar::GetDistance()
{
    float dist_cm = 0;

    for(int i = 0; i < 5; i++)
    {
        digitalWrite(TRIGGER_PIN, HIGH);
        usleep(20);
        digitalWrite(TRIGGER_PIN, LOW);

        while (digitalRead(ECHO_PIN) == LOW);

        auto start = std::chrono::high_resolution_clock::now();

        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

        while (digitalRead(ECHO_PIN) == HIGH && microseconds < 300*60)
        {
            elapsed = std::chrono::high_resolution_clock::now() - start;
            microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        }

        dist_cm += microseconds * 340.0 / 2.0 / 10000.0;
    }

    return dist_cm / 5;
}

Sonar::~Sonar()
{
    
}