#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "aritmetica.h"
#include "quantizacao.h"
#include "transformacaogeometrica.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->toolBar->addAction(ui->actionQuantizacao_2);
    ui->toolBar->addAction(ui->actionAritimetica);
    ui->toolBar->addAction(ui->actionGeometrica);
    ui->actionQuantizacao_2->setIcon(QIcon(":/img/resource/img/quantizacao.png"));
    ui->actionAritimetica->setIcon(QIcon(":/img/resource/img/aritimetico.png"));
    ui->actionGeometrica->setIcon(QIcon(":/img/resource/img/geometrica.png"));
    /*Trabalha os models reponsaveis pela listagem de diretórios e arquivos nos exploradores*/
    QString caminho = "C:/";
    dirmodel = new QFileSystemModel(this);
    dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirmodel->setRootPath(
        caminho); //Define o diretório inicial da lista de arquivos pelo conteudo da 'String' caminho
    ui->treeView_dir->setModel(dirmodel); //Aplica o 'model' "filemodel" à 'listview' de arquivos
    dirmodel_1 = new QFileSystemModel(this);
    dirmodel_1->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirmodel_1->setRootPath(
        caminho); //Define o diretório inicial da lista de arquivos pelo conteudo da 'String' caminho
    ui->treeView_diretorio_imagem_1->setModel(dirmodel_1);
    dirmodel_2 = new QFileSystemModel(this);
    dirmodel_2->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirmodel_2->setRootPath(caminho);
    ui->treeView_diretorio_imagem_2->setModel(dirmodel_2);
    dirmodel_3 = new QFileSystemModel(this);
    dirmodel_3->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirmodel_3->setRootPath(caminho);
    ui->treeView_diretorio_imagem_geometrica->setModel(dirmodel_3);
    filemodel = new QFileSystemModel(this);
    filemodel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    filemodel->setRootPath(caminho);
    ui->listView_file->setModel(filemodel);
    filemodel_1 = new QFileSystemModel(this);
    filemodel_1->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    filemodel_1->setRootPath(caminho);
    ui->listView_arquivo_imagem_1->setModel(filemodel_1);
    filemodel_2 = new QFileSystemModel(this);
    filemodel_2->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    filemodel_2->setRootPath(caminho);
    ui->listView_arquivo_imagem_2->setModel(filemodel_2);
    filemodel_3 = new QFileSystemModel(this);
    filemodel_3->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    filemodel_3->setRootPath(caminho);
    ui->listView_arquivo_imagem_geometrica->setModel(filemodel_3);
    /* define os filtros de extensão de imagens permitidas no programa*/
    QStringList filtros; //cria o filtro
    filtros << "*.jpg" << "*.jpeg" << "*.png" << "*.bmp"
            << "*.tiff";                     //define as extensões de arquivos permitidas
    filemodel->setNameFilters(filtros);      //aplica o filtro à lista de arquivos
    filemodel->setNameFilterDisables(false); //aplica o filtro
    filemodel_1->setNameFilters(filtros);
    filemodel_1->setNameFilterDisables(false);
    filemodel_2->setNameFilters(filtros);
    filemodel_2->setNameFilterDisables(false);
    filemodel_3->setNameFilters(filtros);
    filemodel_3->setNameFilterDisables(false);
    /*Valida os dados de entrada para multiplicação e divisão de imagens por escalar*/
    validator = new QIntValidator(0, 255, this);
    ui->lineEdit_valor->setValidator(validator);
    /*Garante a visibiidade inicial correta na página de operações aritiméticas*/
    ui->groupBox_2->setVisible(false);
    selected_aritimethic_image_1 = false;
    selected_aritimethic_image_2 = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setDefaultImages()
{
    QPixmap pixmap(":/img/resource/img/default_img.png");
    ui->label_imagem_original->setPixmap(pixmap);
    ui->label_imagem_original->setScaledContents(true);
    ui->label_imagem_modificada->setPixmap(pixmap);
    ui->label_imagem_modificada->setScaledContents(true);
    ui->label_imagem_1->setPixmap(pixmap);
    ui->label_imagem_1->setScaledContents(true);
    ui->label_imagem_2->setPixmap(pixmap);
    ui->label_imagem_2->setScaledContents(true);
    ui->label_imagem_3->setPixmap(pixmap);
    ui->label_imagem_3->setScaledContents(true);
}

