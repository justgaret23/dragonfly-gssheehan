//
//logmanager.cpp
//

//C includes
#define _CRT_SECURE_NO_DEPRECATE
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

//Dragonfly includes
#include "LogManager.h"
#include "utility.h"


//Singleton instance
df::LogManager& df::LogManager::getInstance() {
	//A static variable persists after the method ends
	static LogManager single;
	return single;
}

//constructor
df::LogManager::LogManager() {
	m_do_flush = false;
	m_p_f = NULL;
	LOGFILE_NAME = "dragonfly.log";
}

//destructor
df::LogManager::~LogManager() {

}

/*
* Start up log manager
*/
int df::LogManager::startUp() {
	m_p_f = fopen(LOGFILE_NAME, "w");

	//Detect to see if the file was not opened properly
	if(m_p_f == NULL){
		printf("The LogManager did not start successfully...\n");
		return -1;
	}
	
	return 0;
}

/*
* Shut down the log manager, closing the file in the process
*/
void df::LogManager::shutDown() {
	//print out getTimeString beforehand
	fprintf(m_p_f, getTimeString());
	fprintf(m_p_f, " ");
	fprintf(m_p_f, "Log Manager shutting down...");
	fclose(m_p_f);
}

/*
* set flush of logfile after each write
*/
void df::LogManager::setFlush(bool do_flush) {
	//If the file has not been flushed, flush the file.
	//TODO: flush file
	if (!do_flush) {
		fflush(m_p_f);
	}
}

/*
* Write to the logfile. support printf formatting
* Return number of bytes written. If error, return 1;
*/
int df::LogManager::writeLog(const char* fmt, ...) const {
	const std::string dataType = fmt;
	int fmtCount = 0;
	int totalBytes = 0;

	//print out getTimeString beforehand
	fprintf(m_p_f, getTimeString());
	fprintf(m_p_f, " ");

	//Create a va_list and write the string to the log file in printf fashion using vfprintf
	va_list args;
	va_start(args, fmt);
	totalBytes += vfprintf(m_p_f, fmt, args);
	va_end(args);

	fprintf(m_p_f, "\n");


	
	return totalBytes;
}