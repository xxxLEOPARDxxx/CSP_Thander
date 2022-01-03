int nCurScrollNum = -1;
ref refCharacter = PChar;
string sMessageMode;

int iChangeCount = 2;

void InitInterface(string iniName)
{
    	GameInterface.title = "titleColonyGuarding";

    	FillShipsScroll();

    	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	PChar.Colony.Guardians.InstallShip = 0;
	PChar.Colony.Guardians.InstallShip.Character = 0;

	SetInformation();

	SetNodeUsing("FRAME_SHIP_INSTALL", false);
	SetNodeUsing("INSTALL_OK", false);
	SetNodeUsing("INSTALL_CANCEL", false);
	SetNodeUsing("SHIPS_SCROLL", false);
	SetNodeUsing("LEFTSCROLLBUTTON", false);
	SetNodeUsing("RIGHTSCROLLBUTTON", false);
	SetNodeUsing("TABLE_SHIP_INSTALL", false);
	SetNodeUsing("BORDERS_SHIP_INSTALL", false);
	SetNodeUsing("BORDERS_SHIP_INSTALL_1", false);

	SetNodeUsing("CHANGE_OK", false);
	SetNodeUsing("CHANGE_CANCEL", false);
	SetNodeUsing("CHANGE_LEFT", false);
	SetNodeUsing("CHANGE_RIGHT", false);
	SetNodeUsing("BORDERS_SHIP_CHANGE_LEFT", false);
	SetNodeUsing("BORDERS_SHIP_CHANGE_LEFT_1", false);
	SetNodeUsing("BORDERS_SHIP_CHANGE_RIGHT", false);
	SetNodeUsing("BORDERS_SHIP_CHANGE_RIGHT_1", false);
	SetNodeUsing("FRAME_SHIP_CHANGE", false);
	sMessageMode = "";


	//SetInstallFrame(false, true);

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("SetInstallInformation","SetInstallInformation",0);
	SetEventHandler("RefreshInstallInformationRight","RefreshInstallInformationRight",0);
	SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
	SetEventHandler("MouseRClickUp","HideInfoWindow",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);
	SetEventHandler("ShipOneName","ShipOneName",0);
	SetEventHandler("ShipTwoName","ShipTwoName",0);
	SetEventHandler("ShipThreeName","ShipThreeName",0);
	SetEventHandler("ShipFourName","ShipFourName",0);
}

void ShowInfoWindow()
{
	string sCurrentNode = GetCurrentNode();
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;

	sPicture = "-1";
	string sAttributeName;
	int nChooseNum = -1;
	switch (sCurrentNode)
	{
		case "SHIPS_SCROLL":
			string attributeName = GetPictureNumber();
			int iCharacter = sti(GameInterface.SHIPS_SCROLL.(attributeName).companionIndex);
			if(iCharacter != 0)
			{
				ref chr = &Characters[iCharacter];
				SetSPECIALMiniTable("TABLE_SMALLSKILL", chr);
				SetOTHERMiniTable("TABLE_SMALLOTHER", chr);
				SetFormatedText("OFFICER_NAME", GetFullName(chr));
				SetNewPicture("CHARACTER_BIG_PICTURE", "interfaces\portraits\256\face_" + chr.faceId + ".tga");
				SetNewPicture("CHARACTER_FRAME_PICTURE", "interfaces\Frame3.tga");

				XI_WindowShow("RPG_WINDOW", true);
				XI_WindowDisable("RPG_WINDOW", false);
				sMessageMode = "RPG_Hint";
			}
			break;
	}
}

void HideInfoWindow()
{
	CloseTooltip();
	if (sMessageMode == "RPG_Hint")
	{
		XI_WindowShow("RPG_WINDOW", false);
		XI_WindowDisable("RPG_WINDOW", true);
		sMessageMode = "";
	}
}

void FillShipsScroll()
{
	nCurScrollNum = -1;

	string sNodeName = "SHIPS_SCROLL";

	int iNotUsed = 6;

	DeleteAttribute(&GameInterface, sNodeName);
	GameInterface.(sNodeName).current = -1;

	GameInterface.(sNodeName).ImagesGroup.t0 = "BLANK_SHIP2";
	GameInterface.(sNodeName).BadTex1 = 0;
	GameInterface.(sNodeName).BadPic1 = "Not Used2";

	FillShipList(sNodeName + ".ImagesGroup", pchar);

	string attributeName, shipName;
	int iShipType, cn;
	int iListSize = 0;

	int isPossibleToFill = 1;
	for(int i= 0; i< COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);

		if(cn!= -1 && cn != nMainCharacterIndex && !CheckAttribute(&Characters[cn], "PGGAi"))
		{
			iShipType = sti(characters[cn].ship.type);
			if(iShipType != SHIP_NOTUSED)
			{
				iShipType = sti(RealShips[iShipType].basetype);

				if (iShipType!= SHIP_NOTUSED)
				{
					shipName = ShipsTypes[iShipType].Name;
					attributeName = "pic" + (iListSize+1);

					GameInterface.(sNodeName).(attributeName).companionIndex = cn;
					GameInterface.(sNodeName).(attributeName).img1 = "ship";
					GameInterface.(sNodeName).(attributeName).tex1 = FindFaceGroupNum(sNodeName + ".ImagesGroup","SHIPS_"+shipName);

					iListSize++;
				}
			}
		}
	}

	GameInterface.(sNodeName).ListSize = iListSize;
	GameInterface.SHIPS_SCROLL.NotUsed = iNotUsed - iListSize + 1;

	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_SCROLL_CHANGE, sNodeName, -1);

	if(!CheckAttribute(&GameInterface,"SHIPS_SCROLL.current"))
	{
		GameInterface.SHIPS_SCROLL.current = 0;
	}

	//SetInformation();
}

void ShipOneName()
{
	Characters[sti(PChar.Colony.Guardians.Ship1)].ship.name = GameInterface.SHIP1_NAME.str;
	SetShipInformationOne();
}

void ShipTwoName()
{
	Characters[sti(PChar.Colony.Guardians.Ship2)].ship.name = GameInterface.SHIP2_NAME.str;
	SetShipInformationTwo();
}

void ShipThreeName()
{
	Characters[sti(PChar.Colony.Guardians.Ship3)].ship.name = GameInterface.SHIP3_NAME.str;
	SetShipInformationThree();
}

void ShipFourName()
{
	Characters[sti(PChar.Colony.Guardians.Ship4)].ship.name = GameInterface.SHIP4_NAME.str;
	SetShipInformationFour();
}

bool GetCompanionShipQuantity()
{
	ref PChar = GetMainCharacter();

	int cn, iShipType;

	if(GetCompanionQuantity(PChar) <= 1)
	{
		return false;
	}

	for(int i=0;i<COMPANION_MAX;i++)
	{
		cn = GetCompanionIndex(PChar, i);
		if(cn!= -1 && cn != nMainCharacterIndex && !CheckAttribute(&Characters[cn], "PGGAi"))
		{
			iShipType = sti(characters[cn].ship.type);
			if(iShipType != SHIP_NOTUSED)
			{
				return true;
			}
		}
	}

	return false;
}

void ProcessBreakExit()
{
	IDoExit( RC_INTERFACE_SALARY_EXIT );
}

void ProcessCancelExit()
{
	IDoExit( RC_INTERFACE_SALARY_EXIT );
}

void IDoExit(int exitCode)
{
	if (CheckAttribute(pchar,"Colony.Guardians.Ship3")) pchar.g3 = pchar.Colony.Guardians.Ship3;
	if (CheckAttribute(pchar,"Colony.Guardians.Ship4")) pchar.g4 = pchar.Colony.Guardians.Ship4;
	DelEventHandler("SetInstallInformation","SetInstallInformation");
	DelEventHandler("RefreshInstallInformationRight","RefreshInstallInformationRight");
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("ShowInfoWindow","ShowInfoWindow");
	DelEventHandler("MouseRClickUp","HideInfoWindow");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");
	DelEventHandler("ShipOneName","ShipOneName");
	DelEventHandler("ShipTwoName","ShipTwoName");
	DelEventHandler("ShipThreeName","ShipThreeName");
	DelEventHandler("ShipFourName","ShipFourName");

	//CheckDeadColonyGuard();

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
		case "B_OK":
			if(comName=="activate" || comName=="click")
			{
				PostEvent("evntDoPostExit",1,"l",RC_INTERFACE_SALARY_EXIT);
			}
		break;

		case "REPAIR_SHIP1":
			if(comName=="activate" || comName=="click")
			{
				RepairShip(sti(PChar.Colony.Guardians.Ship1));
			}
		break;

		case "REPAIR_SHIP2":
			if(comName=="activate" || comName=="click")
			{
				RepairShip(sti(PChar.Colony.Guardians.Ship2));
			}
		break;

		case "REPAIR_SHIP3":
			if(comName=="activate" || comName=="click")
			{
				RepairShip(sti(PChar.Colony.Guardians.Ship3));
			}
		break;

		case "REPAIR_SHIP4":
			if(comName=="activate" || comName=="click")
			{
				RepairShip(sti(PChar.Colony.Guardians.Ship4));
			}
		break;

		case "GUARD_YES_SHIP2":
			if(comName=="activate" || comName=="click")
			{
				GuardianInizialization(sti(PChar.Colony.Guardians.Ship2), 2, true);
			}
		break;

		case "GUARD_NOT_SHIP2":
			if(comName=="activate" || comName=="click")
			{
				GuardianInizialization(sti(PChar.Colony.Guardians.Ship2), 2, false);
			}
		break;

		case "GUARD_YES_SHIP3":
			if(comName=="activate" || comName=="click")
			{
				GuardianInizialization(sti(PChar.Colony.Guardians.Ship3), 3, true);
			}
		break;

		case "GUARD_NOT_SHIP3":
			if(comName=="activate" || comName=="click")
			{
				GuardianInizialization(sti(PChar.Colony.Guardians.Ship3), 3, false);
			}
		break;

		case "GUARD_YES_SHIP4":
			if(comName=="activate" || comName=="click")
			{
				GuardianInizialization(sti(PChar.Colony.Guardians.Ship4), 4, true);
			}
		break;

		case "GUARD_NOT_SHIP4":
			if(comName=="activate" || comName=="click")
			{
				GuardianInizialization(sti(PChar.Colony.Guardians.Ship4), 4, false);
			}
		break;

		case "INSTALL_SHIP1":
			if(comName=="activate" || comName=="click")
			{
				PChar.Colony.Guardians.InstallShip = 1;
				InstallShipFrame();
			}
		break;

		case "INSTALL_SHIP2":
			if(comName=="activate" || comName=="click")
			{
				PChar.Colony.Guardians.InstallShip = 2;
				InstallShipFrame();
			}
		break;

		case "INSTALL_SHIP3":
			if(comName=="activate" || comName=="click")
			{
				PChar.Colony.Guardians.InstallShip = 3;
				InstallShipFrame();
			}
		break;

		case "INSTALL_SHIP4":
			if(comName=="activate" || comName=="click")
			{
				PChar.Colony.Guardians.InstallShip = 4;
				InstallShipFrame();
			}
		break;

		case "REMOVE_SHIP1":
			if(comName=="activate" || comName=="click")
			{
				RemoveGuardian(1, sti(PChar.Colony.Guardians.Ship1));
			}
		break;

		case "REMOVE_SHIP2":
			if(comName=="activate" || comName=="click")
			{
				RemoveGuardian(2, sti(PChar.Colony.Guardians.Ship2));
			}
		break;

		case "REMOVE_SHIP3":
			if(comName=="activate" || comName=="click")
			{
				RemoveGuardian(3, sti(PChar.Colony.Guardians.Ship3));
			}
		break;

		case "REMOVE_SHIP4":
			if(comName=="activate" || comName=="click")
			{
				RemoveGuardian(4, sti(PChar.Colony.Guardians.Ship4));
			}
		break;


		case "LEFTSCROLLBUTTON":
			if(comName=="activate" || comName=="click")
			{
				CheckInstallInformation(true);
				PostEvent("Event_SwapScrollShip", 400);
			}
		break;

		case "RIGHTSCROLLBUTTON":
			if(comName=="activate" || comName=="click")
			{
				CheckInstallInformation(false);
				PostEvent("Event_SwapScrollShip", 400);
			}
		break;



		case "SHIPS_SCROLL":
			if(comName=="activate" || comName=="click")
			{
				SetInstallInformation(false);
				PostEvent("Event_SwapScrollShip", 400);
			}
		break;


		case "INSTALL_OK":
			if(comName=="activate" || comName=="click")
			{
				InstallShip(sti(PChar.Colony.Guardians.InstallShip), sti(PChar.Colony.Guardians.InstallShip.Character));
			}
		break;

		case "INSTALL_CANCEL":
			if(comName=="activate" || comName=="click")
			{
				PChar.Colony.Guardians.InstallShip = 0;
				PChar.Colony.Guardians.InstallShip.Character = 0;
				SetInstallFrame(true, false);
				SetInformation();
			}
		break;

		case "GUARD_CHANGE":
			if(comName=="activate" || comName=="click")
			{
				SetChangeFrame(false, true);
			}
		break;

		case "CHANGE_CANCEL":
			if(comName=="activate" || comName=="click")
			{
				SetChangeFrame(true, false);
				SetInformation();
			}
		break;

		case "CHANGE_LEFT":
			if(comName=="activate" || comName=="click")
			{
				CheckChangeShips(true);
			}
		break;

		case "CHANGE_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				CheckChangeShips(false);
			}
		break;

		case "CHANGE_OK":
			if(comName=="activate" || comName=="click")
			{
				ChangeShipsOK();
			}
		break;
	}
}

