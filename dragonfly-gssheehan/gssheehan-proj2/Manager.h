#pragma once
//
//manager.h
//

//C includes
#include <string>

//Dragonfly includes
#include "Event.h"

//conditional compilation
#ifndef MANAGER_H_SEEN
#define MANAGER_H_SEEN


//Managers are support systems for game engines and handling crucial tasks
//Different types of managers are broken up into different functions
//This class, MANAGER, serves as a base class for all derived managers
namespace df {

	class Manager {
	private:
		std::string m_type; //Manager type identifier
		bool m_is_started; //bool that checks if manager is started

	protected:
		//Set type identifier of Manager
		//void setType(std::string type);

	public:
		//constructor and destructor
		Manager();
		virtual ~Manager();

		//Get type identifier of manager
		std::string getType() const;

		//Startup manager
		//Return:
		//	0 on successful startup
		//	-1 un unsuccessful startup
		virtual int startUp();

		//Shutdown manager
		virtual void shutDown();

		//sends an event to every object in the game world
		virtual int onEvent(const Event *p_event) const;

		//Return:
		//	true on successful startup
		//	false on unsuccessful startup
		bool isStarted() const;
	};
} 

#endif

