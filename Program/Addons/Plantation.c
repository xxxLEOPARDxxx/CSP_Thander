/* Плантация, её развитие и повседневные дела */
#define EXTRACT_SUGAR 			3.9
#define EXTRACT_COFFEE 			2.1

#define AUTO_SELL_PLANTATION_MAX 	2000
#define AUTO_SELL_SUGAR 		10
#define AUTO_SELL_COFFEE 		46

#define PLANTATION_FOOD_DELIT		50
#define PLANTATION_MEDICAMENT_DELIT	50

void InitPlantation()
{
	ref PChar = GetMainCharacter();
	PChar.Plantation.ResizeMoney = 30000 + rand(5000);

	PChar.Plantation.Size = 1;
	PChar.Plantation.Size.Resize.BuildingTime = false;

	/*
	PChar.Plantation.Slaves.Speed = 0;
	PChar.Plantation.Slaves.Health = 0;
	PChar.Plantation.Slaves.Morale = 0;
	*/

	PChar.Plantation.Slaves.Quantity = 0;
	PChar.Plantation.Slaves.MaxQuantity = 250;
	PChar.Plantation.Slaves.Temp.Quantity = 0;

	PChar.Plantation.Slaves.Epidemy = false;

	PChar.Plantation.Mutiny = false;

	PChar.Plantation.Food.Quantity = 0;
	PChar.Plantation.Food.Temp.Quantity = 0;
	PChar.Plantation.Food.MaxQuantity = 5000;

	PChar.Plantation.Medicament.Quantity = 0;
	PChar.Plantation.Medicament.Temp.Quantity = 0;
	PChar.Plantation.Medicament.MaxQuantity = 3000;

	PChar.Plantation.Sugar.Quantity = 0;
	PChar.Plantation.Sugar.Temp.Quantity = 0;
	PChar.Plantation.Sugar.MaxQuantity = 5000;

	PChar.Plantation.Coffee.Quantity = 0;
	PChar.Plantation.Coffee.Temp.Quantity = 0;
	PChar.Plantation.Coffee.MaxQuantity = 7500;

	PChar.Plantation.Guardians.Quantity = 0;
	PChar.Plantation.Guardians.MaxQuantity = 250;
	PChar.Plantation.Guardians.Temp.Quantity = 0;

	PChar.Plantation.Items.Quantity = 0;
	PChar.Plantation.Items.MaxQuantity = 300;
	PChar.Plantation.Items.Temp.Quantity = 0;

	PChar.Plantation.Instrument = 0;

	PChar.Plantation.Commander = "";

	PChar.Plantation.Defence = false;
	PChar.Plantation.Defence.Block = false;
	PChar.Plantation.Defence.Battle = false;
	PChar.Plantation.Defence.DeadInTown = false;
	PChar.Plantation.Defence.Type = "Mutiny";
}

void UptadeLivedInPlantation()
{
	AutoPurchaseColonyGoods("Plantation");
	ColonyGuardingAutoCrewHire("Plantation");
	PlantationSlavesUptade();

	if(PChar.Plantation.Size.Resize.BuildingTime != true)
	{
		PlantationCheckSlavesEpidemy();
		PlantationExtractUptade();
	}
	else
	{
		Log_InfoS("В связи с расширением плантации добыча товаров приостановлена.");
	}

	PlantationExtractGoodsAutoSell();
}

void PlantationCheckSlavesEpidemy()
{
	if(rand(100) > 10)
	{
		return;
	}

	int iSlaves = sti(PChar.Plantation.Slaves.Quantity);
	int iMedicament = sti(PChar.Plantation.Medicament.Quantity);

	if(iSlaves < 10)
	{
		return;
	}

	Log_InfoS("По вашей плантации пронеслась эпидемия.");

	int iDead = 0;
	int iMedicamentNeed = 0;
	if(iMedicament >= iSlaves)
	{
		iDead = rand(10) + 10;
		iMedicamentNeed = iSlaves - iDead;

		ChangePlantationGoods(-iMedicamentNeed, "Medicament", false);
		ChangePlantationSlaves(-iDead, false);

		Log_Info("Благодаря имеющимся медикаментам количество погибших рабов удалось существенно сократить. Количество погибших рабов: " + iDead);
	}
	else
	{
		iDead = iSlaves - iMedicament;
		if(iDead) { iDead = 0; }

		if(iDead > 0)
		{
			ChangePlantationGoods(-iDead, "Medicament", false);
			ChangePlantationSlaves(-iDead, false);
			Log_Info("Количество погибших рабов: " + iDead);
		}
	}
}

