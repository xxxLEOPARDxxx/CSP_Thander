
#define REAL_SHIPS_QUANTITY 900

object	RealShips[REAL_SHIPS_QUANTITY];
#define SAILSCOLOR_PRICE_RATE    0.1
#define SAILSGERALD_PRICE_RATE   0.2

#define SAIL_COST_PERCENT 10
#define HULL_COST_PERCENT 20

ref GetRealShip(int iType)
{
	if(iType >= REAL_SHIPS_QUANTITY)
	{
		trace ("--- Wrong Ship Index. iType is " + iType);
		Log_TestInfo("--- Wrong Ship Index. iType is " + iType);
		return &ShipsTypes[SHIP_TYPES_QUANTITY + 1]; // для отлова
	}
	return &RealShips[iType];
}

// isLock - рудимент, можно выкидывать (26.05.06 boal)
// новая жизнь isLock (04.07.06) теперь это признак ворованности (те цены на верфи)
// если 1 - ворованный, цена копеешная, 0 - честно купленный - можно перепродать.
int GenerateShip(int iBaseType, bool isLock)
{
	int iShip = CreateBaseShip(iBaseType);

	if (iShip == -1)
	{
		return SHIP_NOTUSED;
	}

	ref rRealShip = GetRealShip(iShip);
	ref rBaseShip = GetShipByType(sti(rRealShip.BaseType));
    //Boyer change for ERAS2 #20170318-49
    if(CheckAttribute(rRealShip, "hullNums")) {
        int nHulls = sti(rRealShip.hullNums);
        nHulls -= 1;
        if(nHulls < 0) nHulls = 0;
        rRealShip.ship.upgrades.hull = 1 + rand(nHulls);
        //Trace("Hull nums = " + rRealShip.hullNums);
    }
    else {
        rRealShip.ship.upgrades.hull = 1 + rand(2);
    }
	rRealShip.ship.upgrades.sails = 1 + rand(2);  // только визуальная разница

	switch (rand(1))
	{
		case 0: rRealShip.MastMultiplier = stf(stf(rRealShip.MastMultiplier)-makefloat(0.02*rand(15))); break;
		case 1: rRealShip.MastMultiplier = stf(stf(rRealShip.MastMultiplier)+makefloat(0.02*rand(15))); break;
	}

	if (!CheckAttribute(rRealShip, "isFort"))
	{
	    int iCaliber = sti(rRealShip.MaxCaliber);
	    if (sti(rRealShip.Class) != 7)
	    {  // чтоб не было баркаса с 16ф
		    switch(iCaliber)
		    {
                case 8:
					iCaliber = 0;
				break;
				case 12:
					iCaliber = 1;
				break;
				case 16:
					iCaliber = 2;
				break;
				case 20:
					iCaliber = 3;
				break;
				case 24:
					iCaliber = 4;
				break;
				case 32:
					iCaliber = 5;
				break;
				case 36:
					iCaliber = 6;
				break;
				case 42:
					iCaliber = 7;
				break;
		    }
			//iCaliber = iCaliber - rand(1);
		    iCaliber = iCaliber; //Jason: согласно новой системе орудий калибр должен быть постоянен, но пока поставим рандом на единицу меньше, а больше - нельзя по определению, на рез. тестов решим, фиксировать или рандомить
		    if (iCaliber < 0) iCaliber = 0;
		    if (sti(rRealShip.Class) == 1)
		    {
		    	if (iCaliber > 7) iCaliber = 7;
		    }
		    else
		    {
		    	if (iCaliber > 6) iCaliber = 6;
		    }
		    switch(iCaliber)
		    {
                case 0:
					iCaliber = 8;
				break;
				case 1:
					iCaliber = 12;
				break;
				case 2:
					iCaliber = 16;
				break;
				case 3:
					iCaliber = 20;
				break;
				case 4:
					iCaliber = 24;
				break;
				case 5:
					iCaliber = 32;
				break;
				case 6:
					iCaliber = 36;
				break;
				case 7:
					iCaliber = 42;
				break;
		    }
		    rRealShip.MaxCaliber = iCaliber;
	    }
	    rRealShip.SpeedRate	       = stf(rRealShip.SpeedRate) + frandSmall(stf(rRealShip.SpeedRate) / 5.0) - stf(rRealShip.SpeedRate) / 10.0;
	    rRealShip.TurnRate         = stf(rRealShip.TurnRate) + frandSmall(stf(rRealShip.TurnRate) / 5.0) - stf(rRealShip.TurnRate) / 10.0;
	    //rRealShip.Price            = sti(rRealShip.Price) + rand(makeint(sti(rRealShip.Price)/2)) - makeint(sti(rRealShip.Price)/4);
	    rRealShip.HP               = sti(rRealShip.HP) + rand(makeint(sti(rRealShip.HP)/5)) - makeint(sti(rRealShip.HP)/10);
	    rRealShip.WindAgainstSpeed = stf(rRealShip.WindAgainstSpeed) + frandSmall(stf(rRealShip.WindAgainstSpeed)/5.0) - stf(rRealShip.WindAgainstSpeed)/10.0;
	}
    rRealShip.Capacity        = sti(rRealShip.Capacity) + rand(makeint(sti(rRealShip.Capacity)/4)) - makeint(sti(rRealShip.Capacity)/8);
    rRealShip.OptCrew         = makeint(sti(rRealShip.OptCrew) + rand(makeint(sti(rRealShip.OptCrew)/3)) - makeint(sti(rRealShip.OptCrew)/6));
    rRealShip.MaxCrew         = makeint(sti(rRealShip.OptCrew) * 1.25 + 0.5);  // 25 процентов перегруза
    rRealShip.MinCrew         = makeint(sti(rRealShip.MinCrew) + rand(makeint(sti(rRealShip.MinCrew)/3)) - makeint(sti(rRealShip.MinCrew)/6));

	rRealShip.Weight		  = sti(rRealShip.Weight) + rand(sti(rRealShip.Weight)/20) - rand(sti(rRealShip.Weight)/20);

	// to_do del -->
	rRealShip.BoardingCrew    = 0;
	rRealShip.GunnerCrew      = 0;
	rRealShip.CannonerCrew    = 0;
	rRealShip.SailorCrew      = sti(rRealShip.OptCrew);
    // to_do del <--

	int iDiffWeight			= sti(rRealShip.Weight) - sti(rBaseShip.Weight);
	int iDiffCapacity		= sti(rRealShip.Capacity) - sti(rBaseShip.Capacity);
	int iDiffMaxCrew		= sti(rRealShip.MaxCrew) - sti(rBaseShip.MaxCrew);
	int iDiffMinCrew		= sti(rRealShip.MinCrew) - sti(rBaseShip.MinCrew);
	float fDiffSpeedRate	= stf(rRealShip.SpeedRate) - stf(rBaseShip.SpeedRate);
	int iDiffTurnRate		= sti(rRealShip.TurnRate) - sti(rBaseShip.TurnRate);
	int iDiffHP	    		= sti(rRealShip.HP) - sti(rBaseShip.HP);

	rRealShip.Price	= GetShipPriceByTTH(iShip, &NullCharacter); //(iDiffWeight + iDiffCapacity + iDiffMaxCrew*2 + iDiffMinCrew + fDiffSpeedRate*2 + iDiffTurnRate*2 + iDiffHP)*5 + sti(rRealShip.Price);

	if (sti(rRealShip.Price) <= 0) rRealShip.Price = 100;

	rRealShip.Stolen = isLock;  // ворованность

	return iShip;
}

