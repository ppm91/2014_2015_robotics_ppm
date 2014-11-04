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

    // Get and enable the compass device
    _my_compass = getCompass("compass");
    _my_compass->enable(_time_step);
    _distance_sensor[0] = getDistanceSensor("ds0");
    _distance_sensor[0]->enable(_time_step);
    _distance_sensor[1] = getDistanceSensor("ds1");
    _distance_sensor[1]->enable(_time_step);
    _distance_sensor[2] = getDistanceSensor("ds2");
    _distance_sensor[2]->enable(_time_step);
    _distance_sensor[3] = getDistanceSensor("ds3");
    _distance_sensor[3]->enable(_time_step);
    _distance_sensor[4] = getDistanceSensor("ds4");
    _distance_sensor[4]->enable(_time_step);
    _distance_sensor[5] = getDistanceSensor("ds5");
    _distance_sensor[5]->enable(_time_step);
    _distance_sensor[6] = getDistanceSensor("ds6");
    _distance_sensor[6]->enable(_time_step);
    _distance_sensor[7] = getDistanceSensor("ds7");
    _distance_sensor[7]->enable(_time_step);
    _distance_sensor[8] = getDistanceSensor("ds8");
    _distance_sensor[8]->enable(_time_step);
    _distance_sensor[9] = getDistanceSensor("ds9");
    _distance_sensor[9]->enable(_time_step);
    _distance_sensor[10] = getDistanceSensor("ds10");
    _distance_sensor[10]->enable(_time_step);
    _distance_sensor[11] = getDistanceSensor("ds11");
    _distance_sensor[11]->enable(_time_step);
    _distance_sensor[12] = getDistanceSensor("ds12");
    _distance_sensor[12]->enable(_time_step);
    _distance_sensor[13] = getDistanceSensor("ds13");
    _distance_sensor[13]->enable(_time_step);
    _distance_sensor[14] = getDistanceSensor("ds14");
    _distance_sensor[14]->enable(_time_step);
    _distance_sensor[15] = getDistanceSensor("ds15");
    _distance_sensor[15]->enable(_time_step);
    
}


//////////////////////////////////////////////

MyRobot::~MyRobot()
{
    _my_compass->disable();
    for (int i=0; i<NUM_DISTANCE_SENSOR; i++) {
        _distance_sensor[i]->disable();
    }

}

//////////////////////////////////////////////

void MyRobot::run()
{
  double counter=0.0;
  double compass_angle;
  double ir0_val = 0.0, ir1_val = 0.0,ir2_val = 0.0, ir3_val = 0.0,ir4_val = 0.0, ir5_val = 0.0, ir6_val = 0.0,ir7_val = 0.0, ir8_val = 0.0;
  double ir9_val = 0.0, ir10_val = 0.0,ir11_val = 0.0, ir12_val = 0.0,ir13_val = 0.0, ir14_val = 0.0, ir15_val = 0.0;

    while (step(_time_step) != -1) {
        // Read the sensors
        ir0_val = _distance_sensor[0]->getValue();
        ir1_val = _distance_sensor[1]->getValue();
        ir2_val = _distance_sensor[2]->getValue();
        ir3_val = _distance_sensor[3]->getValue();
        ir4_val = _distance_sensor[4]->getValue();
        ir5_val = _distance_sensor[5]->getValue();
        ir6_val = _distance_sensor[6]->getValue();
        ir7_val = _distance_sensor[7]->getValue();
        ir8_val = _distance_sensor[8]->getValue();
        ir9_val = _distance_sensor[9]->getValue();
        ir10_val = _distance_sensor[10]->getValue();
        ir11_val = _distance_sensor[11]->getValue();
        ir12_val = _distance_sensor[12]->getValue();
        ir13_val = _distance_sensor[13]->getValue();
        ir14_val = _distance_sensor[14]->getValue();
        ir15_val = _distance_sensor[15]->getValue();
        const double *compass_val = _my_compass->getValues();

        // Convert compass bearing vector to angle, in degrees
        compass_angle = convert_bearing_to_degrees(compass_val);

        // Print sensor values to console
        cout << "Compass angle (degrees): " << compass_angle << endl;
        cout << "Distance:"<< "ds0: " << ir0_val << " ds1:" << ir1_val <<"ds2: " << ir2_val << " ds3:" << ir3_val <<endl;
        cout <<"ds4: "<< ir4_val << " ds5:" << ir5_val<< " ds6:"<< ir6_val << " ds7:" << ir7_val << endl;
        cout <<"ds8: "<< ir8_val << " ds9:" << ir9_val<< " ds10:"<< ir10_val << " ds11:" << ir11_val << endl;
        cout <<"ds12: "<< ir12_val << " ds13:" << ir13_val<< " ds14:"<< ir14_val << " ds15:" << ir15_val << endl;
        // Simple bang-bang control
        if(counter<355)
        {
          if (compass_angle < (DESIRED_ANGLE - 2)) {
              // Turn right
              _left_speed = MAX_SPEED;
              _right_speed = MAX_SPEED - 15;
          }
          else {
              if (compass_angle > (DESIRED_ANGLE + 2)) {
                  // Turn left
                  _left_speed = MAX_SPEED - 15;
                  _right_speed = MAX_SPEED;
              }
              else {
                  // Move straight forward
                  _left_speed = MAX_SPEED;
                  _right_speed = MAX_SPEED;
              }
          }
  
          // Set the motor speeds
          setSpeed(_left_speed, _right_speed);
          counter++;
         
        }
        else{
         setSpeed(0,0);
        }
    }
}

//////////////////////////////////////////////

double MyRobot::convert_bearing_to_degrees(const double* in_vector)
{
    double rad = atan2(in_vector[0], in_vector[2]);
    double deg = rad * (180.0 / M_PI);

    return deg;
}

//////////////////////////////////////////////
