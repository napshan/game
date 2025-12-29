#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>

#define BOARD_SIZE 4    // 棋盤大小
#define TARGET_VALUE 2048 // 遊戲目標值

int board1[BOARD_SIZE][BOARD_SIZE];
int board2[BOARD_SIZE][BOARD_SIZE];
int score1, score2, gamew1, gamew2, move1, move2;

// 遊戲規則函數
void explanation() {
    system("cls");
    printf("\t\t*****************************************\n");
    printf("\t\t****************** 遊戲規則 ***************\n");
    printf("\t\t*****************************************\n");
    printf("玩家1使用 W、A、S、D 控制滑塊移動\n");
    printf("玩家2使用 上、下、左、右 控制滑塊移動\n");
    printf("相同的數字在選擇的方向上會合併\n");
    printf("每步移動後，空白格隨機生成一個 2 或 4\n");
    printf("棋盤被填滿且無法移動時，遊戲結束\n");
    printf("棋盤上出現 %d 時，玩家勝利\n", TARGET_VALUE);
    printf("請按任意鍵返回主選單...\n");
    getch();
    system("cls");
}

// 在空白處生成新數字
void generateNewNumber(int board[BOARD_SIZE][BOARD_SIZE]) {
    int emptySpaces[BOARD_SIZE * BOARD_SIZE];
    int count = 0;

    for (int j = 0; j < BOARD_SIZE; j++) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            if (board[j][i] == 0) {
                emptySpaces[count++] = j * BOARD_SIZE + i;
            }
        }
    }

    if (count > 0) {
        int index = rand() % count;
        int pos = emptySpaces[index];
        board[pos / BOARD_SIZE][pos % BOARD_SIZE] = (rand() % 10 < 9) ? 2 : 4;
    }
}

// 移動與合併邏輯
int addAndMerge(int *line, int *score, int *gamew) {
    int merged[BOARD_SIZE] = { 0 };
    int moved = 0;

    for (int i = 1; i < BOARD_SIZE; i++) {
        if (line[i] != 0) {
            int j = i;
            while (j > 0 && line[j - 1] == 0) {
                line[j - 1] = line[j];
                line[j] = 0;
                j--;
                moved = 1; // 發生移動
            }
            if (j > 0 && line[j - 1] == line[j] && !merged[j - 1]) {
                line[j - 1] *= 2;
                *score += line[j - 1];
                line[j] = 0;
                merged[j - 1] = 1;
                moved = 1; // 發生合併
                if (line[j - 1] == TARGET_VALUE) *gamew = 1;
            }
        }
    }
    return moved;
}

// 處理方向鍵
int processMove(char direction, int board[BOARD_SIZE][BOARD_SIZE], int *score, int *gamew) {
    int moved = 0;

    for (int i = 0; i < BOARD_SIZE; i++) {
        int line[BOARD_SIZE];
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (direction == 'w') line[j] = board[j][i];
            if (direction == 's') line[j] = board[BOARD_SIZE - j - 1][i];
            if (direction == 'a') line[j] = board[i][j];
            if (direction == 'd') line[j] = board[i][BOARD_SIZE - j - 1];
        }

        moved |= addAndMerge(line, score, gamew); // 如果有移動，moved 設為 1

        for (int j = 0; j < BOARD_SIZE; j++) {
            if (direction == 'w') board[j][i] = line[j];
            if (direction == 's') board[BOARD_SIZE - j - 1][i] = line[j];
            if (direction == 'a') board[i][j] = line[j];
            if (direction == 'd') board[i][BOARD_SIZE - j - 1] = line[j];
        }
    }
    return moved;
}

// 遊戲主邏輯
void gameplay() {
    generateNewNumber(board1);
    generateNewNumber(board1);
    generateNewNumber(board2);
    generateNewNumber(board2);

    char key;

    while (1) {
        system("cls");
        // 顯示棋盤
        printf("玩家1分數: %d 步數: %d\n", score1, move1);
        for (int j = 0; j < BOARD_SIZE; j++) {
            for (int i = 0; i < BOARD_SIZE; i++) {
                if (board1[j][i] == 0)
                    printf("|    ");
                else
                    printf("|%4d", board1[j][i]);
            }
            printf("|\n");
        }

        printf("\n玩家2分數: %d 步數: %d\n", score2, move2);
        for (int j = 0; j < BOARD_SIZE; j++) {
            for (int i = 0; i < BOARD_SIZE; i++) {
                if (board2[j][i] == 0)
                    printf("|    ");
                else
                    printf("|%4d", board2[j][i]);
            }
            printf("|\n");
        }

        key = getch();

        int moved1 = 0, moved2 = 0;

        // 玩家1按鍵
        if (key == 'w' || key == 'W') moved1 = processMove('w', board1, &score1, &gamew1);
        if (key == 's' || key == 'S') moved1 = processMove('s', board1, &score1, &gamew1);
        if (key == 'a' || key == 'A') moved1 = processMove('a', board1, &score1, &gamew1);
        if (key == 'd' || key == 'D') moved1 = processMove('d', board1, &score1, &gamew1);

        // 玩家2按鍵
        if (key == 72) moved2 = processMove('w', board2, &score2, &gamew2); // 上
        if (key == 80) moved2 = processMove('s', board2, &score2, &gamew2); // 下
        if (key == 75) moved2 = processMove('a', board2, &score2, &gamew2); // 左
        if (key == 77) moved2 = processMove('d', board2, &score2, &gamew2); // 右

        // 若有移動，生成新數字
        if (moved1) {
            generateNewNumber(board1);
            move1++;
        }
        if (moved2) {
            generateNewNumber(board2);
            move2++;
        }

        // 判斷勝負
        if (gamew1) {
            printf("玩家1贏了！\n");
            break;
        }
        if (gamew2) {
            printf("玩家2贏了！\n");
            break;
        }
    }
}

// 主選單
void menu() {
    printf("1. 開始遊戲\n2. 規則說明\n3. 退出遊戲\n");
    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            gameplay();
            break;
        case 2:
            explanation();
            break;
        case 3:
            exit(0);
    }
}

// 主函數
int main() {
    srand((unsigned int)time(NULL));
    menu();
    return 0;
}

