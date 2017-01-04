#include <windows.h>
#include <string>
#include <exception>
#include <CommCtrl.h>
#include "definitions.h"
#include "toolkit.cpp"
#include "toolkit_home.cpp"
#include "toolkit_bearing.cpp"
#include "toolkit_numbers.cpp"
#include "toolkit_cipher.cpp"
#include "toolkit_morse.cpp"
#include "toolkit_notebook.cpp"

#pragma comment(lib, "comctl32.lib")
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


global_variable HWND *tabSelected = NULL;
global_variable HWND tabHome = NULL;
global_variable HWND tabBearing = NULL;
global_variable HWND tabNumbers = NULL;
global_variable HWND tabMorse = NULL;
global_variable HWND tabCipher = NULL;
global_variable HWND tabNotebook = NULL;

global_variable Home objHome;
global_variable Bearing objBearing;
global_variable Numbers objNumbers;
global_variable Morse objMorse;
global_variable Cipher objCipher;
global_variable Notebook objNotebook;

global_variable HWND hMain;

global_variable bool tabDown = false;


void DrawSingleTab(HWND *tab, LPARAM lParam) {
    LPDRAWITEMSTRUCT drawItem = (LPDRAWITEMSTRUCT)lParam;
    HGDIOBJ origPen = SelectObject(drawItem->hDC, GetStockObject(DC_PEN));
    HGDIOBJ origBrush = SelectObject(drawItem->hDC, GetStockObject(DC_BRUSH));

    if (origPen != NULL && origPen != HGDI_ERROR &&
        origBrush != NULL && origBrush != HGDI_ERROR) {

        HGDIOBJ newPen;
        HGDIOBJ backBrush;
        int rightExt = 0;
        int penWidth = 1;

        if (tabSelected == tab) {
            newPen = CreatePen(PS_SOLID, penWidth, CANONN_ORANGE_RGB);
            backBrush = CreateSolidBrush(CANONN_DARKGRAY_RGB);
            SetTextColor(drawItem->hDC, CANONN_ORANGE_RGB);
            rightExt = penWidth;
        } else {
            penWidth = 1;
            newPen = CreatePen(PS_SOLID, penWidth, CANONN_ORANGE_RGB);
            backBrush = CreateSolidBrush(CANONN_DARKGRAY_RGB);
            SetTextColor(drawItem->hDC, CANONN_DARKORANGE_RGB);
        }

        if (newPen != NULL && backBrush != NULL) {
            SelectObject(drawItem->hDC, newPen);
            SelectObject(drawItem->hDC, backBrush);
            Rectangle(drawItem->hDC, 
                drawItem->rcItem.left-penWidth, drawItem->rcItem.top,
                drawItem->rcItem.right+rightExt, drawItem->rcItem.bottom);

            SelectObject(drawItem->hDC, origBrush);
            DeleteObject(backBrush);
            SelectObject(drawItem->hDC, origPen);
            DeleteObject(newPen);
        }
    }

    HFONT fontTab;
    CreateTabFont(&fontTab, &drawItem->hDC);
    HGDIOBJ fOld = SelectObject(drawItem->hDC, fontTab);
    SetBkMode(drawItem->hDC, TRANSPARENT);

    char *text;
    if (tab == &tabHome) {
        text = TAB_HOME_NAME;
    } else if (tab == &tabBearing) {
        text = TAB_BEARING_NAME;
    } else if (tab == &tabNumbers) {
        text = TAB_NUMBERS_NAME;
    } else if (tab == &tabMorse) {
        text = TAB_MORSE_NAME;
    } else if (tab == &tabCipher) {
        text = TAB_CIPHER_NAME;
    } else if (tab == &tabNotebook) {
        text = TAB_NOTEBOOK_NAME;
    } else {
        text = "ERROR";
    }

    DrawText(drawItem->hDC, text, -1, &drawItem->rcItem, 
        DT_CENTER | DT_VCENTER | DT_SINGLELINE);


    if (fOld != NULL && fOld != HGDI_ERROR) {
        SelectObject(drawItem->hDC, fOld);
        DeleteObject(fontTab);
    }
}


LRESULT CreateTabs(HWND hPWnd) {
    LRESULT Result = 0;
    tabHome = CreateWindow("BUTTON", TAB_HOME_NAME,
        WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
        0, 0, XDIVIDER, TAB_HEIGHT, 
        hPWnd, (HMENU)IDC_TAB_HOME, NULL, NULL);

    if (tabHome == NULL) {
        Result = 1;
    }

    tabBearing = CreateWindow("BUTTON", TAB_BEARING_NAME,
        WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
        0, TAB_HEIGHT, XDIVIDER, TAB_HEIGHT, 
        hPWnd, (HMENU)IDC_TAB_BEARING, NULL, NULL);

    if (tabBearing == NULL) {
        Result = 1;
    }

    tabNumbers = CreateWindow("BUTTON", TAB_NUMBERS_NAME,
        WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
        0, TAB_HEIGHT*2, XDIVIDER, TAB_HEIGHT, 
        hPWnd, (HMENU)IDC_TAB_NUMBERS, NULL, NULL);

    if (tabNumbers == NULL) {
        Result = 1;
    }

    tabMorse = CreateWindow("BUTTON", TAB_MORSE_NAME,
        WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
        0, TAB_HEIGHT*3, XDIVIDER, TAB_HEIGHT, 
        hPWnd, (HMENU)IDC_TAB_MORSE, NULL, NULL);

    if (tabMorse == NULL) {
        Result = 1;
    }

    tabCipher = CreateWindow("BUTTON", TAB_CIPHER_NAME,
        WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
        0, TAB_HEIGHT*4, XDIVIDER, TAB_HEIGHT, 
        hPWnd, (HMENU)IDC_TAB_CIPHER, NULL, NULL);

    if (tabCipher == NULL) {
        Result = 1;
    }

    tabNotebook = CreateWindow("BUTTON", TAB_NOTEBOOK_NAME,
        WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
        0, TAB_HEIGHT*5, XDIVIDER, TAB_HEIGHT, 
        hPWnd, (HMENU)IDC_TAB_NOTEBOOK, NULL, NULL);

    if (tabNotebook == NULL) {
        Result = 1;
    }

    return (Result);
}


LRESULT DestroyWindow() {
    LRESULT Result = 0;

    if (tabSelected == &tabHome) {
        Result = DestroyHomeWindow(&objHome);
    } else if (tabSelected == &tabBearing) {
        Result = DestroyBearingWindow(&objBearing);
    } else if (tabSelected == &tabNumbers) {
        Result = DestroyNumbersWindow(&objNumbers);
    } else if (tabSelected == &tabMorse) {
        Result = DestroyMorseWindow(&objMorse);
    } else if (tabSelected == &tabCipher) {
        Result = DestroyCipherWindow(&objCipher);
    } else if (tabSelected == &tabNotebook) {
        Result = DestroyNotebookWindow(&objNotebook);
    }

    return (Result);
}


