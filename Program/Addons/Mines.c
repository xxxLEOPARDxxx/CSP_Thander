/* Рудники, их развитие и повседневные дела */
#define ORE_GOLD				2.7
#define ORE_SILVER 				3.9
#define ORE_IRON 				5.1

#define AUTO_SELL_MINES_MAX 			500
#define AUTO_SELL_GOLD 				250
#define AUTO_SELL_SILVER 			110
#define AUTO_SELL_IRON 				55

#define MINES_FOOD_DELIT			50
#define MINES_MEDICAMENT_DELIT			50

void InitMines()
{
	ref PChar = GetMainCharacter();
	PChar.ColonyBuilding.GoldMine = false;
	PChar.ColonyBuilding.SilverMine = false;
	PChar.ColonyBuilding.IronMine = false;

	PChar.Mines.MaxSlavesQuantity = 200;
	PChar.Mines.MaxGuardiansQuantity = 200;

	PChar.Mines.GoldMine = false;
	PChar.Mines.SilverMine = false;
	PChar.Mines.IronMine = false;

	PChar.Mines.Slaves.Epidemy = false;
	PChar.Mines.GoldQuantity = 0;
	PChar.Mines.SilverQuantity = 0;
	PChar.Mines.IronQuantity = 0;

	PChar.Mines.GoldQuantity.Max = 2500;
	PChar.Mines.SilverQuantity.Max = 5000;
	PChar.Mines.IronQuantity.Max = 7500;

	PChar.Mines.GuardiansQuantity = 0;
	PChar.Mines.HireGuardiansQuantity = 0;
	PChar.Mines.GuardiansCost = 200;
	PChar.Mines.SlavesQuantity = 0;
	PChar.Mines.FoodQuantity = 0;
	PChar.Mines.MedicamentQuantity = 0;
	PChar.Mines.FoodQuantity.Max = 5000;
	PChar.Mines.MedicamentQuantity.Max = 3000;
	PChar.Mines.Temp.GoldQuantity = 0;
	PChar.Mines.Temp.SilverQuantity = 0;
	PChar.Mines.Temp.IronQuantity = 0;
	PChar.Mines.Temp.GuardiansQuantity = 0;
	PChar.Mines.Temp.SlavesQuantity = 0;
	PChar.Mines.Temp.FoodQuantity = 0;
	PChar.Mines.Temp.MedicamentQuantity = 0;

	PChar.ColonyBuilding.GoldMine.Resize = false;
	PChar.ColonyBuilding.SilverMine.Resize = false;
	PChar.ColonyBuilding.IronMine.Resize = false;

	PChar.Mines.Commander = "";

	PChar.Mines.Defence = false;
	PChar.Mines.Defence.Block = false;
	PChar.Mines.Defence.Battle = false;
	PChar.Mines.Defence.DeadInTown = false;
	PChar.Mines.Defence.Type = "Mutiny";
}

void UptadeLivedInMines()
{
	AutoPurchaseColonyGoods("Mines");
	ColonyGuardingAutoCrewHire("Mines");
	MinesCheckSlavesEpidemy();
	MinesSlavesUptade();
	MinesOreUptade();
	MinesCheckAttack();
	MinesExtractGoodsAutoSell();
}

void MinesCheckSlavesEpidemy()
{
	if(rand(100) > 10)
	{
		return;
	}

	int iSlaves = sti(PChar.Mines.SlavesQuantity);
	int iMedicament = sti(PChar.Mines.MedicamentQuantity);

	if(iSlaves < 10)
	{
		return;
	}

	Log_InfoS("По вашим рудникам пронеслась эпидемия.");

	int iDead = 0;
	int iMedicamentNeed = 0;
	if(iMedicament >= iSlaves)
	{
		iDead = rand(10) + 10;
		iMedicamentNeed = iSlaves - iDead;

		ChangeMinesMainGoods(-iMedicamentNeed, "Medicament", false);
		ChangeMinesSlaves(-iDead, false);

		Log_Info("Благодаря имеющимся медикаментам количество погибших рабов удалось существенно сократить. Количество погибших рабов: " + iDead);
	}
	else
	{
		iDead = iSlaves - iMedicament;
		if(iDead) { iDead = 0; }

		if(iDead > 0)
		{
			ChangeMinesMainGoods(iDead, "Medicament", false);
			ChangeMinesSlaves(iDead, false);
			Log_Info("Количество погибших рабов: " + iDead);
		}
	}
}

void MinesSlavesUptade()
{
	MinesFoodUptade();
	MinesMedicamentUptade();
}

