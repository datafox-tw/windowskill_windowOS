#pragma once
#ifndef TIMER_h
#define TIMER_H
#include "SDL2/SDL.h" 

//The application time based timer
class LTimer{
    public:
		LTimer();	//Initializes variables

		//The various clock actions
		void start();
		void stop();
		void pause();
		void unpause();

		Uint32 getTicks();	//Gets the timer's time

		//Checks the status of the timer
		bool isStarted();
		bool isPaused();

    private:
		Uint32 mStartTicks;	//The clock time when the timer started
		Uint32 mPausedTicks;	//The ticks stored when the timer was paused

		//The timer status
		bool mPaused;
		bool mStarted;
};

#endif