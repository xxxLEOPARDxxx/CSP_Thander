//////////////////////////
// 		CSP 2.2.0+		//
//////////////////////////

string totalInfo = "";
string CurTable, CurRow;
string sMessageMode;
ref chr;

int iSelected; // курсор в таблице

int lastsort = 0;
bool blastsort;

void InitInterface(string iniName)
{
 	StartAboveForm(true);

    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	if (!CheckAttribute(pchar, "PGG_killed"))
	{
		pchar.PGG_killed = 0;
	}
	if (!CheckAttribute(pchar, "PGG_NotKilled"))
	{
		pchar.PGG_NotKilled = 0;
	}

    SetFormatedText("MAP_CAPTION", XI_ConvertString("titlePsHero") + " (" + (PsHeroQty - sti(pchar.PGG_killed) - sti(pchar.PGG_NotKilled))+ " / " + (PsHeroQty - sti(pchar.PGG_NotKilled)) + ")");
	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("MouseRClickUp","HideInfoWindow",0);
	SetEventHandler("TableSelectChange", "TableSelectChange", 0);
	SetEventHandler("OnTableClick", "OnTableClick", 0);
	SetEventHandler("ShowPGGInfo","ShowPGGInfo",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0); // выход из интерфейса
	sMessageMode = "";
	FillTable();
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
    EndAboveForm(true);
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("MouseRClickUp","HideInfoWindow");
	DelEventHandler("TableSelectChange", "TableSelectChange");
	DelEventHandler("OnTableClick", "OnTableClick");
	DelEventHandler("ShowPGGInfo","ShowPGGInfo");
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

	}
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}