void PlantationSlavesUptade()
{
	PlantationFoodUptade();
	PlantationMedicamentUptade();

	int iTools = sti(PChar.Plantation.Items.Quantity) / 100 + rand(2);
	if(rand(100) > 75 && sti(PChar.Plantation.Slaves.Quantity) != 0)
	{
		ChangePlantationGoods(-iTools, "Items", false);
		Log_Info("На вашей плантации инструменты в количестве " + iTools + " шт. пришли в негодность.");
	}

	if(sti(PChar.Plantation.Items.Quantity) < 10 && sti(PChar.Plantation.Items.Quantity) > 0)
	{
		Log_Info("На вашей плантации осталось мало инструментов.");
	}

	if(sti(PChar.Plantation.Items.Quantity) <= 0)
	{
		Log_Info("На вашей плантации нет инструментов.");
		Log_Info("Необходимо срочно доставить новые инструменты, иначе скорость добычи упадёт в несколько раз.");
	}

	bool bDisable = GetDisableAllColonyEvent();
	int iSlaves = sti(PChar.Plantation.Slaves.Quantity);
	if(iSlaves > 100)
	{
		if(rand(100) > 75 && PChar.Plantation.Defence.Block == false && !bDisable)
		{
			PlantationMutiny();
		}
	}
}

void PlantationFoodUptade()
{
	int iDead = 0;
	int iSlaves = sti(PChar.Plantation.Slaves.Quantity);

	if(iSlaves < 1) { return; }

	float fCoff = 0.0;
	int iFoodDiff = iSlaves / PLANTATION_FOOD_DELIT;
	if(iFoodDiff < 1)
	{
		iFoodDiff = 1;
	}

	int iFood = sti(PChar.Plantation.Food.Quantity);
	int iFoodNeed = iFoodDiff * 14;
	fCoff = iFoodDiff / iSlaves;

	if(iFood >= iFoodNeed)
	{
		ChangePlantationGoods(-iFoodNeed, "Food", false);
	}
	else
	{
		iDead = iFoodNeed - iFood;
		iDead /= 14;
		iDead /= fCoff;

		if(iDead > iSlaves)
		{
			iDead = iSlaves;
		}

		ChangePlantationGoods(-iFoodNeed, "Food", false);
		ChangePlantationSlaves(-iDead, false);

		Log_InfoS("На вашей плантации закончился провиант. От голода умерло рабов: " + iDead + ".");
	}

	int iSoldiers = sti(PChar.Plantation.Guardians.Quantity);
	if(iSoldiers < 1) { return; }

	fCoff = 0.0;
	iFoodDiff = iSoldiers / PLANTATION_FOOD_DELIT;
	if(iFoodDiff < 1)
	{
		iFoodDiff = 1;
	}

	iFood = sti(PChar.Plantation.Food.Quantity);
	iFoodNeed = iFoodDiff * 14;
	fCoff = iFoodDiff / iSoldiers;

	if(iFood >= iFoodNeed)
	{
		ChangePlantationGoods(-iFoodNeed, "Food", false);
	}
	else
	{
		iDead = iFoodNeed - iFood;
		iDead /= 14;
		iDead /= fCoff;

		if(iDead > iSoldiers)
		{
			iDead = iSoldiers;
		}

		ChangePlantationGoods(0, "Food", true);
		ChangePlantationSoldiers(-iDead, false);

		Log_InfoS("На вашей плантации закончился провиант. От голода умерло надсмотрщиков: " + iDead + ".");
	}
}

void PlantationMedicamentUptade()
{
	int iDead = 0;
	int iSlaves = sti(PChar.Plantation.Slaves.Quantity);

	if(iSlaves < 1) { return; }

	float fCoff = 0.0;
	int iMedicamentDiff = iSlaves / PLANTATION_MEDICAMENT_DELIT;
	if(iMedicamentDiff < 1)
	{
		iMedicamentDiff = 1;
	}

	int iMedicament = sti(PChar.Plantation.Medicament.Quantity);
	int iMedicamentNeed = iMedicamentDiff * 14;
	fCoff = iMedicamentDiff / iSlaves;

	if(iMedicament >= iMedicamentNeed)
	{
		ChangePlantationGoods(-iMedicamentNeed, "Medicament", false);
	}
	else
	{
		iDead = iMedicamentNeed - iMedicament;
		iDead /= 14;
		iDead /= fCoff;

		if(iDead > iSlaves)
		{
			iDead = iSlaves;
		}

		ChangePlantationGoods(0, "Medicament", true);
		ChangePlantationSoldiers(-iDead, false);

		Log_InfoS("На вашей плантации закончились медикаменты. От болезней умерло рабов: " + iDead + ".");
	}
}

