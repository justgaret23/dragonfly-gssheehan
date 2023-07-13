#pragma once
//
//eventout.h
//

//Dragonfly includes
#include "Event.h"

namespace df {
    const std::string OUT_EVENT = "df::out";

    class EventOut : public Event {
    public:
        //constructor
        EventOut();
    };
}