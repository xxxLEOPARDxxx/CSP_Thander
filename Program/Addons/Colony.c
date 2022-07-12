
#define		COLONY_AUTO_PURCHASE_FOOD		50
#define		COLONY_AUTO_PURCHASE_MEDICAMENT		60
#define		COLONY_AUTO_PURCHASE_TOOLS		45
#define		COLONY_MIN_MORALE_DOWN			3

#define 	COLONY_FOOD_POPULATION_DELIT		25
#define 	COLONY_FOOD_SOLDIERS_DELIT		50
#define 	COLONY_MEDICAMENT_DELIT			50

/////////////////////////////////////////////////////////////////////////////////
// COLONY
/////////////////////////////////////////////////////////////////////////////////
void GenerateColonyVariable()
{
	ref PChar = GetMainCharacter();

	PChar.ColonyBuilding.bAch = false;
	PChar.ColonyBuilding.bCreate = false;

	PChar.ColonyBuilding.SlavesInShore.CurShore = "none";

	PChar.ColonyBuilding.CurrentIconsTexture = 1;
	PChar.ColonyBuilding.MessageInfo = "";
	PChar.ColonyBuilding.Colony.AutoPurchase = false;
	PChar.ColonyBuilding.Mines.AutoPurchase = false;
	PChar.ColonyBuilding.Plantation.AutoPurchase = false;
	PChar.ColonyBuilding.AutoPurchaseFirst = false;
	PChar.ColonyBuilding.AutoPurchaseFirst.Disable = false;

	PChar.ColonyBuilding.Mines.AutoSell = false;
	PChar.ColonyBuilding.Plantation.AutoSell = false;
	PChar.ColonyBuilding.Mines.AutoSell.Qty = 100;
	PChar.ColonyBuilding.Plantation.AutoSell.Qty = 100;

	PChar.ColonyBuilding.Stage = "0";
	PChar.ColonyBuilding.Money = 0;
	PChar.ColonyBuilding.Money.Temp = 0;
	PChar.ColonyBuilding.Nalog = 1;
	PChar.ColonyBuilding.Population = rand(15) + 20;
	PChar.ColonyBuilding.Population.Morale = rand(20) + 20;
	PChar.ColonyBuilding.Population.Max = 250 + (rand(70) + rand(50));
	PChar.ColonyBuilding.Population.Optimal = (sti(PChar.ColonyBuilding.Population.Max) - 35) - rand(15);

	PChar.ColonyBuilding.Population.Epidemy = false;
	PChar.ColonyBuilding.Money.CanGet = false;
	PChar.ColonyBuilding.Store = false;
	PChar.ColonyBuilding.Shipyard = false;
	PChar.ColonyBuilding.Tavern = false;
	PChar.ColonyBuilding.Church = false;
	PChar.ColonyBuilding.Bank = false;
	PChar.ColonyBuilding.HeadPort = false;
	PChar.ColonyBuilding.Expidition = false;
	PChar.ColonyBuilding.StoreHouse = false;
	PChar.ColonyBuilding.StoreHouse.Resize = false;
	PChar.ColonyBuilding.Plantation = false;
	PChar.ColonyBuilding.Plantation.Resize = false;
	PChar.ColonyBuilding.Mines = false;
	PChar.ColonyBuilding.GoldMine = false;
	PChar.ColonyBuilding.SilverMine = false;
	PChar.ColonyBuilding.IronMine = false;
	PChar.ColonyBuilding.GoldMine.Resize = false;
	PChar.ColonyBuilding.SilverMine.Resize = false;
	PChar.ColonyBuilding.IronMine.Resize = false;
	PChar.ColonyBuilding.Store.BuildingTime = false;
	PChar.ColonyBuilding.Shipyard.BuildingTime = false;
	PChar.ColonyBuilding.Tavern.BuildingTime = false;
	PChar.ColonyBuilding.Church.BuildingTime = false;
	PChar.ColonyBuilding.Bank.BuildingTime = false;
	PChar.ColonyBuilding.HeadPort.BuildingTime = false;
	PChar.ColonyBuilding.Expidition.BuildingTime = false;
	PChar.ColonyBuilding.StoreHouse.BuildingTime = false;
	PChar.ColonyBuilding.StoreHouse.Resize.BuildingTime = false;
	PChar.ColonyBuilding.Plantation.Resize.BuildingTime = false;
	PChar.ColonyBuilding.Plantation.BuildingTime = false;
	PChar.ColonyBuilding.GoldMine.BuildingTime = false;
	PChar.ColonyBuilding.SilverMine.BuildingTime = false;
	PChar.ColonyBuilding.IronMine.BuildingTime = false;
	PChar.ColonyBuilding.GoldMine.Resize.BuildingTime = false;
	PChar.ColonyBuilding.SilverMine.Resize.BuildingTime = false;
	PChar.ColonyBuilding.IronMine.Resize.BuildingTime = false;

	PChar.ColonyBuilding.Expidition.Cost 		= (5000 * MOD_SKILL_ENEMY_RATE) + (rand(2500) * MOD_SKILL_ENEMY_RATE);
	PChar.ColonyBuilding.Plantation.Cost		= (70000 * MOD_SKILL_ENEMY_RATE) + (rand(5000) * MOD_SKILL_ENEMY_RATE);
	PChar.ColonyBuilding.StoreHouse.Cost 		= (10000 * MOD_SKILL_ENEMY_RATE) + (rand(2500) * MOD_SKILL_ENEMY_RATE);
	PChar.ColonyBuilding.StoreHouse.ResizeCost 	= (5000 * MOD_SKILL_ENEMY_RATE) + (rand(2500) * MOD_SKILL_ENEMY_RATE);
	PChar.ColonyBuilding.GoldMine.Cost 			= (30000 * MOD_SKILL_ENEMY_RATE) + (rand(10000) * MOD_SKILL_ENEMY_RATE);
	PChar.ColonyBuilding.SilverMine.Cost 		= (25000 * MOD_SKILL_ENEMY_RATE) + (rand(5000) * MOD_SKILL_ENEMY_RATE);
	PChar.ColonyBuilding.IronMine.Cost 			= (20000 * MOD_SKILL_ENEMY_RATE) + (rand(1500) * MOD_SKILL_ENEMY_RATE);
	PChar.ColonyBuilding.GoldMine.ResizeCost 	= (15000 * MOD_SKILL_ENEMY_RATE) + (rand(5000) * MOD_SKILL_ENEMY_RATE);
	PChar.ColonyBuilding.SilverMine.ResizeCost 	= (10000 * MOD_SKILL_ENEMY_RATE) + (rand(2500) * MOD_SKILL_ENEMY_RATE);
	PChar.ColonyBuilding.IronMine.ResizeCost 	= (8500 * MOD_SKILL_ENEMY_RATE) + (rand(2000) * MOD_SKILL_ENEMY_RATE);
	PChar.ColonyBuilding.Store.Cost 			= (15000 * MOD_SKILL_ENEMY_RATE) + (rand(2500) * MOD_SKILL_ENEMY_RATE);
	PChar.ColonyBuilding.Shipyard.Cost 			= (17500 * MOD_SKILL_ENEMY_RATE) + (rand(2850) * MOD_SKILL_ENEMY_RATE);
	PChar.ColonyBuilding.Tavern.Cost 			= (15000 * MOD_SKILL_ENEMY_RATE) + (rand(500) * MOD_SKILL_ENEMY_RATE);
	PChar.ColonyBuilding.Church.Cost 			= (20000 * MOD_SKILL_ENEMY_RATE) + (rand(2500) * MOD_SKILL_ENEMY_RATE);
	PChar.ColonyBuilding.Bank.Cost 				= (20000 * MOD_SKILL_ENEMY_RATE) + (rand(2500) * MOD_SKILL_ENEMY_RATE);
	PChar.ColonyBuilding.HeadPort.Cost 			= (12500 * MOD_SKILL_ENEMY_RATE) + (rand(2550) * MOD_SKILL_ENEMY_RATE);

	PChar.BuildingColony.Blocks = 1000;
	PChar.BuildingColony.Planks = 1000;
	PChar.BuildingColony.Mahogany = 400;
	PChar.BuildingColony.Ebony = 400;
	PChar.BuildingColony.Slaves = 200;
	PChar.BuildingColony.Food = 400;

	PChar.BuildingColony.ColonyTime = rand(10) + 30;
	PChar.BuildingColony.ColonyModification = rand(5) + 40;
	PChar.BuildingColony.ColonyFort = rand(5) + 35 + rand(5);

	PChar.ColonyBuilding.Hovernor = "";
	PChar.ColonyBuilding.MineMessage = false;
	PChar.ColonyBuilding.Action = false;
	PChar.ColonyBuilding.FortBuilding = false;
	PChar.ColonyBuilding.Fort = false;
	PChar.ColonyBuilding.FirstBuild = false;

	PChar.ColonyBuilding.EventBlock = false;

	PChar.ColonyBuilding.Defence = false;
	PChar.ColonyBuilding.Defence.Battle = false;
	PChar.ColonyBuilding.Defence.DeadInTown = false;
	PChar.ColonyBuilding.Defence.Type = "Mutiny";

	PChar.ColonyBuilding.DeleteGoods = "";

	PChar.ColonyBuilding.Soldiers = 0;
	PChar.ColonyBuilding.Soldiers.MaxQuantity = 1000;
	PChar.ColonyBuilding.Food = 0;
	PChar.ColonyBuilding.Food.MaxQuantity = 5000;
	PChar.ColonyBuilding.Medicament = 0;
	PChar.ColonyBuilding.Medicament.MaxQuantity = 1000;

	PChar.ColonyBuilding.ColonyName = "Кайман";
	PChar.ColonyBuilding.ColonyNation = 0;
	PChar.ColonyBuilding.SoldiersType = "officer";

	PChar.ColonyBuilding.Architecture = false;
	PChar.ColonyBuilding.Architecture.Town = 1;
	PChar.ColonyBuilding.Architecture.Store = 1;
	PChar.ColonyBuilding.Architecture.Shipyard = 1;
	PChar.ColonyBuilding.Architecture.Tavern = 1;
	PChar.ColonyBuilding.Architecture.Bank = 1;
	PChar.ColonyBuilding.Architecture.Townhall = 1;

	PChar.ColonyBuilding.Architecture.Town.Cost.Type_1 		= 100000 * MOD_SKILL_ENEMY_RATE;
	PChar.ColonyBuilding.Architecture.Town.Cost.Type_2 		= 200000 * MOD_SKILL_ENEMY_RATE;
	PChar.ColonyBuilding.Architecture.Town.Cost.Type_3 		= 150000 * MOD_SKILL_ENEMY_RATE;

	PChar.ColonyBuilding.Architecture.Store.Cost.Type_1 	= 10000 * MOD_SKILL_ENEMY_RATE;
	PChar.ColonyBuilding.Architecture.Store.Cost.Type_2 	= 15000 * MOD_SKILL_ENEMY_RATE;
	PChar.ColonyBuilding.Architecture.Store.Cost.Type_3 	= 20000 * MOD_SKILL_ENEMY_RATE;
	PChar.ColonyBuilding.Architecture.Store.Cost.Type_4 	= 17500 * MOD_SKILL_ENEMY_RATE;

	PChar.ColonyBuilding.Architecture.Shipyard.Cost.Type_1 	= 10000 * MOD_SKILL_ENEMY_RATE;
	PChar.ColonyBuilding.Architecture.Shipyard.Cost.Type_2 	= 15000 * MOD_SKILL_ENEMY_RATE;
	PChar.ColonyBuilding.Architecture.Shipyard.Cost.Type_3 	= 20000 * MOD_SKILL_ENEMY_RATE;

	PChar.ColonyBuilding.Architecture.Tavern.Cost.Type_1 	= 12500 * MOD_SKILL_ENEMY_RATE;
	PChar.ColonyBuilding.Architecture.Tavern.Cost.Type_2 	= 15000 * MOD_SKILL_ENEMY_RATE;
	PChar.ColonyBuilding.Architecture.Tavern.Cost.Type_3 	= 20000 * MOD_SKILL_ENEMY_RATE;
	PChar.ColonyBuilding.Architecture.Tavern.Cost.Type_4 	= 10000 * MOD_SKILL_ENEMY_RATE;

	PChar.ColonyBuilding.Architecture.Bank.Cost.Type_1 		= 20000 * MOD_SKILL_ENEMY_RATE;
	PChar.ColonyBuilding.Architecture.Bank.Cost.Type_2 		= 25000 * MOD_SKILL_ENEMY_RATE;

	PChar.ColonyBuilding.Architecture.Townhall.Cost.Type_1 	= 30000 * MOD_SKILL_ENEMY_RATE;
	PChar.ColonyBuilding.Architecture.Townhall.Cost.Type_2 	= 20000 * MOD_SKILL_ENEMY_RATE;
	PChar.ColonyBuilding.Architecture.Townhall.Cost.Type_3 	= 35000 * MOD_SKILL_ENEMY_RATE;
	PChar.ColonyBuilding.Architecture.Townhall.Cost.Type_4 	= 25000 * MOD_SKILL_ENEMY_RATE;

	SetColonyMessageInfo("", "", "", PIRATE, 0, true, false);
	InitMines();
	StoreHouseInit();
}

bool GetDisableAllColonyEvent()
{
	bool bEnable = PChar.ColonyBuilding.EventBlock;

	if(bEnable)
	{
		return true;
	}
	else
	{
		return false;
	}

	return false;
}

void LiveOfTheColonyUptade()
{
	ref PChar = GetMainCharacter();

	Log_TestInfo("ИЗМЕНЕНИЕ ЖИЗНИ В КОЛОНИИ.");
	AutoPurchaseColonyGoods("Colony");

	int iPopulationQuantity = sti(PChar.ColonyBuilding.Population);
	int iPopulationQuantityOpt = sti(PChar.ColonyBuilding.Population.Optimal);
	int iPopulationMorale = sti(PChar.ColonyBuilding.Population.Morale);
	int iNalog = sti(PChar.ColonyBuilding.Nalog);

	int iPopulationReSize = 0;
	int iQuantityResize = 0;
	int iMoraleMinus = COLONY_MIN_MORALE_DOWN;

	if(iPopulationQuantity > iPopulationQuantityOpt) { iMoraleMinus = 7; }
	switch(iNalog) { case 1: iMoraleMinus += 3; break; case 2: iMoraleMinus += 17; break; case 3: iMoraleMinus += 24; break; }

	// Влияние зданий на мораль
	//------------>>>>>>>>>>>>>>
	bool temp = false;
	temp = sti(PChar.ColonyBuilding.Store);
	if(!temp) { iMoraleMinus += 2; }else{ iMoraleMinus -= 1; }

	temp = sti(PChar.ColonyBuilding.Tavern);
	if(!temp) { iMoraleMinus += 4; }else{ iMoraleMinus -= 2; }

	if(PChar.ColonyBuilding.Stage == "2" || PChar.ColonyBuilding.Stage == "3")
	{
		temp = sti(PChar.ColonyBuilding.Shipyard);
		if(!temp) { iMoraleMinus += 3; }else{ iMoraleMinus -= 2; }

		temp = sti(PChar.ColonyBuilding.Church);
		if(!temp) { iMoraleMinus += 7; }else{ iMoraleMinus -= 5; }

		temp = sti(PChar.ColonyBuilding.Bank);
		if(!temp) { iMoraleMinus += 5; }else{ iMoraleMinus -= 4; }

		temp = sti(PChar.ColonyBuilding.HeadPort);
		if(!temp) { iMoraleMinus += 4; }else{ iMoraleMinus -= 3; }
	}
	//<<<<<<<<<<<<<<------------

	if(iMoraleMinus < COLONY_MIN_MORALE_DOWN) { iMoraleMinus = COLONY_MIN_MORALE_DOWN; }
	ChangeColonyMorale(-iMoraleMinus, false);

	iPopulationMorale = sti(PChar.ColonyBuilding.Population.Morale);
	bool bDisable = GetDisableAllColonyEvent();
	if(iPopulationMorale < 20 || rand(100) < 10)
	{
		if(!bDisable)
		{
			CreateMutinyColony();
		}
	}

	iQuantityResize = iPopulationQuantity / 10;
	if(iQuantityResize < 12) iQuantityResize = 12;
	if(iQuantityResize > 30) iQuantityResize = 30;


	if(iPopulationMorale < 40)
	{
		//if(PChar.DisappearPeople.Action == true) { iQuantityResize *= 2; }
		ChangeColonyPopulation(-iQuantityResize, false);
	}
	else
	{
		ChangeColonyPopulation(iQuantityResize, false);
	}

	int iMinPeople = GetColonyMinPeople();
	if(sti(PChar.ColonyBuilding.Population) < iMinPeople)
	{
		ChangeColonyPopulation(iMinPeople, true);
	}

	//Log_TestInfo("Мораль после изменения: " + sti(PChar.ColonyBuilding.Population.Morale));
	//Log_TestInfo("Народу после изменения: " + sti(PChar.ColonyBuilding.Population));

	if(rand(15) == 1)
	{
		ColonyCheckEpidemy();
		PlaySound("notebook");
	}

	ColonyCheckFoodNeed();

	MoneyOfTheColony();
	BaseCompletationColonyGuards();
	ColonyGuardingAutoCrewHire("Colony");
}

void MoneyOfTheColony()
{
	ref PChar = GetMainCharacter();

	if(PChar.ColonyBuilding.Hovernor == "")
	{
		Log_InfoS("Ваша колония не имеет управляющего - сбор налога не производится.");
		return;
	}

	int iPeopleQuantity = sti(PChar.ColonyBuilding.Population);
	if(iPeopleQuantity <= 0) return;

	int iBaseMoney, iMoney;
	int iNalog = sti(PChar.ColonyBuilding.Nalog);

	int iMayorIndex = nMainCharacterIndex;
	if(GetCharacterIndex(PChar.ColonyBuilding.Hovernor) != -1)
	{
		iMayorIndex = GetCharacterIndex(PChar.ColonyBuilding.Hovernor);
	}

	ref mayor = &Characters[iMayorIndex];
	int iLeaderShip = GetCharacterSkill(mayor, SKILL_LEADERSHIP) * 5.5;
	int iCommerce = GetCharacterSkill(mayor, SKILL_COMMERCE) * 2.8;

	float fNalog = 1.1;
	switch(iNalog) { case 1: fNalog = 1.2; break; case 2: fNalog = 1.9; break; case 3: fNalog = 2.5; break; }

	iBaseMoney = (iLeaderShip + iCommerce) * fNalog;
	iMoney = iPeopleQuantity * iBaseMoney;

	if(iMoney < 0)
	{
		iMoney = 0;
	}

	if(iMoney > 1000000)
	{
		iMoney = 1000000;
	}

	ChangeColonyMoney(iMoney, false);

	//Log_TestInfo("Прибавили денег колонии за эту неделю: " + iMoney);
	//Log_TestInfo("Стало денег в колонии: " + sti(PChar.ColonyBuilding.Money));
}

void ColonyCheckEpidemy()
{
	int iMedicament = sti(PChar.ColonyBuilding.Medicament);
	int iPopulationQuantity = sti(PChar.ColonyBuilding.Population);

	if(iPopulationQuantity < 20)
	{
		return;
	}

	int iPopulationIll = iPopulationQuantity / rand(6)+4;
	int temp = 0;

	if(iMedicament >= iPopulationIll)
	{
		temp = rand(10);
		ChangeColonyGoods(-(iPopulationIll-temp), "Medicament");
		ChangeColonyPopulation(-temp, false);
		ChangeColonyMorale(50, true);

		if(temp > 0)
		{
			Log_Info("Вести из колонии " + PChar.ColonyBuilding.ColonyName + "!");
			AddQuestRecord("MY_COLONY", "11");
			AddQuestUserData("MY_COLONY", "sEpidemyDead", temp);
		}

		return;
	}
	else
	{
		temp = iPopulationIll - iMedicament;
		if(temp <= 0) { temp = 0; }

		ChangeColonyGoods(-temp, "Medicament");
		ChangeColonyPopulation(-temp, false);
		ChangeColonyMorale(-10, false);

		if(temp > 0)
		{
			Log_Info("Вести из колонии " + PChar.ColonyBuilding.ColonyName + "!");
			AddQuestRecord("MY_COLONY", "12");
			AddQuestUserData("MY_COLONY", "sEpidemyDead", temp);
		}
	}
}

