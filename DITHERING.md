# Algoritmos de Dithering e Meio-Tom (Halftoning)

A classe `Dithering` é um componente avançado do sistema de processamento digital de imagens, projetado especificamente para a redução do espaço de cores (quantização) com a simulação de profundidades de tons estendidas. Através da aplicação de técnicas de **difusão de erro** e **dithering ordenado/estocástico**, a classe permite que monitores, impressoras ou formatos de arquivos com paletas restritas (como imagens binárias de 1 bit ou com poucos níveis de cinza) exibam transições tonais suaves, mitigando artefatos visuais indesejados como o bandeamento de cores (*color banding*).

---

## 1. Pipeline de Pré-processamento Otimizado

Antes da aplicação dos operadores de meio-tom, a classe oferece um método centralizado de condicionamento de imagem. Este pipeline prepara e otimiza a distribuição estatística de luminância para melhorar a fidelidade do resultado final.

### Detalhamento das Etapas e Código (`.cpp`)
O método `Dithering::preprocessamento` opera convertendo inicialmente a imagem de entrada para o formato de luminância nativo de 8 bits (`QImage::Format_Grayscale8`) e aplicando três tratamentos opcionais controlados por flags booleanas:

1. **Suavização Espacial (Filtro de Média $3 \times 3$):**
   Atenua ruídos de alta frequência magnânimos que poderiam corromper os buffers de difusão de erro. A leitura dos pixels vizinhos é otimizada por meio de ponteiros rápidos de linha obtidos via `temp.scanLine(y + ky)`:
   ```cpp
   for (int ky = -1; ky <= 1; ++ky) {
       const uchar* linha = temp.scanLine(y + ky);
       for (int kx = -1; kx <= 1; ++kx) {
           soma += linha[x + kx];
       }
   }
   int media = soma / 9; ```cpp

2. **Ajuste Dinâmico de Contraste:**
Amplia ou atenua linearmente a amplitude tonal do pixel original multiplicando-o por um fator de ganho escalar. Para blindar a memória contra fenômenos de transbordamento (overflow ou underflow), o código encapsula o resultado na função de saturação do Qt:
 
```cpp
 int novoValor = qBound(0, static_cast<int>(linha[x] * fator), 255);
```

3. **Normalização Global do Histograma (Estiramento Linear):**
Realiza um mapeamento de contraste global (contrast stretching). No primeiro passe por toda a matriz de pixels, localiza os valores extremos de intensidade de cinza ($\text{minVal}$ e $\text{maxVal}$). No segundo passe, aplica a fórmula clássica de remapeamento dinâmico para cobrir o intervalo dinâmico total $[0, 255]$:

$$\begin{array}{cc} \\ I_{\text{novo}}(x, y) = \frac{I(x, y) - \text{minVal}}{\text{maxVal} - \text{minVal}} \times 255 \\ \\ \end{array}$$

## 2. Métodos de Dithering por Difusão de Erro

Estes algoritmos operam por meio de uma varredura sequencial (raster) linha a linha. Para cada coordenada $(x, y)$, o valor acumulado no buffer (soma do tom original com os erros herdados) é quantizado para o nível de cinza mais próximo disponível. A diferença matemática residual (o erro) é calculada e fracionada entre os pixels vizinhos à frente e abaixo que ainda não foram processados, utilizando uma matriz de coeficientes específicos.

### Formulação Matemática Geral

Dado um pixel na coordenada espacial $(x, y)$ com valor corrigido $I_{\text{corrigido}}(x, y)$:
1. **Quantização:**
   
   $I_{\text{quantizado}}(x, y) = \text{qRound}\left(\frac{I_{\text{corrigido}}(x, y) \cdot (N - 1)}{255.0}\right) \cdot \left(\frac{255}{N - 1}\right)$, onde $N$ é o número de níveis de cinza de destino.
3. **Cálculo do Erro Residual:**
   
   $E = I_{\text{corrigido}}(x, y) - I_{\text{quantizado}}(x, y)$
   
5. **Dispersão do Erro:**
   
   Para cada vizinho em um deslocamento espacial $(kx, ky)$, incrementa-se o erro acumulado multiplicando $E$ pelo peso matricial $w_{kx, ky}$ normalizado pela soma total dos pesos:

$$cpp I_{\text{buffer}}(x + kx, y + ky) \leftarrow I_{\text{buffer}}(x + kx, y + ky) + E \cdot \left( \frac{w_{kx, ky}}{\sum w} \right)$$



  Para evitar que truncamentos de inteiros destruam a continuidade das transições suaves e causem acúmulo sistemático de erro, todas as variantes de difusão da classe alocam uma matriz de trabalho bidimensional de ponto flutuante de dupla precisão:

```cpp
  std::vector<std::vector<double>> buffer(h, std::vector<double>(w));
```

### 2.1 Floyd-Steinberg:

