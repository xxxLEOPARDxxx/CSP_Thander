
#define MAX_MAPS 32
object ColonyList[MAX_COLONIES];
int playership_x, playership_z;
int MapList[MAX_MAPS];
int CurMap;
int MapCount;
int CurZoom;
object submaps;
int LastMainMap;

void InitInterface(string iniName)
{
  GameInterface.title = "titlePaperMap";

	string sColony, sPic;
	int x, y;

	for(int i = 0; i < MAX_COLONIES; i++)
	{
		sColony = colonies[i].id;
		x = sti(colonies[i].map.x);
		y = sti(colonies[i].map.y);
		if(colonies[i].nation != "none")
		{
			sPic = GetNationNameByType(sti(colonies[i].nation));
		}
		else
		{
			sPic = "select_nation";
		}
		if(sColony == "IslaMona")
		{
			sPic = "Pirate";
		}

		if(sPic != "select_nation")
		{
			GameInterface.MAP.imagelist.(sColony).group = "MAIN_ICONS";
			GameInterface.MAP.imagelist.(sColony).x = x;
			GameInterface.MAP.imagelist.(sColony).y = y;
			GameInterface.MAP.imagelist.(sColony).pic = sPic;
			GameInterface.MAP.imagelist.(sColony).width = 12;
			GameInterface.MAP.imagelist.(sColony).height = 12;
		}
	}

	x = sti(worldMap.playerShipX)/1.66;
	x = 1024 + x - 5;
	y = sti(worldMap.playerShipZ)/1.66;
	y = 1024 - y - 5;

	GameInterface.MAP.imagelist.PShip.group = "FRENDLY";
	GameInterface.MAP.imagelist.PShip.x = x;
	GameInterface.MAP.imagelist.PShip.y = y;
	GameInterface.MAP.imagelist.PShip.pic = "frendly";
	GameInterface.MAP.imagelist.PShip.width = 32;
	GameInterface.MAP.imagelist.PShip.height = 32;

	GameInterface.MAP.centerx = x;
	GameInterface.MAP.centery = y;

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	CreateString(true,"MapsListCaption",XI_ConvertString("MapsList"),FONT_CAPTION,COLOR_NORMAL,714,47,SCRIPT_ALIGN_CENTER,0.9);

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);
	SetEventHandler("TableSelectChange", "TableSelectChange", 0);
	SetEventHandler("SelectIsland", "SelectIsland", 0);
	SetEventHandler("BackToMainMap", "BackToMainMap", 0);
	SetEventHandler("ZoomToggle", "ZoomToggle", 0);
	SetEventHandler("SelectRColony","SelectRColony",0);
	SetEventHandler("MouseRClickUP", "HideRColony",0);


	GetMapList();
	UpdateMapList();
	CurMap = 0;
	CurZoom = 1;
	showmap();
}

void ProcessBreakExit()
{
	IDoExit(RC_INTERFACE_PAPER_MAP);
}

void ProcessCancelExit()
{
	IDoExit(RC_INTERFACE_PAPER_MAP);
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");
	DelEventHandler("SelectRColony","SelectRColony");
	DelEventHandler("MouseRClickUP", "HideRColony");
	DelEventHandler("TableSelectChange", "TableSelectChange");
	DelEventHandler("SelectIsland", "SelectIsland");
	DelEventHandler("BackToMainMap", "BackToMainMap");
	DelEventHandler("ZoomToggle", "ZoomToggle");

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
}

