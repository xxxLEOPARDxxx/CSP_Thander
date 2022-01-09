// Warship -->
// Выставлялка рандомных скиллов
void SetRandSelfSkill(ref _ch, int _min, int _max)
{
	int iDelta = _max-_min;
	_ch.skill.Leadership = _min + rand(iDelta);
	_ch.skill.FencingLight = _min + rand(iDelta);
	_ch.skill.Fencing = _min + rand(iDelta);
	_ch.skill.FencingHeavy = _min + rand(iDelta);
	_ch.skill.Pistol = _min + rand(iDelta);
	_ch.skill.Fortune = _min + rand(iDelta);
	_ch.skill.Sneak = _min + rand(iDelta);
}

void SetRandShipSkill(ref _ch, int _min, int _max)
{
	int iDelta = _max-_min;
	_ch.skill.Sailing = _min + rand(iDelta);
	_ch.skill.Commerce = _min + rand(iDelta);
	_ch.skill.Accuracy = _min + rand(iDelta);
	_ch.skill.Cannons = _min + rand(iDelta);
	_ch.skill.Repair = _min + rand(iDelta);
	_ch.skill.Grappling = _min + rand(iDelta);
	_ch.skill.Defence = _min + rand(iDelta);
}

void DeleteAllPerksExceptChar(ref _ch)
{
	string character = "";
	if (CheckAttribute(_ch,"perks.list.Buccaneer")) character = "Buccaneer";
	if (CheckAttribute(_ch,"perks.list.Fencer")) character = "Fencer";
	if (CheckAttribute(_ch,"perks.list.Grunt")) character = "Grunt";
	if (CheckAttribute(_ch,"perks.list.Trader")) character = "Trader";
	if (CheckAttribute(_ch,"perks.list.Adventurer")) character = "Adventurer";
	if (CheckAttribute(_ch,"perks.list.Agent")) character = "Agent";
	if (CheckAttribute(_ch,"perks.list.SeaWolf")) character = "SeaWolf";
	DeleteAttribute(_ch,"perks.list");
	_ch.perks.list.(character) = 1;
}

void SelAllPerksToNotPChar(ref _ch)
{
	_ch.perks.list.BasicDefense = "1";
	_ch.perks.list.AdvancedDefense = "1";
	_ch.perks.list.CriticalHit = "1";
	_ch.perks.list.Ciras = "1";
	_ch.perks.list.SwordplayProfessional = "1";
	//_ch.perks.list.Grus = "1";
	_ch.perks.list.Rush = "1";
	_ch.perks.list.Tireless = "1";
	_ch.perks.list.HardHitter = "1";
	_ch.perks.list.BladeDancer = "1";
	_ch.perks.list.Sliding = "1";
	_ch.perks.list.Gunman = "1";
	_ch.perks.list.GunProfessional = "1";
	_ch.perks.list.IronWill = "1";
	//_ch.perks.list.Medic = "1";
	_ch.perks.list.HPPlus = "1";
	_ch.perks.list.EnergyPlus = "1";
	_ch.perks.list.Trustworthy = "1";
	_ch.perks.list.ShipEscape = "1";

	_ch.perks.list.FlagPir = "1";
	_ch.perks.list.FlagEng = "1";
	_ch.perks.list.FlagFra = "1";
	_ch.perks.list.FlagSpa = "1";
	_ch.perks.list.FlagHol = "1";
	_ch.perks.list.FastReload = "1";
	_ch.perks.list.ImmediateReload = "1";
	_ch.perks.list.HullDamageUp = "1";
	_ch.perks.list.SailsDamageUp = "1";
	_ch.perks.list.CrewDamageUp = "1";
	_ch.perks.list.CriticalShoot = "1";
	_ch.perks.list.LongRangeShoot = "1";
	_ch.perks.list.CannonProfessional = "1";
	_ch.perks.list.LongRangeGrappling = "1";
	_ch.perks.list.MusketsShoot = "1";
	_ch.perks.list.GrapplingProfessional = "1";
	_ch.perks.list.BasicBattleState = "1";
	_ch.perks.list.AdvancedBattleState = "1";
	_ch.perks.list.ShipDefenseProfessional = "1";
	_ch.perks.list.LightRepair = "1";
	_ch.perks.list.InstantRepair = "1";
	_ch.perks.list.ShipSpeedUp = "1";
	_ch.perks.list.ShipTurnRateUp = "1";
	_ch.perks.list.StormProfessional = "1";
	_ch.perks.list.Turn180 = "1";
	_ch.perks.list.SailingProfessional = "1";
	_ch.perks.list.Brander = "1";
	_ch.perks.list.Troopers = "1";
	_ch.perks.list.BasicCommerce = "1";
	_ch.perks.list.AdvancedCommerce = "1";
	_ch.perks.list.Carpenter = "1";
	_ch.perks.list.Builder = "1";
	_ch.perks.list.WindCatcher = "1";
	_ch.perks.list.SailsMan = "1";
	_ch.perks.list.Doctor1 = "1";
	_ch.perks.list.Doctor2 = "1";
	_ch.perks.list.EmergentSurgeon = "1";
	_ch.perks.list.ByWorker = "1";
	_ch.perks.list.ByWorker2 = "1";
}

// Установить персу все перки
void SelAllPerksToChar(ref _ch, bool _isOfficer)
{
	_ch.perks.list.BasicDefense = "1";
	_ch.perks.list.AdvancedDefense = "1";
	_ch.perks.list.CriticalHit = "1";
	_ch.perks.list.Ciras = "1";
	_ch.perks.list.SwordplayProfessional = "1";
	_ch.perks.list.AgileMan = "1";
	//_ch.perks.list.Grus = "1";
	_ch.perks.list.Rush = "1";
	_ch.perks.list.Tireless = "1";
	_ch.perks.list.HardHitter = "1";
	_ch.perks.list.BladeDancer = "1";
	_ch.perks.list.Sliding = "1";
	_ch.perks.list.Gunman = "1";
	_ch.perks.list.GunProfessional = "1";
	_ch.perks.list.IronWill = "1";
	_ch.perks.list.SharedExperience = "1";
	//_ch.perks.list.Medic = "1";
	_ch.perks.list.Craft = "1";
	_ch.perks.list.HPPlusFixed = "1";
	_ch.perks.list.EnergyPlusFixed = "1";
	_ch.perks.list.Trustworthy = "1";
	_ch.perks.list.UnlimitedContra = "1";
	_ch.perks.list.ShipEscape = "1";
	_ch.perks.list.Buldozer = "1";
	_ch.perks.list.AboardCollector = "1";

	_ch.perks.list.FlagPir = "1";
	_ch.perks.list.FlagEng = "1";
	_ch.perks.list.FlagFra = "1";
	_ch.perks.list.FlagSpa = "1";
	_ch.perks.list.FlagHol = "1";
	_ch.perks.list.FastReload = "1";
	_ch.perks.list.ImmediateReload = "1";
	_ch.perks.list.HullDamageUp = "1";
	_ch.perks.list.SailsDamageUp = "1";
	_ch.perks.list.CrewDamageUp = "1";
	_ch.perks.list.CriticalShoot = "1";
	_ch.perks.list.LongRangeShoot = "1";
	_ch.perks.list.CannonProfessional = "1";
	_ch.perks.list.LongRangeGrappling = "1";
	_ch.perks.list.MusketsShoot = "1";
	_ch.perks.list.GrapplingProfessional = "1";
	_ch.perks.list.BasicBattleState = "1";
	_ch.perks.list.AdvancedBattleState = "1";
	_ch.perks.list.ShipDefenseProfessional = "1";
	_ch.perks.list.LightRepair = "1";
	_ch.perks.list.InstantRepair = "1";
	_ch.perks.list.ShipSpeedUp = "1";
	_ch.perks.list.ShipTurnRateUp = "1";
	_ch.perks.list.StormProfessional = "1";
	_ch.perks.list.Turn180 = "1";
	_ch.perks.list.SeaDogProfessional = "1";
	_ch.perks.list.SailingProfessional = "1";
	_ch.perks.list.Brander = "1";
	_ch.perks.list.Troopers = "1";
	_ch.perks.list.BasicCommerce = "1";
	_ch.perks.list.AdvancedCommerce = "1";
	_ch.perks.list.Carpenter = "1";
	_ch.perks.list.Builder = "1";
	_ch.perks.list.WindCatcher = "1";
	_ch.perks.list.SailsMan = "1";
	_ch.perks.list.Doctor1 = "1";
	_ch.perks.list.Doctor2 = "1";
	_ch.perks.list.EmergentSurgeon = "1";

	if(_isOfficer) // У офов есть доп. перки
	{
		_ch.perks.list.ByWorker = "1";
		_ch.perks.list.ByWorker2 = "1";
	}
}

// Установить персу половину перков
void SetHalfPerksToChar(ref _ch, bool _isOfficer)
{
	_ch.perks.list.BasicDefense = "1";
	_ch.perks.list.AdvancedDefense = "1";
	_ch.perks.list.CriticalHit = "1";
	_ch.perks.list.Ciras = "1";
	_ch.perks.list.SwordplayProfessional = "1";
	_ch.perks.list.Gunman = "1";
	_ch.perks.list.SharedExperience = "1";

	_ch.perks.list.FlagPir = "1";
	_ch.perks.list.FlagEng = "1";
	_ch.perks.list.FlagFra = "1";
	_ch.perks.list.FlagSpa = "1";
	_ch.perks.list.FlagHol = "1";
	_ch.perks.list.HullDamageUp = "1";
	_ch.perks.list.SailsDamageUp = "1";
	_ch.perks.list.CrewDamageUp = "1";
	_ch.perks.list.CriticalShoot = "1";
	_ch.perks.list.LongRangeShoot = "1";
	_ch.perks.list.LongRangeGrappling = "1";
	_ch.perks.list.GrapplingProfessional = "1";
	_ch.perks.list.BasicBattleState = "1";
	_ch.perks.list.AdvancedBattleState = "1";
	_ch.perks.list.ShipSpeedUp = "1";
	_ch.perks.list.ShipTurnRateUp = "1";
	_ch.perks.list.StormProfessional = "1";
	_ch.perks.list.Turn180 = "1";
	_ch.perks.list.SailingProfessional = "1";
	_ch.perks.list.WindCatcher = "1";
	_ch.perks.list.SailsMan = "1";

	if(_isOfficer) // У офов есть доп. перки
	{
		_ch.perks.list.ByWorker = "1";
		_ch.perks.list.ByWorker2 = "1";
	}
}

