//
// Created by vrosca on 1/12/17.
//

#include <future>
#include <chrono>
#include "SearchButton.hpp"
#include "Client.hpp"

SearchButton::SearchButton (QWidget *parent) : QPushButton(parent) {
    QObject::connect(this, SIGNAL(clicked(bool)), this, SLOT(search(bool)));
}

void SearchButton::search(bool checked) {
    if (checked) {
        Client::GetInstance().search ();
    }
}

SearchButton* SearchButton::instance = 0;

SearchButton& SearchButton::GetInstance (QWidget *parent){
    if (instance == nullptr) {
        instance = new SearchButton(parent);
    }
    return *instance;
}