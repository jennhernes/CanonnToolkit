#include <windows.h>
#include "definitions.h"
#include "toolkit_notebook.h"


LRESULT CALLBACK MultiLineWindowProc(HWND hwnd, UINT uMsg, 
                                     WPARAM wParam, LPARAM lParam,
                                     UINT_PTR uIdSubclass, DWORD_PTR dwRefData);


void ChangeFileLocation(Notebook *objNotebook, char *text) {
    strcpy(objNotebook->fileLocation, objNotebook->fileDirectory);
    strcat(objNotebook->fileLocation, text);
}


LRESULT PaintNotebookWindow(HWND *hPWnd, Notebook *objNotebook) {
    LRESULT Result = 0;
    DWORD baseStyle = WS_CHILD | WS_VISIBLE;

    RECT rect;
    SetRect(&rect, XDIVIDER, 0, CLIENT_WIDTH, CLIENT_HEIGHT);
    HDC hdc = GetDC(*hPWnd);
    FillRect(hdc, &rect, CreateSolidBrush(CANONN_DARKGRAY_RGB));

    HFONT fontDefault;

    RECT topRect;
    RECT leftRect;

    objNotebook->comboFiles = CreateWindow(WC_COMBOBOX, "", 
        baseStyle | WS_TABSTOP | WS_VSCROLL | 
            CBS_DROPDOWNLIST | CBS_HASSTRINGS | CBS_SORT,
        XSTART, YSTART, 170, COMBOHEIGHT, 
        *hPWnd, (HMENU)IDC_COMBO_FILELIST, GetModuleHandle(NULL), NULL);
    if (objNotebook->comboFiles == NULL) {
        Result = -1;
        return(Result);
    } else {
        SendMessage(objNotebook->comboFiles, CB_SETMINVISIBLE, (WPARAM)5, 0);
        hdc = GetDC(objNotebook->comboFiles);
        CreateDefaultFont(&fontDefault, &hdc);
        SendMessage(objNotebook->comboFiles, WM_SETFONT, 
            (WPARAM)fontDefault, TRUE);

        objNotebook->fileHandle = CreateFile(objNotebook->fileListLocation, 
            GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS,
            FILE_ATTRIBUTE_NORMAL, NULL);
        if (objNotebook->fileHandle != INVALID_HANDLE_VALUE) {
            DWORD readEOF = 1;
            int i = 0;
            while (readEOF != 0 && i < MAX_ARRAY_LENGTH*4-1) {
                ReadFile(objNotebook->fileHandle, &objNotebook->fileContents[i], 
                    1, &readEOF, NULL);
                i++;
            }
            objNotebook->fileContents[i-1] = '\0';
            CloseHandle(objNotebook->fileHandle);
        } else {
            strcpy(objNotebook->fileContents, "");
        }

        if (strcmp(objNotebook->fileContents, "") != 0) {
            char *token = strtok(objNotebook->fileContents, "\n");
            while (token != NULL) {
                SendMessage(objNotebook->comboFiles, (UINT)CB_ADDSTRING, 
                    (WPARAM)0, (LPARAM)token);
                token = strtok(NULL, "\n");
            }
        }
        SendMessage(objNotebook->comboFiles, CB_SETCURSEL, 
            (WPARAM)objNotebook->baseSelected, (LPARAM)0);
        SendMessage(objNotebook->comboFiles, CB_GETLBTEXT, 
            objNotebook->baseSelected, (LPARAM)objNotebook->currentFile);
    }

    GetWindowRect(objNotebook->comboFiles, &rect);
    AdjustRectToWindow(&rect, hPWnd);

    GetWindowRect(objNotebook->comboFiles, &leftRect);
    AdjustRectToWindow(&leftRect, hPWnd);

    int height = leftRect.bottom-leftRect.top;
    int vspacing = (height-BUTTONHEIGHT)/2;
    objNotebook->buttonDeleteFile = CreateWindow("BUTTON", "OK", 
        baseStyle | WS_TABSTOP | BS_PUSHBUTTON,
        leftRect.right+30, leftRect.top+vspacing, 150, BUTTONHEIGHT,
        *hPWnd, (HMENU)IDC_BUTTON_DELETEFILE, GetModuleHandle(NULL), NULL);
    if (objNotebook->buttonDeleteFile == NULL) {
        Result = -1;
        return(Result);
    } else {
        hdc = GetDC(objNotebook->buttonDeleteFile);
        CreateDefaultFont(&fontDefault, &hdc);
        SendMessage(objNotebook->buttonDeleteFile, WM_SETFONT, 
            (WPARAM)fontDefault, 0);
        SetWindowText(objNotebook->buttonDeleteFile, "Delete Selected File");
    }

    GetWindowRect(objNotebook->buttonDeleteFile, &rect);
    AdjustRectToWindow(&rect, hPWnd);

    GetWindowRect(objNotebook->comboFiles, &topRect);
    AdjustRectToWindow(&topRect, hPWnd);

    objNotebook->editNewFile = CreateWindowEx(0, "EDIT", "", 
        baseStyle | WS_TABSTOP | ES_AUTOHSCROLL, 
        topRect.left, topRect.bottom+20, 170, EDITHEIGHT, 
        *hPWnd, (HMENU)IDC_EDIT_NEWFILE, GetModuleHandle(NULL), NULL);
    if (objNotebook->editNewFile == NULL) {
        Result = -1;
        return(Result);
    } else {
        hdc = GetDC(objNotebook->editNewFile);
        CreateDefaultFont(&fontDefault, &hdc);
        SendMessage(objNotebook->editNewFile, WM_SETFONT, 
            (WPARAM)fontDefault, 0);
        SendMessage(objNotebook->editNewFile, EM_SETCUEBANNER, 
            (WPARAM)FALSE, (LPARAM)L"Enter a new file name.");
    }

    GetWindowRect(objNotebook->editNewFile, &rect);
    AdjustRectToWindow(&rect, hPWnd);

    GetWindowRect(objNotebook->editNewFile, &leftRect);
    AdjustRectToWindow(&leftRect, hPWnd);

    height = leftRect.bottom-leftRect.top;
    vspacing = (height-BUTTONHEIGHT)/2;
    objNotebook->buttonNewFile = CreateWindow("BUTTON", "OK", 
        baseStyle | WS_TABSTOP | BS_PUSHBUTTON,
        leftRect.right+30, leftRect.top+vspacing, 130, BUTTONHEIGHT,
        *hPWnd, (HMENU)IDC_BUTTON_NEWFILE, GetModuleHandle(NULL), NULL);
    if (objNotebook->buttonNewFile == NULL) {
        Result = -1;
        return(Result);
    } else {
        hdc = GetDC(objNotebook->buttonNewFile);
        CreateDefaultFont(&fontDefault, &hdc);
        SendMessage(objNotebook->buttonNewFile, WM_SETFONT, 
            (WPARAM)fontDefault, 0);
        SetWindowText(objNotebook->buttonNewFile, "Save to New File");
    }

    GetWindowRect(objNotebook->buttonNewFile, &rect);
    AdjustRectToWindow(&rect, hPWnd);

    GetWindowRect(objNotebook->editNewFile, &topRect);
    AdjustRectToWindow(&topRect, hPWnd);

    objNotebook->labelNotes = CreateWindowEx(0, "STATIC", "", 
        baseStyle | SS_LEFT, 
        topRect.left, topRect.bottom+20, 100, EDITHEIGHT, 
        *hPWnd, (HMENU)IDC_LABEL_NOTES, GetModuleHandle(NULL), NULL);
    if (objNotebook->labelNotes == NULL) {
        Result = -1;
        return(Result);
    }

    GetWindowRect(objNotebook->labelNotes, &rect);
    AdjustRectToWindow(&rect, hPWnd);

    GetWindowRect(objNotebook->labelNotes, &topRect);
    AdjustRectToWindow(&topRect, hPWnd);

    objNotebook->editNotes = CreateWindowEx(0, "EDIT", "",
        baseStyle | WS_TABSTOP | WS_VSCROLL | ES_AUTOVSCROLL | ES_MULTILINE | ES_LEFT | ES_WANTRETURN, 
        topRect.left, topRect.bottom+10, 
        XEND-topRect.left, YEND-topRect.bottom-10,
        *hPWnd, (HMENU)IDC_EDIT_NOTES, GetModuleHandle(NULL), NULL);
    if (objNotebook->editNotes == NULL) {
        Result = -1;
        return(Result);
    } else {
        SetWindowSubclass(objNotebook->editNotes, MultiLineWindowProc, 0, 0);
        hdc = GetDC(objNotebook->editNotes);
        CreateDefaultFont(&fontDefault, &hdc);
        SendMessage(objNotebook->editNotes, WM_SETFONT, (WPARAM)fontDefault, 0);
        strcpy(objNotebook->fileContents, "");
        ChangeFileLocation(objNotebook, objNotebook->currentFile);
        if (strcmp(objNotebook->currentFile, "") != 0) {
            objNotebook->fileHandle = CreateFile(objNotebook->fileLocation, 
                GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS,
                FILE_ATTRIBUTE_NORMAL, NULL);
            if (objNotebook->fileHandle != INVALID_HANDLE_VALUE) {
                DWORD readEOF = 1;
                int i = 0;
                while (readEOF != 0 && i < MAX_ARRAY_LENGTH*4-1) {
                    ReadFile(objNotebook->fileHandle, &objNotebook->fileContents[i], 
                        1, &readEOF, NULL);
                    i++;
                }
                objNotebook->fileContents[i-1] = '\0';
                CloseHandle(objNotebook->fileHandle);
            } else {
                MessageBox(*hPWnd, 
                    "File could not be read.",
                    "Unknown Error", MB_OK);
            }
        }
        SetWindowText(objNotebook->editNotes, objNotebook->fileContents);
    }

    return (Result);
}


