#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/Joy.h"

float linear_x = 0.0;
float angular_z = 0.0;

void joyCallback(const sensor_msgs::Joy::ConstPtr& msg)
{
  linear_x = msg->axes[1];
  angular_z = msg->axes[3];
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "joy_node2");
  ros::NodeHandle nh;

  ros::Publisher cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);

  ros::Rate loop_rate(10);

  ros::Subscriber sub = nh.subscribe("/joy", 1000, joyCallback);

  while (ros::ok())
  {
    geometry_msgs::Twist msg;

    msg.linear.x = linear_x;
    msg.angular.z = angular_z;

    cmd_vel_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
