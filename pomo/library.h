#ifndef LIBRARY_H
#define LIBRARY_H

typedef struct {
    float lifetime;
} Timer;

void StartTimer(Timer* timer, float lifetime);
void UpdateTimer(Timer* timer);
bool TimerDone(Timer* timer);

#endif // LIBRARY_H
