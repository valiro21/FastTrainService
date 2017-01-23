//
// Created by vrosca on 1/12/17.
//

#ifndef FASTTRAINSERVICE_LAMBDATHREAD_HPP
#define FASTTRAINSERVICE_LAMBDATHREAD_HPP


#include <functional>
#include <JThread.hpp>

class LambdaThread : public JThread{
protected:
    std::function<void(void)> internal_lambda;
public:
    LambdaThread (std::function<void(void)> lambda);
    void run ();
};


#endif //FASTTRAINSERVICE_LAMBDATHREAD_HPP
