#pragma once
#ifndef DATA_MODULE_H
#define DATA_MODULE_H

void saveConfigToFile(int configChoice, const char* message);
void loadConfigFromFile(int* configChoice, char* message, int max_length);

#endif // DATA_MODULE_H
