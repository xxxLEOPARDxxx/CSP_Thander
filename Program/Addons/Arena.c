
//-------------------------------------------------------------------------------
// Арена и всё такое...
//-------------------------------------------------------------------------------
void GenerateArena()
{
	PChar.Arena.Mode = "none";

	GenerateArenaDuel();
	GenerateArenaEtaps();
	GenerateArenaTournament();
	GenerateArenaOdds();

	int iMoneyView = sti(PChar.rank) * 100 + rand(100);
	if(iMoneyView > 10000) { iMoneyView = 10000 + rand(100); }

	PChar.Arena.ViewCost = iMoneyView;

	PChar.Arena.Mode.NotOdd = false;

	PChar.Arena = "Generate";

	if(!CheckAttribute(PChar, "Statistic.Arena.Count")) 		{ PChar.Statistic.Arena.Count = 0; }
	if(!CheckAttribute(PChar, "Statistic.Arena.LooserCount")) 	{ PChar.Statistic.Arena.LooserCount = 0; }
	if(!CheckAttribute(PChar, "Statistic.Arena.WinnerCount")) 	{ PChar.Statistic.Arena.WinnerCount = 0; }

	if(CheckAttribute(PChar, "quest.ClearArenaTime.over"))
	{
		DeleteAttribute(PChar, "quest.ClearArenaTime.over");
	}

	int iTime = rand(5)+20;
	SetTimerFunction("ClearArenaTime", 0, 0, iTime);
}

//-------------------------------------------------------------------------------
// Дуэли
//-------------------------------------------------------------------------------
void GenerateArenaDuel()
{
	int iRank = GetRank(PChar, MOD_SKILL_ENEMY_RATE) + sti(PChar.rank);

	int iCharacter = 0;

	if(GetCharacterIndex("Arena Duel Characer") == -1)
	{
		iCharacter = NPC_GenerateCharacterIndep("Arena Duel Characer", "officer_"+(rand(63)+1), "man", "man", iRank, PIRATE, -1, true);
	}
	else
	{
		iCharacter = CharacterFromID("Arena Duel Characer");
	}

	Characters[iCharacter].id = "Arena Duel Characer";

	string sSaber = GetSaberForArena("FencingLight");
	PChar.Arena.Duel.Saber.Light = sSaber;

	sSaber = GetSaberForArena("Fencing");
	PChar.Arena.Duel.Saber.Saber = sSaber;

	sSaber = GetSaberForArena("FencingHeavy");
	PChar.Arena.Duel.Saber.Heavy = sSaber;

	string sSkill = GetSkillFromSaber(sSaber);

	int iLeaderShip = sti(PChar.skill.LeaderShip);
	int iFencingLight = sti(PChar.skill.FencingLight) + 30;
	int iFencing = sti(PChar.skill.Fencing) + 30;
	int iFencingHeavy = sti(PChar.skill.FencingHeavy) + 30;

	if(iFencingLight < 30) { iFencingLight = 30; }
	if(iFencingLight > 100) { iFencingLight = 100; }

	if(iFencing < 30) { iFencing = 30; }
	if(iFencing > 100) { iFencing = 100; }

	if(iFencingHeavy < 30) { iFencingHeavy = 30; }
	if(iFencingHeavy > 100) { iFencingHeavy = 100; }

	if(rand(3) > 1)
	{
		iLeaderShip += rand(10)+10;
	}
	else
	{
		iLeaderShip -= rand(5)+10;
	}

	if(iLeaderShip > 100)
	{
		iLeaderShip = 100;
	}

	if(iLeaderShip < 30)
	{
		iLeaderShip = 30;
	}

	InitCharacter(&Characters[iCharacter], iCharacter);
	SetRandSPECIAL(&Characters[iCharacter]);

	Characters[iCharacter].id = "Arena Duel Characer";
	Characters[iCharacter].rank = iRank;
	Characters[iCharacter].skill.FencingLight = iFencingLight;
	Characters[iCharacter].skill.Fencing = iFencing;
	Characters[iCharacter].skill.FencingHeavy = iFencingHeavy;
	Characters[iCharacter].skill.LeaderShip = iLeaderShip;
	Characters[iCharacter].model = "officer_" + (rand(63)+1);
	if (MOD_SKILL_ENEMY_RATE == 10 && bHardAnimations) Characters[iCharacter].model.animation = "spy"; // LEO: Превозмогаторам страдать 15.12.2021
	else Characters[iCharacter].model.animation = "man_fast";
	Characters[iCharacter].greeting = "Gr_ArenaMember";

	SetRandomNameToCharacter(&Characters[iCharacter]);
	FaceMaker(&Characters[iCharacter]);

	float fHp = LAi_GetCharacterMaxHP(PChar);
	float fEnergy = LAi_GetCharacterMaxEnergy(PChar);

	int iSkill = GetArenaOddsGreatestFencingSkill(&Characters[iCharacter]) * 10;

	int rand_1 = rand(9)+1;
	int rand_2 = rand(9)+1;
	rand_1 += rand_2;

	float HP = fHp + 250 + (rand(20) * rand_1);
	if(HP < 200) { HP = 200; }

	fEnergy += 10 + rand(5);

	Characters[iCharacter].chr_ai.energy = stf(fEnergy);
	Characters[iCharacter].chr_ai.energyMax = stf(fEnergy);
	SetEnergyToCharacter(&Characters[iCharacter]);
	LAi_SetHP(&Characters[iCharacter], stf(HP), stf(HP));

	int iOdd = GetOddForDuelCharacter(&Characters[iCharacter], sti(Characters[iCharacter].skill.(sSkill)));
	Characters[iCharacter].Odd = iOdd;

    SetSpeciality(&Characters[iCharacter], PerksChars()); // LEO: Характеры 01.12.2021
	SetCharacterPerk(&Characters[iCharacter], "Energaiser");
	if (MOD_SKILL_ENEMY_RATE == 10)
	{
		TakeNItems(&Characters[iCharacter], "BackPack5", 1);
		EquipCharacterbyItem(&Characters[iCharacter], "BackPack5");
		TakeNItems(&Characters[iCharacter], "potion2", 50);
		TakeNItems(&Characters[iCharacter], "Food"+(2+rand(3)), 30);
		TakeNItems(&Characters[iCharacter], "Food"+(2+rand(3)), 30);
	}
	else
	{
		TakeNItems(&Characters[iCharacter], "potion" + (rand(3)+1), (rand(10)+10));
		TakeNItems(&Characters[iCharacter], "potion" + (rand(3)+1), (rand(10)+10));
		TakeNItems(&Characters[iCharacter], "potion" + (rand(3)+1), (rand(10)+10));
		TakeNItems(&Characters[iCharacter], "Food"	 + (1+rand(2)), 20);
	}
	LAi_NPC_EquipPerk(&Characters[iCharacter], "fantom"); // LEO: Перки от уровня 01.12.2021

	if (IsCharacterPerkOn(&Characters[iCharacter], "Ciras"))
		{
			string cirnum;
			switch (rand(4))
			{
				case 0: cirnum = "cirass1"; break;
				case 1: cirnum = "cirass2"; break;
				case 2: cirnum = "cirass3"; break;
				case 3: cirnum = "cirass4"; break;
				case 4: cirnum = "cirass5"; break;
			}
			if (CheckAttribute(&Characters[iCharacter], "HeroModel")) // все, у кого есть что одеть
			{
				switch (cirnum)
				{
					case "cirass1": Characters[iCharacter].model = GetSubStringByNum(Characters[iCharacter].HeroModel, 1); break;
					case "cirass2": Characters[iCharacter].model = GetSubStringByNum(Characters[iCharacter].HeroModel, 2); break;
					case "cirass3": Characters[iCharacter].model = GetSubStringByNum(Characters[iCharacter].HeroModel, 3); break;
					case "cirass4": Characters[iCharacter].model = GetSubStringByNum(Characters[iCharacter].HeroModel, 4); break;
					case "cirass5": Characters[iCharacter].model = GetSubStringByNum(Characters[iCharacter].HeroModel, 5); break;
				}
			}
			Characters[iCharacter].cirassId = Items_FindItemIdx(cirnum);
			Log_TestInfo("Персонаж "+Characters[iCharacter].name+" получил кирасу "+cirnum);
		}

	int iMinOdd = sti(Characters[iCharacter].Odd) / 2;
	int iMaxOdd = sti(Characters[iCharacter].Odd) * 2;
	if(iMinOdd < 500) { iMinOdd = 500; }
	// if(iMaxOdd > 25000) { iMaxOdd = 25000; } // LEO: Без ограничений 01.12.2021

	PChar.Arena.Duel = "Generate";
	PChar.Arena.Duel.Character = iCharacter;
	PChar.Arena.Duel.Saber = sSaber;
	PChar.Arena.Duel.Odd = iMinOdd;
	PChar.Arena.Duel.MinOdd = iMinOdd;
	PChar.Arena.Duel.MaxOdd = iMaxOdd;
	PChar.Arena.Duel.Prize = 0;
	PChar.Arena.Locators = "";

	PChar.Arena.Duel.Count = 0;
	PChar.Arena.Duel.LooserCount = 0;
	PChar.Arena.Duel.WinnerCount = 0;

	PChar.Arena.Duel.BiletCount = 1;
}

void PrepareArenaDuel()
{
	PChar.Arena.Duel.BiletCount = 1;
	ChangeCharacterAddressGroup(CharacterFromID("ArenaBileter"), "FencingTown_ExitTown", "reload", "reload4");
	LAi_SetActorType(CharacterFromID("ArenaBileter"));
	PChar.Arena.Mode = "Duel";
	PChar.quest.PrepareArenaDuelContinue.win_condition.l1 = "locator";
	PChar.quest.PrepareArenaDuelContinue.win_condition.l1.location = "FencingTown_ExitTown";
	PChar.quest.PrepareArenaDuelContinue.win_condition.l1.locator_group = "reload";
	PChar.quest.PrepareArenaDuelContinue.win_condition.l1.locator = "reload4";
	PChar.quest.PrepareArenaDuelContinue.function = "PrepareArenaDuelContinue";
}

void PrepareArenaDuelContinue(string _tmp)
{
	Characters[GetCharacterIndex("ArenaBileter")].Dialog.CurrentNode = "First Time";
	LAi_SetActorType(CharacterFromID("ArenaBileter"));
	LAi_ActorDialogNow(CharacterFromID("ArenaBileter"), Pchar, "", -1);
}

void PrepareArenaDuelEnd()
{
	LAi_SetStayType(CharacterFromID("ArenaBileter"));
	LAi_SetStayType(CharacterFromID("FencingTown_Head"));
	ChangeCharacterAddressGroup(CharacterFromID("FencingTown_Head"), "FencingTown_Arena", "goto", "arena_head");
	Characters[GetCharacterIndex("FencingTown_Head")].dialog.currentnode = "FightInArena_1";
	Locations[FindLocation("FencingTown_ExitTown")].reload.l1.disable = false;

	Locations[FindLocation("FencingTown_Arena")].locators_radius.item.looser_detector = 2.0;

	PChar.quest.StartArenaDuel.win_condition.l1 = "location";
	PChar.quest.StartArenaDuel.win_condition.l1.location = "FencingTown_Arena";
	PChar.quest.StartArenaDuel.function = "StartArenaDuel";
}

void StartArenaDuel(string _tmp)
{
	InterfaceStates.Buttons.Save.enable = false;

	PChar.Arena = "Start";

	CreateFireInArena();
	CreateArenaFightPeople();

	Locations[FindLocation("FencingTown_ExitTown")].reload.l1.disable = true;

	ChangeCharacterAddress(CharacterFromID("ArenaBileter"), "None", "");
	Locations[FindLocation(PChar.location)].reload.l1.disable = true;

	int iEnemy = sti(PChar.Arena.Duel.Character);

	string sLocator = "arena_member_" + (rand(7)+1);
	ChangeCharacterAddressGroup(&Characters[iEnemy], "FencingTown_Arena", "goto", sLocator);
	LAi_SetStayType(&Characters[iEnemy]);

	LAi_SetActorType(PChar);
	LAi_SetActorType(CharacterFromID("FencingTown_Head"));
	LAi_ActorWaitDialog(PChar, CharacterFromID("FencingTown_Head"));
	LAi_ActorDialog(CharacterFromID("FencingTown_Head"), PChar, "", 5.0, 1.0);
}

void ArenaDuelTalkWithEnemy()
{
	int iEnemy = sti(PChar.Arena.Duel.Character);
	Characters[iEnemy].Dialog.FileName = "FencingTownHead_dialog.c";
	Characters[iEnemy].Dialog.CurrentNode = "EnemyFightInArena_1";

	LAi_SetActorType(&Characters[iEnemy]);
	LAi_ActorWaitDialog(PChar, &Characters[iEnemy]);
	LAi_ActorDialog(&Characters[iEnemy], PChar, "", 10.0, 1.0);
}

void ArenaDuelStartBattleWithEnemy()
{
	ChangeCharacterAddressGroup(CharacterFromID("FencingTown_Head"), "FencingTown_Arena", "goto", "arena_vip_3");
	LAi_SetActorType(CharacterFromID("FencingTown_Head"));
	LAi_ActorTurnToLocator(CharacterFromID("FencingTown_Head"), "item", "looser_detector");

	LAi_Fade("", "");

	int iEnemy = sti(PChar.Arena.Duel.Character);
	ref chr = &Characters[iEnemy];

	chr.ArenaAction = true;
	PChar.ArenaAction = true;

	LAi_SetPlayerType(PChar);
	LAi_SetWarriorType(chr);

	string sPlayerLocator, sEnemyLocator;
	if(rand(1) == 1)
	{
		sPlayerLocator = "aloc1"; sEnemyLocator = "aloc3";
	}
	else
	{
		sPlayerLocator = "aloc3"; sEnemyLocator = "aloc1";
	}

	ChangeCharacterAddressGroup(PChar, "FencingTown_Arena", "rld", sPlayerLocator);
	ChangeCharacterAddressGroup(chr, "FencingTown_Arena", "rld", sEnemyLocator);

	string sSaber = "blade1";

	if(CheckAttribute(PChar, "Arena.Duel.Saber"))
	{
		sSaber = PChar.Arena.Duel.Saber;
	}

	RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
	RemoveCharacterEquip(PChar, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(chr, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(chr, GUN_ITEM_TYPE);

        GiveItem2Character(PChar, sSaber);
	EquipCharacterByItem(PChar, sSaber);

	// DeleteAttribute(chr, "items");
        GiveItem2Character(chr, sSaber);
	EquipCharacterByItem(chr, sSaber);

	LAi_SetFightMode(PChar, true);
	LAi_SetFightMode(chr, true);

	LAi_group_MoveCharacter(chr, "EnemyFight");
	LAi_group_SetHearRadius("EnemyFight", 100.0);
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);

	PChar.quest.ArenaDuelLooserDetector.win_condition.l1 = "locator";
	PChar.quest.ArenaDuelLooserDetector.win_condition.l1.location = "FencingTown_Arena";
	PChar.quest.ArenaDuelLooserDetector.win_condition.l1.locator_group = "item";
	PChar.quest.ArenaDuelLooserDetector.win_condition.l1.locator = "looser_detector";
	PChar.quest.ArenaDuelLooserDetector.function = "ArenaDuelLooserDetector";
}

void ArenaDuelLooserDetector(string _tmp)
{
	ArenaDuelSetLooser(PChar);
}

void ArenaDuelSetLooser(ref chr)
{
	LAi_SetImmortal(chr, true);

	int iEnemy = sti(PChar.Arena.Duel.Character);
	LAi_SetFightMode(&Characters[iEnemy], false);
	LAi_SetActorType(&Characters[iEnemy]);

	LAi_SetFightMode(PChar, false);
	LAi_SetActorType(PChar);
	if(CheckAttribute(chr, "id") && GetCharacterIndex(chr.id) == nMainCharacterIndex)
	{
		PChar.Arena.Duel.LooserCount = sti(PChar.Arena.Duel.LooserCount) + 1;
	}
	else
	{
		PChar.Arena.Duel.WinnerCount = sti(PChar.Arena.Duel.WinnerCount) + 1;
	}

	LAi_QuestDelay("ArenaDuelCheckNewRound", 3.0);

}

void ArenaDuelCheckNewRound()
{
	PChar.Arena.Duel.Count = sti(PChar.Arena.Duel.Count) + 1;

	if(sti(PChar.Arena.Duel.LooserCount) >= 3)
	{
		ArenaDuelEnd(sti(PChar.Arena.Duel.Count), false);
	}
	else
	{
		if(sti(PChar.Arena.Duel.WinnerCount) >= 3)
		{
			ArenaDuelEnd(sti(PChar.Arena.Duel.Count), true);
		}
		else
		{
			ArenaDuelStartNewRound(sti(PChar.Arena.Duel.Count));
		}
	}
}

void ArenaDuelStartNewRound(int iCount)
{
	LAi_Fade("", "");

	PlayStereoSound("new_round");
	Log_Info((iCount+1) + " раунд!");

	int iEnemy = sti(PChar.Arena.Duel.Character);
	ref chr = &Characters[iEnemy];

	Log_Info("На данный момент счёт в поединке - " + GetFullName(pchar) + " - " + sti(PChar.Arena.Duel.WinnerCount) + ":" + sti(PChar.Arena.Duel.LooserCount) + " - " + chr.name + " " + chr.lastname);

	LAi_SetImmortal(chr, false);
	LAi_SetImmortal(PChar, false);

	float fEnergy = LAi_GetCharacterMaxEnergy(chr);
	Characters[iEnemy].chr_ai.energy = stf(fEnergy);
	Characters[iEnemy].chr_ai.energyMax = stf(fEnergy);

	LAi_SetCurHPMax(&Characters[iEnemy]);
	SetEnergyToCharacter(&Characters[iEnemy]);

	SetEnergyToCharacter(PChar);
	LAi_SetCurHPMax(PChar);

	LAi_SetPlayerType(PChar);
	LAi_SetWarriorType(chr);

	string sPlayerLocator, sEnemyLocator;
	if(rand(1) == 1)
	{
		sPlayerLocator = "aloc1"; sEnemyLocator = "aloc3";
	}
	else
	{
		sPlayerLocator = "aloc3"; sEnemyLocator = "aloc1";
	}

	ChangeCharacterAddressGroup(PChar, "FencingTown_Arena", "rld", sPlayerLocator);
	ChangeCharacterAddressGroup(chr, "FencingTown_Arena", "rld", sEnemyLocator);

	LAi_group_MoveCharacter(chr, "EnemyFight");
	LAi_group_SetHearRadius("EnemyFight", 100.0);
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);

	PChar.quest.ArenaDuelLooserDetector.win_condition.l1 = "locator";
	PChar.quest.ArenaDuelLooserDetector.win_condition.l1.location = "FencingTown_Arena";
	PChar.quest.ArenaDuelLooserDetector.win_condition.l1.locator_group = "item";
	PChar.quest.ArenaDuelLooserDetector.win_condition.l1.locator = "looser_detector";
	PChar.quest.ArenaDuelLooserDetector.function = "ArenaDuelLooserDetector";
}

