#include "storm-engine\battle_interface\msg_control.h"
#include "storm-engine\sea_ai\script_defines.h"
#include "battle_interface\landinterface.c"
#include "battle_interface\ispyglass.c"
#include "battle_interface\reload_tables.c"
#include "battle_interface\utils.c"
#include "battle_interface\ActivePerksShow.c"
#include "battle_interface\backgroundtask.c"
#include "battle_interface\WmInterface.c"

#define BI_ICONS_SHIPS_TEXTURE_NAME "battle_interface\icons.tga.tx"

#define BI_ICONS_ST_NONE		0
#define BI_ICONS_ST_MYSHIPS		1
#define BI_ICONS_ST_COMMAND		2
#define BI_ICONS_ST_TARGETING		3

#define BI_ICONS_TEXTURE_COMMAND	0
#define BI_ICONS_TEXTURE_SHIP1		1
#define BI_ICONS_TEXTURE_ABILITY	2

#define SAILDIR_POS_DIF             10000.0
#define FLAG_ENSIGN    "E"
#define FLAG_SPECIAL   "S"
#define FLAG_NONE      "N"

#define SHIP_FLAG      -2
#define SHIP_SFLAG     -3
int bi_icons_ShowType;
int bi_icons_CommandMode;

int bi_idxSelectedPicture;

object BattleInterface;

bool bDisableSailTo = false;

bool bDisableMapEnter = false;

bool bReloadCanBe = false;
bool bMapEnter = false;
bool bSailTo=false;
bool bAttack=false;
bool bAbordage = false;
bool bDefend=false;

//speak interface
bool bCanSpeak = false;
//bool bCanSneak = false;

bool bEnableIslandSailTo = false;

int BI_intRetValue;
int BI_retComValue;
int BI_ChargeState[5];
float BI_g_fRetVal;

int BI_intNRetValue[8];

object BI_objRetValue;
object objShipPointer;
// boal -->
bool boal_soundOn = true;
// boal <--

int CurrentShip = 0;
int CurrentFlag = 0;
int ShipFlagsQuantity = -1;
#event_handler("evntRandomSailDmg","ProcessRandomSailDmg");
//#event_handler("NextDay","ProcessDayRepair");
#event_handler("GetSailTextureData","procGetSailTextureData");
#event_handler("GetRiggingData","procGetRiggingData");
#event_handler("EventMastFall","procMastFall");
#event_handler("evntGetSmallFlagData","procGetSmallFlagData");
#event_handler(SHIP_CREATE,"BI_CreateShip");

void InitBattleInterface()
{
	BI_InitializeCommands();
	bi_icons_CommandMode = 0;
	BattleInterface.comstate = 0;
	BattleInterface.SelCharacter = -1;
	bi_idxSelectedPicture = -1;
	BattleInterface.boardRadius = 50;
	BattleInterface.freeDistance = MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER;

	SetParameterData();
	BattleInterface.blindSpeed = 0.003;
	BattleInterface.MaxWind = 30.0;
	BattleInterface.MaxShipSpeed = 20.0;
	if (iArcadeSails == 1)
	{
		BattleInterface.ShipSpeedScaler = (1.0 / 2.5);
	}
	else
	{
		BattleInterface.ShipSpeedScaler = (1.0 / 1.0);
	}
	BattleInterface.ShowNavigator = InterfaceStates.BattleShow.Navigator;
	BattleInterface.ShowCommands = InterfaceStates.BattleShow.Command;
	BattleInterface.MainChrIndex = nMainCharacterIndex;
	CreateEntity(&BattleInterface,"battle_interface");
	DeleteAttribute(&BattleInterface,"CommandTextures");
	DeleteAttribute(&BattleInterface,"CommandShowParam");
	LayerAddObject(SEA_EXECUTE,&BattleInterface,-1);
	LayerAddObject(SEA_REALIZE,&BattleInterface,-1);

	SetEventHandler(SHIP_DELETE,"BI_DeleteShip",0);
	SetEventHandler(SHIP_DEAD,"BI_DeadShip",0);
	SetEventHandler("BI_CommandEndChecking","BI_CommandEndChecking",0);
	SetEventHandler("BI_LaunchCommand","BI_LaunchCommand",0);
	SetEventHandler("BI_GetChargeQuantity","BI_GetChargeQuantity",0);
	SetEventHandler("BI_SetPossibleCommands","BI_SetPossibleCommands",0);
	SetEventHandler("GetCurrentCharge","GetCurrentCharge",0);
	SetEventHandler("evntGetCharacterShipClass","biGetCharacterShipClass",0);
	SetEventHandler(BI_EVENT_SET_VISIBLE,"BI_CommandVisible",0);
	SetEventHandler(BI_EVENT_SET_SEA_STATE,"BI_SetSeaState",0);
	SetEventHandler(BI_EVENT_GET_DATA,"BI_GetData",0);
	SetEventHandler(BI_EVENT_CHECK_SHIPSTATE_SHOW,"BI_GetSSShow",0);
	SetEventHandler("evntGetLandData","BI_GetLandData",0);
	SetEventHandler(BI_EVENT_GET_FORT_RELATION,"BI_GetFortRelation",0);
	SetEventHandler(EVENT_CHANGE_COMPANIONS,"RefreshBattleInterface",0);
	SetEventHandler("BI_CallUpdateShip","BI_UpdateShip",0);
	SetEventHandler("frame","BI_Frame",1);
	SetEventHandler("evntPerkAgainUsable","BI_PerkAgainUsable",0);
	SetEventHandler("evntSetUsingAbility","procSetUsingAbility",0);
	SetEventHandler("evntCheckEnableLocator","procCheckEnableLocator",0);
	SetEventHandler("evntCheckEnableShip","procCheckEnableShip",0);
	SetEventHandler("evntGetSRollSpeed","procGetSRollSpeed",0);
	SetEventHandler("DoSailHole","ProcessSailDamage",0);
	SetEventHandler("evntBISelectShip","procBISelectShip",0);

	procLoadIntoNew(); // Проинитим таблицу активных перков
	SetEventHandler("Control Activation","BI_ProcessControlPress",0);
	CreateILogAndActions(LOG_FOR_SEA);
	Log_SetActiveAction("Nothing");
	ResetTimeScale(); // boal
	//#20190424-02
    ReconnectShips();
}

ref BI_GetFortRelation()
{
	BI_intRetValue = BI_RELATION_NEUTRAL;
	aref arLoc = GetEventData();
	int chrIdx = Fort_FindCharacter(AISea.Island,"reload",arLoc.name);
	if(chrIdx>=0)
	{
		switch( SeaAI_GetRelation(chrIdx,nMainCharacterIndex) )
		{
		case RELATION_FRIEND:	BI_intRetValue = BI_RELATION_FRIEND;	break;
		case RELATION_NEUTRAL:	BI_intRetValue = BI_RELATION_NEUTRAL;	break;
		case RELATION_ENEMY:	BI_intRetValue = BI_RELATION_ENEMY;		break;
		}
	}
	/*string sColony = arLoc.colonyname;
	if (BI_intRetValue == BI_RELATION_ENEMY || CheckForDeclineLoadToColony(sColony) == 1)
	{
		bCanSneak = true;
	}      */
	return &BI_intRetValue;
}

ref BI_GetSSShow()
{
	BI_intRetValue = false;
	int charIdx = GetEventData();
	switch( GetCharacterEquipByGroup(pchar, SPYGLASS_ITEM_TYPE) )
	{
	case CHEAP_SPYGLASS:	BI_intRetValue = false;	break;
	case COMMON_SPYGLASS:	BI_intRetValue = true;	break;
	case GOOD_SPYGLASS:		BI_intRetValue = true;	break;
	case SUPERIOR_SPYGLASS:	BI_intRetValue = true;	break;
	}
	return &BI_intRetValue;
}

void BI_CommandVisible()
{
	int visibleFlag = GetEventData();
	SendMessage(&BattleInterface,"ll",BI_SET_VISIBLE,visibleFlag);
}

int bi_nReloadTarget=-1;
bool biold_bCanEnterToLand = false;
bool biold_bAbordageShipCanBe = false;
bool biold_bAbordageFortCanBe = false;
bool biold_bReloadCanBe = false;
bool biold_bMapEnter = false;
bool bOldNotEnoughBalls = false;

void BI_Frame()
{
	bool bYesUpdateCommand = false;
	if(bNotEnoughBalls!=bOldNotEnoughBalls)
	{
		bOldNotEnoughBalls = bNotEnoughBalls;
		if(bNotEnoughBalls)
		{
			SendMessage(&BattleInterface,"ll",BI_MSG_NOT_ENOUGH_BALLS_FLAG,true);
		}
		else
		{
			SendMessage(&BattleInterface,"ll",BI_MSG_NOT_ENOUGH_BALLS_FLAG,false);
		}
	}
	if(biold_bAbordageShipCanBe!=bAbordageShipCanBe)
	{
		bYesUpdateCommand = true;
		biold_bAbordageShipCanBe = bAbordageShipCanBe;
	}
	if(biold_bAbordageFortCanBe!=bAbordageFortCanBe)
	{
		bYesUpdateCommand = true;
		biold_bAbordageFortCanBe = bAbordageFortCanBe;
	}
	if(biold_bCanEnterToLand!=bCanEnterToLand)
	{
		bYesUpdateCommand = true;
		biold_bCanEnterToLand = bCanEnterToLand;
	}
	if(biold_bReloadCanBe!=bReloadCanBe)
	{
		bYesUpdateCommand = true;
		biold_bReloadCanBe = bReloadCanBe;
	}
	if(biold_bMapEnter!=bMapEnter)
	{
		bYesUpdateCommand = true;
		biold_bMapEnter = bMapEnter;
	}
	if(bYesUpdateCommand)
	{
		BI_SetCommandMode(-1,-1,-1,-1);
	}
	if(bAbordageShipCanBe)
	{
		Log_SetActiveAction("Board");
		// boal -->
		if (boal_soundOn)
		{
		    boal_soundOn = false;
            PlayVoice("interface\_GTBoard"+rand(1)+".wav");
		}
		// boal <--
		return;
	}
	if(bAbordageFortCanBe)
	{
		Log_SetActiveAction("LandTroops");
		// boal -->
		if (boal_soundOn)
		{
		    boal_soundOn = false;
            PlayVoice("interface\_Abandon0.wav");
		}
		// boal <--
		return;
	}
	if(bReloadCanBe)
	{
		Log_SetActiveAction("Reload");
		return;
	}
	if(bCanEnterToLand)
	{
		Log_SetActiveAction("Moor");
		// boal -->
		if (boal_soundOn)
		{
		    boal_soundOn = false;
            PlaySound("interface\_Yakordrop.wav");
		}
		// boal <--
		return;
	}
	// boal -->
	boal_soundOn = true;
	// boal <--
	if(bMapEnter)
	{
		Log_SetActiveAction("Map");
		return;
	}
	Log_SetActiveAction("Nothing");
}

void StartBattleInterface()
{
	bi_nReloadTarget = -1;
	bi_icons_ShowType = BI_ICONS_ST_MYSHIPS;
	BI_SetCommandMode(BI_COMMODE_MY_SHIP_SELECT,-1,-1,-1);
	BI_SetIslandData();
	InterfaceSpyGlassInit(false);
	objShipPointer.textures.friend = "battle_interface\Frendly.tga.tx";
	objShipPointer.textures.enemy = "battle_interface\Enemy.tga.tx";
	CreateEntity(&objShipPointer,"shippointer");
	LayerAddObject(SEA_EXECUTE,&objShipPointer,222222);
	LayerAddObject(SEA_REALIZE,&objShipPointer,-1);
}

void RefreshBattleInterface()
{
	BI_SetCommandMode(0,-1,-1,-1);
	SendMessage(&BattleInterface,"l",BI_MSG_REFRESH);
	BI_SetCommandMode(BI_COMMODE_MY_SHIP_SELECT,-1,-1,-1);
}

void DeleteBattleInterface()
{
    ResetTimeScale(); // boal

	Log_SetActiveAction("Nothing");
	InterfaceSpyGlassRelease();

    DeleteClass(&BattleInterface);
	DeleteClass(&objShipPointer);

	DelEventHandler(SHIP_DELETE, "BI_DeleteShip");
	DelEventHandler(SHIP_DEAD,"BI_DeadShip");
	DelEventHandler("BI_CommandEndChecking", "BI_CommandEndChecking");
	DelEventHandler("BI_LaunchCommand", "BI_LaunchCommand");
	DelEventHandler("BI_GetChargeQuantity","BI_GetChargeQuantity");
	DelEventHandler("BI_SetPossibleCommands","BI_SetPossibleCommands");
	DelEventHandler("GetCurrentCharge","GetCurrentCharge");
	DelEventHandler("evntGetCharacterShipClass","biGetCharacterShipClass");
	DelEventHandler(BI_EVENT_SET_VISIBLE,"BI_CommandVisible");
	DelEventHandler(BI_EVENT_SET_SEA_STATE,"BI_SetSeaState");
	DelEventHandler(BI_EVENT_GET_DATA,"BI_GetData");
	DelEventHandler(BI_EVENT_CHECK_SHIPSTATE_SHOW,"BI_GetSSShow");
	DelEventHandler("evntGetLandData","BI_GetLandData");
	DelEventHandler(BI_EVENT_GET_FORT_RELATION,"BI_GetFortRelation");
	DelEventHandler(EVENT_CHANGE_COMPANIONS,"RefreshBattleInterface");
	DelEventHandler("BI_CallUpdateShip","BI_UpdateShip");
	DelEventHandler("frame","BI_Frame");
	DelEventHandler("evntPerkAgainUsable","BI_PerkAgainUsable");
	DelEventHandler("evntSetUsingAbility","procSetUsingAbility");
	DelEventHandler("evntCheckEnableLocator","procCheckEnableLocator");
	DelEventHandler("evntCheckEnableShip","procCheckEnableShip");
	DelEventHandler("evntGetSRollSpeed","procGetSRollSpeed");
	DelEventHandler("Control Activation","BI_ProcessControlPress");
	DelEventHandler("DoSailHole","ProcessSailDamage");
	DelEventHandler("evntBISelectShip","procBISelectShip");

	// был сброс времени, выше поднял
	//DeleteClass(&BattleInterface);
	//DeleteClass(&objShipPointer);
}

ref BI_CommandEndChecking()
{
	BI_retComValue = 0;
	string comName = GetEventData();

	switch(comName)
	{
	// каюта
	case "BI_Cabin":
		BI_retComValue = 0;
		break;
	// выслать шлюпку для разговора --
	case "BI_Boat":
		BI_retComValue = BI_COMMODE_NEUTRAL_SHIP_SELECT+BI_COMMODE_FRIEND_SHIP_SELECT;
        BattleInterface.Commands.Boat.EffectRadius = DistanceToShipTalk;
		//--> eddy. снижаем радиус базара если взят квест мэра
		if (CheckAttribute(pchar, "GenQuest.DestroyPirate"))
		{
			BattleInterface.Commands.Boat.EffectRadius = 150;
		}
		//<-- eddy. снижаем радиус базара если взят квест мэра
		break;
	case "BI_Bomb":
		BI_retComValue = 0;
		break;
	case "cancel":
		BI_retComValue = -1;
		break;
	case "BI_Moor":
		BI_retComValue = 0;
		break;
	case "BI_SailTo":
		int iIsland = FindIsland(pchar.location);
		if(iIsland > 0 && !sti(Islands[iIsland].reload_enable))
		{
			bEnableIslandSailTo	= false;
		}
		if(bEnableIslandSailTo) {
			BI_retComValue = BI_COMMODE_MY_SHIP_SELECT+BI_COMMODE_NEUTRAL_SHIP_SELECT+BI_COMMODE_FRIEND_SHIP_SELECT+BI_COMMODE_ENEMY_SHIP_SELECT+BI_COMMODE_FRIEND_FORT_SELECT+BI_COMMODE_NEUTRAL_FORT_SELECT+BI_COMMODE_ENEMY_FORT_SELECT+BI_COMMODE_DISEASED_TOWN+BI_COMMODE_NOTDISEASED_TOWN+BI_COMMODE_LAND_SELECT; //+BI_COMMODE_ALLLOCATOR_SELECT;
		} else {
			BI_retComValue = BI_COMMODE_MY_SHIP_SELECT+BI_COMMODE_NEUTRAL_SHIP_SELECT+BI_COMMODE_FRIEND_SHIP_SELECT+BI_COMMODE_ENEMY_SHIP_SELECT;//+BI_COMMODE_ALLLOCATOR_SELECT;
		}
		if (bBettaTestMode)
		{
		    BattleInterface.Commands.SailTo.EffectRadius	= 900000;
		}
  		else
  		{
			string sSpyGlass = GetCharacterEquipByGroup(pchar, SPYGLASS_ITEM_TYPE);
			if(sSpyGlass != "")
			{
				ref rItm = ItemsFromID(sSpyGlass);
				BattleInterface.Commands.SailTo.EffectRadius	= 5000 + sti(rItm.radius);
			}
			else BattleInterface.Commands.SailTo.EffectRadius	= 5000; //boal
		}
		break;
	case "BI_Board":
		BI_retComValue = 0;
		break;
	case "BI_LandTroops":
		BI_retComValue = 0;
		break;
	case "BI_Map":
		BI_retComValue = 0;
		break;
	case "BI_Attack":
		BI_retComValue = BI_COMMODE_ENEMY_SHIP_SELECT+BI_COMMODE_ENEMY_FORT_SELECT+BI_COMMODE_ALLLOCATOR_SELECT;
        BattleInterface.Commands.Attack.EffectRadius	= 2000; //boal
		break;
	case "BI_Abordage":
		BI_retComValue = BI_COMMODE_ENEMY_SHIP_SELECT;
		BattleInterface.Commands.Abordage.EffectRadius	= 2000; //boal
		break;
	case "BI_Defend":
		BI_retComValue = BI_COMMODE_MY_SHIP_SELECT+BI_COMMODE_FRIEND_SHIP_SELECT+BI_COMMODE_FRIEND_FORT_SELECT+BI_COMMODE_ALLLOCATOR_SELECT;
		BattleInterface.Commands.Defend.EffectRadius	= 2000; //boal
		break;
	case "BI_SailAway":
		BI_retComValue = 0;
		break;
    case "BI_SailDir":
	    BI_SailDirIconSet();
		BI_retComValue = BI_COMMODE_USER_ICONS;
		break;
	case "BI_HeaveToDrift":
		BI_retComValue = 0;
		break;
	case "BI_Reload":
		BI_retComValue = 0;
		break;
	case "BI_Charge":
		BI_retComValue = BI_COMMODE_CANNON_CHARGE;
		break;
	case "BI_Speed":
		BI_retComValue = BI_COMMODE_USER_ICONS;
		break;
	case "BI_CompanionCommand":
		BI_retComValue = BI_COMMODE_MY_SHIP_SELECT+BI_COMMODE_ALLLOCATOR_SELECT;
		break;
	case "BI_Brander":
		BI_retComValue = BI_COMMODE_ENEMY_SHIP_SELECT+BI_COMMODE_ALLLOCATOR_SELECT;
		break;
	case "BI_ImmediateReload":
		BI_retComValue = 0;
		break;
	case "BI_LightRepair":
		BI_retComValue = 0;
		break;
	case "BI_InstantRepair":
		BI_retComValue = 0;
		break;
	case "BI_Turn180":
		BI_retComValue = 0;
		break;
	case "BI_SandbankManeuver":
		BI_retComValue = 0;
		break;
	case "BI_Ability":
		BI_retComValue = BI_COMMODE_ABILITY_ICONS;
		break;

	case "BI_ImmDeath":
		BI_retComValue = BI_COMMODE_NEUTRAL_SHIP_SELECT+BI_COMMODE_FRIEND_SHIP_SELECT+BI_COMMODE_ENEMY_SHIP_SELECT+BI_COMMODE_FRIEND_FORT_SELECT+BI_COMMODE_NEUTRAL_FORT_SELECT+BI_COMMODE_ENEMY_FORT_SELECT;
		BattleInterface.Commands.ImmediateDeath.EffectRadius	= 900000;
	break;
	case "BI_InstantBoarding":
		BI_retComValue = BI_COMMODE_NEUTRAL_SHIP_SELECT+BI_COMMODE_FRIEND_SHIP_SELECT+BI_COMMODE_ENEMY_SHIP_SELECT;
	break;
	//speak interface
	case "BI_Speak":
		BI_retComValue = BI_COMMODE_NEUTRAL_SHIP_SELECT+BI_COMMODE_FRIEND_SHIP_SELECT+BI_COMMODE_ENEMY_SHIP_SELECT;
		BattleInterface.Commands.Speak.EffectRadius	= 500;
	break;

	/*case "BI_Sneak":
		BI_retComValue = BI_COMMODE_ENEMY_TOWN;
		BattleInterface.Commands.Sneak.EffectRadius	= 1000; //boal
	break;
	*/
	}

	return &BI_retComValue;
}
void BI_SailDirIconSet()
{
    BattleInterface.UserIcons.ui1.enable = false;
    BattleInterface.UserIcons.ui2.enable = false;
    BattleInterface.UserIcons.ui3.enable = false;

    BattleInterface.UserIcons.ui4.enable = true;
    BattleInterface.UserIcons.ui5.enable = true;
    BattleInterface.UserIcons.ui6.enable = true;
    BattleInterface.UserIcons.ui7.enable = true;
    BattleInterface.UserIcons.ui8.enable = true;
    BattleInterface.UserIcons.ui9.enable = true;
    BattleInterface.UserIcons.ui10.enable = true;
    BattleInterface.UserIcons.ui11.enable = true;
}

void BI_SailSpeedIconSet()
{
    BattleInterface.UserIcons.ui1.enable = true;
    BattleInterface.UserIcons.ui2.enable = true;
    BattleInterface.UserIcons.ui3.enable = true;

    BattleInterface.UserIcons.ui4.enable = false;
    BattleInterface.UserIcons.ui5.enable = false;
    BattleInterface.UserIcons.ui6.enable = false;
    BattleInterface.UserIcons.ui7.enable = false;
    BattleInterface.UserIcons.ui8.enable = false;
    BattleInterface.UserIcons.ui9.enable = false;
    BattleInterface.UserIcons.ui10.enable = false;
    BattleInterface.UserIcons.ui11.enable = false;
}

