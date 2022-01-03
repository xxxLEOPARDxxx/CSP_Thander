
void InitInterface(string iniName)
{
    	GameInterface.title = "titlePlantation";

    	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	ref PChar = GetMainCharacter();

	PChar.Plantation.Interface.Instrument = "Bad";
	PChar.Plantation.Interface.Price = GetCostForInstruments(PChar.Plantation.Interface.Instrument);
	PChar.Plantation.Sugar.Temp.Quantity = 0;
	PChar.Plantation.Slaves.Temp.Quantity = 0;
	PChar.Plantation.Food.Temp.Quantity = 0;
	PChar.Plantation.Medicament.Temp.Quantity = 0;
	PChar.Plantation.Sugar.Temp.Quantity = 0;
	PChar.Plantation.Coffee.Temp.Quantity = 0;
	PChar.Plantation.Guardians.Temp.Quantity = 0;
	PChar.Plantation.Guardians.Price = 0;

	PlantationInformation();

	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",5);

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);
	SetEventHandler("GuardiansTempUptade","GuardiansTempUptade",0);
	SetEventHandler("SlavesTempUptade","SlavesTempUptade",0);
	SetEventHandler("FoodTempUptade","FoodTempUptade",0);
	SetEventHandler("MedicamentTempUptade","MedicamentTempUptade",0);
	SetEventHandler("SugarTempUptade","SugarTempUptade",0);
	SetEventHandler("CoffeeTempUptade","CoffeeTempUptade",0);
	SetEventHandler("ItemsTempUptade","ItemsTempUptade",0);
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
	DelEventHandler("GuardiansTempUptade","GuardiansTempUptade");
	DelEventHandler("SlavesTempUptade","SlavesTempUptade");
	DelEventHandler("FoodTempUptade","FoodTempUptade");
	DelEventHandler("MedicamentTempUptade","MedicamentTempUptade");
	DelEventHandler("SugarTempUptade","SugarTempUptade");
	DelEventHandler("CoffeeTempUptade","CoffeeTempUptade");
	DelEventHandler("ItemsTempUptade","ItemsTempUptade");

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
}

int GetCostForMoraleUp()
{
	ref PChar = GetMainCharacter();

	int iCost = 0;
	int iLeaderShip = GetCharacterSkill(PChar, SKILL_LEADERSHIP);

	if(sti(PChar.Plantation.Slaves.Quantity) <= 0)
	{
		return 0;
	}

	iCost = sti(PChar.Plantation.Slaves.Quantity) * 100 - (iLeaderShip * 10);

	if(iCost <= 0)
	{
		iCost = 1000;
	}

	return iCost;
}

void MoraleUp(int iMoney)
{
	if(iMoney <= 0)
	{
		return;
	}

	ref PChar = GetMainCharacter();
	PChar.Plantation.Slaves.Health = sti(PChar.Plantation.Slaves.Health) + 5 + rand(5);
	PChar.Plantation.Slaves.Morale = sti(PChar.Plantation.Slaves.Morale) + 10;
	AddMoneyToCharacter(PChar, -iMoney);
	PlantationInformation();
}

void PlantationUp(int iMoney)
{
	ref PChar = GetMainCharacter();
	AddMoneyToCharacter(PChar, -iMoney);
	PChar.Plantation.Size.Resize.BuildingTime = true;

	LAi_QuestDelay("Plantation_resize", 2.0);

	PlantationInformation();
}

int GetCostForHireGuardians()
{
	int iCost = 0;
	int iLeaderShip = GetCharacterSkill(PChar, SKILL_LEADERSHIP);

	iCost = 500 - (iLeaderShip * 10);
	return iCost;
}

void SelectHireGuardians(bool bLeft)
{
	ref PChar = GetMainCharacter();
	int iMaxTemp = sti(PChar.Plantation.Guardians.MaxQuantity) - sti(PChar.Plantation.Guardians.Quantity);
	int iCrewInShip = GetCrewQuantity(PChar);

	if(bLeft)
	{
		PChar.Plantation.Guardians.Temp.Quantity = sti(PChar.Plantation.Guardians.Temp.Quantity) + 10;
	}
	else
	{
		PChar.Plantation.Guardians.Temp.Quantity = sti(PChar.Plantation.Guardians.Temp.Quantity) - 10;
	}

	if(sti(PChar.Plantation.Guardians.Temp.Quantity) > iCrewInShip)
	{
		PChar.Plantation.Guardians.Temp.Quantity = iCrewInShip;
	}

	if(sti(PChar.Plantation.Guardians.Temp.Quantity) > iMaxTemp)
	{
		PChar.Plantation.Guardians.Temp.Quantity = iMaxTemp;
	}

	if(sti(PChar.Plantation.Guardians.Temp.Quantity) <= 0)
	{
		PChar.Plantation.Guardians.Temp.Quantity = 0;
	}

	if(sti(PChar.Plantation.Guardians.Temp.Quantity) <= 0)
	{
		SetSelectable("GUARDIANS_HIRE", false);
	}
	else
	{
		SetSelectable("GUARDIANS_HIRE", true);
	}

	UptadeFields("Guardians");
	PlantationInformation();
}

void HireGuardians(int iQuantity)
{
	ref PChar = GetMainCharacter();
	RemoveCharacterCrew(PChar, iQuantity);
	PChar.Plantation.Guardians.Quantity = sti(PChar.Plantation.Guardians.Quantity) + iQuantity;
	PChar.Plantation.Guardians.Temp.Quantity = 0;
	PlantationInformation();
}

void GuardiansSbros()
{
	ref PChar = GetMainCharacter();
	PChar.Plantation.Guardians.Temp.Quantity = 0;
	PChar.Plantation.Guardians.Price = 0;
	PlantationInformation();
}

void SelectFoodQuantity(bool bAdd)
{
	ref PChar = GetMainCharacter();
	int iMaxStep = sti(PChar.Plantation.Food.MaxQuantity) - sti(PChar.Plantation.Food.Quantity);
	int iCargo = GetCargoGoods(PChar, GOOD_FOOD);

	if(bAdd)
	{
		PChar.Plantation.Food.Temp.Quantity = sti(PChar.Plantation.Food.Temp.Quantity) + 100;
	}
	else
	{
		PChar.Plantation.Food.Temp.Quantity = sti(PChar.Plantation.Food.Temp.Quantity) - 100;
	}

	if(sti(PChar.Plantation.Food.Temp.Quantity) > iCargo)
	{
		PChar.Plantation.Food.Temp.Quantity = iCargo;
	}

	if(sti(PChar.Plantation.Food.Temp.Quantity) > iMaxStep)
	{
		PChar.Plantation.Food.Temp.Quantity = iMaxStep;
	}

	if(sti(PChar.Plantation.Food.Temp.Quantity) <= 0)
	{
		PChar.Plantation.Food.Temp.Quantity = 0;
	}

	UptadeFields("Food");
	PlantationInformation();
}

void FoodTransfer(int iQuantity)
{
	ref PChar = GetMainCharacter();
	RemoveCharacterGoods(PChar, GOOD_FOOD, iQuantity);
	PChar.Plantation.Food.Quantity = sti(PChar.Plantation.Food.Quantity) + iQuantity;
	PChar.Plantation.Food.Temp.Quantity = 0;
	PlantationInformation();
}

void FoodSbros()
{
	ref PChar = GetMainCharacter();
	PChar.Plantation.Food.Temp.Quantity = 0;
	PlantationInformation();
}

void SelectSlavesQuantity(bool bAdd)
{
	ref PChar = GetMainCharacter();
	int iMaxStep = sti(PChar.Plantation.Slaves.MaxQuantity) - sti(PChar.Plantation.Slaves.Quantity);
	int iCargo = GetCargoGoods(PChar, GOOD_SLAVES);

	if(bAdd)
	{
		PChar.Plantation.Slaves.Temp.Quantity = sti(PChar.Plantation.Slaves.Temp.Quantity) + 10;
	}
	else
	{
		PChar.Plantation.Slaves.Temp.Quantity = sti(PChar.Plantation.Slaves.Temp.Quantity) - 10;
	}

	if(sti(PChar.Plantation.Slaves.Temp.Quantity) > iCargo)
	{
		PChar.Plantation.Slaves.Temp.Quantity = iCargo;
	}

	if(sti(PChar.Plantation.Slaves.Temp.Quantity) > iMaxStep)
	{
		PChar.Plantation.Slaves.Temp.Quantity = iMaxStep;
	}

	if(sti(PChar.Plantation.Slaves.Temp.Quantity) <= 0)
	{
		PChar.Plantation.Slaves.Temp.Quantity = 0;
	}

	UptadeFields("Slaves");
	PlantationInformation();
}

