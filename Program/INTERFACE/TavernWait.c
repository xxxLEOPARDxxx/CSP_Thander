int iChooseTime = 3;
int iTime = 0;
string sDate;
bool days = false;

void InitInterface_GM(string iniName)
{
    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

    BLI_DisableShow();

    SetTimeScale(0.0);
	locCameraSleep(true);

	EngineLayersOffOn(true);

    SetEventHandler("frame","ProcessFrame",1);
    SetEventHandler("InterfaceBreak","ProcessCancelExit",0);
    SetEventHandler("exitCancel","ProcessCancelExit",0);
    SetEventHandler("eSlideChange","ChangeTimeProgress",0);
	SetEventHandler("RefreshVariables","RefreshVariables",0);
    SetEventHandler("exitOk","Sleep",0);

    SetFormatedText("TIME_TEXT", (iTime+1)+FindHourString(iTime+1));

    SetWariable();

    SetTimeSlider();

    ProcessFrame();

    SetFormatedText("CAPTION", "Отдых");
}

void ProcessFrame()
{
        if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 1))
        {
			days = false;
			SetSelectable("SLIDE", false);
			SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"SLIDE", 0,0);
        }

        if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 2))
        {
			days = false;
			SetSelectable("SLIDE", false);
			SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"SLIDE", 0,0);
        }
        if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 3))
        {
			days = false;
			SetSelectable("SLIDE", true);
        }
		if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 4))
        {
			days = true;
			SetSelectable("SLIDE", true);
        }
}

void RefreshVariables()
{
	SetTimeSlider();
	ChangeTimeProgress();
	if(days == false) SetFormatedText("TIME_TEXT", (iTime+1) + FindHourString(iTime+1));
	else SetFormatedText("TIME_TEXT", "Дней: "+(iTime+1));
}

void ChangeTimeProgress()
{
	string sNode = GetEventData();

	if(sNode == "SLIDE")
	{
		iTime = GetEventData();
		if(days == false) SetFormatedText("TIME_TEXT", (iTime+1) + FindHourString(iTime+1));
		else SetFormatedText("TIME_TEXT", "Дней: "+(iTime+1));
	}
}

void SetTimeSlider()
{
	if (days == false)
	{
		GameInterface.nodes.SLIDE.value = iTime;
		GameInterface.nodes.SLIDE.maxlimit = 23;

		SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"SLIDE", 1,23);
		SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"SLIDE", 0,iTime);
	}
	else
	{
		GameInterface.nodes.SLIDE.value = iTime;
		GameInterface.nodes.SLIDE.maxlimit = 6;

		SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"SLIDE", 1,6);
		SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"SLIDE", 0,iTime);
	}
}

void SetWariable()
{
	string sCurDayTime;
	SetFormatedText("CURRENTTIME_TEXT", "");

	sDate = environment.date.day + " " + XI_ConvertString("target_month_" + environment.date.month) + " " + environment.date.year;

	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"CURRENTTIME_TEXT", 0,&sDate);

	string sTime;
	string sHour = sti(worldMap.date.hour);
	string sMinuts = sti(worldMap.date.min);

   if(sti(sHour) < 10)
	{
		sHour = "0" + sHour;
	}
	if(sti(sMinuts) < 10)
	{
		sMinuts = "0" + sMinuts;
	}

	sTime = sHour + " : " + sMinuts;

	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"CURRENTTIME_TEXT", 0,&sTime);

	sCurDayTime = GetDayTime();

	if(sCurDayTime != "night")
	{
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 5, 1,0);
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 5, 2,1);
	}
	else
	{
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 5, 1,1);
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 5, 2,0);
	}
}

void Sleep()
{
    int iCurrentTime = sti(environment.time);
    int iAddtime = 0;
    int iOldDay = GetDataDay();

    if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 1))
    {
        if (iCurrentTime < 24) iAddtime = 24 - iCurrentTime;
    }

    if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 2))
    {
        if (iCurrentTime >= 21) iAddTime = 24 - iCurrentTime + 7;
		if (iCurrentTime < 7) iAddTime = 7 - iCurrentTime;
    }

    if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 3) == 1 || SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 4) == 1)
    {
        iAddtime = iTime+1;
    }
	
	pchar.quest.waithours = iAddtime;
    if (days == false)
	{
		DoQuestFunctionDelay("WaitNextHours", 0.1);
	}
	else
	{
		DoQuestFunctionDelay("WaitNextDays", 0.1);
	}
	ProcessCancelExit();
}

void ProcessCancelExit()
{
	IDoExit(RC_INTERFACE_TAVERN_WAIT, true);
}

void IDoExit(int exitCode, bool bCode)
{
	DelEventHandler("InterfaceBreak","ProcessCancelExit");
	DelEventHandler("frame","ProcessFrame");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("eSlideChange","ChangeTimeProgress");
	DelEventHandler("RefreshVariables","RefreshVariables");
	DelEventHandler("exitOk","Sleep");

	SetTimeScale(1.0);
	locCameraSleep(false);

	BLI_EnableShow();

	interfaceResultCommand = exitCode;
	EndCancelInterface(bCode);
}

string FindHourString(int iHour)
{
	string sHour = " часов";

	if(iHour == 1 || iHour == 21) sHour = " час";
	if(iHour > 1 && iHour < 5) sHour = " часа";
	if(iHour > 21 && iHour < 25) sHour = " часа";

	return sHour;
}

void Restore_HP()
{
	int iOfficer;
	LAi_SetCurHPMax(pchar);
	for (int i=1; i<4; i++)
	{
		if (GetOfficersIndex(Pchar, i) != -1)
		{
			iOfficer = GetOfficersIndex(Pchar, i);
			LAi_SetCurHPMax(&characters[iOfficer]);
		}
	}
}

// 2 - вкл/выкл, 3 - проверить статус, 4 - проверить порядковый номер, 5 - актив/деактив
//SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 5, 1,1)
