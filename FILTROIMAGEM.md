# Filtros de Imagem

Esta classe disponibiliza métodos avançados de filtragem espacial para imagens digitais em escala de cinza e RGB, abrangendo suavização linear, filtros estatísticos de ordem não-lineares e equalização adaptativa local.

---

## Método Auxiliar: Tratamento de Bordas (Padding)

### Lógica de Funcionamento
- Antes de processar máscaras espaciais convolucionais ou de vizinhança, as bordas da imagem precisam ser estendidas para que o centro do kernel possa atingir os pixels periféricos sem estourar os limites de memória da matriz.
- **Tipo 0 (Zeros/Constant Padding)**: Expande as bordas externas preenchendo as novas coordenadas criadas com a cor preta sólida.
- **Tipo 1 (Replicar/Clamp Padding)**: Estende os limites repetindo a cor do último pixel válido da extremidade original para as linhas e colunas adjacentes criadas.

### Formulação Matemática
Dado um Kernel de tamanho $K \times K$, o deslocamento da borda (offset) é calculado por:
$$\text{offset} = \lfloor K / 2 \rfloor$$
As novas dimensões da imagem expandida passam a ser:
$$W_{\text{nova}} = W + 2 \cdot \text{offset} \quad \text{e} \quad H_{\text{nova}} = H + 2 \cdot \text{offset}$$

### Análise Detalhada do Código (.cpp)
1. **Cálculo do Offset**: `int offset = kernelSize / 2;` define as faixas de expansão usando divisão inteira.
2. **Varredura da Matriz Expandida**: O método roda loops aninhados baseados em `novaLargura` e `novaAltura`. Para cada par $(x,y)$, calcula a coordenada retroativa na imagem real: `int srcX = x - offset; int srcY = y - offset;`.
3. **Estrutura de Decisão (`switch(borderType)`)**:
   - `case 0`: Se `srcX` ou `srcY` assumirem índices negativos ou superiores aos limites da imagem original (`srcX < 0 || srcY < 0 || srcX >= imagem.width() || srcY >= imagem.height()`), o código define `expandida.setPixel(x, y, qRgb(0,0,0));`.
   - `case 1`: Clampa os índices através de `std::max(0, std::min(srcX, imagem.width()-1))` garantindo que coordenadas fora do limite capturem o pixel da borda mais próxima antes de gravar com `expandida.setPixel(x, y, imagem.pixel(srcX, srcY));`.
4. **Região Central**: Se os índices forem internos e válidos, a cópia do pixel ocorre de forma direta $1:1$.

---

## Método 1: Filtro de Média

### Lógica de Funcionamento
- Filtro linear espacial passabaixo utilizado para atenuação de ruído de alta frequência.
- Move uma janela/máscara quadrada de tamanho $K \times K$ sobre a imagem expandida. Soma as intensidades de todos os pixels cobertos por essa janela e extrai a média aritmética, gravando o valor resultante no pixel central correspondente da imagem de destino.

### Formulação Matemática
Para uma vizinhança $V$ de tamanho $K \times K$ centralizada em $(x,y)$:
$$I_{\text{resultante}}(x,y) = \frac{1}{K^2} \sum_{(i,j) \in V} I(i,j)$$

### Exemplo Prático
- **Configuração**: Kernel $3 \times 3$ ($K^2 = 9$ pixels na vizinhança).
- **Matriz de intensidade local detectada (Canal Vermelho)**:

[10, 12, 11]

[ 9, 15, 13]

[11, 10, 12]

- **Cálculo**:
$$\text{Soma} = 10+12+11+9+15+13+11+10+12 = 103$$
$$\text{Média} = \lfloor 103 / 9 \rfloor = 11$$
- **Resultado**: O valor original do pixel central (15) é rebaixado para 11 na matriz final.

