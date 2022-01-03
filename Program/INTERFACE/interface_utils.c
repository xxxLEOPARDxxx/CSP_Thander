string sEType[10] = {"blade","spyglass","cirass","BackPack","talisman","jewelry_indian_left","jewelry_indian_right","indian_center","idols_left","idols_right"};
int CheckItemInSets(ref _character, string sItemName)
{
	if (!checkattribute(_character, "selectedSet")) return 0; //у этого персонажа не было сохранено комплектов
	int i, q;
	string sSET, sTemp;
	for(i=1;i<10;i++)
	{
		if (_character.selectedSet == i) continue;//текущий комплект уже скрыт в списке перемещения предметов
		sSET = "Set" + i;
		if (!checkattribute(_character, sSET)) continue; //нет комплекта
		for (q=0;q<10;q++)
		{
			sTemp = sEType[q];
			if(_character.(sSET).(sTemp) == sItemName && GetCharacterEquipByGroup(_character, sTemp) != sItemName) return i;
				//предмет есть в неактивном комплекте И не экипирован прямо сейчас						//возвращаем номер комплекта
		}
	}
	return 0;
}
//---------------------------------------------------------------------------------------------------
// scrollimage
//---------------------------------------------------------------------------------------------------
void FillScrollImageWithCompanionShips(string sNodeName, int iNotUsed)
{

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

		if(cn!= -1)
		{
			/*if(GetShipRemovable(&characters[cn]) == 0 && cn != nMainCharacterIndex)
			{
				isPossibleToFill = 0;
			}
			else
			{  */
				isPossibleToFill = 1;
			//}
			if(isPossibleToFill == 1)
			{
				iShipType = sti(characters[cn].ship.type);
				if(iShipType != SHIP_NOTUSED)
				{
					//Boyer change #20170430-03
					//iShipType = sti(RealShips[iShipType].basetype);

					if (iShipType!= SHIP_NOTUSED)
					{
					    //Boyer change #20170430-03
						//shipName = ShipsTypes[iShipType].Name;
						attributeName = "pic" + (iListSize+1);

						//Boyer change #20170430-03
                        ref rBaseShip = GetRealShip(iShipType);
                        iShipType = rBaseShip.basetype;
                        //#20170430-03 Companion ships are appended with a "1"
                        if(strlen(rBaseShip.Name)>2)
                            shipName = strcut(rBaseShip.Name, 0, strlen(rBaseShip.Name)-2);
                        else
                            shipName = "";


						shipName = ShipsTypes[iShipType].Name;
						attributeName = "pic" + (iListSize+1);

						GameInterface.(sNodeName).(attributeName).companionIndex = cn;
						GameInterface.(sNodeName).(attributeName).img1 = "ship";
						GameInterface.(sNodeName).(attributeName).tex1 = FindFaceGroupNum(sNodeName + ".ImagesGroup","SHIPS_"+shipName);

						iListSize++;
					}
				}
			}
			/*else
			{
				attributeName = "pic" + (i+1);
				GameInterface.(sNodeName).(attributeName).tex1= 0;
			}  */
		}
		/*else
		{
			attributeName = "pic" + (i+1);
			GameInterface.(sNodeName).(attributeName).tex1= 0;
		} */
	}

	GameInterface.(sNodeName).ListSize = iListSize;
	//GameInterface.(sNodeName).NotUsed = iNotUsed;
	GameInterface.SHIPS_SCROLL.NotUsed = iNotUsed - iListSize + 1;

	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_SCROLL_CHANGE, sNodeName, -1);
}

void FillScrollImageWithCompanions(string sNodeName, int iNotUsed)
{

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
	for(int i= 1; i< COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);

		if(cn!= -1)
		{
			/*if(GetShipRemovable(&characters[cn]) == 0 && cn != nMainCharacterIndex)
			{
				isPossibleToFill = 0;
			}
			else
			{  */
				isPossibleToFill = 1;
			//}
			if(isPossibleToFill == 1)
			{
				iShipType = sti(characters[cn].ship.type);
				if(iShipType != SHIP_NOTUSED)
				{
					//Boyer change #20170430-03
					//iShipType = sti(RealShips[iShipType].basetype);

					if (iShipType!= SHIP_NOTUSED)
					{
					    //Boyer change #20170430-03
						//shipName = ShipsTypes[iShipType].Name;
						attributeName = "pic" + (iListSize+1);

						//Boyer change #20170430-03
                        ref rBaseShip = GetRealShip(iShipType);
                        iShipType = rBaseShip.basetype;
                        //#20170430-03 Companion ships are appended with a "1"
                        if(strlen(rBaseShip.Name)>2)
                            shipName = strcut(rBaseShip.Name, 0, strlen(rBaseShip.Name)-2);
                        else
                            shipName = "";


						shipName = ShipsTypes[iShipType].Name;
						attributeName = "pic" + (iListSize+1);

						GameInterface.(sNodeName).(attributeName).companionIndex = cn;
						GameInterface.(sNodeName).(attributeName).img1 = "ship";
						GameInterface.(sNodeName).(attributeName).tex1 = FindFaceGroupNum(sNodeName + ".ImagesGroup","SHIPS_"+shipName);

						iListSize++;
					}
				}
			}
			/*else
			{
				attributeName = "pic" + (i+1);
				GameInterface.(sNodeName).(attributeName).tex1= 0;
			}  */
		}
		/*else
		{
			attributeName = "pic" + (i+1);
			GameInterface.(sNodeName).(attributeName).tex1= 0;
		} */
	}

	GameInterface.(sNodeName).ListSize = iListSize;
	//GameInterface.(sNodeName).NotUsed = iNotUsed;
	GameInterface.SHIPS_SCROLL.NotUsed = iNotUsed - iListSize + 1;

	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_SCROLL_CHANGE, sNodeName, -1);
}

