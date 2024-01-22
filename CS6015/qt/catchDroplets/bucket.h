#pragma once

#include <QObject>
#include <QGraphicsPixmapItem>

class Bucket : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
private:
    void detectCollision();

protected:
    void keyPressEvent(QKeyEvent *event) override;

public:
    explicit Bucket(QObject *parent = nullptr);
    void startDetectCollision();

signals:
    void collisionDetected();
};
