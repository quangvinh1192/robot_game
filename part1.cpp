
struct Point;
void moveForward(Point& point){
    if (point.direction == 'N') {
        if(point.y != 8)
            point.y++;
    }
    else if (point.direction == 'S') {
        if (point.y !=1)
            point.y--;
    }
    else if(point.direction == 'E'){
        if (point.x !=8)
            point.x ++;
    }
    else if(point.direction == 'W'){
        if (point.x !=1)
            point.x --;
    }
}

void turnLeft(Point &point){
    if (point.direction == 'N') {
        point.direction = 'W';
    }
    else if (point.direction == 'S') {
        point.direction = 'E';
    }
    else if(point.direction == 'E'){
        point.direction = 'N';
    }
    else if(point.direction == 'W'){
        point.direction = 'S';
    }
}

void turnRight(Point &point){
    if (point.direction == 'N') {
        point.direction = 'E';
    }
    else if (point.direction == 'S') {
        point.direction = 'W';
    }
    else if(point.direction == 'E'){
        point.direction = 'S';
    }
    else if(point.direction == 'W'){
        point.direction = 'N';
    }
}
