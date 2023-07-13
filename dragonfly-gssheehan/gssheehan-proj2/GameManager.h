#pragma once
//
//gamemanager.h
//

//Dragonfly includes
#include "Manager.h"

//conditional compilation
#ifndef GAMEMANAGER_H_SEEN
#define GAMEMANAGER_H_SEEN

const int FRAME_TIME_DEFAULT = 33;

# define GM df :: GameManager :: getInstance ()

namespace df {
	class GameManager : public Manager {
	private:
		//Singleton attributes
		GameManager(); //private because it's a singleton
		GameManager(GameManager const&); //no copy!
		void operator=(GameManager const&); //no assignment!

		//other attributes
		bool game_over; //if it's true, the game should stop
		int frame_time; //target time per game loop, in milliseconds
	public: 

		//Get singleton instance of GameManager
		static GameManager& getInstance();

		//Startup all GameManager services
		int startUp();

		//Shut down all GameManager services
		void shutDown();

		//Run game loop
		void run();

		//Set game over status to indicated value
		//If true, will stop game loop
		void setGameOver(bool new_game_over = true);

		//Get game over status
		bool gameOver() const;

		//Return frame time
		//Frame time is target time for game loop, in ms
		int getFrameTime() const;
	};
}

#endif
