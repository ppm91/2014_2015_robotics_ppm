/**
 * @file    MyRobot.cpp
 * @brief   Controller for detecting yellow lines with the spherical camera of the robot.
 *
 * @author  Pablo Pérez Martínez <100275550@uc3m.es>
 * @date    13/11/2014
 */

#include "MyRobot.h"

//////////////////////////////////////////////

MyRobot::MyRobot() : DifferentialWheels()
{
    // init default values
    _time_step = 64;

    _left_speed = 0;
    _right_speed = 0;


    // get distance sensor array and enable each one
    _spherical_camera = getCamera("camera_s");
    _spherical_camera->enable(_time_step);
}

//////////////////////////////////////////////

MyRobot::~MyRobot()
{
    // disable devices
    _spherical_camera->disable();
}

//////////////////////////////////////////////

void MyRobot::run()
{
    int sum = 0;
    unsigned char green = 0, red = 0, blue = 0;
    double percentage_yellow = 0.0;

    // get size of images for spherical camera
    int image_width_s = _spherical_camera->getWidth();
    int image_height_s = _spherical_camera->getHeight();
    cout << "Size of spherical camera image: " << image_width_s << ", " << image_height_s << endl;

    while (step(_time_step) != -1) {
        sum = 0;

        // get current image from spherical camera
        const unsigned char *image_s = _spherical_camera->getImage();

        // count number of pixels that are yellow
        for (int x = 0; x < image_width_s; x++) {
            for (int y = 0; y < image_height_s; y++) {
                green = _spherical_camera->imageGetGreen(image_s, image_width_s, x, y);
                red = _spherical_camera->imageGetRed(image_s, image_width_s, x, y);
                blue = _spherical_camera->imageGetBlue(image_s, image_width_s, x, y);

                if ((green > 230) && (red > 230) && (blue == 0)) {
                    sum = sum + 1;
                }
            }
        }


        percentage_yellow = (sum / (float) (image_width_s * image_height_s)) * 100;
        if (percentage_yellow > 0.30 & percentage_yellow < 0.6){
            cout << "Yellow line detected" << endl;
        }
        if (percentage_yellow > 0.60){
            cout <<"The yellow line is very close" << endl;
        }
       // cout << "Percentage of yellow in spherical camera image: " << percentage_yellow << endl;

        // turn around slowly
        _left_speed = 5;
        _right_speed = -5;

        // set the motor speeds
        setSpeed(_left_speed, _right_speed);
    }
}

//////////////////////////////////////////////
