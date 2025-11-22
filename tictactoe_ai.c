#include <stdio.h>
#include <stdlib.h>

#define PLAYER 'X'
#define COMPUTER 'O'
#define EMPTY  ' '

/* board as 1D array 0..8 (row = idx/3, col = idx%3) */
char board[9];

/* 초기화 */
void initBoard() {
    for (int i = 0; i < 9; ++i) board[i] = EMPTY;
}

/* 보드 출력 (빈칸엔 번호 표시) */
void printBoard() {
    puts("");
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            int idx = r*3 + c;
            if (board[idx] == EMPTY) printf(" %d ", idx+1);
            else printf(" %c ", board[idx]);
            if (c < 2) printf("|");
        }
        puts("");
        if (r < 2) puts("---+---+---");
    }
    puts("");
}

/* 승자 또는 아직 없음 반환: 'X', 'O' 또는 ' ' */
char checkWinner() {
    int lines[8][3] = {
        {0,1,2},{3,4,5},{6,7,8}, // rows
        {0,3,6},{1,4,7},{2,5,8}, // cols
        {0,4,8},{2,4,6}          // diags
    };
    for (int i = 0; i < 8; ++i) {
        int a = lines[i][0], b = lines[i][1], c = lines[i][2];
        if (board[a] != EMPTY && board[a] == board[b] && board[b] == board[c])
            return board[a];
    }
    return EMPTY;
}

/* 남은 수(빈칸) 있는지 */
int movesLeft() {
    for (int i = 0; i < 9; ++i) if (board[i] == EMPTY) return 1;
    return 0;
}

/* 게임 상태 점수화: 컴퓨터(O) 관점에서 반환.
   승리: +10 - depth (빠른 승리 선호), 패배: -10 + depth, 무승부: 0 */
int minimax(int depth, int isMaximizing) {
    char winner = checkWinner();
    if (winner == COMPUTER) return 10 - depth;
    if (winner == PLAYER)   return -10 + depth;
    if (!movesLeft())       return 0; // 무승부

    if (isMaximizing) {
        int best = -1000;
        for (int i = 0; i < 9; ++i) {
            if (board[i] == EMPTY) {
                board[i] = COMPUTER;
                int val = minimax(depth + 1, 0);
                board[i] = EMPTY;
                if (val > best) best = val;
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 9; ++i) {
            if (board[i] == EMPTY) {
                board[i] = PLAYER;
                int val = minimax(depth + 1, 1);
                board[i] = EMPTY;
                if (val < best) best = val;
            }
        }
        return best;
    }
}

/* 컴퓨터의 최적 수 선택 */
int findBestMove() {
    int bestVal = -1000;
    int bestMove = -1;
    for (int i = 0; i < 9; ++i) {
        if (board[i] == EMPTY) {
            board[i] = COMPUTER;
            int moveVal = minimax(0, 0);
            board[i] = EMPTY;
            if (moveVal > bestVal) {
                bestVal = moveVal;
                bestMove = i;
            }
        }
    }
    return bestMove; // index 0..8
}

/* 메인 게임 루프 */
int main() {
    initBoard();
    int pos;
    char turn = PLAYER; // 플레이어가 먼저 둠

    puts("Tic-Tac-Toe (Player X vs Computer O)");
    puts("Enter positions 1-9. Layout:");
    puts(" 1 | 2 | 3 ");
    puts("---+---+---");
    puts(" 4 | 5 | 6 ");
    puts("---+---+---");
    puts(" 7 | 8 | 9 ");
    
    while (1) {
        printBoard();
        if (turn == PLAYER) {
            printf("Your move (1-9): ");
            if (scanf("%d", &pos) != 1) {
                puts("Invalid input. Exiting.");
                return 0;
            }
            pos -= 1;
            if (pos < 0 || pos > 8) {
                puts("Position must be 1..9. Try again.");
                continue;
            }
            if (board[pos] != EMPTY) {
                puts("Cell already taken. Try again.");
                continue;
            }
            board[pos] = PLAYER;
        } else { // COMPUTER
            int best = findBestMove();
            if (best == -1) { // safety
                puts("Computer has no move (weird).");
            } else {
                board[best] = COMPUTER;
                printf("Computer plays at %d\n", best+1);
            }
        }

        char winner = checkWinner();
        if (winner != EMPTY) {
            printBoard();
            if (winner == PLAYER) puts("You WIN! 🎉");
            else puts("Computer WINS. 😬");
            break;
        }
        if (!movesLeft()) {
            printBoard();
            puts("DRAW.");
            break;
        }

        turn = (turn == PLAYER) ? COMPUTER : PLAYER;
    }

    return 0;
}

