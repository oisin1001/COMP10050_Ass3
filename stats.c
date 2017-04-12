#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "crossfireOperations.h"


// This function prints the stats of each player
void printStats(int numberOfPlayers, struct player playerInfo[6])
{
	int i;
	for(i=0; i< numberOfPlayers; i++){
		printf("Player name: %s\n", playerInfo[i].name);
		printf("Player number: %d\n", i+1);
		printf("Player type: %s\n", playerInfo[i].type);
		printf("Luck: %d\n", playerInfo[i].luck);
		printf("Smartness: %d\n", playerInfo[i].smartness);
		printf("Strength: %d\n", playerInfo[i].strength);
		printf("Magic: %d\n", playerInfo[i].magic);
		printf("Dexterity: %d\n", playerInfo[i].dexterity);
		printf("Location: (%d, %d)\n", playerInfo[i].place->row, playerInfo[i].place->column);
	}
	return;
}



void invalidStatCheck(int numberOfPlayers, struct player playerInfo[6]){
	int i;
	// If any of the stats are outside of the limit (0, 100), then I reset them to the closest value e.g. either 0 or 100
	for(i = 0; i < numberOfPlayers; i++)
	{
		if (playerInfo[i].strength > 100)
		{
			playerInfo[i].strength = 100;
		}
		if (playerInfo[i].strength < 0)
		{
			playerInfo[i].strength = 0;
		}
		if (playerInfo[i].dexterity < 0)
		{
			playerInfo[i].strength = 0;
		}
		if (playerInfo[i].magic > 100)
		{
			playerInfo[i].magic = 100;
		}
	}
}

// This function changes the stats of the player, depending on which slot they move to
void changeStats(struct slots slotsArray[20], struct player playerInfo[6], int n1)
{
	int  j, HoldForStats;
	for(j=0;j<n1;j++)//counts through all slots
	{
		if(slotsArray[j].playerNum+1 != 0)//if a player is found in a slot, proceed
		{
			if(strcmp(slotsArray[j].Slot_type, "Hill") ==0)// if the slot is hills then do check , if not keep going
			{
				HoldForStats=slotsArray[j].playerNum;//Not sure if the slotsArray[j].playerNum works , but it is meant to read the player number that is in that slot and change only their stats
				if(playerInfo[HoldForStats].dexterity <50)
				{
					playerInfo[HoldForStats].strength = playerInfo[HoldForStats].strength -10;
				}
				if(playerInfo[HoldForStats].dexterity >=60)
				{
					playerInfo[HoldForStats].strength = playerInfo[HoldForStats].strength +10;
				}

			}


			if(strcmp(slotsArray[j].Slot_type, "City") ==0)//if slot is city then do check, if not loop and increment
			{
				HoldForStats=slotsArray[j].playerNum;
				if(playerInfo[HoldForStats].smartness <=50)
				{
					playerInfo[HoldForStats].dexterity = playerInfo[HoldForStats].dexterity -10;
				}

				if(playerInfo[HoldForStats].smartness >60)
				{
					playerInfo[HoldForStats].magic = playerInfo[HoldForStats].magic +10;
				}

			}
		}
	}
	return;
}
