// boal 26/04/06 морма торговли предметами
int	nCurScrollNum = 0;
int iCharCapacity;
int iTotalSpace;
float fCharWeight, fStoreWeight;
int iMaxGoodsStore = 50000;
bool nocheck = true;

bool bShowChangeWin = false;
int  BuyOrSell = 0; // 1-buy -1 sell
string sChrId;
//ref refStore,
ref refCharacter, refStoreChar; // текущий ГГ (оф) и торгаш
int iCharQty, iStoreQty, iCharPrice, iStorePrice;
float fWeight;
string sCurItem;

//// {*} BUHO-FIST - ADDED CODE - Fist state variable
#define FIT_ALL			0		// Normal
#define FIT_BACKPACK	1		// Show backpack
#define FIT_TRADER		2		// Show trader
int FIT_FilterState;
//// {*} BUHO END ADDITION
//----------------------------------------------------------------------------------------------------------------
void InitInterface_R(string iniName, ref pTrader)
{
	StartAboveForm(true);

	refCharacter = pchar;
	refStoreChar = pTrader;
	//GameInterface.TABLE_LIST.hr.height = 36;
	GameInterface.TABLE_LIST.hr.td1.str = "Кол-во";
	GameInterface.TABLE_LIST.hr.td1.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td2.str = "Вес";
	GameInterface.TABLE_LIST.hr.td2.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td3.str = XI_ConvertString("Price sell");
	GameInterface.TABLE_LIST.hr.td3.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td4.str = "Наименование предметов";
	GameInterface.TABLE_LIST.hr.td4.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td5.str = XI_ConvertString("Price buy");
	GameInterface.TABLE_LIST.hr.td5.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td6.str = "Предметов торговца";//XI_ConvertString("In the store");
	GameInterface.TABLE_LIST.hr.td6.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td7.str = "Вес";
	GameInterface.TABLE_LIST.hr.td7.scale = 0.9;

	FillCharactersScroll();

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	if (checkattribute(pchar, "ItemTradeFilter")) FIT_FilterState = sti(pchar.ItemTradeFilter); else FIT_FilterState = 0;
	switch (FIT_FilterState)
	{
	case FIT_ALL: SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_ALL", 2, 1, 1); break;
	case FIT_BACKPACK: SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_BACKPACK", 2, 1, 1); break;
	case FIT_TRADER: SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_TRADER", 2, 1, 1); break;
	}

	CreateString(true,"CharName","",FONT_NORMAL,COLOR_MONEY, 405,108,SCRIPT_ALIGN_CENTER,1.0);
	SetCharWeight();
	SetDescription();
	FillCharacterInfo();

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
	SetEventHandler("ShowEquipWindow", "ShowEquipWindow", 0);
	SetEventHandler("ExitEquipWindow", "ExitEquipWindow", 0);
	SetEventHandler("ShowBladeEquipInfo", "ShowBladeEquipInfo", 0);
	SetEventHandler("ShowGunEquipInfo", "ShowGunEquipInfo", 0);
	SetEventHandler("ShowSpyglassEquipInfo", "ShowSpyglassEquipInfo", 0);
	SetEventHandler("ShowCirassEquipInfo", "ShowCirassEquipInfo", 0);
	SetEventHandler("ShowBackPackEquipInfo", "ShowBackPackEquipInfo", 0);
	SetEventHandler("ShowTalismanEquipInfo", "ShowTalismanEquipInfo", 0);
	SetEventHandler("ShowBookEquipInfo", "ShowBookEquipInfo", 0);
	SetEventHandler("Show1EquipInfo", "Show1EquipInfo", 0);
	SetEventHandler("Show2EquipInfo", "Show2EquipInfo", 0);
	SetEventHandler("Show3EquipInfo", "Show3EquipInfo", 0);
	SetEventHandler("Show4EquipInfo", "Show4EquipInfo", 0);
	SetEventHandler("Show5EquipInfo", "Show5EquipInfo", 0);
	SetEventHandler("Autotrade_All", "Autotrade_All", 0);
	SetEventHandler("Autotrade_This", "Autotrade_This", 0);

	SetFormatedText("STORECAPTION1", XI_ConvertString("titleItemsTrade"));

	switch (refCharacter.sex)
	{
		case "man": SetNewPicture("EQUIP_BIG_PICTURE", "interfaces\sith\CharEquip_Man.tga");
		break;
		case "woman": SetNewPicture("EQUIP_BIG_PICTURE", "interfaces\sith\CharEquip_Woman.tga");
		break;
		case "skeleton": SetNewPicture("EQUIP_BIG_PICTURE", "interfaces\sith\CharEquip_Skeleton.tga");
		break;
	}

	SetNewPicture("OTHER_PICTURE", "interfaces\portraits\256\face_" + its(refStoreChar.FaceId) + ".tga");

	if (!IsPCharHaveTreasurer()) {SetNodeUsing("Autotrade_All",  false); SetNodeUsing("Autotrade_This",  false);}//скрываем автозакупку без казначея
}

void ProcessBreakExit()
{
	IDoExit( RC_INTERFACE_FOOD_INFO_EXIT );
}

void ProcessCancelExit()
{
	if (bShowChangeWin)
	{
		EndTooltip();
	}
	else
	{
		IDoExit( RC_INTERFACE_FOOD_INFO_EXIT );
	}
}

void IDoExit(int exitCode)
{
	pchar.ItemTradeFilter = FIT_FilterState;
	// boal проверка на перегруз 21.01.2004 -->
	CheckAndSetOverloadMode(GetMainCharacter());
	RefreshEquippedMaps(GetMainCharacter()); // рефрешим карты, если купили
	// boal 21.01.2004 <--
	// раздайте патроны, порутчик Голицын -->
	int i, cn;
	for(i=1;i<=MAX_NUM_FIGHTERS;i++)
	{
		cn = GetOfficersIndex(pchar, i);
		if (cn!=-1)
		{
			refCharacter = GetCharacter(cn);
			CheckAndSetOverloadMode(refCharacter);
			if (CheckAttribute(refCharacter, "skill.Fencing")) //boal fix иначе не берут саблю при перегрузе
			{
				EquipCharacterByItem(refCharacter, FindCharacterItemByGroup(refCharacter,BLADE_ITEM_TYPE));
				//EquipCharacterByItem(refCharacter, FindCharacterItemByGroup(refCharacter,CIRASS_ITEM_TYPE)); // boal 08.10.04 броню офицерам
				EquipCharacterByItem(refCharacter, FindCharacterItemByGroup(refCharacter,BACKPACK_ITEM_TYPE));
				EquipCharacterByItem(refCharacter, FindCharacterItemByGroup(refCharacter,TALISMAN_ITEM_TYPE));
			}
			if (CheckAttribute(refCharacter, "skill.Pistol") && GetCharacterSkill(refCharacter,"Pistol") > 0.1 )
			{
				EquipCharacterByItem(refCharacter, FindCharacterItemByGroup(refCharacter,GUN_ITEM_TYPE));
			}
		}
	}
	// раздайте патроны, порутчик Голицын <--
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

	DelEventHandler("ShowEquipWindow", "ShowEquipWindow");
	DelEventHandler("ExitEquipWindow", "ExitEquipWindow");
	DelEventHandler("ShowBladeEquipInfo", "ShowBladeEquipInfo");
	DelEventHandler("ShowGunEquipInfo", "ShowGunEquipInfo");
	DelEventHandler("ShowSpyglassEquipInfo", "ShowSpyglassEquipInfo");
	DelEventHandler("ShowCirassEquipInfo", "ShowCirassEquipInfo");
	DelEventHandler("ShowBackPackEquipInfo", "ShowBackPackEquipInfo");
	DelEventHandler("ShowTalismanEquipInfo", "ShowTalismanEquipInfo");
	DelEventHandler("ShowBookEquipInfo", "ShowBookEquipInfo");
	DelEventHandler("Show1EquipInfo", "Show1EquipInfo");
	DelEventHandler("Show2EquipInfo", "Show2EquipInfo");
	DelEventHandler("Show3EquipInfo", "Show3EquipInfo");
	DelEventHandler("Show4EquipInfo", "Show4EquipInfo");
	DelEventHandler("Show5EquipInfo", "Show5EquipInfo");
	DelEventHandler("Autotrade_All", "Autotrade_All");
	DelEventHandler("Autotrade_This", "Autotrade_This");

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);

}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
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
		//// {*} BUHO-FIST - ADDED CODE - Response to checkboxes.
		case "CB_BACKPACK":		if (comName == "click")ProcessFilter(nodName); break;
		case "CB_ALL":			if (comName == "click")ProcessFilter(nodName); break;
		case "CB_TRADER":		if (comName == "click")ProcessFilter(nodName); break;
		//// {*} BUHO END ADDITION
	}
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void CalculateInfoData()
{
	AddToTable();
	ShowGoodsInfo(GameInterface.TABLE_LIST.tr1.id);
}

