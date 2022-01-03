#define FANTOM_SHIPS_QTY 150
#define INVALID_SHIP_TYPE			-1

ref Fantom_GetNextFantom()
{
	iNumFantoms++;
	return &Characters[FANTOM_CHARACTERS + iNumFantoms];
}

// -> ugeen 26.01.09
int Fantom_GenerateEncounterExt(string sGroupName, object oResult, int iEType, int iNumWarShips, int iNumMerchantShips, int iNation)
{
	aref	aWar, aMerchant;
	ref		rEnc;
	int		i;
	int		iWarClassMax, iWarClassMin, iMerchantClassMax, iMerchantClassMin;

	makeref(rEnc, EncountersTypes[iEType]);
	makearef(aWar, rEnc.War);
	makearef(aMerchant, rEnc.Merchant);

	if(iEType == ENCOUNTER_TYPE_BARREL || iEType == ENCOUNTER_TYPE_BOAT)
	{
		ref rFantom = GetFantomCharacter(iNumFantoms);

		DeleteAttribute(rFantom, "relation");
		DeleteAttribute(rFantom, "abordage_twice");
		DeleteAttribute(rFantom, "QuestDate");
		DeleteAttribute(rFantom, "ransom");

		rFantom.SeaAI.Group.Name = sGroupName;
		iNumFantoms++;
		return 0;
	}

	int iRank = sti(pchar.Rank);
	Encounter_GetClassesFromRank(iEType, iRank, &iMerchantClassMin, &iMerchantClassMax, &iWarClassMin, &iWarClassMax);

	int iFantomIndex, iShipType;

	for (i=0; i<iNumMerchantShips; i++)
	{
		iShipType = Fantom_GetShipTypeExt(iMerchantClassMin, iMerchantClassMax, "Merchant", sGroupName, "Trade", iEType, iNation );
		if (iShipType == INVALID_SHIP_TYPE) continue;
	}

	for (i=0; i<iNumWarShips; i++)
	{
		iShipType = Fantom_GetShipTypeExt(iWarClassMin, iWarClassMax, "War", sGroupName, "War", iEType, iNation);
		if (iShipType == INVALID_SHIP_TYPE) continue;
	}

	return iNumWarShips + iNumMerchantShips;
}

int Fantom_GetShipTypeExt(int iClassMin, int iClassMax, string sShipType, string sGroupName, string sFantomType, int iEncounterType, int iNation)
{
	int iShips[FANTOM_SHIPS_QTY];
	int i, iShipsNum;
	iShipsNum = 0;
	aref aNation;
	string sAttr;
	bool bOk;

	for (i=SHIP_TARTANE; i<=SHIP_SP_SANFELIPE; i++)  //энкаунтеры только до мановара, квестовые корабли отдельно
	{
		object rShip = GetShipByType(i);
		if (!checkAttribute(rship, "class"))
		{
		trace ("bad ship is: " + rship.name);
		}
		int iClass = MakeInt(rShip.Class);

		if (iClass > iClassMin) { continue; }
		if (iClass < iClassMax) { continue; }
		if (sti(rShip.CanEncounter) != true) { continue; }
		if (sti(rShip.Type.(sShipType)) != true) { continue; }
		bOk = false;
		if(CheckAttribute(rShip, "nation"))
		{
		makearef(aNation, rShip.nation);
		int q = GetAttributesNum(aNation);
		for(int j = 0; j < q; j++)
		{
		sAttr = GetAttributeName(GetAttributeN(aNation, j));
		if(GetNationTypeByName(sAttr) == iNation && rShip.nation.(sAttr) == true ) bOk = true;
		}
		}
		if(!bOk) { continue; }

		iShips[iShipsNum] = i;
		iShipsNum++;
	}
	if (iShipsNum==0)
	{
		Trace("Can't find ship type '" + sShipType + "' with ClassMin = " + iClassMin + " and ClassMax = " + iClassMax);
		return INVALID_SHIP_TYPE;
	}

	int iBaseShipType = iShips[rand(iShipsNum - 1)];

	ref rFantom = GetFantomCharacter(iNumFantoms);

	DeleteAttribute(rFantom, "relation");
	DeleteAttribute(rFantom, "abordage_twice");
	DeleteAttribute(rFantom, "QuestDate");
	DeleteAttribute(rFantom, "ransom");
	DeleteAttribute(rFantom, "DontRansackCaptain");

	rFantom.SeaAI.Group.Name = sGroupName;
	rFantom.Ship.Mode = sFantomType;
	rFantom.Charge.Type = GOOD_BALLS;

	iNumFantoms++;

	int iRealShipType = GenerateShipExt(iBaseShipType, 0, rFantom);

	rFantom.Ship.Type = iRealShipType;

	return iRealShipType;

}
// -> ugeen 26.01.09