void ArenaDuelEnd(int iCount, bool bWin)
{
	LAi_Fade("", "");

	PChar.Statistic.Arena.Count = sti(PChar.Statistic.Arena.Count) + 1;
	if(!bWin)
	{
		PChar.Statistic.Arena.LooserCount = sti(PChar.Statistic.Arena.LooserCount) + 1;
		AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", капитан " + GetNameLugger(PChar, "f") + " потерп"+ GetSexPhrase("ел","ела") +" поражение в дуэли, что проходила в качестве соревнований на Арене!", 5, 1);
	}
	else
	{
		PChar.Statistic.Arena.WinnerCount = sti(PChar.Statistic.Arena.WinnerCount) + 1;
		AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", некий капитан " + GetNameLugger(PChar, "f") + " оказал"+ GetSexPhrase("ся","ась") +" сильнее в дуэли, что проходила в качестве соревнований на Арене!", 5, 1);
	}

	PChar.quest.ArenaDuelLooserDetector.over = "yes";
	PChar.Arena.Duel.Win = bWin;

	LAi_SetCurHPMax(PChar);
	ChangeCharacterAddressGroup(CharacterFromID("FencingTown_Head"), "FencingTown_Arena", "goto", "arena_head");


	InterfaceStates.Buttons.Save.enable = true;

	LAi_SetActorType(PChar);
	LAi_SetActorType(CharacterFromID("FencingTown_Head"));
	LAi_ActorWaitDialog(PChar, CharacterFromID("FencingTown_Head"));
	LAi_ActorDialog(CharacterFromID("FencingTown_Head"), PChar, "", 5.0, 1.0);

	ChangeCharacterAddressGroup(PChar, "FencingTown_Arena", "goto", "arena_member_" + (rand(7)+1));
	Characters[GetCharacterIndex("FencingTown_Head")].dialog.currentnode = "FightInArena_2";
	Locations[FindLocation("FencingTown_Arena")].locators_radius.item.looser_detector = 0.5;
}

void ArenaDuelTheEnd()
{
	InterfaceStates.Buttons.Save.enable = true;
	LAi_SetPlayerType(PChar);
	LAi_SetImmortal(PChar, false);

	int iEnemy = sti(PChar.Arena.Duel.Character);
	LAi_SetStayType(&Characters[iEnemy]);

	ChangeCharacterAddress(&Characters[iEnemy], "None", "");

	LAi_SetOwnerType(CharacterFromID("FencingTown_Head"));
	ChangeCharacterAddressGroup(CharacterFromID("FencingTown_Head"), "FencingTown_Townhall", "goto", "goto2");

	string sSaber = "blade1";

	if(CheckAttribute(PChar, "Arena.Duel.Saber"))
	{
		sSaber = PChar.Arena.Duel.Saber;
	}

	RemoveCharacterEquip(&Characters[iEnemy], BLADE_ITEM_TYPE);
	RemoveCharacterEquip(PChar, BLADE_ITEM_TYPE);
	TakeNItems(&Characters[iEnemy], sSaber, -1);
	TakeNItems(PChar, sSaber, -1);

	DoQuestReloadToLocation("FencingTown_ExitTown", "reload", "reload4", "");

	if(CheckAttribute(PChar, "Arena.Duel"))
	{
		DeleteAttribute(PChar, "Arena.Duel");
	}

	if(CheckAttribute(PChar, "ArenaAction"))
	{
		DeleteAttribute(PChar, "ArenaAction");
	}

	ClearArena("");

	ref member;
	if(GetCharacterIndex("Arena Duel Characer") != -1)
	{
		member = &Characters[GetCharacterIndex("Arena Duel Characer")];
		member.LifeDay = 0;
		Log_TestInfo("Удаляем персонажа для дуэли.");
	}
}

//-------------------------------------------------------------------------------
// Этапы
//-------------------------------------------------------------------------------
void GenerateArenaEtaps()
{
	ArenaEtapsGetEtap();

	string sSaber = GetSaberForArena("FencingLight");
	PChar.Arena.Etaps.Saber.Light = sSaber;

	sSaber = GetSaberForArena("Fencing");
	PChar.Arena.Etaps.Saber.Saber = sSaber;

	sSaber = GetSaberForArena("FencingHeavy");
	PChar.Arena.Etaps.Saber.Heavy = sSaber;

	PChar.Arena.Etaps.Prize = 0;
}

void PrepareArenaEtaps()
{
	PChar.Arena.Etaps.BiletCount = 1;
	PChar.Arena.Mode = "Etaps";
	ChangeCharacterAddressGroup(CharacterFromID("ArenaBileter"), "FencingTown_ExitTown", "reload", "reload4");
	LAi_SetActorType(CharacterFromID("ArenaBileter"));
	PChar.quest.PrepareArenaEtapsContinue.win_condition.l1 = "locator";
	PChar.quest.PrepareArenaEtapsContinue.win_condition.l1.location = "FencingTown_ExitTown";
	PChar.quest.PrepareArenaEtapsContinue.win_condition.l1.locator_group = "reload";
	PChar.quest.PrepareArenaEtapsContinue.win_condition.l1.locator = "reload4";
	PChar.quest.PrepareArenaEtapsContinue.function = "PrepareArenaEtapsContinue";
}

void PrepareArenaEtapsContinue(string _tmp)
{
	Characters[GetCharacterIndex("ArenaBileter")].Dialog.CurrentNode = "First Time";
	LAi_SetActorType(CharacterFromID("ArenaBileter"));
	LAi_ActorDialogNow(CharacterFromID("ArenaBileter"), Pchar, "", -1);
}

void PrepareArenaEtapsEnd()
{
	LAi_SetStayType(CharacterFromID("ArenaBileter"));
	LAi_SetStayType(CharacterFromID("FencingTown_Head"));
	ChangeCharacterAddressGroup(CharacterFromID("FencingTown_Head"), "FencingTown_Arena", "goto", "arena_head");
	Characters[GetCharacterIndex("FencingTown_Head")].dialog.currentnode = "FightInArena_3";
	Locations[FindLocation("FencingTown_ExitTown")].reload.l1.disable = false;

	Locations[FindLocation("FencingTown_Arena")].locators_radius.item.looser_detector = 2.0;

	PChar.quest.StartArenaEtaps.win_condition.l1 = "location";
	PChar.quest.StartArenaEtaps.win_condition.l1.location = "FencingTown_Arena";
	PChar.quest.StartArenaEtaps.function = "StartArenaEtaps";
}

void StartArenaEtaps(string _tmp)
{
	InterfaceStates.Buttons.Save.enable = false;
	PChar.Arena = "Start";

	CreateFireInArena();
	CreateArenaFightPeople();

	Locations[FindLocation("FencingTown_ExitTown")].reload.l1.disable = true;

	ChangeCharacterAddress(CharacterFromID("ArenaBileter"), "None", "");
	Locations[FindLocation(PChar.location)].reload.l1.disable = true;

	LAi_SetActorType(PChar);
	LAi_SetActorType(CharacterFromID("FencingTown_Head"));
	LAi_ActorWaitDialog(PChar, CharacterFromID("FencingTown_Head"));
	LAi_ActorDialog(CharacterFromID("FencingTown_Head"), PChar, "", 5.0, 1.0);
}

void StartArenaEtapsBattle()
{
	ChangeCharacterAddressGroup(CharacterFromID("FencingTown_Head"), "FencingTown_Arena", "goto", "arena_vip_3");
	LAi_Fade("", "");

	PChar.ArenaEtapsAction = true;

	LAi_SetPlayerType(PChar);

	string sPlayerLocator;
	if(rand(1) == 1)
	{
		sPlayerLocator = "aloc1";
	}
	else
	{
		sPlayerLocator = "aloc3";
	}

	ChangeCharacterAddressGroup(PChar, "FencingTown_Arena", "rld", sPlayerLocator);
	string sSaber = "blade1";

	if(CheckAttribute(PChar, "Arena.Etaps.Saber"))
	{
		sSaber = PChar.Arena.Etaps.Saber;
	}

	RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
	RemoveCharacterEquip(PChar, BLADE_ITEM_TYPE);

        GiveItem2Character(PChar, sSaber);
	EquipCharacterByItem(PChar, sSaber);

	LAi_SetFightMode(PChar, true);
	PChar.Arena = "Start";

	ArenaEtapsSetRound(1);
}

void ArenaEtapsSetRound(int iEtap)
{
	string sEtap = "Etap_" + iEtap;

	if(PChar.Arena.Etaps.(sEtap) == "NO")
	{
		ArenaEtapsSetPauseToDoNewRound(iEtap);
		return;
	}

	LAi_SetFightMode(PChar, true);
	PChar.Arena.Etaps.Etap = iEtap;

	int iQuantity = 0;
	string sType = "";

	iQuantity = sti(PChar.Arena.Etaps.(sEtap).Quantity);
	sType = PChar.Arena.Etaps.(sEtap).Type;
	string sModel = "";
	string sAnimation = "";

	string sQuest = "";
	string sSex = "";
	switch(sType)
	{
		case "crabBig": sModel = "crabBig"; sAnimation = "crabBig"; sSex = "crab"; break;
		case "Skel": sModel = "Skel"; sAnimation = "man_fast"; sSex = "skeleton"; break; // LEO: Ловкач
		case "SkelOld": sModel = "Skel_"; sAnimation = "man_fast"; sSex = "skeleton"; break; // LEO: Ловкач
		case "monkey": sModel = "monkey"; sAnimation = "monkey"; sSex = "monkey"; break;
		case "crabBigKing": sModel = "crabBigKing"; sAnimation = "crabBigKing"; sSex = "crab"; break;
		case "SkelKing": sModel = "skeletcap"; sAnimation = "spy"; sSex = "skeleton"; break; // LEO: Анимка "spy" хоть где то должна работать
	}

	int iChar = 0;
	ref chr;
	string sCdn = "";

	if(sType == "Skel")
	{
		sModel = "Skel" + (rand(3)+1);
	}

	if(sType == "SkelOld")
	{
		sModel = "Skel_" + (rand(4)+1);
	}

	if(iQuantity == 1)
	{
		iChar = NPC_GeneratePhantomCharacter("", PIRATE, MAN, 0);
		chr = &Characters[iChar];
		chr.id = "arena_etaps_" + iEtap + "_monster_1";
		chr.model = sModel;
		chr.model.animation = sAnimation;
		chr.sex = sSex;
		SetNewModelToChar(chr);
		ArenaEtapsSetMonsterAttributes(chr, iEtap);

		ChangeCharacterAddressGroup(chr, PChar.location, "goto", "wall_enemy_1");

		LAi_group_MoveCharacter(chr, "EnemyFight");
		LAi_group_SetHearRadius("EnemyFight", 100.0);
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);

		sQuest = "ArenaEtapsPrepareWinEtap_" + iEtap;
		PChar.quest.(sQuest).win_condition.l1 = "NPC_Death";
		PChar.quest.(sQuest).win_condition.l1.character = chr.id;
		PChar.quest.(sQuest).function = "ArenaEtapsPrepareWinEtap";
	}
	else
	{
		for(int i=1; i <= iQuantity; i++)
		{
			if(sType == "Skel")
			{
				sModel = "Skel" + (rand(3)+1);
			}

			if(sType == "SkelOld")
			{
				sModel = "Skel_" + (rand(4)+1);
			}

			iChar = NPC_GeneratePhantomCharacter("", PIRATE, MAN, 0);
			chr = &Characters[iChar];
			chr.id = "arena_etaps_" + iEtap + "_monster_" + i;
			chr.model = sModel;
			chr.model.animation = sAnimation;
			chr.sex = sSex;
			SetNewModelToChar(chr);
			ChangeCharacterAddressGroup(chr, PChar.location, "goto", "wall_enemy_" + i);
			ArenaEtapsSetMonsterAttributes(chr, iEtap);

			if(sModel == "monkey")
			{
				LAi_SetMonkeyTypeNoGroup(chr);
			}

			LAi_group_MoveCharacter(chr, "EnemyFight");

			sCdn = "l" + i;

			sQuest = "ArenaEtapsPrepareWinEtap_" + iEtap;
			PChar.quest.(sQuest).win_condition.(sCdn) = "NPC_Death";
			PChar.quest.(sQuest).win_condition.(sCdn).character = chr.id;
			PChar.quest.(sQuest).function = "ArenaEtapsPrepareWinEtap";
		}

		LAi_group_SetHearRadius("EnemyFight", 100.0);
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	}

	PChar.quest.ArenaEtapsLooserDetector.win_condition.l1 = "locator";
	PChar.quest.ArenaEtapsLooserDetector.win_condition.l1.location = "FencingTown_Arena";
	PChar.quest.ArenaEtapsLooserDetector.win_condition.l1.locator_group = "item";
	PChar.quest.ArenaEtapsLooserDetector.win_condition.l1.locator = "looser_detector";
	PChar.quest.ArenaEtapsLooserDetector.function = "ArenaEtapsLooserDetector";
}

void ArenaEtapsLooserDetector(ref chr)
{
	ArenaEtapsSetLooser(PChar);

	int iEtap = 1;
	if(CheckAttribute(PChar, "Arena.Etaps.Etap"))
	{
		iEtap = sti(PChar.Arena.Etaps.Etap);
	}

	ArenaEtapsClearMonster(iEtap);

	string sQuest = "ArenaEtapsPrepareWinEtap_" + iEtap;

	if(CheckAttribute(PChar, "quest." + sQuest))
	{
		DeleteAttribute(PChar, "quest." + sQuest);
	}
}

void ArenaEtapsSetLooser(ref chr)
{
	if(GetCharacterIndex(chr.id) == nMainCharacterIndex)
	{
		LAi_SetImmortal(chr, true);
		LAi_SetFightMode(PChar, false);
		LAi_SetActorType(PChar);
		ArenaEtapsEnd(false);

		int iEtap = 1;
		if(CheckAttribute(PChar, "Arena.Etaps.Etap"))
		{
			iEtap = sti(PChar.Arena.Etaps.Etap);
		}

		string sQuest = "ArenaEtapsPrepareWinEtap_" + iEtap;
		if(CheckAttribute(PChar, "quest." + sQuest))
		{
			DeleteAttribute(PChar, "quest." + sQuest);
		}
	}
}

void ArenaEtapsSetPauseToDoNewRound(int iEtap)
{
	iEtap++;
	ArenaEtapsSetRound(iEtap);
}

void ArenaEtapsPrepareWinEtap(string qName)
{
	LAi_SetFightMode(PChar, false);
	LAi_SetActorType(PChar);

	DoQuestFunctionDelay("ArenaEtapsWinEtap", 3.0);
}

void ArenaEtapsWinEtap(string qName)
{
	LAi_SetPlayerType(PChar);

	LAi_Fade("", "");

	int iEtap = 1;
	if(CheckAttribute(PChar, "Arena.Etaps.Etap"))
	{
		iEtap = sti(PChar.Arena.Etaps.Etap);
	}

	ArenaEtapsClearMonster(iEtap);

	if(iEtap == 5)
	{
		PlayStereoSound("new_round");
		Log_Info("Все этапы пройдены!");
		ArenaEtapsEnd(true);
		return;
	}

	iEtap++;

	PlayStereoSound("new_round");
	Log_Info("Этап " + (iEtap-1) + " завершён!");
	Log_Info("Этап " + iEtap + " начат!");

	ArenaEtapsSetRound(iEtap);
}

