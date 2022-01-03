string totalInfo;
int idLngFile = -1;

int iBuilderBlocks = sti(PChar.BuildingColony.Blocks);
int iBuilderPlanks = sti(PChar.BuildingColony.Planks);
int iBuilderMahogany = sti(PChar.BuildingColony.Mahogany);
int iBuilderEbony = sti(PChar.BuildingColony.Ebony);
int iBuilderSlaves = sti(PChar.BuildingColony.Slaves);
int iBuilderFood = sti(PChar.BuildingColony.Food);

int iBlocks = GetCargoGoods(PChar, GOOD_BRICK);
int iPlanks = GetCargoGoods(PChar, GOOD_PLANKS);
int iMahogany = GetCargoGoods(PChar, GOOD_MAHOGANY);
int iEbony = GetCargoGoods(PChar, GOOD_EBONY);
int iSlaves = GetCargoGoods(PChar, GOOD_SLAVES);
int iFood = GetCargoGoods(PChar, GOOD_FOOD);

int iCheckSoldiersType = 1;

int iCheckTownType = 1;
int iCheckStoreType = 1;
int iCheckShipyardType = 1;
int iCheckTavernType = 1;
int iCheckBankType = 1;
int iCheckTownhallType = 1;

void InitInterface_BB(string iniName, bool bCreate, bool bArh)
{
    	GameInterface.title = "titleColonyBuilding";

    	if(bCreate) { GameInterface.title = "titleColony"; }
    	if(bCreate && bArh) { GameInterface.title = "titleColonyArchitecture"; }

    	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	CheckNode(bCreate, bArh);
	if(bCreate)
	{
		if(!bArh)
		{
			CreateColonyInfo();
			CreateColonyInfoSoldiersType();
		}
		else
		{
			CreateArchitectureInfo();
		}
	}
	else
	{
		UpgradeMainInterface();
	}

	PChar.ColonyBuilding.bAch = bArh;
	PChar.ColonyBuilding.bCreate = bCreate;

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);
	SetEventHandler("ColonyNameTemp","ColonyNameTemp",0);
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
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");
	DelEventHandler("ColonyNameTemp","ColonyNameTemp");

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);

	if(sti(PChar.ColonyBuilding.bCreate) == 0 && sti(PChar.ColonyBuilding.bAch) == 0)
	{
		if(sti(PChar.BuildingColony.Blocks) == 0 && sti(PChar.BuildingColony.Planks) == 0 && sti(PChar.BuildingColony.Mahogany) == 0 && sti(PChar.BuildingColony.Ebony) == 0 && sti(PChar.BuildingColony.Slaves) == 0 && sti(PChar.BuildingColony.Food) == 0)
		{
			if(PChar.ColonyBuilding.Stage == "0")
			{
				LAi_QuestDelay("ColonyBuildingCayman_2", 0.1);
			}
			else
			{
				if(PChar.ColonyBuilding.Stage == "1")
				{
					LAi_QuestDelay("ColonyModification_1_1", 0.1);
				}
				else
				{
					if(PChar.ColonyBuilding.Stage == "2")
					{
						LAi_QuestDelay("ColonyFortBuilding_1_1", 0.1);
					}
				}
			}
		}
	}
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

		case "BLOCKS_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				BlocksRemoved();
			}
		break;

		case "PLANKS_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				PlanksRemoved();
			}
		break;

		case "MAHOGANY_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				MahoganyRemoved();
			}
		break;

		case "EBONY_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				EbonyRemoved();
			}
		break;

		case "SLAVES_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				SlavesRemoved();
			}
		break;

		case "FOOD_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				FoodRemoved();
			}
		break;

		case "ENGLAND":
			if(comName=="activate" || comName=="click")
			{
				ChangeNation(ENGLAND);
			}
		break;

		case "FRANCE":
			if(comName=="activate" || comName=="click")
			{
				ChangeNation(FRANCE);
			}
		break;

		case "SPAIN":
			if(comName=="activate" || comName=="click")
			{
				ChangeNation(SPAIN);
			}
		break;

		case "HOLLAND":
			if(comName=="activate" || comName=="click")
			{
				ChangeNation(HOLLAND);
			}
		break;

		case "PIRATE":
			if(comName=="activate" || comName=="click")
			{
				ChangeNation(PIRATE);
			}
		break;

		case "CANCEL":
			if(comName=="activate" || comName=="click")
			{
				iCheckSoldiersType = 1;
				CreateColonyInfo();
				CreateColonyInfoSoldiersType();
			}
		break;

		case "OK":
			if(comName=="activate" || comName=="click")
			{
				if(GameInterface.COLONY_NAME.str != PChar.ColonyBuilding.ColonyName && PChar.ColonyBuilding.FirstBuild != true)
				{
					PChar.ColonyBuilding.ColonyName = GameInterface.COLONY_NAME.str;

					DeleteQuestHeader("MY_COLONY");
					SetQuestHeader("MY_COLONY");
					AddQuestRecord("MY_COLONY", "10");
					AddQuestUserDataForTitle("MY_COLONY", "sColonyName", PChar.ColonyBuilding.ColonyName);
					AddQuestUserData("MY_COLONY", "sColonyName", PChar.ColonyBuilding.ColonyName);
				}

				if(sti(PChar.ColonyBuilding.FirstBuild) == 1)
				{
					PChar.ColonyBuilding.ColonyName = GameInterface.COLONY_NAME.str;

					SetQuestHeader("MY_COLONY");
					AddQuestRecord("MY_COLONY", "13");
					AddQuestUserDataForTitle("MY_COLONY", "sColonyName", PChar.ColonyBuilding.ColonyName);
					AddQuestUserData("MY_COLONY", "sColonyName", PChar.ColonyBuilding.ColonyName);

					PChar.ColonyBuilding.FirstBuild = false;
				}

				string sSoldiersType = GetCheckSoldiersTypeName();
				PChar.ColonyBuilding.SoldiersType = sSoldiersType;
				Log_TestInfo(sSoldiersType);
				RenamedColonyCaiman();
				ProcessBreakExit();
			}
		break;

		case "CHECK_TOWN_TYPE_LEFT":
			if(comName=="activate" || comName=="click")
			{
				CheckArchitectureType("Town", true);
			}
		break;

		case "CHECK_TOWN_TYPE_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				CheckArchitectureType("Town", false);
			}
		break;

		case "CHECK_STORE_LEFT":
			if(comName=="activate" || comName=="click")
			{
				CheckArchitectureType("Store", true);
			}
		break;

		case "CHECK_STORE_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				CheckArchitectureType("Store", false);
			}
		break;

		case "CHECK_SHIPYARD_LEFT":
			if(comName=="activate" || comName=="click")
			{
				CheckArchitectureType("Shipyard", true);
			}
		break;

		case "CHECK_SHIPYARD_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				CheckArchitectureType("Shipyard", false);
			}
		break;

		case "CHECK_TAVERN_LEFT":
			if(comName=="activate" || comName=="click")
			{
				CheckArchitectureType("Tavern", true);
			}
		break;

		case "CHECK_TAVERN_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				CheckArchitectureType("Tavern", false);
			}
		break;

		case "CHECK_BANK_LEFT":
			if(comName=="activate" || comName=="click")
			{
				CheckArchitectureType("Bank", true);
			}
		break;

		case "CHECK_BANK_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				CheckArchitectureType("Bank", false);
			}
		break;

		case "CHECK_TOWNHALL_LEFT":
			if(comName=="activate" || comName=="click")
			{
				CheckArchitectureType("Townhall", true);
			}
		break;

		case "CHECK_TOWNHALL_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				CheckArchitectureType("Townhall", false);
			}
		break;

		case "ACTR_RESET":
			if(comName=="activate" || comName=="click")
			{
				ResetArchitectureChanges();
			}
		break;

		case "ACTR_OK":
			if(comName=="activate" || comName=="click")
			{
				ArchitectureOk();
			}
		break;

		case "SOLDIERS_TYPE_LEFT":
			if(comName=="activate" || comName=="click")
			{
				CheckSoldiersType(true);
			}
		break;

		case "SOLDIERS_TYPE_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				CheckSoldiersType(false);
			}
		break;

	}
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void DeleteInterfaceStrings()
{
	GameInterface.strings.OnChar = "";
	GameInterface.strings.Need = "";
	GameInterface.strings.BlocksString = "";
	GameInterface.strings.BuilderBlocksString = "";
	GameInterface.strings.QuantityBlocks = "";
	GameInterface.strings.BuilderBlocks = "";
	GameInterface.strings.PlanksString = "";
	GameInterface.strings.BuilderPlanksString = "";
	GameInterface.strings.QuantityPlanks = "";
	GameInterface.strings.BuilderPlanks = "";
	GameInterface.strings.MahoganyString = "";
	GameInterface.strings.BuilderMahoganyString = "";
	GameInterface.strings.QuantityMahogany = "";
	GameInterface.strings.BuilderMahogany = "";
	GameInterface.strings.EbonyString = "";
	GameInterface.strings.BuilderEbonyString = "";
	GameInterface.strings.QuantityEbony = "";
	GameInterface.strings.BuilderEbony = "";
	GameInterface.strings.SlavesString = "";
	GameInterface.strings.BuilderSlavesString = "";
	GameInterface.strings.QuantitySlaves = "";
	GameInterface.strings.BuilderSlaves = "";
	GameInterface.strings.FoodString = "";
	GameInterface.strings.BuilderFoodString = "";
	GameInterface.strings.QuantityFood = "";
	GameInterface.strings.BuilderFood = "";
}

