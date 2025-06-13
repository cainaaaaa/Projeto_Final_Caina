# Análise orientada a objeto

## Descrição Geral do domínio do problema

O Jogo da Cobrinha é um jogo clássico, popularmente conhecido por sua simplicidade e jogabilidade viciante. O objetivo desse trabalho é desenvolver uma versão do jogo aplicando os conceitos básicos de Programação Orientada a Objetos ultilizando o Qt Crator como plataforma de desenvolvimento.

### Apresentação do Jogo e Funcionalidades

No Jogo da Cobrinha, o jogador controla uma cobra que se move continuamente por um tabuleiro. O principal objetivo é guiar a cobra para comer alimentos que aparecem aleatoriamente no tabuleiro. Ao comer um alimento, duas coisas acontecem:

* A cobra aumenta de tamanho, adicionando um novo segmento ao seu corpo.
* A pontuação do jogador é incrementada.

O desafio e a complexidade do jogo aumentam à medida que a cobra cresce, pois o espaço de manobra diminui. O jogo termina se a cobra colidir com as bordas do tabuleiro ou com seu próprio corpo.

### Funcionalidades Essenciais:

* Controle da Cobra: O jogador deve ser capaz de mudar a direção da cobra (cima, baixo, esquerda, direita) usando teclas de direção.
* Movimentação Contínua: A cobra deve se mover de forma autônoma e contínua em sua direção atual.
* Geração de Alimento: Um alimento deve aparecer aleatoriamente no tabuleiro, em uma posição que não esteja ocupada pelo corpo da cobra.
* Detecção de Colisão: O jogo precisa identificar quando a cabeça da cobra colide com um alimento, com as paredes do jogo ou com o próprio corpo.
* Aumento de Pontuação: A pontuação deve ser atualizada e exibida na tela a cada alimento consumido.
* Crescimento da Cobra: O corpo da cobra deve aumentar em comprimento após comer um alimento.
* Fim de Jogo: A partida deve encerrar quando uma colisão ocorrer, exibindo a pontuação final.
* Pausar/Retomar Jogo: O jogador deve ter a opção de pausar e retomar a partida a qualquer momento.
* Reiniciar Jogo: Após o fim de jogo, o jogador deve poder iniciar uma nova partida.
  
## Diagrama de Casos de Uso

<img src="imagens/cobra_caso_uso.png"
     width="50%"
     style="padding: 10px">
     
Apresentar o diagram de casos de uso, identificando as funcionalidades do sistema assim como os atores envolvidos
 
## Diagrama de Domínio do problema

<img src="imagens/cobra_diagrama_dominio.png"
     width="50%"
     style="padding: 10px">

Elaborar um diagrama conceitual do domínio do problema.


<div align="center">

[Retroceder](README.md) | [Avançar](implementacao.md)

</div>
