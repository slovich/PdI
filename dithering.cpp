#include "Dithering.h"
#include <QtMath>
#include <QColor>

Dithering::Dithering() {}

QImage Dithering::preprocessamento(const QImage& imagem, bool aplicarSuavizacao,
                                   bool ajustarContraste, bool normalizarHistograma)
{
    QImage resultado = imagem.convertToFormat(QImage::Format_Grayscale8);

    // 1. Suavização Gaussiana leve (exemplo simples: média 3x3)
    if (aplicarSuavizacao) {
        QImage temp = resultado;
        int w = resultado.width();
        int h = resultado.height();

        for (int y = 1; y < h - 1; ++y) {
            for (int x = 1; x < w - 1; ++x) {
                int soma = 0;
                for (int ky = -1; ky <= 1; ++ky) {
                    const uchar* linha = temp.scanLine(y + ky);
                    for (int kx = -1; kx <= 1; ++kx) {
                        soma += linha[x + kx];
                    }
                }
                int media = soma / 9;
                resultado.setPixel(x, y, qRgb(media, media, media));
            }
        }
    }

    // 2. Ajuste de contraste simples
    if (ajustarContraste) {
        int w = resultado.width();
        int h = resultado.height();
        for (int y = 0; y < h; ++y) {
            uchar* linha = resultado.scanLine(y);
            for (int x = 0; x < w; ++x) {
                int val = linha[x];
                // Ajuste linear de contraste com conversão explícita
                double temp = (val - 128) * 1.2 + 128;
                temp = qBound(0.0, temp, 255.0); // todos os parâmetros como double
                linha[x] = static_cast<uchar>(temp);
            }
        }
    }

    // 3. Normalização de histograma
    if (normalizarHistograma) {
        int w = resultado.width();
        int h = resultado.height();

        int minVal = 255, maxVal = 0;
        for (int y = 0; y < h; ++y) {
            const uchar* linha = resultado.scanLine(y);
            for (int x = 0; x < w; ++x) {
                int val = linha[x];
                minVal = std::min(minVal, val);
                maxVal = std::max(maxVal, val);
            }
        }

        for (int y = 0; y < h; ++y) {
            uchar* linha = resultado.scanLine(y);
            for (int x = 0; x < w; ++x) {
                int val = linha[x];
                val = (val - minVal) * 255 / std::max(1, maxVal - minVal);
                linha[x] = static_cast<uchar>(val);
            }
        }
    }

    return resultado;
}

QImage Dithering::floydSteinberg(const QImage& imagem, int niveisCinza, int resolucao)
{
    // 1. Ajustar resolução (se diferente da original)
    QImage img = imagem.convertToFormat(QImage::Format_Grayscale8);
    if (resolucao > 0) {
        img = img.scaled(resolucao, resolucao, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    }

    int w = img.width();
    int h = img.height();
    QImage resultado = img;

    // 2. Converter para buffer de trabalho (double para acumular erro)
    std::vector<std::vector<double>> buffer(h, std::vector<double>(w));
    for (int y = 0; y < h; ++y) {
        const uchar* linha = img.scanLine(y);
        for (int x = 0; x < w; ++x) {
            buffer[y][x] = linha[x];
        }
    }

    // 3. Floyd–Steinberg
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            double oldPixel = buffer[y][x];
            // Quantização para níveis de cinza
            int newPixel = qRound((oldPixel * (niveisCinza - 1)) / 255.0) * (255 / (niveisCinza - 1));
            resultado.setPixel(x, y, qRgb(newPixel, newPixel, newPixel));

            double erro = oldPixel - newPixel;

            // Distribuição do erro
            if (x + 1 < w) buffer[y][x + 1] += erro * 7.0 / 16.0;
            if (y + 1 < h && x > 0) buffer[y + 1][x - 1] += erro * 3.0 / 16.0;
            if (y + 1 < h) buffer[y + 1][x] += erro * 5.0 / 16.0;
            if (y + 1 < h && x + 1 < w) buffer[y + 1][x + 1] += erro * 1.0 / 16.0;
        }
    }

    return resultado;
}