void BI_LaunchCommand()
{
	bool bOk;
	int charIdx = GetEventData();
	string commandName = GetEventData();
	int targetNum = GetEventData();
	string locName = GetEventData();
	ref chRef = GetCharacter(charIdx);
	if( LAi_IsDead(chRef) ) return;

	aref arFader;
	if( GetEntity(arFader,"fader") ) {return;}

	if(targetNum==-1 && locName=="cancel") {
		SendMessage(&BattleInterface,"ls",MSG_BATTLE_LAND_MAKE_COMMAND,"cancel");
		return;
	}
	if(commandName=="cancel") {
		SendMessage(&BattleInterface,"ls",MSG_BATTLE_LAND_MAKE_COMMAND,"cancel");
		return;
	}

	string alternativeCommand;
	if( CheckAttribute( &BattleInterface, "AbilityIcons."+commandName+".quest" ) )
	{
		alternativeCommand = commandName;
		commandName = "BI_UseItemAbilitie";
	}

	switch(commandName)
	{
    case "BI_Cabin":
        Sea_CabinStartNow();
		break;
	case "BI_Boat":
		if (!CheckAttribute(Characters[targetNum], "LockBoat"))
		{
			// Warship 09.07.09 Мэри Селест
			// Второй раз на нее выслать шлюпку низя
			if(Characters[targetNum].id != "MaryCelesteCapitan" || PChar.QuestTemp.MaryCeleste != "OnDeck")
			{
				Sea_DeckBoatLoad(targetNum);
			}
			else
			{
				PlaySound("interface\knock.wav");
			}
		}
		else
		{
			PlaySound("interface\knock.wav");
		}
    break;
	 case "BI_Bomb":
        if (GetCargoGoods(chRef, GOOD_POWDER) >= 200 && GetRemovable(chRef)) SetMineFree(chRef, 1); // fix ugeen 21.12.13
		else PlaySound("interface\knock.wav");
		break;
	case "BI_Charge":
		int chargeType=GOOD_BALLS;
		switch(targetNum)
		{
		case 1:
			//Log_SetStringToLog("Cannonballs");
			PlayVoice("interface\_balls.wav");
			chargeType=GOOD_BALLS;
			break;
		case 2:
			//Log_SetStringToLog("Grapes");
			PlayVoice("interface\_grapes.wav");
			chargeType=GOOD_GRAPES;
			break;
		case 3:
			//Log_SetStringToLog("Knippels");
			PlayVoice("interface\_chain.wav");
			chargeType=GOOD_KNIPPELS;
			break;
		case 4:
			//Log_SetStringToLog("Bombs");
			PlayVoice("interface\_bombs.wav");
			chargeType=GOOD_BOMBS;
			break;
		}
		Ship_ChangeCharge(chRef, chargeType);
		// исходим из того, что приказы через команды дают токо ГГ и его офам, офы выбирают какой снаряд, поэтому команду запоминаем для них
		chRef.ShipCannonChargeType = chargeType;
		break;
	case "BI_Map":
		if (bMapEnter)  // boal не помню уже зачем, в ВМЛ было
        {
            //pchar.location = "";
			Sea_MapLoad();
        }
        else
        {
            Log_SetStringToLog("Выход на карту закрыт.");
        }
		break;
	case "BI_Moor":
		Sea_LandLoad();
		break;
	case "BI_Board":
		Sea_AbordageLoad(SHIP_ABORDAGE,true);
		break;
	case "BI_LandTroops":
		Sea_AbordageLoad(FORT_ABORDAGE,true);
		break;
	case "BI_SailAway":
		if (CheckAttribute(&characters[charIdx], "SeaAI.Task.Target"))  //fix
		{
			Ship_SetTaskRunAway(SECONDARY_TASK, charIdx, sti(characters[charIdx].SeaAI.Task.Target));
			PlayVoice("INTERFACE\SignalCompanion.wav");
		}
		else
		{
			Ship_SetTaskRunAway(SECONDARY_TASK, charIdx, GetMainCharacterIndex()); // boal fix если вдруг нет, то от ГГ удаляться
			PlayVoice("INTERFACE\SignalCompanion.wav");
		}
	break;
	case "BI_HeaveToDrift":
		Ship_SetTaskDrift(SECONDARY_TASK,charIdx);
		PlayVoice("INTERFACE\_strike_down.wav");
		break;
	case "BI_Defend":
		Ship_SetTaskDefend(SECONDARY_TASK,charIdx,GetTargChrIndex(targetNum,locName));
		PlayVoice("INTERFACE\SignalCompanion.wav");
		DeleteAttribute(chRef, "ShipCannonChargeType"); // флаг офов, чем пулять постоянно, ставится игроком командами, до след приказа Атака или конца снарядов
		break;
	case "BI_Attack":
		Ship_SetTaskAttack(SECONDARY_TASK,charIdx,GetTargChrIndex(targetNum,locName));
		PlayVoice("INTERFACE\SignalCompanion.wav");
		DeleteAttribute(chRef, "ShipCannonChargeType"); // флаг офов, чем пулять постоянно, ставится игроком командами, до след приказа Атака или конца снарядов
	break;
	case "BI_Abordage":
		Ship_SetTaskAbordage(SECONDARY_TASK,charIdx,GetTargChrIndex(targetNum,locName));
	break;
	case "BI_Reload":
		if(bi_nReloadTarget!=-1)
		{
			LaunchTransferMain(chRef, GetCharacter(bi_nReloadTarget), "Transfer");
		}
		break;
	case "BI_SailTo":
	    if (bDisableMapEnter && !bBettaTestMode)
	    {
           PlaySound("interface\knock.wav");
	       break;
	    }
	    if (!CheckEnemyCompanionDistance2GoAway(false) && !bBettaTestMode)  // компаньон в беде
	    {
           PlaySound("interface\knock.wav");
	       break;
	    }
	    // boal 09.02.2004 <--
		if (targetNum == -1)
		{ // приплыть в локатор с именем locName
            bOk = true;

			if (MOD_SKILL_ENEMY_RATE >= 2 && !bBettaTestMode)
            {
                targetNum = Fort_FindCharacter(AISea.Island,"reload",locName);
                if (targetNum == -1)
                {
                    // тут нужна проверка на город-враг ищем форт по порту
                    targetNum = Fort_FindCharacterByPort(AISea.Island, locName);
                }
            }
			if (targetNum >= 0)
			{
				if (GetRelation(sti(pchar.index), targetNum) == RELATION_ENEMY && !CheckAttribute(&Characters[targetNum], "CanBeSailTo"))
				{
                  	if (sti(Characters[targetNum].Fort.Mode) == FORT_NORMAL)
					{
						bOk = false;
					}
				}
			}
			if (bOk)
   			{
    			if( !IsEntity(&SailToFader) ) {trace("SailToLocator : " + locName); SeaAI_SailToLocator(locName); }
			}
			else
			{
                PlaySound("interface\knock.wav");
			}
		}
		else
		{ // догнать перса с индексом targetNum
		    // boal плывем только к друзьям или спец персам (потопить пирата) -->
            if (GetRelation(sti(pchar.index), targetNum) != RELATION_ENEMY || CheckAttribute(&Characters[targetNum], "CanBeSailTo") || bBettaTestMode)
            {
			    if( !IsEntity(&SailToFader) ) {SeaAI_SailToCharacter(targetNum); }
			}
			else
			{
                PlaySound("interface\knock.wav");
			}
			// boal плывем только к друзьям или спец персам (потопить пирата) <--
		}
		break;
	case "BI_Speed":
		switch(locName)
		{
		case "sail_none":
			Ship_SetSailState(charIdx,0.0);
		break;
		case "sail_midi":
			Ship_SetSailState(charIdx,0.5);
		break;
		case "sail_fast":
			Ship_SetSailState(charIdx,1.0);
		break;
		}
		break;
	case "BI_SailDir":
        float posX = stf(Characters[charIdx].Ship.Pos.x);
        float posZ = stf(Characters[charIdx].Ship.Pos.z);
        float fAng;
        switch(locName)
		{
			case "dir_n":
				posZ += SAILDIR_POS_DIF;
				Ship_SetTaskMove(SECONDARY_TASK, charIdx, posX, posZ);
				PlayVoice("INTERFACE\SignalCompanion.wav");
			break;
			case "dir_ne":
				fAng = PIm2 * 0.125;
				posX = posX + sin(fAng) * SAILDIR_POS_DIF;
				posZ = posZ + cos(fAng) * SAILDIR_POS_DIF;
				Ship_SetTaskMove(SECONDARY_TASK, charIdx, posX, posZ);
				PlayVoice("INTERFACE\SignalCompanion.wav");
			break;
			case "dir_e":
				posX += SAILDIR_POS_DIF;
				Ship_SetTaskMove(SECONDARY_TASK, charIdx, posX, posZ);
				PlayVoice("INTERFACE\SignalCompanion.wav");
			break;
			case "dir_se":
				fAng = PIm2 * 0.375;
				posX = posX + sin(fAng) * SAILDIR_POS_DIF;
				posZ = posZ + cos(fAng) * SAILDIR_POS_DIF;
				Ship_SetTaskMove(SECONDARY_TASK, charIdx, posX, posZ);
				PlayVoice("INTERFACE\SignalCompanion.wav");
			break;
			case "dir_s":
				posZ -= SAILDIR_POS_DIF;
				Ship_SetTaskMove(SECONDARY_TASK, charIdx, posX, posZ);
				PlayVoice("INTERFACE\SignalCompanion.wav");
			break;
			case "dir_sw":
				fAng = PIm2 * 0.625;
				posX = posX + sin(fAng) * SAILDIR_POS_DIF;
				posZ = posZ + cos(fAng) * SAILDIR_POS_DIF;
				Ship_SetTaskMove(SECONDARY_TASK, charIdx, posX, posZ);
				PlayVoice("INTERFACE\SignalCompanion.wav");
			break;
			case "dir_w":
				posX -= SAILDIR_POS_DIF;
				Ship_SetTaskMove(SECONDARY_TASK, charIdx, posX, posZ);
				PlayVoice("INTERFACE\SignalCompanion.wav");
			break;
			case "dir_nw":
				fAng = PIm2 * 0.875;
				posX = posX + sin(fAng) * SAILDIR_POS_DIF;
				posZ = posZ + cos(fAng) * SAILDIR_POS_DIF;
				Ship_SetTaskMove(SECONDARY_TASK, charIdx, posX, posZ);
				PlayVoice("INTERFACE\SignalCompanion.wav");
			break;
		}
        break;
	case "BI_CompanionCommand":
		BI_SetSpecCommandMode(BI_COMMODE_COMMAND_SELECT,-1,-1,targetNum,1);
		return;
		break;
	case "BI_ImmDeath":
		if(targetNum==-1)
		{ // смерть форта
			targetNum = Fort_FindCharacter(AISea.Island,"reload",locName);
			if(targetNum>=0)
			{
				Fort_SetAbordageMode(pchar, GetCharacter(targetNum));
			}
		}
		else
		{
			ShipDead(targetNum,KILL_BY_BALL,nMainCharacterIndex);
		}
		break;
	case "BI_InstantBoarding":
  		ActivateCharacterPerk(GetCharacter(charIdx),"InstantBoarding");
		CharacterPerkOff(GetCharacter(charIdx),"InstantBoarding");
		if( CheckSuccesfullBoard(GetCharacter(charIdx),GetCharacter(targetNum)) ) {
			Sea_AbordageStartNow(SHIP_ABORDAGE,targetNum,true,true);
		} else {
			Log_SetStringToLog( XI_ConvertString("failed to board") );
			Event("BI_LaunchCommand","lsls", charIdx, "BI_SailTo", targetNum, locName);
			return;
		}
		break;
	case "BI_Brander":
		//ActivateCharacterPerk(pchar,"Brander"); - многоразовый приказ
		Ship_SetTaskBrander(SECONDARY_TASK, charIdx, targetNum);
		PlayVoice("INTERFACE\SignalCompanion.wav");
		break;
	case "BI_ImmediateReload":
		ActivateCharacterPerk(GetCharacter(charIdx),"ImmediateReload");
		PlayVoice("INTERFACE\SignalCompanion.wav");
		break;
	case "BI_LightRepair":
		ActivateCharacterPerk(GetCharacter(charIdx),"LightRepair");
		ActivateSpecRepair(GetCharacter(charIdx),0);
		PlayVoice("INTERFACE\SignalCompanion.wav");
		break;
	case "BI_InstantRepair":
		ActivateCharacterPerk(GetCharacter(charIdx),"InstantRepair");
		ActivateSpecRepair(GetCharacter(charIdx),1);
		PlayVoice("INTERFACE\SignalCompanion.wav");
		break;
	case "BI_Turn180":
		ActivateCharacterPerk(GetCharacter(charIdx),"Turn180");
		Ship_Turn180(GetCharacter(charIdx));
		PlayVoice("INTERFACE\SignalCompanion.wav");
		break;
	case "BI_SandbankManeuver":
		ActivateCharacterPerk(GetCharacter(charIdx),"SandbankManeuver");
		PlayVoice("INTERFACE\SignalCompanion.wav");
		break;
	// items abilities
	case "BI_UseItemAbilitie":
		CompleteQuestName( BattleInterface.AbilityIcons.(alternativeCommand).quest, "");
	break;
	case "BI_Speak":
		if(LAi_IsDead(GetCharacter(targetNum)) == false)
		{
			Sea_Speak(GetCharacter(targetNum), nMainCharacterIndex, -1);
		}
	break;
	/*case "BI_Ability":
  		Event("evntSetUsingAbility","l", charIdx);
	break;*/
	}

	//BI_SetCommandMode(BI_COMMODE_MY_SHIP_SELECT,-1,-1,-1);
	BI_SetSpecCommandMode(BI_COMMODE_MY_SHIP_SELECT,-1,-1,-1, 0);
}

void BI_SetIslandData()
{
    if( !CheckAttribute(AISea,"Island"))
	{
		trace("BI_SetIslandData - has bug");
		return; // boal 26.03.04 fix
	}
	int isln = FindIsland(AISea.Island);
	if(isln==-1) return;

	ref atmp;
	atmp = GetIslandByIndex(isln);
	SendMessage(&BattleInterface,"la",BI_MSG_SET_ISLAND,atmp);
}

void BI_UpdateShip()
{
	int charIndex = GetEventData();
	AddShipToInterface(charIndex);
}

void BI_CreateShip()
{
	int charIndex = GetEventData();
	if(charIndex>=0) ClearActiveChrPerks(GetCharacter(charIndex));
	if( IsEntity(&BattleInterface) ) {
		AddShipToInterface(charIndex);
	}
}

void AddShipToInterface(int charIndex)
{
	if(charIndex==-1)
	{
		Trace("ERROR: Invalid character index for create ship");
		return;
	}
	ref chRef = GetCharacter(charIndex);
	int st = GetCharacterShipType(chRef);
	if( st==SHIP_NOTUSED )
	{
		Trace("WARNING!!! Character id = "+chRef.id+" hav`t ship.");
		return;
	}
	ref shipRef = GetRealShip(st);
	ref mainChRef = GetMainCharacter();
	int idx, i;

	if(CheckAttribute(chRef,"curshipnum"))
	{
		idx = sti(chRef.curshipnum);
	}
	else
	{
		for(i = 0; i < MAX_SHIPS_ON_SEA; i++)
		{
			if(Ships[i] == charIndex)
			{
				idx = i;
				chRef.curshipnum = i;
			}
		}
	}
	if (idx < 0)
	{
		for(i = 0; i < 4; i++)
		{
			if (GetCompanionIndex(mainChRef, i) >= 0 && GetRemovable(GetCharacter(GetCompanionIndex(mainChRef, i))))
			{
				if (GetCompanionIndex(mainChRef, i) == charIndex)
				{
					idx = i;
					chRef.curshipnum = i;
				}
			}
		}
	}
	int myShip = false;
	int shipRelation = BI_RELATION_NEUTRAL;
	switch( SeaAI_GetRelation(charIndex,nMainCharacterIndex) )
	{
	case RELATION_FRIEND:
		shipRelation = BI_RELATION_FRIEND;
		break;
	case RELATION_ENEMY:
		shipRelation = BI_RELATION_ENEMY;
		break;
	}

	for(i=0; i<COMPANION_MAX; i++)
	{
		if(GetCompanionIndex(pchar,i) == charIndex)
		{
			myShip = true;
		}
	}


	if( CharacterIsDead(chRef) )
	{
		if( !CheckAttribute(chRef,"ship.shipsink") || sti(chRef.ship.shipsink)==false )
			return;
	}

	if (myShip != true)
	{
		bCanSpeak = true;
	}
	//заглушка, убирающая интерфейс разговоров в море.
	//кому из аддонщиков будет интересно привести систему разговоров в норм - раскоментарьте
	//а у нас поставили сроки жесткие, програмеры в отпуске, и я банально не успеваю все оттестить
	//и поправить, ибо некоторые баги програмерские
	//для изьятия заглушки удалите нах следующую строчку
	//bCanSpeak = false;

	SendMessage(&BattleInterface,"llaall",BI_IN_CREATE_SHIP,charIndex,chRef,shipRef,myShip,shipRelation);
}

void BI_DeleteShip()
{
	/*int charIndex = GetEventData();
	if(charIndex==-1)
	{
		Trace("ERROR: Invalid character index");
		return;
	}
	if( IsCompanion(GetCharacter(charIndex)) )
	{
		RemoveCharacterCompanion(pchar,GetCharacter(charIndex));
	}
	DeleteAttribute(GetCharacter(charIndex),"ship.shipsink");
	DeleteAttribute(GetCharacter(charIndex),"curshipnum");
	//#20190625-02
    ref achr = GetCharacter(charIndex);
    SendMessage(&AISea, "la", AI_MESSAGE_CHARACTER_REMOVE, achr);
    bool bFound = false;
    int newNum = 0;
    int chkShips[32]; //MAX_SHIPS_IN_LOCATION	32
    for (int i=0; i<iNumShips; i++)
    {
        if (Ships[i] > 0 && Ships[i] < TOTAL_CHARACTERS)
        {
            if(Ships[i] == charIndex) continue;
            chkShips[newNum] = Ships[i];
            newNum++
        }
    }
    for (i=0; i<newNum; i++)
    {
        Ships[i] = chkShips[i];
    }
    for (i=newNum; i<iNumShips; i++)
    {
        Ships[i] = -1;
    }
    iNumShips = newNum;

	RefreshBattleInterface();*/
	int charIndex = GetEventData();
	if(charIndex==-1)
	{
		Trace("ERROR: Invalid character index");
		return;
	}
	if( IsCompanion(GetCharacter(charIndex)) )
	{
		RemoveCharacterCompanion(pchar,GetCharacter(charIndex));
	}
	DeleteAttribute(GetCharacter(charIndex),"ship.shipsink");
	RefreshBattleInterface();
}

void BI_DeadShip()
{
	int charIndex = GetEventData();
	if(charIndex==-1)
	{
		Trace("ERROR: Invalid character index");
		return;
	}
	if( IsCompanion(GetCharacter(charIndex)) )
	{
		RemoveCharacterCompanion(pchar,GetCharacter(charIndex));
	}
	Characters[charIndex].ship.shipsink = true;
	RefreshBattleInterface();
}

void BI_SetCommandMode(int commode, int texNum, int picNum, int chIdx)
{
	bi_icons_CommandMode = commode;
	SendMessage(&BattleInterface,"llllll",BI_IN_SET_COMMAND_MODE,commode,texNum,picNum,chIdx,-1);
}

void BI_SetSpecCommandMode(int commode, int texNum, int picNum, int chIdx, int comState)
{
	bi_icons_CommandMode = commode;
	SendMessage(&BattleInterface,"llllll",BI_IN_SET_COMMAND_MODE,commode,texNum,picNum,chIdx,comState);
}

void BI_SetPossibleCommands()
{
	int chIdx = GetEventData();
	int mainIdx = sti(pchar.index);

	if( chIdx<0 || CharacterIsDead(GetCharacter(chIdx)) )
	{
		aref aroot,arcur;
		makearef(aroot,BattleInterface.Commands);
		int q = GetAttributesNum(aroot);
		for(int i=0; i<q; i++)
		{
			arcur = GetAttributeN(aroot,i);
			arcur.enable = false;
		}
		//BattleInterface.Commands.Cancel.enable = true;
		return;
	}

	// для главного персонажа
	if(mainIdx==chIdx)
	{
		//speak interface
		BattleInterface.Commands.ImmediateDeath.enable	= bBettaTestMode; // boal cheat
		BattleInterface.Commands.InstantBoarding.enable	= bBettaTestMode; // boal cheat
		//BattleInterface.Commands.Speak.enable			= bCanSpeak;
		//BattleInterface.Commands.Sneak.enable			= bCanSneak;

		BattleInterface.Commands.Moor.enable			= bCanEnterToLand;
		BattleInterface.Commands.Board.enable			= bAbordageShipCanBe;
		BattleInterface.Commands.SailAway.enable		= false;
		BattleInterface.Commands.HeaveToDrift.enable	= false;
		BattleInterface.Commands.Charge.enable			= CheckAttribute(pchar,"Ship.Cannons.Charge.Type");
		BattleInterface.Commands.LandTroops.enable		= bAbordageFortCanBe;
		BattleInterface.Commands.Attack.enable			= false;
		BattleInterface.Commands.Defend.enable			= false;
		BattleInterface.Commands.Reload.enable			= bReloadCanBe;
		BattleInterface.Commands.Abordage.enable		= false;
		BattleInterface.Commands.SailTo.enable			= !bDisableSailTo && bSailTo;
		BattleInterface.Commands.SailDir.enable			= false;
		/*if( !bEnableIslandSailTo && iArcadeSailTo != 1)
		{
			BattleInterface.Commands.SailTo.enable		= false;
		}*/
		BattleInterface.Commands.Map.enable				= bMapEnter;
		BattleInterface.Commands.Speed.enable			= true;
		//BattleInterface.Commands.CCommand.enable		= GetCompanionQuantity(pchar)>1;
		//BattleInterface.Commands.Ability.enable			= true;
		//  проверка на 7 класс
		if (sti(RealShips[sti(pchar.Ship.Type)].BaseType) > SHIP_WAR_TARTANE)
        {
            BattleInterface.Commands.Cabin.enable		= true;
        }
        BattleInterface.Commands.Boat.enable           = true;
	}
	// для спутников
	else
	{
		BattleInterface.Commands.Moor.enable			= false;
		BattleInterface.Commands.Board.enable			= false;
		BattleInterface.Commands.SailAway.enable		= true;
		BattleInterface.Commands.HeaveToDrift.enable	= true;
		BattleInterface.Commands.Charge.enable			= CheckAttribute(GetCharacter(chIdx),"Ship.Cannons.Charge.Type"); //false;
		BattleInterface.Commands.LandTroops.enable		= false;
		BattleInterface.Commands.Attack.enable			= bAttack;
		BattleInterface.Commands.Abordage.enable		= bAbordage;
		BattleInterface.Commands.Defend.enable			= bDefend;
		BattleInterface.Commands.Reload.enable			= false;
		BattleInterface.Commands.SailTo.enable			= false;
		BattleInterface.Commands.SailDir.enable			= true;
		BattleInterface.Commands.Map.enable				= false;
		BattleInterface.Commands.Speed.enable			= false;
		//BattleInterface.Commands.CCommand.enable		= false;
		//BattleInterface.Commands.Ability.enable			= true;
		BattleInterface.Commands.Speak.enable			= false;
		//BattleInterface.Commands.Sneak.enable			= false;
		BattleInterface.Commands.ImmediateDeath.enable  = false; // boal
		BattleInterface.Commands.InstantBoarding.enable  = false; // boal
		BattleInterface.Commands.Cabin.enable			= false;
        BattleInterface.Commands.Boat.enable			= false; //boal
	}
    Event("evntSetUsingAbility","l", chIdx);
}

