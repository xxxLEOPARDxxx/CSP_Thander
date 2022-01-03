/////////////////////////////////////////////////////////////////////////////////////////////////////////
//Прочие функции
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void BS_SpawnEnemies(int iRnd, int iNation, string winFunction)
{
	ref chr;
	string sLoc, sLoc_2, relation;
	int i;

	relation = LAI_GROUP_PLAYER;
	sLoc = pchar.location;

	chrDisableReloadToLocation = true;
	PChar.GenQuestFort.FarLocator = false;

	Pchar.GenQuestFort.FarLocator = true;
	sLoc = LAi_FindNPCLocator("goto");
	sLoc_2 = LAi_FindNPCLocator("smugglers");
	for (i = 1; i < iRnd; i++)
	{
		chr = SetFantomDefenceForts("goto", sLoc, iNation, "BS_SpawnEnemies");

		chr.id = "pirate_" + i;
		FantomMakeCoolFighterWRankDepend(chr,sti(pchar.rank),25+rand(75),25+rand(75),50);
	}
	//натравим.
	LAi_group_SetHearRadius("BS_SpawnEnemies", 100.0);
	LAi_group_FightGroupsEx("BS_SpawnEnemies", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
	LAi_group_FightGroupsEx("BS_SpawnEnemies", relation, true, Pchar, -1, false, false);

	LAi_group_SetCheckFunction("BS_SpawnEnemies", winFunction);

	LAi_SetFightMode(pchar, true);
}

void BSRepairShip(ref chr)
{
	ProcessHullRepair(chr, 100.0);
	ProcessSailRepair(chr, 100.0);
	DeleteAttribute(chr, "ship.blots");
	DeleteAttribute(chr, "ship.sails");
	DeleteAttribute(chr, "ship.masts");
	Fantom_SetBalls(chr, "war");
	SetCharacterGoods(chr,GOOD_FOOD,1000);
}

void BS_ReplaceHostessWithMaks()
{
	sld = CharacterFromID("PortRoyal_hostess");
	sld.beforeGatriModel = sld.model;
	sld.model = "BS_Maks";
	sld.beforeGatriModelAnimation = sld.model.animation;
	sld.model.animation = "woman";
	sld.beforeGatriName = sld.name;
	sld.name = "Макс";
	sld.beforeGatriLastName = sld.lastname;
	sld.lastname = "";
	sld.beforeGatriGreeting = sld.greeting;
	//sld.greeting = "";
	sld.beforeGatriFileName = sld.Dialog.FileName;
	sld.beforeGatriCurrentNode = sld.Dialog.CurrentNode;
}

void BS_RestoreMaksHostess(string q)
{
	sld = CharacterFromID("PortRoyal_hostess");
	sld.model = sld.beforeGatriModel;
	sld.model.animation = sld.beforeGatriModelAnimation;
	sld.name = sld.beforeGatriName;
	sld.lastname = sld.beforeGatriLastName;
	sld.greeting = sld.beforeGatriGreeting;
	sld.Dialog.FileName = sld.beforeGatriFileName;
	sld.Dialog.CurrentNode = sld.beforeGatriCurrentNode;
}

void BS_ReplaceTraderWithGatri()
{
	sld = CharacterFromID("Pirates_trader");
	sld.beforeGatriModel = sld.model;
	sld.model = "BS_Gatry";
	sld.beforeGatriModelAnimation = sld.model.animation;
	sld.model.animation = "woman";
	sld.beforeGatriName = sld.name;
	sld.name = "Элеонора";
	sld.beforeGatriLastName = sld.lastname;
	sld.lastname = "Гатри";
	sld.beforeGatriGreeting = sld.greeting;
	sld.greeting = "Gr_officiant";
	sld.beforeGatriFileName = sld.Dialog.FileName;
	sld.beforeGatriCurrentNode = sld.Dialog.CurrentNode;
}

void BS_RestoreGatriTrader(string q)
{
	sld = CharacterFromID("Pirates_trader");
	sld.model = sld.beforeGatriModel;
	sld.model.animation = sld.beforeGatriModelAnimation;
	sld.name = sld.beforeGatriName;
	sld.lastname = sld.beforeGatriLastName;
	sld.greeting = sld.beforeGatriGreeting;
	sld.Dialog.FileName = sld.beforeGatriFileName;
	sld.Dialog.CurrentNode = sld.beforeGatriCurrentNode;
}

void BSRestoreWorldAlivePause()
{
	//bWorldAlivePause = true;
	pchar.BSFinish = true;
	Log_TestInfo("Линейка ЧП завершена.")
}

void GatriSpeech(string qName)
{
	sld = CharacterFromID("Gatri_temp");
	LAi_tmpl_SetDialog(sld, pchar, -1.0);
}

void GatriStoreSpeech(string qName)
{
	sld = CharacterFromID("Pirates_trader");
	LAi_tmpl_SetDialog(sld, pchar, -1.0);
}

void FlintSpeech(string qName)
{
	sld = CharacterFromID("Flint");
	LAi_tmpl_SetDialog(sld, pchar, -1.0);
}

void SilverSpeech(string qName)
{
	sld = CharacterFromID("BS_Silver");
	LAi_tmpl_SetDialog(sld, pchar, -1.0);
}
void MaksSpeech(string qName)
{
	sld = CharacterFromID("BS_Maks");
	LAi_tmpl_SetDialog(sld, pchar, -1.0);
}
void VeinSpeech(string qName)
{
	sld = CharacterFromID("BS_Vein");
	LAi_tmpl_SetDialog(sld, pchar, -1.0);
}
void BonySpeech(string qName)
{
	sld = CharacterFromID("BS_Bony");
	LAi_tmpl_SetDialog(sld, pchar, -1.0);
}
void RakhamSpeech(string qName)
{
	sld = CharacterFromID("BS_Rakham");
	LAi_tmpl_SetDialog(sld, pchar, -1.0);
}

void Gatri_upstairs(string qName)
{
	DoQuestFunctionDelay("GatriSpeech", 0);
}

void Flint_upstairs(string qName)
{
	DoQuestFunctionDelay("FlintSpeech", 0);
}

void Silver_Downstairs(string qName)
{
	DoQuestFunctionDelay("SilverSpeech", 0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//Прочие функции
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Черные паруса на горизонте
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void BSOnTheHorizon_start(string qName)
{
	chrDisableReloadToLocation = true;
	sld = GetCharacter(NPC_GenerateCharacter("Gatri_temp", "BS_Gatry", "woman", "woman", 1, PIRATE, -1, true));
	sld.dialog.filename = "Quest\BlackSails\ChernyeParusaNaGorizonte.c";
	sld.dialog.currentnode = "BS_CPNG_3";
	ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload3_back");
	LAi_SetStayTypeNoGroup(sld);
	LAi_SetImmortal(sld, true);
	sld.talker = 10;
	sld.name = "Элеонора";
	sld.lastname = "Гатри";

	for (i = 1; i < 4; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Gatri_temp"+i, "head_pir", "man", "man", 1, PIRATE, -1, true));
		if (i == 1) sld.model = "huber_fra";
		if (i == 2) sld.model = "mansfield";
		ChangeCharacterAddressGroup(sld, PChar.location, "officers", "reload3_"+i);
		LAi_SetImmortal(sld, true);
	}
}

void BSOnTheHorizon_Flint();
{
	sld = GetCharacter(NPC_GenerateCharacter("Flint", "BS_Flint_0", "man", "man", 999, PIRATE, -1, true));
	FantomMakeCoolestSailor(sld, SHIP_NL_PinnaceofWar47, "Морж", CANNON_TYPE_CANNON_LBS24, 100, 100, 100);
	FantomMakeCoolFighter(sld, 100, 100, 100, "blade43", "pistol4", 1000);
	SetSPECIAL(sld, 10, 10, 10, 10, 10, 10, 10);
	sld.name = "Джеймс";
	sld.lastname = "Флинт";
	string sGroup = "Flint_Group";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "капитан Флинт";
	string sColony = "LaVega";
	pchar.questTemp.Flint.City = "PuertoPrincipe";
	int daysQty = 3;
	SetTimerCondition("Flint_SetCity", 0, 0, daysQty, true);
	Map_CreateTrader(sColony, pchar.questTemp.Flint.City, sld.id, daysQty);
	sld.dialog.filename = "Quest\BlackSails\ChernyeParusaNaGorizonte.c";
	sld.DeckDialogNode = "BS_CPNG_15";
	LAi_SetImmortal(sld, true);
	sld.Abordage.Enable = false;
	Log_TestInfo("Флинт выходит из " + sColony + "  в " + pchar.questTemp.Flint.City+", дней до прибытия: "+daysQty);
}

void MeetFlintCrew(string qName)
{
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("Flint");
	ChangeCharacterAddressGroup(sld, PChar.location, "quest", "quest1");
	LAi_SetStayTypeNoGroup(sld);
	LAi_SetImmortal(sld, true);
	sld.talker = 10;
	sld.dialog.currentnode = "BS_CPNG_18";

	sld = GetCharacter(NPC_GenerateCharacter("BS_Silver", "BS_Silver", "man", "man", 999, PIRATE, -1, true));
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
	sld.name = "Джон";
	sld.lastname = "Сильвер";
	LAi_SetImmortal(sld, true);
	sld = GetCharacter(NPC_GenerateCharacter("BS_Billy", "BS_Billy", "man", "man", 999, PIRATE, -1, true));
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto6");
	sld.name = "Билли";
	sld.lastname = "Бонс";
	LAi_SetImmortal(sld, true);
}

void BSOnTheHorizon_End(string qName)
{
	AddQuestRecord("BSOnTheHorizon", "5");
	CloseQuestHeader("BSOnTheHorizon");

	SetFunctionExitFromLocationCondition("BSCourtlyPassions_begin_again", pchar.location, true);

	sld = CharacterFromID("Flint");
	LAi_SetImmortal(sld, false);
	pchar.quest.BSCourtlyPassions_DontStart.win_condition.c1 = "NPC_Death";
	pchar.quest.BSCourtlyPassions_DontStart.win_condition.c1.character ="Flint";
	PChar.quest.BSCourtlyPassions_DontStart.function = "BSCourtlyPassions_DontStart";

	pchar.BSCPFlint_talk = true;
}
void BSOnTheHorizon_SeaBattle()
{
	pchar.ContraInterruptWaiting = true;

	Group_FindOrCreateGroup("BSOnTheHorizon_SeaBattle");
	Group_SetType("BSOnTheHorizon_SeaBattle", "pirate");
	for (i = 1; i < 7; i++)
	{

		sld = GetCharacter(NPC_GenerateCharacter("BSOnTheHorizon_enemyfleet"+i, "off_eng_"+(rand(1)+1), "man", "man", 999, ENGLAND, 3, true));
		if (i == 1)
		{
			sld.Ship.Type = GenerateShipExt(SHIP_FASTFRIGATE, true, sld);
			sld.Ship.Name = "Денуво";
			sld.Name = "Денуво";
			sld.Lastname = "Антитампер";
		}
		if (i == 2) sld.Ship.Type = GenerateShipExt(SHIP_FR_ESSEX, true, sld);
		if (i == 3) sld.Ship.Type = GenerateShipExt(SHIP_FEARLESS, true, sld);
		if (i == 4) sld.Ship.Type = GenerateShipExt(SHIP_ALEXIS, true, sld);
		if (i == 5) sld.Ship.Type = GenerateShipExt(SHIP_NL_FWZP, true, sld);
		if (i == 6) sld.Ship.Type = GenerateShipExt(SHIP_OXFORD, true, sld);
		sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;

		sld.ship.Crew.Morale = 100;
		ChangeCrewExp(sld, "Sailors", 50);
		ChangeCrewExp(sld, "Cannoners", 50);
		ChangeCrewExp(sld, "Soldiers", 50);

		TakeNItems(sld, "Food5", 5);
		TakeNItems(sld, "potion2", 5);

		SetCharacterPerk(sld, "MusketsShoot");
		SetCharacterPerk(sld, "CannonProfessional");

		Fantom_SetBalls(sld, "war");

		sld.AlwaysEnemy = true;
		sld.DontRansackCaptain = true;
		sld.AlwaysSandbankManeuver = true;
		Group_AddCharacter("BSOnTheHorizon_SeaBattle", sld.id);
		if (i == 1) Group_SetGroupCommander("BSOnTheHorizon_SeaBattle", sld.id);
		SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);

		//Group_SetPursuitGroup("BSOnTheHorizon_SeaBattle", PLAYER_GROUP);
		Group_SetTaskAttack("BSOnTheHorizon_SeaBattle", PLAYER_GROUP);
		Group_LockTask("BSOnTheHorizon_SeaBattle");

		Group_SetAddress("BSOnTheHorizon_SeaBattle", "Bermudes", "Quest_ships", "quest_ship_0");
	}
	sld = CharacterFromID("Flint");
	LAi_SetImmortal(sld, false);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- Черные паруса на горизонте --     конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Куртуазные страсти
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void BSCourtlyPassions_DontStart(string qName)
{
	DeleteAttribute(pchar, "BSCPFlint_talk");
	BSRestoreWorldAlivePause();
}

void BSCourtlyPassions_begin(string qName)
{
	ref sld, chr;

	if(pchar.location == pchar.location.from_sea || HasSubStr(pchar.location,"_town" || HasSubStr(pchar.location,"shore")))
	{
		if (CheckAttribute(pchar, "BSCPFlint_talk") && !bSeaActive)
		{
			sld = CharacterFromID("Flint");
			if (!CheckAttribute(sld, "curtown") || sld.curtown != pchar.location)
			{
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
				chrDisableReloadToLocation = true;
				LAi_SetActorType(sld);
				sld.dialog.filename = "Quest\BlackSails\Kurtuaznye_Strasti.c";
				sld.dialog.currentnode = "BS_KS_1";
				LAi_ActorDialog(sld, pchar, "", -1, 0);
				sld.curtown = pchar.location;
				LAi_SetImmortal(sld, true);

				chr = GetCharacter(NPC_GenerateCharacter("BS_Silver", "BS_Silver", "man", "man", 999, PIRATE, -1, true));
				ChangeCharacterAddressGroup(chr, PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
				chr.name = "Джон";
				chr.lastname = "Сильвер";
				LAi_SetActorType(chr);
				LAi_ActorFollow(chr, sld, "", -1);
				LAi_SetImmortal(chr, true);
			}
		}
	}
	else
	{
		SetFunctionExitFromLocationCondition("BSCourtlyPassions_begin_again", pchar.location, true);
	}
}

void BSCourtlyPassions_begin_again(string _quest)
{
	if(CheckAttribute(pchar, "BSCPFlint_talk"))
	{
		pchar.quest.BSCourtlyPassions_begin.win_condition.l1 = "ExitFromLocation";
		pchar.quest.BSCourtlyPassions_begin.function = "BSCourtlyPassions_begin";
	}
}

void BSCourtlyPassions_sailor_begin(string qName)
{
	if(pchar.location == "LeFransua_port" || pchar.location == "FortFrance_town" ||  pchar.location == "Shore38" ||   pchar.location == "Shore39")
	{
		BSCourtlyPassions_sailor();
	}
	else
	{
		SetFunctionExitFromLocationCondition("BSCourtlyPassions_sailor_begin_again", pchar.location, true);
	}
}

ref BSTutorialSailor();
{
	sld = GetCharacter(NPC_GenerateCharacter("Sailor_1", "Pirate_9", "man", "man", 1, PIRATE, 0, false));
	sld.name 	= "Сандро";
	sld.lastname 	= "Торн";
	sld.greeting = "Teacher_pirat";
	return sld;
}

void BSCourtlyPassions_sailor()
{
	ref sld, chr;

	if (CheckAttribute(pchar, "BSCPSailor_talk") && !bSeaActive)
	{
		chr = CharacterFromID("Flint");
		if (!CheckAttribute(chr, "curtown") || chr.curtown != pchar.location)
		{
			chrDisableReloadToLocation = true;
			sld = BSTutorialSailor();
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
			chrDisableReloadToLocation = true;
			LAi_SetActorType(sld);
			sld.dialog.filename = "Quest\BlackSails\Kurtuaznye_Strasti.c";
			sld.dialog.currentnode = "BS_KS_7";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			chr.curtown = pchar.location;
			LAi_SetImmortal(sld, true);
		}
	}
	else
	{
		if (CheckAttribute(pchar, "BSCPSilver_talk") && pchar.location == "FortFrance_town")
		{
			chrDisableReloadToLocation = true;
			sld = CharacterFromID("BS_Silver");
			LAi_type_actor_Reset(sld);
			sld.dialog.currentnode = "BS_KS_8";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld.curtown = pchar.location;
		}
	}
}

void BSCourtlyPassions_sailor_begin_again(string _quest)
{
	if(CheckAttribute(pchar, "BSCPSailor_talk") || CheckAttribute(pchar, "BSCPSilver_talk"))
	{
		pchar.quest.BSCourtlyPassions_sailor_begin.win_condition.l1 = "ExitFromLocation";
		pchar.quest.BSCourtlyPassions_sailor_begin.function = "BSCourtlyPassions_sailor_begin";
	}
}

void BSCourtlyPassions_wait(string _quest)
{
	pchar.ContraInterruptWaiting = true;//Заблочить сон и отдых
	PChar.quest.BSCourtlyPassions_dungeon.win_condition.l1 = "location";
	PChar.quest.BSCourtlyPassions_dungeon.win_condition.l1.location = "FortFrance_dungeon";
	PChar.quest.BSCourtlyPassions_dungeon.function = "BSCourtlyPassions_dungeon";
}

void LockWeapons(string _quest)
{
	ref _location = &locations[reload_location_index];
	LAi_LocationFightDisable(_location, true);
}
void UnLockWeapons(string _quest)
{
	ref _location = &locations[reload_location_index];
	LAi_LocationFightDisable(_location, false);
}

void BSCourtlyPassions_dungeon(string _quest)
{
	WaitDate("",0,0,0,24 - sti(environment.time),5);
	LAi_LocationDisableMonGenTimer("FortFrance_dungeon", 3);//Лок спавна скелетов
	DoQuestFunctionDelay("LockWeapons", 0);
	chrDisableReloadToLocation = true;
	sld = GetCharacter(NPC_GenerateCharacter("BS_Vein", "BS_Vein", "man", "man", 99, PIRATE, -1, true));
	sld.name 	= "Чарльз";
	sld.lastname 	= "Вейн";
	ChangeCharacterAddressGroup(sld, "FortFrance_dungeon", "monsters", "monster35");
	LAi_SetStayTypeNoGroup(sld);
	LAi_SetImmortal(sld, true);
	sld.talker = 10;
	sld.dialog.filename = "Quest\BlackSails\Kurtuaznye_Strasti.c";
	sld.dialog.currentnode = "BS_KS_27";
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
	BSCourtlyPassions_spawn_podsos();
}

void BSCourtlyPassions_spawn_podsos()
{
	aref grp;
	ref _location = &Locations[FindLocation(pchar.location)];
	makearef(grp, _location.locators.monsters);
	int maxPodsos = GetAttributesNum(grp);
	string cnd;
	for (i = 1; i < maxPodsos; i++)
	{

		sld = GetCharacter(NPC_GenerateCharacter("BS_VeinPodsos"+i, "pirate_"+sti(rand(25)+1), "man", "man", 99, PIRATE, 3, true));
		ChangeCharacterAddressGroup(sld, _location.id, "monsters", GetAttributeName(GetAttributeN(grp, i)));
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_SetWarriorTypeNoGroup(sld);
		LAi_warrior_DialogEnable(sld, false);
		cnd = "l" + i;
		//pchar.quest.BSCourtlyPassions_kill_podsos.win_condition.(cnd) = "NPC_Death";
		//pchar.quest.BSCourtlyPassions_kill_podsos.win_condition.(cnd).character = sld.id;
	}
	//PChar.quest.BSCourtlyPassions_kill_podsos.function = "BSCourtlyPassions_kill_podsos";

}

void BSCourtlyPassions_kill_podsos(string _quest)
{
	chrDisableReloadToLocation = false;
	Log_testinfo ("killed all");
	LocatorReloadEnterDisable("FortFrance_Brothel", "reload2_back", true);
	LocatorReloadEnterDisable(pchar.location.from_sea, "boat", false);
	BSCourtlyPassions_SeaBattle();

	DoQuestCheckDelay("hide_weapon", 2.0);
	DoQuestFunctionDelay("BSCourtlyPassions_kill_podsos_1", 2.5);
}

void BSCourtlyPassions_kill_podsos_1(string _quest)
{
	if (WhisperIsHere())
	{
		SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
		StartInstantDialogNoType(pchar.WhisperPGG, "BS_16_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
	}
}

void BSCourtlyPassions_fleeng(string _quest)
{
	sld = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(sld, "FortFrance_town", "goto", "goto34");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "gate_back", "", "", "", "", -1);

	PChar.quest.BSCourtlyPassions_fleeng_1.win_condition.l1 = "location";
	PChar.quest.BSCourtlyPassions_fleeng_1.win_condition.l1.location = "FortFrance_exittown";
	PChar.quest.BSCourtlyPassions_fleeng_1.function = "BSCourtlyPassions_fleeng_1";
}

void BSCourtlyPassions_fleeng_1(string _quest)
{
	sld = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(sld, "FortFrance_exittown", "goto", "goto8");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload1_back", "", "", "", "", -1);

	PChar.quest.BSCourtlyPassions_fleeng_2.win_condition.l1 = "location";
	PChar.quest.BSCourtlyPassions_fleeng_2.win_condition.l1.location = "Martinique_jungle_01";
	PChar.quest.BSCourtlyPassions_fleeng_2.function = "BSCourtlyPassions_fleeng_2";
}

void BSCourtlyPassions_fleeng_2(string _quest)
{
	sld = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(sld, "Martinique_jungle_01", "goto", "goto4");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload1_back", "", "", "", "", -1);

	PChar.quest.BSCourtlyPassions_fleeng_3.win_condition.l1 = "location";
	PChar.quest.BSCourtlyPassions_fleeng_3.win_condition.l1.location = "Martinique_jungle_02";
	PChar.quest.BSCourtlyPassions_fleeng_3.function = "BSCourtlyPassions_fleeng_3";
}

void BSCourtlyPassions_fleeng_3(string _quest)
{
	sld = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(sld, "Martinique_jungle_02", "goto", "goto1");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload2_back", "", "", "", "", -1);

	PChar.quest.BSCourtlyPassions_fleeng_4.win_condition.l1 = "location";
	PChar.quest.BSCourtlyPassions_fleeng_4.win_condition.l1.location = "Martinique_jungle_03";
	PChar.quest.BSCourtlyPassions_fleeng_4.function = "BSCourtlyPassions_fleeng_4";
}

void BSCourtlyPassions_fleeng_4(string _quest)
{
	sld = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(sld, "Martinique_jungle_03", "goto", "goto1");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload2_back", "", "", "", "", -1);

	PChar.quest.BSCourtlyPassions_fleeng_5.win_condition.l1 = "location";
	PChar.quest.BSCourtlyPassions_fleeng_5.win_condition.l1.location = "Shore39";
	PChar.quest.BSCourtlyPassions_fleeng_5.function = "BSCourtlyPassions_fleeng_5";

	if (WhisperIsHere())
	{
		SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
		StartInstantDialogNoType(pchar.WhisperPGG, "BS_15_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
	}
}

void BSCourtlyPassions_fleeng_5(string _quest)
{
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("BS_Vein");
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "Shore39", "goto", "goto1");
	LAi_ActorGoToLocation(sld, "reload", "sea", "", "", "", "", -1);

	BS_SpawnEnemies(3 + drand(3) + GetOfficersQuantity(pchar), PIRATE, "BSCourtlyPassions_kill_podsos");
}

void BSCourtlyPassions_SeaBattle()
{
	Group_FindOrCreateGroup("BSCourtlyPassions_SeaBattle");
	Group_SetType("BSCourtlyPassions_SeaBattle", "pirate");
	sld = CharacterFromID("BS_Vein");
	//LAi_SetHP(sld, 20, 20);
	sld.Ship.Type = GenerateShipExt(SHIP_PDN, true, sld);
	FantomMakeCoolestSailor(sld, SHIP_PDN, "Рейнджер", CANNON_TYPE_CANNON_LBS24, 100, 100, 100);

	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 50);
	ChangeCrewExp(sld, "Cannoners", 50);
	ChangeCrewExp(sld, "Soldiers", 50);

	TakeNItems(sld, "Food5", 5);
	TakeNItems(sld, "potion2", 5);

	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "CannonProfessional");

	Fantom_SetBalls(sld, "war");

	LAi_SetImmortal(sld, false);
	sld.AlwaysEnemy = true;
	sld.DontRansackCaptain = true;
	sld.AlwaysSandbankManeuver = true;
	Group_AddCharacter("BSCourtlyPassions_SeaBattle", sld.id);
	Group_SetGroupCommander("BSCourtlyPassions_SeaBattle", sld.id);
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);

	Group_SetPursuitGroup("BSCourtlyPassions_SeaBattle", PLAYER_GROUP);
	Group_SetTaskAttack("BSCourtlyPassions_SeaBattle", PLAYER_GROUP);
	Group_LockTask("BSCourtlyPassions_SeaBattle");

	Group_SetAddress("BSCourtlyPassions_SeaBattle", "Martinique", "Quest_ships", "quest_ship_0");

	pchar.quest.BSCourtlyPassions_fail_to_board.win_condition.l1 = "NPC_Death";
	pchar.quest.BSCourtlyPassions_fail_to_board.win_condition.l1.character = sld.id;
	PChar.quest.BSCourtlyPassions_fail_to_board.function = "BSCourtlyPassions_fail_to_board";
	pchar.BSCourtlyPassionsFail = true;
}

void BSCourtlyPassions_final(string _quest)
{
	ref chr;
	sld = CharacterFromID("BS_Silver");
	ChangeCharacterAddressGroup(sld, "Shore39", "goto", "goto1");
	chr = CharacterFromID("BS_Maks");
	ChangeCharacterAddressGroup(chr, "Shore39", "goto", "goto3");
	LAi_SetActorTypeNoGroup(chr);
	LAi_ActorFollow(chr, sld, "", -1);
	LAi_SetStayTypeNoGroup(sld);
	sld.talker = 10;
	sld.dialog.currentnode = "BS_KS_33";
}

void BSCourtlyPassions_finalRoyal(string _quest)
{
	chrDisableReloadToLocation = true;
	sld = GetCharacter(NPC_GenerateCharacter("BS_Maks", "BS_Maks", "woman", "woman", 1, PIRATE, 0, false));
	sld.name = "Макс";
	sld.lastname = "";
	ChangeCharacterAddressGroup(sld, "PortRoyal_town", "goto", "goto1");
	LAi_SetActorType(sld);
	sld.dialog.filename = "Quest\BlackSails\Kurtuaznye_Strasti.c";
	sld.dialog.currentnode = "BS_KS_36";
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	LAi_SetImmortal(sld, true);
}

void BSCourtlyPassions_fail_to_board(string _quest)
{
	if (CheckAttribute(pchar, "BSCourtlyPassionsFail"))
	{
		CloseQuestHeader("BSCourtlyPassions");
		AddQuestRecord("BSCourtlyPassions", "9");
		BSRestoreWorldAlivePause();
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- Куртуазные страсти --     конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Погоня начинается
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void BSChaseBegun()
{
	Group_DeleteGroup("BSCourtlyPassions_SeaBattle");
	Group_DeleteGroup("Flint_Group");
	Group_DeleteGroup("BSOnTheHorizon_SeaBattle");
	Group_FindOrCreateGroup("Flint_Group");
	Group_SetType("Flint_Group", "pirate");

	sld = CharacterFromID("Flint");
	sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
	sld.DeckDialogNode = "BS_PN_shipF";
	Group_AddCharacter("Flint_Group", sld.id);
	Group_SetGroupCommander("Flint_Group", sld.id);
	Fantom_SetBalls(sld, "war");
	LAi_SetImmortal(sld, true);
	sld.AlwaysFriend = true;
	sld.DontRansackCaptain = true;
	sld.AlwaysSandbankManeuver = true;
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);

	sld = GetCharacter(NPC_GenerateCharacter("BS_Vein", "BS_Vein", "man", "man", 99, PIRATE, -1, true));
	sld.name 	= "Чарльз";
	sld.lastname 	= "Вейн";
	sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
	sld.DeckDialogNode = "BS_PN_shipV";
	FantomMakeCoolestSailor(sld, SHIP_PDN, "Рейнджер", CANNON_TYPE_CANNON_LBS24, 100, 100, 100);
	Group_AddCharacter("Flint_Group", sld.id);
	Fantom_SetBalls(sld, "war");
	LAi_SetImmortal(sld, true);
	sld.AlwaysFriend = true;
	sld.DontRansackCaptain = true;
	sld.AlwaysSandbankManeuver = true;
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);

	Group_SetTaskAttack("Flint_Group", PLAYER_GROUP);
	Group_LockTask("Flint_Group");

	Group_SetAddress("Flint_Group", "Bermudes", "Quest_ships", "quest_ship_8");

	PChar.quest.BSChaseBegun_shore.win_condition.l1 = "location";
	PChar.quest.BSChaseBegun_shore.win_condition.l1.location = "Shore_ship1";
	PChar.quest.BSChaseBegun_shore.function = "BSChaseBegun_shore";
}

void BSChaseBegun_shore(string q)
{
	InterfaceStates.Buttons.Save.enable = false;
	chrDisableReloadToLocation = true;
	LocatorReloadEnterDisable(pchar.location.from_sea, "boat", true);
	ref chr;
	sld = CharacterFromID("Flint");
	ChangeCharacterAddressGroup(sld, "Shore_ship1", "goto", "goto3");
	LAi_SetStayTypeNoGroup(sld);
	sld.talker = 10;
	sld.dialog.currentnode = "BS_PN_1";
	LAi_SetImmortal(sld, true);

	chr = GetCharacter(NPC_GenerateCharacter("BS_Silver", "BS_Silver", "man", "man", 999, PIRATE, -1, true));
	ChangeCharacterAddressGroup(chr, "Shore_ship1", "goto", "goto1");
	chr.name = "Джон";
	chr.lastname = "Сильвер";
	LAi_SetActorType(chr);
	LAi_ActorFollow(chr, sld, "", -1);
	LAi_SetImmortal(chr, true);

	chr = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(chr, "Shore_ship1", "goto", "goto2");
	LAi_SetActorType(chr);
	LAi_ActorFollow(chr, sld, "", -1);
	LAi_SetImmortal(chr, true);

	chr = GetCharacter(NPC_GenerateCharacter("BS_Rakham", "BS_Rakham", "man", "man", 999, PIRATE, -1, true));
	ChangeCharacterAddressGroup(chr, "Shore_ship1", "goto", "goto5");
	chr.name = "Джек";
	chr.lastname = "Рэкхэм";
	LAi_SetActorType(chr);
	LAi_ActorFollow(chr, sld, "", -1);
	LAi_SetImmortal(chr, true);

	chr = GetCharacter(NPC_GenerateCharacter("BS_Bony", "BS_Bony", "woman", "YokoDias", 999, PIRATE, -1, true));
	ChangeCharacterAddressGroup(chr, "Shore_ship1", "goto", "goto6");
	chr.name = "Энн";
	chr.lastname = "Бони";
	LAi_SetActorType(chr);
	LAi_ActorFollow(chr, sld, "", -1);
	LAi_SetImmortal(chr, true);
}

void BSChaseBegun_shore_fight()
{
	aref grp;
	ref _location = &Locations[FindLocation(pchar.location)];
	//makearef(grp, _location.locators.monsters);
	//int maxPodsos = GetAttributesNum(grp);
	string cnd, fnk;
	Group_DeleteGroup("BSChaseBegun_shore_fight");
	Group_FindOrCreateGroup("BSChaseBegun_shore_fight");//создать группу
	Group_SetType("BSChaseBegun_shore_fight", "war");//тип группы
	for (i = 1; i < 10 + MOD_SKILL_ENEMY_RATE * 2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("BSChaseBegun_shore_fight"+i, "pirate_"+sti(rand(25)+1), "man", "man", 99, PIRATE, 3, true));
		ChangeCharacterAddressGroup(sld, "Shore_ship1", "reload", "reload1_back"));
		LAi_group_MoveCharacter(sld, "BSChaseBegun_shore_fight");
		sld.Ship.Type = GenerateShip(SHIP_TARTANE, false);
		LAi_SetWarriorTypeNoGroup(sld);
		//LAi_warrior_DialogEnable(sld, false);
		cnd = "l" + i;
		//pchar.quest.BSChaseBegun_shore_fight_end.win_condition.(cnd) = "NPC_Death";
		//pchar.quest.BSChaseBegun_shore_fight_end.win_condition.(cnd).character = sld.id;
		fnk = "BSChaseBegun_shore_fightRecheck"+i;
		pchar.quest.(fnk).win_condition.(cnd) = "NPC_Death";
		pchar.quest.(fnk).win_condition.(cnd).character = "BSChaseBegun_shore_fight"+sti(i);
		pchar.quest.(fnk).function = "BSChaseBegun_shore_fightReCheck";
		Group_AddCharacter("BSChaseBegun_shore_fight", sld.id);//добавление в группу
	}
	Group_SetGroupCommander("BSChaseBegun_shore_fight", "BSChaseBegun_shore_fight1");
	Group_SetTaskAttack("BSChaseBegun_shore_fight", PLAYER_GROUP);
	Group_SetPursuitGroup("BSChaseBegun_shore_fight", PLAYER_GROUP);
	Group_SetAddress("BSChaseBegun_shore_fight", "Bermudes", "", "");
	Group_LockTask("BSChaseBegun_shore_fight");
}


