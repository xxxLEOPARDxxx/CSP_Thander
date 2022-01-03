//новый файл, для усиления защиты

//Город погибших кораблей
void CreateLostShipsCity(aref loc)
{
	int i;
	if (loc.id == "LostShipsCity_town" && isDay())
	{
		ref sld;
		string sTemp, sLocator;
		int locNum, n, Index;
		int qtyTavern = 0;
		int qtyResidence = 0;
		int qtyChurch = 0;
		int qtyPrison = 0;
		int qtyStore = 0;
		for(i=0; i<MAX_CHARACTERS; i++)
		{
			makeref(sld, characters[i]);
			if (sld.location == "FleuronTavern") qtyTavern++;
			if (sld.location == "SanAugustineResidence") qtyResidence++;
			if (sld.location == "GloriaChurch") qtyChurch++;
			if (sld.location == "TartarusPrison") qtyPrison++;
			if (sld.location == "EsmeraldaStoreBig") qtyStore++;
		}
		//размещаем нпс
		for(i=0; i<MAX_CHARACTERS; i++)
		{
			makeref(sld, characters[i]);
			if (CheckAttribute(sld, "city") && sld.city == "LostShipsCity")
			{
				//////// если это адмирал /////////
				if (sld.cityTape == "mayor")
				{
					if (GetNpcQuestPastTimeParam(sld, "location") > sti(sld.location.hours))
					{
						DeleteAttribute(sld, "location.going"); //снимаем флаг
						//--> вечером организовываем толпу в таверне
						if (GetTime() > 19.0 && rand(1))
						{
							if (qtyTavern < LSC_MAX_TAVERN)
							{
								sld.location.going = "toTavern"; //флаг генерации в таверне
								qtyTavern++;
							}
							continue;
						}
						//<-- вечером организовываем толпу в таверне
						if (sld.location == "SanAugustineResidence") //если адмирал в резиденции
						{
							if (rand(1))	//вероятность выхода из резиденции
							{
								SaveCurrentNpcQuestDateParam(sld, "location");
								sld.location.hours = rand(5)+1;
								if (rand(1))
								{	//выходим на улицы
									//проверим занятость локатора
									if (!LAi_CheckLocatorFree("goto", sld.location.baseLocator))
									{	//выберем незанятый
										sTemp = sld.location.baseLocator;
										sTemp = strcut(sTemp, 4, 5);
										for (n=0; n<=9; n++)
										{
											sLocator = "goto" + sTemp + "_" + n;
											if (LAi_CheckLocatorFree("goto", sLocator))
											{
												LAi_SetLSCoutTypeNoGroup(sld);
												ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sLocator);
												break;
											}
										}
									}
									else
									{
										LAi_SetLSCoutTypeNoGroup(sld);
										ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sld.location.baseLocator);
									}
								}
								else
								{	//в таверну
									if (qtyTavern < LSC_MAX_TAVERN)
									{
										sld.location.going = "toTavern"; //флаг генерации в таверне
										qtyTavern++;
									}
								}
							}
						}
						else
						{	//рулим в резиденцию
							LAi_SetHuberTypeNoGroup(sld); //садим за стол
							ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "sit", "sit1");
						}
					}
				}
				//////// если это менты /////////
				if (sld.cityTape == "ment")
				{
					if (GetNpcQuestPastTimeParam(sld, "location") > sti(sld.location.hours))
					{
						DeleteAttribute(sld, "location.going"); //снимаем флаг
						//if (rand(1)) LAi_SetLoginTime(sld, 6.0, 21.99);
						//else LAi_RemoveLoginTime(sld);
						//--> вечером организовываем толпу в таверне
						if (GetTime() > 20.0 && rand(1))
						{
							if (qtyTavern < LSC_MAX_TAVERN)
							{
								sld.location.going = "toTavern"; //флаг генерации в таверне
								qtyTavern++;
							}
							continue;
						}
						//<-- вечером организовываем толпу в таверне
						if (sld.location == "LostShipsCity_town") //если мент на улице
						{
							if (rand(1))
							{
								SaveCurrentNpcQuestDateParam(sld, "location");
								sld.location.hours = rand(5)+1;
								switch (rand(2))
								{
								case 0: //в резиденцию к шефу
									if (qtyResidence < LSC_MAX_RESIDENCE)
									{
										qtyResidence++;
										LAi_SetWarriorTypeNoGroup(sld);
										ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "goto", "goto"+qtyResidence);
									}
									break;
								case 1: //в таверну
									if (qtyTavern < LSC_MAX_TAVERN)
									{
										sld.location.going = "toTavern"; //флаг генерации в таверне
										qtyTavern++;
									}
									break;
								case 2: //в тюрьму
									if (qtyPrison < LSC_MAX_PRISON)
									{
										qtyPrison++;
										LAi_SetWarriorTypeNoGroup(sld);
										ChangeCharacterAddressGroup(sld, "TartarusPrison", "goto", "goto"+qtyPrison);
									}
									break;
								}
							}
						}
						else
						{	//возвращемся на варшип
							//проверим занятость локатора
							if (!LAi_CheckLocatorFree("goto", sld.location.baseLocator))
							{	//выберем незанятый
								sTemp = sld.location.baseLocator;
								sTemp = strcut(sTemp, 4, 5);
								for (n=0; n<=9; n++)
								{
									sLocator = "goto" + sTemp + "_" + n;
									if (LAi_CheckLocatorFree("goto", sLocator))
									{
										LAi_SetLSCoutTypeNoGroup(sld);
										ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sLocator);
										break;
									}
								}
							}
							else
							{
								LAi_SetLSCoutTypeNoGroup(sld);
								ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sld.location.baseLocator);
							}
						}
					}
				}
				//////// если внешний горожанин /////////
				if (sld.cityTape == "citizen")
				{
					if (GetNpcQuestPastTimeParam(sld, "location") > sti(sld.location.hours))
					{
						DeleteAttribute(sld, "location.going"); //снимаем флаг
						LAi_SetLoginTime(sld, 6.0, 21.99);
						//--> вечером организовываем толпу в таверне
						if (GetTime() > 19.0 && sld.sex == "man" && rand(1))
						{
							if (qtyTavern < LSC_MAX_TAVERN)
							{
								sld.location.going = "toTavern"; //флаг генерации в таверне
								qtyTavern++;
							}
							continue;
						}
						//<-- вечером организовываем толпу в таверне
						if (sld.location == "LostShipsCity_town") //если горожанин на улице
						{
							if (rand(1))
							{
								SaveCurrentNpcQuestDateParam(sld, "location");
								sld.location.hours = rand(3)+1;
								switch (rand(2))
								{
								case 0: //в церковь
									if (qtyChurch < LSC_MAX_CHURCH)
									{
										sld.location.going = "toChurch"; //флаг генерации в церкви
										qtyChurch++;
									}
									break;
								case 1: //в таверну
									if (qtyTavern < LSC_MAX_TAVERN)
									{
										sld.location.going = "toTavern"; //флаг генерации в таверне
										qtyTavern++;
									}
									break;
								case 2: //в магазин
									if (qtyStore < LSC_MAX_STORE)
									{
										sld.location.going = "toStore"; //флаг генерации в магазине
										qtyStore++;
									}
									break;
								}
							}
						}
						else
						{	//возвращемся на свой корабль
							//проверим занятость локатора
							if (!LAi_CheckLocatorFree("goto", sld.location.baseLocator))
							{	//выберем незанятый
								sTemp = sld.location.baseLocator;
								sTemp = strcut(sTemp, 4, 5);
								for (n=0; n<=9; n++)
								{
									sLocator = "goto" + sTemp + "_" + n;
									if (LAi_CheckLocatorFree("goto", sLocator))
									{
										LAi_SetLSCoutTypeNoGroup(sld);
										ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sLocator);
										break;
									}
								}
							}
							else
							{
								LAi_SetLSCoutTypeNoGroup(sld);
								ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sld.location.baseLocator);
							}
						}
					}
				}
				//////// если домашний горожанин /////////
				if (sld.cityTape == "citizenHome")
				{
					if (GetNpcQuestPastTimeParam(sld, "location") > sti(sld.location.hours))
					{
						DeleteAttribute(sld, "location.going"); //снимаем флаг
						LAi_SetLoginTime(sld, 6.0, 21.99);
						//--> вечером организовываем толпу в таверне
						if (GetTime() > 19.0 && sld.sex == "man" && rand(1))
						{
							if (qtyTavern < LSC_MAX_TAVERN)
							{
								sld.location.going = "toTavern"; //флаг генерации в таверне
								qtyTavern++;
							}
							continue;
						}
						//<-- вечером организовываем толпу в таверне
						if (sld.location == sld.location.baseLocation) //если горожанин у себя дома
						{
							if (rand(1))
							{
								SaveCurrentNpcQuestDateParam(sld, "location");
								sld.location.hours = rand(6)+1;
								switch (rand(3))
								{
								case 0: //в церковь
									if (qtyChurch < LSC_MAX_CHURCH)
									{
										sld.location.going = "toChurch"; //флаг генерации в церкви
										qtyChurch++;
									}
									break;
								case 1: //в таверну
									if (qtyTavern < LSC_MAX_TAVERN)
									{
										sld.location.going = "toTavern"; //флаг генерации в таверне
										qtyTavern++;
									}
									break;
								case 2: //в магазин
									if (qtyStore < LSC_MAX_STORE)
									{
										sld.location.going = "toStore"; //флаг генерации в магазине
										qtyStore++;
									}
									break;
								case 3: //на улицы
									//проверим занятость локатора
									if (!LAi_CheckLocatorFree("goto", sld.location.baseLocator))
									{	//выберем незанятый
										sTemp = sld.location.baseLocator;
										sTemp = strcut(sTemp, 4, 5);
										for (n=0; n<=9; n++)
										{
											sLocator = "goto" + sTemp + "_" + n;
											if (LAi_CheckLocatorFree("goto", sLocator))
											{
												LAi_SetLSCoutTypeNoGroup(sld);
												ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sLocator);
												break;
											}
										}
									}
									else
									{
										LAi_SetLSCoutTypeNoGroup(sld);
										ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sld.location.baseLocator);
									}
									break;
								}
							}
						}
						else
						{	//возвращемся на свой корабль
							LAi_SetOwnerTypeNoGroup(sld);
							ChangeCharacterAddressGroup(sld, sld.location.baseLocation, "barmen", "stay");
						}
					}
				}
			}
		}
	}
	//------------------- таверна ------------------------
	if (loc.id == "FleuronTavern")
	{
		for(i=0; i<MAX_CHARACTERS; i++)
		{
			makeref(sld, characters[i]);
			if (CheckAttribute(sld, "location.going") && sld.location.going == "toTavern")
			{
				DeleteAttribute(sld, "location.going");
				LAi_RemoveLoginTime(sld);
				if (sld.sex == "man")
				{
					DeleteAttribute(sld, "nonTable");
					LAi_SetSitTypeNoGroup(sld);
					if (sld.id == "LSCMayor")
						ChangeCharacterAddressGroup(sld, loc.id, "quest", "head_sit");
					else
						PlaceCharacter(sld, "sit", "random_free");
				}
				else
				{
					LAi_SetCitizenTypeNoGroup(sld);
					PlaceCharacter(sld, "goto", "random_free");
				}
			}
		}
	}
	//------------------- церковь ------------------------
	if (loc.id == "GloriaChurch")
	{
		//сам падре
		if (!isDay())
		{
			Index = GetCharacterIndex("LSC_Priest");
			if (Index != -1)
			{
				sld = &characters[Index];
				LAi_SetSitTypeNoGroup(sld);
				PlaceCharacter(sld, "quest", "priest");
			}
		}
		else
		{
			for(i=0; i<MAX_CHARACTERS; i++)
			{
				makeref(sld, characters[i]);
				//падре днем
				if (sld.id == "LSC_Priest")
				{
					LAi_SetPriestTypeNoGroup(sld);
					ChangeCharacterAddressGroup(sld, sld.location, "barmen",  "stay");
				}
				//граждане
				if (CheckAttribute(sld, "location.going") && sld.location.going == "toChurch")
				{
					DeleteAttribute(sld, "location.going");
					if (sld.sex == "woman")
					{
						LAi_SetCitizenTypeNoGroup(sld);
						PlaceCharacter(sld, "goto", "random_free");
					}
					else
					{
						sld.nonTable = true;
						LAi_SetSitTypeNoGroup(sld);
						PlaceCharacter(sld, "sit", "random_free");
					}
				}
			}
		}
	}
	//------------------- магазин ------------------------
	if (loc.id == "EsmeraldaStoreBig")
	{
		for(i=0; i<MAX_CHARACTERS; i++)
		{
			makeref(sld, characters[i]);
			if (CheckAttribute(sld, "location.going") && sld.location.going == "toStore")
			{
				DeleteAttribute(sld, "location.going");
                LAi_SetStayTypeNoGroup(sld);
				PlaceCharacter(sld, "goto", "random_free");
			}
		}
	}
	//------------------- тюрьма -------------------
	if (loc.id == "TartarusPrison")
	{
		Index = GetCharacterIndex("LSC_PrisonerHead");
		if (Index != -1)
		{
			sld = &characters[Index];
			if (GetNpcQuestPastDayParam(sld, "location") > sti(sld.location.days))
			{
				SaveCurrentNpcQuestDateParam(sld, "location");
				if (rand(1))
				{
					LAi_SetHuberTypeNoGroup(sld);
					ChangeCharacterAddressGroup(sld, loc.id, "sit", "sit1");
				}
				else
				{
					LAi_SetWarriorTypeNoGroup(sld);
					PlaceCharacter(sld, "goto", "random_free");
				}
			}
		}
		Index = GetCharacterIndex("LSC_Prisoner1");
		if (Index != -1)
		{
			sld = &characters[Index];
			if (GetNpcQuestPastTimeParam(sld, "location") > sti(sld.location.hours))
			{
				SaveCurrentNpcQuestDateParam(sld, "location");
				if (rand(1))
				{
					LAi_SetSitTypeNoGroup(sld);
					ChangeCharacterAddressGroup(sld, loc.id, "sit", "sit2");
				}
				else
				{
					LAi_SetWarriorTypeNoGroup(sld);
					PlaceCharacter(sld, "goto", "random_free");
				}
			}
		}
	}
}

