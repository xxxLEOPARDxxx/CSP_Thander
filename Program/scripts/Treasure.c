// клады из ВМЛ

//  Карты сокровищ  ГЕНЕРАТОР -->
string GetIslandForTreasure()
{
	int iNum, m;
	ref Itm;
	aref arDest, arImt;
	string sAttr;

	m = 0;
	string sCurIsland = GetCharacterCurrentIslandId(pchar);
	makearef(arDest, NullCharacter.TravelMap.Islands);
	iNum = GetAttributesNum(arDest);

	string sArray[50]; // динамические массивы в Шторме не организуешь :(
	for (int i = 0; i<iNum; i++)
	{
		arImt = GetAttributeN(arDest, i);
		sAttr = GetAttributeName(arImt);
		if(CheckAttribute(&NullCharacter,"TravelMap.Islands." + sAttr + ".Treasure"))
		{
			if(sCurIsland == sAttr || CheckTreasureMaps(sAttr)) continue;
			else
			{
				sArray[m] = sAttr;
				m++;
			}
		}
	}
	m = rand(m-1);
	return sArray[m];
}

bool CheckTreasureMaps(string sIsland)
{
	ref Itm;

	if(GetCharacterItem(pchar,"mapQuest") > 0)
	{
		itm = ItemsFromID("mapQuest");
		if(CheckAttribute(itm, "MapIslId") && itm.MapIslId == sIsland) return true;
	}
	if(GetCharacterItem(pchar,"map_full") > 0)
	{
		itm = ItemsFromID("map_full");
		if(CheckAttribute(itm, "MapIslId") && itm.MapIslId == sIsland) return true;
	}
	return false;
}

string GetLocationForTreasure(string island)
{
    int iNum;
	aref arDest, arImt;
	string sAttr;

	makearef(arDest, NullCharacter.TravelMap.Islands.(island).Treasure);
	iNum = GetAttributesNum(arDest);
    iNum = rand(iNum-1);

    arImt = GetAttributeN(arDest, iNum);
	Log_TestInfo("Локация: "+GetAttributeName(arImt));
	return GetAttributeName(arImt);
}

string GetBoxForTreasure(string island, string location)
{
    int iNum;
	aref arDest, arImt;
	string sAttr;

	makearef(arDest, NullCharacter.TravelMap.Islands.(island).Treasure.(location));
	iNum = GetAttributesNum(arDest);
    iNum = rand(iNum-1);

    arImt = GetAttributeN(arDest, iNum);
	Log_TestInfo("Локатор: "+GetAttributeValue(arImt));
	return GetAttributeValue(arImt);  // тут не атрибут, а значеие
}

// не при деле....
string GetFileMapForTreasure(string island)
{
    int n;

    for (n = 0; n < ITEMS_QUANTITY; n++)
	{
		if (CheckAttribute(&Items[n], "MapIsland") )
		{
            if (Items[n].MapIsland == island)
            {
                return Items[n].imageTga;
            }
		}
    }
    return "";
}

void GenerateMapsTreasure(ref item, int iProbability1, int iProbability2)
{
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_jam")) item.BoxTreasure.map_jam = 1;
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_cayman")) item.BoxTreasure.map_cayman = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_barbados")) item.BoxTreasure.map_barbados = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_trinidad")) item.BoxTreasure.map_trinidad = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_Curacao")) item.BoxTreasure.map_Curacao = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_martiniqua")) item.BoxTreasure.map_martiniqua = 1;
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_dominica")) item.BoxTreasure.map_dominica = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_puerto")) item.BoxTreasure.map_puerto = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_cuba")) item.BoxTreasure.map_cuba = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_hisp")) item.BoxTreasure.map_hisp = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_nevis")) item.BoxTreasure.map_nevis = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_guad")) item.BoxTreasure.map_guad = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_antigua")) item.BoxTreasure.map_antigua = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_TORTUGA")) item.BoxTreasure.map_TORTUGA = 1;
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_terks")) item.BoxTreasure.map_terks = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_sm")) item.BoxTreasure.map_sm = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_bermudas")) item.BoxTreasure.map_bermudas = 1;
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_Pearl")) item.BoxTreasure.map_Pearl = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_beliz")) item.BoxTreasure.map_beliz = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_santa")) item.BoxTreasure.map_santa = 1;
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_maine_1")) item.BoxTreasure.map_maine_1 = 1;
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_maine_2")) item.BoxTreasure.map_maine_2 = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_panama")) item.BoxTreasure.map_panama = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_maracaibo")) item.BoxTreasure.map_maracaibo = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_cumana")) item.BoxTreasure.map_cumana = 1;
}

