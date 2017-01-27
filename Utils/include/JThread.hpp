//
// Created by vrosca on 12/21/16.
//

#ifndef MERSULTRENURILOR_JTHREAD_H
#define MERSULTRENURILOR_JTHREAD_H


#include <atomic>
#include <thread>
#include <vector>
/** Thread class with the same procedures as Java thread
 * This is an abstract class designed to be extended by other classes.
 * Once the thread starts, the run method is executed, so this
 * method should be implemented.
 */
class JThread {
    static std::atomic_int nr_threads;
    std::thread *proc;
    std::vector<std::function<void()> > observers;
    void notifyAll ();

public:
    void start (); ///
    void join ();
    void attach_lambda(std::function<void()> lambda);
    void detach ();

    virtual void run () = 0;
};


#endif //MERSULTRENURILOR_JTHREAD_H
