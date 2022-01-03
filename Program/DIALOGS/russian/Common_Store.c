// boal 08/04/04 общий диалог торговцев
#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	int skullprice = (sti(PChar.rank) * 4000) - ((sti(PChar.rank) * 2400) * (0.01* (GetSummonSkillFromName(PChar, SKILL_COMMERCE))))+ 10000;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);


	string iDay, iMonth, sTemp, sMoney, attrL;

	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	int iMoney;
	int iQuantityGoods;
	int iTradeGoods;
	int iTmp;

    bool  ok;

	int iTest, cn, i;
	iTest = FindColony(NPChar.City); // город магазина
	ref rColony, chref;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}

    int iSeaGoods = LanguageOpenFile("ShipEatGood.txt"); // нужно заменить на GetGoodsNameAlt(idx)

    if (!CheckAttribute(npchar, "quest.item_date"))
    {
        npchar.quest.item_date = "";
    }
    if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Store\" + NPChar.City + "_Store.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	string attrLoc   = Dialog.CurrentNode;

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase("В городе поднята тревога, тебя всюду ищут! На твоем месте я бы не стал здесь задерживаться.", "Вся городская стража рыщет по городу в поисках тебя. Я не идиот и разговаривать с тобой не буду!", "Беги, "+ GetSexPhrase("приятель","подруга") +", пока солдаты не сделали из тебя решето..."),
					LinkRandPhrase("Что тебе нужно, "+ GetSexPhrase("негодяй","негодяйка") +"?! Городская стража уже взяла твой след, далеко тебе не уйти, "+ GetSexPhrase("грязный пират","гнусная дрянь") +"!", ""+ GetSexPhrase("Грязный","Грязная") +" убийца, вон из моего дома! Стража!!", "Я не боюсь тебя, "+ GetSexPhrase("мерзавец","мерзавка") +"! Скоро тебя повесят в нашем форте, далеко тебе не уйти..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Хех, тревога для меня не проблема...", "Им меня ни за что не поймать."),
					RandPhraseSimple("Заткни свою пасть, " + GetWorkTypeOfMan(npchar, "") + ", а не то вырву твой поганый язык!", "Хех, " + GetWorkTypeOfMan(npchar, "") + ", а все туда же - пиратов ловить! Вот что я тебе скажу, приятель: сиди тихо и будешь жить..."));
				link.l1.go = "fight";
				break;
			}
			//homo Линейка Блада
            if (Pchar.questTemp.CapBloodLine == true )
            {
                dialog.Text = LinkRandPhrase("Эй, доктор Блад! " + TimeGreeting() + ".",
                                    "Рад видеть Вас, Питер Блад.",
                                    "Хорошо, что вы заглянули ко мне, " + GetFullName(pchar) + ". Как поживает полковник Бишоп?");
                Link.l1 = "Увы, я уже ухожу, " + NPChar.name + ". До встречи.";
				Link.l1.go = "exit";
				NextDiag.TempNode = "First time";
				break;
            }
			if (npchar.id != "Pirates_trader" && npchar.id != "Caiman_trader" && CheckAttribute(pchar, "BSStart"))
			{
				//Black sails
				if(pchar.questTemp.BlueBird == "over")
				{
					dialog.text = "Капитан, ничего личного, но очень влиятельная особа запретила вести дела с вами. Никаких сделок, извините.";
					link.l1 = "Простите, но я не понимаю. Что произошло?";
					link.l1.go = "BS_NPVK_2";
					break;
				}
			}
            dialog.text = NPCharRepPhrase(npchar, "Новый клиент - новое золото. "
							+ LinkRandPhrase("Деньги не имеют запаха. ", "Пиастры не пахнут. ","Одной добродетелью сыт не будешь! ")+
							+GetFullName(npchar)+  " к вашим услугам!",
			                + LinkRandPhrase("Приятно познакомится с новым клиентом, ", "Рад новому клиенту, ", "Добро пожаловать, ")
							+ GetAddress_Form(NPChar)+ ". Мое имя "  + GetFullName(npchar)+
							+ RandPhraseSimple(", мой магазин к вашим услугам.",", я полностью в вашем распоряжении."));
			link.l1 = "Позвольте представиться. " +RandPhraseSimple("Меня зовут ","Я - ")+ "капитан "+ GetFullName(pchar)+".";
			link.l1.go = "node_1";
			NextDiag.TempNode = "Second time";
		break;

		//Black sails
		case "BS_NPVK_2":
            dialog.text = "Обратитесь к мисс Гатри, она недавно прибыла с Нассау и взяла под контроль сделки с призами. На Бермудах сам Джекмен к ней с поклоном заходит.";
            link.l1 = "Хм. Гатри… Что – то знакомое. Хорошо, до встречи.";
			link.l1.go = "exit";

			sld = CharacterFromID("Pirates_trader");
			if(sld.lastname != "Гатри")
			{
				BS_ReplaceTraderWithGatri();
				sld.Dialog.FileName = "Quest\BlackSails\NePluyjVKolodec.c";
				sld.Dialog.CurrentNode = "BS_NPVK_3";
				SetQuestHeader("BSPrologue");
				AddQuestRecord("BSPrologue", "1");

				for (i = 1; i < 4; i++)
				{
					sld = GetCharacter(NPC_GenerateCharacter("gatri_grunt"+i, GetPirateMushketerModel(), "man", "mushketer", 777, PIRATE, -1, false));
					LAi_SetWarriorType(sld);
					LAi_warrior_DialogEnable(sld, false);
					ChangeCharacterAddressGroup(sld, "Pirates_store", "goto", "goto"+i);
					LAi_SetImmortal(sld, true);
					LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
				}
			}
		break;
		//Black sails

		case "second time":
			if (LAi_group_GetPlayerAlarm() > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase("В городе поднята тревога, тебя всюду ищут! На твоем месте я бы не стал здесь задерживаться.", "Вся городская стража рыщет по городу в поисках тебя. Я не идиот и разговаривать с тобой не буду!", "Беги, "+ GetSexPhrase("приятель","подруга") +", пока солдаты не сделали из тебя решето..."),
					LinkRandPhrase("Что тебе нужно, "+ GetSexPhrase("негодяй","негодяйка") +"?! Городская стража уже взяла твой след, далеко тебе не уйти, "+ GetSexPhrase("грязный пират","гнусная дрянь") +"!", ""+ GetSexPhrase("Грязный","Грязная") +" убийца, вон из моего дома! Стража!!", "Я не боюсь тебя, "+ GetSexPhrase("мерзавец","мерзавка") +"! Скоро тебя повесят в нашем форте, далеко тебе не уйти..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Хех, тревога для меня не проблема...", "Им меня ни за что не поймать."),
					RandPhraseSimple("Заткни свою пасть, " + GetWorkTypeOfMan(npchar, "") + ", а не то вырву твой поганый язык!", "Хех, " + GetWorkTypeOfMan(npchar, "") + ", а все туда же - пиратов ловить! Вот что я тебе скажу, приятель: сиди тихо и будешь жить..."));
				link.l1.go = "fight";
				break;
			}

			if (npchar.id != "Pirates_trader" && npchar.id != "Caiman_trader" && CheckAttribute(pchar, "BSStart"))
			{
				//Black sails
				if(pchar.questTemp.BlueBird == "over")
				{
					dialog.text = "Капитан, ничего личного, но очень влиятельная особа запретила вести дела с вами. Никаких сделок, извините.";
					link.l1 = "Простите, но я не понимаю. Что произошло?";
					link.l1.go = "BS_NPVK_2";
					break;
				}
			}

            /*if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				dialog.text = NPCharRepPhrase(npchar,
                     		  LinkRandPhrase("Разрази меня гром! ", "Дьявол!!! ", "Тысяча чертей!!! ")
							+ LinkRandPhrase("Неприятель ","Противник ", "Проклятый шпион ")+ LinkRandPhrase("в городе! ","прямо по курсу! ", "в кубрике! ") + RandPhraseSimple("Стража!", "Солдаты!"),
							  LinkRandPhrase("Пресвятая дева","Господи Иисусе", "Святой Себастьян")+ "! "+ LinkRandPhrase("Караул! " ,"Помогите! ","Да вы шпион! ")
							+ LinkRandPhrase("В городе враги! ","Лазутчики в городе! ","Предательство! ")+"Солдаты, сюда!!");
				link.l1 = pcharrepphrase(LinkRandPhrase("Закрой пасть!","Тишина на палубе!","Молчать!")+ " Или я "
											  + LinkRandPhrase("вырву твой язык и скормлю его псам, ", "вышибу тебе мозги, ","удушу тебя твоими же кишками, ")+ LinkRandPhrase("каналья!", "торгаш!", "мерзавец!"),
							                    LinkRandPhrase("Ради бога, ", "Прошу вас, ", "Немедленно ")+LinkRandPhrase("закройте рот!", "прекратите верещать, как свинья на бойне!", "заткнитесь, наконец!")
											  + LinkRandPhrase(" Или я не дам за вашу жизнь и фартинга!"," Меня уже здесь нет! И никогда не было! Вы поняли?"," Или мне придется вас убить на месте."));
				link.l1.go = "fight";
				break;
			}*/
   			// проверка награды
			/*if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) >= 40)
			{
				dialog.text = NPCharRepPhrase(npchar,
                     LinkRandPhrase("Разрази меня гром! ", "Дьявол!!! ", "Тысяча чертей!!! ")+GetFullName(pchar)+ ", по прозвищу "
							+ LinkRandPhrase("'Палач', ","'Окорок', ", "'Потрошитель', ") +LinkRandPhrase(" в городе! "," прямо по курсу! ", " с правого борта! ") + RandPhraseSimple("Стража!", "Солдаты!"),
							  LinkRandPhrase("Пресвятая дева","Господи Иисусе", "Святой Себастьян")+ "! Это сам "+GetFullName(pchar)+ LinkRandPhrase("! Ловите " ,"! Хватайте ","! Держите ")
							+ LinkRandPhrase("висельника! ","вора и убийцу! ","беглого каторжника! ")+"Солдаты, сюда!!");
				link.l1 =      pcharrepphrase(LinkRandPhrase("Закрой пасть!","Тишина на палубе!","Молчать!")+ " А не то я"
											  + LinkRandPhrase(" вырву твой язык, каналья!", " выбью из тебя мозги!"," тебе кишки выпущу!"),
							                    LinkRandPhrase("Ради бога замолчите!", "Прошу вас! Не кричите!", "К чему весь этот шум?")
											  + LinkRandPhrase(" Я уже ухожу!"," Меня уже здесь нет!"," Я не хочу вас убивать!"));
				link.l1.go = "fight";
				break;
			}    */
			dialog.text = NPCharRepPhrase(npchar,
			                 pcharrepphrase(LinkRandPhrase("Капитан ", "Да это "+ GetSexPhrase("сам","сама") +" ", "Кого я вижу? Это же ") +GetFullName(pchar)+"! "
							                 + LinkRandPhrase("Тебя еще не вздернули на рее? Ха-ха!","Говорят, ты "+ GetSexPhrase("был","была") +" в гостях у морского дьявола!", "А я слышал, тебя повесили в Порт-Рояле.")
											  + RandPhraseSimple(" Рад тебя видеть!", " Добро пожаловать!"),
							                LinkRandPhrase("Здравствуйте, ", "Добро пожаловать, ", "Добрый день, ") + "капитан"
											+ RandPhraseSimple(". Вам понравился ",". Приглянулся ли вам ")+" наш"+ RandPhraseSimple(" остров? "," городок? ")
											+ LinkRandPhrase("Тут совсем не плохо,","Отличное место,", ""+ GetSexPhrase("Здесь красивые девушки,","У нас гостеприимный народ,") +"")+RandPhraseSimple(" не правда ли?", " не так ли?")),
							 pcharrepphrase(LinkRandPhrase("Капитан ","Ах, это опять вы, ","Вы меня напугали, ") + GetFullName(pchar)
							 				+ LinkRandPhrase(". Вашим именем матери уже стращают непослушных детей!",". Я надеюсь, у вас нет трений с законом?",". Ваша репутация оставляет желать лучшего.")
											 +LinkRandPhrase(" Чему обязан за ваш визит?"," Что вам угодно?", " Зачем вы пришли?"),
							                "Добро пожаловать, капитан " +GetFullName(pchar)+ LinkRandPhrase("! Немного штормит сегодня",
											"! Похоже, собирается шторм","! Поднимается сильный ветер") +", не правда ли?"));

			link.l1 = NPCharRepPhrase(npchar,
			            pcharrepphrase(LinkRandPhrase("Ты все еще жив, ", "И я тебе "+ GetSexPhrase("рад","рада") +", ","Мы с тобой знали времена и получше, ")
									  +LinkRandPhrase("каналья!","дружище!","морской волк!") +" А я "+ GetSexPhrase("думал","думала") +", "
									  +LinkRandPhrase("твоя жена уже сгрызла тебя с элем!","тебя сожрали термиты!", "твоя старуха сжила тебя со свету!"),
						               LinkRandPhrase("Добрый день, ","Доброго здоровья, ","Привет, ") + GetAddress_FormToNPC(NPChar)+" " +GetFullName(Npchar)
									   +RandPhraseSimple(". Вы правы, ",". Совершенно "+ GetSexPhrase("согласен","согласна") +", ")
									   +LinkRandPhrase("а местные "+ GetSexPhrase("мулатки просто очаровательны","жители очень доброжелательны") +"", "с этим трудно спорить", "а "+ GetSexPhrase("здешние дамы вскружат голову кому угодно","горожане и впрямь весьма любезны") +"")+ "."),
						pcharrepphrase(RandPhraseSimple("К черту такие разговоры, ","Поворачивай на другой галс, ") +GetFullName(Npchar)+ "! "
						              +LinkRandPhrase("Болтаешь, как попугай!", "И не морочь мне голову!","Твои слова не дороже сухаря!")
						              +RandPhraseSimple(" Я "+ GetSexPhrase("пришел","пришла") +" в магазин!"," А зачем ты здесь сидишь?"),
						               "Добрый день, " + GetAddress_FormToNPC(NPChar)+ "! Да, но вчера " + LinkRandPhrase("был полный штиль.",
									    "была отличная погода.", "не было ни ветерка.")));
			link.l1.go = "node_1";
			NextDiag.TempNode = "Second time";
		break;

		case "node_1":
			dialog.text = NPCStringReactionRepeat(NPCharRepPhrase(npchar,
			                                         pcharrepphrase(RandPhraseSimple("Свистать всех наверх! ","Трюм к осмотру! ") +LinkRandPhrase("Что нужно "+ GetSexPhrase("джентльмену","джентльмену, ой, пардон, леди") +" удачи в моем магазине, хе-хе?",
													                                 "Какой приятный сюрприз для бедного старого торговца! Хе-хе!", "Каким попутным ветром тебя занесло в мой магазин?"),
            														LinkRandPhrase("Открыть порты!", "Крючья к борту!","Держать прямо по курсу!")+RandPhraseSimple(" У меня вы найдете"," В моем магазине")
																	+LinkRandPhrase(" самые лучшие цены на острове."," прекрасный выбор товаров."," товары самого высшего качества.")
																	+RandPhraseSimple(" Я к вашим услугам"," Все, что пожелаете")+", капитан!"),
													 pcharrepphrase(RandPhraseSimple("Любые товары для "+ GetSexPhrase("джентльменов","джентльменов и леди") +" удачи! Хе-хе! Пока их не повесили сушиться на солнышке!",
													                                 "Ветер качает повешенных в порту и разносит звон цепей. Но пиастры не пахнут, верно?!"),
                 												"Желаете " +LinkRandPhrase("купить лучшие товары " + NationNameGenitive(sti(NPChar.nation)),"купить или продать груз", "получить выгодный фрахт")
																	+RandPhraseSimple("? Я полностью в вашем распоряжении!","? Мой магазин к вашим услугам!")
																	+RandPhraseSimple(" Рад вас видеть"," Располагайтесь") +", капитан!")),
				                                  NPCharRepPhrase(npchar,
												  	 pcharrepphrase("Мой тебе совет, кэп: не жалей денег на картечь. Обыскивать проще мертвых!",
													                "Я с первого взгляда увидел, что ты "+ GetSexPhrase("ловкий малый","ловкая малая") +". " +RandPhraseSimple("Но теперь я вижу, что ты прямо "+ GetSexPhrase("герой","сорвиголова") +".", "Ты "+ GetSexPhrase("молод","молода") +", но "
																	+RandPhraseSimple("ум у тебя острый.", "тебя не обманешь."))),
													 pcharrepphrase("Я готов покупать у вас весь груз с захваченных призов. Хотите купить золото или серебро? Оно всегда в цене!",
													                "Торговое мореплавание - выгодный бизнес, капитан " + GetFullName(pchar)+", не так ли?")),
												  NPCharRepPhrase(npchar,
												     RandPhraseSimple("Все семьдесят пять не вернулись домой! Они потонули в пучине морской! " ,
													   RandPhraseSimple("Пятнадцать человек на сундук мертвеца!","Пей, и дьявол тебя доведет до конца!") +" Йо-хо-хо! И бутылка рома. ")
													   +RandPhraseSimple("Чего надо, кэп?", "Что вы хотите купить, капитан?"),
													 pcharrepphrase("А вы любите поторговаться, капитан " + GetFullName(pchar)+". Как постоянному клиенту, я предлагаю вам очень выгодные цены!",
													                "Ну хорошо, капитан " + GetFullName(pchar)+", из уважения к вам я готов еще немного уступить в цене! Что вы хотите?")),
												  NPCharRepPhrase(npchar,
												     "Клянусь, мне тошно разговаривать с тобой. "
													 +LinkRandPhrase("Купи два-три земляных ореха. Их так любят свиньи. ","Ты ждешь, что здесь тебе сапоги будут чистить ромом? ",
													 pcharrepphrase("Знаю я вашего брата. Налакаетесь рому - и на виселицу.","Как это твоя мамаша отпустила тебя в море! В море!!! Уж лучше бы ты "+ GetSexPhrase("стал портным","стала портнихой") +"...")),
													 pcharrepphrase(RandPhraseSimple("Я полагал, ","Я надеялся, ")+RandPhraseSimple("что вы покинули наш остров.","что больше никогда вас не увижу.")
													 +RandPhraseSimple(" Мертвецы висят у вас на шее, как мельничные жернова..."," Скольких моряков вы отправили гнить среди кораллов?!"),
													 "Капитан " + GetFullName(pchar)+", ваша страсть к коммерции превосходит все мои ожидания!"
													 +RandPhraseSimple(" Хотите сделать последние покупки перед отплытием?", " Вы хотите купить что-то особенное?"))),
										"cycle", 10, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("Давай, показывай, что у тебя есть, старый пират!",
													               "Я всего лишь хочу посмотреть на ваши товары, любезный."),
													pcharrepphrase("Клянусь виселицей, " +GetFullName(npchar)+", я не позволю тебе водить меня за нос! Живо показывай свои товары!",
													               "Давайте посмотрим ваши товары, " +GetAddress_FormToNPC(NPChar)+ ".")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Это точно! Мертвые не кусаются! Ну, что у тебя в трюме есть?",
													               "Вы, милейший, лучше займитесь своим делом. Какие товары можете мне предложить?"),
												    pcharrepphrase("Однажды и ты станешь моим призом, хе-хе. Шучу. Давай свои товары.",
													               "Давайте обсудим торговые дела, " +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ "")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Что мне надо? Хочу купить кое-что!",
													               "Пьянство вас сведет в могилу, " +GetFullName(npchar)+ ". Мне нужно посмотреть ваши товары."),
												    pcharrepphrase("Знаю я твои скидки! Два фунта какао по цене трех! Живо показывай свои товары",
													               "Это всегда приятно. Давайте поторгуемся.")),
											  "Показывай товары, меньше слов и больше дела. Я тороплюсь.",
											  npchar, Dialog.CurrentNode);
			link.l1.go = "market";
			ChangeImport();
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("Эх, так бы и "+ GetSexPhrase("прирезал","прирезала") +" кого-нибудь! Ладно, давай к делу.",
													               "Перейдем к другим делам, милейший"),
													pcharrepphrase("Каррамба! Я совсем по другому делу!",
													               "Мне нужно с вами поговорить по делу, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+".")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("У меня к тебе дело, старый пират!",
													               "Перейдем к делам, милейший!"),
													pcharrepphrase("Клянусь дьяволом, тебе меня не обмануть, мошенник! У меня другое дело!",
													               "Полностью "+ GetSexPhrase("согласен","согласна") +", " +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ ", я хочу обсудить с вами иные дела.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Уже надрался, приятель?! У меня к тебе дело.",
													               "Я "+ GetSexPhrase("пришел","пришла") +" не торговать, любезный. У меня другое дело."),
													pcharrepphrase("Разрази тебя гром с твоими ценами, негодяй! У меня дело к тебе.",
													               "Скидки всегда приятны, " + GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ ", но я по другому делу.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Придержи язык, старый пьяница, у меня дело к тебе",
													               "Тошнит вас от рома, я полагаю. Впрочем, я от вас тоже не в восторге. Перейдем к делу."),
													pcharrepphrase("Ты и так уже обобрал меня до нитки, мошенник! У меня к тебе дело.",
													               "Ваша ирония неуместна, у меня к вам дело иного порядка")),
											   npchar, Dialog.CurrentNode);
			link.l2.go = "business";
			link.l3 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("Сначала дело, потом веселье. Хочу у тебя узнать кое-что.",
													               "Не сейчас, мне нужна информация."),
													pcharrepphrase("К черту цены! Сначала ты скажешь все, что мне нужно.",
													               "С удовольствием. Я хочу узнать кое-что.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Спасибо за совет, старый убийца. Мне надо кое-что узнать.",
													               "У меня определенный вопрос."),
												    pcharrepphrase("Золото подождет. Я хочу узнать кое-что.",
													               "Да, я "+ GetSexPhrase("согласен","согласна") +". Хочу вас спросить кое о чем.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Я думаю, ты знаешь, о чем я хочу спросить.",
													               "Я надеюсь, вы ответите мне на мой вопрос."),
													pcharrepphrase("У тебя в голове есть что-нибудь кроме ценников? Об этом я и хочу спросить.",
													               "Речь не об этом. Мне нужна кое-какая информация.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Не кипятись, старина! Я просто хочу спросить тебя.",
													               "Не волнуйтесь так, вас хватит удар. Ответьте мне на вопрос, и я уйду"),
													pcharrepphrase("Не жду от тебя умного слова - ум у тебя тараканий. Но ты кое-что знаешь.",
													               "Я не задержу вас надолго. Всего один вопрос.")),
											   npchar, Dialog.CurrentNode);
			link.l3.go = "quests";
			//--> eddy. Аскольд, базар с рендомным торговцем
			if (pchar.questTemp.Ascold == "Seek_powder" && pchar.questTemp.Ascold.TraderId == npchar.id && !CheckAttribute(Pchar, "RomanticQuest.TalkInShop"))
			{
				link.l3.go = "AscoldTrader";
			}
			if (pchar.questTemp.Ascold == "PowderWasSeek" && pchar.questTemp.Ascold.TraderId == npchar.id)
			{
				link.l3.go = "AscoldTrader_WasSeek";
			}
			if (CheckAttribute(pchar,"Whisper.Contraband") && npchar.id == "Tortuga_trader" && GetSquadronGoods(Pchar, GOOD_EBONY) >= 100)
			{//Линейка Виспер
				link.l44 = "Здравствуйте. Я взялась выполнить незавершенную работу бывшего капитана моего корабля. В журнале сказано, что я должна вам сотню единиц черного дерева. Все лежит у меня в трюме и готово к разгрузке.";
				link.l44.go = "Whisper_contraband";
			}
			if (CheckAttribute(pchar,"cursed.waitingSkull") && pchar.questTemp.Cursed.TraderId == npchar.id && !CheckAttribute(pchar,"cursed.Skullbought"))
			{
				link.l44 = "У меня к вам несколько необычный вопрос. Дело в том, что я ищу один предмет - "+ GetConvertStr("itmname_"+pchar.questTemp.Cursed.Item, "ItemsDescribe.txt") +". Мне стало известно, что он мог принадлежать владельцу этого магазина.";
				link.l44.go = "buy_skull";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "store_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l9 = "Здравствуйте, я приш"+ GetSexPhrase("ел","ла") +" по приглашению вашего сына.";
					link.l9.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "store_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "Я по поводу вашей дочери...";
						link.l9.go = "EncGirl_1";
					}
				}
			}
			//<-- eddy. Аскольд, базар с рендомным торговцем
			link.l11 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("Пока, старый пропойца.",
													               "Всего доброго, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"."),
													pcharrepphrase("Каррамба! Никуда не уходи. Я еще зайду.",
													               "Приятно было вас видеть, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"! До свидания!")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Отдать швартовы!",
													               "До свидания, милейший."),
													pcharrepphrase("Эй! Ты что там прячешь? Ром? Нет!?! Ну ладно, пойду, горло промочу.",
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
													               ""+ GetSexPhrase("Рад был","Рада была") +" вас видеть, " + GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),
											  npchar, Dialog.CurrentNode);
			link.l11.go = "exit";
		break;

		//Линейка Виспер
		case "Whisper_contraband":
			dialog.text = "Потише, девушка! Вы что, на Карибах впервые?";
			DeleteAttribute(pchar,"Whisper.Contraband");
			link.l1 = "Да, а что, есть какая-то проблема?";
			link.l1.go = "Whisper_contraband_1";
			link.l2 = "Нет...";
			link.l2.go = "Whisper_contraband_1";
		break;
		case "Whisper_contraband_1":
			dialog.text = "Вообще-то черным деревом на Тортуге торговать строго запрещено. Как бы я не хотел, я не смогу принять у вас товар.";
			link.l1 = "Что же мне делать в таком случае? Искать другого покупателя?";
			link.l1.go = "Whisper_contraband_2";
		break;
		case "Whisper_contraband_2":
			dialog.text = "Не стоит так торопиться с выводами. Мы конечно не можем выгрузить товар прямо в порту, на глазах у стражи. Однако, эту формальность возможно обойти\nВы можете немного отплыть от самой колонии и причалить у пляжа, что называется Глаз Рыбы. Он расположен в северной части острова. Там вас встретят мои знакомые ребята и произведут оплату с разгрузкой.";
			link.l1 = "А если нашу сделку заметит какой-нибудь патруль?";
			link.l1.go = "Whisper_contraband_3";
		break;
		case "Whisper_contraband_3":
			dialog.text = "В этом случае вы сами по себе. Если их увидите - лучше бегите. Но не стоит волноваться понапрасну, в названное мной место стража не заглядывает.";
			pchar.Whisper.ContraSmuggler = true;
			WhisperPlaceSmugglersOnShore("Shore58");
			AddQuestRecord("WhisperContraband", "2");
			SetTimerCondition("W_Smuggling", 0, 0, 10, false);
			link.l1 = "Ладно. Тогда поплыву к бухте.";
			link.l1.go = "exit";
		break;
		//Линейка Виспер
		case "buy_skull":
			dialog.text = GetConvertStr("itmname_"+pchar.questTemp.Cursed.Item, "ItemsDescribe.txt") +"? Извините, но это семейная реликвия, она не продается. Много лет назад дед приобрел его у одного пирата, и с тех пор череп ни разу не покидал стен этого магазина.";
			link.l1 = "Не лгите. Для вас, торгашей, все имеет цену, даже родная мать. Сколько хотите за этот череп?";
			link.l1.go = "buy_skull_1";
		break;

		case "buy_skull_1":
			dialog.text = sti(skullprice) + " и ни монетой меньше.";
			if (sti(pchar.Money) >= skullprice)
            {
    			link.l1 = "Вот деньги. Давайте его сюда.";
				link.l1.go = "buy_skull_2";
			}
			link.l2 = "Да за эти деньги я десяток таких черепов куплю. До свидания.";
			link.l2.go = "exit";
		break;

		case "buy_skull_2":
			pchar.cursed.Skullbought = true;
			AddQuestRecord("CursedSkeleton", "2");
			dialog.text = "С вами приятно иметь дело.";
			AddMoneyToCharacter(pchar, -skullprice);
			GiveItem2Character(pchar, pchar.questTemp.Cursed.Item);
    		link.l1 = "Ага, прощайте.";
			link.l1.go = "exit";
		break;



		case "market":
