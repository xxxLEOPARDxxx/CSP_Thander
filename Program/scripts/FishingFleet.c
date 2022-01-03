//#20181030-01
#define MAX_FISH_FLEET_COUNT 8
#define FISHINGFLEET_CHANCE 0.5
#define FISHINGFLEET_DISCOUNT 0.25

void FishingShipCreate(string sIslandID, int nShipCount, int iNation, int ColonyIdx)
{
    int i, iChar, shipType;
    ref sld;
    string sLocatorGroup = "Quest_Ships";
	string sLocator = Island_FindRandomLocator(sIslandID, sLocatorGroup);

    for(i = 0; i < nShipCount; i++)
    {
        iChar = GenerateCharacter(iNation, WITHOUT_SHIP, "soldier", MAN, -1, WARRIOR);
        sld = &characters[iChar];
        switch(rand(15)) {
            case 0: shipType = SHIP_TARTANE; break;
            case 1: shipType = SHIP_TARTANE2; break;
            case 2: shipType = SHIP_CARAVEL20S; break;
            case 3: shipType = SHIP_Boeier; break;
            case 4: shipType = SHIP_Balandra; break;
            case 5: shipType = SHIP_Chaloupe; break;
            case 6: shipType = SHIP_LUGGER; break;
            case 7: shipType = SHIP_KETCH; break;
            case 8: shipType = SHIP_PINK; break;
            case 9: shipType = SHIP_FLEUT; break;
            case 10: shipType = SHIP_BARQUE_L; break;
            case 11: shipType = SHIP_GALEOTH_H; break;
            case 12: shipType = SHIP_BARQUE3; break;
            case 13: shipType = SHIP_BARQUE4; break;
            case 14: shipType = SHIP_BARQUE; break;
            case 15: shipType = SHIP_QuecheIberica; break;
        }
        sld.Ship.Type = GenerateShip(shipType, false);
		SetRandomNameToShip(sld);
		SetBaseShipData(sld);
		SetCrewQuantityFull(sld);
        PlaceFishingShip(iChar, sIslandID, sLocatorGroup, sLocator);
        sld.FishingShips = Colonies[ColonyIdx].id;
        if (iNation == PIRATE)
        {
            sld.nation = NEUTRAL_NATION;
            //sld.AlwaysFriend = true;
            SetCharacterRelationBoth(iChar, GetMainCharacterIndex(), RELATION_FRIEND);
        }
        sld.fishWhisperer = true;
        sld.Ship.Mode = "trade";
        sld.SinkTenPercent = false;
        sld.AnalizeShips = true;
        sld.AlwaysSandbankManeuver = true;
        sld.location.from_sea = colonies[ColonyIdx].from_sea;
        SetCaptanModelByEncType(sld, sld.Ship.Mode);
        Fantom_SetCannons(sld, sld.Ship.Mode);
        SetGoodsInitNull(sld);
        Fantom_SetBallsFishing(sld);
        int iSpace = GetCharacterFreeSpace(sld, GOOD_FISH);
        Fantom_SetCharacterGoods(sld, GOOD_FISH, iSpace);
        Fantom_SetRandomCrewExp(sld, "trade");
        //#20190109-03
        sld.DropFish = true;
    }
}

void PlaceFishingShip(int iChar, string sIslandID, string sLocatorGroup, string sLocator)
{
    //#20190505-01
    string sGroup = "IslandGroup" + iChar;
	Group_DelCharacter(sGroup, characters[iChar].id);
	sGroup = "FishingGroup" + iChar;
	Group_AddCharacter(sGroup, characters[iChar].id);
	Group_SetGroupCommander(sGroup, characters[iChar].id);
	Group_SetAddress(sGroup, sIslandID, sLocatorGroup, sLocator);
	Ship_SetTaskDrift(SECONDARY_TASK, iChar);
}
//#20190109-03
void DropFishingFloats(ref rCharacter)
{
	ref rGood;
	string sGood;

    sGood = Goods[GOOD_FISH].name;

    int iQuantity = 25 + rand(10);
    iQuantity = iQuantity / sti(Goods[GOOD_FISH].Units);

    int iSwimQuantity = rand(iQuantity/4) + rand(iQuantity/4) + rand(iQuantity/4) + rand(iQuantity/4);

    if(iSwimQuantity < 1)
    {
        iSwimQuantity = 1;
    }
    if (CheckAttribute(&Goods[GOOD_FISH], "Swim"))
    {
        float fTime = 2000.0; //stf(Goods[GOOD_FISH].Swim.Time);
        string sModel = Goods[GOOD_FISH].Swim.Model;
        fTime = fTime + (frnd() - 0.5) * fTime / 2.0;
        AISeaGoods_AddGood(rCharacter, sGood, sModel, fTime * 60.0, iSwimQuantity);
    }
}
