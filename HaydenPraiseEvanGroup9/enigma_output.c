#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enigma_output.h"
#include "enigma_encrypt.h"

void saveToFile(char* inputMessage, char* outputMessage, int messageLength, char* plugboardConnections, char* rotorSettings) {
    char filename[50];
    printf("Enter filename to save the output (without extension): ");
    int retval1 = scanf("%49s", filename); // Limit the input to 49 characters to leave space for the null terminator

    strcat(filename, ".txt");
    FILE* file = fopen(filename, "w");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "Input Message: ");
    for (int i = 0; i < messageLength; i++) {
        fprintf(file, "%c", inputMessage[i] + 'A');
    }
    fprintf(file, "\n");

    fprintf(file, "Output Message: ");
    for (int i = 0; i < messageLength; i++) {
        fprintf(file, "%c", outputMessage[i] + 'A');
    }
    fprintf(file, "\n");

    fprintf(file, "Plugboard Connections: %s\n", plugboardConnections);
    fprintf(file, "Rotor Settings: %s\n", rotorSettings);

    fclose(file);
}


