//
// Created by vrosca on 1/10/17.
//

#ifndef FASTTRAINSERVICE_ACTIONSELECTOR_HPP
#define FASTTRAINSERVICE_ACTIONSELECTOR_HPP


#include <QtWidgets/QTabWidget>
#include <QtWidgets/QLineEdit>
#include <QVBoxLayout>

class ActionSelector : public QTabWidget {
Q_OBJECT
    ActionSelector(QWidget *parent = 0);
    static ActionSelector * instance;
    QLineEdit *arrivals_city;
    QLineEdit *departures_city;
    QLineEdit *start_city_path;
    QLineEdit *destination_city_path;
    int tab = 1;
public:
    static ActionSelector& GetInstance (QWidget *parent = 0);
    std::string getArrivalCity ();
    std::string getDestinationCity ();
    int getCurrentTab ();
private slots:
    void currentTabChanged(int);
};

extern QVBoxLayout* createCityLayout ();


#endif //FASTTRAINSERVICE_ACTIONSELECTOR_HPP
