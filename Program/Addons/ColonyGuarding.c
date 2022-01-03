							/* Охрана колонии с моря */

void SetStartColonyGuarding()
{
	ref PChar = GetMainCharacter();

	PChar.Colony.Guardians.Hovernor = "";

	string sShip = "";
	for(int i=1; i <= 4; i++)
	{
		sShip = "Ship" + i;
		PChar.Colony.Guardians.(sShip) = -1;
		PChar.Colony.Guardians.(sShip).Active = false;
	}

	PChar.Colony.Guardians.BaseComplete = false;
	PChar.Colony.Guardians.BaseComplete.First = true;

	PChar.Colony.Guardians.Colony.AutoCrewHire = false;
	PChar.Colony.Guardians.Mines.AutoCrewHire = false;
	PChar.Colony.Guardians.Plantation.AutoCrewHire = false;
}

int FindCaimanGuardingNum(ref chr)
{
	if(!CheckAttribute(chr, "id"))
	{
		return -1;
	}

	string sShip = "";

	for(int i=1; i<=4; i++)
	{
		sShip = "Ship" + i;

		if(sti(PChar.Colony.Guardians.(sShip)) == GetCharacterIndex(chr.id))
		{
			return i;
		}
	}

	return -1;
}

int GetCostForBaseCompletationAllGuards()
{
	int iBaseCost = 10000;
	int iCost = 0;

	string sShip = "";
	ref chr, rShip;
	int iChar = 0;
	int iClass = 7;

	for(int i=1; i <= 4; i++)
	{
		sShip = "Ship" + i;

		if(PChar.Colony.Guardians.(sShip) != -1 && PChar.Colony.Guardians.(sShip).Active == true)
		{
			iChar = sti(PChar.Colony.Guardians.(sShip));
			chr = &Characters[iChar];
			rShip = GetRealShip(sti(chr.Ship.Type));

			iClass = 1;
			if(CheckAttribute(rShip, "Class"))
			{
				iClass = sti(rShip.Class)
			}

			iBaseCost = 20000 / iClass;
			iCost += iBaseCost;
		}
	}

	return iCost;
}

void BaseCompletationColonyGuards()
{
	RepairAllGuardShips();

	if(PChar.Colony.Guardians.BaseComplete == false)
	{
		return;
	}

	if(GetColonyGuardsShipsQuantity() < 1)
	{
		return;
	}

	int iCost = GetCostForBaseCompletationAllGuards();
	int iColonyMoney = sti(PChar.ColonyBuilding.Money);

	if(iColonyMoney < iCost)
	{
		Log_InfoS("Ваша колония не имеет достаточных средств, чтобы обеспечить базовое комплектование кораблей охраны береговой линии.");
		return;
	}
	else
	{
		Log_InfoS("Все корабли охраны береговой линии были укомплектованы.");
	}

	ChangeColonyMoney(-iCost, false);

	string sShip = "";
	ref chr;
	int iChar = 0;

	for(int i=1; i <= 4; i++)
	{
		sShip = "Ship" + i;

		if(PChar.Colony.Guardians.(sShip) != -1)
		{
			iChar = sti(PChar.Colony.Guardians.(sShip));
			chr = &Characters[iChar];

			SetBaseShipData(chr);
			SetCrewQuantity(chr, GetOptCrewQuantity(chr));
			SetCharacterGoods(chr, GOOD_BALLS, 1000);
			SetCharacterGoods(chr, GOOD_GRAPES, 1000);
			SetCharacterGoods(chr, GOOD_KNIPPELS, 1000);
			SetCharacterGoods(chr, GOOD_BOMBS, 1000);
			SetCharacterGoods(chr, GOOD_POWDER, 4000);
			SetCharacterGoods(chr, GOOD_FOOD, 2000);
			SetCharacterGoods(chr, GOOD_WEAPON, 1000);
			SetCharacterGoods(chr, GOOD_MEDICAMENT, 1000);
		}
	}
}

