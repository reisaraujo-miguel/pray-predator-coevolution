/********************************************************************************
** Form generated from reading UI file 'simulationmanager.ui'
**
** Created by: Qt User Interface Compiler version 5.15.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULATIONMANAGER_H
#define UI_SIMULATIONMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimulationManager
{
public:
    QGroupBox *groupBox;
    QPushButton *importButton;
    QLabel *label;
    QLineEdit *editFileName;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label2;
    QLabel *label6_2;
    QLabel *label4;
    QLabel *label5;
    QLabel *label7;
    QLabel *label9;
    QLabel *label8;
    QLabel *label6;
    QLabel *label3;
    QLineEdit *editHerCarn;
    QLineEdit *editHurt;
    QLineEdit *editHerHerb;
    QLineEdit *editCarn;
    QLineEdit *editHealth;
    QLineEdit *editPlants;
    QLineEdit *editHerb;
    QLineEdit *editGen;
    QLineEdit *editFrames;
    QWidget *tab_2;
    QLabel *label_2;
    QGroupBox *groupBox_2;
    QLabel *label_3;
    QSpinBox *chooseGen;
    QLabel *label_4;
    QSpinBox *frameRate;
    QCheckBox *loop;
    QCheckBox *progress;
    QCheckBox *simulate;
    QLabel *label_5;
    QTabWidget *tabWidget_2;
    QWidget *tab_3;
    QLabel *label_6;
    QSpinBox *chooseHerb;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_12;
    QLabel *label_11;
    QLabel *label_10;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLineEdit *herbPlantConst;
    QLineEdit *herbHerbConst;
    QLineEdit *herbCarnConst;
    QLineEdit *herbCarnWeight;
    QLineEdit *herbHerbWeight;
    QLineEdit *herbPlantWeight;
    QLineEdit *herbHurt;
    QLineEdit *herbEnergy;
    QLineEdit *herbHealth;
    QLineEdit *herbHeight;
    QLabel *label_17;
    QLineEdit *herbSpeed;
    QWidget *tab_4;
    QLineEdit *carnPlantWeight;
    QLabel *label_18;
    QLabel *label_19;
    QLineEdit *carnPlantConst;
    QLineEdit *carnCarnWeight;
    QLabel *label_20;
    QLabel *label_21;
    QLabel *label_22;
    QLineEdit *carnHerbWeight;
    QLineEdit *carnCarnConst;
    QLineEdit *carnHeight;
    QLabel *label_23;
    QSpinBox *chooseCarn;
    QLabel *label_24;
    QLabel *label_25;
    QLineEdit *carnHerbConst;
    QLineEdit *carnEnergy;
    QLabel *label_26;
    QLineEdit *carnSpeed;
    QLabel *label_27;

    void setupUi(QWidget *SimulationManager)
    {
        if (SimulationManager->objectName().isEmpty())
            SimulationManager->setObjectName(QString::fromUtf8("SimulationManager"));
        SimulationManager->resize(623, 632);
        groupBox = new QGroupBox(SimulationManager);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(30, 30, 241, 101));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        groupBox->setFont(font);
        groupBox->setAlignment(Qt::AlignCenter);
        importButton = new QPushButton(groupBox);
        importButton->setObjectName(QString::fromUtf8("importButton"));
        importButton->setGeometry(QRect(10, 30, 89, 25));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        importButton->setFont(font1);
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 70, 81, 17));
        label->setFont(font1);
        editFileName = new QLineEdit(groupBox);
        editFileName->setObjectName(QString::fromUtf8("editFileName"));
        editFileName->setGeometry(QRect(100, 70, 131, 25));
        editFileName->setFont(font1);
        tabWidget = new QTabWidget(SimulationManager);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(30, 270, 241, 271));
        tabWidget->setFont(font);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        label2 = new QLabel(tab);
        label2->setObjectName(QString::fromUtf8("label2"));
        label2->setGeometry(QRect(10, 30, 131, 17));
        label2->setFont(font1);
        label6_2 = new QLabel(tab);
        label6_2->setObjectName(QString::fromUtf8("label6_2"));
        label6_2->setGeometry(QRect(10, 130, 131, 17));
        label6_2->setFont(font1);
        label4 = new QLabel(tab);
        label4->setObjectName(QString::fromUtf8("label4"));
        label4->setGeometry(QRect(10, 70, 131, 17));
        label4->setFont(font1);
        label5 = new QLabel(tab);
        label5->setObjectName(QString::fromUtf8("label5"));
        label5->setGeometry(QRect(10, 90, 131, 17));
        label5->setFont(font1);
        label7 = new QLabel(tab);
        label7->setObjectName(QString::fromUtf8("label7"));
        label7->setGeometry(QRect(10, 150, 141, 17));
        label7->setFont(font1);
        label9 = new QLabel(tab);
        label9->setObjectName(QString::fromUtf8("label9"));
        label9->setGeometry(QRect(10, 190, 131, 17));
        label9->setFont(font1);
        label8 = new QLabel(tab);
        label8->setObjectName(QString::fromUtf8("label8"));
        label8->setGeometry(QRect(10, 170, 131, 17));
        label8->setFont(font1);
        label6 = new QLabel(tab);
        label6->setObjectName(QString::fromUtf8("label6"));
        label6->setGeometry(QRect(10, 110, 131, 17));
        label6->setFont(font1);
        label3 = new QLabel(tab);
        label3->setObjectName(QString::fromUtf8("label3"));
        label3->setGeometry(QRect(10, 50, 131, 17));
        label3->setFont(font1);
        editHerCarn = new QLineEdit(tab);
        editHerCarn->setObjectName(QString::fromUtf8("editHerCarn"));
        editHerCarn->setGeometry(QRect(170, 130, 51, 21));
        editHerCarn->setFont(font1);
        editHerCarn->setReadOnly(true);
        editHurt = new QLineEdit(tab);
        editHurt->setObjectName(QString::fromUtf8("editHurt"));
        editHurt->setGeometry(QRect(170, 190, 51, 21));
        editHurt->setFont(font1);
        editHurt->setReadOnly(true);
        editHerHerb = new QLineEdit(tab);
        editHerHerb->setObjectName(QString::fromUtf8("editHerHerb"));
        editHerHerb->setGeometry(QRect(170, 110, 51, 21));
        editHerHerb->setFont(font1);
        editHerHerb->setReadOnly(true);
        editCarn = new QLineEdit(tab);
        editCarn->setObjectName(QString::fromUtf8("editCarn"));
        editCarn->setGeometry(QRect(170, 50, 51, 21));
        editCarn->setFont(font1);
        editCarn->setReadOnly(true);
        editHealth = new QLineEdit(tab);
        editHealth->setObjectName(QString::fromUtf8("editHealth"));
        editHealth->setGeometry(QRect(170, 170, 51, 21));
        editHealth->setFont(font1);
        editHealth->setReadOnly(true);
        editPlants = new QLineEdit(tab);
        editPlants->setObjectName(QString::fromUtf8("editPlants"));
        editPlants->setGeometry(QRect(170, 70, 51, 21));
        editPlants->setFont(font1);
        editPlants->setReadOnly(true);
        editHerb = new QLineEdit(tab);
        editHerb->setObjectName(QString::fromUtf8("editHerb"));
        editHerb->setGeometry(QRect(170, 30, 51, 21));
        editHerb->setFont(font1);
        editHerb->setReadOnly(true);
        editGen = new QLineEdit(tab);
        editGen->setObjectName(QString::fromUtf8("editGen"));
        editGen->setGeometry(QRect(170, 90, 51, 21));
        editGen->setFont(font1);
        editGen->setReadOnly(true);
        editFrames = new QLineEdit(tab);
        editFrames->setObjectName(QString::fromUtf8("editFrames"));
        editFrames->setGeometry(QRect(170, 150, 51, 21));
        editFrames->setFont(font1);
        editFrames->setReadOnly(true);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());
        label_2 = new QLabel(SimulationManager);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(60, 240, 181, 20));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);
        groupBox_2 = new QGroupBox(SimulationManager);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(350, 30, 241, 181));
        groupBox_2->setFont(font);
        groupBox_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 40, 91, 17));
        label_3->setFont(font1);
        chooseGen = new QSpinBox(groupBox_2);
        chooseGen->setObjectName(QString::fromUtf8("chooseGen"));
        chooseGen->setGeometry(QRect(151, 40, 71, 26));
        chooseGen->setFont(font1);
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 80, 161, 17));
        label_4->setFont(font1);
        frameRate = new QSpinBox(groupBox_2);
        frameRate->setObjectName(QString::fromUtf8("frameRate"));
        frameRate->setGeometry(QRect(151, 80, 71, 26));
        frameRate->setFont(font1);
        frameRate->setMaximum(1000);
        loop = new QCheckBox(groupBox_2);
        loop->setObjectName(QString::fromUtf8("loop"));
        loop->setGeometry(QRect(130, 120, 92, 23));
        loop->setFont(font1);
        loop->setChecked(true);
        progress = new QCheckBox(groupBox_2);
        progress->setObjectName(QString::fromUtf8("progress"));
        progress->setGeometry(QRect(130, 150, 92, 23));
        progress->setFont(font1);
        progress->setChecked(false);
        simulate = new QCheckBox(groupBox_2);
        simulate->setObjectName(QString::fromUtf8("simulate"));
        simulate->setGeometry(QRect(10, 120, 92, 23));
        simulate->setFont(font);
        label_5 = new QLabel(SimulationManager);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(370, 240, 181, 20));
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignCenter);
        tabWidget_2 = new QTabWidget(SimulationManager);
        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
        tabWidget_2->setGeometry(QRect(350, 270, 241, 351));
        tabWidget_2->setFont(font);
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        label_6 = new QLabel(tab_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 10, 91, 17));
        label_6->setFont(font1);
        chooseHerb = new QSpinBox(tab_3);
        chooseHerb->setObjectName(QString::fromUtf8("chooseHerb"));
        chooseHerb->setGeometry(QRect(170, 10, 42, 26));
        chooseHerb->setFont(font1);
        label_7 = new QLabel(tab_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 50, 111, 17));
        label_7->setFont(font1);
        label_8 = new QLabel(tab_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 70, 141, 17));
        label_8->setFont(font1);
        label_9 = new QLabel(tab_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 90, 141, 17));
        label_9->setFont(font1);
        label_12 = new QLabel(tab_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(10, 160, 141, 17));
        label_12->setFont(font1);
        label_11 = new QLabel(tab_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 120, 111, 17));
        label_11->setFont(font1);
        label_10 = new QLabel(tab_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 140, 141, 17));
        label_10->setFont(font1);
        label_13 = new QLabel(tab_3);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 190, 141, 17));
        label_13->setFont(font1);
        label_14 = new QLabel(tab_3);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 250, 141, 17));
        label_14->setFont(font1);
        label_15 = new QLabel(tab_3);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(10, 270, 141, 17));
        label_15->setFont(font1);
        label_16 = new QLabel(tab_3);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(10, 290, 141, 17));
        label_16->setFont(font1);
        herbPlantConst = new QLineEdit(tab_3);
        herbPlantConst->setObjectName(QString::fromUtf8("herbPlantConst"));
        herbPlantConst->setGeometry(QRect(170, 50, 51, 21));
        herbPlantConst->setFont(font1);
        herbPlantConst->setReadOnly(true);
        herbHerbConst = new QLineEdit(tab_3);
        herbHerbConst->setObjectName(QString::fromUtf8("herbHerbConst"));
        herbHerbConst->setGeometry(QRect(170, 70, 51, 21));
        herbHerbConst->setFont(font1);
        herbHerbConst->setReadOnly(true);
        herbCarnConst = new QLineEdit(tab_3);
        herbCarnConst->setObjectName(QString::fromUtf8("herbCarnConst"));
        herbCarnConst->setGeometry(QRect(170, 90, 51, 21));
        herbCarnConst->setFont(font1);
        herbCarnConst->setReadOnly(true);
        herbCarnWeight = new QLineEdit(tab_3);
        herbCarnWeight->setObjectName(QString::fromUtf8("herbCarnWeight"));
        herbCarnWeight->setGeometry(QRect(170, 160, 51, 21));
        herbCarnWeight->setFont(font1);
        herbCarnWeight->setReadOnly(true);
        herbHerbWeight = new QLineEdit(tab_3);
        herbHerbWeight->setObjectName(QString::fromUtf8("herbHerbWeight"));
        herbHerbWeight->setGeometry(QRect(170, 140, 51, 21));
        herbHerbWeight->setFont(font1);
        herbHerbWeight->setReadOnly(true);
        herbPlantWeight = new QLineEdit(tab_3);
        herbPlantWeight->setObjectName(QString::fromUtf8("herbPlantWeight"));
        herbPlantWeight->setGeometry(QRect(170, 120, 51, 21));
        herbPlantWeight->setFont(font1);
        herbPlantWeight->setReadOnly(true);
        herbHurt = new QLineEdit(tab_3);
        herbHurt->setObjectName(QString::fromUtf8("herbHurt"));
        herbHurt->setGeometry(QRect(170, 270, 51, 21));
        herbHurt->setFont(font1);
        herbHurt->setReadOnly(true);
        herbEnergy = new QLineEdit(tab_3);
        herbEnergy->setObjectName(QString::fromUtf8("herbEnergy"));
        herbEnergy->setGeometry(QRect(170, 290, 51, 21));
        herbEnergy->setFont(font1);
        herbEnergy->setReadOnly(true);
        herbHealth = new QLineEdit(tab_3);
        herbHealth->setObjectName(QString::fromUtf8("herbHealth"));
        herbHealth->setGeometry(QRect(170, 250, 51, 21));
        herbHealth->setFont(font1);
        herbHealth->setReadOnly(true);
        herbHeight = new QLineEdit(tab_3);
        herbHeight->setObjectName(QString::fromUtf8("herbHeight"));
        herbHeight->setGeometry(QRect(170, 190, 51, 21));
        herbHeight->setFont(font1);
        herbHeight->setReadOnly(true);
        label_17 = new QLabel(tab_3);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(10, 220, 141, 17));
        label_17->setFont(font1);
        herbSpeed = new QLineEdit(tab_3);
        herbSpeed->setObjectName(QString::fromUtf8("herbSpeed"));
        herbSpeed->setGeometry(QRect(170, 220, 51, 21));
        herbSpeed->setFont(font1);
        herbSpeed->setReadOnly(true);
        tabWidget_2->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        carnPlantWeight = new QLineEdit(tab_4);
        carnPlantWeight->setObjectName(QString::fromUtf8("carnPlantWeight"));
        carnPlantWeight->setGeometry(QRect(170, 120, 51, 21));
        carnPlantWeight->setFont(font1);
        carnPlantWeight->setReadOnly(true);
        label_18 = new QLabel(tab_4);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(10, 140, 141, 17));
        label_18->setFont(font1);
        label_19 = new QLabel(tab_4);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(10, 50, 111, 17));
        label_19->setFont(font1);
        carnPlantConst = new QLineEdit(tab_4);
        carnPlantConst->setObjectName(QString::fromUtf8("carnPlantConst"));
        carnPlantConst->setGeometry(QRect(170, 50, 51, 21));
        carnPlantConst->setFont(font1);
        carnPlantConst->setReadOnly(true);
        carnCarnWeight = new QLineEdit(tab_4);
        carnCarnWeight->setObjectName(QString::fromUtf8("carnCarnWeight"));
        carnCarnWeight->setGeometry(QRect(170, 160, 51, 21));
        carnCarnWeight->setFont(font1);
        carnCarnWeight->setReadOnly(true);
        label_20 = new QLabel(tab_4);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(10, 120, 111, 17));
        label_20->setFont(font1);
        label_21 = new QLabel(tab_4);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(10, 160, 141, 17));
        label_21->setFont(font1);
        label_22 = new QLabel(tab_4);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(10, 10, 91, 17));
        label_22->setFont(font1);
        carnHerbWeight = new QLineEdit(tab_4);
        carnHerbWeight->setObjectName(QString::fromUtf8("carnHerbWeight"));
        carnHerbWeight->setGeometry(QRect(170, 140, 51, 21));
        carnHerbWeight->setFont(font1);
        carnHerbWeight->setReadOnly(true);
        carnCarnConst = new QLineEdit(tab_4);
        carnCarnConst->setObjectName(QString::fromUtf8("carnCarnConst"));
        carnCarnConst->setGeometry(QRect(170, 90, 51, 21));
        carnCarnConst->setFont(font1);
        carnCarnConst->setReadOnly(true);
        carnHeight = new QLineEdit(tab_4);
        carnHeight->setObjectName(QString::fromUtf8("carnHeight"));
        carnHeight->setGeometry(QRect(170, 190, 51, 21));
        carnHeight->setFont(font1);
        carnHeight->setReadOnly(true);
        label_23 = new QLabel(tab_4);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(10, 70, 141, 17));
        label_23->setFont(font1);
        chooseCarn = new QSpinBox(tab_4);
        chooseCarn->setObjectName(QString::fromUtf8("chooseCarn"));
        chooseCarn->setGeometry(QRect(170, 10, 42, 26));
        chooseCarn->setFont(font1);
        label_24 = new QLabel(tab_4);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(10, 190, 141, 17));
        label_24->setFont(font1);
        label_25 = new QLabel(tab_4);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(10, 250, 141, 17));
        label_25->setFont(font1);
        carnHerbConst = new QLineEdit(tab_4);
        carnHerbConst->setObjectName(QString::fromUtf8("carnHerbConst"));
        carnHerbConst->setGeometry(QRect(170, 70, 51, 21));
        carnHerbConst->setFont(font1);
        carnHerbConst->setReadOnly(true);
        carnEnergy = new QLineEdit(tab_4);
        carnEnergy->setObjectName(QString::fromUtf8("carnEnergy"));
        carnEnergy->setGeometry(QRect(170, 250, 51, 21));
        carnEnergy->setFont(font1);
        carnEnergy->setReadOnly(true);
        label_26 = new QLabel(tab_4);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(10, 90, 141, 17));
        label_26->setFont(font1);
        carnSpeed = new QLineEdit(tab_4);
        carnSpeed->setObjectName(QString::fromUtf8("carnSpeed"));
        carnSpeed->setGeometry(QRect(170, 220, 51, 21));
        carnSpeed->setFont(font1);
        carnSpeed->setReadOnly(true);
        label_27 = new QLabel(tab_4);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(10, 220, 141, 17));
        label_27->setFont(font1);
        tabWidget_2->addTab(tab_4, QString());

        retranslateUi(SimulationManager);

        tabWidget->setCurrentIndex(0);
        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SimulationManager);
    } // setupUi

    void retranslateUi(QWidget *SimulationManager)
    {
        SimulationManager->setWindowTitle(QCoreApplication::translate("SimulationManager", "SimulationManager", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SimulationManager", "File Manager", nullptr));
        importButton->setText(QCoreApplication::translate("SimulationManager", "IMPORT", nullptr));
        label->setText(QCoreApplication::translate("SimulationManager", "File name:", nullptr));
        label2->setText(QCoreApplication::translate("SimulationManager", "Qty herbivores:", nullptr));
        label6_2->setText(QCoreApplication::translate("SimulationManager", "Carnivore heritage:", nullptr));
        label4->setText(QCoreApplication::translate("SimulationManager", "Qty plants:", nullptr));
        label5->setText(QCoreApplication::translate("SimulationManager", "Generations", nullptr));
        label7->setText(QCoreApplication::translate("SimulationManager", "Frames/generation", nullptr));
        label9->setText(QCoreApplication::translate("SimulationManager", "Hurt weight:", nullptr));
        label8->setText(QCoreApplication::translate("SimulationManager", "Health weight:", nullptr));
        label6->setText(QCoreApplication::translate("SimulationManager", "Herbivore heritage:", nullptr));
        label3->setText(QCoreApplication::translate("SimulationManager", "Qty carnivores:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("SimulationManager", "Macros", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("SimulationManager", "Evolution", nullptr));
        label_2->setText(QCoreApplication::translate("SimulationManager", "Genetic algorithm data", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("SimulationManager", "Simulation manager", nullptr));
        label_3->setText(QCoreApplication::translate("SimulationManager", "Generation:", nullptr));
        label_4->setText(QCoreApplication::translate("SimulationManager", "frames/generation:", nullptr));
        loop->setText(QCoreApplication::translate("SimulationManager", "Loop", nullptr));
        progress->setText(QCoreApplication::translate("SimulationManager", "Progress", nullptr));
        simulate->setText(QCoreApplication::translate("SimulationManager", "Simulate", nullptr));
        label_5->setText(QCoreApplication::translate("SimulationManager", "Simulation data", nullptr));
        label_6->setText(QCoreApplication::translate("SimulationManager", "Herbivore:", nullptr));
        label_7->setText(QCoreApplication::translate("SimulationManager", "Plant constant:", nullptr));
        label_8->setText(QCoreApplication::translate("SimulationManager", "Herbivore constant:", nullptr));
        label_9->setText(QCoreApplication::translate("SimulationManager", "Carnivore constant:", nullptr));
        label_12->setText(QCoreApplication::translate("SimulationManager", "Carnivore weight:", nullptr));
        label_11->setText(QCoreApplication::translate("SimulationManager", "Plant weight:", nullptr));
        label_10->setText(QCoreApplication::translate("SimulationManager", "Herbivore weight:", nullptr));
        label_13->setText(QCoreApplication::translate("SimulationManager", "Search height limit:", nullptr));
        label_14->setText(QCoreApplication::translate("SimulationManager", "Health:", nullptr));
        label_15->setText(QCoreApplication::translate("SimulationManager", "Hurt:", nullptr));
        label_16->setText(QCoreApplication::translate("SimulationManager", "Energy:", nullptr));
        label_17->setText(QCoreApplication::translate("SimulationManager", "Speed:", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_3), QCoreApplication::translate("SimulationManager", "Herbivores", nullptr));
        label_18->setText(QCoreApplication::translate("SimulationManager", "Herbivore weight:", nullptr));
        label_19->setText(QCoreApplication::translate("SimulationManager", "Plant constant:", nullptr));
        label_20->setText(QCoreApplication::translate("SimulationManager", "Plant weight:", nullptr));
        label_21->setText(QCoreApplication::translate("SimulationManager", "Carnivore weight:", nullptr));
        label_22->setText(QCoreApplication::translate("SimulationManager", "Carnivore:", nullptr));
        label_23->setText(QCoreApplication::translate("SimulationManager", "Herbivore constant:", nullptr));
        label_24->setText(QCoreApplication::translate("SimulationManager", "Search height limit:", nullptr));
        label_25->setText(QCoreApplication::translate("SimulationManager", "Energy:", nullptr));
        label_26->setText(QCoreApplication::translate("SimulationManager", "Carnivore constant:", nullptr));
        label_27->setText(QCoreApplication::translate("SimulationManager", "Speed:", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QCoreApplication::translate("SimulationManager", "Carnivores", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SimulationManager: public Ui_SimulationManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULATIONMANAGER_H
