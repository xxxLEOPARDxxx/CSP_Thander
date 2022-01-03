string totalInfo;
int idLngFile = -1;
int iMoved = 0;

void InitInterface(string iniName)
{
    	GameInterface.title = "titleMines";

    	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	PChar.Mines.GuardiansCost = 0;
	PChar.Mines.Temp.GoldQuantity = 0;
	PChar.Mines.Temp.SilverQuantity = 0;
	PChar.Mines.Temp.IronQuantity = 0;
	PChar.Mines.Temp.GuardiansQuantity = 0;
	PChar.Mines.Temp.SlavesQuantity = 0;
	PChar.Mines.Temp.FoodQuantity = 0;
	PChar.Mines.Temp.MedicamentQuantity = 0;

	MinesInfo();

	//SetFormatedText("INFO_TEXT",totalInfo);
	//SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",5);

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);
	SetEventHandler("GoldTempUptade","GoldTempUptade",0);
	SetEventHandler("SilverTempUptade","SilverTempUptade",0);
	SetEventHandler("IronTempUptade","IronTempUptade",0);
	SetEventHandler("FoodTempUptade","FoodTempUptade",0);
	SetEventHandler("MedicamentTempUptade","MedicamentTempUptade",0);
	SetEventHandler("SlavesTempUptade","SlavesTempUptade",0);
	SetEventHandler("GuardiansTempUptade","GuardiansTempUptade",0);
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
	DelEventHandler("GoldTempUptade","GoldTempUptade");
	DelEventHandler("SilverTempUptade","SilverTempUptade");
	DelEventHandler("IronTempUptade","IronTempUptade");
	DelEventHandler("FoodTempUptade","FoodTempUptade");
	DelEventHandler("MedicamentTempUptade","MedicamentTempUptade");
	DelEventHandler("SlavesTempUptade","SlavesTempUptade");
	DelEventHandler("GuardiansTempUptade","GuardiansTempUptade");

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
		case "GOLDLEFT":
			if(comName=="activate" || comName=="click")
			{
				GoldMovedToCharacter(false);
			}
		break;

		case "GOLDRIGHT":
			if(comName=="activate" || comName=="click")
			{
				GoldMovedToCharacter(true);
			}
		break;

		case "BUTTON_GIVEGOLD":
			if(comName=="activate" || comName=="click")
			{
				AddGoldToCharacter(sti(PChar.Mines.Temp.GoldQuantity));
			}
		break;


		case "SILVERLEFT":
			if(comName=="activate" || comName=="click")
			{
				SilverMovedToCharacter(false);
			}
		break;

		case "SILVERRIGHT":
			if(comName=="activate" || comName=="click")
			{
				SilverMovedToCharacter(true);
			}
		break;

		case "BUTTON_GIVESILVER":
			if(comName=="activate" || comName=="click")
			{
				AddSilverToCharacter(sti(PChar.Mines.Temp.SilverQuantity));
			}
		break;


		case "IRONLEFT":
			if(comName=="activate" || comName=="click")
			{
				IronMovedToCharacter(false);
			}
		break;

		case "IRONRIGHT":
			if(comName=="activate" || comName=="click")
			{
				IronMovedToCharacter(true);
			}
		break;

		case "BUTTON_GIVEIRON":
			if(comName=="activate" || comName=="click")
			{
				AddIronToCharacter(sti(PChar.Mines.Temp.IronQuantity));
			}
		break;

		case "GUARDIANSLEFT":
			if(comName=="activate" || comName=="click")
			{
				ChangeSoldiers(false, false);
			}
		break;

		case "GUARDIANSRIGHT":
			if(comName=="activate" || comName=="click")
			{
				ChangeSoldiers(true, false);
			}
		break;

		case "GUARDIANS_ADD":
			if(comName=="activate" || comName=="click")
			{
				AddGuardians();
			}
		break;

		case "GUARDIANS_SBROS":
			if(comName=="activate" || comName=="click")
			{
				GuardiansSbros();
			}
		break;

		case "SLAVESLEFT":
			if(comName=="activate" || comName=="click")
			{
				SelectSlavesQuantity(false);
			}
		break;

		case "SLAVESRIGHT":
			if(comName=="activate" || comName=="click")
			{
				SelectSlavesQuantity(true);
			}
		break;

		case "SLAVES_ADD":
			if(comName=="activate" || comName=="click")
			{
				TakeSlavesToMines(sti(PChar.Mines.Temp.SlavesQuantity));
			}
		break;

		case "SLAVES_SBROS":
			if(comName=="activate" || comName=="click")
			{
				SlavesSbros();
			}
		break;

		case "FOODLEFT":
			if(comName=="activate" || comName=="click")
			{
				SelectFoodQuantity(false);
			}
		break;

		case "FOODRIGHT":
			if(comName=="activate" || comName=="click")
			{
				SelectFoodQuantity(true);
			}
		break;

		case "FOOD_ADD":
			if(comName=="activate" || comName=="click")
			{
				TakeFoodToMines(sti(PChar.Mines.Temp.FoodQuantity));
			}
		break;

		case "FOOD_SBROS":
			if(comName=="activate" || comName=="click")
			{
				FoodSbros();
			}
		break;

		case "FOOD_LEFT_ALL":
			if(comName=="activate" || comName=="click")
			{
				SelectAll("Food", false);
			}
		break;

		case "FOOD_RIGHT_ALL":
			if(comName=="activate" || comName=="click")
			{
				SelectAll("Food", true);
			}
		break;


		case "MEDICAMENTLEFT":
			if(comName=="activate" || comName=="click")
			{
				SelectMedicamentQuantity(false);
			}
		break;

		case "MEDICAMENTRIGHT":
			if(comName=="activate" || comName=="click")
			{
				SelectMedicamentQuantity(true);
			}
		break;

		case "MEDICAMENT_ADD":
			if(comName=="activate" || comName=="click")
			{
				TakeMedicamentToMines(sti(PChar.Mines.Temp.MedicamentQuantity));
			}
		break;

		case "MEDICAMENT_SBROS":
			if(comName=="activate" || comName=="click")
			{
				MedicamentSbros();
			}
		break;

		case "MEDICAMENT_LEFT_ALL":
			if(comName=="activate" || comName=="click")
			{
				SelectAll("Medicament", false);
			}
		break;

		case "MEDICAMENT_RIGHT_ALL":
			if(comName=="activate" || comName=="click")
			{
				SelectAll("Medicament", true);
			}
		break;

		case "SLAVES_LEFT_ALL":
			if(comName=="activate" || comName=="click")
			{
				SelectAll("Slaves", false);
			}
		break;

		case "SLAVES_RIGHT_ALL":
			if(comName=="activate" || comName=="click")
			{
				SelectAll("Slaves", true);
			}
		break;

		case "GUARDIANS_LEFT_ALL":
			if(comName=="activate" || comName=="click")
			{
				ChangeSoldiers(false, true);
			}
		break;

		case "GUARDIANS_RIGHT_ALL":
			if(comName=="activate" || comName=="click")
			{
				ChangeSoldiers(true, true);
			}
		break;

		case "GOLD_LEFT_ALL":
			if(comName=="activate" || comName=="click")
			{
				SelectAll("Gold", false);
			}
		break;

		case "GOLD_RIGHT_ALL":
			if(comName=="activate" || comName=="click")
			{
				SelectAll("Gold", true);
			}
		break;

		case "SILVER_LEFT_ALL":
			if(comName=="activate" || comName=="click")
			{
				SelectAll("Silver", false);
			}
		break;

		case "SILVER_RIGHT_ALL":
			if(comName=="activate" || comName=="click")
			{
				SelectAll("Silver", true);
			}
		break;

		case "IRON_LEFT_ALL":
			if(comName=="activate" || comName=="click")
			{
				SelectAll("Iron", false);
			}
		break;

		case "IRON_RIGHT_ALL":
			if(comName=="activate" || comName=="click")
			{
				SelectAll("Iron", true);
			}
		break;
	}
}