void MinesFoodUptade()
{
	int iDead = 0;
	int iSlaves = sti(PChar.Mines.SlavesQuantity);

	if(iSlaves < 1) { return; }

	float fCoff = 0.0;
	int iFoodDiff = iSlaves / MINES_FOOD_DELIT;
	if(iFoodDiff < 1)
	{
		iFoodDiff = 1;
	}

	int iFood = sti(PChar.Mines.FoodQuantity);
	int iFoodNeed = iFoodDiff * 14;
	fCoff = iFoodDiff / iSlaves;

	if(iFood >= iFoodNeed)
	{
		ChangeMinesMainGoods(-iFoodNeed, "Food", false);
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

		ChangeMinesMainGoods(-iFoodNeed, "Food", false);
		ChangeMinesSlaves(-iDead, false);

		Log_InfoS("На ваших рудниках закончился провиант. От голода умерло рабов: " + iDead + ".");
	}

	int iSoldiers = sti(PChar.Mines.GuardiansQuantity);
	if(iSoldiers < 1) { return; }

	fCoff = 0.0;
	iFoodDiff = iSoldiers / MINES_FOOD_DELIT;
	if(iFoodDiff < 1)
	{
		iFoodDiff = 1;
	}

	iFood = sti(PChar.Mines.FoodQuantity);
	iFoodNeed = iFoodDiff * 14;
	fCoff = iFoodDiff / iSoldiers;

	if(iFood >= iFoodNeed)
	{
		ChangeMinesMainGoods(-iFoodNeed, "Food", false);
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

		ChangeMinesMainGoods(0, "Food", true);
		ChangeMinesSoldiers(-iDead, false);

		Log_InfoS("На ваших рудниках закончился провиант. От голода умерло надсмотрщиков: " + iDead + ".");
	}
}

void MinesMedicamentUptade()
{
	int iDead = 0;
	int iSlaves = sti(PChar.Mines.SlavesQuantity);

	if(iSlaves < 1) { return; }

	int iMedicamentDiff = iSlaves / MINES_MEDICAMENT_DELIT;
	if(iMedicamentDiff < 1)
	{
		iMedicamentDiff = 1;
	}

	float fCoff = 0.0;
	int iMedicament = sti(PChar.Mines.MedicamentQuantity);
	int iMedicamentNeed = iMedicamentDiff * 14;
	fCoff = iMedicamentDiff / iSlaves;

	if(iMedicament >= iMedicamentNeed)
	{
		ChangeMinesMainGoods(-iMedicamentNeed, "Medicament", false);
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

		ChangeMinesMainGoods(0, "Medicament", true);
		ChangeMinesSlaves(-iDead, false);

		Log_InfoS("На ваших рудниках закончились медикаменты. От болезней умерло рабов: " + iDead + ".");
	}
}

void MinesOreUptade()
{
	if(PChar.Mines.Commander == "")
	{
		Log_InfoS("Ваши рудники не имеют управляющего. Добыча не производится.");
		return;
	}

	int iSlaves = sti(PChar.Mines.SlavesQuantity);

	if(iSlaves < 1)
	{
		return;
	}

	iSlaves = sti(PChar.Mines.SlavesQuantity) / 10;

	float c = 0.0;
	int iQty = 0;
	string sType = "";
	string sMine = "";
	string sText = "";

	for(int i=0; i < 3; i++)
	{
		switch(i)
		{
			case 0: sType = "Gold"; c = ORE_GOLD; sText = "золотой"; break;
			case 1: sType = "Silver"; c = ORE_SILVER; sText = "серебрянной"; break;
			case 2: sType = "Iron"; c = ORE_IRON; sText = "железной"; break;
		}

		sMine = sType + "Mine";
		if(PChar.Mines.(sMine) == false)
		{
			continue;
		}

		if(PChar.ColonyBuilding.(sMine).Resize.BuildingTime == true)
		{
			Log_InfoS("В связи с расширением рудника, добыча " + sText + " руды приостановлена.");
			continue;
		}

		iQty = iSlaves * c;
		ChangeMinesOre(iQty, sType, false);
	}
}

////////////////////////////////////////////////////////////////////////////////////////
// АТАКИ И МЯТЕЖИ
////////////////////////////////////////////////////////////////////////////////////////
void MinesCheckAttack()
{
	bool bDisable = GetDisableAllColonyEvent();
	if(PChar.Mines.Defence.Block == true || bDisable)
	{
		Log_TestInfo("Нападения на рудники не будет, т.к. стоит запрет.");
		return;
	}

	int iRand = rand(10);
	if(iRand < 3)
	{
		return;
	}

	if(iRand >= 3 && iRand < 8)
	{
		GenerateMinesLandAttack();
		return;
	}
	else
	{
		GenerateMinesMutiny();
		return;
	}

	Log_TestInfo("Нападения на рудники не будет, т.к. повезло.");
}

