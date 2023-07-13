//
//manager.cpp
//

//C includes
#include <string>

//Dragonfly includes
#include "Manager.h"
#include "WorldManager.h"


//constructor
df::Manager::Manager() {
	m_is_started = false;
}

//destructor
df::Manager::~Manager() {

}

/*
* Startup manager
* Return:
* 	0 on successful startup
* 	-1 un unsuccessful startup
*/
int df::Manager::startUp() {
	m_is_started = true;
	return 0;
}

/*
* get manager type
*/
std::string df::Manager::getType() const {
	return "";
}

/*
* boolean that detects if manager is started
*/
bool df::Manager::isStarted() const {
	return false;
}

/*
* code that properly shuts manager down
*/
void df::Manager::shutDown() {
	m_is_started = false;
}

//sends an event to every object in the game world
int df::Manager::onEvent(const Event* p_event) const {
	//Create object list
	int count = 0;
	ObjectList all_objects = WM.getAllObjects();
	ObjectListIterator liObj(&all_objects);

	//Dynamic cast to event and pass to object
	for (liObj.first(); !liObj.isDone(); liObj.next()) {
		liObj.currentObject()->eventHandler(p_event);
		count++;
	}

	return count;
}