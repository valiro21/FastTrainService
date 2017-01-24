//
// Created by vrosca on 1/21/17.
//

#include <gtest/gtest.h>
#include "database_tests.hpp"
#include <ProviderFactory.hpp>
#include <Calendar.hpp>

TEST_F (DatabaseTests, Departures) {
    json j;
    Calendar c;
    j["action"] = "departures";
    j["station"] = "Iaşi";
    j["country"] = "Romania";
    j["time"] = c.toJSON();

    Provider *arrivals = ProviderFactory::GetInstance().produce(j);

    json response = arrivals->execute();
    if (not_initialized) {
        ASSERT_STREQ(response["STATUS"].get<std::string>().c_str(), "ERROR");
    }
    else {
        ASSERT_STREQ(response["STATUS"].get<std::string>().c_str(), "OK");
        std::vector<json> x = response["RESULT"].get<std::vector<json> > ();
        ASSERT_NE(x.size(), 0);
    }
}

TEST_F (DatabaseTests, Arrivals) {
    json j;
    Calendar c;
    j["action"] = "arrivals";
    j["station"] = "Iaşi";
    j["country"] = "Romania";
    j["time"] = c.toJSON();

    Provider *arrivals = ProviderFactory::GetInstance().produce(j);

    json response = arrivals->execute();
    if (not_initialized) {
        ASSERT_STREQ(response["STATUS"].get<std::string>().c_str(), "ERROR");
    }
    else {
        ASSERT_STREQ(response["STATUS"].get<std::string>().c_str(), "OK");
        std::vector<json> x = response["RESULT"].get<std::vector<json> > ();
        ASSERT_NE(x.size(), 0);
    }
}

TEST_F (DatabaseTests, AutoComplete) {
    json j;
    Calendar c;
    j["action"] = "autocomplete";
    j["prefix"] = "Iaşi";
    j["lat"] = 43;
    j["lng"] = 28;

    Provider *arrivals = ProviderFactory::GetInstance().produce(j);

    json response = arrivals->execute();
    if (not_initialized) {
        ASSERT_STREQ(response["STATUS"].get<std::string>().c_str(), "ERROR");
    }
    else {
        ASSERT_STREQ(response["STATUS"].get<std::string>().c_str(), "OK");
        std::vector<json> x = response["RESULT"].get<std::vector<json> > ();
        ASSERT_NE(x.size(), 0);
    }
}

