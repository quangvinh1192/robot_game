# Version1.<br />
The program reads the input information from the command line and  it checks/validate <br />
the input before processing the data. After that, it will call version1 function to do this job.<br />
<br />
Algorithm: When the program reads an action, it will perform that action and display<br />
the result to users.<br />
<br />
Error: When users enter an invalid position, direction faced or actions, users have to enter it again. <br />
Also, it will show the message when doing some invalid instructions such that:<br />
when robot is at [4,1]- direction faced: S, it cannot move forward. However, if users
tell it to do that. It will display the error like: <br />
```
Error: Robot cannot move 1 square forward at step: 1 because it's at [4,1] direction faced: S
and it will stay at current location.
```
<br />
Also, if it reads some invalid instructions such that "e", it will display this message and
stay at the same location: 
```
Error: Robot doesn't know the action e. It will ignore this action and continue to do the next step 
```
If the program runs successfully, it will display the message like:<br />

```
Robot is at: 
Location: [2,3]
Direction faced: S 
```
HOW TO COMPILE IT:<br />
This program runs on mac/linux terminal. In order to compile it, We have to go to robot_game folder <br />
type: "make" or "make robot" and press enter<br />

HOW TO RUN IT: <br />
In the robot_game folder, type "./robot" to run it.<br />
Enter 1 and press enter to run the version 1. Please give the correct input information.<br />

This is an simple example to run it:<br />
```
./robot
Please enter 1 to run version 1, enter 2 to run version 2 or enter e to exit: 1 
Please enter the information below:
Original position (e.g [2,3]): [2,3]
Original Direction faced (e.g N): N
Actions: M,M,L

Robot is at:
Location: [2,5]
Direction faced: W
```
Note: users have to enter the position by this format: [x,y] <br />
Direction faced can be a lower/uppercase <br />
Actions have to be separated by comma and can also be a lower/uppercase <br />
<br />
Here is an example output with error message: <br />
```
vinhtran$ ./robot  


Please entet 1 to run a version1, enter 2 to run a version 2 or enter e to extit: 1
Please enter the information below: 
Original position (e.g [2,3]): [1,1]
original Direction faced (e.g N): s
Actions: m,m,l,m,m
Error: Robot cannot move 1 square forward at step: 1 because it's at [1,1] direction faced: S 
Error: Robot cannot move 1 square forward at step: 1 because it's at [1,1] direction faced: S 

Robot is at: 
Location: [3,1] 
Direction faced: E 
```
--------------------------------------------------------------------------------
# Version2. <br />
Like version1, The program reads the input information from the command line and <br /> 
it checks/validate the input before processing the data. After that, it will call<br />
version2 function to do this job.<br />
<br />
Algorithm: The concept uses in this project like BFS. Every step, it will try all possible<br />
movements that robot can do such as: moving forward, turn left or turn right and keep it<br />
in the queue. However, it has a little big modification in this code such that before pushing<br />
any new location into the queue. It checks whenever it can get the target by using this node.<br />
For example, if a robot stays at [2,3]- N, it maybe can get to [3,4]- S within 4 actions.<br />
However, it cannot get to [8,8]-N by using 4 actions. As a result, in 2nd case, the point<br />
[2,3]-N cannot push into the queue. <br />

Error: When users enter an invalid position, direction faced or actions, users have to enter it again.<br />

<br />
HOW TO COMPILE IT: like version 1 <br />
<br />
HOW TO RUN IT:
It's similar to version1. We go to the robot_game folder in the command line, and type ./robot <br />
This is an example output when running it successfully:<br />
<br />

```
Please enter 1 to run version 1, enter 2 to run version 2 or enter e to exit: 2
Please enter the information below:
Original position (e.g [2,3]): [2,3]
Original Direction faced (e.g N): n
Target position (e.g [3,4]): [3,4]
Target position faced (e.g S): s
Maximum actions allowed: 4

Actions - 1 :M,R,M,R
No more possible actions!
```
Another example which cannot find any path: <br />
```
Please enter 1 to run version 1, enter 2 to run version 2 or enter e to exit: 2 
Please enter the information below:
Original position (e.g [2,3]): [1,1]
Original Direction faced (e.g N): s
Target position (e.g [3,4]): [2,3]
Target position faced (e.g S): n
Maximum actions allowed: 4
No possible actions!
```
<br />
--------------------------------------------------------------------------------
<br />
HOW TO TEST IT:<br />
I test it by using testAll function. I write some simple test cases and try to <br />
test a smaller function. That's why i wrote too many functions which is easy to test
and debug.<br />
I also test a whole program in papers and compare the result when running it <br />
--------------------------------------------------------------------------------
<br />author: Vinh Tran<br />
email: vqt004@ucsd.edu<br />
Please send me an email if you have any question about this project