void FillMapForTreasure(ref item)
{
    item.MapIslId   = GetIslandForTreasure();
    item.MapLocId   = GetLocationForTreasure(item.MapIslId);
    item.MapBoxId   = GetBoxForTreasure(item.MapIslId, item.MapLocId);
    item.MapTypeIdx = drand(2);

    // генерим клад
    DeleteAttribute(item, "BoxTreasure");
	if (GetCharacterSPECIALSimple(pchar, SPECIAL_L) > rand(10)) FillBoxForTreasure(item, rand(1));
    else FillBoxForTreasure(item, rand(3));
    FillBoxForTreasureAddition(item);
	Xzibit(item);
	if (rand(100)==0) BookAdd(1, item);//книги в клад 1 уровня

    if (!CheckAttribute(Pchar, "GenQuest.TreasureBuild"))
    {
        if (rand(12+GetCharacterSPECIALSimple(pchar, SPECIAL_L)) == 1) item.MapTypeIdx = -1;
		pchar.PGGTreasureStolen = true;
    }
    else
    {// из кусочков даем супер вещи
       /*while (item.MapLocId == "Muelle_town_04" || item.MapLocId == "Havanna_town_04") // не для халявы
       {
            item.MapIslId   = GetIslandForTreasure();
            item.MapLocId   = GetLocationForTreasure(item.MapIslId);
            item.MapBoxId   = GetBoxForTreasure(item.MapIslId, item.MapLocId);
       } */
       FillBoxForTreasureSuper(item);
	   if (GetCharacterSPECIALSimple(pchar, SPECIAL_L) > rand(10)) FillBoxForTreasureSuper(item);
	   if (rand(100)==0) item.BoxTreasure.mushket_Shtuzer = 1;
	   if (rand(100)==0) BookAdd(2, item);//книги в клад 2 уровня
    }
    DeleteAttribute(Pchar, "GenQuest.TreasureBuild"); //сборный

    if (sti(item.MapTypeIdx) != -1)
    {
        Pchar.quest.SetTreasureFromMap.win_condition.l1          = "location";
        Pchar.quest.SetTreasureFromMap.win_condition.l1.location = item.MapLocId;
        Pchar.quest.SetTreasureFromMap.win_condition             = "SetTreasureFromMap";
    }
}

void FillMapForUniqueTreasure(ref item, string type)
{
	item.MapIslId   = GetIslandForTreasure();
	item.MapLocId   = GetLocationForTreasure(item.MapIslId);
	item.MapBoxId   = GetBoxForTreasure(item.MapIslId, item.MapLocId);
	item.MapTypeIdx = 0;
	item.uniquep = type;

	// генерим клад
	DeleteAttribute(item, "BoxTreasure");

	FillBoxForTreasure(item, rand(1));
	FillBoxForTreasureAddition(item);
	Xzibit(item);
	FillBoxForTreasureSuper(item);
	FillBoxForTreasureSuper(item);
	BookAdd(1, item);//книги в клад 1 уровня
	BookAdd(2, item);//книги в клад 2 уровня
	Log_TestInfo("treasure "+type);

	switch (type)
	{
		case "Barbarigo":
			item.BoxTreasure.gold = 400000+rand(600000);
			item.BoxTreasure.blade41 = 1;
			item.BoxTreasure.cirass5 = 1;
		break;
		case "BlackBeard":
			item.BoxTreasure.gold = 800000+rand(200000);
			item.BoxTreasure.jewelry5 = 900+rand(100);
			item.BoxTreasure.howdah = 1;
		break;
		case "Levasser":
			item.BoxTreasure.gold = 600000+rand(400000);
			item.BoxTreasure.jewelry1 = 250+rand(150);
			item.BoxTreasure.jewelry2 = 250+rand(150);
			item.BoxTreasure.jewelry3 = 250+rand(150);
			item.BoxTreasure.jewelry4 = 250+rand(150);
			item.BoxTreasure.grape_mushket = 1;
		break;
	}

	Pchar.quest.SetTreasureFromMap.win_condition.l1          = "location";
	Pchar.quest.SetTreasureFromMap.win_condition.l1.location = item.MapLocId;
	Pchar.quest.SetTreasureFromMap.win_condition             = "SetTreasureFromMap";
}

string GetUniquePirateName()
{
	int count = -1;
	string name[3];
	/*if (!CheckAttribute(pchar,"questTemp.UniquePirate.Barbarigo"))
	{
		pchar.questTemp.UniquePirate.Barbarigo = 1;
		return "Barbarigo";
	}
	if (!CheckAttribute(pchar,"questTemp.UniquePirate.BlackBeard"))
	{
		pchar.questTemp.UniquePirate.BlackBeard = 1;
		return "BlackBeard";
	}
	if (!CheckAttribute(pchar,"questTemp.UniquePirate.Levasser"))
	{
		pchar.questTemp.UniquePirate.Levasser = 1;
		return "Levasser";
	}*/
	if (!CheckAttribute(pchar,"questTemp.UniquePirate.Barbarigo"))
	{
		count++;
		name[count]="Barbarigo";
	}
	if (!CheckAttribute(pchar,"questTemp.UniquePirate.BlackBeard"))
	{
		count++;
		name[count]="BlackBeard";
	}
	if (!CheckAttribute(pchar,"questTemp.UniquePirate.Levasser"))
	{
		count++;
		name[count]="Levasser";
	}
	if (count == -1) return "";
	else
	{
		string resultname = name[rand(count)];
		pchar.questTemp.UniquePirate.(resultname) = 1;
		return resultname;
	}

	return "";
}

string GetUniquePirateNameString(string type)
{
	switch (type)
	{
		case "Barbarigo": return "Агостино Барбариго"; break;
		case "BlackBeard": return "Чёрной Бороды"; break;
		case "Levasser": return "Левассера"; break;
	}
	return "";
}

void BookAdd(int value, ref item)//книги - Gregg
{
	switch (value)
	{
		string book = "";
		case 1:
		book = "book3_"+(rand(13)+1);
		item.BoxTreasure.(book) = 1;
		break;
		case 2:
		book = "book4_"+(rand(13)+1);
		item.BoxTreasure.(book) = 1;
		break;
	}
}

