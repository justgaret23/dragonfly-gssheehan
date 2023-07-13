//Dragonfly includes
#include "WorldManager.h"
#include "DisplayManager.h"
#include "LogManager.h"
#include "EventMouse.h"

//Project includes
#include "TestReticle.h"


//constructor
TestReticle::TestReticle() {
	//object type is reticle
	setType("Reticle");

	//Reticle should not collide with other objects, so it is soft
	//occasionally will constantly register collisions every update
	setSolidness(df::SPECTRAL);

	//Assign max visual layer to ensure retical is always visible
	setAltitude(df::MAX_ALTITUDE);

	//Register interest in mouse
	//registerInterest(df::MSE_EVENT);

	//Set initial reticle position
	df::Vector p((float)DM.getHorizontal() / 3, (float)DM.getVertical() / 2);
	setPosition(p);
}

/**
* Event handler - gets invoked with every event the game world passes to the object
* Returned by getType - a method in the event class.
* At this point, the saucer will only handle the "out" event
*/
int TestReticle::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::MSE_EVENT) {
		const df::EventMouse* p_mouse_event = dynamic_cast <const df::EventMouse*> (p_e);
		//If the mouse is moved, change the reticle's position accordingly
		if (p_mouse_event->getMouseAction() == df::CLICKED) {
			setPosition(p_mouse_event->getMousePosition());
			return 1;
		}


		//If the mouse is moved, change the reticle's position accordingly
		if (p_mouse_event->getMouseAction() == df::MOVED) {
			setPosition(p_mouse_event->getMousePosition());

			return 1;
		}
	}

	//If we make it here, we ignore the event
	return 0;
}

/*
* We draw a reticle on the window using RETICLE_CHAR, we don't need a sprite
*/
int TestReticle::draw() {
	return DM.drawCh(getPosition(), RETICLE_CHAR, df::RED);
}