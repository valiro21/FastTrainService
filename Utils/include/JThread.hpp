//
// Created by vrosca on 12/21/16.
//

#ifndef MERSULTRENURILOR_JTHREAD_H
#define MERSULTRENURILOR_JTHREAD_H


#include <atomic>
#include <thread>
#include <vector>

class JThread {
    static std::atomic_int nr_threads;
    std::thread *proc;
    std::vector<std::function<void()> > observers;
    void notifyAll ();

public:
    void start ();
    void join ();
    void attach_lambda(std::function<void()> lambda);

    virtual void run () = 0;
};


#endif //MERSULTRENURILOR_JTHREAD_H
