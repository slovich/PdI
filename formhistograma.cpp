#include "formhistograma.h"
#include "ui_formhistograma.h"
#include "histogramaimagem.h"

FormHistograma::FormHistograma(QImage image1, QImage image2, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FormHistograma)
{
    ui->setupUi(this);
    setLayout(ui->gridLayout);
    setItensLayout();
    setMinimumSize(600, 400);
    ui->label_imagem_original->setPixmap(QPixmap::fromImage(image1));
    ui->label_imagem_modificada->setPixmap(QPixmap::fromImage(image2));
    ui->label_histograma_original->setPixmap(QPixmap::fromImage(getHistograma(&image1)));
    ui->label_histograma_modificada->setPixmap(QPixmap::fromImage(getHistograma(&image2)));
}

FormHistograma::~FormHistograma()
{
    delete ui;
}

void FormHistograma::setItensLayout()
{
    ui->gridLayout->setColumnStretch(0, 1);
    ui->gridLayout->setColumnStretch(1, 1);
    ui->gridLayout->setRowStretch(0, 1);
    ui->gridLayout->setRowStretch(1, 1);
    setWindowModality(Qt::ApplicationModal);
    ui->groupBox_1->setLayout(ui->verticalLayout_1);
    ui->verticalLayout_1->setContentsMargins(0,0,0,0);
    ui->verticalLayout_1->setAlignment(Qt::AlignCenter);
    ui->groupBox_2->setLayout(ui->verticalLayout_2);
    ui->verticalLayout_2->setContentsMargins(0,0,0,0);
    ui->verticalLayout_2->setAlignment(Qt::AlignCenter);
    ui->groupBox_3->setLayout(ui->verticalLayout_3);
    ui->verticalLayout_3->setContentsMargins(0,0,0,0);
    ui->verticalLayout_3->setAlignment(Qt::AlignCenter);
    ui->groupBox_4->setLayout(ui->verticalLayout_4);
    ui->verticalLayout_4->setContentsMargins(0,0,0,0);
    ui->verticalLayout_4->setAlignment(Qt::AlignCenter);
}

void FormHistograma::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);

    // Área total do QDialog
    int w = this->width();
    int h = this->height();

    // Calcula 90% da área
    int targetW = static_cast<int>(w * 0.9);
    int targetH = static_cast<int>(h * 0.9);

    // Centraliza
    int offsetX = (w - targetW) / 2;
    int offsetY = (h - targetH) / 2;

    // Aplica margens ao layout para ocupar 90% centralizado
    if (layout()) {
        layout()->setContentsMargins(offsetX, offsetY, offsetX, offsetY);
    }
}

QImage FormHistograma::getHistograma(QImage *img)
{
    HistogramaImagem *histograma = new HistogramaImagem;
    return histograma->gerarHistograma(*img);
}
