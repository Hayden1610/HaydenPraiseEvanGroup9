#define _CRT_SECURE_NO_WARNINGS
#include "enigma_encrypt.h"
#include <stdlib.h>

void plugboardEncode(char* inputMessage, int messageLength, char* outputMessage, char* plugboardConnections) {
    int i = 0;
    for (i = 0; i < messageLength; i++) {
        outputMessage[i] = plugboardConnections[inputMessage[i]];
    }
}

void rotorShift(struct Rotor* rotor, int shiftSize) {
    char tempArray[26] = { 0 };
    int i = 0;
    int j = 0;

    // Create a temp copy of the rotor connections so that it can be shifted
    memcpy(&tempArray, &rotor->leftToRight, 26 * sizeof(char));

    for (i = 0; i < 26; i++) {
        // Corrects the index when the shift wraps over the array
        if (i + shiftSize < 0) {
            j = (i + shiftSize) + 26;
        }
        else if (i + shiftSize > 25) {
            j = (i + shiftSize) - 26;
        }
        else  j = i + shiftSize;

        rotor->leftToRight[i] = tempArray[j];

        // Adjust for the output of rotor
        if (rotor->leftToRight[i] - shiftSize > 25) {
            rotor->leftToRight[i] = (rotor->leftToRight[i] - shiftSize) - 26;
        }
        else if (rotor->leftToRight[i] - shiftSize < 0) {
            rotor->leftToRight[i] = (rotor->leftToRight[i] - shiftSize) + 26;
        }
        else rotor->leftToRight[i] -= shiftSize;
    }

    // Convert from the Left to Right array to the Right to Left array
    for (i = 0; i < 26; i++) {
        rotor->rightToLeft[rotor->leftToRight[i]] = i;
    }

    // Update the current position variable in the rotor struct
    if (rotor->rotorCurrentPosition + shiftSize > 25) {
        rotor->rotorCurrentPosition = (rotor->rotorCurrentPosition + shiftSize) - 26;
    }
    else if (rotor->rotorCurrentPosition + shiftSize < 0) {
        rotor->rotorCurrentPosition = (rotor->rotorCurrentPosition + shiftSize) + 26;
    }
    else rotor->rotorCurrentPosition += shiftSize;
}

void initialiseRotor(struct Rotor* rotor, char* rotorConnections, char rotorOffset, char ringPosition, char carryPosition) {
    // Fill in the initial rotor struct with the provided parameters
    int i = 0;
    char initialOffset = 0;

    // Assign the rotor connections. A is stored as 0, B is stored as 1, Z is stored as 25, etc.
    // Connections should be provided as a string. Eg. "BGJKYU...." would map A to B, B to G, C to J, D to K, E to Y, and F to U etc.
    for (i = 0; i < 26; i++) {
        rotor->leftToRight[i] = rotorConnections[i] - 65; // Minus 65 converts from ASCII to a number from 0-25
    }

    // Convert from the Left to Right array to the Right to Left array
    for (i = 0; i < 26; i++) {
        rotor->rightToLeft[rotor->leftToRight[i]] = i;
    }

    // Set the offset, ring, and carry settings
    // These are all stored as 0-25 instead of A to Z for easier calcs during operation
    rotor->rotorOffset = rotorOffset - 65;
    rotor->ringPosition = ringPosition - 65;
    rotor->carryPosition = carryPosition - 65;
    rotor->rotorCurrentPosition = 0;

    // Calculate initial offset from the ring and offset settings
    if ((rotorOffset - ringPosition) < 0) {
        initialOffset = (rotorOffset - ringPosition) + 26;
    }
    else   initialOffset = (rotorOffset - ringPosition);

    // If there is an offset, apply it to the rotor
    if (initialOffset != 0) rotorShift(rotor, initialOffset);

    // Correct the rotor position variable as it will be wrong the first time due to the ring setting offset
    rotor->rotorCurrentPosition = rotorOffset - 65;
}

// P1 = Position 1 which is the leftmost rotor. P3 = Position 3 which is the rightmost rotor
char newLetter(char letter, struct Rotor* P1, struct Rotor* P2, struct Rotor* P3, struct Rotor* reflector) {
    char firstPass, reflected, secondPass;
    char carryPos;

    // Always shift the first rotor
    rotorShift(P3, 1);

    // Catch the case where carry position + 1 would overflow, i.e., where the carry notch is at Z
    if (P3->carryPosition + 1 > 25) carryPos = 0;
    else carryPos = P3->carryPosition + 1;

    // Shift middle rotor if carry notch engaged
    if (P3->rotorCurrentPosition == carryPos) {
        rotorShift(P2, 1);
    }
    // Double step condition - Shift both middle and leftmost rotor
    else if (P2->rotorCurrentPosition == P2->carryPosition) {
        rotorShift(P2, 1);
        rotorShift(P1, 1);
    }

    firstPass = P1->leftToRight[P2->leftToRight[P3->leftToRight[letter]]];
    reflected = reflector->leftToRight[firstPass];
    secondPass = P3->rightToLeft[P2->rightToLeft[P1->rightToLeft[reflected]]];

    return secondPass;
}

void enigmaEncode(char* inputMessage, char* outputMessage, int messageLength, struct Rotor* P1, struct Rotor* P2, struct Rotor* P3, struct Rotor* reflector) {
    int i = 0;

    // Pass each input letter through the rotors and store it in the output array
    for (i = 0; i < messageLength; i++) {
        outputMessage[i] = newLetter(inputMessage[i], P1, P2, P3, reflector);
    }
}

void initialisePlugboard(char* desiredPlugConnections, char* plugboardConnections) {
    int i = 0;

    // Initialise all connections to be a normal passthrough. E.g., A to A, B to B, C to C, etc.
    // A is stored as 0, B is stored as 1, Z is stored as 25, etc.
    for (char x = 0; x < 26; x++) {
        plugboardConnections[x] = x;
    }

    // Plug Settings are in the format "AH,JI,FY"
    // This means A is connected to H and H is connected to A, J=I and I=J, etc.
    while (desiredPlugConnections[i] != '\0') {
        if (desiredPlugConnections[i] == ',') {
            i++;
        }
        else {
            plugboardConnections[desiredPlugConnections[i] - 65] = desiredPlugConnections[i + 1] - 65;
            plugboardConnections[desiredPlugConnections[i + 1] - 65] = desiredPlugConnections[i] - 65;
            i += 2;
        }
    }
}
