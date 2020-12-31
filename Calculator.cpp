#include "Calculator.h"

Calculator::Calculator()
{

}

bool Calculator::construct()
{
    m_ui = CalculatorUI::NewInstance();

    if (m_ui == NULL)
    {
        return false;
    }

    m_ui->setICalculator(&m_del);

    return true;
}

Calculator *Calculator::NewInstance()
{
    Calculator *ret = new Calculator();

    if (ret == NULL || !ret->construct())
    {
        delete ret;
        ret = NULL;
    }

    return ret;
}

Calculator::~Calculator()
{
    delete m_ui;
}

void Calculator::show()
{
    if (m_ui != NULL)
    {
        m_ui->show();
    }
}


