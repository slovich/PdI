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

std::vector<std::vector<int>> Dithering::gerarMatrizCluster(int clusterSize, int formaPonto) {
    std::vector<std::vector<int>> matriz(clusterSize, std::vector<int>(clusterSize, 0));
    int maxVal = clusterSize * clusterSize;

    // Preenche matriz conforme forma
    for (int y = 0; y < clusterSize; ++y) {
        for (int x = 0; x < clusterSize; ++x) {
            switch (formaPonto) {
            case 0: // Circular
                matriz[y][x] = (x - clusterSize/2)*(x - clusterSize/2) + (y - clusterSize/2)*(y - clusterSize/2);
                break;
            case 1: // Quadrado
                matriz[y][x] = std::max(std::abs(x - clusterSize/2), std::abs(y - clusterSize/2));
                break;
            case 2: // Elíptico
                matriz[y][x] = ((x - clusterSize/2)*(x - clusterSize/2)) + ((y - clusterSize/2)*(y - clusterSize/2))/2;
                break;
            case 3: // Linha/Trama
                matriz[y][x] = (x + y) % clusterSize;
                break;
            default:
                matriz[y][x] = (x + y) % clusterSize;
            }
        }
    }

    // Normaliza valores para [0, maxVal)
    int minVal = matriz[0][0], maxFound = matriz[0][0];
    for (auto& linha : matriz) {
        for (auto v : linha) {
            minVal = std::min(minVal, v);
            maxFound = std::max(maxFound, v);
        }
    }
    for (auto& linha : matriz) {
        for (auto& v : linha) {
            v = (v - minVal) * maxVal / std::max(1, maxFound - minVal);
        }
    }

    return matriz;
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

QImage Dithering::burkes(const QImage& imagem, int niveisCinza, int resolucao)
{
    // 1. Ajustar resolução
    QImage img = imagem.convertToFormat(QImage::Format_Grayscale8);
    if (resolucao > 0) {
        img = img.scaled(resolucao, resolucao, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    }

    int w = img.width();
    int h = img.height();
    QImage resultado = img;

    // 2. Buffer de trabalho
    std::vector<std::vector<double>> buffer(h, std::vector<double>(w));
    for (int y = 0; y < h; ++y) {
        const uchar* linha = img.scanLine(y);
        for (int x = 0; x < w; ++x) {
            buffer[y][x] = linha[x];
        }
    }

    // 3. Algoritmo de Burkes
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            double oldPixel = buffer[y][x];
            int newPixel = qRound((oldPixel * (niveisCinza - 1)) / 255.0) * (255 / (niveisCinza - 1));
            resultado.setPixel(x, y, qRgb(newPixel, newPixel, newPixel));

            double erro = oldPixel - newPixel;

            // Distribuição do erro (linha atual)
            if (x + 1 < w) buffer[y][x + 1] += erro * (8.0 / 32.0);
            if (x + 2 < w) buffer[y][x + 2] += erro * (4.0 / 32.0);

            // Linha seguinte
            if (y + 1 < h) {
                if (x - 2 >= 0) buffer[y + 1][x - 2] += erro * (2.0 / 32.0);
                if (x - 1 >= 0) buffer[y + 1][x - 1] += erro * (4.0 / 32.0);
                buffer[y + 1][x] += erro * (8.0 / 32.0);
                if (x + 1 < w) buffer[y + 1][x + 1] += erro * (4.0 / 32.0);
                if (x + 2 < w) buffer[y + 1][x + 2] += erro * (2.0 / 32.0);
            }
        }
    }

    return resultado;
}