int Fantom_GenerateEncounter(string sGroupName, object oResult, int iEType, int iNumWarShips, int iNumMerchantShips)
{
	aref	aWar, aMerchant;
	ref		rEnc;
	int		i;
	int		iWarClassMax, iWarClassMin, iMerchantClassMax, iMerchantClassMin;

	makeref(rEnc, EncountersTypes[iEType]);
	makearef(aWar, rEnc.War);
	makearef(aMerchant, rEnc.Merchant);

	int iRank = sti(pchar.Rank);
	Encounter_GetClassesFromRank(iEType, iRank, &iMerchantClassMin, &iMerchantClassMax, &iWarClassMin, &iWarClassMax);

	int iFantomIndex, iShipType;

	for (i=0; i<iNumMerchantShips; i++)
	{
		iShipType = Fantom_GetShipType(iMerchantClassMin, iMerchantClassMax, "Merchant");
		if (iShipType == INVALID_SHIP_TYPE) continue;
		Fantom_AddFantomCharacter(sGroupName, iShipType, "Trade", iEType);
	}

	for (i=0; i<iNumWarShips; i++)
	{
		iShipType = Fantom_GetShipType(iWarClassMin, iWarClassMax, "War");
		if (iShipType == INVALID_SHIP_TYPE) continue;
		Fantom_AddFantomCharacter(sGroupName, iShipType, "War", iEType);
	}

	return iNumWarShips + iNumMerchantShips;
}

int Fantom_GetShipType(int iClassMin, int iClassMax, string sShipType)
{
	int iShips[FANTOM_SHIPS_QTY];
	int i, iShipsNum;
	iShipsNum = 0;

	for (i=SHIP_TARTANE; i<=SHIP_SP_SANFELIPE; i++)  //энкаунтеры только до мановара, квестовые корабли отдельно
	{
		object rShip = GetShipByType(i);
		if (!checkAttribute(rship, "class"))
		{
			trace ("bad ship is: " + rship.name);
		}
		int iClass = MakeInt(rShip.Class);

		if (iClass > iClassMin) { continue; }
		if (iClass < iClassMax) { continue; }
		if (sti(rShip.CanEncounter) != true) { continue; }
		if (sti(rShip.Type.(sShipType)) != true) { continue; }
		iShips[iShipsNum] = i;
		iShipsNum++;
	}
	if (iShipsNum==0)
	{
		Trace("Can't find ship type '" + sShipType + "' with ClassMin = " + iClassMin + " and ClassMax = " + iClassMax);
		return INVALID_SHIP_TYPE;
	}

	int iBaseShipType = iShips[rand(iShipsNum - 1)];
	//trace(ShipsTypes[iBaseShipType].name);
	int iRealShipType = GenerateShip(iBaseShipType, 0);
	return iRealShipType;
}

// return new added fantom character
// мктод этот походу левый, тк перекрывается в сиа.с
void Fantom_AddFantomCharacter(string sGroupName, int iShipType, string sFantomType, int iEncounterType)
{
	ref rFantom = GetFantomCharacter(iNumFantoms);



	DeleteAttribute(rFantom, "relation");
	DeleteAttribute(rFantom, "abordage_twice");
	DeleteAttribute(rFantom, "QuestDate");
	DeleteAttribute(rFantom, "ransom");
	DeleteAttribute(rFantom, "DontRansackCaptain");

	//#20170912-02 Fix for RealShips/Character sails
    	DeleteAttribute(rFantom, "ship.sails");
    	//#20170918-01 Fix for Abordage.Enable
    	DeleteAttribute(rFantom, "Abordage.Enable");

	rFantom.SeaAI.Group.Name = sGroupName;
	rFantom.Ship.Type = iShipType;
	rFantom.Ship.Mode = sFantomType;
	rFantom.Charge.Type = GOOD_BALLS;

	iNumFantoms++;
}
// на деле этот метод бесполезен, тк золото в сундуке генерится в др месте, а то что, в к3 тут были распределения опыта и команды вообще позорище.
void Fantom_SetRandomMoney(ref rFantom, string sFantomType)
{
	// clear money from character
	rFantom.Money = 0;

	//GenerateBootyItems(rFantom); // to_do del
	if (!CheckAttribute(rFantom, "ship.type")) return; // fix

    int iShip = sti(rFantom.ship.type);
	if (iShip == SHIP_NOTUSED) return; // fix

	// clear money from character
	rFantom.Money = 0;

	// ship class
	int iSClass = GetCharacterShipClass(rFantom);

	switch (sFantomType)
	{
		case "trade":
			rFantom.Money = (10 - iSClass) * 100 + rand((10 - iSClass) * 800);
			return;
		break;
		case "war":
			rFantom.Money = (10 - iSClass) * 40 + rand((10 - iSClass) * 350);
			return;
		break;
		case "pirate":
		    rFantom.Money = (10 - iSClass) * 80 + rand((10 - iSClass) * 500);
			return;
		break;
	}
}

