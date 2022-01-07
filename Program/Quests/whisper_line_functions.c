
void Whisper_StartGame(string qName)
{
    ref sld;
    Pchar.questTemp.WhisperTutorial = true;
    Pchar.questTemp.WhisperFuture = true;
    Pchar.BaseNation = PIRATE;
    //fix перков флагов
    DeleteAttribute(Pchar, "perks.list.FlagFra");
    DeleteAttribute(Pchar, "perks.list.FlagSpa");
    DeleteAttribute(Pchar, "perks.list.FlagHol");
	DeleteAttribute(Pchar, "perks.list.FlagEng");
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Линейка Виспер	начало
/////////////////////////////////////////////////////////////////////////////////////////////////////////
    SetCharacterPerk(Pchar, "FlagPir");
    Flag_Change(SPAIN);

    //Обираем до нитки
    RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
    RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
    RemoveCharacterEquip(pchar, SPYGLASS_ITEM_TYPE);
    RemoveCharacterEquip(pchar, PATENT_ITEM_TYPE);
	RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
	RemoveCharacterEquip(pchar, MAPS_ITEM_TYPE);
    DeleteAttribute(Pchar, "items");
	//DeleteAttribute(Pchar, "equip");
    DeleteAttribute(Pchar, "ship");
    DeleteAttribute(Pchar, "ShipSails.gerald_name");
    Pchar.ship.type = SHIP_NOTUSED;
	//Одеваемся подходящим образом
	GiveItem2Character(pchar, "blade_whisper");
	EquipCharacterByItem(pchar, "blade_whisper");
	GiveItem2Character(pchar, "pistol7shotgun");
	EquipCharacterByItem(pchar, "pistol7shotgun");
	GiveItem2Character(pchar, "cirass5");
	EquipCharacterbyItem(pchar, "cirass5");
    TakeNItems(Pchar, "12_gauge", 99);
    TakeNItems(Pchar, "grapeshot", 18 - MOD_SKILL_ENEMY_RATE);
	TakeNItems(Pchar, "potion3", 1);
    TakeNItems(Pchar, "potion2", 3);
    TakeNItems(Pchar, "potion1", 4);
	LAi_SetCharacterUseBullet(pchar,"grapeshot");
	Pchar.model="PGG_Whisper_5_NoHat";
	SetNewModelToChar(Pchar);

	Locations[FindLocation("Pirates_Shipyard")].id.label = "";
	Locations[FindLocation("Shore3")].id.label = "";

	//Запретить выход из локации
	chrDisableReloadToLocation = true;
	//Заблокировать меню персонажа
	//bDisableCharacterMenu = true;
	//и фасттревел
	InterfaceStates.DisFastTravel = true;
	//Виспер недоступна испанская линейка
	//LockQuestLine(characterFromId("spa_guber"));

	//Вступительный монолог
	pchar.questTemp.Whisper.Entered_Dungeon = true;
	DoQuestCheckDelay("TalkSelf_Quest", 1.0);

	//worldMap.date.year = 2065;
    //Environment.date.month = 7;
    //Environment.date.day = 3;

	ref _location = &locations[reload_location_index];
	_location.box1.QuestClosed = true;
	_location.box2.QuestClosed = true;
	_location.box3.QuestClosed = true;
	_location.box4.QuestClosed = true;

	//Спавним роботов
	for (int i = 0; i < 10; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Robot"+sti(i), "Terminator", "Terminator_Sex", "Terminator", MOD_SKILL_ENEMY_RATE, PIRATE, 0, false));
		sld.name = "Т-"+(800+rand(150));
		sld.lastname = "";
		sld.CantLoot = true;
		if (rand (1) == 0)
		{
			GiveItem2Character(sld, "katar");
			EquipCharacterByItem(sld, "katar");
		}
		else
		{
			GiveItem2Character(sld, "blade14");
			EquipCharacterByItem(sld, "blade14");
		}
		LAi_SetHP(sld, 10.0 * MOD_SKILL_ENEMY_RATE, 10.0 *MOD_SKILL_ENEMY_RATE);
		if (MOD_SKILL_ENEMY_RATE == 10)
		{
			SetCharacterPerk(sld, "Sliding");
		}
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
		sld.LifeDay = 0;
	}
	sld = characterFromID("Robot0");
	ChangeCharacterAddressGroup(sld, PChar.location, "monsters", "monster32");
	sld = characterFromId("Robot1");
	ChangeCharacterAddressGroup(sld, PChar.location, "monsters", "monster31");
	sld = characterFromId("Robot2");
	ChangeCharacterAddressGroup(sld, PChar.location, "monsters", "monster5");
	sld = characterFromId("Robot3");
	ChangeCharacterAddressGroup(sld, PChar.location, "monsters", "monster8");
	sld = characterFromId("Robot4");
	ChangeCharacterAddressGroup(sld, PChar.location, "monsters", "monster6");
	sld = characterFromId("Robot5");
	ChangeCharacterAddressGroup(sld, PChar.location, "monsters", "monster11");
	sld = characterFromId("Robot6");
	ChangeCharacterAddressGroup(sld, PChar.location, "monsters", "monster17");
	sld = characterFromId("Robot7");
	ChangeCharacterAddressGroup(sld, PChar.location, "monsters", "monster18");
	sld = characterFromId("Robot8");
	ChangeCharacterAddressGroup(sld, PChar.location, "monsters", "monster19");
	sld = characterFromId("Robot9");
	ChangeCharacterAddressGroup(sld, PChar.location, "monsters", "monster24");

	PChar.quest.WhisperScientist.win_condition.l1 = "locator";
	PChar.quest.WhisperScientist.win_condition.l1.location = "Bermudes_Dungeon";
	PChar.quest.WhisperScientist.win_condition.l1.locator_group = "box";
	PChar.quest.WhisperScientist.win_condition.l1.locator = "box1";
	PChar.quest.WhisperScientist.function = "WhisperScientist";
}

void WhisperScientist(string qName)
{

	for (i = 1; i <= PsHeroQty; i++)
	{
		sld = CharacterFromID("PsHero_" + i);

		if(sld.FaceId == 487 || sld.FaceId == 535 || sld.FaceId == 211)
		{//Его мы позже наймем оффом, так что убираем из ПГГ
			sld.willDie = true;
			LAi_KillCharacter(sld);
		}
	}
	pchar.questTemp.Whisper.Near_Chest = true;
	PlayVoice("interface\important_item.wav");
	StartActorSelfDialog("First time");
	sld = GetCharacter(NPC_GenerateCharacter("CrazyScientist", "CCS_Mechanic", "man", "man", 30, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 1, 20, 20, "", "", 80);
	ChangeCharacterAddressGroup(sld, PChar.location, "monsters", "monster25");
	sld.dialog.filename = "Quest\WhisperLine\Whisper.c";
	sld.name = "Альберт";
	sld.lastname = "Маск";
	sld.dialog.currentnode = "First time";
	//sld.greeting = "cit_common";
	//Добавить звуки
	Group_FindOrCreateGroup("Scientist");
	Group_AddCharacter("Scientist", sld.id);
    LAi_SetActorType(sld);
    LAi_type_actor_Reset(sld);
    LAi_ActorDialog(sld, pchar, "", -1, 0);
	LAi_SetHP(sld, 5.0, 5.0);
	LAi_SetImmortal(sld, true);
	sld.LifeDay = 0;

	sld = GetCharacter(NPC_GenerateCharacter("FinalBot", "Terminator", "Terminator_Sex", "Terminator", 55, PIRATE, 0, false));
	FantomMakeCoolFighter(sld, 1, 20, 20, "", "pistol7", 80);
	sld.dialog.filename = "Quest\WhisperLine\Whisper.c";
	sld.name = "Т-911";
	sld.lastname = "";
	sld.dialog.currentnode = "First time";
	//sld.greeting = "cit_common";
	LAi_group_MoveCharacter(sld, sTemp);
    LAi_SetStayTypeNoGroup(sld);
   	LAi_SetImmortal(sld, true);
	sld.talker = 10;
	ChangeCharacterAddressGroup(sld, "Bermudes_Dungeon", "item", "duhi1");
	DoQuestFunctionDelay("TeleportBot", 0.5);
}

void TeleportBot(string qName)
{
	sld = CharacterFromID("FinalBot");
	switch (rand(2))
	{
		case 0:
		TeleportCharacterToPos(sld, -36.0, -0.11696, -18.0);
		break;
		case 1:
		TeleportCharacterToPos(sld, -3.8456, -0.11696, -15.0);
		break;
		case 2:
		TeleportCharacterToPos(sld, 16.0, -0.11696, 20.0);
		break;
	}
}
void WhisperTeleport(string qName)
{
	Locations[FindLocation("Pirates_Shipyard")].id.label = "Shipyard";
	Locations[FindLocation("Shore3")].id.label = "Shore3";

	InterfaceStates.Buttons.Save.enable = false;
	pchar.questTemp.WhisperLine = false;
	sld = GetCharacter(NPC_GenerateCharacter("wl_Pirate_Cap", "PGG_Rozencraft", "man", "man", 1, PIRATE, -1, true));
	sld.dialog.filename = "Quest\WhisperLine\Whisper.c";
	GiveItem2Character(sld, "blade15");
	EquipCharacterByItem(sld, "blade15");
	sld.dialog.currentnode = "First time";
	sld.name = "Эрнан";
	sld.lastname = " Эстебан";
	sld.greeting = "GR_ErnanEsteban";

	LAi_SetStayTypeNoGroup(sld);
	sld.talker = 10;
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto11");

	Group_FindOrCreateGroup("wl_Pirate");
	Group_AddCharacter("wl_Pirate", sld.id);
	string cnd, fnk;

	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);

	for (i = 1; i < 13; i++)
	{
			sld = GetCharacter(NPC_GenerateCharacter("wl_Pirate_"+sti(i), "pirate_"+sti(rand(25)+1), "man", "man", 3+MOD_SKILL_ENEMY_RATE, PIRATE, -1, true));
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto"+sti(i));
			Group_AddCharacter("wl_Pirate", sld.id);
			LAi_SetWarriorType(sld);
			sld.chr_ai.disableDlg = true;
			sld.DontClearDead = true;
			sld.LifeDay = 0;
			cnd = "l" + i;
			fnk = "WhisperBonusChallengeRecheck"+i;
			//pchar.quest.WhisperBonusChallenge.win_condition.(cnd) = "NPC_Death";
			//pchar.quest.WhisperBonusChallenge.win_condition.(cnd).character = "wl_Pirate_"+sti(i);
			//pchar.quest.WhisperBonusChallenge.function = "WhisperBonusChallenge";
			pchar.quest.(fnk).win_condition.(cnd) = "NPC_Death";
			pchar.quest.(fnk).win_condition.(cnd).character = "wl_Pirate_"+sti(i);
			pchar.quest.(fnk).function = "WhisperBonusChallengeReCheck";
	}
}


void WhisperBonusChallengeReCheck(string qName)
{
	if (!CheckAttribute(pchar, "Whisper.BonusEnergy"))
	{
		int n = 1;
		for (int i = 1; i < 13; i++)
		{
			if(LAi_IsDead(CharacterFromID("wl_Pirate_"+sti(i))))
			{
				n++;
			}
		}
		if(n >= 10)
		{
			DoQuestFunctionDelay("WhisperBonusChallenge", 0.5);
		}
	}
}

void WhisperBonusChallenge(string qName)
{
	AddBonusEnergyToCharacter(pchar, MOD_SKILL_ENEMY_RATE);
	pchar.Whisper.BonusEnergy = true;

	for (int i = 0; i < 3; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("wl_Pirate_mush"+i, GetPirateMushketerModel(), "man", "mushketer", 777, PIRATE, 0, false));
		//LAi_SetCharacterUseBullet(sld,"bullet");
		Group_AddCharacter("wl_Pirate", sld.id);
		LAi_SetWarriorType(sld);
		TakeNItems(sld,"potion1", rand(2)+1);
		LAi_warrior_DialogEnable(sld, false);
		ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
		LAi_SetImmortal(sld, true);

		sld = GetCharacter(NPC_GenerateCharacter("wl_Pirate_sword"+sti(i), "pirate_"+sti(rand(25)+1), "man", "man", 777, PIRATE, 0, true));
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto"+sti(i));
		ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
		LAi_SetImmortal(sld, true);
		Group_AddCharacter("wl_Pirate", sld.id);
		LAi_SetWarriorType(sld);
	}
}
	void WhisperHold(string qName)
{
    //chrDisableReloadToLocation = true;
    //InterfaceStates.Launched = false;
    InterfaceStates.Buttons.Save.enable = true;

	//LAi_QuestFader.oldSaveState = InterfaceStates.Buttons.Save.enable;
	//InterfaceStates.Buttons.Save.enable = 0;

	//Возвращаем все после плена
    LAi_SetCurHPMax(Pchar);
    LAi_SetPlayerType(Pchar);
    //Рабство
    LAi_SetImmortal(Pchar, false);
    DeleteAttribute(Pchar, "items");
    DeleteAttribute(Pchar, "equip");

    DeleteAttribute(Pchar, "ship");
    DeleteAttribute(Pchar, "ShipSails.gerald_name");
    Pchar.ship.type = SHIP_NOTUSED;
    Pchar.money = 0;

	bDisableCharacterMenu = false;

    DoReloadCharacterToLocation("My_Deck", "rld", "aloc1");
	DoQuestFunctionDelay("WhisperHoldInit", 1.5);

}


void WhisperHoldInit(string qName)
{
    //Передаем нашу экипировку пирату
	sld = CharacterFromID("wl_Pirate_Cap");
	DeleteAttribute(sld, "equip");
	ChangeCharacterAddressGroup(sld, "My_Deck", "reload", "reload1");
	GiveItem2Character(sld, "blade_whisper");
	EquipCharacterByItem(sld, "blade_whisper");
	GiveItem2Character(sld, "pistol4");
	EquipCharacterByItem(sld, "pistol4");
    TakeNItems(sld, "GunPowder", 99);
    TakeNItems(sld, "bullet", 99);

	LAi_SetActorTypeNoGroup(sld);
    LAi_type_actor_Reset(sld);
    LAi_ActorDialog(sld, pchar, "", 20.0, 0);
	LAi_SetImmortal(sld, true);
}

void WhisperLine_Inquisition(string qName)
{
	DoReloadCharacterToLocation("Santiago_Incquisitio","reload","reload1");
	DoQuestFunctionDelay("WhisperLine_Cage", 1.2);
}
void WhisperLine_Cage(string qName)
{
	TeleportCharacterToPos(pchar, -5.36, -1.96, -0.97);

	bDisableLandEncounters = true;

	//sld = GetCharacter(NPC_GenerateCharacter("AntonioDeSouza", "priest", "man", "man", 10, SPAIN, -1, false));
	sld = GetCharacter(NPC_GenerateCharacter("AntonioDeSouza", "PGG_Vincento_0", "man", "man", 10, SPAIN, -1, false));
   	sld.name 	= "Антониу";
    sld.lastname = "де Соуза";
    sld.Dialog.Filename = "Quest\WhisperLine\Whisper.c";
	sld.greeting = "GR_DeSouza";
    LAi_SetHuberType(sld);
    LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
    ChangeCharacterAddressGroup(sld, "Santiago_Incquisitio", "goto", "goto5");

	LAi_SetActorTypeNoGroup(sld);
    LAi_type_actor_Reset(sld);
    //LAi_ActorDialog(sld, pchar, "", 20.0, 0);
	SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 4.0);
	LAi_SetImmortal(sld, true);

	LAi_SetActorType(pchar);
	LAi_ActorTurnToCharacter(pchar, sld);

}

