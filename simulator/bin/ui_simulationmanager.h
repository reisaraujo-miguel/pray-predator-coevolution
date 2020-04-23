/********************************************************************************
** Form generated from reading UI file 'simulationmanager.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULATIONMANAGER_H
#define UI_SIMULATIONMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimulationManager
{
public:
    QPushButton *startButton;

    void setupUi(QWidget *SimulationManager)
    {
        if (SimulationManager->objectName().isEmpty())
            SimulationManager->setObjectName(QString::fromUtf8("SimulationManager"));
        SimulationManager->resize(800, 600);
        startButton = new QPushButton(SimulationManager);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setGeometry(QRect(350, 210, 89, 25));

        retranslateUi(SimulationManager);

        QMetaObject::connectSlotsByName(SimulationManager);
    } // setupUi

    void retranslateUi(QWidget *SimulationManager)
    {
        SimulationManager->setWindowTitle(QApplication::translate("SimulationManager", "SimulationManager", nullptr));
        startButton->setText(QApplication::translate("SimulationManager", "START", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SimulationManager: public Ui_SimulationManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULATIONMANAGER_H
