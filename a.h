#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "battleship.h"

void generateBoard(char board[16][16]){
    srand(time(NULL));

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
    placeCV(cI1,cI2,cJ1,cJ2,board,'C');

    //generate enemy BB position
    int bI1=rand()%16;
    int bJ1=rand()%16;
    while(board[bI1][bJ1]=='C'){
        srandom(time(NULL));
        int bI1=rand()%16;
        int bJ1=rand()%16;
        if(board[bI1][bJ1]!='C'){
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
                    if(board[bI1][j]=='C'){
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
                    if(board[bI1][j]=='C'){
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
                    if(board[i][bJ1]=='C'){
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
                    if(board[i][bJ1]=='C'){
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
    placeBB(bI1, bI2, bJ1, bJ2, board, 'B');
    placeOtherShips(board);
    printBoard(board);
}