// -> added by ugeen 25.01.09 (на основе GenerateShip(.....)) - рандомизируем кол-во стволов на борту
// 31.01.09 - добавил бонусы к корабельным статам если кол-во орудий на борту < базового
int GenerateShipExt(int iBaseType, bool isLock, ref chr)
{
	string  attr, sCity;
	int 	i;
	aref 	refShip;
	float	Кdckyrd = 1.0;
	bool	isShipyard = false;

	int iShip = CreateBaseShip(iBaseType);

	if (iShip == -1)
	{
		return SHIP_NOTUSED;
	}

	ref rRealShip = GetRealShip(iShip);
	ref rBaseShip = GetShipByType(sti(rRealShip.BaseType));
	//Boyer change for ERAS2 #20170318-49
    if(CheckAttribute(rRealShip, "hullNums")) {
        int nHulls = sti(rRealShip.hullNums);
        nHulls -= 1;
        if(nHulls < 0) nHulls = 0;
        rRealShip.ship.upgrades.hull = 1 + rand(nHulls);
        //Trace("Hull nums = " + rRealShip.hullNums);
    }
    else {
        rRealShip.ship.upgrades.hull = 1 + rand(2);
    }
	rRealShip.ship.upgrades.sails = 1 + rand(2);  // только визуальная разница
	switch (rand(1))
	{
		case 0: rRealShip.MastMultiplier = stf(stf(rRealShip.MastMultiplier)-makefloat(0.02*rand(15))); break;
		case 1: rRealShip.MastMultiplier = stf(stf(rRealShip.MastMultiplier)+makefloat(0.02*rand(15))); break;
	}

	// ugeen --> если кораблик генерится на верфи, разброс статов более узкий
	if (CheckAttribute(chr, "City"))
	{
		sCity = chr.City;
		if(CheckCharacterID(chr, sCity + "_shipyarder"))
		{
			Кdckyrd 	= 0.8;
			isShipyard 	= true;
		}
	}
	// ugeen

	if (!CheckAttribute(rRealShip, "isFort"))
	{
		int iCaliber = sti(rRealShip.MaxCaliber);
		if (sti(rRealShip.Class) != 7 && !CheckAttribute(rRealShip, "QuestShip"))
		{  // чтоб не было баркаса с 16ф
			switch(iCaliber)
			{
				case 8:
					iCaliber = 0;
				break;
				case 12:
					iCaliber = 1;
				break;
				case 16:
					iCaliber = 2;
				break;
				case 20:
					iCaliber = 3;
				break;
				case 24:
					iCaliber = 4;
				break;
				case 32:
					iCaliber = 5;
				break;
				case 36:
					iCaliber = 6;
				break;
				case 42:
					iCaliber = 7;
				break;
			}
			//iCaliber = iCaliber - rand(1);
			iCaliber = iCaliber; //Jason: согласно новой системе орудий калибр должен быть постоянен, но пока поставим рандом на единицу меньше, а больше - нельзя по определению, на рез. тестов решим, фиксировать или рандомить
			if (iCaliber < 0) iCaliber = 0;
			if (sti(rRealShip.Class) == 1)
			{
				if (iCaliber > 7) iCaliber = 7;
			}
			else
			{
				if (iCaliber > 6) iCaliber = 6;
			}
			switch(iCaliber)
			{
				case 0:
					iCaliber = 8;
				break;
				case 1:
					iCaliber = 12;
				break;
				case 2:
					iCaliber = 16;
				break;
				case 3:
					iCaliber = 20;
				break;
				case 4:
					iCaliber = 24;
				break;
				case 5:
					iCaliber = 32;
				break;
				case 6:
					iCaliber = 36;
				break;
				case 7:
					iCaliber = 42;
				break;
			}
			rRealShip.MaxCaliber = iCaliber;
		}

		int   iCannonDiff 		= 0;
		int   iDiffClass  		= 5 - makeint(sti(rRealShip.Class)/2);

		switch(rRealShip.BaseName)
		{
			// 7-й класс
			case "WAR_TARTANE":
				iCannonDiff = rand(1);  // 8, 6
			break;
			case "BERMSLOOP":
				iCannonDiff = rand(1);  // 8, 6
			break;
			case "EMPRESS":
				iCannonDiff = rand(1);  // 10, 8
			break;
			case "PINK":
				iCannonDiff = rand(1);  // 12, 10
			break;
			case "LUGGER":
				iCannonDiff = rand(1);  // 12, 10
			break;
			case "LUGGER_H":
				iCannonDiff = rand(1);  // 12, 10
			break;

			// 6-й класс
			case "SPEEDY":
				iCannonDiff = rand(2);  // 14, 12, 10
			break;
			case "FR_SLOOP":
				iCannonDiff = rand(2);  // 14, 12, 10
			break;
			case "POLACCA":
				iCannonDiff = rand(2);  // 14, 12, 10
			break;
			case "SLOOP":
				iCannonDiff = rand(2);  // 16, 14, 12
			break;
			case "GALEOTH_H":
				iCannonDiff = rand(2);  // 16, 14, 12
			break;
			case "DERFFLINGER":
				iCannonDiff = rand(2);  // 16, 14, 12
			break;
			case "BARQUE":
				iCannonDiff = rand(2);  // 16, 14, 12
			break;
			case "NEPTUNUS":
				iCannonDiff = rand(2);  // 16, 14, 12
			break;
			case "CASTELF":
				iCannonDiff = rand(2);  // 16, 14, 12
			break;
			case "BARKENTINE":
				iCannonDiff = rand(2);  // 16, 14, 12
			break;
			case "BRIGANTINE":
				iCannonDiff = rand(2);  // 16, 14, 12
			break;
			case "BRIG":
				iCannonDiff = rand(2);  // 16, 14, 12
			break;
			case "BRIGHEAVY":
				iCannonDiff = rand(2);  // 16, 14, 12
			break;
			case "SLOOP_B":
				iCannonDiff = rand(2);  // 16, 14, 12
			break;
			case "PINNACE":
				iCannonDiff = rand(2);  // 18, 16, 14
			break;
			case "SOPHIE":
				iCannonDiff = rand(2);  // 18, 16, 14
			break;
			case "FLEUT":
				iCannonDiff = rand(2);  // 18, 16, 14
			break;
			case "INTERCEPTOR":
				iCannonDiff = rand(2);  // 18, 16, 14
			break;

			// 5-й класс
			case "FR_POSTILLIONEN":
				iCannonDiff = rand(2);  // 20, 18, 16
			break;
			case "SCHOONER":
				iCannonDiff = rand(2);  // 20, 18, 16
			break;
			case "COLONIALSCHOONER":
				iCannonDiff = rand(2);  // 20, 18, 16
			break;
			case "DUTCHPINNACE":
				iCannonDiff = rand(2);  // 20, 18, 16
			break;
			case "PO_FLEUT50":
				iCannonDiff = rand(2);  // 20, 18, 16
			break;
			case "GALEON_L":
				iCannonDiff = rand(2);  // 20, 18, 16
			break;
			case "XEBEC":
				iCannonDiff = rand(2);  // 20, 18, 16
			break;
			case "BATTLEXEBEC":
				iCannonDiff = rand(2);  // 20, 18, 16
			break;
			case "SCHOONERLIGHT":
				iCannonDiff = rand(2);  // 22, 20, 18
			break;
			case "SHNYAVA":
				iCannonDiff = rand(2);  // 22, 20, 18
			break;
			case "POLACRE":
				iCannonDiff = rand(2);  // 22, 20, 18
			break;
			case "XEBECLIGHT":
				iCannonDiff = rand(2);  // 22, 20, 18
			break;
			case "ENSLAVER":
				iCannonDiff = rand(2);  // 22, 20, 18
			break;
			case "GREYHOUND":
				iCannonDiff = rand(2);  // 22, 20, 18
			break;
			case "CORVETTELIGHT":
				iCannonDiff = rand(2);  // 22, 20, 18
			break;
			case "PACKET_BRIG":
				iCannonDiff = rand(2);  // 22, 20, 18
			break;
			case "MIRAGE":
				iCannonDiff = rand(2);  // 22, 20, 18
			break;
			case "PDN":
				iCannonDiff = rand(2);  // 24, 22, 20
			break;
			case "ENTERPRISE":
				iCannonDiff = rand(2);  // 24, 22, 20
			break;
			case "POLACRE_H":
				iCannonDiff = rand(2);  // 24, 22, 20
			break;

			// 4-й класс
			case "CRIMSONBLOOD":
				iCannonDiff = rand(3);  // 30, 28, 26, 24
			break;
			case "XEBEKVT":
				iCannonDiff = rand(3);  // 30, 28, 26, 24
			break;
			case "FELIPE":
				iCannonDiff = rand(3);  // 30, 28, 26, 24
			break;
			case "PINNACELIGHT":
				iCannonDiff = rand(3);  // 30, 28, 26, 24
			break;
			case "CARAVEL":
				iCannonDiff = rand(3);  // 30, 28, 26, 24
			break;
			case "FRIGATEMEDIUM":
				iCannonDiff = rand(3);  // 30, 28, 26, 24
			break;
			case "CARAVEL2":
				iCannonDiff = rand(3);  // 32, 30, 28, 26
			break;
			case "CORVETTE":
				iCannonDiff = rand(3);  // 32, 30, 28, 26
			break;
			case "FRIGATE_l":
				iCannonDiff = rand(3);  // 32, 30, 28, 26
			break;
			case "BLACKANGEL":
				iCannonDiff = rand(3);  // 32, 30, 28, 26
			break;
			case "BATTLECORVETTE":
				iCannonDiff = rand(3);  // 32, 30, 28, 26
			break;
			case "COASTALFRIGATE":
				iCannonDiff = rand(3);  // 32, 30, 28, 26
			break;
			case "RAAFRIGATE":
				iCannonDiff = rand(3);  // 32, 30, 28, 26
			break;
			case "FLEUTWAR":
				iCannonDiff = rand(3);  // 34, 32, 30, 28
			break;
			case "FLEUTWARSAT":
				iCannonDiff = rand(3);  // 34, 32, 30, 28
			break;
			case "GALEONTRADER":
				iCannonDiff = rand(3);  // 34, 32, 30, 28
			break;
			case "JAMAICASHIP":
				iCannonDiff = rand(3);  // 36, 34, 32, 30
			break;
			case "LYDIA":
				iCannonDiff = rand(3);  // 36, 34, 32, 30
			break;
			case "THEBLACKPEARL":
				iCannonDiff = rand(3);  // 36, 34, 32, 30
			break;
			case "FR_FRIGATE":
				iCannonDiff = rand(3);  // 36, 34, 32, 30
			break;
			case "GALEON_H":
				iCannonDiff = rand(3);  // 36, 34, 32, 30
			break;
			case "GALEON1":
				iCannonDiff = rand(3);  // 38, 36, 34, 32
			break;
			case "LA_MARIANNA":
				iCannonDiff = rand(3);  // 38, 36, 34, 32
			break;
			case "PIRATFASTGAL":
				iCannonDiff = rand(3);  // 38, 36, 34, 32
			break;
			case "UNICORN":
				iCannonDiff = rand(3);  // 38, 36, 34, 32
			break;

			// 3-й класс
			case "REVENGE":
				iCannonDiff = rand(3);  // 40, 38, 36, 34
			break;
			case "GALEON50":
				iCannonDiff = rand(3);  // 40, 38, 36, 34
			break;
			case "LINEFRIGATE":
				iCannonDiff = rand(3);  // 40, 38, 36, 34
			break;
			case "LIGHTFRIGATE":
				iCannonDiff = rand(3);  // 40, 38, 36, 34
			break;
			case "BOUSSOLE":
				iCannonDiff = rand(3);  // 42, 40, 38, 36
			break;
			case "FASTFRIGATE":
				iCannonDiff = rand(3);  // 42, 40, 38, 36
			break;
			case "SURPRISE":
				iCannonDiff = rand(3);  // 42, 40, 38, 36
			break;
			case "SALAMANDER":
				iCannonDiff = rand(3);  // 44, 42, 40, 38
			break;
			case "FRIGATE_SAT":
				iCannonDiff = rand(3);  // 44, 42, 40, 38
			break;
			case "BATTLEFRIGATE":
				iCannonDiff = rand(3);  // 44, 42, 40, 38
			break;
			case "NIGHTMARE":
				iCannonDiff = rand(3);  // 44, 42, 40, 38
			break;
			case "FRIGATE":
				iCannonDiff = rand(3);  // 46, 44, 42, 40
			break;
			case "FR_ESSEX":
				iCannonDiff = rand(3);  // 46, 44, 42, 40
			break;
			case "MORDAUNT":
				iCannonDiff = rand(3);  // 46, 44, 42, 40
			break;
			case "FRIGATE_H":
				iCannonDiff = rand(4);  // 50, 48, 46, 44, 42
			break;
			case "AMSTERDAM":
				iCannonDiff = rand(4);  // 50, 48, 46, 44, 42
			break;
			case "WARGALLEON2":
				iCannonDiff = rand(4);  // 52, 50, 48, 46, 44
			break;
			case "NL_PINNACEOFWAR47":
				iCannonDiff = rand(4);  // 54, 52, 50, 48, 46
			break;
			case "HOLLGALEON_H":
				iCannonDiff = rand(4);  // 54, 52, 50, 48, 46
			break;
			case "CARRACA":
				iCannonDiff = rand(4);  // 56, 54, 52, 50, 48
			break;
			case "CONSTITUTION":
				iCannonDiff = rand(4);  // 56, 54, 52, 50, 48
			break;
			case "FEARLESS":
				iCannonDiff = rand(4);  // 56, 54, 52, 50, 48
			break;
			case "NL_FWZP":
				iCannonDiff = rand(4);  // 56, 54, 52, 50, 48
			break;
			case "LINESHIP":
				iCannonDiff = rand(4);  // 56, 54, 52, 50, 48
			break;
			case "OXFORD":
				iCannonDiff = rand(4);  // 58, 56, 54, 52, 50
			break;

			// 2-й класс
			case "DUTCHLINESHIP":
				iCannonDiff = rand(4);  // 60, 58, 56, 54, 52
			break;
			case "DUTCHSHIP":
				iCannonDiff = rand(4);  // 60, 58, 56, 54, 52
			break;
			case "NL_CONVOISHIP":
				iCannonDiff = rand(4);  // 60, 58, 56, 54, 52
			break;
			case "COURONNE":
				iCannonDiff = rand(4);  // 64, 62, 60, 58, 56
			break;
			case "ALEXIS":
				iCannonDiff = rand(4);  // 64, 62, 60, 58, 56
			break;
			case "LINESHIPHEAVY":
				iCannonDiff = rand(4);  // 64, 62, 60, 58, 56
			break;
			case "WARSHIP":
				iCannonDiff = rand(4);  // 66, 64, 62, 60, 58
			break;
			case "POSEIDON":
				iCannonDiff = rand(4);  // 66, 64, 62, 60, 58
			break;
			case "HMS_CENTURION":
				iCannonDiff = rand(4);  // 68, 66, 64, 62, 60
			break;
			case "RESOLUTION":
				iCannonDiff = rand(4);  // 70, 68, 66, 64, 62
			break;
			case "FR_SUPERIORWARSHIP1":
				iCannonDiff = rand(4);  // 74, 72, 70, 68, 66
			break;
			case "HEAVYWARSHIP":
				iCannonDiff = rand(4);  // 74, 72, 70, 68, 66
			break;
			case "LINK":
				iCannonDiff = rand(4);  // 78, 76, 74, 72, 70
			break;
			case "SUPERBE":
				iCannonDiff = rand(4);  // 78, 76, 74, 72, 70
			break;

			// 1-й класс
			case "BATTLESHIP":
				iCannonDiff = rand(5);  // 80, 78, 76, 74, 72, 70
			break;
			case "HEAVYLINESHIP":
				iCannonDiff = rand(5);  // 82, 80, 78, 76, 74, 72
			break;
			case "LINK2":
				iCannonDiff = rand(5);  // 84, 82, 80, 78, 76, 74
			break;
			case "BELLONA":
				iCannonDiff = rand(5);  // 84, 82, 80, 78, 76, 74
			break;
			case "LINEARSHIP":
				iCannonDiff = rand(5);  // 84, 82, 80, 78, 76, 74
			break;
			case "SHARK":
				iCannonDiff = rand(5);  // 84, 82, 80, 78, 76, 74
			break;
			case "ZEVENPROVINCIEN":
				iCannonDiff = rand(5);  // 92, 90, 88, 86, 84, 82
			break;
			case "FR_TRINITY":
				iCannonDiff = rand(5);  // 96, 94, 92, 90, 88, 86
			break;
			case "MANOWAR_FAST":
				iCannonDiff = rand(5);  // 100, 98, 96, 94, 92, 90
			break;
			case "BATTLEMANOWAR":
				iCannonDiff = rand(5);  // 100, 98, 96, 94, 92, 90
			break;
			case "MANOWAR_GUB":
				iCannonDiff = rand(5);  // 100, 98, 96, 94, 92, 90
			break;
			case "PRINCE":
				iCannonDiff = rand(5);  // 102, 100, 98, 96, 94, 92
			break;
			case "MANOWAR":
				iCannonDiff = rand(5);  // 102, 100, 98, 96, 94, 92
			break;
			case "HMS_VICTORY":
				iCannonDiff = rand(5);  // 104, 102, 100, 98, 96, 94
			break;
			case "SP_SANFELIPE":
				iCannonDiff = rand(5);  // 108, 106, 104, 102, 100, 98
			break;

			//стволы на квестовых  шипах тоже генерим рандомно
			case "SoleyRu":
				iCannonDiff = rand(5);  // 112, 110, 108,106,104,102
			break;
			case "BrigQeen":
				iCannonDiff = rand(2);  // 24, 22, 20
			break;
			case "BrigSW":
				iCannonDiff = rand(2);  // 24, 22, 20
			break;
			case "XebekVML":
				iCannonDiff = rand(2);  // 22, 20, 18
			break;
			case "Clipper":
				iCannonDiff = rand(3);  // 38, 36, 34, 32
			break;
			case "Corvette_quest":
				iCannonDiff = rand(3);  // 40, 38, 36, 34
			break;
			case "Wh_corvette_quest":
				iCannonDiff = rand(3);  // 40, 38, 36, 34
			break;
			case "ArabellaShip":
				iCannonDiff = rand(3);  // 52, 50, 48, 46
			break;
			case "Flyingdutchman":
				iCannonDiff = rand(4);  // 60, 58, 56, 54, 52
			break;
			case "Catherine":
				iCannonDiff = rand(4);  // 60, 58, 56, 54, 52
			break;
		}
		if(CheckAttribute(rRealShip, "QuestShip") || isShipyard) iCannonDiff = 0;

		// if(rRealShip.BaseName == "FrigateQueen") iCannonDiff = 2; // делаем фрегат "Королева" 48-и пушечным

		// собственно сам рэндом стволов
		makearef(refShip, chr.Ship);
		ResetShipCannonsDamages(chr);

		if (!CheckAttribute(refShip,"soiling"))
		{
			refShip.soiling = 0;
		}

		// куда-нить запишем максимально возможное кол-во орудий (потом нужно будет, если захотим проапгрейдиться на этот счет)
		rRealShip.CannonsQuantityMax = sti(rRealShip.CannonsQuantity);
		// принципиальный момент ! нужно нулить обязательно левые стволы !
		for (i = 0; i < sti(rRealShip.rcannon); i++)
		{
			attr = "c" + i;
			rRealShip.Cannons.Borts.cannonr.damages.(attr) = 1.0;
			rRealShip.Cannons.Borts.cannonl.damages.(attr) = 1.0;
			rRealShip.Cannons.Borts.rcannon.damages.(attr) = 1.0;
			rRealShip.Cannons.Borts.lcannon.damages.(attr) = 1.0;

			refShip.Cannons.Borts.cannonr.damages.(attr) = 1.0;
			refShip.Cannons.Borts.cannonl.damages.(attr) = 1.0;
			refShip.Cannons.Borts.rcannon.damages.(attr) = 1.0;
			refShip.Cannons.Borts.lcannon.damages.(attr) = 1.0;
		}

		rRealShip.rcannon = sti(rRealShip.rcannon) - iCannonDiff;
		rRealShip.lcannon = sti(rRealShip.lcannon) - iCannonDiff;

		rRealShip.cannonr = sti(rRealShip.rcannon);
		rRealShip.cannonl = sti(rRealShip.lcannon);
		rRealShip.cannonf = sti(rRealShip.fcannon);
		rRealShip.cannonb = sti(rRealShip.bcannon);

		rRealShip.Cannons = sti(rRealShip.CannonsQuantityMax) - iCannonDiff * 2;
		rRealShip.CannonsQuantity = sti(rRealShip.Cannons);

		//а теперь вертаем стволы обратно в потребном нам количестве
		for (i = 0; i < sti(rRealShip.rcannon); i++)
		{
			attr = "c" + i;
			rRealShip.Cannons.borts.cannonr.damages.(attr) = 0.0;
			rRealShip.Cannons.borts.cannonl.damages.(attr) = 0.0;
			rRealShip.Cannons.borts.rcannon.damages.(attr) = 0.0;
			rRealShip.Cannons.borts.lcannon.damages.(attr) = 0.0;

			refShip.Cannons.borts.cannonr.damages.(attr) = 0.0;
			refShip.Cannons.borts.cannonl.damages.(attr) = 0.0;
			refShip.Cannons.borts.rcannon.damages.(attr) = 0.0;
			refShip.Cannons.borts.lcannon.damages.(attr) = 0.0;
		}

		for (i = 0; i < sti(rRealShip.fcannon); i++)
		{
			attr = "c" + i;
			rRealShip.Cannons.borts.cannonf.damages.(attr) = 0.0;
			rRealShip.Cannons.borts.fcannon.damages.(attr) = 0.0;
			refShip.Cannons.borts.cannonf.damages.(attr) = 0.0;
			refShip.Cannons.borts.fcannon.damages.(attr) = 0.0;
		}

		for (i = 0; i < sti(rRealShip.bcannon); i++)
		{
			attr = "c" + i;
			rRealShip.Cannons.borts.cannonb.damages.(attr) = 0.0;
			rRealShip.Cannons.borts.bcannon.damages.(attr) = 0.0;
			refShip.Cannons.borts.cannonb.damages.(attr) = 0.0;
			refShip.Cannons.borts.bcannon.damages.(attr) = 0.0;
		}

		refShip.Cannons.Borts.cannonl = sti(rRealShip.lcannon);
		refShip.Cannons.Borts.cannonr = sti(rRealShip.rcannon);
		refShip.Cannons.Borts.cannonf = sti(rRealShip.fcannon);
		refShip.Cannons.Borts.cannonb = sti(rRealShip.bcannon);

		refShip.Cannons.Borts.lcannon = sti(rRealShip.lcannon);
		refShip.Cannons.Borts.rcannon = sti(rRealShip.rcannon);
		refShip.Cannons.Borts.fcannon = sti(rRealShip.fcannon);
		refShip.Cannons.Borts.bcannon = sti(rRealShip.bcannon);

		refShip.Cannons = sti(rRealShip.Cannons);
		// <-- рэндом стволов

		rRealShip.Bonus_Capacity 	= 0;
		rRealShip.Bonus_HP			= 0;
		rRealShip.Bonus_SpeedRate   = 0.0;
		rRealShip.Bonus_TurnRate	= 0.0;

		if(!CheckAttribute(rRealShip, "QuestShip"))
		{
			rRealShip.Bonus_Capacity 	= makeint((sti(rRealShip.Capacity)*iCannonDiff)/(15 * iDiffClass));
			rRealShip.Bonus_HP 			= makeint((sti(rRealShip.HP)*iCannonDiff)/(15 * iDiffClass));
			rRealShip.Bonus_SpeedRate   = (stf(rRealShip.SpeedRate)*iCannonDiff)/(15 * iDiffClass);
			rRealShip.Bonus_TurnRate    = (stf(rRealShip.TurnRate)*iCannonDiff)/(15 * iDiffClass);

			rRealShip.SpeedRate	   		= stf(rRealShip.SpeedRate) + Кdckyrd * (frandSmall(stf(rRealShip.SpeedRate) / 5.0) - stf(rRealShip.SpeedRate) / 10.0);
			rRealShip.TurnRate         	= stf(rRealShip.TurnRate) + Кdckyrd * (frandSmall(stf(rRealShip.TurnRate) / 5.0) - stf(rRealShip.TurnRate) / 10.0);
			//rRealShip.Price            = sti(rRealShip.Price) + rand(makeint(sti(rRealShip.Price)/2)) - makeint(sti(rRealShip.Price)/4);
			rRealShip.HP               	= sti(rRealShip.HP) + makeint(Кdckyrd * (rand(makeint(sti(rRealShip.HP)/5)) - makeint(sti(rRealShip.HP)/10)));
			rRealShip.WindAgainstSpeed 	= stf(rRealShip.WindAgainstSpeed) + Кdckyrd * (frandSmall(stf(rRealShip.WindAgainstSpeed)/5.0) - stf(rRealShip.WindAgainstSpeed)/10.0);
		}
	}

	if(!CheckAttribute(rRealShip, "QuestShip"))
	{
		rRealShip.Capacity        = sti(rRealShip.Capacity) + makeint(Кdckyrd * (rand(makeint(sti(rRealShip.Capacity)/4)) - makeint(sti(rRealShip.Capacity)/8)));
		rRealShip.OptCrew         = makeint(sti(rRealShip.OptCrew) + Кdckyrd * (rand(makeint(sti(rRealShip.OptCrew)/3)) - makeint(sti(rRealShip.OptCrew)/6)));
		rRealShip.MaxCrew         = makeint(sti(rRealShip.OptCrew) * 1.25 + 0.5);  // 25 процентов перегруза
		rRealShip.MinCrew         = makeint(sti(rRealShip.MinCrew) + Кdckyrd * (rand(makeint(sti(rRealShip.MinCrew)/3)) - makeint(sti(rRealShip.MinCrew)/6)));
		rRealShip.Weight		  = sti(rRealShip.Weight) + makeint(Кdckyrd * (rand(sti(rRealShip.Weight)/20) - rand(sti(rRealShip.Weight)/20)));
	}

	// to_do del -->
	rRealShip.BoardingCrew    = 0;
	rRealShip.GunnerCrew      = 0;
	rRealShip.CannonerCrew    = 0;
	rRealShip.SailorCrew      = sti(rRealShip.OptCrew);
	// to_do del <--

	if(!CheckAttribute(rRealShip, "QuestShip"))
	{
		if(CheckAttribute(rRealShip, "Bonus_Capacity"))	rRealShip.Capacity = sti(rRealShip.Capacity) + sti(rRealShip.Bonus_Capacity);
		if(CheckAttribute(rRealShip, "Bonus_HP")) rRealShip.HP = sti(rRealShip.HP) + sti(rRealShip.Bonus_HP);
		if(CheckAttribute(rRealShip, "Bonus_SpeedRate")) rRealShip.SpeedRate = stf(rRealShip.SpeedRate) + stf(rRealShip.Bonus_SpeedRate);
		if(CheckAttribute(rRealShip, "Bonus_TurnRate"))	rRealShip.TurnRate = stf(rRealShip.TurnRate) + stf(rRealShip.Bonus_TurnRate);
	}

	int iDiffWeight			= sti(rRealShip.Weight) - sti(rBaseShip.Weight);
	int iDiffCapacity		= sti(rRealShip.Capacity) - sti(rBaseShip.Capacity);
	int iDiffMaxCrew		= sti(rRealShip.MaxCrew) - sti(rBaseShip.MaxCrew);
	int iDiffMinCrew		= sti(rRealShip.MinCrew) - sti(rBaseShip.MinCrew);
	float fDiffSpeedRate	= stf(rRealShip.SpeedRate) - stf(rBaseShip.SpeedRate);
	int iDiffTurnRate		= sti(rRealShip.TurnRate) - sti(rBaseShip.TurnRate);
	int iDiffHP	    		= sti(rRealShip.HP) - sti(rBaseShip.HP);

	if (CheckAttribute(rRealShip, "QuestShip")) QuestShipDifficultyBoosts(rRealShip);
	else SetCabinTypeEx(rRealShip, sti(rRealShip.Class)); //Выдача случайной каюты по классу не квестовым - Gregg

	rRealShip.Price	= GetShipPriceByTTH(iShip, chr);

	if (sti(rRealShip.Price) <= 0) rRealShip.Price = 100;

	rRealShip.Stolen = isLock;  // ворованность
	rRealShip.soiling = 0;
	if (rand(4)==0) GetRandomSpecialUpgrade(rRealShip);

	SetRandomNameToShip(chr);

	return iShip;
}
// -> ugeen

