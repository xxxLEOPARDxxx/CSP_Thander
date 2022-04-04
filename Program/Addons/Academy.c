/* Академия, тренировки и т.д. */

void AcademyLandInit()
{
	PChar.AcademyLand = "none";
	PChar.AcademyLand.Can = true;
	PChar.AcademyLand.Begin = false;

	PChar.AcademyLand.TrainingType = 0;
	PChar.AcademyLand.DefenceType = 0;

	PChar.AcademyLand.Temp.Rank = 0;
	PChar.AcademyLand.Temp.Skill = 0;
	PChar.AcademyLand.Temp.HP = 0;
	PChar.AcademyLand.Temp.Energy = 0;

	PChar.AcademyLand.Temp.Skill = "Fencing";

	PChar.AcademyLand.Temp.PlayerCrew = 0;
	PChar.AcademyLand.Temp.EnemyCrew = 0;

	PChar.AcademyLand.Temp.Saber = "blade1";

	PChar.AcademyLand.Temp.EnablePotion = 0;
	PChar.AcademyLand.Temp.EnableFood = 0;
	PChar.AcademyLand.RandPlace = rand(1);

	if(!CheckAttribute(PChar, "AcademyLand.Count")) PChar.AcademyLand.Count = 0;

	if(!CheckAttribute(PChar, "AcademyLand.FCCount")) PChar.AcademyLand.FCCount = 0;
	if(!CheckAttribute(PChar, "AcademyLand.FCCountLooserCount")) PChar.AcademyLand.FCCountLooserCount = 0;
	if(!CheckAttribute(PChar, "AcademyLand.FCCountWinnerCount")) PChar.AcademyLand.FCCountWinnerCount = 0;

	if(!CheckAttribute(PChar, "AcademyLand.WWCount")) PChar.AcademyLand.WWCount = 0;
	if(!CheckAttribute(PChar, "AcademyLand.WWCountLooserCount")) PChar.AcademyLand.WWCountLooserCount = 0;
	if(!CheckAttribute(PChar, "AcademyLand.WWCountWinnerCount")) PChar.AcademyLand.WWCountWinnerCount = 0;

	if(!CheckAttribute(PChar, "AcademyLand.OOCount")) PChar.AcademyLand.OOCount = 0;
	if(!CheckAttribute(PChar, "AcademyLand.OOCountLooserCount")) PChar.AcademyLand.OOCountLooserCount = 0;
	if(!CheckAttribute(PChar, "AcademyLand.OOCountWinnerCount")) PChar.AcademyLand.OOCountWinnerCount = 0;
}

void AcademyLandGenerateEnd()
{
	int iType = 0;

	if(CheckAttribute(PChar, "AcademyLand.TrainingType"))
	{
		iType = sti(PChar.AcademyLand.TrainingType);
	}

	switch(iType)
	{
		case 0: LandAcademyPrepareFortCapture(); break;
		case 1: LandAcademyPrepareWallOnWall(); break;
		case 2: LandAcademyPrepareOneOnOne(); break;
	}
}

void SetTrainingStatictic(bool bWinner)
{
	int iType = 0;
	if(CheckAttribute(PChar, "AcademyLand.TrainingType"))
	{
		iType = sti(PChar.AcademyLand.TrainingType);
	}

	string sType = "";
	switch(iType)
	{
		case 0: sType = "FCCount"; break;
		case 1: sType = "WWCount"; break;
		case 2: sType = "OOCount"; break;
	}

	PChar.AcademyLand.(sType) = sti(PChar.AcademyLand.(sType)) + 1;

	string sEndType = "";
	if(bWinner)
	{
		sEndType = "WinnerCount";
	}
	else
	{
		sEndType = "LooserCount";
	}
	string sCount = sType + sEndType;

	if(sCount == "")
	{
		sCount = "OOCountLooserCount";
	}

	PChar.AcademyLand.(sCount) = sti(PChar.AcademyLand.(sCount)) + 1;
	PChar.AcademyLand.Count = sti(PChar.AcademyLand.Count) + 1;
}

