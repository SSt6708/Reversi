#include <stdio.h>
#include <stdbool.h>


void printBoard(char board[][26], int n) //initializes board;  
{
    int i, j; 
    printf("  ");
   for (i=0; i<n; i++) 
        printf("%c",97+i); 
        printf("\n");
    
   for (i=0; i<n; i++){
       for(j=0; j<n; j++)
         board[i][j]='.';
   } 
   board[n/2][n/2]='B'; 
   board[n/2-1][n/2-1]='B'; 
   board[n/2-1][n/2]='W';
   board[n/2][n/2-1]='W';
   for (i=0; i<n; i++){
       printf("%c ",97+i);
       for(j=0; j<n; j++){
           printf("%c",board[i][j]);
       }
       printf("\n"); 
   }
} 
void Board(char board[][26], int n){ 
    int i,j;
    printf("  ");
   for (i=0; i<n; i++) 
        printf("%c",97+i); 
        printf("\n");
    for (i=0; i<n; i++){
       printf("%c ",97+i);
    for(j=0; j<n; j++){
           printf("%c",board[i][j]); 
        }
            printf("\n");
        }
    } 
void temp(char temp[][26], int n){ 
    int i,j;
    printf("  ");
   for (i=0; i<n; i++) 
        printf("%c",97+i); 
        printf("\n");
    for (i=0; i<n; i++){
       printf("%c ",97+i);
    for(j=0; j<n; j++){
           printf("%c",temp[i][j]); 
        }
            printf("\n");
        } 
        
    } 
    
void tempBoard(char temp[][26], char board[][26], int n){ 
    int i,j;
    for(i=0; i<n; i++){ 
        for(j=0; j<n; j++){  
            temp[i][j]=board[i][j]; 
        }
    }
}

void TestBoard(int scoreboard[][26], int n){ 
    int i,j;
    printf("  ");
   for (i=0; i<n; i++) 
        printf("%c",97+i); 
        printf("\n");
    for (i=0; i<n; i++){
       printf("%c ",97+i);
    for(j=0; j<n; j++){
           printf("%d",scoreboard[i][j]); 
        }
            printf("\n");
        }
    }
bool positionInBounds(int n, char row, char col)//check if the row and column is within the dimension 
{ 
int k, o; 
k=row-97; 
o=col-97; 
if(k>=0 && k<n && o>=0 && o<n) 
return true; 
else 
    return false;
}

char opposite(char color){
    if( color == 'W')
        return 'B';
    else
        return 'W';
}

