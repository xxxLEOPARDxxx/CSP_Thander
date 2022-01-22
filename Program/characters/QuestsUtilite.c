// строковая дата, день_мес
string LastSpeakDate()
{
    return environment.date.day + " " + environment.date.month;
}
// Для диалогов НПС -->
string GetNPCQuestDate(ref npchar, string _type)
{
    if (!CheckAttribute(npchar, "QuestDate." + _type))
    {
        npchar.QuestDate.(_type) = "";
    }
    return npchar.QuestDate.(_type);
}
void SetNPCQuestDate(ref npchar, string _type)
{
    npchar.QuestDate.(_type) = LastSpeakDate();
}
bool CheckNPCQuestDate(ref npchar, string _type)
{
    if (GetNPCQuestDate(npchar, _type) != LastSpeakDate())
    {
        return true;
    }
    return false;
}
// Для ГГ <--
void SaveCurrentQuestDateParam(string _quest)
{ // запись даты получения квеста
    aref  arQ;
    makearef(arQ, PChar.(_quest));

    arQ.control_day = GetDataDay();
    arQ.control_month = GetDataMonth();
    arQ.control_year = GetDataYear();
    arQ.control_time = GetTime();
}
int GetQuestPastMonthParam(string _quest)
{
    aref  arQ;
    makearef(arQ, PChar.(_quest));

    return GetPastTime("month", sti(arQ.control_year), sti(arQ.control_month), sti(arQ.control_day), stf(arQ.control_time),GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());
}
int GetQuestPastDayParam(string _quest)
{
    aref  arQ;
    makearef(arQ, PChar.(_quest));
    if (CheckAttribute(PChar, _quest + ".control_year"))
    {
    	return GetPastTime("day", sti(arQ.control_year), sti(arQ.control_month), sti(arQ.control_day), stf(arQ.control_time),GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());
	}
	return 0;
}
int GetQuestPastTimeParam(string _quest)
{
    aref  arQ;
    makearef(arQ, PChar.(_quest));
    if (CheckAttribute(PChar, _quest + ".control_year"))
    {
    	return GetPastTime("hour", sti(arQ.control_year), sti(arQ.control_month), sti(arQ.control_day), stf(arQ.control_time), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());
	}
	return 0;
}
//navy -->
//Ввел еще одну функцию, т.к. нужны прошедшие минуты.
int GetQuestPastMinutesParam(string _quest)
{
    aref  arQ;
    makearef(arQ, PChar.(_quest));
    if (CheckAttribute(PChar, _quest + ".control_year"))
    {
    	return GetPastTime("minute", sti(arQ.control_year), sti(arQ.control_month), sti(arQ.control_day), stf(arQ.control_time), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());
	}
	return 0;
}
//navy <--

// eddy
// ************* для неписей.
void SaveCurrentNpcQuestDateParam(ref _character, string _quest)
{ // запись даты получения квеста
    aref  arQ;
    makearef(arQ, _character.(_quest));

    arQ.control_day = GetDataDay();
    arQ.control_month = GetDataMonth();
    arQ.control_year = GetDataYear();
    arQ.control_time = GetTime();
}

int GetNpcQuestPastDayParam(ref _character, string _quest)
{
    aref  arQ;
    makearef(arQ, _character.(_quest));
    if (CheckAttribute(_character, _quest + ".control_year"))
    {
        return GetPastTime("day", sti(arQ.control_year), sti(arQ.control_month), sti(arQ.control_day), 0,GetDataYear(), GetDataMonth(), GetDataDay(), 0);
    }
    else {return 0;}
}

int GetNpcQuestPastDayWOInit(ref _character, string _quest)
{
    aref  arQ;
    makearef(arQ, _character.(_quest));
    if (CheckAttribute(_character, _quest + ".control_year"))
    {
        return GetPastTime("day", sti(arQ.control_year), sti(arQ.control_month), sti(arQ.control_day), 0,GetDataYear(), GetDataMonth(), GetDataDay(), 0);
    }
    else {return 1000;}  // если нет ветки, то это значит черти когда было дело
}

int GetNpcQuestPastTimeParam(ref _character, string _quest)
{
    aref  arQ;
    makearef(arQ, _character.(_quest));
    if (CheckAttribute(_character, _quest + ".control_year"))
    {
    	return GetPastTime("hour", sti(arQ.control_year), sti(arQ.control_month), sti(arQ.control_day), sti(arQ.control_time), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());
	}
	return 0;
}
int GetNpcQuestPastMinutesParam(ref _character, string _quest)
{
    aref  arQ;
    makearef(arQ, _character.(_quest));
    if (CheckAttribute(_character, _quest + ".control_year"))
    {
    	return GetPastTime("minute", sti(arQ.control_year), sti(arQ.control_month), sti(arQ.control_day), stf(arQ.control_time), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());
	}
	return 0;
}

int GetNpcQuestPastMonthParam(ref _character, string _quest)
{
    aref  arQ;
    makearef(arQ, _character.(_quest));
    if (CheckAttribute(_character, _quest + ".control_year"))
    {
        return GetPastTime("month", sti(arQ.control_year), sti(arQ.control_month), sti(arQ.control_day), 0,GetDataYear(), GetDataMonth(), GetDataDay(), 0);
    }
    else {return 0;}
}
// Поместить непися в компаньоны и тут же отправить его на выход из текущей локации.
void CharacterIntoCompanionAndGoOut(ref _mainCharacter, ref _compCharacter, string _group, string _locator, int _timeToGoOut, bool _compRemove)
{
    if (!bDisableFastReload) //чтобы не снимать запрет, если он установлен другим методом
	{
		bDisableFastReload = true;
		_mainCharacter.GenQuest.CallFunctionParam.CharacterIntoCompanion.FastReload = true;
	}
	if (_group == "")    {_group = "reload";}
    if (_locator == "")
    {
    	float locx, locy, locz;
        GetCharacterPos(_compCharacter, &locx, &locy, &locz);
        _locator = LAi_FindNearestFreeLocator(_group, locx, locy, locz);
    }
    LAi_ActorGoToLocation(_compCharacter, _group, _locator, "none", "", "", "", _timeToGoOut);
    _mainCharacter.GenQuest.CallFunctionParam = "Character_into_companion";
    _mainCharacter.GenQuest.CallFunctionParam.CharacterIntoCompanion.Id = _compCharacter.id;
    _mainCharacter.GenQuest.CallFunctionParam.CharacterIntoCompanion.Remove = _compRemove;
    DoQuestCheckDelay("CallFunctionParam", _timeToGoOut);
}

void Character_into_companion()    // относится к методу выше.
{
    ref NPChar = characterFromID(PChar.GenQuest.CallFunctionParam.CharacterIntoCompanion.Id);
    SetCompanionIndex(pchar, -1, getcharacterIndex(PChar.GenQuest.CallFunctionParam.CharacterIntoCompanion.Id));
    if (PChar.GenQuest.CallFunctionParam.CharacterIntoCompanion.Remove == false)    {SetCharacterRemovable(npchar, false);}
	//снимать запрет, только если он установлен этим методом
	if (CheckAttribute(PChar, "GenQuest.CallFunctionParam.CharacterIntoCompanion.FastReload")) bDisableFastReload = false;
}

string GetBookData(int day, int mn, int year)
{
	string result = "";

	if (day < 10)
	{
	    result = result + "0";
	}
	result = result + day + ".";
	if (mn < 10)
	{
	    result = result + "0";
	}
	result = result + mn + "." + year;

    return result;
}

// ========>>>>>> квест Аззи, подсчет контрольных сумм по неуязвимости =================
void AzzyCheckSumControl()
{
    int   QtyKilled, Result;
    float CurHP, MaxHP;

	if (CheckAttribute(pchar, "questTemp.Azzy.Immortal"))
    {
        QtyKilled = Statistic_AddValue(pchar, "Solder_s", 0) +
                    Statistic_AddValue(pchar, "Solder_g", 0) +
                    Statistic_AddValue(pchar, "Warrior_s", 0) +
                    Statistic_AddValue(pchar, "Warrior_g", 0) +
                    Statistic_AddValue(pchar, "Citizen_s", 0) +
                    Statistic_AddValue(pchar, "Citizen_g", 0) +
                    Statistic_AddValue(pchar, "Monster_s", 0) +
                    Statistic_AddValue(pchar, "Monster_g", 0) -
                    sti(pchar.questTemp.Azzy.Immortal.EarlyKilled);
        pchar.questTemp.Azzy.Immortal.AllQuota = makeint(pchar.questTemp.Azzy.Immortal.AllQuota) + sti(pchar.questTemp.Azzy.Immortal.DayQuota);
        Result = QtyKilled - sti(pchar.questTemp.Azzy.Immortal.AllQuota);
        if (Result < 0)
        {
            MaxHP = LAi_GetCharacterMaxHP(pchar);
            CurHP = LAi_GetCharacterHP(pchar);
            MaxHP = MaxHP - 5;
            pchar.questTemp.Azzy.Immortal.Penalty = makeint(pchar.questTemp.Azzy.Immortal.Penalty) + 5;
            if (!CheckAttribute(pchar, "questTemp.Azzy.OK"))
            {
                pchar.questTemp.Azzy = "HowToKnowAzzy";
                pchar.questTemp.Azzy.OK = 1;
            }
            if (MaxHP < 1)
            {
                LAi_KillCharacter(pchar);
                Log_SetStringToLog("Сообщение из Ада: ваши жизненные силы были окончательно отобраны в счет оплаты наших услуг. Добро пожаловать в Ад.");
            }
            else
            {
                Log_SetStringToLog("Адское уведомление о штрафных санкциях. Пожалуйста, ознакомьтесь!");
            }
            LAi_SetHP(pchar, CurHP, MaxHP);
        }
        if (GetQuestPastDayParam("questTemp.Azzy.Immortal") > 30)
        {
            pchar.questTemp.Azzy.Immortal.DayQuota = makeint(pchar.questTemp.Azzy.Immortal.DayQuota) * 2;
            SaveCurrentQuestDateParam("questTemp.Azzy.Immortal");
        }
        pchar.questTemp.Azzy.Immortal.CurKilled = QtyKilled;
        pchar.questTemp.Azzy.Immortal.CurBalance = Result;
        DeleteQuestHeader("Azzy_HellSign");
		if (sti(pchar.questTemp.Azzy.Immortal.Penalty) > 0)
		{
			AddQuestRecord("Azzy_HellSign", "2");
			AddQuestUserData("Azzy_HellSign", "Penalty", pchar.questTemp.Azzy.Immortal.Penalty);
		}
		AddQuestRecord("Azzy_HellSign", "1");
		AddQuestUserData("Azzy_HellSign", "sName", GetMainCharacterNameGen());
		AddQuestUserData("Azzy_HellSign", "DayQuota", pchar.questTemp.Azzy.Immortal.DayQuota);
		AddQuestUserData("Azzy_HellSign", "AllQuota", pchar.questTemp.Azzy.Immortal.AllQuota);
		AddQuestUserData("Azzy_HellSign", "CurKilled", pchar.questTemp.Azzy.Immortal.CurKilled);
		AddQuestUserData("Azzy_HellSign", "CurBalance", pchar.questTemp.Azzy.Immortal.CurBalance);
    }
}
// <<<<<======== квест Аззи, подсчет контрольныйх сумм по неуязвимости =================

// репутация плохого парня с границами
bool isBadReputation(ref _pchar, int _rep)
{
    if (GetCharacterPerkUsing(_pchar, "Trustworthy") || sti(_pchar.reputation) >= _rep)
    {
        return false;// good guy
    }
    return true;// bad guy
}

// --> ugeen  - генерация карт островов в сундуке каюты во время абордажа   07.07.09
void FillCabinBoxMap(ref _location, int _probability)
{
	int 	i;
	string  itemID, groupID;
    ref     itm;

	for (i=0; i<ITEMS_QUANTITY; i++)
	{
		makeref(itm,Items[i]);
		if(CheckAttribute(itm, "ID") && CheckAttribute(itm, "groupID"))
		{
			itemID = itm.id;
			groupID = itm.groupID;
			if(groupID == MAPS_ITEM_TYPE && !CheckAttribute(itm, "mapSpecial") && (itemID != "Map_Best") && (itemID != "Map_LSC"))
			{
				if(rand(_probability) == 1)
				{
					_location.box1.items.(itemID) = 1;
					return;
				}
			}
		}
	}
}
//<-- ugeen

