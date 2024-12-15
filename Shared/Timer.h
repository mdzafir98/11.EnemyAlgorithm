#pragma once
#include <raylib.h>
#include <iostream>

struct Timer{
    float lifetime;
    void startTimer(Timer* timer, float lifetime);
    void updateTimer(Timer* timer);
    bool TimerDone(Timer* timer);
    float getTimer(Timer* timer);
};