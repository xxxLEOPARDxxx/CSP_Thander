// Warship 06.09.08 Переделка интерфейса обыска трупов, обмена с офами и сундука
// Большая часть интерфейса - это интерфейс покупки/продажи предметов

#define INTERFACETYPE_EXCHANGE_ITEMS		"ExchangeItems"
#define INTERFACETYPE_CHEST					"Chest"
#define INTERFACETYPE_DEADMAN				"Deadman"
#define INTERFACETYPE_BARREL				"Barrel"
#define INTERFACE_ITEMSBOX_CHAR_ARROYSIZE	10

int nCurScrollNum = 0;
int iCharCapacity, iCharQty, iStoreQty;
float fCharWeight, fStoreWeight, fWeight;
bool bShowChangeWin = false;
bool DelLogin = false;
int  BuyOrSell = 0;
string sChrId, sFaceID, sCurItem;
ref refCharacter;
bool bBoxUsed = false; // Сундук-ли?
aref refToChar, arChest, arDeadChar;
String sCharactersArroy[INTERFACE_ITEMSBOX_CHAR_ARROYSIZE] = {"", "", "", "", "", "", "", "", "", ""};

int iTableAddAllBtnX = 270;
int iTableAddAllBtnY = 160;
int iTableRemoveAllBtnX = 504;
int iTableRemoveAllBtnY = 160;

int iCurrentTabMode = 3; // Текущий режим сортировки
String sInterfaceType;

int iLinesCount = 0;

int lastsort = 0;//мало??? - нужно для каждой таблицы запоминать, если в интерфейсе их может быть несколько???
bool blastsort;

int chestsnum;
int curchest = 1;
aref box1;
aref box2;
aref box3;
aref box4;

void InitInterface_RS(string iniName, ref itemsRef, string faceID)
{
	if (loadedLocation.id == Get_My_Cabin())
	{
		aref chests;
		makearef(chests,loadedLocation.locators.box);
		chestsnum = GetAttributesNum(chests);
	}
	sFaceID = faceID;
	sInterfaceType = sGetInterfaceType();
	if(sInterfaceType == INTERFACETYPE_BARREL)
	{
		StartAboveForm(true);
	}
	else
	{
		StartAboveForm(false); // Warship fix 17.04.09 паузить или нет игру. Если false - не паузить. Нужно для обысков сундуков - кражи
	}
	String Tab3Caption;
	refCharacter = GetMainCharacter();
	makearef(refToChar, itemsRef);

	if(CheckAttribute(itemsRef, "Money"))
	{
		Log_TestInfo("Денег - "+itemsRef.money);
	}

	LAi_SetActorTypeNoGroup(PChar); // Тип актера - чтоб с нами могли побазарить, если увидели в сундуке

	if(sInterfaceType == INTERFACETYPE_CHEST || sInterfaceType == INTERFACETYPE_BARREL) // Если сундук или бочка
	{
		if(!LAi_boarding_process)
		{
			QuestCheckTakeBoxes(itemsRef); // Перехват
		}

		makearef(arChest, itemsRef);
		bBoxUsed = true;
	}

	if(sInterfaceType == INTERFACETYPE_EXCHANGE_ITEMS || sInterfaceType == INTERFACETYPE_DEADMAN)
	{
		if(sInterfaceType == INTERFACETYPE_DEADMAN) // Если обыск трупа
		{
			makearef(arDeadChar, itemsRef);
			Tab3Caption = "Предметы на трупе";
		}

		iSetCharIDToCharactersArroy(itemsRef); // Не нужно это, но и не помешает
		bBoxUsed = false;

		// boal -->
		if(!CheckAttribute(itemsRef, "HoldEquip") && CheckAttribute(itemsRef, "rank"))
		{
			if(sti(itemsRef.rank) < sti(refCharacter.rank)) // только, если ранг больше
			{
				RemoveCharacterEquip(itemsRef, GUN_ITEM_TYPE);
				if(!IsEquipCharacterByItem(itemsRef, "unarmed"))
				{
					RemoveCharacterEquip(itemsRef, BLADE_ITEM_TYPE);
				}

				RemoveCharacterEquip(itemsRef, CIRASS_ITEM_TYPE); //броня 081004 boal
				RemoveCharacterEquip(itemsRef, BACKPACK_ITEM_TYPE); //броня 081004 boal
			}
		}
		// boal <--
	}

	if(sInterfaceType == INTERFACETYPE_CHEST || sInterfaceType == INTERFACETYPE_DEADMAN) // проверка квестовых ситуаций в каюте кэпа если сундук или обыск трупа
	{
		ShipSituation_SetQuestSituation(ShipSituation_0);
	}

	GameInterface.TABLE_LIST.hr.td1.str = "Кол-во";
	GameInterface.TABLE_LIST.hr.td1.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td2.str = "Общий\nвес";
	GameInterface.TABLE_LIST.hr.td2.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td2.textoffset = "0, 2";
	GameInterface.TABLE_LIST.hr.td3.str = "Наименование предметов";
	GameInterface.TABLE_LIST.hr.td3.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td4.str = "Общий\nвес";
	GameInterface.TABLE_LIST.hr.td4.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td4.textoffset = "0, 2";
	GameInterface.TABLE_LIST.hr.td5.str = "Кол-во";
	GameInterface.TABLE_LIST.hr.td5.scale = 0.9;

	FillCharactersScroll();

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	if (checkattribute(pchar, "iCurrentTabMode") && sInterfaceType == INTERFACETYPE_EXCHANGE_ITEMS) iCurrentTabMode = sti(pchar.iCurrentTabMode); //запоминание вкладки только если обмен
	SetControlsTabMode(iCurrentTabMode);

	CreateString(true, "CharName", "", FONT_NORMAL, COLOR_MONEY, 405, 108, SCRIPT_ALIGN_CENTER, 1.0);

	InterfaceInitButtons(refCharacter);

	// Тут позиционим кнопки взятия на таблице
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_ALL_BUTTON", 0, iTableAddAllBtnX, iTableAddAllBtnY, iTableAddAllBtnX + 30, iTableAddAllBtnY + 30, 0);
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_ALL_BUTTON", 0, iTableRemoveAllBtnX, iTableRemoveAllBtnY, iTableRemoveAllBtnX + 30, iTableRemoveAllBtnY + 30, 0);

	if(sInterfaceType == INTERFACETYPE_CHEST || sInterfaceType == INTERFACETYPE_BARREL) // Только если сундук - у него никаких кнопок нету
	{
		/* CreateString(true, "VersionInfo", VERSION_NUMBER1 + GetVerNum(), FONT_CAPTION, COLOR_NORMAL, 400, 550, SCRIPT_ALIGN_CENTER, 0.8);
		CreateString(true, "DevTeam", VERSION_NUMBER3, FONT_CAPTION, COLOR_NORMAL, 400, 566, SCRIPT_ALIGN_CENTER, 0.8); */

		if(sInterfaceType == INTERFACETYPE_CHEST)	Tab3Caption = "Предметы в сундуке";
		if(sInterfaceType == INTERFACETYPE_BARREL)	Tab3Caption = "Предметы в бочонке";
	}

	if(sInterfaceType == INTERFACETYPE_EXCHANGE_ITEMS) // Установим строки с именами
	{
		GameInterface.strings.CharName = GetFullName(refToChar);
		Tab3Caption = "Предметы у офицера";
	}
	else
	{
		GameInterface.strings.CharName = GetFullName(refCharacter);
	}

	SetCharWeight();
	SetDescription();

	SetCharacterMoneyToGold(refCharacter); // Переводим деньги ГГ в золото
	SetCharacterMoneyToGold(itemsRef);
	iSetCharIDToCharactersArroy(refCharacter); // Заносим в список ГГ

	AddToTable(itemsRef);
	ShowGoodsInfo(GameInterface.TABLE_LIST.tr1.id);
	FillCharactersImages();

	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",5);

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);
	SetEventHandler("OnTableClick", "OnTableClick", 0);
	SetEventHandler("MouseRClickUP","EndTooltip",0);
	SetEventHandler("ShowHelpHint", "ShowHelpHint", 0);
	SetEventHandler("ShowItemInfo", "ShowItemInfo", 0);
	SetEventHandler("TableSelectChange", "CS_TableSelectChange", 0);
	SetEventHandler("TransactionOK", "TransactionOK", 0);
	SetEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT", 0);
	SetEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON", 0);
	SetEventHandler("ADD_BUTTON","ADD_BUTTON",0);
	SetEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON", 0);
	SetEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON", 0);
	SetEventHandler("frame","ProcessFrame",1);
	SetEventHandler("eTabControlPress", "procTabChange", 0); // Событие смены закладки

	if (csmCA(pchar, "CSM.LootCollector.Run"))
		SetFormatedText("STORECAPTION1", "Вот вся добыча на данный момент, кэп!"));
	else
		SetFormatedText("STORECAPTION1", XI_ConvertString(sGetInterfaceTypeStr("titleExchangeItems", "titleItemsBox", "titleDeadItems","titleBarrel")));

	if (csmCA(pchar, "CSM.LootCollector.Run") && !csmCA(pchar, "CSM.LootCollector.Tutor"))
	{
		string sHeader, sText1, sText2, sText3;

		// 2do: потом добавить -->
		string sPicture = "none";
		string sGroup = "none";
		string sGroupPicture = "none";
		// <--

		sHeader = "Новая система лута при абордаже";
		sText1 = "Более не нужно заглядывать в каждый угол или карман!\n\n" +
				 "Все вещи из сундуков и с трупов будут собраны здесь.\n" +
				 "В капитанских каютах процесс обыска остался прежним.";
		sText2 = "Запуск сундука с добычей доступен в любой момент после окончания боя\n" +
				 "Горячая клавиша по умолчанию: 'тильда', она же 'ё'\n" +
				 "Можно переназначить в настройках игры.";
		sText3 = "Нажмите правую кнопку мыши, чтобы убрать это сообщение";

		CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,255,130), sText3, argb(255,175,255,175), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);
	}

	CreateString(true, "TabCaption1", "Все предметы", FONT_NORMAL, COLOR_NORMAL, 230, 525, SCRIPT_ALIGN_CENTER, 0.8);
	CreateString(true, "TabCaption2", "Предметы героя", FONT_NORMAL, COLOR_NORMAL, 348, 525, SCRIPT_ALIGN_CENTER, 0.8);
	CreateString(true, "TabCaption3", Tab3Caption, FONT_NORMAL, COLOR_NORMAL, 467, 525, SCRIPT_ALIGN_CENTER, 0.8);
	CreateString(true, "TabCaption4", "Оружие и зелья", FONT_NORMAL, COLOR_NORMAL, 587, 525, SCRIPT_ALIGN_CENTER, 0.8);
}

