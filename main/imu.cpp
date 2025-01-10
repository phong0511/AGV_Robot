#include "imu.h"

IMU::IMU(ros::NodeHandle& nodeHandle)
    : imu(), nh(nodeHandle), imu_pub("imu/data", &imu_msg),
      velocityX(0), velocityY(0), velocityZ(0),
      angularVelX(0), angularVelY(0), angularVelZ(0),
      Ax(0), Ay(0), Az(0), Gx(0), Gy(0), Gz(0),
      prevTime(0), currTime(0) {}

void IMU::setup() {
    Serial.begin(115200);
    while (!Serial) {}

    Wire.begin();
    imu.Config(&Wire, bfs::Mpu9250::I2C_ADDR_PRIM);

    if (!imu.Begin()) {
        Serial.println("Error initializing IMU");
        while (1) {}
    }
    nh.initNode();
    
    nh.advertise(imu_pub);
    prevTime = millis();
}

void IMU::readAccelerometer() {
    Ax = imu.accel_x_mps2();
    Ay = imu.accel_y_mps2();
    Az = imu.accel_z_mps2();
}

void IMU::readGyrometer() {
    Gx = imu.gyro_x_radps();
    Gy = imu.gyro_y_radps();
    Gz = imu.gyro_z_radps();
}

void IMU::calculateAngularVelocity() {
    angularVelX = Gx * 180 / M_PI;
    angularVelY = Gy * 180 / M_PI;
    angularVelZ = Gz * 180 / M_PI;
}

void IMU::calculateLinearVelocity() {
    currTime = millis();
    float dt = (currTime - prevTime) / 1000.0; // Convert ms to seconds
    velocityX += Ax * dt;
    velocityY += Ay * dt;
    velocityZ += Az * dt;
    prevTime = currTime;
}

void IMU::populateIMUMessage() {
    imu_msg.header.stamp =  nh.now();
    imu_msg.orientation.x = 0.0;
    imu_msg.orientation.y = 0.0;
    imu_msg.orientation.z = 0.0;
    imu_msg.orientation.w = 1.0;

    imu_msg.linear_acceleration.x = velocityX;
    imu_msg.linear_acceleration.y = velocityY;
    imu_msg.linear_acceleration.z = velocityZ;

    imu_msg.angular_velocity.x = angularVelX;
    imu_msg.angular_velocity.y = angularVelY;
    imu_msg.angular_velocity.z = angularVelZ;
}

void IMU::loop() {
    if (imu.Read()) {
        readAccelerometer();
        readGyrometer();
        calculateLinearVelocity();
        calculateAngularVelocity();
        populateIMUMessage();
        imu_pub.publish(&imu_msg);
    }
}
