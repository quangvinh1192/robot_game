
#include <string>
#ifndef POINT_H
#define POINT_H

/*
* File: point.h
* Define a point struct which uses in the main.
* Struct contains x,y, direction and path
* x, y, direction: is the location of the robot
* path: is the direction which the robot has moved from an initial point
* to the target
*/

struct Point{
    int x;
    int y;
    char direction;
    std::string path;
};
#endif
