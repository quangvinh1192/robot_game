#include <iostream>
#include <string>
#include <list> //used for list
#include <queue> //used for queue
#include <stdlib.h> //used for abs
using namespace std;
#define MAX_INDEX 8
#define MIN_INDEX 1
struct Point{
    int x;
    int y;
    char direction;
    string path;
};

void get_input(Point& original, Point& target, bool isPart1, int& maximum_distance,
    string& actions);
void add_new_point(Point original, Point target,queue<Point>& list_point, list<string>& action_path,
                    int maximum_distance);
bool check_destination(Point target, Point point);
void check_destination_and_update_list(queue<Point>& list_point, list<string>& action_path,
        Point forward, Point left, Point right, Point target, int maximum_distance);
void version2(Point original, Point target,int numStep, list<string>& action_path);
void optimal_add_element(queue<Point>& list_point, Point point,Point target, int maximum_distance);
void version1(Point original, Point target, string actions);
void moveForward(const Point current_point, Point& updated_point);
void turnLeft(const Point current_point, Point& updated_point);
void turnRight(const Point current_point, Point& updated_point);


int main(int argc, char const *argv[]) {
    Point original, target;
    int numStep ;
    list<string> action_path;
    string actions, user_decision;
    do {
        cout<<"\n\nPlease enter 1 to run version 1, enter 2 to run version 2 or enter e to exit: ";
        cin>>user_decision;
        if (user_decision == "1") {
            get_input(original, target, true, numStep,actions);
            version1(original, target, actions);
        }
        else if(user_decision == "2"){
            get_input(original, target, false, numStep,actions);
            version2(original, target,numStep, action_path);
        }
    } while(user_decision != "e");

    return 0;
}

/*---------------------------------------------------------------------
 * Method: get_input(void)
 * Scope:  Global
 * This function will get the input from users. If part 1 call this, it
 * will require users to enter Location, Direction faced, Actions
 *
 *---------------------------------------------------------------------*/
void get_input(Point& original, Point& target, bool isPart1, int& maximum_distance,
    string& actions){
    int x_original, y_original, x_target, y_target;
    string direction;
    //Users enter the location and Direction faced
    do {
        string original_string;
        cout <<"Please enter original position (e.g [2,3]): ";
        cin >>original_string;
        x_original = original_string.at(1)-'0';
        y_original = original_string.at(3)-'0';
        if (x_original >MAX_INDEX || x_original<=MIN_INDEX || y_original <=MIN_INDEX || y_original>MAX_INDEX) {
            cout<<"Please enter again. e.g [3,4]\n";
        }
    } while(x_original>MAX_INDEX || x_original<=MIN_INDEX || y_original <=MIN_INDEX || y_original>MAX_INDEX);

    do {
        cout << "Original Direction faced (e.g N): ";
        cin >> direction;
        if (direction !="N" && direction !="S" &&direction !="W" &&direction !="E") {
            cout<<"Please enter again. Only enter N,S,W or E\n";
        }
    } while(direction !="N" && direction !="S" &&direction !="W" &&direction !="E");

    original.x = x_original;
    original.y = y_original;
    original.direction = direction.at(0);
    //this is for part 1
    if (isPart1) {
        do {
            cout <<"Enter Actions:";
            cin >> actions;
            actions.append(",");
            if (actions.length()%2 !=0) {
                cout<<"Please enter again. e.g M,M,M,L,M,R,R,\n";
            }
        } while(actions.length()%2 !=0);

    }
    else{
        //this is for the second part
        do {
            string original_string;
            cout <<"Please enter Target position (e.g [3,4]): ";
            cin >>original_string;
            x_target = original_string.at(1)-'0';
            y_target = original_string.at(3)-'0';
            if (x_target>MAX_INDEX || x_target<=0 || y_target <=0 || y_target>MAX_INDEX) {
                cout<<"Please enter again. e.g [3,4]\n";
            }
        } while(x_target>MAX_INDEX || x_target<=0 || y_target <=0 || y_target>MAX_INDEX);
        do {
            cout << "Target position faced (e.g S): ";
            cin >> direction;
            if (direction !="N" && direction !="S" &&direction !="W" &&direction !="E") {
                cout<<"Please enter again. Only enter N,S,W or E\n";
            }
        } while(direction !="N" && direction !="S" &&direction !="W" &&direction !="E");
        do {
            cout<<"Maximum actions allowed: ";
            cin>> maximum_distance;
        } while(maximum_distance <=0);

        target.x = x_target;
        target.y = y_target;
        target.direction = direction.at(0);
    }
}
/////////////////////////----> version 2 <-----///////////////////////////
/*---------------------------------------------------------------------
 * Method: check_destination(bool)
 * Scope:  Global
 * This function will check the target point with the current point. If they
 * are the same then returns true. Otherwise, return false
 *---------------------------------------------------------------------*/