LRESULT CALLBACK WindowProc(HWND hwnd,
    						UINT uMsg,
    						WPARAM wParam,
    						LPARAM lParam) {
    if (uMsg == WM_CREATE) {
        LRESULT Result = 0;

        if (tabSelected == NULL) {
            Result = CreateTabs(hwnd);
            tabSelected = &tabHome;
        }

        if (tabSelected == &tabHome) {
            Result = PaintHomeWindow(&hwnd, &objHome);

        } else if (tabSelected == &tabBearing) {
            Result = PaintBearingWindow(&hwnd, &objBearing);

        } else if (tabSelected == &tabNumbers) {
            Result = PaintNumbersWindow(&hwnd, &objNumbers);

        } else if (tabSelected == &tabMorse) {
            Result = PaintMorseWindow(&hwnd, &objMorse);

        } else if (tabSelected == &tabCipher) {
            Result = PaintCipherWindow(&hwnd, &objCipher);

        } else if (tabSelected == &tabNotebook) {
            Result = PaintNotebookWindow(&hwnd, &objNotebook);
        }

        return (Result);

    } else if (uMsg == WM_PAINT) {
        if (tabSelected == &tabHome) {
            HDC hdc;
            PAINTSTRUCT ps;
            hdc = BeginPaint(hwnd,&ps);
            AddTextToWindow(objHome.staticTitle, objHome.title);
            AddTextToWindow(objHome.staticDesc0, objHome.desc0);
            AddTextToWindow(objHome.staticDesc1, objHome.desc1);
            AddTextToWindow(objHome.staticDesc2, objHome.desc2);
            AddTextToWindow(objHome.staticDesc3, objHome.desc3);
            AddTextToWindow(objHome.staticDesc4, objHome.desc4);
            AddTextToWindow(objHome.staticDesc5, objHome.desc5);
            AddTextToWindow(objHome.staticContact, objHome.contact);
            AddTextToWindow(objHome.staticDonate, objHome.donate);
            AddTextToWindow(objHome.staticUpdate, objHome.updateText);
            EndPaint(hwnd, &ps);

        } else if (tabSelected == &tabBearing) {
            HDC hdc;
            PAINTSTRUCT ps;
            hdc = BeginPaint(hwnd,&ps);
            AddTextToWindow(objBearing.labelStarting, "Current Position");
            AddTextToWindow(objBearing.labelLat1, "Latitude:");
            AddTextToWindow(objBearing.labelLon1, "Longitude:");
            AddTextToWindow(objBearing.labelEnding, "Destination");
            AddTextToWindow(objBearing.labelLat2, "Latitude:");
            AddTextToWindow(objBearing.labelLon2, "Longitude:");
            char buffer[MAX_ARRAY_LENGTH];
            if (sprintf(buffer, "Bearing = %3.4f\260",objBearing.bearing) > 0) {
                SetWindowText(objBearing.staticBearing, buffer);
            }
            EndPaint(hwnd, &ps);

        } else if (tabSelected == &tabNumbers) {
            HDC hdc;
            PAINTSTRUCT ps;
            hdc = BeginPaint(hwnd,&ps);
            AddTextToWindow(objNumbers.labelNumBase, "Select Number System");
            AddTextToWindow(objNumbers.labelInput, "Numbers");
            AddTextToWindow(objNumbers.labelOutput, "ASCII");

            HGDIOBJ origPen = SelectObject(hdc, GetStockObject(DC_PEN));

            if (origPen != NULL && origPen != HGDI_ERROR) {

                HGDIOBJ newPen;
                newPen = CreatePen(PS_SOLID, 1, CANONN_ORANGE_RGB);

                if (newPen != NULL) {
                    RECT rect;
                    GetWindowRect(objNumbers.staticAscii, &rect);
                    AdjustRectToWindow(&rect, &hwnd);

                    SelectObject(hdc, newPen);
                    Rectangle(hdc, rect.left-1, rect.top-1,
                        rect.right+1, rect.bottom+1);
                    SelectObject(hdc, origPen);
                    DeleteObject(newPen);
                }
            }

            AddTextToWindow(objNumbers.staticAscii, objNumbers.asciiOutput);
            EndPaint(hwnd, &ps);

        } else if (tabSelected == &tabMorse) {
            HDC hdc;
            PAINTSTRUCT ps;
            hdc = BeginPaint(hwnd,&ps);
            AddTextToWindow(objMorse.labelMorse, "Morse Code");
            AddTextToWindow(objMorse.labelAscii, "ASCII");

            HGDIOBJ origPen = SelectObject(hdc, GetStockObject(DC_PEN));

            if (origPen != NULL && origPen != HGDI_ERROR) {

                HGDIOBJ newPen;
                newPen = CreatePen(PS_SOLID, 1, CANONN_ORANGE_RGB);

                if (newPen != NULL) {
                    RECT rect;
                    GetWindowRect(objMorse.staticAscii, &rect);
                    AdjustRectToWindow(&rect, &hwnd);

                    SelectObject(hdc, newPen);
                    Rectangle(hdc, rect.left-1, rect.top-1,
                        rect.right+1, rect.bottom+1);
                    SelectObject(hdc, origPen);
                    DeleteObject(newPen);
                }
            }

            AddTextToWindow(objMorse.staticAscii, objMorse.asciiOutput);
            EndPaint(hwnd, &ps);

        } else if (tabSelected == &tabCipher) {
            HDC hdc;
            PAINTSTRUCT ps;
            hdc = BeginPaint(hwnd,&ps);
            AddTextToWindow(objCipher.labelKeyword, "Keyword");
            AddTextToWindow(objCipher.labelInput, "Text");
            AddTextToWindow(objCipher.labelShift, "Shift By");
            AddTextToWindow(objCipher.labelOutput, "Message");

            HGDIOBJ origPen = SelectObject(hdc, GetStockObject(DC_PEN));

            if (origPen != NULL && origPen != HGDI_ERROR) {

                HGDIOBJ newPen;
                newPen = CreatePen(PS_SOLID, 1, CANONN_ORANGE_RGB);

                if (newPen != NULL) {
                    RECT rect;
                    GetWindowRect(objCipher.staticOutput, &rect);
                    AdjustRectToWindow(&rect, &hwnd);

                    SelectObject(hdc, newPen);
                    Rectangle(hdc, rect.left-1, rect.top-1,
                        rect.right+1, rect.bottom+1);
                    SelectObject(hdc, origPen);
                    DeleteObject(newPen);
                }
            }

            AddTextToWindow(objCipher.staticOutput, objCipher.output);
            EndPaint(hwnd, &ps);

        } else if (tabSelected == &tabNotebook) {
            HDC hdc;
            PAINTSTRUCT ps;
            hdc = BeginPaint(hwnd,&ps);
            AddTextToWindow(objNotebook.labelNotes, "Notes");
            EndPaint(hwnd, &ps);

        } else {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
        return (0);

    } else if (uMsg == WM_CTLCOLORSTATIC) {
        HBRUSH hBrush = CreateSolidBrush(CANONN_DARKGRAY_RGB);

        if ((HWND)lParam == objHome.staticTitle) {
            HDC hdcStatic = (HDC)wParam;
            HFONT fontTitle;
            CreateTitleFont(&fontTitle, &hdcStatic);
            SendMessage(objHome.staticTitle, WM_SETFONT, 
                (WPARAM)fontTitle, 0);
            SetTextColor(hdcStatic, CANONN_ORANGE_RGB);
            SetBkColor(hdcStatic, CANONN_DARKGRAY_RGB);

        } else if ((HWND)lParam == objHome.staticDesc0) {
            HDC hdcStatic = (HDC)wParam;
            HFONT fontDefault;
            CreateDefaultFont(&fontDefault, &hdcStatic);
            SendMessage(objHome.staticDesc0, WM_SETFONT, 
                (WPARAM)fontDefault, 0);
            SetTextColor(hdcStatic, CANONN_WHITE_RGB);
            SetBkColor(hdcStatic, CANONN_DARKGRAY_RGB);

        } else if ((HWND)lParam == objHome.staticDesc1) {
            HDC hdcStatic = (HDC)wParam;
            HFONT fontLink;
            CreateLinkFont(&fontLink, &hdcStatic);
            SendMessage(objHome.staticDesc1, WM_SETFONT, 
                (WPARAM)fontLink, 0);
            SetTextColor(hdcStatic, CANONN_ORANGE_RGB);
            SetBkColor(hdcStatic, CANONN_DARKGRAY_RGB);

        } else if ((HWND)lParam == objHome.staticDesc2) {
            HDC hdcStatic = (HDC)wParam;
            HFONT fontLink;
            CreateLinkFont(&fontLink, &hdcStatic);
            SendMessage(objHome.staticDesc2, WM_SETFONT, 
                (WPARAM)fontLink, 0);
            SetTextColor(hdcStatic, CANONN_ORANGE_RGB);
            SetBkColor(hdcStatic, CANONN_DARKGRAY_RGB);

        } else if ((HWND)lParam == objHome.staticDesc3) {
            HDC hdcStatic = (HDC)wParam;
            HFONT fontLink;
            CreateLinkFont(&fontLink, &hdcStatic);
            SendMessage(objHome.staticDesc3, WM_SETFONT, 
                (WPARAM)fontLink, 0);
            SetTextColor(hdcStatic, CANONN_ORANGE_RGB);
            SetBkColor(hdcStatic, CANONN_DARKGRAY_RGB);

        } else if ((HWND)lParam == objHome.staticDesc4) {
            HDC hdcStatic = (HDC)wParam;
            HFONT fontLink;
            CreateLinkFont(&fontLink, &hdcStatic);
            SendMessage(objHome.staticDesc4, WM_SETFONT, 
                (WPARAM)fontLink, 0);
            SetTextColor(hdcStatic, CANONN_ORANGE_RGB);
            SetBkColor(hdcStatic, CANONN_DARKGRAY_RGB);

        } else if ((HWND)lParam == objHome.staticDesc5) {
            HDC hdcStatic = (HDC)wParam;
            HFONT fontLink;
            CreateLinkFont(&fontLink, &hdcStatic);
            SendMessage(objHome.staticDesc5, WM_SETFONT, 
                (WPARAM)fontLink, 0);
            SetTextColor(hdcStatic, CANONN_ORANGE_RGB);
            SetBkColor(hdcStatic, CANONN_DARKGRAY_RGB);

        } else if ((HWND)lParam == objHome.staticContact) {
            HDC hdcStatic = (HDC)wParam;
            HFONT fontTiny;
            CreateTinyFont(&fontTiny, &hdcStatic);
            SendMessage(objHome.staticContact, WM_SETFONT, 
                (WPARAM)fontTiny, 0);
            SetTextColor(hdcStatic, CANONN_WHITE_RGB);
            SetBkColor(hdcStatic, CANONN_DARKGRAY_RGB);

        } else if ((HWND)lParam == objHome.staticDonate) {
            HDC hdcStatic = (HDC)wParam;
            HFONT fontTiny;
            CreateTinyFont(&fontTiny, &hdcStatic);
            SendMessage(objHome.staticDonate, WM_SETFONT, 
                (WPARAM)fontTiny, 0);
            SetTextColor(hdcStatic, CANONN_WHITE_RGB);
            SetBkColor(hdcStatic, CANONN_DARKGRAY_RGB);

        } else if ((HWND)lParam == objHome.staticUpdate) {
            HDC hdcStatic = (HDC)wParam;
            HFONT fontLink;
            CreateLinkFont(&fontLink, &hdcStatic);
            SendMessage(objHome.staticUpdate, WM_SETFONT, 
                (WPARAM)fontLink, 0);
            SetTextColor(hdcStatic, CANONN_ORANGE_RGB);
            SetBkColor(hdcStatic, CANONN_DARKGRAY_RGB);

        } else if ((HWND)lParam == objBearing.labelStarting) {
            HDC hdcStatic = (HDC)wParam;
            HFONT fontHeader;
            CreateHeaderFont(&fontHeader, &hdcStatic);
            SendMessage(objBearing.labelStarting, WM_SETFONT, 
                (WPARAM)fontHeader, 0);
            SetTextColor(hdcStatic, CANONN_ORANGE_RGB);
            SetBkColor(hdcStatic, CANONN_DARKGRAY_RGB);

        } else if ((HWND)lParam == objBearing.labelLat1) {
            HDC hdcStatic = (HDC)wParam;
            HFONT fontLabel;
            CreateLabelFont(&fontLabel, &hdcStatic);
            SendMessage(objBearing.labelLat1, WM_SETFONT, 
                (WPARAM)fontLabel, 0);
            SetTextColor(hdcStatic, CANONN_WHITE_RGB);
            SetBkColor(hdcStatic, CANONN_DARKGRAY_RGB);

        } else if ((HWND)lParam == objBearing.labelLon1) {
            HDC hdcStatic = (HDC)wParam;
            HFONT fontLabel;
            CreateLabelFont(&fontLabel, &hdcStatic);
            SendMessage(objBearing.labelLon1, WM_SETFONT, 
                (WPARAM)fontLabel, 0);
            SetTextColor(hdcStatic, CANONN_WHITE_RGB);
            SetBkColor(hdcStatic, CANONN_DARKGRAY_RGB);

        } else if ((HWND)lParam == objBearing.labelEnding) {
            HDC hdcStatic = (HDC)wParam;
            HFONT fontHeader;
            CreateHeaderFont(&fontHeader, &hdcStatic);
            SendMessage(objBearing.labelEnding, WM_SETFONT, 
                (WPARAM)fontHeader, 0);
            SetTextColor(hdcStatic, CANONN_ORANGE_RGB);
            SetBkColor(hdcStatic, CANONN_DARKGRAY_RGB);

        } else if ((HWND)lParam == objBearing.labelLat2) {
            HDC hdcStatic = (HDC)wParam;
            HFONT fontLabel;
            CreateLabelFont(&fontLabel, &hdcStatic);
            SendMessage(objBearing.labelLat2, WM_SETFONT, 
                (WPARAM)fontLabel, 0);
            SetTextColor(hdcStatic, CANONN_WHITE_RGB);
            SetBkColor(hdcStatic, CANONN_DARKGRAY_RGB);

        } else if ((HWND)lParam == objBearing.labelLon2) {
            HDC hdcStatic = (HDC)wParam;
            HFONT fontLabel;
            CreateLabelFont(&fontLabel, &hdcStatic);
            SendMessage(objBearing.labelLon2, WM_SETFONT, 
                (WPARAM)fontLabel, 0);
            SetTextColor(hdcStatic, CANONN_WHITE_RGB);
            SetBkColor(hdcStatic, CANONN_DARKGRAY_RGB);

        } else if ((HWND)lParam == objBearing.staticBearing) {
            HDC hdcStatic = (HDC)wParam;
            HFONT fontHeader;
            CreateHeaderFont(&fontHeader, &hdcStatic);
            SendMessage(objBearing.staticBearing, WM_SETFONT, 
                (WPARAM)fontHeader, 0);
            SetTextColor(hdcStatic, CANONN_ORANGE_RGB);
            SetBkColor(hdcStatic, CANONN_DARKGRAY_RGB);

        } else if ((HWND)lParam == objNumbers.labelNumBase) {
            HDC hdcStatic = (HDC)wParam;
            HFONT fontHeader;
            CreateHeaderFont(&fontHeader, &hdcStatic);
            SendMessage(objNumbers.labelNumBase, WM_SETFONT, 
                (WPARAM)fontHeader, 0);
            SetTextColor(hdcStatic, CANONN_ORANGE_RGB);
            SetBkColor(hdcStatic, CANONN_DARKGRAY_RGB);

        } else if ((HWND)lParam == objNumbers.labelInput) {
            HDC hdcStatic = (HDC)wParam;
            HFONT fontHeader;
            CreateHeaderFont(&fontHeader, &hdcStatic);
            SendMessage(objNumbers.labelInput, WM_SETFONT, 
                (WPARAM)fontHeader, 0);
            SetTextColor(hdcStatic, CANONN_ORANGE_RGB);
            SetBkColor(hdcStatic, CANONN_DARKGRAY_RGB);

        } else if ((HWND)lParam == objNumbers.labelOutput) {
            HDC hdcStatic = (HDC)wParam;
            HFONT fontHeader;
            CreateHeaderFont(&fontHeader, &hdcStatic);
            SendMessage(objNumbers.labelOutput, WM_SETFONT, 
                (WPARAM)fontHeader, 0);
            SetTextColor(hdcStatic, CANONN_ORANGE_RGB);
            SetBkColor(hdcStatic, CANONN_DARKGRAY_RGB);

        } else if ((HWND)lParam == objNumbers.staticAscii) {
            HDC hdcStatic = (HDC)wParam;
            HFONT fontDefault;
            CreateDefaultFont(&fontDefault, &hdcStatic);
            SendMessage(objNumbers.staticAscii, WM_SETFONT, 
                (WPARAM)fontDefault, 0);
            SetTextColor(hdcStatic, CANONN_WHITE_RGB);
            SetBkColor(hdcStatic, CANONN_DARKGRAY_RGB);

        } else if ((HWND)lParam == objMorse.labelMorse) {
            HDC hdcStatic = (HDC)wParam;
            HFONT fontHeader;
            CreateHeaderFont(&fontHeader, &hdcStatic);
            SendMessage(objMorse.labelMorse, WM_SETFONT, 
                (WPARAM)fontHeader, 0);
            SetTextColor(hdcStatic, CANONN_ORANGE_RGB);
            SetBkColor(hdcStatic, CANONN_DARKGRAY_RGB);

        } else if ((HWND)lParam == objMorse.labelAscii) {
            HDC hdcStatic = (HDC)wParam;
            HFONT fontHeader;
            CreateHeaderFont(&fontHeader, &hdcStatic);
            SendMessage(objMorse.labelAscii, WM_SETFONT, 
                (WPARAM)fontHeader, 0);
            SetTextColor(hdcStatic, CANONN_ORANGE_RGB);
            SetBkColor(hdcStatic, CANONN_DARKGRAY_RGB);


        } else if ((HWND)lParam == objMorse.staticAscii) {
            HDC hdcStatic = (HDC)wParam;
            HFONT fontDefault;
            CreateDefaultFont(&fontDefault, &hdcStatic);
            SendMessage(objMorse.staticAscii, WM_SETFONT, 
                (WPARAM)fontDefault, 0);
            SetTextColor(hdcStatic, CANONN_WHITE_RGB);
            SetBkColor(hdcStatic, CANONN_DARKGRAY_RGB);

        } else if ((HWND)lParam == objCipher.labelKeyword) {
            HDC hdcStatic = (HDC)wParam;
            HFONT fontHeader;
            CreateHeaderFont(&fontHeader, &hdcStatic);
            SendMessage(objCipher.labelKeyword, WM_SETFONT, 
                (WPARAM)fontHeader, 0);
            SetTextColor(hdcStatic, CANONN_ORANGE_RGB);
            SetBkColor(hdcStatic, CANONN_DARKGRAY_RGB);

        } else if ((HWND)lParam == objCipher.labelInput) {
            HDC hdcStatic = (HDC)wParam;
            HFONT fontHeader;
            CreateHeaderFont(&fontHeader, &hdcStatic);
            SendMessage(objCipher.labelInput, WM_SETFONT, 
                (WPARAM)fontHeader, 0);
            SetTextColor(hdcStatic, CANONN_ORANGE_RGB);
            SetBkColor(hdcStatic, CANONN_DARKGRAY_RGB);

        } else if ((HWND)lParam == objCipher.labelShift) {
            HDC hdcStatic = (HDC)wParam;
            HFONT fontHeader;
            CreateHeaderFont(&fontHeader, &hdcStatic);
            SendMessage(objCipher.labelShift, WM_SETFONT, 
                (WPARAM)fontHeader, 0);
            SetTextColor(hdcStatic, CANONN_ORANGE_RGB);
            SetBkColor(hdcStatic, CANONN_DARKGRAY_RGB);

        } else if ((HWND)lParam == objCipher.labelOutput) {
            HDC hdcStatic = (HDC)wParam;
            HFONT fontHeader;
            CreateHeaderFont(&fontHeader, &hdcStatic);
            SendMessage(objCipher.labelOutput, WM_SETFONT, 
                (WPARAM)fontHeader, 0);
            SetTextColor(hdcStatic, CANONN_ORANGE_RGB);
            SetBkColor(hdcStatic, CANONN_DARKGRAY_RGB);

        } else if ((HWND)lParam == objCipher.staticOutput) {
            HDC hdcStatic = (HDC)wParam;
            HFONT fontDefault;
            CreateDefaultFont(&fontDefault, &hdcStatic);
            SendMessage(objCipher.staticOutput, WM_SETFONT, 
                (WPARAM)fontDefault, 0);
            SetTextColor(hdcStatic, CANONN_WHITE_RGB);
            SetBkColor(hdcStatic, CANONN_DARKGRAY_RGB);

        } else if ((HWND)lParam == objNotebook.labelNotes) {
            HDC hdcStatic = (HDC)wParam;
            HFONT fontHeader;
            CreateHeaderFont(&fontHeader, &hdcStatic);
            SendMessage(objNotebook.labelNotes, WM_SETFONT, 
                (WPARAM)fontHeader, 0);
            SetTextColor(hdcStatic, CANONN_ORANGE_RGB);
            SetBkColor(hdcStatic, CANONN_DARKGRAY_RGB);
        }
        return((INT_PTR)hBrush);

    } else if (uMsg == WM_DRAWITEM) {
        if (wParam == IDC_TAB_HOME) {
            DrawSingleTab(&tabHome, lParam);

        } else if (wParam == IDC_TAB_BEARING) {
            DrawSingleTab(&tabBearing, lParam);

        } else if (wParam == IDC_TAB_NUMBERS) {
            DrawSingleTab(&tabNumbers, lParam);

        } else if (wParam == IDC_TAB_MORSE) {
            DrawSingleTab(&tabMorse, lParam);

        } else if (wParam == IDC_TAB_CIPHER) {
            DrawSingleTab(&tabCipher, lParam);

        } else if (wParam == IDC_TAB_NOTEBOOK) {
            DrawSingleTab(&tabNotebook, lParam);
        }
        return (TRUE);

    } else if (uMsg == WM_COMMAND) {
        WORD notification = HIWORD(wParam);

        if (notification == BN_CLICKED) {

            if ((HWND)lParam == objHome.buttonDonate) {
                if (!((int)ShellExecute(NULL, "open", objHome.donateURL, 0, 0, 
                    SW_SHOW) > 32)) {
                    char buffer[MAX_ARRAY_LENGTH];
                    sprintf(buffer, 
                        "The website could not be opened. Please visit %s if you wish to donate.", 
                        objHome.donateURL);
                    MessageBox(hwnd, buffer, "Could not open browser.", 
                        MB_OK);
                }

            } else if ((HWND)lParam == objBearing.buttonCalc &&
                GetWindowTextLength(objBearing.editLat1) > 0 &&
                GetWindowTextLength(objBearing.editLon1) > 0 &&
                GetWindowTextLength(objBearing.editLat2) > 0 &&
                GetWindowTextLength(objBearing.editLon2) > 0) {

                objBearing.dataStored = TRUE;

                char input[MAX_ARRAY_LENGTH];
                GetWindowText(objBearing.editLat1, input, MAX_ARRAY_LENGTH);

                try {
                    objBearing.lat1 = std::stod(input, NULL);
                    if (objBearing.lat1 > 90 || objBearing.lat1 <= -90) {
                        throw 20;
                    }

                } catch (std::invalid_argument &ia) {
                    ia.what();
                    objBearing.dataStored = FALSE;
                    MessageBox(hwnd, "Latitude must be a number.", 
                        "Invalid Starting Latitude", MB_OK);

                } catch (...) {
                    objBearing.lat1 = 0;
                    objBearing.dataStored = FALSE;
                    MessageBox(hwnd, 
                        "Latitude must be greater than -90 and less than or equal to 90.", 
                        "Invalid Starting Latitude", MB_OK);
                }

                GetWindowText(objBearing.editLon1, input, 
                    MAX_ARRAY_LENGTH);

                try {
                    objBearing.lon1 = std::stod(input, NULL);
                    if (objBearing.lon1 > 180 || objBearing.lon1 <= -180) {
                        throw 20;
                    }

                } catch (std::invalid_argument &ia) {
                    ia.what();
                    objBearing.dataStored = FALSE;
                    MessageBox(hwnd, "Longitude must be a number.", 
                        "Invalid Starting Longitude", MB_OK);

                } catch (...) {
                    objBearing.lon1 = 0;
                    objBearing.dataStored = FALSE;
                    MessageBox(hwnd, 
                        "Longitude must be greater than -180 and less than or equal to 180.", 
                        "Invalid Starting Longitude", MB_OK);
                }

                GetWindowText(objBearing.editLat2, input, 
                    MAX_ARRAY_LENGTH);

                try {
                    objBearing.lat2 = std::stod(input, NULL);
                    if (objBearing.lat2 > 90 || objBearing.lat2 <= -90) {
                        throw 20;
                    }

                } catch (std::invalid_argument &ia) {
                    ia.what();
                    objBearing.dataStored = FALSE;
                    MessageBox(hwnd, "Latitude must be a number.", 
                        "Invalid Destination Latitude", MB_OK);

                } catch (...) {
                    objBearing.lat2 = 0;
                    objBearing.dataStored = FALSE;
                    MessageBox(hwnd, 
                        "Latitude must be greater than -90 and less than or equal to 90.", 
                        "Invalid Destination Latitude", MB_OK);
                }

                GetWindowText(objBearing.editLon2, input, 
                    MAX_ARRAY_LENGTH);

                try {
                    objBearing.lon2 = std::stod(input, NULL);
                    if (objBearing.lon2 > 180 || objBearing.lon2 <= -180) {
                        throw 20;
                    }

                } catch (std::invalid_argument &ia) {
                    ia.what();
                    objBearing.dataStored = FALSE;
                    MessageBox(hwnd, "Longitude must be a number.", 
                        "Invalid Destination Longitude", MB_OK);

                } catch (...) {
                    objBearing.lon2 = 0;
                    objBearing.dataStored = FALSE;
                    MessageBox(hwnd, 
                        "Longitude must be greater than -180 and less than or equal to 180.", 
                        "Invalid Destination Longitude", MB_OK);
                }

                if (objBearing.dataStored == TRUE) {
                    objBearing.bearing = CalculateBearing(objBearing.lat1, 
                        objBearing.lon1, objBearing.lat2, objBearing.lon2);
                    InvalidateRect(hwnd, NULL, FALSE);
                }

            } else if ((HWND)lParam == objNumbers.buttonConvert) {

                objNumbers.inputLength = GetWindowTextLength(objNumbers.editNumber);
                if (objNumbers.inputLength > 0) {

                    if (objNumbers.inputLength > MAX_ARRAY_LENGTH-1) {
                        objNumbers.inputLength = MAX_ARRAY_LENGTH-1;
                    }
                    objNumbers.inputLength++;

                    GetWindowText(objNumbers.editNumber, 
                        objNumbers.userInput, objNumbers.inputLength);
                    GetWindowText(objNumbers.editNumber, 
                        objNumbers.copyUserInput, objNumbers.inputLength);
                    objNumbers.userInput[objNumbers.inputLength] = '\0';
                    objNumbers.copyUserInput[objNumbers.inputLength] = '\0';

                    if (objNumbers.baseSelected == 0) {
                        ConvertBinaryToAscii(objNumbers.asciiOutput, 
                            objNumbers.copyUserInput);

                    } else if (objNumbers.baseSelected == 1) {
                        ConvertOctToAscii(objNumbers.asciiOutput, 
                            objNumbers.copyUserInput);

                    } else if (objNumbers.baseSelected == 2) {
                        ConvertDecimalToAscii(objNumbers.asciiOutput, 
                            objNumbers.copyUserInput);

                    } else if (objNumbers.baseSelected == 3) {
                        ConvertHexToAscii(objNumbers.asciiOutput, 
                            objNumbers.copyUserInput);

                    } else if (objNumbers.baseSelected == 4) {
                        SwapNumbersToAlphabet(objNumbers.asciiOutput, 
                            objNumbers.copyUserInput);
                    }

                    objNumbers.dataStored = TRUE;
                    InvalidateRect(hwnd, NULL, FALSE);
                }

            } else if ((HWND)lParam == objMorse.buttonConvert) {

                objMorse.inputLength = GetWindowTextLength(objMorse.editMorse);
                if (objMorse.inputLength > 0) {

                    if (objMorse.inputLength > MAX_ARRAY_LENGTH-1) {
                        objMorse.inputLength = MAX_ARRAY_LENGTH-1;
                    }
                    objMorse.inputLength++;

                    GetWindowText(objMorse.editMorse, 
                        objMorse.userInput, objMorse.inputLength);
                    GetWindowText(objMorse.editMorse, 
                        objMorse.copyUserInput, objMorse.inputLength);
                    objMorse.userInput[objMorse.inputLength] = '\0';
                    objMorse.copyUserInput[objMorse.inputLength] = '\0';

                    ConvertMorseToAscii(objMorse.asciiOutput,
                        objMorse.copyUserInput);

                    objMorse.dataStored = TRUE;
                    InvalidateRect(hwnd, NULL, FALSE);
                }

            } else if ((HWND)lParam == objCipher.buttonEncrypt) {

                if (GetWindowTextLength(objCipher.editInput) > 0) {
                    SetKey(&objCipher);
                    SetNewAlphabet(&objCipher);
                    SetInputText(&objCipher);
                    EncryptCipherText(objCipher.output, objCipher.input, 
                        objCipher.inputTextLength, objCipher.newAlphabet);
                    objCipher.dataStored = TRUE;
                    InvalidateRect(hwnd, NULL, FALSE);
                }

            } else if ((HWND)lParam == objCipher.buttonDecrypt) {

                if (GetWindowTextLength(objCipher.editInput) > 0) {
                    SetKey(&objCipher);
                    SetNewAlphabet(&objCipher);
                    SetInputText(&objCipher);
                    DecryptCipherText(objCipher.output, objCipher.input, 
                        objCipher.inputTextLength, objCipher.newAlphabet);
                    objCipher.dataStored = TRUE;
                    InvalidateRect(hwnd, NULL, FALSE);
                }

            } else if ((HWND)lParam == objNotebook.buttonNewFile) {
                objNotebook.nameLength = 
                    GetWindowTextLength(objNotebook.editNewFile);

                if (objNotebook.nameLength > 0) {

                    if (objNotebook.nameLength > MAX_ARRAY_LENGTH-1) {
                        objNotebook.nameLength = MAX_ARRAY_LENGTH-1;
                    }
                    objNotebook.nameLength++;

                    GetWindowText(objNotebook.editNewFile, 
                        objNotebook.currentFile, objNotebook.nameLength);
                    objNotebook.currentFile[objNotebook.nameLength-1] = '\0';

                    ChangeFileLocation(&objNotebook, objNotebook.currentFile);

                    objNotebook.fileHandle = 
                        CreateFile(objNotebook.fileLocation, 
                            GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL,
                            CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

                    if (objNotebook.fileHandle==INVALID_HANDLE_VALUE) {
                        if (GetLastError() == ERROR_FILE_EXISTS) {
                            MessageBox(hwnd, 
                                "A file with this name already exists.",
                                "Cannot Create New File", MB_OK);
                        } else {
                            MessageBox(hwnd, 
                                "File could not be created.",
                                "Unknown Error", MB_OK);
                        }

                    } else {
                        objNotebook.textLength = 
                            GetWindowTextLength(objNotebook.editNotes);

                        if (objNotebook.textLength > MAX_ARRAY_LENGTH*4-1) {
                            objNotebook.textLength = MAX_ARRAY_LENGTH*4-1;
                        }
                        objNotebook.textLength++;
                        GetWindowText(objNotebook.editNotes, 
                            objNotebook.fileContents, objNotebook.textLength);
                        objNotebook.fileContents[objNotebook.textLength-1] = '\0';

                        if (!WriteFile(objNotebook.fileHandle, 
                            objNotebook.fileContents, 
                            objNotebook.textLength, NULL, NULL)) {
                                MessageBox(hwnd, 
                                    "Writing to the file has failed.",
                                    "Unknown Error", MB_OK);
                        }

                        CloseHandle(objNotebook.fileHandle);

                        ChangeFileLocation(&objNotebook, 
                            objNotebook.fileListName);

                        objNotebook.fileHandle = 
                            CreateFile(objNotebook.fileLocation, 
                                GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, 
                                NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
                        if (objNotebook.fileHandle != INVALID_HANDLE_VALUE) {
                            SetFilePointer(objNotebook.fileHandle, 
                                NULL, NULL, FILE_END);
                            WriteFile(objNotebook.fileHandle, 
                                objNotebook.currentFile, 
                                objNotebook.nameLength-1, NULL, NULL);
                            WriteFile(objNotebook.fileHandle, "\n",
                                sizeof(char), NULL, NULL);
                            CloseHandle(objNotebook.fileHandle);
                            SendMessage(objNotebook.comboFiles, CB_ADDSTRING, 
                                0, (LPARAM)objNotebook.currentFile);
                            objNotebook.baseSelected = 
                                (int)SendMessage(objNotebook.comboFiles, 
                                    CB_SELECTSTRING, (WPARAM)-1, 
                                    (LPARAM)objNotebook.currentFile);
                            SendMessage(objNotebook.comboFiles, CB_SETCURSEL, 
                                (WPARAM)objNotebook.baseSelected, 0);
                            InvalidateRect(hwnd, NULL, FALSE);
                        } else {
                            MessageBox(hwnd, "Your file has been saved, but an error occurred when adding the file to the list here.",
                                "Unknown Error", MB_OK);
                        } 

                        ChangeFileLocation(&objNotebook, 
                            objNotebook.currentFile);

                    }

                } else {
                    MessageBox(hwnd, "You must enter a file name.",
                        "No File Name Given", MB_OK);
                }

            } else if ((HWND)lParam == objNotebook.buttonDeleteFile) {
                char buffer[MAX_ARRAY_LENGTH*2];
                sprintf(buffer, "Are you sure you want to delete %s?", 
                    objNotebook.currentFile);
                if (MessageBox(hwnd, buffer,
                    "About to Delete File", MB_YESNO) == IDYES) {
                    ChangeFileLocation(&objNotebook, objNotebook.fileListName);
                    objNotebook.fileHandle = CreateFile(objNotebook.fileLocation, 
                            GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, 
                            NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

                    int fll = 0;
                    if (objNotebook.fileHandle != INVALID_HANDLE_VALUE) {
                        DWORD readEOF = 1;
                        while (readEOF != 0 && fll < MAX_ARRAY_LENGTH*4-1) {
                            ReadFile(objNotebook.fileHandle, 
                                &objNotebook.fileContents[fll], 1, &readEOF, NULL);
                            fll++;
                        }
                        fll--; // to backtrack from the EOF character

                        CloseHandle(objNotebook.fileHandle);
                    } else {
                        strcpy(objNotebook.fileContents, "");
                    }

                    ChangeFileLocation(&objNotebook, objNotebook.tmpFileName);
                    objNotebook.fileHandle = CreateFile(objNotebook.fileLocation,
                            GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, 
                            NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
                    
                    if (objNotebook.fileHandle != INVALID_HANDLE_VALUE) {
                        char *delname = strstr(objNotebook.fileContents, 
                            objNotebook.currentFile);

                        if (delname != NULL) {
                            int j = 0;
                            while (delname != &objNotebook.fileContents[j]) {
                                WriteFile(objNotebook.fileHandle, 
                                    &objNotebook.fileContents[j], 1, NULL, NULL);
                                j++;
                            }

                            while (objNotebook.fileContents[j] != '\n') {
                                j++;
                            }
                            j++; // pass the \n character

                            while (j < fll) {
                                WriteFile(objNotebook.fileHandle, 
                                    &objNotebook.fileContents[j], 1, NULL, NULL);
                                j++;
                            }
                        }

                        CloseHandle(objNotebook.fileHandle);
                        MoveFileEx(objNotebook.tmpFileLocation, 
                            objNotebook.fileListLocation, 
                            MOVEFILE_REPLACE_EXISTING);
                    }

                    SendMessage(objNotebook.comboFiles, (UINT)CB_DELETESTRING, 
                        (WPARAM)objNotebook.baseSelected, 0);
                    ChangeFileLocation(&objNotebook, objNotebook.currentFile);
                    DeleteFile(objNotebook.fileLocation);

                    objNotebook.baseSelected = 0;
                    SendMessage(objNotebook.comboFiles, CB_SETCURSEL,
                        (WPARAM)objNotebook.baseSelected, 0);
                    WPARAM send = MAKEWPARAM(IDC_COMBO_FILELIST, CBN_SELENDOK);
                    SendMessage(hwnd, WM_COMMAND, send, 
                        (LPARAM)objNotebook.comboFiles);
                }

            } else if ((HWND)lParam == tabHome && 
                        tabSelected != &tabHome) {
                DestroyWindow();
                tabSelected = &tabHome;
                InvalidateRect(hwnd, NULL, TRUE);
                PaintHomeWindow(&hwnd, &objHome);

            } else if ((HWND)lParam == tabBearing && 
                        tabSelected != &tabBearing) {
                DestroyWindow();
                tabSelected = &tabBearing;
                InvalidateRect(hwnd, NULL, TRUE);
                PaintBearingWindow(&hwnd, &objBearing);

            } else if ((HWND)lParam == tabNumbers && 
                        tabSelected != &tabNumbers) {
                DestroyWindow();
                tabSelected = &tabNumbers;
                InvalidateRect(hwnd, NULL, TRUE);
                PaintNumbersWindow(&hwnd, &objNumbers);

            } else if ((HWND)lParam == tabMorse && 
                        tabSelected != &tabMorse) {
                DestroyWindow();
                tabSelected = &tabMorse;
                InvalidateRect(hwnd, NULL, TRUE);
                PaintMorseWindow(&hwnd, &objMorse);

            } else if ((HWND)lParam == tabCipher && 
                        tabSelected != &tabCipher) {
                DestroyWindow();
                tabSelected = &tabCipher;
                InvalidateRect(hwnd, NULL, TRUE);
                PaintCipherWindow(&hwnd, &objCipher);

            } else if ((HWND)lParam == tabNotebook && 
                        tabSelected != &tabNotebook) {
                DestroyWindow();
                tabSelected = &tabNotebook;
                InvalidateRect(hwnd, NULL, TRUE);
                PaintNotebookWindow(&hwnd, &objNotebook);

            } else if ((HWND)lParam == objHome.staticDesc1) {
                if (!((int)ShellExecute(NULL, "open", objHome.link1, 0, 0, 
                    SW_SHOW) > 32)) {
                    char buffer[MAX_ARRAY_LENGTH];
                    sprintf(buffer, 
                        "The website (%s) could not be opened.", 
                        objHome.link1);
                    MessageBox(hwnd, buffer, "Could not open browser.", 
                        MB_OK);
                }
            } else if ((HWND)lParam == objHome.staticDesc2) {
                if (!((int)ShellExecute(NULL, "open", objHome.link2, 0, 0, 
                    SW_SHOW) > 32)) {
                    char buffer[MAX_ARRAY_LENGTH];
                    sprintf(buffer, 
                        "The website (%s) could not be opened.", 
                        objHome.link2);
                    MessageBox(hwnd, buffer, "Could not open browser.", 
                        MB_OK);
                }
            } else if ((HWND)lParam == objHome.staticDesc3) {
                if (!((int)ShellExecute(NULL, "open", objHome.link3, 0, 0, 
                    SW_SHOW) > 32)) {
                    char buffer[MAX_ARRAY_LENGTH];
                    sprintf(buffer, 
                        "The website (%s) could not be opened.", 
                        objHome.link3);
                    MessageBox(hwnd, buffer, "Could not open browser.", 
                        MB_OK);
                }
            } else if ((HWND)lParam == objHome.staticDesc4) {
                if (!((int)ShellExecute(NULL, "open", objHome.link4, 0, 0, 
                    SW_SHOW) > 32)) {
                    char buffer[MAX_ARRAY_LENGTH];
                    sprintf(buffer, 
                        "The website (%s) could not be opened.", 
                        objHome.link4);
                    MessageBox(hwnd, buffer, "Could not open browser.", 
                        MB_OK);
                }
            } else if ((HWND)lParam == objHome.staticDesc5) {
                if (!((int)ShellExecute(NULL, "open", objHome.link5, 0, 0, 
                    SW_SHOW) > 32)) {
                    char buffer[MAX_ARRAY_LENGTH];
                    sprintf(buffer, 
                        "The website (%s) could not be opened.", 
                        objHome.link5);
                    MessageBox(hwnd, buffer, "Could not open browser.", 
                        MB_OK);
                }
            } else if ((HWND)lParam == objHome.staticUpdate) {
                if (!((int)ShellExecute(NULL, "open", objHome.updateLink, 0, 0, 
                    SW_SHOW) > 32)) {
                    char buffer[MAX_ARRAY_LENGTH];
                    sprintf(buffer, 
                        "The website (%s) could not be opened.", 
                        objHome.updateLink);
                    MessageBox(hwnd, buffer, "Could not open browser.", 
                        MB_OK);
                }
            }

            return (0);
            
        } else if (notification == CBN_SELENDOK) {

            if ((HWND)lParam == objNumbers.comboNumBase) {
                objNumbers.baseSelected = 
                    (int)SendMessage(objNumbers.comboNumBase, 
                            CB_GETCURSEL, 0, 0);

            } else if ((HWND)lParam == objCipher.comboShift) {
                objCipher.baseSelected = 
                    (int)SendMessage(objCipher.comboShift, 
                            CB_GETCURSEL, 0, 0);

            } else if ((HWND)lParam == objNotebook.comboFiles) {
                objNotebook.baseSelected = 
                    (int)SendMessage(objNotebook.comboFiles, 
                            CB_GETCURSEL, 0, 0);

                if (objNotebook.baseSelected == CB_ERR) { // no more files
                    strcpy(objNotebook.currentFile, "");
                    strcpy(objNotebook.fileContents, "");
                    objNotebook.baseSelected = 0;

                } else {
                    SendMessage(objNotebook.comboFiles, CB_GETLBTEXT,
                        (WPARAM)objNotebook.baseSelected,
                        (LPARAM)objNotebook.currentFile);

                    ChangeFileLocation(&objNotebook, objNotebook.currentFile);
                    objNotebook.fileHandle = 
                        CreateFile(objNotebook.fileLocation, 
                        GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, 
                        NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

                    if (objNotebook.fileHandle != INVALID_HANDLE_VALUE) {
                        strcpy(objNotebook.fileContents, "");
                        DWORD readEOF = 1;
                        int i = 0;
                        while (readEOF != 0 && i < MAX_ARRAY_LENGTH*4-1) {
                            ReadFile(objNotebook.fileHandle, 
                                &objNotebook.fileContents[i], 
                                1, &readEOF, NULL);
                            i++;
                        }
                        objNotebook.fileContents[i-1] = '\0';
                        CloseHandle(objNotebook.fileHandle);
                    } else {
                        strcpy(objNotebook.fileContents, "");
                    }
                }
                SetWindowText(objNotebook.editNotes, 
                    objNotebook.fileContents);
            }

            return (0);
        } else {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }

    } else if (uMsg == WM_DESTROY) {

        if (tabSelected == &tabNotebook) {
            DestroyNotebookWindow(&objNotebook);
        }
        PostQuitMessage(0);
        return (0);
        
    } else {
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

LRESULT CALLBACK MultiLineWindowProc(HWND hwnd, 
                                     UINT uMsg, 
                                     WPARAM wParam, 
                                     LPARAM lParam,
                                     UINT_PTR uIdSubclass,
                                     DWORD_PTR dwRefData) {
    LRESULT Result = DefSubclassProc(hwnd, uMsg, wParam, lParam);

    if (uMsg == WM_GETDLGCODE) {
        if (tabDown) {
        	Result &= ~DLGC_WANTALLKEYS;
        }
    }

    return (Result);
}

int CALLBACK WinMain(HINSTANCE hInst,
    				 HINSTANCE hPrevInst,
    				 LPSTR lpCmdLine,
    				 int nCmdShow) {

    INITCOMMONCONTROLSEX icc;
    icc.dwSize = sizeof(icc);
    icc.dwICC = ICC_STANDARD_CLASSES | ICC_USEREX_CLASSES;

    InitCommonControlsEx(&icc);

    WNDCLASS wc = {};

    wc.style = 0;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;
    wc.hIcon = (HICON)LoadImage(NULL, "./images/toolkitIcon.ico", IMAGE_ICON, 0, 0, 
        LR_DEFAULTSIZE | LR_LOADFROMFILE);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(CANONN_DARKGRAY_RGB);
    wc.lpszMenuName = 0;
    wc.lpszClassName = "Window Class";

    RegisterClass(&wc);

    RECT rect;
    SetRect(&rect, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT);
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

    hMain = CreateWindowEx(0, wc.lpszClassName, "Canonn Toolkit  v1.01", 
        WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 
        rect.right-rect.left, rect.bottom-rect.top, NULL, NULL, hInst, NULL);

    if (hMain == NULL) {
    	return (1);
    }

    ShowWindow(hMain, nCmdShow);
    UpdateWindow(hMain);

    MSG msg;
    // while (GetMessage(&msg, 0, 0, 0)) {
    // 	if (msg.message == WM_KEYDOWN) {
    // 		if (msg.wParam == VK_SHIFT) {
    // 			shiftDown = TRUE;
    // 		} else if (msg.wParam == VK_TAB) {
    // 		} else {
	   //          TranslateMessage(&msg);
	   //          DispatchMessage(&msg);    			
    // 		}
    // 	} else if (msg.message == WM_KEYUP) {
    // 		if (msg.wParam == VK_SHIFT) {
    // 			shiftDown = FALSE;
    // 		} else if (msg.wParam == VK_TAB) {
    // 			HWND hFocus = GetFocus();
    // 			if (hFocus) {
    // 				HWND hNext = GetNextDlgTabItem(GetParent((HWND)hFocus), (HWND)hFocus, shiftDown);
			 //    	SetFocus(hNext);
    // 			}
    // 		} else {
	   //          TranslateMessage(&msg);
	   //          DispatchMessage(&msg);
    //     	}
    // 	} else {
    //         TranslateMessage(&msg);
    //         DispatchMessage(&msg);
    //     }
    // }


    while (GetMessage(&msg, 0, 0, 0)) {
    	if (msg.wParam == VK_TAB) {
    		if (msg.message == WM_KEYDOWN) {
    			tabDown = TRUE;
    		} else if (msg.message == WM_KEYUP) {
    			tabDown = FALSE;
    		}
    	}
    	if (!IsDialogMessage(hMain, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return(0);

}