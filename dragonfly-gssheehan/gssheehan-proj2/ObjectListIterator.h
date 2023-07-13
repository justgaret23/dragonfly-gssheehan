#pragma once
//
//objectlistiterator.h
// 

//conditional compilation
#ifndef OBJECTLISTITERATOR_H_SEEN
#define OBJECTLISTITERATOR_H_SEEN

#include "Object.h"
#include "ObjectList.h"


namespace df {
	class ObjectList;
	class ObjectListIterator {
	private:
		ObjectListIterator(); //must be given list when created
		int m_index; //current index in list
		const ObjectList* m_p_list; //pointer of list being iterated over
	public:
		ObjectListIterator(ObjectList* p_l);

		//set iterator to the first item in the list
		void first();        

		//set iterator to next item in the list
		void next();         

		//return true if at the end of the list
		bool isDone() const; 

		//Return pointer to current object
		//NULL if done/empty
		Object* currentObject() const;
	};
}

#endif
