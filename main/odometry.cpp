#include "odometry.h"

Odometry::Odometry(float wheelRadius, float baseWidth, int ticksPerRevolution,ros::NodeHandle& nodeHandle)
    : R(wheelRadius), L(baseWidth), TICKS_PER_REV(ticksPerRevolution),  nh(nodeHandle),x(0.0), y(0.0), theta(0.0), vx(0.0), vy(0.0), omega(0.0) {
     
      }
void Odometry::setup() {
    // Khởi tạo Publisher cho topic "odom"
    odom_pub = new ros::Publisher("odom", &odom);

    // Đăng ký Publisher với ROS
    nh.advertise(*odom_pub);

    // Nếu cần, bạn có thể cài đặt các tham số khởi tạo ở đây
    // Ví dụ: nh.setParam("odom_frame_id", "odom");
}
float Odometry::calculateWheelSpeed(int ticks, float deltaT) {
    return (ticks / (float)TICKS_PER_REV) * (2.0 * M_PI) / deltaT; // rad/s
}

void Odometry::updateEncoders(int ticksL1, int ticksL2, int ticksR1, int ticksR2, float deltaT) {
    // Tính tốc độ góc từng bánh
    float omegaL1 = calculateWheelSpeed(ticksL1, deltaT);
    float omegaL2 = calculateWheelSpeed(ticksL2, deltaT);
    float omegaR1 = calculateWheelSpeed(ticksR1, deltaT);
    float omegaR2 = calculateWheelSpeed(ticksR2, deltaT);

    // Tính trung bình tốc độ góc bánh trái và phải
    float omegaL = (omegaL1 + omegaL2) / 2.0;
    float omegaR = (omegaR1 + omegaR2) / 2.0;

    // Tính động học
    vx = R * (omegaR + omegaL) / 2.0;
    vy = 0.0; // Differential drive không có chuyển động ngang
    omega = R * (omegaR - omegaL) / L;

    // Tích phân để cập nhật vị trí
    x += vx * cos(theta) * deltaT;
    y += vx * sin(theta) * deltaT;
    theta += omega * deltaT;

    // Đảm bảo góc theta trong khoảng [-pi, pi]
    theta = fmod(theta + M_PI, 2 * M_PI) - M_PI;
}
void Odometry::getOdometry() {
    odom.header.stamp = nh.now();
    odom.header.frame_id = "odom";
    odom.child_frame_id = "base_link";

    odom.pose.pose.position.x = x;
    odom.pose.pose.position.y = y;
    odom.pose.pose.position.z = 0.0;

    geometry_msgs::Quaternion quat;
    quat.z = sin(theta / 2.0);
    quat.w = cos(theta / 2.0);
    odom.pose.pose.orientation = quat;

    odom.twist.twist.linear.x = vx;
    odom.twist.twist.linear.y = vy;
    odom.twist.twist.angular.z = omega;
    odom_pub->publish(&odom);
}
void Odometry::loop(){
    int ticksL1 = encoder1_value;  // Số xung giả định từ encoder bánh trái (L1)
    int ticksL2 = encoder2_value;  // Số xung giả định từ encoder bánh trái (L2)
    int ticksR1 = encoder3_value;  // Số xung giả định từ encoder bánh phải (R1)
    int ticksR2 = encoder4_value;  // Số xung giả định từ encoder bánh phải (R2)
    float deltaT = 0.1; // Thời gian giữa các lần cập nhật (giả định 0.1s)
        // Cập nhật thông tin encoder
    updateEncoders(ticksL1, ticksL2, ticksR1, ticksR2, deltaT);

    // Lấy và publish dữ liệu odometry
    getOdometry();

    // ROS xử lý trong vòng lặp
    nh.spinOnce();
    delay(100);  // Delay cho vòng lặp Arduino (100ms)
}