void BSChaseBegun_shore_fightReCheck(string qName)
{
	if (!CheckAttribute(pchar, "BSChaseBegun_shore_fightEnd"))
	{
		int n = 1;
		for (i = 1; i < 10 + MOD_SKILL_ENEMY_RATE * 2; i++)
		{
			sld = CharacterFromID("BSChaseBegun_shore_fight"+sti(i));
			if(LAi_IsDead(sld))
			{
				n++;
			}
		}
		if(n >= 8 + MOD_SKILL_ENEMY_RATE * 2)
		{
			for (i = 1; i < 10 + MOD_SKILL_ENEMY_RATE * 2; i++)
			{
				sld = CharacterFromID("BSChaseBegun_shore_fight"+sti(i));
				if(!LAi_IsDead(sld))
				{
					LAi_KillCharacter(sld);
				}
			}
			Group_DeleteGroup("BSChaseBegun_shore_fight");
			sld = CharacterFromID("BS_Vein");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_9";
			//DoQuestFunctionDelay("BSChaseBegun_shore_fight_end", 1.5);
			pchar.BSChaseBegun_shore_fightEnd = true;
			PChar.quest.BSChaseBegun_lock_shore.win_condition.l1 = "location";
			PChar.quest.BSChaseBegun_lock_shore.win_condition.l1.location = "Bermudes_Cavern";
			PChar.quest.BSChaseBegun_lock_shore.function = "BSChaseBegun_lock_shore";
		}
	}
}

