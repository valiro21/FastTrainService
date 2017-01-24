//
// Created by vrosca on 1/24/17.
//

#ifndef FASTTRAINSERVICE_DATABASE_TESTS_HPP
#define FASTTRAINSERVICE_DATABASE_TESTS_HPP

#include <gtest/gtest.h>
#include <DatabaseManager.hpp>

class DatabaseTests : public ::testing::Test {
protected:
    bool not_initialized;
    DatabaseManager* manager;

    virtual void SetUp () {
        manager = &DatabaseManager::GetInstance();
        not_initialized = manager->init() != EXIT_SUCCESS;
    }

    virtual void TearDown () {
        manager = NULL;
    }
};

#endif //FASTTRAINSERVICE_DATABASE_TESTS_HPP
