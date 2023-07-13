//
//tester.cpp
//

//C includes
#include <string>

//Dragonfly includes
#include "Object.h"
#include "EventCollision.h"
#include "EventStep.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "LogManager.h"
#include "TestStaticObject.h"
#include "DisplayManager.h"
#include "Vector.h"


//constructor
TestStaticObject::TestStaticObject(df::Vector position, df::Solidness collisionType, std::string objectName) {
	//set members
	o_objectName = objectName;
	currentColor = df::GREEN;
	
	//set attributes
	setType("Tester");
	setAltitude(2);
	setSolidness(collisionType);
	setPosition(position);


}

//destructor
TestStaticObject::~TestStaticObject() {

}

/*
* Event handler - gets invoked with every event the game world passes to the object
* Returned by getType - a method in the event class.
* Primarily used for step events
*/
int TestStaticObject::eventHandler(const df::Event* p_e) {
	
	//Step logic for tester
	if (p_e->getType() == df::STEP_EVENT) {
		//LM.writeLog("Step event has been received by test object!");
		step();
		return 1;
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		//change color on collision
		if (currentColor == df::GREEN) {
			currentColor = df::YELLOW;
		}
		else {
			currentColor = df::GREEN;
		}
		return 1;
	}
	return 0;
}

//draw the static object
int TestStaticObject::draw() {
	return DM.drawString(getPosition(), o_objectName, df::CENTER_JUSTIFIED, currentColor);
}

void TestStaticObject::step() {

}