//navy -->
			//занят ПГГ
			if (CheckFreeServiceForNPC(NPChar, "Store") != -1 && drand(4)>=3)	 // to_do имя сунуть
			{
				if (makeint(environment.time) < 16.0)
				{
					dialog.text = "Извините, но я сейчас занят. Другие клиенты! Заходите сегодня попозже.";
					link.l1 = "Я никуда не спешу.";
					link.l1.go = "WasteTime";
					link.l2 = "Да что вы говорите! Ладно, зайду попозже.";
					link.l2.go = "exit";
					break;
				}
			}
//navy <--
			dialog.text = RandPhraseSimple("У меня есть сабли, пистолеты, пушечные ядра, ценная древесина и другие товары! Что вас интересует?", "Хотите купить золото или серебро? Или, может, присмотреть отличный клинок?");
			link.l1 = pcharrepphrase(LinkRandPhrase("В моем трюме полно добычи! Пиастры не пахнут, не так ли?",
			                         "Мне нужно освободить свой трюм от добычи и набить его твоим золотом. Ха-ха!",
									 "За полновесные дублоны ты и родную мать продашь! Но мне всего лишь нужно пополнить запасы."),
									 LinkRandPhrase("Хочу продать груз и пополнить запасы.",
			                         "Я хочу купить товар на продажу.",
									 "Покажи мне ядра, бомбы и прочие товары."));
			link.l1.go = "trade_1";
			link.l2 = LinkRandPhrase("Покажи мне сабли, пистолеты, и что там у тебя еще есть?",
			                         "Мне не помешает пара новых пистолетов, пули и красивый перстень.",
									 "Драгоценные камни, диковинные идолы - вот что меня интересует.");
			link.l2.go = "items";

			link.l3 = pcharrepphrase(RandPhraseSimple("Отчаливаю без торговли. Бывай!",
			                                          "Пойду, горло промочу. Никуда не уходи."),
									 RandPhraseSimple("Нет, мне сейчас не до покупок. Прощайте.",
									                  "Извините, у меня срочное дело. До свидания!"));
			link.l3.go = "exit";
		break;

		case "WasteTime":
			environment.time = 16.0;
			WasteTime(1);
			DialogExit();
		break;

		case "EncGirl_1":
			dialog.text = "Слушаю вас внимательно.";
			link.l1 = "Я привел"+ GetSexPhrase("","а") +" вашу беглянку.";
			link.l1.go = "EncGirl_2";
		break;

		case "EncGirl_2":
			dialog.text = "Ах, капитан, спасибо вам большое! Как она? здорова, не пострадала? Уж скоро сутки, как убежала, негодница. Разве ж я ей плохого желаю? Замуж отдать собрался... Жених богатый, молодой, а что собою не пригож, так ведь с лица воду не пить. Нет! она всё по-своему норовит - вся в мать, чтоб её...\nХотя, и она бы на свет не появилась, если бы её мамаша в своё время не сбежала с одним предприимчивым оболтусом... ну да что вспоминать... Молодость наивна, глупа... и жестока.";
			link.l1 = "Конечно, вы отец и решать вам, но я бы не торопил"+ GetSexPhrase("ся","ась") +" со свадьбой...";
			link.l1.go = "EncGirl_3";
		break;

		case "EncGirl_3":
			dialog.text = "Да что вы понимаете?.. У вас свои дети есть? Нету? Вот, когда будут - заходите, тогда и поговорим...\nДа... я обещал вознаграждение тому, кто её вернёт - примите пожалуйста.";
			link.l1 = "Спасибо. И держите её покрепче. Что-то мне подсказывает, что она на этом не остановится.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;

		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "А, так вы и есть "+ GetSexPhrase("тот капитан, который привёз","та девушка, которая привезла") +" моего блудного сына с молодой невестой?";
				link.l1 = "Да, это я помог"+ GetSexPhrase("","ла") +" им сбежать.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "А-а, явил"+ GetSexPhrase("ся, благодетель","ась, благодетельница") +". Небось награды ждёшь?";
				link.l1 = "Ну, не то, чтобы награды, но благодарность услышать не мешало бы.";
				link.l1.go = "EncGirl_6";
			}
		break;

		case "EncGirl_5":
			dialog.text = "Я очень вам благодарен, что не оставили моё чадо в затруднительном положении и помогли ему с честью выйти из столь щекотливой ситуации. Разрешите отблагодарить вас, как могу. Примите эту скромную сумму и подарок от меня лично.";
			link.l1 = "Благодарю вас, мне было приятно помогать этим молодым людям.";
			link.l1.go = "EncGirl_5_1";
		break;

		case "EncGirl_6":
			dialog.text = "Какая благодарность?! за что благодарность?! Мало того, что этот оболтус уже полгода слоняется без работы, так ещё и любезничать время нашёл! Да я в его годы уже своё дело держал. А он, ишь, разохотился! У губернатора, вон, дочка на выданье, а этот приволок какую-то шалаву безродную, прости Господи, и благословения родительского испрашивает!";
			link.l1 = "Хм, значит вы не верите в искренние чувства?";
			link.l1.go = "EncGirl_6_1";
		break;

		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "EncGirl_6_1":
			dialog.text = "Какие такие чувства?! О каких чувствах вы говорите? Взрослый, вроде человек, а туда же... чувства! Стыдно вам должно быть молодёжи в таких делах потакать да в сводни подряжаться. Девчонку из родительского гнезда вырвали и моему молокососу жизнь сломали. Не будет вам никакой благодарности. Прощайте.";
			link.l1 = "Что ж, и вам не хворать...";
			link.l1.go = "EncGirl_6_2";
		break;

		case "EncGirl_6_2":
			ChangeCharacterReputation(pchar, -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("ел","ла"));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("","а"));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "trade_1":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea) || (Pchar.location == "Caiman_Store");
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
			    DialogExit();
			    Pchar.PriceList.StoreManIdx = rColony.index; // boal 27.02.05
			    LaunchStore(sti(rColony.StoreNum));
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("Дуришь меня? А где же твой корабль? У пирса его нет!",
				                                                     "Клянусь дьяволом, тебе не обмануть меня! У пирса нет твоего корабля!"),
													  pcharrepphrase("Я не вижу вашего корабля в порту, капитан " +GetFullName(pchar)+ ". Надеюсь, это не 'Летучий голландец'?",
													                 "Капитан, удобнее грузить товар с пирса. Пришвартуйте корабль и приходите."));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+"Какая неприятность!!! Ладно, старый проныра, еще увидимся!",
				                                                 "Я не хотел"+ GetSexPhrase("","а") +" вас обмануть " +GetFullName(npchar)+ ", корабль на другой стороне острова."),
												  pcharrepphrase("Нет. Мой корабль называется Black Pearl. Что это ты побелел? Ха-ха! Шутка!",
												                 "Спасибо за совет, обязательно им воспользуюсь."));
			    link.l1.go = "exit";//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
		break;

		case "storage_0":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.Storage.MoneyForStorage);
			if(sti(NPChar.MoneyForStorage) > 0)
			{
				dialog.text = "С вас за аренду еще " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + ".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
				{
					link.l1 = "Хорошо, сейчас оплачу аренду.";
					link.l1.go = "storage_3";
				}
				else
				{
					link.l1 = "Я зайду попозже.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Проходите.";
				link.l1 = "Спасибо.";
				link.l1.go = "storage_2";
			}
			link.l2 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			link.l2.go = "exit";
		break;

		case "storage_01":
			dialog.text = "Нет, "+ GetSexPhrase("уважаемый","мэм") +", стоит - вас дожидается. Я как знал, что вы не оставите этого предложения.";
			link.l1 = "Это хорошо. Я его арендую.";
			link.l1.go = "storage_1";
			link.l2 = "Да нет, я просто так вспомнил"+ GetSexPhrase("","а") +". Может когда и понадобится...";
			link.l2.go = "exit";
		break;

		case "storage_1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
			dialog.text = "Как вы помните - оплата за месяц вперёд.";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "Помню - держите.";
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = "Вот чёрт. Сейчас деньги принесу.";
				link.l1.go = "exit";
			}
		break;

		case "storage_11":
			AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForStorage));
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			NPChar.Storage.Activate = true;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));
		break;

		case "storage_2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));
		break;

		case "storage_3":
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage));
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));
		break;

		case "storage_04":
			dialog.text = "Неужели освобождаете? Ай-яй-яй, такое великолепное место, такие выгодные условия. Уверяю - больше нигде на Карибах вам не предложат подобных услуг.";
			link.l1 = "Я же сказал"+ GetSexPhrase("","а") +" - освобождаю. Или вы предлагаете мне платить за хранение воздуха? Можете искать другого арендатора.";
			link.l1.go = "storage_4";
			link.l2 = "Нигде не предложат, говорите? Ладно, оставлю пока за собой. Но цена аренды, долж"+ GetSexPhrase("ен","на") +" сказать... немаленькая, одним словом.";
			link.l2.go = "exit";
		break;

		case "storage_4":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar,"Storage.Date") * sti(NPChar.Storage.MoneyForStorage);
			if(sti(NPChar.MoneyForStorage) > 0)
			{
				dialog.text = "С вас за аренду еще " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + ".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
				{
					link.l1 = "Хорошо.";
					link.l1.go = "storage_5";
				}
			}
			else
			{
				dialog.text = "Забирайте свой товар и я закрою склад.";
				link.l1 = "Хорошо.";
				link.l1.go = "storage_6";
			}
		break;

		case "storage_5":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage));
			NPChar.Storage.NoActivate = true;
			DeleteAttribute(NPChar,"Storage.Activate");
			DialogExit();
		break;

		case "storage_6":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			DeleteAttribute(NPChar,"Storage.Activate");
			NPChar.Storage.NoActivate = true;
			DialogExit();
		break;

		case "items":
			if (npchar.quest.item_date != lastspeak_date)
			{
				GiveItemToTrader(npchar);
				npchar.quest.item_date = lastspeak_date;
			}
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar);
		break;

		case "business":
			iTest = 0;
    		//квест Синей Птицы, начальный диалог
			if (pchar.questTemp.BlueBird == "begin" && sti(npchar.nation) != PIRATE && npchar.city != "Panama")
			{
				dialog.text = RandPhraseSimple("Капитан, прошу вас, помогите нам!!!", "Капитан, я прошу у вас помощи от имени всех торговцев!");
				link.l1 = "Что случилось? Чем я могу вам помочь?";
				link.l1.go = "RBlueBird";
				break;
			}
