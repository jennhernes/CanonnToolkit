#ifndef TOOLKIT_H
#define TOOLKIT_H

double CalculateBearing(double Lat1, double Lat2, double Lon1, double Lon2);

void DecryptCipherText(char *Result, char *text, int length, char *alphabet);

void SwapNumbersToAlphabet(char *Result, char *given);

void ConvertBinaryToAscii(char *Result, char *given);

void ConvertOctToAscii(char *Result, char *given);

void ConvertDecimalToAscii(char *Result, char *given);

void ConvertHexToAscii(char *Result, char *given);

void ConvertMorseToAscii(char *Result, char *given);

#endif