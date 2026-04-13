/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSalvar;
    QAction *actionImprimir;
    QAction *actionSair;
    QAction *actionSobre;
    QAction *actionQuantizacao;
    QAction *actionAritimetica;
    QAction *actionQuantizacao_2;
    QAction *actionSalvar_2;
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *quantization;
    QLabel *label_titulo1;
    QLabel *label_imagem_modificada;
    QLabel *label_imagem_original;
    QPushButton *pushButton_aplicar;
    QPushButton *pushButton_procurar;
    QWidget *file_explorer;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_diretorios;
    QTreeView *treeView_dir;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_arquivos;
    QListView *listView_file;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButton_selecionar;
    QPushButton *pushButton_cancelar;
    QSpacerItem *verticalSpacer;
    QWidget *page;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_12;
    QVBoxLayout *verticalLayout_12;
    QGroupBox *groupBox_qu;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_qu1;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_qu2;
    QComboBox *comboBox_niveis_canal;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_qu3;
    QComboBox *comboBox_profundidade_bits;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButton_aplicar_qu;
    QGroupBox *groupBox_cm;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_10;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_cm1;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_cm2;
    QComboBox *comboBox_numero_cores;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_cm3;
    QComboBox *comboBox_criterio_parada;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *pushButton_aplicar_cm;
    QVBoxLayout *verticalLayout_11;
    QSpacerItem *verticalSpacer_4;
    QPushButton *pushButton_cancelar_algoritmo;
    QSpacerItem *verticalSpacer_5;
    QWidget *page_2;
    QLabel *label;
    QTextEdit *textEdit;
    QPushButton *pushButton_voltar;
    QWidget *page_3;
    QLabel *label_titulo1_2;
    QGroupBox *groupBox;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QGroupBox *groupBox_2;
    QLineEdit *lineEdit_valor;
    QGroupBox *groupBox_3;
    QLabel *label_imagem_principal;
    QLabel *label_imagem_adicional;
    QLabel *label_imagem_resultado;
    QLabel *label_imagem_1;
    QLabel *label_imagem_2;
    QLabel *label_imagem_3;
    QPushButton *pushButton;
    QPushButton *pushButton_calcular;
    QWidget *page_4;
    QGroupBox *groupBox_4;
    QWidget *layoutWidget5;
    QVBoxLayout *verticalLayout;
    QLabel *label_arquivo_imagem_1;
    QListView *listView_arquivo_imagem_1;
    QWidget *layoutWidget6;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_diretorio_imagem_1;
    QTreeView *treeView_diretorio_imagem_1;
    QPushButton *pushButton_selecionar_imagens_aritimetica;
    QGroupBox *groupBox_5;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_arquivo_imagem_2;
    QListView *listView_arquivo_imagem_2;
    QWidget *layoutWidget_3;
    QVBoxLayout *verticalLayout_13;
    QLabel *label_diretorio_imagem_2;
    QTreeView *treeView_diretorio_imagem_2;
    QPushButton *pushButton_selecionar_cancelar_aritimetica;
    QMenuBar *menubar;
    QMenu *menuArquivo;
    QMenu *menuAjuda;
    QMenu *menuFerramentas;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        actionSalvar = new QAction(MainWindow);
        actionSalvar->setObjectName("actionSalvar");
        actionImprimir = new QAction(MainWindow);
        actionImprimir->setObjectName("actionImprimir");
        actionSair = new QAction(MainWindow);
        actionSair->setObjectName("actionSair");
        actionSobre = new QAction(MainWindow);
        actionSobre->setObjectName("actionSobre");
        actionQuantizacao = new QAction(MainWindow);
        actionQuantizacao->setObjectName("actionQuantizacao");
        actionAritimetica = new QAction(MainWindow);
        actionAritimetica->setObjectName("actionAritimetica");
        actionQuantizacao_2 = new QAction(MainWindow);
        actionQuantizacao_2->setObjectName("actionQuantizacao_2");
        actionSalvar_2 = new QAction(MainWindow);
        actionSalvar_2->setObjectName("actionSalvar_2");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(10, 10, 781, 541));
        quantization = new QWidget();
        quantization->setObjectName("quantization");
        label_titulo1 = new QLabel(quantization);
        label_titulo1->setObjectName("label_titulo1");
        label_titulo1->setGeometry(QRect(10, 10, 231, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("Times New Roman")});
        font.setPointSize(24);
        font.setBold(true);
        label_titulo1->setFont(font);
        label_titulo1->setStyleSheet(QString::fromUtf8(""));
        label_titulo1->setFrameShape(QFrame::Shape::StyledPanel);
        label_titulo1->setFrameShadow(QFrame::Shadow::Sunken);
        label_titulo1->setMidLineWidth(1);
        label_titulo1->setTextFormat(Qt::TextFormat::RichText);
        label_imagem_modificada = new QLabel(quantization);
        label_imagem_modificada->setObjectName("label_imagem_modificada");
        label_imagem_modificada->setGeometry(QRect(390, 120, 360, 360));
        label_imagem_modificada->setPixmap(QPixmap(QString::fromUtf8(":/img/resource/img/default_img.png")));
        label_imagem_modificada->setScaledContents(true);
        label_imagem_original = new QLabel(quantization);
        label_imagem_original->setObjectName("label_imagem_original");
        label_imagem_original->setGeometry(QRect(10, 120, 360, 360));
        label_imagem_original->setMaximumSize(QSize(16777215, 16777215));
        label_imagem_original->setPixmap(QPixmap(QString::fromUtf8(":/img/resource/img/default_img.png")));
        label_imagem_original->setScaledContents(true);
        pushButton_aplicar = new QPushButton(quantization);
        pushButton_aplicar->setObjectName("pushButton_aplicar");
        pushButton_aplicar->setGeometry(QRect(390, 80, 360, 24));
        pushButton_procurar = new QPushButton(quantization);
        pushButton_procurar->setObjectName("pushButton_procurar");
        pushButton_procurar->setGeometry(QRect(10, 80, 360, 24));
        stackedWidget->addWidget(quantization);
        file_explorer = new QWidget();
        file_explorer->setObjectName("file_explorer");
        layoutWidget = new QWidget(file_explorer);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(30, 20, 643, 500));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        label_diretorios = new QLabel(layoutWidget);
        label_diretorios->setObjectName("label_diretorios");
        QFont font1;
        font1.setBold(true);
        label_diretorios->setFont(font1);

        verticalLayout_5->addWidget(label_diretorios);

        treeView_dir = new QTreeView(layoutWidget);
        treeView_dir->setObjectName("treeView_dir");

        verticalLayout_5->addWidget(treeView_dir);


        horizontalLayout_5->addLayout(verticalLayout_5);

        horizontalSpacer_4 = new QSpacerItem(28, 496, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        label_arquivos = new QLabel(layoutWidget);
        label_arquivos->setObjectName("label_arquivos");
        label_arquivos->setFont(font1);

        verticalLayout_6->addWidget(label_arquivos);

        listView_file = new QListView(layoutWidget);
        listView_file->setObjectName("listView_file");

        verticalLayout_6->addWidget(listView_file);


        horizontalLayout_5->addLayout(verticalLayout_6);


        horizontalLayout_6->addLayout(horizontalLayout_5);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        pushButton_selecionar = new QPushButton(layoutWidget);
        pushButton_selecionar->setObjectName("pushButton_selecionar");

        verticalLayout_3->addWidget(pushButton_selecionar);

        pushButton_cancelar = new QPushButton(layoutWidget);
        pushButton_cancelar->setObjectName("pushButton_cancelar");

        verticalLayout_3->addWidget(pushButton_cancelar);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        verticalLayout_3->setStretch(1, 5);
        verticalLayout_3->setStretch(3, 4);

        horizontalLayout_6->addLayout(verticalLayout_3);

        stackedWidget->addWidget(file_explorer);
        page = new QWidget();
        page->setObjectName("page");
        layoutWidget1 = new QWidget(page);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(20, 20, 541, 401));
        horizontalLayout_12 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        horizontalLayout_12->setContentsMargins(0, 0, 0, 0);
        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName("verticalLayout_12");
        groupBox_qu = new QGroupBox(layoutWidget1);
        groupBox_qu->setObjectName("groupBox_qu");
        groupBox_qu->setMinimumSize(QSize(0, 64));
        layoutWidget2 = new QWidget(groupBox_qu);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(20, 30, 401, 112));
        verticalLayout_8 = new QVBoxLayout(layoutWidget2);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        label_qu1 = new QLabel(layoutWidget2);
        label_qu1->setObjectName("label_qu1");

        verticalLayout_7->addWidget(label_qu1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_qu2 = new QLabel(layoutWidget2);
        label_qu2->setObjectName("label_qu2");

        horizontalLayout_4->addWidget(label_qu2);

        comboBox_niveis_canal = new QComboBox(layoutWidget2);
        comboBox_niveis_canal->addItem(QString());
        comboBox_niveis_canal->addItem(QString());
        comboBox_niveis_canal->addItem(QString());
        comboBox_niveis_canal->addItem(QString());
        comboBox_niveis_canal->setObjectName("comboBox_niveis_canal");
        comboBox_niveis_canal->setMaxVisibleItems(4);

        horizontalLayout_4->addWidget(comboBox_niveis_canal);


        verticalLayout_7->addLayout(horizontalLayout_4);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_qu3 = new QLabel(layoutWidget2);
        label_qu3->setObjectName("label_qu3");

        horizontalLayout_7->addWidget(label_qu3);

        comboBox_profundidade_bits = new QComboBox(layoutWidget2);
        comboBox_profundidade_bits->addItem(QString());
        comboBox_profundidade_bits->addItem(QString());
        comboBox_profundidade_bits->addItem(QString());
        comboBox_profundidade_bits->addItem(QString());
        comboBox_profundidade_bits->setObjectName("comboBox_profundidade_bits");

        horizontalLayout_7->addWidget(comboBox_profundidade_bits);


        verticalLayout_7->addLayout(horizontalLayout_7);


        verticalLayout_8->addLayout(verticalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_5);

        pushButton_aplicar_qu = new QPushButton(layoutWidget2);
        pushButton_aplicar_qu->setObjectName("pushButton_aplicar_qu");
        pushButton_aplicar_qu->setMinimumSize(QSize(170, 0));

        horizontalLayout_8->addWidget(pushButton_aplicar_qu);


        verticalLayout_8->addLayout(horizontalLayout_8);


        verticalLayout_12->addWidget(groupBox_qu);

        groupBox_cm = new QGroupBox(layoutWidget1);
        groupBox_cm->setObjectName("groupBox_cm");
        layoutWidget3 = new QWidget(groupBox_cm);
        layoutWidget3->setObjectName("layoutWidget3");
        layoutWidget3->setGeometry(QRect(20, 40, 401, 112));
        verticalLayout_10 = new QVBoxLayout(layoutWidget3);
        verticalLayout_10->setObjectName("verticalLayout_10");
        verticalLayout_10->setContentsMargins(0, 0, 0, 0);
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName("verticalLayout_9");
        label_cm1 = new QLabel(layoutWidget3);
        label_cm1->setObjectName("label_cm1");

        verticalLayout_9->addWidget(label_cm1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        label_cm2 = new QLabel(layoutWidget3);
        label_cm2->setObjectName("label_cm2");

        horizontalLayout_9->addWidget(label_cm2);

        comboBox_numero_cores = new QComboBox(layoutWidget3);
        comboBox_numero_cores->addItem(QString());
        comboBox_numero_cores->addItem(QString());
        comboBox_numero_cores->addItem(QString());
        comboBox_numero_cores->addItem(QString());
        comboBox_numero_cores->addItem(QString());
        comboBox_numero_cores->setObjectName("comboBox_numero_cores");

        horizontalLayout_9->addWidget(comboBox_numero_cores);


        verticalLayout_9->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        label_cm3 = new QLabel(layoutWidget3);
        label_cm3->setObjectName("label_cm3");

        horizontalLayout_10->addWidget(label_cm3);

        comboBox_criterio_parada = new QComboBox(layoutWidget3);
        comboBox_criterio_parada->addItem(QString());
        comboBox_criterio_parada->addItem(QString());
        comboBox_criterio_parada->addItem(QString());
        comboBox_criterio_parada->setObjectName("comboBox_criterio_parada");

        horizontalLayout_10->addWidget(comboBox_criterio_parada);


        verticalLayout_9->addLayout(horizontalLayout_10);


        verticalLayout_10->addLayout(verticalLayout_9);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_6);

        pushButton_aplicar_cm = new QPushButton(layoutWidget3);
        pushButton_aplicar_cm->setObjectName("pushButton_aplicar_cm");
        pushButton_aplicar_cm->setMinimumSize(QSize(170, 0));

        horizontalLayout_11->addWidget(pushButton_aplicar_cm);


        verticalLayout_10->addLayout(horizontalLayout_11);


        verticalLayout_12->addWidget(groupBox_cm);


        horizontalLayout_12->addLayout(verticalLayout_12);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName("verticalLayout_11");
        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_11->addItem(verticalSpacer_4);

        pushButton_cancelar_algoritmo = new QPushButton(layoutWidget1);
        pushButton_cancelar_algoritmo->setObjectName("pushButton_cancelar_algoritmo");

        verticalLayout_11->addWidget(pushButton_cancelar_algoritmo);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_11->addItem(verticalSpacer_5);

        verticalLayout_11->setStretch(0, 1);
        verticalLayout_11->setStretch(1, 2);
        verticalLayout_11->setStretch(2, 8);

        horizontalLayout_12->addLayout(verticalLayout_11);

        horizontalLayout_12->setStretch(0, 10);
        horizontalLayout_12->setStretch(1, 1);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        label = new QLabel(page_2);
        label->setObjectName("label");
        label->setGeometry(QRect(160, 70, 441, 111));
        textEdit = new QTextEdit(page_2);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(160, 180, 441, 91));
        textEdit->setReadOnly(true);
        pushButton_voltar = new QPushButton(page_2);
        pushButton_voltar->setObjectName("pushButton_voltar");
        pushButton_voltar->setGeometry(QRect(290, 320, 171, 51));
        QFont font2;
        font2.setPointSize(18);
        pushButton_voltar->setFont(font2);
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        label_titulo1_2 = new QLabel(page_3);
        label_titulo1_2->setObjectName("label_titulo1_2");
        label_titulo1_2->setGeometry(QRect(10, 10, 361, 41));
        label_titulo1_2->setFont(font);
        label_titulo1_2->setStyleSheet(QString::fromUtf8(""));
        label_titulo1_2->setFrameShape(QFrame::Shape::StyledPanel);
        label_titulo1_2->setFrameShadow(QFrame::Shadow::Sunken);
        label_titulo1_2->setMidLineWidth(1);
        label_titulo1_2->setTextFormat(Qt::TextFormat::RichText);
        groupBox = new QGroupBox(page_3);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 60, 751, 71));
        layoutWidget4 = new QWidget(groupBox);
        layoutWidget4->setObjectName("layoutWidget4");
        layoutWidget4->setGeometry(QRect(10, 30, 731, 22));
        horizontalLayout = new QHBoxLayout(layoutWidget4);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        radioButton = new QRadioButton(layoutWidget4);
        radioButton->setObjectName("radioButton");
        radioButton->setChecked(true);

        horizontalLayout->addWidget(radioButton);

        radioButton_2 = new QRadioButton(layoutWidget4);
        radioButton_2->setObjectName("radioButton_2");

        horizontalLayout->addWidget(radioButton_2);

        radioButton_3 = new QRadioButton(layoutWidget4);
        radioButton_3->setObjectName("radioButton_3");

        horizontalLayout->addWidget(radioButton_3);

        radioButton_4 = new QRadioButton(layoutWidget4);
        radioButton_4->setObjectName("radioButton_4");

        horizontalLayout->addWidget(radioButton_4);

        groupBox_2 = new QGroupBox(page_3);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(10, 140, 191, 71));
        lineEdit_valor = new QLineEdit(groupBox_2);
        lineEdit_valor->setObjectName("lineEdit_valor");
        lineEdit_valor->setGeometry(QRect(10, 30, 121, 22));
        lineEdit_valor->setInputMethodHints(Qt::InputMethodHint::ImhDigitsOnly|Qt::InputMethodHint::ImhPreferNumbers);
        groupBox_3 = new QGroupBox(page_3);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(10, 220, 751, 291));
        label_imagem_principal = new QLabel(groupBox_3);
        label_imagem_principal->setObjectName("label_imagem_principal");
        label_imagem_principal->setGeometry(QRect(60, 30, 101, 16));
        label_imagem_adicional = new QLabel(groupBox_3);
        label_imagem_adicional->setObjectName("label_imagem_adicional");
        label_imagem_adicional->setGeometry(QRect(320, 30, 101, 16));
        label_imagem_resultado = new QLabel(groupBox_3);
        label_imagem_resultado->setObjectName("label_imagem_resultado");
        label_imagem_resultado->setGeometry(QRect(580, 30, 111, 16));
        label_imagem_1 = new QLabel(groupBox_3);
        label_imagem_1->setObjectName("label_imagem_1");
        label_imagem_1->setGeometry(QRect(10, 50, 200, 200));
        label_imagem_1->setMaximumSize(QSize(200, 200));
        label_imagem_1->setPixmap(QPixmap(QString::fromUtf8(":/img/resource/img/default_img.png")));
        label_imagem_1->setScaledContents(true);
        label_imagem_2 = new QLabel(groupBox_3);
        label_imagem_2->setObjectName("label_imagem_2");
        label_imagem_2->setEnabled(true);
        label_imagem_2->setGeometry(QRect(270, 50, 200, 200));
        label_imagem_2->setMaximumSize(QSize(200, 200));
        label_imagem_2->setPixmap(QPixmap(QString::fromUtf8(":/img/resource/img/default_img.png")));
        label_imagem_2->setScaledContents(true);
        label_imagem_3 = new QLabel(groupBox_3);
        label_imagem_3->setObjectName("label_imagem_3");
        label_imagem_3->setEnabled(true);
        label_imagem_3->setGeometry(QRect(530, 50, 200, 200));
        label_imagem_3->setMaximumSize(QSize(200, 200));
        label_imagem_3->setPixmap(QPixmap(QString::fromUtf8(":/img/resource/img/default_img.png")));
        label_imagem_3->setScaledContents(true);
        pushButton = new QPushButton(page_3);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(320, 170, 121, 24));
        pushButton_calcular = new QPushButton(page_3);
        pushButton_calcular->setObjectName("pushButton_calcular");
        pushButton_calcular->setGeometry(QRect(570, 170, 121, 24));
        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        groupBox_4 = new QGroupBox(page_4);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setGeometry(QRect(10, 10, 581, 261));
        layoutWidget5 = new QWidget(groupBox_4);
        layoutWidget5->setObjectName("layoutWidget5");
        layoutWidget5->setGeometry(QRect(300, 30, 258, 216));
        verticalLayout = new QVBoxLayout(layoutWidget5);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_arquivo_imagem_1 = new QLabel(layoutWidget5);
        label_arquivo_imagem_1->setObjectName("label_arquivo_imagem_1");

        verticalLayout->addWidget(label_arquivo_imagem_1);

        listView_arquivo_imagem_1 = new QListView(layoutWidget5);
        listView_arquivo_imagem_1->setObjectName("listView_arquivo_imagem_1");

        verticalLayout->addWidget(listView_arquivo_imagem_1);

        layoutWidget6 = new QWidget(groupBox_4);
        layoutWidget6->setObjectName("layoutWidget6");
        layoutWidget6->setGeometry(QRect(10, 30, 258, 216));
        verticalLayout_2 = new QVBoxLayout(layoutWidget6);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_diretorio_imagem_1 = new QLabel(layoutWidget6);
        label_diretorio_imagem_1->setObjectName("label_diretorio_imagem_1");

        verticalLayout_2->addWidget(label_diretorio_imagem_1);

        treeView_diretorio_imagem_1 = new QTreeView(layoutWidget6);
        treeView_diretorio_imagem_1->setObjectName("treeView_diretorio_imagem_1");

        verticalLayout_2->addWidget(treeView_diretorio_imagem_1);

        pushButton_selecionar_imagens_aritimetica = new QPushButton(page_4);
        pushButton_selecionar_imagens_aritimetica->setObjectName("pushButton_selecionar_imagens_aritimetica");
        pushButton_selecionar_imagens_aritimetica->setGeometry(QRect(600, 40, 131, 24));
        groupBox_5 = new QGroupBox(page_4);
        groupBox_5->setObjectName("groupBox_5");
        groupBox_5->setGeometry(QRect(10, 270, 581, 261));
        layoutWidget_2 = new QWidget(groupBox_5);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(300, 30, 258, 216));
        verticalLayout_4 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_arquivo_imagem_2 = new QLabel(layoutWidget_2);
        label_arquivo_imagem_2->setObjectName("label_arquivo_imagem_2");

        verticalLayout_4->addWidget(label_arquivo_imagem_2);

        listView_arquivo_imagem_2 = new QListView(layoutWidget_2);
        listView_arquivo_imagem_2->setObjectName("listView_arquivo_imagem_2");

        verticalLayout_4->addWidget(listView_arquivo_imagem_2);

        layoutWidget_3 = new QWidget(groupBox_5);
        layoutWidget_3->setObjectName("layoutWidget_3");
        layoutWidget_3->setGeometry(QRect(10, 30, 258, 216));
        verticalLayout_13 = new QVBoxLayout(layoutWidget_3);
        verticalLayout_13->setObjectName("verticalLayout_13");
        verticalLayout_13->setContentsMargins(0, 0, 0, 0);
        label_diretorio_imagem_2 = new QLabel(layoutWidget_3);
        label_diretorio_imagem_2->setObjectName("label_diretorio_imagem_2");

        verticalLayout_13->addWidget(label_diretorio_imagem_2);

        treeView_diretorio_imagem_2 = new QTreeView(layoutWidget_3);
        treeView_diretorio_imagem_2->setObjectName("treeView_diretorio_imagem_2");

        verticalLayout_13->addWidget(treeView_diretorio_imagem_2);

        pushButton_selecionar_cancelar_aritimetica = new QPushButton(page_4);
        pushButton_selecionar_cancelar_aritimetica->setObjectName("pushButton_selecionar_cancelar_aritimetica");
        pushButton_selecionar_cancelar_aritimetica->setGeometry(QRect(600, 80, 131, 24));
        stackedWidget->addWidget(page_4);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuArquivo = new QMenu(menubar);
        menuArquivo->setObjectName("menuArquivo");
        menuAjuda = new QMenu(menubar);
        menuAjuda->setObjectName("menuAjuda");
        menuFerramentas = new QMenu(menubar);
        menuFerramentas->setObjectName("menuFerramentas");
        MainWindow->setMenuBar(menubar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        toolBar->setMovable(false);
        toolBar->setIconSize(QSize(16, 16));
        toolBar->setFloatable(false);
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        menubar->addAction(menuArquivo->menuAction());
        menubar->addAction(menuFerramentas->menuAction());
        menubar->addAction(menuAjuda->menuAction());
        menuArquivo->addAction(actionSalvar_2);
        menuArquivo->addAction(actionSair);
        menuAjuda->addAction(actionSobre);
        menuFerramentas->addAction(actionQuantizacao_2);
        menuFerramentas->addAction(actionAritimetica);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(4);
        comboBox_niveis_canal->setCurrentIndex(3);
        comboBox_profundidade_bits->setCurrentIndex(3);
        comboBox_numero_cores->setCurrentIndex(2);
        comboBox_criterio_parada->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "PDI", nullptr));
        actionSalvar->setText(QCoreApplication::translate("MainWindow", "Salvar", nullptr));
        actionImprimir->setText(QCoreApplication::translate("MainWindow", "Imprimir", nullptr));
        actionSair->setText(QCoreApplication::translate("MainWindow", "Sair", nullptr));
        actionSobre->setText(QCoreApplication::translate("MainWindow", "Sobre", nullptr));
        actionQuantizacao->setText(QCoreApplication::translate("MainWindow", "Quantiza\303\247\303\243o", nullptr));
        actionAritimetica->setText(QCoreApplication::translate("MainWindow", "Aritim\303\251tica", nullptr));
        actionQuantizacao_2->setText(QCoreApplication::translate("MainWindow", "Quantiza\303\247\303\243o", nullptr));
        actionSalvar_2->setText(QCoreApplication::translate("MainWindow", "Salvar", nullptr));
        label_titulo1->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#ff0000;\">Quantiza\303\247\303\243o</span></p></body></html>", nullptr));
        label_imagem_modificada->setText(QString());
        label_imagem_original->setText(QString());
        pushButton_aplicar->setText(QCoreApplication::translate("MainWindow", "Selecionar Algoritmo", nullptr));
        pushButton_procurar->setText(QCoreApplication::translate("MainWindow", "Procurar", nullptr));
        label_diretorios->setText(QCoreApplication::translate("MainWindow", "Diret\303\263rios:", nullptr));
        label_arquivos->setText(QCoreApplication::translate("MainWindow", "Arquivos:", nullptr));
        pushButton_selecionar->setText(QCoreApplication::translate("MainWindow", "Selecionar", nullptr));
        pushButton_cancelar->setText(QCoreApplication::translate("MainWindow", "Cancelar", nullptr));
        groupBox_qu->setTitle(QCoreApplication::translate("MainWindow", "Quantiza\303\247\303\243o Uniforme", nullptr));
        label_qu1->setText(QCoreApplication::translate("MainWindow", "Selecione os par\303\242metros", nullptr));
        label_qu2->setText(QCoreApplication::translate("MainWindow", "N\303\255veis por canal:", nullptr));
        comboBox_niveis_canal->setItemText(0, QCoreApplication::translate("MainWindow", "2", nullptr));
        comboBox_niveis_canal->setItemText(1, QCoreApplication::translate("MainWindow", "4", nullptr));
        comboBox_niveis_canal->setItemText(2, QCoreApplication::translate("MainWindow", "8", nullptr));
        comboBox_niveis_canal->setItemText(3, QCoreApplication::translate("MainWindow", "16", nullptr));

        label_qu3->setText(QCoreApplication::translate("MainWindow", "Profundidade de bits", nullptr));
        comboBox_profundidade_bits->setItemText(0, QCoreApplication::translate("MainWindow", "1", nullptr));
        comboBox_profundidade_bits->setItemText(1, QCoreApplication::translate("MainWindow", "2", nullptr));
        comboBox_profundidade_bits->setItemText(2, QCoreApplication::translate("MainWindow", "4", nullptr));
        comboBox_profundidade_bits->setItemText(3, QCoreApplication::translate("MainWindow", "6", nullptr));

        pushButton_aplicar_qu->setText(QCoreApplication::translate("MainWindow", "Aplicar Quantiza\303\247\303\243o Uniforme", nullptr));
        groupBox_cm->setTitle(QCoreApplication::translate("MainWindow", "Corte Mediano", nullptr));
        label_cm1->setText(QCoreApplication::translate("MainWindow", "Selecione os par\303\242metros", nullptr));
        label_cm2->setText(QCoreApplication::translate("MainWindow", "N\303\272mero de cores:", nullptr));
        comboBox_numero_cores->setItemText(0, QCoreApplication::translate("MainWindow", "16", nullptr));
        comboBox_numero_cores->setItemText(1, QCoreApplication::translate("MainWindow", "32", nullptr));
        comboBox_numero_cores->setItemText(2, QCoreApplication::translate("MainWindow", "64", nullptr));
        comboBox_numero_cores->setItemText(3, QCoreApplication::translate("MainWindow", "128", nullptr));
        comboBox_numero_cores->setItemText(4, QCoreApplication::translate("MainWindow", "256", nullptr));

        label_cm3->setText(QCoreApplication::translate("MainWindow", "Crit\303\251rio de parada (divis\303\265es):", nullptr));
        comboBox_criterio_parada->setItemText(0, QCoreApplication::translate("MainWindow", "4", nullptr));
        comboBox_criterio_parada->setItemText(1, QCoreApplication::translate("MainWindow", "6", nullptr));
        comboBox_criterio_parada->setItemText(2, QCoreApplication::translate("MainWindow", "8", nullptr));

        pushButton_aplicar_cm->setText(QCoreApplication::translate("MainWindow", "Aplicar Corte Mediano", nullptr));
        pushButton_cancelar_algoritmo->setText(QCoreApplication::translate("MainWindow", "Cancelar", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:22pt; font-weight:700; color:#ff0000;\">PdI</span><span style=\" font-size:22pt; font-weight:700;\"><br/></span><span style=\" font-size:22pt;\">Processamento de Imagens 1.1</span></p></body></html>", nullptr));
        textEdit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Programa desenvolvido pelo Discente Raniere Mendes dos Santos, do Curso de Engenharia da Computa\303\247\303\243o da Universidade Federal do Maranh\303\243o (UFMA) com objetivo de apresentar os entreg\303\241veis da disciplina Processamentos de Imagens ministrada pelo Professor Dr. Aristofanes Correa Silva, do Curso de Ci\303\252ncia da Computa\303\247\303\243o no per\303\255odo 2026.1.</p></body></ht"
                        "ml>", nullptr));
        pushButton_voltar->setText(QCoreApplication::translate("MainWindow", "Voltar", nullptr));
        label_titulo1_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#ff0000;\">Algor\303\255tmos Aritim\303\251ticos</span></p></body></html>", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Opera\303\247\303\243o", nullptr));
        radioButton->setText(QCoreApplication::translate("MainWindow", "Soma de imagens", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MainWindow", "Subtra\303\247\303\243o de imagens", nullptr));
        radioButton_3->setText(QCoreApplication::translate("MainWindow", "Multiplica\303\247\303\243o por escalar", nullptr));
        radioButton_4->setText(QCoreApplication::translate("MainWindow", "Divis\303\243o por escalar", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Valor", nullptr));
#if QT_CONFIG(tooltip)
        lineEdit_valor->setToolTip(QCoreApplication::translate("MainWindow", "Adicione um valor de 0 a 255", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Imagens", nullptr));
        label_imagem_principal->setText(QCoreApplication::translate("MainWindow", "Imagem Original", nullptr));
        label_imagem_adicional->setText(QCoreApplication::translate("MainWindow", "Imagem Adicional", nullptr));
        label_imagem_resultado->setText(QCoreApplication::translate("MainWindow", "Imagem Resultado", nullptr));
        label_imagem_1->setText(QString());
        label_imagem_2->setText(QString());
        label_imagem_3->setText(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "Procurar imagem", nullptr));
        pushButton_calcular->setText(QCoreApplication::translate("MainWindow", "Calcular", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "Imagem Principal", nullptr));
        label_arquivo_imagem_1->setText(QCoreApplication::translate("MainWindow", "Arquivo", nullptr));
        label_diretorio_imagem_1->setText(QCoreApplication::translate("MainWindow", "Diret\303\263rio:", nullptr));
        pushButton_selecionar_imagens_aritimetica->setText(QCoreApplication::translate("MainWindow", "Aplicar", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "Imagem Adicional", nullptr));
        label_arquivo_imagem_2->setText(QCoreApplication::translate("MainWindow", "Arquivo", nullptr));
        label_diretorio_imagem_2->setText(QCoreApplication::translate("MainWindow", "Diret\303\263rio:", nullptr));
        pushButton_selecionar_cancelar_aritimetica->setText(QCoreApplication::translate("MainWindow", "Cancelar", nullptr));
        menuArquivo->setTitle(QCoreApplication::translate("MainWindow", "Arquivo", nullptr));
        menuAjuda->setTitle(QCoreApplication::translate("MainWindow", "Ajuda", nullptr));
        menuFerramentas->setTitle(QCoreApplication::translate("MainWindow", "Ferramentas", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
