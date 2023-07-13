#pragma once
//
//teststaticobject.h
//

#include "Color.h"
#include "Object.h"
#include "EventStep.h"


class TestStaticObject : public df::Object {
private:
	std::string o_objectName;
	df::Color currentColor;
public:

	//constructor
	TestStaticObject(df::Vector position, df::Solidness collisionType, std::string objectName);

	//destructor
	virtual ~TestStaticObject();

	//Event handler
	int eventHandler(const df::Event* p_e) override;

	int draw(void) override;

	void step();
};