//
// Created by vrosca on 1/12/17.
//

#include "ScheduleThread.hpp"

ScheduleThread::ScheduleThread (std::function<void(void)> lambda, unsigned int delay, unsigned int interval) : LambdaThread(lambda) {
    this->delay = delay;
    this->interval = interval;
    this->canceled = false;
}

void ScheduleThread::run () {
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    while (!canceled) {
        this->internal_lambda();
        std::this_thread::sleep_for(std::chrono::milliseconds(this->interval));
    }
}

void ScheduleThread::cancel () {
    canceled = true;
}