void FillScrollImageWithCompanionsUp(string sNodeName, int iNotUsed)
{
	FillShipList(sNodeName + ".ImagesGroup", pchar);

	string attributeName, shipName;
	int iShipType, cn;
	int iListSize = 0;

	int isPossibleToFill = 1;
	for(int i= 1; i< COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);

		if(cn!= -1)
		{
			/*if(GetShipRemovable(&characters[cn]) == 0 && cn != nMainCharacterIndex)
			{
				isPossibleToFill = 0;
			}
			else
			{  */
				isPossibleToFill = 1;
			//}
			if(isPossibleToFill == 1)
			{
				iShipType = sti(characters[cn].ship.type);
				if(iShipType != SHIP_NOTUSED)
				{
					//Boyer change #20170430-03
					//iShipType = sti(RealShips[iShipType].basetype);

					if (iShipType!= SHIP_NOTUSED)
					{
					    //Boyer change #20170430-03
						//shipName = ShipsTypes[iShipType].Name;
						attributeName = "pic" + (iListSize+1);

						//Boyer change #20170430-03
                        ref rBaseShip = GetRealShip(iShipType);
                        iShipType = rBaseShip.basetype;
                        //#20170430-03 Companion ships are appended with a "1"
                        if(strlen(rBaseShip.Name)>2)
                            shipName = strcut(rBaseShip.Name, 0, strlen(rBaseShip.Name)-2);
                        else
                            shipName = "";


						shipName = ShipsTypes[iShipType].Name;
						attributeName = "pic" + (iListSize+1);

						GameInterface.(sNodeName).(attributeName).tex1 = FindFaceGroupNum(sNodeName + ".ImagesGroup","SHIPS_"+shipName);

						iListSize++;
					}
				}
			}
		}
	}
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_SCROLL_CHANGE, sNodeName, -1);
}
//---------------------------------------------------------------------------------------------------
void FillScrollImageWithFaces(string sNodeName, int iNotUsed, bool bCompanions, bool bPassengers)
{

	DeleteAttribute(&GameInterface, sNodeName);
	GameInterface.(sNodeName).current = -1;

	GameInterface.(sNodeName).ImagesGroup.t0 = "EMPTYFACE";
	GameInterface.(sNodeName).BadTex1 = 0;
	GameInterface.(sNodeName).BadPic1 = "emptyface";

	ref refCharacter = pchar;

	int iListSize = 0;
	int cn;
	string attributeName;
	aref pRef,pRef2;
	string PsgAttrName;


	if (bCompanions){

		FillFaceList(sNodeName + ".ImagesGroup", refCharacter, 1); // companions

		for(int n= 0; n< COMPANION_MAX; n++)
		{
			attributeName = "pic" + (iListSize+1);
			cn = GetCompanionIndex(refCharacter, n);

			if(cn!= -1)
			{
				GameInterface.(sNodeName).(attributeName).character = cn;
				GameInterface.(sNodeName).(attributeName).img1 = GetFacePicName(GetCharacter(cn));
				GameInterface.(sNodeName).(attributeName).tex1 = FindFaceGroupNum(sNodeName + ".ImagesGroup","FACE128_"+ characters[cn].FaceID);

				iListSize++;
			}
		}
	}

	if (bPassengers){


		makearef(pRef,refCharacter.Fellows.Passengers);
		FillFaceList(sNodeName + ".ImagesGroup", refCharacter, 2); // passengers

		for(int i= 0; i< GetPassengersQuantity(refCharacter); i++)
		{
			attributeName = "pic" + (iListSize+1);
			PsgAttrName = "id"+(i+1);
			cn = sti(pRef.(PsgAttrName));

			if(cn!=-1 && !CheckAttribute(&characters[cn], "isfree"))
			{
				GameInterface.(sNodeName).(attributeName).character = cn;
				GameInterface.(sNodeName).(attributeName).img1 = GetFacePicName(GetCharacter(cn));
				GameInterface.(sNodeName).(attributeName).tex1 = FindFaceGroupNum(sNodeName + ".ImagesGroup","FACE128_"+ characters[cn].FaceID);

				iListSize++;
			}
		}
	}
	/*
	if (bOfficers)
	{
	makearef(pRef,refCharacter.Fellows.Passengers);

	FillFaceList(sNodeName + ".ImagesGroup", refCharacter, 0); // officers

	for(int o= 0; o< 4; o++)
	{
	attributeName = "pic" + (iListSize+1);
	cn = sti(pRef.(PsgAttrName));
	if(cn!=-1)
	{
	GameInterface.(sNodeName).(attributeName).character = cn;
	GameInterface.(sNodeName).(attributeName).img1 = GetFacePicName(GetCharacter(cn));
	GameInterface.(sNodeName).(attributeName).tex1 = FindFaceGroupNum(sNodeName+ ".ImagesGroup","FACE128_"+ characters[cn].FaceID);

	iListSize++;
	}
	}
	}
	*/
	GameInterface.(sNodeName).ListSize = iListSize;
	GameInterface.(sNodeName).NotUsed = iNotUsed;

	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_SCROLL_CHANGE, sNodeName, -1);
}
/// boal -->
void StartAboveForm(bool _pauseTime)
{
    ChangeShowIntarface();

	EngineLayersOffOn(true);
    if (_pauseTime)
    {
		SetTimeScale(0.0);
	}
	locCameraSleep(true);
	LAi_CharacterDisableDialog(pchar);
}

void EndAboveForm(bool _pauseTime)
{
    if (_pauseTime)
    {
		SetTimeScale(1.0);
		TimeScaleCounter = 0;
	 	DelPerkFromActiveList("TimeSpeed");
	 	DeleteAttribute(pchar, "pause");
	}
	locCameraSleep(false);
	LAi_CharacterEnableDialog(pchar);
	ChangeShowIntarface();
}

void ChangeShowIntarface()
{
    if (bSeaActive && !bAbordageStarted)
    {
        if (!IsEntity(BattleInterface))
        {
            InitBattleInterface();
            StartBattleInterface();
            RefreshBattleInterface();
        }
        else DeleteBattleInterface();
    }
    else
    {
		if (!IsEntity(worldMap))
		{
			if (!bLandInterfaceStart)
	        {
	            StartBattleLandInterface();
	        }
	        else EndBattleLandInterface();
        }
    }
}
// вернуть тип по номеру скрола в ф2 персонаж
string GetOfficerTypeByNum(int nCurScrollNum)
{
    string ret = "";

	switch (nCurScrollNum)
	{
		case 1:
   			ret = "navigator";
		break;

		case 2:
   			ret = "boatswain";
		break;

		case 3:
   			ret = "cannoner";
		break;

		case 4:
   			ret = "doctor";
		break;

		case 5:
   			ret = "treasurer";
		break;

		case 6:
   			ret = "carpenter";
		break;

		//Boyer mod
		/*
		case 7:
  			ret = "fighter";
		break;

		case 8:
   			ret = "fighter";
		break;

		case 9:
   			ret = "fighter";
		break;

		case 10:
			ret = "fighter";
		break;
		//Boyer add
		case 11:
   			ret = "fighter";
		break;

		case 12:
			ret = "fighter";
		break;
		*/
		//default
			ret = "fighter";
		//End Boyer add
	}
	return ret;
}

