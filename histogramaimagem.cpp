#include "histogramaimagem.h"
#include <algorithm>

QImage HistogramaImagem::gerarHistograma(const QImage& imagem, int largura, int altura)
{
    // Vetores para cada canal
    std::vector<int> histR(256,0), histG(256,0), histB(256,0);

    // Calcula histograma
    for (int y = 0; y < imagem.height(); ++y) {
        for (int x = 0; x < imagem.width(); ++x) {
            QColor cor(imagem.pixel(x,y));
            histR[cor.red()]++;
            histG[cor.green()]++;
            histB[cor.blue()]++;
        }
    }

    // Normaliza valores para caber na altura da imagem
    int maxR = *std::max_element(histR.begin(), histR.end());
    int maxG = *std::max_element(histG.begin(), histG.end());
    int maxB = *std::max_element(histB.begin(), histB.end());
    int maxVal = std::max({maxR, maxG, maxB});

    // Cria imagem do histograma (fundo preto)
    QImage histograma(largura, altura, QImage::Format_RGB32);
    histograma.fill(Qt::black);

    // Desenha cada canal
    for (int i = 0; i < 256; ++i) {
        int hR = (histR[i] * altura) / maxVal;
        int hG = (histG[i] * altura) / maxVal;
        int hB = (histB[i] * altura) / maxVal;

        // Posição horizontal proporcional
        int x = (i * largura) / 256;

        // Desenha linhas verticais para cada canal
        for (int y = altura-1; y >= altura-hR; --y) {
            histograma.setPixel(x, y, qRgb(255,0,0)); // vermelho
        }
        for (int y = altura-1; y >= altura-hG; --y) {
            histograma.setPixel(x, y, qRgb(0,255,0)); // verde
        }
        for (int y = altura-1; y >= altura-hB; --y) {
            histograma.setPixel(x, y, qRgb(0,0,255)); // azul
        }
    }

    return histograma;
}
