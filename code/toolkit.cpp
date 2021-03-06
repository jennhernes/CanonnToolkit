#include <math.h>
#include <cstring>

#define PI 3.141592653589793238463
#define DELIM " ,-"


double CalculateBearing(double lat1, double lon1, double lat2, double lon2) {
	double Result = 0;

	if (lat1 > 90 || lat2 > 90 || lat1 <= -90 || lat2 <= -90 ||
		lon1 > 180 || lon2 > 180 || lon1 <= -180 || lon2 <= -180) {
		Result = 0;

	} else {
		lat1 = lat1 * PI/180;
		lon1 = lon1 * PI/180;
		lat2 = lat2 * PI/180;
		lon2 = lon2 * PI/180;

		double Y = lon2 - lon1;
		double X = log(tan(PI/4 + lat2/2) / tan(PI/4 + lat1/2));

		Result = atan2(Y,X) * 180/PI;
	}

	return (Result);
}


// Stores the encrypted text into the first given char *
void EncryptCipherText(char *Result, char *text, int length, char *alphabet) {
	for (int i = 0; i < length; i++) {
		if ((text[i] - ASCII_OFFSET) >= 0 && 
			(text[i] - ASCII_OFFSET) < ALPHABET_LENGTH) {
			Result[i] = alphabet[(int)text[i] - ASCII_OFFSET];
		} else {
			Result[i] = text[i];
		}
	}
}


// Stores the decrypted text into the first given char *
void DecryptCipherText(char *Result, char *text, int length, char *alphabet) {
	for (int i = 0; i < length; i++) {
		if ((text[i] - ASCII_OFFSET) >= 0 && 
			(text[i] - ASCII_OFFSET) < ALPHABET_LENGTH) {
			int j = 0;
			while (TRUE) {
				if (text[i] == alphabet[j]) {
					Result[i] = char(j + ASCII_OFFSET);
					break;
				}
				if (j >= ALPHABET_LENGTH) {
					Result[i] = text[i];
					break;
				}
				j++;
			}
		} else {
			Result[i] = text[i];
		}
	}
}


// Stores the converted text into the first given char *
// Modifies the second given char * with strtok
void SwapNumbersToAlphabet(char *Result, char *given) {
	char *token = strtok(given, DELIM);
	int i = 0;

	while (token != NULL && i < MAX_ARRAY_LENGTH) {
		if (strcmp(token, "1") == 0 ||
			strcmp(token, "01") == 0) {
			Result[i] = 'A';
		} else if (strcmp(token, "2") == 0 ||
			strcmp(token, "02") == 0) {
			Result[i] = 'B';
		} else if (strcmp(token, "3") == 0 ||
			strcmp(token, "03") == 0) {
			Result[i] = 'C';
		} else if (strcmp(token, "4") == 0 ||
			strcmp(token, "04") == 0) {
			Result[i] = 'D';
		} else if (strcmp(token, "5") == 0 ||
			strcmp(token, "05") == 0) {
			Result[i] = 'E';
		} else if (strcmp(token, "6") == 0 ||
			strcmp(token, "06") == 0) {
			Result[i] = 'F';
		} else if (strcmp(token, "7") == 0 ||
			strcmp(token, "07") == 0) {
			Result[i] = 'G';
		} else if (strcmp(token, "8") == 0 ||
			strcmp(token, "08") == 0) {
			Result[i] = 'H';
		} else if (strcmp(token, "9") == 0 ||
			strcmp(token, "09") == 0) {
			Result[i] = 'I';
		} else if (strcmp(token, "10") == 0) {
			Result[i] = 'J';
		} else if (strcmp(token, "11") == 0) {
			Result[i] = 'K';
		} else if (strcmp(token, "12") == 0) {
			Result[i] = 'L';
		} else if (strcmp(token, "13") == 0) {
			Result[i] = 'M';
		} else if (strcmp(token, "14") == 0) {
			Result[i] = 'N';
		} else if (strcmp(token, "15") == 0) {
			Result[i] = 'O';
		} else if (strcmp(token, "16") == 0) {
			Result[i] = 'P';
		} else if (strcmp(token, "17") == 0) {
			Result[i] = 'Q';
		} else if (strcmp(token, "18") == 0) {
			Result[i] = 'R';
		} else if (strcmp(token, "19") == 0) {
			Result[i] = 'S';
		} else if (strcmp(token, "20") == 0) {
			Result[i] = 'T';
		} else if (strcmp(token, "21") == 0) {
			Result[i] = 'U';
		} else if (strcmp(token, "22") == 0) {
			Result[i] = 'V';
		} else if (strcmp(token, "23") == 0) {
			Result[i] = 'W';
		} else if (strcmp(token, "24") == 0) {
			Result[i] = 'X';
		} else if (strcmp(token, "25") == 0) {
			Result[i] = 'Y';
		} else if (strcmp(token, "26") == 0) {
			Result[i] = 'Z';
		} else {
			Result[i] = ' ';
		}
		token = strtok(NULL, DELIM);
		i++;
	}

	if (i < MAX_ARRAY_LENGTH) {
		Result[i] = '\0';
	}
}


