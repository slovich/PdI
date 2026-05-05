#include "filtroimagem.h"
#include <algorithm>

// Construtor
FiltroImagem::FiltroImagem() {}

// Método para tratar bordas (padding)
QImage FiltroImagem::tratarBordas(const QImage& imagem, int kernelSize, int borderType) {
    int offset = kernelSize / 2;
    int novaLargura = imagem.width() + 2 * offset;
    int novaAltura  = imagem.height() + 2 * offset;

    QImage expandida(novaLargura, novaAltura, imagem.format());

    for (int y = 0; y < novaAltura; ++y) {
        for (int x = 0; x < novaLargura; ++x) {
            int srcX = x - offset;
            int srcY = y - offset;

            if (srcX < 0 || srcY < 0 || srcX >= imagem.width() || srcY >= imagem.height()) {
                switch (borderType) {
                case 0: // zeros
                    expandida.setPixel(x, y, qRgb(0,0,0));
                    break;
                case 1: // replicar
                    srcX = std::max(0, std::min(srcX, imagem.width()-1));
                    srcY = std::max(0, std::min(srcY, imagem.height()-1));
                    expandida.setPixel(x, y, imagem.pixel(srcX, srcY));
                    break;
                case 2: // refletir
                    if (srcX < 0) srcX = -srcX;
                    if (srcY < 0) srcY = -srcY;
                    if (srcX >= imagem.width()) srcX = 2*imagem.width()-srcX-2;
                    if (srcY >= imagem.height()) srcY = 2*imagem.height()-srcY-2;
                    expandida.setPixel(x, y, imagem.pixel(srcX, srcY));
                    break;
                }
            } else {
                expandida.setPixel(x, y, imagem.pixel(srcX, srcY));
            }
        }
    }
    return expandida;
}

// Método para aplicar filtro de média
QImage FiltroImagem::filtroMedia(const QImage& imagem, int kernelSize, int borderType,
                                 bool aplicarR, bool aplicarG, bool aplicarB)
{
    int offset = kernelSize / 2;
    QImage expandida = tratarBordas(imagem, kernelSize, borderType);
    QImage resultado(imagem.size(), imagem.format());

    for (int y = offset; y < expandida.height() - offset; ++y) {
        for (int x = offset; x < expandida.width() - offset; ++x) {
            int somaR = 0, somaG = 0, somaB = 0;

            for (int ky = -offset; ky <= offset; ++ky) {
                for (int kx = -offset; kx <= offset; ++kx) {
                    QColor cor(expandida.pixel(x + kx, y + ky));
                    if (aplicarR) somaR += cor.red();
                    if (aplicarG) somaG += cor.green();
                    if (aplicarB) somaB += cor.blue();
                }
            }

            int total = kernelSize * kernelSize;
            QColor original(expandida.pixel(x,y));
            int r = aplicarR ? somaR / total : original.red();
            int g = aplicarG ? somaG / total : original.green();
            int b = aplicarB ? somaB / total : original.blue();

            resultado.setPixel(x - offset, y - offset, qRgb(r, g, b));
        }
    }
    return resultado;
}

// Método para aplicar filtro de média em imagens grayscale
QImage FiltroImagem::filtroMediaGrayscale(const QImage& imagem, int kernelSize, int borderType)
{
    int offset = kernelSize / 2;
    QImage expandida = tratarBordas(imagem, kernelSize, borderType);
    QImage resultado(imagem.size(), imagem.format());

    for (int y = offset; y < expandida.height() - offset; ++y) {
        for (int x = offset; x < expandida.width() - offset; ++x) {
            int soma = 0;

            // percorre vizinhos
            for (int ky = -offset; ky <= offset; ++ky) {
                for (int kx = -offset; kx <= offset; ++kx) {
                    QColor cor(expandida.pixel(x + kx, y + ky));
                    soma += cor.red(); // em grayscale, R=G=B
                }
            }

            int total = kernelSize * kernelSize;
            int intensidade = soma / total;

            // Ajusta coordenadas para imagem original
            resultado.setPixel(x - offset, y - offset, qRgb(intensidade, intensidade, intensidade));
        }
    }
    return resultado;
}

QImage FiltroImagem::filtroMediana(const QImage& imagem, int kernelSize, int borderType,
                                      bool aplicarR, bool aplicarG, bool aplicarB)
{
    int offset = kernelSize / 2;
    QImage expandida = tratarBordas(imagem, kernelSize, borderType);
    QImage resultado(imagem.size(), imagem.format());

    for (int y = offset; y < expandida.height() - offset; ++y) {
        for (int x = offset; x < expandida.width() - offset; ++x) {
            std::vector<int> valoresR, valoresG, valoresB;

            for (int ky = -offset; ky <= offset; ++ky) {
                for (int kx = -offset; kx <= offset; ++kx) {
                    QColor cor(expandida.pixel(x + kx, y + ky));
                    if (aplicarR) valoresR.push_back(cor.red());
                    if (aplicarG) valoresG.push_back(cor.green());
                    if (aplicarB) valoresB.push_back(cor.blue());
                }
            }

            QColor original(expandida.pixel(x,y));

            auto mediana = [](std::vector<int>& v, int valorOriginal) {
                if (v.empty()) return valorOriginal;
                std::sort(v.begin(), v.end());
                return v[v.size()/2];
            };

            int r = aplicarR ? mediana(valoresR, original.red()) : original.red();
            int g = aplicarG ? mediana(valoresG, original.green()) : original.green();
            int b = aplicarB ? mediana(valoresB, original.blue()) : original.blue();

            resultado.setPixel(x - offset, y - offset, qRgb(r, g, b));
        }
    }
    return resultado;
}