void ColonyCheckFoodNeed()
{
	int iPopulation = sti(PChar.ColonyBuilding.Population);
	int iFood = sti(PChar.ColonyBuilding.Food);
	int iPopulationDiff = iPopulation / COLONY_FOOD_POPULATION_DELIT;

	if (iPopulation <= 0) return;

	bool bNotice = false;
	if(iPopulationDiff < 1)
	{
		iPopulationDiff = 1;
	}

	int iFoodNeed = iPopulationDiff * 7;
	float fCoff = iPopulationDiff / iPopulation;

	if (fCoff <= 0) return;

	int iDead = 0;
	if(iPopulation > 0)
	{
		if(iFood > iFoodNeed)
		{
			ChangeColonyGoods(-iFoodNeed, "Food");
		}
		else
		{
			if(!bNotice)
			{
				bNotice = true;
				AddQuestRecord("MY_COLONY", "16");
			}

			iDead = iFoodNeed - iFood;
			iDead /= 7;
			iDead /= fCoff;

			ChangeColonyMorale(-20, false);

			if(iDead > iPopulation)
			{
				iDead = iPopulation;
			}

			ChangeColonyGoods(-iFood, "Food");
			ChangeColonyPopulation(-iDead, false);

			Log_Info("Вести из колонии " + PChar.ColonyBuilding.ColonyName + "!");
			AddQuestRecord("MY_COLONY", "17");
			AddQuestUserData("MY_COLONY", "sFoodNeed", iDead);
		}
	}

	int iSoldiers = sti(PChar.ColonyBuilding.Soldiers);
	if(iSoldiers < 1)
	{
		return;
	}

	int iSoldiersDiff = iSoldiers / COLONY_FOOD_SOLDIERS_DELIT;
	iFood = sti(PChar.ColonyBuilding.Food);

	if(iSoldiersDiff < 1)
	{
		iSoldiersDiff = 1;
	}

	iFoodNeed = iSoldiersDiff * 7;
	fCoff = iSoldiersDiff / iSoldiers;

	if(iSoldiers > 0)
	{
		if(iFood > iFoodNeed)
		{
			ChangeColonyGoods(-iFoodNeed, "Food");
		}
		else
		{
			if(!bNotice)
			{
				bNotice = true;
				AddQuestRecord("MY_COLONY", "16");
			}

			iDead = iFoodNeed - iFood;
			iDead /= 7;
			iDead /= fCoff;

			if(iDead > iSoldiers)
			{
				iDead = iSoldiers;
			}

			ChangeColonyGoods(-iFood, "Food");
			ChangeColonySoldiers(-iDead, false);
			ChangeColonyMorale(-10, false);

			Log_Info("Вести из колонии " + PChar.ColonyBuilding.ColonyName + "!");
			AddQuestRecord("MY_COLONY", "25");
			AddQuestUserData("MY_COLONY", "sFoodNeed", iDead);
		}
	}
}

int GetColonyFoodNeedDays()
{
	int iDays = 0;
	int iFood = sti(PChar.ColonyBuilding.Food);
	int iPopulation = sti(PChar.ColonyBuilding.Population);
	int iSoldiers = sti(PChar.ColonyBuilding.Soldiers);
	int iDay = (iPopulation / COLONY_FOOD_POPULATION_DELIT) + (iSoldiers / COLONY_FOOD_SOLDIERS_DELIT);

	if(iPopulation + iSoldiers <= 0)
	{
		return iFood;
	}

	if(iFood <= 0)
	{
		return 0;
	}

	if(iDay <= 0)
	{
		return iFood;
	}

	iDay *= 21;
	iDays = iFood / iDay;

	if(iDays < 0)
	{
		iDays = 0;
	}

	return iDays;
}

//-------------------------------------------------------------------------------
// НАПАДЕНИЯ НА КОЛОНИЮ
//-------------------------------------------------------------------------------
void CheckDefenceColony()
{
	Log_TestInfo("Готовим нападение на колонию.");

	bool bDisable = GetDisableAllColonyEvent();
	if(PChar.ColonyBuilding.Defence == true || PChar.ColonyBuilding.Action == true || bDisable)
	{
		Log_TestInfo("Нападения не будет, т.к. идёт стройка или уже действует/готовится какое то нападение.");
		/*Log_TestInfo("Строится ли что то: " + sti(PChar.ColonyBuilding.Action));
		Log_TestInfo("Планируется ли нападение: " + sti(PChar.ColonyBuilding.Defence));
		Log_TestInfo("Тип нападения: " + PChar.ColonyBuilding.Defence.Type);*/
		return;
	}

	int iRand = rand(5);

	int iMoney = sti(PChar.ColonyBuilding.Money);
	if(iMoney >= 1000000 && rand(1) == 1)
	{
		if(rand(10) > 5) iRand = 2; else iRand = 5;
	}

	if(iRand != 2 && iRand != 5)
	{
		Log_TestInfo("Никакие нападения не сгенерились.");
		return;
	}
	else
	{
		if(PChar.ColonyBuilding.Stage == "1")
		{
			CreateLandDefenceColony();
			Log_TestInfo("Готовится нападение с суши.");
			return;
		}
		else
		{

			if(iRand == 2)
			{
				CreateSeaDefenceColony();
				Log_TestInfo("Готовится нападение с моря.");
				return;
			}

			if(iRand == 5)
			{
				CreateLandDefenceColony();
				Log_TestInfo("Готовится нападение с суши.");
				return;
			}
		}
	}
}

//-------------------------------------------------------------------------------
// ПЕРВЫЙ ВАРИАНТ - МЯТЕЖ
//-------------------------------------------------------------------------------
void CreateMutinyColony()
{
	Log_TestInfo("Готовится мятеж в колонии.");

	int iPopulationQuantity = sti(PChar.ColonyBuilding.Population);
	int iPopulationMorale = sti(PChar.ColonyBuilding.Population.Morale);

	if(iPopulationQuantity <= 100)
	{
		Log_TestInfo("Мятежа не будет, так как мало населения.");
		return;
	}

	if(rand(100) < 20)
	{
		Log_TestInfo("Мятежа не будет, так как повезло.");
		return;
	}

	if(PChar.ColonyBuilding.Defence == true || PChar.ColonyBuilding.Action == true)
	{
		Log_TestInfo("Мятежа не будет, так как идёт стройка какая-то или какой либо тип нападения уже создан.");
		Log_TestInfo("Строится ли что то: " + sti(PChar.ColonyBuilding.Action));
		Log_TestInfo("Планируется ли нападение: " + sti(PChar.ColonyBuilding.Defence));
		Log_TestInfo("Тип нападения: " + PChar.ColonyBuilding.Defence.Type);
		return;
	}

	// Включаем блокировку всех нападений -->
	PChar.ColonyBuilding.EventBlock = true;
	// Включаем блокировку всех нападений <--

	PChar.ColonyBuilding.Defence = true;
	PChar.ColonyBuilding.Defence.Type = "Mutiny";

	int iSoldiersQuantity = sti(PChar.ColonyBuilding.Soldiers) / 100;
	int iRebels = iPopulationQuantity / 60;

	if(iSoldiersQuantity < 1) { InstantColonyDefendLoose("Colony", "Mutiny"); return; }

	if(iRebels < 2) iRebels = 2;
	if(iRebels > 20) iRebels = 20;

	ChangeColonyPopulation(-(iRebels*15), false);

	if(iSoldiersQuantity < 2) iSoldiersQuantity = 2;
	if(iSoldiersQuantity > 20) iSoldiersQuantity = 25;

	PChar.ColonyBuilding.Defence.Nation = PIRATE;
	PChar.ColonyBuilding.Defence.Soldiers = iSoldiersQuantity;
	PChar.ColonyBuilding.Defence.Soldiers.Delete = rand(1) + 3;
	PChar.ColonyBuilding.Defence.EnemyQuantity = iRebels;

	Log_TestInfo("Кол-во мятежников: " + iRebels);
	Log_TestInfo("Кол-во солдат: " + iSoldiersQuantity);

	int iRandMinus = 2;
	if(iRebels > iSoldiersQuantity)
	{
		iRandMinus -= (iRebels - iSoldiersQuantity);
	}
	else
	{
		iRandMinus += (iSoldiersQuantity - iRebels);
	}

	if(iRandMinus <= -7) { InstantColonyDefendLoose("Colony", "Mutiny"); return; }

	int iRand = iRandMinus - rand(4);

	int iEnd = 0;
	if(iRand > 0) { iEnd = 1; }else{ iEnd = 0; }


	PChar.ColonyBuilding.Defence.End = iEnd;

	int iTime = 7 + rand(10) + iRandMinus;
	if(iTime < 7) { iTime = 7; }
	if(iTime > 30) { iTime = 30; }

	string sClearQuest = "ClearMutinyColony_" + rand(1000000);
	PChar.ColonyBuilding.ClearQuest = sClearQuest;

	PChar.quest.(sClearQuest).win_condition.l1 = "Timer";
	PChar.quest.(sClearQuest).win_condition.l1.date.day = GetAddingDataDay(0, 0, iTime);
	PChar.quest.(sClearQuest).win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTime);
	PChar.quest.(sClearQuest).win_condition.l1.date.year = GetAddingDataYear(0, 0, iTime);
	PChar.quest.(sClearQuest).win_condition.l1.date.hour = 12;
	PChar.quest.(sClearQuest).function = "ClearMutinyColony";

	Log_Info("Вести из колонии " + PChar.ColonyBuilding.ColonyName + "!");

	string sTime = FindRussianDaysString(iTime);

	AddQuestRecord("MY_COLONY", "1");
	AddQuestUserData("MY_COLONY", "sMutinyTime", sTime);

	string sBattleQuest = "BattleMutinyColony_" + rand(1000000);
	PChar.ColonyBuilding.BattleQuest = sBattleQuest;

	PChar.quest.(sBattleQuest).win_condition.l1 = "location";
	PChar.quest.(sBattleQuest).win_condition.l1.location = "Caiman_town";
	PChar.quest.(sBattleQuest).function = "BattleMutinyColony";

	SetColonyMessageInfo("Colony", "Mutiny", "", PIRATE, iTime, true, true);
}

void BattleMutinyColony(string _tmp)
{
	string sClearQuest = PChar.ColonyBuilding.ClearQuest;
	PChar.quest.(sClearQuest).over = "yes";

	chrDisableReloadToLocation = true;
	bDisableFastReload = true;
	LAi_grp_alarmactive = true;
	InterfaceStates.Buttons.Save.enable = false;
	PChar.ColonyBuilding.Defence.Battle = true;

	int i = 0;
	int iSoldiers = sti(PChar.ColonyBuilding.Defence.Soldiers);
	int iRebels = sti(PChar.ColonyBuilding.Defence.EnemyQuantity);
	ref chr;

	if(PChar.ColonyBuilding.Stage != "3")
	{
		ChangeCharacterAddress(CharacterFromID("Builder"), "none", "none");
	}

	if(PChar.ColonyBuilding.Stage == "1" && PChar.location.locator == "reload6")
	{
		ChangeCharacterAddressGroup(PChar, PChar.location, "rld", "aloc0");
	}

	string sModel = "";
	string sLocator = "";

	for(i=1; i <= iRebels; i++)
	{
		sModel = "citiz_" + (rand(11)+1);

		if(PChar.ColonyBuilding.Stage == "1")
		{
			sLocator = "reload6";
		}
		else
		{
			sLocator = "reload3_back";
		}

		chr = GetCharacter(NPC_GeneratePhantomCharacter("officer_1", PIRATE, 1, 0));
		chr.rank = GetRank(PChar, MOD_SKILL_ENEMY_RATE) + 2;
		SetFantomParamFromRank(chr, sti(chr.rank), true);
		chr.id = "My Colony Mutiny Rebel " + i;
		chr.model = sModel;
		chr.model.animation = "man";
		chr.NotRemoved = true;
		SetNewModelToChar(chr);
    		FaceMaker(chr);
		LAi_NoRebirthEnable(chr);
		LAi_SetWarriorType(chr);
		LAi_group_MoveCharacter(chr, "EnemyFight");
		ChangeCharacterAddressGroup(chr, PChar.location, "reload", sLocator);
	}

	int iNation = sti(PChar.ColonyBuilding.ColonyNation);
	string sNation = NationShortName(iNation);

	int iMusketeers = FightInColonyGetMusketeerQty(iSoldiers);
	bool bMusketeer = false;

	string sAni = "man";
	for(i=1; i <= iSoldiers; i++)
	{
		sAni = "man";

		bMusketeer = false;
		if(iSoldiers - i < iMusketeers) { bMusketeer = true; }

		if(PChar.ColonyBuilding.SoldiersType == "officer")
		{
			sModel = "officer_" + (rand(63) + 1);

			if(bMusketeer) { sModel = "officer_" + (rand(63) + 1)+ "_mush"; sAni = "mushketer"; }
		}
		else
		{
			if(PChar.ColonyBuilding.SoldiersType == "pirate")
			{
				sModel = "pirate_" + (rand(24) + 1);

				if(bMusketeer) { sModel = GetPirateMushketerModel(); sAni = "mushketer"; }
			}
			else
			{
				sModel = "sold_" + sNation + "_" + (rand(7) + 1);

				if(bMusketeer) { sModel = sNation + "_mush_" + (rand(2)+1); sAni = "mushketer"; }
			}
		}

		if(PChar.ColonyBuilding.Stage == "1")
		{
			sLocator = "reload3";
		}
		else
		{
			sLocator = "gate_back";
		}

		chr = GetCharacter(NPC_GeneratePhantomCharacter("officer_1", PIRATE, 1, 0));
		chr.rank = GetRank(PChar, MOD_SKILL_ENEMY_RATE) + 4;
		SetFantomParamFromRank(chr, sti(chr.rank), true);
		chr.id = "My Colony Mutiny Defender " + i;
		chr.model = sModel;
		chr.model.animation = sAni;
		chr.NotRemoved = true;
		SetNewModelToChar(chr);
		LAi_NoRebirthEnable(chr);
		LAi_SetWarriorType(chr);
		LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
		ChangeCharacterAddressGroup(chr, PChar.location, "reload", sLocator);
	}

	LAi_group_SetHearRadius("EnemyFight", 100.0);
	LAi_group_FightGroupsEx("EnemyFight", LAI_GROUP_PLAYER, true, PChar, -1, false, false);
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_SetFightMode(PChar, true);

	string cnd, rbl;
	for(i=1; i<=iRebels; i++)
	{
		cnd = "l" + i;
		rbl = "My Colony Mutiny Rebel " + i;
		PChar.quest.BattleMutinyColonyWinner.win_condition.(cnd) = "NPC_Death";
		PChar.quest.BattleMutinyColonyWinner.win_condition.(cnd).character = rbl;
	}

	PChar.quest.BattleMutinyColonyWinner.function = "BattleMutinyColonyWinner";

	ref loc = PCharLoc();
	DeleteAllFantomCharactersFromLocation(loc);

	SetDeadmansToLocation(&Locations[FindLocation(PChar.location)], "citizens");
}

void BattleMutinyColonyWinner(string _tmp)
{
	InterfaceStates.Buttons.Save.enable = true;
	chrDisableReloadToLocation = false;
	bDisableFastReload = false;
	LAi_grp_alarmactive = false;
	PChar.ColonyBuilding.Defence.Battle = false;

	LAi_LockFightMode(PChar, false);
        LAi_SetFightMode(PChar, false);

	if(PChar.ColonyBuilding.Stage != "3")
	{
		ChangeCharacterAddressGroup(CharacterFromID("Builder"), "Caiman_town", "goto", "goto8");
	}

	AddQuestRecord("MY_COLONY", "2");
	ChangeColonyMorale(50, true);

	PChar.ColonyBuilding.Defence = false;
	PChar.ColonyBuilding.Defence.Type = "";

	int iSoldiers = sti(PChar.ColonyBuilding.Defence.Soldiers);
	string sDefender = "";
	int iDead = 0;
	for(int i=1; i<=iSoldiers; i++)
	{
		sDefender = "My Colony Mutiny Defender " + i;

		if(LAi_IsDead(CharacterFromID(sDefender)))
		{
			iDead++;
		}
	}

	int iSoldiersDead = iDead * 100;
	ChangeColonySoldiers(-iSoldiersDead, false);

	// Выключаем блокировку всех нападений -->
	PChar.ColonyBuilding.EventBlock = false;
	// Выключаем блокировку всех нападений <--

	AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", в колонии " + PChar.ColonyBuilding.ColonyName + " вспыхнул мятеж? Пришлось разбираться самому владельцу колонии - капитану " + GetMainCharacterNameDat() + "!", 5, 1);
}

void ClearMutinyColony(string qName)
{
	string sBattleQuest = PChar.ColonyBuilding.BattleQuest;
	PChar.quest.(sBattleQuest).over = "yes";

	PChar.ColonyBuilding.Defence = false;
	PChar.ColonyBuilding.Defence.Type = "";
	PChar.ColonyBuilding.Defence.DeadInTown = true;
	SetTimerCondition("ColonyNotSetDead", 0, 0, 6, false);
	PChar.ColonyBuilding.Defence.Battle = false;

	int iEnd = sti(PChar.ColonyBuilding.Defence.End);
	int iSoldiers = sti(PChar.ColonyBuilding.Defence.Soldiers);

	if(iSoldiers > 0)
	{
		iSoldiers /= sti(PChar.ColonyBuilding.Defence.Soldiers.Delete);
	}

	int iSoldiersDead = iSoldiers * 100;

	int iRebels = sti(PChar.ColonyBuilding.Defence.EnemyQuantity);
	int iMoney = sti(PChar.ColonyBuilding.Money);

	if(iEnd == 1)
	{
		Log_Info("Вести из колонии " + PChar.ColonyBuilding.ColonyName + "!");
		AddQuestRecord("MY_COLONY", "2");
		ChangeColonySoldiers(-iSoldiersDead, false);
		ChangeColonyMorale(50, true);
		SetColonyMessageInfo("Colony", "Mutiny", "Good", PIRATE, 0, false, true);
		AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", в колонии " + PChar.ColonyBuilding.ColonyName + " вспыхнул мятеж? Но гарнизону, охраняющему колонию, удалось разобраться с мятежниками.", 5, 1);
	}
	else
	{
		Log_Info("Вести из колонии " + PChar.ColonyBuilding.ColonyName + "!");
		AddQuestRecord("MY_COLONY", "3");
		ChangeColonySoldiers(0, true);
		ChangeColonyMorale(0, true);
		ChangeColonyMoney(-(iMoney/iRebels), false);
		SetColonyMessageInfo("Colony", "Mutiny", "", PIRATE, 0, false, true);
		AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", в колонии " + PChar.ColonyBuilding.ColonyName + " вспыхнул мятеж? И что вы думали? Гарнизон потерпел поражение!", 5, 1);
	}

	if(PChar.ColonyBuilding.Stage != "3")
	{
		ChangeCharacterAddressGroup(CharacterFromID("Builder"), "Caiman_town", "goto", "goto8");
	}

	// Выключаем блокировку всех нападений -->
	PChar.ColonyBuilding.EventBlock = false;
	// Выключаем блокировку всех нападений <--
}