void RepairAllGuardShips()
{
    	int iChar;
	ref chr;
	string sShip = "";
	for (int i=1; i <= 4; i++)
	{
		sShip = "Ship" + i;

		if(PChar.Colony.Guardians.(sShip) != -1)
		{
			iChar = sti(PChar.Colony.Guardians.(sShip));
			chr = &Characters[iChar];

			chr.ship.hp = GetCharacterShipHP(chr);
			DeleteAttribute(chr, "ship.blots");

			chr.ship.sp = GetCharacterShipSP(chr);
			DeleteAttribute(chr, "ship.sails");
			DeleteAttribute(chr, "ship.masts");

			/*
			ProcessHullRepair(chr, 100.0);
			ProcessSailRepair(chr, 100.0);
			DeleteAttribute(chr, "ship.blots");
			DeleteAttribute(chr, "ship.sails");
			DeleteAttribute(chr, "ship.masts");
			*/

			//RepairCaimanGuardingShip(iChar);
		}
	}
}

int GetColonyGuardsShipsQuantity()
{
	int qty = 0;

	string sShip = "";
	string sCharacter = "";
	for(int i=1; i <= 4; i++)
	{
		sShip = "Ship" + i;

		if(PChar.Colony.Guardians.(sShip) != -1)
		{
			qty++;
		}
	}

	return qty;
}

void CheckDeadColonyGuard()
{
	int i = 0;

	int iCharacter = 0;
	string sShip = "";
	string sStepShip = "";
	string sGroup = "";
	for(i = 1; i <= 4; i++)
	{
		sShip = "Ship" + i;
		iCharacter = sti(PChar.Colony.Guardians.(sShip));

		if(iCharacter != -1)
		{
			if(sti(Characters[iCharacter].Ship.Type) > REAL_SHIPS_QUANTITY || CheckAttribute(&Characters[iCharacter], "ship.shipsink"))
			{
				KillColonyGuarding(i);
			}
		}
	}

	for(i = 1; i <= 3; i++)
	{
		sShip = "Ship" + i;
		iCharacter = sti(PChar.Colony.Guardians.(sShip));

		if(iCharacter == -1)
		{
			sStepShip = "Ship" + (i+1);
			PChar.Colony.Guardians.(sShip) = -1;
			PChar.Colony.Guardians.(sShip) = sti(PChar.Colony.Guardians.(sStepShip));
			PChar.Colony.Guardians.(sShip).Active = sti(PChar.Colony.Guardians.(sStepShip).Active);
			PChar.Colony.Guardians.(sStepShip) = -1;
			PChar.Colony.Guardians.(sStepShip).Active = false;
		}
	}

	for(i = 1; i<=4; i++)
	{
		sGroup = "InterfaceColonyGuardians_" + i;
		sShip = "Ship" + i;
		iCharacter = sti(PChar.Colony.Guardians.(sShip));

		if(Group_FindGroup(sGroup) != -1)
		{
			Group_DeleteGroup(sGroup);
		}

		Group_SetAddress(sGroup, "none", "none", "none");

		if(iCharacter != -1)
		{
			SetCharacterRelationBoth(iCharacter, GetMainCharacterIndex(), RELATION_FRIEND);
			SetCharacterShipLocation(&Characters[iCharacter], "LandGuardingPort");

			sGroup = "InterfaceColonyGuardians_" + i;
			Group_FindOrCreateGroup(sGroup);
			Group_SetType(sGroup, "war");
			Group_AddCharacter(sGroup, Characters[iCharacter].id);
			Group_SetGroupCommander(sGroup, Characters[iCharacter].id);

			if(sti(PChar.Colony.Guardians.(sShip).Active) == true)
			{
				Group_SetAddress(sGroup, "Caiman", "Quest_Ships", "quest_ship_" + i);
			}
		}
	}
}

void KillColonyGuarding(int iNum)
{
	string sShip = "Ship" + iNum;

	int iChar = PChar.Colony.Guardians.(sShip);
	if(iChar == -1)
	{
		return;
	}

	ref chr = GetCharacter(iChar);
	chr.LifeDay = 0;

	string sGroup = "InterfaceColonyGuardians_" + iNum;
	if(Group_FindGroup(sGroup) != -1)
	{
		Group_DeleteGroup(sGroup);
	}

	ChangeCharacterAddressGroup(chr, "none", "none", "none");
	PChar.Colony.Guardians.(sShip) = -1;
	PChar.Colony.Guardians.(sShip).Active = false;
}