// МЯТЕЖ
void GenerateMinesMutiny()
{
	Log_TestInfo("Генерируем мятеж на рудниках.");

	int iSlaves = sti(PChar.Mines.SlavesQuantity);
	int iGuardians = sti(PChar.Mines.GuardiansQuantity);

	if(iSlaves < 1)	{ iSlaves = 1; }
	if(iGuardians < 1) { iGuardians = 1; }

	if(iSlaves < 50)
	{
		Log_TestInfo("Мятежа на рудниках не будет, т.к. рабов слишком мало.");
		return;
	}

	int iDifference = iGuardians / iSlaves;
	if(iDifference >= 2 || rand(4) > 2)
	{
		Log_TestInfo("Мятежа на рудниках не будет, т.к. рабов слишком мало по отношению к охране.");
		return;
	}

	// Включаем блокировку всех нападений -->
	PChar.ColonyBuilding.EventBlock = true;
	// Включаем блокировку всех нападений <--

	PChar.Mines.Defence = true;
	PChar.Mines.Defence.Block = true;
	PChar.Mines.Defence.Type = "Mutiny";

	int iRebels = iSlaves / 20;

	if(iRebels < 2) iRebels = 2;
	if(iRebels > 20) iRebels = 20;

	ChangeMinesSlaves(-(iRebels*10), false);

	int iSoldiersQuantity = iGuardians / 25;

	PChar.Mines.Defence.Nation = PIRATE;
	PChar.Mines.Defence.EnemyQuantity = iRebels;

	if(iSoldiersQuantity < 1)
	{
		InstantColonyDefendLoose("Mines", "Mutiny");
		return;
	}

	if(iSoldiersQuantity < 2) iSoldiersQuantity = 2;
	if(iSoldiersQuantity > 20) iSoldiersQuantity = 20;

	PChar.Mines.Defence.Soldiers = iSoldiersQuantity;
	PChar.Mines.Defence.Soldiers.Delete = rand(1) + 4;

	int iRandMinus = 3;
	if(iRebels > iSoldiersQuantity)
	{
		iRandMinus -= (iRebels - iSoldiersQuantity);
	}
	else
	{
		iRandMinus += (iSoldiersQuantity - iRebels);
	}

	if(iRandMinus < -6)
	{
		InstantColonyDefendLoose("Mines", "Mutiny");
		return;
	}

	int iRand = iRandMinus - rand(4);

	int iEnd = 0;
	if(iRand > 0) { iEnd = 1; }else{ iEnd = 0; }

	PChar.Mines.Defence.End = iEnd;

	int iTime = 4 + rand(10) + iRandMinus;
	//if(iTime < 8) { iTime = 8; }
	//if(iTime > 30) { iTime = 30; }

	string sClearQuest = "ClearMutinyMines_" + rand(1000000);
	PChar.Mines.ClearQuest = sClearQuest;

	PChar.quest.(sClearQuest).win_condition.l1 = "Timer";
	PChar.quest.(sClearQuest).win_condition.l1.date.day = GetAddingDataDay(0, 0, iTime);
	PChar.quest.(sClearQuest).win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTime);
	PChar.quest.(sClearQuest).win_condition.l1.date.year = GetAddingDataYear(0, 0, iTime);
	PChar.quest.(sClearQuest).win_condition.l1.date.hour = 12;
	PChar.quest.(sClearQuest).function = "ClearMutinyMines";

	Log_Info("Вести с рудников, принадлежащих колонии " + PChar.ColonyBuilding.ColonyName + "!");

	string sTime = FindRussianDaysString(iTime);

	AddQuestRecord("MY_COLONY", "19");
	AddQuestUserData("MY_COLONY", "sMutinyTime", sTime);

	string sBattleQuest = "BattleMutinyMines_" + rand(1000000);
	PChar.Mines.BattleQuest = sBattleQuest;

	PChar.quest.(sBattleQuest).win_condition.l1 = "location";
	PChar.quest.(sBattleQuest).win_condition.l1.location = "Caiman_Mines";
	PChar.quest.(sBattleQuest).function = "BattleMutinyMines";

	SetColonyMessageInfo("Mines", "Mutiny", "", PIRATE, iTime, true, true);
}

void BattleMutinyMines(string _tmp)
{
	string sClearQuest = PChar.Mines.ClearQuest;
	PChar.quest.(sClearQuest).over = "yes";

	chrDisableReloadToLocation = true;
	bDisableFastReload = true;
	LAi_grp_alarmactive = true;
	InterfaceStates.Buttons.Save.enable = false;
	PChar.Mines.Defence.Battle = true;

	int i = 0;
	int iSoldiers = sti(PChar.Mines.Defence.Soldiers);
	int iRebels = sti(PChar.Mines.Defence.EnemyQuantity);
	ref chr;

	string sModel = "";
	string sLocator = "";

	for(i=1; i <= iRebels; i++)
	{
		sModel = "Slave" + (rand(3)+1);
		sLocator = "aloc" + i;

		chr = GetCharacter(NPC_GeneratePhantomCharacter("officer_1", PIRATE, 1, 0));
		chr.rank = GetRank(PChar, MOD_SKILL_ENEMY_RATE) + 2;
		SetFantomParamFromRank(chr, sti(chr.rank), true);
		chr.id = "My Mines Mutiny Rebel " + i;
		chr.model = sModel;
		chr.model.animation = "man";
		chr.NotRemoved = true;
		SetNewModelToChar(chr);
    		FaceMaker(chr);
		LAi_NoRebirthEnable(chr);
		LAi_SetWarriorType(chr);
		LAi_group_MoveCharacter(chr, "EnemyFight");
		ChangeCharacterAddressGroup(chr, PChar.location, "rld", sLocator);
	}

	string sAni = "man";

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
		chr.rank = GetRank(PChar, MOD_SKILL_ENEMY_RATE) + 5;
		SetFantomParamFromRank(chr, sti(chr.rank), true);
		chr.id = "My Mines Mutiny Defender " + i;
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
		rbl = "My Mines Mutiny Rebel " + i;
		PChar.quest.BattleMutinyMinesWinner.win_condition.(cnd) = "NPC_Death";
		PChar.quest.BattleMutinyMinesWinner.win_condition.(cnd).character = rbl;
	}

	PChar.quest.BattleMutinyMinesWinner.function = "BattleMutinyMinesWinner";

	ref loc = PCharLoc();
	DeleteAllFantomCharactersFromLocation(loc);

	SetDeadmansToLocation(&Locations[FindLocation(PChar.location)], "pirate");
}

