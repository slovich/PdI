# Transformação Geométrica

Esta classe implementa métodos para a manipulação espacial e geométrica de imagens digitais, alterando as coordenadas dos pixels ou a escala da imagem usando as ferramentas de renderização e desenho da biblioteca Qt.

---

## Método 1: Rotação

### Lógica de Funcionamento
- O método recebe um ângulo em graus e calcula as novas dimensões necessárias para que a imagem rotacionada caiba inteiramente no destino sem sofrer cortes periféricos.
- Aplica uma transformação de rotação usando trigonometria com base no centro geométrico da imagem.
- Utiliza a classe `QPainter` com anti-aliasing ativo para suavizar o mapeamento reverso de pixels e evitar o efeito de serrilhado nas bordas inclinadas.

### Formulação Matemática
As novas coordenadas $(x', y')$ de um pixel rotacionado por um ângulo $\theta$ em relação a uma origem central são baseadas na matriz de rotação padrão:
$$x' = x \cdot \cos(\theta) - y \cdot \sin(\theta)$$
$$y' = x \cdot \sin(\theta) + y \cdot \cos(\theta)$$

As novas dimensões da imagem ($W'$ e $H'$) para comportar a rotação total sem perdas são calculadas por:
$$W' = |W \cdot \cos(\theta)| + |H \cdot \sin(\theta)|$$
$$H' = |W \cdot \sin(\theta)| + |H \cdot \cos(\theta)|$$

### Exemplo Prático
- **Imagem original**: Largura $W = 100$, Altura $H = 100$.
- **Parâmetro**: Ângulo de $90^\circ$ ($\cos(90^\circ) = 0$, $\sin(90^\circ) = 1$).
- **Cálculo de dimensões**: 
  $$W' = |100 \cdot 0| + |100 \cdot 1| = 100$$
  $$H' = |100 \cdot 1| + |100 \cdot 0| = 100$$
- **Resultado**: A imagem é rotacionada perfeitamente em sentido horário, onde o topo original passa a ser a lateral direita.

### Análise Detalhada do Código (.cpp)
1. **Normalização e Conversão Angular**: O código usa `fmod(graus, 360.0)` para garantir que o ângulo esteja no domínio de uma volta e o corrige caso seja negativo. Logo após, `qDegreesToRadians(graus)` converte o valor para radianos, exigência das funções trigonométricas de `QtMath`.
2. **Cálculo de Delimitadores (Bounding Box)**: `int newW = qAbs(w * cosA) + qAbs(h * sinA);` projeta os quatro vértices originais mapeando a largura e altura máximas que a nova imagem precisará ter.
3. **Instanciação do Canvas**: Cria-se um `QImage resultado` usando `QImage::Format_ARGB32` para suportar transparência alfa e o preenche com `Qt::transparent`. Isso impede que o fundo da rotação exiba lixo de memória ou blocos pretos rígidos.
4. **Matriz de Transformação (`QPainter`)**: 
   - `painter.translate(newW / 2.0, newH / 2.0);` move a origem do sistema de coordenadas $(0,0)$ do canto superior esquerdo para o centro da nova imagem.
   - `painter.rotate(graus);` rotaciona o sistema de coordenadas inteiro com base no ângulo fornecido.
   - `painter.drawImage(-w / 2.0, -h / 2.0, imagem);` projeta a imagem original centralizada retroativamente. O Qt cuida do mapeamento reverso dos pixels de forma nativa e performática.

### Impacto dos Parâmetros
- **Ângulos oblíquos (não múltiplos de 90°)**: Geram grandes áreas vazias triangulares ao redor da imagem original, preenchidas por transparência.
- **Render Hints (`Antialiasing`)**: Ativa a interpolação nas bordas externas do desenho, atenuando degraus visuais (serrilhado) à custa de um leve overhead de processamento.

---

## Método 2: Espelhamento (Horizontal e Vertical)

### Lógica de Funcionamento
- **Espelhamento Horizontal**: Inverte a imagem da esquerda para a direita, refletindo os dados ao redor do eixo vertical central.
- **Espelhamento Vertical**: Inverte a imagem de cima para baixo, refletindo os dados ao redor do eixo horizontal central.
- A transferência de dados ocorre através da varredura por linha onde os pixels simétricos trocam de posição.

### Formulação Matemática
Mapeamento de coordenadas indexadas a zero:
- **Horizontal**: $x' = W - 1 - x$ e $y' = y$
- **Vertical**: $x' = x$ e $y' = H - 1 - y$

### Exemplo Prático
- **Imagem original**: Dimensão $W = 200$. Pixel sob análise localizado em $x = 10$.
- **Espelhamento Horizontal**: 
  $$x' = 200 - 1 - 10 = 189$$
- **Resultado**: O pixel da coluna 10 é copiado diretamente para a coluna 189 da imagem de destino.

### Análise Detalhada do Código (.cpp)
1. **Estrutura de Loops Aninhados**: Ambos os métodos utilizam loops for externos iterando sobre a altura (`y`) e internos iterando sobre a largura (`x`).
2. **Varredura e Escrita Direta**:
   - No `espelharHorizontal`, o loop interno faz: `resultado.setPixel(x, y, imagem.pixel(w - 1 - x, y));`. Isso lê a imagem original de trás para frente no eixo X enquanto escreve de forma sequencial no destino.
   - No `espelharVertical`, o mapeamento inverte a linha de origem: `resultado.setPixel(x, y, imagem.pixel(x, h - 1 - y));`.
3. **Desempenho**: Este método opera em complexidade espacial e temporal $O(W \times H)$, alocando uma imagem idêntica em formato e copiando bit a bit cada pixel sem transformações matemáticas complexas.

