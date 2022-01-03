int iCheckBattleType = 0;
int iCheckBattleSaberType = 0;
int iCheckOddsPairs = 1;
int iCheckSaberTypeCount = 1;
int oddsp1 = 0;
int oddsp2 = 0;
int oddsp3 = 0;

int idLngFile = 0;

void InitInterface_B(string iniName, bool bTournamentResult)
{
	GameInterface.title = "titleArena";

    	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	if(!bTournamentResult)
	{
		SetNodeUsing("FRAME2", false);
		SetNodeUsing("BORDERS_3", false);

		GameInterface.DUEL_ODD.str = 0;
		GameInterface.ODDS_ODD.str = 0;
		SetBattleTypeInformation();
		SetEquipmentInformation();
	}
	else
	{
		SetTournamentResultInfo();
	}

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("DuelOddTemp","DuelOddTemp",0);
	SetEventHandler("OddsOddTemp","OddsOddTemp",0);
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
	DelEventHandler("DuelOddTemp","DuelOddTemp");
	DelEventHandler("OddsOddTemp","OddsOddTemp");

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);

	if(CheckAttribute(PChar, "Arena.Tournament.InterfacePause"))
	{
		if(PChar.Arena.Tournament.InterfacePause == true)
		{
			if(PChar.Arena.Tournament.Temp.InterfaceStage == "1_4")
			{
				PChar.Arena.Tournament.Temp.Stage = 1;
				PChar.Arena.Tournament.Temp.StageTemp = 1;
				ArenaTournamentGoStart(1, 1);
				ArenaTournamentStartNewBattle();
			}

			if(PChar.Arena.Tournament.Temp.InterfaceStage == "1_2")
			{
				PChar.Arena.Tournament.Temp.Stage = 2;
				PChar.Arena.Tournament.Temp.StageTemp = 1;
				ArenaTournamentGoStart(2, 1);
				ArenaTournamentStartNewBattle();
			}

			if(PChar.Arena.Tournament.Temp.InterfaceStage == "final")
			{
				PChar.Arena.Tournament.Temp.Stage = 3;
				PChar.Arena.Tournament.Temp.StageTemp = 1;
				ArenaTournamentGoStart(3, 1);
				ArenaTournamentStartNewBattle();
			}

			PChar.Arena.Tournament.InterfacePause = false;
			PChar.Arena.Tournament.Temp.StagePause = false;
		}
	}
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	if(nodName == "ETAP_1_YES" || nodName == "ETAP_2_YES" || nodName == "ETAP_3_YES" || nodName == "ETAP_4_YES" || nodName == "ETAP_5_YES"
	|| nodName == "ETAP_1_NO" || nodName == "ETAP_2_NO" || nodName == "ETAP_3_NO" || nodName == "ETAP_4_NO" || nodName == "ETAP_5_NO")
	{
		CheckEnableEtap(nodName);
		return;
	}

	if(nodName == "ODDS_CHAR_1_YES" || nodName == "ODDS_CHAR_2_YES")
	{
		CheckEnableOddCharacter(nodName);
		return;
	}

	switch(nodName)
	{
		case "BATTLE_SABER_TYPE_LEFT":
			if(comName=="activate" || comName=="click")
			{
				CheckBattleSaberType(true);
			}
		break;

		case "BATTLE_SABER_TYPE_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				CheckBattleSaberType(false);
			}
		break;

		case "BATTLE_TYPE_LEFT":
			if(comName=="activate" || comName=="click")
			{
				CheckBattleType(true);
			}
		break;

		case "BATTLE_TYPE_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				CheckBattleType(false);
			}
		break;

		case "ODDS_PAIRS_LEFT":
			if(comName=="activate" || comName=="click")
			{
				CheckOddsPairs(true);
			}
		break;

		case "ODDS_PAIRS_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				CheckOddsPairs(false);
			}
		break;

		case "DUEL_ODD_YES":
			if(comName=="activate" || comName=="click")
			{
				AcceptOdd("Duel");
			}
		break;

		case "DUEL_ODD_NO":
			if(comName=="activate" || comName=="click")
			{
				ResetOdd("Duel");
			}
		break;


		case "ODDS_ODD_YES":
			if(comName=="activate" || comName=="click")
			{
				AcceptOdd("Odds");
			}
		break;

		case "ODDS_ODD_NO":
			if(comName=="activate" || comName=="click")
			{
				ResetOdd("Odds");
			}
		break;

		case "RESET_ALL":
			if(comName=="activate" || comName=="click")
			{
				ResetAllOperations();
			}
		break;

		case "OK":
			if(comName=="activate" || comName=="click")
			{
				StartArenaOperation();
			}
		break;
	}
}

void CheckBattleType(bool bLeft)
{
	if(bLeft)
	{
		iCheckBattleType--;
	}
	else
	{
		iCheckBattleType++;
	}

	if(iCheckBattleType > 3)
	{
		iCheckBattleType = 0;
	}

	if(iCheckBattleType < 0)
	{
		iCheckBattleType = 3;
	}

	SetBattleTypeInformation();
}

void CheckOddsPairs(bool bLeft)
{
	if(bLeft)
	{
		iCheckOddsPairs--;
	}
	else
	{
		iCheckOddsPairs++;
	}

	if(iCheckOddsPairs > 3)
	{
		iCheckOddsPairs = 1;
	}

	if(iCheckOddsPairs < 1)
	{
		iCheckOddsPairs = 3;
	}

	SetOddsInfo();
	SetEquipmentInformation();
}

void CheckBattleSaberType(bool bLeft)
{
	if (iCheckBattleType == 2)
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
			iCheckSaberTypeCount = 9;
		}

		if(iCheckSaberTypeCount > 9)
		{
			iCheckSaberTypeCount = 1;
		}
	}
	else
	{
		if(bLeft)
		{
			iCheckBattleSaberType--;
		}
		else
		{
			iCheckBattleSaberType++;
		}

		if(iCheckBattleSaberType > 2)
		{
			iCheckBattleSaberType = 0;
		}

		if(iCheckBattleSaberType < 0)
		{
			iCheckBattleSaberType = 2;
		}
	}

	SetEquipmentInformation();
	SetBattleTypeInformation();
}

//---------------------------------------------------------------------

void SetBattleTypeInformation()
{
	CreateString(true,"BattleTypeHeader", "Тип состязаний", FONT_CAPTION, COLOR_NORMAL, 390,42,SCRIPT_ALIGN_CENTER,1.2);

	string sBattleType = GetBattleType();
	SetFormatedText("BATTLE_TYPE_TEXT", sBattleType);

	CheckBattleInformation();
	SetEquipmentInformation();
}

