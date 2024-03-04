#include <stddef.h>

#include "raylib.h"
#include "library.h"

void StartTimer(Timer* timer, float lifetime) {
    if(timer != NULL) 
        timer->lifetime = lifetime;
}

void UpdateTimer(Timer* timer) {
    if(timer != NULL && timer->lifetime > 0)
        timer->lifetime -= GetFrameTime();
}

bool TimerDone(Timer* timer) {
    if(timer != NULL)
        return timer->lifetime <= 0;
    return false;
}

