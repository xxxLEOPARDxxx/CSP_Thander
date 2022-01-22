int g_LocLngFileID = -1;

object objLandInterface;
object objFastReloadTable;
object objTownStateTable;
int g_intRetVal;

bool bDisableFastReload = false;

#define	BLI_UPDATE_PERIOD 400
#event_handler("evntBattleCommandSound","procBattleCommandSound");

bool bLandInterfaceStart = false;

void procBattleCommandSound()
{
	string comName = GetEventData();
	if(comName=="deactivate")
	{
		PlaySound("interface\ok.wav");
	}
	if(comName=="activate")
	{
		PlaySound("interface\ok.wav");
	}
	if(comName=="right" || comName=="left")
	{
		PlaySound("interface\ok.wav");
	}
}

void InitBattleLandInterface()
{
	if( IsEntity(&objLandInterface) ) {
		EndBattleLandInterface();
	}
	bLandInterfaceStart = false;
	SetEventHandler(EVENT_LOCATION_LOAD,"StartBattleLandInterface",0);
	SetEventHandler(EVENT_LOCATION_UNLOAD,"EndBattleLandInterface",0);
	LoadLIStates();
}

void BLI_EnableShow()
{
	SetLandInterfaceShow( sti(InterfaceStates.BattleShow.Command) );
}

void BLI_DisableShow()
{
	bYesBoardStatus=false;
	DeleteClass(&IBoardingStatus);
	DeleteAttribute(&IBoardingStatus,"");
	SetLandInterfaceShow(false);
}

void SetLandInterfaceShow(bool commandosShow)
{
	SendMessage(&objLandInterface,"ll",MSG_BATTLE_LAND_SET_SHOW,commandosShow);
}

void StartBattleLandInterface()
{
	if(bLandInterfaceStart)
	{
		//BLI_SetObjectData();
		return;
	}
	bLandInterfaceStart = true;

	BLI_SetObjectData();
	BLI_SetMessageParameters();
	CreateEntity(&objLandInterface,"battle_land_interface");
	LayerAddObject(EXECUTE,&objLandInterface,-1);
	LayerAddObject(REALIZE,&objLandInterface,-1);

	SetEventHandler(EVENT_CHANGE_OFFICERS,"BLI_UpdateOfficers",0);
	SetEventHandler(EVENT_DIALOG_START,"BLI_DisableShow",0);
	SetEventHandler(EVENT_DIALOG_EXIT,"BLI_EnableShow",0);

	if(dialogRun) BLI_DisableShow();
	else BLI_EnableShow();

	SetEventHandler("evntBLI_Update","BLI_UpdateObjectData",0);
	SetEventHandler("BI_CommandEndChecking","BLI_CheckCommand",0);
	SetEventHandler("BI_LaunchCommand","BLI_ExecuteCommand",0);
	SetEventHandler("BI_SetPossibleCommands","BLI_SetPossibleCommands",0);
	SetEventHandler("evntFindDialogChar","procFindDialogChar",0);
	SetEventHandler("Location_CharacterEntryToLocator", "BLI_ChrEnterToLocation", 0);
	SetEventHandler("Location_CharacterExitFromLocator", "BLI_ChrExitFromLocation", 0);
	SetEventHandler("evntPerkAgainUsable","BLI_RefreshCommandMenu",0);
	SetEventHandler("Control Activation","LI_ProcessControlPress",0);

	Event("evntBLI_Update");
	Event("evntFindDialogChar");
}

void BLI_SetFlags()
{
	int init = 0;
	if (CheckAttribute(&objLandInterface, "DoSetFlags")) init = sti(objLandInterface.DoSetFlags);
	trace("LandInterface DoSetFlags: " + init);
	init++;
	objLandInterface.DoSetFlags = init;
	if (init >= sti(Characters[GetMainCharacterIndex()].numcoastalindocks))
	{
		DeleteAttribute(&objLandInterface, "DoSetFlags");
		DelEventHandler("frame", "BLI_SetFlags");
	}
}
ref BLI_CheckCommand()
{
	string commandName = GetEventData();

	aref uiref;	makearef(uiref,objLandInterface.UserIcons);
	aref ar;
	int nq = GetAttributesNum(uiref);
	int i;

	bool bUsed = false;
	for(i=0; i<nq; i++)
	{
		ar = GetAttributeN(uiref,i);
		ar.enable = false;
	}
	g_intRetVal = BI_COMMODE_USER_ICONS;

	switch(commandName)
	{
		case "cancel":
			g_intRetVal = -1;
		break;
		case "BI_FastReload":
			bUsed = SetReloadIcons();
		break;
		case "BI_ItemsUse":
			bUsed = SetUsedPotionIcons();
		break;
		case "BI_UseFood":
			bool bEnableFood = true;
			if(bEnableFood)
			{
				bUsed = SetUsedFoodIcons();
			}
			else
			{
				g_intRetVal = 0;
			}
		break;
		case "BI_DialogStart":
			g_intRetVal = 0;
		break;
		case "BI_ItemsChange":
			g_intRetVal = 0;
		break;
		case "BI_TakeItem":
			g_intRetVal = 0;
		break;
		case "BI_PlaceItem":
			g_intRetVal = 0;
		break;
		case "BI_OutDoor":
			g_intRetVal = 0;
		break;
		case "BI_UseBox":
			g_intRetVal = 0;
		break;
		// boal
		case "BI_DeadBox":
			g_intRetVal = 0;
		break;
		case "BI_TalkSelf":
			g_intRetVal = 0;
		break;
		case "BI_Craft":
			g_intRetVal = 0;
		break;
		case "BI_ActivateRush":
			g_intRetVal = 0;
		break;
		case "BI_Exit_Deck": //boal
			g_intRetVal = 0;
		break;
	}
	return &g_intRetVal;
}

void BLI_ExecuteCommand()
{
	int		chrIdx = GetEventData();
	string	commName = GetEventData();
	int		targChrIdx = GetEventData();
	string	evntName = GetEventData();

	aref arFader;
	if( GetEntity(arFader,"fader") ) {return;}

	aref	uiref;
	int		curLocIdx;
	int		tmpi;

	if( commName=="cancel" || evntName=="cancel" ) {
		SendMessage(&objLandInterface,"ls",MSG_BATTLE_LAND_MAKE_COMMAND,"cancel");
		return;
	}

	switch(commName)
	{
	case "BI_FastReload":
		{
			curLocIdx = FindLoadedLocation();
			if(curLocIdx==-1) return;
			if( FindUserIcon(evntName,&uiref) )
			{
				string sTravelLocator = "";
				if(CheckAttribute(uiref,"locator")) {sTravelLocator=uiref.locator;}
				if(CheckAttribute(uiref,"location"))
				{
					if(CheckAttribute(loadedLocation,"islandId"))
					{
						if (loadedLocation.islandId == "Caiman")
						{
							DoQuestReloadToLocation(uiref.location, "reload", "reload1", "");
						}
						else PlayerFastTravel(curLocIdx, uiref.location, sTravelLocator);
					}

					else PlayerFastTravel(curLocIdx, uiref.location, sTravelLocator);
				}
			}
		}
	break;
	case "BI_ItemsUse":
		if( FindUserIcon(evntName,&uiref) )
		{
			if(CheckAttribute(uiref,"potion"))
			{
				aref arItm;
				if( Items_FindItem(uiref.potion,&arItm) >= 0 )
				{
					if( CheckAttribute(arItm,"potion") )
					{
						DoCharacterUsedItem(pchar,arItm.id);
					}
				}
			}
		}
	break;
	case "BI_UseFood":
		if( FindUserIcon(evntName,&uiref) )
		{
			if(CheckAttribute(uiref,"Food"))
			{
				if( Items_FindItem(uiref.Food,&arItm) >= 0 )
				{
					if( CheckAttribute(arItm,"Food") )
					{
						DoCharacterUsedFood(pchar,arItm.id);
					}
				}
			}
		}
	break;
	case "BI_DialogStart":
		tmpi = SendMessage(pchar,"ls",MSG_CHARACTER_EX_MSG,"FindDialogCharacter");
		if(tmpi>=0)	Event("dlgReady","l",tmpi);
	break;
	case "BI_ItemsChange":
		tmpi = SendMessage(pchar,"ls",MSG_CHARACTER_EX_MSG,"FindDialogCharacter");
		if(tmpi>=0 && isOfficerInShip(GetCharacter(tmpi), true))//fix вот дыра дл§ обмена с матросом
        {
            LaunchCharacterItemChange(GetCharacter(tmpi));
        }
        // boal 22.01.2004 -->
		else
		{
			if (tmpi>=0 && CheckAttribute(GetCharacter(tmpi), "IsCompanionClone")) // 1.2.4
			{
			    LaunchCharacterItemChange(GetCharacter(tmpi));
			}
			else
			{
				// обмен с офицером всегда и везде (в абордаже нет диалога!)
			    tmpi = LAi_FindNearestVisCharacter(GetMainCharacter(), 1);
			    if( tmpi>0 && IsOfficer(GetCharacter(tmpi)) && IsCharacterPerkOn(pchar,"SharedExperience") )
				{
				    LaunchCharacterItemChange(GetCharacter(tmpi));
				}
			}
		}
	break;
	case "BI_TakeItem":
		Item_OnPickItem();
	break;
	case "BI_PlaceItem":
		Item_OnUseItem();
	break;
	case "BI_OutDoor":
		Event("Control Activation","s","ChrAction");
	break;
	case "BI_UseBox":
		OpenBoxProcedure();
	break;
	// boal
	case "BI_DeadBox":
		Dead_OpenBoxProcedure();
	break;
	case "BI_TalkSelf":
		DoQuestCheckDelay("TalkSelf_Start", 0.2);
	break;
	case "BI_Craft":
		pchar.questTemp.CraftType = "Blacksmith";
		LaunchCraftAll();
	break;
	case "BI_ActivateRush":
		ActivateCharacterPerk(pchar,"Rush");
	break;
	// boal
    case "BI_Exit_Deck":
        if (isShipInside(pchar.location) || CheckShipSituation_GenQuest())
        {
            Return2SeaAfterCabin();
        }
        else
        {
            int idxLoadLoc = FindLoadedLocation();
            if (idxLoadLoc != -1)
            {
	            UnloadLocation(&Locations[idxLoadLoc]);
            }
            wdmReloadToSea();
        }
    break;
	}
}