void BI_InitializeCommands()
{
	int idLngFile = LanguageOpenFile("commands_name.txt");

	DeleteAttribute(&BattleInterface,"Commands");
	DeleteAttribute(&BattleInterface,"AbilityIcons");

	BattleInterface.Commands.Cancel.enable			= false;
	BattleInterface.Commands.Cancel.picNum			= 1;
	BattleInterface.Commands.Cancel.selPicNum		= 0;
	BattleInterface.Commands.Cancel.texNum			= 2;
	BattleInterface.Commands.Cancel.event			= "Cancel";
	BattleInterface.Commands.Cancel.note			= LanguageConvertString(idLngFile, "sea_Cancel");

	BattleInterface.Commands.Moor.enable			= false;
	BattleInterface.Commands.Moor.picNum			= 29;
	BattleInterface.Commands.Moor.selPicNum			= 13;
	BattleInterface.Commands.Moor.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Moor.event				= "BI_Moor";
	BattleInterface.Commands.Moor.note				= LanguageConvertString(idLngFile, "sea_Moor");
	//
	BattleInterface.Commands.SailTo.enable			= false;
	BattleInterface.Commands.SailTo.picNum			= 16;
	BattleInterface.Commands.SailTo.selPicNum		= 0;
	BattleInterface.Commands.SailTo.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.SailTo.event			= "BI_SailTo";
	BattleInterface.Commands.SailTo.note			= LanguageConvertString(idLngFile, "sea_SailTo");
	BattleInterface.FillSailToIcons = "town";
	//
	BattleInterface.Commands.Board.enable			= false;
	BattleInterface.Commands.Board.picNum			= 30;
	BattleInterface.Commands.Board.selPicNum		= 14;
	BattleInterface.Commands.Board.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Board.event			= "BI_Board";
	BattleInterface.Commands.Board.note				= LanguageConvertString(idLngFile, "sea_Board");
	//
	BattleInterface.Commands.LandTroops.enable		= false;
	BattleInterface.Commands.LandTroops.picNum		= 42;
	BattleInterface.Commands.LandTroops.selPicNum	= 45;
	BattleInterface.Commands.LandTroops.texNum		= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.LandTroops.event		= "BI_LandTroops";
	BattleInterface.Commands.LandTroops.note		= LanguageConvertString(idLngFile, "sea_LandTroops");
	//
	BattleInterface.Commands.Map.enable				= false;
	BattleInterface.Commands.Map.picNum				= 28;
	BattleInterface.Commands.Map.selPicNum			= 12;
	BattleInterface.Commands.Map.texNum				= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Map.event				= "BI_Map";
	BattleInterface.Commands.Map.note				= LanguageConvertString(idLngFile, "sea_Map");
	//
	BattleInterface.Commands.Attack.enable			= false;
	BattleInterface.Commands.Attack.picNum			= 49;
	BattleInterface.Commands.Attack.selPicNum		= 33;
	BattleInterface.Commands.Attack.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Attack.event			= "BI_Attack";
	BattleInterface.Commands.Attack.note			= LanguageConvertString(idLngFile, "sea_Attack");
	//
	BattleInterface.Commands.Abordage.enable		= false;
	BattleInterface.Commands.Abordage.picNum		= 30;
	BattleInterface.Commands.Abordage.selPicNum		= 14;
	BattleInterface.Commands.Abordage.texNum		= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Abordage.event			= "BI_Abordage";
	BattleInterface.Commands.Abordage.note			= LanguageConvertString(idLngFile, "sea_Abordage");
	//
	BattleInterface.Commands.Defend.enable			= false;
	BattleInterface.Commands.Defend.picNum			= 51;
	BattleInterface.Commands.Defend.selPicNum		= 35;
	BattleInterface.Commands.Defend.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Defend.event			= "BI_Defend";
	BattleInterface.Commands.Defend.note			= LanguageConvertString(idLngFile, "sea_Defend");
	//
	BattleInterface.Commands.SailAway.enable		= false;
	BattleInterface.Commands.SailAway.picNum		= 50;
	BattleInterface.Commands.SailAway.selPicNum		= 34;
	BattleInterface.Commands.SailAway.texNum		= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.SailAway.event			= "BI_SailAway";
	BattleInterface.Commands.SailAway.note			= LanguageConvertString(idLngFile, "sea_SailAway");
	//
	BattleInterface.Commands.HeaveToDrift.enable	= false;
	BattleInterface.Commands.HeaveToDrift.picNum	= 25;
	BattleInterface.Commands.HeaveToDrift.selPicNum	= 9;
	BattleInterface.Commands.HeaveToDrift.texNum	= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.HeaveToDrift.event		= "BI_HeaveToDrift";
	BattleInterface.Commands.HeaveToDrift.note		= LanguageConvertString(idLngFile, "sea_HeaveToDrift");
	//
	BattleInterface.Commands.Reload.enable			= false;
	BattleInterface.Commands.Reload.picNum			= 48;
	BattleInterface.Commands.Reload.selPicNum		= 32;
	BattleInterface.Commands.Reload.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Reload.event			= "BI_Reload";
	BattleInterface.Commands.Reload.note			= LanguageConvertString(idLngFile, "sea_Reload");
	//
	BattleInterface.Commands.Charge.enable			= false;
	BattleInterface.Commands.Charge.picNum			= 17;
	BattleInterface.Commands.Charge.selPicNum		= 1;
	BattleInterface.Commands.Charge.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Charge.event			= "BI_Charge";
	BattleInterface.Commands.Charge.note			= LanguageConvertString(idLngFile, "sea_Charge");
	//
	BattleInterface.Commands.Speed.enable			= false;
	BattleInterface.Commands.Speed.picNum			= 22;
	BattleInterface.Commands.Speed.selPicNum		= 6;
	BattleInterface.Commands.Speed.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Speed.event			= "BI_Speed";
	BattleInterface.Commands.Speed.note				= LanguageConvertString(idLngFile, "sea_Speed");
	//
	/*BattleInterface.Commands.CCommand.enable		= false;
	BattleInterface.Commands.CCommand.picNum		= 22;
	BattleInterface.Commands.CCommand.selPicNum		= 30;
	BattleInterface.Commands.CCommand.texNum		= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.CCommand.event			= "BI_CompanionCommand";
	BattleInterface.Commands.CCommand.note			= LanguageConvertString(idLngFile, "sea_CCommand");*/
	//
	BattleInterface.Commands.Ability.enable			= false;
	BattleInterface.Commands.Ability.picNum			= 27;
	BattleInterface.Commands.Ability.selPicNum		= 11;
	BattleInterface.Commands.Ability.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Ability.event			= "BI_Ability";
	BattleInterface.Commands.Ability.note			= LanguageConvertString(idLngFile, "sea_Ability");
	//

	BattleInterface.Commands.Boat.enable	= false;
	BattleInterface.Commands.Boat.picNum	= 26;
	BattleInterface.Commands.Boat.selPicNum	= 10;
	BattleInterface.Commands.Boat.texNum	= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Boat.event	= "BI_Boat";
	BattleInterface.Commands.Boat.note	= "Выслать шлюпку";

	BattleInterface.Commands.Cabin.enable	= false;
	BattleInterface.Commands.Cabin.picNum	= 27;
	BattleInterface.Commands.Cabin.selPicNum	= 11;
	BattleInterface.Commands.Cabin.texNum	= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Cabin.event	= "BI_Cabin";
	BattleInterface.Commands.Cabin.note	    = "Каюта";
	BattleInterface.Commands.Bomb.enable	= false;
	BattleInterface.Commands.Bomb.picNum	= 67;
	BattleInterface.Commands.Bomb.selPicNum	= 66;
	BattleInterface.Commands.Bomb.texNum	= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Bomb.event		= "BI_Bomb";
	BattleInterface.Commands.Bomb.note	    = "Спустить мину";

	BattleInterface.Commands.ImmediateDeath.enable	= false;
	BattleInterface.Commands.ImmediateDeath.picNum	= 43;    // это чит
	BattleInterface.Commands.ImmediateDeath.selPicNum	= 43;
	BattleInterface.Commands.ImmediateDeath.texNum	= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.ImmediateDeath.event	= "BI_ImmDeath";
	BattleInterface.Commands.ImmediateDeath.note	= LanguageConvertString(idLngFile, "sea_ImmediateDeath");

	BattleInterface.Commands.Brander.enable			= false;
	BattleInterface.Commands.Brander.picNum			= 52;
	BattleInterface.Commands.Brander.selPicNum		= 36;
	BattleInterface.Commands.Brander.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Brander.event			= "BI_Brander";
    BattleInterface.Commands.Brander.note	= GetConvertStr("Brander", "AbilityDescribe.txt");

	BattleInterface.Commands.ImmediateReload.enable			= false;
	BattleInterface.Commands.ImmediateReload.picNum			= 53;
	BattleInterface.Commands.ImmediateReload.selPicNum		= 37;
	BattleInterface.Commands.ImmediateReload.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.ImmediateReload.event			= "BI_ImmediateReload";
    BattleInterface.Commands.ImmediateReload.note	= GetConvertStr("ImmediateReload", "AbilityDescribe.txt");

	BattleInterface.Commands.InstantBoarding.enable			= false;
	BattleInterface.Commands.InstantBoarding.picNum			= 30;   // это чит
	BattleInterface.Commands.InstantBoarding.selPicNum		= 14;
	BattleInterface.Commands.InstantBoarding.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.InstantBoarding.event			= "BI_InstantBoarding";
    BattleInterface.Commands.InstantBoarding.note	= GetConvertStr("InstantBoarding", "AbilityDescribe.txt");

	BattleInterface.Commands.LightRepair.enable			= false;
	BattleInterface.Commands.LightRepair.picNum			= 54;
	BattleInterface.Commands.LightRepair.selPicNum		= 38;
	BattleInterface.Commands.LightRepair.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.LightRepair.event			= "BI_LightRepair";
	BattleInterface.Commands.LightRepair.note	= GetConvertStr("LightRepair", "AbilityDescribe.txt");

	BattleInterface.Commands.InstantRepair.enable		= false;
	BattleInterface.Commands.InstantRepair.picNum		= 55;
	BattleInterface.Commands.InstantRepair.selPicNum	= 39;
	BattleInterface.Commands.InstantRepair.texNum		= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.InstantRepair.event		= "BI_InstantRepair";
	BattleInterface.Commands.InstantRepair.note	= GetConvertStr("InstantRepair", "AbilityDescribe.txt");

	BattleInterface.Commands.Turn180.enable				= false;
	BattleInterface.Commands.Turn180.picNum				= 56;
	BattleInterface.Commands.Turn180.selPicNum			= 40;
	BattleInterface.Commands.Turn180.texNum				= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Turn180.event				= "BI_Turn180";
	BattleInterface.Commands.Turn180.note	= GetConvertStr("Turn180", "AbilityDescribe.txt");

	BattleInterface.Commands.SandbankManeuver.enable	= false;
	BattleInterface.Commands.SandbankManeuver.picNum	= 57;
	BattleInterface.Commands.SandbankManeuver.selPicNum	= 41;
	BattleInterface.Commands.SandbankManeuver.texNum	= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.SandbankManeuver.event		= "BI_SandbankManeuver";
	BattleInterface.Commands.SandbankManeuver.note	= GetConvertStr("SandbankManeuver", "AbilityDescribe.txt");

	//speak interface Philippe
	BattleInterface.Commands.Speak.enable		= false;
	BattleInterface.Commands.Speak.picNum		= 69;
	BattleInterface.Commands.Speak.selPicNum	= 68;
	BattleInterface.Commands.Speak.event		= "BI_Speak";
	BattleInterface.Commands.Speak.note         = LanguageConvertString(idLngFile, "sea_Speak");

	BattleInterface.Commands.SailDir.enable			= false;
	BattleInterface.Commands.SailDir.picNum			= 71;
	BattleInterface.Commands.SailDir.selPicNum		= 70;
	BattleInterface.Commands.SailDir.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.SailDir.event			= "BI_SailDir";
	BattleInterface.Commands.SailDir.note			= LanguageConvertString(idLngFile, "sea_SailDir");

	LanguageCloseFile(idLngFile);
}

ref BI_GetChargeQuantity()
{
	int chIdx = GetEventData();
	ref chr = GetCharacter(chIdx);
	BI_ChargeState[0] = 4;
	BI_ChargeState[1] = GetCargoGoods(chr,GOOD_BALLS);
	BI_ChargeState[2] = GetCargoGoods(chr,GOOD_GRAPES);
	BI_ChargeState[3] = GetCargoGoods(chr,GOOD_KNIPPELS);
	BI_ChargeState[4] = GetCargoGoods(chr,GOOD_BOMBS);

	return &BI_ChargeState;
}

ref GetCurrentCharge()
{
	BI_intNRetValue[0] = -1;

	if( CheckAttribute(pchar,"Ship.Cannons.Charge.Type") )
	{
		switch(sti(pchar.Ship.Cannons.Charge.Type))
		{
		case GOOD_BALLS:
			BI_intNRetValue[0] = 32;
			BattleInterface.textinfo.Ammo.text = ""+sti(pchar.ship.cargo.goods.balls);
			break;
		case GOOD_GRAPES:
			BI_intNRetValue[0] = 35;
			BattleInterface.textinfo.Ammo.text = ""+sti(pchar.ship.cargo.goods.grapes);
			break;
		case GOOD_KNIPPELS:
			BI_intNRetValue[0] = 34;
			BattleInterface.textinfo.Ammo.text = ""+sti(pchar.ship.cargo.goods.knippels);
			break;
		case GOOD_BOMBS:
			BI_intNRetValue[0] = 33;
			BattleInterface.textinfo.Ammo.text = ""+sti(pchar.ship.cargo.goods.bombs);
			break;
		}
	}

	float fState = Ship_GetSailState(pchar);
	if( fState < 0.33 ) {
		BI_intNRetValue[1] = 20;
	} else {
		if( fState < 0.66 ) {
			BI_intNRetValue[1] = 19;
		} else {
			BI_intNRetValue[1] = 18;
		}
	}
	BI_intNRetValue[2] = 61;

  	//Mett: мониторим порох -->
  	BI_intNRetValue[3] = 53;
	BI_intNRetValue[4] = sti(pchar.ship.cargo.goods.powder == 0);
	BattleInterface.textinfo.Powder.text = /* XI_convertString("Powder") + ": " + */ sti(pchar.ship.cargo.goods.powder);
	// <---
	//мониторим доски, парусину и пушки
	BI_intNRetValue[5] = sti(pchar.ship.cargo.goods.planks == 0);
	BattleInterface.textinfo.Planks.text = /* XI_convertString("Powder") + ": " + */ sti(pchar.ship.cargo.goods.planks);
	BI_intNRetValue[6] = sti(pchar.ship.cargo.goods.sailcloth == 0);
	BattleInterface.textinfo.Sailcloth.text = /* XI_convertString("Powder") + ": " + */ sti(pchar.ship.cargo.goods.sailcloth);
	BI_intNRetValue[7] = sti(GetCannonsNum(pchar) == 0);
	int nShipType = sti(pchar.ship.type);
    ref refBaseShip = GetRealShip(nShipType);
	BattleInterface.textinfo.CannonsNumL.text = GetBortIntactCannonsNum(pchar, "lcannon", sti(refBaseShip.lcannon)) + "/" + GetBortCannonsMaxQty(pchar, "lcannon");
	BattleInterface.textinfo.CannonsNumR.text = GetBortIntactCannonsNum(pchar, "rcannon", sti(refBaseShip.rcannon)) + "/" + GetBortCannonsMaxQty(pchar, "rcannon");
	BattleInterface.textinfo.CannonsNumB.text = GetBortIntactCannonsNum(pchar, "bcannon", sti(refBaseShip.bcannon)) + "/" + GetBortCannonsMaxQty(pchar, "bcannon");
	BattleInterface.textinfo.CannonsNumF.text = GetBortIntactCannonsNum(pchar, "fcannon", sti(refBaseShip.fcannon)) + "/" + GetBortCannonsMaxQty(pchar, "fcannon");
	//<---
	return &BI_intNRetValue;
}

ref biGetCharacterShipClass()
{
	int nChrIdx = GetEventData();
	BI_intRetValue = 1;
	if( nChrIdx>=0 && nChrIdx<TOTAL_CHARACTERS ) {
		BI_intRetValue = GetCharacterShipClass( &Characters[nChrIdx] );
	}
	return &BI_intRetValue;
}
//#20200519-01
bool BI_SetSeaState()
{
	bool bTmp;
	bSailTo = GetEventData();
	bTmp = GetEventData();
	bMapEnter = GetEventData();
	bAttack = GetEventData();
	bAbordage = bAttack;

	bDefend = GetEventData();
	bReloadCanBe = GetEventData();
	bi_nReloadTarget = GetEventData();
	bEnableIslandSailTo = bMapEnter;
	if(bDisableMapEnter)	bMapEnter = false;

	//bReloadCanBe = 0;
	//#20170530-01
    if(bMapEnter) seaAlarmed = false;
	if(CheckAttribute(pchar,"GhostCap.Fight")) bMapEnter = false;
    return bMapEnter;
}