// Отобрать все предметы (кроме квестовых) у выбранного персонажа
void RemoveAllCharacterItems(ref _ch, bool _removemoney)
{
	// сносим нафик всю экипировку
	if(_ch == GetMainCharacter())
	{
		StoreEquippedMaps(_ch);
		_ch.MapsAtlasCount = 0;
	}
	RemoveCharacterEquip(_ch, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(_ch, GUN_ITEM_TYPE);
	RemoveCharacterEquip(_ch, SPYGLASS_ITEM_TYPE);
	RemoveCharacterEquip(_ch, PATENT_ITEM_TYPE);
	RemoveCharacterEquip(_ch, CIRASS_ITEM_TYPE);
	RemoveCharacterEquip(_ch, MAPS_ITEM_TYPE);
	RemoveCharacterEquip(_ch, BACKPACK_ITEM_TYPE);
	RemoveCharacterEquip(_ch, TALISMAN_ITEM_TYPE);
	RemoveCharacterEquip(_ch, BOOK_ITEM_TYPE);

	//сносим все предметы, кроме квестовых -->
	aref arItems;
	string sName;
	ref rLoc;
	makearef(arItems, _ch.items);
	int	Qty = GetAttributesNum(arItems);
	for (int a=0; a<Qty; a++)
	{
		sName = GetAttributeName(GetAttributeN(arItems, a));
		rLoc = ItemsFromID(sName);
		if (rLoc.ItemType == "QUESTITEMS")
		{
			_ch.questTemp.items.(sName) = _ch.items.(sName);
		}
	}
	DeleteAttribute(_ch, "items");
	_ch.items = "";
	makearef(arItems, _ch.questTemp.items);
	Qty = GetAttributesNum(arItems);
	for (a=0; a<Qty; a++)
	{
		sName = GetAttributeName(GetAttributeN(arItems, a));
		TakeNItems(_ch, sName, sti(arItems.(sName)));
	}
	DeleteAttribute(_ch, "questTemp.items");

	if(_removemoney)
	{
		_ch.money = 0;
	}
}

// снести всех пассажиров и компаньонов ГГ
void RemoveAllPassengersAndCompanions()
{
    int iDay = GetPassengersQuantity(pchar);
    int i = 0;
    int n = 0;
	int idx;
	ref ch;

 	while (i < iDay)
	{
		i++;
		idx = GetPassenger(pchar, n); // всегда первый в массиве со смещением, если не трем
		if (idx == -1) break;
		ch = GetCharacter(idx);
		if (GetRemovable(ch)) // квестовых не трогаем
		{
		    ch.LifeDay = 1; // чтоб не сразу потерся
		    RemovePassenger(pchar, ch);
			ChangeCharacterAddress(ch,"none","");
		}
		else
		{
		    n++;
		}
	}
    for (i=0; i<COMPANION_MAX; i++)
	{
		idx = GetCompanionIndex(pchar, i);
		if (idx != -1)
		{
            ch = GetCharacter(idx);
			if (GetShipRemovable(ch) && GetRemovable(ch))  // не трогаем квестовых и ПГГ
			{
			    ch.LifeDay = 1; // чтоб не сразу потерся
			    RemoveCharacterCompanion(pchar, ch);
			}
		}
	}
}

void CleanAllCabinBoxes()
{
	ref loc;
	int n;
	string sTemp;

    if (Pchar.SystemInfo.CabinType != "")
    {
	    loc = &locations[FindLocation(Pchar.SystemInfo.CabinType)]; //"My_Cabin"

	    for (n = 1; n <= 4; n++)
	    {
	        sTemp = "box" + n;
			DeleteAttribute(loc, sTemp + ".items");
		    loc.(sTemp).items = "";
		    loc.(sTemp) = Items_MakeTime(0, 0, 1, 2003);
		    loc.(sTemp).money = 0;
	    }
    }
    loc = &locations[FindLocation("My_Deck")];
    for (n = 1; n <= 4; n++)
    {
        sTemp = "box" + n;
		DeleteAttribute(loc, sTemp + ".items");
	    loc.(sTemp).items = "";
	    loc.(sTemp) = Items_MakeTime(0, 0, 1, 2003);
	    loc.(sTemp).money = 0;
    }
}

// Метод вернет случайный тип корабля, который зависит от класса шипа персонажа
int RandShipFromShipClass(ref _ch)
{
	int iShipClass = sti(RealShips[sti(_ch.Ship.Type)].Class);
	int iShipType;
	switch(iShipClass)
	{
		case 1:
			iShipType = SHIP_WARSHIP + rand(2);
			break;

		case 2:
			iShipType = SHIP_FRIGATE + rand(1);
			break;

		case 3:
			iShipType = SHIP_CORVETTE + rand(2);
			break;

		case 4:
			iShipType = SHIP_FLEUT + rand(2);
			break;

		case 5:
			iShipType = SHIP_BARQUE + rand(1);
			break;

		case 6:
			iShipType = SHIP_SLOOP + rand(1);
			break;

		case 7:
			iShipType = SHIP_WAR_TARTANE + rand(1);
			break;
	}
	return iShipType;
}

// Проверка, есть ли у ГГ казначей
bool IsPCharHaveTreasurer()
{
	ref rOfficer;

	for(int i=0; i<MAX_CHARACTERS; i++)
	{
		rOfficer = &characters[i];
		if(CheckAttribute(rOfficer, "treasurer") && sti(rOfficer.Treasurer) == 1)
		{
			return true; // Казначей есть
		}

	}

	return false;
}

// Метод вернет ссылку на казначея
ref GetPCharTreasurerRef()
{
	if(!IsPCharHaveTreasurer()) return &NullCharacter;
	for(int i=0; i<MAX_CHARACTERS; i++)
	{
		if(CheckAttribute(&characters[i], "treasurer") && sti(characters[i].Treasurer) == 1)
		{
			return &characters[i];
		}
	}

	return &NullCharacter;
}

// Метод вернет значение атрибута
string GetAttrValue(ref _rChar, string _sAttr)
{
	string sTemp;
	if(!CheckAttribute(_rChar, _sAttr)) _rChar.(_sAttr) = "";

	sTemp = _rChar.(_sAttr);
	return sTemp;
}

// Получить рандомную локацию с указанным типом на заданном острове
string IslandGetLocationFromType(string _island, string _type)
{
	ref rLoc;
	int i, iMaxLoc[MAX_LOCATIONS];
	int iRandLoc = 0;
	for(i=1; i<MAX_LOCATIONS; i++)
	{
		makeref(rLoc, locations[i]);
		if(findsubstr(rLoc.id, _type, 0) != -1 && rLoc.islandId == _island)
		{
			iMaxLoc[iRandLoc] = i;
			iRandLoc++;
		}
	}

	if(iRandLoc == 0)
		return "none";

	i = iMaxLoc[rand(iRandLoc-1)];
	return locations[i].id;
}

// Просто сокращение -->
void DisableAllExits(bool _truefalse)
{
	chrDisableReloadToLocation = _truefalse;
	bDisableFastReload         = _truefalse;
}
// Просто сокращение <--

// Warship <--

void LockQuestLine(ref refChar) // Лочим квестовую линейку
{
	refChar.notQuestLine = true;
}

string QuestGetGangLocation(string _areal)	// Получить локацию для генерации банд и т.д.
{
	int n;
	string island = GetArealByCityName(_areal);
	string LocationId, sAreal;
	int storeArray[MAX_LOCATIONS];
	int howStore = 0;

	for(n=0; n<MAX_LOCATIONS; n++)
	{
		if(GiveArealByLocation(&locations[n]) == island)
		{
			//==> на всякий случай
			if(CheckAttribute(&locations[n], "DisableEncounters") && locations[n].DisableEncounters == true) continue;
			LocationId = locations[n].id;
			if(findsubstr(LocationId, "jungle" , 0) != -1 || findsubstr(LocationId, "Shore" , 0) != -1 || findsubstr(LocationId, "CaveEntrance" , 0) != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	n = storeArray[rand(howStore-1)];
	return locations[n].id;
}

string QuestGetColony(string _city) // Получить рандомную колонию по аттрибуту NPChar.city, не равную _city
{
    int storeArray[MAX_COLONIES];
    int howStore = 0;
	string sChrId;

	for(int n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetRelation2BaseNation(sti(colonies[n].nation)) != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != _city)
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	return colonies[storeArray[rand(howStore-1)]].id;
}

string GetColonyExpect2Colonies(string _city1, string _city2) // Исключая две колонии
{
	int storeArray[MAX_COLONIES];
	int howStore = 0;
	string sChrId;
	ref rColony;

	for(int n=0; n<MAX_COLONIES; n++)
	{
		makeref(rColony, colonies[n]);
		if(!CheckAttribute(rColony, "HasNoFort") && rColony.nation != "none" && sti(rColony.nation) != PIRATE && GetRelation2BaseNation(sti(rColony.nation)) != RELATION_ENEMY && rColony.id != "Panama" && rColony.id != _city1 && rColony.id != _city2)
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	return colonies[storeArray[rand(howStore-1)]].id;
}

void initStartState2Character(ref ch)
{// метод вызывается в момент новой игры, заполняет главного героя атрибутами, чтоб убрать лишние проверки в if
    NullCharacter.Siege = "";

	ch.SystemInfo.SaveCount = 0;
    ch.SystemInfo.LoadCount = 0;
    ch.SystemInfo.DeadCount = 0;

    ch.SystemInfo.CabinType          = ""; // boal 28.03.05 каюты нет  My_Cabin_Small

    ch.questTemp.Contraband.relation = 60;
    DeleteAttribute(ch, "quest.meeting");
    ch.ShipInStock = 0; // кораблей в порту
	ch.questTemp.abordage = 0;   // двойной абордаж
	ch.questTemp.donate   = 0; // пожертвование церкви

	ch.questTemp.friend_in_tavern = ""; // оптимизация boal
	ch.questTemp.RelationAgentMet = "0"; // оптимизация boal

	ch.questTemp.NationQuest = ""; // взятая линейка квестов

	ch.GenQuest.BrothelCount = "0"; // счетчик посещений девочек
	//ch.GenQuest.Hunter2Pause   = false; // признак бойни в форте на суше - не делать ОЗГов
	ch.I_MAP_SHOW = false;  // boal карты смотрим из предметов
	ch.CameraHoldPos = false;
	ch.CameraShipNPC = 0;// номер компаньона для камеры 0 - ГГ
	ch.GenQuestFort.FarLocator = true; // для методов пихания фантомов в город

	// Черная жемчужина
	ch.GenQuest.GhostShip.DeadByMe       = 0;
	ch.GenQuest.GhostShip.KillMe         = 0;
	ch.GenQuest.GhostShip.AskAbout       = 0; // в таверне три раза спросить до появления
	ch.GenQuest.GhostShip.lastspeak_date = "";
    GhostShipInit();

    ch.GenQuest.Find_Merchant.lastspeak_date = "";
    ch.GenQuest.ConvoyPassenger = ""; //структура недовольных по квесту доставки пассажира

	// ==> состояние квеста текущей линейки
	ch.questTemp.State = "";
	// ==> кол-во дней ожидания выдачи следующего квеста губером, стандарт - два дня
	ch.questTemp.Waiting_time = "2";
	// ==> номер текущего квеста, присваиваем сразу второй, т.к. первый берется на момент первого обращения к губеру.
	ch.questTemp.CurQuestNumber = "2";
	//параметры островов и бухт для корсарского метро, ПГГ, и много еще чего :)
	InitTravelMap();
	// ==> проверка не посещение борделей после свадьбы
	pchar.RomanticQuest.HorseCheck = -1;
	// ==> Количество карт в навигационном атласе
	ch.MapsAtlasCount = 0;
	// ==> Номер пиратского флага (берется из текстуры персональных флагов ГГ)
	ch.Flags.Pirate = 5;
	// ==> Квест Аскольда.
	ch.questTemp.Ascold = "canTakeQuest"; // состояние, если равен "", то пока не даем квест.
	// ==> работорговец
	ch.questTemp.Slavetrader = "canTakeQuest"; //сюда же пихаем флаг
	// ==> общий индекс Аззи.
	ch.questTemp.Azzy = "1";
	// ==> выбор хозяна магазина и уличного торговца по Аскольду.
	SelectAscoldRendom();
	// ==> выбор ростовщика-работорговца
	SelectSlavetraderRendom(); //это непосредственно выбор
	// ==> квест Изабеллы
	IsabellaInit();
	//==>квест История давней дружбы Lipsar
	SilencePriceInit();
	// ==> Квесты Проклятие Дальних Морей Sinistra
	PDMQuestsInit();
	// ==>  флаги и иниты бергларов
	BerglarsInit();
	// ==>  нищие
	PoormansInit();
	// ==>  кол-во лута, отданного шлюхами
	pchar.questTemp.HorseLoot = 0;
	// ==>  кол-во перетраха со шлюхами
	pchar.questTemp.HorseQty = 0;
	// ==> прерывания на ход к жемчужному промыслу
	PearlGen_SetSantaCatalina("none");
	PearlGen_SetTeno("none");
	// ==> спрашивальщики
	QuestionsInit();
	SeaQuestionsInit(); //02/02/08
	// ==> тюремный флаг на проход внутрь
	ch.questTemp.jailCanMove = false;
	OfficerGirlInit();
	// ==> мушкетеры
	OfficerMushketerInit();
	// ==> линейка ГПК
	ch.questTemp.LSC = false;
	ch.questTemp.LSC.checkBoxes = false; //флаг проверки сундуков в полночь
	pchar.quest.FirstLoginLostShipsCity.win_condition.l1 = "location";
	pchar.quest.FirstLoginLostShipsCity.win_condition.l1.location = "LostShipsCity_town";
	pchar.quest.FirstLoginLostShipsCity.function = "FirstLoginLostShipsCity";
	// ==> квест получения Синей Птицы
	ch.questTemp.BlueBird = "begin";
	ch.questTemp.BlueBird.City = "";
	ch.questTemp.BlueBird.count = 0;
	// ==> генератор Шарпа по жемчугу
	ch.questTemp.Sharp = "begin";
	ch.questTemp.Sharp.City = "";
	ch.questTemp.Sharp.count = 0; //счетчик кол-ва поисков
	ch.questTemp.Sharp.brothelChance = 1; //античит, шанс встретить Шарпа прямо в борделе
	ch.questTemp.Sharp.SeekSpy = "begin"; //состояние квест на поиски информатора Шарпа
	// ==> пиратская линейка
	PiratesLineInit();
	// ==> набор мелких квестов, дается по одному до закрытия
	ch.questTemp.different = "free";
	// ==> линейка Блада homo
	ch.questTemp.CapBloodLine = true;
	ch.questTemp.WhisperLine = true;
	ch.questTemp.CapBUnarmed = false; //ГГ сабля не положена - false
	// ==> линейка Теночтитлана
	ch.questTemp.Teno = "begin";
	pchar.quest.Teno_startInShore.win_condition.l1 = "location";
	pchar.quest.Teno_startInShore.win_condition.l1.location = "Shore53";
	pchar.quest.Teno_startInShore.function = "Teno_startInShore";
	//зачарованный город
	LocatorReloadEnterDisable("Shore_ship3", "reload1", true);
	ch.questTemp.MC = "begin"; //флаг квеста
	pchar.quest.MC_startInCaracas.win_condition.l1 = "location";
	pchar.quest.MC_startInCaracas.win_condition.l1.location = "Caracas_town";
	pchar.quest.MC_startInCaracas.function = "MC_startInCaracas";
	//ситуации в море
	ch.CanGenerateShipSituation = true;
}

//==> eddy. квестовая обработка 'ноль часов'.
void QuestActions()
{
	ref sld;
	int i;
	CompanionTravel_ProcessAllTravellers(); // Warship. Процессирование компаньонов-путешественников
	// забираем просроченные лицензии
	for (i=0; i<4; i++)
	{
		if (CheckCharacterItem(pchar, NationShortName(i)+"TradeLicence") && GetDaysContinueNationLicence(i) == -1)
		{
			TakeNationLicence(i);
		}
	}
	//Если идет линейка ГПК, то шмаляем открытые сундуки. Все, кроме Диффиндура.
	if (sti(pchar.questTemp.LSC.checkBoxes))
	{
		LSC_checkBoxes();
	}
	//************** Фр.линейка, третий квест. открываем двери дома коменданта Гаваны *******************
	if (pchar.questTemp.State == "Fr3TakeAnna_WaitMidnight")
	{
		LocatorReloadEnterDisable("Havana_town", "houseS1", false);
        Pchar.quest.Fr3TakeAnna_FightInHouse.win_condition.l1 = "location";
        Pchar.quest.Fr3TakeAnna_FightInHouse.win_condition.l1.location = "Havana_houseS1";
        Pchar.quest.Fr3TakeAnna_FightInHouse.win_condition = "Fr3TakeAnna_FightInHouse";
		pchar.questTemp.State = "Fr3TakeAnna_DoorIsOpen";
	}
	//************** Изабелла, вечер ужина после спасения братца наступил *******************
	if (CheckAttribute(pchar, "RomanticQuest") && pchar.RomanticQuest == "DelivMigel")
	{
		pchar.RomanticQuest = "SeeTalkNearHouse"; //детектор на итеме теперь сработает
        sld = CharacterFromID("MigelDeValdes");
		//Мигель
		sld.dialog.currentnode = "TalkNearHouse_1";
        ChangeCharacterAddressGroup(sld, "SanJuan_town", "quest", "goto24");
        LAi_SetActorType(sld);
		sld.rank = 1; //чтобы умер сразу
		sld.skill.Fencing = 1;
		sld.skill.Pistol = 1;
		LAi_SetHP(sld, 1, 1);
		DeleteAttribute(sld, "Items");
		GiveItem2Character(sld, "blade1");
		GiveItem2Character(sld, "pistol1");
		GiveItem2Character(sld, "order");
		TakeNItems(sld,"bullet", 1);
		TakeNItems(sld,"GunPowder", 1);
		//Сальватор с бандюганами
		LAi_group_Delete("EnemyFight");
        sld = CharacterFromID("Husband");
        sld.dialog.currentnode = "TalkNearHouse_1";
        ChangeCharacterAddressGroup(sld, "SanJuan_town", "quest", "goto25");
        for (i=8; i<=9; i++)
        {
			sld = GetCharacter(NPC_GenerateCharacter("Bandit_"+i, "pirate_"+i, "man", "man", 30, PIRATE, 1, true));
			FantomMakeCoolFighter(sld, 30, 80, 70, "blade33", "pistol3", 100);
			LAi_SetStayType(sld);
			if (i==8) ChangeCharacterAddressGroup(sld, "SanJuan_town", "quest", "goto7");
			else ChangeCharacterAddressGroup(sld, "SanJuan_town", "quest", "goto26");
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		SetTimerCondition("Romantic_DeadBrother_Cancel", 0, 0, 1, false);
	}
	//************** Изабелла, свадьба!!!! *******************
	if (CheckAttribute(pchar, "RomanticQuest") && pchar.RomanticQuest == "WaitBeginWidding")
	{
		pchar.RomanticQuest = "BeginWidding";
		pchar.quest.Isabella_widding.win_condition.l1 = "locator";
		pchar.quest.Isabella_widding.win_condition.l1.location = "SanJuan_church";
		pchar.quest.Isabella_widding.win_condition.l1.locator_group = "quest";
		pchar.quest.Isabella_widding.win_condition.l1.locator = "detector1";
		pchar.quest.Isabella_widding.function = "Isabella_widding";
		sld = CharacterFromID("Isabella");
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld , "SanJuan_church", "goto",  "goto11");
		sld.dialog.currentnode = "TalkWidding";
		//падре
		LAi_SetActorType(CharacterFromID("SanJuan_Priest"));
		SetTimerCondition("Romantic_Widding_Cancel", 0, 0, 1, false);
	}
	//************** ночной сторож в церкви *******************
	if (CheckAttribute(pchar, "questTemp.different.Church_NightGuard"))
	{
		if (pchar.questTemp.different.Church_NightGuard == pchar.location)
		{
			if (!CheckAttribute(pchar, "pchar.quest.ChurchNightGuard_exitFromLoc") && sti(pchar.questTemp.different.Church_NightGuard.NightQty) < 3)
			{
				pchar.quest.ChurchNightGuard_exitFromLoc.win_condition.l1 = "ExitFromLocation";
				pchar.quest.ChurchNightGuard_exitFromLoc.win_condition.l1.location = pchar.location;
				pchar.quest.ChurchNightGuard_exitFromLoc.function = "ChurchNightGuard_exitFromLoc";
				DoQuestFunctionDelay("ChurchNightGuard_timerInChurch", 10.0 + frand(10.0));
			}
		}
		else
		{	//ГГ не находится в нужной церкви в момент полночи
			string sTitle = pchar.questTemp.different.Church_NightGuard + "Church_NightGuard";
			AddQuestRecordEx(sTitle, "Church_NightGuard", "2");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("ся","ась"));
			CloseQuestHeader(sTitle);
			DeleteAttribute(pchar, "questTemp.different.Church_NightGuard");
			ChangeCharacterReputation(pchar, -20);
		}
	}
	//************** линейка ГПК, переход в погребок таверны *******************
	if (pchar.questTemp.LSC == "toWineCellar")
	{
		if (GetHour() < 1)
		{
			pchar.questTemp.LSC = "toWineCellarGone";
			sld = characterFromId("LSCBarmen");
			LAi_SetStayTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "FleuronTavern", "rld", "stay1");
			PChar.quest.LSC_returnBarmen.win_condition.l1            = "Timer";
			PChar.quest.LSC_returnBarmen.win_condition.l1.date.hour  = 1;
			PChar.quest.LSC_returnBarmen.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			PChar.quest.LSC_returnBarmen.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			PChar.quest.LSC_returnBarmen.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			PChar.quest.LSC_returnBarmen.function = "LSC_returnBarmen";
		}
		else pchar.questTemp.LSC = "toWineCellarLate";
	}
	//************** линейка ГПК, переход в погребок для подслушивания *******************
	if (pchar.questTemp.LSC == "toInterception")
	{
		if (pchar.location == "FleuronTavern" && pchar.location.locator == "reload2")
		{
			DoQuestFunctionDelay("LSC_scriptInterception", 10.0 + frand(20));
		}
		else
		{
			pchar.questTemp.LSC = "InterceptionLate";
			AddQuestRecord("ISS_MainLine", "19");
		}
	}
	//************** линейка ГПК, завал первого каспера с помощь Армо *******************
	if (CheckAttribute (pchar, "questTemp.LSC.Armo"))
	{
		//первый каспер пошел
		if (sti(pchar.questTemp.LSC.Armo) == 1 || sti(pchar.questTemp.LSC.Armo) == 3 || sti(pchar.questTemp.LSC.Armo) == 5)
		{
			if (pchar.location == "LostShipsCity_town" && GetHour() < 2)
			{
				LAi_group_Delete("EnemyFight");
				sld = characterFromId("Casper_" + pchar.questTemp.LSC.Armo);
				sld.BreakTmplAndFight = true; //проверять на атаку
				sld.reactionOnFightModeOn = true; //проверять на вытаскивание оружия
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "reload", "reload55");
				LAi_ActorGoToLocator(sld, "reload", "reload65", "LSC_casperIsGone", -1.0);
				sld.talker = 11;
				LAi_Character_CanDialog(sld, pchar)
				pchar.questTemp.LSC.Armo.casperIdx = sld.index; //запомним индекс, пригодится на выходе
				//таймер на проверку, убит ли каспер
				pchar.quest.LSC_checkCasperDead.win_condition.l1               = "Location_Type";
				pchar.quest.LSC_checkCasperDead.win_condition.l1.location_type = "LSC_inside";
				pchar.quest.LSC_checkCasperDead.win_condition.l2            = "Timer";
				pchar.quest.LSC_checkCasperDead.win_condition.l2.date.hour  = 2;
				pchar.quest.LSC_checkCasperDead.win_condition.l2.date.day   = GetAddingDataDay(0, 0, 0);
				pchar.quest.LSC_checkCasperDead.win_condition.l2.date.month = GetAddingDataMonth(0, 0, 0);
				pchar.quest.LSC_checkCasperDead.win_condition.l2.date.year  = GetAddingDataYear(0, 0, 0);
				pchar.quest.LSC_checkCasperDead.function = "LSC_checkCasperDead";
				pchar.quest.LSC_checkCasperDead.casperIdx = sld.index;
			}
			else
			{
				pchar.questTemp.LSC.Armo = 11; //профукал каспера
			}
		}
	}
	//************** генератор "Продажный патруль" *********************************
	if(CheckAttribute(pchar, "questTemp.ReasonToFast"))
	{
		if(pchar.questTemp.ReasonToFast == "SpeakHorse") // не пришел в бухту
		{
			AddQuestRecord("ReasonToFast", "2");
			AddQuestUserData("ReasonToFast", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("ReasonToFast");
			pchar.questTemp.ReasonToFast.end = true;
		}
		if(pchar.questTemp.ReasonToFast == "MeetPatrolFail") // в бухту пришел не один или удачи не хватило
		{
			AddQuestRecord("ReasonToFast", "3");
			AddQuestUserData("ReasonToFast", "sSex", GetSexPhrase("ся","ась"));
			CloseQuestHeader("ReasonToFast");
			pchar.questTemp.ReasonToFast.end = true;
		}
		if(CheckAttribute(pchar, "questTemp.ReasonToFast.PatrolLocation"))
		{
			if(CheckAttribute(Locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)],"DisableEncounters"))
			{
				DeleteAttribute(Locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], "DisableEncounters");
			}
		}
		if(CheckAttribute(pchar, "questTemp.ReasonToFast.end"))
		{
			DeleteAttribute(pchar, "questTemp.ReasonToFast");
		}
	}
	//************** генератор "Эпидемия на вражеском корабле" **********************
	if(CheckAttribute(pchar,"GenQuest.ShipSituation.Epidemy"))
	{
		ShipSituation_CheckConsequence(sti(pchar.GenQuest.ShipSituation.Epidemy));
	}
	//************** поверка нпс-кэпов 5 и 20 числа каждого месяца *******************
	if (GetDataDay() == 5 || GetDataDay() == 20)
	{
		if (CheckAttribute(NullCharacter, "capitainBase"))
		{
			string sName;
			int capIndex, a;
			aref arCapBase, arBase;
    		makearef(arBase, NullCharacter.capitainBase);
    		int	Qty = GetAttributesNum(arBase);
    		for (a=0; a<Qty; a++)
    		{
    			arCapBase = GetAttributeN(arBase, a);
				sName = GetAttributeName(arCapBase); //Id кэпа
				capIndex = GetCharacterIndex(sName);
    			//---------- мертв ------------
    			if (capIndex == -1)
    			{
					//страховка. если квест еще открыт - закрываем его
					/*if (CheckActiveQuest(arCapBase.Tilte1))
					{
						CitizCapIsDead_CloseQuest(arCapBase, sName);
					}*/
					DeleteAttribute(arBase, sName);
					Qty --; //для корректной работы цикла при удалении записи в базе
					a--;
				}
				//---------- жив ------------
				else
				{
					if (GetNpcQuestPastDayParam(arCapBase, "checkTime") >= sti(arCapBase.checkTime))
					{
						//if (characters[capIndex].location == "none" && characters[capIndex].quest == "InMap")
						//{
							Cap_SetMapAgain(&characters[capIndex], arCapBase);
						//}
					}
				}
    		}
		}
	}
}