void Xzibit(ref item)//сундучный метод
{
	switch (rand(3))
	{
		case 0: item.BoxTreasure.Chest_ammo = 1; break;
		case 1: item.BoxTreasure.Chest_treasure = 1; break;
		case 2: item.BoxTreasure.Chest_quest = 1; break;
		case 3: item.BoxTreasure.Chest_Craftsmans = 1; break;
	}
}

void FillBoxForTreasure(ref item, int i)
{
	// определяем тип
	switch (i)
	{
		// good
		case 0:
		    if (rand(1) == 1)
	        {
            	item.BoxTreasure.jewelry2 = 2 + rand(30);
	        }
	        else
	        {
	            item.BoxTreasure.jewelry3 = 10 + rand(3);
	        }
	        if (rand(1) == 1)
	        {
            	item.BoxTreasure.jewelry3 = 1 + rand(30);
	        }
	        if (rand(1) == 1)
	        {
            	item.BoxTreasure.jewelry5 = 5 + rand(60);
	        }
	        if (rand(1) == 1)
	        {
            	item.BoxTreasure.jewelry7 = 15 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.jewelry10 = 15 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.jewelry13 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.jewelry14 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.jewelry17 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.jewelry18 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral2 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral5 = 5 + rand(100);
	        }
	        if (rand(4) == 1)
	        {
            	item.BoxTreasure.suit_2 = 1;
	        }
			GenerateMapsTreasure(item, 35, 70);
	    break;
	    // best
	    case 1:
            if (rand(2) == 1)
	        {
            	item.BoxTreasure.chest = 1 + rand(14);
	        }
	        else
	        {
	            item.BoxTreasure.jewelry12 = 10 + rand(3);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.icollection = 1 + rand(4);
	        }
	        if (rand(1) == 1)
	        {
            	item.BoxTreasure.jewelry1 = 15 + rand(100);
	        }
	        if (rand(1) == 1)
	        {
            	item.BoxTreasure.jewelry12 = 15 + rand(100);
	        }
	        if (rand(1) == 1)
	        {
            	item.BoxTreasure.jewelry11 = 15 + rand(100);
	        }
	        if (rand(1) == 1)
	        {
            	item.BoxTreasure.jewelry6 = 5 + rand(100);
	        }
	        if (rand(4) == 1)
	        {
            	item.BoxTreasure.suit_3 = 1;
	        }
	    break;
	    // bad
	    case 2:
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.rabble = 5 + rand(100);
	        }
	        else
	        {
                item.BoxTreasure.blade1 = 5 + rand(100);//fix
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.blade1 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.blade5 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.jewelry16 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral4 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral6 = 5 + rand(200);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral7 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral9 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.mineral10 = 25 + rand(300);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.indian4 = 15 + rand(300);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.indian8 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.indian9 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.indian13 = 5 + rand(100);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.indian16 = 5 + rand(200);
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.blade5 = 1;
	        }
	        if (rand(2) == 1)
	        {
            	item.BoxTreasure.suit_1 = 1;
	        }
	    break;

	    case 3:
	        FillBoxForTreasure(item, 0);
	    break;
	}
}

void FillBoxForTreasureAddition(ref item)
{
    float   nLuck   = GetCharacterSkillToOld(Pchar, SKILL_FORTUNE);

    if (5*nLuck > rand(55))
    {
	    if (GetCharacterItem(Pchar, "map_part1") == 0)
	    {
	        item.BoxTreasure.map_part1 = 1;
	    }
	    else
	    {
	        if (GetCharacterItem(Pchar, "map_part2") == 0)
		    {
		        item.BoxTreasure.map_part2 = 1;
		    }
	    }
	}
	// +1 вещи
	switch (rand(40))
	{
		case 1:
		    item.BoxTreasure.STATUE1 = 1;
		break;
		case 2:
		    item.BoxTreasure.jewelry9 = 1;
		break;
		case 3:
		    item.BoxTreasure.jewelry15 = 1;
		break;
		case 4:
		    item.BoxTreasure.jewelry8 = 1;
		break;
		case 5:
		    item.BoxTreasure.indian7 = 1;
		break;
		case 6:
		    item.BoxTreasure.indian2 = 1;
		break;
		case 7:
		    item.BoxTreasure.jewelry4 = 1;
		break;
		case 8:
		    item.BoxTreasure.indian3 = 1;
		break;
		case 9:
		    item.BoxTreasure.indian1 = 1;
		break;
		case 10:
		    item.BoxTreasure.indian5 = 1;
		break;
		case 11:
		    item.BoxTreasure.indian6 = 1;
		break;
		case 12:
		    item.BoxTreasure.indian10 = 1;
		break;
		case 13:
		    item.BoxTreasure.indian12 = 1;
		break;
		case 14:
		    item.BoxTreasure.indian14 = 1;
		break;
		case 15:
		    item.BoxTreasure.indian15 = 1;
		break;
		case 16:
		    item.BoxTreasure.indian17 = 1;
		break;
		case 17:
		    item.BoxTreasure.indian18 = 1;
		break;
		case 18:
		    item.BoxTreasure.indian19 = 1;
		break;
		case 19:
		    item.BoxTreasure.indian20 = 1;
		break;
		case 20:
		    item.BoxTreasure.indian21 = 1;
		break;
		case 21:
		    item.BoxTreasure.indian22 = 1;
		break;
		case 22:
		    item.BoxTreasure.Mineral3 = 1;
		break;
		case 23:
		    item.BoxTreasure.Mineral8 = 1;
		break;
		case 24:
		    item.BoxTreasure.Coins = 1;
		break;
		case 25:
		    item.BoxTreasure.sculMa1 = 1;
		break;
		case 26:
		    item.BoxTreasure.sculMa2 = 1;
		break;
		case 27:
		    item.BoxTreasure.sculMa3 = 1;
		break;
	}
	GenerateMapsTreasure(item, 10, 20);
	//добавим тотемы
	string sName = "Totem_" + (rand(9)+1);
	if (!CheckMainHeroTotem(sName) && rand(20)==1) item.BoxTreasure.(sName) = 1;
}

