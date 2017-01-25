//
// Created by vrosca on 1/10/17.
//

#include <QtWidgets/QCompleter>
#include <QtCore/QStringListModel>
#include "CitySelector.hpp"
#include "Client/src/Client.hpp"
#include <future>

void CitySelector::textAChanged(const QString &text) {
    std::string str_text = text.toUtf8().constData();
    auto result = std::async (std::launch::async, [str_text]() {return Client::GetInstance ().autocompleteUpdate(str_text);});
    autocomplete.lock ();
    auto status = result.wait_for (std::chrono::milliseconds (300));
    autocomplete.unlock ();
    //auto status = result.wait_for (std::chrono::seconds (3000));

    std::vector<std::string> results = result.get();

    QCompleter *completer = new QCompleter();
    QStringListModel *completerModel = new QStringListModel();

    completer->setModel(completerModel);
    QStringList stringListForCompleter;
    for (auto i : results) {
        stringListForCompleter << i.c_str ();
    }

    completerModel->setStringList(stringListForCompleter);
    this->setCompleter(completer);
}

CitySelector::CitySelector (QWidget *parent): QLineEdit(parent) {
    QObject::connect(this, SIGNAL(textChanged(const QString&)), this, SLOT (textAChanged(const QString &)));
};