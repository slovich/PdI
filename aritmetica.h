#ifndef ARITMETICA_H
#define ARITMETICA_H

#include <QImage>

class Aritmetica {
public:
    static QImage somar(const QImage &img1, const QImage &img2);
    static QImage subtrair(const QImage &img1, const QImage &img2);
    static QImage multiplicar(const QImage &img, int valor);
    static QImage dividir(const QImage &img, int valor);
};

#endif // ARITMETICA_H