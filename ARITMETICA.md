A Classe Aritmética

Dependência  
A classe Aritmética depende do framework Qt e utiliza QImage para manipulação direta de pixels. Ela foi projetada para operações aritméticas entre imagens e sobre imagens (soma, subtração, multiplicação e divisão), mantendo coerência com o padrão das demais classes do projeto.

Objetivo  
A classe Aritmética foi criada para fornecer operações elementares de processamento de imagens que atuam pixel a pixel, permitindo combinar imagens ou ajustar intensidades de forma controlada e eficiente.

Funcionamento
- Entrada: uma ou duas QImage (dependendo do método).
- Processamento: conversão para QImage::Format_RGB32 quando necessário; iteração por linhas via scanLine() para acesso eficiente aos pixels; operações aritméticas aplicadas canal a canal (R, G, B).
- Saída: nova QImage com o resultado da operação, no mesmo formato e dimensões (ou redimensionada previamente quando necessário).
- Exibição: o resultado pode ser convertido para QPixmap e exibido em QLabel conforme padrão do projeto.
- Exportação: possibilidade de salvar a imagem resultante para análise posterior.

Métodos e comportamento

somar(const QImage &img1, const QImage &img2)
- Soma os valores R, G e B correspondentes de duas imagens.
- Se as imagens tiverem tamanhos diferentes, a segunda é redimensionada para o tamanho da primeira antes do processamento.
- Os valores resultantes são limitados ao intervalo [0,255] usando qBound.

subtrair(const QImage &img1, const QImage &img2)
- Subtrai os canais correspondentes da segunda imagem da primeira.
- Se as imagens tiverem tamanhos diferentes, a segunda é redimensionada para o tamanho da primeira.
- O resultado é limitado a [0,255] com qBound.

multiplicar(const QImage &img, int valor)
- Multiplica cada canal (R, G, B) de cada pixel por um inteiro 'valor'.
- O resultado é truncado para o intervalo [0,255] com qBound.
- Útil para aumentar brilho ou aplicar ganho por canal de forma simples.

dividir(const QImage &img, int valor)
- Divide cada canal (R, G, B) de cada pixel por um inteiro 'valor'.
- 'valor' deve ser diferente de zero; o método assume entrada válida (ou o chamador deve validar).
- O resultado é limitado a [0,255].

Estrutura interna e escolhas de implementação
- Conversão de formato: cada método converte a imagem para QImage::Format_RGB32 quando necessário, garantindo acesso uniforme aos canais.
- Acesso eficiente: o processamento é feito linha a linha usando scanLine() e reinterpretando o ponteiro para QRgb *, evitando chamadas repetidas a pixel() e setPixel() e melhorando desempenho.
- Controle de overflow/underflow: qBound(0, valor, 255) é usado para manter os canais dentro do intervalo válido.
- Redimensionamento: quando duas imagens participam da operação e têm tamanhos diferentes, a segunda imagem é escalada para o tamanho da primeira com scaled() antes do processamento, preservando a lógica de pixel a pixel.

Exemplo prático (conceitual)
Soma: duas imagens A e B de 300×200. Para cada pixel (x,y):
* r = qBound(0, qRed(A(x,y)) + qRed(B(x,y)), 255)
* g = qBound(0, qGreen(A(x,y)) + qGreen(B(x,y)), 255)
* b = qBound(0, qBlue(A(x,y)) + qBlue(B(x,y)), 255)

Métodos da Classe Aritmética — descrição detalhada
A classe Aritmética utiliza-se das facilidades do framework Qt para manipulação direta de QImage e não é implementada como uma classe C++ “pura” sem dependências. Ela dispõe de quatro métodos públicos principais:
- Adição de imagens — QImage Aritmetica::somar(const QImage &img1, const QImage &img2)
- Subtração de imagens — QImage Aritmetica::subtrair(const QImage &img1, const QImage &img2)
- Multiplicação por escalar — QImage Aritmetica::multiplicar(const QImage &img, int valor)
- Divisão por escalar — QImage Aritmetica::dividir(const QImage &img, int valor)

A seguir apresenta-se, em linguagem natural, o algoritmo e o comportamento de cada método, passo a passo, incluindo decisões de implementação, tratamento de bordas e considerações de desempenho.

