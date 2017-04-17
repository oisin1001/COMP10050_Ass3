#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "crossfireOperations.h"

void nearAttack(struct player playerInfo[6], int distanceArray[6][6], int attacker, int numberOfPlayers)
{
	
	int attacked, i, selectedAttack, attackedSelected;

	for(i = 0; i < numberOfPlayers; i++)
	{
		playerInfo[i].canAttack = false;
	}

	for (attacked = 0; attacked < numberOfPlayers; attacked++)
	{
		if (attacked != attacker && (distanceArray[attacker][attacked] == 0 || distanceArray[attacker][attacked] == 1))
		{
			playerInfo[attacked].canAttack = true;
		}
	}

	printf("Select a player to attack:\n");
	for(i = 0; i < numberOfPlayers; i++)
	{
		if(playerInfo[i].canAttack == true)
		{
			printf("Type %d to attack player %d", i+1, i+1);
		}
	}
	scanf("%d", &attackedSelected);


	while (playerInfo[attackedSelected].canAttack != true) {
		printf("Select a player to attack:\n");
		for(i = 0; i < numberOfPlayers; i++)
		{
			if(playerInfo[i].canAttack == true)
			{
				printf("Type %d to attack player %d", i+1, i+1);
			}
		}
		scanf("%d", &attackedSelected);
	}

	if (playerInfo[attackedSelected].strength <= 70)
	{
		playerInfo[attackedSelected].lifePoints = playerInfo[attackedSelected].lifePoints - (0.5 * playerInfo[attacker].strength);
	} else {
		playerInfo[attacker].lifePoints = playerInfo[attacker].lifePoints - (0.3 * playerInfo[attackedSelected].strength);
	}
	//nothing here ethier
	return;
	return;
}
void distantAttack(struct player playerInfo[6], int distanceArray[6][6], int attacker, int numberOfPlayers)
{

}
void magicAttack(struct player playerInfo[6], int numberOfPlayers, int currentPlayer)
{
	int i, attackedPlayer;
	for (i = 0; i < numberOfPlayers; i++)
	{
		if (i != currentPlayer)
		{
			printf("Type %d to attack player %d\n", i+1, i+1);
		}
	}
	scanf("%d", &attackedPlayer);
	attackedPlayer--;
	playerInfo[attackedPlayer].lifePoints = (0.5 * playerInfo[currentPlayer].magic) + (0.2 * playerInfo[currentPlayer].smartness);
//	((0.5 * Magic Skills of attacker player) + (0.2 * Smartness of attacker player))
}

/*
 * The recursive function that traverses the board to find the slots at a predefined
 * distance from the current slot and place them in foundSlots.
 * Parameters:
 * 	reqDist: the required distance from the starting slot
 * 	currDist: the distance of the current slot from the starting slot
 * 	currSlot: a pointer to the current slot that is traversed
 * 	foundSlots: the array of slots that are at a required distance from the starting slot
 * 	count: pointer to an integer representing the number of slots that are found to be at a required distance from the starting slot
 * 	explored: matrix indicating for each slot at row x and column y has been traversed (true) or not (false)
 */
void findSlots(int reqDist, int currDist,  struct slot * currSlot, struct slot * foundSlots, int * count,  bool explored[7][7]){



	//The base case: the current slot is at the required distance from the starting slot
	if(currDist == reqDist){
		//the current slot was not explored
		if(explored[currSlot->row][currSlot->column] == false){
			//The next availbale position (indicated by count) at foundSlots points to the current slot
			*(foundSlots + *count) = *currSlot;
			//the counter is incremented
			(*count)++;
			//the matrix of the explored slots set to true the element at the row and column of the current slot
			explored[currSlot->row][currSlot->column] = true;
		}
	}
	//The recursive call: the current slot is at a distance that is less than the required distance (more slots still have to be traversed)
	else{
		//if the current slot has the up slot != NULL (i.e. the slot is not in the first row)
		if(currSlot->up != NULL){
			//invokes function find slots incrementing the current Distance (currDist) and setting the current slot to the up slot
			findSlots(reqDist, currDist +1,  currSlot->up, foundSlots, count, explored);
		}
		//if the current slot has the right slot != NULL (i.e. the slot is not in the last column)
		if(currSlot->right != NULL){
			//invokes function find slots incrementing the current Distance (currDist) and setting the current slot to the right slot
			findSlots(reqDist, currDist +1,  currSlot->right, foundSlots, count, explored);
		}
		//if the current slot has the down slot != NULL (i.e. the slot is not in the last row)
		if(currSlot->down != NULL){
			//invokes function find slots incrementing the current Distance (currDist) and setting the current slot to the down slot
			findSlots(reqDist, currDist +1,  currSlot->down, foundSlots, count, explored);
		}
		//if the current slot has the left slot != NULL (i.e. the slot is not in the first column)
		if(currSlot->left != NULL){
			//invokes function find slots incrementing the current Distance (currDist) and setting the current slot to the left slot
			findSlots(reqDist, currDist +1,  currSlot->left, foundSlots, count, explored);
		}

	}


}




// This prints the status of each player at the end of the game
void statusPrint(int numberOfPlayers, struct player playerInfo[6])
{
	printf("\n");
	int i;
	for (i = 0; i < numberOfPlayers; i++)
	{
		printf("%s (%s, %d)\n", playerInfo[i].name, playerInfo[i].type, playerInfo[i].lifePoints);
	}
	return;
}