void AcademyLandTrainingPause()
{
	int iPlayerCrew = sti(PChar.AcademyLand.Temp.PlayerCrew);
	int iEnemyCrew = sti(PChar.AcademyLand.Temp.EnemyCrew);
	int i, n;

	string sCharacter;

	ref chr;
	for(i = 1; i <= iPlayerCrew; i++)
	{
		sCharacter = "AcademyLandPlayer_" + i;
		chr = &Characters[GetCharacterIndex(sCharacter)];

		LAi_SetFightMode(chr, false);
		LAi_SetActorType(chr);
		LAi_group_MoveCharacter(chr, LAI_GROUP_ACTOR);
	}

	for(n = 1; n <= iEnemyCrew; n++)
	{
		sCharacter = "AcademyLandEnemy_" + n;
		chr = &Characters[GetCharacterIndex(sCharacter)];

		LAi_SetFightMode(chr, false);
		LAi_SetActorType(chr);
		LAi_group_MoveCharacter(chr, LAI_GROUP_ACTOR);
	}

	float fMaxHP = LAi_GetCharacterMaxHP(PChar);
	LAi_SetHP(PChar, fMaxHP, fMaxHP);
}

///////////////////////////////////////////////////////////////////////////////////
// Первый вариант - захват форта
///////////////////////////////////////////////////////////////////////////////////
void LandAcademyPrepareFortCapture()
{
	PChar.quest.LandAcademyFortCapture.win_condition.l1 = "location";
	PChar.quest.LandAcademyFortCapture.win_condition.l1.location = "FencingTown_ExitTown";
	PChar.quest.LandAcademyFortCapture.function = "LandAcademyFortCapture";
}

