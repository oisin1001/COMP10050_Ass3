#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "crossfireOperations.h"


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