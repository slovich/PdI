/********************************************************************************
** Form generated from reading UI file 'formhistograma.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMHISTOGRAMA_H
#define UI_FORMHISTOGRAMA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormHistograma
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_1;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_1;
    QLabel *label_imagem_original;
    QGroupBox *groupBox_2;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_histograma_original;
    QGroupBox *groupBox_3;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_imagem_modificada;
    QGroupBox *groupBox_4;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_histograma_modificada;

    void setupUi(QWidget *FormHistograma)
    {
        if (FormHistograma->objectName().isEmpty())
            FormHistograma->setObjectName("FormHistograma");
        FormHistograma->setWindowModality(Qt::WindowModality::ApplicationModal);
        FormHistograma->resize(800, 600);
        gridLayoutWidget = new QWidget(FormHistograma);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(10, 10, 461, 241));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(10);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        groupBox_1 = new QGroupBox(gridLayoutWidget);
        groupBox_1->setObjectName("groupBox_1");
        verticalLayoutWidget_2 = new QWidget(groupBox_1);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(10, 20, 121, 101));
        verticalLayout_1 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_1->setObjectName("verticalLayout_1");
        verticalLayout_1->setContentsMargins(0, 0, 0, 0);
        label_imagem_original = new QLabel(verticalLayoutWidget_2);
        label_imagem_original->setObjectName("label_imagem_original");
        label_imagem_original->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_1->addWidget(label_imagem_original);


        gridLayout->addWidget(groupBox_1, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(gridLayoutWidget);
        groupBox_2->setObjectName("groupBox_2");
        verticalLayoutWidget = new QWidget(groupBox_2);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 20, 121, 101));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_histograma_original = new QLabel(verticalLayoutWidget);
        label_histograma_original->setObjectName("label_histograma_original");
        label_histograma_original->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(label_histograma_original);


        gridLayout->addWidget(groupBox_2, 0, 1, 1, 1);

        groupBox_3 = new QGroupBox(gridLayoutWidget);
        groupBox_3->setObjectName("groupBox_3");
        verticalLayoutWidget_4 = new QWidget(groupBox_3);
        verticalLayoutWidget_4->setObjectName("verticalLayoutWidget_4");
        verticalLayoutWidget_4->setGeometry(QRect(10, 20, 121, 101));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_4);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_imagem_modificada = new QLabel(verticalLayoutWidget_4);
        label_imagem_modificada->setObjectName("label_imagem_modificada");
        label_imagem_modificada->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(label_imagem_modificada);


        gridLayout->addWidget(groupBox_3, 1, 0, 1, 1);

        groupBox_4 = new QGroupBox(gridLayoutWidget);
        groupBox_4->setObjectName("groupBox_4");
        verticalLayoutWidget_3 = new QWidget(groupBox_4);
        verticalLayoutWidget_3->setObjectName("verticalLayoutWidget_3");
        verticalLayoutWidget_3->setGeometry(QRect(10, 20, 121, 101));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_histograma_modificada = new QLabel(verticalLayoutWidget_3);
        label_histograma_modificada->setObjectName("label_histograma_modificada");
        label_histograma_modificada->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(label_histograma_modificada);


        gridLayout->addWidget(groupBox_4, 1, 1, 1, 1);


        retranslateUi(FormHistograma);

        QMetaObject::connectSlotsByName(FormHistograma);
    } // setupUi

    void retranslateUi(QWidget *FormHistograma)
    {
        FormHistograma->setWindowTitle(QCoreApplication::translate("FormHistograma", "Histograma", nullptr));
        groupBox_1->setTitle(QCoreApplication::translate("FormHistograma", "Imagem Original", nullptr));
        label_imagem_original->setText(QCoreApplication::translate("FormHistograma", "Imagem Original", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("FormHistograma", "Histograma", nullptr));
        label_histograma_original->setText(QCoreApplication::translate("FormHistograma", "<html><head/><body><p><span style=\" font-weight:700;\">Histograma</span>:<br/>Imagem Original</p></body></html>", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("FormHistograma", "Imagem Modificada", nullptr));
        label_imagem_modificada->setText(QCoreApplication::translate("FormHistograma", "Imagem Modificada", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("FormHistograma", "Histograma", nullptr));
        label_histograma_modificada->setText(QCoreApplication::translate("FormHistograma", "<html><head/><body><p><span style=\" font-weight:700;\">Histograma:</span><br/>Imagem Modificada</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FormHistograma: public Ui_FormHistograma {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMHISTOGRAMA_H