void EndBattleLandInterface()
{
	if(!bLandInterfaceStart) return;
	bLandInterfaceStart = false;

	DeleteAttribute( pchar, "boxname" );

	bYesBoardStatus=false;
	DeleteClass(&IBoardingStatus);
	DeleteAttribute(&IBoardingStatus,"");

	BLI_DisableShow();
	SendMessage(&objLandInterface,"l",MSG_BATTLE_LAND_END);

	DeleteClass(&objLandInterface);

	DelEventHandler(EVENT_CHANGE_OFFICERS,"BLI_UpdateOfficers");
	DelEventHandler(EVENT_DIALOG_START,"BLI_DisableShow");
	DelEventHandler(EVENT_DIALOG_EXIT,"BLI_EnableShow");
	DelEventHandler("evntBLI_Update","BLI_UpdateObjectData");
	DelEventHandler("BI_CommandEndChecking","BLI_CheckCommand");
	DelEventHandler("BI_LaunchCommand","BLI_ExecuteCommand");
	DelEventHandler("BI_SetPossibleCommands","BLI_SetPossibleCommands");
	DelEventHandler("evntFindDialogChar","procFindDialogChar");
	DelEventHandler("Location_CharacterEntryToLocator", "BLI_ChrEnterToLocation");
	DelEventHandler("Location_CharacterExitFromLocator", "BLI_ChrExitFromLocation");
	DelEventHandler("evntPerkAgainUsable","BLI_RefreshCommandMenu");
	DelEventHandler("Control Activation","LI_ProcessControlPress");

	//#20171218-01 Re-enable fast action for cabin enter during boarding
    if(CheckAttribute(&BattleInterface, "LAi_ActivateReload")) {
        Log_SetActiveAction("Reload");
    }
    else {
        Log_SetActiveAction("Nothing");
    }
}