void BattleMutinyMinesWinner(string _tmp)
{
	InterfaceStates.Buttons.Save.enable = true;
	chrDisableReloadToLocation = false;
	bDisableFastReload = false;
	LAi_grp_alarmactive = false;

	LAi_LockFightMode(PChar, false);
        LAi_SetFightMode(PChar, false);

	AddQuestRecord("MY_COLONY", "2");

	int iSoldiers = sti(PChar.Mines.Defence.Soldiers);
	int iDead = 0;

	string sDefender = "";
	for(int i=1; i<=iSoldiers; i++)
	{
		sDefender = "My Mines Mutiny Defender " + i;
		if(LAi_IsDead(CharacterFromID(sDefender)))
		{
			iDead++;
		}
	}

	int iSoldiersDead = iDead * 25;
	ChangeMinesSoldiers(-iSoldiersDead, false);

	PChar.Mines.Defence = false;
	PChar.Mines.Defence.Battle = false;
	PChar.Mines.Defence.Type = "";

	SetTimerCondition("MinesUptade5", 0, 0, 30, false);

	// Выключаем блокировку всех нападений -->
	PChar.ColonyBuilding.EventBlock = false;
	// Выключаем блокировку всех нападений <--

	AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", на рудниках, что принадлежат колонии " + PChar.ColonyBuilding.ColonyName + " вспыхнул мятеж. Если бы не сам владелец колонии, то ещё неизвестно, смог бы гарнизон справится с мятежниками.", 5, 1);
}

void ClearMutinyMines(string qName)
{
	string sBattleQuest = PChar.Mines.BattleQuest;
	PChar.quest.(sBattleQuest).over = "yes";

	PChar.Mines.Defence = false;
	PChar.Mines.Defence.Type = "";
	PChar.Mines.Defence.DeadInTown = true;
	PChar.Mines.Defence.Battle = false;

	SetTimerCondition("MinesNotSetDead", 0, 0, 6, false);
	SetTimerCondition("MinesUptade5", 0, 0, 40, false);

	int iEnd = sti(PChar.Mines.Defence.End);

	int iSoldiers = sti(PChar.Mines.Defence.Soldiers);
	if(iSoldiers > 0)
	{
		iSoldiers /= sti(PChar.Mines.Defence.Soldiers.Delete);
	}
	int iSoldiersDead = iSoldiers * 25;

	int iRebels = sti(PChar.Mines.Defence.EnemyQuantity);

	if(iEnd == 1)
	{
		Log_Info("Вести с рудников, принадлежащих колонии " + PChar.ColonyBuilding.ColonyName + "!");
		AddQuestRecord("MY_COLONY", "2");
		ChangeMinesSoldiers(-iSoldiersDead, false);
		SetColonyMessageInfo("Mines", "Mutiny", "Good", PIRATE, 0, false, true);

		AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", на рудниках, что принадлежат колонии " + PChar.ColonyBuilding.ColonyName + " вспыхнул мятеж. Но тамошний гарнизон справился с мятежниками.", 5, 1);
	}
	else
	{
		Log_Info("Вести с рудников, принадлежащих колонии " + PChar.ColonyBuilding.ColonyName + "!");
		AddQuestRecord("MY_COLONY", "18");
		ChangeMinesSlaves(0, true);
		ChangeMinesSoldiers(0, true);

		int iOreMinus = iRebels * (3 + rand(2));
		ChangeMinesOre(-iOreMinus, "Gold", false);
		iOreMinus = iRebels * (3 + rand(2));
		ChangeMinesOre(-iOreMinus, "Silver", false);
		iOreMinus = iRebels * (3 + rand(2));
		ChangeMinesOre(-iOreMinus, "Iron", false);

		int iGoodMinus = iRebels * 50;
		ChangeMinesMainGoods(-iGoodMinus, "Food", false);
		iGoodMinus = iRebels * 25;
		ChangeMinesMainGoods(-iGoodMinus, "Medicament", false);
		SetColonyMessageInfo("Mines", "Mutiny", "", PIRATE, 0, false, true);

		AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", на рудниках, что принадлежат колонии " + PChar.ColonyBuilding.ColonyName + " вспыхнул мятеж. И надо сказать, закончился печально для тамошнего гарнизона - мятежники смогли прорваться и обратились в бегство.", 5, 1);
	}

	// Выключаем блокировку всех нападений -->
	PChar.ColonyBuilding.EventBlock = false;
	// Выключаем блокировку всех нападений <--
}

