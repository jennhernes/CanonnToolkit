#include <windows.h>
#include "definitions.h"
#include "toolkit_cipher.h"


LRESULT CALLBACK MultiLineWindowProc(HWND hwnd, UINT uMsg, 
                                     WPARAM wParam, LPARAM lParam,
                                     UINT_PTR uIdSubclass, DWORD_PTR dwRefData);


void SetKey(Cipher *objCipher) {
    objCipher->keyLength = GetWindowTextLength(objCipher->editKey);
    if (objCipher->keyLength > MAX_ARRAY_LENGTH-1) {
        objCipher->keyLength = MAX_ARRAY_LENGTH-1;
    }
    GetWindowText(objCipher->editKey, objCipher->key, objCipher->keyLength+1);
    for (int i = 0; i < objCipher->keyLength; i++) {
    	objCipher->key[i] = (char)toupper(objCipher->key[i]);
    }
}


void SetNewAlphabet(Cipher *objCipher) {
	int newIndex = (ALPHABET_LENGTH - objCipher->baseSelected) % 26;

	for (int i = 0; i < ALPHABET_LENGTH; i++) {
			objCipher->alphabet[i][1] = '\0';
	}

	for (int i = 0; i < objCipher->keyLength; i++) {
		if(objCipher->alphabet[(int)objCipher->key[i]-ASCII_OFFSET][1] != 'X') {
			objCipher->newAlphabet[newIndex] = objCipher->key[i];
			objCipher->alphabet[(int)objCipher->key[i]-ASCII_OFFSET][1] = 'X';
			newIndex++;
			newIndex = newIndex % 26;
		}
	}

	for (int i = 0; i < ALPHABET_LENGTH; i++) {
		if (objCipher->alphabet[i][1] != 'X') {
			objCipher->newAlphabet[newIndex] = objCipher->alphabet[i][0];
			newIndex++;
			newIndex = newIndex % 26;
		}
	}
}


void SetInputText(Cipher *objCipher) {
    objCipher->inputTextLength = GetWindowTextLength(objCipher->editInput);
    if (objCipher->inputTextLength > MAX_ARRAY_LENGTH-1) {
        objCipher->inputTextLength = MAX_ARRAY_LENGTH-1;
    }
    objCipher->inputTextLength++;
    GetWindowText(objCipher->editInput, objCipher->input, 
    	objCipher->inputTextLength);
    for (int i = 0; i < objCipher->inputTextLength; i++) {
    	objCipher->input[i] = (char)toupper(objCipher->input[i]);
    }
    objCipher->input[objCipher->inputTextLength-1] = '\0';
}


