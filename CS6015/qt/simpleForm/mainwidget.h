#pragma once

#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QRadioButton>
#include <QGroupBox>
#include <QTextEdit>

class MainWidget : public QWidget {
    Q_OBJECT

public:
    QGridLayout*  gridLayout;
    QPushButton*  finish;
    QPushButton*  refresh;

    explicit MainWidget(QWidget *parent = nullptr);
    void fillSummary();
    void clearAll();

private:
    QLabel*       firstName;
    QLineEdit*    firstNameInput;

    QLabel*       age;
    QSpinBox*     ageInput;

    QLabel*       lastName;
    QLineEdit*    lastNameInput;

    QLabel*       gender;
    QVBoxLayout*  vBoxLayout;
    QGroupBox*    groupBox;
    QRadioButton* maleInput;
    QRadioButton* femaleInput;

    QTextEdit*    text;

signals:
};
