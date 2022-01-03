// 3. Дуэлянт
// 4. Корабль, потерпевший крушение

/////////////////////////////////////////////////////////////////////////////////
// Дуэлянт
/////////////////////////////////////////////////////////////////////////////////
void QuestDuelCheckPossibility(ref loc)
{
	if(!CheckAttribute(loc, "id") || !CheckAttribute(loc, "type")) { return; }
	if(loc.type != "town") { return; }

	if(loc.id == "Bridgetown_Plantation" || loc.id == "Pirates_town" || loc.id == "Caiman_town" || loc.id == "LeFransua_town"
	|| loc.id == "FortOrange_town" || loc.id == "LaVega_ExitTown" || loc.id == "LaVega_town" || loc.id == "PuertoPrincipe_town"
	|| loc.id == "Caiman_ExitTown") { return; }

	if(!GetCanTakeDuelQuest(loc)) { return; }
	if(LAi_IsCapturedLocation) { return; }
	if(PChar.GenerateQuestDuel.Block == true) { return; }
	if(!isDay()) { return; }
	if(drand1(100) > 20) { return; }

	GenerateQuestDuel();
}

bool GetCanTakeDuelQuest(ref loc)
{
	string sColony = "Pirates";
	if(CheckAttribute(loc, "townsack"))
	{
		sColony = loc.townsack;
	}

	if(loc.id == "SanJuan_town" && bSanJuanIsDamned)
	{
		return false;
	}

	int iNation = GetCityNation(sColony);
	if (GetNationRelation2MainCharacter(iNation) == RELATION_ENEMY && iNation != PIRATE)
	{
		return false;
	}
	else
	{
		return true;
	}

	return false;
}

void GenerateQuestDuel()
{
	int iRang = sti(PChar.rank);
	float fRandom = FRAND(1) + 1;

	float fLuck = GetCharacterSkillToOld(PChar, SKILL_FORTUNE);
	if(fLuck < 1.1) { fLuck = 1.1; }
	fLuck /= 10;

	int iMoney = iRang * 1000 * fLuck * fRandom + drand(100);
	if(iMoney < 1000) { iMoney = 1000 + drand1(500); }
	if(iMoney > 20000) { iMoney = 20000 + drand2(100); }

	int iVariant = drand1(1);
	int iRelative = drand(1);
	int iMercenary = drand2(2);
	if(iMercenary > 1) { iMercenary = 1; }

	int iCharQty = 3;
	if(iVariant == 1) { iCharQty = 4; }


	string sColony = GetCurrentTown();
	string sExitColonyLocator = QuestDuelGetExitTownLocator(sColony);

	PChar.GenerateQuestDuel.Money = iMoney;
	PChar.GenerateQuestDuel.Variant = iVariant;
	PChar.GenerateQuestDuel.Relative = iRelative;
	PChar.GenerateQuestDuel.Mercenary = iMercenary;
	PChar.GenerateQuestDuel.CharQty = iCharQty;
	PChar.GenerateQuestDuel.Colony = sColony;
	PChar.GenerateQuestDuel.ExitTownLocator = sExitColonyLocator;

	Log_TestInfo("Ген.квест Дуэлянт: Награда: " + sti(PChar.GenerateQuestDuel.Money));
	Log_TestInfo("Ген.квест Дуэлянт: Вариант: " + sti(PChar.GenerateQuestDuel.Variant));
	Log_TestInfo("Ген.квест Дуэлянт: Наймёт ли обидчик наёмника: " + sti(PChar.GenerateQuestDuel.Mercenary));
	Log_TestInfo("Ген.квест Дуэлянт: Вероятность родственников: " + sti(PChar.GenerateQuestDuel.Relative));
	Log_TestInfo("Сгенерирован квест ''Дуэлянт''. Должен подойти кто-то.");

	QuestDuelGenerateCharacters();

	string sCharacter = PChar.GenerateQuestDuel.Characters.Duelist_1;
	ref chr = CharacterFromID(sCharacter);

	string sCharacterName = chr.name + " " + chr.lastname;
	PChar.GenerateQuestDuel.DuelistFullName = sCharacterName;
	PChar.GenerateQuestDuel.DuelistName = chr.name;

	if(CheckAttribute(PChar, "GenerateQuestDuel.Characters.Wife"))
	{
		sCharacter = PChar.GenerateQuestDuel.Characters.Wife;
		chr = CharacterFromID(sCharacter);
		PChar.GenerateQuestDuel.WifeName = chr.name;
	}

	QuestDuelStart();
}

string QuestDuelGetExitTownLocator(string sColony)
{
	if(sColony == "Charles") {  return "reload1"; }
	if(sColony == "Cartahena" || sColony == "Villemstad" || sColony == "BasTer" || sColony == "Havana"
	|| sColony == "PortRoyal" || sColony == "Panama" || sColony == "Tortuga" || sColony == "PortSpein")
	{
		return "reload4";
	}

	return "reload3";
}

void QuestDuelGenerateCharacters()
{
	string sColony = GetCurrentTown();
	int iNation = sti(Colonies[FindColony(sColony)].nation);

	int iChar = 0;
	ref chr;

	string sModel, sSex, sAnimation;
	string sChar = "";
	string sCharacter = "";
	bool bEquip = true;

	int iCharQty = 6;
	for(int i = 1; i <= iCharQty; i++)
	{
		switch(i)
		{
			case 1:
				sChar = "Duelist_1";
				sCharacter = "QuestDuel_Duelist_" + rand(100000);

				switch(rand(3))
				{
					case 0: sModel = GetModelForQuestDuel(11, "citiz"); break;
					case 1: sModel = GetModelForQuestDuel(15, "shipowner"); break;
					case 2: sModel = GetModelForQuestDuel(15, "trader"); break;
					case 3: sModel = GetModelForQuestDuel(7, "usurer"); break;
				}

				sSex = "man";
				if (MOD_SKILL_ENEMY_RATE == 10 && bHardAnimations) sAnimation = "spy";
				else sAnimation = "man_fast";
				bEquip = true;
			break;

			case 2:
				sChar = "Duelist_2";
				sCharacter = "QuestDuel_Duelist_" + rand(100000);

				switch(rand(3))
				{
					case 0: sModel = GetModelForQuestDuel(11, "citiz"); break;
					case 1: sModel = GetModelForQuestDuel(15, "shipowner"); break;
					case 2: sModel = GetModelForQuestDuel(15, "trader"); break;
					case 3: sModel = GetModelForQuestDuel(7, "usurer"); break;
				}

				sSex = "man";
				if (MOD_SKILL_ENEMY_RATE == 10 && bHardAnimations) sAnimation = "spy";
				else sAnimation = "man_fast";
				bEquip = true;
			break;

			case 3:
				sChar = "Mercenary";
				sCharacter = "QuestDuel_Mercenary_" + rand(100000);
				sModel = GetModelForQuestDuel(19, "officer");
				sSex = "man";
				if (MOD_SKILL_ENEMY_RATE == 10 && bHardAnimations) sAnimation = "spy";
				else sAnimation = "man_fast";
				bEquip = true;
			break;

			case 4:
				sChar = "Wife";
				sCharacter = "QuestDuel_Wife_" + rand(100000);
				sModel = GetModelForQuestDuel(10, "Girl");
				sSex = "woman";
				sAnimation = "towngirl";
				bEquip = false;
			break;

			case 5:
				sChar = "Relative_1";
				sCharacter = "QuestDuel_Relative_" + rand(100000);
				sModel = GetModelForQuestDuel(11, "citiz");
				sSex = "man";
				if (MOD_SKILL_ENEMY_RATE == 10 && bHardAnimations) sAnimation = "spy";
				else sAnimation = "man_fast";
				bEquip = true;
			break;


			case 6:
				sChar = "Relative_2";
				sCharacter = "QuestDuel_Relative_" + rand(100000);
				sModel = GetModelForQuestDuel(11, "citiz");
				sSex = "man";
				if (MOD_SKILL_ENEMY_RATE == 10 && bHardAnimations) sAnimation = "spy";
				else sAnimation = "man_fast";
				bEquip = true;
			break;

		}

		int iRank = GetRank(PChar, 5) + MOD_SKILL_ENEMY_RATE;
		iChar = NPC_GenerateCharacter(sCharacter, sModel, sSex, sAnimation, iRank, iNation, -1, false);
		chr = GetCharacter(iChar);
		chr.id = sCharacter;
		chr.Dialog.FileName = "GenerateQuestDuel_dialog.c";
		chr.Dialog.CurrentNode = "First Time";

		if(sChar != "Wife" && sChar != "Duelist_1")
		{
    			LAi_NPC_Equip(chr, sti(chr.rank), true, true);
		}

		LAi_SetImmortal(chr, true);
		LAi_SetCitizenType(chr);

		PChar.GenerateQuestDuel.Characters.(sChar) = sCharacter;
	}

	DeleteAttribute(PChar, "GenerateQuestDuel.Models");
}

void QuestDuelStart()
{
	int iVariant = sti(PChar.GenerateQuestDuel.Variant);

	string sCharacter = "";
	ref chr;
	switch(iVariant)
	{
		case 0:
			sCharacter = PChar.GenerateQuestDuel.Characters.Duelist_1;
			chr = CharacterFromID(sCharacter);
			chr.Dialog.CurrentNode = "Duelist_1_1";

			ChangeCharacterAddressGroup(chr, PChar.location, "goto", "goto" + (rand(19)+1));

			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, PChar, "", 25.0, 1.0);
		break;

		case 1:
			sCharacter = PChar.GenerateQuestDuel.Characters.Wife;
			chr = CharacterFromID(sCharacter);
			chr.Dialog.CurrentNode = "Wife_1";
			ChangeCharacterAddressGroup(chr, PChar.location, "goto", "goto" + (rand(19)+1));

			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, PChar, "", 25.0, 1.0);

			sCharacter = PChar.GenerateQuestDuel.Characters.Duelist_1;
			chr = CharacterFromID(sCharacter);
			chr.Dialog.CurrentNode = "First Time";
			ChangeCharacterAddressGroup(chr, PChar.location, "goto", "goto" + (rand(19)+1));
		break;
	}

	PChar.quest.ClearGenerateQuestDuel.win_condition.l1 = "ExitFromLocation";
	PChar.quest.ClearGenerateQuestDuel.win_condition.l1.location = PChar.location;
	PChar.quest.ClearGenerateQuestDuel.function = "ClearGenerateQuestDuel";
}

