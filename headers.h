#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "mainStructures.h"

int getAllocLineInput(problem* str);
int mod(int value, int n);
int returnIndex(int* rotorStart, int index, int mode, int alphSize, rotorAlphabet* rotor);
int checkForNotch(int* rotorStart, int currRotorIndex, int** rotNotch, int* rotorNotchCount, int* rotInd, int alphSize, rotorAlphabet* rotor);
void rotateRotor(int* rotorStart, int selfRotate, int currRotorIndex, int rotorCount, int** rotNotches, int* rotorNotches, int* rotInd, int* rotorSteps, int alphSize, rotorAlphabet* rotor, problem* params);
