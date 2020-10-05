// 
// 
// 

#include "UiMenuMain.h"
#include "encoder/encoder.h"



/// Custom Characters
/*
byte boxCustomChar[] = {
	B00000,
	B00000,
	B01110,
	B01110,
	B01110,
	B01110,
	B00000,
	B00000
};
/// rotate

byte rotateCustomChar[] = {
	B00000,
	B11111,
	B00001,
	B01001,
	B11101,
	B01001,
	B01111,
	B00000
};


byte rotate1customChar[] = {
	B00000,
	B11111,
	B00001,
	B01001,
	B11101,
	B11001,
	B10001,
	B11111
};

*/

/// Down box arrow
byte editCustomChar[] = {
	B01110,
	B01110,
	B01010,
	B01010,
	B01110,
	B11011,
	B01110,
	B00100
};

/// arrown over a container line
byte saveCustomChar[] = {
  B00100,
  B00100,
  B00100,
  B10101,
  B01110,
  B00100,
  B10001,
  B11111
};

// double arrow rotate
byte rotate2customChar[] = {
	B11110,
	B10010,
	B10111,
	B00010,
	B01000,
	B11101,
	B01001,
	B01111
};

byte pressEditCustomChar[] = {
  B10001,
  B00000,
  B01110,
  B01110,
  B01110,
  B01110,
  B00000,
  B10001
};

byte rightArrowCustomChar[] = {
  B00000,
  B01000,
  B00100,
  B00010,
  B00100,
  B01000,
  B00000,
  B00000
};

const char clearScreenBuffer[21] = {
	0x20,0x20,0x20,0x20,0x20,
	0x20,0x20,0x20,0x20,0x20,
	0x20,0x20,0x20,0x20,0x20,
	0x20,0x20,0x20,0x20,0x20,0x0
};

// buffer for this pattern "          > > "
const char topBottomLineBuffer[18] = {
	0x20,0x20,0x20,0x20,0x20,
	0x20,0x20,0x20,0x20,0x20,
	0x20,0x20,0x20,0x20,0x20,
	0x20,0x20,0x00
};

const char splashScreenTopBottomBuffer[21] = {
	0xFF,0xFF,0xFF,0xFF,0xFF,
	0x20,0x20,0x20,0x20,0x20,
	0x20,0x20,0x20,0x20,0x20,
	0xFF,0xFF,0xFF,0xFF,0xFF,0x0
};

const char splashScreenMiddleBuffer[21] = {
	0xFF,0x20,0x20,0x20,0x20,
	0x20,0x20,0x20,0x20,0x20,
	0x20,0x20,0x20,0x20,0x20,
	0x20,0x20,0x20,0x20,0xFF,0x0
};

enum Icons {
	ROTATE_FOR_MORE	=0x0,
	PRESS_TO_SAVE	=0x1,
	PRESS_TO_EDIT	=0x2,
	GENERIC_NAME1	=0x3,
	GENERIC_NAME2	=0x4,
	GENERIC_NAME3	=0x5,
	GENERIC_NAME4	=0x6,
	RIGHT_ARROW_ICON=0x7,
	SEPERATOR_TYPE1	=0x8
	};

extern LiquidCrystal lcd;

UiMenuMainClass UiMenuMain;

void UiMenuMainClass::init() {
	// set up the LCD's number of columns and rows:
	lcd.begin(20, 4);
	//lcd.createChar(GENERIC_NAME1,boxCustomChar);
	lcd.createChar(GENERIC_NAME2,editCustomChar);
	//lcd.createChar(GENERIC_NAME3,rotateCustomChar);
	//lcd.createChar(GENERIC_NAME4,rotate1customChar);
	lcd.createChar(PRESS_TO_SAVE,saveCustomChar);
	lcd.createChar(ROTATE_FOR_MORE,rotate2customChar);
	lcd.createChar(PRESS_TO_EDIT,pressEditCustomChar);
	lcd.createChar(RIGHT_ARROW_ICON,rightArrowCustomChar);
	
	
	editState.currentPosition = 0;
	
	runtimeState.currentPosition = 0;
	
	runtimeState.paramPerScreen = PARAM_3_VERTICAL;
	
	pinMode(DISPLAY_BACK_LED_PIN,OUTPUT);
	digitalWrite(DISPLAY_BACK_LED_PIN,HIGH);
	UiMenuMain.drawSplashScreen(DELAY_1_SECOND);
	
	return;
		
}