void ArenaEtapsEnd(bool bWin)
{
	LAi_Fade("", "");

	PChar.Statistic.Arena.Count = sti(PChar.Statistic.Arena.Count) + 1;
	if(!bWin)
	{
		PChar.Statistic.Arena.LooserCount = sti(PChar.Statistic.Arena.LooserCount) + 1;
		AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", некий капитан " + GetNameLugger(PChar, "f") + "  не справил"+ GetSexPhrase("ся","ась") +" со страшными монстрами на соревнованиях Арены!", 5, 1);
	}
	else
	{
		PChar.Statistic.Arena.WinnerCount = sti(PChar.Statistic.Arena.WinnerCount) + 1;
		AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", капитан " + GetNameLugger(PChar, "f") + " сум"+ GetSexPhrase("ел","ела") +" справиться со страшными монстрами на соревнованиях Арены!", 5, 1);
	}

	LAi_UseAtidoteBottle(PChar);
	LAi_SetCurHPMax(PChar);
	PChar.Arena.Etaps.Win = bWin;
	PChar.quest.ArenaEtapsLooserDetector.over = "yes";

	InterfaceStates.Buttons.Save.enable = true;
	ChangeCharacterAddressGroup(CharacterFromID("FencingTown_Head"), "FencingTown_Arena", "goto", "arena_head");
	LAi_SetActorType(PChar);
	LAi_SetActorType(CharacterFromID("FencingTown_Head"));
	LAi_ActorWaitDialog(PChar, CharacterFromID("FencingTown_Head"));
	LAi_ActorDialog(CharacterFromID("FencingTown_Head"), PChar, "", 5.0, 1.0);

	ChangeCharacterAddressGroup(PChar, "FencingTown_Arena", "goto", "arena_member_" + (rand(7)+1));
	Characters[GetCharacterIndex("FencingTown_Head")].dialog.currentnode = "FightInArena_4";
	Locations[FindLocation("FencingTown_Arena")].locators_radius.item.looser_detector = 0.5;
}

void ArenaEtapsTheEnd()
{
	InterfaceStates.Buttons.Save.enable = true;
	LAi_SetPlayerType(PChar);
	LAi_SetImmortal(PChar, false);
	LAi_SetOwnerType(CharacterFromID("FencingTown_Head"));
	ChangeCharacterAddressGroup(CharacterFromID("FencingTown_Head"), "FencingTown_Townhall", "goto", "goto2");

	string sSaber = "blade1";

	if(CheckAttribute(PChar, "Arena.Etaps.Saber"))
	{
		sSaber = PChar.Arena.Etaps.Saber;
	}

	RemoveCharacterEquip(PChar, BLADE_ITEM_TYPE);
	TakeNItems(PChar, sSaber, -1);

	DoQuestReloadToLocation("FencingTown_ExitTown", "reload", "reload4", "");

	if(CheckAttribute(PChar, "Arena.Etaps"))
	{
		DeleteAttribute(PChar, "Arena.Etaps");
	}

	if(CheckAttribute(PChar, "ArenaEtapsAction"))
	{
		DeleteAttribute(PChar, "ArenaEtapsAction");
	}

	SetEnergyToCharacter(PChar);
	LAi_UseAtidoteBottle(PChar);
	LAi_SetCurHPMax(PChar);

	ClearArena("");
}

void ArenaEtapsClearMonster(int iEtap)
{
	int iQuantity = 0;
	string sMonster = "";
	string sEtap = "";

	sEtap = "Etap_" + iEtap;

	iQuantity = sti(PChar.Arena.Etaps.(sEtap).Quantity);

	if(iQuantity == 1)
	{
		sMonster = "arena_etaps_" + iEtap + "_monster_1";
		ChangeCharacterAddress(CharacterFromID(sMonster), "None", "");
	}
	else
	{
		for(int i=1; i <= iQuantity; i++)
		{
			sMonster = "arena_etaps_" + iEtap + "_monster_" + i;
			ChangeCharacterAddress(CharacterFromID(sMonster), "None", "");
		}
	}
}

