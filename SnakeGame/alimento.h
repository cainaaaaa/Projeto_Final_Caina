#ifndef ALIMENTO_H
#define ALIMENTO_H

#include <QGraphicsEllipseItem> //Inclui a classe base QGraphicsEllipseItem.
#include <QGraphicsScene>       //Inclui QGraphicsScene. A classe Alimento precisa interagir com a cena.
#include <QObject>              //Inclui QObject.
#include "posicao.h"            //Inclui a definição da Posicao, pois o alimento tem uma posição.
#include "cobra.h"              //Inclui a definição da classe Cobra. Para que alimento não seja gerado em cima da cobra.


class Alimento : public QGraphicsEllipseItem //Declara a classe Alimento, herda QGraphicsEllipseItem.
{
public: //Membros públicos: acessíveis de fora da classe.

    //Construtor da classe Alimento.
    Alimento(int tamanhoBloco,      //Tamanho em pixels do bloco.
        QGraphicsScene *scene,      //Ponteiro para a QGraphicsScene onde ele será desenhado.
        QObject *parent = nullptr); //Parent QObject (para gerenciamento de memória).

    //Método para gerar uma nova posição aleatória para o alimento no tabuleiro.
    void gerarNovaPosicao(int larguraTabuleiro,  //Passa a largura do tabuleiro.
                          int alturaTabuleiro,   //Passa a altura do tabuleiro.
                          const QList<SegmentoCobra*>& corpoCobra); //Passa a posição do corpo da cobra por referencia.

    //Método para obter a posição atual do alimento no tabuleiro.
    Posicao getPosicao() const;

private: //Membros privados: acessíveis apenas de dentro da própria classe.
    Posicao m_posicao;       //Atributo que armazena as coordenadas (x, y) do alimento.
    int m_tamanhoBloco;      //Atributo que armazena o tamanho em pixels de um bloco, usado para definir o tamanho visual do alimento.
    QGraphicsScene *m_scene; //Ponteiro para a cena gráfica onde este alimento está ou será adicionado.
};

#endif // ALIMENTO_H // Fim do "include guard".
