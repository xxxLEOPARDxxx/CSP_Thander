//#20180919-02
#define MAX_CHAR_LIST 20
#define NUM_REGULAR_OFFICERS 6

int	nCurScrollNum = 0;
int iCharCapacity;
int iTotalSpace;
float fCharWeight, fStoreWeight;
int iMaxGoodsStore = 50000;
int aList[MAX_CHAR_LIST];
string aListPos[MAX_CHAR_LIST];
int nCurrList = 0;
bool bShowChangeWin = false;
int  BuyOrSell = 0; // 1-buy -1 sell
//ref refStore,
ref refCharacter, refHeroChar;
int iCharQty, iStoreQty;
float fWeight;
int iCurGoodsIdx;
string sCurItem;

//// {*} BUHO-FIST - ADDED CODE - Fist state variable
#define FIT_ALL			0		// Normal
#define FIT_OFFICER	1		// Show backpack
#define FIT_HERO		2		// Show trader
int FIT_FilterState = 0;
//// {*} BUHO END ADDITION

void InitInterface_R(string iniName, ref pHero)
{
    for(int i = 0; i< MAX_CHAR_LIST; i++) aList[i] = -1;

    StartAboveForm(true);

	//refCharacter = pchar;
	refHeroChar = pHero;
	//GameInterface.TABLE_LIST.hr.height = 36;
	GameInterface.TABLE_LIST.hr.td1.str = MsgIS("Officer Items");
	GameInterface.TABLE_LIST.hr.td1.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td2.str = MsgIS("Weight");
	GameInterface.TABLE_LIST.hr.td2.scale = 0.9;
	//GameInterface.TABLE_LIST.hr.td3.str = XI_ConvertString("Price sell");
	//GameInterface.TABLE_LIST.hr.td3.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td4.str = MsgIS("Item name");
	GameInterface.TABLE_LIST.hr.td4.scale = 0.9;
	//GameInterface.TABLE_LIST.hr.td5.str = XI_ConvertString("Price buy");
	//GameInterface.TABLE_LIST.hr.td5.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td6.str = MsgIS("Items2");
	GameInterface.TABLE_LIST.hr.td6.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td7.str = MsgIS("Weight pcs");
	GameInterface.TABLE_LIST.hr.td7.scale = 0.9;

    FillCharactersScroll();

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	CreateString(true,"CharName","",FONT_NORMAL,COLOR_MONEY, 405,105,SCRIPT_ALIGN_CENTER,1.0);
	CreateString(true,"CharPos","",FONT_NORMAL,COLOR_MONEY, 405,55,SCRIPT_ALIGN_CENTER,1.0);
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

	SetFormatedText("STORECAPTION1", XI_ConvertString("titleExchangeItems"));
    SendMessage(&GameInterface,"lslls",MSG_INTERFACE_MSG_TO_NODE, "CB_TRADER", 1, 1, XI_ConvertString("FIST_CB_Hero"));
    SendMessage(&GameInterface,"lslls",MSG_INTERFACE_MSG_TO_NODE, "CB_BACKPACK", 1, 1, XI_ConvertString("FIST_CB_Officer"));
	SetNewPicture("OTHER_PICTURE", "interfaces\\portraits\\256\\face_" + its(refHeroChar.FaceId) + ".tga.tx");
}

void ProcessBreakExit()
{
	IDoExit( RC_INTERFACE_TO_ITEMS );
}

void ProcessCancelExit()
{
	if (bShowChangeWin)
	{
		EndTooltip();
	}
	else
	{
		IDoExit( RC_INTERFACE_TO_ITEMS );
	}
}

