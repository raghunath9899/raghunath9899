
#include<stdio.h>
#include<conio.h>
#include<time.h>

int row;       
int column;   
int cells[4][4];
const int shuffles = 100;
int movement(int move)
{
    const int x[] = {  0,  0, -1, +1 };
    const int y[] = { -1, +1,  0,  0 };
    int i = row     + y[move];
    int j = column + x[move];    
    if ( i >= 0 && i < 4 && j >= 0 && j < 4 )
    {
        int temp;
        temp=cells[row][column];
        cells[row][column] = cells[i][j];
        cells[i][j] = temp; row = i; column = j;
        return 1;
    }
    return 0;
}
 
void initialise(void)
{
    int i,j,k;
    for ( i = 0; i < 4; i++ )
    {
        for ( j = 0; j < 4; j++ )
        {
            cells[i][j] = i * 4 + j + 1;
        }
    }
    cells[3][3] = 0;
    row =  rand() % 4;
    column = rand() % 4;
    k = 0;
    while ( k < shuffles )
        k += movement(rand() % 4);
}
void game()
{
    int i,j,flag=1,move;
    while(flag)
    {
        label1:
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(cells[i][j])
            {
                printf("    %2d    |",cells[i][j]);
            }
            else
            {
                printf("    %2c     |",cells[i][j]);
            }
        }
        printf("\n\n");
    }
    printf("Enter the movement to interchange(Top / Bottom / Left / Right)(1/2/3/4):");
    scanf("%d",&move);
    movement(move-1);
    for(i=0,flag=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(cells[i][j]!=i * 4 + j + 1)
            {
                flag=1;
                goto label1;
            }
        }
    }
    }
    if(flag==0)
    {
        printf("YOU WON");
    }
}
int main()
{
    int i,j;
    srand(time(NULL));
    initialise();
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(cells[i][j]==0)
            {
                row=i;
                column=j;
                goto label;
            }
        }
    }
    label:
    game();
    return 0;
}
