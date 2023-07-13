//
//eventmouse.cpp
//

//Dragonfly includes
#include "EventMouse.h"


//constructor
df::EventMouse::EventMouse() {
	m_mouse_action = UNDEFINED_MOUSE_ACTION;
	m_mouse_button = Mouse::UNDEFINED_MOUSE_BUTTON;
	m_mouse_xy = Vector();
	setType(MSE_EVENT);
}

/*
* set mouse event's action
*/
void df::EventMouse::setMouseAction(EventMouseAction new_mouse_action){
	m_mouse_action = new_mouse_action;
}

/*
* get mouse event's action
*/
df::EventMouseAction df::EventMouse::getMouseAction() const{
	return m_mouse_action;
}

/*
* set mouse event's buttons
*/
void df::EventMouse::setMouseButton(Mouse::Button new_mouse_button){
	m_mouse_button = new_mouse_button;
}

/*
* get mouse event's buttons
*/
df::Mouse::Button df::EventMouse::getMouseButton() const{
	return m_mouse_button;
}

/*
* set mouse event's position
*/
void df::EventMouse::setMousePosition(Vector new_mouse_xy){
	m_mouse_xy = new_mouse_xy;
}

/*
* get mouse event's position
*/
df::Vector df::EventMouse::getMousePosition() const{
	return m_mouse_xy;
}

/*
* convert an SFML mouse input to Dragonfly mouse button event
* Returns the Dragonfly event
*/
df::Mouse::Button df::EventMouse::sfmlToDfMouse(sf::Mouse::Button sfmlButton) {
	switch (sfmlButton) {
	case sf::Mouse::Left:
		return df::Mouse::LEFT;
		break;
	case sf::Mouse::Right:
		return df::Mouse::RIGHT;
		break;
	case sf::Mouse::Middle:
		return df::Mouse::MIDDLE;
		break;
	}
}