void GetRandomSpecialUpgrade(ref rRealShip)
{
	for (int i = 0; i < 1+rand(2); i++)
	{
        switch (rand(5))
		{
			case 0:
				if (rRealShip.Type.War == true && rRealShip.Type.Merchant == false)
				{
					if (CheckAttribute(rRealShip, "Tuning.HullSpecial") && rRealShip.Tuning.HullSpecial == "1") break;//уже был этот апгрейд
					rRealShip.Tuning.HullSpecial = 1;
					rRealShip.price = makeint(sti(rRealShip.price)*1.5);
				}
			break;
			case 1:
				if (CheckAttribute(rRealShip, "Tuning.SailsSpecial") && rRealShip.Tuning.SailsSpecial == "1") break;//уже был этот апгрейд
				rRealShip.Tuning.SailsSpecial = 1;
				rRealShip.price = makeint(sti(rRealShip.price)*1.35);
			break;
			case 2:
				if (rRealShip.Type.War == true && rRealShip.Type.Merchant == false)
				{
					if (CheckAttribute(rRealShip, "Tuning.CannonsSpecial") && rRealShip.Tuning.CannonsSpecial == "1") break;//уже был этот апгрейд
					rRealShip.Tuning.CannonsSpecial = 1;
					rRealShip.price = makeint(sti(rRealShip.price)*1.25);
				}
			break;
			case 3:
				if (CheckAttribute(rRealShip, "Tuning.CuBot") && rRealShip.Tuning.CuBot == "1") break;//уже был этот апгрейд
				rRealShip.Tuning.CuBot = 1;
				rRealShip.price = makeint(sti(rRealShip.price)*1.4);
			break;
			case 4:
				if (rRealShip.Type.War == false && rRealShip.Type.Merchant == true)
				{
					if (CheckAttribute(rRealShip, "Tuning.BotPack") && rRealShip.Tuning.BotPack == "1") break;//уже был этот апгрейд
					rRealShip.Tuning.BotPack = 1;
					rRealShip.price = makeint(sti(rRealShip.price)*1.5);
					rRealShip.Capacity = sti(rRealShip.Capacity) + makeint(sti(rRealShip.Capacity)/2);
					rRealShip.HP = sti(rRealShip.HP) - makeint(sti(rRealShip.HP)/2);
				}
			break;
			case 5:
				if (CheckAttribute(rRealShip, "Tuning.HighBort") && rRealShip.Tuning.HighBort == "1") break;//уже был этот апгрейд
				rRealShip.Tuning.HighBort = 1;
				rRealShip.price = makeint(sti(rRealShip.price)*1.4);
			break;
		}
	}
}

void SetCabinTypeEx(ref rRealShip, int shipclass) //Выдача случайной каюты по классу не квестовым - Gregg
{
	if (shipclass == 7) return;

	if (shipclass == 6 || shipclass == 5)
	{
		switch (rand(1))
		{
			case 0: rRealShip.CabinType = "Cabin_Small"; return;
			break;
			case 1: rRealShip.CabinType = "New_Cabin1"; return;
			break;
		}
	}
	if (shipclass == 4 || shipclass == 3)
	{
		switch (rand(2))
		{
			case 0: rRealShip.CabinType = "Cabin_Medium"; return;
			break;
			case 1: rRealShip.CabinType = "Cabin_Medium2"; return;
			break;
			case 2: rRealShip.CabinType = "New_Cabin2"; return;
			break;
		}
	}
	if (shipclass == 2 || shipclass == 1)
	{
		switch (rand(2))
		{
			case 0: rRealShip.CabinType = "Cabin_Quest"; return;
			break;
			case 1: rRealShip.CabinType = "Cabin"; return;
			break;
			case 2: rRealShip.CabinType = "Cabin_Huge"; return;
			break;
		}
	}
}

// LEO: Пока ненужно всё это 16.12.2021
void QuestShipDifficultyBoosts(ref rRealShip) //LEO & Gregg: Кастомные бафы для квестовых кораблей в зависимости от сложности
{
	if(rRealShip.BaseName == "LuggerQuest")
	{
		// rRealShip.Capacity = sti(rRealShip.Capacity) + (31 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.OptCrew = sti(rRealShip.OptCrew) + (3 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.WindAgainstSpeed = stf(rRealShip.WindAgainstSpeed) + (0.1 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.SpeedRate = stf(rRealShip.SpeedRate) + (0.1 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.TurnRate = stf(rRealShip.TurnRate) + (1.2 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.HP = sti(rRealShip.HP) + (40 * MOD_SKILL_ENEMY_RATE);
		rRealShip.MastMultiplier = 1.3;
	}
	if(rRealShip.BaseName == "XebekVML")
	{
		// rRealShip.Capacity = sti(rRealShip.Capacity) + (50 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.OptCrew = sti(rRealShip.OptCrew) + (4 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.SpeedRate = stf(rRealShip.SpeedRate) + (0.1 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.WindAgainstSpeed = stf(rRealShip.WindAgainstSpeed) + (0.1 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.TurnRate = stf(rRealShip.TurnRate) + (1.0 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.HP = sti(rRealShip.HP) + (50 * MOD_SKILL_ENEMY_RATE);
		rRealShip.MastMultiplier = 1.3;
	}
	if(rRealShip.BaseName == "BrigQeen")
	{
		// rRealShip.Capacity = sti(rRealShip.Capacity) + (50 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.OptCrew = sti(rRealShip.OptCrew) + (4 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.SpeedRate = stf(rRealShip.SpeedRate) + (0.1 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.TurnRate = stf(rRealShip.TurnRate) + (1.0 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.HP = sti(rRealShip.HP) + (50 * MOD_SKILL_ENEMY_RATE);
		rRealShip.MastMultiplier = 1.3;
	}
	if(rRealShip.BaseName == "BrigSW")
	{
		// rRealShip.Capacity = sti(rRealShip.Capacity) + (50 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.OptCrew = sti(rRealShip.OptCrew) + (4 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.SpeedRate = stf(rRealShip.SpeedRate) + (0.1 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.TurnRate = stf(rRealShip.TurnRate) + (1.0 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.HP = sti(rRealShip.HP) + (50 * MOD_SKILL_ENEMY_RATE);
		rRealShip.MastMultiplier = 1.3;
	}
	if(rRealShip.BaseName == "Clipper")
	{
		// rRealShip.Capacity = sti(rRealShip.Capacity) + (50 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.OptCrew = sti(rRealShip.OptCrew) + (7 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.SpeedRate = stf(rRealShip.SpeedRate) + (0.1 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.WindAgainstSpeed = stf(rRealShip.WindAgainstSpeed) + (0.15 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.TurnRate = stf(rRealShip.TurnRate) + (0.7 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.HP = sti(rRealShip.HP) + (70 * MOD_SKILL_ENEMY_RATE);
		rRealShip.MastMultiplier = 1.3;
	}
	if(rRealShip.BaseName == "Corvette_quest")
	{
		// rRealShip.Capacity = sti(rRealShip.Capacity) + (50 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.OptCrew = sti(rRealShip.OptCrew) + (7 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.SpeedRate = stf(rRealShip.SpeedRate) + (0.1 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.WindAgainstSpeed = stf(rRealShip.WindAgainstSpeed) + (0.15 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.TurnRate = stf(rRealShip.TurnRate) + (0.7 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.HP = sti(rRealShip.HP) + (70 * MOD_SKILL_ENEMY_RATE);
		rRealShip.MastMultiplier = 1.3;
	}
	if(rRealShip.BaseName == "Catherine")
	{
		// rRealShip.Capacity = sti(rRealShip.Capacity) + (50 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.OptCrew = sti(rRealShip.OptCrew) + (2 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.SpeedRate = stf(rRealShip.SpeedRate) + (0.1 * MOD_SKILL_ENEMY_RATE); // LEO: Нефиг летать быстрее всех. Для этого есть ЧЖ
		// rRealShip.WindAgainstSpeed = stf(rRealShip.WindAgainstSpeed) + (0.15 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.TurnRate = stf(rRealShip.TurnRate) + (0.8 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.HP = sti(rRealShip.HP) + (60 * MOD_SKILL_ENEMY_RATE);
		rRealShip.MastMultiplier = 1.3;
	}
	if(rRealShip.BaseName == "Wh_corvette_quest")
	{
		// rRealShip.Capacity = sti(rRealShip.Capacity) + (50 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.OptCrew = sti(rRealShip.OptCrew) + (2 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.SpeedRate = stf(rRealShip.SpeedRate) + (0.1 * MOD_SKILL_ENEMY_RATE); // LEO: Нефиг летать быстрее всех. Для этого есть ЧЖ
		// rRealShip.WindAgainstSpeed = stf(rRealShip.WindAgainstSpeed) + (0.15 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.TurnRate = stf(rRealShip.TurnRate) + (0.8 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.HP = sti(rRealShip.HP) + (60 * MOD_SKILL_ENEMY_RATE);
		rRealShip.MastMultiplier = 1.3;
	}
	if(rRealShip.BaseName == "ArabellaShip")
	{
		// rRealShip.Capacity = sti(rRealShip.Capacity) + (50 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.OptCrew = sti(rRealShip.OptCrew) + (7 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.SpeedRate = stf(rRealShip.SpeedRate) + (0.1 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.TurnRate = stf(rRealShip.TurnRate) + (0.8 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.HP = sti(rRealShip.HP) + (150 * MOD_SKILL_ENEMY_RATE);
		rRealShip.MastMultiplier = 1.3;
	}
	if(rRealShip.BaseName == "FrigateQueen")
	{
		// rRealShip.Capacity = sti(rRealShip.Capacity) + (50 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.OptCrew = sti(rRealShip.OptCrew) + (7 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.SpeedRate = stf(rRealShip.SpeedRate) + (0.1 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.TurnRate = stf(rRealShip.TurnRate) + (0.8 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.HP = sti(rRealShip.HP) + (150 * MOD_SKILL_ENEMY_RATE);
		rRealShip.MastMultiplier = 1.3;
	}
	if(rRealShip.BaseName == "Flyingdutchman")
	{
		// rRealShip.Capacity = sti(rRealShip.Capacity) + (50 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.OptCrew = sti(rRealShip.OptCrew) + (7 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.SpeedRate = stf(rRealShip.SpeedRate) + (0.1 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.TurnRate = stf(rRealShip.TurnRate) + (0.8 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.HP = sti(rRealShip.HP) + (150 * MOD_SKILL_ENEMY_RATE);
		rRealShip.MastMultiplier = 1.3;
	}
	if(rRealShip.BaseName == "Santisima")
	{
		// rRealShip.Capacity = sti(rRealShip.Capacity) + (75 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.OptCrew = sti(rRealShip.OptCrew) + (10 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.SpeedRate = stf(rRealShip.SpeedRate) + (0.1 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.TurnRate = stf(rRealShip.TurnRate) + (0.5 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.HP = sti(rRealShip.HP) + (130 * MOD_SKILL_ENEMY_RATE);
		rRealShip.MastMultiplier = 1.3;
	}
	if(rRealShip.BaseName == "SoleyRu")
	{
		// rRealShip.Capacity = sti(rRealShip.Capacity) + (120 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.OptCrew = sti(rRealShip.OptCrew) + (20 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.SpeedRate = stf(rRealShip.SpeedRate) + (0.1 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.TurnRate = stf(rRealShip.TurnRate) + (0.5 * MOD_SKILL_ENEMY_RATE);
		// rRealShip.HP = sti(rRealShip.HP) + (200 * MOD_SKILL_ENEMY_RATE);
		rRealShip.MastMultiplier = 1.3;
	}
	rRealShip.MaxCrew = makeint(sti(rRealShip.OptCrew) * 1.25 + 0.5); // перегруз
}