// boal перенес из ВМЛ
int Fantom_CalcSkill(ref rMainCharacter, string sSkill, int iShipClass, int iSkillMin, int iSkillMax, int iSClass7, int iSClass6, int iSClass5, int iSClass4, int iSClass3, int iSClass2, int iSClass1)
// Stone-D : It was all backwards!
{
	int iSkill = GetSummonSkillFromName(rMainCharacter, sSkill);
    // boal 15.03.04 -->
    int minSkillLevel = 0;
	iSkill = iSkill + iSkillMin + rand(iSkillMax - iSkillMin);
	switch (iShipClass)
	{
		case 1: minSkillLevel =  iSClass1; break;
		case 2: minSkillLevel =  iSClass2; break;
		case 3: minSkillLevel =  iSClass3; break;
		case 4: minSkillLevel =  iSClass4; break;
		case 5: minSkillLevel =  iSClass5; break;
		case 6: minSkillLevel =  iSClass6; break;
		case 7: minSkillLevel =  iSClass7; break;
	}
	minSkillLevel = minSkillLevel*10; // приведение скила к 1-100

    if (iSkill < minSkillLevel)	iSkill = minSkillLevel;
    // boal 15.03.04 <--
	if (iSkill < 1)		    	iSkill = 1;
	if (iSkill > SKILL_MAX)     iSkill = SKILL_MAX;
	return iSkill;
}

