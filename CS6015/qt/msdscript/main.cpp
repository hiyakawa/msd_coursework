#include "mainwidget.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    MainWidget* msdWidget = new MainWidget();

    msdWidget->setLayout(msdWidget->gridLayout);
    msdWidget->show();

    QObject::connect(msdWidget->submit, &QPushButton::clicked, msdWidget, &MainWidget::submitInput);
    QObject::connect(msdWidget->reset, &QPushButton::clicked, msdWidget, &MainWidget::clearAll);

    return app.exec();
}
