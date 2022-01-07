// Прочие квесты

// Warship Квест "Сопровождение флейта 'Орион'" -->

void Andre_Abel_Quest_1Day_Left(string sQuest)	// Провал квеста
{
	ref rChar = CharacterFromID("Andre_Abel");
	rChar.LifeDay = 0;
	LAi_CharacterDisableDialog(rChar);
	ChangeCharacterAddressGroup(rChar, "none", "", "");
	AddQuestRecord("Andre_Abel_Quest", "2");
	AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("","а"));
	CloseQuestHeader("Andre_Abel_Quest");
	DeleteAttribute(pchar,"QuestTemp.AndreAbelQuest");
}

void Andre_Abel_Quest_2Days_Left(string sQuest)	// Провал квеста - не решили свои дела за два дня
{
	ref rChar = CharacterFromID("Andre_Abel");
	rChar.LifeDay = 0;
	LAi_CharacterDisableDialog(rChar);
//	ChangeCharacterAddressGroup(rChar, "none", "", "");
	AddQuestRecord("Andre_Abel_Quest", "2");
	CloseQuestHeader("Andre_Abel_Quest");
	DeleteAttribute(pchar,"QuestTemp.AndreAbelQuest");
}

void Andre_Abel_Quest_Delete_Andre_From_Tavern(string sQuest)	// Убираем Абеля из таверны
{
	ref rChar = CharacterFromID("Andre_Abel");
	ChangeCharacterAddressGroup(rChar, "none", "", "");
	// Присоединяем Андрэ Абеля к игроку в качестве компаньона
	SetCompanionIndex(Pchar, -1, GetCharacterIndex(rChar.id));
	SetCharacterRemovable(rChar, false);	// нельзя сменить
	LAi_SetImmortal(rChar, false);	// можно убить
//	rChar.Dialog.CurrentNode = "Andre_Abel_To_Sea_1";
}

void Andre_Abel_Quest_15_Days_Is_Left(string sQuest)	// Не успели в Порт-о-Принс за 15 дней
{
	ref rChar = CharacterFromID("Andre_Abel");
	rChar.LifeDay = 0;
	AddQuestRecord("Andre_Abel_Quest", "4");
	AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("","а"));
	CloseQuestHeader("Andre_Abel_Quest");
	DeleteAttribute(pchar,"QuestTemp.AndreAbelQuest");
	RemoveCharacterCompanion(PChar, rChar);
	QuestSetCurrentNode("Andre_Abel", "Andre_Abel_15Days_Left_1");
	PChar.Quest.Andre_Abel_Quest_Andre_Is_Dead.over = "yes";
	PChar.Quest.Andre_Abel_Quest_Delete_Andre_From_Tavern.over = "yes";
	PChar.Quest.Andre_Abel_Quest_Battle_With_Pirates_Squadron.over = "yes";
	PChar.Quest.Andre_Abel_Quest_Speak_In_PortPax.over = "yes";
	PChar.Quest.Andre_Abel_Quest_Pirates_Is_Dead.over = "yes";
	PChar.Quest.Andre_Abel_Quest_EnterMap.over = "yes";
}

void Andre_Abel_Quest_Andre_Is_Dead(string sQuest)	// Андрэ Абеля потопили
{
	AddQuestRecord("Andre_Abel_Quest", "5");
	AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("","ла"));
	CloseQuestHeader("Andre_Abel_Quest");
	DeleteAttribute(pchar,"QuestTemp.AndreAbelQuest");
	PChar.Quest.Andre_Abel_Quest_15_Days_Is_Left.over = "yes";
	PChar.Quest.Andre_Abel_Quest_Speak_In_PortPax.over = "yes";
	PChar.Quest.Andre_Abel_Quest_Battle_With_Pirates_Squadron.over = "yes";
}

