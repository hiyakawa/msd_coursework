#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget{parent} {

    firstName = new QLabel("First Name");
    firstNameInput = new QLineEdit();

    age = new QLabel("Age");
    ageInput = new QSpinBox();

    lastName = new QLabel("Last Name");
    lastNameInput = new QLineEdit();

    gender = new QLabel("Gender");
    groupBox = new QGroupBox("");
    vBoxLayout = new QVBoxLayout();
    groupBox->setLayout(vBoxLayout);

    maleInput = new QRadioButton("Male");
    femaleInput = new QRadioButton("Female");

    vBoxLayout->addWidget(maleInput);
    vBoxLayout->addWidget(femaleInput);

    refresh = new QPushButton("Refresh");

    text = new QTextEdit();

    finish = new QPushButton("Finish");

    gridLayout = new QGridLayout;

    gridLayout->addWidget(firstName, 0, 0);
    gridLayout->addWidget(firstNameInput, 0, 1);

    gridLayout->addWidget(age, 0, 2);
    gridLayout->addWidget(ageInput, 0, 3);

    gridLayout->addWidget(lastName, 1, 0);
    gridLayout->addWidget(lastNameInput, 1, 1);

    gridLayout->addWidget(gender, 2, 0);
    gridLayout->addWidget(groupBox, 2, 1);

    gridLayout->addWidget(refresh, 4, 0);

    gridLayout->addWidget(text, 5, 0, 5, 4);
    gridLayout->addWidget(finish, 10, 0, 10, 4);

    gridLayout->addItem(new QSpacerItem(50, 10), 0, 2, 1, 1);
}

void MainWidget::fillSummary() {
    QString firstNameStr = firstNameInput->text();
    QString lastNameStr = lastNameInput->text();
    QString ageStr = ageInput->text();

    QString summary;

    summary += "First Name: " + firstNameStr + "\n";
    summary += "Last Name: " + lastNameStr + "\n";
    summary += "Age: " + ageStr + "\nGender: ";

    if (maleInput->isChecked()) {
        summary += "Male";
    }
    if (femaleInput->isChecked()) {
        summary += "Female";
    }

    text->setText(summary);
}

void MainWidget::clearAll() {
    firstNameInput->setText("");
    lastNameInput->setText("");

    ageInput->clear();

    maleInput->setAutoExclusive(false);
    maleInput->setChecked(false);
    maleInput->setAutoExclusive(true);

    femaleInput->setAutoExclusive(false);
    femaleInput->setChecked(false);
    femaleInput->setAutoExclusive(true);

    text->setText("");
}
