# 4253B Change Up Early Season Code

Software used by [VRC](https://www.vexrobotics.com/v5/competition/vrc-current-game) Team 4253B in the early season of [Change Up](https://www.youtube.com/watch?v=Hxs0q9UoMDQ). The software uses [PROS](https://pros.cs.purdue.edu/).

Check out our late season code [here](https://github.com/Yessir120/4253B-Change-Up-Late-Season). 

## Code Structure

The code is split up into different subsystems of the robot (i.e. chassis, rollers, etc.) found [here](https://github.com/Yessir120/4253B-Change-Up-Early-Season/tree/master/src/subsystems). 

### Subsystems 

* [`/src/subsystems/globals.cpp`](src/subsystems/globals.cpp)

Stores all global variables (i.e. motors, sensors, etc.)

* [`/src/subsystems/drive.cpp`](src/subsystems/drive.cpp)

Controls the chassis of the robot. Uses PID for movement and odometry for position tracking. 

* [`/src/subsystems/odom.cpp`](src/subsystems/odom.cpp)

An attempt at implementing odometry. Successful implementation found in [late season code](https://github.com/Yessir120/4253B-Change-Up-Late-Season). 

* [`/src/subsystems/intakes.cpp`](src/subsystems/intakes.cpp)

Controls the rollers and intakes of the robot. Custom auto index algorithm used to automatically index balls into the roller system. 

## Usage

1. Install PROS [here](https://pros.cs.purdue.edu/v5/getting-started/index.html)
2. Download code: 

| Git Installed | No Git Installed |
|---|---|
| Run ``git clone https://github.com/Yessir120/4253B-Change-Up-Late-Season.git`` in your terminal | Click the green ``Code`` button and select ``Download ZIP`` |
3. Run ``pros mu`` at the root of the project to build and upload the code to a VEX v5 Brain
4. Enjoy!

## License
[MIT](https://choosealicense.com/licenses/mit/)
