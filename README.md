Small hobby Arduino/ROS project. Mainly for keeping references of how to setup the development environment (terminal-based: vim, platformio command line tool, ROS)

## Hardware 

- Arduino Nano Atmega 328
- laser module
- digital temperature module

## General references

- [platformio docs](http://docs.platformio.org/en/latest/installation.html)

## Installing platformio and project

Obviously, get latest source from git (was more up-to-date than PyPI)

    mkvirtualenv --python=$(which python2) platformio
    pip install -e "git+https://github.com/platformio/platformio-core#egg=platformio-core"

Prepare serial port reading

    sudo usermod -a -G dialout $(echo $USER)

Install udev rules file

    sudo wget https://raw.githubusercontent.com/platformio/platformio-core/develop/scripts/99-platformio-udev.rules /etc/udev/rules.d/99-platformio-udev.rules

Create empty project dir or clone

    platformio init -b nanoatmega328 --ide vim

## Workflow

Hack Arduino code and compile

    platformio run

Search libraries (example: ROS)

    platformio lib search ros

Install desired package

    platformio lib install 345

Upload to board

    platformio run -t upload    #or: make upload

## Installing ROS environment

    sudo apt-get install ros-kinetic-desktop-full ros-kinetic-rosserial ros-kinetic-rosserial-arduino

Don't forget to

    source /opt/ros/kinetic/setup.zsh

## Run stuff

Plug board to USB port and run serial connection node (OUTSIDE virtualenv)

    roslaunch serial.launch --screen

Toggle laser by 

    rostopic pub /switch_laser std_msgs/Empty "{}" --once

Read temperature by 

    rostopic echo /temperature
