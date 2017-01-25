#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLayout>
#include "SearchWidget.hpp"
#include "InformationPanel.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow w;
    w.setFixedHeight(1000);
    w.setFixedWidth(1000);

    SearchWidget s(&w);
    InformationPanel::GetInstance(&w);

    w.show();
    return a.exec();
}
