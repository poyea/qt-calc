#include "calculator.h"
#include "ui_calculator.h"

#include <QKeyEvent>
#include <QShortcut>

double currentValue = 0.0;
bool addClicked = false;
bool minusClicked = false;
bool multiplyClicked = false;
bool divideClicked = false;

Calculator::Calculator(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    // ui->Widget
    ui->Display->setText(QString::number(currentValue));
    QPushButton* numButtons[10];
    for (int i = 0; i < 10; ++i)
    {
        QString name = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton*>(name);
        // trigger NumPressed when it's clicked
        numButtons[i]->setShortcut(QKeySequence(QString::number(i)));
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    ui->Dot->setShortcut(QKeySequence("."));
    connect(ui->Dot, SIGNAL(released()), this, SLOT(DotPressed()));

    ui->Add->setShortcut(QKeySequence("+"));
    connect(ui->Add, SIGNAL(released()), this, SLOT(OperationPressed()));
    ui->Minus->setShortcut(QKeySequence("-"));
    connect(ui->Minus, SIGNAL(released()), this, SLOT(OperationPressed()));
    ui->Times->setShortcut(QKeySequence("*"));
    connect(ui->Times, SIGNAL(released()), this, SLOT(OperationPressed()));
    ui->Divided->setShortcut(QKeySequence("/"));
    connect(ui->Divided, SIGNAL(released()), this, SLOT(OperationPressed()));

    ui->Equal->setShortcut(QKeySequence(Qt::Key_Enter));
    connect(ui->Equal, SIGNAL(released()), this, SLOT(EqualPressed()));

    ui->Sign->setShortcut(QKeySequence("s"));
    connect(ui->Sign, SIGNAL(released()), this, SLOT(FlipSignPressed()));

    ui->AC->setShortcut(QKeySequence("c"));
    connect(ui->AC, SIGNAL(released()), this, SLOT(ClearDisplay()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed()
{
    QPushButton* button = (QPushButton*)sender();
    QString value = button->text();
    QString displayValue = ui->Display->text();
    int8_t length = displayValue.length();
    QRegExp regex("^(0.)");
    if (regex.exactMatch(displayValue))
    {
        ui->Display->setText(displayValue + QString(value));
    }
    else if (displayValue.toDouble() == 0 || displayValue.toDouble() == 0.0)
    {
        ui->Display->setText(value);
    }
    else
    {
        QString newValue = displayValue + value;
        double newValueDouble = newValue.toDouble();
        ui->Display->setText(QString::number(newValueDouble, 'g', length));
    }
}

void Calculator::DotPressed()
{
    QString displayValue = ui->Display->text();
    QRegExp regex("[^.]+");
    if (regex.exactMatch(displayValue))
    {
        ui->Display->setText(displayValue + QString("."));
    }
}

void Calculator::OperationPressed()
{
    addClicked = false;
    minusClicked = false;
    multiplyClicked = false;
    divideClicked = false;
    QString displayValue = ui->Display->text();
    currentValue = displayValue.toDouble();
    QPushButton* button = (QPushButton*)sender();
    QString buttonValue = button->text();
    if (QString::compare(buttonValue, "+", Qt::CaseSensitive) == 0)
    {
        addClicked = true;
    }
    else if (QString::compare(buttonValue, "-", Qt::CaseSensitive) == 0)
    {
        minusClicked = true;
    }
    else if (QString::compare(buttonValue, "*", Qt::CaseSensitive) == 0)
    {
        multiplyClicked = true;
    }
    else if (QString::compare(buttonValue, "/", Qt::CaseSensitive) == 0)
    {
        divideClicked = true;
    }
    ui->Display->setText("");
};

void Calculator::EqualPressed()
{
    double result = 0.0;
    QString displayValue = ui->Display->text();
    double displayValueDouble = displayValue.toDouble();
    if (addClicked)
    {
        result = currentValue + displayValueDouble;
    }
    else if (minusClicked)
    {
        result = currentValue - displayValueDouble;
    }
    else if (multiplyClicked)
    {
        result = currentValue * displayValueDouble;
    }
    else if (divideClicked)
    {
        result = currentValue / displayValueDouble;
    }
    ui->Display->setText(QString::number(result));
};

void Calculator::FlipSignPressed()
{
    QString displayValue = ui->Display->text();
    QRegExp regex("[-]?[0-9.]*");
    if (regex.exactMatch(displayValue))
    {
        double displayValueDouble = -1 * displayValue.toDouble();
        ui->Display->setText(QString::number(displayValueDouble));
    }
};

void Calculator::ClearDisplay()
{
    currentValue = 0.0;
    ui->Display->setText(QString::number(currentValue));
}

