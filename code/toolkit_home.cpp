#include <windows.h>
#include "definitions.h"
#include "toolkit_home.h"


LRESULT PaintHomeWindow(HWND *hPWnd, Home *objHome) {
    LRESULT Result = 0;
    DWORD baseStyle = WS_CHILD | WS_VISIBLE;

    RECT rect;
    SetRect(&rect, XDIVIDER, 0, CLIENT_WIDTH, CLIENT_HEIGHT);
    HDC hdc = GetDC(*hPWnd);
    FillRect(hdc, &rect, CreateSolidBrush(CANONN_DARKGRAY_RGB));

    RECT topRect;
    RECT leftRect;


    objHome->staticTitle = CreateWindowEx(0, "STATIC", "", 
        baseStyle | SS_LEFT, 
        XSTART, YSTART, TEXTBOXWIDTH*2, BUTTONHEIGHT, 
        *hPWnd, (HMENU)IDC_STATIC_TITLE, GetModuleHandle(NULL), NULL);
    if (objHome->staticTitle == NULL) {
        Result = -1;
        return(Result);
    }

    GetWindowRect(objHome->staticTitle, &topRect);
    AdjustRectToWindow(&topRect, hPWnd);

    objHome->staticDesc0 = CreateWindowEx(0, "STATIC", "", 
        baseStyle | SS_LEFT | SS_NOTIFY, 
        XSTART, topRect.bottom+20, TEXTBOXWIDTH*2, EDITHEIGHT, 
        *hPWnd, (HMENU)IDC_STATIC_DESC0, GetModuleHandle(NULL), NULL);
    if (objHome->staticDesc0 == NULL) {
        Result = -1;
        return(Result);
    }

    GetWindowRect(objHome->staticDesc0, &topRect);
    AdjustRectToWindow(&topRect, hPWnd);

    int width = 220;
    objHome->staticDesc1 = CreateWindowEx(0, "STATIC", "", 
        baseStyle | SS_LEFT | SS_NOTIFY, 
        XSTART, topRect.bottom+10, width, EDITHEIGHT, 
        *hPWnd, (HMENU)IDC_STATIC_DESC1, GetModuleHandle(NULL), NULL);
    if (objHome->staticDesc1 == NULL) {
        Result = -1;
        return(Result);
    }

    GetWindowRect(objHome->staticDesc1, &topRect);
    AdjustRectToWindow(&topRect, hPWnd);

    objHome->staticDesc2 = CreateWindowEx(0, "STATIC", "", 
        baseStyle | SS_LEFT | SS_NOTIFY, 
        XSTART, topRect.bottom+5, width, EDITHEIGHT, 
        *hPWnd, (HMENU)IDC_STATIC_DESC2, GetModuleHandle(NULL), NULL);
    if (objHome->staticDesc2 == NULL) {
        Result = -1;
        return(Result);
    }

    GetWindowRect(objHome->staticDesc2, &topRect);
    AdjustRectToWindow(&topRect, hPWnd);

    objHome->staticDesc3 = CreateWindowEx(0, "STATIC", "", 
        baseStyle | SS_LEFT | SS_NOTIFY, 
        XSTART, topRect.bottom+5, width, EDITHEIGHT, 
        *hPWnd, (HMENU)IDC_STATIC_DESC3, GetModuleHandle(NULL), NULL);
    if (objHome->staticDesc3 == NULL) {
        Result = -1;
        return(Result);
    }

    GetWindowRect(objHome->staticDesc3, &topRect);
    AdjustRectToWindow(&topRect, hPWnd);

    objHome->staticDesc4 = CreateWindowEx(0, "STATIC", "", 
        baseStyle | SS_LEFT | SS_NOTIFY, 
        XSTART, topRect.bottom+5, width, EDITHEIGHT, 
        *hPWnd, (HMENU)IDC_STATIC_DESC4, GetModuleHandle(NULL), NULL);
    if (objHome->staticDesc4 == NULL) {
        Result = -1;
        return(Result);
    }

    GetWindowRect(objHome->staticDesc4, &topRect);
    AdjustRectToWindow(&topRect, hPWnd);

    objHome->staticDesc5 = CreateWindowEx(0, "STATIC", "", 
        baseStyle | SS_LEFT | SS_NOTIFY, 
        XSTART, topRect.bottom+5, width, EDITHEIGHT, 
        *hPWnd, (HMENU)IDC_STATIC_DESC5, GetModuleHandle(NULL), NULL);
    if (objHome->staticDesc5 == NULL) {
        Result = -1;
        return(Result);
    }

    GetWindowRect(objHome->staticDesc1, &topRect);
    AdjustRectToWindow(&topRect, hPWnd);

    width = 230;
    int height = width * 2 / 5;
    int y = (topRect.top+topRect.bottom)/2;
    objHome->canonnLogo = (HBITMAP)LoadImage(NULL, 
        objHome->logoLocation, IMAGE_BITMAP, width, height, 
        LR_LOADFROMFILE);
    Result = GetLastError();
    Result = Result;
    if (objHome->canonnLogo != NULL) {
        objHome->staticLogo = CreateWindowEx(0, "STATIC", "", 
            baseStyle | SS_BITMAP, 
            CLIENT_WIDTH-YSTART-width, y, width, height, 
            *hPWnd, (HMENU)IDC_STATIC_LOGO, GetModuleHandle(NULL), NULL);
        if (objHome->staticLogo == NULL) {
            Result = -1;
            return(Result);
        } else {
            SendMessage(objHome->staticLogo, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, 
                (LPARAM)objHome->canonnLogo);
        }
    }

    GetWindowRect(objHome->staticDesc5, &topRect);
    AdjustRectToWindow(&topRect, hPWnd);

    height = 55;
    width = 160;
    objHome->staticContact = CreateWindowEx(0, "EDIT", "",
        baseStyle | ES_READONLY | ES_MULTILINE | ES_LEFT,
        topRect.left, topRect.bottom+20, width, height,
        *hPWnd, (HMENU)IDC_STATIC_CONTACT, GetModuleHandle(NULL), NULL);
    if (objHome->staticContact == NULL) {
        Result = -1;
        return (Result);
    }

    GetWindowRect(objHome->staticContact, &leftRect);
    AdjustRectToWindow(&leftRect, hPWnd);

    objHome->staticDonate = CreateWindowEx(0, "STATIC", "",
        baseStyle | SS_LEFT,
        leftRect.right+30, leftRect.top, width, height,
        *hPWnd, (HMENU)IDC_STATIC_DONATE, GetModuleHandle(NULL), NULL);
    if (objHome->staticDonate == NULL) {
        Result = -1;
        return (Result);
    }

    GetWindowRect(objHome->staticDonate, &leftRect);
    AdjustRectToWindow(&leftRect, hPWnd);

    objHome->bitmapDonate = (HBITMAP)LoadImage(NULL, 
        objHome->donateBitmapLocation, IMAGE_BITMAP, 0, 0, 
        LR_CREATEDIBSECTION | LR_LOADFROMFILE);
    if (objHome->bitmapDonate != NULL) {
        objHome->buttonDonate = CreateWindow("BUTTON", "Donate", 
            baseStyle | WS_TABSTOP | BS_BITMAP,
            XEND-objHome->buttonWidth, leftRect.top, 
            objHome->buttonWidth, objHome->buttonHeight, 
            *hPWnd, (HMENU)IDC_BUTTON_DONATE, NULL, NULL);
        if (objHome->buttonDonate != NULL) {
            SendMessage(objHome->buttonDonate, BM_SETIMAGE, IMAGE_BITMAP, 
                (LPARAM)objHome->bitmapDonate);
        }
    } else {
        objHome->buttonDonate = CreateWindow("BUTTON", "Donate", 
            baseStyle | WS_TABSTOP | BS_PUSHBUTTON,
            XEND-objHome->buttonWidth, leftRect.top, 
            objHome->buttonWidth, objHome->buttonHeight, 
            *hPWnd, (HMENU)IDC_BUTTON_DONATE, NULL, NULL);
    }
    if (objHome->buttonDonate == NULL) {
        Result = -1;
        return(Result);
    }

    GetWindowRect(objHome->staticDonate, &leftRect);
    AdjustRectToWindow(&leftRect, hPWnd);
    GetWindowRect(objHome->buttonDonate, &topRect);
    AdjustRectToWindow(&topRect, hPWnd);

    objHome->staticUpdate = CreateWindowEx(0, "STATIC", "", 
        baseStyle | SS_LEFT | SS_NOTIFY, 
        leftRect.right, topRect.bottom+10, width, EDITHEIGHT, 
        *hPWnd, (HMENU)IDC_STATIC_UPDATE, GetModuleHandle(NULL), NULL);
    if (objHome->staticUpdate == NULL) {
        Result = -1;
        return(Result);
    }

    return (Result);
}


LRESULT DestroyHomeWindow(Home *objHome) {
    LRESULT Result = 0;

    if(!DestroyWindow(objHome->staticTitle)) {
        Result = -1;
    }
    if(!DestroyWindow(objHome->staticDesc0)) {
        Result = -1;
    }
    if(!DestroyWindow(objHome->staticDesc1)) {
        Result = -1;
    }
    if(!DestroyWindow(objHome->staticDesc2)) {
        Result = -1;
    }
    if(!DestroyWindow(objHome->staticDesc3)) {
        Result = -1;
    }
    if(!DestroyWindow(objHome->staticDesc4)) {
        Result = -1;
    }
    if(!DestroyWindow(objHome->staticDesc5)) {
        Result = -1;
    }
    if (!DestroyWindow(objHome->staticLogo)) {
        Result = -1;
    }
    if (!DestroyWindow(objHome->buttonDonate)) {
        Result = -1;
    }
    if(!DestroyWindow(objHome->staticContact)) {
        Result = -1;
    }
    if(!DestroyWindow(objHome->staticDonate)) {
        Result = -1;
    }
    if(!DestroyWindow(objHome->staticUpdate)) {
        Result = -1;
    }

    return (Result);
}
