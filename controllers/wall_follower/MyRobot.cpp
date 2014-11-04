/**
 * @file    MyRobot.cpp
 * @brief   A simple example for maintaining a straight line with the compass.
 *
 * @author  Raul Perula-Martinez <raul.perula@uc3m.es>
 * @date    2014-07
 */

#include "MyRobot.h"

//////////////////////////////////////////////

MyRobot::MyRobot() : DifferentialWheels()
{
    _time_step = 64;

    _left_speed = 0;
    _right_speed = 0;
    
    _mode = FORWARD;

    // Get and enable the distance sensors

    _distance_sensor[0] = getDistanceSensor("ds0");
    _distance_sensor[0]->enable(_time_step);
//    _distance_sensor[1] = getDistanceSensor("ds1");
//    _distance_sensor[1]->enable(_time_step);
//    _distance_sensor[2] = getDistanceSensor("ds2");
//    _distance_sensor[2]->enable(_time_step);
    _distance_sensor[1] = getDistanceSensor("ds3");
    _distance_sensor[1]->enable(_time_step);
    _distance_sensor[2] = getDistanceSensor("ds4");
    _distance_sensor[2]->enable(_time_step);
//    _distance_sensor[5] = getDistanceSensor("ds5");
//    _distance_sensor[5]->enable(_time_step);
//    _distance_sensor[6] = getDistanceSensor("ds6");
//    _distance_sensor[6]->enable(_time_step);
//    _distance_sensor[7] = getDistanceSensor("ds7");
//    _distance_sensor[7]->enable(_time_step);
//    _distance_sensor[8] = getDistanceSensor("ds8");
//    _distance_sensor[8]->enable(_time_step);
//    _distance_sensor[9] = getDistanceSensor("ds9");
//    _distance_sensor[9]->enable(_time_step);
//    _distance_sensor[10] = getDistanceSensor("ds10");
//    _distance_sensor[10]->enable(_time_step);
    _distance_sensor[3] = getDistanceSensor("ds11");
    _distance_sensor[3]->enable(_time_step);
    _distance_sensor[4] = getDistanceSensor("ds12");
    _distance_sensor[4]->enable(_time_step);
//    _distance_sensor[13] = getDistanceSensor("ds13");
//    _distance_sensor[13]->enable(_time_step);
//    _distance_sensor[14] = getDistanceSensor("ds14");
//    _distance_sensor[14]->enable(_time_step);
    _distance_sensor[5] = getDistanceSensor("ds15");
    _distance_sensor[5]->enable(_time_step);
    
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
  double ir0_val = 0.0, /*ir1_val = 0.0,*/ ir3_val = 0.0,ir4_val = 0.0/*, ir6_val = 0.0,ir7_val = 0.0*/;
  double /*ir8_val = 0.0,ir9_val = 0.0 ,*/ir11_val = 0.0, ir12_val = 0.0/*, ir14_val = 0.0*/, ir15_val = 0.0;
//  double ir2_val = 0.0, ir5_val = 0.0, ir10_val = 0.0,ir13_val = 0.0;
  double radd=0.0,ladd=0.0,fadd=0.0;


    while (step(_time_step) != -1) {
        // Read the sensors
        ir0_val = _distance_sensor[0]->getValue();
      //ir1_val = _distance_sensor[1]->getValue();
   //   ir2_val = _distance_sensor[2]->getValue();
        ir3_val = _distance_sensor[1]->getValue();
        ir4_val = _distance_sensor[2]->getValue();
     // ir5_val = _distance_sensor[5]->getValue();
     // ir6_val = _distance_sensor[6]->getValue();
     // ir7_val = _distance_sensor[7]->getValue();
      //ir8_val = _distance_sensor[8]->getValue();
     // ir9_val = _distance_sensor[9]->getValue();
     // ir10_val = _distance_sensor[10]->getValue();
        ir11_val = _distance_sensor[3]->getValue();
        ir12_val = _distance_sensor[4]->getValue();
     // ir13_val = _distance_sensor[13]->getValue();
     // ir14_val = _distance_sensor[14]->getValue();
        ir15_val = _distance_sensor[5]->getValue();

        radd=ir12_val-ir11_val;
        ladd=ir3_val-ir4_val;
        fadd=ir0_val-ir15_val;


        // Print sensor values to console


        cout << "Distance:"<<endl;
        cout << "FL: " << ir0_val << " FR:" << ir15_val << endl;
        cout <<" LF:" << ir3_val <<"LB: "<< ir4_val <<endl;
        cout <<"RF: "<< ir12_val <<" RB:" << ir11_val << endl;
        cout <<" fadd:"<<fadd<<" radd:"<<radd<<" ladd:"<<ladd<<endl;
        //Wall follower


        if (ir0_val<DISTANCE_LIMIT && ir15_val<DISTANCE_LIMIT && radd!=0 && ladd!=0){//if any sensor detects nothing

            _mode=FORWARD;
        }
        else{
            if (fadd>10){// if sensor FI detects wall
                _mode=TURN_RIGHT;
            }
            else{
                if(fadd<-10){//if sensor FD detects wall
                    _mode=TURN_LEFT;
                }
                else{
                    if(radd>10 && ir12_val<NEAR_DISTANCE){//if it's looking to the wall
                        _mode=TURN_LEFT;
                    }
                    else{
                        if(ir12_val>NEAR_DISTANCE){
                            _mode=TURN_LEFT;
                        }
                        else{
                          if(radd<-15){//if the back is facing to tha wall
                              _mode=TURN_RIGHT;
                          }
                          else{//its more or less parallel to tha wall
                              _mode=FOLLOWER;




                            if(ladd>10 && ir3_val<NEAR_DISTANCE){//if it's looking to the wall
                                 _mode=TURN_RIGHT;
                             }
                              else{
                                  if(ir3_val>NEAR_DISTANCE){
                                      _mode=TURN_RIGHT;
                                 }
                                 if(ladd<-15){//if the back is facing to tha wall
                                     _mode=TURN_LEFT;
                                 }
                                  else{//its more or less parallel to tha wall
                                      _mode=FOLLOWER;
                                      }

                                  }
                              }

                          }

                     }


                  }



             }



            }

        
        switch (_mode){
            case STOP:
                _left_speed = 0;
                _right_speed = 0;
                cout<<"Stop"<<endl;
                break;
            case FORWARD:
                _left_speed = MAX_SPEED/1.5;
                _right_speed = MAX_SPEED/1.5;
                cout<<"Forward"<<endl;
                break;
            case TURN_LEFT:
                _left_speed = -MAX_SPEED;
                _right_speed = MAX_SPEED;
                cout<<"Left"<<endl;
                break;
            case TURN_RIGHT:
                _left_speed = MAX_SPEED;
                _right_speed = -MAX_SPEED;
                cout<<"Right"<<endl;
                break;
            case FOLLOWER:
                _left_speed = MAX_SPEED/3;
                _right_speed = MAX_SPEED/3;
                cout<<"Follower"<<endl;
                break;
            case BACK:
                _left_speed = -MAX_SPEED;
                _right_speed = -MAX_SPEED;
                cout<<"Back"<<endl;
                break;
            default:
                break;
        }
   setSpeed(_left_speed, _right_speed);
        

        
    }//Llave del while
}

