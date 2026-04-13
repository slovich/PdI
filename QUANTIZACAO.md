A Classe Quantização

Dependência
A classe Quantização é dependente do framework Qt.
Ela utiliza objetos como QImage, QPixmap, QLabel, QTreeView e QListView para manipulação de imagens e interação com a interface gráfica. Portanto, não pode ser utilizada em um projeto C++ puro sem Qt, a menos que seja reescrita para trabalhar com bibliotecas alternativas de processamento de imagem (como OpenCV ou stb_image).

Objetivo
A classe Quantização foi criada para aplicar redução de níveis de intensidade em imagens digitais.
Esse processo consiste em limitar o número de tons possíveis em cada canal de cor (R, G, B), resultando em uma imagem com menos variações de cor, útil para compressão, análise ou efeitos visuais.

Funcionamento
- Seleção da imagem principal
- A interface permite escolher uma imagem através de um QTreeView e QListView, que filtram apenas arquivos de imagem (JPG, PNG, BMP).
- A imagem selecionada é exibida em um QLabel.
- Entrada do valor de quantização
- O usuário informa no campo lineEdit_valor o número de níveis desejado (por exemplo, 2, 4, 8, 16).
- Esse valor define em quantos intervalos cada canal de cor será dividido.
- Processamento da imagem
- A classe converte a imagem para QImage::Format_RGB32.
- Para cada pixel, os valores de R, G e B são ajustados para o nível mais próximo dentro do intervalo definido.
- Exemplo: se o valor informado for 4, cada canal terá apenas 4 níveis possíveis (0, 85, 170, 255).
- Resultado
- A imagem quantizada é exibida em outro QLabel, redimensionada para até 500×500 px mantendo a proporção.
- O usuário pode comparar a imagem original e a quantizada lado a lado.
- Mesmo que o programa não contemple uma forma de zoom nas imagens após concluída a operação, existe a opção de salvar o resultado obtido. Isso permite comparar posteriormente tanto a qualidade visual da imagem quanto o tamanho do arquivo gerado em relação ao original.

Estrutura
- Entrada: QImage carregada a partir de um arquivo selecionado.
- Parâmetro: inteiro informado pelo usuário (número de níveis).
- Saída: nova QImage com os pixels ajustados conforme a quantização.
- Exibição: resultado convertido para QPixmap e mostrado em um QLabel.
- Exportação: possibilidade de salvar a imagem quantizada para análise comparativa.

Observações
- O valor informado deve ser maior que 1 e menor ou igual a 255.
- Valores muito baixos (como 2 ou 4) geram imagens com aparência de posterização.
- Valores altos (como 128 ou 255) mantêm a imagem próxima da original.
- O algoritmo é implementado de forma eficiente usando acesso direto às linhas da imagem (scanLine()).
- A funcionalidade de salvar o resultado é essencial para avaliar não apenas o efeito visual da quantização, mas também o impacto na compressão e no tamanho do arquivo.


Algoritmo Base da Classe Quantização

Lógica de funcionamento
O algoritmo de quantização implementado nesta classe segue a ideia de redução de níveis de intensidade em cada canal de cor (R, G, B) de uma imagem digital. O processo é realizado pixel a pixel, ajustando os valores originais para o nível mais próximo dentro de um conjunto reduzido de intervalos.

Etapas principais
- Conversão de formato
- A imagem recebida é convertida para QImage::Format_RGB32.
- Isso garante acesso uniforme aos canais de cor e facilita a manipulação direta dos pixels.
- Definição do intervalo de quantização
- O valor informado pelo usuário (entre 2 e 255) define o número de níveis possíveis.
- O tamanho de cada intervalo é calculado como:
\mathrm{intervalo}=\frac{256}{\mathrm{valor}}- Exemplo: se o valor for 4, cada canal terá intervalos de 64 unidades (0–63, 64–127, 128–191, 192–255).
- Iteração sobre os pixels
- O algoritmo percorre cada linha da imagem usando scanLine(), que fornece acesso direto à memória dos pixels.
- Para cada pixel, os valores de R, G e B são extraídos.
- Ajuste para o nível mais próximo
- Cada canal é dividido pelo tamanho do intervalo para determinar em qual faixa o valor se encontra.
- O valor é então multiplicado novamente pelo tamanho do intervalo para obter o nível quantizado.
- Fórmula:
\mathrm{novoValor}=\left( \frac{\mathrm{valorOriginal}}{\mathrm{intervalo}}\right) \times \mathrm{intervalo}- Isso garante que o valor seja arredondado para o início da faixa correspondente.
- Construção da imagem resultante
- Os novos valores de R, G e B são combinados em um pixel (qRgb(r, g, b)).
- Esse pixel é escrito na posição correspondente da imagem de saída.
- Ao final da iteração, a imagem resultante contém apenas os níveis permitidos.

