#include "mainwidget.h"
#include <QApplication>
#include <QGraphicsView>
#include <QVBoxLayout>

int main(int argc, char **argv) {
    QApplication app (argc, argv);

    MainWidget* mainWidget = new MainWidget();
    mainWidget->show();

    return app.exec();
}