void ArenaEtapsSetMonsterAttributes(ref monster, int iEtap)
{
	float HP = LAi_GetCharacterMaxHP(PChar);
	HP += 20 + (iEtap * 10);

	float Energy = LAi_GetCharacterMaxEnergy(PChar);
	monster.chr_ai.energy = stf(Energy);
	monster.chr_ai.energyMax = stf(Energy);

	if(monster.model == "skeletcap" || monster.model == "crabBigKing")
	{
		HP += 500 + rand(500);
	}

	if(HP > 5000)
	{
		HP = 5000;
	}

	LAi_SetHP(monster, HP, HP);
	SetEnergyToCharacter(monster);

	int iFencingLight = sti(PChar.skill.FencingLight) + 20;
	if(iFencingLight < 20) { iFencingLight = 20; }
	if(iFencingLight > 100) { iFencingLight = 100; }

	int iFencing = sti(PChar.skill.Fencing) + 20;
	if(iFencing < 20) { iFencing = 20; }
	if(iFencing > 100) { iFencing = 100; }

	int iFencingHeavy = sti(PChar.skill.FencingHeavy) + 20;
	if(iFencingHeavy < 20) { iFencingHeavy = 20; }
	if(iFencingHeavy > 100) { iFencingHeavy = 100; }

	monster.rank = GetRank(PChar, 5) + MOD_SKILL_ENEMY_RATE;
	monster.skill.FencingLight = iFencingLight;
	monster.skill.Fencing = iFencing;
	monster.skill.FencingHeavy = iFencingHeavy;

	SetEnergyToCharacter(PChar);
	LAi_SetCurHPMax(PChar);

	if (MOD_SKILL_ENEMY_RATE == 10)
	{
		TakeNItems(monster, "BackPack5", 1);
		EquipCharacterbyItem(monster, "BackPack5");
		TakeNItems(monster, "potion2", 50);
		TakeNItems(monster, "Food"+(2+rand(3)), 30);
		TakeNItems(monster, "Food"+(2+rand(3)), 30);
	}
	else
	{
		TakeNItems(monster, "potion" + (rand(3)+1), (rand(10)+10));
		TakeNItems(monster, "potion" + (rand(3)+1), (rand(10)+10));
		TakeNItems(monster, "potion" + (rand(3)+1), (rand(10)+10));
		TakeNItems(monster, "Food"	 + (1+rand(2)), 20);
	}

	RemoveCharacterEquip(monster, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(monster, GUN_ITEM_TYPE);

	string sSkeletSaber = GetSaberForArena("Fencing");
	if(monster.model == "crabBig" || monster.model == "crabBigKing" || monster.model == "monkey")
	{
		GiveItem2Character(monster, "monkrab");
		EquipCharacterByItem(monster, "monkrab");
	}
	else
	{
		if(monster.model == "skeletcap")
		{
			sSkeletSaber = PChar.Arena.Etaps.Saber;
		}

		GiveItem2Character(monster, sSkeletSaber);
		EquipCharacterByItem(monster, sSkeletSaber);
	}
}

//-------------------------------------------------------------------------------
// Турнир!
//-------------------------------------------------------------------------------
void GenerateArenaTournament()
{
	int iChar = 0;
	string sChar = "";
	ref chr;

	int iNumPosition = 0;
	string sModel = "";

	int iMoney = 0;
	int iRank = GetRank(PChar, MOD_SKILL_ENEMY_RATE);

	iRank *= 1000;
	iRank *= rand(4)+1;
	iMoney = iRank * 8;
	if(sti(PChar.rank) < 10 && iMoney > 250000) { iMoney = 250000; }

	for(int i=1; i <= 7; i++)
	{
		int iRank2 = GetRank(PChar, 5) + MOD_SKILL_ENEMY_RATE;
		if (iMoney >= 1000000 && bHardAnimations) iChar = NPC_GenerateCharacterIndep("Arena_Tournament_Character_" + i, "officer_"+(rand(63)+1), "man", "spy", iRank2, PIRATE, -1, true);
		else iChar = NPC_GenerateCharacterIndep("Arena_Tournament_Character_" + i, "officer_"+(rand(63)+1), "man", "man_fast", iRank2, PIRATE, -1, true);

		chr = &Characters[iChar];
		DeleteAttribute(chr, "items");
		chr.items = "";
		// SetFoodToCharacter(chr, 5, 50);
		if (iMoney >= 1000000 || MOD_SKILL_ENEMY_RATE == 10)
		{
			TakeNItems(&Characters[iChar], "BackPack5", 1);
			EquipCharacterbyItem(&Characters[iChar], "BackPack5");
			TakeNItems(&Characters[iChar], "potion2", 50);
			TakeNItems(&Characters[iChar], "Food"   + (2+rand(3)), 30);
			TakeNItems(&Characters[iChar], "Food"   + (2+rand(3)), 30);
		}
		else
		{
			TakeNItems(&Characters[iChar], "potion" + (rand(3)+1), (rand(10)+10));
			TakeNItems(&Characters[iChar], "potion" + (rand(3)+1), (rand(10)+10));
			TakeNItems(&Characters[iChar], "potion" + (rand(3)+1), (rand(10)+10));
			TakeNItems(&Characters[iChar], "Food"   + (1+rand(2)), 20);
		}

		sChar = "Arena_Tournament_Character_" + i;

		iNumPosition = GetNumPositionForCharInTournament();
		chr.greeting = "Gr_ArenaMember";

		if (IsCharacterPerkOn(chr, "Ciras") && rand(4)==0)
		{
			string cirnum;
			switch (rand(4))
			{
				case 0: cirnum = "cirass1"; break;
				case 1: cirnum = "cirass2"; break;
				case 2: cirnum = "cirass3"; break;
				case 3: cirnum = "cirass4"; break;
				case 4: cirnum = "cirass5"; break;
			}
			if (CheckAttribute(chr, "HeroModel")) // все, у кого есть что одеть
			{
				switch (cirnum)
				{
					case "cirass1": chr.model = GetSubStringByNum(chr.HeroModel, 1); break;
					case "cirass2": chr.model = GetSubStringByNum(chr.HeroModel, 2); break;
					case "cirass3": chr.model = GetSubStringByNum(chr.HeroModel, 3); break;
					case "cirass4": chr.model = GetSubStringByNum(chr.HeroModel, 4); break;
					case "cirass5": chr.model = GetSubStringByNum(chr.HeroModel, 5); break;
				}
			}
			chr.cirassId = Items_FindItemIdx(cirnum);
			Log_TestInfo("Персонаж "+chr.name+" получил кирасу "+cirnum);
		}

		//SetNewModelToChar(chr);
		SetRandomNameToCharacter(chr);

		PChar.Arena.Tournament.(sChar).Position = iNumPosition;
		ArenaTournamentSetPosition(iNumPosition, sChar, "1_2");
		ArenaTournamentSetPosition(iNumPosition, sChar, "final");
	}

	iNumPosition = GetNumPositionForCharInTournament();
	PChar.Arena.Tournament.Blaze.Position = iNumPosition;

	ArenaTournamentSetPosition(iNumPosition, "Blaze", "1_2");
	ArenaTournamentSetPosition(iNumPosition, "Blaze", "final");

	DeleteAttribute(PChar, "Arena.Tournament.Positions");
	DeleteAttribute(PChar, "Arena.Tournament.Models");

	string sSaber = GetSaberForArenaT("FencingLight",1);
	PChar.Arena.Tournament.Saber.Light1 = sSaber;
	sSaber = GetSaberForArenaT("FencingLight",2);
	PChar.Arena.Tournament.Saber.Light2 = sSaber;
	sSaber = GetSaberForArenaT("FencingLight",3);
	PChar.Arena.Tournament.Saber.Light3 = sSaber;

	sSaber = GetSaberForArenaT("Fencing",1);
	PChar.Arena.Tournament.Saber.Saber1 = sSaber;
	sSaber = GetSaberForArenaT("Fencing",2);
	PChar.Arena.Tournament.Saber.Saber2 = sSaber;
	sSaber = GetSaberForArenaT("Fencing",3);
	PChar.Arena.Tournament.Saber.Saber3 = sSaber;

	sSaber = GetSaberForArenaT("FencingHeavy",1);
	PChar.Arena.Tournament.Saber.Heavy1 = sSaber;
	sSaber = GetSaberForArenaT("FencingHeavy",2);
	PChar.Arena.Tournament.Saber.Heavy2 = sSaber;
	sSaber = GetSaberForArenaT("FencingHeavy",3);
	PChar.Arena.Tournament.Saber.Heavy3 = sSaber;

	PChar.Arena.Tournament.Money = iMoney;

	PChar.Arena.Tournament.Count = 0;

	PChar.Arena.Tournament.Temp.Attack = "";
	PChar.Arena.Tournament.Temp.Enemy = "";
	PChar.Arena.Tournament.Temp.Stage = 1;
	PChar.Arena.Tournament.Temp.StageTemp = 1;
	PChar.Arena.Tournament.Temp.Count = 0;
	PChar.Arena.Tournament.Temp.WinnerCount = 0;
	PChar.Arena.Tournament.Temp.LooserCount = 0;

	PChar.Arena.Tournament.InterfacePause = false;
	PChar.Arena.Tournament.Temp.StagePause = false;
	PChar.Arena.Tournament.Temp.InterfaceStage = "1_4";
	PChar.Arena.Tournament.Temp.Winner = "";
}

void PrepareArenaTournament()
{
	PChar.Arena.Tournament.BiletCount = 1;
	ChangeCharacterAddressGroup(CharacterFromID("ArenaBileter"), "FencingTown_ExitTown", "reload", "reload4");
	LAi_SetActorType(CharacterFromID("ArenaBileter"));
	PChar.Arena.Mode = "Tournament";
	PChar.quest.PrepareArenaTournamentContinue.win_condition.l1 = "locator";
	PChar.quest.PrepareArenaTournamentContinue.win_condition.l1.location = "FencingTown_ExitTown";
	PChar.quest.PrepareArenaTournamentContinue.win_condition.l1.locator_group = "reload";
	PChar.quest.PrepareArenaTournamentContinue.win_condition.l1.locator = "reload4";
	PChar.quest.PrepareArenaTournamentContinue.function = "PrepareArenaTournamentContinue";
}

void PrepareArenaTournamentContinue(string _tmp)
{
	Characters[GetCharacterIndex("ArenaBileter")].Dialog.CurrentNode = "First Time";
	LAi_SetActorType(CharacterFromID("ArenaBileter"));
	LAi_ActorDialogNow(CharacterFromID("ArenaBileter"), Pchar, "", -1);
}

void PrepareArenaTournamentEnd()
{
	LAi_SetStayType(CharacterFromID("ArenaBileter"));
	LAi_SetStayType(CharacterFromID("FencingTown_Head"));
	ChangeCharacterAddressGroup(CharacterFromID("FencingTown_Head"), "FencingTown_Arena", "goto", "arena_head");
	Characters[GetCharacterIndex("FencingTown_Head")].dialog.currentnode = "FightInArena_5";
	Locations[FindLocation("FencingTown_ExitTown")].reload.l1.disable = false;

	Locations[FindLocation("FencingTown_Arena")].locators_radius.item.looser_detector = 2.0;

	PChar.quest.StartArenaTournament.win_condition.l1 = "location";
	PChar.quest.StartArenaTournament.win_condition.l1.location = "FencingTown_Arena";
	PChar.quest.StartArenaTournament.function = "StartArenaTournament";
}

void StartArenaTournament(string _tmp)
{
	SetTimeScale(2.0);
	InterfaceStates.Buttons.Save.enable = false;
	PChar.Arena = "Start";

	CreateFireInArena();
	CreateArenaFightPeople();

	Locations[FindLocation("FencingTown_ExitTown")].reload.l1.disable = true;

	ChangeCharacterAddress(CharacterFromID("ArenaBileter"), "None", "");
	Locations[FindLocation(PChar.location)].reload.l1.disable = true;

	int iEnemy = -1;
	string sLocator = "arena_member_" + (rand(7)+1);

	for(int e=1; e<=7; e++)
	{
		iEnemy = GetCharacterIndex("Arena_Tournament_Character_" + e);

		if(iEnemy != -1)
		{
			sLocator = "arena_member_" + e;
			ChangeCharacterAddressGroup(&Characters[iEnemy], "FencingTown_Arena", "goto", sLocator);
			LAi_SetStayType(&Characters[iEnemy]);
		}
	}

	LAi_SetActorType(PChar);
	LAi_SetActorType(CharacterFromID("FencingTown_Head"));
	LAi_ActorWaitDialog(PChar, CharacterFromID("FencingTown_Head"));
	LAi_ActorDialog(CharacterFromID("FencingTown_Head"), PChar, "", 5.0, 1.0);
}

void ArenaTournamentTalkWithRandEnemy()
{
	SetTimeScale(2.0);
	int iEnemy = -1;
	int iRand = rand(6)+1;

	for(int e=1; e<=7; e++)
	{
		iEnemy = GetCharacterIndex("Arena_Tournament_Character_" + e);

		if(iEnemy != -1)
		{
			Characters[iEnemy].Dialog.FileName = "FencingTownHead_dialog.c";
			Characters[iEnemy].Dialog.CurrentNode = "FightInArena_6";
			LAi_SetActorType(&Characters[iEnemy]);
			LAi_ActorTurnToLocator(&Characters[iEnemy], "item", "looser_detector");

			if(iRand == e)
			{
				LAi_ActorWaitDialog(PChar, &Characters[iEnemy]);
				LAi_ActorDialog(&Characters[iEnemy], PChar, "", 5.0, 1.0);
			}
		}
	}
}

void ArenaTournamentGo()
{
	ChangeCharacterAddressGroup(CharacterFromID("FencingTown_Head"), "FencingTown_Arena", "goto", "arena_vip_3");
	LAi_SetActorType(CharacterFromID("FencingTown_Head"));
	LAi_ActorTurnToLocator(CharacterFromID("FencingTown_Head"), "item", "looser_detector");

	PChar.Arena.Tournament.InterfacePause = true;
	PChar.Arena.Tournament.Temp.InterfaceStage = "1_4";
	LAi_SetActorType(PChar);
	DoQuestFunctionDelay("ArenaResultTournament", 3.0);

	ArenaTournamentSetCharacterFromArena(PChar);
	PChar.Arena = "Start";

	//ArenaTournamentGoStart(1, 1);
	//ArenaTournamentStartNewBattle();
}

void ArenaTournamentGoStart(int iStage, int iStageTemp)
{
	ref attack, enemy;

	if(iStage == 1)
	{
		if(iStageTemp != 1)
		{
			ArenaTournamentPrepareInterface();
		}
	}
	else
	{
		ArenaTournamentPrepareInterface();
	}

	LAi_Fade("", "");

	int iChar = 0;

	int iEnemyPos = 0;
	int iAttackPos = 0;

	string sStage = "1_4";
	switch(iStage)
	{
		case 1: sStage = "1_4";
			if(iStageTemp == 1)
			{
				iAttackPos = 1; iEnemyPos = 2;
			}
			else
			{
				if(iStageTemp == 2)
				{
					iAttackPos = 3; iEnemyPos = 4;
				}
				else
				{
					if(iStageTemp == 3)
					{
						iAttackPos = 5; iEnemyPos = 6;
					}
					else
					{
						iAttackPos = 7; iEnemyPos = 8;
					}
				}
			}

		break;
		case 2: sStage = "1_2"; if(iStageTemp == 1) { iAttackPos = 1; iEnemyPos = 2; }else{ iAttackPos = 3; iEnemyPos = 4; } break;
		case 3: sStage = "final"; iAttackPos = 1; iEnemyPos = 2; break;
	}

	string sChar = ArenaTournamentGetCharacterIDFromPos(iAttackPos, sStage);
	iChar = GetCharacterIndex(sChar);
	attack = &Characters[iChar];
	attack.ArenaTournament = true;
	attack.ArenaTournament.Attack = true;

	sChar = ArenaTournamentGetCharacterIDFromPos(iEnemyPos, sStage);
	iChar = GetCharacterIndex(sChar);
	enemy = &Characters[iChar];
	enemy.ArenaTournament = true;
	enemy.ArenaTournament.Enemy = true;

	PChar.Arena.Tournament.Temp.Attack = attack.id;
	PChar.Arena.Tournament.Temp.Enemy = enemy.id;

	PChar.Arena.Tournament.Temp.Count = 0;
	PChar.Arena.Tournament.Temp.WinnerCount = 0;
	PChar.Arena.Tournament.Temp.LooserCount = 0;

	ArenaTournamentSetDetailsForChar(attack, iStage);
	ArenaTournamentSetDetailsForChar(enemy, iStage);

	Log_Info(attack.name + " " + attack.lastname + " VS " + enemy.name + " " + enemy.lastname);
}

void ArenaTournamentStartNewBattle()
{
	LAi_Fade("", "");

	PlayStereoSound("new_round");

	ref attack, enemy;
	string sAttack = PChar.Arena.Tournament.Temp.Attack;
	string sEnemy = PChar.Arena.Tournament.Temp.Enemy;

	attack = &Characters[GetCharacterIndex(sAttack)];
	enemy = &Characters[GetCharacterIndex(sEnemy)];

	LAi_SetImmortal(attack, false);
	LAi_SetImmortal(enemy, false);

	float fEnergy = LAi_GetCharacterMaxEnergy(attack);
	attack.chr_ai.energy = stf(fEnergy);
	attack.chr_ai.energyMax = stf(fEnergy);
	LAi_SetCurHPMax(attack);
	SetEnergyToCharacter(attack);

	fEnergy = LAi_GetCharacterMaxEnergy(enemy);
	enemy.chr_ai.energy = stf(fEnergy);
	enemy.chr_ai.energyMax = stf(fEnergy);
	LAi_SetCurHPMax(enemy);
	SetEnergyToCharacter(enemy);

	LAi_SetWarriorType(attack);
	LAi_SetWarriorType(enemy);

	if(attack.id == PChar.id)
	{
		LAi_SetPlayerType(attack);
	}
	if(enemy.id == PChar.id)
	{
		LAi_SetPlayerType(enemy);
	}

	float x = -2.26369;
	float y = 18.762;
	float z = -11.5217;

	locCameraToPos(x, y, z, false);

	if(attack.id == PChar.id || enemy.id == PChar.id)
	{
		locCameraFollow();
	}

	string sPlayerLocator, sEnemyLocator;
	if(rand(1) == 1)
	{
		sPlayerLocator = "aloc1"; sEnemyLocator = "aloc3";
	}
	else
	{
		sPlayerLocator = "aloc3"; sEnemyLocator = "aloc1";
	}

	ChangeCharacterAddressGroup(attack, "FencingTown_Arena", "rld", sPlayerLocator);
	ChangeCharacterAddressGroup(enemy, "FencingTown_Arena", "rld", sEnemyLocator);

	LAi_group_MoveCharacter(attack, "ARENA_TOURNAMENT_CHARACTER_1");
	LAi_group_MoveCharacter(enemy, "ARENA_TOURNAMENT_CHARACTER_2");

	LAi_group_SetHearRadius("ARENA_TOURNAMENT_CHARACTER_2", 100.0);
	LAi_group_SetHearRadius("ARENA_TOURNAMENT_CHARACTER_1", 100.0);
	LAi_group_SetRelation("ARENA_TOURNAMENT_CHARACTER_1", "ARENA_TOURNAMENT_CHARACTER_2", LAI_GROUP_ENEMY);
	LAi_group_FightGroups("ARENA_TOURNAMENT_CHARACTER_1", "ARENA_TOURNAMENT_CHARACTER_2", true);

	if(attack.id == PChar.id)
	{
		LAi_group_MoveCharacter(attack, LAI_GROUP_PLAYER);
		LAi_group_SetRelation(LAI_GROUP_PLAYER, "ARENA_TOURNAMENT_CHARACTER_2", LAI_GROUP_ENEMY);
		LAi_group_FightGroups(LAI_GROUP_PLAYER, "ARENA_TOURNAMENT_CHARACTER_2", true);
	}
	if(enemy.id == PChar.id)
	{
		LAi_group_MoveCharacter(enemy, LAI_GROUP_PLAYER);
		LAi_group_SetRelation(LAI_GROUP_PLAYER, "ARENA_TOURNAMENT_CHARACTER_1", LAI_GROUP_ENEMY);
		LAi_group_FightGroups(LAI_GROUP_PLAYER, "ARENA_TOURNAMENT_CHARACTER_1", true);
	}
	if(attack.id != PChar.id && enemy.id != PChar.id) SetTimeScale(6.0);
	else SetTimeScale(1.0);
	if (CheckAttribute(PChar,"ArenaOdds")) SetTimeScale(1.0);
	if(attack.id == PChar.id || enemy.id == PChar.id)
	{
		string sQuest = "AT_LooserDetector_" + sti(PChar.Arena.Tournament.Temp.Stage) + "_" + sti(PChar.Arena.Tournament.Temp.StageTemp);
		PChar.quest.(sQuest).win_condition.l1 = "locator";
		PChar.quest.(sQuest).win_condition.l1.location = "FencingTown_Arena";
		PChar.quest.(sQuest).win_condition.l1.locator_group = "item";
		PChar.quest.(sQuest).win_condition.l1.locator = "looser_detector";
		PChar.quest.(sQuest).function = "ArenaTournamentLooserDetector";
		LAi_SetFightMode(PChar, true);
	}
}

void ArenaTournamentLooserDetector(string qName)
{
	ArenaTournamentSetLooser(PChar);
}

void ArenaTournamentSetLooser(ref chr)
{
	bool bWin = true;

	LAi_SetCurHPMax(chr);
	LAi_SetImmortal(chr, true);

	string sEnemy = PChar.Arena.Tournament.Temp.Enemy;
	string sAttack = PChar.Arena.Tournament.Temp.Attack;

	int iEnemy = GetCharacterIndex(sEnemy);
	int iAttack = GetCharacterIndex(sAttack);

	LAi_SetFightMode(&Characters[iEnemy], false);
	LAi_SetActorType(&Characters[iEnemy]);

	LAi_SetFightMode(&Characters[iAttack], false);
	LAi_SetActorType(&Characters[iAttack]);

	if(CheckAttribute(chr, "ArenaTournament.Attack"))
	{
		PChar.Arena.Tournament.Temp.LooserCount = sti(PChar.Arena.Tournament.Temp.LooserCount) + 1;
		Log_SetStringToLog("В этом раунде победитель " + Characters[iEnemy].name + " " + Characters[iEnemy].lastname);
	}
	else
	{
		PChar.Arena.Tournament.Temp.WinnerCount = sti(PChar.Arena.Tournament.Temp.WinnerCount) + 1;
		Log_SetStringToLog("В этом раунде победитель " + Characters[iAttack].name + " " + Characters[iAttack].lastname);
	}

	Log_SetStringToLog("На этот момент счёт в поединке - " + Characters[iAttack].name + " " + Characters[iAttack].lastname + " - " + PChar.Arena.Tournament.Temp.WinnerCount + ":" + sti(PChar.Arena.Tournament.Temp.LooserCount) + " - " + Characters[iEnemy].name + " " + Characters[iEnemy].lastname);

	DoQuestFunctionDelay("ArenaTournamentCheckNewRound", 3.0);
}

void ArenaTournamentCheckNewRound(string qName)
{
	PChar.Arena.Tournament.Temp.Count = sti(PChar.Arena.Tournament.Temp.Count) + 1;

	PlayStereoSound("new_round");

	string sEnemy = PChar.Arena.Tournament.Temp.Enemy;
	string sAttack = PChar.Arena.Tournament.Temp.Attack;

	int iEnemy = GetCharacterIndex(sEnemy);
	int iAttack = GetCharacterIndex(sAttack);

	string sStage = "";

	switch(sti(PChar.Arena.Tournament.Temp.Stage))
	{
		case 1: sStage = "1_4"; break;
		case 2: sStage = "1_2"; break;
		case 3: sStage = "final"; break;
	}

	if(sti(PChar.Arena.Tournament.Temp.LooserCount) >= 3)
	{
		Characters[iAttack].ArenaTournament.looser.(sStage) = sStage;
		ArenaTournamentDuelEnd(false);
	}
	else
	{
		if(sti(PChar.Arena.Tournament.Temp.WinnerCount) >= 3)
		{
			Characters[iEnemy].ArenaTournament.looser.(sStage) = sStage;
			ArenaTournamentDuelEnd(true);
		}
		else
		{
			ArenaTournamentStartNewBattle();
		}
	}
}

void ArenaTournamentDuelEnd(bool bWin)
{
	LAi_Fade("", "");

	ref looser;
	string sEnemy = PChar.Arena.Tournament.Temp.Enemy;
	string sAttack = PChar.Arena.Tournament.Temp.Attack;

	int iEnemy = GetCharacterIndex(sEnemy);
	int iAttack = GetCharacterIndex(sAttack);

	ref enemy, attack;
	if(CheckAttribute(&Characters[iAttack], "ArenaTournament.looser"))
	{
		looser = &Characters[iAttack];
		PChar.Arena.Tournament.Temp.Winner = Characters[iEnemy].id;
	}

	if(CheckAttribute(&Characters[iEnemy], "ArenaTournament.looser"))
	{
		looser = &Characters[iEnemy];
		PChar.Arena.Tournament.Temp.Winner = Characters[iAttack].id;
	}

	/*
	if(attack.id == PChar.id || enemy.id == PChar.id)
	{
		PChar.Statistic.Arena.Count = sti(PChar.Statistic.Arena.Count) + 1;
		if(!bWin)
		{
			PChar.Statistic.Arena.LooserCount = sti(PChar.Statistic.Arena.LooserCount) + 1;
		}
		else
		{
			PChar.Statistic.Arena.WinnerCount = sti(PChar.Statistic.Arena.WinnerCount) + 1;
		}
	}
	*/

	int iStage = 0;
	int iStageTemp = 0;

	string sQuest = "AT_LooserDetector_" + sti(PChar.Arena.Tournament.Temp.Stage) + "_" + sti(PChar.Arena.Tournament.Temp.StageTemp);
	PChar.quest.(sQuest).over = "yes";

	if(sti(PChar.Arena.Tournament.Temp.Stage) == 1)
	{
		if(sti(PChar.Arena.Tournament.Temp.StageTemp) <= 4)
		{
			PChar.Arena.Tournament.Temp.StageTemp = sti(PChar.Arena.Tournament.Temp.StageTemp) + 1;
		}

		if(sti(PChar.Arena.Tournament.Temp.StageTemp) > 4)
		{
			PChar.Arena.Tournament.Temp.Stage = 2;
			PChar.Arena.Tournament.Temp.StageTemp = 1;
			PChar.Arena.Tournament.Temp.StagePause = true;
		}
	}

	if(sti(PChar.Arena.Tournament.Temp.Stage) == 2 && PChar.Arena.Tournament.Temp.StagePause == false)
	{
		if(sti(PChar.Arena.Tournament.Temp.StageTemp) <= 2)
		{
			PChar.Arena.Tournament.Temp.StageTemp = sti(PChar.Arena.Tournament.Temp.StageTemp) + 1;
		}

		if(sti(PChar.Arena.Tournament.Temp.StageTemp) > 2)
		{
			PChar.Arena.Tournament.Temp.Stage = 3;
			PChar.Arena.Tournament.Temp.StageTemp = 1;
			PChar.Arena.Tournament.Temp.StagePause = true;
		}
	}

	if(sti(PChar.Arena.Tournament.Temp.Stage) == 3 && PChar.Arena.Tournament.Temp.StagePause == false)
	{
		ArenaTournamentEnd();
		return;
	}

	iStage = sti(PChar.Arena.Tournament.Temp.Stage);
	iStageTemp = sti(PChar.Arena.Tournament.Temp.StageTemp);

	if(iStage == 2 && iStageTemp == 1)
	{
		PChar.Arena.Tournament.InterfacePause = true;
		PChar.Arena.Tournament.Temp.InterfaceStage = "1_2";
		LAi_SetActorType(PChar);
		DoQuestFunctionDelay("ArenaResultTournament", 3.0);
		return;
	}

	if(iStage == 3 && iStageTemp == 1)
	{
		PChar.Arena.Tournament.InterfacePause = true;
		PChar.Arena.Tournament.Temp.InterfaceStage = "final";
		LAi_SetActorType(PChar);
		DoQuestFunctionDelay("ArenaResultTournament", 3.0);
		return;
	}

	ArenaTournamentGoStart(iStage, iStageTemp);
	ArenaTournamentStartNewBattle();
}

void ArenaResultTournament(string qName)
{
	LaunchArena(true);
	ArenaTournamentPrepareInterface();
}

void ArenaTournamentEnd()
{
	LAi_Fade("", "");

	bool bWinner = false;

	string sWinner = PChar.Arena.Tournament.Temp.Winner;
	if(sWinner == "Blaze")
	{
		bWinner = true;
	}
	else
	{
		bWinner = false;
	}

	PChar.Arena.Tournament.Win = bWinner;

	PChar.Statistic.Arena.Count = sti(PChar.Statistic.Arena.Count) + 1;
	if(!bWinner)
	{
		PChar.Statistic.Arena.LooserCount = sti(PChar.Statistic.Arena.LooserCount) + 1;
		AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", капитан " + GetNameLugger(PChar, "f") + ", участвов"+ GetSexPhrase("ший","шая") +" в последнем турнире на Арене, не смо"+ GetSexPhrase("г","гла") +" его выиграть.", 5, 1);
	}
	else
	{
		PChar.Statistic.Arena.WinnerCount = sti(PChar.Statistic.Arena.WinnerCount) + 1;
		AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", в последнем турнире, проходящем на Арене, сильнее всех оказал"+ GetSexPhrase("ся","ась") +" капитан " + GetNameLugger(PChar, "f") + ".", 5, 1);
	}

	locCameraFollow();

	LAi_SetCurHPMax(PChar);

	InterfaceStates.Buttons.Save.enable = true;
	ChangeCharacterAddressGroup(PChar, "FencingTown_Arena", "reload", "reload1");
	ChangeCharacterAddressGroup(CharacterFromID("FencingTown_Head"), "FencingTown_Arena", "goto", "arena_head");
	LAi_SetActorType(PChar);
	LAi_SetActorType(CharacterFromID("FencingTown_Head"));
	LAi_ActorWaitDialog(PChar, CharacterFromID("FencingTown_Head"));
	LAi_ActorDialog(CharacterFromID("FencingTown_Head"), PChar, "", 5.0, 1.0);

	Characters[GetCharacterIndex("FencingTown_Head")].dialog.currentnode = "FightInArena_7";
	Locations[FindLocation("FencingTown_Arena")].locators_radius.item.looser_detector = 0.5;
}