void SetShipPictureDataByShipTypeName(string sType)
{
	switch(sType)
	{
	// 7-й КЛАСС	(3 корабля)
	case "tartane":				BI_intNRetValue[0] = 0+0*32;	BI_intNRetValue[1] = 0+0*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тартана
	case "plot":				BI_intNRetValue[0] = 2+0*32;	BI_intNRetValue[1] = 2+0*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Плот
    case "wartartane":			BI_intNRetValue[0] = 4+0*32;	BI_intNRetValue[1] = 4+0*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Баркас
	// 6-й КЛАСС	(12 кораблей)
	case "bermsloop":			BI_intNRetValue[0] = 6+0*32;	BI_intNRetValue[1] = 6+0*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Лёг. Шлюп
	case "empress":				BI_intNRetValue[0] = 8+0*32;	BI_intNRetValue[1] = 8+0*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Джонка
	case "pink":				BI_intNRetValue[0] = 10+0*32;	BI_intNRetValue[1] = 10+0*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Лёг. Шлюп
    case "lugger":				BI_intNRetValue[0] = 12+0*32;	BI_intNRetValue[1] = 12+0*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Люггер
	case "lugger_h":			BI_intNRetValue[0] = 14+0*32;	BI_intNRetValue[1] = 14+0*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тяж. Люггер
	case "speedy":				BI_intNRetValue[0] = 16+0*32;	BI_intNRetValue[1] = 16+0*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Ср. Шлюп
	case "fr_sloop":			BI_intNRetValue[0] = 18+0*32;	BI_intNRetValue[1] = 18+0*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Пир. Шлюп
	case "galeoth_h":			BI_intNRetValue[0] = 20+0*32;	BI_intNRetValue[1] = 20+0*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Галеот
	case "sloop":				BI_intNRetValue[0] = 22+0*32;	BI_intNRetValue[1] = 22+0*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Шлюп
	case "sloop_b":				BI_intNRetValue[0] = 24+0*32;	BI_intNRetValue[1] = 24+0*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Боевой Шлюп
	case "neptunus":			BI_intNRetValue[0] = 26+0*32;	BI_intNRetValue[1] = 26+0*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Усил. Шлюп
	case "sophie":				BI_intNRetValue[0] = 28+0*32;	BI_intNRetValue[1] = 28+0*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тяж. Шлюп
	// 5-й КЛАСС	(13 кораблей)
	case "polacca":				BI_intNRetValue[0] = 30+0*32;	BI_intNRetValue[1] = 30+0*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;    break;	// Полакка
	case "barque":				BI_intNRetValue[0] = 0+1*32;	BI_intNRetValue[1] = 0+1*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Барк
	case "fr_postillionen":		BI_intNRetValue[0] = 2+1*32;	BI_intNRetValue[1] = 2+1*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Лег. Фрегат
	case "schooner":			BI_intNRetValue[0] = 4+1*32;	BI_intNRetValue[1] = 4+1*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Шхуна
	case "colonialschooner":	BI_intNRetValue[0] = 6+1*32;	BI_intNRetValue[1] = 6+1*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Лег. Шхуна
	case "xebec":				BI_intNRetValue[0] = 8+1*32;	BI_intNRetValue[1] = 8+1*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Щебека
	case "battlexebec":			BI_intNRetValue[0] = 10+1*32;	BI_intNRetValue[1] = 10+1*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Усил. Щебека
	case "xebeclight":			BI_intNRetValue[0] = 12+1*32;	BI_intNRetValue[1] = 12+1*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Лег. Щебека
	case "schoonerlight":		BI_intNRetValue[0] = 14+1*32;	BI_intNRetValue[1] = 14+1*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Ср. Шхуна
	case "Mirage":				BI_intNRetValue[0] = 16+1*32;	BI_intNRetValue[1] = 16+1*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тяж. Шхуна
	case "polacre":				BI_intNRetValue[0] = 18+1*32;	BI_intNRetValue[1] = 18+1*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Полакр
	case "enslaver":			BI_intNRetValue[0] = 20+1*32;	BI_intNRetValue[1] = 20+1*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Пир. Бригантина
	case "shnyava":				BI_intNRetValue[0] = 22+1*32;	BI_intNRetValue[1] = 22+1*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Шнява
	// 4-й КЛАСС (24 корабля)
	case "brig":				BI_intNRetValue[0] = 24+1*32;	BI_intNRetValue[1] = 24+1*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Бриг
	case "brigheavy":			BI_intNRetValue[0] = 26+1*32;	BI_intNRetValue[1] = 26+1*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тяж. Бриг
	case "barkentine":			BI_intNRetValue[0] = 28+1*32;	BI_intNRetValue[1] = 28+1*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Баркентина
	case "brigantine":			BI_intNRetValue[0] = 30+1*32;	BI_intNRetValue[1] = 30+1*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Бригантина
	case "castelf":				BI_intNRetValue[0] = 0+2*32;	BI_intNRetValue[1] = 0+2*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тяж. Бригантина
	case "derfflinger":			BI_intNRetValue[0] = 2+2*32;	BI_intNRetValue[1] = 2+2*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Воен. Флейт
	case "interceptor":			BI_intNRetValue[0] = 4+2*32;	BI_intNRetValue[1] = 4+2*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Ост-индец
	case "fleut":				BI_intNRetValue[0] = 6+2*32;	BI_intNRetValue[1] = 6+2*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Флейт
	case "po_fleut50":			BI_intNRetValue[0] = 8+2*32;	BI_intNRetValue[1] = 8+2*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Усил. Флейт
	case "galeon_l":			BI_intNRetValue[0] = 10+2*32;	BI_intNRetValue[1] = 10+2*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Галеон
	case "greyhound":			BI_intNRetValue[0] = 12+2*32;	BI_intNRetValue[1] = 12+2*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Лег. Корвет
	case "corvettelight":		BI_intNRetValue[0] = 14+2*32;	BI_intNRetValue[1] = 14+2*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Лег. Корвет
	case "packet_brig":			BI_intNRetValue[0] = 16+2*32;	BI_intNRetValue[1] = 16+2*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Воен. Бриг
	case "pdn":					BI_intNRetValue[0] = 18+2*32;	BI_intNRetValue[1] = 18+2*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Лин. Бриг
	case "enterprise":			BI_intNRetValue[0] = 20+2*32;	BI_intNRetValue[1] = 20+2*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Воен. Ост-индец
	case "polacre_h":			BI_intNRetValue[0] = 22+2*32;	BI_intNRetValue[1] = 22+2*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тяж. Полакр
	case "caravel":				BI_intNRetValue[0] = 24+2*32;	BI_intNRetValue[1] = 24+2*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Каравелла
	case "FrigateMedium":		BI_intNRetValue[0] = 26+2*32;	BI_intNRetValue[1] = 26+2*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Ср. Фрегат
	case "raafrigate":			BI_intNRetValue[0] = 28+2*32;	BI_intNRetValue[1] = 28+2*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Ср. Фрегат
	case "caravel2":			BI_intNRetValue[0] = 30+2*32;	BI_intNRetValue[1] = 30+2*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Воен. Каравелла
	case "fleutwar":			BI_intNRetValue[0] = 0+3*32;	BI_intNRetValue[1] = 0+3*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тяж. Боев. Флейт
	case "fleutwarsat":			BI_intNRetValue[0] = 2+3*32;	BI_intNRetValue[1] = 2+3*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Пир. Тяж. Флейт
	case "galeontrader":		BI_intNRetValue[0] = 4+3*32;	BI_intNRetValue[1] = 4+3*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Торг. Корабль
	case "lydia":				BI_intNRetValue[0] = 6+3*32;	BI_intNRetValue[1] = 6+3*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Торг. Корабль
	// 3-й КЛАСС	(32 корабля)
	case "pinnace":				BI_intNRetValue[0] = 8+3*32;	BI_intNRetValue[1] = 8+3*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Пинас
	case "dutchpinnace":		BI_intNRetValue[0] = 10+3*32;	BI_intNRetValue[1] = 10+3*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Воен. Пинас
	case "pinnacelight":		BI_intNRetValue[0] = 12+3*32;	BI_intNRetValue[1] = 12+3*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Двухпалуб. Пинас
	case "xebekvt":				BI_intNRetValue[0] = 14+3*32;	BI_intNRetValue[1] = 14+3*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тяж. Воен. Щебека
	case "felipe":				BI_intNRetValue[0] = 16+3*32;	BI_intNRetValue[1] = 16+3*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Воен. Галеон
	case "crimsonblood":		BI_intNRetValue[0] = 18+3*32;	BI_intNRetValue[1] = 18+3*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Пир. Корвет
	case "corvette":			BI_intNRetValue[0] = 20+3*32;	BI_intNRetValue[1] = 20+3*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Корвет
	case "frigate_l":			BI_intNRetValue[0] = 22+3*32;	BI_intNRetValue[1] = 22+3*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тяж. Корвет
	case "battlecorvette":		BI_intNRetValue[0] = 24+3*32;	BI_intNRetValue[1] = 24+3*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тяж. Корвет
	case "blackangel":			BI_intNRetValue[0] = 26+3*32;	BI_intNRetValue[1] = 26+3*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Боевой Корвет
	case "CoastalFrigate":		BI_intNRetValue[0] = 28+3*32;	BI_intNRetValue[1] = 28+3*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Береговой Фрегат
	case "fr_frigate":			BI_intNRetValue[0] = 30+3*32;	BI_intNRetValue[1] = 30+3*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Корсарский Фрегат
	case "jamaicaship":			BI_intNRetValue[0] = 0+4*32;	BI_intNRetValue[1] = 0+4*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тяж. Пинас
	case "theblackpearl":		BI_intNRetValue[0] = 2+4*32;	BI_intNRetValue[1] = 2+4*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Пир. Галеон
	case "galeon_h":			BI_intNRetValue[0] = 4+4*32;	BI_intNRetValue[1] = 4+4*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тяж. Галеон
	case "galeon1":				BI_intNRetValue[0] = 6+4*32;	BI_intNRetValue[1] = 6+4*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Исп. Тяж. Галеон
	case "la_marianna":			BI_intNRetValue[0] = 8+4*32;	BI_intNRetValue[1] = 8+4*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Призрачный Галеон
	case "piratfastgal":		BI_intNRetValue[0] = 10+4*32;	BI_intNRetValue[1] = 10+4*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Пир. Быстрый Галеон
	case "unicorn":				BI_intNRetValue[0] = 12+4*32;	BI_intNRetValue[1] = 12+4*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Приватирский Фрегат
	case "revenge":				BI_intNRetValue[0] = 14+4*32;	BI_intNRetValue[1] = 14+4*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Боевой Галеон
	case "linefrigate":			BI_intNRetValue[0] = 16+4*32;	BI_intNRetValue[1] = 16+4*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Лин. Фрегат
	case "lightfrigate":		BI_intNRetValue[0] = 18+4*32;	BI_intNRetValue[1] = 18+4*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Патр. Корабль
	case "boussole":			BI_intNRetValue[0] = 20+4*32;	BI_intNRetValue[1] = 20+4*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тяж. Воен. Корвет
	case "surprise":			BI_intNRetValue[0] = 22+4*32;	BI_intNRetValue[1] = 22+4*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Фра. фрегат
	case "salamander":			BI_intNRetValue[0] = 24+4*32;	BI_intNRetValue[1] = 24+4*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Анг. фрегат
	case "frigate_sat":			BI_intNRetValue[0] = 26+4*32;	BI_intNRetValue[1] = 26+4*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Исп. фрегат
	case "battlefrigate":		BI_intNRetValue[0] = 28+4*32;	BI_intNRetValue[1] = 28+4*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Гол. фрегат
	case "nightmare":			BI_intNRetValue[0] = 30+4*32;	BI_intNRetValue[1] = 30+4*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Пир. фрегат
	case "mordaunt":			BI_intNRetValue[0] = 0+5*32;	BI_intNRetValue[1] = 0+5*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Фрегат Мордаунт
	case "frigate":				BI_intNRetValue[0] = 2+5*32;	BI_intNRetValue[1] = 2+5*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Фрегат
	case "amsterdam":			BI_intNRetValue[0] = 4+5*32;	BI_intNRetValue[1] = 4+5*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Линкор 3-го класса
	case "carraca":				BI_intNRetValue[0] = 6+5*32;	BI_intNRetValue[1] = 6+5*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Каракка
	// 2-й КЛАСС (21 корабль)
	case "galeon50":			BI_intNRetValue[0] = 8+5*32;	BI_intNRetValue[1] = 8+5*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Императорский Галеон
	case "fastfrigate":			BI_intNRetValue[0] = 10+5*32;	BI_intNRetValue[1] = 10+5*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Боевой Фрегат
	case "fr_essex":			BI_intNRetValue[0] = 12+5*32;	BI_intNRetValue[1] = 12+5*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тяж. Фрегат
	case "frigate_h":			BI_intNRetValue[0] = 14+5*32;	BI_intNRetValue[1] = 14+5*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тяж. Фрегат
	case "wargalleon2":			BI_intNRetValue[0] = 16+5*32;	BI_intNRetValue[1] = 16+5*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тяж. Воен. Галеон
	case "nl_pinnaceofwar47":	BI_intNRetValue[0] = 18+5*32;	BI_intNRetValue[1] = 18+5*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тяж. Воен. Пинас
	case "hollgaleon_h":		BI_intNRetValue[0] = 20+5*32;	BI_intNRetValue[1] = 20+5*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Гол. Воен. Галеон
	case "fearless":			BI_intNRetValue[0] = 22+5*32;	BI_intNRetValue[1] = 22+5*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Усил. Патр. Корабль
	case "lineship":			BI_intNRetValue[0] = 24+5*32;	BI_intNRetValue[1] = 24+5*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Воен. Корабль
	case "nl_fwzp":				BI_intNRetValue[0] = 26+5*32;	BI_intNRetValue[1] = 26+5*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Анг. Воен. Галеон
	case "constitution":		BI_intNRetValue[0] = 28+5*32;	BI_intNRetValue[1] = 28+5*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тяж. Лин. фрегат
	case "oxford":				BI_intNRetValue[0] = 30+5*32;	BI_intNRetValue[1] = 30+5*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Фрегат Оксфорд
	case "dutchlineship":		BI_intNRetValue[0] = 0+6*32;	BI_intNRetValue[1] = 0+6*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Ср. Воен. Корабль
	case "dutchship":			BI_intNRetValue[0] = 2+6*32;	BI_intNRetValue[1] = 2+6*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Усил. Фрегат
	case "nl_convoiship":		BI_intNRetValue[0] = 4+6*32;	BI_intNRetValue[1] = 4+6*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Сторожевой Корабль
	case "couronne":			BI_intNRetValue[0] = 6+6*32;	BI_intNRetValue[1] = 6+6*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Фра. Воен. Галеон
	case "alexis":				BI_intNRetValue[0] = 8+6*32;	BI_intNRetValue[1] = 8+6*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Линкор 2-го класса
	case "lineshipheavy":		BI_intNRetValue[0] = 10+6*32;	BI_intNRetValue[1] = 10+6*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тяж. Воен. Корабль
	case "warship":				BI_intNRetValue[0] = 12+6*32;	BI_intNRetValue[1] = 12+6*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Линейный Корабль
	case "heavywarship":		BI_intNRetValue[0] = 14+6*32;	BI_intNRetValue[1] = 14+6*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Варшип
	case "heavylineship":		BI_intNRetValue[0] = 16+6*32;	BI_intNRetValue[1] = 16+6*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тяж. Лин. Пинас
	// 1-й КЛАСС (20 кораблей)
	case "poseidon":			BI_intNRetValue[0] = 18+6*32;	BI_intNRetValue[1] = 18+6*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Линкор
	case "hms_centurion":		BI_intNRetValue[0] = 20+6*32;	BI_intNRetValue[1] = 20+6*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Линкор
	case "resolution":			BI_intNRetValue[0] = 22+6*32;	BI_intNRetValue[1] = 22+6*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Фрегат Резолюция
	case "fr_superiorwarship1":	BI_intNRetValue[0] = 24+6*32;	BI_intNRetValue[1] = 24+6*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Боевой Корабль
	case "link":				BI_intNRetValue[0] = 26+6*32;	BI_intNRetValue[1] = 26+6*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тяж. Линкор
	case "superbe":				BI_intNRetValue[0] = 28+6*32;	BI_intNRetValue[1] = 28+6*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тяж. Линкор
	case "battleship":			BI_intNRetValue[0] = 30+6*32;	BI_intNRetValue[1] = 30+6*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Боевой Корабль
	case "link2":				BI_intNRetValue[0] = 0+7*32;	BI_intNRetValue[1] = 0+7*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тяж. Варшип
	case "bellona":				BI_intNRetValue[0] = 2+7*32;	BI_intNRetValue[1] = 2+7*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Линкор 1-го класса
	case "linearship":			BI_intNRetValue[0] = 4+7*32;	BI_intNRetValue[1] = 4+7*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тяж. Лин. Корабль
	case "shark":				BI_intNRetValue[0] = 6+7*32;	BI_intNRetValue[1] = 6+7*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тяж. Лин. Корабль
	case "Zevenprovincien":		BI_intNRetValue[0] = 8+7*32;	BI_intNRetValue[1] = 8+7*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Лег. Мановар
	case "fr_trinity":			BI_intNRetValue[0] = 10+7*32;	BI_intNRetValue[1] = 10+7*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Воен. Мановар
	case "manowar_fast":		BI_intNRetValue[0] = 12+7*32;	BI_intNRetValue[1] = 12+7*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Фра. Мановар
	case "battlemanowar":		BI_intNRetValue[0] = 14+7*32;	BI_intNRetValue[1] = 14+7*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Анг. Мановар
	case "manowar_gub":			BI_intNRetValue[0] = 16+7*32;	BI_intNRetValue[1] = 16+7*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Пир. Мановар
	case "prince":				BI_intNRetValue[0] = 18+7*32;	BI_intNRetValue[1] = 18+7*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Королевский Фрегат
	case "manowar":				BI_intNRetValue[0] = 20+7*32;	BI_intNRetValue[1] = 20+7*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Гол. Мановар
	case "hms_victory":			BI_intNRetValue[0] = 22+7*32;	BI_intNRetValue[1] = 22+7*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Мановар Виктория
	case "sp_sanfelipe":		BI_intNRetValue[0] = 24+7*32;	BI_intNRetValue[1] = 24+7*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Исп. Мановар
		// КВЕСТОВЫЕ (11 кораблей)
	case "luggerquest":			BI_intNRetValue[0] = 26+7*32;	BI_intNRetValue[1] = 26+7*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Курьерский Люггер
	case "xebekvml":			BI_intNRetValue[0] = 28+7*32;	BI_intNRetValue[1] = 28+7*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Щебека
	case "brigqeen":			BI_intNRetValue[0] = 30+7*32;	BI_intNRetValue[1] = 30+7*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Бриг
	case "brigsw":				BI_intNRetValue[0] = 0+8*32;	BI_intNRetValue[1] = 0+8*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Бриг
	case "Clipper":				BI_intNRetValue[0] = 2+8*32;	BI_intNRetValue[1] = 2+8*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Корвет
	case "corvette_quest":		BI_intNRetValue[0] = 4+8*32;	BI_intNRetValue[1] = 4+8*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Фрегат
	case "Wh_corvette_quest":	BI_intNRetValue[0] = 6+8*32;	BI_intNRetValue[1] = 6+8*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Корвет
	case "ArabellaShip":		BI_intNRetValue[0] = 8+8*32;	BI_intNRetValue[1] = 8+8*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Фрегат
	case "frigatequeen":		BI_intNRetValue[0] = 10+8*32;	BI_intNRetValue[1] = 10+8*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Фрегат
	case "Catherine":			BI_intNRetValue[0] = 12+8*32;	BI_intNRetValue[1] = 12+8*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Королева-Катрин
	case "flyingdutchman":		BI_intNRetValue[0] = 14+8*32;	BI_intNRetValue[1] = 14+8*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Варшип
	case "santisima":			BI_intNRetValue[0] = 16+8*32;	BI_intNRetValue[1] = 16+8*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Быстрый мановар
	case "soleyru":				BI_intNRetValue[0] = 18+8*32;	BI_intNRetValue[1] = 18+8*32 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Сулей Руаяль
	}
	BI_intNRetValue[3] = false;
}

void SetShipPictureDataByShipType(int st)
{
	if(st>=0 && st<SHIP_TYPES_QUANTITY)
	{
		SetShipPictureDataByShipTypeName( ShipsTypes[st].name );
	}
}

ref BI_GetData()
{
	int dataType = GetEventData();
	int chrIdx;
	ref chRef;

	switch(dataType)
	{
	// Получаем номер картинки корабля
	case BIDT_SHIPPICTURE:
		chRef = GetCharacter(GetEventData());
		//#20190622-03
		if( CharacterIsDead(chRef) && sti(chRef.index) != GetMainCharacterIndex())
		{
            BI_intNRetValue[0] = 65;
            BI_intNRetValue[1] = 64; // выбранная черепушка
            BI_intNRetValue[2] = BI_ICONS_TEXTURE_COMMAND;
            BI_intNRetValue[3] = true;

			return &BI_intNRetValue;
			break;
		}
		int st = sti(chRef.Ship.Type);
		if (!CheckAttribute(&RealShips[st], "basetype")) Log_TestInfo("BIDT_SHIPPICTURE нет basetype у корабля НПС ID=" + chRef.id);
		st = sti(RealShips[st].basetype);
		SetShipPictureDataByShipType( st );
		break;
	case BIDT_GERALD_DATA:
		{
			chrIdx = GetEventData();
			if(chrIdx<0) break;
			chRef = GetCharacter(chrIdx);
			BI_intNRetValue[0] = 8;
			switch( SeaAI_GetRelation(chrIdx,nMainCharacterIndex) )
			{
				case RELATION_FRIEND:
					BI_intNRetValue[1] = 7;
				break;
				case RELATION_NEUTRAL:
					BI_intNRetValue[1] = -1;
				break;
				case RELATION_ENEMY:
					BI_intNRetValue[1] = 6;
				break;
			}
			BI_intNRetValue[2] = 8;
			switch( sti(chRef.nation) )
			{
				//case SMUGGLER:
				//	BI_intNRetValue[3] = 1;
				//break;
				case ENGLAND:
					BI_intNRetValue[3] = 3;
				break;
				case FRANCE:
					BI_intNRetValue[3] = 2;
				break;
				case SPAIN:
					BI_intNRetValue[3] = 0;
				break;
				case HOLLAND:
					BI_intNRetValue[3] = 4;
				break;
				case PIRATE:
					BI_intNRetValue[3] = 5;
				break;
			}
		}
		break;
	}
	return &BI_intNRetValue;
}

