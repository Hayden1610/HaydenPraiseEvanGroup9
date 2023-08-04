#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enigma_input.h"
#include "enigma_encrypt.h"
#include "enigma_output.h"

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    // For Unix-like systems (Linux, macOS, etc.)
    system("clear");
#endif
}

// Function to print the menu options
void printMenu() {
    printf("\n===== Enigma Keyboard Message =====\n");
    printf("1. Encrypt Message\n");
    printf("2. Exit\n");
    printf("====================================\n");
    printf("Enter your choice (1 or 2): ");
}

int main(int argc, char* argv[]) {
    char inputMessage[MAX_MESSAGE_LENGTH] = { 0 };
    char outputMessage[MAX_MESSAGE_LENGTH] = { 0 };
    char plugboardConnections[26];
    int messageLength;

    struct Rotor rI, rII, rIII, rIV, rV;
    struct Rotor reflectorB, reflectorC;

    if (argc != 2) {
        printf("Usage: %s <configuration>\n", argv[0]);
        printf("Please provide a valid configuration (B or C) as the command-line argument.\n");
        return -1;
    }

    char choice;

    while (1) {
        clearScreen();
        printMenu();
        int retval2 = scanf(" %c", &choice);
        clearInputBuffer();
        switch (choice) {
        case '1':
            // Set the configuration
            char configuration = argv[1][0];


            if (configuration == 'B') {
                initialiseRotor(&rI, "EKMFLGDQVZNTOWYHXUSPAIBRCJ", 'A', 'A', 'Q');
                initialiseRotor(&rII, "AJDKSIRUXBLHWTMCQGZNPYFVOE", 'A', 'A', 'E');
                initialiseRotor(&rIII, "BDFHJLCPRTXVZNYEIWGAKMUSQO", 'A', 'A', 'V');
                initialiseRotor(&rIV, "ESOVPZJAYQUIRHXLNFTGKDCMWB", 'A', 'A', 'J');
                initialiseRotor(&rV, "VZBRGITYUPSDNHLXAWMJQOFECK", 'A', 'A', 'Z');
                initialiseRotor(&reflectorB, "YRUHQSLDPXNGOKMIEBFZCWVJAT", 'A', 'A', 'A');
            }
            else if (configuration == 'C') {
                initialiseRotor(&rI, "RDOBJNTKVEHMLFCWZAXGYIPSUQ", 'A', 'A', 'R');
                initialiseRotor(&rII, "FNGZHWKVXQAYBJTOUMLCPDRSEI", 'A', 'A', 'F');
                initialiseRotor(&rIII, "LEYJVCNIXWPBQMDRTAKZGFUHOS", 'A', 'A', 'W');
                initialiseRotor(&rIV, "AFNIRLBSQWVXGUZDKMTPCOYJHE", 'A', 'A', 'K');
                initialiseRotor(&rV, "ZJWULGHRACQDNTKEVOSFYMXBIP", 'A', 'A', 'A');
                initialiseRotor(&reflectorC, "IMETCGFRAYSQBZXWLHKDVUPOJN", 'A', 'A', 'A');
            }
            else {
                printf("Invalid configuration. Please provide 'B' or 'C' as the command-line argument.\n");
                return -1;
            }

            // Setup plugboard connections
            initialisePlugboard("AA,BB", plugboardConnections);

            // Get input text and length
            getInputMessage(inputMessage, &messageLength);

            // Check for a valid message
            if (messageLength == 0) {
                printf("Unexpected character entered. Only A to Z are allowed\n");
                continue;
            }

            // Save a copy of the input message for later use
            char inputCopy[MAX_MESSAGE_LENGTH];
            strcpy(inputCopy, inputMessage);

            // First pass through Plugboard
            plugboardEncode(inputMessage, messageLength, outputMessage, plugboardConnections);

            // Pass through enigma rotors
            enigmaEncode(outputMessage, outputMessage, messageLength, &rI, &rII, &rIII, configuration == 'B' ? &reflectorB : &reflectorC);

            // Second pass through plugboard
            plugboardEncode(outputMessage, messageLength, outputMessage, plugboardConnections);

            printf("Output Message:\t");
            for (int i = 0; i < messageLength; i++) {
                printf("%c", outputMessage[i] + 'A');
            }
            printf("\n");

            char saveOutput;
            printf("Do you want to save the output to a text file? (Y/N): ");
            int retval3 = scanf(" %c", &saveOutput);
            clearInputBuffer();
            if (saveOutput == 'Y' || saveOutput == 'y') {
                saveToFile(inputCopy, outputMessage, messageLength, "AA,BB", "ROTOR SETTINGS"); // Change "AA,BB" and "ROTOR SETTINGS" accordingly
                printf("Output saved to a text file.\n");
            }
            break;

        case '2':
            printf("Exiting the Enigma program.\n");
            return 0;

        default:
            printf("Invalid choice. Please enter 1 or 2.\n");
        }
    }

    return 0;
}