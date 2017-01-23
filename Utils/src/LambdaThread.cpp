//
// Created by vrosca on 1/12/17.
//

#include "LambdaThread.hpp"

LambdaThread::LambdaThread (std::function<void(void)> lambda) {
    internal_lambda = lambda;
}
void LambdaThread::run () {
    internal_lambda ();
}