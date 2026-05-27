#ifndef DITHERING_H
#define DITHERING_H

#include <QImage>

class Dithering {
public:
    // Construtor
    Dithering();

    // Método de pré-processamento
    QImage preprocessamento(const QImage& imagem, bool aplicarSuavizacao = true,
                            bool ajustarContraste = false, bool normalizarHistograma = false);

    //Algoritmos de Dithering
    QImage floydSteinberg(const QImage& imagem, int niveisCinza, int resolucao);
    QImage burkes(const QImage& imagem, int niveisCinza, int resolucao);
    QImage jarvisJudiceNinke(const QImage& imagem, int niveisCinza, int resolucao);
    QImage stucki(const QImage& imagem, int niveisCinza, int resolucao);
    QImage atkinson(const QImage& imagem, int niveisCinza, int resolucao);
    QImage sierra0(const QImage& imagem, int niveisCinza, int resolucao);
    QImage sierra1(const QImage& imagem, int niveisCinza, int resolucao);
    QImage sierra2(const QImage& imagem, int niveisCinza, int resolucao);
    QImage bayerMatrix(const QImage& imagem, int niveisCinza, int resolucao, int tamanhoMatriz);
    QImage clusteredDot(const QImage& imagem, int niveisCinza, int resolucao, int clusterSize, int formaPonto);
    QImage randomDithering(const QImage& imagem, int niveisCinza, int resolucao, int ruido);

private:
    //Função auxiliar para gerar matriz de cluster
    std::vector<std::vector<int>> gerarMatrizCluster(int clusterSize, int formaPonto);
};



#endif // DITHERING_H
