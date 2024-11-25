#pragma once

#include "PCA9685.h"

class Leg
{
    private:
        unsigned int top_servo;
        unsigned int middle_servo;
        unsigned int foot_servo;

        const float top_radius = 2.5f;
        const float middle_length = 5.5f;
        const float foot_length = 6.0f;

        const float x_pivot_offset = 2.0f;
        const float y_pivot_offset = 2.5f;

        float middle_to_foot_ratio;

        Servo* _servo;

        float x_target = 0.0f;
        float y_target = -10.0f;
        float z_target = 0.0f;

    public:
        Leg(Servo* servo, unsigned const int top, unsigned const int middle, unsigned const int foot);
        void SetTarget(const float x, const float y, const float z);
        void UpdateLeg();
};