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

//Método de identificação da vizinhança de um pixel
bool FiltroImagem::dentroVizinhanca(int kx, int ky, int offset, int formaVizinhanca)
{
    switch (formaVizinhanca) {
    case 0: // Quadrado
        return true;
    case 1: // Circular
        return (kx*kx + ky*ky) <= (offset*offset);
    case 2: // Cruz
        return (kx == 0 || ky == 0);
    case 3: // Elíptico
        return ((kx*kx)/(offset*offset*1.0) + (ky*ky)/(offset*offset*1.0)) <= 1.0;
    default:
        return true;
    }
}

std::vector<std::vector<double>> FiltroImagem::gerarMascaraGaussiana(int kernelSize, double sigma) {
    int offset = kernelSize / 2;
    std::vector<std::vector<double>> kernel(kernelSize, std::vector<double>(kernelSize));
    double soma = 0.0;

    for (int y = -offset; y <= offset; ++y) {
        for (int x = -offset; x <= offset; ++x) {
            double valor = std::exp(-(x*x + y*y) / (2 * sigma * sigma));
            kernel[y + offset][x + offset] = valor;
            soma += valor;
        }
    }

    // Normalização
    for (int y = 0; y < kernelSize; ++y) {
        for (int x = 0; x < kernelSize; ++x) {
            kernel[y][x] /= soma;
        }
    }
    return kernel;
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

QImage FiltroImagem::filtroMaximo(const QImage& imagem, int matriz, int borderType,
                                  bool aplicarR, bool aplicarG, bool aplicarB, int formaVizinhanca)
{
    QImage img = tratarBordas(imagem, matriz, borderType);
    QImage resultado(img.size(), QImage::Format_RGB32);

    int offset = matriz / 2;

    for (int y = offset; y < img.height() - offset; ++y) {
        for (int x = offset; x < img.width() - offset; ++x) {
            int maxR = 0, maxG = 0, maxB = 0;

            for (int ky = -offset; ky <= offset; ++ky) {
                const QRgb* linha = reinterpret_cast<const QRgb*>(img.scanLine(y + ky));
                for (int kx = -offset; kx <= offset; ++kx) {
                    if (!dentroVizinhanca(kx, ky, offset, formaVizinhanca)) continue;
                    QRgb pixel = linha[x + kx];
                    if (aplicarR) maxR = std::max(maxR, qRed(pixel));
                    if (aplicarG) maxG = std::max(maxG, qGreen(pixel));
                    if (aplicarB) maxB = std::max(maxB, qBlue(pixel));
                }
            }

            QRgb original = img.pixel(x, y);
            int r = aplicarR ? maxR : qRed(original);
            int g = aplicarG ? maxG : qGreen(original);
            int b = aplicarB ? maxB : qBlue(original);

            resultado.setPixel(x, y, qRgb(r, g, b));
        }
    }
    return resultado;
}

QImage FiltroImagem::filtroMaximoGrayscale(const QImage& imagem, int matriz, int borderType, int formaVizinhanca)
{
    QImage img = tratarBordas(imagem, matriz, borderType);
    QImage resultado(img.size(), QImage::Format_Grayscale8);

    int offset = matriz / 2;

    for (int y = offset; y < img.height() - offset; ++y) {
        for (int x = offset; x < img.width() - offset; ++x) {
            int maxVal = 0;

            for (int ky = -offset; ky <= offset; ++ky) {
                const uchar* linha = img.scanLine(y + ky);
                for (int kx = -offset; kx <= offset; ++kx) {
                    if (!dentroVizinhanca(kx, ky, offset, formaVizinhanca)) continue;
                    int val = linha[x + kx];
                    maxVal = std::max(maxVal, val);
                }
            }
            resultado.setPixel(x, y, qRgb(maxVal, maxVal, maxVal));
        }
    }
    return resultado;
}

QImage FiltroImagem::filtroMinimo(const QImage& imagem, int matriz, int borderType,
                                  bool aplicarR, bool aplicarG, bool aplicarB, int formaVizinhanca)
{
    QImage img = tratarBordas(imagem, matriz, borderType);
    QImage resultado(img.size(), QImage::Format_RGB32);

    int offset = matriz / 2;

    for (int y = offset; y < img.height() - offset; ++y) {
        for (int x = offset; x < img.width() - offset; ++x) {
            int minR = 255, minG = 255, minB = 255;

            for (int ky = -offset; ky <= offset; ++ky) {
                const QRgb* linha = reinterpret_cast<const QRgb*>(img.scanLine(y + ky));
                for (int kx = -offset; kx <= offset; ++kx) {
                    if (!dentroVizinhanca(kx, ky, offset, formaVizinhanca)) continue;
                    QRgb pixel = linha[x + kx];
                    if (aplicarR) minR = std::min(minR, qRed(pixel));
                    if (aplicarG) minG = std::min(minG, qGreen(pixel));
                    if (aplicarB) minB = std::min(minB, qBlue(pixel));
                }
            }

            QRgb original = img.pixel(x, y);
            int r = aplicarR ? minR : qRed(original);
            int g = aplicarG ? minG : qGreen(original);
            int b = aplicarB ? minB : qBlue(original);

            resultado.setPixel(x, y, qRgb(r, g, b));
        }
    }
    return resultado;
}

QImage FiltroImagem::filtroMinimoGrayscale(const QImage& imagem, int matriz, int borderType, int formaVizinhanca)
{
    QImage img = tratarBordas(imagem, matriz, borderType);
    QImage resultado(img.size(), QImage::Format_Grayscale8);

    int offset = matriz / 2;

    for (int y = offset; y < img.height() - offset; ++y) {
        for (int x = offset; x < img.width() - offset; ++x) {
            int minVal = 255;

            for (int ky = -offset; ky <= offset; ++ky) {
                const uchar* linha = img.scanLine(y + ky);
                for (int kx = -offset; kx <= offset; ++kx) {
                    if (!dentroVizinhanca(kx, ky, offset, formaVizinhanca)) continue;
                    int val = linha[x + kx];
                    minVal = std::min(minVal, val);
                }
            }
            resultado.setPixel(x, y, qRgb(minVal, minVal, minVal));
        }
    }
    return resultado;
}

QImage FiltroImagem::filtroGaussiano(const QImage& imagem, int kernelSize, double sigma,
                                     int borderType, bool aplicarR, bool aplicarG, bool aplicarB)
{
    QImage img = tratarBordas(imagem, kernelSize, borderType);
    QImage resultado(img.size(), QImage::Format_RGB32);

    auto kernel = gerarMascaraGaussiana(kernelSize, sigma);
    int offset = kernelSize / 2;

    for (int y = offset; y < img.height() - offset; ++y) {
        for (int x = offset; x < img.width() - offset; ++x) {
            double somaR = 0, somaG = 0, somaB = 0;

            for (int ky = -offset; ky <= offset; ++ky) {
                const QRgb* linha = reinterpret_cast<const QRgb*>(img.scanLine(y + ky));
                for (int kx = -offset; kx <= offset; ++kx) {
                    QRgb pixel = linha[x + kx];
                    double peso = kernel[ky + offset][kx + offset];
                    if (aplicarR) somaR += qRed(pixel) * peso;
                    if (aplicarG) somaG += qGreen(pixel) * peso;
                    if (aplicarB) somaB += qBlue(pixel) * peso;
                }
            }

            QRgb original = img.pixel(x, y);
            int r = aplicarR ? static_cast<int>(somaR) : qRed(original);
            int g = aplicarG ? static_cast<int>(somaG) : qGreen(original);
            int b = aplicarB ? static_cast<int>(somaB) : qBlue(original);

            resultado.setPixel(x, y, qRgb(r, g, b));
        }
    }
    return resultado;
}

QImage FiltroImagem::filtroGaussianoGrayscale(const QImage& imagem, int kernelSize, double sigma, int borderType)
{
    QImage img = tratarBordas(imagem, kernelSize, borderType);
    QImage resultado(img.size(), QImage::Format_Grayscale8);

    auto kernel = gerarMascaraGaussiana(kernelSize, sigma);
    int offset = kernelSize / 2;

    for (int y = offset; y < img.height() - offset; ++y) {
        for (int x = offset; x < img.width() - offset; ++x) {
            double soma = 0;

            for (int ky = -offset; ky <= offset; ++ky) {
                const uchar* linha = img.scanLine(y + ky);
                for (int kx = -offset; kx <= offset; ++kx) {
                    int val = linha[x + kx];
                    double peso = kernel[ky + offset][kx + offset];
                    soma += val * peso;
                }
            }
            int valorFinal = static_cast<int>(soma);
            resultado.setPixel(x, y, qRgb(valorFinal, valorFinal, valorFinal));
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