void SlavesTransfer(int iQuantity)
{
	ref PChar = GetMainCharacter();
	RemoveCharacterGoods(PChar, GOOD_SLAVES, iQuantity);
	PChar.Plantation.Slaves.Quantity = sti(PChar.Plantation.Slaves.Quantity) + iQuantity;
	PChar.Plantation.Slaves.Temp.Quantity = 0;
	PlantationInformation();
}

void SlavesSbros()
{
	ref PChar = GetMainCharacter();
	PChar.Plantation.Slaves.Temp.Quantity = 0;
	PlantationInformation();
}

void SelectMedicamentQuantity(bool bAdd)
{
	ref PChar = GetMainCharacter();
	int iMaxStep = sti(PChar.Plantation.Medicament.MaxQuantity) - sti(PChar.Plantation.Medicament.Quantity);
	int iCargo = GetCargoGoods(PChar, GOOD_MEDICAMENT);

	if(bAdd)
	{
		PChar.Plantation.Medicament.Temp.Quantity = sti(PChar.Plantation.Medicament.Temp.Quantity) + 100;
	}
	else
	{
		PChar.Plantation.Medicament.Temp.Quantity = sti(PChar.Plantation.Medicament.Temp.Quantity) - 100;
	}

	if(sti(PChar.Plantation.Medicament.Temp.Quantity) > iCargo)
	{
		PChar.Plantation.Medicament.Temp.Quantity = iCargo;
	}
	if(sti(PChar.Plantation.Medicament.Temp.Quantity) > iMaxStep)
	{
		PChar.Plantation.Medicament.Temp.Quantity = iMaxStep;
	}
	if(sti(PChar.Plantation.Medicament.Temp.Quantity) <= 0)
	{
		PChar.Plantation.Medicament.Temp.Quantity = 0;
	}

	UptadeFields("Medicament");
	PlantationInformation();
}

void MedicamentTransfer(int iQuantity)
{
	ref PChar = GetMainCharacter();
	RemoveCharacterGoods(PChar, GOOD_MEDICAMENT, iQuantity);
	PChar.Plantation.Medicament.Quantity = sti(PChar.Plantation.Medicament.Quantity) + iQuantity;
	PChar.Plantation.Medicament.Temp.Quantity = 0;
	PlantationInformation();
}

void MedicamentSbros()
{
	ref PChar = GetMainCharacter();
	PChar.Plantation.Medicament.Temp.Quantity = 0;
	PlantationInformation();
}

void SelectSugarQuantity(bool bAdd)
{
	int iSugar = sti(PChar.Plantation.Sugar.Quantity);

	if(bAdd)
	{
		PChar.Plantation.Sugar.Temp.Quantity = sti(PChar.Plantation.Sugar.Temp.Quantity) + 100;
	}
	else
	{
		PChar.Plantation.Sugar.Temp.Quantity = sti(PChar.Plantation.Sugar.Temp.Quantity) - 100;
	}

	if(sti(PChar.Plantation.Sugar.Temp.Quantity) <= 0)
	{
		PChar.Plantation.Sugar.Temp.Quantity = 0;
	}

	if(sti(PChar.Plantation.Sugar.Temp.Quantity) > iSugar)
	{
		PChar.Plantation.Sugar.Temp.Quantity = iSugar;
	}

	int iCargo = GetGoodWeightByType(GOOD_SUGAR, sti(PChar.Plantation.Sugar.Temp.Quantity));
	if(iCargo > GetCargoFreeSpace(PChar))
	{
		PChar.Plantation.Sugar.Temp.Quantity = GetCharacterFreeSpace(PChar, GOOD_SUGAR);
	}

	if(GetCargoFreeSpace(PChar) <= 0)
	{
		PChar.Plantation.Sugar.Temp.Quantity = 0;
	}

	if(sti(PChar.Plantation.Sugar.Temp.Quantity) < 0)
	{
		SetSelectable("SUGAR_GIVE", false);
	}
	else
	{
		SetSelectable("SUGAR_GIVE", true);
	}

	UptadeFields("Sugar");
	PlantationInformation();
}

void GiveSugar(int iQuantity)
{
	ref PChar = GetMainCharacter();
	RemoveCharacterGoods(PChar, GOOD_SUGAR, -iQuantity);
	PChar.Plantation.Sugar.Quantity = sti(PChar.Plantation.Sugar.Quantity) - iQuantity;
	PChar.Plantation.Sugar.Temp.Quantity = 0;
	PlantationInformation();
}

void SugarGiveAll()
{
	ref PChar = GetMainCharacter();
	RemoveCharacterGoods(PChar, GOOD_SUGAR, -sti(PChar.Plantation.Sugar.Quantity));
	PChar.Plantation.Sugar.Quantity = 0;
	PChar.Plantation.Sugar.Temp.Quantity = 0;
	PlantationInformation();
}

void SugarSbros()
{
	ref PChar = GetMainCharacter();
	PChar.Plantation.Sugar.Temp.Quantity = 0;
	PlantationInformation();
}

void SelectCoffeeQuantity(bool bAdd)
{
	int iCoffee = sti(PChar.Plantation.Coffee.Quantity);

	if(bAdd)
	{
		PChar.Plantation.Coffee.Temp.Quantity = sti(PChar.Plantation.Coffee.Temp.Quantity) + 100;
	}
	else
	{
		PChar.Plantation.Coffee.Temp.Quantity = sti(PChar.Plantation.Coffee.Temp.Quantity) - 100;
	}

	if(sti(PChar.Plantation.Coffee.Temp.Quantity) <= 0)
	{
		PChar.Plantation.Coffee.Temp.Quantity = 0;
	}

	if(sti(PChar.Plantation.Coffee.Temp.Quantity) > iCoffee)
	{
		PChar.Plantation.Coffee.Temp.Quantity = iCoffee;
	}

	int iCargo = GetGoodWeightByType(GOOD_COFFEE, sti(PChar.Plantation.Coffee.Temp.Quantity));
	if(iCargo > GetCargoFreeSpace(PChar))
	{
		PChar.Plantation.Coffee.Temp.Quantity = GetCharacterFreeSpace(PChar, GOOD_COFFEE);
	}

	if(GetCargoFreeSpace(PChar) <= 0)
	{
		PChar.Plantation.Coffee.Temp.Quantity = 0;
	}

	if(sti(PChar.Plantation.Coffee.Temp.Quantity) < 0)
	{
		SetSelectable("COFFEE_GIVE", false);
	}
	else
	{
		SetSelectable("COFFEE_GIVE", true);
	}

	UptadeFields("Coffee");
	PlantationInformation();
}

void GiveCoffee(int iQuantity)
{
	ref PChar = GetMainCharacter();
	RemoveCharacterGoods(PChar, GOOD_COFFEE, -iQuantity);
	PChar.Plantation.Coffee.Quantity = sti(PChar.Plantation.Coffee.Quantity) - iQuantity;
	PChar.Plantation.Coffee.Temp.Quantity = 0;
	PlantationInformation();
}

void CoffeeGiveAll()
{
	ref PChar = GetMainCharacter();
	RemoveCharacterGoods(PChar, GOOD_COFFEE, -sti(PChar.Plantation.Coffee.Quantity));
	PChar.Plantation.Coffee.Quantity = 0;
	PChar.Plantation.Coffee.Temp.Quantity = 0;
	PlantationInformation();
}

void CoffeeSbros()
{
	ref PChar = GetMainCharacter();
	PChar.Plantation.Coffee.Temp.Quantity = 0;
	PlantationInformation();
}

void SelectItemsQuantity(bool bAdd)
{
	ref PChar = GetMainCharacter();
	int iMaxStep = sti(PChar.Plantation.Items.MaxQuantity) - sti(PChar.Plantation.Items.Quantity);
	int iCargo = GetCargoGoods(PChar, GOOD_TOOLS);

	if(bAdd)
	{
		PChar.Plantation.Items.Temp.Quantity = sti(PChar.Plantation.Items.Temp.Quantity) + 10;
	}
	else
	{
		PChar.Plantation.Items.Temp.Quantity = sti(PChar.Plantation.Items.Temp.Quantity) - 10;
	}

	if(sti(PChar.Plantation.Items.Temp.Quantity) > iCargo)
	{
		PChar.Plantation.Items.Temp.Quantity = iCargo;
	}

	if(sti(PChar.Plantation.Items.Temp.Quantity) > iMaxStep)
	{
		PChar.Plantation.Items.Temp.Quantity = iMaxStep;
	}

	if(sti(PChar.Plantation.Items.Temp.Quantity) <= 0)
	{
		PChar.Plantation.Items.Temp.Quantity = 0;
	}

	if(sti(PChar.Plantation.Items.Temp.Quantity) <= 0)
	{
		SetSelectable("ITEMS_ADD", false);
	}
	else
	{
		SetSelectable("ITEMS_ADD", true);
	}

	UptadeFields("Items");
	PlantationInformation();
}

