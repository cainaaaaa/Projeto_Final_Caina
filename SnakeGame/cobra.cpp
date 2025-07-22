#include "cobra.h"         //Inclui o cabeçalho da classe Cobra.
#include "posicao.h"       //Inclui a definição de Posicao.
#include "segmentocobra.h" //Inclui o cabeçalho da classe SegmentoCobra.
#include <QDebug>          //Inclui a biblioteca para depuração.
#include <QList>           //Inclui a classe QList do Qt.

#define INICIO_X 5 //Posição x inicial da cobra.
#define INICIO_Y 5 //Posição y inicial da cobra.
#define COMPRIMENTO_INICIAL 5 //Define o tamanho inicial da cobra.

//--- Construtor da Classe Cobra ---
Cobra::Cobra(QGraphicsScene *scene, int tamanhoBloco, QObject *parent) //Inicialização do construtor.
    : QObject(parent),            //Inicializa a classe base QObject.
    m_scene(scene),               //Inicializa o ponteiro para a cena gráfica.
    m_tamanhoBloco(tamanhoBloco), //Inicializa o tamanho do bloco.
    m_deveCrescer(false)          //Flag de crescimento começa em false.
{
    reset(); //Chama o método reset para configurar a cobra pela primeira vez.
}

// --- Método reset ---
void Cobra::reset()  //Reinicia o estado da cobra para um novo jogo.
{
    //Deleta os segmentos da cobra da partida anterior e limpa a lista.
    qDeleteAll(m_corpo);
    m_corpo.clear();

    m_direcaoAtual = Direita;   //Define a direção inicial como Direita.
    m_proximaDirecao = Direita; //Define a próxima direção como Direita.
    m_deveCrescer = false;      //Inicializa o crescimento como false.

    //Adiciona os segmentos iniciais da cobra (COMPRIMENTO_INICIAL)
    for (int i = 0; i < COMPRIMENTO_INICIAL; ++i) {
        //Cria um novo SegmentoCobra na memória.
        SegmentoCobra* seg = new SegmentoCobra(INICIO_X - i, INICIO_Y, m_tamanhoBloco);
        m_corpo.append(seg);   //Adiciona o ponteiro à lista.
        m_scene->addItem(seg); //Adiciona o item à cena gráfica.
    }
}

//--- Método mover ---
void Cobra::mover() //Lógica que move a cobra a cada 'tick' do jogo.
{
    m_direcaoAtual = m_proximaDirecao; //Atualiza a direção com a direção desejada.

    //Pega a posição da cabeça atual.
    Posicao cabecaAtual = getPosicaoCabeca();
    Posicao novaCabecaPos = cabecaAtual;

    //Calcula a nova posição da cabeça com base na direção atual.
    switch (m_direcaoAtual) {
    case Cima:    novaCabecaPos.setY(novaCabecaPos.y() - 1); break;
    case Baixo:   novaCabecaPos.setY(novaCabecaPos.y() + 1); break;
    case Esquerda: novaCabecaPos.setX(novaCabecaPos.x() - 1); break;
    case Direita: novaCabecaPos.setX(novaCabecaPos.x() + 1); break;
    }

    //Cria um novo segmento para a nova cabeça.
    SegmentoCobra* novaCabeca = new SegmentoCobra(novaCabecaPos.x(), novaCabecaPos.y(), m_tamanhoBloco);
    m_corpo.prepend(novaCabeca); //Adiciona a nova cabeça no início da lista.
    m_scene->addItem(novaCabeca); //Adiciona a nova cabeça à cena.

    //Remove o último segmento (a cauda) se a cobra NÃO deve crescer.
    if (!m_deveCrescer) {
        delete m_corpo.last();  //Libera a memória do objeto.
        m_corpo.removeLast();   //Remove a referencia ao objeto da lista.
    }else {
        m_deveCrescer = false; //Reseta o flag após o crescimento.
    }
}

//--- Método crescer ---
void Cobra::crescer()     //Prepara a cobra para crescer no próximo movimento.
{
    m_deveCrescer = true;  //Define a flag de crescimento como true.
    qDebug() << "Cobra sinalizada para crescer!";
}

//--- Método setDirecao ---
void Cobra::setDirecao(Direcao novaDirecao)  //Define a próxima direção da cobra, com validação de 180 graus.
{
    if ((m_direcaoAtual == Cima && novaDirecao == Baixo) ||
        (m_direcaoAtual == Baixo && novaDirecao == Cima) ||
        (m_direcaoAtual == Esquerda && novaDirecao == Direita) ||
        (m_direcaoAtual == Direita && novaDirecao == Esquerda))
    {
        return; //Não permite a virada de 180 graus.
    }
    m_proximaDirecao = novaDirecao;  //Se não entrar no if, atualiza a direção.
}

//--- Método Posição Cobra ---
Posicao Cobra::getPosicaoCabeca() const   //Usado para lógica de colisão.
{
    return m_corpo.first()->getPosicao(); //Retorna a primeira posição do corpo. A cabeça da cobra.
}

//--- Método Colide com Corpo ---
bool Cobra::colideComCorpo() const //Verifica se houve colisão com o corpo.
{
    Posicao cabeca = getPosicaoCabeca();  //Armazena a posição da cabeça em uma variável local

    //Loop para verificar cada segmento do corpo da cobra, começando pelo segundo segmento, para pular a cabeça.
    for (int i = 1; i < m_corpo.size(); ++i) {
        //Compara a posição da cabeça com a posição do segmento atual do corpo.
        if (cabeca == m_corpo.at(i)->getPosicao()) {
            //Se as posições forem iguais, uma colisão foi detectada, e a função retorna 'true'.
            return true;
        }
    }
    //Se o loop terminar sem encontrar uma colisão, a função retorna 'false'.
    return false;
}

//--- Método Colide com Parede ---
bool Cobra::colideComParede(int larguraTabuleiro, int alturaTabuleiro) const //Verifica se houve colisão com a parede.
{
    Posicao cabeca = getPosicaoCabeca(); //Armazena a posição da cabeça em uma variável local
    // Retorna true se qualquer uma das quatro condições de colisão for verdadeira.
    return cabeca.x() <= 0 ||                //A cabeça está à esquerda da borda.
           cabeca.x() >= larguraTabuleiro || //A cabeça está à direita da borda.
           cabeca.y() <= 0 ||                //A cabeça está acima da borda superior.
           cabeca.y() >= alturaTabuleiro;    //A cabeça está abaixo da borda inferior.
}

//--- Método Colide com Parede ---
const QList<SegmentoCobra*>& Cobra::getCorpo() const  //Acesso a lista de ponteiros do corpo da cobra de forma protegida.
{
    return m_corpo;   //Retorna a lista de segmento que compõe a cobra.
}
