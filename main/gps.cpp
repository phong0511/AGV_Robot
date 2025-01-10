#include "gps.h"

GPS::GPS(int rxPin, int txPin, uint32_t baudRate, ros::NodeHandle& nodeHandle)
    : gpsSerial(rxPin, txPin), nh(nodeHandle), gpsPublisher("gps_data", &gpsMsg) {
    gpsSerial.begin(baudRate);
    gpsMsg.header.frame_id = "gps_frame";
}

void GPS::setup() {
    nh.initNode();
    nh.advertise(gpsPublisher);
}

void GPS::loop() {
    while (gpsSerial.available() > 0) {
        gps.encode(gpsSerial.read());
    }

    if (gps.location.isUpdated()) {
        gpsMsg.latitude = gps.location.lat();
        gpsMsg.longitude = gps.location.lng();
        gpsMsg.altitude = gps.altitude.meters();
        gpsMsg.position_covariance_type = sensor_msgs::NavSatFix::COVARIANCE_TYPE_UNKNOWN;
        gpsMsg.header.stamp = nh.now(); // Timestamp

        gpsPublisher.publish(&gpsMsg); // Publish GPS data
    }

    nh.spinOnce(); // ROS loop
    delay(100);    // Adjust for your application
}
