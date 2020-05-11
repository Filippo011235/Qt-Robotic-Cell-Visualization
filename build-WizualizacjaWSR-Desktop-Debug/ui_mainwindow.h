/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label_SzybTasm;
    QScrollBar *horizontalScrollBarSzybTasm;
    QPushButton *pushButtonESTOP;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QCheckBox *checkBoxPET;
    QCheckBox *checkBoxKarton;
    QCheckBox *checkBoxHDPE;
    QCheckBox *checkBoxAlum;
    QCheckBox *checkBoxNieznany;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *lineEdit_PET;
    QLineEdit *lineEdit_Karton;
    QLineEdit *lineEdit_HDPE;
    QLineEdit *lineEdit_Alum;
    QLineEdit *lineEdit_Nieznany;
    QTabWidget *tabWidget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(730, 426);
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label_SzybTasm = new QLabel(centralwidget);
        label_SzybTasm->setObjectName(QStringLiteral("label_SzybTasm"));
        label_SzybTasm->setGeometry(QRect(550, 150, 149, 19));
        QFont font;
        font.setPointSize(12);
        label_SzybTasm->setFont(font);
        horizontalScrollBarSzybTasm = new QScrollBar(centralwidget);
        horizontalScrollBarSzybTasm->setObjectName(QStringLiteral("horizontalScrollBarSzybTasm"));
        horizontalScrollBarSzybTasm->setGeometry(QRect(530, 180, 181, 21));
        horizontalScrollBarSzybTasm->setMaximum(100);
        horizontalScrollBarSzybTasm->setSingleStep(10);
        horizontalScrollBarSzybTasm->setValue(50);
        horizontalScrollBarSzybTasm->setOrientation(Qt::Horizontal);
        pushButtonESTOP = new QPushButton(centralwidget);
        pushButtonESTOP->setObjectName(QStringLiteral("pushButtonESTOP"));
        pushButtonESTOP->setGeometry(QRect(550, 10, 141, 121));
        pushButtonESTOP->setStyleSheet(QLatin1String("#pushButtonESTOP {\n"
"background-color: transparent;\n"
"border-image: url(:ESTOP.png);\n"
"background: none;\n"
"border: none;\n"
"background-repeat: none;\n"
"}"));
        pushButtonESTOP->setCheckable(false);
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(540, 220, 171, 191));
        verticalLayout_4 = new QVBoxLayout(layoutWidget);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font);
        label->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout_2->addWidget(label);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        horizontalLayout_2->addWidget(label_2);


        verticalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        checkBoxPET = new QCheckBox(layoutWidget);
        checkBoxPET->setObjectName(QStringLiteral("checkBoxPET"));
        checkBoxPET->setFont(font);

        verticalLayout->addWidget(checkBoxPET);

        checkBoxKarton = new QCheckBox(layoutWidget);
        checkBoxKarton->setObjectName(QStringLiteral("checkBoxKarton"));
        checkBoxKarton->setFont(font);

        verticalLayout->addWidget(checkBoxKarton);

        checkBoxHDPE = new QCheckBox(layoutWidget);
        checkBoxHDPE->setObjectName(QStringLiteral("checkBoxHDPE"));
        checkBoxHDPE->setFont(font);

        verticalLayout->addWidget(checkBoxHDPE);

        checkBoxAlum = new QCheckBox(layoutWidget);
        checkBoxAlum->setObjectName(QStringLiteral("checkBoxAlum"));
        checkBoxAlum->setFont(font);

        verticalLayout->addWidget(checkBoxAlum);

        checkBoxNieznany = new QCheckBox(layoutWidget);
        checkBoxNieznany->setObjectName(QStringLiteral("checkBoxNieznany"));
        checkBoxNieznany->setFont(font);

        verticalLayout->addWidget(checkBoxNieznany);


        verticalLayout_2->addLayout(verticalLayout);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        lineEdit_PET = new QLineEdit(layoutWidget);
        lineEdit_PET->setObjectName(QStringLiteral("lineEdit_PET"));
        lineEdit_PET->setLayoutDirection(Qt::RightToLeft);
        lineEdit_PET->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_PET->setReadOnly(true);

        verticalLayout_3->addWidget(lineEdit_PET);

        lineEdit_Karton = new QLineEdit(layoutWidget);
        lineEdit_Karton->setObjectName(QStringLiteral("lineEdit_Karton"));
        lineEdit_Karton->setLayoutDirection(Qt::RightToLeft);
        lineEdit_Karton->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_Karton->setReadOnly(true);

        verticalLayout_3->addWidget(lineEdit_Karton);

        lineEdit_HDPE = new QLineEdit(layoutWidget);
        lineEdit_HDPE->setObjectName(QStringLiteral("lineEdit_HDPE"));
        lineEdit_HDPE->setLayoutDirection(Qt::RightToLeft);
        lineEdit_HDPE->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_HDPE->setReadOnly(true);

        verticalLayout_3->addWidget(lineEdit_HDPE);

        lineEdit_Alum = new QLineEdit(layoutWidget);
        lineEdit_Alum->setObjectName(QStringLiteral("lineEdit_Alum"));
        lineEdit_Alum->setLayoutDirection(Qt::RightToLeft);
        lineEdit_Alum->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_Alum->setReadOnly(true);

        verticalLayout_3->addWidget(lineEdit_Alum);

        lineEdit_Nieznany = new QLineEdit(layoutWidget);
        lineEdit_Nieznany->setObjectName(QStringLiteral("lineEdit_Nieznany"));
        lineEdit_Nieznany->setLayoutDirection(Qt::RightToLeft);
        lineEdit_Nieznany->setAutoFillBackground(false);
        lineEdit_Nieznany->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_Nieznany->setReadOnly(true);

        verticalLayout_3->addWidget(lineEdit_Nieznany);


        horizontalLayout->addLayout(verticalLayout_3);


        verticalLayout_4->addLayout(horizontalLayout);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 501, 411));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label_SzybTasm->setText(QApplication::translate("MainWindow", "Szybko\305\233\304\207 ta\305\233moci\304\205gu", Q_NULLPTR));
        pushButtonESTOP->setText(QString());
        label->setText(QApplication::translate("MainWindow", " Materia\305\202", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "  Licznik kg", Q_NULLPTR));
        checkBoxPET->setText(QApplication::translate("MainWindow", "PET", Q_NULLPTR));
        checkBoxKarton->setText(QApplication::translate("MainWindow", "Karton", Q_NULLPTR));
        checkBoxHDPE->setText(QApplication::translate("MainWindow", "HDPE", Q_NULLPTR));
        checkBoxAlum->setText(QApplication::translate("MainWindow", "Alum.", Q_NULLPTR));
        checkBoxNieznany->setText(QApplication::translate("MainWindow", "Nieznany", Q_NULLPTR));
        lineEdit_PET->setText(QString());
        lineEdit_Karton->setText(QString());
        lineEdit_HDPE->setText(QString());
        lineEdit_Alum->setText(QString());
        lineEdit_Nieznany->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