#event_handler("Event_SwapScrollShip", "SwapScrollShip");
void SwapScrollShip()
{
	SetInstallInformation(false);
}

void RepairShip(int iCharacter)
{
	if(iCharacter == -1)
	{
		return;
	}

	ref chr = &Characters[iCharacter];

	//SetBaseShipData(PChar);

	chr.ship.hp = GetCharacterShipHP(chr);
	DeleteAttribute(chr, "ship.blots");

	chr.ship.sp = GetCharacterShipSP(chr);
	DeleteAttribute(chr, "ship.sails");
	DeleteAttribute(chr, "ship.masts");

	/*
	int cn = -1;
	aref arDamages;
	string sBort;
	int iNumRealCannons = 0;
	int iNumIntactCannons = 0;
	string attr;

	cn = iCharacter;

	if(cn != -1)
	{
		if(sti(characters[cn].ship.type) != SHIP_NOTUSED)
		{
			characters[cn].ship.hp = Realships[sti(characters[cn].ship.type)].hp;
			characters[cn].ship.sp = 100;
			for (int m = 0; m < 4; m++)
			{
				switch (m)
				{
					case 0: sBort = "cannonf"; break;
					case 1: sBort = "cannonb"; break;
					case 2: sBort = "cannonl"; break;
					case 3: sBort = "cannonr"; break;
				}
				makearef(arDamages, characters[cn].Ship.Cannons.Borts.(sBort).damages);

				iNumRealCannons = GetAttributesNum(arDamages);

				for (int k=0; k<iNumRealCannons; k++)
				{
					attr = "c" + k;
					if(arDamages.(attr) > 0.01)
					{
						arDamages.(attr) = 0.0;
					}
				}
			}
			DeleteAttribute(&characters[cn], "ship.flow");
		}
	}
	*/

	SetInformation();
}

void RemoveGuardian(int iNum, int iCharacter)
{
	ref chr = &Characters[iCharacter];
	chr.nation = sti(chr.nation.pre);

	string sShip = "Ship" + iNum;
	PChar.Colony.Guardians.(sShip) = -1;
	PChar.Colony.Guardians.(sShip).Active = false;
	DeleteAttribute(pchar,"g"+iNum);
	GuardianInizialization(iCharacter, iNum, false);

	SetCharacterShipLocation(chr, "None");
	// SetGoodsInitNull(chr);
	// SetBaseShipData(chr);
	// SetCrewQuantity(chr, 0);
	SetCompanionIndex(PChar, -1, iCharacter);

	if(CheckAttribute(chr, "AlwaysFriend")) 	{ DeleteAttribute(chr, "AlwaysFriend"); }
	if(CheckAttribute(chr, "ShipEnemyDisable")) 	{ DeleteAttribute(chr, "ShipEnemyDisable"); }
	if(CheckAttribute(chr, "DontCheckFlag")) 	{ DeleteAttribute(chr, "DontCheckFlag"); }

	ClearShipInfo(1);
	ClearShipInfo(2);
	ClearShipInfo(3);
	ClearShipInfo(4);

	string sGroup = "InterfaceColonyGuardians_" + iNum;
	if(Group_FindGroup(sGroup) != -1)
	{
		Group_DeleteGroup(sGroup);
	}

	RefreshShipsScroll(1); //FillShipsScroll();
	SetInformation();
}

void GuardianInizialization(int iCharacter, int iShip, bool bYes)
{
	if(iCharacter == -1)
	{
		return;
	}

	ref chr = &Characters[iCharacter];

	string sNodeNot, sNodeYes;
	string sShip = "Ship" + iShip;
	string sGroup = "InterfaceColonyGuardians_" + iShip;
	if(bYes)
	{
		if(Group_FindGroup(sGroup) != -1)
		{
			Group_SetAddress(sGroup, "Caiman", "quest_ships", "quest_ship_" + iShip);
		}

		sNodeNot = "GUARD_YES_SHIP" + iShip;
		sNodeYes = "GUARD_NOT_SHIP" + iShip;

		PChar.Colony.Guardians.(sShip).Active = true;
	}
	else
	{
		if(Group_FindGroup(sGroup) != -1)
		{
			Group_SetAddress(sGroup, "none", "none", "none");
		}

		sNodeNot = "GUARD_NOT_SHIP" + iShip;
		sNodeYes = "GUARD_YES_SHIP" + iShip;

		PChar.Colony.Guardians.(sShip).Active = false;

		// SetGoodsInitNull(chr);
		// SetBaseShipData(chr);
	}

	SetNodeUsing(sNodeNot, false);
	SetNodeUsing(sNodeYes, true);

	//CheckDeadColonyGuard();

	// SetGoodsInitNull(NPChar);
}

void InstallShip(int iGuardian, int iCharacter)
{
	string sShip = "Ship" + iGuardian;
	PChar.Colony.Guardians.(sShip) = iCharacter;

	ref chr = &Characters[iCharacter];
	RemoveCharacterCompanion(PChar, chr);

	chr.nation.pre = sti(chr.nation);
	chr.nation = PIRATE;//sti(PChar.nation);
	chr.ShipEnemyDisable = true;
	chr.CaimanGuardian = true;
	chr.DontCheckFlag = true;

	//14.05.2021 evil_bars: удаляем аттрибут, т.к. он проверяется в Addons/ColonyGuarding.c/CheckDeadColonyGuard() и удаляет корабли
	if(CheckAttribute(chr,"ship.shipsink")) { DeleteAttribute(chr,"ship.shipsink"); }

	chr.AlwaysFriend = true;
	chr.Ship.Mode = "war";

	SetCharacterRelationBoth(iCharacter, GetMainCharacterIndex(), RELATION_FRIEND);
	SetCharacterShipLocation(chr, "LandGuardingPort");

	string sGroup = "InterfaceColonyGuardians_" + iGuardian;
	Group_FindOrCreateGroup(sGroup);

	Group_SetType(sGroup, "war");
	Group_AddCharacter(sGroup, chr.id);
	Group_SetGroupCommander(sGroup, chr.id);
	GuardianInizialization(iCharacter, iGuardian, true);

	UpdateRelations();

	PChar.Colony.Guardians.InstallShip = 0;
	PChar.Colony.Guardians.InstallShip.Character = 0;

	RefreshShipsScroll(-1); //FillShipsScroll();

	SetInstallFrame(true, false);
	SetInformation();
	//CheckDeadColonyGuard();
}

void SetInformation()
{
	CreateString(true,"ShipHeaderOne","Нет корабля", FONT_CAPTION, COLOR_NORMAL, 190,35,SCRIPT_ALIGN_CENTER,1.5);
	CreateString(true,"ShipHeaderTwo","Нет корабля", FONT_CAPTION, COLOR_NORMAL, 190,317,SCRIPT_ALIGN_CENTER,1.5);
	CreateString(true,"ShipHeaderThree","Нет корабля", FONT_CAPTION, COLOR_NORMAL, 595,35,SCRIPT_ALIGN_CENTER,1.5);
	CreateString(true,"ShipHeaderFour","Нет корабля", FONT_CAPTION, COLOR_NORMAL, 595,317,SCRIPT_ALIGN_CENTER,1.5);

	//if(GetCompanionQuantity(PChar) >= 2)
    	//{
    		//FillShipsScroll();
    	//}

	//RefreshShipsScroll();


	GameInterface.strings.ShipInstallFrameHeader = "";
	SetNodeUsing("FRAME_SHIP_INSTALL", false);
	SetNodeUsing("INSTALL_OK", false);
	SetNodeUsing("INSTALL_CANCEL", false);
	SetNodeUsing("GUARD_CHANGE", true);

	SetShipInformationOne();
	SetShipInformationTwo();
	SetShipInformationThree();
	SetShipInformationFour();

	int iShipOne = sti(PChar.Colony.Guardians.Ship1);
	int iShipTwo = sti(PChar.Colony.Guardians.Ship2);
	int iShipThree = sti(PChar.Colony.Guardians.Ship3);
	int iShipFour = sti(PChar.Colony.Guardians.Ship4);

	if(iShipOne == -1 && iShipTwo == -1 && iShipThree == -1 && iShipFour == -1)
	{
		SetSelectable("GUARD_CHANGE", false);
	}
	else
	{
		if(iShipOne != -1 && iShipTwo != -1)
		{
			SetSelectable("GUARD_CHANGE", true);
		}
		else
		{
			SetSelectable("GUARD_CHANGE", false);
		}
	}
}

