//
//eventstep.cpp
//

//Dragonfly includes
#include "EventStep.h"
#include "LogManager.h"


//default constructor
df::EventStep::EventStep() {
	m_step_count = 0;
	setType(STEP_EVENT);
}

//Constructor with initial step count
df::EventStep::EventStep(int init_step_count){
	m_step_count = init_step_count;
	setType(STEP_EVENT);
}

/*
* set step count
*/
void df::EventStep::setStepCount(int new_step_count){
	m_step_count = new_step_count;
}

/*
* get step count
*/
int df::EventStep::getStepCount() const{
	return m_step_count;
}