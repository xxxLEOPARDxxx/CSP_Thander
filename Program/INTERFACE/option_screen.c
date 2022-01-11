int g_nCurControlsMode = -1;
int g_ControlsLngFile = -1;

bool g_bToolTipStarted = false;

float 	fHUDRatio 	= 1.0;
int 	iHUDBase 	= screenscaling;
int 	newBase 	= screenscaling;

#define BI_LOW_RATIO 	0.25
#define BI_HI_RATIO 	4.0
#define BI_DIF_RATIO 	3.75

int CalcHUDBase(float fSlider, float MyScreen)
{
    float fRes = BI_DIF_RATIO * fSlider;
    float curBase = MyScreen / (BI_LOW_RATIO + fRes);

    return makeint(curBase + 0.5);
}

float CalcHUDSlider(float fRatio)
{
    float fRes = fRatio - BI_LOW_RATIO;
    fRes /= BI_DIF_RATIO;

    return fRes;
}

void InitInterface(string iniName)
{
	fHUDRatio = stf(Render.screen_y) / screenscaling;
    iHUDBase = makeint(screenscaling);
    newBase = iHUDBase;

	g_nCurControlsMode = -1;
	GameInterface.title = "titleOptions";
	g_ControlsLngFile = LanguageOpenFile("ControlsNames.txt");

	if( CheckAttribute(&InterfaceStates,"showGameMenuOnExit") && sti(InterfaceStates.showGameMenuOnExit) == true) {
		LoadGameOptions();
	} else {
		DeleteAttribute( &PlayerProfile, "name" );
		LoadGameOptions();
	}

	IReadVariableBeforeInit();
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);
	IReadVariableAfterInit();

	SetControlsTabMode(1);

	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("InterfaceBreak","ProcessCancelExit",0);  // boal
	SetEventHandler("eTabControlPress","procTabChange",0);
	SetEventHandler("eventBtnAction","procBtnAction",0);
	SetEventHandler("eventKeyChange","procKeyChange",0);

	SetEventHandler("CheckButtonChange","procCheckBoxChange",0);
	SetEventHandler("eSlideChange","procSlideChange",0);

	SetEventHandler("evntKeyChoose","procKeyChoose",0);
	SetEventHandler("ShowInfo", "ShowInfo", 0);
	SetEventHandler("MouseRClickUP","HideInfo",0);

	SetEventHandler("evFaderFrame","FaderFrame",0);

	SetFormatedText("TEXT_NATIONS_PIC_SETTINGS", "Иконки наций");
	SetFormatedText("TEXT_VISUAL_CIRASS_PIC_SETTINGS", "Визуал кирас");
	SetFormatedText("TEXT_FONT_QUESTBOOK_PIC_SETTINGS", "Шрифт журнала");

	aref ar; makearef(ar,objControlsState.key_codes);
	SendMessage(&GameInterface,"lsla",MSG_INTERFACE_MSG_TO_NODE,"KEY_CHOOSER", 0,ar);

	if( sti(Render.full_screen)==0 )
	{
		SetSelectable("GAMMA_SLIDE",false);
		SetSelectable("BRIGHT_SLIDE",false);
		SetSelectable("CONTRAST_SLIDE",false);
	}

	float ftmp1 = -1.0;
	float ftmp2 = -1.0;
	float ftmp3 = -1.0;
	SendMessage(&sound,"leee",MSG_SOUND_GET_MASTER_VOLUME,&ftmp1,&ftmp2,&ftmp3);
	if( ftmp1==-1.0 && ftmp2==-1.0 && ftmp3==-1.0 )
	{
		SetSelectable("MUSIC_SLIDE",false);
		SetSelectable("SOUND_SLIDE",false);
		SetSelectable("DIALOG_SLIDE",false);
	}
	//Set max perspective string (in case constants/ calc changes in AICameras.c)
	float fCamPersp = DEFAULT_CAM_PERSP + (1 / DEFAULT_CAM_PERSP_DEN);
    string sMsg = "#"+ FloatToString(fCamPersp, 3);
    //PerspMax is 17 in coll.
    SendMessage(&GameInterface,"lslls",MSG_INTERFACE_MSG_TO_NODE, "TITLES_STR", 1, 17, sMsg);
    fCamPersp = DEFAULT_LCAM_PERSP + (1 / DEFAULT_LCAM_PERSP_DEN);
    sMsg = "#"+ FloatToString(fCamPersp, 3);
    //PerspMax2 is 21 in coll.
    SendMessage(&GameInterface,"lslls",MSG_INTERFACE_MSG_TO_NODE, "TITLES_STR", 1, 21, sMsg);
    float fCamRad = DEFAULT_CAM_RAD + (1 / DEFAULT_CAM_RAD_DEN);
    sMsg = "#"+ FloatToString(fCamRad, 1);
    //CamRadMax is 24 in coll.
    SendMessage(&GameInterface,"lslls",MSG_INTERFACE_MSG_TO_NODE, "TITLES_STR", 1, 24, sMsg);

	fHUDRatio = stf(Render.screen_y) / screenscaling;
	float sl = CalcHUDSlider(fHUDRatio);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "HUD_SLIDE", 2, makeint(sl * 100.0));
	GameInterface.nodes.hud_slide.value = sl;
	iHUDBase = CalcHUDBase(sl, stf(Render.screen_y));
	SetFormatedText("HUD_DESCRIP_TEXT", Render.screen_y + "  / " + newBase + " : " + fHUDRatio);
}

void ProcessCancelExit()
{
	LoadGameOptions();
	ProcessExit();
}

void ProcessOkExit()
{
	screenscaling = newBase;

	SaveGameOptions();
	ProcessExit();
	Event("eventChangeOption");

	// change sea settings
	SetSeaGridStep(stf(InterfaceStates.SeaDetails));
	//#20171223-01 Camera perspective option
	SetPerspectiveSettings();
	//#20190815-01
	SetPerspective2Settings();
}

void ProcessExit()
{

	if(sti(InterfaceStates.EnabledCMControls) == 1)
	{
		CI_CreateAndSetControls( "Sailing3Pers", "BICommandsActivate", CI_GetKeyCode("VK_MBUTTON"), 0, true );
		CI_CreateAndSetControls( "PrimaryLand", "LICommandsActivate", CI_GetKeyCode("VK_MBUTTON"), 0, true );
		CI_CreateAndSetControls( "BattleInterfaceControls", "BICommandsConfirm", CI_GetKeyCode("VK_LBUTTON"), 0, true );
		CI_CreateAndSetControls( "BattleInterfaceControls", "BICommandsCancel", CI_GetKeyCode("VK_RBUTTON"), 0, false );
		CI_CreateAndSetControls( "BattleInterfaceControls", "BICommandsLeft", CI_GetKeyCode("VK_MWHEEL_DOWN"), 0, true );
		CI_CreateAndSetControls( "BattleInterfaceControls", "BICommandsRight", CI_GetKeyCode("VK_MWHEEL_UP"), 0, true );
	}
	else
	{
		CI_CreateAndSetControls( "Sailing3Pers", "BICommandsActivate", CI_GetKeyCode("VK_RETURN"), 0, true );
		CI_CreateAndSetControls( "PrimaryLand", "LICommandsActivate", CI_GetKeyCode("VK_RETURN"), 0, true );
		CI_CreateAndSetControls( "BattleInterfaceControls", "BICommandsConfirm", CI_GetKeyCode("VK_RETURN"), 0, true );
		CI_CreateAndSetControls( "BattleInterfaceControls", "BICommandsCancel", CI_GetKeyCode("VK_ESCAPE"), 0, false );
		CI_CreateAndSetControls( "BattleInterfaceControls", "BICommandsLeft", CI_GetKeyCode("VK_LEFT"), 0, true );
		CI_CreateAndSetControls( "BattleInterfaceControls", "BICommandsRight", CI_GetKeyCode("VK_RIGHT"), 0, true );
	}

	if( CheckAttribute(&InterfaceStates,"showGameMenuOnExit") && sti(InterfaceStates.showGameMenuOnExit) == true) {
		IDoExit(RC_INTERFACE_LAUNCH_GAMEMENU);
		return;
	}

	IDoExit(RC_INTERFACE_OPTIONSCREEN_EXIT);
	if( !CheckAttribute(&InterfaceStates,"InstantExit") || sti(InterfaceStates.InstantExit)==false ) {
		ReturnToMainMenu();
	}
}

