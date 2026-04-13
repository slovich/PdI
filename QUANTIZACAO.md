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