//ugeen --> заполнить сундук в трюме квестовым барахлом
void FillQuestHoldBox(ref _location)
{
	_location.box1 = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear()); // нужно, чтоб не перетерлось

	int nShipType = sti(pchar.ship.type);

	if(CheckAttribute(pchar,"GenQuest.CaptainComission.CanFindChest"))
	{
		if(nShipType == sti(pchar.GenQuest.CaptainComission.ShipType) && !CheckAttribute(pchar,"GenQuest.CaptainComission.Treasure"))
		{
			Log_QuestInfo("Устанавливаем сундуки");
			DeleteAttribute(_location, "box1");
			_location.box1.items.chest = 3;
			pchar.GenQuest.CaptainComission.Treasure = true;
		}
	}
}
// <-- ugeen
// заполнить сундук каюты во время абордажа
void FillAboardCabinBox(ref _location, ref _npchar)
{
    int     iTemp;
    bool    ok;
	float   nLuck;
	int 	iNation;
	int     iRnd;
	_location.box1 = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());// нужно, чтоб не перетерлось
	// нужно отметить, что в сундуке сгенерятся рандомные вещи, этот код срабатывает потом и правит токо деньги
	ok = true;
	// заготовка под квест
	if (_npchar.id == "GhostCapt" && CheckAttribute(pchar , "GenQuest.GhostShip.LastBattle"))
	{
        // трем все в сундуке
        DeleteAttribute(_location, "box1");
        // кладем супер хрень
        _location.box1.items.indian11 = 1;
        _location.box1.money = 66666;
		//Добавить Иону
		if (!CheckAttribute(pchar , "questTemp.IonaGathered"))
		{
			 _location.box1.items.talisman2 = 1;
		}
        /*if (CheckAttribute(PChar, "GenQuest.GhostShip.TakeShotgun"))
        {
            DeleteAttribute(PChar, "GenQuest.GhostShip.TakeShotgun");
            _location.box1.items.pistol7 = 1;
        }*/
        ok = false;
	}
	if (HasSubStr(_npchar.id,"Hunter01") && !CheckAttribute(pchar,"BermudesSurprise"))
	{
		_location.box1.items.letter_notes = 1;
		ChangeItemDescribe("letter_notes", "CSPD1");
		pchar.BermudesSurprise = 1;
	}
	// пасхалка Кукурузина
	/*if (CheckAttribute(_npchar, "Ship.Name") && _npchar.Ship.Name == FUNY_SHIP_NAME)
	{
        // не трем все в сундуке
        _location.box1.items.mineral4 = 25;
        ok = false;
        PChar.questTemp.FUNY_SHIP_FIND = true;
	}       */
	// маленькая пасхалка от меня -> ugeen  17.06.09

	if (CheckAttribute(_npchar, "Ship.Name") && _npchar.Ship.Name == "Кoлecо Фoртуны" )
	{
		DeleteAttribute(_location, "box1");
		if(drand(100) > 85)
		{
			if(rand(1) == 0) { _location.box1.items.jewelry1 = rand(1500) + 461; }
			if(rand(1) == 0) { _location.box1.items.jewelry2 = rand(800) + 1214; }
			if(rand(1) == 0) { _location.box1.items.jewelry3 = rand(2210) + 750; }
			if(rand(1) == 0) { _location.box1.items.jewelry4 = rand(3450) + 280; }
			if(rand(1) == 0) { _location.box1.items.jewelry5 = rand(2471) + 370; }
			iRnd = drand(4);
			switch (iRnd)
			{
				case 0:
					_location.box1.items.indian18 = 1;
				break;
				case 1:
					_location.box1.items.indian21 = 1;
				break;
				case 2:
					_location.box1.items.indian20 = 1;
				break;
				case 3:
					_location.box1.items.indian11 = 1;
				break;
				case 4:
					_location.box1.items.indian6 = 1;
				break;
			}
		}
		else
		{
			if(rand(1) == 0) { _location.box1.items.mineral4 = rand(118) + 85; }
			_location.box1.items.mineral5 = rand(78) + 115;
			if(rand(1) == 0) { _location.box1.items.mineral8 = rand(86) + 44; }
			_location.box1.items.mineral11 = rand(146) + 131;
		}
		_location.box1.money = 12560 + rand(1000);
		ok = false;
	}
	// квест №4, англ., боевка с голландским бригом
	if (_npchar.id == "CaptainAttack_1" && CheckAttribute(PChar, "questTemp.EngLineQ4_PutLetter"))
	{
        DeleteAttribute(_location, "box1");
        ChangeItemDescribe("letter_1", "itmdescr_letter_1_EngLineQ4");
        _location.box1.items.letter_1 = 1;
        _location.box1.money = 7460;
        _location.box1.items.map_Curacao = 1;
        ok = false;
	}
	// квест №6, англ., боевка с испанским пинасом
	if (_npchar.id == "CaptainAttack_1" && CheckAttribute(PChar, "questTemp.EngLineQ6_PutMoney"))
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 140000;
        _location.box1.items.map_venesuela = 1;
        _location.box1.items.spyglass3 = 1;
        _location.box1.items.potion4 = 10;
        _location.box1.items.indian7 = 1;
        ok = false;
	}
    // квест №8, англ., боевка с испанским галеоном
    if (_npchar.id == "CaptainAttack_1" && CheckAttribute(PChar, "questTemp.ELQ8_PutLetter"))
	{
        DeleteAttribute(_location, "box1");
        ChangeItemDescribe("letter_2", "itmdescr_letter_2_EngLineQ8");
        _location.box1.items.letter_2 = 1;
        _location.box1.money = 2203;
        _location.box1.items.map_cuba = 1;
        _location.box1.items.spyglass2 = 1;
        _location.box1.items.potion2 = 7;
        _location.box1.items.potionwine = 2;
        ok = false;
	}
    // квест №9, англ., боевка с Пардалем
    if (_npchar.id == "CaptainAttack_1" && CheckAttribute(PChar, "questTemp.ELQ9_Diffrent"))
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 853000;
        _location.box1.items.blade28 = 1;
        _location.box1.items.pistol6 = 1;
        _location.box1.items.pistol4 = 1;
        _location.box1.items.potion4 = 10;
        _location.box1.items.chest = 1;
        _location.box1.items.icollection = 1;
        _location.box1.items.map_cuba = 1;
        _location.box1.items.jewelry4 = 25;
        _location.box1.items.cirass4 = 1;
        ok = false;
	}
    // квест №7, испанка , выручаем Пардаля, сундук кэпа флибустьеров
    if (_npchar.id == "CaptainAttack_1" && CheckAttribute(PChar, "questTemp.SLQ7_Diffrent"))
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 753400;
        _location.box1.items.blade28 = 1;
        _location.box1.items.pistol6 = 1;
        _location.box1.items.pistol4 = 1;
        _location.box1.items.potion2 = 10;
        _location.box1.items.potionwine = 1;
        _location.box1.items.jewelry4 = 25;
        _location.box1.items.cirass4 = 1;
		_location.box1.items.cirass3 = 1;
        ok = false;
	}
    // квест №8, испанка , защищаем Куману, сундук кэпа флибустьеров
    if (_npchar.id == "CaptainAttack_1" && CheckAttribute(PChar, "questTemp.SLQ8_Diffrent"))
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 996400;
        _location.box1.items.spyglass4 = 1;
        _location.box1.items.potionrum = 2;
        _location.box1.items.pistol4 = 5;
        _location.box1.items.potion3 = 11;
        _location.box1.items.chest = 1;
        _location.box1.items.icollection = 1;
        _location.box1.items.jewelry5 = 50;
		_location.box1.items.indian13 = 1;
        ok = false;
	}
	// квест Аскольда.
	if (CheckAttribute(PChar, "questTemp.Ascold.Ship"))
	{
        if (_npchar.id == pchar.questTemp.Ascold.Ship)
        {
            DeleteAttribute(_location, "box1");
            _location.box1.items.ShipsJournal = 1;
            ok = false;
        }
	}
	// Осады  homo 22/10/06
	if (findsubstr(_npchar.id, "SiegeCap_" , 0) != -1)
	{
	    aref aData, itm;
	    makearef(aData, NullCharacter.Siege);
	    string sGroup = "Sea_"+NationShortName(sti(aData.nation))+"SiegeCap_1";
	    ref rchar = Group_GetGroupCommander(sGroup);  //поиск текущего командера, он меняется от убиеня
	    Log_TestInfo( _npchar.id +" == "+ rchar.id);
		if (_npchar.id == rchar.id && CheckAttribute(aData, "loot"))
		{
	        DeleteAttribute(_location, "box1");
	        _location.box1.money = sti(aData.loot);
	        _location.box1.items.potionrum = 3;
	        _location.box1.items.potionwine = 1;
	        _location.box1.items.Food1 = rand(2);
	        _location.box1.items.Food2 = rand(2);
	        _location.box1.items.Food3 = rand(2);
	        _location.box1.items.Food4 = rand(2);
	        string idmap = "map_"+aData.island;
            if (Items_FindItem(idmap, &itm) != -1)
            {
                _location.box1.items.(idmap) = 1;
            }

	        ok = false;
		}
	}
	//homo =>
    if (findsubstr(_npchar.id, "_QuestMerchant" , 0) != -1)
    {
        if (trap)
        {
            DeleteAttribute(_location, "box1");
            _location.box1.money = (cRand(30)+1) * 40;
            _location.box1.items.blade31 = 1;
            ok = false;
        }
    }

    if (_npchar.id == "Head_of_Gold_Squadron" )
    {

        DeleteAttribute(_location, "box2");
        _location.box2.money = 2212;
        _location.box2.items.map_normal = 1;
        ok = false;

    }
    //homo <=
    // пиратка, квест №7. драгоценности в каюту
    if (_npchar.id == "QuestCap_PL7")
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 3983;
        _location.box1.items.jewelry1 = 763;
        _location.box1.items.jewelry2 = 562;
        _location.box1.items.jewelry3 = 1771;
        _location.box1.items.jewelry4 = 678;
        _location.box1.items.jewelry6 = 236;
        _location.box1.items.jewelry7 = 321;
        _location.box1.items.jewelry14 = 121;
		_location.box1.items.jewelry15 = 45;
		_location.box1.items.jewelry18 = 311;
        ok = false;
	}
    // пиратка, квест №7. драгоценности в каюту
    if (_npchar.id == "MushketCap")
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 103;
		_location.box1.items.mushket2x2 = 1;
		//Пернатый Змей
		_location.box1.items.talisman1 = 1;
        ok = false;
	}
	 if (_npchar.id == "BlackBeardNPC" && CheckAttribute(pchar, "Titch_seabattle"))
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 500000;
		_location.box1.items.blackbeard_sword_baron = 1;
		_location.box1.items.howdah = 1;
		_location.box1.items.spyglass5 = 1;
		_location.box1.items.cirass5 = 1;
        ok = false;
	}
	//работорговец, 2 эпизод
	if (_npchar.id == "CaptainSlaveAttack_2" && CheckAttribute(PChar, "questTemp.Slavetrader"))
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 20000;
		_location.box1.items.statue1 = 1;
        ok = false;
	}
	//работорговец, письмо, 4 эпизод
	if (_npchar.id == "CapBrigAttack" && CheckAttribute(PChar, "questTemp.Slavetrader"))
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 5500;
		_location.box1.items.letter_1 = 1;
        ok = false;
	}
	//работорговец, линкор
	if (_npchar.id == "GaleonCap" && CheckAttribute(PChar, "questTemp.Slavetrader"))
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 2350;
		_location.box1.items.jewelry5 = 1000;
		DeleteAttribute(_location, "box2");
		_location.box2.items.indian15 = 1;
		_location.box2.items.indian8 = 528;
		_location.box2.items.indian9 = 9;
		_location.box2.items.indian2 = 3;
		_location.box2.items.indian14 = 16;
		DeleteAttribute(_location, "box3");
		_location.box3.items.indian5 = 2;
		_location.box3.items.indian16 = 114;
		_location.box3.items.indian13 = 58;
		_location.box3.items.indian12 = 1;
		_location.box3.items.indian1 = 1;
        ok = false;
	}

	//малява курьер
	if (_npchar.id == "CureerAttack")
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 1000;
        _location.box1.items.jewelry1 = 50+rand(200);
        _location.box1.items.jewelry2 = 50+rand(100);
        _location.box1.items.jewelry3 = 50+rand(100);
        _location.box1.items.jewelry4 = 50+rand(100);
        _location.box1.items.jewelry6 = 50+rand(80);
        _location.box1.items.jewelry7 = 50+rand(100);
		_location.box1.items.jewelry10 = 50+rand(160);
        _location.box1.items.jewelry14 = 50+rand(150);
		_location.box1.items.jewelry15 = rand(40);
		_location.box1.items.jewelry18 = rand(200);
		DeleteAttribute(_location, "box2");
		iRnd = rand(5);
			switch (iRnd)
			{
				case 0:
					_location.box2.items.cirass4 = 1;
				break;
				case 1:
					_location.box2.items.spyglass4 = 1;
				break;
				case 2:
					_location.box2.items.pistol5 = 1;
				break;
				case 3:
					_location.box2.items.blade34 = 1;
				break;
				case 4:
					_location.box2.items.blade19 = 1;
				break;
				case 5:
					_location.box2.items.pistol4 = 1;
				break;
			}
        ok = false;
	}
	//ОЗГ, пинас Крысы, драгоценности
	if (_npchar.id == "RatCaptain" && CheckAttribute(PChar, "questTemp.Headhunter"))
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 21500;
		_location.box1.items.icollection = rand(2);
		_location.box1.items.jewelry1 = 20+rand(20);
        _location.box1.items.jewelry2 = 20+rand(20);
        _location.box1.items.jewelry3 = 30+rand(20);
        _location.box1.items.jewelry4 = 10+rand(10);
        _location.box1.items.jewelry6 = rand(50);
        _location.box1.items.jewelry7 = rand(100);
		_location.box1.items.jewelry10 = rand(50);
        _location.box1.items.jewelry14 = rand(50);
		_location.box1.items.jewelry15 = rand(10);
		_location.box1.items.jewelry18 = rand(100);
        ok = false;
	}
	//Молот Тора + всякое на Нормандии
	if (_npchar.id == "zpqCaptain")
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 25000;
		// _location.box1.items.talisman3 = 1;
        ok = false;
	}
	if(_npchar.id == "Flint")
	{
		_location.box1.items.icollection = 3 + rand(5);
		_location.box1.items.indian1 = 1;
		_location.box1.items.indian7 = 1;
		_location.box1.items.chest = 5 + rand(10);
		_location.box1.items.jewelry1 = 40+rand(5);
		_location.box1.items.jewelry2 = 40+rand(5);
		_location.box1.items.jewelry3 = 40+rand(5);
		_location.box1.items.jewelry4 = 31+rand(5);
		_location.box1.items.jewelry6 = rand(50);
		_location.box1.items.jewelry7 = rand(100);
		_location.box1.items.jewelry10 = rand(50);
		_location.box1.items.jewelry14 = rand(50);
		_location.box1.items.jewelry15 = rand(10);
		_location.box1.items.jewelry18 = rand(100);
	}
	//Квест "Золото не тонет", английский галеон у Доминики, драгоценности
	if (_npchar.id == "PDM_Lesopilka_Galeon")
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 10000;
		_location.box1.items.jewelry1 = 20+rand(10);
        _location.box1.items.jewelry2 = 20+rand(10);
        _location.box1.items.jewelry3 = 30+rand(10);
        _location.box1.items.jewelry4 = 30+rand(10);
        _location.box1.items.jewelry5 = rand(80);
		_location.box1.items.PDM_SJ_Angl_Gal = 1);
        ok = false;
	}

    if (ok) // не квестовый
    {
    	// код для всех

		// Warship 02.07.09 Это прикол такой - можно у случайного кэпа в сундуке обраружить ключ от сундуков Моргана
		// Причем, сундуков у Моргана два, а открыть получится только один из них
		if(!CheckAttribute(PChar, "QuestTemp.MorganKeyTaken") && rand(250-(sti(pchar.rank) * 3)) == 5 && sti(pchar.rank)>10)
		{
			PChar.QuestTemp.MorganKeyTaken = true;
			_location.box1.items.keyMorgan = 1;
			Log_TestInfo("У этого кэпа в сундуке будет ключ Моргана!");
		}

		if(startherotype == 2 && !CheckCharacterItem(pchar,"glasses") && drand(100) < 25)
		{
			_location.box1.items.glasses = 1;
		}

		if(rand(50) == 0)
		{
			switch (rand(3))
			{
				case 0: _location.box1.items.Chest_ammo = 1; break;
				case 1: _location.box1.items.Chest_treasure = 1; break;
				case 2: _location.box1.items.Chest_quest = 1; break;
				case 3: _location.box1.items.Chest_Craftsmans = 1; break;
			}
			Log_TestInfo("xzibit");
		}
		if(rand(100) == 0)//Книги - Gregg
		{
			string book = "book2_"+(rand(13)+1);
			_location.box1.items.(book) = 1;
			Log_TestInfo("bookgen");
		}

		if(rand(200) == 0)
		{
			_location.box1.items.mushket_SeaCarbine = 1;
		}
    	iTemp = GetCharacterShipClass(_npchar);
		iNation = sti(_npchar.nation);

		if(iNation == PIRATE)
		{
			nLuck   = GetCharacterSkillToOld(Pchar, SKILL_FORTUNE);
			if (nLuck > rand(250) && GetCharacterItem(pchar, "map_full") == 0)  // шанс 1/30
			{
				if (GetCharacterItem(pchar, "map_part1") == 0)
				{
					_location.box1.items.map_part1 = 1;
				}
				else
				{
					if (GetCharacterItem(pchar, "map_part2") == 0)
					{
						_location.box1.items.map_part2 = 1;
					}
				}
			}
			FillCabinBoxMap(_location, 200 - (7 - iTemp) * 5);
		}
		else
		{
			FillCabinBoxMap(_location, 250 - (7 - iTemp) * 5);
		}

		if (CheckAttribute(_npchar, "Ship.Mode") && _npchar.Ship.Mode == "Trade")  // торговец
		{
			_location.box1.money = (10 - iTemp) * 200 + rand(10 - iTemp) * 2000 + rand(10)*50 + rand(6 - iTemp) * 4000;
		}
		else // все остальные
		{
			_location.box1.money = (10 - iTemp) * 90 + rand((10 - iTemp) * 2000);
		}
    }
}

// ugeen --> вычисление ранга квестовых проитвников в зависимости от ранга ГГ и уровня сложности
int SetQuestCharacterRank()
{
	int rank = 25 + makeint(sti(pchar.rank)*(0.1 + MOD_SKILL_ENEMY_RATE));

	return rank;
}
// <-- ugeen

// ==> две функции Эдди для крутизны невероятной.
void FantomMakeCoolSailor(ref _Character, int _ShipType, string _ShipName, int _CannonsType, int _Sailing, int _Accuracy, int _Cannons)
{
    _Character.Ship.Cannons.Type = _CannonsType;
	_Character.skill.Sailing  = GetCoffDiff(_Sailing, SKILL_MAX);
	_Character.skill.Accuracy = GetCoffDiff(_Accuracy, SKILL_MAX);
	_Character.skill.Cannons  = GetCoffDiff(_Cannons, SKILL_MAX);
	//_Character.skill.Grappling  = GetCoffDiff((_Cannons+_Accuracy)/2, SKILL_MAX); //zagolski. расчет абордажа и защиты
	//_Character.skill.Defence  = GetCoffDiff((_Sailing+_Accuracy)/2, SKILL_MAX);

    _Character.DontRansackCaptain = true; //квестовые не сдаются
    _Character.SinkTenPercent     = false; // не тонуть при 10 процентах, не убегать в бою
    _Character.AboardToFinalDeck  = true; // абордаж всегда
	_Character.DontClearDead      = true;
	_Character.SaveItemsForDead   = true;
	_Character.AlwaysSandbankManeuver = true;

    _Character.Ship.Type = GenerateShipExt(_ShipType, true, _Character);
    if (_ShipName == "none" || _ShipName == "") {SetRandomNameToShip(_Character)}
    else {_Character.Ship.Name = _ShipName}

    SetBaseShipData(_Character);
    SetCrewQuantityFull(_Character);
    Fantom_SetBalls(_Character, "pirate");

	SetCharacterPerk(_Character, "FastReload");
	SetCharacterPerk(_Character, "HullDamageUp");
	SetCharacterPerk(_Character, "SailsDamageUp");
	SetCharacterPerk(_Character, "CrewDamageUp");
	SetCharacterPerk(_Character, "CriticalShoot");
	SetCharacterPerk(_Character, "LongRangeShoot");
	SetCharacterPerk(_Character, "CannonProfessional");
	SetCharacterPerk(_Character, "ShipDefenseProfessional");
	SetCharacterPerk(_Character, "ShipSpeedUp");
	SetCharacterPerk(_Character, "ShipTurnRateUp");

    DeleteAttribute(_Character, "ship.sails");// убрать дыры на парусах
    DeleteAttribute(_Character, "ship.blots");
    DeleteAttribute(_Character, "ship.masts");// вернуть сбытые мачты
    DeleteAttribute(_Character, "Killer.status"); // снять аттрибут 'был захвачен на абордаж'
    _Character.questTemp.abordage = 0; //снять аттрибут отказа повторного захвата
   	DeleteAttribute(_Character, "Abordage.Enable"); //снять невозможноть абордажа
}
//лучший моряк
void FantomMakeCoolestSailor(ref _Character, int _ShipType, string _ShipName, int _CannonsType, int _Sailing, int _Accuracy, int _Cannons)
{
    _Character.Ship.Cannons.Type = _CannonsType;
	_Character.skill.Sailing  = GetCoffDiff(_Sailing, SKILL_MAX);
	_Character.skill.Accuracy = GetCoffDiff(_Accuracy, SKILL_MAX);
	_Character.skill.Cannons  = GetCoffDiff(_Cannons, SKILL_MAX);
	//_Character.skill.Grappling  = GetCoffDiff((_Cannons+_Accuracy)/2, SKILL_MAX); //zagolski. расчет абордажа и защиты
	//_Character.skill.Defence  = GetCoffDiff((_Sailing+_Accuracy)/2, SKILL_MAX);

    _Character.DontRansackCaptain = true; //квестовые не сдаются
    _Character.SinkTenPercent     = false; // не тонуть при 10 процентах, не убегать в бою
    _Character.AboardToFinalDeck  = true; // абордаж всегда
	_Character.DontClearDead      = true;
	_Character.SaveItemsForDead   = true;
	_Character.AlwaysSandbankManeuver = true;

    _Character.Ship.Type = GenerateShipTop(_ShipType, true, _Character);
    if (_ShipName == "none" || _ShipName == "") {SetRandomNameToShip(_Character)}
    else {_Character.Ship.Name = _ShipName}

    SetBaseShipData(_Character);
    SetCrewQuantityFull(_Character);
    Fantom_SetBalls(_Character, "pirate");

	SetCharacterPerk(_Character, "FastReload");
	SetCharacterPerk(_Character, "HullDamageUp");
	SetCharacterPerk(_Character, "SailsDamageUp");
	SetCharacterPerk(_Character, "CrewDamageUp");
	SetCharacterPerk(_Character, "CriticalShoot");
	SetCharacterPerk(_Character, "LongRangeShoot");
	SetCharacterPerk(_Character, "CannonProfessional");
	SetCharacterPerk(_Character, "ShipDefenseProfessional");
	SetCharacterPerk(_Character, "ShipSpeedUp");
	SetCharacterPerk(_Character, "ShipTurnRateUp");

    DeleteAttribute(_Character, "ship.sails");// убрать дыры на парусах
    DeleteAttribute(_Character, "ship.blots");
    DeleteAttribute(_Character, "ship.masts");// вернуть сбытые мачты
    DeleteAttribute(_Character, "Killer.status"); // снять аттрибут 'был захвачен на абордаж'
    _Character.questTemp.abordage = 0; //снять аттрибут отказа повторного захвата
   	DeleteAttribute(_Character, "Abordage.Enable"); //снять невозможноть абордажа
}

void FantomMakeCoolFighter(ref _Character, int _Rank, int _Fencing, int _Pistol, string _Blade, string _Gun, float _AddHP)
{
    _Character.rank = GetCoffDiff(_Rank, 1000);
    _Character.skill.Fencing = GetCoffDiff(_Fencing, SKILL_MAX);
    _Character.Skill.FencingLight  = GetCoffDiff(sti(_Character.skill.Fencing), SKILL_MAX);
    _Character.Skill.FencingHeavy  = GetCoffDiff(sti(_Character.skill.Fencing), SKILL_MAX);
    _Character.skill.Pistol = GetCoffDiff(_Pistol, SKILL_MAX);
    _Character.skill.Fortune = GetCoffDiff(_Pistol, SKILL_MAX); //zagolski. если умеет хорошо стрелять из пистоля, то умеет и хорошо от него защищаться
	_Character.chr_ai.hp = stf(_Character.chr_ai.hp) + GetCoffDiff(_AddHP, 5000);
	_Character.chr_ai.hp_max = stf(_Character.chr_ai.hp_max) + GetCoffDiff(_AddHP, 5000);
	SetCharacterPerk(_Character, "Energaiser"); // скрытый перк дает 1.5 к приросту энергии, дается ГГ и боссам уровней
	SetCharacterPerk(_Character, "SwordplayProfessional");
	SetCharacterPerk(_Character, "AdvancedDefense");
	SetCharacterPerk(_Character, "CriticalHit");
	SetCharacterPerk(_Character, "Sliding");
	SetCharacterPerk(_Character, "HardHitter");
	DeleteAttribute(_Character, "Items");
	_Character.SuperShooter  = true;
	_Blade = GetGeneratedItem(_Blade);
    GiveItem2Character(_Character, _Blade);
    EquipCharacterbyItem(_Character, _Blade);
    TakeNItems(_Character,"potion1", rand(MOD_SKILL_ENEMY_RATE)+1);
    TakeNItems(_Character,"potion2", rand(2)+1);
    TakeNItems(_Character,"Food1", rand(2)+2);
    if (_Gun != "")
	{
		GiveItem2Character(_Character, _Gun);
		EquipCharacterbyItem(_Character, _Gun);
		GiveGunAmmunition(_Character, _Gun);
	}
	GiveItem2Character(_Character,"spyglass3");
	EquipCharacterbyItem(_Character, "spyglass3");
    FaceMaker(_Character);
    SetNewModelToChar(_Character);  // перерисуем модель на лету
}