void Fantom_SetCannons(ref rFantom, string sFantomType)
{
	int iSClass = GetCharacterShipClass(rFantom);
	ref rShip = GetRealShip(GetCharacterShipType(rFantom));

 	int iCannonsType = sti(rShip.Cannon);
	string sCannonType = "cannon";
	int iCaliber = sti(rShip.MaxCaliber);
    // boal 03.02.2004 -->
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
	if (iCaliber > 0)
	{
		if (sFantomType == "trade" && iCaliber > 3) iCaliber = iCaliber - 1 - rand(1); // LEO: запомнить Lipsar поправил
	}
	else
	{
		iCaliber = 0;
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
	if (iCaliber < 8)
	{
	   iCaliber = 8;
	}
    // boal 03.02.2004 <--
	if (iCaliber > sti(rShip.MaxCaliber)) { iCaliber=sti(rShip.MaxCaliber); }

	switch (sFantomType)
	{
        case "trade":
            // boal 20.01.2004 -->
		    if (rand(1000) < 700)
		    {
			   sCannonType = "cannon";
			}
			else
			{
			   sCannonType = "culverine";
			}
		break;

		case "war":
			if (rand(1000) < 200)
		    {
			   sCannonType = "cannon";
			}
			else
			{
			   sCannonType = "culverine";
			}
		    break;

		case "pirate":
			if (rand(1000) < 400)
		    {
			   sCannonType = "cannon";
			}
			else
			{
			   sCannonType = "culverine";
			}
		    break;
		    // boal 20.01.2004 <--
	}

	if (sti(rShip.Cannon) == CANNON_TYPE_NONECANNON)
	{
		rFantom.Ship.Cannons.Type = CANNON_TYPE_NONECANNON;
		return;
	}
	if (iCaliber == 42)
	{
	    sCannonType = "cannon";
	}
	rFantom.Ship.Cannons.Type = GetCannonByTypeAndCaliber(sCannonType, iCaliber);
}

void Fantom_SetSails(ref rFantom, string sFantomType)
{
	rFantom.Ship.Sails.Gerald = false;
	if (sFantomType == "war") rFantom.Ship.Sails.Gerald = true;
}

void Fantom_SetBalls(ref rFantom, string sFantomType)
{
	float fKBalls = 7 - GetCharacterShipClass(rFantom);

	if (fKBalls <= 0) fKBalls = 0.7; // баркас
	switch (sFantomType)
	{
		case "war":
			fKBalls = fKBalls * 1.5;
		break;
		case "trade":
			fKBalls = fKBalls * 0.7;
		break;
		case "pirate":
			fKBalls = fKBalls * 1.0;
		break;
	}
	if (GetCharacterShipClass(rFantom) == 1) fKBalls = fKBalls * 1.6;	//много пушек, большой расход

    // boal 20.01.2004 -->
	Fantom_SetCharacterGoods(rFantom, GOOD_BALLS,    MakeInt(195 * fKBalls + rand(MakeInt(10 * fKBalls))), 0);
	Fantom_SetCharacterGoods(rFantom, GOOD_BOMBS,    MakeInt(180 * fKBalls + rand(MakeInt(20 * fKBalls))), 0);
	Fantom_SetCharacterGoods(rFantom, GOOD_KNIPPELS, MakeInt(90 * fKBalls + rand(MakeInt(10 * fKBalls))), 0);
	Fantom_SetCharacterGoods(rFantom, GOOD_GRAPES,   MakeInt(70 * fKBalls + rand(MakeInt(10 * fKBalls))), 0);
	Fantom_SetCharacterGoods(rFantom, GOOD_POWDER,   MakeInt(350 * fKBalls + rand(MakeInt(30 * fKBalls))), 0);

	Fantom_SetCharacterGoods(rFantom, GOOD_SAILCLOTH, 	MakeInt(4 * fKBalls + rand(MakeInt(10 * fKBalls))), 0);
	Fantom_SetCharacterGoods(rFantom, GOOD_PLANKS, 		MakeInt(3 * fKBalls + rand(MakeInt(20 * fKBalls))), 0);

    Fantom_SetCharacterGoods(rFantom, GOOD_FOOD, 		MakeInt(60 + 20 * fKBalls  + rand(MakeInt(8 * fKBalls))), 0);  //WW
    Fantom_SetCharacterGoods(rFantom, GOOD_WEAPON, 		MakeInt(20 + 12 * fKBalls + rand(MakeInt(8 * fKBalls))), 0);   //WW
    Fantom_SetCharacterGoods(rFantom, GOOD_RUM, 		MakeInt(60 + 12 * fKBalls  + rand(MakeInt(8 * fKBalls))), 0);  //WW
    Fantom_SetCharacterGoods(rFantom, GOOD_MEDICAMENT, 	MakeInt(20 + 8 * fKBalls + rand(MakeInt(10 * fKBalls))), 0);   //WW
    // boal 20.01.2004 <--
}

void Fantom_SetGoods(ref rFantom, string sFantomType)
{
 	int iMultiply = 10;
	int iRandMultiply = 1;
    int iShipClass = 7 - GetCharacterShipClass(rFantom);  // для баркаса = 0
    // boal 20.01.2004 -->
    int iStart = GOOD_PLANKS + 1;
	int iFinish = GOOD_CANNON_8 - iStart - 1; // исключая пушки
	int i, iGoods, iRandGoods, iGoodName, iGoodQuantity;
	float fModifikator = 0.0;
	bool isLock;
	bool bOk = false;

	if(CheckAttribute(rFantom, "situation")) bOk = true;

	switch (sFantomType)
    {
		case "war":  // на военных кораблях золото и серебро теперь не возят !!!!
		    iMultiply = (rand(5)+5) * (rand(iShipClass) + 1);
			iRandMultiply = 1 + rand(iShipClass);
			iRandGoods = rand(4)+1; // может быть от одного до 5-и видов товара (а не строго 3 как было раньше)
			isLock = 0; isLock = isLock || bOk;
			for (i = 0; i < iRandGoods; i++)
			{
			    Fantom_SetCharacterGoods(rFantom, iStart + rand(iFinish - 2), iMultiply * rand(iRandMultiply * 3), isLock);
			}
		break;
		case "trade":
			if (CheckAttribute(rFantom, "RealEncounterType") && sti(rFantom.RealEncounterType) == ENCOUNTER_TYPE_ESCORT_LARGE)
			{
				//генерим товар (может быть до 12-и видов )
				iGoods = rand(6) + 6; // в больших торговых  караванах  до 12-и видов товара
				fModifikator = 0.4 + 12.0/iGoods;
				iMultiply = (rand(10)+iGoods*3) * (rand(iShipClass) + 4);
				iRandMultiply = 2 + rand(iShipClass);
				if (MOD_SKILL_ENEMY_RATE < rand(12))
				{
    					iFinish = GOOD_CANNON_8 - iStart - 1;
				}
				else
				{
					iFinish = GOOD_GOLD - iStart - 1;
				}
				for (i = 0; i < iGoods; i++)
				{
					iGoodName = iStart + rand(iFinish);
					iGoodQuantity = makeint(fModifikator * iMultiply * (1 + rand(iRandMultiply * 3)));
					if(iGoodName == GOOD_GOLD || iGoodName == GOOD_SILVER)
					{
						iRandMultiply = 2 + rand(iShipClass);
						iMultiply = (rand(10)+ 10) * (rand(iShipClass) + 2);
						iGoodQuantity = makeint((fModifikator * 50 + iMultiply * (1 + rand(iRandMultiply * 3)))/(1.2 * MOD_SKILL_ENEMY_RATE));
						if(iGoodQuantity < 1) iGoodQuantity = 1;
						isLock = 1;
						Fantom_SetCharacterGoods(rFantom, iGoodName, iGoodQuantity, isLock);
					}
					else
					{
						isLock = 0;
						Fantom_SetCharacterGoods(rFantom, iGoodName, iGoodQuantity, isLock);
					}
				}
			}
			else
			{
				iGoods = rand(4) + 4; // у обычных купчишек до 8-и видов товара
				fModifikator = 0.2 + 8.0/iGoods;
				if (CheckAttribute(rFantom, "RealEncounterType") && sti(rFantom.RealEncounterType) == ENCOUNTER_TYPE_MERCHANT_LARGE)
				{
					iGoods = rand(6) + 6; // в торговых  караванах  до 12-и видов товара
					fModifikator = 0.3 + 12.0/iGoods;
				}
				iMultiply = (rand(10)+iGoods*3) * (rand(iShipClass) + 4);
				iRandMultiply = 2 + rand(iShipClass);
				if (MOD_SKILL_ENEMY_RATE < rand(12))
				{
    					iFinish = GOOD_CANNON_8 - iStart - 1;
				}
				else
				{
					iFinish = GOOD_GOLD - iStart - 1;
				}
				for (i = 0; i < iGoods; i++)
				{
					iGoodName = iStart + rand(iFinish);
					iGoodQuantity = makeint(fModifikator * iMultiply * (1+rand(iRandMultiply * 3)));
					if(iGoodName == GOOD_GOLD || iGoodName == GOOD_SILVER)
					{
						iRandMultiply = 2 + rand(iShipClass);
						iMultiply = (rand(10)+ 5) * (rand(iShipClass) + 2);
						iGoodQuantity = makeint((fModifikator * 50 + iMultiply * (1 + rand(iRandMultiply * 3)))/(1.1 * MOD_SKILL_ENEMY_RATE));
						if(iGoodQuantity < 1) iGoodQuantity = 1;
						isLock = 1; isLock = isLock || bOk;
						Fantom_SetCharacterGoods(rFantom, iGoodName, iGoodQuantity, isLock);
					}
					else
					{
						isLock = 0; isLock = isLock || bOk;
						Fantom_SetCharacterGoods(rFantom, iGoodName, iGoodQuantity, isLock);
					}
				}
			}
		break;
		case "pirate":
			fModifikator = 1.2;
			iMultiply = (rand(10)+3) * (rand(iShipClass) + 1);
			iRandMultiply = 2 + rand(iShipClass);
			iRandGoods = rand(5)+1;
			if (MOD_SKILL_ENEMY_RATE < rand(12))
			{
    				iFinish = GOOD_CANNON_8 - iStart - 1;
			}
			else
			{
				iFinish = GOOD_GOLD - iStart - 1;
			}
			for (i = 0; i < iRandGoods; i++)
			{
				iGoodName = iStart + rand(iFinish);
				iGoodQuantity = makeint(fModifikator * iMultiply * (1+rand(iRandMultiply * 3)));
				if(iGoodName == GOOD_GOLD || iGoodName == GOOD_SILVER)
				{
						iRandMultiply = 2 + rand(iShipClass);
						iMultiply = (rand(10)+ 30) * (rand(iShipClass) + 2);
						iGoodQuantity = makeint((fModifikator * 50 + iMultiply * (1 + rand(iRandMultiply * 3)))/(0.9 * MOD_SKILL_ENEMY_RATE));
						if(iGoodQuantity < 1) iGoodQuantity = 1;
						isLock = 1; isLock = isLock || bOk;
						Fantom_SetCharacterGoods(rFantom, iGoodName, iGoodQuantity, isLock);
				}
				else
				{
					isLock = 0; isLock = isLock || bOk;
					Fantom_SetCharacterGoods(rFantom, iGoodName, iGoodQuantity, isLock);
				}
			}
		break;
	}
    // boal 20.01.2004 <--
    // есть еще осталось место, то дать запасных орудий в трюм -->
    iMultiply = GetCannonGoodsIdxByType(sti(rFantom.Ship.Cannons.Type));
    if (iMultiply != -1)
    {
    	iRandMultiply = rand(6) - 2;  // 0..4 пушки
    	if (iRandMultiply > 0)
    	{
    		Fantom_SetCharacterGoods(rFantom, iMultiply, iRandMultiply, 0);
    	}
    }
    // есть еще осталось место, то дать запасных орудий в трюм <--
	RecalculateCargoLoad(rFantom);
}

void Fantom_SetGoodsOld(ref rFantom, string sFantomType)
{
 	int iMultiply = 10;
	int iRandMultiply = 1;
    int iShipClass = 7 - GetCharacterShipClass(rFantom);  // для баркаса = 0
    // boal 20.01.2004 -->
    int iStart = GOOD_PLANKS + 1;
    int iFinish = GOOD_GOLD - iStart - 1; // исключая пушки, серебро и золото
    int i, iGoods;

    // разрешим золото от сложности
    if (MOD_SKILL_ENEMY_RATE < rand(12))
    {
    	iFinish = GOOD_CANNON_8 - iStart - 1;
    }
	switch (sFantomType)
	{
		case "war":
		    iMultiply = (rand(5)+5) * (rand(iShipClass) + 1);
			iRandMultiply = 1 + rand(iShipClass);
			for (i = 0; i < 3; i++)
			{
			    Fantom_SetCharacterGoods(rFantom, iStart + rand(iFinish), iMultiply * rand(iRandMultiply * 3), 0);
			}
		break;
		case "trade":
			iGoods = 8;
			if (CheckAttribute(rFantom, "RealEncounterType") && sti(rFantom.RealEncounterType) == ENCOUNTER_TYPE_ESCORT_LARGE)
			{
                iGoods = 12;
                // золото, если повезет
                if (MOD_SKILL_ENEMY_RATE < rand(12))
                {
					iMultiply = (rand(10)+ 10) * (rand(iShipClass) + 1);
	            	iRandMultiply = 1 + rand(iShipClass);
					if (rand(1) == 0)
					{
						Fantom_SetCharacterGoods(rFantom, GOOD_GOLD, 50 + iMultiply * (1 + rand(iRandMultiply * 3)), 1);
					}
					else
					{
			        	Fantom_SetCharacterGoods(rFantom, GOOD_SILVER, 100 + iMultiply * (1 + rand(iRandMultiply * 3)), 1);
			        }
		        }
			}

			if (CheckAttribute(rFantom, "RealEncounterType") && sti(rFantom.RealEncounterType) == ENCOUNTER_TYPE_MERCHANT_LARGE)
            {
                iGoods = 11;
            }
			iMultiply = (rand(10)+iGoods*3) * (rand(iShipClass) + 4);
        	iRandMultiply = 2 + rand(iShipClass);
			for (i = 0; i < iGoods; i++)
			{
			    Fantom_SetCharacterGoods(rFantom, iStart + rand(iFinish), iMultiply * (1+rand(iRandMultiply * 3)), 0);
			}
		break;
		case "pirate":
			iMultiply = (rand(10)+3) * (rand(iShipClass) + 1);
			iRandMultiply = 2 + rand(iShipClass);
			for (i = 0; i < 4; i++)
			{
			    Fantom_SetCharacterGoods(rFantom, iStart + rand(iFinish), iMultiply * rand(iRandMultiply * 3), 0);
			}
		break;
	}
    // boal 20.01.2004 <--
    // есть еще осталось место, то дать запасных орудий в трюм -->
    iMultiply = GetCannonGoodsIdxByType(sti(rFantom.Ship.Cannons.Type));
    if (iMultiply != -1)
    {
    	iRandMultiply = rand(6) - 2;  // 0..4 пушки
    	if (iRandMultiply > 0)
    	{
    		Fantom_SetCharacterGoods(rFantom, iMultiply, iRandMultiply, 0);
    	}
    }
    // есть еще осталось место, то дать запасных орудий в трюм <--
	RecalculateCargoLoad(rFantom);
}
// доработал метод, теперь возвращает сколько взял
int Fantom_SetCharacterGoods(ref rFantom, int iGoods, int iQuantity, bool isLock)
{
	if (iQuantity == 0) { return 0; }

	string sGood = Goods[iGoods].name;
	int iFreeQuantity = GetGoodQuantityByWeight( iGoods, GetCargoFreeSpace(rFantom) );
	if (iFreeQuantity < 0) { iFreeQuantity = 0; }

	if (iQuantity > iFreeQuantity) { iQuantity = iFreeQuantity; }
    rFantom.Ship.Cargo.Goods.(sGood) = iQuantity;
	if(isLock) {rFantom.Ship.Cargo.Goods.(sGood).Lock = true;}
	RecalculateCargoLoad(rFantom);
	return iQuantity;
}

// опыт матросов
void Fantom_SetRandomCrewExp(ref rFantom, string sFantomType)
{
    if (!CheckAttribute(rFantom, "ship.type")) return; // fix

	int iShip = sti(rFantom.ship.type);
	if (iShip == SHIP_NOTUSED) return; // fix

	// ship class
	int iSClass = GetCharacterShipClass(rFantom);

	switch (sFantomType)
	{
		case "trade":
			rFantom.Ship.Crew.Exp.Sailors   = 20 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(70);
			rFantom.Ship.Crew.Exp.Cannoners = 20 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(70);
			rFantom.Ship.Crew.Exp.Soldiers  = 20 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(70);
		break;
		case "war":
			rFantom.Ship.Crew.Exp.Sailors   = 30 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(60);
			rFantom.Ship.Crew.Exp.Cannoners = 30 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(60);
			rFantom.Ship.Crew.Exp.Soldiers  = 30 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(60);
		break;
		case "pirate":
		    rFantom.Ship.Crew.Exp.Sailors   = 35 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(55);
			rFantom.Ship.Crew.Exp.Cannoners = 35 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(55);
			rFantom.Ship.Crew.Exp.Soldiers  = 35 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(55);
		break;
	}
}

void Fantom_SetQuestSitiation(ref rFantom, string sFantomType)
{
	string sSituation;
	bool CanGenerateSituation = false;
	if (!CheckAttribute(rFantom, "ship.type")) return;

	int iShip = sti(rFantom.ship.type);
	if (iShip == SHIP_NOTUSED) return;

	switch (sFantomType)
	{
		case "pirate": // пираты или ДУ
			if(rand(100) < 5)
			{
				sSituation = "Explosion";
				CanGenerateSituation = true;
			}
		break;
		case "hunter": // ОЗГ
			if(rand(100) < 5)
			{
				sSituation = "Explosion";
				CanGenerateSituation = true;
			}
		break;
		case "war": // военные корабли
			if(rand(100) < 5)
			{
				sSituation = "Explosion";
				CanGenerateSituation = true;
			}
		break;
		case "trade": // торговцы
			if(rand(100) < 5)
			{
				sSituation = "Epidemy";
				CanGenerateSituation = true;
			}
		break;
	}
	if(CanGenerateSituation == true)
	{
		rFantom.situation = sSituation;
		rFantom.situation.type = sFantomType;
		rFantom.DontRansackCaptain = true; // Врагу не сдается наш гордый Варяг !!
	}
}

// ugeen 03.06.09 - вероятность корабликов быть проапгрейженными на 1, 2 ...  все параметры
void Fantom_SetUpgrade(ref rFantom, string sFantomType)
{
	if (!CheckAttribute(rFantom, "ship.type")) return; // fix

	int iShip = sti(rFantom.ship.type);
	if (iShip == SHIP_NOTUSED) return; // fix

	// ship class
	int iSClass = GetCharacterShipClass(rFantom);
	int i = rand(100);

	switch (sFantomType)
	{
		case "pirate":   // апгрейдим параметр(ы)  шипа пиратских случаек
			if(i < (7 - iSClass)*4)
			{
				GenerateShipUpgradeParameters(rFantom);
			}
		break;
		case "hunter":   // апгрейдим параметр(ы) шипа ДУ или ОЗГов
			if(i < ((7 - iSClass)*4 +10))
			{
				GenerateShipUpgradeParameters(rFantom);
			}
		break;
	}
}

void GenerateShipUpgradeParameters(ref rFantom)
{
	int i = rand(100);

	if(i < 30)
	{
		UpgradeShipParameter(rFantom, "SpeedRate");
		return;
	}
	if((i >= 30) && (i < 45))
	{
		UpgradeShipParameter(rFantom, "SpeedRate");
		if(rand(1) == 0)
		{
			UpgradeShipParameter(rFantom, "TurnRate");
		}
		else
		{
			UpgradeShipParameter(rFantom, "WindAgainstSpeed");
		}
		return;
	}
	if((i >= 45) && (i < 60))
	{
		UpgradeShipParameter(rFantom, "SpeedRate");
		UpgradeShipParameter(rFantom, "TurnRate");
		UpgradeShipParameter(rFantom, "WindAgainstSpeed");
		if(rand(1) == 0)
		{
			UpgradeShipParameter(rFantom, "Capacity");
		}
		else
		{
			UpgradeShipParameter(rFantom, "MaxCrew");
		}
		return;
	}
	if((i >= 60) && (i < 75))
	{
		UpgradeShipParameter(rFantom, "SpeedRate");
		UpgradeShipParameter(rFantom, "TurnRate");
		UpgradeShipParameter(rFantom, "WindAgainstSpeed");
		UpgradeShipParameter(rFantom, "Capacity");
		UpgradeShipParameter(rFantom, "MaxCrew");
		if(rand(1) == 0)
		{
			UpgradeShipParameter(rFantom, "Cannons");
		}
		else
		{
			UpgradeShipParameter(rFantom, "HP");
		}
		return;
	}
	if((i >= 75) && (i < 80))
	{
		UpgradeShipParameter(rFantom, "SpeedRate");
		UpgradeShipParameter(rFantom, "TurnRate");
		UpgradeShipParameter(rFantom, "WindAgainstSpeed");
		UpgradeShipParameter(rFantom, "Capacity");
		UpgradeShipParameter(rFantom, "MaxCrew");
		UpgradeShipParameter(rFantom, "Cannons");
		UpgradeShipParameter(rFantom, "HP");
		return;
	}
	if(i >=80)
	{
		int irand = rand(7);
		if(irand == 0) UpgradeShipParameter(rFantom, "SpeedRate");
		if(irand == 1) UpgradeShipParameter(rFantom, "TurnRate");
		if(irand == 2) UpgradeShipParameter(rFantom, "WindAgainstSpeed");
		if(irand == 3) UpgradeShipParameter(rFantom, "Capacity");
		if(irand == 4) UpgradeShipParameter(rFantom, "MaxCrew");
		if(irand == 5) UpgradeShipParameter(rFantom, "Cannons");
		if(irand == 6) UpgradeShipParameter(rFantom, "HP");
	}
}

void UpgradeShipParameter(ref _chr, string _param)
{
	ref 	shTo;
	int 	iCaliber;

	shTo = &RealShips[sti(_chr.Ship.Type)];

	switch(_param)
	{
		case "SpeedRate":

			if(!CheckAttribute(shTo, "Tuning.SpeedRate"))
			{
				if(!CheckAttribute(shTo, "Bonus_SpeedRate"))
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) + stf(shTo.SpeedRate)/5.0);
				}
				//else
				//{
				//	shTo.SpeedRate        = (stf(shTo.SpeedRate) - stf(shTo.Bonus_SpeedRate)) * 1.2 + stf(shTo.Bonus_SpeedRate);
				//}
				shTo.Tuning.SpeedRate = true;
			}

		break;

		case "TurnRate":

			if(!CheckAttribute(shTo, "Tuning.TurnRate"))
			{
				if(!CheckAttribute(shTo, "Bonus_TurnRate"))
				{
					shTo.TurnRate        = (stf(shTo.TurnRate) + stf(shTo.TurnRate)/5.0);
				}
				//else
				//{
				//	shTo.TurnRate        = (stf(shTo.TurnRate) - stf(shTo.Bonus_TurnRate)) * 1.2 + stf(shTo.Bonus_TurnRate);
				//}
				shTo.Tuning.TurnRate = true;
			}

		break;

		case "HP":

			if(!CheckAttribute(shTo, "Tuning.HP"))
			{
				if(!CheckAttribute(shTo, "Bonus_HP"))
				{
					shTo.HP        = sti(shTo.HP) + makeint(sti(shTo.HP)/5);
				}
				//else
				//{
				//	shTo.HP        = makeint((sti(shTo.HP) - sti(shTo.Bonus_HP)) * 1.2 + sti(shTo.Bonus_HP));
				//}
				shTo.Tuning.HP = true;
			}

		break;

		case "WindAgainstSpeed":

			if(!CheckAttribute(shTo, "Tuning.WindAgainst"))
			{
				shTo.WindAgainstSpeed   = FloatToString(stf(shTo.WindAgainstSpeed) + 0.5* stf(shTo.WindAgainstSpeed) / stf(shTo.Class) + 0.005, 2);
				shTo.Tuning.WindAgainst = true;
			}

		break;

		case "Capacity":

			if(!CheckAttribute(shTo, "Tuning.Capacity"))
			{
				if(!CheckAttribute(shTo, "Bonus_Capacity"))
				{
					shTo.Capacity        = sti(shTo.Capacity) + makeint(sti(shTo.Capacity)/5);
				}
				//else
				//{
				//	shTo.Capacity        = makeint((sti(shTo.Capacity) - sti(shTo.Bonus_Capacity)) * 1.2 + sti(shTo.Bonus_Capacity));
				//}
				shTo.Tuning.Capacity = true;
			}

		break;

		case "MaxCrew":

			if(!CheckAttribute(shTo, "Tuning.MaxCrew"))
			{
				shTo.MaxCrew        = sti(shTo.MaxCrew) + makeint(sti(shTo.MaxCrew)/5);
				shTo.Tuning.MaxCrew = true;
				SetCrewQuantityFull(_chr);
			}

		break;

		case "Cannons":

			if(!CheckAttribute(shTo, "Tuning.Cannon"))
			{
				iCaliber = sti(shTo.MaxCaliber);
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
				}
				iCaliber = iCaliber + 1;
				if (iCaliber > 6) iCaliber = 6;
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
				}
				if (iCaliber > sti(shTo.MaxCaliber))
				{
					iCaliber=sti(shTo.MaxCaliber);
				}
				shTo.MaxCaliber = iCaliber;
				shTo.Tuning.Cannon = true;
			}

		break;
	}
}
// ugeen

