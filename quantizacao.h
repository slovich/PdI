#ifndef QUANTIZACAO_H
#define QUANTIZACAO_H

#include <QImage>
#include <QPixmap>

class Quantizacao
{
public:
    // Construtor recebe imagem e parâmetros
    Quantizacao(const QImage &imagemOriginal, int parametro1, int parametro2);

    // Métodos de quantização
    QImage aplicarQuantizacaoUniforme(int niveisPorCanal, int bitsPorCanal);
    QImage aplicarCorteMediano(int numeroCores, int criterioParada);

private:
    QImage imagem;
    int p1;
    int p2;
};

#endif // QUANTIZACAO_H
