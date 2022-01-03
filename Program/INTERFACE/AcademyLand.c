int iCheckTypeCount = 0;
int iCheckDefenceTypeCount = 0;
int iCheckSaberTypeCount = 1;
int iCheckEnemyLevelCount = 0;
int iCheckEnablePotionCount = 0;
int iCheckEnableFoodCount = 0;

int idLngFile = 0;
void InitInterface(string iniName)
{
	GameInterface.title = "titleAcademyLand";

    	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	GameInterface.SET_RANK.str = 1;
	GameInterface.SET_SKILL.str = 50;
	GameInterface.SET_HP.str = 100;
	GameInterface.SET_ENERGY.str = 90;

	SetBattleTypeInformation();
	SetEquipmentInformation();
	SetEnemyDetailsInformation();

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("PlayerCrewQuantityTempUptade","PlayerCrewQuantityTempUptade",0);
	SetEventHandler("EnemyCrewQuantityTempUptade","EnemyCrewQuantityTempUptade",0);
	SetEventHandler("RankUptade","RankUptade",0);
	SetEventHandler("SkillUptade","SkillUptade",0);
	SetEventHandler("HpUptade","HpUptade",0);
	SetEventHandler("EnergyUptade","EnergyUptade",0);
}

void ProcessBreakExit()
{
	IDoExit(RC_INTERFACE_SALARY_EXIT);
}

void ProcessCancelExit()
{
	IDoExit(RC_INTERFACE_SALARY_EXIT);
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("PlayerCrewQuantityTempUptade","PlayerCrewQuantityTempUptade");
	DelEventHandler("EnemyCrewQuantityTempUptade","EnemyCrewQuantityTempUptade");
	DelEventHandler("RankUptade","RankUptade");
	DelEventHandler("SkillUptade","SkillUptade");
	DelEventHandler("HpUptade","HpUptade");
	DelEventHandler("EnergyUptade","EnergyUptade");

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	RankUptade();
	HpUptade();

	switch(nodName)
	{
		case "BATTLE_TYPE_LEFT":
			if(comName=="activate" || comName=="click")
			{
				ChangeBattleType(true);
			}
		break;

		case "BATTLE_TYPE_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				ChangeBattleType(false);
			}
		break;

		case "BATTLE_DEFENCE_TYPE_LEFT":
			if(comName=="activate" || comName=="click")
			{
				ChangeDefenceType(true);
			}
		break;

		case "BATTLE_DEFENCE_TYPE_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				ChangeDefenceType(false);
			}
		break;

		case "BATTLE_SABER_TYPE_LEFT":
			if(comName=="activate" || comName=="click")
			{
				ChangeSaberType(true);
			}
		break;

		case "BATTLE_SABER_TYPE_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				ChangeSaberType(false);
			}
		break;

		case "ENEMY_LEVEL_LEFT":
			if(comName=="activate" || comName=="click")
			{
				ChangeEnemyLevelType(true);
			}
		break;

		case "ENEMY_LEVEL_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				ChangeEnemyLevelType(false);
			}
		break;

		case "ENABLE_POTION_LEFT":
			if(comName=="activate" || comName=="click")
			{
				ChangeEnablePotionType(true);
			}
		break;

		case "ENABLE_POTION_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				ChangeEnablePotionType(false);
			}
		break;

		case "ENABLE_FOOD_LEFT":
			if(comName=="activate" || comName=="click")
			{
				ChangeEnableFoodType(true);
			}
		break;

		case "ENABLE_FOOD_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				ChangeEnableFoodType(false);
			}
		break;

		case "RESET_ALL":
			if(comName=="activate" || comName=="click")
			{
				ResetAll();
			}
		break;

		case "OK":
			if(comName=="activate" || comName=="click")
			{
				AcademyLandDone();
			}
		break;
	}
}

