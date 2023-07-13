Garrett Sheehan (WPI username: gssheehan)
IMGD 3000 C01
Mark Claypool
2/09/2022

Project 2c: Dragonfly Naiad

Platform: Windows 10/11 - built using Visual Studio 2019

File Structure: All .cpp and .h files are provided in the folder "gssheehan-proj2." 
All other supporting files such dlls and font files can be found there as well.
Project is compiled using Visual Studio 2019's Build feature, and is also ran using Visual Studio 2019.

Tests: Version 2c of the Dragonfly game engine extends a toy created for version 2b.
       Within this toy, you can interact with objects of different solidness, shoot kinematic objects 
       with Saucer Shoot's bullets using mouse events, see Saucer Shoot's stars, and move the letter 
       a using keyboard events. For assignment 2c, I made a few extensions. I added sprites in place 
	 of many game objects. The movable character is now the hero sprite from saucer shoot, the 
	 kinematic objects are now saucers, and the bullets fired are now bullet sprites. All sprites 
	 are animated at different speeds. The saucer shoot fire sound effect plays when firing a bullet,
	 and saucer shoot's intro music plays when interacting with the toy. Two ViewObjects are on the
	 screen, with one incrementing by 10 points whenever the player fires. Collision is now handled
	 using collision boxes.

Bugs: I could not figure out how to convert reticle coordinates to world coordinates in time for
	submission. If you move all the way down, aiming becomes impossible because the reticle's window
	does not extend past the initial playing field. I have tried worldToView with no avail, and I will
	get extra help on this issue ASAP.