QImage Aritmetica::somar(const QImage &img1, const QImage &img2)
Objetivo: combinar duas imagens somando os valores dos canais R, G e B pixel a pixel, produzindo uma nova imagem onde cada componente de cor é a soma correspondente das duas imagens.

Fluxo e algoritmo:
1) Normalização de formato: ambas as imagens de entrada são convertidas para um formato de acesso uniforme (por exemplo, QImage::Format_RGB32) para garantir que os canais R, G e B possam ser lidos e escritos de forma consistente.
2) Ajuste de dimensões: se as imagens tiverem tamanhos diferentes, a segunda imagem é redimensionada para o tamanho da primeira (estratégia adotada para manter correspondência pixel a pixel). O redimensionamento é feito antes do processamento para evitar lógica de recorte durante a iteração.
3) Iteração eficiente: o algoritmo percorre a imagem linha a linha, usando acesso direto à memória das linhas (por exemplo, via scanLine()), o que evita chamadas repetidas a funções de alto nível e melhora o desempenho.
4) Operação por pixel: para cada posição (x, y):
- extrai-se r1, g1, b1 da primeira imagem e r2, g2, b2 da segunda;
- calcula-se r = r1 + r2, g = g1 + g2, b = b1 + b2;
- aplica-se um clamping para manter cada componente no intervalo válido [0, 255] (por exemplo, usando qBound).
5) Construção da imagem de saída: os valores resultantes são escritos na imagem de saída na mesma posição (x, y).

QImage Aritmetica::subtrair(const QImage &img1, const QImage &img2)
Objetivo: subtrair os canais da segunda imagem dos canais correspondentes da primeira, pixel a pixel, produzindo uma imagem que realça diferenças ou reduz intensidades.

Fluxo e algoritmo:
1) Conversão de formato: ambas as imagens são convertidas para um formato uniforme (Format_RGB32) para leitura consistente.
2) Redimensionamento condicional: se as dimensões diferirem, a segunda imagem é escalada para o tamanho da primeira para permitir iteração direta.
3) Iteração por linhas: percorre-se cada linha com acesso direto à memória.
4) Operação por pixel: para cada (x, y):
- extrai r1, g1, b1 e r2, g2, b2;
- calcula r = r1 - r2, g = g1 - g2, b = b1 - b2;
- aplica-se qBound(0, valor, 255) para evitar valores negativos (underflow) e manter o intervalo válido.
5) Escrita do resultado: gravação dos canais ajustados na imagem de saída.

QImage Aritmetica::multiplicar(const QImage &img, int valor)
Objetivo: aplicar um ganho escalar a cada canal de cor da imagem, útil para ajustar brilho ou intensidade.

Fluxo e algoritmo:
1) Conversão de formato: a imagem de entrada é convertida para Format_RGB32 para acesso direto aos canais.
2) Iteração por linhas: percorre-se cada linha com ponteiros para os pixels.
3) Operação por pixel: para cada pixel (x, y):
- extrai r, g, b;
- calcula r' = r * valor, g' = g * valor, b' = b * valor;
- aplica-se qBound(0, r', 255) (e equivalente para G e B) para evitar overflow.
4) Escrita do resultado: gravação dos valores limitados na imagem de saída.

QImage Aritmetica::dividir(const QImage &img, int valor)
Objetivo: reduzir a intensidade de cada canal dividindo por um escalar inteiro, útil para atenuar brilho ou aplicar ganho fracionário aproximado.

Fluxo e algoritmo:
1) Validação do divisor: o método assume que valor é diferente de zero; o chamador deve validar ou o método pode tratar valor == 0 retornando a imagem original ou sinalizando erro.
2) Conversão de formato: a imagem é convertida para Format_RGB32.
3) Iteração por linhas: acesso eficiente via scanLine().
4) Operação por pixel: para cada (x, y):
- extrai r, g, b;
- calcula r' = r / valor, g' = g / valor, b' = b / valor;
- aplica-se qBound(0, r', 255) (embora divisão por inteiro já mantenha valores dentro do intervalo).
5) Escrita do resultado: gravação dos canais resultantes na imagem de saída.