// Stores the converted text into the first given char *
// Modifies the second given char * with strtok
void ConvertBinaryToAscii(char *Result, char *given) {
	char *token = strtok(given, DELIM);
	int i = 0;

	while (token != NULL && i < MAX_ARRAY_LENGTH) {
		if (strstr(token, "00100000") != NULL) {
			Result[i] = ' ';
		} else if (strstr(token, "00100001") != NULL) {
			Result[i] = '!';
		} else if (strstr(token, "00100010") != NULL) {
			Result[i] = '\"';
		} else if (strstr(token, "00100011") != NULL) {
			Result[i] = '#';
		} else if (strstr(token, "00100100") != NULL) {
			Result[i] = '$';
		} else if (strstr(token, "00100101") != NULL) {
			Result[i] = '%';
		} else if (strstr(token, "00100110") != NULL) {
			Result[i] = '&';
		} else if (strstr(token, "00100111") != NULL) {
			Result[i] = '\'';
		} else if (strstr(token, "00101000") != NULL) {
			Result[i] = '(';
		} else if (strstr(token, "00101001") != NULL) {
			Result[i] = ')';
		} else if (strstr(token, "00101010") != NULL) {
			Result[i] = '*';
		} else if (strstr(token, "00101011") != NULL) {
			Result[i] = '+';
		} else if (strstr(token, "00101100") != NULL) {
			Result[i] = ',';
		} else if (strstr(token, "00101101") != NULL) {
			Result[i] = '-';
		} else if (strstr(token, "00101110") != NULL) {
			Result[i] = '.';
		} else if (strstr(token, "00101111") != NULL) {
			Result[i] = '/';
		} else if (strstr(token, "00110000") != NULL) {
			Result[i] = '0';
		} else if (strstr(token, "00110001") != NULL) {
			Result[i] = '1';
		} else if (strstr(token, "00110010") != NULL) {
			Result[i] = '2';
		} else if (strstr(token, "00110011") != NULL) {
			Result[i] = '3';
		} else if (strstr(token, "00110100") != NULL) {
			Result[i] = '4';
		} else if (strstr(token, "00110101") != NULL) {
			Result[i] = '5';
		} else if (strstr(token, "00110110") != NULL) {
			Result[i] = '6';
		} else if (strstr(token, "00110111") != NULL) {
			Result[i] = '7';
		} else if (strstr(token, "00111000") != NULL) {
			Result[i] = '8';
		} else if (strstr(token, "00111001") != NULL) {
			Result[i] = '9';
		} else if (strstr(token, "00111010") != NULL) {
			Result[i] = ':';
		} else if (strstr(token, "00111011") != NULL) {
			Result[i] = ';';
		} else if (strstr(token, "00111100") != NULL) {
			Result[i] = '<';
		} else if (strstr(token, "00111101") != NULL) {
			Result[i] = '=';
		} else if (strstr(token, "00111110") != NULL) {
			Result[i] = '>';
		} else if (strstr(token, "00111111") != NULL) {
			Result[i] = '?';
		} else if (strstr(token, "01000000") != NULL) {
			Result[i] = '@';
		} else if (strstr(token, "01000001") != NULL) {
			Result[i] = 'A';
		} else if (strstr(token, "01000010") != NULL) {
			Result[i] = 'B';
		} else if (strstr(token, "01000011") != NULL) {
			Result[i] = 'C';
		} else if (strstr(token, "01000100") != NULL) {
			Result[i] = 'D';
		} else if (strstr(token, "01000101") != NULL) {
			Result[i] = 'E';
		} else if (strstr(token, "01000110") != NULL) {
			Result[i] = 'F';
		} else if (strstr(token, "01000111") != NULL) {
			Result[i] = 'G';
		} else if (strstr(token, "01001000") != NULL) {
			Result[i] = 'H';
		} else if (strstr(token, "01001001") != NULL) {
			Result[i] = 'I';
		} else if (strstr(token, "01001010") != NULL) {
			Result[i] = 'J';
		} else if (strstr(token, "01001011") != NULL) {
			Result[i] = 'K';
		} else if (strstr(token, "01001100") != NULL) {
			Result[i] = 'L';
		} else if (strstr(token, "01001101") != NULL) {
			Result[i] = 'M';
		} else if (strstr(token, "01001110") != NULL) {
			Result[i] = 'N';
		} else if (strstr(token, "01001111") != NULL) {
			Result[i] = 'O';
		} else if (strstr(token, "01010000") != NULL) {
			Result[i] = 'P';
		} else if (strstr(token, "01010001") != NULL) {
			Result[i] = 'Q';
		} else if (strstr(token, "01010010") != NULL) {
			Result[i] = 'R';
		} else if (strstr(token, "01010011") != NULL) {
			Result[i] = 'S';
		} else if (strstr(token, "01010100") != NULL) {
			Result[i] = 'T';
		} else if (strstr(token, "01010101") != NULL) {
			Result[i] = 'U';
		} else if (strstr(token, "01010110") != NULL) {
			Result[i] = 'V';
		} else if (strstr(token, "01010111") != NULL) {
			Result[i] = 'W';
		} else if (strstr(token, "01011000") != NULL) {
			Result[i] = 'X';
		} else if (strstr(token, "01011001") != NULL) {
			Result[i] = 'Y';
		} else if (strstr(token, "01011010") != NULL) {
			Result[i] = 'Z';
		} else if (strstr(token, "01011011") != NULL) {
			Result[i] = '[';
		} else if (strstr(token, "01011100") != NULL) {
			Result[i] = '\\';
		} else if (strstr(token, "01011101") != NULL) {
			Result[i] = ']';
		} else if (strstr(token, "01011110") != NULL) {
			Result[i] = '^';
		} else if (strstr(token, "01011111") != NULL) {
			Result[i] = '_';
		} else if (strstr(token, "01100000") != NULL) {
			Result[i] = '`';
		} else if (strstr(token, "01100001") != NULL) {
			Result[i] = 'a';
		} else if (strstr(token, "01100010") != NULL) {
			Result[i] = 'b';
		} else if (strstr(token, "01100011") != NULL) {
			Result[i] = 'c';
		} else if (strstr(token, "01100100") != NULL) {
			Result[i] = 'd';
		} else if (strstr(token, "01100101") != NULL) {
			Result[i] = 'e';
		} else if (strstr(token, "01100110") != NULL) {
			Result[i] = 'f';
		} else if (strstr(token, "01100111") != NULL) {
			Result[i] = 'g';
		} else if (strstr(token, "01101000") != NULL) {
			Result[i] = 'h';
		} else if (strstr(token, "01101001") != NULL) {
			Result[i] = 'i';
		} else if (strstr(token, "01101010") != NULL) {
			Result[i] = 'j';
		} else if (strstr(token, "01101011") != NULL) {
			Result[i] = 'k';
		} else if (strstr(token, "01101100") != NULL) {
			Result[i] = 'l';
		} else if (strstr(token, "01101101") != NULL) {
			Result[i] = 'm';
		} else if (strstr(token, "01101110") != NULL) {
			Result[i] = 'n';
		} else if (strstr(token, "01101111") != NULL) {
			Result[i] = 'o';
		} else if (strstr(token, "01110000") != NULL) {
			Result[i] = 'p';
		} else if (strstr(token, "01110001") != NULL) {
			Result[i] = 'q';
		} else if (strstr(token, "01110010") != NULL) {
			Result[i] = 'r';
		} else if (strstr(token, "01110011") != NULL) {
			Result[i] = 's';
		} else if (strstr(token, "01110100") != NULL) {
			Result[i] = 't';
		} else if (strstr(token, "01110101") != NULL) {
			Result[i] = 'u';
		} else if (strstr(token, "01110110") != NULL) {
			Result[i] = 'v';
		} else if (strstr(token, "01110111") != NULL) {
			Result[i] = 'w';
		} else if (strstr(token, "01111000") != NULL) {
			Result[i] = 'x';
		} else if (strstr(token, "01111001") != NULL) {
			Result[i] = 'y';
		} else if (strstr(token, "01111010") != NULL) {
			Result[i] = 'z';
		} else if (strstr(token, "01111011") != NULL) {
			Result[i] = '{';
		} else if (strstr(token, "01111100") != NULL) {
			Result[i] = '|';
		} else if (strstr(token, "01111101") != NULL) {
			Result[i] = '}';
		} else if (strstr(token, "01111110") != NULL) {
			Result[i] = '~';
		} else {
			Result[i] = ' ';
		}
		token = strtok(NULL, DELIM);
		i++;
	}

	if (i < MAX_ARRAY_LENGTH) {
		Result[i] = '\0';
	}
}