void BSChaseBegun_shore_fight_end(string q)
{
	pchar.BSChaseBegun_shore_fightEnd = true;
	sld = CharacterFromID("BS_Vein");
	sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
	sld.dialog.currentnode = "BS_PN_9";

	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);

}

void BSChaseBegun_lock_shore(string q)
{
	DeleteAttribute(pchar, "BSChaseBegun_shore_fightEnd")
	LocatorReloadEnterDisable("Bermudes_Cavern", "reload2_back", true);
	InterfaceStates.Buttons.Save.enable = true;
	PChar.quest.BSChaseBegun_dungeon.win_condition.l1 = "location";
	PChar.quest.BSChaseBegun_dungeon.win_condition.l1.location = "Bermudes_Dungeon";
	PChar.quest.BSChaseBegun_dungeon.function = "BSChaseBegun_dungeon";

	if (WhisperIsHere())
	{
		SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
		StartInstantDialogNoType(pchar.WhisperPGG, "BS_18_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
	}
}

void BSChaseBegun_dungeon(string q)
{
	BSCourtlyPassions_spawn_podsos();
	LAi_group_SetHearRadius("EnemyFight", 100.0);
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);

	sld = CharacterFromID("Pirates_Shipyarder");
	sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
	sld.dialog.currentnode = "BS_PN_13";

	LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", true);
}

