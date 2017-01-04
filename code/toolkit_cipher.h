#ifndef TOOLKIT_CIPHER
#define TOOLKIT_CIPHER

struct Cipher {

	HWND labelKeyword;
	HWND editKey;
	HWND labelShift;
	HWND comboShift;
	HWND labelInput;
	HWND editInput;
	HWND labelOutput;
	HWND staticOutput;
	HWND buttonEncrypt;
	HWND buttonDecrypt;

	char key[MAX_ARRAY_LENGTH];
	char input[MAX_ARRAY_LENGTH];
	char output[MAX_ARRAY_LENGTH];
	char alphabet[ALPHABET_LENGTH][2];
	char newAlphabet[ALPHABET_LENGTH];

	int keyLength;
	int inputTextLength;
	int baseSelected;

	bool dataStored;

	Cipher() : keyLength(0), inputTextLength(0), baseSelected(0), 
			dataStored(FALSE) {
		for (int i = 0; i < ALPHABET_LENGTH; i++) {
			alphabet[i][0] = (char)(i+ASCII_OFFSET);
			alphabet[i][1] = '\0';
		}
	}
};


void SetKey(Cipher *objCipher);

void SetNewAlphabet(Cipher *objCipher);

void SetInputText(Cipher *objCipher);

LRESULT PaintCipherWindow(HWND *hPWnd, Cipher *objCipher);

LRESULT DestroyCipherWindow(Cipher *objCipher);

#endif