#include "movement.h"
#include <math.h>
#include <iostream>

Leg::Leg(Servo* servo, unsigned const int top, unsigned const int middle, unsigned const int foot, const bool left)
{
    is_left = left;

    _servo = servo;
    top_servo = top;
    middle_servo = middle;
    foot_servo = foot;

    middle_to_foot_ratio = middle_length / (foot_length + middle_length);

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
    float xy_dist = sqrt(x_target*x_target + y_target*y_target);
    float z_dist = z_target;

    int angle_top = (int)((acos(x_target/xy_dist) / 3.14f)* 180);
    //if(angle_top < 0) angle_top = 0;
    //if(angle_top > 100) angle_top = 100;

    std::cout << "TOP: " << angle_top << '\n';

    xy_dist -= y_pivot_offset;
    z_dist -= x_pivot_offset;

    if(xy_dist < .5)
        xy_dist = .5;

    float c_length = sqrt(xy_dist*xy_dist + z_dist*z_dist);
    float alpha = acos(abs(z_dist)/c_length);
    if(z_dist < 0)
    {
        alpha = 3.14f - alpha;
    }
    float cos_a = ((c_length*c_length) + (middle_length*middle_length) - (foot_length*foot_length)) / (2.0*c_length*middle_length);
    if(cos_a > 1)
        cos_a = 1;
    else if(cos_a < -1)
        cos_a = -1;
    float alpha_prime = acos(cos_a);

    //float x_mid = xy_dist * middle_to_foot_ratio;
    //float z_mid = z_dist * middle_to_foot_ratio;

    int angle_middle = abs((int)((alpha - alpha_prime) / 3.14f * 180.0));
    //angle_middle -= alpha;
    //angle_middle = 180 - angle_middle;
    std::cout << "Length: " << c_length << '\n';
    std::cout << "a: " << alpha << '\n';
    std::cout << "a': " << alpha_prime << '\n';
    std::cout << "MIDDLE: " << angle_middle << '\n';
    //std::cout << "Alpha: " << alpha << '\n';
    //if(angle_middle < 0) angle_middle = 0;
    //if(angle_middle > 150) angle_middle = 150;
    float cos_b = ((middle_length*middle_length) + (foot_length*foot_length) - (c_length*c_length)) / (2.0*middle_length*foot_length);
    if(cos_b > 1)
        cos_b = 1;
    else if(cos_b < -1)
        cos_b = -1;
    int angle_foot = (int)((acos(cos_b) / 3.14f)* 180);
    std::cout << "Foot: " << angle_foot << '\n';
    //angle_foot = 180 - angle_foot;
    //if(angle_foot < 45) angle_foot = 45;
    //if(angle_foot > 130) angle_foot = 130;
    std::cout << "Foot: " << angle_foot << '\n';

    if(is_left)
    {
        angle_middle = 180 - angle_middle;
        angle_foot = 180 - angle_foot;
    }

    _servo->setServoAngle(top_servo, angle_top);
    _servo->setServoAngle(middle_servo, angle_middle);
    _servo->setServoAngle(foot_servo, angle_foot);
}