#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ROWS     4
#define COLUMNS 4
enum Move { MOVE_UP = 0, MOVE_DOWN = 1, MOVE_LEFT = 2, MOVE_RIGHT = 3 };
int row;       
int column;   
int cells[ROWS][COLUMNS];
const int shuffles = 100;
 
int movement(enum Move move){
    const int x[] = {  0,  0, -1, +1 };
    const int y[] = { -1, +1,  0,  0 };
    int i = row     + y[move];
    int j = column + x[move];    
    if ( i >= 0 && i < ROWS && j >= 0 && j < COLUMNS ){
        cells[row][column] = cells[i][j];
        cells[i][j] = 0; row = i; column = j;
        return 1;
    }
    return 0;
}
 
void initialise(void)
{
    int i,j,k;
    for ( i = 0; i < ROWS; i++ )
        for ( j = 0; j < COLUMNS; j++ )
            cells[i][j] = i * COLUMNS + j + 1;
    cells[ROWS-1][COLUMNS-1] = 0;
    row = ROWS - 1;
    column = COLUMNS - 1;
    k = 0;
    while ( k < shuffles )
        k += movement((enum Move)(rand() % 4));
}
 
int gameover(void)
{
    int i,j; int k = 1;
    for ( i = 0; i < ROWS; i++ )
        for ( j = 0; j < COLUMNS; j++ ) 
            if ( (k < ROWS*COLUMNS) && (cells[i][j] != k++ ) )
                return 0;
    return 1;        
}

void display()
{
    int i,j;
    putchar('\n');
    for ( i = 0; i < ROWS; i++ )
    {
        for ( j = 0; j < COLUMNS; j++ )
        {
            if ( cells[i][j] )
            {
                if(j != COLUMNS-1 )
                {
                    printf("%2d ",cells[i][j]);
                }
                else{
                    printf("%2d\n",cells[i][j]);
                }
            }
                
            else
            {
                if(j != COLUMNS-1)
                {
                    printf("%2s ","");
                }
                else
                {
                    printf("%2s\n","");
                }
            }
        }
    }
    putchar('\n');
}

enum Move Controller_getMove(void){
    int c;
    while(1)
    {
        printf("%s", "Enter u/d/l/r : ");
        c = getchar();
        while( getchar() != '\n' );
        switch ( c )
        {
            
            case 'u' : return MOVE_UP;   
            case 'd' : return MOVE_DOWN;
            case 'l' : return MOVE_LEFT;
            case 'r' : return MOVE_RIGHT;
            default : exit(EXIT_SUCCESS);
        }
    }
}

int main(void){
 
    srand((unsigned)time(NULL));
 
    do 
    {
        initialise();
        
    }while ( gameover() );
 
    display();
    while( !gameover() ){ 
        movement( Controller_getMove() ); 
        display(); 
    }
 
    printf("You win");
    getchar();
 
    return 0;
}
