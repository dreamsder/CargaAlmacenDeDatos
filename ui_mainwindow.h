/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCommandLinkButton>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QCommandLinkButton *btnCargar;
    QLabel *lblVersion;
    QSpinBox *sbMesesADepurar;
    QLabel *lblMesesABorrar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(350, 170);
        MainWindow->setMinimumSize(QSize(350, 170));
        MainWindow->setMaximumSize(QSize(350, 170));
        MainWindow->setBaseSize(QSize(400, 170));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        btnCargar = new QCommandLinkButton(centralWidget);
        btnCargar->setObjectName(QString::fromUtf8("btnCargar"));
        btnCargar->setGeometry(QRect(100, 30, 160, 37));
        btnCargar->setMinimumSize(QSize(0, 37));
        btnCargar->setMaximumSize(QSize(16777215, 37));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(12);
        font.setBold(true);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(75);
        font.setStrikeOut(false);
        font.setKerning(true);
        font.setStyleStrategy(QFont::PreferAntialias);
        btnCargar->setFont(font);
        btnCargar->setCheckable(false);
        lblVersion = new QLabel(centralWidget);
        lblVersion->setObjectName(QString::fromUtf8("lblVersion"));
        lblVersion->setGeometry(QRect(10, 140, 221, 17));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Verdana"));
        font1.setPointSize(9);
        lblVersion->setFont(font1);
        sbMesesADepurar = new QSpinBox(centralWidget);
        sbMesesADepurar->setObjectName(QString::fromUtf8("sbMesesADepurar"));
        sbMesesADepurar->setGeometry(QRect(10, 100, 111, 27));
        sbMesesADepurar->setWrapping(true);
        sbMesesADepurar->setAlignment(Qt::AlignCenter);
        sbMesesADepurar->setReadOnly(false);
        sbMesesADepurar->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        sbMesesADepurar->setAccelerated(true);
        sbMesesADepurar->setMaximum(999);
        sbMesesADepurar->setValue(0);
        lblMesesABorrar = new QLabel(centralWidget);
        lblMesesABorrar->setObjectName(QString::fromUtf8("lblMesesABorrar"));
        lblMesesABorrar->setGeometry(QRect(10, 80, 131, 17));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Proceso de carga de datos desde Madai", 0, QApplication::UnicodeUTF8));
        btnCargar->setText(QApplication::translate("MainWindow", "Cargar Almacen", 0, QApplication::UnicodeUTF8));
        lblVersion->setText(QApplication::translate("MainWindow", "Ver.: 1.6.1", 0, QApplication::UnicodeUTF8));
        lblMesesABorrar->setText(QApplication::translate("MainWindow", "Meses a depurar:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
