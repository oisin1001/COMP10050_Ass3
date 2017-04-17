#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "crossfireOperations.h"

/*
 * This function creates the board
 * Parameters:
 * 	size: the size of the board
 * 	upLeft: pointer of pointer to slot at position (0, 0)
 * 	upRight: pointer of pointer to slot at position (0, boardSize -1)
 * 	downLeft: pointer of pointer to slot at position (boardSsize -1, 0)
 * 	upLeft: pointer of pointer to slot at position (boardSize - 1, boardSize -1)
 */

void createBoard(int boardSize, struct slot **upLeft, struct slot **upRight, struct slot **downLeft, struct slot **downRight, struct slot **board){	

	printf("createBoard started\n");
	for(int i =0; i< boardSize; i++){
		//This allocates in memory the space for the slots in each row of the board
		board[i] = malloc(boardSize * sizeof(struct slot));

		//For each slot it sets up the row and column number
		for(int j=0;j < boardSize; j++){
			board[i][j].row = i;
			board[i][j].column = j;
			int k = rand() % 3;// generate a random value 0, 1 or 2, then use this to assign slot type we will use
			board[i][j].type = k;
			// I let the playerNum of every struct in the array equal to -1 -- I'll use this in later when finding the closest player
		}
		printf("\n");
	}

	//It sets up the adjacent slots for the slots that are
	//not at the borders. These slots have 4 adjacent elements
	for(int i =1; i< boardSize-1; i++){
		for(int j=1;j < boardSize-1; j++){
			board[i][j].up = &board[i-1][j];
			board[i][j].right = &board[i][j+1];
			board[i][j].down = &board[i+1][j];
			board[i][j].left = &board[i][j-1];
		}
	}

	//It sets up the adjacent slots for the slots that are
	//in the first and the last row, except the slots at the edges.
	//
	for(int j = 1; j < boardSize -1; j++){
		//It sets up the adjacent slots for the slots that are in the first row.
		//These slots don't have an adjacent element on top of them
		// because they are on the first row of the board
		board[0][j].right = &board[0][j+1];
		board[0][j].left = &board[0][j-1];
		board[0][j].down = &board[1][j];
		board[0][j].up = NULL;

		//It sets up the adjacent slots for the slots that are in the last row.
		//These slots don't have an adjacent element on down them
		// because they are on the last row of the board
		board[boardSize - 1][j].right = &board[boardSize - 1][j+1];
		board[boardSize -1][j].left = &board[boardSize - 1][j-1];
		board[boardSize - 1][j].up = &board[boardSize - 2][j];
		board[boardSize - 1][j].down = NULL;
	}

	//It sets up the adjacent slots for the slots that are
	//in the first and the last column, except the slots at the edges.
	//
	for(int i = 1; i < boardSize -1; i++){
		//It sets up the adjacent slots for the slots that are in the first column.
		//These slots don't have an adjacent element on the left
		// because they are on the first column of the board
		board[i][0].right = &board[i][1];
		board[i][0].up = &board[i-1][0];
		board[i][0].down = &board[i+1][0];
		board[i][0].left = NULL;

		//It sets up the adjacent slots for the slots that are in the last column.
		//These slots don't have an adjacent element on the right
		// because they are on the last column of the board
		board[i][boardSize-1].left = &board[i][boardSize-2];
		board[i][boardSize -1].up = &board[i -1][boardSize-1];
		board[i][boardSize -1].down = &board[i+1][boardSize -1];
		board[i][boardSize -1].right = NULL;
	}


		//It sets up the adjacent slots for the slot at position (0,0).
		//This only has only 2 adjacent slots: right and down
		board[0][0].right = &board[0][1];
		board[0][0].down = &board[1][0];

		//It sets up the adjacent slots for the slot at position (0,boardSize -1).
		//This only has only 2 adjacent slots: left and down
		board[0][boardSize-1].left = &board[0][boardSize-2];
		board[0][boardSize -1].down = &board[1][boardSize -1];

		//It sets up the adjacent slots for the slot at position (boarSize -1 ,0).
		//This only has only 2 adjacent slots: up and right
		board[boardSize -1][0].right = &board[boardSize -1][1];
		board[boardSize -1][0].up = &board[boardSize -2][0];

		//It sets up the adjacent slots for the slot at position (boarSize -1 ,boardSize-1).
		//This only has only 2 adjacent slots: up and left
		board[boardSize - 1][boardSize-1].up = &board[boardSize-2][boardSize-1];
		board[boardSize - 1][boardSize -1].left = &board[boardSize -1][boardSize -2];


	//assigns a pointer to slot at position (0, 0)
	*upLeft = &board[0][0];
	//assigns pointer of pointer to slot at position (0, boardSize -1)
	*upRight = &board[0][boardSize -1];
	//assigns pointer of pointer to slot at position ( boardSize -1,)
	*downLeft = &board[boardSize -1][0];
	//assigns pointer of pointer to slot at position (boardSize -1, boardSize -1)
	*downRight = &board[boardSize -1][boardSize -1];
}