//-------------------------------------------------------------------------------
// ВТОРОЙ ВАРИАНТ - НАПАДЕНИЕ С СУШИ
//-------------------------------------------------------------------------------
void CreateLandDefenceColony()
{
	if(rand(100) < 5)
	{
		Log_TestInfo("Нападения с суши не будет, так как повезло.");
		return;
	}

	if(PChar.ColonyBuilding.Fort == true && rand(100) < 25)
	{
		Log_TestInfo("Нападения с суши не будет, так как охранная база отпугнула вражину.");
		return;
	}

	int iBaseNation = GetBaseHeroNation();
	int iNation = FindEnemyNation2Nation(iBaseNation); //FindEnemyNation2Character(nMainCharacterIndex);
	if(iNation == -1)
	{
		iNation = PIRATE;
	}

	PChar.ColonyBuilding.Defence.Nation = iNation;

	// Включаем блокировку всех нападений -->
	PChar.ColonyBuilding.EventBlock = true;
	// Включаем блокировку всех нападений <--

	PChar.ColonyBuilding.Defence = true;
	PChar.ColonyBuilding.Defence.Type = "BattleLand";

	int iSoldiersQuantity = sti(PChar.ColonyBuilding.Soldiers) / 100;
	int iEnemy = 0;

	if(PChar.ColonyBuilding.Stage == "1")
	{
		iEnemy = 5 + rand(4) + rand(4);
	}
	else
	{
		iEnemy = 7 + rand(4) + rand(6) + rand(3) + 5;
	}

	int iCitizen = 0;
	if(sti(PChar.ColonyBuilding.Population.Morale) >= 70)
	{
		iCitizen = sti(PChar.ColonyBuilding.Population) / 70;
	}

	string sDestroyBuild = "none";
	if(rand(5) > 3)
	{
		sDestroyBuild = GetColonyBuildDestroy();
	}
	PChar.ColonyBuilding.Defence.DestroyBuild = sDestroyBuild;
	SetBestGoodForDeleteFromMyColony();

	if(iSoldiersQuantity < 1) { InstantColonyDefendLoose("Colony", "BattleLand"); return; }

	if(iCitizen < 0) iCitizen = 0;
	if(iCitizen > 7) iCitizen = 7;

	if(iSoldiersQuantity < 2) iSoldiersQuantity = 2;
	if(iSoldiersQuantity > 22) iSoldiersQuantity = 22;

	if(iEnemy < 2) iEnemy = 2;
	if(iEnemy > 20) iEnemy = 20;

	Log_TestInfo("Команда гарнизона + жителей: " + (iSoldiersQuantity + iCitizen));
	Log_TestInfo("Команда противника: " + iEnemy);
	if(PChar.ColonyBuilding.Fort == true)
	{
		iEnemy -= (sti(PChar.ColonyBuilding.Soldiers) / 10) / iEnemy;

		if(iEnemy < 10)
		{
			iEnemy = 10;
		}

		Log_TestInfo("Построена охранная база. Команда противника стала: " + iEnemy);
	}

	PChar.ColonyBuilding.Defence.Soldiers = iSoldiersQuantity;
	PChar.ColonyBuilding.Defence.Citizens = iCitizen;

	PChar.ColonyBuilding.Defence.Soldiers.Delete = rand(1) + 1;
	PChar.ColonyBuilding.Defence.Citizens.Delete = rand(1) + 1;

	PChar.ColonyBuilding.Defence.EnemyQuantity = iEnemy;

	int iRandMinus = -2;
	if(iEnemy > iSoldiersQuantity)
	{
		iRandMinus -= (iEnemy - (iSoldiersQuantity+iCitizen));
	}
	else
	{
		iRandMinus += ((iSoldiersQuantity+iCitizen) - iEnemy);
	}

	if(iRandMinus < -10) { InstantColonyDefendLoose("Colony", "BattleLand"); return; }

	int iRand = iRandMinus - rand(4);

	int iEnd = 0;
	if(iRand > 0) { iEnd = 1; }else{ iEnd = 0; }

	PChar.ColonyBuilding.Defence.End = iEnd;

	int iTime = 7 + rand(5) + iRandMinus;
	if(iTime < 7) { iTime = 7; }
	if(iTime > 30) { iTime = 30; }

	string sClearQuest = "ClearLandDefenceColony_" + rand(1000000);
	PChar.ColonyBuilding.ClearQuest = sClearQuest;

	PChar.quest.(sClearQuest).win_condition.l1 = "Timer";
	PChar.quest.(sClearQuest).win_condition.l1.date.day = GetAddingDataDay(0, 0, iTime);
	PChar.quest.(sClearQuest).win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTime);
	PChar.quest.(sClearQuest).win_condition.l1.date.year = GetAddingDataYear(0, 0, iTime);
	PChar.quest.(sClearQuest).win_condition.l1.date.hour = 12;
	PChar.quest.(sClearQuest).function = "ClearLandDefenceColony";

	string sTime = FindRussianDaysString(iTime);

	Log_Info("Вести из колонии " + PChar.ColonyBuilding.ColonyName + "!");
	AddQuestRecord("MY_COLONY", "4");
	AddQuestUserData("MY_COLONY", "sLandBattleTime", sTime);

	string sLocation, sEnemyLocator, sSoldiersLocator, sCitizenLocator;
	if(PChar.ColonyBuilding.Stage == "1")
	{
		sLocation = "Caiman_ExitTown";
		sEnemyLocator = "reload1_back";
		sSoldiersLocator = "reload3";
		sCitizenLocator = "reload3";

		Locations[FindLocation(sLocation)].hidden_effects = true;
	}
	else
	{
		if(PChar.ColonyBuilding.Plantation == true)
		{
			sLocation = "Caiman_Plantation";
			sEnemyLocator = "reload2_back";
			sSoldiersLocator = "reload1_back";
			sCitizenLocator = "reload1_back";
		}
		else
		{
			sLocation = "Caiman_ExitTown";
			sEnemyLocator = "reload2_back";
			sSoldiersLocator = "reload3";
			sCitizenLocator = "reload3";
		}
	}

	string sBattleQuest = "BattleLandDefenceColony_" + rand(1000000);
	PChar.ColonyBuilding.BattleQuest = sBattleQuest;

	PChar.quest.(sBattleQuest).win_condition.l1 = "location";
	PChar.quest.(sBattleQuest).win_condition.l1.location = sLocation;
	PChar.quest.(sBattleQuest).function = "BattleLandDefenceColony";

	PChar.ColonyBuilding.Defence.Locator.Enemy = sEnemyLocator;
	PChar.ColonyBuilding.Defence.Locator.Soldiers = sSoldiersLocator;
	PChar.ColonyBuilding.Defence.Locator.Citizen = sCitizenLocator;

	SetColonyMessageInfo("Colony", "BattleLand", "", iNation, iTime, true, true);
}

void BattleLandDefenceColony(string _tmp)
{
	string sClearQuest = PChar.ColonyBuilding.ClearQuest;
	PChar.quest.(sClearQuest).over = "yes";

	chrDisableReloadToLocation = true;
	bDisableFastReload = true;
	LAi_grp_alarmactive = true;
	InterfaceStates.Buttons.Save.enable = false;
	PChar.ColonyBuilding.Defence.Battle = true;

	int i = 0;
	int iSoldiers = sti(PChar.ColonyBuilding.Defence.Soldiers);
	int iCitizens = sti(PChar.ColonyBuilding.Defence.Citizens);
	int iEnemy = sti(PChar.ColonyBuilding.Defence.EnemyQuantity);

	ref chr;

	string sModel = "";
	string sLocator = "";
	string sAni = "man";

    	arrayNPCModelHow = 0;
	int iEnemyNation = sti(PChar.ColonyBuilding.Defence.Nation);
	string sEnemyNation = NationShortName(iEnemyNation);

	if(PChar.ColonyBuilding.Stage == "1")
	{
		ChangeCharacterAddressGroup(PChar, PChar.location, "rld", "aloc0");
	}
	else
	{
		ChangeCharacterAddressGroup(PChar, PChar.location, "rld", "loc0");
	}

	int iMusketeers = FightInColonyGetMusketeerQty(iEnemy);
	bool bMusketeer = false;

	for(i=1; i <= iEnemy; i++)
	{
		sAni = "man";

		bMusketeer = false;
		if(iEnemy - i < iMusketeers) { bMusketeer = true; }

		sLocator = PChar.ColonyBuilding.Defence.Locator.Enemy;

		if(iEnemyNation == PIRATE)
		{
			sModel = "pirate_" + (rand(24) + 1);
			if(bMusketeer) { sModel = GetPirateMushketerModel(); sAni = "mushketer"; }
		}
		else
		{
			sModel = "sold_" + sEnemyNation + "_" + (rand(7) + 1);
			if(bMusketeer) { sModel = sEnemyNation + "_mush_" + (rand(2)+1); sAni = "mushketer"; }
		}

		chr = GetCharacter(NPC_GeneratePhantomCharacter("soldier", iEnemyNation, 1, 0));
		chr.rank = GetRank(PChar, MOD_SKILL_ENEMY_RATE) + 5;
		SetFantomParamFromRank(chr, sti(chr.rank), true);
		chr.id = "My Colony Land Defence Pirate " + i;
		chr.model = sModel;
		chr.model.animation = sAni;
		chr.NotRemoved = true;
		SetNewModelToChar(chr);
    		FaceMaker(chr);
		LAi_NoRebirthEnable(chr);
		LAi_SetWarriorType(chr);
		LAi_group_MoveCharacter(chr, "EnemyFight");
		ChangeCharacterAddressGroup(chr, PChar.location, "reload", sLocator);
	}

	int iNation = sti(PChar.ColonyBuilding.ColonyNation);
	string sNation = NationShortName(iNation);

	iMusketeers = FightInColonyGetMusketeerQty(iSoldiers);
	for(i=1; i <= iSoldiers; i++)
	{
		sAni = "man";

		bMusketeer = false;
		if(iSoldiers - i < iMusketeers) { bMusketeer = true; }

		if(PChar.ColonyBuilding.SoldiersType == "officer")
		{
			sModel = "officer_" + (rand(63) + 1);

			if(bMusketeer) { sModel = "officer_" + (rand(63) + 1)+ "_mush"; sAni = "mushketer"; }
		}
		else
		{
			if(PChar.ColonyBuilding.SoldiersType == "pirate")
			{
				sAni = "man";
				sModel = "pirate_" + (rand(24) + 1);

				if(iEnemyNation == PIRATE)
				{
					sModel = "officer_" + (rand(63) + 1);
				}

				if(bMusketeer) { sModel = "Mushketer_" + (rand(4)+1); sAni = "mushketer"; }
			}
			else
			{
				sModel = "sold_" + sNation + "_" + (rand(7) + 1);

				if(bMusketeer) { sModel = sNation + "_mush_" + (rand(2)+1); sAni = "mushketer"; }

				if(iNation == iEnemyNation)
				{
					sAni = "man";
					sModel = "officer_" + (rand(63) + 1);
					if(bMusketeer) { sModel = "officer_" + (rand(63) + 1)+ "_mush"; sAni = "mushketer"; }
				}
			}
		}

		sLocator = PChar.ColonyBuilding.Defence.Locator.Soldiers;
		chr = GetCharacter(NPC_GeneratePhantomCharacter("officer_1", PIRATE, 1, 0));
		chr.rank = GetRank(PChar, MOD_SKILL_ENEMY_RATE) + 4;
		SetFantomParamFromRank(chr, sti(chr.rank), true);
		chr.id = "My Colony Mutiny Defender " + i;
		chr.model = sModel;
		chr.model.animation = sAni;
		chr.NotRemoved = true;
		SetNewModelToChar(chr);
		LAi_NoRebirthEnable(chr);
		LAi_SetWarriorType(chr);
		LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
		ChangeCharacterAddressGroup(chr, PChar.location, "reload", sLocator);
	}

	for(i=1; i <= iCitizens; i++)
	{
		sModel = "citiz_" + (rand(11)+1);
		sLocator = PChar.ColonyBuilding.Defence.Locator.Citizen;

		chr = GetCharacter(NPC_GeneratePhantomCharacter("citiz_1", PIRATE, 1, 0));
		chr.id = "My Colony Mutiny Cit Defender " + i;
		chr.rank = GetRank(PChar, MOD_SKILL_ENEMY_RATE) + 2;
		SetFantomParamFromRank(chr, sti(chr.rank), true);
		chr.model = sModel;
		chr.model.animation = "man";
		chr.NotRemoved = true;
		SetNewModelToChar(chr);
		LAi_NoRebirthEnable(chr);
		LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
		ChangeCharacterAddressGroup(chr, PChar.location, "reload", sLocator);
	}

	LAi_group_SetHearRadius("EnemyFight", 100.0);
	LAi_group_FightGroupsEx("EnemyFight", LAI_GROUP_PLAYER, true, PChar, -1, false, false);
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_SetFightMode(PChar, true);

	string cnd, enm;
	for(i=1; i<=iEnemy; i++)
	{
		cnd = "l" + i;
		enm = "My Colony Land Defence Pirate " + i;
		PChar.quest.BattleLandDefenceColonyWinner.win_condition.(cnd) = "NPC_Death";
		PChar.quest.BattleLandDefenceColonyWinner.win_condition.(cnd).character = enm;
	}

	PChar.quest.BattleLandDefenceColonyWinner.function = "BattleLandDefenceColonyWinner";
}

void BattleLandDefenceColonyWinner(string _tmp)
{
	InterfaceStates.Buttons.Save.enable = true;
	chrDisableReloadToLocation = false;
	bDisableFastReload = false;
	LAi_grp_alarmactive = false;
	PChar.ColonyBuilding.Defence.Battle = false;

	LAi_LockFightMode(PChar, false);
        LAi_SetFightMode(PChar, false);

	AddQuestRecord("MY_COLONY", "5");

	ChangeColonyMorale(70, true);

	int iSoldiers = sti(PChar.ColonyBuilding.Defence.Soldiers);
	int iCitizens = sti(PChar.ColonyBuilding.Defence.Citizens);

	string sDefender = "";
	int iDead = 0;
	int i = 0;
	for(i=1; i<=iSoldiers; i++)
	{
		sDefender = "My Colony Mutiny Defender " + i;

		if(LAi_IsDead(CharacterFromID(sDefender)))
		{
			iDead++;
		}
	}

	int iSoldiersDead = iDead * 100;
	ChangeColonySoldiers(-iSoldiersDead, false);

	iDead = 0;
	for(i=1; i<=iCitizens; i++)
	{
		sDefender = "My Colony Mutiny Cit Defender " + i;
		if(LAi_IsDead(CharacterFromID(sDefender)))
		{
			iDead++;
		}
	}

	iSoldiersDead = iDead * 70;
	ChangeColonyPopulation(-iSoldiersDead, false);

	PChar.ColonyBuilding.Defence = false;
	PChar.ColonyBuilding.Defence.Type = "";

	if(CheckAttribute(&Locations[FindLocation(PChar.Location)], "hidden_effects"))
	{
		DeleteAttribute(&Locations[FindLocation(PChar.Location)], "hidden_effects");
	}

	// Выключаем блокировку всех нападений -->
	PChar.ColonyBuilding.EventBlock = false;
	// Выключаем блокировку всех нападений <--

	AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", на колонию " + PChar.ColonyBuilding.ColonyName + " напали? На помощь гарнизону пришёл сам владелец колонии и дал жару нападавшим мерзавцам!", 5, 1);
}

void ClearLandDefenceColony(string qName)
{
	int iEnd = sti(PChar.ColonyBuilding.Defence.End);

	int iSoldiers = sti(PChar.ColonyBuilding.Defence.Soldiers);
	int iCitizens = sti(PChar.ColonyBuilding.Defence.Citizens);

	if(iSoldiers > 0)
	{
		iSoldiers /= sti(PChar.ColonyBuilding.Defence.Soldiers.Delete);
	}

	if(iCitizens > 0)
	{
		iCitizens /= sti(PChar.ColonyBuilding.Defence.Citizens.Delete);
	}

	int iSoldiersDead = iSoldiers*100;
	int iCitizensDead = iCitizens*70;

	if(iEnd == 1)
	{
		Log_Info("Вести из колонии " + PChar.ColonyBuilding.ColonyName + "!");
		AddQuestRecord("MY_COLONY", "6");

		ChangeColonySoldiers(-iSoldiersDead, false);
		ChangeColonyPopulation(-iCitizensDead, false);
		ChangeColonyMorale(70, true);
		DeleteBestGoodFromMyColony(false);
		SetColonyMessageInfo("Colony", "BattleLand", "Good", PIRATE, 0, false, true);

		AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", на колонию " + PChar.ColonyBuilding.ColonyName + " было совершено нападение? К счастью, подготовленный гарнизон справился с нападавшими.", 5, 1);
	}
	else
	{
		Log_Info("Вести из колонии " + PChar.ColonyBuilding.ColonyName + "!");
		AddQuestRecord("MY_COLONY", "7");
		ChangeColonyPopulation(-iCitizensDead, false);
		ChangeColonySoldiers(0, true);
		ChangeColonyMorale(20, true);
		ChangeColonyMoney(0, true);
		PChar.ColonyBuilding.Defence.DeadInTown = true;
		SetTimerCondition("ColonyNotSetDead", 0, 0, 6, false);

		Locations[FindLocation("Caiman_town")].hidden_effects = true;

		string sDestroyBuild = PChar.ColonyBuilding.Defence.DestroyBuild;
		DestroyBuildInCaimanColony(sDestroyBuild);
		DeleteBestGoodFromMyColony(true);

		SetColonyMessageInfo("Colony", "BattleLand", "", PIRATE, 0, false, true);
		AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", на колонию " + PChar.ColonyBuilding.ColonyName + " было совершено нападение? Нападавшим удалось прорвать оборонительные редуты гарнизона и разграбить колонию.", 5, 1);
	}

	string sBattleQuest = PChar.ColonyBuilding.BattleQuest;
	PChar.quest.(sBattleQuest).over = "yes";

	PChar.ColonyBuilding.Defence.Battle = false;
	PChar.ColonyBuilding.Defence = false;
	PChar.ColonyBuilding.Defence.Type = "";

	// Выключаем блокировку всех нападений -->
	PChar.ColonyBuilding.EventBlock = false;
	// Выключаем блокировку всех нападений <--
}

//-------------------------------------------------------------------------------
// ТРЕТИЙ ВАРИАНТ - НАПАДЕНИЕ С МОРЯ
//-------------------------------------------------------------------------------
void CreateSeaDefenceColony()
{
	if(rand(100) < 5)
	{
		Log_TestInfo("Нападения с моря не будет, так как повезло.");
		return;
	}

	// Включаем блокировку всех нападений -->
	PChar.ColonyBuilding.EventBlock = true;
	// Включаем блокировку всех нападений <--

	PChar.ColonyBuilding.Defence = true;
	PChar.ColonyBuilding.Defence.Type = "BattleSea";

	int iBaseNation = GetBaseHeroNation();
	int iNation = FindEnemyNation2Nation(iBaseNation); //FindEnemyNation2Character(nMainCharacterIndex);
	if(iNation == -1)
	{
		iNation = PIRATE;
	}

	PChar.ColonyBuilding.Defence.Nation = iNation;

	int iSquadronQuantity = rand(3) + 2;
	PChar.ColonyBuilding.Defence.ShipQuantity = iSquadronQuantity;

	int iChar = 0;
	ref chr;
	int iShipType = 0;

	int iFencingLight = sti(PChar.skill.FencingLight);
	int iFencing = sti(PChar.skill.Fencing);
	int iFencingHeavy = sti(PChar.skill.FencingHeavy);

	SetBestGoodForDeleteFromMyColony();

	string sDestroyBuild = "none";
	if(rand(5) > 3)
	{
		sDestroyBuild = GetColonyBuildDestroy();
	}
	PChar.ColonyBuilding.Defence.DestroyBuild = sDestroyBuild;
	SetBestGoodForDeleteFromMyColony();

	Group_FindOrCreateGroup("ColonySeaAttacker");
	Group_SetType("ColonySeaAttacker", "war");

	ref rShip;
	int iEnemyClass = 0;

	for(int i=1; i <= iSquadronQuantity; i++)
	{
		iChar = NPC_GenerateCharacter("ColonySeaAttacker_" + i, "pirate_" + (rand(24)+1), "man", "man", sti(PChar.rank), iNation, -1, true);
		chr = GetCharacter(iChar);

		if(iNation != PIRATE)
		{
			CreateModel(iChar, "officer", 1);
		}

		FaceMaker(chr);

		iShipType = GetShipTypeForColonyBattleSea(chr);
		chr.Ship.Type = GenerateShipExt(iShipType, false, chr);
		chr.AlwaysEnemy        = true;
		chr.Coastal_Captain    = true;
		chr.ShipTaskLock = true;
		chr.AnalizeShips = true;
		SetRandomNameToShip(chr);
		SetBaseShipData(chr);
		SetCrewQuantityFull(chr);

		FantomMakeCoolFighter(chr, iFencingLight, iFencing, iFencingHeavy, BLADE_LONG, "pistol3", 100);
		chr.SinkTenPercent = true;
		SetGeraldDetails(chr, -1, rand(7), "", "");
		SetRandGeraldSail(chr, iNation);

		Group_AddCharacter("ColonySeaAttacker", "ColonySeaAttacker_" + i);

		if(i == 1)
		{
			Group_SetGroupCommander("ColonySeaAttacker", "ColonySeaAttacker_" + i);
		}

		rShip = GetRealShip(sti(chr.Ship.Type));
		iEnemyClass += sti(rShip.Class);
	}

	int iRes = 5 - iSquadronQuantity;
	for(int e=1; e <= iRes; e++)
	{
		iEnemyClass += 7;
	}

	ref rGuardian;
	string sGuardian = "";
	int iGuardianClass = 7;

	for(int g=1; g <= 4; g++)
	{
		sGuardian = "Ship" + g;

		iChar = sti(PChar.Colony.Guardians.(sGuardian));
		if(iChar == -1)
		{
			iGuardianClass += 7;
			continue;
		}
		else
		{
			iChar = sti(PChar.Colony.Guardians.(sGuardian));
			rGuardian = GetCharacter(iChar);
			rShip = GetRealShip(sti(rGuardian.Ship.Type));
			iGuardianClass += sti(rShip.Class);
		}
	}

	if(iGuardianClass - iEnemyClass >= 8)
	{
		BattleSeaDefenceColonyClearAttackers();
		InstantColonyDefendLoose("Colony", "BattleSea");
		return;
	}

	int iEnd = 0;
	if(iGuardianClass <= iEnemyClass)
	{
		iEnd = 1;
	}

	if(rand(5) > 4)
	{
		iEnd = 0;
	}

	PChar.ColonyBuilding.Defence.End = iEnd;
	PChar.ColonyBuilding.Defence.KillShips = rand(1) * rand(1) * rand(1);

	int iTime = 10 + rand(5) - iGuardianClass;
	if(iTime < 7) { iTime = 7; }
	if(iTime > 30) { iTime = 30; }

	string sClearQuest = "ClearBattleSeaColony_" + rand(1000000);
	PChar.ColonyBuilding.ClearQuest = sClearQuest;

	PChar.quest.(sClearQuest).win_condition.l1 = "Timer";
	PChar.quest.(sClearQuest).win_condition.l1.date.day = GetAddingDataDay(0, 0, iTime);
	PChar.quest.(sClearQuest).win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTime);
	PChar.quest.(sClearQuest).win_condition.l1.date.year = GetAddingDataYear(0, 0, iTime);
	PChar.quest.(sClearQuest).win_condition.l1.date.hour = 12;
	PChar.quest.(sClearQuest).function = "ClearBattleSeaColony";

	Log_Info("Вести из колонии " + PChar.ColonyBuilding.ColonyName + "!");

	string sTime = FindRussianDaysString(iTime);

	AddQuestRecord("MY_COLONY", "8");
	AddQuestUserData("MY_COLONY", "sSeaBattleTime", sTime);

	string sNationName = GetNationNameByType(iNation) + "Gen";
	AddQuestUserData("MY_COLONY", "sNationName", XI_ConvertString(sNationName));

	string sBattleQuest = "BattleSeaDefenceColony_" + rand(1000000);
	PChar.ColonyBuilding.BattleQuest = sBattleQuest;

	PChar.quest.(sBattleQuest).win_condition.l1 = "location";
	PChar.quest.(sBattleQuest).win_condition.l1.location = "Caiman";
	PChar.quest.(sBattleQuest).function = "BattleSeaDefenceColony";

	SetColonyMessageInfo("Colony", "BattleSea", "", iNation, iTime, true, true);
}

