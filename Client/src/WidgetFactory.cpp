//
// Created by vrosca on 1/25/17.
//

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include "WidgetFactory.hpp"

WidgetFactory* WidgetFactory::instance = nullptr;

WidgetFactory& WidgetFactory::GetInstance () {
    if (instance == nullptr) {
        instance = new WidgetFactory();
    }
    return *instance;
}

QWidget* WidgetFactory::produce_panel (QWidget *date, QWidget *selector, QWidget* action_button, int height) {
    QWidget *panel = new QWidget();
    QLayout *layout = new QVBoxLayout();
    layout->addWidget(date);
    layout->addWidget (new QLabel ("Oras"));
    layout->addWidget(selector);
    layout->addWidget(action_button);
    panel->setLayout(layout);
    panel->setFixedWidth(200);
    panel->setFixedHeight(height);
    return panel;
}