void UpgradeMainInterface()
{
	DeleteInterfaceStrings();

	int iBlocks = GetCargoGoods(pchar, GOOD_BRICK);
	int iPlanks = GetCargoGoods(pchar, GOOD_PLANKS);
	int iMahogany = GetCargoGoods(pchar, GOOD_MAHOGANY);
	int iEbony = GetCargoGoods(pchar, GOOD_EBONY);
	int iSlaves = GetCargoGoods(pchar, GOOD_SLAVES);
	int iFood = GetCargoGoods(pchar, GOOD_FOOD);

	int iBuilderBlocks = sti(PChar.BuildingColony.Blocks);
	int iBuilderPlanks = sti(PChar.BuildingColony.Planks);
	int iBuilderMahogany = sti(PChar.BuildingColony.Mahogany);
	int iBuilderEbony = sti(PChar.BuildingColony.Ebony);
	int iBuilderSlaves = sti(PChar.BuildingColony.Slaves);
	int iBuilderFood = sti(PChar.BuildingColony.Food);

	int iBlocksColor = ColorQuantityGoods(GOOD_BRICK, "Blocks");
	int iPlanksColor = ColorQuantityGoods(GOOD_PLANKS, "Planks");
	int iMahoganyColor = ColorQuantityGoods(GOOD_MAHOGANY, "Mahogany");
	int iEbonyColor = ColorQuantityGoods(GOOD_EBONY, "Ebony");
	int iSlavesColor = ColorQuantityGoods(GOOD_SLAVES, "Slaves");
	int iFoodColor = ColorQuantityGoods(GOOD_FOOD, "Food");

	CreateString(true,"OnChar","Имеется: ", FONT_CAPTION, COLOR_NORMAL, 160,44,SCRIPT_ALIGN_CENTER,1.5);
	CreateString(true,"Good","Товар: ", FONT_CAPTION, COLOR_NORMAL, 390,44,SCRIPT_ALIGN_CENTER,1.5);
	CreateString(true,"Need","Требуется: ", FONT_CAPTION, COLOR_NORMAL, 625,44,SCRIPT_ALIGN_CENTER,1.5);

	CreateImage("Blocks", "GOODS", "Brick", 310,73,400,163);
	CreateImage("Planks", "GOODS", "Planks", 310,156,400,246);
	CreateImage("Mahogany", "GOODS", "Mahogany", 310,239,400,329);
	CreateImage("Ebony", "GOODS", "Ebony", 310,320,400,410);
	CreateImage("Slaves", "GOODS", "Slaves", 310,405,400,495);
	CreateImage("Food", "GOODS", "Food", 310,488,400,578);

	CreateString(true,"BlocksString","Кирпичи", FONT_CAPTION, COLOR_NORMAL, 150,90,SCRIPT_ALIGN_CENTER,1.2);
	CreateString(true,"BuilderBlocksString","Кирпичи", FONT_CAPTION, COLOR_NORMAL, 630,90,SCRIPT_ALIGN_CENTER,1.2);
	CreateString(true,"QuantityBlocks","" + iBlocks, FONT_BOLD_NUMBERS, iBlocksColor, 150,120,SCRIPT_ALIGN_CENTER,1.2);
	CreateString(true,"BuilderBlocks","" + iBuilderBlocks, FONT_BOLD_NUMBERS, COLOR_NORMAL, 630,120,SCRIPT_ALIGN_CENTER,1.2);

	CreateString(true,"PlanksString","Доски", FONT_CAPTION, COLOR_NORMAL, 150,175,SCRIPT_ALIGN_CENTER,1.2);
	CreateString(true,"BuilderPlanksString","Доски", FONT_CAPTION, COLOR_NORMAL, 630,175,SCRIPT_ALIGN_CENTER,1.2);
	CreateString(true,"QuantityPlanks","" + iPlanks, FONT_BOLD_NUMBERS, iPlanksColor, 150,205,SCRIPT_ALIGN_CENTER,1.2);
	CreateString(true,"BuilderPlanks","" + iBuilderPlanks, FONT_BOLD_NUMBERS, COLOR_NORMAL, 630,205,SCRIPT_ALIGN_CENTER,1.2);

	CreateString(true,"MahoganyString","Красное дерево", FONT_CAPTION, COLOR_NORMAL, 150,255,SCRIPT_ALIGN_CENTER,1.2);
	CreateString(true,"BuilderMahoganyString","Красное дерево", FONT_CAPTION, COLOR_NORMAL, 630,255,SCRIPT_ALIGN_CENTER,1.2);
	CreateString(true,"QuantityMahogany","" + iMahogany, FONT_BOLD_NUMBERS, iMahoganyColor, 150,285,SCRIPT_ALIGN_CENTER,1.2);
	CreateString(true,"BuilderMahogany","" + iBuilderMahogany, FONT_BOLD_NUMBERS, COLOR_NORMAL, 630,285,SCRIPT_ALIGN_CENTER,1.2);

	CreateString(true,"EbonyString","Чёрное дерево", FONT_CAPTION, COLOR_NORMAL, 150,340,SCRIPT_ALIGN_CENTER,1.2);
	CreateString(true,"BuilderEbonyString","Чёрное дерево", FONT_CAPTION, COLOR_NORMAL, 630,340,SCRIPT_ALIGN_CENTER,1.2);
	CreateString(true,"QuantityEbony","" + iEbony, FONT_BOLD_NUMBERS, iEbonyColor, 150,370,SCRIPT_ALIGN_CENTER,1.2);
	CreateString(true,"BuilderEbony","" + iBuilderEbony, FONT_BOLD_NUMBERS, COLOR_NORMAL, 630,370,SCRIPT_ALIGN_CENTER,1.2);

	CreateString(true,"SlavesString","Рабы", FONT_CAPTION, COLOR_NORMAL, 150,425,SCRIPT_ALIGN_CENTER,1.2);
	CreateString(true,"BuilderSlavesString","Рабы", FONT_CAPTION, COLOR_NORMAL, 630,425,SCRIPT_ALIGN_CENTER,1.2);
	CreateString(true,"QuantitySlaves","" + iSlaves, FONT_BOLD_NUMBERS, iSlavesColor, 150,455,SCRIPT_ALIGN_CENTER,1.2);
	CreateString(true,"BuilderSlaves","" + iBuilderSlaves, FONT_BOLD_NUMBERS, COLOR_NORMAL, 630,455,SCRIPT_ALIGN_CENTER,1.2);

	CreateString(true,"FoodString","Провиант", FONT_CAPTION, COLOR_NORMAL, 150,510,SCRIPT_ALIGN_CENTER,1.2);
	CreateString(true,"BuilderFoodString","Провиант", FONT_CAPTION, COLOR_NORMAL, 630,510,SCRIPT_ALIGN_CENTER,1.2);
	CreateString(true,"QuantityFood","" + iFood, FONT_BOLD_NUMBERS, iFoodColor, 150,540,SCRIPT_ALIGN_CENTER,1.2);
	CreateString(true,"BuilderFood","" + iBuilderFood, FONT_BOLD_NUMBERS, COLOR_NORMAL, 630,540,SCRIPT_ALIGN_CENTER,1.2);
}

