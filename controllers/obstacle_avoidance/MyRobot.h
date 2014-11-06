/**
 * @file    MyRobot.h
 * @brief   Definitions
 *
 * @author  Pablo Pérez <100275550@alumnos.uc3m.es>
 * @date    06-11-2014
 */

#include <iostream>
#include <cmath>
#include <webots/DifferentialWheels.hpp>

using namespace std;
using namespace webots;
#define NUM_DISTANCE_SENSOR 16
#define DISTANCE_LIMIT 100
#define MAX_SPEED       100

class MyRobot : public DifferentialWheels {
private:
    int _time_step;

    DistanceSensor * _distance_sensor[NUM_DISTANCE_SENSOR];

    Compass * _my_compass;
    double _left_speed, _right_speed;
    enum Mode {
        STOP,
        FORWARD,
        TURN_LEFT,
        TURN_RIGHT,
        OBSTACLE_AVOID,
        SHARP_TURN,
        BACKWARDS
    };
    
      Mode _mode;
public:
    /**
         * @brief Empty constructor of the class.
         */
    MyRobot();

    /**
         * @brief Destructor of the class.
         */
    ~MyRobot();

    /**
         * @brief User defined function for initializing and running the robot.
         */
    void run();

    /**
          * @brief An example for converting bearing vector from compass to angle (in degrees).
          */
    double convert_bearing_to_degrees(const double* in_vector);
};
