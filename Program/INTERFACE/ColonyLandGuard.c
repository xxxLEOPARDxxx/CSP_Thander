
void InitInterface(string iniName)
{
	GameInterface.title = "titleColonyLandGuard";

    	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	GameInterface.SOLDIERS_STRING.str = 0;
	GameInterface.FOOD_STRING.str = 0;
	GameInterface.MEDICAMENT_STRING.str = 0;

	SetGuardInformation();
	SetFoodInformation();
	SetMedicamentInformation();

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("SoldiersTemp","SoldiersTemp",0);
	SetEventHandler("FoodTemp","FoodTemp",0);
	SetEventHandler("MedicamentTemp","MedicamentTemp",0);
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
	DelEventHandler("SoldiersTemp","SoldiersTemp");
	DelEventHandler("FoodTemp","FoodTemp");
	DelEventHandler("MedicamentTemp","MedicamentTemp");

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
		case "FOOD_LEFT":
			if(comName=="activate" || comName=="click")
			{
				ChangeFood(false, false);
			}
		break;

		case "FOOD_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				ChangeFood(true, false);
			}
		break;

		case "FOOD_LEFT_ALL":
			if(comName=="activate" || comName=="click")
			{
				ChangeFood(false, true);
			}
		break;

		case "FOOD_RIGHT_ALL":
			if(comName=="activate" || comName=="click")
			{
				ChangeFood(true, true);
			}
		break;

		//--------------------------------------------------------

		case "MEDICAMENT_LEFT":
			if(comName=="activate" || comName=="click")
			{
				ChangeMedicament(false, false);
			}
		break;

		case "MEDICAMENT_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				ChangeMedicament(true, false);
			}
		break;

		case "MEDICAMENT_LEFT_ALL":
			if(comName=="activate" || comName=="click")
			{
				ChangeMedicament(false, true);
			}
		break;

		case "MEDICAMENT_RIGHT_ALL":
			if(comName=="activate" || comName=="click")
			{
				ChangeMedicament(true, true);
			}
		break;

		//--------------------------------------------------------

		case "SOLDIERS_LEFT":
			if(comName=="activate" || comName=="click")
			{
				ChangeSoldiers(false, false);
			}
		break;

		case "SOLDIERS_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				ChangeSoldiers(true, false);
			}
		break;

		case "SOLDIERS_LEFT_ALL":
			if(comName=="activate" || comName=="click")
			{
				ChangeSoldiers(false, true);
			}
		break;

		case "SOLDIERS_RIGHT_ALL":
			if(comName=="activate" || comName=="click")
			{
				ChangeSoldiers(true, true);
			}
		break;

		//--------------------------------------------------------

		case "SOLDIERS_HIRE_RESET":
			if(comName=="activate" || comName=="click")
			{
				Reset("SOLDIERS");
			}
		break;

		case "FOOD_TRANSFER_RESET":
			if(comName=="activate" || comName=="click")
			{
				Reset("FOOD");
			}
		break;

		case "MEDICAMENT_TRANSFER_RESET":
			if(comName=="activate" || comName=="click")
			{
				Reset("MEDICAMENT");
			}
		break;

		//--------------------------------------------------------

		case "SOLDIERS_HIRE":
			if(comName=="activate" || comName=="click")
			{
				Done("SOLDIERS");
			}
		break;

		case "FOOD_TRANSFER":
			if(comName=="activate" || comName=="click")
			{
				Done("FOOD");
			}
		break;

		case "MEDICAMENT_TRANSFER":
			if(comName=="activate" || comName=="click")
			{
				Done("MEDICAMENT");
			}
		break;
	}
}

void SoldiersTemp()
{
	int iSoldiersInShip = GetCrewQuantity(PChar);
	if(sti(GameInterface.SOLDIERS_STRING.str) > iSoldiersInShip)
	{
		GameInterface.SOLDIERS_STRING.str = iSoldiersInShip;
	}

	int iFree = sti(PChar.ColonyBuilding.Soldiers.MaxQuantity) - sti(PChar.ColonyBuilding.Soldiers);
	if(sti(GameInterface.SOLDIERS_STRING.str) > iFree)
	{
		GameInterface.SOLDIERS_STRING.str = iFree;
	}

	SetGuardInformation();
}