void QuestDuelAgree()
{
	PChar.GenerateQuestDuel.Block = true;
	PChar.quest.ClearGenerateQuestDuel.over = "yes";

	string sCharacter = PChar.GenerateQuestDuel.Characters.Duelist_1;
	ref chr = CharacterFromID(sCharacter);

	string sCharacterName = PChar.GenerateQuestDuel.DuelistFullName;

	LAi_SetActorType(chr);
	LAi_ActorRunToLocation(chr, "reload", "gate_back", "none", "", "", "", -1);

	string sColony = GetCurrentTown();
	string sExitTown = sColony + "_ExitTown";

	int iMoney = sti(PChar.GenerateQuestDuel.Money);

	DeleteQuestHeader("QuestDuel");
	SetQuestHeader("QuestDuel");
	AddQuestRecord("QuestDuel", "1");
	AddQuestUserData("QuestDuel", "sSex", GetSexPhrase("ся","ась"));
	AddQuestUserData("QuestDuel", "sSex1", GetSexPhrase("ой","ая"));
	AddQuestUserData("QuestDuel", "sSex2", GetSexPhrase("к","ца"));
	AddQuestUserData("QuestDuel", "sColony", XI_ConvertString("Colony" + sColony + "Gen"));
	AddQuestUserData("QuestDuel", "sName", sCharacterName);
	AddQuestUserData("QuestDuel", "sMoney", iMoney);

	PChar.quest.QuestDuelMeeting.win_condition.l1 = "location";
	PChar.quest.QuestDuelMeeting.win_condition.l1.location = sExitTown;
	PChar.quest.QuestDuelMeeting.function = "QuestDuelMeeting";

	SetTimerFunction("QuestDuelMeetingNotLogin", 0, 0, 5);
}

void QuestDuelMeetingNotLogin(string qName)
{
	AddQuestRecord("QuestDuel", "7");
	AddQuestUserData("QuestDuel", "sSex", GetSexPhrase("","а"));
	CloseQuestHeader("QuestDuel");

	PChar.quest.QuestDuelMeeting.over = "yes";
	ClearGenerateQuestDuel("");
}

void QuestDuelWomanAgree()
{
	PChar.GenerateQuestDuel.Block = true;
	PChar.quest.ClearGenerateQuestDuel.over = "yes";

	string sCharacter = PChar.GenerateQuestDuel.Characters.Wife;
	ref chr = CharacterFromID(sCharacter);

	sCharacter = PChar.GenerateQuestDuel.Characters.Duelist_1;
	ref achr = CharacterFromID(sCharacter);
	achr.Dialog.CurrentNode = "Duelist_1_8";

	LAi_SetActorType(chr);
	LAi_ActorFollow(chr, achr, "", 25.0);
	LAi_SetActorType(achr);
	LAi_SetStayType(achr);

	LAi_SetActorType(PChar);
	LAi_ActorFollow(PChar, achr, "QuestDuelTalkWifeWithDuelist", 25.0);

	string sColony = GetCurrentTown();
	string sExitTown = sColony + "_ExitTown";

	int iMoney = sti(PChar.GenerateQuestDuel.Money);
	string sCharacterName = PChar.GenerateQuestDuel.DuelistFullName;
	DeleteQuestHeader("QuestDuel");
	SetQuestHeader("QuestDuel");
	AddQuestRecord("QuestDuel", "2");
	AddQuestUserData("QuestDuel", "sSex", GetSexPhrase("","ла"));
	AddQuestUserData("QuestDuel", "sColony", XI_ConvertString("Colony" + sColony + "Gen"));
	AddQuestUserData("QuestDuel", "sName", sCharacterName);
	AddQuestUserData("QuestDuel", "sMoney", iMoney);
}

void QuestDuelTalkWifeWithDuelist()
{
	string sCharacter = PChar.GenerateQuestDuel.Characters.Duelist_1;
	ref chr = CharacterFromID(sCharacter);

	LAi_SetActorType(chr);
	LAi_SetActorType(PChar);
	LAi_ActorWaitDialog(PChar, chr);
	LAi_ActorDialog(chr, PChar, "", 20.0, 1.0);
}

void QuestDuelWoman2Agree()
{
	PChar.quest.ClearGenerateQuestDuel.over = "yes";

	string sCharacter = PChar.GenerateQuestDuel.Characters.Duelist_1;
	ref chr = CharacterFromID(sCharacter);

	LAi_SetPlayerType(PChar);
	LAi_SetActorType(chr);
	LAi_ActorRunToLocation(chr, "reload", "gate_back", "none", "", "", "", -1);

	sCharacter = PChar.GenerateQuestDuel.Characters.Wife;
	chr = CharacterFromID(sCharacter);
	LAi_SetActorType(chr);
	LAi_ActorRunToLocation(chr, "reload", "reload7", "none", "", "", "", -1);

	string sColony = GetCurrentTown();
	string sExitTown = sColony + "_ExitTown";

	AddQuestRecord("QuestDuel", "3");
	AddQuestUserData("QuestDuel", "sSex", GetSexPhrase("ся","ась"));

	PChar.quest.QuestDuelMeeting.win_condition.l1 = "location";
	PChar.quest.QuestDuelMeeting.win_condition.l1.location = sExitTown;
	PChar.quest.QuestDuelMeeting.function = "QuestDuelMeeting";

	SetTimerFunction("QuestDuelMeetingNotLogin", 0, 0, 5);
}

void QuestDuelMeeting(string qName)
{
	PChar.quest.QuestDuelMeetingNotLogin.over = "yes";

	chrDisableReloadToLocation = true;
	InterfaceStates.Buttons.Save.enable = false;

	DeleteAllOfficersFromLocation();
	bDisableOfficers = true;

	int iMercenary = sti(PChar.GenerateQuestDuel.Mercenary);
	ref chr;
	string sCharacter = "";
	string sType = "";
	string sExitLocator = PChar.GenerateQuestDuel.ExitTownLocator;

	int iChrQty = 2;
	if(iMercenary == 1) { iChrQty = 3; }

	string sLocator = "";
	LAi_SetActorType(PChar);

	for(int i=1; i <= iChrQty; i++)
	{
		switch(i)
		{
			case 1: sType = "Duelist_1"; sLocator = "Duelist_1"; break;
			case 2: sType = "Duelist_2"; sLocator = "Duelist_2"; break;
			case 3: sType = "Mercenary"; sLocator = "Mercenary_2"; break;
		}

		sCharacter = PChar.GenerateQuestDuel.Characters.(sType);
		chr = CharacterFromID(sCharacter);
		ChangeCharacterAddressGroup(chr, PChar.location, "encdetector", "enc01");
		LAi_SetActorType(chr);

		if(i == 2)
		{
			if(iMercenary == 1)
			{
				chr.Dialog.CurrentNode = "Duelist_2_1";
			}
			else
			{
				chr.Dialog.CurrentNode = "Duelist_2_6";
			}

			LAi_ActorFollow(PChar, chr, "QuestDuelTalkMainCharacterWithDuelist", 25.0);
		}

		if(i == 1)
		{
			ChangeCharacterAddressGroup(chr, PChar.location, "reload", sExitLocator);
			LAi_ActorFollow(chr, CharacterFromID(PChar.GenerateQuestDuel.Characters.Duelist_2), "", 25.0);
		}
	}
}

void QuestDuelTalkMainCharacterWithDuelist()
{
	string sCharacter = PChar.GenerateQuestDuel.Characters.Duelist_2;
	ref chr = CharacterFromID(sCharacter);

	LAi_SetActorType(chr);
	LAi_SetActorType(PChar);
	LAi_ActorWaitDialog(PChar, chr);
	LAi_ActorDialog(chr, PChar, "", 20.0, 1.0);
}

void QuestDuelBattleWithMercenary()
{
	LAi_Fade("", "");

	LAi_type_actor_Reset(CharacterFromID(PChar.GenerateQuestDuel.Characters.Duelist_1));
	ChangeCharacterAddressGroup(CharacterFromID(PChar.GenerateQuestDuel.Characters.Duelist_1), PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
	ChangeCharacterAddressGroup(CharacterFromID(PChar.GenerateQuestDuel.Characters.Duelist_2), PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));

	LAi_SetActorType(CharacterFromID(PChar.GenerateQuestDuel.Characters.Duelist_1));
	LAi_ActorTurnToCharacter(CharacterFromID(PChar.GenerateQuestDuel.Characters.Duelist_1), PChar);

	LAi_SetActorType(CharacterFromID(PChar.GenerateQuestDuel.Characters.Duelist_2));
	LAi_ActorTurnToCharacter(CharacterFromID(PChar.GenerateQuestDuel.Characters.Duelist_2), PChar);

	string sCharacter = PChar.GenerateQuestDuel.Characters.Mercenary;
	ref chr = CharacterFromID(sCharacter);

	QuestDuelEquipCharacterSkills(chr, true);
	LAi_SetImmortal(chr, false);

	LAi_SetWarriorType(chr);
	LAi_SetPlayerType(PChar);
	LAi_SetFightMode(pchar, true);
	LAi_group_MoveCharacter(chr, "EnemyFight");
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);

	PChar.quest.QuestDuelBattleWithMercenaryWinner.win_condition.l1 = "NPC_Death";
	PChar.quest.QuestDuelBattleWithMercenaryWinner.win_condition.l1.character = chr.id;
	PChar.quest.QuestDuelBattleWithMercenaryWinner.function = "QuestDuelBattleWithMercenaryWinner";
}

void QuestDuelBattleWithMercenaryWinner(string qName)
{
	bDisableOfficers = false;

	string sCharacter = PChar.GenerateQuestDuel.Characters.Duelist_2;
	ref chr = CharacterFromID(sCharacter);
	chr.Dialog.CurrentNode = "Duelist_2_5";

	string sChar = PChar.GenerateQuestDuel.Characters.Duelist_1;
	ref achr = CharacterFromID(sChar);
	LAi_SetActorType(chr);
	LAi_SetActorType(PChar);
	LAi_ActorFollow(achr, PChar, "", 25.0);
	LAi_ActorWaitDialog(PChar, chr);
	LAi_ActorDialog(chr, PChar, "", 20.0, 1.0);

	AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", капитан " + GetNameLugger(PChar, "f") + " вызвался на дуэль за другого человека и выиграл её.", 5, 1);
}

