#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

typedef struct
{
    int i;
    int j;
}
position;

typedef struct node
{
    position pos;
    struct node* next;
}
node;

//reservoir sampling function to get random node from linked list
position randomNode(struct node *head){
    int reservoir[1];

    srand(time(NULL));
    position result = head->pos;
    struct node *trav = head;
    for(int n=2; trav != NULL; n++){
        if(rand()%n==0){
            result = trav->pos;
        }
        trav = trav->next;
    }
    return result;
}

//function for printing board
void printBoard(char board[16][16]){
    for(int i=0; i<16; i++){
        for(int j=0; j<16; j++){
            if(board[i][j]=='*'){
                printf ("\033[1;34m");
                printf("%c ", board[i][j]);
                printf("\033[0m");
            }else if(board[i][j]=='$'){
                printf ("\033[1;31m");
                printf("%c ", board[i][j]);
                printf("\033[0m");
            }else if(board[i][j]=='+'){
                printf ("\033[0;35m");
                printf("%c ", board[i][j]);
                printf("\033[0m");
            }
            else{
                printf("%c ", board[i][j]);
            }
        }
        printf("\n");
    }
}

//function to create first node and link
node* createNode(position array[4], int i){
    node* a=malloc(sizeof(node));
    a->pos.i=array[i].i;
    a->pos.j=array[i].j;
    a->next=NULL;
    return a;
}

//function to create Nth node and link
node* createNthNode(position array[4], int i, node* head){
    node* b=malloc(sizeof(node));
    b->pos.i=array[i].i;
    b->pos.j=array[i].j;
    b->next=head;
    head=b;
    return b;
}

//function to print battleships ships on the board
void placeBB(int x1, int x2, int y1, int y2, char board[16][16], char type){
    if(x2==x1){
        if(y2<y1){
            for(int j=y2; j<=y1; j++){
                board[x1][j]=type;
            }
        }else{
            for(int j=y1; j<=y2; j++){
                board[x1][j]=type;
            }
        }
    }else{
        if(x2<x1){
            for(int i=x2; i<=x1; i++){
                board[i][y1]=type;
            }
        }else{
            for(int i=x1; i<=x2; i++){
                board[i][y1]=type;
            }
        }
    }
}

//function to print Aircraft Carriers on the board
void placeCV(int x1, int x2, int y1, int y2, char board[16][16], char type){
    if(x1==x2){
        if(y1>2){
            for(int j=y2; j<=y1; j++){
                board[x1][j]=type;
            }
        }
        if(y2>y1){
            for(int j=y1; j<=y2; j++){
                board[x1][j]=type;
            }
        }
    }
    if(y1==y2){
        if(x1>x2){
            for(int i=x2; i<=x1; i++){
                board[i][y1]='C';
            }
        }
        if(x2>x1){
            for(int i=x1; i<=x2; i++){
                board[i][y1]='C';
            }
        }
    }
}

void placeOtherShips(char board[16][16]){
    for(int a=0; a<5; a++){
        position array[6][3];
        int sI=rand()%14+1;
        int sJ=rand()%14+1;
        int counter=0;
        for(int i=sI-1; i<=sI+1; i++){
            int rowSum=0;
            for(int j=sJ-1; j<=sJ+1; j++){
                rowSum+=(int)board[i][j];
            }
            if(rowSum==126){
                for(int x=0,j=sJ-1; x<3; x++, j++){
                    array[counter][x].i=i;
                    array[counter][x].j=j;
                }
                counter++;
            }
        }
        for(int j=sJ-1; j<=sJ+1; j++){
            int colSum=0;
            for(int i=sI-1; i<=sI+1; i++){
                colSum+=(int)board[i][j]; 
            }
            if(colSum==126){
                for(int x=0, i=sI-1; x<3; x++, i++){
                    array[counter][x].i=i;
                    array[counter][x].j=j;
                }
                counter++;
            }
        }
        srandom(time(NULL));
        int index = rand()%counter;
        for(int i=0; i<3; i++){
            if(a==0){
                board[array[index][i].i][array[index][i].j]='S';
            }else if(a==1){
                board[array[index][i].i][array[index][i].j]='A';
            }else if(a==2){
                board[array[index][i].i][array[index][i].j]='D';
            }else if(a==3){
                board[array[index][i].i][array[index][i].j]='L';
            }else{
                board[array[index][i].i][array[index][i].j]='H';
            }
        }
    }
}