int ColorQuantityGoods(int iGood, string sGood)
{
	ref PChar = GetMainCharacter();

	int iNeed = sti(PChar.BuildingColony.(sGood));

	int iMinus = argb(255,255,128,128);
	int iPlus = argb(255,128,255,128);
	int iNormal = argb(255,255,255,255);

	if(iNeed == 0)
	{
		return iNormal;
	}

	if(GetCargoGoods(PChar, iGood) >= iNeed)
	{
		return iPlus;
	}
	else
	{
		return iMinus;
	}
	return iMinus;
}

void BlocksRemoved()
{
	int iBlocks = GetCargoGoods(PChar, GOOD_BRICK);

	if(iBlocks == 0)
	{
		return;
	}

	if(iBlocks < (sti(PChar.BuildingColony.Blocks)))
	{
		RemoveCharacterGoods(PChar, GOOD_BRICK, iBlocks);
		PChar.BuildingColony.Blocks = (sti(PChar.BuildingColony.Blocks))-iBlocks;
	}
	else
	{
		RemoveCharacterGoods(PChar, GOOD_BRICK, (sti(PChar.BuildingColony.Blocks)));
		PChar.BuildingColony.Blocks = 0;
	}

	UpgradeMainInterface();
}

void PlanksRemoved()
{
	int iPlanks = GetCargoGoods(PChar, GOOD_PLANKS);

	if(iPlanks == 0)
	{
		return;
	}

	if(iPlanks < (sti(PChar.BuildingColony.Planks)))
	{
		RemoveCharacterGoods(PChar, GOOD_PLANKS, iPlanks);
		PChar.BuildingColony.Planks =(sti(PChar.BuildingColony.Planks))-iPlanks;
	}
	else
	{
		RemoveCharacterGoods(PChar, GOOD_PLANKS, (sti(PChar.BuildingColony.Planks)));
		PChar.BuildingColony.Planks = 0;
	}

	UpgradeMainInterface();
}