void IDoExit(int exitCode)
{
	DelEventHandler("evntKeyChoose","procKeyChoose");
	DelEventHandler("eSlideChange","procSlideChange");
	DelEventHandler("CheckButtonChange","procCheckBoxChange");

	DelEventHandler("eventKeyChange","procKeyChange");
	DelEventHandler("eventBtnAction","procBtnAction");
	DelEventHandler("eTabControlPress","procTabChange");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ShowInfo", "ShowInfo");
	DelEventHandler("MouseRClickUP","HideInfo");
	DelEventHandler("evFaderFrame","FaderFrame");
	DelEventHandler("InterfaceBreak","ProcessCancelExit");  // boal

	LanguageCloseFile( g_ControlsLngFile );

	interfaceResultCommand = exitCode;
	if( CheckAttribute(&InterfaceStates,"InstantExit") && sti(InterfaceStates.InstantExit)==true ) {
		EndCancelInterface(true);
	} else {
		EndCancelInterface(false);
	}
	ControlsMakeInvert();
	//#20200519-02
	if(bSeaActive) {
        BattleInterface.ShifInfoVisible = InterfaceStates.enabledshipmarks;
        BattleInterface.battleborder.used = InterfaceStates.ShowBattleMode;
	}

}

void IReadVariableBeforeInit()
{
	GetSoundOptionsData();
	GetMouseOptionsData();
	GetVideoOptionsData();
}

