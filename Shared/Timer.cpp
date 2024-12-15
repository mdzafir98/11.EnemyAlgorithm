#include "Timer.h"

void Timer::startTimer(Timer *timer, float lifetime)
{
    if (timer != nullptr){
        timer->lifetime = lifetime;
    }
}

void Timer::updateTimer(Timer *timer)
{
    if (timer != nullptr && timer->lifetime>0){
        timer->lifetime -= GetFrameTime();
    }
    // std::cout << "timer: " << timer->lifetime << "\n";
}

bool Timer::TimerDone(Timer *timer)
{
    if (timer != nullptr){
        return timer->lifetime <=0;
    }
    return false;
}

float Timer::getTimer(Timer* timer)
{
    return timer->lifetime;
}
