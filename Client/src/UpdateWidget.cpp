//
// Created by vrosca on 1/26/17.
//

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSpinBox>
#include <Utils/include/Logger.hpp>
#include "UpdateWidget.hpp"
#include "Client.hpp"

UpdateWidget::UpdateWidget(QWidget *parent) : QWidget(parent) {
    QLayout *layout = new QHBoxLayout ();
    button = new QPushButton("Signal delay");
    time = new QSpinBox ();

    time->setMinimum(-20);
    time->setMaximum(20);
    time->setSingleStep(1);
    time->setValue(0);

    button->setFixedHeight(25);
    time->setFixedHeight(25);

    layout->setMargin(0);
    layout->addWidget(button);
    layout->addWidget(time);
    time->setEnabled(false);

    QObject::connect(button, SIGNAL(clicked(bool)), this, SLOT (update_click (bool)));

    clicked_once = false;
    setLayout(layout);
}

void UpdateWidget::setTripId (std::string trip_id) {
    this->trip_id = trip_id;
    clicked_once = false;
}

void UpdateWidget::update_click (bool) {
    if (clicked_once) {
        std::string text = time->text().toStdString();
        std::string str_minute = text.substr (0, text.find (':'));
        std::string str_second = text.substr (text.find (':') + 1, text.size ());

        int minute = std::stoi (str_minute);

        Logger::GetInstance().logd (trip_id);
        Logger::GetInstance().logd (std::to_string(minute));
        json x = Client::GetInstance().update (trip_id, minute);
        clicked_once = false;
        time->setValue(0);
        time->setEnabled(false);
        button->setText("Signal delay");
    }
    else {
        button->setText(QString("Add delay"));
        clicked_once = true;
        time->setEnabled(true);
    }
}