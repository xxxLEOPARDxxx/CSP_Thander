
void ActivateTimeEvents()
{

}

//////////////////////// boal SLiB ////////////////////////////////
void SalaryNextDayUpdate()
{
	if (sti(NullCharacter.SalayPayMonth) != GetDataMonth() && !bDisableMapEnter) // boal
	{
        // проверка на наличие кому платить -->
        int nPaymentQ = 0;
        int i, cn;
        ref chref;

		for (i=0; i<COMPANION_MAX; i++)
		{
			cn = GetCompanionIndex(pchar, i);
			if (cn >= 0)
			{
				chref = GetCharacter(cn);
				if (GetRemovable(chref)) // считаем только своих, а то вских сопровождаемых кормить!!!
				{
				    nPaymentQ += GetSalaryForShip(chref);
				}
			}
		}
		// проверка на наличие кому платить <--
		NullCharacter.SalayPayMonth = GetDataMonth(); // boal
		if (nPaymentQ > 0)
		{
			if( CheckAttribute(pchar,"CrewPayment") )
			{
				nPaymentQ += makeint(pchar.CrewPayment); // а тут помним все до копейки!
			}
			if( CheckAttribute(pchar,"Partition.MonthPart") )
			{
				nPaymentQ += makeint(pchar.Partition.MonthPart); // доля за месяц
				DeleteAttribute(pchar,"Partition.MonthPart")
			}

			pchar.CrewPayment = nPaymentQ;
			LaunchMoneyGraphCollect();

			if (!dialogRun && !bQuestCheckProcessFreeze && !bAbordageStarted) // можно показать
			{
	      		LaunchSalaryScreen("");
			}
			else
			{
		        Pchar.quest.LaunchSalaryScreen.win_condition.l1 = "MapEnter";
		        PChar.quest.LaunchSalaryScreen.win_condition    = "LaunchSalaryScreen";
		        PChar.quest.LaunchSalaryScreen.function         = "LaunchSalaryScreen";
	        }
        }
	}
}