void QuestDuelBattleWithMercenaryEnd()
{
	string sExitLocator = PChar.GenerateQuestDuel.ExitTownLocator;
	string sCharacter = PChar.GenerateQuestDuel.Characters.Duelist_2;
	ref chr = CharacterFromID(sCharacter);

	string sChar = PChar.GenerateQuestDuel.Characters.Duelist_1;
	ref achr = CharacterFromID(sChar);
	LAi_SetPlayerType(PChar);
	LAi_SetActorType(chr);
	LAi_SetActorType(achr);
	LAi_ActorRunToLocation(chr, "reload", sExitLocator, "none", "", "", "", -1);

	sCharacter = PChar.GenerateQuestDuel.Characters.Duelist_1;
	chr = CharacterFromID(sCharacter);
	chr.Dialog.CurrentNode = "Duelist_1_14";

	LAi_SetActorType(chr);
	LAi_SetActorType(PChar);
	LAi_ActorWaitDialog(PChar, chr);
	LAi_ActorDialog(chr, PChar, "", 20.0, 1.0);
}

void QuestDuelBattleWithMercenaryHappyEnd()
{
	chrDisableReloadToLocation = false;
	InterfaceStates.Buttons.Save.enable = true;

	string sExitLocator = PChar.GenerateQuestDuel.ExitTownLocator;
	string sCharacter = PChar.GenerateQuestDuel.Characters.Duelist_1;
	ref chr = CharacterFromID(sCharacter);

	LAi_SetPlayerType(PChar);
	LAi_SetActorType(chr);
	LAi_ActorRunToLocation(chr, "reload", sExitLocator, "none", "", "", "", -1);

	AddMoneyToCharacter(PChar, sti(PChar.GenerateQuestDuel.Money));
	ChangeCharacterReputation(PChar, 5);

	AddQuestRecord("QuestDuel", "4");
	AddQuestUserData("QuestDuel", "sSex", GetSexPhrase("","а"));
	CloseQuestHeader("QuestDuel");

	pchar.questTemp.duelcount = sti(pchar.questTemp.duelcount) + 1;
	if(sti(pchar.questTemp.duelcount) >= 5) UnlockAchievement("AchDuelyant", 1);
	if(sti(pchar.questTemp.duelcount) >= 10) UnlockAchievement("AchDuelyant", 2);
	if(sti(pchar.questTemp.duelcount) >= 20) UnlockAchievement("AchDuelyant", 3);

	AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", капитан " + GetNameLugger(PChar, "f") + " вызвался на дуэль за другого человека и выиграл её.", 5, 1);

	PChar.quest.ClearGenerateQuestDuel.win_condition.l1 = "ExitFromLocation";
	PChar.quest.ClearGenerateQuestDuel.win_condition.l1.location = PChar.location;
	PChar.quest.ClearGenerateQuestDuel.function = "ClearGenerateQuestDuel";
}

void QuestDuelBattleWithDuelist()
{
	LAi_Fade("", "");

	LAi_type_actor_Reset(CharacterFromID(PChar.GenerateQuestDuel.Characters.Duelist_1));
	ChangeCharacterAddressGroup(CharacterFromID(PChar.GenerateQuestDuel.Characters.Duelist_1), PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));

	LAi_SetActorType(CharacterFromID(PChar.GenerateQuestDuel.Characters.Duelist_1));
	LAi_ActorTurnToCharacter(CharacterFromID(PChar.GenerateQuestDuel.Characters.Duelist_1), PChar);

	string sCharacter = PChar.GenerateQuestDuel.Characters.Duelist_2;
	ref chr = CharacterFromID(sCharacter);
	QuestDuelEquipCharacterSkills(chr, false);

	LAi_SetImmortal(chr, false);

	LAi_SetWarriorType(chr);
	LAi_SetPlayerType(PChar);
	LAi_SetFightMode(pchar, true);
	LAi_group_MoveCharacter(chr, "EnemyFight");
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);

	PChar.quest.QuestDuelBattleWithDuelistWinner.win_condition.l1 = "NPC_Death";
	PChar.quest.QuestDuelBattleWithDuelistWinner.win_condition.l1.character = chr.id;
	PChar.quest.QuestDuelBattleWithDuelistWinner.function = "QuestDuelBattleWithDuelistWinner";
}

void QuestDuelEquipCharacterSkills(ref chr, bool bMercenary)
{
	float fFencing = 1.0;
	float fFencingLight = 1.0;
	float fFencingHeavy = 1.0;
	float fPistol = 1.0;

	if(bMercenary)
	{
		fFencing = GetCharacterSkill(PChar, SKILL_FENCING) + 30;
		fFencingLight = GetCharacterSkill(PChar, SKILL_F_LIGHT) + 30;
		fFencingHeavy = GetCharacterSkill(PChar, SKILL_F_HEAVY) + 30;
		fPistol = GetCharacterSkill(PChar, SKILL_PISTOL) + 40;
	}
	else
	{
		fFencing = GetCharacterSkill(PChar, SKILL_FENCING) - 30;
		fFencingLight = GetCharacterSkill(PChar, SKILL_F_LIGHT) - 30;
		fFencingHeavy = GetCharacterSkill(PChar, SKILL_F_HEAVY) - 30;
		fPistol = GetCharacterSkill(PChar, SKILL_PISTOL) - 45;
	}

	if(fFencing < 20) { fFencing = 20; }
	if(fFencing > 100) { fFencing = 100; }

	if(fFencingLight < 20) { fFencingLight = 20; }
	if(fFencingLight > 100) { fFencingLight = 100; }

	if(fFencingHeavy < 20) { fFencingHeavy = 20; }
	if(fFencingHeavy > 100) { fFencingHeavy = 100; }

	if(fPistol < 20) { fPistol = 20; }
	if(fPistol > 100) { fPistol = 100; }

	chr.skill.Fencing = fFencing;
	chr.skill.FencingHeavy = fFencingHeavy;
	chr.skill.FencingLight = fFencingLight;
	chr.skill.Pistol = fPistol;
	if (bHardBoss) chr.AlwaysReload = true;//перезарядка независимо от Дозарядки
}

void QuestDuelBattleWithDuelistWinner(string qName)
{
	string sCharacter = PChar.GenerateQuestDuel.Characters.Duelist_1;
	ref chr = CharacterFromID(sCharacter);
	chr.Dialog.CurrentNode = "Duelist_1_16";

	LAi_SetActorType(chr);
	LAi_SetActorType(PChar);
	LAi_ActorWaitDialog(PChar, chr);
	LAi_ActorDialog(chr, PChar, "", 20.0, 1.0);
}

void QuestDuelBattleWithDuelistHappyEnd()
{
	chrDisableReloadToLocation = false;
	InterfaceStates.Buttons.Save.enable = true;

	string sCharacter = PChar.GenerateQuestDuel.Characters.Duelist_1;
	ref chr = CharacterFromID(sCharacter);

	string sExitLocator = PChar.GenerateQuestDuel.ExitTownLocator;

	LAi_SetPlayerType(PChar);
	LAi_SetActorType(chr);
	LAi_ActorRunToLocation(chr, "reload", sExitLocator, "none", "", "", "", -1);

	AddMoneyToCharacter(PChar, sti(PChar.GenerateQuestDuel.Money));
	ChangeCharacterReputation(PChar, 5);

	AddQuestRecord("QuestDuel", "5");
	AddQuestUserData("QuestDuel", "sSex", GetSexPhrase("","а"));
	CloseQuestHeader("QuestDuel");

	pchar.questTemp.duelcount = sti(pchar.questTemp.duelcount) + 1;
	if(sti(pchar.questTemp.duelcount) >= 5) UnlockAchievement("AchDuelyant", 1);
	if(sti(pchar.questTemp.duelcount) >= 10) UnlockAchievement("AchDuelyant", 2);
	if(sti(pchar.questTemp.duelcount) >= 20) UnlockAchievement("AchDuelyant", 3);

	if(sti(PChar.GenerateQuestDuel.Mercenary) == 0 && sti(PChar.GenerateQuestDuel.Relative) == 1)
	{
		QuestDuelBattleWithRelativeRevengePrepare();
	}
	else
	{
		bDisableOfficers = false;
		PChar.quest.ClearGenerateQuestDuel.win_condition.l1 = "ExitFromLocation";
		PChar.quest.ClearGenerateQuestDuel.win_condition.l1.location = PChar.location;
		PChar.quest.ClearGenerateQuestDuel.function = "ClearGenerateQuestDuel";
	}

	AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", капитан " + GetNameLugger(PChar, "f") + " вызвался на дуэль за другого человека и выиграл её.", 5, 1);
}

void QuestDuelBattleWithRelativeRevengePrepare()
{
	chrDisableReloadToLocation = true;

	ref chr;
	string sType = "";
	string sCharacter = "";

	string sExitLocator = PChar.GenerateQuestDuel.ExitTownLocator;
	for(int i=1; i <= 2; i++)
	{
		sType = "Relative_" + i;
		sCharacter = PChar.GenerateQuestDuel.Characters.(sType);
		chr = CharacterFromID(sCharacter);

		ChangeCharacterAddressGroup(chr, PChar.location, "reload", sExitLocator);
		chr.Dialog.CurrentNode = "Relative_1";

		LAi_SetActorType(chr);
		LAi_ActorFollow(chr, PChar, "", 25.0);
	}

	LAi_SetActorType(chr);
	LAi_ActorDialog(chr, PChar, "", 20.0, 1.0);
}