void PlantationExtractUptade()
{
	if(PChar.Plantation.Commander == "")
	{
		Log_InfoS("Ваша плантация не имеет управляющего. Добыча не производится.");
		return;
	}

	int iSlaves = sti(PChar.Plantation.Slaves.Quantity);

	if(iSlaves < 1)
	{
		return;
	}

	iSlaves = sti(PChar.Plantation.Slaves.Quantity) / 10;

	float c = 0.0;
	int iQty = 0;
	string sType = "";

	int iSize = sti(PChar.Plantation.Size);
	float fSpeed = PlantationGetExtractSpeed();

	for(int i=1; i <= iSize; i++)
	{
		switch(i)
		{
			case 1: sType = "Sugar"; c = EXTRACT_SUGAR; break;
			case 2: sType = "Coffee"; c = EXTRACT_COFFEE; break;
		}

		iQty = iSlaves * (c * fSpeed);
		ChangePlantationExtract(iQty, sType, false);
	}
}

float PlantationGetExtractSpeed()
{
	float fSpeed = 5.0;

	int iSlaves = sti(PChar.Plantation.Slaves.Quantity);
	int iTools = sti(PChar.Plantation.Items.Quantity);
	float fDifferent = 0.0;

	if(iTools >= iSlaves)
	{
		fSpeed += 5.0;
	}
	else
	{
		if(iTools < iSlaves)
		{
			if(iTools < 1)
			{
				iTools = 1;
			}

			fDifferent = iSlaves / iTools;
			fSpeed -= fDifferent;
		}
	}

	if(fSpeed > 10.0)
	{
		fSpeed = 10.0;
	}

	if(fSpeed < 1.0)
	{
		fSpeed = 1.0;
	}

	return fSpeed;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// МЯТЕЖ
/////////////////////////////////////////////////////////////////////////////////////////////////
void PlantationMutiny()
{
	Log_TestInfo("Генерируем мятеж на плантации.");

	int iSlaves = sti(PChar.Plantation.Slaves.Quantity);
	int iGuardians = sti(PChar.Plantation.Guardians.Quantity);

	if(iSlaves < 1)	{ iSlaves = 1; }
	if(iGuardians < 1) { iGuardians = 1; }

	int iDifference = iGuardians / iSlaves;
	if(iDifference >= 2 || rand(4) > 2)
	{
		Log_TestInfo("Мятежа на рудниках не будет, т.к. рабов слишком мало по отношению к охране.");
		return;
	}

	// Включаем блокировку всех нападений -->
	PChar.ColonyBuilding.EventBlock = true;
	// Включаем блокировку всех нападений <--

	PChar.Plantation.Defence = true;
	PChar.Plantation.Defence.Block = true;
	PChar.Plantation.Defence.Type = "Mutiny";

	int iRebels = iSlaves / 20;
	if(iRebels < 2) iRebels = 2;
	if(iRebels > 20) iRebels = 20;

	PChar.Plantation.Defence.EnemyQuantity = iRebels;

	ChangePlantationSlaves(-(iRebels*10), false);

	int iSoldiersQuantity = iGuardians / 25;
	if(iSoldiersQuantity < 1)
	{
		InstantColonyDefendLoose("Plantation", "Mutiny");
		return;
	}

	if(iSoldiersQuantity < 2) iSoldiersQuantity = 2;
	if(iSoldiersQuantity > 20) iSoldiersQuantity = 20;

	int iRandMinus = 3;
	if(iRebels > iSoldiersQuantity)
	{
		iRandMinus -= (iRebels - iSoldiersQuantity);
	}
	else
	{
		iRandMinus += (iSoldiersQuantity - iRebels);
	}

	if(iRandMinus < -4)
	{
		InstantColonyDefendLoose("Plantation", "Mutiny");
		return;
	}

	int iRand = iRandMinus - rand(4);

	int iEnd = 0;
	if(iRand > 0) { iEnd = 1; }else{ iEnd = 0; }

	PChar.Plantation.Defence.Nation = PIRATE;
	PChar.Plantation.Defence.Soldiers = iSoldiersQuantity;
	PChar.Plantation.Defence.Soldiers.Delete = rand(1) + 3;

	PChar.Plantation.Defence.End = iEnd;

	int iTime = 4 + rand(10) + iRandMinus;
	//if(iTime < 8) { iTime = 8; }
	//if(iTime > 30) { iTime = 30; }

	string sClearQuest = "ClearMutinyPlantation_" + rand(1000000);
	PChar.Plantation.ClearQuest = sClearQuest;

	PChar.quest.(sClearQuest).win_condition.l1 = "Timer";
	PChar.quest.(sClearQuest).win_condition.l1.date.day = GetAddingDataDay(0, 0, iTime);
	PChar.quest.(sClearQuest).win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTime);
	PChar.quest.(sClearQuest).win_condition.l1.date.year = GetAddingDataYear(0, 0, iTime);
	PChar.quest.(sClearQuest).win_condition.l1.date.hour = 12;
	PChar.quest.(sClearQuest).function = "ClearMutinyPlantation";

	Log_Info("Вести с плантации, принадлежащей колонии " + PChar.ColonyBuilding.ColonyName + "!");

	string sTime = FindRussianDaysString(iTime);

	AddQuestRecord("MY_COLONY", "23");
	AddQuestUserData("MY_COLONY", "sMutinyTime", sTime);

	string sBattleQuest = "BattleMutinyPlantation_" + rand(1000000);
	PChar.Plantation.BattleQuest = sBattleQuest;

	PChar.quest.(sBattleQuest).win_condition.l1 = "location";
	PChar.quest.(sBattleQuest).win_condition.l1.location = "Caiman_Plantation";
	PChar.quest.(sBattleQuest).function = "BattleMutinyPlantation";

	SetColonyMessageInfo("Plantation", "Mutiny", "", PIRATE, iTime, true, true);
}