void SetShipInformationOne()
{
	int iShipType = sti(PChar.Colony.Guardians.Ship1);

	if(iShipType == -1)
	{
		CreateImage("ShipType1", "BLANK_SHIP2", "Not Used2", 130,100,258,228);
		CreateString(true,"ShipOneNot","Корабль не назначен.", FONT_NORMAL, argb(255,255,128,128), 195,240,SCRIPT_ALIGN_CENTER,1.0);
		SetNodeUsing("REMOVE_SHIP1", false);
		SetNodeUsing("GUARD_NOT_SHIP1", false);
		SetNodeUsing("BORDERS_SHIP_1", false);
		SetNodeUsing("BORDERS_SHIP_1_1", false);
		SetNodeUsing("TABLE_SHIP_1", false);
		SetNodeUsing("SHIP1_NAME", false);
		SetSelectable("REPAIR_SHIP1", false);
		SetSelectable("GUARD_YES_SHIP1", false);

		SetNodeUsing("INSTALL_SHIP1", true);

		bool bCanInstall = GetCompanionShipQuantity();
		if(bCanInstall)
		{
			SetSelectable("INSTALL_SHIP1", true);
		}
		else
		{
			SetSelectable("INSTALL_SHIP1", false);
		}
	}
	else
	{
		int iCharacter = iShipType;
		ref chr = &Characters[iCharacter];

		ref rShip = GetRealShip(sti(chr.ship.type));
		string sShipType = ShipsTypes[sti(rShip.basetype)].name);
		string sShipName = chr.Ship.name;

		GameInterface.SHIP1_NAME.str = chr.Ship.name;

		float fTurnRate = stf(rShip.turnrate) * FindShipTurnRate(chr);

		int iShipClass = sti(rShip.class);

		int iHpBase = sti(rShip.Hp);
		int iSpBase = sti(rShip.Sp);
		float fSpeedRateBase = fts(stf(rShip.SpeedRate),3);
		float fTurnRateBase = fts(stf(rShip.TurnRate),3);
		int iCannonsBase = sti(rShip.CannonsQuantity);
		int iCannonsType = sti(rShip.Cannon);
		int iCrewBase = GetOptCrewQuantity(chr);

		int iHpReal = sti(chr.ship.Hp);
		int iSpReal = sti(chr.ship.Sp);
		float fSpeedRateReal = fts(FindShipSpeed(chr),3);
		float fTurnRateReal = fts(fTurnRate,3);
		int iCannonsReal = GetCannonsNum(chr);
		int iCrewReal = GetCrewQuantity(chr);

		int iCannon = sti(chr.Ship.Cannons.Type);
		string sCannon = XI_ConvertString(GetCannonType(iCannon) + "s");

		CreateImage("ShipType1", "SHIPS_" + sShipType, "ship", 20,105,160,245);

		GameInterface.strings.ShipHeaderOne = XI_ConvertString(sShipType) + " - " + sShipName;

		// CreateString(true,"ShipName1", sShipName, FONT_CAPTION, COLOR_NORMAL, 90,80,SCRIPT_ALIGN_CENTER,1.0);
		CreateString(true,"ShipType1", XI_ConvertString(sShipType), FONT_CAPTION, COLOR_NORMAL, 90,249,SCRIPT_ALIGN_CENTER,1.0);
		CreateString(true,"ShipClass1", iShipClass, FONT_BOLD_NUMBERS, COLOR_NORMAL, 140,220,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("ShipHp1", "ICONS", "ship hull icon", 173,79,205,111);
		CreateString(true,"ShipHp1", "Корпус", FONT_CAPTION, COLOR_NORMAL, 220,84,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"ShipHpQuantity1", iHpReal + "/" + iHpBase, FONT_NORMAL, COLOR_NORMAL, 306,87,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("ShipSp1", "ICONS", "ship rig icon", 173,116,205,144);
		CreateString(true,"ShipSp1", "Паруса", FONT_CAPTION, COLOR_NORMAL, 220,119,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"ShipSpQuantity1", iSpReal + "/" + iSpBase, FONT_NORMAL, COLOR_NORMAL, 308,121,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("ShipSr1", "ICONS", "ship speed icon", 173,147,205,176);
		CreateString(true,"ShipSr1", "Скорость", FONT_CAPTION, COLOR_NORMAL, 220,151,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"ShipSrQuantity1", fts(FindShipSpeed(chr),3) + "/" + fSpeedRateBase, FONT_NORMAL, COLOR_NORMAL, 308,153,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("ShipTr1", "ICONS", "ship maneuver icon", 173,179,205,208);
		CreateString(true,"ShipTr1", "Маневр.", FONT_CAPTION, COLOR_NORMAL, 220,183,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"ShipTrQuantity1", fts(fTurnRate,3) + "/" + fTurnRateBase, FONT_NORMAL, COLOR_NORMAL, 308,185,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("ShipCrew1", "ICONS", "ship max crew icon", 173,211,205,240);
		CreateString(true,"ShipCrew1", "Команда", FONT_CAPTION, COLOR_NORMAL, 220,216,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"ShipCrewQuantity1", iCrewReal + "/" + iCrewBase, FONT_NORMAL, COLOR_NORMAL, 308,218,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("ShipCannons1", "ICONS", "ship cannons icon", 173,244,205,270);
		CreateString(true,"ShipCannons1", sCannon, FONT_CAPTION, COLOR_NORMAL, 220,247,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"ShipCannonsQuantity1", iCannonsReal + "/" + iCannonsBase, FONT_NORMAL, COLOR_NORMAL, 308,249,SCRIPT_ALIGN_LEFT,1.0);

		SetNodeUsing("INSTALL_SHIP1", false);
		SetNodeUsing("GUARD_NOT_SHIP1", false);
		SetSelectable("REPAIR_SHIP1", true);
		SetSelectable("GUARD_YES_SHIP1", true);

		if(sti(PChar.Colony.Guardians.Ship2) != -1 || GetCompanionQuantity(PChar) >= COMPANION_MAX)
		{
			SetSelectable("REMOVE_SHIP1", false);
		}
		else
		{
			SetSelectable("REMOVE_SHIP1", true);
		}

		if(PChar.Colony.Guardians.Ship1.Active == true)
		{
			SetNodeUsing("GUARD_NOT_SHIP1", true);
			SetNodeUsing("GUARD_YES_SHIP1", false);
		}
		else
		{
			SetNodeUsing("GUARD_NOT_SHIP1", false);
			SetNodeUsing("GUARD_YES_SHIP1", true);
		}
	}
}

void SetShipInformationTwo()
{
	int iShipType = sti(PChar.Colony.Guardians.Ship2);

	if(iShipType == -1)
	{
		CreateImage("ShipType2", "BLANK_SHIP2", "Not Used2", 130,383,258,511);
		CreateString(true,"ShipTwoNot","Корабль не назначен.", FONT_NORMAL, argb(255,255,128,128), 195,523,SCRIPT_ALIGN_CENTER,1.0);
		SetNodeUsing("REMOVE_SHIP2", false);
		SetNodeUsing("GUARD_NOT_SHIP2", false);
		SetNodeUsing("BORDERS_SHIP_2", false);
		SetNodeUsing("BORDERS_SHIP_2_1", false);
		SetNodeUsing("TABLE_SHIP_2", false);
		SetNodeUsing("SHIP2_NAME", false);
		SetSelectable("REPAIR_SHIP2", false);
		SetSelectable("GUARD_YES_SHIP2", false);

		SetNodeUsing("INSTALL_SHIP2", true);

		bool bCanInstall = GetCompanionShipQuantity();
		if(bCanInstall && sti(PChar.Colony.Guardians.Ship1) != -1)
		{
			SetSelectable("INSTALL_SHIP2", true);
		}
		else
		{
			SetSelectable("INSTALL_SHIP2", false);
		}
	}
	else
	{
		int iCharacter = iShipType;
		ref chr = &Characters[iCharacter];

		ref rShip = GetRealShip(sti(chr.ship.type));
		string sShipType = ShipsTypes[sti(rShip.basetype)].name);
		string sShipName = chr.Ship.name;

		GameInterface.SHIP2_NAME.str = chr.Ship.name;

		float fTurnRate = stf(rShip.turnrate) * FindShipTurnRate(chr);

		int iShipClass = sti(rShip.class);

		int iHpBase = sti(rShip.Hp);
		int iSpBase = sti(rShip.Sp);
		float fSpeedRateBase = fts(stf(rShip.SpeedRate),3);
		float fTurnRateBase = fts(stf(rShip.TurnRate),3);
		int iCannonsBase = sti(rShip.CannonsQuantity);
		int iCannonsType = sti(rShip.Cannon);
		int iCrewBase = GetOptCrewQuantity(chr);

		int iHpReal = sti(chr.ship.Hp);
		int iSpReal = sti(chr.ship.Sp);
		float fSpeedRateReal = fts(FindShipSpeed(chr),3);
		float fTurnRateReal = fts(fTurnRate,3);
		int iCannonsReal = GetCannonsNum(chr);
		int iCrewReal = GetCrewQuantity(chr);

		int iCannon = sti(chr.Ship.Cannons.Type);
		string sCannon = XI_ConvertString(GetCannonType(iCannon) + "s");

		CreateImage("ShipType2", "SHIPS_" + sShipType, "ship", 20,388,160,528);

		GameInterface.strings.ShipHeaderTwo = XI_ConvertString(sShipType) + " - " + sShipName;

		//CreateString(true,"ShipName2", sShipName, FONT_CAPTION, COLOR_NORMAL, 90,363,SCRIPT_ALIGN_CENTER,1.0);
		CreateString(true,"ShipType2", XI_ConvertString(sShipType), FONT_CAPTION, COLOR_NORMAL, 90,532,SCRIPT_ALIGN_CENTER,1.0);
		CreateString(true,"ShipClass2", iShipClass, FONT_BOLD_NUMBERS, COLOR_NORMAL, 140,503,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("ShipHp2", "ICONS", "ship hull icon", 173,362,205,394);
		CreateString(true,"ShipHp2", "Корпус", FONT_CAPTION, COLOR_NORMAL, 220,367,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"ShipHpQuantity2", iHpReal + "/" + iHpBase, FONT_NORMAL, COLOR_NORMAL, 306,370,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("ShipSp2", "ICONS", "ship rig icon", 173,399,205,427);
		CreateString(true,"ShipSp2", "Паруса", FONT_CAPTION, COLOR_NORMAL, 220,402,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"ShipSpQuantity2", iSpReal + "/" + iSpBase, FONT_NORMAL, COLOR_NORMAL, 308,404,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("ShipSr2", "ICONS", "ship speed icon", 173,430,205,459);
		CreateString(true,"ShipSr2", "Скорость", FONT_CAPTION, COLOR_NORMAL, 220,434,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"ShipSrQuantity2", fts(FindShipSpeed(chr),3) + "/" + fSpeedRateBase, FONT_NORMAL, COLOR_NORMAL, 308,436,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("ShipTr2", "ICONS", "ship maneuver icon", 173,464,205,493);
		CreateString(true,"ShipTr2", "Маневр.", FONT_CAPTION, COLOR_NORMAL, 220,466,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"ShipTrQuantity2", fts(fTurnRate,3) + "/" + fTurnRateBase, FONT_NORMAL, COLOR_NORMAL, 308,468,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("ShipCrew2", "ICONS", "ship max crew icon", 173,496,205,525);
		CreateString(true,"ShipCrew2", "Команда", FONT_CAPTION, COLOR_NORMAL, 220,499,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"ShipCrewQuantity2", iCrewReal + "/" + iCrewBase, FONT_NORMAL, COLOR_NORMAL, 308,501,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("ShipCannons2", "ICONS", "ship cannons icon", 173,527,205,553);
		CreateString(true,"ShipCannons2", sCannon, FONT_CAPTION, COLOR_NORMAL, 220,531,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"ShipCannonsQuantity2", iCannonsReal + "/" + iCannonsBase, FONT_NORMAL, COLOR_NORMAL, 308,533,SCRIPT_ALIGN_LEFT,1.0);

		SetNodeUsing("INSTALL_SHIP2", false);
		SetNodeUsing("GUARD_NOT_SHIP2", false);
		SetSelectable("REPAIR_SHIP2", true);
		SetSelectable("GUARD_YES_SHIP2", true);

		if(sti(PChar.Colony.Guardians.Ship3) != -1 || GetCompanionQuantity(PChar) >= COMPANION_MAX)
		{
			SetSelectable("REMOVE_SHIP2", false);
		}
		else
		{
			SetSelectable("REMOVE_SHIP2", true);
		}

		if(PChar.Colony.Guardians.Ship2.Active == true)
		{
			SetNodeUsing("GUARD_NOT_SHIP2", true);
			SetNodeUsing("GUARD_YES_SHIP2", false);
		}
		else
		{
			SetNodeUsing("GUARD_NOT_SHIP2", false);
			SetNodeUsing("GUARD_YES_SHIP2", true);
		}
	}
}

void SetShipInformationThree()
{
	int iShipType = sti(PChar.Colony.Guardians.Ship3);
	if (CheckAttribute(pchar,"g3") && pchar.g3 != "-1") {PChar.Colony.Guardians.Ship3 = pchar.g3; iShipType = sti(PChar.Colony.Guardians.Ship3);}
	if(iShipType == -1)
	{
		CreateImage("ShipType3", "BLANK_SHIP2", "Not Used2", 525,100,653,228);
		CreateString(true,"ShipThreeNot","Корабль не назначен.", FONT_NORMAL, argb(255,255,128,128), 590,240,SCRIPT_ALIGN_CENTER,1.0);
		SetNodeUsing("REMOVE_SHIP3", false);
		SetNodeUsing("GUARD_NOT_SHIP3", false);
		SetNodeUsing("BORDERS_SHIP_3", false);
		SetNodeUsing("BORDERS_SHIP_3_1", false);
		SetNodeUsing("TABLE_SHIP_3", false);
		SetNodeUsing("SHIP3_NAME", false);
		SetSelectable("REPAIR_SHIP3", false);
		SetSelectable("GUARD_YES_SHIP3", false);

		SetNodeUsing("INSTALL_SHIP3", true);

		bool bCanInstall = GetCompanionShipQuantity();
		if(bCanInstall && sti(PChar.Colony.Guardians.Ship2) != -1)
		{
			SetSelectable("INSTALL_SHIP3", true);
		}
		else
		{
			SetSelectable("INSTALL_SHIP3", false);
		}
	}
	else
	{
		int iCharacter = iShipType;
		ref chr = &Characters[iCharacter];

		ref rShip = GetRealShip(sti(chr.ship.type));
		string sShipType = ShipsTypes[sti(rShip.basetype)].name);
		string sShipName = chr.Ship.name;

		GameInterface.SHIP3_NAME.str = chr.Ship.name;

		float fTurnRate = stf(rShip.turnrate) * FindShipTurnRate(chr);

		int iShipClass = sti(rShip.class);

		int iHpBase = sti(rShip.Hp);
		int iSpBase = sti(rShip.Sp);
		float fSpeedRateBase = fts(stf(rShip.SpeedRate),3);
		float fTurnRateBase = fts(stf(rShip.TurnRate),3);
		int iCannonsBase = sti(rShip.CannonsQuantity);
		int iCannonsType = sti(rShip.Cannon);
		int iCrewBase = GetOptCrewQuantity(chr);

		int iHpReal = sti(chr.ship.Hp);
		int iSpReal = sti(chr.ship.Sp);
		float fSpeedRateReal = fts(FindShipSpeed(chr),3);
		float fTurnRateReal = fts(fTurnRate,3);
		int iCannonsReal = GetCannonsNum(chr);
		int iCrewReal = GetCrewQuantity(chr);

		int iCannon = sti(chr.Ship.Cannons.Type);
		string sCannon = XI_ConvertString(GetCannonType(iCannon) + "s");

		CreateImage("ShipType3", "SHIPS_" + sShipType, "ship", 415,105,555,245);

		GameInterface.strings.ShipHeaderThree = XI_ConvertString(sShipType) + " - " + sShipName;

		//CreateString(true,"ShipName3", sShipName, FONT_CAPTION, COLOR_NORMAL, 485,80,SCRIPT_ALIGN_CENTER,1.0);
		CreateString(true,"ShipType3", XI_ConvertString(sShipType), FONT_CAPTION, COLOR_NORMAL, 485,249,SCRIPT_ALIGN_CENTER,1.0);
		CreateString(true,"ShipClass3", iShipClass, FONT_BOLD_NUMBERS, COLOR_NORMAL, 535,220,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("ShipHp3", "ICONS", "ship hull icon", 568,79,600,111);
		CreateString(true,"ShipHp3", "Корпус", FONT_CAPTION, COLOR_NORMAL, 615,84,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"ShipHpQuantity3", iHpReal + "/" + iHpBase, FONT_NORMAL, COLOR_NORMAL, 700,87,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("ShipSp3", "ICONS", "ship rig icon", 568,116,600,144);
		CreateString(true,"ShipSp3", "Паруса", FONT_CAPTION, COLOR_NORMAL, 615,119,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"ShipSpQuantity3", iSpReal + "/" + iSpBase, FONT_NORMAL, COLOR_NORMAL, 702,121,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("ShipSr3", "ICONS", "ship speed icon", 568,147,600,176);
		CreateString(true,"ShipSr3", "Скорость", FONT_CAPTION, COLOR_NORMAL, 615,151,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"ShipSrQuantity3", fts(FindShipSpeed(chr),3) + "/" + fSpeedRateBase, FONT_NORMAL, COLOR_NORMAL, 702,153,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("ShipTr3", "ICONS", "ship maneuver icon", 568,179,600,208);
		CreateString(true,"ShipTr3", "Маневр.", FONT_CAPTION, COLOR_NORMAL, 615,183,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"ShipTrQuantity3", fts(fTurnRate,3) + "/" + fTurnRateBase, FONT_NORMAL, COLOR_NORMAL, 702,185,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("ShipCrew3", "ICONS", "ship max crew icon", 568,211,600,240);
		CreateString(true,"ShipCrew3", "Команда", FONT_CAPTION, COLOR_NORMAL, 615,216,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"ShipCrewQuantity3", iCrewReal + "/" + iCrewBase, FONT_NORMAL, COLOR_NORMAL, 702,218,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("ShipCannons3", "ICONS", "ship cannons icon", 568,244,600,270);
		CreateString(true,"ShipCannons3", sCannon, FONT_CAPTION, COLOR_NORMAL, 615,247,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"ShipCannonsQuantity3", iCannonsReal + "/" + iCannonsBase, FONT_NORMAL, COLOR_NORMAL, 702,249,SCRIPT_ALIGN_LEFT,1.0);

		SetNodeUsing("INSTALL_SHIP3", false);
		SetNodeUsing("GUARD_NOT_SHIP3", false);
		SetSelectable("REPAIR_SHIP3", true);
		SetSelectable("GUARD_YES_SHIP3", true);

		if(sti(PChar.Colony.Guardians.Ship4) != -1 || GetCompanionQuantity(PChar) >= COMPANION_MAX)
		{
			SetSelectable("REMOVE_SHIP3", false);
		}
		else
		{
			SetSelectable("REMOVE_SHIP3", true);
		}

		if(PChar.Colony.Guardians.Ship3.Active == true)
		{
			SetNodeUsing("GUARD_NOT_SHIP3", true);
			SetNodeUsing("GUARD_YES_SHIP3", false);
		}
		else
		{
			SetNodeUsing("GUARD_NOT_SHIP3", false);
			SetNodeUsing("GUARD_YES_SHIP3", true);
		}
	}
}

void SetShipInformationFour()
{
	int iShipType = sti(PChar.Colony.Guardians.Ship4);
	if (CheckAttribute(pchar,"g4") && pchar.g4 != "-1") {PChar.Colony.Guardians.Ship4 = pchar.g4; iShipType = sti(PChar.Colony.Guardians.Ship4);}
	if(iShipType == -1)
	{
		CreateImage("ShipType4", "BLANK_SHIP2", "Not Used2", 525,383,653,511);
		CreateString(true,"ShipFourNot","Корабль не назначен.", FONT_NORMAL, argb(255,255,128,128), 590,523,SCRIPT_ALIGN_CENTER,1.0);
		SetNodeUsing("REMOVE_SHIP4", false);
		SetNodeUsing("GUARD_NOT_SHIP4", false);
		SetNodeUsing("BORDERS_SHIP_4", false);
		SetNodeUsing("BORDERS_SHIP_4_1", false);
		SetNodeUsing("TABLE_SHIP_4", false);
		SetNodeUsing("SHIP4_NAME", false);
		SetSelectable("REPAIR_SHIP4", false);
		SetSelectable("GUARD_YES_SHIP4", false);

		SetNodeUsing("INSTALL_SHIP4", true);

		bool bCanInstall = GetCompanionShipQuantity();
		if(bCanInstall && sti(PChar.Colony.Guardians.Ship3) != -1)
		{
			SetSelectable("INSTALL_SHIP4", true);
		}
		else
		{
			SetSelectable("INSTALL_SHIP4", false);
		}
	}
	else
	{
		int iCharacter = iShipType;
		ref chr = &Characters[iCharacter];

		ref rShip = GetRealShip(sti(chr.ship.type));
		string sShipType = ShipsTypes[sti(rShip.basetype)].name);
		string sShipName = chr.Ship.name;

		GameInterface.SHIP4_NAME.str = chr.Ship.name;

		float fTurnRate = stf(rShip.turnrate) * FindShipTurnRate(chr);

		int iShipClass = sti(rShip.class);

		int iHpBase = sti(rShip.Hp);
		int iSpBase = sti(rShip.Sp);
		float fSpeedRateBase = fts(stf(rShip.SpeedRate),3);
		float fTurnRateBase = fts(stf(rShip.TurnRate),3);
		int iCannonsBase = sti(rShip.CannonsQuantity);
		int iCannonsType = sti(rShip.Cannon);
		int iCrewBase = GetOptCrewQuantity(chr);

		int iHpReal = sti(chr.ship.Hp);
		int iSpReal = sti(chr.ship.Sp);
		float fSpeedRateReal = fts(FindShipSpeed(chr),3);
		float fTurnRateReal = fts(fTurnRate,3);
		int iCannonsReal = GetCannonsNum(chr);
		int iCrewReal = GetCrewQuantity(chr);

		int iCannon = sti(chr.Ship.Cannons.Type);
		string sCannon = XI_ConvertString(GetCannonType(iCannon) + "s");
		//
		CreateImage("ShipType4", "SHIPS_" + sShipType, "ship", 415,388,555,528);

		GameInterface.strings.ShipHeaderFour = XI_ConvertString(sShipType) + " - " + sShipName;

		//CreateString(true,"ShipName4", sShipName, FONT_CAPTION, COLOR_NORMAL, 485,363,SCRIPT_ALIGN_CENTER,1.0);
		CreateString(true,"ShipType4", XI_ConvertString(sShipType), FONT_CAPTION, COLOR_NORMAL, 485,532,SCRIPT_ALIGN_CENTER,1.0);
		CreateString(true,"ShipClass4", iShipClass, FONT_BOLD_NUMBERS, COLOR_NORMAL, 535,503,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("ShipHp4", "ICONS", "ship hull icon", 568,362,600,394);
		CreateString(true,"ShipHp4", "Корпус", FONT_CAPTION, COLOR_NORMAL, 615,367,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"ShipHpQuantity4", iHpReal + "/" + iHpBase, FONT_NORMAL, COLOR_NORMAL, 700,370,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("ShipSp4", "ICONS", "ship rig icon", 568,399,600,427);
		CreateString(true,"ShipSp4", "Паруса", FONT_CAPTION, COLOR_NORMAL, 615,402,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"ShipSpQuantity4", iSpReal + "/" + iSpBase, FONT_NORMAL, COLOR_NORMAL, 702,404,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("ShipSr4", "ICONS", "ship speed icon", 568,430,600,459);
		CreateString(true,"ShipSr4", "Скорость", FONT_CAPTION, COLOR_NORMAL, 615,434,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"ShipSrQuantity4", fts(FindShipSpeed(chr),3) + "/" + fSpeedRateBase, FONT_NORMAL, COLOR_NORMAL, 702,436,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("ShipTr4", "ICONS", "ship maneuver icon", 568,464,600,493);
		CreateString(true,"ShipTr4", "Маневр.", FONT_CAPTION, COLOR_NORMAL, 615,466,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"ShipTrQuantity4", fts(fTurnRate,3) + "/" + fTurnRateBase, FONT_NORMAL, COLOR_NORMAL, 702,468,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("ShipCrew4", "ICONS", "ship max crew icon", 568,496,600,525);
		CreateString(true,"ShipCrew4", "Команда", FONT_CAPTION, COLOR_NORMAL, 615,499,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"ShipCrewQuantity4", iCrewReal + "/" + iCrewBase, FONT_NORMAL, COLOR_NORMAL, 702,501,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("ShipCannons4", "ICONS", "ship cannons icon", 568,527,600,553);
		CreateString(true,"ShipCannons4", sCannon, FONT_CAPTION, COLOR_NORMAL, 615,531,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"ShipCannonsQuantity4", iCannonsReal + "/" + iCannonsBase, FONT_NORMAL, COLOR_NORMAL, 702,533,SCRIPT_ALIGN_LEFT,1.0);

		SetNodeUsing("INSTALL_SHIP4", false);
		SetNodeUsing("GUARD_NOT_SHIP4", false);
		SetSelectable("REPAIR_SHIP4", true);
		SetSelectable("GUARD_YES_SHIP4", true);

		if(GetCompanionQuantity(PChar) >= COMPANION_MAX)
		{
			SetSelectable("REMOVE_SHIP4", false);
		}
		else
		{
			SetSelectable("REMOVE_SHIP4", true);
		}

		if(PChar.Colony.Guardians.Ship4.Active == true)
		{
			SetNodeUsing("GUARD_NOT_SHIP4", true);
			SetNodeUsing("GUARD_YES_SHIP4", false);
		}
		else
		{
			SetNodeUsing("GUARD_NOT_SHIP4", false);
			SetNodeUsing("GUARD_YES_SHIP4", true);
		}
	}
}

void SetInstallFrame(bool bInstall, bool bContinue)
{
	SetNodeUsing("FRAME_SHIP_1", bInstall);
	SetNodeUsing("FRAME_SHIP_2", bInstall);
	SetNodeUsing("FRAME_SHIP_3", bInstall);
	SetNodeUsing("FRAME_SHIP_4", bInstall);

	SetNodeUsing("TABLE_SHIP_1", bInstall);
	SetNodeUsing("INSTALL_SHIP1", bInstall);
	SetNodeUsing("REMOVE_SHIP1", bInstall);
	SetNodeUsing("REPAIR_SHIP1", bInstall);
	SetNodeUsing("GUARD_NOT_SHIP1", bInstall);
	SetNodeUsing("GUARD_YES_SHIP1", bInstall);
	SetNodeUsing("BORDERS_SHIP_1", bInstall);
	SetNodeUsing("BORDERS_SHIP_1_1", bInstall);
	SetNodeUsing("SHIP1_NAME", bInstall);

	SetNodeUsing("TABLE_SHIP_2", bInstall);
	SetNodeUsing("INSTALL_SHIP2", bInstall);
	SetNodeUsing("REMOVE_SHIP2", bInstall);
	SetNodeUsing("REPAIR_SHIP2", bInstall);
	SetNodeUsing("GUARD_NOT_SHIP2", bInstall);
	SetNodeUsing("GUARD_YES_SHIP2", bInstall);
	SetNodeUsing("BORDERS_SHIP_2", bInstall);
	SetNodeUsing("BORDERS_SHIP_2_1", bInstall);
	SetNodeUsing("SHIP2_NAME", bInstall);

	SetNodeUsing("TABLE_SHIP_3", bInstall);
	SetNodeUsing("INSTALL_SHIP3", bInstall);
	SetNodeUsing("REMOVE_SHIP3", bInstall);
	SetNodeUsing("REPAIR_SHIP3", bInstall);
	SetNodeUsing("GUARD_NOT_SHIP3", bInstall);
	SetNodeUsing("GUARD_YES_SHIP3", bInstall);
	SetNodeUsing("BORDERS_SHIP_3", bInstall);
	SetNodeUsing("BORDERS_SHIP_3_1", bInstall);
	SetNodeUsing("SHIP3_NAME", bInstall);

	SetNodeUsing("TABLE_SHIP_4", bInstall);
	SetNodeUsing("INSTALL_SHIP4", bInstall);
	SetNodeUsing("REMOVE_SHIP4", bInstall);
	SetNodeUsing("REPAIR_SHIP4", bInstall);
	SetNodeUsing("GUARD_NOT_SHIP4", bInstall);
	SetNodeUsing("GUARD_YES_SHIP4", bInstall);
	SetNodeUsing("BORDERS_SHIP_4", bInstall);
	SetNodeUsing("BORDERS_SHIP_4_1", bInstall);
	SetNodeUsing("SHIP4_NAME", bInstall);

	if(!bContinue)
	{

		GameInterface.pictures.ShipTypeInstall.pic = "";
		GameInterface.pictures.BackgroundShipTypeInstall.pic = "";
		GameInterface.pictures.BackgroundShipNameInstall.pic = "";
		GameInterface.pictures.ShipHpInstall.pic = "";
		GameInterface.pictures.ShipSpInstall.pic = "";
		GameInterface.pictures.ShipSrInstall.pic = "";
		GameInterface.pictures.ShipTrInstall.pic = "";
		GameInterface.pictures.ShipCrewInstall.pic = "";
		GameInterface.pictures.ShipCannonsInstall.pic = "";
		GameInterface.pictures.ShipCannonsTypeInstall.pic = "";

		GameInterface.strings.ShipNameInstall = "";
		GameInterface.strings.ShipTypeInstall = "";
		GameInterface.strings.ShipClassInstall = "";
		GameInterface.strings.ShipHpInstall = "";
		GameInterface.strings.ShipHpQuantityInstall = "";
		GameInterface.strings.ShipSpInstall = "";
		GameInterface.strings.ShipSpQuantityInstall = "";
		GameInterface.strings.ShipSrInstall = "";
		GameInterface.strings.ShipSrQuantityInstall = "";
		GameInterface.strings.ShipTrInstall = "";
		GameInterface.strings.ShipTrQuantityInstall = "";
		GameInterface.strings.ShipCrewInstall = "";
		GameInterface.strings.ShipCrewQuantityInstall = "";
		GameInterface.strings.ShipCannonsInstall = "";
		GameInterface.strings.ShipCannonsQuantityInstall = "";
		GameInterface.strings.ShipCannonsQuantityInstall = "";
		GameInterface.strings.ShipCannonsTypeInstall = "";
		GameInterface.strings.ShipCannonsTypeInstall1 = "";

		SetNodeUsing("FRAME_SHIP_INSTALL", false);
		SetNodeUsing("INSTALL_OK", false);
		SetNodeUsing("INSTALL_CANCEL", false);
		SetNodeUsing("SHIPS_SCROLL", false);
		SetNodeUsing("LEFTSCROLLBUTTON", false);
		SetNodeUsing("RIGHTSCROLLBUTTON", false);
		SetNodeUsing("TABLE_SHIP_INSTALL", false);
		SetNodeUsing("BORDERS_SHIP_INSTALL", false);
		SetNodeUsing("BORDERS_SHIP_INSTALL_1", false);
	}

	if(bContinue)
	{
		GameInterface.pictures.ShipType1.pic = "";
		GameInterface.pictures.BackgroundShipName1.pic = "";
		GameInterface.pictures.BackgroundShipType1.pic = "";
		GameInterface.pictures.ShipHp1.pic = "";
		GameInterface.pictures.ShipSp1.pic = "";
		GameInterface.pictures.ShipSr1.pic = "";
		GameInterface.pictures.ShipTr1.pic = "";
		GameInterface.pictures.ShipCrew1.pic = "";
		GameInterface.pictures.ShipCannons1.pic = "";

		GameInterface.strings.ShipOneNot = "";
		GameInterface.strings.ShipHeaderOne = "";
		GameInterface.strings.ShipName1 = "";
		GameInterface.strings.ShipType1 = "";
		GameInterface.strings.ShipClass1 = "";
		GameInterface.strings.ShipHp1 = "";
		GameInterface.strings.ShipHpQuantity1 = "";
		GameInterface.strings.ShipSp1 = "";
		GameInterface.strings.ShipSpQuantity1 = "";
		GameInterface.strings.ShipSr1 = "";
		GameInterface.strings.ShipSrQuantity1 = "";
		GameInterface.strings.ShipTr1 = "";
		GameInterface.strings.ShipTrQuantity1 = "";
		GameInterface.strings.ShipCrew1 = "";
		GameInterface.strings.ShipCrewQuantity1 = "";
		GameInterface.strings.ShipCannons1 = "";
		GameInterface.strings.ShipCannonsQuantity1 = "";

		GameInterface.pictures.ShipType2.pic = "";
		GameInterface.pictures.BackgroundShipName2.pic = "";
		GameInterface.pictures.BackgroundShipType2.pic = "";
		GameInterface.pictures.ShipHp2.pic = "";
		GameInterface.pictures.ShipSp2.pic = "";
		GameInterface.pictures.ShipSr2.pic = "";
		GameInterface.pictures.ShipTr2.pic = "";
		GameInterface.pictures.ShipCrew2.pic = "";
		GameInterface.pictures.ShipCannons2.pic = "";

		GameInterface.strings.ShipTwoNot = "";
		GameInterface.strings.ShipHeaderTwo = "";
		GameInterface.strings.ShipName2 = "";
		GameInterface.strings.ShipType2 = "";
		GameInterface.strings.ShipClass2 = "";
		GameInterface.strings.ShipHp2 = "";
		GameInterface.strings.ShipHpQuantity2 = "";
		GameInterface.strings.ShipSp2 = "";
		GameInterface.strings.ShipSpQuantity2 = "";
		GameInterface.strings.ShipSr2 = "";
		GameInterface.strings.ShipSrQuantity2 = "";
		GameInterface.strings.ShipTr2 = "";
		GameInterface.strings.ShipTrQuantity2 = "";
		GameInterface.strings.ShipCrew2 = "";
		GameInterface.strings.ShipCrewQuantity2 = "";
		GameInterface.strings.ShipCannons2 = "";
		GameInterface.strings.ShipCannonsQuantity2 = "";

		GameInterface.pictures.ShipType3.pic = "";
		GameInterface.pictures.BackgroundShipName3.pic = "";
		GameInterface.pictures.BackgroundShipType3.pic = "";
		GameInterface.pictures.ShipHp3.pic = "";
		GameInterface.pictures.ShipSp3.pic = "";
		GameInterface.pictures.ShipSr3.pic = "";
		GameInterface.pictures.ShipTr3.pic = "";
		GameInterface.pictures.ShipCrew3.pic = "";
		GameInterface.pictures.ShipCannons3.pic = "";

		GameInterface.strings.ShipThreeNot = "";
		GameInterface.strings.ShipHeaderThree = "";
		GameInterface.strings.ShipName3 = "";
		GameInterface.strings.ShipType3 = "";
		GameInterface.strings.ShipClass3 = "";
		GameInterface.strings.ShipHp3 = "";
		GameInterface.strings.ShipHpQuantity3 = "";
		GameInterface.strings.ShipSp3 = "";
		GameInterface.strings.ShipSpQuantity3 = "";
		GameInterface.strings.ShipSr3 = "";
		GameInterface.strings.ShipSrQuantity3 = "";
		GameInterface.strings.ShipTr3 = "";
		GameInterface.strings.ShipTrQuantity3 = "";
		GameInterface.strings.ShipCrew3 = "";
		GameInterface.strings.ShipCrewQuantity3 = "";
		GameInterface.strings.ShipCannons3 = "";
		GameInterface.strings.ShipCannonsQuantity3 = "";

		GameInterface.pictures.ShipType4.pic = "";
		GameInterface.pictures.BackgroundShipName4.pic = "";
		GameInterface.pictures.BackgroundShipType4.pic = "";
		GameInterface.pictures.ShipHp4.pic = "";
		GameInterface.pictures.ShipSp4.pic = "";
		GameInterface.pictures.ShipSr4.pic = "";
		GameInterface.pictures.ShipTr4.pic = "";
		GameInterface.pictures.ShipCrew4.pic = "";
		GameInterface.pictures.ShipCannons4.pic = "";

		GameInterface.strings.ShipFourNot = "";
		GameInterface.strings.ShipHeaderFour = "";
		GameInterface.strings.ShipName4 = "";
		GameInterface.strings.ShipType4 = "";
		GameInterface.strings.ShipClass4 = "";
		GameInterface.strings.ShipHp4 = "";
		GameInterface.strings.ShipHpQuantity4 = "";
		GameInterface.strings.ShipSp4 = "";
		GameInterface.strings.ShipSpQuantity4 = "";
		GameInterface.strings.ShipSr4 = "";
		GameInterface.strings.ShipSrQuantity4 = "";
		GameInterface.strings.ShipTr4 = "";
		GameInterface.strings.ShipTrQuantity4 = "";
		GameInterface.strings.ShipCrew4 = "";
		GameInterface.strings.ShipCrewQuantity4 = "";
		GameInterface.strings.ShipCannons4 = "";
		GameInterface.strings.ShipCannonsQuantity4 = "";

		CreateString(true,"ShipInstallFrameHeader","Выбор корабля", FONT_CAPTION, COLOR_NORMAL, 395,78,SCRIPT_ALIGN_CENTER,1.5);
		SetNodeUsing("FRAME_SHIP_INSTALL", true);
		SetNodeUsing("INSTALL_OK", true);
		SetNodeUsing("INSTALL_CANCEL", true);
		SetSelectable("INSTALL_OK", true);

		//SetInstallInformation(0);
	}
}

string GetPictureNumber()
{
	nCurScrollNum = sti(GameInterface.SHIPS_SCROLL.current);
	string sPicture = "pic" + (nCurScrollNum+1);

	return sPicture;
}

void CheckInstallInformation(bool left)
{
	SetInstallInformation(1);
}

void RefreshInstallInformationRight()
{
	SetInstallInformation(1);
}

void SetInstallInformation(bool bBool)
{
	string sPicture = GetPictureNumber();

	SetNodeUsing("TABLE_SHIP_INSTALL", true);
	SetNodeUsing("BORDERS_SHIP_INSTALL", true);
	SetNodeUsing("BORDERS_SHIP_INSTALL_1", true);

	int iCharacter = sti(GameInterface.SHIPS_SCROLL.(sPicture).companionIndex);

	PChar.Colony.Guardians.InstallShip.Character = iCharacter;

	ref chr = &Characters[iCharacter];
	ref rShip = GetRealShip(sti(chr.ship.type));

	string sShipType = ShipsTypes[sti(rShip.basetype)].name);
	string sShipName = chr.Ship.name;

	float fTurnRate = stf(rShip.turnrate) * FindShipTurnRate(chr);

	int iShipClass = sti(rShip.class);

	int iHpBase = sti(rShip.Hp);
	int iSpBase = sti(rShip.Sp);
	float fSpeedRateBase = fts(stf(rShip.SpeedRate),3);
	float fTurnRateBase = fts(stf(rShip.TurnRate),3);
	int iCannonsBase = sti(rShip.CannonsQuantity);
	int iCannonsType = sti(rShip.Cannon);
	int iCrewBase = GetOptCrewQuantity(chr);

	int iHpReal = sti(chr.ship.Hp);
	int iSpReal = sti(chr.ship.Sp);
	float fSpeedRateReal = fts(FindShipSpeed(chr),3);
	float fTurnRateReal = fts(fTurnRate,3);
	int iCannonsReal = GetCannonsNum(chr);
	int iCrewReal = GetCrewQuantity(chr);

	int iCannon = sti(chr.Ship.Cannons.Type);
	string sCannon = XI_ConvertString(GetCannonType(iCannon) + "s");
	string sCaliber = GetCannonShip(iCannonsType) + " " + GetCannonCaliber(iCannon)+" фунтовые";//GetCannonTypeCaliber(iCannonsType);
	if (iCannonsReal == 0) sCaliber = "Нет орудий";

	CreateImage("ShipTypeInstall", "SHIPS_" + sShipType, "ship", 116,284,306,474);

	CreateString(true,"ShipNameInstall", sShipName, FONT_CAPTION, COLOR_NORMAL, 210,257,SCRIPT_ALIGN_CENTER,1.2);

	CreateString(true,"ShipTypeInstall", XI_ConvertString(sShipType), FONT_CAPTION, COLOR_NORMAL, 210,477,SCRIPT_ALIGN_CENTER,1.2);
	CreateString(true,"ShipClassInstall", iShipClass, FONT_BOLD_NUMBERS, COLOR_NORMAL, 280,450,SCRIPT_ALIGN_LEFT,1.0);

	CreateImage("ShipHpInstall", "ICONS", "ship hull icon", 330,259,362,291);
	CreateString(true,"ShipHpInstall", "Корпус", FONT_CAPTION, COLOR_NORMAL, 390,264,SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"ShipHpQuantityInstall", iHpReal + "/" + iHpBase, FONT_BOLD_NUMBERS, COLOR_NORMAL, 550,266,SCRIPT_ALIGN_LEFT,0.9);

	CreateImage("ShipSpInstall", "ICONS", "ship rig icon", 330,296,362,328);
	CreateString(true,"ShipSpInstall", "Паруса", FONT_CAPTION, COLOR_NORMAL, 390,300,SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"ShipSpQuantityInstall", iSpReal + "/" + iSpBase, FONT_BOLD_NUMBERS, COLOR_NORMAL, 550,303,SCRIPT_ALIGN_LEFT,0.9);

	CreateImage("ShipSrInstall", "ICONS", "ship speed icon", 330,330,362,360);
	CreateString(true,"ShipSrInstall", "Скорость", FONT_CAPTION, COLOR_NORMAL, 390,335,SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"ShipSrQuantityInstall", fts(FindShipSpeed(chr),3) + "/" + fSpeedRateBase, FONT_BOLD_NUMBERS, COLOR_NORMAL, 550,337,SCRIPT_ALIGN_LEFT,0.9);

	CreateImage("ShipTrInstall", "ICONS", "ship maneuver icon", 330,364,362,394);
	CreateString(true,"ShipTrInstall", "Маневренность", FONT_CAPTION, COLOR_NORMAL, 390,368,SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"ShipTrQuantityInstall", fts(fTurnRate,3) + "/" + fTurnRateBase, FONT_BOLD_NUMBERS, COLOR_NORMAL, 550,370,SCRIPT_ALIGN_LEFT,0.9);

	CreateImage("ShipCrewInstall", "ICONS", "ship max crew icon", 330,397,362,429);
	CreateString(true,"ShipCrewInstall", "Команда", FONT_CAPTION, COLOR_NORMAL, 390,403,SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"ShipCrewQuantityInstall", iCrewReal + "/" + iCrewBase, FONT_BOLD_NUMBERS, COLOR_NORMAL, 550,405,SCRIPT_ALIGN_LEFT,0.9);

	CreateImage("ShipCannonsInstall", "ICONS", "ship cannons icon", 330,432,362,462);
	CreateString(true,"ShipCannonsInstall", "Количество орудий", FONT_CAPTION, COLOR_NORMAL, 390,438,SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"ShipCannonsQuantityInstall", iCannonsReal + "/" + iCannonsBase, FONT_BOLD_NUMBERS, COLOR_NORMAL, 550,440,SCRIPT_ALIGN_LEFT,0.9);

	CreateImage("ShipCannonsTypeInstall", "ICONS", "cannons skill icon", 330,467,362,499);
	CreateString(true,"ShipCannonsTypeInstall", sCannon, FONT_CAPTION, COLOR_NORMAL, 390,473,SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"ShipCannonsTypeInstall1", sCaliber, FONT_CAPTION, COLOR_NORMAL, 525,473,SCRIPT_ALIGN_LEFT,1.1);
}

void InstallShipFrame()
{
	SetInstallFrame(false, true);

	SetNodeUsing("FRAME_SHIP_INSTALL", true);
	SetNodeUsing("INSTALL_OK", true);
	SetNodeUsing("INSTALL_CANCEL", true);
	SetNodeUsing("SHIPS_SCROLL", true);
	SetNodeUsing("LEFTSCROLLBUTTON", true);
	SetNodeUsing("RIGHTSCROLLBUTTON", true);
	SetNodeUsing("GUARD_CHANGE", false);

	SetInstallInformation(1);
}

string GetCannonShip(int iCannonsType)
{
	string sCannon = "";

	switch(iCannonsType)
	{
		case CANNON_TYPE_CANNON_LBS8: sCannon = "Пушки"; break;
		case CANNON_TYPE_CANNON_LBS12: sCannon = "Пушки"; break;
		case CANNON_TYPE_CANNON_LBS16: sCannon = "Пушки"; break;
		case CANNON_TYPE_CANNON_LBS20: sCannon = "Пушки"; break;
		case CANNON_TYPE_CANNON_LBS24: sCannon = "Пушки"; break;
		case CANNON_TYPE_CANNON_LBS32: sCannon = "Пушки"; break;
		case CANNON_TYPE_CANNON_LBS36: sCannon = "Пушки"; break;
		case CANNON_TYPE_CANNON_LBS42: sCannon = "Пушки"; break;
		case CANNON_TYPE_CANNON_LBS48: sCannon = "Пушки"; break;
		case CANNON_TYPE_CULVERINE_LBS8: sCannon = "Кулеврины"; break;
		case CANNON_TYPE_CULVERINE_LBS12: sCannon = "Кулеврины"; break;
		case CANNON_TYPE_CULVERINE_LBS16: sCannon = "Кулеврины"; break;
		case CANNON_TYPE_CULVERINE_LBS20: sCannon = "Кулеврины"; break;
		case CANNON_TYPE_CULVERINE_LBS24: sCannon = "Кулеврины"; break;
		case CANNON_TYPE_CULVERINE_LBS32: sCannon = "Кулеврины"; break;
		case CANNON_TYPE_CULVERINE_LBS36: sCannon = "Кулеврины"; break;
		case CANNON_TYPE_NONECANNON: sCannon = "Нет орудий"; break;
	}
	return sCannon;
}

string GetCannonTypeCaliber(int iCannonsType)
{
	string sCaliber = "";
	switch(iCannonsType)
	{
		case CANNON_TYPE_CANNON_LBS8: sCaliber = "8."; break;
		case CANNON_TYPE_CANNON_LBS12: sCaliber = "12."; break;
		case CANNON_TYPE_CANNON_LBS16: sCaliber = "16."; break;
		case CANNON_TYPE_CANNON_LBS20: sCaliber = "20."; break;
		case CANNON_TYPE_CANNON_LBS24: sCaliber = "24."; break;
		case CANNON_TYPE_CANNON_LBS32: sCaliber = "32."; break;
		case CANNON_TYPE_CANNON_LBS36: sCaliber = "36."; break;
		case CANNON_TYPE_CANNON_LBS42: sCaliber = "42."; break;
		case CANNON_TYPE_CANNON_LBS48: sCaliber = "48."; break;
		case CANNON_TYPE_CULVERINE_LBS8: sCaliber = "8."; break;
		case CANNON_TYPE_CULVERINE_LBS12: sCaliber = "12."; break;
		case CANNON_TYPE_CULVERINE_LBS16: sCaliber = "16."; break;
		case CANNON_TYPE_CULVERINE_LBS20: sCaliber = "20."; break;
		case CANNON_TYPE_CULVERINE_LBS24: sCaliber = "24."; break;
		case CANNON_TYPE_CULVERINE_LBS32: sCaliber = "32."; break;
		case CANNON_TYPE_CULVERINE_LBS36: sCaliber = "36."; break;
		case CANNON_TYPE_NONECANNON: sCaliber = "0."; break;
	}
	return sCaliber;
}

void ClearShipInfo(int iNum)
{
	string sNot = "";
	string sHeader = "";

	switch(iNum)
	{
		case 1: sNot = "ShipOneNot"; sHeader = "ShipHeaderOne"; break;
		case 2: sNot = "ShipTwoNot"; sHeader = "ShipHeaderTwo"; break;
		case 3: sNot = "ShipThreeNot"; sHeader = "ShipHeaderThree"; break;
		case 4: sNot = "ShipFourNot"; sHeader = "ShipHeaderFour"; break;
	}

	string sShipType = "ShipType" + iNum;
	string sShipName = "sShipName" + iNum;
	string sBackgroundShipName = "BackgroundShipName" + iNum;
	string sBackgroundShipType = "BackgroundShipType" + iNum;
	string sShipHp = "ShipHp" + iNum;
	string sShipSp = "ShipSp" + iNum;
	string sShipSr = "ShipSr" + iNum;
	string sShipTr = "ShipTr" + iNum;
	string sShipCrew = "ShipCrew" + iNum;
	string sShipCannons = "ShipCannons" + iNum;
	string sShipClass = "ShipClass" + iNum;
	string sShipHpQuantity = "ShipHpQuantity" + iNum;
	string sShipSpQuantity = "ShipSpQuantity" + iNum;
	string sShipSrQuantity = "ShipSrQuantity" + iNum;
	string sShipTrQuantity = "ShipTrQuantity" + iNum;
	string sShipCrewQuantity = "ShipCrewQuantity" + iNum;
	string sShipCannonsQuantity = "ShipCannonsQuantity" + iNum;

	GameInterface.pictures.(sShipType).pic = "";
	GameInterface.pictures.(sShipName).pic = "";
	GameInterface.pictures.(sBackgroundShipName).pic = "";
	GameInterface.pictures.(sBackgroundShipType).pic = "";
	GameInterface.pictures.(sShipHp).pic = "";
	GameInterface.pictures.(sShipSp).pic = "";
	GameInterface.pictures.(sShipSr).pic = "";
	GameInterface.pictures.(sShipTr).pic = "";
	GameInterface.pictures.(sShipCrew).pic = "";
	GameInterface.pictures.(sShipCannons).pic = "";

	GameInterface.strings.(sNot) = "";
	GameInterface.strings.(sHeader) = "";
	GameInterface.strings.(sShipName) = "";
	GameInterface.strings.(sShipType) = "";
	GameInterface.strings.(sShipClass) = "";
	GameInterface.strings.(sShipHp) = "";
	GameInterface.strings.(sShipHpQuantity) = "";
	GameInterface.strings.(sShipSp) = "";
	GameInterface.strings.(sShipSpQuantity) = "";
	GameInterface.strings.(sShipSr) = "";
	GameInterface.strings.(sShipSrQuantity) = "";
	GameInterface.strings.(sShipTr) = "";
	GameInterface.strings.(sShipTrQuantity) = "";
	GameInterface.strings.(sShipCrew) = "";
	GameInterface.strings.(sShipCrewQuantity) = "";
	GameInterface.strings.(sShipCannons) = "";
	GameInterface.strings.(sShipCannonsQuantity) = "";
}

void RefreshShipsScroll(int i)
{
	//int st = sti(GameInterface.SHIPS_SCROLL.current);
	FillShipsScroll();
	//GameInterface.SHIPS_SCROLL.current = st;
	//nCurScrollNum = st;

	//GameInterface.SHIPS_SCROLL.ListSize = sti(GameInterface.SHIPS_SCROLL.ListSize) + i;
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"SHIPS_SCROLL",-1);
}


void SetChangeFrame(bool bInstall, bool bContinue)
{
	SetNodeUsing("FRAME_SHIP_1", bInstall);
	SetNodeUsing("FRAME_SHIP_2", bInstall);
	SetNodeUsing("FRAME_SHIP_3", bInstall);
	SetNodeUsing("FRAME_SHIP_4", bInstall);

	SetNodeUsing("TABLE_SHIP_1", bInstall);
	SetNodeUsing("INSTALL_SHIP1", bInstall);
	SetNodeUsing("REMOVE_SHIP1", bInstall);
	SetNodeUsing("REPAIR_SHIP1", bInstall);
	SetNodeUsing("GUARD_NOT_SHIP1", bInstall);
	SetNodeUsing("GUARD_YES_SHIP1", bInstall);
	SetNodeUsing("BORDERS_SHIP_1", bInstall);
	SetNodeUsing("BORDERS_SHIP_1_1", bInstall);
	SetNodeUsing("SHIP1_NAME", bInstall);

	SetNodeUsing("TABLE_SHIP_2", bInstall);
	SetNodeUsing("INSTALL_SHIP2", bInstall);
	SetNodeUsing("REMOVE_SHIP2", bInstall);
	SetNodeUsing("REPAIR_SHIP2", bInstall);
	SetNodeUsing("GUARD_NOT_SHIP2", bInstall);
	SetNodeUsing("GUARD_YES_SHIP2", bInstall);
	SetNodeUsing("BORDERS_SHIP_2", bInstall);
	SetNodeUsing("BORDERS_SHIP_2_1", bInstall);
	SetNodeUsing("SHIP2_NAME", bInstall);

	SetNodeUsing("TABLE_SHIP_3", bInstall);
	SetNodeUsing("INSTALL_SHIP3", bInstall);
	SetNodeUsing("REMOVE_SHIP3", bInstall);
	SetNodeUsing("REPAIR_SHIP3", bInstall);
	SetNodeUsing("GUARD_NOT_SHIP3", bInstall);
	SetNodeUsing("GUARD_YES_SHIP3", bInstall);
	SetNodeUsing("BORDERS_SHIP_3", bInstall);
	SetNodeUsing("BORDERS_SHIP_3_1", bInstall);
	SetNodeUsing("SHIP3_NAME", bInstall);

	SetNodeUsing("TABLE_SHIP_4", bInstall);
	SetNodeUsing("INSTALL_SHIP4", bInstall);
	SetNodeUsing("REMOVE_SHIP4", bInstall);
	SetNodeUsing("REPAIR_SHIP4", bInstall);
	SetNodeUsing("GUARD_NOT_SHIP4", bInstall);
	SetNodeUsing("GUARD_YES_SHIP4", bInstall);
	SetNodeUsing("BORDERS_SHIP_4", bInstall);
	SetNodeUsing("BORDERS_SHIP_4_1", bInstall);
	SetNodeUsing("SHIP4_NAME", bInstall);
	SetNodeUsing("GUARD_CHANGE", false);

	if(!bContinue)
	{

		GameInterface.pictures.ShipTypeInstall.pic = "";
		GameInterface.pictures.BackgroundShipTypeInstall.pic = "";
		GameInterface.pictures.BackgroundShipNameInstall.pic = "";
		GameInterface.pictures.ShipHpInstall.pic = "";
		GameInterface.pictures.ShipSpInstall.pic = "";
		GameInterface.pictures.ShipSrInstall.pic = "";
		GameInterface.pictures.ShipTrInstall.pic = "";
		GameInterface.pictures.ShipCrewInstall.pic = "";
		GameInterface.pictures.ShipCannonsInstall.pic = "";
		GameInterface.pictures.ShipCannonsTypeInstall.pic = "";

		GameInterface.strings.ShipChangeFrameHeader = "";
		GameInterface.strings.ShipTypeInstall = "";
		GameInterface.strings.ShipClassInstall = "";
		GameInterface.strings.ShipHpInstall = "";
		GameInterface.strings.ShipHpQuantityInstall = "";
		GameInterface.strings.ShipSpInstall = "";
		GameInterface.strings.ShipSpQuantityInstall = "";
		GameInterface.strings.ShipSrInstall = "";
		GameInterface.strings.ShipSrQuantityInstall = "";
		GameInterface.strings.ShipTrInstall = "";
		GameInterface.strings.ShipTrQuantityInstall = "";
		GameInterface.strings.ShipCrewInstall = "";
		GameInterface.strings.ShipCrewQuantityInstall = "";
		GameInterface.strings.ShipCannonsInstall = "";
		GameInterface.strings.ShipCannonsQuantityInstall = "";
		GameInterface.strings.ShipCannonsQuantityInstall = "";
		GameInterface.strings.ShipCannonsTypeInstall = "";
		GameInterface.strings.ShipCannonsTypeInstall1 = "";

		GameInterface.pictures.ShipTypeChange.tex = "";
		GameInterface.pictures.BackgroundShipTypeChange.pic = "";
		GameInterface.pictures.BackgroundShipNameChange.pic = "";
		GameInterface.strings.ShipNameChange = "";
		GameInterface.strings.ShipTypeChange = "";
		GameInterface.strings.ShipClassChange = "";

		GameInterface.pictures.ShipTypeChange2.tex = "";
		GameInterface.pictures.BackgroundShipTypeChange2.pic = "";
		GameInterface.pictures.BackgroundShipNameChange2.pic = "";
		GameInterface.strings.ShipNameChange2 = "";
		GameInterface.strings.ShipTypeChange2 = "";
		GameInterface.strings.ShipClassChange2 = "";

		SetNodeUsing("FRAME_SHIP_CHANGE", false);
		SetNodeUsing("CHANGE_OK", false);
		SetNodeUsing("CHANGE_CANCEL", false);
		SetNodeUsing("CHANGE_LEFT", false);
		SetNodeUsing("CHANGE_RIGHT", false);
		SetNodeUsing("BORDERS_SHIP_INSTALL", false);
		SetNodeUsing("BORDERS_SHIP_INSTALL_1", false);
		SetNodeUsing("BORDERS_SHIP_CHANGE_LEFT", false);
		SetNodeUsing("BORDERS_SHIP_CHANGE_LEFT_1", false);
		SetNodeUsing("BORDERS_SHIP_CHANGE_RIGHT", false);
		SetNodeUsing("BORDERS_SHIP_CHANGE_RIGHT_1", false);
	}

	if(bContinue)
	{
		GameInterface.pictures.ShipType1.pic = "";
		GameInterface.pictures.BackgroundShipName1.pic = "";
		GameInterface.pictures.BackgroundShipType1.pic = "";
		GameInterface.pictures.ShipHp1.pic = "";
		GameInterface.pictures.ShipSp1.pic = "";
		GameInterface.pictures.ShipSr1.pic = "";
		GameInterface.pictures.ShipTr1.pic = "";
		GameInterface.pictures.ShipCrew1.pic = "";
		GameInterface.pictures.ShipCannons1.pic = "";

		GameInterface.strings.ShipOneNot = "";
		GameInterface.strings.ShipHeaderOne = "";
		GameInterface.strings.ShipName1 = "";
		GameInterface.strings.ShipType1 = "";
		GameInterface.strings.ShipClass1 = "";
		GameInterface.strings.ShipHp1 = "";
		GameInterface.strings.ShipHpQuantity1 = "";
		GameInterface.strings.ShipSp1 = "";
		GameInterface.strings.ShipSpQuantity1 = "";
		GameInterface.strings.ShipSr1 = "";
		GameInterface.strings.ShipSrQuantity1 = "";
		GameInterface.strings.ShipTr1 = "";
		GameInterface.strings.ShipTrQuantity1 = "";
		GameInterface.strings.ShipCrew1 = "";
		GameInterface.strings.ShipCrewQuantity1 = "";
		GameInterface.strings.ShipCannons1 = "";
		GameInterface.strings.ShipCannonsQuantity1 = "";

		GameInterface.pictures.ShipType2.pic = "";
		GameInterface.pictures.BackgroundShipName2.pic = "";
		GameInterface.pictures.BackgroundShipType2.pic = "";
		GameInterface.pictures.ShipHp2.pic = "";
		GameInterface.pictures.ShipSp2.pic = "";
		GameInterface.pictures.ShipSr2.pic = "";
		GameInterface.pictures.ShipTr2.pic = "";
		GameInterface.pictures.ShipCrew2.pic = "";
		GameInterface.pictures.ShipCannons2.pic = "";

		GameInterface.strings.ShipTwoNot = "";
		GameInterface.strings.ShipHeaderTwo = "";
		GameInterface.strings.ShipName2 = "";
		GameInterface.strings.ShipType2 = "";
		GameInterface.strings.ShipClass2 = "";
		GameInterface.strings.ShipHp2 = "";
		GameInterface.strings.ShipHpQuantity2 = "";
		GameInterface.strings.ShipSp2 = "";
		GameInterface.strings.ShipSpQuantity2 = "";
		GameInterface.strings.ShipSr2 = "";
		GameInterface.strings.ShipSrQuantity2 = "";
		GameInterface.strings.ShipTr2 = "";
		GameInterface.strings.ShipTrQuantity2 = "";
		GameInterface.strings.ShipCrew2 = "";
		GameInterface.strings.ShipCrewQuantity2 = "";
		GameInterface.strings.ShipCannons2 = "";
		GameInterface.strings.ShipCannonsQuantity2 = "";

		GameInterface.pictures.ShipType3.pic = "";
		GameInterface.pictures.BackgroundShipName3.pic = "";
		GameInterface.pictures.BackgroundShipType3.pic = "";
		GameInterface.pictures.ShipHp3.pic = "";
		GameInterface.pictures.ShipSp3.pic = "";
		GameInterface.pictures.ShipSr3.pic = "";
		GameInterface.pictures.ShipTr3.pic = "";
		GameInterface.pictures.ShipCrew3.pic = "";
		GameInterface.pictures.ShipCannons3.pic = "";

		GameInterface.strings.ShipThreeNot = "";
		GameInterface.strings.ShipHeaderThree = "";
		GameInterface.strings.ShipName3 = "";
		GameInterface.strings.ShipType3 = "";
		GameInterface.strings.ShipClass3 = "";
		GameInterface.strings.ShipHp3 = "";
		GameInterface.strings.ShipHpQuantity3 = "";
		GameInterface.strings.ShipSp3 = "";
		GameInterface.strings.ShipSpQuantity3 = "";
		GameInterface.strings.ShipSr3 = "";
		GameInterface.strings.ShipSrQuantity3 = "";
		GameInterface.strings.ShipTr3 = "";
		GameInterface.strings.ShipTrQuantity3 = "";
		GameInterface.strings.ShipCrew3 = "";
		GameInterface.strings.ShipCrewQuantity3 = "";
		GameInterface.strings.ShipCannons3 = "";
		GameInterface.strings.ShipCannonsQuantity3 = "";

		GameInterface.pictures.ShipType4.pic = "";
		GameInterface.pictures.BackgroundShipName4.pic = "";
		GameInterface.pictures.BackgroundShipType4.pic = "";
		GameInterface.pictures.ShipHp4.pic = "";
		GameInterface.pictures.ShipSp4.pic = "";
		GameInterface.pictures.ShipSr4.pic = "";
		GameInterface.pictures.ShipTr4.pic = "";
		GameInterface.pictures.ShipCrew4.pic = "";
		GameInterface.pictures.ShipCannons4.pic = "";

		GameInterface.strings.ShipFourNot = "";
		GameInterface.strings.ShipHeaderFour = "";
		GameInterface.strings.ShipName4 = "";
		GameInterface.strings.ShipType4 = "";
		GameInterface.strings.ShipClass4 = "";
		GameInterface.strings.ShipHp4 = "";
		GameInterface.strings.ShipHpQuantity4 = "";
		GameInterface.strings.ShipSp4 = "";
		GameInterface.strings.ShipSpQuantity4 = "";
		GameInterface.strings.ShipSr4 = "";
		GameInterface.strings.ShipSrQuantity4 = "";
		GameInterface.strings.ShipTr4 = "";
		GameInterface.strings.ShipTrQuantity4 = "";
		GameInterface.strings.ShipCrew4 = "";
		GameInterface.strings.ShipCrewQuantity4 = "";
		GameInterface.strings.ShipCannons4 = "";
		GameInterface.strings.ShipCannonsQuantity4 = "";

		CreateString(true,"ShipChangeFrameHeader","Поменять флагман", FONT_CAPTION, COLOR_NORMAL, 395,129,SCRIPT_ALIGN_CENTER,1.5);
		SetNodeUsing("FRAME_SHIP_CHANGE", true);
		SetNodeUsing("CHANGE_OK", true);
		SetNodeUsing("CHANGE_CANCEL", true);
		SetNodeUsing("CHANGE_LEFT", true);
		SetNodeUsing("CHANGE_RIGHT", true);
		SetNodeUsing("BORDERS_SHIP_CHANGE_LEFT", true);
		SetNodeUsing("BORDERS_SHIP_CHANGE_LEFT_1", true);
		SetNodeUsing("BORDERS_SHIP_CHANGE_RIGHT", true);
		SetNodeUsing("BORDERS_SHIP_CHANGE_RIGHT_1", true);
		SetSelectable("CHANGE_OK", true);
		SetChangeInformation();
		//SetInstallInformation(0);
	}
}

void SetChangeInformation()
{
	int iShipOne = sti(PChar.Colony.Guardians.Ship1);

	int iCharacterOne = iShipOne;
	ref chr = &Characters[iCharacterOne];

	ref rShip = GetRealShip(sti(chr.ship.type));
	int iShipClass = sti(rShip.class);
	string sShipType = ShipsTypes[sti(rShip.basetype)].name);
	string sShipName = chr.Ship.name;

	CreateImage("ShipTypeChange", "SHIPS_" + sShipType, "ship", 116,224,306,414);

	CreateString(true,"ShipNameChange", sShipName, FONT_CAPTION, COLOR_NORMAL, 210,196,SCRIPT_ALIGN_CENTER,1.2);

	CreateString(true,"ShipTypeChange", XI_ConvertString(sShipType), FONT_CAPTION, COLOR_NORMAL, 210,417,SCRIPT_ALIGN_CENTER,1.2);
	CreateString(true,"ShipClassChange", iShipClass, FONT_BOLD_NUMBERS, COLOR_NORMAL, 280,390,SCRIPT_ALIGN_LEFT,1.0);

	string sShip = "Ship" + iChangeCount;
	int iShipTwo = sti(PChar.Colony.Guardians.(sShip));
	chr = &Characters[iShipTwo];

	rShip = GetRealShip(sti(chr.ship.type));
	iShipClass = sti(rShip.class);
	sShipType = ShipsTypes[sti(rShip.basetype)].name);
	sShipName = chr.Ship.name;

	CreateImage("ShipTypeChange2", "SHIPS_" + sShipType, "ship", 426,224,616,414);

	CreateString(true,"ShipNameChange2", sShipName, FONT_CAPTION, COLOR_NORMAL, 520,196,SCRIPT_ALIGN_CENTER,1.2);

	CreateString(true,"ShipTypeChange2", XI_ConvertString(sShipType), FONT_CAPTION, COLOR_NORMAL, 520,417,SCRIPT_ALIGN_CENTER,1.2);
	CreateString(true,"ShipClassChange2", iShipClass, FONT_BOLD_NUMBERS, COLOR_NORMAL, 590,390,SCRIPT_ALIGN_LEFT,1.0);
}

void ChangeShipsOK()
{
	string sShip = "Ship" + iChangeCount;

	int iShipOne = sti(PChar.Colony.Guardians.Ship1);
	int iShipTwo = sti(PChar.Colony.Guardians.(sShip));
	if (iShipTwo == sti(PChar.Colony.Guardians.Ship3))
	{
		pchar.g3 = iShipOne;
	}
	if (iShipTwo == sti(PChar.Colony.Guardians.Ship4))
	{
		pchar.g4 = iShipOne;
	}

	PChar.Colony.Guardians.Ship1 = iShipTwo;
	PChar.Colony.Guardians.(sShip) = iShipOne;

	string sGroup = "InterfaceColonyGuardians_1";
	if(Group_FindGroup(sGroup) != -1)
	{
		Group_DeleteGroup(sGroup);
	}

	sGroup = "InterfaceColonyGuardians_" + iChangeCount;
	if(Group_FindGroup(sGroup) != -1)
	{
		Group_DeleteGroup(sGroup);
	}

	ref chr = &Characters[iShipTwo];
	sGroup = "InterfaceColonyGuardians_1";
	Group_FindOrCreateGroup(sGroup);

	Group_SetType(sGroup, "war");
	Group_AddCharacter(sGroup, chr.id);
	Group_SetGroupCommander(sGroup, chr.id);

	chr = &Characters[iShipOne];
	sGroup = "InterfaceColonyGuardians_" + iChangeCount;
	Group_FindOrCreateGroup(sGroup);

	Group_SetType(sGroup, "war");
	Group_AddCharacter(sGroup, chr.id);
	Group_SetGroupCommander(sGroup, chr.id);

	GuardianInizialization(iShipTwo, 1, true);
	GuardianInizialization(iShipOne, iChangeCount, false);

	SetChangeFrame(true, false);
	SetInformation();
}

void CheckChangeShips(bool left)
{
	int iMax = GetMaxChangeShips();

	if(left)
	{
		iChangeCount--;
	}
	else
	{
		iChangeCount++;
	}

	if(iChangeCount < 2)
	{
		iChangeCount = iMax;
	}

	if(iChangeCount > iMax)
	{
		iChangeCount = 2;
	}


	SetChangeInformation();
}

int GetMaxChangeShips()
{
	int iMax = 0;

	string sShip;
	for(int i=1; i <= 4; i++)
	{
		sShip = "Ship" + i;

		if(PChar.Colony.Guardians.(sShip) != -1)
		{
			iMax++;
		}
	}

	return iMax;
}

