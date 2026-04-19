#include "aritmetica.h"
#include <QtGlobal> // para qBound

QImage Aritmetica::somar(const QImage &img1, const QImage &img2)
{
    QImage a = img1.convertToFormat(QImage::Format_RGB32);
    QImage b = img2.convertToFormat(QImage::Format_RGB32);

    // Redimensiona se necessário
    if (a.size() != b.size()) {
        b = b.scaled(a.size());
    }

    QImage resultado(a.size(), QImage::Format_RGB32);

    for (int y = 0; y < a.height(); ++y) {
        const QRgb *linhaA = reinterpret_cast<const QRgb *>(a.scanLine(y));
        const QRgb *linhaB = reinterpret_cast<const QRgb *>(b.scanLine(y));
        QRgb *linhaR = reinterpret_cast<QRgb *>(resultado.scanLine(y));

        for (int x = 0; x < a.width(); ++x) {
            int r = qBound(0, qRed(linhaA[x]) + qRed(linhaB[x]), 255);
            int g = qBound(0, qGreen(linhaA[x]) + qGreen(linhaB[x]), 255);
            int bVal = qBound(0, qBlue(linhaA[x]) + qBlue(linhaB[x]), 255);

            linhaR[x] = qRgb(r, g, bVal);
        }
    }

    return resultado;
}

QImage Aritmetica::subtrair(const QImage &img1, const QImage &img2)
{
    QImage a = img1.convertToFormat(QImage::Format_RGB32);
    QImage b = img2.convertToFormat(QImage::Format_RGB32);

    if (a.size() != b.size()) {
        b = b.scaled(a.size());
    }

    QImage resultado(a.size(), QImage::Format_RGB32);

    for (int y = 0; y < a.height(); ++y) {
        const QRgb *linhaA = reinterpret_cast<const QRgb *>(a.scanLine(y));
        const QRgb *linhaB = reinterpret_cast<const QRgb *>(b.scanLine(y));
        QRgb *linhaR = reinterpret_cast<QRgb *>(resultado.scanLine(y));

        for (int x = 0; x < a.width(); ++x) {
            int r = qBound(0, qRed(linhaA[x]) - qRed(linhaB[x]), 255);
            int g = qBound(0, qGreen(linhaA[x]) - qGreen(linhaB[x]), 255);
            int bVal = qBound(0, qBlue(linhaA[x]) - qBlue(linhaB[x]), 255);

            linhaR[x] = qRgb(r, g, bVal);
        }
    }

    return resultado;
}

QImage Aritmetica::multiplicar(const QImage &img, int valor)
{
    QImage a = img.convertToFormat(QImage::Format_RGB32);
    QImage resultado(a.size(), QImage::Format_RGB32);

    for (int y = 0; y < a.height(); ++y) {
        const QRgb *linhaA = reinterpret_cast<const QRgb *>(a.scanLine(y));
        QRgb *linhaR = reinterpret_cast<QRgb *>(resultado.scanLine(y));

        for (int x = 0; x < a.width(); ++x) {
            int r = qBound(0, qRed(linhaA[x]) * valor, 255);
            int g = qBound(0, qGreen(linhaA[x]) * valor, 255);
            int bVal = qBound(0, qBlue(linhaA[x]) * valor, 255);

            linhaR[x] = qRgb(r, g, bVal);
        }
    }

    return resultado;
}

QImage Aritmetica::dividir(const QImage &img, int valor)
{
    QImage a = img.convertToFormat(QImage::Format_RGB32);
    QImage resultado(a.size(), QImage::Format_RGB32);

    for (int y = 0; y < a.height(); ++y) {
        const QRgb *linhaA = reinterpret_cast<const QRgb *>(a.scanLine(y));
        QRgb *linhaR = reinterpret_cast<QRgb *>(resultado.scanLine(y));

        for (int x = 0; x < a.width(); ++x) {
            int r = qBound(0, qRed(linhaA[x]) / valor, 255);
            int g = qBound(0, qGreen(linhaA[x]) / valor, 255);
            int bVal = qBound(0, qBlue(linhaA[x]) / valor, 255);

            linhaR[x] = qRgb(r, g, bVal);
        }
    }

    return resultado;
}
