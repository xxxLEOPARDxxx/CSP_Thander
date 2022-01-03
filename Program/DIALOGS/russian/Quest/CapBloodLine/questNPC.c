// Блад
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
    string sLocator, sTemp;
    int iTime, n, iChar;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);




	switch(Dialog.CurrentNode)
	{

		// ----------------------------------- Диалог первый - первая встреча
		case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

        case "Exit_Away":

            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(npchar, "reload", Pchar.questTemp.sLocator, "none", "", "", "", sti(Pchar.questTemp.iTime));
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

        case "Exit_RunAway":

            LAi_SetActorTypeNoGroup(npchar);
            LAi_ActorRunToLocation(npchar, "reload", Pchar.questTemp.sLocator, "none", "", "", "", sti(Pchar.questTemp.iTime));
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;




        case "sfight":

			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
            LAi_group_Attack(NPChar, Pchar);

		break;

        case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
   	        LAi_SetWarriorTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
            AddDialogExitQuest("MainHeroFightModeOn");
			chrDisableReloadToLocation = false;
            LAi_CharacterPlaySound(npchar, "toArm");

		break;

        case "Qfight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
   	        LAi_SetWarriorType(NPChar);
            LAi_group_MoveCharacter(NPChar, "TmpEnemy");
			LAi_group_FightGroups("TmpEnemy", LAI_GROUP_PLAYER, true);
			LAi_group_FightGroups(GetNationNameByType(ENGLAND) + "_citizens", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			chrDisableReloadToLocation = true;
			//#20190120-03
			LAi_group_SetCheck("TmpEnemy", "OpenTheDoors");

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
			link.l1.go = "Qfight";
		break;

        case "Draguns_0":
			dialog.text = LinkRandPhrase("Вот он - держи его!", "Хватай его ребята!", "А ну стой!");
			link.l1 = LinkRandPhrase("Дьявол!!", "Как бы не так!", "А-ать, черт!");
			link.l1.go = "Draguns_1";
 		     NextDiag.TempNode = "Draguns_0";
		break;

        case "Draguns_1":

            LAi_group_FightGroups("TmpEnemy", LAI_GROUP_PLAYER, true);
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();

		break;

		case "First time":
        	dialog.text = "Ошибка";
            link.l1 = "...";
            link.l1.go = "Exit";


            if (CheckAttribute(npchar, "CityType") && npchar.CityType == "soldier")
            {

                if(Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape2_1")
                {
                    dialog.text = "Проходи своей дорогой и не отвлекай меня.";
					link.l1 = "Боюсь, дело серьезное. В город попал испанский лазутчик, возможно даже, наемник. Он отправился в дом оружейника, и сейчас дверь к Гриффину наглухо закрыта.";
					link.l1.go = "SQStep_0";
					Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape2_2";
				    break;
                }

               	if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY || ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -15)
                {

    				dialog.text = RandPhraseSimple("Стой! Сдать оружие! Следовать за мной!", "Беглый раб! Немедленно схватить его!");
    				link.l1 = RandPhraseSimple("Заткнись, малахольный!", "Как бы не так!");
    				link.l1.go = "sfight";
    				break;
				}

        		switch (rand(5))
					{
						case 0: ////////////////////////////////////////
							dialog.text = "С чего это раб шатается тут без дела?";
							link.l1 = "Я выполняю поручение полковника Бишопа.";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = "А, это вы, доктор Блад. Вы лечили меня, когда меня списали с ''Прайд оф Девон''";
							link.l1 = "Я рад, что ты поправился.";
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = "Пшел прочь, раб!";
							link.l1 = "Я тоже рад тебя видеть, кто б ты ни был.";
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = "Какая погода, а я вынужден стоять здесь. Мое единственное развлечение заключается в отгонянии мух от своего лица.";
							link.l1 = "Сочувствую. Но ничем не могу помочь, работа у тебя такая.";
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = "Если тебе хочется поболтать, то найдите себе кого-нибудь другого, а лучше возвращайся на плантации.";
							link.l1 = "Непременно.";
							link.l1.go = "exit";
						break;



						case 5: ////////////////////////////////////////////
							dialog.text = "Проходи своей дорогой и не отвлекай меня.";
							link.l1 = "Как скажешь, солдат.";
							link.l1.go = "exit";
						break;


					}
    		}

    		if (CheckAttribute(npchar, "CityType") && npchar.CityType == "citizen")
    		{
            	dialog.text = TimeGreeting() + ", доктор.";
        		link.l1 = "Здравствуйте.";
        		link.l1.go = "Exit";
        		if( Pchar.questTemp.CapBloodLine.stat == "WakerOffer")
        		{
                    link.l2 = RandPhraseSimple("Не подскажете, где мне найти доктора Вакера?", "Мне нужен доктор Вакер. Не видели его?");
                    link.l2.go = "Citizen_0";
                }
                if(CheckAttribute(Pchar, "questTemp.CapBloodLine.ShipForJack") && Pchar.questTemp.CapBloodLine.ShipForJack == true)
                {
                    Link.l2 = RandPhraseSimple("Надо бы кое-куда добраться - не подскажете достойного капитана?", "Я ищу капитана, который доставит моего друга кое-куда за умеренную плату. Нет ли кого на примете?");
    				Link.l2.go = "Citizen_1";
                }
    		}

    		if (CheckAttribute(npchar, "CityType") && npchar.CityType == "citizen" && npchar.location.group == "merchant")
    		{
                if(findsubstr(Pchar.questTemp.CapBloodLine.stat, "PrepareToEscape" , 0) != -1)
                {
                        if (CheckAttribute(npchar, "quest.bGoodMerch") && sti(Pchar.reputation) >= 55)
                        {
                            dialog.text = "О, доктор Блад, здравствуйте! Я так и не поблагодарил"+NPCharSexPhrase(NPChar, " ", "а ")+" вас тогда за спасение моего маленького сына, о чем до сих пор часто вспоминаю и сожалею. Как славно, что я встретил вас сегодня!";
                            link.l1 = "Действительно, как славно, что люди стремятся отблагодарить в самый подходящий момент. Не подскажешь ли, "+NPCharSexPhrase(NPChar, "дорогой друг ", "моя дорогая ")+", где я могу в кратчайшие сроки разжиться несколькими абордажными саблями и парой-тройкой пистолетов без лишнего шума и возни?";
                            link.l1.go = "Merchant_0";
                            break;
                        }
                }
                if (CheckAttribute(npchar, "quest.bGoodMerch"))
                {
                    dialog.text = TimeGreeting() + ", доктор.";
                    link.l1 = "Здравствуйте.";
                }
                else
                {
                    dialog.text = "Ты мне товар загораживаешь. А ну пшел, падаль рабская!";
                    link.l1 = "Уже ухожу.";
                }
        		link.l1.go = "Exit";
				if (CheckAttribute(pchar, "SeekVolverstonRum") && !CheckCharacterItem(pchar, "potionrum") && !CheckAttribute(npchar, "VolverstonRum_fail") && !CheckAttribute(npchar, "quest.bGoodMerch"))
				{
					link.l2 = "У вас случаем нет в продаже бутылочки рома?";
                    link.l2.go = "Merchant_VolverstonRum";
				}
    		}
    		//Рабы на плантациях - постоянный диалог
    		if (CheckAttribute(npchar, "CityType") && npchar.CityType == "citizen" && findsubstr(npchar.id, "Slave_" , 0) != -1)
    		{
			    dialog.text = RandPhraseSimple(RandPhraseSimple("Я так устал - просто с ног валюсь.", "Нет больше сил так жить!"), RandPhraseSimple("Эта работа слишком тяжелая для меня.", "Надсмотрщики уже не оставили живого места на моей шкуре!"));
				if(CheckAttribute(pchar,"GenQuest.CaptainComission") && pchar.GenQuest.CaptainComission.GetSlave == "NoSlave")
				{
					link.l1 = RandPhraseSimple("Да, жизнь в неволе это тяжёлое испытание. А скажи, нет ли среди вас " + pchar.GenQuest.CaptainComission.SlaveName + "?","Да, тебе не позавидуешь... Где-то на плантации должен работать невольник по имени " + pchar.GenQuest.CaptainComission.SlaveName + ". Ты с ним случайно не знаком?");
					link.l1.go = "CapComission_1";
				}
				else
				{
					link.l1 = RandPhraseSimple("Сочувствую, приятель.", "Мне жаль тебя.");
					link.l1.go = "exit";
				}
    		}

    		if (npchar.id == "Bridgetown_Poorman")
    		{
            	dialog.text = "Эй, парень, подкинь монетку... А, это вы, доктор Блад.";
        		link.l1 = "Удачи.";
        		link.l1.go = "Exit";
    		}

    		if (npchar.id == "QuestCitiz_Bridgetown")
    		{
            	dialog.text = TimeGreeting() + ", доктор.";
        		link.l1 = "И вам.";
        		link.l1.go = "Exit";
    		}

    		if (npchar.id == "SolderTakeBlades")
    		{
                dialog.text = RandPhraseSimple("С каких это пор рабы разгуливают, где попало, с оружием?", "Ты же раб полковника Бишопа, почему ты вооружен?");
        		link.l1 = RandPhraseSimple("Э-э-э...", "Сам не пойму...");
        		link.l1.go = "STBStep_0";
    		}

    		if (npchar.id == "Winterwood")
    		{

                if(npchar.location == "Bridgetown_Brothel_room")
                {
                    dialog.text = "Какого черта тебе здесь надо?! Убирайся немедленно!";
                    link.l1 = "Прошу прощения, но эта женщина моя.";
                    link.l1.go = "WWStep_7";
                    break;
                }
                dialog.text = "Какого черта тебе здесь надо?! Убирайся немедленно!";
        		link.l1 = "Не нужно мне грубить! У меня к вам дело.";
        		link.l1.go = "WWStep_0";
    		}

    		if (npchar.id == "Quest_Habitue")
    		{
				dialog.text = "И-ик! О, парень, ты выглядишь бывалым морским волком! Может, купишь мне стаканчик рома?";
				link.l1 = "Может я и морской волк, только это не значит, что я буду поить всякую рвань...";
				link.l1.go = "exit";
    		}

    		if (npchar.id == "Weston")
    		{
				dialog.text = "Пошел прочь из моего дома!";
				link.l1 = "Уже ухожу.";
				link.l1.go = "exit";
    		}

    		if (npchar.id == "MoneySpy")
    		{
                if(npchar.quest.meeting == "1")
                {
                    dialog.text = "Проваливай!";
    				link.l1 = "Уже ухожу.";
    				link.l1.go = "exit";
                }
                else
                {
                    npchar.quest.meeting = "1";
                    dialog.text = "Наконец-то! Я уже думал, ты не придешь! Так, кх-м, тебе удалось узнать что-нибудь?";
    				link.l1 = "Вы меня приняли за кого-то другого.";
    				link.l1.go = "MSStep_0";
    				link.l2 = "Э-э-м-м... да, разумеется.";
    				link.l2.go = "MSStep_1";
                }
    		}

    		if (npchar.id == "Fisherman")
    		{
                dialog.text = "Не поставишь мне стаканчик, а? Ик..";
    			link.l1 = "Не думаю.";
                link.l1.go = "exit";
    		}

    		if (npchar.id == "QStranger")
    		{
                dialog.text = "Что вам нужно?";
    			link.l1 = "Я здесь, чтобы узнать, не собрался ли ты покинуть город, позабыв о том, что должен тридцать тысяч кое-кому?";
                link.l1.go = "QSTStep_0";
    			link.l2 = "Эй, старина, ты чего? Совсем меня позабыл?";
                link.l2.go = "QSTStep_1";
    			link.l3 = "Боюсь, положение твое серьезное. Твой обман, э-э... Раф, был раскрыт. Если ты немедленно не вернешь 30 000 ростовщику, тебя вздернут сегодня же!";
                link.l3.go = "QSTStep_2";
    		}


		break;

		case "CapComission_1":
			dialog.text = "Ему сегодня не повезло. Беднягу высекли и заковали в кандалы. Вы можете найти его во дворе казармы. Боюсь, он долго не протянет на таком солнцепёке...";
			link.l1 = "Спасибо, приятель.";
			link.l1.go = "exit";
		break;


		case "Citizen_0":

            if (!CheckAttribute(npchar, "quest.btmp"))
            {
                npchar.quest.btmp = true;
                if(rand(3)==2)
                {
                    dialog.text = LinkRandPhrase("Рысью в таверну пробежал - там ищи. Не забудь посмотреть под столами.", "Недавно зашел в таверну, вроде. Если правильно помню, не выходил.", "Заскочил в кабак только что... с похмелья, что ли?");
                    link.l1 = "Спасибо.";
                    link.l1.go = "Exit";
                }
                else
                {
                    dialog.text = RandPhraseSimple(RandPhraseSimple("Не знаю, сгинь!", "Ничем не могу помочь."), RandPhraseSimple("А ну пшел, падаль рабская!", "А кто это? Я знаю только доктора Блада... а, это вы, здравствуйте."));
                    link.l1 = "Спасибо.";
                    link.l1.go = "Exit";
                }

            }
            else
            {
                dialog.text = "Доктор, вы уже спрашивали у меня об этом.";
                link.l1 = "Извините.";
                link.l1.go = "Exit";
            }

		break;

		case "Citizen_1":

            dialog.text = LinkRandPhrase("Ничем не могу вам помочь.", "При всем уважении, доктор, в вашем положении не стоит об этом спрашивать.", "Увы, мне некого вам порекомендовать, доктор Блад.");
            link.l1 = "Спасибо.";
            link.l1.go = "Exit";

		break;

		case "Merchant_VolverstonRum":

        	dialog.text = "Есть. С тебя пятьсот монет.";
			if (pchar.money >= 500)
			{
				link.l1 = "Вот. Давайте её сюда.";
				link.l1.go = "Merchant_VolverstonRum_1";
			}
			link.l2 = "Что же так дорого то? Я еще вернусь.";
    		link.l2.go = "exit";

		break;

		case "Merchant_VolverstonRum_1":
			AddMoneyToCharacter(pchar, -500);
        	dialog.text = "Погоди-ка. А откуда это у раба взялись такие деньги? Ничего я тебе не дам. Считай, что это было платой за молчание. А теперь проваливай, а не то стражу позову!";
    		link.l1 = "Послушайте, мне очень нужна эта бутылка. Вопрос жизни и смерти.";
    		link.l1.go = "Merchant_VolverstonRum_2";
		break;
		case "Merchant_VolverstonRum_2":
        	dialog.text = "Ладно. Плати еще тысячу, или проваливай.";
			if (pchar.money >= 1000)
			{
				link.l1 = "На, подавись ты уже своими деньгами!";
				link.l1.go = "Merchant_VolverstonRum_3";
			}
			else
			{
				link.l1 = "Но у меня столько нет...";
				link.l1.go = "Merchant_VolverstonRum_2_1";
			}

		break;

		case "Merchant_VolverstonRum_2_1":
			npchar.VolverstonRum_fail = true;
        	dialog.text = "В таком случае - пшёл вон! И не спрашивай меня больше.";
    		link.l1 = "И не подумаю.";
    		link.l1.go = "exit";

		break;

		case "Merchant_VolverstonRum_3":
			npchar.VolverstonRum_fail = true;
			AddMoneyToCharacter(pchar, -1000);
			TakeNItems(PChar, "potionrum", 1);
        	dialog.text = "Ха, да у тебя, небось, еще деньги остались? Ладно, забирай свою бутылку. И не надоедай мне больше, раб.";
    		link.l1 = "Да я к вам теперь и на пушечный выстрел не подойду.";
    		link.l1.go = "exit";

		break;

		case "Merchant_0":

        	dialog.text = "Я не буду спрашивать, для чего это вам понадобилось, и если меня спросят, мне не придется лгать и выкручиваться. Тем не менее, отчет с меня попросят не ранее чем послезавтра, так что...";
    		link.l1 = "Послезавтра вы уже сможете смело заявить, что предоставили в безвозмездное пользование несколько сабель и пистолетов доктору Питеру Бладу, что был в Бриджтауне доктором. Вряд ли полковник Бишоп будет против...";
    		link.l1.go = "Merchant_1";

		break;

		case "Merchant_1":

        	dialog.text = "Мой сын обязан вам жизнью, впрочем, как и я. Вот, возьмите, доктор Блад. И удачи вам!";
    		link.l1 = "Премного благодарен.";
    		link.l1.go = "Exit";
            NextDiag.TempNode = "Merchant_2";
            if (Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape") Pchar.questTemp.CapBloodLine.stat = "ReadyToEscape";//fix чтоб не сбивать
            GiveItem2Character(Pchar, "Weapon_for_escape");                                                                 //уже начатые варианты
            AddQuestRecord("WeaponsForEscape", "10");
    		CloseQuestHeader("WeaponsForEscape");

		break;

		case "Merchant_2":

        	dialog.text = "И удачи вам, доктор Блад!";
    		link.l1 = "Благодарю.";
    		link.l1.go = "Exit";
    		NextDiag.TempNode = "Merchant_2";

		break;


		// ==> Забираем клинки, пистоли.
		case "STBStep_0":
        	dialog.text = "А ну, немедленно сдай все оружие! Следует сообщить полковнику Бишопу, чтобы он всыпал тебе как следует...";
    		link.l1 = "Вот, возьмите, и забудем об этом.";
    		link.l1.go = "STBStep_1";
            link.l2 = "Сейчас мы посмотрим, кто кому всыплет!";
            link.l2.go = "fight";
		break;

		case "STBStep_1":

                dialog.text = "А, ладно, проваливай.";
                link.l1.go = "Exit_Away";
                Pchar.questTemp.sLocator = "reload1_back";
                Pchar.questTemp.iTime = 40;
                RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
                RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
                while (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) != "" && !HasSubStr(FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE), "blade5"))
                {
                    TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE));

                }
                while (FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE) != "")
                {
                    TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE));
                }
                //GiveItem2Character(Pchar, "unarmed");
                //EquipCharacterByItem(Pchar, "unarmed");
                SetNewModelToChar(Pchar);
                //свободен
                pchar.quest.CapBloodDetectBlades1.over = "yes";
                pchar.quest.CapBloodDetectBlades2.over = "yes";
                chrDisableReloadToLocation = false;

		break;

		case "STBStep_2":
        	dialog.text = "Полковник Бишоп тебя обыскался. Немедленно отправляйся на плантацию...";
    		link.l1 = "Как скажешь.";
            link.l1.go = "Exit_Away";
            //link.l1.go = "finish";
            Pchar.questTemp.sLocator = "gate1_back";
            Pchar.questTemp.iTime = -1;

            chrDisableReloadToLocation = false;
            pchar.quest.CapBloodEscape2.win_condition.l1          = "location";
            pchar.quest.CapBloodEscape2.win_condition.l1.location = "Bridgetown_Plantation";
            pchar.quest.CapBloodEscape2.function                  = "ReturnToPlantation2";

            sld = characterFromID("Hugtorp");
            sld.Dialog.CurrentNode = "HTStep_14";
            ChangeCharacterAddressGroup(sld, "BridgeTown_Plantation", "goto", "goto18");
		break;

		//замечение по обнаженному оружию
		case "SoldierNotBlade":

            if (Pchar.questTemp.CapBUnarmed == false )
            {
                dialog.text = LinkRandPhrase("Какого черта ты бегаешь по городу с обнаженным клинком? Немедленно убери оружие!", "Приказываю вам немедленно убрать оружие в ножны!", "Эй, приятель, прекрати пугать народ! Убери оружие в ножны.");
                link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажешь...");
    			link.l1.go = "exit";
                link.l2 = LinkRandPhrase("Черта с два!", "Помечтай...", "После дождичка, в четверг.");
                link.l2.go = "fight";
			}
            else
            {
                dialog.text = RandPhraseSimple("С каких это пор рабы разгуливают, где попало с оружием?", "Ты же раб полковника Бишопа, почему ты вооружен?")+"\nА ну, немедленно сдай  все оружие! Следует сообщить полковнику Бишопу, чтобы он всыпал тебе как следует...";
                link.l1 = "Вот возьмите, и забудем об этом.";
                link.l1.go = "SoldierNotBladeEx";
                link.l2 = "Сейчас мы посмотрим, кто кому всыпет!";
                link.l2.go = "fight";
            }
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;

		case "SoldierNotBladeEx":

                RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
                RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
                while (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) != "" )
                {
                    TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE));

                }
                while (FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE) != "")
                {
                    TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE));
                }
                //свободен
                pchar.quest.CapBloodDetectBlades1.over = "yes";
                pchar.quest.CapBloodDetectBlades2.over = "yes";

                iChar = GetCharacterIndex("SolderTakeBlades");
                if (iChar != -1)
                {
                    sld = &characters[iChar];
                    LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
                    chrDisableReloadToLocation = false;
                }
                NextDiag.CurrentNode = NextDiag.TempNode;
                DialogExit();

		break;


        // --> Квестовый солдат


 		case "SQStep_0":

            dialog.text = "Испанец? Да ты издеваешься!.. Испанец не мог... или...?";
        	link.l1 = "Уверяю вас, это был испанец.";
            link.l1.go = "SQStep_1";
		break;

 		case "SQStep_1":

            dialog.text = "Я немедленно отправляюсь туда. Где находится этот дом?";
        	link.l1 = "Это дом мистера Гриффина, он неподалеку от усадьбы губернатора.";
            link.l1.go = "Exit_RunAway";
            Pchar.questTemp.sLocator = "houseSp2";
            Pchar.questTemp.iTime = 20;

            string smodel = NPChar.model;
            if (findsubstr(smodel, "eng_mush" , 0) != -1) smodel = "sold_eng_"+(rand(7)+1);
            sld = GetCharacter(NPC_GenerateCharacter("CPBQuest_Solder", smodel, "man", "man", 10, ENGLAND, 1, false));
            sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
            SetFantomParamHunter(sld); //крутые парни
            sld.SaveItemsForDead = true; // сохранять на трупе вещи
            sld.DontClearDead = true;
            LAi_SetActorTypeNoGroup(sld);
            LAi_ActorSetLayMode(sld);
            LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "CommonFlamHouse", "reload","reload3");

            sld = &characters[GetCharacterIndex("Griffin")];
            ChangeCharacterAddressGroup(sld, "CommonRoom_MH4", "barmen","bar1");
            LAi_SetActorTypeNoGroup(sld);
            LAi_ActorTurnToLocator(sld, "goto","goto2");
            LAi_SetStayTypeNoGroup(sld);
            sld = &characters[GetCharacterIndex("Spain_spy")];
            ChangeCharacterAddressGroup(sld, "CommonRoom_MH4", "goto","goto2");
            sld.dialog.currentnode = "SSStep_3";
            LAi_SetActorType(sld);
            LAi_ActorDialog(sld, pchar, "", 0, 0);
             //#20190120-02
            LocatorReloadEnterDisable("BridgeTown_town", "houseSp2", false);


            pchar.quest.PrepareToEscape2_3.win_condition.l1          = "location";
            pchar.quest.PrepareToEscape2_3.win_condition.l1.location = "CommonFlamHouse";
            pchar.quest.PrepareToEscape2_3.function                  = "_DeadSolder";

            Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape2_3";
            DoQuestFunctionDelay("SpainSpyAttack", 20.0);

		break;
        // --> Квестовый раб

        case "SLQStep_0":

            dialog.text = "Здравствуйте, Мистер Блад, вы вроде как у нас доктор? Вы не дадите мне какое-нибудь снадобье от головной боли? А то порой голова так болит, что невмоготу становится.";
            if (GetCharacterItem(pchar,"migraine_potion") > 0)
            {
           	    link.l0 = "Вот примите эту микстуру - она вылечит вашу мигрень.";
                link.l0.go = "SLQStep_3";
            }
        	link.l1 = "К сожалению, от головной боли у меня ничего нет. А полковник Бишоп денег на покупку необходимого лекарства, скорее всего не даст, так как считает, что все болезни у его рабов от безделья. Увы, но я могу только посоветовать - больше отдыхать, когда это возможно.";
            link.l1.go = "SLQStep_1";

        break;

        case "SLQStep_1":

            dialog.text = "Доктор, в моем положение следовать вашему совету затруднительно. Денег у меня нет, но есть кое-что, что может сильно вам пригодиться. Так, что если вам все-таки удастся раздобыть что-нибудь для меня, то я в долгу не останусь.";
        	link.l1 = "Хорошо, я попытаюсь раздобыть какое-нибудь лекарство для тебя.";
            link.l1.go = "Exit";
           	NextDiag.TempNode = "SLQStep_2";

        break;

        case "SLQStep_2":

            dialog.text = "Вы дадите мне лекарство, доктор?";
            if (GetCharacterItem(pchar,"migraine_potion") > 0)
            {
            	link.l1 = "Да, я принес лекарство от мигрени.";
                link.l1.go = "SLQStep_3";
           		link.l2 = "Пожалуй нет.";
                link.l2.go = "Exit";
             }
             else
             {
            	link.l1 = "Нет, мне пока не удалось достать нужной микстуры.";
                link.l1.go = "Exit";
             }
           	NextDiag.TempNode = "SLQStep_2";

        break;

        case "SLQStep_3":

            dialog.text = "Благодарю вас, доктор. В знак благодарности примите вот этот кинжал, я долго прятал его от надсмотрщиков, но, думаю, вам он пригодиться больше.";
        	link.l1 = "Да, но рабам нельзя иметь оружия!";
            link.l1.go = "SLQStep_4";
            TakeItemFromCharacter(Pchar, "migraine_potion");
            GiveItem2Character(Pchar, GetGeneratedItem("blade5"));

        break;


        case "SLQStep_4":

            dialog.text = "Не беспокойтесь доктор, его легко спрятать под одеждой, так что никто ничего не заметит. Если только вы не станете размахивать им перед солдатами.";
        	link.l1 = "Благодарю, друг мой, поправляйся.";
            link.l1.go = "Exit";
            NPChar.talker = 0;
           	NextDiag.TempNode = "First time";

        break;


        // --> Уинтервуд

        case "WWStep_0":

            dialog.text = "Что ты несешь, рабская мразь?! Какое у тебя может быть ко мне дело?!";
        	link.l1 = "Мне нужно вот это кольцо...";
            link.l1.go = "WWStep_1";

        break;

        case "WWStep_1":

            dialog.text = "Кольцо?! Да я не продам тебе его ни за какие деньги! Иди и купи себе другое у какой-нибудь торговки, которая согласится иметь дело с рабом!";
        	link.l1 = "Мне нужно не просто это кольцо, но и палец на котором оно надето.";
            link.l1.go = "WWStep_2";

        break;

        case "WWStep_2":

            dialog.text = "Ты дорого заплатишь за свои слова!";
        	link.l1 = "Я так и знал. Такие дела лучше делать без свидетелей. Приходи через час ко входу в город.";
            link.l1.go = "WWStep_3";

        break;

       	case "WWStep_3":
		Dialog.Text = "Ну что ж, встретимся за воротами через час. Я даже принесу для тебя какую-нибудь железку, чтобы это хоть немного походило на дуэль.";
		link.l1 = "До скорой встречи.";
		link.l1.go = "WWStep_4";
        break;

		//что ж, пойдем выйдем
	case "WWStep_4":

        PChar.quest.CapBloodLineTimer_3.win_condition.l1            = "Timer";
        PChar.quest.CapBloodLineTimer_3.win_condition.l1.date.hour  = sti(GetTime() + 1);
        PChar.quest.CapBloodLineTimer_3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
        PChar.quest.CapBloodLineTimer_3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
        PChar.quest.CapBloodLineTimer_3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
        PChar.quest.CapBloodLineTimer_3.function = "WinterwoodDuel";

		NextDiag.CurrentNode = "WWStep_5";
		DialogExit();
    break;

    case "WWStep_5":

		Dialog.Text = "Ну, чего тебе еще?";
		link.l1 = "У меня мало времени, я хочу покончить с тобой прямо сейчас!";
		link.l1.go = "WWStep_5_1";
		link.l2 = "Просто решил напомнить тебе о нашей встрече.";
		link.l2.go = "Exit";
		NextDiag.TempNode = "WWStep_5";
        break;

    case "WWStep_5_1":
		Dialog.Text = "Хм, ты сам выбрал свою судьбу!";
		link.l1 = "Приступим к делу.";
		link.l1.go = "WWStep_6";
    break;

	case "talk_off_town":
		Dialog.Text = "Ну что, ты готов отправиться в ад?";
		link.l1 = "Да. Сейчас посмотрим, кто кого!";
		link.l1.go = "WWStep_6";
		GiveItem2Character(Pchar, "blade2");
        EquipCharacterByItem(Pchar, "blade2");
        chrDisableReloadToLocation = false;
    break;

	//дуэли быть!
	case "WWStep_6":
		AddDialogExitQuestFunction("Winterwood_Prepare_Fight");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();

	break;

    case "WWStep_7":

        dialog.text = "Что ты несешь, рабская мразь?!";
    	link.l1 = "Я несу тебе весть о том, что приятное времяпрепровождение отменяется.";
        link.l1.go = "WWStep_8";

    break;

    case "WWStep_8":

        dialog.text = "У тебя есть три секунды, чтобы убраться туда, откуда ты выполз, и молиться, чтобы мы больше не повстречались.";
    	link.l1 = "У меня есть идея получше. Давай ты разозлишься и вызовешь меня на дуэль, а я пока постою подожду.";
        link.l1.go = "WWStep_3";
        n = FindLocation("Bridgetown_Brothel");
        locations[n].reload.l2.disable = true;

    break;

    // --> Алкаш

    case "QHStep_0":

		dialog.text = "И-ик! О, парень, ты выглядишь бывалым морским волком! Может, пропустим по стаканчику рома? Я угощаю.";
		link.l1 = "Может я и морской волк, только это не значит, что я буду пить с кем попало.";
		link.l1.go = "exit";
		link.l2 = "Я и сам с радостью присоединюсь к тебе, за компанию.";
		link.l2.go = "QHStep_1";
		NextDiag.TempNode = "QHStep_0";

    break;

	case "QHStep_1":
		NextDiag.TempNode = "begin_sit";
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		pchar.questTemp.friend_in_tavern = npchar.id;
		AddDialogExitQuest("alc");
	break;

	case "begin_sit":
		NextDiag.TempNode = "first time";
		dialog.snd = "Voice\HADI\HADI028";
		dialog.text = "Ик! Вот, это я понимаю! Вот это по-нашему! Сегодня я угощаю!";
		link.l1 = "Трактирщик, рома!";
		link.l1.go = "QHStep_2";
	break;

	case "QHStep_2":
		WaitDate("",0,0,0, 0, 30);
		dialog.text = LinkRandPhrase("Ты настоящий друг! Давай за знакомство!",
		                             "Ик! Какой ром! Ну... вздрогнем!",
									 "За твое здоровье, и за твое скорейшее освобождение!");
		link.l1 = "Скажи мне, братец, какие байки ходят по тавернам?";
		link.l1.go = "QHStep_3";
	break;

	case "QHStep_3":
		dialog.text = "Да ничего особенно нового... приехал недавно какой-то купец рейсом с Ямайки. Поговаривают, привез очень ценный груз. Если ничего не путаю, он вроде старый знакомый полковника Бишопа. Разместился в одном из домов города, собирается пробыть тут еще день-два.";
		link.l1 = "Да, славно посидели, ну, мне пора.";
		link.l1.go = "exit_sit";
		NextDiag.TempNode = "First time";

		if (CheckNationLicence(ENGLAND)) TakeNationLicence(ENGLAND);
		sTemp = NationShortName(ENGLAND)+"TradeLicence";
		ref rItem = ItemsFromID(sTemp);
		SaveCurrentNpcQuestDateParam(rItem, "Action_date");
		rItem.Action_date = GetCurrentDate();
		rItem.Validity = FindRussianDaysString(60);
		rItem.Validity.QtyDays = 60;

       // pchar.GenQuestBox.CommonStoneHouse = true;
       // pchar.GenQuestBox.CommonStoneHouse.stay = true;

        n = FindLocation("CommonStoneHouse");
        locations[n].private1.items.indian1 = 1;
        locations[n].private1.items.EngTradeLicence = 1;
        locations[n].private1.items.potionrum = 1;
        locations[n].private1.money = 6000;




       // pchar.GenQuestBox.CommonStoneHouse.box1.money = 6000;
       // pchar.GenQuestBox.CommonStoneHouse.box1.items.EngTradeLicence = 1;
       // pchar.GenQuestBox.CommonStoneHouse.box1.items.indian1 = 1;

        //Чарльз Вестон
       	sld = GetCharacter(NPC_GenerateCharacter("Weston", "trader_3", "man", "man", 10, ENGLAND, 1, false));
        sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
        sld.name = "Чарльз";
        sld.lastname = "Вестон";
		sld.greeting = "Gr_bankeer";
        FantomMakeCoolFighter(sld, 7, 100, 50, "topor2", "", 10);
       	LAi_SetImmortal(sld, true);
       	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
        LAi_group_MoveCharacter(sld, sTemp);
        LAi_SetOwnerTypeNoGroup(sld);
        ChangeCharacterAddressGroup(sld, "CommonStoneHouse", "barmen","stay");

        pchar.quest.MoneyForDieke.win_condition.l1 = "item";
        pchar.quest.MoneyForDieke.win_condition.l1.item= "EngTradeLicence";
        pchar.quest.MoneyForDieke.function = "MoneyForDieke";
        AddQuestRecord("DiekeQuest", "3");

	break;

	case "exit_sit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
	break;

    //Шпион

    case "MSStep_0":

        dialog.text = "Тогда убирайся!";
    	link.l1 = "";
        link.l1.go = "Exit";

    break;

    case "MSStep_1":

        dialog.text = "Так сколько их?";
    	link.l1 = "Они все там.";
        link.l1.go = "MSStep_2";
       	link.l2 = "Их пятеро.";
        link.l2.go = "MSStep_3";
       	link.l3 = "Их больше, чем я смог сосчитать.";
        link.l3.go = "MSStep_4";

    break;

    case "MSStep_2":

        dialog.text = "Все? О чем ты?! Пошел прочь, треклятый авантюрист!";
    	link.l1 = "...";
        link.l1.go = "exit";

    break;

    case "MSStep_3":

        dialog.text = "Пятеро... хм. Тогда понятно. Они вооружены?";
    	link.l1 = "У них легкое оружие, они не выставляют его напоказ.";
        link.l1.go = "MSStep_5";
       	link.l2 = "Нет, они ведут себя довольно мирно.";
        link.l2.go = "MSStep_6";

    break;

    case "MSStep_4":

        dialog.text = "Их... что?! А ну вон из моего дома, лжец! ";
    	link.l1 = "...";
        link.l1.go = "exit";

    break;

    case "MSStep_5":

        dialog.text = "Я так и знал! Это Гриффин продал им оружие! Они спрашивают про меня или про мой товар?";
    	link.l1 = "Они интересовались тобой, спрашивали гвардейцев.";
        link.l1.go = "MSStep_7";
       	link.l2 = "Они пытались выведать у трактирщика что-нибудь о тебе.";
        link.l2.go = "MSStep_8";

    break;

    case "MSStep_6":

        dialog.text = "Мирно? Ты сумасшедший!";
    	link.l1 = "...";
        link.l1.go = "exit";

    break;

    case "MSStep_7":

        dialog.text = "Гвардейцев? (смеется) Клоун, хоть и сообразительный! Иди к дьяволу!";
    	link.l1 = "...";
        link.l1.go = "exit";

    break;

    case "MSStep_8":

        dialog.text = "Старый пес не выдаст меня. Как они попали в город?";
    	link.l1 = "''Синко Льягас'' пришвартовался - они пришли на нем.";
        link.l1.go = "MSStep_9";
       	link.l2 = "Они пробрались в город ночью через джунгли.";
        link.l2.go = "MSStep_10";
       	link.l3 = "Они были здесь довольно долго, просто не показывались.";
        link.l3.go = "MSStep_11";

    break;

    case "MSStep_9":

        dialog.text = "На... корабле? Но... ты лжешь! Провались ты! ";
    	link.l1 = "...";
        link.l1.go = "exit";

    break;

    case "MSStep_10":

        dialog.text = "Джунгли... впятером? Ты смешон! Проваливай. ";
    	link.l1 = "...";
        link.l1.go = "exit";

    break;

    case "MSStep_11":

        dialog.text = "Точно, я уверен, что видел их раньше. Ладно, ты хорошо поработал, парень. И все же... кто они?";
    	link.l1 = "Испанцы.";
        link.l1.go = "MSStep_12";
       	link.l2 = "Пираты.";
        link.l2.go = "MSStep_13";
       	link.l3 = "Охотники за головами.";
        link.l3.go = "MSStep_14";

    break;

    case "MSStep_12":

        dialog.text = "Неплохая попытка... думаю, они уже заплатили тебе. Просто уходи.";
    	link.l1 = "...";
        link.l1.go = "exit";

    break;

    case "MSStep_13":

        dialog.text = "Пираты? (смеётся) А ты умеешь насмешить. Убирайся к морскому дьяволу!";
    	link.l1 = "...";
        link.l1.go = "exit";

    break;

    case "MSStep_14":

        dialog.text = "Забирай свои деньги. Передай ему, что я доволен твоей работой.";
    	link.l1 = "...";
        link.l1.go = "exit";
        AddMoneyToCharacter(pchar, 1000);
        AddCharacterExpToSkill(pchar, "Sneak", 80);
        AddCharacterExpToSkill(pchar, "Fortune", 30);
    break;

    case "FStep_1":

        dialog.text = "Эх-х... сегодня, пожалуй, угощаю я. Как и вчера, и позавчера, и каждый день с тех пор, как... впрочем, неважно.";
        if(makeint(Pchar.money) >=4 )
        {
            link.l1 = "Нет уж, позволь мне угостить лучшего барбадосского рыбака!";
            link.l1.go = "FStep_1_2";
        }
       	link.l2 = "Как скажешь, повелитель... рыб.";
        link.l2.go = "FStep_1_3";

    break;

   	case "FStep_1_2":
		NextDiag.TempNode = "FStep_2";
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		pchar.questTemp.friend_in_tavern = npchar.id;
		AddDialogExitQuest("alc");
	break;

	case "FStep_1_3":
		NextDiag.TempNode = "FStep_3";
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		pchar.questTemp.friend_in_tavern = npchar.id;
		AddDialogExitQuest("alc");
	break;


    case "FStep_2":

        AddMoneyToCharacter(pchar, -2);
        dialog.snd = "Voice\HADI\HADI028";
        dialog.text = "Ты дьявольски прав, черт возьми! За это и выпьем!";
    	link.l1 = "За лучшего рыбака! (отправляя содержимое кружки в горло) Как давно ты этим занимаешься, Арни?";
        link.l1.go = "FStep_4";

    break;

    case "FStep_3":

        dialog.snd = "Voice\HADI\HADI028";
        dialog.text = "А что тебе не нравится? Дьявол, да я лучший рыбак на всем архипелаге!";
    	link.l1 = "Немудрено быть лучшим там, где рыбы нет... я тоже ловил... рыбу.";
        link.l1.go = "FStep_5";


    break;

    case "FStep_4":

        AddMoneyToCharacter(pchar, -2);
        dialog.text = "Уже не первый десяток лет, друг. Не первый десяток... но ТАКОГО раньше не было, якорь мне...";
    	link.l1 = "КАКОГО раньше не было? Ладно, выпьем еще за ТАКОЕ!";
        link.l1.go = "FStep_6";

    break;

    case "FStep_5":

        dialog.text = "Нет? Нет рыбы?! Надо знать места, недотепа! Я нашел уникальное место... сеть наполняется до отказа за ночь - Господь свидетель!";
    	link.l1 = "Места... я тоже искал места, везде ловил... нет тут рыбы, и мест нет. К черту рыбную ловлю - бесприбыльное это дело!";
        link.l1.go = "FStep_7";

    break;

    case "FStep_6":

        dialog.text = "Выпьем... А это… такое... такое место... оно...";
    	link.l1 = "...";
        link.l1.go = "FStep_8";
       	link.l2 = "Ну? Что за место?!";
        link.l2.go = "FStep_Fail";

    break;

    case "FStep_7":

        dialog.text = "Не умеешь ты искать! Я могу показать тебе, как это... каково это...";
    	link.l1 = "...";
        link.l1.go = "FStep_8";
       	link.l2 = "Ну? Что за место?!";
        link.l2.go = "FStep_Fail";

    break;

    case "FStep_8":

        Pchar.questTemp.CapBloodLine.fishplace = "Мыс Раггед Пойнт.";
        dialog.text = "...оно совсем рядом. "+Pchar.questTemp.CapBloodLine.fishplace;
    	link.l1 = "Невероятно!.. Но мне уже пора.";
        link.l1.go = "exit_sit";
        NextDiag.TempNode = "First time";
        AddQuestRecord("FishermanQuest", "2");

    break;

    case "FStep_Fail":

        dialog.text = "Ах ты... пошел прочь, рабский лазутчик!..";
    	link.l1 = "Да чтоб тебя морской дьявол забрал!";
        link.l1.go = "exit_sit";
        NextDiag.TempNode = "First time";

    break;

    case "QSTStep_0":

        dialog.text = "Кто ты такой вообще? Мое имя Алекс Уиннер, я торговец! Убирайся, а то перекуплю тебя у твоего хозяина и отправлю на дно в обнимку с ядром!";
    	link.l1 = "Эм...";
        link.l1.go = "Exit_Away";
        Pchar.questTemp.sLocator = "reload1_back";
        if(npchar.location == "CommonRoom_MH7") Pchar.questTemp.sLocator = "reload1"
        Pchar.questTemp.iTime = -1;
   		CloseQuestHeader("UsurerQuest");

    break;

    case "QSTStep_1":

        dialog.text = "М-м-м... мы знакомы? Я мог забыть, как тебя?..";
    	link.l1 = "Конечно, Раф! Но... если ты забыл мой долг тебе, то...";
        link.l1.go = "QSTStep_3";

    break;


    case "QSTStep_2":

        dialog.text = "О чем ты говоришь? Я не знаю никакого ростовщика!.. Я... проклятье!";
    	link.l1 = "Отдай мне деньги, и я передам губернатору Стиду, что ты добровольно вернул их, а тебя отпущу.";
        link.l1.go = "QSTStep_6";

    break;

    case "QSTStep_3":

        dialog.text = "Я помню... кажется. Верно. Так, когда же ты отдашь мне долг?";
    	link.l1 = "Долг жизни, друг мой... где ты хотел бы умереть? Может, прямо здесь?";
        link.l1.go = "QSTStep_4";

    break;

    case "QSTStep_4":

        dialog.text = "Что?!";
    	link.l1 = "Ты предал меня, Гиннес! Из-за тебя я лишился всего!.. Ты умрешь!";
        link.l1.go = "QSTStep_5";

    break;

    case "QSTStep_5":

        PChar.quest.QUsurer.win_condition.l1            = "Timer";
        PChar.quest.QUsurer.win_condition.l1.date.hour  = 0;
        PChar.quest.QUsurer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
        PChar.quest.QUsurer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
        PChar.quest.QUsurer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
        PChar.quest.QUsurer.function = "QUsurerLate";

        AddMoneyToCharacter(pchar, 55000);
        ChangeCharacterReputation(PChar, -10);
        AddCharacterExpToSkill(pchar, "Leadership", 30);
        dialog.text = "Нет, подожди... смотри... у меня есть 55 000!.. Забирай все!";
    	link.l1 = "Премного благодарен, дорогой друг.";
        link.l1.go = "Exit_Away";
        Pchar.questTemp.sLocator = "reload1_back";
        if(npchar.location == "CommonRoom_MH7") Pchar.questTemp.sLocator = "reload1";
        Pchar.questTemp.iTime = -1;
        AddQuestRecord("UsurerQuest", "3");

    break;

    case "QSTStep_6":

        PChar.quest.QUsurer.win_condition.l1            = "Timer";
        PChar.quest.QUsurer.win_condition.l1.date.hour  = 0;
        PChar.quest.QUsurer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
        PChar.quest.QUsurer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
        PChar.quest.QUsurer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
        PChar.quest.QUsurer.function = "QUsurerLate";

        AddMoneyToCharacter(pchar, 30000);
        dialog.text = "Ты... ладно. Вот, возьми, забирай, черт! ";
    	link.l1 = "Премного благодарен, дорогой друг.";
        link.l1.go = "Exit_Away";
        Pchar.questTemp.sLocator = "reload1_back";
        if(npchar.location == "CommonRoom_MH7") Pchar.questTemp.sLocator = "reload1"
        Pchar.questTemp.iTime = -1;
        AddQuestRecord("UsurerQuest", "4");

    break;

    //Жак Соловей

    case "JSTStep_0":

        dialog.text = "Здравствуй, незнакомец. Ты здесь по делу? Если нет - отваливай.";
    	link.l1 = "Не очень-то вежливо... А вы кто такой? Не слышал, чтобы сменился наш негоциант.";
        link.l1.go = "JSTStep_1";

    break;

    case "JSTStep_1":

        dialog.text = "Может быть... это потому, что он не менялся, а, друг мой?";
    	link.l1 = "Не имею чести быть вашим другом. Дайте догадаюсь... вы пират? Или простой вор?";
        link.l1.go = "JSTStep_2";

    break;

    case "JSTStep_2":

        dialog.text = "Вы удивительно невежественны! Неужели не слышали о капитане Роландо Пицарро?";
    	link.l1 = "А должен был слышать?";
        link.l1.go = "JSTStep_3";

    break;

    case "JSTStep_3":

        dialog.text = "Хм, позволь, я восполню этот обидный пробел твоей осведомлённости. Итак, спешу представиться! Капитан Роландо Пицарро, он же - Каталонский Лис! Поборник справедливости и чести! Известен во всех Семи Морях от северных льдов, до...";
    	link.l1 = "Это всё очень интересно, только - что вы, поборник справедливости и прочая-прочая, здесь делаете?";
        link.l1.go = "JSTStep_4";
    break;

    case "JSTStep_4":

        dialog.text = "Я? Что здесь делаю... эм-м, ну, положим - то же, что и ты! Да, именно! Зачем вот ты сюда заглянул?";
    	link.l1 = "Честно? Или версия для общественности?";
        link.l1.go = "JSTStep_6";

    break;

    case "JSTStep_6":

        dialog.text = "Будем честными, ведь мы же теперь друзья, так? Когда два человека вламываются в один магазин, в одно время, без ведома хозяина, им просто Небеса указывают стать друзьями, не правда ли?";
    	link.l1 = "Вы не пробовали выступать в парламенте? Столько речей, и ни одного ответа. Ладно - мне сейчас более нужны деньги, нежели новые знакомства, так что, сожалею, но мне пора.";
        link.l1.go = "JSTStep_7";

    break;

    case "JSTStep_7":

        dialog.text = "Эй-эй, не спешите, сударь! Давайте, совместим приятное с полезным - я как раз, по чистой случайности, разжился несколькими монетами... и, если вы решитесь продолжить наше знакомство, часть из них может перейти к вам. Ну, скажем так, в знак дружеского расположения?";
    	link.l1 = "Что-то подсказывает мне, что сие расположение будет отнюдь не бескорыстно...";
        link.l1.go = "JSTStep_8";

    break;

    case "JSTStep_8":

        dialog.text = "Ну вот, мы опять на 'вы'. Это плохой знак - не находишь? Неужели наша дружба уже начинает трещать по швам, как только речь зашла о деньгах?";
    	link.l1 = "Вы удивительно навязчивый и болтливый тип. И в другое время я бы...";
        link.l1.go = "JSTStep_9";

    break;

    case "JSTStep_9":

        dialog.text = "Опуская подробности - найди мне того, кто согласится доставить меня в Порто-Белло за три тысячи, и я дам тебе полторы. По рукам? Думаю, в твоем положении ни один песо лишним не будет?";
    	link.l1 = "Да... заманчивое предложение. Да и выбирать не из чего. По рукам.";
        link.l1.go = "JSTStep_10";
       	link.l2 = "Знаешь, шёл бы ты... морочить головы доверчивым провинциальным барышням! С меня достаточно на сегодня.";
        link.l2.go = "Exit_Away";
        Pchar.questTemp.sLocator = "reload1_back";
        Pchar.questTemp.iTime = -1;

    break;

    case "JSTStep_10":

        dialog.text = "Одно условие, мон шерри - никаких имен. Ну, то есть - своё называй, если хочешь... а вот моё... скажи - я его забыл... Или... лучше скажи, что я красивая юная леди!";
    	link.l1 = "Юная леди?.. однако. Ладно, я что-нибудь придумаю.";
        link.l1.go = "Exit_Away";
        Pchar.questTemp.sLocator = "reload1_back";
        Pchar.questTemp.iTime = -1;
        AddQuestRecord("PirateQuest", "1");
        Pchar.questTemp.CapBloodLine.ShipForJack = true;
       	sld = characterFromID("Bridgetown_trader");
   	    LAi_RemoveLoginTime(sld);

    break;

    case "JSTStep_11":

        dialog.text = "Рад тебя видеть, мой новый друг. Итак, удалось ли тебе оказать мне... ту услугу, о которой мы договаривались?";
    	link.l1 = "Корвет 'Плавучий британец' капитана Джона Майнера уже ждёт.";
        link.l1.go = "JSTStep_12";

    break;

    case "JSTStep_12":

        dialog.text = "Ну, что я могу сказать - поклон и большое спасибо тебе, о...";
    	link.l1 = "Полторы тысячи, Роландо.";
        link.l1.go = "JSTStep_13";

    break;

    case "JSTStep_13":

        dialog.text = "Конечно-конечно! Я просто хотел выразить тебе свою искреннюю признательность и предложить отведать этого чудеснейшего рома, дабы скрепить совместным тостом узы прекрасной дружбы, которая отныне...";
    	link.l1 = "Полторы тысячи! Я жду... мой новый друг.";
        link.l1.go = "JSTStep_14";

    break;

    case "JSTStep_14":

        dialog.text = "Тише ты! Вот, вот твои деньги!..";
    	link.l1 = "Благодарю.";
        link.l1.go = "Exit";
        AddMoneyToCharacter(pchar, 1500);
        AddQuestRecord("PirateQuest", "5");
        CloseQuestHeader("PirateQuest");
        NextDiag.TempNode = "JSTStep_15";
        NPChar.lifeDay = 0;

    break;

    case "JSTStep_15":

        dialog.text = "Я благодарен тебе... друг. Иди - потрать свои деньги на что-нибудь красивое.";
    	link.l1 = "И тебе удачи... хм.";
        link.l1.go = "Exit";
        NextDiag.TempNode = "JSTStep_15";

    break;

    //Джон Майнер

    case "MNStep_0":

        dialog.text = "Джон Майнер, капитан корвета 'Плавучий британец', к вашим услугам. Чем могу помочь?";
    	link.l1 = "Добрый день, мое имя Питер Блад. Могу я просить вас об одолжении, капитан? Одному моему, гм... другу очень нужно добраться до Порто Белло, и он готов распрощаться с тремя тысячами пиастров.";
        link.l1.go = "MNStep_1";

    break;

    case "MNStep_1":

        dialog.text = "Могу я узнать имя вашего друга, мистер Блад?";
    	link.l1 = "Конечно. Его зовут... её... в общем да - это, на самом деле, она...";
        link.l1.go = "MNStep_2";
       	link.l2 = "Конечно. Его имя Роландо Пицарро, слыхал?..";
        link.l2.go = "MNStep_3";
       	link.l3 = "Нет.";
        link.l3.go = "MNStep_4";

    break;

    case "MNStep_2":

        dialog.text = "Барышня? Ваш друг... в смысле подруга, собирается в Порто Белло?";
    	link.l1 = "А почему нет? Порто-Белло вполне благопристойный порт. Почему бы, барышне туда не отправиться?";
        link.l1.go = "MNStep_5";

    break;

    case "MNStep_3":

        dialog.text = "Я... слыхал, да. Что ж, я жду его на борту. Спасибо за правдивый ответ, мистер Блад.";
    	link.l1 = "Честность - клинок обоюдоострый. Всего наилучшего. Надеюсь, вы не пожалеете о своем решении.";
        link.l1.go = "MNStep_Exit";

    break;


    case "MNStep_4":

        dialog.text = "Нет? Как я могу согласиться взять пассажира, если даже не знаю его имени?!";
    	link.l1 = "Вполне можете. Скажем так, это некая миссис Тэйлор... да, именно так - миссис Тэйлор, который... которая даст вам три тысячи золотом, если вы перестанете задавать вопросы.";
        link.l1.go = "MNStep_6";

    break;

    case "MNStep_5":

        dialog.text = "Хорошо, я возьму его... её. Передайте моей будущей пассажирке, что 'Плавучий британец' готов к отбытию.";
    	link.l1 = "Благодарю.";
        link.l1.go = "MNStep_Exit";
        AddCharacterExpToSkill(pchar, "Sneak", 50);

    break;

    case "MNStep_6":

        dialog.text = "Сразу бы так и говорили! По рукам - жду мисс Тэйлор, на борту.";
    	link.l1 = "Миссис Тэйлор, с вашего позволения. Всего доброго, капитан.";
        link.l1.go = "MNStep_Exit";

    break;

   	case "MNStep_Exit":

            AddQuestRecord("PirateQuest", "4");
            sld = characterFromID("Jack");
            sld.Dialog.CurrentNode = "JSTStep_11";
            LAi_SetSitTypeNoGroup(sld);
            ChangeCharacterAddressGroup(sld, "Bridgetown_tavern", "sit","sit4");
            LAi_SetActorType(npchar);
 			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
	break;


    //Служанка Арабеллы

    case "ASStep_0":

        dialog.text = "Вы спасли меня? Кто вы?!";
    	link.l1 = "Я Питер Блад, э-э-э... местный врач. Вы будете ждать, пока я предъявлю вам свои документы? И что здесь, черт возьми, происходит?";
        link.l1.go = "ASStep_1";
        ChangeCharacterReputation(pchar, 5);

    break;

    case "ASStep_1":

        dialog.text = "Испанцы... они... Тот большой корабль, которому сегодня разрешили так спокойно войти под чужим флагом в нашу бухту, оказался испанским капером. Его хитрость с флагом осталась нераскрытой настолько, что, не возбудив подозрений, он преспокойно вошел в бухту и отсалютовал форту в упор бортовым залпом из двадцати пушек...";
    	link.l1 = "А теперь, как я понимаю, экипаж этого капера грабит город?";
        link.l1.go = "ASStep_2";

    break;

    case "ASStep_2":

        dialog.text = "Да, к заходу солнца наш гарнизон сдался и двести пятьдесят испанцев стали хозяевами Бриджтауна.";
    	link.l1 = "Вот это и называется своевременным вмешательством судьбы. Хотя один лишь дьявол знает, что из всего этого выйдет! А вы - бегите в лес и прячьтесь, до тех пор пока испанцы не покинут город.";
        Pchar.questTemp.CapBloodLine.SpainInBridgetown = true;
        Pchar.questTemp.sLocator = "gate1_back";
        Pchar.questTemp.iTime = -1;
        link.l1.go = "Exit_RunAway";
        AddQuestRecord("EscapeFormBarbados", "3");

    break;


	}
}