void MahoganyRemoved()
{
	int iMahogany = GetCargoGoods(PChar, GOOD_MAHOGANY);

	if(iMahogany == 0)
	{
		return;
	}

	if(iMahogany < (sti(PChar.BuildingColony.Mahogany)))
	{
		RemoveCharacterGoods(PChar, GOOD_MAHOGANY, iMahogany);
		PChar.BuildingColony.Mahogany = (sti(PChar.BuildingColony.Mahogany))-iMahogany;
	}
	else
	{
		RemoveCharacterGoods(PChar, GOOD_MAHOGANY, (sti(PChar.BuildingColony.Mahogany)));
		PChar.BuildingColony.Mahogany = 0;
	}

	UpgradeMainInterface();
}

void EbonyRemoved()
{
	int iEbony = GetCargoGoods(PChar, GOOD_EBONY);

	if(iEbony == 0)
	{
		return;
	}

	if(iEbony < (sti(PChar.BuildingColony.Ebony)))
	{
		RemoveCharacterGoods(PChar, GOOD_EBONY, iEbony);
		PChar.BuildingColony.Ebony = (sti(PChar.BuildingColony.Ebony))-iEbony;
	}
	else
	{
		RemoveCharacterGoods(PChar, GOOD_EBONY, (sti(PChar.BuildingColony.Ebony)));
		PChar.BuildingColony.Ebony = 0;
	}

	UpgradeMainInterface();
}

void SlavesRemoved()
{
	int iSlaves = GetCargoGoods(PChar, GOOD_SLAVES);

	if(iSlaves == 0)
	{
		return;
	}

	if(iSlaves < (sti(PChar.BuildingColony.Slaves)))
	{
		RemoveCharacterGoods(PChar, GOOD_SLAVES, iSlaves);
		PChar.BuildingColony.Slaves = (sti(PChar.BuildingColony.Slaves))-iSlaves;
	}
	else
	{
		RemoveCharacterGoods(PChar, GOOD_SLAVES, (sti(PChar.BuildingColony.Slaves)));
		PChar.BuildingColony.Slaves = 0;
	}

	UpgradeMainInterface();
}

void FoodRemoved()
{
	int iFood = GetCargoGoods(PChar, GOOD_FOOD);

	if(iFood == 0)
	{
		return;
	}

	if(iFood < (sti(PChar.BuildingColony.Food)))
	{
		RemoveCharacterGoods(PChar, GOOD_FOOD, iFood);
		PChar.BuildingColony.Food = (sti(PChar.BuildingColony.Food))-iFood;
	}
	else
	{
		RemoveCharacterGoods(PChar, GOOD_FOOD, (sti(PChar.BuildingColony.Food)));
		PChar.BuildingColony.Food = 0;
	}

	UpgradeMainInterface();
}

