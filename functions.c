#include "headers.h"
#include <stdlib.h>
#include <stdio.h>

int getAllocLineInput(problem* str) {
	int z = 0;
	int n = 2;
	int actSize = 10;
	while (scanf("%d", &(str->num[z])) != EOF) {
		if (z + 1 > actSize - 1)
		{
			int* tempTab = (int*)realloc(str->num, n * 10 * sizeof(int));
			if (tempTab != NULL)
				str->num = tempTab;
			actSize = n * 10;
			n++;
		}
		if (str->num[z] == 0)
			break;
		z++;
	}
	return z; //quantity of letters to code
}

int mod(int value, int n) {
	if (value < 0)
		value = n + value;
	else
		value %= n;
	return value;
}

int returnIndex(int* rotorStart, int index, int mode, int alphSize, rotorAlphabet* rotor) {
	int ind = 0;
	int movedPos = mod(*rotorStart + index, alphSize);
	if (mode == 1)
		ind = mod(index + rotor->letter[movedPos], alphSize);
	else
		ind = mod(index + rotor->backAlph[movedPos], alphSize);
	return ind;
}

int checkForNotch(int* rotorStart, int currRotorIndex, int** rotNotch, int* rotorNotchCount, int* rotInd, int alphSize, rotorAlphabet* rotor) {
	for (int i = 0; i < rotorNotchCount[rotInd[currRotorIndex]]; i++) {
		if (rotorStart[currRotorIndex] + 1 < alphSize)
		{
			if (rotor->regAlph[rotorStart[currRotorIndex] + 1] == rotNotch[rotInd[currRotorIndex]][i])
				return 1;
		}
		else {
			if (rotor->regAlph[0] == rotNotch[rotInd[currRotorIndex]][i])
				return 1;
		}
	}
	return 0;
}

void rotateRotor(int* rotorStart, int selfRotate, int currRotorIndex, int rotorCount, int** rotNotches, int* rotorNotches, int* rotInd, int* rotorSteps, int alphSize, rotorAlphabet* rotor, problem* params) {
	if (currRotorIndex + 1 < rotorCount && currRotorIndex < 2 && rotorSteps[currRotorIndex]>0) {
		int rotateNext = 0;
		if (checkForNotch(rotorStart, currRotorIndex, rotNotches, rotorNotches, rotInd, alphSize, rotor + params->rotInd[currRotorIndex])) {
			rotateNext = 1;
			selfRotate = 1;
		}
		if (selfRotate == 1)
			rotateRotor(rotorStart, rotateNext, currRotorIndex + 1, rotorCount, rotNotches, rotorNotches, rotInd, rotorSteps, alphSize, rotor, params);
	}
	if (selfRotate == 1 && currRotorIndex < 3 && currRotorIndex < rotorCount) {
		if (rotorStart[currRotorIndex] + 1 < alphSize)
			rotorStart[currRotorIndex]++;
		else
			rotorStart[currRotorIndex] = 0;
		rotorSteps[currRotorIndex]++;
	}
}