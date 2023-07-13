#pragma once
//
//testbullet.h
// 

//Engine includes
#include "Object.h"
#include "EventCollision.h"

#define BULLET_CHAR 'b'


class TestBullet : public df::Object {
private:
	void out();
	void hit(const df::EventCollision* p_collision_event);
public:
	TestBullet(df::Vector hero_pos);
	//int draw(void) override;
	int eventHandler(const df::Event* p_e) override;
};