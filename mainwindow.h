#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include <QPixmap>
#include <QFileDialog>
#include <QIntValidator>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_pushButton_selecionar_clicked();                                                //Método ao se clicar no botão de selecionar após escolher uma imagem
    void on_pushButton_procurar_clicked();                                                  //Método ao se clicar no botão de procurar imagem
    void on_treeView_dir_clicked(const QModelIndex &index);                                 //Método que atualiza o diretrio de exibição da lista de arquivos quando há mudança na árvore de diretórios.
    void on_treeView_diretorio_imagem_1_clicked(const QModelIndex &index1);
    void on_treeView_diretorio_imagem_2_clicked(const QModelIndex &index2);
    void on_pushButton_cancelar_clicked();
    void on_pushButton_cancelar_algoritmo_clicked();
    void on_pushButton_aplicar_clicked();
    void on_pushButton_aplicar_qu_clicked();
    void on_pushButton_aplicar_cm_clicked();
    void on_pushButton_voltar_clicked();                                                    //Método que retorna para página inicial estando na página Sobre do menu Ajuda
    void on_actionSalvar_2_triggered();
    void on_actionSair_triggered();
    void on_actionSobre_triggered();
    void on_actionQuantizacao_2_triggered();
    void on_actionAritimetica_triggered();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_pushButton_selecionar_cancelar_aritimetica_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QFileSystemModel *dirmodel, *dirmodel_1, *dirmodel_2;
    QFileSystemModel *filemodel, *filemodel_1, *filemodel_2;
    QIntValidator *validator;
};
#endif // MAINWINDOW_H
