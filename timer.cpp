#include "timer.h"

LTimer::LTimer(){
    //Initialize the variables
    mStartTicks = 0;
    mPausedTicks = 0;

    mPaused = false;
    mStarted = false;
}

void LTimer::start(){
    mStarted = true;	//Start the timer
    mPaused = false;	//Unpause the timer

    //Get the current clock time
    mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void LTimer::stop(){
    mStarted = false;	//Stop the timer
    mPaused = false;	//Unpause the timer

	//Clear tick variables
	mStartTicks = 0;
	mPausedTicks = 0;
}

void LTimer::pause(){
    //If the timer is running and isn't already paused
    if( mStarted && !mPaused ){
        mPaused = true;	//Pause the timer
        mPausedTicks = SDL_GetTicks();	//Calculate the paused ticks
    }
}

void LTimer::unpause(){
    //If the timer is running and paused
    if( mStarted && mPaused ){
        mPaused = false;	//Unpause the timer
        mStartTicks += SDL_GetTicks() - mPausedTicks;	//Reset the starting ticks
        mPausedTicks = 0;	//Reset the paused ticks
    }
}

Uint32 LTimer::getTicks(){
	Uint32 time = 0;	//The actual timer time

    //If the timer is running
    if( mStarted ){
        //If the timer is paused
        if( mPaused )	time = mPausedTicks-mStartTicks;	//Return the number of ticks when the timer was paused
        else	time = SDL_GetTicks() - mStartTicks;	//Return the current time minus the start time
    }
    return time;
}

bool LTimer::isStarted(){
    return mStarted;	//Timer is running and paused or unpaused
}

bool LTimer::isPaused(){
    return mPaused && mStarted;	//Timer is running and paused
}