#ifndef CALCULATORDEL_H
#define CALCULATORDEL_H

#include "ICalculator.h"
#include <QQueue>
#include <QStack>

class CalculatorDel : public ICalculator
{
    protected:
        QString m_exp;
        QString m_result;

    protected:
        bool isDigitOrDot(QChar c);
        bool isOperator(QString s);
        bool isSymbol(QChar c);
        bool isNumber(QString s);
        bool match(QQueue<QString> &exp);
        int priority(QString s);

        bool split(const QString &exp, QQueue<QString> &output);
        bool transform(QQueue<QString> &exp, QQueue<QString> &output);
        QString calculate(QQueue<QString> &exp);

    public:
        CalculatorDel();

        bool expression(const QString &exp);
        QString result();
};

#endif // CALCULATORDEL_H