void MainWindow::on_pushButton_procurar_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_treeView_dir_clicked(const QModelIndex &index)
{
    QString novocaminho = dirmodel->fileInfo(index).absolutePath();
    ui->listView_file->setRootIndex(filemodel->setRootPath(novocaminho));
}

void MainWindow::on_treeView_diretorio_imagem_1_clicked(const QModelIndex &index1)
{
    QString novocaminho_1 = dirmodel_1->fileInfo(index1).absolutePath();
    ui->listView_arquivo_imagem_1->setRootIndex(filemodel_1->setRootPath(novocaminho_1));
}

void MainWindow::on_treeView_diretorio_imagem_2_clicked(const QModelIndex &index2)
{
    QString novocaminho_2 = dirmodel_2->fileInfo(index2).absolutePath();
    ui->listView_arquivo_imagem_2->setRootIndex(filemodel_2->setRootPath(novocaminho_2));
}

void MainWindow::on_pushButton_selecionar_clicked()
{
    // obtém o índice selecionado no listView
    QModelIndex index = ui->listView_file->currentIndex();

    if (!index.isValid()) {
        // nada selecionado → não faz nada
        return;
    }

    QString caminhoArquivo = filemodel->filePath(index);

    // verifica se é um arquivo válido de imagem
    QFileInfo info(caminhoArquivo);
    QString ext = info.suffix().toLower();
    if (ext == "jpg" || ext == "jpeg" || ext == "png" || ext == "bmp" || ext == "tiff") {
        // carrega no label do índice 0
        QPixmap pixmap(caminhoArquivo);
        ui->label_imagem_original->setPixmap(pixmap.scaled(ui->label_imagem_original->size(),
                                                           Qt::KeepAspectRatio,
                                                           Qt::SmoothTransformation));
        ui->label_imagem_original->setScaledContents(false);
        // Redimensiona mantendo proporção
        //QPixmap scaled = pixmap.scaled(500, 500, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        //ui->label_imagem_original->setPixmap(pixmap.scaled(500, 500, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        //ui->label_imagem_original->setScaledContents(true);
        // retorna para o índice 0 do stackedWidget
        ui->stackedWidget->setCurrentIndex(0);
    } else {
        // arquivo não é imagem válida → ignora ou mostra aviso
        QMessageBox::warning(this,
                             "Arquivo inválido",
                             "Selecione um arquivo de imagem válido (jpg, jpeg, png, bmp, tiff).");
    }
}
void MainWindow::on_pushButton_cancelar_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_cancelar_algoritmo_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_aplicar_clicked()
{
    //obtém o QPixmap diretamente
    QPixmap pixmap = ui->label_imagem_original->pixmap();

    if (!pixmap.isNull()) {
        // Há uma imagem válida → vai para índice 2
        ui->stackedWidget->setCurrentIndex(2);
    } else {
        // Não há imagem → mostra aviso
        QMessageBox::warning(
            this,
            "Imagem não selecionada",
            "Por favor, selecione uma imagem válida antes de aplicar o algoritmo.");
    }
}