int CreateBaseShip(int iBaseType)
{
	int iShip = FindFirstEmptyShip();

	if(iShip == -1)
	{
        trace("Can not find empty ship slot");
		return SHIP_NOTUSED;
	}

	ref rBaseShip = GetShipByType(iBaseType);
	ref rRealShip = GetRealShip(iShip);
	DeleteAttribute(rRealShip, "");
	CopyAttributes(rRealShip, rBaseShip);
    rRealShip.index = iShip;
    rRealShip.BaseType = iBaseType;
    if (!CheckAttribute(rRealShip, "ship.upgrades.hull")) // если задано в базе, то квестовый тип, не перебивать
    {
    	rRealShip.ship.upgrades.hull = 1;  //признак корабля теперь
    }
	rRealShip.ship.upgrades.sails = 1;

	int hullarmor;//реворк брони корпуса
	switch (rand(1))
	{
		case 0: hullarmor = 1; break;
		case 1: hullarmor = -1 break;
	}
	switch (sti(rRealShip.Class))
	{
		case 7: rRealShip.HullArmor = 4+(rand(1)*hullarmor); break;
		case 6: rRealShip.HullArmor = 12+(rand(1)*hullarmor); break;
		case 5: rRealShip.HullArmor = 16+(rand(1)*hullarmor); break;
		case 4: rRealShip.HullArmor = 20+(rand(2)*hullarmor); break;
		case 3: rRealShip.HullArmor = 24+(rand(2)*hullarmor); break;
		case 2: rRealShip.HullArmor = 32+(rand(2)*hullarmor); break;
		case 1: rRealShip.HullArmor = 42+(rand(2)*hullarmor); break;
	}

    rRealShip.BaseName = rRealShip.name; // запоминалка для нужд, тк далее идет "странное"
	if (rRealShip.name != "Fort" && rRealShip.name != "Boat") // не знаю зачем :(
	{
		rRealShip.name = rRealShip.name + "1"; // без этого вылет, но почему!!!!!!!!!!!!!!
		// выяснил - папка с моделью имеет на конце 1, вот и ответ
	}
    rRealShip.Stolen = 0;  // ворованность - честный

	if (iArcadeSails == 0) // момент инерции ниже для тактики
	{
	    rRealShip.InertiaAccelerationY = stf(rRealShip.InertiaAccelerationY) / 2.0;
	}

	return iShip;
}

void ResetShipCannonsDamages(ref refCharacter)
{
	aref refShip;

	makearef(refShip, refCharacter.Ship);
	refShip.Cannons.Borts = "";

	if (CheckAttribute(refShip, "Cannons.Borts.cannonf.damages")) { DeleteAttribute(refShip, "Cannons.Borts.cannonf.damages"); }
	if (CheckAttribute(refShip, "Cannons.Borts.cannonb.damages")) { DeleteAttribute(refShip, "Cannons.Borts.cannonb.damages"); }
	if (CheckAttribute(refShip, "Cannons.Borts.cannonl.damages")) { DeleteAttribute(refShip, "Cannons.Borts.cannonl.damages"); }
	if (CheckAttribute(refShip, "Cannons.Borts.cannonr.damages")) { DeleteAttribute(refShip, "Cannons.Borts.cannonr.damages"); }

	if (CheckAttribute(refShip, "Cannons.Borts.fcannon.damages")) { DeleteAttribute(refShip, "Cannons.Borts.fcannon.damages"); }
	if (CheckAttribute(refShip, "Cannons.Borts.bcannon.damages")) { DeleteAttribute(refShip, "Cannons.Borts.bcannon.damages"); }
	if (CheckAttribute(refShip, "Cannons.Borts.lcannon.damages")) { DeleteAttribute(refShip, "Cannons.Borts.lcannon.damages"); }
	if (CheckAttribute(refShip, "Cannons.Borts.rcannon.damages")) { DeleteAttribute(refShip, "Cannons.Borts.rcannon.damages"); }
}

// Генерация корабля для верфи
int GenerateStoreShip(int iBaseType)
{
	int iShip = GenerateShip(iBaseType, 0); // честный

	if (iShip == -1)
	{
		return SHIP_NOTUSED;
	}

	ref rRealShip = GetRealShip(iShip);
    rRealShip.StoreShip = true;  // корабль на верфи, трется отдельным методом

	return iShip;
}

// переработка метода 26.05.06 boal

// -> ugeen 25.01.09 -> для верфи
int GenerateStoreShipExt(int iBaseType, ref chr)
{
	int iShip = GenerateShipExt(iBaseType, 0, chr); // честный

	if (iShip == -1)
	{
		return SHIP_NOTUSED;
	}

	ref rRealShip = GetRealShip(iShip);
	rRealShip.StoreShip = false;  // корабль на верфи, трется отдельным методом

	return iShip;
}
// <- ugeen

// идея: трем все корабли, где нет НПС-владельца, все галки пофиг
void EmptyAllFantomShips()
{
	int  i;
	ref  chr;
	// оптимальный код - два прохода, а не вложенный цикл. В начале всем сносим флаг удаляемости, потом проставляем, где есть НПС
	for (i = 0; i < REAL_SHIPS_QUANTITY; i++)
	{
        DeleteAttribute(&RealShips[i], "lock");
	}
	// лодку ставим, тк он имеет индекс НПС за пределами MAX_CHARACTERS
	//RealShips[sti(Characters[BOAT_CHARACTER].ship.type)].lock = true;
	// теперь НПС-кэпы
	for (i = 0; i < MAX_CHARACTERS; i++)
	{
        chr = &Characters[i];
        if (CheckAttribute(chr, "ship.type") && chr.ship.type != SHIP_NOTUSED)
        {
            RealShips[sti(chr.ship.type)].lock = true;
        }
        // очистка для верфи
		if (CheckAttribute(chr, "shipyard"))
		{
		    FreeShipFromShipyard(chr);
		}
	}
	for (i = FANTOM_CHARACTERS; i < TOTAL_CHARACTERS; i++) // фантомы в море
	{
        chr = &Characters[i];
        if (CheckAttribute(chr, "ship.type") && chr.ship.type != SHIP_NOTUSED)
        {
            RealShips[sti(chr.ship.type)].lock = true;
        }
		else
		{
			/*if (CheckAttribute(chr,"id"))
			{
				if (HasSubStr(chr.id,"ShipWreck_") || HasSubStr(chr.id,"Convict")) {}
				else InitCharacter(&Characters[i], i);
			}
			else InitCharacter(&Characters[i], i);	//ugeen : чистим нафиг все атрибуты пустых фантомов (переиничиваем)*/
			//if (CheckAttribute(chr,"location") && chr.location == "none") InitCharacter(&Characters[i], i);
			if (CheckAttribute(chr,"lifeday") && sti(chr.lifeday) == 0) InitCharacter(&Characters[i], i);
		}
	}
	// теперь сборка мусора
	for (i = 0; i < REAL_SHIPS_QUANTITY; i++)
	{
        if (!CheckAttribute(&RealShips[i], "lock") && !CheckAttribute(&RealShips[i], "StoreShip"))  // на верфи корабли не трем
        {
			DeleteAttribute(&RealShips[i], "");
		}
	}
}

int GetRealShipsCount()
{ // метод для отладки
	int result = 0;

	for (int i= 0; i< REAL_SHIPS_QUANTITY; i++)
	{
		if (checkAttribute(&RealShips[i], "name"))
		{
			result++;
		}
	}

	return result;
}

// поиск пустого слота
int FindFirstEmptyShip()
{
	for(int i = 0; i < REAL_SHIPS_QUANTITY; i++)
	{
		if(!checkAttribute(&RealShips[i], "name"))
		{
			//#20170912-02 Fix for RealShips/Character sails
		    DeleteAttribute(&RealShips[i], "ship.upgrades");
		    DeleteAttribute(&RealShips[i], "EmblemedSails");
		    DeleteAttribute(&RealShips[i], "GeraldSails");
			return i;
		}
	}

	return -1;
}

//Boyer add for new game #20170301-6
void ResetRealShipArray()
{
	for(int i = 0; i < REAL_SHIPS_QUANTITY; i++)
	{
		DeleteAttribute(&RealShips[i], "name");
	}
	return;
}

float FindShipSpeed(aref refCharacter)
{
	if(!CheckAttribute(refCharacter, "Ship.type"))
	{
		trace("Character " + refCharacter.id + " have no ship!");
		return 0.0;
	}
	int nShipType = sti(refCharacter.ship.type);
	if(nShipType == SHIP_NOTUSED)
	{
		trace("Character " + refCharacter.id + " have invalid ship!");
		return 1.0;
	}
	ref rShip = GetRealShip(nShipType);

	float	fMaxSpeedZ = stf(rShip.SpeedRate);  // базовая скорость
	float fShipHp = stf(refCharacter.ship.hp);
	float fShipMaxHp = stf(rShip.HP);
	float fSpeedFromHp = fShipHp/fShipMaxHp;
	fSpeedFromHp = 0.8 + fSpeedFromHp*0.3;

	if(fSpeedFromHp > 1.0) // некий запас перед снижением скорости
	{
		fSpeedFromHp = 1.0;
	}

	fMaxSpeedZ = fMaxSpeedZ * AIShip_isPerksUse(CheckCharacterPerk(refCharacter, "MapMaker"), 1.0, 1.05);
	float fSailsDamage = stf(refCharacter.ship.sp);

	float	fTRFromSailDamage = Bring2Range(0.1, 1.0, 0.1, 100.0, fSailsDamage); //0.3

	float fTRFromShipState = fSpeedFromHp * fTRFromSailDamage;
    if(!CheckAttribute(refCharacter, "Cargo")) RecalculateCargoLoad(refCharacter);
	float	fLoad = Clampf(stf(refCharacter.Ship.Cargo.Load) / stf(rShip.Capacity));
	float	fTRFromWeight = Clampf(1.03 - stf(rShip.SpeedDependWeight) * fLoad);
	float   fTRFromSkill = SpeedBySkill(refCharacter);
	// от команды
	float fCrewMax = stf(rShip.MaxCrew);
	float fCrewOpt = stf(rShip.OptCrew);
	float fCrewCur = stf(refCharacter.Ship.Crew.Quantity);
	if (fCrewCur > fCrewMax)
	{
		fCrewCur = fCrewMax;
	}
	float  fTRFromPeople;
	fTRFromPeople = 0.85 + ((GetCrewExp(refCharacter, "Sailors") * fCrewCur) / (fCrewOpt * GetCrewExpRate())) * 0.15;
	if (fTRFromPeople > 1) fTRFromPeople = 1;

	fMaxSpeedZ = fMaxSpeedZ * fTRFromWeight * fTRFromSkill * fTRFromShipState * fTRFromPeople;

	float fSoiling = (100-(stf(refCharacter.ship.soiling)*0.3))/100;
	fMaxSpeedZ = fMaxSpeedZ * fSoiling;

	return fMaxSpeedZ;
}

float SpeedBySkill(aref refCharacter)
{
	float fSkill = GetSummonSkillFromNameToOld(refCharacter, SKILL_SAILING);

	float fTRFromSkill = 0.7 + (0.03 *  fSkill);

    float fSpeedPerk = AIShip_isPerksUse(CheckOfficersPerk(refCharacter, "ShipSpeedUp"), 1.0, 1.15);   //slib
    fSpeedPerk = AIShip_isPerksUse(CheckOfficersPerk(refCharacter, "SailingProfessional"), fSpeedPerk, 1.20);
	fSpeedPerk =  AIShip_isPerksUse(CheckOfficersPerk(refCharacter, "SeaWolf"), fSpeedPerk, fSpeedPerk+0.05);
	//if (CheckAttribute(&RealShips[sti(refCharacter.Ship.Type)], "Tuning.SailsSpecial")) fSpeedPerk *= 0.85;
	if (CheckAttribute(&RealShips[sti(refCharacter.Ship.Type)], "Tuning.HullSpecial")) fSpeedPerk *= 0.75;
	if (CheckAttribute(&RealShips[sti(refCharacter.Ship.Type)], "Tuning.CuBot")) fSpeedPerk *= 1.05;

	return fTRFromSKill*fSpeedPerk;
}

float FindShipTurnRate(aref refCharacter)
{
	if(!CheckAttribute(refCharacter, "Ship.type"))
	{
		trace("Character " + refCharacter.id + " have no ship!");
		return 0.0;
	}
	int nShipType = sti(refCharacter.ship.type);
	if(nShipType == SHIP_NOTUSED)
	{
		trace("Character " + refCharacter.id + " have invalid ship!");
		return 1.0;
	}
	ref rShip = GetRealShip(nShipType);

	float fShipHp = stf(refCharacter.ship.hp);
	float fShipMaxHp = stf(rShip.HP);
	float fSpeedFromHp = fShipHp/fShipMaxHp;
	fSpeedFromHp = 0.7 + fSpeedFromHp * 0.3;
    if(!CheckAttribute(refCharacter, "Cargo")) RecalculateCargoLoad(refCharacter);
	float fLoad = Clampf(stf(refCharacter.Ship.Cargo.Load) / stf(rShip.Capacity));
	float fTRFromWeight;
	if (iArcadeSails == 1)
	{
		fTRFromWeight = Clampf(1.03 - stf(rShip.TurnDependWeight) * fLoad);
	}
	else
	{
		fTRFromWeight = Clampf(1.03 - 2.0*stf(rShip.TurnDependWeight) * fLoad); // влияние веса больше
	}
	// не реализовано, всегда 1 float fTRFromSpeed = 1.0 - stf(rShip.TurnDependSpeed);
	// от команды
	//float fCrewMin = stf(rShip.MinCrew);
	float fCrewMax = stf(rShip.MaxCrew);
	float fCrewOpt = stf(rShip.OptCrew);
	float fCrewCur = stf(refCharacter.Ship.Crew.Quantity);
	if (fCrewCur > fCrewMax)
	{
		fCrewCur = fCrewMax;
	}
	float  fTRFromPeople;
	if (iArcadeSails == 1)
	{
		fTRFromPeople = 0.3 + ((GetCrewExp(refCharacter, "Sailors") * fCrewCur) / (fCrewOpt * GetCrewExpRate())) * 0.7;
	}
	else
	{
		fTRFromPeople = 0.05 + ((GetCrewExp(refCharacter, "Sailors") * fCrewCur) / (fCrewOpt * GetCrewExpRate())) * 0.95;
	}
	if (fTRFromPeople > 1) fTRFromPeople = 1;

	float fTRFromSkill = TurnBySkill(refCharacter);

	float fTRFromSailDamage = Bring2Range(0.05, 1.0, 0.1, 100.0, stf(refCharacter.ship.sp));

	float fTurn = fTRFromWeight * fTRFromSkill * fTRFromPeople * fTRFromSailDamage * fSpeedFromHp;

	float fSoiling = (100-(stf(refCharacter.ship.soiling)*0.15))/100;
	fTurn = fTurn * fSoiling;

	//Log_info(refCharacter.id + "  " + fTurn);
	return fTurn;
}

