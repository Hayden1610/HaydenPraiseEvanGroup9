#pragma once
#ifndef ENCRYPTION_MODULE_H
#define ENCRYPTION_MODULE_H

char enigma_encrypt_char(char c, const char* rotor, int rotation);
void enigma_encrypt_message(char* message, const char* rotor1, int rotation1, const char* rotor2, int rotation2, const char* rotor3, int rotation3, const char* reflector);

#endif // ENCRYPTION_MODULE_H

