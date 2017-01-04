#ifndef TOOLKIT_HOME
#define TOOLKIT_HOME

struct Home {

	HWND buttonDonate;
	HWND staticTitle;
	HWND staticDesc;
	HWND staticContact;
	HWND staticDonate;
	HWND staticDesc0;
	HWND staticDesc1;
	HWND staticDesc2;
	HWND staticDesc3;
	HWND staticDesc4;
	HWND staticDesc5;
	HWND staticLogo;
	HWND staticUpdate;

	HBITMAP bitmapDonate;
	HBITMAP canonnLogo;

	int buttonWidth = 92;
	int buttonHeight = 26;

	char logoLocation[MAX_ARRAY_LENGTH];
	char donateBitmapLocation[MAX_ARRAY_LENGTH];
	char donateURL[MAX_ARRAY_LENGTH];
	char desc0[MAX_ARRAY_LENGTH];
	char desc1[MAX_ARRAY_LENGTH];
	char desc2[MAX_ARRAY_LENGTH];
	char desc3[MAX_ARRAY_LENGTH];
	char desc4[MAX_ARRAY_LENGTH];
	char desc5[MAX_ARRAY_LENGTH];
	char link1[MAX_ARRAY_LENGTH];
	char link2[MAX_ARRAY_LENGTH];
	char link3[MAX_ARRAY_LENGTH];
	char link4[MAX_ARRAY_LENGTH];
	char link5[MAX_ARRAY_LENGTH];
	char contact[MAX_ARRAY_LENGTH];
	char donate[MAX_ARRAY_LENGTH];
	char title[MAX_ARRAY_LENGTH];
	char updateText[MAX_ARRAY_LENGTH];
	char updateLink[MAX_ARRAY_LENGTH];

	Home() {
		strcpy(desc0, "Here is a list of some Canonn related links.");
		strcpy(desc1, "Canonn Website");
		strcpy(desc2, "INARA - Canonn Wing");
		strcpy(desc3, "Frontier Forums Canonn Thread");
		strcpy(desc4, "Canonn Discord");
		strcpy(desc5, "Canonn Subreddit");
		strcpy(link1, "http://canonn.science/");
		strcpy(link2, "http://inara.cz/wing/534");
		strcpy(link3, "https://forums.frontier.co.uk/showthread.php/241512-Canonn");
		strcpy(link4, "http://canonn.science/codex/resource/discord");
		strcpy(link5, "https://www.reddit.com/r/Canonn");
		strcpy(donateBitmapLocation, "./images/donateButton.bmp");
		strcpy(donateURL, "https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=LY7J9H789NUYL");
		strcpy(contact, "To report a bug or give\n feedback, send an email\n to jenn.hernes@gmail.com\n");
		strcpy(donate, "If you wish to donate to\nthe app's developer, click\nthe donate button.\n");
		strcpy(title, "Welcome to the Canonn Toolkit!");
		strcpy(logoLocation, "./images/canonnLogo.bmp");
		strcpy(updateText, "Check for update");
		strcpy(updateLink, "https://github.com/jennhernes/CanonnToolkit");
	}
};


LRESULT PaintHomeWindow(HWND *hPWnd, Home *objHome);

LRESULT DestroyHomeWindow(Home *objHome);

#endif