void BattleSeaDefenceColonyClearAttackers()
{
	ref chr;
	string sCharacter = "";

	for(int i = 1; i <= 5; i++)
	{
		sCharacter = "ColonySeaAttacker_" + i;
		if(GetCharacterIndex(sCharacter) == -1)
		{
			continue;
		}

		chr = CharacterFromID(sCharacter);
		chr.LifeDay = 0;
	}
}

void BattleSeaDefenceColony(string _tmp)
{
	Island_SetReloadEnableGlobal("Caiman", false);

	string sGroup = "";
	string sShip = "";
	for(int i=1; i<=4; i++)
	{
		sGroup = "InterfaceColonyGuardians_" + i;
		sShip = "Ship" + i;
		if(Group_FindGroup(sGroup) != -1 && PChar.Colony.Guardians.(sShip).Active == true)
		{
			if(i != 1 && Group_FindGroup("InterfaceColonyGuardians_1") != -1)
			{
				Group_SetPursuitGroup(sGroup, "InterfaceColonyGuardians_1");
			}
			else
			{
				Group_SetAddress(sGroup, "Caiman", "quest_ships", "Quest_ship_" + (7-i));
			}


			for(q=1; q<=Group_GetCharactersNum("ColonySeaAttacker"); q++)
			{
				iCharacter = Group_GetCharacterIndexR(Group_GetGroupByID("ColonySeaAttacker"), i);
				//Group_SetEnemyToCharacter(sGroup, iCharacter);
			}

			Group_SetTaskAttack(sGroup, "ColonySeaAttacker");
			Group_LockTask(sGroup);
		}
	}

	Group_SetAddress("ColonySeaAttacker", "Caiman", "quest_ships", "Quest_ship_7");

	int q=0;
	int iCharacter = 0;
	for(q=1; q<=4; q++)
	{
		sGroup = "InterfaceColonyGuardians_" + q;
		if(Group_FindGroup(sGroup) != -1)
		{
			iCharacter = Group_GetGroupCommanderIndex(sGroup);
			Group_SetEnemyToCharacter("ColonySeaAttacker", iCharacter);
		}
	}

	Group_SetEnemyToCharacter("ColonySeaAttacker", nMainCharacterIndex);
	Group_SetTaskAttack("ColonySeaAttacker", PLAYER_GROUP);
	Group_LockTask("ColonySeaAttacker");

        UpdateRelations();

	PChar.quest.BattleSeaDefenceColonyWinner.win_condition.l1 = "Group_Death";
	PChar.quest.BattleSeaDefenceColonyWinner.win_condition.l1.group = "ColonySeaAttacker";
	PChar.quest.BattleSeaDefenceColonyWinner.function = "BattleSeaDefenceColonyWinner";

	PChar.quest.ClearBattleSeaColonyFromMapEnter.win_condition.l1 = "MapEnter";
	PChar.quest.ClearBattleSeaColonyFromMapEnter.function = "ClearBattleSeaColonyFromMapEnter";
}

void ClearBattleSeaColonyFromMapEnter(string qName)
{
	string sClearQuest = PChar.ColonyBuilding.ClearQuest;
	PChar.quest.(sClearQuest).over = "yes";
	PChar.quest.BattleSeaDefenceColonyWinner.over = "yes";

	ClearBattleSeaColony("");
}

void BattleSeaDefenceColonyWinner(string _tmp)
{
	string sClearQuest = PChar.ColonyBuilding.ClearQuest;
	PChar.quest.(sClearQuest).over = "yes";
	PChar.quest.ClearBattleSeaColony.over = "yes";
	PChar.quest.ClearBattleSeaColonyFromMapEnter.over = "yes";

	AddQuestRecord("MY_COLONY", "5");

	Group_DeleteGroup("ColonySeaAttacker");
	Island_SetReloadEnableGlobal("Caiman", true);

	ChangeColonyMorale(90, true);
	PChar.ColonyBuilding.Defence = false;
	PChar.ColonyBuilding.Defence.Type = "";

	BattleSeaDefenceColonyClearAttackers();
	CheckDeadColonyGuard();

	// Выключаем блокировку всех нападений -->
	PChar.ColonyBuilding.EventBlock = false;
	// Выключаем блокировку всех нападений <--

	PChar.quest.BattleSeaDefenceColonyExitBattleField.win_condition.l1 = "ExitFromLocation";
	PChar.quest.BattleSeaDefenceColonyExitBattleField.win_condition.l1.location = PChar.location;
	PChar.quest.BattleSeaDefenceColonyExitBattleField.function = "BattleSeaDefenceColonyExitBattleField";

	int iNation = sti(PChar.ColonyBuilding.Defence.Nation);
	string sNationName = GetNationNameByType(iNation) + "Gen";
	AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", на колонию " + PChar.ColonyBuilding.ColonyName + " было совершено нападение эскадрой под флагом " + XI_ConvertString(sNationName) + ". На подмогу прибыл сам владелец колонии! Нападавшая эскадра потерпела поражение и отправилась на дно.", 5, 1);
}

void BattleSeaDefenceColonyExitBattleField(string qName)
{
	string sShip = "";
	for(int i=1; i<=4; i++)
	{
		sShip = "Ship" + i;
		if(Group_FindGroup("InterfaceColonyGuardians_" + i) != -1 && PChar.Colony.Guardians.(sShip).Active == true)
		{
			Group_SetAddress("InterfaceColonyGuardians_" + i, "Caiman", "quest_ships", "Quest_ship_" + i);
			Group_SetTaskNone("InterfaceColonyGuardians_" + i);
		}
	}
}

void ClearBattleSeaColony(string qName)
{
	Group_DeleteGroup("ColonySeaAttacker");
	BattleSeaDefenceColonyClearAttackers();

	Island_SetReloadEnableGlobal("Caiman", true);

	int iEnd = sti(PChar.ColonyBuilding.Defence.End);
	int iSoldiers = sti(PChar.ColonyBuilding.Defence.Soldiers);
	int iSoldiersDead = iSoldiers*(rand(3)+2);

	int iNation = sti(PChar.ColonyBuilding.Defence.Nation);
	string sNationName = GetNationNameByType(iNation) + "Abl";

	Log_Info("Вести из колонии " + PChar.ColonyBuilding.ColonyName + "!");
	if(iEnd == 1)
	{
		AddQuestRecord("MY_COLONY", "14");
		sNationName = "people" + GetNationNameByType(iNation) + "Dat";
		AddQuestUserData("MY_COLONY", "sNationName", XI_ConvertString(sNationName));

		ChangeColonySoldiers(-iSoldiersDead, false);
		ChangeColonyMorale(50, true);

		DeleteBestGoodFromMyColony(false);
		SetColonyMessageInfo("Colony", "BattleSea", "Good", iNation, 0, 0, true);

		AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", на колонию " + PChar.ColonyBuilding.ColonyName + " было совершено нападение эскадрой под флагом " + XI_ConvertString(sNationName) + ". Но охрана береговой линии не сплоховала и оправила мерзавцев, нарушивших спокойствие колонии, к праотцам.", 5, 1);
	}
	else
	{
		AddQuestRecord("MY_COLONY", "9");
		sNationName = GetNationNameByType(iNation) + "Abl";
		AddQuestUserData("MY_COLONY", "sNationName", XI_ConvertString(sNationName));

		ChangeColonyPopulation((-rand(100)-100), true);
		ChangeColonySoldiers(0, true);
		ChangeColonyMorale(0, true);
		ChangeColonyMoney(0, true);
		PChar.ColonyBuilding.Defence.DeadInTown = true;
		SetTimerCondition("ColonyNotSetDead", 0, 0, 6, false);
		PChar.ColonyBuilding.Defence.KillShips = 4;
		string sDestroyBuild = PChar.ColonyBuilding.Defence.DestroyBuild;
		DestroyBuildInCaimanColony(sDestroyBuild);
		DeleteBestGoodFromMyColony(true);
		SetColonyMessageInfo("Colony", "BattleSea", "", iNation, 0, false, true);
		AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", на колонию " + PChar.ColonyBuilding.ColonyName + " было совершено нападение " + XI_ConvertString(sNationName) + ". И вполне удачно - оборона не выдержала мощного натиска и пала перед врагом.", 5, 1);
	}

	int iKillShips = sti(PChar.ColonyBuilding.Defence.KillShips);
	for(int ks = 1; ks <= iKillShips; ks++)
	{
		KillColonyGuarding(ks);
	}

	CheckDeadColonyGuard();
	RepairAllGuardShips();

	string sBattleQuest = PChar.ColonyBuilding.BattleQuest;
	PChar.quest.(sBattleQuest).over = "yes";
	PChar.quest.ClearBattleSeaColonyFromMapEnter.over = "yes";

	PChar.ColonyBuilding.Defence = false;
	PChar.ColonyBuilding.Defence.Type = "";

	// Выключаем блокировку всех нападений -->
	PChar.ColonyBuilding.EventBlock = false;
	// Выключаем блокировку всех нападений <--

	PChar.quest.BattleSeaDefenceColonyExitBattleField.win_condition.l1 = "ExitFromLocation";
	PChar.quest.BattleSeaDefenceColonyExitBattleField.win_condition.l1.location = PChar.location;
	PChar.quest.BattleSeaDefenceColonyExitBattleField.function = "BattleSeaDefenceColonyExitBattleField";
}

/////////////////////////////////////////////////////////////////////////////////
// МГНОВЕННОЕ ПОРАЖЕНИЕ
/////////////////////////////////////////////////////////////////////////////////
void InstantColonyDefendLoose(string sTarget, string sType)
{
	Log_Info("Вести из колонии " + PChar.ColonyBuilding.ColonyName + "!");

	int iRebels = 0;
	int iMoney = 0;
	int iCitizensDead = sti(rand(15)+10)*10;

	int iNation = PIRATE;
	string sNationName = "";
	string sDestroyBuild = "Store";

	int iOreMinus, iGoodMinus, iGold, iSilver, iIron, iSlaves;
	switch(sTarget)
	{
		case "Colony":
			switch(sType)
			{
				case "Mutiny":
					AddQuestRecord("MY_COLONY", "26");
					iRebels = sti(PChar.ColonyBuilding.Defence.EnemyQuantity);
					iMoney = sti(PChar.ColonyBuilding.Money);
					ChangeColonyMoney(-(iMoney/iRebels), false);

					AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", в колонии " + PChar.ColonyBuilding.ColonyName + " вспыхнул мятеж? Мятежники с легкостью овладели ситуацией, потому что владелец колонии не удосужился укрепить колонию!", 5, 1);
				break;

				case "BattleLand":
					sDestroyBuild = PChar.ColonyBuilding.Defence.DestroyBuild;

					AddQuestRecord("MY_COLONY", "27");
					ChangeColonyMoney(0, true);
					DestroyBuildInCaimanColony(sDestroyBuild);
					DeleteBestGoodFromMyColony(true);

					AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", на колонию " + PChar.ColonyBuilding.ColonyName + " было совершено нападение! Напавшие очень удивились, когда не обнаружили у стен колонии охраняющего отряда. А колония была разграблена.", 5, 1);
				break;

				case "BattleSea":
					iNation = sti(PChar.ColonyBuilding.Defence.Nation);
					sNationName = GetNationNameByType(iNation) + "Gen";
					sDestroyBuild = PChar.ColonyBuilding.Defence.DestroyBuild;

					AddQuestRecord("MY_COLONY", "28");
					AddQuestUserData("MY_COLONY", "sNationName", XI_ConvertString(sNationName));
					ChangeColonyMoney(0, true);
					PChar.ColonyBuilding.Defence.KillShips = 4;
					DestroyBuildInCaimanColony(sDestroyBuild);
					DeleteBestGoodFromMyColony(true);
					Group_DeleteGroup("ColonySeaAttacker");
					Island_SetReloadEnableGlobal("Caiman", true);

					AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", на колонию " + PChar.ColonyBuilding.ColonyName + " было совершено силами эскадры под флагом " + XI_ConvertString(sNationName) + "?! Напавшие очень удивились, когда не обнаружили у стен в водах колонии кораблей охраны. Колония была разграблена.", 5, 1);
				break;
			}

			ChangeColonyPopulation(-iCitizensDead, false);
			ChangeColonySoldiers(0, true);
			ChangeColonyMorale(0, true);

			PChar.ColonyBuilding.Defence = false;
			PChar.ColonyBuilding.Defence.Type = "";
			PChar.ColonyBuilding.Defence.DeadInTown = true;
			PChar.ColonyBuilding.Defence.Battle = false;
			SetTimerCondition("ColonyNotSetDead", 0, 0, 6, false);
		break;

		case "Mines":
			switch(sType)
			{
				ChangeMinesSoldiers(0, true);
				ChangeMinesSlaves(0, true);

				case "Mutiny":
					iRebels = sti(PChar.Mines.Defence.EnemyQuantity);
					AddQuestRecord("MY_COLONY", "29");

					iOreMinus = iRebels * (3 + rand(2));
					ChangeMinesOre(-iOreMinus, "Gold", false);
					iOreMinus = iRebels * (3 + rand(2));
					ChangeMinesOre(-iOreMinus, "Silver", false);
					iOreMinus = iRebels * (3 + rand(2));
					ChangeMinesOre(-iOreMinus, "Iron", false);

					iGoodMinus = iRebels * 50;
					ChangeMinesMainGoods(-iGoodMinus, "Food", false);
					iGoodMinus = iRebels * 25;
					ChangeMinesMainGoods(-iGoodMinus, "Medicament", false);

					AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", на рудниках колонии " + PChar.ColonyBuilding.ColonyName + " вспыхнул мятеж. Из-за отсутствия необходимого гарнизона, мятежники легко справились с остальными и обратились в бегство.", 5, 1);
				break;

				case "BattleLand":
					AddQuestRecord("MY_COLONY", "30");

					iGold = sti(PChar.Mines.Defence.Minus.Gold);
					iSilver = sti(PChar.Mines.Defence.Minus.Silver);
					iIron = sti(PChar.Mines.Defence.Minus.Iron);
					iSlaves = sti(PChar.Mines.Defence.Minus.Slaves);

					ChangeMinesOre(-iGold, "Gold", false);
					ChangeMinesOre(-iSilver, "Silver", false);
					ChangeMinesOre(-iIron, "Iron", false);

					AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", на рудники колонии " + PChar.ColonyBuilding.ColonyName + " было совершено нападение?! Самое интересное, что рудники почти никто не охранял!", 5, 1);
				break;
			}

			PChar.Mines.Defence = false;
			PChar.Mines.Defence.Type = "";
			PChar.Mines.Defence.DeadInTown = true;
			PChar.Mines.Defence.Battle = false;

			SetTimerCondition("MinesNotSetDead", 0, 0, 6, false);
			SetTimerCondition("MinesUptade5", 0, 0, 10, false);
		break;

		case "Plantation":
			switch(sType)
			{
				case "Mutiny":
					iRebels = sti(PChar.Plantation.Defence.EnemyQuantity);

					AddQuestRecord("MY_COLONY", "31");
					ChangePlantationSlaves(0, true);
					ChangePlantationSoldiers(0, true);

					iOreMinus = iRebels * (3 + rand(2));
					ChangePlantationExtract(-iOreMinus, "Sugar", false);
					iOreMinus = iRebels * (3 + rand(2));
					ChangePlantationExtract(-iOreMinus, "Coffee", false);

					iGoodMinus = iRebels * 50;
					ChangePlantationGoods(-iOreMinus, "Food", false);
					iGoodMinus = iRebels * 25;
					ChangePlantationGoods(-iOreMinus, "Medicament", false);

					AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", на плантации, принадлежащей колонии " + PChar.ColonyBuilding.ColonyName + " вспыхнул мятеж?! Мятежники тут же праздновали победу, потому что охраняемого гарнизона почти не было!", 5, 1);
				break;

				PChar.Plantation.Defence = false;
				PChar.Plantation.Defence.Type = "";
				PChar.Plantation.Defence.DeadInTown = true;
				PChar.Plantation.Defence.Battle = false;

				SetTimerCondition("PlantationNotSetDead", 0, 0, 6, false);
				SetTimerCondition("PlantationUptade5", 0, 0, 10, false);
			}
		break;
	}

	PChar.ColonyBuilding.EventBlock = false;

	sType += "Loose";
	SetColonyMessageInfo(sTarget, sType, "", iNation, 0, 0, 1);
}

//-------------------------------------------------------------------------------
// OTHER FUNCTIONS
//-------------------------------------------------------------------------------
void SetBestGoodForDeleteFromMyColony()
{
	string sGoodName = "";
	string sGood = "";

	ref rStoreHouse = &Stores[STORE_HOUSE];

	int iDeleteGoods = 0;
	int iQuantity = 0;
	int iRand = 0;
	for(int i=0; i < GOODS_QUANTITY; i++)
	{
		if(sti(Goods[i].Cost) >= 100)
		{
			sGoodName = Goods[i].Name;

			if(sti(rStoreHouse.Goods.(sGoodName).Quantity) > 0)
			{
				iRand = rand(5) + 3;
				iQuantity = sti(rStoreHouse.Goods.(sGoodName).Quantity) / iRand;

				if(iQuantity > 0)
				{
					iDeleteGoods++;
					sGood = "Good_" + iDeleteGoods;

					PChar.ColonyBuilding.DeleteGoods.(sGood) = sGoodName;
					PChar.ColonyBuilding.DeleteGoods.(sGood).Qty = iQuantity;
				}
			}
		}
	}

	PChar.ColonyBuilding.DeleteGoods.DeleteQty = iDeleteGoods;
}

void DeleteBestGoodFromMyColony(bool bDelete)
{
	if(!bDelete)
	{
		return;
	}

	int iDeleteGoods = 0;
	if(CheckAttribute(PChar, "ColonyBuilding.DeleteGoods.DeleteQty"))
	{
		iDeleteGoods = sti(PChar.ColonyBuilding.DeleteGoods.DeleteQty);
	}

	if(iDeleteGoods <= 0)
	{
		return;
	}

	string sGood, sGoodName;
	int iQty = 0;

	Log_InfoS("Склад разграблен.");

	int iGood = 0;
	int iStoreQty = 0;
	for(int i=1; i<=iDeleteGoods; i++)
	{
		sGood = "Good_" + i;
		sGoodName = PChar.ColonyBuilding.DeleteGoods.(sGood);
		iQty = sti(PChar.ColonyBuilding.DeleteGoods.(sGood).Qty);

		iGood = FindGood(sGoodName);
		iStoreQty = Stores[STORE_HOUSE].Goods.(sGoodName).Quantity;

		SetStoreGoodsEdition(&Stores[STORE_HOUSE], iGood, iStoreQty - iQty, iQty, true);

		Log_Info(XI_ConvertString(sGoodName) + " в количестве " + iQty + " шт.");
	}

	if(CheckAttribute(PChar, "ColonyBuilding.DeleteGoods"))
	{
		DeleteAttribute(PChar, "ColonyBuilding.DeleteGoods");
	}

	PChar.ColonyBuilding.DeleteGoods = "";
}

void SetDeadmansToLocation(ref loc, string sType)
{
	if(actLoadFlag) return;
	if(loc.id != "Caiman_town" && loc.id != "Caiman_Plantation" && loc.id != "Caiman_mines") return;

	int iPopulation = 100;//sti(PChar.ColonyBuilding.Population);
	int iMan = iPopulation / 10;
	int iWoman = iPopulation / 20;
    int iMassive;
	string model[23];

	if(iMan > 15) iMan = 15;
	if(iMan < 0) iMan = 0;

	if(iWoman > 10) iWoman = 10;
	if(iWoman < 0) iWoman = 0;

	if(sti(PChar.ColonyBuilding.Stage) <= 1)
	{
		if(iMan > 8) iMan = 8;
		if(iWoman > 7) iWoman = 7;
	}

	int i=1;
	int b=1;
	int iSex = 1;

	ref dead;
	string sModel, sAni;

	iSex = 1;

	for(i=1; i <= iMan; i++)
	{
		dead = GetCharacter(NPC_GeneratePhantomCharacter("citiz_1", PIRATE, iSex, 0));

		sModel = "citiz_" + (rand(11)+1);
		sAni = "man";

		if(sType == "pirate")
		{
            model[0] = "prizon_1";
            model[1] = "prizon_2";
            model[2] = "prizon_3";
            model[3] = "prizon_4";
            model[4] = "prizon_5";
            model[5] = "prizon_6";
            model[6] = "prizon_7";
	        model[7] = "prizon_8";
            model[8] = "pirate_1";
            model[9] = "prison_5";
            model[10] = "pirate_1";
            model[11] = "pirate_11";
            model[12] = "pirate_12";
            model[13] = "pirate_13";
            model[14] = "pirate_14";
            model[15] = "pirate_15";
            model[16] = "pirate_16";
            model[17] = "pirate_21";
            model[18] = "pirate_25";
            model[19] = "PKM_rab_1";
            model[20] = "PKM_rab_2";
            model[21] = "PKM_rab_3";
            model[22] = "PKM_rab_4";

			iMassive = rand(22);

		    sModel = model[iMassive];
		    sAni = "man";
			/* if(model[iMassive] == "pirate_1" || model[iMassive] == "pirate_11" || model[iMassive] == "pirate_12" || model[iMassive] == "pirate_13" || model[iMassive] == "pirate_14" || model[iMassive] == "pirate_15" || model[iMassive] == "pirate_16" || model[iMassive] == "pirate_21" || model[iMassive] == "pirate_25") sAni = "man"; */
		}


		dead.model = sModel;
		dead.model.animation = sAni;
		dead.NotRemoved = true;
		SetNewModelToChar(dead);

		LAi_SetImmortal(dead, true);
		LAi_SetActorType(dead);
		LAi_ActorSetLayMode(dead);
		PlaceCharacter(dead, "goto", "random_free");
		RemoveCharacterEquip(dead, BLADE_ITEM_TYPE);
		RemoveCharacterEquip(dead, GUN_ITEM_TYPE);

		for(b=0; b <= 4; b++)
		{
			LaunchBlood(dead, 7.0, true);
		}
	}

	if(sType == "pirate")
	{
		return;
	}

	iSex = 0;
	for(i=1; i <= iWoman; i++)
	{
		dead = GetCharacter(NPC_GeneratePhantomCharacter("girl_1", PIRATE, iSex, 0));

		sModel = "girl_" + (rand(10)+1);
		sAni = "towngirl";

		dead.model = sModel;
		dead.model.animation = sAni;
		dead.NotRemoved = true;
		SetNewModelToChar(dead);

		LAi_SetImmortal(dead, true);
		LAi_SetActorType(dead);
		LAi_ActorSetLayMode(dead);
		PlaceCharacter(dead, "goto", "random_free");
		RemoveCharacterEquip(dead, BLADE_ITEM_TYPE);
		RemoveCharacterEquip(dead, GUN_ITEM_TYPE);

		for(b=0; b <= 4; b++)
		{
			LaunchBlood(dead, 7.0, true);
		}
	}
}

