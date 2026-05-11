#ifndef HISTOGRAMAIMAGEM_H
#define HISTOGRAMAIMAGEM_H

#include <QImage>
#include <QColor>
#include <vector>

class HistogramaImagem {
public:
    // Recebe uma imagem e retorna um QImage com o histograma
    static QImage gerarHistograma(const QImage& imagem, int largura = 512, int altura = 256);
};

#endif // HISTOGRAMAIMAGEM_H
