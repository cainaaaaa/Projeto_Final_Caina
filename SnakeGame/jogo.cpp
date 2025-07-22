#include "jogo.h"       //Inclui o cabeçalho da classe Jogo, que contém as declarações.
#include <QDebug>       //Inclui a biblioteca para depuração.
#include <QMessageBox>  //Inclui a classe para exibir janelas de mensagem.
#include <Qtimer>       //Inclui a classe QTimer, que controla o tempo do jogo.

//Define uma constante int para a velocidade inicial do jogo.
const int VELOCIDADE_INICIAL_MS = 200; //200ms por tick

//--- Construtor da Classe Jogo ---
//Este método é chamado quando um novo objeto Jogo é criado. Ele inicializa o jogo.
Jogo::Jogo(Tabuleiro *tabuleiro, int larguraLogica, int alturaLogica, int tamanhoBloco, QObject *parent)
    : QObject(parent),              //Inicializa a classe base QObject.
    m_tabuleiro(tabuleiro),         //Inicializa o ponteiro do tabuleiro.
    m_larguraLogica(larguraLogica), //Inicializa a largura lógica.
    m_alturaLogica(alturaLogica),   //Inicializa a altura lógica.
    m_tamanhoBloco(tamanhoBloco),   //Inicializa o tamanho do bloco.
    m_pontuacao(0),                 //A pontuação inicial é zero.
    m_estadoJogo(FimDeJogo),        //O jogo começa no estado de FimDeJogo.
    m_velocidadeJogo(VELOCIDADE_INICIAL_MS) //Define a velocidade inicial.
{
    m_scene = m_tabuleiro->getScene(); //Obtém o ponteiro para a cena gráfica do tabuleiro.

    //Cria os objetos da cobra e do alimento, passando a cena.
    m_cobra = new Cobra(m_scene, m_tamanhoBloco, this);
    m_alimento = new Alimento(m_tamanhoBloco, m_scene, this);

    //Cria o QTimer e conecta seu sinal timeout ao slot atualizarJogo.
    m_timerJogo = new QTimer(this);
    connect(m_timerJogo, &QTimer::timeout, this, &Jogo::atualizarJogo);

}

// --- Método iniciarJogo ---
//Chamado para começar um novo jogo. Também serve como o método de reset do jogo.
void Jogo::iniciarJogo()
{
    qDebug() << "Iniciando jogo...";
    m_cobra->reset();    //Reseta a cobra para sua posição e tamanho iniciais.
    gerarNovoAlimento(); //Gera o primeiro alimento.
    m_pontuacao = 0;     //Zera a pontuação inicial.
    m_velocidadeJogo = VELOCIDADE_INICIAL_MS; //Seta a velocidade inicial.

    m_timerJogo->start(m_velocidadeJogo);  //Inicia o timer com a velocidade.
    m_estadoJogo = Rodando;                //Define o estado como Rodando.
    emit pontuacaoAlterada(m_pontuacao);   //Emite um sinal para atualizar a pontuação na UI.
    emit estadoJogoAlterado(m_estadoJogo); //Emite um sinal para atualizar o estado na UI.
}

//--- Método pausarJogo ---
//Pausa o jogo se ele estiver rodando.
void Jogo::pausarJogo()
{
    if (m_estadoJogo == Rodando) {   //Se o jogo estiver rodando.
        m_timerJogo->stop();         //Para o timer.
        m_estadoJogo = Pausado;      //Muda o estado para Pausado.
        qDebug() << "Jogo Pausado";
        emit estadoJogoAlterado(m_estadoJogo); //Emite um sinal para atualizar o estado na UI.
    }
}

//--- Método retomarJogo ---
//Retoma o jogo se ele estiver pausado.
void Jogo::retomarJogo()
{
    if (m_estadoJogo == Pausado) {            //Se o jogo estiver pausado.
        m_timerJogo->start(m_velocidadeJogo); //Inicia o timer com a velocidade atual.
        m_estadoJogo = Rodando;               //Muda o estado para Rodando.
        qDebug() << "Jogo Retomado";
        emit estadoJogoAlterado(m_estadoJogo);//Emite um sinal para atualizar o estado na UI.
    }
}