void BattleMutinyPlantation(string _tmp)
{
	string sClearQuest = PChar.Plantation.ClearQuest;
	PChar.quest.(sClearQuest).over = "yes";

	chrDisableReloadToLocation = true;
	bDisableFastReload = true;
	LAi_grp_alarmactive = true;
	InterfaceStates.Buttons.Save.enable = false;
	PChar.Plantation.Defence.Battle = true;
	string model[23];
	int iMassive;

	int i = 0;
	int iSoldiers = sti(PChar.Plantation.Defence.Soldiers);
	int iRebels = sti(PChar.Plantation.Defence.EnemyQuantity);
	ref chr;

	string sModel = "";
	string sLocator = "";
	string sAni = "man";

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

	for(i=1; i <= iRebels; i++)
	{
		iMassive = rand(22);

    	sAni = "man";
    	/* if(model[iMassive] == "pirate_1" || model[iMassive] == "pirate_11" || model[iMassive] == "pirate_12" || model[iMassive] == "pirate_13" || model[iMassive] == "pirate_14" || model[iMassive] == "pirate_15" || model[iMassive] == "pirate_16" || model[iMassive] == "pirate_21" || model[iMassive] == "pirate_25") sAni = "man"; */

		sModel = model[iMassive];
		sLocator = "aloc" + i;

		chr = GetCharacter(NPC_GeneratePhantomCharacter("officer_1", PIRATE, 1, 0));
		chr.rank = GetRank(PChar, MOD_SKILL_ENEMY_RATE) + 2;
		SetFantomParamFromRank(chr, sti(chr.rank), true);
		chr.id = "My Plantation Mutiny Rebel " + i;
		chr.model = sModel;
		chr.model.animation = sAni;
		chr.NotRemoved = true;
		SetNewModelToChar(chr);
    	//FaceMaker(chr);
		LAi_NoRebirthEnable(chr);
		LAi_SetWarriorType(chr);
		LAi_group_MoveCharacter(chr, "EnemyFight");
		ChangeCharacterAddressGroup(chr, PChar.location, "rld", sLocator);
	}

	int iNation = sti(PChar.ColonyBuilding.ColonyNation);
	string sNation = NationShortName(iNation);

	int iMusketeers = FightInColonyGetMusketeerQty(iSoldiers);
	bool bMusketeer = false;

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

		sLocator = "loc" + i;

		chr = GetCharacter(NPC_GeneratePhantomCharacter("officer_1", PIRATE, 1, 0));
		chr.rank = GetRank(PChar, MOD_SKILL_ENEMY_RATE) + 4;
		SetFantomParamFromRank(chr, sti(chr.rank), true);
		chr.id = "My Mines Plantation Defender " + i;
		chr.model = sModel;
		chr.model.animation = sAni;
		chr.NotRemoved = true;
		SetNewModelToChar(chr);
		LAi_NoRebirthEnable(chr);
		LAi_SetWarriorType(chr);
		LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
		ChangeCharacterAddressGroup(chr, PChar.location, "rld", sLocator);
	}

	LAi_group_SetHearRadius("EnemyFight", 100.0);
	LAi_group_FightGroupsEx("EnemyFight", LAI_GROUP_PLAYER, true, PChar, -1, false, false);
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_SetFightMode(PChar, true);

	string cnd, rbl;
	for(i=1; i<=iRebels; i++)
	{
		cnd = "l" + i;
		rbl = "My Plantation Mutiny Rebel " + i;
		PChar.quest.BattleMutinyPlantationWinner.win_condition.(cnd) = "NPC_Death";
		PChar.quest.BattleMutinyPlantationWinner.win_condition.(cnd).character = rbl;
	}

	PChar.quest.BattleMutinyPlantationWinner.function = "BattleMutinyPlantationWinner";

	ref loc = PCharLoc();
	DeleteAllFantomCharactersFromLocation(loc);

	SetDeadmansToLocation(&Locations[FindLocation(PChar.location)], "pirate");
}