void ArenaTournamentTheEnd()
{
	InterfaceStates.Buttons.Save.enable = true;
	LAi_SetPlayerType(PChar);
	LAi_SetImmortal(PChar, false);

	string sSaber = "blade1";

	RemoveCharacterEquip(PChar, BLADE_ITEM_TYPE);
	if (CheckAttribute(pchar,"Arena.TournamentWeapon"))
	{
		sSaber = pchar.Arena.TournamentWeapon;
		TakeNItems(PChar, sSaber, -1);
	}


	/*if(CheckAttribute(PChar, "Arena.Tournament.Saber.Light"))
	{
		sSaber = PChar.Arena.Tournament.Saber.Light;
		TakeNItems(PChar, sSaber, -1);
	}
	if(CheckAttribute(PChar, "Arena.Tournament.Saber.Saber"))
	{
		sSaber = PChar.Arena.Tournament.Saber.Saber;
		TakeNItems(PChar, sSaber, -1);
	}
	if(CheckAttribute(PChar, "Arena.Tournament.Saber.Heavy"))
	{
		sSaber = PChar.Arena.Tournament.Saber.Heavy;
		TakeNItems(PChar, sSaber, -1);
	}*/

	string sMember = "";

	ref member;
	for(int i = 1; i <= 7; i++)
	{
		sMember = "Arena_Tournament_Character_" + i;
		member = &Characters[GetCharacterIndex(sMember)];

		RemoveCharacterEquip(member, BLADE_ITEM_TYPE);
		if(CheckAttribute(member, "ArenaAction"))
		{
			DeleteAttribute(member, "ArenaAction");
		}

		if(CheckAttribute(member, "ArenaTournament.looser"))
		{
			DeleteAttribute(member, "ArenaTournament.looser");
		}

		LAi_SetStayType(member);
		ChangeCharacterAddress(member, "None", "");
		member.LifeDay = 0;
		//Log_TestInfo("Удаляем персонажа для турнира: " + sMember);
	}

	LAi_SetOwnerType(CharacterFromID("FencingTown_Head"));
	ChangeCharacterAddressGroup(CharacterFromID("FencingTown_Head"), "FencingTown_Townhall", "goto", "goto2");

	DoQuestReloadToLocation("FencingTown_ExitTown", "reload", "reload4", "");

	if(CheckAttribute(PChar, "ArenaAction"))
	{
		DeleteAttribute(PChar, "ArenaAction");
	}

	if(CheckAttribute(PChar, "ArenaTournament.looser"))
	{
		DeleteAttribute(PChar, "ArenaTournament.looser");
	}

	if(CheckAttribute(PChar, "Arena.Tournament"))
	{
		DeleteAttribute(PChar, "Arena.Tournament");
	}

	ClearArena("");

	LAi_group_MoveCharacter(PChar, LAI_GROUP_PLAYER);
	LAi_group_Delete("ARENA_TOURNAMENT_CHARACTER_1");
	LAi_group_Delete("ARENA_TOURNAMENT_CHARACTER_2");
}

void ArenaTournamentSetDetailsForChar(ref chr, int iStage)
{
	string sSaber = pchar.Arena.TournamentWeapon;

	/*switch(iStage)
	{
		case 1: sSaber = PChar.Arena.Tournament.Saber.Light; break;
		case 2: sSaber = PChar.Arena.Tournament.Saber.Saber; break;
		case 3: sSaber = PChar.Arena.Tournament.Saber.Heavy; break;
	}*/

	RemoveCharacterEquip(chr, GUN_ITEM_TYPE);
	RemoveCharacterEquip(chr, BLADE_ITEM_TYPE);

	if (chr.index == nMainCharacterIndex)
	{
		if (iStage == 2 || iStage == 3) TakeNItems(chr,sSaber,-1);
	}
	GiveItem2Character(chr, sSaber);
	EquipCharacterByItem(chr, sSaber);

	if(chr.id == PChar.id)
	{
		return;
	}

	int iBonus = iStage * 10;

	int iRank = GetRank(PChar, MOD_SKILL_ENEMY_RATE);
	int iFencingLight = sti(PChar.skill.FencingLight);
	int iFencing = sti(PChar.skill.Fencing);
	int iFencingHeavy = sti(PChar.skill.FencingHeavy);

	float HPmx = LAi_GetCharacterMaxHP(PChar);
	float Energy = LAi_GetCharacterMaxEnergy(PChar);

	int rand_1 = rand(9)+1;
	int rand_2 = rand(9)+1;
	rand_1 += rand_2;

	float HP = HPmx + 200 + (rand(20) * rand_1);
	Energy += 10 + rand(5);

	chr.chr_ai.energy = stf(Energy);
	chr.chr_ai.energyMax = stf(Energy);

	if(chr.id != PChar.id)
	{
		LAi_SetHP(chr, stf(HP), stf(HP));
	}
	else
	{
		LAi_SetCurHPMax(PChar);
	}

	iFencingLight += (iBonus + 10);
	iFencing += (iBonus + 10);
	iFencingHeavy += (iBonus + 10);

	if(iFencingLight > 100) { iFencingLight = 100; }
	if(iFencingLight < 30) { iFencingLight = 30; }

	if(iFencing > 100) { iFencing = 100; }
	if(iFencing < 30) { iFencing = 30; }

	if(iFencingHeavy > 100) { iFencingHeavy = 100; }
	if(iFencingHeavy < 30) { iFencingHeavy = 30; }

	chr.skill.FencingLight = iFencingLight;
	chr.skill.Fencing = iFencing;
	chr.skill.FencingHeavy = iFencingHeavy;

	if(chr.id != PChar.id)
	{
		SetCharacterPerk(chr, "Energaiser");
		SetCharacterPerk(chr, "SwordplayProfessional");
		SetCharacterPerk(chr, "AdvancedDefense");
		SetCharacterPerk(chr, "CriticalHit");
		SetCharacterPerk(chr, "Sliding");
	}
}

int GetNumPositionForCharInTournament()
{
	string sPos = "";

	int iRand = rand(7)+1;

	for(int i=1; i <= 8; i++)
	{
		sPos = "Position_" + i;
		if(iRand == i)
		{
			if(!CheckAttribute(PChar, "Arena.Tournament.Positions." + sPos))
			{
				PChar.Arena.Tournament.Positions.(sPos) = true;
				return i;
			}
			else
			{
				i = 0;
				iRand = rand(7)+1;
				continue;
			}
		}
	}

	return -1;
}

string GetModelForCharacterInTournament()
{
	string sModel = "";
	int iRand = rand(19) + 1;

	for(int i=1; i <= 20; i++)
	{
		sModel = "officer_" + i;

		if(iRand == i)
		{
			if(!CheckAttribute(PChar, "Arena.Tournament.Models." + sModel))
			{
				PChar.Arena.Tournament.Models.(sModel) = true;
				return sModel;
			}
			else
			{
				i = 0;
				iRand = rand(19)+1;
				continue;
			}
		}
	}
	return "officer_" + (rand(63)+1);
}

void ArenaTournamentSetPosition(int iNum, string sChar, string sStage)
{
	int iPosition = 1;
	switch(sStage)
	{
		case "1_2":
			if(iNum == 1 || iNum == 2) { iPosition = 1; }
			if(iNum == 3 || iNum == 4) { iPosition = 2; }
			if(iNum == 5 || iNum == 6) { iPosition = 3; }
			if(iNum == 7 || iNum == 8) { iPosition = 4; }
			PChar.Arena.Tournament.(sChar).Position.1_2 = iPosition;
		break;

		case "final":
			if(iNum == 1 || iNum == 2 || iNum == 3 || iNum == 4) { iPosition = 1;}
			if(iNum == 5 || iNum == 6 || iNum == 7 || iNum == 8) { iPosition = 2;}
			PChar.Arena.Tournament.(sChar).Position.final = iPosition;
		break;
	}
}

string ArenaTournamentGetCharacterIDFromPos(int p, string sType)
{
	aref pos;
	string sChar = "";

	for(int i=1; i <= 8; i++)
	{
		sChar = "Arena_Tournament_Character_" + i;

		if(i == 8)
		{
			sChar = "Blaze";
		}

		if(CheckAttribute(&Characters[GetCharacterIndex(sChar)], "ArenaTournament.looser"))
		{
			continue;
		}

		makearef(pos, PChar.Arena.Tournament.(sChar));

		if(sType == "1_4")
		{
			if(sti(pos.Position) == p)
			{
				return sChar;
			}
		}
		else
		{
			if(sti(pos.Position.(sType)) == p)
			{
				return sChar;
			}
		}
	}

	return "Arena_Tournament_Character_1";
}

void ArenaTournamentSetCharacterFromArena(ref chr)
{
	string sLocator = "";

	if(chr.id == "Arena_Tournament_Character_1") { sLocator = "arena_member_1"; }
	if(chr.id == "Arena_Tournament_Character_2") { sLocator = "arena_member_2"; }
	if(chr.id == "Arena_Tournament_Character_3") { sLocator = "arena_member_3"; }
	if(chr.id == "Arena_Tournament_Character_4") { sLocator = "arena_member_4"; }
	if(chr.id == "Arena_Tournament_Character_5") { sLocator = "arena_member_5"; }
	if(chr.id == "Arena_Tournament_Character_6") { sLocator = "arena_member_6"; }
	if(chr.id == "Arena_Tournament_Character_7") { sLocator = "arena_member_7"; }
	if(chr.id == "Blaze") { sLocator = "arena_member_8"; }

	ChangeCharacterAddressGroup(chr, "FencingTown_Arena", "goto", sLocator);
	LAi_SetActorType(chr);
	LAi_ActorTurnToLocator(chr, "item", "looser_detector");
	LAi_group_MoveCharacter(chr, LAI_DEFAULT_GROUP);
}

void ArenaTournamentPrepareInterface()
{
	ref attack, enemy;

	string sAttack = PChar.Arena.Tournament.Temp.Attack;
	string sEnemy = PChar.Arena.Tournament.Temp.Enemy;

	if(GetCharacterIndex(sAttack) != -1)
	{
		attack = &Characters[GetCharacterIndex(sAttack)];
		DeleteAttribute(attack, "ArenaTournament.Attack");
		DeleteAttribute(attack, "ArenaTournament.Enemy");
		ArenaTournamentSetCharacterFromArena(attack);
	}

	if(GetCharacterIndex(sEnemy) != -1)
	{
		enemy = &Characters[GetCharacterIndex(sEnemy)];
		DeleteAttribute(enemy, "ArenaTournament.Attack");
		DeleteAttribute(enemy, "ArenaTournament.Enemy");
		ArenaTournamentSetCharacterFromArena(enemy);
	}

	/*
	if(CheckAttribute(attack, "ArenaTournament.looser"))
	{
		if(attack.id != PChar.id)
		{
			ChangeCharacterAddress(attack, "None", "");
		}
		else
		{
			ArenaTournamentSetCharacterFromArena(attack);
		}
	}
	else
	{
		ArenaTournamentSetCharacterFromArena(attack);
	}

	if(CheckAttribute(enemy, "ArenaTournament.looser"))
	{
		if(enemy.id != PChar.id)
		{
			ChangeCharacterAddress(enemy, "None", "");
		}
		else
		{
			ArenaTournamentSetCharacterFromArena(enemy);
		}
	}
	else
	{
		ArenaTournamentSetCharacterFromArena(enemy);
	}*/
}


//-------------------------------------------------------------------------------
// Ставки
//-------------------------------------------------------------------------------
void GenerateArenaOdds()
{
	string sSaber, sSaberType;

	switch(rand(2)) { case 0: sSaberType = "FencingLight"; break; case 1: sSaberType = "Fencing"; break; case 2: sSaberType = "FencingHeavy"; break; }
	sSaber = GetSaberForArena(sSaberType);
	PChar.Arena.Odds.Saber.Light = sSaber;

	switch(rand(2)) { case 0: sSaberType = "FencingLight"; break; case 1: sSaberType = "Fencing"; break; case 2: sSaberType = "FencingHeavy"; break; }
	sSaber = GetSaberForArena(sSaberType);
	PChar.Arena.Odds.Saber.Saber = sSaber;

	switch(rand(2)) { case 0: sSaberType = "FencingLight"; break; case 1: sSaberType = "Fencing"; break; case 2: sSaberType = "FencingHeavy"; break; }
	sSaber = GetSaberForArena(sSaberType);
	PChar.Arena.Odds.Saber.Heavy = sSaber;

	GenerateArenaOddsDuel(1);
	GenerateArenaOddsDuel(2);
	GenerateArenaOddsDuel(3);

	int iMaxOdd = GetArenaOddsMaxOdd();
	PChar.Arena.Odds.MinOdd = 100;
	PChar.Arena.Odds.MaxOdd = iMaxOdd;
	PChar.Arena.Odds.Odd = 100;

	PChar.Arena.Odds.Temp.Attack = "";
	PChar.Arena.Odds.Temp.Enemy = "";
	PChar.Arena.Odds.Temp.Stage = 1;
	PChar.Arena.Odds.Temp.StageTemp = 1;
	PChar.Arena.Odds.Temp.Count = 0;
	PChar.Arena.Odds.Temp.WinnerCount = 0;
	PChar.Arena.Odds.Temp.LooserCount = 0;
	PChar.Arena.Odds.Temp.Winner = "";
}

void PrepareArenaOdds()
{
	if(PChar.Arena.Mode.NotOdd == false)
	{
		PChar.Arena.Odds.BiletCount = 1;
	}
	else
	{
		PChar.Arena.Odds.BiletCount = 0;
	}

	ChangeCharacterAddressGroup(CharacterFromID("ArenaBileter"), "FencingTown_ExitTown", "reload", "reload4");
	LAi_SetActorType(CharacterFromID("ArenaBileter"));
	PChar.Arena.Mode = "Odds";
	PChar.quest.PrepareArenaOddsContinue.win_condition.l1 = "locator";
	PChar.quest.PrepareArenaOddsContinue.win_condition.l1.location = "FencingTown_ExitTown";
	PChar.quest.PrepareArenaOddsContinue.win_condition.l1.locator_group = "reload";
	PChar.quest.PrepareArenaOddsContinue.win_condition.l1.locator = "reload4";
	PChar.quest.PrepareArenaOddsContinue.function = "PrepareArenaOddsContinue";
}

void PrepareArenaOddsContinue(string _tmp)
{
	Characters[GetCharacterIndex("ArenaBileter")].Dialog.CurrentNode = "First Time";
	LAi_SetActorType(CharacterFromID("ArenaBileter"));
	LAi_ActorDialogNow(CharacterFromID("ArenaBileter"), Pchar, "", -1);
}

void PrepareArenaOddsBilet()
{
	LAi_SetStayType(CharacterFromID("ArenaBileter"));
}

void PrepareArenaOddsEnd()
{
	LAi_SetStayType(CharacterFromID("ArenaBileter"));
	LAi_SetStayType(CharacterFromID("FencingTown_Head"));
	ChangeCharacterAddressGroup(CharacterFromID("FencingTown_Head"), "FencingTown_Arena", "goto", "arena_head");

	if(PChar.Arena.Mode.NotOdd == false)
	{
		Characters[GetCharacterIndex("FencingTown_Head")].dialog.currentnode = "FightInArena_8";
	}
	else
	{
		Characters[GetCharacterIndex("FencingTown_Head")].dialog.currentnode = "FightInArena_10";
	}

	Locations[FindLocation("FencingTown_ExitTown")].reload.l1.disable = false;

	Locations[FindLocation("FencingTown_Arena")].locators_radius.item.looser_detector = 2.0;

	PChar.quest.StartArenaOdds.win_condition.l1 = "location";
	PChar.quest.StartArenaOdds.win_condition.l1.location = "FencingTown_Arena";
	PChar.quest.StartArenaOdds.function = "StartArenaOdds";
}

