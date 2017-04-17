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
	int i, j, numberOfPlayers = 0, n1, row, column, boardSize = 7, attackChoice;

	bool foundDistance[6][6];
	int distanceArray[6][6];

	for(i = 0; i < 6; i++)
	{
		for(j = 0; j < 6; j++)
		{
			if(i < numberOfPlayers && j < numberOfPlayers)
			{
				distanceArray[i][j] = -1;
				foundDistance[i][j] = false;
			} else {
				distanceArray[i][j] = -2;
			}
		}
	}

	//pointer to slot (0,0)
	struct slot *upLeft;
	//pointer to slot (0,boardSize -1)
	struct slot *upRight;
	//pointer to slot (boardSize - 1, 0)
	struct slot *downLeft;
	//pointer to slot (boardSize - 1, boardSize -1)
	struct slot *downRight;

	//declare all players alive
	for(i=0;i<numberOfPlayers;i++)
	{
		d[i]=Alive;
	}

	glados[1]=OK;//make sure still alive glados is initially set to OK so that the game runs

	while (numberOfPlayers < 2 || numberOfPlayers > 6)
	{
		//Here the user enters the number of players in the game
		printf("How many players are playing today?\nPlease enter a number between 2 and 6\n");
		scanf("%d", &numberOfPlayers);
	}
	struct player playerInfo[numberOfPlayers];

	// This functions lets the user select a type and name, and assigns random values for the attributes (using details from the assignment document)
	selectType(numberOfPlayers, playerInfo);
	
	//The board is represented as a pointer of pointer to slots
 	//This allocates in memory the space for the pointers to each row of the board
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
			if(board[i][j].type==0)
			{
            printf("r:%d c:%d LvlGrd  ",i+1,j+1);
			}
			if(board[i][j].type==1)
			{
            printf("r:%d c:%d  Hill   ",i+1,j+1);
            }
			if(board[i][j].type==2)
            {
            printf("r:%d c:%d  City   ",i+1,j+1);
            }
		}
		printf("\n");
	}
	// This function prints the attributes for each player
	printf("-------Player Stats-------\n");
	

	// This function allocates the slots, and calls the printSlots function to print the slots
	slotsAllocation(slotsArray, numberOfPlayers,i,playerInfo, board);

//	for (i = 0; i < numberOfPlayers; i++)
//	{
//		printf("Row %d Column %d: Type %d\n", i, j, board[i][j].type);

//		printf("\n");
//	}
	
	printStats(numberOfPlayers, playerInfo);



while(glados[1]==OK)//while there are at least 2 players still alive keep playing
{

	// This lets the user choose to move
	moveSlots(board, playerInfo, numberOfPlayers);

	//lets players quit if they want to
	quitgame(playerInfo, i,numberOfPlayers);

	//changes player stats based on where they move
	changeStats(numberOfPlayers, playerInfo);

	// This corrects these change stats, not letting values go below 0 and above 100
	invalidStatCheck(numberOfPlayers, playerInfo);

//	// This prints the slots, after players have moved
//	printSlots(numberOfPlayers, slotsArray, n1);

	// This prints the adjusted stats
	printf("-------Player Stats after moving-------\n");
	printStats(numberOfPlayers, playerInfo);

	for(i = 0; i < numberOfPlayers; i++)
	{
		for(j=0; j < numberOfPlayers; j++)
		{
			findDistance(playerInfo[i].place->row, playerInfo[i].place->column, playerInfo[j].place->row, playerInfo[j].place->column, distanceArray, foundDistance, i, j);
		}
	}


	// find the closest player, and attack
	//closestPlayer(numberOfPlayers, playerInfo, slotsArray, n1);
	for(i = 0; i < numberOfPlayers; i++)
	{
	  if(d[i]==Alive)//checks if the player is alive before it allows them to attack
	  {
		attackChoice = 0;
		printf("Player %d:\n", i+1);
		while(attackChoice < 1 || attackChoice > 3)
		{
			printf("Select an attack type.\nType 1 for a near attack. Type 2 for a distant attack. Type 3 for a magic attack.\n");
			scanf("%d", &attackChoice);
		}

		if (attackChoice == 1)
		{
			nearAttack(playerInfo, distanceArray, i, numberOfPlayers);
		} else if (attackChoice == 2)
		{
			distantAttack(playerInfo, distanceArray, i, numberOfPlayers);
		} else if (attackChoice == 3)
		{
			if (playerInfo[i].smartness + playerInfo[i].magic > 150)
			{
				magicAttack(playerInfo, numberOfPlayers, i);
			} else {
				printf("You cannot do a magic attack. Please select another attack type.\n");
				i--;
			}
		}
	   }
	}

	i=0; //reset i so on next turn player
	//check if the player is living
		void playerdeath(int numberOfPlayers, struct player playerInfo[6]);
		//check if everyones still alive
		void allalive(int numberOfPlayers, struct player playerInfo[6]);

}
		//end loop here for letting multiple moves in the game


	// This prints the status at the end of the game
	/*statusPrint(numberOfPlayers, playerInfo); */

	return 0;
}