bool checkLegalInDirection(char board[][26], int n, char row, char col, char color, int deltaRow, int deltaCol){
    int r=(row-'a')+deltaRow;
    int c=(col-'a')+deltaCol;
    if (board[r][c] != opposite(color))
        return false;
    r=r+deltaRow;
    c=c+deltaCol;
    while(positionInBounds(n,r+'a',c+'a')){
        if(board[r][c] != opposite(color)){
            if (board[r][c]=='.'){
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
bool checkDirection(char board[][26], int n, char row, char col, char color){
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



  
void SwapMove(char board[][26], char row, char col, char color, int deltaRow, int deltaCol){
    int i= row-'a';
    int j= col-'a'; 
    //loop through all pieces in the direction and change to current color as long as it's
    //the opponent's color
    while (board[i+deltaRow][j+deltaCol]!=color){
        board[i+deltaRow][j+deltaCol] = color;
        i= i+deltaRow;
        j= j+deltaCol; 
        
    } 
    
} 

void move(char board[][26], int n, char row, char col, char color){
    board[row-'a'][col-'a']=color;
    //check al 8 directions, if the direction is valid, flip
    if (checkLegalInDirection(board, n, row, col,color, -1, -1))
        SwapMove(board, row, col, color, -1, -1);
    if (checkLegalInDirection(board, n, row, col,color, -1, 0))
        SwapMove(board, row, col, color, -1, 0);
    if (checkLegalInDirection(board, n, row, col,color, -1, 1))
        SwapMove(board, row, col, color, -1, 1);
    if (checkLegalInDirection(board, n, row, col,color, 1, -1))
        SwapMove(board, row, col, color, 1, -1);
    if (checkLegalInDirection(board, n, row, col,color, 1, 0))
        SwapMove(board, row, col, color, 1, 0);
    if (checkLegalInDirection(board, n, row, col,color, 1, 1))
        SwapMove(board, row, col, color, 1, 1);
    if (checkLegalInDirection(board, n, row, col,color, 0, 1))
        SwapMove(board, row, col, color, 0, 1);
    if (checkLegalInDirection(board, n, row, col,color, 0, -1))
        SwapMove(board, row, col, color, 0, -1);

    //place piece on spot
    
}     
int OppositeMoves(char board[][26], int n, int i, int j, char color){  
    
	char temp[26][26];
	tempBoard(temp, board, n);
    int score=0;
				if(checkDirection(temp, n, 'a'+i, 'a'+j, color)){
                move(temp, n, 'a'+i, 'a'+j, color);
                 
                for(i=0; i<n; i++){ 
                    for(j=0; j<n; j++){ 
                        if(temp[i][j]=='.'){
                            if(checkDirection(temp, n, 'a'+i, 'a'+j, opposite(color))) 
                            score++; 
                        }
                    }
                } 
    return score; 
		}
}



void Scoreboard( int scoreboard[][26], char board[][26], int n, char color){ 
      int i, j;  
    for (i=0; i<n; i++){ 
            for(j=0; j<n; j++){ 
                if (board[i][j]=='.' && checkDirection(board, n, 'a'+i, 'a'+j, color) && positionInBounds( n, 'a'+i, 'a'+j)){
                 
                if ((i==0&&j==0)|| (i==0&&j==n-1) || (i==n&&j==n) || (i==n-1&&j==0))
                scoreboard[i][j]= -10+OppositeMoves(board, n, i, j, color);  
				
				else if((i==1&&j==1)|| (i==0&&j==1) || (i==1&&j==0) || 
						(i==0&&j==n-2)|| (i==1&&j==n-2) || (i==1&&j==n-1) ||
						(i==n-2&&j==0)|| (i==n-2&&j==1) || (i==n-1&&j==1) || 
						(i==n-2&&j==n-2)|| (i==n-2&&j==n-1) || (i==n-1&&j==n-2))
				
					scoreboard[i][j]= 10+OppositeMoves(board, n, i, j, color);
					
					else
					scoreboard[i][j]= OppositeMoves(board, n, i, j, color);	
					
                }
                else 
                    scoreboard[i][j]=20;
                } 
            }
        } 

            
void ComputerMove(int scoreboard[][26], char board[][26], int n, char color){ 
    int i, j, row, col, min=1000; 
     
    for (i=0; i<n; i++){
        for (j=0; j<n; j++){ 
            if (board[i][j]=='.'){ 
                Scoreboard( scoreboard, board, n, color);
                if (scoreboard[i][j] < min){ 
                 min=scoreboard[i][j];
                 row=i; 
                 col=j; 
                } 
            }
        }
       
    } 
    move(board, n, 'a'+row, 'a'+col, color); 
    printf("Computer places %c at %c%c.\n", color, 'a'+row, 'a'+col); 
     
    
}  

    

bool checkMove(char board[][26], int n, char color){ 
int i, j, value=0;
    for (i=n-1; i>=0; i--){
        for (j=n-1; j>=0; j--){ 
            if (board[i][j]== '.'){ 
                if(!checkDirection(board, n, 'a'+i, 'a'+j, color))
                    value+=0;  
                    else 
                        value++; 
            }
        }
    } 
            if(value==0) 
                return  true; 
            else 
                return false; 
}

bool gameover(char board[][26], int n){
    if(checkMove(board, n, 'W') && checkMove(board, n, 'B')) 
        return true; 
        else 
            return false; 
}

void finalBoard( char board[][26], int n){ 
    int i, j, cnt1=0, cnt2=0; 
    for (i=0; i<n; i++){ 
        for (j=0; j<n; j++){ 
            if (board[i][j]=='W') 
            cnt1++; 
            else if (board[i][j]=='B') 
                cnt2++; 
        }
    } 
   
    if(cnt1>cnt2) 
        printf("W player wins.\n"); 
        else if(cnt2>cnt1) 
            printf("B player wins. \n"); 
            else 
                printf("Draw! \n"); 
}

int main(void){

    char board[26][26], player, row, col, turn='B',me;
    int n, i, j, rows = 0, cols = 0; 
    int scoreboard[26][26];
	printf("Enter the board dimension: ");
    scanf("%d", &n); 
    printf("Computer plays (B/W) : "); 
    scanf(" %c", &player); 
    printBoard(board, n);  
    
    if(player=='B') 
        me='W'; 
        else 
            me='B'; 

    while(!gameover(board, n)){ 
        if(turn==player){ 
            if(checkMove(board, n, player)){ 
                printf("%c player has no valid move.\n", player);
                turn=opposite(player); 
            } 
            else{ 
                
            ComputerMove(scoreboard, board, n, player);
            
			Board(board, n); 
            
            turn=opposite(player);
            }   
        }
        else if(player!=turn){ 
            if(checkMove(board, n, me)){ 
                printf("%c player has no valid move.\n", me);
                turn=opposite(me); 
            }
             else   {
            printf("Enter move for colour %c (RowCol): ", me); 
            scanf(" %c%c",&row, &col );
            
			if(board[row-'a'][col-'a']=='.'){
				if(checkDirection( board, n, row, col, me)){
					move(board, n, row, col, me);  
					Board(board,n);
            }
            else{
            printf("Invalid move.\n");
            printf("%c player wins.\n",opposite(me));
                return 0; 
                }
            }
            else{
                printf("Invalid move.\n");
                printf("%c player wins.\n",opposite(me));
                return 0;
            } 
            
            turn=opposite(me);
            }  
        } 
    }
    
    
    finalBoard( board, n);
     
     
    
    
	return 0;
}
