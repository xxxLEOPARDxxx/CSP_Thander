// Блад
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
    string sLocator;
    int iTime, n;
    string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

/*
	switch(Pchar.questTemp.CapBloodLine.stat)
    {
  		case "1":
            Dialog.CurrentNode = "First Bishop";
		break;

		case "2":
            Dialog.CurrentNode = "First Guard";
		break;

		case "3":
            Dialog.CurrentNode = "First Stid";
		break;

		case "4":
            Dialog.CurrentNode = "First MsStid";
		break;

    }
    */


	switch(Dialog.CurrentNode)
	{
	    // --> Бишоп
		// ----------------------------------- Диалог первый - первая встреча
		case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

        case "Exit_Away":

            LAi_SetActorTypeNoGroup(npchar);
            LAi_ActorGoToLocation(npchar, "reload", Pchar.questTemp.CapBloodLine.sLocator, "none", "", "", "", sti(Pchar.questTemp.CapBloodLine.iTime));
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

        case "Exit_RunAway":

            LAi_SetActorTypeNoGroup(npchar);
            LAi_ActorRunToLocation(npchar, "reload", Pchar.questTemp.CapBloodLine.sLocator, "none", "", "", "", sti(Pchar.questTemp.CapBloodLine.iTime));
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

        case "GFight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
            sld = &characters[GetCharacterIndex("Dragun_0")];
            LAi_SetCheckMinHP(sld, 1, true, "Dragun_0_CheckMinHP");
            LAi_SetImmortal(sld, false);
   	        LAi_SetWarriorTypeNoGroup(sld);//fix
   	        LAi_warrior_DialogEnable(sld, false);//fix
            LAi_group_MoveCharacter(sld, "TmpEnemy");
            //LAi_group_FightGroups("TmpEnemy", LAI_GROUP_PLAYER, true);
            LAi_group_Attack(sld, Pchar);
            LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);//fix
            LAi_group_SetHearRadius("TmpEnemy", 3000.0); //fix
			AddDialogExitQuest("MainHeroFightModeOn");
			//LAi_ActorRunToLocation(NPChar, "goto", "goto6", "none", "", "", "", 20);
			LAi_ActorGoToLocator(NPChar, "goto", "goto6", "", -1);

		break;

        case "fight1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
   	        LAi_SetWarriorType(NPChar);
            LAi_group_MoveCharacter(NPChar, "TmpEnemy");
            LAi_group_FightGroups("TmpEnemy", LAI_GROUP_PLAYER, true)
			AddDialogExitQuest("MainHeroFightModeOn");
			Spain_spyDie("");
			AddQuestRecord("WeaponsForEscape", "5");

		break;

        case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
   	        LAi_SetWarriorType(NPChar);
            LAi_group_MoveCharacter(NPChar, "TmpEnemy");
            LAi_group_FightGroups("TmpEnemy", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");

		break;

		case "Finish":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			RestoreBridgetown();
			initMainCharacterItem();
            ref mc = GetMainCharacter();
            mc.Ship.Type = GenerateShipExt(SHIP_ARABELLA, true, mc);
            mc.Ship.name="Арабелла";
            SetBaseShipData(mc);
            mc.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;
            SetCrewQuantityFull(mc);

            SetCharacterGoods(mc,GOOD_FOOD,2000);
        	SetCharacterGoods(mc,GOOD_BALLS,2000);//2000);
            SetCharacterGoods(mc,GOOD_GRAPES,300);//700);
            SetCharacterGoods(mc,GOOD_KNIPPELS,400);//700);
            SetCharacterGoods(mc,GOOD_BOMBS,2000);//1500);
            SetCharacterGoods(mc,GOOD_POWDER,2000);
            SetCharacterGoods(mc,GOOD_PLANKS,10);
            SetCharacterGoods(mc,GOOD_RUM,40);//600);
            SetCharacterGoods(mc,GOOD_WEAPON,2000);//2000);
            DoReloadCharacterToLocation(Pchar.HeroParam.Location, Pchar.HeroParam.Group, Pchar.HeroParam.Locator);
		break;

        case "Man_FackYou":
			dialog.text = LinkRandPhrase("Грабеж среди бела дня!!! Это что же такое делается?! Ну, погоди, приятель...", "Эй, ты чего это там копаешься?! Никак, вздумал ограбить меня? Ну, тогда тебе конец...", "Постой, ты куда это полез? Да ты вор, оказывается! Ну, считай, что ты приплыл, родной...");
			link.l1 = LinkRandPhrase("Дьявол!!", "Каррамба!!", "А-ать, черт!");
			link.l1.go = "fight_owner";
		break;
		case "fight_owner":
			LAi_SetOwnerTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			//if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NextQuest":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			Pchar.questTemp.CapBloodLine.stat = "";
            CapBloodLineInit("");
		break;







		case "First time":
        	dialog.text = "Ошибка";
            link.l1 = "...";
            link.l1.go = "Exit";
            npchar.quest.meeting = "1";

            if (npchar.id == "Pitt")
            {
     			if (bBettaTestMode)
                {
			        link.l0 = "BetaTest - пропустить и начать игру.";
			        link.l0.go = "Finish";
                }

                if (Pchar.questTemp.CapBloodLine.stat == "Begining")
                {
                    dialog.text = "Лорд Гилдой тяжело ранен... он здесь, в доме... я перетащил его туда... он послал меня за вами... Скорее к нему! Скорей!";
            		link.l1 = "Спасибо, Питт... Я пойду к нему, а ты останься тут и, если увидишь, что сюда скачут королевские драгуны, немедленно предупреди нас.";
                    link.l1.go = "Exit_Away";
                    Pchar.questTemp.CapBloodLine.sLocator = "reload1";
                    Pchar.questTemp.CapBloodLine.iTime = -1;
           			if (bBettaTestMode)
                    {
				        link.l3 = "BetaTest - Ко второму квесту.";
				        link.l3.go = "NextQuest";
                    }
            		break;
        		}

                if (Pchar.questTemp.CapBloodLine.stat == "CureMisStid")
                {
                    dialog.text = "Питер, полковник Бишоп разыскивает тебя весь вечер, у жены губернатора опять приступ. Тебе нужно срочно идти в резиденцию губернатора Стида.";
            		link.l1 = "Спасибо, Питт, он сказал мне.";
            		link.l1.go = "Exit";
            		break;
        		}
                if (Pchar.questTemp.CapBloodLine.stat == "WakerOfferComplited")
                {
                    dialog.text = "Как успехи, друг мой?";
            		link.l1 = "Говори потише, ибо на карту поставлена наша дальнейшая судьба, коллега.";
            		link.l1.go = "PStep_0";
            		break;
        		}

                dialog.text = "Извини, Питер, мне нужно идти работать.";
        		link.l1 = "Хорошо, иди.";
        		link.l1.go = "Exit";

    		}

            if (npchar.id == "Beyns")
            {
                dialog.text = "О, здравствуйте, доктор Блад, как хорошо, что вы пришли. Лорд Гилдой тяжело ранен... Он лежит сейчас в спальне на втором этаже, в западном крыле дома...";
        		link.l1 = "Я прибыл, как только смог. Я немедленно поднимусь к нему, а вы пока приготовьте горячей воды и чистого полотна.";
        		link.l1.go = "EBStep_0";
    		}

            if (npchar.id == "CapGobart")
            {
                dialog.text = "Я - капитан Гобарт из драгун полковника Кирка. Вы укрываете мятежников? Что за калека лежит на втором этаже?";
        		link.l1 = "Мы не укрываем мятежников, сэр. Этот джентльмен ранен...";
        		link.l1.go = "CGStep_1";
        		DragunInvansion4();
    		}

            if (npchar.id == "Bridgetown_Mayor" )
            {
                if( Pchar.questTemp.CapBloodLine.stat == "CureMisStid" )
                {
                    dialog.text = "Я уже хотел было послать за Вакером. Почему так долго?";
            		link.l1 = "Я вынужден был задержаться. Прошу прощения, губернатор.";
            		link.l1.go = "SStep_0";
            		link.l2 = "Ваши люди задержали меня, губернатор Стид. Как выяснилось, Ваши приказы подлежат обсуждению, и еще как - некоторые индивидуумы активно препятствуют мне в деле лечения испанских солдат.";
            		link.l2.go = "SStep_1";
            		break;
                }

                if( Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape3" )
                {
                    dialog.text = "Приветствую, доктор Блад. Чему обязан за ваш визит?";
            		link.l1 = "Добрый день, губернатор. Я принес еще профилактического экстракта для вашей супруги и хотел бы иметь возможность осмотреть ее.";
            		link.l1.go = "SStep_9";
            		break;
                }
                dialog.text = "Что вам угодно доктор Блад?";
          		link.l1 = "Нет, ничего, извините за беспокойство.";
          		link.l1.go = "Exit";
 		         NextDiag.TempNode = "First time";
    		}

    		if (npchar.id == "MisStid" && Pchar.questTemp.CapBloodLine.stat == "CureMisStid")
    		{
            	dialog.text = "О, доктор Блад! Наконец-то... пожалуйста, помогите мне!";
        		link.l1 = "Добрый вечер, миссис Стид. Не волнуйтесь, вы должны успокоиться и перестать жмуриться - потерпите и посмотрите на меня, мне нужно видеть ваши глаза.";
        		link.l1.go = "MSStep_0";
    		}

    		if (npchar.id == "Nettl" ) // && Pchar.questTemp.CapBloodLine.stat == "CureMisStid"
    		{
            	dialog.text = "Эй, парень... я в добром уме и... и... здравии. Каком здра... здравии? Ах да, трезвом... да, трезвом. Не знаешь ли, как можно исч... исчезнуть где-то, а... а потом появится где-то... где-то совсем не там, где... не там, где исчез?";
	            if( Pchar.questTemp.CapBloodLine.stat == "needMoney")
                {
                	link.l1 = "Должен признаться, что знаю как раз один подобный фокус.";
                    link.l1.go = "NStep_6";
                }
                else
                {
            		link.l1 = "Я бы и сам хотел это знать, старина.";
            		link.l1.go = "NStep_0";
                }
    		}

    		if (npchar.id == "Waker")
    		{
                if(Pchar.questTemp.CapBloodLine.stat == "CureMisStid")
                {
                	dialog.text = "Доктор Блад, как я рад вас видеть! Я искал вас сегодня, но поиски мои не увенчались успехом - вы передвигаетесь по городу, словно призрак.";
            		link.l1 = "Жизнь научила. Где я могу найти мистера Дэна?" ;
            		link.l1.go = "WStep_0";
            		link.l2 = "Добрый вечер. Где я могу найти мистера Дэна?";
            		link.l2.go = "WStep_1";
                }

                if(Pchar.questTemp.CapBloodLine.stat == "WakerOffer")
                {
                	dialog.text = "Я слышал, миссис Стид отнимает у Вас уйму времени. Что ж, молодость и привлекательная внешность, доктор Блад! Молодость и красота! Это дает врачу огромное преимущество, особенно когда он лечит дам!";
            		link.l1 = "Мне кажется, я угадываю вашу мысль. Поделитесь ею не со мной, а с губернатором Стидом. Быть может, это его позабавит. Если у вас все, то с вашего позволения..." ;
            		link.l1.go = "WStep_3";

                }
    		}

    		if (npchar.id == "Den")
    		{
            	dialog.text = "Вечер добрый, доктор Блад. Могу я узнать, что вы делали у меня дома?";
        		link.l1 = "У миссис Стид приступ мигрени, меня срочно вызвали к ней. Я осмотрел ее и вынужден был отправиться к вам в столь поздний час за необходимым лекарством. Не обнаружив вас дома, я решил подождать, но уже собирался уходить." ;
        		link.l1.go = "DStep_0";
    			if (GetCharacterItem(pchar,"migraine_potion") > 0)
    			{
            			link.l2 = "У миссис Стид приступ мигрени, меня срочно вызвали к ней. Я осмотрел ее и вынужден был отправиться к вам в столь поздний час за необходимым лекарством. Не сумев вас разыскать, я позволил себе взять лекарство без разрешения - ситуация крайне серьезная. Прошу прощения.";
            			link.l2.go = "DStep_1";
    			}
        		link.l3 = "Я просто зашел передать, что вас разыскивал доктор Вакер, мистер Дэн.";
        		link.l3.go = "DStep_2";
    		}



    		if (npchar.id == "Griffin")
    		{
                if(Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape1" && !CheckAttribute(pchar, "LockBloodWeaponsOptions"))
                {
                	dialog.text = "Какого дьявола ты вваливаешься без стука, проклятый... а, это вы, доктор Блад!";
            		link.l1 = "Добрый день, мистер Гриффин. Прошу прощения за бесцеремонное вторжение, но у меня к вам дело, не терпящее отлагательств.";
            		link.l1.go = "GRStep_0";
            		break;
                }

                if(Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape")
                {

                    dialog.text = "Ты кто такой, дьявол тебя разбери?!";
            		link.l1 = "Я доктор Блад, врач Бриджтауна." ;
            		link.l1.go = "GRStep_10";
            		break;

                }

                dialog.text = "Что ты здесь забыл, дьявол тебя разбери?!";
                link.l1 = "Я доктор Блад, уже ухожу." ;
                link.l1.go = "Exit";
    		}

    		if (npchar.id == "Hells")
    		{
                if(Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape1_1")
                {
                	dialog.text = "Какого дьявола вам всем надо?! Защищайся!..";
            		link.l1 = "Спокойно, я - Питер Блад, врач Бриджтауна. Я не причиню вам вреда.";
            		link.l1.go = "HStep_0";
            		link.l2 = "Раз уж ты просишь...";
            		link.l2.go = "fight1";
            		break;
                }

                if(Pchar.questTemp.CapBloodLine.stat == "needMoney" && !CheckAttribute(Pchar, "questTemp.CapBloodLine.fishplace"))
                {
                	dialog.text = "О, как хорошо, что ты здесь...";
            		link.l1 = "Чем могу помочь?";
            		link.l1.go = "HStep_5";
            		break;
                }

                dialog.text = "Что ты здесь забыл, дьявол тебя разбери?!";
                link.l1 = "Я доктор Блад, уже ухожу." ;
                link.l1.go = "Exit";
    		}

    		if (npchar.id == "Quest_Smuggler")
    		{
                if(Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape" && sti(Pchar.reputation) >= 50  && !CheckAttribute(pchar, "LockBloodWeaponsOptions"))
                {
                	dialog.text = "Слыхал о вас, доктор Блад. Вы стали, в какой-то мере, звездной личностью среди местных рабов, что гниют на плантациях. Чем же я могу вам услужить?";
            		link.l1 = "С вашего позволения, мы будем говорить тише. Все дело в том, что мне нужно оружие...";
            		link.l1.go = "QSStep_0";
            		break;
                }

                dialog.text = "Здравствуйте, доктор Блад, если узнают, что вы со мной разговаривали, то вас запорют до смерти. Так что вам лучшей идти своей дорогой.";
                link.l1 = "Меня могу запороть до смерти и без этого... Хотя вы правы - мне пора." ;
                link.l1.go = "Exit";
    		}

    		if (npchar.id == "Spain_spy" )
    		{
            	dialog.text = "Эй, ты! Подожди...";
        		link.l1 = "Чем могу помочь?";
        		link.l1.go = "SSStep_0";
    		}

    		 if(npchar.id == "Volverston")
    		 {
                if(Pchar.questTemp.CapBloodLine.statcrew == "find")
                {
                    dialog.text = "А-а, Питер, рад тебя видеть!";
                    link.l1 = "Не хочешь составить мне и еще нескольким нашим братьям по несчастью компанию по пути в голландскую колонию Кюрасао завтрешней ночью?";
                    link.l1.go = "VLStep_0";
              		break;
                }
                dialog.text = "А-а, Питер, рад тебя видеть!.";
                link.l1 = "Здравствуй, Волверстон. Извини, но мне нужно идти.";
                link.l1.go = "Exit";

    		 }

    		 if(npchar.id == "Hugtorp")
    		 {
                if(Pchar.questTemp.CapBloodLine.statcrew == "find")
                {
                    dialog.text = "Я уже в курсе, Питер. Джереми кратко изложил мне суть, но, увы, я вынужден отказать тебе.";
                    link.l1 = "Но почему? Ты сомневаешься в чем-то?";
                    link.l1.go = "HTStep_1";
              		break;
                }
                dialog.text = "Приветствую, Питер. Рука, которую ты мне обработал - совсем зажила, спасибо.";
                link.l1 = "Я рад, что ты поправился.";
                link.l1.go = "Exit";

    		 }

    		 if(npchar.id == "Dieke")
    		 {
                if(Pchar.questTemp.CapBloodLine.statcrew == "find")
                {
                    dialog.text = "Чем могу быть полезен вам, доктор?";
                    link.l1 = "Можешь, очень даже можешь, Николас. Питт уже рассказал тебе, что мы затеваем?";
                    link.l1.go = "DKStep_0";
              		break;
                }
                dialog.text = "Чем могу быть полезен вам, доктор?";
                link.l1 = "Нет, ничего, просто шел мимо.";
                link.l1.go = "Exit";
    		 }

    		 if(npchar.id == "Ogl")
    		 {
                if(Pchar.questTemp.CapBloodLine.statcrew == "find")
                {
                    dialog.text = TimeGreeting() + ", доктор Блад.";
                    link.l1 = "Как насчет дельца, Огл? Есть еще порох в пороховницах?";
                    link.l1.go = "OGLStep_0";
              		break;
                }
                dialog.text = TimeGreeting() + ", доктор Блад.";
                link.l1 = "Добрый.";
                link.l1.go = "Exit";
    		 }



		break;


		case "First Bishop":
            if(NPChar.quest.meeting == "0")
            {
            	dialog.text = "У жены губернатора опять приступ. Немедленно отправляйся в резиденцию Стида и делай то, что должен.\nКогда закончишь, чтоб сразу сюда... и не дай боже тебе оказаться близ испанских пациентов!\nЗавтра я найду, чем тебя занять поважнее. Есть...";
                link.l1 = "...есть Вакер и Бронсон, которых вы всегда можете порекомендовать губернатору, сославшись на мою чрезвычайную занятость на плантации. Врачи те еще, но все же люди образованные и трудолюбивые. В ином же случае, если губернатор Стид потребует доложить о состоянии раненых, я вынужден буду ему ответить, а после отправиться к беднягам и осмотреть их.";
                link.l1.go = "BStep_0";
                npchar.quest.meeting = "1";
            }
            else
            {
           	    dialog.text = "Убирайся отсюда, никчемный бездельник, а то я прикажу заковать тебя в кандалы!";
                link.l1 = "Как скажете.";
                link.l1.go = "Exit";
            }
		break;

		case "BStep_0":
        	dialog.text = "Не указывай мне, пес!\nЛечи скорее знатное семейство Стидов, или снисходительное отношение к тебе больного человека сменится холодным равнодушием политика.\nТогда посмотрим, как тебе понравится мотыжить землю на плантации вместо того, чтобы свободно шататься по городу! Помни свое место, раб.";
    		link.l1 = "Полагаю, вы многим рискуете, задерживая меня, когда миссис Стид нуждается в скорой помощи.";
    		link.l1.go = "Bishop_Away";
            LAi_LockFightMode(pchar, false);
            chrDisableReloadToLocation = false;
            LAi_LocationFightDisable(loadedLocation, false);
            Pchar.questTemp.CapBloodLine.stat = "CureMisStid";
            NextDiag.TempNode = "First Bishop";

            //сроки 4 часа
            PChar.quest.CapBloodLineTimer_1.win_condition.l1            = "Timer";
            PChar.quest.CapBloodLineTimer_1.win_condition.l1.date.hour  = 4;
            PChar.quest.CapBloodLineTimer_1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
            PChar.quest.CapBloodLineTimer_1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
            PChar.quest.CapBloodLineTimer_1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
            PChar.quest.CapBloodLineTimer_1.function = "CapBloodLine_q1_Late";
            AddQuestRecord("CapBloodLine_q1", "1");

		break;

		case "BStep_1":
        	dialog.text = "Если ты будешь совать свой нос в мои дела, мне придется кое-что предпринять, красавец, чтобы ты не лодырничал и не злоупотреблял предоставленной тебе свободой. Не забывай, что ты осужденный бунтовщик!";
            link.l1 = "Мне все время об этом напоминают.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "BStep_1";
		break;

		case "BStep_2":
        	dialog.text = "Ты шляешься без дела целыми днями! Насколько мне известно, у губернатора и его супруги все в порядке. Уж не закрыть ли тебе доступ в город до поры?";
            link.l1 = "Вы собираетесь продать Николаса Дайка?";
            link.l1.go = "BStep_3";
		break;

		case "BStep_3":
        	dialog.text = "...а то про тебя уже слухи ходят... что? Какое тебе дело до этого несчастного, пес?";
            link.l1 = "Дело в том, что у него... хм, у него первые признаки проказы...";
            link.l1.go = "BStep_4";
		break;


		case "BStep_4":
        	dialog.text = "Что ты несешь? Не смей соваться в мои дела, иначе я отправлю тебя мотыжить, предварительно выпоров до полусмерти!..";
            link.l1 = "Ответственность за продажу ляжет на...";
            link.l1.go = "BStep_5";
		break;

		case "BStep_5":
        	dialog.text = "Молчать! Я в долгу перед мистером Вестеном, и эта сделка состоится! Убирайся с глаз долой!";
            link.l1 = "Ладно.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "BStep_1";
            sld = characterFromID("Quest_Habitue");
            sld.Dialog.CurrentNode = "QHStep_0";
            AddQuestRecord("DiekeQuest", "2");

		break;

		case "Bishop_Away":

            LAi_SetActorTypeNoGroup(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "Plantation_Sp1", "goto", "goto1", "BishopOnHouse", -1);
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit()
		break;

		// -->Эндрю Бейнс

		case "EBStep_0":

            dialog.text = " Я принесу все, что вы просите. Прошу вас, поспешите, милорд совсем плох!";
        	link.l1 = "Я сделаю все, что в моих силах.";
            link.l1.go = "Exit_RunAway";
            DeleteAttribute(npchar, "talker");
            Pchar.questTemp.CapBloodLine.sLocator = "Reload5";
            Pchar.questTemp.CapBloodLine.iTime = -1;

		break;

		case "EBStep_1":

            dialog.text = "Доктор, я подготовил все, что вы просили.";
        	link.l1 = "Спасибо, поставьте там.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "EBStep_2";
            AddDialogExitQuestFunction("CureLordMovie");

		break;

		case "EBStep_2":

            dialog.text = "Что с лордом Гилдоем? Он выживет?";
        	link.l1 = "Худшее уже позади. Я обработал раны, дал лекарство, теперь он поправится, но ему нужен полный покой...";
            link.l1.go = "Exit";
            NextDiag.TempNode = "EBStep_3";
            AddDialogExitQuestFunction("DragunInvansion");

		break;

		case "EBStep_3":

            dialog.text = "Мне кажется, вам следует воспользоваться советом Джереми Питта и раздобыть себе оружие.";
        	link.l1 = "Хорошо, я так и поступлю.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "EBStep_3";

		break;

		//--> капитан Гобард

		case "CGStep_1":
        	dialog.text = "Это ясно без слов! Нет нужды спрашивать, где ранен этот проклятый мятежник... Взять его, ребята!";
    		link.l1 = "Во имя человечности, сэр! Мы  живем в Англии, а не в Танжере. Этот человек тяжело ранен, его нельзя трогать без опасности для жизни.";
    		link.l1.go = "CGStep_2";

		break;

		case "CGStep_2":
        	dialog.text = "Ах, так я еще должен заботиться о здоровье мятежников! Черт побери! Вы думаете, что мы будем его лечить? Вдоль всей дороги от Вестона до Бриджуотера расставлены виселицы, и он подойдет для любой из них. Полковник Кирк научит этих дураков-протестантов кое-чему такому, о чем будут помнить их дети, внуки и правнуки!";
    		link.l1 = "Прекрасно, но если вы это сделаете, боюсь, что завтра могут повесить вас. Он не принадлежит к категории людей, которых вы можете вздернуть, не задавая вопросов. Он имеет право требовать суда, суда пэров.";
    		link.l1.go = "CGStep_3";

		break;

		case "CGStep_3":
        	dialog.text = "Суда пэров?";
    		link.l1 = "Разумеется. Любой человек, если он не идиот или не дикарь, прежде чем посылать человека на виселицу, спросил бы его фамилию. Этот человек - лорд Гилдой.";
    		link.l1.go = "CGStep_4";

		break;

		case "CGStep_4":
        	dialog.text = "Этот человек - мятежник, и его доставят в Бриджуотер, в тюрьму.";
    		link.l1 = "Он не перенесет этого пути. Его нельзя сейчас трогать.";
    		link.l1.go = "CGStep_5";

		break;

		case "CGStep_5":
        	dialog.text = "Тем хуже для него. Мое дело - арестовывать мятежников!\nА это что за тип, который прятался в камине? Еще один вельможа? Его-то я уж точно повешу собственными руками.";
    		link.l1 = "Вы угадали, капитан. Это виконт Питт, двоюродный брат сэра Томаса Вернона, женатого на красотке Молли Кирк - сестре вашего полковника.";
    		link.l1.go = "CGStep_6";

		break;

		case "CGStep_6":
        	dialog.text = "Ты лжешь, не правда ли? Клянусь богом, он издевается надо мной!";
    		link.l1 = "Если вы в этом  уверены, то повесьте его и увидите, что с вами сделают.";
    		link.l1.go = "CGStep_7";
		break;

		case "CGStep_7":
        	dialog.text = "Дьявол. Да кто ты такой, черт бы тебя побрал? И как ты здесь очутился?";
    		link.l1 = "Мое имя Питер Блад, я врач, и меня привезли сюда для оказания помощи раненому.";
    		link.l1.go = "CGStep_8";
		break;

		case "CGStep_8":
        	dialog.text = "Ну и кто же тебя пригласил? Мятежники?\nВзять его! Свяжите и этих тоже. Мы покажем вам, как укрывать мятежников!";
    		link.l1 = "Ну, уж нет. Этого я допустить не могу!";
    		link.l1.go = "GFight";
    		NextDiag.TempNode = "CGStep_9";
			EndQuestMovie();
		break;

        case "CGStep_9":
			dialog.text = LinkRandPhrase("Вот он - держи его!", "Хватай его ребята!", "А ну стой!");
			link.l1 = LinkRandPhrase("Дьявол!!", "Как бы не так!", "А-ать, черт!");
			link.l1.go = "Exit";
			AddDialogExitQuestFunction("CapGobartAttack");
            NextDiag.TempNode = "CGStep_9";
		break;


		// -->Стражник на входе

		case "First Guard":
        	dialog.text = "Ты куда собрался?";
    		link.l1 = "Мое имя Питер Блад, я здесь по распоряжению полковника Бишопа - мне приказано явиться для осмотра и лечения супруги губернатора.";
    		link.l1.go = "GStep_0";

		break;

		case "GStep_0":

            dialog.text = "Да, припоминаю тебя. Ты лечил моего брата и прочих с ''Прайд оф Девон'', а также всю эту испанскую мразь, что чудом уцелела.\nБронсон мой друг... а ты его разоряешь, равно как и Вакера, успевая все и везде. Такие ловкачи среди рабов - редкость, и долго они не живут.";
        	link.l1 = "Прошу прощения, но в данный момент нездоровится супруге губернатора, и задерживая меня, вы рискуете оказаться в одной клетке с ''испанской мразью''.";
            link.l1.go = "Exit";
            LocatorReloadEnterDisable("BridgeTown_town", "reload3_back", false);//отпираем резеденцию
            //LocatorReloadEnterDisable("BridgeTown_town", "reload3_back", false);
            LocatorReloadEnterDisable("BridgeTown_town", "reloadR1", false);
            //солдата на место
            LAi_SetLoginTime(npchar, 6.0, 23.0);
            npchar.protector = false;
            npchar.protector.CheckAlways = 0;
            npchar.dialog.filename = "Quest\CapBloodLine\questNPC.c";

		break;

		case "GStep_1":

            dialog.text = "О, доктор Блад! На этот раз я что-то не в курсе, чтобы губернатор Стид посылал за вами. Что вам нужно?";
            if (GetCharacterItem(pchar,"migraine_potion") > 0)
            {
       	        link.l1 = "У меня на руках лекарство для профилактики мигрени. Моя задача состоит в том, чтобы доставить его миссис Стид и осмотреть ее. Вы считаете, задерживать меня в такой момент - хорошая мысль?";
                link.l1.go = "Exit";
                LocatorReloadEnterDisable("BridgeTown_town", "reload3_back", false);//отпираем резеденцию
                //LocatorReloadEnterDisable("BridgeTown_town", "reload3_back", false);
                LocatorReloadEnterDisable("BridgeTown_town", "reloadR1", false);
                //солдата на место
                npchar.protector = false;
                npchar.protector.CheckAlways = 0;
                npchar.dialog.filename = "Quest\CapBloodLine\questNPC.c";

            }
            else
            {
           	    link.l1 = "Раз уж я здесь, логично заключить, что мне нужно попасть к губернатору.";
                link.l1.go = "GStep_2";
            }

		break;

 		case "GStep_2":

            dialog.text = "Вон оно как. Но раз уж я вас остановил, логично будет заключить, что в эту дверь вам войти не удастся, пока я не узнаю о соответствующем распоряжении, отданном губернатором Стидом.";
        	link.l1 = "В таком случае, не смею более вас отвлекать.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "GStep_3";
            AddQuestRecord("WeaponsForEscape", "12");
		break;

		case "GStep_3":

            dialog.text = "Ну что еще?";
            if (GetCharacterItem(pchar,"migraine_potion") > 0)
            {
       	        link.l1 = "У меня на руках лекарство для профилактики мигрени. Моя задача состоит в том, чтобы доставить его миссис Стид и осмотреть ее. Вы считаете, задерживать меня в такой момент - хорошая мысль?";
                link.l1.go = "Exit";
                LocatorReloadEnterDisable("BridgeTown_town", "reload3_back", false);//отпираем резеденцию
                //LocatorReloadEnterDisable("BridgeTown_town", "reload3_back", false);
                LocatorReloadEnterDisable("BridgeTown_town", "reloadR1", false);
                //солдата на место
                npchar.protector = false;
                npchar.protector.CheckAlways = 0;
                npchar.dialog.filename = "Quest\CapBloodLine\questNPC.c";
                NextDiag.TempNode = "First time";

            }
            else
            {
            	link.l1 = "Проверял - жив ты или нет.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "GStep_3";
            }

		break;

        // --> Стид


 		case "SStep_0":

            ChangeCharacterReputation(PChar, 5);
            dialog.text = "Как бы там ни было, сейчас главное - моя жена. У нее опять приступ мигрени, она перевозбуждена и отвергает все попытки уложить ее в постель!";
        	link.l1 = "Могу я увидеть ее?";
            link.l1.go = "SStep_2";
		break;

 		case "SStep_1":

            dialog.text = "Как бы там ни было, сейчас главное - моя жена. У нее опять приступ мигрени, она перевозбуждена и отвергает все попытки уложить ее в постель!";
        	link.l1 = "Могу я увидеть ее?";
            link.l1.go = "SStep_2";
		break;

 		case "SStep_2":

            dialog.text = "Да-да, конечно - она в спальне на втором этаже. Вон там - дверь справа от вас и вверх по лестнице. Проходите.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "SStep_3";

			sld = GetCharacter(NPC_GenerateCharacter("MisStid", "AnnaDeLeiva", "woman", "towngirl2", 10, ENGLAND, 3, false));
            sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
			sld.name = "Миссис";
			sld.lastname = "Стид";
			sld.greeting = "Gr_Dama";
			sTemp = GetNationNameByType(ENGLAND) + "_citizens";
            LAi_group_MoveCharacter(sld, sTemp);
			LAi_SetStayTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "CommonBedroom", "goto","goto5");
			AddQuestRecord("CapBloodLine_q1", "2");
		break;


		case "SStep_3":

            sld = &characters[GetCharacterIndex("MisStid")];
            if (sld.quest.meeting != "1")
            {
                dialog.text = "Доктор Блад, осмотрите мою жену поскорее.";
                link.l1 = "Уже иду.";
                link.l1.go = "Exit";
            }
            else
            {
                dialog.text = "Как она, доктор? Вы...";
                link.l1 = "Все будет в порядке, губернатор Стид, но мне необходимо немедленно отправиться за нужными лекарствами домой к аптекарю. Просто решил поставить вас в известность.";
                link.l1.go = "SStep_4";

                link.l2 = "Все будет в порядке, губернатор Стид, если мне удастся застать дома мистера Дэна и разбудить его. Срочно нужны лекарства, и я прошу вас выдать мне средства для их покупки.";
                link.l2.go = "SStep_5";
            }
		break;

		case "SStep_4":

            dialog.text = "Прошу вас, поторопитесь!";
            link.l1 = "Уже иду.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "SStep_4";

		break;

		case "SStep_5":

            dialog.text = "О, конечно, разумеется... сколько вам нужно?";
            link.l1 = "500 пиастров.";
            link.l1.go = "SStep_6";
            link.l2 = "1000 пиастров.";
            link.l2.go = "SStep_7";
            link.l3 = "2500 пиастров, сэр. Это очень дорогой целительный экстракт.";
            link.l3.go = "SStep_8";

		break;

		case "SStep_6":

            AddMoneyToCharacter(pchar, 500);
            dialog.text = "Вот возьмите 500 пиастров.";
            link.l1 = "Я должен поспешить.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "SStep_4";
            AddQuestRecord("CapBloodLine_q1", "4");
            AddQuestUserData("CapBloodLine_q1", "iMoney", 500);

		break;

		case "SStep_7":

            AddMoneyToCharacter(pchar, 1000);
            dialog.text = "Вот, возьмите 1000 пиастров, я надеюсь, что это для мистера Дэна.";
            link.l1 = "Я должен поспешить.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "SStep_4";
            AddQuestRecord("CapBloodLine_q1", "4");
            AddQuestUserData("CapBloodLine_q1", "iMoney", 1000);

		break;

		case "SStep_8":

            AddMoneyToCharacter(pchar, 2500);
            dialog.text = "Это большая сумма, доктор. Я выдам ее, но прошу отчитаться по возвращении - я все проверю.";
            link.l1 = "Я должен поспешить.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "SStep_4";
            AddQuestRecord("CapBloodLine_q1", "5");


		break;

		case "SStep_9":

            dialog.text = "Право слово, конечно, я даю вам такую возможность. Вы считаете, следует опасаться нового приступа?";
            link.l1 = "Я прибыл сюда, чтобы предотвратить его, сэр. С вашего позволения...";
            link.l1.go = "Exit";
            NextDiag.TempNode = "First time";
            LocatorReloadEnterDisable("Bridgetown_Townhall", "reload3", false);
            LocatorReloadEnterDisable("BridgeTown_town", "reloadR1", false);
            Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape3_1";

		break;

        //--> Миссис Стид

        case "MSStep_0":

            dialog.text = "Вы можете что-то сделать, доктор?";
        	link.l1 = "Похоже, никак не обойтись без лекарств, но аптека давно закрыта. Мне придется пойти к мистеру Дэну домой, чтобы получить все необходимое. Попейте теплой воды и ждите меня, я вернусь так скоро, как только смогу!";
            link.l1.go = "Exit";
            NextDiag.TempNode = "MSStep_1";

            sld = GetCharacter(NPC_GenerateCharacter("Waker", "usurer_5", "man", "man", 7, ENGLAND, 3, false));
            sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
            sld.name = "доктор";
            sld.lastname = "Вакер";
            sld.greeting 	=  "Gr_medic";
            sTemp = GetNationNameByType(ENGLAND) + "_citizens";
            LAi_group_MoveCharacter(sld, sTemp);
			ChangeCharacterAddressGroup(sld, "CommonPirateHouse", "goto","goto6");
            LAi_SetActorTypeNoGroup(sld);
            LAi_ActorDialog(sld, pchar, "", 2.0, 0);

            pchar.quest.CureMisStid.win_condition.l1 = "item";
			pchar.quest.CureMisStid.win_condition.l1.item= "migraine_potion";
			pchar.quest.CureMisStid.function = "CapBloodLine_q1_End";

			sld = ItemsFromID("migraine_potion");
			sld.shown = true;
			sld.startLocation = "CommonPirateHouse";
			sld.startLocator = "item1";

			AddQuestRecord("CapBloodLine_q1", "3");


		break;

        case "MSStep_1":

            dialog.text = "Вы принесли лекарства, доктор?";
            if(Pchar.questTemp.CapBloodLine.stat == "CureMisStid_Complite")
            {
                link.l1 = "Да, оно быстро поставит вас на ноги.";
                link.l1.go = "MSStep_2";
                TakeItemFromCharacter(Pchar, "migraine_potion");

            }
            else
            {
                link.l1 = "Еще нет, я как раз шел за ними.";
                link.l1.go = "Exit";
            }

		break;

        case "MSStep_2":

        NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		//Вывести экран в темноту, выполнить квест questFadeOut, вернуть всё обратно, выполнить квест questFadeIn
        //LAi_Fade("", "CapBloodLine_q1_Complited");
        CapBloodLine_q1_Complited("");

		break;

        case "MSStep_3":

            dialog.text = "Здравствуйте, доктор Блад. Мне значительно лучше и, похоже, я действительно пошла на поправку - все благодаря вам.";
        	link.l1 = "Благодарю, миссис Стид. Я здесь, чтобы...";
            link.l1.go = "MSStep_4";
            DeleteAttribute(npchar, "talker");

		break;

        case "MSStep_4":

            dialog.text = "Я вижу, вы не сводите глаз с этого колечка... быть может, оно Ваше?";
        	link.l1 = "Мм... мое?";
            link.l1.go = "MSStep_5";
           	link.l1 = "Нет, увы, оно принадлежит не мне.";
            link.l1.go = "MSStep_5";

		break;

        case "MSStep_5":

            dialog.text = "Дело в том, что оно и не мое. Буквально вчера подобного кольца у меня не было, но сегодня утром я обнаружила его там, где оно находится сейчас. Эх, если бы мой муж не был уверен в том, что во время появления кольца он был со мной, и никто появиться здесь просто не мог, он бы...";
        	link.l1 = "Очень интересно.";
            link.l1.go = "MSStep_6";

		break;

        case "MSStep_6":

            dialog.text = "Колечко простенькое, без изысков. Не мой стиль, да и… забирайте его, доктор Блад. Чье бы оно ни было, мне оно ни к чему.";
        	link.l1 = "Что вы, миссис Стид! Я не могу принять его... впрочем, я могу попробовать выяснить для вас, чье оно и как сюда попало.";
            link.l1.go = "MSStep_7";

		break;

        case "MSStep_7":

            dialog.text = "Пусть будет так. А теперь я вынуждена просить вас покинуть меня.";
        	link.l1 = "Вот, я принес вам еще немного чудодейственного экстракта, что и было изначальной целью моего визита. Всего наилучшего.";
            TakeItemFromCharacter(Pchar, "migraine_potion");
            AddQuestRecord("WeaponsForEscape", "15");
            link.l1.go = "Exit";
            NextDiag.TempNode = "MSStep_8";


		break;

        case "MSStep_8":

            dialog.text = "До свидания, доктор Блад.";
        	link.l1 = "Всего доброго.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "MSStep_8";
		break;




        //--> Нэтталл

        case "NStep_0":

            dialog.text = "Э-э... если узнаешь... если способ узнаешь, то... меня не брось - я помогу. Пра... правда.";
        	link.l1 = "Отправляйся-ка домой, старый морской волк. Тебе надо поспать.";
            link.l1.go = "Nettl_Away";
            NextDiag.TempNode = "NStep_1";
            Pchar.questTemp.CapBloodLine.TalkWithNettl = true;
		break;

        case "NStep_1":

            dialog.text = "Твое здоровье, доктор! Эх-х-х!";
            if( Pchar.questTemp.CapBloodLine.stat == "needMoney")
            {
                link.l1 = "У меня к тебе есть разговор.";
                link.l1.go = "NStep_2";
            }
            else
            {
                link.l1 = "Мой тебе совет - пойди домой и проспись.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "NStep_1";
            }
		break;

        case "NStep_2":

            dialog.text = "Я в курсе, Джереми Питт уже прожужжал...";
            if(makeint(pchar.money) >= 25000)
            {
                link.l1 = "Вот тебе двадцать пять тысяч. Займись покупкой и всеми сопутствующими делами немедленно, друг. Не подведи.";
                link.l1.go = "NStep_3";
            }
            else
            {
                link.l1 = "Будь готов, как только я соберу необходимую сумму денег, ты займешься покупкой шлюпа.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "NStep_5";
            }
		break;

        case "NStep_3":

            AddMoneyToCharacter(pchar, -25000);
            dialog.text = "Ну, выбор у меня невелик... похоже.";
        	link.l1 = "Поторопись.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "NStep_4";
            NPChar.lifeDay = 0;
       		CloseQuestHeader("CapBloodLine_q2");
            CapBloodLine_q3_Complited();

		break;

        case "NStep_4":

            dialog.text = "Вот сейчас допью свой ром и пойду на верфь.";
        	link.l1 = "Поторопись.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "NStep_4";
		break;

        case "NStep_5":

            dialog.text = "Ты принес деньги?";
            if(makeint(pchar.money) >= 25000)
            {
                link.l1 = "Вот тебе двадцать пять тысяч. Займись покупкой и всеми сопутствующими делами немедленно, друг. Не подведи.";
                link.l1.go = "NStep_3";
            }
            else
            {
               	link.l1 = "Пока нет.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "NStep_5";
            }
		break;

		case "Nettl_Away":

            LAi_SetActorTypeNoGroup(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "NettlOnTavern", -1);
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
		break;

        case "NStep_6":

            dialog.text = "Ик... Силы небесные! И как это можно сделать?";
        	link.l1 = "Ну, в общем, я все возьму на себя. Тебе нужно всего-навсего пойти на верфь и купить шлюп, деньги я тебе принесу. Отправляйся в таверну, а то здесь мы очень бросаемся в глаза.";
            link.l1.go = "Nettl_Away";
            NextDiag.TempNode = "NStep_5";
            Pchar.questTemp.CapBloodLine.TalkWithNettl = true;
		break;

        //--> Вакер

        case "WStep_0":

            AddCharacterExpToSkill(pchar, "Sneak", 50);
            dialog.text = "Я бы и сам рад узнать, где он. Жду его здесь уже битый час, а его все нет и нет. Уж не сгинул ли бедняга с перепоя?\nА меж тем, у меня к вам разговор...";
        	link.l1 = "Я очень тороплюсь, доктор Вакер, мне необходимо найти мистера Дэна как можно скорее. Разговор придётся отложить.";
            link.l1.go = "WStep_2";

		break;

        case "WStep_1":

            dialog.text = "Я бы и сам рад узнать, где он. Жду его здесь уже битый час, а его все нет и нет. Уж не сгинул ли бедняга с перепоя?\nА меж тем, у меня к вам разговор...";
        	link.l1 = "Я очень тороплюсь, доктор Вакер, мне необходимо найти мистера Дэна как можно скорее. Разговор придется отложить.";
            link.l1.go = "WStep_2";

		break;

        case "WStep_2":

            dialog.text = "Что ж, я и сам не в настроении обсуждать все то, что обсудить необходимо, именно здесь и сейчас. Я, пожалуй, пойду, а вы, если угодно, дождитесь Дэна. Поговорим завтра. Как только найдете свободную минуту, приходите в таверну. Очень на вас надеюсь.";
        	link.l1 = "До свидания.";
            link.l1.go = "Exit_Away";
            Pchar.questTemp.CapBloodLine.sLocator = "reload1";
            Pchar.questTemp.CapBloodLine.iTime = 5;

            sld = GetCharacter(NPC_GenerateCharacter("Den", "usurer_1", "man", "man", 7, ENGLAND, 3, false));
            sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
            sld.name = "мистер";
            sld.lastname = "Дэн";
            sld.greeting 	=  "Gr_medic";
            sTemp = GetNationNameByType(ENGLAND) + "_citizens";
            LAi_group_MoveCharacter(sld, sTemp);
			ChangeCharacterAddressGroup(sld, "BridgeTown_town", "goto","goto3");
            LAi_SetActorTypeNoGroup(sld);
            LAi_ActorDialog(sld, pchar, "", 2.0, 0);
            AddQuestRecord("CapBloodLine_q2", "1");

		break;
		//Предложение Вакера - вторая встреча
        case "WStep_3":

            dialog.text = "Не будьте так вспыльчивы, мой друг. Вы неправильно поняли, у меня вовсе не было таких мыслей. Я хочу помочь Вам!\nВедь рабство должно быть очень неприятно для такого талантливого человека, как вы.";
        	link.l1 = "Какая проницательность!";
            link.l1.go = "WStep_4";

		break;

        case "WStep_4":

            dialog.text = "Я не дурак, дорогой коллега. Я вижу человека насквозь и могу даже сказать, что он думает.";
        	link.l1 = "Вы убедите меня в этом, если скажете, о чем думаю я.";
            link.l1.go = "WStep_5";

		break;

        case "WStep_5":

            dialog.text = "Не раз наблюдал я за вами, когда вы тоскливо всматривались в морскую даль. И вы полагаете, что я не знаю ваших мыслей?\nЕсли бы вам удалось спастись из этого ада, вы могли бы, как свободный человек, с удовольствием и выгодой для себя всецело отдаться своей профессии, украшением которой вы являетесь.\nМир велик, и, кроме Англии, есть еще много стран, где такого человека, как вы, всегда тепло встретят. Помимо английских колоний, есть и другие.\nОтсюда совсем недалеко до голландской колонии Кюрасао. В это время года туда вполне можно добраться даже на небольшой лодке. Кюрасао может стать мостиком в огромный мир. Он откроется перед вами, как только вы освободитесь от цепей.\nЧто вы на это скажете?";
        	link.l1 = "У меня нет денег, а ведь для такого путешествия их потребуется немало.";
            link.l1.go = "WStep_6";

		break;

        case "WStep_6":

            dialog.text = "Разве я не сказал, что хочу быть вашим другом?";
        	link.l1 = "Почему?";
            link.l1.go = "WStep_7";
           	link.l2 = "Это очень благородно с вашей стороны, коллега. Именно так поступил бы и я, если бы мне представился подобный случай.";
            link.l2.go = "WStep_8";

		break;

        case "WStep_7":

            dialog.text = "Вы себе не представляете, как обливается кровью мое сердце при виде коллеги, изнывающего в рабстве и лишенного возможности применить на деле свои чудесные способности! К чему вам томиться в оковах, хоть и невидимых глазу, когда вы можете отправиться к горизонту, сделать этот мир хоть капельку лучше...\nДа и нам оставить нашу работу в Бриджтауне... н-да?..";
        	link.l1 = "Для побега, помимо мужества, нужны и деньги. Шлюп обойдётся, вероятно, тысяч в двадцать.";
            link.l1.go = "WStep_9";

		break;

        case "WStep_8":

            dialog.text = "Значит, вы согласны?";
        	link.l1 = "Для побега, помимо мужества, нужны и деньги. Шлюп обойдётся, вероятно, тысяч в двадцать.";
            link.l1.go = "WStep_9";

		break;

        case "WStep_9":

            dialog.text = "Деньги вы получите! Это будет заем, который вы нам вернёте... вернете мне, когда сможете.";
        	link.l1 = "Мне необходимо подготовиться, все обдумать и согласовать с нужными людьми. Завтра мы продолжим нашу беседу. Вы приоткрыли мне двери надежды, коллега!";
            link.l1.go = "Exit";
            n = FindLocation("Bridgetown_tavern");
            locations[n].reload.l2.disable = true;
            Pchar.questTemp.CapBloodLine.stat = "WakerOfferComplited";
            AddQuestRecord("CapBloodLine_q2", "4");
            NextDiag.TempNode = "WStep_10";

		break;

        case "WStep_10":

            dialog.text = "До завтра, коллега.";
        	link.l1 = "До свидания.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "WStep_10";

		break;

		//Предложение Вакера - заключение

        case "WStep_11":

            dialog.text = "Доброе утро, доктор Блад. Я ждал вас.";
        	link.l1 = "Доброе, доктор Вакер. Что ж, я собрал людей и все необходимое. Жду только обещанных денег.";
			npchar.LifeDay = 0;
            link.l1.go = "WStep_12";

		break;

        case "WStep_12":

            dialog.text = "Все дело в том, что у меня на руках только 18 000 пиастров, а вам понадобится примерно 25 000. Тем не менее, я уверен, вы сможете раздобыть оставшуюся сумму.";
        	link.l1 = "Это будет затруднительно, но выбора у меня нет. Что насчет шлюпа? Никто из рабов не сможет просто прийти на верфь и прикупить себе шлюп, как ни в чем не бывало.";
            link.l1.go = "WStep_13";
            AddMoneyToCharacter(pchar, 18000);

		break;

        case "WStep_13":

            dialog.text = "Хм, вы, как всегда, правы, доктор. Об этом я не подумал...";
            if(Pchar.questTemp.CapBloodLine.TalkWithNettl == false)
            {
            	link.l1 = "Вы знаете кого-то, кто может помочь?";
                link.l1.go = "WStep_14";
            }
            else
            {
            	link.l1 = "Есть Нэтталл, плотник. Я видел его как-то в городе.";
                link.l1.go = "WStep_15";
            }

		break;

        case "WStep_14":

            dialog.text = "На острове есть не только невольники, но и ссыльные, люди, отбывающие ссылку за долги. Они будут счастливы расправить свои крылья. Я думаю, любой из них с радостью воспользуется возможностью уехать.";
        	link.l1 = "Благодарю, коллега!";
            link.l1.go = "Exit";
            NextDiag.TempNode = "WStep_16";
            n = FindLocation("Bridgetown_tavern");
            locations[n].reload.l2.disable = true;
            Pchar.questTemp.CapBloodLine.stat = "needMoney";
            AddQuestRecord("CapBloodLine_q2", "7");

		break;

        case "WStep_15":

            dialog.text = "Нэтталл... да, корабельный плотник может оказать содействие. Вряд ли у него найдутся причины вам отказать. Что ж, дерзайте, доктор Блад. И удачи вам!";
        	link.l1 = "Благодарю, коллега!";
            link.l1.go = "Exit";
            NextDiag.TempNode = "WStep_16";
            n = FindLocation("Bridgetown_tavern");
            locations[n].reload.l2.disable = true;
            Pchar.questTemp.CapBloodLine.stat = "needMoney";
            AddQuestRecord("CapBloodLine_q2", "7");

		break;

        case "WStep_16":

            dialog.text = "Удачи Вам!";
        	link.l1 = "Благодарю.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "WStep_16";

		break;

        //--> Мистер Дэн

        case "DStep_0":

            dialog.text = "Какой кошмар! Вот, у меня есть с собой склянка - возьмите. Сам страдаю не первый день, а потому всегда держу при себе. Но ничего, у меня запасено еще немного. Берите даром, доктор - это же мой гражданский долг!";
        	link.l1 = "Всего доброго.";
            link.l1.go = "Exit_Away";
            GiveItem2Character(Pchar, "migraine_potion");
            Pchar.questTemp.CapBloodLine.sLocator = "houseSp1";
            Pchar.questTemp.CapBloodLine.iTime = -1;

		break;

        case "DStep_1":

            dialog.text = "Что вы! На кону здоровье миссис Стид - вы правильно поступили! Поторопитесь же!";
        	link.l1 = "Всего доброго.";
            link.l1.go = "Exit_Away";
            ChangeCharacterReputation(PChar, 5);
            Pchar.questTemp.CapBloodLine.sLocator = "houseSp1";
            Pchar.questTemp.CapBloodLine.iTime = -1;

		break;

        case "DStep_2":

            dialog.text = "Хм... ясно.";
        	link.l1 = "Всего доброго.";
            link.l1.go = "Exit_Away";
            Pchar.questTemp.CapBloodLine.sLocator = "houseSp1";
            Pchar.questTemp.CapBloodLine.iTime = -1;

		break;

        case "DStep_3":

            dialog.text = "Здравствуйте, доктор Блад. Чем могу вам помочь?";
        	link.l1 = "Добрый день, мистер Дэн. Я здесь по распоряжению его превосходительства губернатора Стида. Мне срочно необходим ваш чудный экстракт для профилактики мигрени.";
            link.l1.go = "DStep_4";

		break;

        case "DStep_4":

            dialog.text = "О, конечно, вот возьмите - у меня немного осталось. Передайте поклон от меня губернатору.";
        	link.l1 = "Благодарю вас. Позвольте откланяться.";
            link.l1.go = "Exit";
            GiveItem2Character(Pchar, "migraine_potion");
            NextDiag.TempNode = "DStep_5";
            AddQuestRecord("WeaponsForEscape", "13");

		break;

        case "DStep_5":

            dialog.text = "Вам что-то необходимо?";
        	link.l1 = "Нет, спасибо.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "DStep_5";

		break;

		//--> Джереми Питт

		 case "PStep_0":

            dialog.text = "Что? О чем ты говоришь?";
        	link.l1 = "Я говорю о возможности завтрашним утром прикупить шлюп на верфи, собрать людей с плантации и из города - разумеется, исключительно тех, кому можно доверять - и отправиться к горизонту на юго-запад, к Голландской колонии Кюрасао.";
            link.l1.go = "PStep_1";

		break;

        case "PStep_1":

            dialog.text = "Не в бреду ли ты, доктор? Ни денег, ни влияния среди рабов, ни связного в городе - ничего этого у нас нет и быть не может.";
        	link.l1 = "Послушай меня, Джереми Питт. Ты - единственный штурман среди нас. Без тебя мне не добраться до нужного места, даже если я соберу людей и благополучно отплыву на шлюпе аккурат за полночь завтрашнего дня. Ты нужен мне сейчас так же, как я когда-то был нужен тебе в усадьбе Оглторпа...";
        	link.l1.go = "PStep_2";  //(+ небольшой процент авторитета)
        	link.l2 = "Хочешь ты убраться отсюда или нет?";
        	link.l2.go = "PStep_3";

		break;

        case "PStep_2":

            dialog.text = "Хорошо, я понял, я все понял. Сделаю все, что в моих силах, чтобы помочь...";
        	link.l1 = "Помни, что, выдав себя, ты погубишь все: ведь ты - единственный штурман среди нас, и без тебя бегство невозможно.";
            link.l1.go = "Exit";
            AddCharacterExpToSkill(pchar, "LeaderShip", 50);
            NextDiag.TempNode = "PStep_4";
            Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape";
            Pchar.questTemp.CapBloodLine.statcrew = "find";
            Pchar.questTemp.CapBloodLine.Officer = 0;
            AddQuestRecord("CapBloodLine_q2", "5");
            AddQuestRecord("WeaponsForEscape", "1");

		break;

        case "PStep_3":

            dialog.text = "Хорошо, я понял, я все понял. Сделаю все, что в моих силах, чтобы помочь...";
        	link.l1 = "Помни, что, выдав себя, ты погубишь все: ведь ты - единственный штурман среди нас, и без тебя бегство невозможно.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "PStep_4";
            Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape";
            Pchar.questTemp.CapBloodLine.statcrew = "find";
            AddQuestRecord("CapBloodLine_q2", "5");
            AddQuestRecord("WeaponsForEscape", "1");
		break;

        case "PStep_4":

            if(CheckAttribute(Pchar, "questTemp.CapBloodLine.Officer") && Pchar.questTemp.CapBloodLine.Officer == 4 && Pchar.questTemp.CapBloodLine.stat == "ReadyToEscape")
            {
                dialog.text = "Когда уходим, Питер?";
                link.l1 = "Я раздобыл оружие и договорился с парнями. Осталось только купить шлюп. Завтра к вечеру мы будем далеко отсюда!";
                link.l1.go = "PStep_9";
                while (GetCharacterItem(pchar,"Weapon_for_escape") > 0)//homo fix 06/02/08 отбираем все квестовое оружие
                {
                    TakeItemFromCharacter(Pchar, "Weapon_for_escape");
                }
                //link.l10 = "Продолжить игру.";
                //link.l10.go = "finish";
                NextDiag.TempNode = "PStep_10";
                break;

            }
            dialog.text = "Набери людей и подготовь все необходимое. Я буду ждать тебя здесь.";
        	link.l1 = "До встречи.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "PStep_4";
		break;

        case "PStep_5":

            dialog.text = "Питер, сюда скачут драгуны Танжерского полка, они ищут участников восстания...";
        	link.l1 = "Думаю, нам нечего бояться, ведь мы живем в христианской стране, а христиане не воюют с ранеными и с теми, кто их приютил. А вот Питту лучше куда-нибудь исчезнуть.";
            link.l1.go = "PStep_6";
            //NextDiag.TempNode = "SStep_4";

		break;

        case "PStep_6":

            dialog.text = "Хорошо, я спрячусь в каминную трубу, но ты плохо знаешь полковника Кирка, он сущий дьявол. А у тебя нет даже шпаги, чтобы постоять за себя.\nВозьми мою, я спрятал ее на балконе в сундуке. И поспеши, драгуны вот-вот ворвутся в усадьбу.";
        	link.l1 = "Спасибо, я схожу за ней, но, надеюсь, она мне не понадобится.";
            link.l1.go = "Exit_RunAway";
			//кладем ключ на стол
			sld = ItemsFromID("key3");
			sld.shown = true;
			sld.startLocation = "Estate";
			sld.startLocator = "item1";

            Pchar.questTemp.CapBloodLine.sLocator = "reload2";
            Pchar.questTemp.CapBloodLine.iTime = 5;
            AddDialogExitQuestFunction("DragunInvansion2");

		break;

        case "PStep_7":

            dialog.text = "Здравствуй, Питер. Сегодня исполняется ровно месяц, как мы работаем на сахарных плантациях полковника Бишопа. Порой мне кажется, что уж лучше бы нас казнили - так тяжело нам приходится. Все настолько истощены, что просто валятся с ног\nТолько вчера бывший кузнец из Бриджуотера в назидание остальным был насмерть запорот плетьми, а он всего лишь возмутился строгостью надсмотрщика Кента. Нужно что-то делать Питер, иначе мы не доживем и до зимы.";
        	link.l1 = "Я постоянно  думаю об этом, но просто бежать отсюда, без какой-либо поддержки извне слишком рискованно, взять хотя бы того беднягу, который осмелился  бежать две недели назад и был пойман.  Его выпороли, а после выжгли на  лбу буквы ''Б.К.'', чтобы до конца жизни все знали, что это беглый каторжник.";
            link.l1.go = "PStep_8";
        break;

        case "PStep_8":
            dialog.text = "К счастью для страдальца, он умер от побоев\nНо я пришел к тебе не жаловаться на тяготы, а чтобы сообщить, что тебя зачем-то разыскивает Бишоп. Постарайся не злить его, а то мы рискуем остаться без твоей врачебной помощи.";
        	link.l1 = "Спасибо, Питт, тогда я пойду к нему, и обещаю, что буду кроток, как овечка.";
            link.l1.go = "Exit_Away";
            Pchar.questTemp.CapBloodLine.sLocator = "reload1";
            Pchar.questTemp.CapBloodLine.iTime = -1;
            NextDiag.TempNode = "First time";
            Pchar.questTemp.CapBloodLine.stat = "";
            chrDisableReloadToLocation = false;
            AddDialogExitQuestFunction("ChangePIRATES");
		break;

        case "PStep_9":

            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
            CapBloodLine_q2_Complited();

		break;

        case "PStep_10":

            dialog.text = "Питер, тебе удалось купить шлюп?";
        	link.l1 = "Еще нет.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "PStep_10";

		break;

        case "PStep_11":

            dialog.text = "Прости, Питер, они... они выследили меня...";
        	link.l1 = "Успокойся, Питт, Хагторп все мне рассказал. Ты, наверное, полагал, будто мы обойдемся без штурмана, если дал этой  скотине Бишопу повод чуть не убить тебя?";
            link.l1.go = "PStep_12";

		break;

        case "PStep_12":

            dialog.text = "Не думаю, Питер, что штурман вообще понадобится.";
        	link.l1 = "Что, что такое?";
            link.l1.go = "PStep_13";

		break;

        case "PStep_13":

            dialog.text = "Нэтталл сбежал.";
        	link.l1 = "К черту Нэтталла! Мы что-нибудь придумаем. Выкрадем шлюп, в конце концов! Хагторп и остальные уже ждут нас в городе, нужно предупредить их, пока их не схватили!";
            link.l1.go = "PStep_14";

		break;

        case "PStep_14":

            dialog.text = "Тогда беги в город и предупреди остальных, за мной вы можете вернуться позже.";
        	link.l1 = "Жди нас тут, Питт.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "PStep_15";
            chrDisableReloadToLocation = false;
           	LAi_group_SetHearRadius("TmpEnemy", LAI_GROUP_GRD_HEAR - 3);
   	        LAi_group_SetSayRadius("TmpEnemy", LAI_GROUP_GRD_SAY - 1);
   	        LAi_group_SetLookRadius("TmpEnemy", LAI_GROUP_GRD_LOOK - 1);
            AddQuestRecord("EscapeFormBarbados", "2");

		break;

        case "PStep_15":

            dialog.text = "Беги в город!";
        	link.l1 = "Мы заберем тебя.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "PStep_15";

		break;

        case "PStep_16":

            dialog.text = "Поздравляю, Питер, ребята рассказали мне про бой с испанцами. Жаль, что меня с вами не было! Но главное что мы вырвались с этого проклятого острова!";
        	link.l1 = "Рад видеть тебя на ногах дружище. К сожалению, еще не вырвались. Нам еще нужно выйти в открытое море и решить, куда мы отправимся.";
            link.l1.go = "PStep_17";

		break;

        case "PStep_17":

            dialog.text = "Да, в Англию нам нет возврата - там нас сразу же повесят. В Испании или Голландии мы будем не в большей безопасности. То же касается и всех колоний. Остаются только французские колонии, или к пиратам.";
        	link.l1 = "Думаю, у нас еще будет время поразмыслить над этим. А сейчас нельзя терять времени, те, кто остался на берегу - не слепые и не умерли и скоро поймут, что с  кораблем что-то неладно. Нужно выбрать капитана и подготовиться к обороне.";
            link.l1.go = "PStep_18";

		break;

        case "PStep_18":

            dialog.text = "Да что тут выбирать! Все хотят, чтоб ты был нашим капитаном, Питер.";
			DeleteAttribute(pchar, "LockBloodWeaponsOptions");
        	link.l1 = "Ну, если возражений нет, тогда готовим корабль к бою. Ты будешь штурманом, Джереми, так как ты единственный из нас можешь управлять кораблем.";
            link.l1.go = "PStep_19";

		break;

        case "PStep_19":

            dialog.text = "Есть, капитан.";
        	link.l1 = "";
            link.l1.go = "Exit_RunAway";
            Pchar.questTemp.CapBloodLine.sLocator = "reloadShip";
            Pchar.questTemp.CapBloodLine.iTime = 3;

        	NPChar.Money   = 0;
        	NPChar.Payment = true;
       		NPChar.DontClearDead = true;

            AddPassenger(pchar, NPChar, false);

            Pchar.Ship.Type = GenerateShipExt(SHIP_ARABELLA, true, Pchar);
            Pchar.Ship.name="Синко Льягас";
            SetBaseShipData(Pchar);
            Pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;
            SetCrewQuantity(Pchar, GetMinCrewQuantity(Pchar));

            SetCharacterGoods(Pchar,GOOD_FOOD,70);
        	SetCharacterGoods(Pchar,GOOD_BALLS,300);//2000);
            SetCharacterGoods(Pchar,GOOD_GRAPES,100);//700);
            SetCharacterGoods(Pchar,GOOD_KNIPPELS,100);//700);
            SetCharacterGoods(Pchar,GOOD_BOMBS,200);//1500);
            SetCharacterGoods(Pchar,GOOD_POWDER,500);
//            SetCharacterGoods(Pchar,GOOD_PLANKS,10);
//            SetCharacterGoods(Pchar,GOOD_RUM,40);//600);
            SetCharacterGoods(Pchar,GOOD_WEAPON,50);//2000);

            n = FindLocation("Bridgetown_town");

            locations[n].reload.ship1.name = "reloadShip";
            locations[n].reload.ship1.go = "Barbados";
            locations[n].reload.ship1.emerge = "reload_1";
            locations[n].reload.ship1.autoreload = "1";
            locations[n].reload.ship1.label = "Sea";

            Pchar.location.from_sea = "Bridgetown_town";
            setWDMPointXZ("Bridgetown_town");

            string sQuest = "CapBloodLaspEpisode";
            pchar.quest.(sQuest).win_condition.l1 = "EnterToSea";
            pchar.quest.(sQuest).win_condition = "CapBloodLaspEpisode";
            pchar.quest.(sQuest).function = "CapBloodLaspEpisode";

            AddDialogExitQuestFunction("SpaCrewAtack");


		break;

		//-->оружейние Гриффин

        case "GRStep_0":

            dialog.text = "При всем уважении, доктор, коего вы, бесспорно, заслуживаете... провались к морскому черту ваши неотложные дела!";
        	link.l1 = "Сожалею, что застал вас не в лучшем расположении духа. Быть может, я могу вам чем-то помочь, после чего вы меня выслушаете?";
            link.l1.go = "GRStep_1";

		break;

        case "GRStep_1":

            dialog.text = "Помочь мне? Вы?! Чем может своевольный раб помочь...";
        	link.l1 = "Похоже, вы недооцениваете меня, мистер Гриффин. Что ж, вам и многим другим еще предстоит об этом пожалеть!";
            link.l1.go = "GRStep_2";
        	link.l2 = "Почему нет? Я нуждаюсь в вашей помощи и, похоже, предложить могу в данной ситуации разве что помощь взаимную.";
            link.l2.go = "GRStep_3";
		break;

        case "GRStep_2":

            AddQuestRecord("WeaponsForEscape", "4");
            dialog.text = "Убирайся прочь, доктор!";
            link.l1.go = "Exit";
            pchar.quest.PrepareToEscape2.win_condition.l1          = "location";
            pchar.quest.PrepareToEscape2.win_condition.l1.location = "Bridgetown_town";
            pchar.quest.PrepareToEscape2.function                  = "LoginSpain_spy";
        	Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape2";

		break;
        case "GRStep_3":

            dialog.text = "Что ж, посмотрим. Дело в том, что сегодня ко мне зашел испанец. Он не назвал своего имени, но я по глазам понял, что человек этот готов на все. Не знаю, откуда он взялся и как попал в город, но ему нужно было оружие. Да, доктор, я испугался... а потому не могу обратиться к властям сейчас, потому что должен был сделать это раньше. Испанец отказался ждать, пока я изготовлю заказ, и взял мои образчики со стены - несколько абордажных сабель, длинноствольный мушкет и пару пистолетов. Треклятый испанский боров!";
        	link.l1 = "...знаю, знаю - ''к морскому дьяволу''.";
            link.l1.go = "GRStep_2";
            NextDiag.TempNode = "GRStep_2";
           	link.l2 = "Он не оплатил оружие?";
            link.l2.go = "GRStep_4";

		break;
        case "GRStep_4":

            dialog.text = "К дьяволу оплату! На образчиках выгравировано мое имя! Если он вступит в бой с моим оружием в руках, кто-то обязательно это заметит… да и без боя его поймают рано или поздно! Меньше всего мне хочется кончить жизнь на рее сейчас.";
        	link.l1 = "Если вы скажете мне, куда отправился испанец, я попробую решить вашу проблему. Взамен я лишь прошу отдать мне то, что забрал этот человек.";
            link.l1.go = "GRStep_5";

		break;

        case "GRStep_5":

            dialog.text = "Оружие с моим именем на клинке у испанца или раба... да какая, к дьяволу, разница?! Мы вместе будем висеть на центральной площади завтра к рассвету!";
        	link.l1 = "Дьяволу, думаю, никакой. Хорошо. Я верну вам оружие, а вы взамен к сегодняшней ночи подготовите для меня несколько абордажных сабель и пистолетов без ваших опознавательных знаков. Идет?";
            link.l1.go = "GRStep_6";

		break;

        case "GRStep_6":

            dialog.text = "Испанский головорез выпотрошит тебя, доктор. Но меня это не касается. Верни мне образчики, и я сделаю для тебя то, что ты просишь. За полторы тысячи пиастров. Он отправился в порт к рыбаку Хелльсу, чей дом неподалеку от дома аптекаря Дэна.";
        	link.l1 = "Я скоро вернусь, любезнейший мистер Гриффин. Готовьте все необходимое.";
            link.l1.go = "GRStep_7_1";
           	link.l2 = "Не слишком ли много вы просите? Я и без того рискую жизнью ради вашей репутации. Тысяча, и ни фунтом больше.";
            link.l2.go = "GRStep_7_2";

            sld = GetCharacter(NPC_GenerateCharacter("Spain_spy", "shipowner_13", "man", "man", 7, ENGLAND, -1, false));
            sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
            sld.name = "";
            sld.lastname = "Испанец";
            GiveItem2Character(sld, "Griffins_Weapon");
            sld.SaveItemsForDead = true; // сохранять на трупе вещи
            sld.DontClearDead = true;
            LAi_SetActorTypeNoGroup(sld);
            LAi_ActorSetLayMode(sld);
            LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "CommonRoom_MH2", "goto","goto2");


            sld = &characters[GetCharacterIndex("Hells")];
            LAi_SetActorTypeNoGroup(sld);
            LAi_ActorDialog(sld, pchar, "", 1.0, 0);

		break;

        case "GRStep_7_1":

            dialog.text = "Хорошо, поторопитесь.";
        	link.l1 = "Вам не придется долго ждать.";
            link.l1.go = "Exit";
            Pchar.questTemp.CapBloodLine.iMoney = 1500;
            NextDiag.TempNode = "GRStep_8";
			Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape1_1";
            AddQuestRecord("WeaponsForEscape", "3");
            AddQuestUserData("WeaponsForEscape", "iMoney", 1500);

		break;

        case "GRStep_7_2":

            dialog.text = "Хорошо, поторопитесь.";
        	link.l1 = "Вам не придется долго ждать.";
            link.l1.go = "Exit";
            Pchar.questTemp.CapBloodLine.iMoney = 1000;
            NextDiag.TempNode = "GRStep_8";
			Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape1_1";
            AddQuestRecord("WeaponsForEscape", "3");
            AddQuestUserData("WeaponsForEscape", "iMoney", 1000);

		break;

        case "GRStep_8":

            dialog.text = "Вы пришли раньше, чем я ожидал вас увидеть. Что произошло?";
            if (GetCharacterItem(pchar,"Griffins_Weapon") > 0)
            {
            	link.l1 = "Вот ваши образчики, мистер Гриффин - все до единого. Испанский головорез более не представляет опасности.";
                link.l1.go = "GRStep_9";
                TakeItemFromCharacter(Pchar, "Griffins_Weapon");
            }
            else
            {
            	link.l1 = "Я просто зашел вас проведать.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "GRStep_8";
            }

		break;

        case "GRStep_9":

            dialog.text = "Хм... что ж, меня даже не интересует, как вам это удалось и многих ли вы убили в процессе. Сегодня через час точно такой же сверток будет готов для вас. А теперь попрошу меня оставить, предварительно, конечно, оплатив мой труд.";
            if (makeint(pchar.money) >= sti(Pchar.questTemp.CapBloodLine.iMoney))
            {
           	    link.l1 = "Да, безусловно, дорогой мистер Гриффин. Вот ваши деньги. Я зайду в назначенный час.";
                link.l1.go = "Exit";
                AddMoneyToCharacter(pchar, (-sti(Pchar.questTemp.CapBloodLine.iMoney)));
                Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape1_3";
                NextDiag.TempNode = "GRStep_12";
            }
            else
            {
           	    link.l1 = "У меня сейчас нет при себе нужной суммы, я зайду позднее.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "GRStep_13";
            }
            //Pchar.questTemp.CapBloodLine.GriffinTime = GetHour();
            SaveCurrentQuestDateParam("questTemp.CapBloodLine.GriffinTime");
            AddQuestRecord("WeaponsForEscape", "6");

		break;

        case "GRStep_10":

            dialog.text = "Да, что-то припоминаю. Но какого якоря тебе здесь надо?";
        	link.l1 = "Мне... не помешало бы кое-что из вашего ассортимента.";
            link.l1.go = "GRStep_11";

		break;

        case "GRStep_11":

            dialog.text = "Что?! Оружие... тебе?! Ты сошел с ума, морской дьявол! Убирайся!";
        	link.l1 = "";
            link.l1.go = "Exit";
            pchar.quest.PrepareToEscape2.win_condition.l1          = "location";
            pchar.quest.PrepareToEscape2.win_condition.l1.location = "Bridgetown_town";
            pchar.quest.PrepareToEscape2.function                  = "LoginSpain_spy";
        	Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape2";


		break;

        case "GRStep_12":

            if (Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape1_3" && GetQuestPastTimeParam("questTemp.CapBloodLine.GriffinTime") >= 1)
            {
                dialog.text = "Вот, возьмите, но помните - я для вас этого не делал.";
                link.l1 = "Спасибо.";
                link.l1.go = "Exit";
                GiveItem2Character(Pchar, "Weapon_for_escape");
                NextDiag.TempNode = "First time";
          		CloseQuestHeader("WeaponsForEscape");
                Pchar.questTemp.CapBloodLine.stat = "ReadyToEscape";
            }
            else
            {
                dialog.text = "Оружие для вас еще не готово, приходите позднее.";
                link.l1 = "Хорошо.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "GRStep_12";

            }

		break;

        case "GRStep_13":

            dialog.text = "Вы принесли деньги?";
            if (makeint(pchar.money) >= sti(Pchar.questTemp.CapBloodLine.iMoney))
            {
                link.l1 = "Да, вот ваши деньги. Я зайду в назначенный час.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "GRStep_12";
                AddMoneyToCharacter(pchar, (-sti(Pchar.questTemp.CapBloodLine.iMoney)));
                Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape1_3";
            }
            else
            {
           	    link.l1 = "У меня сейчас нет при себе нужной суммы, я зайду позднее.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "GRStep_13";
            }


		break;

        case "GRStep_14":

            dialog.text = "Боже правый!..";
        	link.l1 = "Не совсем. Тем не менее, я зашел узнать - быть может, вы передумали?..";
            link.l1.go = "GRStep_15";

		break;

        case "GRStep_15":

            dialog.text = "П-пе... передумал?";
        	link.l1 = "Оружие, уважаемый мистер Гриффин. Мне нужно оружие. Всего лишь несколько абордажных сабель и пара пистолетов, если вас не затруднит.";
            link.l1.go = "GRStep_16";

		break;

        case "GRStep_16":

            dialog.text = "Я... я не могу, сэр. При всем желании, меня же... повесят!";
        	link.l1 = "Успокойтесь, мне вовсе не нужно, чтобы вы что-то делали официально. Никаких опознавательных гравировок на эфесе, никаких бумаг и отчетов - все тихо и мирно. Никто и никогда не узнает о том, что это произошло.";
            link.l1.go = "GRStep_17";

		break;

        case "GRStep_17":

            dialog.text = "Ммм... ладно, хорошо. У меня есть все это, вот - возьмите. Надеюсь, этого достаточно.";
        	link.l1 = "Более чем. Премного благодарен.";
            link.l1.go = "Exit";

            GiveItem2Character(Pchar, "Weapon_for_escape");
            AddQuestRecord("WeaponsForEscape", "9");
       		CloseQuestHeader("WeaponsForEscape");
            Pchar.questTemp.CapBloodLine.stat = "ReadyToEscape";
            NextDiag.TempNode = "First time";

		break;


        //-->рыбак Хелльс

        case "HStep_0":

            dialog.text = "Врач... что тебе здесь надо?";
        	link.l1 = "Мне нужен был человек, чье бездыханное тело сейчас лежит у ваших ног.";
            link.l1.go = "HStep_1";

		break;

        case "HStep_1":

            dialog.text = "Желаешь отомстить за ублюдка-дружка? Давай, щенок!";
        	link.l1 = "Вы слишком агрессивны, мистер Хелльс. Я пропишу вам успокоительное. Дело в том, что я лишь хочу поблагодарить вас за облегчение моей задачи. Я здесь с целью извлечения кое-какого имущества, которое этот мертвый господин имел неосторожность похитить у мистера Гриффина.";
            link.l1.go = "HStep_2";

		break;

        case "HStep_2":

            dialog.text = "Я не отдам эти деньги! Ублюдок напал на меня, а вы просто хотите...";
        	link.l1 = "...забрать оружие, коим он наверняка воспользовался при нападении. Ничего больше. Его деньги по справедливости принадлежат вам.";
            link.l1.go = "HStep_3";

		break;

        case "HStep_3":

            dialog.text = "Можешь забрать, ему, я думаю, оно больше не к чему.";
        	link.l1 = "Благодарю.";
            link.l1.go = "HStep_4";
            NextDiag.TempNode = "First time";
            Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape1_2";
		break;

        case "HStep_4":

            NextDiag.CurrentNode = NextDiag.TempNode;
            sTemp = GetNationNameByType(ENGLAND) + "_citizens";
            LAi_group_MoveCharacter(NPChar, sTemp);
            LAi_SetOwnerTypeNoGroup(NPChar);
            DialogExit();
            Spain_spyDie("");
		break;

        case "HStep_5":

            dialog.text = "У меня найдется для тебя кое-какая работа, если тебе интересно. Хотя, уверен, что это вопрос глупый. Вам всем нужны деньги.";
        	link.l1 = "Сколько?";
            link.l1.go = "HStep_6";

		break;

        case "HStep_6":

            dialog.text = "Я готов заплатить тебе две тысячи за кое-какую информацию. Дело в том, что Арнольд Саммерлайт - мой конкурент - нашел какое-то место... очень рыбное место. Он разоряет меня! Узнай любой ценой, где он добывает свой улов, и я с радостью расстанусь с двумя тысячами. Идет?";
        	link.l1 = "Идет.";
            link.l1.go = "HStep_7";
           	link.l2 = "Это не для меня.";
            link.l2.go = "Exit";
            NextDiag.TempNode = "HStep_8";
		break;

        case "HStep_7":

            AddQuestRecord("FishermanQuest", "1");
            sld = &characters[GetCharacterIndex("Fisherman")];
            sld.dialog.currentnode = "FStep_1";
            NextDiag.TempNode = "HStep_9";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();

		break;

        case "HStep_8":

            dialog.text = "Так ты не поможешь мне?";
        	link.l1 = "Помогу.";
            link.l1.go = "HStep_7";
           	link.l2 = "Нет.";
            link.l2.go = "Exit";
            NextDiag.TempNode = "HStep_8";

		break;

        case "HStep_9":

            dialog.text = "Итак?";
            if(CheckAttribute(Pchar, "questTemp.CapBloodLine.fishplace"))
            {
            	link.l1 = "Я все выяснил, мистер Хелльс.";
                link.l1.go = "HStep_10";
            }
            else
            {
            	link.l1 = "Пока новостей нет.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "HStep_9";
            }

		break;

        case "HStep_10":

            dialog.text = "Не может быть! Где? Где он добывает рыбу?";
        	link.l1 = "Он забрасывает сети у мыса Раггед Пойнт.";//+Pchar.questTemp.CapBloodLine.fishplace;
            link.l1.go = "HStep_11";

		break;

        case "HStep_11":

            dialog.text = "Дьявол, как же я раньше не додумался!.. Ладно, вот твои деньги.";
        	link.l1 = "Благодарствую.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "First time";
            AddMoneyToCharacter(pchar, 2000);
       		CloseQuestHeader("FishermanQuest");
		break;


        //-->Испанский шпион

        case "SSStep_0":

            dialog.text = "Мне нужен оружейник. Где оружейник?";
        	link.l1 = "Его дом тут неподалеку. Во-о-он там.";
            link.l1.go = "SSStep_1";
           	link.l2 = "С чего это мне указывать тебе путь? Что тебе нужно от оружейника?";
            link.l2.go = "SSStep_2";
            Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape2_1";
            chrDisableReloadToLocation = false;
            LocatorReloadEnterDisable("BridgeTown_town", "houseSp2", true);

		break;

        case "SSStep_1":

            dialog.text = "*хриплый смех*";
        	link.l1 = "";
            link.l1.go = "Exit_Away";
            Pchar.questTemp.CapBloodLine.sLocator = "houseSp2";
            Pchar.questTemp.CapBloodLine.iTime = 20;
            AddQuestRecord("WeaponsForEscape", "7");

		break;

        case "SSStep_2":

            dialog.text = "Тогда проваливай, пока я тебя не выпотрошил.";
        	link.l1 = "Это было бы проблематично.";
            link.l1.go = "Exit_Away";
            Pchar.questTemp.CapBloodLine.sLocator = "houseSp2";
            Pchar.questTemp.CapBloodLine.iTime = 20;
            AddQuestRecord("WeaponsForEscape", "7");

		break;

        case "SSStep_3":

            dialog.text = "(Гриффину): Английская собака!.. Я убью каждого в этом городе, а начну с тебя, упертый старик! Ты не понимаешь, вот-вот ''Синко Льягас''... А ТЫ что тут делаешь?!";
        	link.l1 = "Позвольте вас прервать.";
            link.l1.go = "SSStep_4";
		break;

        case "SSStep_4":

            dialog.text = "Что ж, раз уж ты пришел... ты следующий!";
        	link.l1 = "Нет, пожалуй, я буду предыдущим...";
            link.l1.go = "fight";
            sld = &characters[GetCharacterIndex("Griffin")];
            sld.dialog.currentnode = "GRStep_14";

		break;

		//--> Контрабандист

        case "QSStep_0":

            dialog.text = "Стоп, стоп, стоп... просить о такой услуге немногим лучше, чем просить меня увезти вас отсюда. Причем, увозить вас с этих земель я не рискну и под страхом смерти, ибо если об этом узнают, я умру куда как более мучительно, но оружие! Надо быть человеком достаточно дерзким и немного безумным, чтобы об этом попросить в таверне, будучи привилегированным рабом. И еще большим безумцем нужно быть, чтобы согласиться помочь вам в этом...";
        	link.l1 = "Раз уж вы столь многословны, значит, интерес ваш в этом есть, осталось лишь договориться о цене.";
            link.l1.go = "QSStep_1";
		break;

        case "QSStep_1":

            dialog.text = "Вы очень проницательны, доктор. Что ж, не буду скрывать - вы правы. Меня интересует кое-что, но, боюсь, вы рискнуть не осмелитесь...";
        	link.l1 = "О чем же речь?";
            link.l1.go = "QSStep_2";
		break;

        case "QSStep_2":

            dialog.text = "Я знаю, что у вас есть доступ в усадьбу губернатора...";
        	link.l1 = "Не стоит продолжать. Я крайне тороплюсь, а шанс, что губернатору или его супруге станет сейчас же хуже, ничтожно мал. В иной ситуации дорога в усадьбу для меня закрыта.";
            link.l1.go = "QSStep_3";

		break;

        case "QSStep_3":

            dialog.text = "Уверен, ради десятка абордажных сабель и нескольких мушкетов, что имеются у меня по счастливой случайности прямо при себе, а также, скажем, трех тысяч всегда блестящих денег, вы найдете способ попасть к губернатору.";
        	link.l1 = "Что от меня требуется?.";
            link.l1.go = "QSStep_4";

		break;

        case "QSStep_4":

            dialog.text = "Небольшое колечко. Всего лишь.";
        	link.l1 = "Колечко? Оно на руке его супруги, как я думаю. И мне предстоит его снять и принести?..";
            link.l1.go = "QSStep_5";

		break;

        case "QSStep_5":

            dialog.text = "Вряд ли она носит его, мой дорогой доктор. Тем не менее, оно у нее. Маленькое золотое колечко - простое, как три пиастра, но чертовски для меня важное. Скупщик даст вам за него едва ли пятую долю того, что предлагаю я. Только не спрашивайте, почему. Просто ответьте.";
			pchar.LockBloodWeaponsOptions = true;
        	link.l1 = "Вернусь так быстро, как только смогу. Приготовьте деньги и товар.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "QSStep_6";

            sld = &characters[GetCharacterbyLocation("Bridgetown_town", "soldiers", "soldier2")];
            sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
            sld.Dialog.CurrentNode = "GStep_1";
            sld.protector = true;
            sld.protector.CheckAlways = 1 ;
            LocatorReloadEnterDisable("BridgeTown_town", "reload3_back", true);
            LocatorReloadEnterDisable("Bridgetown_Townhall", "reload3", true);
            LocatorReloadEnterDisable("BridgeTown_town", "reloadR1", true);

            sld = characterFromID("MisStid");
            sld.Dialog.CurrentNode = "MSStep_3";
        	sld.talker = 10;
            ChangeCharacterAddressGroup(sld, "Bridgetown_TownhallRoom", "barmen","bar1");

            sld = characterFromID("Den");
            LAi_SetCitizenTypeNoGroup(sld);
            //LAi_SetStayTypeNoGroup(sld);
            LAi_SetOwnerTypeNoGroup(sld);
            sld.Dialog.CurrentNode = "DStep_3";
			ChangeCharacterAddressGroup(sld, "CommonPirateHouse", "goto","goto6");

            sld = ItemsFromID("MsStid_ring");
			sld.shown = true;
			sld.startLocation = "Bridgetown_TownhallRoom";
			sld.startLocator = "item1";

            pchar.quest.PrepareToEscape3.win_condition.l1          = "location";
            pchar.quest.PrepareToEscape3.win_condition.l1.location = "Bridgetown_TownhallRoom";
            pchar.quest.PrepareToEscape3.function                  = "FindMsStid_ring";
			AddQuestRecord("WeaponsForEscape", "11");
            Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape3";

		break;


        case "QSStep_6":

            if (GetCharacterItem(pchar,"MsStid_ring") > 0)
			{
                dialog.text = "Доктор вернулся! Замечательно!";
                link.l1 = "Как вы узнали про кольцо?";
    			link.l1.go = "QSStep_7";
                link.l2 = "Вот ваша вещь. Так что с золотом и оружием?";
    			link.l2.go = "QSStep_12";
			}
			else
			{
                dialog.text = "Что-то еще?";
            	link.l1 = "Нет.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "QSStep_6";
            }

		break;

        case "QSStep_7":

            dialog.text = "Узнал? Дорогой доктор, я о нем ни малейшего понятия не имел.";
        	link.l1 = "Меня слегка озадачивает ваш ответ. Что это за кольцо? Откуда оно?";
            link.l1.go = "QSStep_8";

		break;

        case "QSStep_8":

            dialog.text = "Это колечко крайне важное для меня, но вам от него никакого толку. Мне повезло вновь обрести его, а потому я готов выполнить свою часть сделки и отдать вам все то, что обещал.";
        	link.l1 = "А может, раз уж про кольцо вы не знали, пойти и узнать про него у кого-нибудь? Быть может, мне подскажут на рыночной площади? Гляньте… как маняще оно поблескивает.";
            link.l1.go = "QSStep_10";

		break;

        case "QSStep_10":

            dialog.text = "*смеётся* Презабавный капитан Блад уже почуял вкус к жизни с новой силой... дай сюда!";
        	link.l1 = "Я считаю, сэр, вам лучше вернуть мне это колечко и объяснить, почему вы назвали меня капитаном.";
            link.l1.go = "QSStep_11";
            TakeItemFromCharacter(Pchar, "MsStid_ring");

		break;

        case "QSStep_11":

            dialog.text = "Не трать на это свое драгоценное время, Питер Блад. Вот твои деньги и оружие - поторопись. Кто знает, быть может, судьба свела нас неслучайно.";
        	link.l1 = "Что ж, ладно.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "First time";
            GiveItem2Character(Pchar, "Weapon_for_escape");
            NextDiag.TempNode = "First time";
       		CloseQuestHeader("WeaponsForEscape");
            AddMoneyToCharacter(pchar, 3000);
            AddQuestRecord("WeaponsForEscape", "16");
            CloseQuestHeader("WeaponsForEscape");
            Pchar.questTemp.CapBloodLine.stat = "ReadyToEscape";

		break;

        case "QSStep_12":

            dialog.text = "Премного благодарен. Вот ваши деньги и все необходимое. Прощайте.";
        	link.l1 = "Всего наилучшего.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "First time";
            GiveItem2Character(Pchar, "Weapon_for_escape");
            NextDiag.TempNode = "First time";
       		CloseQuestHeader("WeaponsForEscape");
            AddMoneyToCharacter(pchar, 3000);
            TakeItemFromCharacter(Pchar, "MsStid_ring");
            AddQuestRecord("WeaponsForEscape", "16");
            CloseQuestHeader("WeaponsForEscape");
            Pchar.questTemp.CapBloodLine.stat = "ReadyToEscape";

		break;

		  //--> Волверстон

        case "VLStep_0":
            dialog.text = "Я бы с радостью, но боюсь толку от меня будет немного.";
        	link.l1 = "Это еще почему?";
            link.l1.go = "VLStep_0_1";
            NextDiag.TempNode = "VLStep_1";
		break;

		case "VLStep_0_1":
            dialog.text = "За эти долгие месяцы каторги я не брал в рот ни капли, а на трезвую голову очень туго соображаю. Не мог бы ты принести мне бутылочку рома?";
			SetQuestHeader("VolversonRum");
			AddQuestRecord("VolversonRum", "1");
			pchar.SeekVolverstonRum = true;
        	link.l1 = "Похоже, у меня нет выбора. без твоего участия о побеге можно будет забыть.";
            link.l1.go = "exit";
            NextDiag.TempNode = "VLStep_0_2";
		break

		case "VLStep_0_2":
            dialog.text = "Ты принес то, что я просил?";
			if(CheckCharacterItem(pchar, "potionrum"))
			{
				link.l1 = "Вот, держи.";
				link.l1.go = "VLStep_0_3";
			}
			link.l2 = "Еще нет.";
            link.l2.go = "exit";
            NextDiag.TempNode = "VLStep_0_2";

		break;

		case "VLStep_0_3":
            dialog.text = "(Он за несколько мгновений выпивает всю бутылку до последней капли) Ох...  Так гораздо лучше. Ты говорил о побеге? Я в деле.";
			RemoveItems(PChar, "potionrum", 1);
			AddQuestRecord("VolversonRum", "2");
			CloseQuestHeader("VolversonRum");
			DeleteAttribute(pchar, "SeekVolverstonRum")
        	link.l1 = "Питт расскажет тебе все подробности. Надеюсь ты сейчас не отрубишься от опъянения и не пропустишь все веселье.";
            link.l1.go = "exit";
            NextDiag.TempNode = "VLStep_1";
            //Pchar.questTemp.CapBloodLine.Volverston = true;
            Pchar.questTemp.CapBloodLine.Officer = sti(Pchar.questTemp.CapBloodLine.Officer)+1;
		break;

        case "VLStep_1":

            dialog.text = "Дьявол, когда же уже наступит эта чертова ночь?!";
        	link.l1 = "Немного терпения, мой друг. Совсем скоро мы уберемся с этого проклятого острова.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "VLStep_1";

		break;

		 case "VLStep_11":

            dialog.text = "Неплохо я размялся! Жаль, что большая часть этих трусливых собак испанцев сейчас на берегу - вот я повеселился бы, хе-хе!";
        	link.l1 = "Если бы они все были здесь, на борту, не думаю, что нам было бы весело, мой друг.";
            link.l1.go = "VLStep_12";

		break;

        case "VLStep_12":

            dialog.text = "Да, Питер, наверное, ты как всегда прав.";
        	link.l1 = "Но я не о том хотел с тобой поговорить. Волверстон, ты хороший боец, сравнится с тобой в силе может не каждый, да и, думаю, если тебе немного походить под парусом, ты станешь отличным первым помошником. Пойдешь ко мне офицером?";
            link.l1.go = "VLStep_13";

		break;

        case "VLStep_13":

            dialog.text = "Поднять Веселый Роджер, стать свободным пиратом, проводить в море больше времени, чем на суше, каждый день риск, запах пороха, золото, ром? С огромным удовольствием!";
        	link.l1 = "Я знал, что ты согласишься.";
            link.l1.go = "Exit_RunAway";
            Pchar.questTemp.CapBloodLine.sLocator = "reloadShip";
            Pchar.questTemp.CapBloodLine.iTime = 3;

        	NPChar.Money   = 0;
        	NPChar.Payment = true;
       		NPChar.DontClearDead = true;

            AddPassenger(pchar, NPChar, false);
            AddDialogExitQuestFunction("VolverstonAdd");

		break;
        //--> Натаниэль Хагторп

        case "HTStep_0":

            dialog.text = "Это колечко крайне важное для меня, но вам от него никакого толку. Мне повезло вновь обрести его, а потому я готов выполнить свою часть сделки и отдать вам все то, что обещал.";
        	link.l1 = "А может, раз уж про кольцо вы не знали, пойти и узнать про него у кого-нибудь? Быть может, мне подскажут на рыночной площади? Гляньте… как маняще оно поблескивает.";
            link.l1.go = "HTStep_1";

		break;

        case "HTStep_1":

            dialog.text = "У меня здесь... осталось незаконченное дело, друг.";
        	link.l1 = "Значит, ты закончишь его немедленно и с моей помощью. Ты понадобишься мне в этом плавании, и я не могу позволить тебе остаться, старый морской волк.";
            link.l1.go = "HTStep_2";

		break;

        case "HTStep_2":

            dialog.text = "*смеётся* Я чертовски уважаю тебя, ты знаешь. Но это дело чести, я должен закончить то, что начал.";
        	link.l1 = "Тогда я прошу тебя поделиться со мной. Что за дело и как я могу помочь?";
            link.l1.go = "HTStep_3";

		break;

        case "HTStep_3":

            dialog.text = "Недавно сюда прибыл человек по имени Стюарт Уинтервуд. Поймешь ли ты меня - не знаю, но он - мой кровник. Из-за него я лишился всего: семьи, чести, жизни. Из-за него я попал сюда!..";
        	link.l1 = "Что произошло?";
            link.l1.go = "HTStep_4";

		break;

        case "HTStep_4":

            dialog.text = "Наплевать на прошлое! Это уже не имеет значения. Я думал, что больше никогда не увижу его лица, что та издевательская ухмылка на его лице будет моим последним воспоминанием об этом человеке... но знаешь, какое воспоминание мне хотелось бы иметь? Его искаженное мукой лицо на отрезанной голове, черт возьми!";
        	link.l1 = "Что ж, пусть будет так. Как мне его найти?";
            link.l1.go = "HTStep_5";

		break;

        case "HTStep_5":

            dialog.text = "Таверна, бордель... он где-то там, дьявол! Веселится и пьет, играет в карты! На его руке МОЕ обручальное кольцо, дома его ждет МОЯ жена! Принеси мне кольцо… вместе с пальцем.";
        	link.l1 = "При желании, ты можешь получить и его голову.";
            link.l1.go = "HTStep_13";
            NextDiag.TempNode = "HTStep_10";
        	link.l2 = "Ты уверен, что хочешь этого, Хагторп? Его смерть не облегчит твоих мук.";
            link.l2.go = "HTStep_6";
		break;

        case "HTStep_6":

            dialog.text = "Если бы я хоть на миг засомневался, что хочу его смерти, я бы не стал так уверенно о ней говорить.";
        	link.l1 = "Тем не менее, ты можешь ошибаться. Подумай, стоит ли убивать его сейчас, рискуя всем? Мы можем...";
            link.l1.go = "HTStep_7";

		break;

        case "HTStep_7":

            dialog.text = "Дьявол тебя разбери, Блад! Это дело чести, я же сказал! Боишься рисковать, не осмелишься помочь мне - не надо! Уплывешь к морскому дьяволу и без меня!";
        	link.l1 = "Хорошо, Хагторп. Я убью его.";
            link.l1.go = "HTStep_13";
           	link.l2 = "Без тебя? Едва ли возможно, но при должном умении... послушай меня. Мы можем сейчас уйти в море и начать новую жизнь, а ты рано или поздно встретишь чертового Уинтервуда и отомстишь, как захочешь, без риска для собственной шкуры. Вздернешь его на нок-рее, срубив хоть все пальцы до единого!";
            link.l2.go = "HTStep_8";
            NextDiag.TempNode = "HTStep_10";

		break;

        case "HTStep_8":

            dialog.text = "Ты... ты пытаешься отговорить меня, когда этот урод у меня под носом?!";
            if(Pchar.SPECIAL.Charisma >= 5)
            {
            	link.l0 = "Ну... да, так дело и обстоит.";
                link.l0.go = "HTStep_9";
            }
            else
            {
                AddCharacterExpToSkill(pchar, "LeaderShip", 50);
            }
           	link.l1 = "Хорошо, Хагторп. Я убью его.";
            link.l1.go = "HTStep_13";

		break;

        case "HTStep_9":

            dialog.text = "Ладно, я согласен! К черту Уинтервуда до некоторых пор. Я присоединюсь к тебе.";
        	link.l1 = "По рукам.";
            link.l1.go = "Exit";
            AddCharacterExpToSkill(pchar, "LeaderShip", 150);
            NextDiag.TempNode = "HTStep_12";
            Pchar.questTemp.CapBloodLine.Hugtorp = true;
            Pchar.questTemp.CapBloodLine.Officer = sti(Pchar.questTemp.CapBloodLine.Officer)+1;
			Pchar.HugtorpQuestFinish = true;
            AddQuestRecord("HugtorpTrouble", "2");
            CloseQuestHeader("HugtorpTrouble");

		break;
        case "HTStep_10":

            dialog.text = "Ты уже вернулся? Он мертв?";
            if (GetCharacterItem(pchar,"DOjeronRing") > 0)
            {
                link.l1 = "Мертвее некуда. Вот то, что ты просил.";
                link.l1.go = "HTStep_11";
                TakeItemFromCharacter(Pchar, "DOjeronRing");
                ref itm = ItemsFromID("DOjeronRing"); //возвращаем все как было
                BackItemName("DOjeronRing");
                BackItemDescribe("DOjeronRing");
                itm.picIndex = 2;
                itm.picTexture = "ITEMS_9";
            }
            else
            {
                link.l1 = "Нет, просто решил узнать, не передумал ли ты - по-видимому, нет.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "HTStep_10";
            }
		break;

        case "HTStep_11":

            dialog.text = "Что ж... наконец-то... я присоединюсь к твоему побегу, Блад. И спасибо тебе.";
        	link.l1 = "По рукам.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "HTStep_12";
            Pchar.questTemp.CapBloodLine.Hugtorp = true;
            Pchar.questTemp.CapBloodLine.Officer = sti(Pchar.questTemp.CapBloodLine.Officer)+1;
			Pchar.HugtorpQuestFinish = true;
            AddQuestRecord("HugtorpTrouble", "4");
            CloseQuestHeader("HugtorpTrouble");

		break;

        case "HTStep_12":

            dialog.text = "Все готово? Что от меня требуется?";
        	link.l1 = "Пока еще нет, я сообщу, когда придет время.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "HTStep_12";

		break;

        case "HTStep_13":

            LoginWinterwood();
			Pchar.HugtorpQuestStart = true;
            AddQuestRecord("HugtorpTrouble", "1");
            NextDiag.CurrentNode = "HTStep_10";
			DialogExit();

		break;

        case "HTStep_14":

            dialog.text = "Питер, дурные вести - люди полковника Бишопа выследили Джереми Питта, как раз в тот момент, когда он прятал припасы для побега. Он едва успел передать, мне, что ему удалось припрятать кое-какое оружие в сундуке между досками - на краю плантации.";
        	link.l1 = "Что с Питтом?";
            link.l1.go = "HTStep_15";
            chrDisableReloadToLocation = false;

		break;

        case "HTStep_15":

            dialog.text = "Эта свинья, Бишоп, высек его до полусмерти и велел не давать ему пищи и воды, пока он не выдаст сообщников.";
        	link.l1 = "Скверно. Бишоп зачем-то вернул меня из города, возможно, я тоже под подозрением...";
            link.l1.go = "HTStep_16";



		break;

        case "HTStep_16":

            dialog.text = "Питт держится, но тебе лучше не ходить к полковнику, он может приказать запереть тебя под замок. Лучше сейчас ничего не предпринимать - дождемся темноты. А как стемнеет, достанем оружие и освободим Джереми.";
        	link.l1 = "Да, так и поступим, я займусь освобождением Питта, а ты в суматохе проведи людей в город. Справишься?";
            link.l1.go = "HTStep_17";

		break;

        case "HTStep_17":

            dialog.text = "Да, Питер, мы будем ждать тебя на верфи. И остерегайся патрулей - люди Бишопа сейчас хватают всех без разбора.";
        	link.l1 = "Я буду аккуратен.";
            link.l1.go = "Exit";
            AddDialogExitQuestFunction("ReturnToPlantation3");
            AddQuestRecord("EscapeFormBarbados", "1");

		break;

        case "HTStep_18":

            dialog.text = "Плохие новости, Питер...";
            if(Pchar.questTemp.CapBloodLine.SpainInBridgetown == false)
            {
               	link.l1 = "Что случилось?";
                link.l1.go = "HTStep_19";
            }
            else
            {
               	link.l1 = "Я уже в курсе.";
                link.l1.go = "HTStep_20";
            }
		break;

        case "HTStep_19":

            dialog.text = "Испанцы захватили Бриджтаун. Сегодня в наш порт под чужим флагом зашел большой корабль. Это был испанский капер. Его хитрость с флагом осталась нераскрытой настолько, что, не возбудив подозрений, он преспокойно вошел в бухту и отсалютовал форту в упор бортовым залпом из двадцати пушек.";
        	link.l1 = "Вот это и называется своевременным вмешательством судьбы. Хотя один лишь дьявол знает, что из всего этого выйдет!";
            link.l1.go = "HTStep_20";
            AddQuestRecord("EscapeFormBarbados", "3");

		break;

        case "HTStep_20":

            dialog.text = "А как же наш план побега? Нэттал сбежал, шлюп теперь недостать...";
        	link.l1 = "План меняется - мы захватим другой корабль.";
            link.l1.go = "HTStep_21";

		break;

        case "HTStep_21":

            dialog.text = "Какой другой?";
        	link.l1 = "Тот, что стоит сейчас на рейде. Думаю, что большая часть экипажа сейчас бесчинствует на берегу, так что мы легко сможем захватить его.";
            link.l1.go = "HTStep_22";

		break;

        case "HTStep_22":

            dialog.text = "Тогда лучше погибнем в бою с испанцами, чем будем гнить на плантациях Бишопа! Веди нас, Питер!";
        	link.l1 = "Постараемся подобраться незаметно...";
            link.l1.go = "Exit";
            AddDialogExitQuestFunction("CapBloodOfficers");
            AddQuestRecord("EscapeFormBarbados", "4");
            NextDiag.TempNode = "HTStep_22b";

		break;

        case "HTStep_22b":

            dialog.text = "Какие приказания, Питер?";
        	link.l1 = "Все за мной, мы идем на штурм.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "HTStep_22b";
            AddDialogExitQuestFunction("CapBloodOfficers");

		break;

        case "HTStep_23":

            dialog.text = "Какой другой?";
        	link.l1 = "Тот, что стоит сейчас на рейде. Думаю, что большая часть экипажа сейчас бесчинствует на берегу, так что мы легко сможем захватить его.";
            link.l1.go = "HTStep_22";

		break;

        case "HTStep_24":

            dialog.text = "Ты был прав, Питер. Все вышло, как ты и сказал, мы овладели этим прекрасным кораблем почти без потерь.";
        	link.l1 = "Да, Хагторп, но боюсь, все только начинается. Мне кажется, ты отличный моряк. Пойдешь ко мне офицером?";
            link.l1.go = "HTStep_25";

		break;

        case "HTStep_25":

            dialog.text = "Питер, ты добрый и отзывчивый человек, слово *Честь* для тебя не пустой звук, ты прекрассный врач, таллантливый капитан и отличный лидер. Если понадобиться, я отдам за тебя жизнь.";
        	link.l1 = "Спасибо, Натаниэль, но отдать за меня жизнь у тебя еще будет время, а сейчас нам еще нужно вырваться из этого ада.";
            link.l1.go = "Exit_RunAway";
            Pchar.questTemp.CapBloodLine.sLocator = "reloadShip";
            Pchar.questTemp.CapBloodLine.iTime = 3;

        	NPChar.Money   = 0;
        	NPChar.Payment = true;
       		NPChar.DontClearDead = true;

            AddPassenger(pchar, NPChar, false);
            AddDialogExitQuestFunction("HugtorpAdd");
		break;

        //--> Николас Дайк

        case "DKStep_0":

            dialog.text = "Нет, увы, я ничего не знаю. Возможно, он еще не успел... но это уже неважно.";
        	link.l1 = "Неважно? Что случилось?";
            link.l1.go = "DKStep_1";

		break;

        case "DKStep_1":

            dialog.text = "Полковник Бишоп продает меня. Вчера в город прибыл покупатель, которому нужен раб, неплохо знакомый с морским делом. Боюсь, уже ничего нельзя сделать...";
        	link.l1 = "Правда?.. Хм. Что ж, посмотрим.";
            link.l1.go = "exit";
            NextDiag.TempNode = "DKStep_2";
            sld = characterFromID("Bishop");
            sld.Dialog.CurrentNode = "BStep_2";
            AddQuestRecord("DiekeQuest", "1");
		break;

        case "DKStep_2":

            dialog.text = "Я сожалею, что так вышло.";
        	link.l1 = "Еще не все потерянно, Ник.";
            link.l1.go = "exit";
            NextDiag.TempNode = "DKStep_2";
		break;

        case "DKStep_3":

            dialog.text = "Недавно от покупателя приходил какой-то врач, он осматривал меня... похоже, сделка вот-вот состоится.";
        	link.l1 = "Успокойся, Николас. Золото, предназначенное для покупки тебя, уже перешло ко мне по наследству. Ты отправляешься с нами завтра ночью.";
            link.l1.go = "exit";
            Pchar.questTemp.CapBloodLine.Dieke = true;
            Pchar.questTemp.CapBloodLine.Officer = sti(Pchar.questTemp.CapBloodLine.Officer)+1;
            NextDiag.TempNode = "DKStep_4";
            CloseQuestHeader("DiekeQuest");

		break;

        case "DKStep_4":

            dialog.text = "Я жду, не дождусь завтрашней ночи!";
        	link.l1 = "Я тоже, Ник.";
            link.l1.go = "exit";
            NextDiag.TempNode = "DKStep_4";

		break;

        case "DKStep_5":

            dialog.text = "Не думал, что на пути к свободе придется пролить столько крови.";
        	link.l1 = "Николас, ты славный парень, из тебя выйдет толковый офицер. Пойдешь с нами?";
            link.l1.go = "DKStep_6";

		break;

        case "DKStep_6":

            dialog.text = "Если честно, я даже не знаю что делать... Я хотел оставить море, осесть на суше, найти достойную жену и зажить спокойной жизнью. Теперь в Англию возврата нет, с Испанией и Голландией та же ситуация, остаеться только Франция, но там нет ничего, что держало бы меня, никого, кто помог бы выжить в этом жестоком мире.\nНа плантациях же я успел подружиться с тобой, Питтом и другими невольниками. Я пойду к тебе на службу, но когда прийдет время и я все же решусь поселиться на берегу, не держи меня.";
        	link.l1 = "Хорошо, я учту это. А теперь иди готовься, мы все еще не на свободе.";
            link.l1.go = "Exit_RunAway";
            Pchar.questTemp.CapBloodLine.sLocator = "reloadShip";
            Pchar.questTemp.CapBloodLine.iTime = 3;

        	NPChar.Money   = 0;
        	NPChar.Payment = true;
       		NPChar.DontClearDead = true;
			NPChar.model = "PBLine_Daik_0";
			FaceMaker(NPChar);

            AddPassenger(pchar, NPChar, false);
            AddDialogExitQuestFunction("DiekeAdd");
		break;

        //--> Нед Огл

        case "OGLStep_0":

            dialog.text = "Ты о чем, дьявол тебя разбери?";
        	link.l1 = "Я о чудесной возможности взять курс на Кюрасао завтрашней ночью.";
            link.l1.go = "OGLStep_1";

		break;

        case "OGLStep_1":

            dialog.text = "Удрать от Бишопа? Ты считаешь, это так просто? Он не только плантатор-садист, он и командир барбадосской милиции по совместительству...";
        	link.l1 = "Мне известно обо всем этом. Но мне также известно, что кое-кто очень хочет нам помочь. Так хочет, что даже предоставит средства на шлюп.";
            link.l1.go = "OGLStep_2";
		break;

        case "OGLStep_2":

            dialog.text = "Что ж, тогда я могу только позавидовать тебе и твоим подельникам...";
        	link.l1 = "Не унывай, мой одноглазый друг. Я здесь, чтобы предложить тебе отправиться с нами.";
            link.l1.go = "OGLStep_3";
		break;

        case "OGLStep_3":

            dialog.text = "Питер, как бы мне этого ни хотелось, я не могу.";
        	link.l1 = "В чем проблема?";
            link.l1.go = "OGLStep_4";
		break;

        case "OGLStep_4":

            dialog.text = "Эх-х-х... проблема в деньгах.";
        	link.l1 = "Деньги? Но...";
            link.l1.go = "OGLStep_5";
		break;

        case "OGLStep_5":

            dialog.text = "Я взял заем некоторое время назад. Ростовщик сжалился надо мной, а мне это было очень нужно. Он помог мне, а я уже не в том возрасте, чтобы быть таким равнодушным\nНе хочу иметь за спиной долги.";
        	link.l1 = "Но как ты выбрался с территории?";
            link.l1.go = "OGLStep_6";
		break;


        case "OGLStep_6":

            dialog.text = "Я не выбирался, он был здесь - приходил зачем-то к полковнику.";
        	link.l1 = "Ладно, ладно... я не могу уйти без канонира, а кроме тебя, я никого тут не найду. Сколько ты должен?";
            link.l1.go = "OGLStep_7";
		break;

        case "OGLStep_7":

            dialog.text = "Я должен пять тысяч, так что забудь, друг. Чтобы добраться до Кюрасао, тебе не понадобится канонир.";
        	link.l1 = "Что ж, посмотрим.";
            link.l1.go = "Exit";
            NextDiag.TempNode = "OGLStep_8";
            Pchar.questTemp.CapBloodLine.Ogl = false;
            AddQuestRecord("OglQuest", "1");

		break;

        case "OGLStep_8":

            if(CheckAttribute(Pchar, "questTemp.CapBloodLine.Ogl") && Pchar.questTemp.CapBloodLine.Ogl == true)
            {
                dialog.text = "Да, Питер?";
            	link.l1 = "Твой долг погашен, Огл. Теперь я не потерплю отказа.";
                link.l1.go = "OGLStep_9";
            }
            else
            {
                NextDiag.TempNode = "OGLStep_8";
                dialog.text = "Да, Питер?";
            	link.l1 = "Нет, я уже ухожу.";
                link.l1.go = "Exit";
                NextDiag.TempNode = "OGLStep_8";
            }
		break;

        case "OGLStep_9":

            dialog.text = "Что? Ты отдал за меня деньги?";
        	link.l1 = "Жди моих распоряжений завтра к вечеру.";
            link.l1.go = "exit";
            Pchar.questTemp.CapBloodLine.Ogl = true;
            Pchar.questTemp.CapBloodLine.Officer = sti(Pchar.questTemp.CapBloodLine.Officer)+1;
            NextDiag.TempNode = "OGLStep_10";
            AddQuestRecord("OglQuest", "3");
            CloseQuestHeader("OglQuest");

		break;

        case "OGLStep_10":

            dialog.text = "Какие будут распоряжения?";
        	link.l1 = "Пока никаких, Нед.";
            link.l1.go = "exit";
            NextDiag.TempNode = "OGLStep_10";

		break;

        case "OGLStep_11":

            dialog.text = "Жаркая была схватка, капитан. Давно уже я так не рубился, как сегодня.";
        	link.l1 = "Нед, если не ошибаюсь, ты когда-то был канониром на королевском флоте?";
            link.l1.go = "OGLStep_12";

		break;

        case "OGLStep_12":

            dialog.text = "В течение пятнадцати лет я был лучшим канониром на всем флоте его величества!";
        	link.l1 = "Тогда, раз уж я капитан этого судна, пойдешь ко мне старшим канониром?";
            link.l1.go = "OGLStep_13";

		break;

        case "OGLStep_13":
            dialog.text = "Если честно, я даже не знаю что делать... Я хотел оставить море, осесть на суше, найти достойную жену и зажить спокойной жизнью. Теперь в Англию возврата нет, с Испанией и Голландией та же ситуация, остаеться только Франция, но там нет ничего, что держало бы меня, никого, кто помог бы выжить в этом жестоком мире.\nНа плантациях же я успел подружиться с тобой, Питтом и другими невольниками. Я пойду к тебе на службу, но когда прийдет время и я все же решусь поселиться на берегу, не держи меня.";
        	link.l1 = "Хорошо, я учту это. А теперь иди готовься, мы все еще не на свободе.";
            link.l1.go = "Exit_RunAway";
            Pchar.questTemp.CapBloodLine.sLocator = "reloadShip";
            Pchar.questTemp.CapBloodLine.iTime = 3;

        	NPChar.Money   = 0;
        	NPChar.Payment = true;
       		NPChar.DontClearDead = true;

            AddPassenger(pchar, NPChar, false);
            AddDialogExitQuestFunction("OglAdd");

		break;

	}
}