void ItemsTransfer(int iQuantity)
{
	ref PChar = GetMainCharacter();
	RemoveCharacterGoods(PChar, GOOD_TOOLS, iQuantity);
	PChar.Plantation.Items.Quantity = sti(PChar.Plantation.Items.Quantity) + iQuantity;
	PChar.Plantation.Items.Temp.Quantity = 0;
	PlantationInformation();
}

void ItemsSbros()
{
	ref PChar = GetMainCharacter();
	PChar.Plantation.Items.Temp.Quantity = 0;
	PlantationInformation();
}

void SelectInstrument(bool bTrue)
{
	ref PChar = GetMainCharacter();
	if(bTrue)
	{
		if(PChar.Plantation.Interface.Instrument == "Bad")
		{
			return;
		}

		if(PChar.Plantation.Interface.Instrument == "Normal")
		{
			PChar.Plantation.Interface.Instrument = "Bad";
		}

		if(PChar.Plantation.Interface.Instrument == "Good")
		{
			PChar.Plantation.Interface.Instrument = "Normal";
		}
	}
	else
	{
		if(PChar.Plantation.Interface.Instrument == "Good")
		{
			return;
		}

		if(PChar.Plantation.Interface.Instrument == "Normal")
		{
			PChar.Plantation.Interface.Instrument = "Good";
		}

		if(PChar.Plantation.Interface.Instrument == "Bad")
		{
			PChar.Plantation.Interface.Instrument = "Normal";
		}
	}
	UptadeFields("All");
	PChar.Plantation.Instrument.Price = GetCostForInstruments(PChar.Plantation.Interface.Instrument);
	PlantationInformation();
}

int GetCostForInstruments(string sInstrument)
{
	ref PChar = GetMainCharacter();
	int iCost, iBonus;

	switch(sInstrument)
	{
		case "Bad": iBonus = 700; break;
		case "Normal": iBonus = 1300; break;
		case "Good": iBonus = 2200; break;
	}

	iCost = sti(PChar.Plantation.Slaves.Quantity) * iBonus;

	return iCost;
}

void InstallInstrument(string sInstrument, int iCost)
{
	AddMoneyToCharacter(PChar, -iCost);
	PChar.Plantation.Instrument = sInstrument;
	PChar.Plantation.Interface.Instrument = "Bad";
	PlantationInformation();
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
		case "MORALE_UP":
			if(comName=="activate" || comName=="click")
			{
				MoraleUp(GetCostForMoraleUp());
			}
		break;

		case "PLANTATION_UP":
			if(comName=="activate" || comName=="click")
			{
				PlantationUp(sti(PChar.Plantation.ResizeMoney));
			}
		break;

		case "GUARDIANS_LEFT":
			if(comName=="activate" || comName=="click")
			{
				SelectHireGuardians(false);
			}
		break;

		case "GUARDIANS_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				SelectHireGuardians(true);
			}
		break;

		case "GUARDIANS_HIRE":
			if(comName=="activate" || comName=="click")
			{
				HireGuardians(sti(PChar.Plantation.Guardians.Temp.Quantity));
			}
		break;

		case "GUARDIANS_LEFT_ALL":
			if(comName=="activate" || comName=="click")
			{
				SelectAll("Guardians", false);
			}
		break;

		case "GUARDIANS_RIGHT_ALL":
			if(comName=="activate" || comName=="click")
			{
				SelectAll("Guardians", true);
			}
		break;

		case "GUARDIANS_SBROS":
			if(comName=="activate" || comName=="click")
			{
				GuardiansSbros();
			}
		break;

		case "SLAVES_LEFT":
			if(comName=="activate" || comName=="click")
			{
				SelectSlavesQuantity(false);
			}
		break;

		case "SLAVES_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				SelectSlavesQuantity(true);
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

		case "SLAVES_TRANSFER":
			if(comName=="activate" || comName=="click")
			{
				SlavesTransfer(sti(PChar.Plantation.Slaves.Temp.Quantity));
			}
		break;

		case "SLAVES_SBROS":
			if(comName=="activate" || comName=="click")
			{
				SlavesSbros();
			}
		break;

		case "FOOD_LEFT":
			if(comName=="activate" || comName=="click")
			{
				SelectFoodQuantity(false);
			}
		break;

		case "FOOD_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				SelectFoodQuantity(true);
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

		case "FOOD_TRANSFER":
			if(comName=="activate" || comName=="click")
			{
				FoodTransfer(sti(PChar.Plantation.Food.Temp.Quantity));
			}
		break;

		case "FOOD_SBROS":
			if(comName=="activate" || comName=="click")
			{
				FoodSbros();
			}
		break;

		case "MEDICAMENT_LEFT":
			if(comName=="activate" || comName=="click")
			{
				SelectMedicamentQuantity(false);
			}
		break;

		case "MEDICAMENT_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				SelectMedicamentQuantity(true);
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

		case "MEDICAMENT_TRANSFER":
			if(comName=="activate" || comName=="click")
			{
				MedicamentTransfer(sti(PChar.Plantation.Medicament.Temp.Quantity));
			}
		break;

		case "MEDICAMENT_SBROS":
			if(comName=="activate" || comName=="click")
			{
				MedicamentSbros();
			}
		break;

		case "SUGAR_LEFT":
			if(comName=="activate" || comName=="click")
			{
				SelectSugarQuantity(false);
			}
		break;

		case "SUGAR_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				SelectSugarQuantity(true);
			}
		break;

		case "SUGAR_GIVE":
			if(comName=="activate" || comName=="click")
			{
				GiveSugar(sti(PChar.Plantation.Sugar.Temp.Quantity));
			}
		break;

		case "SUGAR_LEFT_ALL":
			if(comName=="activate" || comName=="click")
			{
				SelectAll("Sugar", false);
			}
		break;

		case "SUGAR_RIGHT_ALL":
			if(comName=="activate" || comName=="click")
			{
				SelectAll("Sugar", true);
			}
		break;

		case "SUGAR_SBROS":
			if(comName=="activate" || comName=="click")
			{
				SugarSbros();
			}
		break;

		case "COFFEE_LEFT":
			if(comName=="activate" || comName=="click")
			{
				SelectCoffeeQuantity(false);
			}
		break;

		case "COFFEE_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				SelectCoffeeQuantity(true);
			}
		break;

		case "COFFEE_GIVE":
			if(comName=="activate" || comName=="click")
			{
				GiveCoffee(sti(PChar.Plantation.Coffee.Temp.Quantity));
			}
		break;

		case "COFFEE_LEFT_ALL":
			if(comName=="activate" || comName=="click")
			{
				SelectAll("Coffee", false);
			}
		break;

		case "COFFEE_RIGHT_ALL":
			if(comName=="activate" || comName=="click")
			{
				SelectAll("Coffee", true);
			}
		break;

		case "COFFEE_SBROS":
			if(comName=="activate" || comName=="click")
			{
				CoffeeSbros();
			}
		break;

		case "INSTRUMENTS_LEFT":
			if(comName=="activate" || comName=="click")
			{
				SelectInstrument(true);
			}
		break;

		case "INSTRUMENTS_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				SelectInstrument(false);
			}
		break;

		case "INSTRUMENTS_INSTALL":
			if(comName=="activate" || comName=="click")
			{
				InstallInstrument(PChar.Plantation.Interface.Instrument, sti(PChar.Plantation.Instrument.Price));
			}
		break;

		case "ITEMS_LEFT":
			if(comName=="activate" || comName=="click")
			{
				SelectItemsQuantity(false);
			}
		break;

		case "ITEMS_RIGHT":
			if(comName=="activate" || comName=="click")
			{
				SelectItemsQuantity(true);
			}
		break;

		case "ITEMS_LEFT_ALL":
			if(comName=="activate" || comName=="click")
			{
				SelectAll("Items", false);
			}
		break;

		case "ITEMS_RIGHT_ALL":
			if(comName=="activate" || comName=="click")
			{
				SelectAll("Items", true);
			}
		break;

		case "ITEMS_ADD":
			if(comName=="activate" || comName=="click")
			{
				ItemsTransfer(sti(PChar.Plantation.Items.Temp.Quantity));
			}
		break;

		case "ITEMS_SBROS":
			if(comName=="activate" || comName=="click")
			{
				ItemsSbros();
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
			int iGuardiansQuantity = sti(PChar.Plantation.Guardians.Quantity);
			int iGuardiansMaxQuantity = sti(PChar.Plantation.Guardians.MaxQuantity);
			int iGuardiansInShip = GetCrewQuantity(PChar);

			if(!bAdd)
			{
				PChar.Plantation.Guardians.Temp.Quantity = 0;
			}
			else
			{
				PChar.Plantation.Guardians.Temp.Quantity = iGuardiansMaxQuantity - iGuardiansQuantity;

				if(sti(PChar.Plantation.Guardians.Temp.Quantity) > iGuardiansInShip)
				{
					PChar.Plantation.Guardians.Temp.Quantity = iGuardiansInShip;
				}
			}
		break;

		case "Slaves":
			if(!bAdd)
			{
				PChar.Plantation.Slaves.Temp.Quantity = 0;
			}
			else
			{
				int iSlavesHoldQuantity = GetCargoGoods(PChar, GOOD_SLAVES);
				int iSlavesQuantity = sti(PChar.Plantation.Slaves.Quantity);
				int iSlavesMaxQuantity = sti(PChar.Plantation.Slaves.MaxQuantity);

				PChar.Plantation.Slaves.Temp.Quantity = (iSlavesMaxQuantity - iSlavesQuantity);

				if(sti(PChar.Plantation.Slaves.Temp.Quantity) > iSlavesHoldQuantity)
				{
					PChar.Plantation.Slaves.Temp.Quantity = iSlavesHoldQuantity;
				}
			}
		break;

		case "Food":
			if(!bAdd)
			{
				PChar.Plantation.Food.Temp.Quantity = 0;
			}
			else
			{
				int iFoodMaxStep = sti(PChar.Plantation.Food.MaxQuantity) - sti(PChar.Plantation.Food.Quantity);
				int iFoodHoldQuantity = GetCargoGoods(PChar, GOOD_FOOD);

				PChar.Plantation.Food.Temp.Quantity = iFoodMaxStep;

				if(sti(PChar.Plantation.Food.Temp.Quantity) > iFoodHoldQuantity)
				{
					PChar.Plantation.Food.Temp.Quantity = iFoodHoldQuantity;
				}
			}
		break;

		case "Medicament":
			if(!bAdd)
			{
				PChar.Plantation.Medicament.Temp.Quantity = 0;
			}
			else
			{
				int iMedicamentMaxStep = sti(PChar.Plantation.Medicament.MaxQuantity) - sti(PChar.Plantation.Medicament.Quantity);
				int iMedicamentHoldQuantity = GetCargoGoods(PChar, GOOD_MEDICAMENT);

				PChar.Plantation.Medicament.Temp.Quantity = iMedicamentMaxStep;

				if(sti(PChar.Plantation.Medicament.Temp.Quantity) > iMedicamentHoldQuantity)
				{
					PChar.Plantation.Medicament.Temp.Quantity = iMedicamentHoldQuantity;
				}
			}
		break;

		case "Sugar":
			if(!bAdd)
			{
				PChar.Plantation.Sugar.Temp.Quantity = 0;
			}
			else
			{
				PChar.Plantation.Sugar.Temp.Quantity = sti(PChar.Plantation.Sugar.Quantity);

				int iSugarCargo = GetGoodWeightByType(GOOD_SUGAR, sti(PChar.Plantation.Sugar.Temp.Quantity));

				if(GetCargoFreeSpace(PChar) < 0)
				{
					PChar.Plantation.Sugar.Temp.Quantity = 0;
				}
				else
				{
					if(iSugarCargo > GetCargoFreeSpace(PChar))
					{
						PChar.Plantation.Sugar.Temp.Quantity = GetCharacterFreeSpace(PChar, GOOD_SUGAR);
					}
				}
			}
		break;

		case "Coffee":
			if(!bAdd)
			{
				PChar.Plantation.Coffee.Temp.Quantity = 0;
			}
			else
			{
				PChar.Plantation.Coffee.Temp.Quantity = sti(PChar.Plantation.Coffee.Quantity);

				int iCoffeeCargo = GetGoodWeightByType(GOOD_COFFEE, sti(PChar.Plantation.Coffee.Temp.Quantity));

				if(GetCargoFreeSpace(PChar) < 0)
				{
					PChar.Plantation.Coffee.Temp.Quantity = 0;
				}
				else
				{
					if(iCoffeeCargo > GetCargoFreeSpace(PChar))
					{
						PChar.Plantation.Coffee.Temp.Quantity = GetCharacterFreeSpace(PChar, GOOD_COFFEE);
					}
				}
			}
		break;

		case "Items":
			if(!bAdd)
			{
				PChar.Plantation.Items.Temp.Quantity = 0;
			}
			else
			{
				int iItemsMaxStep = sti(PChar.Plantation.Items.MaxQuantity) - sti(PChar.Plantation.Items.Quantity);
				int iItemsHoldQuantity = GetCargoGoods(PChar, GOOD_TOOLS);

				PChar.Plantation.Items.Temp.Quantity = iItemsMaxStep;

				if(sti(PChar.Plantation.Items.Temp.Quantity) > iItemsHoldQuantity)
				{
					PChar.Plantation.Items.Temp.Quantity = iItemsHoldQuantity;
				}
			}
		break;
	}

	UptadeFields(sType);
	PlantationInformation();
}


