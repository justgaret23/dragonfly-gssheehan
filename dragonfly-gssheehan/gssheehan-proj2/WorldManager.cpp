//
//worldmanager.cpp
//

//Dragonfly includes
#include "DisplayManager.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "LogManager.h"
#include "GameManager.h"
#include "WorldManager.h"
#include "ObjectList.h"
#include "ObjectListIterator.h"
#include "utility.h"

//stubs
bool outOfBounds(df::Object* p_o);


//singleton
df::WorldManager& df::WorldManager::getInstance() {
	static WorldManager single;
	return single;
}

//constructor
df::WorldManager::WorldManager() {
	//frame time is 33 milliseconds
}

/*
* startup game world (init everything to empty)
* return 0 on success
*/
int df::WorldManager::startUp() {
	return df::Manager::startUp();
}

/*
* shutdown game world (delete all game world objects)
*/
void df::WorldManager::shutDown() {
	df::ObjectList ol = m_updates;

	//Remove every object from the world
	ObjectListIterator li(&ol);
	for (li.first(); !li.isDone(); li.next()) {
		
		removeObject(li.currentObject());
		LM.writeLog("There are %d objects left in the world.", ol.getcount());
	}

	//Typical shutdown code
	Manager::shutDown();
}


/*
* insert object into world (m_updates)
* return 0 on success
* return -1 on fail
*/
int df::WorldManager::insertObject(Object* p_o) {
	m_updates.insert(p_o);
	return 0;
}


/*
* remove object from world
* return 0 on success
* return -1 on fail
*/
int df::WorldManager::removeObject(Object* p_o) {
	m_updates.remove(p_o);
	return 0;
}

/*
* return list of all objects in world
*/
df::ObjectList df::WorldManager::getAllObjects() const {
	return m_updates;
}

/*
* return list of all objects in world matching type
*/
df::ObjectList df::WorldManager::objectsOfType(std::string type) const {
	df::ObjectList list = m_updates;
	df::ObjectListIterator li(&list);

	//Add all objects of the desired type to new ObjectList typeList, and then return it
	df::ObjectList typeList = ObjectList();
	for (li.first(); !li.isDone(); li.next()) {
		if (li.currentObject()->getType() == type) {
			typeList.insert(li.currentObject());
		}
	}
	return typeList;
}

/*
* Return list of objects collided with at vector "where"
* Only gets collisions with SOLID objects
* Does not consider is p_o is solid or not
*/
df::ObjectList df::WorldManager::getCollisions(Object * p_o , Vector where) const {
	//make empty list
	ObjectList collision_list;

	//update initialize
	df::ObjectList uList = m_updates;
	df::ObjectListIterator li(&uList);
	for (li.first(); !li.isDone(); li.next()) {
		Object* p_temp_o = li.currentObject();

		//Prevent the object* from checking itself with first if
		if (p_temp_o != p_o) {

			Box b = getWorldBox(p_o, where);
			Box b_temp = getWorldBox(p_temp_o, p_temp_o->getPosition());

			//Check to see if both objects are in the same location and both are solid
			//if(positionsIntersect(p_o->getPosition(), p_temp_o->getPosition()) &&
			if (boxIntersectsBox(b, b_temp) &&
				p_temp_o->isSolid()) {
				collision_list.insert(p_temp_o);
			}
		}
	}

	//Return list when all collisions are found
	return collision_list;
}

/*
* Move object 
* If there is a collision with a solid object, send collision events
* If there is no collision with a solid object, we are free to move the object
* If the object is spectral, we can move it without bothering with checks
* Return 0 if we can move, otherwise return -1 if there is a collision with a solid object
*/
int df::WorldManager::moveObject(Object* p_o , Vector where){

	//first, check to see if the object is inside of the world.
	//This is necessary for us to only send one out event upon exiting
	bool initInbound = true;
	if(!GM.gameOver() && outOfBounds(p_o)){

		initInbound = false;
	}

	//Ensure the object is solid to enable collisions
	if(p_o->isSolid()){

		//get collision list and check to see if list is empty before proceeding
		ObjectList cList = getCollisions(p_o, where);
		if(!cList.isEmpty()){

			//We initially assume the object can move and prove it can move before actually moving it
			bool can_move = true;

			ObjectListIterator li(&cList);
			for (li.first(); !li.isDone(); li.next()) {
				Object* p_temp_o = li.currentObject();

				//Create collision event and send it to both objects
				EventCollision c(p_o, p_temp_o, where);
				p_o->eventHandler(&c);
				p_temp_o->eventHandler(&c);

				//if both objects are HARD, neither can move
				if(p_o->getSolidness() == HARD && p_temp_o->getSolidness() == HARD){
					can_move = false;
				}

				//If the object moving on has NO SOFT enabled and the receiving object is SOFT, neither can move
				if(p_o->getNoSoft() && p_temp_o->getSolidness() == SOFT){
					can_move = false;
				}
			}

			//If can_move has been set to false, return -1 to indicate a collision has been found and movement is impossible
			if(!can_move){
				return -1;
			}
		}
	}

	//If we have not found a collision, set the position and proceed as usual
	Box orig_box = getWorldBox(p_o, p_o->getPosition());
	p_o->setPosition(where);
	Box new_box = getWorldBox(p_o, p_o->getPosition());

	//If object moved from inside to outside world,
	//generate OOB event
	if (boxIntersectsBox(orig_box, boundary) && !boxIntersectsBox(new_box, boundary)) {
		EventOut ov = EventOut();
		Event* s = dynamic_cast<EventOut*>(&ov);
		p_o->eventHandler(s);
	}

	//if the view is following this object, adjust the view
	if (p_view_following == p_o) {
		setViewPosition(p_o->getPosition());
	}

	//check for out out bounds event
	//We use initInbound here to see if the object was in bounds before going out of bounds for the first time.
	if(!GM.gameOver() && initInbound && outOfBounds(p_o)){
		EventOut ov = EventOut();
		Event* s = dynamic_cast<EventOut*>(&ov);
		p_o->eventHandler(s);
	}


	return 0;
}