void IReadVariableAfterInit()
{
	GetHerbOptionsData();
	GetControlsStatesData();
	GetFlagAllOptionsData();
	GetVisualCirassOptionsData();
	GetAltFontOptionsData();

	int nShowBattleMode = 0;
	if( CheckAttribute(&InterfaceStates,"ShowBattleMode") ) {
		nShowBattleMode = sti(InterfaceStates.ShowBattleMode);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"BATTLE_MODE_CHECKBOX", 2, 1, nShowBattleMode );

	int nEnabledAutoSaveMode = 1;
	if( CheckAttribute(&InterfaceStates,"EnabledAutoSaveMode") ) {
		nEnabledAutoSaveMode = sti(InterfaceStates.EnabledAutoSaveMode);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"AUTOSAVE_CHECKBOX", 2, 1, nEnabledAutoSaveMode );

	int nEnabledQuestsMarks = 1;
	if( CheckAttribute(&InterfaceStates,"EnabledQuestsMarks") ) {
		nEnabledQuestsMarks = sti(InterfaceStates.EnabledQuestsMarks);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"QUESTMARK_CHECKBOX", 2, 1, nEnabledQuestsMarks );

	int nEnabledFXMarks = 1;
	if( CheckAttribute(&InterfaceStates,"EnabledFXMarks") ) {
		nEnabledFXMarks = sti(InterfaceStates.EnabledFXMarks);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"FXMARK_CHECKBOX", 2, 1, nEnabledFXMarks );

	int nEnabledCMControls = 1;
	if( CheckAttribute(&InterfaceStates,"EnabledCMControls") ) {
		nEnabledCMControls = sti(InterfaceStates.EnabledCMControls);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CM_CONTROLS_CHECKBOX", 2, 1, nEnabledCMControls );

	int nEnabledShipMarks = 1;
	if( CheckAttribute(&InterfaceStates,"EnabledShipMarks") ) {
		nEnabledShipMarks = sti(InterfaceStates.EnabledShipMarks);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"SHIPMARK_CHECKBOX", 2, 1, nEnabledShipMarks );

	int nEnabledSimpleSea = 0;
	if( CheckAttribute(&InterfaceStates,"SimpleSea") )
	{
		nEnabledSimpleSea = sti(InterfaceStates.SimpleSea);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"SIMPLESEA_CHECKBOX", 2, 1, nEnabledSimpleSea );

	int nSpyglassTextures = 0;
	if( CheckAttribute(&InterfaceStates,"SpyglassTextures") )
	{
		nSpyglassTextures = sti(InterfaceStates.SpyglassTextures);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"SPYGLASSTEX_CHECKBOX", 2, 1, nSpyglassTextures );

	int nHUDStyle = 0;
	if( CheckAttribute(&InterfaceStates,"HUDStyle") )
	{
		nHUDStyle = sti(InterfaceStates.HUDStyle);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"HUDStyle_CHECKBOX", 2, 1, nHUDStyle );

	/*int nVISUAL_CIRASS = 0;
	if( CheckAttribute(&InterfaceStates,"VISUAL_CIRASS") )
	{
		nVISUAL_CIRASS = sti(InterfaceStates.VISUAL_CIRASS);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 1, nVISUAL_CIRASS );*/

	int nCannonsHUD = 0;
	if( CheckAttribute(&InterfaceStates,"CannonsHUD") )
	{
		nCannonsHUD = sti(InterfaceStates.CannonsHUD);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CannonsHUD_CHECKBOX", 2, 1, nCannonsHUD );

	int nShowBoardMode = 0;
	if( CheckAttribute(&InterfaceStates,"ShowBoardMode") ) {
		nShowBoardMode = sti(InterfaceStates.ShowBoardMode);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"BOARD_MODE_CHECKBOX", 2, 1, nShowBoardMode );

	int nDeadBoxText = 0;
	if( CheckAttribute(&InterfaceStates,"DeadBoxText") ) {
		nDeadBoxText = sti(InterfaceStates.DeadBoxText);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"DEADBOXTEXT_CHECKBOX", 2, 1, nDeadBoxText );

	/*int nAltFont = 0;
	if( CheckAttribute(&InterfaceStates,"AltFont") ) {
		nAltFont = sti(InterfaceStates.AltFont);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ALTFONT_CHECKBOX", 2, 1, nAltFont );*/

	int nNoInt = 0;
	if( CheckAttribute(&InterfaceStates,"NoInt") ) {
		nNoInt = sti(InterfaceStates.NoInt);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"NOINT_CHECKBOX", 2, 1, nNoInt );

	int nIslandLoader = 0;
	if( CheckAttribute(&InterfaceStates,"IslandLoader") ) {
		nIslandLoader = sti(InterfaceStates.IslandLoader);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ISLAND_LOADER_CHECKBOX", 2, 1, nIslandLoader );

	int nAltIntIcons = 0;
	if( CheckAttribute(&InterfaceStates,"AltIntIcons") ) {
		nAltIntIcons = sti(InterfaceStates.AltIntIcons);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ALT_INT_ICONS_CHECKBOX", 2, 1, nAltIntIcons );


	if(bBoardMode)
	{
		CheckButton_SetState("BOARD_MODE_CHECKBOX", 1, true);
	}
	else
	{
		CheckButton_SetState("BOARD_MODE_CHECKBOX", 1, false);
	}

	int nCharVoice = 0;
	if(bCharVoice)
	{
		nCharVoice = bCharVoice;
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CHAR_VOICE_CHECKBOX", 2, 1, nCharVoice );

}

void SetControlsTabMode(int nMode)
{
	int nColor1 = argb(255,196,196,196);
	int nColor2 = nColor1;
	int nColor3 = nColor1;
	int nColor4 = nColor1;

	string sPic1 = "TabDeSelected";
	string sPic2 = sPic1;
	string sPic3 = sPic1;
	string sPic4 = sPic1;

	switch( nMode )
	{
	case 1: // море от первого лица
		sPic1 = "TabSelected";
		nColor1 = argb(255,255,255,255);
	break;
	case 2: // режим путешествий на земле
		sPic2 = "TabSelected";
		nColor2 = argb(255,255,255,255);
	break;
	case 3: // море от 3-го лица
		sPic3 = "TabSelected";
		nColor3 = argb(255,255,255,255);
	break;
	case 4: // режим боя на земле
		sPic4 = "TabSelected";
		nColor4 = argb(255,255,255,255);
	break;
	}

	SetNewGroupPicture("TABBTN_SAILING_1ST", "TABS", sPic1);
	SetNewGroupPicture("TABBTN_PRIMARY_LAND", "TABS", sPic2);
	SetNewGroupPicture("TABBTN_SAILING_3RD", "TABS", sPic3);
	SetNewGroupPicture("TABBTN_FIGHT_MODE", "TABS", sPic4);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_SAILING_1ST", 8,0,nColor1);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_PRIMARY_LAND", 8,0,nColor2);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_SAILING_3RD", 8,0,nColor3);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_FIGHT_MODE", 8,0,nColor4);

	FillControlsList(nMode);
}

void procTabChange()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();

	if( sNodName == "TABBTN_SAILING_1ST" ) {
		SetControlsTabMode( 1 );
		return;
	}
	if( sNodName == "TABBTN_PRIMARY_LAND" ) {
		SetControlsTabMode( 2 );
		return;
	}
	if( sNodName == "TABBTN_SAILING_3RD" ) {
		SetControlsTabMode( 3 );
		return;
	}
	if( sNodName == "TABBTN_FIGHT_MODE" ) {
		SetControlsTabMode( 4 );
		return;
	}
}

void procBtnAction()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();

	if( sNodName == "BTN_OK" ) {
		if( iComIndex==ACTION_ACTIVATE || iComIndex==ACTION_MOUSECLICK ) {
			ProcessOkExit();
		}
		return;
	}
	if( sNodName == "BTN_CONTROLS_DEFAULT" ) {
		RestoreDefaultKeys(0);
		return;
	}

	if( sNodName == "BTN_CONTROLS_DEFAULT_GPK" ) {
		RestoreDefaultKeys(1);
		return;
	}
}

void procCheckBoxChange()
{
	string sNodName = GetEventData();
	int nBtnIndex = GetEventData();
	int bBtnState = GetEventData();

	if( sNodName == "HERB_CHECKBOX" ) {
		if( bBtnState==true ) {
			switch( nBtnIndex ) {
			case 1: iGrassQuality=3; break;
			case 2: iGrassQuality=2; break;
			case 3: iGrassQuality=1; break;
			case 4: iGrassQuality=0; break;
			}
		}
		return;
	}
	if( sNodName == "ALWAYS_RUN_CHECKBOX" )
	{
		{ // always run
			SetAlwaysRun( bBtnState );
		}
	}
	if( sNodName == "INVERT_MOUSE_CHECKBOX" )
	{
		{ // invert mouse
			InterfaceStates.InvertCameras = bBtnState;
		}
	}
	if( sNodName == "BATTLE_MODE_CHECKBOX" )
	{
		{ // Show battle mode border
			InterfaceStates.ShowBattleMode = bBtnState;
		}
	}
	if( sNodName == "AUTOSAVE_CHECKBOX" )
	{
		{ // Show battle mode border
			InterfaceStates.EnabledAutoSaveMode = bBtnState;
		}
	}

	if( sNodName == "QUESTMARK_CHECKBOX" )
	{
		{ // Show battle mode border
			InterfaceStates.EnabledQuestsMarks = bBtnState;
		}
	}

	if( sNodName == "FXMARK_CHECKBOX" )
	{
		{ // Show battle mode border
			InterfaceStates.EnabledFXMarks = bBtnState;
		}
	}
	if( sNodName == "CM_CONTROLS_CHECKBOX" )
	{
		{ // Show battle mode border
			InterfaceStates.EnabledCMControls = bBtnState;
		}
	}

	if( sNodName == "SHIPMARK_CHECKBOX" )
	{
		{ // Show battle mode border
			InterfaceStates.EnabledShipMarks = bBtnState;
		}
	}

	if( sNodName == "SIMPLESEA_CHECKBOX" )
	{
		{ // Show battle mode border
			InterfaceStates.SimpleSea = bBtnState;
		}
	}

	if( sNodName == "SPYGLASSTEX_CHECKBOX" )
	{
		{ // Show battle mode border
			InterfaceStates.SpyglassTextures = bBtnState;
		}
	}

	if( sNodName == "HUDStyle_CHECKBOX" )
	{
		{ // Show battle mode border
			InterfaceStates.HUDStyle = bBtnState;
		}
	}

	/*if( sNodName == "VISUAL_CIRASS_CHECKBOX" )
	{
		{ // Show battle mode border
			InterfaceStates.VISUAL_CIRASS = bBtnState;
		}
	}*/

	if( sNodName == "CannonsHUD_CHECKBOX" )
	{
		{ // Show battle mode border
			InterfaceStates.CannonsHUD = bBtnState;
		}
	}

	if( sNodName == "DEADBOXTEXT_CHECKBOX" )
	{
		{ // Show battle mode border
			InterfaceStates.DeadBoxText = bBtnState;
		}
	}

	/*if( sNodName == "ALTFONT_CHECKBOX" )
	{
		{ // Show battle mode border
			InterfaceStates.AltFont = bBtnState;
		}
	}*/

	if( sNodName == "NOINT_CHECKBOX" )
	{
		{ // Show battle mode border
			InterfaceStates.NoInt = bBtnState;
		}
	}

	if( sNodName == "ISLAND_LOADER_CHECKBOX" )
	{
		{ // Show battle mode border
			InterfaceStates.IslandLoader = bBtnState;
		}
	}

	if( sNodName == "ALT_INT_ICONS_CHECKBOX" )
	{
		{ // Show battle mode border
			InterfaceStates.AltIntIcons = bBtnState;
		}
	}

 	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "BOARD_MODE_CHECKBOX", 3, 1))
	{
		bBoardMode = true;
	}
	else
	{
		bBoardMode = false;
	}

	if( sNodName == "CHAR_VOICE_CHECKBOX")
	{
		{
			bCharVoice = bBtnState;
		}
	}

	if( sNodName == "FLAGALLWDM_CHECKBOX" )
	{
		if( bBtnState == true )
		{
			switch( nBtnIndex )
			{
				case 1:
					iFlagAllWdm=2;
					SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"FLAGALLWDM_CHECKBOX", 2, 2, false );
					SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"FLAGALLWDM_CHECKBOX", 2, 3, false );
				break;
				case 2:
					iFlagAllWdm=1;
					SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"FLAGALLWDM_CHECKBOX", 2, 1, false );
					SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"FLAGALLWDM_CHECKBOX", 2, 3, false );
				break;
				case 3:
					iFlagAllWdm=0;
					SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"FLAGALLWDM_CHECKBOX", 2, 1, false );
					SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"FLAGALLWDM_CHECKBOX", 2, 2, false );
				break;
			}
		}
		return;
	}

	if( sNodName == "VISUAL_CIRASS_CHECKBOX" )
	{
		InterfaceStates.VISUAL_CIRASS = 0

		if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "VISUAL_CIRASS_CHECKBOX", 3, 1))
		{
			InterfaceStates.VISUAL_CIRASS = sti(InterfaceStates.VISUAL_CIRASS)+1;
		}
		if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "VISUAL_CIRASS_CHECKBOX", 3, 2))
		{
			InterfaceStates.VISUAL_CIRASS = sti(InterfaceStates.VISUAL_CIRASS)+3;
		}
		if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "VISUAL_CIRASS_CHECKBOX", 3, 3))
		{
			InterfaceStates.VISUAL_CIRASS = sti(InterfaceStates.VISUAL_CIRASS)+5;
		}
		//log_testinfo(InterfaceStates.VISUAL_CIRASS);
		return;
	}

	if( sNodName == "ALTFONT_CHECKBOX" )
	{
		if( bBtnState == true )
		{
			switch( nBtnIndex )
			{
				case 1:
					InterfaceStates.AltFont=0;
					SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ALTFONT_CHECKBOX", 2, 2, false );
					SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ALTFONT_CHECKBOX", 2, 3, false );
				break;
				case 2:
					InterfaceStates.AltFont=1;
					SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ALTFONT_CHECKBOX", 2, 1, false );
					SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ALTFONT_CHECKBOX", 2, 3, false );
				break;
				case 3:
					InterfaceStates.AltFont=2;
					SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ALTFONT_CHECKBOX", 2, 1, false );
					SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ALTFONT_CHECKBOX", 2, 2, false );
				break;
			}
		}
		return;
	}
}