float TurnBySkill(aref refCharacter)
{
	float fSkill = GetSummonSkillFromNameToOld(refCharacter, SKILL_SAILING);
	float fTRFromSKill;

    if (iArcadeSails == 1)
	{
		fTRFromSKill = 0.5 + (0.05 * fSkill);
	}
	else
	{
		fTRFromSKill = 0.3 + (0.07 * fSkill);
	}

    float fSpeedPerk = AIShip_isPerksUse(CheckOfficersPerk(refCharacter, "ShipTurnRateUp"), 1.0, 1.15);   //slib
    fSpeedPerk = AIShip_isPerksUse(CheckOfficersPerk(refCharacter, "SailingProfessional"), fSpeedPerk, 1.20);
	fSpeedPerk =  AIShip_isPerksUse(CheckOfficersPerk(refCharacter, "SeaWolf"), fSpeedPerk, fSpeedPerk+0.05);
    float fFastTurn180 = AIShip_isPerksUse(CheckOfficersPerk(refCharacter, "Turn180"), 1.0, 4.0);
	if (CheckAttribute(&RealShips[sti(refCharacter.Ship.Type)], "Tuning.SailsSpecial")) fSpeedPerk *= 0.8;
	if (CheckAttribute(&RealShips[sti(refCharacter.Ship.Type)], "Tuning.HullSpecial")) fSpeedPerk *= 0.75;
	if (CheckAttribute(&RealShips[sti(refCharacter.Ship.Type)], "Tuning.CuBot")) fSpeedPerk *= 1.05;

	return fTRFromSKill*fSpeedPerk*fFastTurn180;
}


float FindShipSpeedBonus(ref refCharacter)
{
	if(!CheckAttribute(refCharacter, "Ship.type"))
	{
		trace("Character " + refCharacter.id + " have no ship!");
		return 0.0;
	}
	int nShipType = sti(refCharacter.ship.type);
	if(nShipType == SHIP_NOTUSED)
	{
		trace("Character " + refCharacter.id + " have invalid ship!");
		return 0.0;
	}
	float	fMaxSpeedZ = 1.0;  // базовая скорость
	fMaxSpeedZ *= AIShip_isPerksUse(CheckCharacterPerk(refCharacter, "MapMaker"), 1.0, 1.05);
	fMaxSpeedZ *= ShipSpeedBonusFromWeight(refCharacter);
	fMaxSpeedZ *= ShipSpeedBonusFromHP(refCharacter);
	fMaxSpeedZ *= ShipSpeedBonusFromPeople(refCharacter);
	fMaxSpeedZ *= ShipSpeedBonusFromSails(refCharacter);
	fMaxSpeedZ *= ShipSpeedBonusFromSoiling(refCharacter);
	fMaxSpeedZ *= SpeedBySkill(refCharacter);
	return fMaxSpeedZ;
}
//================//
float ShipSpeedBonusFromWeight(ref _refCharacter)
{	// от загрузки трюма
	if(!CheckAttribute(_refCharacter, "Cargo")) RecalculateCargoLoad(_refCharacter);
	ref rShip = GetRealShip(sti(_refCharacter.ship.type));
	float	fLoad = Clampf(stf(_refCharacter.Ship.Cargo.Load) / stf(rShip.Capacity));
	float	fTRFromWeight = Clampf(1.03 - stf(rShip.SpeedDependWeight) * fLoad);
	return fTRFromWeight;
}
float ShipSpeedBonusFromHP(ref _refCharacter)
{	// от повреждения корпуса
	ref rShip = GetRealShip(sti(_refCharacter.ship.type));
	float fShipHp = stf(_refCharacter.ship.hp);
	float fShipMaxHp = stf(rShip.HP);
	float fSpeedFromHp = fShipHp/fShipMaxHp;
	fSpeedFromHp = 0.8 + fSpeedFromHp*0.3;
	if(fSpeedFromHp > 1.0) fSpeedFromHp = 1.0;// некий запас перед снижением скорости
	return fSpeedFromHp;
}
float ShipSpeedBonusFromPeople(ref _refCharacter)
{	// от команды
	ref rShip = GetRealShip(sti(_refCharacter.ship.type));
	float fCrewMax = stf(rShip.MaxCrew);
	float fCrewOpt = stf(rShip.OptCrew);
	float fCrewCur = stf(_refCharacter.Ship.Crew.Quantity);
	if (fCrewCur > fCrewMax) fCrewCur = fCrewMax;
	float  fTRFromPeople = 0.85 + ((GetCrewExp(_refCharacter, "Sailors") * fCrewCur) / (fCrewOpt * GetCrewExpRate())) * 0.15;
	if (fTRFromPeople > 1) fTRFromPeople = 1;
	return fTRFromPeople;
}
float ShipSpeedBonusFromSails(ref _refCharacter)
{	// от повреждения парусов
	float fTRFromSailDamage = Bring2Range(0.1, 1.0, 0.1, 100.0, stf(_refCharacter.ship.sp)); //0.3
	return fTRFromSailDamage;
}
float ShipSpeedBonusFromSoiling(ref _refCharacter)
{	// от загрязнения дна
	float fSoiling = (100-(stf(_refCharacter.ship.soiling)*0.3))/100;
	return fSoiling;
}
//================//
float ShipTurnRateBonusFromWeight(ref _refCharacter)
{	// от загрузки трюма
    if(!CheckAttribute(_refCharacter, "Cargo")) RecalculateCargoLoad(_refCharacter);
	ref rShip = GetRealShip(sti(_refCharacter.ship.type));
	float fLoad = Clampf(stf(_refCharacter.Ship.Cargo.Load) / stf(rShip.Capacity));
	float fTRFromWeight;
	if (iArcadeSails == 1) fTRFromWeight = Clampf(1.03 - stf(rShip.TurnDependWeight) * fLoad);
		else fTRFromWeight = Clampf(1.03 - 2.0*stf(rShip.TurnDependWeight) * fLoad); // влияние веса больше
	return fTRFromWeight;
}
float ShipTurnRateBonusFromHP(ref _refCharacter)
{	// от повреждения корпуса
	ref rShip = GetRealShip(sti(_refCharacter.ship.type));
	float fShipHp = stf(_refCharacter.ship.hp);
	float fShipMaxHp = stf(rShip.HP);
	float fSpeedFromHp = fShipHp/fShipMaxHp;
	fSpeedFromHp = 0.7 + fSpeedFromHp * 0.3;
	return fSpeedFromHp;
}
float ShipTurnRateBonusFromPeople(ref _refCharacter)
{	// от команды
	ref rShip = GetRealShip(sti(_refCharacter.ship.type));
	//float fCrewMin = stf(rShip.MinCrew);
	float fCrewMax = stf(rShip.MaxCrew);
	float fCrewOpt = stf(rShip.OptCrew);
	float fCrewCur = stf(_refCharacter.Ship.Crew.Quantity);
	if (fCrewCur > fCrewMax) fCrewCur = fCrewMax;
	float  fTRFromPeople;
	if (iArcadeSails == 1) fTRFromPeople = 0.3 + ((GetCrewExp(_refCharacter, "Sailors") * fCrewCur) / (fCrewOpt * GetCrewExpRate())) * 0.7;
		else fTRFromPeople = 0.05 + ((GetCrewExp(_refCharacter, "Sailors") * fCrewCur) / (fCrewOpt * GetCrewExpRate())) * 0.95;
	if (fTRFromPeople > 1) fTRFromPeople = 1;
	return fTRFromPeople;
}
float ShipTurnRateBonusFromSails(ref _refCharacter)
{	// от повреждения парусов
	float fTRFromSailDamage = Bring2Range(0.05, 1.0, 0.1, 100.0, stf(_refCharacter.ship.sp));
	return fTRFromSailDamage;
}
float ShipTurnRateBonusFromSoiling(ref _refCharacter)
{	// от загрязнения дня
	float fSoiling = (100-(stf(_refCharacter.ship.soiling)*0.15))/100;
	return fSoiling;
}
//================//
float FindShipTurnRateBonus(aref refCharacter)
{
	if(!CheckAttribute(refCharacter, "Ship.type"))
	{
		trace("Character " + refCharacter.id + " have no ship!");
		return 0.0;
	}
	int nShipType = sti(refCharacter.ship.type);
	if(nShipType == SHIP_NOTUSED)
	{
		trace("Character " + refCharacter.id + " have invalid ship!");
		return 0.0;
	}
	ref rShip = GetRealShip(nShipType);

	float fTurn = 1.0;  // базовая скорость
	// не реализовано влияние скорости, всегда 1 float fTRFromSpeed = 1.0 - stf(rShip.TurnDependSpeed);
	fTurn *= ShipTurnRateBonusFromWeight(refCharacter);
	fTurn *= ShipTurnRateBonusFromHP(refCharacter);
	fTurn *= ShipTurnRateBonusFromPeople(refCharacter);
	fTurn *= ShipTurnRateBonusFromSails(refCharacter);
	fTurn *= ShipTurnRateBonusFromSoiling(refCharacter);
	fTurn *= TurnBySkill(refCharacter);
	return fTurn;
}

// calculate recharge time for cannon
float Cannon_GetRechargeTimeValue(aref aCharacter)
{
	if(!CheckAttribute(aCharacter, "Ship.type"))
	{
		trace("Character " + aCharacter.id + " have no ship!");
		return 0.0;
	}
	int nShipType = sti(aCharacter.ship.type);
	if(nShipType == SHIP_NOTUSED)
	{
		trace("Character " + aCharacter.id + " have invalid ship!");
		return 0.0;
	}

	float	fCannonSkill = 1.0 - makefloat(GetCharacterSkill(aCharacter, SKILL_CANNONS)/100.0) / 3.0;

	ref		rCannon = GetCannonByType(sti(aCharacter.Ship.Cannons.Type));
	float	fReloadTime = GetCannonReloadTime(rCannon); // boal 28.01.03 - 09.02.05

	float fMultiply = 1.0;
	if (CheckCharacterPerk(aCharacter, "FastReload")) fMultiply = 0.9;
	else fMultiply = 1.0
	if (IsCharacterPerkOn(aCharacter, "ImmediateReload")) fMultiply *= 0.5;
	else fMultiply = fMultiply - 0.0;
	if (CheckAttribute(&RealShips[sti(aCharacter.Ship.Type)], "Tuning.CannonsSpecial")) fMultiply *= 1.2;
	fMultiply *= (1+CheckOfficersPerk(aCharacter,"InstantRepair"));//x2 времени при активной быстрой починке
	// boal 060804 для компа поблажки
	//Boyer remove reload speed boost for enemies
	if (sti(aCharacter.index) != GetMainCharacterIndex())
	{
	   fReloadTime -= MOD_SKILL_ENEMY_RATE/2; // -10c на невозможном
	}
	// boal <--
	float crewQty  = GetCrewQuantity(aCharacter);
	float OptCrew  = GetOptCrewQuantity(aCharacter);
	float MaxCrew  = GetMaxCrewQuantity(aCharacter);
	float fMorale  = GetCharacterCrewMorale(aCharacter);

	if (crewQty > MaxCrew) crewQty = MaxCrew; // fix 14/03/05
	if (OptCrew > 0)
	{
		float  fExp;
		fExp = 0.001 + stf(GetCrewExp(aCharacter, "Cannoners") * crewQty) / stf(OptCrew * GetCrewExpRate());
		if (fExp > 1) fExp = 1;
		fReloadTime = fReloadTime * (1.0 + (1.0 - fExp) * 3.0);
	}
	fReloadTime = fReloadTime * (1.0 + (1.0 - fMorale / MORALE_NORMAL) * 0.2);

	if (crewQty <= (GetMinCrewQuantity(aCharacter)))
	{
		fReloadTime = fReloadTime * 3.0; //меньше команды - тормозим
	}
    // boal  корректный учет команды <--
	return  fMultiply * fReloadTime * fCannonSkill;
}

int GetCannonsNum(aref chr)
{
	int nShipType = sti(chr.ship.type);
	if(nShipType == SHIP_NOTUSED)
	{
		trace("Character " +chr.id + " have invalid ship!");
		return 0;
	}
    ref refBaseShip = GetRealShip(nShipType);
	int iCannons = GetBortIntactCannonsNum(chr, "fcannon", sti(refBaseShip.fcannon)) + GetBortIntactCannonsNum(chr, "bcannon", sti(refBaseShip.bcannon)) + GetBortIntactCannonsNum(chr, "lcannon", sti(refBaseShip.lcannon)) + GetBortIntactCannonsNum(chr, "rcannon", sti(refBaseShip.rcannon));
	return iCannons;
}

// ugeen  02.02.09
int GetCannonsNumMax(aref chr)
{
	int nShipType = sti(chr.ship.type);
	ref refBaseShip = GetRealShip(nShipType);

	int iCannons = sti(refBaseShip.CannonsQuantityMax);

	return iCannons;
}
// ugeen

// boal
int GetBortCannonsQty(aref chr, string  sType)
{
	int nShipType = sti(chr.ship.type);
	if(nShipType == SHIP_NOTUSED)
	{
		trace("Character " +chr.id + " have invalid ship!");
		return 0;
	}
    ref refBaseShip = GetRealShip(nShipType);

	int iCannons = GetBortIntactCannonsNum(chr, sType, sti(refBaseShip.(sType)));

	return iCannons;
}

int GetBortCannonsMaxQty(aref chr, string  sType)
{
	int nShipType = sti(chr.ship.type);
	if(nShipType == SHIP_NOTUSED)
	{
		trace("Character " +chr.id + " have invalid ship!");
		return 0;
	}
    ref refBaseShip = GetRealShip(nShipType);

	int iCannons = sti(refBaseShip.(sType));

	return iCannons;
}

