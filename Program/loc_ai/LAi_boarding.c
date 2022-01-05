//  логика абордажа, переработка boal 28.04.06
#define BRDLT_SHIP	0
#define BRDLT_FORT	1

#define BRDLT_MAXCREW 44

#define LOCINITBRD_DEFAULTLOCATION "BOARDING_U_H_CS_T12"
#define LOCINITBRD_DEFAULTLOCATION_FORT "Any_fort_1"

#define MAX_GROUP_SIZE   13

bool   IsFort = false;
int    boarding_location = -1;
int    boarding_location_type = -1;
object boarding_fader;


int   boarding_player_crew = 0;
int   boarding_officers    = 0;
float boarding_player_base_crew    = 0.0; //boal
float boarding_player_crew_per_chr = 1.0;
int   boarding_player_crew_start   = 0; //sd

int   boarding_enemy_crew = 0;
float boarding_enemy_base_crew    = 0.0;
float boarding_enemy_crew_per_chr = 1.0;
int   boarding_enemy_crew_start   = 0; //sd

ref    boarding_enemy;
object boarding_adr[4];
float  boarding_exp = 0;
float  boarding_player_hp = 40;
float  boarding_enemy_hp = 40;
int    boarding_echr_index = -1;
int    boarding_erank = 10;
bool   LAi_boarding_process = false;
bool   Surrendered = false; // сдача в плен

int inside_ecrew_1, inside_ecrew_2;
//Процес абордажа
bool LAi_IsBoardingProcess()
{
	return LAi_boarding_process;
}

//Получить картинку для перехода в абордаж
string LAi_GetBoardingImage(ref echr, bool isMCAttack)
{
	ref mchr = GetMainCharacter();
	string deckID = "";
	isMCAttack   = true;// boal 110804 fix всегда герой
	if(isMCAttack)
	{
		deckID = GetShipLocationID(echr);
	}else{
		deckID = GetShipLocationID(mchr);
	}
	int locID = -1;
	if(deckID != "")
	{
		locID = FindLocation(deckID);
		if(locID < 0)
		{
			Trace("Boarding: ship location not found <" + deckID + ">, set default");
			deckID = "";
		}
	}
	if(locID >= 0)
	{
		if(CheckAttribute(&Locations[locID], "image"))
		{
			if(Locations[locID].image != "")
			{
				return Locations[locID].image;
			}
		}
	}
	return "loading\battle_" + rand(24) + ".tga";
}