### Análise Detalhada do Código (.cpp)
1. **Preparação**: Invoca `tratarBordas(imagem, kernelSize, borderType)` para obter a imagem expandida e aloca o objeto `resultado` com o tamanho original da imagem.
2. **Loops de Varredura**: Os loops externos `y` e `x` navegam limitados ao tamanho da imagem original. O mapeamento lê a imagem expandida aplicando um deslocamento fixo (`x + offset`, `y + offset`).
3. **Loops Convolucionais Internos**:
 - Para cada pixel, os acumuladores `somaR`, `somaG` e `somaB` são zerados.
 - Os loops `for (int ky = -offset; ky <= offset; ++ky)` e `for (int kx = -offset; kx <= offset; ++kx)` varrem a janela $K \times K$ ao redor do pixel alvo.
 - Extrai-se a cor local: `QRgb pixelVizinho = expandida.pixel(x + offset + kx, y + offset + ky);`.
 - Se as flags booleanas (`aplicarR`, etc.) forem verdadeiras, adiciona-se o canal correspondente à respectiva soma; caso contrário, preserva-se o valor original do pixel central.
4. **Normalização**: O código calcula a média dividindo a soma por `int totalPixels = kernelSize * kernelSize;`. O pixel é remontado combinando `qBound(0, r, 255)` para garantir a integridade do intervalo de 8 bits.

### Impacto dos Parâmetros
- **Tamanho do Kernel ($kernelSize$)**: Quanto maior a dimensão da janela, maior o efeito de desfoque e a perda de nitidez das bordas estruturais da imagem.

---

## Método 2: Filtro de Mediana

### Lógica de Funcionamento
- Filtro não-linear estatístico de ordem amplamente utilizado para remoção de ruídos impulsivos (como o ruído "sal e pimenta").
- Em vez de realizar operações aritméticas de soma, ele coleta todas as intensidades contidas na vizinhança $K \times K$, ordena os valores em ordem crescente e seleciona o valor posicionado exatamente no centro do vetor (a mediana).

### Formulação Matemática
$$I_{\text{resultante}}(x,y) = \text{Mediana} \{ I(i,j) \mid (i,j) \in V \}$$

### Exemplo Prático
- **Configuração**: Kernel $3 \times 3$ (Vetor de 9 posições).
- **Vizinhança com ruído impulsivo (ponto branco isolado)**:

[12, 14, 13]

[11, 255, 12]

[13, 10, 14]

- **Vetor Unidimensional Gerado**: `[12, 14, 13, 11, 255, 12, 13, 10, 14]`
- **Vetor após Ordenação**: `[10, 11, 12, 12, 13, 13, 14, 14, 255]`
- **Mediana (Índice 4)**: $13$
- **Resultado**: O ruído extremo (255) é movido para o fim do vetor e descartado. O pixel assume o valor representativo 13.

### Análise Detalhada do Código (.cpp)
1. **Estrutura de Vetores Dinâmicos**: Dentro dos loops de imagem, são instanciados vetores `std::vector<int> valoresR, valoresG, valoresB;` reservados com a capacidade exata do kernel via `.reserve(kernelSize * kernelSize)`.
2. **Coleta de Dados da Vizinhança**: Os loops de vizinhança (`kx`, `ky`) extraem os valores individuais dos canais RGB através das funções `qRed`, `qGreen` e `qBlue` inserindo-os nos vetores com `.push_back()`.
3. **Ordenação Algorítmica**: O código utiliza a função de alta performance da biblioteca padrão do C++: `std::sort(valoresR.begin(), valoresR.end());`. Esta função opera em complexidade média $O(N \log N)$.
4. **Seleção do Elemento Central**: A mediana é extraída diretamente pelo índice central do vetor ordenado: `int medianaR = valoresR[valoresR.size() / 2];`, atualizando o pixel de saída através da função `resultado.setPixel(x, y, qRgb(...))`.

### Impacto dos Parâmetros
- Fornece excelente preservação de bordas em comparação com o filtro de média, mas possui maior custo computacional devido à necessidade recorrente de ordenação de vetores em cada pixel da imagem.

---

## Método 3: Filtros de Máximo e Mínimo