//---------------------------------------------------------------------
void ChangeBattleType(bool bLeft)
{
	if(bLeft)
	{
		iCheckTypeCount--;
	}
	else
	{
		iCheckTypeCount++;
	}

	if(iCheckTypeCount < 0)
	{
		iCheckTypeCount = 2;
	}

	if(iCheckTypeCount > 2)
	{
		iCheckTypeCount = 0;
	}

	SetBattleTypeInformation();
}

void ChangeDefenceType(bool bLeft)
{
	if(bLeft)
	{
		iCheckDefenceTypeCount--;
	}
	else
	{
		iCheckDefenceTypeCount++;
	}

	if(iCheckDefenceTypeCount < 0)
	{
		iCheckDefenceTypeCount = 1;
	}

	if(iCheckDefenceTypeCount > 1)
	{
		iCheckDefenceTypeCount = 0;
	}

	SetBattleTypeInformation();
}

void ChangeSaberType(bool bLeft)
{
	if(bLeft)
	{
		iCheckSaberTypeCount--;
	}
	else
	{
		iCheckSaberTypeCount++;
	}

	if(iCheckSaberTypeCount < 1)
	{
		iCheckSaberTypeCount = 15;
	}

	if(iCheckSaberTypeCount > 15)
	{
		iCheckSaberTypeCount = 1;
	}

	SetEquipmentInformation();
	SetEnemyDetailsInformation();
}

void ChangeEnemyLevelType(bool bLeft)
{
	if(bLeft)
	{
		iCheckEnemyLevelCount--;
	}
	else
	{
		iCheckEnemyLevelCount++;
	}

	if(iCheckEnemyLevelCount < 0)
	{
		iCheckEnemyLevelCount = 2;
	}

	if(iCheckEnemyLevelCount > 2)
	{
		iCheckEnemyLevelCount = 0;
	}

	SetEnemyDetailsInformation();
}

void ChangeEnablePotionType(bool bLeft)
{
	if(bLeft)
	{
		iCheckEnablePotionCount--;
	}
	else
	{
		iCheckEnablePotionCount++;
	}

	if(iCheckEnablePotionCount < 0)
	{
		iCheckEnablePotionCount = 1;
	}

	if(iCheckEnablePotionCount > 1)
	{
		iCheckEnablePotionCount = 0;
	}

	SetEnemyDetailsInformation();
}

void ChangeEnableFoodType(bool bLeft)
{
	if(bLeft)
	{
		iCheckEnableFoodCount--;
	}
	else
	{
		iCheckEnableFoodCount++;
	}

	if(iCheckEnableFoodCount < 0)
	{
		iCheckEnableFoodCount = 1;
	}

	if(iCheckEnableFoodCount > 1)
	{
		iCheckEnableFoodCount = 0;
	}

	SetEnemyDetailsInformation();
}

//---------------------------------------------------------------------

void SetBattleTypeInformation()
{
	CreateString(true,"BattleTypeHeader", "Тип тренировки", FONT_CAPTION, COLOR_NORMAL, 390,42,SCRIPT_ALIGN_CENTER,1.2);

	string sType = "";

	switch(iCheckTypeCount)
	{
		case 0: sType = "Захват форта с суши"; break;
		case 1: sType = "Стенка на стенку"; break;
		case 2: sType = "Один на один"; break;
	}

	SetFormatedText("BATTLE_TYPE_TEXT", sType);

	CreateString(true,"PlayerCrewQuantity", "Кол-во союзников: ", FONT_CAPTION, COLOR_NORMAL, 400,95,SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"EnemyCrewQuantity", "Кол-во противников: ", FONT_CAPTION, COLOR_NORMAL, 400,132,SCRIPT_ALIGN_LEFT,1.0);

	int iPlayerCrew = 0;
	int iEnemyCrew = 0;

	switch(iCheckTypeCount)
	{
		case 0: iPlayerCrew = 29; iEnemyCrew = 30; break;
		case 1: iPlayerCrew = 9; iEnemyCrew = 10; break;
		case 2: iPlayerCrew = 0; iEnemyCrew = 1; break;
	}

	GameInterface.PLAYER_CREW_QUANTITY.str = iPlayerCrew;
	GameInterface.ENEMY_CREW_QUANTITY.str = iEnemyCrew;

	//--------------------------------------------------------

	string sDefenceType = "";
	switch(iCheckDefenceTypeCount)
	{
		case 0: if(iCheckTypeCount == 0) sDefenceType = "Нападающая сторона"; else sDefenceType = "На разбитом здании"; break;
		case 1: if(iCheckTypeCount == 0) sDefenceType = "Защищающая сторона"; else sDefenceType = "Около разбитого здания"; break;
	}

	SetFormatedText("BATTLE_DEFENCE_TYPE_TEXT", sDefenceType);
	SetCostInfo();
}

