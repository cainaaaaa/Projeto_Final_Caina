# Análise orientada a objeto

## Descrição Geral do domínio do problema

O Jogo da Cobrinha é um jogo clássico, popularmente conhecido por sua simplicidade e jogabilidade viciante. O objetivo desse trabalho é desenvolver uma versão do jogo aplicando os conceitos básicos de Programação Orientada a Objetos ultilizando o Qt Crator como plataforma de desenvolvimento.

### Apresentação do Jogo e Funcionalidades

No Jogo da Cobrinha, o jogador controla uma cobra que se move continuamente por um tabuleiro. O principal objetivo é guiar a cobra para comer alimentos que aparecem aleatoriamente no tabuleiro. Ao comer um alimento, duas coisas acontecem:

* A cobra aumenta de tamanho, adicionando um novo segmento ao seu corpo.
* A pontuação do jogador é incrementada.

O desafio e a complexidade do jogo aumentam à medida que a cobra cresce, pois o espaço de manobra diminui. O jogo termina se a cobra colidir com as bordas do tabuleiro ou com seu próprio corpo.

### Funcionalidades Essenciais:

* Controle da Cobra: O jogador deve ser capaz de mudar a direção da cobra (cima, baixo, esquerda, direita) usando as teclas de direção do teclado;
* Movimentação Contínua: A cobra deve se mover de forma autônoma e contínua em sua direção atual;
* Geração de Alimento: Um alimento deve aparecer aleatoriamente no tabuleiro, em uma posição que não esteja ocupada pelo corpo da cobra;
* Detecção de Colisão: O jogo precisa identificar quando a cabeça da cobra colide com um alimento, com as paredes do jogo ou com o próprio corpo;
* Aumento de Pontuação: A pontuação deve ser atualizada e exibida na tela a cada alimento consumido;
* Crescimento da Cobra: O corpo da cobra deve aumentar em comprimento após comer um alimento;
* Fim de Jogo: A partida deve encerrar quando uma colisão ocorrer, exibindo a pontuação final;
* Pausar/Retomar Jogo: O jogador deve ter a opção de pausar e retomar a partida a qualquer momento;
* Reiniciar Jogo: Após o fim de jogo, o jogador deve poder iniciar uma nova partida;
* Interface Gráfica Intuitiva: O jogo deve ter uma interface clara e fácil de entender.

### Requisitos Não Funcionais:

* Sons: Efeitos sonoros para comer alimento e fim de jogo.
* Múltiplos Níveis/Dificuldades: Ajuste da velocidade da cobra ou do tamanho do tabuleiro.
* Placar de Recordes: Armazenamento das maiores pontuações.
* Personalização: Opções para mudar as cores da cobra ou do tabuleiro.
  
## Diagrama de Casos de Uso

<img src="imagens/cobra_caso_uso.png"
     width="50%"
     style="padding: 10px">
     

### Casos de Uso Principais:

#### Ator
Jogador: O usuário que interage com o jogo.

#### Iniciar Jogo: O jogador inicia uma nova partida do jogo
* O jogador acessa o jogo;
* O jogador seleciona a opção "Iniciar Jogo";
* O sistema inicializa o tabuleiro, a cobra e a comida em posições iniciais;
* O jogo começa a rodar.

#### Mover Cobra: O jogador controla a direção da cobra
* O jogo está em andamento;
* O jogador pressiona uma tecla direcional (Cima, Baixo, Esquerda, Direita);
* O sistema atualiza a direção da cobra;
* A cobra se move na nova direção.

#### Pausar Jogo: O jogador pode pausar a partida em andamento
* O jogo está em andamento;
* O jogador pressiona a tecla "Pausa";
* O sistema pausa o jogo e exibe uma mensagem de "Jogo Pausado";
* Fluxo Alternativo: O jogo já está pausado, o jogador pressiona "Pausa" novamente e o jogo é retomado.

#### Encerrar Jogo: O jogador finaliza a partida
* O jogo está em andamento ou pausado;
* O jogador seleciona a opção "Encerrar";
* O sistema encerra o jogo e exibe uma mensagem "Fim de Jogo" e mostra a pontuação final;
* Fluxo Alternativo: O jogo também é encerrado automaticamente quando a cobra colide com uma parede ou com o próprio corpo.


 
## Diagrama de Domínio do problema

<img src="imagens/cobra_diagrama_dominio.png"
     width="50%"
     style="padding: 10px">


### Entidades Principais:
* Jogador: A pessoa que interage com o jogo;
* Jogo: Representa a instância principal do jogo;
* Tabuleiro: O ambiente onde o jogo acontece;
* Cobra: A entidade controlada pelo jogador;
* Alimento: O item que a cobra come para crescer;
* Segmento de Cobra: Cada parte individual do corpo da cobra;
* Posição: Represneta a posição da cobra (em movimento) e da comida (estatico).

### Relacionamentos e Associações:
* Um Jogador participa de um Jogo;
* Um Jogo contém um Tabuleiro;
* Um Tabuleiro contém uma Cobra;
* Um Tabuleiro contém um Alimento;
* Uma Cobra é composta por múltiplos Segmentos de Cobra;
* Uma Cobra tem uma Posição;
* Um Alimento tem uma Posição.


<div align="center">

[Retroceder](README.md) | [Avançar](implementacao.md)

</div>