void AddToTable()
{
	int n, i, iTemp;
	string row, sItem;
	int idLngFile;
	int leftQty, rightQty;
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	Table_Clear("TABLE_LIST", false, true, false);

	object allItems;
	aref arInventory, arItem;
	ref rItem;

	if (FIT_FilterState != FIT_TRADER)
	{
		makearef(arInventory, refCharacter.Items);
		n = GetAttributesNum(arInventory);
		for (i = 0; i < n; i++)
		{
			arItem = GetAttributeN(arInventory, i);
			sItem = GetAttributeName(arItem);
			row = DigitsToString(FindItem(sItem), 4);

			if (IsGenerableItem(sItem))
			{
				// Сначала уникальные предметы
				row = "a" + row + sItem;
			}
			else
			{
				row = "b" + row;
			}

			allItems.(row) = sItem;
		}
	}

	if (FIT_FilterState != FIT_BACKPACK)
	{
		makearef(arInventory, refStoreChar.Items);
		n = GetAttributesNum(arInventory);
		for (i = 0; i < n; i++)
		{
			arItem = GetAttributeN(arInventory, i);
			sItem = GetAttributeName(arItem);
			row = DigitsToString(FindItem(sItem), 4);

			if (IsGenerableItem(sItem))
			{
				row = "a" + row + sItem;
			}
			else
			{
				row = "b" + row;
			}

			allItems.(row) = sItem;
		}
	}

	makearef(arInventory, allItems);
	sort(arInventory);

	n = 1;
	for (i = 0; i < GetAttributesNum(arInventory); i++)
	{
		arItem = GetAttributeN(arInventory, i);
		sItem = GetAttributeValue(arItem);
		rItem = ItemsFromID(sItem);

		if (IsQuestUsedItem(sItem)) continue;

		row = "tr" + n;
		// проверка на экипировку, их не продаем
		leftQty  = GetCharacterFreeItem(refCharacter, sItem);
		rightQty = GetCharacterFreeItem(refStoreChar, sItem);

		if ((leftQty == 0) && (rightQty == 0)) continue;
		//// {*} BUHO-FIST - ADDED CODE - Filters at work.
		if (leftQty == 0 && FIT_FilterState == FIT_BACKPACK) continue;
		if (rightQty == 0 && FIT_FilterState == FIT_TRADER) continue;
		//// {*} BUHO END ADDITION

		GameInterface.TABLE_LIST.(row).id = sItem;
		GameInterface.TABLE_LIST.(row).td1.str = leftQty;
		GameInterface.TABLE_LIST.(row).td2.str = FloatToString(GetItemWeight(sItem) * leftQty, 1);
		GameInterface.TABLE_LIST.(row).td7.str = FloatToString(GetItemWeight(sItem), 1);

		GameInterface.TABLE_LIST.(row).td6.str = rightQty;

		GameInterface.TABLE_LIST.(row).td4.icon.group = rItem.picTexture;
		GameInterface.TABLE_LIST.(row).td4.icon.image = "itm" + rItem.picIndex;
		GameInterface.TABLE_LIST.(row).td4.icon.offset = "-2, 0";
		GameInterface.TABLE_LIST.(row).td4.icon.width = 20;
		GameInterface.TABLE_LIST.(row).td4.icon.height = 20;
		GameInterface.TABLE_LIST.(row).td4.textoffset = "20,0";
		GameInterface.TABLE_LIST.(row).td4.str = LanguageConvertString(idLngFile, rItem.name);

		iTemp = CheckItemInSets(refCharacter, sItem);
		if (iTemp > 0)
		{
			GameInterface.TABLE_LIST.(row).td4.str = GameInterface.TABLE_LIST.(row).td4.str + " (К" + iTemp + ")";
			GameInterface.TABLE_LIST.(row).td4.color = argb(255,196,196,255);//подцвечиваем предметы из комплектов
			GameInterface.TABLE_LIST.(row).td1.color = argb(255,196,196,255);
		}

		GameInterface.TABLE_LIST.(row).td4.scale = 0.9;
		GameInterface.TABLE_LIST.(row).td3.str = GetTradeItemPrice(sItem, PRICE_TYPE_BUY);
		GameInterface.TABLE_LIST.(row).td5.str = GetTradeItemPrice(sItem, PRICE_TYPE_SELL);
		n++;
	}
	NextFrameRefreshTable();
	LanguageCloseFile(idLngFile);
	nocheck = false;
}

void NextFrameRefreshTable()
{
	SetEventHandler("frame", "RefreshTableByFrameEvent", 0);
}

void RefreshTableByFrameEvent()
{
	DelEventHandler("frame", "RefreshTableByFrameEvent");
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"TABLE_LIST", 0 );
	if(!nocheck) DoChange1();
}

void DoChange1()
{
	//AddToTable();
	string row = "tr"+sti(GameInterface.TABLE_LIST.select);
	if (row != "tr0") ShowGoodsInfo(GameInterface.TABLE_LIST.(row).id);
	nocheck = true;
}

