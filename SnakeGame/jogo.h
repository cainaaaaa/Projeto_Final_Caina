#ifndef JOGO_H
#define JOGO_H

#include <QObject>      //Inclui a classe QObject.
#include <QTimer>       //Inclui QTimer, que será usado para controlar o loop principal do jogo (velocidade de atualização).
#include "cobra.h"      //Inclui a definição da classe Cobra, pois Jogo gerencia um objeto Cobra.
#include "alimento.h"   //Inclui a definição da classe Alimento, pois Jogo gerencia um objeto Alimento.
#include "tabuleiro.h"  //Inclui a definição da classe Tabuleiro, pois Jogo precisa interagir com o tabuleiro visual.

enum EstadoJogo {  //Definição dos posiveis estados do jogo usando uma variavel enumerada.
    Rodando,       //O jogo está em andamento - 0.
    Pausado,       //O jogo está pausado - 1.
    FimDeJogo      //O jogo terminou - 2.
};

class Jogo : public QObject //Declara a classe Jogo, herda QObject.
{
    Q_OBJECT   //Macro do Qt. Essencial para que esta classe possa usar sinais e slots.

public: //Membros públicos: acessíveis de fora da classe.

    Jogo(Tabuleiro *tabuleiro,       //Construtor da classe Jogo.
         int larguraLogica,          //Largura do tabuleiro.
         int alturaLogica,           //Altura do tabuleiro.
         int tamanhoBloco,           //Tamanho em pixels de cada bloco.
         QObject *parent = nullptr); //Parent QObject (para gerenciamento de memória).

    //Métodos para controlar o fluxo do jogo.
    void iniciarJogo();  //Inicia uma nova partida do jogo.
    void pausarJogo();   //Pausa a execução do jogo.
    void retomarJogo();  //Retoma a execução de um jogo pausado.
    void fimDeJogo();    //Sinaliza o fim da partida (geralmente por colisão).

    //Métodos para obter informações sobre o estado do jogo.
    int getPontuacao() const;         //Retorna a pontuação atual do jogador.
    EstadoJogo getEstadoJogo() const; //Retorna o estado atual do jogo.

public slots: //Slots públicos: métodos que podem ser conectados a sinais.
    void atualizarJogo(); //Atualiza o loop principal do jogo, chamado pelo QtTimer.
    void processarEntrada(Direcao direcao); //Recebe a entrada do teclado.

signals: //Sinais: usados para comunicação entre objetos.
    void pontuacaoAlterada(int novaPontuacao); //Sinal para quando a pontuação aumenta, passa como argumento a nova pontuação.
    void jogoEncerrado(int pontuacaoFinal); //Sinal para quando o jogo termina, passa como argumento a pontuação final.
    void estadoJogoAlterado(EstadoJogo estado); //Sinal para quando o estado do jogo muda.

private: //Membros privados: acessíveis apenas de dentro da própria classe.
    Tabuleiro *m_tabuleiro;  //Referência ao objeto Tabuleiro visual.
    int m_larguraLogica;     //Largura do tabuleiro em unidades de blocos.
    int m_alturaLogica;      //Altura do tabuleiro em unidades de blocos.
    int m_tamanhoBloco;      //Tamanho em pixels de cada bloco do jogo.
    int m_pontuacao;         //Atributo que armazena a pontuação atual do jogo.
    EstadoJogo m_estadoJogo; //Atributo que armazena o estado atual do jogo.

    Cobra *m_cobra;          //Ponteiro para o objeto Cobra do jogo.
    Alimento *m_alimento;    //Ponteiro para o objeto Alimento do jogo.
    QGraphicsScene *m_scene; //Referência à QGraphicsScene onde os elementos são desenhados.

    QTimer *m_timerJogo;     //Timer que dispara o método atualizarJogo() periodicamente.
    int m_velocidadeJogo;    //Intervalo de tempo (em ms) entre cada atualização do jogo.

    void checarColisoes();    //Metodo que verifica todas as possíveis colisões da cobra.
    void gerarNovoAlimento(); //Metodo que gera e posiciona um novo alimento aleatoriamente no tabuleiro.
};

#endif // JOGO_H
