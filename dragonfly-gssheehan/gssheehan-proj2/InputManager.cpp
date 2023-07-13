//
//inputmanager.cpp
//

//Dragonfly includes
#include "DisplayManager.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "InputManager.h"
#include "LogManager.h"
#include "ObjectList.h"
#include "ObjectListIterator.h"
#include "WorldManager.h"
#include "utility.h"


//constructor
df::InputManager::InputManager() {

}

//get singleton instance of inputmanager
df::InputManager& df::InputManager::getInstance() {
	static InputManager single;
	return single;
}


/*
* get window ready to capture input
* Return 0 if success, -1 if fail
*/
int df::InputManager::startUp() {

	//Check to see if display manager is started before starting
	if (DM.startUp() == false) {
		return -1;
	}

	sf::RenderWindow* window = DM.getWindow();

	//Disable keyboard repeat for input
	window->setKeyRepeatEnabled(false);

	Manager::startUp();
	return 0;
}

/*
* Revert back to normal window mode
*/
void df::InputManager::shutDown(){

	sf::RenderWindow* window = DM.getWindow();

	//Enable keyboard repeat for input
	window->setKeyRepeatEnabled(false);

	Manager::startUp();

}

/*
* Get input from the keyboard and mouse
* Pass event along to all objects
*/
void df::InputManager::getInput(){

	sf::Event event;
	sf::RenderWindow* window = DM.getWindow();

	//update game world state
	//get a list of all objects
	ObjectList obList = WM.getAllObjects();
	ObjectListIterator liObj(&obList);

	static int previousMouseMoveX = 0;
	static int previousMouseMoveY = 0;

	//preliminary check to see what inputs are in action
	while (window->pollEvent(event)) {
		previousMouseMoveX = event.mouseMove.x;



		//key was pressed
		if (event.type == sf::Event::KeyPressed) {
			//Set keyboard action
			df::EventKeyboard evPress = EventKeyboard();
			evPress.setKey(evPress.sfmlToDf(event.key.code));
			evPress.setKeyboardAction(df::EventKeyboardAction::KEY_PRESSED);

			//Dynamic cast to event and pass to objects
			Event* s = dynamic_cast<EventKeyboard*>(&evPress);
			onEvent(s);
		}

		//key was released
		if (event.type == sf::Event::KeyReleased) {
			//Set keyboard action
			df::EventKeyboard evPress = EventKeyboard();
			evPress.setKey(evPress.sfmlToDf(event.key.code));
			evPress.setKeyboardAction(df::EventKeyboardAction::KEY_RELEASED);

			//Dynamic cast to event and pass to objects
			Event* s = dynamic_cast<EventKeyboard*>(&evPress);
			onEvent(s);
		}

		//mouse was moved
		if (event.type == sf::Event::MouseMoved) {
			df::EventMouse evPress = EventMouse();
			evPress.setMouseAction(df::EventMouseAction::MOVED);

			//Convert mouse vector before setting it to mouse position
			Vector mouseVector = Vector((float)event.mouseMove.x + (float)WM.getView().getCorner().getX(), (float)event.mouseMove.y + (float)WM.getView().getCorner().getY());
			Vector pixel_pos = DM.pixelsToSpaces(mouseVector);
			Vector view_pos = viewToWorld(pixel_pos);
			evPress.setMousePosition(view_pos);

			//Dynamic cast to event and pass to objects
			Event* s = dynamic_cast<EventMouse*>(&evPress);
			onEvent(s);
		}

		//mouse was clicked
		if (event.type == sf::Event::MouseButtonPressed) {
			df::EventMouse evPress = EventMouse();
			evPress.setMouseButton(evPress.sfmlToDfMouse(event.mouseButton.button));
			evPress.setMouseAction(df::EventMouseAction::CLICKED);

			

			Vector mouseVector = Vector((float)event.mouseButton.x + (float)WM.getView().getCorner().getX(), (float)event.mouseButton.y + (float)WM.getView().getCorner().getY());
			Vector pixel_pos = DM.pixelsToSpaces(mouseVector);
			Vector view_pos = viewToWorld(pixel_pos);
			evPress.setMousePosition(view_pos);

			

			//Dynamic cast to event and pass to objects
			Event* s = dynamic_cast<EventMouse*>(&evPress);
			onEvent(s);
		}

		//mouse was released
		if (event.type == sf::Event::MouseButtonReleased) {
			df::EventMouse evPress = EventMouse();
			evPress.setMouseButton(evPress.sfmlToDfMouse(event.mouseButton.button));
			evPress.setMouseAction(df::EventMouseAction::CLICKED);

			Vector mouseVector = Vector((float)event.mouseButton.x + (float)WM.getView().getCorner().getX(), (float)event.mouseButton.y + (float)WM.getView().getCorner().getY());
			Vector pixel_pos = DM.pixelsToSpaces(mouseVector);
			Vector view_pos = viewToWorld(pixel_pos);
			evPress.setMousePosition(view_pos);

			//Dynamic cast to event and pass to objects
			Event* s = dynamic_cast<EventMouse*>(&evPress);
			onEvent(s);
		}
	}
	if (event.mouseMove.x > 0) {
		previousMouseMoveX = event.mouseMove.x;
	}

	if (event.mouseMove.y > 0) {
		previousMouseMoveY = event.mouseMove.y;
	}

	//Determine is a key is being pressed, then pass a keyboard event
	if (event.key.code >= 0) {
		df::EventKeyboard evPress = df::EventKeyboard();
		evPress.setKey(evPress.sfmlToDf(event.key.code));
		evPress.setKeyboardAction(df::EventKeyboardAction::KEY_PRESSED);

		//Dynamic cast to event and pass to objects
		Event* s = dynamic_cast<EventKeyboard*>(&evPress);
		onEvent(s);
	}

	//cover mouse click
	if (event.type == sf::Event::MouseButtonPressed) {
		//construct mouse event
		df::EventMouse evClick = df::EventMouse();
		evClick.setMouseButton(evClick.sfmlToDfMouse(event.mouseButton.button));
		evClick.setMouseAction(df::EventMouseAction::CLICKED);

		

		Vector mouseVector = Vector((float)event.mouseButton.x + (float)WM.getView().getCorner().getX(), (float)event.mouseButton.y + (float)WM.getView().getCorner().getY());
		Vector pixel_pos = DM.pixelsToSpaces(mouseVector);
		Vector view_pos = viewToWorld(pixel_pos);
		evClick.setMousePosition(view_pos);

		//LM.writeLog("click!");
		LM.writeLog("EvPress x: %f", evClick.getMousePosition().getX());
		LM.writeLog("EvPress y: %f", evClick.getMousePosition().getY());

		//Dynamic cast to event and pass to objects
		Event* s = dynamic_cast<EventMouse*>(&evClick);
		onEvent(s);
	}

	//cover mouse movement
	if (event.type == sf::Event::MouseMoved) {
		df::EventMouse evPress = EventMouse();
		evPress.setMouseAction(df::EventMouseAction::MOVED);
		Vector mouseVector = Vector((float)event.mouseMove.x + (float)WM.getView().getCorner().getX(), (float)event.mouseMove.y + (float)WM.getView().getCorner().getY());
		Vector pixel_pos = DM.pixelsToSpaces(mouseVector);
		Vector view_pos = viewToWorld(pixel_pos);
		evPress.setMousePosition(view_pos);

		//Dynamic cast to event and pass to objects
		Event* s = dynamic_cast<EventMouse*>(&evPress);
		onEvent(s);
	}
}