/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNovo;
    QAction *actionAbrir;
    QAction *actionGuardar;
    QAction *actionAcerca;
    QAction *actionSair;
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit;
    QTreeWidget *treeWidget;
    QWidget *tab_2;
    QFormLayout *formLayout;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_10;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QWidget *tab_3;
    QFormLayout *formLayout_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit_6;
    QLabel *label;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_8;
    QLineEdit *lineEdit_9;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_3;
    QWidget *tab_5;
    QFormLayout *formLayout_3;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_9;
    QLineEdit *lineEdit_12;
    QLineEdit *lineEdit_13;
    QLineEdit *lineEdit_14;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_4;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_11;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_10;
    QLineEdit *lineEdit_11;
    QLineEdit *lineEdit_15;
    QLineEdit *lineEdit_16;
    QLineEdit *lineEdit_21;
    QLineEdit *lineEdit_17;
    QLineEdit *lineEdit_18;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_12;
    QWidget *tab_7;
    QGridLayout *gridLayout_5;
    QVBoxLayout *verticalLayout_9;
    QTreeWidget *treeWidget_4;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *pushButton_7;
    QWidget *tab_6;
    QGridLayout *gridLayout_3;
    QSplitter *splitter;
    QListWidget *listWidget;
    QTreeWidget *treeWidget_2;
    QWidget *tab_4;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout;
    QTreeWidget *treeWidget_3;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_4;
    QLabel *label_5;
    QSlider *horizontalSlider;
    QWidget *tab_8;
    QFormLayout *formLayout_4;
    QLabel *label_8;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_6;
    QLineEdit *lineEdit_19;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QLineEdit *lineEdit_20;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_13;
    QLineEdit *lineEdit_22;
    QHBoxLayout *horizontalLayout_9;
    QCheckBox *checkBox;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButton_3;
    QMenuBar *menuBar;
    QMenu *menuFicheiro;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(720, 480);
        actionNovo = new QAction(MainWindow);
        actionNovo->setObjectName(QStringLiteral("actionNovo"));
        actionAbrir = new QAction(MainWindow);
        actionAbrir->setObjectName(QStringLiteral("actionAbrir"));
        actionGuardar = new QAction(MainWindow);
        actionGuardar->setObjectName(QStringLiteral("actionGuardar"));
        actionAcerca = new QAction(MainWindow);
        actionAcerca->setObjectName(QStringLiteral("actionAcerca"));
        actionSair = new QAction(MainWindow);
        actionSair->setObjectName(QStringLiteral("actionSair"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 721, 451));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lineEdit = new QLineEdit(tab);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        treeWidget = new QTreeWidget(tab);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));

        verticalLayout->addWidget(treeWidget);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        formLayout = new QFormLayout(tab_2);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        lineEdit_2 = new QLineEdit(tab_2);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setClearButtonEnabled(false);

        verticalLayout_2->addWidget(lineEdit_2);

        lineEdit_3 = new QLineEdit(tab_2);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        verticalLayout_2->addWidget(lineEdit_3);

        lineEdit_4 = new QLineEdit(tab_2);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));

        verticalLayout_2->addWidget(lineEdit_4);

        lineEdit_5 = new QLineEdit(tab_2);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));

        verticalLayout_2->addWidget(lineEdit_5);

        lineEdit_10 = new QLineEdit(tab_2);
        lineEdit_10->setObjectName(QStringLiteral("lineEdit_10"));

        verticalLayout_2->addWidget(lineEdit_10);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton = new QPushButton(tab_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout);

        label_2 = new QLabel(tab_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setStyleSheet(QStringLiteral("QLabel { color : red; }"));

        verticalLayout_2->addWidget(label_2);


        formLayout->setLayout(0, QFormLayout::SpanningRole, verticalLayout_2);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        formLayout_2 = new QFormLayout(tab_3);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lineEdit_6 = new QLineEdit(tab_3);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));

        horizontalLayout_2->addWidget(lineEdit_6);

        label = new QLabel(tab_3);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        lineEdit_7 = new QLineEdit(tab_3);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));

        horizontalLayout_2->addWidget(lineEdit_7);


        verticalLayout_3->addLayout(horizontalLayout_2);

        lineEdit_8 = new QLineEdit(tab_3);
        lineEdit_8->setObjectName(QStringLiteral("lineEdit_8"));

        verticalLayout_3->addWidget(lineEdit_8);

        lineEdit_9 = new QLineEdit(tab_3);
        lineEdit_9->setObjectName(QStringLiteral("lineEdit_9"));

        verticalLayout_3->addWidget(lineEdit_9);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        pushButton_2 = new QPushButton(tab_3);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_3->addWidget(pushButton_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_3);

        label_3 = new QLabel(tab_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setStyleSheet(QStringLiteral("QLabel { color : red; }"));

        verticalLayout_3->addWidget(label_3);


        formLayout_2->setLayout(0, QFormLayout::SpanningRole, verticalLayout_3);

        tabWidget->addTab(tab_3, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        formLayout_3 = new QFormLayout(tab_5);
        formLayout_3->setSpacing(6);
        formLayout_3->setContentsMargins(11, 11, 11, 11);
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_9 = new QLabel(tab_5);
        label_9->setObjectName(QStringLiteral("label_9"));

        verticalLayout_4->addWidget(label_9);

        lineEdit_12 = new QLineEdit(tab_5);
        lineEdit_12->setObjectName(QStringLiteral("lineEdit_12"));

        verticalLayout_4->addWidget(lineEdit_12);

        lineEdit_13 = new QLineEdit(tab_5);
        lineEdit_13->setObjectName(QStringLiteral("lineEdit_13"));

        verticalLayout_4->addWidget(lineEdit_13);

        lineEdit_14 = new QLineEdit(tab_5);
        lineEdit_14->setObjectName(QStringLiteral("lineEdit_14"));

        verticalLayout_4->addWidget(lineEdit_14);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        pushButton_4 = new QPushButton(tab_5);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout_4->addWidget(pushButton_4);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        verticalLayout_4->addLayout(horizontalLayout_4);

        label_11 = new QLabel(tab_5);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setStyleSheet(QStringLiteral("QLabel{ color : red;}"));

        verticalLayout_4->addWidget(label_11);


        verticalLayout_6->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        label_10 = new QLabel(tab_5);
        label_10->setObjectName(QStringLiteral("label_10"));

        verticalLayout_5->addWidget(label_10);

        lineEdit_11 = new QLineEdit(tab_5);
        lineEdit_11->setObjectName(QStringLiteral("lineEdit_11"));

        verticalLayout_5->addWidget(lineEdit_11);

        lineEdit_15 = new QLineEdit(tab_5);
        lineEdit_15->setObjectName(QStringLiteral("lineEdit_15"));

        verticalLayout_5->addWidget(lineEdit_15);

        lineEdit_16 = new QLineEdit(tab_5);
        lineEdit_16->setObjectName(QStringLiteral("lineEdit_16"));

        verticalLayout_5->addWidget(lineEdit_16);

        lineEdit_21 = new QLineEdit(tab_5);
        lineEdit_21->setObjectName(QStringLiteral("lineEdit_21"));

        verticalLayout_5->addWidget(lineEdit_21);

        lineEdit_17 = new QLineEdit(tab_5);
        lineEdit_17->setObjectName(QStringLiteral("lineEdit_17"));

        verticalLayout_5->addWidget(lineEdit_17);

        lineEdit_18 = new QLineEdit(tab_5);
        lineEdit_18->setObjectName(QStringLiteral("lineEdit_18"));

        verticalLayout_5->addWidget(lineEdit_18);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        pushButton_5 = new QPushButton(tab_5);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        horizontalLayout_5->addWidget(pushButton_5);

        pushButton_6 = new QPushButton(tab_5);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        horizontalLayout_5->addWidget(pushButton_6);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);


        verticalLayout_5->addLayout(horizontalLayout_5);

        label_12 = new QLabel(tab_5);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setStyleSheet(QStringLiteral("QLabel {color: red;}"));

        verticalLayout_5->addWidget(label_12);


        verticalLayout_6->addLayout(verticalLayout_5);


        formLayout_3->setLayout(0, QFormLayout::SpanningRole, verticalLayout_6);

        tabWidget->addTab(tab_5, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QStringLiteral("tab_7"));
        gridLayout_5 = new QGridLayout(tab_7);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        treeWidget_4 = new QTreeWidget(tab_7);
        treeWidget_4->setObjectName(QStringLiteral("treeWidget_4"));

        verticalLayout_9->addWidget(treeWidget_4);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_6);

        pushButton_7 = new QPushButton(tab_7);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        horizontalLayout_10->addWidget(pushButton_7);


        verticalLayout_9->addLayout(horizontalLayout_10);


        gridLayout_5->addLayout(verticalLayout_9, 0, 0, 1, 1);

        tabWidget->addTab(tab_7, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        gridLayout_3 = new QGridLayout(tab_6);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        splitter = new QSplitter(tab_6);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        listWidget = new QListWidget(splitter);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setSortingEnabled(true);
        splitter->addWidget(listWidget);
        treeWidget_2 = new QTreeWidget(splitter);
        treeWidget_2->setObjectName(QStringLiteral("treeWidget_2"));
        treeWidget_2->setSortingEnabled(true);
        splitter->addWidget(treeWidget_2);

        gridLayout_3->addWidget(splitter, 0, 0, 1, 1);

        tabWidget->addTab(tab_6, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        gridLayout_4 = new QGridLayout(tab_4);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        treeWidget_3 = new QTreeWidget(tab_4);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("Produto"));
        treeWidget_3->setHeaderItem(__qtreewidgetitem);
        treeWidget_3->setObjectName(QStringLiteral("treeWidget_3"));

        gridLayout->addWidget(treeWidget_3, 0, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        label_4 = new QLabel(tab_4);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_7->addWidget(label_4);

        label_5 = new QLabel(tab_4);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout_7->addWidget(label_5);


        horizontalLayout_6->addLayout(verticalLayout_7);

        horizontalSlider = new QSlider(tab_4);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setMaximum(119);
        horizontalSlider->setSingleStep(1);
        horizontalSlider->setSliderPosition(119);
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_6->addWidget(horizontalSlider);


        gridLayout->addLayout(horizontalLayout_6, 1, 0, 1, 1);


        gridLayout_4->addLayout(gridLayout, 0, 0, 1, 1);

        tabWidget->addTab(tab_4, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName(QStringLiteral("tab_8"));
        formLayout_4 = new QFormLayout(tab_8);
        formLayout_4->setSpacing(6);
        formLayout_4->setContentsMargins(11, 11, 11, 11);
        formLayout_4->setObjectName(QStringLiteral("formLayout_4"));
        label_8 = new QLabel(tab_8);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setStyleSheet(QStringLiteral("QLabel {color:red;}"));

        formLayout_4->setWidget(1, QFormLayout::LabelRole, label_8);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_6 = new QLabel(tab_8);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_8->addWidget(label_6);

        lineEdit_19 = new QLineEdit(tab_8);
        lineEdit_19->setObjectName(QStringLiteral("lineEdit_19"));

        horizontalLayout_8->addWidget(lineEdit_19);


        verticalLayout_8->addLayout(horizontalLayout_8);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_7 = new QLabel(tab_8);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_7->addWidget(label_7);

        lineEdit_20 = new QLineEdit(tab_8);
        lineEdit_20->setObjectName(QStringLiteral("lineEdit_20"));

        horizontalLayout_7->addWidget(lineEdit_20);


        verticalLayout_8->addLayout(horizontalLayout_7);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_13 = new QLabel(tab_8);
        label_13->setObjectName(QStringLiteral("label_13"));

        horizontalLayout_11->addWidget(label_13);

        lineEdit_22 = new QLineEdit(tab_8);
        lineEdit_22->setObjectName(QStringLiteral("lineEdit_22"));

        horizontalLayout_11->addWidget(lineEdit_22);


        verticalLayout_8->addLayout(horizontalLayout_11);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        checkBox = new QCheckBox(tab_8);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        horizontalLayout_9->addWidget(checkBox);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_5);

        pushButton_3 = new QPushButton(tab_8);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_9->addWidget(pushButton_3);


        verticalLayout_8->addLayout(horizontalLayout_9);


        formLayout_4->setLayout(0, QFormLayout::SpanningRole, verticalLayout_8);

        tabWidget->addTab(tab_8, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 720, 21));
        menuFicheiro = new QMenu(menuBar);
        menuFicheiro->setObjectName(QStringLiteral("menuFicheiro"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFicheiro->menuAction());
        menuFicheiro->addAction(actionNovo);
        menuFicheiro->addAction(actionAbrir);
        menuFicheiro->addAction(actionGuardar);
        menuFicheiro->addAction(actionAcerca);
        menuFicheiro->addAction(actionSair);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Projeto", 0));
        actionNovo->setText(QApplication::translate("MainWindow", "Novo", 0));
        actionAbrir->setText(QApplication::translate("MainWindow", "Abrir", 0));
        actionGuardar->setText(QApplication::translate("MainWindow", "Guardar", 0));
        actionAcerca->setText(QApplication::translate("MainWindow", "Acerca", 0));
        actionSair->setText(QApplication::translate("MainWindow", "Sair", 0));
        lineEdit->setPlaceholderText(QApplication::translate("MainWindow", "Procura", 0));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("MainWindow", "C\303\263digo", 0));
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "Produtos", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Invent\303\241rio", 0));
        lineEdit_2->setPlaceholderText(QApplication::translate("MainWindow", "Nome", 0));
        lineEdit_3->setPlaceholderText(QApplication::translate("MainWindow", "Codigo", 0));
        lineEdit_4->setPlaceholderText(QApplication::translate("MainWindow", "Pre\303\247o", 0));
        lineEdit_5->setPlaceholderText(QApplication::translate("MainWindow", "Quantidade", 0));
        lineEdit_10->setPlaceholderText(QApplication::translate("MainWindow", "Fornecedor", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Comprar", 0));
        label_2->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Compra", 0));
        lineEdit_6->setPlaceholderText(QApplication::translate("MainWindow", "Nome", 0));
        label->setText(QApplication::translate("MainWindow", "ou", 0));
        lineEdit_7->setPlaceholderText(QApplication::translate("MainWindow", "Codigo", 0));
        lineEdit_8->setPlaceholderText(QApplication::translate("MainWindow", "Pre\303\247o", 0));
        lineEdit_9->setPlaceholderText(QApplication::translate("MainWindow", "Quantidade", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Vender", 0));
        label_3->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Venda", 0));
        label_9->setText(QApplication::translate("MainWindow", "Fornecedores", 0));
        lineEdit_12->setPlaceholderText(QApplication::translate("MainWindow", "Nome", 0));
        lineEdit_13->setPlaceholderText(QApplication::translate("MainWindow", "Morada", 0));
        lineEdit_14->setPlaceholderText(QApplication::translate("MainWindow", "Telefone", 0));
        pushButton_4->setText(QApplication::translate("MainWindow", "Inserir", 0));
        label_11->setText(QString());
        label_10->setText(QApplication::translate("MainWindow", "Editar Itens por nome", 0));
        lineEdit_11->setPlaceholderText(QApplication::translate("MainWindow", "Nome", 0));
        lineEdit_15->setPlaceholderText(QApplication::translate("MainWindow", "C\303\263digo", 0));
        lineEdit_16->setPlaceholderText(QApplication::translate("MainWindow", "Pre\303\247o", 0));
        lineEdit_21->setPlaceholderText(QApplication::translate("MainWindow", "Pre\303\247o de Venda", 0));
        lineEdit_17->setPlaceholderText(QApplication::translate("MainWindow", "Quantidadde", 0));
        lineEdit_18->setPlaceholderText(QApplication::translate("MainWindow", "Fornecedor", 0));
        pushButton_5->setText(QApplication::translate("MainWindow", "Editar", 0));
        pushButton_6->setText(QApplication::translate("MainWindow", "Apagar", 0));
        label_12->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("MainWindow", "Editar", 0));
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget_4->headerItem();
        ___qtreewidgetitem1->setText(2, QApplication::translate("MainWindow", "Quantidade Necess\303\241ria", 0));
        ___qtreewidgetitem1->setText(1, QApplication::translate("MainWindow", "Quantidade", 0));
        ___qtreewidgetitem1->setText(0, QApplication::translate("MainWindow", "Produto", 0));
        pushButton_7->setText(QApplication::translate("MainWindow", "Comprar", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_7), QApplication::translate("MainWindow", "Alertas", 0));
        QTreeWidgetItem *___qtreewidgetitem2 = treeWidget_2->headerItem();
        ___qtreewidgetitem2->setText(3, QApplication::translate("MainWindow", "Diferen\303\247a", 0));
        ___qtreewidgetitem2->setText(2, QApplication::translate("MainWindow", "Pre\303\247o de venda", 0));
        ___qtreewidgetitem2->setText(1, QApplication::translate("MainWindow", "Pre\303\247o de compra", 0));
        ___qtreewidgetitem2->setText(0, QApplication::translate("MainWindow", "Produto", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QApplication::translate("MainWindow", "Estatisticas por fornecedor", 0));
        QTreeWidgetItem *___qtreewidgetitem3 = treeWidget_3->headerItem();
        ___qtreewidgetitem3->setText(3, QApplication::translate("MainWindow", "Diferen\303\247a", 0));
        ___qtreewidgetitem3->setText(2, QApplication::translate("MainWindow", "Pre\303\247o de venda", 0));
        ___qtreewidgetitem3->setText(1, QApplication::translate("MainWindow", "Pre\303\247o de compra", 0));
        label_4->setText(QApplication::translate("MainWindow", "Periodo de tempo:", 0));
        label_5->setText(QApplication::translate("MainWindow", "M\303\252s", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "Fatura\303\247\303\243o", 0));
        label_8->setText(QString());
        label_6->setText(QApplication::translate("MainWindow", "Stock min", 0));
        label_7->setText(QApplication::translate("MainWindow", "Stock max", 0));
        label_13->setText(QApplication::translate("MainWindow", "IVA", 0));
        checkBox->setText(QApplication::translate("MainWindow", "Alertas autom\303\241ticos", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "Aplicar", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_8), QApplication::translate("MainWindow", "Configura\303\247\303\243o", 0));
        menuFicheiro->setTitle(QApplication::translate("MainWindow", "Ficheiro", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
