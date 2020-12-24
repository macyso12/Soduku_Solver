//  Sudoku Solver


#include <iostream>
#include <vector>
//#include <ncurses.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>

using namespace std;

void Print(int arr[9][9]){
    cout << "----------------------------------" << endl ;
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            cout << arr[i][j] << " "  ;
        }
        cout << endl ;
    }
    cout << "----------------------------------" << endl ;
}

bool canPlace (int arr[9][9], int row, int col, int n){
    if (arr[row][col]!=0){
        return false;
    }
    bool status = true ;
    int gridx = (col/3) * 3;
    int gridy = (row/3) * 3;
    for (int i = 0; i < 9; i++){
        if (arr[row][i] == n){
            status = false;
            break;
        }
        if (arr[i][col] == n){
            status = false;
            break;
        }
        if (arr[gridy + i / 3][gridx + i % 3] == n){
            status = false;
            break;
        }
    }
    return status;
}

vector <int> findPlacebles (int arr[9][9], int r, int c){
    vector <int> cps;      // Error
    for (int i = 0; i < 9; i++){
        if (canPlace(arr,r, c, i)){
            cps.push_back(i);
        }
    }
    return cps;
}

void copyArray(int arr[9][9], int arrCpy[9][9]){
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            arrCpy[i][j] = arr [i][j];
        }
    }
}

void nextEmpty(int arr[9][9], int row, int col, int &nRow, int &nCol){
    int index = 9 * 9;
    for (int i = row * 9 + col + 1; i < 9*9; i++){
        if (arr[i / 9][ i % 9] == 0){
            index = i;
            break;
        }
    }
    nRow = index / 9;
    nCol = index % 9;
}

bool solveSoduku(int arr[9][9], int row, int col){
    system("clear");
    
    if (row > 8){
        return true;
    }
    
    if (arr[row][col] != 0){
        int nexCol, nexRow;
        nextEmpty(arr, row, col, nexRow, nexCol);
        
        return solveSoduku(arr, nexRow, nexCol);
    }
    
    vector <int> placeables = findPlacebles(arr, row, col);
    
    if (placeables.size() == 0){
        return false;
    }
    bool status = false ;
    for (int i = 0; i < placeables.size(); i++){
        int n = placeables[i];
        int arrCpy[9][9];
        copyArray(arr,arrCpy);
        arrCpy [row][col] = n;
        int nexCol, nexRow;
        nextEmpty(arrCpy, row, col, nexRow, nexCol);
        
        if(solveSoduku(arrCpy, nexRow, nexCol)){
            copyArray(arrCpy, arr);
            status = true;
            break;
        }
    }
    
    return status;
}

int main() {

    int board[9][9] = {
        {5,3,0,0,7,0,0,0,0},
        {6,0,0,1,9,5,0,0,0},
        {0,9,8,0,0,0,0,6,0},
        {8,0,0,0,6,0,0,0,3},
        {4,0,0,8,0,3,0,0,1},
        {7,0,0,0,2,0,0,0,6},
        {0,6,0,0,0,0,2,8,0},
        {0,0,0,4,1,9,0,0,5},
        {0,0,0,0,8,0,0,7,9}
    };
    
    Print(board);
    solveSoduku(board, 0, 0);
    
    Print(board);
    
    return 0;
}
