#include <iostream>
#include <string>
#include <list> //used for list
#include <queue> //used for queue
#include <stdlib.h> //used for abs

using namespace std;

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
void find_path_to_destination(Point original, Point target,int numStep, list<string>& action_path);
void optimal_add_element(queue<Point>& list_point, Point point,Point target, int maximum_distance);
void part1(Point original, Point target, string actions);
void moveForward(Point& point);
void turnLeft(Point& point);
void turnRight(Point& point);


int main(int argc, char const *argv[]) {
    Point original, target;
    int numStep ;
    list<string> action_path;
    string actions, user_decision;
    do {
        cout<<"Please enter 1 to run part1, enter 2 to run part 2 or enter e to exit: ";
        cin>>user_decision;
        if (user_decision == "1") {
            get_input(original, target, true, numStep,actions);
            part1(original, target, actions);
        }
        else if(user_decision == "2"){
            get_input(original, target, true, numStep,actions);
            find_path_to_destination(original, target,numStep, action_path);
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
        if (x_original >8 || x_original<=0 || y_original <=0 || y_original >=9) {
            cout<<"Please enter again. e.g [3,4]\n";
        }
    } while(x_original >8 || x_original<=0 || y_original <=0 || y_original >=9);

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
            cout <<"Please enter Target position (e.g [2,3]): ";
            cin >>original_string;
            x_target = original_string.at(1)-'0';
            y_target = original_string.at(3)-'0';
            if (x_target >8 || x_target<=0 || y_target <=0 || y_target >=9) {
                cout<<"Please enter again. e.g [3,4]\n";
            }
        } while(x_target >8 || x_target<=0 || y_target <=0 || y_target >=9);
        do {
            cout << "Target position faced (e.g N): ";
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
 * Method: find_path_to_destination(void)
 * Scope:  Global
 * This function will use the concept of DFS to find the part between
 * 2 locations in the map
 *---------------------------------------------------------------------*/
void find_path_to_destination(Point original, Point target,int numStep, list<string>& action_path){
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
                //if robot is not x=1, it can move forward
                if (working.y != 1) {
                    point_move_forward.x = working.x;
                    point_move_forward.y = working.y - 1;
                    point_move_forward.direction = working.direction;
                    point_move_forward.path= original_path;
                    point_move_forward.path.append(",M");
                }
                //robot can turn left
                point_turn_left.x = working.x;
                point_turn_left.y = working.y;
                point_turn_left.direction= 'W';
                point_turn_left.path= original_path;
                point_turn_left.path.append(",R");
                //robot can turn right
                point_turn_right.x = working.x;
                point_turn_right.y = working.y;
                point_turn_right.direction= 'E';
                point_turn_right.path = original_path;
                point_turn_right.path.append(",L");
                break;

            case 'N':
                //if robot is not x=0, it can move forward
                if (working.y != 8) {
                    point_move_forward.x = working.x;
                    point_move_forward.y = working.y+1;
                    point_move_forward.direction = working.direction;
                    point_move_forward.path= original_path;
                    point_move_forward.path.append(",M");
                }
                //robot can turn left
                point_turn_left.x = working.x;
                point_turn_left.y = working.y;
                point_turn_left.direction= 'E';
                point_turn_left.path= original_path;
                point_turn_left.path.append(",R");
                //robot can turn right
                point_turn_right.x = working.x;
                point_turn_right.y = working.y;
                point_turn_right.direction= 'W';
                point_turn_right.path = original_path;
                point_turn_right.path.append(",L");
                break;

            case 'W':
                //
                if (working.x != 1) {
                    point_move_forward.x = working.x -1;
                    point_move_forward.y = working.y;
                    point_move_forward.direction = working.direction;
                    point_move_forward.path= original_path;
                    point_move_forward.path.append(",M");
                }
                //
                point_turn_left.x = working.x;
                point_turn_left.y = working.y;
                point_turn_left.direction= 'N';
                point_turn_left.path= original_path;
                point_turn_left.path.append(",R");

                point_turn_right.x = working.x;
                point_turn_right.y = working.y;
                point_turn_right.direction= 'S';
                point_turn_right.path = original_path;
                point_turn_right.path.append(",L");
                break;
            case 'E':
                //
                if (working.x != 8) {
                    point_move_forward.x = working.x + 1;
                    point_move_forward.y = working.y;
                    point_move_forward.direction = working.direction;
                    point_move_forward.path= original_path;
                    point_move_forward.path.append(",M");
                }
                //
                point_turn_left.x = working.x;
                point_turn_left.y = working.y;
                point_turn_left.direction= 'S';
                point_turn_left.path= original_path;
                point_turn_left.path.append(",R");

                point_turn_right.x = working.x;
                point_turn_right.y = working.y;
                point_turn_right.direction= 'N';
                point_turn_right.path = original_path;
                point_turn_right.path.append(",L");
                break;

            default:
                std::cerr << "something's wrong" << '\n';

        }
        check_destination_and_update_list(list_point, action_path, point_move_forward,
            point_turn_left, point_turn_right, target, maximum_distance);
        list_point.pop();
    }
}

void check_destination_and_update_list(queue<Point>& list_point, list<string>& action_path,
        Point forward, Point left, Point right, Point target, int maximum_distance){
    // check point which is moving forwarding
    if (forward.direction != 'o') {
        if (check_destination(target, forward)){
            action_path.push_back(forward.path);
        }
        optimal_add_element(list_point, forward, target, maximum_distance);
    }
    if (check_destination(target, left)){
        action_path.push_back(left.path);
    }

    if (check_destination(target, right)){
        action_path.push_back(right.path);
    }
    optimal_add_element(list_point, left, target, maximum_distance);
    optimal_add_element(list_point, right, target, maximum_distance);

}

void optimal_add_element(queue<Point>& list_point, Point point,Point target, int maximum_distance){
    if (abs(point.x - target.x)+ abs(point.y - target.y) <= maximum_distance) {
        list_point.push(point);
    }
}

void part1(Point original, Point target, string actions){
    actions.erase(std::remove(actions.begin(), actions.end(), ','), actions.end());
    for (size_t i = 0; i < actions.length(); i++) {
        if(actions.at(i) == 'M')
            moveForward(original);
        else if (actions.at(i) == 'L')
            turnLeft(original);
        else if(actions.at(i) == 'R')
            turnRight(original);
        else //if it contains anymore character than that, then returns
            return;
    }
    cout <<"Location: ["<<original.x<<","<<original.y<<"]\n";
    cout<<"Direction faced: "<<original.direction<<endl;
}
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
