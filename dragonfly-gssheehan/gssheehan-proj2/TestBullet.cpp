//
// testbullet.cpp
// 

//Engine includes
#include "DisplayManager.h"
#include "WorldManager.h"
#include "ObjectList.h"
#include "EventOut.h"
#include "LogManager.h"

//Project includes
#include "TestBullet.h"
#include "TestKinematicObject.h"
#include "TestHero.h"


//constructor
TestBullet::TestBullet(df::Vector hero_pos) {

	//Load bullet sprite and type
	setSprite("bullet");
	setType("Bullet");

	//Make the bullets soft so they can pass through hero if firing backwards
	setSolidness(df::SOFT);

	// Set starting location, based on hero's position passed in.
	df::Vector p(hero_pos.getX() + 3, hero_pos.getY());
	setPosition(p);

	//Fired bullets move 1 space each game loop. Always predetermined to be 1
	setSpeed(1);
}

/**
* Event handler - gets invoked with every event the game world passes to the object
* Returned by getType - a method in the event class.
* At this point, the saucer will only handle the "out" event
*/
int TestBullet::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <const df::EventCollision*> (p_e);
		hit(p_collision_event);
		return 1;
	}
	return 0;
}

/**
* Function that executes upon the bullet leaving the screen.
* Primarily exists to delete.
*/
void TestBullet::out() {
	df::ObjectList getHero = WM.objectsOfType("Hero");
	df::ObjectListIterator hli(&getHero);
	for (hli.first(); !hli.isDone(); hli.next()) {
		if (hli.currentObject()->getNoSoft()) {
			hli.currentObject()->setNoSoft(false);
		}
		else {
			hli.currentObject()->setNoSoft();
		}
		
	}
	WM.markForDelete(this);
}

/**
* Function that executes upon the bullet colliding with a saucer.
* Mark saucer and bullet for deletion
*/
void TestBullet::hit(const df::EventCollision* p_collision_event) {

	if ((p_collision_event->getObject1()->getType() == "Kinematic") ||
		(p_collision_event->getObject2()->getType() == "Kinematic")) {
		WM.markForDelete(p_collision_event->getObject1());
		WM.markForDelete(p_collision_event->getObject2());
	}
}

/*
* Draw the star on the screen
*/
/*
int TestBullet::draw() {
	return DM.drawCh(getPosition(), BULLET_CHAR, df::GREEN);
}
*/