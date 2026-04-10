#include "quantizacao.h"
#include <algorithm>


Quantizacao::Quantizacao(const QImage &imagemOriginal, int parametro1, int parametro2)
    : imagem(imagemOriginal), p1(parametro1), p2(parametro2)
{
    //Construtor já inicia atribuindo os parâmetros às varáveis da classe
}

//Define a estrutura de dados que comportara o vetor da paleta de cores
struct ColorBox {
    QVector<QRgb> pixels;
};

//Calcula a varância das cores presentes na imagem
static int varianciaCanal(const QVector<QRgb> &pixels, char canal) {
    QVector<int> valores;
    for (QRgb c : pixels) {
        if (canal == 'r') valores.append(qRed(c));
        else if (canal == 'g') valores.append(qGreen(c));
        else valores.append(qBlue(c));
    }
    double media = std::accumulate(valores.begin(), valores.end(), 0.0) / valores.size();
    double soma = 0;
    for (int v : valores) soma += (v - media) * (v - media);
    return static_cast<int>(soma / valores.size());
}

//Calcula o valor médio de cada cor presente na imagem
static QRgb mediaCor(const QVector<QRgb> &pixels) {
    long r=0,g=0,b=0;
    for (QRgb c : pixels) {
        r += qRed(c);
        g += qGreen(c);
        b += qBlue(c);
    }
    int n = pixels.size();
    return qRgb(r/n, g/n, b/n);
}


QImage Quantizacao::aplicarQuantizacaoUniforme(int niveisPorCanal, int bitsPorCanal)
{
    QImage resultado = imagem.convertToFormat(QImage::Format_RGB32);

    int step = 256 / niveisPorCanal; // tamanho do intervalo
    int mask = 0xFF << (8 - bitsPorCanal); // máscara de bits

    for (int y = 0; y < resultado.height(); ++y) {
        QRgb *linha = reinterpret_cast<QRgb*>(resultado.scanLine(y));
        for (int x = 0; x < resultado.width(); ++x) {
            int r = qRed(linha[x]);
            int g = qGreen(linha[x]);
            int b = qBlue(linha[x]);

            // aplica quantização uniforme
            r = (r / step) * step;
            g = (g / step) * step;
            b = (b / step) * step;

            // aplica profundidade de bits
            r = r & mask;
            g = g & mask;
            b = b & mask;

            linha[x] = qRgb(r, g, b);
        }
    }
    return resultado;
}


QImage Quantizacao::aplicarCorteMediano(int numeroCores, int criterioParada)
{
    QImage resultado = imagem.convertToFormat(QImage::Format_RGB32);

    // Coleta todos os pixels
    QVector<QRgb> todosPixels;
    for (int y = 0; y < resultado.height(); ++y) {
        const QRgb *linha = reinterpret_cast<const QRgb*>(resultado.scanLine(y));
        for (int x = 0; x < resultado.width(); ++x) {
            todosPixels.append(linha[x]);
        }
    }

    // Inicializa com uma única caixa
    QVector<ColorBox> caixas;
    caixas.append({todosPixels});

    // Divide até atingir número de cores ou critério de parada
    while (caixas.size() < numeroCores && caixas.size() < criterioParada) {
        // encontra caixa com maior variância
        int idxMaior = 0;
        int maiorVar = 0;
        char canalEscolhido = 'r';
        for (int i = 0; i < caixas.size(); ++i) {
            int varR = varianciaCanal(caixas[i].pixels, 'r');
            int varG = varianciaCanal(caixas[i].pixels, 'g');
            int varB = varianciaCanal(caixas[i].pixels, 'b');
            int maxVar = std::max({varR, varG, varB});
            if (maxVar > maiorVar) {
                maiorVar = maxVar;
                idxMaior = i;
                if (maxVar == varR) canalEscolhido = 'r';
                else if (maxVar == varG) canalEscolhido = 'g';
                else canalEscolhido = 'b';
            }
        }

        // ordena pixels da caixa escolhida pelo canal
        auto &pixels = caixas[idxMaior].pixels;
        std::sort(pixels.begin(), pixels.end(), [canalEscolhido](QRgb a, QRgb b){
            if (canalEscolhido == 'r') return qRed(a) < qRed(b);
            if (canalEscolhido == 'g') return qGreen(a) < qGreen(b);
            return qBlue(a) < qBlue(b);
        });

        // divide ao meio
        int mid = pixels.size()/2;
        QVector<QRgb> metade1(pixels.begin(), pixels.begin()+mid);
        QVector<QRgb> metade2(pixels.begin()+mid, pixels.end());

        caixas.remove(idxMaior);
        caixas.append({metade1});
        caixas.append({metade2});
    }

    // cria paleta
    QVector<QRgb> paleta;
    for (const auto &caixa : caixas) {
        paleta.append(mediaCor(caixa.pixels));
    }

    // aplica paleta: substitui cada pixel pela cor média da caixa mais próxima
    for (int y = 0; y < resultado.height(); ++y) {
        QRgb *linha = reinterpret_cast<QRgb*>(resultado.scanLine(y));
        for (int x = 0; x < resultado.width(); ++x) {
            QRgb original = linha[x];
            int melhorDist = INT_MAX;
            QRgb melhorCor = paleta[0];
            for (QRgb cor : paleta) {
                int dr = qRed(original) - qRed(cor);
                int dg = qGreen(original) - qGreen(cor);
                int db = qBlue(original) - qBlue(cor);
                int dist = dr*dr + dg*dg + db*db;
                if (dist < melhorDist) {
                    melhorDist = dist;
                    melhorCor = cor;
                }
            }
            linha[x] = melhorCor;
        }
    }

    return resultado;

    /*QImage resultado = imagem.convertToFormat(QImage::Format_RGB32);

    // Coleta todas as cores
    QVector<QRgb> cores;
    for (int y = 0; y < resultado.height(); ++y) {
        const QRgb *linha = reinterpret_cast<const QRgb*>(resultado.scanLine(y));
        for (int x = 0; x < resultado.width(); ++x) {
            cores.append(linha[x]);
        }
    }

    // Aqui entraria a implementação completa do corte mediano:
    // - dividir cubo RGB pelo eixo de maior variância
    // - repetir até atingir numeroCores ou criterioParada
    // - calcular cor média de cada região
    // Para simplificação, vamos apenas reduzir para uma paleta fixa:
    QVector<QRgb> paleta;
    for (int i = 0; i < numeroCores; ++i) {
        int valor = (i * 255) / (numeroCores - 1);
        paleta.append(qRgb(valor, valor, valor));
    }

    // aplica paleta simplificada
    for (int y = 0; y < resultado.height(); ++y) {
        QRgb *linha = reinterpret_cast<QRgb*>(resultado.scanLine(y));
        for (int x = 0; x < resultado.width(); ++x) {
            int r = qRed(linha[x]);
            int g = qGreen(linha[x]);
            int b = qBlue(linha[x]);
            int media = (r + g + b) / 3;

            // aproxima para cor mais próxima da paleta
            int idx = (media * (numeroCores - 1)) / 255;
            linha[x] = paleta[idx];
        }
    }

    return resultado;*/
}