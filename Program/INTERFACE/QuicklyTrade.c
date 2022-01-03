int iPlanksCost = 18;
int iSailClothCost = 12;

//bool bPlanks = true;
//bool bSailCloth = true;

void InitInterface(string iniName)
{
	GameInterface.title = "titleQuicklyTrade";

    	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	GameInterface.PLANKS_STRING.str = 0;
	GameInterface.SAILCLOTH_STRING.str = 0;

	SetPlanksInformation();
	SetSailClothInformation();

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("PlanksTemp","PlanksTemp",0);
	SetEventHandler("SailClothTemp","SailClothTemp",0);
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
	DelEventHandler("PlanksTemp","PlanksTemp");
	DelEventHandler("SailClothTemp","SailClothTemp");

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);

	if(PChar.GenerateShipWreck.GoodsChange == true)
	{
		ShipWreckBanditsChangeGoodsEnd();
		PChar.GenerateShipWreck.GoodsChange = false;
	}
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
		case "PLANKS_LEFT":
			if(comName=="activate" || comName=="click")
			{
				ChangeGoodQty("PLANKS", true, false);
			}
		break;

		case "PLANKS_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				ChangeGoodQty("PLANKS", false, false);
			}
		break;

		case "PLANKS_LEFT_ALL":
			if(comName=="activate" || comName=="click")
			{
				ChangeGoodQty("PLANKS", true, true);
			}
		break;

		case "PLANKS_RIGHT_ALL":
			if(comName=="activate" || comName=="click")
			{
				ChangeGoodQty("PLANKS", false, true);
			}
		break;

		case "SAILCLOTH_LEFT":
			if(comName=="activate" || comName=="click")
			{
				ChangeGoodQty("SAILCLOTH", true, false);
			}
		break;

		case "SAILCLOTH_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				ChangeGoodQty("SAILCLOTH", false, false);
			}
		break;

		case "SAILCLOTH_LEFT_ALL":
			if(comName=="activate" || comName=="click")
			{
				ChangeGoodQty("SAILCLOTH", true, true);
			}
		break;

		case "SAILCLOTH_RIGHT_ALL":
			if(comName=="activate" || comName=="click")
			{
				ChangeGoodQty("SAILCLOTH", false, true);
			}
		break;

		case "PLANKS_TRANSFER_RESET":
			if(comName=="activate" || comName=="click")
			{
				Reset("PLANKS");
			}
		break;

		case "SAILCLOTH_TRANSFER_RESET":
			if(comName=="activate" || comName=="click")
			{
				Reset("SAILCLOTH");
			}
		break;

		case "PLANKS_TRANSFER":
			if(comName=="activate" || comName=="click")
			{
				Done("PLANKS");
			}
		break;

		case "SAILCLOTH_TRANSFER":
			if(comName=="activate" || comName=="click")
			{
				Done("SAILCLOTH");
			}
		break;
	}
}

void SetPlanksInformation()
{
	CreateString(true,"PlanksHeader", "Доски", FONT_CAPTION, COLOR_NORMAL, 395,149,SCRIPT_ALIGN_CENTER,1.5);

	CreateImage("PlanksQuantity", "GOODS", "Planks", 490,180,590,280);

	int iPlanksInShip = GetCargoGoods(PChar, GOOD_PLANKS);
	CreateString(true,"PlanksQuantityInShip", iPlanksInShip, FONT_BOLD_NUMBERS, COLOR_NORMAL, 505,280,SCRIPT_ALIGN_LEFT,1.0);

	SetFormatedText("PLANKS_GOLD_TEXT", "0");
}

void SetSailClothInformation()
{
	// CreateImage("SailClothHeader", "MAIN_ICONS", "skillborder", 204,320,596,352);
	CreateString(true,"SailClothHeader", "Парусина", FONT_CAPTION, COLOR_NORMAL, 395,314,SCRIPT_ALIGN_CENTER,1.5);

	CreateImage("SailClothQuantity", "GOODS", "SailCloth", 490,350,590,450);

	int iSailClothInShip = GetCargoGoods(PChar, GOOD_SAILCLOTH);
	CreateString(true,"SailClothQuantityInShip", iSailClothInShip, FONT_BOLD_NUMBERS, COLOR_NORMAL, 505,455,SCRIPT_ALIGN_LEFT,1.0);

	SetFormatedText("SAILCLOTH_GOLD_TEXT", "0");
}

