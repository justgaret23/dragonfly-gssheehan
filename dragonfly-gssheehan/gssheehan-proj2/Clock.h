#pragma once
//
//clock.h
//

#ifndef CLOCK_H_SEEN
#define CLOCK_H_SEEN

namespace df {
	class Clock {
	private:
		long int previous_time;
	public:
		Clock();

		//Return time elapsed since delta was last called
		//Reset previous time
		//return -1 on error, units are microseconds
		long int delta(void);

		//Return time elapsed since delta was last called. 
		//Does not reset previous time
		//units are microseconds
		long int split(void) const;
	};
}

#endif
