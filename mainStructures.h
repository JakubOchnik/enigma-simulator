typedef struct problem {
	int rotCount; // rotors quantity
	int* rotInd; // indexes of rotors
	int* initPos; // initial positions of rotors
	int  reflInd; // reflector index

	int len; // length of text to encode
	int* num; // text to encode
}problem;

typedef struct rotorAlphabet {
	int* letter; //special alphabet
	int* regAlph; //regular alphabet
	int* backAlph; //backwards alphabet
}rotorAlphabet;