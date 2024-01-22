#include "raindrop.h"
#include "constants.h"
#include <QTimer>

Raindrop::Raindrop(QObject *parent)
    : QObject{parent}, timer{new QTimer{this}} {
    this->setPixmap((QPixmap("://images/water.gif"))
                        .scaled(RAINDROP_WIDTH,RAINDROP_HEIGHT));
    connect(timer, &QTimer::timeout, this, &Raindrop::fall);
    timer->start(1000);
}

void Raindrop::fall() {
    setPos(x(), y() + RAINDROP_SPEED);

    if (y() > BACKGROUND_HEIGHT ||
        x() < -RAINDROP_WIDTH ||
        x() > BACKGROUND_WIDTH + RAINDROP_WIDTH) {
        timer->stop();
        this->deleteLater();
    }
}