void ProcCommand()
{
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void TableSelectChange()
{
	string sControl = GetEventData();
	CurMap = GetEventData() - 1;
	if (CurZoom == 2) CurZoom = 0;
	showmap();
}

void ZoomToggle() {
	//used to disable select island function if zoomed.
	CurZoom = CurZoom + 1;
	if (CurZoom > 2) CurZoom = 1;
	NoMapMsg(false);
}

void GetMapList() {
	aref submap;
	int j;
	int submapcount;
	ref submapsref;

		for (j=0; j<MAX_MAPS; j++) {
		MapList[j] = -1;
	}

	MapCount = 0;

	if(AnyoneHaveMap("map_good")) {
		MapList[MapCount] = FindItem("map_good");
		MapCount++;
	}
	if(AnyoneHaveMap("map_normal")) {
		MapList[MapCount] = FindItem("map_normal");
		MapCount++;
	}
	if(AnyoneHaveMap("map_bad")) {
		MapList[MapCount] = FindItem("map_bad");
		MapCount++;
	}
	//Get other maps

	InitSubMaps();
	makeref(submapsref, submaps);
	submapcount = GetAttributesNum(submapsref);
	for (j=0; j<submapcount; j++) {
		submap = GetAttributeN(submapsref, j);
		if(AnyoneHaveMap(submap.map)) {
			MapList[MapCount] = FindItem(submap.map);
			MapCount++;
		}
	}

}

bool AnyoneHaveMap(string mapid) {
	if (HaveMap(1,mapid)) return true; //player
	if (HaveMap(sti(pchar.Fellows.Passengers.navigator), mapid)) return true;
	//Boyer mod
	/* if (HaveMap(GetOfficersIndex(pchar,1),mapid)) return true;
	if (HaveMap(GetOfficersIndex(pchar,2),mapid)) return true;
	if (HaveMap(GetOfficersIndex(pchar,3),mapid)) return true; */
	for(int i = 1;i<=MAX_NUM_FIGHTERS;i++){
		if (HaveMap(GetOfficersIndex(pchar,i),mapid)) return true;
	}
	//End Boyer mod
	return false;
}

bool HaveMap(int charIdx, string mapid) {
	if (charIdx == -1) {
		return false;
	}
	if( CheckAttribute(Characters[charIdx],"Items."+mapid) && sti(Characters[charIdx].Items.(mapid))>0)
		{return true;}
	return false;
}

int FoundMap(int mapidx) {
	for (int j=0; j<MAX_MAPS; j++) {
		if(MapList[j] == mapidx) {
			return j;
		}
	}
	return -1;
}

void UpdateMapList() {
	string row;

	i = 1;
	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	for (int j=0; j<MAX_MAPS; j++) {
		if(MapList[j] != -1) {
			row = "tr" + i;
			i++;
			GameInterface.MAPS_LIST.(row).td1.fontidx = 0;
			GameInterface.MAPS_LIST.(row).td1.textoffset = "10,0";
			GameInterface.MAPS_LIST.(row).td1.hlineheight = 0;
			GameInterface.MAPS_LIST.(row).td1.str = LanguageConvertString(idLngFile, Items[MapList[j]].name);
			GameInterface.MAPS_LIST.(row).td1.scale = 0.65;
			GameInterface.MAPS_LIST.(row).td1.color = argb(255,240,230,156);
		}
	}
	Table_UpdateWindow("MAPS_LIST");
}

void showmap() {
	//#20200320-01
    if(MapCount < 1) return;
	if (CurZoom > 2) {
		//fix for swapping maps at zoom, confuses what zoom you're at
		CurZoom = 1;
	}
	string sMap;

	if (CurMap == -1) {
		sMap = "no_map"; //shouldn't get this...
	} else {
		sMap = Items[MapList[CurMap]].imageTga;
	}
	if (CurMap == -1 || Items[MapList[CurMap]].id == "map_good" || Items[MapList[CurMap]].id == "map_normal" || Items[MapList[CurMap]].id == "map_bad") {
		LastMainMap = CurMap;
		//using three map objects with different scales and button responses for different maps
		SetNewPicture("MAP1", "interfaces\Maps\"+ sMap + "QM.tga.tx");      //"set map
		SetNodeUsing("MAP1",  true);
		SetNodeUsing("MAP2",  false);
	} else {
		SetNewPicture("MAP2", "interfaces\Maps\"+ sMap + ".tga.tx");      //"set map
		SetNodeUsing("MAP1",  false);
		SetNodeUsing("MAP2",  true);
	}
	Table_UpdateWindow("MAPS_LIST");
	NoMapMsg(false);
}

void BackToMainMap()
{
	GameInterface.MAPS_LIST.select = LastMainMap + 1;
	CurMap = LastMainMap;
	showmap();
}

void SelectIsland()
{

	aref submap;
	int j;
	int submapcount;
	ref submapsref;
	makeref(submapsref, submaps);

	if (sti(CurZoom) == 2) {
		return;
	}

	float fMouseX = stf(GameInterface.mousepos.x);
	float fMouseY = stf(GameInterface.mousepos.y);

	//scale click position to match new "map_good"
	if (Items[MapList[CurMap]].id == "map_good") {
		fMouseX = 1.18 * fMouseX - 55;
		fMouseY = 1.15 * fMouseY - 65;
	}


	NoMapMsg(false);

	submapcount = GetAttributesNum(submapsref);
	for (j=0; j<submapcount; j++) {
		submap = GetAttributeN(submapsref, j);
		if (fMouseX > sti(submap.x1) && fMouseX < sti(submap.x2) && fMouseY > sti(submap.y1) && fMouseY < sti(submap.y2)) {
			int NewMap = FoundMap(FindItem(submap.map));
			if (NewMap != -1) {
				GameInterface.MAPS_LIST.select = NewMap + 1;
				CurMap = NewMap;
				showmap();
				return;
			}
			NoMapMsg(true);
		}
	}
}

void NoMapMsg(bool bshow) {
	CreateString(bshow,"FoundMap","No Map for this island",FONT_CAPTION,COLOR_MONEY,320,520,SCRIPT_ALIGN_CENTER,0.9);
}

void InitSubMaps() {

	submaps.cuba.x1 = 150;
	submaps.cuba.y1 = 90;
	submaps.cuba.x2 = 260;
	submaps.cuba.y2 = 140;
	submaps.cuba.map = "map_cuba";

	submaps.tortuega.x1 = 305;
	submaps.tortuega.y1 = 105;
	submaps.tortuega.x2 = 330;
	submaps.tortuega.y2 = 130;
	submaps.tortuega.map = "map_TORTUGA";

	submaps.hispaniola.x1 = 270;
	submaps.hispaniola.y1 = 140;
	submaps.hispaniola.x2 = 360;
	submaps.hispaniola.y2 = 190;
	submaps.hispaniola.map = "map_hisp";

	submaps.turks.x1 = 370
	submaps.turks.y1 = 70
	submaps.turks.x2 = 400
	submaps.turks.y2 = 110
	submaps.turks.map = "map_terks"

	submaps.Puerto_Rico.x1 = 375
	submaps.Puerto_Rico.y1 = 180
	submaps.Puerto_Rico.x2 = 420
	submaps.Puerto_Rico.y2 = 210
	submaps.Puerto_Rico.map = "map_puerto"

	submaps.bermuda.x1 = 465
	submaps.bermuda.y1 = 80
	submaps.bermuda.x2 = 495
	submaps.bermuda.y2 = 115
	submaps.bermuda.map = "map_bermudas"

	submaps.st_martin.x1 = 470
	submaps.st_martin.y1 = 170
	submaps.st_martin.x2 = 490
	submaps.st_martin.y2 = 195
	submaps.st_martin.map = "map_sm"

	submaps.Nevis.x1 = 420
	submaps.Nevis.y1 = 220
	submaps.Nevis.x2 = 445
	submaps.Nevis.y2 = 245
	submaps.Nevis.map = "map_nevis"

	submaps.Antigua.x1 = 465
	submaps.Antigua.y1 = 250
	submaps.Antigua.x2 = 495
	submaps.Antigua.y2 = 280
	submaps.Antigua.map = "map_antigua"

	submaps.Guadaloupe.x1 = 380
	submaps.Guadaloupe.y1 = 270
	submaps.Guadaloupe.x2 = 430
	submaps.Guadaloupe.y2 = 310
	submaps.Guadaloupe.map = "map_guad"

	submaps.Dominca.x1 = 440
	submaps.Dominca.y1 = 325
	submaps.Dominca.x2 = 465
	submaps.Dominca.y2 = 355
	submaps.Dominca.map = "map_dominica"

	submaps.Martinique.x1 = 390
	submaps.Martinique.y1 = 345
	submaps.Martinique.x2 = 416
	submaps.Martinique.y2 = 377
	submaps.Martinique.map = "map_martiniqua"

	submaps.Barbados.x1 = 470
	submaps.Barbados.y1 = 370
	submaps.Barbados.x2 = 500
	submaps.Barbados.y2 = 400
	submaps.Barbados.map = "map_barbados"

	submaps.trinidad.x1 = 460
	submaps.trinidad.y1 = 420
	submaps.trinidad.x2 = 490
	submaps.trinidad.y2 = 460
	submaps.trinidad.map = "map_trinidad"

	submaps.cayman.x1 = 190
	submaps.cayman.y1 = 200
	submaps.cayman.x2 = 215
	submaps.cayman.y2 = 225
	submaps.cayman.map = "map_cayman"

	submaps.Jamaica.x1 = 200
	submaps.Jamaica.y1 = 290
	submaps.Jamaica.x2 = 275
	submaps.Jamaica.y2 = 330
	submaps.Jamaica.map = "map_jam"

	submaps.Curacao.x1 = 350
	submaps.Curacao.y1 = 410
	submaps.Curacao.x2 = 400
	submaps.Curacao.y2 = 440
	submaps.Curacao.map = "map_Curacao"

	submaps.beliz.x1 = 85
	submaps.beliz.y1 = 230
	submaps.beliz.x2 = 115
	submaps.beliz.y2 = 270
	submaps.beliz.map = "map_beliz"

	submaps.perl_divers.x1 = 15
	submaps.perl_divers.y1 = 280
	submaps.perl_divers.x2 = 160
	submaps.perl_divers.y2 = 410
	submaps.perl_divers.map = "map_Pearl"

	submaps.cumana.x1 = 420
	submaps.cumana.y1 = 460
	submaps.cumana.x2 = 460
	submaps.cumana.y2 = 480
	submaps.cumana.map = "map_cumana"

	submaps.center_main.x1 = 285
	submaps.center_main.y1 = 445
	submaps.center_main.x2 = 395
	submaps.center_main.y2 = 485
	submaps.center_main.map = "map_maracaibo"

	submaps.panama.x1 = 200
	submaps.panama.y1 = 460
	submaps.panama.x2 = 245
	submaps.panama.y2 = 485
	submaps.panama.map = "map_panama"

	submaps.South_Main.x1 = 200
	submaps.South_Main.y1 = 450
	submaps.South_Main.x2 = 510
	submaps.South_Main.y2 = 500
	submaps.South_Main.map = "map_maine_2"

	submaps.West_Main.x1 = 15
	submaps.West_Main.y1 = 140
	submaps.West_Main.x2 = 165
	submaps.West_Main.y2 = 500
	submaps.West_Main.map = "map_maine_1"

	submaps.santa_catalina.x1 = 140
	submaps.santa_catalina.y1 = 350
	submaps.santa_catalina.x2 = 200
	submaps.santa_catalina.y2 = 500
	submaps.santa_catalina.map = "map_santa"

	}
void SelectRColony()
{
	float fMouseX = stf(GameInterface.mousepos.x) - 6.0 + 5;
	float fMouseY = stf(GameInterface.mousepos.y) - 50.0 + 5;

	//iMouseX = iMouseX * 1.6;

	//SendMessage(&GameInterface,"lslff",MSG_INTERFACE_MSG_TO_NODE,"MAP", 10, iMouseX, iMouseY);

	//определяем верхний левый угол картинки
	float fOffsetX = stf(GameInterface.MAP.offset.x);
	float fOffsetY = stf(GameInterface.MAP.offset.y);

	fMouseX = fOffsetX + fMouseX * stf(GameInterface.MAP.scale.x);
	fMouseY = fOffsetY + fMouseY * stf(GameInterface.MAP.scale.y);

	string sColony;
	for(int i = 0; i < MAX_COLONIES; i++)
	{
		sColony = colonies[i].id;
		if(CheckAttribute(&GameInterface, "MAP.imagelist." + sColony))
		{
			if(fMouseX >= stf(GameInterface.MAP.imagelist.(sColony).x))
			{
				if(fMouseX <= stf(GameInterface.MAP.imagelist.(sColony).x) + 12.0)
				{
					if(fMouseY >= stf(GameInterface.MAP.imagelist.(sColony).y))
					{
						if(fMouseY <= stf(GameInterface.MAP.imagelist.(sColony).y) + 12.0)
						{
							XI_WindowDisable("MAIN_WINDOW", true);
							XI_WindowDisable("INFO_WINDOW", false);
							XI_WindowShow("INFO_WINDOW", true);

							FillColonyInfo(i);
						}
					}
				}
			}
		}
	}
}

void HideRColony()
{
	XI_WindowDisable("MAIN_WINDOW", false);
	XI_WindowDisable("INFO_WINDOW", true);
	XI_WindowShow("INFO_WINDOW", false);
}

void FillColonyInfo(int iColony)
{
	string sColony = colonies[iColony].id;

	SetFormatedText("INFO_CAPTION", XI_ConvertString("Colony"+sColony));

	//string sNation = GetNationNameByType(sti(colonies[iColony].nation));
	//SetNewGroupPicture("INFO_NATION_PICTURE", "NATIONS", sNation);

	string sNation = GameInterface.MAP.imagelist.(sColony).pic;
	SetNewGroupPicture("INFO_NATION_PICTURE", "NATIONS", sNation);

	EI_CreateFrame("INFO_NATIONS_BORDERS",210,152,274,215);

	SelectColony(iColony);
}

void SelectColony(int iColony)
{
	SetFormatedText("COLONY_INFO_TEXT", "");
	SetFormatedText("COLONY_INFO", "");

	string sColony = colonies[iColony].id;

	int iColor;
	int iDistance = CalculateDistance(iColony);

	string sText;

	sText = " " + XI_ConvertString("Population");
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"COLONY_INFO_TEXT", 0,&sText);

	sText = " " + XI_ConvertString("Gold");
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"COLONY_INFO_TEXT", 0,&sText);

	sText = " " + XI_ConvertString("Is Level");
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"COLONY_INFO_TEXT", 0,&sText);

	sText = " " + XI_ConvertString("Is Fort");
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"COLONY_INFO_TEXT", 0,&sText);

	sText = " " + XI_ConvertString("Is Wheat field");
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"COLONY_INFO_TEXT", 0,&sText);

	sText = " " + XI_ConvertString("Is Fishing pier");
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"COLONY_INFO_TEXT", 0,&sText);

	sText = " " + XI_ConvertString("Is Mill");
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"COLONY_INFO_TEXT", 0,&sText);

	sText = " " + XI_ConvertString("Is Shipyard");
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"COLONY_INFO_TEXT", 0,&sText);

	sText = " " + XI_ConvertString("Is Academy");
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"COLONY_INFO_TEXT", 0,&sText);

	sText = " " + XI_ConvertString("is Huts");
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"COLONY_INFO_TEXT", 0,&sText);

	sText = " " + XI_ConvertString("is church");
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"COLONY_INFO_TEXT", 0,&sText);

	sText = " " + XI_ConvertString("is storehouse");
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"COLONY_INFO_TEXT", 0,&sText);

	sText = Colonies[iColony].population;
	sText = sText + " ";
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"COLONY_INFO", 0,&sText);

	sText = Colonies[iColony].money;
	sText = sText + " ";
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"COLONY_INFO", 0,&sText);

	sText = XI_ConvertString("ColonyLevel" + Colonies[iColony].colonylevel);
	sText = sText + " ";
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"COLONY_INFO", 0,&sText);

	sText = Colonies[iColony].fort;
	sText = sText + " ";
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"COLONY_INFO", 0,&sText);

	sText = Colonies[iColony].wheatfield;
	sText = sText + " ";
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"COLONY_INFO", 0,&sText);

	sText = Colonies[iColony].fishingpier;
	sText = sText + " ";
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"COLONY_INFO", 0,&sText);

	sText = Colonies[iColony].mill;
	sText = sText + " ";
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"COLONY_INFO", 0,&sText);

	sText = Colonies[iColony].shipyard;
	sText = sText + " ";
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"COLONY_INFO", 0,&sText);

	sText = Colonies[iColony].academy;
	sText = sText + " ";
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"COLONY_INFO", 0,&sText);

	sText = Colonies[iColony].huts;
	sText = sText + " ";
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"COLONY_INFO", 0,&sText);

	sText = Colonies[iColony].church;
	sText = sText + " ";
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"COLONY_INFO", 0,&sText);

	sText = Colonies[iColony].storehouse;
	sText = sText + " ";
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"COLONY_INFO", 0,&sText);

	if(CheckAttribute(&colonies[iColony], "info.day"))
	{
		sText = XI_ConvertString("LastInfoFromColony");
		sText = sText + colonies[iColony].info.day + " " + XI_ConvertString("target_month_" + colonies[iColony].info.month) + " " + colonies[iColony].info.year + ".";
	}
	SetFormatedText("COLONY_TIME_INFO", sText);

	sText = XI_ConvertString("ColonyDistance") + " "  + FindRussianDaysString(iDistance);
	SetFormatedText("COLONY_TRAVEL_INFO", sText);

	SetFormatedText("IMPORT_INFO", "");
	SetFormatedText("EXPORT_INFO", "");
	int iGood = -1;
	string sGood = "";

	iColor = argb(255,196,196,255);

	iGood = Colonies[iColony].Trade.Import.id1;
	sGood = goods[iGood].name;
	SetNewGroupPicture("IMPORT1_PICTURE", "GOODS", sGood);

	sGood = XI_ConvertString(sGood);
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"IMPORT_INFO", 0,&sGood);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"IMPORT_INFO", 8,-1,iColor);

	iGood = Colonies[iColony].Trade.Import.id2;
	sGood = goods[iGood].name;
	SetNewGroupPicture("IMPORT2_PICTURE", "GOODS", sGood);

	sGood = XI_ConvertString(sGood);
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"IMPORT_INFO", 0,&sGood);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"IMPORT_INFO", 8,-1,iColor);

	iGood = Colonies[iColony].Trade.Import.id3;
	sGood = goods[iGood].name;
	SetNewGroupPicture("IMPORT3_PICTURE", "GOODS", sGood);

	sGood = XI_ConvertString(sGood);
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"IMPORT_INFO", 0,&sGood);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"IMPORT_INFO", 8,-1,iColor);

	iColor = argb(255,196,255,196);

	iGood = Colonies[iColony].Trade.Export.id1;
	sGood = goods[iGood].name;
	SetNewGroupPicture("EXPORT1_PICTURE", "GOODS", sGood);

	sGood = XI_ConvertString(sGood);
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"EXPORT_INFO", 0,&sGood);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"EXPORT_INFO", 8,-1,iColor);

	iGood = Colonies[iColony].Trade.Export.id2;
	sGood = goods[iGood].name;
	SetNewGroupPicture("EXPORT2_PICTURE", "GOODS", sGood);

	sGood = XI_ConvertString(sGood);
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"EXPORT_INFO", 0,&sGood);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"EXPORT_INFO", 8,-1,iColor);

	iGood = Colonies[iColony].Trade.Export.id3;
	sGood = goods[iGood].name;
	SetNewGroupPicture("EXPORT3_PICTURE", "GOODS", sGood);

	sGood = XI_ConvertString(sGood);
	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"EXPORT_INFO", 0,&sGood);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"EXPORT_INFO", 8,-1,iColor);
}