void FillTable()
{
	ref chr;
	int i, n;
	string row;
	int iS,iP,iE,iC,iI,iA,iL;

	n = 1;
	// шапка -->
    GameInterface.TABLE_HERO.select = 0;
    GameInterface.TABLE_HERO.hr.td1.str = "Фото";
    GameInterface.TABLE_HERO.hr.td1.scale = 1.0;
    GameInterface.TABLE_HERO.hr.td2.str = "Имя";
    GameInterface.TABLE_HERO.hr.td2.scale = 1.0;
	GameInterface.TABLE_HERO.hr.td3.str = "Ранг";
	GameInterface.TABLE_HERO.hr.td3.scale = 1.0;
	GameInterface.TABLE_HERO.hr.td4.str = "Нация";
	GameInterface.TABLE_HERO.hr.td4.scale = 1.0;
	GameInterface.TABLE_HERO.hr.td5.str = "Корабль";
	GameInterface.TABLE_HERO.hr.td5.scale = 1.0;
	GameInterface.TABLE_HERO.hr.td6.str = "Местоположение";
	GameInterface.TABLE_HERO.hr.td6.scale = 1.0;
	GameInterface.TABLE_HERO.hr.td7.str = "P.I.R.A.T.E.S.";
	GameInterface.TABLE_HERO.hr.td7.scale = 1.0;
	GameInterface.TABLE_HERO.hr.td8.str = "Репутация";
	GameInterface.TABLE_HERO.hr.td8.scale = 1.0;
	GameInterface.TABLE_HERO.hr.td9.str = "Отношение";
	GameInterface.TABLE_HERO.hr.td9.scale = 1.0;
	GameInterface.TABLE_HERO.hr.td10.str = "Пиастры";
	GameInterface.TABLE_HERO.hr.td10.scale = 1.0;

	for (i = 1; i <= PsHeroQty; i++)
	{
		chr = CharacterFromID("PsHero_" + i);
		if(!CharacterIsDead(chr))
		{
			if(chr.PGGAi.IsPGG != false)
			{
				row = "tr" + n;
				GameInterface.TABLE_HERO.(row).index = i;
				GameInterface.TABLE_HERO.(row).td1.icon.texture = "INTERFACES\PORTRAITS\128\face_" + chr.faceId + ".tga";
				GameInterface.TABLE_HERO.(row).td1.icon.uv = "0,0,1,1";
				GameInterface.TABLE_HERO.(row).td1.icon.width = 40;
				GameInterface.TABLE_HERO.(row).td1.icon.height = 40;
				GameInterface.TABLE_HERO.(row).td1.icon.offset = "-2, -1";
				GameInterface.TABLE_HERO.(row).td1.scale = 0.8;
				GameInterface.TABLE_HERO.(row).td2.str = GetFullName(chr);
				GameInterface.TABLE_HERO.(row).td2.scale = 0.8;
				GameInterface.TABLE_HERO.(row).td3.str = chr.rank;
				GameInterface.TABLE_HERO.(row).td3.scale = 1.0;
				GameInterface.TABLE_HERO.(row).td4.str = chr.nation;
				GameInterface.TABLE_HERO.(row).td4.icon.group  = "NATIONS";
				GameInterface.TABLE_HERO.(row).td4.icon.image  = Nations[sti(chr.nation)].Name;
				GameInterface.TABLE_HERO.(row).td4.icon.width  = 40;
				GameInterface.TABLE_HERO.(row).td4.icon.height = 40;
				GameInterface.TABLE_HERO.(row).td4.icon.offset = "4, 0";
				GameInterface.TABLE_HERO.(row).td4.scale = 0;

				if (GetCharacterShipType(chr) != SHIP_NOTUSED)
				{
					GameInterface.TABLE_HERO.(row).td5.str = XI_ConvertString(RealShips[GetCharacterShipType(chr)].BaseName);
					GameInterface.TABLE_HERO.(row).td5.scale = 0.8;
				}
				else
				{
					GameInterface.TABLE_HERO.(row).td5.str = "Нет корабля";
					GameInterface.TABLE_HERO.(row).td5.scale = 0.8;
				}
				if (!CheckAttribute(chr, "PGGAi.Task.SetSail"))
				{
					GameInterface.TABLE_HERO.(row).td6.str = XI_ConvertString("Colony"+chr.PGGAi.location.town);
				}
				else
				{
					if (CheckAttribute(chr, "PGG_warrior"))
					{
						GameInterface.TABLE_HERO.(row).td6.str = "Охотится на вас");
					}
					else
					{
						GameInterface.TABLE_HERO.(row).td6.str = "Плывет в "+ XI_ConvertString("Colony" + chr.PGGAi.Task.Target + "Acc");
					}
					if (CheckAttribute(chr, "PGG_trader"))
					{
						GameInterface.TABLE_HERO.(row).td6.str = "Сопровождает торговца в "+ XI_ConvertString("Colony" + chr.PGGAi.Task.Target + "Acc");
					}
					if (CheckAttribute(chr, "PGGAi.DontUpdate"))
					{
						GameInterface.TABLE_HERO.(row).td6.str = "Неизвестно");
					}
				}
				GameInterface.TABLE_HERO.(row).td6.scale = 0.8;
				iS = sti(chr.SPECIAL.Strength);
				iP = sti(chr.SPECIAL.Perception);
				iA = sti(chr.SPECIAL.Agility);
				iC = sti(chr.SPECIAL.Charisma);
				iI = sti(chr.SPECIAL.Intellect);
				iE = sti(chr.SPECIAL.Endurance);
				iL = sti(chr.SPECIAL.Luck);
				GameInterface.TABLE_HERO.(row).td7.str = "" + (iS+iP+iE+iC+iI+iA+iL) + " | "+iS+" "+iP+" "+iA+" "+iC+" "+iI+" "+iE+" "+iL;
				GameInterface.TABLE_HERO.(row).td7.scale = 0.8;
				GameInterface.TABLE_HERO.(row).td8.str = ""+makeint(chr.reputation);
				GameInterface.TABLE_HERO.(row).td8.scale = 0.8;
				GameInterface.TABLE_HERO.(row).td9.str = ""+PGG_ChangeRelation2MainCharacter(chr, 0);
				GameInterface.TABLE_HERO.(row).td9.scale = 0.8;
				GameInterface.TABLE_HERO.(row).td10.str = ""+chr.Money;
				GameInterface.TABLE_HERO.(row).td10.scale = 0.8;
				n++;
			}
		}
	}
	Table_UpdateWindow("TABLE_HERO");
}