////////////////////////////// общие методы для форм
void SetOTHERMiniTable(string _tabName, ref _chr)
{
    int     i;
	string  row, skillName, col;
    int     skillVal;

    GameInterface.(_tabName).select = 0;
	GameInterface.(_tabName).hr.td1.str = "";
	for (i=1; i<=5; i++)
	{
	    row = "tr" + i;

	    GameInterface.(_tabName).(row).td1.icon.width = 23;
    	GameInterface.(_tabName).(row).td1.icon.height = 23;
    	GameInterface.(_tabName).(row).td1.icon.offset = "-2, 2";
		GameInterface.(_tabName).(row).td2.align = "left";
		GameInterface.(_tabName).(row).td2.scale = 0.8;
		GameInterface.(_tabName).(row).td2.textoffset = "-2,-1";
		GameInterface.(_tabName).(row).td3.align = "right";
	}
	GameInterface.(_tabName).tr1.UserData.ID = "Rank";
	GameInterface.(_tabName).tr1.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr1.td1.icon.image = "Rank";
	GameInterface.(_tabName).tr1.td2.str = XI_ConvertString("Rank");
	GameInterface.(_tabName).tr1.td3.str = sti(_chr.rank);

	GameInterface.(_tabName).tr2.UserData.ID = "Life";
	GameInterface.(_tabName).tr2.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr2.td1.icon.image = "Life";
	GameInterface.(_tabName).tr2.td2.str = XI_ConvertString("Life");
	GameInterface.(_tabName).tr2.td3.str = MakeInt(LAi_GetCharacterHP(_chr)) + " / " + MakeInt(LAi_GetCharacterMaxHP(_chr));

    GameInterface.(_tabName).tr3.UserData.ID = "Reputation";
	GameInterface.(_tabName).tr3.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr3.td1.icon.image = "Reputation";
	GameInterface.(_tabName).tr3.td2.str = XI_ConvertString("Reputation");
	GameInterface.(_tabName).tr3.td3.str = XI_ConvertString(GetReputationName(sti(_chr.reputation)));
	GameInterface.(_tabName).tr3.td3.scale = 0.8;
	GameInterface.(_tabName).tr3.td3.textoffset = "0,-1";

    GameInterface.(_tabName).tr4.UserData.ID = "Loyality";
	GameInterface.(_tabName).tr4.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr4.td1.icon.image = "Loyality";
	GameInterface.(_tabName).tr4.td2.str = XI_ConvertString("Loyality");
	if (_chr.id == pchar.id)
	{
		GameInterface.(_tabName).tr4.td3.str = "-";
	}
	else
	{
		GameInterface.(_tabName).tr4.td3.str = XI_ConvertString(GetLoyalityName(makeint(GetCharacterLoyality(_chr) * 100 / MAX_LOYALITY)));
	}
	GameInterface.(_tabName).tr4.td3.scale = 0.78;

	GameInterface.(_tabName).tr5.UserData.ID = "weight";
	GameInterface.(_tabName).tr5.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr5.td1.icon.image = "weight";
	GameInterface.(_tabName).tr5.td2.str = XI_ConvertString("weight");
	GameInterface.(_tabName).tr5.td3.str = FloatToString(GetItemsWeight(_chr), 1) + " / "+GetMaxItemsWeight(_chr);
	GameInterface.(_tabName).tr5.td3.scale = 0.8;

	// прорисовка
	Table_UpdateWindow(_tabName);
}
void SetSPECIALMiniTable(string _tabName, ref _chr)
{
    int     i;
	string  row, skillName, col;
    int     diff, skillVal;

    GameInterface.(_tabName).select = 0;
	GameInterface.(_tabName).hr.td1.str = "";
	row = "tr1";
	for (i=1; i<=7; i++)
	{
	    col = "td" + i;
	    skillName = GetSkillNameByTRIdx("SPECIALType", i);

		GameInterface.(_tabName).(row).(col).fontidx = 0;
		//#20170627-01
		GameInterface.(_tabName).(row).(col).scale = 0.65;
		GameInterface.(_tabName).(row).(col).textoffset = "-5,-6";
		GameInterface.(_tabName).(row).(col).str = XI_ConvertString(skillName + "T");
	}
	row = "tr2";
	for (i=1; i<=7; i++)
	{
	    col = "td" + i;
	    skillName = GetSkillNameByTRIdx("SPECIALType", i);
        skillVal = GetCharacterSPECIAL(_chr, skillName);
		GameInterface.(_tabName).(row).(col).fontidx = 1;
		//#20170627-01
		GameInterface.(_tabName).(row).(col).scale = 1.0;
		GameInterface.(_tabName).(row).(col).textoffset = "-5,-4";
		GameInterface.(_tabName).(row).(col).align = "center";

		diff = skillVal - GetSkillValue(_chr, SPECIAL_TYPE, skillName);
		GameInterface.(_tabName).(row).(col).str = skillVal;
		if (diff == 0)
		{
     		GameInterface.(_tabName).(row).(col).color = argb(255,255,255,255);
		}
		else
		{
		   if (diff > 0)
		   {
	          GameInterface.(_tabName).(row).(col).color = argb(255,196,255,196);
	       }
	       else
	       {
	          GameInterface.(_tabName).(row).(col).color = argb(255,255,196,196);
	       }
		}
	}
	row = "tr3";
	for (i=1; i<=7; i++)
	{
	    col = "td" + i;
	    skillName = GetSkillNameByTRIdx("SelfType", i);

		GameInterface.(_tabName).(row).(col).icon.group = "ICONS_SPEC";
	    GameInterface.(_tabName).(row).(col).icon.image = skillName + " skill icon";
	    GameInterface.(_tabName).(row).(col).icon.width = 30;
    	GameInterface.(_tabName).(row).(col).icon.height = 30;
		GameInterface.(_tabName).(row).(col).icon.offset = "0,0";
	}
	row = "tr4";
	for (i=1; i<=7; i++)
	{
	    col = "td" + i;
	    skillName = GetSkillNameByTRIdx("SelfType", i);
        skillVal = GetSummonSkillFromName(_chr, skillName);
		GameInterface.(_tabName).(row).(col).fontidx = 1;
		//#20170627-01
		GameInterface.(_tabName).(row).(col).scale = 0.8;
		GameInterface.(_tabName).(row).(col).textoffset = "-5,-4";
		GameInterface.(_tabName).(row).(col).align = "center";

		diff = skillVal - GetSkillValue(_chr, SKILL_TYPE, skillName);
		GameInterface.(_tabName).(row).(col).str = skillVal;
		if (diff == 0)
		{
     		GameInterface.(_tabName).(row).(col).color = argb(255,255,255,255);
		}
		else
		{
		   if (diff > 0)
		   {
	          GameInterface.(_tabName).(row).(col).color = argb(255,196,255,196);
	       }
	       else
	       {
	          GameInterface.(_tabName).(row).(col).color = argb(255,255,196,196);
	       }
		}
	}

	row = "tr5";
	for (i=1; i<=7; i++)
	{
	    col = "td" + i;
	    skillName = GetSkillNameByTRIdx("ShipType", i);

		GameInterface.(_tabName).(row).(col).icon.group = "ICONS_SPEC";
	    GameInterface.(_tabName).(row).(col).icon.image = skillName + " skill icon";
	    GameInterface.(_tabName).(row).(col).icon.width = 30;
    	GameInterface.(_tabName).(row).(col).icon.height = 30;
		GameInterface.(_tabName).(row).(col).icon.offset = "0,0";
	}
	row = "tr6";
	for (i=1; i<=7; i++)
	{
	    col = "td" + i;
	    skillName = GetSkillNameByTRIdx("ShipType", i);
        skillVal = GetSummonSkillFromName(_chr, skillName);
		GameInterface.(_tabName).(row).(col).fontidx = 1;
		//#20170627-01
		GameInterface.(_tabName).(row).(col).scale = 0.8;
		GameInterface.(_tabName).(row).(col).textoffset = "-5,-4";
		GameInterface.(_tabName).(row).(col).align = "center";

		diff = skillVal - GetSkillValue(_chr, SKILL_TYPE, skillName);
		GameInterface.(_tabName).(row).(col).str = skillVal;
		if (diff == 0)
		{
     		GameInterface.(_tabName).(row).(col).color = argb(255,255,255,255);
		}
		else
		{
		   if (diff > 0)
		   {
	          GameInterface.(_tabName).(row).(col).color = argb(255,196,255,196);
	       }
	       else
	       {
	          GameInterface.(_tabName).(row).(col).color = argb(255,255,196,196);
	       }
		}
	}
	// прорисовка
	Table_UpdateWindow(_tabName);
}