// eddy. подбор типа корабля для фантома от ранга и нац. принадлежности
void SetShipToFantom(ref _chr, string _type, bool _setgoods)
{
	int ShipType;
	int Nation = sti(_chr.nation);
	int Rank = sti(pchar.rank);
	switch (_type)
	{
		case "trade":
			if (Rank >= 1 && Rank <= 5){ShipType = 3 + rand(11);} // 6 класс
			if (Rank >= 5 && Rank <= 10){ShipType = 3 + rand(24);} // 6 - 5 класс
			if (Rank >= 10 && Rank <= 15){ShipType = 15 + rand(36);} // 5 - 4 класс
			if (Rank >= 15 && Rank <= 20){ShipType = 28 + rand(55);} // 4 - 3 класс
			if (Rank >= 20 && Rank <= 30){ShipType = 52 + rand(52);} // 3 - 2 класс
			if (Rank > 30){	ShipType = 84 + rand(40);} // 2 - 1 класс
		break;
		case "pirate":
			if (Rank >= 1 && Rank <= 5){ShipType = 3 + rand(11);} // 6 класс
			if (Rank >= 5 && Rank <= 10){ShipType = 3 + rand(24);} // 6 - 5 класс
			if (Rank >= 10 && Rank <= 15){ShipType = 15 + rand(36);} // 5 - 4 класс
			if (Rank >= 15 && Rank <= 20){ShipType = 28 + rand(55);} // 4 - 3 класс
			if (Rank >= 20 && Rank <= 30){ShipType = 52 + rand(52);} // 3 - 2 класс
			if (Rank > 30){	ShipType = 84 + rand(40);} // 2 - 1 класс
		break;-
	}
	_chr.Ship.Type = GenerateShipExt(ShipType, true, _chr);
	SetRandomNameToShip(_chr);
    SetBaseShipData(_chr);
    SetCrewQuantityFull(_chr);
    Fantom_SetCannons(_chr, _type);
    Fantom_SetBalls(_chr, _type);
	Fantom_SetUpgrade(_chr, _type);

    if (_setgoods)
    {
        Fantom_SetGoods(_chr, _type);
    }
}
