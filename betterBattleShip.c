#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

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

position randomNode(struct node *head);
void printBoard(char board[16][16]);
node* createNode(position array[4], int i);
node* createNthNode(position array[4], int i, node* head);

int main(void){
    srand(time(NULL));

    //create enemy board
    char enemyBoard[16][16];
    for(int i=0; i<16; i++){
        for(int j=0; j<16; j++){
            enemyBoard[i][j]='*';
        }
    }

    //create player board
    char myBoard[16][16];
    for(int i=0; i<16; i++){
        for(int j=0; j<16; j++){
            myBoard[i][j]='*';
        }
    }

    //generate enemy CV position
    int cJ1=rand()%16;
    int cI1=rand()%16;
    position positionPotentialCV[4];
    node *positionPossibleCV=NULL;
    positionPotentialCV[0].i=cI1+4;
    positionPotentialCV[0].j=cJ1;
    positionPotentialCV[1].i=cI1-4;
    positionPotentialCV[1].j=cJ1;
    positionPotentialCV[2].i=cI1;
    positionPotentialCV[2].j=cJ1+4;
    positionPotentialCV[3].i=cI1;
    positionPotentialCV[3].j=cJ1-4;
    for(int i=0; i<4; i++){
        if(positionPotentialCV[i].i>15||positionPotentialCV[i].i<0||positionPotentialCV[i].j>15||positionPotentialCV[i].j<0){
            continue;
        }else{
            //create a node and link to positionPossibleCV
            if(positionPossibleCV==NULL){
                positionPossibleCV=createNode(positionPotentialCV, i);
            }else{
                positionPossibleCV=createNthNode(positionPotentialCV, i, positionPossibleCV);
            }
        }
    }
    int cI2=randomNode(positionPossibleCV).i;
    int cJ2=randomNode(positionPossibleCV).j;
    if(cI1==cI2){
        if(cJ1>cJ2){
            for(int j=cJ2; j<=cJ1; j++){
                enemyBoard[cI1][j]='C';
            }
        }
        if(cJ2>cJ1){
            for(int j=cJ1; j<=cJ2; j++){
                enemyBoard[cI1][j]='C';
            }
        }
    }
    if(cJ1==cJ2){
        if(cI1>cI2){
            for(int i=cI2; i<=cI1; i++){
                enemyBoard[i][cJ1]='C';
            }
        }
        if(cI2>cI1){
            for(int i=cI1; i<=cI2; i++){
                enemyBoard[i][cJ1]='C';
            }
        }
    }


    //generate enemy BB position
    int bI1=rand()%16;
    int bJ1=rand()%16;
    while(enemyBoard[bI1][bJ1]=='C'){
        srandom(time(NULL));
        int bI1=rand()%16;
        int bJ1=rand()%16;
        if(enemyBoard[bI1][bJ1]!='C'){
            break;
        }
    }

    position positionPotentialBB[4];
    node *positionPossibleBB=NULL;
    positionPotentialBB[0].i=bI1+3;
    positionPotentialBB[0].j=bJ1;
    positionPotentialBB[1].i=bI1-3;
    positionPotentialBB[1].j=bJ1;
    positionPotentialBB[2].i=bI1;
    positionPotentialBB[2].j=bJ1+3;
    positionPotentialBB[3].i=bI1;
    positionPotentialBB[3].j=bJ1-3;
    
    for(int i=0; i<4; i++){
        if(positionPotentialBB[i].i>15||positionPotentialBB[i].i<0){
            continue;
        }else if(positionPotentialBB[i].j>15||positionPotentialBB[i].j<0){
            continue;
        }else{
            if(positionPossibleCV==NULL){
                positionPossibleBB=createNode(positionPotentialBB, i);
            }else{
                positionPossibleBB=createNthNode(positionPotentialBB, i, positionPossibleBB);
            }
        }
    }

    //new linked list
    node* head = NULL;

    //create traversing pointer
    node* trav=positionPossibleBB;
    while(trav!=NULL){
        int counter=0;
        if(trav->pos.i==bI1){
            if(bJ1<trav->pos.j){
                for(int j=bJ1; j<=trav->pos.j; j++){
                    if(enemyBoard[bI1][j]=='C'){
                        counter++;
                    }
                }
                if(counter==0){
                    if(head==NULL){
                        node* a=malloc(sizeof(node));
                        a->pos.i=bI1;
                        a->pos.j=trav->pos.j;
                        a->next=NULL;
                        head=a;
                    }else{
                        node* b=malloc(sizeof(node));
                        b->pos.i=bI1;
                        b->pos.j=trav->pos.j;
                        b->next=head;
                        head=b;
                    }     
                }
            }else if(bJ1>trav->pos.j){
                for(int j=trav->pos.j; j<=bJ1; j++){
                    if(enemyBoard[bI1][j]=='C'){
                        counter++;
                    }
                }
                if(counter==0){
                    if(head==NULL){
                        node* a=malloc(sizeof(node));
                        a->pos.i=bI1;
                        a->pos.j=trav->pos.j;
                        a->next=NULL;
                        head=a;
                    }else{
                        node* b=malloc(sizeof(node));
                        b->pos.i=bI1;
                        b->pos.j=trav->pos.j;
                        b->next=head;
                        head=b;
                    }     
                }
            }
        }else if(trav->pos.j==bJ1){
            if(bI1<trav->pos.i){
                for(int i=bI1; i<=trav->pos.i; i++){
                    if(enemyBoard[i][bJ1]=='C'){
                        counter++;
                    }
                }
                if(counter==0){
                    if(head==NULL){
                        node* a=malloc(sizeof(node));
                        a->pos.i=trav->pos.i;
                        a->pos.j=bJ1;
                        a->next=NULL;
                        head=a;
                    }else{
                        node* b=malloc(sizeof(node));
                        b->pos.i=trav->pos.i;
                        b->pos.j=bJ1;
                        b->next=head;
                        head=b;
                    }     
                }
            }else if(bI1>trav->pos.i){
                for(int i=trav->pos.i; i<=bI1; i++){
                    if(enemyBoard[i][bJ1]=='C'){
                        counter++;
                    }
                }
                if(counter==0){
                    if(head==NULL){
                        node* a=malloc(sizeof(node));
                        a->pos.i=trav->pos.i;
                        a->pos.j=bJ1;
                        a->next=NULL;
                        head=a;
                    }else{
                        node* b=malloc(sizeof(node));
                        b->pos.i=trav->pos.i;
                        b->pos.j=bJ1;
                        b->next=head;
                        head=b;
                    }     
                }
            }
        }
        trav=trav->next;
    }

    int bI2 = randomNode(head).i;
    int bJ2 = randomNode(head).j;
    if(bI2==bI1){
        if(bJ2<bJ1){
            for(int j=bJ2; j<=bJ1; j++){
                enemyBoard[bI1][j]='B';
            }
        }else{
            for(int j=bJ1; j<=bJ2; j++){
                enemyBoard[bI1][j]='B';
            }
        }
    }else{
        if(bI2<bI1){
            for(int i=bI2; i<=bI1; i++){
                enemyBoard[i][bJ1]='B';
            }
        }else{
            for(int i=bI1; i<=bI2; i++){
                enemyBoard[i][bJ1]='B';
            }
        }
    }

    //generate 2 enemy Submarines (S) and 3 enemy Destroyers (D)
    for(int a=0; a<5; a++){
        position array[6][3];
        int sI=rand()%14+1;
        int sJ=rand()%14+1;
        int counter=0;
        for(int i=sI-1; i<=sI+1; i++){
            int rowSum=0;
            for(int j=sJ-1; j<=sJ+1; j++){
                rowSum+=(int)enemyBoard[i][j];
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
                colSum+=(int)enemyBoard[i][j]; 
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
                enemyBoard[array[index][i].i][array[index][i].j]='S';
            }else if(a==1){
                enemyBoard[array[index][i].i][array[index][i].j]='A';
            }else if(a==2){
                enemyBoard[array[index][i].i][array[index][i].j]='D';
            }else if(a==3){
                enemyBoard[array[index][i].i][array[index][i].j]='L';
            }else{
                enemyBoard[array[index][i].i][array[index][i].j]='H';
            }
        }
    }
    printBoard(enemyBoard);

}

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

//function for priting enemy board
void printBoard(char board[16][16]){
    for(int i=0; i<16; i++){
        for(int j=0; j<16; j++){
            if(board[i][j]=='*'){
                printf ("\033[0;34m");
                printf("%c ", board[i][j]);
                printf("\033[0m");
            }else{
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

