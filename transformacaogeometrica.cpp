#include "transformacaogeometrica.h"
#include <QtMath>
#include <QPainter>

TransformacaoGeometrica::TransformacaoGeometrica()
{
}

// Função de rotação
QImage TransformacaoGeometrica::rotacionar(const QImage &imagem, double graus)
{
    // Normaliza o ângulo para o intervalo [0, 360)
    graus = fmod(graus, 360.0);
    if (graus < 0) {
        graus += 360.0;
    }

    // Converte para radianos
    double rad = qDegreesToRadians(graus);

    // Dimensões originais
    int w = imagem.width();
    int h = imagem.height();

    // Calcula dimensões da nova imagem
    double cosA = qCos(rad);
    double sinA = qSin(rad);

    int newW = qAbs(w * cosA) + qAbs(h * sinA);
    int newH = qAbs(w * sinA) + qAbs(h * cosA);

    // Cria imagem de saída
    QImage resultado(newW, newH, QImage::Format_ARGB32);
    resultado.fill(Qt::transparent);

    // Usa QPainter para aplicar a rotação
    QPainter painter(&resultado);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    // Move o sistema de coordenadas para o centro da nova imagem
    painter.translate(newW / 2.0, newH / 2.0);

    // Aplica a rotação
    painter.rotate(graus);

    // Desenha a imagem original centralizada
    painter.translate(-w / 2.0, -h / 2.0);
    painter.drawImage(0, 0, imagem);

    painter.end();

    return resultado;
}

QImage TransformacaoGeometrica::espelharVertical(const QImage &imagem)
{
    QImage resultado(imagem.size(), imagem.format());

    int w = imagem.width();
    int h = imagem.height();

    for (int y = 0; y < h; ++y) {
        const QRgb *linhaOrig = reinterpret_cast<const QRgb *>(imagem.scanLine(y));
        QRgb *linhaDest = reinterpret_cast<QRgb *>(resultado.scanLine(h - 1 - y));
        for (int x = 0; x < w; ++x) {
            linhaDest[x] = linhaOrig[x];
        }
    }

    return resultado;
}

QImage TransformacaoGeometrica::espelharHorizontal(const QImage &imagem)
{
    QImage resultado(imagem.size(), imagem.format());

    int w = imagem.width();
    int h = imagem.height();

    for (int y = 0; y < h; ++y) {
        const QRgb *linhaOrig = reinterpret_cast<const QRgb *>(imagem.scanLine(y));
        QRgb *linhaDest = reinterpret_cast<QRgb *>(resultado.scanLine(y));
        for (int x = 0; x < w; ++x) {
            linhaDest[w - 1 - x] = linhaOrig[x];
        }
    }

    return resultado;
}

QImage TransformacaoGeometrica::transladarVertical(const QImage &imagem, int percentual)
{
    // Garante que o percentual esteja dentro do intervalo [-100, 100]
    if (percentual > 100) percentual = 100;
    if (percentual < -100) percentual = -100;

    int w = imagem.width();
    int h = imagem.height();

    // Calcula o deslocamento em pixels
    int deslocamento = (percentual * h) / 100;

    // Cria imagem de saída com mesmas dimensões
    QImage resultado(w, h, imagem.format());
    resultado.fill(Qt::transparent);

    // Copia os pixels com deslocamento
    for (int y = 0; y < h; ++y) {
        const QRgb *linhaOrig = reinterpret_cast<const QRgb *>(imagem.scanLine(y));
        int yDestino = y - deslocamento;

        if (yDestino >= 0 && yDestino < h) {
            QRgb *linhaDest = reinterpret_cast<QRgb *>(resultado.scanLine(yDestino));
            for (int x = 0; x < w; ++x) {
                linhaDest[x] = linhaOrig[x];
            }
        }
        // Pixels que saem fora do intervalo [0, h) são descartados
    }
    return resultado;
}

QImage TransformacaoGeometrica::transladarHorizontal(const QImage &imagem, int percentual)
{
    // Garante que o percentual esteja dentro do intervalo [-100, 100]
    if (percentual > 100) percentual = 100;
    if (percentual < -100) percentual = -100;

    int w = imagem.width();
    int h = imagem.height();

    // Calcula o deslocamento em pixels
    int deslocamento = (percentual * w) / 100;

    // Cria imagem de saída com mesmas dimensões
    QImage resultado(w, h, imagem.format());
    resultado.fill(Qt::transparent);

    // Copia os pixels com deslocamento
    for (int y = 0; y < h; ++y) {
        const QRgb *linhaOrig = reinterpret_cast<const QRgb *>(imagem.scanLine(y));
        QRgb *linhaDest = reinterpret_cast<QRgb *>(resultado.scanLine(y));

        for (int x = 0; x < w; ++x) {
            int xDestino = x + deslocamento;

            if (xDestino >= 0 && xDestino < w) {
                linhaDest[xDestino] = linhaOrig[x];
            }
            // Pixels fora do intervalo [0, w) são descartados
        }
    }
    return resultado;
}