void FoodTemp()
{
	int iFoodInShip = GetCargoGoods(PChar, GOOD_FOOD);
	if(sti(GameInterface.FOOD_STRING.str) > iFoodInShip)
	{
		GameInterface.FOOD_STRING.str = iFoodInShip;
	}

	int iFree = sti(PChar.ColonyBuilding.Food.MaxQuantity) - sti(PChar.ColonyBuilding.Food);
	if(sti(GameInterface.FOOD_STRING.str) > iFree)
	{
		GameInterface.FOOD_STRING.str = iFree;
	}

	SetFoodInformation();
}

void MedicamentTemp()
{
	int iMedicamentInShip = GetCargoGoods(PChar, GOOD_MEDICAMENT);
	if(sti(GameInterface.MEDICAMENT_STRING.str) > iMedicamentInShip)
	{
		GameInterface.MEDICAMENT_STRING.str = iMedicamentInShip;
	}

	int iFree = sti(PChar.ColonyBuilding.Medicament.MaxQuantity) - sti(PChar.ColonyBuilding.Medicament);
	if(sti(GameInterface.MEDICAMENT_STRING.str) > iFree)
	{
		GameInterface.MEDICAMENT_STRING.str = iFree;
	}

	SetMedicamentInformation();
}

void ChangeSoldiers(bool bAdd, bool bAll)
{
	int iSoldiers = GetCrewQuantity(PChar);
	int iFree = sti(PChar.ColonyBuilding.Soldiers.MaxQuantity) - sti(PChar.ColonyBuilding.Soldiers);

	if(bAdd)
	{
		if(bAll)
		{
			GameInterface.SOLDIERS_STRING.str = iSoldiers;

			if(sti(GameInterface.SOLDIERS_STRING.str) > iFree)
			{
				GameInterface.SOLDIERS_STRING.str = iFree;
			}
		}
		else
		{
			if(sti(GameInterface.SOLDIERS_STRING.str) + 10 > iSoldiers)
			{
				GameInterface.SOLDIERS_STRING.str = iSoldiers;

				if(sti(GameInterface.SOLDIERS_STRING.str) > iFree)
				{
					GameInterface.SOLDIERS_STRING.str = iFree;
				}
			}
			else
			{
				if(sti(GameInterface.SOLDIERS_STRING.str) < iSoldiers)
				{
					GameInterface.SOLDIERS_STRING.str = sti(GameInterface.SOLDIERS_STRING.str) + 10;
				}

				if(sti(GameInterface.SOLDIERS_STRING.str) > iFree)
				{
					GameInterface.SOLDIERS_STRING.str = iFree;
				}
			}
		}
	}
	else
	{
		if(bAll)
		{
			GameInterface.SOLDIERS_STRING.str = 0;
		}
		else
		{
			if(sti(GameInterface.SOLDIERS_STRING.str) - 10 < 0)
			{
				GameInterface.SOLDIERS_STRING.str = 0;
			}
			else
			{
				if(sti(GameInterface.SOLDIERS_STRING.str) > 0)
				{
					GameInterface.SOLDIERS_STRING.str = sti(GameInterface.SOLDIERS_STRING.str) - 10;
				}
			}
		}
	}

	SetGuardInformation();
}

void ChangeFood(bool bAdd, bool bAll)
{
	int iFoodInShip = GetCargoGoods(PChar, GOOD_FOOD);
	int iFree = sti(PChar.ColonyBuilding.Food.MaxQuantity) - sti(PChar.ColonyBuilding.Food);

	if(bAdd)
	{
		if(bAll)
		{
			GameInterface.FOOD_STRING.str = iFoodInShip;

			if(sti(GameInterface.FOOD_STRING.str) > iFree)
			{
				GameInterface.FOOD_STRING.str = iFree;
			}
		}
		else
		{
			if(sti(GameInterface.FOOD_STRING.str) + 10 > iFoodInShip)
			{
				GameInterface.FOOD_STRING.str = iFoodInShip;

				if(sti(GameInterface.FOOD_STRING.str) > iFree)
				{
					GameInterface.FOOD_STRING.str = iFree;
				}
			}
			else
			{
				if(sti(GameInterface.FOOD_STRING.str) < iFoodInShip)
				{
					GameInterface.FOOD_STRING.str = sti(GameInterface.FOOD_STRING.str) + 10;
				}

				if(sti(GameInterface.FOOD_STRING.str) > iFree)
				{
					GameInterface.FOOD_STRING.str = iFree;
				}
			}
		}
	}
	else
	{
		if(bAll)
		{
			GameInterface.FOOD_STRING.str = 0;
		}
		else
		{
			if(sti(GameInterface.FOOD_STRING.str) - 10 < 0)
			{
				GameInterface.FOOD_STRING.str = 0;
			}
			else
			{
				if(sti(GameInterface.FOOD_STRING.str) > 0)
				{
					GameInterface.FOOD_STRING.str = sti(GameInterface.FOOD_STRING.str) - 10;
				}
			}
		}
	}

	SetFoodInformation();
}

