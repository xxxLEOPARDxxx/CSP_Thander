//Создать фантома основываясь на характуристиках данного персонажа в самом дальнем углу
void LAi_GenerateFantomFromMe(aref chr)
{
	//Проверяем возможность генерации фантома в данной локации
	if(!TestRef(loadedLocation)) return;
	if(!IsEntity(loadedLocation)) return;
	if(LAi_LocationIsFantomsGen(loadedLocation) == false) return;
	//Проверяем возможность перерождения персонажа
	if(LAi_CharacterIsReincarnation(chr) == false) return;
	//Проверяем какую модельку использовать для перерождения
	bool isGen = LAi_CharacterReincarnationMode(chr);
	if(CheckAttribute(chr, "model") == false) isGen = true;
	if(CheckAttribute(chr, "model.animation") == false) isGen = true;
	if(chr.model == "") isGen = true;
	if(chr.model.animation == "") isGen = true;
	string model, ani;
	if(isGen)
	{
		int nat = GetLocationNation(loadedLocation)
		if(nat < 0) nat = PIRATE;
		if(nat >= MAX_NATIONS) nat = PIRATE;
		if(CheckAttribute(&Nations[nat], "fantomModel") == false)
		{
			Trace("Nation (Nations[" + nat + "]) by name " + Nations[nat].name + " not include fantoms");
			return;
		}
		aref fantoms;
		makearef(fantoms, Nations[nat].fantomModel);
		int num = GetAttributesNum(fantoms);
		if(num <= 0)
		{
			Trace("Nation (Nations[" + nat + "]) by name " + Nations[nat].name + " not include have fantoms");
			return;
		}
		num = rand(num - 1);
		string m = GetAttributeName(GetAttributeN(fantoms, num));
		model = fantoms.(m);
		ani = "man";
		m = m + ".ani";
		if(CheckAttribute(fantoms, m) != false)
		{
			ani = fantoms.(m);
		}
	}else{
		model = chr.model;
		ani = chr.model.animation;
	}
	//Сохраняем параметры персонажа
	object tmp;
	CopyAttributes(&tmp, chr);
	//Создаём фантома
	if(ani == "mushketer")
	{
		ref sld = GetCharacter(NPC_GenerateCharacter("GenChar_", model, "man", "mushketer", chr.rank, sti(chr.nation), sti(chr.lifeDay), false));
		sld.id = "GenChar_" + sld.index;
		sld.reputation = chr.reputation;
		sld.City = chr.City;
        sld.CityType = chr.CityType;
		sld.RebirthPhantom = true;
		sld.dialog.filename = "Common_Soldier.c";
		sld.dialog.currentnode = "first time";
		LAi_CharacterReincarnation(sld, true, true);
		LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); //задаем шаг на увеличение ранга фантомам на реинкарнацию
		if (CheckAttribute(chr, "chr_ai.reincarnation.step"))
		{
			SetFantomParamFromRank(sld, sti(chr.rank) + sti(chr.chr_ai.reincarnation.step), true); // бравые орлы
		}
		LAi_SetLoginTime(sld, 6.0, 23.0); //а ночью будет беготня от патруля :)
		sld.dialog.filename = chr.dialog.filename;
		sld.dialog.currentnode = chr.dialog.currentnode;
		SetRandomNameToCharacter(sld);
		LAi_SetPatrolType(sld);
		LAi_group_MoveCharacter(sld, chr.chr_ai.group);
		PlaceCharacter(sld, "patrol", "random_free");
	}
	else
	{
		ref fnt = LAi_CreateFantomCharacterEx(model, ani, LAi_CharacterReincarnationGroup(chr), "");
		string curidx = fnt.index;
		//Устанавливаем параметры предыдущего персонажа
		CopyAttributes(fnt, &tmp);
		// boal оружие дать! 19.01.2004 -->
		// фантомы точные клоны SetFantomParam(fnt);
		//--> eddy. шаг на увеличение ранга фантома.
		if (CheckAttribute(chr, "chr_ai.reincarnation.step"))
		{
			SetFantomParamFromRank(fnt, sti(chr.rank) + sti(chr.chr_ai.reincarnation.step), true); // бравые орлы
			characters[sti(fnt.baseIndex)].rank = fnt.rank; //в структуру прародителя ранг с наворотом
		}
		else //не даем падать рангу от SetFantomParam
		{
			LAi_NPC_Equip(fnt, sti(fnt.rank), true, true);
			LAi_SetCurHPMax(fnt);
		}
		// boal 19.01.2004 <--
		if(CheckAttribute(fnt, "chr_ai.group"))
		{
			LAi_group_MoveCharacter(fnt, fnt.chr_ai.group);
		}else{
			LAi_group_MoveCharacter(fnt, "");
		}
		//Сохраняем модельку и анимацию
		fnt.model = model;
		fnt.model.animation = ani;
		//Инициализируем тип
		if(!CheckAttribute(fnt, "chr_ai.type")) fnt.chr_ai.type = "";
		string chrtype = fnt.chr_ai.type;
		SetRandomNameToCharacter(fnt);
		fnt.id = tmp.id;
		fnt.index = curidx;
		LAi_tmpl_stay_InitTemplate(fnt);
		fnt.chr_ai.type = "";
		if(chrtype != "")
		{
			chrtype = "LAi_type_" + chrtype + "_Init";
			call chrtype(fnt);
		}
		SetNewModelToChar(fnt);   // fix
	}
}