QImage Dithering::jarvisJudiceNinke(const QImage& imagem, int niveisCinza, int resolucao)
{
    // 1. Ajustar resolução
    QImage img = imagem.convertToFormat(QImage::Format_Grayscale8);
    if (resolucao > 0) {
        img = img.scaled(resolucao, resolucao, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    }

    int w = img.width();
    int h = img.height();
    QImage resultado = img;

    // 2. Buffer de trabalho
    std::vector<std::vector<double>> buffer(h, std::vector<double>(w));
    for (int y = 0; y < h; ++y) {
        const uchar* linha = img.scanLine(y);
        for (int x = 0; x < w; ++x) {
            buffer[y][x] = linha[x];
        }
    }

    // 3. Algoritmo JJN
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            double oldPixel = buffer[y][x];
            int step = 255 / (niveisCinza - 1);
            int newPixel = qRound(oldPixel / step) * step;
            resultado.setPixel(x, y, qRgb(newPixel, newPixel, newPixel));

            double erro = oldPixel - newPixel;

            // Linha atual
            if (x + 1 < w) buffer[y][x + 1] += erro * (7.0 / 48.0);
            if (x + 2 < w) buffer[y][x + 2] += erro * (5.0 / 48.0);

            // Linha seguinte (y+1)
            if (y + 1 < h) {
                if (x - 2 >= 0) buffer[y + 1][x - 2] += erro * (3.0 / 48.0);
                if (x - 1 >= 0) buffer[y + 1][x - 1] += erro * (5.0 / 48.0);
                buffer[y + 1][x] += erro * (7.0 / 48.0);
                if (x + 1 < w) buffer[y + 1][x + 1] += erro * (5.0 / 48.0);
                if (x + 2 < w) buffer[y + 1][x + 2] += erro * (3.0 / 48.0);
            }

            // Linha seguinte (y+2)
            if (y + 2 < h) {
                if (x - 2 >= 0) buffer[y + 2][x - 2] += erro * (1.0 / 48.0);
                if (x - 1 >= 0) buffer[y + 2][x - 1] += erro * (3.0 / 48.0);
                buffer[y + 2][x] += erro * (5.0 / 48.0);
                if (x + 1 < w) buffer[y + 2][x + 1] += erro * (3.0 / 48.0);
                if (x + 2 < w) buffer[y + 2][x + 2] += erro * (1.0 / 48.0);
            }
        }
    }

    return resultado;
}

QImage Dithering::stucki(const QImage& imagem, int niveisCinza, int resolucao)
{
    // 1. Ajustar resolução
    QImage img = imagem.convertToFormat(QImage::Format_Grayscale8);
    if (resolucao > 0) {
        img = img.scaled(resolucao, resolucao, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    }

    int w = img.width();
    int h = img.height();
    QImage resultado = img;

    // 2. Buffer de trabalho
    std::vector<std::vector<double>> buffer(h, std::vector<double>(w));
    for (int y = 0; y < h; ++y) {
        const uchar* linha = img.scanLine(y);
        for (int x = 0; x < w; ++x) {
            buffer[y][x] = linha[x];
        }
    }

    // 3. Algoritmo Stucki
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            double oldPixel = buffer[y][x];
            int step = 255 / (niveisCinza - 1);
            int newPixel = qRound(oldPixel / step) * step;
            resultado.setPixel(x, y, qRgb(newPixel, newPixel, newPixel));

            double erro = oldPixel - newPixel;

            // Linha atual
            if (x + 1 < w) buffer[y][x + 1] += erro * (8.0 / 42.0);
            if (x + 2 < w) buffer[y][x + 2] += erro * (4.0 / 42.0);

            // Linha seguinte (y+1)
            if (y + 1 < h) {
                if (x - 2 >= 0) buffer[y + 1][x - 2] += erro * (2.0 / 42.0);
                if (x - 1 >= 0) buffer[y + 1][x - 1] += erro * (4.0 / 42.0);
                buffer[y + 1][x] += erro * (8.0 / 42.0);
                if (x + 1 < w) buffer[y + 1][x + 1] += erro * (4.0 / 42.0);
                if (x + 2 < w) buffer[y + 1][x + 2] += erro * (2.0 / 42.0);
            }

            // Linha seguinte (y+2)
            if (y + 2 < h) {
                if (x - 2 >= 0) buffer[y + 2][x - 2] += erro * (1.0 / 42.0);
                if (x - 1 >= 0) buffer[y + 2][x - 1] += erro * (2.0 / 42.0);
                buffer[y + 2][x] += erro * (4.0 / 42.0);
                if (x + 1 < w) buffer[y + 2][x + 1] += erro * (2.0 / 42.0);
                if (x + 2 < w) buffer[y + 2][x + 2] += erro * (1.0 / 42.0);
            }
        }
    }

    return resultado;
}