void QuestDuelBattleWithRelativeRevenge()
{
	string sType = "";
	string sCharacter = "";
	ref chr;

	for(int i=1; i <= 2; i++)
	{
		sType = "Relative_" + i;
		sCharacter = PChar.GenerateQuestDuel.Characters.(sType);
		chr = CharacterFromID(sCharacter);

		QuestDuelEquipCharacterSkills(chr, false);
		LAi_SetWarriorType(chr);
		LAi_SetImmortal(chr, false);

		if(i == 1)
		{
			if (!GetCharacterItem(pchar, "map_part1") || !GetCharacterItem(pchar, "map_part2"))
			{
				if (!GetCharacterItem(pchar, "map_part1")) 	GiveItem2Character(chr, "map_part1");
				else 										GiveItem2Character(chr, "map_part2");
			}
			else
			{
				TakeNItems(chr, "QuestDuelNotice", 1);
			}
			chr.SaveItemsForDead = true;
		}

		sType = "l" + i;
		PChar.quest.QuestDuelBattleWithRelativeRevengeWinner.win_condition.(sType) = "NPC_Death";
		PChar.quest.QuestDuelBattleWithRelativeRevengeWinner.win_condition.(sType).character = chr.id;

		LAi_group_MoveCharacter(chr, "EnemyFight");
	}

	LAi_SetPlayerType(PChar);
	LAi_group_SetHearRadius("EnemyFight", 100.0);
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_SetFightMode(PChar, true);

	PChar.quest.QuestDuelBattleWithRelativeRevengeWinner.function = "QuestDuelBattleWithRelativeRevengeWinner";
}

void QuestDuelBattleWithRelativeRevengeWinner(string qName)
{
	bDisableOfficers = false;
	chrDisableReloadToLocation = false;
	InterfaceStates.Buttons.Save.enable = true;
	AddQuestRecord("QuestDuel", "6");
	AddQuestUserData("QuestDuel", "sSex", GetSexPhrase("","а"));
	AddQuestUserData("QuestDuel", "sSex1", GetSexPhrase("ся","ась"));

	PChar.quest.ClearGenerateQuestDuel.win_condition.l1 = "ExitFromLocation";
	PChar.quest.ClearGenerateQuestDuel.win_condition.l1.location = PChar.location;
	PChar.quest.ClearGenerateQuestDuel.function = "ClearGenerateQuestDuel";
}

void QuestDuelManCancel()
{
	PChar.GenerateQuestDuel.Block = true;

	string sCharacter = PChar.GenerateQuestDuel.Characters.Duelist_1;
	ref chr = CharacterFromID(sCharacter);

	LAi_SetActorType(chr);
	LAi_ActorRunToLocation(chr, "reload", "gate_back", "none", "", "", "", -1);

	PChar.quest.ClearGenerateQuestDuel.win_condition.l1 = "ExitFromLocation";
	PChar.quest.ClearGenerateQuestDuel.win_condition.l1.location = PChar.location;
	PChar.quest.ClearGenerateQuestDuel.function = "ClearGenerateQuestDuel";
}

void QuestDuelWomanCancel()
{
	PChar.GenerateQuestDuel.Block = true;

	string sCharacter = PChar.GenerateQuestDuel.Characters.Wife;
	ref chr = CharacterFromID(sCharacter);
	LAi_SetActorType(chr);
	LAi_ActorRunToLocation(chr, "reload", "reload7", "none", "", "", "", -1);

	sCharacter = PChar.GenerateQuestDuel.Characters.Duelist_1;
	chr = CharacterFromID(sCharacter);
	LAi_SetActorType(chr);
	LAi_ActorRunToLocation(chr, "reload", "gate_back", "none", "", "", "", -1);

	PChar.quest.ClearGenerateQuestDuel.win_condition.l1 = "ExitFromLocation";
	PChar.quest.ClearGenerateQuestDuel.win_condition.l1.location = PChar.location;
	PChar.quest.ClearGenerateQuestDuel.function = "ClearGenerateQuestDuel";
}

void ClearGenerateQuestDuel(string qName)
{
	int iCharQty = sti(PChar.GenerateQuestDuel.CharQty);
	string sType = "";
	string sCharacter = "";
	ref chr;

	for(int i = 1; i <= 6; i++)
	{
		switch(i)
		{
			case 1: sType = "Duelist_1"; break;
			case 2: sType = "Duelist_2"; break;
			case 3: sType = "Mercenary"; break;
			case 4: sType = "Wife"; break;
			case 5: sType = "Relative_1"; break;
			case 6: sType = "Relative_2"; break;
		}

		sCharacter = PChar.GenerateQuestDuel.Characters.(sType);

		if(GetCharacterIndex(sCharacter) == -1)
		{
			continue;
		}

		chr = CharacterFromID(sCharacter);
		chr.LifeDay = 0; //LAi_KillCharacter(chr);
	}

	if(CheckAttribute(PChar, "GenerateQuestDuel.Money")) 		{ DeleteAttribute(PChar, "GenerateQuestDuel.Money"); }
	if(CheckAttribute(PChar, "GenerateQuestDuel.Variant")) 		{ DeleteAttribute(PChar, "GenerateQuestDuel.Variant"); }
	if(CheckAttribute(PChar, "GenerateQuestDuel.Relative")) 	{ DeleteAttribute(PChar, "GenerateQuestDuel.Relative"); }
	if(CheckAttribute(PChar, "GenerateQuestDuel.Mercenary")) 	{ DeleteAttribute(PChar, "GenerateQuestDuel.Mercenary"); }
	if(CheckAttribute(PChar, "GenerateQuestDuel.CharQty")) 		{ DeleteAttribute(PChar, "GenerateQuestDuel.CharQty"); }
	if(CheckAttribute(PChar, "GenerateQuestDuel.Colony")) 		{ DeleteAttribute(PChar, "GenerateQuestDuel.Colony"); }
	if(CheckAttribute(PChar, "GenerateQuestDuel.Duelist_1")) 	{ DeleteAttribute(PChar, "GenerateQuestDuel.Duelist_1"); }
	if(CheckAttribute(PChar, "GenerateQuestDuel.Duelist_2")) 	{ DeleteAttribute(PChar, "GenerateQuestDuel.Duelist_2"); }
	if(CheckAttribute(PChar, "GenerateQuestDuel.Wife")) 		{ DeleteAttribute(PChar, "GenerateQuestDuel.Wife"); }
	if(CheckAttribute(PChar, "GenerateQuestDuel.Mercenary")) 	{ DeleteAttribute(PChar, "GenerateQuestDuel.Mercenary"); }
	if(CheckAttribute(PChar, "GenerateQuestDuel.Relative_1")) 	{ DeleteAttribute(PChar, "GenerateQuestDuel.Relative_1"); }
	if(CheckAttribute(PChar, "GenerateQuestDuel.Relative_2")) 	{ DeleteAttribute(PChar, "GenerateQuestDuel.Relative_2"); }
	if(CheckAttribute(PChar, "GenerateQuestDuel.DuelistFullName")) 	{ DeleteAttribute(PChar, "GenerateQuestDuel.DuelistFullName"); }
	if(CheckAttribute(PChar, "GenerateQuestDuel.DuelistName")) 	{ DeleteAttribute(PChar, "GenerateQuestDuel.DuelistName"); }
	if(CheckAttribute(PChar, "GenerateQuestDuel.WifeName")) 	{ DeleteAttribute(PChar, "GenerateQuestDuel.WifeName"); }
	if(CheckAttribute(PChar, "GenerateQuestDuel.ExitTownLocator")) 	{ DeleteAttribute(PChar, "GenerateQuestDuel.ExitTownLocator"); }

	int iTime = 5 + rand(3);
	SetTimerFunction("GenerateQuestDuelBlockReset", 0, 0, iTime);

	Log_TestInfo("Удаляем квест ''Дуэлянт''.");
}

void GenerateQuestDuelBlockReset(string qName)
{
	PChar.GenerateQuestDuel.Block = false;
	Log_TestInfo("Временная блокировка на ген.квест ''Дуэлянт'' снята.");
}

string GetModelForQuestDuel(int iQty, string sType)
{
	string sModel = sType + "_1";

	int iRand = rand(iQty)+1;
	int i = 0;
	for(i=1; i <= (iQty+1); i++)
	{
		if(i == iRand)
		{
			sModel = sType + "_" + i;

			if(!CanUseModelForQuestDuel(sModel))
			{
				iRand = rand(iQty)+1;
				i = 0;
				continue;
			}
			else
			{
				PChar.GenerateQuestDuel.Models.(sModel) = true;
				return sModel;
			}
		}
	}

	return sModel;
}

bool CanUseModelForQuestDuel(string sModel)
{
	if(CheckAttribute(PChar, "GenerateQuestDuel.Models." + sModel))
	{
		return false;
	}
	else
	{
		return true;
	}

	return false;
}


/////////////////////////////////////////////////////////////////////////////////
// Потерпевший крушение
/////////////////////////////////////////////////////////////////////////////////
bool GetCanShipWreck(aref loc)
{
	if(!CheckAttribute(loc, "type")) { return false; }
	if(loc.type != "town" && loc.type != "seashore") { return false; }

	bool bCan = sti(PChar.GenerateShipWreck.Block);
	if(bCan) { return false; }
	if(rand(100) < 90) { return false; }

	return true;
}

