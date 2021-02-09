/********************************************************************************
** Form generated from reading UI file 'acerca.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACERCA_H
#define UI_ACERCA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Acerca
{
public:
    QFormLayout *formLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QDialog *Acerca)
    {
        if (Acerca->objectName().isEmpty())
            Acerca->setObjectName(QStringLiteral("Acerca"));
        Acerca->setWindowModality(Qt::ApplicationModal);
        Acerca->setEnabled(true);
        Acerca->resize(581, 294);
        Acerca->setMinimumSize(QSize(581, 0));
        Acerca->setWindowOpacity(1);
        Acerca->setSizeGripEnabled(false);
        Acerca->setModal(false);
        formLayout = new QFormLayout(Acerca);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label = new QLabel(Acerca);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QStringLiteral("Calibri"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        font.setKerning(true);
        font.setStyleStrategy(QFont::PreferDefault);
        label->setFont(font);
        label->setTextFormat(Qt::AutoText);
        label->setAlignment(Qt::AlignCenter);
        label->setWordWrap(false);

        verticalLayout_2->addWidget(label);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_2 = new QLabel(Acerca);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font1;
        font1.setFamily(QStringLiteral("Calibri"));
        label_2->setFont(font1);

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(Acerca);
        label_3->setObjectName(QStringLiteral("label_3"));
        QFont font2;
        font2.setFamily(QStringLiteral("Calibri"));
        font2.setBold(false);
        font2.setItalic(false);
        font2.setUnderline(false);
        font2.setWeight(50);
        font2.setStrikeOut(false);
        label_3->setFont(font2);
        label_3->setCursor(QCursor(Qt::ArrowCursor));

        verticalLayout->addWidget(label_3);


        verticalLayout_2->addLayout(verticalLayout);


        formLayout->setLayout(0, QFormLayout::SpanningRole, verticalLayout_2);


        retranslateUi(Acerca);

        QMetaObject::connectSlotsByName(Acerca);
    } // setupUi

    void retranslateUi(QDialog *Acerca)
    {
        Acerca->setWindowTitle(QApplication::translate("Acerca", "Acerca", 0));
        label->setText(QApplication::translate("Acerca", "<html><head/><body><p align=\"center\"><span style=\" font-size:28pt;\">Trabalho realizado por:</span></p></body></html>", 0));
        label_2->setText(QApplication::translate("Acerca", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt;\">-Jo\303\243o Barreiros:2014196880</span></p></body></html>", 0));
        label_3->setText(QApplication::translate("Acerca", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt;\">-Filipe Concei\303\247\303\243o:2014196660</span></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class Acerca: public Ui_Acerca {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACERCA_H
