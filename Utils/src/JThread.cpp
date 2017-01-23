//
// Created by vrosca on 12/21/16.
//

#include "JThread.hpp"

std::atomic_int JThread::nr_threads{0};

void JThread::join () {
    if (proc->joinable())
        proc->join();
}

void JThread::start () {
    nr_threads++;
    proc = new std::thread ([this](){run();notifyAll();});
}

void JThread::attach_lambda(std::function<void()> lambda) {
    observers.push_back (lambda);
}

void JThread::notifyAll () {
    for (auto i : observers) {
        i();
    }
}