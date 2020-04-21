/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QTabWidget *graphManagerTabs;
    QWidget *graphManagerBoxPage1;
    QLabel *label10;
    QLabel *label12;
    QLabel *label10_1;
    QLabel *label10_2;
    QLabel *label10_3;
    QLabel *label12_1;
    QLabel *label12_2;
    QLabel *label12_3;
    QPushButton *herbDisp;
    QPushButton *herbMean;
    QPushButton *herbFit;
    QPushButton *carnDisp;
    QPushButton *carnMean;
    QPushButton *carnFit;
    QCheckBox *updateCheckBox;
    QWidget *tab;
    QLabel *label18;
    QLabel *label19;
    QLabel *label20;
    QLabel *label21;
    QSpinBox *interval1SpinBox;
    QSpinBox *interval2SpinBox;
    QSpinBox *interval3SpinBox;
    QTabWidget *graphWidget;
    QWidget *rawDataTab;
    QVBoxLayout *verticalLayout;
    QLabel *label14;
    QCustomPlot *graphHerb;
    QCustomPlot *graphHerbHealth;
    QCustomPlot *graphHerbHurt;
    QLabel *label15;
    QCustomPlot *graphCarn;
    QWidget *processedDataTab;
    QCustomPlot *graphHerbPro;
    QLabel *label16;
    QLabel *label17;
    QCustomPlot *graphCarnPro;
    QCustomPlot *graphHerbProFit;
    QCustomPlot *graphCarnProFit;
    QWidget *tab_2;
    QCustomPlot *graphBoth;
    QTabWidget *tabWidget;
    QWidget *tab1;
    QLabel *label1;
    QPushButton *importButton;
    QLabel *label2;
    QLabel *label3;
    QLabel *label4;
    QLabel *label5;
    QLabel *label6;
    QLabel *label6_2;
    QLabel *label7;
    QLabel *label8;
    QLabel *label9;
    QLineEdit *editFileName;
    QLineEdit *editHerb;
    QLineEdit *editCarn;
    QLineEdit *editPlants;
    QLineEdit *editGen;
    QLineEdit *editHerHerb;
    QLineEdit *editHerCarn;
    QLineEdit *editFrames;
    QLineEdit *editHealth;
    QLineEdit *editHurt;
    QWidget *tab2;
    QLineEdit *editEvaluate;
    QLabel *label4_2;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(879, 670);
        graphManagerTabs = new QTabWidget(Widget);
        graphManagerTabs->setObjectName(QString::fromUtf8("graphManagerTabs"));
        graphManagerTabs->setGeometry(QRect(279, 0, 581, 281));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        graphManagerTabs->setFont(font);
        graphManagerBoxPage1 = new QWidget();
        graphManagerBoxPage1->setObjectName(QString::fromUtf8("graphManagerBoxPage1"));
        label10 = new QLabel(graphManagerBoxPage1);
        label10->setObjectName(QString::fromUtf8("label10"));
        label10->setGeometry(QRect(10, 30, 191, 17));
        QFont font1;
        font1.setBold(true);
        font1.setItalic(false);
        font1.setUnderline(false);
        font1.setWeight(75);
        font1.setKerning(true);
        label10->setFont(font1);
        label12 = new QLabel(graphManagerBoxPage1);
        label12->setObjectName(QString::fromUtf8("label12"));
        label12->setGeometry(QRect(280, 30, 191, 17));
        label12->setFont(font1);
        label10_1 = new QLabel(graphManagerBoxPage1);
        label10_1->setObjectName(QString::fromUtf8("label10_1"));
        label10_1->setGeometry(QRect(10, 70, 91, 17));
        QFont font2;
        font2.setBold(false);
        font2.setWeight(50);
        label10_1->setFont(font2);
        label10_2 = new QLabel(graphManagerBoxPage1);
        label10_2->setObjectName(QString::fromUtf8("label10_2"));
        label10_2->setGeometry(QRect(10, 110, 91, 17));
        label10_2->setFont(font2);
        label10_3 = new QLabel(graphManagerBoxPage1);
        label10_3->setObjectName(QString::fromUtf8("label10_3"));
        label10_3->setGeometry(QRect(10, 150, 91, 17));
        label10_3->setFont(font2);
        label12_1 = new QLabel(graphManagerBoxPage1);
        label12_1->setObjectName(QString::fromUtf8("label12_1"));
        label12_1->setGeometry(QRect(280, 70, 91, 17));
        label12_1->setFont(font2);
        label12_2 = new QLabel(graphManagerBoxPage1);
        label12_2->setObjectName(QString::fromUtf8("label12_2"));
        label12_2->setGeometry(QRect(280, 110, 91, 17));
        label12_2->setFont(font2);
        label12_3 = new QLabel(graphManagerBoxPage1);
        label12_3->setObjectName(QString::fromUtf8("label12_3"));
        label12_3->setGeometry(QRect(280, 150, 91, 17));
        label12_3->setFont(font2);
        herbDisp = new QPushButton(graphManagerBoxPage1);
        herbDisp->setObjectName(QString::fromUtf8("herbDisp"));
        herbDisp->setGeometry(QRect(130, 70, 89, 25));
        herbDisp->setFont(font2);
        herbDisp->setCheckable(true);
        herbMean = new QPushButton(graphManagerBoxPage1);
        herbMean->setObjectName(QString::fromUtf8("herbMean"));
        herbMean->setGeometry(QRect(130, 110, 89, 25));
        herbMean->setFont(font2);
        herbMean->setCheckable(true);
        herbFit = new QPushButton(graphManagerBoxPage1);
        herbFit->setObjectName(QString::fromUtf8("herbFit"));
        herbFit->setGeometry(QRect(130, 150, 89, 25));
        herbFit->setFont(font2);
        herbFit->setCheckable(true);
        carnDisp = new QPushButton(graphManagerBoxPage1);
        carnDisp->setObjectName(QString::fromUtf8("carnDisp"));
        carnDisp->setGeometry(QRect(410, 70, 89, 25));
        carnDisp->setFont(font2);
        carnDisp->setCheckable(true);
        carnMean = new QPushButton(graphManagerBoxPage1);
        carnMean->setObjectName(QString::fromUtf8("carnMean"));
        carnMean->setGeometry(QRect(410, 110, 89, 25));
        carnMean->setFont(font2);
        carnMean->setCheckable(true);
        carnFit = new QPushButton(graphManagerBoxPage1);
        carnFit->setObjectName(QString::fromUtf8("carnFit"));
        carnFit->setGeometry(QRect(410, 150, 89, 25));
        carnFit->setFont(font2);
        carnFit->setCheckable(true);
        updateCheckBox = new QCheckBox(graphManagerBoxPage1);
        updateCheckBox->setObjectName(QString::fromUtf8("updateCheckBox"));
        updateCheckBox->setGeometry(QRect(10, 210, 131, 23));
        updateCheckBox->setFont(font2);
        graphManagerTabs->addTab(graphManagerBoxPage1, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        label18 = new QLabel(tab);
        label18->setObjectName(QString::fromUtf8("label18"));
        label18->setGeometry(QRect(10, 30, 141, 17));
        label19 = new QLabel(tab);
        label19->setObjectName(QString::fromUtf8("label19"));
        label19->setGeometry(QRect(10, 60, 67, 17));
        label19->setFont(font2);
        label20 = new QLabel(tab);
        label20->setObjectName(QString::fromUtf8("label20"));
        label20->setGeometry(QRect(10, 110, 67, 17));
        label20->setFont(font2);
        label21 = new QLabel(tab);
        label21->setObjectName(QString::fromUtf8("label21"));
        label21->setGeometry(QRect(10, 160, 67, 17));
        label21->setFont(font2);
        interval1SpinBox = new QSpinBox(tab);
        interval1SpinBox->setObjectName(QString::fromUtf8("interval1SpinBox"));
        interval1SpinBox->setGeometry(QRect(130, 60, 42, 26));
        interval1SpinBox->setFont(font2);
        interval2SpinBox = new QSpinBox(tab);
        interval2SpinBox->setObjectName(QString::fromUtf8("interval2SpinBox"));
        interval2SpinBox->setGeometry(QRect(130, 110, 42, 26));
        interval2SpinBox->setFont(font2);
        interval3SpinBox = new QSpinBox(tab);
        interval3SpinBox->setObjectName(QString::fromUtf8("interval3SpinBox"));
        interval3SpinBox->setGeometry(QRect(130, 160, 42, 26));
        interval3SpinBox->setFont(font2);
        graphManagerTabs->addTab(tab, QString());
        graphWidget = new QTabWidget(Widget);
        graphWidget->setObjectName(QString::fromUtf8("graphWidget"));
        graphWidget->setGeometry(QRect(20, 290, 841, 1141));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphWidget->sizePolicy().hasHeightForWidth());
        graphWidget->setSizePolicy(sizePolicy);
        graphWidget->setFont(font);
        rawDataTab = new QWidget();
        rawDataTab->setObjectName(QString::fromUtf8("rawDataTab"));
        verticalLayout = new QVBoxLayout(rawDataTab);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label14 = new QLabel(rawDataTab);
        label14->setObjectName(QString::fromUtf8("label14"));
        label14->setFont(font);

        verticalLayout->addWidget(label14);

        graphHerb = new QCustomPlot(rawDataTab);
        graphHerb->setObjectName(QString::fromUtf8("graphHerb"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(graphHerb->sizePolicy().hasHeightForWidth());
        graphHerb->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(graphHerb);

        graphHerbHealth = new QCustomPlot(rawDataTab);
        graphHerbHealth->setObjectName(QString::fromUtf8("graphHerbHealth"));
        sizePolicy1.setHeightForWidth(graphHerbHealth->sizePolicy().hasHeightForWidth());
        graphHerbHealth->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(graphHerbHealth);

        graphHerbHurt = new QCustomPlot(rawDataTab);
        graphHerbHurt->setObjectName(QString::fromUtf8("graphHerbHurt"));
        sizePolicy1.setHeightForWidth(graphHerbHurt->sizePolicy().hasHeightForWidth());
        graphHerbHurt->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(graphHerbHurt);

        label15 = new QLabel(rawDataTab);
        label15->setObjectName(QString::fromUtf8("label15"));
        label15->setFont(font);

        verticalLayout->addWidget(label15);

        graphCarn = new QCustomPlot(rawDataTab);
        graphCarn->setObjectName(QString::fromUtf8("graphCarn"));
        sizePolicy1.setHeightForWidth(graphCarn->sizePolicy().hasHeightForWidth());
        graphCarn->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(graphCarn);

        graphWidget->addTab(rawDataTab, QString());
        processedDataTab = new QWidget();
        processedDataTab->setObjectName(QString::fromUtf8("processedDataTab"));
        graphHerbPro = new QCustomPlot(processedDataTab);
        graphHerbPro->setObjectName(QString::fromUtf8("graphHerbPro"));
        graphHerbPro->setGeometry(QRect(10, 30, 819, 257));
        sizePolicy1.setHeightForWidth(graphHerbPro->sizePolicy().hasHeightForWidth());
        graphHerbPro->setSizePolicy(sizePolicy1);
        label16 = new QLabel(processedDataTab);
        label16->setObjectName(QString::fromUtf8("label16"));
        label16->setGeometry(QRect(10, 10, 819, 17));
        label16->setFont(font);
        label17 = new QLabel(processedDataTab);
        label17->setObjectName(QString::fromUtf8("label17"));
        label17->setGeometry(QRect(10, 560, 819, 17));
        label17->setFont(font);
        graphCarnPro = new QCustomPlot(processedDataTab);
        graphCarnPro->setObjectName(QString::fromUtf8("graphCarnPro"));
        graphCarnPro->setGeometry(QRect(10, 580, 819, 257));
        sizePolicy1.setHeightForWidth(graphCarnPro->sizePolicy().hasHeightForWidth());
        graphCarnPro->setSizePolicy(sizePolicy1);
        graphHerbProFit = new QCustomPlot(processedDataTab);
        graphHerbProFit->setObjectName(QString::fromUtf8("graphHerbProFit"));
        graphHerbProFit->setGeometry(QRect(10, 290, 819, 257));
        sizePolicy1.setHeightForWidth(graphHerbProFit->sizePolicy().hasHeightForWidth());
        graphHerbProFit->setSizePolicy(sizePolicy1);
        graphCarnProFit = new QCustomPlot(processedDataTab);
        graphCarnProFit->setObjectName(QString::fromUtf8("graphCarnProFit"));
        graphCarnProFit->setGeometry(QRect(10, 840, 819, 257));
        sizePolicy1.setHeightForWidth(graphCarnProFit->sizePolicy().hasHeightForWidth());
        graphCarnProFit->setSizePolicy(sizePolicy1);
        graphWidget->addTab(processedDataTab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        graphBoth = new QCustomPlot(tab_2);
        graphBoth->setObjectName(QString::fromUtf8("graphBoth"));
        graphBoth->setGeometry(QRect(10, 20, 819, 257));
        sizePolicy1.setHeightForWidth(graphBoth->sizePolicy().hasHeightForWidth());
        graphBoth->setSizePolicy(sizePolicy1);
        graphWidget->addTab(tab_2, QString());
        tabWidget = new QTabWidget(Widget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(20, 0, 251, 281));
        tabWidget->setFont(font);
        tab1 = new QWidget();
        tab1->setObjectName(QString::fromUtf8("tab1"));
        tab1->setFont(font2);
        label1 = new QLabel(tab1);
        label1->setObjectName(QString::fromUtf8("label1"));
        label1->setGeometry(QRect(10, 40, 131, 17));
        label1->setFont(font2);
        importButton = new QPushButton(tab1);
        importButton->setObjectName(QString::fromUtf8("importButton"));
        importButton->setGeometry(QRect(80, 10, 89, 25));
        importButton->setFont(font2);
        label2 = new QLabel(tab1);
        label2->setObjectName(QString::fromUtf8("label2"));
        label2->setGeometry(QRect(10, 60, 131, 17));
        label2->setFont(font2);
        label3 = new QLabel(tab1);
        label3->setObjectName(QString::fromUtf8("label3"));
        label3->setGeometry(QRect(10, 80, 131, 17));
        label3->setFont(font2);
        label4 = new QLabel(tab1);
        label4->setObjectName(QString::fromUtf8("label4"));
        label4->setGeometry(QRect(10, 100, 131, 17));
        label4->setFont(font2);
        label5 = new QLabel(tab1);
        label5->setObjectName(QString::fromUtf8("label5"));
        label5->setGeometry(QRect(10, 120, 131, 17));
        label5->setFont(font2);
        label6 = new QLabel(tab1);
        label6->setObjectName(QString::fromUtf8("label6"));
        label6->setGeometry(QRect(10, 140, 131, 17));
        label6->setFont(font2);
        label6_2 = new QLabel(tab1);
        label6_2->setObjectName(QString::fromUtf8("label6_2"));
        label6_2->setGeometry(QRect(10, 160, 131, 17));
        label6_2->setFont(font2);
        label7 = new QLabel(tab1);
        label7->setObjectName(QString::fromUtf8("label7"));
        label7->setGeometry(QRect(10, 180, 141, 17));
        label7->setFont(font2);
        label8 = new QLabel(tab1);
        label8->setObjectName(QString::fromUtf8("label8"));
        label8->setGeometry(QRect(10, 200, 131, 17));
        label8->setFont(font2);
        label9 = new QLabel(tab1);
        label9->setObjectName(QString::fromUtf8("label9"));
        label9->setGeometry(QRect(10, 220, 131, 17));
        label9->setFont(font2);
        editFileName = new QLineEdit(tab1);
        editFileName->setObjectName(QString::fromUtf8("editFileName"));
        editFileName->setGeometry(QRect(150, 40, 91, 21));
        editFileName->setFont(font2);
        editFileName->setReadOnly(true);
        editHerb = new QLineEdit(tab1);
        editHerb->setObjectName(QString::fromUtf8("editHerb"));
        editHerb->setGeometry(QRect(190, 60, 51, 21));
        editHerb->setFont(font2);
        editHerb->setReadOnly(true);
        editCarn = new QLineEdit(tab1);
        editCarn->setObjectName(QString::fromUtf8("editCarn"));
        editCarn->setGeometry(QRect(190, 80, 51, 21));
        editCarn->setFont(font2);
        editCarn->setReadOnly(true);
        editPlants = new QLineEdit(tab1);
        editPlants->setObjectName(QString::fromUtf8("editPlants"));
        editPlants->setGeometry(QRect(190, 100, 51, 21));
        editPlants->setFont(font2);
        editPlants->setReadOnly(true);
        editGen = new QLineEdit(tab1);
        editGen->setObjectName(QString::fromUtf8("editGen"));
        editGen->setGeometry(QRect(190, 120, 51, 21));
        editGen->setFont(font2);
        editGen->setReadOnly(true);
        editHerHerb = new QLineEdit(tab1);
        editHerHerb->setObjectName(QString::fromUtf8("editHerHerb"));
        editHerHerb->setGeometry(QRect(190, 140, 51, 21));
        editHerHerb->setFont(font2);
        editHerHerb->setReadOnly(true);
        editHerCarn = new QLineEdit(tab1);
        editHerCarn->setObjectName(QString::fromUtf8("editHerCarn"));
        editHerCarn->setGeometry(QRect(190, 160, 51, 21));
        editHerCarn->setFont(font2);
        editHerCarn->setReadOnly(true);
        editFrames = new QLineEdit(tab1);
        editFrames->setObjectName(QString::fromUtf8("editFrames"));
        editFrames->setGeometry(QRect(190, 180, 51, 21));
        editFrames->setFont(font2);
        editFrames->setReadOnly(true);
        editHealth = new QLineEdit(tab1);
        editHealth->setObjectName(QString::fromUtf8("editHealth"));
        editHealth->setGeometry(QRect(190, 200, 51, 21));
        editHealth->setFont(font2);
        editHealth->setReadOnly(true);
        editHurt = new QLineEdit(tab1);
        editHurt->setObjectName(QString::fromUtf8("editHurt"));
        editHurt->setGeometry(QRect(190, 220, 51, 21));
        editHurt->setFont(font2);
        editHurt->setReadOnly(true);
        tabWidget->addTab(tab1, QString());
        tab2 = new QWidget();
        tab2->setObjectName(QString::fromUtf8("tab2"));
        tab2->setFont(font);
        editEvaluate = new QLineEdit(tab2);
        editEvaluate->setObjectName(QString::fromUtf8("editEvaluate"));
        editEvaluate->setGeometry(QRect(190, 20, 51, 21));
        editEvaluate->setFont(font2);
        editEvaluate->setReadOnly(true);
        label4_2 = new QLabel(tab2);
        label4_2->setObjectName(QString::fromUtf8("label4_2"));
        label4_2->setGeometry(QRect(10, 20, 131, 17));
        label4_2->setFont(font2);
        tabWidget->addTab(tab2, QString());

        retranslateUi(Widget);

        graphManagerTabs->setCurrentIndex(1);
        graphWidget->setCurrentIndex(1);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        label10->setText(QApplication::translate("Widget", "Herbivores", nullptr));
        label12->setText(QApplication::translate("Widget", "Carnivores", nullptr));
        label10_1->setText(QApplication::translate("Widget", "Dispersion", nullptr));
        label10_2->setText(QApplication::translate("Widget", "Mean graph", nullptr));
        label10_3->setText(QApplication::translate("Widget", "Fittest graph", nullptr));
        label12_1->setText(QApplication::translate("Widget", "Dispersion", nullptr));
        label12_2->setText(QApplication::translate("Widget", "Mean graph", nullptr));
        label12_3->setText(QApplication::translate("Widget", "Fittest graph", nullptr));
        herbDisp->setText(QApplication::translate("Widget", "Visible", nullptr));
        herbMean->setText(QApplication::translate("Widget", "Visible", nullptr));
        herbFit->setText(QApplication::translate("Widget", "Visible", nullptr));
        carnDisp->setText(QApplication::translate("Widget", "Visible", nullptr));
        carnMean->setText(QApplication::translate("Widget", "Visible", nullptr));
        carnFit->setText(QApplication::translate("Widget", "Visible", nullptr));
        updateCheckBox->setText(QApplication::translate("Widget", "Update plot", nullptr));
        graphManagerTabs->setTabText(graphManagerTabs->indexOf(graphManagerBoxPage1), QApplication::translate("Widget", "Raw data manager", nullptr));
        label18->setText(QApplication::translate("Widget", "Time intervals", nullptr));
        label19->setText(QApplication::translate("Widget", "Interval 1", nullptr));
        label20->setText(QApplication::translate("Widget", "Interval 2", nullptr));
        label21->setText(QApplication::translate("Widget", "Interval 3", nullptr));
        graphManagerTabs->setTabText(graphManagerTabs->indexOf(tab), QApplication::translate("Widget", "Processed data manager", nullptr));
        label14->setText(QApplication::translate("Widget", "Herbivores", nullptr));
        label15->setText(QApplication::translate("Widget", "Carnivores", nullptr));
        graphWidget->setTabText(graphWidget->indexOf(rawDataTab), QApplication::translate("Widget", "Raw data", nullptr));
        label16->setText(QApplication::translate("Widget", "Herbivores", nullptr));
        label17->setText(QApplication::translate("Widget", "Carnivores", nullptr));
        graphWidget->setTabText(graphWidget->indexOf(processedDataTab), QApplication::translate("Widget", "Processed data", nullptr));
        graphWidget->setTabText(graphWidget->indexOf(tab_2), QApplication::translate("Widget", "Comparison", nullptr));
        label1->setText(QApplication::translate("Widget", "File name :", nullptr));
        importButton->setText(QApplication::translate("Widget", "Import File", nullptr));
        label2->setText(QApplication::translate("Widget", "Qty herbivores:", nullptr));
        label3->setText(QApplication::translate("Widget", "Qty carnivores:", nullptr));
        label4->setText(QApplication::translate("Widget", "Qty plants:", nullptr));
        label5->setText(QApplication::translate("Widget", "Generations", nullptr));
        label6->setText(QApplication::translate("Widget", "Herbivore heritage:", nullptr));
        label6_2->setText(QApplication::translate("Widget", "Carnivore heritage:", nullptr));
        label7->setText(QApplication::translate("Widget", "Frames/generation", nullptr));
        label8->setText(QApplication::translate("Widget", "Health weight:", nullptr));
        label9->setText(QApplication::translate("Widget", "Hurt weight:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab1), QApplication::translate("Widget", "Macros", nullptr));
        editEvaluate->setText(QString());
        label4_2->setText(QApplication::translate("Widget", "Evaluation interval:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab2), QApplication::translate("Widget", "Mutation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