// ВТОРОЙ ВАРИАНТ - НАПАДЕНИЕ С СУШИ
void GenerateMinesLandAttack()
{
	if(rand(100) < 10)
	{
		Log_TestInfo("Нападения с суши не будет, так как повезло.");
		return;
	}

	if(PChar.ColonyBuilding.Fort == true && rand(100) < 30)
	{
		Log_TestInfo("Нападения с суши не будет, так как охранная база отпугнула вражину.");
		return;
	}

	// Включаем блокировку всех нападений -->
	PChar.ColonyBuilding.EventBlock = true;
	// Включаем блокировку всех нападений <--

	int iBaseNation = GetBaseHeroNation();
	int iNation = FindEnemyNation2Nation(iBaseNation); //FindEnemyNation2Character(nMainCharacterIndex);
	if(iNation == -1)
	{
		iNation = PIRATE;
	}

	PChar.Mines.Defence.Nation = iNation;

	PChar.Mines.Defence = true;
	PChar.Mines.Defence.Block = true;
	PChar.Mines.Defence.Type = "BattleLand";

	int iGuardians = sti(PChar.Mines.GuardiansQuantity);
	int iSoldiersQuantity = iGuardians / 20;
	int iEnemy = 7 + rand(4) + rand(6) + rand(3) + 3;

	if(iEnemy < 2) iEnemy = 2;
	if(iEnemy > 20) iEnemy = 20;

	Log_TestInfo("Команда противника: " + iEnemy);

	int iOreMinus = iEnemy * (20 + rand(10));
	int iGoldMinus = iOreMinus * ORE_GOLD;
	int iSilverMinus = iOreMinus * ORE_SILVER;
	int iIronMinus = iOreMinus * ORE_IRON;
	int iSlavesMinus = sti(PChar.Mines.SlavesQuantity) / 2 + rand(10);

	if(iGoldMinus > sti(PChar.Mines.GoldQuantity)) { iGoldMinus = sti(PChar.Mines.GoldQuantity); }
	if(iSilverMinus > sti(PChar.Mines.SilverQuantity)) { iSilverMinus = sti(PChar.Mines.SilverQuantity); }
	if(iIronMinus > sti(PChar.Mines.IronQuantity)) { iIronMinus = sti(PChar.Mines.IronQuantity); }
	if(iSlavesMinus > sti(PChar.Mines.SlavesQuantity)) { iSlavesMinus = sti(PChar.Mines.SlavesQuantity); }

	PChar.Mines.Defence.Minus.Gold = iGoldMinus;
	PChar.Mines.Defence.Minus.Silver = iSilverMinus;
	PChar.Mines.Defence.Minus.Iron = iIronMinus;
	PChar.Mines.Defence.Minus.Slaves = iSlavesMinus;

	if(iSoldiersQuantity < 1)
	{
		InstantColonyDefendLoose("Mines", "BattleLand");
		return;
	}

	if(iSoldiersQuantity < 2) iSoldiersQuantity = 2;
	if(iSoldiersQuantity > 23) iSoldiersQuantity = 23;

	if(PChar.ColonyBuilding.Fort == true)
	{
		iEnemy -= (sti(PChar.ColonyBuilding.Soldiers) / 10) / iEnemy;

		if(iEnemy < 5)
		{
			iEnemy = 5;
		}

		Log_Info("Построена охранная база. Команда противника стала: " + iEnemy);
	}

	PChar.Mines.Defence.Soldiers = iSoldiersQuantity;
	PChar.Mines.Defence.Soldiers.Delete = rand(1) + 1;
	PChar.Mines.Defence.EnemyQuantity = iEnemy;

	int iRandMinus = -5;
	if(iEnemy > iSoldiersQuantity)
	{
		iRandMinus -= (iEnemy - iSoldiersQuantity);
	}
	else
	{
		iRandMinus += (iSoldiersQuantity - iEnemy);
	}

	if(iRandMinus < -10)
	{
		InstantColonyDefendLoose("Mines", "BattleLand");
		return;
	}

	int iRand = iRandMinus - rand(3);

	int iEnd = 0;
	if(iRand > 0) { iEnd = 1; }else{ iEnd = 0; }
	PChar.Mines.Defence.End = iEnd;

	int iTime = 4 + rand(10) + iRandMinus;
	//if(iTime < 7) { iTime = 7; }
	//if(iTime > 30) { iTime = 30; }

	string sClearQuest = "ClearLandDefenceMines_" + rand(1000000);
	PChar.Mines.ClearQuest = sClearQuest;

	PChar.quest.(sClearQuest).win_condition.l1 = "Timer";
	PChar.quest.(sClearQuest).win_condition.l1.date.day = GetAddingDataDay(0, 0, iTime);
	PChar.quest.(sClearQuest).win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTime);
	PChar.quest.(sClearQuest).win_condition.l1.date.year = GetAddingDataYear(0, 0, iTime);
	PChar.quest.(sClearQuest).win_condition.l1.date.hour = 12;
	PChar.quest.(sClearQuest).function = "ClearLandDefenceMines";

	string sTime = FindRussianDaysString(iTime);

	Log_Info("Вести с рудников, принадлежащих колонии " + PChar.ColonyBuilding.ColonyName + "!");
	AddQuestRecord("MY_COLONY", "20");
	AddQuestUserData("MY_COLONY", "sLandBattleTime", sTime);

	string sBattleQuest = "BattleLandDefenceMines_" + rand(1000000);
	PChar.Mines.BattleQuest = sBattleQuest;

	PChar.quest.(sBattleQuest).win_condition.l1 = "location";
	PChar.quest.(sBattleQuest).win_condition.l1.location = "Caiman_ExitMines";
	PChar.quest.(sBattleQuest).function = "BattleLandDefenceMines";

	SetColonyMessageInfo("Mines", "BattleLand", "", iNation, iTime, true, true);
}