void IDoExit(int exitCode)
{
    //#20190210-01
    reCheckCrosshair(true);
    CheckAndSetOverloadMode(GetMainCharacter());
	int i, cn;
	//#20170318-20
    for(i=1;i<=MAX_NUM_FIGHTERS;i++)
	{
		cn = GetOfficersIndex(pchar, i);
		if (cn!=-1)
		{
			refCharacter = GetCharacter(cn);
            CheckAndSetOverloadMode(refCharacter);
			CharacterCheckEquipAll(refCharacter);
		}
	}
	for(i=0; i< NUM_REGULAR_OFFICERS; i++) {
        switch(i) {
            case 0:
				cn = sti(pchar.Fellows.Passengers.navigator);
			break;
			case 1:
				cn = sti(pchar.Fellows.Passengers.boatswain);
			break;
			case 2:
				cn = sti(pchar.Fellows.Passengers.cannoner);
			break;
			case 3:
				cn = sti(pchar.Fellows.Passengers.doctor);
			break;
			case 4:
				cn = sti(pchar.Fellows.Passengers.treasurer);
			break;
			case 5:
				cn = sti(pchar.Fellows.Passengers.carpenter);
			break;
        }
        if (cn!=-1)
		{
			refCharacter = GetCharacter(cn);
            CheckAndSetOverloadMode(refCharacter);
			CharacterCheckEquipAll(refCharacter);
		}
	}
	for(i=1;i<=COMPANION_MAX;i++)
	{
		cn = GetCompanionIndex(pchar, i);
		if (cn!=-1)
		{
			refCharacter = GetCharacter(cn);
            CheckAndSetOverloadMode(refCharacter);
			CharacterCheckEquipAll(refCharacter);
		}
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

	interfaceResultCommand = exitCode;
	EndCancelInterface(false);

	//PostEvent("LaunchIAfterFrame",1,"sl", "I_ITEMS", 1);
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
	int n, i;
	string row, sItem;
	int idLngFile;
	int leftQty, rightQty;
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	Table_Clear("TABLE_LIST", false, true, false);

	object allItems;
	aref arInventory, arItem;
	ref rItem;

	if (FIT_FilterState != FIT_HERO)
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

	if (FIT_FilterState != FIT_OFFICER)
	{
		makearef(arInventory, refHeroChar.Items);
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

        row = "tr" + n;
		leftQty  = GetCharacterFreeItem(refCharacter, sItem);
		rightQty = GetCharacterFreeItem(refHeroChar, sItem);

		if ((leftQty == 0) && (rightQty == 0)) continue;

		//// {*} BUHO-FIST - ADDED CODE - Filters at work.
		if (leftQty == 0 && FIT_FilterState == FIT_OFFICER) continue;
		if (rightQty == 0 && FIT_FilterState == FIT_HERO) continue;
		//// {*} BUHO END ADDITION

		GameInterface.TABLE_LIST.(row).id = sItem;
		GameInterface.TABLE_LIST.(row).td1.str = leftQty;
		GameInterface.TABLE_LIST.(row).td2.str = FloatToString(GetItemWeight(sItem) * sti(GameInterface.TABLE_LIST.(row).td1.str), 1);
		GameInterface.TABLE_LIST.(row).td4.icon.group = rItem.picTexture;
		GameInterface.TABLE_LIST.(row).td4.icon.image = "itm" + rItem.picIndex;
		GameInterface.TABLE_LIST.(row).td4.icon.offset = "3, 0";
		GameInterface.TABLE_LIST.(row).td4.icon.width = 32;
		GameInterface.TABLE_LIST.(row).td4.icon.height = 32;
		GameInterface.TABLE_LIST.(row).td4.textoffset = "31,0";
		GameInterface.TABLE_LIST.(row).td4.str = LanguageConvertString(idLngFile, rItem.name);
		GameInterface.TABLE_LIST.(row).td4.scale = 0.9;
		GameInterface.TABLE_LIST.(row).td6.str = rightQty;
		GameInterface.TABLE_LIST.(row).td7.str = FloatToString(GetItemWeight(sItem), 1);

		n++;
	}
	NextFrameRefreshTable();
	LanguageCloseFile(idLngFile);
}

void NextFrameRefreshTable()
{
	SetEventHandler("frame", "RefreshTableByFrameEvent", 0);
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
    Table_UpdateWindow(sControl);
}

void ChangePosTable()
{
}
//// {*} BUHO-FIST - REPLACEMENT - ShowHelpHint.
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
		sText1 = MsgIS("Team_filter_hint_1");
        sText3 = MsgIS("Team_filter_hint_2");
		sText2 = MsgIS("Team_filter_hint_3");
	}
	else
	{
        sHeader = XI_ConvertString("titleExchangeItems");
		sText1 = MsgIS("Trader_items_hint_1");
        sText3 = MsgIS("Trader_items_hint_2");
		sText2 = MsgIS("Trade_interface_hint_2");
	}
	CreateTooltip("#" + sHeader,
                  sText1, argb(255,255,255,255),
                  sText2, argb(255,192,192,192),
                  sText3, argb(255,255,255,255),
                  "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);
}
// {*} BUHO END REPLACEMENT

