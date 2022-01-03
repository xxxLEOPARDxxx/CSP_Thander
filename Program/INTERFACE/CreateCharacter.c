int curmodel = 0;
int curmanim = 0;
string sCurmanim{10} = {"","начало боя","быстрая атака","мощная атака","attack_feintc_","attack_break_1","parry_","attack_feint_","прыжок","конец боя"};

string totalInfo;
string totalInfo1;
string costume = "обычный";
string sBlockPGG = "None";
int iBlockPGG = 1;
int idLngFile = -1;

int iType = 1;
int iTypeQty = 1;
int iTypeCount = 1;
int iVarCount = 1;

int FState_SEX[3] = {0,0,0};//на старте все три "пола" включены, муж/жен/скелет
bool FState_ANIM = false;

void InitInterface(string iniName)
{
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	startHeroType = 1;

	StartAboveForm(false);

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	//SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);
	SetEventHandler("CheckButtonChange", "ProcessFilter", 0);

	LAi_SetActorTypeNoGroup(PChar);
	SelectOperation();
}

void ProcessBreakExit()
{
	IDoExit( RC_INTERFACE_ANY_EXIT );
}

void ProcessCancelExit()
{
	IDoExit( RC_INTERFACE_ANY_EXIT );
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	//DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");
	DelEventHandler("CheckButtonChange", "ProcessFilter");

	EndAboveForm(true);
	interfaceResultCommand = exitCode;
	EndCancelInterface(true);

	EndQuestMovie();
	//locCameraFollow();
	LAi_SetPlayerType(pchar);

	EndSelectMainCharacter(pchar);
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	if(comName=="leftstep")
	{
		SelectMainCharacter(true);
		return;
	}
	if(comName=="rightstep")
	{
		SelectMainCharacter(false);
		return;
	}

	switch(nodName)
	{
		case "SELECT_LEFT_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				SelectMainCharacter(true);
			}
		break;

		case "SELECT_RIGHT_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				SelectMainCharacter(false);
			}
		break;

		case "COSTUMES_LEFT_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				CycleCirass(false);
			}
		break;

		case "COSTUMES_RIGHT_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				CycleCirass(true);
			}
		break;

		case "ANIMATION_LEFT_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				CycleAnimation(false);
			}
		break;

		case "ANIMATION_RIGHT_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				CycleAnimation(true);
			}
		break;

		case "SELECT_CHARACTER_DONE":
			if(comName=="activate" || comName=="click")
			{
				SelectMainCharacterDone();
			}
		break;

		case "REMOVE_ALL_PGG_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				int  heroQty   = sti(GetNewMainCharacterParam("ps_hero_qty"));
				for (int n=1; n<=heroQty; n++)
				{
					sBlockPGG = "PGG" + n;
					pchar.RemovePGG.(sBlockPGG) = iBlockPGG;
					CheckButton_SetState("REMOVE_PGG_CHECKBOX", 1, iBlockPGG);
				}
				if (iBlockPGG == 1)	iBlockPGG = 0;
				else iBlockPGG = 1;
			}
		break;
	}
}

void CycleAnimation(bool dir)
{
	string anim;
	if (!dir)
	{
		if (curmanim == 0) curmanim = 9;
		else curmanim--;
	}
	if (dir)
	{
		if (curmanim == 9) curmanim = 0;
		else curmanim++;
	}
	LAi_SetActorTypeNoGroup(pchar);
	switch (curmanim)
	{
		case 0:
			LAi_ActorAnimation(pchar, "idle_"+sti(rand(10)+1), "", 0.6);
		break;
		case 1:
			LAi_ActorAnimation(pchar, "normal to fight", "", 0.6);
		break;
		case 2:
			LAi_ActorAnimation(pchar, "attack_fast_"+sti(rand(3)+1), "", 0.6);
		break;
		case 3:
			LAi_ActorAnimation(pchar, "attack_force_"+sti(rand(3)+1), "", 0.6);
		break;
		case 4:
			LAi_ActorAnimation(pchar, "attack_feintc_"+sti(rand(3)+1), "", 0.6);
		break;
		case 5:
			LAi_ActorAnimation(pchar, "attack_break_1", "", 0.6);
		break;
		case 6:
			LAi_ActorAnimation(pchar, "parry_"+sti(rand(3)+1), "", 0.6);
		break;
		case 7:
			LAi_ActorAnimation(pchar, "attack_feint_"+sti(rand(3)+1), "", 0.6);
		break;
		case 8:
			LAi_ActorAnimation(pchar, "jump", "", 0.6);
		break;
		case 9:
			LAi_ActorAnimation(pchar, "fight to normal", "", 0.6);
		break;
	}
}

