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

    //create player board
    char myBoard[16][16];
    for(int i=0; i<16; i++){
        for(int j=0; j<16; j++){
            myBoard[i][j]='*';
        }
    }
    printf("Enemy Board\n");
    generateBoard(enemyBoard);

    sleep(1);

    printf("\nMy Board\n");
    generateBoard(myBoard);
}