void Andre_Abel_Quest_Battle_With_Pirates_Squadron(string sQuest)	// Выполнилось прерывание на Hispaniola2. Боевка с пиратами
{
	Log_TestInfo("Сгенерилась пиратская эскадра.");
	ref rChar;
	string sName, sLastName, sModel, sShipName;
	PChar.Quest.Andre_Abel_Quest_Andre_Is_Dead.over = "yes";
	Group_FindOrCreateGroup("Andre_Abel_Quest_Pirates_Ships");
	for(int i=1; i<=3; i++)
	{
		switch(i)
		{
			case 1:
				sName = "Кристиан";
				sLastName = "Копнер";
				sModel = "pirate_5";
				sShipName = "Аврора";
				break;

			case 2:
				sName = "Роберт";
				sLastName = "Недервин";
				sModel = "pirate_9";
				sShipName = "Антилопа";
				break;

			case 3:
				sName = "Томас";
				sLastName = "Чамберс";
				sModel = "pirate_10";
				sShipName = "Сьюзан";
				break;
		}

		rChar = GetCharacter(NPC_GenerateCharacter("Andre_Abel_Quest_Pirate_" + i, sModel, "man", "man", 15, PIRATE, -1, true));
		FantomMakeCoolFighter(rChar, 35, 40, 35, "blade24", "pistol3", 10);
		FantomMakeCoolSailor(rChar, RandShipFromShipClass(PChar), sShipName, CANNON_TYPE_CANNON_LBS24, 75, 70, 65);
		rChar.name = sName;
		rChar.Lastname = sLastName;
		//rChar.Abordage.Enable = false;
		if (pchar.rank < 10) DeleteAttribute(rChar, "SaveItemsForDead");
		Group_AddCharacter("Andre_Abel_Quest_Pirates_Ships", "Andre_Abel_Quest_Pirate_" + i);
	}

	Group_SetType("Andre_Abel_Quest_Pirates_Ships", "war");
	Group_SetGroupCommander("Andre_Abel_Quest_Pirates_Ships", "Andre_Abel_Quest_Pirate_1");
	Group_SetTaskAttack("Andre_Abel_Quest_Pirates_Ships", PLAYER_GROUP);
	Group_LockTask("Andre_Abel_Quest_Pirates_Ships");
	Group_SetAddress("Andre_Abel_Quest_Pirates_Ships", "Hispaniola2", "", "");
	Group_SetPursuitGroup("Andre_Abel_Quest_Pirates_Ships", PLAYER_GROUP);
//	Island_SetReloadEnableGlobal("Hispaniola2", false); // На берег нельзя
	SetFunctionLocationCondition("Andre_Abel_Quest_Speak_In_PortPax", "PortPax_town", false);
	SetFunctionNPCDeathCondition("Andre_Abel_Quest_Andre_Is_Dead_2", "Andre_Abel", false);
	SetFunctionInterruptionToShips("Andre_Abel_Quest_Pirates_Ships", "Andre_Abel_Quest_Pirates_Is_Dead", "Andre_Abel_Quest_EnterMap");
}

void Andre_Abel_Quest_Andre_Is_Dead_2(string sQuest) // Абеля потопили при боевке с пиратами
{
	AddQuestRecord("Andre_Abel_Quest", "6");
	AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("","ла"));
	CloseQuestHeader("Andre_Abel_Quest");
	DeleteAttribute(pchar,"QuestTemp.AndreAbelQuest");
//	Island_SetReloadEnableGlobal("Hispaniola2", true);
	PChar.Quest.Andre_Abel_Quest_Speak_In_PortPax.over = "yes";
	PChar.Quest.Andre_Abel_Quest_Pirates_Is_Dead.over = "yes";
	PChar.Quest.Andre_Abel_Quest_EnterMap.over = "yes";
}

void Andre_Abel_Quest_EnterMap(string sQuest)	// Свалили
{
	ref rChar = CharacterFromID("Andre_Abel");
	AddQuestRecord("Andre_Abel_Quest", "7");
	AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("","а"));
	CloseQuestHeader("Andre_Abel_Quest");
	DeleteAttribute(pchar,"QuestTemp.AndreAbelQuest");
	Group_DeleteGroup("Andre_Abel_Quest_Pirates_Ships");
	RemoveCharacterCompanion(PChar, rChar);
