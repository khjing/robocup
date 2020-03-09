# robocup
Created by SEU robocup team  
This directory contains our training program

## contest
This is our first training, providing a simple auto-navigation demo using navigation package based on ros-kinetic/ubuntu 16.04LTS.  

 requirements:
- hardware:
  - turtlebot: a kind of service robot
  - hokuyo: laser scan
- software:
  - ros-kinetic on ubuntu 16.04 LTS
  - hokuyo laser driver. You can download from their github: https://github.com/ros-drivers/hokuyo_node
  - some turtlebot packages provided in the directory, as provided in turtlebot_src

If you are familiar with ros, you can configure it easily. If you have any detailed questions, please ask me via email:
kkhjing@163.com. I'm glad to help.

## astar
This is our second training, which requires our teammates finish by their own. I just provide a demo here. 

requirements:
- hardware:
 - all in simulation environment, so you don't need any additional hardware
- software:
 - Since you already compiled the source code in turtlebot_src, your environment is ready
 - maps: see maps.zip
 - you also have to configure your move_base.launch description in $(turtlebot_navigation)/launch/includes/move_base.xml. Add a parameter:  
 '''xml
 <param name="base_global_planner" value="astar_planner/AstarPlanner"/>
 '''
