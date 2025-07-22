#include "segmentocobra.h" //Inclui o cabeçalho da classe SegmentoCobra.
#include <QBrush>          //Inclui QBrush, usado para definir a cor de preenchimento do segmento.
#include <QPen>            //Inclui QPen, usado para definir a cor e espessura da borda.

#define COR_COBRA QColor(0, 150, 0) //Define a cor verde para os segmentos da cobra.

//--- Construtor da Classe SegmentoCobra ---
SegmentoCobra::SegmentoCobra(int x, int y, int tamanhoBloco, QGraphicsItem *parent) // Lista de inicialização do construtor.
    : QGraphicsRectItem(parent), //Chama o construtor da classe base (QGraphicsRectItem) e passa o parent.
    m_posicao(x, y),             //Inicializa a posição lógica do segmento com os valores (x, y).
    m_tamanhoBloco(tamanhoBloco) //Inicializa o tamanho do bloco.
{
    //Define o retângulo visual do item. As coordenadas são em pixels.
    setRect(x * m_tamanhoBloco, y * m_tamanhoBloco, m_tamanhoBloco, m_tamanhoBloco);
    //Define a cor de preenchimento do retângulo com a cor COR_COBRA.
    setBrush(QBrush(COR_COBRA));
    //Define a cor e a espessura da borda do retângulo.
    setPen(QPen(Qt::black, 1));
}

//--- Método getPosicao ---
//Este método 'getter' retorna a posição lógica do segmento.
Posicao SegmentoCobra::getPosicao() const
{
    return m_posicao; //Retorna o valor do atributo privado m_posicao.
}

//--- Método setPosicao ---
//Este método atualiza a posição lógica e visual do segmento.
void SegmentoCobra::setPosicao(int x, int y)
{
    //Atualiza a posição lógica do segmento.
    m_posicao.setX(x);
    m_posicao.setY(y);

    //Atualiza a posição gráfica (em pixels) do QGraphicsRectItem na cena.
    setPos(x * m_tamanhoBloco, y * m_tamanhoBloco);
}
