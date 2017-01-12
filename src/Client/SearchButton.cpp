//
// Created by vrosca on 1/12/17.
//

#include <future>
#include <Logger.hpp>
#include "SearchButton.hpp"
#include "Client.hpp"

SearchButton::SearchButton (QWidget *parent) : QPushButton(parent) {
    QObject::connect(this, SIGNAL(clicked(bool)), this, SLOT(search(bool)));
}

void SearchButton::search(bool checked) {
    if (checked) {
        setEnabled(false);
        auto future = std::async(std::launch::async, []() {Client::GetInstance().search();});
        auto timeout = future.wait_for (std::chrono::seconds (8));
        if (timeout == std::future_status::timeout) {
            Logger::GetInstance() << "Timeout reached\n";
        }
        setEnabled(true);
    }
}

SearchButton* SearchButton::instance = 0;

SearchButton& SearchButton::GetInstance (QWidget *parent){
    if (instance == nullptr) {
        instance = new SearchButton(parent);
    }
    return *instance;
}