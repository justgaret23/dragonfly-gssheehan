#pragma once
//
//eventcollision.h
//

//Dragonfly includes
#include "Event.h"
#include "Object.h"

namespace df{
    const std :: string COLLISION_EVENT = "df::collision";

    class EventCollision: public Event {
    private:
        Vector m_pos ; // Where collision occured.
        Object * m_p_obj1 ; // Moving object causing collision.
        Object * m_p_obj2 ; // Object being collided with.
    public:
        //constructor - create collision event at (0,0) with 01 and 02 null
        EventCollision();

        // Create collision event between objects 1 and 2 and position p
        // Object o1 initiated collision by moving into object 2
        EventCollision ( Object* p_o1 , Object* p_o2 , Vector p ) ;

        //set object that caused collision
        void setObject1 ( Object* p_new_o1 );

        //return object that caused collision
        Object* getObject1 () const ;
                
        //set the object that was collided with
        void setObject2 ( Object* p_new_o2 ) ;

        //Return object that was collided with
        Object* getObject2 () const ;

        //Set collision position
        void setPosition ( Vector new_pos ) ;

        //Return collision position
        Vector getPosition () const ;
    };
}