int GetBortCannonsBaseQty(ref chr, string sBort)
{
	int nShipType = sti(chr.ship.type);
	ref rRealShip = GetRealShip(nShipType);
	ref rBaseShip = GetShipByType(sti(rRealShip.BaseType));

	int iCannons = sti(rBaseShip.(sBort));

	return iCannons;
}
///////////////////////  ВЕРФИ //////////////////////
//Lipsar учет нации на верфях-->
void SetShipyardStore(ref NPChar)
{
    int    iTest_ship, i;
	string attrName;

	if (CheckAttribute(NPChar, "shipyard")) return; // еще есть корабли с того раза

	SaveCurrentNpcQuestDateParam(npchar, "shipyardDate"); // дата заполнения верфи

    if (bBettaTestMode)
    {
        for (i = 1; i <=SHIP_TYPES_QUANTITY; i++)
        {
            attrName = "ship" + i;
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(i-1, NPChar), attrName);
        }
        return;
    }

	FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_TARTANE, NPChar), "ship1"); // обязательный на верфи

	string shipyarder_nation=NPChar.nation;//учет нации Lipsar
	// 0-england 1-france 2-spain 3-holland 4-pirate;
	int storeArray[SHIP_TYPES_QUANTITY];
	aref rShip;
	int j=0;
	switch (shipyarder_nation)
	{
		case "0":
			for (i=0;i<116;i++)//fix 116 для учета только НЕ квестовых кораблей
			{
				makearef(rShip,ShipsTypes[i].nation.england);
				if (rShip==true)
				{
					storeArray[j]= i;
					j++;
				}
			}
		break;
		case "1":
			for (i=0;i<116;i++)
			{
				makearef(rShip,ShipsTypes[i].nation.france);
				if (rShip==true)
				{
					storeArray[j]= i;
					j++;
				}
			}
		break;
		case "2":
			for ( i=0;i<116;i++)
			{
				makearef(rShip,ShipsTypes[i].nation.spain);
				if (rShip==true)
				{
					storeArray[j]= i;
					j++;
				}
			}
		break;
		case "3":
			for (i=0;i<116;i++)
			{
				makearef(rShip,ShipsTypes[i].nation.holland);
				if (rShip==true)
				{
					storeArray[j]= i;
					j++;
				}
			}
		break;
		case "4":
			for (i=0;i<116;i++)
			{
				makearef(rShip,ShipsTypes[i].nation.pirate);
				if (rShip==true)
				{
					storeArray[j]= i;
					j++;
				}
			}
		break;
	}
	int j1,j2,j3,j4,j5,j6=0;
	for (i=0;i<j;i++)
		{
			j6=i;
			if (sti(ShipsTypes[storeArray[i]].Class)==6) break;//ищем начало 6 класса
		}
	iTest_ship=rand(j6-1);
	FillShipParamShipyard(NPChar, GenerateStoreShipExt(storeArray[iTest_ship], NPChar), "ship2");

	iTest_ship=rand(j6-1);
	FillShipParamShipyard(NPChar, GenerateStoreShipExt(storeArray[iTest_ship], NPChar), "ship3");//2 корабля 7 класса

	for (i=j6+1;i<j;i++)
		{
			j5=i;
			if (sti(ShipsTypes[storeArray[i]].Class)==5) break;//ищем начало 5 класса
		}
	if (sti(PChar.rank)>=1)
		{
			iTest_ship=j6+rand(j5-j6-1);
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(storeArray[iTest_ship], NPChar), "ship4");

			iTest_ship=j6+rand(j5-j6-1);
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(storeArray[iTest_ship], NPChar), "ship5");//2 корабля 6 класса
		}
	for (i=j5+1;i<j;i++)
	{
		j4=i;
		if (sti(ShipsTypes[storeArray[i]].Class)==4) break;//ищем начало 4 класса
	}
	if (sti(PChar.rank)>=5)
		{
			iTest_ship=j5+rand(j4-j5-1);
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(storeArray[iTest_ship], NPChar), "ship6");

			iTest_ship=j5+rand(j4-j5-1);
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(storeArray[iTest_ship], NPChar), "ship7");

			iTest_ship=j5+rand(j4-j5-1);
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(storeArray[iTest_ship], NPChar), "ship8");//3 корабля 5 класса
		}

	for (i=j4+1;i<j;i++)
		{
			j3=i;
			if (sti(ShipsTypes[storeArray[i]].Class)==3) break;//ищем начало 3 класса
		}
	if (sti(PChar.rank)>=10)
		{
			iTest_ship=j4+rand(j3-j4-1);
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(storeArray[iTest_ship], NPChar), "ship9");

			iTest_ship=j4+rand(j3-j4-1);
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(storeArray[iTest_ship], NPChar), "ship10");

			iTest_ship=j4+rand(j3-j4-1);
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(storeArray[iTest_ship], NPChar), "ship11");//3 корабля 4 класса
		}
	for (i=j3+1;i<j;i++)
		{
			j2=i;
			if (sti(ShipsTypes[storeArray[i]].Class)==2) break;//ищем начало 2 класса
		}
	if (sti(PChar.rank)>=20)
		{
			iTest_ship=j3+rand(j2-j3-1);
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(storeArray[iTest_ship], NPChar), "ship12");

			iTest_ship=j3+rand(j2-j3-1);
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(storeArray[iTest_ship], NPChar), "ship13");//2 корабля 3 класса
		}
	for (i=j2+1;i<j;i++)
		{
			j1=i;
			if (sti(ShipsTypes[storeArray[i]].Class)==1) break;//ищем начало 1 класса
		}
	if (sti(PChar.rank)>=25)
		{
			iTest_ship=j2+rand(j1-j2-1);
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(storeArray[iTest_ship], NPChar), "ship14");//корабль 2 класса
		}
	if (sti(PChar.rank)>=30)
		{
			iTest_ship=j1+rand(j-j1-1);
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(storeArray[iTest_ship], NPChar), "ship15");//корабль 1 класса
		}
}
//Lipsar учет нации на верфях<--
void FreeShipFromShipyard(ref NPChar)
{
	if (GetNpcQuestPastDayParam(NPChar, "shipyardDate") > (3 + rand(6)))
	{
        aref   arDest, arImt;
		string sAttr;
		int    iNum, i, iShip;
		makearef(arDest, NPChar.shipyard);
		iNum = GetAttributesNum(arDest);
		for (i = 0; i < iNum; i++)
		{
	    	arImt = GetAttributeN(arDest, i);
	    	iShip = sti(arImt.Type); //GetAttributeValue(arImt));
	    	DeleteAttribute(&RealShips[iShip], "StoreShip"); // можно тереть
	    }
        DeleteAttribute(NPChar, "shipyard");
	}
}

void RemoveCannonsFromBortShipyard(ref chr, string sBort)
{
//	int     maxQty = GetBortCannonsMaxQty(chr, sBort);
	int     maxQty = GetBortCannonsBaseQty(chr, sBort);
	int     i;
	string  attr;
	string  sBort_real = sBort;


	if(sBort == "rcannon") sBort_real = "cannonr";
	if(sBort == "lcannon") sBort_real = "cannonl";
	if(sBort == "fcannon") sBort_real = "cannonf";
	if(sBort == "bcannon") sBort_real = "cannonb";

	// нулим кол-во пушек на борту
	for (i = 0; i < maxQty; i++)
	{
		attr = "c" + i;
		// поломана на 100 процентов, не палит, те нет ее
		chr.Ship.Cannons.borts.(sBort).damages.(attr) = 1.0;
		chr.Ship.Cannons.borts.(sBort_real).damages.(attr) = 1.0;
	}

	RecalculateCargoLoad(chr);  // пересчет, тк пушки снялись
}

void RemoveAllCannonsShipyardShip(ref NPChar)
{
    RemoveCannonsFromBortShipyard(NPChar, "fcannon");
    RemoveCannonsFromBortShipyard(NPChar, "bcannon");
    RemoveCannonsFromBortShipyard(NPChar, "rcannon");
    RemoveCannonsFromBortShipyard(NPChar, "lcannon");
}

void FillShipParamShipyard(ref NPChar, int _iType, string _sShipNum)
{
    aref    arTo, arFrom;

	DeleteAttribute(NPChar, "ship");
    NPChar.Ship.Type = _iType;

	SetRandomNameToShip(NPChar);

    SetBaseShipData(NPChar);
    SetCrewQuantity(NPChar, 0);
    if (sti(NPChar.Ship.Cannons.Type) != CANNON_TYPE_NONECANNON)
    {
    	NPChar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS8; // to_do переделать на продажу без орудий вообще
    }
	RemoveAllCannonsShipyardShip(NPChar);	//нулим пушки .. сами покупайте какие надо
    DeleteAttribute(NPChar, "Ship.Cargo");  //пустой трюм
    SetGoodsInitNull(NPChar);
    RecalculateCargoLoad(NPChar);

    FillShipyardShipBack(NPChar, _sShipNum);
}

void FillShipyardShip(ref NPChar, string _sShipNum)
{
    aref    arTo, arFrom;

	DeleteAttribute(NPChar, "ship");

    makearef(arFrom,   NPChar.shipyard.(_sShipNum));
    NPChar.Ship = "";
	makearef(arTo, NPChar.Ship);
	CopyAttributes(arTo, arFrom);
}

void FillShipyardShipBack(ref NPChar, string _sShipNum)
{
    aref    arTo, arFrom;

  	DeleteAttribute(NPChar, "shipyard." + _sShipNum);
    NPChar.shipyard.(_sShipNum) = "";
    makearef(arTo,   NPChar.shipyard.(_sShipNum));
	makearef(arFrom, NPChar.Ship);
	CopyAttributes(arTo, arFrom);
}

int GetSailsTuningPrice(ref _chr, ref _shipyard, float _rate)
{
	int st  = GetCharacterShipType(_chr);
	ref shref;

	if (st==SHIP_NOTUSED) return 0;
	shref = GetRealShip(st);

	return makeint(stf(_shipyard.ShipCostRate) * sti(shref.Price) * _rate / 10) * 10; // кратно 10
}

// Warship 26.07.09 Вынес сюда
// int st - GetCharacterShipType(_character)
// ref _shipyard - референс на верфиста
int GetShipPriceByType(int st, ref _shipyard)
{
	if(st==SHIP_NOTUSED) return 0;
	ref shref = GetRealShip(st);

	return makeint(stf(_shipyard.ShipCostRate) * sti(shref.Price));
}

// Метод вернет цену продажи корабля персонажа с учетом всех скилов (для верфи)
int GetShipSellPrice(ref _chr, ref _shipyard)
{
	int st = GetCharacterShipType(_chr);
	int price = GetShipPriceByType(st, _shipyard);
	price = makeint(price - 1.5*GetSailRepairCost(st, GetSailDamagePercent(_chr), _shipyard));
	price = makeint(price - 1.5*GetHullRepairCost(st, GetHullDamagePercent(_chr), _shipyard));

	float nCommerce   = GetSummonSkillFromNameToOld(GetMainCharacter(), SKILL_COMMERCE) + 0.001;

	if(CheckOfficersPerk(pchar,"Trader")) { nCommerce += 2; }
	if(CheckOfficersPerk(pchar,"AdvancedCommerce"))	{ nCommerce += 4; }
	else
	{
		if(CheckOfficersPerk(pchar,"BasicCommerce"))	{ nCommerce += 2; }
	}

	price = price - price / (nCommerce*10.5);

	ref rRealShip = GetRealShip(st);

	if (sti(rRealShip.Stolen) == true) //проверка на ворованный
	{
    	price = makeint(price/4);
    }
    if (price < 0 && sti(_chr.Ship.Type) != SHIP_NOTUSED)
	{
	   price = 0;
	}

	return price;
}

// Метод вернет цену покупки корабля персонажа с учетом всех скилов (для верфи)
int GetShipBuyPrice(int iType, ref _shipyard)
{
	// boal учет скилов торговли 22.01.2004 -->
	float nCommerce   = GetSummonSkillFromNameToOld(GetMainCharacter(), SKILL_COMMERCE);

	if(CheckOfficersPerk(pchar,"Trader")) { nCommerce += 2; }
    if(CheckOfficersPerk(pchar,"AdvancedCommerce"))	{ nCommerce += 4; }
	else
	{
		if(CheckOfficersPerk(pchar,"BasicCommerce"))	{ nCommerce += 2; }
	}

    return makeint(GetShipPriceByType(iType, _shipyard) + GetShipPriceByType(iType, _shipyard)/(nCommerce*10));
    // boal 22.01.2004 <--
}

int GetSailRepairCost(int shipType, int repairPercent, ref _shipyard)
{
	float fConstanta = 2.0;
	float fSkillDepend = fConstanta + (SKILL_TO_OLD*2.0) - (GetSummonSkillFromNameToOld(pchar, SKILL_REPAIR) + GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE));
	fSkillDepend *= 0.1 + (MOD_SKILL_ENEMY_RATE * 0.01);
	float SailRepairCoeff = 1.0 * fSkillDepend;
	int shipPrice = GetShipPriceByType(shipType, _shipyard);
	if(shipPrice<=0) return 0;
	ref shref = GetRealShip(shipType);
	if(CheckAttribute(shref,"Tuning.GhostShip")) SailRepairCoeff *= 2;
	float scost = SailRepairCoeff * (shipPrice*SAIL_COST_PERCENT+99.0)/100.0;
	return makeint((scost*repairPercent+99.0)/100.0);
}

int GetHullRepairCost(int shipType,int repairPercent, ref _shipyard)
{
	float fConstanta = 4.0;
	float fSkillDepend = fConstanta + (SKILL_TO_OLD*1.75) - (GetSummonSkillFromNameToOld(pchar, SKILL_REPAIR) + GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE));
	fSkillDepend *= 0.1 + (MOD_SKILL_ENEMY_RATE * 0.01);
	float HullRepairCoeff = 1.0 * fSkillDepend;
	int shipPrice = GetShipPriceByType(shipType, _shipyard);
	if(shipPrice<=0) return 0;
	ref shref = GetRealShip(shipType);
	if(CheckAttribute(shref,"Tuning.GhostShip")) HullRepairCoeff *= 2;
	float scost = HullRepairCoeff * (shipPrice*HULL_COST_PERCENT+99.0)/100.0;
	return makeint((scost*repairPercent+99.0)/100.0);
}

int GetSailDamagePercent(ref _chr)
{
	return 100 - MakeInt(GetSailPercent(_chr));
}

int GetHullDamagePercent(ref _chr)
{
	return 100 - MakeInt(GetHullPercent(_chr));
}
///////////////////////////////////////////////////////////////   ВЕРФИ  <--
// палуба от типа корабля
string GetShip_deck(ref chr, bool map2sea)
{
	string ret, add;
	int    iType = sti(chr.Ship.Type);
	if (map2sea)
	{
	    ret = "Ship_deck_";
	}
	else
	{
	    ret = "Deck_Near_Ship_";
	}
	add = "Low"; // если нет типа
	if (iType != SHIP_NOTUSED)
	{
        ref rRealShip = GetRealShip(iType);

		add = rRealShip.DeckType;
	}

	return ret + add;
}

void MakeCloneShipDeck(ref chr, bool map2sea)
{
	ref rOrg, rClone;
	int iOrg, iClone;
    string locId, toLocId;

    locId = GetShip_deck(chr, map2sea);
    if (map2sea)
	{
	    toLocId = "Ship_deck";
	}
	else
	{
	    toLocId = "Deck_Near_Ship";
	}

	iOrg = FindLocation(locId);
	iClone = FindLocation(toLocId);

	if(iOrg < 0 || iClone < 0) {
        Trace("MakeCloneShipDeck error: iOrg " + iOrg + ", iClone " + iClone);
        return;
	}

	makeref(rOrg, Locations[iOrg]);
	makeref(rClone, Locations[iClone]);

	DeleteAttribute(rClone, "");
	CopyAttributes(rClone, rOrg);
	rClone.id = toLocId;
	rClone.index = iClone;
}

void MakeCloneFortBoarding(string fromLocId)
{
	ref rOrg, rClone;
	int iOrg, iClone;
    string toLocId;

    toLocId = "BOARDING_FORT";

	iOrg = FindLocation(fromLocId);
	iClone = FindLocation(toLocId);

	if(iOrg < 0 || iClone < 0) {
        Trace("MakeCloneFortBoarding error: iOrg " + iOrg + ", iClone " + iClone);
        return;
	}

	makeref(rOrg, Locations[iOrg]);
	makeref(rClone, Locations[iClone]);

	DeleteAttribute(rClone, "");
	CopyAttributes(rClone, rOrg);
	rClone.id = toLocId;
	rClone.index = iClone;

    rClone.type = "fort_attack";
	LAi_LocationFantomsGen(rClone, false);
	DeleteAttribute(rClone, "reload");
	//это подкручивание другого файла локаторов. там нет goto, soldiers и пр. есть rld и дополн.сундуки
	if (rClone.models.always.locators == "fortV_locators")
	{
		rClone.models.always.locators = "fortV_lAttack";
		rClone.models.always.fortV = "fortV_attack";
	}
	else
	{
		rClone.models.always.locators = "fortVRight_lAttack";
		rClone.models.always.fortV = "fortVRight_attack";
	}
	rClone.boarding.locatorNum = 15;
	rClone.boarding = "false";
	rClone.boarding.nextdeck = "Boarding_fortyard"; // Jason
	rClone.image = "loading\FortShturm_" + rand(2) + ".tga";
}

