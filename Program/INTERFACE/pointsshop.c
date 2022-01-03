bool bShowChangeWin = false;
int item_price, iCurGoodsIdx;
float fWeight;
float rate = 1500.0;

void InitInterface(string iniName) {
    StartAboveForm(true);

	GameInterface.TABLE_LIST.hr.td1.str = "Наименование предметов";
	GameInterface.TABLE_LIST.hr.td1.scale = 0.9;

	GameInterface.TABLE_LIST.hr.td2.str = "Цена";
	GameInterface.TABLE_LIST.hr.td2.scale = 0.9;

	GameInterface.TABLE_LIST.hr.td3.str = "Вес шт.";
	GameInterface.TABLE_LIST.hr.td3.scale = 0.9;

	SendMessage(&GameInterface, "ls", MSG_INTERFACE_INIT, iniName);

	AddToTable();

	ShowGoodsInfo(sti(GameInterface.TABLE_LIST.tr1.index));
	SetFormatedText("OUR_GOLD", "Очков достижений: " + sti(pchar.ach_points));

	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "INFO_TEXT", 5);

	SetEventHandler("InterfaceBreak", "ProcessBreakExit", 0);
	SetEventHandler("exitCancel", "ProcessCancelExit", 0);
	SetEventHandler("ievnt_command", "ProcCommand", 0);
	SetEventHandler("evntDoPostExit", "DoPostExit", 0);

	SetEventHandler("OnTableClick", "OnTableClick", 0);
	SetEventHandler("MouseRClickUP", "EndTooltip", 0);
	SetEventHandler("ShowItemInfo", "ShowItemInfo", 0);
	SetEventHandler("TableSelectChange", "CS_TableSelectChange", 0);
	SetEventHandler("TransactionOK", "TransactionOK", 0);
	SetEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT", 0);

	SetEventHandler("ADD_BUTTON", "ADD_BUTTON", 0);
	SetEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON", 0);

	SetEventHandler("frame", "ProcessFrame", 1);

	SetFormatedText("STORECAPTION1", "Обмен очков достижений");
}

void TransactionOK() {
	confirmChangeQTY_EDIT();

	if (sti(GameInterface.qty_edit.str) > 0) {
		// PlaySound("Craft\ui_enchanting_learneffect_01.WAV");
		Log_Info("Потрачено " + (item_price * sti(GameInterface.qty_edit.str)) + " очков достижений");
		pchar.ach_points = sti(pchar.ach_points) - item_price * sti(GameInterface.qty_edit.str);
		TakeNItems(pchar, Items[iCurGoodsIdx].id, sti(GameInterface.qty_edit.str));
	}

	EndTooltip();
	ShowGoodsInfo(iCurGoodsIdx);
}

void ChangePosTable() {}

void ProcessFrame() {}

void OnTableClick() {
	string sControl = GetEventData();
	int iRow = GetEventData();
	int iColumn = GetEventData();
	string sRow = "tr" + (iRow + 1);

    Table_UpdateWindow(sControl);
}

void EndTooltip() {
	CloseTooltip();
    GameInterface.qty_edit.str = 0;

	SetFormatedText("OUR_GOLD", "Очков достижений: " + sti(pchar.ach_points));
	SetCurrentNode("TABLE_LIST");

 	XI_WindowDisable("QTY_WINDOW", true);
	XI_WindowShow("QTY_WINDOW", false);

	bShowChangeWin = false;
}

void CS_TableSelectChange() {
	string sControl = GetEventData();
	int iSelected = GetEventData();
    string sRow = "tr" + (iSelected);

	SetFormatedText("OUR_GOLD", "Очков достижений: " + sti(pchar.ach_points));
    ShowGoodsInfo(sti(GameInterface.TABLE_LIST.(sRow).index));
}

void ShowGoodsInfo(int iGoodIndex) {
	string GoodName = Items[iGoodIndex].name;
	ref    arItm = &Items[iGoodIndex];
	int    lngFileID = LanguageOpenFile("ItemsDescribe.txt");
	string sHeader = LanguageConvertString(lngFileID, GoodName);

    iCurGoodsIdx = iGoodIndex;

    string describeStr = GetItemDescribe(FindItem(Items[iGoodIndex].id));
	fWeight = stf(Items[iGoodIndex].weight);

    GameInterface.qty_edit.str = 0;
	item_price = GetItemPrice(iGoodIndex);
	ChangeQTY_EDIT();

	SetNewGroupPicture("QTY_GOODS_PICTURE", Items[iCurGoodsIdx].picTexture, "itm" + Items[iCurGoodsIdx].picIndex);
    SetFormatedText("QTY_CAPTION", sHeader);
    SetFormatedText("QTY_GOODS_INFO", describeStr);
	LanguageCloseFile(lngFileID);
}

