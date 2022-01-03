// Слухи - диалог по типажам

#define MAX_RUMOURS_ABOUT_OWNERS 7

void ProcessCommonDialogRumors(ref NPChar, aref Link, aref NextDiag);
{
    string strum;
    string srum;
	switch(Dialog.CurrentNode)
	{
	case "rumours_citizen":
		NextDiag.CurrentNode = "rumours";
		//------------- квестовые слухи горожан --------->>>>>>>>
		//жемчужный генератор Шарпа
		if(CheckAttribute(NPChar, "city") && pchar.questTemp.Sharp.City == npchar.city && sti(pchar.questTemp.Sharp.City.rumour))
		{
			pchar.questTemp.Sharp.City.rumour = false; //слух дан
			Dialog.Text = Sharp_choiceAction();
			link.l1 = "Гм, понятно... Еще что нового?";
			link.l1.go = "new question";
			link.l2 = RandPhraseSimple("Спасибо, долж"+ GetSexPhrase("ен","на") +" откланяться.",
									"Всего хорошего.");
			link.l2.go = "exit";
			break;
		}

		//квест шебеки Синяя Птица
		if(CheckAttribute(NPChar, "city") && pchar.questTemp.BlueBird.City == npchar.city && pchar.questTemp.BlueBird == "returnMoney")
		{
			Dialog.Text = BlueBurd_setTradeShip();
			link.l1 = "Ага, понятно... Что еще нового в городе?";
			link.l1.go = "new question";
			link.l2 = RandPhraseSimple("Спасибо, долж"+ GetSexPhrase("ен","на") +" откланяться.",
									"Всего хорошего.");
			link.l2.go = "exit";
			//новый слух в другом городе
			pchar.questTemp.BlueBird.City = GetSharpCity();
			break;
		}

		if (pchar.questTemp.Slavetrader == "canTakeQuest" && rand(4) == 0)
		{
			sld = characterFromId(pchar.questTemp.Slavetrader.UsurerId);
			Dialog.Text = "Говорят, что ростовщик из колонии "+ XI_ConvertString("Colony" + sld.city) +" для какой-то прибыльной работы ищет капитана, не брезгующего замарать руки...";
			link.l1 = "Ага, понятно... Что еще нового в городе?";
			link.l1.go = "new question";
			link.l2 = RandPhraseSimple("Спасибо, долж"+ GetSexPhrase("ен","на") +" откланяться.",
									"Всего хорошего.");
			link.l2.go = "exit";
			break;
		}

		if(pchar.questTemp.Ascold == "canTakeQuest" && rand(3) == 0)
		{
			sld = characterFromId(pchar.questTemp.Ascold.TraderId);
			Dialog.Text = "Говорят, что хозяин магазина из колонии "+ XI_ConvertString("Colony" + sld.city) +" ищет какой-то порошок, большие деньги за него предлагает...";
			link.l1 = "Ага, понятно... Что еще нового в городе?";
			link.l1.go = "new question";
			link.l2 = RandPhraseSimple("Спасибо, долж"+ GetSexPhrase("ен","на") +" откланяться.",
									"Всего хорошего.");
			link.l2.go = "exit";
			break;
		}

		//<<<<<-------- квестовые слухи горожан -----------------
		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 3 )
        srum = SelectRumourEx("citizen", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
        string posrep1, posrep2, answ1, answ2, answ3, answ4;
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" Такие вот дела...", " Возможно, вас это позабавит.");
            posrep2 = " А у вас, капитан, есть какие-нибудь известия для нашей колонии?";
            answ1 = RandPhraseSimple(RandSwear() + "Интересные вещи ты рассказываешь, "+GetFullName(NPChar)+".",
                                 "Тогда расскажи мне еще...");
            answ2 = RandPhraseSimple(RandSwear() + "Это очень интересно! Вот что еще хотел"+ GetSexPhrase("","а") +" спросить...",
                                 "Еще вопрос.");
            answ3 = RandPhraseSimple("Чего только не случается на свете. Мне жаль, но никаких новостей у меня нет. ",
                                 "Я немного спешу, так что как-нибудь в другой раз.");
            answ4 = "";

        }
        else
        {
            posrep1 = " У нас вообще редко что-либо происходит. Но если же произойдет что-то необычное, то все об этом только и говорят.";
            posrep2 = " Так что новостей никаких. Но может " + GetAddress_Form(NPChar) + " капитан что-то знает?";
            answ1 = RandPhraseSimple("Тогда расскажи-ка мне лучше...",
                                 RandSwear() + "Ты ничего не знаешь! Ладно, вот что еще хотел"+ GetSexPhrase("","а") +" спросить...");
            answ2 = RandPhraseSimple("Говоришь, не знаешь, ладно, скажи мне тогда...",
                                 "Да, не сильно ты мне помог"+NPCharSexPhrase(NPChar, "","ла")+", но, может, ты знаешь что-то еще?");
            answ3 = RandPhraseSimple("Не думаю, что знаю что-то что, могло бы вас заинтересовать.",
                                 "Я с удовольствием что-нибудь расскажу, но как-нибудь в другой раз.");
            answ4 = "";

        }
		Dialog.Text = NPCStringReactionRepeat(srum,
                                                srum+posrep1,
                                                srum+posrep2,
                                                RandPhraseSimple("К сожалению, больше я ничего не знаю, позвольте мне идти.",
                                                                    "Вы утомили меня своими расспросами, прошу меня простить, но меня ждут дела."),
                                                "block", 1, npchar, Dialog.CurrentNode);

		//link.l1 = RandPhraseSimple(RandSwear() + "Это очень интересно! Вот что еще хотел"+ GetSexPhrase("","а") +" спросить...",
        //                         "Еще вопрос.");
        link.l1 = HeroStringReactionRepeat(answ1,
                                            answ2,
                                            answ3,
                                            answ4,
                                            npchar, Dialog.CurrentNode);
		link.l1.go = "new question";
		link.l2 = RandPhraseSimple("Спасибо, долж"+ GetSexPhrase("ен","на") +" откланяться.",
                                 "Всего хорошего.");
		link.l2.go = "exit";
	break;

	///////////////////////////////////////////---слухи матросов---////////////////////////////////////////////
	case "rumours_sailor":
		NextDiag.CurrentNode = "rumours";

		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2) srum = SelectRumourEx("sailor", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" Такие вот дела...", " Возможно, вас это позабавит.");
            posrep2 = " А у вас, капитан, есть какие-нибудь известия для нашей колонии?";
            answ1 = RandPhraseSimple(RandSwear() + "Интересные вещи ты рассказываешь, "+GetFullName(NPChar)+".",
"Тогда расскажи мне еще...");
            answ2 = RandPhraseSimple(RandSwear() + "Это очень интересно! Вот что еще хотел"+ GetSexPhrase("","а") +" спросить...","Еще вопрос.");
            answ3 = RandPhraseSimple("Чего только не случается на свете. Мне жаль, но никаких новостей у меня нет. ","Я немного спешу, так что как-нибудь в другой раз.");
            answ4 = "";
        }
        else
        {
            posrep1 = " У нас вообще редко что-либо происходит. Но если же произойдет что-то необычное, то все об этом только и говорят.";
            posrep2 = " Так что новостей никаких. Но может " + GetAddress_Form(NPChar) + " капитан что-то знает?";
            answ1 = RandPhraseSimple("Тогда расскажи-ка мне лучше...",RandSwear() + "Ты ничего не знаешь! Ладно, вот что еще хотел"+ GetSexPhrase("","а") +" спросить...");
            answ2 = RandPhraseSimple("Говоришь, не знаешь, ладно, скажи мне тогда...","Да, не сильно ты мне помог"+NPCharSexPhrase(NPChar, "","ла")+", но, может, ты знаешь что-то еще?");
            answ3 = RandPhraseSimple("Не думаю, что знаю что-то что, могло бы вас заинтересовать.","Я с удовольствием что-нибудь расскажу, но как-нибудь в другой раз.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("К сожалению, больше я ничего не знаю, позвольте мне идти.","Вы утомили меня своими расспросами, прошу меня простить, но меня ждут дела."),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
            answ2,
            answ3,
            answ4,
            npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Спасибо, долж"+ GetSexPhrase("ен","на") +" откланяться.","Всего хорошего.");
		link.l2.go = "exit";
	break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case "rumours_habitue":
		//Black Sails
		if (CheckAttribute(pchar, "BSUrka_Negril") && rand(100) > 60)
		{
			DeleteAttribute(pchar, "BSUrka_Negril");
			dialog.text = "Ну твоё здоровье! Ух, хорош ром. Видел"+ GetSexPhrase("","а") +" бы ты, что пару дней назад тут в бухте творилось! Пиратский бриг, весь простреленный, с парусами как у корабля-призрака дал бой двум испанским фрегатам. И тут, откуда не возьмись, из-за мыса три пирата на корветах! Испанцы дружно на левый галс легли и ну шмалять по батарейно. Один корвет от носа до кормы прострелили, крику было! Аж в форте слыхать! Так вот, простреленный сразу на борт завалился, и тонуть начал, а два других, сами бортовыми, почти в упор разнесли фрегат. А бриг тот, который от испанцев удирал, вдруг осмелел, кинул якорь по левому борту и вокруг цепи разворот резкий сделал, такой, что мачту аж потерял. И давай с борта по пирату стрелять. В общем, потопили они корвет второй совместно с испанцем уцелевшим. Кхе, горло пересохло.";
            link.l1 = "Вот, хлебни ещё. Так что дальше-то было? Интересно рассказываешь! Я прям вижу этот бой наяву!";
			link.l1.go = "BS_NU_11";
			break;
		}
		link.l1 = RandPhraseSimple(RandSwear() + "За это надо выпить еще кружечку...",
                                 "Хорошо. Давай еще по одной.");
		link.l1.go = "sit_3";
		link.l2 = RandPhraseSimple("Спасибо, долж"+ GetSexPhrase("ен","на") +" откланяться.",
                                 "Эх, забористый ром. Ладно, мне уже пора, удачно посидеть.");
		link.l2.go = "exit_sit";
		if (pchar.questTemp.piratesLine == "PL5Hunter_toFirst" && npchar.location == pchar.questTemp.piratesLine.Q5.city_1 + "_tavern")
		{
			dialog.text = "Представляешь, сижу никого не трогаю, вдруг, подлетает этот Эйвори и не спросясь – хрясь мне в морду! Ты, говорит, барыге денег должен?! А потом говорит - обознался. Он обознался, а я без зуба остался! А! Каково?! И, не поверишь, неделя уж прошла, а до сих пор болит. Такая боль! Может, по кружке эля?..";
			link.l1 = "Ну, это можно...";
			link.l1.go = "sit_3";
			AddQuestRecord("Pir_Line_5_Hunter", "3");
			AddQuestUserData("Pir_Line_5_Hunter", "sCity", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_1 + "Gen"));
			pchar.questTemp.piratesLine = "PL5Hunter_toFirstUsurer";
			break;
		}
		if (pchar.questTemp.piratesLine == "PL5Hunter_toSecond" && npchar.location == pchar.questTemp.piratesLine.Q5.city_2 + "_tavern")
		{
			dialog.text = "Подсел ко мне, дней пять назад, мужик, вот прям как ты сейчас. Звали его, дай бог памяти... Джон Эйвори. Рассказал, как он надул местного ростовщика, хе-хе-хе. Так ему и надо, кровососу проклятому, сидит на деньгах и пухнет, а работному человеку и закусить-то нечем...";
			link.l1 = "Да уж, эти ростовщики - народ поганый.";
			link.l1.go = "sit_3";
			AddQuestRecord("Pir_Line_5_Hunter", "5");
			AddQuestUserData("Pir_Line_5_Hunter", "sCity", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_2 + "Gen"));
			pchar.questTemp.piratesLine = "PL5Hunter_toSecondUsurer";
			break;
		}
		if (pchar.questTemp.piratesLine == "PL5Hunter_toThird" && npchar.location == pchar.questTemp.piratesLine.Q5.city_3 + "_tavern")
		{
			dialog.text = "Три дня назад тут такая драка была! Джон Эйвори шулера подколол. Знатно, надо сказать, дядька железякой машет. Вжик, вжик! И нету шулера. Крик поднялся, гам. Но Джон - мужик правильный, всем в таверне выпивку поставил. Уважаю!";
			link.l1 = "О как! Круто...";
			link.l1.go = "sit_3";
			AddQuestRecord("Pir_Line_5_Hunter", "7");
			AddQuestUserData("Pir_Line_5_Hunter", "sCity", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_3 + "Gen"));
			pchar.questTemp.piratesLine = "PPL5Hunter_toThirdUsurer";
			break;
		}
		//-->работорговец
		if (pchar.questTemp.Slavetrader == "FindRatJamaica_H" && npchar.location == "FortOrange_tavern")
        {
			dialog.text = "(поет) Однажды мне встре-етился гамбургский шип. На мачтах - мокрицы и пле-есенный гриб, обшивка гнила-ая, в ракушках корма. Клопов полон ку-убрик, а камбуз - дерьма... Как жизнь, моря"+ GetSexPhrase("к","чка") +", рассказывай. Как оно там, в море?";
            link.l1 = "Да в море все так же, как и всегда - сыро и солоно. Ты вот скажи лучше, не знаешь ли, куда ушел мой приятель, который тут комнату снимал недавно? Франсуа Гонтьер его зовут.";
            link.l1.go = "Jamaica_ratH_1";
			break;
        }
		if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_H" && npchar.location == "Villemstad_tavern")
        {
			dialog.text = "(поет) Я бла-агода-арен виски за свой багро-овый нос, и по-о его-о совету пальто в закла-ад отнес... Эх, наливай, моря"+ GetSexPhrase("к","чка") +"! Я только вчера из рейса, поэтому еще немного не в себе.";
            link.l1 = "Угощайся, приятель! Ну, и как там в море, что интересного видел?";
            link.l1.go = "EscapeSlave_Villemstad_H1";
			break;
        }
		//<--работорговец

		//ОЗГ, Крыса
		if(CheckAttribute(pchar, "questTemp.Headhunter"))
		{
    		if (pchar.questTemp.Headhunter == "Rat_Tavern" && npchar.location == pchar.questTemp.Headhunter.Ratrumcity + "_tavern")
            {
    			dialog.text = "(поет) Летучий Голландец, Летучий Голландец, мчит по неведомым морям... Эх, моря"+ GetSexPhrase("к","чка") +", выпьем!";
                link.l1 = "Послушай, мне говорили, что тут матросы с одного судна, 'Аделаида' называется, устроили погром по пьяни...";
                link.l1.go = "Rat_Tavern_1";
				break;
            }
		}
		//<--ОЗГ, Крыса

		if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	    {
			dialog.text = "Эх, " + GetAddress_Form(pchar) + " что за жизнь нынче пошла... Ничего святого в людишках не осталось!";
			link.l1 = "О чём это ты, приятель?";
			link.l1.go = "Alcogol_GenQuest_Church_2_1";
			break;
		}

		if(CheckAttribute(PChar, "HellSpawn.SeekRebirth"))
	    {
			//получим пещеру для чистки
			pchar.quest.HellSpawn.locationId = "DeckWithReefs"; //Id целевой пещеры
			sld = &locations[FindLocation(pchar.quest.HellSpawn.locationId)];
			npchar.quest.HellSpawn.label = GetConvertStr(sld.id.label, "LocLables.txt"); //тип подземелья для диалогов

			dialog.text = "Эх, " + GetAddress_Form(pchar) + " что за жизнь нынче пошла... Слыхал я о страшных вещах, что творятся на рифе Скелета. Говорят, в местной бухте нежить собирается для какого-то ритуала перерождения.";
			DeleteAttribute(PChar, "HellSpawn.SeekRebirth");
			SaveCurrentQuestDateParam("pchar.questTemp.HellSpawn.Rit");

			pchar.quest.HellSpawnRitual.win_condition.l1 = "location";
			pchar.quest.HellSpawnRitual.win_condition.l1.location = pchar.quest.HellSpawn.locationId;
			pchar.quest.HellSpawnRitual.function = "HellSpawnRitual";
			AddQuestRecordInfo("Important_rumours", "1");
			AddQuestUserData("Important_rumours", "sSex", GetSexPhrase("","а"));
			break;
		}

		if(!CheckAttribute(pchar,"SalasarEventKnow") && rand(30)==0)
		{
			dialog.text = "Ходят слухи, что каждый год 3 марта в 3 часа ночи на рифе Скелета в ущелье Дьявола на руинах домика смотрителя кладбища разгорается особенно яркое и пугающее сияние, от которого веет ужасом и безнадёжностью. Хотелось бы самому посмотреть, да слишком уж боязно...";
			Log_Info("Это стоит запомнить. Значит... 3 марта, 3 часа ночи и каждый год.");
			pchar.SalasarEventKnow = true;
			AddQuestRecordInfo("Important_rumours", "2");
			AddQuestUserData("Important_rumours", "sSex", GetSexPhrase("","а"));
			break;
		}
		if(CheckAttribute(pchar,"GiantEvilSkeleton") && rand(20)==0 && !CheckAttribute(pchar,"MalteseInfo"))
		{
			 if (startHeroType != 2 && startHeroType != 7 && pchar.sex != "skeleton")
			 {
				dialog.text = "Ходят слухи, что Испанская инквизиция собирает информацию о рифе Скелета. С какой целью - неизвестно, но любому, кто знает хоть что-то, обещано вознаграждение...";
				Log_Info("Это стоит запомнить. Испанская инквизиция и риф Скелета.");
				pchar.MalteseInfo = true;
				AddQuestRecordInfo("Important_rumours", "3");
				AddQuestUserData("Important_rumours", "sSex", GetSexPhrase("","а"));
				break;
			 }
		}
		if(!CheckAttribute(pchar,"BlackBeardSpawn") && sti(pchar.rank)>=20)
		{
			AddQuestRecordInfo("Important_rumours", "4");
			AddQuestUserData("Important_rumours", "sSex", GetSexPhrase("","а"));
			dialog.text = "Говорят, что на архипелаге впервые за годы увидели корабль самого Чёрной Бороды. По слухам, он ищет самого удачливого пирата на архипелаге для каких-то странных дел.";
			Log_Info("Это стоит запомнить. Эдвард Тич появился на архипелаге.");
			pchar.BlackBeardSpawn = true;

			sld = GetCharacter(NPC_GenerateCharacter("BlackBeardNPC", "PGG_Tich_0", "man", "man", 60, PIRATE, -1, true));
			FantomMakeCoolFighter(sld, 60, 100, 100, "blackbeard_sword_baron", "howdah", 100);
			sld.items.spyglass3 = 0;
			sld.items.spyglass5 = 1;
			EquipCharacterbyItem(sld,"spyglass5");
			sld.name = "Эдвард";
			sld.lastname = "(Чёрная Борода) Тич";
			sld.dialog.filename   = "Quest\BlackBeard.c";
			sld.dialog.currentnode   = "Greetings";
			sld.greeting = "";
			sld.AlwaysReload = true;//перезарядка независимо от Дозарядки
			sld.items.GunEchin = 30;
			LAi_SetCharacterUseBullet(sld,"GunEchin");//зарядить патрики покруче
			FantomMakeCoolSailor(sld, SHIP_FRIGATEQUEEN, "Месть Королевы Анны", CANNON_TYPE_CANNON_LBS36, 90, 90, 90);
			GiveItem2Character(sld, "cirass5");
			EquipCharacterbyItem(sld,"cirass5");

			DeleteAttribute(sld, "DontClearDead");
			DeleteAttribute(sld, "AboardToFinalDeck");
			DeleteAttribute(sld, "SinkTenPercent");
			DeleteAttribute(sld, "DontRansackCaptain");
			sld.AlwaysFriend = true;
			sld.AlwaysSandbankManeuver = true;
			sld.DontRansackCaptain = true; //не сдаваться

			SelAllPerksToNotPCHAR(sld);
			SetCharacterPerk(sld, "Energaiser"); // скрытый перк дает 1.5 к приросту энергии, дается ГГ и боссам уровней
			SetCharacterPerk(sld, "AgileMan"); // ловкач
			sld.SuperShooter  = true;
			SetSPECIAL(sld, 10,10,10,10,10,10,10); // SPECIAL (Сила, Восприятие, Выносливость, Лидерство, Обучаемость, Реакция, Удача)
			SetSelfSkill(sld, 100, 100, 100, 100, 100); //лёгкое, среднее, тяжёлое, пистолет, удача
			SetShipSkill(sld, 100, 100, 100, 100, 100, 100, 100, 100, 100); // лидерство, торговля, точность, пушки, навигация, ремонт, абордаж, защита, скрытность
			LAi_SetHP(sld,1500,1500);
			SetCharacterPerk(sld, "Grunt"); //рубака
			AddBonusEnergyToCharacter(sld, 50);
			TakeNItems(sld,"potion2",10);

			//в морскую группу кэпа
			sGroup = "BlackBeardGroup";
			Group_FindOrCreateGroup(sGroup);
			Group_AddCharacter(sGroup, sld.id);
			Group_SetGroupCommander(sGroup, sld.id);
			Group_SetType("BlackBeardGroup", "pirate");
			SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);
			SetRandGeraldSail(sld, sti(sld.Nation));
			sld.quest = "InMap"; //личный флаг искомого кэпа
			sld.city = "LaVega"; //определим колонию
			sld.cityShore = GetIslandRandomShoreId(GetArealByCityName(sld.city));
			sld.quest.targetCity = GetRandomPirateCity(); //определим колонию, в бухту которой он придет
			sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
			Log_TestInfo("Фрегат Месть Королевы Анны вышел из: " + sld.city + " и направился в: " + sld.quest.targetShore);
			//==> на карту
			sld.mapEnc.type = "trade";
			//выбор типа кораблика на карте
			sld.mapEnc.worldMapShip = "Tich_MKA"; // LEO: Сюда надо заюзать модельку МКА на глобалку, персональную.
			sld.mapEnc.Name = "Фрегат 'Месть Королевы Анны'";
			int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+3; //дней доехать даем с запасом
			Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);
			//заносим Id кэпа в базу нпс-кэпов
			sTemp = sld.id;
			NullCharacter.capitainBase.(sTemp).quest = "BlackBeard"; //идентификатор квеста
			NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
			NullCharacter.capitainBase.(sTemp).Tilte1 = "BlackBeard"; //заголовок квестбука
			NullCharacter.capitainBase.(sTemp).Tilte2 = "BlackBeard"; //имя квеста в квестбуке
			NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 3;
			NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
			NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
			NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
			break;
		}

		if (!CheckAttribute(pchar, "PGG_killed_known")) pchar.PGG_killed_known = 0;
		if (CheckAttribute(pchar, "PGG_killed") && sti(pchar.PGG_killed) > 4 && pchar.PGG_killed != pchar.PGG_killed_known)
		{
			pchar.PGG_killed_known = pchar.PGG_killed;
			dialog.text = "Говорят, что в наших водах "+GetSexPhrase("завелся охотник на честных корсаров, ","завелась охотница на честных корсаров, ") + GetFullName(pchar)+GetSexPhrase(" его "," её") + " звать. Число душ, отправленных на тот свет этой личностью уже достигло " + pchar.PGG_killed + ". Все уважаемые в этих местах люди. Брр... Что-то меня мутить начинает. То ли из-за рома, то ли всей этой истории...";
			break;
		}
		//Титаник
		if (CheckAttribute(pchar, "TitanicRumour") && rand(100) > 80)
		{
			AddQuestRecord("WhisperTitanic", 6);
			AddQuestUserData("WhisperTitanic", "sCity", XI_ConvertString("Colony" + pchar.TitanicCity));
			DeleteAttribute(pchar, "TitanicRumour");
			dialog.text = "Вот это ром! Кстати, капитан, не советую вам соваться в " + XI_ConvertString("Colony" + pchar.TitanicCity) + ". Там сейчас вовсю разбойничает английская плавучая крепость.'Титаник' - её название, кажется...";
			break;
		}
		//BlackThorn викинг
		if (CheckAttribute(pchar, "questTemp.pirateVikingQuest") && rand(100) > 60)
		{
			if (CheckAttribute(pchar, "LastHearedViking") && pchar.LastHearedViking != npchar.city)
			{
				if (pchar.questTemp.pirateVikingQuest == "4")
				{
					if(ShipsTypes[sti(RealShips[sti(pchar.Ship.Type)].BaseType)].Type.Merchant == true && GetCompanionQuantity(pchar) == 1)
					{
						if (GetSquadronGoods(Pchar, GOOD_EBONY) >= 600 || GetSquadronGoods(Pchar, GOOD_SILK) >= 1000 || GetSquadronGoods(Pchar, GOOD_SILVER) >= 400)
						{
							dialog.text = "Вижу, вы - бывалый купец, капитан, немало передряг повидали. Но все же, хоть я сам не моряк, но дал бы вам совет - не выходите сегодня в море. В окрестных водах видели пиратскую щебеку, которая как раз охотится на людей вроде вас.";
							link.l1 = "Ха! Напугал ежа иголкой. Да если мне эта щебека попадется, то считай она уже на дне. Ладно, бывай.";
							link.l1.go = "exit_sit";
							AddQuestRecord("pirateVikingQuest", "6");
							//Можно будет вызвать повторно, если еще не убили
							//pchar.questTemp.pirateVikingQuest = "5";
							pchar.LastHearedViking = npchar.city;

							if (MOD_SKILL_ENEMY_RATE == 10 && bHardAnimations) sld = GetCharacter(NPC_GenerateCharacter("pirateVikingQuest_Captain", "OZG_3", "man", "man_fast", 80, PIRATE, -1, true)); // LEO: Превозмогаторам - страдать 01.12.2021
							else sld = GetCharacter(NPC_GenerateCharacter("pirateVikingQuest_Captain", "OZG_3", "man", "man", 80, PIRATE, -1, true));
							sld.mapEnc.worldMapShip = "quest_ship";
							sld.mapEnc.Name = "щебека 'Драккар'";
							sld.mapEnc.type = "war";
							FantomMakeCoolFighter(sld, 80, 100, 100, "topor_viking", "pistol3", 600);
							//FantomMakeCoolSailor(sld, SHIP_XEBEKVT, "Драккар", CANNON_TYPE_CANNON_LBS24, 100, 100, 100);
							FantomMakeCoolestSailor(sld, SHIP_XEBEKVT, "Драккар", CANNON_TYPE_CANNON_LBS24, 100, 100, 100);

							sld.name 	= "Рагнар";
							sld.lastname = "Лотброк";
							sld.AlwaysSandbankManeuver = true;
							sld.DontRansackCaptain = true;
							sld.AnalizeShips = true;
							if (bHardBoss) sld.AlwaysReload = true;//перезарядка независимо от Дозарядки
							SetCharacterPerk(sld, "MusketsShoot");

							sld.ship.Crew.Morale = 100;
							ChangeCrewExp(sld, "Sailors", 100);
							ChangeCrewExp(sld, "Cannoners", 100);
							ChangeCrewExp(sld, "Soldiers", 100);

							GiveItem2Character(sld, "cirass3");
							EquipCharacterbyItem(sld, "cirass3");
							GiveItem2Character(sld, "jewelry9");
							SetCharacterPerk(sld, "Energaiser"); // скрытый перк дает 1.5 к приросту энергии, дается ГГ и боссам уровней
							TakeNItems(sld, "Food5", 30);
							TakeNItems(sld, "potion2", 15);
							sld.SaveItemsForDead = true;
							sld.DontClearDead = true;

							LAi_group_MoveCharacter(sld, "Vikings");
							string  sGroup = "Sea_" + sld.id;
							group_DeleteGroup(sGroup);
							Group_FindOrCreateGroup(sGroup);
							Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
							Group_LockTask(sGroup);
							Group_AddCharacter(sGroup, sld.id);
							Group_SetGroupCommander(sGroup, sld.id);
							Map_CreateWarrior("", sld.id, 8);
							SetFunctionNPCDeathCondition("PirateVikingQuest_Captain_Is_Dead", sld.id, false);
							break;
						}
						else
						{
							dialog.text = "Говорят, в окрестных водах плавает пиратская щебека. Но вам, капитан, бояться нечего. Хоть у вас и торговый корабль, они вряд ли захотят тратить свои силы на такой скудный груз.";
						}
					}
					else
					{
						dialog.text = "Говорят, в окрестных водах плавает пиратская щебека. Но вам, капитан, бояться нечего. Они охотятся только на одинокие торговые корабли.";
					}
				}
				if (pchar.questTemp.pirateVikingQuest == "3")
				{
					dialog.text = "Говорят, местный хозяин магазина собирается судиться с одним незадачливым капитаном. Тот зафрахтовал свой корабль для доставки крупной партии китайского шёлка, однако пришёл с пустым трюмом! Сами понимаете, деньги тут немаленькие замешаны. Обвиняемый капитан говорит, что его ограбила какая-то щебека, капитан которой - голубоглазый блондин. Вся команда это подтверждает. Даже повреждения на корабле имеются после боя, несколько вмятин от ядер, испорченная остнастка, но хозяин магазина всё равно не верит. Каждый раз повторяет, что доказательства сфабрикованы, а капитан с командой лгут. Но я вот думаю, с чего бы ему лгать? Он уже не один десяток раз возил фрахты, причем с куда более ценными грузами. Если бы захотел украсть - давно уже так поступил бы.";
					AddQuestRecord("pirateVikingQuest", "4");
					AddQuestRecord("pirateVikingQuest", "5");
					pchar.questTemp.pirateVikingQuest = "4";
					pchar.LastHearedViking = npchar.city;
					break;
				}
				if (pchar.questTemp.pirateVikingQuest == "2")
				{
					dialog.text = "Не советую вам выходить в море, капитан. Обычно там только пираты покою не давали, а сейчас завелись ещё и самые настоящие викинги! Один купец до последнего не хотел расставаться с серебром в своем трюме, наивно надеясь, что сможет дать им отпор. Он заплатил жизнями своей команды. С обломками его корабля, в местную бухту недавно прибило бедолагу, матроса, который чудом выжил. Он и рассказал мне эту историю. Говорит, лично видел этих зверей. Здоровенные, злющие и на языке непонятном говорят!";
					AddQuestRecord("pirateVikingQuest", "3");
					pchar.questTemp.pirateVikingQuest = "3";
					pchar.LastHearedViking = npchar.city;
					break;
				}
				if (pchar.questTemp.pirateVikingQuest == "1")
				{
					dialog.text = "Слыхали, капитан? В наш порт недавно вернулся купец, что обычно приторговывает чёрным деревом. Вот только в этот раз он пришел с пустым трюмом. Говорят, в море его перехватила щебека под названием 'Драккар'. Капитан благоразумно поднял белый флаг и его пощадили, однако обобрали до нитки. Он теперь полностью разорён и больше не может продолжать бизнес. В Европу собирается вернуться, к родственникам.";
					AddQuestRecord("pirateVikingQuest", "2");
					pchar.questTemp.pirateVikingQuest = "2";
					pchar.LastHearedViking = npchar.city;
					break;
				}
			}
		}
		Dialog.Text = LinkRandPhrase("Ну... И-ик! ","Эх, какой ром! ","Н-да... ")+SelectRumourEx("habitue", NPChar);
	break;
