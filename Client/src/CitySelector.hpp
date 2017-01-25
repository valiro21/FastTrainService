//
// Created by vrosca on 1/10/17.
//

#ifndef FASTTRAINSERVICE_CITYSELECTOR_HPP
#define FASTTRAINSERVICE_CITYSELECTOR_HPP


#include <QtWidgets/QLineEdit>
#include <mutex>

class CitySelector : public QLineEdit {
Q_OBJECT
public:
    std::mutex autocomplete;
    CitySelector (QWidget *parent = 0);
private slots:
    void textAChanged(const QString &text);
};


#endif //FASTTRAINSERVICE_CITYSELECTOR_HPP
