
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Блейз и Беатрис
/////////////////////////////////////////////////////////////////////////////////////////////////////////
int weaponskill;
void Sharp_StartGame(string qName)
{
	SetQuestsCharacters();
	bDisableLandEncounters = true;
	LocatorReloadEnterDisable("Shore57", "boat", true);
	pchar.cursed.waitingSkull = true;

	//Вступительный монолог
	pchar.questTemp.Sharp.Entered_Shore = true;
	DoQuestCheckDelay("TalkSelf_Quest", 1.0);

	pchar.quest.Sharp_MeetSiblings.win_condition.l1          = "location";
    pchar.quest.Sharp_MeetSiblings.win_condition.l1.location = "Terks_Grot";
    pchar.quest.Sharp_MeetSiblings.function                  = "Sharp_MeetSiblings";

}

void SharpAfterTreasure(string qName)
{
	DeleteAttribute(pchar, "cursed.waitingSkull");
	bDisableLandEncounters = false;
	LocatorReloadEnterDisable("Shore57", "boat", false);
}

void SharpExitFromCave(string qName)
{
	chrDisableReloadToLocation = false;
}
void Sharp_MeetSiblings(string qName)
{
	for (i = 1; i <= PsHeroQty; i++)
	{
		sld = CharacterFromID("PsHero_" + i);
		if(sld.FaceId == 1 || sld.FaceId == 522)
		{//Его мы позже наймем оффом, так что убираем из ПГГ
			sld.willDie = true;
			LAi_KillCharacter(sld);
		}
	}
	chrDisableReloadToLocation = true;
	if (startherotype == 3)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Sharp_Sibling", "PGG_Devlin_0", "man", "man", 1, PIRATE, -1, true));
		sld.dialog.filename = "Quest\MainheroPrologues\Prologue_Blaze_dialog.c";
		sld.name = "Блэйз";
		sld.lastname = "Шарп";
		sld.HeroModel = "PGG_Devlin_0,PGG_Devlin_1,PGG_Devlin_2,PGG_Devlin_3,PGG_Devlin_4,PGG_Devlin_5,PGG_Devlin_6,PGG_Devlin_7,PGG_Devlin_8";
	}
	else
	{
		sld = GetCharacter(NPC_GenerateCharacter("Sharp_Sibling", "PGG_Beatric_0", "woman", "YokoDias", 1, PIRATE, -1, true));
		sld.dialog.filename = "Quest\MainheroPrologues\Prologue_Beatrice_dialog.c";
		sld.name = "Беатрис";
		sld.lastname = "Шарп";
		sld.HeroModel = "PGG_Beatric_0,PGG_Beatric_1,PGG_Beatric_2,PGG_Beatric_3,PGG_Beatric_4,PGG_Beatric_5,PGG_Beatric_6,PGG_Beatric_7,PGG_Beatric_8";
	}
	ChangeCharacterAddressGroup(sld, PChar.location, "monsters", "monster1");
	//sld.greeting = "cit_common";
	//Добавить звуки
	LAi_SetStayTypeNoGroup(sld);
   	LAi_SetImmortal(sld, true);
	sld.talker = 10;
	weaponskill = 5* MOD_SKILL_ENEMY_RATE;
	SetSelfSkill(sld, weaponskill, weaponskill, weaponskill, weaponskill, weaponskill);
	if (MOD_SKILL_ENEMY_RATE == 10)
	{//Сюрприз для невозможки
		SetCharacterPerk(sld, "Sliding");
	}
	LAi_SetHP(sld, 100.0, 100.0);
	sld.Ship.Type = GenerateShipExt(SHIP_SLOOP, true, sld);
	sld.Ship.name = "Любимец удачи";
	SetBaseShipData(sld);
	sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS12;
	Group_FindOrCreateGroup("SharpSibling");
	Group_AddCharacter("SharpSibling", sld.id);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- Блейз и Беатрис --     конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Шарль и Мэри
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void SharleMary_StartGame(string qName)
{
	SetQuestsCharacters();
	bDisableLandEncounters = true;
	LocatorReloadEnterDisable("Shore_ship2", "boat", true);

	//Вступительный монолог
	pchar.questTemp.SharleMary.Entered_Shore = true;
	DoQuestCheckDelay("TalkSelf_Quest", 1.0);

	pchar.quest.SharleMary_Indians.win_condition.l1          = "location";
    pchar.quest.SharleMary_Indians.win_condition.l1.location = "Common_jungle_01";
    pchar.quest.SharleMary_Indians.function                  = "SharleMary_Indians";

	GiveItem2Character(pchar, "blade4");
	GiveItem2Character(pchar, "blade6");
	GiveItem2Character(pchar, "blade35");
	EquipCharacterbyItem(pchar, "blade4");
	TakeNItems(pchar, "potion1", 10);
	AddMoneyToCharacter(PChar, 5000);
}