void LandAcademyFortCapture(string _tmp)
{
	DeleteAllOfficersFromLocation();

	InterfaceStates.Buttons.Save.enable = false;
	PChar.AcademyLand = "Start";

	string sLocator, sLocReload, sGroupReload, sGroupLocator;

	int iDefenceType = 0;
	if(CheckAttribute(PChar, "AcademyLand.DefenceType"))
	{
		iDefenceType = sti(PChar.AcademyLand.DefenceType);
	}

	if(iDefenceType == 0)
	{
		sLocReload = "reload2_back";
		sGroupReload = "reload";
	}
	else
	{
		sLocReload = "reload4";
		sGroupReload = "reload";
	}

	int i, n, iPlayerCrew, iEnemyCrew, iChar;

	iPlayerCrew = 29;
	iEnemyCrew = 30;

	if(CheckAttribute(PChar, "AcademyLand.Temp.PlayerCrew"))
	{
		iPlayerCrew = sti(PChar.AcademyLand.Temp.PlayerCrew);
	}
	if(CheckAttribute(PChar, "AcademyLand.Temp.EnemyCrew"))
	{
		iEnemyCrew = sti(PChar.AcademyLand.Temp.EnemyCrew);
	}

	ref chr;

	int iRank, iSkill, iHp, iEnergy;
	if(CheckAttribute(PChar, "AcademyLand.Temp.Rank")) { iRank = sti(PChar.AcademyLand.Temp.Rank); } else { iRank = 5; }
	if(CheckAttribute(PChar, "AcademyLand.Temp.Skill.Quantity")) { iSkill = sti(PChar.AcademyLand.Temp.Skill.Quantity); } else { iSkill = 20; }
	if(CheckAttribute(PChar, "AcademyLand.Temp.HP")) { iHp = sti(PChar.AcademyLand.Temp.HP); } else { iHp = 30; }
	if(CheckAttribute(PChar, "AcademyLand.Temp.Energy")) { iEnergy = sti(PChar.AcademyLand.Temp.Energy); } else { iEnergy = 40; }

	string sSkill = "Fencing";
	if(CheckAttribute(PChar, "AcademyLand.Temp.Skill"))
	{
		sSkill = PChar.AcademyLand.Temp.Skill;
	}

	string sSaber = "blade1";

	if(CheckAttribute(PChar, "AcademyLand.Temp.Saber"))
	{
		sSaber = PChar.AcademyLand.Temp.Saber;
	}

	for(i = 1; i <= iPlayerCrew; i++)
	{
		iChar = NPC_GenerateCharacterIndep("AcademyLandPlayer_" + i, "shipowner_2"+(rand(9)), "man", "man", iRank, PIRATE, 0, false);
		chr = &Characters[iChar];

		// CreateModel(iChar, "pofficer", MAN);

		SetRandSPECIAL(chr);
		chr.rank = iRank;
		chr.skill.(sSkill) = iSkill;
		LAi_SetHP(chr, stf(iHp), stf(iHp));
		SetEnergyQty(chr, stf(iEnergy), stf(iEnergy));
		chr.LandAcademy = true;
		chr.LandAcademy.Player = true;

		RemoveCharacterEquip(chr, BLADE_ITEM_TYPE);
		RemoveCharacterEquip(chr, GUN_ITEM_TYPE);

		DeleteAttribute(chr, "items");

		GiveItem2Character(chr, sSaber);
		EquipCharacterByItem(chr, sSaber);

		sLocator = GetLocatorAcademyLandFortCapture(i, iDefenceType, true, true, false);
		sGroupLocator = GetLocatorGroupAcademyLandFortCapture(sLocator);
		ChangeCharacterAddressGroup(chr, PChar.location, sGroupLocator, sLocator);

		LAi_SetWarriorType(chr);
		LAi_SetFightMode(chr, true);
		LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
		LAi_NPC_EquipPerk(chr, "fantom");
	}

	for(n = 1; n <= iEnemyCrew; n++)
	{
		iChar = NPC_GenerateCharacterIndep("AcademyLandEnemy_" + n, "pirate_1", "man", "man", iRank, PIRATE, 0, false);

		CreateModel(iChar, "pirate", MAN);

		chr = &Characters[iChar];
		SetRandSPECIAL(chr);
		chr.rank = iRank;
		chr.skill.(sSkill) = iSkill;
		LAi_SetHP(chr, stf(iHp), stf(iHp));
		SetEnergyQty(chr, stf(iEnergy), stf(iEnergy));
		chr.LandAcademy = true;
		chr.LandAcademy.Enemy = true;

		RemoveCharacterEquip(chr, BLADE_ITEM_TYPE);
		RemoveCharacterEquip(chr, GUN_ITEM_TYPE);

		DeleteAttribute(chr, "items");

		GiveItem2Character(chr, sSaber);
		EquipCharacterByItem(chr, sSaber);

		sLocator = GetLocatorAcademyLandFortCapture(n, iDefenceType, false, true, false);
		sGroupLocator = GetLocatorGroupAcademyLandFortCapture(sLocator);
		ChangeCharacterAddressGroup(chr, PChar.location, sGroupLocator, sLocator);

		LAi_SetWarriorType(chr);
		LAi_SetFightMode(chr, true);
		LAi_group_MoveCharacter(chr, "EnemyFight");
		LAi_NPC_EquipPerk(chr, "fantom");
	}
	RemoveCharacterEquip(PChar, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);

	GiveItem2Character(PChar, sSaber);
	EquipCharacterByItem(PChar, sSaber);

	ChangeCharacterAddressGroup(PChar, PChar.location, sGroupReload, sLocReload);

	LAi_SetPlayerType(PChar);
	LAi_SetImmortal(PChar, false);
	LAi_SetFightMode(PChar, true);
	PChar.LandAcademy.Player = true;

	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);

	Locations[FindLocation(PChar.location)].reload.l2.disable = true;
	Locations[FindLocation(PChar.location)].reload.l3.disable = true;
	Locations[FindLocation(PChar.location)].reload.l4.disable = true;

	Log_InfoS("Тренировка началась. Необходимо ликвидировать соперника!");
}

