#include <windows.h>
#include <Commctrl.h>
#include <cstdio>
#include "definitions.h"
#include "toolkit_bearing.h"


LRESULT PaintBearingWindow(HWND *hPWnd, Bearing *objBearing) {
    LRESULT Result = 0;
    DWORD baseStyle = WS_CHILD | WS_VISIBLE;

    RECT rect;
    SetRect(&rect, XDIVIDER, 0, CLIENT_WIDTH, CLIENT_HEIGHT);
    HDC hdc = GetDC(*hPWnd);
    FillRect(hdc, &rect, CreateSolidBrush(CANONN_DARKGRAY_RGB));

    HFONT fontDefault;

    RECT topRect;
    RECT leftRect;
    int col1End = 0;
    int labelWidth = 70;

    objBearing->labelStarting = CreateWindowEx(0, "STATIC", "", 
        baseStyle | SS_LEFT, 
        XSTART, YSTART, 130, BUTTONHEIGHT, 
        *hPWnd, (HMENU)IDC_LABEL_STARTING, GetModuleHandle(NULL), NULL);
    if (objBearing->labelStarting == NULL) {
        Result = -1;
        return(Result);
    }

    GetWindowRect(objBearing->labelStarting, &rect);
    AdjustRectToWindow(&rect, hPWnd);
    if (rect.right > col1End) {
    	col1End = rect.right;
    }

    GetWindowRect(objBearing->labelStarting, &topRect);
    AdjustRectToWindow(&topRect, hPWnd);

    objBearing->labelLat1 = CreateWindowEx(0, "STATIC", "", 
        baseStyle | SS_LEFT, 
        topRect.left, topRect.bottom+10, labelWidth, BUTTONHEIGHT, 
        *hPWnd, (HMENU)IDC_LABEL_LAT1, GetModuleHandle(NULL), NULL);
    if (objBearing->labelLat1 == NULL) {
        Result = -1;
        return(Result);
    }

    GetWindowRect(objBearing->labelLat1, &rect);
    AdjustRectToWindow(&rect, hPWnd);
    if (rect.right > col1End) {
        col1End = rect.right;
    }

    GetWindowRect(objBearing->labelStarting, &topRect);
    GetWindowRect(objBearing->labelLat1, &leftRect);
    AdjustRectToWindow(&topRect, hPWnd);
    AdjustRectToWindow(&leftRect, hPWnd);

    objBearing->editLat1 = CreateWindowEx(0, "EDIT", "", 
        baseStyle | WS_TABSTOP, 
        leftRect.right+10, leftRect.top, 65, EDITHEIGHT, 
        *hPWnd, (HMENU)IDC_EDIT_LAT1, GetModuleHandle(NULL), NULL);
    if (objBearing->editLat1 == NULL) {
        Result = -1;
        return(Result);
    } else {
        hdc = GetDC(objBearing->editLat1);
        CreateDefaultFont(&fontDefault, &hdc);
        SendMessage(objBearing->editLat1, WM_SETFONT, (WPARAM)fontDefault, 0);
        SendMessage(objBearing->editLat1, EM_SETCUEBANNER, 
        	(WPARAM)FALSE, (LPARAM)L"(-90,90]");
    }

    GetWindowRect(objBearing->editLat1, &rect);
    AdjustRectToWindow(&rect, hPWnd);
    if (rect.right > col1End) {
    	col1End = rect.right;
    }

    GetWindowRect(objBearing->labelLat1, &topRect);
    AdjustRectToWindow(&topRect, hPWnd);

    objBearing->labelLon1 = CreateWindowEx(0, "STATIC", "", 
        baseStyle | SS_LEFT, 
        topRect.left, topRect.bottom+10, labelWidth, BUTTONHEIGHT, 
        *hPWnd, (HMENU)IDC_LABEL_LON1, GetModuleHandle(NULL), NULL);
    if (objBearing->labelLon1 == NULL) {
        Result = -1;
        return(Result);
    }

    GetWindowRect(objBearing->labelLon1, &rect);
    AdjustRectToWindow(&rect, hPWnd);
    if (rect.right > col1End) {
    	col1End = rect.right;
    }

    GetWindowRect(objBearing->editLat1, &topRect);
    GetWindowRect(objBearing->labelLon1, &leftRect);
    AdjustRectToWindow(&topRect, hPWnd);
    AdjustRectToWindow(&leftRect, hPWnd);

    objBearing->editLon1 = CreateWindowEx(0, "EDIT", "", 
        baseStyle | WS_TABSTOP, 
        rect.right+10, leftRect.top, 75, EDITHEIGHT, 
        *hPWnd, (HMENU)IDC_EDIT_LON1, GetModuleHandle(NULL), NULL);
    if (objBearing->editLon1 == NULL) {
        Result = -1;
        return(Result);
    } else {
        hdc = GetDC(objBearing->editLon1);
        CreateDefaultFont(&fontDefault, &hdc);
        SendMessage(objBearing->editLon1, WM_SETFONT, (WPARAM)fontDefault, 0);
        SendMessage(objBearing->editLon1, EM_SETCUEBANNER, 
        	(WPARAM)FALSE, (LPARAM)L"(-180,180]");
    }

    GetWindowRect(objBearing->editLon1, &rect);
    AdjustRectToWindow(&rect, hPWnd);
    if (rect.right > col1End) {
    	col1End = rect.right;
    }

    GetWindowRect(objBearing->labelStarting, &leftRect);
    AdjustRectToWindow(&leftRect, hPWnd);

    objBearing->labelEnding = CreateWindowEx(0, "STATIC", "", 
        baseStyle | SS_LEFT, 
        col1End+30, leftRect.top, 110, BUTTONHEIGHT, 
        *hPWnd, (HMENU)IDC_LABEL_ENDING, GetModuleHandle(NULL), NULL);
    if (objBearing->labelEnding == NULL) {
        Result = -1;
        return(Result);
    }

    GetWindowRect(objBearing->labelEnding, &rect);
    AdjustRectToWindow(&rect, hPWnd);

    GetWindowRect(objBearing->labelEnding, &topRect);
    AdjustRectToWindow(&topRect, hPWnd);

    objBearing->labelLat2 = CreateWindowEx(0, "STATIC", "", 
        baseStyle | SS_LEFT, 
        topRect.left, topRect.bottom+10, labelWidth, BUTTONHEIGHT, 
        *hPWnd, (HMENU)IDC_LABEL_LAT2, GetModuleHandle(NULL), NULL);
    if (objBearing->labelLat2 == NULL) {
        Result = -1;
        return(Result);
    }

    GetWindowRect(objBearing->labelLat2, &rect);
    AdjustRectToWindow(&rect, hPWnd);

    GetWindowRect(objBearing->labelEnding, &topRect);
    GetWindowRect(objBearing->labelLat2, &leftRect);
    AdjustRectToWindow(&topRect, hPWnd);
    AdjustRectToWindow(&leftRect, hPWnd);

    objBearing->editLat2 = CreateWindowEx(0, "EDIT", "", 
        baseStyle | WS_TABSTOP, 
        leftRect.right+10, leftRect.top, 65, EDITHEIGHT, 
        *hPWnd, (HMENU)IDC_EDIT_LAT2, GetModuleHandle(NULL), NULL);
    if (objBearing->editLat2 == NULL) {
        Result = -1;
        return(Result);
    } else {
        hdc = GetDC(objBearing->editLat2);
        CreateDefaultFont(&fontDefault, &hdc);
        SendMessage(objBearing->editLat2, WM_SETFONT, (WPARAM)fontDefault, 0);
        SendMessage(objBearing->editLat2, EM_SETCUEBANNER, 
        	(WPARAM)FALSE, (LPARAM)L"(-90,90]");
    }

    GetWindowRect(objBearing->editLat2, &rect);
    AdjustRectToWindow(&rect, hPWnd);

    GetWindowRect(objBearing->labelLat2, &topRect);
    AdjustRectToWindow(&topRect, hPWnd);

    objBearing->labelLon2 = CreateWindowEx(0, "STATIC", "", 
        baseStyle | SS_LEFT, 
        topRect.left, topRect.bottom+10, labelWidth, BUTTONHEIGHT, 
        *hPWnd, (HMENU)IDC_LABEL_LON2, GetModuleHandle(NULL), NULL);
    if (objBearing->labelLon2 == NULL) {
        Result = -1;
        return(Result);
    }

    GetWindowRect(objBearing->labelLon2, &rect);
    AdjustRectToWindow(&rect, hPWnd);

    GetWindowRect(objBearing->editLat2, &topRect);
    GetWindowRect(objBearing->labelLon2, &leftRect);
    AdjustRectToWindow(&topRect, hPWnd);
    AdjustRectToWindow(&leftRect, hPWnd);

    objBearing->editLon2 = CreateWindowEx(0, "EDIT", "", 
        baseStyle | WS_TABSTOP, 
        leftRect.right+10, leftRect.top, 75, EDITHEIGHT, 
        *hPWnd, (HMENU)IDC_EDIT_LON2, GetModuleHandle(NULL), NULL);
    if (objBearing->editLon2 == NULL) {
        Result = -1;
        return(Result);
    } else {
        hdc = GetDC(objBearing->editLon2);
        CreateDefaultFont(&fontDefault, &hdc);
        SendMessage(objBearing->editLon2, WM_SETFONT, (WPARAM)fontDefault, 0);
        SendMessage(objBearing->editLon2, EM_SETCUEBANNER, 
        	(WPARAM)FALSE, (LPARAM)L"(-180,180]");
    }

    GetWindowRect(objBearing->editLon2, &rect);
    AdjustRectToWindow(&rect, hPWnd);

    if (objBearing->dataStored) {
        char buffer[MAX_ARRAY_LENGTH];
        sprintf(buffer, "%2.4f", objBearing->lat1);
        SetWindowText(objBearing->editLat1, buffer);
        sprintf(buffer, "%3.4f", objBearing->lon1);
        SetWindowText(objBearing->editLon1, buffer);
        sprintf(buffer, "%2.4f", objBearing->lat2);
        SetWindowText(objBearing->editLat2, buffer);
        sprintf(buffer, "%3.4f", objBearing->lon2);
        SetWindowText(objBearing->editLon2, buffer);
    }

    GetWindowRect(objBearing->labelLon1, &topRect);
    AdjustRectToWindow(&topRect, hPWnd);

    objBearing->buttonCalc = CreateWindow("BUTTON", "OK", 
        baseStyle | WS_TABSTOP | BS_PUSHBUTTON,
        topRect.left, topRect.bottom+20, 80, BUTTONHEIGHT, 
        *hPWnd, (HMENU)IDC_BUTTON_CALCBEARING, GetModuleHandle(NULL), NULL);
    if (objBearing->buttonCalc == NULL) {
        Result = -1;
        return(Result);
    } else {
        hdc = GetDC(objBearing->buttonCalc);
        CreateDefaultFont(&fontDefault, &hdc);
        SendMessage(objBearing->buttonCalc, WM_SETFONT, (WPARAM)fontDefault, 0);
        SetWindowText(objBearing->buttonCalc, "Calculate");
    }

    GetWindowRect(objBearing->buttonCalc, &rect);
    AdjustRectToWindow(&rect, hPWnd);

    GetWindowRect(objBearing->buttonCalc, &topRect);
    AdjustRectToWindow(&topRect, hPWnd);

    objBearing->staticBearing = CreateWindowEx(0, "STATIC", "", 
        baseStyle | SS_LEFT, 
        topRect.left, topRect.bottom+20, 170, BUTTONHEIGHT, 
        *hPWnd, (HMENU)IDC_STATIC_BEARING, GetModuleHandle(NULL), NULL);
    if (objBearing->staticBearing == NULL) {
        Result = -1;
        return(Result);
    }

    GetWindowRect(objBearing->staticBearing, &rect);
    AdjustRectToWindow(&rect, hPWnd);

    return (Result);
}


LRESULT DestroyBearingWindow(Bearing *objBearing) {
    LRESULT Result = 0;
    if (!DestroyWindow(objBearing->labelStarting)) {
        Result = -1;
    }
    if (!DestroyWindow(objBearing->labelLat1)) {
        Result = -1;
    }
    if (!DestroyWindow(objBearing->editLat1)) {
        Result = -1;
    }
    if (!DestroyWindow(objBearing->labelLon1)) {
        Result = -1;
    }
    if (!DestroyWindow(objBearing->editLon1)) {
        Result = -1;
    }
    if (!DestroyWindow(objBearing->labelEnding)) {
        Result = -1;
    }
    if (!DestroyWindow(objBearing->labelLat2)) {
        Result = -1;
    }
    if (!DestroyWindow(objBearing->editLat2)) {
        Result = -1;
    }
    if (!DestroyWindow(objBearing->labelLon2)) {
        Result = -1;
    }
    if (!DestroyWindow(objBearing->editLon2)) {
        Result = -1;
    }
    if (!DestroyWindow(objBearing->buttonCalc)) {
        Result = -1;
    }
    if (!DestroyWindow(objBearing->staticBearing)) {
        Result = -1;
    }
    return (Result);
}