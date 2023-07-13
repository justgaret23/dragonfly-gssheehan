//
//gamemanager.cpp
//

//C logs
#include <Windows.h>

//Dragonfly logs
#include "Clock.h"
#include "DisplayManager.h"
#include "Event.h"
#include "EventStep.h"
#include "GameManager.h"
#include "InputManager.h"
#include "LogManager.h"
#include "Music.h"
#include "ResourceManager.h"
#include "ObjectList.h"
#include "ObjectListIterator.h"
#include "ViewObject.h"
#include "WorldManager.h"

//Project includes
#include "TestStaticObject.h"
#include "TestKinematicObject.h"
#include "TestHero.h"
#include "TestPoints.h"
#include "TestStar.h"


//singleton
df::GameManager& df::GameManager::getInstance() {
	static GameManager single;
	return single;
}

//constructor
df::GameManager::GameManager() {
	//frame time is 33 milliseconds
	game_over = false;
	frame_time = 33;
}

/*
* Start up all GameManager services
*/
int df::GameManager::startUp() {
	LM.startUp();
	RM.startUp();
	WM.startUp();
	DM.startUp();
	IM.startUp();
	timeBeginPeriod(1);
	return 0;
}

/*
* Shut down all GameManager services
*/
void df::GameManager::shutDown() {
	IM.shutDown();
	DM.shutDown();
	WM.shutDown();
	RM.shutDown();
	timeEndPeriod(1);
	setGameOver();
}

/*
* Run game loop
*/
void df::GameManager::run() {
	df::Clock clock;
	long int loop_time = 0;
	long int TARGET_TIME = frame_time; //convert frame time to milliseconds
	long int intended_sleep_time = 0; //Intended consistent sleep time
	long int actual_sleep_time = 0; //Actual sleep time
	long int adjust_time = 0; //necessary amount to adjust from intended to actual
	int game_loop_count = 0; //number of game loops

	//set up gameobjects
	TestStaticObject* hardTestObject = new TestStaticObject(df::Vector((float)DM.getHorizontal() / 2, (float)DM.getVertical() / 4), df::HARD, "HARD"); 
	TestStaticObject* softTestObject = new TestStaticObject(df::Vector((float)DM.getHorizontal() / 2, 3 * (float)DM.getVertical() / 4), df::SOFT, "SOFT");
	TestStaticObject* spectralTestObject = new TestStaticObject(df::Vector((float)DM.getHorizontal() / 2, 5 * (float)DM.getVertical() / 6), df::SPECTRAL, "SPECTRAL");

	TestKinematicObject* leftTestObject = new TestKinematicObject(df::Vector((float)DM.getHorizontal() / 4, (float)DM.getVertical() / 4), df::Vector(0, 0.25), df::HARD, "HARD");
	TestKinematicObject* rightTestObject = new TestKinematicObject(df::Vector(3 * (float)DM.getHorizontal() / 4, (float)DM.getVertical() / 4), df::Vector(0, 0.25), df::SOFT, "SOFT");

	TestHero* testerHero = new TestHero(); //test movable hero

	df::ViewObject* p_vo = new df::ViewObject;
	p_vo->setViewString("perhaps");
	p_vo->setValue(42);
	p_vo->setLocation(df::BOTTOM_CENTER);
	p_vo->setColor(df::RED);

	new TestPoints;

	//view objects have border bool
	//in draw, check if they have the border
	//if they do, draw the border
	
	new TestStar;
	new TestStar;
	new TestStar;
	new TestStar;
	new TestStar;
	new TestStar;
	new TestStar;
	new TestStar;
	new TestStar;
	new TestStar;
	new TestStar;
	new TestStar;
	new TestStar;
	new TestStar;
	new TestStar;
	new TestStar;

	// Play start music.
	df::Music* p_music = RM.getMusic("start music");
	p_music->play();

	//primary game loop
	while (!game_over) {
		clock.delta();

		//*********
		//get input
		
		IM.getInput();
		
		//*******
		// update game world state
		
		//get a list of all objects
		ObjectList obList = WM.getAllObjects();
		ObjectListIterator liObj(&obList);

		//Pass a step event to each object every frame
		EventStep st = EventStep(game_loop_count);
		Event* s = dynamic_cast<EventStep*>(&st);
		onEvent(s);
		
		//call world manager update
		WM.update();

		//*******************
		//draw current scene to buffer
		WM.draw();
		
		//******************** 
		//swap back buffer to current buffer
		DM.swapBuffers();

		//*******************
		//Get time of loop and sleep to keep things constant
		loop_time = clock.split()/1000;
		intended_sleep_time = TARGET_TIME - loop_time - adjust_time;
		clock.delta();

		//Ensure sleep time cannot go into the negatives, will cause some slowdown tho
		if (intended_sleep_time >= 0) {
			Sleep(intended_sleep_time);
		}

		//Get the actual sleep time and change adjust_time accordingly to keep the next loop in sync
		actual_sleep_time = clock.split()/1000;
		adjust_time = actual_sleep_time - intended_sleep_time;

		//If adjust time drops below zero, force it back to keep the game loop in sync
		if (adjust_time < 0) {
			adjust_time = 0;
		}

		//Increase game loop count so that event_step can keep track of things
		game_loop_count++;

		//Run step count tests after 50 steps
		if (game_loop_count == 50) {
			LM.writeLog("GAME OVER!!");
			//setStepCount and getStepCount tests
			if (st.getStepCount() == 50) {
				LM.writeLog("getStepCount works as intended!");
			}
			st.setStepCount(0);
			if (st.getStepCount() == 0) {
				LM.writeLog("setStepCount works as intended!");
			}
		}
	}

	//If we got out of the loop, setGameOver should work
	if (game_over) {
		LM.writeLog("setGameOver works!");
	}

	ObjectList obList = WM.getAllObjects();
	ObjectListIterator liObj(&obList);
	for (liObj.first(); !liObj.isDone(); liObj.next()) {
		WM.markForDelete(liObj.currentObject());
	}

	WM.update();
}

/*
Set gameover status to indicated value
If true, will stop game loop
*/
void df::GameManager::setGameOver(bool new_game_over) {
	game_over = new_game_over;
}

/*
* Get game over status
*/
bool df::GameManager::gameOver() const {
	return game_over;
}

/*
* Return frame time
* Frame time is target time for game loop in ms
*/
int df::GameManager::getFrameTime() const {
	return frame_time;
}