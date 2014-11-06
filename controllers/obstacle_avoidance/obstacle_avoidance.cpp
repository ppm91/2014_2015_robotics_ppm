/**
 * @file    main.cpp
 * @brief   main program
 *
 * @author  Pablo Pérez <100275550@alumnos.uc3m.es>
 * @date    06-11-2014
 */

#include "MyRobot.h"

/*
 * Main program.
 * The arguments of the main function can be specified by the
 * "controllerArgs" field of the Robot node
 */
int main(int argc, char **argv)
{
    MyRobot* my_robot = new MyRobot();

    my_robot->run();

    delete my_robot;

    return 0;
}