void PlanksInformationUptade()
{
	int iQty = sti(GameInterface.PLANKS_STRING.str);
	int iMoney = iQty * iPlanksCost;

	SetFormatedText("PLANKS_GOLD_TEXT", "" + iMoney);
}


void SailClothInformationUptade()
{
	int iQty = sti(GameInterface.SAILCLOTH_STRING.str);
	int iMoney = iQty * iSailClothCost;

	SetFormatedText("SAILCLOTH_GOLD_TEXT", "" + iMoney);
}

void PlanksTemp()
{
	int iMax = sti(PChar.GenerateShipWreck.MaxGoods);
	int iOnShip = GetCargoGoods(PChar, GOOD_PLANKS);

	if(sti(GameInterface.PLANKS_STRING.str) <= 0)
	{
		GameInterface.PLANKS_STRING.str = 0;
	}

	if(sti(GameInterface.PLANKS_STRING.str) > iOnShip)
	{
		GameInterface.PLANKS_STRING.str = iOnShip;
	}

	if(sti(GameInterface.PLANKS_STRING.str) > iMax)
	{
		GameInterface.PLANKS_STRING.str = iMax;
	}

	PlanksInformationUptade();
}

void SailClothTemp()
{
	int iMax = sti(PChar.GenerateShipWreck.MaxGoods) * 2;
	int iOnShip = GetCargoGoods(PChar, GOOD_PLANKS);

	if(sti(GameInterface.SAILCLOTH_STRING.str) <= 0)
	{
		GameInterface.SAILCLOTH_STRING.str = 0;
	}

	if(sti(GameInterface.SAILCLOTH_STRING.str) > iOnShip)
	{
		GameInterface.SAILCLOTH_STRING.str = iOnShip;
	}

	if(sti(GameInterface.SAILCLOTH_STRING.str) > iMax)
	{
		GameInterface.SAILCLOTH_STRING.str = iMax;
	}

	SailClothInformationUptade();
}

void Reset(string sGood)
{
	string sString = sGood + "_STRING";
	GameInterface.(sString).str = 0;

	PlanksInformationUptade();
	SailClothInformationUptade();
}

void ChangeGoodQty(string sGood, bool bLeft, bool bAll)
{
	string sString = sGood + "_STRING";
	int iMax = sti(PChar.GenerateShipWreck.MaxGoods);

	int iGood = 0;

	if(sGood == "SAILCLOTH")
	{
		iMax *= 2;
		iGood = GOOD_SAILCLOTH;
	}
	else
	{
		iGood = GOOD_PLANKS;
	}

	int iGoodQty = GetCargoGoods(PChar, iGood);

	if(bLeft)
	{
		if(bAll)
		{
			GameInterface.(sString).str = 0;
		}
		else
		{
			GameInterface.(sString).str = sti(GameInterface.(sString).str) - 10;
		}
	}
	else
	{
		if(bAll)
		{
			GameInterface.(sString).str = iGoodQty;
		}
		else
		{
			GameInterface.(sString).str = sti(GameInterface.(sString).str) + 10;
		}
	}

	if(sti(GameInterface.(sString).str) <= 0)
	{
		GameInterface.(sString).str = 0;
	}

	if(sti(GameInterface.(sString).str) > iGoodQty)
	{
		GameInterface.(sString).str = iGoodQty;
	}

	if(sti(GameInterface.(sString).str) > iMax)
	{
		GameInterface.(sString).str = iMax;
	}

	PlanksInformationUptade();
	SailClothInformationUptade();
}

void Done(string sGood)
{
	string sString = sGood + "_STRING";

	int iQty = sti(GameInterface.(sString).str);
	int iCost = 0;
	int iGood = 0;

	if(sGood == "PLANKS")
	{
		iCost = iPlanksCost;
		iGood = GOOD_PLANKS;

		PChar.GenerateShipWreck.MaxGoods.Planks = 1;
		SetSelectable("PLANKS_TRANSFER", false);
	}
	else
	{
		iCost = iSailClothCost;
		iGood = GOOD_SAILCLOTH;

		PChar.GenerateShipWreck.MaxGoods.SailCloth = 1;
		SetSelectable("SAILCLOTH_TRANSFER", false);
	}

	Reset(sGood);

	int iMoney = iQty * iCost;

	RemoveCharacterGoodsSelf(PChar, iGood, iQty);
	AddMoneyToCharacter(PChar, iMoney);

	SetPlanksInformation();
	SetSailClothInformation();
}