void SharleMary_Indians(string qName)
{
	for (i = 1; i <= PsHeroQty; i++)
	{
		sld = CharacterFromID("PsHero_" + i);
		if(sld.FaceId == 508 || sld.FaceId == 517)
		{//Его мы позже наймем оффом, так что убираем из ПГГ
			sld.willDie = true;
			LAi_KillCharacter(sld);
		}
	}
	//Заблокировать меню персонажа
	bDisableCharacterMenu = true;
	chrDisableReloadToLocation = true;
	string cnd;
	int maxIndians = 2;
	if (MOD_SKILL_ENEMY_RATE == 10)
	{//Сюрприз для невозможки
		maxIndians++;
	}
	for (int i = 1; i<=maxIndians; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("SMindian"+i, "Canib_"+(rand(5)+1), "man", "man", 1, PIRATE, 1, true));
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
		if (MOD_SKILL_ENEMY_RATE == 10)
		{//Сюрприз для невозможки
			//FantomMakeCoolFighter(sld, 15, 10, 10, _Blade, "", 0);
			SetCharacterPerk(sld, "Sliding");
			LAi_SetHP(sld, 150.0, 150.0);
		}
		LAi_SetWarriorTypeNoGroup(sld);
		LAi_group_MoveCharacter(sld, "Jungle_indians");

		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto3");
		cnd = "l" + i;
		pchar.quest.SharleMary_Meeting.win_condition.(cnd) = "NPC_Death";
		pchar.quest.SharleMary_Meeting.win_condition.(cnd).character ="SMindian"+i;
	}
	PChar.quest.SharleMary_Meeting.function = "SharleMary_Meeting";

	LAi_group_SetRelation("Jungle_indians", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("Jungle_indians", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("Jungle_indians", "IndianInJungleClearGroup");

	if (startherotype == 5)
	{
		sld = GetCharacter(NPC_GenerateCharacter("SharleMary", "PGG_Mary", "woman", "YokoDias", 1, PIRATE, -1, true));
		sld.name = "Мэри";
		sld.lastname = "Каспер";
		sld.HeroModel = "PGG_Mary";
		sld.greeting = "GR_marycasper";
	}
	else
	{
		sld = GetCharacter(NPC_GenerateCharacter("SharleMary", "PGG_ShMor_0", "man", "man", 1, PIRATE, -1, true));
		sld.name = "Шарль";
		sld.lastname = "де Мор";
		sld.HeroModel = "PGG_ShMor_0,PGG_ShMor_1,PGG_ShMor_2,PGG_ShMor_3,PGG_ShMor_4,PGG_ShMor_5,PGG_ShMor_6,PGG_ShMor_7,PGG_ShMor_8";
		sld.greeting = "Gr_Officer";
	}
	SetSelfSkill(sld,20, 20, 20, 20, 20);
	sld.cirassId = Items_FindItemIdx("cirass4");  // предмета нет, но влияение есть
	TakeNItems(sld, "potion1", 10);
	GiveItem2Character(sld, "blade8");
	EquipCharacterbyItem(sld, "blade8");
	sld.dialog.filename = "Quest\MainheroPrologues\Prologue_SharleMary_dialog.c";
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto5");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	LAi_SetHP(sld, 300.0, 300.0);
}

void SharleMary_Meeting(string qName)
{
	if(!LAi_IsDead(CharacterFromID("SharleMary")))
	{
		sld = characterFromID("SharleMary");
		DeleteAttribute(sld, "chr_ai.poison");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}
	else
	{
		pchar.questTemp.SharleMary.Death = true;
		DoQuestCheckDelay("TalkSelf_Quest", 1.0);
		pchar.SharleMary.LowerIsDead = true;
	}

	pchar.quest.SharleMary_MeetCap.win_condition.l1          = "location";
    pchar.quest.SharleMary_MeetCap.win_condition.l1.location = "Shore_ship2";
    pchar.quest.SharleMary_MeetCap.function                  = "SharleMary_MeetCap";

	setCharacterShipLocation(pchar, "Shore_ship2");
    setWDMPointXZ("Shore_ship2");  // коорд на карте
}

void SharleMary_MeetCap(string qName)
{
	chrDisableReloadToLocation = true;
	if (!CheckAttribute(pchar, "SharleMary.LowerIsDead"))
	{
		sld = characterFromID("SharleMary");
		ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
		LAi_SetCurHPMax(sld);
	}
	ref LocLoad = &locations[reload_location_index];
	LAi_LocationFightDisable(locLoad, true);
	int maxPirates = 3;
	string cnd;
	if (MOD_SKILL_ENEMY_RATE == 10)
	{//Сюрприз для невозможки
		maxPirates++;
	}
	pchar.SharleMary.maxPirates = maxPirates;
	for (int i = 1; i<=maxPirates; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("SMPirate"+i, "pirate_"+(rand(15)+1), "man", "man", 1, PIRATE, 1, true));
		LAi_SetHP(sld, 10*MOD_SKILL_ENEMY_RATE, 10*MOD_SKILL_ENEMY_RATE);
		LAi_SetStayType(sld);
		if (i == 1)
		{
			sld.model = "PGG_Yohang_0";
			sld.dialog.filename = "Quest\MainheroPrologues\Prologue_SharleMary_dialog.c";
			FantomMakeCoolFighter(sld, 10, 2*MOD_SKILL_ENEMY_RATE, 2*MOD_SKILL_ENEMY_RATE, "blade31", "", 6*MOD_SKILL_ENEMY_RATE);
			sld.SaveItemsForDead = true;
			sld.talker = 10;
			LAi_SetStayType(sld);
		}
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto1");

		cnd = "l" + i;
		pchar.quest.SharleMary_MeetCrew.win_condition.(cnd) = "NPC_Death";
		pchar.quest.SharleMary_MeetCrew.win_condition.(cnd).character ="SMPirate"+i;
	}
	PChar.quest.SharleMary_MeetCrew.function = "SharleMary_MeetCrew";
}