void BSChaseBegun_town(string q)
{
	chrDisableReloadToLocation = true;
	BS_spawn_dead_podsos();
	ref chr;
	sld = CharacterFromID("Flint");
	ChangeCharacterAddressGroup(sld, "Pirates_Town", "officers", "reload3_1");
	LAi_SetActorType(sld);
	LAi_SetImmortal(sld, true);

	chr = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(chr, "Pirates_Town", "officers", "reload3_2");
	LAi_SetStayTypeNoGroup(chr);
	chr.talker = 10;
	chr.dialog.currentnode = "BS_PN_15";
	LAi_SetImmortal(chr, true);

	chr = CharacterFromID("BS_Bony");
	ChangeCharacterAddressGroup(chr, "Pirates_Town", "officers", "reload3_3");
	chr.name = "Энн";
	chr.lastname = "Бони";
	LAi_SetActorType(chr);
	LAi_ActorFollow(chr, sld, "", -1);
	LAi_SetImmortal(chr, true);
}

void BS_spawn_dead_podsos()
{
	InterfaceStates.Buttons.Save.enable = false;
	aref grp;
	ref _location = &Locations[FindLocation(pchar.location)];
	makearef(grp, _location.locators.patrol);
	int maxPodsos = GetAttributesNum(grp);
	string cnd;
	for (i = 1; i < maxPodsos; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("BS_VeinPodsos"+i, "pirate_"+sti(rand(25)+1), "man", "man", 99, PIRATE, 3, true));
		ChangeCharacterAddressGroup(sld, _location.id, "patrol", GetAttributeName(GetAttributeN(grp, i)));
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_SetWarriorTypeNoGroup(sld);
		LAi_warrior_DialogEnable(sld, false);
		LAi_KillCharacter(sld);
		cnd = "l" + i;
	}
	sld = CharacterFromID("Atilla");
	sld.AtillaNode = sld.dialog.currentnode;
	sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
	sld.dialog.currentnode = "BS_PN_13_1";
}

void BSChaseBegun_townhall(string q)
{
	chrDisableReloadToLocation = true;
	ref chr;
	sld = CharacterFromID("Jackman");
	SaveOldDialog(sld);
	sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
	sld.dialog.currentnode = "Jackman_Defeated";
	ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "", "");

	sld = CharacterFromID("Flint");
	ChangeCharacterAddressGroup(sld, "Pirates_townhall", "goto", "goto2");
	LAi_SetActorType(sld);

	chr = CharacterFromID("BS_Silver");
	ChangeCharacterAddressGroup(chr, "Pirates_townhall", "goto", "goto3");
	LAi_SetActorType(chr);
	LAi_SetStayTypeNoGroup(chr);
	chr.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
	chr.dialog.currentnode = "BS_PN_21";
	if (!CheckAttribute(pchar, "BSChaseBegun_townhall_Flint"))	chr.talker = 10;

	chr = CharacterFromID("BS_Rakham");
	ChangeCharacterAddressGroup(chr, "Pirates_townhall", "goto", "goto5");
	LAi_SetActorType(chr);

	chr = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(chr, "Pirates_townhall", "goto", "goto5");
	LAi_SetActorType(chr);

	chr = CharacterFromID("BS_Bony");
	ChangeCharacterAddressGroup(chr, "Pirates_townhall", "goto", "goto1");
	LAi_SetActorType(chr);

	chr = CharacterFromID("gatri_temp");
	ChangeCharacterAddressGroup(chr, "Pirates_townhall", "goto", "goto6");
	LAi_SetActorType(chr);
}

void BSChaseBegun_lock_townhall(string q)
{
	InterfaceStates.Buttons.Save.enable = true;
	LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
	LocatorReloadEnterDisable("Pirates_townhall", "reload2", true);
	LocatorReloadEnterDisable("Pirates_portoffice", "reload1", true);

	PChar.quest.BSChaseBegun_Hispaniola.win_condition.l1 = "location";
	PChar.quest.BSChaseBegun_Hispaniola.win_condition.l1.location = "Hispaniola1";
	PChar.quest.BSChaseBegun_Hispaniola.function = "BSChaseBegun_Hispaniola";
}

void BSChaseBegun_unlock_townhall()
{
	LocatorReloadEnterDisable("Pirates_town", "reload3_back", false);
	LocatorReloadEnterDisable("Pirates_townhall", "reload2", false);
	LocatorReloadEnterDisable("Pirates_portoffice", "reload1", false);
}

void BSChaseBegun_FewDeaysLater()
{
	WaitDate("",0,0,3,3,3);
	SetLaunchFrameFormParam("Несколько дней спустя...", "", 0.1, 2.0);
	LaunchFrameForm();
	DoQuestFunctionDelay("BSChaseBegun_FewDeaysLater_Reload", 2.0);
}

void BSChaseBegun_FewDeaysLater_Reload(string q)
{
	ClearIslandShips("SantoDomingo");
    Colonies[FindColony("SantoDomingo")].DontSetShipInPort = true;
    Colonies[FindColony("SantoDomingo")].BSChaseBegun = true;
	BSChaseBegun_SeaBattle();
	DoReloadCharacterToLocation("Pirates_townhall","goto","goto4");
}

void BSChaseBegun_Hispaniola(string q)
{
	AddQuestRecord("BSChaseBegun", "5");
}

void BSChaseBegun_Fail(string q)
{
	CloseQuestHeader("BSChaseBegun");
	DeleteAttribute(Colonies[FindColony("SantoDomingo")], "DontSetShipInPort");
	if (CheckAttribute(Colonies[FindColony("SantoDomingo")], "BSChaseBegun"))
	{
		AddQuestRecord("BSChaseBegun", "7");
		BSChaseBegun_unlock_townhall();
		EraseBSCharacters();
		DeleteAttribute(Colonies[FindColony("SantoDomingo")], "BSChaseBegun");
		BSRestoreWorldAlivePause();
	}
}