int FightInColonyGetMusketeerQty(int iQty)
{
	if(iQty < 5)
	{
		return 0;
	}

	if(iQty >= 20)
	{
		return iQty / 4;
	}
	else
	{
		return iQty / 3;
	}

	return 0;
}

int GetColonyMinPeople()
{
	int iQty = 0;

	if(PChar.ColonyBuilding.Store == true && PChar.ColonyBuilding.Store.BuildingTime == false) 		{ iQty++; }
	if(PChar.ColonyBuilding.Shipyard == true && PChar.ColonyBuilding.Shipyard.BuildingTime == false) 	{ iQty++; }
	if(PChar.ColonyBuilding.Tavern == true && PChar.ColonyBuilding.Tavern.BuildingTime == false) 		{ iQty += 2; }
	if(PChar.ColonyBuilding.Church == true && PChar.ColonyBuilding.Church.BuildingTime == false) 		{ iQty++; }
	if(PChar.ColonyBuilding.Bank == true && PChar.ColonyBuilding.Bank.BuildingTime == false) 		{ iQty++; }
	if(PChar.ColonyBuilding.HeadPort == true && PChar.ColonyBuilding.HeadPort.BuildingTime == false) 	{ iQty++; }
	if(PChar.ColonyBuilding.StoreHouse == true && PChar.ColonyBuilding.StoreHouse.BuildingTime == false) 	{ iQty++; }

	return iQty;
}

void ChangeColonyPopulation(int iQty, bool bSet)
{
	int iMax = sti(PChar.ColonyBuilding.Population.Max);

	if(bSet)
	{
		PChar.ColonyBuilding.Population = iQty;
	}
	else
	{
		PChar.ColonyBuilding.Population = sti(PChar.ColonyBuilding.Population) + iQty;
	}

	if(sti(PChar.ColonyBuilding.Population) < 0) PChar.ColonyBuilding.Population = 0;
	if(sti(PChar.ColonyBuilding.Population) > iMax) PChar.ColonyBuilding.Population = iMax;
}

void ChangeColonyMorale(int iQty, bool bSet)
{
	if(bSet)
	{
		PChar.ColonyBuilding.Population.Morale = iQty;
	}
	else
	{
		PChar.ColonyBuilding.Population.Morale = sti(PChar.ColonyBuilding.Population.Morale) + iQty;
	}

	if(sti(PChar.ColonyBuilding.Population.Morale) < 0) PChar.ColonyBuilding.Population.Morale = 0;
	if(sti(PChar.ColonyBuilding.Population.Morale) > 100) PChar.ColonyBuilding.Population.Morale = 100;
}

void ChangeColonySoldiers(int iQty, bool bSet)
{
	int iMax = sti(PChar.ColonyBuilding.Soldiers.MaxQuantity);

	if(bSet)
	{
		PChar.ColonyBuilding.Soldiers = iQty;
	}
	else
	{
		PChar.ColonyBuilding.Soldiers = sti(PChar.ColonyBuilding.Soldiers) + iQty;
	}

	if(sti(PChar.ColonyBuilding.Soldiers) < 0) PChar.ColonyBuilding.Soldiers = 0;
	if(sti(PChar.ColonyBuilding.Soldiers) > iMax) PChar.ColonyBuilding.Soldiers = iMax;
}

void ChangeColonyGoods(int iQty, string sGood)
{
	int iMax = sti(PChar.ColonyBuilding.(sGood).MaxQuantity);

	PChar.ColonyBuilding.(sGood) = sti(PChar.ColonyBuilding.(sGood)) + iQty;

	if(sti(PChar.ColonyBuilding.(sGood)) < 0) PChar.ColonyBuilding.(sGood) = 0;
	if(sti(PChar.ColonyBuilding.(sGood)) > iMax) PChar.ColonyBuilding.(sGood) = iMax;
}

void ChangeColonyMoney(int iQty, bool bSet)
{
	if(bSet)
	{
		PChar.ColonyBuilding.Money = iQty;
	}
	else
	{
		PChar.ColonyBuilding.Money = sti(PChar.ColonyBuilding.Money) + iQty;
	}

	if(sti(PChar.ColonyBuilding.Money) < 0) PChar.ColonyBuilding.Money = 0;
}

int GetMyColonyMoney()
{
	if(!CheckAttribute(PChar, "ColonyBuilding.Money"))
	{
		return 0;
	}

	return sti(PChar.ColonyBuilding.Money);
}

void SetColonyMessageInfo(string sTarget, string sType, string sEnd, int iNation, int iTime, bool bFirst, bool bInterface)
{
	PChar.ColonyBuilding.MessageInfo.Target = sTarget;
	PChar.ColonyBuilding.MessageInfo.Type = sType;
	PChar.ColonyBuilding.MessageInfo.End = sEnd;
	PChar.ColonyBuilding.MessageInfo.Nation = iNation;
	PChar.ColonyBuilding.MessageInfo.Time = iTime;
	PChar.ColonyBuilding.MessageInfo.First = bFirst;

	if(!dialogRun && !bQuestCheckProcessFreeze && !bAbordageStarted)
	{
		if(bInterface)
		{
			DoQuestFunctionDelay("ColonyMessageStartInfo", 2.5);
		}
	}
}

void ColonyMessageStartInfo(string _tmp)
{
	LaunchAttackMessage();
}

// Разрушить/закрыть здание
void DestroyBuildInCaimanColony(string sBuild)
{
	if(sBuild == "none")
	{
		return; // не сломали ничего
	}

	if(PChar.ColonyBuilding.(sBuild) == false)
	{
		return; // такого здания ещё не построили
	}

	PChar.ColonyBuilding.(sBuild) = false;
	PChar.ColonyBuilding.(sBuild).BuildingTime = false;

	int iCost = 0;

	switch(sBuild)
	{
		case "Store":
			Locations[FindLocation("Caiman_town")].reload.l6.disable = true;
			iCost = 15000 + rand(2500);
		break;

		case "Shipyard":
			Locations[FindLocation("Caiman_town")].reload.l5.disable = true;
			iCost = 17500 + rand(2850);
		break;

		case "Tavern":
			Locations[FindLocation("Caiman_town")].reload.l4.disable = true;
			iCost = 15000 + rand(500);
		break;

		case "Church":
			Locations[FindLocation("Caiman_town")].reload.l7.disable = true;
			iCost = 20000 + rand(2500);
		break;

		case "Bank":
			Locations[FindLocation("Caiman_town")].reload.l8.disable = true;
			iCost = 20000 + rand(2500);
		break;

		case "HeadPort":
			Locations[FindLocation("Caiman_town")].reload.l10.disable = true;
			iCost = 12500 + rand(2550);
		break;
	}

	PChar.ColonyBuilding.(sBuild).Cost = iCost;

	AddQuestRecord("MY_COLONY", "15");
	AddQuestUserData("MY_COLONY", "sDestroyBuild", XI_ConvertString("Destroy" + sBuild));

	if(sBuild == "Store")
	{
		AddQuestRecord("MY_COLONY", "32");
	}
}

void RenamedColonyCaiman()
{
	worldMap.labels.Shore17.text = "";

	string sColonyName = PChar.ColonyBuilding.ColonyName;
	worldMap.labels.Shore17.text = "порт " + sColonyName;
	worldMap.labels.Shore17.icon = PIRATE;
}

string GetColonyBuildDestroy()
{
	switch(rand(5))
	{
		case 0: return "Store"; break;
		case 1: return "Shipyard"; break;
		case 2: return "Tavern"; break;
		case 3: return "Church"; break;
		case 4: return "Bank"; break;
		case 5: return "HeadPort"; break;
	}

	return "Store";
}

int GetShipTypeForColonyBattleSea(ref Hunter)
{
    int Squadron, hcrew;

    int j, q;
    object rShip;
    bool bOk = false;
    int iNation = sti(Hunter.nation);
    aref aNation;
    string sAttr;

    while(!bOk)
    {
        Squadron = 100 + rand(24); // LEO: Чуть-чуть 2 класс и остальное 1 класс

        rShip = GetShipByType(Squadron);
        makearef(aNation, rShip.nation);
        q = GetAttributesNum(aNation);
        for(j = 0; j < q; j++)
        {
            sAttr = GetAttributeName(GetAttributeN(aNation, j));
            if(GetNationTypeByName(sAttr) == iNation && rShip.nation.(sAttr) == true) bOk = true;
        }
    }
    return Squadron;
}

/////////////////////////////////////////////////////////////////////////////////
// АВТОЗАКУПКА ТОВАРА НА КОЛОНИЮ, РУДНИКИ И ПЛАНТАЦИЮ
/////////////////////////////////////////////////////////////////////////////////
int GetSumAutoPurchaseColonyGoods(string sType, bool bCurrent)
{
	int iCost = 0;
	int iNeedFood = 0;
	int iNeedMedicament = 0;
	int iNeedTools = 0;

	if(bCurrent)
	{
		switch(sType)
		{
			case "Colony":
				iNeedFood = sti(PChar.ColonyBuilding.Food.MaxQuantity) - sti(PChar.ColonyBuilding.Food);
				iNeedMedicament = sti(PChar.ColonyBuilding.Medicament.MaxQuantity) - sti(PChar.ColonyBuilding.Medicament);
			break;

			case "Mines":
				iNeedFood = sti(PChar.Mines.FoodQuantity.Max) - sti(PChar.Mines.FoodQuantity);
				iNeedMedicament = sti(PChar.Mines.MedicamentQuantity.Max) - sti(PChar.Mines.MedicamentQuantity);
			break;

			case "Plantation":
				iNeedFood = sti(PChar.Plantation.Food.MaxQuantity) - sti(PChar.Plantation.Food.Quantity);
				iNeedMedicament = sti(PChar.Plantation.Medicament.MaxQuantity) - sti(PChar.Plantation.Medicament.Quantity);
				iNeedTools = sti(PChar.Plantation.Items.MaxQuantity) - sti(PChar.Plantation.Items.Quantity);
			break;
		}
	}
	else
	{
		switch(sType)
		{
			case "Colony":
				iNeedFood = sti(PChar.ColonyBuilding.Food.MaxQuantity);
				iNeedMedicament = sti(PChar.ColonyBuilding.Medicament.MaxQuantity);
			break;

			case "Mines":
				iNeedFood = sti(PChar.Mines.FoodQuantity.Max);
				iNeedMedicament = sti(PChar.Mines.MedicamentQuantity.Max);
			break;

			case "Plantation":
				iNeedFood = sti(PChar.Plantation.Food.MaxQuantity);
				iNeedMedicament = sti(PChar.Plantation.Medicament.MaxQuantity);
				iNeedTools = sti(PChar.Plantation.Items.MaxQuantity);
			break;
		}
	}

	iNeedFood *= COLONY_AUTO_PURCHASE_FOOD;
	iNeedMedicament *= COLONY_AUTO_PURCHASE_MEDICAMENT;
	iNeedTools *= COLONY_AUTO_PURCHASE_TOOLS;

	iCost = iNeedFood + iNeedMedicament + iNeedTools;

	return iCost;
}

void AutoPurchaseColonyGoods(string sType)
{
	bool bCan = PChar.ColonyBuilding.(sType).AutoPurchase;
	if(!bCan)
	{
		return;
	}

	if(PChar.ColonyBuilding.Store == false)
	{
		return;
	}

	int iCost = GetSumAutoPurchaseColonyGoods(sType, true);
	if(iCost <= 0)
	{
		return;
	}

	int iColonyMoney = sti(PChar.ColonyBuilding.Money);

	string sTypeText = "колонии";
	switch(sType)
	{
		case "Colony": sTypeText = "вашей колонии ''" + PChar.ColonyBuilding.ColonyName + "''"; break;
		case "Mines": sTypeText = "ваших рудников"; break;
		case "Plantation": sTypeText = "вашей плантации"; break;
	}

	if(iColonyMoney < iCost)
	{
		Log_InfoS("Авто-закупка для " + sTypeText + " не может быть произведена, так как в казне недостаточно денег.");
		return;
	}
	else
	{
		ChangeColonyMoney(-iCost, false);
	}

	int iFoodMax = 0;
	int iMedicamentMax = 0;
	int iToolsMax = 0;

	switch(sType)
	{
		case "Colony":
			iFoodMax = sti(PChar.ColonyBuilding.Food.MaxQuantity);
			iMedicamentMax = sti(PChar.ColonyBuilding.Medicament.MaxQuantity);

			ChangeColonyGoods(iFoodMax, "Food");
			ChangeColonyGoods(iMedicamentMax, "Medicament");

			Log_InfoS("Авто-закупка необходимого провианта и медикаментов для вашей колонии ''" + PChar.ColonyBuilding.ColonyName + "'' выполнена.");
			Log_Info("Цена составила: " + iCost + " пиастров.");
		break;

		case "Mines":
			iFoodMax = sti(PChar.Mines.FoodQuantity.Max);
			iMedicamentMax = sti(PChar.Mines.MedicamentQuantity.Max);

			ChangeMinesMainGoods(iFoodMax, "Food", true);
			ChangeMinesMainGoods(iMedicamentMax, "Medicament", true);

			Log_InfoS("Авто-закупка необходимого провианта и медикаментов для ваших рудников выполнена.");
			Log_Info("Цена составила: " + iCost + " пиастров.");
		break;

		case "Plantation":
			iFoodMax = sti(PChar.Plantation.Food.MaxQuantity);
			iMedicamentMax = sti(PChar.Plantation.Medicament.MaxQuantity);
			iToolsMax = sti(PChar.Plantation.Items.MaxQuantity);

			ChangePlantationGoods(iFoodMax, "Food", true);
			ChangePlantationGoods(iMedicamentMax, "Medicament", true);
			ChangePlantationGoods(iToolsMax, "Items", true);

			Log_InfoS("Авто-закупка необходимого провианта, медикаментов и инструментов для вашей плантации выполнена.");
			Log_Info("Цена составила: " + iCost + " пиастров.");
		break;
	}
}

//-------------------------------------------------------------------------------
// РУДНИКИ
//-------------------------------------------------------------------------------
void MinesBuilding(string sMine)
{
	ref PChar = GetMainCharacter();

	sMine = sMine + "Mine";

	PChar.Mines.(sMine) = true;

	PChar.Mines.GoldQuantity = 0;
	PChar.Mines.SilverQuantity = 0;
	PChar.Mines.IronQuantity = 0;
	PChar.Mines.GuardiansQuantity = 0;
	PChar.Mines.HireGuardiansQuantity = 0;
	PChar.Mines.GuardiansCost = 200;
	PChar.Mines.MaxGuardiansQuantity = 100;
	PChar.Mines.SlavesQuantity = 0;
	PChar.Mines.MaxSlavesQuantity = 100;
	PChar.Mines.FoodQuantity = 0;
	PChar.Mines.Temp.GoldQuantity = 0;
	PChar.Mines.Temp.SilverQuantity = 0;
	PChar.Mines.Temp.IronQuantity = 0;
	PChar.Mines.Temp.GuardiansQuantity = 0;
	PChar.Mines.Temp.SlavesQuantity = 0;
	PChar.Mines.Temp.FoodQuantity = 0;
}

//-------------------------------------------------------------------------------
// STOREHOUSE
//-------------------------------------------------------------------------------
void StoreHouseInit()
{
	ref PChar = GetMainCharacter();

	PChar.ColonyBuilding.StoreHouse.Size = "Small";

	int iRand = 1000 * rand(15);

	Stores[STORE_HOUSE].max_weight = 60000 + iRand;

	iRand = 1000 * rand(15);
	Stores[STORE_HOUSE].max_resize_weight = sti(Stores[STORE_HOUSE].max_weight) + 35000 + iRand;

	string sGood = "";

	for(int g=0; g < GOODS_QUANTITY; g++)
	{
		sGood = Goods[g].Name;
		Stores[STORE_HOUSE].goods.(sGood).quantity = 0;
	}
}

