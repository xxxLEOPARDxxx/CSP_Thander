
void InitInterface_gm(string iniName)
{
	GameInterface.title = "titleGameMenu";

	SetTimeScale(0.0);
	locCameraSleep(true);

	EngineLayersOffOn(true);

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessCancelExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcessCommandExecute",0);
	SetEventHandler("frame","IProcessFrame",0);

	SetEventHandler("NewClick","NewClick",0);
	SetEventHandler("LoadClick","LoadClick",0);
	SetEventHandler("SaveClick","SaveClick",0);
	SetEventHandler("ResumeClick","ResumeClick",0);
	SetEventHandler("OptionsClick","OptionsClick",0);
	SetEventHandler("QuitClick","QuitClick",0);
	SetEventHandler("QuitProcess","QuitProcess",0);

	SetEventHandler("ConfirmExitClick","ConfirmExitClick",0);
	SetEventHandler("ConfirmExitCancel","ConfirmExitCancel",0);

	InterfaceStates.showGameMenuOnExit = true;

	if(CheckAttribute(&InterfaceStates,"Buttons.Resume.enable") && sti(InterfaceStates.Buttons.Resume.enable) == true)
	{
		SetSelectable("MB_RESUME", true);
	} else {

		SetSelectable("MB_RESUME", false);
	}

	if (QuickSaveGameEnabledHardcore()) // boal 09.07.06
	{
		SetSelectable("MB_SAVE", true);
	}
	else
	{
		SetSelectable("MB_SAVE", false);
	}

	if (!CheckSaveGameEnabled())
	{
		SetSelectable("MB_SAVE", false);
	}

	string text4 = "Стартовые условия";
    SetFormatedText("STARTINFO_TITLE", text4);
	SetFormatedText("VERSION_TEXT", VERSION_NUMBER1 + GetVerNum());
	string text = "Анимация персонажа: "+pchar.model.animation+"\nДозарядка пистолетов: "+bRechargePistolOnLine+"\nРежим хардкора: "+bHardcoreGame+"\nРаздел добычи: "+bPartitionSet+"\nВес матросов: "+bSailorsWeight+"\nУникальные паруса у пиратов: "+bNewSails+"\nХардкорные анимации: "+bHardAnimations+"\nУсложнённые боссы: "+bHardBoss+"\nАльтернативный баланс: "+bAltBalance;
	string text3;
	if (pchar.BaseNation == ENGLAND) text3 = "Англия";
	if (pchar.BaseNation == FRANCE) text3 = "Франция";
	if (pchar.BaseNation == HOLLAND) text3 = "Голландия";
	if (pchar.BaseNation == SPAIN) text3 = "Испания";
	if (pchar.BaseNation == PIRATE) text3 = "Пират";
	string text5;
	if (IsCharacterPerkOn(pchar, "Grunt")) text5 = "Рубака";
	if (IsCharacterPerkOn(pchar, "Trader")) text5 = "Торговец";
	if (IsCharacterPerkOn(pchar, "Fencer")) text5 = "Фехтовальщик";
	if (IsCharacterPerkOn(pchar, "Adventurer")) text5 = "Авантюрист";
	if (IsCharacterPerkOn(pchar, "Buccaneer")) text5 = "Буканьер";
	if (IsCharacterPerkOn(pchar, "Agent")) text5 = "Тайный Агент";
	if (IsCharacterPerkOn(pchar, "SeaWolf")) text5 = "Морской Волк";
	string text2 = "Характер: "+text5+"\nСложность: "+GetLevelComplexity(MOD_SKILL_ENEMY_RATE)+"\nНация: "+text3+"\nСкорость набора опыта: "+MOD_EXP_RATE+" / 105\nКоличество абордажников: "+MOD_OFFICERS_RATE+"\nВремя исчезновения трупов: "+MOD_DEAD_CLEAR_TIME+"\nКоличество кораблей охраны: "+MOD_DEFENDERS_RATE+"\nЧастота событий: "+iEncountersRate;
	string text6 = "Количество энкаунтеров: "+iEncountersCountRate+"\nРежим плавания: "+iArcadeSails+"\nПлатные заходы в порт: "+bPortPermission+"\nВзятки стражникам: "+bBribeSoldiers+"\nСнижение порога личных перков: "+bHigherSelfRate+"\nСнижение порога корабельных перков: "+bHigherShipRate+"\nОграничение бонуса навыка офицеров: "+bNoBonusSkillOff+"\nКонтракт на полубессмертие: "+bHalfImmortalPGG;
	string text7 = "Исследование кораблей: "+bFillEncyShips/* +"\nВлияние сложности на переносимый вес: "+bDifficultyWeight */;

	SetFormatedText("STARTINFO_TEXT1", text+"\n"+text2+"\n"+text6+"\n"+text7);
	SetFormatedText("COPYRIGHTS_TEXT", PROVIDER_TXT);
	SetNewPicture("LOGO", "Interfaces\SL_logo.tga.tx");


	if(LAi_IsBoardingProcess())	SetSelectable("MB_RESUME",false);
}


void IProcessFrame()
{
}

void ProcessCancelExit()
{
	if(CheckAttribute(&InterfaceStates,"Buttons.Resume.enable") && sti(InterfaceStates.Buttons.Resume.enable) == true)
	IDoExit(RC_INTERFACE_DO_RESUME_GAME, true);
}

