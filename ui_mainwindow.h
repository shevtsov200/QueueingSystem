/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QSpinBox *requestsSpinBox;
    QSpinBox *bufferSpinBox;
    QSpinBox *clientsSpinBox;
    QSpinBox *serversSpinBox;
    QDoubleSpinBox *aDoubleSpinBox;
    QDoubleSpinBox *bDoubleSpinBox;
    QDoubleSpinBox *lambdaDoubleSpinBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QPushButton *startButton;
    QMenuBar *menuBar;
    QMenu *menuOptions;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(314, 301);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(70, 10, 171, 228));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        requestsSpinBox = new QSpinBox(widget);
        requestsSpinBox->setObjectName(QStringLiteral("requestsSpinBox"));

        formLayout->setWidget(0, QFormLayout::FieldRole, requestsSpinBox);

        bufferSpinBox = new QSpinBox(widget);
        bufferSpinBox->setObjectName(QStringLiteral("bufferSpinBox"));

        formLayout->setWidget(1, QFormLayout::FieldRole, bufferSpinBox);

        clientsSpinBox = new QSpinBox(widget);
        clientsSpinBox->setObjectName(QStringLiteral("clientsSpinBox"));

        formLayout->setWidget(2, QFormLayout::FieldRole, clientsSpinBox);

        serversSpinBox = new QSpinBox(widget);
        serversSpinBox->setObjectName(QStringLiteral("serversSpinBox"));

        formLayout->setWidget(3, QFormLayout::FieldRole, serversSpinBox);

        aDoubleSpinBox = new QDoubleSpinBox(widget);
        aDoubleSpinBox->setObjectName(QStringLiteral("aDoubleSpinBox"));

        formLayout->setWidget(4, QFormLayout::FieldRole, aDoubleSpinBox);

        bDoubleSpinBox = new QDoubleSpinBox(widget);
        bDoubleSpinBox->setObjectName(QStringLiteral("bDoubleSpinBox"));

        formLayout->setWidget(5, QFormLayout::FieldRole, bDoubleSpinBox);

        lambdaDoubleSpinBox = new QDoubleSpinBox(widget);
        lambdaDoubleSpinBox->setObjectName(QStringLiteral("lambdaDoubleSpinBox"));

        formLayout->setWidget(6, QFormLayout::FieldRole, lambdaDoubleSpinBox);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        label_6 = new QLabel(widget);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_6);

        label_7 = new QLabel(widget);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_7);


        verticalLayout->addLayout(formLayout);

        startButton = new QPushButton(widget);
        startButton->setObjectName(QStringLiteral("startButton"));

        verticalLayout->addWidget(startButton);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 314, 21));
        menuOptions = new QMenu(menuBar);
        menuOptions->setObjectName(QStringLiteral("menuOptions"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuOptions->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "requests", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "buffer", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "clients", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "servers", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "a", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "b", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "lambda", Q_NULLPTR));
        startButton->setText(QApplication::translate("MainWindow", "Start", Q_NULLPTR));
        menuOptions->setTitle(QApplication::translate("MainWindow", "parameters", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