void BLI_SetObjectData()
{
    //#20180714-01
    float fHtRatio = stf(Render.screen_y) / screenscaling;
    int fTmp, fTmp2;
	DeleteAttribute(&objLandInterface,"");

	objLandInterface.parameters.DoShowCommandos = InterfaceStates.BattleShow.Command;
	objLandInterface.data.Alarm = 0; // нет тревоги

	// персы вместе с нами
	aref ar;
	int i,cn;
	ref curCh;
	string attrName;
	//#20170318-20
	for(i=0; i<=MAX_NUM_FIGHTERS; i++)
	{
		cn = GetOfficersIndex(pchar,i);
		if(cn==-1) continue;
		curCh = GetCharacter(cn);
		attrName = "id"+i;
		makearef(ar,objLandInterface.data.icons.(attrName));
		SetCharacterIconData(cn,ar);
	}
	BLI_SetMessageParameters();
	// текстуры
	int idLngFile = LanguageOpenFile("commands_name.txt");
	if(InterfaceStates.AltIntIcons) objLandInterface.CommandTextures.list.t0.name = "battle_interface\LandCommands_Konshud.tga";
	else objLandInterface.CommandTextures.list.t0.name = "battle_interface\LandCommands.tga";
	objLandInterface.CommandTextures.list.t0.xsize = 16;
	objLandInterface.CommandTextures.list.t0.ysize = 4;

 	if(InterfaceStates.AltIntIcons) objLandInterface.CommandTextures.list.t1.name = "battle_interface\LandTarget_SLB_Konshud.tga";
 	else objLandInterface.CommandTextures.list.t1.name = "battle_interface\LandTarget_SLB.tga";
	objLandInterface.CommandTextures.list.t1.xsize = 16;
	objLandInterface.CommandTextures.list.t1.ysize = 2;

	if(InterfaceStates.AltIntIcons) objLandInterface.CommandTextures.list.t2.name = "battle_interface\Cancel_Konshud.tga";
	else objLandInterface.CommandTextures.list.t2.name = "battle_interface\Cancel.tga";
	objLandInterface.CommandTextures.list.t2.xsize = 2;
	objLandInterface.CommandTextures.list.t2.ysize = 1;
	if(InterfaceStates.AltIntIcons) objLandInterface.CommandTextures.list.t3.name = "battle_interface\UseFood_Konshud.tga";
	else objLandInterface.CommandTextures.list.t3.name = "battle_interface\UseFood.tga";
	objLandInterface.CommandTextures.list.t3.xsize = 8;
	objLandInterface.CommandTextures.list.t3.ysize = 2;
	// boal <--
	objLandInterface.CommandTextures.CommandTexNum = 0;
	//
	DeleteAttribute(&objIconsNote,"");
	objIconsNote.1x0 = LanguageConvertString(idLngFile, "go_store");
	objIconsNote.1x1 = LanguageConvertString(idLngFile, "go_shipyard");
	objIconsNote.1x2 = LanguageConvertString(idLngFile, "go_tavern");
	objIconsNote.1x3 = LanguageConvertString(idLngFile, "go_usurer");
	objIconsNote.1x4 = LanguageConvertString(idLngFile, "go_residence");
	objIconsNote.1x5 = LanguageConvertString(idLngFile, "go_prison");
	objIconsNote.1x6 = LanguageConvertString(idLngFile, "go_church");
	objIconsNote.1x7 = LanguageConvertString(idLngFile, "go_fort");
	objIconsNote.1x8 = LanguageConvertString(idLngFile, "go_portman");
	objIconsNote.1x9 = LanguageConvertString(idLngFile, "go_brothel");
	objIconsNote.1x10 = LanguageConvertString(idLngFile, "go_port");
	objIconsNote.1x13 = LanguageConvertString(idLngFile, "go_townexit");
	objIconsNote.1x14 = LanguageConvertString(idLngFile, "go_storehouse");
	objIconsNote.1x15 = LanguageConvertString(idLngFile, "go_minehouse");
	objIconsNote.1x16 = LanguageConvertString(idLngFile, "go_planthouse");
	objIconsNote.1x17 = LanguageConvertString(idLngFile, "go_forthouse");
	objIconsNote.1x18 = LanguageConvertString(idLngFile, "go_graveyard");
	objIconsNote.1x19 = LanguageConvertString(idLngFile, "go_GWIK");
	objIconsNote.1x20 = LanguageConvertString(idLngFile, "go_Inquisition");
	// список команд
	objLandInterface.Commands.Cancel.enable		= false;
	objLandInterface.Commands.Cancel.picNum		= 1;
	objLandInterface.Commands.Cancel.selPicNum	= 0;
	objLandInterface.Commands.Cancel.texNum		= 2;
	objLandInterface.Commands.Cancel.event		= "Cancel";
	objLandInterface.Commands.Cancel.name		= "Cancel";
	objLandInterface.Commands.Cancel.note		= LanguageConvertString(idLngFile, "sea_cancel");

	objLandInterface.Commands.FastReload.enable		= true;
	objLandInterface.Commands.FastReload.picNum		= 27;
	objLandInterface.Commands.FastReload.selPicNum	= 11;
	objLandInterface.Commands.FastReload.texNum		= 1;
	objLandInterface.Commands.FastReload.event		= "BI_FastReload";
	objLandInterface.Commands.FastReload.note		= LanguageConvertString(idLngFile, "land_FastReload");

	objLandInterface.Commands.OutDoor.enable		= true;
	objLandInterface.Commands.OutDoor.picNum		= 28;
	objLandInterface.Commands.OutDoor.selPicNum		= 12;
	objLandInterface.Commands.OutDoor.texNum		= 1;
	objLandInterface.Commands.OutDoor.event			= "BI_OutDoor";
	objLandInterface.Commands.OutDoor.note			= LanguageConvertString(idLngFile, "land_OutDoor");

    objLandInterface.Commands.ItemsUse.enable		= true;
 	objLandInterface.Commands.ItemsUse.picNum		= 20;
	objLandInterface.Commands.ItemsUse.selPicNum		= 4;
	objLandInterface.Commands.ItemsUse.texNum		= 0;
	objLandInterface.Commands.ItemsUse.event		= "BI_ItemsUse";
	objLandInterface.Commands.ItemsUse.note			= LanguageConvertString(idLngFile, "land_ItemsUse");

    objLandInterface.Commands.UseFood.enable		= true;
 	objLandInterface.Commands.UseFood.picNum		= 20;
	objLandInterface.Commands.UseFood.selPicNum		= 4;
	objLandInterface.Commands.UseFood.texNum		= 0;
	objLandInterface.Commands.UseFood.event			= "BI_UseFood";
	objLandInterface.Commands.UseFood.note			= LanguageConvertString(idLngFile, "land_UseFood");

	objLandInterface.Commands.DialogStart.enable	= true;
 	objLandInterface.Commands.DialogStart.picNum		= 17;
	objLandInterface.Commands.DialogStart.selPicNum		= 1;
	objLandInterface.Commands.DialogStart.texNum		= 0;
	objLandInterface.Commands.DialogStart.event		= "BI_DialogStart";
	objLandInterface.Commands.DialogStart.note		= LanguageConvertString(idLngFile, "land_DialogStart");

	objLandInterface.Commands.ItemsChange.enable	= true;
 	objLandInterface.Commands.ItemsChange.picNum		= 19;
	objLandInterface.Commands.ItemsChange.selPicNum		= 3;
	objLandInterface.Commands.ItemsChange.texNum		= 0;
	objLandInterface.Commands.ItemsChange.event		= "BI_ItemsChange";
	objLandInterface.Commands.ItemsChange.note		= LanguageConvertString(idLngFile, "land_ItemsChange");

	objLandInterface.Commands.TakeItem.enable		= true;
 	objLandInterface.Commands.TakeItem.picNum		= 16;
	objLandInterface.Commands.TakeItem.selPicNum		= 0;
	objLandInterface.Commands.TakeItem.texNum		= 0;
	objLandInterface.Commands.TakeItem.event		= "BI_TakeItem";
	objLandInterface.Commands.TakeItem.note			= LanguageConvertString(idLngFile, "land_TakeItem");

	objLandInterface.Commands.PlaceItem.enable		= true;
 	objLandInterface.Commands.PlaceItem.picNum		= 16;
	objLandInterface.Commands.PlaceItem.selPicNum		= 0;
	objLandInterface.Commands.PlaceItem.texNum		= 0;
	objLandInterface.Commands.PlaceItem.event		= "BI_PlaceItem";
	objLandInterface.Commands.PlaceItem.note		= LanguageConvertString(idLngFile, "land_PlaceItem");

	objLandInterface.Commands.UseBox.enable			= true;
 	objLandInterface.Commands.UseBox.picNum		    = 16;
	objLandInterface.Commands.UseBox.selPicNum		= 0;
	objLandInterface.Commands.UseBox.texNum		= 0;
	objLandInterface.Commands.UseBox.event			= "BI_UseBox";
	objLandInterface.Commands.UseBox.note			= LanguageConvertString(idLngFile, "land_UseBox");

	objLandInterface.Commands.DeadBox.enable			= true;
 	objLandInterface.Commands.DeadBox.picNum		    = 20;
	objLandInterface.Commands.DeadBox.selPicNum		= 4;
	objLandInterface.Commands.DeadBox.texNum		= 0;
	objLandInterface.Commands.DeadBox.event			= "BI_DeadBox";
	objLandInterface.Commands.DeadBox.note			= "Обыск тела";
	// диалог сам с собой -->
	objLandInterface.Commands.TalkSelf.enable	= true;
 	objLandInterface.Commands.TalkSelf.picNum	 	= 18;
	objLandInterface.Commands.TalkSelf.selPicNum	= 2;
	objLandInterface.Commands.TalkSelf.texNum		= 0;
	objLandInterface.Commands.TalkSelf.event		= "BI_TalkSelf";
	objLandInterface.Commands.TalkSelf.note		    = "Мысли вслух";
	// диалог сам с собой <--

	objLandInterface.Commands.Craft.enable	= true;
 	objLandInterface.Commands.Craft.picNum	 	= 48;
	objLandInterface.Commands.Craft.selPicNum	= 32;
	objLandInterface.Commands.Craft.texNum		= 0;
	objLandInterface.Commands.Craft.event		= "BI_Craft";
	objLandInterface.Commands.Craft.note		= "Создание предмета";

	objLandInterface.Commands.ActivateRush.enable	= true;
	objLandInterface.Commands.ActivateRush.picNum	= 28;
	objLandInterface.Commands.ActivateRush.selPicNum		= 12;
	objLandInterface.Commands.ActivateRush.texNum		= 0;
	objLandInterface.Commands.ActivateRush.event	= "BI_ActivateRush";
	objLandInterface.Commands.ActivateRush.note		= LanguageConvertString(idLngFile, "land_ActivateRush");

	objLandInterface.Commands.Exit_Deck.enable		= true;
	objLandInterface.Commands.Exit_Deck.picNum		= 30;
	objLandInterface.Commands.Exit_Deck.selPicNum		= 14;
	objLandInterface.Commands.Exit_Deck.texNum		= 0;
	objLandInterface.Commands.Exit_Deck.event		= "BI_Exit_Deck";
	objLandInterface.Commands.Exit_Deck.note		= LanguageConvertString(idLngFile, "land_Exit");
	// boal <--
	// список пользовательских картинок
	LanguageCloseFile(idLngFile);
	// go to icons
	int idxloc = FindLoadedLocation();
	string outGroupName = "";
	RecalculateHireCrew(idxloc);  // to_do убрать на таймер
	if(idxloc>=0 && CheckAttribute(&Locations[idxloc],"fastreload"))
	{
		outGroupName = Locations[idxloc].fastreload;
		CreateReloadPaths(outGroupName);
	}

	objLandInterface.ManSign.useUDFBars = true;
	objLandInterface.ManSign.UDFColor1 = ARGB(255,128,128,128);
	objLandInterface.ManSign.UDFColor2 = ARGB(255,0,255,0);

	if(InterfaceStates.HUDStyle)
	{
		objLandInterface.ManSign.UDFWidth 				= makeint(59.0 * fHtRatio);
		objLandInterface.ManSign.UDFHeight 				= makeint(3.0 * fHtRatio);
		objLandInterface.ManSign.UDFPos2 				= makeint(20.0 * fHtRatio)+","+makeint(85.0 * fHtRatio);
		objLandInterface.ManSign.UDFPos1 				= makeint(20.0 * fHtRatio)+","+makeint(85.0 * fHtRatio);
		objLandInterface.ManSign.UDFOffsets 			= "0,"+makeint(85.0 * fHtRatio);

		objLandInterface.ManSign.backtexturename		= "battle_interface\Char_Border.tga";
		objLandInterface.ManSign.backcolor				= argb(255,128,128,128);
		objLandInterface.ManSign.backuv					= "0.0,0.0,1.0,1.0";
		fTmp 											= makeint(-10.0 * fHtRatio);
		fTmp2 											= makeint(-5.0 * fHtRatio);
		objLandInterface.ManSign.backoffset				= fTmp + "," + fTmp2;
		// fTmp 											= makeint(64.0 * fHtRatio);
		objLandInterface.ManSign.backiconsize			= makeint(64.0 * fHtRatio)+","+makeint(74.0 * fHtRatio);

		objLandInterface.ManSign.alarmtexturename		= "battle_interface\AlarmQ.tga";
		objLandInterface.ManSign.alarmhighcolor			= argb(255,168,28,28);
		objLandInterface.ManSign.alarmlowcolor			= argb(64,168,28,28);
		objLandInterface.ManSign.alarmuptime			= 0.5;
		objLandInterface.ManSign.alarmdowntime			= 1.5;
		objLandInterface.ManSign.alarmuv				= "0.0,0.0,1.0,1.0";
		fTmp 											= makeint(-10.0 * fHtRatio);
		fTmp2 											= makeint(-10.0 * fHtRatio);
		objLandInterface.ManSign.alarmoffset			= fTmp + "," + fTmp2;
		fTmp 											= makeint(62.0 * fHtRatio);
		objLandInterface.ManSign.alarmiconsize			= fTmp + "," + fTmp;

		objLandInterface.ManSign.manstatetexturename	= "battle_interface\ShipHP_SP.tga";
		objLandInterface.ManSign.manstatecolor			= argb(255,128,128,128);
		objLandInterface.ManSign.manhpuv				= "0.0,0.109,0.5,0.6875";
		objLandInterface.ManSign.manenegryuv			= "0.5,0.109,1.0,0.6875";

		fTmp 											= makeint(-30.5 * fHtRatio);
		fTmp2 											= makeint(-13.5 * fHtRatio);
		objLandInterface.ManSign.manhpoffset			= fTmp + "," + fTmp2;
		fTmp 											= makeint(54.0 * fHtRatio);
		fTmp2 											= makeint(69.0 * fHtRatio);
		objLandInterface.ManSign.manhpiconsize			= fTmp + "," + fTmp2;

		fTmp 											= makeint(33.8 * fHtRatio);
		fTmp2 											= makeint(-13.5 * fHtRatio);
		objLandInterface.ManSign.manenegryoffset		= fTmp + "," + fTmp2;
		fTmp 											= makeint(54.0 * fHtRatio);
		fTmp2 											= makeint(69.0 * fHtRatio);
		objLandInterface.ManSign.manenergyiconsize		= fTmp + "," + fTmp2;

		objLandInterface.ManSign.gunchargetexturename	= "battle_interface\GunCharge_CSP.tga"; // LEO: Тут у нас другой GUI
		objLandInterface.ManSign.gunchargecolor			= argb(255,0, 250, 154);
		objLandInterface.ManSign.gunchargebackcolor		= argb(255,0, 0, 0);
		objLandInterface.ManSign.gunchargeuv			= "0.0,0.0,1.0,1.0";
		objLandInterface.ManSign.gunchargeprogress		= "0.0625, 0.219, 0.359, 0.5, 0.641, 0.781, 0.983";

		fTmp 											= makeint(-10.0 * fHtRatio);
		fTmp2 											= makeint(-48.0 * fHtRatio);
		objLandInterface.ManSign.gunchargeoffset		= fTmp + "," + fTmp2;
		fTmp 											= makeint(80.0 * fHtRatio);
		fTmp2 											= makeint(20.0 * fHtRatio);
		objLandInterface.ManSign.gunchargeiconsize		= fTmp + "," + fTmp2;

		objLandInterface.ManSign.manfacecolor			= argb(255,128,128,128);
		fTmp 											= makeint(-10.0 * fHtRatio);
		fTmp2 											= makeint(-10.0 * fHtRatio);
		objLandInterface.ManSign.manfaceoffset			= fTmp + "," + fTmp2;
		fTmp 											= makeint(62.0 * fHtRatio);
		objLandInterface.ManSign.manfaceiconsize		= fTmp + "," + fTmp;
		objLandInterface.ManSign.commandlistverticaloffset = -36 * fHtRatio;
		fTmp 											= makeint(60.0 * fHtRatio);
		fTmp2 											= makeint(85.0 * fHtRatio);

		objLandInterface.ManSign.gunreloadtexturename	= "battle_interface\MORALE_bar.tga";
		objLandInterface.ManSign.gunreloadcolor 		= ARGB(255, 0, 255, 62);
		objLandInterface.ManSign.gunreloadbackcolor		= ARGB(255, 0, 255, 62);
		objLandInterface.ManSign.gunreloadUV			= "0.0,0.0,1.0,1.0";
		fTmp 											= makeint(-10.0 * fHtRatio);
		fTmp2 											= makeint(26.0 * fHtRatio);
		objLandInterface.ManSign.gunreloadoffset		= fTmp + "," + fTmp2;
		fTmp 											= makeint(60.0 * fHtRatio);
		fTmp2 											= makeint(85.0 * fHtRatio);
		objLandInterface.ManSign.gunreloadiconsize		= "70.0,6.0"
	}
	else
	{

		///////////////////////////////////////////////////////////////////
		/// НОВЫЙ HUD НА ЗАМЕНУ СТАНДАРТНОГО BY JOHNNY88
		///////////////////////////////////////////////////////////////////
		objLandInterface.ManSign.UDFWidth 				= makeint(38.0 * fHtRatio);
		objLandInterface.ManSign.UDFHeight 				= makeint(10.0 * fHtRatio);
		objLandInterface.ManSign.UDFPos2 				= makeint(41.0 * fHtRatio)+","+makeint(81.0 * fHtRatio);
		objLandInterface.ManSign.UDFPos1 				= makeint(41.0 * fHtRatio)+","+makeint(81.0 * fHtRatio);
		objLandInterface.ManSign.UDFOffsets 			= "0,"+makeint(85.0 * fHtRatio);

		// подложка иконки ГГ и офицеров
		objLandInterface.ManSign.backtexturename		= "battle_interface\CharBackIcon.tga";
		objLandInterface.ManSign.backcolor				= argb(255,128,128,128);
		objLandInterface.ManSign.backuv					= "0.0,0.0,1.0,1.0";
		fTmp 											= makeint(0.0 * fHtRatio);
		fTmp2 											= makeint(-12.0 * fHtRatio);
		objLandInterface.ManSign.backoffset				= fTmp + "," + fTmp2;
		fTmp 											= makeint(90.0 * fHtRatio);
		objLandInterface.ManSign.backiconsize			= fTmp + "," + fTmp;

		objLandInterface.ManSign.alarmtexturename		= "battle_interface\AlarmBack.tga";
		objLandInterface.ManSign.alarmhighcolor			= argb(255,168,28,28);
		objLandInterface.ManSign.alarmlowcolor			= argb(64,168,28,28);
		objLandInterface.ManSign.alarmuptime			= 0.5;
		objLandInterface.ManSign.alarmdowntime			= 1.5;
		objLandInterface.ManSign.alarmuv				= "0.0,0.0,1.0,1.0";
		fTmp 											= makeint(1.0 * fHtRatio);
		fTmp2 											= makeint(-11.5 * fHtRatio);
		objLandInterface.ManSign.alarmoffset			= fTmp + "," + fTmp2;
		fTmp 											= makeint(92.0 * fHtRatio);
		objLandInterface.ManSign.alarmiconsize			= fTmp + "," + fTmp;

		objLandInterface.ManSign.manstatetexturename	= "battle_interface\Char_State.tga";
		objLandInterface.ManSign.manstatecolor			= argb(255,128,128,128);
		objLandInterface.ManSign.manhpuv				= "0.0,0.13,0.72,0.89";
		objLandInterface.ManSign.manenegryuv			= "0.28,0.12,1.0,0.89";

		fTmp 											= makeint(-14.0 * fHtRatio);		// положение индикатора ХП по горизнтали
		fTmp2 											= makeint(-11.0 * fHtRatio);		// положение индикатора ХП по вертикали
		objLandInterface.ManSign.manhpoffset			= fTmp + "," + fTmp2;
		fTmp 											= makeint(61.0 * fHtRatio);			// размереры индикатора ХП
		fTmp2 											= makeint(68.5 * fHtRatio);
		objLandInterface.ManSign.manhpiconsize			= fTmp + "," + fTmp2;
		fTmp 											= makeint(14.0 * fHtRatio);			// положение индикатора энергии по горизнтали
		fTmp2 											= makeint(-11.0 * fHtRatio);		// положение индикатора энергии по вертикали
		objLandInterface.ManSign.manenegryoffset		= fTmp + "," + fTmp2;
		fTmp 											= makeint(61.0 * fHtRatio);			// размереры индикатора энергии
		fTmp2 											= makeint(68.5 * fHtRatio);
		objLandInterface.ManSign.manenergyiconsize		= fTmp + "," + fTmp2;

		objLandInterface.ManSign.gunchargetexturename	= "battle_interface\GunCharge.tga";
		objLandInterface.ManSign.gunchargecolor			= argb(255,0, 250, 154);
		objLandInterface.ManSign.gunchargebackcolor		= argb(255,0, 0, 0);
		objLandInterface.ManSign.gunchargeuv			= "0.0,0.0,1.0,1.0";
		objLandInterface.ManSign.gunchargeprogress		= "0.0625, 0.219, 0.359, 0.5, 0.641, 0.781, 0.983";

		fTmp 											= makeint(0.0 * fHtRatio);
		fTmp2 											= makeint(-47.0 * fHtRatio);
		objLandInterface.ManSign.gunchargeoffset		= fTmp + "," + fTmp2;
		fTmp 											= makeint(66.0 * fHtRatio);
		fTmp2 											= makeint(15.0 * fHtRatio);
		objLandInterface.ManSign.gunchargeiconsize		= fTmp + "," + fTmp2;
		objLandInterface.ManSign.manfacecolor			= argb(255,128,128,128);

		fTmp 											= makeint(-1.0 * fHtRatio);
		fTmp2											= makeint(-12.0 * fHtRatio);
		objLandInterface.ManSign.manfaceoffset			= fTmp + "," + fTmp2;
		fTmp 											= makeint(60.0 * fHtRatio);
		objLandInterface.ManSign.manfaceiconsize		= fTmp + "," + fTmp;
		objLandInterface.ManSign.commandlistverticaloffset = -36 * fHtRatio;
		fTmp 											= makeint(60.0 * fHtRatio);
		fTmp2 											= makeint(85.0 * fHtRatio);

		objLandInterface.ManSign.gunreloadtexturename	= "battle_interface\MORALE_bar.tga";
		objLandInterface.ManSign.gunreloadcolor 		= ARGB(255, 0, 255, 62);
		objLandInterface.ManSign.gunreloadbackcolor		= ARGB(255, 0, 255, 62);
		objLandInterface.ManSign.gunreloadUV			= "0.0,0.0,1.0,1.0";
		fTmp 											= makeint(0.0 * fHtRatio);
		fTmp2 											= makeint(26.0 * fHtRatio);
		objLandInterface.ManSign.gunreloadoffset		= fTmp + "," + fTmp2;
		fTmp 											= makeint(60.0 * fHtRatio);
		fTmp2 											= makeint(85.0 * fHtRatio);
		objLandInterface.ManSign.gunreloadiconsize		= "48.0,8.0";
	}

	for(i = 1; i<=MAX_NUM_FIGHTERS + 1; i++) {
		string sOffsetIcon = "iconoffset" + i;
		objLandInterface.ManSign.(sOffsetIcon) = fTmp + "," + (fTmp + (i-1)*fTmp2);
	}

	int nLoc = FindLoadedLocation();
	if(nLoc >= 0)
	{
		int nFile = LanguageOpenFile("LocLables.txt");
		if(nFile >= 0) {
			objLandInterface.textinfo.islandname.font = "interface_button";
			objLandInterface.textinfo.islandname.scale = 1.2 * fHtRatio;
			objLandInterface.textinfo.islandname.pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(130 * fHtRatio));
			objLandInterface.textinfo.islandname.pos.y = RecalculateVIcon(makeint(10 * fHtRatio));
			if (CheckAttribute(&locations[nLoc],"islandId"))
			{
				if (locations[nLoc].islandId != "Mein")
				{
					objLandInterface.textinfo.islandname.text = XI_convertString("Island:") + LanguageConvertString(nFile, locations[nLoc].islandId);
				}
				else
				{
					objLandInterface.textinfo.islandname.text = LanguageConvertString(nFile, locations[nLoc].islandId);
				}
			}
			else
			{
				objLandInterface.textinfo.islandname.text = "";//XI_convertString("Open Sea");
			}
			objLandInterface.textinfo.villagename.font = "interface_button";
			objLandInterface.textinfo.villagename.scale = 1.2 * fHtRatio;
			objLandInterface.textinfo.villagename.pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(130 * fHtRatio));
			objLandInterface.textinfo.villagename.pos.y = RecalculateVIcon(makeint(40 * fHtRatio));

			objLandInterface.textinfo.locationname.font = "interface_button";
			objLandInterface.textinfo.locationname.scale = 1.2 * fHtRatio;
			objLandInterface.textinfo.locationname.pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(130 * fHtRatio));
			objLandInterface.textinfo.locationname.pos.y = RecalculateVIcon(makeint(70 * fHtRatio));

            string sCaimanName = PChar.ColonyBuilding.ColonyName;

			if (!CheckAttribute(&locations[nLoc],"fastreload"))
			{
				objLandInterface.textinfo.villagename.text = "";

				if(CheckAttribute(&Locations[nLoc], "islandId"))
				{
					if(Locations[nLoc].islandId == "Caiman")
					{
						if(sCaimanName == "")
						{
							sCaimanName = "Кайман";
						}

						if(PChar.ColonyBuilding.Stage != "0")
						{
							objLandInterface.textinfo.villagename.text = XI_ConvertString("Colony:") + sCaimanName;
						}
					}
				}
			}
			else
			{
				objLandInterface.textinfo.villagename.text = XI_ConvertString("Colony:") + LanguageConvertString(nFile, locations[nLoc].fastreload + " Town");

				bool bCaiman = false;
				if(CheckAttribute(&Locations[nLoc], "islandId"))
				{
					if(Locations[nLoc].islandId == "Caiman") bCaiman = true;
				}

				if(locations[nLoc].fastreload == "Caiman" || locations[nLoc].fastreload == "CaimanSmall" || bCaiman)
				{
					if(sCaimanName == "")
					{
						sCaimanName = "Кайман";
					}

					objLandInterface.textinfo.villagename.text = XI_ConvertString("Colony:") + sCaimanName;
				}
			}

			objLandInterface.textinfo.locationname.text = LanguageConvertString(nFile, locations[nLoc].id.label);
			LanguageCloseFile( nFile );
		}
	}
	objLandInterface.textinfo.datatext.font = "interface_button";
	objLandInterface.textinfo.datatext.scale = 1.2 * fHtRatio;
	objLandInterface.textinfo.datatext.pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(130 * fHtRatio));
	objLandInterface.textinfo.datatext.pos.y = RecalculateVIcon(makeint(100 * fHtRatio));
	RefreshLandTime();
	objLandInterface.textinfo.datatext.refreshable = true;