void SharleMary_FightPirates()
{
	if (!CheckAttribute(pchar, "SharleMary.LowerIsDead"))
	{
		sld = CharacterFromID("SharleMary");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_SetCurHPMax(sld);
	}
	ref LocLoad = &locations[reload_location_index];
	LAi_LocationFightDisable(locLoad, false);
	for (int i = 1; i<= sti(pchar.SharleMary.maxPirates); i++)
	{
		sld = CharacterFromID("SMPirate"+i);
		LAi_SetWarriorTypeNoGroup(sld);
		LAi_group_MoveCharacter(sld, "Jungle_indians");
		LAi_SetImmortal(sld, false);
	}
	LAi_group_SetRelation("Jungle_indians", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("Jungle_indians", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("Jungle_indians", "IndianInJungleClearGroup");
}

void SharleMary_MeetCrew(string qName)
{
	bDisableLandEncounters = false;
	for (int i = 1; i<=5; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("SMCrew"+i, "pirate_"+(rand(15)+1), "man", "man", 1, PIRATE, 0, true));
		ChangeCharacterAddressGroup(sld, PChar.location, "officers", "sea_1");
		LAi_SetImmortal(sld, true);
		if (i == 1)
		{
			sld.dialog.filename = "Quest\MainheroPrologues\Prologue_SharleMary_dialog.c";
			FantomMakeCoolFighter(sld, 15, 20, 20, "blade31", "", 100);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- Шарль и Мэри --     конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Нежить
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void Undead_StartGame(string qName)
{
	DeleteAttribute(Pchar, "ship");
    DeleteAttribute(Pchar, "ShipSails.gerald_name");
    Pchar.ship.type = SHIP_NOTUSED;

	WaitDate("",0,0,0,24 - sti(environment.time),5);

	SetQuestsCharacters();

	LAi_LockFightMode(Pchar, false);
	LAi_LocationFightDisable(loadedLocation, true);
	sld = GetCharacter(NPC_GenerateCharacter("DeadmansGod", "mictlantecuhtli", "skeleton", "man", 100, PIRATE, 0, true));
    FantomMakeCoolFighter(sld, 50, 100, 100, "toporAZ", "pistol4", 3000); //дадим четырехствольник
	sld.name = "Миктлантекутли";
	sld.lastname = "";
	//sld.dialog.filename   = "Quest\Mictlantecuhtli.c";
	sld.dialog.filename   = "Quest\MainheroPrologues\Prologue_Undead_dialog.c";
	//sld.dialog.currentnode   = "ClimeUsurer";
	sld.dialog.currentnode   = "DeadmansGod";
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "Temple_Skulls", "goto", "goto3");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 5.0, 0);
}

void Undead_Start_Graveyard(string qName)
{
	PlaySound("interface\grob.wav");
}
void Undead_Start_Graveyard_1(string qName)
{
	sld = GetCharacter(NPC_GenerateCharacter("Gravedigger", "panhandler_"+(rand(5)+1), "man", "man", 1, PIRATE, 0, true));
	sld.dialog.filename   = "Quest\MainheroPrologues\Prologue_Undead_dialog.c";
	sld.dialog.currentnode   = "Gravedigger";
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto2");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 5.0, 0);

	pchar.quest.Undead_Start_Graveyard_2.win_condition.l1 = "NPC_Death";
	pchar.quest.Undead_Start_Graveyard_2.win_condition.l1.character ="Gravedigger";
	PChar.quest.Undead_Start_Graveyard_2.function = "Undead_Start_Graveyard_3";
}
/*
void Undead_Start_Graveyard_2(string qName)
{
	PChar.quest.Undead_Start_Graveyard_3.win_condition.l1 = "locator";
	PChar.quest.Undead_Start_Graveyard_3.win_condition.l1.location = pchar.location;
	PChar.quest.Undead_Start_Graveyard_3.win_condition.l1.locator_group = "box";
	PChar.quest.Undead_Start_Graveyard_3.win_condition.l1.locator = "box1";
	PChar.quest.Undead_Start_Graveyard_3.function = "Undead_Start_Graveyard_3";
}*/
void Undead_Start_Graveyard_3(string qName)
{
	TakeNItems(pchar, "suit_1", 1);
	Log_Info("Вы получили обноски");
	PlaySound("interface\important_item.wav");
	pchar.questTemp.Undead.Leave_Crypt = true;
	DoQuestCheckDelay("TalkSelf_Quest", 1.0);
	PChar.quest.Undead_Start_Graveyard_4.win_condition.l1 = "locator";
	PChar.quest.Undead_Start_Graveyard_4.win_condition.l1.location = pchar.location;
	PChar.quest.Undead_Start_Graveyard_4.win_condition.l1.locator_group = "reload";
	PChar.quest.Undead_Start_Graveyard_4.win_condition.l1.locator = "reload1";
	PChar.quest.Undead_Start_Graveyard_4.function = "Undead_Start_Graveyard_4";
}
void Undead_Start_Graveyard_4(string qName)
{
	string startCrypt = "Havana_";
	if (pchar.nation == ENGLAND)
	{
		startCrypt = "PortRoyal_";
		setWDMPointXZ("PortRoyal_town");  // коорд на карте
	}
	if (pchar.nation == FRANCE)
	{
		startCrypt = "BasTer_";
		setWDMPointXZ("BasTer_town");  // коорд на карте
	}
	if (pchar.nation == SPAIN)
	{
		startCrypt = "Havana_";
		setWDMPointXZ("Havana_town");  // коорд на карте
	}
	if (pchar.nation == HOLLAND)
	{
		startCrypt = "Villemstad_";
		setWDMPointXZ("Villemstad_town");  // коорд на карте
	}
	DoReloadCharacterToLocation(startCrypt+"cryptbig1", "reload", "reload2");
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- Нежить --     конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////