Características do algoritmo
- Eficiência: o uso de scanLine() evita chamadas repetidas a funções de alto nível como pixel() e setPixel(), tornando o processamento mais rápido.
- Generalidade: funciona para qualquer valor de quantização entre 2 e 255.
- Controle de qualidade: valores baixos geram imagens com forte posterização, enquanto valores altos mantêm maior fidelidade à original.
- Exportação: mesmo sem zoom na interface, o resultado pode ser salvo em arquivo, permitindo comparação posterior da qualidade visual e do tamanho do arquivo.

Exemplo prático
- Imagem original: pixel com valores (R=150, G=200, B=75).
- Valor de quantização: 4 → intervalo = 64.
- Cálculo:
- R: 150/64=2 → 2\times 64=128
- G: 200/64=3 → 3\times 64=192
- B: 75/64=1 → 1\times 64=64
- Pixel resultante: (128, 192, 64).


Métodos da Classe Quantização

Método 1: Quantização Uniforme
Lógica
- A imagem é convertida para QImage::Format_RGB32.
- Define-se o número de níveis por canal (niveisPorCanal) e a profundidade de bits (bitsPorCanal).
- Cada canal (R, G, B) é dividido em intervalos de tamanho:
\mathrm{step}=\frac{256}{\mathrm{niveisPorCanal}}- O valor original do pixel é ajustado para o início do intervalo correspondente.
- Em seguida, aplica-se uma máscara de bits:
\mathrm{mask}=0xFF\ll (8-\mathrm{bitsPorCanal})
- que força o valor a respeitar a profundidade de bits definida.
Impacto dos parâmetros- niveisPorCanal:
- Valores baixos (ex.: 2 ou 4) reduzem drasticamente a paleta de cores, gerando imagens com aparência de posterização.
- Valores altos (ex.: 128 ou 256) mantêm maior fidelidade à original.
- bitsPorCanal:
- Controla a precisão de cada canal.
- Menos bits → menos cores possíveis → maior compressão, mas perda de detalhes.
- Mais bits → mais fidelidade, mas arquivos maiores.
- 
Método 2: Corte MedianoLógica- Coleta todos os pixels da imagem em um vetor.
- Inicializa uma única “caixa” (ColorBox) contendo todos os pixels.
- Enquanto não atingir o número desejado de cores (numeroCores) ou o critério de parada (criterioParada):
- Calcula a variância de cada canal (R, G, B) na caixa.
- Escolhe o canal com maior variância (maior dispersão de valores).
- Ordena os pixels da caixa por esse canal.
- Divide a caixa ao meio, criando duas novas caixas.
- Ao final, cada caixa representa uma região do espaço de cores.
- Calcula-se a cor média de cada caixa, formando a paleta final.
- Cada pixel da imagem é substituído pela cor média da caixa mais próxima (menor distância euclidiana no espaço RGB).
Impacto dos parâmetros- numeroCores:
- Define quantas cores finais a paleta terá.
- Valores baixos → paleta reduzida, imagem mais simplificada.
- Valores altos → paleta mais rica, maior fidelidade.
- criterioParada:
- Limita o número de divisões possíveis.
- Se for menor que numeroCores, a paleta final terá menos cores que o solicitado.
- Impacta diretamente o tempo de execução: valores altos aumentam a complexidade.
