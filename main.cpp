#include "Engine/Engine.h"
#include "LifeScreen.h"

#define FPS 60

Engine* GEngine = new Engine();

int main(int argc, char** argv) {
    float delta = 0.0;

    GEngine->Init();

    //Configures the game of life screen to be the active screen
    GEngine->SetActiveScreen(new class LifeScreen());

    double old_time = al_get_time();

    while (GEngine->ShouldTick()) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(GEngine->getEventQueue(), &ev);

        switch (ev.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                //Quit the game, close the window
                GEngine->Quit();
                break;
            case ALLEGRO_EVENT_TIMER:
                //Handle current tick functions
                GEngine->Tick(delta);
                break;
            default:
                //Handle any other forms of inputController
                GEngine->HandleInput(&ev);
        }

        if (GEngine->ShouldDraw() && al_event_queue_is_empty(GEngine->getEventQueue())) {
            //Get the change in time between two frames
            double new_time = al_get_time();
            delta = (float) (new_time - old_time);
            old_time = new_time;

            //Draw the current frame
            GEngine->Draw();
        }
    }

    GEngine->Kill();

    return 0;
}