////////////////////////////////////////////////////////////////////////////////////////
// Построили колонию - дадим название
////////////////////////////////////////////////////////////////////////////////////////
void CreateColonyInfo()
{
	CreateString(true,"NameHeader","Название колонии", FONT_CAPTION, COLOR_NORMAL, 400,102,SCRIPT_ALIGN_CENTER,1.5);
	CreateString(true,"InName","Введите название колонии: ", FONT_CAPTION, COLOR_NORMAL, 410,160,SCRIPT_ALIGN_CENTER,1.0);

	CreateString(true,"CurName","Текущее название: ", FONT_CAPTION, COLOR_NORMAL, 405,225,SCRIPT_ALIGN_CENTER,1.0);
	CreateString(true,"CurName2", PChar.ColonyBuilding.ColonyName, FONT_CAPTION, argb(255,255,255,128), 400,240,SCRIPT_ALIGN_CENTER,1.5);

	GameInterface.COLONY_NAME.str = PChar.ColonyBuilding.ColonyName;
	ColonyNameTemp();

	if(PChar.ColonyBuilding.FirstBuild == true)
	{
		SetNodeUsing("EXIT_BTN", false);
	}

	CreateString(true,"NationHeader","Внешность солдат", FONT_CAPTION, COLOR_NORMAL, 400,276,SCRIPT_ALIGN_CENTER,1.5);
	// CreateImage("NationHeader", "MAIN_ICONS", "skillborder", 233,276,566,310);

	int iNation = sti(PChar.nation);
	string sNation = GetNationNameByType(iNation);

	CreateString(true,"CurNation2", XI_ConvertString(sNation), FONT_CAPTION, argb(255,255,255,128), 395,345,SCRIPT_ALIGN_CENTER,1.2);
	CreateString(true,"InNation","Выберите нацию: ", FONT_CAPTION, COLOR_NORMAL, 400,370,SCRIPT_ALIGN_CENTER,1.2);
}

void CreateColonyInfoSoldiersType()
{
	string sSoldiersType = GetCheckSoldiersType();
	SetFormatedText("SOLDIERS_TYPE_TEXT", sSoldiersType);

	CheckSelectSoldiersType();
}

void CheckSelectSoldiersType()
{
	if(iCheckSoldiersType == 3)
	{
		SetSelectable("ENGLAND", true);
		SetSelectable("FRANCE", true);
		SetSelectable("SPAIN", true);
		SetSelectable("HOLLAND", true);

		int iNation = sti(PChar.ColonyBuilding.ColonyNation);
		string sNation = GetNationNameByType(iNation);

		ChangeStringColor("CurNation2", argb(255,255,255,128));
		ChangeStringColor("InNation", COLOR_NORMAL);
	}
	else
	{
		SetSelectable("ENGLAND", false);
		SetSelectable("FRANCE", false);
		SetSelectable("SPAIN", false);
		SetSelectable("HOLLAND", false);

		ChangeStringColor("CurNation2", COLOR_DESELECT);
		ChangeStringColor("InNation", COLOR_DESELECT);
	}
}

void ColonyNameTemp()
{
	string sName = GameInterface.COLONY_NAME.str;

	if(GetDisableNames(sName))
	{
		return;
	}

	//PChar.ColonyBuilding.ColonyName = GameInterface.COLONY_NAME.str;
	GameInterface.strings.CurName2 = PChar.ColonyBuilding.ColonyName;
	//GameInterface.strings.CurName2 = GameInterface.COLONY_NAME.str;
}

bool GetDisableNames(string sName)
{
	if(sName == "...")
	{
		return true;
	}

	return false;
}

void ChangeNation(int iNation)
{
	PChar.ColonyBuilding.ColonyNation = iNation;
	GameInterface.strings.CurNation2 = XI_ConvertString(GetNationNameByType(iNation));
}

string GetCheckSoldiersType()
{
	switch(iCheckSoldiersType)
	{
		case 1: return "Офицеры"; break;
		case 2: return "Пираты"; break;
		case 3: return "По нации"; break;
	}

	return "Офицеры";
}

string GetCheckSoldiersTypeName()
{
	switch(iCheckSoldiersType)
	{
		case 1: return "officer"; break;
		case 2: return "pirate"; break;
		case 3: return "nation"; break;
	}

	return "officer";
}

void CheckSoldiersType(bool left)
{
	if(left)
	{
		iCheckSoldiersType--;
	}
	else
	{
		iCheckSoldiersType++;
	}

	if(iCheckSoldiersType > 3) iCheckSoldiersType = 1;
	if(iCheckSoldiersType < 1) iCheckSoldiersType = 3;

	CreateColonyInfoSoldiersType();
}

