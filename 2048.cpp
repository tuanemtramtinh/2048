#include <iostream>
#include <cstdio>
#include <conio.h>
#include <stdio.h>
using namespace std;

int board[4][4] = { {0, 0, 0, 0},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0} };
int boardcheck[4][4];
bool GameOverCheck() {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] != 0) count++;
        }
    }
    if (count == 16) return true;
    return false;
}

void CheckAppearNumber() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (board[i][j] != 0) boardcheck[i][j] = 1;
}

void GenerateRandomNumInArray() {
    bool check = true;
    int x = 0, y = 0;
    while (check) {
        int i = rand() % 4;
        int j = rand() % 4;
        if (board[i][j] == 0 && boardcheck[i][j] == 0) {
            check = false;
            x = i;
            y = j;
        }
    }
    if (check == false) {
        int num = rand() % 100 + 1;
        if (num >= 0 && num <= 90) board[x][y] = 2;
        if (num > 90 && num <= 100) board[x][y] = 4;
    }
}

//Hàm đẩy các phần tử lên trên----------------------------------------------------------------------------------------------------

bool CheckUp(int i, int j) {
    if ((boardcheck[i][j] == 1 && boardcheck[i - 1][j] == 1 && boardcheck[i - 2][j] == 1 && boardcheck[i - 3][j] == 1) ||
        (boardcheck[i - 3][j] == 1 && boardcheck[i - 2][j] == 1 && boardcheck[i - 1][j] == 1 && boardcheck[i][j] == 0) ||
        (boardcheck[i - 3][j] == 1 && boardcheck[i - 2][j] == 1 && boardcheck[i - 1][j] == 0 && boardcheck[i][j] == 0) ||
        (boardcheck[i - 3][j] == 1 && boardcheck[i - 2][j] == 0 && boardcheck[i - 1][j] == 0 && boardcheck[i][j] == 0)) return true;
    return false;
}

void PushAllElementOnTop(int i, int j) {
    if ((i == 0) || (CheckUp(3, j)))return;
    else
    {
        if (boardcheck[i][j] == 0) return PushAllElementOnTop(i - 1, j);
        if (boardcheck[i][j] != 0) {
            for (int k = i; k >= 1; k--) {
                if (boardcheck[k - 1][j] == 0) {
                    board[k - 1][j] = board[k][j];
                    boardcheck[k - 1][j] = 1;
                    board[k][j] = 0;
                    boardcheck[k][j] = 0;
                }
                else {
                    PushAllElementOnTop(k - 1, j);
                    if (boardcheck[k - 1][j] == 0) {
                        board[k - 1][j] = board[k][j];
                        boardcheck[k - 1][j] = 1;
                        board[k][j] = 0;
                        boardcheck[k][j] = 0;
                    }
                }
            }
        }
    }
}

void UpProcess() {
    for (int j = 0; j < 4; j++) {
        PushAllElementOnTop(3, j);
    }
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            if ((board[i][j] == board[i + 1][j]) && (board[i][j] != 0)) {
                board[i][j] += board[i + 1][j];
                board[i + 1][j] = 0;
                boardcheck[i + 1][j] = 0;
                i++;
            }
        }
    }
    for (int j = 0; j < 4; j++) {
        PushAllElementOnTop(3, j);
    }
}

//Hàm đẩy các phần tử đi xuống----------------------------------------------------------------------------------------------------

bool CheckDown(int i, int j) {
    if ((boardcheck[i + 3][j] == 1 && boardcheck[i + 2][j] == 1 && boardcheck[i + 1][j] == 1 && boardcheck[i][j] == 1) ||
        (boardcheck[i + 3][j] == 1 && boardcheck[i + 2][j] == 1 && boardcheck[i + 1][j] == 1 && boardcheck[i][j] == 0) ||
        (boardcheck[i + 3][j] == 1 && boardcheck[i + 2][j] == 1 && boardcheck[i + 1][j] == 0 && boardcheck[i][j] == 0) ||
        (boardcheck[i + 3][j] == 1 && boardcheck[i + 2][j] == 0 && boardcheck[i + 1][j] == 0 && boardcheck[i][j] == 0)) return true;
    return false;
}

void PushAllElementDown(int i, int j) {
    if ((i == 3) || (CheckDown(0, j)))return;
    else
    {
        if (boardcheck[i][j] == 0) return PushAllElementDown(i + 1, j);
        if (boardcheck[i][j] != 0) {
            for (int k = i; k < 3; k++) {
                if (boardcheck[k + 1][j] == 0) {
                    board[k + 1][j] = board[k][j];
                    boardcheck[k + 1][j] = 1;
                    board[k][j] = 0;
                    boardcheck[k][j] = 0;
                }
                else {
                    PushAllElementDown(k + 1, j);
                    if (boardcheck[k + 1][j] == 0) {
                        board[k + 1][j] = board[k][j];
                        boardcheck[k + 1][j] = 1;
                        board[k][j] = 0;
                        boardcheck[k][j] = 0;
                    }
                }
            }
        }
    }
}

void DownProcess() {
    for (int j = 0; j < 4; j++) {
        PushAllElementDown(0, j);
    }
    for (int j = 0; j < 4; j++) {
        for (int i = 3; i >= 1; i--) {
            if ((board[i][j] == board[i - 1][j]) && (board[i][j] != 0)) {
                board[i][j] += board[i - 1][j];
                board[i - 1][j] = 0;
                boardcheck[i - 1][j] = 0;
                i--;
            }
        }
    }
    for (int j = 0; j < 4; j++) {
        PushAllElementDown(0, j);
    }
}