void WhisperLine_DeSouzaHits(string qName)
{
	sld = characterFromId("AntonioDeSouza");
	LAi_SetActorTypeNoGroup(PChar);
    LAi_SetActorTypeNoGroup(sld);
    LAi_ActorTurnToCharacter(pchar, sld);
	switch (2)
	{
		case 0:
			LAi_ActorAnimation(sld, "attack_fast_"+sti(rand(2)+1), "", 0.6);
			DoQuestFunctionDelay("WhisperLine_DeSouzaHits_1", 0.5);
		break;
		case 1:
			LAi_ActorAnimation(sld, "attack_force_"+sti(rand(3)+1), "", 0.6);
			DoQuestFunctionDelay("WhisperLine_DeSouzaHits_1", 0.5);
		break;
		case 2:
			LAi_ActorAnimation(sld, "attack_break_1", "", 2.9);
			DoQuestFunctionDelay("WhisperLine_DeSouzaHits_1", 1.0);
		break;
	}

}

void WhisperLine_WhisperHits(string qName)
{
	sld = characterFromId(pchar.Whisper.IncqGuard_bad);
	LAi_SetActorTypeNoGroup(PChar);
	RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
	TakeNItems(sld, "pistol3", -1);
	LAi_ActorAnimation(pchar, "Shot", "", 1.9);
    DoQuestFunctionDelay("WhisperLine_WhisperHits_1", 0.8);
}
void WhisperLine_WhisperHits_1(string qName)
{
	sld = characterFromId(pchar.Whisper.IncqGuard_bad);
	LAi_KillCharacter(sld);
    DoQuestFunctionDelay("WhisperLine_WhisperHits_2", 0.25);
}
void WhisperLine_WhisperHits_2(string qName)
{
	//LAi_LockFightMode(PChar, false);
	Lai_SetPlayerType(pchar);
	RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
	TakeNItems(pchar, "pistol3", -1);
	pchar.questTemp.Whisper.Inside_Incquisition = true;
	DoQuestCheckDelay("TalkSelf_Quest", 1.3);
}
void WhisperLine_WhisperHits_3(string qName)
{
	for (i=1; i<=4; i++)
	{
		sld = characterFromId("IncqGuard_"+i);
		LAi_SetGuardianTypeNoGroup(sld);
	}
}
void WhisperLine_DeSouzaHits_1(string qName)
{
	LAi_ActorAnimation(pchar, "hit_attack_"+sti(rand(2)+1), "WhisperLine_DeSouzaHits_2", 0.1);
    DoQuestFunctionDelay("WhisperLine_DeSouzaHits_2", 0.5);
}

void WhisperLine_DeSouzaHits_2(string qName)
{
	sld = characterFromId("AntonioDeSouza");
	LAi_SetStayType(sld);

	if (pchar.Whisper.DeSouzaHits == 0)
	{
		LAi_SetActorTypeNoGroup(PChar);
		DoQuestFunctionDelay("WhisperLine_DeSouzaSpeaks", 0.5);
	}
	else
	{
		pchar.Whisper.DeSouzaHits = sti(pchar.Whisper.DeSouzaHits)-1;
		DoQuestFunctionDelay("WhisperLine_DeSouzaHits", 0.5);
	}
}
void WhisperLine_DeSouzaSpeaks(string qName)
{
	sld = characterFromId("AntonioDeSouza");
	LAi_SetActorTypeNoGroup(sld);
    LAi_type_actor_Reset(sld);
    //LAi_ActorDialog(sld, pchar, "", 20.0, 0);
	SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 4.0);
	LAi_SetImmortal(sld, true);
}

void WhisperLine_IncqGuard_bad_speaks(string qName)
{
	sld = characterFromId(pchar.Whisper.IncqGuard_bad);
	sld.dialog.currentnode = "IncqGuard_bad_wheel";
	SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 4.0);
}
void WhisperLine_IncqGuard(string qName)
{
	for (i=1; i<=4; i++)
	{
		sld = characterFromId("IncqGuard_"+i);
		TakeNItems(sld, "spyglass3", -1);
		LAi_SetHP(sld, 10+2.0 * MOD_SKILL_ENEMY_RATE, 10+2.0 *MOD_SKILL_ENEMY_RATE);
		RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
		TakeNItems(sld, "blade16", -10);
		TakeNItems(sld, "blade4", 1);
		EquipCharacterByItem(sld, "blade4");
		if (sld.Dialog.Filename == "Incquistors.c")
		{
			LAi_SetActorTypeNoGroup(sld);
			GetCharacterPos(sld, &locx, &locy, &locz);
			if (LAi_FindNearestLocator("soldiers", locx, locy, locz) == "soldier1")
			{
				float locx, locy, locz;
				GetCharacterPos(pchar, &locx, &locy, &locz);
				sld.Dialog.Filename = "Quest\WhisperLine\Whisper.c";
				if(!CheckAttribute(pchar, "Whisper.IncqGuard_bad"))
				{
					sld.dialog.currentnode = "IncqGuard";
				}
				else
				{
					sld.dialog.currentnode = "IncqGuard_bad";
					pchar.Whisper.IncqGuard_bad = sld.id;
					LAi_SetActorTypeNoGroup(sld);
					AddMoneyToCharacter(sld, 1500);
					TakeNItems(sld, "map_cuba", 1);
				}
				LAi_SetActorTypeNoGroup(sld);
				LAi_type_actor_Reset(sld);
				//LAi_ActorDialog(sld, pchar, "", 20.0, 0);
				SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
				LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 4.0);
				sld.LifeDay = 0;
			}
		}
		else
		{
			if(CheckAttribute(pchar, "Whisper.IncqGuard_bad"))
			{
				int weaponskill = 6 * MOD_SKILL_ENEMY_RATE;
				SetSelfSkill(sld, weaponskill, weaponskill, weaponskill, weaponskill, weaponskill);
				//LAi_group_Attack(sld, Pchar);
				//if (MOD_SKILL_ENEMY_RATE != 10)
				//{
					DeleteAttribute(sld, "perks.list.Sliding");
				//}
				TakeNItems(sld,"potion1", -5);
				TakeNItems(sld,"potion2", -5);
				pchar.quest.WhisperOpenTunnel.win_condition.l1 = "NPC_Death";
				pchar.quest.WhisperOpenTunnel.win_condition.l1.character = sld.id;
				pchar.quest.WhisperOpenTunnel.function = "WhisperOpenTunnel";
				TakeNItems(sld, "pistol3", -1);
				RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
			}
		}
	}
}

void WhisperOpenTunnel(string qName)
{
	PChar.quest.WhisperEscape.win_condition.l1 = "locator";
	PChar.quest.WhisperEscape.win_condition.l1.location = "Santiago_Incquisitio";
	PChar.quest.WhisperEscape.win_condition.l1.locator_group = "reload";
	PChar.quest.WhisperEscape.win_condition.l1.locator = "reload1_back";
	PChar.quest.WhisperEscape.function = "WhisperEscape";
}
void WhisperIncqAlarm(string qName)
{
	LAi_group_AttackGroup("SPAIN_CITIZENS", LAI_GROUP_PLAYER);
}
void WhisperEscape(string qName)
{
	Pchar.BaseNation = PIRATE;
	ChangeCharacterNationReputation(pchar, 2, -15);
	if (!CheckAttribute(pchar, "Whisper.Escaped"))
	{
		DoReloadCharacterToLocation("Santiago_ExitTown","reload","reload3");
		chrDisableReloadToLocation = false;
		LocatorReloadEnterDisable("Santiago_ExitTown", "reload3", true);
		LocatorReloadEnterDisable("Cuba_Jungle_03", "reload1_back", true);
		LocatorReloadEnterDisable("Cuba_Jungle_01", "reload3_back", true);
		LocatorReloadEnterDisable("Havana_ExitTown", "reload4", true);
		pchar.Whisper.Escaped = true;
		PChar.quest.WhisperPirateTown.win_condition.l1 = "location";
		PChar.quest.WhisperPirateTown.win_condition.l1.location = "PuertoPrincipe_town";
		PChar.quest.WhisperPirateTown.function = "WhisperPirateTown";
		if(CheckAttribute(pchar, "Whisper.IncqGuard_bad"))
		{
			pchar.questTemp.Whisper.Escaped_Incquisition = true;
			DoQuestCheckDelay("TalkSelf_Quest", 1.0);
		}
	}
}

void GiveMCItemToSomeoneElse(ref sld)
{
    ref ch = GetMainCharacter();
	String itemID;
    //trace("initMainCharacterItem "  + ch.HeroParam.HeroType);
	switch (ch.HeroParam.HeroType)
	{
        case "Master":	// Рубака
			SetCharacterPerk(sld, "Grunt");
            TakenItems(sld, "potion1", rand(10));
            TakenItems(sld, "potion2", rand(5));
            TakenItems(sld, "indian12", 1);
            TakenItems(sld, "Food1", rand(6)+4);
			switch (sti(ch.nation))
			{
				case ENGLAND:
					itemID = GetGeneratedItem("topor3");
					GiveItem2Character(sld, itemID);
					EquipCharacterbyItem(sld, itemID);
					GiveItem2Character(sld, "pistol2");
					EquipCharacterbyItem(sld, "Pistol2");
					TakeNItems(sld, "bullet", 5);
					AddItems(sld, "GunPowder", 5);
					GiveItem2Character(sld, "Spyglass1");
					EquipCharacterbyItem(sld, "Spyglass1");
					sld.money = 1500/MOD_SKILL_ENEMY_RATE;
				break;
				case FRANCE:
					itemID = GetGeneratedItem("topor3");
					GiveItem2Character(sld, itemID);
					EquipCharacterbyItem(sld, itemID);
					sld.money = 500/MOD_SKILL_ENEMY_RATE;
				break;
				case HOLLAND:
					itemID = GetGeneratedItem("topor1");
					GiveItem2Character(sld, itemID);
					EquipCharacterbyItem(sld, itemID);
					itemID = GetGeneratedItem("pistol" +  (rand(2)+1));
					GiveItem2Character(sld, itemID);
					EquipCharacterbyItem(sld, itemID);
					GiveGunAmmunitionPchar(sld,itemID,5);
					GiveItem2Character(sld, "Spyglass1");
					EquipCharacterbyItem(sld, "Spyglass1");
					sld.money = 1000/MOD_SKILL_ENEMY_RATE;
				break;
				case PIRATE:
					itemID = GetGeneratedItem("topor3");
					GiveItem2Character(sld, itemID);
					EquipCharacterbyItem(sld, itemID);
					itemID = GetGeneratedItem("pistol" + (rand(2)+1));
					GiveItem2Character(sld, itemID);
					EquipCharacterbyItem(sld, itemID);
					GiveGunAmmunitionPchar(sld,itemID,5);
				break;
				case SPAIN:
					itemID = GetGeneratedItem("topor3");
					GiveItem2Character(sld, itemID);
					EquipCharacterbyItem(sld, itemID);
					sld.money = 500/MOD_SKILL_ENEMY_RATE;
				break;
			}
	    break;

        case "Merchant":	// Торговец
			SetCharacterPerk(sld, "Trader");
			itemID = GetGeneratedItem("blade1");
            GiveItem2Character(sld, itemID);
            EquipCharacterbyItem(sld, itemID);
			GiveItem2Character(sld, "Ship_Print_6");
			TakenItems(sld, "potion1", rand(10));
			TakenItems(sld, "Food1", (rand(6)+4));
			switch (sti(ch.nation))
			{
				case ENGLAND:
					GiveItem2Character(sld, "Map_bad");
					TakeNItems(sld, "indian3", 1);
					sld.money = 15000/MOD_SKILL_ENEMY_RATE;
				break;
				case FRANCE:
					TakenItems(sld, "potion1", 2);
					TakeNItems(sld, "indian3", 1);
					GiveItem2Character(sld, "Spyglass1");
					EquipCharacterbyItem(sld, "Spyglass1");
					sld.money = 10000/MOD_SKILL_ENEMY_RATE;
				break;
				case HOLLAND:
					TakeNItems(sld, "indian3", 1);
					GiveItem2Character(sld, "Spyglass3");
					EquipCharacterbyItem(sld, "Spyglass3");
					sld.money = 11000/MOD_SKILL_ENEMY_RATE;
				break;
				case PIRATE:
					GiveItem2Character(sld, "Map_Normal");
					GiveItem2Character(sld, "pistol2");
					EquipCharacterbyItem(sld, "Pistol2");
					TakeNItems(sld, "bullet", 10);
					AddItems(sld, "GunPowder", 10);
					GiveItem2Character(sld, "Spyglass1");
					EquipCharacterbyItem(sld, "Spyglass1");
					sld.money = 5000/MOD_SKILL_ENEMY_RATE;
				break;
				case SPAIN:
					TakeNItems(sld, "indian14", 1);
					TakeNItems(sld, "jewelry8", 1);
					TakeNItems(sld, "jewelry9", 1);
					sld.money = 8000/MOD_SKILL_ENEMY_RATE;
				break;
			}
	    break;

	    case "Corsair":	// Фехтовальщик
			SetCharacterPerk(sld, "Fencer");
			itemID = GetGeneratedItem("Spyglass" + (rand(2)+1));
			GiveItem2Character(sld, itemID);
			EquipCharacterbyItem(sld, itemID);
			itemID = GetGeneratedItem("blade" + (rand(8)+1));
			GiveItem2Character(sld, itemID);
			EquipCharacterbyItem(sld, itemID);
			TakenItems(sld, "potion1", rand(10));
            TakenItems(sld, "Food1", rand(6)+4);
			itemID = GetGeneratedItem("pistol" + (rand(2)+1));
			GiveItem2Character(sld, itemID);
			EquipCharacterbyItem(sld, itemID);
			GiveGunAmmunitionPchar(sld,itemID,10);
			switch (sti(ch.nation))
			{
				case ENGLAND:
					sld.money = 500/MOD_SKILL_ENEMY_RATE;
				break;
				case FRANCE:
					GiveGunAmmunitionPchar(sld,itemID,10);
					sld.money = 1000/MOD_SKILL_ENEMY_RATE;
				break;
				case HOLLAND:
					sld.money = 500/MOD_SKILL_ENEMY_RATE;
				break;
				case PIRATE:
					GiveItem2Character(sld, "Map_part1");
				break;
				case SPAIN:
					sld.money = 2000/MOD_SKILL_ENEMY_RATE;
				break;
			}
	    break;

	    case "Adventurer":	// Авантюрист
			SetCharacterPerk(sld, "Adventurer");
			itemID = GetGeneratedItem("blade" + (rand(7)+1));
            GiveItem2Character(sld, itemID);
            EquipCharacterbyItem(sld, itemID);
			TakenItems(sld, "potion1", rand(10));
			GiveItem2Character(sld, "Totem_" + rand(15));
			GiveItem2Character(sld, "Totem_" + rand(15));
			GiveItem2Character(sld, "Totem_" + rand(15));
	        itemID = GetGeneratedItem("Spyglass" + rand(3));
			GiveItem2Character(sld, itemID);
			EquipCharacterbyItem(sld, itemID);
			sld.money = 3000/MOD_SKILL_ENEMY_RATE;
            TakenItems(sld, "Food1", rand(1)+2);
			itemID = GetGeneratedItem("pistol" + (rand(2)+1));
            GiveItem2Character(sld, itemID);
            EquipCharacterbyItem(sld, itemID);
			GiveGunAmmunitionPchar(sld,itemID,10);
			switch (sti(ch.nation))
			{
				case ENGLAND:
					itemID = GetGeneratedItem("blade7");
					GiveItem2Character(sld, itemID);
					EquipCharacterbyItem(sld, itemID);
				break;
				case FRANCE:
					GiveGunAmmunitionPchar(sld,itemID,10);
					itemID = GetGeneratedItem("blade12");
					GiveItem2Character(sld, itemID);
					EquipCharacterbyItem(sld, itemID);
				break;
				case HOLLAND:
					itemID = GetGeneratedItem("blade3");
					GiveItem2Character(sld, itemID);
					EquipCharacterbyItem(sld, itemID);
				break;
				case PIRATE:
					GiveGunAmmunitionPchar(sld,itemID,10);
					itemID = GetGeneratedItem("blade1");
					GiveItem2Character(sld, itemID);
					EquipCharacterbyItem(sld, itemID);
				break;
				case SPAIN:
					itemID = GetGeneratedItem("blade18");
					GiveItem2Character(sld, itemID);
					EquipCharacterbyItem(sld, itemID);
				break;
			}
	    break;

	    case "Inquisitor":	// Буканьер
			SetCharacterPerk(sld, "Buccaneer");
			itemID = GetGeneratedItem("blade" + (rand(7)+1));
            GiveItem2Character(sld, itemID);
            EquipCharacterbyItem(sld, itemID);
			itemID = GetGeneratedItem("pistol" +  (rand(2)+1));
            GiveItem2Character(sld, itemID);
            EquipCharacterbyItem(sld, itemID);
			itemID = GetGeneratedItem("mushket_drob");
            GiveItem2Character(sld, itemID);
			TakeNItems(sld, "bullet", 30);
			AddItems(sld, "GunPowder", 30);
			GiveGunAmmunitionPchar(sld,itemID,30);
			TakenItems(sld, "potion1", rand(10));
			sld.money = 1000/MOD_SKILL_ENEMY_RATE;
            TakenItems(sld, "Food1", rand(6)+4);
	    break;

	    case "SecretAgent":	// Тайный агент
			SetCharacterPerk(sld, "Agent");
			itemID = GetGeneratedItem("blade" + (rand(7)+1));
            GiveItem2Character(sld, itemID);
            EquipCharacterbyItem(sld, itemID);
			TakenItems(sld, "Food1", rand(6)+4);
			TakenItems(sld, "jewelry15", 1);
			TakenItems(sld, "Totem_2", 1);
			TakenItems(sld, "indian5", 1);
			TakenItems(sld, "indian17", 1);
			switch (sti(ch.nation))
			{
				case ENGLAND:
					GiveItem2Character(sld, "patent_eng");
				break;
				case FRANCE:
					GiveItem2Character(sld, "patent_fra");
				break;
				case HOLLAND:
					GiveItem2Character(sld, "patent_hol");
				break;
				case PIRATE:
					SetCharacterPerk(sld, "FlagEng");
					SetCharacterPerk(sld, "FlagFra");
					SetCharacterPerk(sld, "FlagSpa");
					SetCharacterPerk(sld, "FlagHol");
				break;
				case SPAIN:
					GiveItem2Character(sld, "patent_spa");
				break;
			}
	    break;

		case "SeaWolf":	// Морской Волк
			SetCharacterPerk(sld, "SeaWolf");
			itemID = GetGeneratedItem("blade" + (rand(7)+1));
            GiveItem2Character(sld, itemID);
            EquipCharacterbyItem(sld, itemID);
			GiveItem2Character(sld, "Ship_Print_6");
			itemID = GetGeneratedItem("pistol" +  (rand(2)+1));
            GiveItem2Character(sld, itemID);
            EquipCharacterbyItem(sld, itemID);
			GiveGunAmmunitionPchar(sld,itemID,10);
			TakenItems(sld, "potion1", rand(8));
			sld.money = 2000/MOD_SKILL_ENEMY_RATE;
            TakenItems(sld, "Food1", rand(6)+4);
	    break;
	}
}