// LEO
// Mett: Высчитываем количество бандитов
int LAi_CalculateRaidersQuantity(int iBase)
{
    int iOfficer = GetOfficersQuantity(pchar);
    float fMod = makefloat(MOD_SKILL_ENEMY_RATE  * 0.5); // 1.0 уровень сложности = (+ 1 бандит), т.е. на невозможке будет 5.0 = +5 бандитов *** (База - 4) + (назначенные абордажники) + (сложность * 0.5) ***
    int iQty = iBase + iOfficer/*  + makeint(fMod) */; // LEO: Заебали нытики хуевы, убрал скейлинг сложности 14.12.2021
    return iQty;
}

bool LAi_CreateEncounters(ref location)
{
	aref grp, st, at;
	ref chr, rCharacter;
	string encGroup, str, locator, sAreal, sCity;
	int num, i, iChar, iNation, iRank, n, iTemp, iMassive, iRnd, iRand;
	string model[25];
	if (!bLandEncountersGen) //если прерывание на локацию, энкаунтеров не генерим
	{
		bLandEncountersGen = true;
		return false;
	}
	//Можем ли генерить
	if(CheckAttribute(location, "DisableEncounters")) return false;
	if(!CheckAttribute(location, "locators.encdetector") || !CheckNPCQuestDate(location, "Enc_date") || bDisableLandEncounters) return false;
	if (CheckAttribute(location, "fastreload") && !HasSubStr(location.id, "exitTown")) return false; //отсекаем локации exitTown у пиратских городов
    //boal 02.09.06 пауза случаек на один раз -->
	if (CheckAttribute(pchar, "GenQuest.Enc2Pause"))
	{
	    DeleteAttribute(pchar, "GenQuest.Enc2Pause");
	    return false;
	}
	// boal <--
	//--> если бухта и в ней контра, то не ставим никого
	if (location.type == "seashore")
	{
		makearef(st, location.models.always);
		num = GetAttributesNum(st);
		for(i = 0; i < num; i++)
		{
			at = GetAttributeN(st, i);
			str = GetAttributeName(at);
			if(st.(str) == "smg")
			{
				return false;
			}
		}
	}
	//<-- если бухта и в ней контра, то не ставим никого
	SetNPCQuestDate(location, "Enc_date"); //запись на дату не сегодня
	//Установить нацию патруля
	sAreal = GiveArealByLocation(location);
	if (sAreal == "none") return false;

	// На необитаемых этого всего нету, но там нету и этих квестов
	if(!CheckAttribute(location, "onUninhabitedIsland"))
	{
	sCity = GetCityNameByIsland(sAreal);
	if (sCity == "none") return false;
	iNation = GetCityNation(sCity);
	if (iNation == -1 || iNation == PIRATE) return false;

	if (findsubstr(location.Id, "LaVega" , 0) != -1) return false;
	if (findsubstr(location.Id, "PuertoPrincipe" , 0) != -1) return false;
	if (findsubstr(location.Id, "LeFransua" , 0) != -1) return false;
	}

	// Warship 10.08.09 Если прерывание на локацию - не генерим энкаунтеров, иначе погло накладываться, судя по всму
	// bLandEncountersGen устанавливался вручную и не гарантиварол избежание пересечений квест-энкаункеры
	if(!isLocationFreeForQuests(location.Id)) return false;

	//группа, куда будем помещать фантомов
	encGroup = LAi_FindRandomLocator("encdetector");
	str = "locators." + encGroup;
	makearef(grp, location.(str));
	if(CheckAttribute(location, "onUninhabitedIsland") || CheckAttribute(location, "deadlocked"))
	{
		iRand = rand(1) + 6;
	}
	else
	{
		iRand = rand(5);
	}
	switch (iRand)
	{
		//------------------ Банда рейдеров типа дежурит на грабежах ----------------------
		case 0:
			if(!bbettatestmode){if (rand(10) > 6) return false;}
			if(CheckAttribute(location, "onUninhabitedIsland") || location.type == "seashore" || location.type == "mayak") return false; // На необитаемых нельзя
			num = LAi_CalculateRaidersQuantity(GetAttributesNum(grp)); // LEO
			if (num <= 0 ) num = 1; //если локаторов меньше четырех
			str = "Gang"+ location.index + "_";
			//--> генерим ранг
			if (sti(pchar.rank) > 6 || MOD_SKILL_ENEMY_RATE == 10)
			{
				if (sti(pchar.rank) > 20) iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*2.5);
				else iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*1.5);
			}
			else iRank = sti(pchar.rank);
			//<-- генерим ранг

			// Mett: -->
			for(int m = 1; m < 26; m++)
			{
				model[m-1] = "pirate_" + m;
			}
			// Mett: <--

			LAi_grp_alarmactive = false;
			LAi_group_ClearAllTargets();
			for(i=0;i < num; i++)
			{
					iMassive = rand(24);
					chr = GetCharacter(NPC_GenerateCharacter(str + i, model[iMassive], "man", "man", iRank, iNation, 1, true));
					SetFantomParamFromRank(chr, iRank, true);
					//Получим локатор для логина
					locator = GetAttributeName(GetAttributeN(grp, 1)); // LEO
					ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
					chr.dialog.filename = "Enc_Raiders_dialog.c";
					chr.greeting = "Enc_Raiders";
					chr.EncQty = num;
					LAi_SetStayType(chr);
					LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, true, "LandEnc_RaidersBeforeDialog");
					LAi_group_MoveCharacter(chr, "RaidersGroup_" + location.index);
					if (i == 0)
					{
						sAreal = "Raiders_" + location.index;
						pchar.GenQuest.(sAreal).name = GetFullName(chr); //имя бандита, будет главарем
						pchar.GenQuest.(sAreal).nation = iNation; //нация для слухов
					}
			}
			str = "EncRaiders_" + location.index;
			pchar.quest.(str).win_condition.l1        = "locator";
			pchar.quest.(str).win_condition.l1.location = location.id;
			pchar.quest.(str).win_condition.l1.locator_group = "encdetector";
			pchar.quest.(str).win_condition.l1.locator = encGroup;
			pchar.quest.(str).win_condition = "LandEnc_RaidersBegin";
			pchar.quest.(str).EncQty = num; //кол-во бандитов
			pchar.quest.(str).LocIdx = location.index;
			str = "TimeRaiders_" + location.index;
			pchar.quest.(str).win_condition.l1            = "Timer";
			pchar.quest.(str).win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.(str).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.(str).win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.(str).win_condition               = "LandEnc_RaidersOver";
			pchar.quest.(str).LocIdx = location.index;
		break;
		//------------------ Спасаем девку в пампасах ----------------------
		case 1:
			if(rand(12) > 6) return false;
			if(CheckAttribute(location, "onUninhabitedIsland") || location.type == "seashore" || location.type == "mayak") return false; // На необитаемых  островах, маяках и бухтах нельзя
			num = GetAttributesNum(grp); //кол-во локаторов

			if (bBettaTestMode || drand(95)==0)
			{
				if (!CheckAttribute(pchar,"OldSpawn"))
				{
					model[0] = "capitan_3";
					model[1] = "officer_13";
					model[2] = "officer_32";
					model[3] = "PGG_Black_0";
					model[4] = "pirate_12";
					model[5] = "pirate_25";
					model[6] = "ozg_horn";
					model[7] = "pirate_15";
					model[8] = "pirate_11";
					model[9] = "PKM_rab_1";
					model[10] = "PKM_rab_2";
					for(i=0; i < num; i++)
					{
						iMassive = rand(10);
						//Получим локатор для логина
						locator = GetAttributeName(GetAttributeN(grp, i));
						if (i == 0)
						{
							iChar = NPC_GenerateCharacter("OldMan", "PGG_Barrows_0", "man", "man", 1, iNation, -1, false);
							chr = &characters[iChar];
							chr.dialog.filename = "Old.c";
							chr.dialog.currentnode = "First";
							chr.name = "Дед";
							chr.lastname = "Старый";
							chr.greeting = "DedEvent";
							chr.num = num;
							ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
							LAi_SetActorType(chr);
							LAi_group_MoveCharacter(chr, "player");
							LAi_ActorDialog(chr, pchar, "", -1, 0);
							chr.city = sCity;
							continue;
						}
						chr = GetCharacter(NPC_GenerateCharacter("GangRapersMan_" + i, model[iMassive], "man", "man", iRank, PIRATE, 1, true));
						SetFantomParamFromRank(chr, iRank, true);
						chr.dialog.filename = "Old.c";
						chr.dialog.currentnode = "Second";
						chr.greeting = "Enc_Raiders";
						ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
						LAi_SetActorType(chr);
						LAi_group_MoveCharacter(chr, "player");
						LAi_ActorFollow(chr, &characters[iChar], "", -1);
					}
					pchar.OldSpawn = true;
					break;
				}
			}

			if (num < 2) return false;
			if(CheckAttribute(pchar, "GenQuest.EncGirl") && pchar.GenQuest.EncGirl != "close") return false;
			if (!CheckAttribute(location, "locators.reload.reloadW_back"))
			{//--------------- обычная девка в джунглях ---------------
				if (sti(pchar.rank) > 1)
				{
					if (sti(pchar.rank) > 20) iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*2.5);
					else iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*1.5);
				}
				else iRank = sti(pchar.rank);

				LAi_group_Delete("EnemyFight");
				LAi_group_Delete("LandEncGroup");
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
				LAi_SetFightMode(pchar, false);
				LAi_LockFightMode(pchar, true);
				chrDisableReloadToLocation = true;

				model[0] = "pirate_1";
				model[1] = "pirate_2";
				model[2] = "pirate_3";
				model[3] = "pirate_4";
				model[4] = "pirate_5";
				model[5] = "pirate_6";
				model[6] = "pirate_7";
				model[7] = "pirate_8";
				model[8] = "pirate_9";
				model[9] = "pirate_10";
				model[10] = "pirate_11";
				model[11] = "pirate_12";
				model[12] = "pirate_13";
				model[13] = "pirate_14";
				model[14] = "pirate_15";
				model[15] = "pirate_16";
				model[16] = "pirate_17";
				model[17] = "pirate_18";
				model[18] = "pirate_19";
				model[19] = "pirate_20";
				model[20] = "pirate_21";
				model[21] = "pirate_22";
				model[22] = "pirate_23";
				model[23] = "pirate_24";
				model[24] = "pirate_25";

				for(i=0; i < num; i++)
				{
					iMassive = rand(24);
						//Получим локатор для логина
						locator = GetAttributeName(GetAttributeN(grp, i));
						if (i == 0)
						{
							switch(rand(2)) // генерим один из вариантов начала квеста
							{
								case 0:
									Log_TestInfo("Девица в джунглях : сгенерился вариант 1");
									iChar =	NPC_GenerateCharacter("CangGirl", "girl_"+(rand(7)+1), "woman", "towngirl", 5, iNation, -1, false);
									chr = &characters[iChar];
									chr.dialog.filename = "Enc_RapersGirl_dialog.c";
									chr.dialog.currentnode = "Begin_1";
									pchar.GenQuest.EncGirl = "Begin_1";
								break;
								case 1:
									Log_TestInfo("Девица в джунглях : сгенерился вариант 2");
									iChar =	NPC_GenerateCharacter("CangGirl", "whore_"+(rand(3)+1), "woman", "towngirl3", 5, iNation, -1, false);
									chr = &characters[iChar];
									chr.dialog.filename = "Enc_RapersGirl_dialog.c";
									chr.dialog.currentnode = "Begin_2";
									pchar.GenQuest.EncGirl = "Begin_2";
									pchar.GenQuest.EncGirl.Horse = true;
								break;
								case 2:
									Log_TestInfo("Девица в джунглях : сгенерился вариант 3");
									iChar =	NPC_GenerateCharacter("CangGirl", "girl_"+(rand(7)+1), "woman", "towngirl", 5, iNation, -1, false);
									chr = &characters[iChar];
									chr.dialog.filename = "Enc_RapersGirl_dialog.c";
									chr.dialog.currentnode = "Begin_3";
									pchar.GenQuest.EncGirl = "Begin_3";
								break;
							}
							chr.name = GenerateRandomName_Generator(iNation, "woman");
							chr.lastname = "";
							chr.greeting = "Enc_RapersGirl_1";
							ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
							LAi_SetActorType(chr);
							LAi_group_MoveCharacter(chr, "LandEncGroup");
							LAi_ActorDialog(chr, pchar, "", -1, 0);
							LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, false, "LandEnc_RapersBeforeDialog");
							str = location.index;
							pchar.GenQuest.EncGirl.city = sCity; //  город девицы
							pchar.GenQuest.EncGirl.nation = iNation; //нация для слухов
							pchar.GenQuest.EncGirl.name = GetFullName(chr); //имя девицы
							pchar.GenQuest.EncGirl.LocIdx = location.index;
							chr.city = sCity;
							//i++;
							continue;
						}
						chr = GetCharacter(NPC_GenerateCharacter("GangMan_" + i, model[iMassive], "man", "man", iRank, PIRATE, 1, true));
						SetFantomParamFromRank(chr, iRank, true);
						chr.dialog.filename = "Enc_Rapers_dialog.c";
						chr.dialog.currentnode = "First time";
						chr.greeting = "Enc_Raiders";
						ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
						LAi_SetActorType(chr);
						LAi_group_MoveCharacter(chr, "EnemyFight");
						LAi_ActorFollow(chr, &characters[iChar], "", -1);
						LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, false, "LandEnc_RapersBeforeDialog");
				}
				iRnd = 1;
				if(sti(pchar.rank) > 1) iRnd = 2;
				pchar.GenQuest.EncGirl.variant = rand(iRnd);
				pchar.GenQuest.EncGirl.item = GenQuest_GenerateArtefact();
				pchar.GenQuest.EncGirl.sum  =  500 * (sti(pchar.rank) + 10) + rand(5000);
				sGlobalTemp = "";//состояние квеста на выходе из локации, нулим
				//--> сюрприз для любителей просто свалить из локации
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
				pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
			}
			else
			{//--------------- замануха в колодец -------------------
				LAi_group_Delete("LandEncGroup");
    			aref arRld, arDis;
				makearef(arRld, Locations[sti(location.index)].reload);
    			int	Qty = GetAttributesNum(arRld);
				str = "none";
				for (int a=0; a<Qty; a++)
    			{
    				arDis = GetAttributeN(arRld, a);
    				if (arDis.name == "reloadW_back")
    				{
						str = arDis.go; //ID смежной локации, куда ведет колодец
    				}
    			}
				if (str == "none") return false; //на всякий случай
				//--> снимаем возможный конфликт с бергларами
				if (sAreal == "SentMartin" || sAreal == "SantaCatalina")
				{
					iTemp = GetCharacterIndex("BerglarSantaCatalina");
					if (iTemp != -1 && characters[iTemp].location == str) return false;
					iTemp = GetCharacterIndex("BerglarMarigo");
					if (iTemp != -1 && characters[iTemp].location == str) return false;
				}
				//<-- снимаем возможный конфликт с бергларами
				locator = GetAttributeName(GetAttributeN(grp, 1));
				chr =	GetCharacter(NPC_GenerateCharacter("FriendGirl", "girl_"+(rand(7)+1), "woman", "towngirl", 5, iNation, 0, false));
				chr.dialog.filename = "Enc_FriendGirl_dialog.c";
				chr.dialog.currentnode = "First time";
				chr.greeting = "Enc_RapersGirl_1";
				ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
				LAi_SetActorType(chr);
				LAi_group_MoveCharacter(chr, "LandEncGroup");
				LAi_ActorDialog(chr, pchar, "", -1, 0);
				pchar.GenQuest.EncGirl.locationId = str; //ID локации
				pchar.GenQuest.EncGirl.nation = iNation; //нация для слухов
				pchar.GenQuest.EncGirl.name = GetFullName(chr); //имя девки
				pchar.quest.Enc_FriendGirl_after.win_condition.l1 = "NPC_Death";
				pchar.quest.Enc_FriendGirl_after.win_condition.l1.character = "FriendGirl";
				pchar.quest.Enc_FriendGirl_after.win_condition = "Enc_FriendGirl_after";
			}
		break;
        //------------------ Праздношатающиеся перцы ----------------------
		case 2: // доработка маленького и скучного энкаунтера.
			LAi_group_Delete("LandEncGroup");
			if (rand(10) > 7) return false;
			if(CheckAttribute(location, "onUninhabitedIsland")) return false; // На необитаемых нельзя
			locator = GetAttributeName(GetAttributeN(grp, 0));
			//Начинаем перебирать локаторы и логинить фантомов
			if (rand(5) > 3 && location.id.label == "ExitTown")
			{
				chr = GetCharacter(NPC_GenerateCharacter("WalkerGirl", "girl_"+(rand(7)+1), "woman", "towngirl", 5, PIRATE, 0, false));
				chr.greeting = "Gr_Woman_Citizen";
				LAi_SetCitizenType(chr);
				ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);

				if(rand(3) == 1) // Девушка может появится с мужем, или стражем
				{
					if(rand(1) == 0)
					{
			    		rCharacter = GetCharacter(NPC_GenerateCharacter("WalkerGirl_husband_1", "citiz_"+(rand(11)+1), "man", "man", sti(pchar.rank), PIRATE, 0, true));
    					SetFantomParamFromRank(rCharacter, sti(pchar.rank), true);
	    				rCharacter.greeting = "cit_common";
			    		LAi_SetActorType(rCharacter);
						LAi_ActorFollow(rCharacter, characterFromID("WalkerGirl"), "", -1);
			    		LAi_SetCheckMinHP(rCharacter, LAi_GetCharacterHP(rCharacter)-1, false, "LandEnc_WalkerGirlHusbandHit");
						LAi_group_MoveCharacter(rCharacter, "LandEncGroup");
					   	ChangeCharacterAddressGroup(rCharacter, location.id, encGroup, locator);
					}
					else
					{
    					rCharacter = GetCharacter(NPC_GenerateCharacter("WalkerGirl_sold_1", "sold_"+NationShortName(iNation)+"_"+(rand(7)+1), "man", "man", sti(pchar.rank), PIRATE, 0, true));
    				    SetFantomParamFromRank(rCharacter, sti(pchar.rank), true);
    				    rCharacter.greeting = "soldier_arest";
	    				LAi_SetActorType(rCharacter);
    					LAi_ActorFollow(rCharacter, characterFromID("WalkerGirl"), "", -1);
						LAi_SetCheckMinHP(rCharacter, LAi_GetCharacterHP(rCharacter)-1, false, "LandEnc_WalkerGirlGuardHit");
   	 			       	LAi_group_MoveCharacter(rCharacter, "LandEncGroup");
    					ChangeCharacterAddressGroup(rCharacter, location.id, encGroup, locator);
					}
				}
			}
			else
			{
				chr = GetCharacter(NPC_GenerateCharacter("Walker", "citiz_"+(rand(11)+1), "man", "man", sti(pchar.rank), PIRATE, 0, true));
				SetFantomParamFromRank(chr, sti(pchar.rank), true);
				chr.greeting = "cit_common";
				LAi_SetCitizenType(chr);
				LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, false, "LandEnc_WalkerHit");
				ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);

				if(rand(3) == 1) // Перец может появится с дружками или охраной
				{
					if(rand(1) == 0)
					{
						for(i = 1; i <= (rand(1)+1); i++)
				        {
				    		rCharacter = GetCharacter(NPC_GenerateCharacter("Walker_"+i, "citiz_"+(rand(11)+1), "man", "man", sti(pchar.rank), PIRATE, 0, true));
    					    SetFantomParamFromRank(rCharacter, sti(pchar.rank), true);
	    				    rCharacter.greeting = "cit_common";
		    				LAi_SetActorType(rCharacter);
							LAi_ActorFollow(rCharacter, characterFromID("Walker"), "", -1);
				    		LAi_SetCheckMinHP(rCharacter, LAi_GetCharacterHP(rCharacter)-1, false, "LandEnc_WalkerHit");
							LAi_group_MoveCharacter(rCharacter, "LandEncGroup");
					    	ChangeCharacterAddressGroup(rCharacter, location.id, encGroup, locator);
						}
					}
					else
					{
						for(i = 1; i <= (rand(1)+1); i++)
			    	    {
    						rCharacter = GetCharacter(NPC_GenerateCharacter("Walker_sold_"+i, "sold_"+NationShortName(iNation)+"_"+(rand(7)+1), "man", "man", sti(pchar.rank), PIRATE, 0, true));
	    				    SetFantomParamFromRank(rCharacter, sti(pchar.rank), true);
    					    rCharacter.greeting = "soldier_arest";
    						LAi_SetActorType(rCharacter);
							LAi_ActorFollow(rCharacter, characterFromID("Walker"), "", -1);
    						LAi_SetCheckMinHP(rCharacter, LAi_GetCharacterHP(rCharacter)-1, false, "LandEnc_WalkerHit");
    		    	    	LAi_group_MoveCharacter(rCharacter, "LandEncGroup");
    						ChangeCharacterAddressGroup(rCharacter, location.id, encGroup, locator);
					    }
					}
				}
			}
			DoQuestCheckDelay("Followers_activate", 3.0);
			chr.dialog.filename = "Enc_Walker.c";
			chr.dialog.currentnode = "First time";
			LAi_group_MoveCharacter(chr, "LandEncGroup");
		break;
		//------------------ Военный патруль ----------------------
		case 3:
			if (rand(10) > 3) return false;
			if(CheckAttribute(location, "onUninhabitedIsland")) return false; // На необитаемых нельзя
			//--> генерим ранг. военному патрулю палец в рот не клади и на начальных уровнях.
			num = makeint(5+rand(15)); //кол-во человек в патруле // LEO
			if (num <= 0) num = 1;
			if (sti(pchar.rank) > 14) iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*2.5);
			else iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*1.5);
			//<-- генерим ранг
			//Начинаем перебирать локаторы и логинить фантомов
			str = "Patrol"+ location.index + "_";
			string sGroup = "PatrolGroup_" + location.index; //имя группы
			LAi_group_Register("PatrolGroup_" + location.index);
			for(i = 0; i < num; i++)
			{
				if (i == 0)
				{
					chr = GetCharacter(NPC_GenerateCharacter(str + i, "off_"+NationShortName(iNation)+"_"+(rand(1)+1), "man", "man", iRank+2, iNation, 1, true));
					SetFantomParamFromRank(chr, iRank+2, true);
				}
				else
				{
					// if (i == 2 || prand(2) == 1)
					if (i > 3 && i < 8)
					{
						chr = GetCharacter(NPC_GenerateCharacter(str + i, NationShortName(iNation)+"_mush_"+(rand(2)+1), "man", "mushketer", iRank, iNation, 1, false));
						SetFantomParamFromRank(chr, iRank, true);
					}
					else
					{
						chr = GetCharacter(NPC_GenerateCharacter(str + i, "sold_"+NationShortName(iNation)+"_"+(rand(7)+1), "man", "man", iRank, iNation, 1, true));
						SetFantomParamFromRank(chr, iRank, true);
					}
				}
				chr.City = sCity;
				chr.CityType = "soldier";
				chr.greeting = "soldier_arest";
				chr.dialog.filename = "Enc_Patrol.c";
				chr.EncQty = num;
				LAi_SetStayType(chr);
				LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, false, "LandEnc_PatrolBeforeDialog");
				LAi_group_MoveCharacter(chr, sGroup);
				//Получим локатор для логина
				locator = GetAttributeName(GetAttributeN(grp, 1)); // LEO
				ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
			}
			LAi_group_SetLookRadius(sGroup, 100);
			LAi_group_SetHearRadius(sGroup, 100);

			str = "EncPatrol_" + location.index;
			pchar.quest.(str).win_condition.l1        = "locator";
			pchar.quest.(str).win_condition.l1.location = location.id;
			pchar.quest.(str).win_condition.l1.locator_group = "encdetector";
			pchar.quest.(str).win_condition.l1.locator = encGroup;
			pchar.quest.(str).win_condition = "LandEnc_PatrolBegin";
			pchar.quest.(str).EncQty = num; //кол-во патрульных
			pchar.quest.(str).LocIdx = location.index;
			str = "TimePatrol_" + location.index;
			pchar.quest.(str).win_condition.l1            = "Timer";
			pchar.quest.(str).win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.(str).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.(str).win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.(str).win_condition               = "LandEnc_PatrolOver";
			pchar.quest.(str).LocIdx = location.index;
			str = location.index;
			pchar.GenQuest.(str).nation = iNation; //нация патруля для слухов
		break;

		// --------------------------------- Беглые каторжники -------------------------------------
		case 4:
		if(CheckAttribute(pchar, "catorga"))
		{
			DeleteAttribute(pchar, "catorga");
			return false;
		}
			if(rand(15) > 3 || CheckAttribute(pchar, "GenQuest.Convict") || location.type == "seashore" || location.type == "mayak" ) return false; // LEO
			if(CheckAttribute(location, "onUninhabitedIsland")) return false; // На необитаемых нельзя
			if (sAreal == "Panama") return false;
			num = LAi_CalculateRaidersQuantity(GetAttributesNum(grp)); //кол-во человек в группе // LEO
			if(num <= 1) return false;
			if (num <= 2) num = 2;
			iRank = 2 + rand(3); //ранг каторжан
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
			pchar.GenQuest.Convict.ConvictQty = num;
			pchar.GenQuest.Convict.city = sCity;

			chrDisableReloadToLocation = true;

			while(i < num)
			{
				iMassive = rand(22);
				string sAnime;
				if(model[iMassive] != "")
				{
					sAnime = "man"
					chr = GetCharacter(NPC_GenerateCharacter("Convict_" + i, model[iMassive], "man", sAnime, iRank, PIRATE, -1, true));
					SetFantomParamFromRank(chr, iRank, true);
					// locator = GetAttributeName(GetAttributeN(grp, i));
					locator = GetAttributeName(GetAttributeN(grp, 1)); // LEO
					ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
					chr.dialog.filename = "GenQuests_Dialog.c";
					chr.dialog.currentnode = "First time";
					chr.greeting = "Gr_Slave";
					chr.city = sCity;
					LAi_SetImmortal(chr, true); // До поры нельзя убить
					LAi_SetActorTypeNoGroup(chr);

					if(i == 0)
					{
						LAi_ActorDialog(chr, pchar, "", -1, 0.0);
					}
					else
					{
						LAi_ActorFollow(chr, pchar, "", -1);
					}

					LAi_Group_MoveCharacter(chr, "ConvictGroup");
					LAi_Group_SetRelation("ConvictGroup", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);

					i++;
					model[iMassive] = "";
				}
			}

			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			pchar.GenQuest.Convict.Item = GenQuest_GenerateArtefact();
			pchar.GenQuest.Convict.city = sCity;

			iRnd = rand(9);
			if(iRnd <= 5) pchar.GenQuest.Convict.variant = 1;
			if(iRnd > 5 && iRnd < 8) pchar.GenQuest.Convict.variant = 2;
			if(iRnd >= 8) pchar.GenQuest.Convict.variant = 3;
			pchar.GenQuest.Convict.var = rand(2);
			Log_TestInfo("Каторжане: сгенерился квест");
			pchar.catorga = "1";
		break

					// Dolphin (Корсары: История Пирата)
		//------------------ Индейцы в джунглях (С небольшими апгрейдами от Korsar Maxim, Zik' и LEO) ----------------------
		case 5:
			if(isDay() || location.type == "seashore" || location.type == "mayak") return false;
			num = LAi_CalculateRaidersQuantity(GetAttributesNum(grp));
			if (num <= 0 ) num = 2; //если локаторов меньше четырех
			str = "Indian"+ location.index + "_";
			iRank = sti(pchar.rank);


			int iScl = 10+2*sti(pchar.rank);//казуалам зеленый свет на начало игры
			if (sti(pchar.rank) > 3) iRank = sti(pchar.rank);
			else
			{
				iRank = 1;
				num = 2;
			}

			i = 0;
			while(i < num)
			{
				if(i == 0 && rand(6) == 1) chr = GetCharacter(NPC_GenerateCharacter(str + i, "Canib_boss", "man", "man", iRank+12, PIRATE, 1, true)); // с шансом 1 на 7 встреч, первый индиан может быть главой каннибалов
				else chr = GetCharacter(NPC_GenerateCharacter(str + i, "Canib_"+(rand(5)+1), "man", "man", iRank+6, PIRATE, 1, true));
				SetFantomParamFromRank(chr, iRank, true);
				//Получим локатор для логина
				locator = GetAttributeName(GetAttributeN(grp, 1));

				string _Blade = "blade5";

				DeleteAttribute(chr, "equip");
				DeleteAttribute(chr, "items");
				DeleteAttribute(chr, "perks.list");

				if(chr.model == "Canib_boss") // Глава каннибалов круче своих по экипировке
				{
					chr.HeroModel = "Canib_Boss,Canib_Boss_1,Canib_Boss_2,Canib_Boss_3,Canib_Boss_4,Canib_Boss_5";
					chr.name = "касик";
					chr.lastname = "";

					if(rand(3) == 1)
					{
						_Blade = "topor_01";
					}
					else
					{
						_Blade = GiveRandomBladeByType("good");
					}

					int iHP = (150+MOD_SKILL_ENEMY_RATE*30+sti(pchar.rank)*5)*0.75;

					LAi_SetHP(chr, iHP, iHP);

					chr.DontClearDead = true;
					TakeNItems(chr, "jewelry11", (rand(34)+1));
			        TakeNItems(chr, "jewelry12", (rand(49)+1));

					iRand = rand(5);
					if(iRand == 0) TakeNItems(chr, "jewelry1", (rand(24)+1));
					if(iRand == 1) TakeNItems(chr, "jewelry2", (rand(24)+1));
					if(iRand == 2) TakeNItems(chr, "jewelry3", (rand(24)+1));
					if(iRand == 3) TakeNItems(chr, "jewelry4", (rand(24)+1));
					if(iRand == 4) TakeNItems(chr, "jewelry5", (rand(24)+1));
					if(iRand == 5)
					{
						if (rand(1) == 0) TakeNItems(chr, "StrangeMushrooms", 1);
						else TakeNItems(chr, "StrangePotion", 1);
						chr.SaveItemsForDead  = true;
					}

					iRand = rand(25);
					if(iRand == 5) TakeNItems(chr, "indian18", (rand(24)+1));
					if(iRand == 10) TakeNItems(chr, "indian19", (rand(24)+1));
					if(iRand == 15) TakeNItems(chr, "indian20", (rand(24)+1));
					if(iRand == 20) TakeNItems(chr, "indian21", (rand(24)+1));
					if(iRand == 25) TakeNItems(chr, "indian22", (rand(24)+1));

					TakeNItems(chr, "Food1", (rand(14)+1));
					TakeNItems(chr, "potion5", (rand(9)+1));
					TakeNItems(chr, "potion1", 7);
					TakeNItems(chr, "potion2", 7);
					FantomMakeCoolFighter(chr, iScl*0.80, iScl*2.55, iScl*0.35, _Blade, "", 300);
					DeleteAttribute(chr, "perks.list");
					AddBonusEnergyToCharacter(chr, 200);
					SetCharacterPerk(chr, "BasicDefense");
                    SetCharacterPerk(chr, "Tireless");
                    SetCharacterPerk(chr, "HardHitter");
                    SetCharacterPerk(chr, "CriticalHit");
                    SetCharacterPerk(chr, "SwordplayProfessional");
                    SetCharacterPerk(chr, "Sliding");
				}
				else
				{
					chr.name = "Калинаго";
					chr.lastname = "";
					_Blade = GiveRandomBladeByType("indian");
					FantomMakeCoolFighter(chr, iScl*0.55, iScl*1.90, iScl*0.25, _Blade, "", 150);
					AddBonusEnergyToCharacter(chr, 30);
					DeleteAttribute(chr, "perks.list");
					SetCharacterPerk(chr, "BasicDefense");
					SetCharacterPerk(chr, "AdvancedDefense");
                    SetCharacterPerk(chr, "Tireless");
                    SetCharacterPerk(chr, "CriticalHit");
					SetCharacterPerk(chr, "HardHitter");
					if(rand(19 - (sti(pchar.rank))/5) == 0)
					{
						if (rand(1) == 0) TakeNItems(chr, "StrangeMushrooms", 1);
						else TakeNItems(chr, "StrangePotion", 1);
						chr.SaveItemsForDead  = true;
					}

				}
				DeleteAttribute(chr, "items.spyglass3");

				ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
				LAi_SetWarriorTypeNoGroup(chr);

				LAi_group_MoveCharacter(chr, "Jungle_indians");
				i++;
			}

			LAi_group_SetRelation("Jungle_indians", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("Jungle_indians", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("Jungle_indians", "IndianInJungleClearGroup");
            PlaySound("People Fight\Cannibals_"+rand(1)+".wav");
		break;
		// Warship 05.08.09 Генер "Пираты на необитайке"
		// Pirates on a uninhabited island
		case 6:
			// Если reload_cur_island_index > -1 значит, ГГ пришел с моря
			if(rand(4) == 1 && CheckAttribute(location, "onUninhabitedIsland") && !CheckAttribute(location, "deadlocked") && !CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited") && !CheckAttribute(pchar, "GenQuest.ShipWreck") && reload_cur_island_index > -1)
			{
				model[0] = "pirate_1";
				model[1] = "pirate_2";
				model[2] = "pirate_3";
				model[3] = "pirate_4";
				model[4] = "pirate_5";
				model[5] = "pirate_6";
				model[6] = "pirate_7";
				model[7] = "pirate_8";
				model[8] = "pirate_9";
				model[9] = "pirate_10";
				model[10] = "pirate_11";
				model[11] = "pirate_12";
				model[12] = "pirate_13";
				model[13] = "pirate_14";
				model[14] = "pirate_15";
				model[15] = "pirate_16";
				model[16] = "pirate_17";
				model[17] = "pirate_18";
				model[18] = "pirate_19";
				model[19] = "pirate_20";
				model[20] = "pirate_21";
				model[21] = "pirate_22";
				model[22] = "pirate_23";
				model[23] = "pirate_24";
				model[24] = "pirate_25";

				i = 0;
				iRank = sti(PChar.rank) + MOD_SKILL_ENEMY_RATE;

				num = rand(10) + makeint(MOD_SKILL_ENEMY_RATE / 3) + dRand(5); // Кол-во пиратов
				PChar.GenQuest.PiratesOnUninhabited.PiratesQty = num;

				if(num <= 0) return false;

				while(i < num)
				{
					iMassive = rand(24);

					if(model[iMassive] != "")
					{
						chr = GetCharacter(NPC_GenerateCharacter("PirateOnUninhabited_" + i, model[iMassive], "man", "man", iRank, PIRATE, -1, true));
						SetFantomParamFromRank(chr, iRank, true);
						locator = GetAttributeName(GetAttributeN(grp, 1));
						ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
						//ChangeCharacterAddressGroup(chr, location.id, "goto", "goto" + (i + 1));
						chr.dialog.filename = "GenQuests_Dialog.c";
						chr.dialog.currentnode = "First time";
						chr.greeting = "Gr_MiddPirate"; // Enc_Raiders
						LAi_SetImmortal(chr, true); // До поры нельзя убить
						LAi_SetActorTypeNoGroup(chr);

						if(i == 0)
						{
							LAi_ActorDialog(chr, PChar, "", -1, 0.0);
						}
						else
						{
							LAi_ActorFollow(chr, PChar, "", -1);
						}

						LAi_Group_MoveCharacter(chr, "PiratesOnUninhabitedGroup");
						LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);

						i++;
						model[iMassive] = "";
					}
				}

				PChar.quest.PiratesOnUninhabited_LocExit.win_condition.l1 = "ExitFromLocation";
				PChar.quest.PiratesOnUninhabited_LocExit.win_condition.l1.location = PChar.location;
				PChar.quest.PiratesOnUninhabited_LocExit.function = "PiratesOnUninhabited_LocationExit";

				Log_TestInfo("Пираты на необитайке: сгенерился квест");
			}
		break;

		// --------------------------------- Потерпевшие кораблекрушение -------------------------------------
		case 7:
			if(num <= 0) return false;
			if(rand(4) == 1 && !CheckAttribute(pchar, "GenQuest.PiratesOnUninhabited") && !CheckAttribute(pchar, "GenQuest.ShipWreck") && pchar.location == pchar.location.from_sea)
			{
				model[0] = "pirate_1";
				model[1] = "pirate_2";
				model[2] = "pirate_3";
				model[3] = "pirate_4";
				model[4] = "pirate_5";
				model[5] = "pirate_6";
				model[6] = "pirate_7";
				model[7] = "pirate_8";
				model[8] = "pirate_9";
				model[9] = "pirate_10";
				model[10] = "pirate_11";
				model[11] = "pirate_12";
				model[12] = "pirate_13";
				model[13] = "pirate_14";
				model[14] = "pirate_15";
				model[15] = "pirate_16";
				model[16] = "pirate_17";
				model[17] = "pirate_18";
				model[18] = "pirate_19";
				model[19] = "pirate_20";
				model[20] = "pirate_21";
				model[21] = "pirate_22";
				model[22] = "pirate_23";
				model[23] = "pirate_24";
				model[24] = "pirate_25";

				i = 0;
				iRank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE;

				num = 5 + dRand(10); // Кол-во кораблекрушенцев
				pchar.GenQuest.ShipWreck.Qty = num;
				pchar.GenQuest.ShipWreck.Nation = drand(3); // нация
				pchar.GenQuest.ShipWreck.Prize = GenQuest_GenerateTotem();

				while(i < num)
				{
					iMassive = rand(24);

					if(model[iMassive] != "")
					{
						chr = GetCharacter(NPC_GenerateCharacter("ShipWreck_" + i, model[iMassive], "man", "man", iRank, sti(pchar.GenQuest.ShipWreck.nation), -1, true));
						SetFantomParamFromRank(chr, iRank, true);
						locator = GetAttributeName(GetAttributeN(grp, 1));
						ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
						//ChangeCharacterAddressGroup(chr, location.id, "goto", "goto" + (i + 1));
						FaceMaker(chr);
						chr.dialog.filename = "GenQuests_Dialog.c";
						chr.dialog.currentnode = "First time";
						chr.greeting = "Gr_MiddPirate"; // Enc_Raiders
						LAi_SetImmortal(chr, true); // До поры нельзя убить
						LAi_SetActorTypeNoGroup(chr);

						if(i == 0)
						{
							pchar.GenQuest.ShipWreck.Name = GenerateRandomName_Generator(sti(pchar.GenQuest.ShipWreck.Nation), "man");
							chr.name = pchar.GenQuest.ShipWreck.Name;
							chr.lastname = "";
							LAi_ActorDialog(chr, pchar, "", -1, 0);
						}
						else
						{
							LAi_ActorFollow(chr, pchar, "", -1);
						}

						LAi_Group_MoveCharacter(chr, "ShipWreckGroup");
						LAi_Group_SetRelation("ShipWreckGroup", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);

						i++;
						model[iMassive] = "";
					}
				}
				SetFunctionExitFromLocationCondition("ShipWreck_LocationExit", pchar.location, false);
				Log_TestInfo("Кораблекрушенцы: сгенерился квест");
			}
		break;
	}
	return true;
}