#event_handler("EvSituationsUpdate","WorldSituationsUpdate");
void WorldSituationsUpdate()
{
	int iStep = GetEventData();
	float dayRandom;
	float dayRandom1;
	float dayRandom2;

	// boal -->
	/*if (bQuestCheckProcessFreeze)   // если в квесте, то откладываем
	{
	    if(iStep < 10)
		{
			PostEvent("EvSituationsUpdate", 1000, "l", iStep);
		}
	}*/
	// boal <--

	switch(iStep)
	{
		case 0:
            DeleteAttribute(pchar, "SkipEshipIndex");// boal

			DailyEatCrewUpdate(); // boal
			Log_QuestInfo("WorldSituationsUpdate DailyEatCrewUpdate");

			dayRandom = Random();
			PChar.DayRandom = dayRandom;
			Log_TestInfo("dayRandom == " + dayRandom);

			dayRandom1 = Random();
			PChar.DayRandom1 = dayRandom1;
			Log_TestInfo("dayRandom1 == " + dayRandom1);

			dayRandom2 = Random();
			PChar.DayRandom2 = dayRandom2;
			Log_TestInfo("dayRandom2 == " + dayRandom2);

			ChangeImport();
			UpdateSmugglers();
			CheckOfficersHPMinus(); // ежедневное обновление дней для выздоровления офов
			CheckBook(); //Книги - Gregg
			CheckTrauma();//Тяжёлая травма
		break;

		case 1:
            SalaryNextDayUpdate();  // запрлата
			Log_QuestInfo("WorldSituationsUpdate SalaryNextDayUpdate");
			if(!CheckAttribute(pchar,"repairDefenders")) pchar.repairDefenders = 0;
			if(pchar.repairDefenders != GetDataMonth())
			{
				pchar.repairDefenders = GetDataMonth();
			ref _rChar;//Lipsar ---> Ремонт сторожей
			for (int i = 0; i< MAX_COLONIES; i++)
			{

				if (Colonies[i].island == sIslandID)
				{
					if (colonies[i].nation != "none" && colonies[i].id != "Caiman" && !CheckAttribute(&colonies[i], "HasNoFort") && !CheckAttribute(&colonies[i], "Siege") && !CheckAttribute(&colonies[i], "DontSetShipInPort"))
					{
						bool FortDefender;
						ref FortChref = GetFortCommander(colonies[i].id);
							for (int j=GlobalCharacters; j<MAX_CHARACTERS; j++)
							{
								if (CheckAttribute(&characters[j], "fortDefender") && CheckAttribute(&characters[j], "IslandShips"))
								{
									_rChar = &characters[j];
									if(!bSeaActive)
									{
										DeleteAttribute(_rChar, "ship.masts");
										DeleteAttribute(_rChar, "ship.sails");
										_rChar.Ship.HP = GetCharacterShipHP(_rChar);
										_rChar.Ship.SP = 100;
										SetCrewQuantityFull(_rChar);
										SetCharacterGoods(_rChar, GOOD_BALLS, 2000);
										SetCharacterGoods(_rChar, GOOD_GRAPES, 2000);
										SetCharacterGoods(_rChar, GOOD_KNIPPELS, 2000);
										SetCharacterGoods(_rChar, GOOD_BOMBS, 2000);
										SetCharacterGoods(_rChar, GOOD_POWDER, 8000);
										SetCharacterGoods(_rChar, GOOD_FOOD, 2000);
										SetCharacterGoods(_rChar, GOOD_WEAPON, 1500);
										SetCharacterGoods(_rChar, GOOD_MEDICAMENT, 1000);
										SetCharacterGoods(_rChar, GOOD_PLANKS, 800);
										SetCharacterGoods(_rChar, GOOD_SAILCLOTH, 800);
									}
								}
							}
					}
				}
			}
			Log_TestInfo("Ремонт сторожей");//Lipsar <--- Ремонт сторожей
			}
		break;

		case 2:
			// ушло в переходы локаций PGG_DailyUpdate(); // navy

			ProcessDayRepair();
		break;

		case 3:
			//UpdateDisease();

			Group_FreeAllDead();
		break;

		case 4:

			QuestActions(); //eddy
		break;

		case 5:
			//UpdateColonyProfit();

			wdmEmptyAllOldEncounter();// homo чистка энкоутеров
		break;

		case 6:

			UpdateCrewExp();  // изменение опыта команды
			CheckTraining();//треня оффов
		break;

		case 7:

			UpdateCrewInColonies(); // пересчет наемников в городах
		break;

		case 8:
			if(IsEntity(worldMap))
			{
				EmptyAllFantomCharacter(); // трем НПС
				wdmEmptyAllDeadQuestEncounter();
			}
		break;

		case 9:

            UpdateFame();   // это теперь известность репутации
			GenerateRumour() //homo 05/07/06
		break;

		case 10:
			//
		break;
	}

	iStep++;
	InterfaceStates.WorldSituationUpdateStep = iStep;

	if(iStep <= 10)
	{
		PostEvent("EvSituationsUpdate", 1000, "l", iStep);
	}
}


//////////////////////////////// начало игры - туториал ////////////////////////////////
void Tut_StartGame(string sQuest)
{
    InterfaceStates.Buttons.Save.enable = false;
	StartQuestMovie(true, true, true);
    SetCharacterTask_None(GetMainCharacter());
    LAi_LockFightMode(Pchar, true);
	PChar.GenQuest.CallFunctionParam = "Tut_Continue";
	DoQuestCheckDelay("CallFunctionParam", 5.0);
	LAi_LocationFightDisable(loadedLocation, true);
	InterfaceStates.Buttons.Save.enable = false;
	DoQuestFunctionDelay("Tut_locCamera_1", 0.1);
}

