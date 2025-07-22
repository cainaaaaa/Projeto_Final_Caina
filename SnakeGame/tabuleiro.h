#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <QGraphicsView>
#include <QGraphicsScene>

class Tabuleiro : public QGraphicsView //Declara a classe SegmentoCobra, herda QGraphicsView.
{
    Q_OBJECT //Necessário para usar sinais e slots.
public: //Membros públicos: acessíveis por outras classes.
    Tabuleiro(int larguraLogica,          //Construtor da classe Tabuleiro. Largura do tabuleiro.
              int alturaLogica,           //Altura do tabuleiro.
              int tamanhoBloco,           //Tamanho do bloco em pixels.
              QWidget *parent = nullptr); //Parent QWidget (para gerenciamento de memória).
    QGraphicsScene* getScene() const;     //Retorna a cena gráfica associada ao tabuleiro.
    int getLarguraLogica() const;         //Retorna a largura do tabuleiro em unidades lógicas (blocos). Classe jogo usa pra verificar colisões.
    int getAlturaLogica() const;          //Retorna a altura do tabuleiro em unidades lógicas (blocos). Classe jogo usa pra verificar colisões.

private: //Membros privados: acessíveis apenas dentro da classe.
    QGraphicsScene *m_scene; //Ponteiro para cena onde os itens são desenhados.
    int m_larguraLogica;     //Definição da largura da cena em blocos.
    int m_alturaLogica;      //Definição da altura da cena em blocos.
    int m_tamanhoBloco;      //Definição do tamanho de cada bloco em pixels.
};

#endif
