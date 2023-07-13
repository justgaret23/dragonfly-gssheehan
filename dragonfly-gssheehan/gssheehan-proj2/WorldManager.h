#pragma once
//
//worldmanager.h
//

//conditional compilation
#ifndef WORLDMANAGER_H_SEEN
#define WORLDMANAGER_H_SEEN

//C includes
#include <string>

//Dragonfly includes
#include "Manager.h"
#include "ObjectList.h"

# define WM df :: WorldManager :: getInstance ()


namespace df {

	const int MAX_ALTITUDE = 4;

	class WorldManager : public Manager {
	private:
		//Singleton
		WorldManager(); //private constructor
		WorldManager(WorldManager const&); //no copy
		void operator=(WorldManager const&); //no assign

		//other
		ObjectList m_updates; //All objects in world to update
		ObjectList m_deletions; //All objects in world to delete

		Box boundary;
		Box view;

		Object* p_view_following;
	public:
		//Get only instance of World Manager
		static WorldManager& getInstance();

		//startup game world (init everything to empty)
		//return 0 on success
		int startUp();

		//shutdown game world (delete all game world objects)
		void shutDown();

		//insert object into world
		//return 0 on success
		//return -1 on fail
		int insertObject(Object* p_o);

		//remove object from world
		//return 0 on success
		//return -1 on fail
		int removeObject(Object* p_o);

		//return list of all objects in world
		ObjectList getAllObjects() const;

		//return list of all objects in world matching type
		ObjectList objectsOfType(std::string type) const;

		//Return list of objects collided with at vector "where"
		//Only gets collisions with SOLID objects
		//Does not consider is p_o is solid or not
		ObjectList getCollisions (Object * p_o , Vector where) const ;

		// Move object .
 		// If there is a collision with a solid object, send collision events
 		// If there is no collision with a solid object, we are free to move the object
 		// If the object is spectral, we can move it without bothering with checks
 		// Return 0 if we can move, otherwise return -1 if there is a collision with a solid object
		int moveObject ( Object * p_o , Vector where ) ;

		//set game world boundary
		void setBoundary(Box new_boundary);

		//set game world boundary
		Box getBoundary() const;

		//set game world view
		void setView(Box new_view);

		//get game world view
		Box getView() const;

		//Set view to center window in position view_pos
		//View edge will not go beyond world boundary
		void setViewPosition(Vector view_pos);

		//Set view to cetner window on object
		//Set to NULL to stop following
		//If p_new_view_following not working, return -1
		//return 0 on success
		int setViewFollowing(Object* p_new_view_following);

		//Update world
		//Delete objects marked for deletion
		void update();

		//indicate an object is to be deleted at end of current game loop
		//return 0 on success
		//return -1 on fail
		int markForDelete(Object* p_o);

		//Draws all objects in world
		void draw();
	};
}

#endif