void procSlideChange()
{
	string sNodeName = GetEventData();
	int nVal = GetEventData();
	float fVal = GetEventData();

	if( sNodeName=="GAMMA_SLIDE" || sNodeName=="BRIGHT_SLIDE" || sNodeName=="CONTRAST_SLIDE" ) {
		ChangeVideoColor();
		return;
	}
	if( sNodeName == "SEA_DETAILS_SLIDE" ) {
		ChangeSeaDetail();
		return;
	}
	//#20171223-01 Camera perspective option
	if( sNodeName == "CAM_PERSP_SLIDE" ) {
		ChangePerspDetail();
		return;
	}
	//#20190815-01
	if( sNodeName == "CAM_PERSP_SLIDE2" ) {
		ChangePersp2Detail();
		return;
	}
	if( sNodeName == "CAM_RAD_SLIDE" ) {
		ChangeRadDetail();
		return;
	}
	if( sNodeName == "HUD_SLIDE" ) {
		ChangeHUDDetail();
		return;
	}
	if( sNodeName=="MUSIC_SLIDE" || sNodeName=="SOUND_SLIDE" || sNodeName=="DIALOG_SLIDE" ) {
		ChangeSoundSetting();
		return;
	}
	if( sNodeName=="VMOUSE_SENSITIVITY_SLIDE" || sNodeName=="HMOUSE_SENSITIVITY_SLIDE" ) {
		ChangeMouseSensitivity();
	}
}

void ChangeMouseSensitivity()
{
	InterfaceStates.mouse.x_sens = stf(GameInterface.nodes.hmouse_sensitivity_slide.value);
	InterfaceStates.mouse.y_sens = stf(GameInterface.nodes.vmouse_sensitivity_slide.value);
	SetRealMouseSensitivity();
}

void ChangeVideoColor()
{
	float fCurContrast = stf(GameInterface.nodes.contrast_slide.value);
	float fCurGamma = stf(GameInterface.nodes.GAMMA_SLIDE.value);
	float fCurBright = stf(GameInterface.nodes.BRIGHT_SLIDE.value);

	float fContrast = ConvertContrast(fCurContrast,false);
	float fGamma = ConvertGamma(fCurGamma,false);
	float fBright = ConvertBright(fCurBright,false);

	if( !CheckAttribute(&InterfaceStates,"video.contrast") ||
		(stf(InterfaceStates.video.contrast)!=fContrast) ||
		(stf(InterfaceStates.video.gamma)!=fGamma) ||
		(stf(InterfaceStates.video.brightness)!=fBright) ) {
			InterfaceStates.video.contrast = fContrast;
			InterfaceStates.video.gamma = fGamma;
			InterfaceStates.video.brightness = fBright;
			XI_SetColorCorrection(fContrast,fGamma,fBright);
	}
}

void ChangeSeaDetail()
{
	float fCurSeaDetail = stf(GameInterface.nodes.sea_details_slide.value);
	float fSeaDetail = ConvertSeaDetails(fCurSeaDetail,false);
	if( !CheckAttribute(&InterfaceStates,"SeaDetails") ||
		(stf(InterfaceStates.SeaDetails)!=fSeaDetail) ) {
			InterfaceStates.SeaDetails = fSeaDetail;
	}
}

//#20171223-01 Camera perspective option
void ChangePerspDetail()
{
    float fCurPerspDetail = stf(GameInterface.nodes.cam_persp_slide.value);
	float fPerspDetail = ConvertPerspDetails(fCurPerspDetail,false);
	if( !CheckAttribute(&InterfaceStates,"PerspDetails") ||
		(stf(InterfaceStates.PerspDetails)!=fPerspDetail) ) {
			InterfaceStates.PerspDetails = fPerspDetail;
			float fCamPersp = CalcSeaPerspective();
            string sMsg = "#"+ FloatToString(fCamPersp, 3);
            //PerspMax is 17 in coll.
            SendMessage(&GameInterface,"lslls",MSG_INTERFACE_MSG_TO_NODE, "TITLES_STR", 1, 17, sMsg);
	}
}
//#20190815-01
void ChangePersp2Detail()
{
    float fCurPerspDetail = stf(GameInterface.nodes.cam_persp_slide2.value);
	float fPerspDetail = ConvertPerspDetails(fCurPerspDetail,false);
	if( !CheckAttribute(&InterfaceStates,"Persp2Details") ||
		(stf(InterfaceStates.Persp2Details)!=fPerspDetail) ) {
			InterfaceStates.Persp2Details = fPerspDetail;
			float fCamPersp = CalcLandPerspective();
            string sMsg = "#"+ FloatToString(fCamPersp, 3);
            //PerspMax2 is 21 in coll.
            SendMessage(&GameInterface,"lslls",MSG_INTERFACE_MSG_TO_NODE, "TITLES_STR", 1, 21, sMsg);
	}
}

void ChangeRadDetail()
{
    float fCurPerspDetail = stf(GameInterface.nodes.cam_rad_slide.value);
	float fPerspDetail = ConvertRadDetails(fCurPerspDetail,false);
	if( !CheckAttribute(&InterfaceStates,"RadDetails") ||
		(stf(InterfaceStates.RadDetails)!=fPerspDetail) ) {
			InterfaceStates.RadDetails = fPerspDetail;
			float fCamPersp = CalcLandRadius();
            string sMsg = "#"+ FloatToString(fCamPersp, 1);
            //CamRadMax is 24 in coll.
            SendMessage(&GameInterface,"lslls",MSG_INTERFACE_MSG_TO_NODE, "TITLES_STR", 1, 24, sMsg);
	}
}