void WhisperPirateTown(string qName)
{
	sld = GetCharacter(NPC_GenerateCharacter("NineFingers", "PGG_Alex_blade_0", "man", "man", 10, PIRATE, -1, false));
   	sld.name 	= "Девятипалый Билл";
	chrDisableReloadToLocation = true;
    sld.lastname = "";
    sld.Dialog.Filename = "Quest\WhisperLine\Whisper.c";

	GiveItem2Character(sld, "blade19");
	EquipCharacterByItem(sld, "blade19");
	//sld.greeting = "Gr_padre";
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_town", "goto", "goto5");

	LAi_SetActorTypeNoGroup(sld);
    LAi_type_actor_Reset(sld);
    SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 4.0);
	LAi_SetImmortal(sld, true);

	LAi_SetActorType(pchar);
	LAi_ActorTurnToCharacter(pchar, sld);

	sld = CharacterFromID("Beatrice");
	SaveOldDialog(sld);
	sld.dialog.filename = "Quest\WhisperLine\Whisper.c";
	sld.dialog.currentnode = "Beatrice";
	sld = CharacterFromID("Hugo_Lesopilka");
	SaveOldDialog(sld);
	sld.dialog.filename = "Quest\WhisperLine\Whisper.c";
	sld.dialog.currentnode = "Hugo_Lesopilka";
}

void WhisperPirateTownGetHat(string qName)
{
	InterfaceStates.Buttons.Save.enable = false;
	LocatorReloadEnterDisable("PuertoPrincipe_Town", "reload2", true);
	LocatorReloadEnterDisable("PuertoPrincipe_Town", "reload3", true);
	LocatorReloadEnterDisable("PuertoPrincipe_Town", "reload4", true);
	LocatorReloadEnterDisable("PuertoPrincipe_Town", "reload5", true);
	LocatorReloadEnterDisable("PuertoPrincipe_Town", "reload6", true);
	LocatorReloadEnterDisable("PuertoPrincipe_Town", "reload7", true);
	LocatorReloadEnterDisable("PuertoPrincipe_Town", "reload8", true);
	PlayVoice("VOICE\Russian\EvilPirates02.wav");
	SetLocationCapturedState("PuertoPrincipe_town", false);
}
void WhisperPirateTownGetHat_part_1(string qName)
{
	InterfaceStates.Buttons.Save.enable = true;
	//PlayVoice("VOICE\Russian\EvilPirates02.wav");
	sld = characterFromID("NineFingers");
	//sld.greeting = "Gr_padre";
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item12");
	LAi_SetActorTypeNoGroup(sld);
    LAi_type_actor_Reset(sld);
    SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 4.0);
	LAi_SetImmortal(sld, true);

	LAi_SetActorType(pchar);
	LAi_ActorTurnToCharacter(pchar, sld);

	LocatorReloadEnterDisable("PuertoPrincipe_Town", "reload2", false);
	LocatorReloadEnterDisable("PuertoPrincipe_Town", "reload3", false);
	LocatorReloadEnterDisable("PuertoPrincipe_Town", "reload4", false);
	LocatorReloadEnterDisable("PuertoPrincipe_Town", "reload5", false);
	LocatorReloadEnterDisable("PuertoPrincipe_Town", "reload6", false);
	LocatorReloadEnterDisable("PuertoPrincipe_Town", "reload7", false);
	LocatorReloadEnterDisable("PuertoPrincipe_Town", "reload8", false);
	LocatorReloadEnterDisable("Cuba_Jungle_03", "reload1_back", false);
	LocatorReloadEnterDisable("Cuba_Jungle_01", "reload3_back", false);

	LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload3", true);
	LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload1_back", true);
	LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload2_back", true);

	string cnd;
	int weaponskill = 2 * MOD_SKILL_ENEMY_RATE;
	for (int i = 0; i < 12; i++)
	{
		if (i < 10)
		{
			sld = GetCharacter(NPC_GenerateCharacter("IncqSoldier_"+sti(i), "sold_spa_"+(rand(7)+1), "man", "man", MOD_SKILL_ENEMY_RATE, SPAIN, 0, true));
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
			cnd = "l" + i;
			pchar.quest.WhisperAfterTownBattle.win_condition.(cnd) = "NPC_Death";
			pchar.quest.WhisperAfterTownBattle.win_condition.(cnd).character ="IncqSoldier_"+sti(i);
			LAi_SetImmortal(sld, true);
			GiveItem2Character(sld, "blade4");
			EquipCharacterByItem(sld, "blade4");
			SetSelfSkill(sld, weaponskill, weaponskill, weaponskill, weaponskill, weaponskill);
			LAi_SetHP(sld, 12.0 * MOD_SKILL_ENEMY_RATE, 12.0 *MOD_SKILL_ENEMY_RATE);
			ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item8");
		}
			sld = GetCharacter(NPC_GenerateCharacter("PirateTownDefender_"+sti(i), "pirate_"+sti(rand(25)+1), "man", "man", MOD_SKILL_ENEMY_RATE, PIRATE, 0, true));
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld.Dialog.Filename = "Quest\WhisperLine\Whisper.c";
			sld.dialog.currentnode = "Pirateguard";
			LAi_SetImmortal(sld, true);
			GiveItem2Character(sld, "blade1");
			EquipCharacterByItem(sld, "blade1");
			SetSelfSkill(sld, weaponskill, weaponskill, weaponskill, weaponskill, weaponskill);
			LAi_SetHP(sld, 12.0 * MOD_SKILL_ENEMY_RATE, 12.0 *MOD_SKILL_ENEMY_RATE);
		if (i < 10)
		{
			ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item12");
		}
		if (i >= 10 && MOD_SKILL_ENEMY_RATE < 10)
		{
			ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item1");
			LAi_SetImmortal(sld, false);
		}


	}
	/*
	sld = characterFromID("IncqSoldier_0");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item7");
	sld = characterFromID("IncqSoldier_1");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item10");
	sld = characterFromID("IncqSoldier_2");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item8");
	sld = characterFromID("IncqSoldier_3");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item11");
	sld = characterFromID("IncqSoldier_4");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item13");
	sld = characterFromID("IncqSoldier_5");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item14");
	sld = characterFromID("IncqSoldier_6");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item15");
	sld = characterFromID("IncqSoldier_7");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item16");
	sld = characterFromID("IncqSoldier_8");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item6");
	sld = characterFromID("IncqSoldier_9");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item5");
	sld = characterFromID("PirateTownDefender_0");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "officers", "reload3_2");
	sld = characterFromID("PirateTownDefender_1");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "officers", "reload3_1");
	sld = characterFromID("PirateTownDefender_2");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "officers", "reload3_3");
	sld = characterFromID("PirateTownDefender_3");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "rld", "aloc0");
	sld = characterFromID("PirateTownDefender_4");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item2");
	sld = characterFromID("PirateTownDefender_5");
	ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item1");
	sld = characterFromID("PirateTownDefender_6");
	ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item12");
	sld = characterFromID("PirateTownDefender_7");
	ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item9");

	if (MOD_SKILL_ENEMY_RATE != 10)
	{
		sld = characterFromID("PirateTownDefender_8");
		ChangeCharacterAddressGroup(sld, "PuertoPrincipe_ExitTown", "item", "item9");
	}
	*/
	pchar.quest.WhisperAfterTownBattle.function = "WhisperAfterTownBattle";
}

void WhisperPirateTownBattle(string qName)
{
	SetLocationCapturedState("PuertoPrincipe_town", false);
	DoQuestFunctionDelay("WhisperPirateTownGetHat_part_1", 0.1);
}
void WhisperKillNineFingers(string qName)
{
	//fix
	setCharacterShipLocation(pchar, "PuertoPrincipe_port");
    setWDMPointXZ("PuertoPrincipe_port");  // коорд на карте

	sld = characterFromID("NineFingers");

	DeleteAttribute(sld, "items");
    DeleteAttribute(sld, "equip");
	GiveItem2Character(sld, "Map_bad");
	//GiveItem2Character(sld, "spyglass1");
	//GiveItem2Character(sld, "pistol1");
	//TakeNItems(sld, "GunPowder", 10);
    //TakeNItems(sld, "bullet", 10);
    //TakeNItems(sld, "potionrum", 5);
	GiveMCItemToSomeoneElse(sld);
	//TakeNItems(sld, "hatWhisper", 1);
	RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
	LAi_KillCharacter(sld);
}
void WhisperPirateTownBattleMortality()
{
	for (int i = 0; i < 10; i++)
	{
		sld = characterFromID("IncqSoldier_"+sti(i));
		LAi_SetImmortal(sld, false);
		sld = characterFromID("PirateTownDefender_"+sti(i));
		LAi_SetImmortal(sld, false);
	}
}

void WhisperAfterTownBattle(string qName)
{
	pchar.questTemp.Whisper.AfterTownBattle = true;
	LAi_SetFightMode(PChar, false);
	DoQuestCheckDelay("TalkSelf_Quest", 1.0);
	LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload2_back", false);
	LocatorReloadEnterDisable("PuertoPrincipe_Port", "reload1_back", true);
	LAi_group_Delete("wl_TownDefenders");

}

void WhisperMeetCrew(string qName)
{
	sld = CharacterFromID("Beatrice");
	RestoreOldDialog(sld);
	sld = CharacterFromID("Hugo_Lesopilka");
	RestoreOldDialog(sld);

	LAi_group_Delete("wl_TownDefenders");

	sld = GetCharacter(NPC_GenerateCharacter("Wh_Jack", "PGG_HuanChahotka_0", "man", "man", 5, PIRATE, -1, false));
   	sld.name 	= "Джек";
    sld.lastname = "";
    sld.Dialog.Filename = "Quest\WhisperLine\Whisper.c";
	GiveItem2Character(sld, "blade9");
	EquipCharacterByItem(sld, "blade9");
	LAi_SetHP(sld, 30.0 * MOD_SKILL_ENEMY_RATE, 30.0 *MOD_SKILL_ENEMY_RATE);
	if (MOD_SKILL_ENEMY_RATE == 10)
	{
		SetCharacterPerk(sld, "Sliding");
		LAi_SetHP(sld, 35.0 * MOD_SKILL_ENEMY_RATE, 35.0 *MOD_SKILL_ENEMY_RATE);
	}
	sld.greeting = "GR_ToughPirate";
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_Port", "officers", "reload1_1");
	LAi_SetActorTypeNoGroup(sld);
    LAi_type_actor_Reset(sld);
    SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
	LAi_ActorFollow(sld,pchar, "ActorDialog_Any2Pchar", 4.0);
	LAi_SetImmortal(sld, true);
	LAi_SetActorType(pchar);
	LAi_ActorTurnToCharacter(pchar, sld);

	sld = GetCharacter(NPC_GenerateCharacter("Wh_Jim", "PGG_Doggerty_0", "man", "man", 5, PIRATE, -1, false));
   	sld.name 	= "Вудро";
    sld.lastname = "Доггерти";
    sld.Dialog.Filename = "Quest\WhisperLine\Whisper.c";
	LAi_SetHP(sld, 250.0, 250.0);
	//sld.greeting = "Gr_padre";
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_Port", "goto", "goto7");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorTurnToCharacter(sld, pchar);
	//sld.LifeDay = 0;

	for(i=1; i < 5; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Wh_Crew"+sti(i), "pirate_"+sti(rand(25)+1), "man", "man", 5, PIRATE, -1, false));
		LAi_SetHP(sld, 250.0, 250.0);
		//sld.greeting = "Gr_padre";
		ChangeCharacterAddressGroup(sld, "PuertoPrincipe_Port", "enc03", "enc03_0"+sti(i));
		LAi_SetActorTypeNoGroup(sld);
		LAi_ActorTurnToCharacter(sld, pchar);
		LAi_SetImmortal(sld, true);
		sld.LifeDay = 0;
	}

}
void WhisperJimTalk(string qName)
{
	DeleteAttribute(pchar, "Cirgnore");
	//sld = CharacterFromID("Wh_Jack");
	//Dead_DelLoginedCharacter(sld);
	sld = characterFromID("Wh_Jim");
	LAi_SetActorTypeNoGroup(sld);
    LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	LAi_SetImmortal(sld, true);

	//LAi_SetActorType(pchar);
	//LAi_ActorTurnToCharacter(pchar, sld);
}

