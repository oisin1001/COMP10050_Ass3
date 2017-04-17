/*
 * boardCreation.c

 *
 *  Created on: 29 Mar 2017
 *      Author: liliana
 */


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "crossfireOperations.h"


/*
 * This function traverses the board to find a slot at a predefined
 * position (row, column)
 * Parameters:
 * 	row: the row in which the desired slot is located
 * 	column: the column in which the desired slot is located
 * 	initialSlot: the slot from which the slot search should start
 */
void findDistance(int rowA, int columnA, int rowB, int columnB, int distanceArray[6][6], bool foundDistance[6][6], int player1, int player2)

{
	if(foundDistance[player1][player2] != true && player1 != player2)
	{
		int numMoves = 0;
		bool found = false;
		//current slot
//		struct slot * currentSlot = initialSlot;

//		printf("\nFunction reachDesiredElement invoked\n");

		//prints the column and the row of the initial slot from which the search starts
//		printf("Initial slot (%d, %d) -> \n", rowA, columnA);


		//while the slot is not found
		while(found == false){

			//if the row of the current slot is > of the row of the desired slot,
			//we move up
			if(rowB > rowA){
				//the current slot now points to the slot one row up
		//		currentSlot = currentSlot->up;
				rowA++;
				//prints the column and the row of the current slot
//				printf("Current slot (%d, %d) -> \n",rowA,columnA);
				numMoves++;
			}
			//if the row of the current slot is < of the row of the desired slot,
			//we move down
			if(rowB < rowA){
				//the current slot now points to the slot one row down
				rowA--;
				//prints the row and the column of the current slot
//				printf("Current slot (%d, %d) -> \n",rowA,columnA);
				numMoves++;
			}
			//if the column of the current slot is > of the column of the desired slot,
			//we move left
			if(columnB > columnA){	

				//the current slot now points to the slot one column left
				columnA++;
				//prints the row and the column of the current slot
//				printf("Current slot (%d, %d) -> \n",rowA,columnA);
				numMoves++;
			}

			//if the column of the current slot is < of the column of the desired slot,
			//we move right
			if(columnB < columnA){

				//the current slot now points to the slot one column right
				columnA--;
				//prints the row and the column of the current slot
//				printf("Current slot (%d, %d) -> \n",rowA,columnA);
				numMoves++;

			}
			//if the current slot is at a column and a row equal to the desired column and row, respectively
			// we found the slot
			if(columnA == columnB && rowA == rowB){
//				printf("Found\n");
				found = true;

			}

		}

//		printf("Total number of moves: %d\n\n", numMoves);
		foundDistance[player1][player2] = true;
		foundDistance[player2][player1] = true;
		distanceArray[player1][player2] = numMoves;
		distanceArray[player2][player1] = numMoves;
	}
	//returns the found slot
	return;
}