// Stores the converted text into the first given char *
// Modifies the second given char * with strtok
void ConvertOctToAscii(char *Result, char *given) {
	char *token = strtok(given, DELIM);
	int i = 0;

	while (token != NULL && i < MAX_ARRAY_LENGTH) {
		if (strstr(token, "40") != NULL &&
					strstr(token, "140") == NULL) {
			Result[i] = ' ';
		} else if (strstr(token, "41") != NULL &&
					strstr(token, "141") == NULL) {
			Result[i] = '!';
		} else if (strstr(token, "42") != NULL &&
					strstr(token, "142") == NULL) {
			Result[i] = '\"';
		} else if (strstr(token, "43") != NULL &&
					strstr(token, "143") == NULL) {
			Result[i] = '#';
		} else if (strstr(token, "44") != NULL &&
					strstr(token, "144") == NULL) {
			Result[i] = '$';
		} else if (strstr(token, "45") != NULL &&
					strstr(token, "145") == NULL) {
			Result[i] = '%';
		} else if (strstr(token, "46") != NULL &&
					strstr(token, "146") == NULL) {
			Result[i] = '&';
		} else if (strstr(token, "47") != NULL &&
					strstr(token, "147") == NULL) {
			Result[i] = '\'';
		} else if (strstr(token, "50") != NULL &&
					strstr(token, "150") == NULL) {
			Result[i] = '(';
		} else if (strstr(token, "51") != NULL &&
					strstr(token, "151") == NULL) {
			Result[i] = ')';
		} else if (strstr(token, "52") != NULL &&
					strstr(token, "152") == NULL) {
			Result[i] = '*';
		} else if (strstr(token, "53") != NULL &&
					strstr(token, "153") == NULL) {
			Result[i] = '+';
		} else if (strstr(token, "54") != NULL &&
					strstr(token, "154") == NULL) {
			Result[i] = ',';
		} else if (strstr(token, "55") != NULL &&
					strstr(token, "155") == NULL) {
			Result[i] = '-';
		} else if (strstr(token, "56") != NULL &&
					strstr(token, "156") == NULL) {
			Result[i] = '.';
		} else if (strstr(token, "57") != NULL &&
					strstr(token, "157") == NULL) {
			Result[i] = '/';
		} else if (strstr(token, "60") != NULL &&
					strstr(token, "160") == NULL) {
			Result[i] = '0';
		} else if (strstr(token, "61") != NULL &&
					strstr(token, "161") == NULL) {
			Result[i] = '1';
		} else if (strstr(token, "62") != NULL &&
					strstr(token, "162") == NULL) {
			Result[i] = '2';
		} else if (strstr(token, "63") != NULL &&
					strstr(token, "163") == NULL) {
			Result[i] = '3';
		} else if (strstr(token, "64") != NULL &&
					strstr(token, "164") == NULL) {
			Result[i] = '4';
		} else if (strstr(token, "65") != NULL &&
					strstr(token, "165") == NULL) {
			Result[i] = '5';
		} else if (strstr(token, "66") != NULL &&
					strstr(token, "166") == NULL) {
			Result[i] = '6';
		} else if (strstr(token, "67") != NULL &&
					strstr(token, "167") == NULL) {
			Result[i] = '7';
		} else if (strstr(token, "70") != NULL &&
					strstr(token, "170") == NULL) {
			Result[i] = '8';
		} else if (strstr(token, "71") != NULL &&
					strstr(token, "171") == NULL) {
			Result[i] = '9';
		} else if (strstr(token, "72") != NULL &&
					strstr(token, "172") == NULL) {
			Result[i] = ':';
		} else if (strstr(token, "73") != NULL &&
					strstr(token, "173") == NULL) {
			Result[i] = ';';
		} else if (strstr(token, "74") != NULL &&
					strstr(token, "174") == NULL) {
			Result[i] = '<';
		} else if (strstr(token, "75") != NULL &&
					strstr(token, "175") == NULL) {
			Result[i] = '=';
		} else if (strstr(token, "76") != NULL &&
					strstr(token, "176") == NULL) {
			Result[i] = '>';
		} else if (strstr(token, "77") != NULL &&
					strstr(token, "177") == NULL) {
			Result[i] = '?';
		} else if (strstr(token, "100") != NULL) {
			Result[i] = '@';
		} else if (strstr(token, "101") != NULL) {
			Result[i] = 'A';
		} else if (strstr(token, "102") != NULL) {
			Result[i] = 'B';
		} else if (strstr(token, "103") != NULL) {
			Result[i] = 'C';
		} else if (strstr(token, "104") != NULL) {
			Result[i] = 'D';
		} else if (strstr(token, "105") != NULL) {
			Result[i] = 'E';
		} else if (strstr(token, "106") != NULL) {
			Result[i] = 'F';
		} else if (strstr(token, "107") != NULL) {
			Result[i] = 'G';
		} else if (strstr(token, "110") != NULL) {
			Result[i] = 'H';
		} else if (strstr(token, "111") != NULL) {
			Result[i] = 'I';
		} else if (strstr(token, "112") != NULL) {
			Result[i] = 'J';
		} else if (strstr(token, "113") != NULL) {
			Result[i] = 'K';
		} else if (strstr(token, "114") != NULL) {
			Result[i] = 'L';
		} else if (strstr(token, "115") != NULL) {
			Result[i] = 'M';
		} else if (strstr(token, "116") != NULL) {
			Result[i] = 'N';
		} else if (strstr(token, "117") != NULL) {
			Result[i] = 'O';
		} else if (strstr(token, "120") != NULL) {
			Result[i] = 'P';
		} else if (strstr(token, "121") != NULL) {
			Result[i] = 'Q';
		} else if (strstr(token, "122") != NULL) {
			Result[i] = 'R';
		} else if (strstr(token, "123") != NULL) {
			Result[i] = 'S';
		} else if (strstr(token, "124") != NULL) {
			Result[i] = 'T';
		} else if (strstr(token, "125") != NULL) {
			Result[i] = 'U';
		} else if (strstr(token, "126") != NULL) {
			Result[i] = 'V';
		} else if (strstr(token, "127") != NULL) {
			Result[i] = 'W';
		} else if (strstr(token, "130") != NULL) {
			Result[i] = 'X';
		} else if (strstr(token, "131") != NULL) {
			Result[i] = 'Y';
		} else if (strstr(token, "132") != NULL) {
			Result[i] = 'Z';
		} else if (strstr(token, "133") != NULL) {
			Result[i] = '[';
		} else if (strstr(token, "134") != NULL) {
			Result[i] = '\\';
		} else if (strstr(token, "135") != NULL) {
			Result[i] = ']';
		} else if (strstr(token, "136") != NULL) {
			Result[i] = '^';
		} else if (strstr(token, "137") != NULL) {
			Result[i] = '_';
		} else if (strstr(token, "140") != NULL) {
			Result[i] = '`';
		} else if (strstr(token, "141") != NULL) {
			Result[i] = 'a';
		} else if (strstr(token, "142") != NULL) {
			Result[i] = 'b';
		} else if (strstr(token, "143") != NULL) {
			Result[i] = 'c';
		} else if (strstr(token, "144") != NULL) {
			Result[i] = 'd';
		} else if (strstr(token, "145") != NULL) {
			Result[i] = 'e';
		} else if (strstr(token, "146") != NULL) {
			Result[i] = 'f';
		} else if (strstr(token, "147") != NULL) {
			Result[i] = 'g';
		} else if (strstr(token, "150") != NULL) {
			Result[i] = 'h';
		} else if (strstr(token, "151") != NULL) {
			Result[i] = 'i';
		} else if (strstr(token, "152") != NULL) {
			Result[i] = 'j';
		} else if (strstr(token, "153") != NULL) {
			Result[i] = 'k';
		} else if (strstr(token, "154") != NULL) {
			Result[i] = 'l';
		} else if (strstr(token, "155") != NULL) {
			Result[i] = 'm';
		} else if (strstr(token, "156") != NULL) {
			Result[i] = 'n';
		} else if (strstr(token, "157") != NULL) {
			Result[i] = 'o';
		} else if (strstr(token, "160") != NULL) {
			Result[i] = 'p';
		} else if (strstr(token, "161") != NULL) {
			Result[i] = 'q';
		} else if (strstr(token, "162") != NULL) {
			Result[i] = 'r';
		} else if (strstr(token, "163") != NULL) {
			Result[i] = 's';
		} else if (strstr(token, "164") != NULL) {
			Result[i] = 't';
		} else if (strstr(token, "165") != NULL) {
			Result[i] = 'u';
		} else if (strstr(token, "166") != NULL) {
			Result[i] = 'v';
		} else if (strstr(token, "167") != NULL) {
			Result[i] = 'w';
		} else if (strstr(token, "170") != NULL) {
			Result[i] = 'x';
		} else if (strstr(token, "171") != NULL) {
			Result[i] = 'y';
		} else if (strstr(token, "172") != NULL) {
			Result[i] = 'z';
		} else if (strstr(token, "173") != NULL) {
			Result[i] = '{';
		} else if (strstr(token, "174") != NULL) {
			Result[i] = '|';
		} else if (strstr(token, "175") != NULL) {
			Result[i] = '}';
		} else if (strstr(token, "176") != NULL) {
			Result[i] = '~';
		} else {
			Result[i] = ' ';
		}
		token = strtok(NULL, DELIM);
		i++;
	}

	if (i < MAX_ARRAY_LENGTH) {
		Result[i] = '\0';
	}
}


