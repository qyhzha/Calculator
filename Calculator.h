#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "CalculatorUI.h"
#include "CalculatorDel.h"

class Calculator
{
    protected:
        CalculatorUI *m_ui;
        CalculatorDel m_del;

        Calculator();
        bool construct();

    public:
        static Calculator *NewInstance();
        ~Calculator();

        void show();
};

#endif // CALCULATOR_H
