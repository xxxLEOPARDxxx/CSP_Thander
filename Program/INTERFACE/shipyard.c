/// BOAL Верфь
#define sailCostPercent		10
#define hullCostPercent		20
#define paintCostPercent 0.75
int nCurScrollNum;
ref xi_refCharacter;
ref refNPCShipyard;
int shipIndex;
int upgradevalue;
int uptype = 0;
string SellState = "Max";

int nCurScrollOfficerNum;

string CurTable, CurRow;
int iSelected; // курсор в таблице

string sMessageMode, sFrom_sea, sShipId;

float shipCostRate;
bool  bShipyardOnTop, bEmptySlot;

int RepairHull, RepairSail;
int timeHull, timeRig, timePaint, timeUpgrade, timePreUpgrade, timeSoil;

int iSoilClearCost;

//// {*} BUHO-FIST - ADDED CODE - Fist state variable
#define FIS_ALL		0		// Normal
#define FIS_1		1		// C1
#define FIS_2		2		// C2
#define FIS_3		3		// C3
#define FIS_4		4		// C4
#define FIS_5		5		// C5
#define FIS_6		6		// C6
#define FIS_7		7		// C7
int FIS_FilterState = FIS_ALL;
//// {*} BUHO END ADDITION

void InitInterface_R(string iniName, ref _shipyarder)
{
	GameInterface.title = "titleShipyard";

	xi_refCharacter = pchar;

    refNPCShipyard  = _shipyarder;
    SetShipyardStore(refNPCShipyard);

    shipCostRate = stf(refNPCShipyard.ShipCostRate);

    int iTest = FindColony(refNPCShipyard.City); // город магазина
    ref rColony;
    sFrom_sea = "";
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
		sFrom_sea = rColony.from_sea; // ветка верфи, в сухопутных верфи нет, значит везде правильная
	}

	FillShipsScroll();

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessExitCancel",0);
	SetEventHandler("exitCancel","ProcessExitCancel",0);
    SetEventHandler("ievnt_command","ProcessCommandExecute",0);
    SetEventHandler("frame","ProcessFrame",1);
    SetEventHandler("confirmShipChangeName","confirmShipChangeName",0);
	SetEventHandler("CheckForRename","CheckForRename",0);
	SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
	SetEventHandler("MouseRClickUp","HideInfoWindow",0);
	SetEventHandler("TableSelectChange", "TableSelectChange", 0);
	SetEventHandler("ExitMsgMenu", "ExitMsgMenu", 0);
	SetEventHandler("ExitRepairMenu", "ExitRepairMenu", 0);
	SetEventHandler("ShowOtherClick", "ShowOtherClick", 0);
	SetEventHandler("ExitCannonsMenu", "ExitCannonsMenu", 0);
    SetEventHandler("ExitOfficerMenu","ExitOfficerMenu",0);
	SetEventHandler("acceptaddofficer","AcceptAddOfficer",0);
	SetEventHandler("BuyShipEvent","BuyShipEvent",0);
	SetEventHandler("ClickREPAIR_Soiling","ClickREPAIR_Soiling",0);
	SetEventHandler("OpenShipUp","OpenShipUp",0);
	SetEventHandler("CloseShipUp", "CloseShipUp",0);
	SetEventHandler("ExitChangeHullMenu", "ExitChangeHullMenu",0);
	SetEventHandler("CheckButtonChange","procCheckBoxChange",0);
	SetEventHandler("SelectShipyard","SelectShipyard",0);
    //////////////////
    EI_CreateFrame("SHIP_BIG_PICTURE_BORDER",156,40,366,275); // tak from SHIP_BIG_PICTURE
    EI_CreateHLine("SHIP_BIG_PICTURE_BORDER", 161,246,361,1, 4);
    EI_CreateFrame("SHIP_BIG_PICTURE_BORDER",20,46,134,161);
    EI_CreateHLine("SHIP_BIG_PICTURE_BORDER", 8,187,147,1, 4);
    EI_CreateHLine("SHIP_BIG_PICTURE_BORDER", 8,166,147,1, 4);

    SetNewGroupPicture("Money_PIC", "ICONS_CHAR", "Money");
    SetNewGroupPicture("REPAIR_Money_PIC", "ICONS_CHAR", "Money");

    SetNewGroupPicture("REPAIR_Hull_PIC", "SHIP_STATE_ICONS", "Hull");
    SetNewGroupPicture("REPAIR_Sails_PIC", "SHIP_STATE_ICONS", "Sails");

    SetNewGroupPicture("EXTRAHULLON", "SHIP_UPGRADES", "EXTRAHULLON");
    SetNewGroupPicture("EXTRASAILON", "SHIP_UPGRADES", "EXTRASAILON");
    SetNewGroupPicture("EXTRAGUNSON", "SHIP_UPGRADES", "EXTRAGUNSON");
    SetNewGroupPicture("EXTRAHULLKRENGON", "SHIP_UPGRADES", "EXTRAHULLKRENGON");
    SetNewGroupPicture("EXTRACAPACITYON", "SHIP_UPGRADES", "EXTRACAPACITYON");
    SetNewGroupPicture("EXTRABIGSIDESON", "SHIP_UPGRADES", "EXTRABIGSIDESON");

    FillShipyardTable();

	SetCurrentNode("SHIPS_SCROLL");
	bShipyardOnTop = false;
	OnShipScrollChange();
	bEmptySlot = false;
	sMessageMode = "";
	SetButtionsAccess();
	timeHull = 0;
	timeRig = 0;
	timePaint = 0;
	timeUpgrade = 0;
	timePreUpgrade = 0;
	timeSoil = 0;

	ProcessFilter();
}

void ProcessExitCancel()
{
    // boal время на ремонт -->
    if (timeSoil > 0 || timeRig > 0 || timeHull > 0 || timePaint > 0 || timeUpgrade > 0)
    {
        LAi_Fade("", "");
        bQuestCheckProcessFreeze = true;
    	WaitDate("",0,0,0, 0, makeint((timeSoil + timeHull/4.0 + timeRig/6.0 + timePaint/6.0 + timeUpgrade) * 60.0));
    	RecalculateJumpTable();
    	bQuestCheckProcessFreeze = false;
    	RefreshLandTime();
	}
	if (sti(pchar.ship.type) == SHIP_NOTUSED) PChar.nation = GetBaseHeroNation();
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessExitCancel");
	DelEventHandler("exitCancel","ProcessExitCancel");
    DelEventHandler("ievnt_command","ProcessCommandExecute");
    DelEventHandler("frame","ProcessFrame");
    DelEventHandler("confirmShipChangeName","confirmShipChangeName");
	DelEventHandler("CheckForRename","CheckForRename");
	DelEventHandler("ShowInfoWindow","ShowInfoWindow");
	DelEventHandler("MouseRClickUp","HideInfoWindow");
	DelEventHandler("TableSelectChange", "TableSelectChange");
	DelEventHandler("ExitMsgMenu", "ExitMsgMenu");
	DelEventHandler("ShowOtherClick", "ShowOtherClick");
	DelEventHandler("ExitCannonsMenu", "ExitCannonsMenu");
    DelEventHandler("ExitOfficerMenu","ExitOfficerMenu");
	DelEventHandler("acceptaddofficer","AcceptAddOfficer");
	DelEventHandler("ExitRepairMenu", "ExitRepairMenu");
	DelEventHandler("BuyShipEvent","BuyShipEvent");
	DelEventHandler("ClickREPAIR_Soiling","ClickREPAIR_Soiling");
	DelEventHandler("OpenShipUp","OpenShipUp");
	DelEventHandler("CloseShipUp","CloseShipUp");
	DelEventHandler("ExitChangeHullMenu", "ExitChangeHullMenu");
	DelEventHandler("CheckButtonChange","procCheckBoxChange");
	DelEventHandler("SelectShipyard","SelectShipyard");

	interfaceResultCommand = exitCode;
	if( CheckAttribute(&InterfaceStates,"ReloadMenuExit"))
	{
        DeleteAttribute(&InterfaceStates,"ReloadMenuExit");
		EndCancelInterface(false);
	}
	else
	{
		EndCancelInterface(true);
	}
}

void SelectShipyard()
{
	SetCurrentNode("TABLE_SHIPYARD");
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();

    switch(nodName)
	{
		case "MSG_CREW_CHECKBOX":
			if (comName=="rclick")
			{
				string sText1, sText2, sText3, sPicture, sGroup, sGroupPicture;
				sText1 = "При выборе варианта ''Распределить до максимальной команды по кораблям'' в случае продажи корабля оставшаяся на нём команда распределяется по всем остальным кораблям поочерёдно, начиная с флагмана. При этом команда заполняется до перегруза. Навыки и мораль команды при этом перерассчитываются.";
				sText2 = "При выборе варианта ''Распределить до оптимальной команды по кораблям'' в случае продажи корабля оставшаяся на нём команда распределяется по всем остальным кораблям поочерёдно, начиная с флагмана. При этом команда заполняется до оптимальной, без перегруза.  Навыки и мораль команды при этом перерассчитываются.";
				sText3 = "При выборе варианта ''Уволить в таверну'' в случае продажи корабля оставшаяся на нём команда отправляется в таверну, сливаясь по умениям с уже наличествующими там претендентами в команду.";
				sPicture = "none";
			    CreateTooltip("#" + "Увольнение команды", sText1, argb(255,255,255,255), sText2, argb(255,255,255,255), sText3, argb(255,255,255,255), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 256, 256);
			}
		break;
        case "BUTTON_SELL":
			if (comName=="click" || comName=="activate")
			{
			    ShowMessageInfo();
			}
		break;

		case "BUTTON_BUY":
			if (comName=="click" || comName=="activate")
			{
			    ShowMessageInfo();
			}
		break;
		//#20180922-01
		case "BUTTON_PAINT":
			if (comName=="click" || comName=="activate")
			{
			    ShowChangeHullMenu();
			}
		break;

		case "CHANGE_HULL_LEFT":
			if(comName=="click")
			{
				SelectChangeHull(true);
			}
		break;

		case "CHANGE_HULL_RIGHT":
			if(comName=="click")
			{
				SelectChangeHull(false);
			}
		break;

		case "CHANGE_HULL_OK":
			if(comName=="click")
			{
				SetNewHullToCharacterShip();
			}
		break;

		case "SHIPSUP_BUTTON":
			if (comName=="click" || comName=="activate")
			{
			    OpenShipUp();
			}
		break;

		case "SHIPSUP_DOUP":
			if (comName=="click" || comName=="activate")
			{
			    DoUpgrade();
			}
		break;

		case "CLASS_ALL":
			if (comName == "click")ProcessFilter();
		break;

		case "MSG_OK":
			if (comName=="click" || comName=="activate")
			{
			    MessageOk();
			}
		break;

		case "BUTTON_REPAIR":
			if (comName=="click" || comName=="activate")
			{
			    ShowRepairMenu();
			}
		break;

		case "REPAIR_LEFT_H":
			if (comName=="click" || comName=="activate")
			{
			    ClickRepairArror("hull", -1);
			}
			if (comName=="rclick")
			{
			    ClickRepairArror("hull", -5);
			}
		break;

		case "REPAIR_RIGHT_H":
			if (comName=="click" || comName=="activate")
			{
			    ClickRepairArror("hull", 1);
			}
			if (comName=="rclick")
			{
			    ClickRepairArror("hull", 5);
			}
		break;

		case "REPAIR_LEFT_S":
			if (comName=="click" || comName=="activate")
			{
			    ClickRepairArror("sail", -1);
			}
			if (comName=="rclick")
			{
			    ClickRepairArror("sail", -5);
			}
		break;

		case "REPAIR_RIGHT_S":
			if (comName=="click" || comName=="activate")
			{
			    ClickRepairArror("sail", 1);
			}
			if (comName=="rclick")
			{
			    ClickRepairArror("sail", 5);
			}
		break;

		case "REPAIR_OK":
			if (comName=="click" || comName=="activate")
			{
			    RepairOk();
			}
		break;

		case "REPAIR_ALL":
			if (comName=="click" || comName=="activate")
			{
			    RepairAll();
			}
		break;
	}
}

