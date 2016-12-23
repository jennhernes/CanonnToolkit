#ifndef TOOLKIT_BEARING
#define TOOLKIT_BEARING

struct Bearing {
	HWND labelStarting;
	HWND labelLat1;
	HWND labelLon1;
	HWND labelEnding;
	HWND labelLat2;
	HWND labelLon2;
	HWND editLat1;
	HWND editLon1;
	HWND editLat2;
	HWND editLon2;
	HWND buttonCalc;
	HWND staticBearing;
	
	double lat1;
	double lon1;
	double lat2;
	double lon2;
	double bearing;

	bool dataStored;

	Bearing() : lat1(0), lon1(0), lat2(0), lon2(0), bearing(0), 
				dataStored(FALSE) {}
};


LRESULT PaintBearingWindow(HWND *hPWnd, Bearing *objBearing);

LRESULT DestroyBearingWindow(Bearing *objBearing);

#endif