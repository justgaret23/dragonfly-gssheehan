#pragma once
//
// object.h
// 

//C includes
#include <string>

//Dragonfly includes
#include "Animation.h"
#include "Box.h"
#include "Vector.h"
#include "Event.h"

//conditional compilation
#ifndef OBJECT_H_SEEN
#define OBJECT_H_SEEN


namespace df {
	
	enum Solidness {
		HARD, //object causes collisions and impedes
		SOFT, //object causes collisions but doesn't impede
		SPECTRAL, //object 
	};

	class Object {
	private:
		int m_id; //game engine identifier
		float m_speed; //object speed in direction
		std::string m_type; //defined type
		Vector m_position; //position in game world
		Vector m_direction; //direction vector
		int m_altitude; //0 to MAX supported (lower layers are drawn first)
		Solidness m_solidness; //solidness of object
		bool m_no_soft; //true if the object won't move onto soft objects
		Animation m_animation;
		Box m_box;
	public:
		//Construct object
		//Set default parameters and add it to the game world (WM)
		Object(); 

		//Destroy object
		//Remove it from the game world. (WM) it will not survive.
		virtual ~Object();

		//set object id
		void setId(int new_id);

		//get object id
		int getId() const;

		//set object speed
		void setSpeed(float new_speed);

		//get object speed
		float getSpeed() const;

		//set type identifier of object
		void setType(std::string new_type);

		//Get object type
		std::string getType();

		//set position of object
		void setPosition(Vector new_pos);


		//get position of object
		Vector getPosition() const;

		//set direction of object
		void setDirection(Vector new_direction);

		//get direction of object
		Vector getDirection() const;

		//set velocity of object
		void setVelocity(Vector new_velocity);

		//get velocity of object
		Vector getVelocity() const;

		//predict object position based on speed and direction
		//return predicted position
		Vector predictPosition();

		//Set altitude of object, with checks for range [0, MAX_ALTITUDE]
		//Return 0 if successful, -1 if not
		int setAltitude(int new_altitude);

		//Return altitude of object
		int getAltitude() const;

		//True if hard or soft
		//False is spectral or undefined
		bool isSolid() const;

		// Set object solidness, with checks for consistency
        // Return 0 if ok, -1 if not
		int setSolidness(Solidness new_solid);

		//Return object solidness
		Solidness getSolidness() const;

		//Set objects that cannot move onto soft objects
		void setNoSoft (bool new_no_soft = true);

		//Get an object's "no-soft" setting that stops it from moving onto soft objects
		bool getNoSoft() const;

		//Set sprite for this object to animate
		//Return 0 if ok, return -1 on fail
		int setSprite(std::string sprite_label);

		//Set animation for this object to a new one
		//Set bounding box to size of associated sprite
		void setAnimation(Animation new_animation);

		//Gets the animation for object
		Animation getAnimation() const;

		//set object's bounding box
		void setBox(Box new_box);

		//get object's bounding box
		Box getBox() const;

		virtual int eventHandler(const Event* p_e);

		//Update object behavior in world
		void update();

		//draw object in world
		virtual int draw();
	};
}

#endif