//-------------------------------------------------------------------------------
// Заселяем все постройки
//-------------------------------------------------------------------------------
void CreateCaimanCitizens(aref loc)
{
	if(!CheckAttribute(loc, "id"))
	{
	 	return;
	}

	if(loc.id != "Caiman_town")
	{
		return;
	}

	if(PChar.ColonyBuilding.Defence.Battle == true)
	{
		DeleteAllFantomCharactersFromLocation(loc);
		return;
	}

	if(PChar.ColonyBuilding.Defence.DeadInTown == true)
	{
		SetDeadmansToLocation(loc, "citizens");
		PChar.ColonyBuilding.Defence.DeadInTown = false;

		if(CheckAttribute(loc, "hidden_effects"))
		{
			DeleteAttribute(loc, "hidden_effects");
		}
		if(CheckAttribute(&Locations[FindLocation("Caiman_ExitTown")], "hidden_effects"))
		{
			DeleteAttribute(&Locations[FindLocation("Caiman_ExitTown")], "hidden_effects");
		}
		return;
	}

	if(isLocationHasCitizens(loc.id))
	{
		return;
	}

	int iCitizensQuantity, iModel;
	ref chr;
	int iChar, i, iSex;
	string slai_group, locatorName, sType;

	int iNation = PIRATE;
    	slai_group = GetNationNameByType(iNation)  + "_citizens";
	int iCitizen, iSoldier, iPatrol, iMusketoor, iSoldiers, iGenres, iMechant, iCitizens;
	iSoldiers = sti(PChar.ColonyBuilding.Soldiers);

	iSoldier = (iSoldiers / 2) / 10;
	iPatrol = (iSoldiers / 5) / 10;
	iMusketoor = (iSoldiers / 10) / 10;

	if(iSoldiers <= 0)
	{
		iSoldier = 0;
		iPatrol = 0
		iMusketoor = 0;
	}

	iCitizens = sti(PChar.ColonyBuilding.Population);
	iCitizen = (iCitizens / 2) / 10;
	iGenres = (iCitizens / 10) / 10;
	iMechant = (iCitizens / 10) / 10;


	if(iCitizens <= 0)
	{
		iCitizen = 0;
		iGenres = 0;
		iMechant = 0;
	}

	if(iCitizen > 20) { iCitizen = 20; }

    	arrayNPCModelHow = 0;

    	int iSoldiersNation = sti(PChar.ColonyBuilding.ColonyNation);
    	string sSoldiersType = PChar.ColonyBuilding.SoldiersType;

    	string sSoldierType = "";
	switch(sSoldiersType)
	{
		case "officer": sSoldierType = "pofficer"; break;
		case "pirate": sSoldierType = "pirate"; break;
		case "nation": sSoldierType = "soldier"; break;
	}

	if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.soldiers"))
	{
		aref solderLoc;
		makearef(st, loc.locators.soldiers);
		//iCitizensQuantity = GetAttributesNum(st);

		if(iSoldier > GetAttributesNum(st))
		{
			iSoldier = GetAttributesNum(st);
		}

		for (i=0; i<iSoldier; i++)
		{
			if(sSoldiersType == "nation")
			{
				iChar = NPC_GeneratePhantomCharacter(sSoldierType, iSoldiersNation, MAN, 0);
			}
			else
			{
				iChar = NPC_GeneratePhantomCharacter(sSoldierType, PIRATE, MAN, 0);
			}

			chr = &characters[iChar];
			SetNPCModelUniq(chr, sSoldierType, MAN);
			chr.City = "Caiman";
            		chr.CityType = "soldier";
			chr.RebirthPhantom = true;
			chr.nation = PIRATE;
			LAi_CharacterReincarnation(chr, true, true);
			LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2);
            		SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true);
			LAi_SetLoginTime(chr, 6.0, 23.0);

			solderLoc = GetAttributeN(st, i);
			locatorName = GetAttributeName(solderLoc);
			ChangeCharacterAddressGroup(chr, pchar.location, "soldiers", locatorName);

			if (findsubstr(locatorName, "protector" , 0) != -1 && iNation != PIRATE)
			{
				chr.protector = true;
			}

			LAi_SetGuardianType(chr);

			LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
			chr.greeting = "Gr_questOfficer";

			chr.dialog.filename = "Common_Soldier.c";
			chr.dialog.currentnode = "first time";
			SetFoodToCharacter(chr, 3, 20);
		}
	}

	if(checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.patrol"))
	{
		makearef(st, loc.locators.patrol);
		if(iPatrol > 7)
		{
			iPatrol = 7;
		}

		if(iPatrol > GetAttributesNum(st) - 3)
		{
			iPatrol = GetAttributesNum(st) - 3;
		}

		for (i=0; i<iPatrol-3; i++)
		{
			if(sSoldiersType == "nation")
			{
				iChar = NPC_GeneratePhantomCharacter(sSoldierType, iSoldiersNation, MAN, 0);
			}
			else
			{
				iChar = NPC_GeneratePhantomCharacter(sSoldierType, PIRATE, MAN, 0);
			}

			chr = &characters[iChar];
			SetNPCModelUniq(chr, sSoldierType, MAN);
			chr.nation = PIRATE;
			chr.City = "Caiman";
            chr.CityType = "soldier";
            SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true);
			chr.RebirthPhantom = true;
			LAi_CharacterReincarnation(chr, true, true);
			LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2);
			LAi_SetLoginTime(chr, 0.0, 24.0);
			LAi_SetPatrolType(chr);

			LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
			chr.greeting = "Gr_questOfficer";
			PlaceCharacter(chr, "patrol", "random_free");

			chr.dialog.filename = "Common_Soldier.c";
			chr.dialog.currentnode = "first time";
		}

		if(iMusketoor > 3)
		{
			iMusketoor = 3;
		}

		for (i=1; i<=iMusketoor; i++)
		{
			if(sSoldiersType != "nation")
			{
                sType = "mushketer_" + (rand(4)+1);
			}
			else
			{
                sType = NationShortName(iSoldiersNation) + "_mush_" + i;
			}

			chr = GetCharacter(NPC_GenerateCharacter("GenChar_", sType, "man", "mushketer", sti(pchar.rank), PIRATE, 0, false));
			chr.id = "GenChar_" + chr.index;
			chr.reputation = (1 + rand(44) + rand(44));
			chr.City = "Caiman";
            chr.CityType = "soldier";
			chr.greeting = "soldier_common";
			chr.nation = PIRATE;
			chr.RebirthPhantom = true;
			LAi_CharacterReincarnation(chr, true, true);
			LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2);
            SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true);
			LAi_SetLoginTime(chr, 6.0, 23.0);

			PlaceCharacter(chr, "patrol", "random_free");

			LAi_SetPatrolType(chr);

			LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
			chr.greeting = "Gr_questOfficer";

			chr.dialog.filename = "Common_Soldier.c";
			chr.dialog.currentnode = "first time";
			SetFoodToCharacter(chr, 3, 20);
		}
	}

	for(i=0; i<iCitizen; i++)
	{
		iSex = rand(3);
		if(iSex > 1) iSex = 1;

		iChar = NPC_GeneratePhantomCharacter("citizen", iNation, iSex, 0);

		chr = &characters[iChar];
		sType = "citizen";
		SetNPCModelUniq(chr, sType, iSex);

		chr.City = "Caiman";
		chr.CityType = "citizen";

		LAi_SetLoginTime(chr, 6.0, 21.99);
		LAi_SetCitizenType(chr);
		LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);

		PlaceCharacter(chr, "goto", "random_free");
		chr.dialog.filename    = "Common_citizen.c";
		chr.dialog.currentnode = "First time";
		if(chr.sex == "man")
		{
			if(rand(1) == 1)
			{
				chr.greeting = "cit_common1";
			}
			else
			{
				chr.greeting = "cit_common";
			}
		}
		else
		{
			chr.greeting = "Gr_Woman_Citizen";
		}
	}

	aref st;
	if (checkAttribute(loc, "locators.merchant"))
	{
		makearef(st, loc.locators.merchant);

		if(iMechant > GetAttributesNum(st))
		{
			iMechant = GetAttributesNum(st);
		}

		for (i=0; i<iMechant; i++)
		{
			iSex = rand(1);
			iChar = NPC_GeneratePhantomCharacter("citizen", iNation, iSex, 0);

			chr = &characters[iChar];
			SetNPCModelUniq(chr, "citizen", iSex);

			chr.City = "Caiman";
			chr.CityType = "citizen";
			LAi_SetLoginTime(chr, 7.0, 20.0);

			ChangeCharacterAddressGroup(chr, loc.id, "merchant", "merchant"+(i+1));
			LAi_SetMerchantType(chr);
			chr.dialog.filename = "Common_ItemTrader.c";
			chr.dialog.currentnode = "first time";
			//-->
			if (chr.sex == "man") { chr.greeting = "tra_common"; } else { chr.greeting = "tra_woman_common"; }
			//<--
			LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
		}
	}

	if(CheckAttribute(loc, "carrier") && IsLoginTime())
	{
		int iTemp;
		int iQtyCarrier = rand(2) + 2;
		string locReload[7];
		locReload[0] = "reload4_back";
		locReload[1] = "reload5_back";
		locReload[2] = "reload6_back";
		locReload[3] = "reload7_back";
		locReload[4] = "reload8_back";
		locReload[5] = "reload10_back";
		locReload[6] = "reload9_back";
		string CarrierName[10];
		CarrierName[0] = "GenresBag1";
		CarrierName[1] = "GenresBag2";
		CarrierName[2] = "GenresBarrel1";
		CarrierName[3] = "GenresBarrel2";
		CarrierName[4] = "GenresBarrelTop1";
		CarrierName[5] = "GenresBarrelTop2";
		CarrierName[6] = "GenresBottle1";
		CarrierName[7] = "GenresBottle2";
		CarrierName[8] = "GenresChest1";
		CarrierName[9] = "GenresChest2";

		if(iGenres > 9)
		{
			iGenres = 9;
		}

		for (i=iGenres; i>0; i--)
		{
			iSex = 1;
			while (iSex == 1)
			{
				iTemp = rand(9);
				if (CarrierName[iTemp] != "") iSex = 0;
			}
			chr = GetCharacter(NPC_GenerateCharacter("Carrier", CarrierName[iTemp], "man", "genres", 35, PIRATE, 0, false));
			chr.id = chr.id + "_" + chr.index;
			aref aLocator;
			makearef(aLocator, loc.locators.reload);
			CarrierName[iTemp] = "";
			LAi_SetImmortal(chr, true);
			LAi_SetLoginTime(chr, 7.0, 20.0);
			iSex = 1;
			while (iSex == 1)
			{
				iTemp = rand(6);
				if (CheckAttribute(aLocator, locReload[iTemp]) && locReload[iTemp] != "")
				{
					chr.firstLoc = locReload[iTemp];
					chr.firstLoc.timer = frand(7) + 4.0;
					locReload[iTemp] = "";
					iSex = 0;
				}
			}
			ChangeCharacterAddressGroup(chr, loc.id, "reload", "gate");
			LAi_SetCarrierType(chr);
			LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
		}
	}
}

void CreateCaimanGuardingBase(aref loc)
{
	if(PChar.ColonyBuilding.SlavesInShore.CurShore == "LandGuardingPort")
	{
		return;
	}

	if(!CheckAttribute(loc, "id") || !CheckAttribute(loc, "type"))
	{
		return;
	}

	if(loc.id != "LandGuardingFort" && loc.id != "LandGuardingPort")
	{
		return;
	}

	int iSoldiers = sti(PChar.ColonyBuilding.Soldiers);

	if(iSoldiers <= 0)
	{
		return;
	}

	if(isLocationHasCitizens(loc.id))
	{
		return;
	}

	int iSoldier = (iSoldiers / 2) / 10;
	int iPatrol = (iSoldiers / 5) / 10;

	if(loc.id == "LandGuardingFort")
	{
		if(iSoldier > 15) iSoldier = 15;
	}
	else
	{
		if(iSoldier > 10) iSoldier = 10;
	}

	if(iPatrol > 10) iPatrol = 10;

	int iNation = PIRATE;

	ref chr;
	int iChar, i;
	string sType;
	arrayNPCModelHow = 0;

    	int iSoldiersNation = sti(PChar.ColonyBuilding.ColonyNation);
    	string sSoldiersType = PChar.ColonyBuilding.SoldiersType;

	switch(sSoldiersType)
	{
		case "officer": sType = "pofficer"; break;
		case "pirate": sType = "pirate"; break;
		case "nation": sType = "soldier"; break;
	}

	for (i=0; i<iSoldier; i++)
	{
		if(sSoldiersType == "nation")
		{
			iChar = NPC_GeneratePhantomCharacter(sType, iSoldiersNation, MAN, 0);
		}
		else
		{
			iChar = NPC_GeneratePhantomCharacter(sType, PIRATE, MAN, 0);
		}

		chr = &characters[iChar];
		SetNPCModelUniq(chr, sType, MAN);
		chr.City = "Caiman";
		chr.CityType = "soldier";
		chr.nation = PIRATE;
		chr.RebirthPhantom = true;
		LAi_CharacterReincarnation(chr, true, true);
		LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2);
		SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true);
		LAi_SetLoginTime(chr, 0.0, 24.0);
		LAi_SetGuardianType(chr);
		LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
		chr.dialog.filename = "Common_Fort.c";
		chr.dialog.currentnode = "First time";
		chr.greeting = "Gr_questOfficer";
		SetFoodToCharacter(chr, 3, 20);
		PlaceCharacter(chr, "goto", "random_free");
	}

	for (i=0; i<iPatrol; i++)
	{
		if(sSoldiersType == "nation")
		{
			iChar = NPC_GeneratePhantomCharacter(sType, iSoldiersNation, MAN, 0);
		}
		else
		{
			iChar = NPC_GeneratePhantomCharacter(sType, PIRATE, MAN, 0);
		}

		chr = &characters[iChar];
		SetNPCModelUniq(chr, sType, MAN);
		chr.City = "Caiman";
		chr.CityType = "fortPatrol";
		chr.nation = PIRATE;
		LAi_SetPatrolType(chr);
		LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
		chr.greeting = "Gr_questOfficer";
		chr.dialog.filename = "Common_Fort.c";
		chr.dialog.currentnode = "First time";
		PlaceCharacter(chr, "goto", "random_free");
	}
}

void CreateCaimanMinesCitizens(aref loc)
{
	if(!CheckAttribute(loc, "id") || !CheckAttribute(loc, "type"))
	{
		return;
	}

	if(loc.id != "Caiman_Mines")
	{
		return;
	}

	if(PChar.Mines.Defence.Battle == true)
	{
		DeleteAllFantomCharactersFromLocation(loc);
		return;
	}

	if(PChar.Mines.Defence.DeadInTown == true)
	{
		SetDeadmansToLocation(loc, "pirate");
		PChar.Mines.Defence.DeadInTown = false;
		return;
	}

	bool bBuildingGoldMine = PChar.ColonyBuilding.GoldMine.Resize.BuildingTime;
	bool bBuildingSilverMine = PChar.ColonyBuilding.SilverMine.Resize.BuildingTime;
	bool bBuildingIronMine = PChar.ColonyBuilding.IronMine.Resize.BuildingTime;

	if(bBuildingGoldMine && bBuildingSilverMine && bBuildingIronMine)
	{
		DeleteAllFantomCharactersFromLocation(loc);
		return;
	}

	if(isLocationHasCitizens(loc.id))
	{
		return;
	}

	int iSoldiers = sti(PChar.Mines.GuardiansQuantity);
	int iSlaves = sti(PChar.Mines.SlavesQuantity);

	int iPoorSlaves = iSlaves / 15;
	if(iPoorSlaves > 15) iPoorSlaves = 15;
	if(iPoorSlaves < 0) iPoorSlaves = 0;

	int iStaySlaves = iSlaves / 10;
	if(iStaySlaves > 15) iStaySlaves = 15;
	if(iStaySlaves < 0) iStaySlaves = 0;

	int iPatrol = iSoldiers / 10;
	if(iPatrol > 25) iPatrol = 25;
	if(iPatrol < 0) iPatrol = 0;

	int iNation = PIRATE;
	int iMassive;
	string model[23];

	ref chr;
	int iChar, i;
	string sType;
	arrayNPCModelHow = 0;

    	int iSoldiersNation = sti(PChar.ColonyBuilding.ColonyNation);
    	string sSoldiersType = PChar.ColonyBuilding.SoldiersType;

	switch(sSoldiersType)
	{
		case "officer": sType = "pofficer"; break;
		case "pirate": sType = "pirate"; break;
		case "nation": sType = "soldier"; break;
	}

	if(iPatrol > 0)
	{
		for (i=0; i<=iPatrol; i++)
		{
			if(sSoldiersType == "nation")
			{
				iChar = NPC_GeneratePhantomCharacter(sType, iSoldiersNation, MAN, 0);
			}
			else
			{
				iChar = NPC_GeneratePhantomCharacter(sType, PIRATE, MAN, 0);
			}

			chr = &characters[iChar];
			SetNPCModelUniq(chr, sType, MAN);

			chr.City = "Caiman";
			chr.CityType = "soldier";
			chr.nation = PIRATE;
			SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true);
			chr.RebirthPhantom = true;
			LAi_CharacterReincarnation(chr, true, true);
			LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2);
			LAi_SetLoginTime(chr, 0.0, 24.0);
			PlaceCharacter(chr, "goto", "random_free");
			LAi_SetPatrolType(chr);
			LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
			chr.greeting = "Gr_questOfficer";
			chr.dialog.filename = "Common_Soldier.c";
			chr.dialog.currentnode = "first time";
		}
	}

	model[0] = "prizon_1";
    model[1] = "prizon_2";
    model[2] = "prizon_3";
    model[3] = "prizon_4";
    model[4] = "prizon_5";
    model[5] = "prizon_6";
    model[6] = "prizon_7";
	model[7] = "prizon_8";
    model[8] = "pirate_1";
    model[9] = "prison_5";
    model[10] = "pirate_1";
    model[11] = "pirate_11";
    model[12] = "pirate_12";
    model[13] = "pirate_13";
    model[14] = "pirate_14";
    model[15] = "pirate_15";
    model[16] = "pirate_16";
    model[17] = "pirate_21";
    model[18] = "pirate_25";
    model[19] = "PKM_rab_1";
    model[20] = "PKM_rab_2";
    model[21] = "PKM_rab_3";
    model[22] = "PKM_rab_4";
	string sAni;

	if(iPoorSlaves > 0)
	{

		for(int s=1; s <= iPoorSlaves; s++)
		{
	    	iMassive = rand(22);

        	sAni = "man";
        	/* if(model[iMassive] == "pirate_1" || model[iMassive] == "pirate_11" || model[iMassive] == "pirate_12" || model[iMassive] == "pirate_13" || model[iMassive] == "pirate_14" || model[iMassive] == "pirate_15" || model[iMassive] == "pirate_16" || model[iMassive] == "pirate_21" || model[iMassive] == "pirate_25") sAni = "man"; */

			chr = GetCharacter(NPC_GenerateCharacter("Caiman_Mines_Poor_Slave_" + s, model[iMassive], "man", sAni, 7, PIRATE, 0, false));
			chr.dialog.filename = "Quest\CapBloodLine\questNPC.c";
			chr.greeting = "Gr_slave";
			chr.CityType = "citizen";
			chr.city = "Caiman";
			chr.PoorSit = true;
			LAi_SetLoginTime(chr, 6.0, 22.99);

			PlaceCharacter(chr, "slaves_poor", "random_free");
			LAi_SetGroundSitType(chr);
			LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
		}
	}

	if(iStaySlaves > 0)
	{
		for(int n=1; n <= iStaySlaves; n++)
		{
			iMassive = rand(22);

	        sAni = "man";
	        /* if(model[iMassive] == "pirate_1" || model[iMassive] == "pirate_11" || model[iMassive] == "pirate_12" || model[iMassive] == "pirate_13" || model[iMassive] == "pirate_14" || model[iMassive] == "pirate_15" || model[iMassive] == "pirate_16" || model[iMassive] == "pirate_21" || model[iMassive] == "pirate_25") sAni = "man"; */

			chr = GetCharacter(NPC_GenerateCharacter("Caiman_Mines_Stay_Slave_" + n, model[iMassive], "man", sAni, 7, PIRATE, 0, false));
			chr.dialog.filename = "Quest\CapBloodLine\questNPC.c";
			chr.greeting = "Gr_slave";
			chr.CityType = "citizen";
			chr.city = "Caiman";
			LAi_SetLoginTime(chr, 6.0, 22.99);

			PlaceCharacter(chr, "goto", "random_free");
			LAi_SetCitizenType(chr);
			LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
		}
	}
}


void CreateCaimanPlantationCitizens(aref loc)
{
	if(!CheckAttribute(loc, "id") || !CheckAttribute(loc, "type"))
	{
		return;
	}

	if(loc.id != "Caiman_Plantation")
	{
		return;
	}

	if(PChar.Plantation.Defence.Battle == true || PChar.ColonyBuilding.Defence.Battle == true)
	{
		DeleteAllFantomCharactersFromLocation(loc);
		return;
	}

	if(PChar.Plantation.Defence.DeadInTown == true)
	{
		SetDeadmansToLocation(loc, "pirate");
		PChar.Plantation.Defence.DeadInTown = false;
		return;
	}

	if(PChar.Plantation.Size.Resize.BuildingTime == true)
	{
		DeleteAllFantomCharactersFromLocation(loc);
		return;
	}

	if(isLocationHasCitizens(loc.id))
	{
		return;
	}

	int iSoldiers = sti(PChar.Plantation.Guardians.Quantity);
	int iSlaves = sti(PChar.Plantation.Slaves.Quantity);

	int iStaySlaves = iSlaves / 10;
	if(iStaySlaves > 20) iStaySlaves = 20;
	if(iStaySlaves < 0) iStaySlaves = 0;

	int iPatrol = iSoldiers / 10;
	if(iPatrol > 20) iPatrol = 20;
	if(iPatrol < 0) iPatrol = 0;

	int iNation = sti(PChar.ColonyBuilding.ColonyNation);
	int iMassive;
	string model[23];

	ref chr;
	int iChar, i;
	string sType;
	arrayNPCModelHow = 0;

	SaveCurrentNpcQuestDateParam(loc, "Caiman_Plantation_date");

    	int iSoldiersNation = sti(PChar.ColonyBuilding.ColonyNation);
    	string sSoldiersType = PChar.ColonyBuilding.SoldiersType;

	switch(sSoldiersType)
	{
		case "officer": sType = "pofficer"; break;
		case "pirate": sType = "pirate"; break;
		case "nation": sType = "soldier"; break;
	}

	if(iPatrol > 0)
	{
		for(i=0; i<=iPatrol; i++)
		{
			if(sSoldiersType == "nation")
			{
				iChar = NPC_GeneratePhantomCharacter(sType, iSoldiersNation, MAN, 0);
			}
			else
			{
				iChar = NPC_GeneratePhantomCharacter(sType, PIRATE, MAN, 0);
			}

			chr = &characters[iChar];
			SetNPCModelUniq(chr, sType, MAN);

			chr.City = "Caiman";
			chr.CityType = "soldier";
			chr.nation = PIRATE;
			SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true);
			chr.RebirthPhantom = true;
			LAi_CharacterReincarnation(chr, true, true);
			LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2);
			LAi_SetLoginTime(chr, 0.0, 24.0);
			PlaceCharacter(chr, "goto", "random_free");
			LAi_SetPatrolType(chr);
			LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
			chr.greeting = "Gr_questOfficer";
			chr.dialog.filename = "Common_Soldier.c";
			chr.dialog.currentnode = "first time";
		}
	}

	model[0] = "prizon_1";
    model[1] = "prizon_2";
    model[2] = "prizon_3";
    model[3] = "prizon_4";
    model[4] = "prizon_5";
    model[5] = "prizon_6";
    model[6] = "prizon_7";
	model[7] = "prizon_8";
    model[8] = "pirate_1";
    model[9] = "prison_5";
    model[10] = "pirate_1";
    model[11] = "pirate_11";
    model[12] = "pirate_12";
    model[13] = "pirate_13";
    model[14] = "pirate_14";
    model[15] = "pirate_15";
    model[16] = "pirate_16";
    model[17] = "pirate_21";
    model[18] = "pirate_25";
    model[19] = "PKM_rab_1";
    model[20] = "PKM_rab_2";
    model[21] = "PKM_rab_3";
    model[22] = "PKM_rab_4";

	if(iStaySlaves > 0)
	{
		for(int n=1; n <= iStaySlaves; n++)
		{
	        iMassive = rand(22);

	        string sAni = "man";
	        /* if(model[iMassive] == "pirate_1" || model[iMassive] == "pirate_11" || model[iMassive] == "pirate_12" || model[iMassive] == "pirate_13" || model[iMassive] == "pirate_14" || model[iMassive] == "pirate_15" || model[iMassive] == "pirate_16" || model[iMassive] == "pirate_21" || model[iMassive] == "pirate_25") sAni = "man"; */

			chr = GetCharacter(NPC_GenerateCharacter("Caiman_Plantation_Stay_Slave_" + n, model[iMassive], "man", sAni, 7, PIRATE, 0, false));
			chr.dialog.filename = "Quest\CapBloodLine\questNPC.c";
			chr.greeting = "Gr_slave";
			chr.CityType = "citizen";
			chr.city = "Caiman";
			LAi_SetLoginTime(chr, 6.0, 22.99);

			PlaceCharacter(chr, "patrol", "random_free");
			LAi_SetCitizenType(chr);
			LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
		}
	}
}