void BattleMutinyPlantationWinner(string _tmp)
{
	InterfaceStates.Buttons.Save.enable = true;
	chrDisableReloadToLocation = false;
	bDisableFastReload = false;
	LAi_grp_alarmactive = false;

	LAi_LockFightMode(PChar, false);
        LAi_SetFightMode(PChar, false);

	AddQuestRecord("MY_COLONY", "2");

	int iSoldiers = sti(PChar.Plantation.Defence.Soldiers);
	int iDead = 0;

	string sDefender = "";
	for(int i=1; i<=iSoldiers; i++)
	{
		sDefender = "My Mines Plantation Defender " + i;
		if(LAi_IsDead(CharacterFromID(sDefender)))
		{
			iDead++;
		}
	}

	int iSoldiersDead = iDead * 25;
	ChangePlantationSoldiers(-iSoldiersDead, false);

	PChar.Plantation.Defence = false;
	PChar.Plantation.Defence.Battle = false;
	PChar.Plantation.Defence.Type = "";

	SetTimerCondition("PlantationUptade5", 0, 0, 40, false);

	// Выключаем блокировку всех нападений -->
	PChar.ColonyBuilding.EventBlock = false;
	// Выключаем блокировку всех нападений <--

	AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", на плантации, которая принадлежит колонии " + PChar.ColonyBuilding.ColonyName + " вспыхнул мятеж. Усмирить мятежников прибыл сам владелец колонии. Мало не показалось никому.", 5, 1);
}

