/*
* Author:		Matthew Molnar
* File:			wordEff2.c
* Date:			February 24, 2022
*
* Description:
*		Re-made version of wordEff.c since the last one magically got deleted when trying to compile.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void swap(double* a, double* b, char* A[], char* B[])
{
        int t = *a;
        char* T = *A;
        *a = *b;
        *A = *B;
        *b = t;
        *B = T;
}

int partition(double arr[], int low, char high, char* arr2[])
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

void quickSort(double arr[], int low, int high, char* arr2[])
{
        if(low < high)
        {
                int pi = partition(arr,low,high, arr2);

                quickSort(arr, low, pi - 1, arr2);
                quickSort(arr, pi + 1, high, arr2);
        }
}

double score(int arr[])
{
	float sum = 0.0;
	float sd = 0.0;
	float mean;
	for(int i = 0; i < 19; i++)
	{
		sum += arr[i];
	}
	mean = sum / 19;
	for(int i = 0; i < 19; i++)
	{
		sd += pow(arr[i] - mean, 2);
	}

	return sqrt(sd / 19);
}

int relation(char guess[6], char word[6])
{
	int X = 0;
	int O = 0;
	int $ = 0;
	for(int i = 0; i < 5; i++)
	{
		if(guess[i] == word[i])
		{
			$++;
		}
	}
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 5 ; j++)
		{
			if(i != j)
			{
				if(guess[i] == word[j])
				{
					O++;
				}
			}
		}
	}

	X = 5 - (O+$);
	int rel = 1000 + (X*100) + (O*10) + $;

	switch(rel)
	{
		case 1500:
			return 0;	// _XXXXX
		case 1401:
			return 1;	// _XXXX$
		case 1410:
			return 2;	// _XXXXO
		case 1311:
			return 3;	// _XXXO$
		case 1302:
			return 4;	// _XXX$$
		case 1320:
			return 5;	// _XXXOO
		case 1212:
			return 6;	// _XXO$$
		case 1221:
			return 7;	// _XXOO$
		case 1203:
			return 8;	// _XX$$$
		case 1230:
			return 9;	// _XXOOO
		case 1122:
			return 10;	// _XOO$$
		case 1113:
			return 11;	// _XO$$$
		case 1131:
			return 12;	// _XOOO$
		case 1104:
			return 13;	// _X$$$$
		case 1140:
			return 14;	// _XOOOO
		case 1050:
			return 15;	// _OOOOO
		case 1041:
			return 16;	// _OOOO$
		case 1032:
			return 17;	// _OOO$$
		case 1023:
			return 18;	// _OO$$$
		case 1014:
			return 19;	// _O$$$$
		case 1005:
			return 20;	// _$$$$$
	}

	printf("Error finding relation");
	exit(1);
}

int main()
{
        FILE *file;
        file = fopen("words.txt", "r");

	char** gssArr = (char**)malloc(12972 * sizeof(char*));
	for(int i = 0; i < 12972; i++)
	{
		gssArr[i] = (char*)malloc(5 * sizeof(char));
	}

        char word[6];
	int i = 0;
	while(fgets(word,6,file) != NULL)
	{
		if(word[0] != '\n')
		{
			for(int j = 0; j < 5; j++)
			{
				printf("%c", word[j]);
				gssArr[i][j] = word[j];
			}
			printf("\n");
		}
	}
        fclose(file);

	double* scores = (double*)malloc(12972 * sizeof(double));

	for(int i = 0; i < 12972; i++)
	{
		int rel[20] = {0};
		for(int j = 0; j < 12972; j++)
		{
			int index = relation(gssArr[i],gssArr[j]);
			rel[index] += 1;
		}
		scores[i] = score(rel);
	}

	quickSort(scores,0,12971,gssArr);
	for(int i = 0; i < 12972; i++)
	{
		printf("%s: %f\n", gssArr[i], scores[i]);
	}

	free(gssArr);
	free(scores);
}











