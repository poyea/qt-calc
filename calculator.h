#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
        Q_OBJECT

    public:
        Calculator(QWidget* parent = nullptr);
        ~Calculator();

    private:
        Ui::Calculator* ui;

    private slots:
        // Execute after emitting signals
        void ClearDisplay();
        void EqualPressed();
        void FlipSignPressed();
        void OperationPressed();
        void NumPressed();
        void DotPressed();
        void ePressed();
        void piPressed();
};
#endif // CALCULATOR_H
