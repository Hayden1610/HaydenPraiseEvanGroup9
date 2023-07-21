#define _CRT_SECURE_NO_WARNINGS 
#include "data_module.h"
#include <stdio.h>

void saveConfigToFile(int configChoice, const char* message) {
    FILE* file = fopen("enigma_config.txt", "w");
    if (file != NULL) {
        fprintf(file, "%d\n%s\n", configChoice, message);
        fclose(file);
    }
    else {
        printf("Failed to save configuration to file.\n");
    }
}

void loadConfigFromFile(int* configChoice, char* message, int max_length) {
    FILE* file = fopen("igottenlittleblackkidsplayingwitbigtoys.txt", "r");
    if (file != NULL) {
        fscanf(file, "%d", configChoice);
        fgetc(file); // Read newline character
        fgets(message, max_length, file);
        fclose(file);
    }
    else {
        printf("No previous configuration found.\n");
    }
}
