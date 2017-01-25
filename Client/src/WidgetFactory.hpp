//
// Created by vrosca on 1/25/17.
//

#ifndef FASTTRAINSERVICE_WIDGETFACTORY_HPP
#define FASTTRAINSERVICE_WIDGETFACTORY_HPP

#include <QtWidgets/QWidget>

class WidgetFactory {
protected:
    static WidgetFactory *instance;
    WidgetFactory () {}

public:
    static WidgetFactory& GetInstance ();
    QWidget* produce_panel (QWidget *date, QWidget *selector, QWidget* action_button);
};


#endif //FASTTRAINSERVICE_WIDGETFACTORY_HPP