//-------------------------------------------------------------------------------
// Стройка - куча перенаправлений
//-------------------------------------------------------------------------------
void CreateSmallColonyCaiman()
{
	ref PChar = GetMainCharacter();
	PChar.ColonyBuilding.Stage = "1";
	LAi_QuestDelay("LiveOfTheColonyUptade_1", 0.5);
	LAi_QuestDelay("CheckDefenceColonyUptade_1", 0.5);

	PChar.ColonyBuilding.Food.MaxQuantity = 5000;
	PChar.ColonyBuilding.Medicament.MaxQuantity = 2500;

	Locations[FindLocation("Caiman_town")].reload.l2.disable = true;
	Locations[FindLocation("Caiman_town")].reload.l4.disable = true;
	Locations[FindLocation("Caiman_town")].reload.l5.disable = true;
	Locations[FindLocation("Caiman_town")].reload.l6.disable = true;
	Locations[FindLocation("Caiman_town")].reload.l7.disable = true;
	Locations[FindLocation("Caiman_town")].reload.l8.disable = true;
	Locations[FindLocation("Caiman_town")].reload.l10.disable = true;
	Locations[FindLocation("Caiman_town")].reload.l11.disable = true;

	Locations[FindLocation("Shore17")].type = "port";
	Locations[FindLocation("Shore17")].fastreload = "Caiman";
	Locations[FindLocation("Shore17")].reload.l1.go = "Caiman_ExitTown";
	Locations[FindLocation("Shore17")].reload.l1.label = "ExitTown";
	Locations[FindLocation("Shore17")].reload.l1.emerge = "reload2";
	Locations[FindLocation("Shore17")].reload.l1.autoreload = "1";

	Locations[FindLocation("Caiman_Jungle_01")].reload.l1.name = "reload1_back";
	Locations[FindLocation("Caiman_Jungle_01")].reload.l1.go = "Caiman_ExitTown";
	Locations[FindLocation("Caiman_Jungle_01")].reload.l1.emerge = "reload1";
	Locations[FindLocation("Caiman_Jungle_01")].reload.l1.autoreload = "1";
	Locations[FindLocation("Caiman_Jungle_01")].reload.l1.label = "ExitTown";

	Islands[FindIsland("Caiman")].reload.l1.label = "Caiman Port";
	Islands[FindIsland("Caiman")].colonyquantity = 1;
	Islands[FindIsland("Caiman")].reload.l1.istown = true;

	//int iNation = sti(PChar.ColonyBuilding.ColonyNation);

	int iColony = FindColony("Caiman");
	ref rColony = &Colonies[iColony];
	rColony.StoreNum   = Caiman_STORE;
	rColony.smuggling_nation = PIRATE;
	rColony.nation = PIRATE;
	rColony.island = "Caiman";
	rColony.num = 1;
	rColony.HeroOwn = true;
	rColony.isBought = true;
	rColony.DontSetShipInPort = true;

	RenamedColonyCaiman();

	AddSimpleRumourToAllNations(LinkRandPhrase("Поговаривают", "Говорят", "Ходят слухи") + ", что капитан " + GetNameLugger(PChar, "f") + " построил" + GetSexPhrase("","а") + " свою колонию на острове Кайман.", 5, 1);
}

void CreateModificyColonyCaiman()
{
	ref PChar = GetMainCharacter();
	PChar.ColonyBuilding.Stage = "2";
	PChar.ColonyBuilding.Population.Max = sti(PChar.ColonyBuilding.Population.Max) * 2 + rand(25);
	PChar.ColonyBuilding.Population.Optimal = (sti(PChar.ColonyBuilding.Population.Max) - (75 + rand(15))) - rand(25);
	PChar.ColonyBuilding.Soldiers.MaxQuantity = 2000;

	PChar.ColonyBuilding.Food.MaxQuantity = 10000;
	//PChar.ColonyBuilding.Medicament.MaxQuantity = 5000;

	// МАГАЗИН
	Characters[GetCharacterIndex("Caiman_trader")].from_sea = "Caiman_town";

	ref rStore = &Locations[FindLocation("Caiman_store")];
	DeleteAttribute(rStore, "models");

	//rStore.fastreload = "Caiman";
	//rStore.townsack = "Caiman";

	int iStore = sti(PChar.ColonyBuilding.Architecture.Store);
	string sStore = "Store0" + iStore;

	rStore.filespath.models = "locations\inside\" + sStore + "\";
	rStore.models.always.locators = sStore + "_locators";
	rStore.models.always.store = sStore;
	rStore.models.always.store.level = 65538;
	rStore.models.always.window = sStore + "_window";
	rStore.models.always.window.tech = "LocationWindows";
	rStore.models.always.window.level = 65539;
	rStore.models.always.back = "..\inside_back";
	rStore.models.always.back.level = 65529;
	rStore.models.day.charactersPatch = sStore + "_patch";
	rStore.models.night.charactersPatch = sStore + "_patch";
	rStore.locators_radius.camdetector.camera1 = 5;

	DeleteAttribute(rStore, "reload");
	rStore.reload.l1.name = "reload1_back";
	rStore.reload.l1.go = "Caiman_town";
	rStore.reload.l1.emerge = "reload6";
	rStore.reload.l1.autoreload = "0";
	rStore.reload.l1.label = "Street";

	// ВЕРФЬ
	int iShipyard = sti(PChar.ColonyBuilding.Architecture.Shipyard);
	string sShipyard = "shipyard0" + iShipyard;

	ref rShipyard = &Locations[FindLocation("Caiman_shipyard")];
	DeleteAttribute(rShipyard, "models");

	//rShipyard.fastreload = "Caiman";
	//rShipyard.townsack = "Caiman";

	rShipyard.filespath.models = "locations\inside\" + sShipyard + "\";
	rShipyard.models.always.locators = sShipyard + "_locators";
	rShipyard.models.always.shipyard = sShipyard;
	rShipyard.models.always.shipyard.level = 65538;
	rShipyard.models.always.window = sShipyard + "_window";
	rShipyard.models.always.window.tech = "LocationWindows";
	rShipyard.models.always.window.level = 65539;
	rShipyard.models.always.back = "..\inside_back";
	rShipyard.models.always.back.level = 65529;
	rShipyard.models.day.charactersPatch = sShipyard + "_patch";
	rShipyard.models.night.charactersPatch = sShipyard + "_patch";

	// ТАВЕРНА
	int iTavern = sti(PChar.ColonyBuilding.Architecture.Tavern);
	string sTavern = "tavern0" + iTavern;

	ref rTavern = &Locations[FindLocation("Caiman_tavern")];
	DeleteAttribute(rTavern, "models");

	//rTavern.fastreload = "Caiman";
	//rTavern.townsack = "Caiman";

	rTavern.filespath.models = "locations\inside\" + sTavern + "\";
	rTavern.models.always.tavern = sTavern;
	rTavern.models.always.tavern.level = 65538;
	rTavern.models.always.locators = sTavern + "_locators";

	if(iTavern == 1)
	{
		rTavern.models.always.window = "tavern01_windows";
	}

	rTavern.models.always.window.tech = "LocationWindows";
	rTavern.models.always.window.level = 65539;
	rTavern.models.always.back = "..\inside_back";
	rTavern.models.always.back.level = 65529;
	rTavern.models.day.charactersPatch = sTavern + "_patch";
	rTavern.models.night.charactersPatch = sTavern + "_patch";

	DeleteAttribute(rTavern, "reload");
	rTavern.reload.l1.name = "reload1_back";
	rTavern.reload.l1.go = "Caiman_town";
	rTavern.reload.l1.emerge = "reload4";
	rTavern.reload.l1.autoreload = "0";
	rTavern.reload.l1.label = "Street";

	rTavern.reload.l2.name = "reload2_back";
	rTavern.reload.l2.go = "Caiman_tavern_upstairs";
	rTavern.reload.l2.emerge = "reload1";
	rTavern.reload.l2.autoreload = "0";
	rTavern.reload.l2.label = "Tavern upstairs";
	rTavern.reload.l2.disable = 1;
	// ДОМ РОСТОВЩИКА
	int iBank = sti(PChar.ColonyBuilding.Architecture.Bank);
	string sBank = "Bank0" + iBank;

	ref rBank = &Locations[FindLocation("Caiman_Bank")];
	DeleteAttribute(rBank, "models");

	//rBank.fastreload = "Caiman";
	//rBank.townsack = "Caiman";

	rBank.filespath.models = "locations\inside\" + sBank + "\";
	rBank.models.always.locators = sBank + "_locators";
	rBank.models.always.store = sBank;
	rBank.models.always.store.level = 65538;
	rBank.models.always.window = sBank + "_windows";
	rBank.models.always.window.tech = "LocationWindows";
	rBank.models.always.window.level = 65539;
	rBank.models.always.back = "..\inside_back";
	rBank.models.always.back.level = 65529;
	rBank.models.day.charactersPatch = sBank + "_patch";
	rBank.models.night.charactersPatch = sBank + "_patch";

	// РЕЗИДЕНЦИЯ
	int iTownhall = sti(PChar.ColonyBuilding.Architecture.Townhall);
	string sTownhall = "Residence0" + iTownhall;

	ref rResidence = &Locations[FindLocation("Caiman_townhall")];
	DeleteAttribute(rResidence, "models");

	//rResidence.fastreload = "Caiman";
	//rResidence.townsack = "Caiman";

	rResidence.image = "loading\jonny_load\inside\residence03.tga";
	rResidence.filespath.models = "locations\inside\" + sTownhall;
	rResidence.models.always.locators = sTownhall + "_locators";
	rResidence.models.always.l1 = sTownhall;
	rResidence.models.always.l1.level = 65538;
	rResidence.models.always.window = sTownhall + "_window";
	rResidence.models.always.window.tech = "LocationWindows";
	rResidence.models.always.window.level = 65539;
	rResidence.models.always.back = "..\inside_back";
	rResidence.models.always.back.level = 65529;
	rResidence.models.day.charactersPatch = sTownhall + "_patch";
	rResidence.models.night.charactersPatch = sTownhall + "_patch";

	DeleteAttribute(rResidence, "reload");
	rResidence.reload.l1.name = "reload1_back";
	rResidence.reload.l1.go = "Caiman_town";
	rResidence.reload.l1.emerge = "reload3";
	rResidence.reload.l1.autoreload = "0";
	rResidence.reload.l1.label = "Street";

	// СКЛАД

	ref rStoreHouse = &Locations[FindLocation("Caiman_StoreHouse")];
	DeleteAttribute(rStoreHouse, "rStoreHouse");

	string sShoreHouseEmerge = "houseS1";
	int iTown = sti(PChar.ColonyBuilding.Architecture.Town);
	switch(iTown)
	{
		case 1: sShoreHouseEmerge = "houseS1"; break;
		case 2: sShoreHouseEmerge = "houseS6"; break;
		case 3: sShoreHouseEmerge = "houseS2"; break;
	}

	rStoreHouse.reload.l1.name = "reload1";
	rStoreHouse.reload.l1.go = "Caiman_town";
	rStoreHouse.reload.l1.emerge = sShoreHouseEmerge;
	rStoreHouse.reload.l1.autoreload = "0";
	rStoreHouse.reload.l1.label = "Street";

	// ГОРОД
	CreateTownCaiman();

	// ВЫХОД ИЗ ГОРОДА
	ref rExitTown = &Locations[FindLocation("Caiman_ExitTown")];
	DeleteAttribute(rExitTown, "models");

	rExitTown.type = "jungle";
	rExitTown.islandId = "Caiman";
	rExitTown.islandIdAreal = "Caiman";

	rExitTown.filespath.models = "locations\Outside\Jungles\TownExitY";
	rExitTown.models.always.townExit = "townExitY";
	rExitTown.models.always.townWalls = "townExitY_stucco";
	rExitTown.models.always.locators = "townExitY_locators";
	rExitTown.models.always.grassPatch = "townExitY_grass";
	rExitTown.models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	rExitTown.models.always.l1 = "plan1";
	rExitTown.models.always.l1.level = 9;
	rExitTown.models.always.l1.tech = "DLightModel";
	rExitTown.models.always.l2 = "plan2";
	rExitTown.models.always.l2.level = 8;
	rExitTown.models.always.l2.tech = "DLightModel";
	rExitTown.models.always.l3 = "plan3";
	rExitTown.models.always.l3.level = 7;
	rExitTown.models.always.l3.tech = "DLightModel";
	rExitTown.models.day.charactersPatch = "townExitY_patch";
	rExitTown.models.day.fonars = "townExitY_fd";
	rExitTown.models.night.charactersPatch = "townExitY_patch";
	rExitTown.models.night.fonars = "townExitY_fn";

	rExitTown.environment.weather = "true";
	rExitTown.environment.sea = "false";

	rExitTown.reload.l1.name = "reload3";
	rExitTown.reload.l1.go = "Caiman_town";
	rExitTown.reload.l1.emerge = "gate_back";
	rExitTown.reload.l1.autoreload = "0";
	rExitTown.reload.l1.label = "Caiman";

	rExitTown.reload.l2.name = "reload1_back";
	rExitTown.reload.l2.go = "Caiman_CaveEntrance";
	rExitTown.reload.l2.emerge = "reload2";
	rExitTown.reload.l2.autoreload = "1";
	rExitTown.reload.l2.label = "Jungle";
	rExitTown.locators_radius.reload.reload1_back = 2.0;

	rExitTown.reload.l3.name = "reload2_back";
	rExitTown.reload.l3.go = "Shore16";
	rExitTown.reload.l3.emerge = "reload1";
	rExitTown.reload.l3.autoreload = "1";
	rExitTown.reload.l3.label = "Shore16";
	rExitTown.locators_radius.reload.reload2_back = 2.0;
	rExitTown.locators_radius.quest.detector1 = 2.0;

	Islands[FindIsland("Caiman")].reload.l1.label = "Caiman Port";
	Islands[FindIsland("Caiman")].reload.l1.name = "reload_2";
	Islands[FindIsland("Caiman")].reload.l1.go = "Caiman_town";
	Islands[FindIsland("Caiman")].reload.l1.emerge = "reload1";
	Islands[FindIsland("Caiman")].reload.l1.radius = 600.0;
	Islands[FindIsland("Caiman")].reload.l1.pic = 0;
	Islands[FindIsland("Caiman")].reload.l1.tex = "t1";
	Islands[FindIsland("Caiman")].reload.l1.istown = true;

	ref rShore = &Locations[FindLocation("Shore16")];
	rShore.reload.l1.go = "Caiman_ExitTown";
	rShore.reload.l1.emerge = "reload2";
	rShore.reload.l1.autoreload = "1";
	rShore.reload.l1.label = "ExitTown";

	ref rCaveEntrance = &Locations[FindLocation("Caiman_CaveEntrance")];
	rCaveEntrance.reload.l2.go = "Caiman_ExitTown";
	rCaveEntrance.reload.l2.emerge = "reload1";
	rCaveEntrance.reload.l2.autoreload = "1";
	rCaveEntrance.reload.l2.label = "ExitTown";

	ref rJungle = &Locations[FindLocation("Caiman_Jungle_01")];
	rJungle.reload.l1.name = "reload1_back";
	rJungle.reload.l1.go = "Caiman_Plantation";
	rJungle.reload.l1.emerge = "reload2";
	rJungle.reload.l1.autoreload = "1";
	rJungle.reload.l1.label = "Plantation";

	rJungle.reload.l2.name = "reload2_back";
	rJungle.reload.l2.go = "Shore16";
	rJungle.reload.l2.emerge = "reload1";
	rJungle.reload.l2.autoreload = "1";
	rJungle.reload.l2.label = "Shore16";

	rJungle.reload.l3.name = "reload3_back";
	rJungle.reload.l3.go = "Caiman_CaveEntrance";
	rJungle.reload.l3.emerge = "reload2";
	rJungle.reload.l3.autoreload = "1";
	rJungle.reload.l3.label = "Jungle";

	Stores[Caiman_STORE].StoreSize = "large";

	AddSimpleRumourToAllNations(LinkRandPhrase("Поговаривают", "Говорят", "Ходят слухи") + ", что недавно капитан " + GetNameLugger(PChar, "f") + " расширил"+ GetSexPhrase("","а") +" свою колонию, которая называется ''"+PChar.ColonyBuilding.ColonyName+"''.", 5, 1);
}

void CreatePlantationInCaiman()
{
	LAi_QuestDelay("PlantationUptade1", 1.0);

	PChar.ColonyBuilding.Plantation = true;

	ref rTown = &Locations[FindLocation("Caiman_town")];
	rTown.reload.gate.name = "gate_back";
	rTown.reload.gate.go = "Caiman_Plantation";
	rTown.reload.gate.emerge = "reload1";
	rTown.reload.gate.autoreload = "0";
	rTown.reload.gate.label = "Caiman Plantation";

	ref rJungle = &Locations[FindLocation("Caiman_Jungle_01")];
	rJungle.reload.l1.name = "reload1_back";
	rJungle.reload.l1.go = "Caiman_Plantation";
	rJungle.reload.l1.emerge = "reload2";
	rJungle.reload.l1.autoreload = "1";
	rJungle.reload.l1.label = "Caiman Plantation";

	if(PChar.ColonyBuilding.Mines == false)
	{
		ref rCaveEntrance = &Locations[FindLocation("Caiman_CaveEntrance")];
		rCaveEntrance.reload.l2.go = "Caiman_Jungle_01";
		rCaveEntrance.reload.l2.emerge = "reload3";
		rCaveEntrance.reload.l2.autoreload = "1";
		rCaveEntrance.reload.l2.label = "Jungle";
	}
	else
	{
		rJungle.reload.l3.name = "reload3_back";
		rJungle.reload.l3.go = "Caiman_ExitMines";
		rJungle.reload.l3.emerge = "reload2";
		rJungle.reload.l3.autoreload = "1";
		rJungle.reload.l3.label = "Caiman Mines Exit";

		ref rExitMines = &Locations[FindLocation("Caiman_ExitMines")];
		rExitMines.reload.l2.name = "reload2_back";
		rExitMines.reload.l2.go = "Caiman_Jungle_01";
		rExitMines.reload.l2.emerge = "reload3";
		rExitMines.reload.l2.autoreload = "1";
		rExitMines.reload.l2.label = "Jungle";
	}

	if(PChar.ColonyBuilding.Fort == false)
	{
		ref rShore = &Locations[FindLocation("Shore16")];
		rShore.reload.l1.go = "Caiman_Jungle_01";
		rShore.reload.l1.emerge = "reload2";
		rShore.reload.l1.autoreload = "1";
		rShore.reload.l1.label = "Jungle";
	}
	else
	{
		rJungle.reload.l2.name = "reload2_back";
		rJungle.reload.l2.go = "LandGuardingPort";
		rJungle.reload.l2.emerge = "reload1";
		rJungle.reload.l2.autoreload = "1";
		rJungle.reload.l2.label = "Land Guarding Port";

		ref rBase = &Locations[FindLocation("LandGuardingPort")];
		rBase.reload.l1.name = "reload1_back";
		rBase.reload.l1.go = "Caiman_Jungle_01";
		rBase.reload.l1.emerge = "reload2";
		rBase.reload.l1.autoreload = "1";
		rBase.reload.l1.label = "Jungle";
	}

	AddSimpleRumourToAllNations(LinkRandPhrase("Поговаривают", "Говорят", "Ходят слухи") + ", что колония ''"+PChar.ColonyBuilding.ColonyName+"'', хозяином которой является некий капитан " + GetNameLugger(PChar, "f") + ", недавно обзавелась собственной плантацией!", 5, 1);
}

void CreateMinesInCaiman()
{
	LAi_QuestDelay("MinesUptade1", 1.0);


	PChar.ColonyBuilding.Mines = true;

	ref rExitTown = &Locations[FindLocation("Caiman_ExitTown")];
	rExitTown.reload.l2.name = "reload1_back";
	rExitTown.reload.l2.go = "Caiman_ExitMines";
	rExitTown.reload.l2.emerge = "reload2";
	rExitTown.reload.l2.autoreload = "1";
	rExitTown.reload.l2.label = "Caiman Mines Exit";
	rExitTown.locators_radius.reload.reload1_back = 2.0;

	ref rCaveEntrance = &Locations[FindLocation("Caiman_CaveEntrance")];
	rCaveEntrance.reload.l2.go = "Caiman_ExitMines";
	rCaveEntrance.reload.l2.emerge = "reload1";
	rCaveEntrance.reload.l2.autoreload = "1";
	rCaveEntrance.reload.l2.label = "Caiman Mines Exit";

	if(PChar.ColonyBuilding.Plantation == true && PChar.ColonyBuilding.Plantation.BuildingTime == false)
	{
		ref rJungle = &Locations[FindLocation("Caiman_Jungle_01")];
		rJungle.reload.l3.name = "reload3_back";
		rJungle.reload.l3.go = "Caiman_ExitMines";
		rJungle.reload.l3.emerge = "reload2";
		rJungle.reload.l3.autoreload = "1";
		rJungle.reload.l3.label = "Caiman Mines Exit";

		ref rExitMines = &Locations[FindLocation("Caiman_ExitMines")];
		rExitMines.reload.l2.name = "reload2_back";
		rExitMines.reload.l2.go = "Caiman_Jungle_01";
		rExitMines.reload.l2.emerge = "reload3";
		rExitMines.reload.l2.autoreload = "1";
		rExitMines.reload.l2.label = "Jungle";
	}

	AddSimpleRumourToAllNations(LinkRandPhrase("Поговаривают", "Говорят", "Ходят слухи") + ", что колония ''"+PChar.ColonyBuilding.ColonyName+"'', хозяином которой является некий капитан " + GetNameLugger(PChar, "f") + ", недавно обзавелась собственными рудниками!", 5, 1);
}