void OnTableClick()
{
	string sControl = GetEventData();
	int iRow = GetEventData();
	int iColumn = GetEventData();

	string sRow = "tr" + (iRow + 1);
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
	bool bCheckboxes = False;

	if (bShowChangeWin) return;

	string sNode = GetCurrentNode();

	switch (sNode)
	{
		case "CB_BACKPACK":		bCheckboxes = True; break;
		case "CB_ALL":			bCheckboxes = True; break;
		case "CB_TRADER":		bCheckboxes = True; break;
	}
	if (bCheckboxes)
	{
		sHeader = XI_ConvertString("titleFilter");
		sText1 = "Предметы героя: показывает только те предметы, что есть у вас.";
		sText3 = "Предметы торговца: показывает только те предметы, что есть у торговца.";
		sText2 = "Все предметы: стандарт, показывает как ваши предметы, так и предметы торговца.";
	}
	else
	{// покажем помощь по работе с формой
		sHeader = XI_ConvertString("titleItemsTrade");
		sText1 = "Двойной клик мыши или Enter по строкам таблицы вызывает форму покупки/продажи предмета. "+ newStr() +
				 "Shift + лево/право на строках таблицы автоматически вызывают форму с предустановленным количеством покупки/продажи на максимальное. "+ newStr() +
				 "Ввод положительного количества с клавиатуры устанавливает покупку предмета, а отрицательного (с минусом) продажу."+ newStr() +
				 "Стрелки лево/право изменяют количество по одному, а Shift + лево/право на максимально доступное. Нажатие Enter на форме равносильно ОК, а Esc - Отмена." + newStr() +
				 "Находясь в режиме формы и мотая список в таблице стрелкам вверх/вниз, можно просматривать описание предмета под курсором таблицы.";

		sText3 = "В списке на продажу отсутствуют экипированные персонажем предметы.";
		sText2 = "Быстрая продажа всего: стрелками вверх/вниз по списку, Shift + право, Enter";
	}
	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,192,192,192), sText3, argb(255,255,255,255), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);
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
	if (bShowChangeWin) // жмем окей, когда курсор на таблице
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
	string sControl = GetEventData();
	int iSelected = GetEventData();
	string sRow = "tr" + (iSelected);
	SetCharWeight();
	SetVariable();
	ShowGoodsInfo(GameInterface.TABLE_LIST.(sRow).id);
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
	DeleteAttribute(&GameInterface, "CHARACTERS_SCROLL");

	nCurScrollNum = -1;
	GameInterface.CHARACTERS_SCROLL.current = 0;
	makearef(pRef,pchar.Fellows.Passengers);

	int nListSize = GetPassengersQuantity(pchar);
	int nListSizeFree = GetNotQuestPassengersQuantity(pchar);

	GameInterface.CHARACTERS_SCROLL.NotUsed = 6;
	GameInterface.CHARACTERS_SCROLL.ListSize = nListSizeFree + 2;

	GameInterface.CHARACTERS_SCROLL.ImagesGroup.t0 = "EMPTYFACE";

	FillFaceList("CHARACTERS_SCROLL.ImagesGroup", pchar, 2); // passengers

	GameInterface.CHARACTERS_SCROLL.BadTex1 = 0;
	GameInterface.CHARACTERS_SCROLL.BadPic1 = "emptyface";

	int m = 0;
	attributeName = "pic" + (m + 1);
	GameInterface.CHARACTERS_SCROLL.(attributeName).character = nMainCharacterIndex;
	GameInterface.CHARACTERS_SCROLL.(attributeName).img1 = GetFacePicName(pchar);
	GameInterface.CHARACTERS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup","FACE128_" + pchar.FaceID);
	m++;

	for(i = 0; i < nListSize; i++)
	{
		_curCharIdx = GetPassenger(pchar, i);

		bOk = CheckAttribute(&characters[_curCharIdx], "prisoned") && sti(characters[_curCharIdx].prisoned) == true;
		if(_curCharIdx != -1  && !CheckAttribute(&characters[_curCharIdx], "isquest") && !bOk)
		{
			if (IsOfficer(&characters[_curCharIdx]))  // boal
			{
				attributeName = "pic" + (m + 1);
				GameInterface.CHARACTERS_SCROLL.(attributeName).character = _curCharIdx;
				GameInterface.CHARACTERS_SCROLL.(attributeName).img1 = GetFacePicName(GetCharacter(_curCharIdx));
				GameInterface.CHARACTERS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup","FACE128_"+Characters[_curCharIdx].FaceID);
				m++;
			}
		}
	}
}

void SetVariable()
{
	string sText, sTextSecond;

	iCharCapacity = GetMaxItemsWeight(refCharacter);
	sText  = FloatToString(fCharWeight, 1) + " / " + iCharCapacity;
	SetFormatedText("CAPACITY", XI_ConvertString("Weight") + ":\n" + sText);

	iTotalSpace = iMaxGoodsStore;
	string sMaxGoodsStore;
	sMaxGoodsStore = "Торговец"; //XI_ConvertString("store");
	SetFormatedText("STORE_CAPACITY", sMaxGoodsStore);

	sText = XI_ConvertString("OurMoney") + " " + FindRussianMoneyString(sti(pchar.money));
	SetFormatedText("OUR_GOLD", sText);
}

void ProcessFrame()
{
	if(sti(GameInterface.CHARACTERS_SCROLL.current) != nCurScrollNum && GetCurrentNode() == "CHARACTERS_SCROLL")
	{
		XI_WindowDisable("QTY_WINDOW", true);
		XI_WindowShow("QTY_WINDOW", false);
		nCurScrollNum = sti(GameInterface.CHARACTERS_SCROLL.current);
		string sAttr = "pic" + (nCurScrollNum + 1);
		refCharacter = &characters[sti(GameInterface.CHARACTERS_SCROLL.(sAttr).character)];
		switch (refCharacter.sex)
		{
			case "man": SetNewPicture("EQUIP_BIG_PICTURE", "interfaces\sith\CharEquip_Man.tga");
			break;
			case "woman": SetNewPicture("EQUIP_BIG_PICTURE", "interfaces\sith\CharEquip_Woman.tga");
			break;
			case "skeleton": SetNewPicture("EQUIP_BIG_PICTURE", "interfaces\sith\CharEquip_Skeleton.tga");
			break;
		}
		SetDescription();
		//FillEquipInfo();
		FillCharacterInfo();
		GameInterface.TABLE_LIST.select = 1;
		GameInterface.TABLE_LIST.top = 0;
	}
}
void FillCharacterInfo()
{
	SetNewPicture("MAIN_CHARACTER_PICTURE", "interfaces\portraits\256\face_" + refCharacter.FaceId + ".tga");
	GameInterface.strings.CharName = GetFullName(refCharacter);
}
void SetDescription()
{
 	if(GetCurrentNode() == "CHARACTERS_SCROLL")
	{
		string attributeName = attributeName = "pic" + (nCurScrollNum+1);
		if(CheckAttribute(&GameInterface, "CHARACTERS_SCROLL." + attributeName))
		{
			SetCharWeight();
		}
	}
	CalculateInfoData();
	SetVariable();
}

void SetCharWeight()
{
	fCharWeight  = GetItemsWeight(refCharacter);

	fStoreWeight = 0;
}
// инфа о предмете
void ShowGoodsInfo(string sItemID)
{
	sCurItem = sItemID;
	ref	arItm = &Items[FindItem(sCurItem)];
	string GoodName = arItm.name;
	int	lngFileID = LanguageOpenFile("ItemsDescribe.txt");
	string sHeader = LanguageConvertString(lngFileID, GoodName);

	string describeStr = "";

	if (bBettaTestMode)
	{
		describeStr += " id = " + sCurItem + NewStr();
		if(CheckAttribute(arItm, "dmg_min.old") && CheckAttribute(arItm, "dmg_max.old"))
		{
			describeStr += "OldDmgMin = " + sti(arItm.dmg_min.old) + ", OldDmgMax = "+sti(arItm.dmg_max.old) + newStr();
		}
	}
	describeStr += GetItemDescribe(sCurItem);

	fWeight = GetItemWeight(sCurItem);

	BuyOrSell = 0;
	SetFormatedText("QTY_TypeOperation", "");
	SetFormatedText("QTY_Result", "");
	GameInterface.qty_edit.str = "0";

	SetNewGroupPicture("QTY_GOODS_PICTURE", arItm.picTexture, "itm" + arItm.picIndex);
	SetFormatedText("QTY_CAPTION", sHeader);
	SetFormatedText("QTY_GOODS_INFO", describeStr);
	LanguageCloseFile(lngFileID);

	iCharQty = GetCharacterFreeItem(refCharacter, sCurItem);
	iStoreQty = GetCharacterFreeItem(refStoreChar, sCurItem);

	SetFormatedText("QTY_INFO_STORE_QTY", its(iStoreQty));
	SetFormatedText("QTY_INFO_SHIP_QTY", its(iCharQty));
	BuyOrSell = 0;

	iStorePrice = GetTradeItemPrice(sCurItem, PRICE_TYPE_SELL);
	SetFormatedText("QTY_INFO_STORE_PRICE",XI_ConvertString("Price buy") + NewStr() + its(iStorePrice));

	iCharPrice = GetTradeItemPrice(sCurItem, PRICE_TYPE_BUY);
	SetFormatedText("QTY_INFO_SHIP_PRICE", XI_ConvertString("Price sell") + NewStr() + its(iCharPrice));
}