QImage Dithering::atkinson(const QImage& imagem, int niveisCinza, int resolucao)
{
    // 1. Ajustar resolução
    QImage img = imagem.convertToFormat(QImage::Format_Grayscale8);
    if (resolucao > 0) {
        img = img.scaled(resolucao, resolucao, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    }

    int w = img.width();
    int h = img.height();
    QImage resultado = img;

    // 2. Buffer de trabalho
    std::vector<std::vector<double>> buffer(h, std::vector<double>(w));
    for (int y = 0; y < h; ++y) {
        const uchar* linha = img.scanLine(y);
        for (int x = 0; x < w; ++x) {
            buffer[y][x] = linha[x];
        }
    }

    // 3. Algoritmo Atkinson
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            double oldPixel = buffer[y][x];
            int step = 255 / (niveisCinza - 1);
            int newPixel = qRound(oldPixel / step) * step;
            resultado.setPixel(x, y, qRgb(newPixel, newPixel, newPixel));

            double erro = (oldPixel - newPixel) / 2.0; // erro reduzido pela metade

            // Linha atual
            if (x + 1 < w) buffer[y][x + 1] += erro * (1.0 / 8.0);
            if (x + 2 < w) buffer[y][x + 2] += erro * (1.0 / 8.0);

            // Linha seguinte (y+1)
            if (y + 1 < h) {
                if (x - 1 >= 0) buffer[y + 1][x - 1] += erro * (1.0 / 8.0);
                buffer[y + 1][x] += erro * (1.0 / 8.0);
                if (x + 1 < w) buffer[y + 1][x + 1] += erro * (1.0 / 8.0);
            }

            // Linha seguinte (y+2)
            if (y + 2 < h) {
                buffer[y + 2][x] += erro * (1.0 / 8.0);
            }
        }
    }

    return resultado;
}

QImage Dithering::sierra0(const QImage& imagem, int niveisCinza, int resolucao)
{
    QImage img = imagem.convertToFormat(QImage::Format_Grayscale8);
    if (resolucao > 0)
        img = img.scaled(resolucao, resolucao, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    int w = img.width(), h = img.height();
    QImage resultado = img;
    std::vector<std::vector<double>> buffer(h, std::vector<double>(w));

    for (int y = 0; y < h; ++y) {
        const uchar* linha = img.scanLine(y);
        for (int x = 0; x < w; ++x) buffer[y][x] = linha[x];
    }

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            double oldPixel = buffer[y][x];
            int step = 255 / (niveisCinza - 1);
            int newPixel = qRound(oldPixel / step) * step;
            resultado.setPixel(x, y, qRgb(newPixel, newPixel, newPixel));
            double erro = oldPixel - newPixel;

            if (x+1<w) buffer[y][x+1]+=erro*(5.0/32.0);
            if (x+2<w) buffer[y][x+2]+=erro*(3.0/32.0);

            if (y+1<h) {
                if (x-2>=0) buffer[y+1][x-2]+=erro*(2.0/32.0);
                if (x-1>=0) buffer[y+1][x-1]+=erro*(4.0/32.0);
                buffer[y+1][x]+=erro*(5.0/32.0);
                if (x+1<w) buffer[y+1][x+1]+=erro*(4.0/32.0);
                if (x+2<w) buffer[y+1][x+2]+=erro*(2.0/32.0);
            }
            if (y+2<h) {
                if (x-1>=0) buffer[y+2][x-1]+=erro*(2.0/32.0);
                buffer[y+2][x]+=erro*(3.0/32.0);
                if (x+1<w) buffer[y+2][x+1]+=erro*(2.0/32.0);
            }
        }
    }
    return resultado;
}