void CreatPlantation(aref loc)
{
	if (loc.id == "Plantation_Sp1")
	{
		bool ok = false;
		if (CheckAttribute(Pchar,"questTemp.CapBloodLine") && Pchar.questTemp.CapBloodLine == false) ok = true;
		if (startHeroType != 1 || ok)
		{
			if (!CheckAttribute(pchar,"AlreadyPlantRuler"))
			{
				ref ch = GetCharacter(NPC_GenerateCharacter("PlantRuler", "off_eng_"+(rand(1)+1), "man", "man", 30, ENGLAND, 1, true));
				ch.greeting = "soldier_common";
				ch.name 	= "Джон";
				ch.lastname = "Синс";
				ch.City = "Bridgetown";
				ch.Dialog.Filename = "PlantRuler.c";
				ch.dialog.currentnode   = "Meet";
				LAi_SetCitizenType(ch);
				LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
				LAi_SetImmortal(ch, true);
				DeleteAttribute(ch,"lifeDay");
				pchar.AlreadyPlantRuler = true;
				ch.SlavesLimit = 250+rand(750);
				ChangeCharacterAddressGroup(ch, pchar.location, "goto",  "goto1");
			}
		}
		return;
	}
    if (loc.id != "Bridgetown_Plantation") return;
    if(LAi_IsCapturedLocation) // fix нефиг грузить, когда город трупов или боевка
	{
		return;
	}
	if (GetNpcQuestPastDayWOInit(loc, "Plantation_date") < 2) return;

	int iColony = -1;
	int iNation = -1;

    iColony = FindColony("Bridgetown");

	if(iColony == -1)
	{
		return;
	}

	iNation = GetCityNation("Bridgetown");

	if(iNation == -1)
	{
		return;
	}
	SaveCurrentNpcQuestDateParam(loc, "Plantation_date");
	int iCitizensQuantity, iModel;
	ref chr;
	aref st;
	int iChar, i, iSex;
	string slai_group, locatorName, sType;
    slai_group = GetNationNameByType(iNation)  + "_citizens";
	int num, iMassive, iRank;
	string sAnime;
	string model[23];
// просто работники
    model[0] = "prizon_1";
    model[1] = "prizon_2";
    model[2] = "prizon_3";
    model[3] = "prizon_4";
    model[4] = "prizon_5";
    model[5] = "prizon_6";
    model[6] = "prizon_7";
	model[7] = "prizon_8";
    model[8] = "pirate_1";
    model[9] = "prison_5";
    model[10] = "pirate_1";
    model[11] = "pirate_11";
    model[12] = "pirate_12";
    model[13] = "pirate_13";
    model[14] = "pirate_14";
    model[15] = "pirate_15";
    model[16] = "pirate_16";
    model[17] = "pirate_21";
    model[18] = "pirate_25";
    model[19] = "PKM_rab_1";
    model[20] = "PKM_rab_2";
    model[21] = "PKM_rab_3";
    model[22] = "PKM_rab_4";
    i = 0;
    num = rand(3) + 7; //количество
    while(i < num)
    {
        iMassive = rand(22);
        if (model[iMassive] != "")
        {
            sAnime = "man"
            /* if(model[iMassive] == "pirate_1" || model[iMassive] == "pirate_11" || model[iMassive] == "pirate_12" || model[iMassive] == "pirate_13" || model[iMassive] == "pirate_14" || model[iMassive] == "pirate_15" || model[iMassive] == "pirate_16" || model[iMassive] == "pirate_21" || model[iMassive] == "pirate_25") sAnime = "man"; */

            chr = GetCharacter(NPC_GenerateCharacter("Slave_"+i, model[iMassive], "man", sAnime, 7, ENGLAND, 2, false));
            //chr.dialog.Filename = "Pearl_dialog.c";
            chr.dialog.filename = "Quest\CapBloodLine\questNPC.c";
            //chr.dialog.currentnode = "PearlMan";
            chr.greeting = "Gr_slave";
            chr.CityType = "citizen";
            chr.city = Colonies[iColony].id;
            LAi_SetLoginTime(chr, 6.0, 22.99);

            PlaceCharacter(chr, "goto", "random_free");
            LAi_SetCitizenType(chr);
            LAi_group_MoveCharacter(chr, slai_group);
            i++;
            model[iMassive] = "";
        }
    }
	if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.soldiers"))
	{
 		if(iNation == PIRATE)
		{
            sType = "mushketer_" + (rand(4)+1);
		}
		else
		{
            sType = NationShortName(iNation) + "_mush_" + (rand(2)+1);
		}
		chr = GetCharacter(NPC_GenerateCharacter("GenChar_", sType, "man", "mushketer", sti(pchar.rank), iNation, 2, false));
		chr.id = "GenChar_" + chr.index;
		chr.reputation = (1 + rand(44) + rand(44));// репа всем горожанам
		chr.City = Colonies[iColony].id;
        chr.CityType = "soldier";
		chr.greeting = "soldier_common";
		chr.MusketerDistance = 0;
		LAi_SetLoginTime(chr, 6.0, 23.0); //а ночью будет беготня от патруля :)

		LAi_SetPatrolType(chr);
        if (sti(Colonies[iColony].HeroOwn) == true)
		{
			LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
			chr.greeting = "pirat_guard";
		}
		else
		{
			LAi_group_MoveCharacter(chr, slai_group);
		}
		chr.dialog.filename = "Common_Soldier.c";
		chr.dialog.currentnode = "first time";
		ChangeCharacterAddressGroup(chr, pchar.location, "soldiers", "soldier1");
	}
	// солдаты <--
	// патруль -->
	if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.patrol"))
	{
		makearef(st, loc.locators.patrol);
		iCitizensQuantity = GetAttributesNum(st);
		if(iCitizensQuantity > 10)
		{
			iCitizensQuantity = 10;
		}
		for (i=0; i<iCitizensQuantity-3; i++)
		{
            if(iNation != PIRATE && LAi_IsCapturedLocation == 0)
			{
                sType = "soldier";
				iChar = NPC_GeneratePhantomCharacter("soldier", iNation, MAN, 2);
			}
			else
			{
                sType = "pirate";
				iChar = NPC_GeneratePhantomCharacter("pirate", iNation, MAN, 2);
			}
			chr = &characters[iChar];
			SetNPCModelUniq(chr, sType, MAN);
			chr.City = Colonies[iColony].id;
            chr.CityType = "soldier";
            SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // бравые орлы
			chr.RebirthPhantom = true;
			LAi_CharacterReincarnation(chr, true, true);
			LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); //задаем шаг на увеличение ранга фантомам на реинкарнацию
			LAi_SetLoginTime(chr, 0.0, 24.0);
			LAi_SetPatrolType(chr);

            if (sti(Colonies[iColony].HeroOwn) == true)
			{
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				chr.greeting = "pirat_guard";
			}
			else
			{
				LAi_group_MoveCharacter(chr, slai_group);
				chr.greeting = "soldier_common";
			}
			PlaceCharacter(chr, "patrol", "random_free");
			if(Pchar.questTemp.CapBloodLine == true)  // Линейка Блада
			{
                chr.dialog.filename = "Quest\CapBloodLine\questNPC.c";
            }
            else
            {
                chr.dialog.filename = "Common_Soldier.c";
            }
			chr.dialog.currentnode = "first time";
		}
	}
	// патруль <--
	// грузчики -->
	if (loc.type == "town" && CheckAttribute(loc, "carrier") && IsLoginTime())
	{
		int iTemp;
		int iQtyCarrier = rand(2) + 2;
		string locReload[5];
		locReload[0] = "houseSp1";
		locReload[1] = "houseS1";
		locReload[2] = "houseF1";
		locReload[3] = "houseF2";
		locReload[4] = "houseS2";
		string CarrierName[10];
		CarrierName[0] = "GenresBag1";
		CarrierName[1] = "GenresBag2";
		CarrierName[2] = "GenresBarrel1";
		CarrierName[3] = "GenresBarrel2";
		CarrierName[4] = "GenresBarrelTop1";
		CarrierName[5] = "GenresBarrelTop2";
		CarrierName[6] = "GenresBottle1";
		CarrierName[7] = "GenresBottle2";
		CarrierName[8] = "GenresChest1";
		CarrierName[9] = "GenresChest2";
		for (i=iQtyCarrier; i>0; i--)
		{
			//выберем уникальную для этой локации модельку
			iSex = 1;
			while (iSex == 1)
			{
				iTemp = rand(9);
				if (CarrierName[iTemp] != "") iSex = 0;
			}
			chr = GetCharacter(NPC_GenerateCharacter("Carrier", CarrierName[iTemp], "man", "genres", 35, iNation, 2, false));
			chr.id = chr.id + "_" + chr.index;
			aref aLocator;
			makearef(aLocator, loc.locators.reload);
			CarrierName[iTemp] = ""; //имя модельки уберем из списка
			LAi_SetImmortal(chr, true);
			iSex = 1;
			while (iSex == 1)
			{
				iTemp = rand(4);
				if (CheckAttribute(aLocator, locReload[iTemp]) && locReload[iTemp] != "")
				{
					chr.firstLoc = locReload[iTemp];
					chr.firstLoc.timer = rand(7) + 3;
					locReload[iTemp] = "";
					iSex = 0;
				}
			}
			ChangeCharacterAddressGroup(chr, loc.id, "reload", "gate");
			LAi_SetCarrierType(chr);
			LAi_SetLoginTime(chr, 6.0, 23.0);//homo ночью пусть спят
			LAi_group_MoveCharacter(chr, slai_group);
		}
	}
	// грузчики <--
}

