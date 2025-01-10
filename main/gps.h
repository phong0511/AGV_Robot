#ifndef GPS_H
#define GPS_H

#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ros.h>
#include <sensor_msgs/NavSatFix.h>

class GPS {
public:
    GPS(int rxPin, int txPin, uint32_t baudRate, ros::NodeHandle& nodeHandle);
    void setup();
    void loop();

private:
    TinyGPSPlus gps;
    SoftwareSerial gpsSerial;
    ros::NodeHandle& nh;
    sensor_msgs::NavSatFix gpsMsg;
    ros::Publisher gpsPublisher;
};

#endif // GPS_H
