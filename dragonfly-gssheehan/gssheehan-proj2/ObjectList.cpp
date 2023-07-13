//
//objectlist.cpp
// 

//Dragonfly includes
#include "ObjectList.h"
#include "LogManager.h"


//constructor
df::ObjectList::ObjectList() {
	m_count = 0;

}

/*
* insert object pointer in list
* Return 0 if successful
* Return -1 if not
*/
int df::ObjectList::insert(Object* p_o) {
	//LM.writeLog("item count: %d", m_count);
	if (!isFull()) {
		//m_count points to the next array element that needs filling, increment afterwards
		m_p_obj[m_count] = p_o;
		m_count++;
		return 0;
	}
	else {
		LM.writeLog("Object insertion failed! Max object capacity has been reached...");
		return -1;
	}
	
}

/*
* remove object pointer in list
* Return 0 if successful
* Return -1 if not
*/
int df::ObjectList::remove(Object* p_o) {
	if (!isEmpty()) {
		//Iterate through the object list until we find the requested object
		for (int objectIndex = 0; objectIndex < m_count; objectIndex++) {
			//Upon finding a match, we shift the rest of the array over to cover up the removed object
			if (m_p_obj[objectIndex] = p_o) {
				for (int moveIndex = objectIndex; moveIndex < m_count - 1; moveIndex++) {
					m_p_obj[moveIndex] = m_p_obj[moveIndex + 1];
				}
				m_count--;
				return 0;
			}
		}
		LM.writeLog("Object removal failed! The requested object could not be found...");
		return -1;
	}
	else {
		LM.writeLog("Object removal failed! The object list is empty...");
		return -1;
	}
	
}

/*
* Set the count to zero, stopping the iterator from seeing any of the list.
* The list still exists, but that doesn't matter because we can't access it
*/
void df::ObjectList::clear() {
	m_count = 0;
}

/*
* Return the number of objects currently in the list
*/
int df::ObjectList::getcount() const {
	if (this == NULL) {
		LM.writeLog("Object list is null, cannot get count");
		return -1;
	}
	return m_count;
}

/*
* Return true if the list is empty (count is zero)
* Return false otherwise
*/
bool df::ObjectList::isEmpty() const {
	if (m_count == 0) {
		return true;
	}
	else {
		return false;
	}
	
}

/*
* Return true if the list is full (count is max objects)
* Return false otherwise
*/
bool df::ObjectList::isFull() const {
	if (m_count < MAX_OBJECTS) {
		return false;
	}
	else {
		return true;
	}
	
}

/*
* Operator that adds two lists together
*/
df::ObjectList df::ObjectList::operator+(df::ObjectList list) {

	//Initialize the first list as a beeg list
	df::ObjectList big_list = *this;
	
	//Iterate through the second list, adding each element as we go
	df::ObjectListIterator li(&list);
	for (li.first(); not li.isDone(); li.next()) {
		df::Object* p_o = li.currentObject();
		big_list.insert(p_o);
	}

	//Return combined list
	return big_list;
}
