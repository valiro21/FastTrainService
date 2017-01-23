//
// Created by vrosca on 12/21/16.
//

#ifndef MERSULTRENURILOR_THREADPOOL_H
#define MERSULTRENURILOR_THREADPOOL_H


#include <atomic>
#include <mutex>
#include <vector>
#include <queue>
#include <future>
#include "JThread.hpp"
#include "LambdaThread.hpp"

class RequestsPool {
    int limit;
    std::atomic_int active;
    std::vector<LambdaThread*> running_jobs;
    std::queue<LambdaThread*> waiting_jobs;
    std::mutex waiting_jobs_mutex, running_jobs_mutex;

    static RequestsPool *singleton;
    RequestsPool () {active = 0;}
    void remove (LambdaThread *thread);

public:
    static RequestsPool& GetInstance ();

    void setLimit (int number);

    void execute (std::function<void(void)> task);
};


#endif //MERSULTRENURILOR_THREADPOOL_H
