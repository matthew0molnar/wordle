/*
* Author:		Matthew Molnar
* File:			wordScore.s
* Date:			February 15, 2022
*
* Description:
*		This program will read from a file of all possible
*		guesses from the mobile game Wordle. It will then
*		count how many times each letter appears across
*		all of the possible words as well as what position
*		they appear in.
*/

#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b, char* A, char* B)		// Edited swap function to swap two sets of arrays at the same indexes
{
	int t = *a;
	char T = *A;
	*a = *b;
	*A = *B;
	*b = t;
	*B = T;
}

int partition(int arr[], int low, char high, char arr2[])	// Edited partition to take another array to be swapped in the swap function
{
	int pivot = arr[high];
	int i = (low - 1);

	for(int j = low; j <= high - 1; j++)
	{
		if(arr[j] < pivot)
		{
			i++;
			swap(&arr[i], &arr[j], &arr2[i], &arr2[j]);
		}
	}
	swap(&arr[i + 1], &arr[high], &arr2[i + 1], &arr2[high]);
	return(i + 1);
}

void quickSort(int arr[], int low, int high, char arr2[])		// Takes in two arrays, one being a numerical list used for sorting
{									// while the other is another array sorted in the same manner
	if(low < high)
	{
		int pi = partition(arr,low,high, arr2);

		quickSort(arr, low, pi - 1, arr2);
		quickSort(arr, pi + 1, high, arr2);
	}
}

int main()
{
	FILE *file;				// File of possible guesses.
	file = fopen("words.txt", "r");

	int letterCount[26] = {0};
	char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m',
	'n','o','p','q','r','s','t','u','v','w','x','y','z'};				// Avoids switch statement
	char word[6];
	int count = 0;
	while(fgets(word, 6, file) != NULL)		// Just learned all char arrays/strings need another index for \0
	{
		if(word[0] != '\n')			//  Checks if at end of line.
		{
			for(int i = 0; i < 5; i++)
			{	//printf("%c", word[i]);		// * Debug see if reading properly
				for(int j = 0; j < 26; j++)
				{
					if(word[i] == alphabet[j]) // Probably less efficient than switch statement
					{
						letterCount[j]++;
					}
				}
			}
			//printf("\n");					// *
		}
	}
	fclose(file);

	printf("Frequency of each letter:\n");
	for(int i = 0; i < 26; i++)
	{
		printf("%c: %d\n", alphabet[i], letterCount[i]);
	}

	// Sort letterCount then sort alphabet based on sorting of letterCount
	printf("Sorting...\n");								// Debugging to know if running/looks cool to non programmers
	quickSort(letterCount, 0, 25, alphabet);
	printf("Sorted List:\n");
	for(int i = 25; i > -1; i--)						// Sorted backwards so print backwards. Probably easy fix but idc rn
	{
		printf("%c: %d\n", alphabet[i], letterCount[i]);
	}


}