// плашка дозарядки пистолета
	// if(!dialogRun)
	// {
		// int fTmp3;
		// int fTmp4;
		// if(InterfaceStates.HUDStyle)
		// {
			// fTmp = makeint(19.0 * fHtRatio); 	// left
			// fTmp2 = makeint(96.0 * fHtRatio); 	// top
			// fTmp3 = makeint(81.0 * fHtRatio); 	// right
			// fTmp4 = makeint(80.0 * fHtRatio); 	// bottom
		// }
		// else
		// {
			// fTmp = makeint(15.0 * fHtRatio); 	// left
			// fTmp2 = makeint(7.0 * fHtRatio); 	// top
			// fTmp3 = makeint(102.0 * fHtRatio); 	// right
			// fTmp4 = makeint(93.0 * fHtRatio); 	// bottom
		// }
		// string off	= fTmp + "," + fTmp2 + "," + fTmp3 + "," + fTmp4;

		// if(InterfaceStates.HUDStyle)
		// {
		// objLandInterface.imageslist.textinfoback2.texture = "battle_interface\CharGunBackIcon.tga";
		// objLandInterface.imageslist.textinfoback2.color = argb(255,128,128,128);
		// objLandInterface.imageslist.textinfoback2.uv = "0.0,0.0,0.96,1.0";
		// objLandInterface.imageslist.textinfoback2.pos = off;
		// }
		// else
		// {
		// objLandInterface.imageslist.textinfoback2.texture = "battle_interface\Char_State_Guncharge.tga";
		// objLandInterface.imageslist.textinfoback2.color = argb(255,128,128,128);
		// objLandInterface.imageslist.textinfoback2.uv = "0.0,0.0,0.96,1.0";
		// objLandInterface.imageslist.textinfoback2.pos = off;
		// }
	// }

	if(CheckAttribute(loadedLocation,"fastreload")) // подсказка только там, где она нужна
	{
		objLandInterface.textinfo.AltInfo.font = "interface_normal";
		objLandInterface.textinfo.AltInfo.color = argb(243,254,252,169);
		objLandInterface.textinfo.AltInfo.scale = 1.1 * fHtRatio;
		objLandInterface.textinfo.AltInfo.pos.x = sti(showWindow.left) + RecalculateHIcon(300 * fHtRatio); 
		objLandInterface.textinfo.AltInfo.pos.y = RecalculateVIcon(20 * fHtRatio);
		objLandInterface.textinfo.AltInfo.refreshable = true;
		
		objLandInterface.textinfo.AltInfo1.font = "interface_normal";
		objLandInterface.textinfo.AltInfo1.scale = 1.1 * fHtRatio;
		objLandInterface.textinfo.AltInfo1.pos.x = sti(showWindow.left) + RecalculateHIcon(285 * fHtRatio); 
		objLandInterface.textinfo.AltInfo1.pos.y = RecalculateVIcon(40 * fHtRatio);
		objLandInterface.textinfo.AltInfo1.refreshable = true;
		
		objLandInterface.textinfo.AltInfo2.font = "interface_normal";
		objLandInterface.textinfo.AltInfo2.scale = 1.1 * fHtRatio;
		objLandInterface.textinfo.AltInfo2.pos.x = sti(showWindow.left) + RecalculateHIcon(285 * fHtRatio); 
		objLandInterface.textinfo.AltInfo2.pos.y = RecalculateVIcon(60 * fHtRatio);
		objLandInterface.textinfo.AltInfo2.refreshable = true;

		objLandInterface.textinfo.AltInfo3.font = "interface_normal";
		objLandInterface.textinfo.AltInfo3.scale = 1.1 * fHtRatio;
		objLandInterface.textinfo.AltInfo3.pos.x = sti(showWindow.left) + RecalculateHIcon(306 * fHtRatio); 
		objLandInterface.textinfo.AltInfo3.pos.y = RecalculateVIcon(80 * fHtRatio);
		objLandInterface.textinfo.AltInfo3.refreshable = true;
	}

	objLandInterface.textinfo.deadboxinfo.font = "interface_button";
	objLandInterface.textinfo.deadboxinfo.scale = 1.3 * fHtRatio;
	objLandInterface.textinfo.deadboxinfo.pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(130 * fHtRatio));
	objLandInterface.textinfo.deadboxinfo.pos.y = RecalculateVIcon(makeint(140 * fHtRatio));
	objLandInterface.textinfo.deadboxinfo.refreshable = true;

	objLandInterface.CommandList.CommandMaxIconQuantity = 15;
	objLandInterface.CommandList.CommandIconSpace = 1;
	objLandInterface.CommandList.CommandIconLeft = makeint(110 * fHtRatio);//157;
	objLandInterface.CommandList.CommandIconWidth = RecalculateHIcon(makeint(54 * fHtRatio));
	objLandInterface.CommandList.CommandIconHeight = RecalculateVIcon(makeint(54 * fHtRatio));

	objLandInterface.CommandList.CommandNoteFont = "interface_button";
	objLandInterface.CommandList.CommandNoteColor = argb(255,255,255,255);
	objLandInterface.CommandList.CommandNoteScale = 1.2 * fHtRatio;
	objLandInterface.CommandList.CommandNoteOffset = RecalculateHIcon(0) + "," + RecalculateVIcon(makeint(-50 * fHtRatio));

	objLandInterface.CommandList.UDArrow_Texture = "battle_interface\arrowly.tga.tx";
	objLandInterface.CommandList.UDArrow_UV_Up = "0.0,1.0,1.0,0.0";
	objLandInterface.CommandList.UDArrow_UV_Down = "0.0,0.0,1.0,1.0";
	objLandInterface.CommandList.UDArrow_Size = RecalculateHIcon(makeint(32 * fHtRatio)) + "," + RecalculateVIcon(makeint(32 * fHtRatio));
	objLandInterface.CommandList.UDArrow_Offset_Up = RecalculateHIcon(makeint(-41 * fHtRatio)) + "," + RecalculateVIcon(makeint(-30 * fHtRatio));
	objLandInterface.CommandList.UDArrow_Offset_Down = RecalculateHIcon(makeint(-41 * fHtRatio)) + "," + RecalculateVIcon(makeint(46 * fHtRatio));

	ModifyTextInfo();

	SendMessage(&objLandInterface,"l",MSG_BATTLE_LAND_START);
}