void CreatUnderwater(aref loc)
{
	if (loc.type == "underwater")
	{
		if (CheckAttribute(loc, "type.LSC"))
		{
			LocatorReloadEnterDisable("LostShipsCity_town", "reload73", true);
			pchar.questTemp.LSC.immersions.pay = false; //оплаченное погружение использовано
			pchar.questTemp.LSC.immersions = sti(pchar.questTemp.LSC.immersions);
			SetShowTimer(400.0); //таймер
			for (int i=1; i<=22; i++)
			{
				if (GetCharacterIndex("Crab_"+i) == -1)
				{
					sld = GetCharacter(NPC_GenerateCharacter("Crab_"+i, "crabBig", "crab", "crabBig", 40+(MOD_SKILL_ENEMY_RATE), PIRATE, -1, false));
					GiveItem2Character(sld, "unarmed");
					EquipCharacterbyItem(sld, "unarmed");
					LAi_SetWarriorType(sld);
					LAi_warrior_SetStay(sld, true);
					LAi_warrior_DialogEnable(sld, false);
					LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
					PlaceCharacter(sld, "goto", "random_free");
				}
			}
		}
		else
		{
			SetShowTimer(80.0); //таймер
		}
	}
}

void CreatTenochtitlan(aref loc)
{
	if (loc.id == "Tenochtitlan")
	{
		int i;
		//проверяем наличие тотемов у ГГ, чтобы купленным дать shown
		if (locations[reload_cur_location_index].id == "Tenotchitlan_Jungle_06")
		{	//срабатывает только, если заходим из джунглей
			ref itm;
			string sTemp;
			for (i=1; i<=15; i++)
			{
				if (i == 11) continue;
				sTemp = "Totem_" + i;
				if (CheckCharacterItem(pchar, sTemp))
				{
					itm = ItemsFromID(sTemp);
					//если тотем еще не использован, то помечаем на укладку в button
					if (!CheckAttribute(itm, "shown.used"))
					{
						itm.shown = 0;
					}
				}
			}
		}
		else
		{
			//близнецов расставим иначе
			int iTemp;
			for (i=1; i<=2; i++)
			{
				iTemp = GetCharacterIndex("AztecCitizen_"+i);
				if (iTemp != -1)
				{
					PlaceCharacter(&characters[iTemp], "goto", "random_free");
				}
			}
		}
	}
}