void EraseBSCharacters()
{
	sld = CharacterFromID("Flint");	sld.LifeDay = 0;
	RemoveCharacterCompanion(PChar, sld);
	sld = CharacterFromID("gatri_temp");	sld.LifeDay = 0;
	sld = CharacterFromID("BS_Vein");	sld.LifeDay = 0;
	RemoveCharacterCompanion(PChar, sld);
	sld = CharacterFromID("BS_Rakham");	sld.LifeDay = 0;
	sld = CharacterFromID("BS_Bony");	sld.LifeDay = 0;
	sld = CharacterFromID("BS_Silver");	sld.LifeDay = 0;
	sld = CharacterFromID("BSUrka_enemyfleet");	sld.LifeDay = 0;
	sld = CharacterFromID("BSUrka");	sld.LifeDay = 0;

	for (i = 1; i < 7; i++)
	{
		sld = CharacterFromID("BSUrka_Curacao_enemyfleet"+i);	sld.LifeDay = 0;
	}

	DeleteAttribute(pchar, "LockMapReload");
	DeleteAttribute(pchar, "LockShoreReload");
}
void BSChaseBegun_EndQuest(string q)
{
	sld = CharacterFromID("Flint");
	RemoveCharacterCompanion(PChar, sld);
	ProcessHullRepair(sld, 100.0);
	ProcessSailRepair(sld, 100.0);
	DeleteAttribute(sld, "ship.blots");
	DeleteAttribute(sld, "ship.sails");
	DeleteAttribute(sld, "ship.masts");

	ChangeCharacterAddressGroup(sld, "Pirates_Town", "quest", "quest1");
	chrDisableReloadToLocation = true;
	LAi_SetActorType(sld);
	sld.dialog.currentnode = "BS_PN_30";
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}
void BSChaseBegun_SeaBattle()
{
	Group_FindOrCreateGroup("BSChaseBegun_SeaBattle");
	Group_SetType("BSChaseBegun_SeaBattle", "pirate");

	Group_DeleteGroup("Flint_Group");
	Group_FindOrCreateGroup("Flint_Group");
	Group_SetType("Flint_Group", "pirate");

	ref chr = CharacterFromID("Flint");
	chr.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
	chr.DeckDialogNode = "BS_PN_30_seabattle";
	Group_AddCharacter("Flint_Group", chr.id);
	Group_SetGroupCommander("Flint_Group", chr.id);
	Fantom_SetBalls(chr, "war");
	LAi_SetImmortal(chr, false);
	chr.AlwaysFriend = true;
	chr.DontRansackCaptain = true;
	chr.AlwaysSandbankManeuver = true;
	SetCharacterRelationBoth(sti(chr.index), GetMainCharacterIndex(), RELATION_FRIEND);

	Group_SetTaskAttack("Flint_Group", "BSChaseBegun_SeaBattle");
	Group_LockTask("Flint_Group");

	//Group_SetAddress("Flint_Group", "Hispaniola1", "Quest_ships", "reload_fort1");
	Group_SetAddress("Flint_Group", "Hispaniola1", "Quest_ships", "quest_ship_5");

	pchar.quest.BSChaseBegun_Fail.win_condition.c1 = "NPC_Death";
	pchar.quest.BSChaseBegun_Fail.win_condition.c1.character ="Flint";
	PChar.quest.BSChaseBegun_Fail.function = "BSChaseBegun_Fail";

	for (i = 1; i < 9; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("BSChaseBegun_SeaBattle"+i, "off_spa_"+(rand(1)+1), "man", "man", 999, SPAIN, -1, true));
		CreatePGG_War(sld, 2, chr);
		sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS24;
		sld.ship.Crew.Morale = 100;
		ChangeCrewExp(sld, "Sailors", 50);
		ChangeCrewExp(sld, "Cannoners", 50);
		ChangeCrewExp(sld, "Soldiers", 50);

		TakeNItems(sld, "Food5", 5);
		TakeNItems(sld, "potion2", 5);

		SetCharacterPerk(sld, "MusketsShoot");
		SetCharacterPerk(sld, "CannonProfessional");

		Fantom_SetBalls(sld, "war");

		sld.AlwaysEnemy = true;
		sld.DontRansackCaptain = true;
		sld.AlwaysSandbankManeuver = true;
		Group_AddCharacter("BSChaseBegun_SeaBattle", sld.id);
		if (i == 1) Group_SetGroupCommander("BSChaseBegun_SeaBattle", sld.id);
		SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);

		//Group_SetPursuitGroup("BSChaseBegun_SeaBattle", PLAYER_GROUP);
		Group_SetTaskAttack("BSChaseBegun_SeaBattle", PLAYER_GROUP);
		Group_LockTask("BSChaseBegun_SeaBattle");

		Group_SetAddress("BSChaseBegun_SeaBattle", "Hispaniola1", "Quest_ships", "quest_ship_1");
	}
	//sld = CharacterFromID("Flint");
	//LAi_SetImmortal(sld, false);
	PChar.quest.BSChaseBegun_CheckFlag.win_condition.l1 = "location";
	PChar.quest.BSChaseBegun_CheckFlag.win_condition.l1.location = "Hispaniola1";
	PChar.quest.BSChaseBegun_CheckFlag.function = "BSChaseBegun_CheckFlag";
}
void BSChaseBegun_CheckFlag(string q)
{
	if (sti(pchar.nation) != PIRATE)
	{
		sld = CharacterFromID("Flint");
		DeleteAttribute(sld, "AlwaysFriend");
		sld.AlwaysEnemy = true;
	}
	else
	{
		pchar.LockMapReload = "Нет. Я не могу бросить здесь Флинта.";
		pchar.LockShoreReload = "Нет. Я не могу бросить здесь Флинта.";
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- Погоня начинается --     конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Неуловимая «Урка»
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void BSUrka_Negril(string q)
{
	AddQuestRecord("BSUrka", "2");
	BS_RestoreMaksHostess("q");
	pchar.BSUrka_Negril = true;

	if (WhisperIsHere())
	{
		SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
		StartInstantDialogNoType(pchar.WhisperPGG, "BS_2_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
	}
}

void BSBons_SeaBattle(bool bonsAdmiral)
{
	string sGroup = "Sea_BSBons0";
	string sScarboro = "";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	for (int i = 0; i < 5; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("BSBons"+i, "off_eng_"+(rand(1)+1), "man", "man", 999, ENGLAND, 8, true));
		FantomMakeCoolSailor(sld, SHIP_NL_PinnaceofWar47, "Морж", CANNON_TYPE_CANNON_LBS32, 100, 100, 100);
		sld.AlwaysEnemy = true;
		sld.Ship.Type = GenerateShipExt(SHIP_FEARLESS, true, sld);

		Group_AddCharacter(sGroup, sld.id);
		if (i == 0)
		{

				Group_SetGroupCommander(sGroup, sld.id);
				if (bonsAdmiral)
				{
					if (!CheckAttribute(pchar, "BSBonsSpawned"))
					{
						FantomMakeCoolestSailor(sld, SHIP_FASTFRIGATE, "Фортуна", CANNON_TYPE_CANNON_LBS32, 100, 100, 100);
						sld.Name = "Билли";
						sld.Lastname = "Бонс";
						sld.Model = "BS_Billy";
						sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
						sld.DeckDialogNode = "BS_CPNG_15";
						FaceMaker(sld);
						sld.SaveItemsForDead = true;
						sld.money = 100000;
						sld.items.jewelry1 = 10+rand(5);
						sld.items.jewelry2 = 10+rand(5);
						sld.items.jewelry3 = 10+rand(5);
						sld.items.jewelry4 = 5+rand(5);
						sld.items.jewelry6 = rand(20);
						sld.items.jewelry7 = rand(50);
						sld.items.jewelry10 = rand(20);
						sld.items.jewelry14 = rand(20);
						sld.items.jewelry15 = rand(5);
						sld.items.jewelry18 = rand(50);
					}
					else
					{
						FantomMakeCoolestSailor(sld, SHIP_BATTLEMANOWAR, "Скарборо", CANNON_TYPE_CANNON_LBS42, 100, 100, 100);
						FaceMaker(sld);
						sScarboro = " со 'Скарборо' во главе";
						FantomMakeCoolFighter(sld, 100, 100, 100, "blade33", "pistol4", 1000);
						sld.name = "Френсис";
						sld.lastname = "Ньюм";
						sld.SaveItemsForDead = true;
						sld.money = 300000;
						sld.items.jewelry1 = 20+rand(5);
						sld.items.jewelry2 = 20+rand(5);
						sld.items.jewelry3 = 20+rand(5);
						sld.items.jewelry4 = 11+rand(5);
						sld.items.jewelry6 = rand(50);
						sld.items.jewelry7 = rand(100);
						sld.items.jewelry10 = rand(50);
						sld.items.jewelry14 = rand(50);
						sld.items.jewelry15 = rand(10);
						sld.items.jewelry18 = rand(100);
						pchar.quest.BSUrka_Scarboro.win_condition.l1 = "NPC_Death";
						pchar.quest.BSUrka_Scarboro.win_condition.l1.character ="BSBons0";
						PChar.quest.BSUrka_Scarboro.function = "BSUrka_Scarboro";
					}
				}
		}
		Group_LockTask(sGroup);
		sld.mapEnc.type = "war";
		sld.mapEnc.worldMapShip = "quest_ship";
		sld.mapEnc.Name = "охотники на пиратов" + sScarboro;
	}
	Map_CreateFastWarrior("", "BSBons0", 8);
}

void BSUrka_Pirates_town(string q)
{
	chrDisableReloadToLocation = true;
	ref chr = CharacterFromID("BS_Bony");
	ChangeCharacterAddressGroup(chr, "Pirates_Town", "reload", "reload3_back");
	LAi_SetImmortal(chr, true);
	sld = CharacterFromID("BS_Rakham");
	ChangeCharacterAddressGroup(sld, "Pirates_Town", "goto", "goto7");
	LAi_SetImmortal(sld, true);
	LAi_ActorFollow(chr, sld, "", -1);
	LAi_CharacterDisableDialog(sld);
	LAi_SetWarriorTypeNoGroup(sld);

	sld = GetCharacter(NPC_GenerateCharacter("BS_Maks", "BS_Maks", "woman", "woman", 1, PIRATE, -1, false));
	sld.name = "Макс";
	sld.lastname = "";
	ChangeCharacterAddressGroup(sld, "Pirates_Town", "goto", "goto4");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, pchar, "", -1);
	LAi_SetImmortal(sld, true);
	PChar.quest.BSUrka_Pirates_town_residence.win_condition.l1 = "locator";
	PChar.quest.BSUrka_Pirates_town_residence.win_condition.l1.location = "Pirates_town";
	PChar.quest.BSUrka_Pirates_town_residence.win_condition.l1.locator_group = "reload";
	PChar.quest.BSUrka_Pirates_town_residence.win_condition.l1.locator = "reload3_back";
	PChar.quest.BSUrka_Pirates_town_residence.function = "BSUrka_Pirates_town_residence";
}

void BSUrka_Pirates_town_residence(string q)
{
	sld = CharacterFromID("BS_Maks");
	ChangeCharacterAddressGroup(sld, "Pirates_Townhall", "goto", "goto3");

	DoReloadCharacterToLocation("Pirates_townhall","goto","goto4");
	pchar.BSChaseBegun_townhall_Flint = true;
	BSChaseBegun_townhall("q");
	DeleteAttribute(pchar, "BSChaseBegun_townhall_Flint");

	sld = CharacterFromID("Flint");
	LAi_SetStayTypeNoGroup(sld);
	sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
	sld.dialog.currentnode = "BS_NU_18";
	sld.talker = 10;
}

void BSUrka_Pirates_town_Vein(string q)
{
	sld = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(sld, "Pirates_Town", "quest", "quest1");
	sld.dialog.currentnode = "BS_NU_33_Ya_Ne_Krisa";
	LAi_SetStayTypeNoGroup(sld);
	sld.talker = 10;
	chrDisableReloadToLocation = true;
}

void BSUrka_Curacao_SeaBattle()
{
	Group_FindOrCreateGroup("BSUrka_Curacao_SeaBattle");
	Group_SetType("BSUrka_Curacao_SeaBattle", "pirate");
	LAi_group_Delete("BSUrka_Curacao_Battle");
	string cnd;
	for (i = 1; i < 7; i++)
	{

		sld = GetCharacter(NPC_GenerateCharacter("BSUrka_Curacao_enemyfleet"+i, "off_spa_"+(rand(1)+1), "man", "man", 999, SPAIN, -1, true));
		if (i == 1)
		{
			sld.Ship.Type = GenerateShipExt(SHIP_GALEON50, true, sld);
			//sld.Ship.Name = "Денуво";
			//sld.Name = "Денуво";
			//sld.Lastname = "Антитампер";
		}
		if (i == 2) sld.Ship.Type = GenerateShipExt(SHIP_FRIGATE_SAT, true, sld);
		if (i == 3) sld.Ship.Type = GenerateShipExt(SHIP_WARSHIP, true, sld);
		if (i == 4) sld.Ship.Type = GenerateShipExt(SHIP_ALEXIS, true, sld);
		if (i == 5) sld.Ship.Type = GenerateShipExt(SHIP_SUPERBE, true, sld);
		if (i == 6) sld.Ship.Type = GenerateShipExt(SHIP_LINK2, true, sld);
		sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;

		sld.ship.Crew.Morale = 100;
		ChangeCrewExp(sld, "Sailors", 50);
		ChangeCrewExp(sld, "Cannoners", 50);
		ChangeCrewExp(sld, "Soldiers", 50);

		TakeNItems(sld, "Food5", 5);
		TakeNItems(sld, "potion2", 5);

		SetCharacterPerk(sld, "MusketsShoot");
		SetCharacterPerk(sld, "CannonProfessional");

		Fantom_SetBalls(sld, "war");

		sld.AlwaysEnemy = true;
		sld.DontRansackCaptain = true;
		sld.AlwaysSandbankManeuver = true;
		Group_AddCharacter("BSUrka_Curacao_SeaBattle", sld.id);
		LAi_group_MoveCharacter(sld, "BSUrka_Curacao_Battle");
		if (i == 1) Group_SetGroupCommander("BSUrka_Curacao_SeaBattle", sld.id);
		SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);

		//Group_SetPursuitGroup("BSUrka_Curacao_SeaBattle", PLAYER_GROUP);
		Group_SetTaskAttack("BSUrka_Curacao_SeaBattle", PLAYER_GROUP);
		Group_LockTask("BSUrka_Curacao_SeaBattle");

		Group_SetAddress("BSUrka_Curacao_SeaBattle", "Curacao", "Quest_ships", "quest_ship_4");

		cnd = "l" + i;
		pchar.quest.BSUrka_Curacao_EndSeaBattle.win_condition.(cnd) = "NPC_Death";
		pchar.quest.BSUrka_Curacao_EndSeaBattle.win_condition.(cnd).character ="BSUrka_Curacao_enemyfleet"+sti(i);
	}
	PChar.quest.BSUrka_Curacao_EndSeaBattle.function = "BSUrka_Curacao_EndSeaBattle";

	SetFunctionNPCDeathCondition("BSUrka_Curacao_SeaBattleStarted", "BSUrka_Curacao_enemyfleet1", false);

	PChar.quest.BSUrka_Curacao_Entered.win_condition.l1 = "location";
	PChar.quest.BSUrka_Curacao_Entered.win_condition.l1.location = "Curacao";
	PChar.quest.BSUrka_Curacao_Entered.function = "BSUrka_Curacao_SeaBattleStarted";
}

void BSUrka_Curacao_SeaBattleStarted(string q)
{
	if (!CheckAttribute(pchar, "BSFinish"))
	{
		pchar.LockMapReload = "На это нет времени. Сперва нужно добить испанскую эскадру.";
		pchar.LockShoreReload = "На это нет времени. Сперва нужно добить испанскую эскадру.";
	}
}