int GetPortManPrice(int Price, ref NPChar)
{
    if (!CheckAttribute(NPChar, "PortManPrice"))
	{
		NPChar.PortManPrice = (0.06 + frnd()*0.1);
	}
	return makeint(Price * stf(NPChar.PortManPrice) /10 ) * 10;
}

// ugeen --> альтернативный расчет стоянки корабля в ПУ
int GetPortManPriceExt(ref NPChar, ref chref)
{
	float fLeadership 	= 1.8 - GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/120.0; 	// учитываем авторитет
	float fCommerce 	= 1.8 - GetSummonSkillFromName(pchar, SKILL_COMMERCE)/120.0; 	// учитываем торговлю
	float fRelation 	= 1.0; 															// учитываем  - родная нация или нет

	if(sti(NPChar.nation) == GetBaseHeroNation()) fRelation = 0.5; 						// если нация родная- снижаем цену в два раза
	int price = makeint(100 * MOD_SKILL_ENEMY_RATE * 1.56 * sqr(6.7 - sti(RealShips[sti(chref.Ship.Type)].Class)) * (2 + 0.5 * GetNationRelation2MainCharacter(sti(NPChar.nation))) * fRelation * fLeadership * fCommerce);
	price = price + sti(chref.Ship.Crew.Quantity) * 10; // LEO: за каждого матроса платим по 10 золота

	return price;
}
//<-- альтернативный расчет стоянки корабля в ПУ

// Warship 31.05.09 Установка на корабль персонажа определенного паруса
// Путь относительно папки Textures
bool SetShipSailsFromFile(ref _char, String _sailTexturePath)
{
	ref realShip;
	int shipType = sti(_char.Ship.Type);

	if(shipType == SHIP_NOTUSED) // Есть ли корабль вообще
	{
		return false;
	}

	realShip = GetRealShip(shipType);

	realShip.EmblemedSails.normalTex = _sailTexturePath;

	return true;
}

string GetLocalShipAttrib(ref ship, string attrib)
{
	if (CheckAttribute(ship, attrib)) return ship.(attrib);
	return "";
}

bool CheckShipAttribute(ref ship, string attrib)
{
	if(CheckAttribute(ship, attrib)) return true;
	return false;
}

string GetBaseShipParamFromType(int iType, string _param)
{
	object rBaseShip = GetShipByType(iType);
	return rBaseShip.(_param);
}

//Mett: --> формула стоимости кораблей по ТТХ
int GetShipPriceByTTH(int iType, ref rChar)
{
	ref rRealShip = GetRealShip(iType);
	ref rBaseShip = GetShipByType(sti(rRealShip.BaseType));
	int iSumm = 100;//базовая стоимость sti(rBaseShip.price);
	int shipClass = sti(rRealShip.class);

	//корпус
	int hp_price = 1;
	switch(shipClass)
	{
		case 7: hp_price = 1; break;
		case 6: hp_price = 3; break;
		case 5: hp_price = 5; break;
		case 4: hp_price = 8; break;
		case 3: hp_price = 10; break;
		case 2: hp_price = 12; break;
		case 1: hp_price = 15; break;
	}
	int SummHP = sti(rRealShip.HP) * hp_price;

	//трюм
	int capacity_price = 1;
	switch(shipClass)
	{
		case 7: capacity_price = 1; break;
		case 6: capacity_price = 3; break;
		case 5: capacity_price = 5; break;
		case 4: capacity_price = 8; break;
		case 3: capacity_price = 10; break;
		case 2: capacity_price = 12; break;
		case 1: capacity_price = 15; break;
	}
	int SummCapacity = sti(rRealShip.Capacity) * capacity_price;

	//команда
	int crew_price = 1;
	switch(shipClass)
	{
		case 7: crew_price = 2; break;
		case 6: crew_price = 10; break;
		case 5: crew_price = 15; break;
		case 4: crew_price = 20; break;
		case 3: crew_price = 30; break;
		case 2: crew_price = 35; break;
		case 1: crew_price = 40; break;
	}
	int SummCrew = sti(rRealShip.MaxCrew) * crew_price;

	//калибр
	int caliber_price = 5000;
	switch(sti(rRealShip.MaxCaliber))
	{
		case 8: caliber_price = 1250; break;
		case 12: caliber_price = 2500; break;
		case 16: caliber_price = 7500; break;
		case 20: caliber_price = 11250; break;
		case 24: caliber_price = 15000; break;
		case 32: caliber_price = 30000; break;
		case 36: caliber_price = 40000; break;
		case 42: caliber_price = 75000; break;
		case 48: caliber_price = 150000; break;
	}
	int SummMaxCaliber = caliber_price;

	//количество пушек
	int cannon_price = 100;
	int iCannonsQuantity = 0;
	if(CheckAttribute(rRealShip, "CannonsQuantity"))
	{
		if(sti(rRealShip.CannonsQuantity) > 0)
		{
			if(CheckAttribute(rChar, "Ship.Cannons.Type"))
			{
				ref rCannon = GetCannonByType(sti(rChar.Ship.Cannons.Type));
				if (CheckAttribute(rCannon,"Cost")) cannon_price = sti(rCannon.Cost);
				else {cannon_price = 0; if (CurrentInterface != INTERFACE_SHIPYARD1 && CurrentInterface != INTERFACE_SHIPYARD2) log_info("ОШИБКА 1500-404 - сделайте скрин и отправьте разработчикам краткое описание ситуации и сохранение");}
				//меняю цену с 1500 на 0, чтобы цена корабля без пушек при заказе считалась правильно. - лог для отслеживания, что эта ветка кода только при заказе корабля используется и исправление ничего не сломало
			}
			else
			{
				cannon_price = 1500; //универсальное значение для NullCharacter
			}
			iCannonsQuantity = sti(rRealShip.CannonsQuantity);
		}
		else
		{
			cannon_price = 0;
		}
	}
	else
	{
		trace("GetShipPriceByTTH: у " + rRealShip.BaseName + " отсутствует атрибут CannonsQuantity");
	}
	int SummCannons = iCannonsQuantity * cannon_price; //2

	//бейдевинд
	int was_price = 10;
	switch(shipClass)
	{
		case 7: was_price = 6; break;
		case 6: was_price = 125; break;
		case 5: was_price = 312; break;
		case 4: was_price = 2500; break;
		case 3: was_price = 6250; break;
		case 2: was_price = 12500; break;
		case 1: was_price = 25000; break;
	}
	int SummWAS = stf(rRealShip.WindAgainstSpeed) * was_price;

	//мачты
	int mast_price = 10;
	switch(shipClass)
	{
		case 7: mast_price = 6; break;
		case 6: mast_price = 125; break;
		case 5: mast_price = 312; break;
		case 4: mast_price = 2500; break;
		case 3: mast_price = 6250; break;
		case 2: mast_price = 12500; break;
		case 1: mast_price = 25000; break;
	}
	int SummMast = makeint(mast_price/(stf(rRealShip.MastMultiplier)/2));

	//скорость
	int speed_price = 10;
	switch(shipClass)
	{
		case 7: speed_price = 8; break;
		case 6: speed_price = 50; break;
		case 5: speed_price = 100; break;
		case 4: speed_price = 250; break;
		case 3: speed_price = 1250; break;
		case 2: speed_price = 2500; break;
		case 1: speed_price = 5000; break;
	}
	int SummSpeed = stf(rRealShip.SpeedRate) * speed_price;

	//маневренность
	int turn_price = 10;
	switch(shipClass)
	{
		case 7: turn_price = 2; break;
		case 6: turn_price = 12; break;
		case 5: turn_price = 50; break;
		case 4: turn_price = 125; break;
		case 3: turn_price = 750; break;
		case 2: turn_price = 1500; break;
		case 1: turn_price = 3000; break;
	}
	int SummTurn = stf(rRealShip.TurnRate) * turn_price;

	iSumm += SummHP + SummCapacity + SummCrew + SummMaxCaliber + SummCannons + SummWAS + SummMast + SummSpeed + SummTurn;

	return iSumm;
}
//Mett: <-- формула стоимости кораблей по ТТХ

//<---Lipsar корабли по квесту Предложение Пирата
void CreatePGG_War(ref ch, int iNation, ref shipOwner)
{
	aref rShip;
	ref rMerch;
	int iType, cl, cl1, i, j;
	ref refShip;
	refShip = GetRealShip(sti(shipOwner.ship.Type));
	int storeArray1[SHIP_TYPES_QUANTITY];
	j = 0;
	switch(sti(refShip.Class))
	{
		case 7:
			cl = 3;
			cl1 = 15;
		break;
		case 6:
			cl = 3;
			cl1 = 15;
		break;
		case 5:
			cl = 15;
			cl1 = 28;
		break;
		case 4:
			cl = 28;
			cl1 = 52;
		break;
		case 3:
			if (MOD_SKILL_ENEMY_RATE == 10)
			{
				cl = 52;
				cl1 = 84;
			}
			else
			{
				cl = 28;
				cl1 = 52;
			}
		break;
		case 2:
			if (MOD_SKILL_ENEMY_RATE == 10)
			{
				cl = 84;
				cl1 = 105;
			}
			else
			{
				cl = 52;
				cl1 = 84;
			}
		break;
		case 1:
			if (MOD_SKILL_ENEMY_RATE == 10)
			{
				cl = 105;
				cl1 = 125;
			}
			else
			{
				cl = 84;
				cl1 = 105;
			}
		break;
	}
	switch (iNation)
	{
		case "0":
			for (i=cl;i<cl1;i++)
			{
				makearef(rShip,ShipsTypes[i].nation.england);
				if (rShip == true)
				{
					makeref(rMerch,ShipsTypes[i]);
					if(rMerch.Type.War == true)
					{
						storeArray1[j]= i;
						j++;
					}
				}
			}
		break;
		case "1":
			for (i=cl;i<cl1;i++)
			{
				makearef(rShip,ShipsTypes[i].nation.france);
				if (rShip == true)
				{
					makeref(rMerch,ShipsTypes[i]);
					if(rMerch.Type.War == true)
					{
						storeArray1[j]= i;
						j++;
					}
				}
			}
		break;
		case "2":
			for (i=cl;i<cl1;i++)
			{
				makearef(rShip,ShipsTypes[i].nation.spain);
				if (rShip == true)
				{
					makeref(rMerch,ShipsTypes[i]);
					if(rMerch.Type.War == true)
					{
						storeArray1[j]= i;
						j++;
					}
				}
			}
		break;
		case "3":
			for (i=cl;i<cl1;i++)
			{
				makearef(rShip,ShipsTypes[i].nation.holland);
				if (rShip == true)
				{
					makeref(rMerch,ShipsTypes[i]);
					if(rMerch.Type.War == true)
					{
						storeArray1[j]= i;
						j++;
					}
				}
			}
		break;
		case "4":
			for (i=cl;i<cl1;i++)
			{
				makearef(rShip,ShipsTypes[i].nation.pirate);
				if (rShip == true)
				{
					makeref(rMerch,ShipsTypes[i]);
					if(rMerch.Type.War == true)
					{
						storeArray1[j]= i;
						j++;
					}
				}
			}
		break;
	}
	iType = storeArray1[rand(j-1)];
	ch.Ship.Type = GenerateShipExt(iType, 1, ch);
}
void CreatePGG_Trade(ref ch, int iNation, ref shipOwner)
{
	aref rShip;
	ref rMerch;
	int iType, cl, cl1, i, j;
	ref refShip;
	refShip = GetRealShip(sti(shipOwner.ship.Type));
	int storeArray2[SHIP_TYPES_QUANTITY];
	j = 0;

	switch(sti(refShip.Class))
	{
		case 7:
			cl = 3;
			cl1 = 15;
		break;
		case 6:
			cl = 3;
			cl1 = 15;
		break;
		case 5:
			cl = 15;
			cl1 = 28;
		break;
		case 4:
			cl = 28;
			cl1 = 52;
		break;
		case 3:
			cl = 52;
			cl1 = 84;
		break;
		case 2:
			cl = 52;
			cl1 = 84;
		break;
		case 1:
			cl = 52;
			cl1 = 84;
		break;
	}
	i = cl;
	switch (iNation)
	{
		case "0":
			for (i=cl;i<cl1;i++)
			{
				makearef(rShip,ShipsTypes[i].nation.england);
				if (rShip == true)
				{
					makeref(rMerch,ShipsTypes[i]);
					if(rMerch.Type.Merchant == true)
					{
						storeArray2[j]= i;
						j++;
					}
				}
			}
		break;
		case "1":
			for (i=cl;i<cl1;i++)
			{
				makearef(rShip,ShipsTypes[i].nation.france);
				if (rShip == true)
				{
					makeref(rMerch,ShipsTypes[i]);
					if(rMerch.Type.Merchant == true)
					{
						storeArray2[j]= i;
						j++;
					}
				}
			}
		break;
		case "2":
			for (i;i<cl1;i++)
			{
				makearef(rShip,ShipsTypes[i].nation.spain);
				if (rShip == true)
				{
					makeref(rMerch,ShipsTypes[i]);
					if(rMerch.Type.Merchant == true)
					{
						storeArray2[j]= i;
						j++;
					}
				}
			}
		break;
		case "3":
			for (i=cl;i<cl1;i++)
			{
				makearef(rShip,ShipsTypes[i].nation.holland);
				if (rShip == true)
				{
					makeref(rMerch,ShipsTypes[i]);
					if(rMerch.Type.Merchant == true)
					{
						storeArray2[j]= i;
						j++;
					}
				}
			}
		break;
		case "4":
			for (i=cl;i<cl1;i++)
			{
				makearef(rShip,ShipsTypes[i].nation.pirate);
				if (rShip == true)
				{
					makeref(rMerch,ShipsTypes[i]);
					if(rMerch.Type.Merchant == true)
					{
						storeArray2[j]= i;
						j++;
					}
				}
			}
		break;
	}
	iType = storeArray2[rand(j-1)];

	ch.Ship.Type = GenerateShipExt(iType, 1, ch);
	ch.Ship.Mode = "trade";
}
//--->Lipsar корабли по квесту Предложение Пирата
void CreateFortDefenders(ref ch, int iNation)
{
	aref rShip;
	ref rMerch;
	int iType, cl, cl1, i, j;
	cl1 = 116;
	cl  = 84;
	int storeArray1[SHIP_TYPES_QUANTITY];
	j = 0;
	switch (iNation)
	{
		case "0":
			for (i=cl;i<cl1;i++)
			{
				makearef(rShip,ShipsTypes[i].nation.england);
				if (rShip == true)
				{
					makeref(rMerch,ShipsTypes[i]);
					if(rMerch.Type.War == true)
					{
						storeArray1[j]= i;
						j++;
					}
				}
			}
		break;
		case "1":
			for (i=cl;i<cl1;i++)
			{
				makearef(rShip,ShipsTypes[i].nation.france);
				if (rShip == true)
				{
					makeref(rMerch,ShipsTypes[i]);
					if(rMerch.Type.War == true)
					{
						storeArray1[j]= i;
						j++;
					}
				}
			}
		break;
		case "2":
			for (i=cl;i<cl1;i++)
			{
				makearef(rShip,ShipsTypes[i].nation.spain);
				if (rShip == true)
				{
					makeref(rMerch,ShipsTypes[i]);
					if(rMerch.Type.War == true)
					{
						storeArray1[j]= i;
						j++;
					}
				}
			}
		break;
		case "3":
			for (i=cl;i<cl1;i++)
			{
				makearef(rShip,ShipsTypes[i].nation.holland);
				if (rShip == true)
				{
					makeref(rMerch,ShipsTypes[i]);
					if(rMerch.Type.War == true)
					{
						storeArray1[j]= i;
						j++;
					}
				}
			}
		break;
		case "4":
			for (i=cl;i<cl1;i++)
			{
				makearef(rShip,ShipsTypes[i].nation.pirate);
				if (rShip == true)
				{
					makeref(rMerch,ShipsTypes[i]);
					if(rMerch.Type.War == true)
					{
						storeArray1[j]= i;
						j++;
					}
				}
			}
		break;
	}
	iType = storeArray1[rand(j-1)];
	ch.Ship.Type = GenerateShipExt(iType, 1, ch);
}
void CreateFortMerchants(ref ch, int iNation)
{
	aref rShip;
	ref rMerch;
	int iType, cl, cl1, i, j;
	int storeArray2[SHIP_TYPES_QUANTITY];
	j = 0;
	cl = 3;
	cl1 = 52;
	switch (iNation)
	{
		case "0":
			for (i=cl;i<cl1;i++)
			{
				makearef(rShip,ShipsTypes[i].nation.england);
				if (rShip == true)
				{
					makeref(rMerch,ShipsTypes[i]);
					if(rMerch.Type.Merchant == true)
					{
						storeArray2[j]= i;
						j++;
					}
				}
			}
		break;
		case "1":
			for (i=cl;i<cl1;i++)
			{
				makearef(rShip,ShipsTypes[i].nation.france);
				if (rShip == true)
				{
					makeref(rMerch,ShipsTypes[i]);
					if(rMerch.Type.Merchant == true)
					{
						storeArray2[j]= i;
						j++;
					}
				}
			}
		break;
		case "2":
			for (i;i<cl1;i++)
			{
				makearef(rShip,ShipsTypes[i].nation.spain);
				if (rShip == true)
				{
					makeref(rMerch,ShipsTypes[i]);
					if(rMerch.Type.Merchant == true)
					{
						storeArray2[j]= i;
						j++;
					}
				}
			}
		break;
		case "3":
			for (i=cl;i<cl1;i++)
			{
				makearef(rShip,ShipsTypes[i].nation.holland);
				if (rShip == true)
				{
					makeref(rMerch,ShipsTypes[i]);
					if(rMerch.Type.Merchant == true)
					{
						storeArray2[j]= i;
						j++;
					}
				}
			}
		break;
		case "4":
			for (i=cl;i<cl1;i++)
			{
				makearef(rShip,ShipsTypes[i].nation.pirate);
				if (rShip == true)
				{
					makeref(rMerch,ShipsTypes[i]);
					if(rMerch.Type.Merchant == true)
					{
						storeArray2[j]= i;
						j++;
					}
				}
			}
		break;
	}
	iType = storeArray2[rand(j-1)];
	ch.Ship.Type = GenerateShipExt(iType, 1, ch);
}

