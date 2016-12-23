#ifndef TOOLKIT_NOTEBOOK
#define TOOLKIT_NOTEBOOK

struct Notebook {

	HWND comboFiles;
	HWND buttonDeleteFile;
	HWND buttonNewFile;
	HWND editNewFile;
	HWND labelNotes;
	HWND editNotes;

	HANDLE fileHandle;

	int textLength;
	int nameLength;
	int baseSelected;

	char fileDirectory[MAX_ARRAY_LENGTH];
	char fileLocation[MAX_ARRAY_LENGTH+20];
	char currentFile[MAX_ARRAY_LENGTH];
	char fileContents[MAX_ARRAY_LENGTH*4];
	char fileListName[MAX_ARRAY_LENGTH];
	char fileListLocation[MAX_ARRAY_LENGTH];
	char tmpFileName[MAX_ARRAY_LENGTH];
	char tmpFileLocation[MAX_ARRAY_LENGTH];


	Notebook() : textLength(0), nameLength(0), baseSelected(0) {
		strcpy(fileDirectory, "./Notebook/");
		strcpy(currentFile, "");
		strcpy(fileContents, "");
		strcpy(fileListName, "fileList.txt");
		strcpy(fileListLocation, fileDirectory);
		strcat(fileListLocation, fileListName);
		strcpy(tmpFileName, "tmp.txt");
		strcpy(tmpFileLocation, fileDirectory);
		strcat(tmpFileLocation, tmpFileName);

		CreateDirectory(fileDirectory, NULL);
		fileHandle = CreateFile(tmpFileLocation, GENERIC_READ | GENERIC_WRITE, 
			FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		if (fileHandle != INVALID_HANDLE_VALUE) {
			char eos;
			int i = 0;
			WIN32_FIND_DATA ffd;
			HANDLE hnf = FindFirstFile("./Notebook/*", &ffd);

			if (hnf != INVALID_HANDLE_VALUE) {

				if (strcmp(ffd.cFileName, fileListName) != 0 &&
					strcmp(ffd.cFileName, tmpFileName) != 0 &&
					strcmp(ffd.cFileName, ".") != 0 &&
					strcmp(ffd.cFileName, "..") != 0) {
					eos = ffd.cFileName[i];
					while(eos != '\0') {
						WriteFile(fileHandle, &ffd.cFileName[i], 1, NULL, NULL);
						i++;
						eos = ffd.cFileName[i];
					}
					WriteFile(fileHandle, "\n", 1, NULL, NULL);
				}
				while (FindNextFile(hnf, &ffd) != 0) {
					if (strcmp(ffd.cFileName, fileListName) != 0 &&
						strcmp(ffd.cFileName, tmpFileName) != 0 &&
						strcmp(ffd.cFileName, ".") != 0 &&
						strcmp(ffd.cFileName, "..") != 0) {
						i = 0;
						eos = ffd.cFileName[i];
						while(eos != '\0') {
							WriteFile(fileHandle, &ffd.cFileName[i], 1, 
								NULL, NULL);
							i++;
							eos = ffd.cFileName[i];
						}
						WriteFile(fileHandle, "\n", 1, NULL, NULL);
					}
				}
				FindClose(hnf);
			}
			CloseHandle(fileHandle);
			MoveFileEx(tmpFileLocation, fileListLocation, 
				MOVEFILE_REPLACE_EXISTING);
		}
	}

	~Notebook() {
		DeleteFile(fileListLocation);
		DeleteFile(tmpFileLocation);
	}
};


void ChangeFileLocation(Notebook *objNotebook, char *text);

LRESULT PaintNotebookWindow(HWND *hPWnd, Notebook *objNotebook);

LRESULT DestroyNotebookWindow(Notebook *objNotebook);

#endif