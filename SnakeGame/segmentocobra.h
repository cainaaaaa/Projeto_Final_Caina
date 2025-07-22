#ifndef SEGMENTOCOBRA_H
#define SEGMENTOCOBRA_H

#include <QGraphicsRectItem> //Inclui QGraphicsRectItem. SegmentoCobra vai herdar dela para se tornar um item visual.
#include "posicao.h"         //Inclui a definição de Posicao.

class SegmentoCobra : public QGraphicsRectItem  //Declara a classe SegmentoCobra, herda QGraphicsRectItem.
{
public: //Membros públicos: acessíveis por outras classes.
    SegmentoCobra(int x,                            //Construtor da classe SegmentoCobra. Posição logica x.
                  int y,                            //Posição logica y.
                  int tamanhoBloco,                 //Tamanho do bloco visual.
                  QGraphicsItem *parent = nullptr); //Parent QGraphicsItem (para gerenciamento de memória).
    Posicao getPosicao() const;     //Retorna a posição lógica do segmento.
    void setPosicao(int x, int y);  //Método para atualizar a nova posição logica (x,y) e visual do QGraphicsItem.

private: //Membros privados: acessíveis apenas dentro da classe.
    Posicao m_posicao; //Atributo que armazena a posição lógica em unidades de blocos do segmento.
    int m_tamanhoBloco; //Atributo que armazena o tamanho do bloco em pixels.
};

#endif
