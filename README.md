
# N-Puzzle Solver

Projeto criado como parte da avaliação da disciplina de Inteligência Artificial (DCC014) da Universidade Federal de Juiz de Fora no período 2023.1.

O projeto teve como objetivo explorar algoritmos de busca informados e não informados na resolução do N-Puzzle.

Para mais informações sobre implementação e estatísticas do projeto acesse o **Relatório Técnico** disponibilizado no repositório. 


## Implementação

* Busca Backtracking
* Busca em Largura
* Busca em Profundidade 
* Busca Ordenada
* Busca Gulosa
* Busca A*
* Busca IDA*

Para as buscas informadas levamos em conta as heurísticas:

* Custo estimado: calculado pela distância de Manhattan
* Custo mínimo: calculado pela quantidade de peças fora do lugar

## Estatísticas:

O algoritmo é responsável por realizar as seguintes estatísticas:

- Solução: movimentos que devem ser realizados para que o estado inicial atinja o estado final;
- Profundidade da solução;
- Custo da solução;
- Quantidade de nós expandidos;
- Quantidade de nós visitados;
- Valor médio de ramificação da árvore de busca;
- Tempo de processamento.

## Rodando os testes

Para testes é disponibilzado um acervo com dez instâncias que podem ser rodadas da seguinte forma: 

```bash
  ./main.exe input/NomeTeste.txt
```

Caso necessário é possível gerar novas instâncias no mesmo formato dos testes disponíveis:

- Primeiro valor : tamanho n do seu puzzle
- Primeiros n valores: estado inicial do tabuleiro (valores indo de 0 a (n^2)-1)
- Últimos n valores: estado final do tabuleiro (valores indo de 0 a (n^2)-1)

Exemplo para tabuleiro 3x3:

```bash
  3 // Tamanho n 

  1 2 3
  4 5 6  //Estado inicial
  7 8 0

  0 8 9
  1 2 5 //Estado final 
  6 7 3 
```
## Autores

- Maria Eduarda Simonassi : [@dudasimonassi](https://github.com/dudasimonassi)

