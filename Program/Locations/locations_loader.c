//#20170911-01 Ambient light mod
#define amb_cave 9531723; //12098165 //9531723 //7426088 //2957328 //2105376
#define inca_temple 3158061
#define amb_house 3158065
#define amb_tavern 16750121
#define amb_shop 3158064
#define amb_residence 8750465
#define amb_church 6316121
#define amb_jail 6710861 //2105373
#define amb_dungeon 12622173 //5916200
#define amb_other 0 //3158065

#define LOC_JUNGLE 1
#define LOC_DUNGEON 2
#define LOC_JAIL 3
#define LOC_TOWN 4
#define LOC_RESIDENCE 5
#define LOC_SEASHORE 6
#define LOC_MAYAK 7
#define LOC_PORT 8

#include "Locations\particles.c"

#define EVENT_LOCATION_LOAD		"EventLoadLocation"
#define EVENT_LOCATION_UNLOAD	"EventUnloadLocation"

#define MAX_SHIPS_IN_LOCATION	32

ref loadedLocation;
object locWeather;
object locSea;
object locCamera;
object locShips[MAX_SHIPS_IN_LOCATION];

int iShips[MAX_SHIPS_IN_LOCATION];
int	locNumShips = 0;

float locTmpTime = 0.0;
bool locDisableUpdateTime = false;

int FindLocation(string id)
{
	return NativeFindLocation(&locations, id);
}

void SetCamShuttle(ref loc) // boal вынес в метод
{
    if(CheckAttribute(loc, "camshuttle"))
	{
		if (CheckAttribute(pchar, "SystemInfo.ScaleSeaHeight"))
		{
			float sp = 0.95 - pow(0.91, stf(pchar.SystemInfo.ScaleSeaHeight));
			Log_TestInfo("Волна = "+pchar.SystemInfo.ScaleSeaHeight + "  качка = " + sp);
			//скорость, время, мин, макс, скорость наклона, макс наклон
			SendMessage(&LocCamera, "lffffff", -1, 0.5, -1.0, 1.0, 1.0, (0.07 * sp), (0.045 + sp/15.0)); // зависимость от волнения 14.09.06
		}
		else
		{
			//скорость, время, мин, макс, скорость наклона, макс наклон
			SendMessage(&LocCamera, "lffffff", -1, 0.5, -1.0, 1.0, 1.0, 0.05, 0.1);
		}
	}
	else
	{
		if (CheckAttribute(pchar, "GenQuest.CamShuttle"))
		{
			float fshut = stf(Pchar.GenQuest.CamShuttle)/10;
			float ftmp = 0.1;
			if (fshut > 0.4) fshut = 0.4;
			if (fshut < 0.2) ftmp = 0.05;
			if(!CheckAttribute(Pchar,"Drunked.Today"))
			{
				//Log_Info("Что-то я перепил...");
			}
			else
			{
				if (Pchar.Drunked.Today != Pchar.dayRandom) Log_Info("Ох, что-то штормит меня сегодня...");
			}
			SendMessage(&LocCamera, "lffffff", -1, 0.5, -1.0, 1.0, 1.0, ftmp, fshut);
			Pchar.Drunked.Today = Pchar.dayRandom;
		}
		else
		{
			//скорость, время, мин, макс, скорость наклона, макс наклон
			SendMessage(&LocCamera, "lffffff", -1, 0.5, 1.0, 1.0, 1.0, 0.00, 0.0);
			//SendMessage(&LocCamera, "lffffff", -1, 0.0, 0, 0.0, 0.0, 0.00, 0.0);
		}

	}
}

