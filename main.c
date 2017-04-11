#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "crossfireOperations.h"



// These are the prototypes for all the functions we will use in this program

int main (void)
{

//	Each player will be represented as a struct characterised by the fields
//	identifying the player (player type and player name), life points, and the fields
//	characterising the player capabilities (Smartness, Strength, Magic Skills, Luck and
//	Dexterity).

	// This line is needed to ensure values are truly random
	srand(time(NULL));
	int i, j, numberOfPlayers = 0, n1, row, column, boardSize = 7;

	//pointer to slot (0,0)
	struct slot *upLeft;
	//pointer to slot (0,boardSize -1)
	struct slot *upRight;
	//pointer to slot (boardSize - 1, 0)
	struct slot *downLeft;
	//pointer to slot (boardSize - 1, boardSize -1)
	struct slot *downRight;

	while (numberOfPlayers < 2 || numberOfPlayers > 6)
	{
		//Here the user enters the number of players in the game
		printf("How many players are playing today?\nPlease enter a number between 2 and 6\n");
		scanf("%d", &numberOfPlayers);
	}
	struct player playerInfo[numberOfPlayers];

	// This functions lets the user select a type and name, and assigns random values for the attributes (using details from the assignment document)
//	selectType(numberOfPlayers, playerInfo);

	struct slot ** board = malloc(boardSize * sizeof(struct slot *));

	//  Slots
	createBoard(boardSize,&upLeft, &upRight, &downLeft, &downRight, board);


	// Print function - doesn't work. Doesn't recognise board[][]
	//
	//
	for (i = 0; i < boardSize; i++)
	{
		for (j = 0; j < boardSize; j++)
		{
			printf("Row %d Column %d: Type %d\n", i, j, board[i][j].type);
		}
		printf("\n");
	}
	// This function prints the attributes for each player
/*	printf("-------Player Stats-------\n");
	printStats(numberOfPlayers, playerInfo);

	// This function allocates the slots, and calls the printSlots function to print the slots
//	n1 = slotsAllocation(slotsArray, numberOfPlayers,i,playerInfo);


	

	// This lets the user choose to move
	moveSlots(slotsArray, playerInfo, numberOfPlayers);

	//changes player stats based on where they move
	changeStats(slotsArray, playerInfo, n1);
	// This corrects these change stats, not letting values go below 0 and above 100
	invalidStatCheck(numberOfPlayers, playerInfo);

	// This prints the slots, after players have moved
	printSlots(numberOfPlayers, slotsArray, n1);

	// This prints the adjusted stats
	printf("-------Player Stats after moving-------\n");
	printStats(numberOfPlayers, playerInfo);

	// find the closest player, and attack
	closestPlayer(numberOfPlayers, playerInfo, slotsArray, n1);

	// This prints the status at the end of the game
	statusPrint(numberOfPlayers, playerInfo); */

	return 0;
}