//	Island_SetReloadEnableGlobal("Hispaniola2", true);
	PChar.Quest.Andre_Abel_Quest_Speak_In_PortPax.over = "yes";
	PChar.Quest.Andre_Abel_Quest_Andre_Is_Dead_2.over = "yes";	// Не храним лишние прерывания
}

void Andre_Abel_Quest_Pirates_Is_Dead(string sQuest)	// Победили пиратскую эскадру
{
	AddQuestRecord("Andre_Abel_Quest", "8");
	SetFunctionNPCDeathCondition("Andre_Abel_Quest_Andre_Is_Dead_3", "Andre_Abel", false);
//	SetFunctionLocationCondition("Andre_Abel_Quest_Speak_In_PortPax", "PortPax_town", false);
//	Island_SetReloadEnableGlobal("Hispaniola2", true);
	PChar.Quest.Andre_Abel_Quest_Andre_Is_Dead_2.over = "yes";
}

void Andre_Abel_Quest_Andre_Is_Dead_3(string sQuest)	// Абеля утопил кто-то в порту
{
	AddQuestRecord("Andre_Abel_Quest", "5");
	CloseQuestHeader("Andre_Abel_Quest");
	DeleteAttribute(pchar,"QuestTemp.AndreAbelQuest");
	PChar.Quest.Andre_Abel_Quest_Speak_In_PortPax.over = "yes";
}

void Andre_Abel_Quest_Speak_In_PortPax(string sQuest)	// Разговор с Абелем в порту Порт-о-Принса
{
	ref rChar = CharacterFromID("Andre_Abel");
	RemoveCharacterCompanion(PChar, rChar);
	rChar.Dialog.CurrentNode = "Andre_Abel_In_PortPax";
	LAi_LocationDisableOfficersGen("PortPax_town", true);
	LAi_SetImmortal(rChar, true);
	ChangeCharacterAddressGroup(rChar, "PortPax_town", "quest", "quest1");
	LAi_SetActorType(rChar);
	LAi_ActorDialog(rChar, PChar, "", -1, 5);
	bDisableFastReload = true;
	chrDisableReloadToLocation = true;
	PChar.Quest.Andre_Abel_Quest_Andre_Is_Dead_3.over = "yes";
}

void Andre_Abel_Quest_Dialog_In_PortPax_Tavern()	// В таверне...
{
	ref rChar = CharacterFromID("Andre_Abel");
	QuestSetCurrentNode("Andre_Abel", "Andre_Abel_In_Tavern_1");
	LAi_ActorDialog(rChar, PChar, "", -1, 5);
}

void Andre_Abel_Quest_After_First_Jackman_Dialog()	// Джекмен выставил игрока из своей резиденции
{
	AddQuestRecord("Andre_Abel_Quest", "11");
	QuestSetCurrentNode("Henry Morgan", "Andre_Abel_Quest_Morgan_Dialog_1");
}

void Andre_Abel_Quest_Curasao_10Days_Left(string sQuest)	// Не успели к Стэвезанту за 10 дней
{
	AddQuestRecord("Andre_Abel_Quest", "15");
	AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("","а"));
	TakeItemFromCharacter(PChar, "letter_1");
	ChangeCharacterAddressGroup(CharacterFromID("Andre_Abel"), "none", "", "");
	ref rChar = CharacterFromID("hol_guber");
	rChar.Dialog.CurrentNode = rChar.Dialog.TempNode; // Вернем ноду диалога Ген-Губеру
	PChar.QuestTemp.Andre_Abel_Quest_PortPax_TavernOwner_Speek = true;
	if(!CheckAttribute(PChar, "Quest.Andre_Abel_Quest_In_Curacao_Townhall"))
	{
		rChar = CharacterFromID("Andre_Abel_Quest_Officer_1");
		rChar.LifeDay = 0;
	}
	PChar.Quest.Andre_Abel_Quest_In_Curacao_Townhall.over = "yes";
}