void RemoveColonyGuardingFromSquadron(ref chr)
{
	DeleteAttribute(chr, "CaimanGuardian");
	//chr.nation = sti(chr.nation.prev_nation);
	chr.AlwaysEnemy = true;

	if(CheckAttribute(chr, "AlwaysFriend")) 	{ DeleteAttribute(chr, "AlwaysFriend"); }
	if(CheckAttribute(chr, "DontCheckFlag")) 	{ DeleteAttribute(chr, "DontCheckFlag"); }
	if(CheckAttribute(chr, "ShipEnemyDisable")) 	{ DeleteAttribute(chr, "ShipEnemyDisable"); }

	int iNum = FindCaimanGuardingNum(chr);

	string sShip = "Ship" + iNum;
	PChar.Colony.Guardians.(sShip) = -1;
	PChar.Colony.Guardians.(sShip).Active = false;

	SetCharacterShipLocation(chr, "None");

	string sGroup = "InterfaceColonyGuardians_" + iNum;
	if(Group_FindGroup(sGroup) != -1)
	{
		Group_DeleteGroup(sGroup);
	}

	SetCharacterRelationBoth(GetCharacterIndex(chr.id), GetMainCharacterIndex(), RELATION_ENEMY);

	for(int i=1; i<=4; i++)
	{
		sGroup = "InterfaceColonyGuardians_" + i;
		if(Group_FindGroup(sGroup) != -1)
		{
			Group_SetEnemyToCharacter(sGroup, GetCharacterIndex(chr.id));
		}
	}

	CheckDeadColonyGuard();
}

void RepairCaimanGuardingShip(int iCharacter)
{
	int cn = -1;
	aref arDamages;
	string sBort;
	int iNumRealCannons = 0;
	int iNumIntactCannons = 0;
	string attr;

	cn = iCharacter;
	if(cn != -1)
	{
		if(sti(characters[cn].ship.type) != SHIP_NOTUSED)
		{
			characters[cn].ship.hp = Realships[sti(characters[cn].ship.type)].hp;
			characters[cn].ship.sp = 100;
			for (int m = 0; m < 4; m++)
			{
				switch (m)
				{
					case 0: sBort = "cannonf"; break;
					case 1: sBort = "cannonb"; break;
					case 2: sBort = "cannonl"; break;
					case 3: sBort = "cannonr"; break;
				}
				makearef(arDamages, characters[cn].Ship.Cannons.Borts.(sBort).damages);

				iNumRealCannons = GetAttributesNum(arDamages);

				for (int k=0; k<iNumRealCannons; k++)
				{
					attr = "c" + k;
					if(arDamages.(attr) > 0.01)
					{
						arDamages.(attr) = 0.0;
					}
				}
			}
			DeleteAttribute(&characters[cn], "ship.flow");
		}
	}
}

////////////////////////////////////////////////////////////////////////
// АВТО-НАЙМ ГАРНИЗОНА
////////////////////////////////////////////////////////////////////////
void ColonyGuardingAutoCrewHire(string sType)
{
	if(PChar.Colony.Guardians.Hovernor == "")
	{
		return;
	}

	if(PChar.Colony.Guardians.(sType).AutoCrewHire == false)
	{
		return;
	}

	int iCost = ColonyGuardingGetCostForObject(sType, false);
	if(iCost <= 0)
	{
		return;
	}

	int iQty = 0;
	int iMaxQty = 0;
	int iNeedQty = 0;
	switch(sType)
	{
		case "Colony":
			if(GetMyColonyMoney() >= iCost)
			{
				iMaxQty = sti(PChar.ColonyBuilding.Soldiers.MaxQuantity);
				iQty = sti(PChar.ColonyBuilding.Soldiers);
				iNeedQty = iMaxQty - iQty;

				ChangeColonyMoney(-iCost, false);
				ChangeColonySoldiers(iNeedQty, false);
				Log_InfoS("Гарнизон колонии был пополнен " + iNeedQty + " солдатами за " + iCost + " золотых.");
			}
		break;

		case "Mines":
			if(GetMyColonyMoney() >= iCost)
			{
				iMaxQty = sti(PChar.Mines.MaxGuardiansQuantity);
				iQty = sti(PChar.Mines.GuardiansQuantity);
				iNeedQty = iMaxQty - iQty;

				ChangeColonyMoney(-iCost, false);
				ChangeMinesSoldiers(iNeedQty, false);
				Log_InfoS("Гарнизон рудников был пополнен " + iNeedQty + " солдатами за " + iCost + " золотых.");
			}
		break;

		case "Plantation":
			if(GetMyColonyMoney() >= iCost)
			{
				iMaxQty = sti(PChar.Plantation.Guardians.MaxQuantity);
				iQty = sti(PChar.Plantation.Guardians.Quantity);
				iNeedQty = iMaxQty - iQty;

				ChangeColonyMoney(-iCost, false);
				ChangePlantationSoldiers(iNeedQty, false);
				Log_InfoS("Гарнизон плантации был пополнен " + iNeedQty + " солдатами за " + iCost + " золотых.");
			}
		break;
	}
}

