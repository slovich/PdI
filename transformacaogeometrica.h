#ifndef TRANSFORMACAOGEOMETRICA_H
#define TRANSFORMACAOGEOMETRICA_H

#include <QImage>

class TransformacaoGeometrica
{
public:
    // Construtor padrão
    TransformacaoGeometrica();

    // Função de rotação que recebe uma imagem e um ângulo em graus (0 a 360) e retorna uma nova imagem rotacionada em relação ao centro
    QImage rotacionar(const QImage &imagem, double graus);

    // Espelhamento vertical
    QImage espelharVertical(const QImage &imagem);

    // Espelhamento horizontal
    QImage espelharHorizontal(const QImage &imagem);
};

#endif // TRANSFORMACAOGEOMETRICA_H
