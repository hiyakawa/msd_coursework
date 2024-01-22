#include "mainwidget.h"

#include "expr.h"
#include "parse.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget{parent} {

    expression = new QLabel("Expression:");
    expressionInput = new QTextEdit();

    groupBox = new QGroupBox();
    vBoxLayout = new QVBoxLayout();
    groupBox->setLayout(vBoxLayout);

    interp = new QRadioButton("Interp");
    prettyPrint = new QRadioButton("Pretty Print");

    vBoxLayout->addWidget(interp);
    vBoxLayout->addWidget(prettyPrint);

    submit = new QPushButton("Submit");

    result = new QLabel("Result:");
    resultInput = new QTextEdit();

    reset = new QPushButton("Reset");

    gridLayout = new QGridLayout;

    gridLayout->addWidget(expression, 0, 0);
    gridLayout->addWidget(expressionInput, 0, 1);

    gridLayout->addWidget(groupBox, 5, 1);

    gridLayout->addWidget(submit, 6, 1);

    gridLayout->addWidget(result, 7, 0);
    gridLayout->addWidget(resultInput, 7, 1);

    gridLayout->addWidget(reset, 10, 1);

    gridLayout->addItem(new QSpacerItem(50, 10), 0, 2, 1, 1);
}

void MainWidget::submitInput() {
    std::string exprStr = expressionInput->toPlainText().toUtf8().constData();

    try {
        if (interp->isChecked()) {
            resultInput->setText(QString::fromStdString(parse_str(exprStr)->interp(Env::empty)->to_string()));
        }

        if (prettyPrint->isChecked()) {
            resultInput->setText(QString::fromStdString(parse_str(exprStr)->to_pretty_string()));
        }
    }
    catch (std::runtime_error e) {
        resultInput->setText(QString::fromStdString("Invalid input."));
    }
}

void MainWidget::clearAll() {
    expressionInput->setText("");

    interp->setAutoExclusive(false);
    interp->setChecked(false);
    interp->setAutoExclusive(true);

    prettyPrint->setAutoExclusive(false);
    prettyPrint->setChecked(false);
    prettyPrint->setAutoExclusive(true);

    resultInput->setText("");
}