void ChangeSoundSetting()
{
	float fMusic = stf(GameInterface.nodes.music_slide.value);
	float fSound = stf(GameInterface.nodes.sound_slide.value);
	float fDialog = stf(GameInterface.nodes.dialog_slide.value);
	SendMessage(&sound,"lfff", MSG_SOUND_SET_MASTER_VOLUME, fSound,	fMusic,	fDialog);
}

void FillControlsList(int nMode)
{
	int n,qC,idx;
	string groupName;
	aref arGrp, arC;

	if( nMode == g_nCurControlsMode ) {return;}
	g_nCurControlsMode = nMode;
	DeleteAttribute(&GameInterface,"controls_list");
	GameInterface.controls_list.select = 0;

	groupName = GetGroupNameByMode(nMode);
	if( CheckAttribute(&objControlsState,"keygroups."+groupName) ) {
		makearef(arGrp,objControlsState.keygroups.(groupName));
		qC = GetAttributesNum(arGrp);
		idx = 0;
		for( n=0; n<qC; n++ ) {
			arC = GetAttributeN(arGrp,n);
			if( false==CheckAttribute(arC,"invisible") || arC.invisible!="1" ) {
			//if( CheckAttribute(arC,"remapping") && arC.remapping=="1" ) {
				if( AddToControlsList( idx, GetAttributeName(arC), GetAttributeValue(arC), CheckAttribute(arC,"remapping") && arC.remapping=="1" ) ) {
					idx++;
				}
			}
		}
	}
	SendMessage( &GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "CONTROLS_LIST", 0 );
}

bool AddToControlsList(int row, string sControl, string sKey, bool bRemapable)
{
	string rowname = "tr" + (row+1);
	GameInterface.controls_list.(rowname).userdata.remapable = bRemapable;
	GameInterface.controls_list.(rowname).userdata.control = sControl;
	GameInterface.controls_list.(rowname).userdata.key = sKey;
	GameInterface.controls_list.(rowname).td2.str = LanguageConvertString(g_ControlsLngFile,sControl);
	GameInterface.controls_list.(rowname).td2.textoffset = "2,-1";
	if( GameInterface.controls_list.(rowname).td2.str == "" ) {
		trace("Warning!!! " + sControl + " hav`t translate value");
	}
	if( !bRemapable ) { // выделение контролок которые нельзя поменять
		GameInterface.controls_list.(rowname).td2.color = argb(255,128,128,128);
	}
	if( CheckAttribute(&objControlsState,"key_codes."+sKey+".img") ) {
		GameInterface.controls_list.(rowname).td1.fontidx = 0;
		GameInterface.controls_list.(rowname).td1.textoffset = "-2,-1";
		GameInterface.controls_list.(rowname).td1.scale = 0.5;
		GameInterface.controls_list.(rowname).td1.str = objControlsState.key_codes.(sKey).img;
	}
	return true;
}

string GetGroupNameByMode(int nMode)
{
	switch( nMode ) {
	case 1: return "Sailing1Pers"; break;
	case 2: return "PrimaryLand"; break;
	case 3: return "Sailing3Pers"; break;
	case 4: return "FightModeControls"; break;
	}
	return "unknown";
}

void GetSoundOptionsData()
{
	float fCurMusic = 0.5;
	float fCurSound = 0.5;
	float fCurDialog = 0.5;
	SendMessage(&sound,"leee",MSG_SOUND_GET_MASTER_VOLUME,&fCurSound,&fCurMusic,&fCurDialog);
	GameInterface.nodes.music_slide.value = fCurMusic;
	GameInterface.nodes.sound_slide.value = fCurSound;
	GameInterface.nodes.dialog_slide.value = fCurDialog;
}

void GetMouseOptionsData()
{
	float fCurXSens = 0.5;
	float fCurYSens = 0.5;
	if( CheckAttribute(&InterfaceStates,"mouse.x_sens") ) {fCurXSens=stf(InterfaceStates.mouse.x_sens);}
	if( CheckAttribute(&InterfaceStates,"mouse.y_sens") ) {fCurYSens=stf(InterfaceStates.mouse.y_sens);}
	if(fCurXSens<0.0) fCurXSens = 0.0;
	if(fCurXSens>1.0) fCurXSens = 1.0;
	if(fCurYSens<0.0) fCurYSens = 0.0;
	if(fCurYSens>1.0) fCurYSens = 1.0;
	GameInterface.nodes.hmouse_sensitivity_slide.value = fCurXSens;
	GameInterface.nodes.vmouse_sensitivity_slide.value = fCurYSens;
}

void GetVideoOptionsData()
{
	float fC = 1.0;
	float fG = 1.0;
	float fB = 0.0;
	float fD = 1.0;
	//#20171223-01 Camera perspective option
	float fE = 0.0;
	//#20190815-01
	float fE2 = 0.0;
	float fR = 0.0;

	if( CheckAttribute(&InterfaceStates,"video.contrast") ) {
		fC = stf(InterfaceStates.video.contrast);
	}
	if( CheckAttribute(&InterfaceStates,"video.gamma") ) {
		fG = stf(InterfaceStates.video.gamma);
	}
	if( CheckAttribute(&InterfaceStates,"video.brightness") ) {
		fB = stf(InterfaceStates.video.brightness);
	}

	if( CheckAttribute(&InterfaceStates,"SeaDetails") ) {
		fD = stf(InterfaceStates.SeaDetails);
	}
    //#20171223-01 Camera perspective option
	if( CheckAttribute(&InterfaceStates,"PerspDetails") ) {
		fE = stf(InterfaceStates.PerspDetails);
	}
	//#20190815-01
	if( CheckAttribute(&InterfaceStates,"Persp2Details") ) {
		fE2 = stf(InterfaceStates.Persp2Details);
	}
	if( CheckAttribute(&InterfaceStates,"RadDetails") ) {
		fR = stf(InterfaceStates.RadDetails);
	}
	ISetColorCorrection( fC, fG, fB, fD, fE, fE2, fR );
}
//#20190815-01
void ISetColorCorrection(float fContrast, float fGamma, float fBright, float fSeaDetails, float fPerspDetails, float fPersp2, float fRad)
{
	float fCurContrast = ConvertContrast(fContrast,true);
	float fCurGamma = ConvertGamma(fGamma,true);
	float fCurBright = ConvertBright(fBright,true);
	float fCurSeaDetails = ConvertSeaDetails(fSeaDetails, true);

	if(fCurContrast>1.0) fCurContrast = 1.0;
	if(fCurContrast<0.0) fCurContrast = 0.0;
	if(fCurGamma>1.0) fCurGamma = 1.0;
	if(fCurGamma<0.0) fCurGamma = 0.0;
	if(fCurBright>1.0) fCurBright = 1.0;
	if(fCurBright<0.0) fCurBright = 0.0;
	if(fCurSeaDetails<0.0) fCurSeaDetails = 0.0;
	if(fCurSeaDetails>1.0) fCurSeaDetails = 1.0;
	//#20171223-01 Camera perspective option
	if(fPerspDetails<0.0) fPerspDetails = 0.0;
	if(fPerspDetails>1.0) fPerspDetails = 1.0;
	//#20190815-01
	if(fPersp2<0.0) fPersp2 = 0.0;
	if(fPersp2>1.0) fPersp2 = 1.0;
	if(fRad<0.0) fRad = 0.0;
	if(fRad>1.0) fRad = 1.0;

	GameInterface.nodes.CONTRAST_SLIDE.value = fCurContrast;
	GameInterface.nodes.GAMMA_SLIDE.value = fCurGamma;
	GameInterface.nodes.BRIGHT_SLIDE.value = fCurBright;
	GameInterface.nodes.SEA_DETAILS_SLIDE.value = fCurSeaDetails;
	GameInterface.nodes.CAM_PERSP_SLIDE.value = fPerspDetails;
	//#20190815-01
	GameInterface.nodes.CAM_PERSP_SLIDE2.value = fPersp2;
	GameInterface.nodes.CAM_RAD_SLIDE.value = fRad;

	SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"CONTRAST_SLIDE", 0,fCurContrast);
	SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"GAMMA_SLIDE", 0,fCurGamma);
	SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"BRIGHT_SLIDE", 0,fCurBright);

	SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"SEA_DETAILS_SLIDE", 0, fCurSeaDetails);
	//#20171223-01 Camera perspective option
	SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"CAM_PERSP_SLIDE", 0, fPerspDetails);
	SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"CAM_PERSP_SLIDE2", 0, fPersp2);
	SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"CAM_RAD_SLIDE", 0, fRad);

	XI_SetColorCorrection(fContrast,fGamma,fBright);
	//Set sea detail
}