// Stores the converted text into the first given char *
// Modifies the second given char * with strtok
void ConvertDecimalToAscii(char *Result, char *given) {
	char *token = strtok(given, DELIM);
	int i = 0;

	while (token != NULL && i < MAX_ARRAY_LENGTH) {
		if (strstr(token, "32") != NULL) {
			Result[i] = ' ';
		} else if (strstr(token, "33") != NULL) {
			Result[i] = '!';
		} else if (strstr(token, "34") != NULL) {
			Result[i] = '\"';
		} else if (strstr(token, "35") != NULL) {
			Result[i] = '#';
		} else if (strstr(token, "36") != NULL) {
			Result[i] = '$';
		} else if (strstr(token, "37") != NULL) {
			Result[i] = '%';
		} else if (strstr(token, "38") != NULL) {
			Result[i] = '&';
		} else if (strstr(token, "39") != NULL) {
			Result[i] = '\'';
		} else if (strstr(token, "40") != NULL) {
			Result[i] = '(';
		} else if (strstr(token, "41") != NULL) {
			Result[i] = ')';
		} else if (strstr(token, "42") != NULL) {
			Result[i] = '*';
		} else if (strstr(token, "43") != NULL) {
			Result[i] = '+';
		} else if (strstr(token, "44") != NULL) {
			Result[i] = ',';
		} else if (strstr(token, "45") != NULL) {
			Result[i] = '-';
		} else if (strstr(token, "46") != NULL) {
			Result[i] = '.';
		} else if (strstr(token, "47") != NULL) {
			Result[i] = '/';
		} else if (strstr(token, "48") != NULL) {
			Result[i] = '0';
		} else if (strstr(token, "49") != NULL) {
			Result[i] = '1';
		} else if (strstr(token, "50") != NULL) {
			Result[i] = '2';
		} else if (strstr(token, "51") != NULL) {
			Result[i] = '3';
		} else if (strstr(token, "52") != NULL) {
			Result[i] = '4';
		} else if (strstr(token, "53") != NULL) {
			Result[i] = '5';
		} else if (strstr(token, "54") != NULL) {
			Result[i] = '6';
		} else if (strstr(token, "55") != NULL) {
			Result[i] = '7';
		} else if (strstr(token, "56") != NULL) {
			Result[i] = '8';
		} else if (strstr(token, "57") != NULL) {
			Result[i] = '9';
		} else if (strstr(token, "58") != NULL) {
			Result[i] = ':';
		} else if (strstr(token, "59") != NULL) {
			Result[i] = ';';
		} else if (strstr(token, "60") != NULL) {
			Result[i] = '<';
		} else if (strstr(token, "61") != NULL) {
			Result[i] = '=';
		} else if (strstr(token, "62") != NULL) {
			Result[i] = '>';
		} else if (strstr(token, "63") != NULL) {
			Result[i] = '?';
		} else if (strstr(token, "64") != NULL) {
			Result[i] = '@';
		} else if (strstr(token, "65") != NULL) {
			Result[i] = 'A';
		} else if (strstr(token, "66") != NULL) {
			Result[i] = 'B';
		} else if (strstr(token, "67") != NULL) {
			Result[i] = 'C';
		} else if (strstr(token, "68") != NULL) {
			Result[i] = 'D';
		} else if (strstr(token, "69") != NULL) {
			Result[i] = 'E';
		} else if (strstr(token, "70") != NULL) {
			Result[i] = 'F';
		} else if (strstr(token, "71") != NULL) {
			Result[i] = 'G';
		} else if (strstr(token, "72") != NULL) {
			Result[i] = 'H';
		} else if (strstr(token, "73") != NULL) {
			Result[i] = 'I';
		} else if (strstr(token, "74") != NULL) {
			Result[i] = 'J';
		} else if (strstr(token, "75") != NULL) {
			Result[i] = 'K';
		} else if (strstr(token, "76") != NULL) {
			Result[i] = 'L';
		} else if (strstr(token, "77") != NULL) {
			Result[i] = 'M';
		} else if (strstr(token, "78") != NULL) {
			Result[i] = 'N';
		} else if (strstr(token, "79") != NULL) {
			Result[i] = 'O';
		} else if (strstr(token, "80") != NULL) {
			Result[i] = 'P';
		} else if (strstr(token, "81") != NULL) {
			Result[i] = 'Q';
		} else if (strstr(token, "82") != NULL) {
			Result[i] = 'R';
		} else if (strstr(token, "83") != NULL) {
			Result[i] = 'S';
		} else if (strstr(token, "84") != NULL) {
			Result[i] = 'T';
		} else if (strstr(token, "85") != NULL) {
			Result[i] = 'U';
		} else if (strstr(token, "86") != NULL) {
			Result[i] = 'V';
		} else if (strstr(token, "87") != NULL) {
			Result[i] = 'W';
		} else if (strstr(token, "88") != NULL) {
			Result[i] = 'X';
		} else if (strstr(token, "89") != NULL) {
			Result[i] = 'Y';
		} else if (strstr(token, "90") != NULL) {
			Result[i] = 'Z';
		} else if (strstr(token, "91") != NULL) {
			Result[i] = '[';
		} else if (strstr(token, "92") != NULL) {
			Result[i] = '\\';
		} else if (strstr(token, "93") != NULL) {
			Result[i] = ']';
		} else if (strstr(token, "94") != NULL) {
			Result[i] = '^';
		} else if (strstr(token, "95") != NULL) {
			Result[i] = '_';
		} else if (strstr(token, "96") != NULL) {
			Result[i] = '`';
		} else if (strstr(token, "97") != NULL) {
			Result[i] = 'a';
		} else if (strstr(token, "98") != NULL) {
			Result[i] = 'b';
		} else if (strstr(token, "99") != NULL) {
			Result[i] = 'c';
		} else if (strstr(token, "100") != NULL) {
			Result[i] = 'd';
		} else if (strstr(token, "101") != NULL) {
			Result[i] = 'e';
		} else if (strstr(token, "102") != NULL) {
			Result[i] = 'f';
		} else if (strstr(token, "103") != NULL) {
			Result[i] = 'g';
		} else if (strstr(token, "104") != NULL) {
			Result[i] = 'h';
		} else if (strstr(token, "105") != NULL) {
			Result[i] = 'i';
		} else if (strstr(token, "106") != NULL) {
			Result[i] = 'j';
		} else if (strstr(token, "107") != NULL) {
			Result[i] = 'k';
		} else if (strstr(token, "108") != NULL) {
			Result[i] = 'l';
		} else if (strstr(token, "109") != NULL) {
			Result[i] = 'm';
		} else if (strstr(token, "110") != NULL) {
			Result[i] = 'n';
		} else if (strstr(token, "111") != NULL) {
			Result[i] = 'o';
		} else if (strstr(token, "112") != NULL) {
			Result[i] = 'p';
		} else if (strstr(token, "113") != NULL) {
			Result[i] = 'q';
		} else if (strstr(token, "114") != NULL) {
			Result[i] = 'r';
		} else if (strstr(token, "115") != NULL) {
			Result[i] = 's';
		} else if (strstr(token, "116") != NULL) {
			Result[i] = 't';
		} else if (strstr(token, "117") != NULL) {
			Result[i] = 'u';
		} else if (strstr(token, "118") != NULL) {
			Result[i] = 'v';
		} else if (strstr(token, "119") != NULL) {
			Result[i] = 'w';
		} else if (strstr(token, "120") != NULL) {
			Result[i] = 'x';
		} else if (strstr(token, "121") != NULL) {
			Result[i] = 'y';
		} else if (strstr(token, "122") != NULL) {
			Result[i] = 'z';
		} else if (strstr(token, "123") != NULL) {
			Result[i] = '{';
		} else if (strstr(token, "124") != NULL) {
			Result[i] = '|';
		} else if (strstr(token, "125") != NULL) {
			Result[i] = '}';
		} else if (strstr(token, "126") != NULL) {
			Result[i] = '~';
		} else {
			Result[i] = ' ';
		}
		token = strtok(NULL, DELIM);
		i++;
	}

	if (i < MAX_ARRAY_LENGTH) {
		Result[i] = '\0';
	}
}


