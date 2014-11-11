/**
 * @file    MyRobot.h
 * @brief   The robot goest with odometry until it reaches the end of the map avoiding the obstacle
 *
 * @author  Pablo Pérez Martínez <100275550@alumnos.uc3m.es>
 * @date    11-11-2014
 */



#include <iostream>
#include <cmath>

#include <webots/DifferentialWheels.hpp>

using namespace webots;
using namespace std;

#define MAX_SPEED 100
#define ENCODER_RESOLUTION 5
#define WHEEL_RADIO 0.0825
#define DISTANCE_BETWEEN_WHEELS 0.32
#define X_0 0
#define Y_0 0
#define Z_0 -9
#define ANGLE_0 0
#define ERROR 0.25


// Here is the declaration class of your controller.
// This class declares how to initialize and how to run your controller.
// Note that this class derives from DifferentialWheels who derives from Robot,
// both inherits all its functions
class MyRobot : public DifferentialWheels {
    private:

        double _left_encoder, _right_encoder;
        double _previous_left_encoder, _previous_right_encoder;

        double _left_speed, _right_speed;

        double _distance;
        double _angle;
        double _absolut_z, _absolut_y, _absolut_angle;


        int _status;

        int _time_step;

        /**
         * @brief Sets the encoders to 0
         * @param
         * @return
         */
        void reset_status();

        /**
         * @brief Refresh the position and orientation
         * @param
         * @return
         */
        void refresh_odometry();

        /**
         * @brief The robot goes to the requested point
         * @param The coordinates Z and Y of the  point
         * @return
         */
        void go_to_point(double z, double y);

    public:
    
        /**
         * @brief Empty constructor of the class.
         * @param
         * @return
         */
        MyRobot();

        /**
         * @brief Destructor of the class.
         * @param
         * @return
         */
        ~MyRobot();

        /**
         * @brief Shows the odometry data
         * @param
         * @return
         */
        void print_odometry_data();

        /**
         * @brief User defined function for initializing and running the robot.
         * @param
         * @return
         */
        void run();
};