float ConvertContrast(float fContrast, bool Real2Slider)
{ // контрастность от 0.75 до 1.25
	if(Real2Slider) {
		return fContrast*2.0-1.5;
	}
	return fContrast*0.5+0.75;
}

float ConvertGamma(float fGamma, bool Real2Slider)
{ // гамма от 0.5 до 2.0
	if(Real2Slider)
	{
		if(fGamma<=1.0) {return fGamma-0.5;}
		return fGamma*0.5;
	}
	if(fGamma<=0.5) {return fGamma+0.5;}
	return fGamma*2.0;
}

float ConvertBright(float fBright, bool Real2Slider)
{
	if(Real2Slider) {
		return (fBright+50.0)/100.0;
	}
	return fBright*100-50;
}

float ConvertSeaDetails(float fDetails, bool Real2Slider)
{
	return fDetails;
}
void GetHerbOptionsData()
{
	int nSelBtn = 0;
	switch( iGrassQuality ) {
	case 0: nSelBtn=4; break;
	case 1: nSelBtn=3; break;
	case 2: nSelBtn=2; break;
	case 3: nSelBtn=1; break;
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"HERB_CHECKBOX", 2, nSelBtn, true );
}

void GetFlagAllOptionsData()
{
	int nSelBtn = 0;
	switch( iFlagAllWdm ) {
	case 0: nSelBtn=3; break;
	case 1: nSelBtn=2; break;
	case 2: nSelBtn=1; break;
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"FLAGALLWDM_CHECKBOX", 2, nSelBtn, true );
}

void GetVisualCirassOptionsData()
{
	int nSelBtn = 0;
	switch( sti(InterfaceStates.VISUAL_CIRASS) )
	{
		case 0:
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 1, false );
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 2, false );
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 3, false );
		break;
		case 1:
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 1, true );
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 2, false );
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 3, false );
		break;
		case 3:
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 1, false );
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 2, true );
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 3, false );
		break;
		case 4:
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 1, true );
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 2, true );
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 3, false );
		break;
		case 5:
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 1, false );
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 2, false );
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 3, true );
		break;
		case 6:
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 1, true );
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 2, false );
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 3, true );
		break;
		case 8:
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 1, false );
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 2, true );
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 3, true );
		break;
		case 9:
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 1, true );
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 2, true );
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"VISUAL_CIRASS_CHECKBOX", 2, 3, true );
		break;
	}
}

void GetAltFontOptionsData()
{
	int nSelBtn = 0;
	switch( sti(InterfaceStates.AltFont) ) {
	case 0: nSelBtn=1; break;
	case 1: nSelBtn=2; break;
	case 2: nSelBtn=3; break;
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ALTFONT_CHECKBOX", 2, nSelBtn, true );
}

void GetControlsStatesData()
{
	int nAlwaysRun = 0;
	if( CheckAttribute(&InterfaceStates,"alwaysrun") ) {
		nAlwaysRun = sti(InterfaceStates.alwaysrun);
	}
	int nInvertCam = 0;
	if( CheckAttribute(&InterfaceStates,"InvertCameras") ) {
		nInvertCam = sti(InterfaceStates.InvertCameras);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ALWAYS_RUN_CHECKBOX", 2, 1, nAlwaysRun );
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"INVERT_MOUSE_CHECKBOX", 2, 1, nInvertCam );
}

void SetAlwaysRun(bool bRun)
{
	InterfaceStates.alwaysrun = bRun;
}

void procKeyChange()
{
	//FillControlsList();
	string srow = "tr" + GameInterface.controls_list.select;
	if( !CheckAttribute(&GameInterface,"controls_list."+srow) ) {return;}
	if( sti(GameInterface.controls_list.(srow).userdata.remapable)!=1 ) {return;}
	ChooseOtherControl();
}

void ChooseOtherControl()
{
	XI_WindowDisable("MAIN_WINDOW",true);
	XI_WindowShow("CHANGEKEY_WINDOW",true);
	SetCurrentNode("KEY_CHOOSER");
	string srow = "tr" + GameInterface.controls_list.select;
	SetFormatedText("CHANGEKEY_TEXT", XI_ConvertString("Press any key"));
	AddLineToFormatedText("CHANGEKEY_TEXT", " ");
	AddLineToFormatedText("CHANGEKEY_TEXT", GameInterface.controls_list.(srow).td2.str);
	AddLineToFormatedText("CHANGEKEY_TEXT", " ");
	AddLineToFormatedText("CHANGEKEY_TEXT", XI_ConvertString("KeyAlreadyUsed"));
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CHANGEKEY_TEXT", 8, 0, argb(255,255,128,128) );
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CHANGEKEY_TEXT", 8, 4, argb(0,255,64,64) );
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"CHANGEKEY_TEXT", 5);
}

int glob_retVal;
ref procKeyChoose()
{
	int keyIdx = GetEventData();
	int stickUp = GetEventData();

	glob_retVal = false;

	if (keyIdx == 7) {
		ReturnFromReassign();
		glob_retVal = true;
		return &glob_retVal;
	}

	if( DoMapToOtherKey(keyIdx,stickUp) )
	{
		ReturnFromReassign();
		glob_retVal = true;
	}

	return &glob_retVal;
}

void ReturnFromReassign()
{
	XI_WindowShow("CHANGEKEY_WINDOW",false);
	XI_WindowDisable("MAIN_WINDOW",false);
	SetCurrentNode("CONTROLS_LIST");
}