### Lógica de Funcionamento
- Filtros estatísticos extremos não-lineares equivalentes às operações morfológicas de dilatação e erosão em tons de cinza.
- O **Filtro de Máximo** analisa a vizinhança e substitui o pixel central pelo maior valor de intensidade encontrado.
- O **Filtro de Mínimo** analisa a vizinhança e substitui o pixel central pelo menor valor de intensidade encontrado.
- Suporta dois formatos de vizinhança selecionáveis: **Quadrado** (janela completa) ou **Cruz** (apenas os eixos ortogonais).

### Formulação Matemática
- **Máximo**: $I_{\text{resultante}}(x,y) = \max_{(i,j) \in V} \{ I(i,j) \}$
- **Mínimo**: $I_{\text{resultante}}(x,y) = \min_{(i,j) \in V} \{ I(i,j) \}$

### Análise Detalhada do Código (.cpp)
1. **Inicialização de Extremos**: 
 - Para o filtro de Máximo, as variáveis de controle começam no menor limite possível: `int maxR = 0, maxG = 0, maxB = 0;`.
 - Para o filtro de Mínimo, iniciam no maior valor de um byte: `int minR = 255, minG = 255, minB = 255;`.
2. **Filtragem por Formato Geométrico**: Durante a varredura da vizinhança, o código invoca uma função de validação lógica: `if (!dentroVizinhanca(kx, ky, offset, formaVizinhanca)) continue;`.
 - **Dentro da Função Auxiliar `dentroVizinhanca`**: Se o parâmetro `formaVizinhanca` for igual a `1` (formato em Cruz), a função testa `if (kx != 0 && ky != 0) return false;`. Isso faz com que os cantos diagonais do kernel sejam completamente ignorados no cálculo, processando apenas os pixels em formato de cruz $+$.
3. **Atualização Condicional**:
 - No Filtro de Máximo: `if (r > maxR) maxR = r;` atualiza constantemente o teto de intensidade encontrado na vizinhança ativa.
 - No Filtro de Mínimo: `if (r < minR) minR = r;` captura o menor vale de intensidade.

---

## Método 4: Filtro Gaussiano

### Lógica de Funcionamento
- Filtro linear de suavização passabaixo onde os pesos dos coeficientes da máscara são calculados a partir de uma distribuição gaussiana bidimensional normalizada.
- Diferente do filtro de média uniforme, o filtro gaussiano atribui pesos maiores aos pixels mais próximos do centro da máscara, emulando de forma mais natural os fenômenos físicos de desfoque óptico e preservando melhor as estruturas espaciais locais.

### Formulação Matemática
A equação que governa a distribuição gaussiana bivariada contínua é dada por:
$$G(x, y) = \frac{1}{2\pi\sigma^2} e^{-\frac{x^2 + y^2}{2\sigma^2}}$$
Onde $\sigma$ (Sigma) representa o desvio padrão da distribuição, ditando o espalhamento e o raio de influência da curva de desfoque.

### Análise Detalhada do Código (.cpp)
1. **Geração Dinâmica do Kernel**: O código aloca uma matriz bidimensional nativa para o kernel através de vetores C++: `std::vector<std::vector<double>> kernel(kernelSize, std::vector<double>(kernelSize));`.
2. **Cálculo dos Coeficientes e Normalização**:
 - Um loop duplo calcula o peso de cada célula com base em sua distância ao centro (`x` e `y` variando de `-offset` a `+offset`):
   ```cpp
   double expoente = -(x * x + y * y) / (2.0 * sigma * sigma);
   kernel[y + offset][x + offset] = qExp(expoente); // O termo constante 1/(2*pi*sigma^2) é omitido pois será simplificado na normalização
   somaKernel += kernel[y + offset][x + offset];
   ```
 - Logo após, um segundo loop divide cada termo por `somaKernel`. Essa etapa garante que a soma de todos os coeficientes seja exatamente igual a $1.0$, impedindo que a filtragem altere o brilho global da imagem original.