void ChangeMedicament(bool bAdd, bool bAll)
{
	int iMedicamentInShip = GetCargoGoods(PChar, GOOD_MEDICAMENT);
	int iFree = sti(PChar.ColonyBuilding.Medicament.MaxQuantity) - sti(PChar.ColonyBuilding.Medicament);

	if(bAdd)
	{
		if(bAll)
		{
			GameInterface.MEDICAMENT_STRING.str = iMedicamentInShip;

			if(sti(GameInterface.MEDICAMENT_STRING.str) > iFree)
			{
				GameInterface.MEDICAMENT_STRING.str = iFree;
			}
		}
		else
		{
			if(sti(GameInterface.MEDICAMENT_STRING.str) + 10 > iMedicamentInShip)
			{
				GameInterface.MEDICAMENT_STRING.str = iMedicamentInShip;

				if(sti(GameInterface.MEDICAMENT_STRING.str) > iFree)
				{
					GameInterface.MEDICAMENT_STRING.str = iFree;
				}
			}
			else
			{
				if(sti(GameInterface.MEDICAMENT_STRING.str) < iMedicamentInShip)
				{
					GameInterface.MEDICAMENT_STRING.str = sti(GameInterface.MEDICAMENT_STRING.str) + 10;
				}

				if(sti(GameInterface.MEDICAMENT_STRING.str) > iFree)
				{
					GameInterface.MEDICAMENT_STRING.str = iFree;
				}
			}
		}
	}
	else
	{
		if(bAll)
		{
			GameInterface.MEDICAMENT_STRING.str = 0;
		}
		else
		{
			if(sti(GameInterface.MEDICAMENT_STRING.str) - 10 < 0)
			{
				GameInterface.MEDICAMENT_STRING.str = 0;
			}
			else
			{
				if(sti(GameInterface.MEDICAMENT_STRING.str) > 0)
				{
					GameInterface.MEDICAMENT_STRING.str = sti(GameInterface.MEDICAMENT_STRING.str) - 10;
				}
			}
		}
	}

	SetFoodInformation();
}

void Reset(string sType)
{
	sType += "_STRING";

	GameInterface.(sType).str = 0;

	switch(sType)
	{
		case "SOLDIERS": SetGuardInformation(); break;
		case "FOOD": SetFoodInformation(); break;
		case "MEDICAMENT": SetMedicamentInformation(); break;
	}
}

void Done(string sType)
{
	switch(sType)
	{
		case "SOLDIERS": SoldiersTemp(); break;
		case "FOOD": FoodTemp(); break;
		case "MEDICAMENT": MedicamentTemp(); break;
	}

	sType += "_STRING";
	int iQuantity = sti(GameInterface.(sType).str);

	switch(sType)
	{
		case "SOLDIERS_STRING":
			PChar.ColonyBuilding.Soldiers = sti(PChar.ColonyBuilding.Soldiers) + iQuantity;
			RemoveCharacterCrew(PChar, iQuantity);
		break;

		case "FOOD_STRING":
			PChar.ColonyBuilding.Food = sti(PChar.ColonyBuilding.Food) + iQuantity;
			RemoveCharacterGoodsSelf(PChar, GOOD_FOOD, iQuantity);
		break;

		case "MEDICAMENT_STRING":
			PChar.ColonyBuilding.Medicament = sti(PChar.ColonyBuilding.Medicament) + iQuantity;
			RemoveCharacterGoodsSelf(PChar, GOOD_MEDICAMENT, iQuantity);
		break;
	}

	SetGuardInformation();
	SetFoodInformation();
	SetMedicamentInformation();

	GameInterface.(sType).str = 0;
}

