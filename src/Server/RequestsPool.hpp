//
// Created by vrosca on 12/21/16.
//

#ifndef MERSULTRENURILOR_THREADPOOL_H
#define MERSULTRENURILOR_THREADPOOL_H


#include <atomic>
#include <mutex>
#include <vector>
#include <queue>
#include "JThread.hpp"
#include "RequestWorker.hpp"

class RequestsPool {
    int limit;
    std::atomic_int active;
    std::vector<RequestWorker*> running_jobs;
    std::queue<RequestWorker*> waiting_jobs;
    std::mutex waiting_jobs_mutex, running_jobs_mutex;

    static RequestsPool *singleton;
    RequestsPool () {active = 0;}

public:
    static RequestsPool& GetInstance ();

    void setLimit (int number);

    void remove (RequestWorker *thread);
    void execute (std::string request, std::function<void(std::string)> callback);
};


#endif //MERSULTRENURILOR_THREADPOOL_H