void StartArenaOdds(string _tmp)
{
	InterfaceStates.Buttons.Save.enable = false;
	PChar.Arena = "Start";

	if(PChar.model.animation == "mushketer")
	{
		RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
	}

	CreateFireInArena();
	CreateArenaFightPeople();

	Locations[FindLocation("FencingTown_ExitTown")].reload.l1.disable = true;

	ChangeCharacterAddress(CharacterFromID("ArenaBileter"), "None", "");
	Locations[FindLocation(PChar.location)].reload.l1.disable = true;

	int iEnemy = -1;
	string sLocator = "arena_member_" + (rand(7)+1);

	int iStage = 1;
	int iCount = 1;
	for(int e=1; e<=6; e++)
	{
		switch(e)
		{
			case 1: iStage = 1; iCount = 1; break; case 2: iStage = 1; iCount = 2; break;
			case 3: iStage = 2; iCount = 1; break; case 4: iStage = 2; iCount = 2; break;
			case 5: iStage = 3; iCount = 1; break; case 6: iStage = 3; iCount = 2; break;
		}

		iEnemy = GetCharacterIndex("Arena_Odds_Duel_" + iStage + "_Character_" + iCount);

		if(iEnemy != -1)
		{
			sLocator = "arena_member_" + e;
			ChangeCharacterAddressGroup(&Characters[iEnemy], "FencingTown_Arena", "goto", sLocator);
			LAi_SetActorType(&Characters[iEnemy]);
			LAi_ActorTurnToLocator(&Characters[iEnemy], "item", "looser_detector");
		}
	}

	LAi_SetActorType(PChar);
	LAi_SetActorType(CharacterFromID("FencingTown_Head"));
	LAi_ActorWaitDialog(PChar, CharacterFromID("FencingTown_Head"));
	LAi_ActorDialog(CharacterFromID("FencingTown_Head"), PChar, "", 5.0, 1.0);
}

void StartArenaOddsContinue()
{
	LAi_SetPlayerType(PChar);

	PChar.quest.StartArenaOddsEnd.win_condition.l1 = "locator";
	PChar.quest.StartArenaOddsEnd.win_condition.l1.location = "FencingTown_Arena";
	PChar.quest.StartArenaOddsEnd.win_condition.l1.locator_group = "reload";
	PChar.quest.StartArenaOddsEnd.win_condition.l1.locator = "bashnya_1";
	PChar.quest.StartArenaOddsEnd.function = "StartArenaOddsEnd";
}

void StartArenaOddsEnd(string qName)
{
	ChangeCharacterAddressGroup(PChar, "FencingTown_Arena", "goto", "arena_vip_4");
	ChangeCharacterAddressGroup(CharacterFromID("FencingTown_Head"), "FencingTown_Arena", "goto", "arena_vip_3");

	LAi_SetActorType(PChar);
	LAi_SetActorType(CharacterFromID("FencingTown_Head"));

	LAi_ActorTurnToLocator(PChar, "item", "looser_detector");
	LAi_ActorTurnToLocator(CharacterFromID("FencingTown_Head"), "item", "looser_detector");

	DoQuestFunctionDelay("ArenaOddsGo", 3.0);
}

void ArenaOddsGo(string qName)
{
	ChangeCharacterAddressGroup(PChar, "FencingTown_Arena", "goto", "pchar_temp_loc");

	LAi_SetPlayerType(PChar);
	LAi_SetActorType(PChar);
	LAi_ActorStay(PChar);
	//LAi_ActorSetStayMode(PChar);

	bDisableCharacterMenu = true;
	PChar.TmpModel = PChar.model;
	PChar.model = "";
	SetNewModelToChar(PChar);

    	SetCharacterTask_None(GetMainCharacter());

	LAi_Fade("", "");

	float x = -2.26369;
	float y = 18.762;
	float z = -11.5217;

	locCameraToPos(x, y, z, false);

	ArenaOddsGoStart(1);
	ArenaOddsStartNewBattle();
}

void ArenaOddsGoStart(int iStage)
{
	ref attack, enemy;

	if(iStage != 1)
	{
		ArenaOddsSetCharacterFromArenaToLoc();
	}

	LAi_Fade("", "");

	int iChar = 0;

	string sChar = GetCharacterArenaOddsFromStage(iStage, 1);
	iChar = GetCharacterIndex(sChar);
	attack = &Characters[iChar];
	attack.ArenaOdds = true;
	attack.ArenaOdds.Attack = true;

	sChar = GetCharacterArenaOddsFromStage(iStage, 2);
	iChar = GetCharacterIndex(sChar);
	enemy = &Characters[iChar];
	enemy.ArenaOdds = true;
	enemy.ArenaOdds.Enemy = true;

	PChar.Arena.Odds.Temp.Attack = attack.id;
	PChar.Arena.Odds.Temp.Enemy = enemy.id;

	PChar.Arena.Odds.Temp.Count = 0;
	PChar.Arena.Odds.Temp.WinnerCount = 0;
	PChar.Arena.Odds.Temp.LooserCount = 0;

	ArenaOddsSetDetailsForChar(attack, iStage);
	ArenaOddsSetDetailsForChar(enemy, iStage);

	Log_Info(attack.name + " " + attack.lastname + " VS " + enemy.name + " " + enemy.lastname);

	if(PChar.Arena.Mode.NotOdd == false)
	{
		int iActionStage = sti(PChar.Arena.Odds.ActionFight);
		int iActionCharacter = sti(PChar.Arena.Odds.Character);

		if(iActionStage == iStage)
		{
			Log_Info("Вы сделали ставку на этот поединок. На дуэлянта по имени " + Characters[iActionCharacter].name + " " + Characters[iActionCharacter].lastname + ".");
		}
	}
}

void ArenaOddsStartNewBattle()
{
	LAi_Fade("", "");

	PlayStereoSound("new_round");

	ref attack, enemy;
	string sAttack = PChar.Arena.Odds.Temp.Attack;
	string sEnemy = PChar.Arena.Odds.Temp.Enemy;

	attack = &Characters[GetCharacterIndex(sAttack)];
	enemy = &Characters[GetCharacterIndex(sEnemy)];

	LAi_SetImmortal(attack, false);
	LAi_SetImmortal(enemy, false);

	LAi_SetWarriorType(attack);
	LAi_SetWarriorType(enemy);

	float x = -2.26369;
	float y = 18.762;
	float z = -11.5217;

	locCameraToPos(x, y, z, false);

	string sPlayerLocator, sEnemyLocator;
	if(rand(1) == 1)
	{
		sPlayerLocator = "aloc1"; sEnemyLocator = "aloc3";
	}
	else
	{
		sPlayerLocator = "aloc3"; sEnemyLocator = "aloc1";
	}

	ChangeCharacterAddressGroup(attack, "FencingTown_Arena", "rld", sPlayerLocator);
	ChangeCharacterAddressGroup(enemy, "FencingTown_Arena", "rld", sEnemyLocator);

	LAi_group_MoveCharacter(attack, "ARENA_ODDS_CHARACTER_1");
	LAi_group_MoveCharacter(enemy, "ARENA_ODDS_CHARACTER_2");

	LAi_group_SetHearRadius("ARENA_ODDS_CHARACTER_1", 100.0);
	LAi_group_SetHearRadius("ARENA_ODDS_CHARACTER_2", 100.0);
	LAi_group_SetRelation("ARENA_ODDS_CHARACTER_1", "ARENA_ODDS_CHARACTER_2", LAI_GROUP_ENEMY);
	LAi_group_FightGroups("ARENA_ODDS_CHARACTER_1", "ARENA_ODDS_CHARACTER_2", true);
}

void ArenaOddsSetLooser(ref chr)
{
	LAi_SetImmortal(chr, true);

	string sEnemy = PChar.Arena.Odds.Temp.Enemy;
	string sAttack = PChar.Arena.Odds.Temp.Attack;

	int iEnemy = GetCharacterIndex(sEnemy);
	int iAttack = GetCharacterIndex(sAttack);

	LAi_SetFightMode(&Characters[iEnemy], false);
	LAi_SetActorType(&Characters[iEnemy]);

	LAi_SetFightMode(&Characters[iAttack], false);
	LAi_SetActorType(&Characters[iAttack]);

	if(CheckAttribute(chr, "ArenaOdds.Attack"))
	{
		PChar.Arena.Odds.Temp.LooserCount = sti(PChar.Arena.Odds.Temp.LooserCount) + 1;
		Log_SetStringToLog("В этом раунде победу одержал " + Characters[iEnemy].name + " " + Characters[iEnemy].lastname);
	}
	else
	{
		PChar.Arena.Odds.Temp.WinnerCount = sti(PChar.Arena.Odds.Temp.WinnerCount) + 1;
		Log_SetStringToLog("В этом раунде победу одержал " + Characters[iAttack].name + " " + Characters[iAttack].lastname);
	}

	Log_SetStringToLog("На этот момент счёт в поединке - " + Characters[iAttack].name + " " + Characters[iAttack].lastname + " - " + PChar.Arena.Odds.Temp.WinnerCount + ":" + sti(PChar.Arena.Odds.Temp.LooserCount) + " - " + Characters[iEnemy].name + " " + Characters[iEnemy].lastname);

	DoQuestFunctionDelay("ArenaOddsCheckNewRound", 3.0);
}

void ArenaOddsCheckNewRound(string qName)
{
	PChar.Arena.Odds.Temp.Count = sti(PChar.Arena.Odds.Temp.Count) + 1;

	PlayStereoSound("new_round");

	string sEnemy = PChar.Arena.Odds.Temp.Enemy;
	string sAttack = PChar.Arena.Odds.Temp.Attack;

	int iEnemy = GetCharacterIndex(sEnemy);
	int iAttack = GetCharacterIndex(sAttack);

	if(sti(PChar.Arena.Odds.Temp.LooserCount) >= 3)
	{
		Characters[iAttack].ArenaOdds.looser = true;
		ArenaOddsDuelEnd(false);
	}
	else
	{
		if(sti(PChar.Arena.Odds.Temp.WinnerCount) >= 3)
		{
			Characters[iEnemy].ArenaOdds.looser = true;
			ArenaOddsDuelEnd(true);
		}
		else
		{
			ArenaOddsSetDetailsForChar(&Characters[iAttack], sti(PChar.Arena.Odds.Temp.Stage));
			ArenaOddsSetDetailsForChar(&Characters[iEnemy], sti(PChar.Arena.Odds.Temp.Stage));
			ArenaOddsStartNewBattle();
		}
	}
}

void ArenaOddsDuelEnd(bool bWin)
{
	LAi_Fade("", "");

	ref looser;
	string sEnemy = PChar.Arena.Odds.Temp.Enemy;
	string sAttack = PChar.Arena.Odds.Temp.Attack;

	int iEnemy = GetCharacterIndex(sEnemy);
	int iAttack = GetCharacterIndex(sAttack);

	ref enemy, attack;
	if(CheckAttribute(&Characters[iAttack], "ArenaOdds.looser"))
	{
		looser = &Characters[iAttack];
		PChar.Arena.Odds.Temp.Winner = Characters[iEnemy].id;
	}

	if(CheckAttribute(&Characters[iEnemy], "ArenaOdds.looser"))
	{
		looser = &Characters[iEnemy];
		PChar.Arena.Odds.Temp.Winner = Characters[iAttack].id;
	}

	if(PChar.Arena.Mode.NotOdd == false)
	{
		// логи для теста -->
		//Log_TestInfo("ID атакующего: " + Characters[iAttack].id);
		//Log_TestInfo("ID защищающегося: " + Characters[iEnemy].id);
		//Log_TestInfo("Кто победил: " + PChar.Arena.Odds.Temp.Winner);
		// логи для теста <--
	}

	int iStage = 0;

	if(PChar.Arena.Mode.NotOdd == false)
	{
		int iActionStage = sti(PChar.Arena.Odds.ActionFight);
		int iActionCharacter = sti(PChar.Arena.Odds.Character);
		if(iActionStage == sti(PChar.Arena.Odds.Temp.Stage))
		{
			// логи для теста -->
			//Log_TestInfo("ID того, на кого ставка: " + Characters[iActionCharacter].id);
			// логи для теста <--

			if(PChar.Arena.Odds.Temp.Winner == Characters[iActionCharacter].id)
			{
				PChar.Arena.Odds.Win = true;
				Log_InfoS("Вы сделали ставку на дуэлянта по имени " + Characters[iActionCharacter].name + " " + Characters[iActionCharacter].lastname + " и не прогадали! Ваш выигрыш составил " + sti(PChar.Arena.Odds.Prize) + " золотых.");
				Log_Info("Вы сможете получить выигрыш после соревнований.");
			}
			else
			{
				PChar.Arena.Odds.Win = false;
				Log_InfoS("Вы сделали ставку на дуэлянта по имени " + Characters[iActionCharacter].name + " " + Characters[iActionCharacter].lastname + " и проиграли.");
			}
		}
	}

	if(sti(PChar.Arena.Odds.Temp.Stage) == 1)
	{
		PChar.Arena.Odds.Temp.Stage = 2;
		PChar.Arena.Odds.Temp.StagePause = true;
	}

	if(sti(PChar.Arena.Odds.Temp.Stage) == 2 && PChar.Arena.Odds.Temp.StagePause == false)
	{
		PChar.Arena.Odds.Temp.Stage = 3;
		PChar.Arena.Odds.Temp.StagePause = true;
	}

	if(sti(PChar.Arena.Odds.Temp.Stage) == 3 && PChar.Arena.Odds.Temp.StagePause == false)
	{
		ArenaOddsEnd();
		return;
	}

	iStage = sti(PChar.Arena.Odds.Temp.Stage);
	ArenaOddsGoStart(iStage);
	ArenaOddsStartNewBattle();

	if(iStage == 2 || iStage == 3)
	{
		PChar.Arena.Odds.Temp.StagePause = false;
	}
}

void ArenaOddsEnd()
{
	LAi_Fade("", "");

	locCameraFollow();

	bool bWinner = PChar.Arena.Odds.Win;

	if(PChar.Arena.Mode.NotOdd == false)
	{
		PChar.Statistic.Arena.Count = sti(PChar.Statistic.Arena.Count) + 1;
		if(!bWinner)
		{
			PChar.Statistic.Arena.LooserCount = sti(PChar.Statistic.Arena.LooserCount) + 1;
			AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", даже капитан " + GetNameLugger(PChar, "f") + " не смо"+ GetSexPhrase("г","гла") +" правильно указать победителя одной из дуэлей, недавно проходившей на Арене и проигр"+ GetSexPhrase("ал","ала") +" свои деньги.", 5, 1);
		}
		else
		{
			PChar.Statistic.Arena.WinnerCount = sti(PChar.Statistic.Arena.WinnerCount) + 1;
			AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", капитан " + GetNameLugger(PChar, "f") + "  указ"+ GetSexPhrase("ал","ала") +" победителя одной из дуэлей, недавно проходившей на Арене и выигр"+ GetSexPhrase("ал","ала") +" деньги!", 5, 1);
		}
	}

	if(PChar.Arena.Mode.NotOdd == false)
	{
		Characters[GetCharacterIndex("FencingTown_Head")].dialog.currentnode = "FightInArena_9";
	}
	else
	{
		Characters[GetCharacterIndex("FencingTown_Head")].dialog.currentnode = "FightInArena_11";
	}

	bDisableCharacterMenu = false;
	PChar.model = PChar.TmpModel;
	SetNewModelToChar(PChar);

	InterfaceStates.Buttons.Save.enable = true;
	ChangeCharacterAddressGroup(PChar, "FencingTown_Arena", "reload", "bashnya_1");
	ChangeCharacterAddressGroup(CharacterFromID("FencingTown_Head"), "FencingTown_Arena", "goto", "arena_head");
	LAi_SetActorType(PChar);
	LAi_SetActorType(CharacterFromID("FencingTown_Head"));
	LAi_ActorWaitDialog(CharacterFromID("FencingTown_Head"), PChar);
	LAi_ActorDialog(PChar, CharacterFromID("FencingTown_Head"), "", 25.0, 1.0);

	Locations[FindLocation("FencingTown_Arena")].locators_radius.item.looser_detector = 0.5;
}

void ArenaOddsTheEnd()
{
	InterfaceStates.Buttons.Save.enable = true;
	LAi_SetPlayerType(PChar);

	string sSaber = "blade";
	string sMember = "";

	ref member;
	int iStage = 1;
	int iCount = 1;
	for(int i = 1; i <= 6; i++)
	{
		switch(i)
		{
			case 1: iStage = 1; iCount = 1; break; case 2: iStage = 1; iCount = 2; break;
			case 3: iStage = 2; iCount = 1; break; case 4: iStage = 2; iCount = 2; break;
			case 5: iStage = 3; iCount = 1; break; case 6: iStage = 3; iCount = 2; break;
		}

		sMember = "Arena_Odds_Duel_" + iStage + "_Character_" + iCount;
		member = &Characters[GetCharacterIndex(sMember)];

		RemoveCharacterEquip(member, BLADE_ITEM_TYPE);

		if(CheckAttribute(member, "ArenaAction"))
		{
			DeleteAttribute(member, "ArenaAction");
		}

		if(CheckAttribute(member, "ArenaOdds.looser"))
		{
			DeleteAttribute(member, "ArenaOdds.looser");
		}

		LAi_SetStayType(member);
		ChangeCharacterAddress(member, "None", "");
		member.LifeDay = 0;
		Log_TestInfo("Удаляем персонажа для турнира: " + sMember);
	}

	LAi_group_Delete("ARENA_ODDS_CHARACTER_1");
	LAi_group_Delete("ARENA_ODDS_CHARACTER_2");

	LAi_SetOwnerType(CharacterFromID("FencingTown_Head"));
	ChangeCharacterAddressGroup(CharacterFromID("FencingTown_Head"), "FencingTown_Townhall", "goto", "goto2");

	DoQuestReloadToLocation("FencingTown_ExitTown", "reload", "reload4", "");

	if(CheckAttribute(PChar, "ArenaAction"))
	{
		DeleteAttribute(PChar, "ArenaAction");
	}

	if(CheckAttribute(PChar, "ArenaOdds.looser"))
	{
		DeleteAttribute(PChar, "ArenaOdds.looser");
	}

	if(CheckAttribute(PChar, "Arena.Odds"))
	{
		DeleteAttribute(PChar, "Arena.Odds");
	}

	ClearArena("");
}