void UiMenuMainClass::drawSplashScreen(int displayTime) {
	
	lcd.setCursor(0,0);
	lcd.write(splashScreenTopBottomBuffer);
	lcd.setCursor(0,1);
	lcd.write(splashScreenMiddleBuffer);
	lcd.setCursor(0,2);
	lcd.write(splashScreenMiddleBuffer);
	lcd.setCursor(0,3);
	lcd.write(splashScreenTopBottomBuffer);
	lcd.setCursor(5,1);
	lcd.write("  Tworks  ");
	lcd.setCursor(5,2);
	lcd.write("Ventilator");
	
	delay(displayTime);
	
	return;
}

void UiMenuMainClass::drawClosingScreen() {
	return;
}

void UiMenuMainClass::runtimeDisplayOptions(ParameterDisplayFormat option) {
	runtimeState.paramPerScreen = option;
	
	return;
}

void UiMenuMainClass::drawRuntimeScreens() {
	
	lcd.display();
	
	if ( runtimeState.currentPosition == 0 ) {
		drawRuntimeScreen1();
	} else if ( runtimeState.currentPosition == 1 ) {
		drawRuntimeScreen2();
	}else if ( runtimeState.currentPosition == 2 ) {
		drawRuntimeScreen3();
	}
	runtimeState.currentPosition++;
	if ( runtimeState.currentPosition >= 3 ) {
		runtimeState.currentPosition = 0 ;
	}
	
	return;
}
	
void UiMenuMainClass::drawEditScreens() {
	
	drawEditTopBottomLines();
	
	if ( editState.currentPosition == 0 ) {
		drawEditScreen1();
	} else if ( editState.currentPosition == 1 ) {
		drawEditScreen2();
	}else if ( editState.currentPosition == 2 ) {
		drawEditScreen3();
	}else if ( editState.currentPosition == 3 ) {
		drawEditScreen4();
	}

	editState.currentPosition++;
	if ( editState.currentPosition >= 4 ) {
		editState.currentPosition = 0 ;
	}

	
	return;
}

void UiMenuMainClass::drawEditScreen1(void) {
	
	/// Main Edit Screen 
	lcd.setCursor(0,0);
	lcd.write("  TV    RR   IER   Pmax ");
	lcd.setCursor(0,1);
	lcd.write("  400   40   1:3    40  ");
	lcd.setCursor(0,2);
	lcd.write(" <400> <40> <1:3>  <40> ");
	lcd.setCursor(0,3);
	lcd.write("  v     v     v      v  ");
	
	drawEditTopBottomLines();
}

void UiMenuMainClass::drawEditScreen2(void) {
	
}
	
void UiMenuMainClass::drawEditScreen3(void){
}
	
void UiMenuMainClass::drawEditScreen4(void){
	
}


void UiMenuMainClass::drawRuntimeScreen1(void) {

	drawRuntimeTopBottomLines();

	if ( runtimeState.paramPerScreen == PARAM_3_VERTICAL ) {
		
		lcd.setCursor(0,1);
		lcd.write(" TV    TVi   TVe  ");
		lcd.setCursor(0,2);
		lcd.write(" 400   380   420  ");

	}else if ( runtimeState.paramPerScreen == PARAM_4_VERTICAL ){
		
		lcd.setCursor(0,0);
		lcd.write(" TV        TVi   ");
		lcd.setCursor(0,1);
		lcd.write(" 400       420   ");
		
		lcd.setCursor(0,2);
		lcd.write(" TVe       IER   ");
		lcd.setCursor(0,3);
		lcd.write(" 380       1:3   ");
		
	}else if ( runtimeState.paramPerScreen == PARAM_3_HORIZONTAL){
	
		lcd.setCursor(0,1);
		lcd.write("   TV      400   ");
		lcd.setCursor(0,2);
		lcd.write("   TVi     380   ");
		lcd.setCursor(0,3);
		lcd.write("   TVe     420   ");
		
	} else if ( runtimeState.paramPerScreen == PARAM_4_HORIZONTAL ){
	
		lcd.setCursor(0,0);
		lcd.write(" TV        400   ");
		lcd.setCursor(0,1);
		lcd.write(" TVi       420   ");
	
		lcd.setCursor(0,2);
		lcd.write(" TVe       380   ");
		lcd.setCursor(0,3);
		lcd.write(" IER       1:3   ");
	
	}
	
	return;	
}

