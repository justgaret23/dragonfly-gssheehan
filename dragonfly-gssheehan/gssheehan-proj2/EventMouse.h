#pragma once
//
//eventmouse.h
//

#include <SFML/Graphics.hpp>

#include "Event.h"
#include "Vector.h"

namespace df {
	const std::string MSE_EVENT = "df::mouse";

	//Set of mouse actions recognized by Dragonfly
	enum EventMouseAction {
		UNDEFINED_MOUSE_ACTION = -1,
		CLICKED,
		PRESSED,
		MOVED,
	};

	//set of mouse buttons recognized by dragonfly]
	namespace Mouse {
		enum Button {
			UNDEFINED_MOUSE_BUTTON = -1,
			LEFT,
			RIGHT,
			MIDDLE
		};
	}

	class EventMouse : public Event {
	private:
		EventMouseAction m_mouse_action; // mouse action
		Mouse::Button m_mouse_button; // mouse button
		Vector m_mouse_xy; // Mouse (x,y) coordinates.
	public:
		//constructor
		EventMouse();

		//load mouse event's action
		void setMouseAction(EventMouseAction new_mouse_action);

		//get mouse event's actions
		EventMouseAction getMouseAction() const;

		//set mouse event's buttons
		void setMouseButton(Mouse::Button new_mouse_button);

		//get mouse event's buttons
		Mouse::Button getMouseButton() const;

		//set mouse event's position
		void setMousePosition(Vector new_mouse_xy);

		//get mouse event y position
		Vector getMousePosition() const;

		//get mouse button!!!!!
		Mouse::Button sfmlToDfMouse(sf::Mouse::Button sfmlButton);
	};
}