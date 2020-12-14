#ifndef _VENT_INCLUDES_H_
#define _VENT_INCLUDES_H_


#include <LiquidCrystal.h>

// *********************************************************************
// *********************VENT UI ****************************************
// *********************************************************************

//Display
#define DISPLAY_1_PIN       13   // Changed
#define DISPLAY_2_PIN       12   // Changed
#define DISPLAY_3_PIN       11   // Changed
#define DISPLAY_4_PIN       10   // Changed
#define DISPLAY_EN_PIN       42   // Changed
#define DISPLAY_RS_PIN       43   // Changed

#define DISPLAY_BACK_LED_PIN       44   // Changed

//Control Pots
#define TIDAL_VOLUME_PIN   A0      //Unchanged  5
#define RR_PIN             A1     //Unchanged
#define PMAX_PIN           A2     //Unchanged
#define FiO2_PIN           A3     //Unchanged
#define POT_5_PIN     	   A8    // New


// Rotary Encoder Inputs
#define CLK 19
#define DT 18
#define SW 3		//


/// General Defines

#define DELAY_1_SECOND (1000 * 2 )

enum ParameterDisplayFormat {
	PARAM_3_VERTICAL = 0x0,
	PARAM_3_HORIZONTAL,
	PARAM_4_VERTICAL,
	PARAM_4_HORIZONTAL
	};

#define PARAM_PER_SCREEN PARAM_4_VERTICAL //PARAM_3_HORIZONTAL

// *********************************************************************
// ************************* VARIABLES *********************************
// *********************************************************************

extern LiquidCrystal lcd;

#endif // _VENT_INCLUDES_H_
