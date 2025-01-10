#ifndef ODOM_H
#define ODOM_H

#include <ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Quaternion.h>
#include <math.h>
#include <Arduino.h>
#include "encoder.h"
// Lớp xử lý Odometry
class Odometry {
public:
    // Constructor
    Odometry(float wheelRadius, float baseWidth, int ticksPerRevolution,ros::NodeHandle& nodeHandle);

    // Cập nhật số xung encoder
    void updateEncoders(int ticksL1, int ticksL2, int ticksR1, int ticksR2, float deltaT);

    // Lấy dữ liệu odometry
    void getOdometry();
    void setup();
    void loop();
private:
    // Biến ROS
    ros::NodeHandle& nh;
    nav_msgs::Odometry odom;
    ros::Publisher* odom_pub;
    // Các tham số xe
    float R;                 // Bán kính bánh xe
    float L;                 // Khoảng cách giữa hai bánh
    int TICKS_PER_REV;       // Số xung mỗi vòng encoder

    // Biến toàn cục
    float x, y, theta;       // Vị trí và góc quay
    float vx, vy, omega;     // Vận tốc tuyến tính và góc

    // Tính tốc độ góc từ encoder
    float calculateWheelSpeed(int ticks, float deltaT);

};

#endif // ODOMETRY_H
