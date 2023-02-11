#include <iostream>
#include <cstdio>
using namespace std;

int board[4][4];
int boardcheck[4][4];

void CheckAppearNumber(){
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if (board[i][j] != 0) boardcheck[i][j] = 1;
}

bool CheckUp(int i, int j){
    if ((boardcheck[i][j] == 1 && boardcheck[i-1][j] == 1 && boardcheck[i-2][j] == 1 && boardcheck[i-3][j] == 1) ||
        (boardcheck[i-3][j] == 1 && boardcheck[i-2][j] == 1 && boardcheck[i-1][j] == 1 && boardcheck[i][j] == 0) ||
        (boardcheck[i-3][j] == 1 && boardcheck[i-2][j] == 1 && boardcheck[i-1][j] == 0 && boardcheck[i][j] == 0) ||
        (boardcheck[i-3][j] == 1 && boardcheck[i-2][j] == 0 && boardcheck[i-1][j] == 0 && boardcheck[i][j] == 0)) return true;
    return false;
}

void PushAllElementOnTop(int i, int j){
    if ((i == 0) || (CheckUp(3, j)))return;
    else
    {
        if (boardcheck[i][j] == 0) return PushAllElementOnTop(i-1, j);
        if (boardcheck[i][j] != 0){
            for(int k = i; k >= 1; k--){
                if (boardcheck[k-1][j] == 0){
                    board[k-1][j] = board[k][j];
                    boardcheck[k-1][j] = 1;
                    board[k][j] = 0;
                    boardcheck[k][j] = 0;
                }
                else{
                    PushAllElementOnTop(k-1, j);
                    if (boardcheck[k-1][j] == 0){
                        board[k-1][j] = board[k][j];
                        boardcheck[k-1][j] = 1;
                        board[k][j] = 0;
                        boardcheck[k][j] = 0;
                    }
                }
            }
        }
    }
}

void UpProcess(){
    for (int j = 0; j < 4; j++) {
        PushAllElementOnTop(3, j);
    }
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++){
            if (board[i][j] == board[i+1][j]){
                board[i][j] += board[i+1][j];
                board[i+1][j] = 0;
                boardcheck[i+1][j] = 0;
                i++;
            }
        }
    }
    for (int j = 0; j < 4; j++) {
        PushAllElementOnTop(3, j);
    }
}

void show(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
}

int main() {
    freopen("2048.inp", "r", stdin);
    freopen("2048.out", "w", stdout);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            boardcheck[i][j] = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j ++)
                cin >> board[i][j];
    CheckAppearNumber();
    UpProcess();
    show();
    return 0;
}