QImage Dithering::sierra1(const QImage& imagem, int niveisCinza, int resolucao)
{
    QImage img = imagem.convertToFormat(QImage::Format_Grayscale8);
    if (resolucao > 0)
        img = img.scaled(resolucao, resolucao, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    int w = img.width(), h = img.height();
    QImage resultado = img;
    std::vector<std::vector<double>> buffer(h, std::vector<double>(w));

    for (int y = 0; y < h; ++y) {
        const uchar* linha = img.scanLine(y);
        for (int x = 0; x < w; ++x) buffer[y][x] = linha[x];
    }

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            double oldPixel = buffer[y][x];
            int step = 255 / (niveisCinza - 1);
            int newPixel = qRound(oldPixel / step) * step;
            resultado.setPixel(x, y, qRgb(newPixel, newPixel, newPixel));
            double erro = oldPixel - newPixel;

            if (x+1<w) buffer[y][x+1]+=erro*(4.0/16.0);
            if (x+2<w) buffer[y][x+2]+=erro*(3.0/16.0);

            if (y+1<h) {
                if (x-1>=0) buffer[y+1][x-1]+=erro*(1.0/16.0);
                buffer[y+1][x]+=erro*(2.0/16.0);
                if (x+1<w) buffer[y+1][x+1]+=erro*(3.0/16.0);
                if (x+2<w) buffer[y+1][x+2]+=erro*(1.0/16.0);
            }
        }
    }
    return resultado;
}

QImage Dithering::sierra2(const QImage& imagem, int niveisCinza, int resolucao)
{
    QImage img = imagem.convertToFormat(QImage::Format_Grayscale8);
    if (resolucao > 0)
        img = img.scaled(resolucao, resolucao, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    int w = img.width(), h = img.height();
    QImage resultado = img;
    std::vector<std::vector<double>> buffer(h, std::vector<double>(w));

    for (int y = 0; y < h; ++y) {
        const uchar* linha = img.scanLine(y);
        for (int x = 0; x < w; ++x) buffer[y][x] = linha[x];
    }

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            double oldPixel = buffer[y][x];
            int step = 255 / (niveisCinza - 1);
            int newPixel = qRound(oldPixel / step) * step;
            resultado.setPixel(x, y, qRgb(newPixel, newPixel, newPixel));
            double erro = oldPixel - newPixel;

            // Linha atual
            if (x+1<w) buffer[y][x+1]+=erro*(5.0/32.0);
            if (x+2<w) buffer[y][x+2]+=erro*(3.0/32.0);

            // Linha seguinte (y+1)
            if (y+1<h) {
                if (x-1>=0) buffer[y+1][x-1]+=erro*(2.0/32.0);
                buffer[y+1][x]+=erro*(4.0/32.0);
                if (x+1<w) buffer[y+1][x+1]+=erro*(2.0/32.0);
            }
        }
    }
    return resultado;
}

// Função auxiliar para gerar matriz de Bayer
std::vector<std::vector<int>> gerarMatrizBayer(int n) {
    if (n == 2) {
        return {{0, 2},
                {3, 1}};
    }
    auto menor = gerarMatrizBayer(n/2);
    std::vector<std::vector<int>> matriz(n, std::vector<int>(n));
    for (int y = 0; y < n/2; ++y) {
        for (int x = 0; x < n/2; ++x) {
            int v = menor[y][x];
            matriz[y][x] = 4*v;
            matriz[y][x+n/2] = 4*v+2;
            matriz[y+n/2][x] = 4*v+3;
            matriz[y+n/2][x+n/2] = 4*v+1;
        }
    }
    return matriz;
}

