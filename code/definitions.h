#ifndef DEFINITIONS
#define DEFINITIONS

#include <windows.h>

#define Donate 1

#define IDC_TAB_HOME 101
#define IDC_TAB_BEARING 102
#define IDC_TAB_NUMBERS 103
#define IDC_TAB_MORSE 104
#define IDC_TAB_CIPHER 105
#define IDC_TAB_NOTEBOOK 106
#define IDC_EDIT_LAT1 201
#define IDC_EDIT_LAT2 202
#define IDC_EDIT_LON1 203
#define IDC_EDIT_LON2 204
#define IDC_EDIT_NUMBER 205
#define IDC_EDIT_KEY 206
#define IDC_EDIT_MORSEINPUT 207
#define IDC_EDIT_CIPHERTEXT 208
#define IDC_EDIT_NOTES 209
#define IDC_EDIT_NEWFILE 210
#define IDC_STATIC_TITLE 301
#define IDC_STATIC_DESC0 302
#define IDC_STATIC_DESC1 303
#define IDC_STATIC_DESC2 304
#define IDC_STATIC_DESC3 305
#define IDC_STATIC_DESC4 306
#define IDC_STATIC_DESC5 307
#define IDC_STATIC_CONTACT 308
#define IDC_STATIC_DONATE 309
#define IDC_STATIC_LOGO 310
#define IDC_STATIC_BEARING 311
#define IDC_STATIC_NUMBER 312
#define IDC_STATIC_MORSE 313
#define IDC_STATIC_CIPHEROUTPUT 314
#define IDC_BUTTON_DONATE 401
#define IDC_BUTTON_CALCBEARING 402
#define IDC_BUTTON_NUMTOASCII 403
#define IDC_BUTTON_MORSETOASCII 404
#define IDC_BUTTON_DECRYPT 405
#define IDC_BUTTON_NEWFILE 406
#define IDC_BUTTON_DELETEFILE 407
#define IDC_COMBO_BASELIST 501
#define IDC_COMBO_SHIFTLIST 502
#define IDC_COMBO_FILELIST 503
#define IDC_LABEL_STARTING 601
#define IDC_LABEL_LAT1 602
#define IDC_LABEL_LON1 603
#define IDC_LABEL_ENDING 604
#define IDC_LABEL_LAT2 605
#define IDC_LABEL_LON2 606
#define IDC_LABEL_NUMBASE 607
#define IDC_LABEL_NUMBERSINPUT 608
#define IDC_LABEL_NUMBERSOUTPUT 609
#define IDC_LABEL_MORSEINPUT 610
#define IDC_LABEL_MORSEOUTPUT 611
#define IDC_LABEL_KEYWORD 612
#define IDC_LABEL_INPUTTEXT 613
#define IDC_LABEL_CIPHEROUTPUT 614
#define IDC_LABEL_SHIFT 615
#define IDC_LABEL_NOTES 616


#define XDIVIDER 160
#define YSTART 20
#define XSTART XDIVIDER+YSTART
#define TAB_HEIGHT 50
#define CLIENT_HEIGHT TAB_HEIGHT*6
#define CLIENT_WIDTH 650
#define YEND CLIENT_HEIGHT-YSTART
#define XEND CLIENT_WIDTH-YSTART
#define TEXTBOXWIDTH 210
#define TEXTBOXHEIGHT 120
#define BUTTONHEIGHT 25
#define EDITHEIGHT 20
#define COMBOHEIGHT 130


#define MAX_ARRAY_LENGTH 1024
#define ALPHABET_LENGTH 26
#define ASCII_OFFSET 65


#define TAB_HOME_NAME "Home"
#define TAB_BEARING_NAME "Bearing Calculator"
#define TAB_NUMBERS_NAME "Numbers to ASCII"
#define TAB_MORSE_NAME "Morse to ASCII"
#define TAB_CIPHER_NAME "Keyword Cipher"
#define TAB_NOTEBOOK_NAME "Notebook"


#define FONT_FACE "Calibri"
#define FONT_SIZE_TAB 14
#define FONT_SIZE_DEFAULT 12
#define FONT_SIZE_TITLE 17
#define FONT_SIZE_HEADER 13
#define FONT_SIZE_LABEL FONT_SIZE_DEFAULT
#define FONT_SIZE_TINY FONT_SIZE_DEFAULT-2


#define internal static
#define local_persist static
#define global_variable static