void CreatTenochtitlanInside(aref loc)
{
	if (loc.type == "teno_inside")
	{
		ref chr;
		int iMassive, warriorQty, warriorRank, i, n;
		string model[5];
		string sLocator;
		//----------------- генерим войнов в малых храмах богов -----------------
		if (CheckAttribute(loc, "smallGodTemple"))
		{
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = true;
			//определим кол-во войнов в храме
			//Boyer mod: 3 warriors is very difficult, they will always outrank, have poison and very deadly weapon...and is enough.  At 10 = Impossible, there will be 4
			//#20170318-33
			warriorQty = makeint(MOD_SKILL_ENEMY_RATE / 2.5);
			if (warriorQty < 3) warriorQty = 3;
			//определим ранг войнов. обработаем от сложности, но не менее 15 уровня
			warriorRank = GetCoffDiff(sti(pchar.rank), 1000);
			if (warriorRank < 11) warriorRank = 11;
			//инкремент на кол-во посещений
			loc.smallGodTemple = sti(loc.smallGodTemple) + 1;
			warriorRank = warriorRank + sti(loc.smallGodTemple) * 4;
			//генерим ацтеков с неповторяемыми модельками
		    model[0] = "AztecWarrior1";
			model[1] = "AztecWarrior2";
			model[2] = "AztecWarrior3";
			model[3] = "AztecWarrior4";
			model[4] = "AztecWarrior5";
			//Boyer change
			//i = 0;
			//while(i < warriorQty)
			for(i=0; i < warriorQty; i++)
			{
				iMassive = rand(4);
				//if (model[iMassive] != "")
				//{
					chr = GetCharacter(NPC_GenerateCharacter("AztecWarrior"+loc.index+"_"+i, model[iMassive], "skeleton", "man", warriorRank, PIRATE, 0, true));
					SetFantomParamFromRank(chr, warriorRank, true);
					while (FindCharacterItemByGroup(chr, BLADE_ITEM_TYPE) != "")
					{
						TakeItemFromCharacter(chr, FindCharacterItemByGroup(chr, BLADE_ITEM_TYPE));
					}
					while (FindCharacterItemByGroup(chr, GUN_ITEM_TYPE) != "")
					{
						TakeItemFromCharacter(chr, FindCharacterItemByGroup(chr, GUN_ITEM_TYPE));
					}
					GiveItem2Character(chr, "toporAZ");
					EquipCharacterbyItem(chr, "toporAZ");
					SetCharacterPerk(chr, "Energaiser");
					if (sti(loc.smallGodTemple) > 3 && MOD_SKILL_ENEMY_RATE > 1)
					{
						SetCharacterPerk(chr, "SwordplayProfessional");
						SetCharacterPerk(chr, "AdvancedDefense");
						SetCharacterPerk(chr, "CriticalHit");
						SetCharacterPerk(chr, "Sliding");
						TakeNItems(chr,"potion1", rand(MOD_SKILL_ENEMY_RATE)+1);
					}
					PlaceCharacter(chr, "goto", "random_free");
					LAi_SetWarriorType(chr);
					LAi_group_MoveCharacter(chr, "EnemyFight");
				//	i++;
				//	model[iMassive] = "";
				//}
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
		}
		//----------------- генерим войнов в большом храме -----------------
		if (CheckAttribute(loc, "greatTemple") && locations[reload_cur_location_index].id == "Tenochtitlan")
		{
			//определим кол-во войнов в храме
			//warriorQty = 4;
			//if (MOD_SKILL_ENEMY_RATE > 6) warriorQty = 5;
			//if (MOD_SKILL_ENEMY_RATE <= 1) warriorQty = 3;
			//Boyer mod: 3 warriors is very difficult, they will always outrank, have poison and very deadly weapon...and is enough.  At 10 = Impossible, there will be 4
			//#20170318-33
			warriorQty = makeint(MOD_SKILL_ENEMY_RATE / 2.5);
			if (warriorQty < 3) warriorQty = 3;
			warriorRank = GetCoffDiff(sti(pchar.rank), 1000);
			if (warriorRank < 20) warriorRank = 20;
			//генерим ацтеков с неповторяемыми модельками
			for (n=1; n<=7; n++)
			{
				model[0] = "AztecWarrior1";
				model[1] = "AztecWarrior2";
				model[2] = "AztecWarrior3";
				model[3] = "AztecWarrior4";
				model[4] = "AztecWarrior5";
				//Boyer change
                //i = 0;
                //while(i < warriorQty)
                for(i=0; i < warriorQty; i++)
                {
					iMassive = rand(4);
					//if (model[iMassive] != "")
					//{
						chr = GetCharacter(NPC_GenerateCharacter("AztecWarrior"+loc.index+"_"+n+""+i, model[iMassive], "skeleton", "man", warriorRank, PIRATE, 0, true));
						SetFantomParamFromRank(chr, 15, true);
						while (FindCharacterItemByGroup(chr, BLADE_ITEM_TYPE) != "")
						{
							TakeItemFromCharacter(chr, FindCharacterItemByGroup(chr, BLADE_ITEM_TYPE));
						}
						while (FindCharacterItemByGroup(chr, GUN_ITEM_TYPE) != "")
						{
							TakeItemFromCharacter(chr, FindCharacterItemByGroup(chr, GUN_ITEM_TYPE));
						}
						GiveItem2Character(chr, "toporAZ");
						EquipCharacterbyItem(chr, "toporAZ");
						SetCharacterPerk(chr, "Energaiser");
						if (MOD_SKILL_ENEMY_RATE > 5)
						{
							SetCharacterPerk(chr, "SwordplayProfessional");
							SetCharacterPerk(chr, "AdvancedDefense");
							SetCharacterPerk(chr, "CriticalHit");
							SetCharacterPerk(chr, "Sliding");
							TakeNItems(chr,"potion1", rand(MOD_SKILL_ENEMY_RATE)+1);
						}
						sLocator = "monster"+n;
						ChangeCharacterAddressGroup(chr, loc.id, "monsters", sLocator+(i+1));
						LAi_SetWarriorType(chr);
						LAi_warrior_SetStay(chr, true);
						LAi_warrior_DialogEnable(chr, false);
						LAi_group_MoveCharacter(chr, LAI_GROUP_MONSTERS);
					//	i++;
					//	model[iMassive] = "";
					//}
				}
			}
			//#20191011-01
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		}
	}
}

void CreatDesMoines(aref loc)
{
	ref chr;
	bool bImmortal;
	int i, iMassive;
	string sSex, sNode, sModel;
	string model[10];
	if (pchar.questTemp.MC != "Incquisitio")
	{
		if (loc.id == "DesMoines_town")
		{
			if (GetHour() > 6.0 && GetHour() < 21.99)
			{
				model[0] = "citiz_11";
				model[1] = "citiz_3";
				model[2] = "citiz_5";
				model[3] = "citiz_9";
				model[4] = "citiz_11";
				model[5] = "shipowner_1";
				model[6] = "shipowner_12";
				model[7] = "shipowner_2";
				model[8] = "trader_4";
				model[9] = "barmen_6";
				sSex = "man";
				sNode = "DMCitiz";
				sModel = "Hobart";
				bImmortal = false;
			}
			else
			{
				if (pchar.questTemp.MC == "over")
				{
					model[0] = "citiz_11";
					model[1] = "citiz_3";
					model[2] = "citiz_5";
					model[3] = "citiz_9";
					model[4] = "citiz_11";
					model[5] = "shipowner_1";
					model[6] = "shipowner_12";
					model[7] = "shipowner_2";
					model[8] = "trader_4";
					model[9] = "barmen_6";
					sSex = "man";
					sNode = "DMCitiz";
					sModel = "Hobart";
					bImmortal = false;
				}
				else
				{
					model[0] = "skel1";
					model[1] = "skel2";
					model[2] = "skel3";
					model[3] = "skel4";
					model[4] = "skel1";
					model[5] = "skel2";
					model[6] = "skel3";
					model[7] = "skel4";
					model[8] = "skel1";
					model[9] = "skel2";
					sSex = "skeleton"
					sNode = "DMSkel";
					sModel = "skeletcap";
					bImmortal = true;
				}
			}
			//Boyer change
			//i = 0;
			//while(i < 8)
			for(i=0; i < 8; i++)
			{
				iMassive = rand(9);
				//if (model[iMassive] != "")
				//{
					chr = GetCharacter(NPC_GenerateCharacter("MCCitiz_"+i, model[iMassive], sSex, "man", 15, SPAIN, 0, true));
					chr.dialog.filename = "Quest\MagicCity.c";
					chr.dialog.currentnode = sNode;
					chr.greeting = "cit_common";
					chr.city = "DesMoines";
					LAi_RemoveLoginTime(chr);
					LAi_SetImmortal(chr, bImmortal);
					PlaceCharacter(chr, "goto", "random_free");
					LAi_SetCitizenType(chr);
					LAi_group_MoveCharacter(chr, "SPAIN_CITIZENS");
				//	i++;
				//	model[iMassive] = "";
				//}
			}
		}
		if (loc.id == "DesMoines_Townhall")
		{
			if (GetHour() > 6.0 && GetHour() < 21.99 )
			{
				sSex = "man";
				sNode = "DMCitiz";
				sModel = "Hobart";
				bImmortal = false;
			}
			else
			{
				if (pchar.questTemp.MC == "over")
				{
					sSex = "man";
					sNode = "DMCitiz";
					sModel = "Hobart";
					bImmortal = false;
				}
				else
				{
					sSex = "skeleton"
					sNode = "DMSkel";
					sModel = "skeletcap";
					bImmortal = true;
				}
			}
			//глава поселения
			chr = GetCharacter(NPC_GenerateCharacter("DesMoinesHead", sModel, sSex, "man", 25, SPAIN, 0, true));
			chr.name = "Фернандо";
			chr.lastname = "Торрес";
			chr.dialog.filename = "Quest\MagicCity.c";
			chr.dialog.currentnode = sNode + "Head";
			chr.greeting = "pirat_common";
			chr.city = "DesMoines";
			chr.watchBoxes = true;
			chr.watchBoxes.exitDisable = true;
			LAi_RemoveLoginTime(chr);
			LAi_SetImmortal(chr, bImmortal);
			ChangeCharacterAddressGroup(chr, "DesMoines_Townhall", "goto", "goto1");
			LAi_SetWarriorType(chr);
			LAi_group_MoveCharacter(chr, "SPAIN_CITIZENS");
		}
	}
}