void FillBoxForTreasureSuper(ref item)
{
    float     nLuck   = GetCharacterSkillToOld(Pchar, SKILL_FORTUNE);
	int     i;
	string  itmName;

    if (3*nLuck > rand(21))// еще поди найди 2 куска
    {
		i = 0;
		itmName = "";
		while (itmName == "" && i < 15)
		{
            switch (rand(21))
			{
                case 0:
                	itmName = GetGeneratedItem("blade13");
				break;
				case 1:
        			itmName = GetGeneratedItem("blade20");
				break;
				case 2:
        			itmName = GetGeneratedItem("blade23");
				break;
				case 3:
        			itmName = GetGeneratedItem("blade24");
				break;
				case 4:
        			itmName = "pistol4";
				break;
				case 5:
        			itmName = "indian11";//"idol";
				break;
				case 6:
                    itmName = GetGeneratedItem("topor2"); // to_do
				break;
				case 7:
        			itmName = "spyglass4";
				break;
				case 8:
        			itmName = "cirass3";
				break;
				case 9:
        			itmName = "indian11";
				break;
				case 10:
        			itmName = "cirass4";
				break;
				case 11:
        			itmName = "spyglass5";
				break;
				case 12:
        			itmName = GetGeneratedItem("blade25");
				break;
				case 13:
        			itmName = GetGeneratedItem("blade26");
				break;
				case 14:
        			itmName = GetGeneratedItem("blade30");
				break;
				case 15:
        			itmName = GetGeneratedItem("blade33");
				break;
				case 16:
        			itmName = "mushket";
				break;
				case 17:
        			itmName = "Map_Best";
				break;
				case 18:
					itmName = "BackPack5";
				break;
				case 19:
					itmName = "talisman8";
				break;
				case 20:
					itmName = "talisman1";
				break;
				case 21:
					itmName = "topor_emperor";
				break;
			}
			if (GetCharacterItem(Pchar, itmName) > 0)
		    {
          		itmName = "";
		    }
		    i++;
	    }
	    if (itmName != "")
	    {
	        item.BoxTreasure.(itmName) = 1;
	    }
	}
}

void SetTreasureBoxFromMap()
{
    aref   item;
    ref    loc;
    string box;
    aref   arToBox;
    aref   arFromBox;

    if (GetCharacterItem(Pchar, "map_full")>0 )
    {
        Log_Info("Сокровища где-то рядом!");
		//Запрет спавна проклятого кэпа в этой локации
		ref locLoad = &locations[reload_location_index];
		pchar.treasurelocation = locLoad.id;

        PlaySound("interface\notebook.wav");
		pchar.treasurelocation = locLoad.id;
		Statistic_AddValue(Pchar, "Treasure", 1);
        // немного веселой жизни
		if(MOD_SKILL_ENEMY_RATE == 10)
			Map_CreateFastWarriorTreasure();
		else
			TraderHunterOnMap();
        if( CheckAttribute(Pchar,"location.from_sea") )
        {
            if (rand(2) == 1) //33 процента
            {
                Pchar.quest.SetTreasureHunter.win_condition.l1          = "location";
                Pchar.quest.SetTreasureHunter.win_condition.l1.location = Pchar.location.from_sea;
                Pchar.quest.SetTreasureHunter.win_condition             = "";
				if (rand(1) == 1 && CheckAttribute(pchar, "PGGTreasureStolen")) //50 процентов что это будет ПГГ
				{
					int heroSelected = 1;
					string chosenHero = rand(PsHeroQty);
					for (i = 0; i < 25; i++)
					{
						if (sti(chosenHero) != 0)
						{
							sld = CharacterFromID("PsHero_"+chosenHero);
							if (sld.PGGAi.location == "Dead" || IsCompanion(sld) || IsOfficer(sld) || sld.dialog.filename == "Enc_Officer_dialog.c")
							{
								chosenHero = rand(PsHeroQty);
							}
							else
							{
								heroSelected = 0;
								pchar.chosenTreasureHero = sld.id;
								PGG_Disband_Fleet(sld);
							}
						}
						else
						{
							chosenHero = rand(PsHeroQty);
						}
					}
					if(heroSelected == 0)
					{
						Pchar.quest.SetTreasureHunter.function    = "SetPGGTreasureHunter";
						Log_TestInfo("Вас встретит ПГГ " + pchar.chosenTreasureHero);
					}
					else
					{
						Pchar.quest.SetTreasureHunter.function    = "SetTreasureHunter";
					}
				}
				else
				{
					Pchar.quest.SetTreasureHunter.function    = "SetTreasureHunter";
				}
            }
        }
		DeleteAttribute(pchar, "PGGTreasureStolen");
        Items_FindItem("map_full", &item);

        box = item.MapBoxId;

        loc = &locations[FindLocation(item.MapLocId)];
        loc.(box).items = "";

        makearef(arToBox, loc.(box).items);
        makearef(arFromBox, item.BoxTreasure);
        CopyAttributes(arToBox, arFromBox);

        loc.(box) = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
        loc.(box).Treasure =  true; // признак сокровища в сундуке

        DeleteAttribute(item, "MapIslId");
		DeleteAttribute(item, "uniquep");
        TakeNItems(Pchar, "map_full", -1);
    }
}
//  Карты сокровищ  ГЕНЕРАТОР <--