void SetDuelInfo()
{
	int iCharacter = GetDuelCharacter();
	ref chr = &Characters[iCharacter];

	int iFaceID = sti(chr.FaceID);
	string sCharacterPicture = "face_" + iFaceID + ".tga";
	SetNewPicture("DUEL_CHARACTER_PICTURE", "INTERFACES\PORTRAITS\256\" + sCharacterPicture);

	SetNodeUsing("FRAME_CHARACTER_PICTURE", true);
	string sCharacterName = chr.name + " " + chr.lastname;
	SetFormatedText("DUEL_CHARACTER_NAME_TEXT", sCharacterName);

	SetTableInformation(chr);
    	Table_UpdateWindow("TABLE_DUEL_CHARACTER");

    	int iOdd = sti(PChar.Arena.Duel.MinOdd) * 2;
    	int iMinOdd = sti(PChar.Arena.Duel.MinOdd);
    	int iMaxOdd = sti(PChar.Arena.Duel.MaxOdd);

	CreateString(true,"Duel_Money_1", "Ваше золото: ", FONT_NORMAL, COLOR_NORMAL, 180,320,SCRIPT_ALIGN_LEFT,0.9);
	CreateString(true,"Duel_Money_2", sti(PChar.money), FONT_NORMAL, argb(255,255,255,128), 300,320,SCRIPT_ALIGN_LEFT,0.9);

	CreateString(true,"Duel_Min_Odd_1", "Мин. / макс. ставка: ", FONT_NORMAL, COLOR_NORMAL, 180,335,SCRIPT_ALIGN_LEFT,0.9);
	CreateString(true,"Duel_Min_Odd_2", iMinOdd + "/" + iMaxOdd, FONT_NORMAL, argb(255,255,255,128), 300,335,SCRIPT_ALIGN_LEFT,0.9);

	CreateString(true,"Duel_Odd_1", "Ваша ставка: ", FONT_NORMAL, COLOR_NORMAL, 180,350,SCRIPT_ALIGN_LEFT,0.9);
	CreateString(true,"Duel_Odd_2", iOdd, FONT_NORMAL, argb(255,255,255,128), 300,350,SCRIPT_ALIGN_LEFT,0.9);

	CreateString(true,"Duel_Odd_Install", "Сделать ставку: ", FONT_CAPTION, COLOR_NORMAL, 425,319,SCRIPT_ALIGN_LEFT,1.0);

	AcceptOdd("Duel");
}

void SetTableInformation(ref chr)
{
    	SetEnergyToCharacter(chr);

	string sRow;
	for(int t=0; t < 5; t++)
	{
		if(t == 0)
		{
			sRow = "hr";
		}
		else
		{
			sRow = "tr" + t;
		}

		GameInterface.TABLE_DUEL_CHARACTER.(sRow).td1.icon.width = 32;
	    GameInterface.TABLE_DUEL_CHARACTER.(sRow).td1.icon.height = 32;
	    GameInterface.TABLE_DUEL_CHARACTER.(sRow).td1.icon.offset = "0, 0";
	    GameInterface.TABLE_DUEL_CHARACTER.(sRow).td2.scale = 0.9;
		GameInterface.TABLE_DUEL_CHARACTER.(sRow).td2.color = argb(255,255,255,255);
	}

	GameInterface.TABLE_DUEL_CHARACTER.hr.UserData.ID = "Duel_LeaderShip";
	GameInterface.TABLE_DUEL_CHARACTER.hr.td1.icon.group = "ICONS_SPEC";
    GameInterface.TABLE_DUEL_CHARACTER.hr.td1.icon.image = "leadership skill icon";
	GameInterface.TABLE_DUEL_CHARACTER.hr.td1.icon.offset = "0, 2";
    GameInterface.TABLE_DUEL_CHARACTER.hr.td2.str = XI_ConvertString("LeaderShip");
    GameInterface.TABLE_DUEL_CHARACTER.hr.td3.str = sti(chr.skill.LeaderShip);
	GameInterface.TABLE_DUEL_CHARACTER.hr.td3.color = argb(255,255,255,255);
	GameInterface.TABLE_DUEL_CHARACTER.hr.td3.scale = 0.90;
	GameInterface.TABLE_DUEL_CHARACTER.hr.td3.fontidx = 1;
	GameInterface.TABLE_DUEL_CHARACTER.hr.td3.textoffset = "-15,0";
	//-----------------------------------------------------------------------------
	string sSkill = GetSkillForEnemyFromSaber();
	GameInterface.TABLE_DUEL_CHARACTER.tr1.UserData.ID = "Duel_Skill";
	GameInterface.TABLE_DUEL_CHARACTER.tr1.td1.icon.group = "ICONS_SPEC";
    GameInterface.TABLE_DUEL_CHARACTER.tr1.td1.icon.image = sSkill + " skill icon";
    GameInterface.TABLE_DUEL_CHARACTER.tr1.td2.str = XI_ConvertString(sSkill);
    GameInterface.TABLE_DUEL_CHARACTER.tr1.td3.str = sti(chr.skill.(sSkill));
	GameInterface.TABLE_DUEL_CHARACTER.tr1.td3.color = argb(255,255,255,255);
	GameInterface.TABLE_DUEL_CHARACTER.tr1.td3.scale = 0.90;
	GameInterface.TABLE_DUEL_CHARACTER.tr1.td3.fontidx = 1;
	GameInterface.TABLE_DUEL_CHARACTER.tr1.td3.textoffset = "-15,0";
	//-----------------------------------------------------------------------------
	GameInterface.TABLE_DUEL_CHARACTER.tr2.UserData.ID = "Duel_HP";
	GameInterface.TABLE_DUEL_CHARACTER.tr2.td1.icon.group = "ICONS_CHAR";
    GameInterface.TABLE_DUEL_CHARACTER.tr2.td1.icon.image = "Life";
    GameInterface.TABLE_DUEL_CHARACTER.tr2.td2.str = XI_ConvertString("Life");
    GameInterface.TABLE_DUEL_CHARACTER.tr2.td1.icon.offset = "0, 2";
	GameInterface.TABLE_DUEL_CHARACTER.tr2.td3.str = MakeInt(LAi_GetCharacterHP(chr)) + " / " + MakeInt(LAi_GetCharacterMaxHP(chr));
	GameInterface.TABLE_DUEL_CHARACTER.tr2.td3.color = argb(255,255,255,255);
	GameInterface.TABLE_DUEL_CHARACTER.tr2.td3.scale = 1.0;
	GameInterface.TABLE_DUEL_CHARACTER.tr2.td3.fontidx = 2;
	GameInterface.TABLE_DUEL_CHARACTER.tr2.td3.textoffset = "-5,0";
	//-----------------------------------------------------------------------------
	GameInterface.TABLE_DUEL_CHARACTER.tr3.UserData.ID = "Duel_Energy";
	GameInterface.TABLE_DUEL_CHARACTER.tr3.td1.icon.group = "ICONS_CHAR";
    GameInterface.TABLE_DUEL_CHARACTER.tr3.td1.icon.image = "Energy";
    GameInterface.TABLE_DUEL_CHARACTER.tr3.td2.str = XI_ConvertString("Energy");
    GameInterface.TABLE_DUEL_CHARACTER.tr3.td1.icon.offset = "0, 2";
	GameInterface.TABLE_DUEL_CHARACTER.tr3.td3.str = sti(Lai_CharacterGetEnergy(chr)) + " / " + sti(LAi_GetCharacterMaxEnergy(chr));
	GameInterface.TABLE_DUEL_CHARACTER.tr3.td3.color = argb(255,255,255,255);
	GameInterface.TABLE_DUEL_CHARACTER.tr3.td3.scale = 1.0;
	GameInterface.TABLE_DUEL_CHARACTER.tr3.td3.fontidx = 2;
	GameInterface.TABLE_DUEL_CHARACTER.tr3.td3.textoffset = "-5,0";
	//-----------------------------------------------------------------------------
	GameInterface.TABLE_DUEL_CHARACTER.tr4.UserData.ID = "Duel_Odd";
	GameInterface.TABLE_DUEL_CHARACTER.tr4.td1.icon.group = "ICONS_SPEC";
    GameInterface.TABLE_DUEL_CHARACTER.tr4.td1.icon.image = "trade button";
	GameInterface.TABLE_DUEL_CHARACTER.tr4.td1.icon.width = 50;
    GameInterface.TABLE_DUEL_CHARACTER.tr4.td1.icon.height = 50;
    GameInterface.TABLE_DUEL_CHARACTER.tr4.td1.icon.offset = "-8, -8";
    GameInterface.TABLE_DUEL_CHARACTER.tr4.td2.str = "Ставка";
	GameInterface.TABLE_DUEL_CHARACTER.tr4.td3.str = sti(chr.Odd);
	GameInterface.TABLE_DUEL_CHARACTER.tr4.td3.color = argb(255,255,255,128);
	GameInterface.TABLE_DUEL_CHARACTER.tr4.td3.scale = 1.0;
	GameInterface.TABLE_DUEL_CHARACTER.tr4.td3.fontidx = 2;
	GameInterface.TABLE_DUEL_CHARACTER.tr4.td3.textoffset = "-5,0";
}

void SetEtapsInfo()
{
	SetNodeUsing("FRAME_CHARACTER_PICTURE", false);
	CreateString(true,"Etaps_No_1", "1", FONT_CAPTION, argb(255,255,255,128), 190,130,SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"Etaps_No_2", "2", FONT_CAPTION, argb(255,255,255,128), 340,130,SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"Etaps_No_3", "3", FONT_CAPTION, argb(255,255,255,128), 490,130,SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"Etaps_No_4", "4", FONT_CAPTION, argb(255,255,255,128), 260,249,SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"Etaps_No_5", "5", FONT_CAPTION, argb(255,255,255,128), 410,249,SCRIPT_ALIGN_LEFT,1.0);

	int iGold = 0;
	int iWinGold = 0;

	int iEtapMoney_1 = sti(PChar.Arena.Etaps.Etap_1.Cost);
	int iEtapMoney_2 = sti(PChar.Arena.Etaps.Etap_2.Cost);
	int iEtapMoney_3 = sti(PChar.Arena.Etaps.Etap_3.Cost);
	int iEtapMoney_4 = sti(PChar.Arena.Etaps.Etap_4.Cost);
	int iEtapMoney_5 = sti(PChar.Arena.Etaps.Etap_5.Cost);

	iWinGold = iEtapMoney_1 + iEtapMoney_2 + iEtapMoney_3 + iEtapMoney_4 + iEtapMoney_5;
	iGold = iWinGold / 5;

	PChar.Arena.Etaps.Prize = iWinGold;

	string sEtapType_1 = PChar.Arena.Etaps.Etap_1.Type;
	string sEtapType_2 = PChar.Arena.Etaps.Etap_2.Type;
	string sEtapType_3 = PChar.Arena.Etaps.Etap_3.Type;
	string sEtapType_4 = PChar.Arena.Etaps.Etap_4.Type;
	string sEtapType_5 = PChar.Arena.Etaps.Etap_5.Type;

	int iEtapQuantity_1 = sti(PChar.Arena.Etaps.Etap_1.Quantity);
	int iEtapQuantity_2 = sti(PChar.Arena.Etaps.Etap_2.Quantity);
	int iEtapQuantity_3 = sti(PChar.Arena.Etaps.Etap_3.Quantity);
	int iEtapQuantity_4 = sti(PChar.Arena.Etaps.Etap_4.Quantity);
	int iEtapQuantity_5 = sti(PChar.Arena.Etaps.Etap_5.Quantity);

	SetNewGroupPicture("ETAPS_PICTURE_1", "ARENA_ETAPS", sEtapType_1);
	SetNewGroupPicture("ETAPS_PICTURE_2", "ARENA_ETAPS", sEtapType_2);
	SetNewGroupPicture("ETAPS_PICTURE_3", "ARENA_ETAPS", sEtapType_3);
	SetNewGroupPicture("ETAPS_PICTURE_4", "ARENA_ETAPS", sEtapType_4);
	SetNewGroupPicture("ETAPS_PICTURE_5", "ARENA_ETAPS", sEtapType_5);

	CreateString(true,"Etaps_Money_1", iEtapMoney_1, FONT_CAPTION, argb(255,255,255,128), 305,205,SCRIPT_ALIGN_RIGHT,1.0);
	CreateString(true,"Etaps_Money_2", iEtapMoney_2, FONT_CAPTION, argb(255,255,255,128), 456,205,SCRIPT_ALIGN_RIGHT,1.0);
	CreateString(true,"Etaps_Money_3", iEtapMoney_3, FONT_CAPTION, argb(255,255,255,128), 604,205,SCRIPT_ALIGN_RIGHT,1.0);
	CreateString(true,"Etaps_Money_4", iEtapMoney_4, FONT_CAPTION, argb(255,255,255,128), 375,324,SCRIPT_ALIGN_RIGHT,1.0);
	CreateString(true,"Etaps_Money_5", iEtapMoney_5, FONT_CAPTION, argb(255,255,255,128), 525,324,SCRIPT_ALIGN_RIGHT,1.0);

	CreateString(true,"Etaps_Quantity_1", iEtapQuantity_1, FONT_CAPTION, argb(255,255,128,128), 190,205,SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"Etaps_Quantity_2", iEtapQuantity_2, FONT_CAPTION, argb(255,255,128,128), 340,205,SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"Etaps_Quantity_3", iEtapQuantity_3, FONT_CAPTION, argb(255,255,128,128), 490,205,SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"Etaps_Quantity_4", iEtapQuantity_4, FONT_CAPTION, argb(255,255,128,128), 260,324,SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"Etaps_Quantity_5", iEtapQuantity_5, FONT_CAPTION, argb(255,255,128,128), 410,324,SCRIPT_ALIGN_LEFT,1.0);

	CreateString(true,"Etaps_Payment_1", "Взнос за участие: ", FONT_NORMAL, COLOR_NORMAL, 545,250,SCRIPT_ALIGN_LEFT,0.9);
	CreateString(true,"Etaps_Payment_2", iGold, FONT_BOLD_NUMBERS, argb(255,255,255,128), 590,335,SCRIPT_ALIGN_CENTER,0.75);

	CreateString(true,"Etaps_HeroMoney_1", "Ваше золото: ", FONT_NORMAL, COLOR_NORMAL, 165,250,SCRIPT_ALIGN_LEFT,0.9);
	CreateString(true,"Etaps_HeroMoney_2", sti(PChar.money), FONT_BOLD_NUMBERS, argb(255,255,255,128), 200,335,SCRIPT_ALIGN_CENTER,0.75);

	CreateString(true,"Etaps_Win_Gold_1", "Предпологаемый выигрыш: ", FONT_NORMAL, COLOR_NORMAL, 265,355,SCRIPT_ALIGN_LEFT,0.9);
	CreateString(true,"Etaps_Win_Gold_2", sti(PChar.Arena.Etaps.Prize) + " пиастров", FONT_NORMAL, argb(255,255,255,128), 420,355,SCRIPT_ALIGN_LEFT,1.0);

	for(int e=1; e<=5; e++)
	{
		CheckEnableEtap("ETAP_" + e + "_NO");
	}
}

void SetTournamentInfo()
{
	CreateString(true,"Tournament_1_4_1", "1/4", FONT_CAPTION, argb(255,255,255,128), 220,90,SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"Tournament_1_4_2", "1/4", FONT_CAPTION, argb(255,255,255,128), 550,90,SCRIPT_ALIGN_LEFT,1.0);

	CreateString(true,"Tournament_1_2_1", "1/2", FONT_CAPTION, argb(255,255,255,128), 330,165,SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"Tournament_1_2_2", "1/2", FONT_CAPTION, argb(255,255,255,128), 450,165,SCRIPT_ALIGN_LEFT,1.0);

	CreateString(true,"Tournament_final", "Финал", FONT_CAPTION, argb(255,255,255,128), 380,235,SCRIPT_ALIGN_LEFT,1.0);

	if(GetCharacterIndex("Arena_Tournament_Character_1") == -1)
	{
		CreateString(true,"Tournament_NotGen", "Турниров пока не проводится.", FONT_NORMAL, argb(255,255,128,128), 305,125,SCRIPT_ALIGN_LEFT,1.0);
		SetSelectable("OK", false);
		return;
	}

	int iMoney = sti(PChar.Arena.Tournament.Money);
	CreateString(true,"Tournament_Win_Gold_1", "Призовой фонд: ", FONT_NORMAL, COLOR_NORMAL, 330,330,SCRIPT_ALIGN_LEFT,0.9);
	CreateString(true,"Tournament_Win_Gold_2", iMoney, FONT_NORMAL, argb(255,255,255,128), 430,330,SCRIPT_ALIGN_LEFT,0.9);

	CreateString(true,"Tournament_Cost_1", "Взнос за участие: ", FONT_NORMAL, COLOR_NORMAL, 330,345,SCRIPT_ALIGN_LEFT,0.9);
	CreateString(true,"Tournament_Cost_2", (iMoney / 8), FONT_NORMAL, argb(255,255,255,128), 430,345,SCRIPT_ALIGN_LEFT,0.9);

	CreateString(true,"Tournament_Money_1", "Ваши деньги: ", FONT_NORMAL, COLOR_NORMAL, 330,360,SCRIPT_ALIGN_LEFT,0.9);
	CreateString(true,"Tournament_Money_2", sti(PChar.money), FONT_NORMAL, argb(255,255,255,128), 430,360,SCRIPT_ALIGN_LEFT,0.9);


	string sName, sChar, str;
	int p=1;
	for(int n=1; n<=8; n++)
	{
		if(n == 8)
		{
			sChar = "Blaze";
		}
		else
		{
			sChar = "Arena_Tournament_Character_" + n;
		}

		p = GetTournamentPosition(sChar, "1_4");
		str = "TOURNAMENT_NAME_" + p;

		sName = Characters[GetCharacterIndex(sChar)].name + " " + Characters[GetCharacterIndex(sChar)].lastname;
		SetFormatedText(str, sName);
	}

	SetNodeUsing("BORDERS_2", true);

	if(sti(PChar.money) >= (iMoney / 8))
	{
		SetSelectable("OK", true);
	}
	else
	{
		SetSelectable("OK", false);
	}

}

void SetOddsInfo()
{
	string sOddsPairs = GetOddsPairs();
	SetFormatedText("ODDS_PAIRS_TEXT", sOddsPairs);

	int iAttack = GetArenaOddsCharacter(iCheckOddsPairs, 1);
	int iEnemy = GetArenaOddsCharacter(iCheckOddsPairs, 2);
	ref chr = &Characters[iAttack];

	int iFaceID = sti(chr.FaceID);
	string sCharacterPicture = "face_" + iFaceID + ".tga";
	SetNewPicture("ODDS_CHARACTER_1_PICTURE", "INTERFACES\PORTRAITS\256\" + sCharacterPicture);

	string sCharacterName = chr.name + " " + chr.lastname;
	SetFormatedText("ODDS_CHARACTER_1_NAME_TEXT", sCharacterName);

	chr = &Characters[iEnemy];
	iFaceID = sti(chr.FaceID);
	sCharacterPicture = "face_" + iFaceID + ".tga";
	SetNewPicture("ODDS_CHARACTER_2_PICTURE", "INTERFACES\PORTRAITS\256\" + sCharacterPicture);

	sCharacterName = chr.name + " " + chr.lastname;
	SetFormatedText("ODDS_CHARACTER_2_NAME_TEXT", sCharacterName);

	int iMaxOdd = sti(PChar.Arena.Odds.MaxOdd);
	int iMinOdd = sti(PChar.Arena.Odds.MinOdd);

	CreateString(true,"Odds_Money_1", "Ваше золото: ", FONT_NORMAL, COLOR_NORMAL, 180,320,SCRIPT_ALIGN_LEFT,0.9);
	CreateString(true,"Odds_Money_2", sti(PChar.money), FONT_NORMAL, argb(255,255,255,128), 300,320,SCRIPT_ALIGN_LEFT,0.9);

	CreateString(true,"Odds_Min_Odd_1", "Мин. / макс. ставка: ", FONT_NORMAL, COLOR_NORMAL, 180,335,SCRIPT_ALIGN_LEFT,0.9);
	CreateString(true,"Odds_Min_Odd_2", iMinOdd + "/" + iMaxOdd, FONT_NORMAL, argb(255,255,255,128), 300,335,SCRIPT_ALIGN_LEFT,0.9);

	CreateString(true,"Odds_Odd_1", "Ваша ставка: ", FONT_NORMAL, COLOR_NORMAL, 180,350,SCRIPT_ALIGN_LEFT,0.9);
	CreateString(true,"Odds_Odd_2", iMinOdd, FONT_NORMAL, argb(255,255,255,128), 300,350,SCRIPT_ALIGN_LEFT,0.9);

	CreateString(true,"Odds_Odd_Install", "Сделать ставку: ", FONT_CAPTION, COLOR_NORMAL, 425,319,SCRIPT_ALIGN_LEFT,1.0);

	SetOddsTableInformation(&Characters[iAttack], &Characters[iEnemy]);
    	Table_UpdateWindow("TABLE_ODDS_CHARACTERS");

    	CheckEnableOddCharacter("ODDS_CHAR_2_YES");
}


void SetOddsTableInformation(ref attack, ref enemy)
{
	string sRow;
	for(int t=0; t < 4; t++)
	{
		if(t == 0)
		{
			sRow = "hr";
		}
		else
		{
			sRow = "tr" + t;
		}

		GameInterface.TABLE_ODDS_CHARACTERS.(sRow).td2.icon.width = 32;
	    GameInterface.TABLE_ODDS_CHARACTERS.(sRow).td2.icon.height = 32;
	    GameInterface.TABLE_ODDS_CHARACTERS.(sRow).td2.icon.offset = "0, 0";
	    GameInterface.TABLE_ODDS_CHARACTERS.(sRow).td3.scale = 0.9;
		GameInterface.TABLE_ODDS_CHARACTERS.(sRow).td3.color = argb(255,255,255,255);
	}

	//-----------------------------------------------------------------------------
	string sSkill = GetSkillForEnemyFromSaber();
	GameInterface.TABLE_ODDS_CHARACTERS.hr.UserData.ID = "Odds_Skill_1";
	GameInterface.TABLE_ODDS_CHARACTERS.hr.td2.icon.group = "ICONS_SPEC";
	GameInterface.TABLE_ODDS_CHARACTERS.hr.td2.icon.image = sSkill + " skill icon";
    GameInterface.TABLE_ODDS_CHARACTERS.hr.td2.icon.offset = "-2, 0";
    GameInterface.TABLE_ODDS_CHARACTERS.hr.td1.str = sti(attack.skill.(sSkill));
	GameInterface.TABLE_ODDS_CHARACTERS.hr.td1.color = argb(255,255,255,255);
	GameInterface.TABLE_ODDS_CHARACTERS.hr.td1.scale = 0.90;
	GameInterface.TABLE_ODDS_CHARACTERS.hr.td1.fontidx = 1;
	GameInterface.TABLE_ODDS_CHARACTERS.hr.td1.textoffset = "-15,0";

    GameInterface.TABLE_ODDS_CHARACTERS.hr.td3.str = XI_ConvertString(sSkill);
    GameInterface.TABLE_ODDS_CHARACTERS.hr.td3.str = sti(enemy.skill.(sSkill));
	GameInterface.TABLE_ODDS_CHARACTERS.hr.td3.color = argb(255,255,255,255);
	GameInterface.TABLE_ODDS_CHARACTERS.hr.td3.scale = 0.90;
	GameInterface.TABLE_ODDS_CHARACTERS.hr.td3.fontidx = 1;
	GameInterface.TABLE_ODDS_CHARACTERS.hr.td3.textoffset = "-15,0";
	//-----------------------------------------------------------------------------
	GameInterface.TABLE_ODDS_CHARACTERS.tr1.UserData.ID = "Odds_HP";
	GameInterface.TABLE_ODDS_CHARACTERS.tr1.td2.icon.group = "ICONS_CHAR";
    GameInterface.TABLE_ODDS_CHARACTERS.tr1.td2.icon.image = "Life";
    GameInterface.TABLE_ODDS_CHARACTERS.tr1.td2.icon.offset = "-2, 2";
	GameInterface.TABLE_ODDS_CHARACTERS.tr1.td1.str = MakeInt(LAi_GetCharacterHP(attack)) + "/" + MakeInt(LAi_GetCharacterMaxHP(attack));
	GameInterface.TABLE_ODDS_CHARACTERS.tr1.td1.color = argb(255,255,255,255);
	GameInterface.TABLE_ODDS_CHARACTERS.tr1.td1.scale = 1.0;
	GameInterface.TABLE_ODDS_CHARACTERS.tr1.td1.fontidx = 2;
	GameInterface.TABLE_ODDS_CHARACTERS.tr1.td1.textoffset = "-5,0";
	GameInterface.TABLE_ODDS_CHARACTERS.tr1.td3.str = MakeInt(LAi_GetCharacterHP(enemy)) + "/" + MakeInt(LAi_GetCharacterMaxHP(enemy));
	GameInterface.TABLE_ODDS_CHARACTERS.tr1.td3.color = argb(255,255,255,255);
	GameInterface.TABLE_ODDS_CHARACTERS.tr1.td3.scale = 1.0;
	GameInterface.TABLE_ODDS_CHARACTERS.tr1.td3.fontidx = 2;
	GameInterface.TABLE_ODDS_CHARACTERS.tr1.td3.textoffset = "-5,0";
	//-----------------------------------------------------------------------------
	GameInterface.TABLE_ODDS_CHARACTERS.tr2.UserData.ID = "Odds_Energy";
	GameInterface.TABLE_ODDS_CHARACTERS.tr2.td2.icon.group = "ICONS_CHAR";
	GameInterface.TABLE_ODDS_CHARACTERS.tr2.td2.icon.image = "Energy";
    GameInterface.TABLE_ODDS_CHARACTERS.tr2.td2.icon.offset = "-2, 2";
	GameInterface.TABLE_ODDS_CHARACTERS.tr2.td1.str = sti(Lai_CharacterGetEnergy(attack)) + "/" + sti(LAi_GetCharacterMaxEnergy(attack));
	GameInterface.TABLE_ODDS_CHARACTERS.tr2.td1.color = argb(255,255,255,255);
	GameInterface.TABLE_ODDS_CHARACTERS.tr2.td1.scale = 1.0;
	GameInterface.TABLE_ODDS_CHARACTERS.tr2.td1.fontidx = 2;
	GameInterface.TABLE_ODDS_CHARACTERS.tr2.td1.textoffset = "-5,0";
	GameInterface.TABLE_ODDS_CHARACTERS.tr2.td3.str = sti(Lai_CharacterGetEnergy(enemy)) + "/" + sti(LAi_GetCharacterMaxEnergy(enemy));
	GameInterface.TABLE_ODDS_CHARACTERS.tr2.td3.color = argb(255,255,255,255);
	GameInterface.TABLE_ODDS_CHARACTERS.tr2.td3.scale = 1.0;
	GameInterface.TABLE_ODDS_CHARACTERS.tr2.td3.fontidx = 2;
	GameInterface.TABLE_ODDS_CHARACTERS.tr2.td3.textoffset = "-5,0";
	//-----------------------------------------------------------------------------
	GameInterface.TABLE_ODDS_CHARACTERS.tr3.UserData.ID = "Odds_Rate";
	GameInterface.TABLE_ODDS_CHARACTERS.tr3.td2.icon.group = "ICONS_SPEC";
    GameInterface.TABLE_ODDS_CHARACTERS.tr3.td2.icon.image = "trade button";
	GameInterface.TABLE_ODDS_CHARACTERS.tr3.td2.icon.width = 50;
    GameInterface.TABLE_ODDS_CHARACTERS.tr3.td2.icon.height = 50;
    GameInterface.TABLE_ODDS_CHARACTERS.tr3.td2.icon.offset = "-10, -7";
	GameInterface.TABLE_ODDS_CHARACTERS.tr3.td1.str = FloatToString(stf(attack.Arena.Odds.Rate), 2);
	GameInterface.TABLE_ODDS_CHARACTERS.tr3.td1.color = argb(255,255,255,128);
	GameInterface.TABLE_ODDS_CHARACTERS.tr3.td1.scale = 1.0;
	GameInterface.TABLE_ODDS_CHARACTERS.tr3.td1.fontidx = 2;
	GameInterface.TABLE_ODDS_CHARACTERS.tr3.td1.textoffset = "-5,0";
	GameInterface.TABLE_ODDS_CHARACTERS.tr3.td3.str = FloatToString(stf(enemy.Arena.Odds.Rate), 2);
	GameInterface.TABLE_ODDS_CHARACTERS.tr3.td3.color = argb(255,255,255,128);
	GameInterface.TABLE_ODDS_CHARACTERS.tr3.td3.scale = 1.0;
	GameInterface.TABLE_ODDS_CHARACTERS.tr3.td3.fontidx = 2;
	GameInterface.TABLE_ODDS_CHARACTERS.tr3.td3.textoffset = "-5,0";
}


void SetEquipmentInformation()
{
	CreateString(true,"EquipmentHeader", "Экипировка", FONT_CAPTION, COLOR_NORMAL, 390,382,SCRIPT_ALIGN_CENTER,1.2);

	//--------------------------------------------------------
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	string sSaber = GetSaberName();

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

void SetTournamentResultInfo()
{
	SetNodeUsing("FRAME1", false);
	SetNodeUsing("FRAME3", false);
	SetNodeUsing("FRAME_CHARACTER_PICTURE", false);
	SetNodeUsing("BATTLE_SABER_TYPE_PICTURE", false);
	SetNodeUsing("BATTLE_TYPE_LEFT", false);
	SetNodeUsing("BATTLE_TYPE_RIGHT", false);
	SetNodeUsing("BATTLE_TYPE_TEXT", false);
	SetNodeUsing("RESET_ALL", false);
	SetNodeUsing("CANCEL", false);
	SetNodeUsing("OK", false);

	SetNodeUsing("FRAME2", true);
	SetNodeUsing("BORDERS_3", true);

	DisableTournamentInfo(false);
	DisableDuelInfo(false);
	DisableEtapsInfo(false);
	DisableOddsInfo(false);

	SetNodeUsing("BATTLE_SABER_TYPE_LEFT", false);
	SetNodeUsing("BATTLE_SABER_TYPE_RIGHT", false);

	CreateString(true,"TournamentResultHeader", "Турнир", FONT_CAPTION, COLOR_NORMAL, 390,105,SCRIPT_ALIGN_CENTER,1.0);


	CreateString(true,"TournamentRes_1_4_1", "1/4", FONT_CAPTION, argb(255,255,255,128), 110,145,SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"TournamentRes_1_4_2", "1/4", FONT_CAPTION, argb(255,255,255,128), 650,145,SCRIPT_ALIGN_LEFT,1.0);

	CreateString(true,"TournamentRes_1_2_1", "1/2", FONT_CAPTION, argb(255,255,255,128), 250,145,SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"TournamentRes_1_2_2", "1/2", FONT_CAPTION, argb(255,255,255,128), 515,145,SCRIPT_ALIGN_LEFT,1.0);

	CreateString(true,"TournamentRes_final", "Финал", FONT_CAPTION, argb(255,255,255,128), 370,145,SCRIPT_ALIGN_LEFT,1.0);

	CreateString(true,"TournamentRes_1_4_Name_1", "", FONT_CAPTION, COLOR_NORMAL, 60,180,SCRIPT_ALIGN_LEFT,0.9);
	CreateString(true,"TournamentRes_1_4_Name_2", "", FONT_CAPTION, COLOR_NORMAL, 60,255,SCRIPT_ALIGN_LEFT,0.9);
	CreateString(true,"TournamentRes_1_4_Name_3", "", FONT_CAPTION, COLOR_NORMAL, 60,310,SCRIPT_ALIGN_LEFT,0.9);
	CreateString(true,"TournamentRes_1_4_Name_4", "", FONT_CAPTION, COLOR_NORMAL, 60,385,SCRIPT_ALIGN_LEFT,0.9);
	CreateString(true,"TournamentRes_1_4_Name_5", "", FONT_CAPTION, COLOR_NORMAL, 730,180,SCRIPT_ALIGN_RIGHT,0.9);
	CreateString(true,"TournamentRes_1_4_Name_6", "", FONT_CAPTION, COLOR_NORMAL, 730,255,SCRIPT_ALIGN_RIGHT,0.9);
	CreateString(true,"TournamentRes_1_4_Name_7", "", FONT_CAPTION, COLOR_NORMAL, 730,310,SCRIPT_ALIGN_RIGHT,0.9);
	CreateString(true,"TournamentRes_1_4_Name_8", "", FONT_CAPTION, COLOR_NORMAL, 730,385,SCRIPT_ALIGN_RIGHT,0.9);

	CreateString(true,"TournamentRes_1_2_Name_1", "", FONT_CAPTION, COLOR_NORMAL, 205,220,SCRIPT_ALIGN_LEFT,0.9);
	CreateString(true,"TournamentRes_1_2_Name_2", "", FONT_CAPTION, COLOR_NORMAL, 205,350,SCRIPT_ALIGN_LEFT,0.9);
	CreateString(true,"TournamentRes_1_2_Name_3", "", FONT_CAPTION, COLOR_NORMAL, 585,220,SCRIPT_ALIGN_RIGHT,0.9);
	CreateString(true,"TournamentRes_1_2_Name_4", "", FONT_CAPTION, COLOR_NORMAL, 590,350,SCRIPT_ALIGN_RIGHT,0.9);

	CreateString(true,"TournamentRes_Final_Name_1", "", FONT_CAPTION, COLOR_NORMAL, 335,280,SCRIPT_ALIGN_LEFT,0.9);
	CreateString(true,"TournamentRes_Final_Name_2", "", FONT_CAPTION, COLOR_NORMAL, 335,320,SCRIPT_ALIGN_LEFT,0.9);


	string sName, sChar, str;
	int p=1;

	if(PChar.Arena.Tournament.Temp.InterfaceStage == "1_4")
	{
		for(int n=1; n<=8; n++)
		{
			if(n == 8)
			{
				sChar = "Blaze";
			}
			else
			{
				sChar = "Arena_Tournament_Character_" + n;
			}

			p = GetTournamentPosition(sChar, "1_4");
			str = "TournamentRes_1_4_Name_" + p;

			sName = Characters[GetCharacterIndex(sChar)].name + " " + Characters[GetCharacterIndex(sChar)].lastname;
			GameInterface.strings.(str) = sName;

			if(n == 8)
			{
				ChangeStringColor(str, argb(255,255,255,128));
			}

		}
	}

	if(PChar.Arena.Tournament.Temp.InterfaceStage == "1_2")
	{
		for(n=1; n<=8; n++)
		{
			if(n == 8)
			{
				sChar = "Blaze";
			}
			else
			{
				sChar = "Arena_Tournament_Character_" + n;
			}

			p = GetTournamentPosition(sChar, "1_4");
			str = "TournamentRes_1_4_Name_" + p;

			sName = Characters[GetCharacterIndex(sChar)].name + " " + Characters[GetCharacterIndex(sChar)].lastname;
			GameInterface.strings.(str) = sName;

			if(n == 8)
			{
				ChangeStringColor(str, argb(255,255,255,128));
			}

			if(CheckAttribute(&Characters[GetCharacterIndex(sChar)], "ArenaTournament.looser.1_4"))
			{
				ChangeStringColor(str, argb(255,255,128,128));
			}
			else
			{
				ChangeStringColor(str, argb(255,128,255,128));
			}
		}

		for(n=1; n<=8; n++)
		{
			if(n == 8)
			{
				sChar = "Blaze";
			}
			else
			{
				sChar = "Arena_Tournament_Character_" + n;
			}

			if(CheckAttribute(&Characters[GetCharacterIndex(sChar)], "ArenaTournament.looser"))
			{
				continue;
			}

			p = GetTournamentPosition(sChar, "1_2");
			str = "TournamentRes_1_2_Name_" + p;

			sName = Characters[GetCharacterIndex(sChar)].name + " " + Characters[GetCharacterIndex(sChar)].lastname;
			GameInterface.strings.(str) = sName;

			if(GetCharacterIndex(sChar) == nMainCharacterIndex)
			{
				ChangeStringColor(str, argb(255,255,255,128));
			}
		}
	}

	if(PChar.Arena.Tournament.Temp.InterfaceStage == "final")
	{
		for(n=1; n<=8; n++)
		{
			if(n == 8)
			{
				sChar = "Blaze";
			}
			else
			{
				sChar = "Arena_Tournament_Character_" + n;
			}

			p = GetTournamentPosition(sChar, "1_4");
			str = "TournamentRes_1_4_Name_" + p;

			sName = Characters[GetCharacterIndex(sChar)].name + " " + Characters[GetCharacterIndex(sChar)].lastname;
			GameInterface.strings.(str) = sName;

			if(n == 8)
			{
				ChangeStringColor(str, argb(255,255,255,128));
			}

			if(CheckAttribute(&Characters[GetCharacterIndex(sChar)], "ArenaTournament.looser.1_4"))
			{
				ChangeStringColor(str, argb(255,255,128,128));
			}
			else
			{
				ChangeStringColor(str, argb(255,128,255,128));
			}
		}

		for(n=1; n<=8; n++)
		{
			if(n == 8)
			{
				sChar = "Blaze";
			}
			else
			{
				sChar = "Arena_Tournament_Character_" + n;
			}

			if(CheckAttribute(&Characters[GetCharacterIndex(sChar)], "ArenaTournament.looser.1_4"))
			{
				continue;
			}

			p = GetTournamentPosition(sChar, "1_2");
			str = "TournamentRes_1_2_Name_" + p;

			sName = Characters[GetCharacterIndex(sChar)].name + " " + Characters[GetCharacterIndex(sChar)].lastname;
			GameInterface.strings.(str) = sName;

			if(CheckAttribute(&Characters[GetCharacterIndex(sChar)], "ArenaTournament.looser.1_2"))
			{
				ChangeStringColor(str, argb(255,255,128,128));
			}
			else
			{
				ChangeStringColor(str, argb(255,128,255,128));
			}
		}

		for(n=1; n<=8; n++)
		{
			if(n == 8)
			{
				sChar = "Blaze";
			}
			else
			{
				sChar = "Arena_Tournament_Character_" + n;
			}

			if(CheckAttribute(&Characters[GetCharacterIndex(sChar)], "ArenaTournament.looser"))
			{
				continue;
			}

			p = GetTournamentPosition(sChar, "final");
			str = "TournamentRes_Final_Name_" + p;

			sName = Characters[GetCharacterIndex(sChar)].name + " " + Characters[GetCharacterIndex(sChar)].lastname;
			GameInterface.strings.(str) = sName;

			if(GetCharacterIndex(sChar) == nMainCharacterIndex)
			{
				ChangeStringColor(str, argb(255,255,255,128));
			}
		}
	}
}

int GetTournamentPosition(string sChar, string sType)
{
	switch(sType)
	{
		case "1_4":
			if(CheckAttribute(PChar, "Arena.Tournament." + sChar + ".Position"))
			{
				return sti(PChar.Arena.Tournament.(sChar).Position);
			}
		break;

		case "1_2":
			if(CheckAttribute(PChar, "Arena.Tournament." + sChar + ".Position.1_2"))
			{
				return sti(PChar.Arena.Tournament.(sChar).Position.1_2);
			}
		break;

		case "final":
			if(CheckAttribute(PChar, "Arena.Tournament." + sChar + ".Position.final"))
			{
				return sti(PChar.Arena.Tournament.(sChar).Position.final);
			}
		break;
	}

	return 1;
}

////////////////////////////////////////////////////////////////////////////////////
// Other fucntions
////////////////////////////////////////////////////////////////////////////////////
string GetBattleType()
{
	switch(iCheckBattleType)
	{
		case 0: return "Участие в дуэли"; break;
		case 1: return "Участие в этапах"; break;
		case 2: return "Участие в турнире"; break;
		case 3: return "Участие в ставках"; break;
	}

	return "none battle type";
}

string GetOddsPairs()
{
	switch(iCheckOddsPairs)
	{
		case 1: return "Первый поединок"; break;
		case 2: return "Второй поединок"; break;
		case 3: return "Третий поединок"; break;
	}

	return "none pairs number";
}

string GetSkillForEnemyFromSaber()
{
	string sSaber = GetSaberName();
	ref Saber;

	if(GetItemIndex(sSaber) != -1)
	{
		Saber = &Items[FindItem(sSaber)];
	}
	else
	{
		Saber = &Items[FindItem("blade1")];
	}

	if(CheckAttribute(Saber, "FencingType"))
	{
		return Saber.FencingType;
	}

	return "Fencing";
}

string GetSaberName()
{
	string sSaber = "";

	switch(iCheckBattleType)
	{
		case 0:
			if(CheckAttribute(PChar, "Arena.Duel.Saber"))
			{
				switch(iCheckBattleSaberType)
				{
					case 0: sSaber = PChar.Arena.Duel.Saber.Light; break;
					case 1: sSaber = PChar.Arena.Duel.Saber.Saber; break;
					case 2: sSaber = PChar.Arena.Duel.Saber.Heavy; break;
				}
				return sSaber;
			}
		break;

		case 1:
			if(CheckAttribute(PChar, "Arena.Etaps.Saber"))
			{
				switch(iCheckBattleSaberType)
				{
					case 0: sSaber = PChar.Arena.Etaps.Saber.Light; break;
					case 1: sSaber = PChar.Arena.Etaps.Saber.Saber; break;
					case 2: sSaber = PChar.Arena.Etaps.Saber.Heavy; break;
				}
				return sSaber;
			}
		break;

		case 2:
			if(CheckAttribute(PChar, "Arena.Tournament.Saber"))
			{
				switch(iCheckSaberTypeCount)
				{
					case 1: return PChar.Arena.Tournament.Saber.Light1; break;
					case 2: return PChar.Arena.Tournament.Saber.Light2; break;
					case 3: return PChar.Arena.Tournament.Saber.Light3; break;
					case 4: return PChar.Arena.Tournament.Saber.Saber1; break;
					case 5: return PChar.Arena.Tournament.Saber.Saber2; break;
					case 6: return PChar.Arena.Tournament.Saber.Saber3; break;
					case 7: return PChar.Arena.Tournament.Saber.Heavy1; break;
					case 8: return PChar.Arena.Tournament.Saber.Heavy2; break;
					case 9: return PChar.Arena.Tournament.Saber.Heavy3; break;
				}
				return sSaber;
			}
		break;

		case 3:
			if(CheckAttribute(PChar, "Arena.Odds.Saber"))
			{
				switch(iCheckOddsPairs)
				{
					case 1: sSaber = PChar.Arena.Odds.Saber.Light; break;
					case 2: sSaber = PChar.Arena.Odds.Saber.Saber; break;
					case 3: sSaber = PChar.Arena.Odds.Saber.Heavy; break;
				}
				return sSaber;
			}
		break;
	}
	return "blade1";
}

int GetDuelCharacter()
{
	if(CheckAttribute(PChar, "Arena.Duel.Character"))
	{
		return sti(PChar.Arena.Duel.Character);
	}

	return 1;
}

int GetArenaOddsCharacter(int iCount, int iCharacter)
{
	string sFight = "Fight_" + iCount;
	string sFightChar = "Char_" + iCharacter;

	string sCharacter = "Arena_Odds_Duel_" + iCount + "_Character_" + iCharacter;

	if(CheckAttribute(PChar, "Arena.Odds." + sFight))
	{
		sCharacter = PChar.Arena.Odds.(sFight).(sFightChar);
	}

	return GetCharacterIndex(sCharacter);
}

void CheckEnableEtap(string sNode)
{
	if(sNode == "ETAP_1_YES") { SetSelectable(sNode, false); SetNodeUsing(sNode, false); SetNodeUsing("ETAP_1_NO", true); SetSelectable("ETAP_1_NO", true); CheckEtapsEnable(); return; }
	if(sNode == "ETAP_2_YES") { SetSelectable(sNode, false); SetNodeUsing(sNode, false); SetNodeUsing("ETAP_2_NO", true); SetSelectable("ETAP_2_NO", true); CheckEtapsEnable(); return; }
	if(sNode == "ETAP_3_YES") { SetSelectable(sNode, false); SetNodeUsing(sNode, false); SetNodeUsing("ETAP_3_NO", true); SetSelectable("ETAP_3_NO", true); CheckEtapsEnable(); return; }
	if(sNode == "ETAP_4_YES") { SetSelectable(sNode, false); SetNodeUsing(sNode, false); SetNodeUsing("ETAP_4_NO", true); SetSelectable("ETAP_4_NO", true); CheckEtapsEnable(); return; }
	if(sNode == "ETAP_5_YES") { SetSelectable(sNode, false); SetNodeUsing(sNode, false); SetNodeUsing("ETAP_5_NO", true); SetSelectable("ETAP_5_NO", true); CheckEtapsEnable(); return; }

	if(sNode == "ETAP_1_NO") { SetSelectable(sNode, false); SetNodeUsing(sNode, false); SetNodeUsing("ETAP_1_YES", true); SetSelectable("ETAP_1_YES", true); CheckEtapsEnable(); return; }
	if(sNode == "ETAP_2_NO") { SetSelectable(sNode, false); SetNodeUsing(sNode, false); SetNodeUsing("ETAP_2_YES", true); SetSelectable("ETAP_2_YES", true); CheckEtapsEnable(); return; }
	if(sNode == "ETAP_3_NO") { SetSelectable(sNode, false); SetNodeUsing(sNode, false); SetNodeUsing("ETAP_3_YES", true); SetSelectable("ETAP_3_YES", true); CheckEtapsEnable(); return; }
	if(sNode == "ETAP_4_NO") { SetSelectable(sNode, false); SetNodeUsing(sNode, false); SetNodeUsing("ETAP_4_YES", true); SetSelectable("ETAP_4_YES", true); CheckEtapsEnable(); return; }
	if(sNode == "ETAP_5_NO") { SetSelectable(sNode, false); SetNodeUsing(sNode, false); SetNodeUsing("ETAP_5_YES", true); SetSelectable("ETAP_5_YES", true); CheckEtapsEnable(); return; }
}

void CheckEtapsEnable()
{
	bool bEtapYes_1 = GetSelectable("ETAP_1_YES");
	bool bEtapYes_2 = GetSelectable("ETAP_2_YES");
	bool bEtapYes_3 = GetSelectable("ETAP_3_YES");
	bool bEtapYes_4 = GetSelectable("ETAP_4_YES");
	bool bEtapYes_5 = GetSelectable("ETAP_5_YES");

	int iEtapMoney_1 = 0;
	int iEtapMoney_2 = 0;
	int iEtapMoney_3 = 0;
	int iEtapMoney_4 = 0;
	int iEtapMoney_5 = 0;
	int iEtapsMoney = 0;

	if(bEtapYes_1) { iEtapMoney_1 = sti(PChar.Arena.Etaps.Etap_1.Cost); }
	if(bEtapYes_2) { iEtapMoney_2 = sti(PChar.Arena.Etaps.Etap_2.Cost); }
	if(bEtapYes_3) { iEtapMoney_3 = sti(PChar.Arena.Etaps.Etap_3.Cost); }
	if(bEtapYes_4) { iEtapMoney_4 = sti(PChar.Arena.Etaps.Etap_4.Cost); }
	if(bEtapYes_5) { iEtapMoney_5 = sti(PChar.Arena.Etaps.Etap_5.Cost); }

	iEtapsMoney = iEtapMoney_1 + iEtapMoney_2 + iEtapMoney_3 + iEtapMoney_4 + iEtapMoney_5;
	PChar.Arena.Etaps.Prize = iEtapsMoney;

	GameInterface.strings.Etaps_Payment_2 = sti(iEtapsMoney / 5);
	GameInterface.strings.Etaps_Win_Gold_2 = sti(PChar.Arena.Etaps.Prize) + " пиастров";

	if(!bEtapYes_5)
	{
		SetSelectable("OK", false);
		return;
	}

	if(!bEtapYes_1 && !bEtapYes_2 && !bEtapYes_3 && !bEtapYes_4)
	{
		SetSelectable("OK", false);
		return;
	}
	else
	{
		if(sti(PChar.money) >= sti(iEtapsMoney / 5))
		{
			SetSelectable("OK", true);
		}
		else
		{
			SetSelectable("OK", false);
		}
	}
}

void CheckEnableOddCharacter(string sNode)
{
	SetNodeUsing(sNode, false);
	SetSelectable(sNode, false);

	if(sNode == "ODDS_CHAR_1_YES")
	{
		SetNodeUsing("ODDS_CHAR_2_YES", true);
		SetSelectable("ODDS_CHAR_2_YES", true);
	}

	if(sNode == "ODDS_CHAR_2_YES")
	{
		SetNodeUsing("ODDS_CHAR_1_YES", true);
		SetSelectable("ODDS_CHAR_1_YES", true);
	}

	CheckEnableOddsCharacter();
}

void CheckEnableOddsCharacter()
{
	int iOdd = sti(PChar.Arena.Odds.Odd);

	if(sti(PChar.money) >= iOdd)
	{
		SetSelectable("OK", true);
	}
	else
	{
		SetSelectable("OK", false);
	}
}


void CheckBattleInformation()
{
	switch(iCheckBattleType)
	{
		case 0:
			DisableDuelInfo(true);
			//-----------------------------------------------------
			DisableEtapsInfo(false);
			//-----------------------------------------------------
			DisableTournamentInfo(false);
			//-----------------------------------------------------
			DisableOddsInfo(false);
			//-----------------------------------------------------
			SetDuelInfo();
		break;

		case 1:
			DisableEtapsInfo(true);
			//-----------------------------------------------------
			DisableDuelInfo(false);
			//-----------------------------------------------------
			DisableTournamentInfo(false);
			//-----------------------------------------------------
			DisableOddsInfo(false);
			//-----------------------------------------------------
			SetEtapsInfo();
		break;

		case 2:
			DisableTournamentInfo(true);
			//-----------------------------------------------------
			DisableDuelInfo(false);
			//-----------------------------------------------------
			DisableEtapsInfo(false);
			//-----------------------------------------------------
			DisableOddsInfo(false);
			//-----------------------------------------------------
			SetTournamentInfo();
		break;

		case 3:
			//-----------------------------------------------------
			DisableDuelInfo(false);
			//-----------------------------------------------------
			DisableEtapsInfo(false);
			//-----------------------------------------------------
			DisableTournamentInfo(false);
			//-----------------------------------------------------
			DisableOddsInfo(true);
			//-----------------------------------------------------
			SetOddsInfo();
		break;
	}
}

void DisableDuelInfo(bool bEnable)
{
	SetNodeUsing("DUEL_CHARACTER_PICTURE", bEnable);
	SetNodeUsing("DUEL_CHARACTER_NAME_PICTURE", bEnable);
	SetNodeUsing("DUEL_CHARACTER_NAME_TEXT", bEnable);
	SetNodeUsing("TABLE_DUEL_CHARACTER", bEnable);
	SetNodeUsing("DUEL_ODD_YES", bEnable);
	SetNodeUsing("DUEL_ODD_NO", bEnable);
	SetNodeUsing("V_DUEL_ODD", bEnable);
	SetNodeUsing("DUEL_ODD", bEnable);
	SetNodeUsing("BORDERS_1", bEnable);

	GameInterface.strings.Duel_Money_1 = "";
	GameInterface.strings.Duel_Money_2 = "";
	GameInterface.strings.Duel_Min_Odd_1 = "";
	GameInterface.strings.Duel_Min_Odd_2 = "";
	GameInterface.strings.Duel_Odd_1 = "";
	GameInterface.strings.Duel_Odd_2 = "";
	GameInterface.strings.Duel_Odd_Install = "";

}

void DisableEtapsInfo(bool bEnable)
{
	for(int s=1; s<=5; s++)
	{
		SetNodeUsing("ETAPS_PICTURE_" + s, bEnable);
		SetNodeUsing("ETAPS_BORDER_" + s, bEnable);
		SetNodeUsing("ETAP_" + s + "_YES", bEnable);
		SetNodeUsing("ETAP_" + s + "_NO", bEnable);
	}

	SetNodeUsing("ETAPS_PAYMENT", bEnable);
	SetNodeUsing("ETAPS_MONEY", bEnable);

	GameInterface.strings.Etaps_HeroMoney_1 = "";
	GameInterface.strings.Etaps_HeroMoney_2 = "";
	GameInterface.strings.Etaps_Payment_1 = "";
	GameInterface.strings.Etaps_Payment_2 = "";
	GameInterface.strings.Etaps_No_1 = "";
	GameInterface.strings.Etaps_No_2 = "";
	GameInterface.strings.Etaps_No_3 = "";
	GameInterface.strings.Etaps_No_4 = "";
	GameInterface.strings.Etaps_No_5 = "";
	GameInterface.strings.Etaps_Money_1 = "";
	GameInterface.strings.Etaps_Money_2 = "";
	GameInterface.strings.Etaps_Money_3 = "";
	GameInterface.strings.Etaps_Money_4 = "";
	GameInterface.strings.Etaps_Money_5 = "";
	GameInterface.strings.Etaps_Quantity_1 = "";
	GameInterface.strings.Etaps_Quantity_2 = "";
	GameInterface.strings.Etaps_Quantity_3 = "";
	GameInterface.strings.Etaps_Quantity_4 = "";
	GameInterface.strings.Etaps_Quantity_5 = "";
	GameInterface.strings.Etaps_Win_Gold_1 = "";
	GameInterface.strings.Etaps_Win_Gold_2 = "";
}

void DisableTournamentInfo(bool bEnable)
{
	SetNodeUsing("BORDERS_2", bEnable);

	for(int s=1; s<=8; s++) { SetNodeUsing("TOURNAMENT_NAME_" + s, bEnable); }

	GameInterface.strings.Tournament_1_4_1 = "";
	GameInterface.strings.Tournament_1_4_2 = "";
	GameInterface.strings.Tournament_1_2_1 = "";
	GameInterface.strings.Tournament_1_2_2 = "";
	GameInterface.strings.Tournament_final = "";
	GameInterface.strings.Tournament_Win_Gold_1 = "";
	GameInterface.strings.Tournament_Win_Gold_2 = "";
	GameInterface.strings.Tournament_Cost_1 = "";
	GameInterface.strings.Tournament_Cost_2 = "";
	GameInterface.strings.Tournament_Money_1 = "";
	GameInterface.strings.Tournament_Money_2 = "";
	GameInterface.strings.Tournament_NotGen = "";
}

void DisableOddsInfo(bool bEnable)
{
	SetNodeUsing("FRAME_CHARACTER_PICTURE", false);
	SetNodeUsing("BORDERS_4", bEnable);
	SetNodeUsing("BORDERS_5", bEnable);
	SetNodeUsing("ODDS_CHARACTER_1_PICTURE", bEnable);
	SetNodeUsing("ODDS_CHARACTER_2_PICTURE", bEnable);
	SetNodeUsing("ODDS_CHARACTER_1_NAME_TEXT", bEnable);
	SetNodeUsing("ODDS_CHARACTER_2_NAME_TEXT", bEnable);
	SetNodeUsing("TABLE_ODDS_CHARACTERS", bEnable);
	SetNodeUsing("ODDS_ODD_YES", bEnable);
	SetNodeUsing("ODDS_ODD_NO", bEnable);
	SetNodeUsing("V_ODDS_ODD", bEnable);
	SetNodeUsing("ODDS_ODD", bEnable);
	SetNodeUsing("ODDS_PAIRS_LEFT", bEnable);
	SetNodeUsing("ODDS_PAIRS_RIGHT", bEnable);
	SetNodeUsing("ODDS_PAIRS_TEXT", bEnable);
	SetNodeUsing("ODDS_CHAR_1_YES", bEnable);
	SetNodeUsing("ODDS_CHAR_2_YES", bEnable);

	if(!bEnable)
	{
		SetNodeUsing("BATTLE_SABER_TYPE_LEFT", true);
		SetNodeUsing("BATTLE_SABER_TYPE_RIGHT", true);
	}
	else
	{
		SetNodeUsing("BATTLE_SABER_TYPE_LEFT", false);
		SetNodeUsing("BATTLE_SABER_TYPE_RIGHT", false);
	}

	GameInterface.strings.Odds_Money_1 = "";
	GameInterface.strings.Odds_Money_2 = "";
	GameInterface.strings.Odds_Min_Odd_1 = "";
	GameInterface.strings.Odds_Min_Odd_2 = "";
	GameInterface.strings.Odds_Odd_1 = "";
	GameInterface.strings.Odds_Odd_2 = "";
	GameInterface.strings.Odds_Odd_Install = "";
}

void DuelOddTemp()
{
	int iMinOdd = sti(PChar.Arena.Duel.MinOdd);
	int iMaxOdd = sti(PChar.Arena.Duel.MaxOdd);

	if(sti(GameInterface.DUEL_ODD.str) > iMaxOdd)
	{
		GameInterface.DUEL_ODD.str = iMaxOdd;
	}

	if(sti(GameInterface.DUEL_ODD.str) < iMinOdd)
	{
		GameInterface.DUEL_ODD.str = iMinOdd;
	}
}

void OddsOddTemp()
{
	int iMinOdd = sti(PChar.Arena.Odds.MinOdd);
	int iMaxOdd = sti(PChar.Arena.Odds.MaxOdd);

	if(sti(GameInterface.ODDS_ODD.str) > iMaxOdd)
	{
		GameInterface.ODDS_ODD.str = iMaxOdd;
	}

	if(sti(GameInterface.ODDS_ODD.str) < iMinOdd)
	{
		GameInterface.ODDS_ODD.str = iMinOdd;
	}
}

void AcceptOdd(string sType)
{
	int iMinOdd = sti(PChar.Arena.(sType).MinOdd);
	int iMaxOdd = sti(PChar.Arena.(sType).MaxOdd);

	string sString = sType + "_Odd_2";
	string sNode = sType + "_ODD";

	if(sti(GameInterface.(sNode).str) > iMaxOdd)
	{
		GameInterface.(sNode).str = iMaxOdd;
	}

	if(sti(GameInterface.(sNode).str) < iMinOdd)
	{
		GameInterface.(sNode).str = iMinOdd;
	}

	GameInterface.strings.(sString) = sti(GameInterface.(sNode).str);
	PChar.Arena.(sType).Odd = sti(GameInterface.(sNode).str);
}

void ResetOdd(string sType)
{
	int iOdd = sti(PChar.Arena.(sType).MinOdd);

	string sString = sType + "_Odd_2";
	string sNode = sType + "_ODD";

	GameInterface.strings.(sString) = iOdd;
	GameInterface.(sNode).str = 0;
	PChar.Arena.(sType).Odd = iOdd;
}

void ResetAllOperations()
{
	CheckBattleInformation();
	iCheckOddsPairs = 1;

	GameInterface.DUEL_ODD.str = 0;
	GameInterface.ODDS_ODD.str = 0;
	SetBattleTypeInformation();
	SetEquipmentInformation();
}

//-------------------------------------------------------------------------------
// OK!
//-------------------------------------------------------------------------------
void StartArenaOperation()
{
	PChar.Arena = "Prepare";
	PChar.quest.ClearArenaTime.over = "yes";
	Locations[FindLocation("FencingTown_ExitTown")].reload.l2.disable = 1;
	Locations[FindLocation("FencingTown_ExitTown")].reload.l3.disable = 1;
	Locations[FindLocation("FencingTown_ExitTown")].reload.l4.disable = 1;
	switch(iCheckBattleType)
	{
		case 0: ArenaStartDuel(); break;
		case 1: ArenaStartEtaps(); break;
		case 2: ArenaStartTournament(); break;
		case 3: ArenaStartOdds(); break;
	}
}

void ArenaStartDuel()
{
	ref enemy = &Characters[GetDuelCharacter()];

	int iPlayerOdd = sti(PChar.Arena.Duel.Odd);
	AddMoneyToCharacter(PChar, -iPlayerOdd);

	int iEnemyOdd = sti(enemy.odd);

	iPlayerOdd += iEnemyOdd;
	iPlayerOdd *= 2;

	PChar.Arena.Duel.Saber = GetSaberName();

	PChar.Arena.Duel.Prize = iPlayerOdd;
	PrepareArenaDuel();
	ProcessBreakExit();
}

void ArenaStartEtaps()
{
	int iStartCost = sti(PChar.Arena.Etaps.Prize) / 5;
	AddMoneyToCharacter(PChar, -iStartCost);

	bool bEtapYes_1 = GetSelectable("ETAP_1_YES");
	bool bEtapYes_2 = GetSelectable("ETAP_2_YES");
	bool bEtapYes_3 = GetSelectable("ETAP_3_YES");
	bool bEtapYes_4 = GetSelectable("ETAP_4_YES");
	bool bEtapYes_5 = GetSelectable("ETAP_5_YES");

	if(bEtapYes_1) { PChar.Arena.Etaps.Etap_1 = "YES"; }else{ PChar.Arena.Etaps.Etap_1 = "NO"; }
	if(bEtapYes_2) { PChar.Arena.Etaps.Etap_2 = "YES"; }else{ PChar.Arena.Etaps.Etap_2 = "NO"; }
	if(bEtapYes_3) { PChar.Arena.Etaps.Etap_3 = "YES"; }else{ PChar.Arena.Etaps.Etap_3 = "NO"; }
	if(bEtapYes_4) { PChar.Arena.Etaps.Etap_4 = "YES"; }else{ PChar.Arena.Etaps.Etap_4 = "NO"; }
	if(bEtapYes_5) { PChar.Arena.Etaps.Etap_5 = "YES"; }else{ PChar.Arena.Etaps.Etap_5 = "NO"; }

	PChar.Arena.Etaps.Saber = GetSaberName();

	PrepareArenaEtaps();
	ProcessBreakExit();
}

void ArenaStartTournament()
{
	int iStartCost = sti(PChar.Arena.Tournament.Money) / 8;
	AddMoneyToCharacter(PChar, -iStartCost);

	idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	pchar.Arena.TournamentWeapon = GetSaberName();
	ref rSaber = &Items[FindItem(pchar.Arena.TournamentWeapon)];
	string sSaberName = LanguageConvertString(idLngFile, rSaber.name);
	log_info("Выбранное для турнира оружие: "+sSaberName);
	LanguageCloseFile(idLngFile);

	PrepareArenaTournament();
	ProcessBreakExit();
}

void ArenaStartOdds()
{
	PChar.Arena.Odds.ActionFight = iCheckOddsPairs;

	bool bChar_1 = GetSelectable("ODDS_CHAR_1_YES");
	bool bChar_2 = GetSelectable("ODDS_CHAR_2_YES");

	int iCharacter = 0;
	if(bChar_1)
	{
		iCharacter = GetArenaOddsCharacter(iCheckOddsPairs, 1);
	}
	if(bChar_2)
	{
		iCharacter = GetArenaOddsCharacter(iCheckOddsPairs, 2);
	}

	float fRate = stf(Characters[iCharacter].Arena.Odds.Rate);
	int iOdd = sti(PChar.Arena.Odds.Odd);
	AddMoneyToCharacter(PChar, -iOdd);

	iOdd *= fRate;

	PChar.Arena.Odds.ActionFight = iCheckOddsPairs;
	PChar.Arena.Odds.Prize = iOdd;
	PChar.Arena.Odds.Character = iCharacter;

	PChar.Arena.Mode.NotOdd = false;

	PrepareArenaOdds();
	ProcessBreakExit();
}