void SetParameterData()
{
	float fHtRatio = stf(Render.screen_y) / screenscaling;
	int idLngFile = LanguageOpenFile("commands_name.txt");
	if(InterfaceStates.AltIntIcons) BattleInterface.CommandTextures.list.t0.name = "battle_interface\List_icons_Konshud.tga";
	else BattleInterface.CommandTextures.list.t0.name = "battle_interface\list_icons.tga";
	BattleInterface.CommandTextures.list.t0.xsize = 16;
	BattleInterface.CommandTextures.list.t0.ysize = 8;
	//Новый стиль HUD по чекбоксу
	if(InterfaceStates.AltIntIcons)
	{
		if(InterfaceStates.HUDStyle) BattleInterface.CommandTextures.list.t1.name = "battle_interface\ship_icons1_Konshud.tga";
		else BattleInterface.CommandTextures.list.t1.name = "battle_interface\ship_icons1_Konshud.tga";
	}
	else
	{
		if(InterfaceStates.HUDStyle) BattleInterface.CommandTextures.list.t1.name = "battle_interface\ship_icons1.tga";
		else BattleInterface.CommandTextures.list.t1.name = "battle_interface\ship_icons1.tga";
	}
	//<---
	BattleInterface.CommandTextures.list.t1.xsize = 32;
	BattleInterface.CommandTextures.list.t1.ysize = 32;

	if(InterfaceStates.AltIntIcons) BattleInterface.CommandTextures.list.t2.name = "battle_interface\cancel_Konshud.tga";
	else BattleInterface.CommandTextures.list.t2.name = "battle_interface\cancel.tga";
	BattleInterface.CommandTextures.list.t2.xsize = 2;
	BattleInterface.CommandTextures.list.t2.ysize = 1;

	BattleInterface.CommandTextures.list.t3.name = "battle_interface\small_nations.tga";
	BattleInterface.CommandTextures.list.t3.xsize = 8;
	BattleInterface.CommandTextures.list.t3.ysize = 1;

	BattleInterface.charge.charge1.picNum = 19; // balls
	BattleInterface.charge.charge1.selPicNum = 3;
	BattleInterface.charge.charge2.picNum = 18; // grapes
	BattleInterface.charge.charge2.selPicNum = 2;
	BattleInterface.charge.charge3.picNum = 21; // "Knippels"
	BattleInterface.charge.charge3.selPicNum = 5;
	BattleInterface.charge.charge4.picNum = 20; // bombs
	BattleInterface.charge.charge4.selPicNum = 4;

	BattleInterface.CommandTextures.ChargeTexNum = 0;
	BattleInterface.CommandTextures.CommandTexNum = 0;

	BattleInterface.CommandShowParam.maxShowQuantity = 10;
	BattleInterface.CommandShowParam.iconDistance = makeint(4 * fHtRatio);
	BattleInterface.CommandShowParam.iconWidth = RecalculateHIcon(makeint(64 * fHtRatio));
	BattleInterface.CommandShowParam.iconHeight = RecalculateVIcon(makeint(64 * fHtRatio));
	BattleInterface.CommandShowParam.leftIconsOffset = sti(showWindow.left)+RecalculateHIcon(makeint(16 * fHtRatio));
	BattleInterface.CommandShowParam.downIconsOffset = sti(showWindow.bottom)-RecalculateVIcon(makeint(80 * fHtRatio));
	BattleInterface.CommandShowParam.buttonWidth = RecalculateHIcon(makeint(8 * fHtRatio));
	BattleInterface.CommandShowParam.buttonHeight = RecalculateVIcon(makeint(64 * fHtRatio));
	BattleInterface.CommandShowParam.buttonOffset = RecalculateHIcon(makeint(4 * fHtRatio));
	BattleInterface.CommandShowParam.buttonTexture = "battle_interface\lr_buttons.tga.tx";
	BattleInterface.CommandShowParam.shipStateWidth = RecalculateHIcon(makeint(64 * fHtRatio));
	BattleInterface.CommandShowParam.shipStateHeight = RecalculateVIcon(makeint(16 * fHtRatio));
	BattleInterface.CommandShowParam.shipStateTexture = "battle_interface\indicators.tga.tx";
	BattleInterface.CommandShowParam.shipStateOffset = RecalculateVIcon(0);
	BattleInterface.CommandShowParam.GeraldWidth = RecalculateHIcon(makeint(32 * fHtRatio));
	BattleInterface.CommandShowParam.GeraldHeight = RecalculateVIcon(makeint(32 * fHtRatio));
	BattleInterface.CommandShowParam.commandFont = "bold_numbers";
	BattleInterface.CommandShowParam.printXOffset = RecalculateHIcon(makeint(32 * fHtRatio));
	BattleInterface.CommandShowParam.printYOffset = RecalculateVIcon(makeint(-26 * fHtRatio));
	BattleInterface.CommandShowParam.commandNoteFont = "interface_normal";
	BattleInterface.CommandShowParam.noteXOffset = RecalculateHIcon(0);
	BattleInterface.CommandShowParam.noteYOffset = RecalculateVIcon(makeint(-30 * fHtRatio));
	BattleInterface.CommandShowParam.argbTFactorColor = argb(256,64,64,64);

	BattleInterface.UserIcons.ui1.enable = true;
	BattleInterface.UserIcons.ui1.pic = 25;
	BattleInterface.UserIcons.ui1.selpic = 9;
	BattleInterface.UserIcons.ui1.tex = 0;
	BattleInterface.UserIcons.ui1.name = "sail_none";
	//----------------------------------------------
	BattleInterface.UserIcons.ui2.enable = true;
	BattleInterface.UserIcons.ui2.pic = 24;
	BattleInterface.UserIcons.ui2.selpic = 8;
	BattleInterface.UserIcons.ui2.tex = 0;
	BattleInterface.UserIcons.ui2.name = "sail_midi";
	//----------------------------------------------
	BattleInterface.UserIcons.ui3.enable = true;
	BattleInterface.UserIcons.ui3.pic = 23;
	BattleInterface.UserIcons.ui3.selpic = 7;
	BattleInterface.UserIcons.ui3.tex = 0;
	BattleInterface.UserIcons.ui3.name = "sail_fast";
	BattleInterface.UserIcons.ui4.enable = true;
	BattleInterface.UserIcons.ui4.selpic = 96;
	BattleInterface.UserIcons.ui4.pic = 112;
	BattleInterface.UserIcons.ui4.tex = BI_ICONS_TEXTURE_COMMAND;;
	BattleInterface.UserIcons.ui4.name = "dir_n";
	BattleInterface.UserIcons.ui4.note = LanguageConvertString(idLngFile, "sea_SailN");

	BattleInterface.UserIcons.ui5.enable = true;
	BattleInterface.UserIcons.ui5.selpic = 97;
	BattleInterface.UserIcons.ui5.pic = 113;
	BattleInterface.UserIcons.ui5.tex = BI_ICONS_TEXTURE_COMMAND;;
	BattleInterface.UserIcons.ui5.name = "dir_ne";
	BattleInterface.UserIcons.ui5.note = LanguageConvertString(idLngFile, "sea_SailNE");

	BattleInterface.UserIcons.ui6.enable = true;
	BattleInterface.UserIcons.ui6.selpic = 98;
	BattleInterface.UserIcons.ui6.pic = 114;
	BattleInterface.UserIcons.ui6.tex = BI_ICONS_TEXTURE_COMMAND;;
	BattleInterface.UserIcons.ui6.name = "dir_e";
	BattleInterface.UserIcons.ui6.note = LanguageConvertString(idLngFile, "sea_SailE");

	BattleInterface.UserIcons.ui7.enable = true;
	BattleInterface.UserIcons.ui7.selpic = 99;
	BattleInterface.UserIcons.ui7.pic = 115;
	BattleInterface.UserIcons.ui7.tex = BI_ICONS_TEXTURE_COMMAND;;
	BattleInterface.UserIcons.ui7.name = "dir_se";
	BattleInterface.UserIcons.ui7.note = LanguageConvertString(idLngFile, "sea_SailSE");

	BattleInterface.UserIcons.ui8.enable = true;
	BattleInterface.UserIcons.ui8.selpic = 100;
	BattleInterface.UserIcons.ui8.pic = 116;
	BattleInterface.UserIcons.ui8.tex = BI_ICONS_TEXTURE_COMMAND;;
	BattleInterface.UserIcons.ui8.name = "dir_s";
	BattleInterface.UserIcons.ui8.note = LanguageConvertString(idLngFile, "sea_SailS");

	BattleInterface.UserIcons.ui9.enable = true;
	BattleInterface.UserIcons.ui9.selpic = 101;
	BattleInterface.UserIcons.ui9.pic = 117;
	BattleInterface.UserIcons.ui9.tex = BI_ICONS_TEXTURE_COMMAND;;
	BattleInterface.UserIcons.ui9.name = "dir_sw";
	BattleInterface.UserIcons.ui9.note = LanguageConvertString(idLngFile, "sea_SailSW");

    BattleInterface.UserIcons.ui10.enable = true;
	BattleInterface.UserIcons.ui10.selpic = 102;
	BattleInterface.UserIcons.ui10.pic = 118;
	BattleInterface.UserIcons.ui10.tex = BI_ICONS_TEXTURE_COMMAND;;
	BattleInterface.UserIcons.ui10.name = "dir_w";
	BattleInterface.UserIcons.ui10.note = LanguageConvertString(idLngFile, "sea_SailW");

	BattleInterface.UserIcons.ui11.enable = true;
	BattleInterface.UserIcons.ui11.selpic = 103;
	BattleInterface.UserIcons.ui11.pic = 119;
	BattleInterface.UserIcons.ui11.tex = BI_ICONS_TEXTURE_COMMAND;;
	BattleInterface.UserIcons.ui11.name = "dir_nw";
	BattleInterface.UserIcons.ui11.note = LanguageConvertString(idLngFile, "sea_SailNW");

	//===============================================
	BattleInterface.MessageIcons.IconWidth = RecalculateHIcon(makeint(64 * fHtRatio));
	BattleInterface.MessageIcons.IconHeight = RecalculateVIcon(makeint(24 * fHtRatio));
	BattleInterface.MessageIcons.IconDist = RecalculateVIcon(2);
	BattleInterface.MessageIcons.IconBottom = sti(showWindow.bottom)-RecalculateVIcon(makeint((80+20) * fHtRatio));
	BattleInterface.MessageIcons.IconMaxQuantity = 4;
	BattleInterface.MessageIcons.BlendTime = 3.0;
	BattleInterface.MessageIcons.FallSpeed = 22.0;
	BattleInterface.MessageIcons.argbHighBlind = argb(255,128,128,128);
	BattleInterface.MessageIcons.argbLowBlind = argb(255,68,68,68);
	BattleInterface.MessageIcons.BlindUpTime = 0.5;
	BattleInterface.MessageIcons.BlindDownTime = 1.0;
	BattleInterface.MessageIcons.texture = "battle_interface\MessageIcons.tga";
	BattleInterface.MessageIcons.TexHSize = 2;
	BattleInterface.MessageIcons.TexVSize = 2;

	// Цифры ветра и текущей скорости
	BattleInterface.navigation.aspectRatio				= showWindow.aspectRatio;
	BattleInterface.navigation.navigatorWidth			= RecalculateHIcon(makeint(216 * fHtRatio));
	BattleInterface.navigation.navigatorHeight			= RecalculateVIcon(makeint(216 * fHtRatio));
	BattleInterface.navigation.rightPos					= sti(showWindow.right) + RecalculateHIcon(makeint(-10 * fHtRatio));
	BattleInterface.navigation.topPos					= sti(showWindow.top) - RecalculateVIcon(makeint(24 * fHtRatio));
	BattleInterface.navigation.speedShowFont			= "bold_numbers";
	BattleInterface.navigation.speedOutYOffset			= RecalculateVIcon(makeint(180 * fHtRatio));
	BattleInterface.navigation.shipSpeedXOffset			= RecalculateHIcon(makeint(25 * fHtRatio));
	BattleInterface.navigation.windSpeedXOffset			= RecalculateHIcon(makeint(-25 * fHtRatio));
	BattleInterface.navigation.fontScale				= 0.7 * fHtRatio;
	BattleInterface.navigation.windWidth				= makeint(32 * fHtRatio);
	BattleInterface.navigation.windHeight				= makeint(128 * fHtRatio);

	BattleInterface.navigation.compasTexture			= "battle_interface\compass.tga";
	BattleInterface.navigation.cannonsTexture			= "battle_interface\indicators_cannons_reload.tga";
	BattleInterface.navigation.emptyTexture				= "battle_interface\indicators_dark_and_center_ship.tga";
	BattleInterface.navigation.windTexture				= "battle_interface\wind_pointer.tga";

	BattleInterface.navigation.leftChargeBegAngle		= 214;
	BattleInterface.navigation.leftChargeEndAngle		= 326;
	BattleInterface.navigation.rightChargeBegAngle		= 146;
	BattleInterface.navigation.rightChargeEndAngle		= 34;
	BattleInterface.navigation.forwardChargeBegAngle	= 343;
	BattleInterface.navigation.forwardChargeEndAngle	= 378;
	BattleInterface.navigation.backwardChargeBegAngle	= 198;
	BattleInterface.navigation.backwardChargeEndAngle	= 162;
	BattleInterface.navigation.mapRadius				= makeint(48 * fHtRatio);
	BattleInterface.navigation.horizontRadius			= 400;
	BattleInterface.navigation.minScale					= 0.5;
	BattleInterface.navigation.maxScale					= 4;
	BattleInterface.navigation.curScale					= 2;
	BattleInterface.navigation.scaleStep				= 0.1;
	BattleInterface.navigation.argbReadyCannonColor		= argb(255,0,155,0);
	BattleInterface.navigation.argbChargeCannonColor	= argb(255,0,255,0);
	BattleInterface.navigation.argbDamageCannonColor	= argb(0,190,50,10);
	BattleInterface.navigation.argbSeaColor				= argb(255,10,30,80);
	BattleInterface.navigation.argbFireZoneColor		= argb(60,250,250,250);
	BattleInterface.navigation.argbEnemyShipColor		= argb(255,255,0,0);
	BattleInterface.navigation.argbFrendShipColor		= argb(255,0,255,0);
	BattleInterface.navigation.argbNeutralShipColor		= argb(255,128,128,128);
	BattleInterface.navigation.argbDeadShipColor		= argb(255,0,0,255);
	BattleInterface.navigation.argbBackMaxColor			= argb(255,0,0,128);
	BattleInterface.navigation.argbBackMinColor			= argb(0,0,0,128);
	BattleInterface.navigation.shipShowRadius			= 8.0;

	// Боеприпасы
	if(InterfaceStates.AltIntIcons) BattleInterface.navigation.chargeTexture 			= "battle_interface\list_icon2_Konshud.tga";
	else BattleInterface.navigation.chargeTexture							 			= "battle_interface\list_icon2.tga";
	BattleInterface.navigation.chargeTextureGreed		= "8,8";
	BattleInterface.navigation.chargePos				= RecalculateHIcon(makeint(-25* fHtRatio))+","+RecalculateVIcon(makeint(220* fHtRatio));
	BattleInterface.navigation.chargePictureSize		= RecalculateHIcon(makeint(40* fHtRatio))+","+RecalculateVIcon(makeint(40* fHtRatio));

	// Порох
	if(InterfaceStates.AltIntIcons) BattleInterface.navigation.powderTexture			= "battle_interface\list_icon2_Konshud.tga";
	else BattleInterface.navigation.powderTexture										= "battle_interface\list_icon2.tga";
	BattleInterface.navigation.powderTextureGreed		= "8,8";
	BattleInterface.navigation.powderPos				= RecalculateHIcon(makeint(25* fHtRatio))+","+RecalculateVIcon(makeint(220* fHtRatio));
	BattleInterface.navigation.powderPictureSize		= RecalculateHIcon(makeint(40* fHtRatio))+","+RecalculateVIcon(makeint(40* fHtRatio));

	// Скорость
	if(InterfaceStates.AltIntIcons) BattleInterface.navigation.sailstateTexture			= "battle_interface\list_icon2_Konshud.tga";
	else BattleInterface.navigation.sailstateTexture									= "battle_interface\list_icon2.tga";
	BattleInterface.navigation.sailstateTextureGreed	= "8,8";
	BattleInterface.navigation.sailstatePos				= RecalculateHIcon(makeint(25* fHtRatio))+","+RecalculateVIcon(makeint(160* fHtRatio));
	BattleInterface.navigation.sailstatePictureSize		= RecalculateHIcon(makeint(40* fHtRatio))+","+RecalculateVIcon(makeint(40* fHtRatio));

	// Ветер
	if(InterfaceStates.AltIntIcons) BattleInterface.navigation.windStateTexture			= "battle_interface\list_icon2_Konshud.tga";
	else BattleInterface.navigation.windStateTexture									= "battle_interface\list_icon2.tga";
	BattleInterface.navigation.windTextureGreed			= "8,8";
	BattleInterface.navigation.windPos					= RecalculateHIcon(makeint(-25* fHtRatio))+","+RecalculateVIcon(makeint(160* fHtRatio));
	BattleInterface.navigation.windPictureSize			= RecalculateHIcon(makeint(40* fHtRatio))+","+RecalculateVIcon(makeint(40* fHtRatio));

	// Дата
	BattleInterface.textinfo.Date.font = "interface_button";
	BattleInterface.textinfo.Date.scale = 1.0 * fHtRatio;
	BattleInterface.textinfo.Date.pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(120* fHtRatio));
	BattleInterface.textinfo.Date.pos.y = RecalculateVIcon(makeint(170* fHtRatio));
	BattleInterface.textinfo.Date.text = XI_convertString("Date:")+GetQuestBookData();//GetDataDay()+" "+XI_ConvertString("target_month_" + GetDataMonth())+" "+GetDataYear();
	BattleInterface.textinfo.Date.refreshable = true;

	// Локация
	BattleInterface.textinfo.Location.font = "interface_button";
	BattleInterface.textinfo.Location.scale = 1.0* fHtRatio;
	BattleInterface.textinfo.Location.pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(120* fHtRatio));
	BattleInterface.textinfo.Location.pos.y = RecalculateVIcon(makeint(190* fHtRatio));
	BattleInterface.textinfo.Location.text = GetBILocationName();	// Display MoorName or region name in location
	BattleInterface.textinfo.Location.refreshable = true;			// Enable updates

	//Скорость LEO: (убрал стрингу)
	BattleInterface.textinfo.Speed.font = "interface_button";
	BattleInterface.textinfo.Speed.scale = 1.0 * fHtRatio;
	BattleInterface.textinfo.Speed.color = argb(255,255,255,255);
	BattleInterface.textinfo.Speed.pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(138* fHtRatio));
	BattleInterface.textinfo.Speed.pos.y = RecalculateVIcon(makeint(337* fHtRatio));
	BattleInterface.textinfo.Speed.text = ""/* XI_convertString("Speed") */;

	// Боеприпасы
	BattleInterface.textinfo.Ammo.font = "bold_numbers";
	BattleInterface.textinfo.Ammo.scale = 0.7 * fHtRatio;
	BattleInterface.textinfo.Ammo.color = argb(255,255,255,255);
	BattleInterface.textinfo.Ammo.pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(144* fHtRatio));
	BattleInterface.textinfo.Ammo.pos.y = RecalculateVIcon(makeint(325* fHtRatio));
	BattleInterface.textinfo.Ammo.text = XI_convertString("Ammunition");
	BattleInterface.textinfo.Ammo.refreshable = true;

	// Порох
	BattleInterface.textinfo.Powder.font = "bold_numbers";
	BattleInterface.textinfo.Powder.scale = 0.7 * fHtRatio;
	BattleInterface.textinfo.Powder.color = argb(255,255,255,255);
	BattleInterface.textinfo.Powder.pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(94* fHtRatio));//sti(showWindow.right) - RecalculateHIcon(104);
	BattleInterface.textinfo.Powder.pos.y = RecalculateVIcon(makeint(325* fHtRatio));//RecalculateVIcon(402);
	BattleInterface.textinfo.Powder.text = XI_convertString("Powder");
	BattleInterface.textinfo.Powder.refreshable = true;

	// Доски
	BattleInterface.textinfo.Planks.font = "bold_numbers";
	BattleInterface.textinfo.Planks.scale = 0.7 * fHtRatio;
	BattleInterface.textinfo.Planks.color = argb(255,255,255,255);
	BattleInterface.textinfo.Planks.pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(144* fHtRatio));//sti(showWindow.right) - RecalculateHIcon(104);
	BattleInterface.textinfo.Planks.pos.y = RecalculateVIcon(makeint(388* fHtRatio));//RecalculateVIcon(402);
	BattleInterface.textinfo.Planks.text = XI_convertString("Planks");
	BattleInterface.textinfo.Planks.refreshable = true;

	// Парусина
	BattleInterface.textinfo.Sailcloth.font = "bold_numbers";
	BattleInterface.textinfo.Sailcloth.scale = 0.7 * fHtRatio;
	BattleInterface.textinfo.Sailcloth.color = argb(255,255,255,255);
	BattleInterface.textinfo.Sailcloth.pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(94* fHtRatio));//sti(showWindow.right) - RecalculateHIcon(104);
	BattleInterface.textinfo.Sailcloth.pos.y = RecalculateVIcon(makeint(388* fHtRatio));//RecalculateVIcon(402);
	BattleInterface.textinfo.Sailcloth.text = XI_convertString("Sailcloth");
	BattleInterface.textinfo.Sailcloth.refreshable = true;

	//ставим иконки доскам и парусине --->
	int fTmp = sti(showWindow.right) - RecalculateHIcon(makeint(123* fHtRatio));
	int fTmp2 = sti(showWindow.top) + RecalculateVIcon(makeint(346* fHtRatio));
	int fTmp3 = sti(showWindow.right) - RecalculateHIcon(makeint(163* fHtRatio));
	int fTmp4 = sti(showWindow.top) + RecalculateVIcon(makeint(386* fHtRatio));
	string off	= fTmp + "," + fTmp2 + "," + fTmp3 + "," + fTmp4;
	if(InterfaceStates.AltIntIcons) BattleInterface.imageslist.textinfoback2.texture = "\battle_interface\Icon_Planks_Konshud.tga";
	else BattleInterface.imageslist.textinfoback2.texture = "\battle_interface\Icon_Planks.tga";
	BattleInterface.imageslist.textinfoback2.color = argb(255,128,128,128);
	BattleInterface.imageslist.textinfoback2.uv = "0.0,0.0,1.0,1.0";
	BattleInterface.imageslist.textinfoback2.pos = off;

	fTmp = sti(showWindow.right) - RecalculateHIcon(makeint(73* fHtRatio));
	fTmp3 = sti(showWindow.right) - RecalculateHIcon(makeint(113* fHtRatio));
	off	= fTmp + "," + fTmp2 + "," + fTmp3 + "," + fTmp4;
	if(InterfaceStates.AltIntIcons) BattleInterface.imageslist.textinfoback3.texture = "\battle_interface\Icon_Sailcloth_Konshud.tga";
	else BattleInterface.imageslist.textinfoback3.texture = "\battle_interface\Icon_Sailcloth.tga";
	BattleInterface.imageslist.textinfoback3.color = argb(255,128,128,128);
	BattleInterface.imageslist.textinfoback3.uv = "0.0,0.0,1.0,1.0";
	BattleInterface.imageslist.textinfoback3.pos = off;
	//<---

	//Рисуем интерфейс пушек
	if(InterfaceStates.CannonsHUD)
	{
		BattleInterface.textinfo.CannonsNumL.font = "bold_numbers";
		BattleInterface.textinfo.CannonsNumL.scale = 0.55 * fHtRatio;
		BattleInterface.textinfo.CannonsNumL.color = argb(255,255,255,255);
		BattleInterface.textinfo.CannonsNumL.pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(212* fHtRatio));//sti(showWindow.right) - RecalculateHIcon(104);
		BattleInterface.textinfo.CannonsNumL.pos.y = sti(showWindow.top) + RecalculateVIcon(makeint(80* fHtRatio));;//RecalculateVIcon(402);
		BattleInterface.textinfo.CannonsNumL.refreshable = true;

		BattleInterface.textinfo.CannonsNumR.font = "bold_numbers";
		BattleInterface.textinfo.CannonsNumR.scale = 0.55 * fHtRatio;
		BattleInterface.textinfo.CannonsNumR.color = argb(255,255,255,255);
		BattleInterface.textinfo.CannonsNumR.pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(26* fHtRatio));//sti(showWindow.right) - RecalculateHIcon(104);
		BattleInterface.textinfo.CannonsNumR.pos.y = sti(showWindow.top) + RecalculateVIcon(makeint(80* fHtRatio));;//RecalculateVIcon(402);
		BattleInterface.textinfo.CannonsNumR.refreshable = true;

		BattleInterface.textinfo.CannonsNumB.font = "bold_numbers";
		BattleInterface.textinfo.CannonsNumB.scale = 0.55 * fHtRatio;
		BattleInterface.textinfo.CannonsNumB.color = argb(255,255,255,255);
		BattleInterface.textinfo.CannonsNumB.pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(120* fHtRatio));//sti(showWindow.right) - RecalculateHIcon(104);
		BattleInterface.textinfo.CannonsNumB.pos.y = sti(showWindow.top) + RecalculateVIcon(makeint(158* fHtRatio));;//RecalculateVIcon(402);
		BattleInterface.textinfo.CannonsNumB.refreshable = true;

		BattleInterface.textinfo.CannonsNumF.font = "bold_numbers";
		BattleInterface.textinfo.CannonsNumF.scale = 0.55 * fHtRatio;
		BattleInterface.textinfo.CannonsNumF.color = argb(255,255,255,255);
		BattleInterface.textinfo.CannonsNumF.pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(120* fHtRatio));//sti(showWindow.right) - RecalculateHIcon(104);
		BattleInterface.textinfo.CannonsNumF.pos.y = sti(showWindow.top) + RecalculateVIcon(makeint(0* fHtRatio));;//RecalculateVIcon(402);
		BattleInterface.textinfo.CannonsNumF.refreshable = true;
	}
	else
	{
		BattleInterface.textinfo.CannonsNumL.scale = 0;
		BattleInterface.textinfo.CannonsNumR.scale = 0;
		BattleInterface.textinfo.CannonsNumB.scale = 0;
		BattleInterface.textinfo.CannonsNumF.scale = 0;
	}
	//<---

	/* BattleInterface.LineInfo.speed.color = argb(255,0,0,0);
	BattleInterface.LineInfo.speed.begin.x = sti(showWindow.right) - RecalculateHIcon(202);
	BattleInterface.LineInfo.speed.begin.y = RecalculateVIcon(339);
	BattleInterface.LineInfo.speed.end.x = RecalculateHIcon(128);
	BattleInterface.LineInfo.speed.end.y = 0;
	//
	BattleInterface.LineInfo.Ammo.color = argb(255,0,0,0);
	BattleInterface.LineInfo.Ammo.begin.x = sti(showWindow.right) - RecalculateHIcon(202);
	BattleInterface.LineInfo.Ammo.begin.y = RecalculateVIcon(418);
	BattleInterface.LineInfo.Ammo.end.x = RecalculateHIcon(128);
	BattleInterface.LineInfo.Ammo.end.y = 0; */

	BattleInterface.LineInfo.speed.color = "";
	BattleInterface.LineInfo.speed.begin.x = "";
	BattleInterface.LineInfo.speed.begin.y = "";
	BattleInterface.LineInfo.speed.end.x = "";
	BattleInterface.LineInfo.speed.end.y = "";
	//
	BattleInterface.LineInfo.Ammo.color = "";
	BattleInterface.LineInfo.Ammo.begin.x = "";
	BattleInterface.LineInfo.Ammo.begin.y = "";
	BattleInterface.LineInfo.Ammo.end.x = "";
	BattleInterface.LineInfo.Ammo.end.y = "";

	if( CheckAttribute(&InterfaceStates,"ShowBattleMode") ) {
		BattleInterface.battleborder.used = InterfaceStates.ShowBattleMode;
	} else {
		BattleInterface.battleborder.used = false;
	}
	BattleInterface.battleborder.color1 = argb(255,255,255,255);
	BattleInterface.battleborder.color2 = argb(155,255,255,255);
	BattleInterface.battleborder.extpos = "0,0," + ShowWindow.right + "," + ShowWindow.bottom;
	BattleInterface.battleborder.intpos1 =
		RecalculateHIcon(20) + "," +
		RecalculateVIcon(20) + "," +
		(sti(ShowWindow.right)-RecalculateHIcon(20)) + "," +
		(sti(ShowWindow.bottom)-RecalculateVIcon(20));
	BattleInterface.battleborder.intpos2 =
		RecalculateHIcon(10) + "," +
		RecalculateVIcon(10) + "," +
		(sti(ShowWindow.right)-RecalculateHIcon(10)) + "," +
		(sti(ShowWindow.bottom)-RecalculateVIcon(10));
	BattleInterface.battleborder.speed = 1.5;
	BattleInterface.battleborder.texture = "battle_interface\battleborder.tga";


	//Новый стиль HUD по чекбоксу
	if (InterfaceStates.HUDStyle)
	{
		// Рамка на иконку
		BattleInterface.ShipIcon.backtexturename		= "battle_interface\Ship_Border.tga"; // Основа
		BattleInterface.ShipIcon.backcolor				= argb(255,128,128,128);
		BattleInterface.ShipIcon.backuv					= "0.0,0.0,1.0,1.0";
		BattleInterface.ShipIcon.backoffset				= "0,0";
		BattleInterface.ShipIcon.backiconsize			= RecalculateHIcon(makeint(80* fHtRatio))+","+RecalculateVIcon(makeint(80* fHtRatio));

		// Количество команды
		BattleInterface.ShipIcon.sailorfontid			= "bold_numbers";
		BattleInterface.ShipIcon.sailorfontcolor		= argb(255,255,255,255); // Цвет количества матросов
		BattleInterface.ShipIcon.sailorfontscale		= 0.65 * fHtRatio;
		BattleInterface.ShipIcon.sailorfontoffset		= RecalculateHIcon(makeint(0* fHtRatio))+","+RecalculateVIcon(makeint(42* fHtRatio));

		// Название корабля
		BattleInterface.ShipIcon.shipnamefontid			= "interface_normal";
		BattleInterface.ShipIcon.shipnamefontcolor		= argb(255,255,255,255); // Цвет имени корабля
		BattleInterface.ShipIcon.shipnamefontscale		= 1.0 * fHtRatio;
		BattleInterface.ShipIcon.shipnamefontoffset		= RecalculateHIcon(makeint(0* fHtRatio))+","+RecalculateVIcon(makeint(-56* fHtRatio));

		BattleInterface.ShipIcon.shipstatetexturename	= "battle_interface\ShipHP_SP.tga"; // Полоски HP/SP
		BattleInterface.ShipIcon.shipstatecolor			= argb(255,128,128,128);

		BattleInterface.ShipIcon.shiphpuv				= "0.0,0.109,0.5,0.6875";
		BattleInterface.ShipIcon.shiphpoffset			= RecalculateHIcon(-27.5* fHtRatio)+","+RecalculateVIcon(-3.5* fHtRatio);
		BattleInterface.ShipIcon.shiphpiconsize			= RecalculateHIcon(makeint(64* fHtRatio))+","+RecalculateVIcon(makeint(88* fHtRatio));

		BattleInterface.ShipIcon.shipspuv				= "0.5,0.109,1.0,0.6875";
		BattleInterface.ShipIcon.shipspoffset			= RecalculateHIcon(54.5* fHtRatio)+","+RecalculateVIcon(-3.5* fHtRatio);
		BattleInterface.ShipIcon.shipspiconsize			= RecalculateHIcon(makeint(64* fHtRatio))+","+RecalculateVIcon(makeint(88* fHtRatio));

		BattleInterface.ShipIcon.shipclassiconsize		= "0,0";
		BattleInterface.ShipIcon.gunchargeprogress		= "0.0625, 0.219, 0.359, 0.5, 0.641, 0.781, 0.983";

		BattleInterface.ShipIcon.shiptexturename		= "battle_interface\ship_icons2.tga"; // Иконка корабля
		BattleInterface.ShipIcon.shipcolor				= argb(255,128,128,128);
		BattleInterface.ShipIcon.shipoffset				= RecalculateHIcon(makeint(0* fHtRatio))+","+RecalculateVIcon(makeint(0* fHtRatio));
		BattleInterface.ShipIcon.shipiconsize			= RecalculateHIcon(makeint(86* fHtRatio))+","+RecalculateVIcon(makeint(86* fHtRatio));
		BattleInterface.ShipIcon.xsize = 32;
		BattleInterface.ShipIcon.ysize = 32;

		BattleInterface.ShipIcon.commandlistverticaloffset =  makeint(-40 * fHtRatio);

		BattleInterface.ShipIcon.iconoffset1 = RecalculateHIcon(makeint(70* fHtRatio))+","+RecalculateVIcon(makeint(68* fHtRatio));
		BattleInterface.ShipIcon.iconoffset2 = RecalculateHIcon(makeint(70* fHtRatio))+","+RecalculateVIcon(makeint(178* fHtRatio));
		BattleInterface.ShipIcon.iconoffset3 = RecalculateHIcon(makeint(70* fHtRatio))+","+RecalculateVIcon(makeint(288* fHtRatio));
		BattleInterface.ShipIcon.iconoffset4 = RecalculateHIcon(makeint(70* fHtRatio))+","+RecalculateVIcon(makeint(398* fHtRatio));
		BattleInterface.ShipIcon.iconoffset5 = RecalculateHIcon(makeint(70* fHtRatio))+","+RecalculateVIcon(makeint(508* fHtRatio));
		BattleInterface.ShipIcon.iconoffset6 = RecalculateHIcon(makeint(70* fHtRatio))+","+RecalculateVIcon(makeint(618* fHtRatio));
		BattleInterface.ShipIcon.iconoffset7 = RecalculateHIcon(makeint(70* fHtRatio))+","+RecalculateVIcon(makeint(728* fHtRatio));
		BattleInterface.ShipIcon.iconoffset8 = RecalculateHIcon(makeint(70* fHtRatio))+","+RecalculateVIcon(makeint(838* fHtRatio));

		BattleInterface.CommandList.CommandMaxIconQuantity = 15; //boal
		BattleInterface.CommandList.CommandIconSpace = 1;
		BattleInterface.CommandList.CommandIconLeft = makeint(150 * fHtRatio);//157;
		BattleInterface.CommandList.CommandIconWidth = RecalculateHIcon(makeint(54 * fHtRatio));
		BattleInterface.CommandList.CommandIconHeight = RecalculateVIcon(makeint(54* fHtRatio));

		BattleInterface.CommandList.CommandNoteFont = "interface_button";
		BattleInterface.CommandList.CommandNoteColor = argb(255,255,255,255);
		BattleInterface.CommandList.CommandNoteScale = 1.2 * fHtRatio;
		BattleInterface.CommandList.CommandNoteOffset = RecalculateHIcon(makeint(0* fHtRatio)) + "," + RecalculateVIcon(makeint(-50* fHtRatio));

		BattleInterface.CommandList.UDArrow_Texture = "battle_interface\arrowly.tga";
		BattleInterface.CommandList.UDArrow_UV_Up = "0.0,1.0,1.0,0.0";
		BattleInterface.CommandList.UDArrow_UV_Down = "0.0,0.0,1.0,1.0";
		BattleInterface.CommandList.UDArrow_Size = RecalculateHIcon(makeint(32* fHtRatio)) + "," + RecalculateVIcon(makeint(32* fHtRatio));
		BattleInterface.CommandList.UDArrow_Offset_Up = RecalculateHIcon(makeint(-36* fHtRatio)) + "," + RecalculateVIcon(makeint(-37* fHtRatio));
		BattleInterface.CommandList.UDArrow_Offset_Down = RecalculateHIcon(makeint(-36* fHtRatio)) + "," + RecalculateVIcon(makeint(60* fHtRatio));
	}
	else
	{

		////////////////////////////////////////////////
		/// НОВЫЙ HUD НА ЗАМЕНУ СТАНДАРТНОГО BY JOHNNY88
		////////////////////////////////////////////////

		// подложка иконки корабля
		BattleInterface.ShipIcon.backtexturename		= "battle_interface\ShipBackIcon.tga"; // Основа
		BattleInterface.ShipIcon.backcolor				= argb(255,128,128,128);
		BattleInterface.ShipIcon.backuv					= "0.0,0.0,1.0,1.0";
		BattleInterface.ShipIcon.backoffset				= "-1,0";
		BattleInterface.ShipIcon.backiconsize			= RecalculateHIcon(makeint(110* fHtRatio))+","+RecalculateVIcon(makeint(110* fHtRatio));

		// Количество команды
		BattleInterface.ShipIcon.sailorfontid			= "bold_numbers";
		BattleInterface.ShipIcon.sailorfontcolor		= argb(255,255,255,255); // Цвет количества матросов
		BattleInterface.ShipIcon.sailorfontscale		= 0.6 * fHtRatio;
		BattleInterface.ShipIcon.sailorfontoffset		= RecalculateHIcon(makeint(-2* fHtRatio))+","+RecalculateVIcon(makeint(31* fHtRatio));

		// Название корабля
		BattleInterface.ShipIcon.shipnamefontid			= "interface_button";
		BattleInterface.ShipIcon.shipnamefontcolor		= argb(255,255,255,255); // Цвет имени корабля
		BattleInterface.ShipIcon.shipnamefontscale		= 1.15 * fHtRatio;
		BattleInterface.ShipIcon.shipnamefontoffset		= RecalculateHIcon(makeint(0* fHtRatio))+","+RecalculateVIcon(makeint(-66* fHtRatio));
		BattleInterface.ShipIcon.shipnamefont.align 	= "left";

		// индикаторы ХП корпуса и парусов
		BattleInterface.ShipIcon.shipstatetexturename	= "battle_interface\ShipState.tga"; // Полоски HP/SP
		BattleInterface.ShipIcon.shipstatecolor			= argb(255,128,128,128);
		BattleInterface.ShipIcon.shiphpuv				= "0.0,0.153,0.68,0.815";
		BattleInterface.ShipIcon.shiphpoffset			= RecalculateHIcon(-17* fHtRatio)+","+RecalculateVIcon(-2* fHtRatio);
		BattleInterface.ShipIcon.shiphpiconsize			= RecalculateHIcon(makeint(78* fHtRatio))+","+RecalculateVIcon(makeint(75* fHtRatio));

		BattleInterface.ShipIcon.shipspuv				= "0.32,0.149,1.0,0.816";
		BattleInterface.ShipIcon.shipspoffset			= RecalculateHIcon(16* fHtRatio)+","+RecalculateVIcon(-2* fHtRatio);
		BattleInterface.ShipIcon.shipspiconsize			= RecalculateHIcon(makeint(78* fHtRatio))+","+RecalculateVIcon(makeint(75* fHtRatio));

		BattleInterface.ShipIcon.shipclassiconsize		= "0,0";
		BattleInterface.ShipIcon.gunchargeprogress		= "0.0625, 0.219, 0.359, 0.5, 0.641, 0.781, 0.983";

		BattleInterface.ShipIcon.shiptexturename		= "battle_interface\ship_icons2_johnny88hud.tga"; // Иконка корабля
		BattleInterface.ShipIcon.shipcolor				= argb(255,128,128,128);
		BattleInterface.ShipIcon.shipoffset				= RecalculateHIcon(makeint(-1* fHtRatio))+","+RecalculateVIcon(makeint(-5* fHtRatio));
		BattleInterface.ShipIcon.shipiconsize			= RecalculateHIcon(makeint(70* fHtRatio))+","+RecalculateVIcon(makeint(70* fHtRatio));
		BattleInterface.ShipIcon.xsize = 32;
		BattleInterface.ShipIcon.ysize = 32;

		BattleInterface.ShipIcon.commandlistverticaloffset = makeint(-32 * fHtRatio);

		BattleInterface.ShipIcon.iconoffset1 = RecalculateHIcon(makeint(70* fHtRatio))+","+RecalculateVIcon(makeint(66* fHtRatio));
		BattleInterface.ShipIcon.iconoffset2 = RecalculateHIcon(makeint(70* fHtRatio))+","+RecalculateVIcon(makeint(178* fHtRatio));
		BattleInterface.ShipIcon.iconoffset3 = RecalculateHIcon(makeint(70* fHtRatio))+","+RecalculateVIcon(makeint(290* fHtRatio));
		BattleInterface.ShipIcon.iconoffset4 = RecalculateHIcon(makeint(70* fHtRatio))+","+RecalculateVIcon(makeint(402* fHtRatio));
		BattleInterface.ShipIcon.iconoffset5 = RecalculateHIcon(makeint(70* fHtRatio))+","+RecalculateVIcon(makeint(514* fHtRatio));
		BattleInterface.ShipIcon.iconoffset6 = RecalculateHIcon(makeint(70* fHtRatio))+","+RecalculateVIcon(makeint(626* fHtRatio));
		BattleInterface.ShipIcon.iconoffset7 = RecalculateHIcon(makeint(70* fHtRatio))+","+RecalculateVIcon(makeint(738* fHtRatio));
		BattleInterface.ShipIcon.iconoffset8 = RecalculateHIcon(makeint(70* fHtRatio))+","+RecalculateVIcon(makeint(850* fHtRatio));

		BattleInterface.CommandList.CommandMaxIconQuantity = 15; //boal
		BattleInterface.CommandList.CommandIconSpace = 1;
		BattleInterface.CommandList.CommandIconLeft = makeint(150 * fHtRatio);//157;
		BattleInterface.CommandList.CommandIconWidth = RecalculateHIcon(makeint(54 * fHtRatio));
		BattleInterface.CommandList.CommandIconHeight = RecalculateVIcon(makeint(54 * fHtRatio));

		BattleInterface.CommandList.CommandNoteFont = "interface_button";
		BattleInterface.CommandList.CommandNoteColor = argb(255,255,255,255);
		BattleInterface.CommandList.CommandNoteScale = 1.2 * fHtRatio;
		BattleInterface.CommandList.CommandNoteOffset = RecalculateHIcon(makeint(0 * fHtRatio)) + "," + RecalculateVIcon(makeint(-50 * fHtRatio));

		BattleInterface.CommandList.UDArrow_Texture = "battle_interface\arrowly.tga";
		BattleInterface.CommandList.UDArrow_UV_Up = "0.0,1.0,1.0,0.0";
		BattleInterface.CommandList.UDArrow_UV_Down = "0.0,0.0,1.0,1.0";
		BattleInterface.CommandList.UDArrow_Size = RecalculateHIcon(makeint(32 * fHtRatio)) + "," + RecalculateVIcon(makeint(32 * fHtRatio));
		BattleInterface.CommandList.UDArrow_Offset_Up = RecalculateHIcon(makeint(-36 * fHtRatio)) + "," + RecalculateVIcon(makeint(-37 * fHtRatio));
		BattleInterface.CommandList.UDArrow_Offset_Down = RecalculateHIcon(makeint(-36 * fHtRatio)) + "," + RecalculateVIcon(makeint(66 * fHtRatio));
	}
	/*BattleInterface.CommandList.ActiveIcon_Texture = "battle_interface\enter_list.tga";
	BattleInterface.CommandList.ActiveIcon_Offset = RecalculateHIcon(-49) + ",0";
	BattleInterface.CommandList.ActiveIcon_Size = RecalculateHIcon(48) + "," + RecalculateVIcon(48);
	BattleInterface.CommandList.ActiveIcon_UV1 = "0.5,0.0,1.0,1.0";
	BattleInterface.CommandList.ActiveIcon_UV2 = "0.0,0.0,0.5,1.0";
	BattleInterface.CommandList.ActiveIcon_Note = XI_ConvertString("MenuNote"); */

	BattleInterface.ShipInfoImages.RelationTexture = "battle_interface\ship_arrows1.tga";
	BattleInterface.ShipInfoImages.RelationOffset.x = 0.0;
	BattleInterface.ShipInfoImages.RelationOffset.y = 0.3;
	BattleInterface.ShipInfoImages.RelationOffset.z = 0.0;
	BattleInterface.ShipInfoImages.RelationSize = "0.75,0.5";
	BattleInterface.ShipInfoImages.RelationUV1 = "0.0,0.0,0.25,1.0"; // friend
	BattleInterface.ShipInfoImages.RelationUV2 = "0.25,0.0,0.5,1.0"; // enemy
	BattleInterface.ShipInfoImages.RelationUV3 = "0.5,0.0,0.75,1.0"; // neutral

	BattleInterface.ShipInfoImages.ProgressTexture = "battle_interface\indicators.tga"; // Индикаторы над кораблями HP/SP/CREW
	BattleInterface.ShipInfoImages.ProgressSize = "2.0,0.1"; // Цветные индикаторы

	// Задние индикаторы (тени)
	BattleInterface.ShipInfoImages.ProgressBackOffset.x = 0.0;
	BattleInterface.ShipInfoImages.ProgressBackOffset.y = 0.65;
	BattleInterface.ShipInfoImages.ProgressBackOffset.z = 0.0;
	BattleInterface.ShipInfoImages.ProgressBackSize = "2.0,0.3";
	BattleInterface.ShipInfoImages.ProgressBackUV = "0.0,0.5,1.0,1.0";

	// Корпус
	BattleInterface.ShipInfoImages.HullOffset.x = 0.0;
	BattleInterface.ShipInfoImages.HullOffset.y = 0.75;
	BattleInterface.ShipInfoImages.HullOffset.z = 0.0;
	BattleInterface.ShipInfoImages.HullUV = "0.0,0.333,1.0,0.5";

	// Паруса
	BattleInterface.ShipInfoImages.SailOffset.x = 0.0;
	BattleInterface.ShipInfoImages.SailOffset.y = 0.65;
	BattleInterface.ShipInfoImages.SailOffset.z = 0.0;
	BattleInterface.ShipInfoImages.SailUV = "0.0,0.167,1.0,0.333";

	// Команда
	BattleInterface.ShipInfoImages.CrewOffset.x = 0.0;
	BattleInterface.ShipInfoImages.CrewOffset.y = 0.55;
	BattleInterface.ShipInfoImages.CrewOffset.z = 0.0;
	BattleInterface.ShipInfoImages.CrewUV = "0.0,0.0,1.0,0.166";

	BattleInterface.ShifInfoVisible = InterfaceStates.enabledshipmarks;
	LanguageCloseFile(idLngFile);
}

