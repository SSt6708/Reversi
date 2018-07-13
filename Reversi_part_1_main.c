#include <stdio.h>
#include <stdbool.h>
void printBoard(char board[][26],int n);
bool checkLegalInDirection(char board[][26], int n, char row, char col, char color, int deltaRow, int deltaCol);
bool positionInBounds(int n, char row, char col);
char opponentColor(char color);
bool everyDirection(char board[][26], int n, char row, char col, char color);
void flip(char board[][26], char row, char col, char color, int deltaRow, int deltaCol);
void move(char board[][26], int n, char row, char col, char color);

int main(int argc, char **argv)
{
    int size, row, col;
    char board[26][26];
    char player;
    printf("Enter the board dimension: ");
    scanf("%d",&size);
    for(row = 0; row < size; row++){
        for (col = 0; col < size; col++){
            board[row][col]='U';
        }
    }
    int topleftRow = ((size/2) - 1);
    int topleftCol = ((size/2) - 1);
    board[topleftRow][topleftCol] = 'W';
    int toprightRow = ((size/2)-1);
    int toprightCol = ((size/2));
    board[toprightRow][toprightCol] = 'B';
    board[topleftRow+1][topleftCol] = 'B';
    board[topleftRow+1][toprightCol] = 'W';
    printBoard( board, size);

    printf("Enter board configuration:\n");
    scanf(" %c%c%c", &player, &row, &col);
    while(player !='!'){
        board[row-'a'][col-'a']= player;
        scanf(" %c%c%c", &player, &row, &col);
    }
    printBoard( board, size);
    printf("Available moves for W:\n");
    for(row=0; row < size; row++){
        for(col=0; col < size; col++){
            if(board[row][col]=='U'){
                if(everyDirection( board, size, 'a'+row, 'a'+col, 'W'))
                    printf("%c%c\n",'a'+row, 'a'+col);
            }
        }
    }
    printf("Available moves for B:\n");
    for(row=0; row < size; row++){
        for(col=0; col < size; col++){
            if(board[row][col]=='U'){
                if(everyDirection( board, size, 'a'+row, 'a'+col, 'B'))
                    printf("%c%c\n",'a'+row,'a'+col);
            }
        }
    }

    printf("Enter a move:\n");
    scanf(" %c%c%c", &player, &row, &col);

    if(board[row-'a'][col-'a']=='U'){
        //if empty:
        if(everyDirection( board, size, row, col, player)){
            //make a move
            printf("Valid move.\n");
            move(board, size, row, col, player);
        }
        else
            printf("Invalid move.\n");
    }
    else
        printf("Invalid move.\n");

    //print board after move is made
    printBoard(board, size);

    return 0;
}

void printBoard(char board[][26],int n){
    int col, row;
    printf("  ");
    for(col=0; col < n; col++){
        printf("%c",'a'+col);
    }
    printf("\n");
    for(row=0; row < n; row++){
        printf("%c",'a'+row);
        printf(" ");
        for(col=0; col < n; col++){
            printf("%c", board[row][col]);
        }
        printf("\n");
    }
}

bool checkLegalInDirection(char board[][26], int n, char row, char col, char color, int deltaRow, int deltaCol){
    int r=(row-'a')+deltaRow;
    int c=(col-'a')+deltaCol;
    if (board[r][c] != opponentColor(color))
        return false;
    r=r+deltaRow;
    c=c+deltaCol;
    while(positionInBounds(n,r+'a',c+'a')){
        if(board[r][c] != opponentColor(color)){
            if (board[r][c]=='U'){
                return false;
            }
            else{
                return true;
            }

        }
        else{
            r = r +deltaRow;
            c = c +deltaCol;
        }

    }
    return false;
}

bool positionInBounds(int n, char row, char col){
    bool valid = false;
    if(row - 'a' < 0 || row-'a'> n-1 || col - 'a' < 0 || col - 'a' > n-1 )
        valid = false;
    else
        valid = true;
    return valid;

}

char opponentColor(char color){
    if( color == 'W')
        return 'B';
    else
        return 'W';
}

bool everyDirection(char board[][26], int n, char row, char col, char color){
    if(checkLegalInDirection(board, n, row, col, color, -1,-1)||
        checkLegalInDirection(board, n, row, col, color, -1,0)||
        checkLegalInDirection(board, n, row, col, color, -1,1)||
        checkLegalInDirection(board, n, row, col, color, 1,-1)||
        checkLegalInDirection(board, n, row, col, color, 1,0)||
        checkLegalInDirection(board, n, row, col, color, 1,1)||
        checkLegalInDirection(board, n, row, col, color, 0,-1)||
        checkLegalInDirection(board, n, row, col, color, 0,1)
        )
            return true;
    else
        return false;
}

void flip(char board[][26], char row, char col, char color, int deltaRow, int deltaCol){
    int r = row-'a';
    int c = col-'a';
    //loop through all pieces in the direction and change to current color as long as it's
    //the opponent's color
    while (board[r][c]!=color){
        board[r][c] = color;
        r= r+deltaRow;
        c= c+deltaCol;
    }
}

void move(char board[][26], int n, char row, char col, char color){
    //check al 8 directions, if the direction is valid, flip
    if (checkLegalInDirection(board, n, row, col,color, -1, -1))
        flip(board, row, col, color, -1, -1);
    if (checkLegalInDirection(board, n, row, col,color, -1, 0))
        flip(board, row, col, color, -1, 0);
    if (checkLegalInDirection(board, n, row, col,color, -1, 1))
        flip(board, row, col, color, -1, 1);
    if (checkLegalInDirection(board, n, row, col,color, 1, -1))
        flip(board, row, col, color, 1, -1);
    if (checkLegalInDirection(board, n, row, col,color, 1, 0))
        flip(board, row, col, color, 1, 0);
    if (checkLegalInDirection(board, n, row, col,color, 1, 1))
        flip(board, row, col, color, 1, 1);
    if (checkLegalInDirection(board, n, row, col,color, 0, -1))
        flip(board, row, col, color, 0, -1);
    if (checkLegalInDirection(board, n, row, col,color, 0, 1))
        flip(board, row, col, color, 0, 1);

    //place piece on spot
    board[row-'a'][col-'a'] = color;
}