void SetEquipmentInformation()
{
	CreateString(true,"EquipmentHeader", "Экипировка", FONT_CAPTION, COLOR_NORMAL, 390,173,SCRIPT_ALIGN_CENTER,1.2);

	//--------------------------------------------------------
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	string sSaber = GetSaberNameFromCount();

	ref rSaber = &Items[FindItem(sSaber)];

	string sSaberName = LanguageConvertString(idLngFile, rSaber.name);
	string sSaberDescribe = GetItemDescribe(FindItem(sSaber));
	string sSaberPicture = "itm" + rSaber.picIndex;
	string sSaberTexture = rSaber.picTexture;

	SetFormatedText("BATTLE_SABER_NAME_TYPE_TEXT", sSaberName);
	SetFormatedText("BATTLE_SABER_TYPE_TEXT", sSaberDescribe);
	SetNewGroupPicture("BATTLE_SABER_TYPE_PICTURE", sSaberTexture, sSaberPicture);

	LanguageCloseFile(idLngFile);
}

void SetEnemyDetailsInformation()
{
	CreateString(true,"EnemyDetailsHeader", "Параметры соперника", FONT_CAPTION, COLOR_NORMAL, 390,347,SCRIPT_ALIGN_CENTER,1.2);

	string sEnemyLevel = GetEnemyLevel();
	SetFormatedText("ENEMY_LEVEL_TEXT", sEnemyLevel);

	string sEnablePotion = GetEnablePotion();
	SetFormatedText("ENABLE_POTION_TEXT", sEnablePotion);

	string sEnableFood = GetEnableFood();
	SetFormatedText("ENABLE_FOOD_TEXT", sEnableFood);

	//----------------------------------------------------------

	string sSkill = XI_ConvertString(GetSkillForEnemyFromSaber());

	CreateString(true,"EnemyRank", "Ранг: ", FONT_CAPTION, COLOR_NORMAL, 395,390,SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"EnemySkill", sSkill + ": ", FONT_CAPTION, COLOR_NORMAL, 395,425,SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"EnemyHP", "Примерное кол-во жизни: ", FONT_CAPTION, COLOR_NORMAL, 395,460,SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"EnemyEnergy", "Примерное кол-во энергии: ", FONT_CAPTION, COLOR_NORMAL, 395,495,SCRIPT_ALIGN_LEFT,1.0);

	GetEnemyDetails();
	SetCostInfo();
}

void SetCostInfo()
{
	int iMoney = GetCost();
	CreateString(true,"AcademyLandCost", "Цена: " + iMoney, FONT_NORMAL, argb(255,255,255,128), 360,528,SCRIPT_ALIGN_LEFT,1.0);

	if(sti(PChar.Money) >= iMoney)
	{
		SetSelectable("OK", true);
	}
	else
	{
		SetSelectable("OK", false);
	}
}