int ColonyGuardingGetCostForObject(string sType, bool bFull)
{
	int iQty = 0;
	int iMaxQty = 0;
	int iNeedQty = 0;
	int iCost = 0;

	switch(sType)
	{
		case "Colony":
			iMaxQty = sti(PChar.ColonyBuilding.Soldiers.MaxQuantity);
			if(bFull)
			{
				iCost = ColonyGuardingAutoCrewHireCost() * iMaxQty;
				return iCost;
			}

			iQty = sti(PChar.ColonyBuilding.Soldiers);
			iNeedQty = iMaxQty - iQty;
			iCost = ColonyGuardingAutoCrewHireCost() * iNeedQty;
			return iCost;
		break;

		case "Mines":
			iMaxQty = sti(PChar.Mines.MaxGuardiansQuantity);
			if(bFull)
			{
				iCost = ColonyGuardingAutoCrewHireCost() * iMaxQty;
				return iCost;
			}

			iQty = sti(PChar.Mines.GuardiansQuantity);
			iNeedQty = iMaxQty - iQty;
			iCost = ColonyGuardingAutoCrewHireCost() * iNeedQty;
			return iCost;
		break;

		case "Plantation":
			iMaxQty = sti(PChar.Plantation.Guardians.MaxQuantity);
			if(bFull)
			{
				iCost = ColonyGuardingAutoCrewHireCost() * iMaxQty;
				return iCost;
			}

			iQty = sti(PChar.Plantation.Guardians.Quantity);
			iNeedQty = iMaxQty - iQty;
			iCost = ColonyGuardingAutoCrewHireCost() * iNeedQty;
			return iCost;
		break;
	}

	return iCost;
}

int ColonyGuardingAutoCrewHireCost()
{
	int iBaseCost = 10;
	iBaseCost = GetCrewPriceForTavern("Caiman") * 3.6;

	return iBaseCost;
}

string ColonyGuardingAutoCrewHireGetWork()
{
	bool bColony = PChar.Colony.Guardians.Colony.AutoCrewHire;
	bool bMines = PChar.Colony.Guardians.Mines.AutoCrewHire;
	bool bPlantation = PChar.Colony.Guardians.Plantation.AutoCrewHire;

	if(!bColony && !bMines && !bPlantation)
	{
		return XI_ConvertString("HireGetWork_1");
	}
	if(bColony && !bMines && !bPlantation)
	{
		return XI_ConvertString("HireGetWork_2");
	}
	if(!bColony && bMines && !bPlantation)
	{
		return XI_ConvertString("HireGetWork_3");
	}
	if(!bColony && !bMines && bPlantation)
	{
		return XI_ConvertString("HireGetWork_4");
	}
	if(bColony && bMines && !bPlantation)
	{
		return XI_ConvertString("HireGetWork_5");
	}
	if(bColony && !bMines && bPlantation)
	{
		return XI_ConvertString("HireGetWork_6");
	}
	if(!bColony && bMines && bPlantation)
	{
		return XI_ConvertString("HireGetWork_7");
	}
	if(bColony && bMines && bPlantation)
	{
		return XI_ConvertString("HireGetWork_8");
	}

	return "bug";
}