void SelectAll(string sType, bool bAdd)
{
	ref PChar = GetMainCharacter();

	switch(sType)
	{
		case "Guardians":
			if(!bAdd)
			{
				PChar.Mines.Temp.GuardiansQuantity = 0;
				PChar.Mines.GuardiansCost = 0;
			}
			else
			{
				int iGuardiansQuantity = sti(PChar.Mines.GuardiansQuantity);
				int iGuardiansMaxQuantity = sti(PChar.Mines.MaxGuardiansQuantity);
				int iGuardiansHireQuantity = sti(PChar.Mines.HireGuardiansQuantity);
				PChar.Mines.Temp.GuardiansQuantity = (iGuardiansMaxQuantity - iGuardiansQuantity);

				if(sti(PChar.Mines.Temp.GuardiansQuantity) > iGuardiansHireQuantity)
				{
					PChar.Mines.Temp.GuardiansQuantity = iGuardiansHireQuantity;
				}
			}
		break;

		case "Slaves":
			if(!bAdd)
			{
				PChar.Mines.Temp.SlavesQuantity = 0;
			}
			else
			{
				int iSlavesHoldQuantity = GetCargoGoods(PChar, GOOD_SLAVES);
				int iSlavesQuantity = sti(PChar.Mines.SlavesQuantity);
				int iSlavesMaxQuantity = sti(PChar.Mines.MaxSlavesQuantity);

				PChar.Mines.Temp.SlavesQuantity = (iSlavesMaxQuantity - iSlavesQuantity);

				if(sti(PChar.Mines.Temp.SlavesQuantity) > iSlavesHoldQuantity)
				{
					PChar.Mines.Temp.SlavesQuantity = iSlavesHoldQuantity;
				}
			}
		break;

		case "Food":
			if(!bAdd)
			{
				PChar.Mines.Temp.FoodQuantity = 0;
			}
			else
			{
				int iFoodMaxStep = sti(PChar.Mines.FoodQuantity.Max) - sti(PChar.Mines.FoodQuantity);
				int iFoodHoldQuantity = GetCargoGoods(PChar, GOOD_FOOD);

				PChar.Mines.Temp.FoodQuantity = iFoodMaxStep;

				if(sti(PChar.Mines.Temp.FoodQuantity) > iFoodHoldQuantity)
				{
					PChar.Mines.Temp.FoodQuantity = iFoodHoldQuantity;
				}
			}
		break;

		case "Medicament":
			if(!bAdd)
			{
				PChar.Mines.Temp.MedicamentQuantity = 0;
			}
			else
			{
				int iMedicamentMaxStep = sti(PChar.Mines.MedicamentQuantity.Max) - sti(PChar.Mines.MedicamentQuantity);
				int iMedicamentHoldQuantity = GetCargoGoods(PChar, GOOD_MEDICAMENT);

				PChar.Mines.Temp.MedicamentQuantity = iMedicamentMaxStep;
				if(sti(PChar.Mines.Temp.MedicamentQuantity) > iMedicamentHoldQuantity)
				{
					PChar.Mines.Temp.MedicamentQuantity = iMedicamentHoldQuantity;
				}
			}
		break;

		case "Gold":
			if(!bAdd)
			{
				PChar.Mines.Temp.GoldQuantity = 0;
			}
			else
			{
				PChar.Mines.Temp.GoldQuantity = sti(PChar.Mines.GoldQuantity);
				int iCargoGold = GetGoodWeightByType(GOOD_GOLD, sti(PChar.Mines.GoldQuantity));

				if(GetCargoFreeSpace(PChar) < 0)
				{
					PChar.Mines.Temp.GoldQuantity = 0;
				}
				else
				{
					if(iCargoGold > GetCargoFreeSpace(PChar))
					{
						PChar.Mines.Temp.GoldQuantity = GetCharacterFreeSpace(PChar, GOOD_GOLD);
					}
				}
			}
		break;

		case "Silver":
			if(!bAdd)
			{
				PChar.Mines.Temp.SilverQuantity = 0;
			}
			else
			{
				PChar.Mines.Temp.SilverQuantity = sti(PChar.Mines.SilverQuantity);

				int iCargoSilver = GetGoodWeightByType(GOOD_SILVER, sti(PChar.Mines.SilverQuantity));

				if(GetCargoFreeSpace(PChar) < 0)
				{
					PChar.Mines.Temp.SilverQuantity = 0;
				}
				else
				{
					if(iCargoSilver > GetCargoFreeSpace(PChar))
					{
						PChar.Mines.Temp.SilverQuantity = GetCharacterFreeSpace(PChar, GOOD_SILVER);
					}
				}
			}
		break;

		case "Iron":
			if(!bAdd)
			{
				PChar.Mines.Temp.IronQuantity = 0;
			}
			else
			{
				PChar.Mines.Temp.IronQuantity = sti(PChar.Mines.IronQuantity);
				int iCargoIron = GetGoodWeightByType(GOOD_IRON, sti(PChar.Mines.IronQuantity));

				if(GetCargoFreeSpace(PChar) < 0)
				{
					PChar.Mines.Temp.IronQuantity = 0;
				}
				else
				{
					if(iCargoIron > GetCargoFreeSpace(PChar))
					{
						PChar.Mines.Temp.IronQuantity = GetCharacterFreeSpace(PChar, GOOD_IRON);
					}
				}
			}
		break;
	}

	UptadeFields(sType);
	MinesInfo();
}

void GuardiansTempUptade()
{
	int iSoldiersInShip = GetCrewQuantity(PChar);
	if(sti(GameInterface.GUARDIANS_STRING.str) > iSoldiersInShip)
	{
		GameInterface.GUARDIANS_STRING.str = iSoldiersInShip;
	}

	int iFree = sti(PChar.Mines.MaxGuardiansQuantity) - sti(PChar.Mines.GuardiansQuantity);
	if(sti(GameInterface.GUARDIANS_STRING.str) > iFree)
	{
		GameInterface.GUARDIANS_STRING.str = iFree;
	}

	PChar.Mines.Temp.GuardiansQuantity = sti(GameInterface.GUARDIANS_STRING.str);

	UptadeFields("Guardians");
	MinesInfo();
}

void AddGuardians()
{
	int iQuantity = sti(GameInterface.GUARDIANS_STRING.str);

	PChar.Mines.GuardiansQuantity = sti(PChar.Mines.GuardiansQuantity) + iQuantity;
	RemoveCharacterCrew(PChar, iQuantity);

	UptadeFields("Guardians");
	GuardiansSbros();
}

void SlavesTempUptade()
{
	int iHoldQuantity = GetCargoGoods(PChar, GOOD_SLAVES);
	int iFree = sti(PChar.Mines.MaxSlavesQuantity) - sti(PChar.Mines.SlavesQuantity);

	PChar.Mines.Temp.SlavesQuantity = sti(GameInterface.SLAVES_STRING.str);

	if(sti(PChar.Mines.Temp.SlavesQuantity) > iHoldQuantity)
	{
		PChar.Mines.Temp.SlavesQuantity = iHoldQuantity;
	}

	if(sti(PChar.Mines.Temp.SlavesQuantity) > iFree)
	{
		PChar.Mines.Temp.SlavesQuantity = iFree;
	}

	UptadeFields("Slaves");
	MinesInfo();
}

void FoodTempUptade()
{
	int iMaxStep = sti(PChar.Mines.FoodQuantity.Max) - sti(PChar.Mines.FoodQuantity);
	int iHoldQuantity = GetCargoGoods(PChar, GOOD_FOOD);

	PChar.Mines.Temp.FoodQuantity = sti(GameInterface.FOOD_STRING.str);

	if(sti(PChar.Mines.Temp.FoodQuantity) > iHoldQuantity)
	{
		PChar.Mines.Temp.FoodQuantity = iHoldQuantity;
	}

	if(sti(PChar.Mines.Temp.FoodQuantity) > iMaxStep)
	{
		PChar.Mines.Temp.FoodQuantity = iMaxStep;
	}

	UptadeFields("Food");
	MinesInfo();
}

