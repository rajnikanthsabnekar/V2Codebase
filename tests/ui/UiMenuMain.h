// UiMenuMain.h

#ifndef _UIMENUMAIN_h
#define _UIMENUMAIN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "VentIncludes.h"

class UiMenuMainClass
{
 protected:
 

 public:

	UiMenuMainClass() {} ;

	void init();
	
	void drawSplashScreen(int displayTime);
	
	void drawClosingScreen();
	
	void drawRuntimeScreens(void) ;
	
	void drawEditScreens(void);
	
	void drawEditScreen1(void);
	
	void drawEditScreen2(void);
	
	void drawEditScreen3(void);
	
	void drawEditScreen4(void);
	
	void drawEditScreen5(void);
	
	void drawEditScreen6(void);
	
	void runtimeDisplayOptions(ParameterDisplayFormat option);
	
	void drawRuntimeScreen1(void);
	
	void drawRuntimeScreen2(void);
	
	void drawRuntimeScreen3(void);
	
	void drawServiceMenuScreen1(void);
	
	void drawServiceMenuScreen2(void);
	
	void drawServiceMenuScreen3(void);
	
	
	void clearDisplay(void);
	
	void lookForKeyEvents(void);
	
	void errorScreen ( int moduleName, int msgId);

private:
	void drawRuntimeTopBottomLines(int currentPage, int totalPages);	
	
	void drawEditTopBottomLines(/*int currentPage, int totalPages*/void);	
	
	
	void updateScreen();
	
	
	struct MenuItems {
		int						currentPosition;
		ParameterDisplayFormat	paramPerScreen;
		int						totalPages;
	}; 	

	/// run time screen parameters
	struct MenuItems editState;
	
	/// edit screen parameters
	struct MenuItems runtimeState;
	
	struct MenuItems currentState;
	
};

extern UiMenuMainClass UiMenuMain;

#endif

