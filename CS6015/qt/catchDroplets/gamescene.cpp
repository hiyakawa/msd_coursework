#include "gamescene.h"
#include "constants.h"
#include "raindrop.h"
#include "bucket.h"
#include <QBrush>
#include <QTimer>
#include <QGraphicsItem>

class MainWidget;

GameScene::GameScene(MainWidget* widget, QObject* parent)
    : QGraphicsScene(parent), mainWidget(widget) {
    this->setSceneRect(0,0,BACKGROUND_WIDTH, BACKGROUND_HEIGHT);
    this->setBackgroundBrush(QBrush(QImage("://images/background.jpg")
                                        .scaledToHeight(BACKGROUND_HEIGHT)
                                        .scaledToWidth(BACKGROUND_WIDTH)));
    this->setBucket();
    this->addItem(bucket);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameScene::newRaindrop);
    timer->start(1000);
}

void GameScene::setBucket() {
    bucket = new Bucket();

    bucket->setPos(BACKGROUND_WIDTH / 2 - BUCKET_WIDTH / 2,
                   BACKGROUND_HEIGHT - BUCKET_WIDTH);
    bucket->setFlag(QGraphicsItem::ItemIsFocusable);
    bucket->setFocus();
    bucket->startDetectCollision();
}

void GameScene::newRaindrop() {
    int raindropCount = 0;

    for (QGraphicsItem* item : this->items()) {
        if (dynamic_cast<Raindrop*>(item) != nullptr) {
            raindropCount++;
        }
    }

    if (raindropCount < RAINDROP_COUNT) {
        Raindrop* raindrop = new Raindrop();
        int rand = arc4random_uniform(BACKGROUND_WIDTH);
        raindrop->setPos(rand, 0);
        this->addItem(raindrop);
    }
}