//снятие квеста, если энкаунтер кэпа исчез на карте
void CitizCapIsDead_CloseQuest(aref arCapBase, string capId)
{
	ref sld;
	string sTemp;
	//снимаем установленный таймер
	sTemp = "SecondTimer_" + capId;
	if (capId == "MushketCap") sTemp = "MushketTimer";
	if (capId == "Danielle")   sTemp = "DanielleTimer";
	if (capId == "BlackBeardNPC")   sTemp = "BlackBeardTimer";
	pchar.quest.(sTemp).over = "yes";
	//---------- нпс-квестодатель -------------
	int iTemp = GetCharacterIndex(arCapBase.questGiver);
	if (iTemp != -1)
	{
		//снимаем прерывание на смерть квестодателя
		ref npchar = &characters[iTemp];
		if (CheckAttribute(npchar, "quest.PortmansSeekShip") || CheckAttribute(npchar, "quest.PortmansJornal"))
		{
			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			DeleteAttribute(npchar, "quest.PortmansJornal");
			npchar.quest = ""; //освобождаем личный флаг квеста для портмана
		}
		else
		{
			sTemp = "SCQ_" + iTemp;
			pchar.quest.(sTemp).over = "yes";
			characters[iTemp].lifeDay = 0;
		}
	}
	string sTitle1 = arCapBase.Tilte1;
	string sTitle2 = arCapBase.Tilte2;
}

//переустанавливаем на карте живого, но потерянного кэпа
void Cap_SetMapAgain(ref sld, aref arCapBase)
{
	//в морскую группу кэпа
	string sGroup = "SeekCapShip_" + sld.index;
	group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation));
	switch (arCapBase.quest)
	{
	case "mushket":
		if (sld.cityShore == sld.quest.targetShore)
		{
			sld.quest.targetShore = SelectAnyColony(sld.cityShore);
		}
		Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, sti(arCapBase.checkTime)-5);
		break
	case "citizen":
		if (sld.city == sld.quest.targetCity)
		{
			sld.quest.targetCity = SelectAnyColony(sld.city);
		}
		Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, sti(arCapBase.checkTime)-5);
		break
	case "robber":
		if (sld.city == sld.quest.targetCity)
		{
			sld.quest.targetCity = SelectAnyColony(sld.city);
		}
		Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, sti(arCapBase.checkTime)-5);
		break
	case "jornal":
		if (sld.quest.baseShore == sld.quest.targetCity)
		{
			sld.quest.targetCity = SelectAnyColony(sld.quest.baseShore);
		}
		Map_CreateTrader(sld.quest.baseShore, sld.quest.targetCity, sld.id, sti(arCapBase.checkTime)-5);
		break
	case "Danielle":
		if (sld.cityShore == sld.quest.targetCity)
		{
			sld.quest.targetCity = SelectAnyColony(sld.cityShore);
		}
		Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, sti(arCapBase.checkTime)-5);
		break
	case "BlackBeard":
		if (sld.cityShore == sld.quest.targetCity)
		{
			sld.quest.targetCity = GetRandomPirateCity();
			sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
		}
		Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, sti(arCapBase.checkTime)-5);
		break
	}
	//меняем сроки проверки по Id кэпа в базе нпс-кэпов
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = iTemp + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

//Иниты Остина, убийцы в городах
void BerglarsInit()
{
	// Бандиты сразу экипировывуют оружие при выдаче (Это из-за новой логики экипировки.), поэтому теперь оно выдается и экипировывуется прямо в диалоге Бергларов.
	ref sld;
	pchar.questTemp.tugs.berglarState = 1; //счетчик
	//============> грабитель в Сент-Джонсе
	pchar.questTemp.tugs.berglarSentJons = "SentJons_TownCave"; //указание где забивать стрелу
	pchar.questTemp.tugs.berglarSentJons.hp = 160; //сколько HP
	pchar.questTemp.tugs.berglarSentJons.locator = "basement1"; //выходной локатор
	sld = GetCharacter(NPC_GenerateCharacter("BerglarSentJons", "citiz_12", "man", "spy", 22, ENGLAND, -1, false));
	sld.name 	= "Альберт";
	sld.lastname = "Грин";
	sld.rank = 25;
	sld.city = "SentJons";
	sld.location	= "SentJons_town";
	sld.location.group = "goto";
	sld.location.locator = "goto4";
	sld.dialog.filename   = "Quest\Berglars.c";
	sld.greeting = "pirat_quest";
	TakeNItems(sld, "jewelry1", 30+rand(10));
	TakeNItems(sld, "bullet", 51);
	TakeNItems(sld, "GunPowder", 51);
	sld.money = 10460;
	sld.talker = 7; //начать диалог
	SetSelfSkill(sld, 10, 100, 70, 100, 70);
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "HardHitter");
	sld.SuperShooter  = true;
	LAi_SetHP(sld, 1.0, 1.0);
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	//=============> грабитель на Мартинике
	pchar.questTemp.tugs.berglarFortFrance = "FortFrance_Dungeon"; //указание где забивать стрелу
	pchar.questTemp.tugs.berglarFortFrance.hp = 180; //сколько HP
	pchar.questTemp.tugs.berglarFortFrance.locator = "basement1"; //выходной локатор
	sld = GetCharacter(NPC_GenerateCharacter("BerglarFortFrance", "citiz_11", "man", "man", 23, FRANCE, -1, false));
	sld.name 	= "Гаэтано";
	sld.lastname = "Лемье";
	sld.rank = 25;
	sld.city = "FortFrance";
	sld.location	= "FortFrance_town";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	sld.dialog.filename   = "Quest\Berglars.c";
	sld.greeting = "pirat_quest";
	TakeNItems(sld, "bullet", 51);
	TakeNItems(sld, "GunPowder", 51);
	TakeNItems(sld, "jewelry2", 25+rand(10));
	sld.money = 12670;
	sld.talker = 7; //начать диалог
	SetSelfSkill(sld, 10, 100, 70, 50, 60);
	SetCharacterPerk(sld, "BasicDefense");
	sld.SuperShooter  = true;
	LAi_SetHP(sld, 1.0, 1.0);
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	//============> грабитель в Мариго
	pchar.questTemp.tugs.berglarMarigo = "Marigo_Cave"; //указание где забивать стрелу
	pchar.questTemp.tugs.berglarMarigo.hp = 200; //сколько HP
	pchar.questTemp.tugs.berglarMarigo.locator = "gate_back"; //выходной локатор
	sld = GetCharacter(NPC_GenerateCharacter("BerglarMarigo", "citiz_1", "man", "man", 21, HOLLAND, -1, false));
	sld.name 	= "Эстебан";
	sld.lastname = "Морэ";
	sld.rank = 25;
	sld.city = "Marigo";
	sld.location	= "Marigo_town";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	sld.dialog.filename   = "Quest\Berglars.c";
	sld.greeting = "pirat_quest";
/* 	GiveItem2Character(sld, "pistol2");
	GiveItem2Character(sld, GetGeneratedItem("blade16")); */
	TakeNItems(sld, "jewelry3", 25+rand(10));
	TakeNItems(sld, "bullet", 51);
	TakeNItems(sld, "GunPowder", 51);
	sld.money = 15480;
	sld.talker = 7; //начать диалог
	SetSelfSkill(sld, 60, 10, 100, 100, 40);
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "HardHitter");
	sld.SuperShooter  = true;
	LAi_SetHP(sld, 1.0, 1.0);
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
	//============> грабитель в Панаме
	pchar.questTemp.tugs.berglarPanama = "Panama_Cave"; //указание где забивать стрелу
	pchar.questTemp.tugs.berglarPanama.hp = 200; //сколько HP
	pchar.questTemp.tugs.berglarPanama.locator = "gate_back"; //выходной локатор
	sld = GetCharacter(NPC_GenerateCharacter("BerglarPanama", "citiz_4", "man", "man", 27, SPAIN, -1, false));
	sld.name 	= "Хуан";
	sld.lastname = "Карлос";
	sld.rank = 27;
	sld.city = "Panama";
	sld.location	= "Panama_town";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	sld.dialog.filename   = "Quest\Berglars.c";
	sld.greeting = "pirat_quest";
	TakeNItems(sld, "jewelry2", 30+rand(5));
	TakeNItems(sld, "bullet", 51);
	TakeNItems(sld, "GunPowder", 51);
	sld.money = 15180;
	sld.talker = 8; //начать диалог
	SetSelfSkill(sld, 100, 10, 50, 50, 70);
	SetCharacterPerk(sld, "AdvancedDefense");
	sld.SuperShooter  = true;
	LAi_SetHP(sld, 1.0, 1.0);
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//============> грабитель в Картахене
	pchar.questTemp.tugs.berglarCartahena = "Cartahena_Cave"; //указание где забивать стрелу
	pchar.questTemp.tugs.berglarCartahena.hp = 170; //сколько HP
	pchar.questTemp.tugs.berglarCartahena.locator = "gate_back"; //выходной локатор
	sld = GetCharacter(NPC_GenerateCharacter("BerglarCartahena", "citiz_7", "man", "man", 22, SPAIN, -1, false));
	sld.name 	= "Мигель";
	sld.lastname = "Карлитос";
	sld.rank = 22;
	sld.city = "Cartahena";
	sld.location	= "Cartahena_town";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	sld.dialog.filename   = "Quest\Berglars.c";
	sld.greeting = "pirat_quest";
	TakeNItems(sld, "jewelry1", 40+rand(10));
	TakeNItems(sld, "bullet", 51);
	TakeNItems(sld, "GunPowder", 51);
	sld.money = 15980;
	sld.talker = 7; //начать диалог
	SetSelfSkill(sld, 100, 10, 70, 100, 50);
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "CriticalHit");
	sld.SuperShooter  = true;
	LAi_SetHP(sld, 1.0, 1.0);
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//============> грабитель в Санта Каталине
	pchar.questTemp.tugs.berglarSantaCatalina = "SantaCatalina_Cave"; //указание где забивать стрелу
	pchar.questTemp.tugs.berglarSantaCatalina.hp = 230; //сколько HP
	pchar.questTemp.tugs.berglarSantaCatalina.locator = "gate_back"; //выходной локатор
	sld = GetCharacter(NPC_GenerateCharacter("BerglarSantaCatalina", "citiz_9", "man", "man", 25, SPAIN, -1, false));
	sld.name 	= "Лоренсо";
	sld.lastname = "Сантино";
	sld.rank = 25;
	sld.city = "SantaCatalina";
	sld.location	= "SantaCatalina_town";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	sld.dialog.filename   = "Quest\Berglars.c";
	sld.greeting = "pirat_quest";
	TakeNItems(sld, "jewelry3", 25+rand(10));
	TakeNItems(sld, "bullet", 51);
	TakeNItems(sld, "GunPowder", 51);
	sld.money = 16450;
	sld.talker = 7; //начать диалог
	SetSelfSkill(sld, 10, 10, 100, 50, 80);
	SetCharacterPerk(sld, "CriticalHit");
	sld.SuperShooter  = true;
	LAi_SetHP(sld, 1.0, 1.0);
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
}