LRESULT PaintCipherWindow(HWND *hPWnd, Cipher *objCipher) {
    LRESULT Result = 0;
    DWORD baseStyle = WS_CHILD | WS_VISIBLE;

    RECT rect;
    SetRect(&rect, XDIVIDER, 0, CLIENT_WIDTH, CLIENT_HEIGHT);
    HDC hdc = GetDC(*hPWnd);
    FillRect(hdc, &rect, CreateSolidBrush(CANONN_DARKGRAY_RGB));

    HFONT fontDefault;

    RECT topRect;
    RECT leftRect;

    objCipher->labelKeyword = CreateWindowEx(0, "STATIC", "", 
        baseStyle | SS_LEFT, 
        XSTART, YSTART, TEXTBOXWIDTH, BUTTONHEIGHT, 
        *hPWnd, (HMENU)IDC_LABEL_KEYWORD, GetModuleHandle(NULL), NULL);
    if (objCipher->labelKeyword == NULL) {
        Result = -1;
        return(Result);
    }

    GetWindowRect(objCipher->labelKeyword, &topRect);
    AdjustRectToWindow(&topRect, hPWnd);

    objCipher->editKey = CreateWindowEx(0, "EDIT", "", 
        baseStyle | WS_TABSTOP | ES_AUTOHSCROLL, 
        topRect.left, topRect.bottom+10, TEXTBOXWIDTH, BUTTONHEIGHT, 
        *hPWnd, (HMENU)IDC_EDIT_KEY, GetModuleHandle(NULL), NULL);
    if (objCipher->editKey == NULL) {
        Result = -1;
        return(Result);
    } else {
        hdc = GetDC(objCipher->editKey);
        CreateDefaultFont(&fontDefault, &hdc);
        SendMessage(objCipher->editKey, WM_SETFONT, (WPARAM)fontDefault, 0);
    }

    GetWindowRect(objCipher->labelKeyword, &leftRect);
    AdjustRectToWindow(&leftRect, hPWnd);

    objCipher->labelShift = CreateWindowEx(0, "STATIC", "", 
        baseStyle | SS_LEFT, 
        leftRect.right+30, leftRect.top, 60, BUTTONHEIGHT, 
        *hPWnd, (HMENU)IDC_LABEL_SHIFT, GetModuleHandle(NULL), NULL);
    if (objCipher->labelShift == NULL) {
        Result = -1;
        return(Result);
    }

    GetWindowRect(objCipher->labelShift, &topRect);
    AdjustRectToWindow(&topRect, hPWnd);

    objCipher->comboShift = CreateWindow(WC_COMBOBOX, "", 
        baseStyle | WS_TABSTOP | WS_VSCROLL | CBS_DROPDOWNLIST | CBS_HASSTRINGS,
        topRect.left, topRect.bottom+10, 60, COMBOHEIGHT, 
        *hPWnd, (HMENU)IDC_COMBO_SHIFTLIST, GetModuleHandle(NULL), NULL);
    if (objCipher->comboShift == NULL) {
        Result = -1;
        return(Result);
    } else {
        SendMessage(objCipher->comboShift, CB_SETMINVISIBLE, (WPARAM)5, 0);
        hdc = GetDC(objCipher->comboShift);
        CreateDefaultFont(&fontDefault, &hdc);
        SendMessage(objCipher->comboShift, WM_SETFONT, 
            (WPARAM)fontDefault, TRUE);
        char buffer[3];
        for (int i = 0; i < ALPHABET_LENGTH; i++) {
            sprintf(buffer, "%d", i);
            SendMessage(objCipher->comboShift, (UINT)CB_ADDSTRING,
                (WPARAM)0, (LPARAM)buffer);
        }
        SendMessage(objCipher->comboShift, CB_SETCURSEL, 
            (WPARAM)objCipher->baseSelected, (LPARAM)0);
    }

    GetWindowRect(objCipher->labelShift, &leftRect);
    AdjustRectToWindow(&leftRect, hPWnd);

    objCipher->buttonEncrypt = CreateWindow("BUTTON", "OK", 
        baseStyle | WS_TABSTOP | BS_PUSHBUTTON,
        XEND-75, leftRect.top, 75, BUTTONHEIGHT,
        *hPWnd, (HMENU)IDC_BUTTON_ENCRYPT, GetModuleHandle(NULL), NULL);
    if (objCipher->buttonEncrypt == NULL) {
        Result = -1;
        return(Result);
    } else {
        hdc = GetDC(objCipher->buttonEncrypt);
        CreateDefaultFont(&fontDefault, &hdc);
        SendMessage(objCipher->buttonEncrypt, WM_SETFONT, 
            (WPARAM)fontDefault, 0);
        SetWindowText(objCipher->buttonEncrypt, "Encrypt");
    }

    GetWindowRect(objCipher->comboShift, &leftRect);
    AdjustRectToWindow(&leftRect, hPWnd);

    objCipher->buttonDecrypt = CreateWindow("BUTTON", "OK", 
        baseStyle | WS_TABSTOP | BS_PUSHBUTTON,
        XEND-75, leftRect.top, 75, BUTTONHEIGHT,
        *hPWnd, (HMENU)IDC_BUTTON_DECRYPT, GetModuleHandle(NULL), NULL);
    if (objCipher->buttonDecrypt == NULL) {
        Result = -1;
        return(Result);
    } else {
        hdc = GetDC(objCipher->buttonDecrypt);
        CreateDefaultFont(&fontDefault, &hdc);
        SendMessage(objCipher->buttonDecrypt, WM_SETFONT, 
            (WPARAM)fontDefault, 0);
        SetWindowText(objCipher->buttonDecrypt, "Decrypt");
    }

    GetWindowRect(objCipher->editKey, &topRect);
    AdjustRectToWindow(&topRect, hPWnd);

    objCipher->labelInput = CreateWindowEx(0, "STATIC", "", 
        baseStyle | SS_LEFT, 
        topRect.left, topRect.bottom+20, TEXTBOXWIDTH, BUTTONHEIGHT, 
        *hPWnd, (HMENU)IDC_LABEL_INPUTTEXT, GetModuleHandle(NULL), NULL);
    if (objCipher->labelInput == NULL) {
        Result = -1;
        return(Result);
    }

    GetWindowRect(objCipher->labelInput, &topRect);
    AdjustRectToWindow(&topRect, hPWnd);

    objCipher->editInput = CreateWindowEx(0, "EDIT", "", 
        baseStyle | WS_TABSTOP | WS_VSCROLL | ES_AUTOVSCROLL | ES_MULTILINE | ES_LEFT | ES_WANTRETURN, 
        topRect.left, topRect.bottom+10, TEXTBOXWIDTH, YEND-topRect.bottom-10, 
        *hPWnd, (HMENU)IDC_EDIT_CIPHERTEXT, GetModuleHandle(NULL), NULL);
    if (objCipher->editInput == NULL) {
        Result = -1;
        return(Result);
    } else {
        SetWindowSubclass(objCipher->editInput, MultiLineWindowProc, 0, 0);
        hdc = GetDC(objCipher->editInput);
        CreateDefaultFont(&fontDefault, &hdc);
        SendMessage(objCipher->editInput, WM_SETFONT, 
        	(WPARAM)fontDefault, 0);
        SendMessage(objCipher->editInput, EM_SETLIMITTEXT, MAX_ARRAY_LENGTH, 0);
    }

    if (objCipher->dataStored) {
        char buffer[MAX_ARRAY_LENGTH];
        sprintf(buffer, "%s", objCipher->key);
        SetWindowText(objCipher->editKey, buffer);
        sprintf(buffer, "%s", objCipher->input);
        SetWindowText(objCipher->editInput, buffer);
    }

    GetWindowRect(objCipher->editKey, &leftRect);
    AdjustRectToWindow(&leftRect, hPWnd);

    GetWindowRect(objCipher->editKey, &topRect);
    GetWindowRect(objCipher->labelInput, &leftRect);
    AdjustRectToWindow(&topRect, hPWnd);
    AdjustRectToWindow(&leftRect, hPWnd);

    objCipher->labelOutput = CreateWindowEx(0, "STATIC", "", 
        baseStyle | SS_LEFT, 
        topRect.right+30, leftRect.top, TEXTBOXWIDTH, BUTTONHEIGHT, 
        *hPWnd, (HMENU)IDC_LABEL_CIPHEROUTPUT, GetModuleHandle(NULL), NULL);
    if (objCipher->labelOutput == NULL) {
        Result = -1;
        return(Result);
    }

    GetWindowRect(objCipher->labelOutput, &topRect);
    GetWindowRect(objCipher->editInput, &leftRect);
    AdjustRectToWindow(&topRect, hPWnd);
    AdjustRectToWindow(&leftRect, hPWnd);

    objCipher->staticOutput = CreateWindowEx(0, "EDIT", "",
        baseStyle | WS_VSCROLL | ES_READONLY | ES_MULTILINE | ES_LEFT, 
        topRect.left, leftRect.top, TEXTBOXWIDTH, leftRect.bottom-leftRect.top,
        *hPWnd, (HMENU)IDC_STATIC_CIPHEROUTPUT, GetModuleHandle(NULL), NULL);
    if (objCipher->staticOutput == NULL) {
        Result = -1;
        return(Result);
    }

    return (Result);
}


LRESULT DestroyCipherWindow(Cipher *objCipher) {
    LRESULT Result = 0;
    if (!DestroyWindow(objCipher->labelKeyword)) {
        Result = -1;
    }
    if (!DestroyWindow(objCipher->editKey)) {
        Result = -1;
    }
    if (!DestroyWindow(objCipher->labelShift)) {
        Result = -1;
    }
    if (!DestroyWindow(objCipher->comboShift)) {
        Result = -1;
    }
    if (!DestroyWindow(objCipher->labelInput)) {
        Result = -1;
    }
    if (!DestroyWindow(objCipher->editInput)) {
        Result = -1;
    }
    if (!DestroyWindow(objCipher->buttonEncrypt)) {
        Result = -1;
    }
    if (!DestroyWindow(objCipher->buttonDecrypt)) {
        Result = -1;
    }
    if (!DestroyWindow(objCipher->labelOutput)) {
        Result = -1;
    }
    if (!DestroyWindow(objCipher->staticOutput)) {
        Result = -1;
    }
    return (Result);
}