#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <unistd.h>
#include "a.h"

position randomNode(struct node *head);
void printBoard(char board[16][16]);
node* createNode(position array[4], int i);
node* createNthNode(position array[4], int i, node* head);
void placeBB(int x1, int x2, int y1, int y2, char board[16][16], char type);
void placeCV(int x1, int x2, int y1, int y2, char board[16][16], char type);
void placeOtherShips(char board[16][16]);

int main(void){
    //create enemy board
    char enemyBoard[16][16];
    for(int i=0; i<16; i++){
        for(int j=0; j<16; j++){
            enemyBoard[i][j]='*';
        }
    }

    //create enemy board overlay
    char enemyBoardOverlay[16][16];
    for(int i=0; i<16; i++){
        for(int j=0; j<16; j++){
            enemyBoardOverlay[i][j]='*';
        }
    }

    //create player board
    char myBoard[16][16];
    for(int i=0; i<16; i++){
        for(int j=0; j<16; j++){
            myBoard[i][j]='*';
        }
    }

    printf("Enemy Board\n");
    generateBoard(enemyBoard);
    printBoard(enemyBoardOverlay);

    sleep(1);

    printf("\nMy Board\n");
    generateBoard(myBoard);
    printBoard(myBoard);

    int eCountR=3, eCountT=1;
    int mCountR=3, mCountT=1;

    while(true){
        int eCountS=0, eCountH=0, eCountL=0, eCountB=0, eCountA=0, eCountC=0, eCountD=0;
        int mCountS=0, mCountH=0, mCountL=0, mCountB=0, mCountA=0, mCountC=0, mCountD=0;

        //my turn
        int mRow;
        int mCol;
        char action;

        //prompt for user input
        printf("Which row? ");
        scanf("%i", &mRow);
        printf("Which column? ");
        scanf("%i", &mCol);
        if(enemyBoard[mRow][mCol]=='*'){
            enemyBoard[mRow][mCol]='+';
            enemyBoardOverlay[mRow][mCol]='+';
        }else{
            enemyBoard[mRow][mCol]='$';
            enemyBoardOverlay[mRow][mCol]='$';
        }
        
        //count
        for(int i=0; i<16; i++){
            for(int j=0; j<16; j++){
                if(enemyBoard[i][j]=='S'){
                    eCountS++;
                }else if(enemyBoard[i][j]=='H'){
                    eCountH++;
                }else if(enemyBoard[i][j]=='L'){
                    eCountL++;
                }else if(enemyBoard[i][j]=='B'){
                    eCountB++;
                }else if(enemyBoard[i][j]=='A'){
                    eCountA++;
                }else if(enemyBoard[i][j]=='C'){
                    eCountC++;
                }else if(enemyBoard[i][j]=='D'){
                    eCountD++;
                }
            }
        }

        int sumE=eCountS+eCountH+eCountL+eCountB+eCountA+eCountC+eCountD;
        if(sumE==0){
            printf("You won!");
            return 0;
        }

        //generate enemy board
        printf("\nEnemy Board: \n");
        printBoard(enemyBoardOverlay);

        //enemy turn
        srandom(time(NULL));
        int targetI = rand()%15;
        int targetJ = rand()%15;
        if(myBoard[targetI][targetJ]!='*'){
            myBoard[targetI][targetJ]='$';
            }else{
            myBoard[targetI][targetJ]='+';
        }

        //count
        for(int i=0; i<16; i++){
            for(int j=0; j<16; j++){
                if(myBoard[i][j]=='S'){
                    mCountS++;
                }else if(myBoard[i][j]=='H'){
                    mCountH++;
                }else if(myBoard[i][j]=='L'){
                    mCountL++;
                }else if(myBoard[i][j]=='B'){
                    mCountB++;
                }else if(myBoard[i][j]=='A'){
                    mCountA++;
                }else if(myBoard[i][j]=='C'){
                    mCountC++;
                }else if(myBoard[i][j]=='D'){
                    mCountD++;
                }
            }
        }

        int sumM=mCountS+mCountH+mCountL+mCountB+mCountA+mCountC+mCountD;
        if(sumM==0){
            printf("You lost!");
            return 1;
        }

        //generate my board
        printf("\nMy Board: \n");
        printBoard(myBoard);
    }
}