void CycleCirass(bool dir)
{
	string itemID;
	if (!dir)
	{
		if (curmodel == 0) curmodel = 8;
		else curmodel--;
	}
	if (dir)
	{
		if (curmodel == 8) curmodel = 0;
		else curmodel++;
	}
	switch (curmodel)
	{
		case 0:
			pchar.model = GetSubStringByNum(pchar.HeroModel, 0);
			DeleteAttribute(pchar, "cirassId");
			SetNewModelToChar(pchar);//boal
			costume = "обычный";
		break;
		case 1:
			itemID = "cirass1";
			costume = "кираса 1";
		break;
		case 2:
			itemID = "cirass2";
			costume = "кираса 2";
		break;
		case 3:
			itemID = "cirass3";
			costume = "кираса 3";
		break;
		case 4:
			itemID = "cirass4";
			costume = "кираса 4";
		break;
		case 5:
			itemID = "cirass5";
			costume = "кираса 5";
		break;
		case 6:
			itemID = "suit_1";
			costume = "обноски";
		break;
		case 7:
			itemID = "suit_2";
			costume = "негоциант";
		break;
		case 8:
			itemID = "suit_3";
			costume = "дворянин";
		break;
	}
	SetFormatedText("COSTUME", "Выбранный костюм: "+costume);
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"COSTUME",5);
	if (curmodel != 0) ShowCirassOnCharacter(pchar, CIRASS_ITEM_TYPE, itemID);
}