void WhisperPlaceSmugglersOnShore(string LocationId)
{
	ref Smuggler, player;
	int RandCounter;
	int i;

	player = GetMainCharacter();

	string Model;

	player.GenQuest.Smugglers_Group = "Smugglers_1";
    LAi_group_Register(player.GenQuest.Smugglers_Group);

	for (i = 1; i <= 6; i++)
    {
        Model = "pirate_" + (rand(9)+1);
		Smuggler = GetCharacter(NPC_GenerateCharacter("W_Smug0" + i, Model, "man", "man", 5, PIRATE, -1, true)); // 4 дн¤, потом сами пропадут
		SetFantomParam(Smuggler);
		LAi_SetWarriorTypeNoGroup(Smuggler);
		LAi_warrior_DialogEnable(Smuggler, true);
		LAi_warrior_SetStay(Smuggler, true);
		Smuggler.Dialog.Filename = "Quest\WhisperLine\Whisper.c";
		Smuggler.Dialog.CurrentNode = "Smuggler";
		Smuggler.greeting = "Gr_Smuggler_OnShore";
		LAi_SetImmortal(Smuggler, true);
		LAi_group_MoveCharacter(Smuggler, player.GenQuest.Smugglers_Group);
		if (i < 3) ChangeCharacterAddressGroup(Smuggler, LocationID, "Smugglers", "Smuggler0" + i);
		else
		{
			int rando = rand(3);
			switch (rando)
			{
				case 0: rando = 1; break;
				case 1: rando = 1; break;
				case 2: rando = 2; break;
				case 3: rando = 3; break;
			}
			ChangeCharacterAddressGroup(Smuggler, LocationID, "Smugglers", "Smuggler0"+rando);
		}
    }

	AddGeometryToLocation(LocationID, "smg");

	LAi_group_SetRelation(LAI_GROUP_PLAYER, player.GenQuest.Smugglers_Group, LAI_GROUP_NEITRAL);
	LAi_group_SetRelation(player.GenQuest.Smugglers_Group, "CoastalGuards", LAI_GROUP_NEITRAL); // патруль на берегу

	//SetTimerCondition("Rand_Smuggling", 0, 0, 4, false);  // через 4 дн¤ всех убрать
}

void WhisperRemoveSmugglersFromShore()
{
	ref Smuggler;
	int RandCounter, i, cn;
	string sLoc = "Shore58";

	RemoveGeometryFromLocation(sLoc, "smg");

	for (i = 1; i <= 6; i++) //eddy
	{
		cn = GetCharacterIndex("W_Smug0"+i);
		if (cn != -1)
		{
			characters[cn].lifeDay = 0;
		}
	}
	LAi_group_SetRelation(LAI_GROUP_PLAYER, "CoastalGuards", LAI_GROUP_NEITRAL);
}

void WhisperChinaman(string qName)
{
	Sea_CabinStartNow();

	pchar.quest.WhisperChinamanCapSpeaks.win_condition.l1          = "location";
	pchar.quest.WhisperChinamanCapSpeaks.win_condition.l1.location = Get_My_Cabin();
	pchar.quest.WhisperChinamanCapSpeaks.function             = "WhisperChinamanCapSpeaks";
}

void WhisperChinamanCapSpeaks(string qName)
{
	sld = GetCharacter(NPC_GenerateCharacter("W_ChinamanGuard", "pirate_10", "man", "man", 5, PIRATE, 0, false));
	LAi_SetActorTypeNoGroup(sld);
	sld.name 	= "Хуан";
    sld.lastname = "";
	sld.greeting = "Gr_Officer";
	GiveItem2Character(sld, "blade9");
	EquipCharacterByItem(sld, "blade9");
    ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "rld", LAi_FindNearestFreeLocator2Pchar("rld"));
	sld.Dialog.Filename = "Quest\WhisperLine\Whisper_cabin_dialog.c";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);

	sld = GetCharacter(NPC_GenerateCharacter("W_Chinaman", "PGG_Longway_0", "man", "man", 5, PIRATE, -1, false));
	sld.CanTakeMushket = true;
	sld.greeting = "GR_longway";
	//PlayVoice("Voice\Russian\Longway-01.wav");
	LAi_SetActorTypeNoGroup(sld);
	sld.name 	= "Лонг";
    sld.lastname = "Вэй";
	sld.Dialog.Filename = "Quest\WhisperLine\Whisper_cabin_dialog.c";
    ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "rld", LAi_FindNearestFreeLocator2Pchar("rld"));
}
void WhisperChinamanSpeaks(string qName)
{
	sld = characterFromID("W_Chinaman");
	SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 4.0);
}
void WhisperChinamanCapSpeaksAgain(string qName)
{
	sld = characterFromID("W_ChinamanGuard");
	SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 4.0);
}

void WhisperSmugglingPatrol()
{
	ref CoastGuard;
	int i;
	int iNation = 1;// Нация патруля
	string Model;

	for (i = 1; i <= 3; i++)
    {
        Model = "off_" + NationShortName(iNation) + "_" + (rand(1) + 1);
		CoastGuard = GetCharacter(NPC_GenerateCharacter("Coastal_Captain0" + i, Model, "man", "man", sti(pchar.rank) + rand(MOD_SKILL_ENEMY_RATE), iNation, 3, true)); // 3 дня, потом сами пропадут
		SetFantomParam(CoastGuard);
		SelectCoastalGuardShip(CoastGuard);
		CoastGuard.AlwaysEnemy = true;
		CoastGuard.DontRansackCaptain = true;
		CoastGuard.AlwaysSandbankManeuver = true;
		Group_AddCharacter("Coastal_Guards", CoastGuard.id);
		SetCharacterRelationBoth(sti(CoastGuard.index), GetMainCharacterIndex(), RELATION_ENEMY);
		//if (makeint(pchar.rank) < 6 && i == 1 && GetCompanionQuantity(pchar) == 1) break;

		if (MOD_SKILL_ENEMY_RATE!= 10)
		{
			if (makeint(pchar.rank) < 9 && i == 2 && GetCompanionQuantity(pchar) < 3) break;
		}
    }
	Group_SetGroupCommander("Coastal_Guards", "Coastal_Captain01");
	Group_SetAddress("Coastal_Guards", Islands[GetCharacterCurrentIsland(Pchar)].id, "", "");
	Group_SetPursuitGroup("Coastal_Guards", PLAYER_GROUP);
	Group_SetTaskAttack("Coastal_Guards", PLAYER_GROUP);
	Group_LockTask("Coastal_Guards");
	Flag_Change(PIRATE);
}

void WhisperHuntersCaveEntrance(string qName)
{
	Group_FindOrCreateGroup("DeSouzaHunter");

	chrDisableReloadToLocation = true;
	string cnd;
	for (int i = 1; i <= 7; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("DeSouzaHunter"+sti(i), "OZG_" + (rand(6) + 1), "man", "man", 5+MOD_SKILL_ENEMY_RATE, PIRATE, 0, true));
		//SetFantomParamHunter(sld);
		LAi_SetHP(sld, 50+sti(pchar.rank)*10.0, 50+sti(pchar.rank)*10.0);
		if (MOD_SKILL_ENEMY_RATE == 10)
		{
			LAi_SetHP(sld, 50+sti(pchar.rank) * 20.0, 50+sti(pchar.rank) * 20.0);
		}

		LAi_SetActorType(sld);
		//LAi_warrior_SetStay(sld, true);
		Group_AddCharacter("DeSouzaHunter", sld.id);
		sld.LifeDay = 0;

		cnd = "l" + i;
		pchar.quest.WhisperAfterHuntersCaveBattle.win_condition.(cnd) = "NPC_Death";
		pchar.quest.WhisperAfterHuntersCaveBattle.win_condition.(cnd).character ="DeSouzaHunter"+sti(i);
		if (i < 5)
		{
			ChangeCharacterAddressGroup(sld, PChar.location, "monsters", "monster3");
		}
		else
		{
			ChangeCharacterAddressGroup(sld, PChar.location, "monsters", "monster1");
		}
		if (i == 1)
		{
			LAi_SetStayTypeNoGroup(sld);
			sld.talker = 10;
			ChangeCharacterAddressGroup(sld, PChar.location, "enc01", "enc01_03");
			sld.dialog.filename = "Quest\WhisperLine\Whisper.c";
			sld.dialog.currentnode = "DeSouzaHunter";
	        sld.greeting = "Gr_HUNTER";
		}
		LAi_SetImmortal(sld, true);
	}

	sld = GetCharacter(NPC_GenerateCharacter("W_Lejitos", "PGG_Lejitos_0", "man", "man", 1, PIRATE, -1, false));
	sld.CanTakeMushket = true;
	sld.HasNoFear = true;
	sld.name = "Элихио";
	sld.lastname = "Лехито";
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	sld.dialog.filename = "Quest\WhisperLine\Whisper.c";
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, PChar.location, "enc01", "enc01_02");
	LAi_SetImmortal(sld, true);
	SetSelfSkill(sld, 45, 45, 75, 45, 35);
	SetShipSkill(sld, 80, 25, 20, 20, 20, 25, 70, 25, 15);
	SetSPECIAL(sld, 10, 3, 10, 4, 8, 9, 5);
	sld.rank = 15;
	LAi_SetHP(sld, 250.0, 250.0);
	sld.greeting = "GR_Lejitos";
	string lejitosAx = GetGeneratedItem("topor_01");
	GiveItem2Character(sld, lejitosAx);
	EquipCharacterByItem(sld, lejitosAx);
	GiveItem2Character(sld, "cirass2");
	EquipCharacterbyItem(sld, "cirass2");
	GiveItem2Character(sld, "pistol2");
	EquipCharacterbyItem(sld, "pistol2")
	TakeNItems(sld, "indian18", 1);

	SetCharacterPerk(sld, "ByWorker");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "LongRangeGrappling");
	SetCharacterPerk(sld, "GrapplingProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "IronWill");
	SetCharacterPerk(sld, "Ciras");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "Energaiser"); // скрытый перк дает 1.5 к приросту энергии, дается ГГ и боссам уровней


	PChar.quest.WhisperAfterHuntersCaveBattle.function = "WhisperAfterHuntersCaveBattle";

}

void WhisperAfterHuntersCaveBattle(string qName)
{
	chrDisableReloadToLocation = false;
	if(!LAi_IsDead(CharacterFromID("W_Lejitos")))
	{
		sld = characterFromID("W_Lejitos");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	WhisperDeSouzaSeaBattle();
}

void WhisperDeSouzaSeaBattle()
{
	sld = CharacterFromID("AntonioDeSouza");
	SetFantomParamHunter(sld);
	sld.Ship.Type = GenerateShipExt(SHIP_GALEON_H, true, sld);
	sld.Ship.name = "Кара Господня";
	LAi_SetImmortal(sld, false);
	//SetBaseShipData(sld);
	sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS24;

	SetCrewQuantityFull(sld);
	realships[sti(sld.ship.type)].MaxCrew = 500;
	SetCrewQuantity(sld,GetMaxCrewQuantity(sld));

	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 20 + 5 * MOD_SKILL_ENEMY_RATE);
	ChangeCrewExp(sld, "Cannoners", 20 + 5 * MOD_SKILL_ENEMY_RATE);
	ChangeCrewExp(sld, "Soldiers", 20 + 5 * MOD_SKILL_ENEMY_RATE);
	sld.SaveItemsForDead = true;
	TakeNItems(sld, "DeSouzaCross", 1);

	SetSelfSkill(sld, 50, 50, 50, 50, 50);
	SetShipSkill(sld, 50, 50, 50, 50, 50, 50, 50, 50, 50);
	//SetSPECIAL(sld, 10, 3, 10, 4, 8, 9, 5);
	sld.rank = 25;
	LAi_SetHP(sld, 50.0 * MOD_SKILL_ENEMY_RATE, 50.0 * MOD_SKILL_ENEMY_RATE);
	GiveItem2Character(sld, "cirass3");
	EquipCharacterbyItem(sld, "cirass3");

	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "CannonProfessional");

	if (MOD_SKILL_ENEMY_RATE == 10)
	{
		SetCharacterPerk(sld, "Sliding");
		sld.rank = 40;
		SetSelfSkill(sld, 80, 80, 80, 80, 80);
		SetShipSkill(sld, 80, 80, 80, 80, 80, 80, 80, 80, 80);
		LAi_SetHP(sld, 500.0, 500.0);
	}

    SetCharacterGoods(sld,GOOD_FOOD,500);
    SetCharacterGoods(sld,GOOD_BALLS,1000);
    SetCharacterGoods(sld,GOOD_GRAPES,1000);
    SetCharacterGoods(sld,GOOD_KNIPPELS,1000);
    SetCharacterGoods(sld,GOOD_BOMBS,1000);
    SetCharacterGoods(sld,GOOD_POWDER,3000);
    SetCharacterGoods(sld,GOOD_PLANKS,150);
    SetCharacterGoods(sld,GOOD_SAILCLOTH,150);
    SetCharacterGoods(sld,GOOD_RUM,200);
    SetCharacterGoods(sld,GOOD_WEAPON,600);
	SetCharacterGoods(sld,GOOD_MEDICAMENT,300);
	sld.AlwaysEnemy = true;
	sld.DontRansackCaptain = true;
	sld.AlwaysSandbankManeuver = true;
	Group_FindOrCreateGroup("DeSouza");
	Group_AddCharacter("DeSouza", sld.id);
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
	Group_SetGroupCommander("DeSouza", "AntonioDeSouza");
	//Group_SetPursuitGroup("DeSouza", PLAYER_GROUP);
	Group_SetTaskAttack("DeSouza", PLAYER_GROUP);
	Group_LockTask("DeSouza");

	Group_SetAddress("DeSouza", "SentMartin", "Quest_ships", "quest_ship_7");
	SetFunctionNPCDeathCondition("WhisperDeSouza_Is_Dead", "AntonioDeSouza", false);
}

void WhisperDeSouza_Is_Dead(string qName)
{
	if (!CheckAttribute(pchar, "Whisper.DeSouzaTalked"))
	{
		AddQuestRecord("WhisperQuestline", "3");
		CloseQuestHeader("WhisperQuestline");
	}
}

void WhisperWarDog_Is_Dead(string qName)
{
	if (!CheckAttribute(pchar, "Whisper.NanoCostume"))
	{
		AddQuestRecord("WhisperQuestline", "3");
		CloseQuestHeader("WhisperQuestline");
	}
}

