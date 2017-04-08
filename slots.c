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

void createBoard(int boardSize, struct slot **upLeft, struct slot **upRight, struct slot **downLeft, struct slot **downRight){

	//The board is represented as a pointer of pointer to slots
	//This allocates in memory the space for the pointers to each row of the board
	struct slot ** board = malloc(boardSize * sizeof(struct slot *));

	printf("createBoard started\n");
	for(int i =0; i< boardSize; i++){
		//This allocates in memory the space for the slots in each row of the board
		board[i] = malloc(boardSize * sizeof(struct slot));

		//For each slot it sets up the row and column number
		for(int j=0;j < boardSize; j++){
			board[i][j].row = i;
			board[i][j].column = j;
			int j = rand() % 3;// generate a random value 0, 1 or 2, then use this to assign slot type we will use
			if (j==0)
			{
				strcpy(board[i][j].Slot_type, "Level Ground");
			}

			if (j==1)
			{
				strcpy(board[i][j].Slot_type, "Hill");
			}
			if (j==2)
			{
				strcpy(board[i][j].Slot_type, "City");
			}
			printf("%s, ", board[i][j].Slot_type);
			//	slotsArray[i].player = "_";
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
/*int slotsAllocation(struct slots slotsArray[20], int numberOfPlayers, int i, struct player playerInfo[6])
{
	int rnd,n1,t;
	printf("How many slots would you like to create? Please enter a number between %d and 20\n\n",numberOfPlayers);
	// allows the user to enter the amount of the slots they want with a max of 20
	scanf("%d", &n1);

	if(n1<numberOfPlayers)
	{
		printf("There must be at least %d slots - one for each player \n\n", numberOfPlayers);
		printf("Please enter a number between %d and 20\n",numberOfPlayers);
		// allows user to enter again if they made a mistake the first time and entered an invalid number
		scanf("%d", &n1);
	}

	if(n1>20)
	{
		//secondary check, less important than the n1<numberOfPlayers check, makes sure the number entered isn't too high
		printf("Please enter a number between %d and 20\n",numberOfPlayers);
		scanf("%d", &n1);
	}


	for(i=0;i<n1;i++)//for generating the slots themselves
	{
		int j = rand() % 3;// generate a random value 0, 1 or 2, then use this to assign slot type we will use
		if (j==0)
		{
			slotsArray[i].l = i;
			strcpy(slotsArray[i].Slot_type, "Level Ground");
		}

		if (j==1)
		{
			slotsArray[i].l = i;
			strcpy(slotsArray[i].Slot_type, "Hill");
		}
		if (j==2)
		{
			slotsArray[i].l = i;
			strcpy(slotsArray[i].Slot_type, "City");
		}
		//	slotsArray[i].player = "_";
		strcpy(slotsArray[i].player, "_");
		// I let the playerNum of every struct in the array equal to -1 -- I'll use this in later when finding the closest player
		slotsArray[i].playerNum = -1;
	}



	//placing players into slots
	for(t=0;t<numberOfPlayers;t++)
	{
		rnd = rand() %n1;
		if(strcmp(slotsArray[rnd].player, "_") == 0)
		{
			strcpy(slotsArray[rnd].player, playerInfo[t].name);
			// Here the number t replaces -1 -- this lets the program know later that this slot contains a player
			slotsArray[rnd].playerNum = t;
			playerInfo[t].location = rnd;
		} else {
			t--;
		}
	}

	printSlots(numberOfPlayers, slotsArray, n1);

	// I return the value n1, so I can use the number of slots in other programs
	return n1;
}*/

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

// This lets the user move from one slot to another if they wish
void moveSlots(struct slots slotsArray[20], struct player playerInfo[6], int numberOfPlayers)
{
	int locationAsInt, C1, C2, pl;
	// We use booleans to check if a player is allowed to move forwards or backwards
	bool canMoveForwards, canMoveBackwards;
	int locationPlusOne, locationMinusOne;
	// We use temp characters and strings to let us swap characters/strings
	char temp[30], tempChar;

	for(pl=0;pl<numberOfPlayers;pl++)
	{
		printf("\nPlayer %d, you are curently at slot %d. \nDo you wish to move? Enter 1 to move, or enter 2 to stay in your current location and attack\n", pl+1, playerInfo[pl].location+1);
		scanf("%d",&C1);
		if(C1==1)
		{
			// We assume that we cannot move into any slots, unless we prove later on that those slots exist and are empty
			canMoveBackwards = false;
			canMoveForwards = false;
			locationAsInt = playerInfo[pl].location;
			locationPlusOne = locationAsInt + 1;
			locationMinusOne = locationAsInt - 1;
			if((strcmp(slotsArray[locationAsInt+1].player, "_")) == 0)
			{
				// The next slot is empty, so we can move there
				canMoveForwards=true;
			}
			if((strcmp(slotsArray[locationAsInt-1].player, "_")) == 0)
			{
				// The previous slot is empty, so we can move there
				canMoveBackwards=true;
			}
			if(canMoveForwards==true && canMoveBackwards==true)
			{
				// The player can move either backwards or forwards, so I let the user select which one
				printf("Enter 1 if you wish to move forwards\nEnter 2 if you wish to move backwards\n");
				scanf("%d",&C2);
				if(C2==1)
				{
					// This swaps the players location with the next one
					// I use strcpy to copy the strings
					strcpy(temp, slotsArray[locationAsInt].player);
					strcpy(slotsArray[locationAsInt].player, slotsArray[locationPlusOne].player);
					strcpy(slotsArray[locationPlusOne].player, temp);
					tempChar = slotsArray[locationAsInt].playerNum;
					slotsArray[locationAsInt].playerNum = slotsArray[locationPlusOne].playerNum;
					slotsArray[locationPlusOne].playerNum = tempChar;
					// I set the .canAttack boolean to false. The player cannot attack, as they have used their turn to move
					playerInfo[pl].canAttack = false;
					// I add +1 here, purely for asthetic purposes
					printf("Your new position is slot %d\n\n",locationPlusOne+1);
				}
				if(C2==2)
				{
					// This swaps the players location with the previous one
					// I use strcpy to copy the strings
					strcpy(temp, slotsArray[locationAsInt].player);
					strcpy(slotsArray[locationAsInt].player, slotsArray[locationMinusOne].player);
					strcpy(slotsArray[locationMinusOne].player, temp);
					tempChar = slotsArray[locationAsInt].playerNum;
					slotsArray[locationAsInt].playerNum = slotsArray[locationMinusOne].playerNum;
					slotsArray[locationMinusOne].playerNum = tempChar;
					// I set the .canAttack boolean to false. The player cannot attack, as they have used their turn to move
					playerInfo[pl].canAttack = false;
					printf("Your new position is slot %d\n\n",locationMinusOne+1);
				}
			}
			else if(canMoveForwards==true)
			{
				// This swaps the players location with the next one
				// I use strcpy to copy the strings
				printf("You can only move forwards\n");
				strcpy(temp, slotsArray[locationAsInt].player);
				strcpy(slotsArray[locationAsInt].player, slotsArray[locationPlusOne].player);
				strcpy(slotsArray[locationPlusOne].player, temp);
				tempChar = slotsArray[locationAsInt].playerNum;
				slotsArray[locationAsInt].playerNum = slotsArray[locationPlusOne].playerNum;
				slotsArray[locationPlusOne].playerNum = tempChar;
				// I set the .canAttack boolean to false. The player cannot attack, as they have used their turn to move
				playerInfo[pl].canAttack = false;
				printf("Your new position is slot %d\n\n",locationPlusOne+1);
			}
			else if(canMoveBackwards==true)
			{
				// This swaps the players location with the previous one
				// I use strcpy to copy the strings
				printf("You can only move backwards\n");
				strcpy(temp, slotsArray[locationAsInt].player);
				strcpy(slotsArray[locationAsInt].player, slotsArray[locationMinusOne].player);
				strcpy(slotsArray[locationMinusOne].player, temp);
				tempChar = slotsArray[locationAsInt].playerNum;
				slotsArray[locationAsInt].playerNum = slotsArray[locationMinusOne].playerNum;
				slotsArray[locationMinusOne].playerNum = tempChar;
				// I set the .canAttack boolean to false. The player cannot attack, as they have used their turn to move
				playerInfo[pl].canAttack = false;
				printf("Your new position is slot %d\n\n",locationMinusOne+1);
			}
			else
			{
				// If neither booleans are true, the player cannot move
				printf("you cannot move\n\n");
				// The player didn't move, so they can still attack
				playerInfo[pl].canAttack = true;
			}
		} else {
			// The player didn't move, so they can still attack
			playerInfo[pl].canAttack = true;
		}
	}
	return;
}