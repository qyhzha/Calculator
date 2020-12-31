#include "CalculatorUI.h"
#include <QDebug>

CalculatorUI::CalculatorUI()
{
    p = NULL;
    m_result = false;
}

bool CalculatorUI::construct()
{
    QGridLayout *gLayout = new QGridLayout();
    gLayout->setSpacing(10);

    m_edit = new QLineEdit(this);
    if (m_edit == NULL)
    {
        return false;
    }

    m_edit->setText("");
    m_edit->setMinimumHeight(30);
    m_edit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_edit->setReadOnly(true);
    m_edit->setAlignment(Qt::AlignRight);

    gLayout->addWidget(m_edit, 0, 0, 1, 5);

    const char *btnText[20] =
    {
        "7", "8", "9", "+", "(",
        "4", "5", "6", "-", ")",
        "1", "2", "3", "*", "<-",
        "0", ".", "=", "/", "C"
    };

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            m_btn[i * 5 + j] = new QPushButton(this);
            if (m_btn[i * 5 + j] == NULL)
            {
                return false;
            }

            gLayout->addWidget(m_btn[i * 5 + j], i + 1, j);

            m_btn[i * 5 + j]->setText(btnText[i * 5 + j]);
            m_btn[i * 5 + j]->setMinimumSize(40, 40);
            m_btn[i * 5 + j]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            m_btn[i * 5 + j]->

            connect(m_btn[i * 5 + j], SIGNAL(clicked()), this, SLOT(onBtnClicked()));
        }
    }

    setLayout(gLayout);

    return true;
}

CalculatorUI *CalculatorUI::NewInstance()
{
    CalculatorUI *ret = new CalculatorUI();

    if (ret == NULL || !ret->construct())
    {
        delete ret;
        ret = NULL;
    }

    return ret;
}

void CalculatorUI::onBtnClicked()
{
    QPushButton *btn = dynamic_cast<QPushButton *>(sender());
    if (btn == NULL)
    {
        return;
    }

    if (btn->text() == "=" || btn->text() == "<-" || btn->text() == "C")
    {
        if (btn->text() == "C")
        {
            m_edit->setText("");
            m_result = false;
        }

        if (btn->text() == "<-")
        {
            m_edit->setText(m_edit->text().left(m_edit->text().count() - 1));
            m_result = false;
        }

        if (btn->text() == "=")
        {
            m_result = true;
            if (p != NULL)
            {
                if (p->expression(m_edit->text()) == false)
                {
                    m_edit->setText(QString::fromWCharArray(L"表达式不合法"));
                }
                else
                {
                    m_edit->setText(p->result());
                }
            }
        }
    }
    else
    {
        if (m_result)
        {
            m_edit->setText("");
            m_result = false;
        }
        m_edit->setText(QString(m_edit->text() + btn->text()));
    }
}

CalculatorUI::~CalculatorUI()
{

}

void CalculatorUI::setICalculator(ICalculator *ptr)
{
    p = ptr;
}

void CalculatorUI::show()
{
    move(100, 100);
    resize(300, 300);
    setWindowTitle(QString::fromWCharArray(L"计算器"));

    QWidget::show();
}