///////////////////////////////////////////////////////////////////////////////////////////
// архитектура
///////////////////////////////////////////////////////////////////////////////////////////
void CreateArchitectureInfo()
{
	CreateString(true,"TownHeader","Город", FONT_CAPTION, COLOR_NORMAL, 175,105,SCRIPT_ALIGN_CENTER,1.5);
	CreateString(true,"BuildingHeader","Главные здания", FONT_CAPTION, COLOR_NORMAL, 540,105,SCRIPT_ALIGN_CENTER,1.5);

	string sTownPicture = GetArchitecturePictureName(iCheckTownType, "Town");
	SetNewGroupPicture("CHECK_TOWN_TYPE", "COLONY_ARCHITECTURE", sTownPicture);

	int iTownCost = GetCostForBuildArchitecture(iCheckTownType, "Town");
	CreateString(true,"TownCost","Цена: " + iTownCost, FONT_CAPTION, argb(255,255,128,128), 135,305,SCRIPT_ALIGN_LEFT,0.9);

	CreateString(true,"StoreHeader","Магазин", FONT_CAPTION, COLOR_NORMAL, 435,145,SCRIPT_ALIGN_CENTER,0.9);

	string sStorePicture = GetArchitecturePictureName(iCheckStoreType, "Store");
	SetNewGroupPicture("CHECK_STORE_PICTURE", "COLONY_ARCHITECTURE", sStorePicture);

	int iStoreCost = GetCostForBuildArchitecture(iCheckStoreType, "Store");
	CreateString(true,"StoreCost","Цена: " + iStoreCost, FONT_CAPTION, argb(255,255,128,128), 400,280,SCRIPT_ALIGN_LEFT,0.9);

	CreateString(true,"ShipyardHeader","Верфь", FONT_CAPTION, COLOR_NORMAL, 660,145,SCRIPT_ALIGN_CENTER,0.9);
	string sShipyardPicture = GetArchitecturePictureName(iCheckShipyardType, "Shipyard");
	SetNewGroupPicture("CHECK_SHIPYARD_PICTURE", "COLONY_ARCHITECTURE", sShipyardPicture);

	int iShipyardCost = GetCostForBuildArchitecture(iCheckShipyardType, "Shipyard");
	CreateString(true,"ShipyardCost","Цена: " + iShipyardCost, FONT_CAPTION, argb(255,255,128,128), 625,280,SCRIPT_ALIGN_LEFT,0.9);

	CreateString(true,"TavernHeader","Таверна", FONT_CAPTION, COLOR_NORMAL, 435,325,SCRIPT_ALIGN_CENTER,0.9);
	string sTavernPicture = GetArchitecturePictureName(iCheckTavernType, "Tavern");
	SetNewGroupPicture("CHECK_TAVERN_PICTURE", "COLONY_ARCHITECTURE", sTavernPicture);

	int iTavernCost = GetCostForBuildArchitecture(iCheckTavernType, "Tavern");
	CreateString(true,"TavernCost","Цена: " + iTavernCost, FONT_CAPTION, argb(255,255,128,128), 400,460,SCRIPT_ALIGN_LEFT,0.9);

	CreateString(true,"BankHeader","Дом ростовщика", FONT_CAPTION, COLOR_NORMAL, 660,325,SCRIPT_ALIGN_CENTER,0.9);
	string sBankPicture = GetArchitecturePictureName(iCheckBankType, "Bank");
	SetNewGroupPicture("CHECK_BANK_PICTURE", "COLONY_ARCHITECTURE", sBankPicture);

	int iBankCost = GetCostForBuildArchitecture(iCheckBankType, "Bank");
	CreateString(true,"BankCost","Цена: " + iBankCost, FONT_CAPTION, argb(255,255,128,128), 625,460,SCRIPT_ALIGN_LEFT,0.9);

	CreateString(true,"TownhallHeader","Резиденция", FONT_CAPTION, COLOR_NORMAL, 180,335,SCRIPT_ALIGN_CENTER,0.9);
	string sTownhallPicture = GetArchitecturePictureName(iCheckTownhallType, "Townhall");
	SetNewGroupPicture("CHECK_TOWNHALL_PICTURE", "COLONY_ARCHITECTURE", sTownhallPicture);

	int iTownhallCost = GetCostForBuildArchitecture(iCheckTownhallType, "Townhall");
	CreateString(true,"TownhallCost","Цена: " + iTownhallCost, FONT_CAPTION, argb(255,255,128,128), 140,470,SCRIPT_ALIGN_LEFT,0.9);

	int TOTAL = iTownCost + iStoreCost + iShipyardCost + iTavernCost + iBankCost + iTownhallCost + 50000;
	CreateString(true,"ArchitectorCost","Услуги архитектора: 50000", FONT_CAPTION, COLOR_NORMAL, 340,510,SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"TotalCost","Итоговая цена: " + TOTAL, FONT_CAPTION, COLOR_NORMAL, 340,530,SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"CharMoney","Ваше золото: " + sti(PChar.money), FONT_CAPTION, argb(255,255,255,128), 340,550,SCRIPT_ALIGN_LEFT,1.0);

	if(sti(PChar.money) >= TOTAL)
	{
		SetSelectable("ACTR_OK", true);
	}
	else
	{
		SetSelectable("ACTR_OK", false);
	}
}

string GetArchitecturePictureName(int iBuild, string sBuild)
{
	string sPicture = sBuild + "_Type_" + iBuild;

	if(sPicture != "")
	{
		return sPicture;
	}

	return "Store_Type_1";
}

int GetCostForBuildArchitecture(int iBuild, string sBuild)
{
	int iCost = 0;

	string sType = "Type_" + iBuild;
	iCost = sti(PChar.ColonyBuilding.Architecture.(sBuild).Cost.(sType));

	if(sBuild == "Town")
	{
		if(iCost < 50000) { iCost = 50000; }
	}

	return iCost;
}

void CheckArchitectureType(string sType, bool bLeft)
{
	switch(sType)
	{
		case "Town":
			if(bLeft) { iCheckTownType--; }else{ iCheckTownType++ }
			if(iCheckTownType > 3) iCheckTownType = 1;
			if(iCheckTownType < 1) iCheckTownType = 3;

			CreateArchitectureInfo();
			return;
		break;

		case "Store":
			if(bLeft) { iCheckStoreType--; }else{ iCheckStoreType++ }
			if(iCheckStoreType > 4) iCheckStoreType = 1;
			if(iCheckStoreType < 1) iCheckStoreType = 4;

			CreateArchitectureInfo();
			return;
		break;

		case "Shipyard":
			if(bLeft) { iCheckShipyardType--; }else{ iCheckShipyardType++ }
			if(iCheckShipyardType > 3) iCheckShipyardType = 1;
			if(iCheckShipyardType < 1) iCheckShipyardType = 3;

			CreateArchitectureInfo();
			return;
		break;

		case "Tavern":
			if(bLeft) { iCheckTavernType--; }else{ iCheckTavernType++ }
			if(iCheckTavernType > 4) iCheckTavernType = 1;
			if(iCheckTavernType < 1) iCheckTavernType = 4;

			CreateArchitectureInfo();
			return;
		break;

		case "Bank":
			if(bLeft) { iCheckBankType--; }else{ iCheckBankType++ }
			if(iCheckBankType > 2) iCheckBankType = 1;
			if(iCheckBankType < 1) iCheckBankType = 2;

			CreateArchitectureInfo();
			return;
		break;

		case "Townhall":
			if(bLeft) { iCheckTownhallType--; }else{ iCheckTownhallType++ }
			if(iCheckTownhallType > 4) iCheckTownhallType = 1;
			if(iCheckTownhallType < 1) iCheckTownhallType = 4;

			CreateArchitectureInfo();
			return;
		break;
	}

	CreateArchitectureInfo();
}