// опыт команды нпс _chr
void SetCrewExpTable(ref _chr, string _tabName, string _bar1, string _bar2, string _bar3)
{
    int     i;
	string  row, skillName, col;
    int     skillVal;

    GameInterface.(_tabName).select = 0;
	GameInterface.(_tabName).hr.td1.str = "";
	for (i=1; i<=3; i++)
	{
	    row = "tr" + i;

	    GameInterface.(_tabName).(row).td1.icon.width = 23;
    	GameInterface.(_tabName).(row).td1.icon.height = 23;
    	GameInterface.(_tabName).(row).td1.icon.offset = "0, 2";
		GameInterface.(_tabName).(row).td2.align = "left";
		GameInterface.(_tabName).(row).td2.scale = 0.8;
		GameInterface.(_tabName).(row).td2.textoffset = "3,0";
		GameInterface.(_tabName).(row).td3.align = "right";
		GameInterface.(_tabName).(row).td3.scale = 0.8;
		//GameInterface.(_tabName).(row).td3.textoffset = "0,1";
	}
	GameInterface.(_tabName).tr1.UserData.ID = "Sailors";
	GameInterface.(_tabName).tr1.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr1.td1.icon.image = "Class";
	GameInterface.(_tabName).tr1.td2.str = XI_ConvertString("Sailors");
	if (GetCrewQuantity(_chr) > 0)
    {
		GameInterface.(_tabName).tr1.td3.str = XI_ConvertString(GetExpName(sti(_chr.Ship.Crew.Exp.Sailors)));
	}
	else
	{
		GameInterface.(_tabName).tr1.td3.str = "";
	}

	GameInterface.(_tabName).tr2.UserData.ID = "Cannoners";
	GameInterface.(_tabName).tr2.td1.icon.group = "ICONS_SPEC";
    GameInterface.(_tabName).tr2.td1.icon.image = "Cannons skill icon";
	GameInterface.(_tabName).tr2.td2.str = XI_ConvertString("Cannoners");
	if (GetCrewQuantity(_chr) > 0)
    {
		GameInterface.(_tabName).tr2.td3.str = XI_ConvertString(GetExpName(sti(_chr.Ship.Crew.Exp.Cannoners)));
	}
		else
	{
		GameInterface.(_tabName).tr2.td3.str = "";
	}

    GameInterface.(_tabName).tr3.UserData.ID = "Soldiers";
	GameInterface.(_tabName).tr3.td1.icon.group = "ICONS_SPEC";
    GameInterface.(_tabName).tr3.td1.icon.image = "grappling skill icon";
	GameInterface.(_tabName).tr3.td2.str = XI_ConvertString("Soldiers");
	if (GetCrewQuantity(_chr) > 0)
    {
		GameInterface.(_tabName).tr3.td3.str = XI_ConvertString(GetExpName(sti(_chr.Ship.Crew.Exp.Soldiers)));
	}
		else
	{
		GameInterface.(_tabName).tr3.td3.str = "";
	}
	// прорисовка
	Table_UpdateWindow(_tabName);

	///  прогресбары
	GameInterface.StatusLine.(_bar1).Max   = 100;
    GameInterface.StatusLine.(_bar1).Min   = 1;
    if (GetCrewQuantity(_chr) > 0)
    {
    	GameInterface.StatusLine.(_bar1).Value = sti(_chr.Ship.Crew.Exp.Sailors);
    }
    else
    {
    	GameInterface.StatusLine.(_bar1).Value = 1;
    }
    SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, _bar1,0);

    GameInterface.StatusLine.(_bar2).Max   = 100;
    GameInterface.StatusLine.(_bar2).Min   = 1;
    if (GetCrewQuantity(_chr) > 0)
    {
    	GameInterface.StatusLine.(_bar2).Value = sti(_chr.Ship.Crew.Exp.Cannoners);
    }
    else
    {
    	GameInterface.StatusLine.(_bar2).Value = 1;
    }
    SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, _bar2,0);

    GameInterface.StatusLine.(_bar3).Max   = 100;
    GameInterface.StatusLine.(_bar3).Min   = 1;
    if (GetCrewQuantity(_chr) > 0)
    {
    	GameInterface.StatusLine.(_bar3).Value = sti(_chr.Ship.Crew.Exp.Soldiers);
    }
    else
    {
    	GameInterface.StatusLine.(_bar3).Value = 1;
    }
    SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, _bar3,0);
}

