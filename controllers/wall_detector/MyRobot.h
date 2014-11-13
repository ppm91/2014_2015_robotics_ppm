#ifndef MY_ROBOT_H_
#define MY_ROBOT_H_

/**
 * @file    MyRobot.h
 * @brief   Controller for detecting wall with the frontal camera of the robot.
 *
 * @author  Pablo Pérez Martínez <100275550@alumnos.uc3m.es>
 * @date    13/11/2014
 */

#include <iostream>
#include <webots/DifferentialWheels.hpp>

using namespace std;
using namespace webots;

#define NUM_DISTANCE_SENSOR 2
#define DISTANCE_LIMIT      100
#define MAX_SPEED           100

class MyRobot : public DifferentialWheels {
    public:
        // You may need to define your private methods or variables, like
        //  Constructors, helper functions, etc.

        /**
         * @brief Empty constructor of the class.
         */
        MyRobot();

        /**
         * @brief Destructor of the class.
         */
        ~MyRobot();

        /**
         * @brief Function with the logic of the controller.
         * @param
         * @return
         */
        void run();
        
    private:
        int _time_step;
        
        // velocities
        double _left_speed, _right_speed;

        // sensors
        Camera *_forward_camera;
        Camera *_spherical_camera;
};

#endif

