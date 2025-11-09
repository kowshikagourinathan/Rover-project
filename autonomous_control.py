#!/usr/bin/env python3
import rospy
from geometry_msgs.msg import Twist
from sensor_msgs.msg import LaserScan

def callback(data):
    move = Twist()
    front = min(min(data.ranges[0:30]), min(data.ranges[330:360]))
    if front < 0.5:
        move.linear.x = 0.0
        move.angular.z = 0.5
    else:
        move.linear.x = 0.3
        move.angular.z = 0.0
    pub.publish(move)

rospy.init_node('autonomous_control')
pub = rospy.Publisher('/cmd_vel', Twist, queue_size=10)
rospy.Subscriber('/scan', LaserScan, callback)
rospy.spin()
