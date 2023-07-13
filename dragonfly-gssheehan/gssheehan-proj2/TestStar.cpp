//
// star.cpp
// 

//Dragonfly includes
#include "DisplayManager.h"
#include "EventOut.h"
#include "Object.h"
#include "WorldManager.h"

//Project includes
#include "TestStar.h"

//constructor
TestStar::TestStar() {

	//Stars should not be interacting with anything else, background material
	setType("Star");
	setSolidness(df::SPECTRAL);

	//Parallax effect: Randomly moving stars creates more depth in the background
	setVelocity(df::Vector((float)-1.0 / (rand() % 9 + 2), 0));

	//Stars are backgroud, so they should be covered
	setAltitude(0);

	//Position of star is chosen randomly over the window
	df::Vector p((float)(rand() % (int)DM.getHorizontal()),
		(float)(rand() % (int)DM.getVertical()));
	setPosition(p);

}

/**
* Event handler - gets invoked with every event the game world passes to the object
* Returned by getType - a method in the event class.
* At this point, the saucer will only handle the "out" event
*/
int TestStar::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		//new TestStar;
		return 1;
	}

	return 0;
}

/*
* Draw the star on the screen
*/
int TestStar::draw() {
	return DM.drawCh(getPosition(), STAR_CHAR, df::WHITE);
}

/*
* If the star moves off the window, move it back to the far right
*/
void TestStar::out() {
	
	df::Vector p((float)(DM.getHorizontal() + rand() % 20),
		(float)(rand() % (int)DM.getVertical()));
	setPosition(p);
	setVelocity(df::Vector((float)-1.0 / (rand() % 9 + 2), 0));
}