string GetLocatorAcademyLandFortCapture(int iNum, bool bDefence, bool bPlayer, bool bFortCapture, bool bRand)
{
	if(bFortCapture)
	{
		if(!bDefence)
		{
			if(bPlayer)
			{
				if(iNum >= 3 && iNum <= 10)
				{
					// return "reload2_back";
					return "loc" + iNum;
				}
				else
				{
					return "loc" + iNum;
				}
			}
			else
			{
				if(iNum <= 15)
				{
					return "aloc" + iNum;
				}
				else
				{
					// return "reload4";
					return "aloc" + iNum;
				}
			}
		}
		else
		{
			if(bPlayer)
			{
				if(iNum <= 15)
				{
					return "aloc" + iNum;
				}
				else
				{
					// return "reload4";
					return "aloc" + iNum;
				}
			}
			else
			{
				if(iNum >= 3 && iNum <= 10)
				{
					// return "reload2_back";
					return "loc" + iNum;
				}
				else
				{
					return "loc" + iNum;
				}
			}
		}
	}
	else
	{
		if(bPlayer)
		{
			if(!bDefence)
			{
				if(!bRand)
				{
					return "wall_player_" + iNum;
				}
				else
				{
					return "wall_enemy_" + iNum;
				}
			}
			else
			{
				if(!bRand)
				{
					return "loc" + iNum;
				}
				else
				{
					return "aloc" + iNum;
				}
			}
		}
		else
		{
			if(!bDefence)
			{
				if(bRand)
				{
					return "wall_player_" + iNum;
				}
				else
				{
					return "wall_enemy_" + iNum;
				}
			}
			else
			{
				if(bRand)
				{
					return "loc" + iNum;
				}
				else
				{
					return "aloc" + iNum;
				}
			}
		}
	}

	return "reload2_back";
}

string GetLocatorGroupAcademyLandFortCapture(string sLocator)
{
	if(sLocator == "reload2_back" || sLocator == "reload4")
	{
		return "reload";
	}
	else
	{
		return "rld";
	}
}

void AcademyLandSetLooser(ref chr)
{
	if(chr.id != PChar.id)
	{
		LAi_SetHP(chr, 5.0, 5.0);
	}

	LAi_SetImmortal(chr, true);

	chr.LandAcademy.Dead = true;
	LAi_SetFightMode(chr, false);
	LAi_group_MoveCharacter(chr, LAI_DEFAULT_GROUP);

	LAi_SetActorType(chr);

	string sLocator = "";
	if(PChar.location == "FencingTown_ExitTown")
	{
		sLocator = "reload3_back";
	}
	else
	{
		sLocator = "reload1";
	}

	if(chr.id != PChar.id)
	{
		LAi_ActorRunToLocation(chr, "reload", sLocator, "none", "", "", "", -1);
		//LogoffCharacter(chr);
	}

	AcademyLandCheckLoosers();
}

void AcademyLandCheckLoosers()
{
	int iPlayerCrew = sti(PChar.AcademyLand.Temp.PlayerCrew);
	int iEnemyCrew = sti(PChar.AcademyLand.Temp.EnemyCrew);

	iPlayerCrew++;

	int i, n;
	ref chr;

	string sCharacter;

	int iPlayerCount = 0;
	int iEnemyCount = 0;

	for(i = 1; i <= iPlayerCrew; i++)
	{
		sCharacter = "AcademyLandPlayer_" + i;

		if(i == iPlayerCrew)
		{
			chr = GetMainCharacter();
		}
		else
		{
			chr = &Characters[GetCharacterIndex(sCharacter)];
		}

		if(CheckAttribute(chr, "LandAcademy.Dead"))
		{
			iPlayerCount++;
		}
	}

	for(n = 1; n <= iEnemyCrew; n++)
	{
		sCharacter = "AcademyLandEnemy_" + n;
		chr = &Characters[GetCharacterIndex(sCharacter)];

		if(CheckAttribute(chr, "LandAcademy.Dead"))
		{
			iEnemyCount++;
		}
	}

	if(iPlayerCount == iPlayerCrew)
	{
		InterfaceStates.Buttons.Save.enable = true;

		AcademyLandTrainingPause();
		Log_Info("Вы проиграли. Тренировка завершена.");
		LAi_SetFightMode(PChar, false);
		LAi_QuestDelay("AcademyLand_Loose", 5.0);

		return;
	}

	if(iEnemyCount == iEnemyCrew)
	{
		InterfaceStates.Buttons.Save.enable = true;

		AcademyLandTrainingPause();
		Log_Info("Вы выиграли. Тренировка завершена.");
		LAi_SetFightMode(PChar, false);
		LAi_QuestDelay("AcademyLand_Winner", 5.0);
		return;
	}
}

