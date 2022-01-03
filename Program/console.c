#include "locations\locations_init.c"
#include "islands\Islands_init.c"
void ExecuteConsole()
{
	//#include "Ships\Ships_init.c"
	//#include "Locations\init\boarding.c"

	/*
	InitShips(); // Updates ships to have the new cabins - is it really needed?

	// This number is needed to reinit only boarding locations, avoiding unnecessary reinit of all locations
	int n = 631; // If you have "vanilla" ERAS2 v1.5.7 don't change this number, if you added new locations on your own put the number you find in compile.log (see README)

	n = LocationInitBoarding(n); // Updates locations to include the new cabins models

	// Uncomment the next line only if your current ship got the new cabins; you must use the name the ship has in the code (for example SHIP_BRIG3)
	//pchar.Ship.Type = GenerateShip(name_of_your_ship, true);

	case ENGLAND:
            return "eng";
		break;
		case FRANCE:
            return "fra";
		break;
		case SPAIN:
            return "spa";
		break;
		case HOLLAND:
			return "hol";
		break;
		case PIRATE:
			return "pir";
		break;

		#define ENGLAND		0
#define FRANCE		1
#define SPAIN		2
#define HOLLAND		3
#define PIRATE		4
#define PORTUGAL         5
#define PRIVATEER_NATION 8

    pchar.Nation = SPAIN;
    //GiveItem2Character(pchar, "patent_spa");

    AddTitleNextRate(SPAIN, 2);

    if (isReadyToNextTitle(SPAIN))
    {
        Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
        Items[sti(pchar.EquipedPatentId)].TitulCur = sti(Items[sti(pchar.EquipedPatentId)].TitulCur) + 1;
        Log_SetStringToLog("Operation successful!");
    }
    else {
        Log_SetStringToLog("Nope");
    }
    */

    /*
    int 	n, i, idx, iDay;
    ref ch;

    iDay = GetPassengersQuantity(pchar);
    i = 0;
    n = 0;
 	while (i < iDay)
	{
		i++;
		idx = GetPassenger(pchar, n);
		if (idx==-1) break;
		ch = GetCharacter(idx);
			trace("Passenger " + ch.id + " is PGG " + CheckAttribute(ch, "PGGAi.IsPGG") + " type? " + ch.ship.type);
        n++;

	}
    for (i=0; i<COMPANION_MAX; i++)
	{
		idx = GetCompanionIndex(pchar, i);
		if (idx != -1)
		{
            ch = GetCharacter(idx);
            if(ch.id == pchar.id)
                    trace("me");
            else
                trace("companion " + ch.id + " is PGG " + CheckAttribute(ch, "PGGAi.IsPGG") + " type? " + ch.ship.type);
		}
	}
  Log_SetStringToLog("Operation successful!");
    */

    //pchar.ship.type = 100;

    //SurviveSinkingWashAshore();
    //Environment.date.year = 1665;
    //Environment.date.month = 7;
    //Environment.date.day = 3;
    //CannonsInit();
    //ShipsInit();

//ref rRealBloodShip = GetRealShip(sti(pchar.Ship.Type));
    //ref thischr = GetCharacter(GetCharacterIndex("PSHero_78"));

    //thischr.reputation = 30;
    // thischr.PGGAi.ActiveQuest = 1;
//if(LoadSegment("store\initGoods.c"))
		//{
		  //  trace("Done.");
			//InitGoods();
			//UnloadSegment("store\initGoods.c");
		//}

	//ref  ch;
	//ch = characterfromid("PsHero_78");
	//ch.heroparam.herotype = 1;
	//GetCharacter(NPC_GenerateCharacter("PsHero_78", "off_hol_2", "man", "man", 5, PIRATE, -1, true));
    /*ch.PGGAi.HeroNum = 79;
    ch.rank = 10;
    ch.faceid = 430;
    ch.name = "Jean";
    ch.lastname = "Bart";
    ch.Nation = FRANCE;
    ch.PGGAi = true;
    ch.PGGAi.IsPGG = true;
    ch.Ship.Type = SHIP_NOTUSED;
	ch.PGGAi.location.town = "None";
	ch.PGGAi.location = "Dead";
	ch.RebirthPhantom = false;*/
	//ch.reputation = 1;

	//SetNationRelations();

    InitLocations();
    //InitIslands();

    Log_SetStringToLog("Operation successful! ");
}



