#include "input_module.h"
#include <stdio.h>
#include <stdlib.h>

int getEnigmaConfigChoice(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <config_choice>\n", argv[0]);
        exit(1);
    }

    int configChoice = atoi(argv[1]);
    if (configChoice != 1 && configChoice != 2) {
        printf("Invalid configuration choice. Please use 1 for Basic Enigma Machine or 2 for Advanced Enigma Machine.\n");
        exit(1);
    }

    return configChoice;
}

void getMessage(char* message, int max_length) {
    printf("Enter the message to be encrypted: ");
    fflush(stdin); // Clear input buffer
    fgets(message, max_length, stdin);

    // Remove newline character from fgets
    int len = (int)strlen(message);
    if (len > 0 && message[len - 1] == '\n') {
        message[len - 1] = '\0';
    }
}
