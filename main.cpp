/******************************************************************************
 *	Name: Derek Ellis                                                         *
 *	Course: ICS4U                                                             *
 *	Date: Mar 24, 2017                                                        *
 *	                                                                          *
 *	Purpose: An RPN calculator program                                        *
 *	                                                                          *
 *	Usage: Compile and Run. Instructions are displayed in-game                *
 *	Revision History:                                                         *
 *	                                                                          *
 *	Known Issues:                                                             *
 *	                                                                          *
 ******************************************************************************/

#include "Engine/Engine.h"
#include "LifeScreen.h"
#include "RpnScreen.h"

Engine* GEngine = new Engine();

int main(int argc, char** argv) {
    GEngine->Init();

    // Configures the game of life screen to be the active screen
    GEngine->SetActiveScreen(new class RpnScreen(GEngine->GetDisplayWidth(), GEngine->GetDisplayHeight()));

    while (GEngine->ShouldDoTick()) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(GEngine->GetEventQueue(), &ev);

        // Handle the events coming from the event queue
        GEngine->HandleInput(&ev);

        // Only draw the next frame if all other events have been handled first
        if (GEngine->ShouldDraw() && al_event_queue_is_empty(GEngine->GetEventQueue())) {
            // Draw the current frame
            GEngine->Draw();
        }
    }

    // Cleanup memory
    GEngine->Kill();

    return 0;
}