//// {*} BUHO-FIST - ADDED CODE - Checkboxes processing function.
void ProcessFilter(string sButton)
{
	nocheck = false;
	switch (sButton)
	{
	case "CB_BACKPACK":
		/*
		Radio-button semantics:
		- If the button was selected the user is deselecting it, so reselect it and exit.
		- If the button was not selected, deselect all others, set the state variable and
		  reload the table.
		*/
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_BACKPACK", 2, 1, 1);
		if (FIT_FilterState != FIT_BACKPACK)
		{
			// Button being selected.
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_ALL", 2, 1, 0);
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_TRADER", 2, 1, 0);
			FIT_FilterState = FIT_BACKPACK;
			AddToTable();
		}
		break;
	case "CB_ALL":
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_ALL", 2, 1, 1);
		if (FIT_FilterState != FIT_ALL)
		{
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_BACKPACK", 2, 1, 0);
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_TRADER", 2, 1, 0);
			FIT_FilterState = FIT_ALL;
			AddToTable();
		}
		break;
	case "CB_TRADER":
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_TRADER", 2, 1, 1);
		if (FIT_FilterState != FIT_TRADER)
		{
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_BACKPACK", 2, 1, 0);
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_ALL", 2, 1, 0);
			FIT_FilterState = FIT_TRADER;
			AddToTable();
		}
		break;
	}
}
//// {*} BUHO END ADDITION