//set game world boundary
void df::WorldManager::setBoundary(Box new_boundary) {
	boundary = new_boundary;
}

//set game world boundary
df::Box df::WorldManager::getBoundary() const {
	return boundary;
}

//set game world view
void df::WorldManager::setView(Box new_view) {
	view = new_view;
}

//get game world view
df::Box df::WorldManager::getView() const {
	return view;
}

//Set view to center window in position view_pos
//View edge will not go beyond world boundary
void df::WorldManager::setViewPosition(Vector view_pos) {

	//Check to see if horizontal view is not out of world bounds
	float x = view_pos.getX() - view.getHorizontal() / 2;
	if (x + view.getHorizontal() > boundary.getHorizontal()) {
		x = boundary.getHorizontal() - view.getHorizontal();
	}
	if (x < 0) {
	   x = 0;
	}

	//Check to see if vertical view is not out of world bounds
	float y = view_pos.getY() - view.getVertical() / 2;
	if (y + view.getVertical() > boundary.getVertical()) {
		y = boundary.getVertical() - view.getVertical();
	}
	if (y < 0) {
		y = 0;
	}

	//Set view
	Vector new_corner(x, y);
	view.setCorner(new_corner);
	LM.writeLog("view position X: %f", getView().getCorner().getX());
	LM.writeLog("view position Y: %f", getView().getCorner().getY());

}

//Set view to cetner window on object
//Set to NULL to stop following
//If p_new_view_following not working, return -1
//return 0 on success
int df::WorldManager::setViewFollowing(Object* p_new_view_following) {

	//Set to null to turn off following
	if (p_new_view_following == NULL) {
		p_view_following = NULL;
		return 0;
	}

	//Iterate over all objects.
	bool found = false;
	ObjectList allObjects = m_updates;
	ObjectListIterator uli(&allObjects);
	for (uli.first(); !uli.isDone(); uli.next()) {
		if (uli.currentObject() == p_new_view_following) {
			found = true;
			break;
		}
	}

	//If we found the view, adjust the attribute accordingly and set view position
	if (found) {
		p_view_following = p_new_view_following;
		setViewPosition(p_view_following->getPosition());
		return 0;
	}


	//If we get here, something's up. Don't change the current view
	LM.writeLog("setViewFollowing ERROR: setViewFollowing was not found, are you sure it exists?");
	return -1;
}

/*
* Update world
* Delete objects marked for deletion
*/
void df::WorldManager::update() {

	if (!GM.gameOver()) {
		//Delete all marked objects
		df::ObjectList deleteList = m_deletions;
		df::ObjectListIterator dli(&deleteList);
		for (dli.first(); !dli.isDone(); dli.next()) {
			//Properly delete object later, for now we force C's hand
			delete dli.currentObject();
		}

		//Make objects update themselves
		df::ObjectList updateList = m_updates;
		ObjectListIterator uli(&updateList);
		for (uli.first(); !uli.isDone(); uli.next()) {
			uli.currentObject()->update();
		}

		//Move all objects (later)
		for (uli.first(); !uli.isDone(); uli.next()) {
			//Add velocity to position
			Vector new_pos = uli.currentObject()->predictPosition();

			//if moveObject succeeds, set the position of the current object
			int can_move = moveObject(uli.currentObject(), new_pos);
			if (can_move == 0) {
				uli.currentObject()->setPosition(new_pos);
			}
		}

		//Clear deletions list for next update phase
		m_deletions.clear();
	}
}


/*
* indicate an object is to be deleted at end of current game loop
* return 0 on success
* return -1 on fail
*/
int df::WorldManager::markForDelete(Object* p_o) {
	df::ObjectList list = m_deletions;
	df::ObjectListIterator li(&list);

	//Check to see if the object is already marked for deletion before flagging it
	for (li.first(); !li.isDone(); li.next()) {
		if (li.currentObject() == p_o) {
			return 0;
		}
	}

	//Add the object to the list, if we made it this far it's not inserted
	m_deletions.insert(p_o);

	//TODO: Fail state?
	return 0;
}

/*
* Draw all game world objects sequentially on a game step
*/
void df::WorldManager::draw() {
	//Get all game objects to draw them
	df::ObjectList list = m_updates;
	df::ObjectListIterator li(&list);

	//TODO: could be more efficient, come back later
	//Draw the object in order of altitude: lower objects get drawn first
	for (int alt = 0; alt <= df::MAX_ALTITUDE; alt++) {
		//draw every game object
		for (li.first(); !li.isDone(); li.next()) {
			if (li.currentObject()->getAltitude() == alt) {
				Object* p_temp_o = li.currentObject();
				p_temp_o->draw();
			}
		}
	}
}

//Other helper functions
bool outOfBounds(df::Object* p_o) {
	return (p_o->getPosition().getX() < 0 ||
		p_o->getPosition().getY() < 0 ||
		p_o->getPosition().getX() > WM.getBoundary().getHorizontal() ||
		p_o->getPosition().getY() > WM.getBoundary().getVertical());
}