#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "crossfireOperations.h"


// This function finds the closest player to the current player, and lets them attack that player
/*void closestPlayer(int numberOfPlayers, struct player playerInfo[6], struct slots slotsArray[20], int n1)
{
	int i;
	// This boolean lets me check if I've already found the attacker. This saves processing time, as unnecessary lines of code are not used depending on the circumstances
	bool attackedLocationFound;
	int attackerLocation;
	int attackedLocation, attackChoice, attackedPlayer;
	// bottomNum and topNum are variables used to search through the array for the next closest player
	int bottomNum = attackerLocation - 1;
	int topNum = attackerLocation + 1;
	for (i = 0; i < numberOfPlayers; i++)
	{
		// If the player has already moved, they're not allowed to attack
		if (playerInfo[i].canAttack == true) {
			// I use the boolean attackedLocationFound so I don't trigger later-on loops when I already have an answer
			attackedLocationFound = false;
			attackerLocation = playerInfo[i].location;
			// I store the attackers location for future reference
			bottomNum = attackerLocation - 1;
			topNum = attackerLocation + 1;

			// This while loop repeats until it finds a slot with a player in it or reaches the end of the array of structs
			while(slotsArray[topNum].playerNum == -1 && slotsArray[bottomNum].playerNum == -1 && bottomNum >= 0 && topNum < n1 && attackedLocationFound == false)
			{
				bottomNum--;
				topNum++;
			}

			// If we reach the bottom of the array (if the bottomNum is less than 0), we increase topNum until we find a value for playerNum that isn't -1
			if (bottomNum < 0 && attackedLocationFound == false)
			{
				while (slotsArray[topNum].playerNum == -1)
				{
					topNum++;
				}
				attackedLocation = topNum;
				attackedLocationFound = true;
			}

			// If we reach the top of the array (if the topNum is less than 0), we decrease bottomNum until we find a value for playerNum that isn't -1
			if (topNum >= n1 && attackedLocationFound == false)
			{
				while (slotsArray[bottomNum].playerNum == -1)
				{
					bottomNum--;
				}
				attackedLocation = bottomNum;
				attackedLocationFound = true;
			}


			// If we haven't reached the top or bottom of the array and only the bottom playerNum is -1, we set the topNum as the attackedLocation
			if (slotsArray[bottomNum].playerNum == -1 && bottomNum >= 0 && topNum < n1 && attackedLocationFound == false)
			{
				attackedLocation = topNum;
			// If we haven't reached the top or bottom of the array and only the top playerNum is -1, we set the bottomNum as the attackedLocation
			} else if (slotsArray[topNum].playerNum == -1 && bottomNum >= 0 && topNum < n1 && attackedLocationFound == false) {
				attackedLocation = bottomNum;
			// If neither value is -1, we let the user choose which to attack
			} else if (bottomNum >= 0 && topNum < n1 && attackedLocationFound == false) {
				// Here the user chooses who to attack
				printf("Both opponents are equally close. Type 1 to attack player %d. Type 2 to attack player %d.\n", slotsArray[bottomNum].playerNum + 1, slotsArray[topNum].playerNum + 1);
				scanf("%d", &attackChoice);
				if (attackChoice == 1)
				{
					attackedLocation = bottomNum;
				}
				if (attackChoice == 2)
				{
					attackedLocation = topNum;
				}
			}
			attackedPlayer = slotsArray[attackedLocation].playerNum;

			// Start of actual attack sequence
			attackChoice = 0;
			printf("\nPlayer %d:\n", i+1);
			printf("Do you want to attack player %d (e.g. %s)?\nType 1 to attack.\nType 2 to not attack.\n", (attackedPlayer+1), playerInfo[attackedPlayer].name);
			scanf("%d", &attackChoice);
			// Here the user attacks - depending on their strength values, each player's life points may change
			if (attackChoice == 1)
			{
				if (playerInfo[attackedPlayer].strength <= 70)
				{
					playerInfo[attackedPlayer].lifePoints = playerInfo[attackedPlayer].lifePoints - (0.5 * playerInfo[attackedPlayer].strength);
				} else {
					playerInfo[i].lifePoints = playerInfo[i].lifePoints - (0.3 * playerInfo[attackedPlayer].strength);
				}
			}
		}
		else {
			// If the player has moved, they cannot attack
		printf("Player %d: you have moved slot, so you cannot attack\n", i+1);
	}
	}
	return;
}*/

void nearAttack(struct player playerInfo[6])
{
	//not much here yet
	return;
}
void distantAttack(struct player playerInfo[6])
{
	//nothing here ethier
	return;
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
