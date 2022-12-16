#!/usr/bin/env python3

from dynamic_reconfigure.client import Client
from rospy import init_node

init_node('emitter_modifier', anonymous=True)

client = Client('d435i_camera/stereo_module', timeout=15)

check = client.get_configuration()

if check.get('emitter_enabled') == 1:
        emitter = { 'emitter_enabled' : 0 }
else:
        emitter = { 'emitter_enabled' : 1 }

config = client.update_configuration(emitter)

client.close()




