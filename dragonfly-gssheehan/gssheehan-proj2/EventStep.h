#pragma once
//
//eventstep.h
//

//C includes
#include <string>

//Dragonfly includes
#include "Event.h"

//conditional compilation
#ifndef EVENTSTEP_H_SEEN
#define EVENTSTEP_H_SEEN

namespace df {

	//String to be passed as type
	const std::string STEP_EVENT = "df::step";

	class EventStep : public Event {
	private:
		//Iteration number of game loop
		int m_step_count;
	public:
		//default constructor
		EventStep();

		//Constructor with initial step count
		EventStep(int init_step_count);

		//set step count
		void setStepCount(int new_step_count);

		//get step count
		int getStepCount() const;
	};
}

#endif