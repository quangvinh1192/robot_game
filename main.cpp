#include <iostream>
#include <string>
#include <list>
#include <queue>
using namespace std;

struct Point{
    int x;
    int y;
    char direction;
    string path;
};
void get_input(Point& original, Point& target);
void add_new_point(Point original, Point target,queue<Point>& list_point, list<string>& action_path);
bool check_destination(Point target, Point point);
void check_destination_and_update_list(queue<Point>& list_point, list<string>& action_path,
        Point forward, Point left, Point right, Point target);


int main(int argc, char const *argv[]) {
    Point original, target;
    list<string> action_path;
    queue<Point> list_point;
    get_input(original, target);
    list_point.push(original);
    add_new_point(original, target, list_point, action_path);
    if (list_point.empty()) {
        std::cout << "empty" << '\n';
    }
    while (!list_point.empty())
    {
        std::cout << "x: " << list_point.front().x <<"  y: "<<list_point.front().y
            <<"  direction: "<<list_point.front().direction<< endl;;
        list_point.pop();
    }
    return 0;
}

void get_input(Point& original, Point& target){
    // int x_original, y_original, x_target, y_target;
    // char original_position, target_position;
    // cout <<"Please enter original position: ";
    // cin >> original.x >> original.y;
    // cout << "Original Direction faced: ";
    // cin >> original.direction;
    original.x = 3;
    original.y = 3;
    original.direction = 'S';
    target.x = 9;
    target.y = 3;
    target.direction = 'E';
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
void add_new_point(Point original, Point target,queue<Point>& list_point, list<string>& action_path){
    Point point_move_forward, point_turn_left, point_turn_right;
    int size = list_point.size();

    for (int i = 0; i < size; i++) {
        Point working= list_point.front();
        point_move_forward.direction='o';//create dummy value
        switch (working.direction) {
            case 'S':
                //if robot is not x=1, it can move forward
                if (working.y != 8) {
                    point_move_forward.x = working.x;
                    point_move_forward.y = working.y-1;
                    point_move_forward.direction = working.direction;
                    (point_move_forward.path).append(",M");

                }
                //robot can turn left
                point_turn_left.x = working.x;
                point_turn_left.y = working.y;
                point_turn_left.direction= 'W';
                (point_turn_left.path).append(",L");
                //robot can turn right
                point_turn_right.x = working.x;
                point_turn_right.y = working.y;
                point_turn_right.direction= 'E';
                (point_turn_right.path).append(",R");
                break;

            case 'N':
                //if robot is not x=0, it can move forward
                if (working.y != 8) {
                    point_move_forward.x = working.x;
                    point_move_forward.y = working.y+1;
                    point_move_forward.direction = working.direction;
                    (point_move_forward.path).append(",M");
                }
                //robot can turn left
                point_turn_left.x = working.x;
                point_turn_left.y = working.y;
                point_turn_left.direction= 'E';
                (point_turn_left.path).append(",L");
                //robot can turn right
                point_turn_right.x = working.x;
                point_turn_right.y = working.y;
                point_turn_right.direction= 'W';
                (point_turn_right.path).append(",R");
                break;

            case 'W':
                //
                if (working.x != 1) {
                    point_move_forward.x = working.x -1;
                    point_move_forward.y = working.y;
                    point_move_forward.direction = working.direction;
                    (point_move_forward.path).append(",M");
                }
                //
                point_turn_left.x = working.x;
                point_turn_left.y = working.y;
                point_turn_left.direction= 'N';
                (point_turn_left.path).append(",L");

                point_turn_right.x = working.x;
                point_turn_right.y = working.y;
                point_turn_right.direction= 'S';
                (point_turn_right.path).append(",R");
                break;
            case 'E':
                //
                if (working.x != 8) {
                    point_move_forward.x = working.x - 1;
                    point_move_forward.y = working.y;
                    point_move_forward.direction = working.direction;
                    (point_move_forward.path).append(",M");
                }
                //
                point_turn_left.x = working.x;
                point_turn_left.y = working.y;
                point_turn_left.direction= 'S';
                (point_turn_left.path).append(",L");

                point_turn_right.x = working.x;
                point_turn_right.y = working.y;
                point_turn_right.direction= 'N';
                (point_turn_right.path).append(",R");
                break;

            default:
                std::cerr << "something's wrong" << '\n';

        }
        check_destination_and_update_list(list_point, action_path, point_move_forward,
            point_turn_left, point_turn_right, target);
        list_point.pop();
    }
}

void check_destination_and_update_list(queue<Point>& list_point, list<string>& action_path,
        Point forward, Point left, Point right, Point target){
    // check point which is moving forwarding
    if (forward.direction != 'o') {
        if (check_destination(target, forward))
            action_path.push_back(forward.path);
        list_point.push(forward);
    }
    if (check_destination(target, left))
        action_path.push_back(left.path);

    if (check_destination(target, right))
        action_path.push_back(right.path);
    list_point.push(left);
    list_point.push(right);
}
