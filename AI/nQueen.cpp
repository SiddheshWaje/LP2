#include <bits/stdc++.h>
using namespace std;
#define n 4
void PrintBoard(int board[n][n])
{

    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
            if(board[row][col] == 0) {
                cout<<'.';
            }
            else{
                cout<<'Q';
            }
        cout << endl;
    }
    cout << endl;
}

bool isSafe(int arr[n][n], int x, int y)
{

    for(int row=0;row<x;row++){
        if(arr[row][y]==1){
            return false;
        }
    }
    int row =x;
    int col =y;
    while(row>=0 && col>=0){
        if(arr[row][col]==1){
            return false;
        }
        row--;
        col--;
    }
    row=x;
    col=y;
    while(row>=0 && col<n){
        if(arr[row][col]==1){
            return false;
        }
        row--;
        col++;
    }
    return true;
}

bool nQueenUtil(int board[n][n], int row)
{

    if (row == n)
    {
        PrintBoard(board);
        // not returning true here
    }
    for (int col = 0; col < n; col++)
    {
        if (isSafe(board, row, col))
        {

            board[row][col] = 1;

            if (nQueenUtil(board, row + 1))
            {

                return true;
            }
            board[row][col] = 0;
        }
    }
    return false;
}
int main()
{
    cout << "For " << n << " * " << n << " matrix : \n";

    int board[n][n] = {0};

    nQueenUtil(board, 0);
    return 0;
}