#include <stdio.h>

/*are these considered to be global variables? */
const int PLAYERS = 2;
const int CHOICES = 8;
/*
    GAME LOGIC FUNCTIONS
*/
int nValidateMove(int nRow,int nCol,int nBoardIndex);
int nCheckWinner(char cBoard[5][5]);
int nPlayer(int i);
int printAbilities();
void nChooseAbilities(int nAbilities[PLAYERS][CHOICES], int (*numOfChoices)());
void move(int nPlayerMove[2], char cBoard[5][5], char cToken);
void askInput(int nPlayerMove[2], int nPlayer, char cToken);
void printBoard(char cBoard[5][5]);
void gameResult(int nPlayer, int nCheckWinner, char cToken);
void playerAbilities(int nAbilities[PLAYERS][CHOICES], int nPlayer);
/*
    SPECIAL ABILITIES FUNCTIONS
*/
void extraTurn();
void steal(char cBoard[5][5], char cToken);
void cleanCorners(char cBoard[5][5]);
void rowWipe(char cBoard[5][5], char cToken);
void ladysChoice(char cBoard[5][5], char cToken, int (*valid)(int, int, int), void (*print)(char *));
void evenItOut(char cBoard[5][5], char cToken);

void main() 
{
    int i = 0;
    int nAbilities[PLAYERS][CHOICES];
    int nPlayerMove[2];
    char cToken = ' ';
 
    char cBoard [5][5] = {
                {'_', '_', '_', '_', '_'},
                {'_', '_', '_', '_', '_'},
                {'_', '_', '_', '_', '_'},
                {'_', '_', '_', '_', '_'},  
                {' ', ' ', ' ', ' ', ' '},
                        };

    /*Run game*/

    //nChooseAbilities(nAbilities, printAbilities);

    for (; i < 25 && !nCheckWinner(cBoard); i++)
    {
        printBoard(cBoard);
        //playerAbilities(nAbilities, nPlayer(i));
        /*set cToken*/
        cToken = (nPlayer(i) == 1) ? 'X' : 'O';

        if(i == 2)
        {
            ladysChoice(cBoard, cToken, nValidateMove, printBoard);
        }
        do
        {   /*set cBoard indices from input*/
            askInput(nPlayerMove, nPlayer(i), cToken);
        /*validate move*/
        } while (!nValidateMove(nPlayerMove[0], nPlayerMove[1], cBoard[--nPlayerMove[0]][--nPlayerMove[1]]));
        
        move(nPlayerMove, cBoard, cToken);

    }

    gameResult(nPlayer(i-1), nCheckWinner(cBoard), cToken);
    printBoard(cBoard);
    printf("\n");

}
/*
    GAME LOGIC FUNCTIONS' DEFINITIONS
*/
/* function to ask the player for input and return the indices of the board*/
void askInput(int nPlayerMove[2], int nPlayer, char cToken)
{
        printf("\n");
        printf("Player %d, please choose a square to place your %c by selecting the column first \n"
                "and then the row (e.g. 1 5 for the bottom left square).\n", nPlayer, cToken);
        printf("Column (1-5): ");
        scanf("%d", &nPlayerMove[1]);
        printf("Row (1-5): ");
        scanf("%d", &nPlayerMove[0]);
        
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
void move(int nPlayerMove[2], char cBoard[5][5], char cToken)
{
    cBoard[nPlayerMove[0]][nPlayerMove[1]] = cToken;
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

/* validates each set of inputs from the player */
int nValidateMove(int nRow, int nCol, int nBoardIndex)
{
    int nValid = 0;

    nValid = (nRow > 0 && nRow < 6) 
            && (nCol > 0 && nCol < 6) 
            && (nBoardIndex != 'X' && nBoardIndex != 'O');

    return nValid;
}

/* print the results of the game */
void gameResult(int nPlayer, int nCheckWinner, char cToken)
{
    printf("\n");

    if (nCheckWinner)
    {
        printf("%c Wins! ", cToken);
        printf("Good job Player %d!\n", nPlayer);
    }
    else
        printf("Its a draw!\n");
}

int printAbilities()
{
    int nChoices = 0;

    printf("Each player may choose from the following special abilities to use during the game:\n"
            "NOTE: Each ability can only be used once. DO NOT CHOOSE AN ABILITY MULTIPLE TIMES.\n"
            "1. Extra Turn\n"
            "2. Steal\n"
            "3. Clean Corners\n"
            "4. Row Wipe\n"
            "5. Lady's Choice\n"
            "6. Even It Out\n"
            "7. Missed Chance\n"
            "8. Block\n"
            "How many abilities would you like to to be able to use?: ");
    scanf("%d", &nChoices);

    return nChoices;

}

void nChooseAbilities(int nAbilities[PLAYERS][CHOICES], int (*numOfChoices)())
{
    int nNum = numOfChoices(), i = 0, j; 

    for (; i < PLAYERS; i++)
    {
        printf("Player %d\n", (i == 0) ? 1 : 2 );

        for (j = 0; j < nNum; j++)
        {
            if (nNum-j == 1)
                printf("Please choose 1 more ability by entering its number: ");
            else
                printf("Please choose %d more abilities by entering the ability's number: ", nNum-j);
            
            scanf("%d", &nAbilities[i][j]);       
        }

    }
}

void playerAbilities(int nAbilities[PLAYERS][CHOICES], int nPlayer)
{
    for (int i = 0; i < CHOICES && nAbilities[nPlayer][i] != 0; i++)
    {
            printf("%d ", nAbilities[nPlayer][i]);
    }
}
/*  
    SPECIAL ABILITIES FUNCTIONS' DEFINITIONS
*/
void extraTurn()
{

}

void steal(char cBoard[5][5], char cToken)
{
    int nCol = 0, nRow = 0;
    char cOpponent = (cToken == 'X') ? 'O' : 'X';

    printf("Please choose a square to steal from your opponent: \n");
    printf("Column: ");
    scanf("%d", &nCol);
    printf("Row: ");
    scanf("%d", &nRow);

    int nIdx1 = nRow-1, nIdx2 = nCol-1;

    if (cBoard[nIdx1][nIdx2] == cOpponent)
        cBoard[nIdx1][nIdx2] = cToken;
    else
        steal(cBoard, cToken);

}

void cleanCorners(char cBoard[5][5])
{
    char c = '_', x = ' ';

    cBoard[0][0] = c;
    cBoard[0][4] = c;
    cBoard[2][2] = c;
    cBoard[4][0] = x;
    cBoard[4][4] = x;
}

void rowWipe(char cBoard[5][5], char cToken)
{
    int nRow = 0, nCount = 0, i = 0;
    char cOpponent = (cToken == 'X') ? 'O' : 'X';

    printf("Please chose a row where you occupy 2 squares: ");
    scanf("%d", &nRow);
    
    if (nRow < 1 || nRow > 5)
        rowWipe(cBoard, cToken);

    int nIdx = nRow - 1;
    char cChar = (nIdx == 4) ? ' ' : '_';

    for (; i < 5; i++)
    {
        if(cBoard[nIdx][i] == cToken)
            nCount++;
    }

    if (nCount > 1)
    {
        for (i = 0; i < 5; i++)
        {
            if(cBoard[nIdx][i] == cOpponent)
                cBoard[nIdx][i] = cChar;
        }
    }
    else
        rowWipe(cBoard, cToken);

}

void ladysChoice(char cBoard[5][5], char cToken, int (*valid)(int, int, int), void (*print)(char *))
{
    int nLady = (cToken == 'X' ? 2 : 1);
    int nRow = 0, nCol = 0;

    for (int i = 0; i < 3; i++)
    {
        print(cBoard);

        do
        {
            printf("Player %d, please choose %d empty square(s) to place your opponent's %c\n", nLady, 3-i, cToken);
            printf("Column (1-5): ");
            scanf("%d", &nCol);
            printf("Row (1-5): ");
            scanf("%d", &nRow);

        } while (!valid(nRow, nCol, cBoard[--nRow][--nCol]));
        
        cBoard[nRow][nCol] = cToken;
    }
    print(cBoard);
}

void evenItOut(char cBoard[5][5], char cToken)
{
    int i = 0, j = 0, k = 0;
    int nTokenCount = 0, nOppoCount = 0, nCol = 0, nRow = 0, nIdx1 = 0, nIdx2 = 0;
    char cOpponent = (cToken == 'X') ? 'O' : 'X';
    char cChar;

    for (; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (cBoard[i][j] == cToken)
                nTokenCount++;
            else if (cBoard[i][j] == cOpponent)
                nOppoCount++;
        }
    }

    if (nOppoCount > nTokenCount)
    {
        for (; k < (nOppoCount - nTokenCount); k++)
        {
            do
            {
                printf("Please choose a square to clear: \n");
                printf("Column: ");
                scanf("%d", &nCol);
                printf("Row: ");
                scanf("%d", &nRow);

                nIdx1 = nRow-1;
                nIdx2 = nCol-1;
                cChar = (nIdx1 == 4) ? ' ' : '_';

                cBoard[nIdx1][nIdx2] = cChar;

            } while (!(cBoard[nIdx1][nIdx2] == cOpponent));
            
        }
    }

}