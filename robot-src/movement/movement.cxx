#include "movement.h"
#include <math.h>

Leg::Leg(Servo* servo, unsigned const int top, unsigned const int middle, unsigned const int foot)
{
    _servo = servo;
    top_servo = top;
    middle_servo = middle;
    foot_servo = foot;
    UpdateLeg();
}

void Leg::SetTarget(const float x, const float y, const float z)
{
    x_target = x;
    y_target = y;
    z_target = z;
    UpdateLeg();
}

void Leg::UpdateLeg()
{
    float target_dist = sqrt(x_target*x_target + y_target*y_target);
    _servo->setServoAngle(top_servo, (int)((acos(x_target/target_dist) / 3.14f)* 180) + 90);
}