//--- Método fimDeJogo ---
//Lógica que é executada quando o jogo termina.
void Jogo::fimDeJogo()
{
    m_timerJogo->stop();             //Para o timer.
    m_estadoJogo = FimDeJogo;        //Muda o estado para Fim de Jogo.
    qDebug() << "Fim de Jogo! Pontuação: " << m_pontuacao;
    emit jogoEncerrado(m_pontuacao); //Emite um sinal para a UI com a pontuação final.
    emit estadoJogoAlterado(m_estadoJogo); //Emite um sinal para atualizar o estado na UI.

    //Exibe uma janela de mensagem com a pontuação final.
    QMessageBox::information(nullptr, "Fim de Jogo", QString("Sua pontuação final: %1").arg(m_pontuacao));
}


//--- Método atualizarJogo ---
//Este método é chamado pelo QTimer a cada tick.
void Jogo::atualizarJogo() //Loop principal do jogo.
{
    //Se o jogo NÃO estiver rodando, o método não faz nada.
    if (m_estadoJogo != Rodando) {
        return;
    }
    //Se o jogo estiver rodando.
    m_cobra->mover();  //Chama o método para mover a cobra.
    checarColisoes();  //Chama o método para verificar colisões.
}

//--- Método checarColisoes ---
//Verifica se a cobra colidiu.
void Jogo::checarColisoes()
{
    //Colisão com parede: Se a cobra colidir com as bordas, o jogo termina.
    if (m_cobra->colideComParede(m_tabuleiro->getLarguraLogica(), m_tabuleiro->getAlturaLogica())) {
        fimDeJogo();
        return;
    }

    //Colisão com o próprio corpo: Se a cabeça colidir com o corpo, o jogo termina.
    if (m_cobra->colideComCorpo()) {
        fimDeJogo();
        return;
    }

    //Colisão com alimento: Se a cabeça da cobra colidir com o alimento.
    if (m_cobra->getPosicaoCabeca() == m_alimento->getPosicao()) {
        m_cobra->crescer();                 //Chama o metodo crescer.
        m_pontuacao += 10;                  //Aumenta a pontuação.
        emit pontuacaoAlterada(m_pontuacao);//Emite um sinal para atualizar a pontuação na UI.

        gerarNovoAlimento(); //Um novo alimento é gerado.

         //Velocidade aumenta a cada 50 pontos e não será maior que 50ms.
        if (m_pontuacao % 50 == 0 && m_velocidadeJogo > 50) {
            m_velocidadeJogo -= 10;                      //Diminui em 10ms o intervalo do QTimer.
            m_timerJogo->setInterval(m_velocidadeJogo);  //Seta o QTimer com o novo valor.
            qDebug() << "Velocidade aumentada para:" << m_velocidadeJogo;
        }
    }
}

//--- Método gerarNovoAlimento ---
//Gera e posiciona um novo alimento na tela.
void Jogo::gerarNovoAlimento()
{
    //Chama o metoto do alimento de gerarNovaPosicao.
    m_alimento->gerarNovaPosicao(m_tabuleiro->getLarguraLogica(), m_tabuleiro->getAlturaLogica(), m_cobra->getCorpo());
}

//--- Método processarEntrada ---
//Processa a entrada do teclado do usuário.
void Jogo::processarEntrada(Direcao direcao)
{
    if (m_estadoJogo == Rodando) {     //Se o jogo estiver rodando.
        m_cobra->setDirecao(direcao);  //Chama o metodo da cobra setDirecao.
    }
}

//--- Métodos Getters ---
//Métodos para obter informações do estado do jogo.
int Jogo::getPontuacao() const
{
    return m_pontuacao;
}

EstadoJogo Jogo::getEstadoJogo() const
{
    return m_estadoJogo;
}