void procCheckBoxChange()
{
	string sNodName = GetEventData();
	int nBtnIndex = GetEventData();
	int bBtnState = GetEventData();

	if( sNodName == "MSG_CREW_CHECKBOX" ) {
		if( bBtnState==true ) {
			switch( nBtnIndex ) {
			case 1: SellState="Max"; break;
			case 2: SellState="Opt" break;
			case 3: SellState="Fire" break;
			}
		}
		return;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////
void FillShipsScroll()
{
    DeleteAttribute(&GameInterface, "SHIPS_SCROLL");
	nCurScrollNum = -1;
	if(!CheckAttribute(&GameInterface,"SHIPS_SCROLL.current"))
	{
		GameInterface.SHIPS_SCROLL.current = 0;
	}

	string attributeName;
	string shipName;
	int iShipType, cn;
	GameInterface.SHIPS_SCROLL.ImagesGroup.t0 = "BLANK_SHIP2";

	FillShipList("SHIPS_SCROLL.ImagesGroup", xi_refCharacter);
	GameInterface.SHIPS_SCROLL.BadTex1 = 0;
	GameInterface.SHIPS_SCROLL.BadPic1 = "Not Used2";

	int m = 0;
	for(int i = 0; i < COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);
		if(cn != -1)
		{
			iShipType = sti(characters[cn].ship.type);
			if(iShipType != SHIP_NOTUSED)
			{
				attributeName = "pic" + (m+1);
				iShipType = sti(RealShips[iShipType].basetype);
				shipName = ShipsTypes[iShipType].Name;

				GameInterface.SHIPS_SCROLL.(attributeName).character = cn;
				GameInterface.SHIPS_SCROLL.(attributeName).str1 = "#"+"Класс "+ShipsTypes[iShipType].Class;
				GameInterface.SHIPS_SCROLL.(attributeName).str4 = shipName;
				GameInterface.SHIPS_SCROLL.(attributeName).str3 = "#" + MakeMoneyShow(GetShipSellPrice(&characters[cn], refNPCShipyard), MONEY_SIGN,MONEY_DELIVER);
				GameInterface.SHIPS_SCROLL.(attributeName).img1 = "ship";
				GameInterface.SHIPS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("SHIPS_SCROLL.ImagesGroup","SHIPS_"+shipName);
				m++;
			}
			else
			{
				attributeName = "pic" + (m+1);
				GameInterface.SHIPS_SCROLL.(attributeName).character = cn;
				GameInterface.SHIPS_SCROLL.(attributeName).str1 = "#";
				GameInterface.SHIPS_SCROLL.(attributeName).str2 = "NoneBoat";
				GameInterface.SHIPS_SCROLL.(attributeName).img1 = "Not Used2";
				GameInterface.SHIPS_SCROLL.(attributeName).tex1 = "BLANK_SHIP2";
				m++;
			}
		}
		else
		{
		    attributeName = "pic" + (m+1);
			GameInterface.SHIPS_SCROLL.(attributeName).character = -1;
			GameInterface.SHIPS_SCROLL.(attributeName).str1 = "#";
			GameInterface.SHIPS_SCROLL.(attributeName).str2 = "";
			GameInterface.SHIPS_SCROLL.(attributeName).img1 = "Not Used2";
			GameInterface.SHIPS_SCROLL.(attributeName).tex1 = "BLANK_SHIP2";
			m++;
		}
	}

	GameInterface.SHIPS_SCROLL.ListSize = m;
	//GameInterface.SHIPS_SCROLL.NotUsed = 5 - m + 1;
	GameInterface.SHIPS_SCROLL.NotUsed = 0;
}

void ProcessFrame()
{
	string attributeName;
	int iCharacter;

	string sNode = GetCurrentNode();

    if (sNode == "PASSENGERSLIST" && sti(GameInterface.PASSENGERSLIST.current)!= nCurScrollOfficerNum)
	{
		nCurScrollOfficerNum = sti(GameInterface.PASSENGERSLIST.current);
		SetOfficersSkills();
	}
	if(sNode == "SHIPS_SCROLL")
	{
		if (sti(GameInterface.SHIPS_SCROLL.current)!= nCurScrollNum || CurTable != "")
		{
            CurTable = "";
			NullSelectTable("TABLE_SHIPYARD"); // убрать скрол
			bShipyardOnTop = false;

			nCurScrollNum = sti(GameInterface.SHIPS_SCROLL.current);

			attributeName = "pic" + (nCurScrollNum+1);

			iCharacter = sti(GameInterface.SHIPS_SCROLL.(attributeName).character);

			if(iCharacter > 0)
			{
				string sChrId = characters[iCharacter].id;

				xi_refCharacter = characterFromID(sChrId);
				bEmptySlot = false;
				shipIndex= nCurScrollNum+ 1;
				if (shipIndex< 0)
				{
					shipIndex= 0;
				}
				if (sti(xi_refCharacter.ship.type) == SHIP_NOTUSED)
				{
					shipIndex= -1;
				}
				// boal оптимизация скилов -->
			    DelBakSkillAttr(xi_refCharacter);
			    ClearCharacterExpRate(xi_refCharacter);
			    RefreshCharacterSkillExpRate(xi_refCharacter);

			    SetEnergyToCharacter(xi_refCharacter);
			    // boal оптимизация скилов <--
				OnShipScrollChange();
			}
			else
			{
				shipIndex= -1;
				bEmptySlot = true;
			}
			SetButtionsAccess();
		}
	}
}

void FillShipParam(ref _chr)
{
    int iShip = sti(_chr.ship.type);
	if (iShip != SHIP_NOTUSED)
	{
        if (CheckAttribute(_chr, "Ship.Cargo.RecalculateCargoLoad") && sti(_chr.Ship.Cargo.RecalculateCargoLoad))
		{
			RecalculateCargoLoad(_chr);
			_chr.Ship.Cargo.RecalculateCargoLoad = 0;
		}
		ref refBaseShip = GetRealShip(iShip);
		string sShip = refBaseShip.BaseName;
		SetNewPicture("SHIP_BIG_PICTURE", "interfaces\ships\" + sShip + ".tga");
		if (!CheckAttribute(refBaseShip,"QuestShip")) SetNodeUsing("SHIP_BIG_PICTURE_VIDEO",false);
		else
		{
			SetNewPicture("SHIP_BIG_PICTURE", "interfaces\ships\" + sShip + ".tga.tx");
			SetNodeUsing("SHIP_BIG_PICTURE_VIDEO",true);
			SetNewVideoPicture("SHIP_BIG_PICTURE_VIDEO","SHIP_"+sShip);
		}

		GameInterface.edit_box.str = _chr.ship.name;
		SetFormatedText("SHIP_RANK", refBaseShip.Class);
		SetFormatedText("CLASS_ARMOR", refBaseShip.HullArmor);
		SetNewGroupPicture("CLASS_ARMOR_ICON", "ICONS_CHAR", "Reputation");
		SetShipOTHERTable("TABLE_OTHER", _chr);

		if (CheckAttribute(refBaseShip,"Tuning.HullSpecial")) SetNewGroupPicture("EXTRAHULLON", "SHIP_UPGRADES", "EXTRAHULLON");
		else SetNewGroupPicture("EXTRAHULLON", "SHIP_UPGRADES", "EXTRAHULLOFF");
		if (CheckAttribute(refBaseShip,"Tuning.SailsSpecial")) SetNewGroupPicture("EXTRASAILON", "SHIP_UPGRADES", "EXTRASAILON");
		else SetNewGroupPicture("EXTRASAILON", "SHIP_UPGRADES", "EXTRASAILOFF");
		if (CheckAttribute(refBaseShip,"Tuning.CannonsSpecial")) SetNewGroupPicture("EXTRAGUNSON", "SHIP_UPGRADES", "EXTRAGUNSON");
		else SetNewGroupPicture("EXTRAGUNSON", "SHIP_UPGRADES", "EXTRAGUNSOFF");
		if (CheckAttribute(refBaseShip,"Tuning.CuBot")) SetNewGroupPicture("EXTRAHULLKRENGON", "SHIP_UPGRADES", "EXTRAHULLKRENGON");
		else SetNewGroupPicture("EXTRAHULLKRENGON", "SHIP_UPGRADES", "EXTRAHULLKRENGOFF");
		if (CheckAttribute(refBaseShip,"Tuning.BotPack")) SetNewGroupPicture("ExtraCapacityOn", "SHIP_UPGRADES", "ExtraCapacityOn");
		else SetNewGroupPicture("ExtraCapacityOn", "SHIP_UPGRADES", "ExtraCapacityOff");
		if (CheckAttribute(refBaseShip,"Tuning.HighBort")) SetNewGroupPicture("ExtraBigSidesOn", "SHIP_UPGRADES", "ExtraBigSidesOn");
		else SetNewGroupPicture("ExtraBigSidesOn", "SHIP_UPGRADES", "ExtraBigSidesOff");

		SetShipQualityTable(_chr, "BAR_HP", "BAR_Mast", "BAR_Speed", "BAR_TurnRate", "BAR_WAS", "BAR_Capacity", "BAR_Crew");
		SetFormatedText("FRAME_INFO_CAPTION", XI_ConvertString(sShip));
		SetFormatedText("INFO_TEXT", GetConvertStr(sShip, "ShipsDescribe.txt"));
	}
	else
	{
		SetNewPicture("SHIP_BIG_PICTURE", "interfaces\blank_ship2.tga");
		SetNodeUsing("SHIP_BIG_PICTURE_VIDEO",false);
		GameInterface.edit_box.str = XI_Convertstring("NoneBoat");
		SetFormatedText("FRAME_INFO_CAPTION","");
		SetFormatedText("INFO_TEXT","");
	}
	Table_UpdateWindow("TABLE_OTHER");
}

void OnShipScrollChange()
{
	SetNewPicture("MAIN_CHARACTER_PICTURE", "interfaces\portraits\128\face_" + xi_refCharacter.FaceId + ".tga");
	SetFormatedText("HERO_NAME", GetFullName(xi_refCharacter));
	SetFormatedText("HERO_RANK",xi_refCharacter.Rank);
	// нулим все формы, тк корабля может не быть
	SetFormatedText("SHIP_RANK","");
	Table_Clear("TABLE_OTHER", false, true, false);
	//Ship info window
	SetFormatedText("Money_TEXT", MakeMoneyShow(sti(pchar.Money), MONEY_SIGN,MONEY_DELIVER));
    FillShipParam(xi_refCharacter);
}

void confirmShipChangeName()
{
	/*
	if (shipIndex== -1) return;
	xi_refcharacter.ship.name = GameInterface.edit_box.str;
	GameInterface.edit_box.str = xi_refcharacter.ship.name;
	SetCurrentNode("SHIP_INFO_TEXT");   */
}

void CheckForRename()
{
	/*if (GetShipRemovable(xi_refCharacter) == true && shipIndex!= -1)
	{
		SetCurrentNode("EDIT_BOX");
	}    */
}

void ShowInfoWindow()
{
	string sCurrentNode = GetCurrentNode();
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;
	int iItem;
	int xx = 256;
	int yy = 256;

	//Boyer fix #20170401-01 Can't load texture -1.tx log errors
	//sPicture = "-1";
	sPicture = "";
	string sAttributeName;
	int nChooseNum = -1;
	int iShip;
	ref refBaseShip;

	bool  bShowHint = true;

	ref rChr;
	if (bShipyardOnTop)
	{
	    rChr = refNPCShipyard;
	}
	else
	{
		rChr = xi_refCharacter;
	}
	switch (sCurrentNode)
	{
		case "SHIP_BIG_PICTURE":
			if (shipIndex != -1 || bShipyardOnTop)
			{
			    iShip = sti(rChr.ship.type);
			    refBaseShip = GetRealShip(iShip);
				sHeader = XI_ConvertString(refBaseShip.BaseName);
				sText1 = GetConvertStr(refBaseShip.BaseName, "ShipsDescribe.txt");
			}
			else
			{
				sHeader = XI_Convertstring("NoneBoat");
				sText1  = GetConvertStr("NoneBoat2", "ShipsDescribe.txt");
			}
		break;

		case "SHIPS_SCROLL":
			if (shipIndex != -1)
			{
			    iShip = sti(xi_refCharacter.ship.type);
			    refBaseShip = GetRealShip(iShip);
				sHeader = XI_ConvertString(refBaseShip.BaseName);
				sText1 = GetConvertStr(refBaseShip.BaseName, "ShipsDescribe.txt");
				//sText2 = GetRPGText("shipChoose_hint");
			}
			else
			{
				sHeader = XI_Convertstring("NoneBoat");
				sText1  = GetConvertStr("NoneBoat2", "ShipsDescribe.txt");
			}
		break;

		case "MAIN_CHARACTER_PICTURE":
			// отдельная форма
			bShowHint = false;
			ShowRPGHint();
		break;

		case "TABLE_OTHER":
			sHeader = XI_ConvertString(GameInterface.(CurTable).(CurRow).UserData.ID);
		    sText1  = GetConvertStr(GameInterface.(CurTable).(CurRow).UserData.ID, "ShipsDescribe.txt");
		    if (GameInterface.(CurTable).(CurRow).UserData.ID == "CannonType" && sti(rChr.Ship.Cannons.Type) != CANNON_TYPE_NONECANNON)
		    {
		    	ref Cannon = GetCannonByType(sti(rChr.Ship.Cannons.Type));
		    	sText2 = "Тип: " + XI_ConvertString(GetCannonType(sti(rChr.Ship.Cannons.Type)));
		    	sText2 = sText2 + NewStr() + "Калибр: " + XI_ConvertString("caliber" + GetCannonCaliber(sti(rChr.Ship.Cannons.Type)));
		    	sText2 = sText2 + NewStr() + "Дальность: "  + sti(Cannon.FireRange);
		    	sText2 = sText2 + NewStr() + "Урон: x"  + FloatToString(stf(Cannon.DamageMultiply), 1);
		    	sText2 = sText2 + NewStr() + "Перезарядка: "  + sti(GetCannonReloadTime(Cannon)) + " сек.";
		    	sText2 = sText2 + NewStr() + "Вес: "  + sti(Cannon.Weight) + " ц.";

		    	sGroup = "GOODS";
				sGroupPicture = GetCannonType(sti(rChr.Ship.Cannons.Type)) + "_" + GetCannonCaliber(sti(rChr.Ship.Cannons.Type));

				sText3 = "Двойной клик или Enter по этому полю вызывает просмотр экипировки орудий по бортам.";
		    }
		    if (GameInterface.(CurTable).(CurRow).UserData.ID == "Crew" && sti(rChr.ship.type) != SHIP_NOTUSED)
			{
				sText2 = "Команды может быть больше максимальной, но это вызывает перегруз и условия жизни на корабле становятся ужасными, что влечет ежедневное падение морали. В среднем можно взять на борт до 25% больше матросов.";
				sText2 = sText2 + NewStr() + "Максимальное количество экипажа с учетом перегруза: " + GetMaxCrewQuantity(rChr);
			}
			// процент ремонта
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Hull" && sti(rChr.ship.type) != SHIP_NOTUSED)
			{
				sText3 = xiStr("Hull") + ": " + FloatToString(GetHullPercent(rChr), 1)  + " %";
			}
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Sails" && sti(rChr.ship.type) != SHIP_NOTUSED)
			{
				sText3 = xiStr("Sails") + ": " + FloatToString(GetSailPercent(rChr), 1) + " %";
			}
			// трюм
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Capacity" && sti(rChr.ship.type) != SHIP_NOTUSED)
			{
				sText3 = "Занято: " + FloatToString((stf(GetCargoLoad(rChr))  /  stf(GetCargoMaxSpace(rChr))) * 100.0, 1)+ " %";
			}
		break;

		case "TABLE_SHIPYARD" :
		    sHeader = XI_Convertstring("Shipyard");
			sText1  = GetConvertStr("Shipyard_hint", "ShipsDescribe.txt");
		break;
		case "SHIPSUP_TABLE" :
		    sHeader = XI_Convertstring("SHIPS_UPGRADES");
			sText1  = GetConvertStr("SHIPSUP_TABLE_hint", "ShipsDescribe.txt");
		break;

		// LEO - чудим с доп инфой
		case "EXTRAHULLON":
			sHeader = XI_ConvertString("EXTRAHULLON");
			sText1 = GetConvertStr("SUP_HULL_descr", "ShipsDescribe.txt");

			sGroup = "SHIP_UPGRADES";
			if (CheckAttribute(RealShips[sti(rChr.Ship.Type)],"Tuning.HullSpecial")) sGroupPicture = "EXTRAHULLON";
			else sGroupPicture = "EXTRAHULLOFF";
			xx = 256;
			yy = 256;
		break;
		case "EXTRASAILON":
			sHeader = XI_ConvertString("EXTRASAILON");
			sText1 = GetConvertStr("SUP_SAIL_descr", "ShipsDescribe.txt");

			sGroup = "SHIP_UPGRADES";
			if (CheckAttribute(RealShips[sti(rChr.Ship.Type)],"Tuning.SailsSpecial")) sGroupPicture = "EXTRASAILON";
			else sGroupPicture = "EXTRASAILOFF";
			xx = 256;
			yy = 256;
		break;
		case "EXTRAGUNSON":
			sHeader = XI_ConvertString("EXTRAGUNSON");
			sText1 = GetConvertStr("SUP_CANNONS_descr", "ShipsDescribe.txt");

			sGroup = "SHIP_UPGRADES";
			if (CheckAttribute(RealShips[sti(rChr.Ship.Type)],"Tuning.CannonsSpecial")) sGroupPicture = "EXTRAGUNSON";
			else sGroupPicture = "EXTRAGUNSOFF";
			xx = 256;
			yy = 256;
		break;
		case "EXTRAHULLKRENGON":
			sHeader = XI_ConvertString("EXTRAHULLKRENGON");
			sText1 = GetConvertStr("SUP_HULLCOPPER_descr", "ShipsDescribe.txt");

			sGroup = "SHIP_UPGRADES";
			if (CheckAttribute(RealShips[sti(rChr.Ship.Type)],"Tuning.CuBot")) sGroupPicture = "EXTRAHULLKRENGON";
			else sGroupPicture = "EXTRAHULLKRENGOFF";
			xx = 256;
			yy = 256;
		break;
		case "EXTRACAPACITYON":
			sHeader = XI_ConvertString("EXTRACAPACITYON");
			sText1 = GetConvertStr("SUP_CAPACITY_descr", "ShipsDescribe.txt");

			sGroup = "SHIP_UPGRADES";
			if (CheckAttribute(RealShips[sti(rChr.Ship.Type)],"Tuning.BotPack")) sGroupPicture = "EXTRACAPACITYON";
			else sGroupPicture = "EXTRACAPACITYOFF";
			xx = 256;
			yy = 256;
		break;
		case "EXTRABIGSIDESON":
			sHeader = XI_ConvertString("EXTRABIGSIDESON");
			sText1 = GetConvertStr("SUP_BIGSIDES_descr", "ShipsDescribe.txt");

			sGroup = "SHIP_UPGRADES";
			if (CheckAttribute(RealShips[sti(rChr.Ship.Type)],"Tuning.HighBort")) sGroupPicture = "EXTRABIGSIDESON";
			else sGroupPicture = "EXTRABIGSIDESOFF";
			xx = 256;
			yy = 256;
		break;
	}
	if (bShowHint)
	{
		CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, xx, yy);
	}
}

void HideInfoWindow()
{
	CloseTooltip();
	ExitRPGHint();
}

void TableSelectChange()
{
	string sControl = GetEventData();
	iSelected = GetEventData();
    CurTable = sControl;
    CurRow   =  "tr" + (iSelected);
    NullSelectTable("TABLE_OTHER");
    // не тереть скрол на верфи

    // заполнялка
    if (CurTable == "TABLE_SHIPYARD")
	{
        FillShipyardShip(refNPCShipyard, GameInterface.(CurTable).(CurRow).sShipId);
		FillShipParam(refNPCShipyard);
		bShipyardOnTop = true;
		SetButtionsAccess();
	}
	if (CurTable == "SHIPSUP_TABLE")
	{
		int iShip = sti(xi_refCharacter.Ship.Type);
		int upsq = 0;
		switch(CurRow)
		{
			case "tr1":
				if (CheckAttribute(RealShips[iShip],"Tuning.HullSpecial")) upgradevalue = 0;
				else upgradevalue = makeint(sti(RealShips[iShip].price)/2);
				uptype = 1;
			break;
			case "tr2":
				if (CheckAttribute(RealShips[iShip],"Tuning.SailsSpecial")) upgradevalue = 0;
				else upgradevalue = makeint(sti(RealShips[iShip].price)*0.35);
				uptype = 2;
			break;
			case "tr3":
				if (CheckAttribute(RealShips[iShip],"Tuning.CannonsSpecial")) upgradevalue = 0;
				else upgradevalue = makeint(sti(RealShips[iShip].price)*0.25);
				uptype = 3;
			break;
			case "tr4":
				if (CheckAttribute(RealShips[iShip],"Tuning.CuBot")) upgradevalue = 0;
				else upgradevalue = makeint(sti(RealShips[iShip].price)*0.4);
				uptype = 4;
			break;
			case "tr5":
				if (CheckAttribute(RealShips[iShip],"Tuning.BotPack")) upgradevalue = 0;
				else upgradevalue = makeint(sti(RealShips[iShip].price)*0.5);
				uptype = 5;
			break;
			case "tr6":
				if (CheckAttribute(RealShips[iShip],"Tuning.HighBort")) upgradevalue = 0;
				else upgradevalue = makeint(sti(RealShips[iShip].price)*0.4);
				uptype = 6;
			break;
		}

		if (CheckAttribute(RealShips[iShip],"Tuning.HullSpecial")) upsq++;
		if (CheckAttribute(RealShips[iShip],"Tuning.SailsSpecial")) upsq++;
		if (CheckAttribute(RealShips[iShip],"Tuning.CannonsSpecial")) upsq++;
		if (CheckAttribute(RealShips[iShip],"Tuning.CuBot")) upsq++;
		if (CheckAttribute(RealShips[iShip],"Tuning.BotPack")) upsq++;
		if (CheckAttribute(RealShips[iShip],"Tuning.HighBort")) upsq++;

		switch (sti(RealShips[iShip].class))
		{
			case 7:
				timePreUpgrade = 2+drand(1);
			break;
			case 6:
				timePreUpgrade = 2+drand(2);
			break;
			case 5:
				timePreUpgrade = 3+drand(3);
			break;
			case 4:
				timePreUpgrade = 4+drand(4);
			break;
			case 3:
				timePreUpgrade = 4+drand(6);
			break;
			case 2:
				timePreUpgrade = 6+drand(6);
			break;
			case 1:
				timePreUpgrade = 10+drand(10);
			break;
		}
		if (upgradevalue == 0)
		{
			timePreUpgrade = makeint(timePreUpgrade/2);
			SetFormatedText("SHIPSUP_VALUE","Демонтаж займёт часов: не менее "+timePreUpgrade);
		}
		else SetFormatedText("SHIPSUP_VALUE",FindRussianMoneyString(upgradevalue)+", апгрейд займёт часов: не менее "+timePreUpgrade);

		SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"SHIPSUP_DOUP",0, "#"+"Улучшить");
		if (upgradevalue == 0) SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"SHIPSUP_DOUP",0, "#"+"Демонтаж");

		if (sti(pchar.money)>=upgradevalue && upsq < 3) SetSelectable("SHIPSUP_DOUP", true);
		if (sti(pchar.money)<upgradevalue) SetSelectable("SHIPSUP_DOUP", false);
		if (upsq >= 3 && upgradevalue > 0)
		{
			SetFormatedText("SHIPSUP_VALUE","Максимум апгрейдов");
			SetSelectable("SHIPSUP_DOUP", false);
		}
		if (upsq >= 3 && upgradevalue == 0)
		{
			SetFormatedText("SHIPSUP_VALUE","Максимум апгрейдов, часов для снятия: не менее "+timePreUpgrade);
			SetSelectable("SHIPSUP_DOUP", true);
			SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"SHIPSUP_DOUP",0, "#"+"Демонтаж");
		}
		switch(uptype)
		{
			case 1:
				if (RealShips[iShip].Type.War == true && RealShips[iShip].Type.Merchant == false)
				{
					if (sti(pchar.money)>=upgradevalue && upsq < 3) SetSelectable("SHIPSUP_DOUP", true);
				}
				else
				{
					SetFormatedText("SHIPSUP_VALUE","Апгрейд невозможен для данного корабля");
					SetSelectable("SHIPSUP_DOUP", false);
				}
			break;
			case 2:

			break;
			case 3:
				if (RealShips[iShip].Type.War == true && RealShips[iShip].Type.Merchant == false)
				{
					if (sti(pchar.money)>=upgradevalue && upsq < 3) SetSelectable("SHIPSUP_DOUP", true);
				}
				else
				{
					SetFormatedText("SHIPSUP_VALUE","Апгрейд невозможен для данного корабля");
					SetSelectable("SHIPSUP_DOUP", false);
				}
			break;
			case 4:

			break;
			case 5:
				if (RealShips[iShip].Type.War == false && RealShips[iShip].Type.Merchant == true)
				{
					if (sti(pchar.money)>=upgradevalue && upsq < 3) SetSelectable("SHIPSUP_DOUP", true);
				}
				else
				{
					SetFormatedText("SHIPSUP_VALUE","Апгрейд невозможен для данного корабля");
					SetSelectable("SHIPSUP_DOUP", false);
				}
			break;
			case 6:

			break;
		}
	}
}

