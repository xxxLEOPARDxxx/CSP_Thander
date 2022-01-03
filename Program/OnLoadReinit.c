//Boyer mod #20170301-6

void onLoadReInit()
{
	bool reinit = false;
	bool bInitItems = true;
	//#20170625-02 Fix PC ship chest item disappear upon ship/location array reinit
	bool bResetShipChest = false;
	int nCannonSize = GetArraySize(&Cannon);
	int nGoodsSize = GetArraySize(&Goods);
	int nEncounterSize = GetArraySize(&EncountersTypes);
	int nSailSize = GetArraySize(&SailsColors);
	int nItemSize = GetArraySize(&Items);
	int nStoreSize = GetArraySize(&Stores);
	int nShipSize = GetArraySize(&ShipsTypes);
	int nWeatherSize = GetArraySize(&Weathers);
	int nLocationsSize = GetArraySize(&Locations);
	int nIslandsSize = GetArraySize(&Islands);
	int nColonySize = GetArraySize(&Colonies);
	int nRandItemSize = GetArraySize(&RandItems);
	int nRandModelSize = GetArraySize(&randItemModels);
	int nRealShipsSize = GetArraySize(&RealShips);
	//#20190619-01
    object tmpChest;

	//Trace("onLoadReInit Reinitializing");
    //#20190605-02
	setCurrentCabinLocIndex(&tmpChest);

	if(nRealShipsSize != REAL_SHIPS_QUANTITY){
		SetArraySize(&RealShips,REAL_SHIPS_QUANTITY);
	}
	if(nCannonSize != CANNON_TYPES_QUANTITY){
		SetArraySize(&Cannon,CANNON_TYPES_QUANTITY);
		CannonsInit();
	}
	if(nGoodsSize != GOODS_QUANTITY){
		SetArraySize(&Goods,GOODS_QUANTITY);
		//if(LoadSegment("store\initGoods.c"))
		//{
			InitGoods();
			//UnloadSegment("store\initGoods.c");
		//}
	}
	if(nEncounterSize != MAX_ENCOUNTER_TYPES){
		reinit = true;
		SetArraySize(&EncountersTypes,MAX_ENCOUNTER_TYPES);
		EncountersInit();
	}
	if(nSailSize != SAILS_COLOR_QUANTITY){
		SetArraySize(&SailsColors,SAILS_COLOR_QUANTITY);
		if(LoadSegment("Ships\Sails_Init.c"))
		{
			InitSailsColors();
			//UnloadSegment("Ships\Sails_Init.c");
		}
	}

	if (nRandModelSize != MAX_LOADED_RANDITEMS)
		SetArraySize(&randItemModels,MAX_LOADED_RANDITEMS);
	if (nRandItemSize != RANDITEMS_QUANTITY){
		SetArraySize(&RandItems, RANDITEMS_QUANTITY);
		bInitItems = true;
	}
	if (bInitItems || (nItemSize != ITEMS_QUANTITY))
	{
		SetArraySize(&Items,ITEMS_QUANTITY);
		SetArraySize(&itemModels,ITEMS_QUANTITY);
	}
	if(nShipSize  != SHIP_TYPES_QUANTITY_WITH_FORT){
		reinit = true;
		SetArraySize(&ShipsTypes, SHIP_TYPES_QUANTITY_WITH_FORT);
		if (LoadSegment("ships\ships_init.c"))
        {
	    //#20170706-02 Bug fix ship types on ship array resize
            storeOldShipType();
            InitShips();
	    resetRealShipType();
            //UnloadSegment("ships\ships_init.c");
        }
		//ShipsInit();
	}
	if(nWeatherSize != MAX_WEATHERS){
		SetArraySize(&Weathers,MAX_WEATHERS);
		WeatherInit();
	}
	if(nIslandsSize != MAX_ISLANDS){
		reinit = true;
		SetArraySize(&Islands,MAX_ISLANDS);
		IslandsInit();
		if(LoadSegment("WorldMap\worldmap_init.c"))
		{
			wdmInitWorldMap();
			//UnloadSegment("WorldMap\worldmap_init.c");
		}
	}
	if(nLocationsSize != MAX_LOCATIONS){
		reinit = true;
		SetArraySize(&Locations,MAX_LOCATIONS);
		SetArraySize(&Locations,MAX_LOCATIONS);
		LocationInit();
	}
	if(nColonySize != MAX_COLONIES){
		reinit = true;
		SetArraySize(&Colonies,MAX_COLONIES);
		ColoniesInit();
		CreateColonyCommanders();
		SetGovenourToCity(ENGLAND, "PortRoyal");
		SetGovenourToCity(SPAIN, "Havana");
		SetGovenourToCity(FRANCE, "Tortuga");
		SetGovenourToCity(HOLLAND, "Villemstad");
	}
	if(nStoreSize != STORE_QUANTITY){
		SetArraySize(&stores,STORE_QUANTITY);
		if(LoadSegment("store\initStore.c"))
		{
			InitStores();
			//UnloadSegment("store\initStore.c");
		}
	}
	if(reinit){
		if(LoadSegment("characters\Characters_tables.c"))
		{
			InitCharactersTables();
			//UnloadSegment("characters\Characters_tables.c");
		}
		ClearAllFantomShips();
		if(LoadSegment("nations\nations_init.c"))
		{
			InitNations();
			//UnloadSegment("nations\nation_init.c");
		}
		if(LoadSegment("INTERFACE\perks\perks_init.c"))
		{
			extrnInitPerks();
			//UnloadSegment("INTERFACE\perks\perks_init.c");
		}
	}
    fixChurchNightLocks();
	//#20170625-02 Fix PC ship chest item disappear upon ship/location array reinit
	Set_My_Cabin();
	resetCabinMoney(&tmpChest);

	return;
}