void MedicamentTempUptade()
{
	int iMaxStep = sti(PChar.Mines.MedicamentQuantity.Max) - sti(PChar.Mines.MedicamentQuantity);
	int iHoldQuantity = GetCargoGoods(PChar, GOOD_MEDICAMENT);

	PChar.Mines.Temp.MedicamentQuantity = sti(GameInterface.MEDICAMENT_STRING.str);

	if(sti(PChar.Mines.Temp.MedicamentQuantity) > iHoldQuantity)
	{
		PChar.Mines.Temp.MedicamentQuantity = iHoldQuantity;
	}

	if(sti(PChar.Mines.Temp.MedicamentQuantity) > iMaxStep)
	{
		PChar.Mines.Temp.MedicamentQuantity = iMaxStep;
	}

	UptadeFields("Medicament");
	MinesInfo();
}

void GoldTempUptade()
{
	PChar.Mines.Temp.GoldQuantity = sti(GameInterface.GOLD_STRING.str);
	if(sti(PChar.Mines.Temp.GoldQuantity) > sti(PChar.Mines.GoldQuantity))
	{
		PChar.Mines.Temp.GoldQuantity = sti(PChar.Mines.GoldQuantity);
	}

	int iCargo = GetGoodWeightByType(GOOD_GOLD, sti(PChar.Mines.Temp.GoldQuantity));

	if(GetCargoFreeSpace(PChar) < 0)
	{
		PChar.Mines.Temp.GoldQuantity = 0;
	}
	else
	{
		if(iCargo > GetCargoFreeSpace(PChar))
		{
			PChar.Mines.Temp.GoldQuantity = GetCharacterFreeSpace(PChar, GOOD_GOLD);
		}
	}

	UptadeFields("Gold");
	MinesInfo();
}

void SilverTempUptade()
{
	PChar.Mines.Temp.SilverQuantity = sti(GameInterface.SILVER_STRING.str);
	if(sti(PChar.Mines.Temp.SilverQuantity) > sti(PChar.Mines.SilverQuantity))
	{
		PChar.Mines.Temp.SilverQuantity = sti(PChar.Mines.SilverQuantity);
	}

	int iCargo = GetGoodWeightByType(GOOD_SILVER, sti(PChar.Mines.Temp.SilverQuantity));

	if(GetCargoFreeSpace(PChar) < 0)
	{
		PChar.Mines.Temp.SilverQuantity = 0;
	}
	else
	{
		if(iCargo > GetCargoFreeSpace(PChar))
		{
			PChar.Mines.Temp.SilverQuantity = GetCharacterFreeSpace(PChar, GOOD_SILVER);
		}
	}

	UptadeFields("Silver");
	MinesInfo();
}

void IronTempUptade()
{
	PChar.Mines.Temp.IronQuantity = sti(GameInterface.IRON_STRING.str);
	if(sti(PChar.Mines.Temp.IronQuantity) > sti(PChar.Mines.IronQuantity))
	{
		PChar.Mines.Temp.IronQuantity = sti(PChar.Mines.IronQuantity);
	}

	int iCargo = GetGoodWeightByType(GOOD_IRON, sti(PChar.Mines.Temp.IronQuantity));

	if(GetCargoFreeSpace(PChar) < 0)
	{
		PChar.Mines.Temp.IronQuantity = 0;
	}
	else
	{
		if(iCargo > GetCargoFreeSpace(PChar))
		{
			PChar.Mines.Temp.IronQuantity = GetCharacterFreeSpace(PChar, GOOD_IRON);
		}
	}

	UptadeFields("Iron");
	MinesInfo();
}

void SelectFoodQuantity(bool bAdd)
{
	int iMaxStep = sti(PChar.Mines.FoodQuantity.Max) - sti(PChar.Mines.FoodQuantity);
	int iCargo = GetCargoGoods(PChar, GOOD_FOOD);

	if(bAdd)
	{
		PChar.Mines.Temp.FoodQuantity = sti(PChar.Mines.Temp.FoodQuantity) + 100;
	}
	else
	{
		PChar.Mines.Temp.FoodQuantity = sti(PChar.Mines.Temp.FoodQuantity) - 100;
	}

	if(sti(PChar.Mines.Temp.FoodQuantity) > iCargo)
	{
		PChar.Mines.Temp.FoodQuantity = iCargo;
	}
	if(sti(PChar.Mines.Temp.FoodQuantity) > iMaxStep)
	{
		PChar.Mines.Temp.FoodQuantity = iMaxStep;
	}
	if(sti(PChar.Mines.Temp.FoodQuantity) <= 0)
	{
		PChar.Mines.Temp.FoodQuantity = 0;
	}

	UptadeFields("Food");
	MinesInfo();
}

void SelectMedicamentQuantity(bool bAdd)
{
	int iMaxStep = sti(PChar.Mines.MedicamentQuantity.Max) - sti(PChar.Mines.MedicamentQuantity);
	int iCargo = GetCargoGoods(PChar, GOOD_MEDICAMENT);

	if(bAdd)
	{
		PChar.Mines.Temp.MedicamentQuantity = sti(PChar.Mines.Temp.MedicamentQuantity) + 100;
	}
	else
	{
		PChar.Mines.Temp.MedicamentQuantity = sti(PChar.Mines.Temp.MedicamentQuantity) - 100;
	}

	if(sti(PChar.Mines.Temp.MedicamentQuantity) > iCargo)
	{
		PChar.Mines.Temp.MedicamentQuantity = iCargo;
	}
	if(sti(PChar.Mines.Temp.MedicamentQuantity) > iMaxStep)
	{
		PChar.Mines.Temp.MedicamentQuantity = iMaxStep;
	}
	if(sti(PChar.Mines.Temp.MedicamentQuantity) <= 0)
	{
		PChar.Mines.Temp.MedicamentQuantity = 0;
	}

	UptadeFields("Medicament");
	MinesInfo();
}

void SelectSlavesQuantity(bool bAdd)
{
	int iMaxStep = sti(PChar.Mines.MaxSlavesQuantity) - sti(PChar.Mines.SlavesQuantity) - 1;
	int iCargo = GetCargoGoods(PChar, GOOD_SLAVES);

	if(bAdd)
	{
		PChar.Mines.Temp.SlavesQuantity = sti(PChar.Mines.Temp.SlavesQuantity) + 1;
	}
	else
	{
		PChar.Mines.Temp.SlavesQuantity = sti(PChar.Mines.Temp.SlavesQuantity) - 1;
	}

	if(sti(PChar.Mines.Temp.SlavesQuantity) > iCargo)
	{
		PChar.Mines.Temp.SlavesQuantity = iCargo;
	}
	if(sti(PChar.Mines.Temp.SlavesQuantity) > iMaxStep)
	{
		PChar.Mines.Temp.SlavesQuantity = iMaxStep;
	}
	if(sti(PChar.Mines.Temp.SlavesQuantity) <= 0)
	{
		PChar.Mines.Temp.SlavesQuantity = 0;
	}

	UptadeFields("Slaves");
	MinesInfo();
}

void TakeFoodToMines(int iQuantity)
{
	ref PChar = GetMainCharacter();
	PChar.Mines.FoodQuantity = sti(PChar.Mines.FoodQuantity) + iQuantity;
	RemoveCharacterGoods(PChar, GOOD_FOOD, iQuantity);
	PChar.Mines.Temp.FoodQuantity = 0;
	MinesInfo();
}

void TakeMedicamentToMines(int iQuantity)
{
	ref PChar = GetMainCharacter();
	PChar.Mines.MedicamentQuantity = sti(PChar.Mines.MedicamentQuantity) + iQuantity;
	RemoveCharacterGoods(PChar, GOOD_MEDICAMENT, iQuantity);
	PChar.Mines.Temp.MedicamentQuantity = 0;
	MinesInfo();
}

