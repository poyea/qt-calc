#include "calculator.h"
#include "ui_calculator.h"

double current_value = 0.0;
bool add_clicked = false;
bool minus_clicked = false;
bool multiply_clicked = false;
bool divide_clicked = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    // ui->Widget
    ui->Display->setText(QString::number(current_value));

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
    QString display_value = ui->Display->text();
    if(display_value.toDouble() == 0 || display_value.toDouble() == 0.0){
        ui->Display->setText(value);
    }else{
        QString new_value = display_value + value;
        double new_value_double = new_value.toDouble();
        ui->Display->setText(QString::number(new_value_double,'g',20));
    }
}

void Calculator::OperationPressed(){
    add_clicked = false;
    minus_clicked = false;
    multiply_clicked = false;
    divide_clicked = false;
    QString display_value = ui->Display->text();
    current_value = display_value.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString button_value = button->text();
    if(QString::compare(button_value, "+", Qt::CaseSensitive) == 0){
        add_clicked = true;
    }else if(QString::compare(button_value, "-", Qt::CaseSensitive) == 0){
        minus_clicked = true;
    }else if(QString::compare(button_value, "*", Qt::CaseSensitive) == 0){
        multiply_clicked = true;
    }else if(QString::compare(button_value, "/", Qt::CaseSensitive) == 0){
        divide_clicked = true;
    }

    ui->Display->setText("");
};

void Calculator::EqualPressed(){
    double result = 0.0;
    QString display_value = ui->Display->text();
    double display_value_double = display_value.toDouble();
    if(add_clicked){
        result = current_value + display_value_double;
    }else if(minus_clicked){
        result = current_value - display_value_double;
    }else if(multiply_clicked){
        result = current_value * display_value_double;
    }else if(divide_clicked){
        result = current_value / display_value_double;
    }

    ui->Display->setText(QString::number(result));
};

void Calculator::FlipSignPressed(){
    QString display_value = ui->Display->text();
    QRegExp regex("[-]?[0-9.]*");
    if(regex.exactMatch(display_value)){
        double display_value_double = -1 * display_value.toDouble();
        ui->Display->setText(QString::number(display_value_double));
    }
};
