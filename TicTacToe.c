#include <stdio.h>

/*
    GAME LOGIC FUNCTIONS
*/
int nValidateMove();
int nCheckWinner();
int nPlayer();
int *nAskInput();
void move();
void printBoard();
void gameResult();
//build printing abilities and asking for input and storing choices
/*
    SPECIAL ABILITIES FUNCTIONS
*/
void extraTurn();

void main() 
{
    int nIndex1 = 0, nIndex2 = 0, nRow = 0, nCol = 0, i = 0;
    int *n = NULL;
 
    char cBoard [5][5] = {
                {'_', '_', '_', '_', '_'},
                {'_', '_', '_', '_', '_'},
                {'_', '_', '_', '_', '_'},
                {'_', '_', '_', '_', '_'},  
                {' ', ' ', ' ', ' ', ' '},
                        };

    /*Run game*/
    for (; i < 25 && !nCheckWinner(cBoard); i++)
    {
        printBoard(cBoard);

        do
        {
            /*set cBoard indices from input*/
            n = nAskInput(nPlayer(i));
            nRow = n[0]; /*WHy do I need to do this?*/
            nCol = n[1];
            nIndex1 = --n[0];
            nIndex2 = --n[1];
        
        /*validate move*/
        } while (!nValidateMove(nRow, nCol, cBoard[nIndex1][nIndex2]));
        
        move(nIndex1, nIndex2, nPlayer(i), cBoard);

    }

    gameResult(nPlayer(i-1), nCheckWinner(cBoard));
    printBoard(cBoard);
    printf("\n");

}
/*
    GAME LOGIC FUNCTIONS' DEFINITIONS
*/
/* function to ask the player for input and return the indices of the board*/
int *nAskInput(int nPlayer)
{
    int nCol = 0, nRow = 0;
    int nIdx[2];

        printf("\n");
        printf("Player %d, please choose a square to place your %c by selecting the column first \n"
                "and then the row (e.g. 1 5 for the bottom left square).\n", nPlayer, (nPlayer == 1) ? 'X' : 'O');
        printf("Column (1-5): ");
        scanf("%d", &nIdx[1]);
        printf("Row (1-5): ");
        scanf("%d", &nIdx[0]);

    return nIdx;

}

/* prints the board */
void printBoard(char cBoard[5][5])
{
    printf("\n");
    printf("  1|2|3|4|5\n");
    printf("1:%c|%c|%c|%c|%c\n",cBoard[0][0],cBoard[0][1],cBoard[0][2],cBoard[0][3],cBoard[0][4]);
    printf("2:%c|%c|%c|%c|%c\n",cBoard[1][0],cBoard[1][1],cBoard[1][2],cBoard[1][3],cBoard[1][4]);
    printf("3:%c|%c|%c|%c|%c\n",cBoard[2][0],cBoard[2][1],cBoard[2][2],cBoard[2][3],cBoard[2][4]);
    printf("4:%c|%c|%c|%c|%c\n",cBoard[3][0],cBoard[3][1],cBoard[3][2],cBoard[3][3],cBoard[3][4]);
    printf("5:%c|%c|%c|%c|%c\n",cBoard[4][0],cBoard[4][1],cBoard[4][2],cBoard[4][3],cBoard[4][4]);
}

/* returns the player number */
int nPlayer(int i)
{
    return i%2 + 1;
}

/* assign's the player character to the correct board index */
void move(int nIndex1, int nIndex2, int nPlayer, char cBoard[5][5]) //is this needed?
{
    cBoard[nIndex1][nIndex2] = (nPlayer == 1) ? 'X' : 'O';
}

/* checks the board after each mve to determine if there is a winner */
int nCheckWinner(char cBoard[5][5])
{
    int nWinner = 0, j = 0;

    if((cBoard[0][0]==cBoard[1][1] 
        && cBoard[0][0]==cBoard[2][2] 
        && cBoard[0][0]==cBoard[3][3] 
        && cBoard[0][0]==cBoard[4][4]) 
        || (cBoard[0][4]==cBoard[1][3] 
        && cBoard[0][4]==cBoard[2][2] 
        && cBoard[0][4]==cBoard[3][1] 
        && cBoard[0][4]==cBoard[4][0])) /*Diagonal*/
        nWinner++;
    else
        for(j = 0; j <= 4; j++)  //need to set j = 0 in for-loop condition
            if((cBoard[j][0]==cBoard[j][1] 
                && cBoard[j][0]==cBoard[j][2]
                && cBoard[j][0]==cBoard[j][3] 
                && cBoard[j][0]==cBoard[j][4]
                && (cBoard[j][0]=='X' || cBoard[j][0]=='O')) /*Horizontal*/
                || (cBoard[0][j]==cBoard[1][j] 
                && cBoard[0][j]==cBoard[2][j]
                && cBoard[0][j]==cBoard[3][j] 
                && cBoard[0][j]==cBoard[4][j]
                && (cBoard[0][j]=='X' || cBoard[0][j]=='O'))) /*Vertical*/                
                nWinner++;

    return nWinner;
}

/* validates each set if inputs from the player */
int nValidateMove(int nRow,int nCol,int nBoardIndex)
{
    int nValid = 0;

    nValid = (nRow > 0 && nRow < 6) 
            && (nCol > 0 && nCol < 6) 
            && (nBoardIndex != 'X' && nBoardIndex != 'O');

    return nValid;
}

/* print the results of the game */
void gameResult(int nPlayer, int nCheckWinner)
{
    printf("\n");

    if (nCheckWinner)
    {
        printf("%c Wins! ", (nPlayer == 1) ? 'X' : 'O');
        printf("Good job Player %d!\n", nPlayer);
    }
    else
        printf("Its a draw!\n");
}

void printAbilities()
{
    printf("You may choose from the following special abilities for the game:\n"
            "1. Extra Turn\n"
            "2. Steal\n"
            "3. Clean Corners\n"
            "4. Row Wipe\n"
            "5. Lady's Choice\n"
            "6. Even It Out\n"
            "7. Missed Chance\n"
            "8. Block\n");
}
/*
    SPECIAL ABILITIES FUNCTIONS' DEFINITIONS
*/
void extraTurn()
{

}