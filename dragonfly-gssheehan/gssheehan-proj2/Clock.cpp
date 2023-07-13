//
//clock.cpp
//

//C includes
#include <Windows.h>

//Dragonfly includes
#include "Clock.h"

//Stubs
long int currentSystemTime();


//constructor
df::Clock::Clock() {
	//compute start time in microseconds
	long int start_msec = currentSystemTime();
	previous_time = start_msec;
}

/*
* Return time elapsed since delta was last called
* Reset previous time
* Return -1 on error, units are microseconds
*/
long int df::Clock::delta() {
	//Get current time in system and microseconds
	long int delta_msec = currentSystemTime();

	//Calculate current elapsed time
	long int elapsed_time = delta_msec - previous_time;

	//Reset previous time
	previous_time = delta_msec;

	return elapsed_time;
}

/*
* Return time elapsed since delta was last called
* Does not reset previous time
* Return -1 on error, units are microseconds
*/
long int df::Clock::split() const {
	//Get current time in system and microseconds
	long int split_msec = currentSystemTime();

	//Calculate current elapsed time
	long int elapsed_time = split_msec - previous_time;

	return elapsed_time;
}

/*
* Helper function that calculates the current system time
*/
long int currentSystemTime() {
	//Get current time as a SYSTEMTIME
	SYSTEMTIME current_st;
	GetSystemTime(&current_st);

	//compute and return start time in microseconds
	long int current_msec = (current_st.wDay * 24 * 60 * 60 * 1000000)
		+ (current_st.wHour * 60 * 60 * 1000000)
		+ (current_st.wMinute * 60 * 1000000)
		+ (current_st.wSecond * 1000000)
		+ (current_st.wMilliseconds * 1000);

	return current_msec;
}
