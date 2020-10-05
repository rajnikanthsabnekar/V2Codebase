#include "UiMenuMain.h"


// include the library code:
// local includes
#include "UiMenuMain.h"
#include "./encoder/encoder.h"

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
	delay(200);
	
	for ( int i = 0 ; i < 4 ; i++ ) {

		UiMenuMain.clearDisplay();
		lcd.setCursor(5,2);
		lcd.write("PATTERN  ");lcd.print(i+1);
		delay(200);
		
		UiMenuMain.runtimeDisplayOptions((ParameterDisplayFormat)(i));

		for (int j =0 ; j < 3; j++ ) {
			UiMenuMain.clearDisplay();
			UiMenuMain.drawRuntimeScreens();
			delay(500);
		}
	}
	
#endif	
	
#if 1

	UiMenuMain.clearDisplay();
	lcd.setCursor(5,2);
	lcd.write("EDIT SCREENS");
	delay(200);

	for ( int i = 0 ; i < 6 ; i++ ) 
	{
		UiMenuMain.clearDisplay();
		UiMenuMain.drawEditScreens();
	
		delay(500);
	}
	
#endif
	
	return;
}

