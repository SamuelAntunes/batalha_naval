#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

const int BOARD_SIZE = 10;
const int MAX_ATTEMPTS = 5;
const int TOTAL_BOATS = 10;

// Codigos ANSI para cores
const char* BLUE   = "\x1b[1;34m";
const char* GREEN  = "\x1b[1;32m";
const char* YELLOW = "\x1b[1;33m";
const char* CYAN   = "\x1b[1;36m";
const char* RED    = "\x1b[1;31m";
const char* WHITE  = "\x1b[1;37m";
const char* RESET  = "\x1b[0m";

// Funcao para limpar a tela (compatibilidade Windows/Unix)
void clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Exibe um banner colorido para o jogo
void displayBanner(){
    cout << YELLOW;
    cout << "========================================\n";
    cout << "            BATALHA NAVAL               \n";
    cout << "========================================\n" << RESET << "\n";
}

// Inicializa os tabuleiros: o real (com barcos) e a mascara (para exibicao)
void initializeBoards(char board[BOARD_SIZE][BOARD_SIZE], char mask[BOARD_SIZE][BOARD_SIZE]){
    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 0; j < BOARD_SIZE; j++){
            board[i][j] = 'A'; // 'A' representa agua
            mask[i][j] = '*';  // '*' representa celula oculta (nao revelada)
        }
    }
}

// Posiciona os barcos aleatoriamente no tabuleiro real
void placeBoats(char board[BOARD_SIZE][BOARD_SIZE]) {
    int placed = 0;
    while (placed < TOTAL_BOATS) {
        int row = rand() % BOARD_SIZE;
        int col = rand() % BOARD_SIZE;
        if (board[row][col] == 'A'){
            board[row][col] = 'P'; // 'P' representa um barco
            placed++;
        }
    }
}

// Exibe o tabuleiro com cores, usando caracteres ASCII para as bordas e efeito de agua
void displayBoardColored(char board[BOARD_SIZE][BOARD_SIZE], char mask[BOARD_SIZE][BOARD_SIZE], bool showSolution = false) {
    // Cabecalho com indices das colunas
    cout << "    ";
    for (int col = 0; col < BOARD_SIZE; col++){
        cout << " " << col << "  ";
    }
    cout << "\n";

    // Linha superior do tabuleiro
    cout << "   +";
    for (int col = 0; col < BOARD_SIZE; col++){
        cout << "---+";
    }
    cout << "\n";

    // Exibe cada linha do tabuleiro
    for (int row = 0; row < BOARD_SIZE; row++){
        // Exibe o numero da linha
        cout << (row < 10 ? " " : "") << row << " |";
        for (int col = 0; col < BOARD_SIZE; col++){
            char cell = mask[row][col];
            char displayChar;
            string colorCode;
            if (cell == '*'){
                displayChar = '*';
                colorCode = WHITE;
            } else if (cell == 'A'){
                displayChar = '~';  // efeito de agua
                colorCode = BLUE;
            } else if (cell == 'P'){
                displayChar = 'P';
                colorCode = GREEN;
            } else {
                displayChar = cell;
                colorCode = WHITE;
            }
            cout << " " << colorCode << displayChar << RESET << " |";
        }
        cout << "\n";

        // Linha divisoria entre as linhas
        cout << "   +";
        for (int col = 0; col < BOARD_SIZE; col++){
            cout << "---+";
        }
        cout << "\n";
    }

    // Se solicitado, exibe a solucao completa do tabuleiro
    if (showSolution) {
        cout << "\n" << CYAN << "Solucao do tabuleiro:" << RESET << "\n";
        for (int row = 0; row < BOARD_SIZE; row++){
            for (int col = 0; col < BOARD_SIZE; col++){
                char cell = board[row][col];
                if (cell == 'A')
                    cout << BLUE << "~" << RESET << " ";
                else if (cell == 'P')
                    cout << GREEN << "P" << RESET << " ";
                else
                    cout << cell << " ";
            }
            cout << "\n";
        }
    }
}

// Verifica se as coordenadas estao dentro dos limites do tabuleiro
bool isValidCoordinate(int row, int col){
    return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE);
}

// Processa o tiro do jogador: verifica acerto ou erro e evita tiros repetidos
void processShot(char board[BOARD_SIZE][BOARD_SIZE], char mask[BOARD_SIZE][BOARD_SIZE], int row, int col, int &score, string &message) {
    if (mask[row][col] != '*') {
        message = string(RED) + "Voce ja atirou nessa posicao. Tente outra!" + RESET;
        return;
    }
    if (board[row][col] == 'P'){
        score += 10;
        message = string(GREEN) + "Voce acertou um barco! (+10 pontos)" + RESET;
    } else {
        message = string(BLUE) + "Agua! Tente novamente." + RESET;
    }
    mask[row][col] = board[row][col];
}