void GuardiansTempUptade()
{
	int iGuardiansQuantity = sti(PChar.Plantation.Guardians.Quantity);
	int iGuardiansMaxQuantity = sti(PChar.Plantation.Guardians.MaxQuantity);
	int iGuardiansInShip = GetCrewQuantity(PChar);

	PChar.Plantation.Guardians.Temp.Quantity = sti(GameInterface.HIRE_GUARDIANS_STRING.str);

	if(sti(PChar.Plantation.Guardians.Temp.Quantity) > iGuardiansInShip)
	{
		PChar.Plantation.Guardians.Temp.Quantity = iGuardiansInShip;
	}
	if(sti(PChar.Plantation.Guardians.Temp.Quantity) > iGuardiansMaxQuantity)
	{
		PChar.Plantation.Guardians.Temp.Quantity = iGuardiansMaxQuantity;
	}
	if(sti(PChar.Plantation.Guardians.Temp.Quantity) <= 0)
	{
		PChar.Plantation.Guardians.Temp.Quantity = 0;
	}

	UptadeFields("Guardians");
	PlantationInformation();
}

void SlavesTempUptade()
{
	int iHoldQuantity = GetCargoGoods(PChar, GOOD_SLAVES);
	int iMaxStep = sti(PChar.Plantation.Slaves.MaxQuantity) - sti(PChar.Plantation.Slaves.Quantity);

	PChar.Plantation.Slaves.Temp.Quantity = sti(GameInterface.SLAVES_STRING.str);

	if(sti(PChar.Plantation.Slaves.Temp.Quantity) > iHoldQuantity)
	{
		PChar.Plantation.Slaves.Temp.Quantity = iHoldQuantity;
	}
	if(sti(PChar.Plantation.Slaves.Temp.Quantity) > iMaxStep)
	{
		PChar.Plantation.Slaves.Temp.Quantity = iMaxStep;
	}
	if(sti(PChar.Plantation.Slaves.Temp.Quantity) <= 0)
	{
		PChar.Plantation.Slaves.Temp.Quantity = 0;
	}

	UptadeFields("Slaves");
	PlantationInformation();
}

void FoodTempUptade()
{
	int iMaxStep = sti(PChar.Plantation.Food.MaxQuantity) - sti(PChar.Plantation.Food.Quantity);
	int iHoldQuantity = GetCargoGoods(PChar, GOOD_FOOD);

	PChar.Plantation.Food.Temp.Quantity = sti(GameInterface.FOOD_STRING.str);

	if(sti(PChar.Plantation.Food.Temp.Quantity) > iHoldQuantity)
	{
		PChar.Plantation.Food.Temp.Quantity = iHoldQuantity;
	}
	if(sti(PChar.Plantation.Food.Temp.Quantity) > iMaxStep)
	{
		PChar.Plantation.Food.Temp.Quantity = iMaxStep;
	}
	if(sti(PChar.Plantation.Food.Temp.Quantity) <= 0)
	{
		PChar.Plantation.Food.Temp.Quantity = 0;
	}

	UptadeFields("Food");
	PlantationInformation();
}

void MedicamentTempUptade()
{
	int iMaxStep = sti(PChar.Plantation.Medicament.MaxQuantity) - sti(PChar.Plantation.Medicament.Quantity);
	int iHoldQuantity = GetCargoGoods(PChar, GOOD_MEDICAMENT);

	PChar.Plantation.Medicament.Temp.Quantity = sti(GameInterface.MEDICAMENT_STRING.str);

	if(sti(PChar.Plantation.Medicament.Temp.Quantity) > iHoldQuantity)
	{
		PChar.Plantation.Medicament.Temp.Quantity = iHoldQuantity;
	}
	if(sti(PChar.Plantation.Medicament.Temp.Quantity) > iMaxStep)
	{
		PChar.Plantation.Medicament.Temp.Quantity = iMaxStep;
	}
	if(sti(PChar.Plantation.Medicament.Temp.Quantity) <= 0)
	{
		PChar.Plantation.Medicament.Temp.Quantity = 0;
	}

	UptadeFields("Medicament");
	PlantationInformation();
}

