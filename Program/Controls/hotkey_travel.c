void HKT_Button(string sHKB) // быстрый переход
{
	int curLocIdx, i; 
	String locID, sCityID;
	bool bOk;
	
	curLocIdx = FindLoadedLocation();
	sCityID = Locations[curLocIdx].fastreload;
	locID = strcut(sHKB, 4 , strlen(sHKB)-1);
	// --> проверка запретов перехода
	bOk = true;
	if(LAi_group_IsActivePlayerAlarm()) bOk = false;
	if(!LAi_IsCharacterControl(pchar)) bOk = false;
	if(bDisableFastReload)	bOk = false;
	if(!IsEnableFastTravel()) bOk = false;
	if (chrDisableReloadToLocation) bOk = false;
	if (sHKB != "Fast_port" && !CheckFastJump(Locations[curLocIdx].id, sCityID + locID)) bOk = false;
	if (sHKB == "Fast_port" && !CheckFastJump(Locations[curLocIdx].id, pchar.location.from_sea)) bOk = false;
	if (!bBettaTestMode && bOk) // проверка города на враждебность
	{
		string sNation = Colonies[FindColony(loadedLocation.fastreload)].nation;
		if (sNation != "none")
		{
			i = sti(sNation);
			bOk = (GetNationRelation2MainCharacter(i) == RELATION_ENEMY) || GetRelation2BaseNation(i) == RELATION_ENEMY;
			if (bOk && (i != PIRATE))
			{
				bOk = false;
			}
			else
			{
				bOk = true;
			}
		}
	}
	// <--
	if(bOk)
	{
		if (sHKB == "Fast_port")
			PlayerFastTravel(curLocIdx, pchar.location.from_sea, "reload1");
			else PlayerFastTravel(curLocIdx, sCityID + locID, "");
	}
	else
	{
		Log_info(XI_ConvertString("Вы во враждебном городе!")); 
		PlaySound("interface\knock.wav");
	}	
	if(pchar.location == sCityID + locID) 
	{
		Log_info(XI_ConvertString("You are already there")); 
		PlaySound("interface\knock.wav");
	}
	if (sHKB == "Fast_port" && pchar.location == pchar.location.from_sea) 
	{
		Log_info(XI_ConvertString("You are already there")); 
		PlaySound("interface\knock.wav");
	}
}	