//Borrowed from GOF reinit.c
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

//#20170706-01 Bug fix on location array resize, ship cabin items
void setCurrentCabinLocIndex(ref tmpChest)
{
    //From  Set_My_Cabin()
    int nShipType = GetCharacterShipType(pchar);

	if (nShipType != SHIP_NOTUSED)
	{
        pchar.tmpCabinIndex = FindLocation(Pchar.SystemInfo.CabinType);
        //#20190619-01
        storeCabinMoney(tmpChest);
	}
}
//#20190619-01
void storeCabinMoney(ref tmpChest)
{
    //From  Set_My_Cabin()
    int     n,i;
    string  sTemp;
    int nNewLocIndex = -1;

    if(!CheckAttribute(pchar, "SystemInfo.CabinType"))
        return;
    nNewLocIndex = FindLocation(Pchar.SystemInfo.CabinType);

	if (nNewLocIndex > -1)
	{
        ref     loc, locTo;
        aref    arFromBox;
        aref    curItem;
        string  attr;

        loc   = &locations[nNewLocIndex];
        locTo = &tmpChest;
        locTo.box1.money = 0;

        for (n = 1; n <= 4; n++)
        {
            sTemp = "box" + n;

            if(!CheckAttribute(loc, sTemp)) continue;
            if (CheckAttribute(loc, sTemp + ".money"))
            {
                locTo.box1.money = sti(locTo.box1.money) + sti(loc.(sTemp).money);
                if(sti(locTo.box1.money) > 0)
                    locTo.hasItems = true;
            }
            makearef(arFromBox, loc.(sTemp).items);
            for(i=0; i<GetAttributesNum(arFromBox); i++)
            {
                curItem = GetAttributeN(arFromBox, i);
                attr = GetAttributeName(curItem);
                if (attr != "")
                {
                    if (!CheckAttribute(locTo, "box1.items." + attr))
                    {
                        locTo.box1.items.(attr) = 0;
                    }
                    locTo.box1.items.(attr) = makeint(sti(locTo.box1.items.(attr)) + makeint(GetAttributeValue(curItem)));
                    locTo.hasItems = true;
                }
            }
        }
    }
}

