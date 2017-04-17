author: Vinh Tran<br />
email: vqt004@ucsd.edu<br />
--------------------------------------------------------------------------------
# Version1.
The program reads the input information from the command line and  it checks/validate
the input before processing the data. After that, it will call version1 function to do this job.
Algorithm: When the program reads an action, it will perform that action and display
the result to users.
Error: When users enter an invalid position, direction faced or actions,
users have to enter it again. Also, it will show the message when doing some invalid
instructions such that:
when robot is at [4,1]- direction faced: S, it cannot move forward. However, if users
tell it to do that. It will display the error like: "Error: Robot cannot move 1 square forward at step:
1 because it's at [4,1] direction faced: S" and it will stay at current location.
Also, if it reads some invalid instructions such that "e", it will display this message and
stay at the same location: "Error: Robot doesn't know the action e.
It will ignore this action and continue to do the next step"
If the program runs successfully, it will display the message like:
"Robot is at:
Location: [2,3]
Direction faced: S

HOW TO COMPILE IT:
This program runs on mac/linux terminal. In order to compile it, We have to go to robot_game folder
type: "make" or "make robot" and press enter

HOW TO RUN IT:
In the robot_game folder, type "./robot" to run it.
Enter 1 and press enter to run the version 1. Please give the correct input information.
This is an simple example to run it:
'''
./robot
Please enter 1 to run version 1, enter 2 to run version 2 or enter e to exit: 1
Please enter the information below:
Original position (e.g [2,3]): [2,3]
Original Direction faced (e.g N): N
Actions: M,M,L

Robot is at:
Location: [2,5]
Direction faced: W
'''

Note: position has to enter by this format: [x,y]
Direction faced can be lower/uppercase
Actions: has to be separated by comma and can be lower/uppercase

Here is an example output with error message:
'''
Please enter 1 to run version 1, enter 2 to run version 2 or enter e to exit: 1
Please enter the information below:
Original position (e.g [2,3]): [4,1]
Original Direction faced (e.g N): S
Actions: M,M,L
Error: Robot cannot move 1 square forward at step: 1 because it's at [4,1] direction faced: S
Error: Robot cannot move 1 square forward at step: 2 because it's at [4,1] direction faced: S

Robot is at:
Location: [4,1]
Direction faced: E
'''
EXIT PROGRAM by type e and press enter.

--------------------------------------------------------------------------------
# Version2.
Like version1, The program reads the input information from the command line and  
it checks/validate the input before processing the data. After that, it will call
version2 function to do this job.
Algorithm: The concept uses in this project like BFS. Every step, it will try all possible
movements that robot can do such as: moving forward, turn left or turn right and keep it
in the queue. However, it has a little big modification in this code such that before pushing
any new location into the queue. It checks whenever it can get the target by using this node.
For example, if a robot stays at [2,3]- N, it maybe can get to [3,4]- S within 4 actions.
However, it cannot get to [8,8]-N by using 4 actions. As a result, in 2nd case, the point
[2,3]-N cannot push into the queue.
Error: When users enter an invalid position, direction faced or actions,
users have to enter it again.

HOW TO COMPILE IT: like version 1

HOW TO RUN IT:
It's similar to version1. We go to the robot_game folder in the command line,
and type ./robot
This is an example output when running it successfully:
'''
Please enter 1 to run version 1, enter 2 to run version 2 or enter e to exit: 2
Please enter the information below:
Original position (e.g [2,3]): [2,3]
Original Direction faced (e.g N): n
Target position (e.g [3,4]): [3,4]
Target position faced (e.g S): s
Maximum actions allowed: 4

Actions - 1 :M,R,M,R
No more possible actions!
'''
Another example which cannot find any path:
'''
Please enter 1 to run version 1, enter 2 to run version 2 or enter e to exit: 2
Please enter the information below:
Original position (e.g [2,3]): [1,1]
Original Direction faced (e.g N): s
Target position (e.g [3,4]): [2,3]
Target position faced (e.g S): n
Maximum actions allowed: 4
No possible actions!
'''
--------------------------------------------------------------------------------
HOW TO TEST IT:
I test it by using testAll function. I write some simple test cases and try to
test a smaller function. That's why i wrote too many functions which is easy to test
and debug.
I also test a whole program in papers and compare when running it
