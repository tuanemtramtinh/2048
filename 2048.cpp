#include <iostream>

using namespace std;

int board[4][4] = {{2, 0, 2, 2},
                   {0, 2, 0, 0},
                   {0, 2, 2, 2},
                   {0, 2, 0, 2}};
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
    (boardcheck[i-3][j] == 1 && boardcheck[i-2][j] == 0 && boardcheck[i-1][j] == 0 && boardcheck[i][j] == 0) ||
    (boardcheck[i-3][j] == 0 && boardcheck[i-2][j] == 1 && boardcheck[i-1][j] == 1 && boardcheck[i][j] == 0)) return true;
    return false;
}

bool CheckSimilarUp(int i, int j){
    for(int i = 3; i>=0; i--)
        if (board[i][j] == board[i-1][j] && board[i][j] != 0) return false;
    return true;
}

void PushAllElementOnTop(int i, int j){
    if (i == 0) return;
    else
    {
        if (boardcheck[i][j] == 0) return PushAllElementOnTop(i-1, j);
        if (boardcheck[i][j] != 0){
            for(int k = i; k >= 0; k--){
                if (boardcheck[i-1][j] == 0){
                    board[i-1][j] = board[i][j];
                    boardcheck[i-1][j] = 1;
                    board[i][j] = 0;
                    boardcheck[i][j] = 0;
                }
                else{
                    PushAllElementOnTop(i-1, j);
                    if (boardcheck[i-1][j] == 0){
                        board[i-1][j] = board[i][j];
                        boardcheck[i-1][j] = 1;
                        board[i][j] = 0;
                        boardcheck[i][j] = 0;
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
    /*for(int j = 0; j < 4; j++){
        int i = 3;
        while((CheckSimilarUp(3,j) == false)) {
            if (board[i][j] == board[i - 1][j]) {
                board[i - 1][j] += board[i][j];
                board[i][j] = 0;
                boardcheck[i][j] = 0;
            }
            i--;
            if (i == 0){
                PushAllElementOnTop(3,j);
                i = 3;
            }
        }
    }*/
}



void show(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
}
int main() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            boardcheck[i][j] = 0;
    CheckAppearNumber();
    UpProcess();
    cout << "The Matrix at first: " << endl;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j ++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << "The Matrix after go up: " << endl;
    show();
    return 0;
}
