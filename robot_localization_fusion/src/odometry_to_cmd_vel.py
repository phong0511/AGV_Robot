#!/usr/bin/env python3

import rospy
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Twist
import serial

# Kết nối với Arduino
ser = serial.Serial('/dev/ttyUSB0', 9600)  # Đảm bảo port đúng với Arduino

def odometry_callback(msg):
    # Lấy thông tin vận tốc từ odometry
    linear_x = msg.twist.twist.linear.x
    angular_z = msg.twist.twist.angular.z

    # Tạo thông điệp cmd_vel
    cmd_vel_msg = Twist()
    cmd_vel_msg.linear.x = linear_x
    cmd_vel_msg.angular.z = angular_z

    # Gửi tín hiệu đến encoder (Arduino)
    send_to_encoder(linear_x, angular_z)

    # Xuất ra cmd_vel (nếu cần sử dụng)
    cmd_vel_pub.publish(cmd_vel_msg)

def send_to_encoder(linear_x, angular_z):
    """
    Chuyển vận tốc tuyến tính và góc thành tín hiệu cho encoder
    """
    # Giả sử robot là loại differential drive
    wheel_base = 0.5  # khoảng cách giữa hai bánh xe
    wheel_radius = 0.1  # bán kính bánh xe

    # Tính tốc độ góc của từng bánh
    v_left = (linear_x - (angular_z * wheel_base / 2)) / wheel_radius
    v_right = (linear_x + (angular_z * wheel_base / 2)) / wheel_radius

    # Đóng gói dữ liệu và gửi qua Serial
    data = f"{v_left},{v_right}\n"
    ser.write(data.encode())

def main():
    rospy.init_node('odometry_to_cmdvel', anonymous=True)

    # Subscriber cho topic /odometry/filtered
    rospy.Subscriber('/odometry/filtered', Odometry, odometry_callback)

    # Publisher cho topic /cmd_vel (tùy chọn)
    global cmd_vel_pub
    cmd_vel_pub = rospy.Publisher('/cmd_vel', Twist, queue_size=10)

    rospy.spin()

if __name__ == '__main__':
    try:
        main()
    except rospy.ROSInterruptException:
        pass

