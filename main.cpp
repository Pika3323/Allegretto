/******************************************************************************
 *	Name: Derek Ellis                                                         *
 *	Course: ICS4U                                                             *
 *	Date: Feb 22, 2017                                                        *
 *	                                                                          *
 *	Purpose: An implementation of Conway's Game of Life                       *
 *	                                                                          *
 *	Usage: Compile and Run. Instructions are displayed in-game                *
 *	       All game logic is held in the LifeScreen.h and LifeScreen.cpp files*
 *	Revision History:                                                         *
 *	                                                                          *
 *	Known Issues:                                                             *
 *	                                                                          *
 ******************************************************************************/

#include "Engine/Engine.h"
#include "LifeScreen.h"

#define FPS 60

Engine* GEngine = new Engine();

int main(int argc, char** argv) {
    GEngine->Init();

    // Configures the game of life screen to be the active screen
    GEngine->SetActiveScreen(new class LifeScreen(GEngine->getDisplayWidth(), GEngine->getDisplayHeight()));

    while (GEngine->ShouldTick()) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(GEngine->getEventQueue(), &ev);

        // Handle the events coming from the event queue
        GEngine->HandleInput(&ev);

        // Only draw the next frame if all other events have been handled first
        if (GEngine->ShouldDraw() && al_event_queue_is_empty(GEngine->getEventQueue())) {
            // Draw the current frame
            GEngine->Draw();
        }
    }

    // Cleanup memory
    GEngine->Kill();

    return 0;
}