void BattleLandDefenceMines(string _tmp)
{
	string sClearQuest = PChar.Mines.ClearQuest;
	PChar.quest.(sClearQuest).over = "yes";

	chrDisableReloadToLocation = true;
	bDisableFastReload = true;
	LAi_grp_alarmactive = true;
	InterfaceStates.Buttons.Save.enable = false;
	PChar.Mines.Defence.Battle = true;

	ChangeCharacterAddressGroup(PChar, PChar.location, "rld", "loc0");

	int i = 0;
	int iSoldiers = sti(PChar.Mines.Defence.Soldiers);
	int iEnemy = sti(PChar.Mines.Defence.EnemyQuantity);

	ref chr;

	string sModel = "";
	string sLocator = "";
	string sAni = "man";

	int iMusketeers = FightInColonyGetMusketeerQty(iEnemy);
	bool bMusketeer = false;

    	arrayNPCModelHow = 0;
	int iEnemyNation = sti(PChar.Mines.Defence.Nation);
	string sEnemyNation = NationShortName(iEnemyNation);
	for(i=1; i <= iEnemy; i++)
	{
		sAni = "man";

		bMusketeer = false;
		if(iEnemy - i < iMusketeers) { bMusketeer = true; }

		sLocator = "reload2_back";

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
		chr.id = "My Mines Land Defence Pirate " + i;
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

		if(PChar.ColonyBuilding.SoldiersType == "officer" || PChar.ColonyBuilding.SoldiersType == "pirate")
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
					sModel = "officer_" + (rand(63) + 1);
					if(bMusketeer) { sModel = "officer_" + (rand(63) + 1)+ "_mush"; sAni = "mushketer"; }
				}
			}
		}

		sLocator = "reload3";
		chr = GetCharacter(NPC_GeneratePhantomCharacter("officer_1", PIRATE, 1, 0));
		chr.rank = GetRank(PChar, MOD_SKILL_ENEMY_RATE) + 4;
		SetFantomParamFromRank(chr, sti(chr.rank), true);
		chr.id = "My Mines Land Defender " + i;
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

	string cnd, enm;
	for(i=1; i<=iEnemy; i++)
	{
		cnd = "l" + i;
		enm = "My Mines Land Defence Pirate " + i;
		PChar.quest.BattleLandDefenceMinesWinner.win_condition.(cnd) = "NPC_Death";
		PChar.quest.BattleLandDefenceMinesWinner.win_condition.(cnd).character = enm;
	}

	ref loc = PCharLoc();
	DeleteAllFantomCharactersFromLocation(loc);

	PChar.quest.BattleLandDefenceMinesWinner.function = "BattleLandDefenceMinesWinner";
}

void BattleLandDefenceMinesWinner(string _tmp)
{
	InterfaceStates.Buttons.Save.enable = true;
	chrDisableReloadToLocation = false;
	bDisableFastReload = false;
	LAi_grp_alarmactive = false;

	LAi_LockFightMode(PChar, false);
        LAi_SetFightMode(PChar, false);

	AddQuestRecord("MY_COLONY", "5");

	int iSoldiers = sti(PChar.Mines.Defence.Soldiers);
	int iDead = 0;

	string sDefender = "";
	for(int i=1; i<=iSoldiers; i++)
	{
		sDefender = "My Mines Land Defender " + i;
		if(LAi_IsDead(CharacterFromID(sDefender)))
		{
			iDead++;
		}
	}

	int iSoldiersDead = iDead * 20;
	ChangeMinesSoldiers(-iSoldiersDead, false);
	PChar.Mines.Defence = false;
	PChar.Mines.Defence.Battle = false;
	PChar.Mines.Defence.Type = "";

	SetTimerCondition("MinesUptade5", 0, 0, 40, false);

	// Выключаем блокировку всех нападений -->
	PChar.ColonyBuilding.EventBlock = false;
	// Выключаем блокировку всех нападений <--

	AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", на рудники, принадлежащие колонии " + PChar.ColonyBuilding.ColonyName + " напали. Помочь уничтожению врага прибыл сам владелец колонии!", 5, 1);
}

