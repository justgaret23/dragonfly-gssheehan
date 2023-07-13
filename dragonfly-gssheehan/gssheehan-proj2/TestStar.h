#pragma once
//
//teststar.h
// 

//C includes
#include <stdlib.h>

//Dragonfly includes
#include "EventOut.h"
#include "Object.h"
#include "WorldManager.h"

//Defines
#define STAR_CHAR '.'


class TestStar : public df::Object {

private:
    void out();

public:
    TestStar();
    int draw(void) override;
    int eventHandler(const df::Event* p_e) override;
};