// Stores the converted text into the first given char *
// Modifies the second given char * with strtok
void ConvertHexToAscii(char *Result, char *given) {
	int resultIndex = 0;
	int givenIndex = 0;
	char digit1 = given[givenIndex];
	char digit2 = '\0';
	if (digit1 != '\0') {
		digit2 = given[givenIndex+1];
	}

	while (digit1 != '\0' && digit2 != '\0' && 
		   resultIndex < MAX_ARRAY_LENGTH) {
		if (digit1 == '2') {
			if (digit2 == '0') {
				Result[resultIndex] = ' ';
			} else if (digit2 == '1') {
				Result[resultIndex] = '!';
			} else if (digit2 == '2') {
				Result[resultIndex] = '\"';
			} else if (digit2 == '3') {
				Result[resultIndex] = '#';
			} else if (digit2 == '4') {
				Result[resultIndex] = '$';
			} else if (digit2 == '5') {
				Result[resultIndex] = '%';
			} else if (digit2 == '6') {
				Result[resultIndex] = '&';
			} else if (digit2 == '7') {
				Result[resultIndex] = '\'';
			} else if (digit2 == '8') {
				Result[resultIndex] = '(';
			} else if (digit2 == '9') {
				Result[resultIndex] = ')';
			} else if (digit2 == 'A' || digit2 == 'a') {
				Result[resultIndex] = '*';
			} else if (digit2 == 'B' ||	digit2 == 'b') {
				Result[resultIndex] = '+';
			} else if (digit2 == 'C' ||	digit2 == 'c') {
				Result[resultIndex] = ',';
			} else if (digit2 == 'D' ||	digit2 == 'd') {
				Result[resultIndex] = '-';
			} else if (digit2 == 'E' ||	digit2 == 'e') {
				Result[resultIndex] = '.';
			} else if (digit2 == 'F' ||	digit2 == 'f') {
				Result[resultIndex] = '/';
			} else {
				Result[resultIndex] = ' ';
			}
		} else if (digit1 == '3') {
			if (digit2 == '0') {
				Result[resultIndex] = '0';
			} else if (digit2 == '1') {
				Result[resultIndex] = '1';
			} else if (digit2 == '2') {
				Result[resultIndex] = '2';
			} else if (digit2 == '3') {
				Result[resultIndex] = '3';
			} else if (digit2 == '4') {
				Result[resultIndex] = '4';
			} else if (digit2 == '5') {
				Result[resultIndex] = '5';
			} else if (digit2 == '6') {
				Result[resultIndex] = '6';
			} else if (digit2 == '7') {
				Result[resultIndex] = '7';
			} else if (digit2 == '8') {
				Result[resultIndex] = '8';
			} else if (digit2 == '9') {
				Result[resultIndex] = '9';
			} else if (digit2 == 'A' ||	digit2 == 'a') {
				Result[resultIndex] = ':';
			} else if (digit2 == 'B' ||	digit2 == 'b') {
				Result[resultIndex] = ';';
			} else if (digit2 == 'C' ||	digit2 == 'c') {
				Result[resultIndex] = '<';
			} else if (digit2 == 'D' ||	digit2 == 'd') {
				Result[resultIndex] = '=';
			} else if (digit2 == 'E' ||	digit2 == 'e') {
				Result[resultIndex] = '>';
			} else if (digit2 == 'F' ||	digit2 == 'f') {
				Result[resultIndex] = '?';
			} else {
				Result[resultIndex] = ' ';
			}
		} else if (digit1 == '4') {
			if (digit2 == '0') {
				Result[resultIndex] = '@';
			} else if (digit2 == '1') {
				Result[resultIndex] = 'A';
			} else if (digit2 == '2') {
				Result[resultIndex] = 'B';
			} else if (digit2 == '3') {
				Result[resultIndex] = 'C';
			} else if (digit2 == '4') {
				Result[resultIndex] = 'D';
			} else if (digit2 == '5') {
				Result[resultIndex] = 'E';
			} else if (digit2 == '6') {
				Result[resultIndex] = 'F';
			} else if (digit2 == '7') {
				Result[resultIndex] = 'G';
			} else if (digit2 == '8') {
				Result[resultIndex] = 'H';
			} else if (digit2 == '9') {
				Result[resultIndex] = 'I';
			} else if (digit2 == 'A' ||	digit2 == 'a') {
				Result[resultIndex] = 'J';
			} else if (digit2 == 'B' ||	digit2 == 'b') {
				Result[resultIndex] = 'K';
			} else if (digit2 == 'C' ||	digit2 == 'c') {
				Result[resultIndex] = 'L';
			} else if (digit2 == 'D' ||	digit2 == 'd') {
				Result[resultIndex] = 'M';
			} else if (digit2 == 'E' ||	digit2 == 'e') {
				Result[resultIndex] = 'N';
			} else if (digit2 == 'F' ||	digit2 == 'f') {
				Result[resultIndex] = 'O';
			} else {
				Result[resultIndex] = ' ';
			}
		} else if (digit1 == '5') {
			if (digit2 == '0') {
				Result[resultIndex] = 'P';
			} else if (digit2 == '1') {
				Result[resultIndex] = 'Q';
			} else if (digit2 == '2') {
				Result[resultIndex] = 'R';
			} else if (digit2 == '3') {
				Result[resultIndex] = 'S';
			} else if (digit2 == '4') {
				Result[resultIndex] = 'T';
			} else if (digit2 == '5') {
				Result[resultIndex] = 'U';
			} else if (digit2 == '6') {
				Result[resultIndex] = 'V';
			} else if (digit2 == '7') {
				Result[resultIndex] = 'W';
			} else if (digit2 == '8') {
				Result[resultIndex] = 'X';
			} else if (digit2 == '9') {
				Result[resultIndex] = 'Y';
			} else if (digit2 == 'A' ||	digit2 == 'a') {
				Result[resultIndex] = 'Z';
			} else if (digit2 == 'B' ||	digit2 == 'b') {
				Result[resultIndex] = '[';
			} else if (digit2 == 'C' ||	digit2 == 'c') {
				Result[resultIndex] = '\\';
			} else if (digit2 == 'D' ||	digit2 == 'd') {
				Result[resultIndex] = ']';
			} else if (digit2 == 'E' ||	digit2 == 'e') {
				Result[resultIndex] = '^';
			} else if (digit2 == 'F' ||	digit2 == 'f') {
				Result[resultIndex] = '_';
			} else {
				Result[resultIndex] = ' ';
			}
		} else if (digit1 == '6') {
			if (digit2 == '0') {
				Result[resultIndex] = '`';
			} else if (digit2 == '1') {
				Result[resultIndex] = 'a';
			} else if (digit2 == '2') {
				Result[resultIndex] = 'b';
			} else if (digit2 == '3') {
				Result[resultIndex] = 'c';
			} else if (digit2 == '4') {
				Result[resultIndex] = 'd';
			} else if (digit2 == '5') {
				Result[resultIndex] = 'e';
			} else if (digit2 == '6') {
				Result[resultIndex] = 'f';
			} else if (digit2 == '7') {
				Result[resultIndex] = 'g';
			} else if (digit2 == '8') {
				Result[resultIndex] = 'h';
			} else if (digit2 == '9') {
				Result[resultIndex] = 'i';
			} else if (digit2 == 'A' ||	digit2 == 'a') {
				Result[resultIndex] = 'j';
			} else if (digit2 == 'B' ||	digit2 == 'b') {
				Result[resultIndex] = 'k';
			} else if (digit2 == 'C' ||	digit2 == 'c') {
				Result[resultIndex] = 'l';
			} else if (digit2 == 'D' ||	digit2 == 'd') {
				Result[resultIndex] = 'm';
			} else if (digit2 == 'E' ||	digit2 == 'e') {
				Result[resultIndex] = 'n';
			} else if (digit2 == 'F' ||	digit2 == 'f') {
				Result[resultIndex] = 'o';
			} else {
				Result[resultIndex] = ' ';
			}
		} else if (digit1 == '7') {
			if (digit2 == '0') {
				Result[resultIndex] = 'p';
			} else if (digit2 == '1') {
				Result[resultIndex] = 'q';
			} else if (digit2 == '2') {
				Result[resultIndex] = 'r';
			} else if (digit2 == '3') {
				Result[resultIndex] = 's';
			} else if (digit2 == '4') {
				Result[resultIndex] = 't';
			} else if (digit2 == '5') {
				Result[resultIndex] = 'u';
			} else if (digit2 == '6') {
				Result[resultIndex] = 'v';
			} else if (digit2 == '7') {
				Result[resultIndex] = 'w';
			} else if (digit2 == '8') {
				Result[resultIndex] = 'x';
			} else if (digit2 == '9') {
				Result[resultIndex] = 'y';
			} else if (digit2 == 'A' ||	digit2 == 'a') {
				Result[resultIndex] = 'z';
			} else if (digit2 == 'B' ||	digit2 == 'b') {
				Result[resultIndex] = '{';
			} else if (digit2 == 'C' ||	digit2 == 'c') {
				Result[resultIndex] = '|';
			} else if (digit2 == 'D' ||	digit2 == 'd') {
				Result[resultIndex] = '}';
			} else if (digit2 == 'E' ||	digit2 == 'e') {
				Result[resultIndex] = '~';
			} else {
				Result[resultIndex] = ' ';
			}
		} else {
			Result[resultIndex] = ' ';
		}

		resultIndex++;
		givenIndex += 2;
		digit1 = given[givenIndex];
		while (digit1 != '\0' && digit1 != '2' && digit1 != '3' && 
			digit1 != '4' && digit1 != '5' && digit1 != '6' && digit1 != '7') {
			givenIndex++;
			digit1 = given[givenIndex];
		}
		if (digit1 != '\0') {
			digit2 = given[givenIndex+1];
		}
	}

	if (resultIndex < MAX_ARRAY_LENGTH) {
		Result[resultIndex] = '\0';
	}
}