void Andre_Abel_Quest_In_Curacao_Townhall(string sQuest)	// Зашли в резиденцию Виллемстеда
{
	ref rChar = GetCharacter(NPC_GenerateCharacter("Andre_Abel_Quest_Officer_1", "off_hol_2", "man", "man", 20, HOLLAND, -1, true));
	FantomMakeCoolFighter(rChar, 15, 60, 65, "blade24", "pistol3", 100);
	rChar.Dialog.FileName = "Quest\Other_Quests_NPC.c";
	rChar.greeting = "soldier_common";
	LAi_SetGuardianType(rChar);
	LAi_SetImmortal(rChar, true);
	ChangeCharacterAddressGroup(rChar, "Villemstad_Townhall", "goto", "goto6");
	string slai_group = "HOLLAND_citizens";
	LAi_group_MoveCharacter(rChar, slai_group);
}

void Andre_Abel_Quest_In_Prison()	// В тюрьме...
{
	AddQuestRecord("Andre_Abel_Quest", "17");
	ref rChar = GetCharacter(NPC_GenerateCharacter("Martin_Bleker", "OffOrion", "man", "man", 10, PIRATE, -1, true));
	rChar.rank = 18;
	LAi_SetHP(rChar, 200, 200);
	SetSPECIAL(rChar, 8, 6, 9, 4, 5, 8, 7);
	SetSelfSkill(rChar, 60, 60, 60, 60, 40);
	SetShipSkill(rChar, 55, 10, 45, 50, 60, 50, 50, 50, 40);
	SetCharacterPerk(rChar, "Energaiser");
	SetCharacterPerk(rChar, "BasicDefense");
	SetCharacterPerk(rChar, "AdvancedDefense");
	SetCharacterPerk(rChar, "CriticalHit");
	SetCharacterPerk(rChar, "Sliding");
	SetCharacterPerk(rChar, "ByWorker");
	SetCharacterPerk(rChar, "Tireless");
	SetCharacterPerk(rChar, "Gunman");
	SetCharacterPerk(rChar, "IronWill");
	SetCharacterPerk(rChar, "ShipEscape");
	SetCharacterPerk(rChar, "LongRangeGrappling");
	SetCharacterPerk(rChar, "GrapplingProfessional");
	SetCharacterPerk(rChar, "HullDamageUp");
	SetCharacterPerk(rChar, "CrewDamageUp");
	SetCharacterPerk(rChar, "AdvancedBattleState");
	SetCharacterPerk(rChar, "BasicBattleState");
	SetCharacterPerk(rChar, "ShipSpeedUp");
	SetCharacterPerk(rChar, "ShipTurnRateUp");
	SetCharacterPerk(rChar, "Doctor1");
	ChangeCharacterAddressGroup(rChar, "Villemstad_prison", "goto", "goto24");
	rChar.Dialog.Filename = "Quest\Other_Quests_NPC.c";
	rChar.greeting = "pirat_quest";
	rChar.name = "Мартин";
	rChar.Lastname = "Блэкер";
	LAi_SetStayType(rChar);
	RemoveAllCharacterItems(rChar, true);
	rChar.HeroModel = "OffOrion,OffOrion_1,OffOrion_2,OffOrion_3,OffOrion_4,OffOrion_5";
	rChar = CharacterFromID("Andre_Abel_Quest_Officer_1");
	ChangeCharacterAddressGroup(rChar, "none", "", ""); // Убираем солдера из резиденции

	PChar.QuestTemp.JailCanMove = false; // Если было - уберем
	PChar.QuestTemp.Andre_Abel_Quest_In_Prison = true;

	ref location = &Locations[FindLocation("Villemstad_fort")];

	// Перекладываем предметы ГГ в сундук
	aref arItems, boxItems;
	ref rItem;
	string sName;
	makearef(arItems, PChar.items);
	makearef(boxItems, location.box1.items);
	int iItemsNum = GetAttributesNum(arItems);
	for(int i=0; i<iItemsNum; i++)
	{
		sName = GetAttributeName(GetAttributeN(arItems, i));
		rItem = ItemsFromID(sName);
		if (rItem.ItemType != "QUESTITEMS")
		{
			boxItems.(sName) = PChar.items.(sName);
		}
	}
	location.box1.money = PChar.money;
	location.box1 = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear())

	RemoveAllCharacterItems(PChar, true);
}