void IDoExit(int exitCode, bool bClear)
{
	DelEventHandler("InterfaceBreak","ProcessCancelExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcessCommandExecute");
	DelEventHandler("frame","IProcessFrame");

	DelEventHandler("NewClick","NewClick");
	DelEventHandler("LoadClick","LoadClick");
	DelEventHandler("SaveClick","SaveClick");
	DelEventHandler("ResumeClick","ResumeClick");
	DelEventHandler("OptionsClick","OptionsClick");
	DelEventHandler("QuitClick","QuitClick");
    DelEventHandler("QuitProcess","QuitProcess");

	DelEventHandler("ConfirmExitClick","ConfirmExitClick");
	DelEventHandler("ConfirmExitCancel","ConfirmExitCancel");

	SetTimeScale(1.0);
	TimeScaleCounter = 0;
	DelPerkFromActiveList("TimeSpeed");
	locCameraSleep(false);
	DeleteAttribute(pchar, "pause");

	interfaceResultCommand = exitCode;

	if( interfaceResultCommand == RC_INTERFACE_DO_RESUME_GAME ) {
		DeleteEntitiesByType("scrshoter");
	}
	EndCancelInterface(bClear);
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
		case "MB_NEW":

			if (comName == "click" || comName == "activate"){

				if(CheckAttribute(&InterfaceStates,"Buttons.Resume.enable") && sti(InterfaceStates.Buttons.Resume.enable) == true)
				{
					ShowConfirmWindow(true);
				} else {

					NewClick();
				}
			}

			break;

		case "CONFIRM_WINDOW_MB_YES":

			if (comName == "click" || comName == "activate"){

				//ShowConfirmWindow(false);
				NewClick();
			}

			if (comName == "deactivate"){

				ShowConfirmWindow(false);
			}

			break;

		case "CONFIRM_WINDOW_MB_NO":

			if (comName == "click" || comName == "activate"){
				ShowConfirmWindow(false);
			}

			if (comName == "deactivate"){

				ShowConfirmWindow(false);
			}

			break;

		case "MB_STARTINFO_OPEN":
			if (comName == "click" || comName == "activate")
			{
				XI_WindowDisable("MAIN_WINDOW",true);
				XI_WindowShow("MAIN_WINDOW", false);
				XI_WindowDisable("STARTINFO_WINDOW",false);
				XI_WindowShow("STARTINFO_WINDOW", true);
				SetNodeUsing("FRAME_COPYRIGHTS", false);
				SetNodeUsing("CIRCLE1", true);
				SetNodeUsing("CIRCLE2", true);
				SetNodeUsing("CIRCLE3", true);
			}
			break;

		case "STARTINFO_EXIT":
			if (comName == "click" || comName == "activate")
			{
				XI_WindowDisable("MAIN_WINDOW",false);
				XI_WindowShow("MAIN_WINDOW", true);
				XI_WindowDisable("STARTINFO_WINDOW",true);
				XI_WindowShow("STARTINFO_WINDOW", false);
				SetNodeUsing("FRAME_COPYRIGHTS", true);
			}
			break;
	}

}

void NewClick()
{
	InterfaceStates.showGameMenuOnExit = false;
	IDoExit( RC_INTERFACE_DO_NEW_GAME, true);
}

void LoadClick()
{
	IDoExit( RC_INTERFACE_DO_LOAD_GAME, true);
}

void SaveClick()
{
	IDoExit( RC_INTERFACE_DO_SAVE_GAME, true);
}

void ResumeClick()
{
	IDoExit(RC_INTERFACE_DO_RESUME_GAME, true);
}


void OptionsClick()
{
	IDoExit(RC_INTERFACE_DO_OPTIONS, true);
}

void QuitClick()
{
	XI_WindowDisable("MAIN_WINDOW",true);
	XI_WindowDisable("CONFIRM_EXIT_WINDOW",false);
	XI_WindowShow("CONFIRM_EXIT_WINDOW", true);
	SetCurrentNode("CONFIRM_EXIT_NO");
}

void ConfirmExitClick()
{
    PauseParticles(true); //fix вылета у форта
	EngineLayersOffOn(false);
	QuitProcess();
	//IDoExit(-1, false); // fix
	//ExitProgram();
}

void ConfirmExitCancel()
{
    XI_WindowDisable("CONFIRM_EXIT_WINDOW",true);
	XI_WindowShow("CONFIRM_EXIT_WINDOW",false);
	XI_WindowDisable("MAIN_WINDOW",false);
	SetCurrentNode("MB_EXITGAME");
}

void ShowConfirmWindow(bool show)
{
	if (show){

		SetCurrentNode("CONFIRM_WINDOW_MB_NO");

		XI_WindowDisable("MAIN_WINDOW", true);
		XI_WindowDisable("CONFIRM_WINDOW", false);
		XI_WindowShow("CONFIRM_WINDOW", true);
		EI_CreateFrame("CONFIRM_WINDOW_BORDER",190,190,610,360);

	} else {

		XI_WindowDisable("CONFIRM_WINDOW", true);
		XI_WindowShow("CONFIRM_WINDOW", false);
		XI_WindowDisable("MAIN_WINDOW", false);

		if(GetSelectable("MB_RESUME"))
			SetCurrentNode("MB_RESUME");
		else
			SetCurrentNode("MB_NEW");
	}
}

void QuitProcess()
{
    // вылетам у форта НЕТ -->
    if (bSeaActive && !bAbordageStarted)
    {
		SendMessage(&AIBalls, "l", MSG_MODEL_RELEASE);
	}
	// вылетам у форта НЕТ <--
	IDoExit(-1, false);
	ExitProgram();
}
