/**
 * @file    wall_detector.cpp
 * @brief   Controller for detecting wall with the frontal camera of the robot.
 *
 * @author  Pablo Pérez Martínez <100275550@uc3m.es>
 * @date    13/11/2014
 */

#include "MyRobot.h"

/**
 * @brief Main program.
 */
int main(int argc, char **argv)
{
    MyRobot* my_robot = new MyRobot();

    my_robot->run();

    delete my_robot;

    return 0;
}