void ModifyTextInfo()
{
	if(bAltInfo)
	{
		objLandInterface.textinfo.AltInfo4.text = "";
		if(CheckAttribute(loadedLocation,"fastreload"))
		{
			objLandInterface.textinfo.AltInfo.text  = "Для быстрого перехода используйте кнопки:"; 
			objLandInterface.textinfo.AltInfo1.text = "1-Порт, 2-Магазин, 3-Верфь, 4-Таверна ";
			objLandInterface.textinfo.AltInfo2.text = "5-Резиденция, 6-Ростовщик, 7-Церковь ";
			objLandInterface.textinfo.AltInfo3.text = "8-Бордель, 9-Портовое управление, 0-Тюрьма"; 

		}
		else
		{
			objLandInterface.textinfo.AltInfo.text  = " "; 
			objLandInterface.textinfo.AltInfo1.text = " ";
			objLandInterface.textinfo.AltInfo2.text = " ";
			objLandInterface.textinfo.AltInfo3.text = " "; 
		}
	}
	else
	{
		objLandInterface.textinfo.AltInfo.text  =  " "; 
		objLandInterface.textinfo.AltInfo1.text =  " ";
		objLandInterface.textinfo.AltInfo2.text =  " ";
		objLandInterface.textinfo.AltInfo3.text = " "; 
	}
}