bool DoMapToOtherKey(int keyIdx,int stickUp)
{
	string srow = "tr" + GameInterface.controls_list.select;
	string groupName = GetGroupNameByMode( g_nCurControlsMode );
	string sControl = GameInterface.controls_list.(srow).userdata.control;
	string sKey = GameInterface.controls_list.(srow).userdata.key;


	aref arControlGroup;
	aref arKeyRoot,arKey;
	string tmpstr;
	int keyCode;

	if( stickUp )
	{
		//SetStickNotAvailable();
		return false;
	}

	makearef(arControlGroup,objControlsState.keygroups.(groupName));
	makearef(arKeyRoot,objControlsState.key_codes);
	arKey = GetAttributeN(arKeyRoot,keyIdx);
	keyCode = sti(GetAttributeValue(arKey));

	// check for not allowed keys
	if( //keyCode==sti(objControlsState.key_codes.VK_F1) ||
		keyCode==sti(objControlsState.key_codes.VK_F2) ||
		//keyCode==sti(objControlsState.key_codes.VK_F3) ||
		//keyCode==sti(objControlsState.key_codes.VK_F4) ||
		//keyCode==sti(objControlsState.key_codes.VK_F5) ||
		keyCode==sti(objControlsState.key_codes.VK_F6) ||
		//keyCode==sti(objControlsState.key_codes.VK_F7) ||
		keyCode==sti(objControlsState.key_codes.VK_F8) ||
		keyCode==sti(objControlsState.key_codes.VK_F9) )
	{
		return false;
	}

	if( CheckAttribute(arKey,"stick") && sti(arKey.stick)==true ) return false;

	if( KeyAlreadyUsed(groupName, sControl, GetAttributeName(arKey)) )
	{
		SetKeyChooseWarning( XI_ConvertString("KeyAlreadyUsed") );
		return false;
	}

	tmpstr = arControlGroup.(sControl);
	if( CheckAttribute(arKeyRoot,tmpstr+".stick") && sti(arKeyRoot.(tmpstr).stick)==true ) return false;

	int state = 0;
	if(CheckAttribute(arControlGroup,sControl+".state"))
	{	state = sti(arControlGroup.(sControl).state);	}

	CI_CreateAndSetControls( groupName,sControl,keyCode, state, true );
	GameInterface.controls_list.(srow).userdata.key = arKey;
	GameInterface.controls_list.(srow).td1.str = arKey.img;
	SendMessage( &GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "CONTROLS_LIST", 0 );
	return true;
}

void RestoreDefaultKeys(int choice)
{
	SetMouseToDefault();
	if (choice == 0)
	{
		ControlsInit(GetTargetPlatform(),false, 0);
	}
	if (choice == 1)
	{
		ControlsInit(GetTargetPlatform(),false, 1);
	}

	int nMode = g_nCurControlsMode;
	g_nCurControlsMode = -1;
	FillControlsList(nMode);
}

void SetMouseToDefault()
{
	InterfaceStates.InvertCameras = false;
	InterfaceStates.mouse.x_sens = 0.5;
	InterfaceStates.mouse.y_sens = 0.5;

	SetRealMouseSensitivity();
	SetAlwaysRun(true);

	GetControlsStatesData();
	SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"VMOUSE_SENSITIVITY_SLIDE", 0,stf(InterfaceStates.mouse.y_sens));
	SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"HMOUSE_SENSITIVITY_SLIDE", 0,stf(InterfaceStates.mouse.x_sens));
}

void ShowInfo()
{
	g_bToolTipStarted = true;
	string sHeader = "TEST";
	string sNode = GetCurrentNode();

	string sText1, sText2, sText3, sPicture, sGroup, sGroupPicture;
	sPicture = "none";
	// sGroup = "none";
	// sGroupPicture = "none";
	int xx = 256;
	int yy = 256;

	switch (sNode)
	{
		case "GAMMA_SLIDE":
			sHeader = XI_ConvertString("gamma");
			sText1 = XI_ConvertString("gamma_descr");
			sText3 = XI_ConvertString("FullScreenOnly");
		break;
		case "BRIGHT_SLIDE":
			sHeader = XI_ConvertString("Brightness");
			sText1 = XI_ConvertString("brightness_descr");
			sText3 = XI_ConvertString("FullScreenOnly");
		break;
		case "CONTRAST_SLIDE":
			sHeader = XI_ConvertString("Contrast");
			sText1 = XI_ConvertString("Contrast_descr");
			sText3 = XI_ConvertString("FullScreenOnly");
		break;
		case "SEA_DETAILS_SLIDE":
			sHeader = XI_ConvertString("Sea Detail");
			sText1 = XI_ConvertString("Sea Detail_descr");
			sText2 = XI_ConvertString("ItCanRedusePerfomance");
			sText3 = XI_ConvertString("NeedToExitFromSea");
		break;

		case "HERB_CHECKBOX":
            sHeader = XI_ConvertString("Herb Quantity");
            sText1 = XI_ConvertString("Herb Quantity_descr");
            sText2 = XI_ConvertString("ItCanRedusePerfomance");
        break;

		case "MUSIC_SLIDE":
			sHeader = XI_ConvertString("Music Volume");
			sText1 = XI_ConvertString("Music Volume_descr");
		break;

		case "SOUND_SLIDE":
			sHeader = XI_ConvertString("Sound Volume");
			sText1 = XI_ConvertString("Sound Volume_descr");
		break;

		case "DIALOG_SLIDE":
			sHeader = XI_ConvertString("Dialog Volume");
			sText1 = XI_ConvertString("Dialog Volume_descr");
		break;

		case "HUD_SLIDE":
			sHeader = XI_ConvertString("HUD_SLIDE");
			sText1 = XI_ConvertString("HUD_SLIDE_descr");
		break;

		case "ALWAYS_RUN_CHECKBOX":
			sHeader = XI_ConvertString("Always Run");
			sText1 = XI_ConvertString("Always Run_descr");
		break;

		case "INVERT_MOUSE_CHECKBOX":
			sHeader = XI_ConvertString("Invert Vertical Mouse Control");
			sText1 = XI_ConvertString("Invert Vertical Mouse Control_descr");
		break;

		case "VMOUSE_SENSITIVITY_SLIDE":
			sHeader = XI_ConvertString("Vertical Mouse Sensitivity");
			sText1 = XI_ConvertString("Vertical Mouse Sensitivity_descr");
		break;

		case "HMOUSE_SENSITIVITY_SLIDE":
			sHeader = XI_ConvertString("Horizontal Mouse Sensitivity");
			sText1 = XI_ConvertString("Horizontal Mouse Sensitivity_descr");
		break;

		case "BOARD_MODE_CHECKBOX":
			sHeader = XI_ConvertString("BOARD_MODE");
			sText1 = XI_ConvertString("BOARD_MODE_descr");
            sPicture = "INTERFACES\FaqPictures\BOARD_MODE_CHECKBOX.png";
			xx = 600;
			yy = 300;
		break;

		case "BATTLE_MODE_CHECKBOX":
			sHeader = XI_ConvertString("Show battle mode");
			sText1 = XI_ConvertString("Show battle mode_descr");
		break;

		case "AUTOSAVE_CHECKBOX":
			sHeader = XI_ConvertString("AutoSave Mode");
			sText1 = XI_ConvertString("AutoSave Mode_descr");
		break;

		case "QUESTMARK_CHECKBOX":
			sHeader = XI_ConvertString("QuestMark Mode");
			sText1 = XI_ConvertString("QuestMark Mode_descr");
            sPicture = "INTERFACES\FaqPictures\QUESTMARK_CHECKBOX.png";
			xx = 256;
			yy = 256;
		break;

		case "FXMARK_CHECKBOX":
			sHeader = XI_ConvertString("FXMark Mode");
			sText1 = XI_ConvertString("FXMark Mode_descr");
            sPicture = "INTERFACES\FaqPictures\FXMARK_CHECKBOX.png";
			xx = 256;
			yy = 256;
		break;

		case "CM_CONTROLS_CHECKBOX":
			sHeader = XI_ConvertString("CMControls Mode");
			sText1 = XI_ConvertString("CMControls Mode_descr");
		break;

		case "FLAGALLWDM_CHECKBOX":
			sHeader = XI_ConvertString("FlagAllWDM");
			sText1 = XI_ConvertString("FlagAllWDM_descr");
            sPicture = "INTERFACES\FaqPictures\FLAGALLWDM_CHECKBOX.png";
			xx = 600;
			yy = 200;
		break;

		case "SHIPMARK_CHECKBOX":
			sHeader = XI_ConvertString("ShipMark Mode");
			sText1 = XI_ConvertString("ShipMark Mode_descr");
            sPicture = "INTERFACES\FaqPictures\SHIPMARK_CHECKBOX.png";
			xx = 256;
			yy = 256;
		break;

		case "SIMPLESEA_CHECKBOX":
			sHeader = XI_ConvertString("SimpleSea Mode");
			sText1 = XI_ConvertString("SimpleSea Mode_descr");
		break;

		case "SPYGLASSTEX_CHECKBOX":
			sHeader = XI_ConvertString("SpyglassTextures_title");
			sText1 = XI_ConvertString("SpyglassTextures_desc");
            sPicture = "INTERFACES\FaqPictures\SPYGLASSTEX_CHECKBOX.png";
			xx = 448;
			yy = 448;
		break;

		case "HUDStyle_CHECKBOX":
			sHeader = XI_ConvertString("HUDStyle_title");
			sText1 = XI_ConvertString("HUDStyle_desc");
            sPicture = "INTERFACES\FaqPictures\HUDStyle_CHECKBOX.png";
			xx = 600;
			yy = 300;
		break;

		case "VISUAL_CIRASS_CHECKBOX":
			sHeader = XI_ConvertString("VISUAL_CIRASS_title");
			sText1 = XI_ConvertString("VISUAL_CIRASS_desc");
            sPicture = "INTERFACES\FaqPictures\VISUAL_CIRASS_CHECKBOX.png";
			xx = 512;
			yy = 256;
		break;

		case "CannonsHUD_CHECKBOX":
			sHeader = XI_ConvertString("CannonsHUD_title");
			sText1 = XI_ConvertString("CannonsHUD_desc");
            sPicture = "INTERFACES\FaqPictures\CannonsHUD_CHECKBOX.png";
			xx = 256;
			yy = 256;
		break;

		case "DEADBOXTEXT_CHECKBOX":
			sHeader = XI_ConvertString("DeadBoxText_title");
			sText1 = XI_ConvertString("DeadBoxText_desc");
            sPicture = "INTERFACES\FaqPictures\DEADBOXTEXT_CHECKBOX.png";
			xx = 256;
			yy = 256;
		break;

		case "ALTFONT_CHECKBOX":
			sHeader = XI_ConvertString("AltFont_title");
			sText1 = XI_ConvertString("AltFont_desc");
            sPicture = "INTERFACES\FaqPictures\ALTFONT_CHECKBOX.png";
			xx = 570;
			yy = 494;
		break;

		case "NOINT_CHECKBOX":
			sHeader = XI_ConvertString("NoInt_title");
			sText1 = XI_ConvertString("NoInt_desc");
		break;

		case "ISLAND_LOADER_CHECKBOX":
			sHeader = XI_ConvertString("IslandLoader_title");
			sText1 = XI_ConvertString("IslandLoader_desc");
		break;

		case "ALT_INT_ICONS_CHECKBOX":
			sHeader = XI_ConvertString("AltIntIcons_title");
			sText1 = XI_ConvertString("AltIntIcons_desc");
            sPicture = "INTERFACES\FaqPictures\ALT_INT_ICONS_CHECKBOX.png";
			xx = 256;
			yy = 256;
		break;

		case "CHAR_VOICE_CHECKBOX":
			sHeader = XI_ConvertString("CHAR_VOICE_CHECKBOX_header");
			sText1 = XI_ConvertString("CHAR_VOICE_CHECKBOX_desc");
            PlayVoice("Kopcapkz\Voices\Traders\Trader_man_0"+rand(9)+".ogg");
		break;

		//#20171223-01 Camera perspective option
		case "CAM_PERSP_SLIDE":
			sHeader = XI_ConvertString("cameraPersp_title");
			sText1 = XI_ConvertString("cameraPersp_desc");
		break;

		case "CAM_RAD_SLIDE":
			sHeader = XI_ConvertString("cameraRad_title");
			sText1 = XI_ConvertString("cameraRad_desc");
		break;

		case "CAM_PERSP_SLIDE2":
			sHeader = XI_ConvertString("cameraPersp2_title");
			sText1 = XI_ConvertString("cameraPersp2_desc");
		break;
	}

	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,255,255,255), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, xx, yy);
}