void InterfaceInitButtons(ref _refCharacter)
{
	String sInterfaceType = sGetInterfaceType();

	SetNodeUsing("GETALL_BUTTON", false);
	SetNodeUsing("DELBODY_BUTTON", false);
	SetNodeUsing("SKULL_BUTTON", false);
	SetNodeUsing("CYCLE_CHEST", false);

	switch(sInterfaceType)
	{
		case INTERFACETYPE_EXCHANGE_ITEMS:
			SetNodeUsing("GETALL_BUTTON", true);
		break;

		case INTERFACETYPE_DEADMAN:
			SetNodeUsing("GETALL_BUTTON", true);
			SetNodeUsing("DELBODY_BUTTON", true);

			// Проверка на возможность использования черепа
			if(CheckCharacterItem(_refCharacter, "SkullAztec") && IsAztecSkullOfficer(characters[sti(arDeadChar.index)]) && LAi_IsDead(characters[sti(arDeadChar.index)]) && CheckNPCQuestDate(_refCharacter, "AztecSkull"))
			{
				SetNodeUsing("SKULL_BUTTON", true);
			}
		break;

		case INTERFACETYPE_CHEST:
			if (csmCA(pchar, "CSM.LootCollector.Run"))
			{
				SetNodeUsing("GETALL_BUTTON", true);
			}
			if (loadedLocation.id == Get_My_Cabin())
			{
				SetNodeUsing("CYCLE_CHEST", true);
			}
		break;

		case INTERFACETYPE_BARREL:

		break;
	}
}

void SetCharacterMoneyToGold(aref rChar) // В интерфейсе оперируем с деньгами как с предметом "gold"
{
	string sInterfaceType = sGetInterfaceType();
	bool bOk = sInterfaceType == INTERFACETYPE_CHEST || sInterfaceType == INTERFACETYPE_BARREL;
	if(bOk && !CheckAttribute(rChar, "ID"))
	{
		if(!CheckAttribute(rChar, "Items.Gold")) rChar.Items.Gold = 0;
		rChar.items.gold = sti(rChar.items.gold)+sti(GetAttrValue(rChar, "money")); // По квестам ложится сразу золото, а не деньги
	}
	else
	{
		rChar.items.gold = sti(GetAttrValue(rChar, "money"));
	}
}

int iSetCharIDToCharactersArroy(ref _rChar)
{
	string sCurArroyID;
	string sCharID = _rChar.id;
	for(int i=0; i<INTERFACE_ITEMSBOX_CHAR_ARROYSIZE; i++)
	{
		sCurArroyID = sCharactersArroy[i];
		if(sCurArroyID == sCharID) return i;

		if(sCurArroyID == "")
		{
			sCharactersArroy[i] = sCharID;
			return i;
		}
	}

	// Не знаю, возможна ли нехватка свободных, ведь define INTERFACE_ITEMSBOX_CHAR_ARROYSIZE 10
	sCharactersArroy[0] = sCharID; // Свободных нету, но поставить-то нужно
	return 0;
}

void MakeMoneyFromGoldWithowtChest()
{
	string sCurArroyID;
	ref arCurChar;
	for(int i=0; i<INTERFACE_ITEMSBOX_CHAR_ARROYSIZE, i++)
	{
		sCurArroyID = sCharactersArroy[i];
		if(sCurArroyID != "")
		{
			arCurChar = CharacterFromID(sCurArroyID);
			arCurChar.money = GetCharacterItem(arCurChar, "Gold");
			DeleteAttribute(arCurChar, "items.gold");
		}
	}
}

void MakeMoneyFromGoldWithChest(aref arChest)
{
	arChest.money = GetCharacterItem(arChest, "Gold");
	DeleteAttribute(arChest, "items.gold");
	MakeMoneyFromGoldWithowtChest();
}

void MakeMoneyFromGoldWithDeadMan(aref arDeadChar)
{
	arDeadChar.money = GetCharacterItem(arDeadChar, "Gold");
	DeleteAttribute(arDeadChar, "items.gold");
	MakeMoneyFromGoldWithowtChest();
}

string sGetInterfaceType()
{
	string sRetStr = INTERFACETYPE_EXCHANGE_ITEMS;
	if(sFaceID == "") // Сундук
	{
		sRetStr = INTERFACETYPE_CHEST;
	}

	if(sFaceID == "Barrel") // Бочонок
	{
		sRetStr = INTERFACETYPE_BARREL;
	}

	if(sFaceID == "666") // Мертвец
	{
		sRetStr = INTERFACETYPE_DEADMAN;
	}

	return sRetStr;
}

string sGetInterfaceTypeStr(string sExchangeItems, string sChest, string sDeadMan, string sBarrel)
{
	string sType = sGetInterfaceType();
	string sRetStr="";

	switch(sType)
	{
		case INTERFACETYPE_EXCHANGE_ITEMS:
			sRetStr = sExchangeItems;
		break;

		case INTERFACETYPE_CHEST:
			sRetStr = sChest;
		break;

		case INTERFACETYPE_BARREL:
			sRetStr = sBarrel;
		break;

		case INTERFACETYPE_DEADMAN:
			sRetStr = sDeadMan;
		break;
	}

	return sRetStr;
}

void SetCharactersMoneyOnExit() // Выставим деньги
{
	string sInterfaceType = sGetInterfaceType();
	switch(sInterfaceType)
	{
		case INTERFACETYPE_EXCHANGE_ITEMS:
			MakeMoneyFromGoldWithowtChest();
		break;

		case INTERFACETYPE_CHEST:
			MakeMoneyFromGoldWithChest(arChest);
		break;

		case INTERFACETYPE_BARREL:
			MakeMoneyFromGoldWithChest(arChest);
		break;

		case INTERFACETYPE_DEADMAN:
			MakeMoneyFromGoldWithDeadMan(arDeadChar);
		break;
	}
}

void ShowItemsWeight()
{
	string sInterfaceType = sGetInterfaceType();
	int iWeight, iMaxWeight;
	CreateString(true, "ToCharacterWeightStr", "", FONT_NORMAL, COLOR_NORMAL, 601, 110, SCRIPT_ALIGN_CENTER, 0.9);

	if(sInterfaceType == INTERFACETYPE_EXCHANGE_ITEMS)
	{
		GameInterface.strings.ToCharacterWeightStr =  XI_ConvertString("Weight") + ": " + FloatToString(GetItemsWeight(refToChar), 1) + " / " + GetMaxItemsWeight(refToChar);
	}
	else
	{
		GameInterface.strings.ToCharacterWeightStr = "";
	}

	CreateString(true, "MyCharacterWeightStr", XI_ConvertString("Weight") + ": " + FloatToString(GetItemsWeight(refCharacter), 1) + " / " + GetMaxItemsWeight(refCharacter), FONT_NORMAL, COLOR_NORMAL, 215, 110, SCRIPT_ALIGN_CENTER, 0.9);
}