void ClearLandDefenceMines(string qName)
{
	int iEnd = sti(PChar.Mines.Defence.End);

	int iSoldiers = sti(PChar.Mines.Defence.Soldiers);
	if(iSoldiers > 0)
	{
		iSoldiers /= sti(PChar.Mines.Defence.Soldiers.Delete);
	}
	int iSoldiersDead = iSoldiers * 20;

	SetTimerCondition("MinesUptade5", 0, 0, 30, false);

	if(iEnd == 1)
	{
		Log_Info("Вести из колонии " + PChar.ColonyBuilding.ColonyName + "!");
		AddQuestRecord("MY_COLONY", "21");
		ChangeMinesSoldiers(-iSoldiersDead, false);
		SetColonyMessageInfo("Mines", "BattleLand", "Good", sti(PChar.Mines.Defence.Nation), 0, false, true);

		AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", на рудники, принадлежащие колонии " + PChar.ColonyBuilding.ColonyName + " напали. Но нападавшие ничего не смогли поделать с охранявшими рудники силами и пали в бою.", 5, 1);
	}
	else
	{
		Log_Info("Вести из колонии " + PChar.ColonyBuilding.ColonyName + "!");
		AddQuestRecord("MY_COLONY", "22");
		ChangeMinesSoldiers(0, true);
		ChangeMinesSlaves(0, true);
		PChar.Mines.Defence.DeadInTown = true;
		SetTimerCondition("MinesNotSetDead", 0, 0, 6, false);
		MinesLandDefenceOnMap();
		SetColonyMessageInfo("Mines", "BattleLand", "", sti(PChar.Mines.Defence.Nation), 0, false, true);

		AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", на рудники, принадлежащие колонии " + PChar.ColonyBuilding.ColonyName + " напали. Как оказалось - не зря. Гарнизон был в слишком ослабленном состоянии не смог ничего противопоставить нападавшим.", 5, 1);
	}

	string sBattleQuest = PChar.Mines.BattleQuest;
	PChar.quest.(sBattleQuest).over = "yes";

	PChar.Mines.Defence.Battle = false;
	PChar.Mines.Defence = false;
	PChar.Mines.Defence.Type = "";

	// Выключаем блокировку всех нападений -->
	PChar.ColonyBuilding.EventBlock = false;
	// Выключаем блокировку всех нападений <--
}

void MinesLandDefenceOnMap()
{
	ref  sld;
	int  i;

	string sCapId = "Follower0";
	string sGroup = "Sea_" + sCapId + "1";

	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);

	int iDifferent = GetCompanionQuantity(PChar) - 1;

	if(iDifferent < 1)
	{
		iDifferent = 1;
	}

	int iGold = sti(PChar.Mines.Defence.Minus.Gold);
	int iSilver = sti(PChar.Mines.Defence.Minus.Silver);
	int iIron = sti(PChar.Mines.Defence.Minus.Iron);
	int iSlaves = sti(PChar.Mines.Defence.Minus.Slaves);

	ChangeMinesOre(-iGold, "Gold", false);
	ChangeMinesOre(-iSilver, "Silver", false);
	ChangeMinesOre(-iIron, "Iron", false);
	ChangeMinesSlaves(-iSlaves, false);

	iGold = sti(PChar.Mines.Defence.Minus.Gold) / iDifferent;
	iSilver = sti(PChar.Mines.Defence.Minus.Silver) / iDifferent;
	iIron = sti(PChar.Mines.Defence.Minus.Iron) / iDifferent;
	iSlaves = sti(PChar.Mines.Defence.Minus.Slaves) / iDifferent;

	int iNation = sti(PChar.Mines.Defence.Nation);

	for (i = 1; i <= iDifferent; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "off_hol_2", "man", "man", 5, iNation, 12, true));
		SetShipHunter(sld);
		SetFantomParamHunter(sld);
		SetCaptanModelByEncType(sld, "war");
		sld.AlwaysEnemy = true;
		sld.DontRansackCaptain = true;
		sld.mapEnc.type = "war";
		sld.mapEnc.Name = "Джентльмены удачи";
		Group_AddCharacter(sGroup, sCapId + i);

		SetCharacterGoods(sld, GOOD_GOLD, iGold);
		SetCharacterGoods(sld, GOOD_SILVER, iSilver);
		SetCharacterGoods(sld, GOOD_IRON, iIron);
		SetCharacterGoods(sld, GOOD_SLAVES, iSlaves);
	}

	Group_SetGroupCommander(sGroup, sCapId+ "1");
	//Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	//Map_CreateWarrior("", sCapId + "1", 8);
	Map_CreateTrader("Shore17", "", sCapId + "1", 10);
}

////////////////////////////////////////////////////////////////////////////////////////
// MAIN MINES FUCNTIONS
////////////////////////////////////////////////////////////////////////////////////////
void ChangeMinesSlaves(int iQty, bool bSet)
{
	if(bSet)
	{
		PChar.Mines.SlavesQuantity = iQty;
	}
	else
	{
		PChar.Mines.SlavesQuantity = sti(PChar.Mines.SlavesQuantity) + iQty;
	}

	int iMax = sti(PChar.Mines.MaxSlavesQuantity);
	if(sti(PChar.Mines.SlavesQuantity) > iMax) { PChar.Mines.SlavesQuantity = iMax; }
	if(sti(PChar.Mines.SlavesQuantity) < 0) { PChar.Mines.SlavesQuantity = 0; }
}

void ChangeMinesOre(int iQty, string sType, bool bSet)
{
	string sOre = sType + "Quantity";

	if(bSet)
	{
		PChar.Mines.(sOre) = iQty;
	}
	else
	{
		PChar.Mines.(sOre) = sti(PChar.Mines.(sOre)) + iQty;
	}

	int iMax = sti(PChar.Mines.(sOre).Max);
	if(sti(PChar.Mines.(sOre)) > iMax) { PChar.Mines.(sOre) = iMax; }
	if(sti(PChar.Mines.(sOre)) < 0) { PChar.Mines.(sOre) = 0; }
}

