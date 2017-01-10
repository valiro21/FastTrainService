//
// Created by vrosca on 12/21/16.
//

#include <algorithm>
#include "RequestsPool.hpp"
#include "Server/Requests/RequestTaskFactory.hpp"
#include "Logger.hpp"
#include "Utils.hpp"

RequestsPool* RequestsPool::singleton = NULL;

void RequestsPool::execute (std::string request, std::function<void(std::string)> callback) {
    Logger::GetInstance().logd(request + " in pool");
    RequestWorker *worker;

    json json_request;
    try {
        json_request = json::parse(request);
         worker = new RequestWorker(json_request,
                                                  callback,
                                                  RequestTaskFactory::GetInstance().getTask(json_request));
    }
    catch (std::invalid_argument &e) {
        Logger::GetInstance().logd ("Request parse error: " + std::string(e.what()));
        callback(Utils::GetInstance().getErrorJSONString ("Invalid JSON format!"));
        return;
    }
    catch (std::domain_error &e) {
        Logger::GetInstance().logd ("Request parse error: " + std::string(e.what()));
        callback(Utils::GetInstance().getErrorJSONString ("Invalid action format!"));
        return;
    }
    catch (std::exception *e) {
        Logger::GetInstance().logd("Request parse error: " + std::string(e->what()));
        callback(Utils::GetInstance().getErrorJSONString ("Unknown error!"));
        return;
    }
    worker->attach_lambda([this, worker](){this->remove(worker);});

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

void RequestsPool::remove (RequestWorker *thread) {
    running_jobs_mutex.lock ();
    auto pos = std::find (running_jobs.begin(), running_jobs.end(), thread);
    if (pos != running_jobs.end())
        running_jobs.erase (pos);
    running_jobs_mutex.unlock ();

    waiting_jobs_mutex.lock ();
    if (!waiting_jobs.empty ()) {
        RequestWorker *next_worker = waiting_jobs.front ();
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