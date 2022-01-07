void ProcessDialogEvent()
{
	ref NPChar, mc;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    ref chr, rShip;
    float  fTemp;
    bool bOk;
	int i, iTemp;
	string sAttr;


	// генератор ИДХ по кейсу -->
	sAttr = Dialog.CurrentNode;
  	if (findsubstr(sAttr, "CabinCompanionTalk_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	PChar.GenQuest.CabinCompanionNum = strcut(sAttr, i+1, strlen(sAttr)-1); // индех в конце
 	    Dialog.CurrentNode = "Cabin_Companion_Talk";
 	}

// Вызов персонажей by xxxZohanxxx -->
  	if (findsubstr(sAttr, "CabinPassengerTalk_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
		PChar.GenQuest.CabinPassengerNum = strcut(sAttr, i+1, strlen(sAttr)-1); // индекс в конце
 	    Dialog.CurrentNode = "Cabin_Passenger_Talk";
 	}
// <-- Вызов персонажей by xxxZohanxxx
 	// генератор ИДХ по кейсу <--

	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;

		case "WhisperTownbattle_1":
				dialog.Text = "Интересная у тебя шляпа\n(Подсказка: чтобы забрать остальные вещи нажмите клавишу 1 над трупом)";
				//GiveItem2Character(pchar, "blade19");
				//EquipCharacterByItem(pchar, "blade19");
				Pchar.model="PGG_Whisper_0";
				pchar.Whisper.HatEnabled = true;
				TakeNItems(PChar, "hatWhisper", 1);
				EquipCharacterByItem(pchar, "hatWhisper");
				ChangeWhisperHeroModel();
				Link.l1 = "Мне жаль что все так вышло, приятель. Надеюсь, ты не в обиде.";
				Link.l1.go = "exit_WhisperTownbattle";
		break;

		case "exit_WhisperTownbattle":
			NextDiag.CurrentNode = NextDiag.TempNode;
			WhisperPirateTownBattleMortality();
			//AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit_Self();
		break;
		case "exit_WhisperIncq":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			DoQuestFunctionDelay("WhisperLine_WhisperHits_3", 3.00);
		break;
		case "exit_WhisperAddWidow":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();

			mc = GetMainCharacter();

			mc.Ship.Type = GenerateShipExt(SHIP_SOPHIE, true, mc);
			mc.Ship.name="Черная Вдова";
			SetBaseShipData(mc);
			mc.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS12;
			SetCrewQuantityFull(mc);

            SetCharacterGoods(mc,GOOD_FOOD,200);
        	SetCharacterGoods(mc,GOOD_BALLS,300);//2000);
        	SetCharacterGoods(mc,GOOD_MEDICAMENT,300);//2000);
            SetCharacterGoods(mc,GOOD_GRAPES,300);//700);
            SetCharacterGoods(mc,GOOD_KNIPPELS,300);//700);
            SetCharacterGoods(mc,GOOD_BOMBS,300);//1500);
            SetCharacterGoods(mc,GOOD_POWDER,1000);
            SetCharacterGoods(mc,GOOD_PLANKS,50);
            SetCharacterGoods(mc,GOOD_SAILCLOTH,50);
            SetCharacterGoods(mc,GOOD_RUM,40);//600);
            SetCharacterGoods(mc,GOOD_WEAPON,200);//2000);
            SetCharacterGoods(mc,GOOD_EBONY,100);//2000);
		break;
		case "Exit_incq":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DoQuestFunctionDelay("WhisperLine_Inquisition", 2.0);
			WaitDate("", 0, 0, 3, 2, 30);
			DialogExit_Self();
		break;
		case "Exit_Special":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			pchar.SystemInfo.ChangePIRATES = true;
			LaunchCharacter(pchar);
		break;

		case "First time":
	      	NextDiag.TempNode = "First time";

	        Dialog.Text = "Если вы читаете эти строки, значит, где-то явный баг в коде";
			Link.l1 = "Выход";
			Link.l1.go = "exit";

			//ОЗГ
			if(CheckAttribute(pchar, "questTemp.Headhunter"))
			{
	    		if (pchar.questTemp.Headhunter == "halen_room")
        		{
        		    dialog.text = "Ну, пока можно и отдохнуть. Надо хорошенько выспаться...";
        			link.l1 = "...";
        			link.l1.go = "exit";
		    		AddDialogExitQuestFunction("RatHunters_Sleep");
        		}
			}
 			//===> Квесты мэра, базар после боевки на палубе
			if (CheckAttribute(pchar, "quest.DestroyPirate_PirateIsOut") || CheckAttribute(pchar,"quest.CaptainComission_CapIsOut"))
			{
				dialog.text = "Пора сваливать отсюда, пока кэп не вернулся с остальной командой...";
				Link.l1 = "...";
    			Link.l1.go = "exit";
				pchar.quest.Munity = "Deads";
			}
			// ==> Английская линейка, квест №8: в поселении буканьеров
   	    	if (pchar.questTemp.State == "ToMansfield_GoOn")
    		{
    		    dialog.text = "Дьявол!!! Что здесь произошло? Нужно попытаться найти хоть кого-нибудь живого...";
    			link.l1 = "...";
    			link.l1.go = "exit";
				Pchar.quest.ToMansfield_OutFromFort.win_condition.l1 = "location";
				Pchar.quest.ToMansfield_OutFromFort.win_condition.l1.location = "LaVega_port";
				Pchar.quest.ToMansfield_OutFromFort.win_condition = "ToMansfield_OutFromFort";
    		}
            // ==> Исп. линейка, квест №4: в спальне донны Анны
            if (pchar.questTemp.State == "Sp4Detection_toMirderPlace")
    		{
    		    dialog.text = "Хм, странное письмо. Она получила известие о прибытии человека... А кто мог ее известить? Тот, кто своим визитом не привлечет внимания слуг! Это может быть только местный житель. Мне нужно найти и допросить местного жителя, который известил донну Анну.";
    			link.l1 = "...";
    			link.l1.go = "exit";
                pchar.questTemp.State = "Sp4Detection_FoundLetter";
                AddQuestRecord("Spa_Line_4_MirderDetection", "2");
				AddQuestUserData("Spa_Line_4_MirderDetection", "sSex", GetSexPhrase("","а"));
    		}
            // ==> Французская линейка, квест №2: в таверне Тортуги
   	    	if (pchar.questTemp.State == "Fr2Letter_SeekProblems")
    		{
    		    dialog.text = "Странная парочка, однако... Пожалуй, стоит проследить, куда это они направились...";
    			link.l1 = "...";
    			link.l1.go = "exit";
				pchar.questTemp.Out = 1;
				SaveCurrentQuestDateParam("questTemp");
    		}
			// ==> Изабелла, нашли мертвую служанку
   	    	if (pchar.RomanticQuest == "SeekIsabella" && pchar.location == "Beliz_ExitTown")
    		{
    		    dialog.text = "Похоже, это и есть служанка Роситы... Дела Сальватора угадать легко - повсюду трупы невинных. Значит, я на верном пути.";
    			link.l1 = "...";
    			link.l1.go = "exit";
				pchar.RomanticQuest = "FoundServantGirl";
				characters[GetCharacterIndex("ServantGirl")].LifeDay = 0;
    		}
			// ==> Квест Аскольда, обнаружение входа в пещеру к гробнице
			if (pchar.questTemp.Ascold == "Ascold_NotEnterFoundGrave")
			{
				dialog.text = "Ага, здесь явно вход куда-то. Но он закрыт плитой. Войти не удается.";
				link.l1 = "";
				link.l1.go = "exit";
			}
			//===> Квест Аскольда, попытка вскрыть лампу.
			if (pchar.questTemp.Azzy == "Azzy_IHaveLamp" && locations[reload_location_index].type == "shipyard")
			{
				dialog.text = "Ага, вот и то, что мне нужно: паяльная лампа, коловорот, ножницы для жести... Можно приступать к операции...";
				Link.l1 = "Применить инструменты.";
    			Link.l1.go = "FreedomAzzy";
			}
			//===> шебека Синяя Птица
			if (pchar.questTemp.BlueBird == "seenCarriers")
			{
				dialog.text = "Та-а-ак, слышу какой-то шум. Постою здесь, посмотрю, что будет дальше...";
				Link.l1 = "...";
    			Link.l1.go = "exit";
				AddDialogExitQuestFunction("BlueBird_endCaveDialog");
			}
			//Квест нежити на перерождение
			if (CheckAttribute(pchar, "questTemp.HellSpawn.Rebirth"))
			{
				dialog.Text = "(У одного из поверженных противников вы находите клочок бумаги с каким-то текстом, а также пузырек со странным содержимым)\nКажется, чтобы переродиться, я должен выпить зелье и прочесть вслух этот текст.";
				bMonstersGen = true;
				DeleteAttribute(pchar, "questTemp.HellSpawn.Rebirth");
				Link.l1 = "(Исполнить ритуал)";
				Link.l1.go = "HellSpawn_Ritual";
				Link.l2 = "Нет, меня вполне устраивает моя текущая форма.";
				Link.l2.go = "exit";
			}
			//Старт за Шарпов
			if (CheckAttribute(pchar, "questTemp.Sharp.Entered_Shore"))
			{
				dialog.Text = "Если верить подсказкам на карте, сокровища должны быть где-то неподалеку.";
				bMonstersGen = true;
				DeleteAttribute(pchar, "questTemp.Sharp.Entered_Shore");
				Link.l1 = "Нужно отыскать грот.";
				Link.l1.go = "Exit_Special";
			}
			//Старт за Мэри и Шарля
			if (CheckAttribute(pchar, "questTemp.SharleMary.Entered_Shore"))
			{
				dialog.Text = "Матерь Небесная, вот это шторм был... Кровь... У меня голова разбита... Черт возьми, всё как в тумане. "+GetSexPhrase("Мэри! Где Мэри?!","Шарль! Где Шарль?!")+" На песке ни досок, ни трупов. 'Фортуна' погибла или дрейфует где то в море. К дьяволу их всех!";
				DeleteAttribute(pchar, "questTemp.SharleMary.Entered_Shore");
				Link.l1 = "Мне нужно найти "+GetSexPhrase("Мэри.","Шарля.");
				Link.l1.go = "Exit_Special";
			}
			if (CheckAttribute(pchar, "questTemp.SharleMary.Death"))
			{
				dialog.Text = "Ох... "+GetSexPhrase("Бедная Мэри...","Бедный Шарль...")+" У меня не вышло спасти тебя.";
				chrDisableReloadToLocation = false;
				DeleteAttribute(pchar, "questTemp.SharleMary.Death");
				Link.l1 = "Не знаю, смогу ли жить дальше после такого. Пойду на пляж, возможно, ещё хоть кто-то выжил.";
				Link.l1.go = "Exit";
			}
			//Старт за нежить
			if (CheckAttribute(pchar, "questTemp.Undead.Leave_Crypt"))
			{
				dialog.Text = "Микту... Мекетлу... М... Что со мной? Я чувствую, что "+GetSexPhrase("должен","должна")+" покинуть это место. Мне нужен корабль. Я слышу зов. Другие. Они ждут взаперти. Нет сил противиться. Я иду, бог мёртвых. Я иду.";
				DeleteAttribute(pchar, "questTemp.Undead.Leave_Crypt");
				Link.l1 = "Стоит переодеться в эту неприметную одежду, прежде чем посещать мир живых.";
				Link.l1.go = "Exit_Special";
			}
			//Линейка Виспер
			if (CheckAttribute(pchar, "questTemp.Whisper.Entered_Dungeon"))
			{
				dialog.Text = "Координаты совпадают. Кажется, я на месте. Похоже на древние катакомбы. Им лет 300, а то и больше. Надеюсь, ничего не обвалится мне на голову.";
				bMonstersGen = true;
				DeleteAttribute(pchar, "questTemp.Whisper.Entered_Dungeon");
				if (bBettaTestMode)
                {
			        link.l1 = "BetaTest - пропустить и начать игру.";
			        link.l1.go = "Whisper_Finish";
					Link.l2 = "(Перечитать сообщение от заказчика)";
					Link.l2.go = "Whisper_mission_1";

                }
				else
				{
					Link.l1 = "(Перечитать сообщение от заказчика)";
					Link.l1.go = "Whisper_mission_1";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Whisper.Inside_Incquisition"))
			{
				dialog.Text = "Проклятье, как же громко! Еще и это 'оружие' разлетелось на куски после выстрела. Эх, я бы сейчас всё отдала за свой верный шотган...";
				DeleteAttribute(pchar, "questTemp.Whisper.Inside_Incquisition");
				Link.l1 = "Нужно забрать с трупа саблю, пока остальные стражники не прибежали. Похоже, придется прорываться с боем.";
				Link.l1.go = "exit_WhisperIncq";
			}
			if (CheckAttribute(pchar, "questTemp.Whisper.Escaped_Incquisition"))
			{
				dialog.Text = "Кажется, оторвалась. Пришлось бежать из города\nСреди прочего барахла, у тюремщика была карта этого острова. На ней отмечено поселение Пуэрто-Принсипе, что находится недалеко отсюда.";
				DeleteAttribute(pchar, "questTemp.Whisper.Escaped_Incquisition");
				Link.l1 = "Стоит попытать свою удачу там.";
				Link.l1.go = "exit";
			}
			if (CheckAttribute(pchar, "questTemp.Whisper.Near_Chest"))
			{
				DeleteAttribute(pchar, "questTemp.Whisper.Near_Chest");

				dialog.Text = "Отлично, устройство у меня. Теперь пора убираться отсюда.";
				Log_Info("Вы нашли квантовый выпрямитель часлиц.");
				Link.l1 = "...";
				Link.l1.go = "exit";
			}
			if (CheckAttribute(pchar, "questTemp.Whisper.HoldMonologue"))
			{
				string sTemp = ""
				DeleteAttribute(pchar, "questTemp.Whisper.HoldMonologue");
				if (CheckAttribute(pchar, "Whisper.BonusEnergy"))
				{
					//DeleteAttribute(pchar, "Whisper.BonusEnergy");
					sTemp = "\n(Вы в одиночку вырезали половину экипажа на корабле, это навсегда укрепило ваши боевые навыки. Максимальная энергия увеличена на "+MOD_SKILL_ENEMY_RATE+".)"
				}
				dialog.Text = "Проклятье! Не хватало того, что меня закинуло в прошлое, а машина времени повреждена и находится вместе во всеми моими вещами в лапах этих немытых головорезов. В довесок я попала в плен, а в ближайшие дни меня наверняка ожидает казнь."+sTemp;
				pchar.Whisper.BonusEnergy = true;
				Link.l1 = "Нужно собраться. Я выберусь на свободу, рано или поздно.";
				Link.l1.go = "exit_incq";
			}
			if (CheckAttribute(pchar, "questTemp.Whisper.GetHat"))
			{
				DeleteAttribute(pchar, "questTemp.Whisper.GetHat");
				dialog.Text = "Вот чёрт! Пули свистят вокруг!\nПрости приятель, но я позаимствую твои пожитки, в данный момент они мне гораздо нужнее.";
				//GiveItem2Character(pchar, "blade19");
				//EquipCharacterByItem(pchar, "blade19");
				//Pchar.model="PGG_Whisper_0";
				//pchar.Whisper.HatEnabled = true;
				//TakeNItems(PChar, "hatWhisper", 1);
				//EquipCharacterByItem(pchar, "hatWhisper");

				Link.l1 = "";
				Link.l1.go = "WhisperTownbattle_1";
			}
			if (CheckAttribute(pchar, "questTemp.Whisper.AfterTownBattle"))
			{
				DeleteAttribute(pchar, "questTemp.Whisper.AfterTownBattle");
				dialog.Text = "Похоже, мы отбились. Жаль, что столько людей погибло\nДевятипалый говорил, что его тут недалеко ждет корабль. Стоит попытаться попасть на него, ведь испанцы наверняка могут вернуться сюда в любой момент с подкреплением.";
				Link.l1 = "Нужно найти бухту.";
				Link.l1.go = "exit_WhisperAddWidow";
				PChar.quest.WhisperPirateTownBattle.win_condition.l1 = "location";
				PChar.quest.WhisperPirateTownBattle.win_condition.l1.location = "PuertoPrincipe_Port";
				PChar.quest.WhisperPirateTownBattle.function = "WhisperMeetCrew";
			}
			if (CheckAttribute(pchar, "questTemp.Whisper.SmugPatrol"))
			{
				DeleteAttribute(pchar, "questTemp.Whisper.SmugPatrol");
				dialog.Text = "Так и знала! Конечно же сюда заходят патрули, этот торгаш мне лапшу на уши навесил.";
				Link.l1 = "Нужно поспешить на палубу, пока мне корабль не потопили.";
				Link.l1.go = "exit";
			}
			if (CheckAttribute(pchar, "questTemp.Whisper.Portman_Deck"))
			{
				DeleteAttribute(pchar, "questTemp.Whisper.Portman_Deck");
				dialog.Text = "Не думаю, что я смогу что-то выяснить блуждая по палубе, а в каюту меня не пустят.";
				Link.l1 = "Остается только один выход - брать на абордаж.";
				Link.l1.go = "exit";
			}
			if (CheckAttribute(pchar, "questTemp.Whisper.KilledPortman"))
			{
				DeleteAttribute(pchar, "questTemp.Whisper.KilledPortman");
				AddQuestRecord("WhisperChardQuest", "7");
				pchar.Whisper.FoundPortmanJournal = true;
				dialog.Text = "Хм... В журнале тоже какой-то шифр. Не думаю, что сама разберусь в нём.";
				Link.l1 = "Нужно отнести его Чарду.";
				Link.l1.go = "exit";
			}
			if (CheckAttribute(pchar, "questTemp.Whisper.EngRevenge"))
			{
				AddQuestRecord("WhisperChardQuest", "9");
				CloseQuestHeader("WhisperChardQuest");
				DeleteAttribute(pchar, "questTemp.Whisper.EngRevenge");
				dialog.Text = "Похоже, смерть Портмана разозлила англичан. Я уже вижу на горизонте корабли.";
				Link.l1 = "Стоит поспешить к шлюпке.";
				Link.l1.go = "exit";
			}
			//Линейка Виспер
		break;
		// boal -->
		case "TalkSelf_Main":
	   		NextDiag.TempNode = "First time";
//navy --> after duel in tavern
			if (CheckAttribute(pchar, "questTemp.LocationClone"))
			{
				Dialog.Text = RandPhraseSimple("Жаркая была схватка... Теперь можно позвать разбежавшихся трусов.", "Ха! Это было просто. А эти сухопутные крысы разбежались!");
				link.l1 = "...";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.LocationClone");
				break;
			}
//navy <--
	        Dialog.Text = RandPhraseSimple("Хм... Что бы мне сейчас хотелось сделать?", "Чем бы заняться?");
		if(!bDisableMapEnter && !CheckAttribute(pchar,"GenQuest.CannotWait") && CheckSaveGameEnabled() == true) // 21.03.09 Warship fix Во время линейки Блада отдыхать нельзя
	    {
				if(PChar.Dozor != "0" && PChar.Dozor != "END")
				{
					if(sti(PChar.Dozor.Riddle.CanInterface) == 1)
					{
							link.l4 = "Текущее задание мекахрома.";
							link.l4.go = "Dozor_MekaKhrom";
					}
				}
		}
	        if (!bDisableMapEnter && pchar.location == Get_My_Cabin())
	        {
	        	// Для отдыха теперь есть отдельный интерфейс
	            if (makeint(environment.time) >= 22.0 || makeint(environment.time) < 10.0)
	    		{
	    			link.l1 = "Отдыхать до утра.";
	    			link.l1.go = "TalkSelf_room_day";
	    		}
	    		else
	    		{
	    			link.l1 = "Отдыхать до ночи.";
	    			link.l1.go = "TalkSelf_room_night";
	    			link.l2 = "Отдыхать до следующего утра.";
					link.l2.go = "TalkSelf_room_day";
	    		}
				//navy --> 13.02.08
				if (!bDisableMapEnter && pchar.location == Get_My_Cabin())
				{
// Вызов персонажей by xxxZohanxxx -->
					link.l3 = "Вызвать ко мне...";
					link.l3.go = "Cabin_PersonSelect";
// <-- Вызов персонажей by xxxZohanxxx
				}
				//navy <--
			}
			else
			{   //исп.линейка, квест №6, возможность переночевать в оплаченной комнате
				if (CheckAttribute(pchar, "questTemp.State.Open") && pchar.location == "Tortuga_tavern_upstairs")
				{
					if (makeint(environment.time) >= 22.0 || makeint(environment.time) < 10.0)
	    			{
	    				link.l1 = "Отдыхать до утра.";
	    				link.l1.go = "TalkSelf_room_day";
	    			}
	    			else
	    			{
	    				link.l1 = "Отдыхать до ночи.";
	    				link.l1.go = "TalkSelf_room_night";
	    				link.l2 = "Отдыхать до следующего утра.";
						link.l2.go = "TalkSelf_room_day";
	    			}
				}
			}
	        /*if (CheckAttribute(pchar, "Quest.Loans") || CheckAttribute(pchar, "Quest.Deposits"))
	        {
	    		Link.l4 = "Кассовая книга.";
	    		Link.l4.go = "TalkSelf_CashBook";
			}*/
	        if (!bDisableMapEnter)//боя в море нет
	        {
	            if (GetCargoGoods(pchar, GOOD_SLAVES) > 0)
	            {
	                Link.l5 = "Зачислить рабов в команду";
	        		Link.l5.go = "TalkSelf_SlavesToCrew";
	    		}
	        }
	        // захват города
	        if (GetCharIDXForTownAttack(pchar.location) != -1 && !CheckAttribute(Pchar, "GenQuestFort.StartAttack"))
	        {
	            Link.l6 = "Начать захват ближайшего города.";
	    		Link.l6.go = "TalkSelf_TownAttack";
	        }

			if(PChar.ColonyBuilding.Stage != "0" && PChar.ColonyBuilding.Hovernor == "")
			{
				if(CheckAttribute(&Locations[FindLocation(PChar.location)], "islandId"))
				{
					if(Locations[FindLocation(PChar.location)].islandId == "Caiman")
					{
						Link.l18 = "Хм... Необходимо как можно скорее назначить управляющего колонии ''" + PChar.ColonyBuilding.ColonyName + "''. Быть может, я и сам"+GetSexPhrase("","а")+" справлюсь?";
						Link.l18.go = "ColonyBuilding_Hovernor_1";
					}
				}
			}

			if(PChar.ColonyBuilding.Hovernor == PChar.id)
			{
				if(CheckAttribute(&Locations[FindLocation(PChar.location)], "islandId"))
				{
					if(Locations[FindLocation(PChar.location)].islandId == "Caiman")
					{
						Link.l19 = "Перейти к делам колонии.";
						Link.l19.go = "ColonyBuilding_Hovernor";
					}
				}
			}

			if(PChar.Dozor != "0" && PChar.Dozor != "END")
			{
				if(sti(PChar.Dozor.Riddle.CanInterface) == 1)
				{
		    			link.l10 = "Текущее задание мекахрома.";
		    			link.l10.go = "Dozor_MekaKhrom";
				}
			}

			if (!CheckAttribute(pchar,"questTemp.stels.sea")) pchar.questTemp.stels.sea = GetDataDay();
	        if (pchar.location != Get_My_Cabin() && Pchar.questTemp.CapBloodLine == false && !CheckAttribute(pchar, "DisableChangeFlagMode") && sti(pchar.questTemp.stels.sea) != GetDataDay() && CheckSaveGameEnabled() == true)
			{
				Link.l7 = "Отдать приказ на смену флага.";
				Link.l7.go = "TalkSelf_ChangeFlag";
			}
	        if(!bDisableMapEnter && Pchar.questTemp.CapBloodLine == false && PChar.location != "Deck_Near_Ship" && findsubstr(PChar.location, "_shipyard" , 0) == -1 && PChar.location != "CommonPackhouse_2" && !CheckAttribute(pchar,"GenQuest.CannotWait") && !CheckAttribute(pchar,"ContraInterruptWaiting")) // 21.03.09 Warship fix Во время линейки Блада отдыхать нельзя
	        {
	        	Link.l8 = "Мне не мешало бы отдохнуть...";
	    		Link.l8.go = "TalkSelf_StartWait";
	    	}
			if(!CheckAttribute(pchar,"bookreadtoday") && CheckAttribute(pchar,"booktime") && !bDisableMapEnter && Pchar.questTemp.CapBloodLine == false && PChar.location != "Deck_Near_Ship" && findsubstr(PChar.location, "_shipyard" , 0) == -1 && PChar.location != "CommonPackhouse_2" && !CheckAttribute(pchar,"GenQuest.CannotWait")) // 21.03.09 Warship fix Во время линейки Блада отдыхать нельзя
	        {
	        	Link.l9 = "Почитать книгу.";
	    		Link.l9.go = "ReadBook";
	    	}
			Link.l10 = "Установить приоритет использования еды.";
	    	Link.l10.go = "food_priority";
			if (pchar.location == Get_My_Cabin())
				{
				Link.l11 = "Использовать еду автоматически.";
				Link.l11.go = "autofood";
				if(CheckAttribute(pchar,"autofood"))
				{
					Link.l11 = "Прекратить автоматическое использование еды.";
					Link.l11.go = "autofood_stop";
				}
			}
			if (CheckAttribute(pchar,"usepotionbest"))
			{
				link.lpotion = "Снять приоритет на использование лучших лечебных средств.";
				Link.lpotion.go = "potion_priority";
			}
			else
			{
				link.lpotion = "Установить приоритет на использование лучших лечебных средств.";
				Link.lpotion.go = "potion_priority";
			}
			if(startHeroType == 2)
			{
				if(CheckCharacterItem(pchar,"hatWhisper"))
				{
					if (!CheckAttribute(pchar,"Whisper.Equipped"))
					{
						Link.lWhisperHat = "Прекратить носить шляпу.";
						Link.lWhisperHat.go = "WhisperHatUnequip";
					}
					else
					{
						Link.lWhisperHat = "Носить шляпу.";
						Link.lWhisperHat.go = "WhisperHatEquip";
					}
				}
				if(CheckCharacterItem(pchar,"glasses"))
				{
					if (IsEquipCharacterByItem(pchar, "glasses"))
					{
						Link.lWhisperGlasses = "Прекратить носить очки.";
						Link.lWhisperGlasses.go = "WhisperGlassesUnequip";
					}
					else
					{
						Link.lWhisperGlasses = "Носить очки.";
						Link.lWhisperGlasses.go = "WhisperGlassesEquip";
					}
				}
				Link.lWhisperPortrait = "Сменить портрет.";
				Link.lWhisperPortrait.go = "WhisperPortrait";
			}
			if (bBettaTestMode)
			{
				Link.l12 = "Установить время на глобальной карте (должно быть значение float)";
				Link.l12.go = "WorldmapTime";
			}

			Link.lSmugglingFlag = "Во время контрабандных сделок, автоматически менять флаг на пиратский, в случае нападения патруля.";
			Link.lSmugglingFlag.go = "SmugglingFlag";
			if (CheckAttribute(pchar, "SmugglingFlag"))
			{
				Link.lSmugglingFlag = "Отключить автоматическую смену флага во время контрабандных сделок.";
				Link.lSmugglingFlag.go = "SmugglingFlag";
			}

			Link.l14 = RandPhraseSimple("Не сейчас. Нет времени.", "Некогда. Дела ждут.");
			Link.l14.go = "exit";
		break;

		case "SmugglingFlag":
			if (CheckAttribute(pchar, "SmugglingFlag")) DeleteAttribute(pchar, "SmugglingFlag");
			else pchar.SmugglingFlag = true;
			Dialog.Text = "Готово.";
			Link.l12 = "С этим закончили.";
			Link.l12.go = "exit";
		break;
// Вызов персонажей by xxxZohanxxx -->
		case "Cabin_PersonSelect":
				Dialog.Text = "Кого именно?";
				if (!bDisableMapEnter && GetCompanionQuantity(PChar) > 1)
				{
    				link.l1 = "Компаньона.";
    				link.l1.go = "Cabin_CompanionSelect";
				}
				if (!bDisableMapEnter)
				{
					if (sti(pchar.Fellows.Passengers.navigator) != -1 || sti(pchar.Fellows.Passengers.boatswain) != -1 || sti(pchar.Fellows.Passengers.cannoner) != -1 || sti(pchar.Fellows.Passengers.doctor) != -1 || sti(pchar.Fellows.Passengers.treasurer) != -1 || sti(pchar.Fellows.Passengers.carpenter) != -1)
					{
					link.l2 = "Офицера.";
    				link.l2.go = "Cabin_OfficerSelect";
					}
				}
				if (!bDisableMapEnter)
				{
					link.l3 = "Пассажира.";
    				link.l3.go = "Cabin_PassengerSelect";
				}
			link.l4 = "В другой раз.";
			link.l4.go = "exit";
		break;
// <-- Вызов персонажей by xxxZohanxxx

		case "WorldmapTime":
			Dialog.Text = "Напишите float число формата x.x, желательно не более 12.0, иначе возможны сбои даже при небольшом ускорении времени.";
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "WorldmapTime_Change";
		break;

		case "WorldmapTime_Change":
			if (stf(GetStrSmallRegister(dialogEditStrings[1])) > 0.0 && stf(GetStrSmallRegister(dialogEditStrings[1])) < 12.1) pchar.wmtimechange = stf(GetStrSmallRegister(dialogEditStrings[1]));
			else pchar.wmtimechange = 0.5;
			if (stf(pchar.wmtimechange) != 0.5) Dialog.Text = "Установлена скорость глобальной карты "+pchar.wmtimechange+".";
			else Dialog.Text = "Установлена стандартное значение в 0.5.";
			worldMap.date.hourPerSec = stf(pchar.wmtimechange);
			Link.l1 = "Отлично.";
			Link.l1.go = "exit";
		break;
		case "HellSpawn_Ritual"://перерождение
			Dialog.Text = "(Вы чувствуете себя немного другим).";
			pchar.Ritual.ModelChanged = false;
			if (HasSubStr(pchar.model,"Skeletcap"))
			{//веселый роджер
				pchar.sex = "man";
				pchar.animation = "man";
				pchar.model = "PGG_Tich_0";
				pchar.HeroModel  = "PGG_Tich_0,PGG_Tich_1,PGG_Tich_2,PGG_Tich_3,PGG_Tich_4,PGG_Tich_5";
				pchar.Ritual.ModelChanged = true;
			}
			if (HasSubStr(pchar.model,"PGG_Ghost"))
			{//призрак джессики
				pchar.sex = "woman";
				pchar.animation = "Jessika";
				pchar.model = "PGG_MaryBred_0";
				pchar.HeroModel  = "PGG_MaryBred_0,PGG_MaryBred_1,PGG_MaryBred_2,PGG_MaryBred_3,PGG_MaryBred_4,PGG_MaryBred_5";
				pchar.Ritual.ModelChanged = true;
			}
			if (HasSubStr(pchar.model,"PGG_Meriman"))
			{//ужасный
				pchar.sex = "man";
				pchar.animation = "man";
				pchar.model = "PGG_WillTerner_0";
				pchar.HeroModel  = "PGG_WillTerner_0,PGG_WillTerner_1,PGG_WillTerner_2,PGG_WillTerner_3,PGG_WillTerner_4,PGG_WillTerner_5,PGG_WillTerner_6,PGG_WillTerner_7,PGG_WillTerner_8";
				pchar.Ritual.ModelChanged = true;
			}
			/*if (pchar.HeroModel == "PGG_Giant_0,PGG_Giant_1,PGG_Giant_2,PGG_Giant_3,PGG_Giant_4,PGG_Giant_5" )
			{//каскос
				pchar.Ritual.ModelChanged = true;
			}*/
			if (pchar.Ritual.ModelChanged == false)
			{//никто из перечисленных
				pchar.sex = "man";
				pchar.animation = "man";
				pchar.model = "PGG_Pat_0";
				pchar.HeroModel  = "PGG_Pat_0,PGG_Pat_1,PGG_Pat_2,PGG_Pat_3,PGG_Pat_4,PGG_Pat_5,PGG_Pat_6,PGG_Pat_7,PGG_Pat_8";
			}
			SetNewModelToChar(pchar);
			link.l1 = "Что-то мне нехорошо. Выйду на воздух.";
			Link.l1.go = "exit";
		break

		case "autofood":
			Dialog.Text = "Введите процент, до которого должна опуститься энергия, прежде чем начать использовать еду (10-90).";
			//PChar.autofood_use
			link.l1 = "";
			Link.l1.edit = 3;
			Link.l1.go = "autofood_percentage";
		break

		case "autofood_stop":
			//DoQuestReloadToLocation(pchar.location, "reload", "LAi_FindNearestFreeLocator("reload", locx, locy, locz)", "");
			DeleteAttribute(pchar, "autofood");
			DeleteAttribute(pchar, "autofood_use");
			dialog.text = "Автоматическое использование еды отключено.";
			Link.l1 = "Всё, хватит на сегодня.";
			Link.l1.go = "exit";
		break

		case "autofood_percentage":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 10 || iTemp > 90)
			{
				dialog.text = "Что-то я немного не в себе сегодня... В другой раз, пожалуй.";
				link.l1 = "Дьявол!";
				link.l1.go = "exit";
				break;
			}
			PChar.autofood_use = iTemp;
			dialog.text = "Автоматическое использование еды включено.";
			pchar.autofood = true;
			link.l1 = "Славно!";
			link.l1.go = "exit";
		break;

		case "food_priority":
			dialog.text = "Какую еду стоит использовать в первую очередь?.";
			link.l1 = "Менее питательную (Фрукты, хлеб)";
			link.l1.go = "autofood_finished";
			link.l2 = "Более питательную (Рыба, мясо)";
			link.l2.go = "autofood_finished_betterfood";
		break;

		case "potion_priority":
			if (CheckAttribute(pchar,"usepotionbest"))
			{
				dialog.text = "Снят приоритет на использование самых сильных лечебных средств.";
				link.l1 = "Славно!";
				link.l1.go = "exit";
				DeleteAttribute(pchar,"usepotionbest");
			}
			else
			{
				dialog.text = "Установлен приоритет на использование самых сильных лечебных средств.";
				link.l1 = "Славно!";
				link.l1.go = "exit";
				pchar.usepotionbest = true;
			}
		break;

		case "autofood_finished":
			dialog.text = "Приоритет для еды установлен.";
			DeleteAttribute(pchar, "autofood_betterfood");
			link.l1 = "Славно!";
			link.l1.go = "exit";
		break;

		case "autofood_finished_betterfood":
			dialog.text = "Приоритет для еды установлен.";
			PChar.autofood_betterfood = true;
			link.l1 = "Славно!";
			link.l1.go = "exit";
		break;

		case "ReadBook":
			Dialog.Text = "Ну что-ж, почитал"+GetSexPhrase("","а")+" пару часов...";
			WasteTime(4);
			pchar.booktime = sti(pchar.booktime) - 1;
			pchar.bookreadtoday = true;
			if (sti(pchar.booktime) <= 0)
			{
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
			}
			Link.l6 = "Всё, хватит на сегодня.";
			Link.l6.go = "exit";
		break

		case "TalkSelf_ChangeFlag":
			Dialog.Text = "Какой флаг мне необходим на данный момент? Его смена займёт 1 час.";
			if (IsCharacterPerkOn(pchar,"FlagPir") && sti(pchar.nation) != 4) {Link.l1 = "Поднять пиратский флаг."; Link.l1.go = "TalkSelf_ChangeFlagPir";}
			if (IsCharacterPerkOn(pchar,"FlagEng") && sti(pchar.nation) != 0) {Link.l2 = "Поднять английский флаг."; Link.l2.go = "TalkSelf_ChangeFlagEng";}
			if (IsCharacterPerkOn(pchar,"FlagFra") && sti(pchar.nation) != 1) {Link.l3 = "Поднять французский флаг."; Link.l3.go = "TalkSelf_ChangeFlagFra";}
			if (IsCharacterPerkOn(pchar,"FlagSpa") && sti(pchar.nation) != 2) {Link.l4 = "Поднять испанский флаг."; Link.l4.go = "TalkSelf_ChangeFlagSpa";}
			if (IsCharacterPerkOn(pchar,"FlagHol") && sti(pchar.nation) != 3) {Link.l5 = "Поднять голландский флаг."; Link.l5.go = "TalkSelf_ChangeFlagHol";}
			Link.l6 = RandPhraseSimple("Не сейчас. Нет времени.", "Некогда. Дела ждут.");
			Link.l6.go = "exit";
		break;

		case "TalkSelf_ChangeFlagPir":
			Log_Info("Выбран пиратский флаг");
			FlagsProcess1(4);
			DialogExit_Self();
		break;

		case "TalkSelf_ChangeFlagEng":
			Log_Info("Выбран английский флаг");
			FlagsProcess1(0);
			DialogExit_Self();
		break;

		case "TalkSelf_ChangeFlagFra":
			Log_Info("Выбран французский флаг");
			FlagsProcess1(1);
			DialogExit_Self();
		break;

		case "TalkSelf_ChangeFlagSpa":
			Log_Info("Выбран испанский флаг");
			FlagsProcess1(2);
			DialogExit_Self();
		break;

		case "TalkSelf_ChangeFlagHol":
			Log_Info("Выбран голландский флаг");
			FlagsProcess1(3);
			DialogExit_Self();
		break;

		// Мекахром смотрим
		case "Dozor_MekaKhrom":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			LaunchMekakhrom();
		break;

		case "TalkSelf_StartWait":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			PChar.GenQuest.CallFunctionParam = "LaunchTavernWaitScreen";
			DoQuestCheckDelay("CallFunctionParam", 0.1); // Нужно с задержкой, иначе - ГГ начинает крутиться
		break;

		case "TalkSelf_room_night":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Night");
			TavernWaitDate("wait_night");
			DialogExit_Self();
		break;

		case "TalkSelf_room_day":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Day");
			TavernWaitDate("wait_day");
			DialogExit_Self();
		break;
		//  захват города
		case "TalkSelf_TownAttack":
            bOk = (GetPartyCrewQuantity(Pchar, true) >= 500) || bBettaTestMode;
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && bOk)
	        {
	            chr = GetCharacter(GetCharIDXForTownAttack(pchar.location));
	            if (chr.from_sea == Pchar.location.from_sea)
	            {
					Dialog.Text = "Начать захват, конечно, можно, да вот только корабль под залпами форта долго не продержится. И десант высадить не успеем.";
	    			Link.l1 = "...";
	    			Link.l1.go = "exit";
	            }
	            else
	            {
	                if (pchar.location == "Santiago_ExitTown")
					{
						if (CheckAttribute(pchar, "PGGWhisperLetter") || CheckAttribute(pchar, "PGGWhisperLetterSent"))
						{
							Dialog.Text = "У форта достаточно орудий, чтобы похоронить нас прямо в городе. Нет, Виспер права - захватить Сантьяго можно только с моря.";
							Link.l1 = "...";
							Link.l1.go = "exit";
							break;
						}
					}
					if (pchar.location == "Panama_ExitTown")
					{
						Dialog.Text = "Не-е-ет, я не сумасшедш"+ GetSexPhrase("ий","ая")+". Это же Панама! Взять ее НЕВОЗМОЖНО!!! Надо валить отсюда, а то точно дождусь черной метки...";
	    				Link.l1 = "...";
	    				Link.l1.go = "exit";
					}
					else
					{
						Dialog.Text = "Напасть на город " + GetCityName(chr.City) + ".";
		    			Link.l1 = "К оружию!";
		    			Link.l1.go = "TalkSelf_TownAttack_Start";
		    			Link.l2 = "Отставить!";
		    			Link.l2.go = "exit";
					}
	    		}
	        }
	        else
	        {
				if(!CheckAttribute(Pchar, "GenQuestFort.StartAttack"))
				{
					Dialog.Text = "Эх! Команды маловато, нужно хотя бы 500 человек.";
					Link.l1 = "...";
					Link.l1.go = "exit";
				}
				else
				{
					Dialog.Text = "Не разбредаться! Продолжаем атаку!";
					Link.l2 = "...";
					Link.l2.go = "exit";
				}
			}
	    break;

		case "TalkSelf_TownAttack_Start":
	        NextDiag.CurrentNode = NextDiag.TempNode;

			Pchar.GenQuestFort.StartAttack = true;
		    Pchar.GenQuestFort.fortCharacterIdx = GetCharIDXForTownAttack(pchar.location);
		    DeleteQuestAttribute("Union_with_Escadra");
	        chr = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
			if (isCityHasFort(chr.City))
			{
	        	SetLocationCapturedState(chr.from_sea, true);
	        }
	        else
	        {
	            SetLocationCapturedState(chr.Default, true); // для сухопутных
	        }
	        AddDialogExitQuest("Capture_Forts");
	        Ship_NationAgressive(chr, chr);
	        DialogExit_Self();
	    break;
	    // Зачислить рабов в команду  -->
		case "TalkSelf_SlavesToCrew":
	        if (GetCurCrewEscadr() >= GetMaxCrewAble())
	        {
	            Dialog.Text = "Никто из рабов не хочет идти в команду.";
	            Link.l1 = "Ну и не нужно!";
	    		Link.l1.go = "exit";
	        }
	        else
	        {
	            if (GetCrewQuantity(pchar) >= GetMaxCrewQuantity(pchar))
	            {
	                Dialog.Text = "На корабле нет места для новых матросов.";
	                Link.l1 = "Эх! Нужно переместить часть экипажа на другой корабль.";
	        		Link.l1.go = "exit";
	            }
	            else
	            {
	                if (GetFreeCrewQuantity(pchar) <= GetCargoGoods(pchar, GOOD_SLAVES))
	                {
	                    pchar.GenQuest.SlavesToCrew = GetFreeCrewQuantity(pchar);
	                }
	                else
	                {
	                    pchar.GenQuest.SlavesToCrew = GetCargoGoods(pchar, GOOD_SLAVES);
	                }
	                Dialog.Text = "В команду желают пойти " + pchar.GenQuest.SlavesToCrew+ " рабов. Взять их?";
	                Link.l1 = "Да";
	        		Link.l1.go = "TalkSelf_SlavesToCrew_1";
	        		Link.l2 = "Нет";
	        		Link.l2.go = "exit";
	    		}
			}
		break;

		case "TalkSelf_SlavesToCrew_1":
	        if (CheckOfficersPerk(pchar, "IronWill"))
	        {
	            AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 5.0))
	        }
	        else
	        {
	            AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 3.0))
	        }
	        // падение опыта -->
	        fTemp =  stf(GetCrewQuantity(pchar) + sti(pchar.GenQuest.SlavesToCrew));
	        pchar.Ship.Crew.Exp.Sailors   = (stf(pchar.Ship.Crew.Exp.Sailors)*GetCrewQuantity(pchar) +
			                                        stf(pchar.Ship.Crew.Exp.Sailors)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Cannoners   = (stf(pchar.Ship.Crew.Exp.Cannoners)*GetCrewQuantity(pchar) +
			                                        stf(pchar.Ship.Crew.Exp.Cannoners)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Soldiers   = (stf(pchar.Ship.Crew.Exp.Soldiers)*GetCrewQuantity(pchar) +
			                                        stf(pchar.Ship.Crew.Exp.Soldiers)*0.3*sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			// падение опыта <--
			pchar.Ship.Crew.Quantity = sti(pchar.Ship.Crew.Quantity) + sti(pchar.GenQuest.SlavesToCrew);
	        RemoveCharacterGoodsSelf(pchar, GOOD_SLAVES, sti(pchar.GenQuest.SlavesToCrew));

	        NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
		// Зачислить рабов в команду  <--
		// boal <--

//navy CONTRABAND METRO -->
		case "GenTravel_Main":
			NextDiag.TempNode = "First time";
			dialog.Text = "Теперь этот отличный корабль мой, и я здесь капитан! Жаль, пришлось вырезать всю команду.";
			Link.l1 = "Пора на берег...";
			Link.l1.go = "exit";

			chr = CharacterFromID("Abracham_Gray");
			chr.location = "none";
			SeaExchangeCharactersShips(PChar, chr, false, false);
			SetCrewQuantity(PChar, 0);

			//грузим ГГ куда нужно...
			SetAnyReloadToLocation(pchar.GenQuest.contraTravel.destination.loc, pchar.GenQuest.contraTravel.destination.group, pchar.GenQuest.contraTravel.destination.locator, "", 0, 0, 0, 0);
			AddDialogExitQuest("AnyReloadToLocation");
            chrDisableReloadToLocation = false;

			CloseQuestHeader("Gen_ContrabandTravel");
			setCharacterShipLocation(PChar, pchar.GenQuest.contraTravel.destination.loc);
			setWDMPointXZ(pchar.GenQuest.contraTravel.destination.loc);

			//трем аттрибуты
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			break;
//navy CONTRABAND METRO <--

//navy --> 13.02.08
		case "Cabin_CompanionSelect":
			Dialog.Text = "Кого из компаньонов вызвать?";
			for (i = 1; i < GetCompanionQuantity(PChar); i++)
			{
				chr = GetCharacter(GetCompanionIndex(PChar, i));
				if (!CheckAttribute(chr, "Tasks.Clone") && sti(chr.Payment) == true)
				{
					sAttr = "l" + i;
					rShip = GetRealShip(sti(chr.Ship.Type));
					link.(sAttr) = GetFullName(chr) + " - " + xiStr(rShip.BaseName) + " '" + chr.Ship.Name + "'.";
					link.(sAttr).go = "CabinCompanionTalk_" + i;
				}
			}
			link.l9 = "В другой раз.";
			link.l9.go = "exit";
			break;

// Вызов персонажей by xxxZohanxxx -->
		case "Cabin_OfficerSelect":
			Dialog.Text = "Кого из офицеров вызвать?";
			if (sti(pchar.Fellows.Passengers.navigator) != -1)
			{
				chr = GetCharacter(sti(pchar.Fellows.Passengers.navigator));
				if (chr.location != Get_My_Cabin())
				{
				link.l1 = "Штурман " + GetFullName(chr) + ".";
				link.l1.go = "Cabin_navigator_Talk";
				}
			}
			if (sti(pchar.Fellows.Passengers.boatswain) != -1)
			{
				chr = GetCharacter(sti(pchar.Fellows.Passengers.boatswain));
				if (chr.location != Get_My_Cabin())
				{
				link.l2 = "Боцман " + GetFullName(chr) + ".";
				link.l2.go = "Cabin_boatswain_Talk";
				}
			}
			if (sti(pchar.Fellows.Passengers.cannoner) != -1)
			{
				chr = GetCharacter(sti(pchar.Fellows.Passengers.cannoner));
				if (chr.location != Get_My_Cabin())
				{
				link.l3 = "Канонир " + GetFullName(chr) + ".";
				link.l3.go = "Cabin_cannoner_Talk";
				}
			}
			if (sti(pchar.Fellows.Passengers.doctor) != -1)
			{
				chr = GetCharacter(sti(pchar.Fellows.Passengers.doctor));
				if (chr.location != Get_My_Cabin())
				{
				link.l4 = "Врач " + GetFullName(chr) + ".";
				link.l4.go = "Cabin_doctor_Talk";
				}
			}
			if (sti(pchar.Fellows.Passengers.treasurer) != -1)
			{
				chr = GetCharacter(sti(pchar.Fellows.Passengers.treasurer));
				if (chr.location != Get_My_Cabin())
				{
				link.l5 = "Казначей " + GetFullName(chr) + ".";
				link.l5.go = "Cabin_treasurer_Talk";
				}
			}
			if (sti(pchar.Fellows.Passengers.carpenter) != -1)
			{
				chr = GetCharacter(sti(pchar.Fellows.Passengers.carpenter));
				if (chr.location != Get_My_Cabin())
				{
				link.l6 = "Плотник " + GetFullName(chr) + ".";
				link.l6.go = "Cabin_carpenter_Talk";
				}
			}
			link.l7 = "В другой раз.";
			link.l7.go = "exit";
			break;

		case "Cabin_PassengerSelect":
			Dialog.Text = "Кого из пассажиров вызвать?";
			for (i = 0; i < GetPassengersQuantity(PChar); i++)
			{
				chr = GetCharacter(GetPassenger(PChar,i));
					if (HasSubStr(chr.id,"ShipWreckSailor"))
					{
						LAi_SetCitizenType(chr);
						sAttr = "l" + i;
						link.(sAttr) = GetFullName(chr) + ".";
						link.(sAttr).go = "CabinPassengerTalk_" + i;
						continue;
					}
					if (!CheckAttribute(chr,"prisoned") && !IsOfficer(chr) && GetRemovable(chr) && chr.location != Get_My_Cabin() && !CheckAttribute(chr, "isfree")) // Чтобы в список не попадали квестовые, офицеры и пленники
					{
						sAttr = "l" + i;
						link.(sAttr) = GetFullName(chr) + ".";
						link.(sAttr).go = "CabinPassengerTalk_" + i;
					}
			}
			link.l99 = "В другой раз.";
			link.l99.go = "exit";
			break;

		case "Cabin_navigator_Talk":
			chr = GetCharacter(sti(pchar.Fellows.Passengers.navigator));
			PlaceCharacter(chr, "rld", PChar.location);
			LAi_SetStayType(chr);
			DialogExit_Self();
		break;
		case "Cabin_boatswain_Talk":
			chr = GetCharacter(sti(pchar.Fellows.Passengers.boatswain));
			PlaceCharacter(chr, "rld", PChar.location);
			LAi_SetStayType(chr);
			DialogExit_Self();
		break;
		case "Cabin_cannoner_Talk":
			chr = GetCharacter(sti(pchar.Fellows.Passengers.cannoner));
			PlaceCharacter(chr, "rld", PChar.location);
			LAi_SetStayType(chr);
			DialogExit_Self();
		break;
		case "Cabin_doctor_Talk":
			chr = GetCharacter(sti(pchar.Fellows.Passengers.doctor));
			PlaceCharacter(chr, "rld", PChar.location);
			LAi_SetStayType(chr);
			DialogExit_Self();
		break;
		case "Cabin_treasurer_Talk":
			chr = GetCharacter(sti(pchar.Fellows.Passengers.treasurer));
			PlaceCharacter(chr, "rld", PChar.location);
			LAi_SetStayType(chr);
			DialogExit_Self();
		break;
		case "Cabin_carpenter_Talk":
			chr = GetCharacter(sti(pchar.Fellows.Passengers.carpenter));
			PlaceCharacter(chr, "rld", PChar.location);
			LAi_SetStayType(chr);
			DialogExit_Self();
		break;

		case "Cabin_Passenger_Talk":
			i = sti(PChar.GenQuest.CabinPassengerNum);
			chr = GetCharacter(GetPassenger(PChar,i));
			PlaceCharacter(chr, "rld", PChar.location);
			LAi_SetStayType(chr);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
// <-- Вызов персонажей by xxxZohanxxx

		case "Cabin_Companion_Talk":
			i = sti(PChar.GenQuest.CabinCompanionNum);
			PlaceCompanionCloneNearMChr(i, false);

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			break;
//navy <--

		// Квест Аскольда, освобождение Аззи.
		case "FreedomAzzy":
			chr = GetCharacter(NPC_GenerateCharacter("Azzy", "Azzy", "man", "man", 22, PIRATE, -1, false));
			chr.name = "демон";
			chr.lastname = "Аззи";
			chr.Dialog.Filename = "Quest\Azzy_dialog.c";
			GiveItem2Character(chr, "blade28");// сабля Моргана
			chr.equip.blade = "blade28";
			chr.rank 	= 100;
			chr.reputation = "0";
			SetSelfSkill(chr, 100, 100, 100, 100, 100);
			SetShipSkill(chr, 100, 100, 100, 100, 100, 100, 100, 100, 100);
			LAi_SetImmortal(chr, true);
			LAi_SetActorType(chr);
			LAi_SetLoginTime(chr, 0.0, 24.0);
			LAi_SetHP(chr, 10000.0, 10000.0);
			chr.greeting = "Gr_Azzy";
			ChangeCharacterAddressGroup(chr, pchar.location, "officers", "reload1_1");
			DoQuestCheckDelay("Ascold_AzzyIsFree", 4.0);
			pchar.questTemp.Azzy = "Azzy_Freedom";
			DialogExit();
		break;

		// Сами хотим колонией управлять.
		case "ColonyBuilding_Hovernor_1":
			dialog.Text = "Или же найти помошника?";
			Link.l1 = "Пожалуй, я и сам"+GetSexPhrase("","а")+" справлюсь.";
			Link.l1.go = "ColonyBuilding_Hovernor_2";
			Link.l2 = "Я передумал"+ GetSexPhrase("","а")+".";
			Link.l2.go = "Exit";
		break;
	        case "ColonyBuilding_Hovernor_2":
		        bQuestDisableMapEnter = true;
		        Log_SetStringToLog("Так как вы стали губернатором, теперь вы не можете покидать пределы острова.");

			PChar.ColonyBuilding.Hovernor = PChar.id;
			DialogExit_Self();
	        break;

		case "ColonyBuilding_Hovernor":
			dialog.Text = "Просмотреть текущее состояние дел колонии " + PChar.ColonyBuilding.ColonyName + ".";
			Link.l1 = "Нужно детально изучить текущее состояние дел.";
			Link.l1.go = "ColonyBuilding_Hovernor_3";
			Link.l2 = "Что-то мне не по душе эта сухопутная жизнь.";
			Link.l2.go = "ColonyBuilding_Hovernor_4";
			Link.l3 = "Ничего не предпринимать.";
			Link.l3.go = "Exit";
		break;

		case "ColonyBuilding_Hovernor_3":
			dialog.Text = "Хм... О каких именно делах я хочу осведомиться?";
			Link.l1 = "Состояния колонии и её финансовые возможности.";
			Link.l1.go = "ColonyBuilding_Hovernor_3_1";
			Link.l2 = "Боевая готовность гарнизона и здоровье жителей.";
			Link.l2.go = "ColonyBuilding_Hovernor_3_2";
			Link.l3 = "Название колонии и внешний вид солдат.";
			Link.l3.go = "ColonyBuilding_Hovernor_3_3";
			Link.l4 = "Ничего не предпринимать.";
			Link.l4.go = "Exit";
		break;

		case "ColonyBuilding_Hovernor_3_1":
			DialogExit_Self();
			LaunchColony();
		break;

		case "ColonyBuilding_Hovernor_3_2":
			DialogExit_Self();
			LaunchColonyLandGuard();
		break;

		case "ColonyBuilding_Hovernor_3_3":
			DialogExit_Self();
			LaunchColonyBuilding(true, false);
		break;

		case "ColonyBuilding_Hovernor_4":
			dialog.Text = "Уверен"+GetSexPhrase("","а")+" ли я, что не хочу управлять своей колонией?";
			Link.l1 = "Да.";
			Link.l1.go = "ColonyBuilding_Hovernor_5";
			Link.l2 = "Нет, я передумал"+GetSexPhrase("","а")+". Моё призвание - губернатор!";
			Link.l2.go = "Exit";
		break;

		case "ColonyBuilding_Hovernor_5":
			PChar.ColonyBuilding.Hovernor = "";
		        bQuestDisableMapEnter = false;
		        Log_SetStringToLog("Перестав быть губернатором вы вновь можете быть свободным капитаном!");
			dialog.Text = "Замечательно! Быть сухопутной крысой не мой удел.";
			Link.l1 = "...";
			Link.l1.go = "exit";
			NextDiag.TempNode = "TalkSelf_Main";
		break;

		// Мекахром смотрим
		case "Dozor_MekaKhrom":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			LaunchMekakhrom();
		break;

		// Линейка Виспер
		case "Whisper_mission":
			dialog.Text = "Координаты совпадают. Кажется, я на месте. Похоже на древние катакомбы - им лет 300, не меньше. Надеюсь, ничего не обвалится, пока я здесь.";
			Link.l1 = "(Перечитать сообщение от заказчика)";
			Link.l1.go = "Whisper_mission_1";
		break;
		case "Whisper_mission_1":
			dialog.Text = "'Дорогая Виспер, тебя приветствует корпорация Omnitech! Мы слышали, что ты лучшая в своем деле, и хотим предложить тебе одну работу. Дело в том, что существует некий предмет - квантовый выпрямитель частиц. Это опасное устройство, в плохих руках оно может принести вред всему человечеству. В данный момент оно и находится в таких руках.'";
			Link.l1.go = "Whisper_mission_2";
		break;
		case "Whisper_mission_2":
			dialog.Text = "'Мы выслали тебе координаты лаборатории безумного ученого, что разработал данное устройство. Он окружил себя отрядом боевых ботов, но для тебя это не должно стать большой помехой. Оплата будет достойной, мы за ценой не постоим. У нас есть информация, что на твое имя записан ипотечный кредит. Считай, что он уже погашен, если возьмешься за это дело. И поторапливайся, устройство может активироваться в любой момент!'";
			Link.l1 = "Что ж, приступим...";
			DeleteAttribute(pchar, "questTemp.Whisper.Entered_Dungeon");
			//AddDialogExitQuest("MainHeroFightModeOn");
			Link.l1.go = "Exit_Special";
		break;
		case "Whisper_Finish":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			Pchar.BaseNation = FRANCE;
			Flag_Change(FRANCE);
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			InterfaceStates.DisFastTravel = false;
			pchar.Whisper.NanoCostume = true;
			pchar.questTemp.WhisperLine = false;
			pchar.Whisper.HatEnabled = false;

			TakeNItems(PChar, "hatWhisper", 1);
			TakeNItems(PChar, "glasses", 1);

			SetQuestHeader("WhisperContraband");
			AddQuestRecord("WhisperContraband", "1");
			pchar.Whisper.Contraband = true;
			pchar.Whisper.FindDesouza = true;
			SetTimerCondition("W_Smuggling", 0, 0, 60, false);

			//initMainCharacterItem();
            mc = GetMainCharacter();

			mc.Ship.Type = GenerateShipExt(SHIP_SOPHIE, true, mc);
			mc.Ship.name="Черная Вдова";
			SetBaseShipData(mc);
			mc.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS12;
			SetCrewQuantityFull(mc);

            SetCharacterGoods(mc,GOOD_FOOD,200);
        	SetCharacterGoods(mc,GOOD_BALLS,300);//2000);
        	SetCharacterGoods(mc,GOOD_MEDICAMENT,300);//2000);
            SetCharacterGoods(mc,GOOD_GRAPES,300);//700);
            SetCharacterGoods(mc,GOOD_KNIPPELS,300);//700);
            SetCharacterGoods(mc,GOOD_BOMBS,300);//1500);
            SetCharacterGoods(mc,GOOD_POWDER,1000);
            SetCharacterGoods(mc,GOOD_PLANKS,50);
            SetCharacterGoods(mc,GOOD_SAILCLOTH,50);
            SetCharacterGoods(mc,GOOD_RUM,40);//600);
            SetCharacterGoods(mc,GOOD_WEAPON,200);//2000);
            SetCharacterGoods(mc,GOOD_EBONY,100);//2000);
            DoReloadCharacterToLocation(Pchar.HeroParam.Location, Pchar.HeroParam.Group, Pchar.HeroParam.Locator);
		break;
		case "WhisperPortrait":
			dialog.Text = "И как же я буду выглядеть сегодня?";
			Link.l1 = "Вариант 1.";
			Link.l1.go = "portrait1";
			Link.l2 = "Вариант 2.";
			Link.l2.go = "portrait2";
			Link.l3 = "Вариант 3.";
			Link.l3.go = "portrait3";
			Link.l4 = "Вариант 4.";
			Link.l4.go = "portrait4";
			Link.l5 = "Вариант 5.";
			Link.l5.go = "portrait5";
			Link.l6 = "Вариант 6.";
			Link.l6.go = "portrait6";
			Link.l7 = "Вариант 7.";
			Link.l7.go = "portrait7";
			Link.l99 = "Пожалуй, оставлю всё как есть.";
			Link.l99.go = "Exit";
		break;
		case "portrait1":
			pchar.faceID = "543";
			dialog.Text = "Гораздо лучше.";
			Link.l1 = "Все, хватит на сегодня.";
			Link.l1.go = "Exit";
		break;
		case "portrait2":
			pchar.faceID = "543_2";
			dialog.Text = "Гораздо лучше.";
			Link.l1 = "Все, хватит на сегодня.";
			Link.l1.go = "Exit";
		break;
		case "portrait3":
			pchar.faceID = "543_3";
			dialog.Text = "Гораздо лучше.";
			Link.l1 = "Все, хватит на сегодня.";
			Link.l1.go = "Exit";
		break;
		case "portrait4":
			pchar.faceID = "543_4";
			dialog.Text = "Гораздо лучше.";
			Link.l1 = "Все, хватит на сегодня.";
			Link.l1.go = "Exit";
		break;
		case "portrait5":
			pchar.faceID = "543_5";
			dialog.Text = "Гораздо лучше.";
			Link.l1 = "Все, хватит на сегодня.";
			Link.l1.go = "Exit";
		break;
		case "portrait6":
			pchar.faceID = "543_6";
			dialog.Text = "Гораздо лучше.";
			Link.l1 = "Все, хватит на сегодня.";
			Link.l1.go = "Exit";
		break;
		case "portrait7":
			pchar.faceID = "543_7";
			dialog.Text = "Гораздо лучше.";
			Link.l1 = "Все, хватит на сегодня.";
			Link.l1.go = "Exit";
		break;
		case "WhisperHatUnequip":
			dialog.Text = "Оставлю ее в каюте, а то голова потеет.";
			ref hatRef = ItemsFromID("hatWhisper");
			string itmGroup = hatRef.groupID;
			RemoveCharacterEquip(pchar, itmGroup);
			ChangeWhisperHeroModel();
			Link.l1 = "С этим разобрались.";
			Link.l1.go = "TalkSelf_Main";
		break;
		case "WhisperHatEquip":
			dialog.Text = "Вот, так гораздо лучше.";
			EquipCharacterByItem(pchar, "hatWhisper");
			ChangeWhisperHeroModel();
			Link.l1 = "С этим разобрались.";
			Link.l1.go = "TalkSelf_Main";
		break;
		case "WhisperGlassesUnequip":
			dialog.Text = "Что-то у меня уже глаза побаливают, пожалуй, сниму очки.";
			ref glassesRef = ItemsFromID("glasses");
			string gItmGroup = glassesRef.groupID;
			RemoveCharacterEquip(pchar, gItmGroup);
			Link.l1 = "С этим разобрались.";
			Link.l1.go = "TalkSelf_Main";
		break;
		case "WhisperGlassesEquip":
			dialog.Text = "Вот, так гораздо лучше.";
			EquipCharacterByItem(pchar, "glasses");
			Link.l1 = "С этим разобрались.";
			Link.l1.go = "TalkSelf_Main";
		break;
		case "PriestSurprise":
			dialog.Text = "Меня сейчас вырвет... Такого я не ждал от посещения борделя. Поиграли, аргххх, в палки-дырки! Это же надо было гея-священника в комнату уединения отправить. Не дай бог ещё слухи пойдут.";
			Link.l1 = "Ну, тут ничего не поделаешь уже, будем жить дальше.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "TalkSelf_Main";
			chrDisableReloadToLocation = false;
		break;

	}
}

void  DialogExit_Self()
{
    DialogExit();
	locCameraSleep(false); //boal
}


void FlagsProcess1(int nation)
{
	// boal 04.04.2004 -->
	bool bTmpBool = true;
	int i, cn;
	ref chref;


	Sea_ClearCheckFlag(); // сбросить всем в море проверку смотрения на флаг.
	DoQuestFunctionDelay("FreeChangeFlagMode", 15.0); // ролик + запас

	switch (nation)
	{
    	case ENGLAND:	EnglandProcess();	break;
    	case FRANCE:	FranceProcess();	break;
    	case SPAIN:		SpainProcess();		break;
    	case PIRATE:	PirateProcess();	break;
    	case HOLLAND:	HollandProcess();	break;
	}
}

void PirateProcess()
{
	pchar.DisableChangeFlagMode = true;
    //DoQuestCheckDelay("pir_flag_rise", 1.0);
    PChar.GenQuest.VideoAVI        = "Pirate";
    PChar.GenQuest.VideoAfterQuest = "pir_flag_rise";

    DoQuestCheckDelay("PostVideo_Start", 0); WasteTime(1);
}

void EnglandProcess()
{
	pchar.DisableChangeFlagMode = true;
    //DoQuestCheckDelay("eng_flag_rise", 1.0);
    PChar.GenQuest.VideoAVI        = "England";
    PChar.GenQuest.VideoAfterQuest = "eng_flag_rise";

    DoQuestCheckDelay("PostVideo_Start", 0); WasteTime(1);
}

void FranceProcess()
{
	pchar.DisableChangeFlagMode = true;
    PChar.GenQuest.VideoAVI        = "France";
    PChar.GenQuest.VideoAfterQuest = "fra_flag_rise";

    DoQuestCheckDelay("PostVideo_Start", 0); WasteTime(1);
}

void SpainProcess()
{
	pchar.DisableChangeFlagMode = true;
    PChar.GenQuest.VideoAVI        = "Spain";
    PChar.GenQuest.VideoAfterQuest = "spa_flag_rise";

    DoQuestCheckDelay("PostVideo_Start", 0); WasteTime(1);
}

void HollandProcess()
{
	pchar.DisableChangeFlagMode = true;
    PChar.GenQuest.VideoAVI        = "Holland";
    PChar.GenQuest.VideoAfterQuest = "hol_flag_rise";

    DoQuestCheckDelay("PostVideo_Start", 0); WasteTime(1);
}