// погодня за ГГ на карте
void  TraderHunterOnMap()
{
    // немного веселой жизни
    ref  sld;
    int  i;

    string sCapId = "TraderHunter";
    string sGroup = "Sea_" + sCapId + "1";

	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
    for (i = 1; i <= GetCompanionQuantity(pchar); i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "off_hol_2", "man", "man", sti(PChar.rank) + 5, PIRATE, 15, true));
        SetShipHunter(sld);
        SetFantomParamHunter(sld); //крутые парни
        SetCaptanModelByEncType(sld, "war");
        sld.AlwaysEnemy = true;
        sld.DontRansackCaptain = true;
        sld.mapEnc.type = "war";
        sld.mapEnc.Name = "Джентльмены удачи";
		sld.hunter = "pirate";
        Group_AddCharacter(sGroup, sCapId + i);
    }

    Group_SetGroupCommander(sGroup, sCapId+ "1");
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
	Map_CreateFastTradeHunter("", sCapId + "1", 8);
}

void SetTreasureHunter(string temp)
{
    int    j, i, k;
	string sTemp, sCapId;
	ref    sld;
	bool   ok;

	if (chrDisableReloadToLocation) return; // идет некий другой квест с запретом выхода

    Pchar.GenQuest.Hunter2Pause            = true;

    j = GetOfficersQuantity(Pchar) + 2;

	sCapId = "LandHunter0";
    sTemp = "LAND_HUNTER";
	ok = true;
	arrayNPCModelHow = 0;
    for (i = 1; i <= j; i++)
    {
        if (MOD_SKILL_ENEMY_RATE == 10 && bHardAnimations) sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "Pirate_" + (rand(24) + 1), "man", "spy", sti(PChar.rank) + 5, PIRATE, 0, true));
        else sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "Pirate_" + (rand(24) + 1), "man", "man_fast", sti(PChar.rank) + 5, PIRATE, 0, true));
        SetFantomParamHunter(sld); //крутые парни
        sld.Dialog.CurrentNode = "TreasureHunter";
        sld.dialog.filename = "Hunter_dialog.c";
        sld.greeting = "Gr_HUNTER";
		if (bHardBoss) sld.AlwaysReload = true;//перезарядка независимо от Дозарядки
        sld.location = "none"; // вот где порылась собака!!!!!!!!!!!

        /*SetModelPirate(sld);
        k = 0;
		while (!CheckNPCModelUniq(sld) && k < 10)
		{
		    k++;
			SetModelPirate(sld);
		}
		arrayNPCModel[arrayNPCModelHow] = sld.model;
		arrayNPCModelHow++;*/

        LAi_SetActorTypeNoGroup(sld);
        LAi_SetCheckMinHP(sld, (LAi_GetCharacterHP(sld) - 1), false, "Battle_Hunters_Land");
        if (PlaceCharacter(sld, "goto", "random_must_be_near") == "" && i == 1) // fix если вдруг нет в локации
        {
            ok = false;
            break;
        }
        LAi_ActorFollow(sld, pchar, "", 8.0);
        //LAi_Actor2WaitDialog(sld, pchar); // ждать диалог, но бежать
        LAi_group_MoveCharacter(sld, sTemp);
    }

	LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER_OWN, LAI_GROUP_NEITRAL);

	LAi_group_ClearAllTargets();
	LAi_SetFightModeForOfficers(false);
	if (ok)
    {
        PChar.HunterCost = makeint(sti(Pchar.money) / 5) + rand(20)*1000; //сразу генерим
        //#20180912-02 Fix
        PChar.HunterCost.Qty = j; //i;
        PChar.HunterCost.TempHunterType = "";
        sld = characterFromID(sCapId + "1");
        LAi_type_actor_Reset(sld);
        LAi_ActorDialog(sld, pchar, "", 4.0, 0);
		chrDisableReloadToLocation = true;
		DoQuestCheckDelay("OpenTheDoors", 5.0);
    }
}