void RefreshChargeTime()
{
	/* if (dialogRun || !bLandInterfaceStart)
	{
		bYesBoardStatus=false;
		DeleteClass(&IBoardingStatus);
		DeleteAttribute(&IBoardingStatus,"");
	}
	else
	{
		ref chr = &Characters[nMainCharacterIndex];
		aref chr_ai;
		makearef(chr_ai, Characters[nMainCharacterIndex].chr_ai);
		if (CheckAttribute(chr,"chr_ai.charge"))
		{
			float gunch = chr_ai.charge;
			if (gunch > 1.0)
			{
				gunch -= makeint(gunch);
			}

			if (CheckAttribute(chr,"chr_ai.charge_max"))
			{
				if (MakeInt(chr_ai.charge) == makeint(chr_ai.charge_max))
				{
					gunch = 1.0;
				}
			}
			float gunchm = 1.0;
			if(InterfaceStates.HUDStyle) DrawCharacterHPEx(makefloat(0.42/makefloat(gunchm)*makefloat(gunch)),0.1);
			else DrawCharacterHPExx(makefloat(0.35/makefloat(gunchm)*makefloat(gunch)),0.35);
		}
	} */
	if (InterfaceStates.DeadBoxText)
	{
		i = Dead_FindCloseBody();
		if (i != -1)
		{
			objLandInterface.textinfo.deadboxinfo.text = "Есть труп для обыска";
		}
		else objLandInterface.textinfo.deadboxinfo.text = "";
	}
}

bool FindUserIcon(string id,ref uiref)
{
	aref arroot,ar; makearef(arroot,objLandInterface.UserIcons);
	int iMax = GetAttributesNum(arroot); //fix
	for(int i=0; i<iMax; i++)
	{
		ar = GetAttributeN(arroot,i);
		if(ar.name != id) continue;
		uiref = ar;
		return true;
	}
	return false;
}

void BLI_SetMessageParameters()
{
	objLandInterface.MessageIcons.IconWidth = RecalculateHIcon(64);
	objLandInterface.MessageIcons.IconHeight = RecalculateVIcon(24);
	objLandInterface.MessageIcons.IconDist = RecalculateVIcon(2);
	objLandInterface.MessageIcons.IconBottom = sti(showWindow.bottom)-RecalculateHIcon(80+40);
	objLandInterface.MessageIcons.IconMaxQuantity = 4;
	objLandInterface.MessageIcons.BlendTime = 3.0;
	objLandInterface.MessageIcons.FallSpeed = 22.0;
	objLandInterface.MessageIcons.argbHighBlind = argb(255,128,128,128);
	objLandInterface.MessageIcons.argbLowBlind = argb(255,68,68,68);
	objLandInterface.MessageIcons.BlindUpTime = 0.5;
	objLandInterface.MessageIcons.BlindDownTime = 1.0;
	objLandInterface.MessageIcons.texture = "battle_interface\MessageIcons.tga.tx";
	objLandInterface.MessageIcons.TexHSize = 2;
	objLandInterface.MessageIcons.TexVSize = 2;
}

void BLI_UpdateObjectData()
{
	bool bIsRiskAlarm = LAi_group_IsActivePlayerAlarm();
	if(sti(objLandInterface.data.Alarm)!=bIsRiskAlarm) BLI_RefreshCommandMenu();
	objLandInterface.data.Alarm = bIsRiskAlarm;

	aref ar,arItm;
	int i,cn;
	ref curCh;
	string attrName;
	for(i=0; i<=MAX_NUM_FIGHTERS; i++)
	{
		attrName = "id"+i;
		cn = GetOfficersIndex(pchar,i);
		if(cn==-1 || !IsEntity(&Characters[cn]))
		{
			DeleteAttribute(&objLandInterface,"data.icons."+attrName);
			continue;
		}
		curCh = GetCharacter(cn);
		makearef(ar,objLandInterface.data.icons.(attrName));
		SetCharacterIconData(cn,ar);
	}

	PostEvent("evntBLI_Update",BLI_UPDATE_PERIOD);
}

void BLI_SetPossibleCommands()
{
	int chrMode = SendMessage(pchar,"ls",MSG_CHARACTER_EX_MSG,"IsFightMode");

	bool bTmpBool;
	bool bTmpBool2;
	bool bTmpBool3;
	bool bUseCommand = false;
	int i;
	aref rootcom,curcom;
	makearef(rootcom,objLandInterface.Commands);
	int iMax = GetAttributesNum(rootcom); //fix
	for(i=0; i<iMax; i++)
	{
		curcom = GetAttributeN(rootcom,i);
		curcom.enable = false;
	}

	if(chrMode==0)
	{
		bTmpBool = true;
		if(LAi_group_IsActivePlayerAlarm()) bTmpBool = false;
		if(!LAi_IsCharacterControl(pchar)) bTmpBool = false;
		if(bDisableFastReload)	bTmpBool = false;
		if(!IsEnableFastTravel()) bTmpBool = false;
		// boal запрет всех переходов
		if (chrDisableReloadToLocation) bTmpBool = false;
		if (!CheckAttribute(loadedLocation,"fastreload")) bTmpBool = false;  // в каюте некуда переходить
		if (bTmpBool) // все еще можно переходить, провер§ем город враг
		{
		    string sNation = Colonies[FindColony(loadedLocation.fastreload)].nation;
			if (sNation != "none")
			{
				i = sti(sNation);
				bTmpBool = (GetNationRelation2MainCharacter(i) == RELATION_ENEMY) || GetRelation2BaseNation(i) == RELATION_ENEMY;
				string SNK = SKILL_SNEAK;
				int skillSNK = sti(pchar.Skill.(SNK));
				bTmpBool2 = skillSNK >= 50 && CheckNationLicence(i);
				bTmpBool3 = GetNationRelation2MainCharacter(i) != RELATION_ENEMY;
				if (bTmpBool2 && bTmpBool3) bTmpBool = false;
				if (bTmpBool && (i != PIRATE))// && !CheckAttribute(pchar, "CheckStateOk"))
				{
					bTmpBool = false;
				}
				else
				{
		    		bTmpBool = true;
				}
			}
		}
		objLandInterface.Commands.FastReload.enable	= bTmpBool;
		///// boal -->
		i = -1;
		if (CheckAttribute(pchar,"dialogready")) i=sti(pchar.dialogready);
		if (i>=0)
		{
			objLandInterface.Commands.DialogStart.enable	= true;
			if (isOfficerInShip(&Characters[i], true) || CheckAttribute(&Characters[i], "IsCompanionClone"))
			{
				objLandInterface.Commands.ItemsChange.enable = true;
			}
		}
		// boal 22.01.2004 -->
		else
		// обмен с офицером всегда и везде (в абордаже нет диалога!)
		{
		    i = LAi_FindNearestVisCharacter(pchar, 1);
		    if( i>0 && IsOfficer(GetCharacter(i)) && IsCharacterPerkOn(pchar, "SharedExperience"))
			{
				objLandInterface.Commands.ItemsChange.enable = true;
			}
		}
		//////// <--
		bUseCommand = true;
	}
	if (objLandInterface.Commands.DialogStart.enable == false && LAi_IsCharacterControl(pchar) && !LAi_IsFightMode(pchar) && !LAi_grp_alarmactive && !chrDisableReloadToLocation)
	{
    	objLandInterface.Commands.TalkSelf.enable = true;//boal разговор с каюте сам с собой
    	bUseCommand = true;
    }
	if (!LAi_IsFightMode(pchar) && !LAi_grp_alarmactive )
	{
    	objLandInterface.Commands.Craft.enable = true;//boal разговор с каюте сам с собой
    	bUseCommand = true;
    }
	if(GetCharacterPerkUsing(pchar,"Rush") && PChar.location != "FencingTown_Arena" && PChar.location != "FencingTown_ExitTown")
	{
		objLandInterface.Commands.ActivateRush.enable = true;
		bUseCommand = true;
	}
	if( CanBeUseItem(pchar) )
	{
		objLandInterface.Commands.ItemsUse.enable = true;
		bUseCommand = true;
	}
	if( CanBeUseFood(pchar) )
	{
		objLandInterface.Commands.UseFood.enable = true;
		bUseCommand = true;
	}
	if(CheckAttribute(pchar,"boxname"))
	{
		objLandInterface.Commands.UseBox.enable	= true;
		bUseCommand = true;
	}
	if( CheckAttribute(pchar,"activeItem") && pchar.activeItem!="" )
	{
		bUseCommand = true;
		if( CheckAttribute(pchar,"activeItem.pick") && pchar.activeItem.pick=="1" )
		{
			objLandInterface.Commands.TakeItem.enable = true;
		}
		else
		{
			objLandInterface.Commands.PlaceItem.enable = true;
		}
	}
	if( chrWaitReloadLocator != "" )
	{
		bUseCommand = true;
		objLandInterface.Commands.OutDoor.enable = true;
	}
    // boal dead can be searched 14.12.2003 -->
    i = Dead_FindCloseBody();
    if (i != -1)
    {
        objLandInterface.Commands.DeadBox.enable	= true;
		bUseCommand = true;
    }
	// boal dead can be searched 14.12.2003 <--
	// boal 20.03.2004 -->
    if (isShipInside(pchar.location) && !chrDisableReloadToLocation)
    {
       bUseCommand = true;
       objLandInterface.Commands.Exit_Deck.enable = true;
    }

	// ugeen  --> отслеживаем ситуацию взрыва или эпидемии на захваченном корабле --> покидание каюты мину§ интерфейс грабежа
	if(CheckAttribute(loadedLocation, "CabinType") && !chrDisableReloadToLocation)
	{
		if(CheckShipSituation_GenQuest())
		{
			bUseCommand = true;
			objLandInterface.Commands.Exit_Deck.enable = true;
		}
	}
	// <-- ugeen
    // boal 20.03.2004 <--
    // boal 20.03.2004 <--
    if (pchar.location == "Ship_deck")
    {
		if (CheckQuestAttribute("Munity", "Deads"))
		{
			bUseCommand = true;
			objLandInterface.Commands.Exit_Deck.enable = true;
		}
    }
	//objLandInterface.Commands.OutDoor.enable		= true;
	if(!bUseCommand)
	{
		SendMessage(&objLandInterface,"llllll",BI_IN_SET_COMMAND_MODE,0,-1,-1,-1,-1);
	}
}