void SetShipOTHERTable(string _tabName, ref _chr)
{
    int     i;
	string  row;

    int iShip = sti(_chr.ship.type);
	ref refBaseShip = GetRealShip(iShip);

    GameInterface.(_tabName).select = 0;
	GameInterface.(_tabName).hr.td1.str = "";
	for (i=1; i<=10; i++)
	{
	    row = "tr" + i;

	    GameInterface.(_tabName).(row).td1.icon.width = 24;
    	GameInterface.(_tabName).(row).td1.icon.height = 24;
    	GameInterface.(_tabName).(row).td1.icon.offset = "2, 1";
		GameInterface.(_tabName).(row).td2.align = "left";
		GameInterface.(_tabName).(row).td2.scale = 0.8;
		GameInterface.(_tabName).(row).td2.textoffset = "0,0";
		GameInterface.(_tabName).(row).td3.align = "right";
		GameInterface.(_tabName).(row).td3.scale = 0.8;
	}
	GameInterface.(_tabName).tr1.UserData.ID = "Hull";
	GameInterface.(_tabName).tr1.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr1.td1.icon.image = "Hull";
	GameInterface.(_tabName).tr1.td2.str = XI_ConvertString("Hull");
	GameInterface.(_tabName).tr1.td3.str = sti(_chr.ship.hp) + " / " + sti(refBaseShip.hp);
    if (!CheckAttribute(&RealShips[iShip], "Tuning.HP"))
	{
		GameInterface.(_tabName).tr1.td3.color = argb(255,255,255,255);
	}
	else
	{
		GameInterface.(_tabName).tr1.td3.color = argb(255,128,200,225);
	}

	GameInterface.(_tabName).tr2.UserData.ID = "Sails";
	GameInterface.(_tabName).tr2.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr2.td1.icon.image = "Sails";
	GameInterface.(_tabName).tr2.td2.str = XI_ConvertString("Sails");
	GameInterface.(_tabName).tr2.td3.str = sti(_chr.ship.sp) + " / " + sti(refBaseShip.sp);

	GameInterface.(_tabName).tr3.UserData.ID = "MastHP";
	GameInterface.(_tabName).tr3.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr3.td1.icon.image = "MastHP";
	GameInterface.(_tabName).tr3.td2.str = XI_ConvertString("MastHP");
	GameInterface.(_tabName).tr3.td3.str = FloatToString(stf(refBaseShip.MastMultiplier),2);
	if (!CheckAttribute(&RealShips[iShip], "Tuning.MastMultiplier"))
	{
		GameInterface.(_tabName).tr3.td3.color = argb(255,255,255,255);
	}
	else
	{
		GameInterface.(_tabName).tr3.td3.color = argb(255,128,200,225);
	}

    GameInterface.(_tabName).tr4.UserData.ID = "Speed";
	GameInterface.(_tabName).tr4.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr4.td1.icon.image = "Speed";
	GameInterface.(_tabName).tr4.td2.str = XI_ConvertString("Speed");
	if (IsCompanion(_chr))
	{
		GameInterface.(_tabName).tr4.td3.str = FloatToString(FindShipSpeed(_chr),2) + " / " + FloatToString(stf(refBaseShip.SpeedRate),2);
	}
	else
	{
	    GameInterface.(_tabName).tr4.td3.str = FloatToString(stf(refBaseShip.SpeedRate),2);
	}
	if (!CheckAttribute(&RealShips[iShip], "Tuning.SpeedRate"))
	{
		GameInterface.(_tabName).tr4.td3.color = argb(255,255,255,255);
	}
	else
	{
		GameInterface.(_tabName).tr4.td3.color = argb(255,128,200,225);
	}


    GameInterface.(_tabName).tr5.UserData.ID = "Maneuver";
	GameInterface.(_tabName).tr5.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr5.td1.icon.image = "Maneuver";
	GameInterface.(_tabName).tr5.td2.str = XI_ConvertString("Maneuver");
	if (IsCompanion(_chr))
	{
  		GameInterface.(_tabName).tr5.td3.str = FloatToString((stf(refBaseShip.turnrate) * FindShipTurnRate(_chr)), 2) + " / " + FloatToString(stf(refBaseShip.TurnRate),2);
	}
	else
	{
	    GameInterface.(_tabName).tr5.td3.str = FloatToString(stf(refBaseShip.TurnRate),2);
	}
	if (!CheckAttribute(&RealShips[iShip], "Tuning.TurnRate"))
	{
		GameInterface.(_tabName).tr5.td3.color = argb(255,255,255,255);
	}
	else
	{
		GameInterface.(_tabName).tr5.td3.color = argb(255,128,200,225);
	}

	GameInterface.(_tabName).tr6.UserData.ID = "AgainstWind";
	GameInterface.(_tabName).tr6.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr6.td1.icon.image = "AgainstWind";
	GameInterface.(_tabName).tr6.td2.str = XI_ConvertString("AgainstWind");
	GameInterface.(_tabName).tr6.td3.str = FloatToString(stf(refBaseShip.WindAgainstSpeed),2);
	if (!CheckAttribute(&RealShips[iShip], "Tuning.WindAgainst"))
	{
		GameInterface.(_tabName).tr6.td3.color = argb(255,255,255,255);
	}
	else
	{
		GameInterface.(_tabName).tr6.td3.color = argb(255,128,200,225);
	}


	RecalculateCargoLoad(_chr);
	GameInterface.(_tabName).tr7.UserData.ID = "Capacity";
	GameInterface.(_tabName).tr7.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr7.td1.icon.image = "Capacity";
	GameInterface.(_tabName).tr7.td2.str = XI_ConvertString("Capacity");
	GameInterface.(_tabName).tr7.td3.str = GetCargoLoad(_chr) + " / " + GetCargoMaxSpace(_chr);
	if (!CheckAttribute(&RealShips[iShip], "Tuning.Capacity"))
	{
		GameInterface.(_tabName).tr7.td3.color = argb(255,255,255,255);
	}
	else
	{
		GameInterface.(_tabName).tr7.td3.color = argb(255,128,200,225);
	}

	GameInterface.(_tabName).tr8.UserData.ID = "Crew";
	GameInterface.(_tabName).tr8.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr8.td1.icon.image = "Crew";
	GameInterface.(_tabName).tr8.td2.str = XI_ConvertString("Crew");
	GameInterface.(_tabName).tr8.td3.str = GetCrewQuantity(_chr) + " : "+ sti(refBaseShip.MinCrew) +" / " + sti(refBaseShip.OptCrew);
	if (!CheckAttribute(&RealShips[iShip], "Tuning.MaxCrew"))
	{
		GameInterface.(_tabName).tr8.td3.color = argb(255,255,255,255);
	}
	else
	{
		GameInterface.(_tabName).tr8.td3.color = argb(255,128,200,225);
	}

	GameInterface.(_tabName).tr9.UserData.ID = "sCannons";
	GameInterface.(_tabName).tr9.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr9.td1.icon.image = "Caliber";
	GameInterface.(_tabName).tr9.td2.str = XI_ConvertString("sCannons"); //XI_ConvertString("Caliber");
	GameInterface.(_tabName).tr9.td3.str = XI_ConvertString("caliber" + refBaseShip.MaxCaliber) + " / " + sti(refBaseShip.CannonsQuantity);

	if (!CheckAttribute(&RealShips[iShip], "Tuning.Cannon"))
	{
		GameInterface.(_tabName).tr9.td3.color = argb(255,255,255,255);
	}
	else
	{
		GameInterface.(_tabName).tr9.td3.color = argb(255,128,200,225);
	}

	GameInterface.(_tabName).tr10.UserData.ID = "CannonType";
	GameInterface.(_tabName).tr10.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr10.td1.icon.image = "Cannons";
	GameInterface.(_tabName).tr10.td2.str = XI_ConvertString(GetCannonType(sti(_chr.Ship.Cannons.Type)) + "s2");
	if (sti(_chr.Ship.Cannons.Type) != CANNON_TYPE_NONECANNON)
	{
		if(GetCannonsNum(_chr) > 0)
		{
		GameInterface.(_tabName).tr10.td3.str = XI_ConvertString("caliber" + GetCannonCaliber(sti(_chr.Ship.Cannons.Type))) + " / " + GetCannonsNum(_chr);
	}
	else
	{
			GameInterface.(_tabName).tr10.td3.str = GetCannonsNum(_chr);
		}
	}
	else
	{
	    GameInterface.(_tabName).tr10.td3.str = "";
	}
	// прорисовка
	Table_UpdateWindow(_tabName);
}