void ChangeMinesSoldiers(int iQty, bool bSet)
{
	if(bSet)
	{
		PChar.Mines.GuardiansQuantity = iQty;
	}
	else
	{
		PChar.Mines.GuardiansQuantity = sti(PChar.Mines.GuardiansQuantity) + iQty;
	}

	int iMax = sti(PChar.Mines.MaxGuardiansQuantity);
	if(sti(PChar.Mines.GuardiansQuantity) > iMax) { PChar.Mines.GuardiansQuantity = iMax; }
	if(sti(PChar.Mines.GuardiansQuantity) < 0) { PChar.Mines.GuardiansQuantity = 0; }
}

void ChangeMinesMainGoods(int iQty, string sType, bool bSet)
{
	string sGood = sType + "Quantity";

	if(bSet)
	{
		PChar.Mines.(sGood) = iQty;
	}
	else
	{
		PChar.Mines.(sGood) = sti(PChar.Mines.(sGood)) + iQty;
	}

	int iMax = sti(PChar.Mines.(sGood).Max);
	if(sti(PChar.Mines.(sGood)) > iMax) { PChar.Mines.(sGood) = iMax; }
	if(sti(PChar.Mines.(sGood)) < 0) { PChar.Mines.(sGood) = 0; }
}

int GetMinesFoodDays()
{
	int iDays = 0;
	int iSlaves = sti(PChar.Mines.SlavesQuantity);
	int iSoldiers = sti(PChar.Mines.GuardiansQuantity);
	int iDay = (iSlaves / MINES_FOOD_DELIT) + (iSoldiers / MINES_FOOD_DELIT);
	int iGood = sti(PChar.Mines.FoodQuantity);

	if(iSlaves + iSoldiers <= 0) { return iGood; }
	if(iGood <= 0) { return 0; }
	if(iDay <= 0) { return iGood; }

	iDay *= 42;
	iDays = iGood / iDay;

	if(iDays < 0)
	{
		iDays = 0;
	}

	return iDays;
}

int GetMinesMedicamentDays()
{
	int iDays = 0;
	int iSlaves = sti(PChar.Mines.SlavesQuantity);
	int iDay = iSlaves / MINES_MEDICAMENT_DELIT;
	int iGood = sti(PChar.Mines.MedicamentQuantity);

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
void MinesExtractGoodsAutoSell()
{
	bool bCan = sti(PChar.ColonyBuilding.Mines.AutoSell);
	if(!bCan)
	{
		return;
	}

	if(PChar.ColonyBuilding.Store == false)
	{
		return;
	}

	int iSellQty = sti(PChar.ColonyBuilding.Mines.AutoSell.Qty);
	int iGoodQty = 0;
	int iCost = 0;
	int iCoff = 0;
	string sType = "Gold";

	bool bSell = false;
	string sMine = "GoldMine";

	int iMoney = 0;
	for(int i = 0; i < 3; i++)
	{
		switch(i)
		{
			case 0: sType = "Gold"; iCoff = GetCurrentGoodBaseCostForAutoSell(GOOD_GOLD); break;
			case 1: sType = "Silver"; iCoff = GetCurrentGoodBaseCostForAutoSell(GOOD_SILVER); break;
			case 2: sType = "Iron"; iCoff = GetCurrentGoodBaseCostForAutoSell(GOOD_IRON); break;
		}

		sMine = sType + "Mine";
		if(PChar.Mines.(sMine) == false)
		{
			continue;
		}

		/*if(PChar.ColonyBuilding.(sMine).Resize.BuildingTime == true)
		{
			continue;
		}*/

		sMine = sType + "Quantity";
		iGoodQty = sti(PChar.Mines.(sMine));

		if(iGoodQty <= 0)
		{
			continue;
		}

		if(iGoodQty > AUTO_SELL_MINES_MAX)
		{
			iGoodQty = AUTO_SELL_MINES_MAX;
		}

		if(iGoodQty > iSellQty)
		{
			iGoodQty = iSellQty;
		}

		if(!bSell) { PlayStereoSound("new_round"); }
		bSell = true;

		iCost = iGoodQty * iCoff;
		ChangeColonyMoney(iCost, false);
		ChangeMinesOre(-iGoodQty, sType, false);

		iMoney += iCost;
		Log_Info(XI_ConvertString(sType) + " в количестве " + iGoodQty + " было продано за " + iCost + " золотых.");

		/*AddQuestRecord("MY_COLONY", "34");
		AddQuestUserData("MY_COLONY", "sOre", XI_ConvertString(sType));
		AddQuestUserData("MY_COLONY", "sOreQty", iGoodQty);
		AddQuestUserData("MY_COLONY", "sOreCost", iCost);*/
	}

	if(bSell)
	{
		string sColonyName = PChar.ColonyBuilding.ColonyName;
		AddQuestRecord("MY_COLONY", "33");
		AddQuestUserData("MY_COLONY", "sColonyName", sColonyName);
		AddQuestUserData("MY_COLONY", "sMoney", iMoney);
	}
}