void ShowCirassOnCharacter(ref chref, string groupID, string itemID)
{
	object emptyItm;
	aref arItm;
	string modelName = "";
	makearef(arItm,emptyItm);
 	int itemNum; // boal 23.01.2004

	if(itemID != "")
	{
		itemNum = Items_FindItem(itemID,&arItm);// boal 23.01.2004
	}

	switch(groupID)
	{
    case CIRASS_ITEM_TYPE:
        if (CheckAttribute(chref, "HeroModel")) // все, у кого есть что одеть
        {
            if (CheckAttribute(arItm, "model"))
            {
                chref.model = GetSubStringByNum(chref.HeroModel, sti(arItm.model));
				if (startherotype == 2 && sti(arItm.model) == 5 && findsubstr(chref.HeroModel, "Whisper" , 0) != -1 && CheckCharacterItem(pchar,"hatWhisper") &&  !CheckAttribute(pchar, "Whisper.NanoCostume"))
				{
					chref.model = "PGG_Whisper_5_Cirass"
				}
                chref.cirassId = itemNum;
            }
            else
            {
                chref.model = GetSubStringByNum(chref.HeroModel, 0);
                DeleteAttribute(chref, "cirassId");
            }
        }
        else
        {
            // тут анализ модели офицера или пирата
            if(CheckAttribute(arItm, "model"))
            {
                chref.cirassId = itemNum;
            }
            else
            {
                DeleteAttribute(chref, "cirassId");
            }
        }
        SetNewModelToChar(chref);//boal
	break;
	}
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void SelectMainCharacterDone()
{
	PlaySound("notebook");
	PChar.Selected = true;

    int idLngFile = LanguageOpenFile("HeroDescribe.txt");
	string sName = LanguageConvertString(idLngFile, "heroName_" + startHeroType);
	string sLastName = LanguageConvertString(idLngFile, "heroLastname_" + startHeroType);
	string sCharacterName = sName + " " + sLastName;
	Log_SetStringToLog("Выбран персонаж " + sCharacterName + ".");

	PChar.DefaultModel = PChar.model;

	SetNewModelToChar(PChar);
	FaceMaker(PChar);

	DeleteAttribute(pchar,"items");
	DeleteAttribute(pchar,"equip");

	ProcessCancelExit();
}

void SelectMainCharacter(bool bLeft)
{
	int idLngFile = LanguageOpenFile("HeroDescribe.txt");
	string sQuantity = LanguageConvertString(idLngFile, "hero_qty");
	int iQuantity = sti(sQuantity);
	string sSex, sAnim, sName;

	while (1)
	{
		if (bLeft)
		{
			startHeroType = startHeroType - 1;
			if (startHeroType <= 0) { startHeroType = iQuantity; }
		}
		else
		{
			startHeroType = startHeroType + 1;
			if (startHeroType > iQuantity) { startHeroType = 1; }
		}

		sSex = LanguageConvertString(idLngFile, "sex_" + startHeroType);
		sAnim = LanguageConvertString(idLngFile, "animation_" + startHeroType);
		if (FState_SEX[0] && sSex == "man") {continue;}
		if (FState_SEX[1] && sSex == "woman") {continue;}
		if (FState_SEX[2] && sSex == "skeleton") {continue;}
		sName = LanguageConvertString(idLngFile, "heroName_" + startHeroType);
		if (FState_ANIM) {if (sAnim == "man" || sAnim == "skeleton" || sAnim == "YokoDias"  || sAnim == "Milenace") {} else continue;}
		break;//выходим из цикла, если все иф не сработали = перс подходит
	}

	sName = LanguageConvertString(idLngFile, "heroName_" + startHeroType);
	string sLastName = LanguageConvertString(idLngFile, "heroLastname_" + startHeroType);
	string sCharacterName = sName + " " + sLastName;

	string sHeroModel = LanguageConvertString(idLngFile, "heroModel_" + startHeroType);
	PChar.HeroModel = sHeroModel;
	string sModel = GetSubStringByNum(PChar.HeroModel, 0);
	string sAni = LanguageConvertString(idLngFile, "animation_" + startHeroType);
	string sMush = LanguageConvertString(idLngFile, "heroMush_" + startHeroType);

	PChar.model = sModel;
	PChar.model.animation = sAni;
	SetNewModelToChar(PChar);

	CreateString(true, "SelectCharacterName", sCharacterName, FONT_CAPTION, COLOR_NORMAL, 395, 545, SCRIPT_ALIGN_CENTER, 1.0);
    LanguageCloseFile(idLngFile);

	curmodel = 0;
	costume = "обычный";
	SetFormatedText("ANIMATION", "Анимации");
	SetFormatedText("COSTUME", "Выбранный костюм: "+costume);
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"COSTUME",5);
	UpdateHeroInfo();

	bool bDelPGG = false;
	sBlockPGG = "PGG" + startHeroType;
	if (CheckAttribute(pchar,"RemovePGG." + sBlockPGG)) bDelPGG = sti(pchar.RemovePGG.(sBlockPGG));
	CheckButton_SetState("REMOVE_PGG_CHECKBOX", 1, bDelPGG);
}

void SelectOperation()
{
	int idLngFile = LanguageOpenFile("HeroDescribe.txt");
	string sQuantity = LanguageConvertString(idLngFile, "hero_qty");
	int iQuantity = sti(sQuantity);

	SetNodeUsing("SELECT_CHARACTER_DONE", true);
	SetNodeUsing("SELECT_CHARACTER_PICTURE", true);
	SetNodeUsing("SELECT_LEFT_BUTTON", true);
	SetNodeUsing("SELECT_RIGHT_BUTTON", true);
	SetNodeUsing("COSTUMES_LEFT_BUTTON", true);
	SetNodeUsing("CHECK_HERO_SEX", true);
	SetNodeUsing("CHECK_HERO_ANIM", true);
	SetNodeUsing("COSTUMES_RIGHT_BUTTON", true);
	SetNodeUsing("ANIMATION_LEFT_BUTTON", true);
	SetNodeUsing("ANIMATION_RIGHT_BUTTON", true);
	SetNodeUsing("ANIMATION", true);
	SetNodeUsing("COSTUME", true);
	SetNodeUsing("INFO_TEXT", true);

	SetFormatedText("ANIMATION", "Анимации");
	SetFormatedText("COSTUME", "Выбранный костюм: "+costume);
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"COSTUME",5);

	LanguageConvertString(idLngFile, "hero_" + startHeroType);

	string sName = LanguageConvertString(idLngFile, "heroName_" + startHeroType);
	string sLastName = LanguageConvertString(idLngFile, "heroLastname_" + startHeroType);
	string sCharacterName = sName + " " + sLastName;

	string sHeroModel = LanguageConvertString(idLngFile, "heroModel_" + startHeroType);
	PChar.HeroModel = sHeroModel;
	string sModel = GetSubStringByNum(PChar.HeroModel, 0);
	string sAni = LanguageConvertString(idLngFile, "animation_" + startHeroType);
	string sMush = LanguageConvertString(idLngFile, "heroMush_" + startHeroType);

	PChar.model = sModel;
	PChar.model.animation = sAni;
	SetNewModelToChar(PChar);

	UpdateHeroInfo();
	CreateString(true, "SelectCharacterName", sCharacterName, FONT_CAPTION, COLOR_NORMAL, 395, 545, SCRIPT_ALIGN_CENTER, 1.0);

    LanguageCloseFile(idLngFile);
}

