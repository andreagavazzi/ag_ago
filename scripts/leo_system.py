#!/usr/bin/env python

import rospy
import os
from dynamic_reconfigure.client import Client

from std_msgs.msg import Empty
from std_msgs.msg import String


def rebootCallback(x):
    rospy.loginfo("Reboot command invoked")
    os.system("shutdown -r now")


def shutdownCallback(x):
    rospy.loginfo("Shutdown command invoked")
    os.system("shutdown -h now")


def publishNamespace():
    namespace_pub = rospy.Publisher("robot_namespace", String, queue_size=1, latch=True)
    namespace = rospy.get_namespace()
    namespace_pub.publish(namespace)


def toggleEmitterCallback():    # Accende o spegne il laser
    rospy.loginfo("Toggle emitter command invoked")
    client = Client('d435i_camera/stereo_module', timeout=15)
    check = client.get_configuration()

    if check.get('emitter_enabled') == 1:
            emitter = { 'emitter_enabled' : 0 }
    else:
            emitter = { 'emitter_enabled' : 1 }

    client.update_configuration(emitter)
    client.close()


try:
    rospy.init_node("leo_system")
    pose_sub = rospy.Subscriber("system/shutdown", Empty, shutdownCallback)
    pose_sub = rospy.Subscriber("system/reboot", Empty, rebootCallback)
    pose_sub = rospy.Subscriber("system/emitter", Empty, toggleEmitterCallback)
    rospy.loginfo("Leo system node started!")

    publishNamespace()
except rospy.ROSInterruptException as e:
    rospy.logerr(e)

rospy.spin()