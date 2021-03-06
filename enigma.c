#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>

#include "headers.h"

int main() {

	int alphSize, rotorCount, reflCount; // size of alphabet, number of rotors, number of reflectors
	int** rotorNotchDef; // notches of each rotor
	int** reflDef; // definitions of reflectors
	printf("SIMPLE ENIGMA SIMULATOR\nAuthor: Jakub Ochnik\n\n");
	printf("WARNING! Please note that in this program letters are only represented by numbers.\n Regular (a-z) letters are not supported yet.\n\n");
	printf("Enter the length of the numerical alphabet:\n");
	scanf("%d", &alphSize);
	printf("Enter the number of rotors:\n");
	scanf("%d", &rotorCount);

	rotorNotchDef = (int**)malloc(rotorCount * sizeof(int*));
	for (int i = 0; i < rotorCount; i++)
		rotorNotchDef[i] = NULL;

	int* rotorNotchesCount = (int*)malloc(rotorCount * sizeof(int));
	rotorAlphabet* rotor = (rotorAlphabet*)malloc(rotorCount * sizeof(rotorAlphabet));
	for (int i = 0; i < rotorCount; i++) {
		(rotor + i)->letter = (int*)malloc(alphSize * sizeof(int));
		(rotor + i)->regAlph = (int*)malloc(alphSize * sizeof(int));
		(rotor + i)->backAlph = (int*)malloc(alphSize * sizeof(int));
	}
	for (int i = 0; i < rotorCount; i++) {
		printf("\t --ROTOR %d--\nSpecify the initial position of rotor (letters separated by spaces):\n",i);
		for (int j = 0; j < alphSize; j++)
		{
			int rotorLetter;
			scanf("%d", &rotorLetter);
			(rotor + i)->regAlph[j] = j + 1;
			if (rotorLetter != j + 1)
				(rotor + i)->letter[j] = rotorLetter - (j + 1);
			else
				(rotor + i)->letter[j] = 0;
		}
		for (int j = 0; j < alphSize; j++) {
			int rotorLetter = (rotor + i)->regAlph[j];
			int x = j;
			for (int k = 0; k < alphSize; k++) {
				if ((rotor + i)->letter[k] + (rotor + i)->regAlph[k] == rotorLetter)
				{
					(rotor + i)->backAlph[j] = k - x;
					break;
				}
			}
		}
		printf("Enter the number of turnover letters (notches):\n");
		scanf("%d", &(rotorNotchesCount[i]));
		rotorNotchDef[i] = (int*)malloc(rotorNotchesCount[i] * sizeof(int));
		if(rotorNotchesCount[i]>0)
			printf("Enter turnover letters (separated by spaces):\n");
		for (int j = 0; j < rotorNotchesCount[i]; j++)
			scanf("%d", &(rotorNotchDef[i][j]));
	}
	printf("Enter the number of reflectors:\n");
	scanf("%d", &reflCount);
	reflDef = (int**)malloc(reflCount * sizeof(int));
	for (int i = 0; i < reflCount; i++)
		reflDef[i] = (int*)malloc(alphSize * sizeof(int));

	for (int i = 0; i < reflCount; i++) {
		printf("Enter the definition of reflector %d (letters separated by whitespaces):\n", i);
		for (int j = 0; j < alphSize; j++) {
			scanf("%d", &(reflDef[i][j]));
		}
	}

	int problemCount;
	printf("Enter the number of messages to encrypt:\n");
	scanf("%d", &problemCount);
	problem* params = (problem*)malloc(sizeof(problem));
	for (int i = 0; i < problemCount; i++) {
		params->rotInd = NULL;
		params->initPos = NULL;
	}
	int currentNumber;
	int index;
	for (int i = 0; i < problemCount; i++) {
		printf("\t--MESSAGE %d--\n",i);
		int z = 0;
		printf("Enter the number of rotors to use:\n");
		scanf("%d", &(params->rotCount));
		params->rotInd = (int*)malloc(params->rotCount * sizeof(int));
		params->initPos = (int*)malloc(params->rotCount * sizeof(int));
		while (z < params->rotCount * 2) {
			if (z % 2 == 0) {
				printf("Enter the index of rotor %d:\n",z/2);
				scanf("%d", &(params->rotInd[z / 2]));
			}
			else {
				printf("Enter the initial position of rotor %d:\n", z/2);
				scanf("%d", &(params->initPos[z / 2]));
			}
			z++;
		}
		printf("Enter the index of reflector:\n");
		scanf("%d", &(params->reflInd));
		params->num = (int*)malloc(10 * sizeof(int));
		printf("Enter a sequence of numbers to encrypt:\n");
		params->len = getAllocLineInput(params);

		printf("ENCODED MESSAGE %d:\n",i);
		// START OF ENCODING
		int* rotorStart = (int*)malloc(params->rotCount * sizeof(int));
		int rotorSteps[3] = { 0 };
		for (int l = 0; l < params->rotCount; l++)
			rotorStart[l] = params->initPos[l] - 1;
		for (int l = 0; l < params->len; l++) {
			rotateRotor(rotorStart, 1, 0, params->rotCount, rotorNotchDef, rotorNotchesCount, params->rotInd, rotorSteps, alphSize, rotor, params);
			currentNumber = params->num[l];
			// ROTORS:
			index = returnIndex(rotorStart, currentNumber - 1, 1, alphSize, rotor + params->rotInd[0]);
			for (int j = 1; j < params->rotCount; j++)
				index = returnIndex(rotorStart + j, index, 1, alphSize, rotor + params->rotInd[j]);
			// REFLECTOR:
			currentNumber = reflDef[params->reflInd][index] - 1;
			// ROTORS, SIGNAL PASSES IN REVERSE DIRECTION:
			for (int j = params->rotCount; j > 1; j--) {
				index = returnIndex(rotorStart + j - 1, currentNumber, 0, alphSize, rotor + params->rotInd[j - 1]);
				currentNumber = index;
			}
			// ENCODED LETTER:
			index = returnIndex(rotorStart, currentNumber, 0, alphSize, rotor + params->rotInd[0]) + 1;

			printf("%d ", index);
		}
		printf("\n");
		free(params->rotInd);
		free(params->initPos);
		free(params->num);
		free(rotorStart);
	}
	free(*rotorNotchDef);
	free(rotorNotchDef);
	free(rotorNotchesCount);
	free(rotor);
	free(*reflDef);
	free(reflDef);
	free(params);
}