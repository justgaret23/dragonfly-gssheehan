#pragma once
//
//inputmanager.h
//

#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

//Dragonfly includes
#include "Manager.h"

# define IM df :: InputManager :: getInstance ()

namespace df {
	class InputManager : Manager {
	private:
		//singleton
		InputManager(); //private constructor
		InputManager(InputManager const&); //no copy!
		void operator=(InputManager const&); //no assign!
	public:

		//get singleton instance of inputmanager
		static InputManager& getInstance();

		//get window ready to capture input
		//Return 0 if success, -1 if fail
		int startUp();

		//Revert back to normal window mode
		void shutDown();

		//Get input from the keyboard and mouse
		//Pass event along to all objects
		void getInput();

	};
}

#endif