void UiMenuMainClass::drawRuntimeScreen2(void) {
	
	drawRuntimeTopBottomLines();
	
	if ( runtimeState.paramPerScreen == PARAM_3_VERTICAL ) {	
		
		lcd.setCursor(0,1);
		lcd.write(" IE    RR   Plato ");
		lcd.setCursor(0,2);
		lcd.write(" 1:3   30    34   ");
		
	} else 	if ( runtimeState.paramPerScreen == PARAM_3_HORIZONTAL ) {
		
		lcd.setCursor(0,1);
		lcd.write("   IER      1:3  ");
		lcd.setCursor(0,2);
		lcd.write("   RR       30   ");
		lcd.setCursor(0,3);
		lcd.write("   Plato    34   ");
		
	} else if ( runtimeState.paramPerScreen == PARAM_4_VERTICAL ) {

		lcd.setCursor(0,0);
		lcd.write(" RR        Plato ");
		lcd.setCursor(0,1);
		lcd.write(" 30         34   ");
				
		lcd.setCursor(0,2);
		lcd.write(" PIP       PEEP  ");
		lcd.setCursor(0,3);
		lcd.write(" 38        10   ");
		
	} else 	if ( runtimeState.paramPerScreen == PARAM_4_HORIZONTAL ) {
		lcd.setCursor(0,0);
		lcd.write(" RR        30    ");
		lcd.setCursor(0,1);
		lcd.write(" Plato     34    ");
		lcd.setCursor(0,2);
		lcd.write(" PIP       38    ");
		lcd.setCursor(0,3);
		lcd.write(" PEEP      10    ");
	}
	return;
}

void UiMenuMainClass::drawRuntimeScreen3(void) {
	
	drawRuntimeTopBottomLines();

	if ( runtimeState.paramPerScreen == PARAM_3_VERTICAL ) {
	
		lcd.setCursor(0,1);
		lcd.write(" PIP  FiO2   PEEP ");
		lcd.setCursor(0,2);
		lcd.write(" 42    40%    10  ");
		
	} else 	if ( runtimeState.paramPerScreen == PARAM_3_HORIZONTAL ) {
	
		lcd.setCursor(0,1);
		lcd.write("   PIP      42   ");
		lcd.setCursor(0,2);
		lcd.write("   FiO2     40%  ");
		lcd.setCursor(0,3);
		lcd.write("   PEEP     10   ");
	
	} else if ( runtimeState.paramPerScreen == PARAM_4_VERTICAL ) {
		
		lcd.setCursor(0,0);
		lcd.write(" FiO2            ");
		lcd.setCursor(0,1);
		lcd.write(" 40%             ");

	}  else if ( runtimeState.paramPerScreen == PARAM_4_HORIZONTAL ) {
	
		lcd.setCursor(0,0);
		lcd.write(" FiO2      40%   ");

	}

	return ;
}

void UiMenuMainClass::clearDisplay(void) {
	lcd.setCursor(0,0);
	lcd.write(clearScreenBuffer);
	lcd.write(clearScreenBuffer);
	lcd.write(clearScreenBuffer);
	lcd.write(clearScreenBuffer);
	
	return;
}


void UiMenuMainClass::drawRuntimeTopBottomLines(void) {
	lcd.setCursor(0,0);
	lcd.write(topBottomLineBuffer);
	lcd.write(RIGHT_ARROW_ICON);lcd.write(" ");lcd.write(ROTATE_FOR_MORE);
	lcd.setCursor(0,3);
	lcd.write(topBottomLineBuffer);
	lcd.write(RIGHT_ARROW_ICON);lcd.write(" ");lcd.write(PRESS_TO_EDIT);
	
	return;
}

void UiMenuMainClass::drawEditTopBottomLines(void) {
	
	lcd.setCursor(0,19);
	lcd.write(ROTATE_FOR_MORE);
	lcd.setCursor(2,19);
	lcd.write(PRESS_TO_SAVE);
	
	return;
	
}

void lookForKeyEvents(void) {
	
	RT_Events_T eRTState = RT_NONE;
	eRTState = encoderScanUnblocked();
	switch (eRTState)
	{
		case RT_INC:
		
		break;
		case   RT_DEC:
		break;
		case   RT_BT_PRESS:
		break;
		case RT_NONE:
		break;
	}
	
	if (eRTState != RT_NONE) {

	}
	
	return;
}

void testIcons(){
	//	lcd.setCursor(5,0);
	//	lcd.write(GENERIC_NAME1);
	
	lcd.setCursor(15,0);
	lcd.write(GENERIC_NAME2);
	
	//lcd.setCursor(10,1);
	//lcd.write(GENERIC_NAME3);
	
	//lcd.setCursor(20,1);
	//lcd.write(GENERIC_NAME4);
	
	lcd.setCursor(15,2);
	lcd.write(PRESS_TO_EDIT);

	lcd.setCursor(5,2);
	lcd.write(PRESS_TO_SAVE);
	
	lcd.setCursor(7,3);
	lcd.write(ROTATE_FOR_MORE);
	
	lcd.setCursor(15,3);
	lcd.write(RIGHT_ARROW_ICON);

	return ;
}
