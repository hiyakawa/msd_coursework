#pragma once

#include "bucket.h"
#include "mainwidget.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QLabel>

class GameScene: public QGraphicsScene {
    Q_OBJECT
private:
    Bucket* bucket;
    void setBucket();
    void newRaindrop();

public:
    MainWidget* mainWidget;
    explicit GameScene(MainWidget* widget, QObject* parent = nullptr);
};