//Black Sails
		case "BS_NU_11":
            dialog.text = "Ух. Хорошо пошло, благодарствуйте. Так вот. Пират, на уцелевшем корвете, смекнул, что дело плохо, стал по ветру и на всех парусах за горизонт удрал! А на бриге, цепь якорную отрубили и бортом на фрегат навалились. На абордаж, стало быть, пошли. И одолели - таки испанцев! Фрегат черный флаг поднял, дал залп по бригу потрёпанному и ушел, куда - то на север. Такая баталия была, хоть на картину! Обломками всё побережье усыпано.";
            link.l1 = "Спасибо за рассказ. Тебе бы книги писать с таким талантом!";
			link.l1.go = "exit_sit";

			BSBons_SeaBattle(true);
			AddQuestRecord("BSUrka", "3");
			PChar.quest.BSUrka_Pirates_town.win_condition.l1 = "location";
			PChar.quest.BSUrka_Pirates_town.win_condition.l1.location = "Pirates_town";
			PChar.quest.BSUrka_Pirates_town.function = "BSUrka_Pirates_town";
		break;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_trader":
            if (!CheckAttribute(NPChar, "quest.repeat.rumours_trader") || NPChar.quest.repeat.rumours_trader!= 3 )
            strum = SelectRumourEx("trader", NPChar);
            else strum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
			Dialog.Text =  NPCStringReactionRepeat(strum, strum+" Да. Больше ничего не припомню.",
                                                   strum+" А сейчас мне нужно вернуться к делам.",
                                                    RandPhraseSimple("Я ведь уже сказал, что у меня нет времени на пустую болтовню!",
                                                                        "Я занятой человек и мне некогда обсуждать всякие сплетни!"),
                                                                         "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(pcharrepphrase(RandSwear() + "Это очень интересно! Но давай к делу","Благодарю, тогда вот еще какое дело."),
                                                pcharrepphrase(""+ GetSexPhrase("Чтоб я сдох","Разрази меня гром") +"! Складно врешь. Но у меня есть еще вопрос.",
                                                                "Так не будем больше терять драгоценное время и перейдем к делам."),
                                                pcharrepphrase(RandSwear() +" Еще одно дельце, и я уйду.","Вы правы, время - деньги."),
                                                pcharrepphrase("Только и думаешь, что о своей выгоде. Ладно, не кипятись.",
                                                                "Прошу простить меня. Перейдем к делу."),
                                                npchar, Dialog.CurrentNode);

			link.l1.go = "business";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("Пока, старый пропойца.",
													               "Всего доброго, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"."),
													pcharrepphrase("Каррамба! Никуда не уходи. Я еще зайду.",
													               "Приятно было вас видеть, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"! До свидания!")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Отдать швартовы!",
													               "До свидания, милейший."),
													pcharrepphrase("Эй! Ты что там прячешь? Ром? Нет!?! Ну ладно, пойду горло промочу.",
													               "Прошу меня извинить, у меня срочные дела в городе.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Хех! Еще увидимся!",
													               "Мне надо идти. Прощайте, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!"),
													pcharrepphrase("И не смей мне перечить! Недосуг мне тут с тобой спорить!",
													               "Пожалуй, стоит проверить, как дела на корабле. Прощайте, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Что с тобой, старина? Это же я - " +GetFullName(pchar)+ "! Проспись, я потом зайду.",
													               "Боюсь, ваша печень прикончит вас раньше, чем я еще раз зайду сюда."),
													pcharrepphrase("Считай свои пиастры, пройдоха! Я еще зайду.",
													               "Рад"+ GetSexPhrase("","а") +" был"+ GetSexPhrase("","а") +" вас видеть, " + GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),
											  npchar, Dialog.CurrentNode);
			link.l2.go = "Exit";
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_capitan":
			Dialog.Text = SelectRumourEx("capitan", NPChar);
			Link.l1 = RandPhraseSimple(RandSwear() + "Это очень интересно! Вот что еще хотел"+ GetSexPhrase("","а") +" спросить...",
                                     "Еще вопрос.");
			Link.l1.go = "quests";
			Link.l2 = RandPhraseSimple("Спасибо, долж"+ GetSexPhrase("ен","на") +" откланяться.",
                                     "Всего хорошего");
			Link.l2.go = "exit";
			NextDiag.TempNode = "quests";
            NPChar.talk_date =  lastspeakdate();
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_tavern":  // homo 03/08/06

                 Dialog.Text = NPCStringReactionRepeat(LinkRandPhrase("Сведения стоят денег. За скромные 1000 золотых я расскажу все, что знаю.",
                "Что-то я запамятовал. Но, возможно, 1000 монет освежат мою память.",
                "Я готов рассказать все, что знаю. Но не бесплатно - 1000 золотых, на меньшее я не согласен."),
                "Больше мне нечего добавить. А теперь прошу меня извинить, но дела не ждут.",
                "", "", "block", 1, npchar, Dialog.CurrentNode);

    			link.l1 = HeroStringReactionRepeat(RandPhraseSimple(RandSwear() + "Платить за пустую болтовню? Нет уж, поищи кого-нибудь другого.",
                                         "За такие деньги я сам"+ GetSexPhrase("","а") +" все узнаю."), "Давай поговорим о чем-нибудь другом.", "Давай поговорим о чем-нибудь другом.", "Давай поговорим о чем-нибудь другом.", npchar, Dialog.CurrentNode);
                link.l1.go = HeroStringReactionRepeat("rumours_tavern_no", "first time", "first time", "first time", npchar, Dialog.CurrentNode);//"rumours_tavern_no";
                NextDiag.CurrentNode = NextDiag.TempNode;
    			if (makeint(pchar.money) >= 1000 )
    			{
    				link.l2 = HeroStringReactionRepeat(RandPhraseSimple("Ты их получишь, если я получу действительно ценные сведения.", "Я заплачу, но только при условии, что ты мне расскажешь действительно что-то важное."),
                     "", "", "" , npchar, Dialog.CurrentNode);
    				link.l2.go = HeroStringReactionRepeat("rumours_tavern_yes", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
    			}
    			else
    			{
                    link.l2 =  HeroStringReactionRepeat("У меня нет такой суммы.", "", "", "", npchar, Dialog.CurrentNode);
    				link.l2.go = HeroStringReactionRepeat("rumours_tavern_no", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
    			}

		break;

		case "rumours_tavern_yes":

			//------------- квестовые слухи тавернщика --------->>>>>>>>
			//пиратка, квест №3
			if (pchar.questTemp.piratesLine == "KillLoy_toCumana")
			{
				Dialog.Text =  "В последнее время стали часто пропадать корабли, причем, что странно, пропадают только курьерские люггеры и шлюпы. Поговаривают о появлении в водах Куманы какого-то брига... Так что будьте осторожны!";
				link.l1 = "Только курьерские люггеры, говоришь? Очень интересно... А больше ничего примечательного не знаешь?";
				link.l1.go = "rumours_tavern";
				AddQuestRecord("Pir_Line_3_KillLoy", "14");
				AddQuestUserData("Pir_Line_3_KillLoy", "sSex", GetSexPhrase("","а"));
				pchar.questTemp.piratesLine = "KillLoy_toCumana_2";
				break;
			}
			//ОЗГ, Крыса на Тортуге
			if(CheckAttribute(pchar, "questTemp.Headhunter"))
			{
	    		if (pchar.questTemp.Headhunter == "Rat_tortuga" && npchar.location == "Tortuga_tavern")
	    		{
	    			Dialog.Text =  "Говорят, капитан и собственник пинаса 'Аделаида' заключил какую-то сделку с д'Ожероном и отчаливает буквально на днях. Вся его команда целую неделю без продыха безобразничала в борделе и у меня в таверне. Слава Богу, уберутся наконец, быстрее бы... А сам капитан сейчас у меня отдыхает - видишь, вон сидит, за круглым столиком. Видный моряк...";
	    			link.l1 = "Очень интересно... А больше ничего примечательного не знаешь?";
	    			link.l1.go = "rumours_tavern";
	    			pchar.quest.Headhunter_PinasseTortugaOver.over = "yes";
	    			AddQuestRecord("Headhunt", "17");
	    			pchar.questTemp.Headhunter = "Rat_officer";
	    			FreeSitLocator("Tortuga_tavern", "sit1");
	    			SetFunctionTimerCondition("Headhunter_RatOfficerOver", 0, 0, 3, false);//таймер
	    			break;
	    		}
			}
			//ОЗГ, Крыса на Тортуге
			//<<<<<-------- квестовые слухи тавернщика -----------------

            string RumText = SelectRumourEx("tavern", NPChar); //fix
            //SelectRumour();

		    if(!RumourHasInformation(RumText))
            {
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; //fix
                link.l1 = RandPhraseSimple("Я не стану платить за пустые сплетни, прощай.", "Твои сведения не стоят и ломаного гроша - ты ничего не получишь.");

			    link.l1.go = "Exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
			  //  link.l2 = LinkRandPhrase("Спасибо, долж"+ GetSexPhrase("ен","на") +" откланяться.",
              //                       "Всего хорошего","Спасибо, мне пора. До свидания.");
			  //  link.l2.go = "Exit";
            }
            else
            {

                AddMoneyToCharacter(pchar, -1000);

                Dialog.Text = RumText;

    			link.l1 = RandPhraseSimple("Благодарю, вот твое золото. А больше ничего не припомнишь?", "Хорошо, ты заслужил свои деньги - держи. Есть что-нибудь еще?");
                //RandPhraseSimple(RandSwear() + "Это очень интересно! Вот что еще хотел"+ GetSexPhrase("","а") +" спросить...",
                //                         "Еще вопрос.");

    			link.l1.go = "rumours_tavern";
    			NextDiag.CurrentNode = NextDiag.TempNode;
    			//link.l2 = LinkRandPhrase("Спасибо, долж"+ GetSexPhrase("ен","на") +" откланяться.",
              //                           "Всего хорошего","Спасибо, ты мне очень помог. До свидания.");
    		//	link.l2.go = "Exit";
            }

		break;

		case "rumours_tavern_no":
			Dialog.Text = "Поймите меня правильно, мне нужно кормить семью.";
            link.l1 = "Давай поговорим о чем-нибудь другом.";
			link.l1.go = "first time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			link.l2 = LinkRandPhrase("Спасибо, долж"+ GetSexPhrase("ен","на") +" откланяться.",
                                     "Всего хорошего","До свидания.");
			link.l2.go = "Exit";
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_poor":
			if (!CheckAttribute(NPChar, "quest.repeat.rumours_poor") || NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("poor", NPChar);
				Link.l1 = RandPhraseSimple(RandSwear() + "Да, это интересно. Имеется еще вопрос...",
										"Хм, вот что еще хотел"+ GetSexPhrase("","а") +" спросить...");
				Link.l1.go = "rumours_poor_2";
				Link.l2 = RandPhraseSimple("Ну, прощай, барыга.",
										"Всего хорошего, приятель.");
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else
			{
				Dialog.Text = RandPhraseSimple("Не о чем говорить, все уже выболтал, что знал.",
					"Больше я ничего не слышал, извините...");
				Link.l1 = RandPhraseSimple("Понятно. Ну что же, всего хорошего.",
										"Ясно. Ну, бывай, приятель...");
				Link.l1.go = "exit";
			}
            NPChar.talk_date = lastspeakdate();
		break;
        case "rumours_poor_2":
			if (NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("poor", NPChar);
				Link.l1 = RandPhraseSimple(RandSwear() + "Да, это интересно. Имеется еще вопрос...",
										"Хм, вот что еще хотел"+ GetSexPhrase("","а") +" спросить...");
				Link.l1.go = "rumours_poor";
				Link.l2 = RandPhraseSimple("Ну, прощай, барыга.",
										"Всего хорошего, приятель.");
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else
			{
				Dialog.Text = RandPhraseSimple("Не о чем говорить, все уже выболтал, что знал.",
					"Больше я ничего не слышал, извините...");
				Link.l1 = RandPhraseSimple("Понятно. Ну что же, всего хорошего.",
										"Ясно. Ну, бывай, приятель...");
				Link.l1.go = "exit";
			}
			NPChar.talk_date = lastspeakdate();
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_LSC":
			if (CheckNPCQuestDate(NPChar, "quest.repeat.rumours"))
			{
				Dialog.Text = SelectRumourExSpecial("LSC", NPChar);
				Link.l1 = RandPhraseSimple("Понятно...",
										"Ясно...");
				Link.l1.go = "exit";
				SetNPCQuestDate(NPChar, "quest.repeat.rumours");
			}
			else
			{
				Dialog.Text = NPCharSexPhrase(npchar, RandPhraseSimple("Не о чем говорить, все уже выболтал, что знал.", "Больше я ничего не слышал, прошу прощения..."),
					RandPhraseSimple("Простите, но я вам уже все выболтала.", "Больше я ничего не слышала, извините..."));
				Link.l1 = RandPhraseSimple("Я понял"+ GetSexPhrase("","а") +".", "Ну, всего хорошего.");
				Link.l1.go = "exit";
			}
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Кредитный генератор Loan
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "LoanForAll": //пересылка в финансы для всех
			dialog.text = LinkRandPhrase("Финансы? Хм, говорите, вас слушаю.", "Финансовые вопросы - это всегда интересно. Говорите, я слушаю вас.", "Что же, давайте поговорим о финансах.");
            if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
            {
                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
                {
                    dialog.text = LinkRandPhrase("А вы уверены, что обратились по адресу, " + GetAddress_Form(NPChar) + "? Мое имя " + GetFullName(npchar) + ". Чем могу служить?",
                             "По финансам ко мне, " + GetAddress_Form(NPChar) + "?! Я " + GetFullName(npchar) + ". А что за дело у вас?",
                             "Я вас слушаю, " + GetAddress_Form(NPChar) + ". Что вы хотели? Кстати, меня зовут " + GetFullName(npchar) + ".");
                    link.l1 = NPCharRepPhrase(pchar, "Я от ростовщика, должник! Деньги на бочку!", "У меня к вам щекотливый вопрос по вашему долгу, " + GetAddress_FormToNPC(NPChar) + ".");
                    link.l1.go = "LoanFindCitizen_1";
				    NPChar.quest.LoanFindCitizenType = rand(2); // три типа
                    break;
                }
            }
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
            {
                link.l2 = "Я привез"+ GetSexPhrase("","ла") +" ваш кредит.";
                link.l2.go = "TakeChest_2";
            }
			link.l9 = RandPhraseSimple("М-м-м, я, видимо, ошиб"+ GetSexPhrase("ся","лась") +". Никаких финансовых дел я с вами не веду.", "Простите, никаких финансовых вопросов у меня к вам нет.");
			link.l9.go = "exit";
		break;
		// вернуть долг ростовщику
		case "LoanFindCitizen_1":
            switch (sti(pchar.GenQuest.Loan.FindCitizenChance1))
            {
                case 0 :
                    dialog.text = "Да, точно. Я как раз собирался ему все отдать.";
        			Link.l1 = "Ну что же, очень хорошо! Итого с тебя " + FindRussianMoneyString(makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent))) + ".";
        			Link.l1.go = "LoanFindCitizenType_0";
        			Link.l2 = "Замечательно, вот и отнеси все сам!";
        			Link.l2.go = "exit";
                break;

                case 1 :
                    dialog.text = "Нет! Ничего я не отдам! А будете приставать, стражу позову.";
                    Link.l1 = "Ничего не знаю, с тебя " + FindRussianMoneyString(makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent))) + ". А то можно поговорить и по-другому.";
        			Link.l1.go = "LoanFindCitizenType_1";
        			Link.l2 = "Ах ты, негодяй! Ну ничего, Земля круглая, свидимся еще...";
        			Link.l2.go = "LoanFindCitizenType_1_1";
                break;

                case 2 :
                    dialog.text = "К сожалению, у меня нет всей суммы.";
                    Link.l1 = "Ничего не знаю, с тебя " + FindRussianMoneyString(makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent))) + ". А то можно поговорить и по-другому.";
        			Link.l1.go = "LoanFindCitizen_1_1";
        			Link.l2 = "А сколько есть?";
        			Link.l2.go = "LoanFindCitizenType_2";
        			//NPChar.quest.LoanFindCitizenType = rand(1);// первые 2 типа
                break;
			}
		break;

		case "LoanFindCitizen_1_1":
            switch (sti(pchar.GenQuest.Loan.FindCitizenChance2))
            {
                case 0 :
                    dialog.text = "Да, точно. Я как раз собирался ему все отдать.";
        			Link.l1 = "Ну что же, очень хорошо! Итого с тебя " + FindRussianMoneyString(makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent))) + ".";
        			Link.l1.go = "LoanFindCitizenType_0";
        			Link.l2 = "Замечательно, вот и отнеси все сам!";
        			Link.l2.go = "exit";
                break;

                case 1 :
                    dialog.text = "Нет! Ничего я не отдам! А будете приставать, стражу позову.";
                    Link.l1 = "Ничего не знаю, с тебя " + FindRussianMoneyString(makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent))) + ". А то можно поговорить и по-другому.";
        			Link.l1.go = "LoanFindCitizenType_1";
        			Link.l2 = "Ах ты, негодяй! Ну ничего, Земля круглая, свидимся еще...";
        			Link.l2.go = "LoanFindCitizenType_1_1";
                break;
			}
		break;

			case "LoanFindCitizen_1_2":
            switch (sti(pchar.GenQuest.Loan.FindCitizenChance3))
            {
                case 0 :
                    dialog.text = "Да, точно. Я как раз собирался ему все отдать.";
        			Link.l1 = "Ну что же, очень хорошо! Итого с тебя " + FindRussianMoneyString(makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent))) + ".";
        			Link.l1.go = "LoanFindCitizenType_0";
        			Link.l2 = "Замечательно, вот и отнеси все сам!";
        			Link.l2.go = "exit";
                break;

                case 1 :
                    dialog.text = "Нет! Ничего я не отдам! А будете приставать, стражу позову.";
                    Link.l1 = "Ничего не знаю, с тебя " + FindRussianMoneyString(makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent))) + ". А то можно поговорить и по-другому.";
        			Link.l1.go = "LoanFindCitizenType_1";
        			Link.l2 = "Ах ты, негодяй! Ну ничего, Земля круглая, свидимся еще...";
        			Link.l2.go = "LoanFindCitizenType_1_1";
                break;
			}
		break;

		case "LoanFindCitizenType_0":
            dialog.text = "Вот вся сумма.";
			Link.l1 = "Спасибо за сотрудничество!";
			Link.l1.go = "exit";
			pchar.GenQuest.Loan.FindCitizenDone = true;
        	addMoneyToCharacter(Pchar, (sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent)));
        	SetTimerCondition("LoanFindCitizenTimer", 0, 0, 30, false);
        	Log_SetStringToLog("У вас есть 30 дней, чтобы доложить работодателю и вернуть ему деньги.");
        	AddCharacterExpToSkill(pchar, "COMMERCE", 100);
		AddCharacterExpToSkill(pchar, "Fortune", 50);
        	AddQuestRecord("Gen_LoanFindCitizen", "3");
			npchar.LifeDay = 0;
		break;

		case "LoanFindCitizenType_1_1":
            dialog.text = "Рад, что мы с вами договорились.";
			Link.l1 = "Ты меня еще попомнишь!";
			Link.l1.go = "exit";
			pchar.GenQuest.Loan.FindCitizenFalied = true;
        	SetTimerCondition("LoanFindCitizenTimer", 0, 0, 30, false);
        	Log_SetStringToLog("У вас есть 30 дней, чтобы доложить работодателю о провале миссии.");
        	AddQuestRecord("Gen_LoanFindCitizen", "2");
			npchar.LifeDay = 0;
		break;

		case "LoanFindCitizenType_1":
            dialog.text = "Стража!! Хулиган"+ GetSexPhrase("ы","ки") +" зрения лишают!";
			Link.l1 = "Замолчи!";
			Link.l1.go = "fight";
			pchar.GenQuest.Loan.FindCitizenFalied = true;
        	SetTimerCondition("LoanFindCitizenTimer", 0, 0, 30, false);
        	Log_SetStringToLog("У вас есть 30 дней, чтобы доложить работодателю о провале миссии.");
        	AddQuestRecord("Gen_LoanFindCitizen", "2");
			npchar.LifeDay = 0;
			AddCharacterExpToSkill(pchar, "Sneak", 150);
		break;

		case "LoanFindCitizenType_2":
            pchar.GenQuest.Loan.FindCitizenTempMoney = makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) - rand(sti(pchar.GenQuest.Loan.FindCitizenPercent)));
            dialog.text = "Только " + pchar.GenQuest.Loan.FindCitizenTempMoney + " золотых.";
			Link.l1 = "Нет. Нужно всю сумму!";
			Link.l1.go = "LoanFindCitizen_1_2";
			Link.l2 = "Давай, что есть. Сам"+ GetSexPhrase("","а") +" доплачу. Так"+ GetSexPhrase("ой","ая") +" я сегодня добр"+ GetSexPhrase("ый","ая") +".";
			Link.l2.go = "LoanFindCitizenType_2_1";
			//NPChar.quest.LoanFindCitizenType = rand(1);// первые 2 типа
		break;

		case "LoanFindCitizenType_2_1":
            dialog.text = "Вы очень добры! Большое спасибо!";
			Link.l1 = "Эх! Вечно сам"+ GetSexPhrase("","а") +" во все лезу.";
			Link.l1.go = "exit";
			pchar.GenQuest.Loan.FindCitizenDone = true;
        	addMoneyToCharacter(Pchar, sti(pchar.GenQuest.Loan.FindCitizenTempMoney));
        	SetTimerCondition("LoanFindCitizenTimer", 0, 0, 30, false);
        	Log_SetStringToLog("У вас есть 30 дней, чтобы доложить работодателю и вернуть ему деньги.");
        	OfficersReaction("good");
        	ChangeCharacterReputation(pchar, 3);
        	AddCharacterExpToSkill(pchar, "Leadership", 30);
        	AddQuestRecord("Gen_LoanFindCitizen", "3");
			npchar.LifeDay = 0;
		break;
		//доставка сундуков
        case "TakeChest_2":
            if (GetCharacterItem(pchar, "Chest") >= sti(pchar.GenQuest.LoanChest.Chest))
            {
                if (CheckAttribute(pchar, "GenQuest.LoanChest.Money.Discount"))
				{
					Dialog.Text = "Все это хорошо, и я принимаю у вас золото. Однако, вы не уложились в отведенные вам сроки доставки. Поэтому я вынужден сократить размер вашего гонорара на " + pchar.GenQuest.LoanChest.Money.Discount + " процентов. Прошу прощения, но это обсуждению не подлежит. Извольте получить...";
					link.l1 = "Спасибо!";
    				link.l1.go = "exit";
					AddMoneyToCharacter(pchar, sti(pchar.GenQuest.LoanChest.Money)/100*sti(pchar.GenQuest.LoanChest.Money.Discount));
				}
				else
				{
					Dialog.Text = "Замечательно! Я давно его жду. Вот ваша награда.";
					link.l1 = "Спасибо!";
    				link.l1.go = "exit";
					AddMoneyToCharacter(pchar, sti(pchar.GenQuest.LoanChest.Money));
				}
				ChangeCharacterReputation(pchar, 1);
                AddCharacterExpToSkill(pchar, "Sailing", 50);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCharacterExpToSkill(pchar, "COMMERCE", 5);
                OfficersReaction("good");
    			TakeNItems(pchar, "Chest", -sti(pchar.GenQuest.LoanChest.Chest));
    			DeleteAttribute(pchar, "GenQuest.LoanChest");
    			DeleteAttribute(Pchar, "quest.LoanChestTimer");
    			AddQuestRecord("Gen_LoanTakeChest", "3");
                CloseQuestHeader("Gen_LoanTakeChest");

				pchar.questTemp.genquestcount = sti(pchar.questTemp.genquestcount) + 1;
				if(sti(pchar.questTemp.genquestcount) >= 10) UnlockAchievement("gen_quests", 1);
				if(sti(pchar.questTemp.genquestcount) >= 20) UnlockAchievement("gen_quests", 2);
				if(sti(pchar.questTemp.genquestcount) >= 40) UnlockAchievement("gen_quests", 3);
			}
			else
			{
                Dialog.Text = "Замечательно! Но где же все сундуки с золотом?";
                link.l1 = "А вы можете принять золото без сундуков?";
    			link.l1.go = "TakeChest_3";
                link.l2 = "Зайду позже.";
    			link.l2.go = "exit";
			}
		break;

		case "TakeChest_3":
            Dialog.Text = "Нет! Только в сундуках!";
            link.l1 = "Плохо. Крысы у меня их попортили.";
			link.l1.go = "exit";
			//link.l2 = "Ну а, скажем, сумма в " + FindRussianMoneyString(sti(pchar.GenQuest.LoanChest.Chest)*30000) + " покроет стоимость сундуков?";
			//link.l2.go = "TakeChest_4";
		break;

		/*case "TakeChest_4":
            Dialog.Text = "Да, это приемлемо.";
            if (sti(pchar.Money) >= (sti(pchar.GenQuest.LoanChest.Chest)*30000))
            {
                link.l1 = "Вот и договорились!";
    			link.l1.go = "TakeChest_5";
			}
			link.l2 = "Только это много для меня.";
			link.l2.go = "exit";
		break;

		case "TakeChest_5":
            ChangeCharacterReputation(pchar, 1);
            AddCharacterExpToSkill(pchar, "Sailing", 30);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "COMMERCE", 30);
            OfficersReaction("good");
            Dialog.Text = "С вами можно иметь дело!";
            link.l1 = "Спасибо!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1*(sti(pchar.GenQuest.LoanChest.Chest)*30000));
			DeleteAttribute(pchar, "GenQuest.LoanChest");
			DeleteAttribute(Pchar, "quest.LoanChestTimer");
			AddQuestRecord("Gen_LoanTakeChest", "4");
            CloseQuestHeader("Gen_LoanTakeChest");
		break;
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Квесты мэра, проникновение во враждебный город
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "IntelligenceForAll":
            Dialog.Text = RandPhraseSimple("Ну что же, очень хорошо. У меня готов для вас пакет, который вам надлежит доставить известному лицу лично в руки. Извольте получить.\nНе подходите ко мне больше и не заговаривайте со мной, это может быть подозрительным. Соблюдайте осторожность...",
				"Хм, прекрасно. Я вручаю вам пакет, и помните, что он должен быть доставлен названному вами лицу лично в руки.\nТеперь прощайте и не подходите ко мне более - это опасно.");
            link.l1 = RandPhraseSimple("Я понял"+ GetSexPhrase("","а") +". Прощайте...", "Прощайте и удачи.");
			link.l1.go = "exit";
			pchar.GenQuest.Intelligence = "Execute";
			GiveItem2Character(pchar, "sicretLetter");
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			ref rItem = ItemsFromID("sicretLetter");
			rItem.City = XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.Intelligence.MayorId)].city+"Gen"));
			rItem.Mayor = GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId));
			AddQuestRecord("MayorsQuestsList", "7");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.Intelligence.MayorId)].city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat"));
			AddQuestUserData("MayorsQuestsList", "sWho", GetWorkTypeOfMan(&characters[GetCharacterIndex(pchar.GenQuest.Intelligence.SpyId)], "Gen"));
			AddQuestUserData("MayorsQuestsList", "SpyName", GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.Intelligence.SpyId)]));
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Квест Асокольда, рендомные базары
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "AscoldTrader": //рендомный хозяин магаза
            dialog.Text = "Послушай, не встречал"+ GetSexPhrase("","а") +" еще порошка мумии, который я просил тебя разыскать?";
            if (GetQuestPastDayParam("questTemp.Ascold") > 3)
			{
				Link.l1 = "Нет, пока не встречал"+ GetSexPhrase("","а") +"... Послушай, у торговцев на улицах он, кажется, есть, но что-то они темнят...";
            	Link.l1.go = "AscoldTrader_6";
			}
			else
			{
				Link.l1 = "Нет, пока не встречал"+ GetSexPhrase("","а") +"... Но я продолжу поиски.";
            	Link.l1.go = "quests";
			}
		break;
        case "AscoldTrader_WasSeek":
            dialog.Text = "Послушай, не встречал"+ GetSexPhrase("","а") +" еще порошка мумии, который я просил тебя разыскать?";
            Link.l2 = "Да, наш"+ GetSexPhrase("ел","ла") +". И сколько ты мне за него заплатишь?";
            Link.l2.go = "AscoldTrader_1";
        break;
		case "AscoldTrader_1":
        	dialog.text = "Я - нисколько. Но я знаю, кто купит у тебя это.";
    		link.l1 = "Хм, я рассчитывал"+ GetSexPhrase("","а") +" на получение денег прямо сейчас.";
    		link.l1.go = "AscoldTrader_2";
		break;
 		case "AscoldTrader_2":
        	dialog.text = "Полагаю, ты не останешься в накладе. Слушай внимательно.\n"+
                          "На Гваделупе в городе Бас Тер живет один странный тип - Аскольд.";
            if (Characters[GetCharacterIndex("Ascold")].quest.meeting == "0")
            {
                link.l1 = "Странное имя...";
                link.l1.go = "AscoldTrader_4";
            }
            else
            {
                link.l1 = "Знаю я его, довелось поговорить. Наглец, каких поискать...";
                link.l1.go = "AscoldTrader_3";
            }
		break;
 		case "AscoldTrader_3":
        	dialog.text = "А что случилось? Испытал"+ GetSexPhrase("","а") +" на себе его крутой нрав?";
    		link.l1 = "Да уж, он просто выставил меня за дверь, как "+ GetSexPhrase("мальчишку","девчонку") +"!";
    		link.l1.go = "AscoldTrader_4";
		break;
 		case "AscoldTrader_4":
        	dialog.text = "Аскольд немного резковат, но человек он хороший, честный. По слухам - московит, есть такой народ, который живет на севере Старого Света, где круглый год снег, а вокруг одни леса да медведи. Оттого и характер суровый, а силы в руках хватит на четверых здоровенных молодцов.\n"+
                          "Как и когда он оказался здесь, я точно не знаю, как и не знаю, чем он занимается.\n"+
                          "Но мне он доверяет, так как я имею с ним торговые дела.\n"+
                          "Так что поезжай к нему, представишься, скажешь, что от меня - и все будет в порядке. Купит он у тебя эту дрянь, так как это его заказ.";
    		link.l1 = "А тебе с этого какой доход?";
    		link.l1.go = "AscoldTrader_5";
		break;
 		case "AscoldTrader_5":
        	dialog.text = "За меня не переживай, я удержу нужную сумму комиссионных из нашей с ним текущей оборотки.";
    		link.l1 = "Понятно. Что ж, пожалуй, загляну к твоему Аскольду при случае.";
    		link.l1.go = "exit";
    	    pchar.questTemp.Ascold = "GoToAscold";
    	    QuestSetCurrentNode("Ascold", "HaveRecomendation");
            AddQuestRecord("Ascold", "2");
		break;
 		case "AscoldTrader_6":
        	dialog.text = "Небось, и Инквизицией грозятся?";
    		link.l1 = "Точно, грозятся...";
    		link.l1.go = "AscoldTrader_7";
		break;
 		case "AscoldTrader_7":
        	dialog.text = "Ну а как ты хотел"+ GetSexPhrase("","а") +"?.. Вот что я тебе скажу, "+ GetSexPhrase("приятель","подруга") +": порошок есть у них. Не у всех, конечно, но у кого-то точно он имеется. Поэтому ты будь настойчивей с ними - и в итоге добьешься своего.";
    		link.l1 = "Хех, ну что же, спасибо за помощь.";
    		link.l1.go = "quests";
			SaveCurrentQuestDateParam("questTemp.Ascold");
		break;
        //==> Общий диалог для хозяев верфи, квест Аззи.
		case "AzzyTryTalk":
			dialog.Text = NPCStringReactionRepeat("Давай посмотрим на твою жестянку. Э-э-э, нет. Ты посмотри на нее, она сплошь покрыта странными письменами, не иначе это колдовство. Советую тебе отнести эту вещь в церковь, там разберутся, что с ней делать.", "none", "none", "none", "block", 0, npchar, Dialog.CurrentNode);
  			Link.l1 = HeroStringReactionRepeat("Спасибо за добрый совет.", "none", "none", "none", npchar, Dialog.CurrentNode);
			Link.l1.go = "Exit";
		break;
		case "AggryHelp":
			dialog.Text = NPCStringReactionRepeat("Вот там на столе лежит инструмент: паяльная лампа, ножовка по металлу, ножницы для жести и прочее. Бери и открывай сам"+ GetSexPhrase("","а") +", а денег мне не надо.", "none", "none", "none", "block", 0, npchar, Dialog.CurrentNode);
			Link.l10 = HeroStringReactionRepeat("Спасибо, " + npchar.name + ".", "none", "none", "none", npchar, Dialog.CurrentNode);
			Link.l10.go = "exit";
			items[GetItemIndex("Azzy_bottle")].shown = 0; //даем возможность вскрыть лампу
		break;
		//==> Общий диалог для церкви, квест Аззи.
        case "GiveLamp":
			dialog.text = "Ты правильно поступил"+ GetSexPhrase(", сын мой","а, дочь моя") +". Неизвестно, что там внутри, но по всему видно, что завтра церковь нужно будет освящать заново.\n"+
                          "Я не хочу спрашивать, где ты это взял"+ GetSexPhrase("","а") +". Именем Спасителя прощаю тебе грехи твои! Иди с миром.";
			link.l1 = "Спасибо, Святой Отец.";
			link.l1.go = "exit";
            ChangeCharacterReputation(pchar, 100);
            TakeItemFromCharacter(pchar, "Azzy_bottle");
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Грабеж среди бела дня, попытка залезть в сундуки
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "Man_FackYou":
			dialog.text = LinkRandPhrase("Грабеж среди бела дня!!! Это что же такое делается?! Ну, погоди, "+ GetSexPhrase("приятель","подруга") +"...", "Эй, ты чего это там копаешься?! Никак, вздумал"+ GetSexPhrase("","а") +" ограбить меня? Ну, тогда тебе конец...", "Постой, ты куда это полез"+ GetSexPhrase("","ла") +"? Да ты вор"+ GetSexPhrase("","овка") +", оказывается! Ну, считай, что ты приплыл"+ GetSexPhrase("","а") +", родн"+ GetSexPhrase("ой","ая") +"...");
			link.l1 = LinkRandPhrase("Дьявол!!", "Каррамба!!", "А-ать, черт!");
			link.l1.go = "fight_owner";
		break;
		case "fight_owner":
			LAi_SetOwnerTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Квест получения Синей птицы
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "RBlueBird":
			dialog.text = "Эх, капитан, не случилось, а случается уже давно. Мы, торговцы Карибского моря, на грани разорения. А во всем виновата проклятая 'Синяя Птица'...";
			link.l1 = "'Синяя Птица'?";
			link.l1.go = "RBlueBird_1";
		break;
		case "RBlueBird_1":
			dialog.text = "Да, это чертова шебека, единственный корабль такого типа здесь, уйти от него в море невозможно. Грабит только корабли торговцев. Большие караваны, усиленные военными кораблями, не трогает.";
			link.l1 = "А почему вы сказали, что торговцы разоряются? Ведь товары все равно поступают сюда с этими караванами.";
			link.l1.go = "RBlueBird_2";
		break;
		case "RBlueBird_2":
			dialog.text = "Поступают, верно. Но все дело в том, что оборот при таком раскладе становится невыгодным. Лучше всего иметь свой шлюп или флейт, самим закупать товары в Старом Свете и везти сюда. Вот это - торговля!\nА когда мы закупаем товары у перевозчиков - тут уже не до прибылей, речь идет о простом выживании.";
			link.l1 = "Понятно. И как раз ваши корабли берет на абордаж шебека...";
			link.l1.go = "RBlueBird_3";
		break;
		case "RBlueBird_3":
			dialog.text = "Именно так. Уже почти все торговцы потеряли собственные корабли, черт ее дери, эту 'Синюю Птицу'!";
			link.l1 = "М-да, печально для вас... Ну, так что же вы хотите от меня?";
			link.l1.go = "RBlueBird_4";
		break;
		case "RBlueBird_4":
			dialog.text = "Мы хотим, чтобы вы уничтожили эту сизокрылую выхухоль, мать ее перемать!!!";
			link.l1 = "И что я буду с этого иметь?";
			link.l1.go = "RBlueBird_5";
		break;
		case "RBlueBird_5":
			dialog.text = "Я соберу со всех коллег достойную оплату для вас за эту работу. Пятьдесят тысяч пиастров я могу вам твердо обещать. Чертова шебека должна пойти на дно!";
			link.l1 = "За такие деньги, приятель, я и пальцем не шевельну. Ищи дурака!";
			link.l1.go = "RBlueBird_close";
			link.l2 = "Хм, эти деньги меня интересуют. Я готов"+ GetSexPhrase("","а") +" взяться за это дело. Каковы сроки выполнения?";
			link.l2.go = "RBlueBird_6";
		break;
		case "RBlueBird_6":
			dialog.text = "Вы не ограничены во времени. Я прекрасно понимаю, что сделать это будет нелегко, черт возьми! Сказать по правде, мы уже привлекали наемных убийц к этому делу, хотели убрать капитана. Безрезультатно...";
			link.l1 = "Вот как? Вы можете подробней об этом рассказать?";
			link.l1.go = "RBlueBird_7";
		break;
		case "RBlueBird_7":
			dialog.text = "Ну, скинулись мы и наняли кое-кого, чтобы он разыскал кэпа этой шебеки среди пиратов. Ничего не вышло, наш наймит с полгода рыскал по Карибам, но ничего не нашел. Черт его знает, где они базируются и куда сбывают награбленное...";
			link.l1 = "Та-а-а-ак, приятель, это уже что-то. А теперь послушай мои условия сделки.";
			link.l1.go = "RBlueBird_8";
		break;
		case "RBlueBird_8":
			dialog.text = "Внимательно слушаю, " + GetAddress_Form(NPChar) + "." ;
			link.l1 = "Эта сделка между тобой и мной, деньги собирай, как хочешь, но никому не болтай, что я взял"+ GetSexPhrase("ся","ась") +" за это дело. И второе. Ты сказал, что потеряли свои корабли ПОЧТИ все торговцы. Что значит 'почти'?";
			link.l1.go = "RBlueBird_9";
		break;
		case "RBlueBird_9":
			dialog.text = "У одного торговца остался флейт. Но он счастливчик, ни разу не попадал на эту шебеку. Он - наша единственная надежда закрепиться здесь, уже все наши ему должны. Если бы он не поддерживал нас в трудную минуту - всем давно пришел бы конец. Он еще никому не отказывал в просьбах дать денег в долг!";
			link.l1 = "Понятно. Почти святой! И как же его зовут?";
			link.l1.go = "RBlueBird_10";
		break;
		case "RBlueBird_10":
			dialog.text = "Паскаль Вуазье. Он содержит лавку на Бермудах в пиратском поселении. Так вы беретесь за дело?";
			link.l1 = "Вы принимаете мое условие о молчании?";
			link.l1.go = "RBlueBird_11";
		break;
		case "RBlueBird_11":
			dialog.text = "Безусловно!";
			link.l1 = "Тогда берусь. Я начинаю поиски с этого дня, надеюсь вскоре закончить.";
			link.l1.go = "RBlueBird_12";
		break;
		case "RBlueBird_12":
			dialog.text = "Эх, вашими бы устами, да мед пить! Ну что же, приступайте. Очень надеюсь, что все будет проходить так, как вы сказали.";
			link.l1 = "Будет, можете не сомневаться!";
			link.l1.go = "exit";
			pchar.questTemp.BlueBird = "toBermudes";
			pchar.questTemp.BlueBird.traiderId = npchar.id; //запомним Id торговца
			SetQuestHeader("Xebeca_BlueBird");
			AddQuestRecord("Xebeca_BlueBird", "1");
			AddQuestUserData("Xebeca_BlueBird", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("Xebeca_BlueBird", "sName", GetFullName(npchar));
		break;


		case "RBlueBird_close":
			dialog.text = "Ну что же, очень жаль. Пожалуй, мы поищем 'дурака' в другом месте...";
			link.l1 = "Гм...";
			link.l1.go = "exit";
			pchar.questTemp.BlueBird = "declined";//Блокировка ЧП
		break;
		case "RBlueBirdWon":
			dialog.text = "Прекрасная новость, скажу я вам! Наконец-то мы сможем заняться торговлей по-настоящему... Вы хотите получить деньги прямо сейчас?";
			link.l1 = "Да, желательно...";
			link.l1.go = "RBlueBirdWon_1";
			int chComp;
			for (int i=0; i<=COMPANION_MAX; i++)
        	{
                chComp = GetCompanionIndex(pchar, i);
                if(chComp != -1 && RealShips[sti(characters[chComp].ship.type)].Name == "XebekVML1")
        		{
					dialog.text = "Хм, подождите... Насколько мне известно, вы сумели настигнуть шебеку, но не потопили ее! Теперь она находится в вашем владении.";
					link.l1 = "Да, это так. Ну и в чем проблема?";
					link.l1.go = "RBlueBirdWon_10";
					break;
                }
            }
		break;

		case "RBlueBirdWon_1":
			dialog.text = "Без проблем, извольте получить. Деньги в сундуках. Здесь даже немного больше пятидесяти тысяч.";
			link.l1 = "Спасибо, мы в расчете. Желаю всего наилучшего... Кстати, а вы не хотите узнать, кто стоял за всем этим?";
			link.l1.go = "RBlueBirdWon_2";
			TakeNItems(pchar, "chest", 4);
			Log_Info("Вы получили кредитные сундуки");
			PlaySound("interface\important_item.wav");
		break;
		case "RBlueBirdWon_2":
			dialog.text = "Хм, очень будет интересно узнать...";
			link.l1 = "Это самый 'святой' торговец в Карибском море - Паскаль Вуазье.";
			link.l1.go = "RBlueBirdWon_3";
		break;
		case "RBlueBirdWon_3":
			dialog.text = "Не может быть!..";
			link.l1 = "Может. Доказательств, к сожалению, у меня нет, но вы имейте в виду, кто ссужает вам ваши же деньги.";
			link.l1.go = "RBlueBirdWon_4";
		break;
		case "RBlueBirdWon_4":
			dialog.text = "Хм, все это нужно проверить... Ну что же, спасибо вам за работу и за информацию.";
			link.l1 = "Да не за что, это вами оплачено. Прощайте.";
			link.l1.go = "exit";
			CloseQuestHeader("Xebeca_BlueBird");
			pchar.questTemp.BlueBird = "over";
		break;

		case "RBlueBirdWon_10":
			dialog.text = "Проблема в том, что этот проклятый корабль теперь у вас в руках. А вы, кстати, тоже пират! И кто вам помешает грабить торговцев точно так же, как это делал предыдущий хозяин?";
			link.l1 = "Хм, вопрос, конечно, интересный... Однако, я выполнил"+ GetSexPhrase("","а") +" работу!";
			link.l1.go = "RBlueBirdWon_11";
		break;
		case "RBlueBirdWon_11":
			dialog.text = "Нет, вы ее не выполнили. Мы договаривались о потоплении 'Синей Птицы', а не об абордаже.";
			link.l1 = "Хм, вот значит как! Ну что же, я вас понял"+ GetSexPhrase("","а") +"... Всего наилучшего, передавайте мой пламенный привет вашим коллегам.";
			link.l1.go = "RBlueBirdWon_12";
		break;
		case "RBlueBirdWon_12":
			dialog.text = "Передам всенепременно! Прощайте, и впредь держите свое слово 'от' и 'до'.";
			link.l1 = "Обязательно. Но я не прощаюсь...";
			link.l1.go = "exit";
			AddQuestRecord("Xebeca_BlueBird", "9");
			AddQuestUserData("Xebeca_BlueBird", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("Xebeca_BlueBird", "sSex1", GetSexPhrase("полный кретин","полная дура"));
			pchar.questTemp.BlueBird = "returnMoney";
			pchar.questTemp.BlueBird.City = GetSharpCity();
		break;

		case "RBlueBirdDieHard":
			dialog.text = "Очень и очень жаль. Ну что же, вы не перв"+ GetSexPhrase("ый","ая") +", кто берется за это дело, и у кого ничего не выходит. Плохо, придется нам и далее прозябать...";
			link.l1 = "Надеюсь, все придет в норму со временем...";
			link.l1.go = "RBlueBirdDieHard_1";
		break;
		case "RBlueBirdDieHard_1":
			dialog.text = "Это уж точно. Вот живем тут в суете, и наивно полагаем, что именно вокруг нас земля вертится. Ан нет, из земли взято, в землю и уйдем\nХех, что-то меня на лирику потянуло.";
			link.l1 = "Бывает... Ну что же, прощайте.";
			link.l1.go = "exit";
			CloseQuestHeader("Xebeca_BlueBird");
			pchar.questTemp.BlueBird = "over";
		break;

		case "RBlueBird_retMoney_1":
			dialog.text = "Ах ты мерзав"+ GetSexPhrase("ец","ка") +"! Значит, наши опасения оказались верными!!";
			link.l1 = "Я бы вас не трогал"+ GetSexPhrase("","а") +", если бы вы не начали жульничать!";
			link.l1.go = "RBlueBird_retMoney_2";
		break;
		case "RBlueBird_retMoney_2":
			dialog.text = "А-а-ать, черт! Стража, хватай е"+ GetSexPhrase("го","е") +"!! Далеко тебе не уйти, мерзав"+ GetSexPhrase("ец","ка") +"...";
			link.l1 = "Лучше бы вернули мои деньги, проныры. Будем лечить вас дальше...";
			link.l1.go = "fight";
		break;

		case "RBlueBird_retMoney_3":
			dialog.text = "Будь ты проклят"+ GetSexPhrase("","а") +", мерзав"+ GetSexPhrase("ец","ка") +"! Как я жалею, что связался с тобой!! До тебя 'Синяя Птица' никогда не доставляла нам СТОЛЬКО проблем!..";
			link.l1 = "Друзья мои, вы сами виноваты, нужно было держаться договора.";
			link.l1.go = "RBlueBird_retMoney_4";
		break;
		case "RBlueBird_retMoney_4":
			dialog.text = "Какого договора, нашего с вами? Мы его неукоснительно придерживались! Это вы его нарушили, не потопив шебеку!";
			link.l1 = "Мон шер, не надо так кричать, это пагубно отражается на голосовых связках. А вдруг не сможете потом разговаривать? В общем, я готов"+ GetSexPhrase("","а") +" говорить с вами только на умеренных тонах...";
			link.l1.go = "RBlueBird_retMoney_5";
		break;
		case "RBlueBird_retMoney_5":
			dialog.text = "Ну хорошо, хотя тон здесь ни при чем. Это вы нарушили условия сделки, а не мы - вот суть вопроса!";
			link.l1 = "Хех! Вы, торговцы, большие мастера эдаких заковык в договорах. Знаю я ваши штучки. Где-то запятую не поставил, и смысл текста сразу меняется.";
			link.l1.go = "RBlueBird_retMoney_6";
		break;
		case "RBlueBird_retMoney_6":
			dialog.text = "При чем здесь запятые? У нас с вами была устная договоренность.";
			link.l1 = "Ну, это я образно выражаюсь. Смысл в том, что вы зацепились за возможность кинуть меня на бабки, и сделали это. А я пират, мне недосуг разбираться в двойных смыслах ваших условий.";
			link.l1.go = "RBlueBird_retMoney_7";
		break;
		case "RBlueBird_retMoney_7":
			dialog.text = "Каких условий?";
			link.l1 = "Условий наших договоренностей. Вам мешала 'Синяя Птица' - я решил"+ GetSexPhrase("","а") +" эту проблему. Если бы вы отдали мне мои деньги, то я вас и пальцем бы не тронул"+ GetSexPhrase("","а") +". Так что все ваши проблемы от вашей мудрости, так сказать...";
			link.l1.go = "RBlueBird_retMoney_8";
		break;
		case "RBlueBird_retMoney_8":
			dialog.text = "Ну ладно, забирайте ваши 50 тысяч и убирайтесь отсюда!";
			link.l1 = "Не так быстро, мон шер. Все дело в том, что я понес"+ GetSexPhrase("","ла") +" дополнительные финансовые издержки, пытаясь вразумить вас. Не говоря уже о моральном ущербе. Поэтому сумма выросла.";
			link.l1.go = "RBlueBird_retMoney_9";
		break;
		case "RBlueBird_retMoney_9":
			dialog.text = "И что это за новая сумма? Назовите ее.";
			link.l1 = "Увеличьте ее в четыре раза. 200 тысяч, и я оставлю вас в покое. Иначе - разорю. А потом убью. Сначала вашу семью, а потом вас...";
			link.l1.go = "RBlueBird_retMoney_10";
		break;
		case "RBlueBird_retMoney_10":
			dialog.text = "Да ты - дьявол"+ GetSexPhrase("","ица") +"!!";
			link.l1 = "И очень, очень зл"+ GetSexPhrase("ой дьявол","ая дьяволица") +"...";
			link.l1.go = "RBlueBird_retMoney_11";
		break;
		case "RBlueBird_retMoney_11":
			dialog.text = "Хорошо. Вот твои деньги - четырнадцать сундуков. Здесь даже больше двухсот тысяч. А теперь убирайся! И оставь нас в покое!";
			link.l1 = "Всенепременно. Теперь, когда вы рассчитались со мной, 'Синяя Птица' вам более не угрожает. Прощайте, удачи в делах коммерческих...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.BlueBird");
			pchar.questTemp.BlueBird = "over"; //закрываем квест
			TakeNItems(pchar, "chest", 14);
			Log_Info("Вы получили кредитные сундуки");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Xebeca_BlueBird", "14");
			AddQuestUserData("Xebeca_BlueBird", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("Xebeca_BlueBird", "sSex1", GetSexPhrase("ен","ьна"));
			CloseQuestHeader("Xebeca_BlueBird");
		break;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Линейка острова погибших кораблей ISS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "ISS_deposit":
			dialog.text = NPCStringReactionRepeat("Совершенно верно. Один миллион пиастров вы можете получить через минуту после получения мной подтверждения.",
				"Я уже говорил вам, " + GetAddress_Form(NPChar) + ", что депозит у меня. Я жду подтверждения на его выдачу.",
				"Вам не стоит беспокоиться. Депозит находится у меня, я жду только подтверждения на его выдачу.",
				"Хм, мне кажется, вы чрезмерно обеспокоены этим депозитом. Моя репутация безупречна, поэтому я могу только повторить ранее сказанное. Депозит на ваше имя находится у меня, получить вы его сможете после подтверждения на выдачу.", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Понятно. Ну что же, прекрасно. Я узнал"+ GetSexPhrase("","а") +" то, что хотел"+ GetSexPhrase("","а") +".",
				"Ага, понятно...",
				"Я и не беспокоюсь особо.",
				"Понятно... Спасибо вам, " + GetAddress_Form(NPChar) + ".", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		case "ISS_takeDeposit":
			dialog.text = "Да-да, я получил разрешение провести эту финансовую операцию. Извольте получить, " + GetAddress_Form(NPChar) + ".";
			link.l1 = "Хе-хе, очень хорошо...";
			link.l1.go = "ISS_takeDeposit_1";
			AddMoneyToCharacter(pchar, 1000000);
			CloseQuestHeader("ISS_PoorsMurder");
		break;
		case "ISS_takeDeposit_1":
			dialog.text = "Быть может, вы решите пустить эти деньги в рост? Я всегда к вашим услугам, моя репутация...";
			link.l1 = "Я понял"+ GetSexPhrase("","а") +" вас, спасибо. Я подумаю.";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "over"; //конец линейки ГПК
			CloseQuestHeader("ISS_PoorsMurder");
		break;
		//механика арестовали, диалоги мужика
		case "MechanicIsPrison_man":
			dialog.text = "А-а, ну вот и вы, наконец...";
			link.l1 = "В чем дело? Почему вы еще не на фрегате?... А где Механик?";
			link.l1.go = "MechanicIsPrison_man_1";
		break;
		case "MechanicIsPrison_man_1":
			dialog.text = "Где он сейчас я не знаю. Когда я приш"+ NPCharSexPhrase(NPChar, "ел","ла") +" на 'Сан Габриэль', его как раз выводили милиционеры. Судя по всему, он арестован, и сделать это мог только адмирал.";
			link.l1 = "Каррамба!!! Что же теперь делать?";
			link.l1.go = "MechanicIsPrison_man_2";
		break;
		case "MechanicIsPrison_man_2":
			dialog.text = "А без Механика нам не обойтись?";
			link.l1 = "Ведекер нам нужен. На фрегат мы попасть сможем, а вот освободить его без Хенрика не выйдет.";
			link.l1.go = "MechanicIsPrison_man_3";
		break;
		case "MechanicIsPrison_man_3":
			dialog.text = "Тогда нужно идти в резиденцию к Капперу, выручать Механика. Я, к сожалению, пас в этом деле - адмирал наводит на меня ужас одним своим видом...";
			link.l1 = "Хех, оно и понятно... Отправляйтесь на корабль, я скоро прибуду с Ведекером. Остальные члены команды, судя по всему, уже там.";
			link.l1.go = "MechanicIsPrison_man_4";
		break;
		case "MechanicIsPrison_man_4":
			dialog.text = "Как скажете, капитан.";
			link.l1 = "Не паникуйте там без меня. Все будет хорошо.";
			link.l1.go = "exit";
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.LSC = "MechanicIsArrest_toResidence";
			SetCrewQuantity(pchar, GetMinCrewQuantity(pchar));
			bDisableFastReload = true;
			AddQuestRecord("ISS_MainLine", "64");
			pchar.quest.LSC_fightEnterResidence.win_condition.l1 = "location";
			pchar.quest.LSC_fightEnterResidence.win_condition.l1.location = "SanAugustineResidence";
			pchar.quest.LSC_fightEnterResidence.function = "LSC_fightEnterResidence";
		break;
		//механика арестовали, диалоги бабы
		case "MechanicIsPrison_woman":
			dialog.text = "А-а, ну вот и вы, наконец...";
			link.l1 = "В чем дело? Почему вы еще не на фрегате?... А где Механик?";
			link.l1.go = "MechanicIsPrison_man_1";
		break;
		case "MechanicIsPrison_woman_1":
			dialog.text = "Где он сейчас я не знаю. Когда я пришла на 'Сан Габриэль', его как раз выводили милиционеры. Судя по всему, он арестован, и сделать это мог только адмирал.";
			link.l1 = "Каррамба!!! Что же теперь делать?";
			link.l1.go = "MechanicIsPrison_woman_2";
		break;
		case "MechanicIsPrison_woman_2":
			dialog.text = "А без Механика нам не обойтись?";
			link.l1 = "Ведекер нам нужен. На корабль мы попасть сможем, а вот освободить его без Хенрика не выйдет.";
			link.l1.go = "MechanicIsPrison_man_3";
		break;
		case "MMechanicIsPrison_woman_3":
			dialog.text = "Тогда нужно идти в резиденцию к Капперу, выручать Механика. Я, как женщина, помочь в этом деле вам не смогу, к сожалению.";
			link.l1 = "Это точно... Отправляйтесь на корабль, я скоро прибуду с Ведекером. Остальные члены команды, судя по всему, уже там.";
			link.l1.go = "MechanicIsPrison_man_4";
		break;
		case "MechanicIsPrison_woman_4":
			dialog.text = "Как скажете, капитан.";
			link.l1 = "Не паникуйте там без меня. Все будет хорошо.";
			link.l1.go = "exit";
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.LSC = "MechanicIsArrest_toResidence";
			SetCrewQuantity(pchar, GetMinCrewQuantity(pchar));
			bDisableFastReload = true;
			AddQuestRecord("ISS_MainLine", "64");
			pchar.quest.LSC_fightEnterResidence.win_condition.l1 = "location";
			pchar.quest.LSC_fightEnterResidence.win_condition.l1.location = "SanAugustineResidence";
			pchar.quest.LSC_fightEnterResidence.function = "LSC_fightEnterResidence";
		break;
		case "SeekCrew_all":
			pchar.questTemp.LSC.crew = sti(pchar.questTemp.LSC.crew) + 1;
			chrDisableReloadToLocation = true;
			float   locx, locy, locz;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			if (sti(pchar.questTemp.LSC.crew) >= 15)
			{
				DeleteAttribute(pchar, "questTemp.LSC.crew");
				pchar.questTemp.LSC = "MechanicIsArrest";
				pchar.questTemp.LSC.lastManId = npchar.index; //сюда запишем индекс
				NextDiag.TempNode = "MechanicIsPrison_" + npchar.sex;
				AddQuestRecord("ISS_MainLine", "63");
				AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("","а"));
				AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("ен","на"));
				if (npchar.location.group == "sit")
				{
					ChangeCharacterAddressGroup(npchar, npchar.location, "goto", LAi_FindNearestLocator("goto", locx, locy, locz));
				}
				npchar.cityTape = "quest";  //чтобы не передвигался
				DeleteAttribute(npchar, "location.going"); //снять метку на перемещение
				LAi_SetActorType(npchar);
				LAi_ActorRunToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 10.0);
				pchar.quest.LSC_afterArestMachanic.win_condition.l1 = "ExitFromLocation";
				pchar.quest.LSC_afterArestMachanic.win_condition.l1.location = pchar.location;
				pchar.quest.LSC_afterArestMachanic.function = "LSC_afterArestMachanic";
			}
			else
			{
				AddQuestRecord("ISS_MainLine", "62");
				AddQuestUserData("ISS_MainLine", "sName", GetFullName(npchar));
				AddQuestUserData("ISS_MainLine", "Sex", NPCharSexPhrase(npchar, "согласился", "согласилась"));
				AddQuestUserData("ISS_MainLine", "iCrew", FindRussianPeoplesString(15-sti(pchar.questTemp.LSC.crew), "Acc"));
				npchar.lifeDay = 0;
				if (npchar.location.group == "sit")
				{
					ChangeCharacterAddressGroup(npchar, npchar.location, "goto", LAi_FindNearestLocator("goto", locx, locy, locz));
				}
				LAi_SetActorType(npchar);
				LAi_ActorRunToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 10.0);
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string sRumourAboutOwners_CityRumour(string sCity, string sOwnerType) // Здесь идет распределение по городам
{
	string sRetRumour = "Явный баг. Сообщите о нем АТ, для Warship'а.";
	// флаг - PChar.QuestTemp.RumoursAboutOwners.(sOwner) - для проверок, какой вопрос выпал. Ножно будет юзать для квестов
	switch(sCity)
	{
		case "Tortuga":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 0;
		break;

		case "PortRoyal":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 1;
		break;

		case "FortOrange":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 2;
		break;

		case "Beliz":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 3;
		break;

		case "PortoBello":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 4;
		break;

		case "Cartahena":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 5;
		break;

		case "Maracaibo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 6;
		break;

		case "Caracas":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 7;
		break;

		case "Cumana":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 8;
		break;

		case "SantaCatalina":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 9;
		break;

		case "SanJuan":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 10;
		break;

		case "Marigo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 11;
		break;

		case "Charles":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 12;
		break;

		case "SentJons":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 13;
		break;

		case "FortFrance":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 14;
		break;

		case "BasTer":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 15;
		break;

		case "Bridgetown":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 16;
		break;

		case "PortSpein":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 17;
		break;

		case "Havana":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 18;
		break;

		case "Villemstad":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 19;
		break;

		case "Santiago":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 20;
		break;

		case "PortPax":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 21;
		break;

		case "SantoDomingo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 22;
		break;
	}

	return sRetRumour;
}

string sRumourAboutOwners_Init(string sOwnerType, int iRumourNum) // База слухов жителей. Можно менять без новой игры
{

	string STR_MAYOR[MAX_RUMOURS_ABOUT_OWNERS]; // Губернаторы
	STR_MAYOR[0] = "О, господин губернатор - замечательный человек. Он умело управляет нашей колонией - с момента ее основания у нас не было ни единого крупного конфликта\nЕдинственный его недостаток - он... ммм... весьма бережлив. Хотя, возможно, это наоборот достоинство.";
	STR_MAYOR[1] = "О, господин губернатор - замечательный человек. Он умело управляет нашей колонией - с момента ее основания у нас не было ни единого крупного конфликта\nЕдинственный его недостаток - он... ммм... весьма бережлив. Хотя, возможно, это наоборот достоинство.";
	STR_MAYOR[2] = "Увы, господин губернатор у нас хороший... Но слабохарактерный. Ему бы чуточку твердости в душе - и у наших торговцев появились бы небольшие налоговые льготы... И субсидии на ремонт форта давно пора бы выделить.";
	STR_MAYOR[3] = "Хм... Он недавно стал у нас губернатором. Он довольно молод и поэтому очень инициативен - при нем наша колония процветает.";
	STR_MAYOR[4] = "Наш губернатор еще относительно молод. Говорят, он - непутевый младший сын испанского графа, отправленный от двора куда подальше, чтобы прекратил позорить свой род. Назначен он был сюда совсем недавно, и ничего запоминающегося сотворить не успел.";
	STR_MAYOR[5] = "Хм... Он недавно стал у нас губернатором. Он довольно молод и поэтому очень инициативен - при нем наша колония процветает.";
	STR_MAYOR[6] = "Э-э... Ничего... ничего плохого сказать про него не могу.";

	string STR_TAVERNKEEPER[MAX_RUMOURS_ABOUT_OWNERS]; // Тавернщики
	STR_TAVERNKEEPER[0] = "Хм, я бы не доверил свое имущество этому пройдохе. Не поймите меня неправильно, но мне кажется, что это самый ненадежный человек в нашем городке\nГоворят, что он путается с контрабандистами и пиратами - и в таверне у него все время всякий сброд ошивается!";
	STR_TAVERNKEEPER[1] = "Да что о нем можно сказать! Трусоват, да и умом не отличается. К тому же жаден до денег, отчего постоянно попадает в различные неприятности! Зато, правда, он всегда в курсе всех новостей.";
	STR_TAVERNKEEPER[2] = "Довольно приятный тип. У него в таверне всегда приятно посидеть, да и чувством юмора у хозяина все в порядке. А самое главное - он следит за порядком в таверне и не позволяет всякой пьяной швали задирать добропорядочных граждан.";
	STR_TAVERNKEEPER[3] = "Удивительный человек. Ему надо не таверну содержать, а осведомителем быть при тайной канцелярии. Иногда кажется, что ему известно буквально все, что происходит в нашем городе. Даже жуть пробирает.";
	STR_TAVERNKEEPER[4] = "Не знаю, чего уж вам о нем сказать. Человек как человек. Содержит таверну, соответственно, в курсе всех новостей нашего острова.";
	STR_TAVERNKEEPER[5] = "Говорят, на него можно положиться. С другой стороны, я слышал, что он не любит ненужного риска и всегда расчетливо ведет свои дела. Да и темными делишками вроде не занимается.";
	STR_TAVERNKEEPER[6] = "Таверна досталась ему от отца. Его отец содержал таверну не так далеко отсюда, на небольшом острове Хайрок в другом архипелаге. Потом отец перебрался сюда, построил здесь новую таверну, и теперь в ней заправляет его сын.";

	string STR_SHIPYARDER[MAX_RUMOURS_ABOUT_OWNERS]; // Верфисты
	STR_SHIPYARDER[0] = "Корабли он строит неплохие... А как о человеке, о нем трудно что-либо сказать - он живет тихо и спокойно. Наверное, неплохой человек.";
	STR_SHIPYARDER[1] = "Корабли он строит неплохие... А как о человеке, о нем трудно что-либо сказать - он живет тихо и спокойно. Наверное, неплохой человек.";
	STR_SHIPYARDER[2] = "Неплохой человек, но говорят, что он излишне суров. Постоянно отчитывает всех работников. Поэтому они часто у него меняются. Правда, не смотря на это, корабел он превосходный.";
	STR_SHIPYARDER[3] = "Он очень образованный человек. Говорят, что он учился кораблестроению в Англии, потом в Голландии. А в конце концов оказался здесь - вдали от метрополии, в захолустном архипелаге\nГоворят, что он не поладил в свое время со Святой Инквизицией, и ему пришлось бежать в колонии.";
	STR_SHIPYARDER[4] = "Да, этот старик уже никуда не годится. Он постоянно грезит о прошедших временах, и ворчит, когда ему заказывают что-нибудь, кроме каравеллы или галеона.";
	STR_SHIPYARDER[5] = "Отличный парень. Всегда готов помочь, выручить из беды. Надо сказать, что и корабли для подобного захолустья он строит очень даже неплохие.";
	STR_SHIPYARDER[6] = "Он был ссыльным в нашей колонии, пока не оказалось, что у него талант к кораблестроению. После того, как под его руководством на верфях нашей колонии были построены два великолепных брига, ему простили его прегрешения, и теперь он - полноправный член нашего общества.";

	string STR_TRADER[MAX_RUMOURS_ABOUT_OWNERS]; // Магазинщики
	STR_TRADER[0] = "Ничего особенно плохого о нем сказать не могу. Добропорядочный житель, усердный прихожанин нашей церкви. Никогда не слышал, чтобы кто-нибудь хулил его или был на него обижен.";
	STR_TRADER[1] = "Он главный поставщик нашего губернатора, и это дает ему неплохой доход. Но дела он свои ведет честно. Ну, или пока ни в чем позорящем его замечен не был.";
	STR_TRADER[2] = "Этот толстяк пользуется заслуженным уважением в нашем городе. Товар у него всегда отменный, и я не припомню случая, чтобы он кого-нибудь обсчитал.";
	STR_TRADER[3] = "Непутевый он малый. Торгует-торгует, а толку никакого. То одних товаров нет, то других. И сам из долгов никак не вылезет.";
	STR_TRADER[4] = "Нехороший он человек, мсье. Говорят, он был помощником Болдуина Коффье, но разорил его и потом перекупил магазин. Не знаю, как насчет качества товаров, которые он продает, но как человек он мне весьма неприятен.";
	STR_TRADER[5] = "О! Это мерзкий человек, я бы не советовал вам иметь с ним никаких дел\nОн держит половину жителей нашего города в должниках! А товары, которые продаются у него в магазине всегда низкого качества.";
	STR_TRADER[6] = "Да никто о нем ничего толком и не знает. Он недавно сюда переселился, и сразу открыл свое дело. Торгует вроде честно, контрабанды не возит.";

	string sTempMayor = STR_MAYOR[iRumourNum];
	string sTempTavernkeper = STR_TAVERNKEEPER[iRumourNum];
	string sTempShipyarder = STR_SHIPYARDER[iRumourNum];
	string sTempTrader = STR_TRADER[iRumourNum];

	if(sOwnerType == "Mayor") return sTempMayor;
	if(sOwnerType == "TavernKeeper") return sTempTavernkeper;
	if(sOwnerType == "ShipYarder") return sTempShipyarder;
	if(sOwnerType == "Trader") return sTempTrader;
}