void AcademyLandTrainingEnd(bool bWinner)
{
	InterfaceStates.Buttons.Save.enable = true;

	string sSaber = "blade1";
	if(CheckAttribute(PChar, "AcademyLand.Temp.Saber"))
	{
		sSaber = PChar.AcademyLand.Temp.Saber;
	}

	RemoveCharacterEquip(PChar, BLADE_ITEM_TYPE);
	TakeNItems(PChar, sSaber, -1);

	// Для статистики -->
	SetTrainingStatictic(bWinner);
	// Для статистики <--

	AcademyLandInit();

	LAi_group_MoveCharacter(PChar, LAI_GROUP_PLAYER);
	LAi_SetPlayerType(PChar);

	LAi_RemoveCheckMinHP(PChar);
	LAi_SetCurHPMax(PChar);
	LAi_SetImmortal(PChar, false);
	
	// LEO: Зачем вытирать этот перк, непонятно...
	/* if(CheckAttribute(PChar, "perks.list.Energaiser"))
	{
		DeleteAttribute(PChar, "perks.list.Energaiser");
	} */

	if(PChar.location == "FencingTown_ExitTown")
	{
		Locations[FindLocation(PChar.location)].reload.l2.disable = false;
		Locations[FindLocation(PChar.location)].reload.l3.disable = false;
		Locations[FindLocation(PChar.location)].reload.l4.disable = false;
		DoQuestReloadToLocation("FencingTown_Fort", "reload", "reload1_back", "");
	}

	if(CheckAttribute(PChar, "LandAcademy"))
	{
		DeleteAttribute(PChar, "LandAcademy");
	}

	if(PChar.location == "FencingTown_Arena")
	{
		DoQuestReloadToLocation("FencingTown_ExitTown", "reload", "reload4", "");
	}

	int d = rand(5) + 5;
	PChar.AcademyLand.Can = false;
	Log_TestInfo("Возможность тренировок заблокирована на " + d + " дней.");

	SetTimerFunction("AcademyLandBlockReset", 0, 0, d);
}

void AcademyLandBlockReset(string qName)
{
	PChar.AcademyLand.Can = true;
	Log_TestInfo("Возможность тренировок включена.");
}

///////////////////////////////////////////////////////////////////////////////////
// Второй вариант - стенка на стенку
///////////////////////////////////////////////////////////////////////////////////
void LandAcademyPrepareWallOnWall()
{
	Locations[FindLocation("FencingTown_ExitTown")].reload.l1.disable = false;
	PChar.quest.LandAcademyWallOnWall.win_condition.l1 = "location";
	PChar.quest.LandAcademyWallOnWall.win_condition.l1.location = "FencingTown_Arena";
	PChar.quest.LandAcademyWallOnWall.function = "LandAcademyWallOnWall";
}