void SetShipQualityTable(ref _chr, string _bar1, string _bar7, string _bar2, string _bar3, string _bar4, string _bar5, string _bar6)
{
	int iShip = sti(_chr.ship.type);
	float fHP = 100;
	float fMast = 100;
	float fSpeedRate = 100;
	float fTurnRate = 100;
	float fWAS = 100;
	float fCapacity = 100;
	float fCrew = 100;
	ref refShip = GetRealShip(iShip);

	if (sti(refShip.BaseType) <= SHIP_SP_SANFELIPE)//рассчитываем качество только для НЕквестовых кораблей
	{
	ref rBaseShip = GetShipByType(sti(refShip.BaseType));

	int iDiffClass = 5 - makeint(sti(refShip.Class)/2);
	int MaxiCannonDiff;
	if (rBaseShip.CannonsQuantity > 7) MaxiCannonDiff = 1;
	if (rBaseShip.CannonsQuantity > 13) MaxiCannonDiff = 2;
	if (rBaseShip.CannonsQuantity > 29) MaxiCannonDiff = 3;
	if (rBaseShip.CannonsQuantity > 49) MaxiCannonDiff = 4;
	if (rBaseShip.CannonsQuantity > 79) MaxiCannonDiff = 5;
	float MaxSpeedBONUS = (stf(rBaseShip.SpeedRate) * MaxiCannonDiff) / (15*iDiffClass);//рассчитываем бонусы от неполного числа пушек при генерации корабля
	float MaxTurnBONUS = (stf(rBaseShip.TurnRate) * MaxiCannonDiff) / (15*iDiffClass);
	float MaxHPBONUS = (stf(rBaseShip.HP) * MaxiCannonDiff) / (15*iDiffClass);
	float MaxCapacityBONUS = (stf(rBaseShip.Capacity) * MaxiCannonDiff) / (15*iDiffClass);

	float Bonus_Capacity, Bonus_HP, Bonus_SpeedRate, Bonus_TurnRate;
	if (CheckAttribute(refShip, "Bonus_Capacity")) Bonus_Capacity = refShip.Bonus_Capacity; else Bonus_Capacity = 0;
	if (CheckAttribute(refShip, "Bonus_HP")) Bonus_HP = refShip.Bonus_HP; else Bonus_HP = 0;
	if (CheckAttribute(refShip, "Bonus_SpeedRate")) Bonus_SpeedRate = refShip.Bonus_SpeedRate; else Bonus_SpeedRate = 0;
	if (CheckAttribute(refShip, "Bonus_TurnRate")) Bonus_TurnRate = refShip.Bonus_TurnRate; else Bonus_TurnRate = 0;

	float fTemp; //приводим 0,9 - 1,1 к формату 0-100
//=======================================//четыре параметра с бонусами от числа пушек
	fTemp = stf(refShip.Capacity) - Bonus_Capacity;
	if (CheckAttribute(refShip, "Tuning.BotPack")) fTemp = fTemp/1.5;
	if (CheckAttribute(refShip, "Tuning.Capacity")) fTemp = fTemp/1.2;
	fCapacity = 100*(fTemp + Bonus_Capacity - 0.87499*stf(rBaseShip.Capacity)) / (MaxCapacityBONUS + 0.25*stf(rBaseShip.Capacity));

	fTemp = stf(refShip.HP) - Bonus_HP;
	if (CheckAttribute(refShip, "Tuning.BotPack")) fTemp = fTemp*2;
	if (CheckAttribute(refShip, "Tuning.HP")) fTemp = fTemp/1.2;
	fHP = 100*(fTemp + Bonus_HP - 0.899*stf(rBaseShip.HP)) / (MaxHPBONUS + 0.2*stf(rBaseShip.HP));

	fTemp = stf(refShip.SpeedRate) - Bonus_SpeedRate;
	if (CheckAttribute(refShip, "Tuning.SpeedRate")) fTemp = fTemp/1.2;
	fSpeedRate = 100*(fTemp + Bonus_SpeedRate - 0.899*stf(rBaseShip.SpeedRate)) / (MaxSpeedBONUS + 0.2*stf(rBaseShip.SpeedRate));

	fTemp = stf(refShip.TurnRate) - Bonus_TurnRate;
	if (CheckAttribute(refShip, "Tuning.TurnRate")) fTemp = fTemp/1.2;
	fTurnRate = 100*(fTemp + Bonus_TurnRate - 0.899*stf(rBaseShip.TurnRate)) / (MaxTurnBONUS + 0.2*stf(rBaseShip.TurnRate));
//=======================================//
	fTemp = stf(refShip.MastMultiplier);
	if (CheckAttribute(refShip, "Tuning.MastMultiplier")) fTemp = fTemp + 0.3;
	fMast = 100*(stf(rBaseShip.MastMultiplier)+0.3-fTemp)/0.6;

	fTemp = stf(refShip.WindAgainstSpeed);
	if (CheckAttribute(refShip, "Tuning.WindAgainst")) fTemp = stf(FloatToString((fTemp-0.005)*stf(refShip.Class)*2/(stf(refShip.Class)*2+1),2));// :(
	fWAS = 500*(fTemp/stf(rBaseShip.WindAgainstSpeed)-0.9);

	fTemp = stf(refShip.OptCrew); 	//тюнинг не влияет на оптимальную
	fCrew = 300*(fTemp/stf(rBaseShip.OptCrew)-0.8333);

	if (fCapacity < 0) fCapacity = 0;
	if (fWAS < 0) fWAS = 0;
	}

	GameInterface.StatusLine.(_bar1).Max   = 100;
	GameInterface.StatusLine.(_bar1).Min   = 0;
	GameInterface.StatusLine.(_bar1).Value = fHP;
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, _bar1,0);

	GameInterface.StatusLine.(_bar2).Max   = 100;
	GameInterface.StatusLine.(_bar2).Min   = 0;
	GameInterface.StatusLine.(_bar2).Value = fspeedRate;
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, _bar2,0);

	GameInterface.StatusLine.(_bar3).Max   = 100;
	GameInterface.StatusLine.(_bar3).Min   = 0;
	GameInterface.StatusLine.(_bar3).Value = fTurnRate;
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, _bar3,0);

	GameInterface.StatusLine.(_bar4).Max   = 100;
	GameInterface.StatusLine.(_bar4).Min   = 0;
	GameInterface.StatusLine.(_bar4).Value = fWAS;
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, _bar4,0);

	GameInterface.StatusLine.(_bar5).Max   = 100;
	GameInterface.StatusLine.(_bar5).Min   = 0;
	GameInterface.StatusLine.(_bar5).Value = fCapacity;
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, _bar5,0);

	GameInterface.StatusLine.(_bar6).Max   = 100;
	GameInterface.StatusLine.(_bar6).Min   = 0;
	GameInterface.StatusLine.(_bar6).Value = fCrew;
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, _bar6,0);

	GameInterface.StatusLine.(_bar7).Max   = 100;
	GameInterface.StatusLine.(_bar7).Min   = 0;
	GameInterface.StatusLine.(_bar7).Value = fMast;
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, _bar7,0);
}

