//
// Created by vrosca on 12/21/16.
//

#include "RequestWorker.hpp"

void RequestWorker::run() {
    callback (task->solve (request));
}