void ArenaOddsSetDetailsForChar(ref chr, int iStage)
{
	float Energy = LAi_GetCharacterMaxEnergy(chr);
	chr.chr_ai.energy = stf(Energy);
	chr.chr_ai.energyMax = stf(Energy);
	SetEnergyToCharacter(chr);
	LAi_SetCurHPMax(chr);

	SetCharacterPerk(chr, "Energaiser");
	SetCharacterPerk(chr, "SwordplayProfessional");
	SetCharacterPerk(chr, "AdvancedDefense");
	SetCharacterPerk(chr, "CriticalHit");
	SetCharacterPerk(chr, "Sliding");

	string sSaber = "blade1";

	switch(iStage)
	{
		case 1: sSaber = PChar.Arena.Odds.Saber.Light; break;
		case 2: sSaber = PChar.Arena.Odds.Saber.Saber; break;
		case 3: sSaber = PChar.Arena.Odds.Saber.Heavy; break;
	}

	RemoveCharacterEquip(chr, GUN_ITEM_TYPE);
	RemoveCharacterEquip(chr, BLADE_ITEM_TYPE);

	GiveItem2Character(chr, sSaber);
	EquipCharacterByItem(chr, sSaber);
}

void ArenaOddsSetCharacterFromArenaToLoc()
{
	ref attack, enemy;

	string sAttack = PChar.Arena.Odds.Temp.Attack;
	string sEnemy = PChar.Arena.Odds.Temp.Enemy;

	attack = &Characters[GetCharacterIndex(sAttack)];
	enemy = &Characters[GetCharacterIndex(sEnemy)];

	DeleteAttribute(attack, "ArenaOdds.Attack");
	DeleteAttribute(attack, "ArenaOdds.Enemy");

	DeleteAttribute(enemy, "ArenaOdds.Attack");
	DeleteAttribute(enemy, "ArenaOdds.Enemy");

	ArenaOddsSetCharacterFromArena(attack);
	ArenaOddsSetCharacterFromArena(enemy);
}

void ArenaOddsSetCharacterFromArena(ref chr)
{
	string sLocator = "";

	if(chr.id == "Arena_Odds_Duel_1_Character_1") { sLocator = "arena_member_1"; }
	if(chr.id == "Arena_Odds_Duel_1_Character_2") { sLocator = "arena_member_2"; }
	if(chr.id == "Arena_Odds_Duel_2_Character_1") { sLocator = "arena_member_3"; }
	if(chr.id == "Arena_Odds_Duel_2_Character_2") { sLocator = "arena_member_4"; }
	if(chr.id == "Arena_Odds_Duel_3_Character_1") { sLocator = "arena_member_5"; }
	if(chr.id == "Arena_Odds_Duel_3_Character_2") { sLocator = "arena_member_6"; }

	ChangeCharacterAddressGroup(chr, "FencingTown_Arena", "goto", sLocator);
	LAi_group_MoveCharacter(chr, "ARENA_ODDS_NONE_ACTION");

	LAi_SetActorType(chr);
	LAi_ActorTurnToLocator(chr, "item", "looser_detector");
}

string GetCharacterArenaOddsFromStage(int iStage, int iNum)
{
	string sChar = "Arena_Odds_Duel_" + iStage + "_Character_1";

	string sFight = "Fight_" + iStage;
	string sFightChar = "Char_" + iNum;

	if(CheckAttribute(PChar, "Arena.Odds." + sFight + "." + sFightChar))
	{
		sChar = PChar.Arena.Odds.(sFight).(sFightChar);
	}

	return sChar;
}

void GenerateArenaOddsDuel(int iCount)
{
	ref chr;
	int iChar = 0;
	string sChar, sModel;

	string sFight = "Fight_" + iCount;
	string sFightChar = "";
	for(int i=1; i <= 2; i++)
	{
		iChar = NPC_GenerateCharacter("Arena_Odds_Duel_" + iCount + "_Character_" + i, "officer_"+(rand(63)+1), "man", "man", GetRank(PChar, MOD_SKILL_ENEMY_RATE), PIRATE, -1, true);

		chr = &Characters[iChar];
		DeleteAttribute(chr, "items");
		chr.items = "";

		sChar = "Arena_Odds_Duel_" + iCount + "_Character_" + i;
		//sModel = GetModelForCharacterInOdds();

		//chr.id = "Arena_Odds_Duel_" + iCount + "_Character_" + i;
		//chr.model = sModel;
		//chr.model.animation = "man";
		//SetNewModelToChar(chr);
		SetRandomNameToCharacter(chr);
		ArenaOddsSetCharacterDetails(chr);
		//FaceMaker(chr);

		sFightChar = "Char_" + i;
		PChar.Arena.Odds.(sFight).(sFightChar) = sChar;
	}

	DeleteAttribute(PChar, "Arena.Odds.Models");
}

void ArenaOddsSetCharacterDetails(ref chr)
{
	int iRank = GetRank(PChar, MOD_SKILL_ENEMY_RATE);
	int iFencingLight = sti(PChar.skill.FencingLight);
	int iFencing = sti(PChar.skill.Fencing);
	int iFencingHeavy = sti(PChar.skill.FencingHeavy);

	int rand_1 = rand(9)+1;
	int rand_2 = rand(9)+1;

	rand_1 += rand_2;

	float HP = 200 + (rand(20) * rand_1);
	if(HP > 1000)
	{
		HP = 1000;
	}
	LAi_SetHP(chr, HP, HP);

	float Energy = LAi_GetCharacterMaxEnergy(chr);

	chr.chr_ai.energy = stf(Energy);
	chr.chr_ai.energyMax = stf(Energy);

	int iSkill = GetArenaOddsGreatestFencingSkill(chr);

	iFencingLight += 20 + rand(50);
	iFencing +=  20 + rand(50);
	iFencingHeavy += 20 + rand(50);

	if(iFencingLight > 100) { iFencingLight = 100 - rand(30); }
	if(iFencingLight < 30) { iFencingLight = 30 + rand(30); }

	if(iFencing > 100) { iFencing = 100 - rand(30); }
	if(iFencing < 30) { iFencing = 30 + rand(30); }

	if(iFencingHeavy > 100) { iFencingHeavy = 100 - rand(30); }
	if(iFencingHeavy < 30) { iFencingHeavy = 30 + rand(30); }

	chr.skill.FencingLight = iFencingLight;
	chr.skill.Fencing = iFencing;
	chr.skill.FencingHeavy = iFencingHeavy;

	float fRate = GetArenaOddsRateForCharacter(chr);
	chr.Arena.Odds.Rate = fRate;
}

float GetArenaOddsRateForCharacter(ref chr)
{
	float fRate = 10.0;
	float HP = LAi_GetCharacterMaxHP(chr);

	HP /= 80;
	fRate -= HP;

	int iSkill = GetArenaOddsGreatestFencingSkill(chr);
	iSkill *= 10;
	iSkill /= 100;

	fRate -= stf(iSkill);

	int iRandBonus = rand(3)+1;
	float fBonus = 1.1 * (iRandBonus);

	fRate += fBonus;

	if(fRate > 15.0) { fRate = 15.0; }
	if(fRate < 1.3) { fRate = 1.3; }

	return fRate;
}

int GetArenaOddsGreatestFencingSkill(ref chr)
{
	int iFencingLight = sti(chr.skill.FencingLight);
	int iFencing = sti(chr.skill.Fencing);
	int iFencingHeavy = sti(chr.skill.FencingHeavy);

	if(iFencingLight >= iFencing && iFencingLight >= iFencingHeavy)
	{
		return iFencingLight;
	}

	if(iFencing >= iFencingLight && iFencing >= iFencingHeavy)
	{
		return iFencing;
	}

	if(iFencingHeavy >= iFencing && iFencingHeavy >= iFencingLight)
	{
		return iFencingHeavy;
	}

	return iFencing;
}

int GetArenaOddsMaxOdd() // LEO: Параметры ставок - изимани скейл с ростом уровня
{
	int iRank = GetRank(PChar, MOD_SKILL_ENEMY_RATE);
	int iOdd = iRank * ((20 + rand(20)) * sti(PChar.rank)) + rand(1000);

	// if(iOdd > 25000) { iOdd = 25000; }	// LEO: Без ограничений
	if(iOdd < 100) { iOdd = 100; }

	return iOdd;
}

string GetModelForCharacterInOdds()
{
	string sModel = "";
	int iRand = rand(19) + 1;

	for(int i=1; i <= 20; i++)
	{
		sModel = "officer_" + i;

		if(iRand == i)
		{
			if(!CheckAttribute(PChar, "Arena.Odds.Models." + sModel))
			{
				PChar.Arena.Odds.Models.(sModel) = true;
				return sModel;
			}
			else
			{
				i = 0;
				iRand = rand(19)+1;
				continue;
			}
		}
	}
	return "officer_" + (rand(63)+1);
}

//-------------------------------------------------------------------------------
// other functions
//-------------------------------------------------------------------------------
string GetSkillFromSaber(string sSaber)
{
	ref Saber = &Items[FindItem(sSaber)];
	if(CheckAttribute(Saber, "FencingType"))
	{
		return Saber.FencingType;
	}

	return "Fencing";
}

string GetSaberForArena(string sType)
{
	/*
	int iRand = rand(Weapon_End) + Weapon_Start;

	for(int i=Weapon_Start; i<Weapon_End; i++)
	{
		if(i == iRand)
		{
			if(CheckAttribute(&Items[i], "groupID"))
			{
				if(Items[i].groupID == BLADE_ITEM_TYPE && !CheckAttribute(&Items[i], "UniqueSaber"))
				{
					return Items[i].id;
				}
				else
				{
					iRand = rand(Weapon_End) + Weapon_Start;
					i = Weapon_Start;
					continue;
				}
			}
			else
			{
				iRand = rand(Weapon_End) + Weapon_Start;
				i = Weapon_Start;
				continue;
			}
		}
	}
	*/

	// Примитивным рандомом
	switch(sType)
	{
		case "FencingLight":
			switch(rand(6))
			{
				case 0: return "blade2"; break;
				case 1: return "blade6"; break;
				case 2: return "blade9"; break;
				case 3: return "blade14"; break;
				case 4: return "blade19"; break;
				case 5: return "blade22"; break;
				case 6: return "blade23"; break;
			}
		break;

		case "Fencing":
			switch(rand(8))
			{
				case 0: return "blade1"; break;
				case 1: return "blade4"; break;
				case 2: return "topor3"; break;
				case 3: return "blade3"; break;
				case 4: return "blade7"; break;
				case 5: return "blade12"; break;
				case 6: return "blade18"; break;
				case 7: return "blade30"; break;
				case 8: return "blade25"; break;
			}
		break;

		case "FencingHeavy":
			switch(rand(5))
			{
				case 0: return "blade10"; break;
				case 1: return "blade35"; break;
				case 2: return "blade11"; break;
				case 3: return "topor1"; break;
				case 4: return "blade15"; break;
				case 5: return "blade16"; break;
			}
		break;
	}

	return "blade1";
}

string GetSaberForArenaT(string sType, int LA)
{
	// Примитивным рандомом
	switch(sType)
	{
		case "FencingLight":
			if (LA == 1)
			{
				switch(rand(2))
				{
					case 0: return "blade9"; break;
					case 1: return "blade14"; break;
					case 2: return "blade45"; break;
				}
			}
			if (LA == 2)
			{
				switch(rand(3))
				{
					case 0: return "blade19"; break;
					case 1: return "blade22"; break;
					case 2: return "blade36"; break;
					case 3: return "blade37"; break;
				}
			}
			if (LA == 3)
			{
				switch(rand(4))
				{
					case 0: return "blade14"; break;
					case 1: return "blade23"; break;
					case 2: return "blade27"; break;
					case 3: return "blade38"; break;
					case 4: return "blade26"; break;
				}
			}
		break;

		case "Fencing":
			if (LA == 1)
			{
				switch(rand(3))
				{
					case 0: return "blade7"; break;
					case 1: return "blade12"; break;
					case 2: return "blade18"; break;
					case 3: return "topor_05"; break;
				}
			}
			if (LA == 2)
			{
				switch(rand(4))
				{
					case 0: return "blade31"; break;
					case 1: return "blade34"; break;
					case 2: return "blade39"; break;
					case 3: return "blade40"; break;
					case 4: return "blade46"; break;
				}
			}
			if (LA == 3)
			{
				switch(rand(2))
				{
					case 0: return "blade30"; break;
					case 1: return "blade24"; break;
					case 2: return "blade25"; break;
				}
			}
		break;

		case "FencingHeavy":
			if (LA == 1)
			{
				switch(rand(2))
				{
					case 0: return "blade8"; break;
					case 1: return "blade11"; break;
					case 2: return "blade16"; break;
				}
			}
			if (LA == 2)
			{
				switch(rand(3))
				{
					case 0: return "blade15"; break;
					case 1: return "blade21"; break;
					case 2: return "blade42"; break;
					case 3: return "topor2"; break;
				}
			}
			if (LA == 3)
			{
				switch(rand(3))
				{
					case 0: return "blade13"; break;
					case 1: return "blade20"; break;
					case 2: return "blade33"; break;
					case 3: return "blade28"; break;
				}
			}
		break;
	}

	return "blade1";
}

int GetOddForDuelCharacter(ref chr, int iSkill)
{
	int iSum = 0;
	int iRank = GetRank(PChar, MOD_SKILL_ENEMY_RATE);
	int iLeader = sti(chr.skill.LeaderShip);
	float HP = LAi_GetCharacterMaxHP(chr);

	// --> LEO: Серьёзные ставки против потного противника с антифритайзовской системой финтов - анимка Spy
	HP *= 10 + (sti(PChar.rank)*2);

	iRank *= 30 + (sti(PChar.rank)*6);
	iLeader *= 25 + (sti(PChar.rank)*5);
	iSkill *= 35 + (sti(PChar.rank)*7);

	// <-- LEO
	iSum = iRank + iLeader + iSkill + HP;

	return iSum;
}

void ArenaEtapsGetEtap()
{
	string sType_1, sType_2, sType_3, sType_4, sType_5;
	int iQuantity = 0;
	int iCost = 0;

	for(int e=1; e <= 5; e++)
	{
		switch(e)
		{
			case 1:
				sType_1 = ArenaEtapsGetEtapType(1, "");
				iQuantity = 1;
				iCost = ArenaEtapsGetCostForEtap(sType_1, iQuantity);

				PChar.Arena.Etaps.Etap_1.Type = sType_1;
				PChar.Arena.Etaps.Etap_1.Quantity = iQuantity;
				PChar.Arena.Etaps.Etap_1.Cost = iCost;
			break;

			case 2:
				sType_2 = ArenaEtapsGetEtapType(2, sType_1);
				iQuantity = rand(4) + 1;
				iCost = ArenaEtapsGetCostForEtap(sType_2, iQuantity);

				PChar.Arena.Etaps.Etap_2.Type = sType_2;
				PChar.Arena.Etaps.Etap_2.Quantity = iQuantity;
				PChar.Arena.Etaps.Etap_2.Cost = iCost;
			break;

			case 3:
				sType_3 = ArenaEtapsGetEtapType(3, sType_2);
				iQuantity = rand(4) + 1;
				iCost = ArenaEtapsGetCostForEtap(sType_3, iQuantity);

				PChar.Arena.Etaps.Etap_3.Type = sType_3;
				PChar.Arena.Etaps.Etap_3.Quantity = iQuantity;
				PChar.Arena.Etaps.Etap_3.Cost = iCost;
			break;

			case 4:
				sType_4 = ArenaEtapsGetEtapType(4, sType_3);
				iQuantity = rand(4) + 1;
				iCost = ArenaEtapsGetCostForEtap(sType_4, iQuantity);

				PChar.Arena.Etaps.Etap_4.Type = sType_4;
				PChar.Arena.Etaps.Etap_4.Quantity = iQuantity;
				PChar.Arena.Etaps.Etap_4.Cost = iCost;
			break;

			case 5:
				sType_5 = ArenaEtapsGetEtapType(5, "");
				iQuantity = 1;
				iCost = ArenaEtapsGetCostForEtap(sType_5, iQuantity);

				PChar.Arena.Etaps.Etap_5.Type = sType_5;
				PChar.Arena.Etaps.Etap_5.Quantity = iQuantity;
				PChar.Arena.Etaps.Etap_5.Cost = iCost;
			break;
		}
	}
}

