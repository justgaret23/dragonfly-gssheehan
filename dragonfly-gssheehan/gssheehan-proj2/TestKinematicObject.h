#pragma once
//
//testkinematicobject.h
//

#include "Color.h"
#include "Object.h"
#include "EventCollision.h"
#include "EventStep.h"


class TestKinematicObject : public df::Object {
private:
	std::string o_objectName;
	df::Vector o_velocity;
	df::Color currentColor;
public:

	//constructor
	TestKinematicObject(df::Vector position, df::Vector velocity, df::Solidness collisionType, std::string objectName);

	//destructor
	virtual ~TestKinematicObject();

	//Event handler
	int eventHandler(const df::Event* p_e) override;

	//int draw(void) override;

	void step();
	void out();
	void hit(const df::EventCollision* p_c);
};