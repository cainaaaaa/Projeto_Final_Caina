#include "tabuleiro.h"  //Inclui o cabeçalho da classe Tabuleiro.
#include <QBrush>       //Inclui a classe para definir a cor do fundo da cena.
#include <QPen>         //Inclui a classe para desenhar linhas ou bordas.

#define COR_FUNDO QColor(100, 100, 100) //Define a cor cinza escuro para o fundo do tabuleiro.

//--- Construtor da Classe Tabuleiro ---
//Este método é chamado para criar e configurar o palco visual do jogo.
Tabuleiro::Tabuleiro(int larguraLogica, int alturaLogica, int tamanhoBloco, QWidget *parent)
    : QGraphicsView(parent),        //Inicializa a classe base QGraphicsView com o parent.
    m_larguraLogica(larguraLogica), //Inicializa o atributo com a largura lógica.
    m_alturaLogica(alturaLogica),   //Inicializa o atributo com a altura lógica.
    m_tamanhoBloco(tamanhoBloco)    //Inicializa o atributo com o tamanho do bloco.
{
    //Calcula o tamanho total da cena em pixels com base nos valores lógicos.
    int larguraPixels = m_larguraLogica * m_tamanhoBloco;
    int alturaPixels = m_alturaLogica * m_tamanhoBloco;

    //Cria a cena gráfica com as dimensões em pixels.
    m_scene = new QGraphicsScene(0, 0, larguraPixels, alturaPixels, this);
    setScene(m_scene);    //Associa a cena criada ao QGraphicsView.

    //Define a cor de fundo da cena.
    m_scene->setBackgroundBrush(QBrush(COR_FUNDO));

    //Desabilita as barras de rolagem que apareceriam se a cena fosse maior que a view.
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //Define um tamanho fixo para a janela do tabuleiro (+2 pixels para a borda).
    setFixedSize(larguraPixels + 2, alturaPixels + 2);
    //Habilita o antialiasing para renderizar as bordas de forma mais suave.
    setRenderHint(QPainter::Antialiasing);
    //Impede que este widget capture o foco do teclado, permitindo que a MainWindow
    //o processe em keyPressEvent.
    setFocusPolicy(Qt::NoFocus);
}

//--- Método getScene ---
//Este "getter" permite que a classe Jogo acesse o ponteiro para a cena gráfica.
QGraphicsScene* Tabuleiro::getScene() const
{
    return m_scene;
}

//--- Métodos de Getter para as Dimensões ---
//Estes métodos expõem as dimensões lógicas do tabuleiro para outras classes.
int Tabuleiro::getLarguraLogica() const
{
    return m_larguraLogica;
}

int Tabuleiro::getAlturaLogica() const
{
    return m_alturaLogica;
}