void GenerateShipWreck(aref loc)
{
	bool bCan = GetCanShipWreck(loc);
	// if(!bCan && !bBettaTestMode) { return; }
	if(!bCan) { return; }
	PChar.GenerateShipWreck.Block = true;

	Log_TestInfo("Сгенерирован квест 'Кораблекрушение'. На карте подплывёт корабль.");

	SetTimerFunction("ShipWreckTimeActionEnd", 0, 0, 30);

	int iMaxGoods = 1000;
	int iClass = 7;
	int iRank = GetRank(PChar, 0);

	if(iRank < 4) 					{ iClass = 6; iMaxGoods = 250; }
	if(iRank >= 5 && iRank < 10) 	{ iClass = 5; iMaxGoods = 500; }
	if(iRank >= 10 && iRank < 15) 	{ iClass = 4; iMaxGoods = 500; }
	if(iRank >= 15 && iRank < 20) 	{ iClass = 3; iMaxGoods = 750; }
	if(iRank >= 20 && iRank < 30) 	{ iClass = 2; iMaxGoods = 1000; }
	if(iRank >= 30) 				{ iClass = 1; iMaxGoods = 1500; }

 	iClass -= rand(1);
 	if(iClass < 1) { iClass = 1; }

	PChar.GenerateShipWreck.MaxGoods = iMaxGoods;

	int iShipType = FindShipFromClass(iClass, "All");
	int iNation = PIRATE;

	string sModel = "officer_1";
	switch(rand(2))
	{
		case 0: sModel = "officer_" + (rand(63)+1); break;
		case 1: sModel = "citiz_" + (rand(11)+1); break;
		case 2: sModel = "trader_" + (rand(15)+1); break;
		case 3: sModel = "pirate_" + (rand(24)+1); break;
	}

	int iCharacter = NPC_GenerateCharacter("ShipWreck_" + rand(10000), sModel, "man", "man", GetRank(PChar, 5) + MOD_SKILL_ENEMY_RATE, iNation, -1, true);
	ref chr = GetCharacter(iCharacter);
	chr.Ship.Type = GenerateShip(iShipType, 0);
	chr.greeting = "Gr_AllowToDump";
	chr.sex = "man";
	chr.Dialog.Filename = "DamnedDestiny\ShipWreck_dialog.c";
	chr.Dialog.CurrentNode = "First Time";
	chr.DeckDialogNode = "1";
	chr.DontRansackCaptain = true;
	chr.AlwaysFriend = true;
	chr.ShipEnemyDisable = true;
	chr.ShipTaskLock = true;
	chr.ShipWreck = true;
	chr.Abordage.Enable = false;
	chr.DontCheckFlag = true;
	SetRandomNameToCharacter(chr);
	SetRandomNameToShip(chr);
	SetBaseShipData(chr);
	SetCrewQuantity(chr, (GetMaxCrewQuantity(chr) / 4 + rand(10)));
	SetFantomParamFromRank(chr, GetRank(PChar, 5) + MOD_SKILL_ENEMY_RATE, true);
	chr.ship.HP = sti(chr.ship.HP) / 4;

	PChar.GenerateShipWreck.ShipWreckIdx = sti(chr.Ship.Type);
	PChar.GenerateShipWreck.ShipWreckName = chr.Ship.Name;
	PChar.GenerateShipWreck.ShipHP = sti(chr.ship.HP);

	int iMast = 0;
	int iMastQty = 4;
	string sMast = "";
	for(int m=1; m <= iMastQty; m++)
	{
		if(rand(10) > 3)
		{
			sMast = "mast" + m;
			chr.ship.masts.(sMast) = true;
		}
	}

	sMast = "mast" + rand(2)+2;
	if(CheckAttribute(chr, "ship.masts." + iMastQty))
	{
		DeleteAttribute(chr, "ship.masts." + iMastQty);
	}

	int iGoods = rand(4) + 2;
	int iGood = 0;
	int iDel = 0;
	int qty = 0;

	for(int i = 1; i <= iGoods; i++)
	{
		switch(i)
		{
			case 1: iGood = GOOD_GOLD; break;
			case 2: iGood = GOOD_SILVER; break;
			case 3: iGood = GOOD_EBONY; break;
			case 4: iGood = GOOD_MAHOGANY; break;
			case 5: iGood = GOOD_COFFEE; break;
			case 6: iGood = GOOD_TOBACCO; break;
		}

		iDel = 8 - i;
		qty = GetCharacterFreeSpace(chr, iGood) / iDel;
		AddCharacterGoodsSimple(chr, iGood, qty);
	}

	iRank = GetRank(PChar, 0) * 150;

	float fLeaderShip = GetCharacterSkillToOld(PChar, SKILL_LEADERSHIP) * 290;
	float fCommerce = GetCharacterSkillToOld(PChar, SKILL_COMMERCE) * 335;
	float fLuck = GetCharacterSkillToOld(PChar, SKILL_FORTUNE) * 380;

	int iMoney = iRank + fLeaderShip + fCommerce + fLuck + rand(500);
	if(iMoney < 1000) 	{ iMoney = 1000; }
	if(iMoney > 50000) 	{ iMoney = 50000; }

	int iRand = rand(2);
	if(iRand > 1) { iRand = 1; chr.DeckDialogNode = "1"; }

	int iCrewQty = 0;
	if(GetCrewQuantity(PChar) > 10)	{ iCrewQty = GetCrewQuantity(PChar) / 100; }
	if(iCrewQty > 10) { iCrewQty = 10; }

	PChar.GenerateShipWreck.MyCrewQty = iCrewQty;

	iCrewQty = 0;
	if(GetCrewQuantity(chr) > 10)	{ iCrewQty = GetCrewQuantity(chr) / 70; }
	if(iCrewQty > 10) { iCrewQty = 10; }

	sModel = "officer_1";
	switch(rand(1))
	{
		case 0: sModel = "officer_" + (rand(63)+1); break;
		case 1: sModel = "citiz_" + (rand(11)+1); break;
	}

	PChar.GenerateShipWreck.ShipCrewQty = iCrewQty;
	PChar.GenerateShipWreck.Situation = iRand;
	PChar.GenerateShipWreck.Money = iMoney;
	PChar.GenerateShipWreck.CharacterIdx = iCharacter;
	PChar.GenerateShipWreck.CharacterID = chr.id;
	PChar.GenerateShipWreck.ModelHelper = sModel;

	PChar.quest.ShipWreckLoginToWorldMap.win_condition.l1 = "MapEnter";
	PChar.quest.ShipWreckLoginToWorldMap.function = "ShipWreckLoginToWorldMap";

	if(iRand == 0)
	{
		ShipWreckBandInit();
	}
}

void ShipWreckLoginToWorldMap(string qName)
{
	if(!CheckAttribute(PChar, "GenerateShipWreck.CharacterID"))
	{
		return;
	}

	if(GetCharacterIndex(PChar.GenerateShipWreck.CharacterID) == -1)
	{
		return;
	}

	ref chr = CharacterFromID(PChar.GenerateShipWreck.CharacterID);
	chr.LifeDay = 10;
	SaveCurrentNpcQuestDateParam(chr, "LifeTimeCreate");

	string sGroup = chr.id;
	Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup, "trade");
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sGroup);
	Group_SetGroupCommander(sGroup, sGroup);

	chr.mapEnc.type = "warrior";
	chr.mapEnc.worldMapShip = "ranger";
	chr.mapEnc.Name = "сильно потрепавшийся неизвестный корабль прямо по курсу";

	//Map_CreateWarrior("", sGroup, 30);
	Map_CreateSlowMerch("",sGroup, 30);
}

void ShipWreckInSea(ref chr)
{
	chr.nation = sti(PChar.nation);
	Map_ReleaseQuestEncounter(chr.id);

	PChar.quest.ShipWreckInSeaFailedSink.win_condition.l1 = "Group_Death";
	PChar.quest.ShipWreckInSeaFailedSink.win_condition.l1.group = chr.id;
	PChar.quest.ShipWreckInSeaFailedSink.function = "ShipWreckInSeaFailedSink";

	/*PChar.quest.ShipWreckTimeActionEnd.win_condition.l1 = "ExitFromLocation";
	PChar.quest.ShipWreckTimeActionEnd.win_condition.l1.Location = PChar.location;
	PChar.quest.ShipWreckTimeActionEnd.function = "ShipWreckTimeActionEnd";

	PChar.quest.ShipWreckInSeaExitFromSea.win_condition.l1 = "MapEnter";
	PChar.quest.ShipWreckInSeaExitFromSea.function = "ShipWreckInSeaExitFromSea";

	PChar.quest.ShipWreckInSeaExitFromSea.win_condition.l1 = "ExitFromLocation";
	PChar.quest.ShipWreckInSeaExitFromSea.win_condition.l1.Location = PChar.location;
	PChar.quest.ShipWreckInSeaExitFromSea.function = "ShipWreckInSeaExitFromSea";*/
}

void ShipWreckInSeaFailedSink(string qName)
{
	Log_TestInfo("Убили крушённый корабль.");

	ChangeCharacterReputation(PChar, -15);
	AddSimpleRumourToAllNations(LinkRandPhrase("Слыхали", "Знаете ли вы", "Невероятно") + ", некий капитан " + GetNameLugger(PChar, "f") + " встретил в море потерпевший крушение корабль. Но вместо того, чтобы оказать помощь, он его утопил!", 5, 1);

	PChar.quest.ShipWreckInTown.over = "yes";
	PChar.GenerateShipWreck.Block = true;
	SetTimerFunction("ShipWreckResetBlock", 0, 0, 35);

	if(CheckAttribute(PChar, "GenerateShipWreck.SailorID"))
	{
		if(GetCharacterIndex(PChar.GenerateShipWreck.SailorID) != -1)
		{
			string sCharacter = PChar.GenerateShipWreck.SailorID;
			ref chr = CharacterFromID(sCharacter);
			chr.LifeDay = 0;

			if(CheckPassengerInCharacter(PChar, sCharacter))
			{
				RemovePassenger(PChar, chr);
			}
		}
	}

	PChar.GenerateShipWreck.State = "none";

	CloseQuestHeader("ShipWreck");
	ClearShipWreckQuest();
}

/////////////////////////////////////////////////////////////////////////
// ПЕРВЫЙ ВАРИАНТ - ПРОСЬБА О ПОМОЩИ
/////////////////////////////////////////////////////////////////////////
void ShipWreckInSeaWait()
{
	LAi_Fade("", "");

	chrDisableReloadToLocation = true;

	string sModel = PChar.GenerateShipWreck.ModelHelper;
	int iRank = GetRank(PChar, 5) + MOD_SKILL_ENEMY_RATE;
	ref chr = GetCharacter(NPC_GenerateCharacter("ShipWreckSailor_" + rand(30000), sModel, "man", "man", iRank, PIRATE, -1, true));
	chr.greeting = "Gr_AllowToDump";
	chr.Dialog.Filename = "DamnedDestiny\ShipWreck_dialog.c";
	chr.Dialog.CurrentNode = "5";
	chr.ShipWrick = true;
	LAi_SetImmortal(chr, true);

	SetFantomParamFromRank(chr, iRank, true);

	ChangeCharacterAddressGroup(chr, PChar.location, "reload", "reload1");
	SetDialogCharacter2Character(PChar, chr, 15.0, false);

	PChar.GenerateShipWreck.SailorID = chr.id;

	string sCharacter = PChar.GenerateShipWreck.CharacterID;
	LAi_SetActorType(CharacterFromID(sCharacter));
	LAi_ActorTurnToCharacter(CharacterFromID(sCharacter), chr);
}

