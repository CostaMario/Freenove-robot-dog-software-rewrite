#include "movement.h"
#include <math.h>

Leg::Leg(Servo* servo, unsigned const int top, unsigned const int middle, unsigned const int foot)
{
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
    float yz_dist = z_target;

    int angle_top = (int)((acos(x_target/xy_dist) / 3.14f)* 180);
    if(angle_top < 0) angle_top = 0;
    if(angle_top > 100) angle_top = 100;

    xy_dist += y_pivot_offset;
    yz_dist += x_pivot_offset;

    float c_length = sqrt(xy_dist*xy_dist + yz_dist*yz_dist);
    int alpha = (int)((acos(yz_dist/c_length) / 3.14f)* 180);

    float middle_projection = c_length / middle_to_foot_ratio;
    int angle_middle = ((int)((acos(middle_projection/middle_length) / 3.14f) * 180)) - alpha;
    if(angle_middle < 0) angle_middle = 0;  
    if(angle_middle > 150) angle_middle = 150;

    float foot_projection = c_length - middle_projection;
    int angle_foot = (int)((asin(foot_projection/foot_length) / 3.14f) * 180);
    if(angle_foot < 45) angle_foot = 45;
    if(angle_foot > 130) angle_foot = 130;

    _servo->setServoAngle(top_servo, 90);
    _servo->setServoAngle(middle_servo, 90);
    _servo->setServoAngle(foot_servo, 90);
}