void AddToTable() {
	int n = 1;
	int i = 0;
	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	string row;

	Table_Clear("TABLE_LIST", false, true, false);

	for (i = 0; i < ITEMS_QUANTITY; i++) {
        row = "tr" + n;

		if (CheckAttribute(&Items[i], "points_shop")) {
			GameInterface.TABLE_LIST.(row).td1.icon.group = Items[i].picTexture;
			GameInterface.TABLE_LIST.(row).td1.icon.image = "itm" + Items[i].picIndex;
			GameInterface.TABLE_LIST.(row).td1.icon.offset = "-2,0";
			GameInterface.TABLE_LIST.(row).td1.icon.width = 64;
			GameInterface.TABLE_LIST.(row).td1.icon.height = 64;
			GameInterface.TABLE_LIST.(row).td1.textoffset = "31,0";
			GameInterface.TABLE_LIST.(row).td1.str = LanguageConvertString(idLngFile, Items[i].name);
			GameInterface.TABLE_LIST.(row).td1.scale = 0.9;

			GameInterface.TABLE_LIST.(row).td2.str = GetItemPrice(i);
			GameInterface.TABLE_LIST.(row).td3.str = FloatToString(stf(Items[i].Weight), 1);

			GameInterface.TABLE_LIST.(row).index = i;
			n++;
		}
	}

	NextFrameRefreshTable();
	LanguageCloseFile(idLngFile);
}

int GetItemPrice(int itmIdx) {
	int itmprice = 0;

	if (itmIdx < 0 || itmIdx > ITEMS_QUANTITY)
		return 0;

	if (CheckAttribute(&Items[itmIdx], "points_shop"))
		itmprice = sti(Items[itmIdx].points_shop);

	return itmprice;
}

void ProcessBreakExit() {
	IDoExit(RC_INTERFACE_FOOD_INFO_EXIT);
}

void ProcessCancelExit() {
	if (bShowChangeWin)
		EndTooltip();
	else IDoExit(RC_INTERFACE_FOOD_INFO_EXIT);
}

void ProcCommand() {
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName) {
		case "QTY_OK_BUTTON":
			if(comName=="leftstep")
				ADD_BUTTON();

			if(comName=="rightstep")
				REMOVE_BUTTON();
			break;

		case "QTY_CANCEL_BUTTON":
			if(comName=="leftstep")
				ADD_BUTTON();

			if(comName=="rightstep")
				REMOVE_BUTTON();
			break;

		case "TABLE_LIST":
			if(comName=="leftstep")
				ADD_BUTTON();

			if(comName=="rightstep")
				REMOVE_BUTTON();
			break;
	}
}

void DoPostExit() {
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void IDoExit(int exitCode) {
	CheckAndSetOverloadMode(GetMainCharacter());
	EndAboveForm(true);

	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");

	DelEventHandler("OnTableClick", "OnTableClick");
	DelEventHandler("MouseRClickUP","EndTooltip");
	DelEventHandler("ShowItemInfo", "ShowItemInfo");
	DelEventHandler("TableSelectChange", "CS_TableSelectChange");
	DelEventHandler("frame","ProcessFrame");
	DelEventHandler("TransactionOK", "TransactionOK");
	DelEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT");

	DelEventHandler("ADD_BUTTON","ADD_BUTTON");
	DelEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON");

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
}

void NextFrameRefreshTable() {
	SetEventHandler("frame", "RefreshTableByFrameEvent", 0);
}

void RefreshTableByFrameEvent() {
	DelEventHandler("frame", "RefreshTableByFrameEvent");
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE,"TABLE_LIST", 0);
}

void REMOVE_BUTTON() {
    if (!bShowChangeWin)
		return;

	GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) + 1);
	ChangeQTY_EDIT();
}

void ADD_BUTTON() {
    if (!bShowChangeWin)
		return;

	GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) - 1);
	ChangeQTY_EDIT();
}

void ShowItemInfo() {
	if (bShowChangeWin) {
	    TransactionOK();
	} else {
		GameInterface.qty_edit.str = 0;
		ChangeQTY_EDIT();

		XI_WindowDisable("QTY_WINDOW", false);
		XI_WindowShow("QTY_WINDOW", true);
		bShowChangeWin = true;
	}
}

void confirmChangeQTY_EDIT() {
	ChangeQTY_EDIT();
    SetCurrentNode("QTY_OK_BUTTON");
}

void ChangeQTY_EDIT() {
	float iWeight;

	if (sti(GameInterface.qty_edit.str) < 0)
		GameInterface.qty_edit.str = 0;

	if (item_price * sti(GameInterface.qty_edit.str) > sti(pchar.ach_points))
		GameInterface.qty_edit.str = makeint(sti(pchar.ach_points) / item_price);

	iWeight = fWeight * sti(GameInterface.qty_edit.str);

	SetFormatedText("QTY_TypeOperation", "Обменять");
	SetFormatedText("QTY_Result", "Очков за единицу: " + (item_price) + NewStr() + "Сумма: " + (item_price * sti(GameInterface.qty_edit.str)) +
		", вес: " + FloatToString(iWeight, 1));

    SetFormatedText("OUR_GOLD", "Очков достижений: " + sti(pchar.ach_points));
}
