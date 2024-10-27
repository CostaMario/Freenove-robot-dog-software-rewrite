#include "sonar.h"

Sonar::Sonar()
{
    std::cout << "SETUP WIRING: " << wiringPiSetup();
}

Sonar::~Sonar()
{
    
}