É o algoritmo clássico de difusão. Distribui o erro residual para quatro pixels vizinhos imediatos, gerando estruturas de ruído de alta frequência espacial (blue noise) balanceadas.

**Matriz de Coeficientes e Pesos ($\sum w = 16$):**

$$\begin{array}{-----------}& \bullet & \rightarrow & \frac{7}{16} \\frac{3}{16} & \frac{5}{16} & \frac{1}{16} &\end{array}$$

**Implementação$$ de Núcleo:**

```cpp
if (x + 1 < w) buffer[y][x + 1] += erro * 7.0 / 16.0;
if (y + 1 < h && x > 0) buffer[y + 1][x - 1] += erro * 3.0 / 16.0;
if (y + 1 < h) buffer[y + 1][x] += erro * 5.0 / 16.0;
if (y + 1 < h && x + 1 < w) buffer[y + 1][x + 1] += erro * 1.0 / 16.0;
```
### 2.2 Burkes:

Uma evolução do Floyd-Steinberg com maior alcance horizontal na linha atual e subsequente. Distribui o erro para sete vizinhos, o que diminui a ocorrência de padrões lineares artificiais verticais.

**Matriz de Coeficientes e Pesos ($\sum w = 32$):**

$$\begin{array}{-----------}& & \bullet & \rightarrow & \frac{8}{32} & \frac{4}{32} \\frac{2}{32} & \frac{4}{32} & \frac{8}{32} & \frac{4}{32} & \frac{2}{32} &\end{array}$$

### 2.3 Jarvis, Judice e Ninke:

Algoritmo de altíssima densidade espacial que espalha o erro residual por uma vizinhança estendida de 12 vizinhos, atingindo até duas linhas abaixo do pixel ativo. Produz imagens ricas em detalhes texturizados.

**Matriz de Coeficientes e Pesos ($\sum w = 48$):**

$$\begin{array}{-----------}& & \bullet & \rightarrow & \frac{7}{48} & \frac{5}{48} \\frac{3}{48} & \frac{5}{48} & \frac{7}{48} & \frac{5}{48} & \frac{3}{48} & \\frac{1}{48} & \frac{3}{48} & \frac{5}{48} & \frac{3}{48} & \frac{1}{48} &\end{array}$$

### 2.4 Stucki:

Semelhante ao Jarvis em termos de abrangência espacial (12 vizinhos espalhados por duas linhas abaixo), porém ajusta os numeradores e adota uma base de normalização igual a 42. Produz transições de meio-tom com nitidez acentuada nas bordas estruturais (edge enhancement).

**Matriz de Coeficientes e Pesos ($\sum w = 42$):**

$$\begin{array}{-----------}& & \bullet & \rightarrow & \frac{8}{42} & \frac{4}{42} \\frac{2}{42} & \frac{4}{42} & \frac{8}{42} & \frac{4}{42} & \frac{2}{42} & \\frac{1}{42} & \frac{2}{42} & \frac{4}{42} & \frac{2}{42} & \frac{1}{42} &\end{array}$$  

### 2.5 Atkinson:

Desenvolvido na Apple por Bill Atkinson, possui a característica singular de propagar apenas $75\%$ (uma fração parcial fixa de $6/8$) do erro gerado para 6 vizinhos circundantes, descartando o restante. Esse vazamento intencional de erro resulta em um ganho de contraste pronunciado, preservando brancos puros e pretos densos.

**Matriz de Coeficientes e Pesos ($\sum w = 8$, propaga apenas $6/8$):**

$$\begin{array}{-----------}& \bullet & \rightarrow & \frac{1}{8} & \frac{1}{8} \\frac{1}{8} & \frac{1}{8} & \frac{1}{8} & & \& \frac{1}{8} & & &\end{array}$$

### 2.6 Família Sierra (Sierra3, Sierra2, Sierra-2-Slices)

A classe fornece suporte completo para as três variantes propostas por Frankie Sierra, adaptando o pipeline para diferentes compromissos entre fidelidade e custo computacional:
    
**Sierra  3:**  Versão completa de três linhas e 12 vizinhos (∑w=32).

**Sierra2:** Versão simplificada de duas linhas e 7 vizinhos (∑w=16).

**Sierra 2-Slices:** Variante ultra-rápida de duas linhas e apenas 3 vizinhos diretos, ideal para aceleração em hardware devido ao divisor estável de base 4 (∑w=4):

$$\begin{array}{-----------} & \bullet & \rightarrow & \frac{2}{4} \ \frac{1}{4} & \frac{1}{4} & & \end{array}$$

## 3. Métodos de Dithering Ordenado e Espacial

Diferente da difusão de erro, estes algoritmos tomam decisões locais isoladas para cada pixel com base em matrizes matemáticas de limiarização periódica ou funções estocásticas, eliminando a dependência de dados entre coordenadas vizinhas.