void TakeSlavesToMines(int iQuantity)
{
	ref PChar = GetMainCharacter();
	PChar.Mines.SlavesQuantity = sti(PChar.Mines.SlavesQuantity) + iQuantity;
	RemoveCharacterGoods(PChar, GOOD_SLAVES, iQuantity);
	PChar.Mines.Temp.SlavesQuantity = 0;
	MinesInfo();
}

void FoodSbros()
{
	ref PChar = GetMainCharacter();
	PChar.Mines.Temp.FoodQuantity = 0;
	MinesInfo();
}

void MedicamentSbros()
{
	ref PChar = GetMainCharacter();
	PChar.Mines.Temp.MedicamentQuantity = 0;
	MinesInfo();
}

void SlavesSbros()
{
	ref PChar = GetMainCharacter();
	PChar.Mines.Temp.SlavesQuantity = 0;
	MinesInfo();
}

void GoldMovedToCharacter(bool bAdd)
{
	int iGold = sti(PChar.Mines.GoldQuantity);
	if(bAdd)
	{
		PChar.Mines.Temp.GoldQuantity = sti(PChar.Mines.Temp.GoldQuantity) + 10;
	}
	else
	{
		PChar.Mines.Temp.GoldQuantity = sti(PChar.Mines.Temp.GoldQuantity) - 10;
	}

	if(sti(PChar.Mines.Temp.GoldQuantity) > iGold)
	{
		PChar.Mines.Temp.GoldQuantity = iGold;
	}

	int iCargo = GetGoodWeightByType(GOOD_GOLD, sti(PChar.Mines.Temp.GoldQuantity));

	if(iCargo > GetCargoFreeSpace(PChar))
	{
		PChar.Mines.Temp.GoldQuantity = GetCharacterFreeSpace(PChar, GOOD_GOLD);
	}

	if(GetCargoFreeSpace(PChar) < 0)
	{
		PChar.Mines.Temp.GoldQuantity = 0;
	}

	if(sti(PChar.Mines.Temp.GoldQuantity) <= 0)
	{
		PChar.Mines.Temp.GoldQuantity = 0;
	}

	if(sti(PChar.Mines.Temp.GoldQuantity) <= 0)
	{
		SetSelectable("BUTTON_GIVEGOLD", false);
	}
	else
	{
		SetSelectable("BUTTON_GIVEGOLD", true);
	}

	UptadeFields("Gold");
	MinesInfo();
}

void AddGoldToCharacter(int iGold)
{
	PChar.Mines.Temp.GoldQuantity = 0;
	PChar.Mines.GoldQuantity = sti(PChar.Mines.GoldQuantity) - iGold;
	RemoveCharacterGoods(PChar, GOOD_GOLD, -iGold);
	MinesInfo();
}

void SilverMovedToCharacter(bool bAdd)
{
	int iSilver = sti(PChar.Mines.SilverQuantity);
	if(bAdd)
	{
		PChar.Mines.Temp.SilverQuantity = sti(PChar.Mines.Temp.SilverQuantity) + 10;
	}
	else
	{
		PChar.Mines.Temp.SilverQuantity = sti(PChar.Mines.Temp.SilverQuantity) - 10;
	}

	if(sti(PChar.Mines.Temp.SilverQuantity) > iSilver)
	{
		PChar.Mines.Temp.SilverQuantity = iSilver;
	}

	int iCargo = GetGoodWeightByType(GOOD_SILVER, sti(PChar.Mines.Temp.SilverQuantity));

	if(iCargo > GetCargoFreeSpace(PChar))
	{
		PChar.Mines.Temp.SilverQuantity = GetCharacterFreeSpace(PChar, GOOD_SILVER);
	}

	if(GetCargoFreeSpace(PChar) < 0)
	{
		PChar.Mines.Temp.SilverQuantity = 0;
	}

	if(sti(PChar.Mines.Temp.SilverQuantity) <= 0)
	{
		PChar.Mines.Temp.SilverQuantity = 0;
	}

	if(sti(PChar.Mines.Temp.SilverQuantity) <= 0)
	{
		SetSelectable("BUTTON_GIVESILVER", false);
	}
	else
	{
		SetSelectable("BUTTON_GIVESILVER", true);
	}

	UptadeFields("Silver");
	MinesInfo();
}

void AddSilverToCharacter(int iSilver)
{
	PChar.Mines.Temp.SilverQuantity = 0;
	PChar.Mines.SilverQuantity = sti(PChar.Mines.SilverQuantity) - iSilver;
	RemoveCharacterGoods(PChar, GOOD_SILVER, -iSilver);
	MinesInfo();
}

void IronMovedToCharacter(bool bAdd)
{
	int iIron = sti(PChar.Mines.IronQuantity);
	if(bAdd)
	{
		PChar.Mines.Temp.IronQuantity = sti(PChar.Mines.Temp.IronQuantity) + 10;
	}
	else
	{
		PChar.Mines.Temp.IronQuantity = sti(PChar.Mines.Temp.IronQuantity) - 10;
	}

	if(sti(PChar.Mines.Temp.IronQuantity) > iIron)
	{
		PChar.Mines.Temp.IronQuantity = iIron;
	}

	int iCargo = GetGoodWeightByType(GOOD_IRON, sti(PChar.Mines.Temp.IronQuantity));

	if(iCargo > GetCargoFreeSpace(PChar))
	{
		PChar.Mines.Temp.IronQuantity = GetCharacterFreeSpace(PChar, GOOD_IRON);
	}

	if(GetCargoFreeSpace(PChar) < 0)
	{
		PChar.Mines.Temp.IronQuantity = 0;
	}

	if(sti(PChar.Mines.Temp.IronQuantity) <= 0)
	{
		PChar.Mines.Temp.IronQuantity = 0;
	}

	if(sti(PChar.Mines.Temp.IronQuantity) <= 0)
	{
		SetSelectable("BUTTON_GIVEIRON", false);
	}
	else
	{
		SetSelectable("BUTTON_GIVEIRON", true);
	}

	UptadeFields("Iron");
	MinesInfo();
}

void AddIronToCharacter(int iIron)
{
	PChar.Mines.Temp.IronQuantity = 0;
	PChar.Mines.IronQuantity = sti(PChar.Mines.IronQuantity) - iIron;
	RemoveCharacterGoods(PChar, GOOD_IRON, -iIron);
	MinesInfo();
}

//-----------------------------------------------------------------

void ChangeSoldiers(bool bAdd, bool bAll)
{
	int iCrewInShip = GetCrewQuantity(PChar);
	int iFree = sti(PChar.Mines.MaxGuardiansQuantity) - sti(PChar.Mines.GuardiansQuantity);

	if(bAdd)
	{
		if(bAll)
		{
			GameInterface.GUARDIANS_STRING.str = iCrewInShip;
		}
		else
		{
			GameInterface.GUARDIANS_STRING.str = sti(GameInterface.GUARDIANS_STRING.str) + 10;
		}
	}
	else
	{
		if(bAll)
		{
			GameInterface.GUARDIANS_STRING.str = 0;
		}
		else
		{
			GameInterface.GUARDIANS_STRING.str = sti(GameInterface.GUARDIANS_STRING.str) - 10;
		}
	}

	if(sti(GameInterface.GUARDIANS_STRING.str) > iCrewInShip)
	{
		GameInterface.GUARDIANS_STRING.str = iCrewInShip;
	}

	if(sti(GameInterface.GUARDIANS_STRING.str) > iFree)
	{
		GameInterface.GUARDIANS_STRING.str = iFree;
	}

	if(sti(GameInterface.GUARDIANS_STRING.str) <= 0)
	{
		GameInterface.GUARDIANS_STRING.str = 0;
	}

	PChar.Mines.Temp.GuardiansQuantity = sti(GameInterface.GUARDIANS_STRING.str);

	MinesInfo();
}

//-----------------------------------------------------------------


void GuardiansSbros()
{
	ref PChar = GetMainCharacter();
	PChar.Mines.GuardiansCost = 0;
	PChar.Mines.Temp.GuardiansQuantity = 0;
	MinesInfo();
}

