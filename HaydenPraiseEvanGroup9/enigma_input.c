#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enigma_encrypt.h"
#include "enigma_input.h"

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void getInputMessage(char* inputMessage, int* messageLength) {
    int i = 0;

    printf("Enter message: ");

    // Get user message. Max size is set by MAX_MESSAGE_LENGTH
    fgets(inputMessage, MAX_MESSAGE_LENGTH, stdin);

    // Remove the trailing newline character, if present
    inputMessage[strcspn(inputMessage, "\n")] = '\0';

    //Go through all the entered chars and format them correctly
    while (inputMessage[i] != '\0' && i < MAX_MESSAGE_LENGTH) {
        // Replace spaces with X
        if (inputMessage[i] == ' ')
            inputMessage[i] = 'X' - 65;

        // Convert lower case letters to upper case and shift A-Z range to between 0 and 25 where A=0, B=1, C=2, etc
        if (inputMessage[i] >= 97 && inputMessage[i] <= 122)
            inputMessage[i] -= 97;

        // Shift to A-Z range to between 0 and 25 where A = 0, B = 1, C = 2, etc
        if (inputMessage[i] >= 65 && inputMessage[i] <= 90)
            inputMessage[i] -= 65;

        // Test to make sure all chars are now only in range A-Z. If they are not, then quit
        if (inputMessage[i] < 0 || inputMessage[i] > 25) {
            *messageLength = 0;
            return;
        }

        i++;
    }

    *messageLength = i;
}
