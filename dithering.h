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

    QImage floydSteinberg(const QImage& imagem, int niveisCinza, int resolucao);
};

#endif // DITHERING_H
