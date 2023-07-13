
//Dragonfly includes
#include "DisplayManager.h"
#include "EventCollision.h"
#include "EventStep.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "EventOut.h"
#include "LogManager.h"
#include "Object.h"
#include "ObjectList.h"
#include "ResourceManager.h"
#include "Vector.h"
#include "WorldManager.h"

//Project includes
#include "TestKinematicObject.h"


//constructor
TestKinematicObject::TestKinematicObject(df::Vector position, df::Vector velocity, df::Solidness collisionType, std::string objectName) {
	//set members
	o_objectName = objectName;
	currentColor = df::GREEN;
	o_velocity = velocity;

	//Set basic attributes
	setSprite("saucer");
	setType("Kinematic");
	setAltitude(2);
	setPosition(position);
	setVelocity(o_velocity);
	setSolidness(collisionType);
}

//destructor
TestKinematicObject::~TestKinematicObject(){

}

//Event handler
int TestKinematicObject::eventHandler(const df::Event* p_e) {
	//Step logic for tester

	if (p_e->getType() == df::STEP_EVENT) {
		//LM.writeLog("Step event has been received by test object!");
		step();
		return 1;
	}

	if (p_e->getType() == df::OUT_EVENT) {
		LM.writeLog("Kinematic ran away!");
		out();
		return 1;
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		//Reverse color on hit
		const df::EventCollision* p_collision_event = dynamic_cast <df::EventCollision const*> (p_e);
		hit(p_collision_event);
	}
	return 0;
}

/*
//draw function
int TestKinematicObject::draw(void) {
	return DM.drawString(getPosition(), o_objectName, df::CENTER_JUSTIFIED, currentColor);
}
*/

//step function
void TestKinematicObject::step(){
	
}

//step function
void TestKinematicObject::hit(const df::EventCollision* p_c) {
	//If a bullet hits a saucer, it's done for
	if ((p_c->getObject1()->getType() == "Bullet") ||
		(p_c->getObject2()->getType() == "Bullet")) {

		WM.markForDelete(p_c->getObject1());
		WM.markForDelete(p_c->getObject2());

		// Play "explode" sound.
		df::Sound* p_sound = RM.getSound("explode");
		p_sound->play();

	}
}

//actions on out event
void TestKinematicObject::out() {
	df::Vector p((float)getPosition().getX(),
		(float)2.0);
	setPosition(p);

	//Periodically reverse direction of kinematic objects whenever the reach the appropriate barrier
	if (getVelocity().getY() > 0) {
		setVelocity(df::Vector(0, -0.25));
	}
	else {
		setVelocity(df::Vector(0, 0.25));
	}
}