void SugarTempUptade()
{
	PChar.Plantation.Sugar.Temp.Quantity = sti(GameInterface.SUGAR_STRING.str);

	if(sti(GameInterface.SUGAR_STRING.str) > sti(PChar.Plantation.Sugar.Quantity))
	{
		GameInterface.SUGAR_STRING.str = sti(PChar.Plantation.Sugar.Quantity);
		PChar.Plantation.Sugar.Temp.Quantity = sti(GameInterface.SUGAR_STRING.str);
	}

	int iCargo = GetGoodWeightByType(GOOD_SUGAR, sti(GameInterface.SUGAR_STRING.str));

	if(GetCargoFreeSpace(PChar) < 0)
	{
		GameInterface.SUGAR_STRING.str = 0;
		PChar.Plantation.Sugar.Temp.Quantity = sti(GameInterface.SUGAR_STRING.str);
	}
	else
	{
		if(iCargo > GetCargoFreeSpace(PChar))
		{
			GameInterface.SUGAR_STRING.str = GetCharacterFreeSpace(PChar, GOOD_SUGAR);
			PChar.Plantation.Sugar.Temp.Quantity = sti(GameInterface.SUGAR_STRING.str);
		}
	}
	UptadeFields("Sugar");
	PlantationInformation();
}

void CoffeeTempUptade()
{
	PChar.Plantation.Coffee.Temp.Quantity = sti(GameInterface.COFFEE_STRING.str);

	if(sti(GameInterface.COFFEE_STRING.str) > sti(PChar.Plantation.Coffee.Quantity))
	{
		GameInterface.COFFEE_STRING.str = sti(PChar.Plantation.Coffee.Quantity);
		PChar.Plantation.Coffee.Temp.Quantity = sti(GameInterface.COFFEE_STRING.str);
	}

	int iCargo = GetGoodWeightByType(GOOD_COFFEE, sti(GameInterface.COFFEE_STRING.str));

	if(GetCargoFreeSpace(PChar) <= 0)
	{
		GameInterface.COFFEE_STRING.str = 0;
		PChar.Plantation.Coffee.Temp.Quantity = sti(GameInterface.COFFEE_STRING.str);
	}
	else
	{
		if(iCargo > GetCargoFreeSpace(PChar))
		{
			GameInterface.COFFEE_STRING.str = GetCharacterFreeSpace(PChar, GOOD_COFFEE);
			PChar.Plantation.Coffee.Temp.Quantity = sti(GameInterface.COFFEE_STRING.str);
		}
	}
	UptadeFields("Coffee");
	PlantationInformation();
}