void Andre_Abel_Quest_Runaway_From_Prison()	// По другую сторону решетки
{
	ref rChar = CharacterFromID("Martin_Bleker");
	AddQuestRecord("Andre_Abel_Quest", "18");

	rChar.location = "Villemstad_fort";	// Нужно для того, чтобы он появился в локации форта
	rChar.location.group = "goto";
	rChar.location.locator = "goto1";
	LAi_SetOfficerType(rChar);

	LAi_Group_MoveCharacter(rChar, LAI_GROUP_PLAYER);
	QuestSetCurrentNode("Henry Morgan", "Andre_Abel_Quest_Morgan_Dialog_11");

	// LAi_group_FightGroups(LAI_GROUP_PLAYER, "HOLLAND_citizens", true);

	rChar = CharacterFromID("VillemstadJailOff");
	ChangeCharacterAddressGroup(rChar, "Villemstad_prison", "reload", "reload1");

	LAi_SetFightMode(PChar, true);
	Flag_Change(PIRATE);

	PChar.Quest.Andre_Abel_Quest_In_Sea_After_Prison.win_condition.l1 = "EnterToSea";
	PChar.Quest.Andre_Abel_Quest_In_Sea_After_Prison.function = "Andre_Abel_Quest_In_Sea_After_Prison";
}

void Andre_Abel_Quest_Martin_Bleker_Is_Dead(string sQuest)	// Мартина убили
{
	Log_TestInfo("Мартина убили");
	PChar.Quest.Andre_Abel_Quest_Liberty.over = "yes";
}

void Andre_Abel_Quest_Liberty(string sQuest)	// Локация выхода из Виллемстада
{
	ref rChar = CharacterFromID("Martin_Bleker");
	ChangeCharacterAddressGroup(rChar, "Villemstad_ExitTown", "goto", "goto8");
	chrDisableReloadToLocation = true;
	LAi_SetActorType(rChar);
	DeleteAttribute(PChar, "QuestTemp.Andre_Abel_Quest_In_Prison");
	QuestSetCurrentNode("Martin_Bleker", "Andre_Abel_Quest_In_Liberty_1");
	LAi_ActorDialog(rChar, PChar, "", -1, 5);
	PChar.Quest.Andre_Abel_Quest_Martin_Bleker_Is_Dead.over = "yes";
	LAi_LocationDisableOfficersGen("Villemstad_prison",false);
	LAi_LocationDisableOfficersGen("Villemstad_fort",false);
	LAi_LocationDisableOfficersGen("Villemstad_ExitTown",false);
}

void Andre_Abel_Quest_Delete_Martin(string sQuest)	// Попрощались с Мартином
{
	ref rChar = CharacterFromID("Martin_Bleker");
	ChangeCharacterAddressGroup(rChar, "none", "", "");
}

void Andre_Abel_Quest_In_Sea_After_Prison(string sQuest)	// Вышли в море
{
	// LAi_group_FightGroups(LAI_GROUP_PLAYER, "HOLLAND_citizens", false);
	LAi_LocationDisableOfficersGen("Villemstad_prison",false);
	LAi_LocationDisableOfficersGen("Villemstad_fort",false);
	LAi_LocationDisableOfficersGen("Villemstad_ExitTown",false);
	AddQuestRecord("Andre_Abel_Quest", "20");
	AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("ся","ась"));
}

// <-- Квест "Сопровождение флейта 'Орион'"
