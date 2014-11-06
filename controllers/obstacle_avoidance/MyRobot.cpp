#include "MyRobot.h"

//////////////////////////////////////////////
/**
 * @file    MyRobot.cpp
 * @brief   Robot behaviour
 *
 * @author  Pablo Pérez <100275550@alumnos.uc3m.es>
 * @date    06-11-2014
 */

MyRobot::MyRobot() : DifferentialWheels()
{
    _time_step = 64;

    _left_speed = 0;
    _right_speed = 0;

    _mode = FORWARD;

    _distance_sensor[0] = getDistanceSensor("ds1");
    _distance_sensor[1] = getDistanceSensor("ds14");
    _distance_sensor[2] = getDistanceSensor("ds4");
    _distance_sensor[3] = getDistanceSensor("ds11");
    _distance_sensor[4] = getDistanceSensor("ds12");
    _distance_sensor[5] = getDistanceSensor("ds0");
    _distance_sensor[6] = getDistanceSensor("ds15");
    _distance_sensor[7] = getDistanceSensor("ds3");
    _distance_sensor[8] = getDistanceSensor("ds2");
    _distance_sensor[9] = getDistanceSensor("ds13");
    _distance_sensor[10] = getDistanceSensor("ds5");
    _distance_sensor[11] = getDistanceSensor("ds6");
    _distance_sensor[12] = getDistanceSensor("ds7");
    _distance_sensor[13] = getDistanceSensor("ds8");
    _distance_sensor[14] = getDistanceSensor("ds9");
    _distance_sensor[15] = getDistanceSensor("ds10");
    
    for (int i=0; i<NUM_DISTANCE_SENSOR;i++){

        _distance_sensor[i]->enable(_time_step);
    }




}

//////////////////////////////////////////////

MyRobot::~MyRobot()
{
    for (int i=0; i<NUM_DISTANCE_SENSOR; i++) {
        _distance_sensor[i]->disable();
    }
}

//////////////////////////////////////////////

void MyRobot::run()
{
    int i;
    double  ir_val[8];
    while (step(_time_step) != -1) {
        // Read the sensors

        for(i=0;i<8;i++){
            ir_val[i] = _distance_sensor[i]->getValue();
        }

        // Control logic of the robot
        if ((ir_val[0] > DISTANCE_LIMIT) || (ir_val[2] > DISTANCE_LIMIT)||(ir_val[1] > DISTANCE_LIMIT)) {
            _mode = OBSTACLE_AVOID;
            cout << "Going back and turning left." << endl;
        }
        else{

            _mode = FORWARD;
            cout << "Moving forward." << endl;
        }

        if ((ir_val[4] == 0.0)&&(ir_val[3]== 0.0)&&(ir_val[1]==0.0)&&(ir_val[5]== 0.0)&&(ir_val[6]==0.0))
        {
            _mode = TURN_RIGHT;
            cout<<"Turning right"<<endl;
        }


        if((ir_val[3]!= 0.0)&&(ir_val[4]==0.0)&&(ir_val[1]==0.0)&&(ir_val[5]== 0.0)&&(ir_val[6]==0.0))
        {
            _mode = SHARP_TURN;
            cout<<"Turning to the right strongly"<<endl;
        }

        // Robot wheels mode
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
            _left_speed = MAX_SPEED / 1.25;
            _right_speed = MAX_SPEED;
            break;
        case TURN_RIGHT:
            _left_speed = MAX_SPEED;
            _right_speed = MAX_SPEED / 2.00;
            break;
        case OBSTACLE_AVOID:
            _left_speed = -MAX_SPEED / 3.0;
            _right_speed = -MAX_SPEED / 10.0;
            break;
        case SHARP_TURN:
            _left_speed = MAX_SPEED;
            _right_speed = MAX_SPEED / 4.00;
            break;
        case BACKWARDS:
            _left_speed = -MAX_SPEED;
            _right_speed =-MAX_SPEED;
            break;
        default:
            break;
        }

        /**
         * @brief Defines the wheels speed.
         */
        setSpeed(_left_speed, _right_speed);
    }
}

//////////////////////////////////////////////
