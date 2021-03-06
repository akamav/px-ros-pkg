#include <ros/ros.h>

#include "mavlink_serial_client/SerialComm.h"

void
printTopicInfo(void)
{
    // print published/subscribed topics
    std::string nodeName = ros::this_node::getName();

    ros::V_string topics;
    ros::this_node::getSubscribedTopics(topics);

    std::string topicsStr = nodeName + ":\n\tsubscribed to topics:\n";
    for (unsigned int i = 0; i < topics.size(); ++i)
    {
        topicsStr += ("\t\t" + topics.at(i) + "\n");
    }

    topicsStr += "\tadvertised topics:\n";
    ros::this_node::getAdvertisedTopics(topics);
    for (unsigned int i = 0; i < topics.size(); ++i)
    {
        topicsStr += ("\t\t" + topics.at(i) + "\n");
    }

    ROS_INFO("%s", topicsStr.c_str());
}

int
main(int argc, char** argv)
{
    ros::init(argc, argv, "mavlink");

    std::string nodeName = ros::this_node::getName();
    ros::NodeHandle nh(nodeName);

    ros::NodeHandle pnh("~");

    std::string portStr;
    pnh.param("serial_port", portStr, std::string("/dev/ttyS0"));

    int baudrate;
    pnh.param("baudrate", baudrate, 115200);

    std::string frameId;
    pnh.param("frame_id", frameId, std::string("fcu"));

    px::SerialComm comm(nh, frameId);
    if (!comm.open(portStr, baudrate))
    {
        return -1;
    }

    printTopicInfo();

    ros::spin();

    return 0;
}