void UpdateHeroInfo()
{
	int idLngFile = LanguageOpenFile("HeroDescribe.txt");
	totalInfo1 = LanguageConvertString(idLngFile, "hero_" + startHeroType);
	if (MOD_BETTATESTMODE == "On") SetFormatedText("INFO_TEXT", totalInfo1+"\n( Номер ПГГ: "+startHeroType+" | Модель: "+PChar.model+" | Анимация: "+PChar.model.animation+" )");
	else SetFormatedText("INFO_TEXT", totalInfo1);
    SetVAligmentFormatedText("INFO_TEXT");
	LanguageCloseFile(idLngFile);
}

void ProcessFilter()
{
	string sControl = GetEventData();
	int iSelectedCB = GetEventData();
	int iNewState = GetEventData();
	int idLngFile;
//========================================//
	if (sControl == "CHECK_HERO_SEX")
	{
		FState_SEX[iSelectedCB-1] = iNewState;
		if (!iNewState && FState_SEX[0]+FState_SEX[1]+FState_SEX[2] == 1)//нужно разлочить кнопку
		{
			for(i=1;i<4;i++) {SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_HERO_SEX", 5, i, 0);} //разблочим все кнопки
		}
		if (FState_SEX[0]+FState_SEX[1]+FState_SEX[2] == 2) //блочим оставшийся единственным ненажатым чекбокс. иначе вообще все герои будут недоступны и бесконечный цикл
		{
			for(i=1;i<4;i++)
			{
				if (SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_HERO_SEX", 3, i)) continue;
					else {SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_HERO_SEX", 5, i, 1); break;}//блочим ненажатую кнопку и выходим из цикла, так как она одна
			}
		}
		if (iNewState) //отключили какой-то пол
		{
			idLngFile = LanguageOpenFile("HeroDescribe.txt");
			string sSex = LanguageConvertString(idLngFile, "sex_" + startHeroType);
			switch (iSelectedCB-1)
			{
				case 0: if (sSex == "man") SelectMainCharacter(0); break;//если был выбран муж. и мы сняли чекбокс муж., то переходим к следующему персу
				case 1: if (sSex == "woman") SelectMainCharacter(0); break;
				case 2: if (sSex == "skeleton") SelectMainCharacter(0); break;
			}
			LanguageCloseFile(idLngFile);
		}
		return;
	}
//========================================//
	if (sControl == "CHECK_HERO_ANIM")
	{
		FState_ANIM = iNewState;
		if (iNewState) //отключили анимки
		{
			idLngFile = LanguageOpenFile("HeroDescribe.txt");
			string sAnim = LanguageConvertString(idLngFile, "animation_" + startHeroType);
			string sName = LanguageConvertString(idLngFile, "heroName_" + startHeroType);
			if (FState_ANIM) { if (sAnim == "man" || sAnim == "skeleton" || sAnim == "YokoDias"  || sAnim == "Milenace") {} else SelectMainCharacter(0); }
			LanguageCloseFile(idLngFile);
		}
		return;
	}

	if (sControl == "REMOVE_PGG_CHECKBOX")
	{
		sBlockPGG = "PGG" + startHeroType;
		if (iNewState)
		{
			pchar.RemovePGG.(sBlockPGG) = 1;
		}
		else
		{
			pchar.RemovePGG.(sBlockPGG) = 0;
		}
		return;
	}
}