//navy -->
			//занят ПГГ
			iTmp = CheckAvailableTaskForNPC(NPChar, PGG_TASK_WORKONSTORE);
			if (iTmp != -1)
			{
				dialog.text = "Была у меня работенка, но " + GetFullName(&Characters[iTmp]) + " уже взялся выполнить ее для меня.";
				link.l1 = "Да что вы говорите! Ладно, зайду попозже.";
				link.l1.go = "exit";
				break;
			}
//navy <--
			dialog.text = NPCharRepPhrase(npchar,"Дела?! Выкладывай все по порядку!","Я вас слушаю. О каком деле идет речь?");
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea) || (Pchar.location.from_sea == "Shore17");
            if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
    			/*if (CheckAttribute(pchar, "CargoQuest.iQuantityGoods"))
    			{
    				int iQuantityShipGoods = pchar.CargoQuest.iQuantityGoods;
    				int iQuestTradeGoods = pchar.CargoQuest.iTradeGoods;
    			}  */
    			if (CheckQuestAttribute("generate_trade_quest_progress", "begin") || CheckQuestAttribute("generate_trade_quest_progress",  "failed"))
    			{
    				if (pchar.CargoQuest.TraderID == npchar.id )//&&  GetSquadronGoods(pchar, iQuestTradeGoods) >= iQuantityShipGoods)
    				{
    					link.l1 = RandPhraseSimple("В трюме моего корабля груз для вашего магазина.", "Мой корабль зафрахтован для доставки груза в ваш магазин. Товар уже выгружают.");
    					link.l1.go = "generate_quest_2";
    				}
    				else
    				{
                        if (!CheckQuestAttribute("generate_trade_quest_progress",  "failed") && pchar.CargoQuest.GiveTraderID == npchar.id && GetNationRelation2MainCharacter(sti(characters[GetCharacterIndex(pchar.CargoQuest.TraderID)].nation)) == RELATION_ENEMY)
                        {
                            link.l1 = "К сожалению, я вынужден"+ GetSexPhrase("","а") +" отказаться от взятых обязательств. Политическая обстановка не позволяет мне доставить груз.";
            				link.l1.go = "generate_quest_cannot_done";
                        }
                        else
                        {
                            if (rand(1) == 1)
                            {
                                link.l1 = RandPhraseSimple("Я хочу предложить вам зафрахтовать мое судно для перевозки груза.",
								                           "У меня прекрасный корабль, и я могу доставить любой груз, куда только вы пожелаете.");
            				    link.l1.go = "generate_quest_not_closed";
        				    }
    				    }
    				}
    			}
    			else
    			{
    				link.l1 = "Не хотите зафрахтовать судно, " +GetAddress_FormToNPC(NPChar)+ "? У меня надежный корабль и опытные матросы.";
    				link.l1.go = "generate_quest";
    			}
    			// --> на кредитный генератор
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
    			{
	                link.l3 = pcharrepphrase(RandPhraseSimple("Эх, вымотал"+ GetSexPhrase("ся","ась") +" в море... Вот что, приятель, денежный вопрос стоит остро.",
	                                                          "Ну что, старый плут, давай обсудим дела наши денежные."),
	                                        RandPhraseSimple("Я хотел"+ GetSexPhrase("","а") +" бы обсудить с вами финансовые вопросы.",
	                                                         "Давайте обсудим финансовые вопросы, нам есть о чем переговорить."));,

	                link.l3.go = "LoanForAll";
                }
				//квест мэра - на связь с нашим шпионом
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "")
				{
					link.l4 = RandPhraseSimple("Я здесь по поручению одного человека. Его зовут губернатор " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".",
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " прислал меня к вам. Я долж"+ GetSexPhrase("ен","на") +" кое-что забрать...");
					link.l4.go = "IntelligenceForAll";
				}
				// ----------------- квест получения Синей Птицы, сдаем квест -----------------
				if (pchar.questTemp.BlueBird == "weWon" && pchar.questTemp.BlueBird.traiderId == npchar.id)
				{
					link.l1 = "Хочу вас уведомить, что мне удалось справиться с вашим поручением. Шебека 'Синяя Птица' не будет более досаждать торговцам. Я прибыл"+ GetSexPhrase("","а") +" за условленным гонораром.";
					link.l1.go = "RBlueBirdWon";
				}
				if (pchar.questTemp.BlueBird == "DieHard" && pchar.questTemp.BlueBird.traiderId == npchar.id)
				{
					link.l1 = "Долж"+ GetSexPhrase("ен","на") +" вам сообщить, что мне не удалось потопить шебеку 'Синяя Птица'. Я сделал все, что мог...";
					link.l1.go = "RBlueBirdDieHard";
				}
				if (pchar.questTemp.BlueBird == "returnMoney" && pchar.questTemp.BlueBird.traiderId == npchar.id && sti(pchar.questTemp.BlueBird.count) > 0)
				{
					if (sti(pchar.questTemp.BlueBird.count) < 5)
					{
						link.l1 = "Как собственные флейты ваших коллег поживают? Все нормально?";
						link.l1.go = "RBlueBird_retMoney_1";
					}
					else
					{
						link.l1 = "Вы еще не одумались, не желаете отдать мне мои честно заработанные деньги?";
						link.l1.go = "RBlueBird_retMoney_3";
					}
				}
				// ----------------- квест получения Синей Птицы, продолжение -----------------
				//homo 25/06/06 слухи
                link.l6 = pcharrepphrase(RandPhraseSimple("Расскажешь мне последние сплетни? Все равно торчишь тут целый день.",
                                                          "Не суетись, старый мошенник, а лучше расскажи, как течет жизнь на суше?"),
                                        RandPhraseSimple("Кажется, что провел"+ GetSexPhrase("","а") +" в море целую вечность. Что новенького в ваших краях?",
                                                         "Вы, наверное, знаете все последние новости? Что важного произошло?"));,

    		    link.l6.go = "rumours_trader";

				// ugeen --> склад товаров для ГГ
				if(NPChar.city != "Pirates")
				{
					if(!CheckAttribute(NPChar,"Storage.NoActivate"))
					{
						link.l7 = "Можно ли арендовать у вас склад?";
						link.l7.go = "storage_rent";
					}
					if(CheckAttribute(NPChar,"Storage.NoActivate") && !CheckAttribute(NPChar,"Storage.Activate"))
					{
						link.l7 = "Я хотел бы вновь арендовать у вас склад.";
						link.l7.go = "storage_rent";
					}
				}
				if(CheckAttribute(NPChar,"Storage"))
				{
					if(CheckAttribute(NPChar,"Storage.Activate"))
					{
						link.l7 = "Проводите меня в пакгауз. Я хочу взглянуть на состояние своего склада.";
						link.l7.go = "storage_0";
						link.l8 = "Я решил"+ GetSexPhrase("","а") +" освободить пакгауз. Он мне больше без надобности.";
						link.l8.go = "storage_04";
					}
					else
					{
						if(!CheckAttribute(NPChar,"Storage.NoActivate") && CheckAttribute(pchar,"questTemp.BlueBird.speakWon"))
						{
							link.l7 = "Помнится, вы как-то о складе упоминали. Место ещё не занято?";
							link.l7.go = "storage_01";
						}
					}
				}
				// <-- ugeen
				// <-- homo
				link.l99 = "Впрочем, сейчас не до разговоров.";
    			link.l99.go = "no_quests";
			}
			else
			{
                link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+"Я оставил"+ GetSexPhrase("","а") +" корабль на другой стороне острова. Зайду попозже!", "Прошу меня простить, " +GetFullName(npchar)+ ", я зайду позже. Мой корабль еще не подошел к пирсу."), pcharrepphrase("Дьявол! Эти ротозеи не поставили корабль под погрузку! Зайду позже!", "Извините, я долж"+ GetSexPhrase("ен","на") +" приказать поставить свой корабль к пирсу!"));
                link.l1.go = "exit";
    			// --> на кредитный генератор
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
    			{
	                link.l3 = pcharrepphrase(RandPhraseSimple("Эх, вымотал"+ GetSexPhrase("ся","ась") +" в море... Вот что, приятель, денежный вопрос стоит остро.",
	                                                          "Ну что, старый плут, давай обсудим дела наши денежные."),
	                                        RandPhraseSimple("Я хотел"+ GetSexPhrase("","а") +" бы обсудить с вами финансовые вопросы.",
	                                                         "Давайте обсудим финансовые вопросы, нам есть о чем переговорить."));,

	                link.l3.go = "LoanForAll";
                }
				//квест мэра - на связь с нашим шпионом
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "")
				{
					link.l7 = RandPhraseSimple("Я здесь по поручению одного человека. Его зовут губернатор " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".",
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " прислал меня к вам. Я долж"+ GetSexPhrase("ен","на") +" кое-что забрать...");
					link.l7.go = "IntelligenceForAll";
				}
			}
		break;

		case "generate_quest":
			if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
				dialog.text = "Нет, не нужно! По крайней мере, до тех пор, пока вы враждуете с " + NationNameAblative(sti(NPChar.nation)) + ".";
				link.l1 = "В таком случае, прощайте.";
				link.l1.go = "exit";
			}
			else
			{
				// проверка на проф пригодность -->
				if (isBadReputation(pchar, 42))
				{
					dialog.text = RandSwear() + "Ты ведь " + GetFullName(pchar)+ ", не так ли? О тебе " +
								  RandPhraseSimple("ходят ужасные слухи","говорят не лучшим образом") + ", я не хочу иметь с тобой дело.";
					link.l1 = RandPhraseSimple("Эх... стоит человеку раз оступиться, и все будут в него плевать.",
											   RandSwear()+ "Что же, в море есть занятия и поинтереснее, "+GetFullName(npchar)+".");
					link.l1.go = "exit";
					break;
				}
				// проверка на проф пригодность <--

				if (CheckAttribute(Npchar, "CargoQuest.Cooldown") && GetNpcQuestPastDayParam(Npchar, "Cooldown") < sti(npchar.CargoQuest.Cooldown))
				{
					iTmp = sti(npchar.CargoQuest.Cooldown) - GetNpcQuestPastDayParam(Npchar, "Cooldown");
					iDay = " дней.";
					if (iTmp == 1) { iDay = " день."; }
					else { if (iTmp <= 4) iDay = " дня."; }
					dialog.text = "Извините, сейчас заказов нет. Заходите через " + iTmp + iDay;
					link.l1 = "Хорошо, подожду.";
					link.l1.go = "exit";
					break;
				}

				npchar.iTradeNation1 = GenerateNationTrade(sti(NPChar.nation));
				npchar.iTradeNation2 = GenerateNationTrade(sti(NPChar.nation));
				npchar.iTradeNation3 = GenerateNationTrade(sti(NPChar.nation));

				if (sti(npchar.iTradeNation1) < 0 && sti(npchar.iTradeNation2) < 0 && sti(npchar.iTradeNation3) < 0)
				{
					dialog.text = NPCharRepPhrase(npchar, "Эх, "+GetAddress_Form(NPChar)+", не до фрахтов сегодня. Приходите завтра.","Зайдите завтра. Возможно, я сделаю вам выгодное предложение.");
					link.l1 = "Хорошо, я зайду завтра.";
					link.l1.go = "exit";
				}
				else
				{
					npchar.storeMan1 = findStoreMan(NPChar,0);
					npchar.storeMan2 = findStoreMan(NPChar,1);
					npchar.storeMan3 = findStoreMan(NPChar,2);

					if (sti(npchar.storeMan1) <= 0 || sti(npchar.storeMan2) <= 0 || sti(npchar.storeMan3) <= 0)
					{
						dialog.text = "Политическая обстановка на архипеллаге не позволяет мне торговать. "+
									  XI_ConvertString(NationShortName(sti(NPChar.nation))+"hunter") + " во вражде со всеми, и магазин остался только у меня.";
						link.l1 = "О! Сожалею. Всего хорошего.";
						link.l1.go = "exit";
					}
					else
					{
						//проверяем импорт/экспорт
						npchar.iTradeGoods1 = GOOD_CHOCOLATE + drand(GOOD_BRICK-GOOD_CHOCOLATE); //Рабы и золото не даем, бомбы и еду - да!!
						npchar.iTradeGoods2 = GOOD_CHOCOLATE + drand1(GOOD_BRICK-GOOD_CHOCOLATE); //Рабы и золото не даем, бомбы и еду - да!!
						npchar.iTradeGoods3 = GOOD_CHOCOLATE + drand2(GOOD_BRICK-GOOD_CHOCOLATE); //Рабы и золото не даем, бомбы и еду - да!!
						//проверяем свободное место (при этом должно вмещаться по меньшей мере 100 единиц выбранного груза
						RecalculateSquadronCargoLoad(pchar); // fix неверное место
						if (CheckOfficersPerk(pchar,"Trader"))
						{
							npchar.iQuantityGoods1 = GetSquadronFreeSpace(pchar, sti(npchar.iTradeGoods1));
							npchar.iQuantityGoods2 = GetSquadronFreeSpace(pchar, sti(npchar.iTradeGoods2));
							npchar.iQuantityGoods3 = GetSquadronFreeSpace(pchar, sti(npchar.iTradeGoods3));
						}
						else
						{
							iQuantityGoods = GetSquadronFreeSpace(pchar, sti(npchar.iTradeGoods1));
							npchar.iQuantityGoods1 = iQuantityGoods - drand(iQuantityGoods / 4 - drand(iQuantityGoods / 5));
							iQuantityGoods = GetSquadronFreeSpace(pchar, sti(npchar.iTradeGoods2));
							npchar.iQuantityGoods2 = iQuantityGoods - drand1(iQuantityGoods / 4 - drand1(iQuantityGoods / 5));
							iQuantityGoods = GetSquadronFreeSpace(pchar, sti(npchar.iTradeGoods3));
							npchar.iQuantityGoods3 = iQuantityGoods - drand2(iQuantityGoods / 4 - drand2(iQuantityGoods / 5));
						}
						if (sti(npchar.iQuantityGoods1) < 100 || sti(npchar.iQuantityGoods2) < 100 || sti(npchar.iQuantityGoods3) < 100)// это в шт. товара
						{
							dialog.text = NPCharRepPhrase(npchar, "В твою жалкую посудину не поместится весь груз, сегодня сделки не будет.","К сожалению, капитан "+GetFullName(pchar)+", для доставки груза мне нужен более вместительный корабль, чем ваш.");
							link.l1 = NPCharRepPhrase(npchar, "У меня достойный корабль, но я понял вашу мысль. До свиданья.","Я вас понимаю, бизнес прежде всего. Прощайте.");
							link.l1.go = "exit";
						}
						else
						{
							npchar.iTradeIsland1 = GetIslandByCityName(Characters[sti(npchar.storeMan1)].city);
							npchar.iTradeIsland2 = GetIslandByCityName(Characters[sti(npchar.storeMan2)].city);
							npchar.iTradeIsland3 = GetIslandByCityName(Characters[sti(npchar.storeMan3)].city);

							if (CheckOfficersPerk(pchar,"Trader"))
							{
								npchar.iDaysExpired1 = (GetMaxDaysFromIsland2Island(GetArealByCityName(NPChar.city),GetArealByCityName(Characters[sti(npchar.storeMan1)].city))/2 - drand(MakeInt(GetMaxDaysFromIsland2Island(GetArealByCityName(Characters[sti(npchar.storeMan1)].city),GetArealByCityName(NPChar.city))/20 * 4))) * 2 + 1 + drand(MakeInt(GetMaxDaysFromIsland2Island(GetArealByCityName(Characters[sti(npchar.storeMan1)].city),GetArealByCityName(NPChar.city))/8 * 3) - 1));
								npchar.iDaysExpired2 = (GetMaxDaysFromIsland2Island(GetArealByCityName(NPChar.city),GetArealByCityName(Characters[sti(npchar.storeMan2)].city))/2 - drand1(MakeInt(GetMaxDaysFromIsland2Island(GetArealByCityName(Characters[sti(npchar.storeMan2)].city),GetArealByCityName(NPChar.city))/20 * 4))) * 2 + 1 + drand1(MakeInt(GetMaxDaysFromIsland2Island(GetArealByCityName(Characters[sti(npchar.storeMan2)].city),GetArealByCityName(NPChar.city))/8 * 3) - 1));
								npchar.iDaysExpired3 = (GetMaxDaysFromIsland2Island(GetArealByCityName(NPChar.city),GetArealByCityName(Characters[sti(npchar.storeMan3)].city))/2 - drand2(MakeInt(GetMaxDaysFromIsland2Island(GetArealByCityName(Characters[sti(npchar.storeMan3)].city),GetArealByCityName(NPChar.city))/20 * 4))) * 2 + 1 + drand2(MakeInt(GetMaxDaysFromIsland2Island(GetArealByCityName(Characters[sti(npchar.storeMan3)].city),GetArealByCityName(NPChar.city))/8 * 3) - 1));
							}
							else //Lipsar переделал формулы (ВСЕ(Почти)). Что бы поменять кол-во дней просто меняеете цифры вот тут -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------> Сверху торгаш Снизу обычный. А так же тут ---------------------------------------------------------------------------------------------->
							{
								npchar.iDaysExpired1 = GetMaxDaysFromIsland2Island(GetArealByCityName(NPChar.city),GetArealByCityName(Characters[sti(npchar.storeMan1)].city))/2 - MakeInt(GetMaxDaysFromIsland2Island(GetArealByCityName(NPChar.city),GetArealByCityName(Characters[sti(npchar.storeMan1)].city))/20 * 4) + 1 + drand(MakeInt(GetMaxDaysFromIsland2Island(GetArealByCityName(Characters[sti(npchar.storeMan1)].city),GetArealByCityName(NPChar.city))/8 * 3) - 1));
								npchar.iDaysExpired2 = GetMaxDaysFromIsland2Island(GetArealByCityName(NPChar.city),GetArealByCityName(Characters[sti(npchar.storeMan2)].city))/2 - MakeInt(GetMaxDaysFromIsland2Island(GetArealByCityName(NPChar.city),GetArealByCityName(Characters[sti(npchar.storeMan2)].city))/20 * 4) + 1 + drand1(MakeInt(GetMaxDaysFromIsland2Island(GetArealByCityName(Characters[sti(npchar.storeMan2)].city),GetArealByCityName(NPChar.city))/8 * 3) - 1));
								npchar.iDaysExpired3 = GetMaxDaysFromIsland2Island(GetArealByCityName(NPChar.city),GetArealByCityName(Characters[sti(npchar.storeMan3)].city))/2 - MakeInt(GetMaxDaysFromIsland2Island(GetArealByCityName(NPChar.city),GetArealByCityName(Characters[sti(npchar.storeMan3)].city))/20 * 4) + 1 + drand2(MakeInt(GetMaxDaysFromIsland2Island(GetArealByCityName(Characters[sti(npchar.storeMan3)].city),GetArealByCityName(NPChar.city))/8 * 3) - 1));
							}

							if(CheckOfficersPerk(pchar,"Trader"))
							{
								npchar.iMoney1 = makeint(sti(npchar.iQuantityGoods1) / sti(Goods[sti(npchar.iTradeGoods1)].Units) * sti(Goods[sti(npchar.iTradeGoods1)].Weight) * GetMaxDaysFromIsland2Island(GetArealByCityName(NPChar.city),GetArealByCityName(Characters[sti(npchar.storeMan1)].city)) / 2 / (sti(npchar.iDaysExpired1)/2)) * (9 + sti(pchar.Skill.Commerce) / 18);
								npchar.iMoney2 = makeint(sti(npchar.iQuantityGoods2) / sti(Goods[sti(npchar.iTradeGoods2)].Units) * sti(Goods[sti(npchar.iTradeGoods2)].Weight) * GetMaxDaysFromIsland2Island(GetArealByCityName(NPChar.city),GetArealByCityName(Characters[sti(npchar.storeMan2)].city)) / 2 / (sti(npchar.iDaysExpired2)/2)) * (9 + sti(pchar.Skill.Commerce) / 18);
								npchar.iMoney3 = makeint(sti(npchar.iQuantityGoods3) / sti(Goods[sti(npchar.iTradeGoods3)].Units) * sti(Goods[sti(npchar.iTradeGoods3)].Weight) * GetMaxDaysFromIsland2Island(GetArealByCityName(NPChar.city),GetArealByCityName(Characters[sti(npchar.storeMan3)].city)) / 2 / (sti(npchar.iDaysExpired3)/2)) * (9 + sti(pchar.Skill.Commerce) / 18);
							}
							else
							{
								npchar.iMoney1 = makeint(sti(npchar.iQuantityGoods1) / sti(Goods[sti(npchar.iTradeGoods1)].Units) * sti(Goods[sti(npchar.iTradeGoods1)].Weight) * GetMaxDaysFromIsland2Island(GetArealByCityName(NPChar.city),GetArealByCityName(Characters[sti(npchar.storeMan1)].city)) / 2 / sti(npchar.iDaysExpired1)) * (9 + sti(pchar.Skill.Commerce) / 20);
								npchar.iMoney2 = makeint(sti(npchar.iQuantityGoods2) / sti(Goods[sti(npchar.iTradeGoods2)].Units) * sti(Goods[sti(npchar.iTradeGoods2)].Weight) * GetMaxDaysFromIsland2Island(GetArealByCityName(NPChar.city),GetArealByCityName(Characters[sti(npchar.storeMan2)].city)) / 2 / sti(npchar.iDaysExpired2)) * (9 + sti(pchar.Skill.Commerce) / 20);
								npchar.iMoney3 = makeint(sti(npchar.iQuantityGoods3) / sti(Goods[sti(npchar.iTradeGoods3)].Units) * sti(Goods[sti(npchar.iTradeGoods3)].Weight) * GetMaxDaysFromIsland2Island(GetArealByCityName(NPChar.city),GetArealByCityName(Characters[sti(npchar.storeMan3)].city)) / 2 / sti(npchar.iDaysExpired3)) * (9 + sti(pchar.Skill.Commerce) / 20);
							}
							SaveCurrentQuestDateParam("CargoQuest");
							NPChar.sNation1 = XI_ConvertString("Colony"+Characters[sti(npchar.storeMan1)].city);
							NPChar.sNation2 = XI_ConvertString("Colony"+Characters[sti(npchar.storeMan2)].city);
							NPChar.sNation3 = XI_ConvertString("Colony"+Characters[sti(npchar.storeMan3)].city);
							NPChar.sTemp1 = "";
							NPChar.sTemp2 = "";
							NPChar.sTemp3 = "";
							if (npchar.iTradeIsland1 != Characters[sti(npchar.storeMan1)].city)
							{
								NPChar.sTemp1 = ", что на " + XI_ConvertString(npchar.iTradeIsland1+"Dat");
							}
							if (npchar.iTradeIsland2 != Characters[sti(npchar.storeMan2)].city)
							{
								NPChar.sTemp2 = ", что на " + XI_ConvertString(npchar.iTradeIsland2+"Dat");
							}
							if (npchar.iTradeIsland3 != Characters[sti(npchar.storeMan3)].city)
							{
								NPChar.sTemp3 = ", что на " + XI_ConvertString(npchar.iTradeIsland3+"Dat");
							}

							//dialog.text =  "Одну минуту, сейчас найду свой журнал\nВот, что мне нужно сейчас доставить. Груз " + GetGoodsNameAlt(sti(npchar.iTradeGoods1))+ " в количестве " + FindRussianQtyString(sti(npchar.iQuantityGoods1)) + " в город " + NPChar.sNation1 + NPChar.sTemp1 + " за " +  FindRussianDaysString(makeint(sti(npchar.iDaysExpired1))) +", вознаграждение - " +FindRussianMoneyString(sti(npchar.iMoney1)) + ". Еще есть груз " + GetGoodsNameAlt(sti(npchar.iTradeGoods2))+ " в количестве " + FindRussianQtyString(sti(npchar.iQuantityGoods2)) + " в город " + NPChar.sNation2 + NPChar.sTemp2 + " за " +  FindRussianDaysString(makeint(sti(npchar.iDaysExpired2))) +", вознаграждение - " +FindRussianMoneyString(sti(npchar.iMoney2)) + ". А также груз " + GetGoodsNameAlt(sti(npchar.iTradeGoods3))+ " в количестве " + FindRussianQtyString(sti(npchar.iQuantityGoods3)) + " в город " + NPChar.sNation3 + NPChar.sTemp3 + " за " +  FindRussianDaysString(makeint(sti(npchar.iDaysExpired3))) +", вознаграждение - " +FindRussianMoneyString(sti(npchar.iMoney3)) + ".";
							dialog.text =  "Одну минуту, сейчас найду свой журнал\nВот, что мне нужно сейчас доставить. Выбирайте, какой заказ вам больше всего подходит."
							link.l1 = "Я возьмусь доставить груз " + GetGoodsNameAlt(sti(npchar.iTradeGoods1)) + " в количестве " + FindRussianQtyString(sti(npchar.iQuantityGoods1)) + " в город " + NPChar.sNation1 + NPChar.sTemp1 + ", за " +  FindRussianMoneyString(sti(npchar.iMoney1)) +", не позднее чем за " + FindRussianDaysString(makeint(sti(npchar.iDaysExpired1))) + ".";
							link.l1.go = "exit_trade1";
							link.l2 = "Я возьмусь доставить груз " + GetGoodsNameAlt(sti(npchar.iTradeGoods2)) + " в количестве " + FindRussianQtyString(sti(npchar.iQuantityGoods2)) + " в город " + NPChar.sNation2 + NPChar.sTemp2 + ", за " +  FindRussianMoneyString(sti(npchar.iMoney2)) +" не позднее чем за " + FindRussianDaysString(makeint(sti(npchar.iDaysExpired2))) + ".";
							link.l2.go = "exit_trade2";
							link.l3 = "Я возьмусь доставить груз " + GetGoodsNameAlt(sti(npchar.iTradeGoods3)) + " в количестве " + FindRussianQtyString(sti(npchar.iQuantityGoods3)) + " в город " + NPChar.sNation3 + NPChar.sTemp3 + ", за " +  FindRussianMoneyString(sti(npchar.iMoney3)) +" не позднее чем за " + FindRussianDaysString(makeint(sti(npchar.iDaysExpired3))) + ".";
							link.l3.go = "exit_trade3";
							link.l4  = "Мне нужно подумать.";
							link.l4.go = "exit";
						}
					}
				}
			}
		break;

		case "exit_trade":
			AddDialogExitQuest("trade_quest_open");
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;
		case "exit_trade1":
			dialog.text = "Отлично! Разрешите приступить к погрузке.";
			link.l1 = "Приступайте, уважаемый!";
			link.l1.go = "exit";
			pchar.CargoQuest.iDaysExpired = sti(npchar.iDaysExpired1);
    		pchar.CargoQuest.iTradeGoods = npchar.iTradeGoods1;
    		pchar.CargoQuest.iQuantityGoods = sti(npchar.iQuantityGoods1);
    		pchar.CargoQuest.iMoney = sti(npchar.iMoney1);
    		pchar.CargoQuest.iTradeNation = sti(npchar.iTradeNation1);
    		pchar.CargoQuest.iTradeColony = Characters[sti(npchar.storeMan1)].city;
    		pchar.CargoQuest.iTradeIsland = npchar.iTradeIsland1;
			pchar.CargoQuest.TraderID     = Characters[sti(npchar.storeMan1)].id;
    		pchar.CargoQuest.GiveTraderID = NPChar.id;
			Npchar.CargoQuest.Cooldown = MakeInt(sti(npchar.iQuantityGoods1)/sti(Goods[sti(npchar.iTradeGoods1)].units)*sti(Goods[sti(npchar.iTradeGoods1)].weight)/1000);
			SaveCurrentNpcQuestDateParam(Npchar, "Cooldown");
			AddDialogExitQuest("trade_quest_open");
			Nextdiag.CurrentNode = Nextdiag.TempNode;
		break;
		case "exit_trade2":
			dialog.text = "Отлично! Разрешите приступить к погрузке.";
			link.l1 = "Приступайте, уважаемый!";
			link.l1.go = "exit";
			pchar.CargoQuest.iDaysExpired = sti(npchar.iDaysExpired2);
    		pchar.CargoQuest.iTradeGoods = npchar.iTradeGoods2;
    		pchar.CargoQuest.iQuantityGoods = sti(npchar.iQuantityGoods2);
    		pchar.CargoQuest.iMoney = sti(npchar.iMoney2);
    		pchar.CargoQuest.iTradeNation = sti(npchar.iTradeNation2);
    		pchar.CargoQuest.iTradeColony = Characters[sti(npchar.storeMan2)].city;
    		pchar.CargoQuest.iTradeIsland = npchar.iTradeIsland2;
			pchar.CargoQuest.TraderID     = Characters[sti(npchar.storeMan2)].id;
    		pchar.CargoQuest.GiveTraderID = NPChar.id;
			Npchar.CargoQuest.Cooldown = MakeInt(sti(npchar.iQuantityGoods2)/sti(Goods[sti(npchar.iTradeGoods2)].units)*sti(Goods[sti(npchar.iTradeGoods2)].weight)/1000);
			SaveCurrentNpcQuestDateParam(Npchar, "Cooldown");
			AddDialogExitQuest("trade_quest_open");
			Nextdiag.CurrentNode = Nextdiag.TempNode;
		break;
		case "exit_trade3":
			dialog.text = "Отлично! Разрешите приступить к погрузке.";
			link.l1 = "Приступайте, уважаемый!";
			link.l1.go = "exit";
			pchar.CargoQuest.iDaysExpired = sti(npchar.iDaysExpired3);
    		pchar.CargoQuest.iTradeGoods = npchar.iTradeGoods3;
    		pchar.CargoQuest.iQuantityGoods = sti(npchar.iQuantityGoods3);
    		pchar.CargoQuest.iMoney = sti(npchar.iMoney3);
    		pchar.CargoQuest.iTradeNation = sti(npchar.iTradeNation3);
    		pchar.CargoQuest.iTradeColony = Characters[sti(npchar.storeMan3)].city;
    		pchar.CargoQuest.iTradeIsland = npchar.iTradeIsland3;
			pchar.CargoQuest.TraderID     = Characters[sti(npchar.storeMan3)].id;
    		pchar.CargoQuest.GiveTraderID = NPChar.id;
			Npchar.CargoQuest.Cooldown = MakeInt(sti(npchar.iQuantityGoods3)/sti(Goods[sti(npchar.iTradeGoods3)].units)*sti(Goods[sti(npchar.iTradeGoods3)].weight)/1000);
			SaveCurrentNpcQuestDateParam(Npchar, "Cooldown");
			AddDialogExitQuest("trade_quest_open");
			Nextdiag.CurrentNode = Nextdiag.TempNode;
		break;

		case "generate_quest_2":
			if (pchar.quest.generate_trade_quest_progress == "failed")
			{
				dialog.text = RandSwear() + "Вы вспомнили о порученном вам деле слишком поздно, не находите? Мне пришлось заказывать товар повторно. Прощайте.";
				link.l1 = "Простите меня, но я так спешил"+ GetSexPhrase("","а") +". Возможно, если я покрою ваши убытки, это восстановит мою деловую репутацию?";
				link.l1.go = "generate_quest_failed";
				link.l9 = "Всего хорошего.";
				link.l9.go = "exit";
				ChangeCharacterReputation(pchar, -1);
			}
			else
			{
                iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
                iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);

                dialog.text = "Точно! Я его давно ждал. Вы должны доставить мне груз " +
                GetGoodsNameAlt(iTradeGoods) + " в количестве " + FindRussianQtyString(iQuantityGoods) + " и получить за это " +
                FindRussianMoneyString(sti(pchar.CargoQuest.iMoney)) + ".";
				link.l1 = "Именно так.";
				link.l1.go = "generate_quest_ready";
			}
		break;

		case "generate_quest_ready":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);

            // блок кидалова нас на бабки -->
            if (rand(8) == 1 && sti(Goods[iTradeGoods].Cost) <= 44 && GetQuestPastDayParam("CargoQuest") > 5)
            {
                dialog.text = RandSwear() + "Я вынужден извиниться перед вами, "+GetAddress_Form(NPChar)+
                              ". Дело в том, что я " + RandPhraseSimple("в затруднительном положении и не смогу оплатить ваши услуги"," уже взял этот груз в другом месте по более выгодной цене")+
                              ". В качестве оплаты вашего фрахта я передаю вам весь доставленный вами груз.";
				link.l1 = RandSwear() + RandPhraseSimple("И я берег"+ GetSexPhrase("","ла") +" этот чертов груз от всех напастей!!! Я две сотни крыс из-за него убил"+ GetSexPhrase("","а") +"!",
                                                         "Вы ставите меня в безвыходное положение, и мне придется согласиться.");
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, 2);
				AddCharacterExpToSkill(pchar, "Sailing", 60);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCharacterExpToSkill(pchar, "COMMERCE", 15);

				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";

                AddQuestRecord("DELIVERY_TRADE_QUEST", "4");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Dat"));
                CloseQuestHeader("DELIVERY_TRADE_QUEST");

				pchar.questTemp.genquestcount = sti(pchar.questTemp.genquestcount) + 1;
				if(sti(pchar.questTemp.genquestcount) >= 10) UnlockAchievement("gen_quests", 1);
				if(sti(pchar.questTemp.genquestcount) >= 20) UnlockAchievement("gen_quests", 2);
				if(sti(pchar.questTemp.genquestcount) >= 40) UnlockAchievement("gen_quests", 3);

                break;
            }
            // блок кидалова нас на бабки <--
			if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
			{
                iTmp = iQuantityGoods - GetSquadronGoods(pchar, iTradeGoods);
                dialog.text = "Вы привезли не весь товар!! Согласно условиям договора недостает еще "
                              + FindRussianQtyString(iTmp) + " груза.";
				link.l9 = RandPhraseSimple("Да, действительно. Придется восполнить недостачу. Зайду еще раз.",
                                           RandSwear() +"Дьявольские крысы попортили чертов груз. Я восполню недостачу и зайду еще раз.");
				link.l9.go = "exit";
                AddQuestRecord("DELIVERY_TRADE_QUEST", "8");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sHaveNotQty", iTmp);
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			}
			else
			{
				if (GetQuestPastDayParam("CargoQuest") == sti(pchar.CargoQuest.iDaysExpired))
				{
					dialog.text = "Вы опоздали на 1 день. Поэтому я заплачу вам только пол цены";
					link.l1 = "Эхх, с кем не бывает, давайте";
					link.l1.go = "exit";
					ChangeCharacterReputation(pchar, 3);
					AddCharacterExpToSkill(pchar, "Sailing", sti(pchar.rank) * GetCharacterSPECIALSimple(pchar, SPECIAL_I) );
					AddCharacterExpToSkill(pchar, "Leadership", sti(pchar.rank) * GetCharacterSPECIALSimple(pchar, SPECIAL_C));
					AddCharacterExpToSkill(pchar, "COMMERCE", sti(pchar.rank) * (GetCharacterSPECIALSimple(pchar, SPECIAL_C) + GetCharacterSPECIALSimple(pchar, SPECIAL_I)));

					AddMoneyToCharacter(pchar, makeint(sti(pchar.CargoQuest.iMoney)/2));
					pchar.quest.generate_trade_quest_progress = "";
					pchar.quest.generate_trade_quest.over = "yes";
					RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));
					ref cstore = GetColonyByIndex(FindColony(npchar.city));
					AddStoreGoods(&stores[sti(cstore.StoreNum)],makeint(pchar.CargoQuest.iTradeGoods),makeint(pchar.CargoQuest.iQuantityGoods));

					OfficersReaction("good");

					AddQuestRecord("DELIVERY_TRADE_QUEST", "Late1Day");
					CloseQuestHeader("DELIVERY_TRADE_QUEST");

					pchar.questTemp.genquestcount = sti(pchar.questTemp.genquestcount) + 1;
					if(sti(pchar.questTemp.genquestcount) >= 10) UnlockAchievement("gen_quests", 1);
					if(sti(pchar.questTemp.genquestcount) >= 20) UnlockAchievement("gen_quests", 2);
					if(sti(pchar.questTemp.genquestcount) >= 40) UnlockAchievement("gen_quests", 3);
				}
				else
				{
					dialog.text = "Замечательно! Вот ваша награда, капитан "+GetFullName(pchar)+".";
					link.l1 = "Приятно с вами работать.";
					link.l1.go = "exit";
					ChangeCharacterReputation(pchar, 3);

					AddCharacterExpToSkill(pchar, "Sailing", (GetQuestPastDayParam("CargoQuest") + 1) * sti(pchar.rank) * GetCharacterSPECIALSimple(pchar, SPECIAL_I) );
					AddCharacterExpToSkill(pchar, "Leadership", (GetQuestPastDayParam("CargoQuest") + 1) * sti(pchar.rank) * GetCharacterSPECIALSimple(pchar, SPECIAL_C));
					AddCharacterExpToSkill(pchar, "COMMERCE", (GetQuestPastDayParam("CargoQuest") + 1) * sti(pchar.rank) * (GetCharacterSPECIALSimple(pchar, SPECIAL_C) + GetCharacterSPECIALSimple(pchar, SPECIAL_I)));

					AddMoneyToCharacter(pchar, makeint(pchar.CargoQuest.iMoney));
					pchar.quest.generate_trade_quest_progress = "";
					pchar.quest.generate_trade_quest.over = "yes";
					RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));
					ref custore = GetColonyByIndex(FindColony(npchar.city));
					AddStoreGoods(&stores[sti(custore.StoreNum)],makeint(pchar.CargoQuest.iTradeGoods),makeint(pchar.CargoQuest.iQuantityGoods));

					OfficersReaction("good");
					AddQuestRecord("DELIVERY_TRADE_QUEST", "2");
					AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
					AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
					CloseQuestHeader("DELIVERY_TRADE_QUEST");

					pchar.questTemp.genquestcount = sti(pchar.questTemp.genquestcount) + 1;
					if(sti(pchar.questTemp.genquestcount) >= 10) UnlockAchievement("gen_quests", 1);
					if(sti(pchar.questTemp.genquestcount) >= 20) UnlockAchievement("gen_quests", 2);
					if(sti(pchar.questTemp.genquestcount) >= 40) UnlockAchievement("gen_quests", 3);
				}
			}
			SaveCurrentNpcQuestDateParam(Npchar, "Cooldown");
			Npchar.CargoQuest.Cooldown = MakeInt(sti(pchar.CargoQuest.iQuantityGoods)/sti(Goods[sti(pchar.CargoQuest.iTradeGoods)].units)*sti(Goods[sti(pchar.CargoQuest.iTradeGoods)].weight)/1000);
		break;

		case "generate_quest_failed":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            iMoney =  3*makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
			dialog.text = "Хорошо... Сумма в " + FindRussianMoneyString(iMoney) + " как раз покроет мои убытки от нарушения вами сроков доставки товара.";
			link.l1 = "Ого! Нет уж! Пожалуй, я не буду больше вообще возить эти чертовы грузы! В море их и так достаточно!";
			link.l1.go = "exit";
            if (sti(pchar.Money) >= iMoney)
            {
    			link.l2 = "Вот требуемая сумма";
    			link.l2.go = "generate_quest_failed_2";
			}
            else
            {
                AddQuestRecord("DELIVERY_TRADE_QUEST", "7");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
    		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            }
		break;

		case "generate_quest_failed_2":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            iMoney =  3*makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
			dialog.text = "Замечательно. Теперь я могу сообщить своим коллегам, что с вами все же можно иметь дело.";
			link.l1 = "Спасибо! В следующий раз я не подведу.";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 10);
			AddCharacterExpToSkill(pchar, "Sailing", -100);
			AddCharacterExpToSkill(pchar, "Leadership", -50);
			AddCharacterExpToSkill(pchar, "COMMERCE", -100);

			AddMoneyToCharacter(pchar, -iMoney);
			pchar.quest.generate_trade_quest_progress = "";
			pchar.quest.generate_trade_quest.over = "yes";

            AddQuestRecord("DELIVERY_TRADE_QUEST", "5");
            AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
            AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            CloseQuestHeader("DELIVERY_TRADE_QUEST");

			pchar.questTemp.genquestcount = sti(pchar.questTemp.genquestcount) + 1;
			if(sti(pchar.questTemp.genquestcount) >= 10) UnlockAchievement("gen_quests", 1);
			if(sti(pchar.questTemp.genquestcount) >= 20) UnlockAchievement("gen_quests", 2);
			if(sti(pchar.questTemp.genquestcount) >= 40) UnlockAchievement("gen_quests", 3);

		break;

		case "generate_quest_not_closed":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);

            dialog.text = "Хм. Я слышал, что вы еще не выполнили обязательства по предыдущему фрахту, а уже просите новый. Вы должны были доставить груз " +
            LanguageConvertString(iSeaGoods, "seg_" + Goods[iTradeGoods].Name)+ " в " + XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony) + ".";
			link.l1 = "Да, точно! Вы правы!";
			link.l1.go = "exit";
		break;

		case "generate_quest_cannot_done":
            dialog.text = RandSwear() + GetAddress_Form(NPChar) +", вы подводите меня!!! Может, попытаетесь как-то решить эту проблему?";
			link.l1 = "Хорошо. Я постараюсь доставить груз.";
			link.l1.go = "exit";
			link.l2 = "Нет. Не смогу. Сожалею";
			link.l2.go = "generate_quest_cannot_done_2";

		break;

		case "generate_quest_cannot_done_2":
		    iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
			{
				dialog.text = "Минуточку! Но на корабле нет такого количества товара!! Вам недостает еще "
                              + FindRussianQtyString(iQuantityGoods - GetSquadronGoods(pchar, iTradeGoods)) + " груза.";
				link.l9 = RandPhraseSimple("Да, действительно. Придется восполнить недостачу.",
                                           RandSwear() +"Корабельные крысы попортили груз. Я докуплю товар и зайду еще раз.");
				link.l9.go = "exit";
			}
			else
			{
                dialog.text = "Ладно, я понимаю... принимаю товар обратно.";
    			link.l1 = "Спасибо. В следующий раз я не подведу!";
    			link.l1.go = "exit";
    			ChangeCharacterReputation(pchar, -3);

				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
				RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));

                AddQuestRecord("DELIVERY_TRADE_QUEST", "6");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodQty", FindRussianQtyString(sti(pchar.CargoQuest.iQuantityGoods)));
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
    		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Dat"));
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
            }
		break;

		case "no_quests":
			dialog.text = "В данный момент я не нуждаюсь в ваших услугах.";
			link.l1 = "Очень жаль. Тогда давайте поговорим о другом.";
			link.l1.go = "node_1";
		break;

        case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

		case "Exit":
			if (pchar.questTemp.Ascold == "canTakeQuest" && pchar.questTemp.Ascold.TraderId == npchar.id)//eddy. Аскольд, начало
			{
				dialog.Text = "Ты много где бываешь. Слушай, если встретишь где-нибудь порошок египетской мумии, то будь добр"+ GetSexPhrase("","а") +", привези его мне. У меня есть серьезный клиент на это дело.";
				Link.l1 = "Хорошо.";
				Link.l1.go = "exit";
				SaveCurrentQuestDateParam("questTemp.Ascold");
				pchar.questTemp.Ascold = "Seek_powder";
				AddQuestRecord("Ascold", "1");
				AddQuestUserData("Ascold", "sName", GetFullName(npchar));
				AddQuestUserData("Ascold", "sCity", XI_ConvertString("Colony" + npchar.city + "Dat"));
			}
			else
			{
				Nextdiag.CurrentNode = Nextdiag.TempNode;
				DialogExit();
			}
		break;
		case "storage_rent":
			dialog.text = "Значит, желаете арендовать один из наших складов за умеренную плату?";
			link.l1 = "А он большой? и сколько попросите за аренду?";
			link.l1.go = "storage_rent1";
		break;

		case "storage_rent1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
			if (NPChar.city == "Tortuga" || NPChar.city == "Villemstad" || NPChar.city == "PortRoyal" || NPChar.city == "Havana")
			{
				dialog.text = "Он достаточно просторный даже для припортового пакгауза - вместимость 100000 ц. За " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + " в месяц я готов обеспечить сохранность ваших запасов. "+
				"Это включает услуги по охране, защиту от подтопления и борьбу с грызунами. Ну как, годится?.. Ну, и конфиденциальность, понятное дело, гарантирую.";
			}
			else
			{
				dialog.text = "Он достаточно просторный даже для припортового пакгауза - вместимость 50000 ц. За " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + " в месяц я готов обеспечить сохранность ваших запасов. "+
				"Это включает услуги по охране, защиту от подтопления и борьбу с грызунами. Ну как, годится?.. Ну, и конфиденциальность, понятное дело, гарантирую.";
			}

			link.l1 = "Годится. Могу я его осмотреть?";
			link.l1.go = "storage_rent2";
			link.l2 = "Слишком дорого просите. Там, небось, воды по колено и крысы вовсю шуруют.";
			link.l2.go = "storage_rent3";
		break;

		case "storage_rent2":
			dialog.text = "Конечно-конечно. Только эм-м... оплату за месяц попрошу вперёд.";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "Экий вы... меркантильный. Держите свои деньги - я арендую этот сарай.";
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = "Экий вы... меркантильный. Сейчас деньги принесу.";
				link.l1.go = "exit";
			}
		break;

		case "storage_rent3":
			dialog.text = "Ну, как знаете. Если надумаете - обращайтесь. Только учтите, что такое сокровище долго пустовать не будет. Как бы не опоздали.";
			link.l1 = "Не волнуйтесь. Если понадобится - спрошу.";
			link.l1.go = "exit";
		break;

	}
	LanguageCloseFile(iSeaGoods);
}

