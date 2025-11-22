#include <stdio.h>

char board[3][3];

// 보드 초기화
void initBoard() {
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            board[i][j] = ' ';
}

// 보드 출력
void printBoard() {
    printf("\n");
    for(int i=0;i<3;i++) {
        printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
        if(i < 2) printf("---|---|---\n");
    }
    printf("\n");
}

// 승리 체크
char checkWinner() {
    for(int i=0;i<3;i++) {
        // 가로
        if(board[i][0] != ' ' &&
           board[i][0] == board[i][1] &&
           board[i][1] == board[i][2])
            return board[i][0];

        // 세로
        if(board[0][i] != ' ' &&
           board[0][i] == board[1][i] &&
           board[1][i] == board[2][i])
            return board[0][i];
    }

    // 대각선
    if(board[0][0] != ' ' &&
       board[0][0] == board[1][1] &&
       board[1][1] == board[2][2])
        return board[0][0];

    if(board[0][2] != ' ' &&
       board[0][2] == board[1][1] &&
       board[1][1] == board[2][0])
        return board[0][2];

    return ' '; // 아직 승리 없음
}

// 무승부 체크
int isDraw() {
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(board[i][j] == ' ')
                return 0; // 빈칸 있음 → 진행중
    return 1; // 빈칸 없음 → 무승부
}

int main() {
    int row, col;
    char currentPlayer = 'X';

    initBoard();

    while(1) {
        printBoard();
        printf("Player %c, enter row and col (0~2): ", currentPlayer);
        scanf("%d %d", &row, &col);

        // 입력 검증
        if(row < 0 || row > 2 || col < 0 || col > 2) {
            printf("잘못된 입력이야! 다시 해줘.\n");
            continue;
        }
        if(board[row][col] != ' ') {
            printf("이미 차있어! 다시 골라!\n");
            continue;
        }

        board[row][col] = currentPlayer;

        // 승리 체크
        char winner = checkWinner();
        if(winner != ' ') {
            printBoard();
            printf("Player %c WIN!! 🎉\n", winner);
            break;
        }

        // 무승부 체크
        if(isDraw()) {
            printBoard();
            printf("DRAW 😶\n");
            break;
        }

        // 턴 변경
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    return 0;
}

