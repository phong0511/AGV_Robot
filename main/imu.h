#ifndef IMU_H
#define IMU_H

#include "mpu9250.h"
#include <ros.h>
#include <sensor_msgs/Imu.h>
#include <Wire.h>

class IMU {
public:
    IMU(ros::NodeHandle& nodeHandle);
    void setup();
    void loop();

private:
    bfs::Mpu9250 imu;
    sensor_msgs::Imu imu_msg;
     ros::NodeHandle& nh;  
    ros::Publisher imu_pub;

    float velocityX, velocityY, velocityZ;
    float angularVelX, angularVelY, angularVelZ;
    float Ax, Ay, Az;
    float Gx, Gy, Gz;

    unsigned long prevTime;
    unsigned long currTime;

    void readAccelerometer();
    void readGyrometer();
    void calculateAngularVelocity();
    void calculateLinearVelocity();
    void populateIMUMessage();
};

#endif // IMU_H