void ShipWreckInSeaWaitEnd()
{
	string sCharacter = PChar.GenerateShipWreck.SailorID;
	ref chr = CharacterFromID(sCharacter);
	chr.Dialog.CurrentNode = "10";

	LAi_SetActorType(chr);
	LAi_ActorGoToLocation(chr, "reload", "reload1", "none", "", "", "", -1);

	SetCharacterRemovable(chr, false);
	AddPassenger(PChar, chr, 0);

	sCharacter = PChar.GenerateShipWreck.CharacterID;
	chr = CharacterFromID(sCharacter);
	chr.DeckDialogNode = "First Time";
	chr.Dialog.CurrentNode = "6";

	SetDialogCharacter2Character(PChar, chr, 15.0, false);

	PChar.quest.ShipWreckInTown.win_condition.l1 = "Location_Type";
	PChar.quest.ShipWreckInTown.win_condition.l1.location_type = "town";
	PChar.quest.ShipWreckInTown.function = "ShipWreckInTown";
}

void ShipWreckInSeaCancel()
{
	chrDisableReloadToLocation = false;
	ChangeCharacterReputation(PChar, -10);
	PChar.quest.ShipWreckInSeaFailedSink.over = "yes";
	PChar.quest.ShipWreckTimeActionEnd.over = "yes";

	string sCharacter = PChar.GenerateShipWreck.CharacterID;
	ref chr = CharacterFromID(sCharacter);
	chr.Killer.Status = KILL_BY_ABORDAGE;
	chr.Killer.Index = 0;
	LAi_SetCurHP(chr, 0.0);
	LAi_SetActorType(chr);
	LAi_ActorGoToLocation(chr, "reload", "reload1", "none", "", "", "", -1);

	PChar.GenerateShipWreck.Block = true;
	SetTimerFunction("ShipWreckResetBlock", 0, 0, 35);
	ClearShipWreckQuest();
}

void ShipWreckInSeaWaitEndToSea()
{
	PChar.quest.ShipWreckTimeActionEnd.over = "yes";
	chrDisableReloadToLocation = false;

	string sCharacter = PChar.GenerateShipWreck.CharacterID;
	ref chr = CharacterFromID(sCharacter);

	DeleteQuestHeader("ShipWreck");

	SetQuestHeader("ShipWreck");
	AddQuestRecord("ShipWreck", "1");
	AddQuestUserData("ShipWreck", "sCharacter", GetNameLugger(chr, "f"));
	AddQuestUserData("ShipWreck", "sShipName", chr.Ship.Name);
	AddQuestUserData("ShipWreck", "sMoney", sti(PChar.GenerateShipWreck.Money));

	LAi_SetWarriorType(chr);
}

void ShipWreckBattleWithSailor()
{
	chrDisableReloadToLocation = true;

	string sCharacter = PChar.GenerateShipWreck.SailorID;
	ref chr = CharacterFromID(sCharacter);
	RemovePassenger(PChar, chr);
	chr.LifeDay = 0;
	chr.SaveItemsForDead = true;
	chr.ShipWrickDel = true;
	chr.money = sti(PChar.GenerateShipWreck.Money) + rand(1000);

	LAi_SetImmortal(chr, false);

	LAi_group_MoveCharacter(chr, "EnemyFight");
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);

	PChar.quest.ShipWreckBattleWithSailorWinner.win_condition.l1 = "NPC_Death";
	PChar.quest.ShipWreckBattleWithSailorWinner.win_condition.l1.character = chr.id;
	PChar.quest.ShipWreckBattleWithSailorWinner.function = "ShipWreckBattleWithSailorWinner";

	LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
}

void ShipWreckBattleWithSailorWinner(string qName)
{
	AddQuestRecord("ShipWreck", "2");
	chrDisableReloadToLocation = false;

	string sCharacter = PChar.GenerateShipWreck.CharacterID;
	ref chr = CharacterFromID(sCharacter);
	chr.Abordage.Enable = true;

	DeleteAttribute(chr, "AlwaysFriend");
	DeleteAttribute(chr, "ShipEnemyDisable");

	PChar.GenerateShipWreck.State = "CanAbordage";
	LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], true);

	SetQuestFunction("ShipWreckBattleWithSailorOut", "ShipWreckBattleWithSailorOut", "efl", PChar.location);

	PChar.quest.ShipWreckCapture.win_condition.l1 = "Character_Capture";
	PChar.quest.ShipWreckCapture.win_condition.l1.character = chr.id;
	PChar.quest.ShipWreckCapture.function = "ShipWreckCapture";

	PChar.quest.ShipWreckNoCapture.win_condition.l1 = "MapEnter";
	PChar.quest.ShipWreckNoCapture.function = "ShipWreckNoCapture";
}

void ShipWreckNoCapture(string qName)
{
	PChar.GenerateShipWreck.State = "none";
	if(CheckAttribute(PChar, "quest.ShipWreckCapture")) { DeleteAttribute(PChar, "quest.ShipWreckCapture"); }
	if(CheckAttribute(PChar, "quest.ShipWreckNoCapture")) { DeleteAttribute(PChar, "quest.ShipWreckNoCapture"); }
	CloseQuestHeader("ShipWreck");
}

void ShipWreckCapture(string qName)
{
	AddQuestRecord("ShipWreck", "3");
	CloseQuestHeader("ShipWreck");

	PChar.GenerateShipWreck.State = "none";
	PChar.GenerateShipWreck.Block = true;
	SetTimerFunction("ShipWreckResetBlock", 0, 0, 35);

	ClearShipWreckQuest();
}

void ShipWreckBattleWithSailorOut(string qName)
{
	string sCharacter = PChar.GenerateShipWreck.SailorID;
	ChangeCharacterAddress(CharacterFromID(sCharacter), "None", "");
	LAi_KillCharacter(CharacterFromID(sCharacter));
}

void ShipWreckInTown(string qName)
{
	chrDisableReloadToLocation = true;

	string sCharacter = PChar.GenerateShipWreck.SailorID;
	ref chr = CharacterFromID(sCharacter);
	chr.Dialog.CurrentNode = "20";
	RemovePassenger(PChar, chr);

	string sLocator = "reload1_back";
	if(PChar.location == "Pirates_town" || PChar.location == "PuertoPrincipe_town" || PChar.location == "LaVega_town" || PChar.location == "LeFransua_town" || PChar.location == "FortOrange_town")
	{
		sLocator = "reload1";
	}

	ChangeCharacterAddressGroup(chr, PChar.location, "reload", sLocator);
	SetDialogCharacter2Character(PChar, chr, 2.0, true);
}

void ShipWreckInTownSuccess()
{
	LAi_SetPlayerType(PChar);
	chrDisableReloadToLocation = false;

	string sCharacter = PChar.GenerateShipWreck.SailorID;
	ref chr = CharacterFromID(sCharacter);
	chr.LifeDay = 0;

	string sLocator = "reload10";
	if(PChar.location == "Pirates_town" || PChar.location == "PuertoPrincipe_town" || PChar.location == "LaVega_town" || PChar.location == "LeFransua_town")
	{
		sLocator = "reload5";
	}

	LAi_SetActorType(chr);
	LAi_ActorRunToLocation(chr, "reload", sLocator, "none", "", "", "", -1);

	int iMoney = sti(PChar.GenerateShipWreck.Money);
	AddMoneyToCharacter(PChar, iMoney);
	ChangeCharacterReputation(PChar, 10);

	AddQuestRecord("ShipWreck", "4");
	CloseQuestHeader("ShipWreck");

	PChar.GenerateShipWreck.Block = true;
	SetTimerFunction("ShipWreckResetBlock", 0, 0, 35);

	if(CheckAttribute(PChar, "quest.ShipWreckInSeaFailedSink"))
	{
		DeleteAttribute(PChar, "quest.ShipWreckInSeaFailedSink");
	}

	ClearShipWreckQuest();
}

/////////////////////////////////////////////////////////////////////////
// ВТОРОЙ ВАРИАНТ - НЕПРИВЕТЛИВЫЕ РОБЯТЫ
/////////////////////////////////////////////////////////////////////////
void ShipWreckBandInit()
{
	string sCharacter = PChar.GenerateShipWreck.CharacterID;
	ref chr = CharacterFromID(sCharacter);

	chr.greeting = "Gr_UnpleasantPerson";
	chr.Dialog.Filename = "DamnedDestiny\ShipWreck_dialog.c";
	chr.Dialog.CurrentNode = "21";
	chr.DeckDialogNode = "21";

	string sModel = "officer_" + (rand(63)+1);
	chr.model = sModel;
	FaceMaker(chr);

	SetCharacterGoods(chr, GOOD_GOLD, 0);
	SetCharacterGoods(chr, GOOD_SILVER, 0);
	SetCharacterGoods(chr, GOOD_EBONY, 0);
	SetCharacterGoods(chr, GOOD_MAHOGANY, 0);
	SetCharacterGoods(chr, GOOD_COFFEE, 0);
	SetCharacterGoods(chr, GOOD_TOBACCO, 0);

	int iRank = GetRank(PChar, 0) + MOD_SKILL_ENEMY_RATE;
	chr = GetCharacter(NPC_GenerateCharacter("ShipWreckValodya_" + rand(30000), "citiz_" + (rand(11)+1), "man", "man", iRank, PIRATE, -1, true));
	chr.greeting = "Gr_AllowToDump";
	chr.Dialog.Filename = "DamnedDestiny\ShipWreck_dialog.c";
	chr.Dialog.CurrentNode = "5";
	chr.ShipWrick = true;
	LAi_SetImmortal(chr, true);
	SetFantomParamFromRank(chr, iRank, true);

	PChar.GenerateShipWreck.ValodyaID = chr.id;

	float fLeaderShip = GetCharacterSkillToOld(PChar, SKILL_LEADERSHIP);
	float fCommerce = GetCharacterSkillToOld(PChar, SKILL_COMMERCE);
	int iMyCrew = sti(PChar.GenerateShipWreck.MyCrewQty);
	int iShipCrew = sti(PChar.GenerateShipWreck.ShipCrewQty);

	int iRand = iShipCrew - (iMyCrew-fLeaderShip) + rand(4);
	if(iRand <= 0)
	{
		iRand = 1;
	}
	else
	{
		iRand = 0;
	}

	PChar.GenerateShipWreck.ToSquadron = iRand;

	float fSkills = fCommerce + fLeaderShip;
	if(fSkills > rand(15))
	{
		iRand = 1;
	}
	else
	{
		iRand = 0;
	}

	PChar.GenerateShipWreck.ToSquadronWithMoney = iRand;

	string sCapModel = "";
	switch(rand(2))
	{
		case 0: sCapModel = "citiz_" + (rand(11)+1); break;
		case 1: sCapModel = "trader_" + (rand(15)+1); break;
		case 2: sCapModel = "officer_" + (rand(63)+1); break;
	}

	PChar.GenerateShipWreck.CapModel = sCapModel;
	PChar.GenerateShipWreck.PrisonedCrew = rand(3) + 5;

	int iShipNation = FindNonEnemyNation2Nation(sti(PChar.nation));
	PChar.GenerateShipWreck.CapNation = iShipNation;

	PChar.GenerateShipWreck.State = "BanditsInShip";
}