bool check_destination(Point target, Point point){
    if (target.x == point.x && target.y == point.y && target.direction == point.direction) {
        return true;
    }
    return false;
}
/*---------------------------------------------------------------------
 * Method: version2(void)
 * Scope:  Global
 * This function will use the concept of DFS to find the part between
 * 2 locations in the map
 *---------------------------------------------------------------------*/
void version2(Point original, Point target,int numStep, list<string>& action_path){
    int count =0;
    queue<Point> list_point;
    list_point.push(original);

    while (count++ < numStep) {
        add_new_point(original, target, list_point, action_path, numStep- count);
        // std::cout << "/* message */" << '\n';
        // for (size_t i = 0; i < list_point.size(); i++) {
        //     std::cout << "x: " << list_point.front().x <<"  y: "<<list_point.front().y
        //         <<"  direction: "<<list_point.front().direction<<
        //         "  path: "<<list_point.front(). path<<endl;;
        //     list_point.push(list_point.front());
        //     list_point.pop();
        // }
    }
    if (action_path.empty()) {
        std::cout << "No possible actions!" << '\n';
    }
    else{
        int numAction =1;
        while (!action_path.empty()) {
            std::cout << "Actions - " << numAction ++ <<" :";
            std::cout << action_path.front().erase(0, 1)<< '\n';
            action_path.pop_front();
        }
        std::cout << "No more possible actions!" << '\n';
    }
}
/*---------------------------------------------------------------------
 * Method: add_new_point(void)
 * Scope:  Global
 * This function will try all step from the current point which are moving forward,
 * turning left and turning right
 *---------------------------------------------------------------------*/
void add_new_point(Point original, Point target,queue<Point>& list_point, list<string>& action_path,
                    int maximum_distance){
    //get the size of the input list
    int size = list_point.size();
    for (int i = 0; i < size; i++) {
        Point working= list_point.front();
        string original_path(working.path);
        Point point_move_forward, point_turn_left, point_turn_right;
        point_move_forward.direction='o';//create dummy value
        switch (working.direction) {
            case 'S':
            case 'N':
            case 'W':
            case 'E':
                moveForward(working, point_move_forward);
                turnLeft(working, point_turn_left);
                turnRight(working, point_turn_right);
                break;
            default:
                std::cerr << "something's wrong" << '\n';
                return;
                break;
        }
        // update the list and check the destination
        check_destination_and_update_list(list_point, action_path, point_move_forward,
            point_turn_left, point_turn_right, target, maximum_distance);
        //pop that location because we didn't need it anymore
        list_point.pop();
    }
}
/*---------------------------------------------------------------------
 * Method: check_destination_and_update_list(void)
 * Scope:  Global
 * This function will try all step from the current point which are moving forward,
 * turning left and turning right
 *---------------------------------------------------------------------*/
void check_destination_and_update_list(queue<Point>& list_point, list<string>& action_path,
        Point forward, Point left, Point right, Point target, int maximum_distance){
    // if this is summy location, then we didn't check
    if (forward.direction != 'o') {
        if (check_destination(target, forward))
            action_path.push_back(forward.path);
        optimal_add_element(list_point, forward, target, maximum_distance);
    }
    //checl left and right location
    if (check_destination(target, left))
        action_path.push_back(left.path);
    if (check_destination(target, right))
        action_path.push_back(right.path);
    //call this functions to add the only needed location to the list
    optimal_add_element(list_point, left, target, maximum_distance);
    optimal_add_element(list_point, right, target, maximum_distance);
}
/*---------------------------------------------------------------------
 * Method: optimal_add_element(void)
 * Scope:  Global
 * This function will check the current location with the target location.
 * For example, when robot is at [2,3] and the destination is at [4,5]
 * then it needs at least 4 steps to get there. We can remove unnecessary location
 * to the list
 *---------------------------------------------------------------------*/