string ArenaEtapsGetEtapType(int iEtap, string sBack)
{
	if(iEtap == 1)
	{
		switch(rand(3))
		{
			case 0: return "crabBig"; break;
			case 1: return "Skel"; break;
			case 2: return "SkelOld"; break;
			case 3: return "monkey"; break;
		}
	}

	if(iEtap == 2 || iEtap == 3 || iEtap == 4)
	{
		if(sBack == "Skel" || sBack == "SkelOld")
		{
			switch(rand(1))
			{
				case 0: return "crabBig"; break;
				case 1: return "monkey"; break;
			}
		}
		else
		{
			if(sBack == "crabBig")
			{
				switch(rand(2))
				{
					case 0: return "monkey"; break;
					case 1: return "Skel"; break;
					case 2: return "SkelOld"; break;
				}
			}
			else
			{
				if(sBack == "monkey")
				{
					switch(rand(2))
					{
						case 0: return "crabBig"; break;
						case 1: return "Skel"; break;
						case 2: return "SkelOld"; break;
					}
				}
			}
		}
	}

	if(iEtap == 5)
	{
		if(rand(2) > 1)
		{
			return "SkelKing";
		}
		else
		{
			return "crabBigKing";
		}
	}
}

int ArenaEtapsGetCostForEtap(string sType, int iQuantity)
{
	int iRank = GetRank(PChar, 0);
	int iLeader = GetCharacterSkill(PChar, SKILL_LEADERSHIP);
	int iType = 0;
	int iCost = 0;

	iRank *= 100 + (sti(PChar.rank)*2);
	iLeader *= 200 + (sti(PChar.rank)*4);

	switch(sType)
	{
		case "crabBig": iType = 40 + (sti(PChar.rank)*20); break;
		case "Skel": iType = 220 + (sti(PChar.rank)*110); break;
		case "SkelOld": iType = 220 + (sti(PChar.rank)*110); break;
		case "monkey": iType = 55 + (sti(PChar.rank)*25); break;
		case "crabBigKing": iType = 4000 + (sti(PChar.rank)*2000); break;
		case "SkelKing": iType = 5000 + (sti(PChar.rank)*2500); break;
	}

	//iQuantity += rand(2);

	//iCost = iRank + iLeader + (iQuantity * iType) + rand(1000);
	iCost = (iRank + iLeader + iType) * iQuantity + rand(1000);

	return iCost;
}

void ClearArena(string qName)
{
	if(CheckAttribute(PChar, "Arena"))
	{
		DeleteAttribute(PChar, "Arena");
	}
	if(CheckAttribute(PChar, "ArenaAction"))
	{
		DeleteAttribute(PChar, "ArenaAction");
	}
	if(CheckAttribute(PChar, "ArenaEtapsAction"))
	{
		DeleteAttribute(PChar, "ArenaEtapsAction");
	}
	if(CheckAttribute(PChar, "ArenaTournament"))
	{
		DeleteAttribute(PChar, "ArenaTournament");
	}
	if(CheckAttribute(PChar, "ArenaOdds"))
	{
		DeleteAttribute(PChar, "ArenaOdds");
	}

	Locations[FindLocation("FencingTown_ExitTown")].reload.l2.disable = 0;
	Locations[FindLocation("FencingTown_ExitTown")].reload.l3.disable = 0;
	Locations[FindLocation("FencingTown_ExitTown")].reload.l4.disable = 0;

	ClearArenaCharacters();

	PChar.Arena = "none";
	SetArenaTimeWait();
}

void ClearArenaCharacters()
{
	ref member;
	if(GetCharacterIndex("Arena Duel Characer") != -1)
	{
		member = &Characters[GetCharacterIndex("Arena Duel Characer")];
		member.LifeDay = 0;
	}

	int i = 0;

	string sMember = "";
	for(i = 1; i <= 7; i++)
	{
		sMember = "Arena_Tournament_Character_" + i;
		if(GetCharacterIndex(sMember) == -1)
		{
			continue;
		}

		member = CharacterFromID(sMember);
		member.LifeDay = 0;
	}


	int iStage = 1;
	int iCount = 1;
	for(i = 1; i <= 6; i++)
	{
		switch(i)
		{
			case 1: iStage = 1; iCount = 1; break; case 2: iStage = 1; iCount = 2; break;
			case 3: iStage = 2; iCount = 1; break; case 4: iStage = 2; iCount = 2; break;
			case 5: iStage = 3; iCount = 1; break; case 6: iStage = 3; iCount = 2; break;
		}

		sMember = "Arena_Odds_Duel_" + iStage + "_Character_" + iCount;
		if(GetCharacterIndex(sMember) == -1)
		{
			continue;
		}

		member = CharacterFromID(sMember);
		member.LifeDay = 0;
	}
}

void ClearArenaTime(string qName)
{
	if(CheckAttribute(PChar, "Arena"))
	{
		DeleteAttribute(PChar, "Arena");
	}
	if(CheckAttribute(PChar, "ArenaAction"))
	{
		DeleteAttribute(PChar, "ArenaAction");
	}
	if(CheckAttribute(PChar, "ArenaEtapsAction"))
	{
		DeleteAttribute(PChar, "ArenaEtapsAction");
	}
	if(CheckAttribute(PChar, "ArenaTournament"))
	{
		DeleteAttribute(PChar, "ArenaTournament");
	}
	if(CheckAttribute(PChar, "ArenaOdds"))
	{
		DeleteAttribute(PChar, "ArenaOdds");
	}

	PChar.Arena = "none";
	SetArenaTimeWait();
}

//-------------------------------------------------------------------------------
// Заселяем
//-------------------------------------------------------------------------------
void CreateArenaCitizens(aref loc)
{
	if(!CheckAttribute(loc, "id"))
	{
		return;
	}

	if(loc.id != "FencingTown_Fort")
	{
		return;
	}

	if(isLocationHasCitizens(loc.id))
	{
		return;
	}

	int iCharacter = 0;
	int iNation = PIRATE;

	ref chr;

	string sModels[12];

	sModels[0] = "";
	sModels[1] = "officer_12";
	sModels[2] = "officer_13";
	sModels[3] = "officer_11";
	sModels[4] = "officer_4";
	sModels[5] = "officer_5";
	sModels[6] = "officer_16";
	sModels[7] = "officer_7";
	sModels[8] = "officer_18";
	sModels[9] = "officer_9";
	sModels[10] = "officer_1";
	sModels[11] = "officer_10";

	int iRank = GetRank(PChar, MOD_SKILL_ENEMY_RATE);
	int iQuantity = rand(5)+6;

	for(int i=1; i <= iQuantity; i++)
	{
		iCharacter = NPC_GenerateCharacter("FencingTown_Citizen_" + i, sModels[i], "man", "man", iRank, iNation, 2, true);
		chr = &Characters[iCharacter];

		SetFantomParamFromRank(chr, iRank, true);
		chr.Dialog.FileName = "FencingTown_dialog.c";
		chr.Dialog.CurrentNode = "First Time";

		if(rand(1) == 1)
		{
			chr.greeting = "cit_common1";
		}
		else
		{
			chr.greeting = "cit_common";
		}

		chr.quest.meeting = "0";
		//chr.City = "";
		chr.CityType = "FencingTown";
		PlaceCharacter(chr, "goto", "random");
		LAi_SetCitizenType(chr);
		LAi_group_MoveCharacter(chr, "PIRATE_CITIZENS");
		SetFoodToCharacter(chr, 3, 20);
	}

	if(GetCharacterIndex("FencingTown_Head") == -1)
	{
		SetFencingTownHead();
	}
}

void SetFencingTownHead()
{
	int iRank = 20 + rand(15);

	int iChar = NPC_GenerateCharacter("FencingTown_Head", "Hobart", "man", "man", iRank, PIRATE, -1, true);
	ref chr = &Characters[iChar];

	chr.dialog.Filename = "FencingTownHead_dialog.c";
	chr.dialog.currentnode = "First Time";
	//chr.city = "";
	chr.greeting = "Gr_ArenaHead";
	LAi_SetOwnerType(chr);
	LAi_SetImmortal(chr, true);
	LAi_group_MoveCharacter(chr, "PIRATE_CITIZENS");
	ChangeCharacterAddressGroup(chr, "FencingTown_Townhall", "goto", "goto2");
	SetFantomParamFromRank(chr, iRank, true);
	SetCharacterPerk(chr, "Energaiser");
	SetCharacterPerk(chr, "SwordplayProfessional");
}

//-------------------------------------------------------------------------------
// Оформление
//-------------------------------------------------------------------------------

// Огонь
void CreateFireInArena()
{
	float x, y, z;

	int n = 0;
	int step = 0;

	// Первая часть
	x = -1.948;
	y = 15.762;
	z = 2.95;

	step = 42;
	for(n = 1; n <= step; n++)
	{
		x += 0.1;
		CreateParticleSystem("fire", x, y, z,-1.57,0,0,0);
	}

	// Вторая часть
	x = 2.3047;
	z = 3.3012;

	step = 40;
	for(n = 1; n <= step; n++)
	{
		z += 0.1;
		CreateParticleSystem("fire", x, y, z,-1.57,0,0,0);
	}

	// Третья часть
	x = 2.5038;
	z = 7.1013;

	step = 40;
	for(n = 1; n <= step; n++)
	{
		x += 0.1;
		CreateParticleSystem("fire", x, y, z,-1.57,0,0,0);
	}

	// Четвёртая часть
	x = 6.6021;
	z = 6.8021;

	step = 123;
	for(n = 1; n <= step; n++)
	{
		z -= 0.1;
		CreateParticleSystem("fire", x, y, z,-1.57,0,0,0);
	}

	// Пятая часть
	x = 6.4805;
	z = -5.1131;

	step = 130;
	for(n = 1; n <= step; n++)
	{
		x -= 0.1;
		CreateParticleSystem("fire", x, y, z,-1.57,0,0,0);
	}

	// Шестая часть
	x = -6.4291;
	z = -5.053;

	step = 126;
	for(n = 1; n <= step; n++)
	{
		z += 0.1;
		CreateParticleSystem("fire", x, y, z,-1.57,0,0,0);
	}

	// Седьмая часть
	x = -6.2873;
	z = 7.0759;

	step = 40;
	for(n = 1; n <= step; n++)
	{
		x += 0.1;
		CreateParticleSystem("fire", x, y, z,-1.57,0,0,0);
	}

	// Восьмая часть
	x = -2.1548;
	z = 7.0156;

	step = 40;
	for(n = 1; n <= step; n++)
	{
		z -= 0.1;
		CreateParticleSystem("fire", x, y, z,-1.57,0,0,0);
	}

	// "Фонарики"
	x = -4.3352; y = 17.887; z = -4.6905;
	CreateParticleSystem("torch", x, y, z,-1.57,0,0,0);

	x = 4.4049;
	CreateParticleSystem("torch", x, y, z,-1.57,0,0,0);
}

void CreateArenaFightPeople()
{
	int iCitizenQuantity = rand(10) + 13;
	int iTraderQuantity = rand(10) + 8;

	ref chr;
	string sType, sLocator, sAnimation;
	for(int i=1; i <= iCitizenQuantity; i++)
	{
		switch(rand(2))
		{
			case 0: sType = "pirate"; break;
			case 1: sType = "citizen"; break;
			case 2: sType = "shipowner"; break;
		}

		if(rand(1) == 0)
		{
			sAnimation = "Sit_Idle02";
		}
		else
		{
			sAnimation = "Sit2_Idle0" + (rand(6)+1);
		}

		chr = GetCharacter(NPC_GeneratePhantomCharacter(sType, PIRATE, MAN, 0));
		RemoveCharacterEquip(chr, GUN_ITEM_TYPE);
		RemoveCharacterEquip(chr, BLADE_ITEM_TYPE);

		sLocator = GetLocatorForCitizenInArenaFight();
		ChangeCharacterAddressGroup(chr, PChar.location, "sit", sLocator);

		chr.nonTable = true;

		LAi_SetImmortal(chr, true);
		LAi_SetActorTypeNoGroup(chr);
		LAi_ActorSetSitMode(chr);
		LAi_ActorTurnToLocator(chr, "goto", "wall_player_1");
		LAi_ActorAnimation(chr, sAnimation, "", 5.0);

		LAi_group_MoveCharacter(chr, "PIRATE_CITIZENS");
	}

	for(int n=1; n <= iTraderQuantity; n++)
	{
		switch(rand(1))
		{
			case 0: sType = "trader"; break;
			case 1: sType = "usurer"; break;
		}

		sAnimation = "idle_" + (rand(10)+1);

		chr = GetCharacter(NPC_GeneratePhantomCharacter(sType, PIRATE, MAN, 0));
		RemoveCharacterEquip(chr, GUN_ITEM_TYPE);
		RemoveCharacterEquip(chr, BLADE_ITEM_TYPE);

		sLocator = GetLocatorForTraderInArenaFight();
		ChangeCharacterAddressGroup(chr, PChar.location, "goto", sLocator);

		chr.nonTable = true;
		LAi_SetImmortal(chr, true);
		LAi_SetActorTypeNoGroup(chr);
		//LAi_ActorSetSitMode(chr);
		LAi_ActorTurnToLocator(chr, "goto", "wall_player_1");
		LAi_ActorAnimation(chr, sAnimation, "", 5.0);

		LAi_group_MoveCharacter(chr, "PIRATE_CITIZENS");
	}
}

string GetLocatorForCitizenInArenaFight()
{
	int iRand = rand(117)+1;
	string sLocator = "";

	for(int i=1; i <= 118; i++)
	{
		if(i == iRand)
		{
			sLocator = "arena_sit_" + i;
			if(!CheckAttribute(PChar, "Arena.Locators." + sLocator))
			{
				PChar.Arena.Locators.(sLocator) = "use";
				return sLocator;
			}
			else
			{
				iRand = rand(117)+1;
				i = 1;
			}
		}
	}
	return "arena_sit_1";
}

string GetLocatorForTraderInArenaFight()
{
	int iRand = rand(90)+1;
	string sLocator = "";

	for(int i=1; i <= 91; i++)
	{
		if(i == iRand)
		{
			sLocator = "arena_stay_" + i;
			if(!CheckAttribute(PChar, "Arena.Locators." + sLocator))
			{
				PChar.Arena.Locators.(sLocator) = "use";
				return sLocator;
			}
			else
			{
				iRand = rand(90)+1;
				i = 1;
			}
		}
	}
	return "arena_stay_1";
}

///////////////////////////////////////////////////////////////////////////////////
// OTHER FUNCTIONS
///////////////////////////////////////////////////////////////////////////////////
void CheckAcademyAndOtherLoosers(ref chr)
{
	bool ok = CheckAttribute(chr, "LandAcademy") || CheckAttribute(chr, "ArenaAction") || CheckAttribute(chr, "ArenaEtapsAction") || CheckAttribute(chr, "ArenaTournament") || CheckAttribute(chr, "ArenaOdds");
	if(ok)
	{
		if(CheckAttribute(chr, "LandAcademy"))
		{
			AcademyLandSetLooser(chr);
			return;
		}
		if(CheckAttribute(chr, "ArenaAction"))
		{
			ArenaDuelSetLooser(chr);
			return;
		}
		if(CheckAttribute(chr, "ArenaEtapsAction"))
		{
			ArenaEtapsSetLooser(chr);
			return;
		}
		if(CheckAttribute(chr, "ArenaTournament"))
		{
			ArenaTournamentSetLooser(chr);
			return;
		}
		if(CheckAttribute(chr, "ArenaOdds"))
		{
			ArenaOddsSetLooser(chr);
			return;
		}
	}
}

void SetArenaTimeWait()
{
	int d = rand(5) + 20;
	SetTimerFunction("ArenaReGenerate", 0, 0, d);

	Log_TestInfo("Через " + d + " дней на арене сгенерируются новые соревнования.");
	AddSimpleRumourToAllNations("Поговаривают, что в Поселении Фехтовальщиков на Доминике дней через 20 начнётся очередная серия соревнований.", 5, 1);
}

void ArenaReGenerate(string qName)
{
	GenerateArena();
	Log_TestInfo("На арене сгенерировались новые соревнования.");
	AddSimpleRumourToAllNations("Я где-то слышал, что на Доминике в Поселении Фехтовальщиков недавно начались соревнования. Эх, будь я половчее - непременно попытал бы счастья там.", 5, 1);
}

void ArenaBileterGiveItems(ref chr)
{
	int d = 1;
	int i = 0;

	string sItem = "Food1";
	for(i=1; i<=5; i++)
	{
		sItem = "Food" + i;
		d = (20 / i) + rand(5);
		TakeNItems(chr, sItem, d);
	}

	for(i=1; i<=5; i++)
	{
		sItem = "potion" + i;
		d = (20 / i) + rand(5);
		TakeNItems(chr, sItem, d);
	}
}

