//Boyer fix #20170301-6

#include "STORE\initGoods.c"
#include "ITEMS\initItems.c"
#include "CANNONS\Cannons_init.c"
#include "characters\Characters_tables.c"
#include "Ships\Ships_init.c"
#include "Ships\Sails_init.c"
#include "Weather\WhrInit.c"
#include "encounters\Encounters_init.c"
#include "STORE\store_init.c"
#include "nations\nations_init.c"
//Boyer fix #20170301-6
//#include "Locations\locations_init.c"
//#include "Locations\locations.c"
#include "colonies\Colonies_init.c"
#include "INTERFACE\perks\perks_init.c"
//#include "Quests\quests.c"
//#include "islands\Islands_init.c"
//#include "WorldMap\worldmap_init.c"

//#include "INTERFACE\shipyard.c"
//#include "scripts\ShipsUtilites.c"

void initReInit(bool bAll)
{
	//Boyer fix...remove from here, put outside function #20170301-6
	/*
	#include "STORE\initGoods.c"
	#include "ITEMS\initItems.c"
	#include "CANNONS\Cannons_init.c"
	#include "characters\Characters_tables.c"
	#include "Ships\Ships_init.c"
	#include "Ships\Sails_init.c"
	#include "Weather\WhrInit.c"
	#include "encounters\Encounters_init.c"
	#include "STORE\store_init.c"
	#include "nations\nations_init.c"
	#include "Locations\locations_init.c"
	#include "colonies\Colonies_init.c"
	#include "INTERFACE\perks\perks_init.c"
	//#include "Quests\quests.c"
	//#include "islands\Islands_init.c"
	//#include "WorldMap\worldmap_init.c"

	//#include "INTERFACE\shipyard.c"
	//#include "scripts\ShipsUtilites.c"
	*/
	//End Boyer fix

Trace("Reinitializing");


//Re-init things that can change via the options screen
	SetArraySize(&Cannon,CANNON_TYPES_QUANTITY)
	InitCannons();
	SetArraySize(&Goods,GOODS_QUANTITY);
	InitGoods();
	SetArraySize(&EncountersTypes,MAX_ENCOUNTER_TYPES);
	InitEncounters();
	SetArraySize(&SailsColors,SAILS_COLOR_QUANTITY);
	InitSailsColors();


if (bAll) {
	//reinit all.  Note this could break some stuff
	//Boyer add #20170301-6
	SetArraySize(&randItemModels,MAX_LOADED_RANDITEMS);
	SetArraySize(&RandItems, RANDITEMS_QUANTITY);
	SetArraySize(&Items,ITEMS_QUANTITY);
	InitItems();
	SetArraySize(&stores,STORE_QUANTITY);
	StoreInit();
	InitCharactersTables();
	SetArraySize(&ShipsTypes, SHIP_TYPES_QUANTITY_WITH_FORT);
	InitShips();
	SetArraySize(&Weathers,MAX_WEATHERS);
	InitWeather();
	InitNations();
	SetArraySize(&Locations,MAX_LOCATIONS);
	InitLocations();
	InitColonies();
	CreateColonyCommanders();
	SetGovenourToCity(ENGLAND, "PortRoyal");
	SetGovenourToCity(SPAIN, "Havana");
	SetGovenourToCity(FRANCE, "Tortuga");
	SetGovenourToCity(HOLLAND, "Villemstad");
	extrnInitPerks();
//	QuestsInit();
//	InitIslands();
//	wdmInitWorldMap();

	ClearAllFantomShips();
	}
}

/*
void ClearAllFantomShips()
{
	int  i;
	ref  chr;
	for (i = 0; i < REAL_SHIPS_QUANTITY; i++)
	{
        DeleteAttribute(&RealShips[i], "lock");
	}
	RealShips[sti(Characters[BOAT_CHARACTER].ship.type)].lock = true;
	for (i = 0; i < MAX_CHARACTERS; i++)
	{
        chr = &Characters[i];
        if (CheckAttribute(chr, "ship.type") && chr.ship.type != SHIP_NOTUSED)
        {
            RealShips[sti(chr.ship.type)].lock = true;
        }
		if (CheckAttribute(chr, "shipyard"))
		{
		    RemoveShipFromShipyard(chr);
		}
	}
	for (i = FANTOM_CHARACTERS; i < TOTAL_CHARACTERS; i++)
	{
        chr = &Characters[i];
        if (CheckAttribute(chr, "ship.type") && chr.ship.type != SHIP_NOTUSED)
        {
            RealShips[sti(chr.ship.type)].lock = true;
        }
	}
	for (i = 0; i < REAL_SHIPS_QUANTITY; i++)
	{
        if (!CheckAttribute(&RealShips[i], "lock") && !CheckAttribute(&RealShips[i], "StoreShip"))
        {
			DeleteAttribute(&RealShips[i], "");
		}
	}
}

void RemoveShipFromShipyard(ref NPChar)
{
        aref   arDest, arImt;
		string sAttr;
		int    iNum, i, iShip;
		makearef(arDest, NPChar.shipyard);
		iNum = GetAttributesNum(arDest);
		for (i = 0; i < iNum; i++)
		{
	    	arImt = GetAttributeN(arDest, i);
	    	iShip = sti(arImt.Type);
	    	DeleteAttribute(&RealShips[iShip], "StoreShip");
	    }
        DeleteAttribute(NPChar, "shipyard");
}

*/


/*
for (int i = 1; i<=14; i++)
{
	AddDataToCurrent(0, 0, 1);
}
*/



/*
	if(LoadSegment("items\initItems.c"))
	{
		InitItems();
		UnloadSegment("items\initItems.c");
	}
	if(LoadSegment("store\initGoods.c"))
	{
		InitGoods();
		UnloadSegment("store\initGoods.c");
	}
*/

/*NEED TO ADD*/
/*
program/characters/RPGUtilite
program/characters/LSC_Q2Utilite

program/DIALOGS
program/text

program/Quests/reaction_functions
program/Quests/quests_reaction

resource/ini/texts/russian/common
resource/ini/texts/russian/herodescribe
resource/ini/texts/russian/itemdescribe
resource/ini/texts/russian/shipdescribe
resource/ini/textus/russian/questbook
*/

/*COMPLETE*/
/*
program/store/initGoods
program/items/initItems
program/CANNONS
program/ships/Ships_init
program/ships/Ships
program/encounters/Encounters_init
program/store
*/

/*DOES NOT APPEAR TO NEED RE-INIT*/
/*

*/
