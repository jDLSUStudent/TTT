#include <stdio.h>

int nCheckValidity();
void main() 
{
    int nCol = 0, nRow = 0, nIndex1 = 0, nIndex2 = 0, nPlayer = 0, nWinner = 0, nValidMove = 0, i = 0, j = 0;
 
    char cBoard [5][5] = {
                {'_', '_', '_', '_', '_'},
                {'_', '_', '_', '_', '_'},
                {'_', '_', '_', '_', '_'},
                {'_', '_', '_', '_', '_'},
                {' ', ' ', ' ', ' ', ' '},
                        };

    for (; i < 25 && !nWinner; i++)
    {
        printf("\n");
        printf("  1|2|3|4|5\n");
        printf("1:%c|%c|%c|%c|%c\n",cBoard[0][0],cBoard[0][1],cBoard[0][2],cBoard[0][3],cBoard[0][4]);
        printf("2:%c|%c|%c|%c|%c\n",cBoard[1][0],cBoard[1][1],cBoard[1][2],cBoard[1][3],cBoard[1][4]);
        printf("3:%c|%c|%c|%c|%c\n",cBoard[2][0],cBoard[2][1],cBoard[2][2],cBoard[2][3],cBoard[2][4]);
        printf("4:%c|%c|%c|%c|%c\n",cBoard[3][0],cBoard[3][1],cBoard[3][2],cBoard[3][3],cBoard[3][4]);
        printf("5:%c|%c|%c|%c|%c\n",cBoard[4][0],cBoard[4][1],cBoard[4][2],cBoard[4][3],cBoard[4][4]);

        nPlayer = i%2 + 1;

        /*
        nValidMove = 
        nRow > 0 && nRow < 6
        nCol > 0 && nCol < 6
        cBoard[row][column] != 'X' || cBoard[row][column] != 'O'
        */
        do
        {
            printf("\n");    
            printf("Player %d, please choose a square to place your %c by selecting the column first \n"
                    "and then the row (e.g. 1 5 for the bottom left square).\n", nPlayer, (nPlayer == 1) ? 'X' : 'O');
            printf("Column (1-5): ");
            scanf("%d", &nCol);
            printf("Row (1-5): ");
            scanf("%d", &nRow);

            nIndex1 = nRow - 1;
            nIndex2 = nCol - 1;
            nValidMove = (nRow > 0 && nRow < 6) && (nCol > 0 && nCol < 6) 
                        && (cBoard[nIndex1][nIndex2] != 'X' && cBoard[nIndex1][nIndex2] != 'O'); 

        } while (!nValidMove);
        
        cBoard[nIndex1][nIndex2] = (nPlayer == 1) ? 'X' : 'O';

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
            for(; j <= 4; j++)
				if((cBoard[j][0]==cBoard[j][1] 
                    && cBoard[j][0]==cBoard[j][2]
                    && cBoard[j][0]==cBoard[j][3] 
                    && cBoard[j][0]==cBoard[j][4]
                    /*&& (cBoard[j][0]=='X' || cBoard[j][0]=='O')*/) /*Horizontal*/
                    /*|| (cBoard[0][j]==cBoard[1][j] 
                    && cBoard[0][j]==cBoard[2][j]
                    && cBoard[0][j]==cBoard[3][j] 
                    && cBoard[0][j]==cBoard[4][j]
                    && (cBoard[0][j]=='X' || cBoard[0][j]=='O'))*/) /*Vertical*/
					nWinner++;
        
    }

/*
    printf("\n");
    printf("  1|2|3|4|5\n");
    printf("1|%c|%c|%c|%c|%c\n",cBoard[0][0],cBoard[0][1],cBoard[0][2],cBoard[0][3],cBoard[0][4]);
    printf("2|%c|%c|%c|%c|%c\n",cBoard[1][0],cBoard[1][1],cBoard[1][2],cBoard[1][3],cBoard[1][4]);
    printf("3|%c|%c|%c|%c|%c\n",cBoard[2][0],cBoard[2][1],cBoard[2][2],cBoard[2][3],cBoard[2][4]);
    printf("4|%c|%c|%c|%c|%c\n",cBoard[3][0],cBoard[3][1],cBoard[3][2],cBoard[3][3],cBoard[3][4]);
    printf("5|%c|%c|%c|%c|%c\n",cBoard[4][0],cBoard[4][1],cBoard[4][2],cBoard[4][3],cBoard[4][4]);
*/
}

int nCheckValidity(int nRow,int nCol,char cBoard[nRow][nCol])
{
    int nValid = 0;

    nValid = (nRow > 0 && nRow < 6) && (nCol > 0 && nCol < 6) && (cBoard[nRow][nCol] != 'X' && cBoard[nRow][nCol] != 'O');

    return nValid;
}
