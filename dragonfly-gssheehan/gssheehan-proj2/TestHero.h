#pragma once
//
//testhero.h
// 

//Dragonfly includes
#include "Object.h"
#include "EventKeyboard.h"
#include "EventMouse.h"

//Project includes
#include "TestReticle.h"


class TestHero : public df::Object {

private:
    TestReticle* p_reticle; //reticle for firing
    df::Color p_color;
    void kbd(const df::EventKeyboard* p_keyboard_event);
    void mouse(const df::EventMouse* p_mouse_event);
    void move(int dy);
    void step();
    void fire(df::Vector target);
    int move_slowdown;
    int move_countdown;
    int fire_slowdown;
    int fire_countdown;

public:
    TestHero();
    ~TestHero();
    int eventHandler(const df::Event* p_e) override;
    //int draw(void) override;
    void setColor(df::Color new_color);
};