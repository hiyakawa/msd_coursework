#include "mainwidget.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    MainWidget* simpleWidget = new MainWidget();

    simpleWidget->setLayout(simpleWidget->gridLayout);
    simpleWidget->show();

    QObject::connect(simpleWidget->refresh, &QPushButton::clicked, simpleWidget, &MainWidget::fillSummary);
    QObject::connect(simpleWidget->finish, &QPushButton::clicked, simpleWidget, &MainWidget::clearAll);

    return app.exec();
}