void ItemsTempUptade()
{
	int iMaxStep = sti(PChar.Plantation.Items.MaxQuantity) - sti(PChar.Plantation.Items.Quantity);
	int iHoldQuantity = GetCargoGoods(PChar, GOOD_TOOLS);

	PChar.Plantation.Items.Temp.Quantity = sti(GameInterface.ITEMS_STRING.str);

	if(sti(PChar.Plantation.Items.Temp.Quantity) > iMaxStep)
	{
		PChar.Plantation.Items.Temp.Quantity = iMaxStep;
	}

	if(sti(PChar.Plantation.Items.Temp.Quantity) > iHoldQuantity)
	{
		PChar.Plantation.Items.Temp.Quantity = iHoldQuantity;
	}

	if(sti(PChar.Plantation.Items.Temp.Quantity) <= 0)
	{
		PChar.Plantation.Items.Temp.Quantity = 0;
	}

	UptadeFields("Items");
	PlantationInformation();
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void PlantationInformation()
{
	IsEnabledButtons();

	string sPlantationSize = "";
	string sPlantationGoods = "";
	string sPlantationSlavesSpeed = "";

	int iMoneyColor = argb(255,255,255,128);
	int iColorSlavesSpeed = 0;

	float fSpeed = PlantationGetExtractSpeed();
	if(fSpeed >= 7.0)
	{
		sPlantationSlavesSpeed = "Хорошая";
		iColorSlavesSpeed = argb(255,128,255,128);
	}
	if(fSpeed < 5.0 && fSpeed >= 2.0)
	{
		sPlantationSlavesSpeed = "Нормальная";
		iColorSlavesSpeed = argb(255,255,255,255);
	}
	if(fSpeed < 2.0)
	{
		sPlantationSlavesSpeed = "Медленная";
		iColorSlavesSpeed = argb(255,255,128,128);
	}

	if(PChar.Plantation.Size == 1)
	{
		sPlantationSize = "Маленькая";
		sPlantationGoods = "Сахар";
	}
	if(PChar.Plantation.Size == 2)
	{
		sPlantationSize = "Большая";
		sPlantationGoods = "Сахар и Кофе";
	}

	int iCostMoraleUp = GetCostForMoraleUp();
	int iCostPlantationUp = sti(PChar.Plantation.ResizeMoney);

	//-----------------------------------------------------------------------------------------------------------------

	// CreateImage("GuardiansHeader", "MAIN_ICONS", "skillborder", 14,188,266,218);
	// CreateImage("FoodHeader", "MAIN_ICONS", "skillborder", 279,224,531,256);
	// CreateImage("MedicamentHeader", "MAIN_ICONS", "skillborder", 279,406,531,438);
	// CreateImage("ItemsHeader", "MAIN_ICONS", "skillborder", 14,393,266,424);

	CreateString(true,"InfromationHeader", "Информация о плантации", FONT_CAPTION, COLOR_NORMAL, 138,40,SCRIPT_ALIGN_CENTER, 1.4);
	CreateString(true,"SlavesHeader", "Рабы", FONT_CAPTION, COLOR_NORMAL, 400,39,SCRIPT_ALIGN_CENTER, 1.5);
	CreateString(true,"SugarHeader", "Добыча сахара", FONT_CAPTION, COLOR_NORMAL, 665,39,SCRIPT_ALIGN_CENTER, 1.5);
	CreateString(true,"CoffeeHeader", "Добыча кофе", FONT_CAPTION, COLOR_NORMAL, 665,329,SCRIPT_ALIGN_CENTER, 1.5);
	CreateString(true,"GuardiansHeader", "Надсмотрщики", FONT_CAPTION, COLOR_NORMAL, 135,187,SCRIPT_ALIGN_CENTER, 1.5);
	CreateString(true,"FoodHeader", "Провиант", FONT_CAPTION, COLOR_NORMAL, 400,223,SCRIPT_ALIGN_CENTER, 1.5);
	CreateString(true,"MedicamentHeader", "Лекарства", FONT_CAPTION, COLOR_NORMAL, 400,407,SCRIPT_ALIGN_CENTER, 1.5);
	CreateString(true,"InstrumentsHeader", "Инструменты", FONT_CAPTION, COLOR_NORMAL, 135,387,SCRIPT_ALIGN_CENTER, 1.5);

	//CreateImage("CharacterMoney", "MAIN_ICONS", "skillborder", 279,568,531,587);
	//CreateString(true,"CharacterMoney", "Ваше золото: " + sti(PChar.money), FONT_NORMAL, iMoneyColor, 400,570,SCRIPT_ALIGN_CENTER, 0.9);

	//-----------------------------------------------------------------------------------------------------------------

	CreateString(true,"PlantationSize", "Размер плантации: ", FONT_NORMAL, COLOR_NORMAL, 20,90,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"PlantationSizeContinue", sPlantationSize, FONT_NORMAL, COLOR_NORMAL, 170,90,SCRIPT_ALIGN_LEFT, 1.0);

	CreateString(true,"PlantationGoods", "Добывает: ", FONT_NORMAL, COLOR_NORMAL, 20,120,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"PlantationGoodsContinue", sPlantationGoods, FONT_NORMAL, COLOR_NORMAL, 170,120,SCRIPT_ALIGN_LEFT, 1.0);

	CreateString(true,"PlantationSlavesSpeed", "Скорость добычи: ", FONT_NORMAL, COLOR_NORMAL, 20,150,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"PlantationSlavesSpeedContinue", sPlantationSlavesSpeed, FONT_NORMAL, iColorSlavesSpeed, 170,150,SCRIPT_ALIGN_LEFT, 1.0);

	/*
	CreateString(true,"PlantationSlavesHealth", "Состояние рабов: ", FONT_NORMAL, COLOR_NORMAL, 20,155,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"PlantationSlavesHealthContinue", sPlantationSlavesHealth, FONT_NORMAL, iColorSlavesHealth, 170,155,SCRIPT_ALIGN_LEFT, 1.0);

	CreateString(true,"PlantationSlavesMorale", "Мораль рабов: ", FONT_NORMAL, COLOR_NORMAL, 20,180,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"PlantationSlavesMoraleContinue", sPlantationSlavesMorale, FONT_NORMAL, iColorSlavesMorale, 170,180,SCRIPT_ALIGN_LEFT, 1.0);

	CreateString(true,"PlantationSlavesMoraleUpPrice", "Поднять мораль: ", FONT_NORMAL, COLOR_NORMAL, 20,205,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"PlantationSlavesMoraleUpPriceContinue", "" + iCostMoraleUp, FONT_NORMAL, argb(255,255,192,192), 170,205,SCRIPT_ALIGN_LEFT, 1.0);

	if(iSlavesMorale >= 90)
	{
		SetSelectable("MORALE_UP", false);
		CreateString(true,"PlantationSlavesMoraleUpPriceContinue", "0", FONT_NORMAL, argb(255,255,192,192), 170,205,SCRIPT_ALIGN_LEFT, 1.0);
	}
	else
	{
		if(sti(PChar.money) < GetCostForMoraleUp() || GetCostForMoraleUp() <= 0)
		{
			SetSelectable("MORALE_UP", false);
		}
		else
		{
			SetSelectable("MORALE_UP", true);
		}
	}
	*/

	//-----------------------------------------------------------------------------------------------------------------

	int iGuardiansQuantity = sti(PChar.Plantation.Guardians.Quantity);
	int iGuardiansMaxQuantity = sti(PChar.Plantation.Guardians.MaxQuantity);
	int iGuardiansTempQuantity = sti(PChar.Plantation.Guardians.Temp.Quantity);
	int iGuardiansInShip = GetCrewQuantity(PChar);

	GameInterface.HIRE_GUARDIANS_STRING.str = sti(PChar.Plantation.Guardians.Temp.Quantity);

	CreateString(true,"GuardiansQuantity", "Количество: ", FONT_NORMAL, COLOR_NORMAL, 20,230,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"GuardiansQuantityContinue", iGuardiansQuantity, FONT_NORMAL, COLOR_NORMAL, 170,230,SCRIPT_ALIGN_LEFT, 1.0);

	CreateString(true,"GuardiansMaxQuantity", "Макс. количество: ", FONT_NORMAL, COLOR_NORMAL, 20,250,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"GuardiansMaxQuantityContinue", iGuardiansMaxQuantity, FONT_NORMAL, COLOR_NORMAL, 170,250,SCRIPT_ALIGN_LEFT, 1.0);

	CreateString(true,"GuardiansInShip", "Команды на корабле: ", FONT_NORMAL, COLOR_NORMAL, 20,270,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"GuardiansInShipContinue", "" + iGuardiansInShip, FONT_NORMAL, COLOR_NORMAL, 170,270,SCRIPT_ALIGN_LEFT, 1.0);

	//CreateImage("GuardiansTransfer", "MAIN_ICONS", "skillborder", 80,510,200,542);
	//CreateString(true,"GuardiansHireQuantityTransfer", "" + iGuardiansTempQuantity, FONT_CAPTION, COLOR_NORMAL, 140,509,SCRIPT_ALIGN_CENTER, 1.5);

	//-----------------------------------------------------------------------------------------------------------------

	int iItemsQuantity = sti(PChar.Plantation.Items.Quantity);
	int iItemsMaxQuantity = sti(PChar.Plantation.Items.MaxQuantity);
	int itemsTempQuantity = sti(PChar.Plantation.Items.Temp.Quantity);
	int iItemsInShip = GetCargoGoods(PChar, GOOD_TOOLS);

	GameInterface.ITEMS_STRING.str = sti(PChar.Plantation.Items.Temp.Quantity);

	CreateString(true,"ItemsQuantity", "Количество: ", FONT_NORMAL, COLOR_NORMAL, 20,435,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"ItemsQuantityContinue", iItemsQuantity, FONT_NORMAL, COLOR_NORMAL, 170,435,SCRIPT_ALIGN_LEFT, 1.0);

	CreateString(true,"ItemsMaxQuantity", "Макс. количество: ", FONT_NORMAL, COLOR_NORMAL, 20,455,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"ItemsMaxQuantityContinue", iItemsMaxQuantity, FONT_NORMAL, COLOR_NORMAL, 170,455,SCRIPT_ALIGN_LEFT, 1.0);

	CreateString(true,"ItemsInShip", "На корабле: ", FONT_NORMAL, COLOR_NORMAL, 20,475,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"ItemsInShipContinue", "" + iItemsInShip, FONT_NORMAL, COLOR_NORMAL, 170,475,SCRIPT_ALIGN_LEFT, 1.0);

	//-----------------------------------------------------------------------------------------------------------------

	int iSlavesQuantity = sti(PChar.Plantation.Slaves.Quantity);
	int iSlavesMaxQuantity = sti(PChar.Plantation.Slaves.MaxQuantity);
	int iSlavesTempQuantity = sti(PChar.Plantation.Slaves.Temp.Quantity);

	GameInterface.SLAVES_STRING.str = sti(PChar.Plantation.Slaves.Temp.Quantity);

	CreateString(true,"SlavesQuantity", "Количество: ", FONT_NORMAL, COLOR_NORMAL, 285,80,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"SlavesQuantityContinue", "" + iSlavesQuantity, FONT_NORMAL, COLOR_NORMAL, 465,80,SCRIPT_ALIGN_LEFT, 1.0);

	CreateString(true,"SlavesMaxQuantity", "Макс. количество: ", FONT_NORMAL, COLOR_NORMAL, 285,100,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"SlavesMaxQuantityContinue", "" + iSlavesMaxQuantity, FONT_NORMAL, COLOR_NORMAL, 465,100,SCRIPT_ALIGN_LEFT, 1.0);

	CreateString(true,"SlavesInHold", "Рабов в трюме: ", FONT_NORMAL, COLOR_NORMAL, 285,120,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"SlavesInHoldContinue", "" + GetCargoGoods(PChar, GOOD_SLAVES), FONT_NORMAL, COLOR_NORMAL, 465,120,SCRIPT_ALIGN_LEFT, 1.0);

	//CreateImage("SlavesTransfer", "MAIN_ICONS", "skillborder", 340,145,470,177);
	//CreateString(true,"SlavesQuantityTransfer", "" + iSlavesTempQuantity, FONT_CAPTION, COLOR_NORMAL, 405,145,SCRIPT_ALIGN_CENTER, 1.5);

	//-----------------------------------------------------------------------------------------------------------------

	int iFoodMax = sti(PChar.Plantation.Food.MaxQuantity);
	int iFoodQuantity = sti(PChar.Plantation.Food.Quantity);
	int iFoodTempQuantity = sti(PChar.Plantation.Food.Temp.Quantity);
	int iFoodDays = GetPlantationFoodDays();

	GameInterface.FOOD_STRING.str = sti(PChar.Plantation.Food.Temp.Quantity);

	string sFoodDays = "Провианта на плантации на " + iFoodDays + " нед.";

	CreateString(true,"FoodQuantity", "Количество: ", FONT_NORMAL, COLOR_NORMAL, 285,260,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"FoodQuantityContinue", "" + iFoodQuantity + "/" + iFoodMax, FONT_NORMAL, COLOR_NORMAL, 465,260,SCRIPT_ALIGN_LEFT, 1.0);

	CreateString(true,"FoodInHold", "Провианта в трюме: ", FONT_NORMAL, COLOR_NORMAL, 285,280,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"FoodInHoldContinue", "" + GetCargoGoods(PChar, GOOD_FOOD), FONT_NORMAL, COLOR_NORMAL, 465,280,SCRIPT_ALIGN_LEFT, 1.0);

	CreateString(true,"FoodDays", sFoodDays, FONT_NORMAL, COLOR_NORMAL, 285,300,SCRIPT_ALIGN_LEFT, 1.0);

	//CreateImage("FoodTransfer", "MAIN_ICONS", "skillborder", 340,322,470,354);
	//CreateString(true,"FoodQuantityTransfer", "" + iFoodTempQuantity, FONT_CAPTION, COLOR_NORMAL, 405,320,SCRIPT_ALIGN_CENTER, 1.5);

	//-----------------------------------------------------------------------------------------------------------------

	int iMedicamentMax = sti(PChar.Plantation.Medicament.MaxQuantity);
	int iMedicamentQuantity = sti(PChar.Plantation.Medicament.Quantity);
	int iMedicamentTempQuantity = sti(PChar.Plantation.Medicament.Temp.Quantity);
	int iMedicamentDays = GetPlantationMedicamentDays();

	GameInterface.MEDICAMENT_STRING.str = sti(PChar.Plantation.Medicament.Temp.Quantity);

	string sMedicamentDays = "Лекарств на плантации на " + iMedicamentDays + " нед.";

	CreateString(true,"MedicamentQuantity", "Количество: ", FONT_NORMAL, COLOR_NORMAL, 285,440,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"MedicamentQuantityContinue", "" + iMedicamentQuantity + "/" + iMedicamentMax, FONT_NORMAL, COLOR_NORMAL, 465,440,SCRIPT_ALIGN_LEFT, 1.0);

	CreateString(true,"MedicamentInHold", "Лекарств в трюме: ", FONT_NORMAL, COLOR_NORMAL, 285,460,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"MedicamentInHoldContinue", "" + GetCargoGoods(PChar, GOOD_MEDICAMENT), FONT_NORMAL, COLOR_NORMAL, 465,460,SCRIPT_ALIGN_LEFT, 1.0);

	CreateString(true,"MedicamentDays", sMedicamentDays, FONT_NORMAL, COLOR_NORMAL, 285,480,SCRIPT_ALIGN_LEFT, 1.0);

	//CreateImage("MedicamentTransfer", "MAIN_ICONS", "skillborder", 340,495,470,527);
	//CreateString(true,"MedicamentQuantityTransfer", "" + iMedicamentTempQuantity, FONT_CAPTION, COLOR_NORMAL, 405,495,SCRIPT_ALIGN_CENTER, 1.5);

	//-----------------------------------------------------------------------------------------------------------------

	int iSugarWeightColor = argb(255,255,128,128);
	int iCoffeeWeightColor = argb(255,255,128,128);

	int iSugarSpaceColor = argb(255,128,255,128);
	int iCoffeeSpaceColor = argb(255,128,255,128);

	if(sti(PChar.Plantation.Sugar.Temp.Quantity) == 0)
	{
		iSugarWeightColor = argb(255,255,255,255);
	}
	if(sti(PChar.Plantation.Coffee.Temp.Quantity) == 0)
	{
		iCoffeeWeightColor = argb(255,255,255,255);
	}

	if(GetCargoFreeSpace(PChar) <= 1)
	{
		iSugarSpaceColor = argb(255,255,128,128);
		iCoffeeSpaceColor = argb(255,255,128,128);
	}

	int iMaxSugarQuantity = sti(PChar.Plantation.Sugar.MaxQuantity);
	int iMaxCoffeeQuantity = sti(PChar.Plantation.Coffee.MaxQuantity);

	//-----------------------------------------------------------------------------------------------------------------

	CreateImage("SugarPicture", "GOODS", "Sugar", 550,78,582,110);

	GameInterface.SUGAR_STRING.str = sti(PChar.Plantation.Sugar.Temp.Quantity);

	int iSugarQuantity = sti(PChar.Plantation.Sugar.Quantity);
	int iSugarTempQuantity = sti(PChar.Plantation.Sugar.Temp.Quantity);

	CreateString(true,"SugarQuantity", iSugarQuantity + "/" + iMaxSugarQuantity, FONT_BOLD_NUMBERS, COLOR_MONEY, 610,83,SCRIPT_ALIGN_LEFT,1.0);

	CreateImage("SugarWeight", "ICONS", "weight icon", 550,114,582,146);
	int iSugarCargo = GetGoodWeightByType(GOOD_SUGAR, iSugarTempQuantity);

	CreateString(true,"SugarWeight", iSugarCargo, FONT_BOLD_NUMBERS, iSugarWeightColor, 610,120,SCRIPT_ALIGN_LEFT,1.0);

	CreateImage("Sugar_ShipCapacity", "ICONS", "ship capacity icon", 552,150,584,182);
	CreateString(true,"Sugar_ShipCapacity", GetCargoFreeSpace(PChar) + "/" +  GetCargoMaxSpace(PChar), FONT_BOLD_NUMBERS, iSugarSpaceColor, 610,157,SCRIPT_ALIGN_LEFT,1.0);


	//CreateImage("SugarTransfer", "MAIN_ICONS", "skillborder", 600,173,730,205);
	//CreateString(true,"SugarQuantityTransfer", "" + iSugarTempQuantity, FONT_CAPTION, COLOR_NORMAL, 665,172,SCRIPT_ALIGN_CENTER, 1.5);

	//-----------------------------------------------------------------------------------------------------------------

	if(PChar.Plantation.Size == 2)
	{
		SetNodeUsing("BORDERS_2", true);

		GameInterface.COFFEE_STRING.str = sti(PChar.Plantation.Coffee.Temp.Quantity);

		int iCoffeeQuantity = sti(PChar.Plantation.Coffee.Quantity);
		int iCoffeeTempQuantity = sti(PChar.Plantation.Coffee.Temp.Quantity);

		CreateImage("CoffeePicture", "GOODS", "Coffee", 550,368,582,400);

		CreateString(true,"CoffeeQuantity", iCoffeeQuantity + "/" + iMaxCoffeeQuantity, FONT_BOLD_NUMBERS, COLOR_MONEY, 610,375,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("CoffeeWeight", "ICONS", "weight icon", 550,405,582,437);
		int iCoffeeCargo = GetGoodWeightByType(GOOD_COFFEE, iCoffeeTempQuantity);

		CreateString(true,"CoffeeWeight", iCoffeeCargo, FONT_BOLD_NUMBERS, iCoffeeWeightColor, 610,412,SCRIPT_ALIGN_LEFT,1.0);

		CreateImage("Coffee_ShipCapacity", "ICONS", "ship capacity icon", 552,441,584,473);
		CreateString(true,"Coffee_ShipCapacity", GetCargoFreeSpace(PChar) + "/" +  GetCargoMaxSpace(PChar), FONT_BOLD_NUMBERS, iCoffeeSpaceColor, 610,448,SCRIPT_ALIGN_LEFT,1.0);

	}
	else
	{
		GameInterface.pictures.CoffeePicture.tex = "";
		GameInterface.pictures.CoffeePicture.pic = "";
		GameInterface.pictures.CoffeeTransfer.tex = "";
		GameInterface.pictures.CoffeeTransfer.pic = "";
		GameInterface.strings.CoffeeHeader = "";
		GameInterface.strings.CoffeeQuantity = "";
		GameInterface.strings.CoffeeQuantityContinue = "";
		GameInterface.strings.CoffeeQuantityTransfer = "";

		SetNodeUsing("FRAME4", false);
		SetNodeUsing("BORDERS_2", false);
		SetNodeUsing("COFFEE_STRING", false);
		SetNodeUsing("COFFEE_STRING_VIDEO", false);
		SetNodeUsing("COFFEE_GIVE", false);
		SetNodeUsing("COFFEE_SBROS", false);
		SetNodeUsing("COFFEE_LEFT", false);
		SetNodeUsing("COFFEE_RIGHT", false);
		SetNodeUsing("COFFEE_LEFT_ALL", false);
		SetNodeUsing("COFFEE_RIGHT_ALL", false);
	}

	//-----------------------------------------------------------------------------------------------------------------
	/*
	string sInstrument = "";

	int iInstrumentColor = 0;

	if(PChar.Plantation.Instrument == "Bad")
	{
		sInstrument = "Плохие";
		iInstrumentColor = argb(255,255,192,192);
	}
	if(PChar.Plantation.Instrument == "Normal")
	{
		sInstrument = "Обычные";
		iInstrumentColor = argb(255,255,255,255);
	}
	if(PChar.Plantation.Instrument == "Good")
	{
		sInstrument = "Хорошие";
		iInstrumentColor = argb(255,128,255,128);
	}

	string sSelectInstrument = "";

	if(PChar.Plantation.Interface.Instrument == "Bad")
	{
		sSelectInstrument = "Плохие";
	}
	if(PChar.Plantation.Interface.Instrument == "Normal")
	{
		sSelectInstrument = "Обычные";
	}
	if(PChar.Plantation.Interface.Instrument == "Good")
	{
		sSelectInstrument = "Хорошие";
	}

	CreateString(true,"Instrument", "Текущие инструменты: ", FONT_NORMAL, COLOR_NORMAL, 550,490,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"InstrumentContinue", sInstrument, FONT_NORMAL, iInstrumentColor, 700,490,SCRIPT_ALIGN_LEFT, 1.0);

	CreateString(true,"InstrumentPrice", "Цена: ", FONT_NORMAL, COLOR_NORMAL, 550,507,SCRIPT_ALIGN_LEFT, 1.0);
	CreateString(true,"InstrumentPriceContinue", "" + iSelectInstrumentsPrice, FONT_NORMAL, argb(255,255,192,192), 700,507,SCRIPT_ALIGN_LEFT, 1.0);


	int iSelectInstrumentX = 0;

	if(sSelectInstrument == "Плохие" || sSelectInstrument == "Обычные")
	{
		iSelectInstrumentX = 632;
	}
	if(sSelectInstrument == "Хорошие")
	{
		iSelectInstrumentX = 625;
	}

	CreateString(true,"SecectInstrumentString", sSelectInstrument, FONT_CAPTION, COLOR_NORMAL, iSelectInstrumentX,523,SCRIPT_ALIGN_LEFT, 1.0);

	if(1==1)
	{
		SetSelectable("INSTRUMENTS_INSTALL", false);
	}
	else
	{
		SetSelectable("INSTRUMENTS_INSTALL", true);
	}

	*/
}

int GetGoodsDaysForSlaves(bool bFood)
{
	int iQuantity = 0;
	int iSlavesQuantity = sti(PChar.Plantation.Slaves.Quantity);

	if(bFood)
	{
		int iFood = sti(PChar.Plantation.Food.Quantity);

		if(iFood == 0)
		{
			iQuantity = 0;
			return iQuantity;
		}

		iQuantity = iFood / (iSlavesQuantity / 6);
	}
	else
	{
		int iMedicament = sti(PChar.Plantation.Medicament.Quantity);

		if(iMedicament == 0)
		{
			iQuantity = 0;
			return iQuantity;
		}

		iQuantity = iMedicament / (iSlavesQuantity / 8);
	}

	if(iQuantity < 0)
	{
		iQuantity = 0;
	}

	return iQuantity;
}

void UptadeFields(string sType)
{
	int iGuardiansTempQuantity = sti(PChar.Plantation.Guardians.Temp.Quantity);
	int iSlavesTempQuantity = sti(PChar.Plantation.Slaves.Temp.Quantity);
	int iFoodTempQuantity = sti(PChar.Plantation.Food.Temp.Quantity);
	int iMedicamentTempQuantity = sti(PChar.Plantation.Medicament.Temp.Quantity);
	int iSugarTempQuantity = sti(PChar.Plantation.Sugar.Temp.Quantity);
	int iCoffeeTempQuantity = sti(PChar.Plantation.Coffee.Temp.Quantity);
	int iItemsTempQuantity = sti(PChar.Plantation.Items.Temp.Quantity);

	if(sType == "Guardians")
	{
		PChar.Plantation.Guardians.Temp.Quantity = sti(PChar.Plantation.Guardians.Temp.Quantity);
		PChar.Plantation.Slaves.Temp.Quantity = 0;
		PChar.Plantation.Food.Temp.Quantity = 0;
		PChar.Plantation.Medicament.Temp.Quantity = 0;
		PChar.Plantation.Sugar.Temp.Quantity = 0;
		PChar.Plantation.Coffee.Temp.Quantity = 0;
		PChar.Plantation.Items.Temp.Quantity = 0;
	}

	if(sType == "Slaves")
	{
		PChar.Plantation.Slaves.Temp.Quantity = sti(PChar.Plantation.Slaves.Temp.Quantity);
		PChar.Plantation.Guardians.Temp.Quantity = 0;
		PChar.Plantation.Food.Temp.Quantity = 0;
		PChar.Plantation.Medicament.Temp.Quantity = 0;
		PChar.Plantation.Sugar.Temp.Quantity = 0;
		PChar.Plantation.Coffee.Temp.Quantity = 0;
		PChar.Plantation.Items.Temp.Quantity = 0;
	}

	if(sType == "Food")
	{
		PChar.Plantation.Food.Temp.Quantity = sti(PChar.Plantation.Food.Temp.Quantity);
		PChar.Plantation.Slaves.Temp.Quantity = 0;
		PChar.Plantation.Guardians.Temp.Quantity = 0;
		PChar.Plantation.Medicament.Temp.Quantity = 0;
		PChar.Plantation.Sugar.Temp.Quantity = 0;
		PChar.Plantation.Coffee.Temp.Quantity = 0;
		PChar.Plantation.Items.Temp.Quantity = 0;
	}

	if(sType == "Medicament")
	{
		PChar.Plantation.Medicament.Temp.Quantity = sti(PChar.Plantation.Medicament.Temp.Quantity);
		PChar.Plantation.Slaves.Temp.Quantity = 0;
		PChar.Plantation.Food.Temp.Quantity = 0;
		PChar.Plantation.Guardians.Temp.Quantity = 0;
		PChar.Plantation.Sugar.Temp.Quantity = 0;
		PChar.Plantation.Coffee.Temp.Quantity = 0;
		PChar.Plantation.Items.Temp.Quantity = 0;
	}

	if(sType == "Sugar")
	{
		PChar.Plantation.Sugar.Temp.Quantity = sti(PChar.Plantation.Sugar.Temp.Quantity);
		PChar.Plantation.Slaves.Temp.Quantity = 0;
		PChar.Plantation.Food.Temp.Quantity = 0;
		PChar.Plantation.Medicament.Temp.Quantity = 0;
		PChar.Plantation.Guardians.Temp.Quantity = 0;
		PChar.Plantation.Coffee.Temp.Quantity = 0;
		PChar.Plantation.Items.Temp.Quantity = 0;
	}

	if(sType == "Coffee")
	{
		PChar.Plantation.Coffee.Temp.Quantity = sti(PChar.Plantation.Coffee.Temp.Quantity);
		PChar.Plantation.Slaves.Temp.Quantity = 0;
		PChar.Plantation.Food.Temp.Quantity = 0;
		PChar.Plantation.Medicament.Temp.Quantity = 0;
		PChar.Plantation.Sugar.Temp.Quantity = 0;
		PChar.Plantation.Guardians.Temp.Quantity = 0;
		PChar.Plantation.Items.Temp.Quantity = 0;
	}

	if(sType == "Items")
	{
		PChar.Plantation.Items.Temp.Quantity = sti(PChar.Plantation.Items.Temp.Quantity);
		PChar.Plantation.Slaves.Temp.Quantity = 0;
		PChar.Plantation.Guardians.Temp.Quantity = 0;
		PChar.Plantation.Medicament.Temp.Quantity = 0;
		PChar.Plantation.Sugar.Temp.Quantity = 0;
		PChar.Plantation.Coffee.Temp.Quantity = 0;
	}

	if(sType == "All")
	{
		PChar.Plantation.Coffee.Temp.Quantity = 0;
		PChar.Plantation.Slaves.Temp.Quantity = 0;
		PChar.Plantation.Food.Temp.Quantity = 0;
		PChar.Plantation.Medicament.Temp.Quantity = 0;
		PChar.Plantation.Sugar.Temp.Quantity = 0;
		PChar.Plantation.Guardians.Temp.Quantity = 0;
		PChar.Plantation.Items.Temp.Quantity = 0;
	}

	PlantationInformation();
}

void IsEnabledButtons()
{
	int iGuardiansTempQuantity = sti(PChar.Plantation.Guardians.Temp.Quantity);
	int iSlavesTempQuantity = sti(PChar.Plantation.Slaves.Temp.Quantity);
	int iFoodTempQuantity = sti(PChar.Plantation.Food.Temp.Quantity);
	int iMedicamentTempQuantity = sti(PChar.Plantation.Medicament.Temp.Quantity);
	int iSugarTempQuantity = sti(PChar.Plantation.Sugar.Temp.Quantity);
	int iCoffeeTempQuantity = sti(PChar.Plantation.Coffee.Temp.Quantity);
	int iItemsTempQuantity = sti(PChar.Plantation.Items.Temp.Quantity);

	if(iItemsTempQuantity == 0)
	{
		SetSelectable("ITEMS_ADD", false);
	}
	else
	{
		SetSelectable("ITEMS_ADD", true);
	}

	if(iGuardiansTempQuantity == 0)
	{
		SetSelectable("GUARDIANS_HIRE", false);
	}
	else
	{
		SetSelectable("GUARDIANS_HIRE", true);
	}

	if(iSlavesTempQuantity == 0)
	{
		SetSelectable("SLAVES_TRANSFER", false);
	}
	else
	{
		SetSelectable("SLAVES_TRANSFER", true);
	}

	if(iFoodTempQuantity == 0)
	{
		SetSelectable("FOOD_TRANSFER", false);
	}
	else
	{
		SetSelectable("FOOD_TRANSFER", true);
	}

	if(iMedicamentTempQuantity == 0)
	{
		SetSelectable("MEDICAMENT_TRANSFER", false);
	}
	else
	{
		SetSelectable("MEDICAMENT_TRANSFER", true);
	}

	if(iSugarTempQuantity == 0)
	{
		SetSelectable("SUGAR_GIVE", false);
	}
	else
	{
		SetSelectable("SUGAR_GIVE", true);
	}

	if(iCoffeeTempQuantity == 0)
	{
		SetSelectable("COFFEE_GIVE", false);
	}
	else
	{
		SetSelectable("COFFEE_GIVE", true);
	}
}