3. **Processamento Convolucional**: Durante a filtragem da imagem, acumuladores do tipo ponto flutuante (`double acumR = 0;`, etc.) multiplicam a intensidade do pixel da imagem expandida pelo peso correspondente armazenado no kernel: `acumR += qRed(pixelVizinho) * peso;`. Ao final, o valor é convertido de volta para inteiro e limitado por segurança com a função `qBound`.

---

## Método 5: CLAHE (Contrast Limited Adaptive Histogram Equalization)

### Lógica de Funcionamento
- Técnica avançada de aprimoramento adaptativo de contraste local que soluciona o problema da equalização global de histogramas (que tende a superamplificar ruídos e estourar o brilho em sub-regiões).
- Divide a imagem em uma grade de blocos retangulares homogêneos (*Tiles* ou sub-regiões).
- Para cada bloco, calcula-se o histograma local. Os pixels que excedem um limite de corte definido pelo usuário (`clipLimit`) são ceifados e o excesso acumulado é redistribuído uniformemente por todos os tons de cinza do histograma antes de gerar a Função de Distribuição Acumulada (CDF).
- Para remover artefatos visuais de descontinuidade nas fronteiras das grades (*blocking artifacts*), o método realiza uma interpolação bilinear na junção dos blocos.

### Formulação Matemática
Se a contagem de pixels de um nível de cinza específico $h(i)$ for superior ao limite de corte $C_L$:
$$\text{Excesso} = \sum_{i=0}^{255} \max(0, h(i) - C_L)$$
$$\text{Redistribuição} = \frac{\text{Excesso}}{256}$$
$$h_{\text{limitado}}(i) = \min(h(i), C_L) + \text{Redistribuição}$$

### Análise Detalhada do Código (.cpp)
1. **Divisão em Sub-regiões**: O código calcula o tamanho interno de cada bloco dividindo as dimensões totais pela quantidade de grades especificadas nas entradas: `int tileW = imagem.width() / tileGridWidth; int tileH = imagem.height() / tileGridHeight;`.
2. **Mapeamento de Histogramas Locais**: Uma matriz de vetores armazena a tabela de mapeamento para cada bloco: `std::vector<std::vector<std::vector<int>>> cdfGrids(...)`.
 - Dentro de cada bloco, um histograma de 256 posições é preenchido.
 - **Limitador de Contraste**: O código percorre o histograma coletando pixels acima do teto: `if (hist[i] > clipLimit) { excess += hist[i] - clipLimit; hist[i] = clipLimit; }`.
 - **Redistribuição Uniforme**: O excesso é rateado por igual: `int redist = excess / 256; for (int i = 0; i < 256; ++i) hist[i] += redist;`.
 - **Cálculo da CDF Local**: Gera-se a curva acumulada normalizando-a para a escala $[0, 255]$ com base no número total de pixels do bloco.
3. **Reconstrução com Interpolação Bilinear**: Esta é a seção mais complexa do código. Para cada pixel global da imagem localizado nas coordenadas $(x, y)$:
 - O algoritmo identifica os quatro blocos vizinhos mais próximos (Superior Esquerdo, Superior Direito, Inferior Esquerdo, Inferior Direito) e calcula os pesos de distância relativa `tx` e `ty`.
 - Consulta o valor de mapeamento da intensidade do cinza atual nas quatro tabelas CDF calculadas.
 - Executa a interpolação linear dupla:
   ```cpp
   double topo = (1.0 - tx) * vTL + tx * vTR;
   double baixo = (1.0 - tx) * vBL + tx * vBR;
   int valorFinal = qBound(0, qRound((1.0 - ty) * topo + ty * baixo), 255);
   ```
 - Isso elimina as marcas de grade e suaviza perfeitamente a transição de contraste entre as sub-regiões da imagem.

### Impacto dos Parâmetros
- **`clipLimit`**: Valores baixos restringem a equalização mantendo o aspecto original. Valores muito altos aproximam o método do comportamento agressivo do AHE convencional, o que pode evidenciar ruídos de fundo indesejados em áreas de textura constante.
