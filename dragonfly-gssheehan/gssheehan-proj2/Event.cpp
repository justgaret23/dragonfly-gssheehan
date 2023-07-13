//
//event.cpp
//

//Dragonfly includes
#include "Event.h"


//constructor
df::Event::Event() {
	m_event_type = "";
}

//destructor
df::Event::~Event(){

}

/*
* set event type
*/
void df::Event::setType(std::string new_type){
	m_event_type = new_type;
}

/*
* get event type
*/
std::string df::Event::getType() const{
	return m_event_type;
}