void ResetArchitectureChanges()
{
	iCheckTownType = 1;
	iCheckStoreType = 1;
	iCheckShipyardType = 1;
	iCheckTavernType = 1;
	iCheckBankType = 1;
	iCheckTownhallType = 1;

	CreateArchitectureInfo();
}

void ArchitectureOk()
{
	int iTownCost = GetCostForBuildArchitecture(iCheckTownType, "Town");
	int iStoreCost = GetCostForBuildArchitecture(iCheckStoreType, "Store");
	int iShipyardCost = GetCostForBuildArchitecture(iCheckShipyardType, "Shipyard");
	int iTavernCost = GetCostForBuildArchitecture(iCheckTavernType, "Tavern");
	int iBankCost = GetCostForBuildArchitecture(iCheckBankType, "Bank");
	int iTownhallCost = GetCostForBuildArchitecture(iCheckTownhallType, "Townhall");
	int TOTAL = iTownCost + iStoreCost + iShipyardCost + iTavernCost + iBankCost + iTownhallCost + 50000;
	AddMoneyToCharacter(PChar, -TOTAL);

	PChar.ColonyBuilding.Architecture.Town = iCheckTownType;
	PChar.ColonyBuilding.Architecture.Store = iCheckStoreType;
	PChar.ColonyBuilding.Architecture.Shipyard = iCheckShipyardType;
	PChar.ColonyBuilding.Architecture.Tavern = iCheckTavernType;
	PChar.ColonyBuilding.Architecture.Bank = iCheckBankType;
	PChar.ColonyBuilding.Architecture.Townhall = iCheckTownhallType;

	PChar.ColonyBuilding.Architecture = true;

	ProcessBreakExit();

	LAi_SetActorType(PChar);
	LAi_QuestDelay("ColonyModification_7", 2.5);
}