void ClearMutinyPlantation(string qName)
{
	string sBattleQuest = PChar.Plantation.BattleQuest;
	PChar.quest.(sBattleQuest).over = "yes";

	PChar.Plantation.Defence = false;
	PChar.Plantation.Defence.Type = "";
	PChar.Plantation.Defence.DeadInTown = true;
	PChar.Plantation.Defence.Battle = false;

	SetTimerCondition("PlantationNotSetDead", 0, 0, 6, false);
	SetTimerCondition("PlantationUptade5", 0, 0, 30, false);

	int iEnd = sti(PChar.Plantation.Defence.End);
	int iSoldiers = sti(PChar.Plantation.Defence.Soldiers);
	int iRebels = sti(PChar.Plantation.Defence.EnemyQuantity);

	if(iSoldiers > 0)
	{
		iSoldiers /= sti(PChar.Plantation.Defence.Soldiers.Delete);
	}
	int iSoldiersDead = iSoldiers * 25;

	if(iEnd == 1)
	{
		Log_Info("Вести c плантации, принадлежащей колонии " + PChar.ColonyBuilding.ColonyName + "!");
		AddQuestRecord("MY_COLONY", "2");
		ChangePlantationSoldiers(-iSoldiersDead, false);
		SetColonyMessageInfo("Plantation", "Mutiny", "Good", PIRATE, 0, false, true);

		AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", на плантации, которая принадлежит колонии " + PChar.ColonyBuilding.ColonyName + " вспыхнул мятеж. Гарнизон легко справился с мятежниками.", 5, 1);
	}
	else
	{
		Log_Info("Вести c плантации, принадлежащей колонии " + PChar.ColonyBuilding.ColonyName + "!");
		AddQuestRecord("MY_COLONY", "24");
		ChangePlantationSlaves(0, true);
		ChangePlantationSoldiers(0, true);

		int iExtractMinus = iRebels * (3 + rand(2));
		ChangePlantationExtract(-iExtractMinus, "Sugar", false);
		iExtractMinus = iRebels * (3 + rand(2));
		ChangePlantationExtract(-iExtractMinus, "Coffee", false);

		int iGoodMinus = iRebels * 50;
		ChangePlantationGoods(-iGoodMinus, "Food", false);
		iGoodMinus = iRebels * 25;
		ChangePlantationGoods(-iGoodMinus, "Medicament", false);
		SetColonyMessageInfo("Plantation", "Mutiny", "", PIRATE, 0, false, true);

		AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", на плантации, которая принадлежит колонии " + PChar.ColonyBuilding.ColonyName + " вспыхнул мятеж. Казалось бы, гарнизон легко справится с мятежниками, но не тут то было! Гарнизон, охранявший плантацию, умудрился проиграть в этом бою, а бунтари обратились в бегство.", 5, 1);
	}

	// Выключаем блокировку всех нападений -->
	PChar.ColonyBuilding.EventBlock = false;
	// Выключаем блокировку всех нападений <--
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// OTHER
/////////////////////////////////////////////////////////////////////////////////////////////////
void ChangePlantationSlaves(int iQty, bool bSet)
{
	if(bSet)
	{
		PChar.Plantation.Slaves.Quantity = iQty;
	}
	else
	{
		PChar.Plantation.Slaves.Quantity = sti(PChar.Plantation.Slaves.Quantity) + iQty;
	}

	int iMax = sti(PChar.Plantation.Slaves.MaxQuantity);
	if(sti(PChar.Plantation.Slaves.Quantity) > iMax) { PChar.Plantation.Slaves.Quantity = iMax; }
	if(sti(PChar.Plantation.Slaves.Quantity) < 0) { PChar.Plantation.Slaves.Quantity = 0; }
}

void ChangePlantationExtract(int iQty, string sType, bool bSet)
{
	if(bSet)
	{
		PChar.Plantation.(sType).Quantity = iQty;
	}
	else
	{
		PChar.Plantation.(sType).Quantity = sti(PChar.Plantation.(sType).Quantity) + iQty;
	}

	int iMax = sti(PChar.Plantation.(sType).MaxQuantity);
	if(sti(PChar.Plantation.(sType).Quantity) > iMax) { PChar.Plantation.(sType).Quantity = iMax; }
	if(sti(PChar.Plantation.(sType).Quantity) < 0) { PChar.Plantation.(sType).Quantity = 0; }
}

void ChangePlantationSoldiers(int iQty, bool bSet)
{
	if(bSet)
	{
		PChar.Plantation.Guardians.Quantity = iQty;
	}
	else
	{
		PChar.Plantation.Guardians.Quantity = sti(PChar.Plantation.Guardians.Quantity) + iQty;
	}

	int iMax = sti(PChar.Plantation.Guardians.MaxQuantity);
	if(sti(PChar.Plantation.Guardians.Quantity) > iMax) { PChar.Plantation.Guardians.Quantity = iMax; }
	if(sti(PChar.Plantation.Guardians.Quantity) < 0) { PChar.Plantation.Guardians.Quantity = 0; }
}

void ChangePlantationGoods(int iQty, string sType, bool bSet)
{
	if(bSet)
	{
		PChar.Plantation.(sType).Quantity = iQty;
	}
	else
	{
		PChar.Plantation.(sType).Quantity = sti(PChar.Plantation.(sType).Quantity) + iQty;
	}

	int iMax = sti(PChar.Plantation.(sType).MaxQuantity);
	if(sti(PChar.Plantation.(sType).Quantity) > iMax) { PChar.Plantation.(sType).Quantity = iMax; }
	if(sti(PChar.Plantation.(sType).Quantity) < 0) { PChar.Plantation.(sType).Quantity = 0; }
}

