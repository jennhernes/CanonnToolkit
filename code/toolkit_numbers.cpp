#include <windows.h>
#include <CommCtrl.h>
#include "definitions.h"
#include "toolkit_numbers.h"


LRESULT CALLBACK MultiLineWindowProc(HWND hwnd, UINT uMsg, 
                                     WPARAM wParam, LPARAM lParam,
                                     UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

LRESULT PaintNumbersWindow(HWND *hPWnd, Numbers *objNumbers) {
    LRESULT Result = 0;
    DWORD baseStyle = WS_CHILD | WS_VISIBLE;

    RECT rect;
    SetRect(&rect, XDIVIDER, 0, CLIENT_WIDTH, CLIENT_HEIGHT);
    HDC hdc = GetDC(*hPWnd);
    FillRect(hdc, &rect, CreateSolidBrush(CANONN_DARKGRAY_RGB));

    HFONT fontDefault;

    RECT topRect;
    RECT leftRect;

    objNumbers->labelNumBase = CreateWindowEx(0, "STATIC", "", 
        baseStyle | SS_LEFT, 
        XSTART, YSTART, TEXTBOXWIDTH, BUTTONHEIGHT, 
        *hPWnd, (HMENU)IDC_LABEL_NUMBASE, GetModuleHandle(NULL), NULL);
    if (objNumbers->labelNumBase == NULL) {
        Result = -1;
        return(Result);
    }

    GetWindowRect(objNumbers->labelNumBase, &rect);
    AdjustRectToWindow(&rect, hPWnd);

    GetWindowRect(objNumbers->labelNumBase, &topRect);
    AdjustRectToWindow(&topRect, hPWnd);

    objNumbers->comboNumBase = CreateWindow(WC_COMBOBOX, "", 
        baseStyle | WS_TABSTOP | WS_VSCROLL | CBS_DROPDOWNLIST | CBS_HASSTRINGS,
        topRect.left, topRect.bottom+10, 140, COMBOHEIGHT, 
        *hPWnd, (HMENU)IDC_COMBO_BASELIST, GetModuleHandle(NULL), NULL);
    if (objNumbers->comboNumBase == NULL) {
        Result = -1;
        return(Result);
    } else {
        SendMessage(objNumbers->comboNumBase, CB_SETMINVISIBLE, (WPARAM)5, 0);
        hdc = GetDC(objNumbers->comboNumBase);
        CreateDefaultFont(&fontDefault, &hdc);
        SendMessage(objNumbers->comboNumBase, WM_SETFONT, 
        	(WPARAM)fontDefault, TRUE);
        SendMessage(objNumbers->comboNumBase, (UINT)CB_ADDSTRING, 
            (WPARAM)0, (LPARAM)objNumbers->numBaseList[0]);
        SendMessage(objNumbers->comboNumBase, (UINT)CB_ADDSTRING, 
            (WPARAM)0, (LPARAM)objNumbers->numBaseList[1]);
        SendMessage(objNumbers->comboNumBase, (UINT)CB_ADDSTRING, 
            (WPARAM)0, (LPARAM)objNumbers->numBaseList[2]);
        SendMessage(objNumbers->comboNumBase, (UINT)CB_ADDSTRING, 
            (WPARAM)0, (LPARAM)objNumbers->numBaseList[3]);
        SendMessage(objNumbers->comboNumBase, (UINT)CB_ADDSTRING, 
            (WPARAM)0, (LPARAM)objNumbers->numBaseList[4]);
        SendMessage(objNumbers->comboNumBase, CB_SETCURSEL, 
            (WPARAM)objNumbers->baseSelected, (LPARAM)0);
    }

    GetWindowRect(objNumbers->comboNumBase, &rect);
    AdjustRectToWindow(&rect, hPWnd);

    GetWindowRect(objNumbers->labelNumBase, &topRect);
    AdjustRectToWindow(&topRect, hPWnd);

    objNumbers->buttonConvert = CreateWindow("BUTTON", "OK",
        baseStyle | WS_TABSTOP | BS_PUSHBUTTON,
        topRect.right+30, topRect.bottom+10, 75, BUTTONHEIGHT,
        *hPWnd, (HMENU)IDC_BUTTON_NUMTOASCII, GetModuleHandle(NULL), NULL);
    if (objNumbers->buttonConvert == NULL) {
        Result = -1;
        return(Result);
    } else {
        hdc = GetDC(objNumbers->buttonConvert);
        CreateDefaultFont(&fontDefault, &hdc);
        SendMessage(objNumbers->buttonConvert, WM_SETFONT, 
            (WPARAM)fontDefault, 0);
        SetWindowText(objNumbers->buttonConvert, "Convert");
    }

    GetWindowRect(objNumbers->buttonConvert, &rect);
    AdjustRectToWindow(&rect, hPWnd);

    GetWindowRect(objNumbers->comboNumBase, &topRect);
    AdjustRectToWindow(&topRect, hPWnd);

    objNumbers->labelInput = CreateWindowEx(0, "STATIC", "", 
        baseStyle | SS_LEFT, 
        topRect.left, topRect.bottom+20, TEXTBOXWIDTH, BUTTONHEIGHT, 
        *hPWnd, (HMENU)IDC_LABEL_NUMBERSINPUT, GetModuleHandle(NULL), NULL);
    if (objNumbers->labelInput == NULL) {
        Result = -1;
        return(Result);
    }

    GetWindowRect(objNumbers->labelInput, &rect);
    AdjustRectToWindow(&rect, hPWnd);

    GetWindowRect(objNumbers->labelInput, &topRect);
    AdjustRectToWindow(&topRect, hPWnd);

    objNumbers->editNumber = CreateWindowEx(0, "EDIT", "",
        baseStyle | WS_TABSTOP | WS_VSCROLL | ES_AUTOVSCROLL | ES_MULTILINE | ES_LEFT, 
        topRect.left, topRect.bottom+10, TEXTBOXWIDTH, YEND-topRect.bottom-10,
        *hPWnd, (HMENU)IDC_EDIT_NUMBER, GetModuleHandle(NULL), NULL);
    if (objNumbers->editNumber == NULL) {
        Result = -1;
        return(Result);
    } else {
        SetWindowSubclass(objNumbers->editNumber, MultiLineWindowProc, 0, 0);
        hdc = GetDC(objNumbers->editNumber);
        CreateDefaultFont(&fontDefault, &hdc);
        SendMessage(objNumbers->editNumber, WM_SETFONT, (WPARAM)fontDefault, 0);
    }

    GetWindowRect(objNumbers->labelInput, &rect);
    AdjustRectToWindow(&rect, hPWnd);

    if (objNumbers->dataStored) {
        char buffer[MAX_ARRAY_LENGTH];
        sprintf(buffer, "%s", objNumbers->userInput);
        SetWindowText(objNumbers->editNumber, buffer);
    }

    GetWindowRect(objNumbers->buttonConvert, &topRect);
    GetWindowRect(objNumbers->labelInput, &leftRect);
    AdjustRectToWindow(&topRect, hPWnd);
    AdjustRectToWindow(&leftRect, hPWnd);

    objNumbers->labelOutput = CreateWindowEx(0, "STATIC", "", 
        baseStyle | SS_LEFT, 
        topRect.left, leftRect.top, TEXTBOXWIDTH, BUTTONHEIGHT, 
        *hPWnd, (HMENU)IDC_LABEL_NUMBERSOUTPUT, GetModuleHandle(NULL), NULL);
    if (objNumbers->labelOutput == NULL) {
        Result = -1;
        return(Result);
    }

    GetWindowRect(objNumbers->labelOutput, &rect);
    AdjustRectToWindow(&rect, hPWnd);

    GetWindowRect(objNumbers->labelOutput, &topRect);
    GetWindowRect(objNumbers->editNumber, &leftRect);
    AdjustRectToWindow(&topRect, hPWnd);
    AdjustRectToWindow(&leftRect, hPWnd);

    objNumbers->staticAscii = CreateWindowEx(0, "EDIT", "",
        baseStyle | WS_VSCROLL | ES_READONLY | ES_MULTILINE | ES_LEFT, 
        topRect.left, leftRect.top, TEXTBOXWIDTH, leftRect.bottom-leftRect.top,
        *hPWnd, (HMENU)IDC_STATIC_NUMBER, GetModuleHandle(NULL), NULL);
    if (objNumbers->staticAscii == NULL) {
        Result = -1;
        return(Result);
    }

    return (Result);
}


LRESULT DestroyNumbersWindow(Numbers *objNumbers) {
    LRESULT Result = 0;

    objNumbers->baseSelected = (int)SendMessage(objNumbers->comboNumBase, 
        CB_GETCURSEL, 0, 0);
    if (!DestroyWindow(objNumbers->labelNumBase)) {
        Result = -1;
    }
    if (!DestroyWindow(objNumbers->comboNumBase)) {
        Result = -1;
    }
    if (!DestroyWindow(objNumbers->labelInput)) {
        Result = -1;
    }
    if (!DestroyWindow(objNumbers->editNumber)) {
        Result = -1;
    }
    if (!DestroyWindow(objNumbers->buttonConvert)) {
        Result = -1;
    }
    if (!DestroyWindow(objNumbers->labelOutput)) {
        Result = -1;
    }
    if (!DestroyWindow(objNumbers->staticAscii)) {
        Result = -1;
    }

    return (Result);
}