void FantomMakeCoolFighterWRankDepend(ref _Character, int _Rank, int _Fencing, int _Pistol, float _AddHP)
{
    _Character.rank = GetCoffDiff(_Rank, 1000);
    _Character.skill.Fencing = GetCoffDiff(_Fencing, SKILL_MAX);
    _Character.Skill.FencingLight  = GetCoffDiff(sti(_Character.skill.Fencing), SKILL_MAX);
    _Character.Skill.FencingHeavy  = GetCoffDiff(sti(_Character.skill.Fencing), SKILL_MAX);
    _Character.skill.Pistol = GetCoffDiff(_Pistol, SKILL_MAX);
    _Character.skill.Fortune = GetCoffDiff(_Pistol, SKILL_MAX); //zagolski. если умеет хорошо стрелять из пистоля, то умеет и хорошо от него защищаться
	_Character.chr_ai.hp = stf(_Character.chr_ai.hp) + GetCoffDiff(_AddHP, 5000);
	_Character.chr_ai.hp_max = stf(_Character.chr_ai.hp_max) + GetCoffDiff(_AddHP, 5000);
	SetCharacterPerk(_Character, "Energaiser"); // скрытый перк дает 1.5 к приросту энергии, дается ГГ и боссам уровней
	SetCharacterPerk(_Character, "SwordplayProfessional");
	SetCharacterPerk(_Character, "AdvancedDefense");
	SetCharacterPerk(_Character, "CriticalHit");
	SetCharacterPerk(_Character, "Sliding");
	SetCharacterPerk(_Character, "HardHitter");
	DeleteAttribute(_Character, "Items");
	_Character.SuperShooter  = true;
	string sword = LAi_NPC_EquipBladeSelection(sti(_Character.rank));
	sword = GetGeneratedItem(sword);
    GiveItem2Character(_Character, sword);
    EquipCharacterbyItem(_Character, sword);
    TakeNItems(_Character,"potion1", rand(MOD_SKILL_ENEMY_RATE)+1);
    TakeNItems(_Character,"potion2", rand(2)+1);
    TakeNItems(_Character,"Food1", rand(2)+2);
	string Gun = GiveRankGun(_Character);
    if (Gun != "")
	{
		GiveItem2Character(_Character, Gun);
		EquipCharacterbyItem(_Character, Gun);
		GiveGunAmmunition(_Character, Gun);
	}
	GiveItem2Character(_Character,"spyglass3");
	EquipCharacterbyItem(_Character, "spyglass3");
    FaceMaker(_Character);
    SetNewModelToChar(_Character);  // перерисуем модель на лету
}

string GiveRankGun(ref chr)
{
	string guntype = "";
	int iRnd = rand(1);
	if(sti(chr.rank) > 10) iRnd = rand(2);
	if(sti(chr.rank) > 15) iRnd = rand(2) + 1;
	if(sti(chr.rank) > 20) iRnd = rand(3) + 2;

	switch(iRnd)
	{
		case 0:
			if(rand(100) < 70)
			{
				guntype = "pistol1"; // Пистоль
			}
		break;

		case 1:
			if(rand(100) < 75)
			{
				guntype = "pistol2"; // Колониальный пистолет
			}
		break;

		case 2:
			if(rand(100) < 80)
			{
				guntype = "pistol3"; // Тромбон
			}
		break;

		case 3:
			if(rand(100) < 85)
			{
				guntype = "pistol6"; // Бок-пистолет
			}
		break;

		case 4:
			if(rand(100) < 90)
			{
				guntype = "pistol5"; // Бретерский пистолет
			}
		break;

		case 5:
			if(rand(100) < 95)
			{
				guntype = "pistol4"; // Четырёхствольный пистолет
			}
		break;
	}
	return guntype;
}

void GiveGunAmmunition(ref _Character, string sItem)
{
	ref itm = ItemsFromID(sItem);
	TakeNItems(_Character,itm.type.t1.bullet, 30+rand(20));
	AddItems(_Character, itm.type.t1.gunpowder, 30+rand(20)); // Warship. Порох
	LAi_SetCharacterUseBullet(_Character, itm.type.t1.bullet);
}

void GiveGunAmmunitionPchar(ref _Character, string sItem, int qty)
{
	ref itm = ItemsFromID(sItem);
	TakeNItems(_Character,itm.type.t1.bullet, qty);
	AddItems(_Character, itm.type.t1.gunpowder, qty); // Warship. Порох
	LAi_SetCharacterUseBullet(_Character, itm.type.t1.bullet);
}

int GetCoffDiff(float _num, int _maxRange)
{
	switch (MOD_SKILL_ENEMY_RATE)
	{
		case  1: _num *= 0.6;  break;
		case  2: _num *= 0.75; break;
		case  3: _num *= 0.85; break;
		case  4: _num *= 0.9;  break;
		case  5: _num *= 0.95; break;
		case  6: _num *= 1;    break;
		case  7: _num *= 1.1;  break;
		case  8: _num *= 1.2;  break;
		case  9: _num *= 1.3;  break;
		case 10: _num *= 1.5;  break;
	}
	_num += 0.5;
	if (_num > _maxRange) return _maxRange;
	else return sti(_num);
}
// заполнение сундуков и рандитема по квесту
bool SetLocationQuestRandItem(int _index, aref _location, string _locatorName, aref al) // al - ветка локатора из модели, остальное тоже из обратотки локации
{   // метод редактировать не нужно - все задается в квестах
	string  lastSpawnTimeString;
    int     n;
	string  itemId;
	aref checkAref

	/* Пример
 	pchar.GenQuestRandItem.QC_Port = true;
    pchar.GenQuestRandItem.QC_Port.randitem1 = "pistol6";
    // если нужно чтоб было всегда
	pchar.GenQuestRandItem.QC_Port.stay = true; - тереть потом эту ветку самому по квесту

    QC_Port - локация где
    randitem1 - локатор
    pistol6 - предмет

    если нужно сразу несколько локаторов, то
    pchar.GenQuestRandItem.QC_Port.randitem1 = "pistol6";
    pchar.GenQuestRandItem.QC_Port.randitem2 = "pistol1";
 	*/
	lastSpawnTimeString = _location.id;
    if (CheckAttribute(pchar , "GenQuestRandItem." + lastSpawnTimeString) && CheckAttribute(pchar , "GenQuestRandItem." + lastSpawnTimeString +"."+_locatorName))
    {
        itemId = pchar.GenQuestRandItem.(lastSpawnTimeString).(_locatorName);
        if (!CheckAttribute(pchar , "GenQuestRandItem." + lastSpawnTimeString +".stay"))
        {
			//--> fix eddy. нельзя было положить в несколько локаторов
			DeleteAttribute(pchar , "GenQuestRandItem." + lastSpawnTimeString + "." + _locatorName); // если токо один раз
			makearef(checkAref,  pchar.GenQuestRandItem.(lastSpawnTimeString));
			if (GetAttributesNum(checkAref) == 0) DeleteAttribute(pchar , "GenQuestRandItem." + lastSpawnTimeString);
        }
        // только один предмет!!!!!!!!!!!!
        n = SetRandItemShow(_index, al, itemId); // вывести 3д модель в лакацию, если модель вообще есть
		if (n != -1)
		{
            Log_TestInfo("SetLocationQuestRandItem");
            lastSpawnTimeString = "LastSpawnTime"+_index;
		    _location.(lastSpawnTimeString) = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
            lastSpawnTimeString = "RandItemType"+_index;
        	_location.(lastSpawnTimeString) = n;
            return true;
        }
    }

    return false;
}
// загрузить модель
int SetRandItemShow(int _index, aref al, string _itemId)
{
    int     n;
    aref    randItem;

    n = Items_FindItem(_itemId, &randItem);
	if (n != -1)
	{
        if (!CheckAttribute(randItem, "model") || randItem.model == "")
    	{
    		Trace("SetRandItemShow: no model for item "+randItem.id);
    		return -1;
    	}
	    Items_LoadModel(&randItemModels[_index],  randItem);
    	SendMessage(&randItemModels[_index], "lffffffffffff", MSG_MODEL_SET_POSITION, makeFloat(al.x), makeFloat(al.y), makeFloat(al.z), makeFloat(al.vx.x), makeFloat(al.vx.y), -makeFloat(al.vx.z), makeFloat(al.vy.x), makeFloat(al.vy.y), -makeFloat(al.vy.z), makeFloat(al.vz.x), makeFloat(al.vz.y), -makeFloat(al.vz.z));

        return n;
    }
    return n;
}
// заполнить сундук
bool SetLocationQuestBox(ref _location, string _locatorName)
{   // метод редактировать не нужно - все задается в квестах
    bool    ok = false;
    string  locId;
    aref    arToBox;
    aref    arFromBox;

    /* Пример
 	pchar.GenQuestBox.Havanna_town_04 = true;
    pchar.GenQuestBox.Havanna_town_04.box1.items.jewelry1 = 4;
    pchar.GenQuestBox.Havanna_town_04.box1.items.mineral2 = 10;
    // если нужны деньги, иначе не заполнять
	pchar.GenQuestBox.Havanna_town_04.box1.money          = 100;
    // если нужно чтоб было всегда
	pchar.GenQuestBox.Havanna_town_04.stay = true; - тереть потом эту ветку самому по квесту

    Havanna_town_04
    box1
    items

    Havanna_town_04 - локация где
    box1 - локатор
    items - список предметов

    если нужно сразу несколько локаторов, то
    pchar.GenQuestBox.Havanna_town_04.box2.items.jewelry1 = 34;
 	*/
 	locId  = _location.id;
    if (CheckAttribute(pchar , "GenQuestBox." + locId) && CheckAttribute(pchar , "GenQuestBox." + locId + "." + _locatorName))
    {
        Log_TestInfo("SetLocationQuestBox");

        makearef(arToBox, _location.(_locatorName));
        makearef(arFromBox, pchar.GenQuestBox.(locId).(_locatorName));
        CopyAttributes(arToBox, arFromBox);
        _location.(_locatorName) = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear()); // таймер, чтоб не затерлись рандомом при выходе из локации
        if (!CheckAttribute(pchar , "GenQuestBox." + locId +".stay"))
        {
			//--> fix eddy. нельзя было положить в несколько локаторов
			DeleteAttribute(pchar , "GenQuestBox." + locId + "." + _locatorName); // если токо один раз
			makearef(arToBox,  pchar.GenQuestBox.(locId));
			if (GetAttributesNum(arToBox) == 0) DeleteAttribute(pchar , "GenQuestBox." + locId);
        }
        return true;
    }
    return false;
}

// ==> Метод открытия\закрытия локаторов релоад. Если _flag=true - закрыть локатор, если _flag=false - открыть.
void LocatorReloadEnterDisable(string _locationID, string _locator, bool _flag)
{
    aref arDis, arRld;
	makearef(arRld, Locations[FindLocation(_locationID)].reload);
	int	Qty = GetAttributesNum(arRld);
	for (int i=0; i<Qty; i++)
	{
		arDis = GetAttributeN(arRld, i);
        if (arDis.name == _locator)
        {
    		if (_flag) arDis.disable = 1;
    		else DeleteAttribute(arDis, "disable");
            break;
        }
	}
}

//===>>> Функции по работе с диалоговыми файлами. Эдди. ================================================================
// == _strNormal - обычная строка диалога
// == _strBad1, _strBad2, _strBad3 - строки степени возмущения,  "" и "none" - базовый набор.
// == _kind - вид возмущения: "repeat" - снимается на следующий день при условии, что НПС вконец не разозлился (не задействован анги-файл).
//                            "quest"  - квестовые повторялки, не снимаются на следующий день, но может быть задан срок примирения после перевода на ангри.
//                            "block"  - реакцию НПС на повторные клики без включения ангри, для того, чтобы обозначить интеллект, но не ругаться. Ангри вообще не делать.
//                            "cycle"  - крутим цикл из повторялок, ангри не заряжать. На след. день все снимается.
// == _terms для "repeat" и "quest" - сроки в днях примирения само-собой после задействоания ангри-файла, если == 0, то ругань навсегда (примерение только через подарки).
//    _terms для "block" - сроки возврата в норму в днях, если 0 - навсегда.
// == _character и _Node - npchar и Dialog.CurrentNode
string NPCStringReactionRepeat(string _strNormal, string _strBad1, string _strBad2, string _strBad3, string _kind, int _terms, ref _character, string _Node)
{
    _Node = stripblank(_Node); //fix spaces
	string strBack;
    string strTemp = "quest.repeat." + _Node;
    if (!CheckAttribute(_character , strTemp))
    {
        _character.quest.repeat.(_Node) = 0;
        _character.quest.repeat.(_Node).ans = 0;
    }
    if (_kind == "cycle" || _kind == "repeat") //на след.день все снимается.
    {
        if (GetNpcQuestPastDayParam(_character, strTemp) >= 1)
        {
            _character.quest.repeat.(_Node) = 0;
            _character.quest.repeat.(_Node).ans = 0;
        }
    }
    else
    {
        if (GetNpcQuestPastDayParam(_character, strTemp) >= _terms && _terms!=0 && _kind != "quest") //снятие по "block"
        {
            _character.quest.repeat.(_Node) = 0;
            _character.quest.repeat.(_Node).ans = 0;
        }
    }
    switch(_character.quest.repeat.(_Node))
	{
        case "0":
            strBack = _strNormal;
            _character.quest.repeat.(_Node) = 1;
            _character.quest.repeat.(_Node).ans = 0;
            SaveCurrentNpcQuestDateParam(_character, strTemp);
        break;
        case "1":
            if (_strBad1 == "none" || _strBad1 == "")
            {
                strBack = LinkRandPhrase("Я не хочу говорить об одном и том же по нескольку раз.",
                          "Мы уже говорили об этом.",
                          "Эту тему мы уже обсуждали.");
            }
            else
            {
                strBack = _strBad1;
            }
            _character.quest.repeat.(_Node) = 2;
            _character.quest.repeat.(_Node).ans = 1;
        break;
        case "2":
            if (_strBad2 == "none" || _strBad2 == "")
            {
                strBack = LinkRandPhrase("Еще раз повторяю, что я не хочу говорить об одном и том же по десять раз!",
                          "Повторяю, мы уже говорили об этом!",
                          "Я же говорю, мы это уже обсуждали. Проблемы с памятью?");
            }
            else
            {
                strBack = _strBad2;
            }
            _character.quest.repeat.(_Node) = 3;
            _character.quest.repeat.(_Node).ans = 2;
        break;
        case "3":
            if (_strBad3 == "none" || _strBad3 == "")
            {
                strBack = LinkRandPhrase("Я не намерен более с вами общаться.",
                          "Не буду с тобой больше разговаривать!",
                          "Ты меня порядком разозлил"+ GetSexPhrase("","а") +", никакого общения более.");
            }
            else
            {
                strBack = _strBad3;
            }
            // ==> Реакция на третье повторение.
            if (_kind == "cycle") //снова на первую строку.
            {
			    _character.quest.repeat.(_Node) = 0;
            }
			else
            {
                if(_kind != "block") //если block, то опять в последнюю строку
                {
                    _character.quest.repeat.(_Node) = 4;
                    CharacterAddAngry(_character, _Node, _kind, _terms);
    			}
            }
            _character.quest.repeat.(_Node).ans = 3;
        break;
        case "4":
            strBack = "NPCStringReactionRepeat error!!!"
        break;
	}
    return strBack;
}

string HeroStringReactionRepeat(string _strNormal, string _strBad1, string _strBad2, string _strBad3, ref _character, string _Node)
{
    _Node = stripblank(_Node); //fix spaces
	string strBack;
    int Temp = sti(_character.quest.repeat.(_Node).ans);
    switch(Temp)
	{
        case "0":
            strBack = _strNormal;
        break;
        case "1":
            if (_strBad1 == "none" || _strBad1 == "")
            {
                strBack = LinkRandPhrase("Хорошо, приятель.",
                          "Как скажешь.",
                          "Не то ляпнул"+ GetSexPhrase("","а") +", извини...");
            }
            else
            {
                strBack = _strBad1;
            }
        break;
        case "2":
            if (_strBad2 == "none" || _strBad2 == "")
            {
                strBack = LinkRandPhrase("Хорошо, хорошо. Только не кипятись.",
                          "Как скажешь, только не надо кричать.",
                          "Извини, что-то я сегодня не в форме... Голова с утра раскалывается...");
            }
            else
            {
                strBack = _strBad2;
            }
        break;
        case "3":
            if (_strBad3 == "none" || _strBad3 == "")
            {
                strBack = LinkRandPhrase("Как знаешь.",
                          "Очень жаль...",
                          "Невелика потеря.");
            }
            else
            {
                strBack = _strBad3;
            }
        break;
        case "4":
            strBack = "HeroStringReactionRepeat error!!!"
        break;
	}
    return strBack;
}

// возможны только две переходные ноды: _GoNode1 и _GoNode2, третья не нужна, т.к. идет сразу в ангри-файл.
// неверно, оставил третью ноду для циклов и прочего.
string DialogGoNodeRepeat(string _NormalNode, string _GoNode1, string _GoNode2, string _GoNode3, ref _character, string _Node)
{
    _Node = stripblank(_Node); //fix spaces
	string strBack, Temp;
    Temp = sti(_character.quest.repeat.(_Node).ans);
    switch(Temp)
	{
        case "0":
            strBack = _NormalNode;
        break;
        case "1":
            if (_GoNode1 == "none" || _GoNode1 == "")
            {
                strBack = "exit";
            }
            else
            {
                strBack = _GoNode1;
            }
        break;
        case "2":
            if (_GoNode2 == "none" || _GoNode2 == "")
            {
                strBack = "exit";
            }
            else
            {
                strBack = _GoNode2;
            }
        break;
        case "3":
            if (_GoNode3 == "none" || _GoNode3 == "")
            {
                strBack = "exit";
            }
            else
            {
                strBack = _GoNode3;
            }
        break;
        case "4":
            strBack = "exit"
            Log_SetStringToLog("DialogGoNodeRepeat#4 error!!!");
        break;
    }
    return strBack;
}

// _Node - имя ноды, идентификатор текущей ангри. Если метод вызывается не в диалоговом файле, то == "none".
void CharacterAddAngry(ref _character, string _Node, string _kind, int _terms)
{
    if (_kind == "repeat" || _kind == "quest")
    {
        DeleteAttribute(_character, "angry");
        _character.angry.kind = _kind;
        _character.angry.name = _Node; //и имя ноды тоже, для расфасовки разных ангри
        if (_terms != 0) // если == 0, то ссора непроходящая с течением времени.
        {
            _character.angry.terms = _terms;
            SaveCurrentNpcQuestDateParam(_character, "angry.terms");
            if (_terms < 10) // размер вознаграждения за примирение, анти с/л
            {
                _character.angry.QtyMoney = (rand(10)+1) * 500;
            }
            else
            {
                _character.angry.QtyMoney = (rand(10)+1) * 5000;
            }
        }
        else
        {
            _character.angry.QtyMoney = (rand(10)+1) * 10000;
        }
    }
    else {Log_Info("CharacterAddAngry error!!!");}
}

void CharacterDelAngry(ref _character)
{
    DeleteAttribute(_character, "angry");
    DeleteAttribute(_character, "quest.repeat");
}

//В условиях возможного тотального применения ангри по квестам, нужно подстраховаться.
//Если нода дается НПС в момет, когда у него задействован ангри, то нода будет возвращена после примирения.
//Соотв. менять ноды желательно данным методом.
void QuestSetCurrentNode(string _chID, string _Node)
{
    ref chref = characterFromID(_chID);
    if (CheckAttribute(chref, "angry")) chref.dialog.TempNode = _Node;
    else chref.dialog.currentnode = _Node;
}

// фраза от пола НПС
string NPCharSexPhrase(ref _character, string StrMan, string StrWoman)
{
	string strBack;
    if (_character.sex == "woman" || findsubstr(_character.Model, "PGG_Ghost" , 0) != -1)
    {
        strBack = StrWoman;
    }
    else
    {
        strBack = StrMan;
    }
    return strBack;
}
// фраза от пола ГГ
string GetSexPhrase(string StrMan, string StrWoman)
{
    return NPCharSexPhrase(PChar, StrMan, StrWoman);
}
//<<<=== Функции по работе с диалоговыми файлами. =======================================================================


// Временно сохранить все данные о нашем корабле в памяти
//--------------------------------------------------------
bool SetTempRemoveParam(ref _refCharacter, string _param)
{
    string sParam = "TmpRemember" + _param;

	if( CheckAttribute(_refCharacter, sParam) ) return false;
	if( !CheckAttribute(_refCharacter, _param) ) return false;

	aref dstRef; makearef(dstRef, _refCharacter.(sParam));
	aref srcRef; makearef(srcRef, _refCharacter.(_param));

	CopyAttributes(dstRef,srcRef);
	return true;
}

