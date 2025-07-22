# Implementação


Para cada classe temos um aquivo .h (header/cabeçalho) e um .cpp (source/fonte), além de arquivos para a interface gráfica e o ponto de entrada do programa.

## 1. Arquivos de Cabeçalho (.h)
    • Contem as declarações (o que a classe é, quais atributos ela tem, quais métodos ela oferece),
    mas não as implementações (como os métodos fazem o que fazem).
    • Conteúdo:
        ◦ Includes: Outros arquivos de cabeçalho necessários para que as declarações desta classe funcionem
        (ex: Cobra.h precisa incluir SegmentoCobra.h).
        ◦ Declaração da classe:  nome da classe, membros (public, private, protected) e a declaração de 
        atributos e métodos.
        ◦ Enums ou structs: Definições de tipos personalizados que são usados por várias partes do código.
          
## 2. Arquivos de Implementação (.cpp)
    • Contêm a implementação real das funcionalidades declaradas nos arquivos .h. É aqui onde é escrito 
    o "como" os métodos funcionam.
    • Conteúdo:
        ◦ Include do .h correspondente: Sempre começa incluindo seu próprio arquivo de cabeçalho.
        ◦ Implementação dos métodos: O código que faz cada método funcionar.

## 3. Arquivos Específicos do Qt
    • main.cpp:
        ◦ Ponto de Entrada: É o primeiro arquivo que o programa executa.
        ◦ Cria a aplicação Qt (QApplication): Necessário para que a aplicação Qt funcione.
        ◦ Cria a janela principal (MainWindow): Instancia sua janela principal.
        ◦ Inicia o loop de eventos: a.exec(), que faz a aplicação rodar e responder a eventos do usuário 
        (cliques, teclado, etc.).
        
    • mainwindow.ui:
        ◦ Interface de Usuário (UI): Descreve a aparência da janela: onde os botões estão, labels, 
        campos de texto, etc.

    • .pro (Arquivo de Projeto):
        ◦ Configuração do Projeto: É um arquivo de texto simples que o sistema de build do Qt (qmake) usa. 
        Ele informa ao Qt Creator:
            ▪ Quais módulos do Qt usar (QT += core gui widgets).
            ▪ Quais arquivos .h, .cpp e .ui fazem parte do seu projeto.
            ▪ Outras opções de compilação, links de bibliotecas, etc.






<div align="center">

[Retroceder](analise.md) | [Avançar](projeto.md)

</div>
