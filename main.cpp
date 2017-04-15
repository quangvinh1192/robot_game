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
void get_input(Point& original, Point& target);
void add_new_point(Point original, Point target,queue<Point>& list_point, list<string>& action_path,
                    int maximum_distance);
bool check_destination(Point target, Point point);
void check_destination_and_update_list(queue<Point>& list_point, list<string>& action_path,
        Point forward, Point left, Point right, Point target, int maximum_distance);
void find_path_to_destination(Point original, Point target,int numStep, list<string>& action_path);
void optimal_add_element(queue<Point>& list_point, Point point,Point target, int maximum_distance);

int main(int argc, char const *argv[]) {
    Point original, target;
    int numStep =4;
    list<string> action_path;

    get_input(original, target);
    find_path_to_destination(original, target,numStep, action_path);


    if (action_path.empty()) {
        std::cout << "empty" << '\n';
    }
    else{
        while (!action_path.empty()) {
            std::cout << action_path.front().erase(0, 1)<< '\n';
            action_path.pop_front();
        }
    }
    // while (!list_point.empty())
    // {
    //     std::cout << "x: " << list_point.front().x <<"  y: "<<list_point.front().y
    //         <<"  direction: "<<list_point.front().direction<< endl;;
    //     list_point.pop();
    // }
    return 0;
}

void get_input(Point& original, Point& target){
    // int x_original, y_original, x_target, y_target;
    // char original_position, target_position;
    // cout <<"Please enter original position: ";
    // cin >> original.x >> original.y;
    // cout << "Original Direction faced: ";
    // cin >> original.direction;
    original.x = 2;
    original.y = 3;
    original.direction = 'N';
    target.x = 3;
    target.y = 4;
    target.direction = 'S';
    // cout <<"Please enter original position: ";
    // cin >> target.x >> target.y;
    // cout << "Target position: ";
    // cin >> target.direction;
}
bool check_destination(Point target, Point point){
    if (target.x == point.x && target.y == point.y && target.direction == point.direction) {
        return true;
    }
    return false;
}

void find_path_to_destination(Point original, Point target,int numStep, list<string>& action_path){
    int count =0;
    queue<Point> list_point;
    list_point.push(original);
    while (count++ < numStep) {
        add_new_point(original, target, list_point, action_path, numStep- count);
        std::cout << "/* message */" << '\n';
        for (size_t i = 0; i < list_point.size(); i++) {
            std::cout << "x: " << list_point.front().x <<"  y: "<<list_point.front().y
                <<"  direction: "<<list_point.front().direction<<
                "  path: "<<list_point.front(). path<<endl;;
            list_point.push(list_point.front());
            list_point.pop();
        }
    }


}
void add_new_point(Point original, Point target,queue<Point>& list_point, list<string>& action_path,
                    int maximum_distance){

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
