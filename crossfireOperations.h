/*
 * crossfireOperations.h
 *
 *  Created on: 29 Mar 2017
 *      Author: liliana
 */

#ifndef CROSSFIREOPERATIONS_H_
#define CROSSFIREOPERATIONS_H_



#endif /* CROSSFIREOPERATIONS_H_ */

enum slotTypes {CITY, HILL, LEVEL_GROUND} slotTypes; // enumeration for the type of slot

struct slot{
	//row number
	int row;
	//column number
	int column;

	// adjacent left slot
	struct slot *left;
	// adjacent right slot
	struct slot *right;
	// adjacent up slot
	struct slot *up;
	// adjacent down slot
	struct slot *down;

	enum slotTypes type;
//	char Slot_type[20];
}slot;

struct player
{
    char type[10];//type
    char name[30];//name
    int lifePoints;//number of life points (100 at the start of the game)
    int smartness;//smartness
    int strength;//strength
    int magic;//magic skills
    int luck;//luck
    int dexterity;//dexterity
	int location;//location of each player
	bool canAttack;
	struct slot *place;
};


struct slots
{
	int l;//for location i.e which slot 1-20
	char Slot_type[20];//whether the slot is level ground city or hill
	char player[20];//note what player is in the slot
	char playerNum;
};

struct slots slotsArray[20];

void selectType(int numberOfPlayers, struct player playerInfo[6]);
void statsForElf(struct player playerInfo[6], int i);
void statsForHuman(struct player playerInfo[6], int i);
void statsForOgre(struct player playerInfo[6], int i);
void statsForWizard(struct player playerInfo[6], int i);
int slotsAllocation(struct slots slotsArray[20], int numberOfPlayers, int i,struct player playerInfo[6], struct slot **board);
void moveSlots(struct slots slotsArray[20], struct player playerInfo[6], int numberOfPlayers);
void changeStats(struct slots slotsArray[20], struct player playerInfo[6], int n1);
void closestPlayer(int numberOfPlayers, struct player playerInfo[6], struct slots slotsArray[20], int n1);
void statusPrint(int numberOfPlayers, struct player PlayerInfo[6]);
void printStats(int numberOfPlayers, struct player playerInfo[6]);
void printSlots(int numberOfPlayers, struct slots slotsArray[20], int n1);
void invalidStatCheck(int numberOfPlayers, struct player playerInfo[6]);
/*
 * FUNCTIONS PROTOTYPES
 */

// NEW FUNCTIONS

void createBoard(int boardSize, struct slot **upLeft, struct slot **upRight, struct slot **downLeft, struct slot **downRight, struct slot **board);

/*
 * Functions getBoardSize and getDesiredElement
 * manage the interaction with the users
 */

//Asks the user to provide as input the size of the board
//Returns the size of the board
//int getBoardSize();

//Asks the user to insert the row and the column of the element
//she wants to find given a board of size equal to maxsize
//void getDesiredElement(int maxsize, int * row, int * col);

/*
 * Functions createBoard and reachDesiredElement
 * manage the creation and manipulation of the board
 */
/*
 * This function creates the board
 * Parameters:
 * 	boardSize: the size of the board
 * 	upLeft: pointer of pointer to slot at position (0, 0)
 * 	upRight: pointer of pointer to slot at position (0, size -1)
 * 	downLeft: pointer of pointer to slot at position (size -1, 0)
 * 	upLeft: pointer of pointer to slot at position (size - 1, size -1)
 */
//void createBoard(int boardSize, struct slot **upLeft, struct slot **upRight, struct slot **downLeft, struct slot **downRight);

/*
 * This function traverses the board to find a slot at a predefined
 * position (row, column)
 * Parameters:
 * 	row: the row in which the desired slot is located
 * 	column: the column in which the desired slot is located
 * 	initialSlot: the slot from which the slot search should start
 */
//void reachDesiredElement(int row, int column, struct slot * initialSlot);