//Начать абордаж с главным персонажем
void LAi_StartBoarding(int locType, ref echr, bool isMCAttack)
{
    SendMessage(&Particles,"l", PS_CLEAR_CAPTURED); // повторное удаление партиклов, фикс огней в море.
	//ResetSoundScheme();
	ResetSound(); // new
	PauseAllSounds();
	sTemp = RealShips[sti(echr.Ship.Type)].BaseName;
	Pchar.Encyclopedia.(sTemp) = "1";

	bQuestCheckProcessFreeze = true;//fix

	EmptyAbordageCharacters();
	// NK -->
	if(locType == BRDLT_FORT)
    {
        isMCAttack = true;
        IsFort = true;
    }
	else
    {
        IsFort = false;
    }
    // NK <--
	//Установим обработчик на убийство группы
	SetEventHandler("LAi_event_GroupKill", "LAi_BoardingGroupKill", 1);
	//Настроим интерфейс
	DeleteBattleInterface();
	InitBattleLandInterface();
	//StartBattleLandInterface();
	//Сохраним индекс врага
	boarding_echr_index = sti(echr.index);
	//Параметры сражающихся сторон
	ref mchr = GetMainCharacter();
	int mclass = GetCharacterShipClass(mchr);
	int mcrew = GetCrewQuantity(mchr);

	// Saving enemy captain rank for future use in CalculateAppropriateSkills (Gray 12.02.2005)
	mchr.EnemyRank = echr.rank

	DeleteAttribute(pchar, "abordage_active");
	// boal учет оружия 21.01.2004 -->
	Log_TestInfo("Наших до оружия " + mcrew);
	mcrew = GetWeaponCrew(mchr, mcrew);

	// boal 21.01.2004 <--
	int eclass = GetCharacterShipClass(echr);
	int ecrew = GetCrewQuantity(echr);
	int ecrewBak;

    Log_TestInfo("Наших с оружием " + mcrew + " Врагов " + ecrew);

    boarding_location_type = locType;
	// Сдача в плен -->
	bool ok = (TestRansackCaptain) && (boarding_location_type != BRDLT_FORT);
    if (!CheckAttribute(echr, "DontRansackCaptain")) //квестовые не сдаются
    {
    	if (CheckForSurrender(mchr, echr, 1) || ok) // 1 - это учет первый раз, до битвы на палубе
    	{
    		echr.ship.crew.morale = 5;// после захвата у них мораль такая

    		if (mclass < eclass)
			{
				AddCrewMorale(mchr, ( 3 + 2*rand(eclass-mclass)));
			}
			else
			{
				AddCrewMorale(mchr, 3);
			}
			SendMessage(&Particles,"l", PS_CLEAR_CAPTURED); // повторное удаление партиклов, фикс огней в море.
            //Следующей локации нет
			DelEventHandler("LAi_event_GroupKill", "LAi_BoardingGroupKill");
			boarding_location = -1;

			// Saved value is not needed anymore... (Gray 14.02.2005)
			DeleteAttribute(GetMainCharacter(), "EnemyRank");
		    bQuestCheckProcessFreeze = false;//fix

			//Настроим интерфейс
			Log_SetActiveAction("Nothing");
			EndBattleLandInterface();
            //Выгружаемся в интерфейс

			ChangeCrewExp(pchar, "Soldiers", AIShip_isPerksUse(CheckOfficersPerk(pchar, "SeaWolf"),1.0, 2.0));
			LaunchRansackMain(pchar, echr, "crew");
			// на деле параметры LaunchRansackMain не важны совсем - все определеятеся от реалий - жив кэп и сколько у него матросов - их и обрабатываем
			// но они используются в сообщениях  crew - это сдался сразу
    		LAi_boarding_process = false;
			Event(SHIP_CAPTURED, "l", sti(echr.index));
    		return;
    	}
	}
	// Сдача в плен <--

	// MusketsShoot -->
	float tmpDefence;
    if (CheckOfficersPerk(mchr, "MusketsShoot") && IsFort == false)
    {
        tmpDefence   = MakeFloat(GetSummonSkillFromName(echr, SKILL_DEFENCE)) / SKILL_MAX;
		ecrewBak = makeint(mcrew * 0.25 * AIShip_isPerksUse(CheckOfficersPerk(mchr, "EmergentSurgeon"), 1.0, 0.75));//aw013
		ecrewBak = makeint(ecrewBak * (2.1 - tmpDefence) / 2.0);
		if (ecrewBak > ecrew) ecrewBak = ecrew;//aw013
		PlaySound("INTERFACE\_musketshot_" + rand(3) + ".wav");
		if (CheckAttribute(RealShips[sti(echr.Ship.Type)],"Tuning.HighBort")) ecrewBak = makeint(ecrewBak/2);
		ecrew = ecrew - ecrewBak;
		Log_SetStringToLog("Мушкетным залпом убито " + ecrewBak + " человек команды противника.");
	}
	if (CheckOfficersPerk(echr, "MusketsShoot") && IsFort == false)
	{
		tmpDefence  = MakeFloat(GetSummonSkillFromName(mchr, SKILL_DEFENCE)) / SKILL_MAX;
		ecrewBak = makeint(ecrew * 0.25 * AIShip_isPerksUse(CheckOfficersPerk(echr, "EmergentSurgeon"), 1.0, 0.75));//aw013
		ecrewBak = makeint(ecrewBak * (2.1 - tmpDefence) / 2.0);
		if (ecrewBak > mcrew) ecrewBak = mcrew;//aw013
		PlaySound("INTERFACE\_musketshot_" + rand(3) + ".wav");
		if (CheckAttribute(RealShips[sti(mchr.Ship.Type)],"Tuning.HighBort")) ecrewBak = makeint(ecrewBak/2);
		mcrew = mcrew - ecrewBak;
		Log_SetStringToLog("Мушкетным залпом убито " + ecrewBak + " человек нашей команды.");
		Statistic_AddValue(mchr, "DeadCrewBoard", ecrewBak);
    }
    // MusketsShoot <--

	if(ecrew < 0) ecrew = 0;
	if(mcrew < 0) mcrew = 0;
	boarding_erank = sti(echr.rank);

	// база для расчета
	boarding_enemy_base_crew = ecrew;
	boarding_player_base_crew = mcrew;

	//Количество хитпойнтов для бонуса - учет опыта солдат
	GetBoardingHP(mchr, echr, &boarding_player_hp, &boarding_enemy_hp);

	//Определяем цепь локаций для абордажа
	boarding_location = -1;

	string deckID = "";
	isMCAttack   = true;// boal 110804 fix всегда герой
	if(isMCAttack)
	{
		deckID = GetShipLocationID(echr);
	}else{
		deckID = GetShipLocationID(mchr);
	}
	int locID = -1;
	if(deckID != "")
	{
		locID = FindLocation(deckID);
		if(locID < 0)
		{
			Trace("Boarding: ship location not found <" + deckID + ">, set default");
			deckID = "";
		}
	}
	if(deckID == "")
	{
		if(locType == BRDLT_FORT)
		{
			deckID = LOCINITBRD_DEFAULTLOCATION_FORT;
		}else{
			deckID = LOCINITBRD_DEFAULTLOCATION;
		}
		locID = FindLocation(deckID);
	}
	if (locID < 0)
	{   // исключительная ситуация
		Trace("Boarding: ship location not found <" + deckID + ">, no start boarding");
		// Saved value is not needed anymore... (Gray 14.02.2005)
		DeleteAttribute(GetMainCharacter(), "EnemyRank");
	    bQuestCheckProcessFreeze = false;//fix

		if(boarding_location_type == BRDLT_SHIP)
		{
            ChangeCrewExp(pchar, "Soldiers", AIShip_isPerksUse(CheckOfficersPerk(pchar, "SeaWolf"),1.0, 2.0));
            SendMessage(&Particles,"l", PS_CLEAR_CAPTURED); // повторное удаление партиклов, фикс огней в море.
			LaunchRansackMain(GetMainCharacter(), echr, "captain");	  // на деле параметры LaunchRansackMain не важны совсем - все определеятеся от реалий
            LAi_boarding_process = false;
			Event(SHIP_CAPTURED, "l", sti(echr.index)); // to_do can be harmfull
		}
		else
		{
			if (boarding_location_type == BRDLT_FORT)
			{
                ChangeCrewExp(pchar, "Soldiers", AIShip_isPerksUse(CheckOfficersPerk(pchar, "SeaWolf"),1.0, 2.0));
                SendMessage(&Particles,"l", PS_CLEAR_CAPTURED); // повторное удаление партиклов, фикс огней в море.
				Event(FORT_CAPTURED, "l", sti(echr.index));
				echr.Ship.Crew.Quantity = 10 + rand(350); // рабы (остатки выживших)
                LaunchFortCapture(echr);
                LAi_boarding_process = false;
			}else{
				Trace("Boarding: unknow boarding location type");
			}
		}
		return;
	}

	pchar.abordage = 0;
	//Определяем размеры команд
	boarding_enemy = echr;
	//Максимальное количество человек на корабле
	int maxcrew = MAX_GROUP_SIZE;

    if(CheckAttribute(&Locations[locID], "boarding.locatorNum"))
	{
		maxcrew = sti(Locations[locID].boarding.locatorNum);
	}
    //  модифицируем от класса корабля тут
    int iMaxcrew  = func_min(mclass, eclass); // класс 1 - сама круть 7 - хрень
    switch (iMaxcrew)
    {
        case 7:
			iMaxcrew = 4;
		break;
		case 6:
			iMaxcrew = 4;
		break;
		case 5:
			iMaxcrew = 6;
		break;
		case 4:
			iMaxcrew = 8;
		break;
		case 3:
			iMaxcrew = 12;
		break;
		case 2:
			iMaxcrew = 16;
		break;
		case 1:
			iMaxcrew = 20;
		break;
    }
    if (iMaxcrew < maxcrew) maxcrew = iMaxcrew;

	if (boarding_location_type == BRDLT_SHIP && eclass != 7)  // на тартане каюты нет
	{
    	boarding_enemy.ShipCabinLocationId = GetShipCabinID(echr);
	}

	// boal check -->
	if(maxcrew > BRDLT_MAXCREW)
	{
	    maxcrew = BRDLT_MAXCREW;
	}
	// boal check <--

	//Отношение сторон

	// fort -->
	// boal 21.01.2004 -->
	int cn, j, compCrew;
    ref officer;
    if(IsFort)
    {
        mcrew = mcrew + GetTroopersCrewQuantity(GetMainCharacter()); // если нет перка, то нолик
        boarding_player_base_crew = mcrew;// учет всех кораблей
        //Максимальное количество человек
        Log_TestInfo("Итого: До расчета mcrew = "+mcrew+ " ecrew = "+ ecrew + " boarding_enemy_hp = "+ boarding_enemy_hp + " boarding_player_hp = "+boarding_player_hp);
    }
    // boal 21.01.2004 <--
    // fort <--

	float rel;
	if(mcrew > ecrew)
	{
        // нам бонуc boal
        boarding_player_hp = boarding_player_hp + GetBoarding_player_hp_Bonus(mcrew, ecrew);
		if (boarding_player_hp > 1000) boarding_player_hp = 1000;

        if(mcrew > maxcrew)
		{
			rel = makefloat(mcrew) / makefloat(maxcrew);
			mcrew = maxcrew;
			ecrew = MakeInt(ecrew / rel + 0.5);
		}
	}
	else
	{
		// boal 30.01.2004 -->
		boarding_enemy_hp = boarding_enemy_hp + GetBoarding_enemy_hp_Bonus(mcrew, ecrew);
		if (boarding_enemy_hp > 1500) boarding_enemy_hp = 1500;
		// boal 30.01.2004 <--
        if(ecrew > maxcrew)
		{
			rel = makefloat(ecrew) / makefloat(maxcrew);
			ecrew = maxcrew;
			mcrew = MakeInt(mcrew/rel + 0.5);
		}
	}
	if(mcrew < 1) mcrew = 1;
	if(ecrew < 1) ecrew = 1;

    Log_TestInfo("После приведения mcrew = "+mcrew+ " ecrew = "+ ecrew + " boarding_enemy_hp = "+ boarding_enemy_hp + " boarding_player_hp = "+boarding_player_hp);
	//Jason: устанавливаем число тушек по разным палубам
	// верхнюю палубу оставляем без изменений по количеству, но срезаем 15 процентов HP у воинов противника, на нижних палубах будут добавочные враги, но это компенсация за разделенность сил противника относительно сил героя
	inside_ecrew_1 = makeint(ecrew*0.3+0.5); // 30 процентов - инсайд первого прохода
	inside_ecrew_2 = makeint(ecrew*0.2+0.5); // 20 процентов - инсайд второго прохода
	if (inside_ecrew_1 < 1) inside_ecrew_1 = 1;
	if (inside_ecrew_2 < 1) inside_ecrew_2 = 1;
	boarding_enemy_crew        = ecrew;
	boarding_enemy_crew_start  = ecrew;
	boarding_player_crew       = mcrew;
	boarding_player_crew_start = mcrew;
	//Количество офицеров
	boarding_officers = 0;
	int passq;
	for(int i = 1; i <=MAX_NUM_FIGHTERS; i++)
	{
		passq = GetOfficersIndex(pchar, i);
		if (passq >= 0)
		{
            // boal 05.09.03 offecer need to go to abordage -->
		    // to_do if(makeint(Characters[GetOfficersIndex(GetMainCharacter(), i)].AbordageMode) == 0) continue;	// не берем
			// boal 05.09.03 offecer need to go to abordage <--
			boarding_officers = boarding_officers + 1;
			LAi_SetOfficerType(&characters[passq]);
		}
	}

    //boarding_player_crew_per_chr = (curplayercrew + boarding_officers)/(mcrew + boarding_officers);
    boarding_player_crew_per_chr = makefloat(boarding_player_base_crew / makefloat(mcrew)); //приведение типа
	// START MOD Code by Stone-D : 30/07/2003
	boarding_enemy_crew_per_chr = makefloat(boarding_enemy_base_crew / makefloat(ecrew)); // Stone-D : For calculating final crew numbers
	// END MOD Code by Stone-D : 30/07/2003

	//Выставим игроку и офицерам максимальную жизнь и запомним адреса
	LAi_SetCurHPMax(mchr);
	boarding_adr[0].location = mchr.location;
	boarding_adr[0].group    = mchr.location.group;
	boarding_adr[0].locator  = mchr.location.locator;
	for(i = 1; i <= MAX_NUM_FIGHTERS; i++)
	{
		int idx = GetOfficersIndex(GetMainCharacter(), i);
		//Boyer mod
		int k = i % 3;
		if(k==0) k = 3;
		if(idx < 0)
		{
			//Boyer mod
			boarding_adr[k].location = "";
			boarding_adr[k].group	= "";
			boarding_adr[k].locator  = "";
			continue;
		}
		LAi_SetCurHPMax(&Characters[idx]);
		boarding_adr[k].location = Characters[idx].location;
		boarding_adr[k].group	= Characters[idx].location.group;
		boarding_adr[k].locator  = Characters[idx].location.locator;
	}
	//Стартуем
	LAi_boarding_process = true;
	LAi_LoadLocation(deckID, locType);
	CreateEntity(&boarding_fader, "fader");
	SendMessage(&boarding_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
}

//Загрузить локацию абордажа
void LAi_LoadLocation(string locationID, int locType)
{
//	Log_TestInfo("LoadLocation()");
	ReloadProgressStart();
	//Ищем локацию
	int locIndex = FindLocation(locationID);
	Log_SetActiveAction("Nothing");
    Dead_Char_num = 0; // boal dead body
	if(locIndex >= 0)
	{
		//Устанавливаем главного персонажа
		ref mchr = GetMainCharacter();
		mchr.location = locationID;
		mchr.location.group = "rld";
		// boal random place to star battle 28/11/03 -->
		int locNum[20];
		int locI;
		int maxLocators = 2;

		if (CheckAttribute(&Locations[locIndex], "boarding.locatorNum"))
		{
			maxLocators = sti(Locations[locIndex].boarding.locatorNum);
		}
		locI = 0;
		locNum[locI] = rand(maxLocators-1);
		string sLocType = "loc";
		// определение стороны на палубе
		if (CheckAttribute(&Locations[locIndex], "UpDeckType"))
		{
		    sLocType = ChooseShipUpDeck(mchr, boarding_enemy);
		}

		mchr.location.locator = sLocType + locNum[locI];
		// для каюты перекрыть
		if (CheckAttribute(&Locations[locIndex], "CabinType") && CheckAttribute(&Locations[locIndex], "boarding.Loc.Hero"))
		{
		    mchr.location.locator = Locations[locIndex].boarding.Loc.Hero;
		}
		bool   okLoc;
		int iLoc, j;
		// boal random place to star battle 28/11/03 <--
		if (!CheckAttribute(&Locations[locIndex], "CabinType"))
		{ // не грузим офов, если каюту
	        //Устанавливаем офицеров, если такие есть
	        int logined = 0;
			//Boyer mod
			for(int i = 1; i <= MAX_NUM_FIGHTERS ; i++)
			{
				int idx = GetOfficersIndex(mchr, i);
				if(idx < 0) continue;
				//Log_TestInfo("Load Off " + Characters[idx].id);
				if (logined > maxLocators) break;
				if (CheckAttribute(characters[idx],"AboardRestriction")) continue;

	            // boal 05.09.03 offecer need to go to abordage -->
//			    if(makeint(Characters[idx].AbordageMode) == 0) continue;	// не берем
				// boal 05.09.03 offecer need to go to abordage <--
				DeleteAttribute(&Characters[idx], "location");
				//Characters[idx].location = locationID;
				// boal чтоб грузились в фортах -->
				Characters[idx].location.loadcapture = true;
			    // boal чтоб грузились в фортах <--
				//Characters[idx].location.group = "rld";
				// boal random place to star battle 28/11/03 -->
				iLoc = rand(5);//3

				okLoc = false;
				while (!okLoc)
				{
				    for(j = 0; j <=locI; j++)
				    {
				        if (locNum[j] == iLoc)
				        {
				            iLoc = rand(5);//3
				            okLoc = false;
				            break;
				        }
				        okLoc = true;
				    }
				    //Boyer mod to fix stack error
				    okLoc = true;
				}
				locI++;
			    locNum[locI] = iLoc;
				//Characters[idx].location.locator = sLocType + locNum[locI];
				// boal random place to star battle 28/11/03 <--
				ChangeCharacterAddressGroup(&Characters[idx], locationID, "rld", sLocType + locNum[locI]);
				logined = logined + 1;

			}
			boarding_player_crew = boarding_player_crew - logined;
		}
		//Перегружаемся в локацию
		boarding_location = locIndex;
		if(LoadLocation(&Locations[boarding_location]))
		{
			//работа с сундуком в каюте boal -->
			if (CheckAttribute(&Locations[boarding_location], "CabinType"))
			{
				FillAboardCabinBox(&Locations[boarding_location], boarding_enemy);
			}
			//Расставляем персонажей
			LAi_SetBoardingActors(locationID);
			// boal <--
			//Вытащим саблю
			SendMessage(&mchr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightMode", 1);
			//Запретим диалог
			dialogDisable = true;
		}else{
			Trace("Boarding: Boarding location not loaded, current loc <" + locationID + ">");
		}
	}else{
		Trace("Boarding: Boarding location not found, current loc <" + locationID + ">");
	}
	ReloadProgressEnd();
	PostEvent("LoadSceneSound", 500);
	pchar.OfficerAttRange = 100.0;//автоагр абордажников на палубе
}

//Перегрузиться в следующую локации
void LAi_ReloadBoarding()
{
//	Log_TestInfo("ReloadBoarding()");
	//Разрешим диалоги
	dialogDisable = false;
	//Проверим предыдущую локацию
	if(boarding_location < 0)
	{
		Trace("Boarding: No loaded current boarding location");
		LAi_boarding_process = false;
		return;
	}

	csmHideLootCollectorBox(true);

	//Установить хендлеры для обработки
	SetEventHandler("FaderEvent_StartFade", "LAi_ReloadStartFade", 0);
	SetEventHandler("FaderEvent_EndFade", "LAi_ReloadEndFade", 0);
	//Создаём фейдер и запускаем
	CreateEntity(&boarding_fader, "fader");

	string nextDeck = Locations[boarding_location].boarding.nextdeck;
	if (nextDeck != "")
	{
		if(CheckAttribute(&Locations[FindLocation(nextDeck)], "image"))
		{
			SendMessage(&boarding_fader, "ls", FADER_PICTURE0, Locations[FindLocation(nextDeck)].image);
		}
	}
	float fadeOutTime = RELOAD_TIME_FADE_OUT;
	SendMessage(&boarding_fader, "lfl", FADER_OUT, fadeOutTime, false);
	SendMessage(&boarding_fader, "l", FADER_STARTFRAME);
}

void LAi_ReloadStartFade()
{
	//Выгружаем локацию
 //ResetSoundScheme();
	ResetSound(); // new
	PauseAllSounds();
	SendMessage(&Particles,"l", PS_CLEAR_CAPTURED);
	DelEventHandler("FaderEvent_StartFade", "LAi_ReloadStartFade");
	if(boarding_location >= 0) UnloadLocation(&Locations[boarding_location]);
}

void LAi_ReloadEndFade()
{
	bool bCaptanSurrender = false;
	//Загружаем следующую локацию
	DelEventHandler("FaderEvent_EndFade", "LAi_ReloadEndFade");
	SendMessage(&boarding_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
	//Определим возможность продолжения перегрузок
	bool canReload = true;

	// Jason: во всех инсайдах и добавочных локациях форта число расчетных тушек х2, по рез.тестов возможно, будет дифференциация по типам инсайдов.
	if(CheckAttribute(&Locations[boarding_location], "UpDeckType"))
	{
		boarding_enemy_crew = inside_ecrew_1*2; // увеличиваем внутри число тушек вдвое
	}
	else boarding_enemy_crew = inside_ecrew_2*2; // увеличиваем внутри число тушек вдвое

	if(IsFort)
    {
		if(CheckAttribute(&Locations[boarding_location], "insidenext")) boarding_enemy_crew = inside_ecrew_2*2;
		else boarding_enemy_crew = inside_ecrew_1*2;
	}
	//if(boarding_enemy_crew <= 0) canReload = false;
	if(!CheckAttribute(&Locations[boarding_location], "boarding.nextdeck")) canReload = false;
	if(Locations[boarding_location].boarding.nextdeck == "") canReload = false;

 	if(canReload) //Jason Продолжаем абордаж
	{
		Trace("Boarding: go to inside location");
		LAi_LoadLocation(Locations[boarding_location].boarding.nextdeck, -1);
	}
    else
    {
		if (CheckAttribute(boarding_enemy, "ShipCabinLocationId"))
		{
            if (!CheckAttribute(boarding_enemy, "DontRansackCaptain")) //квестовые не сдаются
	        {
	            Surrendered = (Surrendered) || (TestRansackCaptain);
	    		if (Surrendered && (boarding_location_type == BRDLT_SHIP))
	    		{
	    		    bCaptanSurrender = true;    // это уже не первая палуба точно, значит потери были
	   			}
	    	}
    		if (!bCaptanSurrender)
    		{
				boarding_enemy_crew = 1;
				if(CheckAttribute(&Locations[FindLocation(boarding_enemy.ShipCabinLocationId)], "image"))
				{
					SendMessage(&boarding_fader, "ls", FADER_PICTURE0, Locations[FindLocation(boarding_enemy.ShipCabinLocationId)].image);
				}
				LAi_LoadLocation(boarding_enemy.ShipCabinLocationId, -1);
				DeleteAttribute(boarding_enemy, "ShipCabinLocationId"); // чтоб не зациклилось
				return;
			}
	}

  		if (CheckAttribute(pchar, "GenQuest.QuestAboardCaptanSurrender")) // квестовая сдача в плен кэпа
		{
		    DeleteAttribute(pchar, "GenQuest.QuestAboardCaptanSurrender"); // разово
		    bCaptanSurrender = true;
		}
		SendMessage(&Particles,"l", PS_CLEAR_CAPTURED); // повторное удаление партиклов, фикс огней в море.
		//Следующей локации нет
		DelEventHandler("LAi_event_GroupKill", "LAi_BoardingGroupKill");
		boarding_location = -1;
		//Пересчитываем команду игрока

		float crew = boarding_player_crew * boarding_player_crew_per_chr; // ВЫЖИВШИЕ офицеры - это не мартросы не должны влиять
		// boal 22.01.2004 -->
		ref mchar       = GetMainCharacter();
		float fDefenceSkill = 0.9 + MakeFloat(GetSummonSkillFromName(mchar, SKILL_DEFENCE)) / SKILL_MAX;
		int deadCrew    = makeint((boarding_player_base_crew - crew) / fDefenceSkill + 0.3 + AIShip_isPerksUse(CheckOfficersPerk(mchar, "EmergentSurgeon"), 0.0, 0.9)); // бонус выжившим
		int deadCrewWOMedic = makeint(boarding_player_base_crew - crew); // без бонуса
		float leaderSkill = GetSummonSkillFromNameToOld(mchar, SKILL_LEADERSHIP);
		int iTemp;
		if (leaderSkill < 1) leaderSkill = 1; //fix

		// расчет медицины -->
		iTemp = deadCrewWOMedic - deadCrew;
		if(CheckShipSituationDaily_GenQuest(pchar) > 1)
		{
			if(iTemp > 0)
			{
				deadCrew += deadCrewWOMedic; // если эпидемия - матросы не лечатся, лекарство не потребляется
			}
		}
		else
		{
			if (iTemp > 0)
			{
				if (GetCargoGoods(mchar, GOOD_MEDICAMENT) < iTemp)
				{
					deadCrewWOMedic = iTemp - GetCargoGoods(mchar, GOOD_MEDICAMENT); // умерли от ран
					RemoveCharacterGoodsSelf(mchar, GOOD_MEDICAMENT, GetCargoGoods(mchar, GOOD_MEDICAMENT)); // все нулим
					deadCrew += deadCrewWOMedic; // трупов больше
					Log_Info("Из-за нехватки медикаментов от ран умерли " + deadCrewWOMedic + " матросов");
				}
				else
				{
					RemoveCharacterGoodsSelf(mchar, GOOD_MEDICAMENT, iTemp);
					if (GetCargoGoods(mchar, GOOD_MEDICAMENT) < 16)
					{
						Log_Info("На корабле " + mchar.Ship.Name + " осталось мало медикаментов");
					}
				}
			}
			// расчет медицины <--
			// Saved value is not needed anymore... (Gray 14.02.2005)
			DeleteAttribute(mchar, "EnemyRank");
			bQuestCheckProcessFreeze = false;//fix

			RemoveCharacterGoodsSelf(mchar, GOOD_WEAPON, deadCrew);

			crew = boarding_player_base_crew - deadCrew; // выжившие с бонусом
			Statistic_AddValue(mchar, "Sailors_dead", deadCrew);
			Statistic_AddValue(mchar, "DeadCrewBoard", deadCrew);
			AddCharacterExpToSkill(mchar, "Defence", makeint(deadCrew / 3 + 0.5)); //качаем защиту
			AddCharacterExpToSkill(mchar, "Grappling", makeint(deadCrew / 3 + 0.5));

			// после боя падает мораль
			if (deadCrew > makeint(crew+0.3)) // погибло больше, чем выжило
			{
				AddCrewMorale(mchar, sti(-20 / leaderSkill));
			}
			else
			{  //растет, если потерь мало
				AddCrewMorale(mchar, sti(leaderSkill));
			}

			// boal 22.01.2004 <--
			//SetCrewQuantityOverMax(GetMainCharacter(), MakeInt(crew + 0.3)); // десант весь ГГ как перегруз команды
			SetCrewQuantity(GetMainCharacter(), MakeInt(crew + 0.3)); // фикс после переделки оверкоманды БМС
			Log_TestInfo("----- в конце стало " + crew +" матросов ---");
			//Пересчитываем команду соперника
			crew = 0;// какие еще люди? все трупы! boarding_enemy_base_crew*(0.1 + rand(20)*0.01);
			if (boarding_echr_index >= 0)
			{
				SetCrewQuantity(&Characters[boarding_echr_index], MakeInt(crew + 0.3));
				boarding_echr_index = -1;
			}

			//Начислим опыт
			//AddCharacterExp(GetMainCharacter(), MakeInt(boarding_exp));

			//Настроим интерфейс
			Log_SetActiveAction("Nothing");
			EndBattleLandInterface();
			//Востановим адреса
			ref mchr = GetMainCharacter();
			mchr.location         = boarding_adr[0].location;
			mchr.location.group   = boarding_adr[0].group;
			mchr.location.locator = boarding_adr[0].locator;

			for(int i = 1; i <=MAX_NUM_FIGHTERS; i++)
			{
				int idx = GetOfficersIndex(GetMainCharacter(), i);
				//Boyer mod
				int k = i % 3;
				if(k==0) k = 3;
				if(idx < 0) continue;
				Characters[idx].location			= boarding_adr[k].location;
				Characters[idx].location.group	= boarding_adr[k].group;
				Characters[idx].location.locator = boarding_adr[k].locator;
			}
			//Выгружаемся в интерфейс
			LAi_boarding_process = false;
			// START MOD Code by Stone-D : 27/07/2003
			if (bCaptanSurrender)
			{
				ChangeCrewExp(pchar, "Soldiers", AIShip_isPerksUse(CheckOfficersPerk(pchar, "SeaWolf"), 4.0, 8.0));
				LAi_SetCurHPMax(boarding_enemy);  // нужно, чтоб был живой!!!
				SetCrewQuantity(boarding_enemy, MakeInt(boarding_enemy_base_crew*(rand(20)*0.01))); // раз кэп живой, то можно раненых воскресить
				LaunchRansackMain(pchar, boarding_enemy, "captain"); //капитан в плен
				LAi_boarding_process = false;
				Event(SHIP_CAPTURED, "l", sti(boarding_enemy.index));
				return;
			}
			// END MOD Code by Stone-D : 27/07/2003
			if(boarding_location_type == BRDLT_SHIP)
			{
				ChangeCrewExp(pchar, "Soldiers", AIShip_isPerksUse(CheckOfficersPerk(pchar, "SeaWolf"),5.0, 10.0));
				// нельзя это делать до формы, критерий будет "" LAi_SetCurHP(boarding_enemy, 0.0); // умер, чтоб на форме обмена не жил
				LaunchRansackMain(pchar, boarding_enemy, ""); //не сдался
				LAi_boarding_process = false;
				Event(SHIP_CAPTURED, "l", sti(boarding_enemy.index));
				return;
			}
			if(boarding_location_type == BRDLT_FORT)
			{
				ChangeCrewExp(pchar, "Soldiers", AIShip_isPerksUse(CheckOfficersPerk(pchar, "SeaWolf"),7.0, 14.0));
				Event(FORT_CAPTURED, "l", sti(boarding_enemy.index));
				boarding_enemy.Ship.Crew.Quantity = 10 + rand(350); // рабы (остатки выживших)
				LaunchFortCapture(boarding_enemy);
				LAi_boarding_process = false;
				return;
			}
			Trace("Boarding: unknow boarding location type");
			Log_TestInfo("Boarding - unknown boarding location type : " + boarding_location_type);
		}
	}
}

//Разрешить перегрузку на следующую палубу
#event_handler("LAi_event_boarding_EnableReload", "LAi_EnableReload");
void LAi_EnableReload()
{
    //Log_Testinfo("LAi_BoardingGroupKill boardM = " + boardM);
	if (boardM == 1)
	{
	//	Trace("Выключить шума абордажа");
		//ResetSound();
		ResetSoundScheme(); //надо гасить только Scheme, иначе партиклы звука на кострах, факелах, и прочем - не пашут
		//StopSound(abordageSoundID, 0);
		SetSoundScheme("deck"); // обычная схема
		SetMusic("music_bitva");
		boardM = -1;
		//Log_Testinfo("Выключить шума абордажа " + abordageSoundID);
	}
	Surrendered = CheckForSurrender(GetMainCharacter(), boarding_enemy, 2); // проверка сдачи в плен, перед каютой 2 - второй учет метода

	if (csmCA(pchar, "CSM.LootCollector.Enable") && loadedLocation.type != "boarding_cabine")
	{
		pchar.CSM.LootCollector.CanBeRun = true;
		csmLootCollector();
	}
	PostEvent("csmEvent_RefreshReload", 100);
    //#20171218-01 Re-enable fast action for cabin enter during boarding
    BattleInterface.LAi_ActivateReload = true;
	SetEventHandler("Control Activation","LAi_ActivateReload",1);
	Log_SetActiveAction("Reload");
	//Уберём саблю
	ref mchr = GetMainCharacter();
	SendMessage(&mchr, "lsl", MSG_CHARACTER_EX_MSG, "ChangeFightMode", 0);

	// sd -->
	Log_TestInfo("Start boarding_enemy_crew_start: " + boarding_enemy_crew_start + " boarding_enemy_crew: " + boarding_enemy_crew);
	Log_TestInfo("Start boarding_player_crew_start: " + boarding_player_crew_start + " boarding_player_crew: " + boarding_player_crew);
	// sd <--

	//Вернём выживших обратно в кучу
	for(int i = 0; i < LAi_numloginedcharacters; i++)
	{
		int index = LAi_loginedcharacters[i];
		if(index >= 0)
		{
			if(index != GetMainCharacterIndex())
			{
				ref chr = &Characters[index];
				if(!LAi_IsDead(chr) && !CheckAttribute(chr,"AboardFantomMush")) // boal && sd не нужны офицеры для матросов
				{
					if(chr.chr_ai.group == LAI_GROUP_PLAYER)
					{
						boarding_player_crew = boarding_player_crew + 1;
						//LAi_tmpl_stay_InitTemplate(chr);  // 05.02.08 требует локаторов ГОТО, что б не ходили за ГГ матросы толпой - нихрена это не работает, все равно ходят !
						//LAi_SetStayType(chr); // а вот так не ходят !!  <-- ugeen
						if (!IsOfficer(chr)) LAi_SetHuberStayType(chr); //нефиг им стоять, все-равно мешаются ! пущай расходятся по палубе
					}
				}
				/*
				// Fix избытка команды ! - убираем, глючный
				if(chr.model.animation == "mushketer" && !IsOfficer(chr)) //мушкетеров убираем с палубы
				{
                    ChangeCharacterAddress(chr, "none", "");
				}
				*/
			}
		}
	}
	// Jason: перебираем классы кораблей и определяем следующую палубу
	int eclass = sti(GetCharacterShipClass(boarding_enemy)); // класс корабля противника
	if (CheckAttribute(&Locations[boarding_location], "UpDeckType"))
	{
		switch (eclass)
		{
			case 1: Locations[boarding_location].boarding.nextdeck = "Boarding_GunDeck"; break;
			case 2: Locations[boarding_location].boarding.nextdeck = "Boarding_GunDeck"; break;
			case 3: Locations[boarding_location].boarding.nextdeck = "Boarding_Campus"; break;
			case 4: Locations[boarding_location].boarding.nextdeck = "Boarding_Campus"; break;
			case 5: Locations[boarding_location].boarding.nextdeck = "Boarding_Cargohold"; break;
			case 6: Locations[boarding_location].boarding.nextdeck = ""; break;
		}
	}
	if (IsFort && Locations[boarding_location].boarding.nextdeck == "Boarding_bastion")
	{
		Locations[boarding_location].boarding.nextdeck = "Boarding_bastion"+(drand(1)+1);
	}
	// END MOD Code by Stone-D : 01/08/2003 -->
	Log_TestInfo("New boarding_player_crew: " + boarding_player_crew);
	Log_TestInfo("Next Location: " + Locations[boarding_location].boarding.nextdeck);
    Log_TestInfo("Enemy ship class: " + eclass);
	// END MOD Code by Stone-D : 01/08/2003 <--
}

//Активация перегрузки на следующую палубу
void LAi_ActivateReload()
{
	string controlName = GetEventData();
	if(controlName != "ChrAction") return;
	if (CheckAttribute(pchar, "GenQuest.CannotReloadBoarding")) return; // Jason
	DelEventHandler("Control Activation", "LAi_ActivateReload");
	//#20171218-01 Re-enable fast action for cabin enter during boarding
    DeleteAttribute(&BattleInterface, "LAi_ActivateReload");
	Log_SetActiveAction("Nothing");
	LAi_ReloadBoarding();
}

//Расставить персонажей для боя
void LAi_SetBoardingActors(string locID)
{
    int    limit, i, iQty;
	ref    chr;
	string model, ani, sTemp;
	int    xhp;
	int    locIndex = FindLocation(locID);
	int    mclass = GetCharacterShipClass(GetMainCharacter());
	int    eclass = GetCharacterShipClass(boarding_enemy);
	ref    mchr = GetMainCharacter(); // boal star with new loc always
    int    locMChar;

	limit = MAX_GROUP_SIZE;
	// локаторов разное число на моделях :( Переделал все на инфу из кода boal 01.01.05  +1 всегда для ГГ
	chr = &Locations[locIndex];

	if(CheckAttribute(chr, "boarding.locatorNum")) limit = sti(chr.boarding.locatorNum);

	Log_TestInfo("Location: " + locID + " Limit: " + limit);
	Log_TestInfo("Player: " + boarding_player_crew + " х " + boarding_player_crew_per_chr + " Enemy: " + boarding_enemy_crew + " х " + boarding_enemy_crew_per_chr);

	//Установим союзников из команды
	// boal прежде всего ставим офицеров, коротых в фотре почему-то нет -->
	/*if (IsFort) // boal 21.01.05 не прошло и года... починил в другом месте - правильно
	{
        for(i = 1; i < 4; i++)
		{
			int idx = GetOfficersIndex(mchr, i);
			if(idx < 0) continue;
            // boal 05.09.03 offecer need to go to abordage -->
		    if(makeint(Characters[idx].AbordageMode) == 0) continue;	// не берем
		    // грузим сами насильно уже в сущ локацию
		    chr = &Characters[idx];
		    PlaceCharacter(chr, mchr.location.group, mchr.location);
		}
	} */
	// boal прежде всего ставим офицеров, коротых в форте почему-то нет <--
    string sLocType = "loc";
	// определение стороны на палубе
	if (CheckAttribute(&Locations[locIndex], "UpDeckType"))
	{
	    sLocType = ChooseShipUpDeck(mchr, boarding_enemy);
	}
	if (!CheckAttribute(&Locations[locIndex], "CabinType"))
	{ // не грузим матросов в каюту
		for(i = LAi_numloginedcharacters; i < limit; i++)
		{
			if(boarding_player_crew <= 0) break;
			model = LAi_GetBoardingModel(mchr, &ani);
			// boal star with new loc always  -->
			if (mchr.location.locator == (sLocType + i))
			{ // искодим из того, что наша локация всегда < 4 офицеры пусть накладываются а матросик идет к противнику.
	           locMChar = rand(3);
	           while (mchr.location.locator == (sLocType + locMChar))
	           {
	               locMChar = rand(3);
	           }
		       chr = LAi_CreateFantomCharacterEx(model, ani, "rld", sLocType+locMChar);// 0-всегда свободен, если офицеров нет, а i != 0, тк мы точно есть
			}
			else
			{
			   chr = LAi_CreateFantomCharacterEx(model, ani, "rld", sLocType + i);
			}
			// boal star with new loc always  <--

			LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);

			boarding_player_crew = boarding_player_crew - 1;
			// boal расчет как у нормальных фантомов -->
			//LAi_SetAdjustFencingSkill(chr, 3.0, 6.0);
			//LAi_AdjustFencingSkill(chr);

			// boal <--
			if (!IsFort)
			{
	            SetFantomParamAbordOur(chr);
			}
			else
			{
			    SetFantomParamFortOur(chr);
			}
			SetNewModelToChar(chr); //иначе сабли не те, что реально
			chr.AboardFantom = true;
			AddCharHP(chr, boarding_player_hp); // влияение опыта и морали в НР
			/*if (!bNewFantomGenerator)
	        {
				xhp = GetBoarding_player_hp(boarding_player_hp);
				LAi_SetHP(chr, xhp, xhp);
			}*/
			if (IsCharacterPerkOn(chr, "Ciras") && rand(4)==0)
			{
				string cirnum;
				switch (rand(4))
				{
					case 0: cirnum = "cirass1"; break;
					case 1: cirnum = "cirass1"; break;
					case 2: cirnum = "cirass2"; break;
					case 3: cirnum = "cirass3"; break;
					case 4: cirnum = "cirass4"; break;
				}
				if (CheckAttribute(chr, "HeroModel")) // все, у кого есть что одеть
				{
					switch (cirnum)
					{
						case "cirass1": chr.model = GetSubStringByNum(chr.HeroModel, 1); break;
						case "cirass2": chr.model = GetSubStringByNum(chr.HeroModel, 2); break;
						case "cirass3": chr.model = GetSubStringByNum(chr.HeroModel, 3); break;
						case "cirass4": chr.model = GetSubStringByNum(chr.HeroModel, 4); break;
					}
				}
				chr.cirassId = Items_FindItemIdx(cirnum);
				Log_TestInfo("Персонаж "+chr.name+" получил кирасу "+cirnum);
			}
		}
		//ставим своих мушкетеров -->
		if (CheckOfficersPerk(mchr, "MusketsShoot") && !CheckAttribute(boarding_enemy, "GenQuest.CrewSkelMode"))
		{
			if (!IsFort) iQty = 7;
			else iQty = 3;
			for(i=1; i<=iQty; i++)
			{
				if (LAi_CheckLocatorFree("rld", sLocType+"mush"+i))
				{
					model = LAi_GetBoardingMushketerModel(mchr);
					chr = GetCharacter(NPC_GenerateCharacter("GenChar_", model, "man", "mushketer", 5, sti(mchr.nation), 0, false));
					chr.id = "GenChar_" + chr.index;
					chr.AboardFantom = true;
					chr.AboardFantomMush = true;
					if (!IsFort) chr.MusketerDistance = 0;
					LAi_SetWarriorType(chr);
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
					ChangeCharacterAddressGroup(chr, locID, "rld", sLocType+"mush"+i);
				}
			}
			if (!IsFort)
			{
	            SetMushketerParamAbordOur(chr);
			}
			else
			{
			    SetMushketerParamFortOur(chr);
			}
			AddCharHP(chr, boarding_player_hp); // влияение опыта и морали в НР
		}
		//<-- ставим своих мушкетеров
	}
	//Установим врагов
	if (sLocType == "loc")
	{
	    sLocType = "aloc";
	}
	else
	{
	    sLocType = "loc";
	}
	trace("sLocType = " + sLocType);
	if (HasSubStr(boarding_enemy.model,"trader_")) boarding_enemy.Ship.Mode = "Trade";
	for(i = 0; i < limit; i++) // <= тк loc0 .. loc4 = 5
	{
		if(boarding_enemy_crew <= 0) break;
		model = LAi_GetBoardingModel(boarding_enemy, &ani);
		if (i == 0 && CheckAttribute(&Locations[locIndex], "boarding.Loc.Capt")) //локатор каюты
		{
		    chr = LAi_CreateFantomCharacterEx(model, ani, "rld", Locations[locIndex].boarding.Loc.Capt);
		}
		else
		{
			chr = LAi_CreateFantomCharacterEx(model, ani, "rld", sLocType + i);
		}

		LAi_group_MoveCharacter(chr, LAI_GROUP_BRDENEMY);

		boarding_enemy_crew = boarding_enemy_crew - 1;
		// boal расчет как у нормальных фантомов -->
		//LAi_SetAdjustFencingSkill(chr, 2.0, 6.0);
		//LAi_AdjustFencingSkill(chr);

		if (!IsFort)
		{
            SetFantomParamAbordEnemy(chr);
		}
		else
		{
            SetFantomParamFortEnemy(chr);
			//xhp = GetBoarding_enemy_hp(LAi_GetCharacterMaxHP(chr));
		}
		// капитана в рубку!!! boal
		if (i == 0 && CheckAttribute(&Locations[locIndex], "CabinType"))
		{
			ChangeAttributesFromCharacter(chr, boarding_enemy, true);
			chr.CaptanId = boarding_enemy.id; // иначе у фантома свой ИД   // to_do поправить опечатку
			boarding_enemy.CaptanId = boarding_enemy.id;
			chr.SuperShooter = true; // супер стрелок (вероятность пальбы выше, от сложности, если еще и пистоль есть)
			if (boarding_enemy.sex == "man") chr.greeting = "CapSinkShip";
			SetCharacterPerk(chr, "Energaiser"); // скрытый перк дает 1.5 к приросту энергии, дается ГГ и боссам уровней
			if (CheckAttribute(chr,"Situation"))
			{
				if(bSeaCanGenerateShipSituation) SetQuestAboardCabinDialogSituation(chr);
				else DeleteAttribute(chr,"Situation");
			}
			else
			{
				CaptainComission_GenerateSituation(chr);
				SetQuestAboardCabinDialog(chr); /// проверка на минНр
			}
			// если это место отработало, то кэп либо убит, либо по квестам сдается в плен
			// 1.2.3 эффект кирасы
			//if (CheckCharacterPerk(chr, "Ciras"))
			//{
		    xhp = makeint((MOD_SKILL_ENEMY_RATE*2+sti(chr.rank))/10.0);

		    if (xhp > 0)
		    {
		        if (xhp >= 5) xhp = 5;
		        // путаница с 3  и 4 кирасами (меняем)
		        if (xhp == 3)
				{
					xhp = 4;
				}
				else
				{
				    if (xhp == 4) xhp = 3;
				}
				model = "cirass" + xhp;
				chr.cirassId  = Items_FindItemIdx(model);
				Log_TestInfo("На капитане кираса " + model);
		    }
			//}
		}
		SetNewModelToChar(chr); //иначе сабли не те, что реально
		string weaponID = GetCharacterEquipByGroup(chr, BLADE_ITEM_TYPE);
		aref weapon;
		Items_FindItem(weaponID, &weapon);
		chr.chr_ai.fencingtype = weapon.FencingType;
		chr.AboardFantom = true;
		AddCharHP(chr, boarding_enemy_hp); // влияение опыта и морали в НР
		if (IsCharacterPerkOn(chr, "Ciras") && rand(4)==0)
		{
			string cirnum1;
			switch (rand(4))
			{
				case 0: cirnum1 = "cirass1"; break;
				case 1: cirnum1 = "cirass1"; break;
				case 2: cirnum1 = "cirass2"; break;
				case 3: cirnum1 = "cirass3"; break;
				case 4: cirnum1 = "cirass4"; break;
			}
			if (CheckAttribute(chr, "HeroModel")) // все, у кого есть что одеть
			{
				switch (cirnum1)
				{
					case "cirass1": chr.model = GetSubStringByNum(chr.HeroModel, 1); break;
					case "cirass2": chr.model = GetSubStringByNum(chr.HeroModel, 2); break;
					case "cirass3": chr.model = GetSubStringByNum(chr.HeroModel, 3); break;
					case "cirass4": chr.model = GetSubStringByNum(chr.HeroModel, 4); break;
				}
			}
			chr.cirassId = Items_FindItemIdx(cirnum1);
			Log_TestInfo("Персонаж "+chr.name+" получил кирасу "+cirnum1);
		}
	}
	//ставим вражеских мушкетеров -->
	if (CheckCharacterPerk(boarding_enemy, "MusketsShoot") || IsFort)
	{
		if (!CheckAttribute(&Locations[locIndex], "CabinType") && !CheckAttribute(boarding_enemy, "GenQuest.CrewSkelMode"))
		{
			if (!IsFort) iQty = 7;
			else iQty = 3;
			for(i=1; i<=iQty; i++)
			{
				if (LAi_CheckLocatorFree("rld", sLocType+"mush"+i))
				{
					model = LAi_GetBoardingMushketerModel(boarding_enemy);
					chr = GetCharacter(NPC_GenerateCharacter("GenChar_", model, "man", "mushketer", 5, sti(boarding_enemy.nation), 0, false));
					chr.id = "GenChar_" + chr.index;
					chr.AboardFantom = true;
					chr.MusketerDistance = 0;
					LAi_SetWarriorType(chr);
					LAi_group_MoveCharacter(chr, LAI_GROUP_BRDENEMY);
					ChangeCharacterAddressGroup(chr, locID, "rld", sLocType+"mush"+i);
				}
			}
			if (!IsFort)
			{
				SetMushketerParamAbordEnemy(chr);
			}
			else
			{
				SetMushketerParamFortEnemy(chr);
			}
			AddCharHP(chr, boarding_enemy_hp); // влияение опыта и морали в НР
		}
	}
	//<-- ставим вражеских мушкетеров
	//Заставим драться эти 2 группы
	LAi_group_FightGroupsEx(LAI_GROUP_PLAYER, LAI_GROUP_BRDENEMY, true, GetMainCharacterIndex(), -1, false, false);
	LAi_group_SetCheckEvent(LAI_GROUP_BRDENEMY);
}

//Убийство группы
void LAi_BoardingGroupKill()
{
	string group = GetEventData();
	if(group != LAI_GROUP_BRDENEMY) return;
	// отключим шум абордажа (который включается при аларме в sound.c)

	if (CheckAttribute(pchar, "questTemp.Whisper.KilledPortman"))
	{
		Log_Info("Вы находите журнал капитана.");
		LAi_SetFightMode(PChar, false);
		PlaySound("interface\important_item.wav");
		DoQuestCheckDelay("TalkSelf_Quest", 0.8);
	}

	PostEvent("LAi_event_boarding_EnableReload", 1000);
}

//Моделька для абордажного персонажа
string LAi_GetBoardingModel(ref rCharacter, ref ani)
{
	ani = "man";
	int iNation = sti(rCharacter.nation);
	string atr;
	string model;


	if (CheckAttribute(rCharacter, "GenQuest.CrewSkelMode"))
    {
        model = GetRandSkelModel();
		ani = "man";
		return model;
    }
	if (CheckAttribute(rCharacter, "GenQuest.CrewSkelModeClassic"))
    {
        model = GetRandSkelModelClassic();
		ani = "man";
		return model;
    }
    if (CheckAttribute(rCharacter, "OZG") == true)
    {
        model = "OZG_" + (rand(8) + 1);
	    ani = "man";
		return model;
    }

	if(sti(rCharacter.index) == GetMainCharacterIndex())
	{
        // boal 290904 форма солдат -->
        if (CheckAttribute(rCharacter, "GenQuest.CrewSkelMode"))
        {
            model = GetRandSkelModel();
			ani = "man";
			return model;
        }
		if (CheckAttribute(rCharacter, "OZG") == true)
        {
            model = "OZG_" + (rand(9) + 1);
			ani = "man";
			return model;
        }
        if (isMainCharacterPatented() && sti(Items[sti(rCharacter.EquipedPatentId)].TitulCur) > 1) //форма только со звания капитан
        {
            atr = "boardingModel.enemy";
            iNation = sti(Items[sti(rCharacter.EquipedPatentId)].Nation);
        }
        else
        {
            atr = "boardingModel.player";
        }
        // boal 290904 форма солдат <--
	}
	else
    {   //boal -->
		if (CheckAttribute(rCharacter, "Ship.Mode") && rCharacter.Ship.Mode == "Trade")
		{
            atr = "boardingModel.merchant";
        }
		else
        {//boal <--
            atr = "boardingModel.enemy";
        }
	}

	if (iNation < 0) iNation = PIRATE;
	//eddy. замаскировавшися пиратов тоже надо учитывать
	if (CheckAttribute(rCharacter, "Ship.Mode") && rCharacter.Ship.Mode == "Pirate" && !IsMainCharacter(rCharacter)) iNation = PIRATE;
	Nations[iNation].boardingModel.player = "";
	Nations[iNation].boardingModel.enemy = "";
	Nations[iNation].boardingModel.merchant = "";

	aref models;
	makearef(models, Nations[iNation].(atr));
	int num = GetAttributesNum(models);
	if(num <= 0) return "pirate_1";
	int i = rand(num - 1);
	atr = GetAttributeName(GetAttributeN(models, i));
	model = models.(atr);
	atr = atr + ".ani";
	if(CheckAttribute(models, atr))
	{
		if(models.(atr) != "")
		{
			ani = models.(atr);
		}
	}
	if (GetCharacterItem(rCharacter, "SkullAztec") && rand(1)==0)
	{
		if(rand(1)==0)	model = GetRandSkelModel();
		else			model = GetRandSkelModelClassic();

		ani = "man";
		return model;
	}

	return model;
}

string LAi_GetBoardingMushketerModel(ref rCharacter)
{
	string model;
	int iNation = sti(rCharacter.nation);

	if(sti(rCharacter.index) == GetMainCharacterIndex())
	{
        if (isMainCharacterPatented() && sti(Items[sti(rCharacter.EquipedPatentId)].TitulCur) > 1) //форма только со звания капитан
        {
            iNation = sti(Items[sti(rCharacter.EquipedPatentId)].Nation);
        }
        else
        {
            iNation = PIRATE;
        }
	}
	else
    {   //boal -->
		if (CheckAttribute(rCharacter, "Ship.Mode") && rCharacter.Ship.Mode == "Trade")
		{
            iNation = PIRATE;
        }
		else
        {//boal <--
            iNation = sti(rCharacter.nation);
        }
	}

	if (iNation < 0) iNation = PIRATE;
	//eddy. замаскировавшися пиратов тоже надо учитывать
	if (CheckAttribute(rCharacter, "Ship.Mode") && rCharacter.Ship.Mode == "Pirate") iNation = PIRATE;
	if(iNation == PIRATE)
	{
		model = GetPirateMushketerModel();
	}
	else
	{
		model = NationShortName(iNation) + "_mush_" + (rand(2)+1);
	}
	return model;
}

// boal 03/08/06 полностью переписал метод Stone-D от 27/07/2003
bool CheckForSurrender(ref mchr, ref echr, int _deck)
{
    if(boarding_location_type == BRDLT_FORT) return false; // Forts don't surrender.

    if (GetPrisonerQty() > PRISONER_MAX) return false; // очень много пленых

	float fEnemyRate = 0.5 - 0.02 * MOD_SKILL_ENEMY_RATE;
	if (sti(echr.Nation) == PIRATE)
	{
		fEnemyRate = 0.2 - 0.01 * MOD_SKILL_ENEMY_RATE;
	}
	else
	{
		if (CheckAttribute(echr, "Ship.Mode") && echr.Ship.Mode == "Trade") // торговцы склонны сдаться
		{
			fEnemyRate = 0.9 - 0.03 * MOD_SKILL_ENEMY_RATE;
		}
	}

	int eclass = GetCharacterShipClass(echr);
	int mclass = GetCharacterShipClass(mchr);

	float mcrew = stf(GetWeaponCrew(mchr, GetCrewQuantity(mchr))); // честный учет с оружием
	float ecrew = stf(GetCrewQuantity(echr));

	float fRep    = Bring2Range(0.0, 1.0, stf(REPUTATION_MIN), stf(REPUTATION_MAX), stf(mchr.reputation)); // приведение к 0..1
	float mmorale = stf(mchr.ship.crew.morale) / MORALE_MAX; // 0..1
	float emorale = stf(echr.ship.crew.morale) / MORALE_MAX; // 0..1
	float mskill  = (GetSummonSkillFromName(mchr, "Leadership") + GetSummonSkillFromName(mchr, "Grappling")) / (2.0 * SKILL_MAX_TOTAL);  // 0..1
	float eskill  = (GetCharacterSkill(echr, "Leadership") + GetCharacterSkill(echr, "Defence")) / (2.0 * SKILL_MAX_TOTAL);              // 0..1
	float mcskill = GetCrewExp(mchr, "Soldiers") / GetCrewExpRate();
	float ecskill = GetCrewExp(echr, "Soldiers") / GetCrewExpRate();

	mcrew = mcrew * (1.0 + 5.0 * mskill) * (1.0 + 5.0 * mcskill) * (1.0 + 5.0 * mmorale) * (1.0 + 0.5 * _deck) * fEnemyRate * (fRep * fRep * fRep); // Если у ГГ низкая репутация - очень не хотят сдаваться
	ecrew = ecrew * (1.0 + 5.0 * eskill) * (1.0 + 5.0 * ecskill) * (1.0 + 5.0 * emorale);

	float seaDogCoeff = 1.0;
	if (CheckOfficersPerk(mchr, "SeaDogProfessional") && CheckAttribute(pchar, "SeaDogProfessionalSwitch"))
	{
		if (pchar.SeaDogProfessionalSwitch == 1)
			seaDogCoeff = 2.0;
	}
	mcrew = mcrew * seaDogCoeff;

	// подсчет компаньенов у сторон  -->
    int mShip = GetCompanionQuantity(mchr);
    int eShip;
    string sGroupID = Ship_GetGroupID(echr);
    if (sGroupID != "")
    {
    	eShip = Group_GetLiveCharactersNum(sGroupID);
    }
    else
    {
    	eShip = 1;
    }
    mcrew = mcrew * (1.0 + (mShip - 1) / 10.0);
    ecrew = ecrew * (1.0 + (eShip - 1) / 10.0);
	// <--

    Log_TestInfo("Surrender Hero = " + mcrew + "    Enemy = " + ecrew + " eShipQty = " + eShip);

    if (mcrew > ecrew)
	{
		int randval = rand(1000);
		Log_TestInfo("rand: " + randval);
		if (randval < 1000.0 * (mcrew - ecrew) / ecrew)
		{
			Log_TestInfo("Surrender!");
			return true;
		}
	}
	Log_TestInfo("Fight!");
	return false;
}

// boal 03/12/05 выбор локатора от корабля лок - маленькие, алок - большие-->
string ChooseShipUpDeck(ref _mchar, ref _enemy)
{
    string sLoc = "loc";

	if (GetCargoMaxSpace(_mchar) > GetCargoMaxSpace(_enemy))
	{
	    sLoc = "aloc";
	}

    return sLoc;
}
// boal 03/12/05 <--
// CSM -->
#event_handler("csmEvent_RefreshReload", "csmRefreshReload");
void csmRefreshReload()
{
	if (!LAi_IsBoardingProcess() || !IsEntity(&loadedLocation))
	{
		csmDA(pchar, "CSM.LootCollector.CanBeRun");
		return;
	}

	if (loadedLocation.type == "boarding_cabine" && csmCA(pchar, "CSM.LootCollector.Enable"))
		csmDA(pchar, "CSM.LootCollector.CanBeRun");

	if (g_ActiveActionName == "" || g_ActiveActionName == "Nothing")
		Log_SetActiveAction("Reload");

	PostEvent("csmEvent_RefreshReload", 250);
}
// CSM <--