// Восстановить данные о нашем старом корабле из памяти
//------------------------------------------------------
bool RestoreTempRemoveParam(ref _refCharacter, string _param)
{
    string sParam = "TmpRemember" + _param;

	if( !CheckAttribute(_refCharacter, sParam) ) return false;

	aref dstRef; makearef(dstRef, _refCharacter.(_param));
	aref srcRef; makearef(srcRef, _refCharacter.(sParam));

	DeleteAttribute(_refCharacter, _param);
	//--> eddy. структура быть должна, иначе вылет в винду.
	_refCharacter.(_param) = "";
	CopyAttributes(dstRef,srcRef);
	DeleteAttribute(_refCharacter, sParam);
	return true;
}

// установка отмены боевки в резиденции при захвате города
// ВАЖНО: работает только не в пиратском городе - иначе это просто мятеж и губернатора там нет вообще
void SetCaptureResidenceQuest(string _city, string _method, bool _majorOff)
{
    PChar.GenQuestFort.ResidenceQuest.(_city) = true;
    // убирать ли губернатора из локации вообще, он пропадет, но потом обратно пропишется, чтоб не рушить мир игры.
    PChar.GenQuestFort.ResidenceQuest.(_city).MayorOff = _majorOff;
    if (_method != "")
    {
        PChar.GenQuestFort.ResidenceQuest.(_city).method = _method;
	}
}

// вернем диалог после разговора и спрячем
void  SetReturn_Gover_Dialog_Exit(ref NPChar)
{
	LAi_LoginInCaptureTown(NPChar, false);

	PChar.GenQuest.GoverIdx = NPChar.index;
	Pchar.quest.Return_Gover_Dialog_Exit.win_condition.l1          = "ExitFromLocation";
    Pchar.quest.Return_Gover_Dialog_Exit.win_condition.l1.location = Pchar.location;
    Pchar.quest.Return_Gover_Dialog_Exit.win_condition             = "Return_Gover_Dialog_Exit";
}

//#20171020-01 Bug fix SetNewModelToChar sending itemID, and needs model name
void SetNewModelToChar(ref chref)
{
    float liveTime = 0.1;
	int colors = argb(64, 64, 64, 64);
	int colore = argb(0, 32, 32, 32);

	aref arItm;
    string modelName;
    object emptyItm;

    if (IsEntity(chref))
    {
    	if(CheckAttribute(chref, "model"))
        {
			if(chref.model == "") chref.model = "none";
			SendMessage(chref, "lss",   MSG_CHARACTER_SETMODEL, chref.model, chref.model.animation);
			if (findsubstr(chref.model, "ghost" , 0) != -1 )
			{
				object persRef = GetCharacterModel(chref);
				SendMessage(persRef, "ls", MSG_MODEL_SET_TECHNIQUE, "DLightMark");
			}
        }
        if(CheckAttribute(chref, "equip.gun"))
        {
            modelName = chref.equip.gun;
            makearef(arItm,emptyItm);
            if(modelName!="")
            {
                Items_FindItem(modelName,&arItm);
            }
            if(CheckAttribute(arItm,"model"))    {modelName = arItm.model;}
            //SendMessage(chref, "ls",    MSG_CHARACTER_SETGUN,   chref.equip.gun);
            SendMessage(chref, "ls",    MSG_CHARACTER_SETGUN,   modelName);
        }
        if(CheckAttribute(chref, "equip.blade"))
        {
            modelName = chref.equip.blade;
            makearef(arItm,emptyItm);
            if(modelName!="")
            {
                Items_FindItem(modelName,&arItm);
            }
            if(CheckAttribute(arItm,"model"))    {modelName = arItm.model;}
             //#20191009-01
            if(CheckAttribute(arItm, "param.time")) //"blade.time"))
            {
                liveTime = stf(arItm.param.time);
            }
            if(CheckAttribute(arItm, "param.colorstart")) //"blade.colorstart"))
            {
                colors = sti(arItm.param.colorstart);
            }
            if(CheckAttribute(arItm, "param.colorend")) //"blade.colorend"))
            {
                colore = sti(arItm.param.colorend);
            }
            //SendMessage(chref, "lsfll", MSG_CHARACTER_SETBLADE, chref.equip.blade, liveTime, colors, colore);
            //SendMessage(chref, "llsfll", MSG_CHARACTER_SETBLADE, 0, chref.equip.blade, liveTime, colors, colore);
            SendMessage(chref, "llsfll", MSG_CHARACTER_SETBLADE, 0, modelName, liveTime, colors, colore);
        }
		/*if (CheckAttribute(chref, "HeadAccessory") && IsEquipCharacterByItem(chref, chref.HeadAccessory))
		{
			SendMessage(chref,"lsss",MSG_CHARACTER_SETHEAD, chref.model, chref.HeadAccessory, "pscripts\HeadGear.ini");
		}
		else
		{
			SendMessage(chref,"lsss",MSG_CHARACTER_SETHEAD, chref.model, "", "pscripts\HeadGear.ini");
		}*/
    }
}
// функции из квест_реакшн
void SetNationToOfficers(int _nat)
{
    int j, cn;
    ref officer;

    for(j=1; j<COMPANION_MAX; j++)
    {
        cn = GetCompanionIndex(GetMainCharacter(),j);
        if( cn>0 )
        {
	        officer = GetCharacter(cn);
	        if (!GetRemovable(officer)) continue;
	        officer.nation = _nat;
	        Ship_FlagRefresh(officer); //флаг на лету
	    }
	}
}

bool IsOfficerCompanion(ref _refCharacter)
{
	int findIdx = sti(_refCharacter.index);
	ref mc = GetMainCharacter();
	int ci, cn;
	ref npc;
	for(int i=1; i<COMPANION_MAX; i++)
	{
		ci = GetCompanionIndex(mc,i);
		npc = GetCharacter(ci);
		for(int j=1; j<=MAX_NUM_FIGHTERS; j++)
		{
			if(GetOfficersIndex(npc,j)==findIdx) return true;
		}
	}
	return false;
}

void SortItems(ref NPChar)
{// отсортировать предметы в кармане, сундуке
    aref   arToChar;
    aref   arFromChar;
    object objChar;
    int    i;
    aref   curItem;
	string attr;
	ref    itm;
	ref    rObj;
	int    iSortIndex;
	bool   ok;

    objChar.Items = "";
    rObj = &objChar;

    makearef(arToChar,   rObj.Items);
    makearef(arFromChar, NPChar.Items);

    CopyAttributes(arToChar, arFromChar);

    DeleteAttribute(NPChar, "Items");
    NPChar.Items = "";

    makearef(arFromChar, NPChar.equip); // экипировка
    int iMax = GetAttributesNum(arFromChar);
    for(i=0; i<iMax; i++)
    {
        curItem = GetAttributeN(arFromChar, i);
		if (curItem == "") continue;
        attr = GetAttributeValue(curItem);
        if (attr != "") //патенты клинит
        {
        	NPChar.Items.(attr) = sti(rObj.Items.(attr));
        }
    }
    // неоптимальная сортировка по индексу itm.SortIndex
	// размерность индекса определяется автоматом - длжен быть непрерывен!!, начинается с 1 - целое число
    ok = true;
	iSortIndex = 1;
	while (iSortIndex < 3) // 2 типа
	{
		ok = false;
		for (i=0; i<TOTAL_ITEMS; i++)
		{
			// Warship 11.05.09 fix для новой системы предметов
			if(!CheckAttribute(&Items[i], "ID"))
			{
				continue;
			}

			makeref(itm, Items[i]);
			attr = itm.id;
			if (CheckAttribute(rObj, "items."+attr) && CheckAttribute(itm, "SortIndex") && sti(itm.SortIndex) == iSortIndex)
			{
                NPChar.Items.(attr) = sti(rObj.Items.(attr));
	   			ok = true;
	      	}
	    }
	    iSortIndex++;
    }
    // все остальные
    for (i=0; i<TOTAL_ITEMS; i++)
	{
		// Warship 11.05.09 fix для новой системы предметов
		if(!CheckAttribute(&Items[i], "ID"))
		{
			continue;
		}
		makeref(itm, Items[i]);
		attr = itm.id;
		if (CheckAttribute(rObj, "items."+attr) && !CheckAttribute(itm, "SortIndex"))
		{
   			NPChar.Items.(attr) = sti(rObj.Items.(attr));
   			ok = true;
      	}
    }
}
// установка квестовых товаров и цен
void SetQuestGoodsToStore(ref refStore)
{
	string    goodName;
	// пример использования по квест_реакшн
	/*
	pchar.GenQuest.StoreGoods.StoreIdx = Bridgetown_STORE;
	pchar.GenQuest.StoreGoods.NowNeedToBe = true;
	*/
	if (CheckAttribute(pchar, "GenQuest.StoreGoods.StoreIdx") && refStore.index == pchar.GenQuest.StoreGoods.StoreIdx)
	{
        // пример обработки события
		/*if (CheckAttribute(pchar, "GenQuest.StoreGoods.NowNeedToBe")) // состояние говорящие, то нужно делать
		{
		    DeleteAttribute(pchar, "GenQuest.StoreGoods"); // одноразовая операция, трем обе ветки
		    goodName = Goods[GOOD_RUM].Name;
		    refStore.Goods.(goodName).Quantity       = 666;
		    // цена из обратного вычисления 20 в модификатор
			refStore.Goods.(goodName).RndPriceModify = GetStoreGoodsRndPriceModify(refStore, GOOD_RUM, PRICE_TYPE_BUY, pchar, 20);
		}  */
		if (CheckAttribute(pchar, "GenQuest.StoreGoods.HL2_DiscountPrices")) //Голл.линейка, квест №2, дискаунт в форте Оранж.
		{
		    DeleteAttribute(pchar, "GenQuest.StoreGoods"); // одноразовая операция, трем обе ветки
			goodName = Goods[GOOD_EBONY].Name;
		    pchar.questTemp.HL2Save.EbonyQty = refStore.Goods.(goodName).Quantity;
		    refStore.Goods.(goodName).Quantity       = 400;
		    pchar.questTemp.HL2Save.EbonyPrice = GetStoreGoodsPrice(refStore, GOOD_EBONY, PRICE_TYPE_BUY, pchar, refStore.Goods.(goodName).RndPriceModify);
			refStore.Goods.(goodName).RndPriceModify = GetStoreGoodsRndPriceModify(refStore, GOOD_EBONY, PRICE_TYPE_BUY, pchar, 10);

		    goodName = Goods[GOOD_COFFEE].Name;
		    pchar.questTemp.HL2Save.CoffeeQty = refStore.Goods.(goodName).Quantity;
		    refStore.Goods.(goodName).Quantity       = 400;
		    pchar.questTemp.HL2Save.CoffeePrice = GetStoreGoodsPrice(refStore, GOOD_COFFEE, PRICE_TYPE_BUY, pchar, refStore.Goods.(goodName).RndPriceModify);
			refStore.Goods.(goodName).RndPriceModify = GetStoreGoodsRndPriceModify(refStore, GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 9);

		    goodName = Goods[GOOD_MAHOGANY].Name;
		    pchar.questTemp.HL2Save.MahoganyQty = refStore.Goods.(goodName).Quantity;
		    refStore.Goods.(goodName).Quantity       = 400;
		    pchar.questTemp.HL2Save.MahoganyPrice =  GetStoreGoodsPrice(refStore, GOOD_MAHOGANY, PRICE_TYPE_BUY, pchar, refStore.Goods.(goodName).RndPriceModify);
			refStore.Goods.(goodName).RndPriceModify = GetStoreGoodsRndPriceModify(refStore, GOOD_MAHOGANY, PRICE_TYPE_BUY, pchar, 14);

		    goodName = Goods[GOOD_SANDAL].Name;
		    pchar.questTemp.HL2Save.SandalQty = refStore.Goods.(goodName).Quantity;
		    refStore.Goods.(goodName).Quantity       = 400;
		    pchar.questTemp.HL2Save.SandalPrice = GetStoreGoodsPrice(refStore, GOOD_SANDAL, PRICE_TYPE_BUY, pchar, refStore.Goods.(goodName).RndPriceModify);
			refStore.Goods.(goodName).RndPriceModify = GetStoreGoodsRndPriceModify(refStore, GOOD_SANDAL, PRICE_TYPE_BUY, pchar, 11);
        	pchar.GenQuest.StoreGoods.StoreIdx = FortOrange_STORE; //держим цены для след. посещений
        	pchar.GenQuest.StoreGoods.HL2_AgainDiscount = true;
		}
		if (CheckAttribute(pchar, "GenQuest.StoreGoods.HL2_AgainDiscount")) //Голл.линейка, квест №2, держим дисконтные цены
		{
		    goodName = Goods[GOOD_EBONY].Name;
			refStore.Goods.(goodName).RndPriceModify = GetStoreGoodsRndPriceModify(refStore, GOOD_EBONY, PRICE_TYPE_BUY, pchar, 10);

		    goodName = Goods[GOOD_COFFEE].Name;
			refStore.Goods.(goodName).RndPriceModify = GetStoreGoodsRndPriceModify(refStore, GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 9);

		    goodName = Goods[GOOD_MAHOGANY].Name;
			refStore.Goods.(goodName).RndPriceModify = GetStoreGoodsRndPriceModify(refStore, GOOD_MAHOGANY, PRICE_TYPE_BUY, pchar, 14);

		    goodName = Goods[GOOD_SANDAL].Name;
			refStore.Goods.(goodName).RndPriceModify = GetStoreGoodsRndPriceModify(refStore, GOOD_SANDAL, PRICE_TYPE_BUY, pchar, 11);
		}
		if (CheckAttribute(pchar, "GenQuest.StoreGoods.HL2_QtyPriceIsBack")) //Голл.линейка, квест №2, возврат цен и кол-ва после квеста.
		{
            DeleteAttribute(pchar, "GenQuest.StoreGoods"); // одноразовая операция, трем обе ветки
		    goodName = Goods[GOOD_EBONY].Name;
		    refStore.Goods.(goodName).Quantity       = pchar.questTemp.HL2Save.EbonyQty;
			refStore.Goods.(goodName).RndPriceModify = GetStoreGoodsRndPriceModify(refStore, GOOD_EBONY, PRICE_TYPE_BUY, pchar, sti(pchar.questTemp.HL2Save.EbonyPrice));

		    goodName = Goods[GOOD_COFFEE].Name;
		    refStore.Goods.(goodName).Quantity       = pchar.questTemp.HL2Save.CoffeeQty;
			refStore.Goods.(goodName).RndPriceModify = GetStoreGoodsRndPriceModify(refStore, GOOD_COFFEE, PRICE_TYPE_BUY, pchar, sti(pchar.questTemp.HL2Save.CoffeePrice));

		    goodName = Goods[GOOD_MAHOGANY].Name;
		    refStore.Goods.(goodName).Quantity       = pchar.questTemp.HL2Save.MahoganyQty;
			refStore.Goods.(goodName).RndPriceModify = GetStoreGoodsRndPriceModify(refStore, GOOD_MAHOGANY, PRICE_TYPE_BUY, pchar, sti(pchar.questTemp.HL2Save.MahoganyPrice));

		    goodName = Goods[GOOD_SANDAL].Name;
		    refStore.Goods.(goodName).Quantity       = pchar.questTemp.HL2Save.SandalQty;
			refStore.Goods.(goodName).RndPriceModify = GetStoreGoodsRndPriceModify(refStore, GOOD_SANDAL, PRICE_TYPE_BUY, pchar, sti(pchar.questTemp.HL2Save.SandalPrice));
            DeleteAttribute(pchar, "questTemp.HL2Save");
        }
		if (CheckAttribute(pchar, "GenQuest.StoreGoods.HL5_ThreeFleutes")) //Голл.линейка, квест №5, добавляем количества.
		{
            DeleteAttribute(pchar, "GenQuest.StoreGoods"); // одноразовая операция, трем обе ветки
            goodName = Goods[GOOD_FOOD].Name;
		    refStore.Goods.(goodName).Quantity       = 100000;
			refStore.Goods.(goodName).RndPriceModify = GetStoreGoodsRndPriceModify(refStore, GOOD_FOOD, PRICE_TYPE_BUY, pchar, 10);
        }
	}
}

void HolLine2_NullGoods() //для второго квеста голл. линейки.
{
    ref sld;
    int chComp;
    if (CheckAttribute(pchar, "questTemp.EbonyQtyElseNeed")) pchar.Ship.Cargo.Goods.Ebony = 0;
    if (CheckAttribute(pchar, "questTemp.CoffeeQtyElseNeed")) pchar.Ship.Cargo.Goods.Coffee = 0;
    if (CheckAttribute(pchar, "questTemp.MahoganyQtyElseNeed")) pchar.Ship.Cargo.Goods.Mahogany = 0;
    if (CheckAttribute(pchar, "questTemp.SandalQtyElseNeed")) pchar.Ship.Cargo.Goods.Sandal = 0;
    for (int i=1; i<=COMPANION_MAX; i++)
	{
        chComp = GetCompanionIndex(pchar,i);
        if(chComp != -1)
		{
			sld = GetCharacter(chComp);
            if (CheckAttribute(pchar, "questTemp.EbonyQtyElseNeed")) sld.Ship.Cargo.Goods.Ebony = 0;
            if (CheckAttribute(pchar, "questTemp.CoffeeQtyElseNeed")) sld.Ship.Cargo.Goods.Coffee = 0;
            if (CheckAttribute(pchar, "questTemp.MahoganyQtyElseNeed")) sld.Ship.Cargo.Goods.Mahogany = 0;
            if (CheckAttribute(pchar, "questTemp.SandalQtyElseNeed")) sld.Ship.Cargo.Goods.Sandal = 0;
        }
    }
}