void MinesInfo()
{
	ClearMinesInfo();

	int iMoneyColor =  argb(255,255,255,128);

	if(sti(PChar.Mines.Temp.GuardiansQuantity) <= 0)
	{
		SetSelectable("GUARDIANS_ADD", false);
	}
	else
	{
		SetSelectable("GUARDIANS_ADD", true);
	}

	// HEADERS
	CreateString(true,"GoldMineHeader", XI_ConvertString("GoldMineHeader"), FONT_CAPTION, COLOR_NORMAL, 140,35,SCRIPT_ALIGN_CENTER,1.5);
	CreateString(true,"SilverMineHeader", XI_ConvertString("SilverMineHeader"), FONT_CAPTION, COLOR_NORMAL, 400,35,SCRIPT_ALIGN_CENTER,1.5);
	CreateString(true,"IronMineHeader", XI_ConvertString("IronMineHeader"), FONT_CAPTION, COLOR_NORMAL, 665,35,SCRIPT_ALIGN_CENTER,1.5);

	int iGoldQuantity = sti(PChar.Mines.GoldQuantity);
	int iSilverQuantity = sti(PChar.Mines.SilverQuantity);
	int iIronQuantity = sti(PChar.Mines.IronQuantity);
	int iGuardiansQuantity = sti(PChar.Mines.GuardiansQuantity);
	int iSailorsInShip = GetCrewQuantity(PChar);
	int iMaxGuardiansQuantity = sti(PChar.Mines.MaxGuardiansQuantity);
	int iGuardiansCost = sti(PChar.Mines.GuardiansCost);
	int iSlavesQuantity = sti(PChar.Mines.SlavesQuantity);
	int iMaxSlavesQuantity = sti(PChar.Mines.MaxSlavesQuantity);
	int iFoodQuantity = sti(PChar.Mines.FoodQuantity);
	int iMedicamentQuantity = sti(PChar.Mines.MedicamentQuantity);

	int iGoldTempQuantity = sti(PChar.Mines.Temp.GoldQuantity);
	int iSilverTempQuantity = sti(PChar.Mines.Temp.SilverQuantity);
	int iIronTempQuantity = sti(PChar.Mines.Temp.IronQuantity);
	int iGuardiansTempQuantity = sti(PChar.Mines.Temp.GuardiansQuantity);
	int iSlavesTempQuantity = sti(PChar.Mines.Temp.SlavesQuantity);
	int iFoodTempQuantity = sti(PChar.Mines.Temp.FoodQuantity);
	int iMedicamentTempQuantity = sti(PChar.Mines.Temp.MedicamentQuantity);

	int iMaxGoldQuantity = 2500;
	int iMaxSilverQuantity = 5000;
	int iMaxIronQuantity = 7500;

	int iGoldWeightColor = argb(255,255,128,128);
	int iSilverWeightColor = argb(255,255,128,128);
	int iIronWeightColor = argb(255,255,128,128);

	int iGoldSpaceColor = argb(255,128,255,128);
	int iSilverSpaceColor = argb(255,128,255,128);
	int iIronSpaceColor = argb(255,128,255,128);

	if(iGoldTempQuantity == 0)
	{
		iGoldWeightColor = argb(255,255,255,255);
	}
	if(iSilverTempQuantity == 0)
	{
		iSilverWeightColor = argb(255,255,255,255);
	}
	if(iIronTempQuantity == 0)
	{
		iIronWeightColor = argb(255,255,255,255);
	}

	if(GetCargoFreeSpace(PChar) <= 0)
	{
		iGoldSpaceColor = argb(255,255,128,128);
		iSilverSpaceColor = argb(255,255,128,128);
		iIronSpaceColor = argb(255,255,128,128);
	}

	iMaxGoldQuantity = sti(PChar.Mines.GoldQuantity.Max);
	iMaxSilverQuantity = sti(PChar.Mines.SilverQuantity.Max);
	iMaxIronQuantity = sti(PChar.Mines.IronQuantity.Max);

	// GOLD MINE
	if(PChar.Mines.GoldMine == false || PChar.ColonyBuilding.GoldMine.BuildingTime == true)
	{
		SetNodeUsing("GOLDLEFT", false);
		SetNodeUsing("GOLDRIGHT", false);
		SetNodeUsing("GOLD_STRING", false);
		SetNodeUsing("GOLD_STRING_VIDEO", false);
		SetNodeUsing("GOLD_LEFT_ALL", false);
		SetNodeUsing("GOLD_RIGHT_ALL", false);
		SetNodeUsing("BUTTON_GIVEGOLD", false);
		CreateString(true,"GoldMineNot", "Данный рудник не построен.", FONT_NORMAL, argb(255,255,128,128), 140,227,SCRIPT_ALIGN_CENTER,1.4);

		CreateImage("Gold", "GOODS", "Gold", 30,58,100,128);
		CreateString(true,"GoldInMine", "0/0", FONT_BOLD_NUMBERS, argb(255,255,128,128), 115,85,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("GoldWeight", "ICONS", "weight icon", 45,126,77,158);
		CreateString(true,"GoldWeight", "0", FONT_BOLD_NUMBERS, argb(255,255,128,128), 115,131,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("Gold_ShipCapacity", "ICONS", "ship capacity icon", 47,165,79,197);
		CreateString(true,"Gold_ShipCapacity", GetCargoFreeSpace(PChar) + "/" +  GetCargoMaxSpace(PChar), FONT_BOLD_NUMBERS, argb(255,255,128,128), 115,170,SCRIPT_ALIGN_LEFT,1.0);
	}
	else
	{
		CreateImage("Gold", "GOODS", "Gold", 30,58,100,128);
		CreateString(true,"GoldInMine", iGoldQuantity + "/" + iMaxGoldQuantity, FONT_BOLD_NUMBERS, iMoneyColor, 115,85,SCRIPT_ALIGN_LEFT,1.0);
		GameInterface.GOLD_STRING.str = iGoldTempQuantity;

		CreateImage("GoldWeight", "ICONS", "weight icon", 45,126,77,158);
		int iGoldCargo = GetGoodWeightByType(GOOD_GOLD, iGoldTempQuantity);

		CreateString(true,"GoldWeight", iGoldCargo, FONT_BOLD_NUMBERS, iGoldWeightColor, 115,131,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("Gold_ShipCapacity", "ICONS", "ship capacity icon", 47,165,79,197);
		CreateString(true,"Gold_ShipCapacity", GetCargoFreeSpace(PChar) + "/" +  GetCargoMaxSpace(PChar), FONT_BOLD_NUMBERS, iGoldSpaceColor, 115,170,SCRIPT_ALIGN_LEFT,1.0);

		//CreateImage("GoldToCharacter", "MAIN_ICONS", "skillborder", 100,205,184,237);
		//CreateString(true,"GoldToCharacter", iGoldTempQuantity, FONT_CAPTION, COLOR_NORMAL, 141,204,SCRIPT_ALIGN_CENTER,1.5);
	}

	// SILVER MINE
	if(PChar.Mines.SilverMine == false || PChar.ColonyBuilding.SilverMine.BuildingTime == true)
	{
		SetNodeUsing("SILVERLEFT", false);
		SetNodeUsing("SILVERRIGHT", false);
		SetNodeUsing("SILVER_STRING", false);
		SetNodeUsing("SILVER_STRING_VIDEO", false);
		SetNodeUsing("SILVER_LEFT_ALL", false);
		SetNodeUsing("SILVER_RIGHT_ALL", false);
		SetNodeUsing("BUTTON_GIVESILVER", false);
		CreateString(true,"SilverMineNot", "Данный рудник не построен.", FONT_NORMAL, argb(255,255,128,128), 400,230,SCRIPT_ALIGN_CENTER,1.0);

		CreateImage("Silver", "GOODS", "Silver", 285,58,355,128);
		CreateString(true,"SilverInMine", "0/0", FONT_BOLD_NUMBERS, argb(255,255,128,128), 370,85,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("SilverWeight", "ICONS", "weight icon", 303,126,335,158);
		CreateString(true,"SilverWeight", "0", FONT_BOLD_NUMBERS, argb(255,255,128,128), 370,131,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("Silver_ShipCapacity", "ICONS", "ship capacity icon", 304,165,337,197);
		CreateString(true,"Silver_ShipCapacity", GetCargoFreeSpace(PChar) + "/" +  GetCargoMaxSpace(PChar), FONT_BOLD_NUMBERS, argb(255,255,128,128), 370,170,SCRIPT_ALIGN_LEFT,1.0);

	}
	else
	{
		CreateImage("Silver", "GOODS", "Silver", 285,58,355,128);
		//CreateString(true,"SilverHeader", "Добыто", FONT_CAPTION, COLOR_NORMAL, 400,145,SCRIPT_ALIGN_CENTER,1.0);
		CreateString(true,"SilverInMine", iSilverQuantity + "/" + iMaxSilverQuantity, FONT_BOLD_NUMBERS, iMoneyColor, 370,85,SCRIPT_ALIGN_LEFT,1.0);
		GameInterface.SILVER_STRING.str = iSilverTempQuantity;

		CreateImage("SilverWeight", "ICONS", "weight icon", 303,126,335,158);
		int iSilverCargo = GetGoodWeightByType(GOOD_SILVER, iSilverTempQuantity);

		CreateString(true,"SilverWeight", iSilverCargo, FONT_BOLD_NUMBERS, iSilverWeightColor, 370,131,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("Silver_ShipCapacity", "ICONS", "ship capacity icon", 304,165,337,197);
		CreateString(true,"Silver_ShipCapacity", GetCargoFreeSpace(PChar) + "/" +  GetCargoMaxSpace(PChar), FONT_BOLD_NUMBERS, iSilverSpaceColor, 370,170,SCRIPT_ALIGN_LEFT,1.0);

		//CreateImage("SilverToCharacter", "MAIN_ICONS", "skillborder", 360,205,444,237);
		//CreateString(true,"SilverToCharacter", iSilverTempQuantity, FONT_CAPTION, COLOR_NORMAL, 401,204,SCRIPT_ALIGN_CENTER,1.5);
	}

	// IRON MINE
	if(PChar.Mines.IronMine == false || PChar.ColonyBuilding.IronMine.BuildingTime == true)
	{
		SetNodeUsing("IRONLEFT", false);
		SetNodeUsing("IRONRIGHT", false);
		SetNodeUsing("IRON_STRING", false);
		SetNodeUsing("IRON_STRING_VIDEO", false);
		SetNodeUsing("IRON_LEFT_ALL", false);
		SetNodeUsing("IRON_RIGHT_ALL", false);
		SetNodeUsing("BUTTON_GIVEIRON", false);;
		CreateString(true,"IronMineNot", "Данный рудник не построен.", FONT_NORMAL, argb(255,255,128,128), 660,230,SCRIPT_ALIGN_CENTER,1.0);

		CreateImage("Iron", "GOODS", "Iron", 545,58,615,128);
		CreateString(true,"IronInMine", "0/0", FONT_BOLD_NUMBERS, argb(255,255,128,128), 630,85,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("IronWeight", "ICONS", "weight icon", 562,126,594,158);
		CreateString(true,"IronWeight", "0", FONT_BOLD_NUMBERS, argb(255,255,128,128), 630,131,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("Iron_ShipCapacity", "ICONS", "ship capacity icon", 565,165,597,197);
		CreateString(true,"Iron_ShipCapacity", GetCargoFreeSpace(PChar) + "/" +  GetCargoMaxSpace(PChar), FONT_BOLD_NUMBERS, argb(255,255,128,128), 630,170,SCRIPT_ALIGN_LEFT,1.0);

	}
	else
	{
		CreateImage("Iron", "GOODS", "Iron", 545,58,615,128);
		CreateString(true,"IronInMine", iIronQuantity + "/" + iMaxIronQuantity, FONT_BOLD_NUMBERS, iMoneyColor, 630,85,SCRIPT_ALIGN_LEFT,1.0);
		GameInterface.IRON_STRING.str = iIronTempQuantity;

		CreateImage("IronWeight", "ICONS", "weight icon", 562,126,594,158);
		int iIronCargo = GetGoodWeightByType(GOOD_IRON, iIronTempQuantity);

		CreateString(true,"IronWeight", iIronCargo, FONT_BOLD_NUMBERS, iIronWeightColor, 630,131,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("Iron_ShipCapacity", "ICONS", "ship capacity icon", 565,165,597,197);
		CreateString(true,"Iron_ShipCapacity", GetCargoFreeSpace(PChar) + "/" +  GetCargoMaxSpace(PChar), FONT_BOLD_NUMBERS, iIronSpaceColor, 630,170,SCRIPT_ALIGN_LEFT,1.0);
	}

	CreateString(true,"GuardiansHeader", "Охранники", FONT_CAPTION, COLOR_NORMAL, 200,281,SCRIPT_ALIGN_CENTER,1.5);
	CreateString(true,"SlavesHeader", "Рабы", FONT_CAPTION, COLOR_NORMAL, 200,442,SCRIPT_ALIGN_CENTER,1.5);
	CreateString(true,"FoodHeader", "Провиант", FONT_CAPTION, COLOR_NORMAL, 590,281,SCRIPT_ALIGN_CENTER,1.5);
	CreateString(true,"MedicamentHeader", "Лекарства", FONT_CAPTION, COLOR_NORMAL, 590,442,SCRIPT_ALIGN_CENTER,1.5);


	if(PChar.Mines.GoldMine == true || PChar.Mines.SilverMine == true || PChar.Mines.IronMine == true)
	{
		CreateString(true,"GuardiansQuantity", "Количество охранников: ", FONT_NORMAL, COLOR_NORMAL, 30,320,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"GuardiansQuantityContinue", "" + iGuardiansQuantity, FONT_NORMAL, COLOR_NORMAL, 320,320,SCRIPT_ALIGN_LEFT,1.0);

		CreateString(true,"MaxGuardiansQuantity", "Максимальное количество охранников: ", FONT_NORMAL, COLOR_NORMAL, 30,337,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"MaxGuardiansQuantityContinue", "" + iMaxGuardiansQuantity, FONT_NORMAL, COLOR_NORMAL, 320,337,SCRIPT_ALIGN_LEFT,1.0);

		CreateString(true,"HireGuardiansQuantity", "Моряков на корабле: ", FONT_NORMAL, COLOR_NORMAL, 30,353,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"HireGuardiansQuantityContinue", "" + iSailorsInShip, FONT_NORMAL, COLOR_NORMAL, 320,353,SCRIPT_ALIGN_LEFT,1.0);

		GameInterface.GUARDIANS_STRING.str = iGuardiansTempQuantity;

		//---------------------------------------------------------------------------------------------------------

		CreateString(true,"SlavesQuantity", "Количество рабов: ", FONT_NORMAL, COLOR_NORMAL, 30,475,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"SlavesQuantityContinue", "" + iSlavesQuantity, FONT_NORMAL, COLOR_NORMAL, 320,475,SCRIPT_ALIGN_LEFT,1.0);

		CreateString(true,"MaxSlavesQuantity", "Максимальное количество рабов: ", FONT_NORMAL, COLOR_NORMAL, 30,493,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"MaxSlavesQuantityContinue", "" + iMaxSlavesQuantity, FONT_NORMAL, COLOR_NORMAL, 320,493,SCRIPT_ALIGN_LEFT,1.0);

		CreateString(true,"SlavesInHold", "Количество рабов в трюме: ", FONT_NORMAL, COLOR_NORMAL, 30,509,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"SlavesInHoldContinue", "" + GetCargoGoods(PChar, GOOD_SLAVES), FONT_NORMAL, COLOR_NORMAL, 320,509,SCRIPT_ALIGN_LEFT,1.0);

		GameInterface.SLAVES_STRING.str = iSlavesTempQuantity;

		//---------------------------------------------------------------------------------------------------------

		int iFoodMax = sti(PChar.Mines.FoodQuantity.Max);
		int iFoodDays = GetMinesFoodDays();
		string sFoodDays = "Провианта на рудниках на " + iFoodDays + " нед.";

		CreateString(true,"FoodQuantity", "Количество провианта (тек. / макс.): ", FONT_NORMAL, COLOR_NORMAL, 420,320,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"FoodQuantityContinue", "" + iFoodQuantity + "/" + iFoodMax, FONT_NORMAL, COLOR_NORMAL, 690,320,SCRIPT_ALIGN_LEFT,1.0);

		CreateString(true,"FoodInHold", "Количество провианта в трюме: ", FONT_NORMAL, COLOR_NORMAL, 420,336,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"FoodInHoldContinue", "" + GetCargoGoods(PChar, GOOD_FOOD), FONT_NORMAL, COLOR_NORMAL, 690,336,SCRIPT_ALIGN_LEFT,1.0);

		CreateString(true,"FoodDays", sFoodDays, FONT_NORMAL, COLOR_NORMAL, 420,352,SCRIPT_ALIGN_LEFT,1.0);

		GameInterface.FOOD_STRING.str = iFoodTempQuantity;

		//---------------------------------------------------------------------------------------------------------

		int iMedicamentMax = sti(PChar.Mines.MedicamentQuantity.Max);
		int iMedicamentDays = GetMinesMedicamentDays()
		string sMedicamentDays = "Лекарств на рудниках на " + iMedicamentDays + " нед.";

		CreateString(true,"MedicamentQuantity", "Количество лекарств (тек. / макс.): ", FONT_NORMAL, COLOR_NORMAL, 420,475,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"MedicamentQuantityContinue", "" + iMedicamentQuantity + "/" + iMedicamentMax, FONT_NORMAL, COLOR_NORMAL, 690,475,SCRIPT_ALIGN_LEFT,1.0);

		CreateString(true,"MedicamentInHold", "Количество лекарств в трюме: ", FONT_NORMAL, COLOR_NORMAL, 420,493,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"MedicamentInHoldContinue", "" + GetCargoGoods(PChar, GOOD_MEDICAMENT), FONT_NORMAL, COLOR_NORMAL, 690,493,SCRIPT_ALIGN_LEFT,1.0);
		CreateString(true,"MedicamentDays", sMedicamentDays, FONT_NORMAL, COLOR_NORMAL, 420,509,SCRIPT_ALIGN_LEFT,1.0);

		GameInterface.MEDICAMENT_STRING.str = iMedicamentTempQuantity;

	}
	else
	{
		SetNodeUsing("GUARDIANSLEFT", false);
		SetNodeUsing("GUARDIANSRIGHT", false);
		SetNodeUsing("GUARDIANS_LEFT_ALL", false);
		SetNodeUsing("GUARDIANS_RIGHT_ALL", false);
		SetNodeUsing("GUARDIANS_ADD", false);
		SetNodeUsing("GUARDIANS_SBROS", false);
		SetNodeUsing("SLAVESLEFT", false);
		SetNodeUsing("SLAVESRIGHT", false);
		SetNodeUsing("SLAVES_LEFT_ALL", false);
		SetNodeUsing("SLAVES_RIGHT_ALL", false);
		SetNodeUsing("SLAVES_ADD", false);
		SetNodeUsing("SLAVES_SBROS", false);
		SetNodeUsing("FOODLEFT", false);
		SetNodeUsing("FOODRIGHT", false);
		SetNodeUsing("FOOD_LEFT_ALL", false);
		SetNodeUsing("FOOD_RIGHT_ALL", false);
		SetNodeUsing("FOOD_ADD", false);
		SetNodeUsing("FOOD_SBROS", false);
		SetNodeUsing("MEDICAMENTLEFT", false);
		SetNodeUsing("MEDICAMENTRIGHT", false);
		SetNodeUsing("MEDICAMENT_LEFT_ALL", false);
		SetNodeUsing("MEDICAMENT_RIGHT_ALL", false);
		SetNodeUsing("MEDICAMENT_ADD", false);
		SetNodeUsing("MEDICAMENT_SBROS", false);
		SetNodeUsing("GUARDIANS_STRING", false);
		SetNodeUsing("SLAVES_STRING", false);
		SetNodeUsing("FOOD_STRING", false);
		SetNodeUsing("MEDICAMENT_STRING", false);
		CreateString(true,"AllMinesNot1", "Не построено ни одного рудника.", FONT_NORMAL, argb(255,255,128,128), 210,380,SCRIPT_ALIGN_CENTER,1.0);
		CreateString(true,"AllMinesNot2", "Не построено ни одного рудника.", FONT_NORMAL, argb(255,255,128,128), 600,380,SCRIPT_ALIGN_CENTER,1.0);
		CreateString(true,"AllMinesNot3", "Не построено ни одного рудника.", FONT_NORMAL, argb(255,255,128,128), 600,525,SCRIPT_ALIGN_CENTER,1.0);
		CreateString(true,"AllMinesNot4", "Не построено ни одного рудника.", FONT_NORMAL, argb(255,255,128,128), 210,525,SCRIPT_ALIGN_CENTER,1.0);
	}

	IsEnabledButtons();
}

int GetMaxSlavesQuantity()
{
	int iQuantity = 0;

	//iQuantity = sti(PChar.ColonyBuilding.GoldMine.MaxSlaves) + sti(PChar.ColonyBuilding.SilverMine.MaxSlaves) + sti(PChar.ColonyBuilding.IronMine.MaxSlaves);
	iQuantity = sti(PChar.Mines.MaxSlavesQuantity);

	return iQuantity;
}

int GetCostForHireGuardians()
{
	int iCost = 0;
	int iLeaderShip = GetCharacterSkill(PChar, SKILL_LEADERSHIP);

	iCost = 500 - (iLeaderShip * 10);
	return iCost;
}

void IsEnabledButtons()
{
	int iGoldTempQuantity = sti(PChar.Mines.Temp.GoldQuantity);
	int iSilverTempQuantity = sti(PChar.Mines.Temp.SilverQuantity);
	int iIronTempQuantity = sti(PChar.Mines.Temp.IronQuantity);
	int iGuardiansTempQuantity = sti(PChar.Mines.Temp.GuardiansQuantity);
	int iSlavesTempQuantity = sti(PChar.Mines.Temp.SlavesQuantity);
	int iFoodTempQuantity = sti(PChar.Mines.Temp.FoodQuantity);
	int iMedicamentTempQuantity = sti(PChar.Mines.Temp.MedicamentQuantity);

	if(iGoldTempQuantity == 0)
	{
		SetSelectable("BUTTON_GIVEGOLD", false);
	}
	else
	{
		SetSelectable("BUTTON_GIVEGOLD", true);
	}

	if(iSilverTempQuantity == 0)
	{
		SetSelectable("BUTTON_GIVESILVER", false);
	}
	else
	{
		SetSelectable("BUTTON_GIVESILVER", true);
	}

	if(iIronTempQuantity == 0)
	{
		SetSelectable("BUTTON_GIVEIRON", false);
	}
	else
	{
		SetSelectable("BUTTON_GIVEIRON", true);
	}

	if(iGuardiansTempQuantity == 0)
	{
		SetSelectable("GUARDIANS_ADD", false);
	}
	else
	{
		SetSelectable("GUARDIANS_ADD", true);
	}

	if(iSlavesTempQuantity == 0)
	{
		SetSelectable("SLAVES_ADD", false);
	}
	else
	{
		SetSelectable("SLAVES_ADD", true);
	}

	if(iFoodTempQuantity == 0)
	{
		SetSelectable("FOOD_ADD", false);
	}
	else
	{
		SetSelectable("FOOD_ADD", true);
	}

	if(iMedicamentTempQuantity == 0)
	{
		SetSelectable("MEDICAMENT_ADD", false);
	}
	else
	{
		SetSelectable("MEDICAMENT_ADD", true);
	}
}

void UptadeFields(string sActive)
{
	if(sActive == "Guardians")
	{
		PChar.Mines.GuardiansCost = sti(PChar.Mines.GuardiansCost);
		PChar.Mines.Temp.GuardiansQuantity = sti(PChar.Mines.Temp.GuardiansQuantity);
		PChar.Mines.Temp.GoldQuantity = 0;
		PChar.Mines.Temp.SilverQuantity = 0;
		PChar.Mines.Temp.IronQuantity = 0;
		PChar.Mines.Temp.SlavesQuantity = 0;
		PChar.Mines.Temp.FoodQuantity = 0;
		PChar.Mines.Temp.MedicamentQuantity = 0;
	}

	if(sActive == "Slaves")
	{
		PChar.Mines.Temp.SlavesQuantity = sti(PChar.Mines.Temp.SlavesQuantity);
		PChar.Mines.GuardiansCost = 0;
		PChar.Mines.Temp.GoldQuantity = 0;
		PChar.Mines.Temp.SilverQuantity = 0;
		PChar.Mines.Temp.IronQuantity = 0;
		PChar.Mines.Temp.GuardiansQuantity = 0;
		PChar.Mines.Temp.FoodQuantity = 0;
		PChar.Mines.Temp.MedicamentQuantity = 0;
	}

	if(sActive == "Food")
	{
		PChar.Mines.Temp.FoodQuantity = sti(PChar.Mines.Temp.FoodQuantity);
		PChar.Mines.GuardiansCost = 0;
		PChar.Mines.Temp.GoldQuantity = 0;
		PChar.Mines.Temp.SilverQuantity = 0;
		PChar.Mines.Temp.IronQuantity = 0;
		PChar.Mines.Temp.GuardiansQuantity = 0;
		PChar.Mines.Temp.SlavesQuantity = 0;
		PChar.Mines.Temp.MedicamentQuantity = 0;
	}

	if(sActive == "Medicament")
	{
		PChar.Mines.Temp.MedicamentQuantity = sti(PChar.Mines.Temp.MedicamentQuantity);
		PChar.Mines.GuardiansCost = 0;
		PChar.Mines.Temp.GoldQuantity = 0;
		PChar.Mines.Temp.SilverQuantity = 0;
		PChar.Mines.Temp.IronQuantity = 0;
		PChar.Mines.Temp.GuardiansQuantity = 0;
		PChar.Mines.Temp.SlavesQuantity = 0;
		PChar.Mines.Temp.FoodQuantity = 0;
	}

	if(sActive == "Gold")
	{
		PChar.Mines.Temp.GoldQuantity = sti(PChar.Mines.Temp.GoldQuantity);
		PChar.Mines.GuardiansCost = 0;
		PChar.Mines.Temp.SilverQuantity = 0;
		PChar.Mines.Temp.IronQuantity = 0;
		PChar.Mines.Temp.GuardiansQuantity = 0;
		PChar.Mines.Temp.SlavesQuantity = 0;
		PChar.Mines.Temp.FoodQuantity = 0;
		PChar.Mines.Temp.MedicamentQuantity = 0;
	}

	if(sActive == "Silver")
	{
		PChar.Mines.Temp.SilverQuantity = sti(PChar.Mines.Temp.SilverQuantity);
		PChar.Mines.GuardiansCost = 0;
		PChar.Mines.Temp.GoldQuantity = 0;
		PChar.Mines.Temp.IronQuantity = 0;
		PChar.Mines.Temp.GuardiansQuantity = 0;
		PChar.Mines.Temp.SlavesQuantity = 0;
		PChar.Mines.Temp.FoodQuantity = 0;
		PChar.Mines.Temp.MedicamentQuantity = 0;
	}

	if(sActive == "Iron")
	{
		PChar.Mines.Temp.IronQuantity = sti(PChar.Mines.Temp.IronQuantity);
		PChar.Mines.GuardiansCost = 0;
		PChar.Mines.Temp.GoldQuantity = 0;
		PChar.Mines.Temp.SilverQuantity = 0;
		PChar.Mines.Temp.GuardiansQuantity = 0;
		PChar.Mines.Temp.SlavesQuantity = 0;
		PChar.Mines.Temp.FoodQuantity = 0;
		PChar.Mines.Temp.MedicamentQuantity = 0;
	}
}

void ClearMinesInfo()
{
	GameInterface.pictures.Gold.tex = "";
	GameInterface.pictures.Gold.pic = "";
	GameInterface.pictures.GoldToCharacter.tex = "";
	GameInterface.pictures.GoldToCharacter.pic = "";
	GameInterface.pictures.Silver.tex = "";
	GameInterface.pictures.SilverToCharacter.pic = "";
	GameInterface.pictures.Iron.tex = "";
	GameInterface.pictures.IronToCharacte.pic = "";
	GameInterface.pictures.TrasferGuardians.tex = "";
	GameInterface.pictures.TrasferGuardians.pic = "";
	GameInterface.pictures.TrasferSlaves.tex = "";
	GameInterface.pictures.TrasferSlaves.pic = "";
	GameInterface.pictures.MedicamentHeaderPicture.tex = "";
	GameInterface.pictures.MedicamentHeaderPicture.pic = "";
	GameInterface.pictures.TrasferFood.tex = "";
	GameInterface.pictures.TrasferFood.pic = "";

	DisableString("GoldHeader");
	DisableString("GoldInMine");
	DisableString("GoldToCharacter");
	DisableString("SilverHeader");
	DisableString("SilverInMine");
	DisableString("SilverToCharacter");
	DisableString("IronHeader");
	DisableString("IronInMine");
	DisableString("IronToCharacter");
	DisableString("GuardiansQuantity");
	DisableString("GuardiansQuantityContinue");
	DisableString("MaxGuardiansQuantity");
	DisableString("MaxGuardiansQuantityContinue");
	DisableString("HireGuardiansQuantity");
	DisableString("HireGuardiansQuantityContinue");
	DisableString("HireGuardiansPrice");
	DisableString("HireGuardiansPriceContinue");
	DisableString("GuardiansCharacterMoney");
	DisableString("GuardiansCharacterMoneyContinue");
	DisableString("TrasferGuardians");
	DisableString("SlavesQuantity");
	DisableString("SlavesQuantityContinue");
	DisableString("MaxSlavesQuantity");
	DisableString("MaxSlavesQuantityContinue");
	DisableString("SlavesInHold");
	DisableString("SlavesInHoldContinue");
	DisableString("TrasferSlaves");
	DisableString("FoodQuantity");
	DisableString("FoodQuantityContinue");
	DisableString("FoodInHold");
	DisableString("FoodInHoldContinue");
	DisableString("MedicamentQuantity");
	DisableString("MedicamentQuantityContinue");
	DisableString("MedicamentInHold");
	DisableString("MedicamentInHoldContinue");
	DisableString("MedicamentHeader");
	DisableString("TrasferFood");
	DisableString("GoldMineNot");
	DisableString("SilverMineNot");
	DisableString("IronMineNot");
	DisableString("AllMinesNot1");
	DisableString("AllMinesNot2");
	DisableString("AllMinesNot3");
	DisableString("AllMinesNot4");

	GameInterface.pictures.GoldWeight.tex = "";
	GameInterface.pictures.GoldWeight.pic = ""
	GameInterface.pictures.Gold_ShipCapacity.tex = "";
	GameInterface.pictures.Gold_ShipCapacity.pic = ""
	DisableString("GoldWeight");
	DisableString("Gold_ShipCapacity");

	GameInterface.pictures.SilverWeight.tex = "";
	GameInterface.pictures.SilverWeight.pic = ""
	GameInterface.pictures.Silver_ShipCapacity.tex = "";
	GameInterface.pictures.Silver_ShipCapacity.pic = ""
	DisableString("SilverWeight");
	DisableString("Silver_ShipCapacity");

	GameInterface.pictures.IronWeight.tex = "";
	GameInterface.pictures.IronWeight.pic = ""
	GameInterface.pictures.Iron_ShipCapacity.tex = "";
	GameInterface.pictures.Iron_ShipCapacity.pic = ""
	DisableString("IronWeight");
	DisableString("Iron_ShipCapacity");
}
