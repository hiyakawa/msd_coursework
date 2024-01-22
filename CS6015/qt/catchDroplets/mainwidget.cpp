#include "gamescene.h"
#include "mainwidget.h"
#include "constants.h"
#include <QGraphicsView>
#include <QVBoxLayout>

MainWidget::MainWidget(QWidget *parent)
    : QWidget{parent} {
    setWindowTitle("Catch Droplets");

    QGraphicsView* mainView = new QGraphicsView(this);
    mainView->setFixedSize(BACKGROUND_WIDTH, BACKGROUND_HEIGHT);

    mainView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mainView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    GameScene* mainScene = new GameScene(this);
    mainView->setScene(mainScene);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(mainView);
    mainLayout->setAlignment(Qt::AlignCenter);

    setLayout(mainLayout);
}