//Генерация топового корабля
int GenerateShipTop(int iBaseType, bool isLock, ref chr)
{
	string  attr, sCity;
	int 	i;
	aref 	refShip;
	float	Кdckyrd = 1.0;
	bool	isShipyard = false;

	int iShip = CreateBaseShip(iBaseType);

	if (iShip == -1)
	{
		return SHIP_NOTUSED;
	}

	ref rRealShip = GetRealShip(iShip);
	ref rBaseShip = GetShipByType(sti(rRealShip.BaseType));
	//Boyer change for ERAS2 #20170318-49
    if(CheckAttribute(rRealShip, "hullNums")) {
        int nHulls = sti(rRealShip.hullNums);
        nHulls -= 1;
        if(nHulls < 0) nHulls = 0;
        rRealShip.ship.upgrades.hull = 1 + rand(nHulls);
        //Trace("Hull nums = " + rRealShip.hullNums);
    }
    else {
        rRealShip.ship.upgrades.hull = 1 + rand(2);
    }
	rRealShip.ship.upgrades.sails = 1 + rand(2);  // только визуальная разница
	rRealShip.MastMultiplier = 1.3;

	int hullarmor;//реворк брони корпуса
	switch (sti(rRealShip.Class))
	{
		case 7: rRealShip.HullArmor = 8; break;
		case 6: rRealShip.HullArmor = 16; break;
		case 5: rRealShip.HullArmor = 20; break;
		case 4: rRealShip.HullArmor = 24; break;
		case 3: rRealShip.HullArmor = 28; break;
		case 2: rRealShip.HullArmor = 36; break;
		case 1: rRealShip.HullArmor = 46; break;
	}

	// ugeen --> если кораблик генерится на верфи, разброс статов более узкий
	if (CheckAttribute(chr, "City"))
	{
		sCity = chr.City;
		if(CheckCharacterID(chr, sCity + "_shipyarder"))
		{
			Кdckyrd 	= 0.8;
			isShipyard 	= true;
		}
	}
	// ugeen

	if (!CheckAttribute(rRealShip, "isFort"))
	{
		int iCaliber = sti(rRealShip.MaxCaliber);
		if (sti(rRealShip.Class) != 7 && !CheckAttribute(rRealShip, "QuestShip"))
		{  // чтоб не было баркаса с 16ф
			switch(iCaliber)
			{
				case 8:
					iCaliber = 0;
				break;
				case 12:
					iCaliber = 1;
				break;
				case 16:
					iCaliber = 2;
				break;
				case 20:
					iCaliber = 3;
				break;
				case 24:
					iCaliber = 4;
				break;
				case 32:
					iCaliber = 5;
				break;
				case 36:
					iCaliber = 6;
				break;
				case 42:
					iCaliber = 7;
				break;
			}
			//iCaliber = iCaliber - rand(1);
			iCaliber = iCaliber; //Jason: согласно новой системе орудий калибр должен быть постоянен, но пока поставим рандом на единицу меньше, а больше - нельзя по определению, на рез. тестов решим, фиксировать или рандомить
			if (iCaliber < 0) iCaliber = 0;
			if (sti(rRealShip.Class) == 1)
			{
				if (iCaliber > 7) iCaliber = 7;
			}
			else
			{
				if (iCaliber > 6) iCaliber = 6;
			}
			switch(iCaliber)
			{
				case 0:
					iCaliber = 8;
				break;
				case 1:
					iCaliber = 12;
				break;
				case 2:
					iCaliber = 16;
				break;
				case 3:
					iCaliber = 20;
				break;
				case 4:
					iCaliber = 24;
				break;
				case 5:
					iCaliber = 32;
				break;
				case 6:
					iCaliber = 36;
				break;
				case 7:
					iCaliber = 42;
				break;
			}
			rRealShip.MaxCaliber = iCaliber;
		}

		makearef(refShip, chr.Ship);
		ResetShipCannonsDamages(chr);

		// куда-нить запишем максимально возможное кол-во орудий (потом нужно будет, если захотим проапгрейдиться на этот счет)
		rRealShip.CannonsQuantityMax = sti(rRealShip.CannonsQuantity);
		// принципиальный момент ! нужно нулить обязательно левые стволы !
		for (i = 0; i < sti(rRealShip.rcannon); i++)
		{
			attr = "c" + i;
			rRealShip.Cannons.Borts.cannonr.damages.(attr) = 1.0;
			rRealShip.Cannons.Borts.cannonl.damages.(attr) = 1.0;
			rRealShip.Cannons.Borts.rcannon.damages.(attr) = 1.0;
			rRealShip.Cannons.Borts.lcannon.damages.(attr) = 1.0;

			refShip.Cannons.Borts.cannonr.damages.(attr) = 1.0;
			refShip.Cannons.Borts.cannonl.damages.(attr) = 1.0;
			refShip.Cannons.Borts.rcannon.damages.(attr) = 1.0;
			refShip.Cannons.Borts.lcannon.damages.(attr) = 1.0;
		}

		rRealShip.rcannon = sti(rRealShip.rcannon);
		rRealShip.lcannon = sti(rRealShip.lcannon);

		rRealShip.cannonr = sti(rRealShip.rcannon);
		rRealShip.cannonl = sti(rRealShip.lcannon);
		rRealShip.cannonf = sti(rRealShip.fcannon);
		rRealShip.cannonb = sti(rRealShip.bcannon);

		rRealShip.Cannons = sti(rRealShip.CannonsQuantityMax);
		rRealShip.CannonsQuantity = sti(rRealShip.Cannons);

		//а теперь вертаем стволы обратно в потребном нам количестве
		for (i = 0; i < sti(rRealShip.rcannon); i++)
		{
			attr = "c" + i;
			rRealShip.Cannons.borts.cannonr.damages.(attr) = 0.0;
			rRealShip.Cannons.borts.cannonl.damages.(attr) = 0.0;
			rRealShip.Cannons.borts.rcannon.damages.(attr) = 0.0;
			rRealShip.Cannons.borts.lcannon.damages.(attr) = 0.0;

			refShip.Cannons.borts.cannonr.damages.(attr) = 0.0;
			refShip.Cannons.borts.cannonl.damages.(attr) = 0.0;
			refShip.Cannons.borts.rcannon.damages.(attr) = 0.0;
			refShip.Cannons.borts.lcannon.damages.(attr) = 0.0;
		}

		for (i = 0; i < sti(rRealShip.fcannon); i++)
		{
			attr = "c" + i;
			rRealShip.Cannons.borts.cannonf.damages.(attr) = 0.0;
			rRealShip.Cannons.borts.fcannon.damages.(attr) = 0.0;
			refShip.Cannons.borts.cannonf.damages.(attr) = 0.0;
			refShip.Cannons.borts.fcannon.damages.(attr) = 0.0;
		}

		for (i = 0; i < sti(rRealShip.bcannon); i++)
		{
			attr = "c" + i;
			rRealShip.Cannons.borts.cannonb.damages.(attr) = 0.0;
			rRealShip.Cannons.borts.bcannon.damages.(attr) = 0.0;
			refShip.Cannons.borts.cannonb.damages.(attr) = 0.0;
			refShip.Cannons.borts.bcannon.damages.(attr) = 0.0;
		}

		refShip.Cannons.Borts.cannonl = sti(rRealShip.lcannon);
		refShip.Cannons.Borts.cannonr = sti(rRealShip.rcannon);
		refShip.Cannons.Borts.cannonf = sti(rRealShip.fcannon);
		refShip.Cannons.Borts.cannonb = sti(rRealShip.bcannon);

		refShip.Cannons.Borts.lcannon = sti(rRealShip.lcannon);
		refShip.Cannons.Borts.rcannon = sti(rRealShip.rcannon);
		refShip.Cannons.Borts.fcannon = sti(rRealShip.fcannon);
		refShip.Cannons.Borts.bcannon = sti(rRealShip.bcannon);

		refShip.Cannons = sti(rRealShip.Cannons);
		// <-- рэндом стволов

		rRealShip.Bonus_Capacity 	= makeint(sti(rRealShip.Capacity)*0.25);
		rRealShip.Bonus_HP 			= makeint(sti(rRealShip.HP)*0.25);
		rRealShip.Bonus_SpeedRate   = stf(rRealShip.SpeedRate)*0.25;
		rRealShip.Bonus_TurnRate    = stf(rRealShip.TurnRate)*0.25;

		rRealShip.WindAgainstSpeed 	= stf(rRealShip.WindAgainstSpeed)*1.25;
	}

	// to_do del -->
	rRealShip.BoardingCrew    = 0;
	rRealShip.GunnerCrew      = 0;
	rRealShip.CannonerCrew    = 0;
	rRealShip.OptCrew      = makeint(sti(rRealShip.OptCrew)*1.25);
	rRealShip.MaxCrew      = makeint(sti(rRealShip.OptCrew)*1.25);
	// to_do del <--

	if(CheckAttribute(rRealShip, "Bonus_Capacity"))	rRealShip.Capacity = sti(rRealShip.Capacity) + sti(rRealShip.Bonus_Capacity);
	if(CheckAttribute(rRealShip, "Bonus_HP")) rRealShip.HP = sti(rRealShip.HP) + sti(rRealShip.Bonus_HP);
	if(CheckAttribute(rRealShip, "Bonus_SpeedRate")) rRealShip.SpeedRate = stf(rRealShip.SpeedRate) + stf(rRealShip.Bonus_SpeedRate);
	if(CheckAttribute(rRealShip, "Bonus_TurnRate"))	rRealShip.TurnRate = stf(rRealShip.TurnRate) + stf(rRealShip.Bonus_TurnRate);

	SetCabinTypeEx(rRealShip, sti(rRealShip.Class)); //Выдача случайной каюты по классу не квестовым - Gregg

	rRealShip.Price	= GetShipPriceByTTH(iShip, chr); //(iDiffWeight + iDiffCapacity + iDiffMaxCrew*2 + iDiffMinCrew + fDiffSpeedRate*2 + iDiffTurnRate*2 + iDiffHP)*5 + sti(rRealShip.Price);

	if (sti(rRealShip.Price) <= 0) rRealShip.Price = 100;

	rRealShip.Stolen = isLock;  // ворованность
	rRealShip.soiling = 0;
	//if (rand(4)==0) GetRandomSpecialUpgrade(rRealShip);

	return iShip;
}
// -> ugeen

int GetShootDistance(ref chref, string ball)
{
	float distance = 0.0;
	ref	rCannon = GetCannonByType(sti(chref.Ship.Cannons.Type));
	distance = stf(rCannon.FireRange);
	switch(ball)
	{
		case "ball":
			if (CheckAttribute(chref, "perks.list.LongRangeShoot"))
			{
				distance = distance * 1.15*(1.0+GetCharacterSPECIALSimple(chref, SPECIAL_P)*0.02);
			}
			else
			{
				distance = distance * (1.0+GetCharacterSPECIALSimple(chref, SPECIAL_P)*0.02);
			}
		break;
		case "grape":
			if (CheckAttribute(chref, "perks.list.LongRangeShoot"))
			{
				distance = distance * 0.6 * 1.15*(1.0+GetCharacterSPECIALSimple(chref, SPECIAL_P)*0.02);
			}
			else
			{
				distance = distance * 0.6  * (1.0+GetCharacterSPECIALSimple(chref, SPECIAL_P)*0.02);
			}
		break;
		case "knippel":
			if (CheckAttribute(chref, "perks.list.LongRangeShoot"))
			{
				distance = distance * 0.9  * 1.15*(1.0+GetCharacterSPECIALSimple(chref, SPECIAL_P)*0.02);
			}
			else
			{
				distance = distance * 0.9  * (1.0+GetCharacterSPECIALSimple(chref, SPECIAL_P)*0.02);
			}
		break;
		case "bomb":
			if (CheckAttribute(chref, "perks.list.LongRangeShoot"))
			{
				distance = distance * 0.8  * 1.15*(1.0+GetCharacterSPECIALSimple(chref, SPECIAL_P)*0.02);
			}
			else
			{
				distance = distance * 0.8  * (1.0+GetCharacterSPECIALSimple(chref, SPECIAL_P)*0.02);
			}
		break;
	}
	return makeint(distance+0.5);
}
