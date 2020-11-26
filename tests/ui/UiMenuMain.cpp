// 
// 
// 

#include "UiMenuMain.h"
//#include "encoder/encoder.h"



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

byte doubleArrowCustomChar[] = {
	B00000,
	B10001,
	B01010,
	B10101,
	B01010,
	B00100,
	B00000,
	B00000
};

byte singleDownArrowCustomChar[] = {
	B00000,
	B00000,
	B00000,
	B00000,
	B10001,
	B01010,
	B00100,
	B00000
};

byte InvertPointedArrowCustomChar[] = {
	B00000,
	B00100,
	B00100,
	B00100,
	B10101,
	B01110,
	B00100,
	B00000
};

byte filledDownArrowCustomChar[] = {
	B00100,
	B00100,
	B00100,
	B00100,
	B11111,
	B01110,
	B00100,
	B00000
};





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
byte saveCustomChar1[] = {
  B00100,
  B00100,
  B00100,
  B10101,
  B01110,
  B00100,
  B10001,
  B11111
};

byte saveCustomChar2[] = {
    B00011,
    B10001,
    B01001,
    B00101,
    B00101,
    B01001,
    B10001,
    B00011
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
B00100,
B00010,
B11111,
B11111,
B00010,
B00100,
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
	ROTATE_FOR_MORE	=0x4,
	PRESS_TO_SAVE	=0x5,
	PRESS_TO_EDIT	=0x6,
//	GENERIC_NAME1	=0x3,
//	GENERIC_NAME2	=0x4,
//	GENERIC_NAME3	=0x5,
//	GENERIC_NAME4	=0x6,
	RIGHT_ARROW_ICON=0x7,
	SEPERATOR_TYPE1	=0x8
	};

extern LiquidCrystal lcd;

UiMenuMainClass UiMenuMain;

void UiMenuMainClass::init() {
	// set up the LCD's number of columns and rows:
	lcd.begin(20, 4);
	
	
	lcd.createChar(0x0, doubleArrowCustomChar);
	lcd.createChar(0x1, singleDownArrowCustomChar);
	lcd.createChar(0x2, InvertPointedArrowCustomChar);
	lcd.createChar(0x3, filledDownArrowCustomChar);
		
	lcd.createChar(0x4,rotate2customChar);
	lcd.createChar(0x5,saveCustomChar2);
		
	lcd.createChar(PRESS_TO_EDIT,pressEditCustomChar);
	lcd.createChar(RIGHT_ARROW_ICON,rightArrowCustomChar);

	
	editState.currentPosition = 0;
	
	runtimeState.currentPosition = 0;
	
	runtimeState.totalPages = 3;
	
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
	}else if ( editState.currentPosition == 4 ) {
		drawEditScreen5();
	}else if ( editState.currentPosition == 5 ) {
		drawEditScreen6();
	}

	editState.currentPosition++;
	if ( editState.currentPosition >= 6 ) {
		editState.currentPosition = 0 ;
	}

	
	return;
}

void UiMenuMainClass::drawEditTopBottomLines(void) {
	
	lcd.setCursor(19,0);
	lcd.write((byte)(0x4));

//	lcd.setCursor(19,3);
//	lcd.write((byte)(0x5));
	
	return;
	
}


void UiMenuMainClass::drawEditScreen1(void) {
	

	/// Main Edit Screen 
	lcd.setCursor(0,0);
	lcd.write(" RR  TV  Pmax IER");
	lcd.setCursor(0,1);
	lcd.write(" 40  400  40  1:3");
	lcd.setCursor(0,2);
	lcd.write("<40><400><40><1:3>");
	
	//lcd.setCursor(0,3);
	//lcd.write(" v    v     v    v ");
	lcd.setCursor(1,3);lcd.write((byte)(0x3));
	lcd.setCursor(6,3);lcd.write((byte)(0x3));
	lcd.setCursor(11,3);lcd.write((byte)(0x3));
	lcd.setCursor(16,3);lcd.write((byte)(0x3));
	
	//drawEditTopBottomLines();
	lcd.setCursor(19,3);
	lcd.write((byte)(0x5));

	delay( DELAY_1_SECOND * 2 );
}

void UiMenuMainClass::drawEditScreen2(void) {
	
	lcd.setCursor(7,0);
	lcd.write("ALARMS");
	lcd.setCursor(1,2);
	lcd.write("FiO2  35%  <35%>");
	lcd.setCursor(14,3);
	lcd.write((byte)(0x3));
	
	drawEditTopBottomLines();
	lcd.setCursor(19,3);
	lcd.write((byte)(0x6));
	
	delay(200);
	lcd.setCursor(19,3);
	lcd.write((byte)(0x5));
	
	for ( int i = 0 ; i < 3 ; i ++ ){
		lcd.setCursor(13,2);
		lcd.print( 40 + (5 * i) );	
		delay(DELAY_1_SECOND);
	}
	lcd.setCursor(7,2);lcd.print(50);
	lcd.setCursor(19,3);
	lcd.write((byte)(0x6));
	
	return ;
}
	