int GetPlantationFoodDays()
{
	int iDays = 0;
	int iSlaves = sti(PChar.Plantation.Slaves.Quantity);
	int iSoldiers = sti(PChar.Plantation.Guardians.Quantity);
	int iDay = (iSlaves / PLANTATION_FOOD_DELIT) + (iSoldiers / PLANTATION_FOOD_DELIT);
	int iGood = sti(PChar.Plantation.Food.Quantity);

	if(iSlaves + iSoldiers <= 0) { return iGood; }
	if(iDay <= 0) { return iGood; }
	if(iGood <= 0) { return 0; }

	iDay *= 42;
	iDays = iGood / iDay;

	if(iDays < 0)
	{
		iDays = 0;
	}

	return iDays;
}

int GetPlantationMedicamentDays()
{
	int iDays = 0;
	int iSlaves = sti(PChar.Plantation.Slaves.Quantity);
	int iDay = iSlaves / PLANTATION_MEDICAMENT_DELIT;
	int iGood = sti(PChar.Plantation.Medicament.Quantity);

	if(iSlaves <= 0) { return iGood; }
	if(iGood <= 0) { return 0; }

	iDay *= 42;
	iDays = iGood / iDay;

	if(iDays < 0)
	{
		iDays = 0;
	}

	return iDays;
}

////////////////////////////////////////////////////////////////////////////////////////
// АВТО-СБЫТ
////////////////////////////////////////////////////////////////////////////////////////
void PlantationExtractGoodsAutoSell()
{
	bool bCan = sti(PChar.ColonyBuilding.Plantation.AutoSell);
	if(!bCan)
	{
		return;
	}

	if(PChar.ColonyBuilding.Store == false)
	{
		return;
	}

	/*if(PChar.Plantation.Size.Resize.BuildingTime == true)
	{
		return;
	}*/

	int iSellQty = sti(PChar.ColonyBuilding.Plantation.AutoSell.Qty);
	int iGoodQty = 0;
	int iCost = 0;
	int iCoff = 0;
	string sType = "Sugar";

	bool bSell = false;
	int iMoney = 0;
	for(int i = 0; i < 2; i++)
	{
		switch(i)
		{
			case 0: sType = "Sugar"; iCoff = GetCurrentGoodBaseCostForAutoSell(GOOD_SUGAR); break;
			case 1: sType = "Coffee"; iCoff = GetCurrentGoodBaseCostForAutoSell(GOOD_COFFEE); break;
		}

		if(sType == "Coffee" && sti(PChar.Plantation.Size) != 2)
		{
			continue;
		}

		iGoodQty = sti(PChar.Plantation.(sType).Quantity);
		if(iGoodQty <= 0)
		{
			continue;
		}

		if(iGoodQty > AUTO_SELL_PLANTATION_MAX)
		{
			iGoodQty = AUTO_SELL_PLANTATION_MAX;
		}

		if(iGoodQty > iSellQty)
		{
			iGoodQty = iSellQty;
		}


		iCost = iGoodQty * iCoff;
		ChangeColonyMoney(iCost, false);
		ChangePlantationGoods(-iGoodQty, sType, false);

		iMoney += iCost;

		bSell = true;
		if(!bSell) { PlayStereoSound("new_round"); }
		Log_Info("Товар ''" + XI_ConvertString(sType) + "'' в количестве " + iGoodQty + " был продан за " + iCost + " золотых.");

		/*AddQuestRecord("MY_COLONY", "36");
		AddQuestUserData("MY_COLONY", "sGood", XI_ConvertString(sType));
		AddQuestUserData("MY_COLONY", "sGoodQty", iGoodQty);
		AddQuestUserData("MY_COLONY", "sGoodCost", iCost);*/
	}

	if(bSell)
	{
		string sColonyName = PChar.ColonyBuilding.ColonyName;
		AddQuestRecord("MY_COLONY", "35");
		AddQuestUserData("MY_COLONY", "sColonyName", sColonyName);
		AddQuestUserData("MY_COLONY", "sMoney", iMoney);
	}
}