void WhisperWarDogSeaBattle()
{
	sld = CharacterFromID("wl_Pirate_Cap")
	sld.Ship.Type = GenerateShipExt(SHIP_WH_CORVETTE_QUEST, true, sld);
	sld.Ship.name = "Пёс Войны";
	//SetBaseShipData(sld);
	sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;

	ChangeCharacterAddressGroup(sld, "My_Deck", "reload", "reload1");
	EquipCharacterByItem(sld, "blade_15");
	EquipCharacterByItem(sld, "pistol4");
    TakeNItems(sld, "blade_whisper", -2);

	SetCrewQuantityFull(sld);
	int hcrew = GetMaxCrewQuantity(sld);
	SetCrewQuantityOverMax(sld, hcrew + 12 * MOD_SKILL_ENEMY_RATE);// Усложним бой

	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 50 + 5 * MOD_SKILL_ENEMY_RATE);
	ChangeCrewExp(sld, "Cannoners", 50 + 5 * MOD_SKILL_ENEMY_RATE);
	ChangeCrewExp(sld, "Soldiers", 50 + 5 * MOD_SKILL_ENEMY_RATE);

	TakeNItems(sld, "Food5", 5);
	TakeNItems(sld, "potion2", 5);
	sld.SaveItemsForDead = true;
	GiveItem2Character(sld, "cirass5");
	EquipCharacterbyItem(sld, "cirass5")
	LAi_SetHP(sld, 200.0 + 20 * MOD_SKILL_ENEMY_RATE, 200.0 + 20 * MOD_SKILL_ENEMY_RATE);
	SetSelfSkill(sld, 80, 80, 80, 80, 80);
	SetShipSkill(sld, 75, 75, 75, 75, 75, 75, 75, 75, 75);
	sld.rank = 30;
	if (MOD_SKILL_ENEMY_RATE > 2)
	{
		SetHalfPerksToChar(sld, true);
	}
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	if (MOD_SKILL_ENEMY_RATE == 10)
	{
		sld.rank = 60;
		SetSelfSkill(sld, 100, 100, 100, 100, 100);
		SetShipSkill(sld, 100, 100, 100, 100, 100, 100, 100, 100, 100);
		//LAi_SetHP(sld, 1000.0, 1000.0);
	}
	SetFoodToCharacter(sld, 3, 20);
	SetSPECIAL(sld, 10, 10, 10, 10, 10, 10, 10);

    SetCharacterGoods(sld,GOOD_FOOD,500);
    SetCharacterGoods(sld,GOOD_BALLS,1000);
    SetCharacterGoods(sld,GOOD_GRAPES,1000);
    SetCharacterGoods(sld,GOOD_KNIPPELS,1000);
    SetCharacterGoods(sld,GOOD_BOMBS,1000);
    SetCharacterGoods(sld,GOOD_POWDER,3000);
    SetCharacterGoods(sld,GOOD_PLANKS,150);
    SetCharacterGoods(sld,GOOD_SAILCLOTH,150);
    SetCharacterGoods(sld,GOOD_RUM,200);
    SetCharacterGoods(sld,GOOD_WEAPON,600);
	SetCharacterGoods(sld,GOOD_MEDICAMENT,300);

	sld.AlwaysEnemy = true;
	sld.DontRansackCaptain = true;
	sld.AlwaysSandbankManeuver = true;
	Group_FindOrCreateGroup("WarDog");
	Group_SetType("WarDog", "pirate");
	Group_AddCharacter("WarDog", "wl_Pirate_Cap");
	Group_SetGroupCommander("WarDog", "wl_Pirate_Cap");
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);

	LAi_SetImmortal(sld, false);
	Group_SetPursuitGroup("WarDog", PLAYER_GROUP);
	Group_SetTaskAttack("WarDog", PLAYER_GROUP);
	Group_LockTask("WarDog");

	Group_SetAddress("WarDog", "Terks", "Quest_ships", "quest_ship_7");
	SetFunctionNPCDeathCondition("WhisperWarDog_Is_Dead", "wl_Pirate_Cap", false);
}

void WhisperSpawn_Chard()
{
	SetQuestHeader("WhisperChardQuest");
	AddQuestRecord("WhisperChardQuest", "1");
	AddQuestUserData("WhisperChardQuest", "sCity", XI_ConvertString("Colony" + pchar.Whisper.EsFriendTown + "Gen")));
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.Whisper.EsFriendTown+"_tavern_upstairs")], true);
	LocatorReloadEnterDisable(pchar.Whisper.EsFriendTown+"_tavern", "reload2_back", false);
	sld = GetCharacter(NPC_GenerateCharacter("W_Chard", "PGG_Chard_0", "man", "man", 1, PIRATE, -1, true));
	LAi_SetStayType(sld);
	ChangeCharacterAddressGroup(sld, pchar.Whisper.EsFriendTown+"_tavern_upstairs", "goto", "goto1");
	sld.dialog.filename = "Quest\WhisperLine\Whisper.c";

	sld.CanTakeMushket = true;
	sld.HeroModel = "PGG_Chard_0,PGG_Chard_1,PGG_Chard_2,PGG_Chard_3,PGG_Chard_4,PGG_Chard_5";
	sld.name = "Майкл";
	sld.lastname = "Чард";
	//LAi_SetImmortal(sld, true);
	SetSelfSkill(sld, 50, 50, 50, 50, 100);
	SetShipSkill(sld, 60, 30, 80, 80, 40, 30, 40, 30, 60);
	SetSPECIAL(sld, 7, 10, 8, 6, 7, 8, 10);
	sld.rank = 20;
	LAi_SetHP(sld, 220.0, 220.0);
	//sld.greeting = "GR_Lejitos";
	GiveItem2Character(sld, "blade_whisper");
	EquipCharacterByItem(sld, "blade_whisper");
	GiveItem2Character(sld, "cirass4");
	EquipCharacterbyItem(sld, "cirass4");
	GiveItem2Character(sld, "pistol4");
	EquipCharacterbyItem(sld, "pistol4");
	TakeNItems(sld, "bullet", 10);
	TakeNItems(sld, "GunPowder", 10);
	TakeNItems(sld, "Food5", 5);
	TakeNItems(sld, "potion2", 5);

	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "ImmediateReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "ByWorker");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "Tireless");
	//SetCharacterPerk(sld, "Grus");
	SetCharacterPerk(sld, "Ciras");
	SetCharacterPerk(sld, "Energaiser"); // скрытый перк дает 1.5 к приросту энергии, дается ГГ и боссам уровней
}

void WhisperSpawnPortman (ref npchar)
{
	//pchar.Whisper.PortmanAtSea = true;
	int difficulty = 5 * MOD_SKILL_ENEMY_RATE;
	sld = GetCharacter(NPC_GenerateCharacter("Whisper_Portman_Captain", "off_eng_2", "man", "man", 55, ENGLAND, -1, true));
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "эскадра Ральфа Портмана";
	sld.mapEnc.type = "trade";
	FantomMakeCoolFighter(sld, 70, 50 + difficulty, 50 + difficulty, "blade23", "pistol3", 60);
	FantomMakeCoolSailor(sld, SHIP_UNICORN, "Единорог", CANNON_TYPE_CANNON_LBS32, 50 + difficulty, 50 + difficulty, 50 + difficulty);
	sld.dialog.filename = "Quest\WhisperLine\Whisper_cabin_dialog.c";
	sld.DeckDialogNode = "Portman";
	sld.name 	= "Ральф";
	sld.lastname = "Портман";
	sld.AlwaysSandbankManeuver = true;
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	SetCharacterPerk(sld, "MusketsShoot");

	sld.ship.Crew.Morale = 50 + difficulty;
	ChangeCrewExp(sld, "Sailors", 50 + difficulty);
	ChangeCrewExp(sld, "Cannoners", 50 + difficulty);
	ChangeCrewExp(sld, "Soldiers", 50 + difficulty);

	GiveItem2Character(sld, "cirass4");
	EquipCharacterbyItem(sld, "cirass4");
	GiveItem2Character(sld, "jewelry9");
	SetCharacterPerk(sld, "Energaiser"); // скрытый перк дает 1.5 к приросту энергии, дается ГГ и боссам уровней
	TakeNItems(sld, "Food5", 5);
	TakeNItems(sld, "potion2", 5);
	sld.money = 100000;
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;

	LAi_group_MoveCharacter(sld, "W_portman");
	string  sGroup = "Sea_" + sld.id;
	group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	string targetCity = PGG_FindRandomTownByNation(sti(npchar.nation));
	while (targetCity == npchar.city)
	{
		targetCity = PGG_FindRandomTownByNation(sti(npchar.nation));
	}
	AddQuestRecord("WhisperChardQuest", "3");
	AddQuestUserData("WhisperChardQuest", "sTargetCity", XI_ConvertString("Colony" + targetCity + "Gen")));
	Map_CreateTrader(npchar.city, targetCity, sld.id, 8);
	pchar.Whisper.PortmanTargetCity = targetCity;
	SetFunctionNPCDeathCondition("Whisper_Portman_Is_Dead", sld.id, false);
	for (int i = 0; i < 2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Whisper_Portman_follower"+i, "off_eng_1", "man", "man", 30, ENGLAND, -1, true));
		FantomMakeCoolFighter(sld, 50, 30 + difficulty, 30 + difficulty, "blade36", "pistol3", 10);
		FantomMakeCoolSailor(sld, SHIP_SALAMANDER, "", CANNON_TYPE_CANNON_LBS24, 30 + difficulty, 30 + difficulty, 30 + difficulty);
		SetRandomNameToShip(sld);
		sld.AlwaysSandbankManeuver = true;
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		SetCharacterPerk(sld, "MusketsShoot");

		sld.ship.Crew.Morale = 30 + difficulty;
		ChangeCrewExp(sld, "Sailors",30 + difficulty);
		ChangeCrewExp(sld, "Cannoners", 30 + difficulty);
		ChangeCrewExp(sld, "Soldiers", 30 + difficulty);

		GiveItem2Character(sld, "cirass3");
		EquipCharacterbyItem(sld, "cirass3");
		GiveItem2Character(sld, "jewelry9");
		SetCharacterPerk(sld, "Energaiser"); // скрытый перк дает 1.5 к приросту энергии, дается ГГ и боссам уровней
		TakeNItems(sld, "Food5", 3);
		TakeNItems(sld, "potion2", 3);
		sld.money = 30000;
		sld.SaveItemsForDead = true;
		sld.DontClearDead = true;

		LAi_group_MoveCharacter(sld, "W_portman");
		Group_AddCharacter(sGroup, sld.id);
	}
}

void Whisper_Portman_Is_Dead(string qName)
{
	DeleteAttribute(pchar, "Whisper.ActiveChardQuest");
	if (!CheckAttribute(pchar, "Whisper.FoundPortmanJournal"))
	{
		AddQuestRecord("WhisperChardQuest", "6");
		CloseQuestHeader("WhisperChardQuest");
	}
}

void WhisperChardShore(string qName)
{
	if(CheckAttribute(pchar,"WhisperChardCompanion"))
	{
		LocatorReloadEnterDisable("shore26", "boat", true);
		LocatorReloadEnterDisable("shore27", "boat", true);
		sld = CharacterFromID("W_Chard");
		LAi_SetImmortal(sld, true);
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
		chrDisableReloadToLocation = true;
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	DeleteAttribute(pchar,"WhisperChardCompanion");
}

void WhisperChardCave(string qName)
{
	LocatorReloadEnterDisable("shore26", "boat", true);
	LocatorReloadEnterDisable("shore27", "boat", true);
	GiveItem2Character(sld, "blade13");
	EquipCharacterbyItem(sld, "blade13");
	sld = CharacterFromID("W_Chard");
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
	chrDisableReloadToLocation = true;
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);

}

void WhisperEngRevengeWarning(string qName)
{
	pchar.questTemp.Whisper.EngRevenge = true;
	DoQuestCheckDelay("TalkSelf_Quest", 1.0);
}

void WhisperEnglandRevengel()
{
	ref sld;
	int i;
	int difficulty = 5 * MOD_SKILL_ENEMY_RATE;
	for (i = 1; i <= 4; i++)
    {
		sld = GetCharacter(NPC_GenerateCharacter("W_Captain0"+i, "off_eng_" + (rand(1) + 1), "man", "man", difficulty, ENGLAND, 3, true));
		FantomMakeCoolFighter(sld, 50, 30 + difficulty, 30 + difficulty, "blade36", "pistol3", 50);
		FantomMakeCoolSailor(sld, SHIP_OXFORD, "", CANNON_TYPE_CANNON_LBS24, 40 + difficulty, 40 + difficulty, 40 + difficulty);
		SetRandomNameToShip(sld);
		sld.AlwaysSandbankManeuver = true;
		sld.DontRansackCaptain = true;
		sld.AnalizeShips = true;
		SetCharacterPerk(sld, "MusketsShoot");

		sld.ship.Crew.Morale = 40 + difficulty;
		ChangeCrewExp(sld, "Sailors",40 + difficulty);
		ChangeCrewExp(sld, "Cannoners", 40 + difficulty);
		ChangeCrewExp(sld, "Soldiers", 40 + difficulty);

		GiveItem2Character(sld, "cirass3");
		EquipCharacterbyItem(sld, "cirass3");
		SetCharacterPerk(sld, "Energaiser"); // скрытый перк дает 1.5 к приросту энергии, дается ГГ и боссам уровней
		TakeNItems(sld, "Food5", 2);
		TakeNItems(sld, "potion2", 2);
		sld.money = 40000;
		sld.SaveItemsForDead = true;
		sld.DontClearDead = true;

		sld.AlwaysEnemy = true;
		Group_AddCharacter("Coastal_Guards", sld.id);
		SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
		Fantom_SetBalls(sld, "pirate");
		if (MOD_SKILL_ENEMY_RATE!= 10)
		{
			if (i == 3) break;
		}
    }
	Group_SetGroupCommander("Coastal_Guards", "W_Captain01");
	if(pchar.location.from_sea == "shore27")
	{
		Group_SetAddress("Coastal_Guards", Islands[GetCharacterCurrentIsland(Pchar)].id, "Quest_ships", "quest_ship_1");
	}
	else
	{
		Group_SetAddress("Coastal_Guards", Islands[GetCharacterCurrentIsland(Pchar)].id, "", "");
		Group_SetPursuitGroup("Coastal_Guards", PLAYER_GROUP);
	}
	Group_SetTaskAttack("Coastal_Guards", PLAYER_GROUP);
	Group_LockTask("Coastal_Guards");
	Flag_Change(PIRATE);
}