void ShipWreckBandValodyaToMoney()
{
	chrDisableReloadToLocation = true;

	string sValodya = PChar.GenerateShipWreck.ValodyaID;
	ref chr = CharacterFromID(sValodya);

	LAi_SetActorType(chr);
	LAi_ActorRunToLocation(chr, "reload", "reload1", "none", "", "", "", -1);

	if(PChar.GenerateShipWreck.ValodyaToMoney == true)
	{
		//LAi_SetActorType(PChar);
		DoQuestFunctionDelay("ShipWreckBandValodyaReturnWithMoneyS", 10.0);
	}
}

void ShipWreckBandValodyaReturnWithMoneyS(string _tmp)
{
	ShipWreckBandValodyaReturnWithMoney();
}

void ShipWreckBandValodyaReturnWithMoney()
{
	chrDisableReloadToLocation = true;

	string sValodya = PChar.GenerateShipWreck.ValodyaID;
	ref chr = CharacterFromID(sValodya);

	ChangeCharacterAddressGroup(chr, PChar.location, "reload", "reload1");

	LAi_SetActorType(chr);
	LAi_ActorFollow(chr, PChar, "", -1);

	if(PChar.GenerateShipWreck.ValodyaToMoney == true)
	{
		sValodya = PChar.GenerateShipWreck.CharacterID;
		chr = CharacterFromID(sValodya);
		chr.Dialog.CurrentNode = "44";
		chr.greeting = "";
		SetDialogCharacter2Character(PChar, chr, 15.0, false);
		PChar.GenerateShipWreck.ValodyaToMoney = false;
	}
}

void ShipWreckBanditsChangeGoodsEnd()
{
	string sCharacter = PChar.GenerateShipWreck.CharacterID;
	ref chr = CharacterFromID(sCharacter);

	chr.greeting = "";
	chr.Dialog.Filename = "DamnedDestiny\ShipWreck_dialog.c";
	chr.Dialog.CurrentNode = "33";
	SetDialogCharacter2Character(PChar, chr, 15.0, false);
}

void ShipWreckBanditsOneTypeEnd()
{
	chrDisableReloadToLocation = false;

	string sValodya = PChar.GenerateShipWreck.ValodyaID;
	ref chr = CharacterFromID(sValodya);

	PChar.quest.ShipWreckInSeaFailedSink.over = "yes";

	LAi_SetActorType(chr);
	LAi_ActorRunToLocation(chr, "reload", "reload1", "none", "", "", "", -1);

	string sCharacter = PChar.GenerateShipWreck.CharacterID;
	chr = CharacterFromID(sCharacter);

	if(PChar.GenerateShipWreck.AddBandaShip != true)
	{
		chr.LifeDay = 0;
		//Group_DeleteGroup(chr.id);
		//Group_SetAddress(chr.id, "none", "none", "none");
		chr.Killer.Status = KILL_BY_ABORDAGE;
		chr.Killer.Index = 0;
		LAi_SetCurHP(chr, 0.0);
	}
	else
	{
		chr.Ship.crew.morale = 10;
		//chr.CompanionEnemyEnable = true;
		DeleteAttribute(chr, "AlwaysFriend");
		DeleteAttribute(chr, "ShipEnemyDisable");
		DeleteAttribute(chr, "ShipTaskLock");
		DeleteAttribute(chr, "ShipWreck");
		DeleteAttribute(chr, "Abordage.Enable");

		SetCompanionIndex(PChar, -1, GetCharacterIndex(chr.id));
		PChar.VolodyaDebil.Convoy = "1";
		PChar.IdVolodiDebila = chr.id;
		Ship_FlagRefresh(chr);
		DeleteAttribute(chr,"LifeDay");


		ChangeCharacterReputation(chr, -50);
		ChangeCharacterReputation(PChar, -30);
		AddQuestRecord("ShipWreck", "7");
		PChar.GenerateShipWreck.AddBandaShip = false;
	}

	if(PChar.GenerateShipWreck.GoodsChange.Yes == true)
	{
		ChangeCharacterReputation(PChar, -10);

		string sNotice = "5";
		int iPlanksTake = sti(PChar.GenerateShipWreck.MaxGoods.Planks);
		int iSailClothTake = sti(PChar.GenerateShipWreck.MaxGoods.SailCloth);

		if(iPlanksTake == 1 && iSailClothTake == 1)
		{
			sNotice = "5";
		}else{
			if(iPlanksTake == 1 && iSailClothTake == 0)
			{
				sNotice = "9";
			}else{
				if(iPlanksTake == 0 && iSailClothTake == 1)
				{
					sNotice = "10";
				}else{
					if(iPlanksTake == 0 && iSailClothTake == 0)
					{
						sNotice = "11";
					}
				}
			}
		}

		AddQuestRecord("ShipWreck", sNotice);
		AddQuestUserData("ShipWreck", "sNavigator", GetNameLugger(chr, "f"));
		PChar.GenerateShipWreck.GoodsChange.Yes = false;
	}

	CloseQuestHeader("ShipWreck");

	PChar.GenerateShipWreck.Block = true;
	SetTimerFunction("ShipWreckResetBlock", 0, 0, 35);

	ClearShipWreckQuest();

	LAi_SetPlayerType(PChar);
	LAi_SetActorType(chr);
	LAi_ActorGoToLocation(chr, "reload", "reload1", "", "", "", "", 5.0);

	chr.loyality = MAX_LOYALITY/2;
	chr.greeting = "Gr_questOfficer";
	chr.Dialog.FileName = "Enc_Officer_dialog.c";
	chr.Dialog.CurrentNode = "hired";
}

void ShipWreckBanditsStartBattle()
{
	PChar.quest.ShipWreckInSeaFailedSink.over = "yes";
	chrDisableReloadToLocation = true;

	LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);

	int iQty = sti(PChar.GenerateShipWreck.ShipCrewQty) + 2;
	ref chr;

	int i = 0;
	string sSailor = "";
	for(i = 1; i <= iQty; i++)
	{
		sSailor = "saylor_0" + i;

		if(i == iQty)
		{
			sSailor = PChar.GenerateShipWreck.CharacterID;
		}
		if(i == (iQty-1))
		{
			sSailor = PChar.GenerateShipWreck.ValodyaID;
		}

		chr = CharacterFromID(sSailor);
		LAi_SetImmortal(chr, false);

		LAi_SetWarriorType(chr);
		LAi_group_MoveCharacter(chr, "EnemyFight");
	}

	iQty = sti(PChar.GenerateShipWreck.MyCrewQty);
	for(i = 1; i <= iQty; i++)
	{
		sSailor = "my_saylor_0" + i;

		if(GetCharacterIndex(sSailor) != -1)
		{
			chr = CharacterFromID(sSailor);
			LAi_SetImmortal(chr, false);

			LAi_SetWarriorType(chr);
			LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
		}
	}

	LAi_SetPlayerType(PChar);

	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);

	string sCnd = "";

	iQty = sti(PChar.GenerateShipWreck.ShipCrewQty) + 2;
	for(i = 1; i <= iQty; i++)
	{
		sSailor = "saylor_0" + i;
		if(i == iQty)
		{
			sSailor = PChar.GenerateShipWreck.CharacterID;
		}

		if(i == (iQty-1))
		{
			sSailor = PChar.GenerateShipWreck.ValodyaID;
		}

		sCnd = "l" + i;
		PChar.quest.ShipWreckBanditsBattleWinner.win_condition.(sCnd) = "NPC_Death";
		PChar.quest.ShipWreckBanditsBattleWinner.win_condition.(sCnd).character = sSailor;
	}

	PChar.quest.ShipWreckBanditsBattleWinner.function = "ShipWreckBanditsBattleWinner";
}

void ShipWreckBanditsBattleWinner(string qName)
{
	ChangeCharacterReputation(PChar, 10);

	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], true);

	string sValodya = PChar.GenerateShipWreck.ValodyaID;
	ref chr = CharacterFromID(sValodya);
	chr.LifeDay = 0;
	//ChangeCharacterAddress(chr, "None", "");

	string sCharacter = PChar.GenerateShipWreck.CharacterID;
	chr = CharacterFromID(sCharacter);
	chr.LifeDay = 0;
	chr.Killer.Status = KILL_BY_ABORDAGE;
	chr.Killer.Index = 0;
	LAi_SetCurHP(chr, 0.0);

	//ShipTaken(GetCharacterIndex(chr.id), KILL_BY_ABORDAGE, nMainCharacterIndex);

	//ChangeCharacterAddress(chr, "None", "");

	LAi_Fade("", "");

	string sModel = PChar.GenerateShipWreck.CapModel;
	int iRank = GetRank(PChar, 3) + rand(3);
	int iNation = sti(PChar.GenerateShipWreck.CapNation);

	chr = GetCharacter(NPC_GenerateCharacter("ShipWreckBadCaptain_" + rand(30000), sModel, "man", "man", iRank, iNation, -1, true));
	chr.greeting = "Gr_AllowToDump";
	chr.Dialog.Filename = "DamnedDestiny\ShipWreck_dialog.c";
	chr.Dialog.CurrentNode = "NewCap_1";

	SetFantomParamFromRank(chr, iRank, true);

	ChangeCharacterAddressGroup(chr, PChar.location, "reload", "reload1");
	SetDialogCharacter2Character(PChar, chr, 20.0, false);

	PChar.GenerateShipWreck.NewCapID = chr.id;
}