#define CANONN_ORANGE_HEX 0XEE7A04
#define CANONN_DARKORANGE_HEX 0XB77D42
#define CANONN_DARKGRAY_HEX 0X212121
#define CANONN_LIGHTGRAY_HEX 0X2D2D2D


global_variable COLORREF CANONN_ORANGE_RGB = RGB(238,122,4);
global_variable COLORREF CANONN_DARKORANGE_RGB = RGB(183, 125, 66);
global_variable COLORREF CANONN_DARKGRAY_RGB = RGB(12, 12, 12);
global_variable COLORREF CANONN_LIGHTGRAY_RGB = RGB(45, 45, 45);
global_variable COLORREF CANONN_WHITE_RGB = RGB(255, 255, 255);


void CreateTabFont(HFONT *Result, HDC *hdc) {
    long fontSize = -MulDiv(FONT_SIZE_TAB, 
                            GetDeviceCaps(*hdc, LOGPIXELSY), 72);

    *Result = CreateFont(fontSize, 0, 0, 0, FW_BOLD, 
        0, 0, 0, 0, 0, 0, 0, 0, FONT_FACE);
}


void CreateDefaultFont(HFONT *Result, HDC *hdc) {
    long fontSize = -MulDiv(FONT_SIZE_DEFAULT, 
                            GetDeviceCaps(*hdc, LOGPIXELSY), 72);

    *Result = CreateFont(fontSize, 0, 0, 0, FW_NORMAL, 
        0, 0, 0, 0, 0, 0, 0, 0, FONT_FACE);
}


void CreateTitleFont(HFONT *Result, HDC *hdc) {
    long fontSize = -MulDiv(FONT_SIZE_TITLE, 
                            GetDeviceCaps(*hdc, LOGPIXELSY), 72);

    *Result = CreateFont(fontSize, 0, 0, 0, FW_SEMIBOLD, 
        0, 0, 0, 0, 0, 0, 0, 0, FONT_FACE);
}


void CreateHeaderFont(HFONT *Result, HDC *hdc) {
    long fontSize = -MulDiv(FONT_SIZE_HEADER, 
                            GetDeviceCaps(*hdc, LOGPIXELSY), 72);

    *Result = CreateFont(fontSize, 0, 0, 0, FW_SEMIBOLD, 
        0, 0, 0, 0, 0, 0, 0, 0, FONT_FACE);
}


void CreateLabelFont(HFONT *Result, HDC *hdc) {
    long fontSize = -MulDiv(FONT_SIZE_LABEL, 
                            GetDeviceCaps(*hdc, LOGPIXELSY), 72);

    *Result = CreateFont(fontSize, 0, 0, 0, FW_NORMAL, 
        TRUE, 0, 0, 0, 0, 0, 0, 0, FONT_FACE);
}


void CreateLinkFont(HFONT *Result, HDC *hdc) {
    long fontSize = -MulDiv(FONT_SIZE_DEFAULT, 
                            GetDeviceCaps(*hdc, LOGPIXELSY), 72);

    *Result = CreateFont(fontSize, 0, 0, 0, FW_NORMAL, 
        0, TRUE, 0, 0, 0, 0, 0, 0, FONT_FACE);
}


void CreateTinyFont(HFONT *Result, HDC *hdc) {
    long fontSize = -MulDiv(FONT_SIZE_TINY, 
                            GetDeviceCaps(*hdc, LOGPIXELSY), 72);

    *Result = CreateFont(fontSize, 0, 0, 0, FW_NORMAL, 
        0, 0, 0, 0, 0, 0, 0, 0, FONT_FACE);
}


void AdjustRectToWindow(RECT *rect, HWND *hwnd) {
	POINT tl;
	tl.x = rect->left;
	tl.y = rect->top;

	POINT br;
	br.x = rect->right;
	br.y = rect->bottom;

	ScreenToClient(*hwnd, &tl);
	ScreenToClient(*hwnd, &br);

	rect->left = tl.x;
	rect->top = tl.y;
	rect->right = br.x;
	rect->bottom = br.y;
}

void AddTextToWindow(HWND hwnd, char *text, int length = MAX_ARRAY_LENGTH) {
    char *buffer = new char[length];
    if (sprintf(buffer, "%s", text) > 0) {
        SetWindowText(hwnd, buffer);
    }
    delete[] buffer;
}


#endif