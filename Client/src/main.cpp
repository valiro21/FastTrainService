#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLayout>
#include "DeparturesTab.hpp"
#include "ArrivalsTab.hpp"
#include "RoutesTab.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow w;
    w.setFixedHeight(500);
    w.setFixedWidth(1200);

    QTabWidget mainTabManager(&w);
    QWidget *dTab = new DeparturesTab();
    QWidget *aTab = new ArrivalsTab();
    QWidget *pTab = new RoutesTab ();
    mainTabManager.addTab(dTab, "Departures");
    mainTabManager.addTab(aTab, "Arrivals");
    mainTabManager.addTab(pTab, "Routes");
    mainTabManager.setFixedWidth(1200);
    mainTabManager.setFixedHeight(500);

    w.show();
    return a.exec();
}
