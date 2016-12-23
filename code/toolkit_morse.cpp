#include <windows.h>
#include "definitions.h"
#include "toolkit_morse.h"


LRESULT CALLBACK MultiLineWindowProc(HWND hwnd, UINT uMsg, 
                                     WPARAM wParam, LPARAM lParam,
                                     UINT_PTR uIdSubclass, DWORD_PTR dwRefData);


LRESULT PaintMorseWindow(HWND *hPWnd, Morse *objMorse) {
    LRESULT Result = 0;
    DWORD baseStyle = WS_CHILD | WS_VISIBLE;

    RECT rect;
    SetRect(&rect, XDIVIDER, 0, CLIENT_WIDTH, CLIENT_HEIGHT);
    HDC hdc = GetDC(*hPWnd);
    FillRect(hdc, &rect, CreateSolidBrush(CANONN_DARKGRAY_RGB));

    HFONT fontDefault;

    RECT topRect;
    RECT leftRect;
    
    objMorse->buttonConvert = CreateWindow("BUTTON", "OK", 
        baseStyle | WS_TABSTOP | BS_PUSHBUTTON,
        XSTART, YSTART, 75, BUTTONHEIGHT,
        *hPWnd, (HMENU)IDC_BUTTON_MORSETOASCII, GetModuleHandle(NULL), NULL);
    if (objMorse->buttonConvert == NULL) {
        Result = -1;
        return(Result);
    } else {
        hdc = GetDC(objMorse->buttonConvert);
        CreateDefaultFont(&fontDefault, &hdc);
        SendMessage(objMorse->buttonConvert, WM_SETFONT, 
            (WPARAM)fontDefault, 0);
        SetWindowText(objMorse->buttonConvert, "Convert");
    }

    GetWindowRect(objMorse->buttonConvert, &rect);
    AdjustRectToWindow(&rect, hPWnd);

    GetWindowRect(objMorse->buttonConvert, &topRect);
    AdjustRectToWindow(&topRect, hPWnd);

    objMorse->labelMorse = CreateWindowEx(0, "STATIC", "", 
        baseStyle | SS_LEFT, 
        topRect.left, topRect.bottom+20, TEXTBOXWIDTH, BUTTONHEIGHT, 
        *hPWnd, (HMENU)IDC_LABEL_MORSEINPUT, GetModuleHandle(NULL), NULL);
    if (objMorse->labelMorse == NULL) {
        Result = -1;
        return(Result);
    }

    GetWindowRect(objMorse->labelMorse, &rect);
    AdjustRectToWindow(&rect, hPWnd);

    GetWindowRect(objMorse->labelMorse, &topRect);
    AdjustRectToWindow(&topRect, hPWnd);

    objMorse->editMorse = CreateWindowEx(0, "EDIT", "", 
        baseStyle | WS_TABSTOP | WS_VSCROLL | ES_AUTOVSCROLL | ES_MULTILINE | ES_LEFT, 
        topRect.left, topRect.bottom+10, TEXTBOXWIDTH, YEND-topRect.bottom-10, 
        *hPWnd, (HMENU)IDC_EDIT_MORSEINPUT, GetModuleHandle(NULL), NULL);
    if (objMorse->editMorse == NULL) {
        Result = -1;
        return(Result);
    } else {
        SetWindowSubclass(objMorse->editMorse, MultiLineWindowProc, 0, 0);
        hdc = GetDC(objMorse->editMorse);
        CreateDefaultFont(&fontDefault, &hdc);
        SendMessage(objMorse->editMorse, WM_SETFONT, (WPARAM)fontDefault, 0);
    }

    GetWindowRect(objMorse->editMorse, &rect);
    AdjustRectToWindow(&rect, hPWnd);

    if (objMorse->dataStored) {
        char buffer[MAX_ARRAY_LENGTH];
        sprintf(buffer, "%s", objMorse->userInput);
        SetWindowText(objMorse->editMorse, buffer);
    }

    GetWindowRect(objMorse->editMorse, &leftRect);
    AdjustRectToWindow(&leftRect, hPWnd);

    GetWindowRect(objMorse->labelMorse, &leftRect);
    AdjustRectToWindow(&leftRect, hPWnd);

    objMorse->labelAscii = CreateWindowEx(0, "STATIC", "", 
        baseStyle | SS_LEFT, 
        leftRect.right+30, leftRect.top, TEXTBOXWIDTH, BUTTONHEIGHT, 
        *hPWnd, (HMENU)IDC_LABEL_MORSEOUTPUT, GetModuleHandle(NULL), NULL);
    if (objMorse->labelAscii == NULL) {
        Result = -1;
        return(Result);
    }

    GetWindowRect(objMorse->labelAscii, &rect);
    AdjustRectToWindow(&rect, hPWnd);

    GetWindowRect(objMorse->labelAscii, &topRect);
    GetWindowRect(objMorse->editMorse, &leftRect);
    AdjustRectToWindow(&topRect, hPWnd);
    AdjustRectToWindow(&leftRect, hPWnd);

    objMorse->staticAscii = CreateWindowEx(0, "EDIT", "",
        baseStyle | WS_VSCROLL | ES_READONLY | ES_MULTILINE | ES_LEFT, 
        topRect.left, leftRect.top, TEXTBOXWIDTH, leftRect.bottom-leftRect.top,
        *hPWnd, (HMENU)IDC_STATIC_MORSE, GetModuleHandle(NULL), NULL);
    if (objMorse->staticAscii == NULL) {
        Result = -1;
        return(Result);
    }

    return (Result);
}


LRESULT DestroyMorseWindow(Morse *objMorse) {
    LRESULT Result = 0;

    if (!DestroyWindow(objMorse->labelMorse)) {
        Result = -1;
    }
    if (!DestroyWindow(objMorse->editMorse)) {
        Result = -1;
    }
    if (!DestroyWindow(objMorse->buttonConvert)) {
        Result = -1;
    }
    if (!DestroyWindow(objMorse->labelAscii)) {
        Result = -1;
    }
    if (!DestroyWindow(objMorse->staticAscii)) {
        Result = -1;
    }

    return (Result);
}