void TransactionOK()
{
	int nTradeQuantity, moneyback;
	confirmChangeQTY_EDIT();
	nTradeQuantity = sti(GameInterface.qty_edit.str);
	if (BuyOrSell == 0)
	{
		EndTooltip();
		return;
	}

 	if (BuyOrSell == 1) // BUY
	{
		TakeNItems(refStoreChar, sCurItem, -nTradeQuantity);
		TakeNItems(refCharacter, sCurItem, nTradeQuantity);
		//#20200218-01
		/*if (CheckAttribute(&Items[FindItem(sCurItem)], "shown"))
			Items[FindItem(sCurItem)].shown = false;*/
		moneyback = makeint(iCharPrice*stf(GameInterface.qty_edit.str) + 0.5);
		pchar.money = sti(pchar.money) - moneyback;
		Statistic_AddValue(Pchar, "Money_spend", moneyback);
		// boal  check skill -->
		AddCharacterExpToSkill(pchar, "Commerce", moneyback / 700.0);
		WaitDate("",0,0,0, 0, 1);
		// boal <--
	}
 	else
	{ // SELL
		TakeNItems(refStoreChar, sCurItem, nTradeQuantity);
		TakeNItems(refCharacter, sCurItem, -nTradeQuantity);
		//#20200218-01
		/*if(CheckAttribute(&Items[FindItem(sCurItem)], "shown"))
			Items[FindItem(sCurItem)].shown = true;*/
		moneyback = makeint(iStorePrice*stf(GameInterface.qty_edit.str) + 0.5);
  		pchar.money = sti(pchar.money) + moneyback;
		Statistic_AddValue(Pchar, "Money_get", moneyback);
		// boal  check skill -->
		AddCharacterExpToSkill(pchar, "Commerce", moneyback / 1000.0);
		WaitDate("",0,0,0, 0, 1);
		// boal <--
	}
	AddToTable();
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
	trace("ChangeQTY_EDIT");
	float iWeight;
	SetCharWeight();
	GameInterface.qty_edit.str = sti(GameInterface.qty_edit.str);
	if (sti(GameInterface.qty_edit.str) == 0)
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
			iWeight = (fWeight * sti(GameInterface.qty_edit.str));
			if ((fStoreWeight + iWeight) > iTotalSpace)
			{
				iWeight = iTotalSpace - fStoreWeight - 0.01; // чуть меньше
				GameInterface.qty_edit.str = makeint(iWeight / fWeight );
				iWeight = fWeight * sti(GameInterface.qty_edit.str);
				GameInterface.qty_edit.str = makeint(iWeight / fWeight ); // округдение
			}
			// проверка на колво доступное <--
			// квестовые не продать -->
			if (IsQuestUsedItem(sCurItem))
			{
				GameInterface.qty_edit.str = 0;
			}
			// квестовые не продать <--
			SetFormatedText("QTY_TypeOperation", "Продать");
			SetFormatedText("QTY_Result", "Золото " + makeint(iStorePrice*stf(GameInterface.qty_edit.str) + 0.5) +
							", вес " + FloatToString(iWeight, 1) );
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
			if ((fCharWeight + iWeight) > iCharCapacity)
			{
				iWeight = iCharCapacity - fCharWeight - 0.01; // чуть меньше
				if (iWeight < 0) iWeight = 0;
				GameInterface.qty_edit.str = makeint(iWeight / fWeight );
				iWeight = fWeight * sti(GameInterface.qty_edit.str);
				GameInterface.qty_edit.str = makeint(iWeight / fWeight ); // округдение
			}
			if (makeint(iCharPrice*stf(GameInterface.qty_edit.str) + 0.5) > sti(pchar.money))
			{
				GameInterface.qty_edit.str = makeint(sti(pchar.money) / iCharPrice);
				iWeight = fWeight * sti(GameInterface.qty_edit.str);
			}
			// проверка на колво доступное <--

			SetFormatedText("QTY_TypeOperation", "Купить");
			SetFormatedText("QTY_Result", "Золото " + makeint(iCharPrice*stf(GameInterface.qty_edit.str) + 0.5) +
							", вес " + FloatToString(iWeight, 1) );
		}
	}
	// если получили ноль
	if (sti(GameInterface.qty_edit.str) == 0)
	{
		SetFormatedText("QTY_TypeOperation", "");
		SetFormatedText("QTY_Result", "");
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
	if (!bShowChangeWin)
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
	if (!bShowChangeWin)
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
	if (!bShowChangeWin) return;
	if (BuyOrSell == 0)
	{
		GameInterface.qty_edit.str = -1;
	}
	else
	{
		if (BuyOrSell == -1)
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
	if (!bShowChangeWin) return;
	if (BuyOrSell == 0)
	{
		GameInterface.qty_edit.str = 1;
	}
	else
	{
  		if (BuyOrSell == 1)
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

// Lugger: Equip Info -->

void ExitEquipWindow()
{
	XI_WindowShow("EQUIP_WINDOW", false);
	XI_WindowDisable("EQUIP_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetNodeUsing("TABLE_LIST", true);
	SetNodeUsing("SCROLL_LIST", true);

	SetNodeUsing("CB_BACKPACK", true);//TO DO - просто добавить заглушку? стрелки скролла персонажей доступны, но не обновляют снаряжение на кукле. только фоновую картинку
	SetNodeUsing("CB_ALL", true);
	SetNodeUsing("CB_TRADER", true);
	SetNodeUsing("AUTOTRADE_ALL", true);

	SetCurrentNode("TABLE_LIST");

}

void ShowEquipWindow()
{
	XI_WindowShow("EQUIP_WINDOW", true);
	XI_WindowDisable("EQUIP_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetNodeUsing("TABLE_LIST", false);
	SetNodeUsing("SCROLL_LIST", false);

	SetNodeUsing("CB_BACKPACK", false);
	SetNodeUsing("CB_ALL", false);
	SetNodeUsing("CB_TRADER", false);
	SetNodeUsing("AUTOTRADE_ALL", false);

	SetCurrentNode("EQUIP_WINDOW");

	string sBlade = GetCharacterEquipByGroup(refCharacter, "blade");
	string sGun = GetCharacterEquipByGroup(refCharacter, "gun");
	string sSpyglass = GetCharacterEquipByGroup(refCharacter, "spyglass");
	string sCirass = GetCharacterEquipByGroup(refCharacter, "cirass");
	string sBackPack = GetCharacterEquipByGroup(refCharacter, "BackPack");
	string sTalisman = GetCharacterEquipByGroup(refCharacter, "talisman");
	string sBook = GetCharacterEquipByGroup(refCharacter, "book");
	string sShow1 = GetCharacterEquipByGroup(refCharacter, "jewelry_indian_left");
	string sShow2 = GetCharacterEquipByGroup(refCharacter, "jewelry_indian_right");
	string sShow3 = GetCharacterEquipByGroup(refCharacter, "indian_center");
	string sShow4 = GetCharacterEquipByGroup(refCharacter, "idols_left");
	string sShow5 = GetCharacterEquipByGroup(refCharacter, "idols_right");

	if(CheckAttribute(refCharacter, "equip.blade") && refCharacter.equip.blade != "")
	{
		SetNewGroupPicture("EQUIP_BLADE_PIC", Items[FindItem(sBlade)].picTexture, "itm" + Items[FindItem(sBlade)].picIndex);
	}
	else
	{
		SetNewGroupPicture("EQUIP_BLADE_PIC", "none", "none");
	}

	if(CheckAttribute(refCharacter, "equip.gun") && refCharacter.equip.gun != "")
	{
		SetNewGroupPicture("EQUIP_GUN_PIC", Items[FindItem(sGun)].picTexture, "itm" + Items[FindItem(sGun)].picIndex);
	}
	else
	{
		SetNewGroupPicture("EQUIP_GUN_PIC", "none", "none");
	}

	if(CheckAttribute(refCharacter, "equip.spyglass") && refCharacter.equip.spyglass != "")
	{
		SetNewGroupPicture("EQUIP_SPYGLASS_PIC", Items[FindItem(sSpyglass)].picTexture, "itm" + Items[FindItem(sSpyglass)].picIndex);
	}
	else
	{
		SetNewGroupPicture("EQUIP_SPYGLASS_PIC", "none", "none");
	}

	if(CheckAttribute(refCharacter, "equip.cirass") && refCharacter.equip.cirass != "")
	{
		SetNewGroupPicture("EQUIP_CIRASS_PIC", Items[FindItem(sCirass)].picTexture, "itm" + Items[FindItem(sCirass)].picIndex);
	}
	else
	{
		SetNewGroupPicture("EQUIP_CIRASS_PIC", "none", "none");
	}

	if(CheckAttribute(refCharacter, "equip.BackPack") && refCharacter.equip.BackPack != "")
	{
		SetNewGroupPicture("EQUIP_BACKPACK_PIC", Items[FindItem(sBackPack)].picTexture, "itm" + Items[FindItem(sBackPack)].picIndex);
	}
	else
	{
		SetNewGroupPicture("EQUIP_BACKPACK_PIC", "none", "none");
	}

	if(CheckAttribute(refCharacter, "equip.talisman") && refCharacter.equip.talisman != "")
	{
		SetNewGroupPicture("EQUIP_TALISMAN_PIC", Items[FindItem(sTalisman)].picTexture, "itm" + Items[FindItem(sTalisman)].picIndex);
	}
	else
	{
		SetNewGroupPicture("EQUIP_TALISMAN_PIC", "none", "none");
	}

	if(CheckAttribute(refCharacter, "equip.book") && refCharacter.equip.book != "")
	{
		SetNewGroupPicture("EQUIP_BOOK_PIC", Items[FindItem(sBook)].picTexture, "itm" + Items[FindItem(sBook)].picIndex);
	}
	else
	{
		SetNewGroupPicture("EQUIP_BOOK_PIC", "none", "none");
	}

	if(CheckAttribute(refCharacter, "equip.jewelry_indian_left") && refCharacter.equip.jewelry_indian_left != "")
	{
		SetNewGroupPicture("EQUIP_SHOW1_PIC", Items[FindItem(sShow1)].picTexture, "itm" + Items[FindItem(sShow1)].picIndex);
	}
	else
	{
		SetNewGroupPicture("EQUIP_SHOW1_PIC", "none", "none");
	}

	if(CheckAttribute(refCharacter, "equip.jewelry_indian_right") && refCharacter.equip.jewelry_indian_right != "")
	{
		SetNewGroupPicture("EQUIP_SHOW2_PIC", Items[FindItem(sShow2)].picTexture, "itm" + Items[FindItem(sShow2)].picIndex);
	}
	else
	{
		SetNewGroupPicture("EQUIP_SHOW2_PIC", "none", "none");
	}

	if(CheckAttribute(refCharacter, "equip.indian_center") && refCharacter.equip.indian_center != "")
	{
		SetNewGroupPicture("EQUIP_SHOW3_PIC", Items[FindItem(sShow3)].picTexture, "itm" + Items[FindItem(sShow3)].picIndex);
	}
	else
	{
		SetNewGroupPicture("EQUIP_SHOW3_PIC", "none", "none");
	}

	if(CheckAttribute(refCharacter, "equip.idols_left") && refCharacter.equip.idols_left != "")
	{
		SetNewGroupPicture("EQUIP_SHOW4_PIC", Items[FindItem(sShow4)].picTexture, "itm" + Items[FindItem(sShow4)].picIndex);
	}
	else
	{
		SetNewGroupPicture("EQUIP_SHOW4_PIC", "none", "none");
	}

	if(CheckAttribute(refCharacter, "equip.idols_right") && refCharacter.equip.idols_right != "")
	{
		SetNewGroupPicture("EQUIP_SHOW5_PIC", Items[FindItem(sShow5)].picTexture, "itm" + Items[FindItem(sShow5)].picIndex);
	}
	else
	{
		SetNewGroupPicture("EQUIP_SHOW5_PIC", "none", "none");
	}

	SetFormatedText("EQUIP_CAPTION", XI_ConvertString("Equipment") + ": " + refCharacter.name + " " + refCharacter.lastname);
}

void ShowBladeEquipInfo()
{
	if(!CheckAttribute(refCharacter, "equip.blade"))
	{
		return;
	}
	if(refCharacter.equip.blade == "")
	{
		return;
	}

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;

	string sItem = GetCharacterEquipByGroup(refCharacter, "blade");
	ref itm = ItemsFromID(sItem);

	sGroup = itm.picTexture;
	sGroupPicture = "itm" + itm.picIndex;

	sHeader = "";

	sHeader = itm.name;
	sHeader = LanguageConvertString(idLngFile, sHeader);

	sText1 = GetItemDescribe(sItem);

	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 100, 100);
	LanguageCloseFile(idLngFile);
}

void ShowGunEquipInfo()
{
	if(!CheckAttribute(refCharacter, "equip.gun"))
	{
		return;
	}
	if(refCharacter.equip.gun == "")
	{
		return;
	}

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;

	string sItem = GetCharacterEquipByGroup(refCharacter, "gun");
	ref itm = ItemsFromID(sItem);

	sGroup = itm.picTexture;
	sGroupPicture = "itm" + itm.picIndex;

	sHeader = "";

	sHeader = itm.name;
	sHeader = LanguageConvertString(idLngFile, sHeader);

	sText1 = GetItemDescribe(sItem);

	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 100, 100);
	LanguageCloseFile(idLngFile);
}

void ShowSpyglassEquipInfo()
{
	if(!CheckAttribute(refCharacter, "equip.spyglass"))
	{
		return;
	}
	if(refCharacter.equip.spyglass == "")
	{
		return;
	}

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;

	string sItem = GetCharacterEquipByGroup(refCharacter, "spyglass");
	ref itm = ItemsFromID(sItem);

	sGroup = itm.picTexture;
	sGroupPicture = "itm" + itm.picIndex;

	sHeader = "";

	sHeader = itm.name;
	sHeader = LanguageConvertString(idLngFile, sHeader);

	sText1 = GetItemDescribe(sItem);

	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 100, 100);
	LanguageCloseFile(idLngFile);
}

void ShowBackPackEquipInfo()
{
	if(!CheckAttribute(refCharacter, "equip.BackPack"))
	{
		return;
	}
	if(refCharacter.equip.BackPack == "")
	{
		return;
	}

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;

	string sItem = GetCharacterEquipByGroup(refCharacter, "BackPack");
	ref itm = ItemsFromID(sItem);

	sGroup = itm.picTexture;
	sGroupPicture = "itm" + itm.picIndex;

	sHeader = "";

	sHeader = itm.name;
	sHeader = LanguageConvertString(idLngFile, sHeader);

	sText1 = GetItemDescribe(sItem);

	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 100, 100);
	LanguageCloseFile(idLngFile);
}

void ShowTalismanEquipInfo()
{
	if(!CheckAttribute(refCharacter, "equip.talisman"))
	{
		return;
	}
	if(refCharacter.equip.talisman == "")
	{
		return;
	}

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;

	string sItem = GetCharacterEquipByGroup(refCharacter, "talisman");
	ref itm = ItemsFromID(sItem);

	sGroup = itm.picTexture;
	sGroupPicture = "itm" + itm.picIndex;

	sHeader = "";

	sHeader = itm.name;
	sHeader = LanguageConvertString(idLngFile, sHeader);

	sText1 = GetItemDescribe(sItem);

	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 100, 100);
	LanguageCloseFile(idLngFile);
}

