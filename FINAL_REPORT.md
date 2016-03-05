#Final Project Report#

##Key components:##
* GameObject: Works as expected, GameObject works fine in prototyping for other objects in Ogre space.

* Ball: Almost as expected. The ball works perfectly in collision detection, changing into different states and checking boundaries. However, the user is not able to change the ball’s initial speed/velocity or material.

* Paddle: Paddle is the most time consuming part in this project that requires a lot of math adjustments. Our paddle works fine in moving in four directions (positive/negative along x-axis and positive/negative along y-axis). We rotate the paddle using the mouse. This was extremely difficult to get fully working due to the use of Euler angles. We only wanted to pitch and yaw the paddle, but not roll. We eventually solved this issue by implementing the paddle as a child of some parent node. The parent node would yaw which would cause the child orbit to the parent. When we wanted to pitch, we a would just pitch the child node. This prevented the roll that we didn’t want.

* Wall: Works as expected. Walls work fine in collision detection, sound playing and communicating with point system.

* UI: Works as expected. UI can display properly on the screen and react to possible user inputs. We switched from CEGUI to OgreText because we had difficulties in compiling CEGUI files. OgreText and OIS can interact with users but there are no instructions on controls. Users have to master basic operations to interact with the game.

* Sound: Works better. We have sound generated whenever ball collides with other game objects in the Ogre space. We enabled background music and users can mute it as well as the game sounds.

* Camera and Camera Control: The camera was implemented differently as we went along. It was initially behind the paddle. However, this made it too difficult to track the ball and the paddle at the same time. We came up with a way to track the middle position between the paddle and the ball. This made it much easier for the the player to follow the ball. We also added an ability for the user to zoom the camera in and out.

* Particle effects: We added particle effects (jet flame) at the end of the ball which makes the ball easier to track and it looks pretty cool.

* Point System: Works as expected. Point System can communicate with different files and report lose/win condition to TutorialApplication.cpp

* Bullet: Works as expected. Bullet is responsible for physical simulation. The only problem is it can detect only one collision at a time and if the object goes too fast, Bullet cannot update in time. In some extreme situations, the ball can fall out of the room because the speed is too fast. We also ran into an issue with the ContextCallback with Bullet. We learned that the ContextCallback does not work well when there are multiple collisions. We had a problem when the Paddle would be hitting the ground floor at the same time as the Ball. Sometimes the ContextCallback would detect it was the Ball and sometimes it would detect the Paddle. Otherwise, Bullet works fine for collision detection and real world simulation.

* Lose/Win Condition: The Win/Lose condition happens when the ball hits the ground twice. The game then evaluates whether the user wins or loses based on the total score and the high score. If the total score is higher than the high score, the high score is replaced by the total score, “New High Score” appears on the screen, and a winning sound is played. If the total score is equal to or lower than the high score, “Game Over” appears on the screen. 



##Final Game design##

In our initial design, we adopted complex rules that every wall can only be touched once and system keeps track of the current score, total score and highest score. System updates total score once the ball hits the paddle and the player loses the game if the ball hits ground twice. We later changed the rule because our rule requires lots of communication between different classes and instances of the same class. Added that we use OgreText for displaying scores so it will consume too much space to display three texts in a screen. We changed our rule to display two texts: current score and highest score in the screen. The ball can hit the wall multiple times. The game ends if the ball hits the ground twice.

##Extra Credit Implementations##

###Background Music###
* We have background music that starts when the scene is created for the game. The song we use is called “Released” from the Halo 3 soundtrack, which does not violate any copyright policy because it may be used “in non-profit ventures thanks to an arrangement with O'Donnell/Salvatori, Inc., composers of this iconic theme” (http://www.xbox.com/en-us/developers/rules)

###Improved Camera Controls###
* We added controls (the scroll wheel on the mouse) that zooms in and out of the paddle.

###End Condition###
* We added an end condition to the game. When the ball bounces twice on the ground without hitting the wall, one of two things will happen. If the total score is higher than the high score, a “New High Score” text appears over the screen and people cheering sound comes up. If the total score is equal to or lower than the high score, a “Game Over” text appears on the screen. After one of these options happen, the user has the ability to restart the game by pressing R

###Particle Effects###
* We simply added a jet flame particle effect at the end of the ball. Makes the ball easier to follow and can look really cool sometimes.
