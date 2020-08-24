#include "calculator.h"
#include "ui_calculator.h"

#include <QKeyEvent>
#include <QShortcut>

const uint16_t DEFAULT_LENGTH = 20;
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

    ui->Conste->setShortcut(QKeySequence("e"));
    connect(ui->Conste, SIGNAL(released()), this, SLOT(ePressed()));
    ui->Constpi->setShortcut(QKeySequence("p"));
    connect(ui->Constpi, SIGNAL(released()), this, SLOT(piPressed()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::ePressed()
{
    currentValue = 2.7182818284590452353602874713526624977572470936999;
    ui->Display->setText(QString::number(currentValue, 'g', DEFAULT_LENGTH));
}

void Calculator::piPressed()
{
    currentValue = 3.1415926535897932384626433832795028841971693993751;
    ui->Display->setText(QString::number(currentValue, 'g', DEFAULT_LENGTH));
}

void Calculator::NumPressed()
{
    QPushButton* button = (QPushButton*)sender();
    QString value = button->text();
    QString displayValue = ui->Display->text();
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
        ui->Display->setText(QString::number(newValueDouble, 'g', DEFAULT_LENGTH));
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
    ui->Display->setText(QString::number(result, 'g', DEFAULT_LENGTH));
};

void Calculator::FlipSignPressed()
{
    QString displayValue = ui->Display->text();
    QRegExp regex("[-]?[0-9.]*");
    if (regex.exactMatch(displayValue))
    {
        double displayValueDouble = -1 * displayValue.toDouble();
        ui->Display->setText(QString::number(displayValueDouble, 'g', DEFAULT_LENGTH));
    }
};

void Calculator::ClearDisplay()
{
    currentValue = 0.0;
    ui->Display->setText(QString::number(currentValue));
}

