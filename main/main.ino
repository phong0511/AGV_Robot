  #include <ros.h>
#include "gps.h"
#include "odometry.h"
#include "imu.h"
// Define GPS pins and baud rate
static const int RXPin = 0, TXPin = 1;
static const uint32_t GPSBaud = 9600;
// Thông số xe
const float R = 0.05;   // Bán kính bánh xe (m)
const float L = 0.3;    // Khoảng cách giữa hai bánh xe (m)
const int TICKS_PER_REV = 1000; // Số xung mỗi vòng encoder
// ROS NodeHandle
ros::NodeHandle nhGps;
ros::NodeHandle nhOdometry;
ros::NodeHandle nhImu;
//  object
GPS gps(RXPin, TXPin, GPSBaud, nhGps);
Odometry odometry(R,L,TICKS_PER_REV,nhOdometry);
IMU imu(nhImu);
void setup() {
    Serial.begin(115200);
    gps.setup();
    odometry.setup();
    imu.setup();
}

void loop() {
    gps.loop();
    odometry.loop();
    imu.loop();
    nhGps.spinOnce();
    nhOdometry.spinOnce();
    nhImu.spinOnce();
    delay(100); 
}
