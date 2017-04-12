#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "crossfireOperations.h"


void selectType(int numberOfPlayers, struct player playerInfo[6]) {
	int i;
	for(i=0; i<numberOfPlayers; i++)
	{
		int typeNum;
		printf("\nPlayer %d, please select a type:\n", i+1);
		printf("To select \"Elf\", type 1.\nTo select \"Human\", type 2.\nTo select \"Ogre\", type 3.\nTo select \"Wizard\", type 4.\n");
		scanf("%d", &typeNum);
		// I use a switch statement to call different functions depending on the player type
		switch(typeNum) {
			case 1:
				statsForElf(playerInfo, i);
				break;
			case 2:
				statsForHuman(playerInfo, i);
				break;
			case 3:
				statsForOgre(playerInfo, i);
				break;
			case 4:
				statsForWizard(playerInfo, i);
				break;
			default:
				// If the user doesn't enter a valid value, the loop repeats itself again
				printf("That is not a valid entry. Please try again.\n");
				i--;
				break;
		}
	}
	return;
}

// If the player is an elf, we use this function to allocate values
void statsForElf(struct player playerInfo[6], int i)
{
	strcpy(playerInfo[i].type, "Elf");
	// We use the modulus and rand() to assign random values to each player
	playerInfo[i].luck = rand() % 41 + 60;
	playerInfo[i].smartness = rand() % 31 + 70;
	playerInfo[i].strength = rand() % 51;
	playerInfo[i].magic = rand() % 31 + 50;
	playerInfo[i].dexterity = rand() %101;
	printf("Enter the player name:\n");
	scanf("%s", playerInfo[i].name);
	// All players start with 100 lifepoints
	playerInfo[i].lifePoints = 100;
	return;
}

void statsForHuman(struct player playerInfo[6], int i) {
	strcpy(playerInfo[i].type, "Human");
	int combo = 301;
	while (combo >= 300)
	{
		playerInfo[i].luck = rand() % 101;
		playerInfo[i].smartness = rand() % 101;
		playerInfo[i].strength = rand() % 101;
		playerInfo[i].magic = rand() % 101;
		playerInfo[i].dexterity = rand() %101;
		// The luck, smartness, strength and magic must be less than or equal to 300
		// If it isn't, I generate new values for luch, smartness, strength and magic
		combo = playerInfo[i].luck + playerInfo[i].smartness + playerInfo[i].strength + playerInfo[i].magic+ playerInfo[i].dexterity;
		// All players start with 100 lifepoints
		playerInfo[i].lifePoints = 100;
	}
	printf("Enter the player name:\n");
	scanf("%s", playerInfo[i].name);
	return;
}

void statsForOgre(struct player playerInfo[6], int i) {
	strcpy(playerInfo[i].type, "Ogre");
	int combo = 51;
	while (combo > 50)
	{
		playerInfo[i].luck = rand() % 51;
		playerInfo[i].smartness = rand() % 21;
		combo = playerInfo[i].luck + playerInfo[i].smartness;
	}
	playerInfo[i].dexterity = rand() %21 +80;
	playerInfo[i].strength = rand() % 21 + 80;
	playerInfo[i].magic = 0;
	printf("Enter the player name:\n");
	scanf("%s", playerInfo[i].name);
	// All players start with 100 lifepoints
	playerInfo[i].lifePoints = 100;
	return;
}


void statsForWizard(struct player playerInfo[6], int i) {
	strcpy(playerInfo[i].type, "Wizard");
	playerInfo[i].luck = rand() % 51 + 50;
	playerInfo[i].smartness = rand() % 11 + 90;
	playerInfo[i].strength = rand() % 51;
	playerInfo[i].magic = rand() % 81;
	playerInfo[i].dexterity = rand() %101;
	printf("Enter the player name:\n");
	scanf("%s", playerInfo[i].name);
	// All players start with 100 lifepoints
	playerInfo[i].lifePoints = 100;
	return;
}

