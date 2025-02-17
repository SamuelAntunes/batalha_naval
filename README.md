# Batalha Naval

Este é um projeto simples de jogo de batalha naval desenvolvido em C++. O jogo consiste em um tabuleiro 10x10 onde o jogador tem um número limitado de tentativas para encontrar os barcos escondidos. Cada acerto vale pontos e, ao final, é possível visualizar a solução do tabuleiro.

## Funcionalidades

- **Tabuleiro Colorido:**  
  - O tabuleiro é exibido com cores utilizando códigos ANSI.
  - A água é representada por `~` em azul e os barcos atingidos por `P` em verde.
- **Menu Interativo:**  
  - O menu utiliza caracteres ASCII para exibição, garantindo compatibilidade sem o uso de acentos.
  - Opções disponíveis: Jogar, Instrucoes, Sobre o Jogo e Sair.
- **Validação de Entrada:**  
  - O jogo valida as coordenadas informadas e impede que o jogador atire na mesma posição mais de uma vez.
- **Feedback Dinâmico:**  
  - Mensagens de acerto, erro, pontuacao e tentativas restantes são exibidas durante o jogo.

## Requisitos

- **Compilador C++:**  
  Recomenda-se o uso do [g++](https://gcc.gnu.org/) ou de outro compilador compatível com C++11 ou superior.
- **Terminal Compatível com ANSI:**  
  Para que as cores sejam exibidas corretamente.

## Como Compilar

### Em Sistemas Linux ou macOS:
Abra um terminal na pasta do projeto e execute:

```bash
g++ -std=c++11 -o batalhanaval main.cpp

 
