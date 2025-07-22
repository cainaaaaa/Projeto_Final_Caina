#ifndef COBRA_H
#define COBRA_H

#include <QObject>
#include <QList>
#include <QGraphicsScene>
#include "segmentocobra.h"
#include "posicao.h"

// Definição das direções da cobra
enum Direcao {
    Cima,
    Baixo,
    Esquerda,
    Direita
};

class Cobra : public QObject
{
    Q_OBJECT //Macro do Qt. Essencial para que esta classe possa usar sinais e slots.

public:  //Membros públicos: acessíveis de fora da classe.

    Cobra(QGraphicsScene *scene,      //Construtor da classe MainWindow. Ponteiro para a QGraphicsScene onde ele será desenhado.
          int tamanhoBloco,           //Tamanho em pixels do bloco.
          QObject *parent = nullptr); //Parent QObject (para gerenciamento de memória).

    void mover(); //Move a cobra na direção atual.
    void crescer(); //Adiciona um novo segmento ao corpo.
    void setDirecao(Direcao novaDirecao); //Define a direção da cobra.
    Posicao getPosicaoCabeca() const; //Retorna a posição da cabeça.
    bool colideComCorpo() const; //Verifica colisão com o próprio corpo.
    bool colideComParede(int larguraTabuleiro, int alturaTabuleiro) const; //Verifica colisão com as paredes.
    const QList<SegmentoCobra*>& getCorpo() const; //Retorna a lista de segmentos.
    void reset(); //Reinicia a cobra.

private:  //Membros privados: acessíveis apenas de dentro da própria classe.

    QList<SegmentoCobra*> m_corpo; //Segmentos do corpo da cobra.
    Direcao m_direcaoAtual; //Direção atual de movimento.
    Direcao m_proximaDirecao; //Próxima direção (para evitar inversão 180 graus).
    QGraphicsScene *m_scene; //Cena gráfica onde a cobra é desenhada.
    int m_tamanhoBloco; //Tamanho de cada bloco/segmento.
    bool m_deveCrescer; //Flag para indicar crescimento.
};

#endif // COBRA_H