ref ProcessSailDamage()
{
	// от кого удар
	int shootIdx = GetEventData();
	// перс
	int chrIdx = GetEventData();

	string sMastName = GetEventData();
	// координаты паруса
	string reyName = GetEventData();
	int groupNum = GetEventData();
	// данные о дырках
	int holeCount = GetEventData();
	int holeData = GetEventData();
	int maxHoleCount = GetEventData();
	// мощность паруса
	float sailPower = GetEventData();

	ref chref = GetCharacter(chrIdx);
	if (CheckAttribute(&RealShips[sti(chref.Ship.Type)], "Tuning.SailsSpecial") && rand(2)<1)
	{
		BI_g_fRetVal = 0;
		return &BI_g_fRetVal;
	}

	if (LAi_IsImmortal(chref))
	{
		BI_g_fRetVal = 0;
		return &BI_g_fRetVal;
	}

	string groupName = ""+groupNum;
	aref arSail;
	makearef(arSail,chref.ship.sails.(reyName).(groupName));

	float sailDmg = 0.0;
	float sailDmgMax = GetCharacterShipSP(chref) * sailPower;
	if( !CheckAttribute(arSail,"dmg") )	{ sailDmg = 0.0; }

	if(sMastName=="*")
	{
		sailDmg = sailDmg + GetRigDamage(shootIdx,sti(AIBalls.CurrentBallType),chref);
		if(sailDmg>sailDmgMax)	{ sailDmg = sailDmgMax; }
		int needHole = GetNeedHoleFromDmg(sailDmg,sailDmgMax,maxHoleCount);
		if(holeCount!=needHole)
		{
			if(holeCount<needHole)
			{
				holeData = RandomHole2Sail(chrIdx,reyName,groupNum, maxHoleCount, holeData, needHole-holeCount);
				holeCount = needHole;
			}
			else
			{
				sailDmg = GetNeedDmgFromHole(holeCount,sailDmgMax,maxHoleCount);
			}
		}
	}
	else
	{
		if(sMastName!="#")	{ arSail.mastFall = sMastName; }
		sailDmg = sailDmgMax;
	}

	/*if (sailDmg < 0.5)
	{
		Log_SetStringtoLog("MUST DIE!!! " + sailDmg);
	}*/

	arSail.hc = holeCount;
	arSail.hd = holeData;
	arSail.mhc = maxHoleCount;
	arSail.sp = sailPower;
	arSail.dmg = sailDmg;

	chref.ship.SP = CalculateShipSP(chref);
	BI_g_fRetVal = sailDmg;
	return &BI_g_fRetVal;
}

