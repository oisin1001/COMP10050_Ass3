/*
 * userInteraction.c

 *
 *  Created on: 29 Mar 2017
 *      Author: liliana
 */

#include <stdio.h>
#include <stdbool.h>
#include "crossfireOperations.h"

//This function returns the board size provided as input by the user
int getBoardSize(){
	int boardSize;
	printf("Please enter the required size of the board\n");
	//asks the user to enter the desired board size
	scanf("%d", &boardSize);
	return boardSize;
}

void quitgame(struct player playerInfo[6], int currentplayer, int numberOfPlayers)
{
	int l;
	for(currentplayer = 0; currentplayer < numberOfPlayers; currentplayer++)
		{
		if(d[currentplayer]==Alive)
			{
				printf("player %d if you wish to quit the game enter 1, enter 2 to continue playing\n ",currentplayer+1);
				scanf("%d",&l);
			}
		if(l==1)
		{
			d[currentplayer]=Dead;
		}

		}

	return;
}
//THis function takes as input the size of the board and the pointers
// to the integers representing the row and the column of the slot that
// the user want to retrieve
void getDesiredElement(int boardSize, int * row, int * col){
	printf("Please enter the column and the Row of the desired slot \n");
	printf("Note that size of the board is %d\n", boardSize);

		//it will cycle asking the user to insert the row
		//until the value of the desired row is >= 0 or < of the
		// size of the board
		do {
			printf("Row: ");
			scanf("%d", row);
			printf("%d\n", *row);
			if(row < 0 && *row >= boardSize)
				printf("Error: Incorrect row dimension\n");
		} while(*row < 0 && *row >= boardSize);

		//it will cycle asking the user to insert the column
		//until the value of the desired row is >= 0 or < of the
		// size of the board
		do {
			printf("Column: ");
			scanf("%d", col);
			printf("%d\n", *col);
			if(*col < 0 && *col >= boardSize)
				printf("Error: Incorrect column dimension\n");
		} while(*col < 0 && *col >= boardSize);
}