void WhisperSelectRandomUsurer() // Выбор случайного ростовщика по квесту
{
	if (CheckAttribute(&colonies[1], "nation"))
	{
		int n, nation;
		int storeArray[MAX_COLONIES];
		int howStore = 0;
		string thisTown = FindStringBeforeChar(pchar.location, "_tavern");
		for(n=0; n<MAX_COLONIES; n++)
		{
			if (colonies[n].nation != thisTown && colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && colonies[n].id != "FortOrange" && colonies[n].id != "Havana" && colonies[n].id != "Santiago" && colonies[n].id != "Portroyal" && colonies[n].id != "Villemstad" && colonies[n].id != "Tortuga" && colonies[n].id != "Panama")
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
		nation = storeArray[rand(howStore-1)];
		pchar.Whisper.UsurerId = colonies[nation].id + "_usurer";
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- Линейка Виспер --     конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Линейка Темного Странника	начало
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void DarkHuman_StartGame(string qName)
{
	DeleteAttribute(Pchar, "ship");
    DeleteAttribute(Pchar, "ShipSails.gerald_name");
    Pchar.ship.type = SHIP_NOTUSED;
	SaveCurrentQuestDateParam ("pchar.questTemp.DHRaceAgainstTime");
	SetQuestHeader("DarkHumanQuestline");
	AddQuestRecord("DarkHumanQuestline", "1");

	//Запретить выход из локации
	chrDisableReloadToLocation = true;
	//Заблокировать меню персонажа
	bDisableCharacterMenu = true;
	//и фасттревел
	InterfaceStates.DisFastTravel = true;

	SetQuestsCharacters();
	bDisableLandEncounters = true;

	//ChangeCharacterAddressGroup(pchar, PChar.location, "sit", "sit3");
	//LAi_SetActorTypeNoGroup(pchar);
	//LAi_ActorSetSitMode(pchar);
	pchar.selectedHero = rand(PsHeroQty-2)+2;
	sld = CharacterFromID("PsHero_" + pchar.selectedHero);
	ChangeCharacterAddressGroup(pchar, PChar.location, "rld", "aloc12");
	ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload_hold");

	sld.dialog.filename = "Quest\WhisperLine\DarkHuman.c";
	sld.dialog.currentnode = "PGG_transporter";
	LAi_SetActorType(sld);
    LAi_ActorDialog(sld, pchar, "", -1, 0);
	//SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
	//LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 0.0);
	sld.PGGAi.location.town = PGG_FindRandomTownByNation(sti(sld.nation));

	GiveNationLicence(SPAIN, 45);
	GiveNationLicence(HOLLAND, 80);
	Flag_Change(HOLLAND);
	pchar.money = 1000;
	GiveItem2Character(pchar, "DHGlove");
	EquipCharacterbyItem(pchar, "DHGlove");
}

void DarkHuman_Amatike(string qName)
{
	bDisableCharacterMenu = false;
	sld = CharacterFromID("PsHero_" + pchar.selectedHero);
	string futureLoc = sld.PGGAi.location.town + "_Tavern";
	ChangeCharacterAddressGroup(sld, futureLoc, "goto", "goto1");
	DeleteAttribute(pchar, "selectedHero");
	DoReloadCharacterToLocation("Shore9","smugglers", "smuggler02");

	sld = GetCharacter(NPC_GenerateCharacter("DH_mercenary", "officer_" + (rand(62)+2), "man", "man", MOD_SKILL_ENEMY_RATE, PIRATE, -1, true));
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "Shore9", "smugglers", "smuggler01");
	sld.dialog.filename = "Quest\WhisperLine\DarkHuman.c";
	sld.dialog.currentnode = "DH_mercenary_shore";
	LAi_SetActorType(sld);
	Group_AddCharacter(PLAYER_GROUP, sld.id);
    LAi_ActorDialog(sld, pchar, "", 1.0, 0);
	//LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", -1);

	for (int i = 0; i < 4; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("DH_merc_mush" + i, GetPirateMushketerModel(), "man", "mushketer", MOD_SKILL_ENEMY_RATE, PIRATE, -1, true));
		ChangeCharacterAddressGroup(sld, "Shore9", "smugglers", "smugglerload");
		LAi_SetWarriorType(sld);
		LAi_SetActorType(sld);
		Group_AddCharacter(PLAYER_GROUP, sld.id);
		TakeNItems(sld,"potion1", rand(2)+1);
		LAi_warrior_DialogEnable(sld, false);

		sld = GetCharacter(NPC_GenerateCharacter("DH_merc_blade"+sti(i), "pirate_"+sti(rand(25)+1), "man", "man", MOD_SKILL_ENEMY_RATE, PIRATE, -1, true));

		ChangeCharacterAddressGroup(sld, "Shore9", "smugglers", "smugglerload");
		LAi_SetWarriorType(sld);
		LAi_SetActorType(sld);
		Group_AddCharacter(PLAYER_GROUP, sld.id);
		TakeNItems(sld,"potion1", rand(2)+1);
		LAi_warrior_DialogEnable(sld, false);
	}
	LocatorReloadEnterDisable("Tenotchitlan_Jungle_03", "reload3_back", true);
	LocatorReloadEnterDisable("Tenotchitlan_Jungle_02", "reload1_back", true);
}

void DarkHuman_Temple(string qName)
{
	sld = CharacterFromID("DH_mercenary");
	ChangeCharacterAddressGroup(sld, "Temple", "goto", "goto1");
	LAi_ActorDialog(sld, pchar, "", 1.0, 0);
	sld.dialog.currentnode = "DH_mercenary_temple";
	for (int i = 0; i < 4; i++)
	{
		sld = CharacterFromID("DH_merc_mush" + i);
		ChangeCharacterAddressGroup(sld, "Temple", "goto", "goto2");
		LAi_SetStayType(sld);
		sld = CharacterFromID("DH_merc_blade" + i);
		ChangeCharacterAddressGroup(sld, "Temple", "goto", "goto5");
		LAi_SetStayType(sld);
	}

	string cnd;
	pchar.maxIndians = 8;
	if (MOD_SKILL_ENEMY_RATE == 10)
	{//Сюрприз для невозможки
		pchar.maxIndians+=2;
	}
	for (i = 0; i <= sti(pchar.maxIndians) * 2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("DHindian"+i, "Canib_"+(rand(5)+1), "man", "man", MOD_SKILL_ENEMY_RATE, PIRATE, 1, true));
		//SetFantomParamFromRank(sld, 1, true);
		sld.name = "Калинаго";
		sld.lastname = "";
		DeleteAttribute(sld, "equip");
		DeleteAttribute(sld, "items");
		string _Blade = GiveRandomBladeByType("indian");
		LAi_SetHP(sld, 10*MOD_SKILL_ENEMY_RATE, 10*MOD_SKILL_ENEMY_RATE);
		weaponskill = 2* MOD_SKILL_ENEMY_RATE;
		SetSelfSkill(sld, weaponskill, weaponskill, weaponskill, weaponskill, weaponskill);
		GiveItem2Character(sld, _Blade);
		EquipCharacterbyItem(sld, _Blade);

		LAi_SetStayTypeNoGroup(sld);
		LAi_group_MoveCharacter(sld, "Jungle_indians");

		ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload2");
		cnd = "l" + i;
		pchar.quest.DarkHuman_Temple_Afterfight.win_condition.(cnd) = "NPC_Death";
		pchar.quest.DarkHuman_Temple_Afterfight.win_condition.(cnd).character ="DHindian"+i;

		if (i < sti(pchar.maxIndians))
		{
			LAi_KillCharacter(sld);
		}
	}
	PChar.quest.DarkHuman_Temple_Afterfight.function = "DarkHuman_Temple_Afterfight";
	LAi_group_SetCheck("Jungle_indians", "IndianInJungleClearGroup");

}

void DarkHuman_Temple_Afterfight(string qName)
{
	sld = CharacterFromID("DH_mercenary");
	Lai_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 1.0, 0);
	sld.dialog.currentnode = "DH_mercenary_temple_afterfight";
	LocatorReloadEnterDisable("Temple", "reload1_back", true);
	LocatorReloadEnterDisable("Temple", "reload2", false);
	//CheckAttribute(Items[itemN], "shown")

	PChar.quest.DarkHuman_Temple_Inside.win_condition.l1 = "location";
	PChar.quest.DarkHuman_Temple_Inside.win_condition.l1.location = "Temple_Inside";
	PChar.quest.DarkHuman_Temple_Inside.function = "DarkHuman_Temple_Inside";

	sld = GetCharacter(NPC_GenerateCharacter("Dark_Incquisitor", "Dark_Incquisitor", "man", "man", MOD_SKILL_ENEMY_RATE/2, PIRATE, 1, false));
	ChangeCharacterAddressGroup(sld, "Temple_Inside", "goto", "goto9");
	TakeNItems(sld, "suit_1", 1);
	GiveItem2Character(sld, "blade22");
	EquipCharacterByItem(sld, "blade22");
	sld.SaveItemsForDead = true;
	LAi_SetActorType(sld);
	//LAi_ActorDialog(sld, pchar, "", -1.0, 0);
	sld.dialog.filename = "Quest\WhisperLine\DarkHuman.c";
	sld.dialog.currentnode = "Dark_Incquisitor";
	LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
	LAi_SetHP(sld, 5*MOD_SKILL_ENEMY_RATE, 5*MOD_SKILL_ENEMY_RATE);
	TakeNItems(sld, "GunPowder", -99);
	sld = GetCharacter(NPC_GenerateCharacter("Dark_Incquisitor1", "sold_spa_"+(rand(7)+1), "man", "man", MOD_SKILL_ENEMY_RATE/2, PIRATE, 1, true));
	ChangeCharacterAddressGroup(sld, "Temple_Inside", "goto", "goto11");
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
	LAi_SetHP(sld, 3*MOD_SKILL_ENEMY_RATE, 3*MOD_SKILL_ENEMY_RATE);
	TakeNItems(sld, "GunPowder", -99);
	sld = GetCharacter(NPC_GenerateCharacter("Dark_Incquisitor2", "sold_spa_"+(rand(7)+1), "man", "man", MOD_SKILL_ENEMY_RATE/2, PIRATE, 1, true));
	ChangeCharacterAddressGroup(sld, "Temple_Inside", "goto", "goto13");
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
	LAi_SetHP(sld, 3*MOD_SKILL_ENEMY_RATE, 3*MOD_SKILL_ENEMY_RATE);
	TakeNItems(sld, "GunPowder", -99);
}

void DarkHuman_Temple_Inside(string qName)
{
	pchar.CantTakeItems = true;

	sld = CharacterFromID("Dark_Incquisitor");
	LAi_ActorDialog(sld, pchar, "", -1.0, 0);
	chrDisableReloadToLocation = true;
}

void DarkHuman_Temple_Stash(string qName)
{
	//Log_Info("Опа")
	AddQuestRecord("DarkHumanQuestline", "3");
	SetQuestHeader("DarkHumanIncquisitorJournal");
	AddQuestRecord("DarkHumanIncquisitorJournal", "1");
	chrDisableReloadToLocation = false;

	PChar.quest.DarkHuman_Temple_Merc_After_Stash.win_condition.l1 = "location";
	PChar.quest.DarkHuman_Temple_Merc_After_Stash.win_condition.l1.location = "Temple";
	PChar.quest.DarkHuman_Temple_Merc_After_Stash.function = "DarkHuman_Temple_Merc_After_Stash";
}
void DarkHuman_Temple_Merc_After_Stash(string qName)
{
	AddQuestRecord("DarkHumanQuestline", "4");
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("DH_mercenary");
	ChangeCharacterAddressGroup(sld, "Temple", "goto", "goto3");
	Lai_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1.0, 0);
	sld.dialog.currentnode = "DH_mercenary_temple_afterstash";

	PChar.quest.DarkHuman_Amatike_return.win_condition.l1 = "location";
	PChar.quest.DarkHuman_Amatike_return.win_condition.l1.location = "Shore9";
	PChar.quest.DarkHuman_Amatike_return.function = "DarkHuman_Amatike_return";
}
void DarkHuman_Amatike_return(string qName)
{
	sld = GetCharacter(NPC_GenerateCharacter("DH_sailor", "officer_1", "man", "man", MOD_SKILL_ENEMY_RATE/2, PIRATE, 1, true));
	ChangeCharacterAddressGroup(sld, "Shore9", "smugglers", "smuggler02");
	Lai_SetActorType(sld);
	//LAi_ActorFollow(sld, pchar, "", -1);

	sld = CharacterFromID("DH_mercenary");
	ChangeCharacterAddressGroup(sld, "Shore9", "smugglers", "smugglerload");
	Lai_SetActorType(sld);

	PChar.quest.DarkHuman_Amatike_return_dialog.win_condition.l1 = "locator";
	PChar.quest.DarkHuman_Amatike_return_dialog.win_condition.l1.location = "Shore9";
	PChar.quest.DarkHuman_Amatike_return_dialog.win_condition.l1.locator_group = "encdetector";
	PChar.quest.DarkHuman_Amatike_return_dialog.win_condition.l1.locator = "enc02";
	PChar.quest.DarkHuman_Amatike_return_dialog.function = "DarkHuman_Amatike_return_dialog";
}

void DarkHuman_Amatike_return_dialog(string qName)
{
	sld = CharacterFromID("DH_mercenary");
	LAi_ActorDialog(sld, pchar, "", -1.0, 0);
	sld.dialog.currentnode = "DH_mercenary_Amatike_return";
	chrDisableReloadToLocation = true;
}

void DarkHuman_SK(string qName)
{
	CloseQuestHeader("DarkHumanIncquisitorJournal");
	DoReloadCharacterToLocation("SantaCatalina_exittown","goto", "goto1");
	DoQuestFunctionDelay("DarkHuman_SK_gate", 2.5);
}
void DarkHuman_SK_gate(string qName)
{
	LocatorReloadEnterDisable("Tenotchitlan_Jungle_03", "reload3_back", false);
	LocatorReloadEnterDisable("Tenotchitlan_Jungle_02", "reload1_back", false);

	LocatorReloadEnterDisable("SantaCatalina_town", "reload5_back", true);
	LocatorReloadEnterDisable("Villemstad_town", "gate_back", true);
	LocatorReloadEnterDisable("Villemstad_town", "reload4_back", true);
	LocatorReloadEnterDisable("SantaCatalina_exittown", "reload1_back", true);
	LocatorReloadEnterDisable("SantaCatalina_exittown", "reload2_back", true);
	AddQuestRecord("DarkHumanQuestline", "5");
	sld = CharacterFromID("DH_mercenary");
	LAi_ActorDialog(sld, pchar, "", -1.0, 0);
	sld.dialog.currentnode = "DH_mercenary_SK_gate";

	PChar.quest.DarkHuman_SK_tavern_dialog.win_condition.l1 = "location";
	PChar.quest.DarkHuman_SK_tavern_dialog.win_condition.l1.location = "SantaCatalina_tavern";
	PChar.quest.DarkHuman_SK_tavern_dialog.function = "DarkHuman_SK_tavern_dialog";
}
void DarkHuman_SK_tavern_dialog(string qName)
{
	chrDisableReloadToLocation = true;
	pchar.ContraInterruptWaiting = true;
	sld = CharacterFromID("DH_mercenary");
	ChangeCharacterAddressGroup(sld, "SantaCatalina_tavern", "goto", "goto2");
	LAi_ActorDialog(sld, pchar, "", -1.0, 0);
	sld.dialog.currentnode = "DH_mercenary_SK_vavern";

	for (i = 0; i < 4; i++)
	{
		sld = CharacterFromID("DH_merc_mush" + i);
		if (CheckAttribute(sld, "model"))
		{
			Lai_SetWarriorType(sld);
			sld.LifeDay = 0;
			LAi_warrior_DialogEnable(sld, false);
		}
		sld = CharacterFromID("DH_merc_blade" + i);
		if (CheckAttribute(sld, "model"))
		{
			Lai_SetWarriorType(sld);
			sld.LifeDay = 0;
			LAi_warrior_DialogEnable(sld, false);
		}
	}
}
void DarkHuman_Villemstad(string qName)
{
	DoReloadCharacterToLocation("Villemstad_town","reload", "reload1_back");
	sld = CharacterFromID("DH_mercenary");
	ChangeCharacterAddressGroup(sld, "Villemstad_town", "goto", "goto23");
	DoQuestFunctionDelay("DarkHuman_Villemstad_merc", 1.5);
}
void DarkHuman_Villemstad_merc(string qName)
{
	sld = CharacterFromID("DH_mercenary");
	LAi_ActorDialog(sld, pchar, "", -1.0, 0);
	sld.dialog.currentnode = "DH_Villemstad_merc";
	bDisableLandEncounters = false;
}
void SpeakAfterKill(string qName)
{
	sld = characterFromId(qName);
	Lai_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", -1.0, 0);
}

void DHmessages(string qName)
{
	Log_info("Первая - "+(1500 + rand(750)));
	DoQuestFunctionDelay("DHmessages_wait",1.0);
	DoQuestFunctionDelay("DHmessages_2",3.0);
}
void DHmessages_2(string qName)
{
	Log_info("Вторая - "+(1500 + rand(750)));
	DoQuestFunctionDelay("DHmessages_wait",1.0);
	DoQuestFunctionDelay("DHmessages_3",3.0);
}void DHmessages_3(string qName)
{
	Log_info("Третья - "+(1500 + rand(750)));
	DoQuestFunctionDelay("DHmessages_wait",1.0);
	DoQuestFunctionDelay("DHmessages_4",3.0);
}void DHmessages_4(string qName)
{
	Log_info("Четвертая - "+(1500 + rand(750)));
	DoQuestFunctionDelay("DHmessages_wait",1.0);
	DoQuestFunctionDelay("DHmessages_5",3.0);
}void DHmessages_5(string qName)
{
	Log_info("Пятая - "+(1500 + rand(750)));
}void DHmessages_wait(string qName)
{
	Log_info(" - Ожидайте - ");
}

