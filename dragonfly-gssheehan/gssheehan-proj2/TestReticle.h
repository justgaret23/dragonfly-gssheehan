#pragma once
//
// testreticle.h
// 

//Dragonfly includes
#include "Object.h"

//Defines
#define RETICLE_CHAR '+'


class TestReticle : public df::Object {
public:
	TestReticle();
	int draw(void) override;
	int eventHandler(const df::Event* p_e) override;
};