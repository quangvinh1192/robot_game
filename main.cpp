#include <iostream>
#include <string>
#include <list> //used for list
#include <queue> //used for queue
#include <stdlib.h> //used for abs
#include <locale>    //std::toupper
#include <assert.h>
#include "point.h"

using namespace std;
#define MAX_INDEX 8
#define MIN_INDEX 1


void get_input(Point& original, Point& target, bool isPart1, int& maximum_distance,
    string& actions);
void add_Possible_Moving(Point target,queue<Point>& list_point, list<string>& action_path,
                    int maximum_distance);
bool check_destination(Point target, Point point);
void check_destination_and_update_list(queue<Point>& list_point, list<string>& action_path,
        Point forward, Point left, Point right, Point target, int maximum_distance);
void version2(Point original, Point target,int numStep);
void optimal_add_element(queue<Point>& list_point, Point point,Point target, int maximum_distance);
void version1(Point original, Point target, string actions);
bool moving_Forward(const Point current_point, Point& updated_point);
void turning_Left(const Point current_point, Point& updated_point);
void turning_Right(const Point current_point, Point& updated_point);
void testAll();

int main(int argc, char const *argv[]) {
    //original,target, numStep, actions are the input from users
    Point original, target;
    int numStep ;
    string actions, user_decision;

    // testAll(); //Calling testing function
    do {
        cout<<"\n\nPlease enter 1 to run version 1, enter 2 to run version 2 or enter e to exit: ";
        getline(cin, user_decision);
        if (user_decision == "1") {
            get_input(original, target, true, numStep,actions);
            version1(original, target, actions);
        }
        else if(user_decision == "2"){
            get_input(original, target, false, numStep,actions);
            version2(original, target,numStep);
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
    //these variable to hold the input from users
    int x_original, y_original, x_target, y_target;
    string direction, original_string;;

    cout<<"Please enter the information below: \n";
    //Users enter the location and Direction faced
    do {
        cout <<"Original position (e.g [2,3]): ";
        getline(cin, original_string);
        x_original = original_string.at(1)-'0';
        y_original = original_string.at(3)-'0';
        if (original_string.length()==4 && (x_original >MAX_INDEX || x_original< MIN_INDEX ||
                                        y_original <MIN_INDEX || y_original>MAX_INDEX)) {
            cout<<"Please enter again.[x,y](0<x,y<9)\n";
        }

    } while(original_string.length()==4 && (x_original >MAX_INDEX || x_original< MIN_INDEX ||
                                    y_original <MIN_INDEX || y_original>MAX_INDEX));
    //get original direction
    do {
        cout << "Original Direction faced (e.g N): ";
        getline(cin, direction);
        direction[0] = toupper(direction[0]);
        if (direction !="N" && direction !="S" &&direction !="W" &&direction !="E"
                            && direction.length()==1) {
            cout<<"Please enter again. Only using N,S,W or E\n";
        }
    } while(direction !="N" && direction !="S" &&direction !="W" &&direction !="E"
                            && direction.length()==1);
    //initial the original
    original.x = x_original;
    original.y = y_original;
    original.direction = direction.at(0);
    //this is for part 1, get the actions and print out the result
    if (isPart1) {
        bool valid_actions = true;
        do {
            //get actions and remove any empty space between any character
            cout <<"Actions: ";
            getline(cin, actions);
            actions.erase(std::remove(actions.begin(), actions.end(), ' '), actions.end());
            //validation the input
            for (int i = 0; i < actions.length(); i++) {
                if (toupper(actions[i])!='M' && toupper(actions[i])!='L' &&
                        toupper(actions[i])!='R' && toupper(actions[i])!=',') {
                    valid_actions = false;
                }
            }
            if (!valid_actions) {
                cout << "Actions only contains: 'M', 'L', 'R' or ','" << '\n';
            }
        } while(!valid_actions);
    }
    else{
        //this is for the second part
        //get the targer position and maximum actions allowed
        do {
            cout <<"Target position (e.g [3,4]): ";
            getline(cin, original_string);
            x_target = original_string.at(1)-'0';
            y_target = original_string.at(3)-'0';
            if (original_string.length()==4 && (x_target >MAX_INDEX || x_target< MIN_INDEX ||
                                            y_target <MIN_INDEX || y_target>MAX_INDEX)) {
                cout<<"Please enter again. [x,y](0<x,y<9)\n";
            }
        } while(original_string.length()==4 && (x_target >MAX_INDEX || x_target< MIN_INDEX ||
                                        y_target <MIN_INDEX || y_target>MAX_INDEX));
        //get position faced
        do {
            cout << "Target position faced (e.g S): ";
            getline(cin, direction);
            direction[0] = toupper(direction[0]);
            if (direction !="N" && direction !="S" &&direction !="W" &&direction !="E"
                        && direction.length()== 1) {
                cout<<"Please enter again. Only using 'N','S','W' or 'E'\n";
            }
        } while(direction !="N" && direction !="S" &&direction !="W" &&direction !="E"
                            && direction.length()== 1);
        //get actions allowed
        do {
            cout<<"Maximum actions allowed: ";
            cin>> maximum_distance;
            cin.ignore();
        } while(maximum_distance <=0);
        //initial target object
        target.x = x_target;
        target.y = y_target;
        target.direction = direction.at(0);
    }
}
/////////////////////////----> version 2 <-----///////////////////////////

/*---------------------------------------------------------------------
 * Method: version2(void)
 * Scope:  Global
 * This function will use the concept of DFS to find the part between
 * 2 locations in the map
 *---------------------------------------------------------------------*/
void version2(Point original, Point target,int numStep){
    int count =0; //count to count number of steps that robot has moved.
    //action_path: keep track the posible path which robot can move to get to the target
    list<string> action_path;
    //list_point: contains the locations which robot can get there from original location
    queue<Point> list_point;
    list_point.push(original);
    //for every steps, calling add_Possible_Moving to get all possible movements
    while (count++ < numStep) {
        add_Possible_Moving(target, list_point, action_path, numStep- count);
    }
    //print out the result
    if (action_path.empty()) {
        cout << "No possible actions!" << '\n';
    }
    else{
        cout << '\n';
        int numAction =1;
        while (!action_path.empty()) {
            cout << "Actions - " << numAction ++ <<" :";
            cout << action_path.front().erase(0, 1)<< '\n';
            action_path.pop_front();
        }
        cout << "No more possible actions!" << '\n';
    }
}

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
 * Method: add_Possible_Moving(void)
 * Scope:  Global
 * This function will try all step from the current point which are moving forward,
 * turning left and turning right
 *---------------------------------------------------------------------*/
void add_Possible_Moving(Point target,queue<Point>& list_point, list<string>& action_path,
                    int maximum_distance){
    //get the size of the input list
    int size = list_point.size();
    for (int i = 0; i < size; i++) {
        Point working= list_point.front();
        string original_path(working.path);
        Point point_move_forward, point_turn_left, point_turn_right;

        switch (working.direction) {
            case 'S':
            case 'N':
            case 'W':
            case 'E':
                //set direction to dummy node if it's not a valid move
                if (!moving_Forward(working, point_move_forward)) {
                    point_move_forward.direction= 'o';
                }
                turning_Left(working, point_turn_left);
                turning_Right(working, point_turn_right);
                break;
            default:
                std::cerr << "invalid direction" << '\n';
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
 * to the list. For example, [1,1] cannot made it into [4,5] in 2 steps
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
    int actions_length ;
    //remove all the comma from input string, or space and convert in into uppercase
    actions.erase(std::remove(actions.begin(), actions.end(), ','), actions.end());
    actions_length = actions.length();
    transform(actions.begin(), actions.end(), actions.begin(), ::toupper);
    //everytime, robot can try 1 of 3 posible actions per step
    for (size_t i = 0; i < actions_length; i++) {
        if(actions.at(i) == 'M'){
            if(!moving_Forward(original, original)){
                cerr << "Error: Robot cannot move 1 square forward at step: " << i+1
                <<" because it's at [" <<original.x <<","<<original.y<<"]"
                <<" direction faced: "<< original.direction <<endl;
            }
        }
        else if (actions.at(i) == 'L')
            turning_Left(original, original);
        else if(actions.at(i) == 'R')
            turning_Right(original, original);
        else //if it contains anymore character than that
        {
            std::cerr << "Error: Robot doesn't know the action "<< actions.at(i)<<
            ". It will ignore this action and continue to do the next step"<< '\n';
        }
    }
    //print out the result
    cout <<"\nRobot is at: \n";
    cout <<"Location: ["<<original.x<<","<<original.y<<"]\n";
    cout<<"Direction faced: "<<original.direction<<endl;
}
/*---------------------------------------------------------------------
 * Method: moving_Forward(void)
 * Scope:  Global
 * This function will check the direction and location in order to move the robot
 * fowarding. Return true if robot can do this action. Otherwise, returns false
 *---------------------------------------------------------------------*/
bool moving_Forward(const Point current_point, Point& updated_point){
    //set initial values
    updated_point.x = current_point.x;
    updated_point.y = current_point.y;
    updated_point.path = current_point.path;
    updated_point.direction = current_point.direction;
    updated_point.path.append(",M");
    // robot can have 4 posible direction with 4 posible movements
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
        //this is an invalid actions, return false
        return false;
    }
    return true;
}
/*---------------------------------------------------------------------
 * Method: turning_Left(void)
 * Scope:  Global
 * This function will update the current location of the robot after turning
 * left. This function only updates the direction and path
 *---------------------------------------------------------------------*/
void turning_Left(const Point current_point, Point& updated_point){
    //initial values and updated robot's information
    updated_point.x = current_point.x;
    updated_point.y = current_point.y;
    updated_point.path = current_point.path;
    updated_point.path.append(",L");
    //there is 4 posible directions with 4 posible movements
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
 * Method: moving_Forward(void)
 * Scope:  Global
 * This function will update the current location of the robot after turning
 * right. This function only updates the direction and path
 *---------------------------------------------------------------------*/
void turning_Right(const Point current_point, Point& updated_point){
    //update initial values and path
    updated_point.x = current_point.x;
    updated_point.y = current_point.y;
    updated_point.path = current_point.path;
    updated_point.path.append(",R");
    //there is 4 posible directions with 4 posible movements
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

/*---------------------------------------------------------------------
 * Method: testAll(void)
 * Scope:  Global
 * This function will try to test all the function in this program. It's more
 * easy to test when break program into smaller parts which can be tested.
 *---------------------------------------------------------------------*/
void testAll(){
    Point special_0,special_1,special_2,special_3;
    Point normal_1, normal_2, target, test_point;
    //initial some test points
    special_0.x = 1;
    special_0.y = 1;
    special_0.direction = 'S';
    special_1.x = 1;
    special_1.y = 8;
    special_1.direction = 'E';
    special_2.x = 8;
    special_2.y = 1;
    special_2.direction = 'N';
    special_3.x = 8;
    special_3.y = 8;
    special_3.direction = 'W';
    normal_1.x = 2;
    normal_1.y = 3;
    normal_1.direction = 'N';
    target.x = 3;
    target.y = 4;
    target.direction = 'S';
    //Test turning_Right function.
    turning_Right(special_0, test_point);
    assert(test_point.x == 1);
    assert(test_point.y == 1);
    assert(test_point.direction == 'W');
    turning_Right(normal_1, test_point);
    assert(test_point.x == 2);
    assert(test_point.y == 3);
    assert(test_point.direction == 'E');
    turning_Right(special_1, test_point);
    assert(test_point.direction == 'S');
    turning_Right(special_3, test_point);
    assert(test_point.direction == 'N');

    //test turn left function
    turning_Left(special_1, test_point);
    assert(test_point.x == 1);
    assert(test_point.y == 8);
    assert(test_point.direction == 'N');
    turning_Left(normal_1, test_point);
    assert(test_point.x == 2);
    assert(test_point.y == 3);
    assert(test_point.direction == 'W');
    turning_Left(special_0, test_point);
    assert(test_point.direction == 'E');
    turning_Left(special_3, test_point);
    assert(test_point.direction == 'S');

    //test moving_Forward for special point [1,1],[1,8],[8,1],[8,8],
    assert(moving_Forward(special_0, test_point) == false);
    assert(test_point.x == 1); assert(test_point.y == 1);
    assert(test_point.direction == 'S');
    assert(moving_Forward(special_1, test_point) == true);
    assert(test_point.x == 2); assert(test_point.y == 8);
    assert(test_point.direction == 'E');
    assert(moving_Forward(special_2, test_point) == true);
    assert(test_point.x == 8); assert(test_point.y == 2);
    assert(test_point.direction == 'N');
    assert(moving_Forward(special_3, test_point) == true);
    assert(test_point.x == 7); assert(test_point.y == 8);
    assert(test_point.direction == 'W');

    //test for updating the path
    normal_1.path="";
    turning_Left(normal_1, test_point);
    assert(test_point.path == ",L");
    turning_Right(normal_1, test_point);
    assert(test_point.path == ",R");
    assert(moving_Forward(normal_1, test_point) == true);
    assert(test_point.path == ",M");

    // Test optimal_add_element
    queue<Point> list_point;
    //from [1,1], it's cannot get to [3,4] by using 1 step
    optimal_add_element(list_point, special_0, target, 1);
    assert(list_point.size() == 0);
    while(!list_point.empty()) list_point.pop();
    //it maybe can get to the target with 10 steps
    optimal_add_element(list_point, special_0, target, 10);
    assert(list_point.size() == 1);
    while(!list_point.empty()) list_point.pop();

    // check the input location is the same as the destination
    assert(check_destination(special_0,special_1) == false);
    assert(check_destination(target,target) == true);
    test_point.x = 3;
    test_point.y = 4;
    test_point.direction = 'S';
    assert(check_destination(test_point,target) == true);

    //test add_Possible_Moving function
    list<string> action_path ;
    //testing location: [2,3] direction faced: s after 1 action allowed
    list_point.push(normal_1);
    add_Possible_Moving(target,list_point,action_path,1);
    //in this function, i add an optimal function that check every location before
    //putting in the list. There is one way to get to [3,4] in 1 remaining action allowed, so
    //this list is emply.
    assert(list_point.size() == 1);
    assert(action_path.size() == 0);//it cannot get to the destination
    while(!list_point.empty()) list_point.pop(); //remove everything from list
    /*In order to get to [3,4] from [2,3] and we only allow 2 actions,
    We can only moving forward. Turn left and turn right seems imposible to get there
    Therefore, list_point has size is 1*/
    list_point.push(normal_1);
    add_Possible_Moving(target,list_point,action_path,2);
    assert(list_point.size() == 3);
    assert(action_path.size() == 0);//it cannot get to the destination
    while(!list_point.empty()) list_point.pop(); //remove everything from list

    /*In order to get to [3,4] from [2,3] and we only allow 4 actions,
    robot maybe move forward, turn left or turn right, so robot will try all of them
    Therefore, list_point has size is 4. After the first step, it cannot get to the destination
    location, so action_path is 0*/
    list_point.push(normal_1);
    add_Possible_Moving(target,list_point,action_path,4);
    assert(list_point.size() == 3);
    assert(action_path.size() == 0);//it cannot get to the destination
    while(!list_point.empty()) list_point.pop();

    /*In order to get to [3,4] S from [3,4], E and we only allow 1 actions,
    robot maybe turn left or turn right, but it cannot move forward. Therefore,
    list_point is 2. Moreover, robot can turn right and get to the destination,
    so the action_path is 1. action_path contains the direction to get to that target*/
    normal_2.x = 3;
    normal_2.y = 4;
    normal_2.direction = 'E';
    list_point.push(normal_2);
    add_Possible_Moving(target,list_point,action_path,1);
    assert(list_point.size() == 3);
    assert(action_path.size() == 1);//it cannot get to the destination
}