void SetPGGTreasureHunter(string temp)
{
    int    j, i, k;
	string sTemp, sCapId;
	ref    sld;
	bool   ok;

	if (chrDisableReloadToLocation) return; // идет некий другой квест с запретом выхода

    Pchar.GenQuest.Hunter2Pause            = true;

    j = GetOfficersQuantity(Pchar) + 2;

	sCapId = "LandHunter0";
    sTemp = "LAND_HUNTER";
	ok = true;
	arrayNPCModelHow = 0;
    for (i = 1; i <= j; i++)
    {
		if (i == 1)
		{
			sld = CharacterFromID(pchar.chosenTreasureHero);
			sld.Dialog.CurrentNode = "TreasureHunterPGG";
			sld.location = "none"; // вот где порылась собака!!!!!!!!!!!
		}
		else
		{
			if (MOD_SKILL_ENEMY_RATE == 10 && bHardAnimations)sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "Pirate_" + (rand(24) + 1), "man", "spy", sti(PChar.rank) + 5, PIRATE, 0, true));
			else sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "Pirate_" + (rand(24) + 1), "man", "man_fast", sti(PChar.rank) + 5, PIRATE, 0, true));
			SetFantomParamHunter(sld); //крутые парни
			sld.greeting = "Gr_HUNTER";
			if (bHardBoss) sld.AlwaysReload = true;//перезарядка независимо от Дозарядки
			sld.location = "none"; // вот где порылась собака!!!!!!!!!!!
			/*SetModelPirate(sld);
			k = 0;
			while (!CheckNPCModelUniq(sld) && k < 10)
			{
				k++;
				SetModelPirate(sld);
			}
			arrayNPCModel[arrayNPCModelHow] = sld.model;
			arrayNPCModelHow++;*/
			sld.dialog.filename = "Hunter_dialog.c";
			sld.Dialog.CurrentNode = "TreasureHunter";
		}

        LAi_SetActorTypeNoGroup(sld);
        LAi_SetCheckMinHP(sld, (LAi_GetCharacterHP(sld) - 1), false, "Battle_PGGHunters_Land");
        if (PlaceCharacter(sld, "goto", "random_must_be_near") == "" && i == 1) // fix если вдруг нет в локации
        {
            ok = false;
            break;
        }
        LAi_ActorFollow(sld, pchar, "", 8.0);
        //LAi_Actor2WaitDialog(sld, pchar); // ждать диалог, но бежать
        LAi_group_MoveCharacter(sld, sTemp);
    }

	LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER_OWN, LAI_GROUP_NEITRAL);

	LAi_group_ClearAllTargets();
	LAi_SetFightModeForOfficers(false);
	if (ok)
    {
        PChar.HunterCost = makeint(sti(Pchar.money) / 5) + rand(20)*1000; //сразу генерим
        //#20180912-02 Fix
        PChar.HunterCost.Qty = j; //i;
        PChar.HunterCost.TempHunterType = "";
        sld = CharacterFromID(pchar.chosenTreasureHero);
        LAi_type_actor_Reset(sld);
        LAi_ActorDialog(sld, pchar, "", 4.0, 0);
		chrDisableReloadToLocation = true;
		//DoQuestCheckDelay("OpenTheDoors", 5.0);
    }
}

ref SetFantomSkeletForts(string group, string locator, string enemygroup, string _type)
// _type = "GhostShipCrew"   _type = "ParamHunter"  _type = "none"
{
    string emodel;
    ref    Cr;

    emodel = GetRandSkelModel();

    Cr = LAi_CreateFantomCharacterEx(emodel, "man", group, locator);

    if (Cr.location.locator != "")
    {
		if (_type == "GhostShipCrew" || _type == "ParamHunter")
		{
			SetFantomParamHunter(Cr);
		}
		else
		{
		    SetFantomParam(Cr);
		}
		LAi_SetWarriorType(Cr);
	    LAi_group_MoveCharacter(Cr, enemygroup);
	    LAi_NoRebirthEnable(Cr); //не показывать убитых при входе в локацию
	    LAi_LoginInCaptureTown(Cr, true); // для записи игры
	    if (_type == "GhostShipCrew")
	    {
		    // возможно дает вылеты от многих трупов Cr.DontClearDead = true;
		    Cr.GhostShipCrew = true;
	    }
    }
    return Cr;
}

