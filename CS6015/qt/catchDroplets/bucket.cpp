#include "bucket.h"
#include "constants.h"
#include "raindrop.h"
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>

Bucket::Bucket(QObject *parent) : QObject{parent} {
    this->setPixmap(QPixmap("://images/bucket.png")
                        .scaled(BUCKET_WIDTH, BUCKET_HEIGHT));
}

void Bucket::keyPressEvent(QKeyEvent *event) {
    int prevX = pos().x();

    if (event->key() == Qt::Key_Left) {
        if (prevX > 0) {
            setPos(prevX - BUCKET_STEP, pos().y());
        }
    }
    else if (event->key() == Qt::Key_Right) {
        if (prevX + BUCKET_WIDTH < BACKGROUND_WIDTH) {
            setPos(prevX + BUCKET_STEP, pos().y());
        }
    }
    else {
        QGraphicsItem::keyPressEvent(event);
    }
}

void Bucket::startDetectCollision() {
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Bucket::detectCollision);
    timer->start(COLLISION_INTERVAL);
}

void Bucket::detectCollision() {
    for (QGraphicsItem* item : scene()->collidingItems(this)) {
        if (dynamic_cast<Raindrop*>(item)) {
            scene()->removeItem(item);
            delete item;
            emit collisionDetected();
        }
    }
}