///////////////////////////////////////////////////////////////////////////////////
// other functions
///////////////////////////////////////////////////////////////////////////////////
int GetCost()
{
	int iSaberCost = 0;
	string sSaberType = GetSaberNameFromCount();
	switch(Items[FindItem(sSaberType)].FencingType)
	{
		case "FencingLight": iSaberCost = 15; break;
		case "Fencing": iSaberCost = 30; break;
		case "FencingHeavy": iSaberCost = 50; break;
	}

	int iRank = GetRank(PChar, 0) * 250;
	int iQty = sti(GameInterface.PLAYER_CREW_QUANTITY.str) + sti(GameInterface.ENEMY_CREW_QUANTITY.str) + 1;
	int iAmmoCost = iQty * iSaberCost;

	iQty = (sti(GameInterface.PLAYER_CREW_QUANTITY.str) + sti(GameInterface.ENEMY_CREW_QUANTITY.str) + 1) * 50;
	int iMoney = iRank + iQty + iAmmoCost;

	return iMoney;
}

string GetSaberNameFromCount()
{
	switch(iCheckSaberTypeCount)
	{
		case 1: return "blade1"; break;
		case 2: return "blade4"; break;
		case 3: return "blade6"; break;
		case 4: return "blade7"; break;
		case 5: return "blade9"; break;
		case 6: return "blade11"; break;
		case 7: return "blade12"; break;
		case 8: return "blade16"; break;
		case 9: return "blade18"; break;
		case 10: return "blade22"; break;
		case 11: return "blade23"; break;
		case 12: return "blade25"; break;
		case 13: return "blade35"; break;
		case 14: return "topor3"; break;
		case 15: return "topor1"; break;
	}
}

string GetEnemyLevel()
{
	switch(iCheckEnemyLevelCount)
	{
		case 0: return "Слабый соперник"; break;
		case 1: return "Равный соперник"; break;
		case 2: return "Сильный соперник"; break;
	}
}

string GetEnablePotion()
{
	switch(iCheckEnablePotionCount)
	{
		case 0: return "Запретить эликсиры"; break;
		case 1: return "Разрешить эликсиры"; break;
	}
}

string GetEnableFood()
{
	switch(iCheckEnableFoodCount)
	{
		case 0: return "Запретить еду"; break;
		case 1: return "Разрешить еду"; break;
	}
}

void PlayerCrewQuantityTempUptade()
{
	if(iCheckTypeCount == 0)
	{
		if(sti(GameInterface.PLAYER_CREW_QUANTITY.str) > 29)
		{
			GameInterface.PLAYER_CREW_QUANTITY.str = 29;
		}

		if(sti(GameInterface.PLAYER_CREW_QUANTITY.str) < 0)
		{
			GameInterface.PLAYER_CREW_QUANTITY.str = 0;
		}
	}
	else
	{
		if(iCheckTypeCount == 1)
		{
			if(iCheckDefenceTypeCount == 0)
			{
				if(sti(GameInterface.PLAYER_CREW_QUANTITY.str) > 9)
				{
					GameInterface.PLAYER_CREW_QUANTITY.str = 9;
				}
			}
			else
			{
				if(sti(GameInterface.PLAYER_CREW_QUANTITY.str) > 14)
				{
					GameInterface.PLAYER_CREW_QUANTITY.str = 14;
				}
			}

			if(sti(GameInterface.PLAYER_CREW_QUANTITY.str) < 0)
			{
				GameInterface.PLAYER_CREW_QUANTITY.str = 0;
			}
		}
		else
		{
			GameInterface.PLAYER_CREW_QUANTITY.str = 0;
		}
	}
}

void EnemyCrewQuantityTempUptade()
{
	if(iCheckTypeCount == 0)
	{
		if(sti(GameInterface.ENEMY_CREW_QUANTITY.str) > 30)
		{
			GameInterface.ENEMY_CREW_QUANTITY.str = 30;
		}

		if(sti(GameInterface.ENEMY_CREW_QUANTITY.str) <= 0)
		{
			GameInterface.ENEMY_CREW_QUANTITY.str = 1;
		}
	}
	else
	{
		if(iCheckTypeCount == 1)
		{
			if(iCheckDefenceTypeCount == 0)
			{
				if(sti(GameInterface.ENEMY_CREW_QUANTITY.str) > 10)
				{
					GameInterface.ENEMY_CREW_QUANTITY.str = 10;
				}
			}
			else
			{
				if(sti(GameInterface.ENEMY_CREW_QUANTITY.str) > 15)
				{
					GameInterface.ENEMY_CREW_QUANTITY.str = 15;
				}
			}

			if(sti(GameInterface.ENEMY_CREW_QUANTITY.str) <= 0)
			{
				GameInterface.ENEMY_CREW_QUANTITY.str = 1;
			}
		}
		else
		{
			GameInterface.ENEMY_CREW_QUANTITY.str = 1;
		}
	}
}