// метод обработки капитана в каюте на абордаже. Ставим проверку на минНР + дилог
// refChar - это фантом, а не реальный кэп, он копия, диалог от настоящего, но ИД и индекс не его, а фантомный, поэтому управляем имено этим актером
// CaptanId - реальный ИД кэпа, запомненный в момент копирования.
void SetQuestAboardCabinDialog(ref refChar)
{
	// пример. тут задаю для теста, все это должно быть на изначальном капитане по квестам
	//refChar.DontClearDead      = true;
	//refChar.SaveItemsForDead   =   true;
	//TakeNItems(refChar, "Chest", 1);
	// пример. <--

	if (CheckAttribute(refChar, "CaptanId"))
	{
        pchar.GenQuest.QuestAboardCabinDialogIdx = refChar.index;
        // как использовать, пример
		/*if (true) // true - для теста, должно быть это CheckAttribute(pchar, "квестовая ветка, если нужно") && refChar.CaptanId == "IdNPC")
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
            refChar.Dialog.Filename    = "Capitans_dialog.c";   // это нужно задать на изначальном кэпе в др месте
	    	refChar.Dialog.CurrentNode = "QuestAboardCabinDialog";
	    	// все остальное в диалоге, по образцу
		}*/
        //Голл. линейка, квест №7, доставка депеши до Тортуги
        if (refChar.CaptanId == "CaptainAttack_1" && pchar.questTemp.State == "DelivLettTortuga_NotFoundLetter")
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
		    return;
		}
		if (refChar.CaptanId == "AntonioDeBarras" && pchar.questTemp.State == "DelivLettTortuga_NotFoundLetter")
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
		    return;
		}
        //Исп. линейка, квест №2, задания Инквизиции
        if (refChar.CaptanId == "JansenDeFonceicao" && CheckAttribute(pchar, "questTemp.State.Usurer"))
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
		    return;
		}
		//Исп. линейка, квест №3, захват Рока Бразильца
		if (refChar.CaptanId == "RockBrasilian" && pchar.questTemp.State == "TakeRockBras_toNearestMaracaibo")
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
		    return;
		}
		//Исп. линейка, квест №7, спасение рядового Пардаля, базар с Моисеем Воклейном
		if (refChar.CaptanId == "CaptainAttack_1" && pchar.questTemp.State == "Sp7SavePardal_toAntigua")
		{
		    LAi_SetCheckMinHP(refChar, 50, true, "QuestAboardCabinDialog");  // сколько НР мин
		    return;
		}
		if (refChar.CaptanId == "CaptainAttack_1" && pchar.questTemp.State == "Sp7SavePardal_PardalIsSink")
		{
		    LAi_SetCheckMinHP(refChar, 50, true, "QuestAboardCabinDialog");  // сколько НР мин
		    return;
		}
		if (refChar.CaptanId == "CaptainAttack_1" && pchar.questTemp.State == "Sp8SaveCumana_toCumana")
		{
		    LAi_SetCheckMinHP(refChar, 50, true, "QuestAboardCabinDialog");  // сколько НР мин
		    return;
		}
		//фр. линейка, квест №2, атака галеона испанских пиратов
		if (refChar.CaptanId == "CaptainAttack_1" && pchar.questTemp.State == "Fr2Letter_SeekProblems")
		{
		    LAi_SetCheckMinHP(refChar, 5, true, "QuestAboardCabinDialog");  // сколько НР мин
		    return;
		}
		//капитан брига, который везет Изабеллу на убой Сальватору
		if (refChar.CaptanId == "IsaAttackCap" && pchar.RomanticQuest == "AttackBrig")
		{
		    LAi_SetCheckMinHP(refChar, 5, true, "QuestAboardCabinDialog");  // сколько НР мин
		    return;
		}
		//капитан по квесту мэра на поиск и уничтожение пирата.
		if (refChar.CaptanId == "MQPirate" && CheckAttribute(pchar, "GenQuest.DestroyPirate"))
		{
		    LAi_SetCheckMinHP(refChar, 5, true, "QuestAboardCabinDialog");  // сколько НР мин
			refChar.dialog.currentnode = "DestroyPirate_Abordage";
		    return;
		}
		//засада на ГГ по наводке на купца homo
		if (findsubstr(refChar.CaptanId, "_QuestMerchant" , 0) != -1  && trap)
		{
		    LAi_SetCheckMinHP(refChar, 30, true, "QuestAboardCabinDialog");  // сколько НР мин
		    refChar.dialog.filename = "Capitans_dialog.c";  //fix homo 23/03/07
			refChar.dialog.currentnode = "MerchantTrap_Abordage";
		    return;
		}
		//капитан шебеки Синяя Птица
		if (refChar.CaptanId == "BlueBirdCapitain" && pchar.questTemp.BlueBird == "toSeaBattle")
		{
		    LAi_SetCheckMinHP(refChar, 5, true, "QuestAboardCabinDialog");  // сколько НР мин
		    return;
		}
		//капитан шебеки Синяя Птица
		if (refChar.CaptanId == "BlueBirdTrader" && pchar.questTemp.BlueBird == "attackFleut")
		{
		    LAi_SetCheckMinHP(refChar, 20, true, "QuestAboardCabinDialog");  // сколько НР мин
		    return;
		}
		//пиратка, Эдвард Лоу на бриге Морской Волк
		if (refChar.CaptanId == "EdwardLoy" && pchar.questTemp.piratesLine == "KillLoy_SeaWolfBattle")
		{
		    LAi_SetCheckMinHP(refChar, 5, true, "QuestAboardCabinDialog");  // сколько НР мин
		    return;
		}
		if (refChar.CaptanId == "LeonCapitain" && pchar.questTemp.piratesLine == "Soukins_seekLeon")
		{
		    LAi_SetCheckMinHP(refChar, 5, true, "QuestAboardCabinDialog");  // сколько НР мин
		    return;
		}
		//квест возврата украденного корабля
		if (findsubstr(refChar.CaptanId, "SeekCap_" , 0) != -1)
		{
		    LAi_SetCheckMinHP(refChar, 5, true, "QuestAboardCabinDialog");  // сколько НР мин
			refChar.Dialog.CurrentNode = "SeekCap"; //даем абордажную ноду
		    return;
		}
		//квест горожанина по возвращения украденной жены
		if (findsubstr(refChar.CaptanId, "SeekCitizCap_" , 0) != -1)
		{
			switch(refChar.quest.SeekCap) {
                case "manRapeWife":
                    LAi_SetCheckMinHP(refChar, 5, true, "QuestAboardCabinDialog");  // сколько НР мин
                    refChar.Dialog.CurrentNode = "RapeWifeCap_Board"; //даем абордажную ноду
                break;
                case "womanRevenge":
                    LAi_SetCheckMinHP(refChar, 5, true, "QuestAboardCabinDialog");  // сколько НР мин
                    refChar.Dialog.CurrentNode = "RevengeCap_board"; //даем абордажную ноду
                break;
                case "womanPirates":
                    LAi_SetCheckMinHP(refChar, 5, true, "QuestAboardCabinDialog");  // сколько НР мин
                    refChar.Dialog.CurrentNode = "PiratesCap_Board"; //даем абордажную ноду
                break;
			}
		    return;
		}
		//зачарованный город, штурм брига с Данькой
		//#20180222-04
		if (findsubstr(refChar.CaptanId, "CompPrisCap_" , 0) != -1)
		{
		    return;
		}
		if (refChar.CaptanId == "Danielle")
		{
			LAi_LocationFightDisable(loadedLocation, false);
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
		    return;
		}
		if (refChar.CaptanId == "BlackBeardNPC" && CheckAttribute(pchar,"Titch_seabattle"))
		{
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetCheckMinHP(refChar, 5.0, true, "Titch_seabattle");  // сколько НР мин
		    return;
		}
		if (refChar.CaptanId == "Dozor_Ship" && PChar.Dozor == "18")//Дозорный
		{
			refChar.Dialog.FileName = "DamnedDestiny\Dozor\Characters.c";
			refChar.Dialog.CurrentNode = "Justin_Butt_1";
			LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
		}
		if(CheckAttribute(pchar, "GenerateShipWreck.CharacterID") && refChar.CaptanId == PChar.GenerateShipWreck.CharacterID && PChar.GenerateShipWreck.State == "CanAbordage")//shipwreck
		{
			refChar.Dialog.Filename = "DamnedDestiny\ShipWreck_dialog.c";
			refChar.Dialog.CurrentNode = "17";
			LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");
		}
		//генератор "Продажный патруль"
		if (refChar.CaptanId == "PirateCapt")
		{
			LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
		}

		// Warship Генер "Пираты на необитайке"
		if(refChar.CaptanId == "PiratesOnUninhabited_BadPirate")
		{
			LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
			refChar.Dialog.FileName = "GenQuests_Dialog.c";
			refChar.Dialog.CurrentNode = "PiratesOnUninhabited_46"; //даем абордажную ноду
		}

		// Генерратор "Поручение капитана 'Выкуп' или 'Операция Галеон'"
		if(CheckAttribute(pchar,"GenQuest.CaptainComission") && pchar.GenQuest.CaptainComission == "Begin")
		{
			LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
			refChar.Dialog.FileName = "GenQuests_Dialog.c";
			refChar.Dialog.CurrentNode = "CaptainComission_1"; //даем абордажную ноду
		}

		if(refChar.CaptanId == "Sharp")
		{
			LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
			refChar.Dialog.FileName = "Quest\ForAll_dialog.c";
			refChar.Dialog.CurrentNode = "SharpCapitain"; //даем абордажную ноду
		}

		if(refChar.CaptanId == "zpqCaptain")
		{
			LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
			refChar.Dialog.FileName = "Quest\ForAll_dialog.c";
			refChar.Dialog.CurrentNode = "zpqCapitain"; //даем абордажную ноду
		}
		if(refChar.CaptanId == "BSBons0" && refChar.model == "BS_Billy")
		{
			LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
			refChar.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			refChar.Dialog.CurrentNode = "BS_NU_12";
		}
		if(refChar.CaptanId == "pirateVikingQuest_Captain")
		{
			LAi_CharacterPlaySound(refChar,"Voice\valhalla_scream.wav");
		}
		if(findsubstr(refChar.CaptanId, "PsHero_" , 0) != -1)
		{
			sld = CharacterFromID(refChar.CaptanId);
			refChar.money = sti(sti(refChar.money)*0.3);//Ибо жирно
			if(!CheckAttribute(sld, "PGG_companion") && CheckAttribute(sld, "PGG_Grudge"))
			{
				sld.willDie = true;
				LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
				refChar.Dialog.FileName = "Quest\ForAll_dialog.c";
				refChar.Dialog.CurrentNode = "PGG_cabin"; //даем абордажную ноду
			}
			else
			{
				if(findsubstr(refChar.CaptanId, "_Trader" , 0) != -1)
				{
					ChangeCharacterNationReputation(PChar, sti(sld.Nation), -15);
				}
			}
		}
		if(refChar.CaptanId == "AntonioDeSouza")
		{
			LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
			refChar.Dialog.FileName = "Quest\WhisperLine\Whisper_cabin_dialog.c";
			refChar.Dialog.CurrentNode = "DeSouza"; //даем абордажную ноду
			refChar.greeting = "GR_DeSouza";
		}
		if(refChar.CaptanId == "wl_Pirate_Cap")
		{
			LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
			refChar.Dialog.FileName = "Quest\WhisperLine\Whisper_cabin_dialog.c";
			refChar.Dialog.CurrentNode = "WarDogCap"; //даем абордажную ноду
			refChar.greeting = "GR_ErnanEsteban";
		}
		if(refChar.CaptanId == "BS_Vein")
		{
			LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
			refChar.dialog.filename = "Quest\BlackSails\Kurtuaznye_Strasti.c";
			refChar.dialog.currentnode = "BS_KS_29";
		}
		if(refChar.CaptanId == "Whisper_Portman_Captain")
		{
			if(!CheckAttribute(pchar,"Whisper.BetrayChardKill"))
			{
				LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
				refChar.Dialog.FileName = "Quest\WhisperLine\Whisper_cabin_dialog.c";
				refChar.Dialog.CurrentNode = "Portman_Cabin"; //даем абордажную ноду
				//refChar.greeting = "GR_ErnanEsteban";
			}
			else
			{
				DeleteAttribute(refChar,"SaveItemsForDead");
			}
		}
		if(refChar.CaptanId == "Flint")
		{
			if(CheckAttribute(pchar,"FlintBoardingDialog"))
			{
				LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
				sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
				sld.dialog.currentnode = "BS_F1_35";
				BSHangover_FlintFight();
			}
			else
			{
				DeleteAttribute(refChar,"SaveItemsForDead");
			}
		}
		if(refChar.CaptanId == "ShipWreck_BadPirate")
		{
			LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
			refChar.Dialog.FileName = "GenQuests_Dialog.c";
			refChar.Dialog.CurrentNode = "ShipWreck_50"; //даем абордажную ноду
		}

		if (refChar.CaptanId == "GhostCapt" && CheckAttribute(pchar,"GenQuest.GhostShip.Prize"))
		{
		    LAi_SetCheckMinHP(refChar, 50, true, "QuestAboardCabinDialog");  // сколько НР мин
			refChar.Dialog.CurrentNode = "GhostCapt_LastDialog";
		}
		if (refChar.CaptanId == "Slaveshorecap")
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
			refChar.Dialog.FileName = "Quest\Other_Quests_NPC.c";
			refChar.Dialog.CurrentNode = "TakeShoreCap"; //даем абордажную ноду
		}
		if (refChar.CaptanId == "RatCaptain")
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
			refChar.Dialog.FileName = "Quest\Other_Quests_NPC.c";
			refChar.Dialog.CurrentNode = "Rat_talk"; //даем абордажную ноду
		}
		if (refChar.CaptanId == "Jafar")
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
			refChar.Dialog.FileName = "Quest\Other_Quests_NPC.c";
			refChar.Dialog.CurrentNode = "Ja_talk"; //даем абордажную ноду
		}
	}
}

// ugeen --> ситуации на абордаже в каюте вражеского кэпа (эпидемия или взрыв)
void SetQuestAboardCabinDialogSituation(ref refChar)
{
	LAi_SetFightMode(pchar, false);
	LAi_LockFightMode(pchar, true);
	refChar.Dialog.FileName = "GenQuests_Dialog.c";
	switch(refChar.situation.type)
	{
		case "pirate": 	// пираты или ДУ
			refChar.Dialog.CurrentNode = "ShipSituation11";
		break;
		case "hunter": 	// ОЗГ
			refChar.Dialog.CurrentNode = "ShipSituation31";
		break;
		case "war": 	// военные корабли
			refChar.Dialog.CurrentNode = "ShipSituation21";
		break;
		case "trade": 	// торговцы
			refChar.Dialog.CurrentNode = "ShipEpidemy1";
		break;
	}
	LAi_SetActorType(refChar);
	LAi_ActorDialog(refChar, pchar, "", -1, 0);
}
// <-- ugeen
void QuestAboardCabinDialogFree()
{
	ref sld;
	sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
	Lai_SetPlayerType(pchar);
	LAi_RemoveCheckMinHP(sld);
	LAi_SetImmortal(sld, false);
    LAi_SetWarriorType(sld);
    LAi_group_MoveCharacter(sld, LAI_GROUP_BRDENEMY);
}
//выход без боевки, но в плен не надо
void QuestAboardCabinDialogNotBattle()
{
	ref sld;
	sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
	Lai_SetPlayerType(pchar);
	LAi_RemoveCheckMinHP(sld);
	LAi_SetImmortal(sld, false);
    LAi_SetWarriorType(sld);
	LAi_LocationFightDisable(loadedLocation, false);
	DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
}
// выход с боевкой
void QuestAboardCabinDialogExitWithBattle(string _questName)
{
    QuestAboardCabinDialogFree(); // важный метод
	ref sld;
	sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
	LAi_SetFightMode(pchar, true);
	LAi_SetFightMode(sld, true);
	LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck(LAI_GROUP_BRDENEMY, _questName);
	// SetCharacterTask_Fight(sld, pchar);
}

void QuestAboardCabinDialogExitWithBattleNoParam() // homo тоже самое, только без параметров
{
    QuestAboardCabinDialogExitWithBattle("");
}

void QuestAboardCabinDialogSurrender()
{
 	ref sld;
	sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
	DeleteAttribute(sld, "DontRansackCaptain"); // если было зачем-то
	pchar.GenQuest.QuestAboardCaptanSurrender = true;
	Lai_SetPlayerType(pchar);
	LAi_RemoveCheckMinHP(sld);
	LAi_SetImmortal(sld, false);
	//на форме убиваем LAi_SetCurHP(characterFromId(sld.CaptanId), 0.0);
	//sld.LifeDay = 0;    это не фантом многодневка, а фантом локации, трется он сам при закрузке локации, но не при выгрузке
	DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
}
//==> квестовое пленение с сохранением индекса пленного.
void QuestAboardCabinDialogQuestSurrender()
{
	ref sld;
	sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
	sld.DontRansackCaptain = true; // чтоб не сдался второй раз
	Lai_SetPlayerType(pchar);
	LAi_RemoveCheckMinHP(sld);
	LAi_SetImmortal(sld, false);
	//на форме убиваем LAi_SetCurHP(characterFromId(sld.CaptanId), 0.0);
	//sld.LifeDay = 0;
	pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(sld);
	SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
	DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
}

// eddy. лицензии торговых компаний. -->
//дать лицензию
void GiveNationLicence(int _nation, int _validity)
{
	string sTemp;
	ref rItem;
	for(int i=0; i<4; i++)
	{
		if (CheckNationLicence(i) && GetDaysContinueNationLicence(i) == -1) TakeNationLicence(i);
	}
	if (_nation != PIRATE)
	{
		if (CheckNationLicence(_nation)) TakeNationLicence(_nation);
		sTemp = NationShortName(_nation)+"TradeLicence";
		GiveItem2Character(pchar, sTemp);
		rItem = ItemsFromID(sTemp);
		SaveCurrentNpcQuestDateParam(rItem, "Action_date");
		rItem.Action_date = GetCurrentDate();
		rItem.Validity = FindRussianDaysString(_validity); //строка для дескрайба
		rItem.Validity.QtyDays = _validity; //время действия лицензии в днях для расчетов
	}
}
//забрать лицензию
void TakeNationLicence(int _nation)
{
	string sTemp;
	if (_nation != PIRATE && CheckNationLicence(_nation))
	{
		sTemp = NationShortName(_nation)+"TradeLicence";
		TakeItemFromCharacter(pchar, sTemp);
		DeleteAttribute(ItemsFromID(sTemp), "Action_date");
		DeleteAttribute(ItemsFromID(sTemp), "Validity");
	}
}
//проверить наличие лицензии
bool CheckNationLicence(int _nation)
{
	if (_nation != PIRATE)
	{
		if (CheckCharacterItem(pchar, NationShortName(_nation)+"TradeLicence")) return true;
	}
	return false;
}
//проверить сроки лицензии, сколько осталось дней. если -1, то просрочена или отсутствует
int GetDaysContinueNationLicence(int _nation)
{
	int iTerms = -1;
	ref rItem;
	if (_nation != PIRATE)
	{
		if (CheckNationLicence(_nation))
		{
			rItem = ItemsFromID(NationShortName(_nation)+"TradeLicence");
			if(!CheckAttribute(rItem, "Validity")) // Warship 10.07.09 fix - Судя по логам, могло не быть
			{
				return -1;
			}
			int Validity = sti(rItem.Validity.QtyDays);
			iTerms = GetNpcQuestPastDayParam(rItem, "Action_date");
			if (iTerms > Validity) iTerms = -1;
			else iTerms = Validity - iTerms;
		}
	}
	return iTerms;
}
//дать наименование лицензии, например 'Лицензия Голландской Вест-Индской компании'
string GetRusNameNationLicence(int _nation)
{
	string sTemp, itmTitle;
	int lngFileID;
	if (_nation != PIRATE)
	{
		if (CheckNationLicence(_nation))
		{
			sTemp = NationShortName(_nation)+"TradeLicence";
			lngFileID = LanguageOpenFile("ItemsDescribe.txt");
			itmTitle = LanguageConvertString(lngFileID, Items[GetItemIndex(sTemp)].name);
		}
	}
	return itmTitle;
}
// eddy. лицензии торговых компаний. <--