void ProcessBreakExit()
{
	IDoExit(RC_INTERFACE_FOOD_INFO_EXIT);
}

void ProcessCancelExit()
{
	if(bShowChangeWin)
	{
		EndTooltip();
	}
	else
	{
		IDoExit(RC_INTERFACE_FOOD_INFO_EXIT);
	}
}

void IDoExit(int exitCode)
{
	if (sInterfaceType == INTERFACETYPE_EXCHANGE_ITEMS) pchar.iCurrentTabMode = iCurrentTabMode;

	ref arCurChar;
	string sCurArroyID;
	SetCharactersMoneyOnExit(); // Переводим монеты "gold" в деньгиъ
	RefreshEquippedMaps(GetMainCharacter()); // рефрешим карты, если купили
	ref sld;

	if(!bBoxUsed)
	{
		for(int i=0; i<INTERFACE_ITEMSBOX_CHAR_ARROYSIZE, i++)
		{
			sCurArroyID = sCharactersArroy[i];
			if(sCurArroyID != "")
			{
				arCurChar = CharacterFromID(sCurArroyID);
				if(IsMainCharacter(arCurChar)) continue;

				if(CheckAttribute(arCurChar, "skill.Fencing")) //boal fix иначе не берут саблю при перегрузе
				{
					EquipCharacterByItem(arCurChar, FindCharacterItemByGroup(arCurChar,BLADE_ITEM_TYPE));
				}

				/*if(CheckAttribute(arCurChar, "skill.Fencing") &&  GetCharacterSkill(arCurChar, "Fencing") > 0.1)
				{
					EquipCharacterByItem(arCurChar, FindCharacterItemByGroup(arCurChar, CIRASS_ITEM_TYPE)); // boal 08.10.04 броню офицерам
				}*/

				if(CheckAttribute(arCurChar, "skill.Pistol") && GetCharacterSkill(arCurChar,"Pistol") > 0.1 )
				{
					EquipCharacterByItem(arCurChar, FindCharacterItemByGroup(arCurChar, GUN_ITEM_TYPE));
				}

				if(CheckAttribute(arCurChar, "RealCompanionIdx")) // 1.2.4 обмен с компаньоном
				{
					sld = GetCharacter(sti(arCurChar.RealCompanionIdx));
					ChangeAttributesFromCharacter(sld, arCurChar, false); //тут предметы и деньги
				}
			}
		}
	}
	else
	{
		bMainCharacterInBox = false; // снимаем флаг 'в боксе'
	}

	EndAboveForm(true);

	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");

	DelEventHandler("OnTableClick", "OnTableClick");
	DelEventHandler("MouseRClickUP","EndTooltip");
	DelEventHandler("ShowHelpHint", "ShowHelpHint");
	DelEventHandler("ShowItemInfo", "ShowItemInfo");
	DelEventHandler("TableSelectChange", "CS_TableSelectChange");
	DelEventHandler("frame","ProcessFrame");
	DelEventHandler("TransactionOK", "TransactionOK");
	DelEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT");
	DelEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON");
	DelEventHandler("ADD_BUTTON","ADD_BUTTON");
	DelEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON");
	DelEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON");

	DelEventHandler("eTabControlPress", "procTabChange"); // Событие смены закладки

	interfaceResultCommand = exitCode;

	string sInterfaceType = sGetInterfaceType();
	if (sInterfaceType == INTERFACETYPE_DEADMAN)
	{
		if (DelLogin)
		{
			//Log_Info("Должен удалиться");
			Dead_DelLoginedCharacter(refToChar);
		}
	}

	EndCancelInterface(true);

	LAi_SetPlayerType(PChar); // Возвращаем тип игрока

	// boal проверка на перегруз 21.01.2004 -->
	CheckAndSetOverloadMode(GetMainCharacter());
	// boal 21.01.2004 <--

	// CSM -->
	if (csmCA(pchar, "CSM.LootCollector.Run"))
	{
		csmHideLootCollectorBox(false);

		if (!csmCA(pchar, "CSM.LootCollector.Tutor"))
		{
			pchar.CSM.LootCollector.Tutor = true;
			ClearAllLogStrings();
			Log_Info("Клавиша запуска сундука с добычей: тильда, она же русская 'Ё'");
			Log_Info("Можно изменить на другую в настройках игры");
			PlaySound("interface\notebook.wav");
		}
	}

	csmDA(pchar, "CSM.LootCollector.Run");
	// CSM <--
	if (!bLandInterfaceStart)
	{
		StartBattleLandInterface();
	}
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
		case "TABLE_ADD_ALL_BUTTON":
			if(comName == "activate" || comName == "click")
			{
				ADD_ALL_BUTTON();
				TransactionOK();
			}
		break;

		case "TABLE_REMOVE_ALL_BUTTON":
			if(comName == "activate" || comName == "click")
			{
				REMOVE_ALL_BUTTON();
				TransactionOK();
			}
		break;

		case "QTY_OK_BUTTON":
			if(comName=="leftstep")
			{
				ADD_BUTTON();
			}
			if(comName=="rightstep")
			{
				REMOVE_BUTTON();
			}
			if(comName=="speedleft")
			{
				ADD_ALL_BUTTON();
			}
			if(comName=="speedright")
			{
				REMOVE_ALL_BUTTON();
			}
		break;

		case "QTY_CANCEL_BUTTON":
			if(comName=="leftstep")
			{
				ADD_BUTTON();
			}
			if(comName=="rightstep")
			{
				REMOVE_BUTTON();
			}
			if(comName=="speedleft")
			{
				ADD_ALL_BUTTON();
			}
			if(comName=="speedright")
			{
				REMOVE_ALL_BUTTON();
			}
		break;

		case "TABLE_LIST":
			if(comName=="leftstep")
			{
				ADD_BUTTON();
			}
			if(comName=="rightstep")
			{
				REMOVE_BUTTON();
			}
			if(comName=="speedleft")
			{
				ADD_ALL_BUTTON();
			}
			if(comName=="speedright")
			{
				REMOVE_ALL_BUTTON();
			}
		break;

		case "GETALL_BUTTON":
			if(comName == "activate" || comName == "click")
			{
				onGetAllBtnClick();
			}
		break;

		//navy --> Убрать тело ;)
		case "DELBODY_BUTTON":
			if(comName=="downstep" && GetSelectable("SKULL_BUTTON"))
			{
				SetCurrentNode("SKULL_BUTTON");
			}

			if(comName=="activate" || comName=="click")
			{
				//оставил только на DEV версии... Алекс, только на тебя надежда, что в длл-ке поправишь.
				/*if (MOD_BETTATESTMODE == "On")
				{
					Dead_DelLoginedCharacter(refToChar);
					CharacterExitFromLocation(&Characters[sti(refToChar.index)]);
				}*/
				//все равно падает.. не понятно :(
				//PostEvent("LAi_event_Character_Dead", 10, "i", &Characters[sti(refToChar.index)]);
				Dead_DelLoginedCharacter(refToChar);
				ProcessCancelExit();
			}
		break;
		//navy <--

		case "SKULL_BUTTON":
			if(comName=="upstep")
			{
				SetCurrentNode("DELBODY_BUTTON");
			}

			if(comName=="activate" || comName=="click")
			{
				SetNPCQuestDate(refCharacter, "AztecSkull"); //запомним день
				OfficerReincarnation(&characters[sti(refToChar.index)]);
				Dead_DelLoginedCharacter(refToChar);
				ProcessCancelExit();
			}
		break;
		case "CYCLE_CHEST":
			if(comName=="activate" || comName=="click")
			{
				aref chest;
				string box;
				if (curchest <= chestsnum)
				{
					box = "box"+curchest;
					makearef(chest,loadedLocation.(box));
					SetCharactersMoneyOnExit();
					SetCharacterMoneyToGold(refCharacter); // Переводим деньги ГГ в золото
					SetCharacterMoneyToGold(chest);
					iSetCharIDToCharactersArroy(refCharacter); // Заносим в список ГГ
					AddToTable(chest);
					SetFormatedText("STORECAPTION1","Сундук каюты под номером "+curchest);
					curchest = curchest+1;
				}
				else
				{
					curchest = 1;
					box = "box"+curchest;
					makearef(chest,loadedLocation.(box));
					SetCharactersMoneyOnExit();
					SetCharacterMoneyToGold(refCharacter); // Переводим деньги ГГ в золото
					SetCharacterMoneyToGold(chest);
					iSetCharIDToCharactersArroy(refCharacter); // Заносим в список ГГ
					AddToTable(chest);
					SetFormatedText("STORECAPTION1","Сундук каюты под номером "+curchest);
					curchest = curchest+1;
				}
				StartAboveForm(false);
			}
		break;
	}
}

