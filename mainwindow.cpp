#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "quantizacao.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->toolBar->addAction(ui->actionQuantizacao_2);
    ui->toolBar->addAction(ui->actionAritimetica);
    ui->actionQuantizacao_2->setIcon(QIcon(":/img/resource/img/quantizacao.png"));
    ui->actionAritimetica->setIcon(QIcon(":/img/resource/img/aritimetico.png"));
    /*Trabalha os modles reponsavel pela listagem de diretórios e arquivos nos exploradores*/
    QString caminho = "C:/";
    dirmodel = new QFileSystemModel(this);
    dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirmodel->setRootPath(caminho);                                                         //Define o diretório inicial da lista de arquivos pelo conteudo da 'String' caminho
    ui->treeView_dir->setModel(dirmodel);                                                   //Aplica o 'model' "filemodel" à 'listview' de arquivos
    dirmodel_1 = new QFileSystemModel(this);
    dirmodel_1->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirmodel_1->setRootPath(caminho);                                                       //Define o diretório inicial da lista de arquivos pelo conteudo da 'String' caminho
    ui->treeView_diretorio_imagem_1->setModel(dirmodel_1);
    dirmodel_2 = new QFileSystemModel(this);
    dirmodel_2->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirmodel_2->setRootPath(caminho);
    ui->treeView_diretorio_imagem_2->setModel(dirmodel_2);
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
    /* define os filtros de extensão de imagens permitidas no programa*/
    QStringList filtros;                                                                    //cria o filtro
    filtros << "*.jpg" << "*.jpeg" << "*.png" << "*.bmp" << "*.tiff";                       //define as extensões de arquivos permitidas
    filemodel->setNameFilters(filtros);                                                     //aplica o filtro à lista de arquivos
    filemodel->setNameFilterDisables(false);                                                //aplica o filtro
    filemodel_1->setNameFilters(filtros);
    filemodel_1->setNameFilterDisables(false);
    filemodel_2->setNameFilters(filtros);
    filemodel_2->setNameFilterDisables(false);
    /*Valida os dados de entrada para multiplicação e divisão de imagens por escalar*/
    validator = new QIntValidator(0, 255, this);
    ui->lineEdit_valor->setValidator(validator);
    /*Garante a visibiidade inicial correta na página de operações aritiméticas*/
    ui->groupBox_2->setVisible(false);
    ui->groupBox_2->setVisible(true);
}

MainWindow::~MainWindow()
{
    delete ui;
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
        ui->label_imagem_original->setPixmap(pixmap.scaled(ui->label_imagem_original->size(),Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->label_imagem_original->setScaledContents(false);
            // Redimensiona mantendo proporção
        //QPixmap scaled = pixmap.scaled(500, 500, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        //ui->label_imagem_original->setPixmap(pixmap.scaled(500, 500, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        //ui->label_imagem_original->setScaledContents(true);
        // retorna para o índice 0 do stackedWidget
        ui->stackedWidget->setCurrentIndex(0);
    }
    else {
        // arquivo não é imagem válida → ignora ou mostra aviso
        QMessageBox::warning(this, "Arquivo inválido",
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
        QMessageBox::warning(this,
                             "Imagem não selecionada",
                             "Por favor, selecione uma imagem válida antes de aplicar o algoritmo.");
    }
}


void MainWindow::on_pushButton_aplicar_qu_clicked()
{
    // Verifica se há imagem original carregada
    QPixmap pixmap = ui->label_imagem_original->pixmap();
    if (!pixmap || pixmap.isNull()) {
        QMessageBox::warning(this, "Imagem não selecionada",
                             "Selecione uma imagem válida antes de aplicar o algoritmo.");
        return;
    }

    // Converte para QImage
    QImage imagem_original = pixmap.toImage();

    // Lê parâmetros dos combobox
    int niveisPorCanal = ui->comboBox_niveis_canal->currentText().toInt();
    int bitsPorCanal   = ui->comboBox_profundidade_bits->currentText().toInt();

    // Cria objeto Quantizacao e aplica algoritmo
    Quantizacao q(imagem_original, niveisPorCanal, bitsPorCanal);
    QImage resultado = q.aplicarQuantizacaoUniforme(niveisPorCanal, bitsPorCanal);

    // Exibe resultado no label da imagem processada
    ui->label_imagem_modificada->setPixmap(QPixmap::fromImage(resultado).scaled(ui->label_imagem_modificada->size(),Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->label_imagem_modificada->setScaledContents(false);

    // Retorna para índice 0
    ui->stackedWidget->setCurrentIndex(0);

}


void MainWindow::on_pushButton_aplicar_cm_clicked()
{
    QPixmap pixmap = ui->label_imagem_original->pixmap();
    if (!pixmap || pixmap.isNull()) {
        QMessageBox::warning(this, "Imagem não selecionada",
                             "Selecione uma imagem válida antes de aplicar o algoritmo.");
        return;
    }

    QImage imagem_original = pixmap.toImage();

    // Lê parâmetros dos combobox
    int numeroCores    = ui->comboBox_numero_cores->currentText().toInt();
    int criterioParada = ui->comboBox_criterio_parada->currentText().toInt();

    // Cria objeto Quantizacao e aplica algoritmo
    Quantizacao q(imagem_original, numeroCores, criterioParada);
    QImage resultado = q.aplicarCorteMediano(numeroCores, criterioParada);

    // Exibe resultado no label da imagem processada
    ui->label_imagem_modificada->setPixmap(QPixmap::fromImage(resultado).scaled(ui->label_imagem_modificada->size(),Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->label_imagem_modificada->setScaledContents(false);

    // Retorna para índice 0
    ui->stackedWidget->setCurrentIndex(0);

}

//Salva a imagem modificada como um PNG
void MainWindow::on_actionSalvar_2_triggered()
{
    // Verifica se há imagem processada
    QPixmap pixmap = ui->label_imagem_modificada->pixmap();
    if (!pixmap || pixmap.isNull()) {
        QMessageBox::warning(this, "Nenhuma imagem",
                             "Não há imagem processada para salvar.");
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
        QMessageBox::critical(this, "Erro",
                              "Não foi possível salvar a imagem.");
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
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_actionAritimetica_triggered()
{
    ui->stackedWidget->setCurrentIndex(4);
}
void MainWindow::on_radioButton_clicked()
{
    ui->label_imagem_2->setVisible(true);
    ui->groupBox_2->setVisible(false);
    ui->groupBox_5->setVisible(true);
}


void MainWindow::on_radioButton_2_clicked()
{
    ui->label_imagem_2->setVisible(true);
    ui->groupBox_2->setVisible(false);
    ui->groupBox_5->setVisible(true);
}


void MainWindow::on_radioButton_3_clicked()
{
    ui->label_imagem_2->setVisible(false);
    ui->groupBox_2->setVisible(true);
    ui->groupBox_5->setVisible(false);
}


void MainWindow::on_radioButton_4_clicked()
{
    ui->label_imagem_2->setVisible(false);
    ui->groupBox_2->setVisible(true);
    ui->groupBox_5->setVisible(false);
}


void MainWindow::on_pushButton_selecionar_cancelar_aritimetica_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