//--> eddy. квест Изабеллы, методы для контроля семейной жизни
//запишем текущие показтели статистики. записать так же не все, а один из показателей.
// если _TypeOfCheck == "all", то обнулить все. _TypeOfCheck может быть "KillFort", "TakeTown",
void IsabellaSetCurrentState(string _TypeOfCheck)
{
	if (_TypeOfCheck == "all" || _TypeOfCheck == "KillFort")
	{
		DeleteAttribute(pchar, "RomanticQuest.Cheking.KillFort");
		pchar.RomanticQuest.State.KillFort = Statistic_AddValue(PChar, "pir_KillFort", 0) +
											Statistic_AddValue(PChar, "eng_KillFort", 0) +
											Statistic_AddValue(PChar, "fra_KillFort", 0) +
											Statistic_AddValue(PChar, "spa_KillFort", 0) +
											Statistic_AddValue(PChar, "hol_KillFort", 0);
	}
	if (_TypeOfCheck == "all" || _TypeOfCheck == "TakeTown")
	{
		DeleteAttribute(pchar, "RomanticQuest.Cheking.TakeTown");
		pchar.RomanticQuest.State.TakeTown = Statistic_AddValue(PChar, "pir_TakeTown", 0) +
											Statistic_AddValue(PChar, "eng_TakeTown", 0) +
											Statistic_AddValue(PChar, "fra_TakeTown", 0) +
											Statistic_AddValue(PChar, "spa_TakeTown", 0) +
											Statistic_AddValue(PChar, "hol_TakeTown", 0);
	}
	if (_TypeOfCheck == "all" || _TypeOfCheck == "GrabbingTown")
	{
		DeleteAttribute(pchar, "RomanticQuest.Cheking.GrabbingTown");
		pchar.RomanticQuest.State.GrabbingTown = Statistic_AddValue(PChar, "pir_GrabbingTown", 0) +
												Statistic_AddValue(PChar, "eng_GrabbingTown", 0) +
												Statistic_AddValue(PChar, "fra_GrabbingTown", 0) +
												Statistic_AddValue(PChar, "spa_GrabbingTown", 0) +
  												Statistic_AddValue(PChar, "hol_GrabbingTown", 0);
	}
	if (_TypeOfCheck == "all" || _TypeOfCheck == "AbordShip")
	{
		DeleteAttribute(pchar, "RomanticQuest.Cheking.AbordShip");
		pchar.RomanticQuest.State.AbordShip = Statistic_AddValue(PChar, "pir_AbordShip", 0) +
											Statistic_AddValue(PChar, "eng_AbordShip", 0) +
											Statistic_AddValue(PChar, "fra_AbordShip", 0) +
											Statistic_AddValue(PChar, "spa_AbordShip", 0) +
											Statistic_AddValue(PChar, "hol_AbordShip", 0);
	}
	if (_TypeOfCheck == "all" || _TypeOfCheck == "KillShip")
	{
		DeleteAttribute(pchar, "RomanticQuest.Cheking.KillShip");
		pchar.RomanticQuest.State.KillShip = Statistic_AddValue(PChar, "pir_KillShip", 0) +
											Statistic_AddValue(PChar, "eng_KillShip", 0) +
											Statistic_AddValue(PChar, "fra_KillShip", 0) +
											Statistic_AddValue(PChar, "spa_KillShip", 0) +
											Statistic_AddValue(PChar, "hol_KillShip", 0);
	}
}
//проверим текущее состояние в рамках контроля за статистикой
void IsabellaCheckBreachState()
{
	int iTemp;
	iTemp = Statistic_AddValue(PChar, "pir_KillFort", 0) +
			Statistic_AddValue(PChar, "eng_KillFort", 0) +
			Statistic_AddValue(PChar, "fra_KillFort", 0) +
			Statistic_AddValue(PChar, "spa_KillFort", 0) +
			Statistic_AddValue(PChar, "hol_KillFort", 0);
	if (iTemp > sti(pchar.RomanticQuest.State.KillFort)) pchar.RomanticQuest.Cheking.KillFort = iTemp - sti(pchar.RomanticQuest.State.KillFort);
	iTemp = Statistic_AddValue(PChar, "pir_TakeTown", 0) +
			Statistic_AddValue(PChar, "eng_TakeTown", 0) +
			Statistic_AddValue(PChar, "fra_TakeTown", 0) +
			Statistic_AddValue(PChar, "spa_TakeTown", 0) +
			Statistic_AddValue(PChar, "hol_TakeTown", 0);
	if (iTemp > sti(pchar.RomanticQuest.State.TakeTown)) pchar.RomanticQuest.Cheking.TakeTown = iTemp - sti(pchar.RomanticQuest.State.TakeTown);
	iTemp = Statistic_AddValue(PChar, "pir_GrabbingTown", 0) +
			Statistic_AddValue(PChar, "eng_GrabbingTown", 0) +
			Statistic_AddValue(PChar, "fra_GrabbingTown", 0) +
			Statistic_AddValue(PChar, "spa_GrabbingTown", 0) +
  			Statistic_AddValue(PChar, "hol_GrabbingTown", 0);
	if (iTemp > sti(pchar.RomanticQuest.State.GrabbingTown)) pchar.RomanticQuest.Cheking.GrabbingTown = iTemp - sti(pchar.RomanticQuest.State.GrabbingTown);
	iTemp = Statistic_AddValue(PChar, "pir_AbordShip", 0) +
			Statistic_AddValue(PChar, "eng_AbordShip", 0) +
			Statistic_AddValue(PChar, "fra_AbordShip", 0) +
			Statistic_AddValue(PChar, "spa_AbordShip", 0) +
			Statistic_AddValue(PChar, "hol_AbordShip", 0);
	if (iTemp > sti(pchar.RomanticQuest.State.AbordShip)) pchar.RomanticQuest.Cheking.AbordShip = iTemp - sti(pchar.RomanticQuest.State.AbordShip);
	iTemp = Statistic_AddValue(PChar, "pir_KillShip", 0) +
			Statistic_AddValue(PChar, "eng_KillShip", 0) +
			Statistic_AddValue(PChar, "fra_KillShip", 0) +
			Statistic_AddValue(PChar, "spa_KillShip", 0) +
			Statistic_AddValue(PChar, "hol_KillShip", 0);
	if (iTemp > sti(pchar.RomanticQuest.State.KillShip)) pchar.RomanticQuest.Cheking.KillShip = iTemp - sti(pchar.RomanticQuest.State.KillShip);
	return;
}
//сбросить счетчик по семейному бюджету
void IsabellaNullBudget()
{
	pchar.RomanticQuest.Budget = "0";
	SaveCurrentQuestDateParam("RomanticQuest.Budget");
}
//возвращает текущую задолженность в деньгах. положительное значение - задолж., отрицательное - профицит.
int IsabellaCheckBudgetMoney()
{
	int Debt = GetQuestPastMonthParam("RomanticQuest.Budget")*MOD_SKILL_ENEMY_RATE*10000;
	int CurMoney = sti(pchar.RomanticQuest.Budget);
	return Debt - CurMoney;
}
//добавить денег на текущий баланс бюджета
void IsabellaAddMoneyBudget(int _money)
{
	pchar.RomanticQuest.Budget = sti(pchar.RomanticQuest.Budget) + _money;
	AddMoneyToCharacter(pchar, -_money);
}
// <-- eddy. квест Изабеллы, методы для контроля семейной жизни

void SelectAscoldRendom()
{
	if (CheckAttribute(&colonies[1], "nation"))
	{
		int n, nation;
		int storeArray[MAX_COLONIES];
		int howStore = 0;
		for(n=0; n<MAX_COLONIES; n++)
		{
			if (colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && colonies[n].id != "FortOrange")
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
		nation = storeArray[rand(howStore-1)];
		pchar.questTemp.Ascold.TraderId = colonies[nation].id + "_trader";
		nation = storeArray[rand(howStore-1)];
		pchar.questTemp.Ascold.MerchantColony = colonies[nation].id;
		pchar.questTemp.Ascold.dialogNation = sti(colonies[nation].nation);
		nation = storeArray[rand(howStore-1)];
		while (colonies[nation].id == "Panama")
		{
			nation = storeArray[rand(howStore-1)];
		}

		pchar.questTemp.Ascold.ShipyarderId = colonies[nation].id + "_shipyarder";
		pchar.questTemp.Ascold.ShipyarderColony = colonies[nation].id;
		items[GetItemIndex("Azzy_bottle")].useLocation = colonies[nation].id + "_Shipyard";
	}
}
void SelectSlavetraderRendom() // работорговец, выбор города
{
	if (CheckAttribute(&colonies[1], "nation"))
	{
		int n, nation;
		int storeArray[MAX_COLONIES];
		int howStore = 0;
		for(n=0; n<MAX_COLONIES; n++)
		{
			if (colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && colonies[n].id != "FortOrange" && colonies[n].id != "Havana" && colonies[n].id != "Santiago" && colonies[n].id != "Portroyal" && colonies[n].id != "Villemstad" && colonies[n].id != "Tortuga" && colonies[n].id != "Panama")
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
		nation = storeArray[rand(howStore-1)];
		pchar.questTemp.Slavetrader.UsurerId = colonies[nation].id + "_usurer";
	}
}
// квест Изабеллы
void IsabellaInit()
{
	ref ch;
	// ==> состояние квеста Изабеллы, если равен "" - то квест Атилла не даст.
	pchar.RomanticQuest = "canTakeQuest";
	//Атилла
	ch = GetCharacter(NPC_GenerateCharacter("Atilla", "pirate_1", "man", "man", 22, PIRATE, -1, false));
	ch.name 	= "Атилла";
	ch.lastname 	= "";
	GiveItem2Character(ch, GUN_COMMON);
	ch.equip.gun = GUN_COMMON;
	GiveItem2Character(ch, BLADE_LONG);
	ch.equip.blade = BLADE_LONG;
	ch.location	= "Pirates_town";
	ch.location.group = "goto";
	ch.location.locator = "goto1";
	ch.Dialog.Filename = "Quest\Isabella\Atilla.c";
	ch.greeting = "Gr_Smuggler Agent";
	ch.rank 	= 25;
	ch.reputation = "30";
	ch.talker = 5; //начать диалог
	ch.TiedItems.itm1.model = "HandsItems\meet";
	ch.TiedItems.itm1.locator = "Saber_hand";
	ch.TiedItems.itm2.model = "HandsItems\cup";
	ch.TiedItems.itm2.locator = "Saber_hand";
    SetRandSPECIAL(ch);
    SetSelfSkill(ch, 80, 70, 90, 60, 50);
    SetShipSkill(ch, 50, 10, 60, 60, 40, 70, 70, 40, 50);
	ch.money = "200";
	LAi_SetCitizenType(ch);
	LAi_group_MoveCharacter(ch, "PIRATE_CITIZENS");
	LAi_SetLoginTime(ch, 0.0, 24.0);
	LAi_SetHP(ch, 200.0, 200.0);
	LAi_NoRebirthEnable(ch);
	ch.DontClearDead = true;  // не убирать труп
	ch.greeting = "Gr_Atilla";
	// Злой муж :)
	ch = GetCharacter(NPC_GenerateCharacter("Husband", "Usurer_7", "man", "man", 22, PIRATE, -1, false));
	ch.name 	= "Сальватор";
	ch.lastname = "Олеварес";
	ch.location	= "SanJuan_houseSp6";
	ch.location.group = "goto";
	ch.location.locator = "goto2";
	ch.Dialog.Filename = "Quest\Isabella\Husband.c";
	GiveItem2Character(ch, "pistol5");
	ch.equip.gun = "pistol5";
	TakeNItems(ch,"bullet", Rand(20)+20);
	AddItems(ch, "GunPowder", rand(20)+20);
	GiveItem2Character(ch, "blade34");
	ch.equip.blade = "blade34";
	ch.rank 	= 40;
	ch.reputation = "35";
    SetRandSPECIAL(ch);
    SetSelfSkill(ch, 90, 90, 90, 70, 90);
    SetShipSkill(ch, 20, 90, 10, 10, 10, 20, 10, 10, 50);
	ch.money = "1000";
	ch.SaveItemsForDead = true; // сохранять на трупе вещи
	ch.DontClearDead = true; // не убирать труп через 200с
	LAi_SetLoginTime(ch, 0.0, 24.0);
	LAi_SetHP(ch, 220.0, 220.0);
	LAi_SetHuberStayType(ch);
	LAi_SetStayHuberPointWindow(ch, "goto", "goto1");
	LAi_SetStayHuberPointMap(ch, "goto", "goto2");
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetImmortal(ch, true);
	LAi_LoginInCaptureTown(ch, true);
	ch.greeting = "Gr_OliverTrast";
}
//установить говорилку на горожанина. нужно по Изабелле.
void SetIsabellaTalker(string qName)
{
	ref chr = characterFromID("Isabella");
	chr.talker = 10;
}
//История давней дружбы Lipsar
void SilencePriceInit()
{
	//квестовый перс Люк
	ref ch;
	ch = GetCharacter(NPC_GenerateCharacter("Old Friend", "officer_34", "man", "man", 30, PIRATE, -1, false));
	ch.name = "Люк";
	ch.lastname = "Фрайленг";
	ch.location	= "Bridgetown_town";
	ch.location.group = "goto";
	ch.location.locator = "goto1";
	ch.Dialog.Filename = "Quest\SilencePrice\Luke.c";
	FantomMakeCoolFighter(ch, 30, 90, 50, "blade44", "pistol9", 300);
	GiveItem2Character(ch, "cirass1");
	ch.equip.cirass = "cirass1";
	ch.rank = 30;
	ch.talker = -1;
	SelAllPerksToNotPchar(ch);
	ch.SaveItemsForDead = true;
	AddBonusEnergyToCharacter(ch, 50);
	SetSelfSkill(ch, 80, 100, 100, 100, 100);
	SetShipSkill(ch, 80, 80, 80, 80, 80, 80, 80, 80, 80);
	LAi_SetImmortal(ch, true);
	LAi_SetCitizenType(ch);
	LAi_SetLoginTime(ch, 0.0, 24.0);
	ch.greeting = "Gr_Atilla";
	ChangeCharacterAddressGroup(ch, "LaVega_town", "goto", "goto15");
}
//Проклятие Дальних Морей
void PDMQuestsInit()
{
	ref sld;
	//******Альбрех Пальцфер Sinistra******
	//Альбрех Пальцфер
	sld = GetCharacter(NPC_GenerateCharacter("Albreht_Zalpfer", "Mechanic", "man", "man", 6, ENGLAND, -1, false));
	sld.name	= "Альбрехт";
	sld.lastname	= "Цальпфер";
	sld.City = "Charles";
	sld.location	= "Charles_town";
	sld.location.group = "goto";
	sld.location.locator = "goto22";
	sld.Dialog.Filename = "Quest/PDM/Albreht_Zalpfer.c";
	sld.greeting = "Albrecht_Zalpfer";
	SetCharacterPerk(sld, "Carpenter");
	SetCharacterPerk(sld, "BasicBattleState");
	SetShipSkill(sld, 2, 3, 2, 3, 1, 21, 3, 1, 2);
	sld.talker = 7;
	sld.nation = ENGLAND;
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	LAi_SetImmortal(sld, false);

	//******Проклятый идол Sinistra******
	//Джеймс Кэллоу
	sld = GetCharacter(NPC_GenerateCharacter("James_Callow", "ozg_green", "man", "man", 6, PIRATE, -1, false));
	sld.name	= "Джеймс";
	sld.lastname	= "Кэллоу";
	sld.rank     = 7;
	sld.model	= "ozg_green";
	GiveItem2Character(sld, BLADE_LONG);
	sld.sex = "man";
	sld.City = "LaVega";
	sld.location	= "LaVega_tavern";
	sld.Dialog.Filename = "Quest/PDM/Cursed_Idol.c";
	sld.nation = PIRATE;
	LAi_SetSitType(sld);
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_tavern","sit","sit_base3");

	//******Новая Родина Sinistra******
	//Хьюго Лесопилка
	sld = GetCharacter(NPC_GenerateCharacter("Hugo_Lesopilka", "officer_63", "man", "man", 10, PIRATE, -1, false));
	sld.name	= "Хьюго";
	sld.lastname	= "Лесопилка";
	GiveItem2Character(sld, BLADE_LONG);
	sld.sex = "man";
	sld.City = "PuertoPrincipe";
	sld.location	= "PuertoPrincipe_tavern";
	sld.Dialog.Filename = "Quest/PDM/Novaya_Rodina.c";
	sld.nation = PIRATE;
	LAi_SetSitType(sld);
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld,"PuertoPrincipe_tavern","sit","sit_front2");

	//******Потерянное кольцо Sinistra******
	//Жозефина Лодет
	sld = GetCharacter(NPC_GenerateCharacter("Josephine_Lodet", "BaynesWife", "woman", "woman", 10, FRANCE, -1, false));
	sld.name	= "Старушка";
	sld.lastname	= "";
	sld.City = "BasTer";
	sld.Dialog.Filename = "Quest/PDM/Poteryanoe_Koltso.c";
	LAi_SetCitizenType(sld);
	LAi_SetLoginTime(sld, 6.0, 21.99);
	sld.talker = 7;
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	ChangeCharacterAddressGroup(sld,"BasTer_town","goto","goto4");

	//******Непутёвый казначей Sinistra******
	//Андреас Фиклер
	sld = GetCharacter(NPC_GenerateCharacter("Andreas_Fickler", "usurer_5", "man", "man", 10, HOLLAND, -1, false));
	SetCharacterPerk(sld, "Trader");
	sld.name	= "Андреас";
	sld.lastname	= "Фиклер";
	sld.City = "Villemstad";
	sld.Dialog.Filename = "Quest/PDM/Neputyovy_kaznachey.c";
	LAi_SetCitizenType(sld);
	LAi_SetLoginTime(sld, 6.0, 21.99);
	sld.talker = 7;
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
	ChangeCharacterAddressGroup(sld,"Villemstad_town","officers","houseSp5_2");

	//******Клан Ламбрини Sinistra******
	//Октавио Ламбрини
	sld = GetCharacter(NPC_GenerateCharacter("PDM_Octavio_Lambrini", "barmen_3", "man", "man", 10, PIRATE, -1, false));
	sld.name	= "Октавио";
	sld.lastname	= "Ламбрини";
	sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
	LAi_SetSitType(sld);
	LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
	ChangeCharacterAddressGroup(sld,"PortSpein_tavern","sit","sit_front2");
	//******Проклятая жара Sinistra******
	//Стражники
	sld = GetCharacter(NPC_GenerateCharacter("PDM_PJ_Strajnik_1", "sold_fra_5", "man", "man", 10, FRANCE, -1, false));
	sld.name	= "Джори";
	sld.lastname	= "";
	sld.Dialog.Filename = "Quest/PDM/Proklyataya_Jara.c";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	sld.talker = 7;
	LAi_SetStayType(sld);
	sld.City = "FortFrance";
	FantomMakeCoolFighter(sld, 25, 25, 25, "blade10", "", 40);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	ChangeCharacterAddressGroup(sld,"FortFrance_town","officers","soldier_uniq2");

	sld = GetCharacter(NPC_GenerateCharacter("PDM_PJ_Strajnik_2", "sold_fra_1", "man", "man", 10, FRANCE, -1, false));
	sld.name	= "Алэр";
	sld.lastname	= "";
	sld.dialog.filename   = "Common_Soldier.c";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetGuardianType(sld);
	sld.City = "FortFrance";
	FantomMakeCoolFighter(sld, 25, 25, 25, "blade10", "", 40);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	ChangeCharacterAddressGroup(sld,"FortFrance_town","officers","soldier_uniq1");

	//******Аптекарь Sinistra******
	//Маркус
	sld = GetCharacter(NPC_GenerateCharacter("PDM_Markus", "prison_3", "man", "man", 10, ENGLAND, -1, false));
	sld.name	= "Маркус";
	sld.lastname	= "";
	sld.City = "SentJons";
	sld.Dialog.Filename = "Quest/PDM/Aptekar.c";
	LAi_SetGroundSitType(sld);
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	ChangeCharacterAddressGroup(sld,"SentJons_tavern","goto","goto1");
}
void OfficerGirlInit()
{
    ref sld;

    // Бывшая Данька. АйДи не меняю, т.к. нужно сменить просто модель и анимацию
    sld = GetCharacter(NPC_GenerateCharacter("Daniel", "PGG_YokoDias_0", "woman", "YokoDias", 15, PIRATE, -1, false));
	sld.name 	= "Йоко";
	sld.lastname = "Диаз";
	sld.loyality = 12;
	sld.rank 	= 15;
    sld.reputation = 70; // good девочка
	sld.alignment = "good";
	// Прописка всех моделей для кирас. -->
	sld.HeroModel = "PGG_YokoDias_0,PGG_YokoDias_1,PGG_YokoDias_2,PGG_YokoDias_3,PGG_YokoDias_4,PGG_YokoDias_5,PGG_YokoDias_6,PGG_YokoDias_7,PGG_YokoDias_8";
	// Прописка всех моделей для кирас. <--
	GiveItem2Character(sld, "blade5");
	TakeNItems(sld,"potion2", Rand(4)+1);
	sld.equip.blade = "blade5";
	GiveItem2Character(sld, "pistol2");
	sld.equip.gun = "pistol2";
    TakeNItems(sld,"bullet", Rand(20)+20);
	AddItems(sld, "GunPowder", rand(20)+20);
    sld.Payment = true;
    sld.HoldEquip = false; // не отдавать саблю и пистоль

	sld.location	= "Pirates_town";
	sld.location.group = "goto";
	sld.location.locator = "goto20";
	sld.dialog.filename   = "Enc_OfficerGirl.c";
	sld.dialog.currentnode = "Yoko_meet";
	sld.greeting = "Gr_Danielle";
	sld.money = 0;
 	SetSPECIAL(sld, 9,4,8,6,7,8,6);
	//f_l, f, f_h, p, f
	SetSelfSkill(sld, 43,25,69,45,46);
	// l, c, a, cn, sl, re, gr, de, sn
	SetShipSkill(sld, 45,13,23,34,24,43,54,62,40);
	LAi_NPC_EquipPerk(sld, "fantom");
	sld.perks.list.BasicDefense = true;
    sld.perks.list.AdvancedDefense = true;
    sld.perks.list.SwordplayProfessional = true;
    sld.perks.list.CriticalHit = true;
    sld.perks.list.Gunman = true;
    sld.perks.list.GunProfessional = true;
    sld.perks.list.Energaiser = true;
	sld.perks.list.Ciras = true;
	sld.perks.list.LongRangeGrappling = true;
    LAi_NoRebirthEnable(sld);
    LAi_SetWarriorType(sld);
    LAi_warrior_DialogEnable(sld, true);
    LAi_SetLoginTime(sld, 0.0, 24.0);
    SetFantomHP(sld);
	LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");

	sld = GetCharacter(NPC_GenerateCharacter("Beatrice", "PGG_Rumba", "woman", "Milenace", 15, PIRATE, -1, false));
	sld.name 	= "Элен";
	sld.lastname = "МакАртур";
	sld.loyality = 20;
	sld.rank 	= 15;
    sld.reputation = 50; // good девочка
	sld.alignment = "good";
	sld.HeroModel = "PGG_Rumba_0,PGG_Rumba_1,PGG_Rumba_2,PGG_Rumba_3,PGG_Rumba_4,PGG_Rumba_5";
	GiveItem2Character(sld, "blade36");
	TakeNItems(sld,"potion2", Rand(4)+1);
	sld.equip.blade = "blade36";
	GiveItem2Character(sld, "pistol2");
	sld.equip.gun = "pistol2";
    TakeNItems(sld,"bullet", Rand(20)+20);
	AddItems(sld, "GunPowder", rand(20)+20);
    sld.Payment = true;
    sld.HoldEquip = false; // не отдавать саблю и пистоль

	sld.location	= "PuertoPrincipe_town";
	sld.location.group = "goto";
	sld.location.locator = "goto6";
	sld.dialog.filename   = "Enc_OfficerGirl.c";
	sld.dialog.currentnode = "Helen_meet";
	sld.greeting = "Gr_Danielle";
	sld.money = 0;
  	SetSPECIAL(sld, 6,8,7,6,7,9,5);
	//f_l, f, f_h, p, f
	SetSelfSkill(sld, 68,23,38,45,44);
	// l, c, a, cn, sl, re, gr, de, sn
	SetShipSkill(sld, 30,15,35,40,45,22,33,21,34);
	LAi_NPC_EquipPerk(sld, "fantom");
	sld.perks.list.BasicDefense = true;
    sld.perks.list.AdvancedDefense = true;
    sld.perks.list.SwordplayProfessional = true;
    sld.perks.list.CriticalHit = true;
    sld.perks.list.Gunman = true;
    sld.perks.list.GunProfessional = true;
    sld.perks.list.Energaiser = true;
	sld.perks.list.Ciras = true;
	sld.perks.list.ShipSpeedUp = true;
    LAi_NoRebirthEnable(sld);
    LAi_SetWarriorType(sld);
    LAi_warrior_DialogEnable(sld, true);
    LAi_SetLoginTime(sld, 0.0, 24.0);
    SetFantomHP(sld);
    LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");

	sld = GetCharacter(NPC_GenerateCharacter("Angellica", "PGG_Angellica", "woman", "Milenace", 15, PIRATE, -1, false));
	sld.name 	= "Анджелика";
	sld.lastname = "Шарп";
	sld.loyality = 20;
	sld.rank 	= 15;
    sld.reputation = 10; // good девочка
	sld.alignment = "bad";
	GiveItem2Character(sld, "blade34");
	TakeNItems(sld,"potion2", Rand(4)+1);
	sld.equip.blade = "blade34";
	GiveItem2Character(sld, "pistol2");
	sld.equip.gun = "pistol2";
    TakeNItems(sld,"bullet", Rand(20)+20);
	AddItems(sld, "GunPowder", rand(20)+20);
    sld.Payment = true;
    sld.HoldEquip = false; // не отдавать саблю и пистоль

	sld.location	= "LeFransua_town";
	sld.location.group = "rld";
	sld.location.locator = "loc0";
	sld.dialog.filename   = "Enc_OfficerGirl.c";
	sld.dialog.currentnode = "Angellica_meet";
	sld.greeting = "Gr_Danielle";
	sld.money = 0;
  	SetSPECIAL(sld, 7,8,7,5,7,9,5);
	//f_l, f, f_h, p, f
	SetSelfSkill(sld, 23,68,38,35,33);
	// l, c, a, cn, sl, re, gr, de, sn
	SetShipSkill(sld, 45,33,55,56,35,22,33,21,34);
	LAi_NPC_EquipPerk(sld, "fantom");
	sld.perks.list.BasicDefense = true;
    sld.perks.list.AdvancedDefense = true;
    sld.perks.list.SwordplayProfessional = true;
    sld.perks.list.CriticalHit = true;
    sld.perks.list.Gunman = true;
    sld.perks.list.GunProfessional = true;
    sld.perks.list.Energaiser = true;
	sld.perks.list.Ciras = true;
	sld.perks.list.HullDamageUp = true;
    LAi_NoRebirthEnable(sld);
    LAi_SetWarriorType(sld);
    LAi_warrior_DialogEnable(sld, true);
    LAi_SetLoginTime(sld, 0.0, 24.0);
    SetFantomHP(sld);
    LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
}

void OfficerMushketerInit()
{
    ref sld;
    //мушкетер №1 - пират
    sld = GetCharacter(NPC_GenerateCharacter("OfMush1", "quest_mush_2", "man", "mushketer", 15, PIRATE, -1, true));
	sld.name = "Николя";
	sld.lastname = "Рималье";
	sld.greeting = "Gr_Officer";
	sld.loyality = 18;
	sld.rank = 15;
	//Прописка всех моделей для кирас. -->
	sld.HeroModel = "quest_mush_2,quest_mush_2_1,quest_mush_2_2,quest_mush_2_3,quest_mush_2_4,quest_mush_2_5";
	//Прописка всех моделей для кирас. <--
	sld.reputation = 20;
	sld.alignment = "bad";
	LAi_SetHP(sld, 180, 180);
	sld.Dialog.Filename = "Enc_OfficerMush.c";
	sld.dialog.currentnode = "Lostpirate";
	TakeNItems(sld,"potion2", Rand(2)+2);
	sld.IsMushketer = true;
	sld.CanTakeMushket = true;
	sld.equip.gun = "mushket";
	sld.IsMushketer.LastGunID = -1;
	sld.IsMushketer.MushketID = "mushket";
    TakeNItems(sld,"bullet", 100);
	AddItems(sld, "GunPowder", 100);
    sld.Payment = true;
    sld.HoldEquip = false; // не отдавать саблю и пистоль
	sld.location	= "Shore59";
	sld.location.group = "goto";
	sld.location.locator = "goto3";
	sld.money = 0;
	sld.SuperShooter  = true;
 	SetSPECIAL(sld, 6, 9, 8, 3, 6, 9, 9);
	SetSelfSkill(sld, 60, 3, 3, 100, 80);
	SetShipSkill(sld, 40, 7, 25, 15, 8, 10, 5, 10, 25);
	DeleteAllPerksExceptChar(sld);
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "HPPlus");
    LAi_SetWarriorType(sld);
	LAi_warrior_DialogEnable(sld, true);
	LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
	locations[FindLocation("Shore59")].DisableEncounters = true; //энкаутеры в локации закроем до поры

	//мушкетер №2 - саксонец
	sld = GetCharacter(NPC_GenerateCharacter("OfMush2", "quest_mush_1", "man", "mushketer", 18, SPAIN, -1, true));
	sld.name = "Магнус";
	sld.lastname = "фон Коккай";
	sld.greeting = "Gr_Officer";
	sld.loyality = 13;
	sld.rank = 15;
	sld.reputation = 75;
	//Прописка всех моделей для кирас. -->
	sld.HeroModel = "quest_mush_1,quest_mush_1_1,quest_mush_1_2,quest_mush_1_3,quest_mush_1_4,quest_mush_1_5";
	//Прописка всех моделей для кирас. <--
	sld.alignment = "good";
	LAi_SetHP(sld, 210, 210);
	sld.Dialog.Filename = "Enc_OfficerMush.c";
	sld.dialog.currentnode = "Saxon";
	TakeNItems(sld,"potion2", Rand(2)+2);
	sld.IsMushketer = true;
	sld.CanTakeMushket = true;
	sld.equip.gun = "mushket";
	GiveItem2Character(sld, "cirass2");
	sld.IsMushketer.LastGunID = -1;
	sld.IsMushketer.MushketID = "mushket";
	EquipCharacterbyItem(sld, "cirass2");
    TakeNItems(sld,"bullet", 100);
	AddItems(sld, "GunPowder", 100);
    sld.Payment = true;
    sld.HoldEquip = false; // не отдавать саблю и пистоль
	sld.location	= "Santodomingo_town";
	sld.location.group = "goto";
	sld.location.locator = "goto10";
	sld.money = 0;
	sld.SuperShooter  = true;
 	SetSPECIAL(sld, 7, 9, 7, 4, 3, 10, 8);
	SetSelfSkill(sld, 70, 10, 10, 100, 70);
	SetShipSkill(sld, 30, 9, 8, 8, 15, 20, 18, 5, 30);
	DeleteAllPerksExceptChar(sld);
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "IronWill");
	SetCharacterPerk(sld, "Ciras");
    LAi_SetWarriorType(sld);
    LAi_warrior_DialogEnable(sld, true);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
}
string GetStrSmallRegister(string sBase)
{
	string sResult, Simbol;
	sResult = "";
	int qty = strlen(sBase);
	for (int i=0; i<qty; i++)
	{
		Simbol = GetSymbol(sBase, i);
		switch (Simbol)
		{
			case "А": sResult += "а"; continue; break;
			case "Б": sResult += "б"; continue; break;
			case "В": sResult += "в"; continue; break;
			case "Г": sResult += "г"; continue; break;
			case "Д": sResult += "д"; continue; break;
			case "Е": sResult += "е"; continue; break;
			case "Ё": sResult += "ё"; continue; break;
			case "Ж": sResult += "ж"; continue; break;
			case "З": sResult += "з"; continue; break;
			case "И": sResult += "и"; continue; break;
			case "Й": sResult += "й"; continue; break;
			case "К": sResult += "к"; continue; break;
			case "Л": sResult += "л"; continue; break;
			case "М": sResult += "м"; continue; break;
			case "Н": sResult += "н"; continue; break;
			case "О": sResult += "о"; continue; break;
			case "П": sResult += "п"; continue; break;
			case "Р": sResult += "р"; continue; break;
			case "С": sResult += "с"; continue; break;
			case "Т": sResult += "т"; continue; break;
			case "У": sResult += "у"; continue; break;
			case "Ф": sResult += "ф"; continue; break;
			case "Х": sResult += "х"; continue; break;
			case "Ц": sResult += "ц"; continue; break;
			case "Ч": sResult += "ч"; continue; break;
			case "Ш": sResult += "ш"; continue; break;
			case "Щ": sResult += "щ"; continue; break;
			case "Э": sResult += "э"; continue; break;
			case "Ю": sResult += "ю"; continue; break;
			case "Я": sResult += "я"; continue; break;
			
			case "A": sResult += "a"; continue; break;
			case "B": sResult += "b"; continue; break;
			case "C": sResult += "c"; continue; break;
			case "D": sResult += "d"; continue; break;
			case "E": sResult += "e"; continue; break;
			case "F": sResult += "f"; continue; break;
			case "G": sResult += "g"; continue; break;
			case "H": sResult += "h"; continue; break;
			case "I": sResult += "i"; continue; break;
			case "J": sResult += "j"; continue; break;
			case "K": sResult += "k"; continue; break;
			case "L": sResult += "l"; continue; break;
			case "M": sResult += "m"; continue; break;
			case "N": sResult += "n"; continue; break;
			case "O": sResult += "o"; continue; break;
			case "P": sResult += "p"; continue; break;
			case "Q": sResult += "q"; continue; break;
			case "R": sResult += "r"; continue; break;
			case "S": sResult += "s"; continue; break;
			case "T": sResult += "t"; continue; break;
			case "U": sResult += "u"; continue; break;
			case "V": sResult += "v"; continue; break;
			case "W": sResult += "w"; continue; break;
			case "X": sResult += "x"; continue; break;
			case "Y": sResult += "y"; continue; break;
			case "Z": sResult += "z"; continue; break;
		}
		sResult += Simbol;
	}
	return sResult;
}