////////////////////////////////////////////////////////////////////////////////////////
// check node
////////////////////////////////////////////////////////////////////////////////////////
void CheckNode(bool bCreate, bool bArch)
{
	if(bArch)
	{
		SetNodeUsing("FRAME2", false);
		SetNodeUsing("FRAME2_1", false);
		SetNodeUsing("BORDERS_1", false);
		SetNodeUsing("OK", false);
		SetNodeUsing("CANCEL", false);
		SetNodeUsing("COLONY_NAME_EDIT", false);
		SetNodeUsing("COLONY_NAME", false);
		SetNodeUsing("ENGLAND", false);
		SetNodeUsing("FRANCE", false);
		SetNodeUsing("SPAIN", false);
		SetNodeUsing("HOLLAND", false);
		SetNodeUsing("PIRATE", false);
		SetNodeUsing("SOLDIERS_TYPE_TEXT", false);
		SetNodeUsing("SOLDIERS_TYPE_LEFT", false);
		SetNodeUsing("SOLDIERS_TYPE_RIGHT", false);
		SetNodeUsing("BORDERS", false);
		SetNodeUsing("FRAME1", false);
		SetNodeUsing("BLOCKS_BUTTON", false);
		SetNodeUsing("PLANKS_BUTTON", false);
		SetNodeUsing("MAHOGANY_BUTTON", false);
		SetNodeUsing("EBONY_BUTTON", false);
		SetNodeUsing("SLAVES_BUTTON", false);
		SetNodeUsing("FOOD_BUTTON", false);

		SetNodeUsing("CHECK_TOWN_TYPE", true);
		SetNodeUsing("CHECK_TOWN_TYPE_LEFT", true);
		SetNodeUsing("CHECK_TOWN_TYPE_RIGHT", true);
		SetNodeUsing("CHECK_STORE_PICTURE", true);
		SetNodeUsing("CHECK_STORE_BORDER", true);
		SetNodeUsing("CHECK_STORE_LEFT", true);
		SetNodeUsing("CHECK_STORE_RIGHT", true);
		SetNodeUsing("CHECK_SHIPYARD_PICTURE", true);
		SetNodeUsing("CHECK_SHIPYARD_BORDER", true);
		SetNodeUsing("CHECK_SHIPYARD_LEFT", true);
		SetNodeUsing("CHECK_SHIPYARD_RIGHT", true);
		SetNodeUsing("CHECK_TAVERN_PICTURE", true);
		SetNodeUsing("CHECK_TAVERN_BORDER", true);
		SetNodeUsing("CHECK_TAVERN_LEFT", true);
		SetNodeUsing("CHECK_TAVERN_RIGHT", true);
		SetNodeUsing("CHECK_BANK_PICTURE", true);
		SetNodeUsing("CHECK_BANK_BORDER", true);
		SetNodeUsing("CHECK_BANK_LEFT", true);
		SetNodeUsing("CHECK_BANK_RIGHT", true);
		SetNodeUsing("CHECK_TOWNHALL_PICTURE", true);
		SetNodeUsing("CHECK_TOWNHALL_BORDER", true);
		SetNodeUsing("CHECK_TOWNHALL_LEFT", true);
		SetNodeUsing("CHECK_TOWNHALL_RIGHT", true);
		SetNodeUsing("FRAME3", true);
		SetNodeUsing("FRAME4", true);
		SetNodeUsing("ACTR_OK", true);
		SetNodeUsing("ACTR_RESET", true);
	}
	else
	{
		SetNodeUsing("CHECK_TOWN_TYPE", false);
		SetNodeUsing("CHECK_TOWN_TYPE_LEFT", false);
		SetNodeUsing("CHECK_TOWN_TYPE_RIGHT", false);
		SetNodeUsing("CHECK_STORE_PICTURE", false);
		SetNodeUsing("CHECK_STORE_BORDER", false);
		SetNodeUsing("CHECK_STORE_LEFT", false);
		SetNodeUsing("CHECK_STORE_RIGHT", false);
		SetNodeUsing("CHECK_SHIPYARD_PICTURE", false);
		SetNodeUsing("CHECK_SHIPYARD_BORDER", false);
		SetNodeUsing("CHECK_SHIPYARD_LEFT", false);
		SetNodeUsing("CHECK_SHIPYARD_RIGHT", false);
		SetNodeUsing("CHECK_TAVERN_PICTURE", false);
		SetNodeUsing("CHECK_TAVERN_BORDER", false);
		SetNodeUsing("CHECK_TAVERN_LEFT", false);
		SetNodeUsing("CHECK_TAVERN_RIGHT", false);
		SetNodeUsing("CHECK_BANK_PICTURE", false);
		SetNodeUsing("CHECK_BANK_BORDER", false);
		SetNodeUsing("CHECK_BANK_LEFT", false);
		SetNodeUsing("CHECK_BANK_RIGHT", false);
		SetNodeUsing("CHECK_TOWNHALL_PICTURE", false);
		SetNodeUsing("CHECK_TOWNHALL_BORDER", false);
		SetNodeUsing("CHECK_TOWNHALL_LEFT", false);
		SetNodeUsing("CHECK_TOWNHALL_RIGHT", false);
		SetNodeUsing("FRAME3", false);
		SetNodeUsing("FRAME4", false);
		SetNodeUsing("ACTR_OK", false);
		SetNodeUsing("ACTR_RESET", false);
		GameInterface.strings.TownHeader = "";
		GameInterface.strings.BuildingHeader = "";
		GameInterface.strings.TownCost = "";
		GameInterface.strings.StoreHeader = "";
		GameInterface.strings.StoreCost = "";
		GameInterface.strings.ShipyardHeader = "";
		GameInterface.strings.ShipyardCost = "";
		GameInterface.strings.TavernHeader = "";
		GameInterface.strings.TavernCost = "";
		GameInterface.strings.BankHeader = "";
		GameInterface.strings.BankCost = "";
		GameInterface.strings.TownhallHeader = "";
		GameInterface.strings.TownhallCost = "";
		GameInterface.strings.ArchitectorCost = "";
		GameInterface.strings.TotalCost = "";
		GameInterface.strings.CharMoney = "";

		if(bCreate)
		{
			SetNodeUsing("COLONY_NAME", true);
			SetNodeUsing("BORDERS_1", true);
			SetNodeUsing("OK", true);
			SetNodeUsing("CANCEL", true);
			SetNodeUsing("ENGLAND", true);
			SetNodeUsing("FRANCE", true);
			SetNodeUsing("SPAIN", true);
			SetNodeUsing("HOLLAND", true);
			SetNodeUsing("PIRATE", true);
			SetNodeUsing("SOLDIERS_TYPE_TEXT", true);
			SetNodeUsing("SOLDIERS_TYPE_LEFT", true);
			SetNodeUsing("SOLDIERS_TYPE_RIGHT", true);
			SetNodeUsing("BORDERS", false);
			SetNodeUsing("FRAME1", false);
			SetNodeUsing("BLOCKS_BUTTON", false);
			SetNodeUsing("PLANKS_BUTTON", false);
			SetNodeUsing("MAHOGANY_BUTTON", false);
			SetNodeUsing("EBONY_BUTTON", false);
			SetNodeUsing("SLAVES_BUTTON", false);
			SetNodeUsing("FOOD_BUTTON", false);
		}
		else
		{
			SetNodeUsing("FRAME2", false);
			SetNodeUsing("FRAME2_1", false);
			SetNodeUsing("BORDERS_1", false);
			SetNodeUsing("OK", false);
			SetNodeUsing("CANCEL", false);
			SetNodeUsing("COLONY_NAME_EDIT", false);
			SetNodeUsing("COLONY_NAME", false);
			SetNodeUsing("ENGLAND", false);
			SetNodeUsing("FRANCE", false);
			SetNodeUsing("SPAIN", false);
			SetNodeUsing("HOLLAND", false);
			SetNodeUsing("PIRATE", false);
			SetNodeUsing("SOLDIERS_TYPE_TEXT", false);
			SetNodeUsing("SOLDIERS_TYPE_LEFT", false);
			SetNodeUsing("SOLDIERS_TYPE_RIGHT", false);

			SetNodeUsing("BORDERS", true);
			SetNodeUsing("FRAME1", true);
			SetNodeUsing("BLOCKS_BUTTON", true);
			SetNodeUsing("PLANKS_BUTTON", true);
			SetNodeUsing("MAHOGANY_BUTTON", true);
			SetNodeUsing("EBONY_BUTTON", true);
			SetNodeUsing("SLAVES_BUTTON", true);
			SetNodeUsing("FOOD_BUTTON", true);
		}
	}
}
