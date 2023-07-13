//
//logmanager.h
//

#ifndef __LOG_MANAGER_H__
#define __LOG_MANAGER_H__

//C includes
#include <stdio.h>

//Dragonfly includes
#include "Manager.h"

# define LM df :: LogManager :: getInstance ()


namespace df {
	//Singleton LogManager
	
	class LogManager : public Manager {
	private:
		//Singleton attributes
		LogManager(); //No constructing
		LogManager(LogManager const& copy); //No copying
		void operator=(LogManager const& assign); //No assigning

		const char* LOGFILE_NAME;
		//Other attributes
		bool m_do_flush; //true if fflush occurs after each write to dragonfly.log
		FILE* m_p_f; //pointer to logfile 

	public:
		//Singleton methods
		~LogManager(); //log manager destructor - close logfile if open
		static LogManager &getInstance(); //return instance

		//Other methods
		//Start up the log manager, opening logfile (dragonfly.log)
		int startUp();

		//Shut down log manager (close the logfile)
		void shutDown();

		//set flush of logfile after each write
		void setFlush(bool do_flush = true);

		//Write to the logfile. support printf formatting
		//return number of bytes written, -1 if error
		int writeLog(const char* fmt, ...) const;
	};
}
#endif