// This creates the slots, and places players in each slot
int slotsAllocation(struct slots slotsArray[20], int numberOfPlayers, int i, struct player playerInfo[6], struct slot **board)
{
	int rndColumn, rndRow, t;
	//placing players into slots
	for(t=0;t<numberOfPlayers;t++)
	{
		rndColumn = rand()%7;
		rndRow = rand() %7;
		printf("rndColumn is %d, rndRow is %d\n", rndColumn, rndRow);
		playerInfo[t].place = &board[rndColumn][rndRow];
	//	strcpy(slotsArray[rnd].player, playerInfo[t].name);
		// Here the number t replaces -1 -- this lets the program know later that this slot contains a player
	//	slotsArray[rnd].playerNum = t;
	//	playerInfo[t].location = rnd;
		
	}
	return 0;
}

void printSlots(int numberOfPlayers, struct slots slotsArray[20], int n1)
{
	int i;
	for(i = 0; i < n1; i++)//changed from playernum to n1 so as to only count the amount of slots present
	{
		printf("Location is %d\n", slotsArray[i].l+1);//added a +1 to make slots start at 1 , simply aestheical change , non essential
		printf("Slot type is %s\n", slotsArray[i].Slot_type);


		if(strcmp(slotsArray[i].player, "_") != 0)// a check to say if there is no player present to print a differant message
		{
			printf("Player name is %s\n", slotsArray[i].player);
		}
		if(strcmp(slotsArray[i].player, "_") == 0)
		{
			printf("No player present\n");
		}

		if (slotsArray[i].playerNum+1 != 0)//a check to only print this line if a player is present
		{
			printf("Player number is %d\n\n", slotsArray[i].playerNum+1);//added +1 so player 1 is counted as 1 and not 0 as before ,player 2 being called player 1 etc.
		}
		if ( slotsArray[i].playerNum+1 == 0)
		{
			printf("\n");//added simply for output spacing consistancy , non essential to code
		}
	}
	return;
}

void moveSlots(struct slot **board, struct player playerInfo[6], int numberOfPlayers)
{
	bool canMoveUp = true, canMoveDown = true, canMoveLeft = true, canMoveRight = true, validMove;
	int i, column, row, select, slotSelect;

	for (i = 0; i < numberOfPlayers; i++)
	{
		if(d[i]==Alive)//make sure their allive
        {
			printf("Do you want to move? Type 1 to move to an adjacent slot. Type 2 to stay in your current position.\n");
			scanf("%d", &select);

			if (select == 1)
			{
				row = playerInfo[i].place->row;
				column = playerInfo[i].place->column;

				// Checks when the player can move into a slot
				if (row == 0 && column == 0) {
					canMoveUp = false;
					canMoveLeft = false;
				} else if (row == 0 && column == 6) {
					canMoveUp = false;
					canMoveRight = false;
				} else if (row == 6 && column == 0) {
					canMoveDown = false;
					canMoveLeft = false;
				} else if (row == 6 && column == 6) {
					canMoveDown = false;
					canMoveRight = false;
				} else if (row == 0) {
					canMoveUp = false;
				} else if (row == 6) {
					canMoveDown = false;
				} else if (column == 0) {
					canMoveLeft = false;
				} else if (column == 6) {
					canMoveRight = false;
				}
				validMove = false;
				while(validMove == false)
				{
					printf("Type 1 to move up. Type 2 to move right. Type 3 to move down. Type 4 to move left.\n");
					scanf("%d", &slotSelect);
					// Changes the player location depending on the input
					if(slotSelect == 1 && canMoveUp == true)
					{
						playerInfo[i].place = playerInfo[i].place->up;
						validMove = true;
					} else if(slotSelect == 2 && canMoveRight == true)
					{
						playerInfo[i].place = playerInfo[i].place->right;
						validMove = true;
					} else if(slotSelect == 3 && canMoveDown == true)
					{
						playerInfo[i].place = playerInfo[i].place->down;
						validMove = true;
					} else if(slotSelect == 4 && canMoveLeft == true)
					{
						playerInfo[i].place = playerInfo[i].place->left;
						validMove = true;
					} else {
						printf("You cannot move in that direction. Please try again.\n");
					}
				}
			}
		}
	}	

	return;
}