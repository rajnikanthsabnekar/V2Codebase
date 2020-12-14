
#include "Arduino.h"

// include the library code:
// local includes
#include "UiMenuMain.h"

#define DELAY_HALF_SECOND ( 500 * 2 )

extern UiMenuMainClass UiMenuMain;

LiquidCrystal lcd(DISPLAY_RS_PIN, DISPLAY_EN_PIN, DISPLAY_4_PIN, DISPLAY_3_PIN, DISPLAY_2_PIN, DISPLAY_1_PIN);

void setup() {
  UiMenuMain.init();
  
}

void loop() {  
	
#if 1

	UiMenuMain.clearDisplay();
	
	lcd.setCursor(5,2);
	lcd.write("RUNTIME SCREENS");
	delay(DELAY_HALF_SECOND);
	
	for ( int i = 0 ; i < 1 ; i++ ) {

		UiMenuMain.clearDisplay();
		lcd.setCursor(5,2);
		lcd.write("PATTERN  ");lcd.print(i+1);
		delay(DELAY_HALF_SECOND);
		
		UiMenuMain.runtimeDisplayOptions((ParameterDisplayFormat)(i));

		for (int j =0 ; j < 3; j++ ) {
			UiMenuMain.clearDisplay();
			UiMenuMain.drawRuntimeScreens();
			delay(DELAY_1_SECOND);
		}
	}
	
#endif	
	
#if 1

	UiMenuMain.clearDisplay();
	lcd.setCursor(5,2);
	lcd.write("EDIT SCREENS");
	delay(DELAY_HALF_SECOND);

	for ( int i = 0 ; i < 6 ; i++ ) 
	{
		UiMenuMain.clearDisplay();
		UiMenuMain.drawEditScreens();
	
		delay(DELAY_1_SECOND);
	}
	
#endif

#if 1
	UiMenuMain.clearDisplay();
	UiMenuMain.drawServiceMenuScreen1();
	delay(DELAY_1_SECOND);

	UiMenuMain.clearDisplay();
	UiMenuMain.drawServiceMenuScreen2();
	delay(DELAY_1_SECOND);

	UiMenuMain.clearDisplay();
	UiMenuMain.drawServiceMenuScreen3();
	delay(DELAY_1_SECOND);
	

#endif

#if 1
	UiMenuMain.clearDisplay();

	UiMenuMain.errorScreen(1,1);
#endif
	return;
}