// Exibe a pontuacao atual e as tentativas restantes
void displayScoreAndAttempts(int score, int attemptsLeft) {
    cout << "\n" << CYAN << "Pontos: " << score << " | Tentativas restantes: " << attemptsLeft << RESET << "\n";
}

// Exibe as instrucoes do jogo
void displayInstructions(){
    clearScreen();
    displayBanner();
    cout << CYAN << "Instrucoes:" << RESET << "\n";
    cout << "1. O tabuleiro e uma grade de 10x10.\n";
    cout << "2. Existem 10 barcos escondidos no tabuleiro.\n";
    cout << "3. Voce tem " << MAX_ATTEMPTS << " tentativas para acertar os barcos.\n";
    cout << "4. A cada acerto, voce ganha 10 pontos.\n";
    cout << "5. Digite as coordenadas (linha e coluna) para atirar.\n";
    cout << "6. Nao e permitido atirar na mesma posicao duas vezes.\n";
    cout << "\nPressione ENTER para voltar ao menu...";
    cin.ignore();
    cin.get();
}

// Funcao que executa a logica do jogo
void playGame(const string &playerName){
    char board[BOARD_SIZE][BOARD_SIZE];
    char mask[BOARD_SIZE][BOARD_SIZE];
    int score = 0;
    int attempts = MAX_ATTEMPTS;
    string message = "Bem-vindo, " + playerName + "!";

    initializeBoards(board, mask);
    placeBoats(board);

    while (attempts > 0) {
        clearScreen();
        displayBanner();
        displayBoardColored(board, mask, false);
        displayScoreAndAttempts(score, attempts);
        cout << message << "\n";

        int row, col;
        cout << "\n" << playerName << ", digite a linha (0-9): ";
        cin >> row;
        cout << playerName << ", digite a coluna (0-9): ";
        cin >> col;

        if (!isValidCoordinate(row, col)) {
            message = string(RED) + "Coordenadas invalidas! Por favor, digite valores entre 0 e 9." + RESET;
            continue;
        }

        string tempMessage;
        processShot(board, mask, row, col, score, tempMessage);
        // Se o tiro foi repetido, nao desconta tentativa
        if (tempMessage.find("ja atirou") != string::npos) {
            message = tempMessage;
            continue;
        } else {
            message = tempMessage;
            attempts--;
        }
    }

    clearScreen();
    displayBanner();
    displayBoardColored(board, mask, false);
    cout << "\n" << YELLOW << "Fim de jogo! Sua pontuacao final foi: " << score << RESET << "\n";
    cout << "\nDeseja ver a solucao do tabuleiro? (s/n): ";
    char show;
    cin >> show;
    if (show == 's' || show == 'S'){
        displayBoardColored(board, mask, true);
    }
    cout << "\nPressione ENTER para retornar ao menu...";
    cin.ignore();
    cin.get();
}

// Menu principal utilizando apenas caracteres ASCII para a moldura
void mainMenu(){
    int choice = 0;
    string playerName;
    do {
        clearScreen();
        displayBanner();
        cout << CYAN;
        cout << "+--------------------------------------+\n";
        cout << "|           MENU PRINCIPAL             |\n";
        cout << "+--------------------------------------+\n";
        cout << "| 1. Jogar                             |\n";
        cout << "| 2. Instrucoes                        |\n";
        cout << "| 3. Sobre o Jogo                      |\n";
        cout << "| 4. Sair                              |\n";
        cout << "+--------------------------------------+\n" << RESET;
        cout << "\nEscolha uma opcao e pressione ENTER: ";
        cin >> choice;
        switch(choice) {
            case 1:
                cout << "\nDigite seu nome: ";
                cin >> playerName;
                playGame(playerName);
                break;
            case 2:
                displayInstructions();
                break;
            case 3:
                clearScreen();
                displayBanner();
                cout << CYAN << "Sobre o Jogo:" << RESET << "\n";
                cout << "Batalha Naval - Versao 1.4.2\n";
                cout << "Desenvolvido como um projeto simples de jogo em C++.\n";
                cout << "\nPressione ENTER para retornar ao menu...";
                cin.ignore();
                cin.get();
                break;
            case 4:
                cout << "\n" << YELLOW << "Saindo do jogo. Ate logo!" << RESET << "\n";
                break;
            default:
                cout << "\n" << RED << "Opcao invalida! Tente novamente." << RESET << "\n";
                cin.ignore();
                cin.get();
                break;
        }
    } while (choice != 4);
}

int main(){
    srand(static_cast<unsigned int>(time(0)));
    mainMenu();
    return 0;
}
