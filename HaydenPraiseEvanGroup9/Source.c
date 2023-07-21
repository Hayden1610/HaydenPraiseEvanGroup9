#include <stdio.h>
#include <string.h>
#include "input_module.h"
#include "encryption_module.h"
#include "data_module.h"
#include "output_module.h"

// Basic Enigma Machine Configuration
#define BASIC_ROTOR "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define BASIC_REFLECTOR "YRUHQSLDPXNGOKMIEBFZCWVJAT"
#define BASIC_ROTATION 0

// Advanced Enigma Machine Configuration
#define ADVANCED_ROTOR1 "EKMFLGDQVZNTOWYHXUSPAIBRCJ"
#define ADVANCED_ROTOR2 "AJDKSIRUXBLHWTMCQGZNPYFVOE"
#define ADVANCED_ROTOR3 "BDFHJLCPRTXVZNYEIWGAKMUSQO"
#define ADVANCED_REFLECTOR "YRUHQSLDPXNGOKMIEBFZCWVJAT"
#define ADVANCED_ROTATION1 0
#define ADVANCED_ROTATION2 0
#define ADVANCED_ROTATION3 0

int main(int argc, char* argv[]) {
    // Input Module (Hayden)
    int configChoice = getEnigmaConfigChoice(argc, argv);

    char message[256];
    getMessage(message, sizeof(message));

    // Data Storing Module (Data Team)
    saveConfigToFile(configChoice, message);

    // Encryption Module (Evan)
    if (configChoice == 1) {
        enigma_encrypt_message(message, BASIC_ROTOR, BASIC_ROTATION, NULL, 0, NULL, 0, BASIC_REFLECTOR);
    }
    else {
        enigma_encrypt_message(message, ADVANCED_ROTOR1, ADVANCED_ROTATION1, ADVANCED_ROTOR2, ADVANCED_ROTATION2, ADVANCED_ROTOR3, ADVANCED_ROTATION3, ADVANCED_REFLECTOR);
    }

    // Data Storing Module (Data Team)
    loadConfigFromFile(&configChoice, message, sizeof(message));

    // Output Module (Praise)
    displayEncryptedMessage(message);

    return 0;
}
