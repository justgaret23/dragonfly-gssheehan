#pragma once
//
// testpoints.h
// 

//Dragonfly includes
#include "Event.h"
#include "ViewObject.h"

//Defines
#define POINTS_STRING "Points"


class TestPoints : public df::ViewObject {

public:
    TestPoints();
    int eventHandler(const df::Event* p_e) override;
};