void BSUrka_Curacao_EndSeaBattle(string q)
{
	LAi_group_Delete("BSUrka_Curacao_Battle");
	Sea_CabinStartNow();
	pchar.quest.BSUrka_Curacao_Cabin.win_condition.l1          = "location";
	pchar.quest.BSUrka_Curacao_Cabin.win_condition.l1.location = Get_My_Cabin();
	pchar.quest.BSUrka_Curacao_Cabin.function             = "BSUrka_Curacao_CabinTalk";
}

void BSUrka_Curacao_CabinTalk(string q)
{
	chrDisableReloadToLocation = true;
	LAi_LockFightMode(pchar, true);
	sld = CharacterFromID("Flint");
	sld.dialog.currentnode = "BS_NU_35";
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, pchar.location, "rld", LAi_FindFarLocator("rld", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void BSUrka_Curacao_Shore(string q)
{
	ref locLoad = &locations[reload_location_index];
	LAi_LocationFightDisable(locLoad, true);
	chrDisableReloadToLocation = true;
	LAi_LockFightMode(pchar, true);
	sld = CharacterFromID("Flint");
	sld.dialog.currentnode = "BS_NU_37";
	ChangeCharacterAddressGroup(sld, pchar.location, "smugglers", "smugglerload");
	LAi_SetStayType(sld);
	sld.talker = 10;
	sld = GetCharacter(NPC_GenerateCharacter("BSUrka_Prisoner", "off_spa_"+(rand(1)+1), "man", "man", 999, SPAIN, 3, true));
	ChangeCharacterAddressGroup(sld, pchar.location, "smugglers", "smuggler01");
	LAi_SetActorType(sld);
	sld = CharacterFromID("BS_Bony");
	ChangeCharacterAddressGroup(sld, pchar.location, "smugglers", "smuggler02");
	LAi_SetActorType(sld);
	sld = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto2");
	LAi_SetActorType(sld);

}

void BSUrka_BonyHits(string qName)
{
	sld = CharacterFromId("BSUrka_Prisoner");
	ref chr = CharacterFromId("BS_Bony");
	LAi_SetActorTypeNoGroup(chr);
	LAi_ActorTurnToCharacter(chr, sld);
	LAi_ActorAnimation(chr, "Shot", "", 1.9);
    DoQuestFunctionDelay("BSUrka_BonyHits_1", 0.8);
}
void BSUrka_BonyHits_1(string qName)
{
	DialogExit();
	sld = CharacterFromId("BSUrka_Prisoner");
	ref chr = CharacterFromId("BS_Bony");
	LAi_KillCharacter(sld);
    DoQuestFunctionDelay("BSUrka_BonyHits_2", 0.25);
}
void BSUrka_BonyHits_2(string qName)
{
	ref chr = CharacterFromId("BS_Bony");
	Lai_SetStayType(chr);

	sld = CharacterFromID("BS_Vein");
	sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
	sld.dialog.currentnode   = "BS_NU_41";
	pchar.InstantDialog = sld.id;
	DoQuestFunctionDelay("InstantDialog", 1.3);

	ref locLoad = &locations[reload_location_index];
	LAi_LocationFightDisable(locLoad, false);
}
void BSUrka_Found(string qName)
{
	AddQuestRecord("BSUrka", "8");
}

void BSUrka_PlaceUrka()
{
	//Урка
	Group_FindOrCreateGroup("BSUrka");
	Group_SetType("BSUrka", "pirate");
	string cnd;

	sld = GetCharacter(NPC_GenerateCharacter("BSUrka", "off_spa_"+(rand(1)+1), "man", "man", 999, SPAIN, -1, true));

	sld.Ship.Type = GenerateShipExt(SHIP_GALEON50, true, sld);
	sld.Ship.Name = "Урка де Лима";
	sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;

	sld.LockBoat = true;
	sld.ShipEnemyDisable = true;
	sld.AlwaysFriend = true;
	sld.DontRansackCaptain = true;
	sld.AlwaysSandbankManeuver = true;
	Group_AddCharacter("BSUrka", sld.id);
	LAi_group_MoveCharacter(sld, "BSUrka");
	Group_SetGroupCommander("BSUrka", sld.id);
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);

	int iMast = 0;
	int iMastQty = 4;
	string sMast = "";
	for(int m=1; m <= iMastQty; m++)
	{
		sMast = "mast" + m;
		sld.ship.masts.(sMast) = true;
	}
	sld.ship.HP = sti(sld.ship.HP) / 4;
	SetCrewQuantity(sld, 0);
	LAi_SetImmortal(sld, true);

	Group_SetAddress("BSUrka", "Cumana", "quest_ships", "quest_ship_9");

	//Самовар
	Group_FindOrCreateGroup("BSUrka_SeaBattle");
	Group_SetType("BSUrka_SeaBattle", "pirate");

	sld = GetCharacter(NPC_GenerateCharacter("BSUrka_enemyfleet", "off_spa_"+(rand(1)+1), "man", "man", 999, SPAIN, -1, true));
	sld.Ship.Type = GenerateShipExt(SHIP_SP_SANFELIPE, true, sld);
	sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;

	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 50);
	ChangeCrewExp(sld, "Cannoners", 50);
	ChangeCrewExp(sld, "Soldiers", 50);

	TakeNItems(sld, "Food5", 5);
	TakeNItems(sld, "potion2", 5);

	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "CannonProfessional");

	Fantom_SetBalls(sld, "war");

	sld.AlwaysEnemy = true;
	sld.DontRansackCaptain = true;
	sld.AlwaysSandbankManeuver = true;
	Group_AddCharacter("BSUrka_SeaBattle", sld.id);
	Group_SetGroupCommander("BSUrka_SeaBattle", sld.id);
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);

	Group_SetTaskAttack("BSUrka_SeaBattle", PLAYER_GROUP);
	Group_LockTask("BSUrka_SeaBattle");

	Group_SetAddress("BSUrka_SeaBattle", "Cumana", "Quest_ships", "quest_ship_9");

	SetFunctionNPCDeathCondition("BSUrka_SeaBattleEnded", "BSUrka_enemyfleet", false);
}

void BSUrka_SeaBattleEnded(string q)
{
	AddQuestRecord("BSUrka", "8_1");
	pchar.quest.BSUrka_ShoreBattle.win_condition.l1          = "location";
	pchar.quest.BSUrka_ShoreBattle.win_condition.l1.location = "Shore20";
	pchar.quest.BSUrka_ShoreBattle.function             = "BSUrka_ShoreBattle";

	AddGeometryToLocation("Shore20", "smg");
}

