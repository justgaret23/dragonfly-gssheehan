//
//utility.cpp
//

//C includes
#define _CRT_SECURE_NO_DEPRECATE
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <sstream>

//Dragonfly includes
#include "Box.h"
#include "LogManager.h"
#include "Object.h"
#include "utility.h"
#include "Vector.h"
#include "WorldManager.h"


/*
* Return a nicely formatted time string (HH:MM::SS)
*/
char* getTimeString() {

	//Return time string, made static so it persists beyond the function
	static char time_str[30];

	//System calls to get current time
	time_t now;
	time(&now);
	struct tm* p_time = localtime(&now);

	//Burn time to the string.
	// "%02d gives two integer digits
	sprintf_s(time_str, "[%02d:%02d:%02d]",
		3 * sizeof(int),
		p_time->tm_hour,
		p_time->tm_min,
		p_time->tm_sec);

	//return
	return time_str;
}

/*
* Return true if two positions intersect, otherwise return false
*/
bool positionsIntersect(df::Vector p1, df::Vector p2){
	if(abs(static_cast<float>(p1.getX()) - static_cast<float>(p2.getX())) <= 1 &&
	   abs(static_cast<float>(p1.getY()) - static_cast<float>(p2.getY())) <= 1){
		//LM.writeLog("positions intersecting...");
		   return true;
	} else {
		   return false;
	   }
}

/*
* Return true if boxes intersect, else false
*/
bool boxIntersectsBox(df::Box A, df::Box B) {

	bool x_overlap = false;
	bool y_overlap = false;

	//Get all individual box coordinates
	//a
	float aX1 = A.getCorner().getX();
	float aY1 = A.getCorner().getY();
	float aX2 = A.getCorner().getX() + A.getHorizontal();
	float aY2 = A.getCorner().getY() + A.getVertical();

	//b
	float bX1 = B.getCorner().getX();
	float bY1 = B.getCorner().getY();
	float bX2 = B.getCorner().getX() + B.getHorizontal();
	float bY2 = B.getCorner().getY() + B.getVertical();

	//test horizontal overlap
	if ((bX1 <= aX1 && aX1 <= bX2) ||
		(aX1 <= bX1 && bX1 <= aX2)) {
		x_overlap = true;
	}

	//test vertical overlap
	if ((bY1 <= aY1 && aY1 <= bY2) ||
		(aY1 <= bY1 && bY1 <= aY2)) {
		y_overlap = true;
	}

	//check to see if the boxes overlap
	if (x_overlap && y_overlap) {
		return true;
	}
	else {
		return false;
	}
}

/*
* convert relative bounding box for object to absolute world box
*/
df::Box getWorldBox(const df::Object* p_o, df::Vector where) {
	df::Box temp_box = p_o->getBox();
	df::Vector corner = temp_box.getCorner();

	//convert coordinates
	corner.setX(corner.getX() + where.getX());
	corner.setY(corner.getY() + where.getY());
	temp_box.setCorner(corner);

	return temp_box;
}

//Convert world position to view position
df::Vector worldToView(df::Vector world_pos) {
	df::Vector view_origin = WM.getView().getCorner();
	float view_x = view_origin.getX();
	float view_y = view_origin.getY();

	df::Vector view_pos(world_pos.getX() - view_x, world_pos.getY() - view_y);

	return view_pos;
}

//Convert world position to view position
df::Vector viewToWorld(df::Vector view_pos) {
	df::Vector view_origin = WM.getView().getCorner();
	float view_x = view_origin.getX();
	float view_y = view_origin.getY();

	df::Vector world_pos(view_pos.getX() + view_x, view_pos.getY() + view_y);

	return world_pos;
}

std::string toString(int i) {
	std::stringstream ss;
	ss << i;
	return ss.str();
}