void SetFoodShipInfo(ref chr, string _textName)
{
	int iColor, iFood;
	string sText;

	SetFormatedText(_textName, "");
	if (sti(chr.ship.type) != SHIP_NOTUSED)
	{
		sText = "Провианта на корабле на ";
		iFood = CalculateShipFood(chr);
		sText = sText + FindRussianDaysString(iFood);
		SetFormatedText(_textName, sText);
		if(iFood >= 5)
		{
			iColor = argb(255,255,255,192);
		}
		if(iFood > 10)
		{
			iColor = argb(255,192,255,192);
		}
		if(iFood < 5)
		{
			iColor = argb(255,255,192,192);
		}
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE, _textName, 8,-1,iColor);
	}
}

void SetSquadronFoodShipInfo(ref chr, string _textName)
{
	int iColor, iFood;
	string sText;

	SetFormatedText(_textName, "");
	if (sti(chr.ship.type) != SHIP_NOTUSED)
	{
		sText = "Провианта на:\n корабле / в эскадре\n на ";
		iFood = CalculateShipFood(chr);
		sText = sText + iFood+" / "+FindRussianDaysString(CalculateFood());
		SetFormatedText(_textName, sText);
		if(iFood >= 5)
		{
			iColor = argb(255,255,255,192);
		}
		if(iFood > 10)
		{
			iColor = argb(255,192,255,192);
		}
		if(iFood < 5)
		{
			iColor = argb(255,255,192,192);
		}
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE, _textName, 8,-1,iColor);
	}
}