void ShipWreckBanditsNewCapAdd()
{
	chrDisableReloadToLocation = false;

	string sCharacter = PChar.GenerateShipWreck.NewCapID;
	ref chr = CharacterFromID(sCharacter);

	chr.Ship.crew.morale = MORALE_MAX;
	//chr.CompanionEnemyEnable = true;
	DeleteAttribute(chr, "AlwaysFriend");
	DeleteAttribute(chr, "ShipEnemyDisable");
	DeleteAttribute(chr, "ShipTaskLock");
	DeleteAttribute(chr, "ShipWreck");
	DeleteAttribute(chr, "Abordage.Enable");

	SetCompanionIndex(PChar, -1, GetCharacterIndex(chr.id));
	Ship_FlagRefresh(chr);

	AddQuestRecord("ShipWreck", "6");
	CloseQuestHeader("ShipWreck");

	PChar.GenerateShipWreck.Block = true;
	SetTimerFunction("ShipWreckResetBlock", 0, 0, 35);

	ClearShipWreckQuest();

	LAi_SetActorType(chr);
	LAi_ActorGoToLocation(chr, "reload", "reload1", "none", "", "", "", -1);

	chr.greeting = "Gr_questOfficer";
	chr.Dialog.FileName = "Enc_Officer_dialog.c";
	chr.Dialog.CurrentNode = "hired";
}

void ShipWreckBanditsNewCapNoAdd()
{
	chrDisableReloadToLocation = false;

	string sCharacter = PChar.GenerateShipWreck.NewCapID;
	ref chr = CharacterFromID(sCharacter);
	chr.LifeDay = 0;

	LAi_SetActorType(chr);
	LAi_ActorGoToLocation(chr, "reload", "reload1", "none", "", "", "", -1);

	chr.greeting = "Gr_questOfficer";
	chr.Dialog.FileName = "Enc_Officer_dialog.c";
	chr.Dialog.CurrentNode = "hired";

	AddQuestRecord("ShipWreck", "6");
	CloseQuestHeader("ShipWreck");

	PChar.GenerateShipWreck.Block = true;
	SetTimerFunction("ShipWreckResetBlock", 0, 0, 35);

	ClearShipWreckQuest();
}

/////////////////////////////////////////////////////////////////////////
// УДАЛЯЕМ КВЕСТ
/////////////////////////////////////////////////////////////////////////
void ShipWreckTimeActionEnd(string qName)
{
	PChar.GenerateShipWreck.Block = true;
	SetTimerFunction("ShipWreckResetBlock", 0, 0, 35);
	//if(!CheckAttribute(PChar, "GenerateShipWreck.CharacterID")) { return; }
	//if(GetCharacterIndex(PChar.GenerateShipWreck.CharacterID) == -1) { return; }

	PChar.quest.ShipWreckInSeaFailedSink.over = "yes";
	PChar.quest.ShipWreckLoginToWorldMap.over = "yes";

	if(CheckAttribute(PChar, "GenerateShipWreck.CharacterID"))
	{
		if(GetCharacterIndex(PChar.GenerateShipWreck.CharacterID) != -1)
		{
			ref chr = CharacterFromID(PChar.GenerateShipWreck.CharacterID);
			chr.LifeDay = 0;
			Map_ReleaseQuestEncounter(chr.id);
		}
	}

	ClearShipWreckQuest();
}

void ShipWreckInMapCancel(ref chr)
{
	PChar.quest.ShipWreckTimeActionEnd.over = "yes";
	Map_ReleaseQuestEncounter(chr.id);

	PChar.GenerateShipWreck.Block = true;
	SetTimerFunction("ShipWreckResetBlock", 0, 0, 35);

	ClearShipWreckQuest();
}

void ShipWreckResetBlock(string qName)
{
	PChar.GenerateShipWreck.Block = false;
	Log_TestInfo("Квест 'Кораблекрушение' - блокировка снята.");
}

void ClearShipWreckQuest()
{
	Log_TestInfo("Удаляем квест 'Кораблекрушение' по истечении времени, по прохождении или игнора.");

	ref chr;
	if(!CheckAttribute(PChar,"VolodyaDebil.Convoy"))
	{
		if(CheckAttribute(PChar, "GenerateShipWreck.CharacterID"))
		{
			if(GetCharacterIndex(PChar.GenerateShipWreck.CharacterID) != -1)
			{
				chr = CharacterFromID(PChar.GenerateShipWreck.CharacterID);
				chr.LifeDay = 0;
				chr.mapEnc.Name = "нам показалось";
				Map_ReleaseQuestEncounter(chr.id);
			}
		}

		if(CheckAttribute(PChar, "GenerateShipWreck.ValodyaID"))
		{
			if(GetCharacterIndex(PChar.GenerateShipWreck.ValodyaID) != -1)
			{
				chr = CharacterFromID(PChar.GenerateShipWreck.ValodyaID);
				chr.LifeDay = 0;
			}
		}
	}
	else
	{
		chr = CharacterFromID(PChar.GenerateShipWreck.CharacterID);
		Map_ReleaseQuestEncounter(chr.id);
		/*aref encs;
		makearef(encs, worldMap.encounters);
		int num =  GetAttributesNum(encs);
		chr = CharacterFromID(PChar.GenerateShipWreck.CharacterID);
		makearef(encs, worldMap.encounters);
		num = GetAttributesNum(encs);
	for(int i = 0; i < num; i++)
	{
		aref enc = GetAttributeN(encs, i);
		if(CheckAttribute(enc, "quest.chrID") == 0) continue;
		if(enc.quest.chrID == chr.id)
		{
			wdmDeleteLoginEncounter(GetAttributeName(enc));
		}
	}*/
	}
	if(CheckAttribute(PChar, "GenerateShipWreck.ShipCrewQty")) 		{ DeleteAttribute(PChar, "GenerateShipWreck.ShipCrewQty"); }
	if(CheckAttribute(PChar, "GenerateShipWreck.Situation")) 		{ DeleteAttribute(PChar, "GenerateShipWreck.Situation"); }
	if(CheckAttribute(PChar, "GenerateShipWreck.Money")) 			{ DeleteAttribute(PChar, "GenerateShipWreck.Money"); }
	if(CheckAttribute(PChar, "GenerateShipWreck.CharacterIdx")) 		{ DeleteAttribute(PChar, "GenerateShipWreck.CharacterIdx"); }
	if(CheckAttribute(PChar, "GenerateShipWreck.CharacterID")) 		{ DeleteAttribute(PChar, "GenerateShipWreck.CharacterID"); }
	if(CheckAttribute(PChar, "GenerateShipWreck.MyCrewQty")) 		{ DeleteAttribute(PChar, "GenerateShipWreck.MyCrewQty"); }
	if(CheckAttribute(PChar, "GenerateShipWreck.ShipCrewQty")) 		{ DeleteAttribute(PChar, "GenerateShipWreck.ShipCrewQty"); }
	if(CheckAttribute(PChar, "GenerateShipWreck.NewCapID")) 		{ DeleteAttribute(PChar, "GenerateShipWreck.NewCapID"); }
	if(CheckAttribute(PChar, "GenerateShipWreck.CapModel")) 		{ DeleteAttribute(PChar, "GenerateShipWreck.CapModel"); }
	if(CheckAttribute(PChar, "GenerateShipWreck.CapNation")) 		{ DeleteAttribute(PChar, "GenerateShipWreck.CapNation"); }
	if(CheckAttribute(PChar, "GenerateShipWreck.ShipWreckName")) 		{ DeleteAttribute(PChar, "GenerateShipWreck.ShipWreckName"); }
	if(CheckAttribute(PChar, "GenerateShipWreck.ShipWreckIdx")) 		{ DeleteAttribute(PChar, "GenerateShipWreck.ShipWreckIdx"); }
	if(CheckAttribute(PChar, "GenerateShipWreck.ModelHelper")) 		{ DeleteAttribute(PChar, "GenerateShipWreck.ModelHelper"); }
	if(CheckAttribute(PChar, "GenerateShipWreck.ToSquadronWithMoney")) 	{ DeleteAttribute(PChar, "GenerateShipWreck.ToSquadronWithMoney"); }
	if(CheckAttribute(PChar, "GenerateShipWreck.ToSquadron")) 		{ DeleteAttribute(PChar, "GenerateShipWreck.ToSquadron"); }
	if(CheckAttribute(PChar, "GenerateShipWreck.PrisonedCrew")) 		{ DeleteAttribute(PChar, "GenerateShipWreck.PrisonedCrew"); }
	if(CheckAttribute(PChar, "GenerateShipWreck.ValodyaID")) 		{ DeleteAttribute(PChar, "GenerateShipWreck.ValodyaID"); }
	if(CheckAttribute(PChar, "GenerateShipWreck.ShipSP")) 			{ DeleteAttribute(PChar, "GenerateShipWreck.ShipSP"); }
	if(CheckAttribute(PChar, "GenerateShipWreck.ShipHP")) 			{ DeleteAttribute(PChar, "GenerateShipWreck.ShipHP"); }
	if(CheckAttribute(PChar, "GenerateShipWreck.ShipInMap")) 		{ DeleteAttribute(PChar, "GenerateShipWreck.ShipInMap"); }

	PChar.GenerateShipWreck.State = "none";
	PChar.GenerateShipWreck.MaxGoods = 0;
	PChar.GenerateShipWreck.MaxGoods.Planks = 0;
	PChar.GenerateShipWreck.MaxGoods.SailCloth = 0;
	PChar.GenerateShipWreck.GoodsChange = false;
	PChar.GenerateShipWreck.GoodsChange.Yes = false;
	PChar.GenerateShipWreck.AddBandaShip = false;
	PChar.GenerateShipWreck.ValodyaToMoney = false;
	DeleteAttribute(PChar,"VolodyaDebil.Convoy");
	DeleteAttribute(PChar,"IdVolodiDebila");
}

