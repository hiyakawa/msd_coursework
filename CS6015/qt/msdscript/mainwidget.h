#pragma once

#include <QStyle>
#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QRadioButton>
#include <QGroupBox>
#include <QTextEdit>

class MainWidget : public QWidget {
    Q_OBJECT

public:
    QGridLayout*  gridLayout;
    QPushButton*  submit;
    QPushButton*  reset;

    explicit MainWidget(QWidget *parent = nullptr);
    void submitInput();
    void clearAll();

private:
    QLabel*       expression;
    QTextEdit*    expressionInput;

    QVBoxLayout*  vBoxLayout;
    QGroupBox*    groupBox;
    QRadioButton* interp;
    QRadioButton* prettyPrint;

    QLabel*       result;
    QTextEdit*    resultInput;

signals:
};