// Stores the converted text into the first given char *
// Modifies the second given char * with strtok
void ConvertMorseToAscii(char *Result, char *given) {
	char delim[3] = " ,";
	char *token = strtok(given, delim);
	int i = 0;

	while (token != NULL && i < MAX_ARRAY_LENGTH) {
		if (strcmp(token, "-----") == 0) {
			Result[i] = '0';
		} else if (strcmp(token, ".----") == 0) {
			Result[i] = '1';
		} else if (strcmp(token, "..---") == 0) {
			Result[i] = '2';
		} else if (strcmp(token, "...--") == 0) {
			Result[i] = '3';
		} else if (strcmp(token, "....-") == 0) {
			Result[i] = '4';
		} else if (strcmp(token, ".....") == 0) {
			Result[i] = '5';
		} else if (strcmp(token, "-....") == 0) {
			Result[i] = '6';
		} else if (strcmp(token, "--...") == 0) {
			Result[i] = '7';
		} else if (strcmp(token, "---..") == 0) {
			Result[i] = '8';
		} else if (strcmp(token, "----.") == 0) {
			Result[i] = '9';
		} else if (strcmp(token, ".-") == 0) {
			Result[i] = 'A';
		} else if (strcmp(token, "-...") == 0) {
			Result[i] = 'B';
		} else if (strcmp(token, "-.-.") == 0) {
			Result[i] = 'C';
		} else if (strcmp(token, "-..") == 0) {
			Result[i] = 'D';
		} else if (strcmp(token, ".") == 0) {
			Result[i] = 'E';
		} else if (strcmp(token, "..-.") == 0) {
			Result[i] = 'F';
		} else if (strcmp(token, "--.") == 0) {
			Result[i] = 'G';
		} else if (strcmp(token, "....") == 0) {
			Result[i] = 'H';
		} else if (strcmp(token, "..") == 0) {
			Result[i] = 'I';
		} else if (strcmp(token, ".---") == 0) {
			Result[i] = 'J';
		} else if (strcmp(token, "-.-") == 0) {
			Result[i] = 'K';
		} else if (strcmp(token, ".-..") == 0) {
			Result[i] = 'L';
		} else if (strcmp(token, "--") == 0) {
			Result[i] = 'M';
		} else if (strcmp(token, "-.") == 0) {
			Result[i] = 'N';
		} else if (strcmp(token, "---") == 0) {
			Result[i] = 'O';
		} else if (strcmp(token, ".--.") == 0) {
			Result[i] = 'P';
		} else if (strcmp(token, "--.-") == 0) {
			Result[i] = 'Q';
		} else if (strcmp(token, ".-.") == 0) {
			Result[i] = 'R';
		} else if (strcmp(token, "...") == 0) {
			Result[i] = 'S';
		} else if (strcmp(token, "-") == 0) {
			Result[i] = 'T';
		} else if (strcmp(token, "..-") == 0) {
			Result[i] = 'U';
		} else if (strcmp(token, "...-") == 0) {
			Result[i] = 'V';
		} else if (strcmp(token, ".--") == 0) {
			Result[i] = 'W';
		} else if (strcmp(token, "-..-") == 0) {
			Result[i] = 'X';
		} else if (strcmp(token, "-.--") == 0) {
			Result[i] = 'Y';
		} else if (strcmp(token, "--..") == 0) {
			Result[i] = 'Z';
		} else if (strcmp(token, ".-.-") == 0) {
			Result[i] = '\xC4';
		} else if (strcmp(token, ".--.-") == 0) {
			Result[i] = '\xC1';
		} else if (strcmp(token, ".--.-") == 0) {
			Result[i] = '\xC5';
		} else if (strcmp(token, "----") == 0) {
			Result[i] = '\xC7';
		} else if (strcmp(token, "..-..") == 0) {
			Result[i] = '\xC9';
		} else if (strcmp(token, "--.--") == 0) {
			Result[i] = '\xD1';
		} else if (strcmp(token, "---.") == 0) {
			Result[i] = '\xD6';
		} else if (strcmp(token, "..--") == 0) {
			Result[i] = '\xDC';
		} else if (strcmp(token, ".-.-.-") == 0) {
			Result[i] = '.';
		} else if (strcmp(token, "--..--") == 0) {
			Result[i] = ',';
		} else if (strcmp(token, "---...") == 0) {
			Result[i] = ':';
		} else if (strcmp(token, "..--..") == 0) {
			Result[i] = '?';
		} else if (strcmp(token, ".----.") == 0) {
			Result[i] = '\'';
		} else if (strcmp(token, "-....-") == 0) {
			Result[i] = '-';
		} else if (strcmp(token, "-..-.") == 0) {
			Result[i] = '/';
		} else if (strcmp(token, "-.--.") == 0) {
			Result[i] = '(';
		} else if (strcmp(token, ".-..-.") == 0) {
			Result[i] = '\"';
		} else if (strcmp(token, ".--.-.") == 0) {
			Result[i] = '@';
		} else if (strcmp(token, "-...-") == 0) {
			Result[i] = '=';
		} else if (strcmp(token, "-.-.--") == 0) {
			Result[i] = '!';
		} else if (strcmp(token, "-.--.-") == 0) {
			Result[i] = ')';
		} else if (strcmp(token, ".-...") == 0) {
			Result[i] = '&';
		} else if (strcmp(token, "-.-.-.") == 0) {
			Result[i] = ';';
		} else if (strcmp(token, ".-.-.") == 0) {
			Result[i] = '+';
		} else if (strcmp(token, "..--.-") == 0) {
			Result[i] = '_';
		} else if (strcmp(token, "...-..-") == 0) {
			Result[i] = '$';
		} else {
			Result[i] = ' ';
		}
		token = strtok(NULL, delim);
		i++;
	}

	if (i < MAX_ARRAY_LENGTH) {
		Result[i] = '\0';
	}
}