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

TEST_F (DatabaseTests, WrongAction) {
    json j;
    j["action"] = "none";

    Provider *arrivals = ProviderFactory::GetInstance().produce(j);

    json response = arrivals->execute();
    ASSERT_STREQ(response["STATUS"].get<std::string>().c_str(), "ERROR");
}

TEST_F (DatabaseTests, MissingAction) {
    json j;

    Provider *arrivals = ProviderFactory::GetInstance().produce(j);

    json response = arrivals->execute();
    ASSERT_STREQ(response["STATUS"].get<std::string>().c_str(), "ERROR");
}

TEST_F (DatabaseTests, AutoCompleteMissingField) {
    json j;
    Calendar c;
    j["action"] = "autocomplete";
    j["lat"] = 43;
    j["lng"] = 28;

    Provider *arrivals = ProviderFactory::GetInstance().produce(j);

    json response = arrivals->execute();
    ASSERT_STREQ(response["STATUS"].get<std::string>().c_str(), "ERROR");
}

TEST_F (DatabaseTests, ArrivalsMissingField) {
    json j;
    Calendar c;
    j["action"] = "arrivals";

    Provider *arrivals = ProviderFactory::GetInstance().produce(j);

    json response = arrivals->execute();
    ASSERT_STREQ(response["STATUS"].get<std::string>().c_str(), "ERROR");
}

TEST_F (DatabaseTests, DeparturesMissingField) {
    json j;
    Calendar c;
    j["action"] = "departures";

    Provider *arrivals = ProviderFactory::GetInstance().produce(j);

    json response = arrivals->execute();
    ASSERT_STREQ(response["STATUS"].get<std::string>().c_str(), "ERROR");
}

TEST_F (DatabaseTests, ShortestPath) {
    json j;
    Calendar c;
    j["action"] = "path";
    j["origin"] = "Iaşi";
    j["destination"] = "Galaţi";
    j["time"] = c.toJSON();

    Provider *path = ProviderFactory::GetInstance().produce(j);

    json response = path->execute();
    if (not_initialized) {
        ASSERT_STREQ(response["STATUS"].get<std::string>().c_str(), "ERROR");
    }
    else {
        ASSERT_STREQ(response["STATUS"].get<std::string>().c_str(), "OK");
        std::vector<json> x = response["RESULT"].get<std::vector<json> > ();
        Logger::GetInstance().logd(response.dump());
        ASSERT_NE(x.size(), 0);
    }
}

TEST_F (DatabaseTests, ShortestPathVoid) {
    json j;
    Calendar c;
    j["action"] = "path";
    j["origin"] = "Iai";
    j["destination"] = "Galaţi";
    j["time"] = c.toJSON();

    Provider *path = ProviderFactory::GetInstance().produce(j);

    json response = path->execute();
    ASSERT_STREQ(response["STATUS"].get<std::string>().c_str(), "ERROR");
}

TEST_F (DatabaseTests, ShortestPathMissing) {
    json j;
    Calendar c;
    j["action"] = "path";
    j["destination"] = "Galaţi";
    j["time"] = c.toJSON();

    Provider *path = ProviderFactory::GetInstance().produce(j);

    json response = path->execute();
    ASSERT_STREQ(response["STATUS"].get<std::string>().c_str(), "ERROR");
}