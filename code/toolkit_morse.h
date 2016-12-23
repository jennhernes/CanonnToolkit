#ifndef TOOLKIT_MORSE
#define TOOLKIT_MORSE

struct Morse {

	HWND buttonConvert;
	HWND labelMorse;
	HWND editMorse;
	HWND labelAscii;
	HWND staticAscii;

	char userInput[MAX_ARRAY_LENGTH];
	char copyUserInput[MAX_ARRAY_LENGTH];
	char asciiOutput[MAX_ARRAY_LENGTH];

	int inputLength;

	bool dataStored;

	Morse() : inputLength(0), dataStored(FALSE) {}
};


LRESULT PaintMorseWindow(HWND *hPWnd, Morse *objMorse);

LRESULT DestroyMorseWindow(Morse *objMorse);

#endif