void LandAcademyWallOnWall(string _tmp)
{
	InterfaceStates.Buttons.Save.enable = false;

	Locations[FindLocation("FencingTown_ExitTown")].reload.l1.disable = true;
	Locations[FindLocation(PChar.location)].reload.l1.disabled = true;

	PChar.AcademyLand = "Start";
	int iRandPlace = sti(PChar.AcademyLand.RandPlace);

	string sLocator, sLocReload, sGroupReload, sGroupLocator;

	int iDefenceType = 0;
	if(CheckAttribute(PChar, "AcademyLand.DefenceType"))
	{
		iDefenceType = sti(PChar.AcademyLand.DefenceType);
	}

	if(iDefenceType == 0)
	{
		sLocReload = "wall_enemy_1";

		if(iRandPlace == 0)
		{
			sLocReload = "wall_player_1";
		}

		sGroupReload = "goto";
	}
	else
	{
		sLocReload = "aloc1";

		if(iRandPlace == 0)
		{
			sLocReload = "loc1";
		}

		sGroupReload = "rld";
	}

	int i, n, iPlayerCrew, iEnemyCrew, iChar;

	iPlayerCrew = 9;
	iEnemyCrew = 10;

	if(CheckAttribute(PChar, "AcademyLand.Temp.PlayerCrew"))
	{
		iPlayerCrew = sti(PChar.AcademyLand.Temp.PlayerCrew);
	}
	if(CheckAttribute(PChar, "AcademyLand.Temp.EnemyCrew"))
	{
		iEnemyCrew = sti(PChar.AcademyLand.Temp.EnemyCrew);
	}

	ref chr;

	int iRank, iSkill, iHp, iEnergy;
	if(CheckAttribute(PChar, "AcademyLand.Temp.Rank")) { iRank = sti(PChar.AcademyLand.Temp.Rank); } else { iRank = 5; }
	if(CheckAttribute(PChar, "AcademyLand.Temp.Skill.Quantity")) { iSkill = sti(PChar.AcademyLand.Temp.Skill.Quantity); } else { iSkill = 20; }
	if(CheckAttribute(PChar, "AcademyLand.Temp.HP")) { iHp = sti(PChar.AcademyLand.Temp.HP); } else { iHp = 30; }
	if(CheckAttribute(PChar, "AcademyLand.Temp.Energy")) { iEnergy = sti(PChar.AcademyLand.Temp.Energy); } else { iEnergy = 40; }

	string sSkill = "Fencing";
	if(CheckAttribute(PChar, "AcademyLand.Temp.Skill"))
	{
		sSkill = PChar.AcademyLand.Temp.Skill;
	}

	string sSaber = "blade1";

	if(CheckAttribute(PChar, "AcademyLand.Temp.Saber"))
	{
		sSaber = PChar.AcademyLand.Temp.Saber;
	}

	for(i = 1; i <= iPlayerCrew; i++)
	{
		iChar = NPC_GenerateCharacterIndep("AcademyLandPlayer_" + i, "shipowner_2"+(rand(9)), "man", "man", iRank, PIRATE, 0, false);
		chr = &Characters[iChar];

		// CreateModel(iChar, "pofficer", MAN);

		SetRandSPECIAL(chr);
		chr.rank = iRank;
		chr.skill.(sSkill) = iSkill;
		LAi_SetHP(chr, stf(iHp), stf(iHp));
		SetEnergyQty(chr, stf(iEnergy), stf(iEnergy));
		chr.LandAcademy = true;
		chr.LandAcademy.Player = true;

		RemoveCharacterEquip(chr, BLADE_ITEM_TYPE);
		RemoveCharacterEquip(chr, GUN_ITEM_TYPE);

		DeleteAttribute(chr, "items");

		GiveItem2Character(chr, sSaber);
		EquipCharacterByItem(chr, sSaber);

		sLocator = GetLocatorAcademyLandFortCapture((i+1), iDefenceType, true, false, iRandPlace);
		ChangeCharacterAddressGroup(chr, PChar.location, sGroupReload, sLocator);

		LAi_SetWarriorType(chr);
		LAi_SetFightMode(chr, true);
		LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
		LAi_NPC_EquipPerk(chr, "fantom");
	}

	for(n = 1; n <= iEnemyCrew; n++)
	{
		iChar = NPC_GenerateCharacterIndep("AcademyLandEnemy_" + n, "pirate_1", "man", "man", iRank, PIRATE, 0, false);

		CreateModel(iChar, "pirate", MAN);

		SetRandSPECIAL(chr);
		chr = &Characters[iChar];
		chr.rank = iRank;
		chr.skill.(sSkill) = iSkill;
		LAi_SetHP(chr, stf(iHp), stf(iHp));
		SetEnergyQty(chr, stf(iEnergy), stf(iEnergy));
		chr.LandAcademy = true;
		chr.LandAcademy.Enemy = true;

		RemoveCharacterEquip(chr, BLADE_ITEM_TYPE);
		RemoveCharacterEquip(chr, GUN_ITEM_TYPE);

		DeleteAttribute(chr, "items");

		GiveItem2Character(chr, sSaber);
		EquipCharacterByItem(chr, sSaber);

		sLocator = GetLocatorAcademyLandFortCapture(n, iDefenceType, false, false, iRandPlace);
		ChangeCharacterAddressGroup(chr, PChar.location, sGroupReload, sLocator);

		LAi_SetWarriorType(chr);
		LAi_SetFightMode(chr, true);
		LAi_group_MoveCharacter(chr, "EnemyFight");
		LAi_NPC_EquipPerk(chr, "fantom");
	}

	RemoveCharacterEquip(PChar, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
	GiveItem2Character(PChar, sSaber);
	EquipCharacterByItem(PChar, sSaber);
	ChangeCharacterAddressGroup(PChar, PChar.location, sGroupReload, sLocReload);

	LAi_SetPlayerType(PChar);
	LAi_SetFightMode(PChar, true);
	PChar.LandAcademy.Player = true;

	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	Log_Info("Тренировка началась. Необходимо ликвидировать соперника!");
}

///////////////////////////////////////////////////////////////////////////////////
// Третий вариант - один на один! Соперник намного серьёзнее
///////////////////////////////////////////////////////////////////////////////////
void LandAcademyPrepareOneOnOne()
{
	Locations[FindLocation("FencingTown_ExitTown")].reload.l1.disable = false;
	PChar.quest.LandAcademyOneOnOne.win_condition.l1 = "location";
	PChar.quest.LandAcademyOneOnOne.win_condition.l1.location = "FencingTown_Arena";
	PChar.quest.LandAcademyOneOnOne.function = "LandAcademyOneOnOne";
}

void LandAcademyOneOnOne(string _tmp)
{
	InterfaceStates.Buttons.Save.enable = false;
	Locations[FindLocation("FencingTown_ExitTown")].reload.l1.disable = true;
	Locations[FindLocation(PChar.location)].reload.l1.disable = true;

	PChar.AcademyLand = "Start";
	int iRandPlace = sti(PChar.AcademyLand.RandPlace);

	string sPlayerLocator, sEnemyLocator, sGroupLocator;

	int iDefenceType = 0;
	if(CheckAttribute(PChar, "AcademyLand.DefenceType"))
	{
		iDefenceType = sti(PChar.AcademyLand.DefenceType);
	}

	if(iDefenceType == 0)
	{
		if(iRandPlace == 0)
		{
			sPlayerLocator = "aloc2";
			sEnemyLocator = "aloc4";
			if(rand(1) == 1) { sPlayerLocator = "aloc2"; } else { sPlayerLocator = "aloc3"; }
			if(rand(1) == 1) { sEnemyLocator = "aloc4"; } else { sEnemyLocator = "aloc1"; }
		}
		else
		{
			sPlayerLocator = "aloc1";
			sEnemyLocator = "aloc3";
			if(rand(1) == 1) { sPlayerLocator = "aloc1"; } else { sPlayerLocator = "aloc4"; }
			if(rand(1) == 1) { sEnemyLocator = "aloc3"; } else { sEnemyLocator = "aloc2"; }
		}
	}
	else
	{
		if(iRandPlace == 0)
		{
			sPlayerLocator = "aloc8";
			sEnemyLocator = "aloc10";
			if(rand(1) == 1) { sPlayerLocator = "aloc8"; } else { sPlayerLocator = "aloc9"; }
			if(rand(1) == 1) { sEnemyLocator = "aloc10"; } else { sEnemyLocator = "aloc11"; }
		}
		else
		{
			sPlayerLocator = "aloc11";
			sEnemyLocator = "aloc9";
			if(rand(1) == 1) { sPlayerLocator = "aloc11"; } else { sPlayerLocator = "aloc10"; }
			if(rand(1) == 1) { sEnemyLocator = "aloc9"; } else { sEnemyLocator = "aloc8"; }
		}
	}

	int iChar;
	ref chr;

	string sSkill = "Fencing";
	if(CheckAttribute(PChar, "AcademyLand.Temp.Skill"))
	{
		sSkill = PChar.AcademyLand.Temp.Skill;
	}

	int iRank, iSkill, iHp, iEnergy;
	if(CheckAttribute(PChar, "AcademyLand.Temp.Rank")) { iRank = sti(PChar.AcademyLand.Temp.Rank); } else { iRank = sti(PChar.rank); }
	if(CheckAttribute(PChar, "AcademyLand.Temp.Skill.Quantity")) { iSkill = sti(PChar.AcademyLand.Temp.Skill.Quantity); } else { iSkill = sti(PChar.skill.(sSkill)); }
	if(CheckAttribute(PChar, "AcademyLand.Temp.HP")) { iHp = sti(PChar.AcademyLand.Temp.HP); } else { iHp = sti(LAi_GetCharacterMaxHP(PChar)); }
	if(CheckAttribute(PChar, "AcademyLand.Temp.Energy")) { iEnergy = sti(PChar.AcademyLand.Temp.Energy); } else { iEnergy = 100; }

	iHp += 200 + rand(50)+50;

	string sSaber = "blade1";

	if(CheckAttribute(PChar, "AcademyLand.Temp.Saber"))
	{
		sSaber = PChar.AcademyLand.Temp.Saber;
	}

	iChar = NPC_GenerateCharacterIndep("AcademyLandEnemy_1", "pofficer", "man", "man", iRank, PIRATE, 0, false);
	CreateModel(iChar, "pofficer", MAN);

	chr = &Characters[iChar];
	SetRandSPECIAL(chr);
	chr.rank = iRank;
	chr.skill.(sSkill) = iSkill;
	LAi_SetHP(chr, stf(iHp), stf(iHp));
	SetEnergyQty(chr, stf(iEnergy), stf(iEnergy));
	chr.LandAcademy = true;
	chr.LandAcademy.Enemy = true;

	RemoveCharacterEquip(chr, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(chr, GUN_ITEM_TYPE);

	DeleteAttribute(chr, "items");

	GiveItem2Character(chr, sSaber);
	EquipCharacterByItem(chr, sSaber);

	ChangeCharacterAddressGroup(chr, PChar.location, "rld", sEnemyLocator);

	LAi_SetWarriorType(chr);
	LAi_SetFightMode(chr, true);
	LAi_group_MoveCharacter(chr, "EnemyFight");

	RemoveCharacterEquip(PChar, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
	GiveItem2Character(PChar, sSaber);
	EquipCharacterByItem(PChar, sSaber);
	ChangeCharacterAddressGroup(PChar, PChar.location, "rld", sPlayerLocator);

	LAi_SetPlayerType(PChar);
	LAi_SetFightMode(PChar, true);
	PChar.LandAcademy.Player = true;

	LAi_NPC_EquipPerk(chr, "fantom");
	SetCharacterPerk(chr, "Energaiser");
	SetCharacterPerk(PChar, "Energaiser");

	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	Log_Info("Тренировка началась. Необходимо ликвидировать соперника!");
}