void MainWindow::on_pushButton_aplicar_qu_clicked()
{
    // Verifica se há imagem original carregada
    QPixmap pixmap = ui->label_imagem_original->pixmap();
    if (!pixmap || pixmap.isNull()) {
        QMessageBox::warning(this,
                             "Imagem não selecionada",
                             "Selecione uma imagem válida antes de aplicar o algoritmo.");
        return;
    }

    // Converte para QImage
    QImage imagem_original = pixmap.toImage();

    // Lê parâmetros dos combobox
    int niveisPorCanal = ui->comboBox_niveis_canal->currentText().toInt();
    int bitsPorCanal = ui->comboBox_profundidade_bits->currentText().toInt();

    // Cria objeto Quantizacao e aplica algoritmo
    Quantizacao q(imagem_original, niveisPorCanal, bitsPorCanal);
    QImage resultado = q.aplicarQuantizacaoUniforme(niveisPorCanal, bitsPorCanal);

    // Exibe resultado no label da imagem processada
    ui->label_imagem_modificada->setPixmap(
        QPixmap::fromImage(resultado).scaled(ui->label_imagem_modificada->size(),
                                             Qt::KeepAspectRatio,
                                             Qt::SmoothTransformation));
    ui->label_imagem_modificada->setScaledContents(false);

    // Retorna para índice 0
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_aplicar_cm_clicked()
{
    QPixmap pixmap = ui->label_imagem_original->pixmap();
    if (!pixmap || pixmap.isNull()) {
        QMessageBox::warning(this,
                             "Imagem não selecionada",
                             "Selecione uma imagem válida antes de aplicar o algoritmo.");
        return;
    }

    QImage imagem_original = pixmap.toImage();

    // Lê parâmetros dos combobox
    int numeroCores = ui->comboBox_numero_cores->currentText().toInt();
    int criterioParada = ui->comboBox_criterio_parada->currentText().toInt();

    // Cria objeto Quantizacao e aplica algoritmo
    Quantizacao q(imagem_original, numeroCores, criterioParada);
    QImage resultado = q.aplicarCorteMediano(numeroCores, criterioParada);

    // Exibe resultado no label da imagem processada
    ui->label_imagem_modificada->setPixmap(
        QPixmap::fromImage(resultado).scaled(ui->label_imagem_modificada->size(),
                                             Qt::KeepAspectRatio,
                                             Qt::SmoothTransformation));
    ui->label_imagem_modificada->setScaledContents(false);

    // Retorna para índice 0
    ui->stackedWidget->setCurrentIndex(0);
}

//Salva a imagem modificada como um PNG
void MainWindow::on_actionSalvar_2_triggered()
{
    if (ui->stackedWidget->currentIndex() == 0) {
        // Verifica se há imagem processada
        QPixmap pixmap = ui->label_imagem_modificada->pixmap();
        if (!pixmap || pixmap.isNull()) {
            QMessageBox::warning(this, "Nenhuma imagem", "Não há imagem processada para salvar.");
            return;
        }

        // Abre diálogo para escolher local e formato
        QString fileName = QFileDialog::getSaveFileName(this,
                                                        "Salvar imagem",
                                                        QDir::homePath(),
                                                        "Imagens (*.png *.jpg *.bmp)");

        if (fileName.isEmpty())
            return;

        // Converte para QImage e salva
        QImage img = pixmap.toImage();
        if (!img.save(fileName)) {
            QMessageBox::critical(this, "Erro", "Não foi possível salvar a imagem.");
        }
    }
    if (ui->stackedWidget->currentIndex() == 4) {
        // Verifica se há imagem processada
        QPixmap pixmap = ui->label_imagem_3->pixmap();
        if (!pixmap || pixmap.isNull()) {
            QMessageBox::warning(this, "Nenhuma imagem", "Não há imagem processada para salvar.");
            return;
        }

        // Abre diálogo para escolher local e formato
        QString fileName = QFileDialog::getSaveFileName(this,
                                                        "Salvar imagem",
                                                        QDir::homePath(),
                                                        "Imagens (*.png *.jpg *.bmp)");

        if (fileName.isEmpty())
            return;

        // Converte para QImage e salva
        QImage img = pixmap.toImage();
        if (!img.save(fileName)) {
            QMessageBox::critical(this, "Erro", "Não foi possível salvar a imagem.");
        }
    }
    if (ui->stackedWidget->currentIndex() == 6) {
        // Verifica se há imagem processada
        QPixmap pixmap = ui->label_imagem_tg_modificada->pixmap();
        if (!pixmap || pixmap.isNull()) {
            QMessageBox::warning(this, "Nenhuma imagem", "Não há imagem processada para salvar.");
            return;
        }

        // Abre diálogo para escolher local e formato
        QString fileName = QFileDialog::getSaveFileName(this,
                                                        "Salvar imagem",
                                                        QDir::homePath(),
                                                        "Imagens (*.png *.jpg *.bmp)");

        if (fileName.isEmpty())
            return;

        // Converte para QImage e salva
        QImage img = pixmap.toImage();
        if (!img.save(fileName)) {
            QMessageBox::critical(this, "Erro", "Não foi possível salvar a imagem.");
        }
    }
}

//Fecha o programa
void MainWindow::on_actionSair_triggered()
{
    this->close();
}

void MainWindow::on_actionSobre_triggered()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_voltar_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_actionQuantizacao_2_triggered()
{
    setDefaultImages();
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_actionAritimetica_triggered()
{
    setDefaultImages();
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_actionGeometrica_triggered()
{
    setDefaultImages();
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_radioButton_clicked()
{
    ui->label_imagem_2->setVisible(true);
    ui->groupBox_2->setVisible(false);
    ui->groupBox_5->setVisible(true);
    ui->label_imagem_adicional->setVisible(true);
    setDefaultImages();
}

void MainWindow::on_radioButton_2_clicked()
{
    ui->label_imagem_2->setVisible(true);
    ui->groupBox_2->setVisible(false);
    ui->groupBox_5->setVisible(true);
    ui->label_imagem_adicional->setVisible(true);
    setDefaultImages();
}

void MainWindow::on_radioButton_3_clicked()
{
    ui->label_imagem_2->setVisible(false);
    ui->groupBox_2->setVisible(true);
    ui->groupBox_5->setVisible(false);
    ui->label_imagem_adicional->setVisible(false);
    setDefaultImages();
}

void MainWindow::on_radioButton_4_clicked()
{
    ui->label_imagem_2->setVisible(false);
    ui->groupBox_2->setVisible(true);
    ui->groupBox_5->setVisible(false);
    ui->label_imagem_adicional->setVisible(false);
    setDefaultImages();
}

void MainWindow::on_pushButton_selecionar_cancelar_aritimetica_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    selected_aritimethic_image_1 = false;
    selected_aritimethic_image_2 = false;
    if (ui->radioButton->isChecked() or ui->radioButton_2->isChecked()) {
        ui->groupBox_5->setVisible(true);
    }
    if (ui->radioButton_3->isChecked() or ui->radioButton_4->isChecked()) {
        ui->groupBox_5->setVisible(false);
    }
}

void MainWindow::on_pushButton_selecionar_imagens_aritimetica_clicked()
{
    // Código de adição de imagem para adição e subtração
    if (ui->radioButton->isChecked() or ui->radioButton_2->isChecked()) {
        //obtém o índice selecionado nos dois listView
        QModelIndex index1 = ui->listView_arquivo_imagem_1->currentIndex();
        QModelIndex index2 = ui->listView_arquivo_imagem_2->currentIndex();
        if (!(index1.isValid() or index2.isValid())) {
            // nada selecionado → não faz nada
            return;
        }
        //obtém o PATH para os arquivos selecionados
        QString caminhoArquivo1 = filemodel_1->filePath(index1);
        QString caminhoArquivo2 = filemodel_2->filePath(index2);
        // verifica se são arquivos válidos de imagens
        QFileInfo info1(caminhoArquivo1);
        QFileInfo info2(caminhoArquivo2);
        //Extrai as extensões dos arquivos selecionados para verificar se são arquivos válidos (jpeg, png, bmp, tiff)
        QString ext1 = info1.suffix().toLower();
        QString ext2 = info2.suffix().toLower();
        if ((ext1 == "jpg" || ext1 == "jpeg" || ext1 == "png" || ext1 == "bmp" || ext1 == "tiff")
            and (ext2 == "jpg" || ext2 == "jpeg" || ext2 == "png" || ext2 == "bmp"
                 || ext2 == "tiff")) {
            // carrega nos labels do índice 4
            QPixmap pixmap1(caminhoArquivo1);
            QPixmap pixmap2(caminhoArquivo2);
            //atribui as imagens validadas aos labels
            ui->label_imagem_1->setPixmap(pixmap1.scaled(ui->label_imagem_1->size(),
                                                         Qt::KeepAspectRatio,
                                                         Qt::SmoothTransformation));
            ui->label_imagem_2->setPixmap(pixmap2.scaled(ui->label_imagem_2->size(),
                                                         Qt::KeepAspectRatio,
                                                         Qt::SmoothTransformation));
            ui->label_imagem_1->setScaledContents(false);
            ui->label_imagem_2->setScaledContents(false);
            selected_aritimethic_image_1 = true;
            selected_aritimethic_image_2 = true;
            ui->stackedWidget->setCurrentIndex(4);
        } else {
            // Pelo menos um dos arquivos não é imagem válida → ignora ou mostra aviso
            QMessageBox::warning(
                this,
                "Arquivo inválido",
                "Selecione um arquivo de imagem válido (jpg, jpeg, png, bmp, tiff).");
        }
    }
    if (ui->radioButton_3->isChecked() or ui->radioButton_4->isChecked()) {
        //obtém o índice selecionado no listView
        QModelIndex index = ui->listView_arquivo_imagem_1->currentIndex();
        if (!index.isValid()) {
            // nada selecionado → não faz nada
            return;
        }
        //obtém o PATH do arquivo selecionado
        QString caminhoArquivo = filemodel_1->filePath(index);
        // verifica se o arquivo é válidos de imagens
        QFileInfo info(caminhoArquivo);
        //Extrai a extensão do arquivo selecionado para verificar se é um arquivos válido (jpeg, png, bmp, tiff)
        QString ext = info.suffix().toLower();
        if (ext == "jpg" || ext == "jpeg" || ext == "png" || ext == "bmp" || ext == "tiff") {
            // carrega imagem no label do índice 4
            QPixmap pixmap(caminhoArquivo);
            //atribui imagem validada no label
            ui->label_imagem_1->setPixmap(pixmap.scaled(ui->label_imagem_1->size(),
                                                        Qt::KeepAspectRatio,
                                                        Qt::SmoothTransformation));
            ui->label_imagem_1->setScaledContents(false);
            selected_aritimethic_image_1 = true;
            ui->stackedWidget->setCurrentIndex(4);
        } else {
            // Pelo menos um dos arquivos não é imagem válida → ignora ou mostra aviso
            QMessageBox::warning(
                this,
                "Arquivo inválido",
                "Selecione um arquivo de imagem válido (jpg, jpeg, png, bmp, tiff).");
        }
    }
}
void MainWindow::on_pushButton_calcular_clicked()
{
    //Verifica se é uma operação de soma ou subtração
    if (ui->radioButton->isChecked() or ui->radioButton_2->isChecked()) {
        //Verifica se ambas as imagens estão selecionadas.
        if (selected_aritimethic_image_1 == true and selected_aritimethic_image_2 == true) {
            if (ui->radioButton->isChecked()) {
                if (!ui->label_imagem_1->pixmap() || !ui->label_imagem_2->pixmap()) {
                    QMessageBox::warning(this, "Erro", "Imagens não carregadas.");
                    return;
                } else {
                    //Aplica a adição das imagens
                    QPixmap pixmap_pacela_1 = ui->label_imagem_1->pixmap();
                    QPixmap pixmap_pacela_2 = ui->label_imagem_2->pixmap();
                    QImage imagem_parcela_1 = pixmap_pacela_1.toImage();
                    QImage imagem_parcela_2 = pixmap_pacela_2.toImage();
                    QImage total = Aritmetica::somar(imagem_parcela_1, imagem_parcela_2);
                    ui->label_imagem_3->setPixmap(
                        QPixmap::fromImage(total).scaled(ui->label_imagem_3->size(),
                                                         Qt::KeepAspectRatio,
                                                         Qt::SmoothTransformation));
                    ui->label_imagem_3->setScaledContents(false);
                }
            }
            if (ui->radioButton_2->isChecked()) {
                if (!ui->label_imagem_1->pixmap() || !ui->label_imagem_2->pixmap()) {
                    QMessageBox::warning(this, "Erro", "Imagens não carregadas.");
                    return;
                } else {
                    //Aplica a adição das imagens
                    QPixmap pixmap_minuendo = ui->label_imagem_1->pixmap();
                    QPixmap pixmap_subtraendo = ui->label_imagem_2->pixmap();
                    QImage imagem_minuendo = pixmap_minuendo.toImage();
                    QImage imagem_subtraendo = pixmap_subtraendo.toImage();
                    QImage diferenca = Aritmetica::subtrair(imagem_minuendo, imagem_subtraendo);
                    ui->label_imagem_3->setPixmap(
                        QPixmap::fromImage(diferenca).scaled(ui->label_imagem_3->size(),
                                                             Qt::KeepAspectRatio,
                                                             Qt::SmoothTransformation));
                    ui->label_imagem_3->setScaledContents(false);
                }
            }
        } else {
            QMessageBox::warning(this, "Erro", "Variaveis de seleção falsas..");
        }
    }
    //Verifica se é uma operação de multiplicação ou divisão
    if (ui->radioButton_3->isChecked() or ui->radioButton_4->isChecked()) {
        //Verifica se a imagem original foi selecionada.
        if (selected_aritimethic_image_1 == true) {
            //Verifica se o valor da da multiplicação ou divisão foi inserido no campo apropriado e com valores válidos
            if (ui->lineEdit_valor->text().toInt() > 0
                and ui->lineEdit_valor->text().toInt() < 256) {
                if (ui->radioButton_3->isChecked()) {
                    if (!ui->label_imagem_1->pixmap()) {
                        QMessageBox::warning(this, "Erro", "Imagem não carregada.");
                        return;
                    } else {
                        //Aplica operação de multiplicação
                        QPixmap pixmap_multiplicando = ui->label_imagem_1->pixmap();
                        int multiplicador = ui->lineEdit_valor->text().toInt();
                        QImage imagem_multiplicando = pixmap_multiplicando.toImage();
                        QImage produto = Aritmetica::multiplicar(imagem_multiplicando,
                                                                 multiplicador);
                        ui->label_imagem_3->setPixmap(
                            QPixmap::fromImage(produto).scaled(ui->label_imagem_3->size(),
                                                               Qt::KeepAspectRatio,
                                                               Qt::SmoothTransformation));
                        ui->label_imagem_3->setScaledContents(false);
                    }
                }
                if (ui->radioButton_4->isChecked()) {
                    if (!ui->label_imagem_1->pixmap()) {
                        QMessageBox::warning(this, "Erro", "Imagem não carregada.");
                        return;
                    } else {
                        //Aplica operação de divisão
                        QPixmap pixmap_dividendo = ui->label_imagem_1->pixmap();
                        int divisor = ui->lineEdit_valor->text().toInt();
                        QImage imagem_dividendo = pixmap_dividendo.toImage();
                        QImage quociente = Aritmetica::dividir(imagem_dividendo, divisor);
                        ui->label_imagem_3->setPixmap(
                            QPixmap::fromImage(quociente).scaled(ui->label_imagem_3->size(),
                                                                 Qt::KeepAspectRatio,
                                                                 Qt::SmoothTransformation));
                        ui->label_imagem_3->setScaledContents(false);
                    }
                }
            } else {
                // Valor a ser multiplicado é vazio ou maior que o permitido
                QMessageBox::warning(this,
                                     "Valor inválido",
                                     "Indique um valor maior que 0 e menor ou igual a 255");
            }
        } else {
            // Imagem original não selecionada
            QMessageBox::warning(
                this,
                "Arquivo inválido",
                "Selecione um arquivo de imagem válido (jpg, jpeg, png, bmp, tiff).");
        }
    }
}

void MainWindow::on_treeView_diretorio_imagem_geometrica_clicked(const QModelIndex &index3)
{
    QString novocaminho_3 = dirmodel_3->fileInfo(index3).absolutePath();
    ui->listView_arquivo_imagem_geometrica->setRootIndex(filemodel_3->setRootPath(novocaminho_3));
}


void MainWindow::on_pushButton_selecionar_imagem_geometrica_clicked()
{
    // obtém o índice selecionado no listView
    QModelIndex index = ui->listView_arquivo_imagem_geometrica->currentIndex();

    if (!index.isValid()) {
        // nada selecionado → não faz nada
        return;
    }

    QString caminhoArquivo = filemodel_3->filePath(index);

    // verifica se é um arquivo válido de imagem
    QFileInfo info(caminhoArquivo);
    QString ext = info.suffix().toLower();
    if (ext == "jpg" || ext == "jpeg" || ext == "png" || ext == "bmp" || ext == "tiff") {
        // carrega no label do índice 0
        QPixmap pixmap(caminhoArquivo);
        ui->label_imagem_tg_original->setPixmap(pixmap.scaled(ui->label_imagem_tg_original->size(),
                                                           Qt::KeepAspectRatio,
                                                           Qt::SmoothTransformation));
        ui->label_imagem_tg_original->setScaledContents(false);
    } else {
        // arquivo não é imagem válida → ignora ou mostra aviso
        QMessageBox::warning(this,
                             "Arquivo inválido",
                             "Selecione um arquivo de imagem válido (jpg, jpeg, png, bmp, tiff).");
    }
}


void MainWindow::on_pushButton__rotacionar_imagem_geometrica_clicked()
{
    // Verifica se há imagem original carregada
    QPixmap pixmap = ui->label_imagem_tg_original->pixmap();
    if (!pixmap || pixmap.isNull()) {
        QMessageBox::warning(this,
                             "Imagem não selecionada",
                             "Selecione uma imagem válida antes de aplicar o algoritmo.");
        return;
    }
    // Converte para QImage
    QImage imagem_original = pixmap.toImage();
    // Lê o valor em graus em que a imagem deve ser rotacionada
    int graus_rotacao = ui->lineEdit_graus->text().toInt();
    // Cria objeto Transformação de Geométrica
    TransformacaoGeometrica *tg = new TransformacaoGeometrica;
    //Aplica a rotação na imagem
    QImage resultado = tg->rotacionar(imagem_original, graus_rotacao);
    // Exibe resultado no label da imagem processada
    ui->label_imagem_tg_modificada->setPixmap(
        QPixmap::fromImage(resultado).scaled(ui->label_imagem_tg_modificada->size(),
                                             Qt::KeepAspectRatio,
                                             Qt::SmoothTransformation));
    ui->label_imagem_tg_modificada->setScaledContents(false);
}


void MainWindow::on_pushButton_manter_alteracao_clicked()
{
    ui->label_imagem_tg_original->setPixmap(ui->label_imagem_tg_modificada->pixmap());
}


void MainWindow::on_pushButton_espelhamento_vertical_clicked()
{
    // Verifica se há imagem original carregada
    QPixmap pixmap = ui->label_imagem_tg_original->pixmap();
    if (!pixmap || pixmap.isNull()) {
        QMessageBox::warning(this,
                             "Imagem não selecionada",
                             "Selecione uma imagem válida antes de aplicar o algoritmo.");
        return;
    }
    // Converte para QImage
    QImage imagem_original = pixmap.toImage();
    // Cria objeto Transformação de Geométrica
    TransformacaoGeometrica *tg = new TransformacaoGeometrica;
    //Aplica o espelhamento vertical na imagem
    QImage resultado = tg->espelharVertical(imagem_original);
    // Exibe resultado no label da imagem processada
    ui->label_imagem_tg_modificada->setPixmap(
        QPixmap::fromImage(resultado).scaled(ui->label_imagem_tg_modificada->size(),
                                             Qt::KeepAspectRatio,
                                             Qt::SmoothTransformation));
    ui->label_imagem_tg_modificada->setScaledContents(false);
}


void MainWindow::on_pushButton_espelhamento_horizontal_clicked()
{
    // Verifica se há imagem original carregada
    QPixmap pixmap = ui->label_imagem_tg_original->pixmap();
    if (!pixmap || pixmap.isNull()) {
        QMessageBox::warning(this,
                             "Imagem não selecionada",
                             "Selecione uma imagem válida antes de aplicar o algoritmo.");
        return;
    }
    // Converte para QImage
    QImage imagem_original = pixmap.toImage();
    // Cria objeto Transformação de Geométrica
    TransformacaoGeometrica *tg = new TransformacaoGeometrica;
    //Aplica o espelhamento vertical na imagem
    QImage resultado = tg->espelharHorizontal(imagem_original);
    // Exibe resultado no label da imagem processada
    ui->label_imagem_tg_modificada->setPixmap(
        QPixmap::fromImage(resultado).scaled(ui->label_imagem_tg_modificada->size(),
                                             Qt::KeepAspectRatio,
                                             Qt::SmoothTransformation));
    ui->label_imagem_tg_modificada->setScaledContents(false);
}