void ExitRPGHint()
{
	if (sMessageMode == "RPG_Hint")
	{
		XI_WindowShow("RPG_WINDOW", false);
		XI_WindowDisable("RPG_WINDOW", true);
		XI_WindowDisable("MAIN_WINDOW", false);
		sMessageMode = "";
	}
}

void ShowRPGHint()
{
	SetSPECIALMiniTable("RPG_TABLE_SMALLSKILL", xi_refCharacter);
    SetOTHERMiniTable("RPG_TABLE_SMALLOTHER", xi_refCharacter);
    SetFormatedText("RPG_OFFICER_NAME", GetFullName(xi_refCharacter));

	XI_WindowShow("RPG_WINDOW", true);
	XI_WindowDisable("RPG_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);
	sMessageMode = "RPG_Hint";
}


void NullSelectTable(string sControl)
{
	if (sControl != CurTable)
	{
	    GameInterface.(sControl).select = 0;
	    Table_UpdateWindow(sControl);
	}
}

void ExitMsgMenu()
{
	XI_WindowShow("MSG_WINDOW", false);
	XI_WindowDisable("MSG_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("SHIPS_SCROLL");
	sMessageMode = "";
}

void ShowMsgMenu(bool change)
{
	XI_WindowShow("MSG_WINDOW", true);
	XI_WindowDisable("MSG_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	if (change) SetNodeUsing("MSG_CREW_CHECKBOX",false);
	else SetNodeUsing("MSG_CREW_CHECKBOX",true);

	SetCurrentNode("MSG_CANCEL");
}

void ShowOtherClick()
{
	if (CheckAttribute(GameInterface,CurTable+"."+CurRow+".UserData"))
	{
		if (GameInterface.(CurTable).(CurRow).UserData.ID == "CannonType")
		{
			ShowCannonsMenu();
		}
	}
}

void ShowCannonsMenu()
{
	XI_WindowShow("CANNONS_WINDOW", true);
	XI_WindowDisable("CANNONS_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetCurrentNode("CANNONS_CANCEL");

    DeleteAttribute(&GameInterface, "CANNONS_TABLE.BackUp")
    CannonsMenuRefresh();
}
void CannonsMenuRefresh()
{
	ref rChr;
	if (bShipyardOnTop)
	{
	    rChr = refNPCShipyard;
	}
	else
	{
		rChr = xi_refCharacter;
	}
	int idx = GetCannonGoodsIdxByType(sti(rChr.Ship.Cannons.Type));
	if (idx != -1)
	{
		int nShipType = GetCharacterShipType(rChr);
		ref refBaseShip = GetRealShip(nShipType);
	    SetNewGroupPicture("CANNONS_PIC", "GOODS", Goods[idx].Name);
		SetFormatedText("CANNONS_TEXT", XI_ConvertString(Goods[idx].Name));

		SetFormatedText("CANNONS_QTY_F", its(GetBortCannonsQty(rChr, "fcannon")) + "/" + refBaseShip.fcannon);
		SetFormatedText("CANNONS_QTY_B", its(GetBortCannonsQty(rChr, "bcannon")) + "/" + refBaseShip.bcannon);
		SetFormatedText("CANNONS_QTY_R", its(GetBortCannonsQty(rChr, "rcannon")) + "/" + refBaseShip.rcannon);
		SetFormatedText("CANNONS_QTY_L", its(GetBortCannonsQty(rChr, "lcannon")) + "/" + refBaseShip.lcannon);
		/// всего GetCannonsNum(xi_refCharacter)
	}
	else
	{
		SetNewGroupPicture("CANNONS_PIC", "GOODS", "");
		SetFormatedText("CANNONS_TEXT", "");
		SetFormatedText("CANNONS_QTY_F", "0");
		SetFormatedText("CANNONS_QTY_B", "0");
		SetFormatedText("CANNONS_QTY_R", "0");
		SetFormatedText("CANNONS_QTY_L", "0");
	}
}
void ExitCannonsMenu()
{
	HideCannonsMenu();
}

void HideCannonsMenu()
{
	XI_WindowShow("CANNONS_WINDOW", false);
	XI_WindowDisable("CANNONS_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("TABLE_OTHER");
	sMessageMode = "";
}

////////////// ценообразование

int GetBuyPrice(int iType)
{
	// boal учет скилов торговли 22.01.2004 -->
	float nCommerce   = GetSummonSkillFromNameToOld(GetMainCharacter(), SKILL_COMMERCE);

	if(CheckOfficersPerk(pchar,"Trader")) { nCommerce += 2; }
    if(CheckOfficersPerk(pchar,"AdvancedCommerce"))	{ nCommerce += 4; }
	else
	{
		if(CheckOfficersPerk(pchar,"BasicCommerce"))	{ nCommerce += 2; }
	}

    return makeint(GetShipPriceByType(iType) + GetShipPriceByType(iType)/(nCommerce*10));
    // boal 22.01.2004 <--
}

int GetSellPrice(ref _chr)
{
	int st = GetCharacterShipType(_chr);
	int price = GetShipPriceByType(st);
	price = makeint(price - 1.5*GetSailRepairCost(st, GetSailDamagePercent(_chr)));
	price = makeint(price - 1.5*GetHullRepairCost(st, GetHullDamagePercent(_chr)));

	float nCommerce   = GetSummonSkillFromNameToOld(GetMainCharacter(), SKILL_COMMERCE) + 0.001;

	if(CheckOfficersPerk(pchar,"Trader")) { nCommerce += 2; }
	if(CheckOfficersPerk(pchar,"AdvancedCommerce"))	{ nCommerce += 4; }
	else
	{
		if(CheckOfficersPerk(pchar,"BasicCommerce"))	{ nCommerce += 2; }
	}

	price = price - price / (nCommerce*10.5);

	ref rRealShip = GetRealShip(st);

	if (sti(rRealShip.Stolen) == true) //проверка на ворованный
	{
    	price = makeint(price/3);
    }
    if (price < 0 && sti(_chr.Ship.Type) != SHIP_NOTUSED)
	{
	   price = 0;
	}

	return price;
}

void FillShipyardTable()
{
    Table_Clear("TABLE_SHIPYARD", false, true, false);

	GameInterface.TABLE_SHIPYARD.hr.td1.str = "Корабль";
	GameInterface.TABLE_SHIPYARD.hr.td1.scale = 0.9;
	GameInterface.TABLE_SHIPYARD.hr.td2.str = "Специф.";
	GameInterface.TABLE_SHIPYARD.hr.td2.scale = 0.9;
	GameInterface.TABLE_SHIPYARD.hr.td3.str = "Класс";
	GameInterface.TABLE_SHIPYARD.hr.td3.scale = 0.9;
	GameInterface.TABLE_SHIPYARD.hr.td4.str = "Орудия";
	GameInterface.TABLE_SHIPYARD.hr.td4.scale = 0.9;
	GameInterface.TABLE_SHIPYARD.hr.td5.str = "Дедвейт";
	GameInterface.TABLE_SHIPYARD.hr.td5.scale = 0.9;
	GameInterface.TABLE_SHIPYARD.hr.td6.str = "Цена";
	GameInterface.TABLE_SHIPYARD.hr.td6.scale = 0.9;
	GameInterface.TABLE_SHIPYARD.select = 0;
	GameInterface.TABLE_SHIPYARD.top = 0;

	aref   arDest, arImt;
	string sAttr;
	int    iNum, i, iShip;
	ref    refBaseShip;
	string sShip;
	string row;
	int k = 0;

	makearef(arDest, refNPCShipyard.shipyard);
	iNum = GetAttributesNum(arDest);
	for (i = 0; i < iNum; i++)
	{
        row = "tr" + (k+1);

		arImt = GetAttributeN(arDest, i);
		//Log_Info(GetAttributeName(arImt));
		sAttr = GetAttributeName(arImt);
    	FillShipyardShip(refNPCShipyard, sAttr); // скинуть в стандарт корабль из ШипХХ

    	iShip = sti(refNPCShipyard.Ship.Type);
    	refBaseShip = GetRealShip(iShip);
		sShip = refBaseShip.BaseName;

		int nClass = sti(refBaseShip.Class);
		if (FIS_FilterState != FIS_ALL)
		{
			if (sti(FIS_FilterState) != nClass)
			{
				DeleteAttribute(&GameInterface,"TABLE_SHIPYARD.row");
				continue;
			}
		}

		k++;
		GameInterface.TABLE_SHIPYARD.(row).sShipId = sAttr;
        GameInterface.TABLE_SHIPYARD.(row).td1.icon.texture = "interfaces\\ships\\" + sShip + ".tga.tx";
		GameInterface.TABLE_SHIPYARD.(row).td1.icon.uv = "0,0,1,1";
		GameInterface.TABLE_SHIPYARD.(row).td1.icon.width = 46;
    	GameInterface.TABLE_SHIPYARD.(row).td1.icon.height = 46;
    	GameInterface.TABLE_SHIPYARD.(row).td1.icon.offset = "0, 1";
    	GameInterface.TABLE_SHIPYARD.(row).td1.textoffset = "53,0";
		GameInterface.TABLE_SHIPYARD.(row).td1.str = XI_Convertstring(sShip) + "\n"+refNPCShipyard.ship.name;
		GameInterface.TABLE_SHIPYARD.(row).td1.align = "left";
		GameInterface.TABLE_SHIPYARD.(row).td1.scale = 0.82;
		GameInterface.TABLE_SHIPYARD.(row).td2.str = GetShipsType(refBaseShip);
		GameInterface.TABLE_SHIPYARD.(row).td2.scale = 0.85;
		GameInterface.TABLE_SHIPYARD.(row).td2.align = "left";
		GameInterface.TABLE_SHIPYARD.(row).td3.str = refBaseShip.Class;
		GameInterface.TABLE_SHIPYARD.(row).td4.str = sti(refBaseShip.CannonsQuantity);
		GameInterface.TABLE_SHIPYARD.(row).td5.str = GetCargoMaxSpace(refNPCShipyard);
		GameInterface.TABLE_SHIPYARD.(row).td6.str = GetShipBuyPrice(iShip, refNPCShipyard);
		GameInterface.TABLE_SHIPYARD.(row).td6.color = argb(255,255,228,80);
    }

	Table_UpdateWindow("TABLE_SHIPYARD");
}

string GetShipsType(ref refBaseShip)
{
	string spectypes = "";
	if (refBaseShip.Type.War == true) spectypes = "Военный";
	if (refBaseShip.Type.Merchant == true) spectypes = "Торговый";
	if (refBaseShip.Type.Merchant == true && refBaseShip.Type.War == true) spectypes = "Универс.";
	return spectypes;
}

void ProcessFilter()
{
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CLASS_ALL", 3, 1))
	{
		FIS_FilterState = FIS_ALL;
		FillShipyardTable();
		return;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CLASS_ALL", 3, 2))
	{
		FIS_FilterState = FIS_7;
		FillShipyardTable();
		return;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CLASS_ALL", 3, 3))
	{
		FIS_FilterState = FIS_6;
		FillShipyardTable();
		return;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CLASS_ALL", 3, 4))
	{
		FIS_FilterState = FIS_5;
		FillShipyardTable();
		return;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CLASS_ALL", 3, 5))
	{
		FIS_FilterState = FIS_4;
		FillShipyardTable();
		return;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CLASS_ALL", 3, 6))
	{
		FIS_FilterState = FIS_3;
		FillShipyardTable();
		return;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CLASS_ALL", 3, 7))
	{
		FIS_FilterState = FIS_2;
		FillShipyardTable();
		return;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CLASS_ALL", 3, 8))
	{
		FIS_FilterState = FIS_1;
		FillShipyardTable();
		return;
	}
}

void SetButtionsAccess()
{
    SetSelectable("BUTTON_REPAIR", false);
    SetSelectable("BUTTON_SELL", true);
    SetSelectable("BUTTON_BUY", true);
	//#20180922-01
    SetSelectable("BUTTON_PAINT", true);
	SetSelectable("SHIPSUP_BUTTON", true);

    if (bShipyardOnTop)
    {
        SetSelectable("BUTTON_REPAIR", false);
    	SetSelectable("BUTTON_SELL", false);
    	//#20180922-01
    	SetSelectable("BUTTON_PAINT", false);
		SetSelectable("SHIPSUP_BUTTON", false);
    	if (shipIndex == -1)// проверка на цену
    	{
    	    if (GetShipBuyPrice(sti(refNPCShipyard.Ship.Type), refNPCShipyard) > sti(pchar.Money) )
    	    {
    	        SetSelectable("BUTTON_BUY", false);
    	    }
   			if (bEmptySlot && sti(pchar.ship.type) == SHIP_NOTUSED)
   			{ // нельзя купить корабль компаньону, если у ГГ нету
   			    SetSelectable("BUTTON_BUY", false);
   			}
    	}
    	else
    	{
    	    if (GetShipBuyPrice(sti(refNPCShipyard.Ship.Type), refNPCShipyard) > (GetShipSellPrice(xi_refCharacter, refNPCShipyard) + sti(pchar.Money)) )
    	    {
    	        SetSelectable("BUTTON_BUY", false);
    	    }
    	    if (!GetRemovable(xi_refCharacter) || !GetShipRemovable(xi_refCharacter))
    	    {
    	        SetSelectable("BUTTON_BUY", false);
    	    }
    	}
    }
    else
    {
        SetSelectable("BUTTON_BUY", false);

        if (GetHullPercent(xi_refCharacter) < 100 || GetSailPercent(xi_refCharacter) < 100 || sti(xi_refCharacter.ship.soiling) > 0)
        {
            SetSelectable("BUTTON_REPAIR", true);
        }
        if (shipIndex == -1)
        {
            SetSelectable("BUTTON_SELL", false);
            SetSelectable("BUTTON_REPAIR", false);
            //#20180922-01
            SetSelectable("BUTTON_PAINT", false);
			SetSelectable("SHIPSUP_BUTTON", false);
        }
        else
        {

            if (!GetRemovable(xi_refCharacter) || !GetShipRemovable(xi_refCharacter))
    	    {
    	        SetSelectable("BUTTON_SELL", false);
                //#20180922-01
                SetSelectable("BUTTON_PAINT", false);
				SetSelectable("SHIPSUP_BUTTON", false);
    	    }
    	    else {
                //#20180922-01
                SetSelectable("BUTTON_PAINT", true);
				SetSelectable("SHIPSUP_BUTTON", true);
    	    }
    	    if (xi_refCharacter.id == pchar.id && GetCompanionQuantity(pchar) > 1)
    	    { // нельзя продать корабль ГГ, если есть еще компаньоны
    	        SetSelectable("BUTTON_SELL", false);
    	    }
		}
    }
}

//////////////// назначение капитана  //////////////////////////////////////////////////////////////////////
void ShipChangeCaptan()
{
	FillPassengerScroll();
    SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"PASSENGERSLIST",-1);
    SetCurrentNode("PASSENGERSLIST");
	ProcessFrame();
	SetOfficersSkills();

	XI_WindowShow("OFFICERS_WINDOW", true);
	XI_WindowDisable("OFFICERS_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);
}

void ExitOfficerMenu()
{
	XI_WindowShow("OFFICERS_WINDOW", false);
	XI_WindowDisable("OFFICERS_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("SHIPS_SCROLL");
}

void AcceptAddOfficer()
{
	string  attributeName2 = "pic"+(nCurScrollOfficerNum+1);
    ref     sld;

    if (checkAttribute(GameInterface, "PASSENGERSLIST."+attributeName2 + ".character"))
    {
		int iChar = sti(GameInterface.PASSENGERSLIST.(attributeName2).character);
        // назначение нового кэпа, возможно, если там уже не наш, те или враг или снят
        sld = GetCharacter(iChar);

		if(sld.id != "pet_crab" && sld.id != "Albreht_Zalpfer" && !CheckAttribute(sld,"HPminusDaysNeedtoRestore"))
		{
			DeleteAttribute(sld, "ship");
			sld.ship.Type = SHIP_NOTUSED;

			// снимем пассажира -->
			CheckForReleaseOfficer(iChar);
			RemovePassenger(pchar, sld);
			// снимем пассажира <--
			SetCompanionIndex(pchar, -1, iChar);

			xi_refCharacter = sld;
			DoBuyShip();
		}
	}
	ExitOfficerMenu();
}

void SetOfficersSkills()
{
	string sCharacter = "pic"+(sti(GameInterface.PASSENGERSLIST.current)+1);
	if (checkAttribute(GameInterface, "PASSENGERSLIST."+sCharacter))
	{
		if (checkAttribute(GameInterface, "PASSENGERSLIST."+sCharacter + ".character"))
		{
			sCharacter = GameInterface.PASSENGERSLIST.(sCharacter).character;
			ref otherchr = &characters[sti(sCharacter)];
	        SetSPECIALMiniTable("TABLE_SMALLSKILL", otherchr);
	        SetOTHERMiniTable("TABLE_SMALLOTHER", otherchr);
	        SetFormatedText("OFFICER_NAME", GetFullName(otherchr));
	        SetSelectable("ACCEPT_ADD_OFFICER", true);
	        return;
        }
	}
    Table_Clear("TABLE_SMALLSKILL", false, true, true);
    Table_Clear("TABLE_SMALLOTHER", false, true, true);
    SetFormatedText("OFFICER_NAME", "");
    SetSelectable("ACCEPT_ADD_OFFICER", false);
}

void FillPassengerScroll()
{
	int i, howWork;
	string faceName;
	string attributeName;
	int _curCharIdx;
	ref _refCurChar;
	bool  ok;

	DeleteAttribute(&GameInterface, "PASSENGERSLIST");

	nCurScrollOfficerNum = -1;
	GameInterface.PASSENGERSLIST.current = 0;

	int nListSize = GetPassengersQuantity(pchar);
	int nListSizeFree = nListSize;

	GameInterface.PASSENGERSLIST.NotUsed = 6;
	GameInterface.PASSENGERSLIST.ListSize = nListSizeFree + 2;

	GameInterface.PASSENGERSLIST.ImagesGroup.t0 = "EMPTYFACE";

	FillFaceList("PASSENGERSLIST.ImagesGroup", pchar, 2); // passengers

	GameInterface.PASSENGERSLIST.BadTex1 = 0;
	GameInterface.PASSENGERSLIST.BadPic1 = "emptyface";
	int m = 0;
	for(i=0; i<nListSize; i++)
	{
		attributeName = "pic" + (m+1);
		_curCharIdx = GetPassenger(pchar,i);

		if (_curCharIdx!=-1)
		{
			ok = CheckAttribute(&characters[_curCharIdx], "prisoned") && sti(characters[_curCharIdx].prisoned) == true;
			if (!ok && GetRemovable(&characters[_curCharIdx]))
			{
				GameInterface.PASSENGERSLIST.(attributeName).character = _curCharIdx;
				GameInterface.PASSENGERSLIST.(attributeName).img1 = GetFacePicName(GetCharacter(_curCharIdx));
				GameInterface.PASSENGERSLIST.(attributeName).tex1 = FindFaceGroupNum("PASSENGERSLIST.ImagesGroup", "FACE128_"+Characters[_curCharIdx].FaceID);
				m++;
			}
		}
	}
	GameInterface.PASSENGERSLIST.ListSize = m + 2; // не знаю зачем, но для совместимости с 'было'
}
// рефреш скилов офа и ГГ, если офа сняли для компаньона
void DelBakSkill()
{
	DelBakSkillAttr(xi_refCharacter);
    ClearCharacterExpRate(xi_refCharacter);
    RefreshCharacterSkillExpRate(xi_refCharacter);
    SetEnergyToCharacter(xi_refCharacter);

    DelBakSkillAttr(pchar);
    ClearCharacterExpRate(pchar);
    RefreshCharacterSkillExpRate(pchar);
    SetEnergyToCharacter(pchar);
}

void ShowMessageInfo()
{
	bool   bBuy;
	int    iMoney;
	string add = "";

	if (bShipyardOnTop) // на стороне верфи (купить)
    {
        bBuy = true;
		if (shipIndex == -1)// проверка на цену
    	{
    	    iMoney = GetShipBuyPrice(sti(refNPCShipyard.Ship.Type), refNPCShipyard);
    	}
    	else
    	{
            iMoney = GetShipBuyPrice(sti(refNPCShipyard.Ship.Type), refNPCShipyard) - GetShipSellPrice(xi_refCharacter, refNPCShipyard);
    	}
    }
    else  // продать
    {
        bBuy = false;
        iMoney = GetShipSellPrice(xi_refCharacter, refNPCShipyard);
    }
	SetFormatedText("MSG_WINDOW_CAPTION", XI_ConvertString("Ship"));

	if (bBuy)
	{
		if (iMoney < 0) add = "-";
		SetFormatedText("MSG_WINDOW_TEXT", "");
		SetFormatedText("MSG_WINDOW_TEXT2", "");
		SetFormatedText("MSG_WINDOW_TEXT3", "Купить корабль за " + add + FindRussianMoneyString(abs(iMoney)) + "?");
		SetSelectable("MSG_OK", true);
		sMessageMode = "ShipBuy";
	}
	else
	{
	    SetFormatedText("MSG_WINDOW_TEXT", "Продать корабль за " + add + FindRussianMoneyString(abs(iMoney)) + "?");
		SetFormatedText("MSG_WINDOW_TEXT2", "Как поступить с оставшейся на корабле командой?");
		SetFormatedText("MSG_WINDOW_TEXT3", "");
		SetSelectable("MSG_OK", true);
		sMessageMode = "ShipSell";
	}
	ShowMsgMenu(bBuy);
}

//#20180922-01
void ShowMessageInfo2()
{
    ref rShip;
	bool bShipOK = false;
	float iMoney = 0.0;
	string sText;
    int nClass, nMinClass = 1;

	if(bShipyardOnTop) return;

    int iShip = sti(xi_refCharacter.ship.type);
	SetFormatedText("MSG_WINDOW_CAPTION", "Покраска");
    SetSelectable("MSG_OK", false);
    //Check ship and add msg can/can't do based on class, size, hull avail, etc.  If not, disable MSG_OK
    if (shipIndex != -1 && iShip != SHIP_NOTUSED)
    {
        rShip = GetRealShip(iShip);
        nClass = sti(rShip.Class);
        bShipOK = true;
		iMoney = rShip.price;
		iMoney /= 25;
    }
    if(bShipOK)
    {
        if(iMoney > sti(pchar.money)) {
            sText = "У вас недостаточно средств.";
        }
        else {
			sText = "Я использую свой опыт и наилучшие суждения, чтобы наложить новую покраску на ваш корабль. Это обойдётся вам в " + makeint(iMoney) + " пиастров. Согласны?";
            SetSelectable("MSG_OK", true);

        }
    }
    else {
        sText = "К сожалению, не могу предоставить вам данную услугу сейчас. Приношу свои искренние извинения.";
    }
    SetFormatedText("MSG_WINDOW_TEXT", sText);
    sMessageMode = "ShipPaint";
	//ShowMsgMenu();
}

void MessageOk()
{
	switch (sMessageMode)
	{
	    case "ShipSell" :
	        DoSellShip(true);
	        ExitMsgMenu();
	    break;

	    case "ShipBuy" :
	        DoBuyShipMain();
	    break;
		//#20180922-01
	    case "ShipPaint" :
	        DoPaintShipMain();
	    break;
	}
}

void DoSellShip(bool _refresh)
{
	ref chref = xi_refCharacter;
	if (shipIndex != -1 && sti(chref.ship.type) != SHIP_NOTUSED)
	{
    	int sellPrice = GetShipSellPrice(chref, refNPCShipyard);

    	AddMoneyToCharacter(pchar, sellPrice);
        AddCharacterExpToSkill(pchar, "Commerce", sellPrice / 1600.0);
        WaitDate("",0,0,0, 0, 10);
        Statistic_AddValue(pchar, "SellShip", 1);

    	DeleteAttribute(chref,"ship.sails");
    	DeleteAttribute(chref,"ship.blots");
        DeleteAttribute(chref,"ship.masts");

        // в списке на покупку. -->
        AddShip2Shipyard(chref);
        // в списке на покупку. <--
    	chref.ship.type = SHIP_NOTUSED;
    	// снять кэпа -->
    	if (_refresh)
		{
	    	if (sti(chref.index) != GetMainCharacterIndex())
	    	{
				if (SellState == "Max") SendCrewToPchar(chref);
				if (SellState == "Opt") SendOptCrewToPchar(chref);
				if (SellState == "Fire") FireCrew(chref);
	            RemoveCharacterCompanion(pchar, chref);
				AddPassenger(pchar, chref, false);
				DelBakSkill();
				//navy --> Фигвам, а не халява :)
				if (CheckAttribute(chref, "PGGAi") && CheckAttribute(chref, "PGGAi.OwnShip")) //за корабли данные ГГ, деньги ГГ.
				{
					chref.Payment = true;
					DeleteAttribute(chref, "PGGAi.OwnShip")
					Log_Info("Деньги за свой корабль забрал компаньон.");
					AddMoneyToCharacter(pchar, -(sellPrice));
				}
				//navy <--
	    	}
	    	else
	    	{
          		pchar.location.from_sea = ""; // нет корабля в порту
	    	}
    		RefreshShipLists();
    	}
	}
}

void SendCrewToPchar(ref chref)
{
	int i, cn;
	ref chreff;
	if (GetCrewQuantity(pchar) < GetMaxCrewQuantity(pchar))
	{
		int crewn = GetMaxCrewQuantity(pchar) - GetCrewQuantity(pchar);
		float fTemp =  stf(GetCrewQuantity(pchar) + crewn);
		float fTemp2 =  stf(GetCrewQuantity(pchar) + GetCrewQuantity(chref));

		if (GetCrewQuantity(chref)>crewn)
		{
			pchar.Ship.Crew.Exp.Sailors   = (stf(pchar.Ship.Crew.Exp.Sailors)*GetCrewQuantity(pchar) +
												stf(chref.Ship.Crew.Exp.Sailors)*crewn) / fTemp;
			pchar.Ship.Crew.Exp.Cannoners   = (stf(pchar.Ship.Crew.Exp.Cannoners)*GetCrewQuantity(pchar) +
													stf(chref.Ship.Crew.Exp.Cannoners)*crewn) / fTemp;
			pchar.Ship.Crew.Exp.Soldiers   = (stf(pchar.Ship.Crew.Exp.Soldiers)*GetCrewQuantity(pchar) +
														stf(chref.Ship.Crew.Exp.Soldiers)*crewn) / fTemp;
			pchar.Ship.Crew.morale   = (stf(pchar.Ship.Crew.morale)*GetCrewQuantity(pchar) +
														stf(chref.Ship.Crew.morale)*crewn) / fTemp;

			SetCrewQuantity(pchar,GetMaxCrewQuantity(pchar));
			Log_Info("Часть команды с проданного корабля перешла на ваш корабль.");
			crewn = GetCrewQuantity(chref)-crewn;
			if (crewn > 0)
			{
				for(i=1; i<COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					if(cn > 0 && crewn > 0)
					{
						chreff = GetCharacter(cn);
						if (crewn != 0) crewn = SendCrewToShip(chref, chreff, crewn);
					}
				}
				if (crewn > 0) SendCrewToTavern(chref, crewn);

			}
		}
		else
		{
			pchar.Ship.Crew.Exp.Sailors   = (stf(pchar.Ship.Crew.Exp.Sailors)*GetCrewQuantity(pchar) +
												stf(chref.Ship.Crew.Exp.Sailors)*GetCrewQuantity(chref)) / fTemp2;
			pchar.Ship.Crew.Exp.Cannoners   = (stf(pchar.Ship.Crew.Exp.Cannoners)*GetCrewQuantity(pchar) +
													stf(chref.Ship.Crew.Exp.Cannoners)*GetCrewQuantity(chref)) / fTemp2;
			pchar.Ship.Crew.Exp.Soldiers   = (stf(pchar.Ship.Crew.Exp.Soldiers)*GetCrewQuantity(pchar) +
														stf(chref.Ship.Crew.Exp.Soldiers)*GetCrewQuantity(chref)) / fTemp2;

			pchar.Ship.Crew.morale   = (stf(pchar.Ship.Crew.morale)*GetCrewQuantity(pchar) +
														stf(chref.Ship.Crew.morale)*GetCrewQuantity(chref)) / fTemp2;
			SetCrewQuantity(pchar,GetCrewQuantity(pchar)+GetCrewQuantity(chref));
			Log_Info("Команда с проданного корабля перешла на ваш корабль.");
		}
	}
	else
	{
		int creww = GetCrewQuantity(chref);
		for(i=1; i<COMPANION_MAX; i++)
		{
			cn = GetCompanionIndex(PChar, i);
			if(cn > 0 && creww > 0)
			{
				chreff = GetCharacter(cn);
				creww = SendCrewToShip(chref, chreff, creww);
			}
		}
		if (creww > 0) SendCrewToTavern(chref, creww);
	}
}

int SendCrewToShip(ref chref, ref chreff, int crewnum)
{
	int crewn = GetMaxCrewQuantity(chreff) - GetCrewQuantity(chreff);
	if (crewn == 0) return crewnum;
	float fTemp =  stf(GetCrewQuantity(chreff) + crewn);
	float fTemp2 =  stf(GetCrewQuantity(chreff) + crewnum);

	if (crewnum>crewn)
	{
		chreff.Ship.Crew.Exp.Sailors   = (stf(chreff.Ship.Crew.Exp.Sailors)*GetCrewQuantity(chreff) +
											stf(chref.Ship.Crew.Exp.Sailors)*crewn) / fTemp;
		chreff.Ship.Crew.Exp.Cannoners   = (stf(chreff.Ship.Crew.Exp.Cannoners)*GetCrewQuantity(chreff) +
												stf(chref.Ship.Crew.Exp.Cannoners)*crewn) / fTemp;
		chreff.Ship.Crew.Exp.Soldiers   = (stf(chreff.Ship.Crew.Exp.Soldiers)*GetCrewQuantity(chreff) +
													stf(chref.Ship.Crew.Exp.Soldiers)*crewn) / fTemp;
		chreff.Ship.Crew.morale   = (stf(chreff.Ship.Crew.morale)*GetCrewQuantity(chreff) +
													stf(chref.Ship.Crew.morale)*crewn) / fTemp;

		SetCrewQuantity(chreff,GetMaxCrewQuantity(chreff));
		Log_Info("Часть команды с проданного корабля перешла на корабль компаньона "+chreff.name+" "+chreff.lastname+".");
		crewn = crewnum-crewn;
	}
	else
	{
		chreff.Ship.Crew.Exp.Sailors   = (stf(chreff.Ship.Crew.Exp.Sailors)*GetCrewQuantity(chreff) +
											stf(chref.Ship.Crew.Exp.Sailors)*crewnum) / fTemp2;
		chreff.Ship.Crew.Exp.Cannoners   = (stf(chreff.Ship.Crew.Exp.Cannoners)*GetCrewQuantity(chreff) +
												stf(chref.Ship.Crew.Exp.Cannoners)*crewnum) / fTemp2;
		chreff.Ship.Crew.Exp.Soldiers   = (stf(chreff.Ship.Crew.Exp.Soldiers)*GetCrewQuantity(chreff) +
													stf(chref.Ship.Crew.Exp.Soldiers)*crewnum) / fTemp2;

		chreff.Ship.Crew.morale   = (stf(chreff.Ship.Crew.morale)*GetCrewQuantity(chreff) +
													stf(chref.Ship.Crew.morale)*crewnum) / fTemp2;
		SetCrewQuantity(chreff,GetCrewQuantity(chreff)+crewnum);
		Log_Info("Команда с проданного корабля перешла на корабль компаньона "+chreff.name+" "+chreff.lastname+".");
		crewn = 0;
	}
	return crewn;
}

void SendCrewToTavern(ref chref, int crewn)
{
	ref refTown = GetColonyByIndex(FindColony(loadedLocation.fastreload));
	float fTemp3 =  stf(GetCrewQuantity(refTown) + crewn);
	refTown.Ship.Crew.Exp.Sailors   = (stf(refTown.Ship.Crew.Exp.Sailors)*GetCrewQuantity(refTown) +
											stf(chref.Ship.Crew.Exp.Sailors)*crewn) / fTemp3;
	refTown.Ship.Crew.Exp.Cannoners   = (stf(refTown.Ship.Crew.Exp.Cannoners)*GetCrewQuantity(refTown) +
											stf(chref.Ship.Crew.Exp.Cannoners)*crewn) / fTemp3;
	refTown.Ship.Crew.Exp.Soldiers   = (stf(refTown.Ship.Crew.Exp.Soldiers)*GetCrewQuantity(refTown) +
											stf(chref.Ship.Crew.Exp.Soldiers)*crewn) / fTemp3;
	refTown.Ship.Crew.Morale   = (stf(refTown.Ship.Crew.Morale)*GetCrewQuantity(refTown) +
											stf(chref.Ship.Crew.Morale)*crewn) / fTemp3;
	refTown.Ship.Crew.Quantity = sti(refTown.Ship.Crew.Quantity) + crewn;
	Log_Info("Оставшаяся команда с проданного корабля отправилась в увольнение.")
}

void SendOptCrewToPchar(ref chref)
{
	int i, cn;
	ref chreff;
	if (GetCrewQuantity(pchar) < GetOptCrewQuantity(pchar))
	{
		int crewn = GetOptCrewQuantity(pchar) - GetCrewQuantity(pchar);
		float fTemp =  stf(GetCrewQuantity(pchar) + crewn);
		float fTemp2 =  stf(GetCrewQuantity(pchar) + GetCrewQuantity(chref));

		if (GetCrewQuantity(chref)>crewn)
		{
			pchar.Ship.Crew.Exp.Sailors   = (stf(pchar.Ship.Crew.Exp.Sailors)*GetCrewQuantity(pchar) +
												stf(chref.Ship.Crew.Exp.Sailors)*crewn) / fTemp;
			pchar.Ship.Crew.Exp.Cannoners   = (stf(pchar.Ship.Crew.Exp.Cannoners)*GetCrewQuantity(pchar) +
													stf(chref.Ship.Crew.Exp.Cannoners)*crewn) / fTemp;
			pchar.Ship.Crew.Exp.Soldiers   = (stf(pchar.Ship.Crew.Exp.Soldiers)*GetCrewQuantity(pchar) +
														stf(chref.Ship.Crew.Exp.Soldiers)*crewn) / fTemp;
			pchar.Ship.Crew.morale   = (stf(pchar.Ship.Crew.morale)*GetCrewQuantity(pchar) +
														stf(chref.Ship.Crew.morale)*crewn) / fTemp;

			SetCrewQuantity(pchar,GetOptCrewQuantity(pchar));
			Log_Info("Часть команды с проданного корабля перешла на ваш корабль.");
			crewn = GetCrewQuantity(chref)-crewn;
			if (crewn > 0)
			{
				for(i=1; i<COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					if(cn > 0 && crewn > 0)
					{
						chreff = GetCharacter(cn);
						if (crewn != 0) crewn = SendOptCrewToShip(chref, chreff, crewn);
					}
				}
				if (crewn > 0) SendCrewToTavern(chref, crewn);

			}
		}
		else
		{
			pchar.Ship.Crew.Exp.Sailors   = (stf(pchar.Ship.Crew.Exp.Sailors)*GetCrewQuantity(pchar) +
												stf(chref.Ship.Crew.Exp.Sailors)*GetCrewQuantity(chref)) / fTemp2;
			pchar.Ship.Crew.Exp.Cannoners   = (stf(pchar.Ship.Crew.Exp.Cannoners)*GetCrewQuantity(pchar) +
													stf(chref.Ship.Crew.Exp.Cannoners)*GetCrewQuantity(chref)) / fTemp2;
			pchar.Ship.Crew.Exp.Soldiers   = (stf(pchar.Ship.Crew.Exp.Soldiers)*GetCrewQuantity(pchar) +
														stf(chref.Ship.Crew.Exp.Soldiers)*GetCrewQuantity(chref)) / fTemp2;

			pchar.Ship.Crew.morale   = (stf(pchar.Ship.Crew.morale)*GetCrewQuantity(pchar) +
														stf(chref.Ship.Crew.morale)*GetCrewQuantity(chref)) / fTemp2;
			SetCrewQuantity(pchar,GetCrewQuantity(pchar)+GetCrewQuantity(chref));
			Log_Info("Команда с проданного корабля перешла на ваш корабль.");
		}
	}
	else
	{
		int creww = GetCrewQuantity(chref);
		for(i=1; i<COMPANION_MAX; i++)
		{
			cn = GetCompanionIndex(PChar, i);
			if(cn > 0 && creww > 0)
			{
				chreff = GetCharacter(cn);
				creww = SendOptCrewToShip(chref, chreff, creww);
			}
		}
		if (creww > 0) SendCrewToTavern(chref, creww);
	}
}

int SendOptCrewToShip(ref chref, ref chreff, int crewnum)
{
	if (GetCrewQuantity(chreff) >= GetOptCrewQuantity(chreff)) return crewnum;
	int crewn = GetOptCrewQuantity(chreff) - GetCrewQuantity(chreff);
	if (crewn == 0) return crewnum;
	float fTemp =  stf(GetCrewQuantity(chreff) + crewn);
	float fTemp2 =  stf(GetCrewQuantity(chreff) + crewnum);

	if (crewnum>crewn)
	{
		chreff.Ship.Crew.Exp.Sailors   = (stf(chreff.Ship.Crew.Exp.Sailors)*GetCrewQuantity(chreff) +
											stf(chref.Ship.Crew.Exp.Sailors)*crewn) / fTemp;
		chreff.Ship.Crew.Exp.Cannoners   = (stf(chreff.Ship.Crew.Exp.Cannoners)*GetCrewQuantity(chreff) +
												stf(chref.Ship.Crew.Exp.Cannoners)*crewn) / fTemp;
		chreff.Ship.Crew.Exp.Soldiers   = (stf(chreff.Ship.Crew.Exp.Soldiers)*GetCrewQuantity(chreff) +
													stf(chref.Ship.Crew.Exp.Soldiers)*crewn) / fTemp;
		chreff.Ship.Crew.morale   = (stf(chreff.Ship.Crew.morale)*GetCrewQuantity(chreff) +
													stf(chref.Ship.Crew.morale)*crewn) / fTemp;

		SetCrewQuantity(chreff,GetOptCrewQuantity(chreff));
		Log_Info("Часть команды с проданного корабля перешла на корабль компаньона "+chreff.name+" "+chreff.lastname+".");
		crewn = crewnum-crewn;
	}
	else
	{
		chreff.Ship.Crew.Exp.Sailors   = (stf(chreff.Ship.Crew.Exp.Sailors)*GetCrewQuantity(chreff) +
											stf(chref.Ship.Crew.Exp.Sailors)*crewnum) / fTemp2;
		chreff.Ship.Crew.Exp.Cannoners   = (stf(chreff.Ship.Crew.Exp.Cannoners)*GetCrewQuantity(chreff) +
												stf(chref.Ship.Crew.Exp.Cannoners)*crewnum) / fTemp2;
		chreff.Ship.Crew.Exp.Soldiers   = (stf(chreff.Ship.Crew.Exp.Soldiers)*GetCrewQuantity(chreff) +
													stf(chref.Ship.Crew.Exp.Soldiers)*crewnum) / fTemp2;

		chreff.Ship.Crew.morale   = (stf(chreff.Ship.Crew.morale)*GetCrewQuantity(chreff) +
													stf(chref.Ship.Crew.morale)*crewnum) / fTemp2;
		SetCrewQuantity(chreff,GetCrewQuantity(chreff)+crewnum);
		Log_Info("Команда с проданного корабля перешла на корабль компаньона "+chreff.name+" "+chreff.lastname+".");
		crewn = 0;
	}
	return crewn;
}

void FireCrew(ref chref)
{
	int crewn = GetCrewQuantity(chref);
	ref refTown = GetColonyByIndex(FindColony(loadedLocation.fastreload));
	float fTemp3 =  stf(GetCrewQuantity(refTown) + crewn);
	refTown.Ship.Crew.Exp.Sailors   = (stf(refTown.Ship.Crew.Exp.Sailors)*GetCrewQuantity(refTown) +
											stf(chref.Ship.Crew.Exp.Sailors)*crewn) / fTemp3;
	refTown.Ship.Crew.Exp.Cannoners   = (stf(refTown.Ship.Crew.Exp.Cannoners)*GetCrewQuantity(refTown) +
											stf(chref.Ship.Crew.Exp.Cannoners)*crewn) / fTemp3;
	refTown.Ship.Crew.Exp.Soldiers   = (stf(refTown.Ship.Crew.Exp.Soldiers)*GetCrewQuantity(refTown) +
											stf(chref.Ship.Crew.Exp.Soldiers)*crewn) / fTemp3;
	refTown.Ship.Crew.Morale   = (stf(refTown.Ship.Crew.Morale)*GetCrewQuantity(refTown) +
											stf(chref.Ship.Crew.Morale)*crewn) / fTemp3;
	refTown.Ship.Crew.Quantity = sti(refTown.Ship.Crew.Quantity) + crewn;
	Log_Info("Оставшаяся команда с проданного корабля отправилась в увольнение.")
}

void RefreshShipLists()
{
    xi_refCharacter = pchar;
	FillShipsScroll();
   	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"SHIPS_SCROLL",-1);
    SetCurrentNode("SHIPS_SCROLL");
	ProcessFrame();

	FillShipyardTable();
	bShipyardOnTop = false;
}

void AddShip2Shipyard(ref _chr)
{
    aref    arTo, arFrom;

	aref   arDest, arImt;
	string sAttr;
	int    iNum, i, iShip;
	ref    refBaseShip;
	string sShip;
	string row;

    iShip = sti(_chr.ship.type);
    RealShips[iShip].StoreShip = true;  // кораль на верфи, трется отдельным методом
    RealShips[iShip].Stolen = 0; // уже не ворованный
	makearef(arDest, refNPCShipyard.shipyard);
	iNum = GetAttributesNum(arDest);
	if (iNum == 0)
	{
	    sAttr = "ship1";
	}
	else
	{
	    arImt = GetAttributeN(arDest, iNum - 1);
	    sAttr = GetAttributeName(arImt) + "2";
	}
	makearef(arTo,   refNPCShipyard.ship);
	makearef(arFrom, _chr.Ship);
	CopyAttributes(arTo, arFrom);
	// нулим экипаж и трюм
	SetCrewQuantity(refNPCShipyard, 0);
	DeleteAttribute(refNPCShipyard, "Ship.Cargo");  //пустой трюм
	SetGoodsInitNull(refNPCShipyard);
    RecalculateCargoLoad(refNPCShipyard);

	FillShipyardShipBack(refNPCShipyard, sAttr);
	// бакапим атрибуты груза и матросов
	DeleteAttribute(refNPCShipyard, "BakCargo");
 	DeleteAttribute(refNPCShipyard, "BakCrew");
 	refNPCShipyard.BakCargo = "";
	makearef(arTo,   refNPCShipyard.BakCargo);
	makearef(arFrom, _chr.Ship.Cargo);
	CopyAttributes(arTo, arFrom);

	refNPCShipyard.BakCrew = "";
	makearef(arTo,   refNPCShipyard.BakCrew);
	makearef(arFrom, _chr.Ship.Crew);
	CopyAttributes(arTo, arFrom);
}

void DoBuyShip()
{
    aref    arTo, arFrom;
	int     iBuyMoney = GetShipBuyPrice(sti(refNPCShipyard.Ship.Type), refNPCShipyard);

 	DeleteAttribute(refNPCShipyard, "BakCargo");
 	DeleteAttribute(refNPCShipyard, "BakCrew");
	DoSellShip(false);
	AddMoneyToCharacter(pchar, -iBuyMoney);

    AddCharacterExpToSkill(pchar, "Commerce", iBuyMoney / 700.0);
    WaitDate("",0,0,0, 0, 10);
    Statistic_AddValue(pchar, "BuyShip", 1);

    FillShipyardShip(refNPCShipyard, sShipId); // то, что покупаем

    makearef(arTo,   xi_refCharacter.ship);
	makearef(arFrom, refNPCShipyard.Ship);
	CopyAttributes(arTo, arFrom);

	DeleteAttribute(refNPCShipyard, "shipyard." + sShipId);

    int iShip = sti(xi_refCharacter.ship.type);
    DeleteAttribute(&RealShips[iShip], "StoreShip"); // можно тереть

	if (CheckAttribute(refNPCShipyard, "BakCargo")) // есть бакап корабля
	{
        DeleteAttribute(xi_refCharacter, "Ship.Cargo");
		DeleteAttribute(xi_refCharacter, "Ship.Crew");

		xi_refCharacter.Ship.Cargo = "";
		makearef(arTo,   xi_refCharacter.Ship.Cargo);
		makearef(arFrom, refNPCShipyard.BakCargo);
		CopyAttributes(arTo, arFrom);

        xi_refCharacter.Ship.Crew = "";
		makearef(arTo,   xi_refCharacter.Ship.Crew);
		makearef(arFrom, refNPCShipyard.BakCrew);
		CopyAttributes(arTo, arFrom);

		AddCharacterCrew(xi_refCharacter, 0); // обрезать перегруз
	    RecalculateCargoLoad(xi_refCharacter);
	}
	if(!CheckAttribute(xi_refCharacter, "Ship.soiling"))
	{
		xi_refCharacter.Ship.soiling = 0;
	}
	if (sti(xi_refCharacter.index) == GetMainCharacterIndex())
	{
  		pchar.location.from_sea = sFrom_sea; // корабль в порту
	}
	DelBakSkill();
	RefreshShipLists();
}

void DoBuyShipMain()
{
	if (CheckAttribute(&GameInterface, CurTable + "." + CurRow + ".sShipId"))
	{
	    sShipId = GameInterface.(CurTable).(CurRow).sShipId;

		if (!bEmptySlot) // был коарбль или ГГ без корабля
		{
		    DoBuyShip();
		    ExitMsgMenu();
		}
		else
		{
		    ExitMsgMenu();
		    ShipChangeCaptan();
		}
	}
}

void DoPaintShip()
{
    ref rRealShip;
    int nHulls = 3;
    int nCurrHull = 1;
    int nRandHull;
    int iShip = sti(xi_refCharacter.ship.type);

    timePaint = 0;
	if (iShip != SHIP_NOTUSED)
	{
	    rRealShip = GetRealShip(iShip);
		int iBuyMoney = rRealShip.price;
		iBuyMoney /= 25;
	    if(CheckAttribute(rRealShip, "BaseType")) {
           if(CheckAttribute(&ShipsTypes[sti(rRealShip.BaseType)], "hullNums"))
             nHulls = ShipsTypes[sti(rRealShip.BaseType)].hullNums;
        }
        if(nHulls < 2)
            return;
	    timePaint = timePaint + (8-GetCharacterShipClass(xi_refCharacter));
	    AddMoneyToCharacter(pchar, makeint(-iBuyMoney));
	    AddCharacterExpToSkill(pchar, "Commerce", iBuyMoney / 700.0);
        if(CheckAttribute(rRealShip, "ship.upgrades.hull"))
            nCurrHull = sti(rRealShip.ship.upgrades.hull);
        nRandHull = nCurrHull;
        while(nCurrHull == nRandHull) {
            nRandHull = rand(nHulls-1) + 1;
        }
        rRealShip.ship.upgrades.hull = nRandHull;
	}
}

void DoPaintShipMain()
{
	if (shipIndex != -1 && sti(xi_refCharacter.ship.type) != SHIP_NOTUSED)
	{
		DoPaintShip();
	}
	ExitMsgMenu();
}

int ScrollGetTexture()
{
	string sName = GetEventData();
	int iPicIndex = GetEventData();
	string sScrollID = GetEventData();

	//Boyer change #20170301-2 to new function as NFGetFile (NF) functions no longer exist in our source
	int iTexture = GetTexture(sName); //NFGetTexture(sScrollID, sName);

	return iTexture;
}

//////////////////// ремонт ///////////////
void ExitRepairMenu()
{
	XI_WindowShow("REPAIR_WINDOW", false);
	XI_WindowDisable("REPAIR_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("SHIPS_SCROLL");
	sMessageMode = "";
}

void ShowRepairMenu()
{
	XI_WindowShow("REPAIR_WINDOW", true);
	XI_WindowDisable("REPAIR_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

    SetRepairData();
	SetCurrentNode("REPAIR_CANCEL");
}

void SetRepairData()
{
	RepairSail = 0;
	RepairHull = 0;
 	RepairStatShow();
}

void RepairMoneyShow()
{
    int st = GetCharacterShipType(xi_refCharacter);
	int soiltime = 0;
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "REPAIR_Soiling_CHECKBOX", 3, 1)) soiltime = (8-GetCharacterShipClass(xi_refCharacter));
	else soiltime = 0;
	int iTimeM = makeint((soiltime + (RepairHull * (8-GetCharacterShipClass(xi_refCharacter)))/4.0 + (RepairSail * (8-GetCharacterShipClass(xi_refCharacter)))/6.0) * 60.0);
	string _sTime;
	if (iTimeM<1) _sTime = "\n"; else _sTime = "часов: " + iTimeM/60 + " | минут: " + its(iTimeM-(iTimeM/60)*60) + "\n";
	int repwt = its(iSoilClearCost + GetSailRepairCost(st, RepairSail, refNPCShipyard) + GetHullRepairCost(st, RepairHull, refNPCShipyard));
	SetFormatedText("REPAIR_WINDOW_TEXT", _sTime + its(iSoilClearCost + GetSailRepairCost(st, RepairSail, refNPCShipyard) + GetHullRepairCost(st, RepairHull, refNPCShipyard)));
	if (repwt > 0) SetSelectable("REPAIR_OK", true);
	else SetSelectable("REPAIR_OK", false);
}

void RepairStatShow()
{
    int hp = MakeInt(GetHullPercent(xi_refCharacter));
	int sp = MakeInt(GetSailPercent(xi_refCharacter));

	SetFormatedText("REPAIR_QTY_H", (hp+RepairHull) + "%");
	SetFormatedText("REPAIR_QTY_S", (sp+RepairSail) + "%");
	if(sti(xi_refCharacter.ship.soiling) == 0)
	{
		//SetFormatedText("REPAIR_Soiling_TEXT" , "не требуется");
		SetNodeUsing("REPAIR_Soiling_CHECKBOX",false);
		SetNodeUsing("REPAIR_Soiling_TEXT",false);
	}else{
		SetFormatedText("REPAIR_Soiling_TEXT" , FindRussianMoneyString(GetChrClearSoilingCoast()));
	}

	RepairMoneyShow();
}

void ClickRepairArror(string _type, int add)
{
    int st = GetCharacterShipType(xi_refCharacter);
    int i;
    int hp = MakeInt(GetHullPercent(xi_refCharacter));
	int sp = MakeInt(GetSailPercent(xi_refCharacter));

	if (_type == "hull")
	{
		if (add > 0)
		{
			if (sti(pchar.Money) >= (GetSailRepairCost(st, RepairSail, refNPCShipyard) + GetHullRepairCost(st, RepairHull + add, refNPCShipyard)))
		    {
		        RepairHull = RepairHull + add;
		    }
		    else
		    {
		        i = sti(pchar.Money) - (GetSailRepairCost(st, RepairSail, refNPCShipyard) + GetHullRepairCost(st, RepairHull, refNPCShipyard));
		        i = i / GetHullRepairCost(st, 1, refNPCShipyard); // на сколько хватит
		        RepairHull = RepairHull + i;
		    }
		    if ((RepairHull + hp) > 100)  RepairHull = 100 - hp;
	    }
	    else
	    {
            RepairHull = RepairHull + add;
			if (RepairHull < 0)  RepairHull = 0;
	    }
	}
	else
	{
	    if (add > 0)
		{
			if (sti(pchar.Money) >= (GetSailRepairCost(st, RepairSail+ add, refNPCShipyard) + GetHullRepairCost(st, RepairHull, refNPCShipyard)))
		    {
		        RepairSail = RepairSail + add;
		    }
		    else
		    {
		        i = sti(pchar.Money) - (GetSailRepairCost(st, RepairSail, refNPCShipyard) + GetHullRepairCost(st, RepairHull, refNPCShipyard));
		        i = i / GetSailRepairCost(st, 1, refNPCShipyard); // на сколько хватит
		        RepairSail = RepairSail + i;
		    }
		    if ((RepairSail+sp) > 100)  RepairSail = 100 - sp;
	    }
	    else
	    {
            RepairSail = RepairSail + add;
			if (RepairSail < 0)  RepairSail = 0;
	    }
	}
	RepairStatShow();
}

void RepairOk()
{
    int st = GetCharacterShipType(xi_refCharacter);
    int hp = MakeInt(GetHullPercent(xi_refCharacter));
	int sp = MakeInt(GetSailPercent(xi_refCharacter));
	float ret;

	if(GetChrClearSoilingCoast() > 0 && SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "REPAIR_Soiling_CHECKBOX", 3, 1) && xi_refCharacter.ship.soiling > 0)
	{
		xi_refCharacter.ship.soiling = 0;
		timeSoil = timeSoil + (8-GetCharacterShipClass(xi_refCharacter));
		AddCharacterExpToSkill(pchar, "Repair", (GetChrClearSoilingCoast()) / 2.5));
		AddMoneyToCharacter(pchar, -GetChrClearSoilingCoast());
		iSoilClearCost = 0;
	}

	if (RepairHull > 0)
	{
		timeHull = timeHull + RepairHull * (8-GetCharacterShipClass(xi_refCharacter));
	    AddCharacterExpToSkill(pchar, "Repair", (RepairHull * (7-GetCharacterShipClass(xi_refCharacter)) / 2.5));
		AddMoneyToCharacter(pchar, -GetHullRepairCost(st, RepairHull, refNPCShipyard));

		ret = ProcessHullRepair(xi_refCharacter, stf(RepairHull));
	}
	if (RepairSail > 0)
	{
	  	timeRig = timeRig + RepairSail * (8-GetCharacterShipClass(xi_refCharacter));
	    AddCharacterExpToSkill(pchar, "Repair", (RepairSail * (7-GetCharacterShipClass(xi_refCharacter)) / 3.5));
		AddMoneyToCharacter(pchar,-GetSailRepairCost(st, RepairSail, refNPCShipyard));

		ret = ProcessSailRepair(xi_refCharacter, stf(RepairSail));
	}
	if ((hp + RepairHull) >= 100)
	{
        xi_refCharacter.ship.hp = GetCharacterShipHP(xi_refCharacter);
		DeleteAttribute(xi_refCharacter, "ship.blots");
	}
	if ((sp+RepairSail) >= 100)
	{
		xi_refCharacter.ship.sp = GetCharacterShipSP(xi_refCharacter);
		DeleteAttribute(xi_refCharacter, "ship.sails");
		DeleteAttribute(xi_refCharacter, "ship.masts");
	}
	///
	ExitRepairMenu();
	st = sti(GameInterface.SHIPS_SCROLL.current);
	FillShipsScroll();
	GameInterface.SHIPS_SCROLL.current = st;
	nCurScrollNum = st;
   	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"SHIPS_SCROLL",-1);
	OnShipScrollChange();
	SetButtionsAccess();
}

void RepairAll()
{
    ClickRepairArror("sail", 100);
    ClickRepairArror("hull", 100);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"REPAIR_Soiling_CHECKBOX", 2, 1, 1);
	ClickREPAIR_Soiling();
}

void BuyShipEvent()
{
	if (GetSelectable("BUTTON_BUY"))
	{
	    ShowMessageInfo();
	}
}

void ClickREPAIR_Soiling()
{
	if((sti(xi_refCharacter.ship.soiling) != 0)&&(sti(pchar.money) >= GetChrClearSoilingCoast()))
	{
		if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "REPAIR_Soiling_CHECKBOX", 3, 1))
		{
			iSoilClearCost = GetChrClearSoilingCoast();
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"REPAIR_Soiling_TEXT", 8,0,argb(255,255,255,200));
		}else{
			iSoilClearCost = 0;
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"REPAIR_Soiling_TEXT", 8,0,argb(255,196,196,196));
		}
	}else{
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"REPAIR_Soiling_CHECKBOX", 2, 1, 0);
		iSoilClearCost = 0;
	}

	RepairMoneyShow();

//	iFullPrice = iHullRepairCost + iSailsRepairCost + iCannonsRepairCost + iSoilClearCost;
//	UpdateRepairWindow();
}

int GetChrClearSoilingCoast()
{
	int Soiling = xi_refCharacter.ship.soiling;
	int iClass = sti(RealShips[sti(xi_refCharacter.ship.type)].Class);
	int sum = 50;

	switch(iClass)
	{
		case 7:
			sum= 100;
			if(Soiling > 25){sum= sum + ((Soiling-25) * 5)}
		break;
		case 6:
			sum= 350;
			if(Soiling > 25){sum= sum + ((Soiling-25) * 10)}
		break;
		case 5:
			sum= 600;
			if(Soiling > 25){sum= sum + ((Soiling-25) * 12)}
		break;
		case 4:
			sum= 1000;
			if(Soiling > 25){sum= sum + ((Soiling-25) * 15)}
		break;
		case 3:
			sum= 1500;
			if(Soiling > 25){sum= sum + ((Soiling-25) * 25)}
		break;
		case 2:
			sum= 1700;
			if(Soiling > 25){sum= sum + ((Soiling-25) * 30)}
		break;
		case 1:
			sum= 2500;
			if(Soiling > 25){sum= sum + ((Soiling-25) * 35)}
		break;
	}

	return sum;
}

void CloseShipUp()
{
	XI_WindowShow("MAIN_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);
	XI_WindowShow("SHIPSUP_WINDOW", false);
	XI_WindowDisable("SHIPSUP_WINDOW", true);
	SetNodeUsing("MAIN_WINDOW", true);
	SetNodeUsing("SHIPSUP_WINDOW", false);
	SetShipOTHERTable("TABLE_OTHER",xi_refCharacter);
}

void OpenShipUp()
{
	int upsq = 0;
	XI_WindowShow("MAIN_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);
	XI_WindowShow("SHIPSUP_WINDOW", true);
	XI_WindowDisable("SHIPSUP_WINDOW", false);
	SetNodeUsing("MAIN_WINDOW", false);
	SetNodeUsing("SHIPSUP_WINDOW", true);
	upgradevalue = 0;
	int iShip = sti(xi_refCharacter.Ship.Type);
	for (int i = 0; i < 6; i++)
	{
        string row = "tr" + (i+1);
        GameInterface.SHIPSUP_TABLE.(row).td1.icon.group = "SHIP_UPGRADES";
		GameInterface.SHIPSUP_TABLE.(row).td1.icon.width = 128;
    	GameInterface.SHIPSUP_TABLE.(row).td1.icon.height = 128;
    	GameInterface.SHIPSUP_TABLE.(row).td1.icon.offset = "-3, 0";
    	GameInterface.SHIPSUP_TABLE.(row).td1.textoffset = "65,0";
		GameInterface.SHIPSUP_TABLE.(row).td1.str = "";
		GameInterface.SHIPSUP_TABLE.(row).td1.align = "left";
		GameInterface.SHIPSUP_TABLE.(row).td1.scale = 0.8;
		GameInterface.SHIPSUP_TABLE.(row).td2.scale = 1.0;
		GameInterface.SHIPSUP_TABLE.(row).td3.scale = 1.0;
		switch (i)
		{
			case 0:
				GameInterface.SHIPSUP_TABLE.(row).td2.str = GetConvertStr("SUP_HULL_descr","ShipsDescribe.txt");
				if (CheckAttribute(RealShips[iShip],"Tuning.HullSpecial"))
				{
					GameInterface.SHIPSUP_TABLE.(row).td1.icon.image = "EXTRAHULLON";
					GameInterface.SHIPSUP_TABLE.(row).td3.str = "Уже улучшено";
					upgradevalue = 0;
					upsq++;
				}
				else
				{
					GameInterface.SHIPSUP_TABLE.(row).td1.icon.image = "EXTRAHULLOFF";
					if (RealShips[iShip].Type.War == true && RealShips[iShip].Type.Merchant == false) GameInterface.SHIPSUP_TABLE.(row).td3.str = "Можно улучшить";
						else GameInterface.SHIPSUP_TABLE.(row).td3.str = "Апгрейд невозможен для данного корабля";
				}
				if (RealShips[iShip].Type.War == false && RealShips[iShip].Type.Merchant == true) GameInterface.SHIPSUP_TABLE.(row).td3.str = "Апгрейд невозможен";
			break;
			case 1:
				GameInterface.SHIPSUP_TABLE.(row).td2.str = GetConvertStr("SUP_SAIL_descr","ShipsDescribe.txt");
				if (CheckAttribute(RealShips[iShip],"Tuning.SailsSpecial"))
				{
					GameInterface.SHIPSUP_TABLE.(row).td1.icon.image = "EXTRASAILON";
					GameInterface.SHIPSUP_TABLE.(row).td3.str = "Уже улучшено";
					upgradevalue = 0;
					upsq++;
				}
				else
				{
					GameInterface.SHIPSUP_TABLE.(row).td1.icon.image = "EXTRASAILOFF";
					GameInterface.SHIPSUP_TABLE.(row).td3.str = "Можно улучшить";
				}
			break;
			case 2:
				GameInterface.SHIPSUP_TABLE.(row).td2.str = GetConvertStr("SUP_CANNONS_descr","ShipsDescribe.txt");
				if (CheckAttribute(RealShips[iShip],"Tuning.CannonsSpecial"))
				{
					GameInterface.SHIPSUP_TABLE.(row).td1.icon.image = "EXTRAGUNSON";
					GameInterface.SHIPSUP_TABLE.(row).td3.str = "Уже улучшено";
					upgradevalue = 0;
					upsq++;
				}
				else
				{
					GameInterface.SHIPSUP_TABLE.(row).td1.icon.image = "EXTRAGUNSOFF";
					if (RealShips[iShip].Type.War == true && RealShips[iShip].Type.Merchant == false) GameInterface.SHIPSUP_TABLE.(row).td3.str = "Можно улучшить";
						else GameInterface.SHIPSUP_TABLE.(row).td3.str = "Апгрейд невозможен для данного корабля";
				}
				if (RealShips[iShip].Type.War == false && RealShips[iShip].Type.Merchant == true) GameInterface.SHIPSUP_TABLE.(row).td3.str = "Апгрейд невозможен";
			break;
			case 3:
				GameInterface.SHIPSUP_TABLE.(row).td2.str = GetConvertStr("SUP_HULLCOPPER_descr","ShipsDescribe.txt");
				if (CheckAttribute(RealShips[iShip],"Tuning.CuBot"))
				{
					GameInterface.SHIPSUP_TABLE.(row).td1.icon.image = "EXTRAHULLKRENGON";
					GameInterface.SHIPSUP_TABLE.(row).td3.str = "Уже улучшено";
					upgradevalue = 0;
					upsq++;
				}
				else
				{
					GameInterface.SHIPSUP_TABLE.(row).td1.icon.image = "EXTRAHULLKRENGOFF";
					GameInterface.SHIPSUP_TABLE.(row).td3.str = "Можно улучшить";
				}
			break;
			case 4:
				GameInterface.SHIPSUP_TABLE.(row).td2.str = GetConvertStr("SUP_CAPACITY_descr","ShipsDescribe.txt");
				if (CheckAttribute(RealShips[iShip],"Tuning.BotPack"))
				{
					GameInterface.SHIPSUP_TABLE.(row).td1.icon.image = "ExtraCapacityOn";
					GameInterface.SHIPSUP_TABLE.(row).td3.str = "Уже улучшено";
					upgradevalue = 0;
					upsq++;
				}
				else
				{
					GameInterface.SHIPSUP_TABLE.(row).td1.icon.image = "ExtraCapacityOff";
					if (RealShips[iShip].Type.War == false && RealShips[iShip].Type.Merchant == true) GameInterface.SHIPSUP_TABLE.(row).td3.str = "Можно улучшить";
						else GameInterface.SHIPSUP_TABLE.(row).td3.str = "Апгрейд невозможен для данного корабля";
				}
				if (RealShips[iShip].Type.War == true && RealShips[iShip].Type.Merchant == false) GameInterface.SHIPSUP_TABLE.(row).td3.str = "Апгрейд невозможен";
			break;
			case 5:
				GameInterface.SHIPSUP_TABLE.(row).td2.str = GetConvertStr("SUP_BIGSIDES_descr","ShipsDescribe.txt");
				if (CheckAttribute(RealShips[iShip],"Tuning.HighBort"))
				{
					GameInterface.SHIPSUP_TABLE.(row).td1.icon.image = "ExtraBigSidesOn";
					GameInterface.SHIPSUP_TABLE.(row).td3.str = "Уже улучшено";
					upgradevalue = 0;
					upsq++;
				}
				else
				{
					GameInterface.SHIPSUP_TABLE.(row).td1.icon.image = "ExtraBigSidesOff";
					GameInterface.SHIPSUP_TABLE.(row).td3.str = "Можно улучшить";
				}
			break;
		}
		if (upsq >= 3) SetFormatedText("SHIPSUP_VALUE","Максимальное количество апгрейдов");
		else SetFormatedText("SHIPSUP_VALUE",FindRussianMoneyString(upgradevalue));
		SetFormatedText("SHIPSUP_CAPTION", "Уникальные улучшения корабля");
		SetFormatedText("SHIPSUP_Q", "Улучшений: "+upsq+"/3");
		SetSelectable("SHIPSUP_DOUP", false);
    }
	GameInterface.SHIPSUP_TABLE.select = 1;
	Table_UpdateWindow("SHIPSUP_TABLE");
}

void DoUpgrade()
{
	if (upgradevalue > 0) AddMoneyToCharacter(pchar, -upgradevalue);
	ref shTo = &RealShips[sti(xi_refCharacter.Ship.Type)];
	bool up = true;
	switch (uptype)
	{
		case 1:
			if (!CheckAttribute(shTo,"Tuning.HullSpecial"))
			{
				shTo.Tuning.HullSpecial = 1;
				shTo.price = makeint(sti(shTo.price)*1.5);
			}
			else
			{
				DeleteAttribute(shTo,"Tuning.HullSpecial");
				shTo.price = makeint(sti(shTo.price)/1.5);
				up = false;
			}
		break;
		case 2:
			if (!CheckAttribute(shTo,"Tuning.SailsSpecial"))
			{
				shTo.Tuning.SailsSpecial = 1;
				shTo.price = makeint(sti(shTo.price)*1.35);
			}
			else
			{
				DeleteAttribute(shTo,"Tuning.SailsSpecial");
				shTo.price = makeint(sti(shTo.price)/1.35);
				up = false;
			}
		break;
		case 3:
			if (!CheckAttribute(shTo,"Tuning.CannonsSpecial"))
			{
				shTo.Tuning.CannonsSpecial = 1;
				shTo.price = makeint(sti(shTo.price)*1.25);
			}
			else
			{
				DeleteAttribute(shTo,"Tuning.CannonsSpecial");
				shTo.price = makeint(sti(shTo.price)/1.25);
				up = false;
			}
		break;
		case 4:
			if (!CheckAttribute(shTo,"Tuning.CuBot"))
			{
				shTo.Tuning.CuBot = 1;
				shTo.price = makeint(sti(shTo.price)*1.4);
			}
			else
			{
				DeleteAttribute(shTo,"Tuning.CuBot");
				shTo.price = makeint(sti(shTo.price)/1.4);
				up = false;
			}
		break;
		case 5:
			if (!CheckAttribute(shTo,"Tuning.BotPack"))
			{
				shTo.Tuning.BotPack = 1;
				shTo.price = makeint(sti(shTo.price)*1.5);
				shTo.Capacity = sti(shTo.Capacity) + makeint(sti(shTo.Capacity)/2);
				shTo.HP = sti(shTo.HP) - makeint(sti(shTo.HP)/2);
				if (xi_refCharacter.ship.hp > sti(shTo.HP)) xi_refCharacter.ship.hp = sti(shTo.HP);
			}
			else
			{
				DeleteAttribute(shTo,"Tuning.BotPack");
				shTo.price = makeint(sti(shTo.price)/1.5);
				shTo.Capacity = makeint(sti(shTo.Capacity)/1.5);
				shTo.HP = sti(shTo.HP)*2;
				up = false;
			}
		break;
		case 6:
			if (!CheckAttribute(shTo,"Tuning.HighBort"))
			{
				shTo.Tuning.HighBort = 1;
				shTo.price = makeint(sti(shTo.price)*1.4);
			}
			else
			{
				DeleteAttribute(shTo,"Tuning.HighBort");
				shTo.price = makeint(sti(shTo.price)/1.4);
				up = false;
			}
		break;
	}
	timeUpgrade = timePreUpgrade;
	OpenShipUp();
}

// Lugger: Смена разцветки корпуса -->
void ExitChangeHullMenu()
{
	HideChangeHullMenu();
	OnShipScrollChange();
}

void HideChangeHullMenu()
{
	XI_WindowShow("CHANGE_HULL_WINDOW", false);
	XI_WindowDisable("CHANGE_HULL_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);
	SetCurrentNode("TABLE_OTHER");
	sMessageMode = "";
}

void ShowChangeHullMenu()
{
	ref rShip = GetRealShip(sti(xi_refCharacter.Ship.Type));

	XI_WindowShow("CHANGE_HULL_WINDOW", true);
	XI_WindowDisable("CHANGE_HULL_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);
	SetCurrentNode("CHANGE_Hull_CANCEL");

	ref refShip = GetRealShip(sti(xi_refCharacter.Ship.Type));
	int iCurrentType = sti(refShip.Ship.Upgrades.Hull);
	PChar.ChangeHull.Type = iCurrentType;

	SetChangeHullInfo();
}

int GetShipHullCount(ref rShip)
{
	int iMax = 3;
	if (CheckAttribute(rShip,"hullNums")) iMax = sti(rShip.hullNums);
	return iMax;
}

void SetChangeHullInfo()
{
	ref rShip = GetRealShip(sti(xi_refCharacter.Ship.Type));
	string sShipName = rShip.name;

	SetFormatedText("CHANGE_HULL_CAPTION", "Окраска корпуса (" + sti(PChar.ChangeHull.Type) + "/" + GetShipHullCount(rShip) + ")");

	string sTypeName = "Hull" + sti(PChar.ChangeHull.Type);

	string sTexture = GetShipTexturesForChangeHull();
	SetNewPicture("CHANGE_HULL_TYPE", "ships\" + sShipName + "\" + sTypeName + "\" + sTexture);

	int iMoney = CalculateHullChangePrice(sti(rShip.Class));
	SetFormatedText("CHANGE_HULL_MONEY", "Цена: " + iMoney);

	if(sti(PChar.money) > iMoney)
	{
		SetSelectable("CHANGE_HULL_OK", true);
	}
	else
	{
		SetSelectable("CHANGE_HULL_OK", false);
	}
}

string GetShipTexturesForChangeHull()
{
	ref rShip = GetRealShip(sti(xi_refCharacter.Ship.Type));
	string sShipName = rShip.name;

	int Hulls = LanguageOpenFile("Hulls.txt");
	string sTex = LanguageConvertString(Hulls, sShipName);
	LanguageCloseFile(Hulls);

	return sTex;
}

void SelectChangeHull(bool bLeft)
{
	ref rShip = GetRealShip(sti(xi_refCharacter.Ship.Type));
	string sShipName = rShip.name;

	int iMax = GetShipHullCount(rShip);

	if(bLeft)
	{
		PChar.ChangeHull.Type = sti(PChar.ChangeHull.Type) - 1;

		if(sti(PChar.ChangeHull.Type) < 1)
		{
			PChar.ChangeHull.Type = iMax;
		}
	}
	else
	{
		PChar.ChangeHull.Type = sti(PChar.ChangeHull.Type) + 1;

		if(sti(PChar.ChangeHull.Type) > iMax)
		{
			PChar.ChangeHull.Type = 1;
		}
	}

	SetChangeHullInfo();
}

void SetNewHullToCharacterShip()
{
	ref refShip = GetRealShip(sti(xi_refCharacter.Ship.Type));

	int iMoney = CalculateHullChangePrice(sti(refShip.Class));
	AddMoneyToCharacter(PChar, -iMoney);

	refShip.Ship.Upgrades.Hull = sti(PChar.ChangeHull.Type);

	ExitChangeHullMenu();
}

int CalculateHullChangePrice(int value)
{
	switch (value)
	{
		case 7: return 1000+drand(500);
		break;
		case 6: return 5000+drand(2500);
		break;
		case 5: return 10000+drand(5000);
		break;
		case 4: return 20000+drand(10000);
		break;
		case 3: return 35000+drand(17500);
		break;
		case 2: return 50000+drand(25000);
		break;
		case 1: return 100000+drand(50000);
		break;
	}
}

// Lugger: Смена разцветки корпуса <--
