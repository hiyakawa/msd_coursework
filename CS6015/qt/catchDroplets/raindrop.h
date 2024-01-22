#pragma once

#include <QGraphicsPixmapItem>
#include <QObject>

class QTimer;

class Raindrop : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    explicit Raindrop(QObject *parent = nullptr);

public slots:
    void fall();

private:
    QTimer *timer;
};