void ResetAll()
{
	iCheckTypeCount = 0;
	iCheckDefenceTypeCount = 0;
	iCheckSaberTypeCount = 0;
	iCheckEnemyLevelCount = 0;
	iCheckEnablePotionCount = 0;
	iCheckEnableFoodCount = 0;

	GameInterface.SET_RANK.str = 1;
	GameInterface.SET_SKILL.str = 50;
	GameInterface.SET_HP.str = 100;
	GameInterface.SET_ENERGY.str = 90;

	SetBattleTypeInformation();
	SetEquipmentInformation();
	SetEnemyDetailsInformation();
}

bool CheckEnableCrewQuantity()
{
	int iPlayerCrew, iEnemyCrew;
	switch(iCheckTypeCount)
	{
		case 0: iPlayerCrew = 29; iEnemyCrew = 30; break;
		case 1: if(iCheckDefenceTypeCount == 0) iPlayerCrew = 9; iEnemyCrew = 10; else iPlayerCrew = 14; iEnemyCrew = 15; break;
		case 2: iPlayerCrew = 0; iEnemyCrew = 1; break;
	}

	int iPlayerCrewQuantityInString = sti(GameInterface.PLAYER_CREW_QUANTITY.str);
	int iEnemyCrewQuantityInString = sti(GameInterface.ENEMY_CREW_QUANTITY.str);

	if(iPlayerCrewQuantityInString > iPlayerCrew || iEnemyCrewQuantityInString > iEnemyCrew)
	{
		return false;
	}

	return true;
}

string GetSkillForEnemyFromSaber()
{
	string sSaber = GetSaberNameFromCount();
	ref Saber = &Items[FindItem(sSaber)];

	if(CheckAttribute(Saber, "FencingType"))
	{
		return Saber.FencingType;
	}

	return "Fencing";
}

void GetEnemyDetails()
{
	string sSkill = GetSkillForEnemyFromSaber();
	int iSkill = sti(PChar.Skill.(sSkill));
	int iRank = sti(PChar.rank);
	int iHp = sti(LAi_GetCharacterMaxHP(PChar));
	int iEnergy = sti(LAi_GetCharacterMaxEnergy(PChar));

	int iSkillBonus = 0;
	int iRankBonus = 0;
	int iHpBonus = 0;
	int iEnergyBonus = 0;

	switch(iCheckEnemyLevelCount)
	{
		case 0:
			iSkillBonus = -25;
			iRankBonus = -3;
			iHpBonus = -10;
			iEnergyBonus = -10;
		break;

		case 1:
			iSkillBonus = 25;
			iRankBonus = 3;
			iHpBonus = 10;
			iEnergyBonus = 10;
		break;

		case 2:
			iSkillBonus = 50;
			iRankBonus = 5;
			iHpBonus = 20;
			iEnergyBonus = 30;
		break;
	}

	iSkill += iSkillBonus;
	iRank += iRankBonus;
	iHp += iHpBonus;
	iEnergy += iEnergyBonus;

	if(iSkill > 100) { iSkill = 100; }
	if(iSkill < 20) { iSkill = 20; }

	if(iRank > sti(pchar.rank)+10) { iRank = sti(pchar.rank)+10; }
	if(iRank < 5) { iRank = 5; }

	if(iHp > 500) { iHp = 500; }
	if(iHp < 30) { iHp = 30; }

	if(iEnergy > 300) { iEnergy = 300; }
	if(iEnergy < 40) { iEnergy = 40; }

	GameInterface.SET_SKILL.str = iSkill;
	GameInterface.SET_RANK.str = iRank;
	GameInterface.SET_HP.str = iHp;
	GameInterface.SET_ENERGY.str = iEnergy;
}