// to_Do del -->
int CalculateDistance(int iColonyNumber)
{
	int playership_x, playership_z;

	int iX = sti(worldMap.playerShipX)/1.66;
	int iZ = sti(worldMap.playerShipZ)/1.66;

	iX = 1024 + iX - 10;
	iZ = 1024 - iZ - 10;

	playership_x = iX;
	playership_z = iZ;

	string sColony = colonies[iColonyNumber].id;

	iX = colonies[iColonyNumber].map.x;
	iZ = colonies[iColonyNumber].map.y;


	int ipX = playership_x - iX;
	int ipZ = playership_z - iZ;

	if(ipX < 0)
	{
		ipX = -ipX;
	}

	if(ipZ < 0)
	{
		ipZ = -ipZ;
	}

	iX = 0;
	iZ = 0;

	int iDist = (ipX*ipX + ipZ*ipZ);

	iDist = sti(sqrt(iDist)+0.5);

	iDist = iDist/100;

	int iDistance = iDist;

	float fDist = 1.0;//  + (0.1 * makefloat(MOD_SKILL_ENEMY_RATE));

	iDistance = makefloat(iDistance) * fDist;

	iDistance = iDistance * 2.8;

	if(iDistance < 1)
	{
		iDistance = 1;
	}

	return iDistance;
}
