//
// object.cpp
// 

//C includes
#include <string>

//Dragonfly includes
#include "LogManager.h"
#include "Object.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "EventStep.h"
#include "utility.h"


/*
* Construct object
* Set default parameters and add it to the game world (WM)
*/
df::Object::Object() {
	//Set default object parameters
	static int idCounter = 0;
	m_id = idCounter;
	m_position = Vector();
	m_direction = Vector();
	m_type = "default_type";
	m_altitude = 0;
	m_no_soft = false;
	m_speed = 1;

	//Increment id counter to allow for different variables
	idCounter += 1;

	//Add self to game world
	WM.insertObject(this);
}

/*
* Destroy object
* Remove it from the game world. (WM) it will not survive.
*/
df::Object::~Object() {
	WM.removeObject(this);
}

/*
*set object id
*/
void df::Object::setId(int new_id) {
	m_id = new_id;
}

/*
*get object id
*/
int df::Object::getId() const {
	return m_id;
}

//set object speed
void df::Object::setSpeed(float new_speed){
	m_speed = new_speed;
}

//get object speed
float df::Object::getSpeed() const{
	return m_speed;
}

/*
*set type identifier of object
*/
void df::Object::setType(std::string new_type) {
	m_type = new_type;
}

/*
*get type identifier of object
*/
std::string df::Object::getType() {
	return m_type;
}


/*
*set position of object
*/
void df::Object::setPosition(Vector new_pos) {
	m_position = new_pos;
}

/*
*get position of object
*/
df::Vector df::Object::getPosition() const {
	return m_position;
}

//set direction of object
void df::Object::setDirection(Vector new_direction) {
	m_direction = new_direction;
}

//get direction of object
df::Vector df::Object::getDirection() const{
	return m_direction;
}

//set velocity of object
//We set the velocity by changing the other aspects of the object directly affected by velocity:
//speed and direction
void df::Object::setVelocity(Vector new_velocity){
	//new direction
	Vector newDirection = new_velocity;
	newDirection.normalize();
	//LM.writeLog("new direction x: %f", newDirection.getX());
	//LM.writeLog("new direction y: %f", newDirection.getY());
	setDirection(newDirection);

	//new speed
	//LM.writeLog("new speed: %f", new_velocity.getMagnitude());
	float newSpeed = new_velocity.getMagnitude();
	setSpeed(newSpeed);

	//LM.writeLog("tester velocity x: %f", getVelocity().getX());
	//LM.writeLog("tester velocity y: %f", getVelocity().getY());
}

//get velocity of object
//Because velocity has no member, we use m_direction and get its scale.
df::Vector df::Object::getVelocity() const{
	Vector copyDirection = m_direction;
	copyDirection.scale(getSpeed());
	return copyDirection;
}

/*
* Predict object position based on speed and direction
* Return predicted position
*/
df::Vector df::Object::predictPosition(){
	//Add velocity to position
	Vector new_pos = m_position + getVelocity();

	//Return new position
	return new_pos;
}

/*
* Set altitude of object, with checks for range [0, MAX_ALTITUDE]
* Return 0 if successful, -1 if not
*/

int df::Object::setAltitude(int new_altitude) {
	if (new_altitude >= 0 && new_altitude <= df::MAX_ALTITUDE) {
		m_altitude = new_altitude;
		return 0;
	}
	LM.writeLog("ERROR: Set altitude is outside of altitude range.");
	LM.writeLog("ERROR: Please keep your altitude within a range of 0-%d.", df::MAX_ALTITUDE);
	return -1;
}

/*
* Return altitude of object
*/
int df::Object::getAltitude() const {
	return m_altitude;
}

//True if hard or soft
//False is spectral or undefined
bool df::Object::isSolid() const{
	if(getSolidness() == HARD || getSolidness() == SOFT){
		return true;
	} else {
		return false;
	}
}

// Set object solidness, with checks for consistency
// Return 0 if ok, -1 if not
int df::Object::setSolidness(Solidness new_solid){
	if (new_solid == df::SPECTRAL || new_solid == df::HARD || new_solid == df::SOFT) {
		m_solidness = new_solid;
		return 0;
	}
	else {
		LM.writeLog("Your solid type is not supported. Please enter df::HARD, df::SPECTRAL, or df::SOFT.");
		return -1;
	}
	
}

//Return object solidness
df::Solidness df::Object::getSolidness() const{
	return m_solidness;
}

//Set objects that cannot move onto soft objects
void df::Object::setNoSoft (bool new_no_soft){
	m_no_soft = new_no_soft;
}

//Get an object's "no-soft" setting that stops it from moving onto soft objects
bool df::Object::getNoSoft() const{
	return m_no_soft;
}

/*
* Handle event (default is to ignore everything)
* Return 0 if ignored
* Return 1 if handled
*/
int df::Object::eventHandler(const df::Event* p_e) {
	return 0;
}

/*
* Set sprite for this object to animate
* Return 0 if ok, return -1 on fail
*/
int df::Object::setSprite(std::string sprite_label) {
	Sprite* p_temp_sprite = RM.getSprite(sprite_label);

	//Error handling in case the sprite is null
	if (p_temp_sprite == NULL) {
		LM.writeLog("setSprite ERROR: sprite could not be found using label %s", sprite_label.c_str());
		return -1;
	}

	//If the sprite exists, set it as usual
	m_animation.setSprite(p_temp_sprite);

	//set collision bounding box to object
	setBox(m_animation.getBox());
	return 0;
}

/*
* Set animation for this object to a new one
* Set bounding box to size of associated sprite
*/
void df::Object::setAnimation(Animation new_animation) {
	m_animation = new_animation;
}

/*
* Gets the animation for object
*/
df::Animation df::Object::getAnimation() const {
	return m_animation;
}

//set object's bounding box
void df::Object::setBox(Box new_box) {
	m_box = new_box;
}

//get object's bounding box
df::Box df::Object::getBox() const {
	return m_box;
}


/*
* Update object behavior in world
*/
void df::Object::update() {
	//predict position function?

}

/*
* draws object in world
* Overriden by all game objects that use this function
*/
int df::Object::draw() {
	//df::Vector worldPosition = viewToWorld(getPosition());
	return m_animation.draw(getPosition());
}