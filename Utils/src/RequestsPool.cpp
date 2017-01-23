//
// Created by vrosca on 12/21/16.
//

#include <algorithm>
#include "RequestsPool.hpp"
#include "Utils.hpp"

RequestsPool* RequestsPool::singleton = NULL;

void RequestsPool::execute (std::function<void(void)> task) {
    LambdaThread *worker = new LambdaThread(task);

    worker->attach_lambda([&](){this->remove(worker);});

    if (active < limit) {
        running_jobs_mutex.lock ();
        running_jobs.push_back (worker);
        running_jobs_mutex.unlock ();
        worker->start ();
    }
    else {
        waiting_jobs_mutex.lock ();
        waiting_jobs.push (worker);
        waiting_jobs_mutex.unlock ();
    }
}

void RequestsPool::remove (LambdaThread *thread) {
    running_jobs_mutex.lock ();
    auto pos = std::find (running_jobs.begin(), running_jobs.end(), thread);
    if (pos != running_jobs.end())
        running_jobs.erase (pos);
    running_jobs_mutex.unlock ();

    waiting_jobs_mutex.lock ();
    if (!waiting_jobs.empty ()) {
        LambdaThread *next_worker = waiting_jobs.front ();
        waiting_jobs.pop ();
        next_worker->run ();

        running_jobs_mutex.lock ();
        running_jobs.push_back (next_worker);
        running_jobs_mutex.unlock ();
    }
    waiting_jobs_mutex.unlock ();
}

RequestsPool& RequestsPool::GetInstance () {
    if (singleton == nullptr) {
        singleton = new RequestsPool ();
        singleton->setLimit (20);
    }
    return *singleton;
}

void RequestsPool::setLimit (int number) {
    this->limit = number;
}