void DHRaceAgainstTime(string qName)
{
	LocatorReloadEnterDisable("LaVega_town", "reload1", true);
	LocatorReloadEnterDisable("LaVega_town", "reload2", true);
	LocatorReloadEnterDisable("LaVega_town", "reload3", true);
	LocatorReloadEnterDisable("LaVega_town", "reload4", true);
	LocatorReloadEnterDisable("LaVega_town", "reload5", true);
	LocatorReloadEnterDisable("LaVega_town", "reload6", true);
	//LocatorReloadEnterDisable("LaVega_town", "reload7", true);
	LocatorReloadEnterDisable("LaVega_town", "reload8", true);
	LocatorReloadEnterDisable("LaVega_town", "reload1_back", true);
	LocatorReloadEnterDisable("LaVega_town", "reload3_back", true);

	AddQuestRecord("DHRaceAgainstTime", "4");

	PChar.quest.DHRaceAgainstTime1.win_condition.l1 = "location";
	PChar.quest.DHRaceAgainstTime1.win_condition.l1.location = "CommonRoom_MH2";
	PChar.quest.DHRaceAgainstTime1.function = "DHRaceAgainstTime_findHouse";
}

void DHRaceAgainstTime_findHouse(string qName)
{
	LocatorReloadEnterDisable("LaVega_town", "reload1", false);
	LocatorReloadEnterDisable("LaVega_town", "reload2", false);
	LocatorReloadEnterDisable("LaVega_town", "reload3", false);
	LocatorReloadEnterDisable("LaVega_town", "reload4", false);
	LocatorReloadEnterDisable("LaVega_town", "reload5", false);
	LocatorReloadEnterDisable("LaVega_town", "reload6", false);
	//LocatorReloadEnterDisable("LaVega_town", "reload7", false);
	LocatorReloadEnterDisable("LaVega_town", "reload8", false);
	LocatorReloadEnterDisable("LaVega_town", "reload1_back", false);
	LocatorReloadEnterDisable("LaVega_town", "reload3_back", false);

	if(GetQuestPastDayParam("pchar.questTemp.DHRaceAgainstTime") < 59)
	{
		chrDisableReloadToLocation = true;

		sld = GetCharacter(NPC_GenerateCharacter("DHMerc", "OZG_" + (rand(6) + 1), "man", "man", 10+MOD_SKILL_ENEMY_RATE, PIRATE, -1, false));
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		ChangeCharacterAddressGroup(sld, "CommonRoom_MH2", "goto", "goto4");
		GiveItem2Character(sld, "blade202");
		EquipCharacterByItem(sld, "blade202");
		sld.SaveItemsForDead = true;
		//LAi_SetImmortal(sld, true);
		Group_FindOrCreateGroup("DHAmbush");
		LAi_group_MoveCharacter(sld, "DHAmbush");
		pchar.quest.DHRaceAgainstTime_End.win_condition.c1 = "NPC_Death";
		pchar.quest.DHRaceAgainstTime_End.win_condition.c1.character ="DHMerc";

		sld = GetCharacter(NPC_GenerateCharacter("DHIncq", "PGG_Vincento_0", "man", "man", 5+MOD_SKILL_ENEMY_RATE, SPAIN, -1, true));
		ChangeCharacterAddressGroup(sld, "CommonRoom_MH2", "goto", "goto3");
		ChangeItemName("DeSouzaCross", "itmname_DeSouzaCross_DH");
		GiveItem2Character(sld, "DeSouzaCross");
		sld.SaveItemsForDead = true;
		LAi_group_MoveCharacter(sld, "DHAmbush");
		Lai_SetActorTypeNoGroup(sld);
		//LAi_SetImmortal(sld, true);
		LAi_ActorDialog(sld, pchar, "", 2.0, 0);

		pchar.quest.DHRaceAgainstTime_End.win_condition.c2 = "NPC_Death";
		pchar.quest.DHRaceAgainstTime_End.win_condition.c2.character ="DHIncq";
		PChar.quest.DHRaceAgainstTime_End.function = "DHRaceAgainstTime_End";

		sld.dialog.filename = "Quest\WhisperLine\DarkHuman.c";
		sld.dialog.currentnode = "DH_Ambush";
	}
	else
	{
		chrDisableReloadToLocation = false;
		AddQuestRecord("DHRaceAgainstTime", "3");
		CloseQuestHeader("DHRaceAgainstTime");
	}
}

void DHRaceAgainstTime_end(string qName)
{
	chrDisableReloadToLocation = false;
	group_DeleteGroup("DHAmbush");
	AddQuestRecord("DHRaceAgainstTime", "2");
	CloseQuestHeader("DHRaceAgainstTime");
}
void DHRaceAgainstTime_end_late(string qName)
{
	chrDisableReloadToLocation = false;
	AddQuestRecord("DHRaceAgainstTime", "3");
	CloseQuestHeader("DHRaceAgainstTime");
}
void DHLockSK(string qName)
{
	LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", true);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- Линейка Темного Странника --     конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  Капитул     начало
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void CaptureCapitol_SeaBattle()
{
	pchar.ContraInterruptWaiting = true;

	Group_FindOrCreateGroup("CaptureCapitol_SeaBattle");
	Group_SetType("CaptureCapitol_SeaBattle", "pirate");
	for (i = 1; i < 8; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("CaptureCapitol_enemyfleet"+i, "off_spa_"+(rand(1)+1), "man", "man", sti(pchar.rank)+10, SPAIN, -1, true));

		if (i == 1) FantomMakeQuickSailor(sld, SHIP_GALEON50, "Откровение", CANNON_TYPE_CANNON_LBS32, 50, 50, 50);
		if (i == 2) FantomMakeQuickSailor(sld, SHIP_GALEON1, "Деяния святых апостолов", CANNON_TYPE_CANNON_LBS24, 50, 50, 50);
		if (i == 3) FantomMakeQuickSailor(sld, SHIP_REVENGE, "Евангелие", CANNON_TYPE_CANNON_LBS32, 50, 50, 50);
		if (i == 4) FantomMakeQuickSailor(sld, SHIP_GALEON_H, "Плач Иеремии", CANNON_TYPE_CANNON_LBS32, 50, 50, 50);
		if (i == 5) FantomMakeQuickSailor(sld, SHIP_FELIPE, "Притчи", CANNON_TYPE_CANNON_LBS32, 50, 50, 50);
		if (i == 6) FantomMakeQuickSailor(sld, SHIP_WARGALLEON2, "Псалмы", CANNON_TYPE_CANNON_LBS32, 50, 50, 50);
		if (i == 7) FantomMakeQuickSailor(sld, SHIP_GALEON_L, "Бытие", CANNON_TYPE_CANNON_LBS16, 50, 50, 50);

		TakeNItems(sld, "Food5", 5);
		TakeNItems(sld, "potion2", 5);

		sld.AlwaysEnemy = true;

		Group_AddCharacter("CaptureCapitol_SeaBattle", sld.id);
		if (i == 1) Group_SetGroupCommander("CaptureCapitol_SeaBattle", sld.id);
		SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);

		//Group_SetPursuitGroup("CaptureCapitol_SeaBattle", PLAYER_GROUP);
		Group_SetTaskAttack("CaptureCapitol_SeaBattle", PLAYER_GROUP);
		Group_LockTask("CaptureCapitol_SeaBattle");

		Group_SetAddress("CaptureCapitol_SeaBattle", "Reefs", "reloas", "reload_1");
		string cnd = "l"+i;
		pchar.quest.CaptureCapitol_EndSeaBattle.win_condition.(cnd) = "NPC_Death";
		pchar.quest.CaptureCapitol_EndSeaBattle.win_condition.(cnd).character = sld.id;
	}
	PChar.quest.CaptureCapitol_EndSeaBattle.function = "CaptureCapitol_EndSeaBattle";
}

void CaptureCapitol_SeaBattleStarted(string q)
{
	pchar.LockMapReload = "Отступать уже поздно. Нужно дать бой испанцам";
	pchar.LockShoreReload = "Я не могу встать на якорь пока не уничтожу эскадру врага целиком.";
}

void CaptureCapitol_EndSeaBattle(string q)
{
	DeleteAttribute(pchar, "LockShoreReload");
	pchar.LockMapReload = "Некогда отступать. Нужно дать бой испанцам в бухте проклятых";
	AddQuestRecord("TheLastMass", "4");
	pchar.quest.CaptureCapitol_ShoreBattle.win_condition.l1          = "location";
	pchar.quest.CaptureCapitol_ShoreBattle.win_condition.l1.location = "DeckWithReefs";
	pchar.quest.CaptureCapitol_ShoreBattle.function             = "CaptureCapitol_ShoreBattle";
}

void FantomMakeQuickSailor(ref _Character, int _ShipType, string _ShipName, int _CannonsType, int _Sailing, int _Accuracy, int _Cannons)
{
    _Character.Ship.Cannons.Type = _CannonsType;
	_Character.skill.Sailing  = GetCoffDiff(_Sailing, SKILL_MAX);
	_Character.skill.Accuracy = GetCoffDiff(_Accuracy, SKILL_MAX);
	_Character.skill.Cannons  = GetCoffDiff(_Cannons, SKILL_MAX);

    //_Character.DontRansackCaptain = true; //квестовые не сдаются
    //_Character.SinkTenPercent     = false; // не тонуть при 10 процентах, не убегать в бою
    //_Character.AboardToFinalDeck  = true; // абордаж всегда
	//_Character.DontClearDead      = true;
	_Character.SaveItemsForDead   = true;
	//_Character.AlwaysSandbankManeuver = true;

    _Character.Ship.Type = GenerateShipExt(_ShipType, true, _Character);
    if (_ShipName == "none" || _ShipName == "") {SetRandomNameToShip(_Character)}
    else {_Character.Ship.Name = _ShipName}

    SetCrewQuantityFull(_Character);
    Fantom_SetBalls(_Character, "pirate");

	SetCharacterPerk(_Character, "FastReload");
	SetCharacterPerk(_Character, "HullDamageUp");
	SetCharacterPerk(_Character, "SailsDamageUp");
	SetCharacterPerk(_Character, "CrewDamageUp");
	SetCharacterPerk(_Character, "CriticalShoot");
	SetCharacterPerk(_Character, "LongRangeShoot");
	SetCharacterPerk(_Character, "CannonProfessional");
	SetCharacterPerk(_Character, "ShipDefenseProfessional");
	SetCharacterPerk(_Character, "ShipSpeedUp");
	SetCharacterPerk(_Character, "ShipTurnRateUp");

    DeleteAttribute(_Character, "ship.sails");// убрать дыры на парусах
    DeleteAttribute(_Character, "ship.blots");
    DeleteAttribute(_Character, "ship.masts");// вернуть сбытые мачты
    DeleteAttribute(_Character, "Killer.status"); // снять аттрибут 'был захвачен на абордаж'
    _Character.questTemp.abordage = 0; //снять аттрибут отказа повторного захвата
   	DeleteAttribute(_Character, "Abordage.Enable"); //снять невозможноть абордажа
}