void ProcessDayRepair()
{
	int i, cn;
	float matQ, tmpf, repPercent;
	ref chref;
	ref mchar = GetMainCharacter();
	// boal 21.01.2004 на лету в море не чиним, тк идут дни прям в море -->
	if (bSeaActive == false || mchar.location == mchar.SystemInfo.CabinType) // спим в каюте
	{
		for (i=0; i<COMPANION_MAX; i++)
		{
			cn = GetCompanionIndex(mchar,i);
			if(cn==-1) continue;
			chref = GetCharacter(cn);

			// расчет починки корпуса
			if (GetHullPercent(chref)<100.0 )
			{
				repPercent = GetHullRPD(chref);
				matQ = repPercent*GetHullPPP(chref);
				tmpf = GetRepairGoods(true,chref);
				if (tmpf > 0)
				{
					if (tmpf < matQ)	{ repPercent = tmpf/GetHullPPP(chref); }
					repPercent = ProcessHullRepair(chref, repPercent);
					matQ = repPercent*GetHullPPP(chref);
					RemoveRepairGoods(true,chref,matQ);
					// boal  check skill -->
		            AddCharacterExpToSkill(chref, "Repair", matQ / 3.0);
		            // boal <--
	            }
			}

			// расчет починки парусов
			if (GetSailPercent(chref)<100.0 )
			{
				repPercent = GetSailRPD(chref);
				matQ = repPercent*GetSailSPP(chref);
				tmpf = GetRepairGoods(false,chref);
				if (tmpf > 0)
				{
					if (tmpf < matQ)	{ repPercent = tmpf/GetSailSPP(chref); }
					repPercent = ProcessSailRepair(chref,repPercent);
					matQ = repPercent*GetSailSPP(chref);
					RemoveRepairGoods(false,chref,matQ);
					// boal  check skill -->
		            AddCharacterExpToSkill(chref, "Repair", matQ / 4.0);
		            // boal <--
	            }
			}
		}
	}
	// boal 21.01.2004 <--
}

ref procGetSailTextureData()
{
	int st,i,sq;
	ref shref;
	aref arEmbl,arSail;
	string attrName;
	int iUpgrade;
	string sUpgrade;
	string nationFileName;
	string tmpStr;

	int chrIdx = GetEventData();

	DeleteAttribute(&BI_objRetValue,"");
	if (bNewSails)
	{
		if (chrIdx>=0)
		{
			st = GetCharacterShipType(GetCharacter(chrIdx));
			if (st != SHIP_NOTUSED)
			{
				sUpgrade = "common";

				shref = GetRealShip(st);

				iUpgrade = sti(shref.ship.upgrades.sails);
				switch(iUpgrade)
				{
					case 1:	sUpgrade = "common";	break; // LEO: --> Все корабли используют
					case 2: sUpgrade = "pat";		break;
					case 3:	sUpgrade = "silk";		break;
					case 4: sUpgrade = "silkblack";	break; // Sea Boss
					case 5:	sUpgrade = "usual_1";	break;
					case 6:	sUpgrade = "usual_2";	break;
					case 7:	sUpgrade = "usual_3";	break;
					case 8:	sUpgrade = "usual_4";	break;
					case 9:	sUpgrade = "usual_5";	break;
					case 10:sUpgrade = "usual_6";	break;
					case 11:sUpgrade = "usual_7";	break;
					case 12:sUpgrade = "usual_8";	break;
					case 13:sUpgrade = "usual_9";	break;
					case 14:sUpgrade = "usual_10";	break;
					case 15:sUpgrade = "usual_11";	break;
					case 16:sUpgrade = "usual_12";	break;
					case 17:sUpgrade = "usual_13";	break;
					case 18:sUpgrade = "usual_14";	break;
					case 19:sUpgrade = "usual_15";	break;
					case 20:sUpgrade = "usual_16";	break;
					case 21:sUpgrade = "usual_17";	break;
					case 22:sUpgrade = "usual_18";	break;
					case 23:sUpgrade = "usual_19";	break;
					case 24:sUpgrade = "usual_20";	break;
					case 25:sUpgrade = "usual_21";	break;
					case 26:sUpgrade = "usual_22";	break;
					case 27:sUpgrade = "usual_23";	break;
					case 28:sUpgrade = "usual_24";	break;
					case 29:sUpgrade = "usual_25";	break;
					case 30:sUpgrade = "usual_26";	break;
					case 31:sUpgrade = "usual_27";	break;
					case 32:sUpgrade = "usual_28";	break;
					case 33:sUpgrade = "usual_29";	break;
					case 34:sUpgrade = "usual_30";	break;
					case 35:sUpgrade = "usual_31";	break;
					case 36:sUpgrade = "usual_32";	break;
					case 37:sUpgrade = "usual_33";	break; // LEO: <-- Все корабли используют

					case 38:sUpgrade = "sail_torn_black_pirate_1";		break; // LEO: --> Только пираты
					case 39:sUpgrade = "sail_torn_black_pirate_2";		break;
					case 40:sUpgrade = "sail_torn_black_pirate_3";		break;
					case 41:sUpgrade = "sail_torn_black_pirate_4";		break;
					case 42:sUpgrade = "sail_torn_black_pirate_5";		break;
					case 43:sUpgrade = "sail_torn_black_pirate_6";		break;
					case 44:sUpgrade = "sail_torn_black_pirate_7";		break;
					case 45:sUpgrade = "sail_torn_black_pirate_8";		break;
					case 46:sUpgrade = "sail_torn_black_pirate_9";		break;
					case 47:sUpgrade = "sail_torn_black_pirate_10";		break;
					case 48:sUpgrade = "sail_torn_black_pirate_11";		break;
					case 49:sUpgrade = "sail_torn_black_pirate_12";		break;
					case 50:sUpgrade = "sail_torn_black_pirate_13";		break;
					case 51:sUpgrade = "sail_torn_black_pirate_14";		break;
					case 52:sUpgrade = "sail_whole_black_pirate_1";		break;
					case 53:sUpgrade = "sail_whole_black_pirate_2";		break;
					case 54:sUpgrade = "sail_whole_black_pirate_3";		break;
					case 55:sUpgrade = "sail_whole_black_pirate_4";		break;
					case 56:sUpgrade = "sail_whole_black_pirate_5";		break;
					case 57:sUpgrade = "sail_whole_black_pirate_6";		break;
					case 58:sUpgrade = "sail_whole_black_pirate_7";		break;
					case 59:sUpgrade = "sail_whole_black_pirate_8";		break;
					case 60:sUpgrade = "sail_whole_black_pirate_9";		break;
					case 61:sUpgrade = "sail_whole_black_pirate_10";	break;
					case 62:sUpgrade = "sail_whole_black_pirate_11";	break;
					case 63:sUpgrade = "sail_whole_black_pirate_12";	break;
					case 64:sUpgrade = "sail_whole_black_pirate_13";	break;
					case 65:sUpgrade = "sail_whole_black_pirate_14";	break;
					case 66:sUpgrade = "sail_whole_black_pirate_15";	break;
					case 67:sUpgrade = "sail_whole_black_pirate_16";	break;
					case 68:sUpgrade = "sail_whole_black_pirate_17";	break;
					case 69:sUpgrade = "sail_whole_white_pirate_1";		break;
					case 70:sUpgrade = "sail_whole_white_pirate_2";		break;
					case 71:sUpgrade = "sail_whole_white_pirate_3";		break;
					case 72:sUpgrade = "sail_whole_white_pirate_4";		break;
					case 73:sUpgrade = "sail_whole_white_pirate_5";		break;
					case 74:sUpgrade = "sail_whole_white_pirate_6";		break;
					case 75:sUpgrade = "sail_whole_white_pirate_7";		break;
					case 76:sUpgrade = "sail_whole_white_pirate_8";		break;
					case 77:sUpgrade = "sail_whole_white_pirate_9";		break;
					case 78:sUpgrade = "sail_whole_white_pirate_10";	break;
					case 79:sUpgrade = "sail_whole_white_pirate_11";	break;
					case 80:sUpgrade = "sail_whole_white_pirate_12";	break;
					case 81:sUpgrade = "sail_whole_white_pirate_13";	break;
					case 82:sUpgrade = "sail_whole_white_pirate_14";	break;
					case 83:sUpgrade = "sail_whole_white_pirate_15";	break;
					case 84:sUpgrade = "sail_whole_white_pirate_16";	break;
					case 85:sUpgrade = "sail_whole_white_pirate_17";	break;
					case 86:sUpgrade = "sail_whole_white_pirate_18";	break;
					case 87:sUpgrade = "sail_whole_white_pirate_19";	break;
					case 88:sUpgrade = "sail_whole_white_pirate_20";	break; // LEO: <-- Только пираты
					case 89:sUpgrade = "common_torn";					break;
					case 90:sUpgrade = "common_torn1";					break;
					case 91:sUpgrade = "common_torn2";					break;
				}
				nationFileName = "ships\parus_" + sUpgrade + ".tga";

				BI_objRetValue.normalTex = nationFileName;
				BI_objRetValue.geraldTex = "";//"ships\gerald\chuckskull.tga";
				BI_objRetValue.sailscolor = argb(255,255,255,255);  // белый парус

				if (CheckAttribute(shref, "ShipSails.SailsColor")) // 1.2.3 цвет теперь атрибут корабля, а не НПС
				{
					BI_objRetValue.sailscolor = sti(shref.ShipSails.SailsColor);
				}
				//if( CheckAttribute(&characters[chrIdx],"ShipSails.gerald_name") ) // не наследуется при обмене кораблей, потому не в  ship.
				if( CheckAttribute(shref,"ShipSails.gerald_name") ) // 1.2.3 герб теперь атрибут корабля, а не НПС
				{
					BI_objRetValue.geraldTex = "Ships\Gerald\" + shref.ShipSails.gerald_name + ".tga";
				}

				BI_objRetValue.maxSP = shref.sp;
				// boal -->
				if (CheckAttribute(shref, "EmblemedSails.normalTex")) // заднанный в типе парус
				{
					BI_objRetValue.normalTex = shref.EmblemedSails.normalTex;
					nationFileName           = shref.EmblemedSails.normalTex;
				}
				if( CheckAttribute(&Characters[chrIdx],"Features.GeraldSails") && sti(Characters[chrIdx].Features.GeraldSails)==true)
				{
					makearef(arEmbl,shref.GeraldSails);
				} else {
					makearef(arEmbl,shref.EmblemedSails);
				}
				sq = GetAttributesNum(arEmbl);
				for(i=0; i<sq; i++)
				{
					arSail = GetAttributeN(arEmbl,i);
					attrName = GetAttributeName(arSail);
					tmpStr = GetAttributeValue(arSail);
					if( CheckAttribute(arSail,"hscale") ) {
						BI_objRetValue.(attrName).hscale = arSail.hscale;
					}
					if( CheckAttribute(arSail,"vscale") ) {
						BI_objRetValue.(attrName).vscale = arSail.vscale;
					}
					if(tmpStr=="1") {
						//BI_objRetValue.(attrName).Gerald = nationFileName;
						BI_objRetValue.(attrName) = nationFileName;
					} else {
						BI_objRetValue.(attrName).Gerald = tmpStr;
					}
				}
			}
		}
	}
	else
	{
		if (chrIdx>=0)
		{
			st = GetCharacterShipType(GetCharacter(chrIdx));
			if (st != SHIP_NOTUSED)
			{
				sUpgrade = "common";

				shref = GetRealShip(st);

				iUpgrade = sti(shref.ship.upgrades.sails);
				switch(iUpgrade)
				{
					case 1:	sUpgrade = "common";	break; // LEO: --> Все корабли используют
					case 2: sUpgrade = "pat";		break;
					case 3:	sUpgrade = "silk";		break;
					case 4: sUpgrade = "silkblack";	break;
					case 5:	sUpgrade = "usual_1";	break;
					case 6:	sUpgrade = "usual_2";	break;
					case 7:	sUpgrade = "usual_3";	break;
					case 8:	sUpgrade = "usual_4";	break;
					case 9:	sUpgrade = "usual_5";	break;
					case 10:sUpgrade = "usual_6";	break;
					case 11:sUpgrade = "usual_7";	break;
					case 12:sUpgrade = "usual_8";	break;
					case 13:sUpgrade = "usual_9";	break;
					case 14:sUpgrade = "usual_10";	break;
					case 15:sUpgrade = "usual_11";	break;
					case 16:sUpgrade = "usual_12";	break;
					case 17:sUpgrade = "usual_13";	break;
					case 18:sUpgrade = "usual_14";	break;
					case 19:sUpgrade = "usual_15";	break;
					case 20:sUpgrade = "usual_16";	break;
					case 21:sUpgrade = "usual_17";	break;
					case 22:sUpgrade = "usual_18";	break;
					case 23:sUpgrade = "usual_19";	break;
					case 24:sUpgrade = "usual_20";	break;
					case 25:sUpgrade = "usual_21";	break;
					case 26:sUpgrade = "usual_22";	break;
					case 27:sUpgrade = "usual_23";	break;
					case 28:sUpgrade = "usual_24";	break;
					case 29:sUpgrade = "usual_25";	break;
					case 30:sUpgrade = "usual_26";	break;
					case 31:sUpgrade = "usual_27";	break;
					case 32:sUpgrade = "usual_28";	break;
					case 33:sUpgrade = "usual_29";	break;
					case 34:sUpgrade = "usual_30";	break;
					case 35:sUpgrade = "usual_31";	break;
					case 36:sUpgrade = "usual_32";	break;
					case 37:sUpgrade = "usual_33";	break; // LEO: <-- Все корабли используют
					else sUpgrade = "common";	break;
				}
				nationFileName = "ships\parus_" + sUpgrade + ".tga";

				BI_objRetValue.normalTex = nationFileName;
				BI_objRetValue.geraldTex = "";//"ships\gerald\chuckskull.tga";
				BI_objRetValue.sailscolor = argb(255,255,255,255);  // белый парус

				if (CheckAttribute(shref, "ShipSails.SailsColor")) // 1.2.3 цвет теперь атрибут корабля, а не НПС
				{
					BI_objRetValue.sailscolor = sti(shref.ShipSails.SailsColor);
				}
				//if( CheckAttribute(&characters[chrIdx],"ShipSails.gerald_name") ) // не наследуется при обмене кораблей, потому не в  ship.
				if( CheckAttribute(shref,"ShipSails.gerald_name") ) // 1.2.3 герб теперь атрибут корабля, а не НПС
				{
					BI_objRetValue.geraldTex = "Ships\Gerald\" + shref.ShipSails.gerald_name + ".tga";
				}
				BI_objRetValue.maxSP = shref.sp;
				// boal -->
				if (CheckAttribute(shref, "EmblemedSails.normalTex")) // заднанный в типе парус
				{
					BI_objRetValue.normalTex = shref.EmblemedSails.normalTex;
					nationFileName           = shref.EmblemedSails.normalTex;
				}
				if( CheckAttribute(&Characters[chrIdx],"Features.GeraldSails") && sti(Characters[chrIdx].Features.GeraldSails)==true)
				{
					makearef(arEmbl,shref.GeraldSails);
				} else {
					makearef(arEmbl,shref.EmblemedSails);
				}
				/*if (CheckAttribute(shref, "GeraldSails"))
				{
					makearef(arEmbl, shref.GeraldSails);  */
					// boal <--
				sq = GetAttributesNum(arEmbl);
				for(i=0; i<sq; i++)
				{
					arSail = GetAttributeN(arEmbl,i);
					attrName = GetAttributeName(arSail);
					tmpStr = GetAttributeValue(arSail);
					if( CheckAttribute(arSail,"hscale") ) {
						BI_objRetValue.(attrName).hscale = arSail.hscale;
					}
					if( CheckAttribute(arSail,"vscale") ) {
						BI_objRetValue.(attrName).vscale = arSail.vscale;
					}
					if(tmpStr=="1") {
						//BI_objRetValue.(attrName).Gerald = nationFileName;
						BI_objRetValue.(attrName) = nationFileName;
					} else {
						BI_objRetValue.(attrName).Gerald = tmpStr;
					}
				}
				//}
			}
		}
	}
	return &BI_objRetValue;
}

ref procGetRiggingData()
{
	int i,n;

	int retVal = 0;

	string datName = GetEventData();
	i = GetEventData();
    n = GetEventData();
    //aref chr = GetEventData();

	if(true) //tName=="GetFlagTexNum")
	{
		if(i==true)
		{
			switch(n)
			{
			case ENGLAND: retVal = 1; break;
			case FRANCE: retVal = 2; break;
			case SPAIN: retVal = 4; break;
			case PIRATE: retVal = 5; break;
			case HOLLAND: retVal = 0; break;
			//case SMUGGLER: retVal = 3; break;
			}
		}
		else
		{
			switch(n)
			{
			case ENGLAND: retVal = 1; break;
			case FRANCE: retVal = 2; break;
			case SPAIN: retVal = 4; break;
			case PIRATE: retVal = 5; break;
			case HOLLAND: retVal = 0; break;
			//case SMUGGLER: retVal = 3; break;
			}
		}
	}
	if(datName == "PENNANT")
	{
		switch(n)
		{
			case HOLLAND: retVal = rand(2); break;
			case ENGLAND: retVal = 3 + rand(2); break;
			case FRANCE: retVal = 6 + rand(2); break;
			case SPAIN: retVal = 9 + rand(2); break;
			case PIRATE: retVal = 12 + rand(2); break;
			retVal = 18;
		}
    }
	return &retVal;
}

void procBISelectShip()
{
	int chrIdx = GetEventData();
	int isMyChr = GetEventData();

	if(chrIdx==nMainCharacterIndex)	chrIdx = -1;

	float fShSpeed = 0.005;
	float fShAmp = 1.0;
	float fShW = 1.0;
	float fShH = 1.0;
	float fTop = 5.0;

	SendMessage(&objShipPointer,"lllfffff",MSG_SP_CHANGESHIP,chrIdx,isMyChr,fShSpeed,fShAmp,fShW,fShH,fTop);
}

ref procGetSmallFlagData()
{
	int chrIdx = GetEventData();
	BI_intNRetValue[0] = 3;
	BI_intNRetValue[1] = 0;
	if( chrIdx >= 0 ) {
		int iNation = sti(Characters[chrIdx].nation);
		switch( iNation )
		{
		case ENGLAND: BI_intNRetValue[1]=3; break;
		case FRANCE: BI_intNRetValue[1]=2; break;
		case SPAIN: BI_intNRetValue[1]=0; break;
		case HOLLAND: BI_intNRetValue[1]=4; break;
		case PIRATE: BI_intNRetValue[1]=5; break;
		//case SMUGGLER: BI_intNRetValue[1]=1; break;
		}

		BI_intNRetValue[2] = 7;
		switch( SeaAI_GetRelation(chrIdx,nMainCharacterIndex) )
		{
			case RELATION_FRIEND:	BI_intNRetValue[2] = 7; break;
			case RELATION_NEUTRAL:	BI_intNRetValue[2] = 7; break;
			case RELATION_ENEMY:	BI_intNRetValue[2] = 6; break;
		}
	}
	return &BI_intNRetValue;
}

void procMastFall()
{
	int chrIdx = GetEventData();
	string mastName = GetEventData();
	int bFirstFall = GetEventData();

	if(chrIdx<0) return;
	int mastNum = strcut(mastName,4,strlen(mastName)-1);

	//trace("For character "+chrIdx+" fall Mast name "+mastName+" has index "+mastNum);
	SendMessage(&Sailors, "lal", MSG_PEOPLES_ON_SHIP_MASTFALL, GetCharacter(chrIdx), mastNum);
}