void procFindDialogChar()
{
	int dlgChar = -1;
	if(!LAi_IsBoardingProcess())
		dlgChar = SendMessage(pchar,"ls",MSG_CHARACTER_EX_MSG,"FindDialogCharacter");

	int oldDlgChar = -1;
	if(CheckAttribute(pchar,"dialogready")) oldDlgChar = sti(pchar.dialogready);

	if(dlgChar!=oldDlgChar)
	{
		pchar.dialogready = dlgChar;
		//BLI_RefreshCommandMenu();
		LI_CareUpdateCommandList();
	}
	PostEvent("evntFindDialogChar",1000);
}

void BLI_ChrEnterToLocation()
{
	aref loc = GetEventData();
	aref chr = GetEventData();
	string group = GetEventData();
	string locator = GetEventData();
	aref locList,locCur;
	int i,n;

	if(sti(chr.index) != nMainCharacterIndex) return;

	if(group=="reload")
	{
		makearef(locList,loc.reload);
		n = GetAttributesNum(locList);
		for(i=0;i<n;i++)
		{
			locCur = GetAttributeN(locList,i);
			if(locCur.name == locator) break;
		}
		if(i<n)
		{
			i = FindLocation(locCur.go);
			if(i>=0)
			{
				if(CheckAttribute(&locations[i],"id.label"))
				{
					Log_SetStringToLog( LanguageConvertString(g_LocLngFileID,locations[i].id.label) );
				}
			}
		}
		LI_CareUpdateCommandList();
	}
}

void BLI_ChrExitFromLocation()
{
	LI_CareUpdateCommandList();
}

void LI_Reload()
{
	Event("Control Activation","s","ChrAction");
}

bool SetUsedPotionIcons()
{
	aref arItm, ar, uiref;
	int i, itmIdx, nq;

	bool bUsed = false;

	makearef(uiref,objLandInterface.UserIcons);
	nq = GetAttributesNum(uiref);
	for(i=0; i<nq; i++)
	{
		ar = GetAttributeN(uiref,i);
		if( CheckAttribute(ar,"potion") ) {
			DeleteAttribute(uiref,GetAttributeName(ar));
			nq--; i--;
		}
	}

	string UI_name;
	int UI_idx = 0;

	itmIdx = FindPotionFromChr(pchar, &arItm, 0);
	while(itmIdx>=0)
	{
		if(EnablePotionUsing(PChar, arItm) || EnableAntidoteUsing(PChar, arItm))
		{
			UI_idx++;
			UI_name = "potion"+UI_idx;
			objLandInterface.UserIcons.(UI_name).enable = true;
			objLandInterface.UserIcons.(UI_name).pic = GetPotionPicture(arItm);
            objLandInterface.UserIcons.(UI_name).selpic = GetPotionPicture(arItm) - 16;
			objLandInterface.UserIcons.(UI_name).tex = GetPotionTexture(arItm);
			objLandInterface.UserIcons.(UI_name).name = UI_name;
			objLandInterface.UserIcons.(UI_name).potion = arItm.id;
			bUsed = true;
		}
		itmIdx = FindPotionFromChr(pchar, &arItm, itmIdx+1);
	}
	return bUsed;
}

bool SetUsedFoodIcons()
{
	aref arItm, ar, uiref;
	int i, itmIdx, nq;

	bool bUsed = false;

	makearef(uiref,objLandInterface.UserIcons);
	nq = GetAttributesNum(uiref);
	for(i=0; i<nq; i++)
	{
		ar = GetAttributeN(uiref,i);
		if( CheckAttribute(ar,"Food") ) {
			DeleteAttribute(uiref,GetAttributeName(ar));
			nq--; i--;
		}
	}

	string UI_name;
	int UI_idx = 0;

	itmIdx = FindFoodFromChr(pchar, &arItm, 0);
	while(itmIdx>=0)
	{
		if( EnableFoodUsing(pchar,arItm) )
		{
			UI_idx++;
			UI_name = "Food"+UI_idx;
			objLandInterface.UserIcons.(UI_name).enable = true;
			objLandInterface.UserIcons.(UI_name).pic = GetFoodPicture(arItm);
            		objLandInterface.UserIcons.(UI_name).selpic = GetFoodSelectPicture(arItm);
			objLandInterface.UserIcons.(UI_name).tex = GetFoodTexture(arItm);
			objLandInterface.UserIcons.(UI_name).name = UI_name;
			objLandInterface.UserIcons.(UI_name).Food = arItm.id;
			bUsed = true;
		}
		itmIdx = FindFoodFromChr(pchar, &arItm, itmIdx+1);
	}

	return bUsed;
}