### Impacto dos Parâmetros
- A operação preserva rigorosamente as dimensões, canais e proporções originais da imagem, alterando exclusivamente a orientação espacial do conteúdo.

---

## Método 3: Translação (Horizontal e Vertical)

### Lógica de Funcionamento
- Desloca espacialmente todos os pixels da imagem em uma direção linear com base em um valor percentual informado pelo usuário (-100% a +100%).
- O espaço vazio deixado pela translação é intencionalmente preenchido com pixels transparentes para preservar o tamanho original da imagem e evitar artefatos de "fantasmas" ou repetição de bordas.

### Formulação Matemática
O deslocamento absoluto em pixels ($\Delta$) é calculado como uma fração da dimensão correspondente:
$$\Delta_x = W \cdot \left(\frac{\text{percentual}}{100}\right) \quad \text{ou} \quad \Delta_y = H \cdot \left(\frac{\text{percentual}}{100}\right)$$

Novas posições geradas: $x' = x + \Delta_x$ e $y' = y + \Delta_y$. Pixels cuja coordenada resultante fique fora do intervalo válido $[0, W-1]$ ou $[0, H-1]$ são descartados.

### Exemplo Prático
- **Imagem original**: $W = 400$. Percentual de translação horizontal informado = $+25\%$.
- **Cálculo**: $\Delta_x = 400 \cdot 0.25 = +100$ pixels.
- **Resultado**: Um pixel originalmente em $x = 50$ vai para $x' = 150$. As colunas resultantes de $0$ a $99$ serão preenchidas com transparência.

### Análise Detalhada do Código (.cpp)
1. **Cálculo do Deslocamento**: O código executa `int deslocamento = qRound(w * (static_cast<double>(percentual) / 100.0));` para converter o valor percentual em pixels inteiros com arredondamento seguro.
2. **Inicialização Limpa**: A imagem de `resultado` é preenchida com `resultado.fill(Qt::transparent);`, limpando os buffers.
3. **Loop de Mapeamento com Validação**:
   - Durante a iteração por todos os pixels $(x, y)$, calcula-se a coordenada de origem: `int srcX = x - deslocamento;` (no caso horizontal).
   - Uma condicional condensa a regra de decisão: `if (srcX >= 0 && srcX < w)`. Se a coordenada calculada pertencer à imagem original, o pixel é transportado via `resultado.setPixel(x, y, imagem.pixel(srcX, srcY));`. Caso contrário, o loop avança deixando o pixel com a transparência definida na inicialização.

### Impacto dos Parâmetros
- **Valores Extremos**: Valores percentuais próximos a 100% ou -100% empurram quase todo o conteúdo para fora da matriz visível, gerando imagens majoritariamente vazias.

---

## Método 4: Alongamento e Compressão (Escalonamento)

### Lógica de Funcionamento
- Redimensiona de forma independente a largura ou a altura da imagem aplicando um fator multiplicativo de escala.
- Faz uso da classe `QPainter` combinada com flags de suavização gráfica para realizar a amostragem espacial e reconstrução através de interpolação bilinear.
- Uma função auxiliar pós-processamento de suavização (filtro de média de tamanho fixo $3 \times 3$) é aplicada ao final do fluxo para atenuar imperfeições de subamostragem.

### Formulação Matemática
As novas dimensões resultantes são derivadas da multiplicação direta:
$$W' = \text{qRound}(W \cdot \text{fator}) \quad \text{e} \quad H' = \text{qRound}(H \cdot \text{fator})$$

### Exemplo Prático
- **Imagem original**: Altura $H = 150$, Largura estável $W = 200$. Fator de alongamento vertical = $2.0$.
- **Cálculo**: $H' = \text{qRound}(150 \cdot 2.0) = 300$.
- **Resultado**: A imagem final terá dimensões $200 \times 300$, esticando verticalmente o conteúdo.

### Análise Detalhada do Código (.cpp)
1. **Validação de Entrada**: O método inicia testando `if (fator <= 0.0) return imagem;` prevenindo divisões por zero ou inversões espaciais negativas não tratadas pelo algoritmo.
2. **Redimensionamento por Canvas Aberto**: Um `QPainter` é atrelado a um novo canvas ajustado (`novaLargura` ou `novaAltura`). 
3. **Interpolação Nativa**: A instrução `painter.setRenderHint(QPainter::SmoothPixmapTransform);` força o framework Qt a abandonar o algoritmo invasivo do vizinho mais próximo (*Nearest Neighbor*) em prol de um mapeamento bilinear suavizado durante a execução de `painter.drawImage(resultado.rect(), imagem);`.
4. **Filtro Auxiliar de Suavização**: O método retorna o resultado envelopado por `aplicarFiltroSuavizacao(resultado)`.
   - **Dentro do Filtro Auxiliar**: Dois loops excluem as bordas externas (`for (int y = 1; y < h - 1; ++y)`). Para cada pixel interno, ele varre uma vizinhança de 9 pixels através de loops de offset `i` e `j` de $-1$ a $+1$. Soma os canais (`somaR += qRed(pixel);`, etc.) e divide por 9. Reconstrói o pixel através de `qRgb(somaR / 9, somaG / 9, somaB / 9)`. Isso reduz o efeito de aliasing (pixelado) gerado pela transformação.

### Impacto dos Parâmetros
- **Fatores $> 1.0$ (Alongamento)**: Amplia a imagem. Embora a interpolação atenue os blocos de pixels, o resultado pode perder nitidez (aspecto borrado).
- **Fatores $< 1.0$ (Compressão)**: Encolhe a imagem, provocando perda irreversível de altas frequências espaciais (detalhes finos).
