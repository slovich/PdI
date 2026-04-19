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