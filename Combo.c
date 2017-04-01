/*
 * Main.c
 *
 *  Created on: 31 Mar 2017
 *      Author: Darragh
 */

// This was an early version of our program - before functions were added.
// main.c is the completed project

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int main(void)
{


	struct player
	{
	    char type[10];//type
	    char name[30];//name
	    int lifePoints;//life points
	    int smartness;//smartness
	    int strength;//strength
	    int magic;//magic skills
	    int luck;//luck
	    int dexterity;//dexterity
	    int location;
	};

//	Each player will be represented as a struct characterised by the fields
//	identifying the player (player type and player name), life points, and the fields
//	characterising the player capabilities (Smartness, Strength, Magic Skills, Luck and
//	Dexterity).

	srand(time(NULL));
	int i, typeNum, combo, numberOfPlayers, n1, j,pl,C1,C2, attackerLocation, attackedLocation, topNum, bottomNum, attackChoice, HoldForStats, attackedPlayer;
	struct player playerInfo[6];
	bool attackedLocationFound;

	printf("How many players are playing today?\n");
	scanf("%d", &numberOfPlayers);

	// This loop lets the user select a type, and assigns random values for the attributes (using details from the assignment document)
	for (i = 0; i < numberOfPlayers; i++)
	{
		printf("Select a type:\n");
		printf("To select \"Elf\", type 1.\nTo select \"Human\", type 2.\nTo select \"Ogre\", type 3.\nTo select \"Wizard\", type 4.\n\n");
		scanf("%d", &typeNum);
		switch(typeNum) {
			case 1:
				strcpy(playerInfo[i].type, "Elf");
				playerInfo[i].luck = rand() % 41 + 60;
				playerInfo[i].smartness = rand() % 31 + 70;
				playerInfo[i].strength = rand() % 51;
				playerInfo[i].magic = rand() % 31 + 50;
				playerInfo[i].dexterity = rand() %101;
				break;
			case 2:
				strcpy(playerInfo[i].type, "Human");
				combo = 301;
				while (combo >= 300)
				{
					playerInfo[i].luck = rand() % 101;
					playerInfo[i].smartness = rand() % 101;
					playerInfo[i].strength = rand() % 101;
					playerInfo[i].magic = rand() % 101;
					playerInfo[i].dexterity = rand() %101;
					// The luck, smartness, strength and magic must be less than or equal to 300
					// If it isn't, I generate new values for luck, smartness, strength and magic
					combo = playerInfo[i].luck + playerInfo[i].smartness + playerInfo[i].strength + playerInfo[i].magic+ playerInfo[i].dexterity;
				}
				break;
			case 3:
				strcpy(playerInfo[i].type, "Ogre");
				combo = 51;
				while (combo > 50)
				{
					playerInfo[i].luck = rand() %100;
					playerInfo[i].smartness = rand() %100;
					combo = playerInfo[i].luck + playerInfo[i].smartness;
					printf("Combo is %d\n", combo);
				}
				playerInfo[i].strength = rand() %20 + 80;
				playerInfo[i].dexterity = rand() %20 +80;
				playerInfo[i].magic = 0;
				break;
			case 4:
				strcpy(playerInfo[i].type, "Wizard");
				playerInfo[i].luck = rand() % 51 + 50;
				playerInfo[i].smartness = rand() % 11 + 90;
				playerInfo[i].strength = rand() % 21;
				playerInfo[i].magic = rand() % 81;
				playerInfo[i].dexterity = rand() %101;
				break;
		}
		printf("Enter the player name:\n");
		scanf("%s", playerInfo[i].name);
		// All players start with 100 lifepoints
		playerInfo[i].lifePoints = 100;
	}

	// This test loop prints the attributes for each player
	for(i=0; i< numberOfPlayers; i++){
		printf("luck: %d\n", playerInfo[i].luck);
		printf("smart: %d\n", playerInfo[i].smartness);
		printf("strength: %d\n", playerInfo[i].strength);
		printf("magic: %d\n\n", playerInfo[i].magic);
	}



	struct slots
	{
		int l;//for location i.e which tile 1-20
		char Slot_type[20];//whether the slot is level ground city or hill
		char player[20];//note what player is in the slot
		char playerNum;
	};
	struct slots slotsArray[20];

	int t, rnd;

	printf("how many slots would you like , please enter a number between %d and 20\n\n",numberOfPlayers);
	// allows the user to enter the amount of the slots they want with a max of 20
	scanf("%d", &n1);



	if(n1<numberOfPlayers)
	{
		printf("There must be at least %d Slots , one for each player \n\n", numberOfPlayers);
		printf("Please enter a number between %d and 20\n",numberOfPlayers);
		// allows user to enter again if they made a mistake the first time and entered an invalid number
		scanf("%d", &n1);

	}

	if(n1>20)
	{
		//secondary check  , less important than the n1<numberOfPlayers check, makes sure the number entered isn't too high
		printf("Please enter a number between %d and 20\n",numberOfPlayers);
		scanf("%d", &n1);

	}


	for(i=0;i<n1;i++)//for generating the slots themselves
	{
		//int j=0;
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
//		slotsArray[i].player = "_";
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
	}//playerInfo[i].name

	for(i = 0; i < n1; i++)//changed from playernum to n1 so as to only count the amount of slots present
	{
		// This line confused me when I was trying to sort out attack - just temporarily changing it back to l --- Oisin
		printf("Location is %d\n", slotsArray[i].l);//added a +1 to make slots start at 1 , simply aestheical change , non essential
		printf("Slot type is %s\n", slotsArray[i].Slot_type);
		if(strcmp(slotsArray[i].player, "_") != 0)// a check to say if there is no player present to print a differant message
		{
		printf("%s is here\n", slotsArray[i].player);
		}
		if(strcmp(slotsArray[i].player, "_") == 0)
		{
		printf("No Player present\n");
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





	// Movement
	for(pl=0;pl<numberOfPlayers;pl++)
	{
		printf("Player %d,You are curently at tile %d \nDo you wish to move, enter 1 to move , enter 2 to stay in current location and attack\n",playerInfo[pl].location, pl);
		scanf("%d",&C1);
		if(C1==1)
		{
			if (playerInfo[pl].location==n1)
			{
				printf("You can only move backwards\n");
				playerInfo[pl].location=playerInfo[pl].location-1;
				printf("Your new position is tile %d",playerInfo[pl].location);
			}
			if (playerInfo[pl].location==0)
			{
				printf("You can only move forwards");
				playerInfo[pl].location=playerInfo[pl].location+1;
				printf("Your new position is tile %d",playerInfo[pl].location);

			}
			else
			{
				printf("Enter 1 if you wish to move forward\nEnter 2 if you wish to move backwards");
				scanf("%d",&C2);

					if(C2==1)
					{
						playerInfo[pl].location=playerInfo[pl].location+1;
						printf("Your new position is tile %d",playerInfo[pl].location);
					}
					if(C2==2)
					{
						playerInfo[pl].location=playerInfo[pl].location-1;
						printf("Your new position is tile %d",playerInfo[pl].location);
					}
			}
		}
	}
	//changes player stats based on where they move ,
	for(j=0;j<n1;j++)//counts through all slots
	{
		if(slotsArray[j].playerNum+1 != 0)//if a player is found in a slot procede
		{
			if(strcmp(slotsArray[j].Slot_type, "Hill") ==0)// if the slot is hills then do check , if not keep going
			{
				HoldForStats=slotsArray[j].playerNum;//Not sure if the slotsArray[j].playerNum works , but it is meant to read the player number that is in that tile and change only their stats
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


	// find the closest player
	for (i = 0; i < numberOfPlayers; i++)
	{
		// I use the boolean attackedLocationFound so I don't trigger later-on loops when I already have an answer
		attackedLocationFound = false;
		// I store the attackers location for future reference
		attackerLocation = playerInfo[i].location;
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
		printf("Do you want to attack player %d?\nType 1 to attack.\nType 2 to not attack.\n", (attackedPlayer+1));
		scanf("%d", &attackChoice);
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

	for (i = 0; i < numberOfPlayers; i++)
	{
		printf("%s (%s, %d)\n", playerInfo[i].name, playerInfo[i].type, playerInfo[i].lifePoints);
	}

	return 0;
}