void TableSelectChange()
{
	string sControl = GetEventData();
	iSelected = GetEventData();
    CurTable = sControl;
    CurRow   =  "tr" + (iSelected);
}

void ShowPGGInfo()
{
	if (CheckAttribute(&GameInterface, CurTable + "." + CurRow + ".index"))
	{ // нет ПГГ в списке
	chr = CharacterFromID("PsHero_" + GameInterface.TABLE_HERO.(CurRow).index);
	SetSPECIALMiniTable("TABLE_SMALLSKILL", chr);
	SetOTHERMiniTable("TABLE_SMALLOTHER", chr);
	SetFormatedText("OFFICER_NAME", GetFullName(chr));
	SetNewPicture("CHARACTER_BIG_PICTURE", "interfaces\portraits\256\face_" + chr.faceId + ".tga");
	SetNewPicture("CHARACTER_FRAME_PICTURE", "interfaces\Frame3.tga");

	string texturedata;
	if (IsCharacterPerkOn(chr, "Grunt")) texturedata = "INTERFACES\Sith\Char_Master.tga";
	if (IsCharacterPerkOn(chr, "Trader")) texturedata = "INTERFACES\Sith\Char_Merchant.tga";
	if (IsCharacterPerkOn(chr, "Fencer")) texturedata = "INTERFACES\Sith\Char_Corsair.tga";
	if (IsCharacterPerkOn(chr, "Adventurer")) texturedata = "INTERFACES\Sith\Char_Adventurer.tga";
	if (IsCharacterPerkOn(chr, "Buccaneer")) texturedata = "INTERFACES\Sith\Char_Inquisitor.tga";
	if (IsCharacterPerkOn(chr, "Agent")) texturedata = "INTERFACES\Sith\Char_SecretAgent.tga";
	if (IsCharacterPerkOn(chr, "SeaWolf")) texturedata = "INTERFACES\Sith\Char_SeaWolf.tga";
	SetNewPicture("CHARACTER_PROFESSION", texturedata);

	XI_WindowShow("RPG_WINDOW", true);
	XI_WindowDisable("RPG_WINDOW", false);
	sMessageMode = "RPG_Hint";
	}
}

void ExitRPGHint()
{
	if (sMessageMode == "RPG_Hint")
	{
		XI_WindowShow("RPG_WINDOW", false);
		XI_WindowDisable("RPG_WINDOW", true);
		sMessageMode = "";
	}
}

void HideInfoWindow()
{
	CloseTooltip();
	ExitRPGHint();
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
		if (iColumn == 1) return;//эти колонки не сортируем

		if (lastsort == iColumn) {bLastSort = !bLastSort;} else {lastsort = iColumn; bLastSort = 1;}//запоминаем сортировку и меняем направление сортировки, если это повторный клик по колонке
//todo - разобраться, как заблокировать активацию двойного клика на заголовке - подменять его на ординарные как-то
//todo - устанавливать стрелочку направления сортировки по запомненным значениям переменных - но тут нужно как-то узнавать ширину колонок таблицы, чтобы пересчитать координаты???
//todo - не забыть, что может быть несколько таблиц на одном интерфейсе - надо ещё и последнюю таблицы запоминать и сбрасывать(?) сортировку при смене или запоминать для каждой?

		if (iColumn == 3 || iColumn == 4 || iColumn == 8 || iColumn == 9 || iColumn == 10)
			SortTable(sControl, iColumn, 0, !bLastSort, -1);//числа		//работает и без указания числа строк, вроде бы
		else
			SortTable(sControl, iColumn, 1, bLastSort, -1);//текст
		}
//вызывать направление сортировки разными действиями - ЛКМ/ПКМ??
//<-- mod tablesort
	Table_UpdateWindow(sControl);
}