void procTabChange()
{
	int comIndex = GetEventData();
	String nodName = GetEventData();
	SetCurrentNode("TABLE_LIST");

	// Сами закладки оказались почему-то ненажимаемыми - проверка на кнопки
	switch(nodName)
	{
		case "TABSTR_1":
			SetControlsTabMode(1)
		break;

		case "TABSTR_2":
			SetControlsTabMode(2)
		break;

		case "TABSTR_3":
			SetControlsTabMode(3)
		break;

		case "TABSTR_4":
			SetControlsTabMode(4)
		break;
	}
}

void SetControlsTabMode(int _mode)
{
	String Pic1 = "TabSelected";
	String Pic2 = Pic1;
	String Pic3 = Pic1;
	String Pic4 = Pic1;

	switch(_mode)
	{
		case 1:
			Pic1 = "TabDeSelected";
		break;

		case 2:
			Pic2 = "TabDeSelected";
		break;

		case 3:
			Pic3 = "TabDeSelected";
		break;

		case 4:
			Pic4 = "TabDeSelected";
		break;
	}

	iCurrentTabMode = _mode;

	// Выставим таблицу в начало
	GameInterface.TABLE_LIST.select = 1;
	GameInterface.TABLE_LIST.top = 0;

	// Тут идет рефрешь предметов
	AddToTable(refToChar);

	// Сбросим позицию стрелок
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_ALL_BUTTON", 0, iTableAddAllBtnX, iTableAddAllBtnY, iTableAddAllBtnX + 30, iTableAddAllBtnY + 30, 0);
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_ALL_BUTTON", 0, iTableRemoveAllBtnX, iTableRemoveAllBtnY, iTableRemoveAllBtnX + 30, iTableRemoveAllBtnY + 30, 0);

	SetNewGroupPicture("TABBTN_1", "TABS", Pic1);
	SetNewGroupPicture("TABBTN_2", "TABS", Pic2);
	SetNewGroupPicture("TABBTN_3", "TABS", Pic3);
	SetNewGroupPicture("TABBTN_4", "TABS", Pic4);
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void FillCharactersScroll()
{
	int i;
	string faceName;
	string attributeName;
	string PsgAttrName;
	int _curCharIdx;
	ref _refCurChar;
	aref pRef, pRef2;
	bool bOk;
	string sInterfaceType = sGetInterfaceType();
	DeleteAttribute(&GameInterface, "CHARACTERS_SCROLL");

	nCurScrollNum = -1;
	GameInterface.CHARACTERS_SCROLL.current = 0;
	makearef(pRef,pchar.Fellows.Passengers);

	int nListSize = GetPassengersQuantity(pchar);
	int nListSizeFree = GetNotQuestPassengersQuantity(pchar);

	GameInterface.CHARACTERS_SCROLL.NotUsed = 6;
	GameInterface.CHARACTERS_SCROLL.ListSize = nListSizeFree + 2;

	GameInterface.CHARACTERS_SCROLL.ImagesGroup.t0 = "EMPTYFACE";
	GameInterface.CHARACTERS_SCROLL.ImagesGroup.t1 = "BOX_IMAGE";

	FillFaceList("CHARACTERS_SCROLL.ImagesGroup", pchar, 2); // passengers

	GameInterface.CHARACTERS_SCROLL.BadTex1 = 0;
	GameInterface.CHARACTERS_SCROLL.BadPic1 = "emptyface";

	string sCharID = "";
	int iCharIDX;

	int m = 0;
	if(sInterfaceType != INTERFACETYPE_EXCHANGE_ITEMS)
	{
		attributeName = "pic" + (m + 1);
		GameInterface.CHARACTERS_SCROLL.(attributeName).character = nMainCharacterIndex;
		GameInterface.CHARACTERS_SCROLL.(attributeName).img1 = GetFacePicName(pchar);
		GameInterface.CHARACTERS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup","FACE128_" + pchar.FaceID);
		m++;
	}
	else // При обмене предметами с офом первая картинка - собсно офф
	{
		sCharID = refToChar.ID;
		iCharIDX = GetCharacterIndex(sCharID);
		attributeName = "pic" + (m + 1);

		SetCharacterMoneyToGold(refToChar);
		iSetCharIDToCharactersArroy(refToChar); // Пометим его для удаления золота и дачи денег

		GameInterface.CHARACTERS_SCROLL.(attributeName).character = iCharIDX;
		GameInterface.CHARACTERS_SCROLL.(attributeName).img1 = GetFacePicName(refToChar);
		GameInterface.CHARACTERS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup","FACE128_" + refToChar.FaceID);
		m++;
	}

	for(i = 0; i < nListSize; i++)
	{
		_curCharIdx = GetPassenger(pchar, i);

		bOk = CheckAttribute(&characters[_curCharIdx], "prisoned") && sti(characters[_curCharIdx].prisoned) == true;
		if(_curCharIdx != -1  && !CheckAttribute(&characters[_curCharIdx], "isquest") && !bOk)
		{
			if(IsOfficer(&characters[_curCharIdx]) && PChar.location == Characters[_curCharIdx].location)  // boal // fix - ГГ и офы должны быть в одной локации
			{
				if(sCharID == characters[_curCharIdx].ID) continue;

				SetCharacterMoneyToGold(GetCharacter(_curCharIdx));
				iSetCharIDToCharactersArroy(GetCharacter(_curCharIdx)); // Пометим его для удаления золота и дачи денег
				attributeName = "pic" + (m + 1);
				GameInterface.CHARACTERS_SCROLL.(attributeName).character = _curCharIdx;
				GameInterface.CHARACTERS_SCROLL.(attributeName).img1 = GetFacePicName(GetCharacter(_curCharIdx));
				GameInterface.CHARACTERS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup","FACE128_"+Characters[_curCharIdx].FaceID);
				m++;
				continue;
			}
			if(IsOfficer(&characters[_curCharIdx]) && PChar.location != Characters[_curCharIdx].location && HasSubStr(pchar.location,"_bank"))  // fix - ячейка банковская и аборды
			{
				if(sCharID == characters[_curCharIdx].ID) continue;

				SetCharacterMoneyToGold(GetCharacter(_curCharIdx));
				iSetCharIDToCharactersArroy(GetCharacter(_curCharIdx)); // Пометим его для удаления золота и дачи денег
				attributeName = "pic" + (m + 1);
				GameInterface.CHARACTERS_SCROLL.(attributeName).character = _curCharIdx;
				GameInterface.CHARACTERS_SCROLL.(attributeName).img1 = GetFacePicName(GetCharacter(_curCharIdx));
				GameInterface.CHARACTERS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup","FACE128_"+Characters[_curCharIdx].FaceID);
				m++;
			}
		}
	}
	if (HasSubStr(loadedLocation.id,"_bank"))
	{
		ref cabinloc = &locations[FindLocation(Pchar.SystemInfo.CabinType)];
		chestsnum = 0;
		if (CheckAttribute(cabinloc,"box1")) {chestsnum++; makearef(box1,cabinloc.box1);}
		if (CheckAttribute(cabinloc,"box2")) {chestsnum++; makearef(box2,cabinloc.box2);}
		if (CheckAttribute(cabinloc,"box3")) {chestsnum++; makearef(box3,cabinloc.box3);}
		if (CheckAttribute(cabinloc,"box4")) {chestsnum++; makearef(box4,cabinloc.box4);}
		for (i = 1;i <= chestsnum;i++)
		{
			attributeName = "pic" + (m + 1);
			GameInterface.CHARACTERS_SCROLL.(attributeName).character = "box"+i;
			GameInterface.CHARACTERS_SCROLL.(attributeName).img1 = "BoxImage";
			GameInterface.CHARACTERS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup","BOX_IMAGE");
			m++;
		}
	}
}

void AddToTable(ref rChar)
{
	string sList, sItem;
	int n, i, iLeftQty, iRightQty, iSelLine, iTemp;
	ref rItem;
	bool ok;
	bool ok1 = false;
	n = 1;
	int iRightQtyTotal=0;

	// Warship fix 31.05.09 - слетала текущая полоска + кнопочки забрать/отдать все
	// Садо-мазо получилось еще то
	ok = iCurrentTabMode == 2 || iCurrentTabMode == 3; // Долбаный шторм не понимает И и ИЛИ в одном выражении, даж со скобками
	if(ok && iLinesCount > 2)
	{
		if(sti(GameInterface.TABLE_LIST.select) + 1 == iLinesCount)
		{
			iLinesCount -= 2;
			GameInterface.TABLE_LIST.select = iLinesCount;

			iSelLine = iLinesCount;

			if(CheckAttribute(&GameInterface, "TABLE_LIST.top"))
			{
				if(sti(GameInterface.TABLE_LIST.top) > 0)
				{
					GameInterface.TABLE_LIST.top = sti(GameInterface.TABLE_LIST.top) - 1;
				}

				iSelLine = iLinesCount - sti(GameInterface.TABLE_LIST.top);
			}

			SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_ALL_BUTTON", 0, iTableAddAllBtnX, iTableAddAllBtnY + 30 * (iSelLine - 1), iTableAddAllBtnX + 30, iTableAddAllBtnY + 30 * (iSelLine - 1) + 30, 0);
			SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_ALL_BUTTON", 0, iTableRemoveAllBtnX, iTableRemoveAllBtnY + 30 * (iSelLine - 1), iTableRemoveAllBtnX + 30, iTableRemoveAllBtnY + 30 * (iSelLine - 1) + 30, 0);

			sList = "tr" + sti(GameInterface.TABLE_LIST.select);
			sCurItem = GameInterface.TABLE_LIST.(sList).id;
			ShowGoodsInfo(sCurItem);
		}
		else
		{
			GameInterface.TABLE_LIST.select = sti(GameInterface.TABLE_LIST.select) + 1;

			ok1 = true; // См. ниже проверку if(ok1) - бред-бредом конечно, но по-другому не получается
		}
	}

	iLinesCount = 1;

	Table_Clear("TABLE_LIST", false, true, false);

	iLeftQty  = GetCharacterFreeItem(refCharacter, "Gold");
	iRightQty = GetCharacterFreeItem(rChar, "Gold");
	if (iRightQty>0) iRightQtyTotal += 1;

	// Фикс - должно быть всегда, иначе у нищих офов слетает стрелочки
	//if(iLeftQty > 0 || iRightQty > 0)
	//{
		sList = "tr" + n;
		rItem = &Items[FindItem("Gold")];
		GameInterface.TABLE_LIST.(sList).id = "Gold";
		GameInterface.TABLE_LIST.(sList).td1.str = iLeftQty;
		GameInterface.TABLE_LIST.(sList).td1.scale = 0.8;
		GameInterface.TABLE_LIST.(sList).td2.str = "-";
		GameInterface.TABLE_LIST.(sList).td3.icon.group = rItem.picTexture;
		GameInterface.TABLE_LIST.(sList).td3.icon.image = "itm" + rItem.picIndex;
		GameInterface.TABLE_LIST.(sList).td3.icon.offset = "-2, 0";
		GameInterface.TABLE_LIST.(sList).td3.icon.width = 30;
		GameInterface.TABLE_LIST.(sList).td3.icon.height = 30;
		GameInterface.TABLE_LIST.(sList).td3.textoffset = "30, 0";
		GameInterface.TABLE_LIST.(sList).td3.str = GetConvertStr(rItem.name, "ItemsDescribe.txt");
		GameInterface.TABLE_LIST.(sList).td3.scale = 1.0;
		GameInterface.TABLE_LIST.(sList).td4.str = "-";
		GameInterface.TABLE_LIST.(sList).td5.str = iRightQty;
		GameInterface.TABLE_LIST.(sList).td5.scale = 1.0;
		n++;

		iLinesCount++;
	//}

	object allItems;
	aref arInventory, arItem;
	int inventorySize;

	if (iCurrentTabMode != 3) // Сортировка не "в сундуке"
	{
		makearef(arInventory, refCharacter.Items);
		inventorySize = GetAttributesNum(arInventory);
		for (i = 0; i < inventorySize; i++)
		{
			arItem = GetAttributeN(arInventory, i);
			sItem = GetAttributeName(arItem);
			sList = DigitsToString(FindItem(sItem), 4);

			if (IsGenerableItem(sItem))
			{
				// Сначала заполняем рандомящимся оружием
				sList = "a" + sList + sItem;
			}
			else
			{
				sList = "b" + sList;
			}

			allItems.(sList) = sItem;
		}
	}

	if (iCurrentTabMode != 2) // Сортировка не "у героя"
	{
		makearef(arInventory, rChar.Items);
		inventorySize = GetAttributesNum(arInventory);
		for (i = 0; i < inventorySize; i++)
		{
			arItem = GetAttributeN(arInventory, i);
			sItem = GetAttributeName(arItem);
			sList = DigitsToString(FindItem(sItem), 4);

			if (IsGenerableItem(sItem))
			{
				sList = "a" + sList + sItem;
			}
			else
			{
				sList = "b" + sList;
			}

			allItems.(sList) = sItem;
		}
	}

	makearef(arInventory, allItems);
	sort(arInventory);

	inventorySize = GetAttributesNum(arInventory);
	for (i = 0; i < inventorySize; i++)
	{
		arItem = GetAttributeN(arInventory, i);
		sItem = GetAttributeValue(arItem);
		rItem = ItemsFromID(sItem);

		if (sItem == "Gold") continue; // Золото выше

		iLeftQty  = GetCharacterFreeItem(refCharacter, sItem);
		iRightQty = GetCharacterFreeItem(rChar, sItem);
		if (iRightQty > 0) iRightQtyTotal += 1;

		if ((iLeftQty == 0) && (iRightQty == 0)) continue;
		if (iCurrentTabMode == 2 && iLeftQty < 1) continue; // Сортировка "у героя"
		if (iCurrentTabMode == 3 && iRightQty < 1) continue; // Сортировка "в сундуке"

		if (iCurrentTabMode == 4) // Сортировка "оружие и зелья"
		{
			if (CheckAttribute(rItem, "groupID"))
			{
				// Проверка на оружие
				if (rItem.groupID != BLADE_ITEM_TYPE && rItem.groupID != GUN_ITEM_TYPE && rItem.groupID != TALISMAN_ITEM_TYPE)
				{
					continue;
				}
			}
			else
			{
				// Проверка на зелья
				if(!HasSubStr(sItem, "potion"))
				{
					continue;
				}
			}
		}

		sList = "tr" + n;
		GameInterface.TABLE_LIST.(sList).id = sItem;
		GameInterface.TABLE_LIST.(sList).td1.str = iLeftQty;
		GameInterface.TABLE_LIST.(sList).td2.str = FloatToString(GetItemWeight(sItem) * iLeftQty, 1);
		GameInterface.TABLE_LIST.(sList).td3.icon.group = rItem.picTexture;
		GameInterface.TABLE_LIST.(sList).td3.icon.image = "itm" + rItem.picIndex;
		GameInterface.TABLE_LIST.(sList).td3.icon.offset = "-2, 0";
		GameInterface.TABLE_LIST.(sList).td3.icon.width = 30;
		GameInterface.TABLE_LIST.(sList).td3.icon.height = 30;
		GameInterface.TABLE_LIST.(sList).td3.textoffset = "30, 0";
		GameInterface.TABLE_LIST.(sList).td3.str = GetConvertStr(rItem.name, "ItemsDescribe.txt");
		GameInterface.TABLE_LIST.(sList).td3.scale = 1.0;
		GameInterface.TABLE_LIST.(sList).td4.str = FloatToString(GetItemWeight(sItem) * iRightQty, 1);
		GameInterface.TABLE_LIST.(sList).td5.str = iRightQty;

		iTemp = CheckItemInSets(refCharacter, sItem);
		if (iTemp > 0)
		{
			GameInterface.TABLE_LIST.(sList).td3.str = GameInterface.TABLE_LIST.(sList).td3.str + " (К" + iTemp + ")";
			GameInterface.TABLE_LIST.(sList).td3.color = argb(255,196,196,255);//подцвечиваем предметы из комплектов
			GameInterface.TABLE_LIST.(sList).td1.color = argb(255,196,196,255);//в комплекте у левого персонажа
		}
		iTemp = CheckItemInSets(rChar, sItem);
		if (iTemp > 0)
		{
			GameInterface.TABLE_LIST.(sList).td3.str = GameInterface.TABLE_LIST.(sList).td3.str + " (К" + iTemp + ")";
			GameInterface.TABLE_LIST.(sList).td3.color = argb(255,196,196,255);
			GameInterface.TABLE_LIST.(sList).td5.color = argb(255,196,196,255);//в комплекте у правого персонажа
		}
		n++;

		iLinesCount++;
	}

	if(ok1)
	{
		GameInterface.TABLE_LIST.select = sti(GameInterface.TABLE_LIST.select) - 1;
		sList = "tr" + sti(GameInterface.TABLE_LIST.select);

		// Warship 10.07.09 fix - Могло не быть, при сбрасывании в начало при переключении персонажей
		if(CheckAttribute(GameInterface, "TABLE_LIST." + sList + ".id"))
		{
			sCurItem = GameInterface.TABLE_LIST.(sList).id;
			ShowGoodsInfo(sCurItem);
		}
	}

	Table_UpdateWindow("TABLE_LIST");
	SetEventHandler("frame", "RefreshTableByFrameEvent", 0);
	string sInterfaceType = sGetInterfaceType();
	if (sInterfaceType == INTERFACETYPE_DEADMAN)
	{
		if (iRightQtyTotal == 0)
		{
			DelLogin = true;
			//Log_Info("Количество предметов у трупа: "+iRightQtyTotal);
		}
	}
}

void RefreshTableByFrameEvent()
{
	DelEventHandler("frame", "RefreshTableByFrameEvent");
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"TABLE_LIST", 0 );
}

