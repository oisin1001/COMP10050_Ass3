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
		printf("Location: (%d, %d)\n\n", playerInfo[i].place->row, playerInfo[i].place->column);
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

void playerdeath(int numberOfPlayers, struct player playerInfo[6])
{

	int i;
	for(i = 0; i < numberOfPlayers; i++)
	{
	 if (playerInfo[i].lifePoints <=0)
	  {
		 d[i]=Dead;
	  }
	}
}

void allalive(int numberOfPlayers, struct player playerInfo[6])
{
	int i,t=0;
	for(i = 0; i < numberOfPlayers; i++)
		{
		 if(d[i]==Dead)
		  {
			t=t+1;
		  }
		}
	if(t==(numberOfPlayers-1))
	{
		glados[1]=GG;
	}
	else
	{
		t=0;//reset it to 0 to make sure that it doesn't double count people across turns
	}
}

void changeStats(int numberOfPlayers, struct player playerInfo[6])
{
	int i;
	for(i = 0; i < numberOfPlayers; i++)//counts through all players
	{
		if(playerInfo[i].place->type == HILL)
		{
			if(playerInfo[i].dexterity <50)
			{
				playerInfo[i].strength = playerInfo[i].strength -10;
			}
			if(playerInfo[i].dexterity >=60)
			{
				playerInfo[i].strength = playerInfo[i].strength +10;
			}
			printf("Hill buff enabled for player %d\n", i+1);
		}
		if(playerInfo[i].place->type == CITY)
		{
			if(playerInfo[i].smartness <=50)
			{
				playerInfo[i].dexterity = playerInfo[i].dexterity -10;
			}

			if(playerInfo[i].smartness >60)
			{
				playerInfo[i].magic = playerInfo[i].magic +10;
			}
			printf("City buff enabled for player %d\n", i+1);
		}
	}
	return;
}
