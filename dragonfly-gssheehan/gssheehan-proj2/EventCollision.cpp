//
//eventcollision.cpp
//

//Dragonfly includes
#include "EventCollision.h"


//constructor - create collision event at (0,0) with 01 and 02 null
df::EventCollision::EventCollision(){
    m_pos = Vector();
    m_p_obj1 = NULL;
    m_p_obj2 = NULL;
    setType(df::COLLISION_EVENT);
}

/*
* Create collision event between objects 1 and 2 and position p
* Object o1 initiated collision by moving into object 2
*/
df::EventCollision::EventCollision ( Object* p_o1 , Object* p_o2 , Vector p ) {
    m_pos = p;
    m_p_obj1 = p_o1;
    m_p_obj2 = p_o2;
    setType(df::COLLISION_EVENT);
}

/*
* set object that caused collision
*/
void df::EventCollision::setObject1 ( Object* p_new_o1 ){
    m_p_obj1 = p_new_o1;
}

/*
* get object that caused collision
*/
df::Object* df::EventCollision::getObject1 () const {
    return m_p_obj1;
}
        
/*
* set the object that was collided with
*/
void df::EventCollision::setObject2 ( Object* p_new_o2 ) {
    m_p_obj2 = p_new_o2;
}

/*
* get the object that was collided with
*/
df::Object* df::EventCollision::getObject2 () const {
    return m_p_obj2;
}

/*
* Set collision position
*/
void df::EventCollision::setPosition ( Vector new_pos ) {
    m_pos = new_pos;
}

/*
* Get collision position
*/
df::Vector df::EventCollision::getPosition () const {
    return m_pos;
}