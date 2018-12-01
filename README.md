# Instruction to run the Tiago Librarian demo simulation

Software Framework

1) ROS Kinetic
2) Ubuntu 16.04 LTS




Note: Assuming all the TIAGo packages are set on your computer

## Challenge Packages 

1) From the repository, copy following packages to the ROS workspace and do catkin build

```
mob_manip_challenge_2018  
mob_manip_gui
```


## Use-case 1: Delivering book to a table

Starting the simulation with MoveIt! and ROS navigation stack
```
$ roslaunch mob_manip_challenge_2018 mob_manip_2018_bringup_all.launch
```

Starting the grasping pipeline
```
$ roslaunch mob_manip_challenge_2018 pick_place_bringup.launch
```

Starting the demo execution node
```
$ rosrun mob_manip_challenge_2018 library_robot_bringup.py
```

## Use-case 2: Guiding student to the shelf

Starting the simulation with MoveIt! and ROS navigation stack
```
$ roslaunch mob_manip_challenge_2018 mob_manip_2018_bringup_all.launch
```
Start rqt to start GUI, Load the Mob manip GUI from Plugins->Mob_Manip_GUI


Now you can select a book and robot will guide you





