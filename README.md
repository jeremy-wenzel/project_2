<!---# Building the Executable

1. Place the project_1_jhw866 (may also be name project_1_jhw866-master) folder that contains the code and executable into some desired directory. The directory doesn't matter. This project is based of Ronald's OgreAppBase.

2. CD into the project_1_jhw866 directory.

3. Run the following command "mkdir Build && cd Build/". This is where we will do the CMake business.

4. Then run the following command "cmake -DOGRE_HOME=/lusr/opt/ogre-1.9/ ..". This will create all the dependencies needed for Ogre to be compiled with the project.

5. Run the following comman "make". This will compile the code into an executable placed in Binaries/ titled "ProjectName"

6. To run the executable, run the following command "./Binaries/ProjectName"

7. Wala!

8. There is also an executable of the project in the root of the directory called "ProjectName". The code for the project is located in "Source/Core"-->

README file for assignment2 milestone 3

Functions:
1. Camera chasing after the ball
2. Implemented sound on collisions
3. Implemented paddle movement
4. Integrated physics
5. Added background music
6. Added lose condition
7. Added special sound on win
8. Added player control, e.g. pause, restart, start
9. Display text on screen


User Manual:
R: restart + reset ball
Left Click: start
P: pause
WASDQR camera control