void RankUptade()
{
	int iString = sti(GameInterface.SET_RANK.str);

	if(iString > sti(pchar.rank)+10) { iString = sti(pchar.rank)+10; }
	if(iString < 5) { iString = 5; }

	GameInterface.SET_RANK.str = iString;
}

void SkillUptade()
{
	int iString = sti(GameInterface.SET_SKILL.str);

	if(iString > 100) { iString = 100; }
	if(iString < 20) { iString = 20; }

	GameInterface.SET_SKILL.str = iString;
}

void HpUptade()
{
	int iString = sti(GameInterface.SET_HP.str);

	if(iString > 500) { iString = 500; }
	if(iString < 30) { iString = 30; }

	GameInterface.SET_HP.str = iString;
}

void EnergyUptade()
{
	int iString = sti(GameInterface.SET_ENERGY.str);

	if(iString > 300) { iString = 300; }
	if(iString < 40) { iString = 40; }

	GameInterface.SET_ENERGY.str = iString;
}

//////////////////////////////////////////////////////////////////////////////////
// DONE
//////////////////////////////////////////////////////////////////////////////////
void AcademyLandDone()
{
	RankUptade();
	SkillUptade();
	HpUptade();
	EnergyUptade();

	if(!CheckEnableCrewQuantity())
	{
		PlayerCrewQuantityTempUptade();
		EnemyCrewQuantityTempUptade();
		return;
	}

	int iMoney = GetCost();
	if(sti(PChar.Money) < iMoney)
	{
		return;
	}
	else
	{
		AddMoneyToCharacter(PChar, -iMoney);
	}

	int iRank = sti(GameInterface.SET_RANK.str);
	int iSkill = sti(GameInterface.SET_SKILL.str);
	int iHp = sti(GameInterface.SET_HP.str);
	int iEnergy = sti(GameInterface.SET_ENERGY.str);

	int iHpBonus = (iRank * 3) + (rand(5) * 3);
	int iEnergyBonus = iRank * 3;

	iHp += iHpBonus;
	iEnergy += iEnergyBonus;

	GameInterface.SET_HP.str = iHp;
	GameInterface.SET_ENERGY.str = iEnergy;

	HpUptade();
	EnergyUptade();

	iHp = sti(GameInterface.SET_HP.str);
	iEnergy = sti(GameInterface.SET_ENERGY.str);

	PChar.AcademyLand.Temp.Rank = iRank;
	PChar.AcademyLand.Temp.HP = iHp;
	PChar.AcademyLand.Temp.Energy = iEnergy;

	string sSkill = GetSkillForEnemyFromSaber();
	PChar.AcademyLand.Temp.Skill = sSkill;
	PChar.AcademyLand.Temp.Skill.Quantity = iSkill;

	int iPlayerCrew = sti(GameInterface.PLAYER_CREW_QUANTITY.str);
	int iEnemyCrew = sti(GameInterface.ENEMY_CREW_QUANTITY.str);

	PChar.AcademyLand.Temp.PlayerCrew = iPlayerCrew;
	PChar.AcademyLand.Temp.EnemyCrew = iEnemyCrew;

	string sSaber = GetSaberNameFromCount();
	PChar.AcademyLand.Temp.Saber = sSaber;

	PChar.AcademyLand.Temp.EnablePotion = iCheckEnablePotionCount;
	PChar.AcademyLand.Temp.EnableFood = iCheckEnableFoodCount;

	PChar.AcademyLand = "Generate";
	PChar.AcademyLand.Can = false;
	PChar.AcademyLand.Begin = true;

	PChar.AcademyLand.TrainingType = iCheckTypeCount;
	PChar.AcademyLand.DefenceType = iCheckDefenceTypeCount;

	AcademyLandGenerateEnd();
	ProcessBreakExit();
}