void Tut_locCamera_1(string _tmp)
{
    locCameraToPos(-5, 2.5, 5.6, false);
    DoQuestFunctionDelay("Tut_locCamera_2", 10.0);
}

void Tut_locCamera_2(string _tmp)
{
    locCameraFollow();
}
void Tut_Continue()
{
    ref sld;
    LAi_LocationFightDisable(loadedLocation, false);
    LAi_SetFightMode(Pchar, false);
    LAi_LockFightMode(pchar, true);

	if(rand(95)==0)
	{
		switch (rand(1))
		{
			case 0:
				sld = GetCharacter(NPC_GenerateCharacter("Sailor_1", "Skelt", "man", "man", 1, PIRATE, 0, false));
				sld.name 	= "T-800";
				sld.lastname 	= "";
				sld.Dialog.CurrentNode = "Alt_start";
				sld.dialog.filename = "Quest\StartGame_dialog.c";
				sld.greeting = "";
			break;
			case 1:
				StopSound(0,0);
				PlayStereoOGG("CSR\Music\Sea\Deck_Nekro.ogg");
				sld = GetCharacter(NPC_GenerateCharacter("Sailor_1", "Skel_5", "man", "man", 1, PIRATE, 0, false));
				sld.name 	= "Некромант";
				sld.lastname 	= "Сандро";
				sld.Dialog.CurrentNode = "Alt_start2";
				sld.dialog.filename = "Quest\StartGame_dialog.c";
				sld.greeting = "";
			break;
		}
	}
	else
	{
		sld = GetCharacter(NPC_GenerateCharacter("Sailor_1", "Pirate_9", "man", "man", 1, PIRATE, 0, false));
		sld.name 	= "Сандро";
		sld.lastname 	= "Торн";
		sld.Dialog.CurrentNode = "First time";
		sld.dialog.filename = "Quest\StartGame_dialog.c";
		sld.greeting = "Teacher_pirat";
	}

    SetSPECIAL(sld, 9,8,10,3,6,10,4);
    InitStartParam(sld);
    SetEnergyToCharacter(sld);

    LAi_SetCheckMinHP(sld, 1, true, "Tut_StartGame_CheckMinHP_1");
    GiveItem2Character(sld, "blade1");
	EquipCharacterByItem(sld, "blade1");
	// пустоля нет, лечилок нет
    ChangeCharacterAddressGroup(sld, "Ship_deck_Low", "reload", "reload1");
    LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 5.0, 0);

	// генерим второго матроса, но пока не ставим
	sld = GetCharacter(NPC_GenerateCharacter("Sailor_2", "shipowner_2", "man", "man", 1, PIRATE, 0, false));
    sld.name 	= "Джим";
    sld.lastname 	= "Хопкинс";

    SetSPECIAL(sld, 8,10,9,3,6,10,4);
    InitStartParam(sld);
    SetEnergyToCharacter(sld);

    LAi_SetCheckMinHP(sld, 1, true, "Tut_StartGame_CheckMinHP_2");
    GiveItem2Character(sld, "blade4");
	EquipCharacterByItem(sld, "blade4");
	GiveItem2Character(sld, "pistol2");
	EquipCharacterByItem(sld, "pistol2");
	TakeNItems(sld, "bullet", 30);
	AddItems(sld, "GunPowder", 30);
	// лечилок нет
    sld.location = "Ship_deck_Low";  // чтоб не терся, пока его нет
	//раскидаем квестовых нпс по локациям
	SetQuestsCharacters();
}

void Tut_RestoreState()
{
	ref sld;

	pchar.Health.Damg = 0.0; // здоровье бережем
	pchar.Health.weekDamg = 0.0;

	LAi_SetCurHPMax(pchar);
	LAi_SetCheckMinHP(pchar, 1, true, "Tut_StartGame_CheckMinHP_Hero");
	LAi_SetImmortal(pchar, false);

	sld = characterFromID("Sailor_1");
	LAi_SetCurHPMax(sld);
	LAi_SetCheckMinHP(sld, 1, true, "Tut_StartGame_CheckMinHP_1");
	LAi_SetImmortal(sld, false);

	sld = characterFromID("Sailor_2");
	LAi_SetCurHPMax(sld);
	LAi_SetCheckMinHP(sld, 1, true, "Tut_StartGame_CheckMinHP_2");
	LAi_SetImmortal(sld, false);

	DeleteAttribute(pchar, "HeroParam.Teach_beat");
}