///////////////////////////////////////////   Квест летучего голландца /////////////////////////////////
// летучий голландец
void  GhostShipOnMap()
{
    ref  sld;
    int  i;
    ref  rRealShip;

    sld = characterFromID("GhostCapt");
    // пушки чинятся в SetBaseShipData DeleteAttribute(sld, "ship.cannons");

    SetBaseShipData(sld);
    rRealShip = GetRealShip(sti(sld.Ship.Type));
    rRealShip.ShipSails.SailsColor = argb(255, 60, 60, 60);  // 1.2.3 переделка цвета паруса от НПС

    DeleteAttribute(sld,"ship.sails");
    DeleteAttribute(sld,"ship.masts");
    DeleteAttribute(sld,"ship.blots");

	sld.Ship.Name = "Летучий голландец";

    Ship_SetTaskNone(SECONDARY_TASK, sti(sld.index));

    if (CheckAttribute(pchar , "GenQuest.GhostShip.LastBattle"))
    {
		rRealShip.EmblemedSails.normalTex =  "ships\parus_common_torn.tga";

		sld.Ship.Type = GenerateShipExt(SHIP_FLYINGDUTCHMAN, true, sld);
		SetBaseShipData(sld);

        DeleteAttribute(rRealShip, "ShipSails.SailsColor");  // белый парус

        sld.ship.Cannons.Type = CANNON_TYPE_CULVERINE_LBS36;

        Character_SetAbordageEnable(sld, true);
    }
    else
    {
        sld.ship.hp = 50000; // 13 процентов
    }
	sld.items.talisman3 = 1;
	EquipCharacterByItem(sld,"talisman3");
    SetCrewQuantityOverMax(sld, 666);
    sld.mapEnc.type = "war";
    sld.mapEnc.Name = "Летучий голландец";
	sld.mapEnc.worldMapShip = "Flying_Dutchman";
	SelAllPerksToNotPCHAR(sld);
	DeleteAttribute(sld,"perks.list.ShipEscape");

    sld.ship.Crew.Morale = 90;
    ChangeCrewExp(sld, "Sailors", 100);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers", 100);

    Fantom_SetBalls(sld, "pirate");
    Fantom_SetCharacterGoods(sld, GOOD_BALLS,  4900 + rand(300), 0);
	Fantom_SetCharacterGoods(sld, GOOD_BOMBS,  5900 + rand(300), 0);
	Fantom_SetCharacterGoods(sld, GOOD_POWDER, 12000 + rand(300), 0);

    LAi_SetCurHPMax(sld); // если он умер
    string sGroup = "Sea_GhostCapt";  // приставка "Sea_" + ИД важна
    Group_FindOrCreateGroup(sGroup);
	Group_AddCharacter(sGroup, "GhostCapt");
    Group_SetGroupCommander(sGroup, "GhostCapt");

    SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
    Group_SetTaskAttack(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);

	Group_SetAddress(sGroup,"KhaelRoa","quest_ships","Quest_ship_9");

	Pchar.quest.GhostShip_Start.win_condition.l1 = "location";
	Pchar.quest.GhostShip_Start.win_condition.l1.location = "KhaelRoa";
	Pchar.quest.GhostShip_Start.win_condition = "GhostShip_Start";

    Pchar.quest.GhostShip_Dead.win_condition.l1 = "NPC_Death";
	Pchar.quest.GhostShip_Dead.win_condition.l1.character = "GhostCapt";
	Pchar.quest.GhostShip_Dead.win_condition = "GhostShip_Dead";
}

