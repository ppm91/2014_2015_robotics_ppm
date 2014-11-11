/**
 * @file    MyRobot.h
 * @brief   The robot goes straight with odometry until it reaches the end of the map
 *
 * @author  Pablo Pérez Martínez <100275550@alumnos.uc3m.es>
 * @date    11-11-2014
 */

#include "MyRobot.h"

//////////////////////////////////////////////

MyRobot::MyRobot() : DifferentialWheels()
{
    _time_step = 64;

    enableEncoders(_time_step);

    _mode = FORWARD;
    _distance = 0;
}

//////////////////////////////////////////////

MyRobot::~MyRobot()
{
    disableEncoders();
}

//////////////////////////////////////////////

void MyRobot::run()
{

    // Main loop:
    // Perform simulation steps of 64 milliseconds
    // and leave the loop when the simulation is over
    while (step(_time_step) != -1)
    {

        //Get encoders values
        _left_encoder = getLeftEncoder();
        _right_encoder = getRightEncoder();

        //Converts rad to meters
        _distance = _left_encoder/ENCODER_RESOLUTION*WHEEL_RADIO;

        print_odometry_data();

        //Robot control
        if(_left_encoder > _right_encoder)
        {
            _mode = TURN_LEFT;
        }
        else
        {
            _mode = TURN_RIGHT
        }

        setSpeed(_left_speed, _right_speed);

        if (_distance > TOTAL_DISTANCE)
        {
            _left_speed = 0;
            _right_speed = 0;

            setSpeed(_left_speed, _right_speed);
        }
        switch (_mode){
        case STOP:
            _left_speed = 0;
            _right_speed = 0;
            break;
        case FORWARD:
            _left_speed = MAX_SPEED;
            _right_speed = MAX_SPEED;
            break;
        case TURN_LEFT:
            _left_speed = MAX_SPEED *0.9;
            _right_speed = MAX_SPEED;
            break;
        case TURN_RIGHT:
            _left_speed = MAX_SPEED;
            _right_speed = MAX_SPEED *0.9;
            break;
        default:
            break;
        }



    }
}

//////////////////////////////////////////////

void MyRobot::print_odometry_data()
{
    cout<< "Left Encoder: " << _left_encoder << endl << "Right Encoder: " << _right_encoder<< endl
        << "Distance: " << _distance << endl;
}
