//
//objectlistiterator.cpp
// 

//Dragonfly includes
#include "Object.h"
#include "ObjectListIterator.h"


//constructor
df::ObjectListIterator::ObjectListIterator(df::ObjectList* p_l) {
    m_p_list = p_l;
    m_index = 0;
    m_p_list = p_l;
}

/*
* set iterator to the first item in the list
*/
void df::ObjectListIterator::first(){
    m_index = 0;
}

/*
* set iterator to the next item in the list
*/
void df::ObjectListIterator::next(){
    //If we're not at the end of the list, get the count
    if (m_index < m_p_list->getcount()) {
        m_index++;
    }
}

/*
* return true if at the end of the list
*/
bool df::ObjectListIterator::isDone() const{
    if (m_index == m_p_list->getcount()) {
        return true;
    }
    else {
        return false;
    }
}


/*
* Return pointer to current object
* NULL if done/empty
*/
df::Object* df::ObjectListIterator::currentObject() const {
    return m_p_list->m_p_obj[m_index];
}