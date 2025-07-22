#include "mainwindow.h"      //Inclui o cabeçalho da classe MainWindow.
#include "./ui_mainwindow.h" //Inclui o cabeçalho gerado pelo Qt Designer que contém a definição da UI.
#include <QVBoxLayout>       //Inclui a classe para organizar widgets em uma coluna.
#include <QHBoxLayout>       //Inclui a classe para organizar widgets em uma linha.
#include <QPushButton>       //Inclui a classe para criar botões.
#include <QDebug>            //Inclui a classe para mensagens de depuração no console.

//--- Construtor da Classe MainWindow ---
//Este método é chamado quando a janela principal da aplicação é criada.
MainWindow::MainWindow(QWidget *parent) //Inicialização do construtor.
    : QMainWindow(parent),              //Inicializa a classe base QMainWindow.
    ui(new Ui::MainWindow)              //Cria uma nova instância da classe de UI gerada.
{
    ui->setupUi(this);                  //Configura a janela principal com os widgets do arquivo .ui.

    //1. Configurar o layout principal.
    QWidget *centralWidget = new QWidget(this);              //Cria um widget central para o layout.
    setCentralWidget(centralWidget);                         //Define o widget central da janela.
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);//Cria um layout vertical para o widget central.

    //2. Cria e adiciona o tabuleiro (QGraphicsView).
    //O 'this' no final define a MainWindow como o pai do Tabuleiro.
    m_tabuleiro = new Tabuleiro(LARGURA_TABULEIRO, ALTURA_TABULEIRO, TAMANHO_BLOCO, this);
    mainLayout->addWidget(m_tabuleiro); //Adiciona o tabuleiro ao layout principal.

    //3. Criar os labels para pontuação e estado.
    QHBoxLayout *infoLayout = new QHBoxLayout();         //Cria um layout horizontal para os labels.
    m_pontuacaoLabel = new QLabel("Pontuação: 0", this); //Cria o label da pontuação.
    m_estadoJogoLabel = new QLabel("Estado: Pressione 'Iniciar'", this); //Cria o label do estado.

    infoLayout->addWidget(m_pontuacaoLabel);  //Adiciona o label de pontuação ao layout de info.
    infoLayout->addStretch();                 //Adiciona um espaço flexível.
    infoLayout->addWidget(m_estadoJogoLabel); //Adiciona o label de estado ao layout.
    mainLayout->addLayout(infoLayout);        //Adiciona o layout de info ao layout principal.

    //4. Criar botões Iniciar/Pausar
    QHBoxLayout *buttonLayout = new QHBoxLayout();      //Cria um layout horizontal para os botões.
    QPushButton *startButton = new QPushButton("Iniciar Jogo", this); //Cria o botão Iniciar.
    QPushButton *pauseButton = new QPushButton("Pausar Jogo", this);  //Cria o botão Pausar.

    buttonLayout->addWidget(startButton); //Adiciona o botão Iniciar ao layout dos botões.
    buttonLayout->addWidget(pauseButton); //Adiciona o botão Pausar ao layout dos botões.
    mainLayout->addLayout(buttonLayout);  //Adiciona o layout dos botões ao layout principal.

    //5. Instanciar a lógica do jogo
    //Cria uma nova instância da classe Jogo, passando o Tabuleiro e as dimensões.
    m_jogo = new Jogo(m_tabuleiro, LARGURA_TABULEIRO, ALTURA_TABULEIRO, TAMANHO_BLOCO, this);

    //6. Conectar sinais e slots do jogo com a UI
    //Conecta o sinal de pontuação da classe Jogo ao label da pontuação.
    connect(m_jogo, &Jogo::pontuacaoAlterada, m_pontuacaoLabel, [this](int pontuacao){
        m_pontuacaoLabel->setText(QString("Pontuação: %1").arg(pontuacao));
    });
    //Conecta o sinal de jogo encerrado. A mensagem é exibida em Jogo.
    connect(m_jogo, &Jogo::jogoEncerrado, this, [this]{
    });
    //Conecta o sinal de estado do jogo para atualizar o label de estado.
    connect(m_jogo, &Jogo::estadoJogoAlterado, this, [this](EstadoJogo estado){
        QString estadoStr;
        switch (estado) {
        case Rodando: estadoStr = "Rodando"; break;
        case Pausado: estadoStr = "Pausado"; break;
        case FimDeJogo: estadoStr = "Fim de Jogo"; break;
        }
        m_estadoJogoLabel->setText(QString("Estado: %1").arg(estadoStr));
    });

    //Conecta o clique dos botões aos métodos da classe Jogo.
    connect(startButton, &QPushButton::clicked, m_jogo, &Jogo::iniciarJogo);
    connect(pauseButton, &QPushButton::clicked, m_jogo, [this](){
        if (m_jogo->getEstadoJogo() == Rodando) {
            m_jogo->pausarJogo();
        } else if (m_jogo->getEstadoJogo() == Pausado) {
            m_jogo->retomarJogo();
        }
    });

    //Garante que a MainWindow receba eventos de teclado.
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
}

//--- Destrutor da Classe MainWindow ---
MainWindow::~MainWindow()
{
    delete ui; // Deleta a interface de usuário gerada.
    // Os objetos m_jogo e m_tabuleiro são deletados automaticamente pelo Qt,
    // pois eles foram criados com 'this' (a MainWindow) como parent.
}

//--- Método keyPressEvent ---
//Sobrescreve o método padrão para capturar o pressionar de teclas.
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //Se o jogo estiver rodando, processa a entrada do teclado.
    if (m_jogo->getEstadoJogo() == Rodando) {
        Direcao direcao;
        bool direcaoValida = true;
        //Usa switch/case para determinar qual tecla foi pressionada.
        switch (event->key()) {
        case Qt::Key_Up:    direcao = Cima;    break;
        case Qt::Key_Down:  direcao = Baixo;   break;
        case Qt::Key_Left:  direcao = Esquerda; break;
        case Qt::Key_Right: direcao = Direita; break;
        case Qt::Key_Space: m_jogo->pausarJogo(); return; //Pausa o jogo e sai da função.
        default: direcaoValida = false; break; //Se a tecla não for uma seta ou espaço, a entrada é inválida.
        }
        if (direcaoValida) {
            m_jogo->processarEntrada(direcao); //Envia a direção válida para a classe Jogo.
        }
    } else if (event->key() == Qt::Key_Space && m_jogo->getEstadoJogo() == Pausado) {
        m_jogo->retomarJogo(); //Se o jogo estiver pausado, a tecla Espaço o retoma.
    }
    //Chama a implementação do método na classe base QMainWindow.
    QMainWindow::keyPressEvent(event);
}