void ShowCirassEquipInfo()
{
	if(!CheckAttribute(refCharacter, "equip.cirass"))
	{
		return;
	}
	if(refCharacter.equip.cirass == "")
	{
		return;
	}

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;

	string sItem = GetCharacterEquipByGroup(refCharacter, "cirass");
	ref itm = ItemsFromID(sItem);

	sGroup = itm.picTexture;
	sGroupPicture = "itm" + itm.picIndex;

	sHeader = "";

	sHeader = itm.name;
	sHeader = LanguageConvertString(idLngFile, sHeader);

	sText1 = GetItemDescribe(sItem);

	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 100, 100);
	LanguageCloseFile(idLngFile);
}

void ShowBookEquipInfo()
{
	if(!CheckAttribute(refCharacter, "equip.book"))
	{
		return;
	}
	if(refCharacter.equip.book == "")
	{
		return;
	}

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;

	string sItem = GetCharacterEquipByGroup(refCharacter, "book");
	ref itm = ItemsFromID(sItem);

	sGroup = itm.picTexture;
	sGroupPicture = "itm" + itm.picIndex;

	sHeader = "";

	sHeader = itm.name;
	sHeader = LanguageConvertString(idLngFile, sHeader);

	sText1 = GetItemDescribe(sItem);

	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 100, 100);
	LanguageCloseFile(idLngFile);
}

void Show1EquipInfo()
{
	if(!CheckAttribute(refCharacter, "equip.jewelry_indian_left"))
	{
		return;
	}
	if(refCharacter.equip.jewelry_indian_left == "")
	{
		return;
	}

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;

	string sItem = GetCharacterEquipByGroup(refCharacter, "jewelry_indian_left");
	ref itm = ItemsFromID(sItem);

	sGroup = itm.picTexture;
	sGroupPicture = "itm" + itm.picIndex;

	sHeader = "";

	sHeader = itm.name;
	sHeader = LanguageConvertString(idLngFile, sHeader);

	sText1 = GetItemDescribe(sItem);

	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 100, 100);
	LanguageCloseFile(idLngFile);
}

void Show2EquipInfo()
{
	if(!CheckAttribute(refCharacter, "equip.jewelry_indian_right"))
	{
		return;
	}
	if(refCharacter.equip.jewelry_indian_right == "")
	{
		return;
	}

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;

	string sItem = GetCharacterEquipByGroup(refCharacter, "jewelry_indian_right");
	ref itm = ItemsFromID(sItem);

	sGroup = itm.picTexture;
	sGroupPicture = "itm" + itm.picIndex;

	sHeader = "";

	sHeader = itm.name;
	sHeader = LanguageConvertString(idLngFile, sHeader);

	sText1 = GetItemDescribe(sItem);

	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 100, 100);
	LanguageCloseFile(idLngFile);
}

void Show3EquipInfo()
{
	if(!CheckAttribute(refCharacter, "equip.indian_center"))
	{
		return;
	}
	if(refCharacter.equip.indian_center == "")
	{
		return;
	}

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;

	string sItem = GetCharacterEquipByGroup(refCharacter, "indian_center");
	ref itm = ItemsFromID(sItem);

	sGroup = itm.picTexture;
	sGroupPicture = "itm" + itm.picIndex;

	sHeader = "";

	sHeader = itm.name;
	sHeader = LanguageConvertString(idLngFile, sHeader);

	sText1 = GetItemDescribe(sItem);

	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 100, 100);
	LanguageCloseFile(idLngFile);
}

void Show4EquipInfo()
{
	if(!CheckAttribute(refCharacter, "equip.idols_left"))
	{
		return;
	}
	if(refCharacter.equip.idols_left == "")
	{
		return;
	}

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;

	string sItem = GetCharacterEquipByGroup(refCharacter, "idols_left");
	ref itm = ItemsFromID(sItem);

	sGroup = itm.picTexture;
	sGroupPicture = "itm" + itm.picIndex;

	sHeader = "";

	sHeader = itm.name;
	sHeader = LanguageConvertString(idLngFile, sHeader);

	sText1 = GetItemDescribe(sItem);

	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 100, 100);
	LanguageCloseFile(idLngFile);
}

void Show5EquipInfo()
{
	if(!CheckAttribute(refCharacter, "equip.idols_right"))
	{
		return;
	}
	if(refCharacter.equip.idols_right == "")
	{
		return;
	}

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;

	string sItem = GetCharacterEquipByGroup(refCharacter, "idols_right");
	ref itm = ItemsFromID(sItem);

	sGroup = itm.picTexture;
	sGroupPicture = "itm" + itm.picIndex;

	sHeader = "";

	sHeader = itm.name;
	sHeader = LanguageConvertString(idLngFile, sHeader);

	sText1 = GetItemDescribe(sItem);

	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 100, 100);
	LanguageCloseFile(idLngFile);
}

void ClickSaber()
{
	ClickItem("BLADE");
}

void ClickGun()
{
	ClickItem("GUN");
}

void ClickSpyGlass()
{
	ClickItem("SPYGLASS");
}

void ClickCirass()
{
	ClickItem("CIRASS");
}

void ClickBackPack()
{
	ClickItem("BACKPACK");
}

void ClickTalisman()
{
	ClickItem("TALISMAN");
}

void ClickBook()
{
	ClickItem("BOOK");
}

void ClickShow1()
{
	ClickItem("SHOW1");
}

void ClickShow2()
{
	ClickItem("SHOW2");
}

void ClickShow3()
{
	ClickItem("SHOW3");
}

void ClickShow4()
{
	ClickItem("SHOW4");
}

void ClickShow5()
{
	ClickItem("SHOW5");
}

void ClickItem(string sItem)
{
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BLADE_PIC", 5, 0);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_GUN_PIC", 5, 0);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_CIRASS_PIC", 5, 0);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_SPYGLASS_PIC", 5, 0);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BACKPACK_PIC", 5, 0);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_TALISMAN_PIC", 5, 0);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BOOK_PIC", 5, 0);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_SHOW1_PIC", 5, 0);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_SHOW2_PIC", 5, 0);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_SHOW3_PIC", 5, 0);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_SHOW4_PIC", 5, 0);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_SHOW5_PIC", 5, 0);

	string sNode = "EQUIP_" + sItem + "_PIC";
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,sNode, 5, 1);
}

// Lugger: Equip Info <--

void Autotrade_All()
{
	if (!IsPCharHaveTreasurer()) {Log_Info("Нет казначея. Закупки некому проводить!"); return;}
	Fastsale_trash();
	int iOfficer = -1;
	ref _chr;

	for(int z = 0; z < MAX_NUM_FIGHTERS+6; z++)
	{
		iOfficer = GetOfficersIndex(pchar, z);
		if(iOfficer != -1)
		{
			_chr = &characters[iOfficer];
			SellExcessConsume(_chr);
		}
	}
	for(z = 0; z < MAX_NUM_FIGHTERS+6; z++)
	{
		iOfficer = GetOfficersIndex(pchar, z);
		if(iOfficer != -1)
		{
			_chr = &characters[iOfficer];
			BuyConsume(_chr);
		}
	}
//двумя циклами сначала продавать со всех, а потом покупать - это позволит "передавать" излишки через торговца. Но так будут теряться монеты на разнице цен.
//TO DO - с одной стороны - это плата за удобство, с другой - нелепость. Позже заменить функцией равномерного распредления припасов между абордагами???

	AddToTable();
	EndTooltip();
}

