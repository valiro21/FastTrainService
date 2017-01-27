//
// Created by vrosca on 1/26/17.
//

#ifndef FASTTRAINSERVICE_UPDATEWIDGETS_HPP
#define FASTTRAINSERVICE_UPDATEWIDGETS_HPP


#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>

class UpdateWidget : public QWidget {
Q_OBJECT
public:
    bool clicked_once;
    std::string trip_id;
    UpdateWidget(QWidget *parent = 0);
    QSpinBox *time;
    QPushButton *button;
    void setTripId (std::string trip_id);
private slots:
    void update_click (bool);
};


#endif //FASTTRAINSERVICE_UPDATEWIDGETS_HPP
