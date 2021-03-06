//
// Created by vrosca on 1/12/17.
//

#ifndef FASTTRAINSERVICE_SCHEDULETHREAD_HPP
#define FASTTRAINSERVICE_SCHEDULETHREAD_HPP


#include "LambdaThread.hpp"
#include <functional>
/** Executes a task at regular intervals.
 *  After delay execute task until canceled. Waits for interval number of
 *  milliseconds.
 */
class ScheduleThread : public LambdaThread {
    unsigned int delay, interval;
    bool canceled;
public:
    ScheduleThread (std::function<void(void)> lambda, unsigned int delay, unsigned int interval);
    void run ();
    void cancel ();
};


#endif //FASTTRAINSERVICE_SCHEDULETHREAD_HPP
