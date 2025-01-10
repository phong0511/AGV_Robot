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
    if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    float v_left = 0;
    float v_right = 0;

    // Tách dữ liệu vận tốc
    int comma_index = data.indexOf(',');
    if (comma_index != -1) {
      v_left = data.substring(0, comma_index).toFloat();
      v_right = data.substring(comma_index + 1).toFloat();
    }

    // Chuyển đổi vận tốc thành PWM (giả sử v_left/v_right nằm trong [-1, 1])
    int pwm_left = constrain(map(v_left, -1, 1, -255, 255), -255, 255);  
    //v_left: Giá trị đầu vào (tốc độ góc của bánh xe trái), -1, 1: Khoảng giá trị đầu vào, Giả sử vận tốc góc của bánh xe trái nằm trong khoảng [-1, 1],  
    //-255, 255: Khoảng giá trị đầu ra.→ Kết quả sẽ được ánh xạ sang khoảng [-255, 255] (giá trị PWM để điều khiển động cơ)
    int pwm_right = constrain(map(v_right, -1, 1, -255, 255), -255, 255);
    }
 
}
