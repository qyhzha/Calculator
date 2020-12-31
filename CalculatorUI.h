#ifndef CALCULATORUI_H
#define CALCULATORUI_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include "ICalculator.h"

class CalculatorUI : public QWidget
{
        Q_OBJECT

    protected:
        bool m_result;

        QLineEdit *m_edit;
        QPushButton *m_btn[20];

        ICalculator *p;

    protected:
        CalculatorUI();
        bool construct();

    protected slots:
        void onBtnClicked();

    public:
        static CalculatorUI *NewInstance();
        ~CalculatorUI();

        void setICalculator(ICalculator *ptr);
        void show();
};

#endif // CALCULATORUI_H
