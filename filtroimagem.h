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

    // Método para aplicar filtro CLAHE em imagens em tons de cinza
    // Recebe: imagem original, tamanho do kernel, tipo de borda, tamanho da grade e limite de contraste
    QImage filtroCLAHEGrayscale(const QImage& imagem, int tileGridWidth, int tileGridHeight, double clipLimit, int borderType);

    // Método para tratar bordas (padding)
    // Recebe: imagem original, tamanho do kernel, tipo de borda
    // Retorna: imagem expandida com bordas tratadas.
    QImage tratarBordas(const QImage& imagem, int kernelSize, int borderType);
};

#endif // FILTROIMAGEM_H