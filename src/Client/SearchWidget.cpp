//
// Created by vrosca on 1/10/17.
//

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include "SearchWidget.hpp"
#include "ActionSelector.hpp"
#include "DateSelector.hpp"
#include "SearchButton.hpp"

SearchWidget::SearchWidget(QWidget* parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout();
    DateSelector *dateSelector = new DateSelector ();
    ActionSelector *actionSelector = &ActionSelector::GetInstance();

    SearchButton *searchButton = &SearchButton::GetInstance ();

    layout->addWidget(dateSelector);
    layout->addWidget(actionSelector);
    layout->addWidget(searchButton);
    setLayout(layout);
    setFixedWidth(300);
    setFixedHeight(500);
}