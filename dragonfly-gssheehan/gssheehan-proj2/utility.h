#pragma once
//
//utility.h
//

//Dragonfly includes
#include "Box.h"
#include "Object.h"
#include "Vector.h"

//stubs
char* getTimeString();
bool positionsIntersect(df::Vector p1, df::Vector p2);
bool boxIntersectsBox(df::Box A, df::Box B);
df::Box getWorldBox(const df::Object* p_o, df::Vector where); \
df::Vector worldToView(df::Vector world_pos);
std::string toString(int i);
df::Vector viewToWorld(df::Vector view_pos);