void HideInfo()
{
	if( g_bToolTipStarted ) {
		g_bToolTipStarted = false;
		CloseTooltip();
		SetCurrentNode("OK_BUTTON");
	}
}

bool KeyAlreadyUsed(string sGrpName, string sControl, string sKey)
{
	if( !CheckAttribute(&objControlsState,"keygroups."+sGrpName+"."+sControl) ) {return false;}
	if( objControlsState.keygroups.(sGrpName).(sControl) == sKey ) {return false;}

	bool bAlreadyUsed = false;
	int n,q, i,grp;
	aref arGrp,arCntrl, arGrpList;

	// проверка на совпадение в той же группе
	makearef(arGrp,objControlsState.keygroups.(sGrpName));
	q = GetAttributesNum(arGrp);
	for(n=0; n<q; n++)
	{
		arCntrl = GetAttributeN(arGrp,n);
		if( GetAttributeValue(arCntrl) == sKey ) {
			bAlreadyUsed = true;
			break;
		}
	}

	if( bAlreadyUsed ) {return bAlreadyUsed;}

	// найдем группу в которой эта контролка также отображается
	makearef(arGrpList, objControlsState.keygroups);
	grp = GetAttributesNum(arGrpList);
	for( i=0; i<grp; i++ )
	{
		arGrp = GetAttributeN(arGrpList,i);
		if( !CheckAttribute(arGrp,sControl) ) {continue;}

		q = GetAttributesNum(arGrp);
		for(n=0; n<q; n++)
		{
			arCntrl = GetAttributeN(arGrp,n);
			if( GetAttributeValue(arCntrl) == sKey ) {
				bAlreadyUsed = true;
				break;
			}
		}
		if( bAlreadyUsed ) {break;}
	}

	return bAlreadyUsed;
}

void SetKeyChooseWarning( string sWarningText )
{
	SendMessage(&GameInterface,"lslle",MSG_INTERFACE_MSG_TO_NODE,"CHANGEKEY_TEXT", 10, 4, &sWarningText );
	SendMessage( &GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"CHANGEKEY_TEXT", 5 );
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CHANGEKEY_TEXT", 8, 4, argb(255,255,64,64) );
	PostEvent("evFaderFrame",700,"lll",500,0,50);
}

void FaderFrame()
{
	int nTotalTime = GetEventData();
	int nCurTime = GetEventData();
	int nDeltaTime = GetEventData();

	nCurTime = nCurTime + nDeltaTime;
	if( nCurTime>nTotalTime ) {nCurTime=nTotalTime;}

	int nAlpha = 255*(nTotalTime-nCurTime) / nTotalTime;
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CHANGEKEY_TEXT", 8, 4, argb(nAlpha,255,64,64) );

	if( nCurTime<nTotalTime ) {
		PostEvent("evFaderFrame",nDeltaTime,"lll",nTotalTime,nCurTime,nDeltaTime);
	}
}

void ChangeHUDDetail()
{
    float sl = stf(GameInterface.nodes.hud_slide.value);
	newBase = CalcHUDBase(sl, stf(Render.screen_y));
	if( newBase != iHUDBase)
	{
        fHUDRatio = stf(Render.screen_y) / newBase;
		SetFormatedText("HUD_DESCRIP_TEXT", Render.screen_y + "  / " + newBase + " : " + fHUDRatio);
	}
}