void OnTableClick()
{
	string sControl = GetEventData();
	int iRow = GetEventData();
	int iColumn = GetEventData();

	string sRow = "tr" + (iRow + 1);
//--> mod tablesort
	if (!SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, sControl, 1 ))
		{
		if (lastsort == iColumn) {bLastSort = !bLastSort;} else {lastsort = iColumn; bLastSort = 1;}//запоминаем сортировку и меняем направление сортировки, если это повторный клик по колонке
//todo - разобраться, как заблокировать активацию двойного клика на заголовке - подменять его на ординарные как-то
//todo - устанавливать стрелочку направления сортировки по запомненным значениям переменных - но тут нужно как-то узнавать ширину колонок таблицы, чтобы пересчитать координаты???
//todo - не забыть, что может быть несколько таблиц на одном интерфейсе - надо ещё и последнюю таблицы запоминать и сбрасывать(?) сортировку при смене или запоминать для каждой?
		if (iColumn == 3)
			SortTable(sControl, iColumn, 1, bLastSort, iLinesCount);//3 колонка - текстовая
		else
			SortTable(sControl, iColumn, 0, !bLastSort, iLinesCount);//остальные колонки - числа
		}
//вызывать направление сортировки разными действиями - ЛКМ/ПКМ??
//<-- mod tablesort
	Table_UpdateWindow(sControl);
}