void SetGuardInformation()
{
	CreateString(true,"SoldiersHeader", "Гарнизон", FONT_CAPTION, COLOR_NORMAL, 395,59,SCRIPT_ALIGN_CENTER,1.5);
	CreateImage("SoldiersQuantity", "SHIP_STATE_ICONS", "Crew", 480,100,580,200);

	int iSoldiersQuantity = sti(PChar.ColonyBuilding.Soldiers);
	int iSoldiersMaxQuantity = sti(PChar.ColonyBuilding.Soldiers.MaxQuantity);
	CreateString(true,"SoldiersQuantity", iSoldiersQuantity + "/" + iSoldiersMaxQuantity, FONT_BOLD_NUMBERS, COLOR_NORMAL, 515,197,SCRIPT_ALIGN_CENTER,1.0);

	CreateString(true,"SoldiersQuantityInShip", "Количество на корабле: ", FONT_NORMAL, COLOR_NORMAL, 210,105,SCRIPT_ALIGN_LEFT,1.0);

	int iCrewInShip = GetCrewQuantity(PChar);
	CreateString(true,"SoldiersQuantityInShip2", iCrewInShip, FONT_NORMAL, COLOR_NORMAL, 400,105,SCRIPT_ALIGN_LEFT,1.0);
}

void SetFoodInformation()
{
	// CreateImage("FoodHeader", "MAIN_ICONS", "skillborder", 204,230,596,262);
	CreateString(true,"FoodHeader", "Провиант", FONT_CAPTION, COLOR_NORMAL, 395,229,SCRIPT_ALIGN_CENTER,1.5);

	CreateImage("FoodQuantity", "GOODS", "Food", 480,260,580,360);

	int iFoodQuantity = sti(PChar.ColonyBuilding.Food);
	int iFoodMaxQuantity = sti(PChar.ColonyBuilding.Food.MaxQuantity);
	CreateString(true,"FoodQuantity", iFoodQuantity + "/" + iFoodMaxQuantity, FONT_BOLD_NUMBERS, COLOR_NORMAL, 515,360,SCRIPT_ALIGN_CENTER,1.0);

	CreateString(true,"FoodQuantityInShip", "Количество на корабле: ", FONT_NORMAL, COLOR_NORMAL, 210,265,SCRIPT_ALIGN_LEFT,1.0);

	int iFoodInShip = GetCargoGoods(PChar, GOOD_FOOD);
	CreateString(true,"FoodQuantityInShip2", iFoodInShip, FONT_NORMAL, COLOR_NORMAL, 400,265,SCRIPT_ALIGN_LEFT,1.0)

	int iDays = GetColonyFoodNeedDays();
	string sFoodDays = "Провианта в колонии на " + iDays + " нед.";
	CreateString(true,"FoodDays", sFoodDays, FONT_NORMAL, COLOR_NORMAL, 210,282,SCRIPT_ALIGN_LEFT,1.0);
}

void SetMedicamentInformation()
{
	// CreateImage("MedicamentHeader", "MAIN_ICONS", "skillborder", 204,391,596,425);
	CreateString(true,"MedicamentHeader", "Медикаменты", FONT_CAPTION, COLOR_NORMAL, 395,389,SCRIPT_ALIGN_CENTER,1.5);

	CreateImage("MedicamentQuantity", "GOODS", "Medicament", 480,420,580,520);

	int iMedicamentQuantity = sti(PChar.ColonyBuilding.Medicament);
	int iMedicamentMaxQuantity = sti(PChar.ColonyBuilding.Medicament.MaxQuantity);
	CreateString(true,"MedicamentQuantity", iMedicamentQuantity + "/" + iMedicamentMaxQuantity, FONT_BOLD_NUMBERS, COLOR_NORMAL, 515,520,SCRIPT_ALIGN_CENTER,1.0);

	CreateString(true,"MedicamentQuantityInShip", "Количество на корабле: ", FONT_NORMAL, COLOR_NORMAL, 210,433,SCRIPT_ALIGN_LEFT,1.0);

	int iMedicamentInShip = GetCargoGoods(PChar, GOOD_MEDICAMENT);
	CreateString(true,"MedicamentQuantityInShip2", iMedicamentInShip, FONT_NORMAL, COLOR_NORMAL, 400,433,SCRIPT_ALIGN_LEFT,1.0);
}