bool SetReloadIcons()
{
	int i, nq, locidx;
	aref ar, curloc, locref, locList, uiref;

	bool bUse = false;

	makearef(uiref,objLandInterface.UserIcons);
	nq = GetAttributesNum(uiref);
	for(i=0; i<nq; i++)
	{
		ar = GetAttributeN(uiref,i);
		if( CheckAttribute(ar,"location") ) {
			DeleteAttribute(uiref,GetAttributeName(ar));
			nq--;
			i--;
		}
	}

	int idxloc = FindLoadedLocation();
	string str1,str2,fastLocName;
	string outGroupName = "";
	if(idxloc>=0 && CheckAttribute(&Locations[idxloc],"fastreload"))
	{
		outGroupName = Locations[idxloc].fastreload;

		if( CheckAttribute(&objFastReloadTable,"table."+outGroupName) )
		{
			makearef(locList,objFastReloadTable.table.(outGroupName));
			nq = GetAttributesNum(locList);
			// to port icon
			if( GetCharacterShipType(pchar)!=SHIP_NOTUSED )
			{
				if( CheckFastJump(Locations[idxloc].id, pchar.location.from_sea) )
				{
					objLandInterface.UserIcons.port.enable = true;
					objLandInterface.UserIcons.port.pic = 26;
					objLandInterface.UserIcons.port.selpic = 10;
					objLandInterface.UserIcons.port.tex = 1;
					objLandInterface.UserIcons.port.name = "reloadtoport";
					objLandInterface.UserIcons.port.location = pchar.location.from_sea;
					objLandInterface.UserIcons.port.locator = "reload1";
					objLandInterface.UserIcons.port.note = GetNodeForIcon(1, 10);
					bUse = true;
				}
			}
			for(i=0; i<nq; i++)
			{
				curloc = GetAttributeN(locList,i);
				if(!CheckFastJump(Locations[idxloc].id, curloc.location) )
				{
					continue;
				}
				fastLocName = "fr_"+(i+1);
				objLandInterface.UserIcons.(fastLocName).enable = true;
				objLandInterface.UserIcons.(fastLocName).pic = sti(curloc.pic)+16;
				objLandInterface.UserIcons.(fastLocName).selpic = curloc.pic;
				objLandInterface.UserIcons.(fastLocName).tex = 1+sti(curloc.tex);
				objLandInterface.UserIcons.(fastLocName).name = "reload"+i;
				objLandInterface.UserIcons.(fastLocName).location = curloc.location;
				objLandInterface.UserIcons.(fastLocName).note = GetNodeForIcon(1+sti(curloc.tex), sti(curloc.pic));
				if(!CheckAttribute(Locations[idxloc],"islandId")) Locations[idxloc].islandId = 0;
				if (HasSubStr(objLandInterface.UserIcons.(fastLocName).note,"Кладбище"))
				{
					objLandInterface.UserIcons.(fastLocName).pic = 51;
					objLandInterface.UserIcons.(fastLocName).selpic = 35;
					objLandInterface.UserIcons.(fastLocName).tex = 0;
				}
				if (Locations[idxloc].islandId == "Caiman")
				{
					if (objLandInterface.UserIcons.(fastLocName).note == "Дом управляющего плантацией")
					{
						objLandInterface.UserIcons.(fastLocName).pic = 50;
						objLandInterface.UserIcons.(fastLocName).selpic = 34;
						objLandInterface.UserIcons.(fastLocName).tex = 0;
						continue;
					}
					if (objLandInterface.UserIcons.(fastLocName).note == "Дом начальника охранной базы")
					{
						objLandInterface.UserIcons.(fastLocName).pic = 49;
						objLandInterface.UserIcons.(fastLocName).selpic = 33;
						objLandInterface.UserIcons.(fastLocName).tex = 0;
						continue;
					}
				}
				if (Locations[idxloc].islandId == "Curacao" || Locations[idxloc].islandId == "SentMartin")
				{
					if (objLandInterface.UserIcons.(fastLocName).note == "Представительство ГВИК")
					{
						objLandInterface.UserIcons.(fastLocName).pic = 53;
						objLandInterface.UserIcons.(fastLocName).selpic = 37;
						objLandInterface.UserIcons.(fastLocName).tex = 0;
						continue;
					}
				}
				if (Locations[idxloc].islandId == "Barbados")
				{
					if (objLandInterface.UserIcons.(fastLocName).note == "Дом управляющего плантацией")
					{
						objLandInterface.UserIcons.(fastLocName).pic = 50;
						objLandInterface.UserIcons.(fastLocName).selpic = 34;
						objLandInterface.UserIcons.(fastLocName).tex = 0;
						continue;
					}
				}
				if (Locations[idxloc].islandId == "Cuba")
				{
					if (objLandInterface.UserIcons.(fastLocName).note == "Инквизиция")
					{
						objLandInterface.UserIcons.(fastLocName).pic = 52;
						objLandInterface.UserIcons.(fastLocName).selpic = 36;
						objLandInterface.UserIcons.(fastLocName).tex = 0;
					}
				}
				bUse = true;
			}
		}
	}
	int idLngFile = LanguageOpenFile("commands_name.txt");

	return bUse;
}

void SetOfficerTexture(int officerIdx)
{
	aref ar; makearef(ar,objLandInterface.Parameters);
	string attrName = "iconTexture"+officerIdx;

	int cn = GetOfficersIndex(pchar,officerIdx);
	if(cn<0) {
		DeleteAttribute(ar,attrName);
		ar.(attrName) = "";
	} else {
		ar.(attrName) = "interfaces\portraits\64\face_"+Characters[cn].FaceID+".tga";
	}
}

void BLI_UpdateOfficers()
{
	for(int i=0;i<=MAX_NUM_FIGHTERS;i++) {
		SetOfficerTexture(i);
	}
	for(i=0;i<=MAX_NUM_FIGHTERS;i++) {
		string sTexture;
		sTexture = "iconTexture" + i;
		SendMessage(&objLandInterface, "lls", MSG_BATTLE_LAND_SET_ICONTEX, i, objLandInterface.Parameters.(sTexture));
	}
	//End Boyer mod
	//Log_TestInfo("BLI_UpdateOfficers");
	BLI_UpdateObjectData();
	LI_CareUpdateCommandList();
	SendMessage(&objLandInterface,"ls",MSG_BATTLE_LAND_MAKE_COMMAND,"cancel");  // фикс иконок офов (рефреш) boal
}

int GetPotionPicture(aref arItm)
{
	if( CheckAttribute(arItm,"potion.pic") ) {
		return sti(arItm.potion.pic);
	}
	trace("Item "+arItm.id+ " hav`t POTION.PIC attribute");
	return 0;
}

int GetPotionTexture(aref arItm)
{
	if( !CheckAttribute(arItm,"potion.tex") ) {
		trace("Item "+arItm.id+ " hav`t POTION.TEX attribute");
		return 0;
	}
	return sti(arItm.potion.tex);
}

int GetFoodPicture(aref arItm)
{
	if( CheckAttribute(arItm,"Food.pic") ) {
		return sti(arItm.Food.pic);
	}
	return 0;
}

int GetFoodSelectPicture(aref arItm)
{
	if( CheckAttribute(arItm,"Food.selpic") ) {
		return sti(arItm.Food.selpic);
	}
	return 0;
}

int GetFoodTexture(aref arItm)
{
	if( !CheckAttribute(arItm,"Food.tex") ) {
		return 0;
	}
	return sti(arItm.Food.tex);
}

// можем ли юзать хоть что то
bool CanBeUseItem(ref chref)
{
	for(int i=0; i<ITEMS_QUANTITY; i++)
	{
		if( CheckAttribute(&Items[i],"potion") && CheckAttribute(chref,"items."+Items[i].id) ) {
			if( EnablePotionUsing(chref,&Items[i]) ) {return true;}
		}
	}
	return false;
}

bool CanBeUseFood(ref chref)
{
	for(int i=0; i<ITEMS_QUANTITY; i++)
	{
		if( CheckAttribute(&Items[i],"Food") && CheckAttribute(chref,"items."+Items[i].id) ) {
			if( EnableFoodUsing(chref,&Items[i]) ) {return true;}
		}
	}
	return false;
}
object objIconsNote;
string GetNodeForIcon(int nTex, int nPic)
{
	string attrName = nTex+"x"+nPic;
	if( CheckAttribute(objIconsNote,attrName) ) return objIconsNote.(attrName);
	return "";
}

void LI_ProcessControlPress()
{
	string ControlName = GetEventData();

	switch(ControlName)
	{
		case "hk_Cure": // TO_DO не работет - у мен§ в др месте
			if( LAi_GetCharacterRelHP(pchar) < 1.0 )
			{
				float dhlt = LAi_GetCharacterMaxHP(pchar) - LAi_GetCharacterHP(pchar);
				string btl = FindHealthForCharacter(pchar, dhlt);
				DoCharacterUsedItem(pchar, btl);
			}
		break;

		case "LICommandsActivate":
			PlaySound("interface\ok.wav"); // boal даешь звуки! 
			if(bAltInfo)
			{
				bAltInfo = false;
				ModifyTextInfo();
			}				
		break;
	}
}

void BLI_RefreshCommandMenu()
{
	SendMessage( &objLandInterface,"l",BI_MSG_CARE_COMMANDLIST_UPDATE );
}
void LI_CareUpdateCommandList()
{
	SendMessage( &objLandInterface,"l",BI_MSG_CARE_COMMANDLIST_UPDATE );
}

void SetCharacterIconData(int chrindex, aref arData)
{
	ref chref = GetCharacter(chrindex);
	arData.chrindex = chrindex;
	arData.health = LAi_GetCharacterRelHP(chref);
	arData.energy = LAi_GetCharacterRelEnergy(chref);
	arData.shootMax = LAi_GetCharacterChargeQuant(chref);
	arData.shootCur = LAi_GetCharacterChargeCur(chref);
	arData.gunprogress = LAi_GetGunChargeProgress(chref);
	if( CheckAttribute(chref,"FaceId") ) {
		if(InterfaceStates.HUDStyle) arData.texture = "battle_interface\portraits_csp\face_"+chref.FaceID+".tga";
		else arData.texture = "battle_interface\portraits\face_"+chref.FaceID+".tga";
		if( CheckAttribute(chref,"FaceUV") ) {
			arData.uv = chref.FaceUV;
		} else {
			arData.uv = "0.0,0.0,1.0,1.0";
		}
	} else {
		arData.texture = "battle_interface\two.tga";
		if( chrindex == 1 ) {
			arData.uv = "0.5,0.0,1.0,1.0";
		} else {
			arData.uv = "0.0,0.0,0.5,1.0";
		}
	}
}