// Warship 15.08.09 -->
// Перевод всей строки в верхний регистр
String ToUpper(String _text)
{
	String retString, symbol;
	retString = "";
	int length = strlen(_text);

	for(int i = 0; i < length; i++)
	{
		symbol = GetSymbol(_text, i);

		switch(symbol)
		{
			case "а": retString += "А"; continue; break;
			case "б": retString += "Б"; continue; break;
			case "в": retString += "В"; continue; break;
			case "г": retString += "Г"; continue; break;
			case "д": retString += "Д"; continue; break;
			case "е": retString += "Е"; continue; break;
			case "ё": retString += "Ё"; continue; break;
			case "ж": retString += "Ж"; continue; break;
			case "з": retString += "З"; continue; break;
			case "и": retString += "И"; continue; break;
			case "й": retString += "Й"; continue; break;
			case "к": retString += "К"; continue; break;
			case "л": retString += "Л"; continue; break;
			case "м": retString += "М"; continue; break;
			case "н": retString += "Н"; continue; break;
			case "о": retString += "О"; continue; break;
			case "п": retString += "П"; continue; break;
			case "р": retString += "Р"; continue; break;
			case "с": retString += "С"; continue; break;
			case "т": retString += "Т"; continue; break;
			case "у": retString += "У"; continue; break;
			case "ф": retString += "Ф"; continue; break;
			case "х": retString += "Х"; continue; break;
			case "ц": retString += "Ц"; continue; break;
			case "ч": retString += "Ч"; continue; break;
			case "ш": retString += "Ш"; continue; break;
			case "щ": retString += "Щ"; continue; break;
			case "э": retString += "Э"; continue; break;
			case "ю": retString += "Ю"; continue; break;
			case "я": retString += "Я"; continue; break;

			case "a": retString += "A"; continue; break;
			case "b": retString += "B"; continue; break;
			case "c": retString += "C"; continue; break;
			case "d": retString += "D"; continue; break;
			case "e": retString += "E"; continue; break;
			case "f": retString += "F"; continue; break;
			case "g": retString += "G"; continue; break;
			case "h": retString += "H"; continue; break;
			case "i": retString += "I"; continue; break;
			case "j": retString += "J"; continue; break;
			case "k": retString += "K"; continue; break;
			case "l": retString += "L"; continue; break;
			case "m": retString += "M"; continue; break;
			case "n": retString += "N"; continue; break;
			case "o": retString += "O"; continue; break;
			case "p": retString += "P"; continue; break;
			case "q": retString += "Q"; continue; break;
			case "r": retString += "R"; continue; break;
			case "s": retString += "S"; continue; break;
			case "t": retString += "T"; continue; break;
			case "u": retString += "U"; continue; break;
			case "v": retString += "V"; continue; break;
			case "w": retString += "W"; continue; break;
			case "x": retString += "X"; continue; break;
			case "y": retString += "Y"; continue; break;
			case "z": retString += "Z"; continue; break;
		}

		retString += symbol;
	}

	return retString;
}

// Первый символ в верхний регистр
String UpperFirst(String _text)
{
	String firstSymbol = GetSymbol(_text, 0);
	firstSymbol = ToUpper(firstSymbol);

	return firstSymbol + strcut(_text, 1, strlen(_text) - 1);
}

// Первый символ в нижний регистр
String LowerFirst(String _text)
{
	String firstSymbol = GetSymbol(_text, 0);
	firstSymbol = GetStrSmallRegister(firstSymbol);

	return firstSymbol + strcut(_text, 1, strlen(_text) - 1);
}
// <--

//===>>> постановка прерываний на жемчужный генератор
void PearlGen_SetSantaCatalina(string sQuest)
{
	pchar.quest.PearlGen_checkSantaCatalina.win_condition.l1 = "location";
	pchar.quest.PearlGen_checkSantaCatalina.win_condition.l1.location = "Pearl_Jungle_06";
	pchar.quest.PearlGen_checkSantaCatalina.win_condition = "PearlGen_checkSantaCatalina";
}
void PearlGen_SetTeno(string sQuest)
{
	pchar.quest.PearlGen_checkTeno.win_condition.l1 = "location";
	pchar.quest.PearlGen_checkTeno.win_condition.l1.location = "Pearl_Jungle_02";
	pchar.quest.PearlGen_checkTeno.win_condition = "PearlGen_checkTeno";
}
//домашние энкаунтеры. установка тамера 'покинуть дом'
void HouseEnc_TimerGoUot(string qName)
{
	if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
	{
		if (pchar.location == pchar.questTemp.HouseEncTimer && !actLoadFlag && !LAi_grp_alarmactive)
		{
			LAi_group_Attack(characterFromId(pchar.questTemp.HouseEncTimer.Id), Pchar);
		}
		DeleteAttribute(pchar, "questTemp.HouseEncTimer");
	}
}