void Tut_TeachBattle()
{
	ref sld;

	LAi_SetPlayerType(pchar);
	LAi_SetFightMode(Pchar, true);
	sld = characterFromID("Sailor_1");
	LAi_SetWarriorType(sld);
    LAi_group_MoveCharacter(sld, "TmpEnemy");

	if (sti(pchar.HeroParam.Teach_battle) == 2)
	{
        sld = characterFromID("Sailor_2");
		if (!IsEntity(sld))
        {
        	ChangeCharacterAddressGroup(sld, "Ship_deck_Low", "reload", "reload1");
        }
		LAi_SetWarriorType(sld);
	    LAi_group_MoveCharacter(sld, "TmpEnemy");
	}
	LAi_group_SetHearRadius("TmpEnemy", 100.0);
    LAi_group_FightGroupsEx("TmpEnemy", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
    LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
}

void Tut_StartDialog()
{
	ref sld = characterFromID("Sailor_1");

	if (CheckAttribute(pchar, "HeroParam.Teach_beat"))
	{ // признак, что выиграл
		if (sti(pchar.HeroParam.Teach_beat) == 3)
		{
		    sld.Dialog.CurrentNode = "Teach_battle_win_2";
		}
		else
		{
			if (sti(pchar.HeroParam.Teach_battle) == 1)
			{
				sld.Dialog.CurrentNode = "Teach_battle_win";
			}
			else
			{
			    sld.Dialog.CurrentNode = "Teach_battle_win_3";
			}
		}
	}
	else
	{
		sld.Dialog.CurrentNode = "Teach_battle_lose";
	}
	LAi_ActorWaitDialog(pchar, sld);
	LAi_ActorDialog(sld, pchar, "", 4.0, 0);
}
//поставить НПС-раздатчиков квеста в нужные города по нации ГГ
void SetQuestsCharacters()
{
	ref sld;
	string sTown;
	int iNation = sti(pchar.nation);
	switch (iNation)
	{
		case 0: sTown = "PortRoyal"; break;
		case 1: sTown = "Tortuga";	break;
		case 2:	sTown = "Havana";	break;
		case 3:	sTown = "Villemstad"; break;
		case 4:
			sTown = "PortRoyal";
			iNation = ENGLAND;
		break;
	}
	//заказчик убийства нищих
	sld = characterFromId("PoorKillSponsor");
	sld.nation = iNation;
	sld.city = sTown;
	sld.location = sTown + "_town";
	sld.location.group = "goto";
	sld.location.locator = "goto2";
	LAi_group_MoveCharacter(sld, GetNationNameByType(iNation) + "_citizens");
}

// выздоровление офицеров после потери сознания.
void CheckOfficersHPMinus()
{
	ref sld;
	int i, iOfficer;

	for(i = 1; i < 22; i++)  // Нюанс: обновляются только офы на должностях. Пассажиры не считаются, но я уже дрыхнуть хочу, поэтому дальше не разбираюсь. (Кто реши это - сотрите этот месседж)
	{
		if (GetOfficersIndex(Pchar, i) != -1)
		{
			iOfficer = GetOfficersIndex(Pchar, i);
			sld = GetCharacter(iOfficer);
			if (CheckAttribute(sld, "HPminusDays")) sld.HPminusDays = sti(sld.HPminusDays) + 1;

			/*if(CheckAttribute(sld,"HPminus"))
			{
				int ihpm = sti(sld.chr_ai.hp_max)+sti(sld.HPminus);*/

			if(CheckAttribute(sld, "HPminusDays") && CheckAttribute(sld, "HPminusDaysNeedtoRestore"))
			{
				if(sti(sld.HPminusDays) >= sti(sld.HPminusDaysNeedtoRestore))
				{
					DeleteAttribute(sld, "HPminusDays");
					//DeleteAttribute(sld, "HPminus");
					DeleteAttribute(sld, "HPminusDaysNeedtoRestore");
					//LAi_SetHP(sld, ihpm, ihpm);
					Log_Info("Офицер " + GetFullName(sld) + " выздоровел.");
				}
			}
		}
	}
	for(i=0; i<GetPassengersQuantity(pchar); i++)
	{
		iOfficer = GetPassenger(pchar, i);
		sld = GetCharacter(iOfficer);
		if (CheckAttribute(sld, "HPminusDays")) sld.HPminusDays = sti(sld.HPminusDays) + 1;

		/*if(CheckAttribute(sld,"HPminus"))
		{
			int ihpm = sti(sld.chr_ai.hp_max)+sti(sld.HPminus);*/

		if(CheckAttribute(sld, "HPminusDays") && CheckAttribute(sld, "HPminusDaysNeedtoRestore"))
		{
			if(sti(sld.HPminusDays) >= sti(sld.HPminusDaysNeedtoRestore))
			{
				DeleteAttribute(sld, "HPminusDays");
				//DeleteAttribute(sld, "HPminus");
				DeleteAttribute(sld, "HPminusDaysNeedtoRestore");
				//LAi_SetHP(sld, ihpm, ihpm);
				Log_Info("Офицер " + GetFullName(sld) + " выздоровел.");
			}
		}
	}
	int iCompanionQuantity = getCompanionQuantity(pchar);
	if(iCompanionQuantity > 1)
	{
		for(int n=1; n<COMPANION_MAX; n++)
		{
			iOfficer = GetCompanionIndex(pchar, n);
			sld = GetCharacter(iOfficer);
			if (CheckAttribute(sld, "HPminusDays")) sld.HPminusDays = sti(sld.HPminusDays) + 1;

		/*if(CheckAttribute(sld,"HPminus"))
		{
			int ihpm = sti(sld.chr_ai.hp_max)+sti(sld.HPminus);*/

			if(CheckAttribute(sld, "HPminusDays") && CheckAttribute(sld, "HPminusDaysNeedtoRestore"))
			{
				if(sti(sld.HPminusDays) >= sti(sld.HPminusDaysNeedtoRestore))
				{
					DeleteAttribute(sld, "HPminusDays");
					//DeleteAttribute(sld, "HPminus");
					DeleteAttribute(sld, "HPminusDaysNeedtoRestore");
					DeleteAttribute(sld, "Doctored");
					//LAi_SetHP(sld, ihpm, ihpm);
					Log_Info("Офицер " + GetFullName(sld) + " выздоровел.");
				}
			}
		}
	}
}
void CheckBook()//Проверка книги только на глобалке - Gregg
{
	if (CheckAttribute(pchar,"bookreadtoday"))//учёт чтения на суше, блок полночного чтения на глобалке
	{
		DeleteAttribute(pchar,"bookreadtoday");
		return;
	}
	if (IsEntity(&worldMap) != 0)//учёт чтения на глобалке
	{
		if (CheckAttribute(pchar,"booktype"))
		{
			if (sti(pchar.booktime) > 0)
			{
				pchar.booktime = sti(pchar.booktime)-1;
				//if (sti(pchar.booktime) != 0)Log_Info("Осталось "+pchar.booktime+" дней по полного изучения книги.");
				//if (sti(pchar.booktime) == 0)Log_Info("Последний день изучения книги!");
			}
			if (sti(pchar.booktime) <= 0)
			{
				if (pchar.booktype == "Defense") pchar.booktype = "Defence";
				if (pchar.booktype == "Defenсe") pchar.booktype = "Defence";
				AddCharacterExpToSkill(pchar, pchar.booktype, sti(pchar.bookbonus));
				int idLngFile = LanguageOpenFile("ItemsDescribe.txt");
				Log_Info(GetFullName(pchar) + " изучил книгу ''"+LanguageConvertString(idLngFile, pchar.bookname)+"'' и увеличил навык ''"+XI_ConvertString(pchar.booktype)+"''");
				LanguageCloseFile(idLngFile);
				DeleteAttribute(pchar,"booktime");
				DeleteAttribute(pchar,"booktime.full");
				DeleteAttribute(pchar,"bookbonus");
				DeleteAttribute(pchar,"booktime");
				DeleteAttribute(pchar,"booktype");
				DeleteAttribute(pchar,"bookreadtoday");
				string sEquipItem = GetCharacterEquipByGroup(pchar, BOOK_ITEM_TYPE);
				RemoveCharacterEquip(pchar, BOOK_ITEM_TYPE);
				RemoveItems(pchar, sEquipItem, 1);

				pchar.questTemp.bookcount = sti(pchar.questTemp.bookcount) + 1;
				// Открываем достижения
				if(sti(pchar.questTemp.bookcount) >= 3) UnlockAchievement("books", 1);
				if(sti(pchar.questTemp.bookcount) >= 6) UnlockAchievement("books", 2);
				if(sti(pchar.questTemp.bookcount) >= 10) UnlockAchievement("books", 3);
			}
		}
	}
}

void CheckTrauma() //тяжёлая травма - Lipsar и Gregg
{
    /*string sTmp;
    ref chr;
    aref arTmp;
    int i, idx;
    // сохраним офицеров
    makearef( arTmp, refCh.Fellows.Old.Officers );
    for(i = 1; i < MAX_NUM_FIGHTERS; i++ )
    {
        idx = GetOfficersIndex(refCh,i);
        if( idx != -1 )
        {
            chr = GetCharacter(idx);
            if(CheckAttribute(chr, "chr_ai.HeavyTrauma"))
            {
                chr.chr_ai.HeavyTrauma = sti(chr.chr_ai.HeavyTrauma) - 1;
                if(sti(chr.chr_ai.HeavyTrauma) <= 0)
                {
                    DeleteAttribute(chr, "chr_ai.HeavyTrauma");
                    Log_Info("Офицер" + chr.Name + "оправился от тяжелой травмы");
					CheckAndSetOverloadMode(chr);
                }
            }
        }
    }*/
	if(CheckAttribute(PChar, "chr_ai.Trauma"))//только ГГ, так как здоровье меняется только у ГГ
    {
		DeleteAttribute(PChar, "chr_ai.Trauma");
		Log_Info("Вы оправились от травмы");
	}
    if(CheckAttribute(PChar, "chr_ai.HeavyTrauma"))//только ГГ, так как здоровье меняется только у ГГ
    {
        PChar.chr_ai.HeavyTrauma = sti(PChar.chr_ai.HeavyTrauma) - 1;
        if(sti(PChar.chr_ai.HeavyTrauma) <= 0)
        {
			DeleteAttribute(PChar, "chr_ai.TraumaQ");
            DeleteAttribute(PChar, "chr_ai.HeavyTrauma");
            Log_Info("Вы оправились от тяжелой травмы");
			CheckAndSetOverloadMode(pchar);
        }
    }
}

void CheckTraining()//треня офов
{
	ref chref;
	for(i=1; i<MAX_CHARACTERS; i++)
	{
		makeref(chref, Characters[i]);
		if (CheckAttribute(chref, "OfficerInStockMan"))
		{
			string skilltype = skillz[rand(13)];
			log_testinfo(chref.name+" "+skilltype);
			AddCharacterExpToSkill(chref, skilltype, sti(chref.skill.(skilltype))+sti(chref.rank)+15+(GetCharacterSPECIALSimple(chref,SPECIAL_I)*2));
		}
	}
}