void resetCabinMoney(ref tmpChest)
{
    //From  Set_My_Cabin()
    int     n,i;
    string  sTemp;
    int nOldLocIndex = -1;
    int nNewLocIndex = -1;
    bool bNoneFound = true;

    if(!CheckAttribute(pchar, "tmpCabinIndex"))
        return;

    nOldLocIndex = sti(pchar.tmpCabinIndex);
    nNewLocIndex = FindLocation(Pchar.SystemInfo.CabinType);
    DeleteAttribute(pchar, "tmpCabinIndex");

	if (nOldLocIndex > -1 && nNewLocIndex > -1) // && nOldLocIndex != nNewLocIndex)
	{
        ref     loc, locTo;
        aref    arFromBox;
        aref    curItem;
        string  attr;
        bool bHasItems = CheckAttribute(&tmpChest, "hasItems");

        loc   = &locations[nOldLocIndex];
        locTo = &locations[nNewLocIndex];
        //Check for box in old loc
        if(bHasItems) {
            for (n = 1; n <= 4; n++)
            {
                sTemp = "box" + n;

                if(!CheckAttribute(loc, sTemp + ".money")) continue;
                if(!CheckAttribute(loc, sTemp + ".items")) continue;
                bNoneFound = false;
                break;
            }
        }
        else {
            return;
        }
        if(bNoneFound) {
            loc = &tmpChest; //Use temp storage
        }
        else {
            if(nOldLocIndex == nNewLocIndex) return;
        }
        locTo.box1.money = 0;

        for (n = 1; n <= 4; n++)
        {
            sTemp = "box" + n;

            if(!CheckAttribute(loc, sTemp)) continue;
            if (CheckAttribute(loc, sTemp + ".money"))
            {
                locTo.box1.money = sti(locTo.box1.money) + sti(loc.(sTemp).money);
            }
            makearef(arFromBox, loc.(sTemp).items);
            for(i=0; i<GetAttributesNum(arFromBox); i++)
            {
                curItem = GetAttributeN(arFromBox, i);
                attr = GetAttributeName(curItem);
                if (attr != "")
                {
                    if (!CheckAttribute(locTo, "box1.items." + attr))
                    {
                        locTo.box1.items.(attr) = 0;
                    }
                    locTo.box1.items.(attr) = makeint(sti(locTo.box1.items.(attr)) + makeint(GetAttributeValue(curItem)));
                }
            }
            // del
            DeleteAttribute(loc, sTemp + ".items");
            loc.(sTemp).items = "";
            loc.(sTemp) = Items_MakeTime(0, 0, 1, 2003);
            loc.(sTemp).money = 0;
        }
    }
}

//#20170706-02 Bug fix ship type on ship array resize
void storeOldShipType()
{
    int i;
    int nIndex;

    for (i=0; i<REAL_SHIPS_QUANTITY; i++)
	{
	    if(!CheckAttribute(&RealShips[i], "BaseType"))
            continue;
	    nIndex = sti(RealShips[i].BaseType);
	    if(nIndex != SHIP_NOTUSED)
        {
            if(CheckAttribute(&ShipsTypes[nIndex], "Name"))
                RealShips[i].tempBaseID = ShipsTypes[nIndex].Name;
        }
	}
}

void resetRealShipType()
{
    int i;

    for (i=0; i<REAL_SHIPS_QUANTITY; i++)
	{
	    if(CheckAttribute(&RealShips[i], "tempBaseID"))
        {
            RealShips[i].BaseType = GetShipIdxByName(RealShips[i].tempBaseID);
            DeleteAttribute(&RealShips[i], "tempBaseID");
        }
	}
}

int GetShipIdxByName(string shipName)
{
    int idx;

    for (idx=0; idx<SHIP_TYPES_QUANTITY_WITH_FORT; idx++)
    {
        if(CheckAttribute(&ShipsTypes[idx], "Name"))
        {
            if(ShipsTypes[idx].Name == shipName)
                return idx;
        }
    }

    return SHIP_NOTUSED;
}
//#20190909-01
void fixChurchNightLocks()
{
    if(CheckAttribute(pchar, "fix20190909"))
        return;

    pchar.fix20190909 = true;

    int n = FindLocation("SentJons_town");
    if(n > -1) {
        DeleteAttribute(&locations[n], "reload.l7.close_for_night");
        DeleteAttribute(&locations[n], "reload.l71.close_for_night");
    }
    n = FindLocation("PortoBello_town");
    if(n > -1) {
        DeleteAttribute(&locations[n], "reload.l7.close_for_night");
        DeleteAttribute(&locations[n], "reload.l71.close_for_night");
    }
}