// Warship 11.07.09 Вывести в текстовое поле инфу о количестве дней, на сколько хватит рому на судне
void SetRumShipInfo(ref _character, String _node)
{
	int color, rum;
	String text;

	SetFormatedText(_node, "");

	if(sti(_character.ship.type) != SHIP_NOTUSED)
	{
		text = "Рома на корабле на ";
		rum = CalculateShipRum(_character);
		text = text + FindRussianDaysString(rum);
		SetFormatedText(_node, text);

		if(rum < 3)
		{
			color = argb(255, 255, 192, 192);
		}

		if(rum >= 3)
		{
			color = argb(255, 255, 255, 192);
		}

		if(rum >= 10)
		{
			color = argb(255, 192, 255, 192);
		}

		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, _node, 8, -1, color);
	}
}

int GetTradeItemPrice(int itmIdx, int tradeType)
{
	int itmprice = 0;
	if(itmIdx<0 || itmIdx>TOTAL_ITEMS) return 0;

	if(CheckAttribute(&Items[itmIdx],"price"))
	{
		itmprice = sti(Items[itmIdx].price);
	}

	float skillDelta = GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE);
	float skillModify;
	if(tradeType == PRICE_TYPE_BUY)
	{
		skillModify = 1.45 - skillDelta*0.019;
		if(CheckOfficersPerk(pchar,"Trader")) { skillModify -= 0.05; }
		if(CheckOfficersPerk(pchar,"AdvancedCommerce"))	{ skillModify -= 0.2; }
		else
		{
			if(CheckOfficersPerk(pchar,"BasicCommerce"))	{ skillModify -= 0.1; }
		}
		if(CheckAttribute(&Items[itmIdx],"groupID"))
		{
			if(Items[itmIdx].groupID == BLADE_ITEM_TYPE || Items[itmIdx].groupID == GUN_ITEM_TYPE) skillModify *= 10.0;//меняем после всех перков, иначе скидка от перков непропорциональная
		}
	}
	else
	{
		skillModify = 0.70 + skillDelta*0.019;
		if(CheckOfficersPerk(pchar,"AdvancedCommerce"))	skillModify += 0.05;
		if(CheckOfficersPerk(pchar,"Trader")) { skillModify += 0.05; }
	}

	return makeint(makefloat(itmprice)*skillModify);
}

int strcmp(string a, string b)
{
	return 0;
}

//--> mod tablesort
void SortTable(string sControl,int iColumn, bool bIsString, bool bAsc, int _iLinesCount)
{
	bool bNoSize;
	if (_iLinesCount < 1) {bNoSize = true; _iLinesCount = 998;} else bNoSize = false;//если число строк не передано, ставим 998 строк для цикла
	string sColumn = "td" + iColumn;
	int m, n;
	string sCurRow, sNextRow, sRow;
	sRow = "tr" + 999;//пузырёк
	aref aCurRow, aNextRow, aRow;

	for (m = 0; m < _iLinesCount-2; m++)
	{
		for (n = 0; n < _iLinesCount-2; n++)
		{
		sCurRow = "tr" + (n + 1);
		sNextRow = "tr" + (n + 2);
		if (bNoSize) {if (!checkattribute(&GameInterface,sControl + "." + sNextRow)) {_iLinesCount = n+2; bNoSize = false; break;}}//если число строк не было указано, проверяем, не кончилась ли таблица
//находим число строк - проверить, что это оптимально, и что мусорное значение не сломает//TODO - обязательно разобраться!!! ВАЖНО!!!

//TODO - убрать это деление на строки, автоматически определять - текст или число сортируем
		if (bIsString)//строки
			{
			if (bAsc)//по возрастанию
				{
				if (strcmp (GameInterface.(sControl).(sCurRow).(sColumn).str, GameInterface.(sControl).(sNextRow).(sColumn).str)>0)
					{
					makearef(aRow, GameInterface.(sControl).(sRow));
					makearef(aCurRow, GameInterface.(sControl).(sCurRow));
					makearef(aNextRow, GameInterface.(sControl).(sNextRow));
					CopyAttributes(aRow, aCurRow);
					CopyAttributes(aCurRow, aNextRow);
					CopyAttributes(aNextRow, aRow);
					}
				}
				else//по убыванию
				{
				if (strcmp (GameInterface.(sControl).(sCurRow).(sColumn).str, GameInterface.(sControl).(sNextRow).(sColumn).str)<0)
					{
					makearef(aRow, GameInterface.(sControl).(sRow));
					makearef(aCurRow, GameInterface.(sControl).(sCurRow));
					makearef(aNextRow, GameInterface.(sControl).(sNextRow));
					CopyAttributes(aRow, aCurRow);
					CopyAttributes(aCurRow, aNextRow);
					CopyAttributes(aNextRow, aRow);
					}
				}
			}
			else//числа
			{
			if (bAsc)//по возрастанию
				{
				if (stf(GameInterface.(sControl).(sCurRow).(sColumn).str) > stf(GameInterface.(sControl).(sNextRow).(sColumn).str))
					{
					makearef(aRow, GameInterface.(sControl).(sRow));
					makearef(aCurRow, GameInterface.(sControl).(sCurRow));
					makearef(aNextRow, GameInterface.(sControl).(sNextRow));
					CopyAttributes(aRow, aCurRow);
					CopyAttributes(aCurRow, aNextRow);
					CopyAttributes(aNextRow, aRow);
					}
				}
				else
				{
				if (stf(GameInterface.(sControl).(sCurRow).(sColumn).str) < stf(GameInterface.(sControl).(sNextRow).(sColumn).str))
					{
					makearef(aRow, GameInterface.(sControl).(sRow));
					makearef(aCurRow, GameInterface.(sControl).(sCurRow));
					makearef(aNextRow, GameInterface.(sControl).(sNextRow));
					CopyAttributes(aRow, aCurRow);
					CopyAttributes(aCurRow, aNextRow);
					CopyAttributes(aNextRow, aRow);
					}
				}
			}
		}
	}
}
//<-- mod tablesort