void Autotrade_This()
{
	if (!IsPCharHaveTreasurer()) {Log_Info("Нет казначея. Закупки некому проводить!"); return;}
	Fastsale_trash_single(refCharacter);
	SellExcessConsume(refCharacter);
	BuyConsume(refCharacter);
	AddToTable();
	EndTooltip();
}

void BuyConsume(ref chr)
{
	int 	qty = 0;
	int 	i, iCost;
	int		curqty = 0;
	int		curTraderQty = 0;
	int		iMoneyQty = 0;
	bool	bAdded, bNotEnough, bNotOverWeight, bNotEnoughTrader;
	float	freeWeight, fItemWeight;

	string sTemp = "";
	if (chr.sex == "woman") sTemp = "а";

	freeWeight = GetMaxItemsWeight(chr) - GetItemsWeight(chr);
	if (freeWeight < 0.1)
	{
		Log_Info(GetFullName(chr) + " перегружен" + sTemp + ". Пополнить снаряжение не удалось.");
		return;
	}

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	bAdded = false;//будет ли хоть один предмет добавлен
	bNotOverWeight = false;//хватало ли места в инвентаре
	bNotEnough = false;//хватало ли уже всего
	bNotEnoughTrader = false;//хватало ли у торговца

	aref arInventory, arItem;
	string sItem;
	ref rItem;

	makearef(arInventory, chr.TransferItems);
	for (i = 0; i < GetAttributesNum(arInventory); i++)
	{
		arItem = GetAttributeN(arInventory, i);
		sItem = GetAttributeName(arItem);
		rItem = ItemsFromID(sItem);

		if (IsGenerableItem(sItem)) continue;
		if (!CheckAttribute(rItem, "sortIndex"))
		{
			if (!HasSubStr(sItem, "CompCraft")) continue;//в списке только расходники
		}
		else
		{
			if (rItem.SortIndex == 1 || rItem.SortIndex == 2 || rItem.ItemType == "CRAFTCOMPONENTS"); else continue;//в списке расходники и крафт
		}

		if (sItem == "Lockpick") continue;//отмычки пропускаем
		if (sItem == "CompCraft_Tools" || sItem == "CompCraft_Locksmith" || sItem == "CompCraft_Puleleyka") continue; //исключение выбранных Шахом штук
		curTraderQty = GetCharacterItem(refStoreChar, sItem);

//if (curTraderQty == 0) continue;//у торговца ничего нет, давай следующий предмет//TO DO - пока что без возможности покупать из воздуха
//row = "tr" + n;
		qty = sti(chr.TransferItems.(sItem));
		//if (qty == 0) continue; //вообще не требуется закупать
		curqty = GetCharacterItem(chr, sItem);
		if (qty > curqty) {qty = qty - curqty;}
			else continue;//этого припаса уже было достаточно
//TO DO - можно бы совсем убрать эту проверку превышения, если сначала всё равно должна идти продажа лишнего
//Log_TestInfo("отладка - " + sItem + "|" + qty + "|" + curqty + "|" + curTraderQty);
		if (qty > curTraderQty) {qty = curTraderQty; bNotEnoughTrader = true;}//TO DO - пока что без возможности покупать из воздуха
		if (qty == 0) continue; //нечего купить у торговца

		bNotEnough = true;//если сюда дошли хоть раз за цикл, значит чего-то не хватало до лимита

		fItemWeight = GetItemWeight(sItem);
		if (qty > makeint(freeWeight / fItemWeight)) qty = makeint(freeWeight / fItemWeight);
		if (qty == 0) continue; //не хватает места даже для одного такого предмета
		bNotOverWeight = true;//хватало места хотя бы для одного предмета

		iCost = GetTradeItemPrice(sItem, PRICE_TYPE_BUY);
		if (qty > sti(PChar.Money) / iCost)) qty = sti(PChar.Money) / iCost;//TO DO - ВАЖНО - перепроверить деления и округления - при тесте покупало на один предмет больше, чем было денег в кармане.
		if (qty == 0) continue; //не хватает денег даже на один такой предмет

		iMoneyQty -= iCost*qty;
		TakeNItems(chr, sItem, qty);
		TakeNItems(refStoreChar, sItem, -qty);
		if (qty > 0 && GetFullName(chr) == GetFullName(PChar)) Log_Info(GetFullName(chr) + " куплено: " + "'" + LanguageConvertString(idLngFile, rItem.name) + "' " + qty + " шт. " + iCost*qty + " зол.");
		//WaitDate("", 0, 0, 0, 0, 1);// Крутим время за каждый товар - многовато для закупок по списку
		freeWeight -= fItemWeight*qty;
		bAdded = true;//что-то успешно докупили
	}

	if (iMoneyQty != 0) // Если хоть что-то купили
	{
		AddmoneyToCharacter(PChar, iMoneyQty);
		ref rTreasurer = GetPCharTreasurerRef();//Казначей. Ему даем экспу
		AddCharacterExpToSkill(rTreasurer, "Commerce", MakeInt(abs(iMoneyQty) / 800) + rand(1) + 2) //отчитываться о том, что опыт за торговлю получил казначей, а не игрок?
		//TO DO - это начисление опыта за торговлю товарами, перепроверить, что за предметы столько же идёт
	}

	LanguageCloseFile(idLngFile);

	if (bAdded) 		{Log_Info(GetFullName(chr)+" пополнил" + sTemp + " комплект расходников.");	return;}
	if (bNotOverWeight)	{Log_Info(GetFullName(chr)+" не получил" + sTemp + " новых расходников. Кончились деньги."); return;}
	if (bNotEnough) 	{Log_Info(GetFullName(chr)+" не получил" + sTemp + " новых расходников из-за перегруза."); return;}
	if (bNotEnoughTrader) 	{Log_Info(GetFullName(chr)+" не получил" + sTemp + " новых расходников. Не было в наличии у торговца."); return;}
						 Log_Info(GetFullName(chr)+" уже имел" + sTemp + " полный комплект расходников.");
	//TO DO - сделать подробный и красивый вывод результата
	//TO DO - содержимое таблицы товаров не обновляется после отъёма товаров у торговца - исправить, Да и остаток золота в кармане тоже обновлять надо
}

void SellExcessConsume(ref chr)
{
	if (!CheckAttribute(chr,"TransferItems.SellRestriction")) return;//не включено разрешение продавать
	int 	qty = 0;
	int 	i, n, iCost;
	int		curqty = 0;
	int		iMoneyQty = 0;

	string sTemp = "";
	if (chr.sex == "woman") sTemp = "а";

	aref arInventory, arItem;
	string sItem;
	ref rItem;

	makearef(arInventory, chr.TransferItems);
	for (i = 0; i < GetAttributesNum(arInventory); i++)
	{
		arItem = GetAttributeN(arInventory, i);
		sItem = GetAttributeName(arItem);
		rItem = ItemsFromID(sItem);

		if (IsGenerableItem(sItem)) continue;
		if (!CheckAttribute(rItem,"sortIndex"))
		{
			if (!HasSubStr(sItem,"CompCraft")) continue;//в списке только расходники
		}
		else
		{
			if (rItem.SortIndex == 1 || rItem.SortIndex == 2 || rItem.ItemType == "CRAFTCOMPONENTS"); else continue;//в списке расходники и крафт
		}

		if (sItem == "Lockpick") continue;//отмычки пропускаем
		if (sItem == "CompCraft_Tools" || sItem == "CompCraft_Locksmith" || sItem == "CompCraft_Puleleyka") continue; //исключение выбранных Шахом штук
		qty = sti(chr.TransferItems.(sItem));
		curqty = GetCharacterItem(chr, sItem);
		if (curqty > qty) qty = curqty - qty; else continue;
		iCost = GetTradeItemPrice(sItem, PRICE_TYPE_SELL);
		iMoneyQty += iCost*qty;
		TakeNItems(chr, sItem, -qty);
		TakeNItems(refStoreChar, sItem, qty);
		//WaitDate("", 0, 0, 0, 0, 1);// Крутим время за каждый товар - многовато для закупок по списку
	}
	if(iMoneyQty != 0) // Если хоть что-то продали
	{
		AddmoneyToCharacter(PChar, iMoneyQty);
		ref rTreasurer = GetPCharTreasurerRef();//Казначей. Ему даем экспу
		AddCharacterExpToSkill(rTreasurer, "Commerce", MakeInt(abs(iMoneyQty) / 800) + rand(1) + 2) //отчитываться о том, что опыт за торговлю получил казначей, а не игрок?
		//TO DO - это начисление опыта за торговлю товарами, перепроверить, что за предметы столько же идёт
		//TO DO - рандомные пары единичек опыта за каждую операцию в сумме дали бы больше опыта - надо ли это менять? выдавать опыт за каждый предмет или в суммарной функции увеличить бонус за число сделок?
		Log_Info(GetFullName(chr)+" продал" + sTemp + " излишки расходников.");
	}
}

