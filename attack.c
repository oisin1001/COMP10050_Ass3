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

	return;
}


void findSlots(int reqDist, int currDist, struct slot * currSlot, struct slot * foundSlots, int * count, bool explored[7][7])
{
	if(currDist == reqDist){
		if(explored[currSlot->row][currSlot->column] == false){
			*(foundSlots + *count) = *currSlot;
			(*count)++;
			explored[currSlot->row][currSlot->column] = true;
		}
	}

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