int findStoreMan(ref NPChar, int delta)
{
    ref ch;
	aref chNat;
	int n;
    int storeArray[30];
    int howStore = 0;
	bool ok;
		for (int i = 0; i < MAX_CHARACTERS; i++)
		{
			makeref(ch,Characters[i]);
			makearef(chNat,Characters[i].Nation);
			if (CheckAttribute(ch, "Dialog.Filename") && ch.Dialog.Filename == "Common_Store.c")
			{
				if (NPChar.id == ch.id) continue;
				if (NPChar.id == "Panama_trader" || ch.id == "Panama_trader") continue; //нельзя доплыть
				if (NPChar.id == "Caiman_trader" || ch.id == "Caiman_trader") continue;
				if (ch.location == "none") continue; // фикс для новых, невидимых до поры островов
				if (GetIslandByCityName(ch.city) == GetIslandByCityName(NPChar.city)) continue; // хрен вам, а не читы!
				ok = (GetNationRelation2MainCharacter(sti(chNat)) == RELATION_ENEMY) && (sti(chNat) != PIRATE);
				if (GetNationRelation(sti(chNat), sti(NPChar.Nation)) != RELATION_ENEMY && !ok)
				{
					storeArray[howStore] = i;
					howStore++;
				}
			}
		}
		if (howStore == 0)
		{
			return -1;
		}
		else
		{
			n = drand(howStore - 3) + delta;
			return storeArray[n];
		}
}

// ugeen -->
//--> расчет аренды склада
int GetStoragePriceExt(ref NPChar, ref chref)
{
	/* float fLeadership = 1.5 - GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/120.0; // учитываем авторитет
	float fCommerce = 1.5 - GetSummonSkillFromName(pchar, SKILL_COMMERCE)/120.0; // учитываем торговлю

	int price = makeint(2000 * MOD_SKILL_ENEMY_RATE * fLeadership * fCommerce); */

	int price = makeint(2000 * MOD_SKILL_ENEMY_RATE);

	return price;
}
//<-- расчет аренды склада
// --> перемещаем остатки груза со склада на корабль ГГ с перегрузом, пусть сам разбирается что делать со всем этим барахлом
void SetStorageGoodsToShip(ref pStorage)
{
	int iStoreQ;
	for (int i = 0; i< GOODS_QUANTITY; i++)
	{
		iStoreQ = GetStorageGoodsQuantity(pStorage, i);
		if (iStoreQ == 0) continue;
		SetCharacterGoods(pchar, i, GetCargoGoods(pchar, i) + iStoreQ);// перегруз
	}
}