bool CheckInstantRepairCondition(ref chref)
{
//boal -->
    if (CheckOfficersPerk(chref,"InstantRepair")) return false;  // уже в деле
    if (!GetOfficersPerkUsing(chref,"InstantRepair")) return false;  // можно включить?
//boal <--

	float chrShipHP = GetHullPercent(chref);
	float chrShipSP = GetSailPercent(chref);

	bool bYesHPRepair = chrShipHP < InstantRepairRATE;// boal 23.01.2004
	bool bYesSPRepair = chrShipSP < InstantRepairRATEsail; //bestreducer быстрая починка// boal 23.01.2004

	if( bYesHPRepair )	{ bYesHPRepair = GetCargoGoods(chref,GOOD_PLANKS)>0; }
	if( bYesSPRepair )	{ bYesSPRepair = GetCargoGoods(chref,GOOD_SAILCLOTH)>0; }

	return bYesHPRepair || bYesSPRepair;
}

void BI_PerkAgainUsable()
{
	BI_SetCommandMode(-1,-1,-1,-1);
}

float GetRepairGoods(bool bIsHull, ref chref)
{
	float fGoodsQ = 0.0;

	if( bIsHull )
	{
		fGoodsQ = GetCargoGoods(chref,GOOD_PLANKS);
		if( CheckAttribute(chref,"RepairMaterials.forHull") )   // погрешность округления списания колва досок за процент
		{
			fGoodsQ += stf(chref.RepairMaterials.forHull);
		}
	}
	else
	{
		fGoodsQ = GetCargoGoods(chref,GOOD_SAILCLOTH);
		if( CheckAttribute(chref,"RepairMaterials.forSails") )
		{
			fGoodsQ += stf(chref.RepairMaterials.forSails);
		}
	}
	return fGoodsQ;
}

void RemoveRepairGoods(bool bIsHull, ref chref, float matQ)
{
	int nGoodsQ = 0;
	float fGoodsQ = GetRepairGoods(bIsHull,chref);

	if( bIsHull )
	{
		if(fGoodsQ<=matQ)	{ DeleteAttribute(chref,"RepairMaterials.forHull"); }
		else
		{
			fGoodsQ -= matQ;
			nGoodsQ = makeint(fGoodsQ);
			chref.RepairMaterials.forHull = fGoodsQ - nGoodsQ;
		}
		SetCharacterGoods(chref,GOOD_PLANKS,nGoodsQ);
	}
	else
	{
		if(fGoodsQ<=matQ)	{ DeleteAttribute(chref,"RepairMaterials.forSails"); }
		else
		{
			fGoodsQ -= matQ;
			nGoodsQ = makeint(fGoodsQ);
			chref.RepairMaterials.forSails = fGoodsQ - nGoodsQ;
		}
		SetCharacterGoods(chref,GOOD_SAILCLOTH,nGoodsQ);
	}
}

float GetRigDamage(int shootIdx, int iBallType, ref damage_chr)
{
	ref rBall = GetGoodByType(iBallType);
	float fDistanceDamageMultiply = Bring2Range(1.2, 0.25, 0.0, stf(AIBalls.CurrentMaxBallDistance), stf(AIBalls.CurrentBallDistance));
	float fDmgRig = fDistanceDamageMultiply * stf(rBall.DamageRig);
	//float fDmgRig = stf(rBall.DamageRig);
    if (shootIdx>=0 )
	{
		ref shoot_chr = GetCharacter(shootIdx);
		if (CheckOfficersPerk(shoot_chr,"CannonProfessional") )	{ fDmgRig *= 1.3; }
		else
		{
			if( CheckOfficersPerk(shoot_chr,"SailsDamageUp") )	{ fDmgRig *= 1.15; }
		}
	}

	if (CheckOfficersPerk(damage_chr,"ShipDefenseProfessional") )	{ fDmgRig *= 0.65; } // fix
	else
	{
		if (CheckOfficersPerk(damage_chr,"AdvancedBattleState") )	{ fDmgRig *= 0.75; } // fix
		else
		{
			if (CheckOfficersPerk(damage_chr,"BasicBattleState") )	{ fDmgRig *= 0.85; } // fix
		}
	}
	return fDmgRig;
}

void MakeSailDmg(int chrIdx, float dmg)
{
	object objSail;
	if( !GetEntity(&objSail,"sail") )
	{
		return;
	}
	if (CheckAttribute(&RealShips[sti(characters[chrIdx].Ship.Type)], "Tuning.SailsSpecial") && rand(4)>1) return;
	int iSailsUpgrade = 1;
	if(!CheckAttribute(&characters[chrIdx], "upgrades.sails"))
	{
		characters[chrIdx].upgrades.sails = 1;
	}
	//убираем 1 вариант апгрейда (паруса по умолчанию))
	iSailsUpgrade = sti(characters[chrIdx].upgrades.sails) - 1;
	dmg = dmg + ((dmg/100)*iSailsUpgrade*5);
	SendMessage(&objSail,"lslf", MSG_SAIL_SCRIPT_PROCESSING,"RandomSailsDmg", chrIdx,dmg);
}

ref ProcessRandomSailDmg()
{
	BI_g_fRetVal = 0.0;
	//"lslfflll"
	int chrIdx = GetEventData();
	string nodeName = GetEventData();
	int grNum = GetEventData();
	float fDmg = GetEventData();
	float fSPow = GetEventData();
	int hc_new = GetEventData();
	int mhc = GetEventData();
	int hdat_new = GetEventData();

	if(chrIdx<0) return &BI_g_fRetVal;
	ref chref = GetCharacter(chrIdx);

	aref arSail;
	string groupName = ""+grNum;
	makearef(arSail,chref.ship.sails.(nodeName).(groupName));

	int hc_old = 0;
	if( CheckAttribute(arSail,"hc") )	hc_old = sti(arSail.hc);
	float fDmg_old = 0.0;
	if( CheckAttribute(arSail,"dmg") )	fDmg_old = stf(arSail.dmg);

	int itmp = hc_new;
	float sailDmgMax = GetCharacterShipSP(chref) * fSPow;

	float fTopDmg = sailDmgMax;
	if(itmp<mhc)	fTopDmg = GetNeedDmgFromHole(itmp+1,sailDmgMax,mhc) - 0.0001;
	if(fTopDmg>fDmg_old+fDmg)	fTopDmg = fDmg_old+fDmg;

	fDmg = fTopDmg-fDmg_old;
	if(fDmg<=0.0)	return &BI_g_fRetVal;
	chref.ship.SP = stf(chref.ship.SP)-fDmg;

	itmp = GetNeedHoleFromDmg(fTopDmg,sailDmgMax,mhc);
	if(itmp>hc_old)
	{
		BI_g_fRetVal = fDmg;
		arSail.hc = hc_new;
		arSail.hd = hdat_new;
	}
	else
	{
		BI_g_fRetVal = -fDmg;
		if( !CheckAttribute(arSail,"hc") )	arSail.hc = 0;
		if( !CheckAttribute(arSail,"hd") )	arSail.hd = 0;
	}

	arSail.mhc = mhc;
	arSail.sp = fSPow;
	arSail.dmg = fTopDmg;

	return &BI_g_fRetVal;
}

void procSetUsingAbility()
{
	//Log_Info("procSetUsingAbility");
	int q;
	int chIdx = GetEventData();
	int mainIdx = sti(pchar.index);
	aref aroot,arcur;
	string tmpStr;

	if( chIdx<0 || CharacterIsDead(GetCharacter(chIdx)) )
	{
		makearef(aroot,BattleInterface.AbilityIcons);
		q = GetAttributesNum(aroot);
		for(int i=0; i<q; i++)
		{
			arcur = GetAttributeN(aroot,i);
			arcur.enable = false;
		}
		return;
	}

	// для главного персонажа
	if(mainIdx==chIdx)
	{
        BattleInterface.Commands.Bomb.enable = true;
		BattleInterface.Commands.Brander.enable			= false;
		//BattleInterface.AbilityIcons.Troopers.enable		= false;

        //if (bBettaTestMode) BattleInterface.AbilityIcons.InstantBoarding.enable	= bAttack;

		BattleInterface.Commands.ImmediateReload.enable	= false; //GetCharacterPerkUsing
        if (!CheckOfficersPerk(pchar, "ImmediateReload") && GetOfficersPerkUsing(pchar, "ImmediateReload"))
        {
            BattleInterface.Commands.ImmediateReload.enable = true;
        }
		BattleInterface.Commands.LightRepair.enable		= false;
		if (!CheckOfficersPerk(pchar, "LightRepair") && GetOfficersPerkUsing(pchar,"LightRepair"))
		{
            if(GetHullPercent(pchar)<10.0 || GetSailPercent(pchar)<10.0)
			{
                BattleInterface.Commands.LightRepair.enable = true;
			}
		}
		BattleInterface.Commands.InstantRepair.enable	= CheckInstantRepairCondition(pchar);
		BattleInterface.Commands.Turn180.enable = false;
		if (!CheckOfficersPerk(pchar, "Turn180") && GetOfficersPerkUsing(pchar, "Turn180"))
        {
			BattleInterface.Commands.Turn180.enable = true;
        }
        BattleInterface.Commands.SandbankManeuver.enable = false;
        if (!CheckOfficersPerk(pchar, "SandbankManeuver") && GetOfficersPerkUsing(pchar, "SandbankManeuver"))
        {
            BattleInterface.Commands.SandbankManeuver.enable = true;
        }
		// Set items abilities
		q = FindQuestUsableItem(&arcur,0);
		while( q>0 )
		{
			tmpStr = arcur.id;
			if( GetCharacterItem(pchar,arcur.id)>0 )
			{
				BattleInterface.AbilityIcons.(tmpStr).enable	= true;
				BattleInterface.AbilityIcons.(tmpStr).picNum	= arcur.quest.pic;
				BattleInterface.AbilityIcons.(tmpStr).texNum	= 9;
				BattleInterface.AbilityIcons.(tmpStr).event		= arcur.id;
				BattleInterface.AbilityIcons.(tmpStr).quest		= arcur.quest;
			}
			else
			{
				BattleInterface.AbilityIcons.(tmpStr).enable	= false;
			}
			q = FindQuestUsableItem(&arcur,q+1);
		}
	}

	else
	{
		BattleInterface.Commands.Brander.enable			= false;
		BattleInterface.Commands.Bomb.enable = true;
		if(bAttack && GetRemovable(GetCharacter(chIdx)) && GetOfficersPerkUsing(pchar,"Brander"))
		{
			BattleInterface.Commands.Brander.enable		= true;
		}
		//BattleInterface.AbilityIcons.Troopers.enable		= GetCharacterPerkUsing(pchar,"Troopers");

		BattleInterface.Commands.InstantRepair.enable	= false;
		BattleInterface.Commands.InstantRepair.enable	= CheckInstantRepairCondition(GetCharacter(chIdx));
		BattleInterface.Commands.ImmediateReload.enable	= GetCharacterPerkUsing(GetCharacter(chIdx), "ImmediateReload");//false;
		BattleInterface.Commands.InstantBoarding.enable	= false;
		BattleInterface.Commands.LightRepair.enable		= GetCharacterPerkUsing(GetCharacter(chIdx), "LightRepair");//false;
		if (GetCharacterPerkUsing(GetCharacter(chIdx),"LightRepair"))
		{
            if(GetHullPercent(GetCharacter(chIdx))<10.0 || GetSailPercent(GetCharacter(chIdx))<10.0)
			{
                BattleInterface.Commands.LightRepair.enable = true;
			}
		}
		BattleInterface.Commands.Turn180.enable			= GetCharacterPerkUsing(GetCharacter(chIdx), "Turn180");//false;
	}
}

ref procCheckEnableLocator()
{
	BI_intRetValue = true;

	string comName = GetEventData();
	aref arLoc = GetEventData();

	if(comName=="BI_SailTo")
	{
		if( CheckAttribute(&AISea,"Island") && CheckAttribute(arLoc,"name") )
		{
			BI_intRetValue = Island_isGotoEnableLocal(AISea.Island,arLoc.name);
		}
	}

	return &BI_intRetValue;
}

ref procCheckEnableShip()
{
	BI_intRetValue = true;

	string comName = GetEventData();
	int cn = GetEventData();

	ref rCommander;

	if(cn>=0)
	{
		switch(comName)
		{
		case "BI_InstantBoarding":
			BI_intRetValue = true;
		break;

		case "BI_Speak":
			BI_intRetValue = true;
		break;
		}
	}

	return &BI_intRetValue;
}

void BI_ProcessControlPress()
{
	string ControlName = GetEventData();
	if( sti(InterfaceStates.Launched) != 0 ) {return;}

	switch(ControlName)
	{
		case "hk_charge1":
			PlayVoice("interface\_balls.wav");
			Ship_ChangeCharge(pchar, GOOD_BALLS);
		break;
		case "hk_charge2":
			PlayVoice("interface\_grapes.wav");
			Ship_ChangeCharge(pchar, GOOD_GRAPES);
		break;
		case "hk_charge3":
			PlayVoice("interface\_chain.wav");
			Ship_ChangeCharge(pchar, GOOD_KNIPPELS);
		break;
		case "hk_charge4":
			PlayVoice("interface\_bombs.wav");
			Ship_ChangeCharge(pchar, GOOD_BOMBS);
		break;
		case "BICommandsActivate":
			PlaySound("interface\ok.wav"); // boal даешь звуки!
		break;
	}
}

ref procGetSRollSpeed()
{
	int chrIdx = GetEventData();
	BI_g_fRetVal = 0.0;
	if(chrIdx>=0) BI_g_fRetVal = GetRSRollSpeed(GetCharacter(chrIdx));
	return &BI_g_fRetVal;
}
// скорость подъема паруса
float GetRSRollSpeed(ref chref)
{
	int iShip = sti(chref.ship.type);
	if( iShip<0 || iShip>=REAL_SHIPS_QUANTITY ) {return 0.0;}

	float fRollSpeed = 0.5 + 0.05 * makefloat( GetSummonSkillFromNameToOld(chref,SKILL_SAILING) ); //fix skill
	int crewQ = GetCrewQuantity(chref);
	//int crewMin = sti(RealShips[iShip].MinCrew);
	if (!CheckAttribute(&RealShips[iShip], "MaxCrew"))
	{
		Log_TestInfo("GetRSRollSpeed нет MaxCrew у корабля НПС ID=" + chref.id);
		return 0.0;
	}
 	int crewMax = sti(RealShips[iShip].MaxCrew);
 	int crewOpt = sti(RealShips[iShip].OptCrew);//boal
 	if (crewMax < crewQ) crewQ  = crewMax; // boal
	//if(crewQ < crewMin) fRollSpeed *= makefloat(crewQ)/makefloat(2*crewMin);
	//fRollSpeed = fRollSpeed * (0.5 + makefloat(crewQ)/makefloat(2*crewMax)); // уменьшение скорости разворота от команды
	//fRollSpeed = fRollSpeed * makefloat(crewQ)/makefloat(crewMax);
	// опыт матросов
	float  fExp;

	if (crewOpt <= 0) crewOpt = 0; // fix для профилактики деления на ноль

	fExp = 0.05 + stf(GetCrewExp(chref, "Sailors") * crewQ) / stf(crewOpt * GetCrewExpRate());
	if (fExp > 1) fExp = 1;
	fRollSpeed = fRollSpeed * fExp;
	// мораль
	float  fMorale = stf(stf(GetCharacterCrewMorale(chref)) / MORALE_MAX);
	fRollSpeed = fRollSpeed * (0.7 + fMorale / 2.0);

	if (iArcadeSails != 1)
	{
		fRollSpeed = fRollSpeed / 2.5;
	}
	if(CheckOfficersPerk(chref, "SailsMan"))
	{
		fRollSpeed = fRollSpeed * 1.1; // 10 процентов
	}
	if (CheckAttribute(&RealShips[iShip],"Tuning.SailsSpecial")) fRollSpeed = fRollSpeed * 1.25;
	return fRollSpeed;
}

ref BI_GetLandData()
{
	int iTmp;
	string attrName;
	aref arLoc, arIsl, arList;
	arLoc = GetEventData();

	BI_intNRetValue[0] = 0;
	BI_intNRetValue[1] = BI_RELATION_NEUTRAL;
	BI_intNRetValue[2] = -1;
	BI_intNRetValue[3] = -1;
	BI_intNRetValue[4] = -1;
	BI_intNRetValue[5] = -1;
	BI_intNRetValue[6] = -1;

	if( CheckAttribute(arLoc,"fort.model") )
	{
		BI_intNRetValue[0] = 1; // тип форт
		int chrIdx = Fort_FindCharacter(AISea.Island,"reload",arLoc.name);
		if(chrIdx>=0)
		{
			switch( SeaAI_GetRelation(chrIdx,nMainCharacterIndex) )
			{
			case RELATION_FRIEND:	BI_intNRetValue[1] = BI_RELATION_FRIEND; break;
			case RELATION_NEUTRAL:	BI_intNRetValue[1] = BI_RELATION_NEUTRAL; break;
			case RELATION_ENEMY:	BI_intNRetValue[1] = BI_RELATION_ENEMY; break;
			}
			BI_intNRetValue[5] = chrIdx;
		}
	}
	else
	{
		if( CheckAttribute(arLoc,"istown") && arLoc.istown=="1" )
		{
			iTmp = FindLocation( arLoc.go );
			if( iTmp>=0 ) {
				iTmp = FindColony( Locations[iTmp].fastreload );
				if( iTmp>=0 ) {
					BI_intNRetValue[0] = 2; // тип город
					switch( GetNationRelation2MainCharacter(sti(Colonies[iTmp].nation)) )
					{
					case RELATION_FRIEND:	BI_intNRetValue[1] = BI_RELATION_FRIEND; break;
					case RELATION_NEUTRAL:	BI_intNRetValue[1] = BI_RELATION_NEUTRAL; break;
					case RELATION_ENEMY:	BI_intNRetValue[1] = BI_RELATION_ENEMY; break;
					}
					BI_intNRetValue[6] = sti(Colonies[iTmp].disease);
				}
			}
		}
		else
		{// не форт, не город - бухта!
			BI_intNRetValue[0] = 3; // тип бухта
		}
	}

	int g_LocLngFileID = LanguageOpenFile("LocLables.txt");
	if( CheckAttribute(arLoc,"label") ) {
		arLoc.labelLoc = LanguageConvertString(g_LocLngFileID,arLoc.label);
		string sColonyName = PChar.ColonyBuilding.ColonyName;

		if(arLoc.label == "Caiman Port")
		{
			arLoc.labelLoc = "порт " + sColonyName;
		}
		if( arLoc.labelLoc == "" ) {
			Trace("Warning! Language: string <"+arLoc.label+"> hav`t translation into file <LocLables.txt>");
		}
	}
	LanguageCloseFile(g_LocLngFileID);

	if( BI_intNRetValue[2]<0 || BI_intNRetValue[3]<0 )
	{
		BI_intNRetValue[2] = 0;
		switch (BI_intNRetValue[0])
		{
			case 1: // форт
				BI_intNRetValue[3] = 62;
				BI_intNRetValue[4] = 46;
			break;
			case 2: // город
				BI_intNRetValue[3] = 63;
				BI_intNRetValue[4] = 47;
            break;
            case 3: // бухта
				BI_intNRetValue[3] = 31;
				BI_intNRetValue[4] = 15;
            break;
		}
	}

	return &BI_intNRetValue;
}

int GetTargChrIndex(int targNum, string locName)
{
	if(targNum==-1) {
		return Fort_FindCharacter(AISea.Island,"reload",locName);
	}
	else
	{
		return targNum;
	}
}

bool CheckSuccesfullBoard(ref rBoarderChr, ref rSieger)
{
	if (bBettaTestMode) return true;
	if (LAi_IsDead(rSieger)) return false;  // fix
	// skill = 1 -> k = 0.5; skill = 10 -> k = 2.0
	float k = 0.333 + GetSummonSkillFromNameToOld(rBoarderChr, SKILL_SNEAK)*0.167;

	// skill = 1 -> limit = 0.45 -> 0.2^0.5 (20 percents);   skill = 10 -> limit = 0.81 -> 0.9^2 (90 percents)
	float topLimit = 0.41 + GetSummonSkillFromNameToOld(rBoarderChr, SKILL_GRAPPLING)*0.04;

	if( pow(rand(1000)/1000.0, k) < topLimit ) return true;
	return false;
}
// НОВОЕ ГПК патч 1.2.3
// рандомный герб на парус
void SetRandGeraldSail(ref chr, int nation)
{
	string ret = "";
	int    st = GetCharacterShipType(chr);
	ref    shref;

	// 1.2.3 переделка на герб привязан к кораблю, то есть при обмене сохранится
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st);
		switch (nation)
		{
			case ENGLAND:
				ret = "eng_" + (1 + rand(4));
			break;
			case FRANCE:
				ret = "fra_" + (1 + rand(5));
			break;
			case SPAIN:
				ret = "spa_" + (1 + rand(4));
			break;
			case HOLLAND:
				ret = "hol_" + (1 + rand(3));
			break;
			case PIRATE:
				ret = "pir_" + (1 + rand(5));
			break;
		}
		shref.ShipSails.Gerald_Name = ret;
	}
}

void SetSailsColor(ref chr, int col)
{
	int    st = GetCharacterShipType(chr);
	ref    shref;

	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st);

		shref.SailsColorIdx   = col;
		shref.ShipSails.SailsColor = SailsColors[col].color;
	}
}

// Warship 04.06.09 Проверка, можно ли на паруса корабля персонажа поставить герб
bool CanSetSailsGerald(ref _char)
{
	int shipClass = GetCharacterShipClass(_char); // Если корабля нет, вернет 7 (лодка)

	if(shipClass > 4) // Проверка на класс корабля > 4
	{
		return false;
	}

	return true;
}
// LDH 13Feb17 - return moor location name or map region, adjusted for long strings and enlarged fonts
string GetBILocationName()
{
	string Name;
	if(CheckAttribute(pchar,"MoorName"))
	{
		if (pchar.MoorName == " ")
			Name = GetCurLocationName1();
		else
			Name = pchar.MoorName;
	}
	float fHtRatio = stf(Render.screen_y) / screenscaling;

	if (strlen(Name) > 24 && fHtRatio > 1.0)
		Name += strcut("               ", 0, makeint((fHtRatio - 1.0) * 10.0 + 0.5));
	return Name;
}
