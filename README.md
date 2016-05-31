# Busca_Largura_RestaUM
Utilização da técnica de busca em largura com método heurístico para encontrar solução para o problema do jogo RestaUm. Será desenvolvido em Java, Python e C de forma serial e paralela. Até o momento a solução apenas foi implementada de forma correta em Java (serial) e Python (serial). O código em C já existe, mas ainda não converge. O paralelismo será efetuado por meio da biblioteca OpenMP. 

#######
DETALHES IMPORTANTES DA IMPLEMENTAÇÃO

Talvez não seja a melhor solução, mas...

O jogo:
     O tabuleiro é representado por uma matriz quadrada de ordem 7 (7X7). 
                   0 --> espaço morto
                   1 --> peça
                   2 --> local vazio
     estado inicial:                       estado alvo:
          0 0 1 1 1 0 0                 0 0 2 2 2 0 0
          0 0 1 1 1 0 0                 0 0 2 2 2 0 0
          1 1 1 1 1 1 1                 2 2 2 2 2 2 2
          1 1 1 2 1 1 1                 2 2 2 1 2 2 2 
          1 1 1 1 1 1 1                 2 2 2 2 2 2 2
          0 0 1 1 1 0 0                 0 0 2 2 2 0 0
          0 0 1 1 1 0 0                 0 0 2 2 2 0 0
  Movimentos possíveis conforme algumas regras: 
    saltar:
          esquerda
          direita
          para cima
          para baixo
JAVA:
O código é composto por três classes, a saber, Nodo, RestaUm e BuscaLargura. O nodo é o objeto composto por três atributos: estado, nodo pai e valor. O estado é a matriz resultado de um determinado movimento. Cada movimento instancia um novo nodo, que segue uma lógica de lista encadeada com inserções no início. O nodo criado aponta para o nodo pai. Valor é o atributo que corresponde à distância do nodo filho com relação ao estado alvo. Isto quer dizer que o valor é um inteiro construído com base na comparação entre a matriz atual e a matriz alvo. Todo elemento distinto entre as matrizes incrementa um contador. 

A classe RestaUM é composta pelos estados e pelas seguintes funções ou métodos: valida, insereNoFinal, pulaDireita, pulaEsquerda, pulaUp, pulaDown, imprimir, caminho, removePrimeiro e valor. O valida serve para verificar se o nodo já está presente no ArrayList. InsereNoFinal é a função que percorre o nodo explorado em busca de espaços vazios. A cada espaço vazio, chama os métodos de saltos. Os saltos verificam se o movimento é válido, criam um novo nodo, realizam o movimento, atribuem o valor de distância e verificam se o estado gerado já foi explorado. Se não foi explorado, ou melhor, se não é um nodo já inserido no vetor dinâmico (I), então insere no vetor (E) para posterior análise. O método imprimir apenas formata a saída dos dados para um formato de matriz, o caminho percorerrá a lista encadeada dos nodos que compoe a solução do problema e o valor comparará duas matrizes (alvo x Mn) afim de atribuir um valor inteiro ao nodo.Mn. A última classe, a principal, realiza os movimentos necessários para a busca em si. 

A busca em largura analisa todos os nodos de uma camada antes de prosseguir para a próxima. Dentro de uma estrutura de repetição, remove-se o primeiro nodo da lista dinâmica "E" (ArrayList<Nodo>), o retorno do método removePrimeiro é o nodo removido, o qual é em seguida comparado com o estado alvo. Se não for igual ao estado final, então insere-o no vetor dinâmico "I" e depois chama o método insereNoFinal com os dois vetores, mais o nodoAtual como parâmetros. Por último, realiza uma ordenação do vetor "E" com base no atributo valor de cada nodo. Quanto menor o valor, mais próximo do alvo. 

Nodo -> Lista encadeada simples
Vetores que armazenam os nodos -> ArrayList<Nodo>
Ordenação -> Collections.sort()

PYTHON: 

O código em python é bem semelhante embora tenha um desempenho bem inferior, mesmo com Cython. Acho que já era de se esperar. Ainda não tive tempo de pesquisar para verificar se o list do python faz a mesma coisa que o ArrayList do Java. Possivelmente não, mas gostaria de saber o quanto ambos são diferentes entre si. Também não sei sobre a eficiência dos métodos de ordenação. 

Nodo -> Lista encadeada
Vetores -> List
Ordenação -> sort(key=attrgetter("valor"))

C:

struct nodo (apelido Nodo) -> lista encadeada com os tipos: int valor, int[][] estado e struct nodo* proximo
Vetores são estáticos -> não gostei de fazer isso, mas não obtive sucesso com uma fila ou só outra lista encadeada. Abandonei a fila quando resolvi ordenar a cada inserção, mas o programa não convergiu e não identifiquei a falha. Depois de várias tentativas, passei a usar vetores estáticos, mas ainda assim estou sem sucesso e não consigo encontrar a falha ou as falhas. O método de ordenação atual é o bubble, sei, deixa o desempenho horrível, mas está fazendo o que deve fazer, não é a minha preocupação no momento ordenar de forma eficiente. A ordenação ainda ocorre a cada inserção de um nodo no vetor estático de nodos (struct). A remoção também não é saudável, pois me obriga a realizar os movimentos para esquerda de todos os nodos inseridos (Terrível), mas, repito, cumpri o papel - aparentemente, o que importa nessa parte do projeto. 