LRESULT DestroyNotebookWindow(Notebook *objNotebook) {
    LRESULT Result = 0;

    if (strcmp(objNotebook->currentFile, "") == 0) {
        strcpy(objNotebook->currentFile, "notebook.txt");
        objNotebook->nameLength = 12;

        objNotebook->fileHandle = CreateFile(objNotebook->fileListLocation, 
                GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, 
                OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

        if (objNotebook->fileHandle != INVALID_HANDLE_VALUE) {
            SetFilePointer(objNotebook->fileHandle, NULL, NULL, FILE_END);
            WriteFile(objNotebook->fileHandle, objNotebook->currentFile, 
                objNotebook->nameLength, NULL, NULL);
            WriteFile(objNotebook->fileHandle, "\n", sizeof(char), NULL, NULL);
            CloseHandle(objNotebook->fileHandle);
        }

        SendMessage(objNotebook->comboFiles, CB_ADDSTRING, 
            (WPARAM)0, (LPARAM)objNotebook->currentFile);
        objNotebook->baseSelected = (int)SendMessage(objNotebook->comboFiles, 
            CB_SELECTSTRING, (WPARAM)-1, (LPARAM)objNotebook->currentFile);
        SendMessage(objNotebook->comboFiles, CB_SETCURSEL, 
            (WPARAM)objNotebook->baseSelected, (LPARAM)0);

        ChangeFileLocation(objNotebook, objNotebook->currentFile);
        objNotebook->fileHandle = CreateFile(objNotebook->fileLocation, 
            GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS,
            FILE_ATTRIBUTE_NORMAL, NULL);

        if (objNotebook->fileHandle != INVALID_HANDLE_VALUE) {
            objNotebook->textLength = 
                GetWindowTextLength(objNotebook->editNotes);

            if (objNotebook->textLength > MAX_ARRAY_LENGTH*4-1) {
                objNotebook->textLength = MAX_ARRAY_LENGTH*4-1;
            }
            GetWindowText(objNotebook->editNotes, objNotebook->fileContents, 
                objNotebook->textLength+1);
            WriteFile(objNotebook->fileHandle, objNotebook->fileContents, 
                objNotebook->textLength, NULL, NULL);

            CloseHandle(objNotebook->fileHandle);

        } else {
            MessageBox(objNotebook->editNotes, 
                "Writing to the file has failed.",
                "Unknown Error", MB_OK);
            objNotebook->fileHandle = CreateFile("tmp.txt", 
                GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, 
                OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

            if (objNotebook->fileHandle != INVALID_HANDLE_VALUE) {
                objNotebook->textLength = 
                    GetWindowTextLength(objNotebook->editNotes);
                if (objNotebook->textLength > MAX_ARRAY_LENGTH*4-1) {
                    objNotebook->textLength = MAX_ARRAY_LENGTH*4-1;
                }
                GetWindowText(objNotebook->editNotes, objNotebook->fileContents, 
                    objNotebook->textLength+1);
                WriteFile(objNotebook->fileHandle, objNotebook->fileContents, 
                    objNotebook->textLength, NULL, NULL);

                CloseHandle(objNotebook->fileHandle);

                MessageBox(objNotebook->editNotes, 
                    "File has been saved in the toolkit's main directory, alongside the exe file.",
                    "Temporary File Created", MB_OK);

            } else {
                MessageBox(objNotebook->editNotes, objNotebook->fileContents, 
                    "Copy your text and save manually.", MB_OK);
            }
        }
    } else {
        objNotebook->fileHandle = CreateFile(objNotebook->tmpFileLocation, 
            GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS,
            FILE_ATTRIBUTE_NORMAL, NULL);

        if (objNotebook->fileHandle != INVALID_HANDLE_VALUE) {
            objNotebook->textLength = GetWindowTextLength(objNotebook->editNotes);
            
            if (objNotebook->textLength > MAX_ARRAY_LENGTH*4-1) {
                objNotebook->textLength = MAX_ARRAY_LENGTH*4-1;
            }
            GetWindowText(objNotebook->editNotes, objNotebook->fileContents, 
                objNotebook->textLength+1);
            WriteFile(objNotebook->fileHandle, objNotebook->fileContents, 
                objNotebook->textLength, NULL, NULL);
            CloseHandle(objNotebook->fileHandle);
            MoveFileEx(objNotebook->tmpFileLocation, objNotebook->fileLocation, 
                MOVEFILE_REPLACE_EXISTING);
        } else {
            MessageBox(objNotebook->editNotes, 
                "Writing to the file has failed.",
                "Unknown Error", MB_OK);
            objNotebook->fileHandle = CreateFile("tmp.txt", 
                GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, 
                OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

            if (objNotebook->fileHandle != INVALID_HANDLE_VALUE) {
                objNotebook->textLength = 
                    GetWindowTextLength(objNotebook->editNotes);
                if (objNotebook->textLength > MAX_ARRAY_LENGTH*4-1) {
                    objNotebook->textLength = MAX_ARRAY_LENGTH*4-1;
                }
                GetWindowText(objNotebook->editNotes, objNotebook->fileContents, 
                    objNotebook->textLength+1);
                WriteFile(objNotebook->fileHandle, objNotebook->fileContents, 
                    objNotebook->textLength, NULL, NULL);

                CloseHandle(objNotebook->fileHandle);

                MessageBox(objNotebook->editNotes, 
                    "File has been saved in the toolkit's main directory, alongside the exe file.",
                    "Temporary File Created", MB_OK);

            } else {
                MessageBox(objNotebook->editNotes, objNotebook->fileContents, 
                    "Copy your text and save manually.", MB_OK);
            }
        }
    }

    if (!DestroyWindow(objNotebook->comboFiles)) {
        Result = -1;
    }
    if (!DestroyWindow(objNotebook->buttonDeleteFile)) {
        Result = -1;
    }
    if (!DestroyWindow(objNotebook->editNewFile)) {
        Result = -1;
    }
    if (!DestroyWindow(objNotebook->buttonNewFile)) {
        Result = -1;
    }
    if (!DestroyWindow(objNotebook->labelNotes)) {
        Result = -1;
    }
    if (!DestroyWindow(objNotebook->editNotes)) {
        Result = -1;
    }

    return (Result);
}