QImage FiltroImagem::filtroMedianaGrayscale(const QImage& imagem, int kernelSize, int borderType)
{
    int offset = kernelSize / 2;
    QImage expandida = tratarBordas(imagem, kernelSize, borderType);
    QImage resultado(imagem.size(), imagem.format());

    for (int y = offset; y < expandida.height() - offset; ++y) {
        for (int x = offset; x < expandida.width() - offset; ++x) {
            std::vector<int> valores;

            for (int ky = -offset; ky <= offset; ++ky) {
                for (int kx = -offset; kx <= offset; ++kx) {
                    QColor cor(expandida.pixel(x + kx, y + ky));
                    valores.push_back(cor.red()); // em grayscale, R=G=B
                }
            }

            std::sort(valores.begin(), valores.end());
            int intensidade = valores[valores.size()/2];

            resultado.setPixel(x - offset, y - offset, qRgb(intensidade, intensidade, intensidade));
        }
    }
    return resultado;
}

QImage FiltroImagem::filtroCLAHE(const QImage& imagem,
                                    int tileGridWidth, int tileGridHeight,
                                    double clipLimit, int borderType,
                                    bool aplicarR, bool aplicarG, bool aplicarB)
{
    QImage expandida = tratarBordas(imagem, std::max(tileGridWidth, tileGridHeight), borderType);
    QImage resultado(imagem.size(), imagem.format());

    int largura = expandida.width();
    int altura  = expandida.height();
    int tileW = largura / tileGridWidth;
    int tileH = altura / tileGridHeight;

    auto aplicarCLAHECanal = [&](int canal, bool aplicar) {
        if (!aplicar) return;
        for (int ty = 0; ty < tileGridHeight; ++ty) {
            for (int tx = 0; tx < tileGridWidth; ++tx) {
                std::vector<int> hist(256, 0);

                // Histograma local
                for (int y = ty * tileH; y < (ty+1)*tileH; ++y) {
                    for (int x = tx * tileW; x < (tx+1)*tileW; ++x) {
                        QColor cor(expandida.pixel(x,y));
                        int valor = (canal==0?cor.red():(canal==1?cor.green():cor.blue()));
                        hist[valor]++;
                    }
                }

                // Limitação de contraste
                int excess = 0;
                for (int i = 0; i < 256; ++i) {
                    if (hist[i] > clipLimit) {
                        excess += hist[i] - clipLimit;
                        hist[i] = clipLimit;
                    }
                }
                int redist = excess / 256;
                for (int i = 0; i < 256; ++i) hist[i] += redist;

                // CDF
                std::vector<int> cdf(256,0);
                cdf[0] = hist[0];
                for (int i = 1; i < 256; ++i) cdf[i] = cdf[i-1] + hist[i];

                int totalPixels = tileW * tileH;
                for (int y = ty * tileH; y < (ty+1)*tileH && y < resultado.height(); ++y) {
                    for (int x = tx * tileW; x < (tx+1)*tileW && x < resultado.width(); ++x) {
                        QColor cor(expandida.pixel(x,y));
                        int valor = (canal==0?cor.red():(canal==1?cor.green():cor.blue()));
                        int novoValor = (cdf[valor] * 255) / totalPixels;

                        int r = (canal==0?novoValor:cor.red());
                        int g = (canal==1?novoValor:cor.green());
                        int b = (canal==2?novoValor:cor.blue());

                        resultado.setPixel(x, y, qRgb(r,g,b));
                    }
                }
            }
        }
    };

    aplicarCLAHECanal(0, aplicarR);
    aplicarCLAHECanal(1, aplicarG);
    aplicarCLAHECanal(2, aplicarB);

    return resultado;
}

QImage FiltroImagem::filtroCLAHEGrayscale(const QImage& imagem,
                                          int tileGridWidth, int tileGridHeight,
                                          double clipLimit, int borderType)
{
    QImage expandida = tratarBordas(imagem, std::max(tileGridWidth, tileGridHeight), borderType);
    QImage resultado(imagem.size(), imagem.format());

    int largura = expandida.width();
    int altura  = expandida.height();

    int tileW = largura / tileGridWidth;
    int tileH = altura / tileGridHeight;

    for (int ty = 0; ty < tileGridHeight; ++ty) {
        for (int tx = 0; tx < tileGridWidth; ++tx) {
            std::vector<int> hist(256, 0);

            // Histograma local
            for (int y = ty * tileH; y < (ty+1)*tileH; ++y) {
                for (int x = tx * tileW; x < (tx+1)*tileW; ++x) {
                    int intensidade = QColor(expandida.pixel(x,y)).red();
                    hist[intensidade]++;
                }
            }

            // Limitação de contraste
            int excess = 0;
            for (int i = 0; i < 256; ++i) {
                if (hist[i] > clipLimit) {
                    excess += hist[i] - clipLimit;
                    hist[i] = clipLimit;
                }
            }
            int redist = excess / 256;
            for (int i = 0; i < 256; ++i) hist[i] += redist;

            // CDF
            std::vector<int> cdf(256,0);
            cdf[0] = hist[0];
            for (int i = 1; i < 256; ++i) cdf[i] = cdf[i-1] + hist[i];

            int totalPixels = tileW * tileH;
            for (int y = ty * tileH; y < (ty+1)*tileH && y < resultado.height(); ++y) {
                for (int x = tx * tileW; x < (tx+1)*tileW && x < resultado.width(); ++x) {
                    int intensidade = QColor(expandida.pixel(x,y)).red();
                    int novoValor = (cdf[intensidade] * 255) / totalPixels;
                    resultado.setPixel(x, y, qRgb(novoValor, novoValor, novoValor));
                }
            }
        }
    }
    return resultado;
}