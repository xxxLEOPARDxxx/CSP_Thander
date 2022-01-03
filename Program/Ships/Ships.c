#include "ships\ships.h"

extern void InitShips();
extern void InitSailsColors();
extern void InitRandomShipsNames();

string	sRndShpSpName[22], sRndShpEnName[21], sRndShpFrName[12], sRndShpPiName[9], sRndShpHoName[10];

void ShipsInit()
{
	if (LoadSegment("ships\ships_init.c"))
	{
		InitShips();
		UnloadSegment("ships\ships_init.c");
	}

	// init sails color
	if (LoadSegment("ships\sails_init.c"))
	{
		InitSailsColors();
		UnloadSegment("ships\sails_init.c");
	}
}

void SetRandomNameToShip(ref rCharacter)
{
	ref rMassiveOfNames;
	if(!CheckAttribute(rCharacter, "nation"))
	{
		rCharacter.nation = PIRATE;
	}
	if(sti(rCharacter.nation) == -1)
	{
		rCharacter.nation = PIRATE;
	}

	switch (sti(rCharacter.nation))
	{
		case ENGLAND:	makeref(rMassiveOfNames, sRndShpEnName); break;
		case FRANCE:	makeref(rMassiveOfNames, sRndShpFrName); break;
		case SPAIN:		makeref(rMassiveOfNames, sRndShpSpName); break;
		case PIRATE:	makeref(rMassiveOfNames, sRndShpPiName); break;
		case HOLLAND:	makeref(rMassiveOfNames, sRndShpHoName); break;
		makeref(rMassiveOfNames, sRndShpPiName);
	}
	int iMassiveOfNamesSize = GetArraySize(rMassiveOfNames);
    int nRand = rand(iMassiveOfNamesSize-1);
    if (nRand < 0)
        nRand = 0;
    rCharacter.Ship.Name = GetRandSubString(rMassiveOfNames[nRand]);
}

string generateRandomNameToShip(int iNation)
{
	ref rMassiveOfNames;
	switch (iNation)
	{
		case ENGLAND:	makeref(rMassiveOfNames, sRndShpEnName); break;
		case FRANCE:	makeref(rMassiveOfNames, sRndShpFrName); break;
		case SPAIN:		makeref(rMassiveOfNames, sRndShpSpName); break;
		case PIRATE:	makeref(rMassiveOfNames, sRndShpPiName); break;
		case HOLLAND:	makeref(rMassiveOfNames, sRndShpHoName); break;
		makeref(rMassiveOfNames, sRndShpPiName);
	}
	int iMassiveOfNamesSize = GetArraySize(rMassiveOfNames);
    int nRand = rand(iMassiveOfNamesSize-1);
    if (nRand < 0)
        nRand = 0;
    string sName = GetRandSubString(rMassiveOfNames[nRand]);

    return sName;
}

string GetShipLocationID(ref chref)
{
	if(!CheckAttribute(chref,"ship.type"))
	{
		return "";
	}
	int st = sti(chref.ship.type);
	if(st==SHIP_NOTUSED)
	{
		return "";
	}

	int iShipType = sti(RealShips[st].basetype);
	if(ShipsTypes[iShipType].name == "Fort")
	{
		aref ar_FindLoc = FindIslandReloadLocator(chref.location,chref.location.locator);
		if( CheckAttribute(ar_FindLoc,"go") )
		{
			MakeCloneFortBoarding(ar_FindLoc.go); // инитим локацию из разных городов
            return "BOARDING_FORT"; // всегда клоновая локация
		}
		return "";
	}
	// в данный метод на вход всегда идет враг ГГ, метод только на абордаже
	// решаем, что за палуба
	bool bBig1 = (ShipsTypes[iShipType].DeckType == "Big");
	bool bBig2 = (RealShips[sti(pchar.ship.type)].DeckType == "Big");
	bool bMed1 = (ShipsTypes[iShipType].DeckType == "Medium");
	bool bMed2 = (RealShips[sti(pchar.ship.type)].DeckType == "Medium");
	//Boyer change #20170501-01 New Orazio decks
	bool bLineship1 = (ShipsTypes[iShipType].DeckType == "Lineship");
	bool bLineship2 = (RealShips[sti(pchar.ship.type)].DeckType == "Lineship");
	bool bFrigate1 = (ShipsTypes[iShipType].DeckType == "Frigate");
	bool bFrigate2 = (RealShips[sti(pchar.ship.type)].DeckType == "Frigate");

	//Log_SetStringToLog("My deck type: " + RealShips[sti(pchar.ship.type)].DeckType);
	//Log_SetStringToLog("Enemy deck type: " + ShipsTypes[iShipType].DeckType);

	if (bBig1 || bLineship1 || bFrigate1) {
		if (bBig2 || bLineship2 || bFrigate2) {
			return "BOARDING_LNSHP_FRGT_DECK"; // Big VS Big
		} else {
			if (bMed2) {
				return "BOARDING_BIG_DECK"; // Big VS Medium
			} else {
				return "BOARDING_MEDIUM_DECK"; // Big VS Small
			}
		}
	} else {
		if (bMed1) {
			if (bMed2 || bBig2 || bLineship2 || bFrigate2) {
				return "BOARDING_BIG_DECK"; // Medium VS Big & Medium
			} else {
				return "BOARDING_SMALL_DECK"; // Medium VS Small
			}
		} else {
			if (bBig2 || bLineship2 || bFrigate2) {
				return "BOARDING_MEDIUM_DECK"; // Small VS Big
			} else {
				return "BOARDING_SMALL_DECK"; // Small VS Medium & Small
			}
		}
	}
}
// boal
string GetShipCabinID(ref chref)
{

	if(!CheckAttribute(chref,"ship.type"))
	{
		return "";
	}
	int st = sti(chref.ship.type);
	if(st==SHIP_NOTUSED)
	{
		return "";
	}

	int iShipType = sti(RealShips[st].basetype);
	if(ShipsTypes[iShipType].name == "Fort")
	{
		return "";
	}
	if(!CheckAttribute(&RealShips[st],"CabinType"))
	{
		trace("WARNING!!! Ship ("+st+") " + ShipsTypes[st].name + " hav`t attribute CabinType");
		return "";
	}
	return RealShips[st].CabinType;
}
