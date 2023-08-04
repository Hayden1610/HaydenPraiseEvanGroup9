#define MAX_MESSAGE_LENGTH 100

struct Rotor {
    char rotorCurrentPosition;
    char rotorOffset;
    char ringPosition;
    char carryPosition;
    char leftToRight[26];
    char rightToLeft[26];
};

void plugboardEncode(char* inputMessage, int messageLength, char* outputMessage, char* plugboardConnections);
void rotorShift(struct Rotor* rotor, int shiftSize);
void initialiseRotor(struct Rotor* rotor, char* rotorConnections, char rotorOffset, char ringPosition, char carryPosition);
void initialisePlugboard(char* desiredPlugConnections, char* plugboardConnections);
char newLetter(char letter, struct Rotor* P1, struct Rotor* P2, struct Rotor* P3, struct Rotor* reflector);
void enigmaEncode(char* inputMessage, char* outputMessage, int messageLength, struct Rotor* P1, struct Rotor* P2, struct Rotor* P3, struct Rotor* reflector);