#include "calculator.h"
#include "ui_calculator.h"

double currentValue = 0.0;
bool addClicked = false;
bool minusClicked = false;
bool multiplyClicked = false;
bool divideClicked = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    // ui->Widget
    ui->Display->setText(QString::number(currentValue));

    QPushButton *numButtons[10];
    for(int i = 0; i < 10; ++i){
        QString name = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(name);
        // trigger NumPressed when it's clicked
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }
    connect(ui->Add, SIGNAL(released()), this, SLOT(OperationPressed()));
    connect(ui->Minus, SIGNAL(released()), this, SLOT(OperationPressed()));
    connect(ui->Times, SIGNAL(released()), this, SLOT(OperationPressed()));
    connect(ui->Divided, SIGNAL(released()), this, SLOT(OperationPressed()));

    connect(ui->Equal, SIGNAL(released()), this, SLOT(EqualPressed()));

    connect(ui->Sign, SIGNAL(released()), this, SLOT(FlipSignPressed()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString value = button->text();
    QString displayValue = ui->Display->text();
    if(displayValue.toDouble() == 0 || displayValue.toDouble() == 0.0){
        ui->Display->setText(value);
    }else{
        QString newValue = displayValue + value;
        double newValueDouble = newValue.toDouble();
        ui->Display->setText(QString::number(newValueDouble,'g',20));
    }
}

void Calculator::OperationPressed(){
    addClicked = false;
    minusClicked = false;
    multiplyClicked = false;
    divideClicked = false;
    QString displayValue = ui->Display->text();
    currentValue = displayValue.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString buttonValue = button->text();
    if(QString::compare(buttonValue, "+", Qt::CaseSensitive) == 0){
        addClicked = true;
    }else if(QString::compare(buttonValue, "-", Qt::CaseSensitive) == 0){
        minusClicked = true;
    }else if(QString::compare(buttonValue, "*", Qt::CaseSensitive) == 0){
        multiplyClicked = true;
    }else if(QString::compare(buttonValue, "/", Qt::CaseSensitive) == 0){
        divideClicked = true;
    }

    ui->Display->setText("");
};

void Calculator::EqualPressed(){
    double result = 0.0;
    QString displayValue = ui->Display->text();
    double displayValueDouble = displayValue.toDouble();
    if(addClicked){
        result = currentValue + displayValueDouble;
    }else if(minusClicked){
        result = currentValue - displayValueDouble;
    }else if(multiplyClicked){
        result = currentValue * displayValueDouble;
    }else if(divideClicked){
        result = currentValue / displayValueDouble;
    }

    ui->Display->setText(QString::number(result));
};

void Calculator::FlipSignPressed(){
    QString displayValue = ui->Display->text();
    QRegExp regex("[-]?[0-9.]*");
    if(regex.exactMatch(displayValue)){
        double displayValueDouble = -1 * displayValue.toDouble();
        ui->Display->setText(QString::number(displayValueDouble));
    }
};
