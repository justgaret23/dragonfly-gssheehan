#pragma once
//
//event.h
//

//conditional compilation
#ifndef EVENT_H_SEEN
#define EVENT_H_SEEN

//C includes
#include <string>

const std::string UNDEFINED_EVENT = "df::undefined";

namespace df {

	class Event {
	private:
		std::string m_event_type;
	public:
		//base event
		Event();

		//destructor
		virtual ~Event();

		//set event type
		void setType(std::string new_type);

		//get event type
		std::string getType() const;
	};
}

#endif