#ifndef TOOLKIT_NUMBERS
#define TOOLKIT_NUMBERS

struct Numbers {
	HWND labelNumBase;
	HWND comboNumBase;
	HWND labelInput;
	HWND editNumber;
	HWND buttonConvert;
	HWND labelOutput;
	HWND staticAscii;

	char userInput[MAX_ARRAY_LENGTH];
	char copyUserInput[MAX_ARRAY_LENGTH];
	char asciiOutput[MAX_ARRAY_LENGTH];

	char numBaseList[5][15];

	int baseSelected;
	int inputLength;

	bool dataStored;

	Numbers() : baseSelected(0), inputLength(0), dataStored(FALSE) {
		strcpy(this->asciiOutput, "");
		strcpy(this->numBaseList[0], "BINARY");
		strcpy(this->numBaseList[1], "OCTAL");
		strcpy(this->numBaseList[2], "DECIMAL");
		strcpy(this->numBaseList[3], "HEXADECIMAL");
		strcpy(this->numBaseList[4], "ALPHABET SWAP");
	}
};


LRESULT PaintNumbersWindow(HWND *hPWnd, Numbers *objNumbers);

LRESULT DestroyNumbersWindow(Numbers *objNumbers);


#endif