void UiMenuMainClass::drawEditScreen3(void){
	
	lcd.setCursor(7,0);
	lcd.write("About");
	lcd.setCursor(0,1);
	lcd.write("Device   : BMV");
	lcd.setCursor(0,2);
	lcd.write("Serial No: TW0001");
	lcd.setCursor(0,3);
	lcd.write("Version  : P4_V2.3");

	//drawEditTopBottomLines();
	lcd.setCursor(19,3);
	lcd.write(" ");
	
	return ;
	
}
	
void UiMenuMainClass::drawEditScreen4(void){
#if 0

	lcd.setCursor(3,0);
	lcd.write("Raw Voltages");
	
	lcd.setCursor(0,2);
	lcd.write("GP1 :256 DP1:2899");
	lcd.setCursor(0,3);
	lcd.write("GP2 :198 DP2:2034");
	delay(DELAY_1_SECOND);
	
	lcd.setCursor(3,0);
	lcd.write("Raw Pressures");
	
	lcd.setCursor(0,2);
	lcd.write("GP1 : 20  DP1: 25   ");
	lcd.setCursor(0,3);
	lcd.write("GP2 : 30  DP2: 34   ");
#endif
	return ;
}

void UiMenuMainClass::drawEditScreen5(void){
	
	lcd.setCursor(1,0);
	lcd.write(" O2 Calibration");
	
	lcd.setCursor(1,1);lcd.write("0%");
	lcd.setCursor(7,1);lcd.write("21%");
	lcd.setCursor(14,1);lcd.write("100%");
	
	lcd.setCursor(0,2);lcd.write("11.5");
	lcd.setCursor(6,2);lcd.write("109.7");
	lcd.setCursor(13,2);lcd.write("595.9");
	
	lcd.setCursor(1,3);
	lcd.write((byte)(0x3));
	lcd.setCursor(7,3);
	lcd.write((byte)(0x3));
	lcd.setCursor(14,3);
	lcd.write((byte)(0x3));
	
	lcd.setCursor(19,3);
	lcd.write((byte)(0x5));
	return ;
	
}

void UiMenuMainClass::drawEditScreen6(void){
	
	lcd.setCursor(3,0);
	lcd.write("LCD Contrast");
	
	lcd.setCursor(1,2);
	lcd.write("Value 50%  <50%>");
	lcd.setCursor(14,3);
	lcd.write((byte)(0x3));
	
	lcd.setCursor(19,3);
	lcd.write((byte)(0x5));
	
	return ;
	
}




void UiMenuMainClass::drawRuntimeScreen1(void) {

	drawRuntimeTopBottomLines(runtimeState.currentPosition+1,runtimeState.totalPages);

	if ( runtimeState.paramPerScreen == PARAM_3_VERTICAL ) {
		
		lcd.setCursor(0,1);
		lcd.write("  TV    TVi   TVe ");
		lcd.setCursor(0,2);
		lcd.write(" 400ml 380ml 420ml");

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

void UiMenuMainClass::drawRuntimeScreen3(void) {
	
	drawRuntimeTopBottomLines(runtimeState.currentPosition+1,runtimeState.totalPages);
	
	if ( runtimeState.paramPerScreen == PARAM_3_VERTICAL ) {	
		
		lcd.setCursor(0,1);
		lcd.write(" IER   RR    FiO2 ");
		lcd.setCursor(0,2);
		lcd.write(" 1:3  30bpm   34% ");
		
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

void UiMenuMainClass::drawRuntimeScreen2(void) {
	
	drawRuntimeTopBottomLines(runtimeState.currentPosition+1,runtimeState.totalPages);

	if ( runtimeState.paramPerScreen == PARAM_3_VERTICAL ) {
	
		lcd.setCursor(0,1);
		lcd.write(" PIP  Plat  PEEP ");
		lcd.setCursor(0,2);
		lcd.write(" 42    34    10  ");
		lcd.setCursor(2,3);
		lcd.write("units : cmh2o");
		
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


void UiMenuMainClass::drawRuntimeTopBottomLines(int currentPage, int totalPages) {
	static char buffer[4];
	lcd.setCursor(0,0);
	lcd.write(topBottomLineBuffer);
	//lcd.setCursor(17,0);
	//lcd.write(RIGHT_ARROW_ICON);lcd.write(" ");
	lcd.setCursor(19,0);
	lcd.write(ROTATE_FOR_MORE);
	lcd.setCursor(0,3);
	lcd.write(topBottomLineBuffer);
	//lcd.write(RIGHT_ARROW_ICON);lcd.write(" ");
	lcd.setCursor(19,3);lcd.write(PRESS_TO_EDIT);
	sprintf(buffer,"%d/%d",currentPage, totalPages);
	lcd.setCursor(0,0);lcd.write(buffer);
	
	return;
}

void lookForKeyEvents(void) {
#if 0	
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
#endif	
	return;
}

void testIcons(){
	//	lcd.setCursor(5,0);
	//	lcd.write(GENERIC_NAME1);
	
//	lcd.setCursor(15,0);
//	lcd.write(GENERIC_NAME2);
	
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