void FastSaleCharacter(ref rChar, ref rSaleProps)
{
	aref arInventory, arItem;
	string sItem;
	ref rItem;
	int sellQty, sellcost, i;

	makearef(arInventory, rChar.Items);
	for (i = 0; i < GetAttributesNum(arInventory); i++)
	{
		arItem = GetAttributeN(arInventory, i);
		sItem = GetAttributeName(arItem);
		rItem = ItemsFromID(sItem);

		sellQty = GetCharacterFreeItem(rChar, sItem);
		if (sellQty == 0) continue;

		if ((sItem == "slave_01") || (sItem == "pistol3")) continue;

		if (CheckAttribute(rItem, "quality"))
		{
			if ((rItem.quality == "poor") || (rItem.quality == "ordinary"))
			{
				if (CheckAttribute(rItem, "groupID") && (rItem.groupID == GUN_ITEM_TYPE))
					rSaleProps.GunCount = sti(rSaleProps.GunCount) + sellQty;
				else
					rSaleProps.BladeCount = sti(rSaleProps.BladeCount) + sellQty;
			}
			else continue;
		}
		else
		{
			bool isRubbish =
				(sItem == "mineral2") ||	// Лютня
				(sItem == "mineral3") ||    // Свечи
				(sItem == "mineral4") ||    // Баклан
				(sItem == "mineral5") ||    // Старое ведро
				(sItem == "mineral6") ||    // Коралл
				(sItem == "mineral7") ||    // Трубка
				(sItem == "mineral8") ||    // Башмак
				(sItem == "mineral9") ||    // Кружка
				(sItem == "mineral10") ||   // Мешочек соли
				(sItem == "spyglass1") ||   // Дешевая подзорная труба
				(sItem == "spyglass2") ||   // Обычная подзорная труба
				(sItem == "jewelry6") ||    // Серебряное кольцо с сапфиром
				(sItem == "jewelry7") ||    // Золотое кольцо с изумрудом
				(sItem == "jewelry10") ||   // Золотое кольцо с сапфиром
				(sItem == "jewelry11") ||   // Большая жемчужина
				(sItem == "jewelry12") ||   // Маленькая жемчужина
				(sItem == "jewelry13") ||   // Камея
				(sItem == "jewelry16") ||   // Ожерелье
				(sItem == "jewelry18") ||   // Золотое кольцо с рубином
				(sItem == "indian2") ||     // Пугающая фигурка
				(sItem == "indian8") ||     // Серебряный кубок
				(sItem == "indian9") ||     // Алебастровый сосуд
				(sItem == "indian13") ||    // Древняя курительница
				(sItem == "indian16");      // Раскрашенный сосуд
			bool isTalisman =               
				(sItem == "indian17") ||	// Тельная ладанка
				(sItem == "indian3") ||     // Нефритовая маска
				(sItem == "indian5") ||     // Двойная маска
				(sItem == "indian7") ||     // Идол Великой Матери
				(sItem == "indian14") ||    // Чаша Ололиуки
				(sItem == "indian12") ||    // Кубок-тотем Тепейоллотля
				(sItem == "indian10") ||    // Оберег Эхекатля
				(sItem == "indian1");       // Оберег Тлальчитонатиу
			if (isRubbish)
			{
				rSaleProps.RubbishCount = sti(rSaleProps.RubbishCount) + sellQty;
			}
			else
			{
				if (isTalisman)
				{
					sellQty -= 1;
					rSaleProps.TalismanCount = sti(rSaleProps.TalismanCount) + sellQty;
				}
				else continue;
			}
		}

		rSaleProps.Items.(sItem) = sellQty;
	}

	makearef(arInventory, rSaleProps.Items);
	for (i = 0; i < GetAttributesNum(arInventory); i++)
	{
		arItem = GetAttributeN(arInventory, i);
		sItem = GetAttributeName(arItem);
		sellQty = sti(GetAttributeValue(arItem));

		sellcost = GetTradeItemPrice(sItem, PRICE_TYPE_SELL) * sellQty;
		TakeNItems(rChar, sItem, -sellQty);
		TakeNItems(refStoreChar, sItem, sellQty);
		rSaleProps.money = sti(rSaleProps.money) + sellcost;
	}

	DeleteAttribute(rSaleProps, "Items");
}

void Fastsale_trash()
{
	int iOfficer = -1;

	object sellProps;
	ref rSaleProps;
	makeref(rSaleProps, sellProps);

	rSaleProps.money = 0;
	rSaleProps.BladeCount = 0;
	rSaleProps.GunCount = 0;
	rSaleProps.RubbishCount = 0;
	rSaleProps.TalismanCount = 0;

	for (int z = 0; z < 6 + MAX_NUM_FIGHTERS; z++)
	{
		if (z == 0) iOfficer = GetMainCharacterIndex();
		else iOfficer = GetOfficersIndex(pchar, z);
		if (iOfficer != -1)
		{
			if (CheckAttribute(&characters[iOfficer],"fighter") || z == 0)
			{
				FastSaleCharacter(&characters[iOfficer], rSaleProps);
			}
		}
	}

	Log_Info("Продано: Клинков " + rSaleProps.BladeCount + ", Пистолетов " + rSaleProps.GunCount +
		", Идолов " + rSaleProps.TalismanCount + ", Хлама " + rSaleProps.RubbishCount);
	AddmoneyToCharacter(PChar, sti(rSaleProps.money));
	ref rTreasurer = GetPCharTreasurerRef();//Казначей. Ему даем экспу
	AddCharacterExpToSkill(rTreasurer, "Commerce", MakeInt(abs(sti(rSaleProps.money)) / 800) + rand(1) + 2);
}

void Fastsale_trash_single(ref character)
{
	object sellProps;
	ref rSaleProps;
	makeref(rSaleProps, sellProps);

	rSaleProps.money = 0;
	rSaleProps.BladeCount = 0;
	rSaleProps.GunCount = 0;
	rSaleProps.RubbishCount = 0;
	rSaleProps.TalismanCount = 0;

	FastSaleCharacter(character, rSaleProps);

	Log_Info("Продано: Клинков " + rSaleProps.BladeCount + ", Пистолетов " + rSaleProps.GunCount +
		", Идолов " + rSaleProps.TalismanCount + ", Хлама " + rSaleProps.RubbishCount);
	AddmoneyToCharacter(PChar, sti(rSaleProps.money));
	ref rTreasurer = GetPCharTreasurerRef();//Казначей. Ему даем экспу
	AddCharacterExpToSkill(rTreasurer, "Commerce", MakeInt(abs(sti(rSaleProps.money)) / 800) + rand(1) + 2);
}
