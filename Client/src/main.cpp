#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLayout>
#include "DeparturesTab.hpp"
#include "ArrivalsTab.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow w;
    w.setFixedHeight(500);
    w.setFixedWidth(900);

    QTabWidget mainTabManager(&w);
    QWidget *dTab = new DeparturesTab();
    QWidget *aTab = new ArrivalsTab();
    mainTabManager.addTab(dTab, "Departures");
    mainTabManager.addTab(aTab, "Arrivals");
    mainTabManager.setFixedWidth(900);
    mainTabManager.setFixedHeight(500);

    w.show();
    return a.exec();
}