void EndTooltip()
{
	CloseTooltip();
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
	if (bShowChangeWin)
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

bool isExist(int checkThis)
{
    for(int i = 0; i < nCurrList; i++)
    {
        if(aList[i] == -1) return false;
        if(aList[i] == checkThis) return true;
    }
    return false;
}

void FillCharactersScroll()
{
	int i;
	string faceName;
	string attributeName;
	string PsgAttrName;
	int _curCharIdx;
	ref _refCurChar;
	aref pRef;

 	DeleteAttribute(&GameInterface, "CHARACTERS_SCROLL");

	nCurScrollNum = -1;
	GameInterface.CHARACTERS_SCROLL.current = 0;
	makearef(pRef,pchar.Fellows.Passengers);

	int nNotUsed = 3;
	GameInterface.CHARACTERS_SCROLL.ImagesGroup.t0 = "EMPTYFACE";

	FillFaceListEx("CHARACTERS_SCROLL.ImagesGroup", pchar, 0, false); // officers
	FillFaceListEx("CHARACTERS_SCROLL.ImagesGroup", pchar, 1, false); // companions
	FillFaceListEx("CHARACTERS_SCROLL.ImagesGroup", pchar, 2, false); // passengers

	GameInterface.CHARACTERS_SCROLL.BadTex1 = 0;
	GameInterface.CHARACTERS_SCROLL.BadPic1 = "emptyface";

	int m = 0;
	for(i=0; i<NUM_REGULAR_OFFICERS;i++)
	{
		switch(i)
		{
			case 0:
				PsgAttrName = "navigator";
			break;
			case 1:
				PsgAttrName = "boatswain";
			break;
			case 2:
				PsgAttrName = "cannoner";
			break;
			case 3:
				PsgAttrName = "doctor";
			break;
			case 4:
				PsgAttrName = "treasurer";
			break;
			case 5:
				PsgAttrName = "carpenter";
			break;
		}
		_curCharIdx = sti(pRef.(PsgAttrName));
		if(_curCharIdx!=-1 && _curCharIdx < MAX_CHARACTERS)
		{
		    if(isExist(_curCharIdx)) continue;
		    aList[nCurrList] = _curCharIdx;
		    aListPos[nCurrList] = PsgAttrName;
		    nCurrList++;
		    attributeName = "pic" + (m+1);
		    if(m == 0) refCharacter = &characters[_curCharIdx];
			GameInterface.CHARACTERS_SCROLL.(attributeName).character = _curCharIdx;
			GameInterface.CHARACTERS_SCROLL.(attributeName).img1 = GetFacePicName(GetCharacter(_curCharIdx));
			GameInterface.CHARACTERS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup","FACE128_"+Characters[_curCharIdx].FaceID);
			m++;
			nNotUsed--;
		}
	}
    //#20170318-20
	for(i=1; i<=MAX_NUM_FIGHTERS; i++)
	{
		_curCharIdx = GetOfficersIndex(pchar, i);
		if(_curCharIdx!=-1 && _curCharIdx < MAX_CHARACTERS)
		{
		    if(isExist(_curCharIdx)) continue;
		    aList[nCurrList] = _curCharIdx;
            aListPos[nCurrList] = "fighter";
		    nCurrList++;
		    if(m == 0) refCharacter = &characters[_curCharIdx];
			attributeName = "pic" + (m + 1);
            GameInterface.CHARACTERS_SCROLL.(attributeName).character = _curCharIdx;
            GameInterface.CHARACTERS_SCROLL.(attributeName).img1 = GetFacePicName(GetCharacter(_curCharIdx));
            GameInterface.CHARACTERS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup","FACE128_"+Characters[_curCharIdx].FaceID);
            m++;
            nNotUsed--;
		}
	}
	int iCompanionQuantity = getCompanionQuantity(pchar);
	if(iCompanionQuantity > 1)
	{
		for(i=1; i<=COMPANION_MAX; i++)
		{
		    _curCharIdx = GetCompanionIndex(pchar, i);
			if(_curCharIdx != -1 && _curCharIdx < MAX_CHARACTERS && !CheckAttribute(&characters[_curCharIdx], "isquest"))
			{
			    if(isExist(_curCharIdx)) continue;
                aList[nCurrList] = _curCharIdx;
                aListPos[nCurrList] = "companionship";
                nCurrList++;
				if(m == 0) refCharacter = &characters[_curCharIdx];
                attributeName = "pic" + (m + 1);
                GameInterface.CHARACTERS_SCROLL.(attributeName).character = _curCharIdx;
                GameInterface.CHARACTERS_SCROLL.(attributeName).img1 = GetFacePicName(GetCharacter(_curCharIdx));
                GameInterface.CHARACTERS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup","FACE128_"+Characters[_curCharIdx].FaceID);
                m++;
                nNotUsed--;
			}
		}
	}
	if(nNotUsed < 0) nNotUsed = 0;
	GameInterface.CHARACTERS_SCROLL.NotUsed = nNotUsed;
	GameInterface.CHARACTERS_SCROLL.ListSize = m;
}

void SetVariable()
{
	string sText, sTextSecond;

	iCharCapacity = GetMaxItemsWeight(refCharacter);
	sText  = FloatToString(fCharWeight, 1) + " / " + iCharCapacity;
	SetFormatedText("CAPACITY", XI_ConvertString("Weight") + ":\n" + sText);

	iTotalSpace = iMaxGoodsStore;
	string sMaxGoodsStore;
    sMaxGoodsStore = MsgIS("Hero");
	SetFormatedText("STORE_CAPACITY", sMaxGoodsStore);

	sText = XI_ConvertString("OurMoney") + " " + FormatMoneyString(sti(pchar.money));
	SetFormatedText("OUR_GOLD", sText);
}

void ProcessFrame()
{
    int idxChar = -1;
	if(sti(GameInterface.CHARACTERS_SCROLL.current) != nCurScrollNum && GetCurrentNode() == "CHARACTERS_SCROLL")
	{
        XI_WindowDisable("QTY_WINDOW", true);
		XI_WindowShow("QTY_WINDOW", false);
		nCurScrollNum = sti(GameInterface.CHARACTERS_SCROLL.current);
		string sAttr = "pic" + (nCurScrollNum + 1);
		idxChar = sti(GameInterface.CHARACTERS_SCROLL.(sAttr).character);
		//#20190528-01
		if(idxChar < 0 || idxChar >= MAX_CHARACTERS) return;
		refCharacter = &characters[idxChar];
		if(refCharacter.id == "0") return;
		SetDescription();
		//FillEquipInfo();
		FillCharacterInfo();
		GameInterface.TABLE_LIST.select = 1;
		GameInterface.TABLE_LIST.top = 0;
	}
}
void FillCharacterInfo()
{
    SetNewPicture("MAIN_CHARACTER_PICTURE", "interfaces\\portraits\\256\\face_" + refCharacter.FaceId + ".tga.tx");
	GameInterface.strings.CharName = GetFullName(refCharacter);
	GameInterface.strings.CharPos = XI_ConvertString(aListPos[sti(GameInterface.CHARACTERS_SCROLL.current)]);
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

void ShowGoodsInfo(string sItemID)
{
	sCurItem = sItemID;
	int iGoodIndex = FindItem(sCurItem);
	ref    arItm = &Items[iGoodIndex];
	string GoodName = arItm.name;
	int    lngFileID = LanguageOpenFile("ItemsDescribe.txt");
	string sHeader = LanguageConvertString(lngFileID, GoodName);

    string describeStr = "";

    if (bBettaTestMode)
	{
	    describeStr += " id = " + sCurItem + NewStr();
	}
	describeStr += GetItemDescribe(iGoodIndex);

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
	iStoreQty = GetCharacterFreeItem(refHeroChar, sCurItem);

	SetFormatedText("QTY_INFO_STORE_QTY", its(iStoreQty));
	SetFormatedText("QTY_INFO_SHIP_QTY", its(iCharQty));
	BuyOrSell = 0;
}

//// {*} BUHO-FIST - ADDED CODE - Checkboxes processing function.
void ProcessFilter(string sButton)
{
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
		if (FIT_FilterState != FIT_OFFICER)
		{
			// Button being selected.
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_ALL", 2, 1, 0);
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_TRADER", 2, 1, 0);
			FIT_FilterState = FIT_OFFICER;
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
		if (FIT_FilterState != FIT_HERO)
		{
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_BACKPACK", 2, 1, 0);
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CB_ALL", 2, 1, 0);
			FIT_FilterState = FIT_HERO;
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
		TakeNItems(refHeroChar, sCurItem, -nTradeQuantity);
		TakeNItems(refCharacter, sCurItem, nTradeQuantity);
	}
 	else
	{ // SELL
	    TakeNItems(refHeroChar, sCurItem, nTradeQuantity);
	    TakeNItems(refCharacter, sCurItem, -nTradeQuantity);
	}
	//#20200218-01
    if(CheckAttribute(&Items[FindItem(sCurItem)], "shown"))
        Items[FindItem(sCurItem)].shown = false;
	AddToTable();
	EndTooltip();
	ShowGoodsInfo(sCurItem);
}

void confirmChangeQTY_EDIT()
{
	ChangeQTY_EDIT();
    SetCurrentNode("QTY_OK_BUTTON");
}

void ChangeQTY_EDIT()
{
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
		    if (sti(GameInterface.qty_edit.str) > iCharQty)
		    {
		        GameInterface.qty_edit.str = iCharQty;
		    }
		    iWeight = (fWeight * sti(GameInterface.qty_edit.str));
		    if ((fStoreWeight + iWeight) > iTotalSpace)
		    {
		        iWeight = iTotalSpace - fStoreWeight - 0.01;
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight );
		        iWeight = fWeight * sti(GameInterface.qty_edit.str);
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight );
		    }
		    if (IsQuestUsedItem(sCurItem))
		    {
		        GameInterface.qty_edit.str = 0;
		    }
		    SetFormatedText("QTY_TypeOperation", MsgIS("Give"));
		    //SetFormatedText("QTY_Result", MsgIS("Gold") +" " + makeint(iStorePrice*stf(GameInterface.qty_edit.str) + 0.5) +
			//                MsgIS("__weight") +" " + FloatToString(iWeight, 1) );
		}
		else
		{
			BuyOrSell = 1;
		    if (sti(GameInterface.qty_edit.str) > iStoreQty)
		    {
		        GameInterface.qty_edit.str = iStoreQty;
		    }
		    iWeight = (fWeight * sti(GameInterface.qty_edit.str));
		    if ((fCharWeight + iWeight) > iCharCapacity)
		    {
		        iWeight = iCharCapacity - fCharWeight - 0.01;
				if (iWeight < 0) iWeight = 0;
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight );
		        iWeight = fWeight * sti(GameInterface.qty_edit.str);
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight );
		    }
            if (IsQuestUsedItem(sCurItem))
		    {
		        GameInterface.qty_edit.str = 0;
		    }
			SetFormatedText("QTY_TypeOperation", MsgIS("Take"));
			//SetFormatedText("QTY_Result", MsgIS("Gold") + " " + makeint(iCharPrice*stf(GameInterface.qty_edit.str) + 0.5) +
			//                MsgIS("__weight")+ " " + FloatToString(iWeight, 1) );
		}
	}
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

void REMOVE_ALL_BUTTON()
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

void ADD_ALL_BUTTON()
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

void REMOVE_BUTTON()
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

void ADD_BUTTON()
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