void CreateFortInCaiman()
{
	PChar.ColonyBuilding.Food.MaxQuantity = 12500;

	PChar.ColonyBuilding.Fort = true;
	PChar.ColonyBuilding.Stage = "3";
	PChar.ColonyBuilding.Soldiers.MaxQuantity = 2500;

	if(PChar.ColonyBuilding.Plantation == true)
	{
		ref rBase = &Locations[FindLocation("LandGuardingPort")];
		rBase.reload.l1.name = "reload1_back";
		rBase.reload.l1.go = "Caiman_Jungle_01";
		rBase.reload.l1.emerge = "reload2";
		rBase.reload.l1.autoreload = "1";
		rBase.reload.l1.label = "Jungle";

		ref rJungle = &Locations[FindLocation("Caiman_Jungle_01")];
		rJungle.reload.l2.name = "reload2_back";
		rJungle.reload.l2.go = "LandGuardingPort";
		rJungle.reload.l2.emerge = "reload1";
		rJungle.reload.l2.autoreload = "1";
		rJungle.reload.l2.label = "Land Guarding Port";
	}
	else
	{
		ref rExitTown = &Locations[FindLocation("Caiman_ExitTown")];
		rExitTown.reload.l3.name = "reload2_back";
		rExitTown.reload.l3.go = "LandGuardingPort";
		rExitTown.reload.l3.emerge = "reload1";
		rExitTown.reload.l3.autoreload = "1";
		rExitTown.reload.l3.label = "Land Guarding Port";
	}

	Islands[FindIsland("Caiman")].reload.l2.label = "Land Guarding Port";
	Islands[FindIsland("Caiman")].reload.l2.name = "reload_1";
	Islands[FindIsland("Caiman")].reload.l2.go = "LandGuardingPort";
	Islands[FindIsland("Caiman")].reload.l2.emerge = "sea";
	Islands[FindIsland("Caiman")].reload.l2.radius = 600.0;
	Islands[FindIsland("Caiman")].reload.l2.pic = 0;
	Islands[FindIsland("Caiman")].reload.l2.tex = "t1";

	int idLngFile = LanguageOpenFile("LocLables.txt");
	worldMap.labels.Shore16.text = CheckingTranslate(idLngFile,"Land Guarding Port");
	LanguageCloseFile(idLngFile);

	AddSimpleRumourToAllNations(LinkRandPhrase("Поговаривают", "Говорят", "Ходят слухи") + ", что известный в Карибах капитан " + GetNameLugger(PChar, "f") + " приказал архитектору, возводившему его колонию, соорудить защитную базу для отражения вражеских атак.", 5, 1);
}

void CreateTownCaiman()
{
	ref rTown;
	int n = FindLocation("Caiman_town");
	makeref(rTown, Locations[n]);

	DeleteAttribute(rTown, "models.always");
	DeleteAttribute(rTown, "models.day");
	DeleteAttribute(rTown, "models.night");

	rTown.id.label = "Street";
	rTown.worldmap = "Caiman";
	rTown.image = "loading\jonny_load\outside\smugglerLairTown_(pirate_town).tga";
	rTown.citizens = true;
	rTown.soldiers = true;
	rTown.carrier = true;
	//rTown.townsack = "Caiman";
	//rTown.fastreload = "Caiman";
	rTown.type = "town";
	//rTown.islandId = "Caiman";
	LAi_LocationFantomsGen(rTown, false);
	rTown.houseEnc = false;

	int iTown = sti(PChar.ColonyBuilding.Architecture.Town);
	string sTown = "Antigua";

	switch(iTown) { case 1: sTown = "Antigua"; break; case 2: sTown = "Maracaibo"; break; case 3: sTown = "Cartahena"; break; }

	rTown.filespath.models = "locations\Town_" + sTown + "\Town\";
	rTown.models.always.town = sTown;
	rTown.models.always.town.sea_reflection = 1;
	rTown.models.always.L1 = sTown + "_signsA";
	rTown.models.always.seabed =  sTown + "_sb";
	rTown.models.always.locators =  sTown + "_locators";
	rTown.models.always.grassPatch =  sTown + "_grass";
	rTown.models.day.fonar =  sTown + "_fd";
	rTown.models.day.charactersPatch =  sTown + "_patch_day";
	rTown.models.day.rinok =  sTown + "_rinok";
	rTown.models.night.fonar =  sTown + "_fn";
	rTown.models.night.charactersPatch =  sTown + "_patch_night";
	rTown.models.always.plan = "plan1";
	rTown.models.always.plan.level = 9;

	rTown.models.always.MillFan = "MillFan";
	rTown.models.always.MillFan.locator.group = "WindMill";
	rTown.models.always.MillFan.locator.name ="Fan";
	rTown.models.always.MillFan.rotate.x = 0.0;
	rTown.models.always.MillFan.rotate.y = 0.0;
	rTown.models.always.MillFan.rotate.z = 0.3;

	if(sTown == "Maracaibo") { rTown.models.always.MillFan.rotate.z = 0.26; }

	if(sTown == "Maracaibo")
	{
		rTown.models.always.Waterfall1 = "fontain1";
		rTown.models.always.Waterfall1.uvslide.v0 = 0.5;
		rTown.models.always.Waterfall1.uvslide.v1 = 0.0;
		rTown.models.always.Waterfall1.tech = "LocationWaterFall";
		rTown.models.always.Waterfall1.level = 50;

		rTown.models.always.Waterfall2 = "fontain2";
		rTown.models.always.Waterfall2.uvslide.v0 = 0.2;
		rTown.models.always.Waterfall2.uvslide.v1 = 0.0;
		rTown.models.always.Waterfall2.tech = "LocationWaterFall";
		rTown.models.always.Waterfall2.level = 49;
	}

	if(sTown == "Cartahena")
	{
		rTown.models.always.Waterfall1 = "river1";
		rTown.models.always.Waterfall1.uvslide.v0 = 0.2;
		rTown.models.always.Waterfall1.uvslide.v1 = 0.0;
		rTown.models.always.Waterfall1.tech = "LocationWaterFall";
		rTown.models.always.Waterfall1.level = 50;

		rTown.models.always.Waterfall2 = "river2";
		rTown.models.always.Waterfall2.uvslide.v0 = 0.3;
		rTown.models.always.Waterfall2.uvslide.v1 = 0.0;
		rTown.models.always.Waterfall2.tech = "LocationWaterFall";
		rTown.models.always.Waterfall2.level = 49;
	}

	rTown.environment.weather = "true";
	rTown.environment.sea = "true";

	DeleteAttribute(rTown, "reload");

	rTown.reload.l1.name = "reload1_back";
	rTown.reload.l1.go = "Caiman";
	rTown.reload.l1.emerge = "reload_2";
	rTown.reload.l1.autoreload = "0";
	rTown.reload.l1.label = "Sea";
	rTown.locators_radius.reload.reload1_back = 1.8;

	rTown.reload.l2.name = "reload2_back";
	rTown.reload.l2.go = "Caiman";
	rTown.reload.l2.emerge = "reload_2";
	rTown.reload.l2.autoreload = "0";
	rTown.reload.l2.label = "Sea";
	rTown.locators_radius.reload.reload2_back = 1.8;

	rTown.reload.l3.name = "reload3_back";
	rTown.reload.l3.go = "Caiman_townhall";
	rTown.reload.l3.emerge = "reload1";
	rTown.reload.l3.autoreload = "0";
	rTown.reload.l3.label = "Townhall";
	rTown.reload.l3.disable = false;

	rTown.reload.l4.name = "reload4_back";
	rTown.reload.l4.go = "Caiman_tavern";
	rTown.reload.l4.emerge = "reload1";
	rTown.reload.l4.autoreload = "0";
	rTown.reload.l4.label = "Tavern";
	rTown.reload.l4.disable = true;

	rTown.reload.l5.name = "reload5_back";
	rTown.reload.l5.go = "Caiman_shipyard";
	rTown.reload.l5.emerge = "reload1";
	rTown.reload.l5.autoreload = "0";
	rTown.reload.l5.label = "Shipyard";
	rTown.reload.l5.disable = true;
	rTown.reload.l5.close_for_night = 1;

	rTown.reload.l6.name = "reload6_back";
	rTown.reload.l6.go = "Caiman_store";
	rTown.reload.l6.emerge = "reload1";
	rTown.reload.l6.autoreload = "0";
	rTown.reload.l6.label = "Store";
	rTown.reload.l6.close_for_night = 1;
	rTown.reload.l6.disable = true;

	rTown.reload.l7.name = "reload7_back";
	rTown.reload.l7.go = "Caiman_church";
	rTown.reload.l7.emerge = "reload1";
	rTown.reload.l7.autoreload = "0";
	rTown.reload.l7.label = "Church";
	rTown.reload.l7.disable = true;
	rTown.reload.l7.close_for_night = 1;

	rTown.reload.l8.name = "reload8_back";
	rTown.reload.l8.go = "Caiman_bank";
	rTown.reload.l8.emerge = "reload1";
	rTown.reload.l8.autoreload = "0";
	rTown.reload.l8.label = "Usurer House";
	rTown.reload.l8.close_for_night = 1;
	rTown.reload.l8.disable = true;

	rTown.reload.l10.name = "reload10_back";
	rTown.reload.l10.go = "Caiman_PortOffice";
	rTown.reload.l10.emerge = "reload1";
	rTown.reload.l10.autoreload = "0";
	rTown.reload.l10.label = "PortOffice";
	rTown.reload.l10.close_for_night = 1;
	rTown.reload.l10.disable = true;

	rTown.reload.gate.name = "gate_back";
	rTown.reload.gate.go = "Caiman_ExitTown";
	rTown.reload.gate.emerge = "reload3";
	rTown.reload.gate.autoreload = "0";
	rTown.reload.gate.label = "ExitTown";

	if(sTown == "Antigua") 		{ rTown.reload.l11.name = "houseS1"; }
	if(sTown == "Maracaibo") 	{ rTown.reload.l11.name = "houseS6"; }
	if(sTown == "Cartahena") 	{ rTown.reload.l11.name = "houseS2"; }

	rTown.reload.l11.go = "Caiman_StoreHouse";
	rTown.reload.l11.emerge = "reload1";
	rTown.reload.l11.autoreload = "0";
	rTown.reload.l11.label = "Caiman Store House";
	rTown.reload.l11.disable = true;
	rTown.reload.l11.close_for_night = 1;

	if(PChar.ColonyBuilding.Store == true) { rTown.reload.l6.disable = false; }
	if(PChar.ColonyBuilding.StoreHouse == true) { rTown.reload.l11.disable = false; }
	if(PChar.ColonyBuilding.Tavern == true) { rTown.reload.l4.disable = false; }

	if(sTown == "Antigua")
	{
		rTown.reload.l20.name = "houseF2";
		rTown.reload.l20.go = "CommonRoom_MH2";
		rTown.reload.l20.emerge = "reload1";
		rTown.reload.l20.autoreload = "0";
		rTown.reload.l20.label = "House";

		rTown.reload.l21.name = "houseSp3";
		rTown.reload.l21.go = "CommonDoubleflourHouse_1";
		rTown.reload.l21.emerge = "reload1";
		rTown.reload.l21.autoreload = "0";
		rTown.reload.l21.label = "House";

		rTown.reload.l22.name = "houseS4";
		rTown.reload.l22.go = "CommonCobHouse";
		rTown.reload.l22.emerge = "reload1";
		rTown.reload.l22.autoreload = "0";
		rTown.reload.l22.label = "House";

		rTown.reload.l23.name = "houseH2";
		rTown.reload.l23.go = "CommonRoom_MH4";
		rTown.reload.l23.emerge = "reload1";
		rTown.reload.l23.autoreload = "0";
		rTown.reload.l23.label = "House";

		rTown.reload.l24.name = "houseS2";
		rTown.reload.l24.go = "CommonPirateHouse";
		rTown.reload.l24.emerge = "reload1";
		rTown.reload.l24.autoreload = "0";
		rTown.reload.l24.label = "House";

		rTown.reload.l25.name = "houseSp2";
		rTown.reload.l25.go = "CommonStoneHouse";
		rTown.reload.l25.emerge = "reload1";
		rTown.reload.l25.autoreload = "0";
		rTown.reload.l25.label = "House";

		rTown.reload.l26.name = "houseSp1";
		rTown.reload.l26.go = "CommonResidence_BackHall";
		rTown.reload.l26.emerge = "reload1";
		rTown.reload.l26.autoreload = "0";
		rTown.reload.l26.label = "House";

		rTown.reload.l27.name = "houseF1";
		rTown.reload.l27.go = "CommonRoom_MH5";
		rTown.reload.l27.emerge = "reload1";
		rTown.reload.l27.autoreload = "0";
		rTown.reload.l27.label = "House";

		rTown.reload.l28.name = "houseH1";
		rTown.reload.l28.go = "CommonHut";
		rTown.reload.l28.emerge = "reload1";
		rTown.reload.l28.autoreload = "0";
		rTown.reload.l28.label = "House";

		rTown.reload.l29.name = "houseS3";
		rTown.reload.l29.go = "CommonStoneHouse";
		rTown.reload.l29.emerge = "reload1";
		rTown.reload.l29.autoreload = "0";
		rTown.reload.l29.label = "House";

		rTown.reload.l30.name = "houseF4";
		rTown.reload.l30.go = "CommonRoom_MH5";
		rTown.reload.l30.emerge = "reload1";
		rTown.reload.l30.autoreload = "0";
		rTown.reload.l30.label = "House";

		RecalculateJumpTable();
		return;
	}

	if(sTown == "Maracaibo")
	{
		rTown.reload.l20.name = "houseSp3";
		rTown.reload.l20.go = "CommonDoubleflourHouse_1";
		rTown.reload.l20.emerge = "reload1";
		rTown.reload.l20.autoreload = "0";
		rTown.reload.l20.label = "House";

		rTown.reload.l21.name = "houseSp2";
		rTown.reload.l21.go = "CommonStoneHouse";
		rTown.reload.l21.emerge = "reload1";
		rTown.reload.l21.autoreload = "0";
		rTown.reload.l21.label = "House";

		rTown.reload.l22.name = "houseF3";
		rTown.reload.l22.go = "CommonRoom_MH2";
		rTown.reload.l22.emerge = "reload1";
		rTown.reload.l22.autoreload = "0";
		rTown.reload.l22.label = "House";

		rTown.reload.l23.name = "houseS2";
		rTown.reload.l23.go = "CommonPirateHouse";
		rTown.reload.l23.emerge = "reload1";
		rTown.reload.l23.autoreload = "0";
		rTown.reload.l23.label = "House";

		rTown.reload.l24.name = "houseF4";
		rTown.reload.l24.go = "CommonRoom_MH";
		rTown.reload.l24.emerge = "reload1";
		rTown.reload.l24.autoreload = "0";
		rTown.reload.l24.label = "House";

		rTown.reload.l25.name = "houseS5";
		rTown.reload.l25.go = "CommonStoneHouse";
		rTown.reload.l25.emerge = "reload1";
		rTown.reload.l25.autoreload = "0";
		rTown.reload.l25.label = "House";

		rTown.reload.l26.name = "houseSp1";
		rTown.reload.l26.go = "CommonDoubleflourHouse_2";
		rTown.reload.l26.emerge = "reload1";
		rTown.reload.l26.autoreload = "0";
		rTown.reload.l26.label = "House";

		rTown.reload.l27.name = "houseF2";
		rTown.reload.l27.go = "CommonRoom_MH3";
		rTown.reload.l27.emerge = "reload1";
		rTown.reload.l27.autoreload = "0";
		rTown.reload.l27.label = "House";

		rTown.reload.l28.name = "houseS4";
		rTown.reload.l28.go = "CommonCobHouse";
		rTown.reload.l28.emerge = "reload1";
		rTown.reload.l28.autoreload = "0";
		rTown.reload.l28.label = "House";

		rTown.reload.l29.name = "houseS3";
		rTown.reload.l29.go = "CommonPirateHouse";
		rTown.reload.l29.emerge = "reload1";
		rTown.reload.l29.autoreload = "0";
		rTown.reload.l29.label = "House";

		rTown.reload.l30.name = "houseS1";
		rTown.reload.l30.go = "CommonFlamHouse";
		rTown.reload.l30.emerge = "reload1";
		rTown.reload.l30.autoreload = "0";
		rTown.reload.l30.label = "House";

		rTown.reload.l31.name = "houseF1";
		rTown.reload.l31.go = "CommonRoom_MH9";
		rTown.reload.l31.emerge = "reload1";
		rTown.reload.l31.autoreload = "0";
		rTown.reload.l31.label = "House";

		RecalculateJumpTable();
		return;
	}

	if(sTown == "Cartahena")
	{
		rTown.reload.l20.name = "houseS1";
		rTown.reload.l20.go = "CommonCobHouse";
		rTown.reload.l20.emerge = "reload1";
		rTown.reload.l20.autoreload = "0";
		rTown.reload.l20.label = "House";

		rTown.reload.l21.name = "houseSp1";
		rTown.reload.l21.go = "CommonPirateHouse";
		rTown.reload.l21.emerge = "reload1";
		rTown.reload.l21.autoreload = "0";
		rTown.reload.l21.label = "House";

		rTown.reload.l22.name = "houseSp2";
		rTown.reload.l22.go = "CommonDoubleflourHouse_1";
		rTown.reload.l22.emerge = "reload1";
		rTown.reload.l22.autoreload = "0";
		rTown.reload.l22.label = "House";

		rTown.reload.l23.name = "houseH1";
		rTown.reload.l23.go = "CommonRoom_MH3";
		rTown.reload.l23.emerge = "reload1";
		rTown.reload.l23.autoreload = "0";
		rTown.reload.l23.label = "House";
		rTown.reload.l23.close_for_night = 1;

		rTown.reload.l24.name = "houseSp3";
		rTown.reload.l24.go = "CommonResidence_BackHall";
		rTown.reload.l24.emerge = "reload1";
		rTown.reload.l24.autoreload = "0";
		rTown.reload.l24.label = "House";

		rTown.reload.l25.name = "houseS3";
		rTown.reload.l25.go = "CommonPirateHouse";
		rTown.reload.l25.emerge = "reload1";
		rTown.reload.l25.autoreload = "0";
		rTown.reload.l25.label = "House";

		rTown.reload.l26.name = "houseH2";
		rTown.reload.l26.go = "CommonRoom_MH4";
		rTown.reload.l26.emerge = "reload1";
		rTown.reload.l26.autoreload = "0";
		rTown.reload.l26.label = "House";

		rTown.reload.l27.name = "houseS4";
		rTown.reload.l27.go = "CommonStoneHouse";
		rTown.reload.l27.emerge = "reload1";
		rTown.reload.l27.autoreload = "0";
		rTown.reload.l27.label = "House";

		rTown.reload.l28.name = "houseF2";
		rTown.reload.l28.go = "CommonRoom_MH9";
		rTown.reload.l28.emerge = "reload1";
		rTown.reload.l28.autoreload = "0";
		rTown.reload.l28.label = "House";

		rTown.reload.l29.name = "houseF1";
		rTown.reload.l29.go = "CommonRoom_MH7";
		rTown.reload.l29.emerge = "reload1";
		rTown.reload.l29.autoreload = "0";
		rTown.reload.l29.label = "House";

		RecalculateJumpTable();
		return;
	}
}

/////////////////////////////////////////////////////////////////////////////
// AUTO SELL
/////////////////////////////////////////////////////////////////////////////
int GetCurrentGoodBaseCostForAutoSell(int iGood)
{
	ref rStore = &Stores[Caiman_STORE];

	int iStoreCost = 0;
	iStoreCost = GetStoreGoodsPrice(rStore, iGood, PRICE_TYPE_SELL, PChar, 1) / 1.3;

	return iStoreCost;
}

string GetColonyAutoSellWork()
{
	bool bMines = PChar.ColonyBuilding.Mines.AutoSell;
	bool bPlantation = PChar.ColonyBuilding.Plantation.AutoSell;

	if(!bMines && !bPlantation)
	{
		return XI_ConvertString("ColonyGoodsAutoSell_1");
	}
	if(bMines && !bPlantation)
	{
		return XI_ConvertString("ColonyGoodsAutoSell_2");
	}
	if(!bMines && bPlantation)
	{
		return XI_ConvertString("ColonyGoodsAutoSell_3");
	}
	if(bMines && bPlantation)
	{
		return XI_ConvertString("ColonyGoodsAutoSell_4");
	}

	return "bug";
}

int GetColonyAutoSellCurrentQty(string sType)
{
	if(CheckAttribute(PChar, "ColonyBuilding." + sType + ".AutoSell.Qty"))
	{
		return sti(PChar.ColonyBuilding.(sType).AutoSell.Qty);
	}

	return 0;
}