void ChangePosTable()
{

}

void ShowHelpHint()
{
	string sHeader;
	string sText1, sText2, sText3, sPicture, sGroup, sGroupPicture;
	sPicture = "none";
	sGroup = "none";
	sGroupPicture = "none";

	if(!bShowChangeWin) // покажем помощь по работе с формой
	{
		sHeader = XI_ConvertString("titleItemsTrade");
		sText1 = "Двойной клик мыши или Enter по строкам таблицы вызывает форму обмена предметами "+ newStr() +
			"Shift + лево/право на строках таблицы автоматически вызывают форму с предустановленным количеством покупки/продажи на максимальное. "+ newStr() +
			"Ввод положительного количества с клавиатуры устанавливает забирание предмета, а отрицательного (с минусом) отдачу."+ newStr() +
			"Стрелки лево/право изменяют количество по одному, а Shift + лево/право на максимально доступное. Нажатие Enter на форме равносильно ОК, а Esc - Отмена." + newStr() +
			"Находясь в режиме формы и мотая список в таблице стрелкам вверх/вниз, можно просматривать описание предмета под курсором таблицы.";

		sText3 = "В списке на обмен отсутствуют экипированные персонажем предметы.";
		sText2 = "Быстрая отдача всего: стрелками вверх/вниз по списку, Shift + право, Enter";

		CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,192,192,192), sText3, argb(255,255,255,255), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);
	}
}

void EndTooltip()
{
	CloseTooltip(); // всегда убирать, если был
	GameInterface.qty_edit.str = 0;
	SetCharWeight();
	SetVariable();
	SetCurrentNode("TABLE_LIST");
 	XI_WindowDisable("QTY_WINDOW", true);
	XI_WindowShow("QTY_WINDOW", false);
	bShowChangeWin = false;
}

void ShowItemInfo()
{
	if(bShowChangeWin) // жмем окей, когда курсор на таблице
	{
		TransactionOK();
	}
	else
	{
		GameInterface.qty_edit.str = "0";
		BuyOrSell = 0;
		ChangeQTY_EDIT();

		XI_WindowDisable("QTY_WINDOW", false);
		XI_WindowShow("QTY_WINDOW", true);
		bShowChangeWin = true;
	}
}

void CS_TableSelectChange()
{
	String sControl = GetEventData();
	int iSelected = GetEventData();
	int iCol = GetEventData();

	// Warship 26.04.09 fix - при прокрутке можго вылазить за экран, неправильно определялась текущая линия
	int iSelLine = iSelected;

	if(CheckAttribute(&GameInterface, "TABLE_LIST.top"))
	{
		iSelLine = iSelected - sti(GameInterface.TABLE_LIST.top);
	}

	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_ALL_BUTTON", 0, iTableAddAllBtnX, iTableAddAllBtnY + 30 * (iSelLine - 1), iTableAddAllBtnX + 30, iTableAddAllBtnY + 30 * (iSelLine - 1) + 30, 0);
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_ALL_BUTTON", 0, iTableRemoveAllBtnX, iTableRemoveAllBtnY + 30 * (iSelLine - 1), iTableRemoveAllBtnX + 30, iTableRemoveAllBtnY + 30 * (iSelLine - 1) + 30, 0);

	String sList = "tr" + iSelected;
	SetCharWeight();
	SetVariable();
	ShowGoodsInfo(GameInterface.TABLE_LIST.(sList).id);
}

void SetVariable()
{
	string sText, sTextSecond;

	iCharCapacity = GetMaxItemsWeight(refCharacter);
	sText  = FloatToString(fCharWeight, 1) + " / " + iCharCapacity;
	ShowItemsWeight(); // Переделка
}

void SetCharacterName()
{
	string sInterfaceType = sGetInterfaceType();

	aref arChar;
	ref rChar;

	string sAttr = "pic" + (nCurScrollNum + 1);
	int iCurCharImageIndex = sti(GameInterface.CHARACTERS_SCROLL.(sAttr).character);

	string sFullName = GetFullName(&characters[iCurCharImageIndex]);
	if (!HasSubStr(GameInterface.CHARACTERS_SCROLL.(sAttr).character,"box")) sFullName = GetFullName(&characters[iCurCharImageIndex]);
	else
	{
		switch (GameInterface.CHARACTERS_SCROLL.(sAttr).character)
		{
			case "box1": sFullName = "1-ый Сундук каюты" break;
			case "box2": sFullName = "2-ой Сундук каюты" break;
			case "box3": sFullName = "3-ий Сундук каюты" break;
			case "box4": sFullName = "4-ый Сундук каюты" break;
		}
	}

	GameInterface.strings.CharName = sFullName;
}

