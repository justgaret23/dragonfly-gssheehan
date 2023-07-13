//
// points.cpp
// 

//Project includes
#include "EventStep.h"
#include "TestPoints.h"


//constructor
TestPoints::TestPoints() {

    //Set attributes of points to display it properly
    setLocation(df::TOP_RIGHT);
    setViewString(POINTS_STRING);
    setColor(df::YELLOW);

    //Update score every second, so use step events
    //registerInterest(df::STEP_EVENT);
}

/**
* Event handler - gets invoked with every event the game world passes to the object
* Returned by getType - a method in the event class.
* The reflector only checks for collisions with enemy saucers
*/
int TestPoints::eventHandler(const df::Event* p_e) {
    //Parent handles the event if the score updates
    if (df::ViewObject::eventHandler(p_e)) {
        return 1;
    }

    //We want to increment the score every 30 steps (remember, DF runs at 30fps)
    if (p_e->getType() == df::STEP_EVENT) {
        if (dynamic_cast <const df::EventStep*> (p_e)->getStepCount() % 30 == 0)
            setValue(getValue() + 1);
        return 1;
    }

    //If we get here, we ignored the event
    return 0;
}