QImage Dithering::bayerMatrix(const QImage& imagem, int niveisCinza, int resolucao, int tamanhoMatriz)
{
    // 1. Ajustar resolução
    QImage img = imagem.convertToFormat(QImage::Format_Grayscale8);
    if (resolucao > 0)
        img = img.scaled(resolucao, resolucao, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    int w = img.width(), h = img.height();
    QImage resultado(w, h, QImage::Format_Grayscale8);

    // 2. Gerar matriz de Bayer
    auto matriz = gerarMatrizBayer(tamanhoMatriz);
    int maxVal = tamanhoMatriz * tamanhoMatriz;

    // 3. Aplicar dithering
    for (int y = 0; y < h; ++y) {
        const uchar* linha = img.scanLine(y);
        uchar* out = resultado.scanLine(y);
        for (int x = 0; x < w; ++x) {
            int val = linha[x];
            int step = 255 / (niveisCinza - 1);

            // Normaliza pixel para [0, niveisCinza)
            double norm = (val / 255.0) * (niveisCinza - 1);

            // Limiar da matriz
            int limiar = matriz[y % tamanhoMatriz][x % tamanhoMatriz];
            double ajuste = limiar / (double)maxVal;

            // Decide se arredonda para cima ou para baixo
            int quant = (int)norm;
            if (norm - quant > ajuste) quant++;

            int newPixel = quant * step;
            out[x] = static_cast<uchar>(newPixel);
        }
    }

    return resultado;
}

QImage Dithering::clusteredDot(const QImage& imagem, int niveisCinza, int resolucao, int clusterSize, int formaPonto)
{
    // 1. Ajustar resolução
    QImage img = imagem.convertToFormat(QImage::Format_Grayscale8);
    if (resolucao > 0)
        img = img.scaled(resolucao, resolucao, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    int w = img.width(), h = img.height();
    QImage resultado(w, h, QImage::Format_Grayscale8);

    // 2. Gerar matriz de cluster
    auto matriz = gerarMatrizCluster(clusterSize, formaPonto);
    int maxVal = clusterSize * clusterSize;

    // 3. Aplicar dithering
    for (int y = 0; y < h; ++y) {
        const uchar* linha = img.scanLine(y);
        uchar* out = resultado.scanLine(y);
        for (int x = 0; x < w; ++x) {
            int val = linha[x];
            int step = 255 / (niveisCinza - 1);

            // Normaliza pixel para [0, niveisCinza)
            double norm = (val / 255.0) * (niveisCinza - 1);

            // Limiar do cluster
            int limiar = matriz[y % clusterSize][x % clusterSize];
            double ajuste = limiar / (double)maxVal;

            // Decide arredondamento
            int quant = (int)norm;
            if (norm - quant > ajuste) quant++;

            int newPixel = quant * step;
            out[x] = static_cast<uchar>(newPixel);
        }
    }

    return resultado;
}

#include <random>

QImage Dithering::randomDithering(const QImage& imagem, int niveisCinza, int resolucao, int ruido)
{
    // 1. Ajustar resolução
    QImage img = imagem.convertToFormat(QImage::Format_Grayscale8);
    if (resolucao > 0)
        img = img.scaled(resolucao, resolucao, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    int w = img.width(), h = img.height();
    QImage resultado(w, h, QImage::Format_Grayscale8);

    // 2. Configurar gerador de números aleatórios
    std::random_device rd;
    std::mt19937 gen(rd());

    // Ruído padrão: 0 → faixa normal, -1 → menos ruído, 1 → mais ruído
    int intensidadeRuido;
    if (ruido == -1) intensidadeRuido = 16;   // menos ruído
    else if (ruido == 1) intensidadeRuido = 64; // mais ruído
    else intensidadeRuido = 32;               // padrão

    std::uniform_int_distribution<int> dist(-intensidadeRuido, intensidadeRuido);

    // 3. Aplicar dithering aleatório
    for (int y = 0; y < h; ++y) {
        const uchar* linha = img.scanLine(y);
        uchar* out = resultado.scanLine(y);
        for (int x = 0; x < w; ++x) {
            int val = linha[x];

            // Adiciona ruído aleatório
            val = std::clamp(val + dist(gen), 0, 255);

            // Quantização para níveis de cinza
            int step = 255 / (niveisCinza - 1);
            int newPixel = static_cast<int>(std::round(static_cast<double>(val) / step)) * step;

            out[x] = static_cast<uchar>(newPixel);
        }
    }

    return resultado;
}