void CaptureCapitol_ShoreBattle(string q)
{
	DeleteAttribute(pchar, "LockMapReload");
	chrDisableReloadToLocation = true;

	ref chr;
	string attrName, sLoc, sLoc_2, relation;
	int i, iRnd, iNation, perSailor;

	relation = LAI_GROUP_PLAYER;
	sLoc = "Reefs";
	iNation = SPAIN;

	perSailor = 50;
	iRnd = GetCrewQuantity(pchar)/perSailor - GetOfficersQuantity(pchar);

	pchar.CaptureCapitolSailors = iRnd;
	pchar.CaptureCapitolPerSailor = perSailor;

	PChar.GenQuestFort.FarLocator = false;
	sLoc = LAi_FindNPCLocator("officers");
	for (i = 1; i < iRnd; i++)
	{
		chr = SetFantomDefenceForts("officers", sLoc, PIRATE, relation);
		FantomMakeCoolFighterWRankDepend(chr,sti(pchar.rank),25+rand(75),25+rand(75),50);

		string cnd = "CaptureCapitolSailor"+i;
		pchar.quest.(cnd).win_condition.(cnd) = "NPC_Death";
		pchar.quest.(cnd).win_condition.(cnd).character = chr.id;
		pchar.quest.(cnd).function = "CaptureCapitol_SailorDead";
	}
	Pchar.GenQuestFort.FarLocator = true;

	//enemy
	iRnd = iRnd + sti(pchar.rank) + MOD_SKILL_ENEMY_RATE;
	Pchar.GenQuestFort.FarLocator = true;
	sLoc = LAi_FindNPCLocator("quest");
	sLoc_2 = LAi_FindNPCLocator("reload");
	for (i = 1; i < iRnd; i++)
	{
		if (i % 2 == 0)
		{
		chr = SetFantomDefenceForts("quest", sLoc, iNation, "CaptureCapitol");
		}
		else
		{
			chr = SetFantomDefenceForts("reload", sLoc_2, iNation, "CaptureCapitol");
		}
		chr.id = "pirate_" + i;
		FantomMakeCoolFighterWRankDepend(chr,sti(pchar.rank),25+rand(75),25+rand(75),50);
	}
	//натравим.
	LAi_group_SetHearRadius("CaptureCapitol", 100.0);
	LAi_group_FightGroupsEx("CaptureCapitol", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
	LAi_group_FightGroupsEx("CaptureCapitol", relation, true, Pchar, -1, false, false);

	LAi_group_SetCheckFunction("CaptureCapitol", "CaptureCapitol_ShoreBattleRespite");

	LAi_SetFightMode(pchar, true);
}

void CaptureCapitol_SailorDead(string q)
{
	SetCrewQuantity(pchar, GetCrewQuantity(pchar) - sti(pchar.CaptureCapitolPerSailor));
}

void CaptureCapitol_ShoreBattleRespite(string q)
{
	ref locLoad = &locations[reload_location_index];
	LAi_LocationFightDisable(locLoad, true);
	DoQuestCheckDelay("hide_weapon", 2.0);
	sld = GetCharacter(NPC_GenerateCharacter("CapitolLeader", "Dark_Incquisitor", "man", "man", 99, SPAIN, -1, true));

	if (startherotype == 2)
	{
		FantomMakeCoolFighter(sld, 100, 100, 100, "blade24", "pistol7shotgun", 80);
		TakeNItems(sld, "12_gauge", 99);
	}
	else	FantomMakeCoolFighter(sld, 100, 100, 100, "blade24", "pistol4", 80);
	LAi_SetHP (sld, MOD_SKILL_ENEMY_RATE * 150 + 500, MOD_SKILL_ENEMY_RATE * 150);
	SetSPECIAL(sld, 10, 10, 10, 10, 10, 10, 10);
	sld.cirassID = Items_FindItemIdx("cirass5");
	sld.SaveItemsForDead = true;

	sld.name 	= "Хулио";
	sld.lastname 	= "Иглесиас";
	sld.Dialog.CurrentNode = "OrderLeader";
	sld.dialog.filename = "Quest\WhisperLine\Whisper.c";
	Lai_SetStayType(sld);
	sld.talker = 10;
	ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload2_back");
}

void CaptureCapitol_ShoreBattleRaiseUndead(string q)
{
	ref locLoad = &locations[reload_location_index];
	LAi_LocationFightDisable(locLoad, false);

	pchar.OrderDestroyed = true;
	SetReefSkeletonsToLocation(locLoad, "DeckWithReefs");
}

void CaptureCapitol_ShoreBattleEnd()
{
	if (CheckAttribute(pchar, "OrderDestroyed"))
	{
		chrDisableReloadToLocation = false;

		for (i = 1; i < sti(pchar.CaptureCapitolSailors); i++)
		{
			string cnd = "CaptureCapitolSailor"+i;
			PChar.quest.(cnd).over = "yes";
		}
		DeleteAttribute(pchar, "CaptureCapitolSailors");
		DeleteAttribute(pchar, "CaptureCapitolPerSailor");

		LocatorReloadEnterDisable(pchar.location, "reload1", true);
		LocatorReloadEnterDisable(pchar.location, "reload2", false);

		pchar.quest.CaptureCapitol_ChapterEnter.win_condition.l1          = "location";
		pchar.quest.CaptureCapitol_ChapterEnter.win_condition.l1.location = "Reefs_Chapter";
		pchar.quest.CaptureCapitol_ChapterEnter.function             = "CaptureCapitol_ChapterEnter";
	}
}

void CaptureCapitol_ChapterEnter(string q)
{
	DoQuestFunctionDelay("CaptureCapitol_ChapterEnter_1",0)
	chrDisableReloadToLocation = true;
}
void CaptureCapitol_ChapterEnter_1(string q)
{
	for (int j=1; j<=6; j++)
	{
		sld = CharacterFromID("MaltGuard_"+j);
		ChangeCharacterAddressGroup(sld, "none", "none", "none");
	}
	sld = CharacterFromID("CapitolLeader");
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto6");
	sld.Dialog.CurrentNode = "OrderLeader_1";
	LAi_SetStayType(sld);
	sld.talker = 10;
}

void CaptureCapitol_OnLeaderDeath()
{
	for (int j=1; j<=6; j++)
	{
		string cnd = "MaltGuard_"+j;
		pchar.quest.CaptureCapitol_OnLeaderDeath_1.win_condition.(cnd) = "NPC_Death";
		pchar.quest.CaptureCapitol_OnLeaderDeath_1.win_condition.(cnd).character = cnd;
	}
	pchar.quest.CaptureCapitol_OnLeaderDeath_1.win_condition.l1 = "NPC_Death";
	pchar.quest.CaptureCapitol_OnLeaderDeath_1.win_condition.l1.character = "CapitolLeader";
	pchar.quest.CaptureCapitol_OnLeaderDeath_1.function = "CaptureCapitol_OnLeaderDeath_1";
}

void CaptureCapitol_OnLeaderDeath_1(string q)
{
	ref locLoad = &locations[reload_location_index];
	LAi_LocationFightDisable(locLoad, true);
	DoQuestCheckDelay("hide_weapon", 2.0);

	if (startherotype == 2)	sld = CharacterFromID("Wh_Jim");
	else sld = GetCharacter(NPC_GenerateCharacter("Wh_Jim", "officer_"+(rand(63)+1), "man", "man", 5, PIRATE, -1, false));
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto7");
	LAi_SetActorTypeNoGroup(sld);
    LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	sld.Dialog.Filename = "Quest\WhisperLine\Whisper.c";
	sld.Dialog.CurrentNode = "CapitolCaptured";
}

void CaptureCapitol_Decision(string q)
{
	LocatorReloadEnterDisable(pchar.location, "reload1", false);
	if(CheckAttribute(pchar, "SellCapitol"))
	{
		LocatorReloadEnterDisable(pchar.location, "reload2", true);
		AddQuestRecord("TheLastMass", "6");
	}
	else
	{
		BuildPirateOrder();
		AddQuestRecord("TheLastMass", "5");
		CloseQuestHeader("TheLastMass");
	}
}
void BuildPirateOrder()
{
	Locations[FindLocation("DeckWithReefs")].reload.l2.label = "Reefs_Chapter";
	Locations[FindLocation("Reefs_Chapter")].id.label = "Reefs_Chapter";
	pchar.PirateOrder = true;
	sld = CharacterFromID("Wh_Jim");
	ChangeCharacterAddressGroup(sld, "Reefs_Chapter", "sit", "sit1");
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
	LAi_SetImmortal(sld, true);
	sld.Dialog.Filename = "MalteseOrder.c";
	sld.City = "Reefs";
}
//todo: Если найдётся подходящая модель, посадить в одну из клеток Капитула пленницу (Новый квест и потенциальный оф)
//Добавить возможность оставить собственного пленника в темнице, чтобы через время выбить из него генераторный квест
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- Капитул --     конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   Квест ПГГ Виспер     начало
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void QuestWhisper_RoomFight(string q)
{
	ref chr;

	chr = CharacterFromID(pchar.WhisperId);
	chr.dialog.currentnode   = "Quest_Whisper_8";
	DoQuestCheckDelay("hide_weapon", 2.0);
	LAi_SetActorTypeNoGroup(chr);
	LAi_ActorDialog(chr, pchar, "", -1, 0);
	chrDisableReloadToLocation = true;
	DoQuestCheckDelay("OpenTheDoors", 3.0);
}

void QuestWhisper_Siege(string q)
{
	ref chr;
	chr = CharacterFromID(pchar.WhisperId);
	ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto20");
	chr.dialog.currentnode   = "Quest_Whisper_ToSiege";
	LAi_SetStayTypeNoGroup(chr);
	chr.talker = 10;

	GiveItem2Character(chr, "blade_whisper");
	EquipCharacterByItem(chr, "blade_whisper");
	GiveItem2Character(chr, "pistol_grapebok");
	EquipCharacterByItem(chr, "pistol_grapebok");
	GiveItem2Character(chr, "cirass5");
	EquipCharacterbyItem(chr, "cirass5");
	TakeNItems(chr, "GunPowder", 30);
    TakeNItems(chr, "grapeshot", 30);

	chr.perks.list.AgileMan = "1";
	ApplayNewSkill(chr, "AgileMan", 0);

	chr.SPECIAL.Agility = 10;
	chr.SPECIAL.Intellect = 10;
	chr.SPECIAL.Endurance = 10;
	chr.SPECIAL.Luck = 10;
	LAi_SetHP(chr, LAi_GetCharacterMaxHP(chr) + 100, LAi_GetCharacterMaxHP(chr) + 100);
	AddBonusEnergyToCharacter(chr, 80);
	AddCharacterExpToSkill(chr, "FencingLight", 20000);
	AddCharacterExpToSkill(chr, "Pistol", 20000);
	RemoveSpeciality(chr);
	SetCharacterPerk(chr, "Adventurer");

	chrDisableReloadToLocation = true;

	ClearIslandShips("Santiago");
    Colonies[FindColony("Santiago")].DontSetShipInPort = true;
	chr = CharacterFromID("Santiago Fort Commander");
	SetCrewQuantity(chr,500 + rand (100));

	pchar.LockMapReload = "Ну уж нет. Если я сейчас уплыву, шанс взять этот форт без больших потерь будет навсегда упущен.";
}
void QuestWhisper_Siege_1()
{
	ref chr;

	chr = CharacterFromID(pchar.WhisperId);
	chr.dialog.currentnode   = "Quest_Whisper_AfterSiege";
	DoQuestCheckDelay("hide_weapon", 2.0);
	LAi_SetActorTypeNoGroup(chr);
	LAi_ActorDialog(chr, pchar, "", -1, 0);
	chrDisableReloadToLocation = true;
}

void QuestWhisper_Incq(string q)
{
	chrDisableReloadToLocation = true;
	DoQuestFunctionDelay("QuestWhisper_Incq_1", 0.1);
	DoQuestFunctionDelay("QuestWhisper_Incq_2", 11.0 - MOD_SKILL_ENEMY_RATE);
	sld = CharacterFromID(pchar.WhisperId);
	ChangeCharacterAddressGroup(sld, "Santiago_Incquisitio", "goto", "goto14");
	LAi_SetWarriorTypeNoGroup(sld);
	LAi_group_FightGroups("SPAIN_CITIZENS", LAI_GROUP_PLAYER, true);
}
void QuestWhisper_Incq_1(string q)
{
	string cnd;
	int j;
	for (j=1; j<=3; j++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Incquisitor_"+j, "priest_sp"+j, "man", "man", 20, SPAIN, 1, true));
		ChangeCharacterAddressGroup(sld, "Santiago_Incquisitio", "goto", "goto1"+j);
		LAi_SetWarriorTypeNoGroup(sld);
		cnd = "i"+j;
		pchar.quest.QuestWhisper_Incq_3.win_condition.(cnd) = "NPC_Death";
		pchar.quest.QuestWhisper_Incq_3.win_condition.(cnd).character = sld.id;
	}
	for (j=1; j<=4; j++)
	{
		sld = CharacterFromID("IncqGuard_"+j);
		cnd = "ig"+j;
		pchar.quest.QuestWhisper_Incq_3.win_condition.(cnd) = "NPC_Death";
		pchar.quest.QuestWhisper_Incq_3.win_condition.(cnd).character = sld.id;
	}
	pchar.quest.QuestWhisper_Incq_3.function = "QuestWhisper_Incq_3";
}

void QuestWhisper_Incq_2(string q)
{
	sld = CharacterFromID(pchar.WhisperId);
	string sGun = GetCharacterEquipByGroup(sld, GUN_ITEM_TYPE);
	ref rItm = ItemsFromID(sGun);
	int iCharge = iGetPistolChargeNum(sld, LAi_GunSetChargeQuant(sld,sti(rItm.chargeQ)));
	LAi_SetImmortal(sld, false);
	DeleteAttribute(sld, "SaveItemsForDead");
}

void QuestWhisper_Incq_3(string q)
{
	sld = CharacterFromID(pchar.WhisperId);
	sld.dialog.currentnode   = "Quest_Whisper_Incq";
	if (LAi_IsDead(sld))
	{
		DeleteCharacter(sld);
		LAi_SetCurHPMax(sld);
		sld.dialog.currentnode   = "Quest_Whisper_Incq_fall";
		DoQuestFunctionDelay("QuestWhisper_Incq_3_1", 1.0);
		PGG_ChangeRelation2MainCharacter(sld, 30);
		sld.FailedRecruitment = true;
	}
	DoQuestCheckDelay("hide_weapon", 2.0);
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void QuestWhisper_Incq_3_1(string q)
{
	sld = CharacterFromID(pchar.WhisperId);
	ChangeCharacterAddressGroup(sld, "Santiago_Incquisitio", "goto", "goto14");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void QuestWhisper_Incq_4(string q)
{
	sld = CharacterFromID(pchar.WhisperId);
	sld.dialog.currentnode   = "Quest_Whisper_Incq_1";
	LAi_SetStayTypeNoGroup(pchar);
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);

	sld.HasNoFear = true;
	GiveItem2Character(sld, "pistol7shotgun");
	EquipCharacterByItem(sld, "pistol7shotgun");
	sld.DontChangeGun = true;
	TakeNItems(sld, "12_gauge", 50);
    TakeNItems(sld, "grapeshot", 50);
	DeleteAttribute(pchar, "PGGWhisperLetterSent");
}

void QuestWhisper_Incq_5(string q)
{
	LAi_group_SetRelation("SPAIN_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	sld = CharacterFromID(pchar.WhisperId);
	ChangeCharacterAddressGroup(sld, "Santiago_Town", "patrol", "patrol10");
	sld.dialog.currentnode   = "Quest_Whisper_Finish";
	chrDisableReloadToLocation = true;
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", 5, 0);
}

bool WhisperIsHere()
{
	if (CheckAttribute(pchar, "WhisperId"))
	{
		sld = CharacterFromID(pchar.WhisperId);
		if (sld.location == pchar.location && !LAi_IsDead(sld))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool WhisperIsOfficer()
{
	if (CheckAttribute(pchar, "WhisperId"))
	{
		sld = CharacterFromID(pchar.WhisperId);
		if (IsOfficer(sld))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

void W_RestoreOfficerDialog()
{
	ref chr = CharacterFromID(pchar.WhisperPGG)
	chr.Dialog.Filename = "Enc_Officer_dialog.c";
	chr.dialog.currentnode   = "hired";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- Квест ПГГ Виспер --     конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   Квест Титаник     начало
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void RefreshTitanic()
{
	sld = CharacterFromID("W_Titanic");
	//sld.AlwaysFriend = true;

	ProcessHullRepair(sld, 100.0 - sti(pchar.rank));
	ProcessSailRepair(sld, 100.0);
	DeleteAttribute(sld, "ship.blots");
	DeleteAttribute(sld, "ship.sails");
	DeleteAttribute(sld, "ship.masts");
	SetCrewQuantityFull(sld);

	DeleteAttribute(pchar, "Abordage.Enable");
}

void RefreshTitanic_1(string q)
{
	if(CheckAttribute(pchar, "TitanicIsKicking"))
	{
		AddQuestRecord("WhisperTitanic", 5);
		AddQuestUserData("WhisperTitanic", "sCity", XI_ConvertString("Colony" + pchar.TitanicCity));
		RefreshTitanic();
		WhisperTitanic_ToRandomTown();
		Log_TestInfo("Титаник уплыл в" + pchar.TitanicCity);
		pchar.quest.WhisperTitanic_SurrenderFort.win_condition.l1          = "location";
		pchar.quest.WhisperTitanic_SurrenderFort.win_condition.l1.location = pchar.TitanicCity;
		pchar.quest.WhisperTitanic_SurrenderFort.function             = "WhisperTitanic_SurrenderFort";
	}
}

void WhisperTitanic_ToRandomTown()
{
	if (CheckAttribute(&colonies[1], "nation"))
	{
		int n, nation;
		int storeArray[MAX_COLONIES];
		int howStore = 0;
		for(n=0; n<MAX_COLONIES; n++)
		{
			if (colonies[n].nation == SPAIN)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
		bool townIsSet = false;
		string prevCity = "";
		if(CheckAttribute(pchar, "TitanicCity"))	prevCity = pchar.TitanicCity;
		while (!townIsSet)
		{
			nation = storeArray[rand(howStore-1)];
			pchar.TitanicCity = colonies[nation].id;
			if (colonies[nation].id == "Beliz" || colonies[nation].id == "Santacatalina" || colonies[nation].id == "PortoBello" || colonies[nation].id == "Cartahena" || colonies[nation].id == "Maracaibo" || colonies[nation].id == "Caracas" || colonies[nation].id == "Cumana") townIsSet = true;
			if(prevCity == pchar.TitanicCity) townIsSet = false;
		}
		Group_SetAddress("WarDog", pchar.TitanicCity, "Quest_ships", "reload_fort1_siege");
		pchar.TitanicRumour = true;
	}
}
void WhisperTitanic_SurrenderFort(string q)
{
	DoQuestFunctionDelay("WhisperTitanic_SurrenderFort_1", 0);
	PChar.quest.RefreshTitanic_1.win_condition.l1 = "ExitFromLocation";
	PChar.quest.RefreshTitanic_1.win_condition.l1.location = pchar.location;
	PChar.quest.RefreshTitanic_1.function = "RefreshTitanic_1";
}
void WhisperTitanic_SurrenderFort_1(string q)
{
	Log_Info("Похоже, что солдаты из форта уже сдались англичанам.")
	sld = CharacterFromID(pchar.TitanicCity + " Fort Commander");
	sld.Fort.DieTime.Year = GetDataYear();
	sld.Fort.DieTime.Month = GetDataMonth();
	sld.Fort.DieTime.Day = GetDataDay();
	sld.Fort.DieTime.Time = GetTime();
	sld.Fort.Mode = FORT_DEAD;
}

void WhisperTitanic_Is_Dead(string q)
{
	AddQuestRecord("WhisperTitanic", 2);
	DeleteAttribute(pchar, "TitanicIsKicking");
	DeleteAttribute(pchar, "TitanicRumour");
	pchar.TitanicIsDown = true;
	Log_Info("Titanic is down");
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- Квест Титаник --     конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////