void optimal_add_element(queue<Point>& list_point, Point point,Point target, int maximum_distance){
    if (abs(point.x - target.x)+ abs(point.y - target.y) <= maximum_distance) {
        list_point.push(point);
    }
}

/////////////////////////----> PART1 <-----///////////////////////////
/*---------------------------------------------------------------------
 * Method: version1(void)
 * Scope:  Global
 * This function will print the outcome; direction faced and position on the board
 * when users enter a starting position [x,y] (0<x,y<9), initial direction faced
 * (W, S, N, E) on 8 x 8 square board and sequence of actions for a robot
 *---------------------------------------------------------------------*/
void version1(Point original, Point target, string actions){
    actions.erase(std::remove(actions.begin(), actions.end(), ','), actions.end());
    for (size_t i = 0; i < actions.length(); i++) {
        if(actions.at(i) == 'M')
            moveForward(original, original);
        else if (actions.at(i) == 'L')
            turnLeft(original, original);
        else if(actions.at(i) == 'R')
            turnRight(original, original);
        else //if it contains anymore character than that, then returns
            return;
    }
    cout <<"Location: ["<<original.x<<","<<original.y<<"]\n";
    cout<<"Direction faced: "<<original.direction<<endl;
}
/*---------------------------------------------------------------------
 * Method: moveForward(void)
 * Scope:  Global
 * This function will check the direction and location in order to move Forward
 * the robot
 *---------------------------------------------------------------------*/
void moveForward(const Point current_point, Point& updated_point){
    updated_point.x = current_point.x;
    updated_point.y = current_point.y;
    updated_point.path = current_point.path;
    updated_point.direction = current_point.direction;
    updated_point.path.append(",M");

    if (current_point.direction == 'N' && current_point.y != MAX_INDEX) {
        updated_point.y++;
    }
    else if (current_point.direction == 'S' && current_point.y !=MIN_INDEX) {
        updated_point.y--;
    }
    else if(current_point.direction == 'E' && current_point.x !=MAX_INDEX){
        updated_point.x ++;
    }
    else if(current_point.direction == 'W' && current_point.x !=MIN_INDEX){
        updated_point.x --;
    }
    else{
        updated_point.direction= 'o'; //dummy direction
    }
}
/*---------------------------------------------------------------------
 * Method: turnLeft(void)
 * Scope:  Global
 * This function will turn left
 *---------------------------------------------------------------------*/
void turnLeft(const Point current_point, Point& updated_point){
    updated_point.x = current_point.x;
    updated_point.y = current_point.y;
    updated_point.path = current_point.path;
    updated_point.path.append(",L");
    if (current_point.direction == 'N') {
        updated_point.direction = 'W';
    }
    else if (current_point.direction == 'S') {
        updated_point.direction = 'E';
    }
    else if(current_point.direction == 'E'){
        updated_point.direction = 'N';
    }
    else if(current_point.direction == 'W'){
        updated_point.direction = 'S';
    }
}
/*---------------------------------------------------------------------
 * Method: moveForward(void)
 * Scope:  Global
 * This function will turn right
 *---------------------------------------------------------------------*/
void turnRight(const Point current_point, Point& updated_point){
    updated_point.x = current_point.x;
    updated_point.y = current_point.y;
    updated_point.path = current_point.path;
    updated_point.path.append(",R");
    if (current_point.direction == 'N') {
        updated_point.direction = 'E';
    }
    else if (current_point.direction == 'S') {
        updated_point.direction = 'W';
    }
    else if(current_point.direction == 'E'){
        updated_point.direction = 'S';
    }
    else if(current_point.direction == 'W'){
        updated_point.direction = 'N';
    }
}
