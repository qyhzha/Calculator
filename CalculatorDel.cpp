#include "CalculatorDel.h"
#include <QDebug>

CalculatorDel::CalculatorDel()
{
    m_exp = "";
    m_result = "";
}

bool CalculatorDel::isDigitOrDot(QChar c)
{
    return (c >= '0' && c <= '9') || (c == '.');
}

bool CalculatorDel::isOperator(QString s)
{
    return (s == "+") || (s == "-") || (s == "*") || (s == "/");
}

bool CalculatorDel::isSymbol(QChar c)
{
    return isOperator(c) || c == '(' || c == ')';
}

bool CalculatorDel::isNumber(QString s)
{
    bool ret = false;

    s.toDouble(&ret);

    return ret;
}

bool CalculatorDel::match(QQueue<QString> &exp)
{
    QStack<QString> m_stack;

    for (int i = 0; i < exp.length(); i++)
    {
        if (exp[i] == "(")
        {
            m_stack.push(exp[i]);
        }

        if (exp[i] == ")")
        {
            if (m_stack.isEmpty())
            {
                return false;
            }
            else
            {
                m_stack.pop();
            }
        }
    }

    if (!m_stack.isEmpty())
    {
        return false;
    }

    return true;
}

int CalculatorDel::priority(QString s)
{
    int ret = 0;

    if (s == "+" || s == "-")
    {
        ret = 1;
    }

    if (s == "*" || s == "/")
    {
        ret = 2;
    }

    return ret;
}

bool CalculatorDel::split(const QString &exp, QQueue<QString> &output)
{
    QString digit = "";
    QString predigit = "";

    output.clear();

    for (int i = 0; i < exp.length(); i++)
    {
        if (isDigitOrDot(exp[i]))
        {
            digit += exp[i];
            predigit = exp[i];
        }
        else if (isSymbol(exp[i]))
        {
            if (!digit.isEmpty())
            {
                if (isNumber(digit))
                {
                    output.enqueue(digit);
                    digit.clear();
                }
                else
                {
                    return false;
                }
            }

            if ((exp[i] == '+' || exp[i] == '-') && (predigit == "" || predigit == "("
                    || isOperator(predigit)))
            {
                digit = exp[i];
            }
            else
            {
                output.enqueue(exp[i]);
            }

            predigit = exp[i];
        }
        else
        {
            return false;
        }
    }

    if (!digit.isEmpty())
    {
        if (isNumber(digit))
        {
            output.enqueue(digit);
            digit.clear();
        }
        else
        {
            return false;
        }
    }

    return true;
}

bool CalculatorDel::transform(QQueue<QString> &exp, QQueue<QString> &output)
{
    if (match(exp) == false)
    {
        return false;
    }

    output.clear();

    QStack<QString> m_stack;

    while (!exp.isEmpty())
    {
        QString str = exp.dequeue();
        if (isNumber(str))
        {
            output.enqueue(str);
        }

        if (str == "(")
        {
            m_stack.push(str);
        }

        if (isOperator(str))
        {
            while (!m_stack.isEmpty() && priority(str) <= priority(m_stack.top()))
            {
                output.enqueue(m_stack.pop());
            }

            m_stack.push(str);
        }

        if (str == ")")
        {
            while (!m_stack.isEmpty() && m_stack.top() != "(")
            {
                output.enqueue(m_stack.pop());
            }
        }
    }

    while (!m_stack.isEmpty())
    {
        output.enqueue(m_stack.pop());
    }

    return true;
}

QString CalculatorDel::calculate(QQueue<QString> &exp)
{
    QString ret;
    QStack<QString> m_stack;
    double num1 = 0;
    double num2 = 0;

    while (!exp.isEmpty())
    {
        QString str = exp.dequeue();

        if (isNumber(str))
        {
            m_stack.push(str);
        }

        if (isOperator(str))
        {
            if (m_stack.count() >= 2)
            {
                num2 = m_stack.pop().toDouble();
                num1 = m_stack.pop().toDouble();

                if (str == "+")
                {
                    m_stack.push(QString::number(num1 + num2));
                }

                if (str == "-")
                {
                    m_stack.push(QString::number(num1 - num2));
                }

                if (str == "*")
                {
                    m_stack.push(QString::number(num1 * num2));
                }

                if (str == "/")
                {
                    if (num2 < 0.000001 && num2 > -0.000001)
                    {
                        m_stack.clear();
                        break;
                    }
                    else
                    {
                        m_stack.push(QString::number(num1 / num2));
                    }

                }
            }
            else
            {
                break;
            }
        }
    }

    if (m_stack.count() == 1)
    {
        ret = m_stack.pop();
    }
    else if (m_stack.isEmpty())
    {
        ret = QString::fromWCharArray(L"除数不能为0");
    }
    else
    {
        ret = QString::fromWCharArray(L"表达式不合法");
    }

    return ret;
}

bool CalculatorDel::expression(const QString &exp)
{
    bool ret = false;
    QQueue<QString> output1;
    QQueue<QString> output2;

    m_exp = exp;

    ret = split(exp, output1);
    if (!ret)
    {
        return false;
    }

    ret = transform(output1, output2);
    if (!ret)
    {
        return false;
    }

    m_result = calculate(output2);

    return true;
}

QString CalculatorDel::result()
{
    return m_result;
}