void ProcessFrame()
{
	aref arCurCharFromImage;
	string sInterfaceType = sGetInterfaceType();
	if(sti(GameInterface.CHARACTERS_SCROLL.current) != nCurScrollNum && GetCurrentNode() == "CHARACTERS_SCROLL")
	{
		XI_WindowDisable("QTY_WINDOW", true);
		XI_WindowShow("QTY_WINDOW", false);
		nCurScrollNum = sti(GameInterface.CHARACTERS_SCROLL.current);
		string sAttr = "pic" + (nCurScrollNum + 1);
		int iCurCharImageIndex = sti(GameInterface.CHARACTERS_SCROLL.(sAttr).character);

		switch(sInterfaceType)
		{
			case INTERFACETYPE_EXCHANGE_ITEMS:
				makearef(refToChar, characters[iCurCharImageIndex]);
			break;

			case INTERFACETYPE_CHEST:
				makeref(refCharacter, characters[iCurCharImageIndex]);
			break;

			case INTERFACETYPE_BARREL:
				makeref(refCharacter, characters[iCurCharImageIndex]);
			break;

			case INTERFACETYPE_DEADMAN:
				makeref(refCharacter, characters[iCurCharImageIndex]);
			break;
		}

		SetDescription();
		if (HasSubStr(GameInterface.CHARACTERS_SCROLL.(sAttr).character,"box"))
		{
			switch (GameInterface.CHARACTERS_SCROLL.(sAttr).character)
			{
				case "box1": makeref(refCharacter,box1) break;
				case "box2": makeref(refCharacter,box2) break;
				case "box3": makeref(refCharacter,box3) break;
				case "box4": makeref(refCharacter,box4) break;
			}
		}
		
		AddToTable(refToChar);
		FillCharactersImages();
		SetVariable();
		GameInterface.TABLE_LIST.select = 1;
		GameInterface.TABLE_LIST.top = 0;
		SetCharacterName();

		// Стрлочки на первую позицию
		SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_ALL_BUTTON", 0, iTableAddAllBtnX, iTableAddAllBtnY, iTableAddAllBtnX + 30, iTableAddAllBtnY + 30, 0);
		SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_ALL_BUTTON", 0, iTableRemoveAllBtnX, iTableRemoveAllBtnY, iTableRemoveAllBtnX + 30, iTableRemoveAllBtnY + 30, 0);
	}
}

void FillCharactersImages()
{
	string sInterfaceType = sGetInterfaceType();
	if (CheckAttribute(refCharacter,"faceid")) SetNewPicture("MAIN_CHARACTER_PICTURE", "interfaces\portraits\128\face_" + refCharacter.FaceId + ".tga");
	else SetNewPicture("MAIN_CHARACTER_PICTURE", "interfaces\BoxImage.tga");

	switch(sInterfaceType)
	{
		case INTERFACETYPE_EXCHANGE_ITEMS:
			SetNewPicture("OTHER_PICTURE", "interfaces\portraits\128\face_" + refToChar.FaceId + ".tga");
		break;

		case INTERFACETYPE_CHEST:
			SetNewGroupPicture("OTHER_PICTURE", "BOX_IMAGE", "BoxImage");
		break;

		case INTERFACETYPE_BARREL:
			SetNewGroupPicture("OTHER_PICTURE", "BARREL_IMAGE", "BarrelImage");
		break;

		case INTERFACETYPE_DEADMAN:
			SetNewPicture("OTHER_PICTURE", "interfaces\portraits\128\face_666.tga");
		break;
	}
}

void SetDescription()
{
	SetVariable();
}

void SetCharWeight()
{
    fCharWeight  = GetItemsWeight(refCharacter);
    fStoreWeight = GetItemsWeight(refToChar);
}

// Жмакнули по кнопке "взять все"
void onGetAllBtnClick()
{
	int i, iItemsQty, maxItemsToAdd;
	String itemID;
	aref arInventory, arItem;
	object itemsToTake;
	float weight;
	bool bOk = false;

	makearef(arInventory, refToChar.Items);
	for (i = 0; i < GetAttributesNum(arInventory); i++)
	{
		arItem = GetAttributeN(arInventory, i);
		itemID = GetAttributeName(arItem);

		iItemsQty = GetCharacterFreeItem(refToChar, itemID);
		if(iItemsQty < 1) continue;

		// Учет перегруза -->
		//maxItemsToAdd = GetMaxItemsToTake(refCharacter, itemID)
		float itemWeight = GetItemWeight(itemID);
		if(itemWeight == 0)
		{
			itemsToTake.(itemID) = iItemsQty;
			AddItems(refCharacter, itemID, iItemsQty);
			continue;
		}
		else
		{
			int maxWeight = GetMaxItemsWeight(refCharacter);
			maxItemsToAdd = makeint((maxWeight-GetItemsWeight(refCharacter))/itemWeight);

			if(maxItemsToAdd < iItemsQty) iItemsQty = maxItemsToAdd;
			// <-- Учет перегруза

			if(iItemsQty < 1) continue;

			itemsToTake.(itemID) = iItemsQty;
			AddItems(refCharacter, itemID, iItemsQty);

			bOk = true;

			weight = iItemsQty * GetItemWeight(itemID);
			fCharWeight += weight; // Тут обновляем для метода GetMaxItemsToTake, иначе тормоза
			fStoreWeight -= weight;
		}
	}

	makearef(arInventory, itemsToTake);
	for (i = 0; i < GetAttributesNum(arInventory); i++)
	{
		arItem = GetAttributeN(arInventory, i);
		itemID = GetAttributeName(arItem);
		iItemsQty = sti(GetAttributeValue(arItem));

		RemoveItems(refToChar, itemID, iItemsQty);
	}

	if(bOk) WaitDate("", 0, 0, 0, 0, 1);

	// Warship fix 10.06.09 -->
	// Обновление текущего веса и т.д.
	SetCharWeight();
	SetVariable();

	GameInterface.TABLE_LIST.top = 0;
	GameInterface.TABLE_LIST.select = 1;

	sCurItem = GameInterface.TABLE_LIST.tr1.id;
	ShowGoodsInfo(sCurItem);

	AddToTable(refToChar); // Рефрешь таблицы
	// Рефреш позиции стрелочек
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_ALL_BUTTON", 0, iTableAddAllBtnX, iTableAddAllBtnY, iTableAddAllBtnX + 30, iTableAddAllBtnY + 30, 0);
	SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_ALL_BUTTON", 0, iTableRemoveAllBtnX, iTableRemoveAllBtnY, iTableRemoveAllBtnX + 30, iTableRemoveAllBtnY + 30, 0);
	// <-- Warship fix 10.06.09
}

// Нажали на табличной стрелочке "взять все предметы одного типа"
void onTableAddAllBtnClick()
{
	int iItemsQty = GetCharacterFreeItem(refToChar, sCurItem);

	// Учет перегруза
	int maxItemsToAdd = GetMaxItemsToTake(refCharacter, sCurItem);

	if(maxItemsToAdd < iItemsQty) iItemsQty = maxItemsToAdd;

	if(iItemsQty > 0) // fix
	{
		RemoveItems(refToChar, sCurItem, iItemsQty);
		AddItems(refCharacter, sCurItem, iItemsQty);
		WaitDate("", 0, 0, 0, 0, 1);

		AddToTable(refToChar);

		// Обновление текущего веса и т.д.
		SetCharWeight();
		SetVariable();

		iCharQty = GetCharacterFreeItem(refCharacter, sCurItem);
		iStoreQty = GetCharacterFreeItem(refToChar, sCurItem);
	}
}

// Нажали на табличной стрелочке "отдать все предметы одного типа"
void onTableRemoveAllBtnClick()
{
	int iItemsQty = GetCharacterFreeItem(refCharacter, sCurItem);

	if(IsQuestUsedItem(sCurItem) && sCurItem != "Gold") return; // Квестовые не отдать, только золото

	// Учет перегруза (в сундуки и трупы можно ложить сколько угодно)
	int maxItemsToAdd = GetMaxItemsToTake(refToChar, sCurItem);

	if(maxItemsToAdd < iItemsQty) iItemsQty = maxItemsToAdd;

	if(iItemsQty > 0) // fix
	{
		RemoveItems(refCharacter, sCurItem, iItemsQty);
		AddItems(refToChar, sCurItem, iItemsQty);
		WaitDate("", 0, 0, 0, 0, 1);

		AddToTable(refToChar);

		// Обновление текущего веса и т.д.
		SetCharWeight();
		SetVariable();

		iCharQty = GetCharacterFreeItem(refCharacter, sCurItem);
		iStoreQty = GetCharacterFreeItem(refToChar, sCurItem);
	}
}

// инфа о предмете
void ShowGoodsInfo(int sItem)
{
	int itemIndex = FindItem(sItem);
	string GoodName = Items[itemIndex].name;
	int    lngFileID = LanguageOpenFile("ItemsDescribe.txt");
	string sHeader = LanguageConvertString(lngFileID, GoodName);

	sCurItem = sItem;
	string describeStr = "";

	if(bBettaTestMode)
	{
		describeStr += "id = " + sItem + NewStr();
	}
	describeStr += GetItemDescribe(sItem);

	fWeight = GetItemWeight(sItem);

	BuyOrSell = 0;
	SetFormatedText("QTY_TypeOperation", "");
	SetFormatedText("QTY_Result", "");
	GameInterface.qty_edit.str = "0";

	SetNewGroupPicture("QTY_GOODS_PICTURE", Items[itemIndex].picTexture, "itm" + Items[itemIndex].picIndex);
	SetFormatedText("QTY_CAPTION", sHeader);
	SetFormatedText("QTY_GOODS_INFO", describeStr);
	LanguageCloseFile(lngFileID);

	iCharQty = GetCharacterFreeItem(refCharacter, sItem);
	iStoreQty = GetCharacterFreeItem(refToChar, sItem);

	SetFormatedText("QTY_INFO_STORE_QTY", its(iStoreQty));
	SetFormatedText("QTY_INFO_SHIP_QTY", its(iCharQty));
	BuyOrSell = 0;
}