//удаления группы с задержкой
void Delay_DeleteGroup(string GroupName)
{
	DoQuestCheckDelay("DeleteGroupOnExitLocation", 2.0);
	pchar.quest.DeleteGroupOnExitLocation.GroupName = GroupName;
}
//установка скелетов по пещерам
void SetSkeletonsToLocation(aref _location)
{
	int iRank, iStep;
	float sTime, eTime;
	ref sld;
	bMonstersGen = true; //флаг генерации монстров
	//--> генерим инкремент к рангу
	if (!CheckAttribute(_location, "Monsters_step"))
	{
		iStep = 0;
		_location.Monsters_step = sti(MOD_SKILL_ENEMY_RATE / 1.5 + 0.5);
		SaveCurrentNpcQuestDateParam(_location, "Monsters_step"); //запись даты
	}
	else
	{
		if (GetNpcQuestPastDayParam(_location, "Monsters_step") > 3)
		{
			iStep = 0;
			_location.Monsters_step = sti(MOD_SKILL_ENEMY_RATE / 1.5 + 0.5);
			SaveCurrentNpcQuestDateParam(_location, "Monsters_step"); //запись даты
		}
		else
		{
			iStep = _location.Monsters_step;
			_location.Monsters_step = iStep + sti(MOD_SKILL_ENEMY_RATE / 1.5 + 0.5);
		}
	}
	LAi_group_Delete("EnemyFight");
	//<-- генерим инкремент к рангу
	//--> генерим ранг
	if (sti(pchar.rank) > 6)
	{
		if (sti(pchar.rank) > 20) iRank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE;
		else iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE/2);
	}
	else
	{	//казуалам зеленый свет на начало игры
		iRank = sti(pchar.rank);
	}
	iRank += iStep;
	//<-- генерим ранг
	aref grp;
	makearef(grp, _location.locators.monsters);
	int num = GetAttributesNum(grp);
	int rNum = drand(num);
	for(int i = 0; i < num; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Skelet"+_location.index+"_"+i, "Skel"+(rand(3)+1), "skeleton", "skeleton", iRank, PIRATE, 1, true));
		//если квест по зачистке от нечисти - скелетов делаем круче
		if (CheckAttribute(_location, "DestroyGhost"))
		{
			FantomMakeCoolFighter(sld, sti(pchar.rank)+5, 90, 90, LinkRandPhrase(RandPhraseSimple("blade23","blade25"), RandPhraseSimple("blade30","blade26"), RandPhraseSimple("blade24","blade13")), RandPhraseSimple("pistol6", "pistol3"), MOD_SKILL_ENEMY_RATE*4);
			DeleteAttribute(sld, "SuperShooter");
		}
		else
		{
			if (i == rNum && sti(pchar.rank) > 5)
			{
				FantomMakeCoolFighter(sld, sti(pchar.rank)+5, 80, 80, LinkRandPhrase(RandPhraseSimple("blade23","blade25"), RandPhraseSimple("blade30","blade26"), RandPhraseSimple("blade24","blade13")), RandPhraseSimple("pistol6", "pistol4"), MOD_SKILL_ENEMY_RATE*3);
				DeleteAttribute(sld, "SuperShooter");
			}
			else SetFantomParamFromRank(sld, iRank, true);
		}
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		//if (CheckAttribute(_location, "DestroyGhost"))
		//{
		//	LAi_group_MoveCharacter(sld, "EnemyFight");
		//}
		//else
		//{
			LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
		//}
		ChangeCharacterAddressGroup(sld, _location.id, "monsters", GetAttributeName(GetAttributeN(grp, i)));
	}
	//проверяем, есть ли на локацию квест по очистке от нечисти
	if (CheckAttribute(_location, "DestroyGhost"))
	{
		chrDisableReloadToLocation = true;
		characters[sti(_location.DestroyGhost)].quest.DestroyGhost = "GoodResult";
		DeleteAttribute(_location, "DestroyGhost");
		LAi_LocationDisableMonGenTimer(_location.id, 3); //монстров не генерить 3 дня
		LAi_group_SetCheck(LAI_GROUP_MONSTERS, "OpenTheDoors");
		if (!CheckAttribute(pchar,"Dovahkiin") && rand(3)==0) LAi_group_SetCheck(LAI_GROUP_MONSTERS, "Dovahkiin");
		AddQuestRecordEx(_location.id + "Church_DestroyGhost", "Church_DestroyGhost", "2");
	}
	else
	{
		LAi_LocationDisableMonGenTimer(_location.id, 1); //монстров не генерить 1 день
		pchar.GenQuest.monstersTimer = true;
		SetFunctionTimerConditionParam("GenQuest_EnableMonstersGen", 0, 0, 0, 24, false);
	}

	//#20190928-02
	LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
}

void SetReefSkeletonsToLocation(aref _location, string loc)
{
	int iRank, iStep;
	float sTime, eTime;
	ref sld;
	bMonstersGen = true; //флаг генерации монстров
	//--> генерим инкремент к рангу
	if (!CheckAttribute(_location, "Monsters_step"))
	{
		iStep = 0;
		_location.Monsters_step = sti(MOD_SKILL_ENEMY_RATE / 1.5 + 0.5);
		SaveCurrentNpcQuestDateParam(_location, "Monsters_step"); //запись даты
	}
	else
	{
		if (GetNpcQuestPastDayParam(_location, "Monsters_step") > 3)
		{
			iStep = 0;
			_location.Monsters_step = sti(MOD_SKILL_ENEMY_RATE / 1.5 + 0.5);
			SaveCurrentNpcQuestDateParam(_location, "Monsters_step"); //запись даты
		}
		else
		{
			iStep = _location.Monsters_step;
			_location.Monsters_step = iStep + sti(MOD_SKILL_ENEMY_RATE / 1.5 + 0.5);
		}
	}
	LAi_group_Delete("EnemyFight");
	//<-- генерим инкремент к рангу
	//--> генерим ранг
	if (sti(pchar.rank) > 5)
	{
		if (sti(pchar.rank) > 20) iRank = sti(pchar.rank)+5 + MOD_SKILL_ENEMY_RATE;
		else iRank = sti(pchar.rank)+5 + sti(MOD_SKILL_ENEMY_RATE/2);
	}
	else
	{	//казуалам набьют ебало, ибо ранг+5 и толпа
		iRank = sti(pchar.rank)+5;
	}
	iRank += iStep;
	//<-- генерим ранг
	aref grp;
	int num;
	if (loc == "MountainPath")
	{
		makearef(grp, _location.locators.quest);
		num = GetAttributesNum(grp);
	}
	if (loc == "DeckWithReefs")
	{
		makearef(grp, _location.locators.monsters);
		// num = makeint(GetAttributesNum(grp)/7);
		num = makeint(GetAttributesNum(grp)/4); // LEO: ЛЮБЛЮ РЕЗНЮ!
	}
	int rNum = drand(num);
	LAi_group_Register("ReefAssholes");
	for(int i = 0; i < num; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Skelet"+_location.index+"_"+i, "Skel"+(rand(3)+1), "skeleton", "skeleton", iRank, PIRATE, 1, true));
		//если квест по зачистке от нечисти - скелетов делаем круче

		if (i == rNum && sti(pchar.rank) > 5)
		{
			FantomMakeCoolFighter(sld, iRank, 80, 80, LinkRandPhrase(RandPhraseSimple("blade23","blade25"), RandPhraseSimple("blade30","blade26"), RandPhraseSimple("blade24","blade13")), RandPhraseSimple("pistol6", "pistol4"), MOD_SKILL_ENEMY_RATE*3);
			DeleteAttribute(sld, "SuperShooter");
		}
		else SetFantomParamFromRank(sld, iRank, true);
		if (i == 0)
		{
			if (GetDataDay() == 3 && GetDataMonth() == 3 && GetTime() >= 3.0 && GetTime() < 4.0 && loc == "MountainPath" && !CheckAttribute(pchar,"salasarmet") && CheckAttribute(pchar,"SalasarEventKnow"))
			{
				pchar.salasarmet = true;
				if (MOD_SKILL_ENEMY_RATE == 10 && bHardAnimations) sld = GetCharacter(NPC_GenerateCharacter("salasar", "salasar", "skeleton", "spy", iRank, PIRATE, 1, true)); // LEO: Превозмогаторам - страдать 01.12.2021
				else sld = GetCharacter(NPC_GenerateCharacter("salasar", "salasar", "skeleton", "skeleton", iRank, PIRATE, 1, true));
				sld.name = "Армандо";
				sld.lastname = "Салазар";
				sld.SaveItemsForDead = true;
				if (bHardBoss) sld.AlwaysReload = true;//перезарядка независимо от Дозарядки

				SetSPECIAL(sld, 10,10,10,10,10,10,10); // SPECIAL (Сила, Восприятие, Выносливость, Лидерство, Обучаемость, Реакция, Удача)
				FantomMakeCoolFighter(sld, 55, 100, 100, RandPhraseSimple("blade46","blade42"), "pistol8", 300); //55 лвл, Кханда или Офицерский клеванг, Бландербуз
				LAi_SetHP(sld,2500,2500);

				SelAllPerksToNotPCHAR(sld); //укоротил все перки

				//установить ЛУ и КУ
				SetSelfSkill(sld, 100, 100, 100, 100, 100); //лёгкое, среднее, тяжёлое, пистолет, удача
				SetShipSkill(sld, 100, 100, 100, 100, 100, 100, 100, 100, 100); // лидерство, торговля, точность, пушки, навигация, ремонт, абордаж, защита, скрытность

				sld.money = 1000000;
				GiveItem2Character(sld, "cirass5");
				EquipCharacterbyItem(sld,"cirass5");
				SetCharacterPerk(sld, "Fencer"); //фехт
				AddBonusEnergyToCharacter(sld, 200);
				Log_info("Вы пробудили проклятых!");
				Log_info("Потусторонняя аура пошатнула ваше здоровье.");
				AddCharacterHealth(pchar, -10);
				chrDisableReloadToLocation = true; //пока Салазар жив - хер, а не выход
			}
			if (loc != "MountainPath")
			{
				if (startHeroType != 2 && startHeroType != 7 && !CheckAttribute(pchar, "PGGWhisperQuest"))
				{
					Log_info("Вы пробудили проклятых!");
					chrDisableReloadToLocation = true; //пока Злой Скелет Гигант жив - хер, а не выход
					pchar.GiantEvilSkeleton = true;
					LAi_group_SetCheck("ReefAssholes", "SpawnGiantEvilSkeleton");
				}
				else
				{
					if (CheckAttribute(pchar,"OrderDestroyed"))
					{
						Log_info("Вы пробудили проклятых!");
						chrDisableReloadToLocation = true; //пока Злой Скелет Гигант жив - хер, а не выход
						pchar.GiantEvilSkeleton = true;
						LAi_group_SetCheck("ReefAssholes", "SpawnGiantEvilSkeleton");
					}
					else
					{
						return;
					}
				}
			}
		}
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "ReefAssholes");
		string locator = GetAttributeName(GetAttributeN(grp, i));
		if (loc == "MountainPath")
		{
			if (locator == "rock" || locator == "wall" || locator == "top") locator = "skeleton5"; //нет скелетам на скалах и на крыше
			ChangeCharacterAddressGroup(sld, _location.id, "quest", locator);
			if (i == 0 && sld.name == "Армандо")
			{
				LAi_SetCheckMinHP(sld, 1750.0, false, "SpawnSalasarSupports");
			}
		}
		if (loc == "DeckWithReefs") ChangeCharacterAddressGroup(sld, _location.id, "monsters", locator);
	}

	LAi_LocationDisableMonGenTimer(_location.id, 1); //монстров не генерить 1 день
	pchar.GenQuest.monstersTimer = true;
	SetFunctionTimerConditionParam("GenQuest_EnableMonstersGen", 0, 0, 0, 24, false);

	if (loc == "MountainPath" && CheckAttribute(pchar,"salasarmet") && !CheckAttribute(pchar,"SalasarSpawned"))
	{
		sld = CharacterFromID("salasar");
		LAi_SetActorTypeNoGroup(sld);
		sld.dialog.filename = "Salasar.c";
		sld.dialog.currentnode = "First";
		LAi_ActorDialog(sld, pchar, "", 4.0, 0);
		LAi_SetFightMode(pchar, false);
		LAi_LockFightMode(pchar, false);
		LAi_LocationFightDisable(loadedLocation, true);
		pchar.SalasarSpawned = true;
	}
	else
	{
		LAi_group_SetRelation("ReefAssholes", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_Attack(sld, Pchar);
		LAi_group_SetLookRadius("ReefAssholes", 1000.0);
	}
}

//Перехват всех попыток ГГ залезть в боксы
void QuestCheckTakeBoxes(ref itemsRef)
{
	//Boyer fix
	if (reload_location_index < 0) return; //Boyer fix
	ref locLoad = &locations[reload_location_index];
    ref sld;
	int i, num;
	String title;
	//--> флаг 'в сундуке'
	bMainCharacterInBox = true;
	//<-- флаг 'в сундуке'
	//-------------------- КЛАДЫ ------------>>>>>>>>>>>>>

	//Спавн проклятого кэпа
	if (!CheckAttribute(pchar,"treasurelocation"))
	{
		if (CheckCharacterItem(pchar,"letter_notes") && locLoad.id == "Bermudes_Dungeon" && !CheckAttribute(pchar,"FishHeadsSpawned"))
		{
			Log_info("Вы нашли вторую часть записки.");
			/*string chesttype = "";
			switch (drand(3))
			{
				case 0: chesttype = "Chest_ammo"; break;
				case 1: chesttype = "Chest_treasure"; break;
				case 2: chesttype = "Chest_quest"; break;
				case 3: chesttype = "Chest_Craftsmans"; break;
			}
			TakeNItems(pchar,chesttype,1);
			Log_info("Вы обнаружили сундучок.");*/
			Log_info("Это что ещё за шум?");
			ChangeItemDescribe("letter_notes", "CSPD2");
			pchar.FishHeadsSpawned = true;
			SpawnFishHeads();
			pchar.quest.EasterFish.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EasterFish.win_condition.l1.location = pchar.location;
			pchar.quest.EasterFish.function = "FishHDS";
			return;
		}
		spawnToughSkeleton(locLoad);
	}
	if (CheckAttribute(pchar,"treasurelocation"))
	{
		if (locLoad.id != pchar.treasurelocation) spawnToughSkeleton(locLoad);
	}
	/*if (locLoad.id != pchar.treasurelocation)
	{
		 //&& locLoad != pchar.treasurelocation
		spawnToughSkeleton(locLoad);
	}*/
	if (CheckAttribute(itemsRef, "Treasure"))
	{
		Log_Info("Похоже, что это и есть клад.");
		PlaySound("interface\notebook.wav");
		DeleteAttribute(itemsRef, "Treasure");
		DeleteAttribute(PChar, "treasurelocation");

		pchar.questTemp.treasurecount = sti(pchar.questTemp.treasurecount) + 1;
		if(sti(pchar.questTemp.treasurecount) >= 5) UnlockAchievement("AchTreasure", 1);
		if(sti(pchar.questTemp.treasurecount) >= 15) UnlockAchievement("AchTreasure", 2);
		if(sti(pchar.questTemp.treasurecount) >= 30) UnlockAchievement("AchTreasure", 3);

		//eddy. для безконфликтности квестов

		if(!CheckAttribute(itemsRef, "PiratesOnUninhabitedTreasure"))
		{
			if (LAi_LocationIsMonstersGen(locLoad) && !bMonstersGen && LAi_grp_playeralarm == 0)
			{
				SetSkeletonsToLocation(locLoad);
			}
		}
		else
		{
			title = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;

			if(CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.UseMainPiratename"))
			{
				AddQuestRecordEx(title, "PiratesOnUninhabited", "10");
				AddQuestUserData(title, "sSex", GetSexPhrase("му","й"));
			}
			else
			{
				AddQuestRecordEx(title, "PiratesOnUninhabited", "9");
				AddQuestUserData(title, "sSex", GetSexPhrase("ел","ла"));
				AddQuestUserData(title, "shore", XI_ConvertString(PChar.location + "Dat"));
			}

			CloseQuestHeader(title);

			PChar.Quest.PiratesOnUninhabited_ShoreTreasureLose.over = "yes";

			DeleteAttribute(itemsRef, "PiratesOnUninhabitedTreasure");
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
		}

		if(CheckAttribute(itemsRef, "Hold_GenQuest_Treasure"))
		{
			if(sti(pchar.GenQuest.Hold_GenQuest.Treasure) == 0)
			{
				AddQuestRecord("HoldQuest", "18");
				AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.Name);
			}
			else
			{
				AddQuestRecord("HoldQuest", "17");
				AddQuestUserData("HoldQuest", "sCapName", pchar.GenQuest.Hold_GenQuest.CapName);
			}
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(itemsRef, "Hold_GenQuest_Treasure");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");
		}
	}
	//<<<<<<<<<<---------- КЛАДЫ --------------------------
	//-->> Генератор грабежа жемчуга, у главы поселения
	if (GetCharacterIndex("HeadMan_2") != -1 && locLoad.id == "PearlTown2_Townhall")
	{
		if (pchar.questTemp.Sharp.SeekSpy != "begin" && pchar.questTemp.Sharp.SeekSpy != "over")
		{	//если взят квест на поиски крысы Шарпа - закрываем его
			pchar.questTemp.Sharp.SeekSpy = "over";
			CloseQuestHeader("SharpPearl_SeekSpy");
    		ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, SPAIN, -10);
		}
		ChangeCharacterReputation(pchar, -20);
		SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
		LAi_group_Attack(characterFromId("HeadMan_2"), Pchar);
		chrDisableReloadToLocation = true;
		pchar.quest.PearlGen_HeadMan_2_death.win_condition.l1 = "NPC_Death";
		pchar.quest.PearlGen_HeadMan_2_death.win_condition.l1.character = "HeadMan_2";
		pchar.quest.PearlGen_HeadMan_2_death.win_condition = "OpenTheDoors";
		return;
	}
	if (GetCharacterIndex("HeadMan_1") != -1 && locLoad.id == "PearlTown1_Townhall")
	{
		if (pchar.questTemp.Sharp.SeekSpy != "begin" && pchar.questTemp.Sharp.SeekSpy != "over")
		{	//если взят квест на поиски крысы Шарпа - закрываем его
			pchar.questTemp.Sharp.SeekSpy = "over";
			CloseQuestHeader("SharpPearl_SeekSpy");
    		ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, SPAIN, -10);
		}
		ChangeCharacterReputation(pchar, -20);
		SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
		LAi_group_Attack(characterFromId("HeadMan_1"), Pchar);
		chrDisableReloadToLocation = true;
		pchar.quest.PearlGen_HeadMan_1_death.win_condition.l1 = "NPC_Death";
		pchar.quest.PearlGen_HeadMan_1_death.win_condition.l1.character = "HeadMan_1";
		pchar.quest.PearlGen_HeadMan_1_death.win_condition = "OpenTheDoors";
		return;
	}
	//<<-- Генератор грабежа жемчуга, у главы поселения
	//-->> Квест Изабеллы.
	if (GetCharacterIndex("Husband") != -1  && locLoad.id == "SanJuan_houseSp6" && characters[GetCharacterIndex("Isabella")].location != "SanJuan_houseSp6" && characters[GetCharacterIndex("Husband")].location == "SanJuan_houseSp6")
	{
		ChangeCharacterReputation(pchar, -3);
		SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
		sld = characterFromId("Husband");
		LAi_SetWarriorType(sld);
		//LAi_SetImmortal(sld, false);
		LAi_group_Attack(sld, Pchar);
		chrDisableReloadToLocation = true;
		LAi_LocationFightDisable(locLoad, false);
		LocatorReloadEnterDisable(locLoad.id, "reload2", true);
		pchar.quest.Husband_death.win_condition.l1 = "NPC_Death";
		pchar.quest.Husband_death.win_condition.l1.character = "Husband";
		pchar.quest.Husband_death.win_condition = "OpenTheDoors";
	}
}
//открытие дверей в локации города для коммонов. только на текущие сутки + еще одни, потом снимается само.
void SetOpenDoorCommonLoc(string City, string locationId)
{
	aref arRld, arDis, arRld2, arDis2;
	string LocId;
	makearef(arRld, locations[FindLocation(City + "_town")].reload);
    int Qty2, n, i;
	int Qty = GetAttributesNum(arRld);
	for (i=0; i<Qty; i++)
    {
    	arDis = GetAttributeN(arRld, i);
		LocId = arDis.go;
    	if (LocId == locationId)
    	{
			arDis.disable = false;
			arDis.canEnter = true;
			return;
    	}
		if (arDis.label != "Sea")
		{
			makearef(arRld2, Locations[FindLocation(LocId)].reload);
			Qty2 = GetAttributesNum(arRld2);
			for (n=0; n<Qty2; n++)
			{
    			arDis2 = GetAttributeN(arRld2, n);
				LocId = arDis2.go;
				if (LocId == locationId)
    			{
					arDis.disable = false;
					arDis.canEnter = true;
					return;
				}
			}
		}
    }
}

//личные боевые навыки, нужны для экспы после сухопутных боев
void AddComplexSelfExpToScill(int l, int m, int h, int p)
{
	AddCharacterExpToSkill(pchar, "FencingLight", l);//легкое оружие
	AddCharacterExpToSkill(pchar, "Fencing", m);//среднее оружие
	AddCharacterExpToSkill(pchar, "FencingHeavy", h);//тяжелое оружие
	AddCharacterExpToSkill(pchar, "Pistol", p); //пистоли
}
