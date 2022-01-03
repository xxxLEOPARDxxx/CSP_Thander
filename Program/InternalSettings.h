/*
++++++++++++++ TWEAKS AND SWITCHES FOR MODS ++++++++++++++
In this list you can customize the keyfeatures of the game to your liking.
Or disable certain mods completely.

!!!!!!!!!!!!!! WARNING !!!!!!!!!!!!!!
This is a program file. Changes to the format of the code will mess up the game.
Please follow these rules when editing settings:
- Change ONLY the values after the CAPITAL_SETTING names.
- Use ONLY the values from the explanation below the setting.
- DO NOT replace numbers with "letters", or integer numbers (1) with decimal values (0.75)
- NEVER remove a line starting with "#define".
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

#define MAX_SHIPS_ON_SEA			40			// INT - original value is 32, DO NOT TOUCH THIS

// Crew morale section
#define CREW_PCT_FOR_MORALE			0.02		// FLOAT - morale decreases by 1 for each time crew decreases by this pct. (0.02 = 2 percents)

#define CREW_PCT_FOR_HPDAM			0.02		// FLOAT - morale decreases by 1 for each time shiphp decreases by this pct.

// Combat levels - also, how much decrease in morale
#define COMBATLEVEL_NONE			0.0			// FLOAT - not in combat
#define COMBATLEVEL_ENEMYHERE		0.06		// FLOAT - not in combat but enemy present.
#define COMBATLEVEL_GUNS			0.08		// FLOAT - fired OR RELOADED guns, but has not been hit
#define COMBATLEVEL_HIT				0.3			// FLOAT - has been hit. Note this is increased by crewpct above

// Time delays, in seconds -- how long does the combatlevel last
#define TIME_SINCE_GUNS				120			// INT - (no description)
#define TIME_SINCE_HIT				60			// INT - (no description)

#define MORALE_AMT_COMEBACK			0.5			// FLOAT - amount by which morale goes back towards basemorale each time we update morale

#define RANGE_TO_ENEMY				3000		// INT - in feet/yards/whatever unit the game uses.

#define DIST_NOSHIP					100000.0	// FLOAT - big dist num

#define CLASS_SCALAR_FOR_MORALE 				5.0	// FLOAT - class ratio between killship and deadship is scaled by this before applied as morale bonus to killer.
#define CLASS_SCALAR_FOR_MORALE_OTHER 			1.0	// FLOAT - class ratio between current enemy ship and deadship scaled by this before applied as morale bonus to current enemy ship
#define CLASS_SCALAR_FOR_MORALE_ORIG_TO_OTHER 	0.1	// FLOAT - in addition to above, current enemy ship gets this * the killer ship's morale bonus as well (so if a MoW sees a schooner kill a frigate, they get both the bonus for the frigate death and this * the bonus for the schooner killing it)

#define CHANGE_MORALE_EVERY			5			// INT - change crew morale based on above once per this many ticks. THIS WILL ALSO SCALE MORALE CHANGES! Bigger number, less effect. Should be divisable by 3.

// Surrender adjustments
#define SURR_MAX_MORALE				30			// INT - if morale > this, no surrender check. Scaled to between below two numbers.
#define SURR_MRL_SCL_MAX			1.0			// FLOAT - (no description)
#define SURR_MRL_SCL_MIN			0.2			// FLOAT - (no description)
#define SURR_GROUP				"surrendered"	// STRING - (no description)

float SURR_GLOBAL_SCL = 0.2;
	// Ships will surrender if damage or crew morale become critical
	// 0.0 : Stock PotC, no surrenders
	// 0.01 - 0.5 : The higher that value the faster ships surrender

// Realistic distances for board surrendered ships
#define BOARD_SURR_DISTANCE_MULT	10.0		// FLOAT - Times surrendered ship box size to automatically board

#define BOARD_SURR_CHANCE_MULT	0.5	//float - modifier to surrender chance at boarding.

