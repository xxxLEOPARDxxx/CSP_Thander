
void InitInterface(string iniName)
{
    	GameInterface.title = "titleAttackMessage";

    	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	MessageInfo();

	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",5);

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);
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
	DelEventHandler("evntDoPostExit","DoPostExit");

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
	    case "BUTTON":
		  if(comName=="activate" || comName=="click")
		  {
			 PostEvent("evntDoPostExit",1,"l",RC_INTERFACE_SALARY_EXIT);
		  }
	    break;

	    /*
	    case "TO_NOTICE":
		  if(comName=="activate" || comName=="click")
		  {
			IDoExit(RC_INTERFACE_CREATE_NOTICE, false);
			return;
		  }
	    break;
	    */
	}
}


void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void MessageInfo()
{
	string sMessageFrom = "";

	CreateString(true,"Header", "Срочное сообщение", FONT_CAPTION, COLOR_NORMAL, 395,153,SCRIPT_ALIGN_CENTER,1.5);

	string sColonyName = "Кайман";
	if(CheckAttribute(PChar, "ColonyBuilding.ColonyName"))
	{
		sColonyName = PChar.ColonyBuilding.ColonyName;
	}

	bool bFirst = sti(PChar.ColonyBuilding.MessageInfo.First);

	string sTarget = PChar.ColonyBuilding.MessageInfo.Target;
	string sType = PChar.ColonyBuilding.MessageInfo.Type;
	string sEnd = PChar.ColonyBuilding.MessageInfo.End;
	int iTime = sti(PChar.ColonyBuilding.MessageInfo.Time);
	int iNation = sti(PChar.ColonyBuilding.MessageInfo.Nation);

	string sNation = GetNationNameByType(iNation) + "Gen";
	string sNationEnd = GetNationNameByType(iNation) + "Abl";
	string sNationDat = "people" + GetNationNameByType(iNation) + "Dat";

	sNation = XI_ConvertString(sNation);
	sNationEnd = XI_ConvertString(sNationEnd);
	sNationDat = XI_ConvertString(sNationDat);

	string sTexture = GetPictureForMessage(sTarget, true);
	string sPicture = GetPictureForMessage(sTarget, false);

	if(PChar.ColonyBuilding.Stage == "1" && sTarget == "Colony")
	{
		SetNewPicture("TARGET", "loading\jonny_load\outside\smugglerLairTown_(pirate_town).tga");
	}
	else
	{
		SetNewGroupPicture("TARGET", sTexture, sPicture);
	}

	string sTemp = "";
	string sMessage = "";

	if(bFirst)
	{
		sMessage += "Капитан " + GetNameLugger(PChar, "f") + ", тревожные вести пришли из колонии ''" + sColonyName + "''!";
	}

	sMessage += newStr();

	if(bFirst)
	{
		sPicture = "Enemy";

		switch(sTarget)
		{
			case "Colony":
				switch(sType)
				{
					case "Mutiny": sTemp = "В вашей колонии готовится мятеж. По сведениям, присланным из колонии, гарнизон сможет продержаться "; break;
					case "BattleLand": sTemp = "На вашу колонию ожидается нападение с суши. По сведениям, присланным из колонии, гарнизон сможет продержаться "; break;
					case "BattleSea": sTemp = "На колонию ожидается нападение эскадрой под флагом " + sNation + ". По полученным сведениям охрана сможет продержаться "; break;
				}
			break;

			case "Mines":
				switch(sType)
				{
					case "Mutiny": sTemp = "На ваших рудниках готовится мятеж. По присланным сведениям, гарнизон сможет продержаться "; break;
					case "BattleLand": sTemp = "На ваши рудники ожидается нападение. По присланным сведениям, гарнизон сможет продержаться "; break;
					case "BattleSea": sTemp = ""; break;
				}
			break;

			case "Plantation":
				switch(sType)
				{
					case "Mutiny": sTemp = "На вашей плантации готовится мятеж. По присланным сведениям, гарнизон сможет продержаться "; break;
					case "BattleLand": sTemp = ""; break;
					case "BattleSea": sTemp = ""; break;
				}
			break;
		}
	}
	else
	{
		if(sEnd == "Good")
		{
			sPicture = "Friend";
		}
		else
		{
			sPicture = "Enemy";
		}

		switch(sTarget)
		{
			case "Colony":
				switch(sType)
				{
					case "Mutiny": if(sEnd == "Good") { sTemp = "Мятеж в вашей колонии удалось подавить."; }else{ sTemp = "Мятежникам удалось сломить сопротивление гарнизона колонии."; } break;
					case "BattleLand": if(sEnd == "Good") { sTemp = "Из колонии пришли хорошие новости! Нападение, организованное врагом, было отбито!"; }else{ sTemp = "Из колонии пришли плохие новости... Колония не смогла защитить себя и была разграблена."; } break;
					case "BattleSea": if(sEnd == "Good") { sTemp = "Отличные новости прислали из колонии! Общими усилиями охраны колонии удалось дать отпор проклятым " + sNationDat + "."; }else{ sTemp = "Плохие новости пришли из колонии. Нападению, совершённому " + sNationEnd + ", не удалось противостоять. Колония была разграблена."; } break;
				}
			break;

			case "Mines":
				switch(sType)
				{
					case "Mutiny": if(sEnd == "Good") { sTemp = "Мятеж на ваших рудниках удалось подавить."; }else{ sTemp = "Рабы сломили сопротивление гарнизона рудников и обратились в бегство, попутно прихватив провиант, медикаменты и добытую руду."; } break;
					case "BattleLand": if(sEnd == "Good") { sTemp = "Из колонии пришли хорошие новости! Нападение, организованное врагом на рудники, было отбито!"; }else{ sTemp = "Из колонии пришли плохие новости... Гарнизон, защищающий рудники, не смог противопоставить достойное сопротивление. Рудники были разграблены."; } break;
				}
			break;

			case "Plantation":
				switch(sType)
				{
					case "Mutiny": if(sEnd == "Good") { sTemp = "Мятеж на вашей плантации удалось подавить."; }else{ sTemp = "Рабы сломили сопротивление гарнизона и обратились в бегство, попутно прихватив провиант, медикаменты и добытые продукты."; } break;
				}
			break;
		}
	}

	SetNewGroupPicture("STATE", "RELATIONS", sPicture);

	bool bLoose = sType == "MutinyLoose" || sType == "BattleLandLoose" || sType == "BattleSeaLoose";
	if(!bFirst && bLoose)
	{
		switch(sTarget)
		{
			case "Colony":
				switch(sType)
				{
					case "MutinyLoose": sTemp = "В вашей колонии вспыхнул мятеж. Из-за отсутствия необходимого гарнизона мятежники праздновали победу."; break;
					case "BattleLandLoose": sTemp = "На вашу колонию было совершено нападение с суши. Из-за отсутствия необходимого гарнизона нападавшие легко взяли колонию боем и разграбили её."; break;
					case "BattleSeaLoose": sTemp = "На колонию напала эскадра под флагом " + sNation + ". Из-за отсутствия достойной охраны береговой линии и гарнизона эскадра разграбила колонию."; break;
				}
			break;

			case "Mines":
				switch(sType)
				{
					case "MutinyLoose": sTemp = "На ваших рудниках вспыхнул мятеж. Из-за отсутствия необходимого гарнизона мятежники праздновали победу и пустились в бегство."; break;
					case "BattleLandLoose": sTemp = "На ваши рудники было совершено нападение. Из-за отсутствия необходимого гарнизона нападавшие легко взяли рудники боем и разграбили их."; break;
				}
			break;

			case "Plantation":
				switch(sType)
				{
					case "MutinyLoose": sTemp = "На вашей плантации вспыхнул мятеж. Из-за отсутствия необходимого гарнизона мятежники праздновали победу и пустились в бегство."; break;
				}
			break;
		}
	}

	sMessage += sTemp;

	if(bFirst)
	{
		sMessage += FindRussianDaysString(iTime) + "."
	}

	SetFormatedText("MESSAGE", sMessage);
}

string GetPictureForMessage(string sTarget, bool bTexture)
{
	int iTown = 1;
	if(CheckAttribute(PChar, "ColonyBuilding.Architecture.Town"))
	{
		iTown = sti(PChar.ColonyBuilding.Architecture.Town);
	}

	switch(sTarget)
	{
		case "Colony": 		if(bTexture) { return "COLONY_ARCHITECTURE"; 	}else{ return "Town_Type_" + iTown; } 	break;
		case "Mines": 		if(bTexture) { return GetCurrentTexture(); 	}else{ return "GoldMine"; } 		break;
		case "Plantation": 	if(bTexture) { return GetCurrentTexture(); 	}else{ return "Plantation"; } 		break;
	}

	return "none";
}

string GetCurrentTexture()
{
	if(CheckAttribute(PChar, "ColonyBuilding.CurrentIconsTexture"))
	{
		return "COLONY_BUILDINGS_" + sti(PChar.ColonyBuilding.CurrentIconsTexture);
	}

	return "COLONY_BUILDINGS_1";
}