//Hàm đẩy trái----------------------------------------------------------------------------------------------------
bool CheckLeft(int i, int j) {
    if ((boardcheck[i][j - 3] == 1 && boardcheck[i][j - 2] == 1 && boardcheck[i][j - 1] == 1 && boardcheck[i][j] == 1) ||
        (boardcheck[i][j - 3] == 1 && boardcheck[i][j - 2] == 1 && boardcheck[i][j - 1] == 1 && boardcheck[i][j] == 0) ||
        (boardcheck[i][j - 3] == 1 && boardcheck[i][j - 2] == 1 && boardcheck[i][j - 1] == 0 && boardcheck[i][j] == 0) ||
        (boardcheck[i][j - 3] == 1 && boardcheck[i][j - 2] == 0 && boardcheck[i][j - 1] == 0 && boardcheck[i][j] == 0)) return true;
    return false;
}

void PushAllElementLeft(int i, int j) {
    if ((j == 0) || (CheckLeft(i, 3))) return;
    else
    {
        if (boardcheck[i][j] == 0) return PushAllElementLeft(i, j - 1);
        if (boardcheck[i][j] != 0) {
            for (int k = j; k >= 1; k--) {
                if (boardcheck[i][k - 1] == 0) {
                    board[i][k - 1] = board[i][k];
                    boardcheck[i][k - 1] = 1;
                    board[i][k] = 0;
                    boardcheck[i][k] = 0;
                }
                else {
                    PushAllElementLeft(i, j - 1);
                    if (boardcheck[i][k - 1] == 0) {
                        board[i][k - 1] = board[i][k];
                        boardcheck[i][k - 1] = 1;
                        board[i][k] = 0;
                        boardcheck[i][k] = 0;
                    }
                }
            }
        }
    }
}

void LeftProcess() {
    for (int i = 0; i < 4; i++) {
        PushAllElementLeft(i, 3);
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if ((board[i][j] == board[i][j + 1]) && (board[i][j] != 0)) {
                board[i][j + 1] += board[i][j];
                board[i][j] = 0;
                boardcheck[i][j] = 0;
                j++;
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        PushAllElementLeft(i, 3);
    }
}

//Hàm đẩy phải----------------------------------------------------------------------------------------------------
bool CheckRight(int i, int j) {
    if ((boardcheck[i][j + 3] == 1 && boardcheck[i][j + 2] == 1 && boardcheck[i][j + 1] == 1 && boardcheck[i][j] == 1) ||
        (boardcheck[i][j + 3] == 1 && boardcheck[i][j + 2] == 1 && boardcheck[i][j + 1] == 1 && boardcheck[i][j] == 0) ||
        (boardcheck[i][j + 3] == 1 && boardcheck[i][j + 2] == 1 && boardcheck[i][j + 1] == 0 && boardcheck[i][j] == 0) ||
        (boardcheck[i][j + 3] == 1 && boardcheck[i][j + 2] == 0 && boardcheck[i][j + 1] == 0 && boardcheck[i][j] == 0)) return true;
    return false;
}

void PushAllElementRight(int i, int j) {
    if ((j == 3) || (CheckRight(i, 0))) return;
    else
    {
        if (boardcheck[i][j] == 0) return PushAllElementRight(i, j + 1);
        if (boardcheck[i][j] != 0) {
            for (int k = j; k < 3; k++) {
                if (boardcheck[i][k + 1] == 0) {
                    board[i][k + 1] = board[i][k];
                    boardcheck[i][k + 1] = 1;
                    board[i][k] = 0;
                    boardcheck[i][k] = 0;
                }
                else {
                    PushAllElementRight(i, j + 1);
                    if (boardcheck[i][k + 1] == 0) {
                        board[i][k + 1] = board[i][k];
                        boardcheck[i][k + 1] = 1;
                        board[i][k] = 0;
                        boardcheck[i][k] = 0;
                    }
                }
            }
        }
    }
}

void RightProcess() {
    for (int i = 0; i < 4; i++) {
        PushAllElementRight(i, 0);
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 3; j >= 1; j--) {
            if ((board[i][j] == board[i][j - 1]) && (board[i][j] != 0)) {
                board[i][j] += board[i][j - 1];
                board[i][j - 1] = 0;
                boardcheck[i][j - 1] = 0;
                j--;
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        PushAllElementRight(i, 0);
    }
}

//Hàm in ra---------------------------------------------------
void show() {
    system("cls");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
    bool check = false;
    check = GameOverCheck();
    if (check == true) {
        cout << "GAME OVER!!!";
        exit(0);
    }
}

int main() {
    char key;
    bool check = false;
    srand(time(NULL));
    GenerateRandomNumInArray();
    show();
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            boardcheck[i][j] = 0;
    CheckAppearNumber();
    while (true) {
        key = getch();
        if (key == 'q'){
            cout << "Quit Success";
            break;
        }
        if (key == 'w'){
            CheckAppearNumber();
            UpProcess();
            GenerateRandomNumInArray();
            show();
        }
        if (key == 's') {
            CheckAppearNumber();
            DownProcess();
            GenerateRandomNumInArray();
            show();
        }
        if (key == 'a') {
            CheckAppearNumber();
            LeftProcess();
            GenerateRandomNumInArray();
            show();
        }
        if (key == 'd') {
            CheckAppearNumber();
            RightProcess();
            GenerateRandomNumInArray();
            show();
        }
    }
    return 0;
}
