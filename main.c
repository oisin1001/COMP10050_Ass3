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
	int i, numberOfPlayers = 0, n1;

	while (numberOfPlayers < 2 || numberOfPlayers > 6)
	{
		//Here the user enters the number of players in the game
		printf("How many players are playing today?\nPlease enter a number between 2 and 6\n");
		scanf("%d", &numberOfPlayers);
	}
	struct player playerInfo[numberOfPlayers];

	// This functions lets the user select a type and name, and assigns random values for the attributes (using details from the assignment document)
	selectType(numberOfPlayers, playerInfo);

	// This function prints the attributes for each player
	printf("-------Player Stats-------\n");
	printStats(numberOfPlayers, playerInfo);

	// This function allocates the slots, and calls the printSlots function to print the slots
	n1 = slotsAllocation(slotsArray, numberOfPlayers,i,playerInfo);

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
	statusPrint(numberOfPlayers, playerInfo);

	return 0;
}

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
	playerInfo[i].magic = rand() % 28 + 51;
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
	playerInfo[i].strength = rand() % 20 + 80;
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
	playerInfo[i].strength = rand() % 21;
	playerInfo[i].magic = rand() % 81;
	playerInfo[i].dexterity = rand() %101;
	printf("Enter the player name:\n");
	scanf("%s", playerInfo[i].name);
	// All players start with 100 lifepoints
	playerInfo[i].lifePoints = 100;
	return;
}

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
		printf("Dexterity: %d\n\n", playerInfo[i].dexterity);
	}
	return;
}

// This creates the slots, and places players in each slot
int slotsAllocation(struct slots slotsArray[20], int numberOfPlayers, int i, struct player playerInfo[6])
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
	int i, j, HoldForStats;
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

// This function finds the closest player to the current player, and lets them attack that player
void closestPlayer(int numberOfPlayers, struct player playerInfo[6], struct slots slotsArray[20], int n1)
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