void TransactionOK()
{
	int nTradeQuantity;
	String list;
	confirmChangeQTY_EDIT();
	nTradeQuantity = sti(GameInterface.qty_edit.str);
	if(BuyOrSell == 0)
	{
	    EndTooltip();
	    return;
	}

 	if(BuyOrSell == 1) // Забираем
	{
		RemoveItems(refToChar, sCurItem, nTradeQuantity);
		AddItems(refCharacter, sCurItem, nTradeQuantity);
    	WaitDate("",0,0,0, 0, 1);
	}
 	else // Отдаем
	{
		AddItems(refToChar, sCurItem, nTradeQuantity);
		RemoveItems(refCharacter, sCurItem, nTradeQuantity);
		WaitDate("",0,0,0, 0, 1);
	}

	AddToTable(refToChar);
	EndTooltip();

	ShowGoodsInfo(sCurItem); //сбросим все состояния
}

void confirmChangeQTY_EDIT()
{
	ChangeQTY_EDIT();
	SetCurrentNode("QTY_OK_BUTTON");
}

void ChangeQTY_EDIT()
{
	float iWeight;
	float fRefCharWeight, fRefCharMaxWeight;
	string sInterfaceType = sGetInterfaceType();
	SetCharWeight();
	GameInterface.qty_edit.str = sti(GameInterface.qty_edit.str);
	if(sti(GameInterface.qty_edit.str) == 0)
	{
	    SetFormatedText("QTY_TypeOperation", "");
	    SetFormatedText("QTY_Result", "");
	    BuyOrSell = 0;
	}
	else
	{
		if (sti(GameInterface.qty_edit.str) < 0 || BuyOrSell == -1)
		{
			if (BuyOrSell != -1)
			{
		    	GameInterface.qty_edit.str = -sti(GameInterface.qty_edit.str);
		    }

		    BuyOrSell = -1;

		    // проверка на колво доступное -->
		    if (sti(GameInterface.qty_edit.str) > iCharQty)
		    {
		        GameInterface.qty_edit.str = iCharQty;
		    }

		    if(sInterfaceType == INTERFACETYPE_EXCHANGE_ITEMS) // Сундуки и трупы бездонны
		    {
				fRefCharWeight = GetItemsWeight(refToChar);
				fRefCharMaxWeight = GetMaxItemsWeight(refToChar);
				iWeight = (fWeight * sti(GameInterface.qty_edit.str));
				if((fRefCharWeight + iWeight) > fRefCharMaxWeight)
				{
					iWeight = fRefCharMaxWeight - fRefCharWeight - 0.01; // чуть меньше
					GameInterface.qty_edit.str = makeint(iWeight / fWeight );
					iWeight = fWeight * sti(GameInterface.qty_edit.str);
					GameInterface.qty_edit.str = makeint(iWeight / fWeight ); // округдение
				}
		    }
		    // проверка на колво доступное <--
		    // квестовые не продать -->
		    if (IsQuestUsedItem(sCurItem) && sCurItem != "Gold")
		    {
		        GameInterface.qty_edit.str = 0;
		    }
			if (sti(GameInterface.qty_edit.str) < 0) GameInterface.qty_edit.str = 0;
		    // квестовые не продать <--
		    SetFormatedText("QTY_TypeOperation", "Отдать");
		}
		else
		{
			BuyOrSell = 1;

	        // проверка на колво доступное -->
		    if (sti(GameInterface.qty_edit.str) > iStoreQty)
		    {
		        GameInterface.qty_edit.str = iStoreQty;
		    }
		    iWeight = (fWeight * sti(GameInterface.qty_edit.str));
		    if((fCharWeight + iWeight) > iCharCapacity && sCurItem != "Gold")
		    {
		        iWeight = iCharCapacity - fCharWeight - 0.01; // чуть меньше

				if(iWeight < 0) iWeight = 0;

		        GameInterface.qty_edit.str = makeint(iWeight / fWeight );
		        iWeight = fWeight * sti(GameInterface.qty_edit.str);
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight ); // округдение
		    }
		    // проверка на колво доступное <--

			SetFormatedText("QTY_TypeOperation", "Забрать");
		}
	}
	// если получили ноль
	if (sti(GameInterface.qty_edit.str) == 0)
	{
	    SetFormatedText("QTY_TypeOperation", "");
	    BuyOrSell = 0;
	}
    SetFormatedText("QTY_INFO_STORE_QTY", its(iStoreQty - BuyOrSell*sti(GameInterface.qty_edit.str)));
    SetFormatedText("QTY_INFO_SHIP_QTY", its(iCharQty + BuyOrSell*sti(GameInterface.qty_edit.str)));
    SetCharWeight();
    fCharWeight  = fCharWeight  + BuyOrSell * iWeight;
	fStoreWeight = fStoreWeight - BuyOrSell * iWeight;
    SetVariable();
}

void REMOVE_ALL_BUTTON()  // продать все
{
	if(!bShowChangeWin)
	{
	    ShowItemInfo();
	}

	ShowGoodsInfo(sCurItem);
	GameInterface.qty_edit.str = -iCharQty;
	BuyOrSell = 0;
	ChangeQTY_EDIT();
}

void ADD_ALL_BUTTON()  // купить все
{
	if(!bShowChangeWin)
	{
	    ShowItemInfo();
	}

	ShowGoodsInfo(sCurItem);
	GameInterface.qty_edit.str = iStoreQty;
	BuyOrSell = 0;
	ChangeQTY_EDIT();
}

void REMOVE_BUTTON()  // продать
{
	if(!bShowChangeWin) return;

	if(BuyOrSell == 0)
	{
		GameInterface.qty_edit.str = -1;
	}
	else
	{
		if(BuyOrSell == -1)
		{
			GameInterface.qty_edit.str = -(sti(GameInterface.qty_edit.str) + 1);
		}
		else
		{
			GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) - 1);
		}

		BuyOrSell = 0;
	}

	ChangeQTY_EDIT();
}

void ADD_BUTTON()  // купить
{
	if(!bShowChangeWin) return;

	if(BuyOrSell == 0)
	{
		GameInterface.qty_edit.str = 1;
	}
	else
	{
		if(BuyOrSell == 1)
		{
			GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) + 1);
		}
		else
		{
			GameInterface.qty_edit.str = -(sti(GameInterface.qty_edit.str) - 1);
		}

		BuyOrSell = 0;
	}

	ChangeQTY_EDIT();
}

// Сколько еще могет утащить указанного предмета, в штуках
int GetMaxItemsToTake(ref _char, String _item)
{
	float curWeight;

	// Warship MEGA FIX 10.07.09
	if(_char == refToChar)
	{
		curWeight = fStoreWeight;
	}
	else
	{
		curWeight = fCharWeight;
	}

	int maxWeight = GetMaxItemsWeight(_char);

	float itemWeight = GetItemWeight(_item);

	if(itemWeight == 0) // Это золото и прочая байда - лезла ошибка деления на нуль
	{
		return 1000000000;
	}

	return MakeInt((maxWeight - curWeight) / itemWeight);
}

void OfficerReincarnation(ref rPassanger);
{
	ref rOff = GetCharacter(NPC_GenerateCharacter("Clon", "none", rPassanger.sex, rPassanger.model.animation, 1, sti(rPassanger.nation), -1, false));
	ChangeAttributesFromCharacter(rOff, rPassanger, true);
	rOff.id = rPassanger.id;
	LAi_SetCurHPMax(rOff);
	RemoveCharacterEquip(rOff, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(rOff, GUN_ITEM_TYPE);
	RemoveCharacterEquip(rOff, SPYGLASS_ITEM_TYPE);
	RemoveCharacterEquip(rOff, PATENT_ITEM_TYPE);
	RemoveCharacterEquip(rOff, CIRASS_ITEM_TYPE);
	RemoveCharacterEquip(rOff, MAPS_ITEM_TYPE);
	DeleteAttribute(rOff, "items");
	rOff.items = "";
	DeleteAttribute(rOff, "isMusketer.weapon");
	DeleteAttribute(pchar, "items.mushket2x2");
	AddPassenger(pchar, rOff, false);
	Log_Info("Абордажник " + GetFullName(rOff) + " реанимирован.");
}
