#include "MyRobot.h"

//////////////////////////////////////////////


MyRobot::MyRobot() : DifferentialWheels()
{
    _time_step = 64;

    _left_speed = 0;
    _right_speed = 0;

    _mode = FORWARD;

    _distance_sensor[0] = getDistanceSensor("ds1");
    _distance_sensor[0]->enable(_time_step);
    _distance_sensor[1] = getDistanceSensor("ds14");
    _distance_sensor[1]->enable(_time_step);
    _distance_sensor[2] = getDistanceSensor("ds4");
    _distance_sensor[2]->enable(_time_step);
    _distance_sensor[3] = getDistanceSensor("ds11");
    _distance_sensor[3]->enable(_time_step);
    _distance_sensor[4] = getDistanceSensor("ds12");
    _distance_sensor[4]->enable(_time_step);
    _distance_sensor[5] = getDistanceSensor("ds0");
    _distance_sensor[5]->enable(_time_step);
    _distance_sensor[6] = getDistanceSensor("ds15");
    _distance_sensor[6]->enable(_time_step);
    _distance_sensor[7] = getDistanceSensor("ds3");
    _distance_sensor[7]->enable(_time_step);
    _distance_sensor[8] = getDistanceSensor("ds2");
    _distance_sensor[8]->enable(_time_step);
    _distance_sensor[9] = getDistanceSensor("ds13");
    _distance_sensor[9]->enable(_time_step);
    _distance_sensor[10] = getDistanceSensor("ds5");
    _distance_sensor[10]->enable(_time_step);
    _distance_sensor[11] = getDistanceSensor("ds6");
    _distance_sensor[11]->enable(_time_step);
    _distance_sensor[12] = getDistanceSensor("ds7");
    _distance_sensor[12]->enable(_time_step);
    _distance_sensor[13] = getDistanceSensor("ds8");
    _distance_sensor[13]->enable(_time_step);
    _distance_sensor[14] = getDistanceSensor("ds9");
    _distance_sensor[14]->enable(_time_step);
    _distance_sensor[15] = getDistanceSensor("ds10");
    _distance_sensor[15]->enable(_time_step);
    





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
    double ir1_val = 0.0, ir14_val = 0.0,ir4_val = 0.0,ir11_val = 0.0,ir12_val = 0.0,ir15_val = 0.0,ir0_val = 0.0,ir3_val=0.0;

    while (step(_time_step) != -1) {
        // Read the sensors
    ir0_val = _distance_sensor[5]->getValue();
    ir15_val = _distance_sensor[6]->getValue();
    ir1_val = _distance_sensor[0]->getValue();
    ir14_val = _distance_sensor[1]->getValue();
	ir12_val = _distance_sensor[4]->getValue();
	ir11_val = _distance_sensor[3]->getValue();	
	ir3_val = _distance_sensor[7]->getValue();
    ir4_val = _distance_sensor[2]->getValue();


        // Control logic of the robot
        if ((ir1_val > DISTANCE_LIMIT) || (ir4_val > DISTANCE_LIMIT)||(ir14_val > DISTANCE_LIMIT)) {
            _mode = OBSTACLE_AVOID;
            cout << "Going back and turning left." << endl;
            }
	else{
        
            _mode = FORWARD;
            cout << "Moving forward." << endl;
        }
       
	if ((ir12_val == 0.0)&&(ir11_val== 0.0)&&(ir14_val==0.0)&&(ir0_val== 0.0)&&(ir15_val==0.0))
              {
 		_mode = TURN_RIGHT;	
 		cout<<"Turning right"<<endl;
	      }
    
       
        if((ir11_val!= 0.0)&&(ir12_val==0.0)&&(ir14_val==0.0)&&(ir0_val== 0.0)&&(ir15_val==0.0))
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
            default:
                break;
        }

        // Set the motor speed
        setSpeed(_left_speed, _right_speed);
    }
}

//////////////////////////////////////////////
