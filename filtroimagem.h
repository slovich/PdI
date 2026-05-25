#ifndef FILTROIMAGEM_H
#define FILTROIMAGEM_H

#include <QImage>
#include <QColor>

class FiltroImagem {
public:
    // Construtor
    FiltroImagem();

    // Método para aplicar filtro de média
    // Recebe: imagem original, tamanho do kernel, tipo de borda,
    // flags para aplicar em cada canal RGB.
    QImage filtroMedia(const QImage& imagem, int kernelSize, int borderType, bool aplicarR, bool aplicarG, bool aplicarB);

    // Método para aplicar filtro de média em imagens em tons de cinza
    // Recebe: imagem original, tamanho do kernel, tipo de borda.
    QImage filtroMediaGrayscale(const QImage& imagem, int kernelSize, int borderType);

    // Método para aplicar filtro de mediana
    // Recebe: imagem original, tamanho do kernel, tipo de borda,
    // flags para aplicar em cada canal RGB.
    QImage filtroMediana(const QImage& imagem, int kernelSize, int borderType, bool aplicarR, bool aplicarG, bool aplicarB);

    // Método para aplicar filtro de mediana em imagens em tons de cinza
    // Recebe: imagem original, tamanho do kernel, tipo de borda.
    QImage filtroMedianaGrayscale(const QImage& imagem, int kernelSize, int borderType);

    // Método para aplicar filtro CLAHE (Contrast Limited Adaptive Histogram Equalization)
    // Recebe: imagem original, tamanho do kernel, tipo de borda, tamanho da grade e limite de contraste
    // flags para aplicar em cada canal RGB.
    QImage filtroCLAHE(const QImage& imagem, int tileGridWidth, int tileGridHeight, double clipLimit, int borderType, bool aplicarR, bool aplicarG, bool aplicarB);

    // Filtro de Máximo em RGB
    QImage filtroMaximo(const QImage& imagem, int matriz, int borderType, bool aplicarR, bool aplicarG, bool aplicarB, int formaVizinhanca);

    // Filtro de Máximo em Grayscale
    QImage filtroMaximoGrayscale(const QImage& imagem, int matriz, int borderType, int formaVizinhanca);

    // Filtro de Mínimo em RGB
    QImage filtroMinimo(const QImage& imagem, int matriz, int borderType, bool aplicarR, bool aplicarG, bool aplicarB, int formaVizinhanca);

    // Filtro de Mínimo em Grayscale
    QImage filtroMinimoGrayscale(const QImage& imagem, int matriz, int borderType, int formaVizinhanca);

    //Filtro Gaussiano para imagens RGB
    QImage filtroGaussiano(const QImage& imagem, int kernelSize, double sigma, int borderType, bool aplicarR, bool aplicarG, bool aplicarB);

    //Filtro Gaussiano para imagens em Grayscale
    QImage filtroGaussianoGrayscale(const QImage& imagem, int kernelSize, double sigma, int borderType);

    // Método para aplicar filtro CLAHE em imagens em tons de cinza
    // Recebe: imagem original, tamanho do kernel, tipo de borda, tamanho da grade e limite de contraste
    QImage filtroCLAHEGrayscale(const QImage& imagem, int tileGridWidth, int tileGridHeight, double clipLimit, int borderType);

    // Método para tratar bordas (padding)
    // Recebe: imagem original, tamanho do kernel, tipo de borda
    // Retorna: imagem expandida com bordas tratadas.
    QImage tratarBordas(const QImage& imagem, int kernelSize, int borderType);

    //Método auxiliar que verifica a vizinhança dos pixels para aplicação do filtro de Máximo e Mínimo
    bool dentroVizinhanca(int kx, int ky, int offset, int formaVizinhanca);

    //Função auxiliar para gerar máscara gaussiana
    std::vector<std::vector<double>> gerarMascaraGaussiana(int kernelSize, double sigma);
};

#endif // FILTROIMAGEM_H