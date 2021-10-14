![Curiosity](/banner.jpg)

# Background

Ago is my version of [Leo Rover](https://www.leorover.tech/), an UGV platform by Fictionlab. Ago is intended to be an hardware platform for future software projects in autonomous operations and IA development.

All information for building Ago is free and public open source for anyone to build their own.

* Motorization: Moving the wheels is done with serial bus servo motors. I went for Dynamixel AX-18A I took from a previous hexapod project. 
* Construction Method: Instead of using the [Actobotics construction system](https://www.servocity.com/actobotics), Perseverance will be built from aluminum extrusions connected by 3D-printed plastic parts.

# Development Status and Milestones
<img src="https://github.com/andreagavazzi/Curiosity/blob/main/images/nasa_logo.jpg" alt="ag_logo" width="600"/>

**Ago version 1.0** 

- [ ] This milestone includes a basic rolling chassis that is mechanically functional
- [ ] Aestetic add-ons on the chassis (reactor, attachments and linkages, ...)
- [ ] Camera turret (webcamto be defined)
- [ ] Dynamixel + OpenCR controller

# IA, Sensors and Controllers
<img src="https://github.com/andreagavazzi/Ago/assets/ag_logo.jpg" alt="ag_logo" width="200"/>
  
Ago is a [ROS](http://ros.org) robotics platform running on Linux Ubuntu.

**ROS Melodic**: [a ground-up rewrite of a ROS-centric stack](https://github.com/srmainwaring/curio) by Rhys Mainwaring (srmainwaring) is extensive and powerful. Going beyond responding to `/cmd_vel` commands, it also calculates `/odom` by interpolating the AX-18A position encoder ~270 degree feedback into full 360 degrees. Plus visualizing rover state in RViz, and files to put a digital Perseverance in Gazebo robot simulation environment.

**NVIDIA Jetson AGX Xavier**: The latest addition to the Jetson platform. It’s an AI computer for autonomous machines, delivering the performance of a GPU workstation in an embedded module under 30W. Jetson AGX Xavier is designed for robots, drones and other autonomous machines.

Additional material can be found in my [Onedrive shared folder](https://1drv.ms/f/s!AkUtNLbG6ptfpiPbJ0WKSoO58hIA).
