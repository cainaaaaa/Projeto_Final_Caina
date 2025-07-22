#include "alimento.h"       //Inclui o cabeçalho de Alimento, que contém a declaração da classe.
#include <QRandomGenerator> //Inclui biblioteca para gerar números aleatórios.
#include <QBrush>           //Inclui QBrush, classe do Qt usada para definir a cor de preenchimento de formas.
#include <QPen>             //Inclui QPen, classe do Qt usada para definir a cor e o estilo da borda de formas.
#include <QDebug>           //Inclui QDebug para permitir a saída de mensagens de depuração no console.

// Cor do alimento
#define COR_ALIMENTO QColor(200, 0, 0) //Define uma macro para a cordo alimento. Vermelha.

//--- Construtor da Classe Alimento ---
Alimento::Alimento(int tamanhoBloco, QGraphicsScene *scene, QObject *parent) //Inicialização do construtor.
    : QGraphicsEllipseItem(),     //Chama o construtor da classe QGraphicsEllipseItem para inicializar as propriedades gráficas.
    m_tamanhoBloco(tamanhoBloco), //Inicializa o atributo m_tamanhoBloco com o valor do parâmetro tamanhoBloco.
    m_scene(scene)                //Inicializa o atributo m_scene com o valor do parâmetro scene.
{
    setRect(0, 0, m_tamanhoBloco, m_tamanhoBloco); //Define o tamanho visual da elipse.
    setBrush(QBrush(COR_ALIMENTO));                //Define a cor de preenchimento da elipse para vermelho.
    setPen(QPen(Qt::black, 2));                    //Define a cor da borda da elipse como preta, com espessura 1.
}

//--- Método gerarNovaPosicao ---
//Este método encontra e define uma nova posição para o alimento que não está ocupada pela cobra.
void Alimento::gerarNovaPosicao(int larguraTabuleiro, int alturaTabuleiro, const QList<SegmentoCobra*>& corpoCobra)
{
    Posicao novaPos;      //Declara uma variável para a nova posição.
    bool colidiuComCobra; //Declara uma flag para verificar se a posição gerada colide com a cobra.

    do { //Loop que será executado pelo menos uma vez.
        colidiuComCobra = false; //Reseta a flag a cada iteração do loop.

        //Gera posições aleatórias para o alimento dentro dos limites do tabuleiro.
        novaPos.setX(QRandomGenerator::global()->bounded(larguraTabuleiro));
        novaPos.setY(QRandomGenerator::global()->bounded(alturaTabuleiro));

        //Inicia um loop para verificar cada segmento da cobra.
        for (SegmentoCobra* seg : corpoCobra) {
            if (novaPos == seg->getPosicao()) { //Se a nova posição colidir com um segmento da cobra,
                colidiuComCobra = true;         //Define a flag como verdadeira,
                break;                          //Sai do loop for para gerar uma nova posição.
            }
        }
    } while (colidiuComCobra); //O loop 'do-while' continua enquanto a posição gerada colidir com a cobra.

    m_posicao = novaPos;       //Atribui a nova posição válida ao atributo m_posicao do alimento.
    setPos(m_posicao.x() * m_tamanhoBloco, m_posicao.y() * m_tamanhoBloco); //Atualiza a posição visual do alimento.

    if (!scene()) {             //Se scene() não tiver um alimento.
        m_scene->addItem(this); //Adiciona um alimento a cena.
    }
    qDebug() << "Alimento gerado em:" << m_posicao.x() << "," << m_posicao.y(); //Imprime a nova posição para depuração.
}


Posicao Alimento::getPosicao() const  //Método para retornar a posição lógica do alimento
{
    return m_posicao; //Retorna o valor do atributo privado m_posicao.
}