### 3.1 Dithering Ordenado por Matriz de Bayer:

O algoritmo projeta ciclicamente as coordenadas espaciais globais da imagem $(x, y)$ sobre uma matriz estática quadrada indexada de tamanho $N \times N$ por meio de aritmética modular:

$$i = x \pmod N \quad \text{e} \quad j = y \pmod N$$

O valor de intensidade do pixel escalado é testado diretamente contra o limiar normalizado contido na célula da matriz:

```cpp
double limiar = (matriz[j][i] + 0.5) / (tamanhoMatriz * tamanhoMatriz) * 255.0;

```

A classe suporta nativamente as ordens estruturais $2 \times 2$, $4 \times 4$ e $8 \times 8$, gerando padrões geométricos cruzados estáveis muito utilizados na estética visual computacional retrô.

### 3.2 Clustered Dot (Meio-Tom Agrupado / Trama de Impressão):

Simula o processo físico de impressão analógica e serigrafia. Agrupa os pixels quantizados em macroestruturas geométricas cujo diâmetro se expande de forma circular, quadrada ou elíptica de acordo com o nível de cinza local da imagem original.O comportamento da trama é governado pelo método auxiliar

```cpp
Dithering::gerarMatrizCluster(clusterSize, formaPonto)
```
que modela geometricamente o crescimento do ponto a partir do seu centro de gravidade cartesiano através do parâmetro formaPonto:

### 3.2 Clustered Dot (Meio-Tom Agrupado / Trama de Impressão)

Simula o processo físico de impressão analógica e serigrafia. Agrupa os pixels quantizados em macroestruturas geométricas cujo diâmetro se expande de forma circular, quadrada ou elíptica de acordo com o nível de cinza local da imagem original.

O comportamento da trama é governado pelo método auxiliar

```cpp
Dithering::gerarMatrizCluster(clusterSize, formaPonto)
```
que modela geometricamente o crescimento do ponto a partir do seu centro de gravidade cartesiano através do parâmetro formaPonto:

| ID (formaPonto) | Tipo de Geometria | Equação Matemática de Preenchimento do Kernel (xc​,yc​=centro) |
| --- | --- | --- |
| 0 | Circular | $M(x,y) = (x - x_c)^2 + (y - y_c)^2$ |
| 1 | Quadrado | $M(x,y) = \max( |
| 2 | Elíptico | $M(x,y) = (x - x_c)^2 + \frac{(y - y_c)^2}{2}$ |
| 3 | Linha / Trama | $M(x,y) = (x + y) \pmod{\text{clusterSize}}$ |

Após o preenchimento geométrico básico, o kernel sofre uma normalização automática para garantir uma distribuição uniforme dos limiares no intervalo $[0, \text{maxVal})$:

```cpp
v = (v - minVal) * maxVal / std::max(1, maxFound - minVal);
```

### 3.3 Random Dithering (Dithering Aleatório)

Abordagem puramente estocástica. Introduz um ruído branco uniforme simétrico a cada pixel antes da limiarização rígida, quebrando linhas abruptas de contorno.

A implementação utiliza o motor de números pseudo-aleatórios Mersenne Twister do C++11 (```std::mt19937```) alimentado por sementes de hardware (```std::random_device```), garantindo a quebra de correlação espacial com alta performance computacional:

```cpp
std::uniform_int_distribution<int> dist(-intensidadeRuido, intensidadeRuido);
int valorComRuido = qBound(0, linha[x] + dist(gen), 255);
```
## 4. Análise e Comparação de Complexidade Algorítmica

A tabela abaixo correlaciona as características computacionais e o comportamento visual de cada algoritmo implementado na classe:

| Algoritmo | Abordagem Matemática | Complexidade Temporal | Complexidade Espacial Adicional |
| --- | --- | --- | --- |
| Floyd-Steinberg | Difusão de Erro (4 posições) | $O(W \times H)$ | $O(W \times H)$ |
| Burkes | Difusão de Erro (7 posições) | $O(W \times H)$ | $O(W \times H)$ |
| Jarvis / Stucki | Difusão de Erro (12 posições) | $O(W \times H)$ | $O(W \times H)$ |
| Atkinson | Difusão de Erro Parcial ($75\%$) | $M(x,y) = (x + y) \pmod{\text{clusterSize}}$ | $O(W \times H)$ |
| Família Sierra | Difusão Adaptativa (3 a 12 posições) | $O(W \times H)$ | $O(W \times H)$ |
| Bayer Matrix | Dithering Ordenado Periódico | $O(W \times H)$ | $O(1)$ |
| Clustered Dot / Stucki | Meio-Tom Espacial Estruturado | $O(W \times H)$ | $O(\text{clusterSize}^2)$ |
| Aleatório | Dithering Estocástico Neutro | $O(W \times H)$ | $O(1)$ |