void Survive_In_Sea_Go2Land()
{
    string  sTemp;
    int     iDay;
    ref 	ch;
	int 	n, i, idx;
    int 	storeArray[30];
    int 	howStore = 0;

    // трем всех офов и компаньонов, не квестовых
    iDay = GetPassengersQuantity(pchar);
    i = 0;
    n = 0;
 	while (i < iDay)
	{
		i++;
		idx = GetPassenger(pchar, n); // всегда первый в массиве со смещением, если не трем
		if (idx==-1) break;
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

	DeleteAttribute(pchar, "ship");
	pchar.ship.name = "";
	pchar.ship.type = SHIP_NOTUSED;
	pchar.money = 0;

	SetCharacterShipLocation(pchar, "");

	// выбор города близ бухты
    for (n = 0; n < MAX_COLONIES; n++)
	{
  		if (colonies[n].nation == "none") continue; // необитайки
  		if (sti(colonies[n].nation) == PIRATE) continue;
  		if (colonies[n].from_sea == "") continue; // необитайки
  		if (!CheckAttribute(&Colonies[n], "islandLable") || Colonies[n].islandLable == "Mein") continue; // только острова

        storeArray[howStore] = n;
   		howStore++;
    }

    makeref(ch,colonies[storeArray[rand(howStore-1)]]);
    setWDMPointXZ(ch.from_sea);
    pchar.location = ch.from_sea; // это порт, ниже ищем бухту

    // нулим предметы в каюте
    ref loc;
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
	Pchar.GenQuest.Hunter2Pause = true;
    iDay = 5+rand(17);
    bQuestCheckProcessFreeze = true;
    WaitDate("",0,0,iDay, rand(10), 1); // прошло время
    bQuestCheckProcessFreeze = false;

	// бухта контры
    pchar.location = SelectSmugglingLocation();

    pchar.Health.Damg = stf(pchar.chr_ai.hp_max)*40;
	// дает лог в + и - AddCharacterHealth(pchar, -30);
	Log_Info("О чудо! Я жив!");
	if (sti(PChar.GenQuest.GhostShip.KillMe) <= 1)
	{
		AddQuestRecord("GhostShipQuest", "Survive_1");
	}
	else
	{
	    AddQuestRecord("GhostShipQuest", "Survive_2");
	    // добавить предмет Т102
	    if (sti(PChar.GenQuest.GhostShip.KillMe) == 2)
		{
			Log_Info("Вы нашли очень странный предмет.");
			TakeNItems(Pchar, "term_arm", 1);
	    	pchar.QuestTemp.TakeShotgun = true;
	    }
	}
	sGlobalTemp = "afterFDsink";
	bDisableMapEnter           = false;   // мир, был бой с ЛГ

	SetLaunchFrameFormParam("Прошло " + iDay + " дней." + NewStr() +
	                        "Остров " + GetConvertStr(ch.islandLable, "LocLables.txt")+","+ NewStr() +
							"" + GetConvertStr(pchar.location, "LocLables.txt") + ".",
						                        "Reload_To_Location", 0.1, 7.0);
    SetLaunchFrameReloadLocationParam(pchar.location, "Smugglers", "Smuggler01", "");
	LaunchFrameForm();
	DeleteAttribute(pchar,"GhostCap.Fight");
}

void GhostShipInit()
{
	ref sld;
	//============> Капитан призрака
	if (MOD_SKILL_ENEMY_RATE == 10 && bHardAnimations) sld = GetCharacter(NPC_GenerateCharacter("GhostCapt", "PotCMobCap", "skeleton", "spy", 55, PIRATE, -1, true));
	else sld = GetCharacter(NPC_GenerateCharacter("GhostCapt", "PotCMobCap", "skeleton", "man_fast", 55, PIRATE, -1, true));
	sld.dialog.filename      = "Quest\GhostShip_dialog.c";
	sld.dialog.currentnode   = "GhostCapt";
	sld.name 	= "Дейви";
	sld.lastname = "Джонс";
	sld.reputation = 15;
	LAi_NoRebirthDisable(sld);
	LAi_RebirthOldName(sld);
	if (bHardBoss) sld.AlwaysReload = true;//перезарядка независимо от Дозарядки
	sld.RebirthPhantom     = true;
	sld.AlwaysEnemy        = true;
	sld.DontHitInStorm     = true; // не ломается в шторм
	sld.DontRansackCaptain = true; //квестовые не сдаются
	sld.SinkTenPercent     = false;  // не тонуть после 10 процентах корпуса
	sld.Abordage.Enable    = false; // запрет абордажа
	sld.SaveItemsForDead   = true; // сохранять на трупе вещи
	sld.cirassId           = Items_FindItemIdx("cirass5");  // предмета нет, но влияение есть
	sld.AlwaysSandbankManeuver = true;  // тупым запрет тонуть об берег
	sld.GenQuest.CrewSkelMode  = true; // на абордаже скелеты
	LAi_SetHP(sld, 666, 666);
	SetCharacterPerk(sld, "Energaiser"); // скрытый перк дает 1.5 к приросту энергии, дается ГГ и боссам уровней
    sld.SuperShooter  = true;
	DeleteAttribute(sld, "items");
	GiveItem2Character(sld, "topor2");
	EquipCharacterByItem(sld, "topor2");
	GiveItem2Character(sld, "pistol6");
	EquipCharacterByItem(sld, "pistol6");
	TakeNItems(sld, "bullet", 10);
	AddItems(sld, "GunPowder", 10);
	TakeNItems(sld,"potion2", 10);
	sld.money = 70000;

//	LAi_SetLoginTime(sld, 6.0, 21.99); // <---  а вот это вот нахрена было ? ugeen
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	sld.Ship.Type = CreateBaseShip(SHIP_FLYINGDUTCHMAN);
	sld.Ship.Name = "Летучий голландец";

	ref rRealShip = GetRealShip(sti(sld.Ship.Type));
	//sld.ship.sailscolor = argb(255,60,60,60);
	rRealShip.ship.upgrades.sails = 3;
	rRealShip.EmblemedSails.normalTex =  "ships\parus_common_torn.tga";
	rRealShip.ShipSails.SailsColor = argb(255,60,60,60);
	rRealShip.MaxCaliber = 48;
    rRealShip.Cannon     = CANNON_TYPE_CANNON_LBS48;
    rRealShip.MaxCrew    = 525;
    rRealShip.OptCrew    = 400;
    rRealShip.Capacity   = 5000;
    rRealShip.HP         = 400000;
    rRealShip.WindAgainstSpeed = 10.0;
    rRealShip.SpeedRate	 = 15.0;
	rRealShip.TurnRate   = 60.0;
	rRealShip.Price      = 500000;

	pchar.GenQuest.GhostShip.ShipType   = sti(sld.Ship.Type); // запомним, потом пригодится, когда парус нужно сменить на целый
}

// квест шотгана - терминатора Т-102 появление в комнате таверны
void QuestShotgunT102()
{
	ref sld;
	sld = GetCharacter(NPC_GenerateCharacter("T102", "Terminator", "Terminator_Sex", "Terminator", 55, PIRATE, 0, false));
	sld.dialog.filename      = "Quest\T102_dialog.c";
	FantomMakeCoolFighter(sld, 80, 80, 80, "katar", "", 80);

    sld.name  = "Terminator";
    sld.lastname = "";
	LAi_SetHP(sld, 1500.0, 1500.0);
	AddBonusEnergyToCharacter(sld, 200);
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "SwordplayProfessional");

	ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	LAi_SetActorType(sld);
    LAi_SetActorType(pchar);

	SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 4.0);
    LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
}

void Map_CreateFastWarriorTreasure()
{
	// немного веселой жизни
    ref  sld;
    int  i;

    string sCapId = "WarriorTreasure";
    string sGroup = "Sea_" + sCapId + "1";

	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
    for (i = 1; i <= 3; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "off_hol_2", "man", "man", sti(PChar.rank) + 5, PIRATE, 15, true));
		if(CheckAttribute(PChar,"Luke.SpawnMaks")) CreatePGG_War(sld, PIRATE, pchar);
		else SetShipHunter(sld);
        SetFantomParamHunter(sld); //крутые парни
        SetCaptanModelByEncType(sld, "war");
        sld.AlwaysEnemy = true;
        sld.DontRansackCaptain = true;
        sld.mapEnc.type = "war";
        sld.mapEnc.Name = "Джентльмены удачи";
		sld.hunter = "pirate";
        Group_AddCharacter(sGroup, sCapId + i);
    }

    Group_SetGroupCommander(sGroup, sCapId+ "1");
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);
    Map_CreateFastWarrior("", sCapId + "1", 8);
}
