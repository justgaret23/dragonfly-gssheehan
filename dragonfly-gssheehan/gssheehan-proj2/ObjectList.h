#pragma once
//
//objectlist.h
// 

//conditional compilation
#ifndef OBJECTLIST_H_SEEN
#define OBJECTLIST_H_SEEN

//Dragonfly includes
#include "Object.h"
#include "ObjectListIterator.h"

 
namespace df {
	const int MAX_OBJECTS = 1000;

	//Guarantees compilation independent of include files
	class ObjectListIterator;
	class ObjectList {
	private:
		int m_count; //number of objects in list
		Object* m_p_obj[MAX_OBJECTS]; //Array of pointer to objects
	public:
		friend class ObjectListIterator;

		//default constructor
		ObjectList();

		//insert object pointer in list
		//Return 0 if successful
		//Return -1 if not
		int insert(Object* p_o);

		//remove object pointer in list
		//Return 0 if successful
		//Return -1 if not
		int remove(Object* p_o);

		//clear list, setting the count to zero in the process
		void clear();

		//Return the number of objects currently in the list
		int getcount() const;

		//Return true if the list is empty (count is zero)
		//Return false otherwise
		bool isEmpty() const;

		//Return true if the list is full (count is max objects)
		//Return false otherwise
		bool isFull() const;

		//Operator that adds two lists together
		ObjectList operator+(ObjectList list);
	};
}

#endif
