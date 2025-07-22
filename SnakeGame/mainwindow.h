#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>  //Inclui QMainWindow. Herda para ter funcionalidades como barra de menu, barra de status, etc.
#include <QLabel>       //Inclui QLabel. Usado para criar os rótulos de texto que exibirão a pontuação e o estado do jogo.
#include <QKeyEvent>    //Inclui QKeyEvent. Necessário para capturar os eventos do teclado.

#include "jogo.h"       //Inclui Jogo.h, usado para criar uma instância dele para interagir com sua lógica.
#include "tabuleiro.h"  //Inclui Tabuleiro.h, usado para criar uma instância do tabuleiro para exibir o jogo.

//Macros do Qt para vincular toda a logica do projeto com a interface visual.
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow //Declara a classe MainWindow, herda QMainWindow. Janela de exibição do jogo
{
    Q_OBJECT //Macro do Qt. Essencial para que esta classe possa usar sinais e slots.

public: //Membros públicos: acessíveis de fora da classe.

    MainWindow(QWidget *parent = nullptr); //Construtor da classe MainWindow. Parent QObject (para gerenciamento de memória).
    ~MainWindow(); //Destrutor da classe, responsavel por liberar os recursos gerados pela classe dos objetos m_jogo e m_tabuleiro.

protected: //Membros protegidos: acessíveis pela própria classe e por classes que herdam dela.
    void keyPressEvent(QKeyEvent *event) override; // Ele é chamado automaticamente pelo Qt sempre que uma tecla é pressionada.

private: //Membros privados: acessíveis apenas de dentro desta classe.
    Ui::MainWindow *ui;     //Ponteiro para a classe de interface de usuário. Contém todos os widgets adicionados visualmente no arquivo .ui.

    Jogo *m_jogo;           //Ponteiro para um objeto do tipo jogo que a MainWindow gerencia.
    Tabuleiro *m_tabuleiro; //Ponteiro para um objeto do tipo tabuleiro que a MainWindow usa para exibir o campo visual do jogo.

    QLabel *m_pontuacaoLabel;  //Ponteiro para exibição da pontuação através de um QLabel.
    QLabel *m_estadoJogoLabel; //Ponteiro para exibição do estado do jogo através de um QLabel.

    const int LARGURA_TABULEIRO = 40;  //Atributo contante para a lagura do tabuleiro em blocos.
    const int ALTURA_TABULEIRO = 30;   //Atributo contante para a altura do tabuleiro em blocos.
    const int TAMANHO_BLOCO = 20;      //Atributo constante para o tamanho de cada bloco em pixels.
};

#endif
