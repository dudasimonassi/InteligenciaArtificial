Para testes é disponibilzado um acervo com instâncias que podem ser rodadas da seguinte forma: 

  ./main.exe input/NomeTeste.txt

Caso necessário é possível gerar novas instâncias no mesmo formato dos testes disponíveis:

- Primeiro valor : tamanho n do seu puzzle
- Primeiros n valores: estado inicial do tabuleiro (valores indo de 0 a (n^2)-1)
- Últimos n valores: estado final do tabuleiro (valores indo de 0 a (n^2)-1)

Exemplo para tabuleiro 3x3:

  3 // Tamanho n 

  1 2 3
  4 5 6  //Estado inicial
  7 8 0

  0 8 9
  1 2 5 //Estado final 
  6 7 3 