void BSUrka_ShoreBattle(string q)
{
	ref chr;
	string attrName, sLoc, sLoc_2, relation;
	int i, iRnd, iNation;

	relation = LAI_GROUP_PLAYER;
	sLoc = "Shore20";
	iNation = SPAIN;

	chrDisableReloadToLocation = true;
	//our
	chr = CharacterFromID("Flint");
	ChangeCharacterAddressGroup(chr,pchar.location, "officers", "sea_1");
	LAi_SetWarriorType(chr);
	LAi_SetImmortal(chr, true);
	LAi_group_MoveCharacter(chr, relation);

	chr = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(chr,pchar.location, "officers", "sea_1");
	LAi_SetWarriorType(chr);
	LAi_SetImmortal(chr, true);
	LAi_group_MoveCharacter(chr, relation);

	chr = CharacterFromID("BS_Bony");
	ChangeCharacterAddressGroup(chr,pchar.location, "officers", "sea_1");
	LAi_SetWarriorType(chr);
	LAi_SetImmortal(chr, true);
	LAi_group_MoveCharacter(chr, relation);

	chr = CharacterFromID("BS_Silver");
	ChangeCharacterAddressGroup(chr,pchar.location, "officers", "sea_1");
	LAi_SetWarriorType(chr);
	LAi_SetImmortal(chr, true);
	LAi_group_MoveCharacter(chr, relation);

	chr = CharacterFromID("BS_Rakham");
	ChangeCharacterAddressGroup(chr,pchar.location, "officers", "sea_1");
	LAi_SetWarriorType(chr);
	LAi_SetImmortal(chr, true);
	LAi_group_MoveCharacter(chr, relation);

	iRnd = 15 - GetOfficersQuantity(pchar);
	PChar.GenQuestFort.FarLocator = false;
	sLoc = LAi_FindNPCLocator("officers");
	for (i = 1; i < iRnd; i++)
	{
		if (i % 3 != 0)
		{
		chr = SetFantomDefenceForts("officers", sLoc, PIRATE, relation);
		}
		else
		{
		chr = SetFantomDefenceForts("enc02", "",PIRATE, relation);
		}
		FantomMakeCoolFighterWRankDepend(chr,sti(pchar.rank),25+rand(75),25+rand(75),50);
	}
	Pchar.GenQuestFort.FarLocator = true;

	//enemy
	iRnd = 80;
	Pchar.GenQuestFort.FarLocator = true;
	sLoc = LAi_FindNPCLocator("goto");
	sLoc_2 = LAi_FindNPCLocator("smugglers");
	for (i = 1; i < iRnd; i++)
	{
		if (i % 2 == 0)
		{
		chr = SetFantomDefenceForts("goto", sLoc, iNation, "BSUrkaShore");
		}
		else
		{
			chr = SetFantomDefenceForts("smugglers", sLoc_2, iNation, "BSUrkaShore");
		}
		chr.id = "pirate_" + i;
		FantomMakeCoolFighterWRankDepend(chr,sti(pchar.rank),25+rand(75),25+rand(75),50);
	}
	//натравим.
	LAi_group_SetHearRadius("BSUrkaShore", 100.0);
	LAi_group_FightGroupsEx("BSUrkaShore", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
	LAi_group_FightGroupsEx("BSUrkaShore", relation, true, Pchar, -1, false, false);

	LAi_group_SetCheckFunction("BSUrkaShore", "BSUrka_AfterShoreBattle");

	LAi_SetFightMode(pchar, true);
}

void BSUrka_AfterShoreBattle()
{
	//chrDisableReloadToLocation = false;
	RemoveGeometryFromLocation("Shore20", "smg");

	ref chr, rGroup;
	string sGroup;

	chr = CharacterFromID("BSUrka");
	chr.LifeDay = 0;
	chr = CharacterFromID("Flint");
	chr.dialog.currentnode   = "BS_NU_45";
	DoQuestCheckDelay("hide_weapon", 2.0);
	LAi_SetActorType(chr);
	LAi_ActorDialog(chr, pchar, "", -1, 0);
}

void BSUrka_Scarboro(string q)
{
	AddQuestRecord("BSUrka", "11");
}

void BSUrka_Fail(string q)
{
	AddQuestRecord("BSUrka", "12");
	CloseQuestHeader("BSUrka");
	BSChaseBegun_unlock_townhall();
	PChar.quest.BSChaseBegun_Fail.over = "yes";
	PChar.quest.BSUrka_Fail1.over = "yes";
	PChar.quest.BSUrka_Fail2.over = "yes";
	PChar.quest.BSUrka_Curacao_EndSeaBattle.over = "yes";
	PChar.quest.BSUrka_SeaBattleEnded.over = "yes";
	EraseBSCharacters();
	BSRestoreWorldAlivePause();
}

void BSUrka_Finish(string q)
{
	pchar.BSChaseBegun_townhall_Flint = true;
	BSChaseBegun_townhall("");
	DeleteAttribute(pchar, "BSChaseBegun_townhall_Flint");

	sld = CharacterFromID("Flint");
	LAi_SetStayTypeNoGroup(sld);
	sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
	sld.dialog.currentnode = "BS_NU_50";
	sld.talker = 10;
}

void BSUrka_Poison()
{
	LAi_SetActorTypeNoGroup(pchar);
	DoQuestFunctionDelay("BSUrka_Poison_1", 3);
	DoQuestFunctionDelay("BSUrka_Poison_2", 5);
	DoQuestFunctionDelay("BSUrka_Poison_3", 7);
	DoQuestFunctionDelay("BSUrka_Poison_4", 9);
	DoQuestFunctionDelay("BSUrka_Poison_5", 10);
	DoQuestFunctionDelay("BSUrka_Poison_6", 12);
	if (!WhisperIsHere())
	{
		DoQuestFunctionDelay("BSUrka_PoisonOfficers", 13);
		DoQuestFunctionDelay("BSUrka_PoisonSelf", 14.0);
		DoQuestFunctionDelay("BSUrka_Poison_Flint", 17.0);
	}

	sld = CharacterFromID("Flint");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorTurnToCharacter(sld, pchar);
}
void BSUrka_PoisonSelf(string q)
{
	SetCharacterTask_Dead(pchar);
}

void BSUrka_PoisonOfficers(string q)
{
	int idx;
	for(int i=1; i<=MAX_NUM_FIGHTERS; i++)
	{
		idx = GetOfficersIndex(PChar,i);
		if (idx != -1) {
			ref offchar = GetCharacter(idx);
			SetCharacterTask_Dead(offchar);
		}
	}
}

void BSUrka_Poison_1(string q)
{
	sld = CharacterFromID("BS_Silver");
	SetCharacterTask_Dead(sld);
	Log_Info("После нескольких глотков, вы ощущаете лёгкое головокружение.");
}
void BSUrka_Poison_2(string q)
{
	sld = CharacterFromID("BS_Rakham");
	SetCharacterTask_Dead(sld);
}
void BSUrka_Poison_3(string q)
{
	sld = CharacterFromID("BS_Vein");
	SetCharacterTask_Dead(sld);
}
void BSUrka_Poison_4(string q)
{
	sld = CharacterFromID("BS_Bony");
	SetCharacterTask_Dead(sld);

	if (WhisperIsHere())
	{
		LAi_SetPlayerType(pchar);
		SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
		StartInstantDialogNoType(pchar.WhisperPGG, "BS_20_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
	}
}
void BSUrka_Poison_5(string q)
{
	sld = CharacterFromID("gatri_temp");
	SetCharacterTask_Dead(sld);
	Log_Info("Вы чувствуете, как сознание покидает вас.");
}
void BSUrka_Poison_6(string q)
{
	sld = CharacterFromID("BS_Maks");
	SetCharacterTask_Dead(sld);
}
void BSUrka_Poison_Flint(string q)
{
	BSUrka_FewDaysLater();
}

void BSUrka_FewDaysLater()
{
	WaitDate("",0,0,3,3,3);
	SetLaunchFrameFormParam("Несколько дней спустя...", "", 0.1, 2.0);
	LaunchFrameForm();
	DoQuestFunctionDelay("BSUrka_FewDaysLater_Reload", 2.0);
}

void BSUrka_FewDaysLater_Reload(string q)
{
	DoReloadCharacterToLocation("Pirates_tavern_upstairs","goto","goto1");
	pchar.quest.BSHangover_Start.win_condition.l1          = "location";
	pchar.quest.BSHangover_Start.win_condition.l1.location = "Pirates_tavern_upstairs";
	pchar.quest.BSHangover_Start.function             = "BSHangover_Start";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- Неуловимая «Урка» --     конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- Тяжелое похмелье --     начало
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void BSHangover_Start(string q)
{
	LAi_SetPlayerType(pchar);
	chrDisableReloadToLocation = false;
	CloseQuestHeader("BSUrka");
	SetQuestHeader("BSHangover");
	AddQuestRecord("BSHangover", "1");

	LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
	LocatorReloadEnterDisable("Pirates_townhall", "reload2", true);
	LocatorReloadEnterDisable("Pirates_portoffice", "reload1", true);

	pchar.quest.BSHangover_Downstairs.win_condition.l1          = "location";
	pchar.quest.BSHangover_Downstairs.win_condition.l1.location = "Pirates_tavern";
	pchar.quest.BSHangover_Downstairs.function             = "BSHangover_Downstairs";

	if (WhisperIsOfficer())
	{
		sld = CharacterFromID(pchar.WhisperId);
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto1");
		SaveOldDialog(sld);
		StartInstantDialogNoType(pchar.WhisperPGG, "BS_6_WhisperIsHere_1", "Quest\WhisperLine\Whisper.c");
	}
}

void BSHangover_Downstairs(string q)
{
	sld = CharacterFromID("BS_Maks");
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto1");
	sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
	sld.dialog.currentnode = "BS_F1_5";
	LAi_SetStayTypeNoGroup(sld);
	LAi_SetImmortal(sld, true);
	sld.talker = 10;
}

void BSHangover_PortRoyal(string q)
{
	BSCourtlyPassions_finalRoyal("");
	sld = CharacterFromID("BS_Maks");
	sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
	sld.dialog.currentnode = "BS_F1_8_MaksRoyal";
}

void BSHangover_Vein(string q)
{
	sld = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto1");
	SaveOldDialog(sld);
	StartInstantDialog("BS_Vein", "BS_F1_14", "Quest\BlackSails\BS_Final_1.c");
}

void BSHangover_RoyalVein(string q)
{
	chrDisableReloadToLocation = true;

	sld = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto7");

	sld = CharacterFromID("PortRoyal_hostess");
	SaveOldDialog(sld);
	sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
	sld.dialog.currentnode = "BS_F1_16";

}

void BSHangover_SearchStingerCheck()
{
	if(sti(pchar.BSSearchStinger) == 7)
	{
		AddQuestRecord("BSHangover", "6");
		LocatorReloadEnterDisable("Bridgetown_town", "gate_back", false);
		pchar.quest.BSHangover_Jail.win_condition.l1          = "location";
		pchar.quest.BSHangover_Jail.win_condition.l1.location = "Bridgetown_prison";
		pchar.quest.BSHangover_Jail.function             = "BSHangover_Jail";

		if (WhisperIsHere())
		{
			SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
			StartInstantDialogNoType(pchar.WhisperPGG, "BS_11_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
		}
	}
}

void BSHangover_Jail(string q)
{
	chrDisableReloadToLocation = true;
	DoQuestFunctionDelay("BSHangover_Jail_1", 0);
}
void BSHangover_Jail_1(string q)
{
	sld = CharacterFromID("BridgetownJailOff");
	SaveOldDialog(sld);
	sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
	sld.dialog.currentnode = "BS_F1_SearchStinger";
}

void BSHangover_StingerFound(string q)
{
	chrDisableReloadToLocation = true;
	LockWeapons("");
	sld = CharacterFromID("BS_Silver");
	Lai_SetStayTypeNoGroup(sld);
	sld.talker = 10;
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto61");
	sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
	sld.dialog.currentnode = "BS_F1_19";
}
void BSHangover_VeinFollows(string q)
{
	sld = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto1");
	Lai_SetActorTypeNoGroup(sld);
	LAi_ActorFollowEverywhere(sld, "", -1);

	LocatorReloadEnterDisable("Bridgetown_town", "gate_back", true);
	LocatorReloadEnterDisable("Bridgetown_town", "gate1_back", true);
	LocatorReloadEnterDisable("Bridgetown_town", "reload1_back", true);
	LocatorReloadEnterDisable("Bridgetown_town", "reload2_back", true);
	LocatorReloadEnterDisable("Bridgetown_exittown", "reload1_back", true);
}

void BSHangover_FewDaysLater()
{
	WaitDate("",0,0,3,3,3);
	SetLaunchFrameFormParam("Несколько дней спустя...", "", 0.1, 2.0);
	LaunchFrameForm();
	DoQuestFunctionDelay("BSHangover_FewDaysLater_Reload", 2.0);
}

void BSHangover_FewDaysLater_Reload(string q)
{
	DoReloadCharacterToLocation("Bridgetown_tavern_upstairs","goto","goto1");
	pchar.quest.BSHangover_horse.win_condition.l1          = "location";
	pchar.quest.BSHangover_horse.win_condition.l1.location = "Bridgetown_tavern_upstairs";
	pchar.quest.BSHangover_horse.function             = "BSHangover_horse";
}

void BSHangover_horse(string q)
{
	sld = CharacterFromID("BS_Vein");
	Lai_SetStayTypeNoGroup(sld);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto1");
	sld = GetCharacter(NPC_GenerateCharacter("BSHangover_horse", "horse0"+(rand(7)+1), "woman", "woman", 1, PIRATE, 0, false));
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
	sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
	sld.dialog.currentnode = "BS_F1_29";
	Lai_SetStayTypeNoGroup(sld);
	sld.talker = 10;

	LocatorReloadEnterDisable("Bridgetown_town", "gate_back", false);
	LocatorReloadEnterDisable("Bridgetown_town", "gate1_back", false);
	LocatorReloadEnterDisable("Bridgetown_town", "reload1_back", false);
	LocatorReloadEnterDisable("Bridgetown_town", "reload2_back", false);
	LocatorReloadEnterDisable("Bridgetown_exittown", "reload1_back", false);
	LocatorReloadEnterDisable("Shore5", "boat", true);

	pchar.LockMapReload = "Чёрта с два я уплыву отсюда без Флинта!";

	pchar.quest.BSHangover_Cave.win_condition.l1          = "location";
	pchar.quest.BSHangover_Cave.win_condition.l1.location = "barbados_cave";
	pchar.quest.BSHangover_Cave.function             = "BSHangover_Cave";

	if (WhisperIsOfficer())
	{
		sld = CharacterFromID(pchar.WhisperId);
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto1");
	}
}

void BSHangover_Cave(string q)
{
	chrDisableReloadToLocation = true;
	LAi_LocationDisableMonGenTimer("barbados_cave", 3);
	pchar.DisableToughSkeleton = true;

	sld = CharacterFromID("BS_Silver");
	ChangeCharacterAddressGroup(sld, pchar.location, "item", "berglar1");
	LAi_SetWarriorType(sld);
	//LAi_SetHP(sld, 2000, 2000);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	LAi_SetImmortal(sld, true);
	DoQuestFunctionDelay("BSHangover_SilverMortality", 35);

	string cnd;
	for (int i = 1; i <= 12; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("DeSouzaHunter"+sti(i), "OZG_" + (rand(6) + 1), "man", "man", sti(pchar.rank)+MOD_SKILL_ENEMY_RATE * 2, PIRATE, 0, true));

		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
		sld.LifeDay = 0;

		cnd = "l" + i;
		pchar.quest.BSHangover_CaveAfterBattle.win_condition.(cnd) = "NPC_Death";
		pchar.quest.BSHangover_CaveAfterBattle.win_condition.(cnd).character ="DeSouzaHunter"+sti(i);

		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto"+i);
	}
	PChar.quest.BSHangover_CaveAfterBattle.function = "BSHangover_CaveAfterBattle";
	LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
}

void BSHangover_CaveAfterBattle(string qName)
{
	sld = CharacterFromID("BS_Silver");
	sld.dialog.currentnode   = "BS_F1_32";
	if(LAi_IsDead(sld))
	{
		DeleteCharacter(sld);
		LAi_SetCurHPMax(sld);
		DoQuestFunctionDelay("BSHangover_CaveAfterBattle_1", 0);
		sld.dialog.currentnode   = "BS_F1_32_beaten";
	}
	else
	{
		LAi_SetActorTypeNoGroup(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}

	pchar.quest.BSHangover_CaveEntrance.win_condition.l1          = "location";
	pchar.quest.BSHangover_CaveEntrance.win_condition.l1.location = "barbados_CaveEntrance";
	pchar.quest.BSHangover_CaveEntrance.function             = "BSHangover_CaveEntrance";
}

void BSHangover_CaveAfterBattle_1(string qName)
{
	sld = CharacterFromID("BS_Silver");
	LAi_SetGroundSitTypeNoGroup(sld);
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, pchar.location, "item", "berglar1");
	sld.CantLoot = true;
	//LAi_SetActorTypeNoGroup(sld);
	//LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void BSHangover_SilverMortality(string qName)
{
	sld = CharacterFromID("BS_Silver");
	LAi_SetImmortal(sld, false);
	sld.DontClearDead = true;
}

void BSHangover_CaveEntrance(string qName)
{
	PChar.quest.BSChaseBegun_Fail.over = "yes";
	PChar.quest.BSUrka_Fail1.over = "yes";
	PChar.quest.BSUrka_Fail2.over = "yes";
	PChar.quest.BSUrka_Curacao_EndSeaBattle.over = "yes";
	PChar.quest.BSUrka_SeaBattleEnded.over = "yes";
	pchar.quest.BSCourtlyPassions_DontStart.over = "yes";
	chrDisableReloadToLocation = true;
	DeleteAttribute(pchar, "DisableToughSkeleton");

	for (int i = 1; i <= 4; i++)
	{
		if(i == 1)	sld = CharacterFromID("BS_Vein");
		if(i == 2)	sld = CharacterFromID("BS_Silver");
		if(i == 3)	sld = CharacterFromID("BS_Rakham");
		if(i == 4)	sld = CharacterFromID("BS_Bony");
		LAi_SetHP(sld, 1000 - MOD_SKILL_ENEMY_RATE * 50, 1000);
		ChangeCharacterAddressGroup(sld, pchar.location, "enc01", "enc01_02");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_SetImmortal(sld, false);
		sld.DontClearDead = true;
		sld.CantLoot = true;
	}

	string cnd;
	for (i = 1; i <= 20; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("DeSouzaHunter"+sti(i), "OZG_" + (rand(6) + 1), "man", "man", sti(pchar.rank)+MOD_SKILL_ENEMY_RATE * 2, PIRATE, 0, true));

		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
		sld.LifeDay = 0;

		cnd = "l" + i;
		pchar.quest.BSHangover_CaveEntranceAfterBattle.win_condition.(cnd) = "NPC_Death";
		pchar.quest.BSHangover_CaveEntranceAfterBattle.win_condition.(cnd).character ="DeSouzaHunter"+sti(i);

		ChangeCharacterAddressGroup(sld, PChar.location, "monsters", "monster"+(rand(2)+1));
	}
	PChar.quest.BSHangover_CaveEntranceAfterBattle.function = "BSHangover_CaveEntranceAfterBattle";
	LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
}

void BSHangover_CaveEntranceAfterBattle(string qName)
{
	AddQuestRecord("BSHangover", "8");
	BSHangover_IsEveryoneOkay();
	DoQuestFunctionDelay("BSHangover_CaveEntranceAfterBattle_2", 3);
	DoQuestFunctionDelay("BSHangover_CaveEntranceAfterBattle_1", 5);

	sld = CharacterFromID("Flint");
	sld.AlwaysEnemy = true;
	DeleteAttribute(sld, "AlwaysFriend");
	BSRepairShip(sld);
	DeleteAttribute(sld, "Abordage.Enable");
	//LAi_SetHP(sld, 50, 50);
	sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
	sld.dialog.currentnode = "BS_F1_35";
	LAi_SetImmortal(sld, false);
	pchar.FlintBoardingDialog = true;
	Group_SetAddress("Flint_Group", "Barbados", "Quest_ships", "quest_ship_7");
}

void BSHangover_CaveEntranceAfterBattle_2(string qName)
{
	if (WhisperIsHere())
	{
		SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
		StartInstantDialogNoType(pchar.WhisperPGG, "BS_12_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
	}
}
void BSHangover_CaveEntranceAfterBattle_1(string qName)
{
	sld = CharacterFromID("BS_Vein");
	Lai_SetStayTypeNoGroup(sld);
	sld.dialog.currentnode = "BS_F1_34";
	sld.talker = 10;
}

void BSHangover_IsEveryoneOkay()
{
	for (int i = 1; i <= 4; i++)
	{
		if(i == 1)	sld = CharacterFromID("BS_Vein");
		if(i == 2)	sld = CharacterFromID("BS_Silver");
		if(i == 3)	sld = CharacterFromID("BS_Rakham");
		if(i == 4)	sld = CharacterFromID("BS_Bony");
		Lai_SetActorTypeNoGroup(sld);
		if(LAi_IsDead(sld))
		{
			if(!CheckAttribute(pchar, "BSHangover_IsEveryoneOkay"))
			{
				pchar.BSHangover_IsEveryoneOkay = true;
				SetLaunchFrameFormParam("Битва окончена. Ваши компаньоны постепенно приходят в себя", "", 0.1, 2.0);
				LaunchFrameForm();
			}
			DeleteCharacter(sld);
			LAi_SetCurHPMax(sld);
			sld.RezMe = true;
			DoQuestFunctionDelay("BSHangover_IsEveryoneOkay_1", 0);
		}
	}

	pchar.quest.BSHangover_Fail1.win_condition.c1 = "NPC_Death";
	pchar.quest.BSHangover_Fail1.win_condition.c1.character ="Flint";
	PChar.quest.BSHangover_Fail1.function = "BSHangover_Fail";

	pchar.quest.BSHangover_Fail1.win_condition.c1 = "BS_Vein";
	pchar.quest.BSHangover_Fail1.win_condition.c1.character ="Flint";
	PChar.quest.BSHangover_Fail1.function = "BSHangover_Fail";
}

void BSHangover_IsEveryoneOkay_1(string q)
{
	for (int i = 1; i <= 4; i++)
	{
		if(i == 1)	sld = CharacterFromID("BS_Vein");
		if(i == 2)	sld = CharacterFromID("BS_Silver");
		if(i == 3)	sld = CharacterFromID("BS_Rakham");
		if(i == 4)	sld = CharacterFromID("BS_Bony");

		if(CheckAttribute(sld, "RezMe"))
		{
			DeleteAttribute(sld, "RezMe")
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto1");
		}
	}
}

void BSHangover_Fail(string q)
{
	CloseQuestHeader("BSHangover");
	EraseBSCharacters();
}
void BSHangover_FlintFight()
{
	for (int i = 1; i <= 6; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("FlintOff"+i, "officer_" + (rand(62)+2), "man", "man", sti(pchar.rank) + MOD_SKILL_ENEMY_RATE, PIRATE, 0, true));
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_BRDENEMY);
	}
	DoQuestFunctionDelay("BSHangover_FlintFight_1", 3);
	DoQuestFunctionDelay("BSHangover_FlintFight_2", 15);
	if (WhisperIsOfficer())
	{
		DoQuestFunctionDelay("BSHangover_FlintFight_3", 8);
		DoQuestFunctionDelay("BSHangover_FlintFight_4", 30);
	}
}

void BSHangover_FlintFight_1(string q)
{
	Log_Info("На подмогу Флинту приходит один из его офицеров!");
	sld = CharacterFromID("FlintOff1");
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
}

void BSHangover_FlintFight_2(string q)
{
	Log_Info("На подмогу Флинту приходит ещё несколько офицеров!");
	sld = CharacterFromID("FlintOff2");
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
	sld = CharacterFromID("FlintOff3");
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
}

void BSHangover_FlintFight_3(string q)
{
	Log_Info("Виспер приходит к вам на подмогу!");
	sld = CharacterFromID(pchar.WhisperId);
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
}

void BSHangover_FlintFight_4(string q)
{
	Log_Info("Вся кают-компания собралась здесь чтобы помочь Флинту!");
	sld = CharacterFromID("FlintOff4");
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
	sld = CharacterFromID("FlintOff5");
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
	sld = CharacterFromID("FlintOff6");
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
}

void BSHangover_MaksOnShip(string q)
{
	BS_RestoreMaksHostess("");
	pchar.quest.BSHangover_FlintEscaped.win_condition.l1          = "location";
	pchar.quest.BSHangover_FlintEscaped.win_condition.l1.location = "pirates_town";
	pchar.quest.BSHangover_FlintEscaped.function             = "BSHangover_FlintEscaped";
}
void BSHangover_FlintEscaped(string q)
{
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
	sld = BSTutorialSailor();
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
	chrDisableReloadToLocation = true;
	LAi_SetActorType(sld);
	sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
	sld.dialog.currentnode = "BS_F1_41";
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	LAi_SetImmortal(sld, true);
}

void BSHangover_TownHall(string q)
{
	ref chr;
	chr = CharacterFromID("gatri_temp");
	//ChangeCharacterAddressGroup(chr, "Pirates_townhall", "goto", "goto3");
	LAi_SetActorType(chr);
	LAi_SetStayTypeNoGroup(chr);
	chr.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
	chr.dialog.currentnode = "BS_F1_48";
	chr.talker = 10;

	chr = CharacterFromID("BS_Rakham");
	ChangeCharacterAddressGroup(chr, "Pirates_townhall", "goto", "goto5");
	LAi_SetActorType(chr);

	chr = CharacterFromID("BS_Vein");
	ChangeCharacterAddressGroup(chr, "Pirates_townhall", "goto", "goto5");
	LAi_SetActorType(chr);

	chr = CharacterFromID("BS_Bony");
	ChangeCharacterAddressGroup(chr, "Pirates_townhall", "goto", "goto1");
	LAi_SetActorType(chr);

	chr = CharacterFromID("BS_Silver");
	ChangeCharacterAddressGroup(chr, "Pirates_townhall", "goto", "goto3");
	LAi_SetActorType(chr);

	chr = CharacterFromID("BS_Maks");
	ChangeCharacterAddressGroup(chr, "Pirates_townhall", "goto", "goto3");
	LAi_SetActorType(chr);
}


void BSHangover_Cutscene(string q)
{
	FreeSitLocator("Pirates_tavern", "sit_front4");  // очистим стул
	FreeSitLocator("Pirates_tavern", "sit_front1");  // очистим стул
	FreeSitLocator("Pirates_tavern", "sit_base4");  // очистим стул
	FreeSitLocator("Pirates_tavern", "sit_base1");  // очистим стул
	ChangeCharacterAddressGroup(pchar, "Pirates_tavern", "sit", "sit_base4");

	LAi_SetSitTypeNoGroup(pchar);
	DoQuestFunctionDelay("BSHangover_Cutscene_0", 0);
}
void BSHangover_Cutscene_0(string q)
{
	DoQuestFunctionDelay("BSHangover_Cutscene_1", 5);
	if (WhisperIsHere())
	{
		sld = CharacterFromID(pchar.WhisperId);
		ChangeCharacterAddressGroup(sld, "Pirates_tavern", "sit", "sit_front4");
		LAi_SetSitTypeNoGroup(sld);
	}
}
void BSHangover_Cutscene_1(string q)
{
	SetLaunchFrameFormParam("Прошло три часа", "", 0.1, 2.0);
	LaunchFrameForm();
	WaitDate("",0,0,0,3,3);
	if (WhisperIsHere())
	{
		SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
		StartInstantDialogNoType(pchar.WhisperPGG, "BS_13_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
	}
	else
	{
		DoQuestFunctionDelay("BSHangover_Cutscene_2", 5);
	}
}
void BSHangover_Cutscene_2(string q)
{
	ChangeCharacterAddressGroup(pchar, "Pirates_tavern", "goto", "goto4");
	LAi_SetPlayerType(pchar);
	AddQuestRecord("BSHangover", "12");
	pchar.quest.BSHangover_FirstEnding.win_condition.l1          = "location";
	pchar.quest.BSHangover_FirstEnding.win_condition.l1.location = "pirates_townhall";
	pchar.quest.BSHangover_FirstEnding.function             = "BSHangover_FirstEnding";
}

void BSHangover_FirstEnding(string q)
{
	ref chr;
	chr = CharacterFromID("BS_Silver");
	LAi_SetStayTypeNoGroup(chr);
	chr.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
	chr.dialog.currentnode = "BS_F1_53";
	chr.talker = 10;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- Тяжелое похмелье --     конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////