bool LoadLocation(ref loc)
{
	NullCharacter.TravelMap.Islands.Caiman.Shore.t0			= "shore16";
	NullCharacter.TravelMap.Islands.Caiman.Shore.t1			= "shore17";
	//trace("LoadLocation(ref loc) " + loc.id);
	if (loc.id == "Bridgetown_Plantation") DeleteAttribute(loc,"fastreload");
	if (loc.id == "Marigo_ExitTown") {loc.townsack = "Marigo"; loc.fastreload = "Marigo";}
	if (loc.id == "Temple_h" && !CheckAttribute(pchar,"Janitor"))
	{
		pchar.quest.CleanUpGrandma.win_condition.l1 = "Location";
		pchar.quest.CleanUpGrandma.win_condition.l1.location = "Temple_h";
		pchar.quest.CleanUpGrandma.win_condition = "CleanUpGrandma";
		pchar.quest.CleanGrandma.win_condition.l1 = "ExitFromLocation";
		pchar.quest.CleanGrandma.win_condition.l1.location = pchar.location;
		pchar.quest.CleanGrandma.win_condition = "CleanGrandma";
		pchar.Janitor = true;
	}
	PostEvent(EVENT_LOCATION_LOAD,0);

	int i;
	bool res;
    int nLocConst = 0;

	// Lugger -->
	GetBoardModeToLocation(loc);
	// Lugger <--

	//Time update==========================================================================
	locTmpTime += 5;
	CalcLocalTime(3);
	//Environment==========================================================================
	chrWaitReloadLocator = ""; // fix перехода в таверну при клики на диалог
	chrWaitReloadIsNoLink = false;
	//Environment==========================================================================

    loadedLocation = loc;
	//Environment
	//#20170911-01 Ambient light mod
    int nAmbient = 0;
	if(CheckAttribute(loc, "type"))
	{
	    res = true;
		switch(loc.type)
		{
        case "jungle":
            nLocConst = LOC_JUNGLE;
            break;
        case "seashore":
            nLocConst = LOC_SEASHORE;
            break;
        case "port":
            nLocConst = LOC_PORT;
            break;
        case "mayak":
            nLocConst = LOC_MAYAK;
            break;
		case "cave":			// пещера
			nAmbient = amb_cave;
			//res = false;
            break;
		case "inca_temple":		// храм инков
			nAmbient = inca_temple;
			//res = false;
			break;
		case "house":			// дом
			nAmbient = amb_house;
			break;
		case "tavern":			// таверна
			nAmbient = amb_tavern;
			/* if (makeint(environment.time) > 22.0 || makeint(environment.time) < 7.0)
			{
				res = false;
			} */
			break;
		case "shop":			// магазин
			nAmbient = amb_shop;
			//res = false;
			break;
		case "residence":		// резиденция
			nAmbient = amb_residence;
			nLocConst = LOC_RESIDENCE;
			//res = false;
			break;
		case "church":			// церковь
			nAmbient = amb_church;
			//res = false;
			break;
		case "fort_attack":			// тюрьма
			nAmbient = amb_jail;
			//res = false;
			break;
		case "dungeon":
			nAmbient = amb_dungeon;
			nLocConst = LOC_DUNGEON;
			//res = false;
			break;
        case "jail":
			nAmbient = amb_jail;
			nLocConst = LOC_JAIL;
			break;
        case "town":
            nLocConst = LOC_TOWN;
            break;
		}
		if(res)
		{
			nAmbient = amb_other;
		}
	}
	if(CheckAttribute(loc, "QuestlockWeather"))
	{
		if (CheckAttribute(loc, "QuestlockWeather.hours") && CheckAttribute(loc, "QuestlockWeather.minutes"))
		{
			SetCurrentTime(sti(loc.QuestlockWeather.hours), sti(loc.QuestlockWeather.minutes));
			DeleteAttribute(loc, "QuestlockWeather.hours");
			DeleteAttribute(loc, "QuestlockWeather.minutes");
		}
		//SetNextWeather(loc.QuestlockWeather);
	}
	bool isNoBoarding = true;
	bool isFort = false;
	//#20190613-01
	bool dropSea = false;
	if(CheckAttribute(loc, "boarding"))
	{
		if(loc.boarding == "true") isNoBoarding = false;
		if(loc.boarding == "fort")
		{
			isNoBoarding = false;
			isFort = true;
		}
	}
	if(isNoBoarding)
	{
		//Sea
		//#20190613-01
		if(loc.environment.sea == "true")
		{
			Ship_Walk_Init();
			LayerFreeze(SEA_EXECUTE,false);
			LayerFreeze(SEA_REALIZE,false);
			CreateSea(EXECUTE, REALIZE);
			if (!CheckAttribute(loc, "notCrateFoam"))
			{
				CreateCoastFoamEnvironment(loc.id, EXECUTE, REALIZE);
			}
		}
		else {
            if(nLocConst != LOC_TOWN) {
                dropSea = true;
                switch(nLocConst) {
                    case LOC_JUNGLE:
                        dropSea = false;
                    break;
                    case LOC_DUNGEON:
                        dropSea = false;
                    break;
                    case LOC_JAIL:
                        dropSea = false;
                    break;
                }
				if (CheckAttribute(loc, "id.label") && loc.id.label == "Alcove") dropSea = false;
                if(dropSea)
                    CreateSea(EXECUTE, REALIZE);
            }
		}
		//Weather
		if(loc.environment.weather == "true") CreateWeather(EXECUTE, REALIZE);//CreateEntity(&locWeather, "weather");
		//Ship env
		CreateShipEnvironment();
	}
	if(isFort)
	{
		//Sea
		if(loc.environment.sea == "true") CreateSea(EXECUTE, REALIZE);//CreateEntity(&locSea, "sea");
		//Weather
		if(loc.environment.weather == "true") CreateWeather(EXECUTE, REALIZE);//CreateEntity(&locWeather, "weather");
	}
	ReloadProgressUpdate();
	//SendMessage(Sound,"lf",MSG_SOUND_SET_MASTER_VOLUME,0.0);

	//Create location
	if(CreateEntity(&loc, "location") == 0) return 0;
	//Set models path
	if(CheckAttribute(loc, "filespath.models"))
	{
		SendMessage(loc, "ls", MSG_LOCATION_MODELSPATH, loc.filespath.models);
	}
	//Set textures path
	if(CheckAttribute(loc, "filespath.textures"))
	{
		SendMessage(loc, "ls", MSG_LOCATION_TEXTURESPATH, loc.filespath.textures);
	}
	//Set lighting path
	string lightingPath = GetLightingPath();

	if (isDynamicLightsEnabled(loc.filespath.models)) {
		lightingPath = "";
	}

	SendMessage(loc, "ls", MSG_LOCATION_LIGHTPATH, lightingPath);
	SendMessage(loc, "ls", MSG_LOCATION_SHADOWPATH, GetLmLightingPath());
	//#20170911-01 Ambient light mod
	//if(nAmbient != 0) {
    //    SendMessage(loc, "ll", MSG_LOCATION_SET_AMBIENT_LIGHT, nAmbient);
        //#20190515-02
    //    loc.ambientLight = nAmbient;
	//}
    //#20180920-01
    ReloadProgressUpdate();
    //Loading day/night models
	//--> проверяем наличие контры для установки нужного патча
	string smg = "";
	if (loc.type == "seashore" || loc.type == "mayak")
	{
		makearef(st, loc.models.always);
		num = GetAttributesNum(st);
		for(i = 0; i < num; i++)
		{
			at = GetAttributeN(st, i);
			sat = GetAttributeName(at);
			if(st.(sat) == "smg")
			{
				smg = "smg";
				//#20180920-01
				break;
			}
		}
	}
	//<-- проверяем наличие контры для установки нужного патча
	if(Whr_IsDay() != 0)
	{
		//Day
		makearef(st, loc.models.day);
		num = GetAttributesNum(st);
		for(i = 0; i < num; i++)
		{
			at = GetAttributeN(st, i);
			sat = GetAttributeName(at);
			if((sat != "charactersPatch") && (sat != "jumpPatch") && (sat != "lights"))
			{
				sat = "models.day." + sat;
				res = LocLoadModel(loc, sat, "");
				if(res == 0)
				{
                    Trace("LocationLoader: not loaded model location." + sat + ", id = " + loc.id);
					Trace("Unload location.");
					UnloadLocation(loc);
					return 0;
				}
			}
			ReloadProgressUpdate();
		}
		//Loading patches
		if(CheckAttribute(loc, "models.day.charactersPatch") != 0)
		{
			res = SendMessage(loc, "ls", MSG_LOCATION_SET_CHRS_PATCH, loc.models.day.charactersPatch + smg);
			if(res == 0)
			{
				Trace("");
				Trace("\");
				Trace("Character patch not loaded!");
				Trace("/");
				Trace("");
				UnloadLocation(loc);
				return 0;
			}
		}else{
			Trace("");
			Trace("\");
			Trace("Character patch not setting for location.models.day.charactersPatch!");
			Trace("/");
			Trace("");
			UnloadLocation(loc);
			return 0;
		}
		if(CheckAttribute(loc, "models.day.jumpPatch") != 0)
		{
			SendMessage(loc, "ls", MSG_LOCATION_SET_JMP_PATCH, loc.models.day.jumpPatch);
		}
	}else{
		//Night
		makearef(st, loc.models.night);
		num = GetAttributesNum(st);
		for(i = 0; i < num; i++)
		{
			at = GetAttributeN(st, i);
			sat = GetAttributeName(at);
			if((sat != "charactersPatch") && (sat != "jumpPatch") && (sat != "lights"))
			{
				sat = "models.night." + sat;
				res = LocLoadModel(loc, sat, "");
				if(res == 0)
				{
                    Trace("LocationLoader: not loaded model location." + sat + ", id = " + loc.id);
					Trace("Unload location.");
					UnloadLocation(loc);
					return 0;
				}
				ReloadProgressUpdate();
			}
		}
		//Loading patches
		if(CheckAttribute(loc, "models.night.charactersPatch") != 0)
		{
			res = SendMessage(loc, "ls", MSG_LOCATION_SET_CHRS_PATCH, loc.models.night.charactersPatch + smg);
			if(res == 0)
			{
				Trace("");
				Trace("\");
				Trace("Character patch not loaded!");
				Trace("/");
				Trace("");
				UnloadLocation(loc);
				return 0;
			}
		}else{
			Trace("");
			Trace("\");
			Trace("Character patch not setting for location.models.night.charactersPatch!");
			Trace("/");
			Trace("");
			UnloadLocation(loc);
			return 0;
		}
		if(CheckAttribute(loc, "models.night.jumpPatch") != 0)
		{
			SendMessage(loc, "ls", MSG_LOCATION_SET_JMP_PATCH, loc.models.night.jumpPatch);
		}
	}
	//#20180920-01
	bool bUpLoc = true;
	if(amb_tavern == 0 || nAmbient==amb_tavern || nAmbient != amb_house)
        bUpLoc = false;
	if(bUpLoc && CheckFP(loc)) {
        nAmbient = amb_tavern;
    //    SendMessage(loc, "ll", MSG_LOCATION_SET_AMBIENT_LIGHT, nAmbient);
        bUpLoc = false;
    }
	//Loading always models
	aref st, at, lit, lit1;
	string sat;

	makearef(st, loc.models.always);
	int num = GetAttributesNum(st);
	for(i = 0; i < num; i++)
	{
		at = GetAttributeN(st, i);
		sat = GetAttributeName(at);
        if(sat != "grassPatch")
		{
		    //#20180920-01
            if(bUpLoc && CheckFP(loc)) { //locator models typically precede
                nAmbient = amb_tavern;
             //   SendMessage(loc, "ll", MSG_LOCATION_SET_AMBIENT_LIGHT, nAmbient);
                bUpLoc = false;
            }
			sat = "models.always." + sat;
			res = LocLoadModel(loc, sat, "");
			if(res == 0)
			{
				Trace("LocationLoader: not loaded model location." + sat + ", id = " + loc.id);
				Trace("Unload location.");
				UnloadLocation(loc);
				return 0;
			}
		}else{
			LocLoadGrass(loc, "models.always." + sat);
		}
		ReloadProgressUpdate();
	}
	//Loading background model
	if(CheckAttribute(loc, "models.back"))
	{
		if(LocLoadModel(loc, "models.back", Whr_GetInsideBack()) == 0)
		{
			Trace("LocationLoader: not loaded back model location." + sat + ", id = " + loc.id);
		}
	}
	ReloadProgressUpdate();

	//Entry models
	if(LocIsEntryLocation(loc) == true)
	{
		makearef(st, loc.models.entry);
		num = GetAttributesNum(st);
		for(i = 0; i < num; i++)
		{
			at = GetAttributeN(st, i);
			sat = "models.entry." + GetAttributeName(at);
			res = LocLoadModel(loc, sat, "");
			if(res == 0)
			{
                Trace("LocationLoader: not loaded model location." + sat + ", id = " + loc.id);
				Trace("Unload location.");
				UnloadLocation(loc);
				return 0;
			}
			ReloadProgressUpdate();
		}
	}
	//Locators=============================================================================
	//#20190613-01
	if(dropSea) {
        dropSeaHt();
	}
    else {
        Sea.MaxSeaHeight = 0.5;
        if(CheckAttribute(loc, "MaxWaveHeigh"))
        {
            if(stf(loc.MaxWaveHeigh) > 0.0)
            {
                Sea.MaxSeaHeight = stf(loc.MaxWaveHeigh);
            }
        }
    }
	//Locator's radiuses
	int j, k, gnum, lnum;
	aref locator_rad;
	if(CheckAttribute(loc, "locators_radius") != 0)
	{
		makearef(locator_rad, loc.locators_radius);
		gnum = GetAttributesNum(locator_rad);
		for(j = 0; j < gnum; j++)
		{
			//Group radius
			aref rdgrp = GetAttributeN(locator_rad, j);
			string rdgname = GetAttributeName(rdgrp);
			float rad = MakeFloat("" + rdgrp);
			SetLocatorGroupRadius(loc, rdgname, rad);
			//Some locators radius
			lnum = GetAttributesNum(rdgrp);
			for(k = 0; k < lnum; k++)
			{
				aref rdloc = GetAttributeN(rdgrp, k);
				string rdlname = GetAttributeName(rdloc);
				rad = MakeFloat("" + rdloc);
				SetLocatorRadius(loc, rdgname, rdlname, rad);
			}
		}
	}
	//Updatelocators=======================================================================
	SendMessage(loc, "l", MSG_LOCATION_UPDATELOCATORS);
	loadedLocation = loc;

	ReloadProgressUpdate();

	//Lights===============================================================================
	LocationSetLights(loc);
	//Particles============================================================================
	CreateParticles(loc);
	//Ships================================================================================
	if (isNoBoarding && loc.environment.sea == "true") LocLoadShips(loc); // boal fix!!!!!!!!
	//Animals===========================================================================
	CreateAnimals(loc);
	//Characters===========================================================================
	LoginCharactersInLocation(loc);
	//CheckEnemyLocators(loc);
	//Main character options===============================================================
	ref mainCharacter = GetMainCharacter();
	if(IsEntity(mainCharacter) == 0)
	{
		Trace("Main character not loaded!");
		UnloadLocation(loc);
		return 0;
	}
	AddCharacterLocatorGroup(mainCharacter, "reload");
	AddCharacterLocatorGroup(mainCharacter, "camdetector");
	AddCharacterLocatorGroup(mainCharacter, "item");
	AddCharacterLocatorGroup(mainCharacter, "randitem");
	AddCharacterLocatorGroup(mainCharacter, "box");
	AddCharacterLocatorGroup(mainCharacter, "teleport");

	ReloadProgressUpdate();

 	//Camera===============================================================================
	CreateEntity(&locCamera, "locationcamera");
	SendMessage(&locCamera, "li", MSG_CAMERA_SETTARGET, mainCharacter);
	//#20190815-01
	SetPerspective2Settings();
	locCameraFollow();
	pchar.CameraHoldPos = false; //boal
	if(CheckAttribute(loc, "lockCamAngle"))
	{
		float lockCamAngle = stf(loc.lockCamAngle);
		if(lockCamAngle < -1.5) lockCamAngle = -1.5;
		if(lockCamAngle > 1.5) lockCamAngle = 1.5;
		//SendMessage(&locCamera, "lf", MSG_CAMERA_MOVE, lockCamAngle);
		//#20200331-01 only boarding is set to 0.4 and static...make range instead
//		SendMessage(&locCamera, "lf", MSG_CAMERA_LIMITRANGE, 0.25);
	}
    SetCamShuttle(loc);

	SetEventHandler("Control Activation","locCameraSwitch",1);
	/*if(isNoBoarding) мешало релоду на абордаже и каюте*/ SetEventHandler("Control Activation","chrCharacterKeys",1);
    //#20190327-01
	//int nPCharCamEye = sti(pchar.camEye);
	//locSetCameraEyes(nPCharCamEye);

	bool crtAnimals;

	if(CheckAttribute(loc, "type"))
	{
		switch(loc.type)
		{
        case "jungle":
			if(rand(100) < 80)
			{
				crtAnimals = true;
				if(!IsDay()) crtAnimals = false;
				if(Whr_GetWindSpeed() > 10.0) crtAnimals = false;
				if(Whr_IsRain()) crtAnimals = false;
				if(Whr_IsStorm()) crtAnimals = false;
				if(Whr_GetFogDensity() > 0.008) crtAnimals = false;
				if(crtAnimals)
				{
					SendMessage(loc, "ls", MSG_LOCATION_EX_MSG, "AddEagle");
				}
			}
			//Ящерецы
			if(rand(100) < 95)
			{
				crtAnimals = true;
				if(Whr_IsStorm()) crtAnimals = false;
				if(Whr_GetFogDensity() > 0.008) crtAnimals = false;
				if(Whr_GetWindSpeed() > 10.0) crtAnimals = false;
				if(crtAnimals)
				{
					SendMessage(loc, "ls", MSG_LOCATION_EX_MSG, "AddLizards");
				}
			}
			//Крысы
			if(rand(100) < 50)
			{
				if(IsDay())
				{
					if(rand(100) < 50)
					{
						SendMessage(loc, "lsl", MSG_LOCATION_EX_MSG, "AddRats", 1 + rand(2));
					}
				}else{
					SendMessage(loc, "lsl", MSG_LOCATION_EX_MSG, "AddRats", 1 + rand(4));
				}
			}
            break;
		case "Dungeon":
			if(rand(100) < 95)
			{
				SendMessage(loc, "lsl", MSG_LOCATION_EX_MSG, "AddRats", 16 + rand(16));
			}
            break;
		case "jail":
			if(rand(100) < 75)
			{
				SendMessage(loc, "lsl", MSG_LOCATION_EX_MSG, "AddRats", 1 + rand(3));
			}
            break;
		case "town":
			if(rand(100) < 35)
			{
				crtAnimals = true;
				if(Whr_IsStorm()) crtAnimals = false;
				if(Whr_GetFogDensity() > 0.008) crtAnimals = false;
				if(Whr_GetWindSpeed() > 10.0) crtAnimals = false;
				if(crtAnimals)
				{
					if(IsDay())
					{
						SendMessage(loc, "lsl", MSG_LOCATION_EX_MSG, "AddRats", 1 + rand(2));
					}else{
						SendMessage(loc, "lsl", MSG_LOCATION_EX_MSG, "AddRats", 2 + rand(4));
					}
				}
			}
			break;
		}
		// boal -->
        if (loc.id == "My_Deck_Medium" || loc.id == "My_Deck")
        {
            SendMessage(loc, "lsl", MSG_LOCATION_EX_MSG, "AddRats", 2 + rand(3));
        }
        // boal <--
	}
    float resizeRatio = stf(Render.screen_y) / screenscaling;
    SendMessage(loadedLocation, "lsf", MSG_LOCATION_EX_MSG, "resizeRatio", resizeRatio);
    // boal debug info -->
	if (bLocatorShow)
	{
        ShowAllLocators();
    }
    //#20181023-02
	//else if(CheckAttribute(loc, "showLocatorGrp"))
       // VisibleLocatorsGroup(loc.showLocatorGrp, 1.0, 15.0, 255, 0, 255, 0);
    // boal debug info <--

	Item_OnLoadLocation(loc.id);

	ReloadProgressUpdate();

	if (isNoBoarding) { Island_Start(); }

	if(CheckAttribute(&mainCharacter, "lastFightMode") != 0)
	{
		if(sti(mainCharacter.lastFightMode) != 0)
		{
			if(CheckAttribute(loc, "noFight") && loc.noFight != "1") //eddy. для переходов в режиме боя, чтобы не було эррорлога. счас только при читовых телепортах вылазит, сам смотри.
			{
				SendMessage(&mainCharacter, "lsl", MSG_CHARACTER_EX_MSG, "SetFightMode", 1);
			}
		}
	}
	if (loc.type == "residence") //eddy. в резиденции нельзя дебоширить
	{
		if (!IsLocationCaptured(loc.id) && !CheckAttribute(loc, "boarding"))// захват города
		{
			LAi_LockFightMode(Pchar, true);
		}
	}

	// ADDED BY VANO
	// сбрасываем цвет фона на 0
	Render.BackColor = 0;
	// выключаем эффект моря
	Render.SeaEffect = false;
	// включаем плавание в локации
	loc.Swimming = true;
	// 14.07.2007 - отключаем подводную часть
	Sea.UnderWater = false;

	// если мы под водой
	if(CheckAttribute(loc, "underwater") != 0)
	{
		if (sti(loc.underwater))
		{
			aref arWeather = GetCurrentWeather();

			// отключаем плавание - персонаж ходит в воде
			loc.Swimming = false;

			// включаем эффект воды
			Render.SeaEffect = true;
			// я не помню, тут 0.02 или 0.002 должно быть, если сильно колбасит - то надо уменьшить :)
			Render.SeaEffectSize = 0.003;
			Render.SeaEffectSpeed = 3.0;
			// ставим цвет фона равным цвету тумана
			Render.BackColor = arWeather.Fog.Color;

			// 14.07.2007 - включаем подводную часть в море
			Sea.UnderWater = true;

			Loc.Caustic.scale = 0.2;
			Loc.Caustic.fogdensity = 0.00;
			Loc.Caustic.distance = 30.0;
			Loc.Caustic.color = argb(128, 255, 255, 255);
			Loc.Caustic.speed = 10.0;

			SendMessage(loc, "ls", MSG_LOCATION_EX_MSG, "LoadCaustic");
			SendMessage(loc, "lsl", MSG_LOCATION_EX_MSG, "EnableCaustic", 1);
		}
	}
	// ADDED BY VANO
	if (CheckAttribute(pchar,"chr_ai.HeavyTrauma")) SetNoRun(pchar);
	return 1;
}

void dropSeaHt()
{
    Sea.MaxSeaHeight = -25.0;
    Sea.Sea2.LodScale = 2.0;
    Sea.Sea2.GridStep = 0.25;
    Sea.Sea2.BumpScale = 0.0;
    Sea.Sea2.PosShift = 0.0;
    Sea.Sea2.Amp1 = 0.0;
    Sea.Sea2.Scale1 = 0.0;
    Sea.Sea2.Amp2 = 0.0;
    Sea.Sea2.Scale2 = 0.0;
    Sea.Sea2.AnimSpeed1 = 0.0;
    Sea.Sea2.MoveSpeed1 = "0.0, 0.0, 0.0";
    Sea.Sea2.AnimSpeed2 = 0.0;
    Sea.Sea2.MoveSpeed2 = "0.0, 0.0, 0.0";
    Sea.isDone = "";
}

void LocationSetLights(ref loc)
{
	SendMessage(loc, "ls", MSG_LOCATION_EX_MSG, "DelAllLights");

	string lightPath,lightName,lightGroupName;
	string sat;
	aref st,at,lit,lit1;
	int i,num, lnum,j;

	if(Whr_IsLight() == 0)
	{
		lightPath = "models.day.lights";
	}else{
		lightPath = "models.night.lights";
	}

	if(CheckAttribute(loc, lightPath) != 0)
	{
		makearef(st, loc.(lightPath));
		num = GetAttributesNum(st);
		//Trace("numLights = " + num);
		for(i = 0; i < num; i++)
		{
			at = GetAttributeN(st, i);
			lightGroupName = GetAttributeName(at);
			sat = lightPath + "." + lightGroupName;
			lightName = loc.(sat);
			sat = "locators." + lightGroupName;
			if(CheckAttribute(loc, sat) != 0)
			{
				makearef(lit, loc.(sat));
				lnum = GetAttributesNum(lit);
				for(j = 0; j < lnum; j++)
				{
					lit1 = GetAttributeN(lit, j);
					float litX = stf(lit1.x);
					float litY = stf(lit1.y);
					float litZ = stf(lit1.z);
					//Trace("     AddLight: " + lightName + " (" + litX + ", " + litY + ", " + litZ);
					SendMessage(loc, "lsfff", MSG_LOCATION_ADD_LIGHT, lightName, litX, litY, litZ);
					if(lightName == "lamp")
					{
						SendMessage(loc, "lsfff", MSG_LOCATION_EX_MSG, "AddFlys", litX, litY, litZ);
					}
				}
			}
		}
	}
}

bool UnloadLocation(aref loc)
{
	// ADDED BY VANO
	// сбрасываем цвет фона на 0
	Render.BackColor = 0;
	// выключаем эффект моря
	Render.SeaEffect = false;
	// ADDED BY VANO
	// 14.07.2007 - отключаем подводную часть
	Sea.UnderWater = false;
	//#20190327-01
    //pchar.camEye = locGetCameraEyes();

	//trace("UnloadLocation(aref loc) " + loc.id);
	DialogExit();

	ref mainCharacter = GetMainCharacter();
	if(SendMessage(&mainCharacter, "ls", MSG_CHARACTER_EX_MSG, "IsFightMode") != 0)
	{
		mainCharacter.lastFightMode = "1";
	}else{
		mainCharacter.lastFightMode = "0";
	}

	Event(EVENT_LOCATION_UNLOAD,"");

	int n;

	DeleteCoastFoamEnvironment();

	bool isNoBoarding = true;
	bool isFort = false;
	if(CheckAttribute(loc, "boarding"))
	{
		if(loc.boarding == "true") isNoBoarding = false;
		if(loc.boarding == "fort")
		{
			isNoBoarding = false;
			isFort = true;
		}
	}
	if(isNoBoarding)
	{
		DeleteParticles();
		//DeleteClass(&Island);
		DeleteAnimals();
		DeleteSea();
		DeleteWeather();
		DeleteShipEnvironment();
		Ship_Walk_Delete();
		for(n = 0; n < locNumShips; n++) {DeleteClass(locShips[n]);}
		locNumShips = 0;
	}
	else
	{
        //DeleteParticles();  // фикс костров
		SendMessage(&Particles,"l", PS_CLEAR_CAPTURED);
	}
	if(isFort)
	{
		DeleteSea();
		DeleteWeather();
	}

	DelEventHandler("Control Activation","locCameraSwitch");
	/*if(isNoBoarding) fix 31.03.05 */ DelEventHandler("Control Activation","chrCharacterKeys");
	Item_OnUnLoadLocation();
	LocAi_Release();
	DeleteClass(&loc);
	DeleteClass(&locCamera);
	return true;
}

bool LocLoadModel(aref loc, string sat, string addition)
{
	//Trace("Load model: " + loc.(sat) + " from:" + sat);

	//Пропустим пустое имя
	if(loc.(sat) == "") return true;
	//Считываем параметры модельки
	string attr, attr1;
	bool res;
	string tech = "";
	int level = 10;
	attr = sat + ".tech";
	if(CheckAttribute(loc, attr)) tech = loc.(attr);
    attr = sat + ".level";
    //#20180615-01
    if(CheckAttribute(loc, attr)) {
        level = MakeInt(loc.(attr));
        if(!bSeaActive) level += 10;
    }
    attr = sat + ".lights";

	int dynamicLightsOn = 0;

	if (isDynamicLightsEnabled(loc.filespath.models)) {
		dynamicLightsOn = 1
	}

    if(CheckAttribute(loc, attr)) dynamicLightsOn = MakeInt(loc.(attr));
    //Грузим модельку
    res = SendMessage(loc, "lssll", MSG_LOCATION_ADD_MODEL, loc.(sat) + addition, tech, level, dynamicLightsOn);
	if(res == 0) return 0;
	//Устанавливаем флаги
	object mdl;
	if(SendMessage(loc, "le", MSG_LOCATION_GET_MODEL, &mdl) != 0)
	{
		string sAreal = GiveArealByLocation(loc);
		if (sAreal != "none")
		{
			string sCity = GetCityNameByIsland(sAreal);
			if (sCity != "none")
			{
				SendMessage(&Flag, "lil", MSG_FLAG_INIT, &mdl, GetCityNation(sCity));
			}
		}
	}
	// Проверяем на пену
	attr = sat + ".foam";
	if(CheckAttribute(loc, attr) != 0)
	{
		if (loc.(attr) == "1")
		{

		}
	}
	//Ставим модификаторы
	//locator
	attr = sat + ".locator.group";
	//Trace("> " + attr);
	if(CheckAttribute(loc, attr) != 0)
	{
		res = 0;
		attr1 = sat + ".locator.name";
		//Trace("> " + attr1);
		if(CheckAttribute(loc, attr1) != 0)
		{
			res = SendMessage(loc, "lss", MSG_LOCATION_MODEL_SET_POS, loc.(attr), loc.(attr1));
		}
		if(res == 0)
		{
			Trace("Can't set locator modifier to model: " + loc.(sat));
		}
	}
	//rotate
	attr = sat + ".rotate";
	if(CheckAttribute(loc, attr) != 0)
	{
		float x, y, z;
		attr1 = attr + ".x";
		if(CheckAttribute(loc, attr1) != 0) x = MakeFloat(loc.(attr1));
		attr1 = attr + ".y";
		if(CheckAttribute(loc, attr1) != 0) y = MakeFloat(loc.(attr1));
		attr1 = attr + ".z";
		if(CheckAttribute(loc, attr1) != 0) z = MakeFloat(loc.(attr1));
		res = SendMessage(loc, "lfff", MSG_LOCATION_MODEL_SET_ROT, x, y, z);
		if(res == 0) Trace("Can't set rotate modifier to model: " + loc.(sat));
	}
	//uvslide
	attr = sat + ".uvslide";
	if(CheckAttribute(loc, attr) != 0)
	{
		float u0, v0, u1, v1;
		u0 = 0; v0 = 0; u1 = 0; v1 = 0;
		attr1 = attr + ".u0";
		if(CheckAttribute(loc, attr1) != 0) u0 = MakeFloat(loc.(attr1));
		attr1 = attr + ".v0";
		if(CheckAttribute(loc, attr1) != 0) v0 = MakeFloat(loc.(attr1));
		attr1 = attr + ".u1";
		if(CheckAttribute(loc, attr1) != 0) u1 = MakeFloat(loc.(attr1));
		attr1 = attr + ".v1";
		if(CheckAttribute(loc, attr1) != 0) v1 = MakeFloat(loc.(attr1));
		res = SendMessage(loc, "lffff", MSG_LOCATION_MODEL_SET_UVS, u0, v0, u1, v1);
		if(res == 0) Trace("Can't set uvslide modifier to model: " + loc.(sat));
	}
	//rotate
	attr = sat + ".lamps";
	if(CheckAttribute(loc, attr) != 0)
	{
		if(loc.(attr) != "0")
		{
			SendMessage(loc, "l", MSG_LOCATION_MODEL_LAMPS);
		}
	}
	//reflection
	attr = sat + ".reflection";
	if(CheckAttribute(loc, attr) != 0)
	{
		SendMessage(loc, "lf", MSG_LOCATION_MODEL_REFLECTION, stf(loc.(attr)));
	}
	//reflection
	attr = sat + ".sea_reflection";
	if(CheckAttribute(loc, attr) != 0)
	{
		LayerAddObject(SEA_REFLECTION2, &mdl, 4);
	}
	return 1;
}

float GetAngleY(float x, float z)
{
	return atan2(x,z);
}

void LocLoadShips(ref Location)
{
	int		i, j;
	int		iShips[MAX_SHIPS_IN_LOCATION];
	int		iShipsType[MAX_SHIPS_IN_LOCATION];
	int		iShipType, iMainCharacterShipType;
	aref	locator_ships,locator_otherships;
	aref	locator;

	locNumShips = 0;

	bool bMainCharacterHere = LocIsEntryLocation(Location);

	ref rPlayer = GetMainCharacter();

	if (!CheckAttribute(Location, "locators"))
	{
		//Trace("LocLoadShips: Can't find Location.locators in location: " + Location.id);
		return;
	}

	int iMCI = GetMainCharacterIndex();
	int iNumShips = 0;
	int iNumOtherShips = 0;
	if (CheckAttribute(Location, "locators.ships"))
	{
	    makearef(locator_ships, location.locators.ships);
		iNumShips = GetAttributesNum(locator_ships);
	}
	else {
		Trace("LocLoadShips: Can't find Location.locators.ships in location: " + Location.id); //return;
	}
	if (CheckAttribute(Location, "locators.ships_other"))
	{
	    makearef(locator_otherships, location.locators.ships_other);
	    iNumOtherShips = GetAttributesNum(locator_otherships);
	}
	else {
		Trace("LocLoadShips: Can't find Location.locators.ships_other in location: " + Location.id); //return;
	}
	int totLocs = iNumShips + iNumOtherShips;
	if(totLocs == 0) return;

	iMainCharacterShipType = sti(Characters[iMCI].Ship.Type);
	//#20200226-01
    int maxShipsLoc = MAX_SHIPS_IN_LOCATION - 1;
	maxShipsLoc = i_min(maxShipsLoc, totLocs);
	int iCurNumShips = 0;
	int iCurNumOtherShips = 0;
	// create our characters ships
	if (bMainCharacterHere)
	{
		for (i=0;i<COMPANION_MAX;i++)
		{
			if (locNumShips >= iNumShips) break;
			if (locNumShips >= maxShipsLoc) break;
			int iCompanionIndex = GetCompanionIndex(&Characters[iMCI],i);
			if (iCompanionIndex==-1) continue;
			ref rCompanion = GetCharacter(iCompanionIndex);
			SetCharacterShipLocation(&Characters[iCompanionIndex],Location.id);
			iShipType = sti(Characters[iCompanionIndex].Ship.Type);
			if (iShipType == SHIP_NOTUSED) continue;
			iShips[locNumShips] = iCompanionIndex;
			iShipsType[locNumShips] = 0;
			rCompanion.curshipnum = locNumShips;
			locNumShips++;
			iCurNumShips++;
			Characters[iCompanionIndex].Ship.Stopped = true; // fix
		}
	}
	// create other quest characters ships
	for (i=1;i<MAX_CHARACTERS;i++)  // начало не с 0
	{
		if (i == iMCI) continue;
		if (locNumShips >= iNumOtherShips) break;
		if (locNumShips >= maxShipsLoc) break;
		if (!Character_LocIsEntryLocation(&Characters[i],Location)) continue;
		//#20200226-02
		if (CheckAttribute(&Characters[i], "ShipInStockMan")) continue;
		bool bExist = false;
		for (j=0;j<locNumShips;j++)
		{
			if (i == iShips[j])
			{
				bExist = true; break;
			}
		}
		if (bExist) continue;
		iShipType = sti(Characters[i].Ship.Type);
		if (iShipType == SHIP_NOTUSED) continue;
		iShips[locNumShips] = i;
		Characters[i].curshipnum = locNumShips;
		iShipsType[locNumShips] = 1;
        locNumShips++;
        iCurNumOtherShips++;
		Characters[i].Ship.Stopped = true; // boal fix
	}
	//#20200226-02 Ships stored by mainchar
	if(locNumShips < totLocs) {
        for (i=1;i<MAX_CHARACTERS;i++)
        {
            if (i == iMCI) continue;
            if (locNumShips >= maxShipsLoc) break;
            if (!CheckAttribute(&Characters[i], "ShipInStockMan")) continue;
            if (!Character_LocIsEntryLocation(&Characters[i],Location)) continue;
            bExist = false;
            for (j=0;j<locNumShips;j++)
            {
                if (i == iShips[j])
                {
                    bExist = true; break;
                }
            }
            if (bExist) continue;
            iShipType = sti(Characters[i].Ship.Type);
            if (iShipType == SHIP_NOTUSED) continue;
            iShips[locNumShips] = i;
            if(iCurNumShips < iNumShips) {
                iShipsType[locNumShips] = 0;
                iCurNumShips++
            }
            else {
                iShipsType[locNumShips] = 1;
            }
            locNumShips++;
            Characters[i].Ship.Stopped = true; // fix
        }
	}
	iCurNumShips = 0;
	iCurNumOtherShips = 0;
	for(int n = 0; n < locNumShips; n++)
	{
		bool bContinue = false;
		switch(iShipsType[n])
		{
			case 0:
				if (iCurNumShips >= iNumShips)
				{
					Trace("LocLoadShips: need (ships): " + iCurNumShips + ", but max_num_ships: " + iNumShips);
					bContinue = true;
				}
				//Boyer fix #20170331-04
				else {
                    locator = GetAttributeN(locator_ships, iCurNumShips);
				}
				iCurNumShips++;
			break;
			case 1:
				if (iCurNumOtherShips >= iNumOtherShips)
				{
					Trace("LocLoadShips: need (ships_other): " + iCurNumOtherShips + ", but max_num_ships_other: " + iNumOtherShips);
					bContinue = true;
				}
				//Boyer fix #20170331-04
				else {
                    locator = GetAttributeN(locator_otherships, iCurNumOtherShips);
				}
				iCurNumOtherShips++;
			break;
		}
		if (bContinue) continue;
		if (CreateEntity(&locShips[n], "ship") == 0) break;
		//if (iShips[n] == 0) Log_info("Bad index");
		ref rCharacter = GetCharacter(iShips[n]);
		ref rShip = GetRealShip(sti(rCharacter.Ship.Type));
		//SetTextureForShip(rShip, rCharacter);
		Ship_SetLightsAndFlares(rCharacter);
		//rCharacter.Ship.TexturePath = "";
		rCharacter.Ship.Pos.x = stf(locator.x);
		rCharacter.Ship.Pos.z = stf(locator.z);
		rCharacter.Ship.Ang.y = GetAngleY(stf(locator.vZ.x),stf(locator.vZ.z));
		rCharacter.Ship.stopped = true;
		rCharacter.Ship.Speed.z = 0.0;
		Ship_PrepareShipForLocation(rCharacter);
		rPlayer.numcoastalindocks = locNumShips;
		SendMessage(&locShips[n],"laa",MSG_SHIP_CREATE,&rCharacter,&rShip);
	}

	aref ShipLoc;
	string sLocShip;

	if(Location.id == "Marigo_town")
	{
    	sLocShip = "1";

		makearef(ShipLoc, Location.locators.ports.(sLocShip));

    	CreateEntity(&locShips[locNumShips], "ship");

    	rCharacter = GetCharacter(NPC_GenerateCharacter("Marigo_Lugger_char", "pirate_"+(rand(9)+1), "man", "man", 25, GetCityNation("Marigo"), 0, true));
		rCharacter.ship.type = GenerateShip(4+rand(10), false);
		rShip = GetRealShip(sti(rCharacter.Ship.Type));
		Ship_SetLightsAndFlares(rCharacter);
		Ship_PrepareShipForLocation(rCharacter);
		Ship_SetFantomData( rCharacter );
		Ship_ClearImpulseStrength( rCharacter );
		rCharacter.TmpPerks.StormProfessional = 0;
		rCharacter.Ship.Pos.x = stf(ShipLoc.x);
		rCharacter.Ship.Pos.z = stf(ShipLoc.z);
		rCharacter.Ship.Ang.y = GetAngleY(stf(ShipLoc.vZ.x),stf(ShipLoc.vZ.z));
		rCharacter.Ship.stopped = true;
		rCharacter.Ship.Speed.z = 0.0;
		rShip.ship.upgrades.hull = 1;
		rShip.ship.upgrades.sails = (rand(2)+1);
		SendMessage(&locShips[locNumShips],"laa",MSG_SHIP_CREATE,&rCharacter,&rShip);
		locNumShips++;

    	for (i = 1; i<=2; i++)
		{
    		CreateEntity(&locShips[locNumShips], "ship");

        	rCharacter = GetCharacter(NPC_GenerateCharacter("Marigo_tartane_char_"+i, "pirate_"+(rand(9)+1), "man", "man", 25, GetCityNation("Marigo"), 0, true));
			if(i == 1) {sLocShip = "2"; rCharacter.ship.type = GenerateShip(rand(2), false);}
			else {sLocShip = "3"; rCharacter.ship.type = GenerateShip(4+drand(10), false);}
			rShip = GetRealShip(sti(rCharacter.Ship.Type));
			Ship_SetLightsAndFlares(rCharacter);
			Ship_PrepareShipForLocation(rCharacter);
			Ship_SetFantomData( rCharacter );
			Ship_ClearImpulseStrength( rCharacter );
			rCharacter.TmpPerks.StormProfessional = 0;

			makearef(ShipLoc, Location.locators.ports.(sLocShip));

			rCharacter.Ship.Pos.x = stf(ShipLoc.x);
			rCharacter.Ship.Pos.z = stf(ShipLoc.z);
			rCharacter.Ship.Ang.y = GetAngleY(stf(ShipLoc.vZ.x),stf(ShipLoc.vZ.z));
			rCharacter.Ship.stopped = true;
			rCharacter.Ship.Speed.z = 0.0;
			rShip.ship.upgrades.hull = i;
			rShip.ship.upgrades.sails = i;
			SendMessage(&locShips[locNumShips],"laa",MSG_SHIP_CREATE,&rCharacter,&rShip);
			locNumShips++;
		}

		for (i = 1; i<=2; i++)
		{
    		CreateEntity(&locShips[locNumShips], "ship");

        	rCharacter = GetCharacter(NPC_GenerateCharacter("Marigo_sixfifth_char_"+i, "pirate_"+(rand(9)+1), "man", "man", 25, GetCityNation("Marigo"), 0, true));
			if(i == 1) {sLocShip = "4"; rCharacter.ship.type = GenerateShip(3+drand1(24), false);}
			else {sLocShip = "5"; rCharacter.ship.type = GenerateShip(3+drand2(24), false);}
			SetBaseShipData( rCharacter );
			rShip = GetRealShip(sti(rCharacter.Ship.Type));
			Ship_SetLightsAndFlares(rCharacter);
			Ship_PrepareShipForLocation(rCharacter);
			Ship_SetFantomData( rCharacter );
			Ship_ClearImpulseStrength( rCharacter );

			makearef(ShipLoc, Location.locators.ports.(sLocShip));

			rCharacter.Ship.Pos.x = stf(ShipLoc.x);
			rCharacter.Ship.Pos.z = stf(ShipLoc.z);
			rCharacter.Ship.Ang.y = GetAngleY(stf(ShipLoc.vZ.x),stf(ShipLoc.vZ.z));
			rCharacter.TmpPerks.StormProfessional = 0;
			if(i == 1)
			{
				rCharacter.Ship.stopped = true;
				rCharacter.Ship.Speed.z = 0.0;
			}
			else
			{
				rCharacter.Ship.LastBallCharacter = -1;
				rCharacter.Ship.WindDotShip = 1.0;
				rShip.SpeedRate = 2.0; // чтоб не летал
				rCharacter.Ship.Speed.z = 1.0;
				rCharacter.Ship.Pos.Mode = SHIP_SAIL;
			}
			rShip.ship.upgrades.hull = i;
			rShip.ship.upgrades.sails = i;
			SendMessage(&locShips[locNumShips],"laa",MSG_SHIP_CREATE,&rCharacter,&rShip);
			locNumShips++;
		}

		for (i = 1; i<=2; i++)
		{
    		CreateEntity(&locShips[locNumShips], "ship");

        	rCharacter = GetCharacter(NPC_GenerateCharacter("Marigo_any_char_"+i, "pirate_"+(rand(9)+1), "man", "man", 25, GetCityNation("Marigo"), 0, true));
			if(i == 1) {sLocShip = "6"; rCharacter.ship.type = GenerateShip(3+drand1(52), false);}
			else {sLocShip = "7"; rCharacter.ship.type = GenerateShip(3+drand2(52), false);}
			SetBaseShipData( rCharacter );
			rShip = GetRealShip(sti(rCharacter.Ship.Type));
			Ship_SetLightsAndFlares(rCharacter);
			Ship_PrepareShipForLocation(rCharacter);
			Ship_SetFantomData( rCharacter );
			Ship_ClearImpulseStrength( rCharacter );

			makearef(ShipLoc, Location.locators.ports.(sLocShip));

			rCharacter.Ship.Pos.x = stf(ShipLoc.x);
			rCharacter.Ship.Pos.z = stf(ShipLoc.z);
			rCharacter.Ship.Ang.y = GetAngleY(stf(ShipLoc.vZ.x),stf(ShipLoc.vZ.z));
			rCharacter.TmpPerks.StormProfessional = 0;
			rCharacter.Ship.LastBallCharacter = -1;
			rCharacter.Ship.WindDotShip = 1.0;
			rShip.SpeedRate = 2.0; // чтоб не летал
			rCharacter.Ship.Speed.z = 1.0;
			rCharacter.Ship.Pos.Mode = SHIP_SAIL;
			rShip.ship.upgrades.hull = i;
			rShip.ship.upgrades.sails = i;
			SendMessage(&locShips[locNumShips],"laa",MSG_SHIP_CREATE,&rCharacter,&rShip);
			locNumShips++;
		}
	}
	// load boat 2 location
	if (CheckAttribute(Location, "locators.reload.boat"))
	{
		if (bMainCharacterHere && iMainCharacterShipType != SHIP_NOTUSED)
		{
			if (!CheckAttribute(pchar,"JustGotIntoLSC"))
			{
				if (CreateEntity(&locShips[locNumShips], "ship"))
				{
					makearef(locator,Location.locators.reload.boat);

					rCharacter = GetCharacter(BOAT_CHARACTER); // boal
					//Boyer fix #20170331-05 BOAT_CHARACTER to be same nation as PC so flag is correct, instead of always ENGLAND
					rCharacter.nation = rplayer.nation;
					rShip = GetRealShip(sti(rCharacter.Ship.Type));
					rCharacter.Ship.TexturePath = "";
					rCharacter.Ship.Pos.x = stf(locator.x);
					rCharacter.Ship.Pos.z = stf(locator.z);
					rCharacter.Ship.Ang.y = GetAngleY(stf(locator.vZ.x),stf(locator.vZ.z));
					rCharacter.Ship.stopped = true;
					rCharacter.Ship.Speed.z = 0.0;
					Ship_SetLightsAndFlares(rCharacter);
					Ship_PrepareShipForLocation(rCharacter);
					SendMessage(&locShips[locNumShips],"laa",MSG_SHIP_CREATE,&rCharacter,&rShip);
					locNumShips++;
				}
			}
		}
	}
	else
	{
		if (bMainCharacterHere)
		{
			Trace("LocLoadShips: Can't find boat locator in location: " + Location.id);
		}
	}
}

bool Character_LocIsEntryLocation(ref rCharacter, ref rLocation)
{
	if (CheckAttribute(rCharacter,"location.from_sea") && !LAi_IsDead(rCharacter))  // boal superfix 26/05/06
	{
		if (rCharacter.location.from_sea == rLocation.id) return true;
	}
	return false;
}

bool LocIsEntryLocation(ref Location)
{
	ref rPlayer = GetMainCharacter();
	//Trace("LocIsEntryLocation = " + rPlayer.location.from_sea);
	if(rPlayer.location.from_sea != Location.id) return false;
	return true;
}

bool LocLoadGrass(aref loc, string sat)
{
	string grs = loc.(sat);
	string tex = "";
	sat = sat + ".texture";
	if(CheckAttribute(loc, sat) != 0)
	{
		tex = loc.(sat);
	}
	return SendMessage(loc, "lss", MSG_LOCATION_SET_GRS_PATCH, grs, tex);
}

#event_handler("LocationTimeUpdate", "LocationTimeUpdateFunc");
void LocationTimeUpdateFunc()
{
	float dltTime = GetEventData();
	if(locDisableUpdateTime) return;
	locTmpTime = locTmpTime + dltTime;
	//if(locTmpTime > 100000.0) locTmpTime = 100000.0;
	// boal -->
	if (locTmpTime > 9)//14)
	{
		    CalcLocalTime(3);
		    RefreshLandTime();
	}
	// boal <--
}

void CheckAndDisableLocator(ref loc, string locatorname, string checkdestination, bool bDisable)
{
	string sLocTo = "";
	if( CheckAttribute(loc,locatorname) ) {
		sLocTo = loc.fastreload + checkdestination;
		if( loc.(locatorname).go == sLocTo ) {
			if( CheckAttribute(loc,locatorname+".storyloc_disable") ) {
				loc.(locatorname).disable = loc.(locatorname).storyloc_disable;
			} else {
				loc.(locatorname).disable = bDisable;
			}
		}
	}
}

void StoryLineEnableLocator(string locID, string locname, bool bEnable)
{
	int nLoc = FindLocation(locID);
	if( nLoc >= 0 ) {
		if( CheckAttribute(&Locations[nLoc],"reload."+locname) ) {
			chrEnableReloadLocator(locID,Locations[nLoc].reload.(locname).name,bEnable);
		}
		if( CheckAttribute(&Locations[nLoc],"reload."+locname+".disable") ) {
			Locations[nLoc].reload.(locname).storyloc_disable = Locations[nLoc].reload.(locname).disable;
		} else {
			DeleteAttribute(&Locations[nLoc],"reload."+locname+".storyloc_disable");
		}
	}
}

void ShowAllLocators()
{
    VisibleLocatorsGroup("rld", 1.0, 15.0, 255, 128, 200, 120);
    VisibleLocatorsGroup("reload", 1.0, 15.0, 255, 0, 255, 0);
    VisibleLocatorsGroup("goto", 1.0, 15.0, 255, 255, 0, 0);
    VisibleLocatorsGroup("sit", 1.0, 15.0, 255, 255, 0, 0);
    VisibleLocatorsGroup("item", 1.0, 15.0, 255, 255, 0, 255);
    VisibleLocatorsGroup("randitem", 1.0, 15.0, 255, 255, 0, 255);
    VisibleLocatorsGroup("characters", 1.0, 15.0, 155, 255, 0, 0);
    VisibleLocatorsGroup("Merchant", 1.0, 15.0, 105, 0, 255, 125);
    VisibleLocatorsGroup("box", 1.0, 15.0, 255, 0, 255, 255);
    VisibleLocatorsGroup("encdetector", 1.0, 15.0, 255, 0, 255, 255);
    VisibleLocatorsGroup("outside", 1.0, 15.0, 255, 155, 155, 255);
    VisibleLocatorsGroup("officers", 1.0, 15.0, 255, 255, 0, 0);
    VisibleLocatorsGroup("waitress", 1.0, 15.0, 255, 255, 0, 0);
    VisibleLocatorsGroup("barmen", 1.0, 15.0, 255, 255, 0, 0);
    VisibleLocatorsGroup("teleport", 1.0, 15.0, 255, 255, 0, 0);
    VisibleLocatorsGroup("magsteleport", 1.0, 15.0, 255, 255, 0, 0);
    VisibleLocatorsGroup("greenteleport", 1.0, 15.0, 255, 255, 0, 0);
    VisibleLocatorsGroup("Enc01", 1.0, 15.0, 255, 255, 0, 0);
    VisibleLocatorsGroup("Enc02", 1.0, 15.0, 255, 255, 0, 0);
    VisibleLocatorsGroup("Enc03", 1.0, 15.0, 255, 255, 0, 0);
    VisibleLocatorsGroup("Enc04", 1.0, 15.0, 255, 255, 0, 0);
    VisibleLocatorsGroup("redteleport", 1.0, 15.0, 255, 255, 0, 0);
    VisibleLocatorsGroup("blueteleport", 1.0, 15.0, 255, 255, 0, 0);
    VisibleLocatorsGroup("monsters", 1.0, 15.0, 255, 255, 200, 0);
    VisibleLocatorsGroup("Smugglers", 1.0, 15.0, 255, 255, 0, 0);
    VisibleLocatorsGroup("camera", 1.0, 15.0, 155, 0, 255, 255);
    VisibleLocatorsGroup("soldiers", 1.0, 15.0, 255, 255, 100, 200);
    VisibleLocatorsGroup("quest", 1.0, 15.0, 255, 255, 200, 200);
    VisibleLocatorsGroup("patrol", 1.0, 15.0, 255, 255, 100, 200);
    VisibleLocatorsGroup("tables", 1.0, 15.0, 255, 255, 0, 0);
	// видимость новых (и старых) локаторов
	VisibleLocatorsGroup("ships_other", 1.0, 15.0, 255, 255, 200, 200);
	VisibleLocatorsGroup("ships", 1.0, 15.0, 255, 255, 200, 200);
	VisibleLocatorsGroup("Actor", 1.0, 15.0, 155, 255, 0, 0);
	VisibleLocatorsGroup("Genres", 1.0, 15.0, 255, 0, 255, 0);
	VisibleLocatorsGroup("prison", 1.0, 15.0, 255, 0, 255, 0);
}

void HideAllLocators()
{
    HideLocatorsGroup("rld");
    HideLocatorsGroup("reload");
    HideLocatorsGroup("goto");
    HideLocatorsGroup("sit");
    HideLocatorsGroup("item");
    HideLocatorsGroup("randitem");
    HideLocatorsGroup("characters");
    HideLocatorsGroup("Merchant");
    HideLocatorsGroup("box");
    HideLocatorsGroup("encdetector");
    HideLocatorsGroup("outside");
    HideLocatorsGroup("officers");
    HideLocatorsGroup("waitress");
    HideLocatorsGroup("barmen");
    HideLocatorsGroup("teleport");
    HideLocatorsGroup("magsteleport");
    HideLocatorsGroup("greenteleport");
    HideLocatorsGroup("Enc01");
    HideLocatorsGroup("Enc02");
    HideLocatorsGroup("Enc03");
    HideLocatorsGroup("Enc04");
    HideLocatorsGroup("redteleport");
    HideLocatorsGroup("blueteleport");
    HideLocatorsGroup("monsters");
    HideLocatorsGroup("Smugglers");
    HideLocatorsGroup("camera");
    HideLocatorsGroup("soldiers");
    HideLocatorsGroup("quest");
    HideLocatorsGroup("patrol");
    HideLocatorsGroup("tables");

	// прячем новые (и старые) локаторы
    HideLocatorsGroup("ships_other");
    HideLocatorsGroup("ships");
    HideLocatorsGroup("Actor");
    HideLocatorsGroup("Genres");
	HideLocatorsGroup("prison");
}
//#20180920-01
bool CheckFP(ref loc)
{
    /*for(int i = 1; i < 10; i++) {
        string sAtt = "fireplace0" + i;
        bool bCheck = SendMessage(loc, "ls", MSG_LOCATION_LOC_EXISTS, sAtt);
        //trace("check? " + sAtt + " = " + bCheck);
        if(bCheck)
            return true;
    }
    return false;*/
}

bool isDynamicLightsEnabled(string modelPath)
{
	// Костылики из-за того, что движок не воспринимает иначе
	bool isDisabled = HasSubstr(modelPath, "decks") ||
		HasSubstr(modelPath, "EstateRooms") ||
		HasSubstr(modelPath, "Fort_Inside") ||
		HasSubstr(modelPath, "Incas Temple") ||
		HasSubstr(modelPath, "Inside") ||
		HasSubstr(modelPath, "LostShipsCityInsides") ||
		HasSubstr(modelPath, "TenochtitlanInside") ||
		HasSubstr(modelPath, "UnderWater");
	return !isDisabled;
}