void QuestionsInit()
{
	ref sld;
	//============> база вопросов, специально делаю в коде, не в ини. шоб не ковыряли.
	NullCharacter.questions = 73; //кол-во вопросов (нумерация с нуля, соотв. последней записи структуры !!!)
	NullCharacter.questions.q0 = "Как называется группа тросов, закрепленных в просверленном переднем крае марсовой площадки и проходящих через специальный блок на штаге? Подсказка: нужна для того, чтобы избежать перетирания марселей о штаги и зацепления за марсы.";
	NullCharacter.questions.a0 = "анапуть";
	NullCharacter.questions.q1 = "Назовите небольшой деревянный бочонок для запасов пресной воды?";
	NullCharacter.questions.a1 = "анкерок";
	NullCharacter.questions.q2 = "Как называется деревянная цилиндрическая колодка со щеткой, насаженная на древко, служащая для очистки канала орудия от порохового нагара?";
	NullCharacter.questions.a2 = "банник";
	NullCharacter.questions.q3 = "Как называется усиленный ряд наружной обшивки корпуса судна над ватерлинией?";
	NullCharacter.questions.a3 = "бархоут";
	NullCharacter.questions.q4 = "Как называется кусок троса, обшитый кожей, с помощью которого рей или гафель удерживается в обхват у мачты или стеньги?";
	NullCharacter.questions.a4 = "бейфут";
	NullCharacter.questions.q5 = "Как называется перевязка двух тросов тонким тросом или линем?";
	NullCharacter.questions.a5 = "бензель";
	NullCharacter.questions.q6 = "Как называется поперечная переборка в носовой части парусных судов.";
	NullCharacter.questions.a6 = "бикгед";
	NullCharacter.questions.q7 = "Как называются поперечные связи судна, служащие для поддержания палуб, соединяющие противоположные бортовые ветви шпангоутов и придающие судну поперечную прочность?";
	NullCharacter.questions.a7 = "бимсы";
	NullCharacter.questions.q8 = "Как назывался античный гребной военный корабль с двумя рядами весел?";
	NullCharacter.questions.a8 = "бирема";
	NullCharacter.questions.q9 = "Как называется деревянная тумба на палубе корабля для крепления тросов?";
	NullCharacter.questions.a9 = "битенг";
	NullCharacter.questions.q10 = "Как назыавется небольшая мачта на бушприте, несущая рей с прямым парусом?";
	NullCharacter.questions.a10 = "блинда-стеньга";
	NullCharacter.questions.q11 = "Назовите парус, который ставят под бушпритом.";
	NullCharacter.questions.a11 = "блинд";
	NullCharacter.questions.q12 = "Как называются горизонтальные рангоутные деревья, имеющие крепление только на одном конце? Могу подсказать, что они служат для вынесения паруса за борт, разноса такелажа и подвешивания шлюпок.";
	NullCharacter.questions.a12 = "боканцы";
	NullCharacter.questions.q13 = "Назовите рангоутное дерево, служащее продолжением стеньги.";
	NullCharacter.questions.a13 = "брам-стеньга";
	NullCharacter.questions.q14 = "Как называется снасть бегучего такелажа, служащая для поворота рея в горизонтальной плоскости?";
	NullCharacter.questions.a14 = "брас";
	NullCharacter.questions.q15 = "Назовите устройство с горизонтальным валом для подъема якорей и грузов.";
	NullCharacter.questions.a15 = "брашпиль";
	NullCharacter.questions.q16 = "Как называется мощный трос, служащий для удержания корабельного орудия при откате?";
	NullCharacter.questions.a16 = "брюк";
	NullCharacter.questions.q17 = "Назовите дополнительный парус, крепящийся шнуровкой непосредственно к основному.";
	NullCharacter.questions.a17 = "бонет";
	NullCharacter.questions.q18 = "Как называется трос, который служит для оттягивания к носу боковой шкаторины прямого паруса при ходе судна в бейдевинд?";
	NullCharacter.questions.a18 = "булинь";
	NullCharacter.questions.q19 = "Назовите третий снизу прямой парус на мачте, ставящийся между брам-реем и марса-реем.";
	NullCharacter.questions.a19 = "брамсель";
	NullCharacter.questions.q20 = "Как называются мощные тросы стоячего такелажа, служащие для удержания мачт с боков?";
	NullCharacter.questions.a20 = "ванты";
	NullCharacter.questions.q21 = "Назовите тросовое крепление бушприта с форштевнем.";
	NullCharacter.questions.a21 = "ватер-вулинг";
	NullCharacter.questions.q22 = "Назовите вспомогательный судовой якорь, служащий для снятия судна с мели.";
	NullCharacter.questions.a22 = "верп";
	NullCharacter.questions.q23 = "Как называется округлый прилив на казенной части орудия?";
	NullCharacter.questions.a23 = "винград";
	NullCharacter.questions.q24 = "Как называются тонкие тросы, ввязанные поперек вант и служащие ступенями при подъеме по вантам на мачты и стеньги?";
	NullCharacter.questions.a24 = "выбленки";
	NullCharacter.questions.q25 = "Назовите металлический крюк, прикрепленный к концу троса, служащий для подъема шлюпок, груза и многого другого.";
	NullCharacter.questions.a25 = "гак";
	NullCharacter.questions.q26 = "Как называется плоская часть кормовой оконечности судна, на которой устанавливаются кормовые фонари?";
	NullCharacter.questions.a26 = "гакаборт";
	NullCharacter.questions.q27 = "Назовите снасть бегучего такелажа для оттягивания шкотового угла паруса к носу.";
	NullCharacter.questions.a27 = "галс";
	NullCharacter.questions.q28 = "Назовите наклонное рангоутное дерево для крепления верхней шкаторины триселя.";
	NullCharacter.questions.a28 = "гафель";
	NullCharacter.questions.q29 = "Назовите меру длины, равную одной десятой морской мили.";
	NullCharacter.questions.a29 = "кабельтов";
	NullCharacter.questions.q30 = "Как называется полотняный мешочек с зарядом пороха?";
	NullCharacter.questions.a30 = "картуз";
	NullCharacter.questions.q31 = "Как называется приподнятая часть верхней палубы в кормовой части судна?";
	NullCharacter.questions.a31 = "квартердек";
	NullCharacter.questions.q32 = "Назовите конусообразный кусок твердого дерева, вставляемого в узел, чтобы последний не затягивался.";
	NullCharacter.questions.a32 = "клевант";
	NullCharacter.questions.q33 = "Назовите косой треугольный парус, прикрепленный к снасти, идущей от мачты к бушприту.";
	NullCharacter.questions.a33 = "кливер";
	NullCharacter.questions.q34 = "Как называется отверстие в борту судна для якорного каната?";
	NullCharacter.questions.a34 = "клюз";
	NullCharacter.questions.q35 = "Как называется марсель бизань-мачты?";
	NullCharacter.questions.a35 = "крюйсель";
	NullCharacter.questions.q36 = "Как называется дополнительный парус в форме трапеции, который ставят с внешней стороны прямого паруса?";
	NullCharacter.questions.a36 = "лисель";
	NullCharacter.questions.q37 = "Назовите мягкий трос, которым обшивают кромки парусов.";
	NullCharacter.questions.a37 = "ликтрос";
	NullCharacter.questions.q38 = "Как называется груз, служащий для измерения глубины?";
	NullCharacter.questions.a38 = "лот";
	NullCharacter.questions.q39 = "Назовите лицо, измеряющее лотом глубины, и потому знающее характер побережья.";
	NullCharacter.questions.a39 = "лоцман";
	NullCharacter.questions.q40 = "Как называется круглое, обметанное отверстие в парусе?";
	NullCharacter.questions.a40 = "люверс";
	NullCharacter.questions.q41 = "Назовите второй снизу прямой парус на мачте, ставящийся между марса-реем и нижним реем.";
	NullCharacter.questions.a41 = "марсель";
	NullCharacter.questions.q42 = "Как называется деревянный гвоздь?";
	NullCharacter.questions.a42 = "нагель";
	NullCharacter.questions.q43 = "Как называется деревянный шкафчик, где хранятся компас, лампа и песочные часы?";
	NullCharacter.questions.a43 = "нактоуз";
	NullCharacter.questions.q44 = "Назовите тросы, на которые встают матросы во время работы на реях.";
	NullCharacter.questions.a44 = "перты";
	NullCharacter.questions.q45 = "Назовите самый верхний брус на фальшборте палубных судов.";
	NullCharacter.questions.a45 = "планшир";
	NullCharacter.questions.q46 = "Как называется горизонтальный ряд завязок, продетых сквозь парус, которые позволяют уменьшить его площадь?";
	NullCharacter.questions.a46 = "рифы";
	NullCharacter.questions.q47 = "Назовите кольцо якоря, за которое крепится якорный канат.";
	NullCharacter.questions.a47 = "рым";
	NullCharacter.questions.q48 = "Как называется рама, служащая для соединения составных частей мачты?";
	NullCharacter.questions.a48 = "салинг";
	NullCharacter.questions.q49 = "Назовите гнездо, в которое вставляется мачта своим шпором.";
	NullCharacter.questions.a49 = "степс";
	NullCharacter.questions.q50 = "Как называется рангоутное дерево, служащее продолжением нижней мачты?";
	NullCharacter.questions.a50 = "стеньга";
	NullCharacter.questions.q51 = "Назовите косой парус треугольной или трапециевидной формы, ставящийся на штаге.";
	NullCharacter.questions.a51 = "стаксель";
	NullCharacter.questions.q52 = "Как называется корабельная мазь для защиты днища судна от древоточцев?";
	NullCharacter.questions.a52 = "тир";
	NullCharacter.questions.q53 = "Назовите косой трапециевидный парус, верхней шкаториной шнурующийся к гафелю, а нижней растягивающийся по гику.";
	NullCharacter.questions.a53 = "трисель";
	NullCharacter.questions.q54 = "Как назывался боевой гребной корабль в Древней Греции с тремя рядами весел, главным оружием которого был таран?";
	NullCharacter.questions.a54 = "триера";
	NullCharacter.questions.q55 = "Как назывался боевой гребной корабль в Древнем Риме с тремя рядами весел?";
	NullCharacter.questions.a55 = "трирема";
	NullCharacter.questions.q56 = "Как называется рангоутное дерево, служащее продолжением бушприту?";
	NullCharacter.questions.a56 = "утлегарь";
	NullCharacter.questions.q57 = "Назовите снасть, служащая для подъема некоторых рей, парусов, сигнальных флагов и многого другого.";
	NullCharacter.questions.a57 = "фал";
	NullCharacter.questions.q58 = "Как называется продолжение борта выше открытой верхней палубы?";
	NullCharacter.questions.a58 = "фальшборт";
	NullCharacter.questions.q59 = "Как называются цилиндрические приливы, с помощью которых орудию можно установить нужный прицел по высоте?";
	NullCharacter.questions.a59 = "цапфы";
	NullCharacter.questions.q60 = "Как называется верхняя палуба в кормовой части парусного судна, где находятся вахтенные офицеры и устанавливаются компасы?";
	NullCharacter.questions.a60 = "шканцы";
	NullCharacter.questions.q61 = "Как называются широкие доски, уложенные горизонтально вдоль бортов для прохода с бака на шканцы?";
	NullCharacter.questions.a61 = "шкафут";
	NullCharacter.questions.q62 = "Как называется снасть, оттягивающая нижний угол паруса в направлении кормы судна и удерживающая парус в желаемом положении?";
	NullCharacter.questions.a62 = "шкот";
	NullCharacter.questions.q63 = "Как называется поперечная связь, образующая ребро корпуса судна?";
	NullCharacter.questions.a63 = "шпангоут";
	NullCharacter.questions.q64 = "Как называется петля троса, образующаяся при обнесении его вокруг какого-либо предмета?";
	NullCharacter.questions.a64 = "шлаг";
	NullCharacter.questions.q65 = "Как называется большая цилиндрическая ложка для разрядки орудия, то есть для вытаскивания ядра и картуза?";
	NullCharacter.questions.a65 = "шуфла";
	NullCharacter.questions.q66 = "Как называется деревянная соединительная обойма с двумя отверстиями, служащая для соединения составных частей мачты?";
	NullCharacter.questions.a66 = "эзельгофт";
	NullCharacter.questions.q67 = "Назовите круглый деревянный блок без шкива с тремя сквозными отверстиями для натяжения штагов и вант.";
	NullCharacter.questions.a67 = "юферс";
	NullCharacter.questions.q68 = "Назовите основной продукт торгового экспорта в Карибском море в начале-середине этого века.";
	NullCharacter.questions.a68 = "сахар";
	NullCharacter.questions.q69 = "Назовите основной продукт торгового импорта в Карибском море в начале-середине этого века.";
	NullCharacter.questions.a69 = "рабы";
	NullCharacter.questions.q70 = "Назовите полное имя первого голландского мореплавателя, совершившего кругосветное плавание?";
	NullCharacter.questions.a70 = "оливер ван норт";
	NullCharacter.questions.q71 = "Как называлась первая фактория Голландской Вест-Индской Компании в Америке? Была основана в 1626.";
	NullCharacter.questions.a71 = "нью амстердам";
	NullCharacter.questions.q72 = "Какой английский поэт, пират, морской капитан, колонизатор Вирджинии и поклонник королевы Елизаветы I был казнён(через отсечение головы) в 1618 году?";
	NullCharacter.questions.a72 = "сэр уолтер рейли";
	NullCharacter.questions.q73 = "Кто первым из пиратов стал изображать на своем флаге череп с костями?";
	NullCharacter.questions.a73 = "эммануэль винн";
	//============> спрашиватель в Тринидаде
	sld = GetCharacter(NPC_GenerateCharacter("QuetionsPortSpein", "citiz_"+(rand(11)+1), "man", "man", 5, ENGLAND, -1, false));
	sld.rank = 5;
	sld.city = "PortSpein";
	sld.location	= "PortSpein_town";
	sld.location.group = "goto";
	sld.location.locator = "goto1";
	sld.dialog.filename   = "Quest\Questions.c";
	sld.dialog.currentnode   = "PortSpein";
	sld.greeting = "cit_common";
	sld.talker = 4; //начать диалог
	sld.quest.numQuestion = SelectQuestions(); //номер вопроса
	SetSelfSkill(sld, 10, 10, 10, 10, 10);
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	//============> спрашивательница в Виллемстде
	sld = GetCharacter(NPC_GenerateCharacter("QuetionsVillemstad", "girl_"+(rand(7)+1), "woman", "towngirl", 5, HOLLAND, -1, false));
	sld.rank = 5;
	sld.city = "Villemstad";
	sld.location	= "Villemstad_town";
	sld.location.group = "goto";
	sld.location.locator = "goto1";
	sld.dialog.filename   = "Quest\Questions.c";
	sld.dialog.currentnode   = "Villemstad";
	sld.greeting = "Gr_Woman_Citizen";
	sld.talker = 3; //начать диалог
	sld.quest.numQuestion = SelectQuestions(); //номер вопроса
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
	//============> спрашивательница в Порт-о-Принсе
	sld = GetCharacter(NPC_GenerateCharacter("QuetionsPortPax", "girl_"+(rand(7)+1), "woman", "towngirl", 5, FRANCE, -1, false));
	sld.rank = 5;
	sld.city = "PortPax";
	sld.location	= "PortPax_town";
	sld.location.group = "goto";
	sld.location.locator = "goto1";
	sld.dialog.filename   = "Quest\Questions.c";
	sld.dialog.currentnode   = "PortPax";
	sld.greeting = "Gr_Woman_Citizen";
	sld.talker = 6; //начать диалог
	sld.quest.numQuestion = SelectQuestions(); //номер вопроса
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	//============> спрашиватель в Сан-Хуане
	sld = GetCharacter(NPC_GenerateCharacter("QuetionsSanJuan", "citiz_"+(rand(11)+1), "man", "man", 5, SPAIN, -1, false));
	sld.rank = 5;
	sld.city = "SanJuan";
	sld.location	= "SanJuan_town";
	sld.location.group = "goto";
	sld.location.locator = "goto1";
	sld.dialog.filename   = "Quest\Questions.c";
	sld.dialog.currentnode   = "SanJuan";
	sld.greeting = "cit_common";
	sld.talker = 6; //начать диалог
	sld.quest.numQuestion = SelectQuestions(); //номер вопроса
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//============> спрашиватель в Кумане
	sld = GetCharacter(NPC_GenerateCharacter("QuetionsCumana", "citiz_"+(rand(11)+1), "man", "man", 5, SPAIN, -1, false));
	sld.rank = 5;
	sld.city = "Cumana";
	sld.location	= "Cumana_town";
	sld.location.group = "goto";
	sld.location.locator = "goto10";
	sld.dialog.filename   = "Quest\Questions.c";
	sld.dialog.currentnode   = "Cumana";
	sld.greeting = "cit_common";
	sld.talker = 6; //начать диалог
	sld.quest.numQuestion = SelectQuestions(); //номер вопроса
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//============> спрашиватель в Порт Рояле
	sld = GetCharacter(NPC_GenerateCharacter("QuetionsPortRoyal", "girl_"+(rand(7)+1), "woman", "towngirl", 5, ENGLAND, -1, false));
	sld.rank = 5;
	sld.city = "PortRoyal";
	sld.location	= "PortRoyal_town";
	sld.location.group = "goto";
	sld.location.locator = "goto10";
	sld.dialog.filename   = "Quest\Questions.c";
	sld.dialog.currentnode   = "PortRoyal";
	sld.greeting = "Gr_Woman_Citizen";
	sld.talker = 3; //начать диалог
	sld.quest.numQuestion = SelectQuestions(); //номер вопроса
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	//============> спрашиватель в Сантьяго
	sld = GetCharacter(NPC_GenerateCharacter("QuetionsSantiago", "citiz_"+(rand(11)+1), "man", "man", 5, SPAIN, -1, false));
	sld.rank = 5;
	sld.city = "Santiago";
	sld.location	= "Santiago_town";
	sld.location.group = "goto";
	sld.location.locator = "goto10";
	sld.dialog.filename   = "Quest\Questions.c";
	sld.dialog.currentnode   = "Santiago";
	sld.greeting = "cit_common";
	sld.talker = 5; //начать диалог
	sld.quest.numQuestion = SelectQuestions(); //номер вопроса
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");

}
// ==> обработка базы вопросов, относится к методу выше
int SelectQuestions()
{
	bool bOk = true;
	int iTemp;
	string sTemp;
	while (bOk)
	{
		iTemp = rand(sti(NullCharacter.questions));
		sTemp = "m" + iTemp;
		if (!CheckAttribute(NullCharacter, "questions" + sTemp))
		{
			NullCharacter.questions.(sTemp) = true;
			break;
		}
	}
	return iTemp;
}
// -- нищие --
void PoormansInit()
{
	ref sld;
	//нищий в Сент-Джонсе
	sld = GetCharacter(NPC_GenerateCharacter("SentJons_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, ENGLAND, -1, false));
	sld.city = "SentJons";
	sld.location	= "SentJons_town";
	sld.location.group = "goto";
	sld.location.locator = "goto6";
	sld.forStay.locator = "goto6"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto15";
	sld.forSit.locator1 = "goto17"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto4";
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	//нищий в Бриджтауне
	sld = GetCharacter(NPC_GenerateCharacter("Bridgetown_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, ENGLAND, -1, false));
	sld.city = "Bridgetown";
	sld.location	= "Bridgetown_town";
	sld.location.group = "goto";
	sld.location.locator = "goto12";
	sld.forStay.locator = "goto12"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto9";
	sld.forSit.locator1 = "goto19"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto4";
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	//нищий в Белизе
	sld = GetCharacter(NPC_GenerateCharacter("Beliz_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false));
	sld.city = "Beliz";
	sld.location	= "Beliz_town";
	sld.location.group = "goto";
	sld.location.locator = "goto9";
	sld.forStay.locator = "goto9"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto7";
	sld.forSit.locator1 = "goto19"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto3";
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//нищий в Каракасе
	sld = GetCharacter(NPC_GenerateCharacter("Caracas_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false));
	sld.city = "Caracas";
	sld.location	= "Caracas_town";
	sld.location.group = "goto";
	sld.location.locator = "goto20";
	sld.forStay.locator = "goto20"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto1";
	sld.forSit.locator1 = "goto21"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto23";
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//нищий в Картахене
	sld = GetCharacter(NPC_GenerateCharacter("Cartahena_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false));
	sld.city = "Cartahena";
	sld.location	= "Cartahena_town";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	sld.forStay.locator = "goto5"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto18";
	sld.forSit.locator1 = "goto14"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto6";
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//нищий в Кумане
	sld = GetCharacter(NPC_GenerateCharacter("Cumana_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false));
	sld.city = "Cumana";
	sld.location	= "Cumana_town";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	sld.forStay.locator = "goto5"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto13";
	sld.forSit.locator1 = "goto15"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto3";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//нищий в Кюрасао
	/*sld = GetCharacter(NPC_GenerateCharacter("Villemstad_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, HOLLAND, -1, false));
	sld.city = "Villemstad";
	sld.location	= "Villemstad_town";
	sld.location.group = "goto";
	sld.location.locator = "goto24";
	sld.forStay.locator = "goto24"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto23";
	sld.forSit.locator1 = "goto7"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto8";
	LAi_SetLoginTime(sld, 9.0, 22.0);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");*/
	//нищий в Бас-Тере, Гваделупа
	sld = GetCharacter(NPC_GenerateCharacter("BasTer_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, FRANCE, -1, false));
	sld.city = "BasTer";
	sld.location	= "BasTer_town";
	sld.location.group = "goto";
	sld.location.locator = "goto18";
	sld.forStay.locator = "goto18"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto24";
	sld.forSit.locator1 = "goto16"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto17";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	//нищий в Гаване
	sld = GetCharacter(NPC_GenerateCharacter("Havana_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false));
	sld.city = "Havana";
	sld.location	= "Havana_town";
	sld.location.group = "goto";
	sld.location.locator = "goto12";
	sld.forStay.locator = "goto12"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto16";
	sld.forSit.locator1 = "goto22"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto23";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//нищий в Порт Рояле
	sld = GetCharacter(NPC_GenerateCharacter("PortRoyal_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, ENGLAND, -1, false));
	sld.city = "PortRoyal";
	sld.location	= "PortRoyal_town";
	sld.location.group = "goto";
	sld.location.locator = "goto15";
	sld.forStay.locator = "goto15"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto16";
	sld.forSit.locator1 = "goto28"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto7";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	//нищий в Форт-де-Франсе, Мартиника
	sld = GetCharacter(NPC_GenerateCharacter("FortFrance_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, FRANCE, -1, false));
	sld.city = "FortFrance";
	sld.location	= "FortFrance_town";
	sld.location.group = "goto";
	sld.location.locator = "goto4";
	sld.forStay.locator = "goto4"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto14";
	sld.forSit.locator1 = "goto10"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto1";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	//нищий на Невисе
	sld = GetCharacter(NPC_GenerateCharacter("Charles_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, ENGLAND, -1, false));
	sld.city = "Charles";
	sld.location	= "Charles_town";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	sld.forStay.locator = "goto5"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto19";
	sld.forSit.locator1 = "goto13"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto3";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	//нищий в Порто Белло
	sld = GetCharacter(NPC_GenerateCharacter("PortoBello_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false));
	sld.city = "PortoBello";
	sld.location	= "PortoBello_town";
	sld.location.group = "goto";
	sld.location.locator = "goto15";
	sld.forStay.locator = "goto15"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto3";
	sld.forSit.locator1 = "goto25"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto12";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//нищий в Порт-о-Принс, Эспаньола
	sld = GetCharacter(NPC_GenerateCharacter("PortPax_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, FRANCE, -1, false));
	sld.city = "PortPax";
	sld.location	= "PortPax_town";
	sld.location.group = "goto";
	sld.location.locator = "goto14";
	sld.forStay.locator = "goto14"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto25";
	sld.forSit.locator1 = "goto13"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto11";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	//нищий в Сантьяго
	sld = GetCharacter(NPC_GenerateCharacter("Santiago_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false));
	sld.city = "Santiago";
	sld.location	= "Santiago_town";
	sld.location.group = "goto";
	sld.location.locator = "goto6";
	sld.forStay.locator = "goto6"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto3";
	sld.forSit.locator1 = "goto15"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto28";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//нищий в Мариго, Сан Мартин
	sld = GetCharacter(NPC_GenerateCharacter("Marigo_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, HOLLAND, -1, false));
	sld.city = "Marigo";
	sld.location	= "Marigo_town";
	sld.location.group = "goto";
	sld.location.locator = "goto16";
	sld.forStay.locator = "goto16"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto1";
	sld.forSit.locator1 = "goto4"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto9";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
	//нищий в Тортуге
	sld = GetCharacter(NPC_GenerateCharacter("Tortuga_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, FRANCE, -1, false));
	sld.city = "Tortuga";
	sld.location	= "Tortuga_town";
	sld.location.group = "goto";
	sld.location.locator = "goto23";
	sld.forStay.locator = "goto23"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto16";
	sld.forSit.locator1 = "goto18"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto1";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	//нищий в Порт Спейне, Тринидад
	sld = GetCharacter(NPC_GenerateCharacter("PortSpein_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, ENGLAND, -1, false));
	sld.city = "PortSpein";
	sld.location	= "PortSpein_town";
	sld.location.group = "goto";
	sld.location.locator = "goto6";
	sld.forStay.locator = "goto6"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto9";
	sld.forSit.locator1 = "goto14"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto1";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	//заказчик нищих
	if (MOD_SKILL_ENEMY_RATE == 10 && bHardAnimations) sld = GetCharacter(NPC_GenerateCharacter("PoorKillSponsor", "smuggler_boss", "man", "spy", 30, PIRATE, -1, false)); // LEO: Страдать превозмогаторам 07.12.2021
	else sld = GetCharacter(NPC_GenerateCharacter("PoorKillSponsor", "smuggler_boss", "man", "man_fast", 30, PIRATE, -1, false));
	sld.name = "Оливер";
	sld.lastname = "Траст";
	sld.talker = 8; //начать диалог
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "Begin_PoorKill";
	sld.greeting = "Gr_OliverTrast";
	LAi_SetCitizenType(sld);
	LAi_SetImmortal(sld, true);
	LAi_SetHP(sld, 100.0, 100.0);
	sld.greeting = "Gr_OliverTrast";
	if (bHardBoss) sld.AlwaysReload = true;//перезарядка независимо от Дозарядки
	//несчастный мушкетер
	sld = GetCharacter(NPC_GenerateCharacter("OffMushketer", "MusketeerEnglish_1", "man", "man", 25, ENGLAND, -1, false));
	sld.name = "Хемфри";
	sld.lastname = "Дуглас";
	sld.location	= "PortSpein_houseH3";
	sld.location.group = "sit";
	sld.location.locator = "sit1";
	sld.Dialog.Filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "OffMushketer";
	sld.HalfImmortal = true;  // Контузия
	sld.HeroModel = "MusketeerEnglish_1,MusketeerEnglish_1_1,MusketeerEnglish_1_2,MusketeerEnglish_1_3,MusketeerEnglish_1_4,MusketeerEnglish_1_5";
	SetSelfSkill(sld, 80, 10, 2, 100, 80);
	SetShipSkill(sld, 5, 5, 2, 10, 5, 20, 10, 10, 70);
	SetSPECIAL(sld, 7, 4, 9, 3, 8, 7, 9);
	LAi_SetSitType(sld);
	sld.greeting = "cit_common";
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "HPPlus");
	//SetCharacterPerk(sld, "Medic");
	SetCharacterPerk(sld, "GunProfessional");
	DeleteAttribute(sld, "Items");
	GiveItem2Character(sld, "unarmed");
	EquipCharacterbyItem(sld, "unarmed");
	sld.HoldEquip = true; //удерживать оружие при обмене предметами
}

//=============== капитан Шарп ====================
string Sharp_choiceAction()
{
	string sBack;
	ref sld;
	//удалим Шарпа с карты, если он плывет еще где-то
	Map_ReleaseQuestEncounter("Sharp");
	group_DeleteGroup("Sharp_Group");
	if (rand(3) != 2 && sti(pchar.questTemp.Sharp.count) < 5)
	{	//еще динамим, отправляем ГГ в другой город
		string sCity = pchar.questTemp.Sharp.City; //предыдущая цель, запомним для СЖ
		pchar.questTemp.Sharp.City.rumour = true; //флаг дать слух в городе
		pchar.questTemp.Sharp.City = GetSharpCity(); //новый город
		sBack = GetSharpRumour_toCityTarget();
		pchar.questTemp.Sharp.count = sti(pchar.questTemp.Sharp.count) + 1; //счетчик
		AddQuestRecord("SharpPearl", "2");
		AddQuestUserData("SharpPearl", "sOldTarget", XI_ConvertString("Colony" + sCity + "Dat"));
		AddQuestUserData("SharpPearl", "sTarget", XI_ConvertString("Colony" + pchar.questTemp.Sharp.City + "Acc"));
		if (GetIslandByCityName(pchar.questTemp.Sharp.City) != pchar.questTemp.Sharp.City)
		{
			AddQuestUserData("SharpPearl", "sAreal", ", что находится на " + XI_ConvertString(GetIslandByCityName(pchar.questTemp.Sharp.City) + "Dat"));
		}
		//запускаем опять Шарпа на карту
		sld = characterFromId("Sharp");
		string sGroup = "Sharp_Group";
		Group_FindOrCreateGroup(sGroup);
		Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
		Group_LockTask(sGroup);
		Group_AddCharacter(sGroup, sld.id);
		Group_SetGroupCommander(sGroup, sld.id);
		sld.mapEnc.type = "trade";
		sld.mapEnc.worldMapShip = "quest_ship";
		sld.mapEnc.Name = "бриг 'Шарпоносец'";
		string sColony= SelectAnyColony(sCity); //колония, откуда плывет Шарп
		int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sColony), GetArealByCityName(pchar.questTemp.Sharp.City))+3; //дней доехать даем с запасом
		Map_CreateTrader(sColony, pchar.questTemp.Sharp.City, sld.id, daysQty);
	}
	else
	{
		if (rand(5) < 4)
		{
			sBack = GetSharpRumour_inIsland();
			pchar.questTemp.Sharp.Island = GiveArealByLocation(loadedLocation);
			pchar.questTemp.Sharp.count = 0; //счетчик нулим для след. раза
			pchar.questTemp.Sharp.price = 5000+rand(20)*1000; //цена за наводку
			pchar.questTemp.Sharp.price.evil = rand(1); //добрый или злой, для скидки
			Pchar.quest.Sharp_loginNearIsland.win_condition.l1 = "location";
			Pchar.quest.Sharp_loginNearIsland.win_condition.l1.location = pchar.questTemp.Sharp.Island;
			Pchar.quest.Sharp_loginNearIsland.function = "Sharp_loginNearIsland";
			AddQuestRecord("SharpPearl", "3");
			SaveCurrentQuestDateParam("questTemp.Sharp");
			Log_QuestInfo("Сработало на остров.");
		}
		else
		{
			sBack = GetSharpRumour_inCity();
			pchar.questTemp.Sharp.count = 0; //счетчик нулим для след. раза
			pchar.questTemp.Sharp.price = 5000+rand(20)*1000; //цена за наводку
			pchar.questTemp.Sharp.price.evil = rand(1); //добрый или злой, для скидки
			float locx, locy, locz;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			sld = &characters[GetCharacterIndex("Sharp")];
			sld.dialog.currentnode = "CitySharp";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
			ChangeCharacterAddressGroup(sld, pchar.location, "patrol", LAi_FindFarLocator("patrol", locx, locy, locz));
			AddQuestRecord("SharpPearl", "11");
			Log_QuestInfo("Сработало на город.");
		}
	}
	return sBack;
}

//ищем новый город
string GetSharpCity()
{
	int n, iRes;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	if (GetBaseHeroNation() != PIRATE)
	{
	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation != "none" && GetRelation2BaseNation(sti(colonies[n].nation)) != RELATION_ENEMY && GiveArealByLocation(loadedLocation) != colonies[n].island && colonies[n].id != "Panama") //не на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	}
	else
	{
		for(n=0; n<MAX_COLONIES; n++)
		{
			if (colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GiveArealByLocation(loadedLocation) != colonies[n].island && colonies[n].id != "Panama") //не на свой остров
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	iRes = storeArray[rand(howStore-1)];
	return colonies[iRes].id;
}
//фразы по умолчанию
string GetSharpRumour_default()
{
	string sRumour;
	switch (rand(2))
    {
        case 0: sRumour = "Капитан Шарп был здесь, я его видел. Но сейчас его в городе нет, а куда ушел - не знаю."; break;
        case 1: sRumour = "Капитан Шарп заходил в наш город. Где он сейчас я не знаю, у нас его точно нет."; break;
        case 2:	sRumour = "Капитан Барталомью Шарп ушел из города буквально на днях..."; break;
    }
	return sRumour;
}
//фразы в другой город
string GetSharpRumour_toCityTarget()
{
	string sRumour;
	switch (rand(2))
    {
        case 0: sRumour = "Капитан Бартоломью Шарп был у нас в городе и, как всегда, умудрился 'отметиться'... Но сейчас его здесь нет. По слухам он ушел в " + XI_ConvertString("Colony" + pchar.questTemp.Sharp.City + "Acc") + "."; break;
        case 1: sRumour = "Знаете, капитан Шарп был в городе недавно. Веселый пират, этот Барталомью... Хорошо, однако, что он покинул наш город. Кажется он ушел в " + XI_ConvertString("Colony" + pchar.questTemp.Sharp.City + "Acc") + "."; break;
        case 2:	sRumour = "Вы знаете, недавно нас почтил своим присутствием капитан Шарп. Но, к нашему большому разочарованию, нового карибского анекдота 'от Шарпа' не случилось. Жаль... А сейчас его нет у нас в городе. Говорят, он ушел в " + XI_ConvertString("Colony" + pchar.questTemp.Sharp.City + "Acc") + ". Может им повезет..."; break;
    }
	return sRumour;
}
//фразы у осрова
string GetSharpRumour_inIsland()
{
	string sRumour;
	switch (rand(2))
    {
        case 0: sRumour = "Вы знаете, капитан Шарп только что вышел из города на своем бриге. Если бы вы прибыли с пол часа назад, то увидели бы его прямо в порту."; break;
        case 1: sRumour = "Капитан Шарп... Да уже, тот еще капитан. Знаете, он только что покинул наш город. Если вы поторопитесь, то сможете его застать в окрестных водах."; break;
        case 2:	sRumour = "Бартоломью Шарп буквально с час назад вышел из нашего порта в море."; break;
    }
	return sRumour;
}
//фразы в городе
string GetSharpRumour_inCity()
{
	string sRumour;
	switch (rand(2))
    {
        case 0: sRumour = "Пару минут назад капитан Шарп столкнулся со мной лицом к лицу. Ходит здесь по улицам, странно, что не в борделе..."; break;
        case 1: sRumour = "Только что на улице довелось поговорить с капитаном Шарпом. Занятный, знаете ли, тип..."; break;
        case 2:	sRumour = "Капитан Шарп сейчас гуляет по улицам. А мы все ждем, чего же он выкинет в очередной раз..."; break;
    }
	return sRumour;
}

//=============== шебека Синяя Птица.  ====================
string BlueBurd_setTradeShip()
{
	pchar.questTemp.BlueBird.Island = GiveArealByLocation(loadedLocation);
	Pchar.quest.BlueBird_loginFleut.win_condition.l1 = "location";
	Pchar.quest.BlueBird_loginFleut.win_condition.l1.location = pchar.questTemp.BlueBird.Island;
	Pchar.quest.BlueBird_loginFleut.function = "BlueBird_loginFleut";
	pchar.questTemp.BlueBird.nation = colonies[FindColony(pchar.questTemp.BlueBird.City)].nation; //нация колонии, откуда кораблик
	aref aName;
	makearef(aName, pchar.questTemp.BlueBird);
	SetRandomNameToShip(aName);
	AddQuestRecord("Xebeca_BlueBird", "10");
	AddQuestUserData("Xebeca_BlueBird", "sCity", XI_ConvertString("Colony" + pchar.questTemp.BlueBird.City + "Dat"));
	AddQuestUserData("Xebeca_BlueBird", "sShipName", "'" + aName.Ship.Name + "'");
	AddQuestUserData("Xebeca_BlueBird", "sCity_2", XI_ConvertString("Colony" + pchar.questTemp.BlueBird.City + "Gen"));
	AddQuestUserData("Xebeca_BlueBird", "sTradeName", GetFullName(characterFromId(pchar.questTemp.BlueBird.City + "_trader")));
	AddQuestUserData("Xebeca_BlueBird", "sIsland", XI_ConvertString(pchar.questTemp.BlueBird.Island + "Gen"));
	SaveCurrentQuestDateParam("questTemp.BlueBird");
	return GetBlueBirdRumour_Ship(); //текст слуха
}
//фразы по слухам, наводки на корабли тоговцев
string GetBlueBirdRumour_Ship()
{
	string sRumour;
	switch (rand(2))
    {
        case 0: sRumour = "Вы знаете, местный торговец, " + GetFullName(characterFromId(pchar.questTemp.BlueBird.City + "_trader")) + ", опять отправляет собственный флейт '" + pchar.questTemp.BlueBird.Ship.Name + "' в Старый Свет за товаром. Недавно флейт вышел из порта."; break;
		case 1: sRumour = "Хм, а дела у нашего негоцианта доморощенного идут неплохо! " + GetFullName(characterFromId(pchar.questTemp.BlueBird.City + "_trader")) + " вновь отправил собственный флейт '" + pchar.questTemp.BlueBird.Ship.Name + "' за товаром, тот только что вышел из нашего порта."; break;
        case 2:	sRumour = "М-да, а " + GetFullName(characterFromId(pchar.questTemp.BlueBird.City + "_trader")) + " все богатеет и богатеет. Только вчера его парусник стоял под разгрузкой в порту, а сегодня порт уже попрощался с ним. Флейт '" + pchar.questTemp.BlueBird.Ship.Name + "' ушел опять за товаром, так то!"; break;
    }
	return sRumour;
}
//======================= пиратская линейка ===================================
void PiratesLineInit()
{
	ref sld;
	pchar.questTemp.piratesLine = "begin";
	sld = GetCharacter(NPC_GenerateCharacter("QuestPirate1", "officer_9", "man", "man", 20, PIRATE, -1, true));
	sld.name = "Капитан";
	sld.lastname = "Гудли";
	sld.rank = 20;
	sld.city = "PuertoPrincipe";
	sld.location	= "PuertoPrincipe_town";
	sld.location.group = "goto";
	sld.location.locator = "goto7";
	sld.dialog.filename   = "Quest\PiratesLine_dialog.c";
	sld.dialog.currentnode   = "PiratesMan1";
	sld.greeting = "Gr_EvilPirate";
	sld.talker = 8; //начать диалог
	sld.TiedItems.itm1.model = "HandsItems\meet";
	sld.TiedItems.itm1.locator = "Saber_hand";
	sld.TiedItems.itm2.model = "HandsItems\cup";
	sld.TiedItems.itm2.locator = "Saber_hand";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
}

//ищем город определенной нации, проверять наличие ростовщика и тавернщика
string GetQuestNationsCity(int _nation)
{
	int n, iRes;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation != "none"  && colonies[n].id != "Panama" && sti(colonies[n].nation) == _nation && GiveArealByLocation(loadedLocation) != colonies[n].island) //не на свой остров
		{
			if (GetCharacterIndex(colonies[n].id + "_tavernkeeper") > 0 && GetCharacterIndex(colonies[n].id + "_usurer") > 0)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	iRes = storeArray[cRand(howStore-1)];
	return colonies[iRes].id;
}

string GetRandomPirateCity()
{
	int n, iRes;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation != "none"  && colonies[n].id != "Panama" && sti(colonies[n].nation) == 4 && GiveArealByLocation(loadedLocation) != colonies[n].island) //не на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	iRes = storeArray[cRand(howStore-1)];
	return colonies[iRes].id;
}

//ищем не вражескую колонию, куда можно доплыть
string SelectNotEnemyColony(ref NPChar)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		
		/* if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "FortOrange" && colonies[n].id != "Caiman" && colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров */
		if (colonies[n].id != "Panama" && colonies[n].id != "FortOrange" && colonies[n].id != "Caiman" && colonies[n].nation != "none"  && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
			if (nation != RELATION_ENEMY)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
}

//ищем любую национальную колонию, куда можно доплыть
string SelectAnyColony(string _City)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].id != "Panama" && colonies[n].id != "FortOrange" && colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetIslandByCityName(_City) != colonies[n].islandLable) //не на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
}

string SelectAnyColony2(string _City1, string _City2)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].id != "Panama" && colonies[n].id != "FortOrange" && colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetIslandByCityName(_City1) != colonies[n].islandLable && GetIslandByCityName(_City2) != colonies[n].islandLable) //не на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
}

ref CheckLSCCitizen()
{
	ref rCharacter;
	string sTemp, sSeeked;
	sSeeked = GetStrSmallRegister(dialogEditStrings[3]);
	if (sSeeked == "адмирал" || sSeeked == "адмиралa")
	{
		return characterFromId("LSCMayor");
	}
	if (sSeeked == "трактирщик" || sSeeked == "трактирщика" || sSeeked == "тавернщик"|| sSeeked == "тавернщика" || sSeeked == "хозяин таверны" || sSeeked == "хозяина таверны")
	{
		return characterFromId("LSCBarmen");
	}
	if (sSeeked == "официантка" || sSeeked == "официантку")
	{
		return characterFromId("LSCwaitress");
	}
	if (sSeeked == "механика" || sSeeked == "механик")
	{
		return characterFromId("Mechanic");
	}
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (CheckAttribute(rCharacter, "city") && rCharacter.city == "LostShipsCity")
		{
			sTemp = GetStrSmallRegister(rCharacter.name + " " + rCharacter.lastname);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
			{
				return rCharacter;
			}
			sTemp = GetStrSmallRegister(rCharacter.lastname);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
			{
				return rCharacter;
			}
			else
			{
				sTemp = GetStrSmallRegister(rCharacter.name);
				if (findsubstr(sSeeked, sTemp , 0) != -1)
				{
					return rCharacter;
				}
			}
		}
	}
	return &NullCharacter;
}

string WhereLSCCitizen(ref rCharacter)
{
	string sShip = "none";
	string sTemp;
	if (rCharacter.location	== "LostShipsCity_town")
	{
		sTemp = rCharacter.location.locator;
		sTemp = strcut(sTemp, 4, 5);
		switch (sTemp)
		{
			case "01": sShip = "на бэттлшипе 'Тартарус', где тюрьма"; break;
			case "02": sShip = "на фрегате 'Каролина'"; break;
			case "03": sShip = "на флейте 'Церес Смити'"; break;
			case "04": sShip = "на галеоне 'Эсмеральда', где магазин"; break;
			case "05": sShip = "на каравелле 'Флерон', где таверна"; break;
			case "06": sShip = "на пинасе 'Фурия', в носовой части"; break;
			case "07": sShip = "на пинасе 'Фурия', в кормовой части"; break;
			case "08": sShip = "на галеоне 'Глория', где церковь"; break;
			case "09": sShip = "на флейте 'Плуто'"; break;
			case "10": sShip = "на корвете 'Протектор'"; break;
			case "11": sShip = "на варшипе 'Сан Августин', где резиденция адмирала"; break;
			case "12": sShip = "на барке 'Сан Габриель', в носовой части"; break;
			case "13": sShip = "на барке 'Сан Габриель', в кормовой части"; break;
			case "14": sShip = "на бриге 'Санта Флорентина'"; break;
			case "15": sShip = "на галеоне 'Эва'"; break;
			case "16": sShip = "на галеоне 'Веласко'"; break;
		}
	}
	else
	{
		switch (rCharacter.location)
		{
			case "AvaShipInside3": sShip = "в галеоне 'Эва'"; break;
			case "CarolineBank": sShip = "в фрегате 'Каролина'"; break;
			case "CeresSmithy": sShip = "во флейте 'Церес Смити'"; break;
			case "EsmeraldaStoreBig": sShip = "в галеоне 'Эсмеральда', в магазине"; break;
			case "FenixPlatform": sShip = "в платформе 'Феникс'"; break;
			case "FernandaDiffIndoor": sShip = "во флейте 'Фернандо Диффиндур'"; break;
			case "FleuronTavern": sShip = "в каравелле 'Флерон', в таверне"; break;
			case "FurieShipInside2": sShip = "в пинасе 'Фурия'"; break;
			case "GloriaChurch": sShip = "в галеоне 'Глория', в церкви"; break;
			case "PlutoStoreSmall": sShip = "во флете 'Плуто'"; break;
			case "ProtectorFisher": sShip = "в корвете 'Протектор'"; break;
			case "SanAugustineResidence": sShip = "в варшипе 'Сан Августин', в резиденции адмирала"; break;
			case "SanGabrielMechanic": sShip = "в барке 'Сан Габриель'"; break;
			case "SantaFlorentinaShipInside4": sShip = "в бриге 'Санта Флорентина'"; break;
			case "TartarusPrison": sShip = "в бэттлшипе 'Тартарус', в тюрьме"; break;
			case "VelascoShipInside1": sShip = "в галеоне 'Веласко'"; break;
		}
	}
	return sShip;
}

//отдать забытый судовой журнал. помещаем в город кэпа, который приплыл к назначенной колонии
void SetCapitainFromSeaToCity(string sChar)
{
	ref sld = &characters[GetCharacterIndex(sChar)];
	sld.quest = "InCity"; //флаг в городе
	sld.City = sld.quest.targetCity; //аттрибут текущего города пропишем
	sld.location	= sld.City + "_PortOffice";
	sld.location.group = "goto";
	sld.location.locator = "goto"+(rand(2)+1);
	LAi_SetCitizenType(sld);

	/*int iColony = FindColony(sld.City);
	string sGroup = "PorpmansShip_" + sld.index;
	group_DeleteGroup(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	Group_SetAddress(sGroup, colonies[iColony].island, "quest_ships", "Quest_ship_"+(rand(2)+1));
	Group_SetTaskNone(sGroup);*/

	//таймер через сколько опять выйти в море
	int Qty = rand(4)+3;
	string name = "Timer_" + sld.id;
	PChar.quest.(name).win_condition.l1            = "Timer";
    PChar.quest.(name).win_condition.l1.date.day   = GetAddingDataDay(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.month = GetAddingDataMonth(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.year  = GetAddingDataYear(0, 0, Qty);
    PChar.quest.(name).function					= "SetCapitainFromCityToSea";
	pchar.quest.(name).CapId = sld.id; //в прерывании запомним Id кэпа
	//обновим дату в базе для контроля кэпов на суше
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = Qty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
	//даем слух, что кэп в городе
	AddSimpleRumourCity(LinkRandPhrase("Капитан " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' сейчас в городе. Кажется, его зовут " + GetFullName(sld) + ". Он сейчас должнен быть у начальника порта.",
		"Вы знаете, капитана " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' сейчас можно застать у начальника порта.",
		"Если вы хотите пообщаться с капитаном " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "', то идите прямоком к начальнику порта. " + GetFullName(sld) + " сейчас там..."), sld.City, Qty, 1, "none");
}
//отдать забытый судовой журнал. записть в квестбук из слухов
void PortmansBook_writeQuestBook(ref rid)
{
	int iTemp = GetCharacterIndex(rid.addString)
	if (iTemp != -1)
	{
		ref sld = &characters[iTemp];
		if (LAi_IsDead(sld)) return;
		string sTitle = characters[GetCharacterIndex(sld.quest.firstCity + "_PortMan")].id + "PortmansBook_Delivery";
		AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "4");
		AddQuestUserData(sTitle, "sCapName", GetFullName(sld));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + rid.city + "Gen"));
		AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + sld.quest.targetCity + "Acc"));
		if (GetIslandByCityName(sld.quest.targetCity) != sld.quest.targetCity)
		{
			AddQuestUserData(sTitle, "sAreal", ", что находится на " + XI_ConvertString(GetIslandByCityName(sld.quest.targetCity) + "Dat"));
		}
	}
}

//разыскать кэпа-вора. помещаем в город кэпа, который приплыл к назначенной колонии
void SetRobberFromMapToSea(string sChar)
{
	ref sld = &characters[GetCharacterIndex(sChar)];
	sld.quest = "InPort"; //флаг кэпа стоит в порту
	sld.City = sld.quest.targetCity; //аттрибут текущего города пропишем
	int iColony = FindColony(sld.City);
	sld.nation = colonies[iColony].nation; //нацию дадим, что и у города

	string sGroup = "SeekCapShip_" + sld.index;
	group_DeleteGroup(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	Group_SetAddress(sGroup, colonies[iColony].island, "quest_ships", "Quest_ship_"+(rand(2)+1));
	Group_SetTaskNone(sGroup);

	//таймер через сколько опять выйти на карту
	int Qty = rand(5)+4;
	string name = "SecondTimer_" + sld.id;
	PChar.quest.(name).win_condition.l1            = "Timer";
    PChar.quest.(name).win_condition.l1.date.day   = GetAddingDataDay(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.month = GetAddingDataMonth(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.year  = GetAddingDataYear(0, 0, Qty);
    PChar.quest.(name).function					= "SetRobberFromSeaToMap";
	pchar.quest.(name).CapId = sld.id; //в прерывании запомним Id кэпа
	//обновим дату в базе для контроля кэпов на суше
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = Qty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
	//даем слух, что кэп на рейде
	AddSimpleRumourCity(LinkRandPhrase("Капитан " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' стоит в порту на рейде. Кажется, его зовут " + GetFullName(sld) + ". Странный тип, скажу я вам, на берег не сходит вообще.",
		"Вы знаете, капитана " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' сейчас можно встретить, только если выйти на шлюпке в порт. Корабль стоит на рейде, но капитан в город не выходит, предпочитает оставаться на корабле. И не надоело ему?..",
		"Если вы хотите пообщаться с капитаном " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "', то выходите в порт. " + GetFullName(sld) + " вроде бы его зовут... В общем, он бросил якорь в порту, но на берег не сходит. Настоящий морской волк, даже с палубной качкой расставаться не хочет."), sld.City, Qty, 1, "none");
}
//разыскать кэпа-вора. запись в квестбук из слухов
void PortmansSeekShip_writeQuestBook(ref rid)
{
	int iTemp = GetCharacterIndex(rid.addString)
	if (iTemp != -1)
	{
		ref sld = &characters[iTemp];
		if (LAi_IsDead(sld)) return;
		ref npchar = &characters[GetCharacterIndex(sld.quest.firstCity + "_PortMan")];
		string sTitle = npchar.id + "Portmans_SeekShip";
		AddQuestRecordEx(sTitle, "Portmans_SeekShip", "3");
		AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName)));
		AddQuestUserData(sTitle, "sShipName", sld.Ship.name);
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + rid.city + "Gen"));
		iTemp = RealShips[sti(sld.Ship.Type)].basetype;
		AddQuestUserData(sTitle, "sSexWord", GetShipSexWord(ShipsTypes[iTemp].name, "ушел", "ушла"));
		AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + sld.quest.targetCity + "Acc"));
		if (GetIslandByCityName(sld.quest.targetCity) != sld.quest.targetCity)
		{
			AddQuestUserData(sTitle, "sAreal", ", что находится на " + XI_ConvertString(GetIslandByCityName(sld.quest.targetCity) + "Dat"));
		}
	}
}

//розыск кэпов горожанами
void CitizCapFromMapToCity(string sChar)
{
	ref sld = &characters[GetCharacterIndex(sChar)];
	sld.quest = "InCity"; //флаг кэпа ходит по городу
	sld.City = sld.quest.targetCity; //аттрибут текущего города пропишем
	int iColony = FindColony(sld.City);
	sld.nation = colonies[iColony].nation; //нацию дадим, что и у города
	if (rand(1))
	{	//ходит в городе
		sld.location	= sld.City + "_town";
		sld.location.group = "goto";
		sld.location.locator = "goto"+(rand(5)+1);
		LAi_SetCitizenType(sld);
		string slai_group = GetNationNameByType(sti(colonies[iColony].nation))  + "_citizens";
		LAi_group_MoveCharacter(sld, slai_group);
		//даем слух, что кэп на рейде
		AddSimpleRumourCity(LinkRandPhrase("Капитан " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' в городе. Кажется, его зовут " + GetFullName(sld) + ".",
			"Вы знаете, капитана " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' сейчас можно застать в городе.",
			"Если вы хотите пообщаться с капитаном " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "', то поищите его в на улицах. " + GetFullName(sld) + " вроде бы его зовут..."), sld.City, Qty, 1, "none");
	}
	else
	{	//стоит на рейде в порту
		string sGroup = "SeekCapShip_" + sld.index;
		group_DeleteGroup(sGroup);
		Group_AddCharacter(sGroup, sld.id);
		Group_SetGroupCommander(sGroup, sld.id);
		Group_SetAddress(sGroup, colonies[iColony].island, "quest_ships", "Quest_ship_"+(rand(2)+1));
		Group_SetTaskNone(sGroup);
		//даем слух, что кэп на рейде
		AddSimpleRumourCity(LinkRandPhrase("Капитан " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' находится в порту на рейде. Кажется, его зовут " + GetFullName(sld) + ".",
			"Вы знаете, капитана " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "' сейчас можно застать в нашем порту. Его корабль стоит на рейде.",
			"Если вы хотите пообщаться с капитаном " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "', то поищите его корабль в нашем порту. " + GetFullName(sld) + " вроде бы его зовут..."), sld.City, Qty, 1, "none");
	}
	//таймер через сколько опять выйти на карту
	int Qty = rand(7)+5; //через сколько дней выйдем на карту
	string name = "SecondTimer_" + sld.id;
	PChar.quest.(name).win_condition.l1            = "Timer";
    PChar.quest.(name).win_condition.l1.date.day   = GetAddingDataDay(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.month = GetAddingDataMonth(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.year  = GetAddingDataYear(0, 0, Qty);
    PChar.quest.(name).function					= "CitizCapFromSeaToMap";
	pchar.quest.(name).CapId = sld.id; //в прерывании запомним Id кэпа
	//обновим дату в базе для контроля кэпов на суше
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = Qty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

//разыск кэпа от горожан. запись в квестбук из слухов
void CitizSeekCap_writeQuestBook(ref rid)
{
	int iTemp = GetCharacterIndex(rid.addString)
	if (iTemp != -1)
	{
		ref sld = &characters[iTemp];
		if (LAi_IsDead(sld)) return;
		ref npchar = &characters[GetCharacterIndex("QuestCitiz_" + sld.quest.cribCity)];
		string sTitle = sld.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "3");
		AddQuestUserData(sTitle, "sCapName", GetFullName(sld));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + rid.city + "Gen"));
		AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + sld.quest.targetCity + "Acc"));
		if (GetIslandByCityName(sld.quest.targetCity) != sld.quest.targetCity)
		{
			AddQuestUserData(sTitle, "sAreal", ", что находится на " + XI_ConvertString(GetIslandByCityName(sld.quest.targetCity) + "Dat"));
		}
	}
}

//плавание мушкетерского кэпа
void SetMushketFromMapToSea()
{
	ref sld = characterFromId("MushketCap");
	sld.quest = "InShore"; //флаг кэпа стоит в порту
	sld.City = sld.quest.targetCity; //аттрибут текущего города пропишем
	int iColony = FindColony(sld.City);

	string sGroup = "MushketCapShip";
	group_DeleteGroup(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	Group_SetAddress(sGroup, colonies[iColony].island, "quest_ships", "Quest_ship_"+(rand(2)+5));
	Group_SetTaskNone(sGroup);
	//таймер через сколько опять выйти на карту
	int Qty = rand(2)+3;
	string name = "MushketTimer";
	PChar.quest.(name).win_condition.l1            = "Timer";
    PChar.quest.(name).win_condition.l1.date.day   = GetAddingDataDay(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.month = GetAddingDataMonth(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.year  = GetAddingDataYear(0, 0, Qty);
    PChar.quest.(name).function					= "SetMushketFromSeaToMap";
	//обновим дату в базе для контроля кэпов на суше
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = Qty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

//плавание Даньки
void SetDanielleFromMapToSea()
{
	ref sld = characterFromId("Danielle");
	sld.quest = "InShore"; //флаг кэпа стоит в порту
	sld.City = sld.quest.targetCity; //аттрибут текущего города пропишем
	int iColony = FindColony(sld.City);

	string sGroup = "DanielleGroup";
	group_DeleteGroup(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	Group_SetAddress(sGroup, colonies[iColony].island, "quest_ships", "Quest_ship_"+(rand(2)+3));
	Group_SetTaskNone(sGroup);
	//таймер через сколько опять выйти на карту
	int Qty = rand(5)+7;
	string name = "DanielleTimer";
	PChar.quest.(name).win_condition.l1            = "Timer";
    PChar.quest.(name).win_condition.l1.date.day   = GetAddingDataDay(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.month = GetAddingDataMonth(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.year  = GetAddingDataYear(0, 0, Qty);
    PChar.quest.(name).function					= "SetDanielleFromSeaToMap";
	//обновим дату в базе для контроля кэпов на суше
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = Qty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

void SetBlackBeardFromMapToSea()
{
	ref sld = characterFromId("BlackBeardNPC");
	sld.quest = "InShore"; //флаг кэпа стоит в порту
	sld.City = sld.quest.targetCity; //аттрибут текущего города пропишем
	int iColony = FindColony(sld.City);

	string sGroup = "BlackBeardGroup";
	group_DeleteGroup(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	Group_SetAddress(sGroup, colonies[iColony].island, "quest_ships", "Quest_ship_"+(rand(2)+3));
	Group_SetTaskNone(sGroup);
	//таймер через сколько опять выйти на карту
	int Qty = rand(5)+5;
	string name = "BlackBeardTimer";
	PChar.quest.(name).win_condition.l1            = "Timer";
    PChar.quest.(name).win_condition.l1.date.day   = GetAddingDataDay(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.month = GetAddingDataMonth(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.year  = GetAddingDataYear(0, 0, Qty);
    PChar.quest.(name).function					= "SetBlackBeardFromSeaToMap";
	//обновим дату в базе для контроля кэпов на суше
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = Qty + 3;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

//линейка Блада в Барбадосе
//поставить Синко Льягас в город
void SetShipInBridgetown()
{
	int n = FindLocation("Bridgetown_town");
	locations[n].models.always.ship = "Bridgetown_ship";
	locations[n].models.always.shipreflect = "Bridgetown_shipreflect";
	Locations[n].models.always.shipreflect.sea_reflection = 1;
	locations[n].models.always.locators = "Bridgetown_locatorsShip";
	locations[n].models.day.fonarShip = "Bridgetown_fdShip";
	locations[n].models.night.fonarShip = "Bridgetown_fnShip";
	locations[n].models.day.charactersPatch = "Bridgetown_patchship_day";
	locations[n].models.night.charactersPatch = "Bridgetown_patchship_night";

	locations[n].reload.ship1.name = "reloadShip";
	locations[n].reload.ship1.go = "Cabin";
	locations[n].reload.ship1.emerge = "reload1";
	locations[n].reload.ship1.autoreload = "0";
	locations[n].reload.ship1.label = "cabine";

	n = FindLocation("Cabin");
	DeleteAttribute(&locations[n], "boarding");
	DeleteAttribute(&locations[n], "camshuttle");
	DeleteAttribute(&locations[n], "CabinType");

	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Bridgetown_town";
	locations[n].reload.l1.emerge = "reloadShip";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Ship";
}
//убрать Синко Льягас из города
void RemoveShipFromBridgetown()
{
	int n = FindLocation("Bridgetown_town");
	DeleteAttribute(&locations[n], "models.always.ship");
	DeleteAttribute(&locations[n], "models.always.shipreflect");
	DeleteAttribute(&locations[n], "models.always.shipreflect.sea_reflection");
	locations[n].models.always.locators = "Bridgetown_locators";
	DeleteAttribute(&locations[n], "models.day.fonarShip");
	DeleteAttribute(&locations[n], "models.night.fonarShip");
	locations[n].models.day.charactersPatch = "Bridgetown_patch_day";
	locations[n].models.night.charactersPatch = "Bridgetown_patch_night";
	DeleteAttribute(&locations[n], "reload.ship1");

	n = FindLocation("Cabin");
	DeleteAttribute(&locations[n], "reload");
	Locations[n].boarding = "true";
	Locations[n].boarding.nextdeck = "";
	Locations[n].camshuttle = 1;
	Locations[n].boarding.locatorNum = 1;
	Locations[n].CabinType = true;
	locations[n].environment.weather.rain = false;
	Locations[n].boarding.Loc.Hero = "loc0";
    Locations[n].boarding.Loc.Capt = "aloc2";
}

//------------------- линейка ГПК ----------------------
//пробежаться по сундукам
void LSC_checkBoxes()
{
	ref loc;
	aref arBox;
	string sName;
	for(int i=0; i<MAX_LOCATIONS; i++)
	{
		loc = &locations[i];
		if (CheckAttribute(loc, "fastreload") && loc.fastreload == "LostShipsCity" && loc.id != "FernandaDiffIndoor")
		{
			for(int n=1; n<=MAX_HANDLED_BOXES; n++)
			{
				sName = "private" + n;
				if (CheckAttribute(loc, sName) && sName != "private11")
				{
					makearef(arBox, loc.(sName));
					if (CheckAttribute(arBox, "equip") && rand(1))
					{
						DeleteAttribute(arBox, "items");
						arBox.items = "";
					}
				}
				else break;
			}
		}
	}
}

//линейка ГПК. проверить дистанцию до своих во время атаки
void LSC_CheckCasperDistance(ref sld)
{
	if (!CheckAttribute(pchar, "questTemp.LSC.Armo.Interrapt"))
	{
		sld.quest.checkCasper = true; //для обработки в АИ warrior
		pchar.quest.LSC_KillOneCasper.win_condition.l1 = "NPC_Death";
		pchar.quest.LSC_KillOneCasper.win_condition.l1.character = sld.id;
		pchar.quest.LSC_KillOneCasper.function= "LSC_KillOneCasper";
		pchar.quest.LSC_KillOneCasper.casperIdx = sld.index;
		pchar.questTemp.LSC.Armo.Interrapt = true; //чтобы не вызывать больше прерывания
	}
	float dist;
	if (GetCharacterDistByLoc(sld, "goto", "goto12_4", &dist))
	{
		if (dist < 40.0)
		{
			LSC_CasperIsHelp();
		}
	}
}
//клан ломится на выручку
void LSC_CasperIsHelp()
{
	Log_SetStringToLog("Звуки борьбы были услышаны на барке 'Сан Габриэль'.");
	chrDisableReloadToLocation = true;
	pchar.questTemp.LSC = "toSeekMechanikCasperOff";
	//если пошел навал, то чистим квест Армо
	pchar.questTemp.LSC.Armo = 15; //завязываем с дачей квестов от Армо
	pchar.quest.LSC_KillOneCasper.over = "yes";
	pchar.quest.LSC_checkCasperDead.over = "yes";
	//бойцов в подмогу
	int iTemp = GetCharacterIndex("Casper_head");
	if (iTemp != -1) ChangeCharacterAddressGroup(&characters[iTemp], "LostShipsCity_town", "reload", "reload55");
	for (int i=1; i<=11; i++)
	{
		iTemp = GetCharacterIndex("Casper_"+i);
		if (iTemp != -1)
		{
			if (characters[iTemp].location != "LostShipsCity_town")
			{
				ChangeCharacterAddressGroup(&characters[iTemp], "LostShipsCity_town", "reload", "reload55");
			}
			else
			{
				if (!LAi_IsDead(&characters[iTemp]))
				{
					LAi_group_MoveCharacter(&characters[iTemp], "PearlGroup_2");
					DeleteAttribute(&characters[iTemp], "quest.checkCasper"); //сносим флаги на проверку расстояния до базы
				}
			}
		}
	}
	//мушкетеров ставим
	sld = GetCharacter(NPC_GenerateCharacter("CasperMush_1", "Mushketer_2", "man", "mushketer", 30, PIRATE, -1, false));
	SetCharacterPerk(sld, "GunProfessional");
	sld.MusketerDistance = 0;
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_2");
	ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "reload", "reload55");

	sld = GetCharacter(NPC_GenerateCharacter("CasperMush_2", "Mushketer_4", "man", "mushketer", 30, PIRATE, -1, false));
	SetCharacterPerk(sld, "GunProfessional");
	sld.MusketerDistance = 0;
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PearlGroup_2");
	ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "reload", "reload55");
	//дополнительно, на всякий случай
	//LAi_group_SetRelation("PearlGroup_2", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	//LAi_group_FightGroups("PearlGroup_2", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("PearlGroup_2", "OpenTheDoors");
}

//квест на мужа Элис Тейлор, после получения слуха
void LSC_rumourElisHusband()
{
	if (!CheckActiveQuest("ISS_ElisHusband"))
	{
		pchar.questTemp.LSC.ElisHusband = "begin";
		AddQuestRecord("ISS_ElisHusband", "1");
	}
}
//начало сразу, после первого базара с адмиралом
void LSC_beginElisHusband()
{
	// муж Элис Тейлор
	ref sld = GetCharacter(NPC_GenerateCharacter("MaximTailor", "shipowner_10", "man", "man", 10, PIRATE, -1, false));
	sld.name = "Максим";
	sld.lastname = "Тейлор";
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "TartarusPrison";
	sld.location.group = "quest";
	sld.location.locator = "prison4";
	sld.dialog.filename   = "Quest\LostShipsCity\MaximTailor.c";
	sld.dialog.currentnode   = "InPrison";
	sld.cityTape = "quest"; //тип нпс
	sld.greeting = "pirat_common";
	sld.location.hours = 4; //передвижения через .. часов
	LAi_SetGroundSitType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
}

//квест со скелетом Лейтона Декстера
void LSC_rumourLostDecster()
{
	if (!CheckActiveQuest("LSC_findDekster"))
		AddQuestRecord("LSC_findDekster", "1");
}
void LSC_enterAdmiralBox()
{
	if (!CheckAttribute(pchar, "questTemp.LSC.private10"))
	{
		if (CheckAttribute(pchar, "questTemp.LSC.lostDecster"))
		{
			if (pchar.questTemp.LSC.lostDecster == "seekBox")
			{
				AddQuestRecord("LSC_findDekster", "6");
				AddQuestUserData("LSC_findDekster", "sSex", GetSexPhrase("ел","ла"));
			}
			else
			{
				iTemp = GetCharacterIndex("LSC_Prisoner1");
				if (iTemp != 1 && CheckAttribute(&characters[iTemp], "quest.decster"))
				{
					AddQuestRecord("LSC_findDekster", "7");
				}
				else
				{
					AddQuestRecord("LSC_findDekster", "9");
					AddQuestUserData("LSC_findDekster", "sSex", GetSexPhrase("ел","ла"));
				}
			}
		}
		else
		{
			AddQuestRecord("LSC_findDekster", "8");
			AddQuestUserData("LSC_findDekster", "sSex", GetSexPhrase("ел","ла"));
		}
		pchar.questTemp.LSC.lostDecster = "foundAdmiralBox";
		AddSimpleRumourCityTip("Вы слышали, что Чад Каппер потерял какой-то важный для него ключ. Теперь бегает по всему Городу, ищет...", "LostShipsCity", 10, 1, "LSC", "LSC_rumourAdmiralLostKey");
		pchar.questTemp.LSC.private10 = true; //чтобы больше не срабатывало
	}
}
void LSC_rumourAdmiralLostKey()
{
	//делаем видимым ключ
	ref sld = ItemsFromID("keyPanama");
	sld.shown = true;
	sld.startLocation = "LostShipsCity_town";
	sld.startLocator = "item" + (rand(4)+2);
	ChangeItemName("keyPanama", "itmname_keyPanama_LSC");
	ChangeItemDescribe("keyPanama", "itmdescr_keyPanama_LSC");
	SetTimerFunction("LSC_admiralFoundOwnKey", 0, 0, 2); //таймер на снятие ключа из локатора
	pchar.questTemp.LSC.lostDecster = "admiralLostKey";
	AddQuestRecord("LSC_findDekster", "10");
}

//таймер
void SetShowTimer(float time)
{
	pchar.showTimer = time + 0.99;
	pchar.quest.ClearTimer.win_condition.l1 = "ExitFromLocation";
	pchar.quest.ClearTimer.win_condition.l1.location = pchar.location;
	pchar.quest.ClearTimer.function = "ClearTimer";
}

void ClearTimer(string qName)
{
	DeleteAttribute(pchar, "showTimer");
	ClearAllLogStrings();
}

//создание резервной базы на абордажников для юза нефритового черепа
void CopyPassForAztecSkull()
{
	if (CheckCharacterItem(pchar, "SkullAztec"))
	{
        //сносим старую базу
        DeleteAttribute(pchar, "AztecSkull");
		pchar.AztecSkull = "";
		//заполняем архивную базу
		string sTemp;
		aref	arFromBox, arToBox;
    	makearef(arFromBox, pchar.fellows.passengers.officers);
		makearef(arToBox, pchar.AztecSkull);
		CopyAttributes(arToBox, arFromBox);
	}
}

bool IsAztecSkullOfficer(ref sld)
{
	if (!CheckAttribute(pchar, "AztecSkull.id1")) return false;
	string sTemp;
	aref arOfficer;
    makearef(arOfficer, pchar.AztecSkull);
    for (i=1; i<=MAX_NUM_FIGHTERS; i++)
    {
		sTemp = "id" + i;
		if (arOfficer.(sTemp) == sld.index)
		{
			return true;
		}
	}
	return false;
}

void SetAztecUsedTotem(ref _location, string _itemId, string _locator)
{
	//-----------------------------------------
	if (_itemId == "Totem_11")    //снимаем огонь
	{
		DeleteAttribute(_location, "gotoFire");
		Log_SetStringToLog("Заклятие огня снято");
		pchar.questTemp.Teno = "takeFire";
	}
	//-----------------------------------------
	if (_itemId == "Totem_12") //открываем каменный сундук в большом храме (с кинжалом)
	{
		DeleteAttribute(_location, "private1.closed");
		Log_SetStringToLog("Открыт каменный сундук");
	}
	//-----------------------------------------
	if (_itemId == "Totem_13") //снимаем огонь 2х
	{
		_location.lockFire.button02.active = true;
		if (CheckAttribute(_location, "lockFire.button02.active") && CheckAttribute(_location, "lockFire.button03.active"))
		{
			DeleteAttribute(_location, "gotoFire");
			Log_SetStringToLog("Заклятие огня снято");
			pchar.questTemp.Teno = "takeFire";
		}
	}
	if (_itemId == "Totem_14") //снимаем огонь 2х
	{
		_location.lockFire.button03.active = true;
		if (CheckAttribute(_location, "lockFire.button02.active") && CheckAttribute(_location, "lockFire.button03.active"))
		{
			DeleteAttribute(_location, "gotoFire");
			Log_SetStringToLog("Заклятие огня снято");
			pchar.questTemp.Teno = "takeFire";
		}
	}
	//-----------------------------------------
	if (_itemId == "Totem_15") //открываем каменный сундук в большом храме
	{
		DeleteAttribute(_location, "private2.closed");
		Log_SetStringToLog("Открыт каменный сундук");
	}
	//-----------------------------------------
	if (_itemId == "Totem_1" || _itemId == "Totem_2" || _itemId == "Totem_3" || _itemId == "Totem_4" || _itemId == "Totem_5" ||
		_itemId == "Totem_6" || _itemId == "Totem_7" || _itemId == "Totem_8" || _itemId == "Totem_9" || _itemId == "Totem_10")
	{
		int n;
		int num = 0;
		int locIndex = sti(_location.idxTeno); //индекс Теночтитлана
		string sTemp;
		_location.openGreatTemple = true;
		for (int i=1 ; i<=10; i++)
		{
			sTemp = "idx" + i;
			n = sti(locations[locIndex].temples.(sTemp));
			if (CheckAttribute(locations[n], "openGreatTemple")) num++;
		}
		if (num >= 10)
		{
			DeleteAttribute(&locations[locIndex], "reload.l32.disable");
			DeleteAttribute(&locations[locIndex], "reload.l33.disable");
			DeleteAttribute(&locations[locIndex], "reload.l34.disable");
			AddQuestRecord("Tenochtitlan", "7");
			pchar.questTemp.Teno = "takeSkull";
		}
	}
}

//бог мертвых разгневан
void LoginDeadmansGod()
{
	chrDisableReloadToLocation = true;
	LAi_group_SetRelation("teno_monsters_group", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	//ставим бога мертвых
	LAi_SetFightMode(pchar, false);
	LAi_LockFightMode(pchar, false);
	LAi_LocationFightDisable(loadedLocation, true);
	if (MOD_SKILL_ENEMY_RATE == 10 && bHardAnimations) ref sld = GetCharacter(NPC_GenerateCharacter("DeadmansGod", "mictlantecuhtli", "skeleton", "spy", 100, PIRATE, 0, true));
	else sld = GetCharacter(NPC_GenerateCharacter("DeadmansGod", "mictlantecuhtli", "skeleton", "man_fast", 100, PIRATE, 0, true));
    FantomMakeCoolFighter(sld, 100, 100, 100, "toporAZ", "pistol5", 3000);
	sld.name = "Миктлантекутли";
	sld.lastname = "";
	sld.dialog.filename   = "Quest\Mictlantecuhtli.c";
	sld.dialog.currentnode   = "InGreateTemple";
	if (bHardBoss) sld.AlwaysReload = true;//перезарядка независимо от Дозарядки
	ChangeCharacterAddressGroup(sld, "Temple_great", "goto", "goto1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0.0, 0);
	LAi_CharacterPlaySound(sld, "DeadmansGod");
}

void LoginDeadmansGod2()
{
	if (MOD_SKILL_ENEMY_RATE == 10 && bHardAnimations) ref sld = GetCharacter(NPC_GenerateCharacter("DeadmansGod2", "mictlantumsamil", "skeleton", "spy", 60, PIRATE, 0, true)); // LEO: Превозмогаторам - страдать 01.12.2021
	else sld = GetCharacter(NPC_GenerateCharacter("DeadmansGod2", "mictlantumsamil", "skeleton", "man_fast", 60, PIRATE, 0, true));
    FantomMakeCoolFighter(sld, 60, 100, 100, "blade201", "", 2500);
	sld.name = "Юм";
	sld.lastname = "Самиль";
	sld.vampire = true;
	sld.SaveItemsForDead = true;
	if (bHardBoss) sld.AlwaysReload = true;//перезарядка независимо от Дозарядки
	ChangeCharacterAddressGroup(sld, "treasure_alcove", "goto", "goto3");
	LAi_CharacterPlaySound(sld, "DeadmansGod");
	LAi_group_MoveCharacter(sld, "evil");
	LAi_group_SetRelation("evil", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("evil", LAI_GROUP_PLAYER, true);
	LAi_SetFightMode(sld, true);
	LAi_SetCheckMinHP(sld, 5.0, true, "UmSamilDefeated");
}

void LoginUmSamilGuards()
{
	chrDisableReloadToLocation = true;
	for(int i = 0; i < 3; i++)
	{
		if (MOD_SKILL_ENEMY_RATE == 10 && bHardAnimations) ref sld = GetCharacter(NPC_GenerateCharacter("UmSamilGuard"+i, "Chavinavi_1", "skeleton", "spy", 55, PIRATE, 0, true)); // LEO: Превозмогаторам - страдать 01.12.2021
		else sld = GetCharacter(NPC_GenerateCharacter("UmSamilGuard"+i, "Chavinavi_1", "skeleton", "man_fast", 55, PIRATE, 0, true));
		if (i == 0) FantomMakeCoolFighter(sld, 55, 90, 90, "blade37", "", 750);
		if (i == 1) FantomMakeCoolFighter(sld, 55, 90, 90, "blade39", "", 750);
		if (i == 2) FantomMakeCoolFighter(sld, 55, 90, 90, "blade42", "", 750);
		sld.name = "Воин-Ягуар";
		sld.lastname = "";
		sld.vampire = true;
		if (bHardBoss) sld.AlwaysReload = true;//перезарядка независимо от Дозарядки
		if (i == 0) ChangeCharacterAddressGroup(sld, "treasure_alcove", "goto", "monster1");
		if (i == 1) ChangeCharacterAddressGroup(sld, "treasure_alcove", "goto", "monster4");
		if (i == 2) ChangeCharacterAddressGroup(sld, "treasure_alcove", "goto", "monster3");
		LAi_group_MoveCharacter(sld, "evil_");
		LAi_group_SetRelation("evil_", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("evil_", LAI_GROUP_PLAYER, true);
		LAi_SetFightMode(sld, true);
	}
	LAi_group_SetCheck("evil_", "UmSamilGuardsDefeated");
}

void SpawnFishHeads()
{
	int stopp = 0;
	//chrDisableReloadToLocation = true;
	for(int i = 0; i < 36; i++)
	{
		if (stopp == 1) {stopp = 0; continue;}
		ref sld = GetCharacter(NPC_GenerateCharacter("FishHead"+i, GetRandSkelModel(), "skeleton", "man", 55, PIRATE, 0, true));
		FantomMakeCoolFighter(sld, 25, 90, 90, "blade42", "", 300);
		sld.name = "Рыболюд";
		sld.lastname = "";
		ChangeCharacterAddressGroup(sld, "Bermudes_Dungeon", "monsters", "monster"+i);
		LAi_group_MoveCharacter(sld, "evilf_");
		LAi_group_SetRelation("evilf_", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("evilf_", LAI_GROUP_PLAYER, true);
		LAi_SetFightMode(sld, true);
		sld.lifeDay = 0;
		stopp = 1;
	}
	LAi_group_SetCheck("evilf_", "FishHeadsDefeated");
}

void SpawnGreedyBastards()
{
	chrDisableReloadToLocation = true;
	int iCount = makeint(MOD_SKILL_ENEMY_RATE/2+0.5);
	if (sti(pchar.rank) < 3 && iCount > 2) iCount = 1; //казуалам не набьют ебало сразу
	if (iCount<1) iCount = 1;
	for(int i = 0; i < iCount; i++)
	{
		ref sld = GetCharacter(NPC_GenerateCharacter("GreedyBastard_"+pchar.location+"_"+i, "panhandler_"+(rand(4)+1), "man", "man", 5+makeint(sti(pchar.rank)/3), PIRATE, 0, true));
		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
		LAi_group_Delete("greedybastard");
		LAi_group_MoveCharacter(sld, "greedybastard");

		if (i!=0)
		{
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		}
		else
		{
			sld.quant = iCount;
			switch (rand(14))
			{
				case 0: sld.name = "Ери"; sld.lastname = "Лейн"; break;
				case 1: sld.name = "Фри"; sld.lastname = "Тиз"; break;
				case 2: sld.name = "Роман"; sld.lastname = "Войсович"; break;
				case 3: sld.name = "Семён"; sld.lastname = "Семёныч"; break;
				case 4: sld.name = "Капитан"; sld.lastname = "Дилл Доу"; break;
				case 5: sld.name = "Шах"; sld.lastname = "Аран"; break;
				case 6: sld.name = "Грег"; sld.lastname = "де Грим"; break;
				case 7: sld.name = "Скэм"; sld.lastname = "Геймс"; break;
				case 8: sld.name = "Скар"; sld.lastname = "Хэд"; break;
				case 9: sld.name = "Гуг"; sld.lastname = "Мэн"; break;
				case 10: sld.name = "Асар"; sld.lastname = "Дагон"; break;
				case 11: sld.name = "Сиб"; sld.lastname = "Иряк"; break;
				case 12: sld.name = "Дио"; sld.lastname = "Диегович"; break;
				case 13: sld.name = "Син"; sld.lastname = "Истра"; break;
				case 14: sld.name = "Лип"; sld.lastname = "Сар"; break;
			}
			LAi_SetActorTypeNoGroup(sld);
			sld.dialog.filename = "GenQuests_dialog.c";
			sld.dialog.currentnode = "Greedy";
			LAi_ActorDialog(sld, pchar, "", 10.0, 0);
		}
	}
	LAi_group_SetCheck("greedybastard", "OpenTheDoors");
}

//проверка на наличие тотемов в ГГ и их использование ранее
bool CheckMainHeroTotem(string itemName)
{
    if( CheckAttribute(pchar,"Items."+itemName) && sti(pchar.Items.(itemName))>0 )
	{
		return true;
	}
	else
	{
		for (int i=Totems_start; i<Totems_end; i++)
		{
			if (Items[i].id == itemName)
			{
				if (CheckAttribute(&Items[i], "shown.used"))
				{
					return true;
				}
				break;
			}
		}
	}
	return false;
}

// --> ugeen 20.06.09 - проверка на наличие карт у ГГ
bool CheckMainHeroMap(string itemName)
{
    if( CheckAttribute(pchar,"Items."+itemName) && sti(pchar.Items.(itemName))>0 )
	{
		return true;
	}
	return false;
}
// <-- ugeen
void LoginShotgunGuards()
{
	ref sld;
	if (pchar.questTemp.Teno != "YouWinGod")
	{
		LAi_group_Delete("EnemyFight");
		chrDisableReloadToLocation = true;
		for (i=1; i<=8; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("AztecWarrior_"+i, "AztecWarrior"+(rand(4)+1), "skeleton", "man", 30, PIRATE, 0, true));
			FantomMakeCoolFighter(sld, 30, 90, 90, "toporAZ", "", 100);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto"+i);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
		}
	}
}

// Инициализация прочих квестов. Warship
void OtherQuestCharactersInit()
{
	ref sld;

	// Квест "Помощь Андрэ Абелю"
	/*sld = GetCharacter(NPC_GenerateCharacter("Andre_Abel" , "officer_19", "man", "man", 10, FRANCE, -1, true));
	FantomMakeCoolFighter(sld, 10, 30, 35, "blade14", "pistol2", 10);
	FantomMakeCoolSailor(sld, SHIP_FLEUT, "Орион", CANNON_TYPE_CANNON_LBS16, 30, 30, 30);
	sld.name = "Андрэ";
	sld.lastname = "Абель";
	sld.SaveItemsForDead = true; // сохранять на трупе вещи
	sld.DontClearDead = true; // не убирать труп через 200с
	sld.dialog.FileName = "Quest\Andre_Abel_Dialog.c";
	sld.greeting = "cit_quest";
	LAi_SetSitType(sld);
	LAi_SetImmortal(sld, true);	// До поры нельзя убить
	SetCharacterGoods(sld, GOOD_SILK, 700);
	SetCharacterGoods(sld, GOOD_TOBACCO, 500);
	ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "sit", "sit7");*/
}

// Warship 07.07.09 Пасхалка - бригантина "Мэри Селест"
void MaryCelesteInit()
{
	ref character, realShip;
	String capID = "MaryCelesteCapitan";
	String seaGroup = "MaryCelesteGroup";
	int good;

	// Сцуко.. В функции низя делать как generableGoods[15] = { GOOD_FOOD, GOOD_WEAPON, ... }; - дает ошибку
	// Если вынести из функции, то все норм
	/*int generableGoods[15] = { GOOD_FOOD, GOOD_WEAPON, GOOD_MAHOGANY, GOOD_MEDICAMENT, GOOD_SILK,
		GOOD_SANDAL, GOOD_COFFEE, GOOD_CLOTHES, GOOD_EBONY, GOOD_TOBACCO,
		GOOD_CHOCOLATE, GOOD_WINE, GOOD_RUM, GOOD_CINNAMON, GOOD_LEATHER };*/

	int generableGoods[15];

	generableGoods[0] = GOOD_FOOD;
	generableGoods[1] = GOOD_WEAPON;
	generableGoods[2] = GOOD_MAHOGANY;
	generableGoods[3] = GOOD_MEDICAMENT;
	generableGoods[4] = GOOD_SILK;
	generableGoods[5] = GOOD_SANDAL;
	generableGoods[6] = GOOD_COFFEE;
	generableGoods[7] = GOOD_CLOTHES;
	generableGoods[8] = GOOD_EBONY;
	generableGoods[9] = GOOD_TOBACCO;
	generableGoods[10] = GOOD_CHOCOLATE;
	generableGoods[11] = GOOD_WINE;
	generableGoods[12] = GOOD_RUM;
	generableGoods[13] = GOOD_CINNAMON;
	generableGoods[14] = GOOD_LEATHER;

	character = GetCharacter(NPC_GenerateCharacter(capID , "Pirate_5", "man", "man", 50, ENGLAND, -1, true));
//	FantomMakeCoolFighter(character, 50, 50, 45, "blade34", "pistol5", 50);
	FantomMakeCoolSailor(character, SHIP_BRIGANTINE, "Мэри Селест", CANNON_TYPE_CANNON_LBS24, 50, 50, 50);
	character.name = "Корабль пуст";
	character.lastname = "";
	character.mapEnc.type = "trade";
	character.mapEnc.Name = "бригантина 'Мэри Селест'";
	LAi_SetImmortal(character, true);
	SetCharacterGoods(character, GOOD_RUM, 700);
	Character_SetAbordageEnable(character, false); // Низя абордировать

	SetCrewQuantityOverMax(character, 0); // Никого живого

	realShip = GetRealShip(GetCharacterShipType(character));

	PChar.QuestTemp.MaryCeleste = "NotFind";
	PChar.QuestTemp.MaryCeleste.TurnRate = realShip.TurnRate; // Запомним, потом восстановим для интерфейса

	realShip.lowpolycrew = 0; // Нету никого на палубе
	realShip.TurnRate = 1; // Чтоб не особо изворотливым был
	realShip.capacity = 2820;

	NullCharacterGoods(character); // Нулим товары в трюме

	AddCharacterGoodsSimple(character, GOOD_BALLS, 200 + rand(50));
	AddCharacterGoodsSimple(character, GOOD_GRAPES, 200 + rand(50));
	AddCharacterGoodsSimple(character, GOOD_KNIPPELS, 200 + rand(50));
	AddCharacterGoodsSimple(character, GOOD_BOMBS, 200 + rand(50));
	AddCharacterGoodsSimple(character, GOOD_POWDER, 500 + rand(50));
	AddCharacterGoodsSimple(character, GOOD_FOOD, 50 + rand(50));
	AddCharacterGoodsSimple(character, GOOD_WEAPON, 20 + rand(30));
	AddCharacterGoodsSimple(character, GOOD_MEDICAMENT, 10 + rand(20));
	AddCharacterGoodsSimple(character, GOOD_SAILCLOTH, 50 + rand(50));
	AddCharacterGoodsSimple(character, GOOD_PLANKS, 20 + rand(30));

	good = generableGoods[rand(14)];
	// GetCharacterFreeSpace(ref _refCharacter,int _Goods) - вернет сколько можно положить данного товара в трюм персонажу
	AddCharacterGoodsSimple(character, good, GetCharacterFreeSpace(character, good) - 1);

	character.AlwaysFriend = true; // Друзья навек
	character.ShipEnemyDisable = true; // Флаг не обижаться на выстрелы
	character.CanDropSails = false; // Низя спускать паруса

	Group_FindOrCreateGroup(seaGroup);
	Group_SetTaskAttackInMap(seaGroup, PLAYER_GROUP);
	Group_LockTask(seaGroup);
	Group_AddCharacter(seaGroup, capID);
	Group_SetGroupCommander(seaGroup, capID);
	SetRandGeraldSail(character, ENGLAND);

	character.fromCity = SelectAnyColony(""); // Колония, из бухты которой выйдет
	character.fromShore = GetIslandRandomShoreId(GetArealByCityName(character.fromCity));
	character.toCity = SelectAnyColony(character.fromCity); // Колония, в бухту которой придет
	character.toShore = GetIslandRandomShoreId(GetArealByCityName(character.toCity));

	Map_CreateTrader(character.fromShore, character.toShore, capID, GetMaxDaysFromIsland2Island(GetArealByCityName(character.toCity), GetArealByCityName(character.fromCity)));

	trace("Бригантина Мэри Селест вышла из " + character.fromCity + " и направилась в " + character.toShore);
}
