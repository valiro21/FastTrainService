//
// Created by vrosca on 1/12/17.
//

#ifndef FASTTRAINSERVICE_SEARCHBUTTON_HPP
#define FASTTRAINSERVICE_SEARCHBUTTON_HPP


#include <QtCore/QArgument>
#include <QtWidgets/QPushButton>

class SearchButton : public QPushButton {
Q_OBJECT

private:
    static SearchButton* instance;
    SearchButton (QWidget *parent = 0);

public:
    static SearchButton& GetInstance (QWidget *parent = 0);

private slots:
    void search(bool checked = false);
};


#endif //FASTTRAINSERVICE_SEARCHBUTTON_HPP
