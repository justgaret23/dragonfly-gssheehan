//
// testhero.cpp
// 

//Dragonfly includes
#include "DisplayManager.h"
#include "GameManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "EventStep.h"
#include "EventMouse.h"
#include "EventOut.h"
#include "EventView.h"
#include "EventCollision.h"
#include "ResourceManager.h"
#include "Sound.h"
#include "Vector.h"

//Project includes
#include "TestHero.h"
#include "TestBullet.h"
#include "TestPoints.h"


//constructor
TestHero::TestHero() {

	//Register for any events that the object may use. For the hero, this is the keyboard event, as we control them.
	p_color = df::YELLOW;
	setType("Hero");
	setAltitude(3);
	setSolidness(df::HARD);
	setSprite("ship");

	//make camera follow hero
	WM.setViewFollowing(this);
	//setNoSoft();


	//Place hero
	df::Vector p((float)DM.getHorizontal() / 2, (float)DM.getVertical() / 2);
	setPosition(p);

	//initialize slowdown and countdown ints
	move_slowdown = 2;
	move_countdown = move_slowdown;

	fire_slowdown = 15;
	fire_countdown = fire_slowdown;

	//create reticle to test mouse movement
	p_reticle = new TestReticle();
	p_reticle->draw();
}

//destructor
TestHero::~TestHero() {
	//mark reticle for deletion on end
	WM.markForDelete(p_reticle);
}

/**
* Event handler - gets invoked with every event the game world passes to the object
* Returned by getType - a method in the event class.
* The Hero will use the keyboard event because we control them
*/
int TestHero::eventHandler(const df::Event* p_e) {
	//Move logic
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		//Respond to only the keyboard event.
		//We do this by casting a generic event object pointer as an eventKeyboard object pointer
		//We then call kbd using that method
		const df::EventKeyboard* p_keyboard_event = dynamic_cast <const df::EventKeyboard*> (p_e);
		kbd(p_keyboard_event);
		return 1;
	}

	//Step logic for hero
	if (p_e->getType() == df::COLLISION_EVENT) {
		return 1;
	}

	if (p_e->getType() == df::OUT_EVENT) {
		LM.writeLog("Hey where you going?");
		return 1;
	}

	//Fire logic
	if (p_e->getType() == df::MSE_EVENT) {
		const df::EventMouse* p_mouse_event = dynamic_cast <const df::EventMouse*> (p_e);
		mouse(p_mouse_event);
		return 1;
	}

	//Step logic for hero
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}
	return 0;
}

/*
* Controls: Take the appropriate action depending on what key is pressed
*/
void TestHero::kbd(const df::EventKeyboard* p_keyboard_event) {
	switch (p_keyboard_event->getKey()) {
	case df::Keyboard::Q: //quit
		//kill the game
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			WM.markForDelete(this);
			GM.setGameOver();
		}
		break;
	case df::Keyboard::W: //up
		//LM.writeLog("up");
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			//LM.writeLog("up");
			move(-1);
		}
		break;
	case df::Keyboard::S: //down
		//LM.writeLog("down");
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			move(+1);
		}
		break;
	default: //key not handled
		return;
	};
	return;
}

/*
* Take appropriate action from mouse
*/
void TestHero::mouse(const df::EventMouse* p_mouse_event) {
	if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
		(p_mouse_event->getMouseButton() == df::Mouse::LEFT)) {
		fire(p_reticle->getPosition());
	}
}

/*
* Movement: Move the hero up or down
*/
void TestHero::move(int dy) {
	// See if time to move.
	if (move_countdown > 0)
		return;
	move_countdown = move_slowdown;

	//if the hero stays on the game window, allow the move
	// If stays on window, allow move.
	df::Vector new_pos(getPosition().getX(), getPosition().getY() + dy);

	//Only allow moves if the ship stays on the screen and is under the display elements
	if ((new_pos.getY() > 3)) {
		WM.moveObject(this, new_pos);
	}

	//adjust view to keep hero in center of screen
	/*
	df::Box new_view = WM.getView();
	df::Vector corner = new_view.getCorner();
	corner.setY(corner.getY() + dy);
	new_view.setCorner(corner);
	WM.setView(new_view);
	*/
}


/*
* Step logic for hero.
* Mainly exists to handle cooldowns.
*/
void TestHero::step() {
	// Move countdown.
	move_countdown--;
	if (move_countdown < 0) {
		move_countdown = 0;
	}

	//fire countdown
	fire_countdown--;
	if (fire_countdown < 0) {
		fire_countdown = 0;
	}
}

void TestHero::fire(df::Vector target) {
	if (fire_countdown > 0) {
		return;
	}
	fire_countdown = fire_slowdown;

	// Fire Bullet towards target.
	// Compute normalized vector to position, then scale by speed (1).
	df::Vector v = target - getPosition();
	v.normalize();
	v.scale(1);


	TestBullet* p = new TestBullet(getPosition());
	p->setVelocity(v);

	df::EventView ev(POINTS_STRING, 10, true);
	WM.onEvent(&ev);

	// Play "fire" sound.
	df::Sound* p_sound = RM.getSound("fire");
	p_sound->play();
}

void TestHero::setColor(df::Color new_color) {
	p_color = new_color;
}

