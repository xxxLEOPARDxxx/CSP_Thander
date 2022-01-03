

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//Скипаем с отравления три дня. ГГ приходит в себя в комнате таверны. Запись в СЖ: «Неожиданно. Но предсказуемо. Флинт поимел нас всех. Кто бы мог подумать. Хорошо, что жив(ва) остался(лась)! Нужно разобраться в происходящем. Дьявол, как же мутит то!

		//Далее, если договорились поймать Флинта для разведки – Вейна нет на Бермудах. Если не договаривались – он в таверне за столом пьянствует.

		//Спускаемся в таверну. Вариант без Вейна. Подходит Макс

		case "BS_F1_1":	//Максин
			dialog.text = "Очнул"+ GetSexPhrase("ся","ась") +" наконец, ты дольше всех в отключке был"+ GetSexPhrase("","а") +"";
			link.l1 = "Все живы? Что нового?";
			link.l1.go = "BS_F1_2";
		break;

		case "BS_F1_2": //Максин
			dialog.text = "Все живы, он подмешал белладонну в вино. Мастер Алексус отпаивал нас всех, какой то дрянью из древесного угля и Бог знает чего ещё. Заблевали всю резиденцию, но выжили.";
			link.l1 = "Обязательно куплю ему что-нибудь техническое. Так какие новости? Флинт? Золото?";
			link.l1.go = "BS_F1_3";
		break;

		case "BS_F1_3":	//Максин
			dialog.text = "Ни Флинта, ни золота. На складе только один сундук с дублонами, там примерно по пятьдесят тысяч на всех. И записка. «Простите, поделите это и забудьте про 'Урку' и Флинта. Так нужно. Всё равно вам не понять. Ф.»";
			link.l1 = "Чертов ханжа! А я почти поверил"+ GetSexPhrase("","а") +" в его 'дружбу'. Где остальные?";
			link.l1.go = "BS_F1_4";
		break;

		case "BS_F1_4":	//Максин
			dialog.text = "Элеонора в резиденции, с ней Рекхэм и Бонни, все трое злые как черти. Постоянно что–то бьют и орут друг на друга. Вейн как только встал на ноги, поднял паруса и умчался куда-то";
			link.l1 = "Думаю, в резиденцию пока лучше не соваться. Пойду, подышу воздухом.";
			link.l1.go = "exit";
		break;

		//Запись в СЖ: «Трудно думать, когда тебя постоянно тошнит. Но нужно что-то делать. Попробую подключить разведку. Какой там пароль? На Антигуа! В путь».

		//Вариант с Вейном

		//Подходит Макс

		case "BS_F1_5":	//Максин
			LAi_SetActorType(npchar);
			dialog.text = "Очнул"+ GetSexPhrase("ся","ась") +" наконец, ты дольше всех в отключке был"+ GetSexPhrase("","а") +".";
			link.l1 = "Все живы? Что нового?";
			link.l1.go = "BS_F1_6";
		break;

		case "BS_F1_6": //Максин
			dialog.text = "Все живы, он подмешал белладонну в вино. Мастер Алексус отпаивал нас всех, какой то дрянью из древесного угля и Бог знает чего ещё. Заблевали всю резиденцию, но выжили.";
			link.l1 = "Обязательно куплю ему что-нибудь техническое. Так какие новости? Флинт? Золото?";
			link.l1.go = "BS_F1_7";
		break;

		case "BS_F1_7":	//Максин
			dialog.text = "Ни Флинта, ни золота. На складе только один сундук с дублонами, там примерно по пятьдесят тысяч на всех. И записка: \n'Простите, поделите это и забудьте про 'Урку' и Флинта. Так нужно. Всё равно вам не понять. Ф.'";
			link.l1 = "Чертов ханжа! А я почти поверил"+ GetSexPhrase("ся","ась") +" в его 'дружбу'. Где остальные?";
			link.l1.go = "BS_F1_8";
			AddMoneyToCharacter(PChar, 50000);
		break;

		case "BS_F1_8":	//Максин
			dialog.text = "В резиденции Чарльз и Элеонора выясняют, у кого из них яйца больше. Постоянно орут и бьют что-то, потом затихают. Они или прирежут друг друга или трахнутся. Или и то, и другое.";
			link.l1 = "Они не были женаты раньше? Хм. Можешь не отвечать. Есть какие то зацепки?";
			link.l1.go = "BS_F1_9";
		break;

		case "BS_F1_9":	//Максин
			dialog.text = "Мне нужно вернуться в Порт Рояль, возможно девочки что-то слышали.";
			link.l1 = "Ну, в таком случае – добро пожаловать на борт! Оставим голубков выяснять отношения. Надеюсь, они всё-таки трахнутся, а не прикончат друг друга.";
			link.l1.go = "BS_F1_9exit";
		break;

		case "BS_F1_9exit":	//Максин
			DialogExit();
			PChar.quest.BSHangover_PortRoyal.win_condition.l1 = "location";
			PChar.quest.BSHangover_PortRoyal.win_condition.l1.location = "PortRoyal_town";
			PChar.quest.BSHangover_PortRoyal.function = "BSHangover_PortRoyal";
			AddQuestRecord("BSHangover", "2");
			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				StartInstantDialogNoType(pchar.WhisperPGG, "BS_7_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
			}
		break;
		case "BS_F1_8_MaksRoyal":	//Максин
			chrDisableReloadToLocation = false;
			dialog.text = "Благодарю. Мне понадобится какое-то время, чтобы собрать информацию. Можешь отдохнуть в таверне несколько дней.";
			link.l1 = "Ладно, тогда я пойду навещу Вейна и Гатри. Думаю, они уже успокоились.";
			link.l1.go = "BS_F1_8_MaksRoyal_exit";
		break;

		case "BS_F1_8_MaksRoyal_exit":
			DialogExit();
			BS_ReplaceHostessWithMaks();
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload9_back", "none", "", "", "", -1);
			DeleteAttribute(npchar, "LifeDay");
			AddQuestRecord("BSHangover", "3");
			//npchar.location = "none";
			sld = CharacterFromID("BS_Silver");
			sld.location = "none";
			sld = CharacterFromID("BS_Rakham");
			sld.location = "none";
			sld = CharacterFromID("BS_Vein");
			sld.location = "none";
			sld = CharacterFromID("BS_Bony");
			sld.location = "none";
			sld = CharacterFromID("Flint");
			sld.location = "none";

			ref jackman = CharacterFromID("Jackman");
			ChangeCharacterAddressGroup(jackman,"Pirates_townhall", "sit", "sit1");

			sld = CharacterFromID("gatri_temp");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_10";
			if(jackman.dialog.currentnode == "Jackman_Defeated")
			{
				sld.location.locator = "goto4";
			}

			LocatorReloadEnterDisable("Pirates_town", "reload3_back", false);
			LocatorReloadEnterDisable("Pirates_townhall", "reload2", false);
			LocatorReloadEnterDisable("Pirates_portoffice", "reload1", false);
		break;

		//Запись в СЖ: «Флинт не мог испариться бесследно и в Европу, ему путь заказан. Попробуем узнать что-то с помощью пташек Макс. В Порт Рояль!»

		//Далее вариант поисков Флинта, без договора с Бонсом

		//Отвозим Макс в Порт Рояль. Она покидает корабль. Заменяем мадам на Макс.

		//Запись в СЖ: «Максин пока займётся сбором слухов, а я проведаю Вейна и мисс Гатри»

		//Пиздуем на Бермуды. В резиденции Гатри. Вейна пока нигде нет, после диалога, ставим его в комнату таверны.

		case "BS_F1_10": //Гатри
			dialog.text = "";
			link.l1 = "Утихла буря? Когда покидал"+ GetSexPhrase("","а") +" эту гавань, тут аж стены тряслись и крысы толпой топиться бежали!";
			link.l1.go = "BS_F1_11";
		break;

		case "BS_F1_11": //Гатри
			dialog.text = "Этот мерзкий, самовлюблённый, неотёсанный кретин! Да как он смел! Видеть его больше не желаю! Не напоминай мне о нём! А лучше проваливай вслед за ним! К чертям собачьим!";
			link.l1 = "";
			LAi_SetActorTypeNoGroup(npchar);
			link.l1.go = "exit";

			sld = CharacterFromID("Pirates_tavernkeeper");
			SaveOldDialog(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_12";

		break;

		//Выкидывает нас на порог. Дверь закрыта.

		//Идём в таверну. Ставим Вейна в комнату.

		//Подходим к бармену.

		case "BS_F1_12": //Б
			dialog.text = "";
			link.l1 = "Вейн наверху?";
			link.l1.go = "BS_F1_13";
		break;

		case "BS_F1_13": //Б
			dialog.text = "Третий день как. Выжрал уже с бочонок рому и ещё требует.";
			link.l1 = "Подожди пока с ромом, потолковать нужно.";
			link.l1.go = "BS_F1_13exit";
		break;

		case "BS_F1_13exit": //Б
			DialogExit();
			RestoreOldDialog(npchar);

			DoReloadCharacterToLocation("Pirates_tavern_upstairs","goto","goto1");
			pchar.quest.BSHangover_Vein.win_condition.l1          = "location";
			pchar.quest.BSHangover_Vein.win_condition.l1.location = "Pirates_tavern_upstairs";
			pchar.quest.BSHangover_Vein.function             = "BSHangover_Vein";
		break;

		//Идём наверх

		case "BS_F1_14": //Вейн
			dialog.text = "Проваливай!";
			link.l1 = "Ну и вонь! Ты тут упиться решил? Собирай мозги в кучу. Возможно есть зацепки по Флинту! Ты со мной?";
			link.l1.go = "BS_F1_15";
		break;

		case "BS_F1_15": //Вейн
			dialog.text = "Зацепки? Да, чёрт возьми, я с тобой! И гори эта мисс Надменная Задница синим пламенем!";
			link.l1 = "Вот и чудно. В суть конфликта вникать не буду. Становись в эскадру, путь в Порт Рояль!";
			link.l1.go = "BS_F1_15exit";
			SetCompanionIndex(PChar, -1, GetCharacterIndex(npchar.id));
			BSRepairShip(npchar);
			AddQuestRecord("BSHangover", "4");
			npchar.location = "none";
			pchar.quest.BSHangover_RoyalVein.win_condition.l1          = "location";
			pchar.quest.BSHangover_RoyalVein.win_condition.l1.location = "PortRoyal_SecBrRoom";
			pchar.quest.BSHangover_RoyalVein.function             = "BSHangover_RoyalVein";
		break;

		case "BS_F1_15exit": //Вейн
			DialogExit();
			npchar.dialog.currentnode = "BS_F1_15Vein";
		break;

		case "BS_F1_15Vein": //Вейн
			npchar.dialog.currentnode = "BS_F1_15Vein"
			dialog.text = "Флинт заплатит!";
			link.l1 = "От нас ему не уйти.";
			link.l1.go = "BS_F1_15exit";
		break;
		//Запись в СЖ: «Гатри и Вейн поссорились. Ничего нового. Главное мы снова в деле. Пора проведать Макс»

		//Без приключений плывём в Порт Рояль. Идём в кабинет Макс. Вейн прицепом.

		case "BS_F1_16": //Максин
			dialog.text = "";
			link.l1 = "Какие новости, мадам?";
			link.l1.go = "BS_F1_17";
		break;

		case "BS_F1_17": //Максин
			dialog.text = "И вам не хворать. Новости неожиданные. У нас новая девочка из Бриджтауна, так вот она рассказала, что в их заведении почти прописался некий пират. Золото горстями раскидывает, по пьяни каждой девочке рассказывает, как его лучший друг и капитан бросил. А он его, как отца родного любил. И далее в том же духе. А зовут этого моряка – Джон Стингер.";
			link.l1 = "";
			link.l1.go = "BS_F1_17exit";
		break;

		case "BS_F1_17exit": //Максин
			RestoreOldDialog(npchar);
			StartInstantDialogNoType("BS_Vein", "BS_F1_18", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_18": //Вейн
			chrDisableReloadToLocation = false;
			npchar.location = "none";
			AddQuestRecord("BSHangover", "5");
			dialog.text = "Сильвер?! Он как то хвалился, что его Жалом шлюхи прозвали!";
			link.l1 = "Нужно поспешить. Не верю я, что Флинт просто так его с корабля списал!";
			link.l1.go = "BS_F1_15exit";

			pchar.quest.BSHangover_VeinFollows.win_condition.l1          = "location";
			pchar.quest.BSHangover_VeinFollows.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.BSHangover_VeinFollows.function             = "BSHangover_VeinFollows"

			pchar.BSSearchStinger = 0;

			sld = CharacterFromID("Bridgetown_tavernkeeper");
			SaveOldDialog(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_SearchStinger";

			sld = CharacterFromID("Bridgetown_shipyarder");
			SaveOldDialog(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_SearchStinger";

			sld = CharacterFromID("Bridgetown_trader");
			SaveOldDialog(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_SearchStinger";

			sld = CharacterFromID("Bridgetown_hostess");
			SaveOldDialog(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_SearchStinger";

			sld = CharacterFromID("Bridgetown_usurer");
			SaveOldDialog(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_SearchStinger";

			sld = CharacterFromID("Bridgetown_priest");
			SaveOldDialog(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_SearchStinger";

			sld = CharacterFromID("Bridgetown_portman");
			SaveOldDialog(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_SearchStinger";
		break;

		case "BS_F1_SearchStinger":
			dialog.text = "";
			link.l1 = "Привет. Я кое-кого ищу. К тебе не заходил некий Джон Стингер? Или, быть может, Джон Сильвер? Он ещё носит деревяшку вместо ноги. Могу неплого заплатить за информацию.";
			if(npchar.id == "BridgetownJailOff")
			{
				link.l1 = "Здравствуйте. Извиняюсь за нескромный вопрос, но среди ваших 'подопечных' случайно нет человека по имени Джон Стингер? Или, быть может, Джон Сильвер?  Он ещё носит деревяшку вместо ноги. ";
			}
			link.l1.go = "BS_F1_SearchStinger_1";
		break;

		case "BS_F1_SearchStinger_1":
			dialog.text = "Простите, но я впервые слышу это имя. Ничем не могу помочь.";
			link.l1 = "Жаль.";
			link.l1.go = "BS_F1_SearchStinger_2";
		break;

		case "BS_F1_SearchStinger_2":
			pchar.BSSearchStinger = sti(pchar.BSSearchStinger)+1;
			Log_TestInfo(pchar.BSSearchStinger);
			RestoreOldDialog(npchar);
			DialogExit();
			if(npchar.id == "BridgetownJailOff")
			{
				chrDisableReloadToLocation = false;
				InterfaceStates.DisFastTravel = true;

				pchar.quest.BSHangover_StingerFound.win_condition.l1          = "location";
				pchar.quest.BSHangover_StingerFound.win_condition.l1.location = "Bridgetown_fort";
				pchar.quest.BSHangover_StingerFound.function             = "BSHangover_StingerFound";
			}
			else
			{
				BSHangover_SearchStingerCheck();
			}

		break;

		//Запись в СЖ: «Есть зацепка, в борделе на Барбадосе, сорит деньгами и жалуется на жизнь Джон Сильвер. Нужно успеть туда раньше Флинта и подготовить засаду!»

		//Плывём на Барбадос. В борделе никто ничего про Сильвера-Стингера не знает. Тыкаемся во все двери. После того, как оббежали всех (бармен, ПУ, верфь, церковь, магазин, банк) дзынь! Запись в СЖ: «Никто не видел или не хочет говорить о Сильвере или Стингере, или ком-то похожем на него. Остаётся проверить тюрьму!»

		//Идём в тюрячку. Комендант, тоже шлёт нахой. В расстроенных чувствах уходим. На переходе Форт-Гор Ворота, в локации ворот, подходит сам Сильвер.

		case "BS_F1_19": //Сильвер
			dialog.text = "Рад видеть вас компаньоны! Соображалка у вас работает побыстрее Флинтовской!";
			link.l1 = "Ты специально использовал шлюх, что бы слух о несчастном пропойце Стингере дошел до Максин? Рискованный ход. Флинт мог бы добраться до неё первым!";
			link.l1.go = "BS_F1_19exit";
		break;

		case "BS_F1_19exit":
			StartInstantDialog("BS_Vein", "BS_F1_20", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_20": //Вейн
			dialog.text = "Твою ж мать! Максин! Если Флинт думал так же, как ты – она в опасности!";
			link.l1 = "";
			link.l1.go = "BS_F1_20exit";
		break;

		case "BS_F1_20exit":
			StartInstantDialogNoType("BS_Silver", "BS_F1_21", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_21": //Сильвер
			dialog.text = "О, наша Макс за себя постоять может. Это уже не та, бедная рабыня из Луизианы, которую продали в бордель ещё в детстве.";
			link.l1 = "И тем не менее, я чувствую, что она в беде. Нужно поспешить в Порт Рояль.";
			link.l1.go = "BS_F1_22";
		break;

		case "BS_F1_22": //Сильвер
			dialog.text = "Или подождать ещё немного. Что такого ей сделает Флинт? Устроим засаду, а я приманка. Несчастный, спившийся Сильвер.";
			link.l1 = "";
			link.l1.go = "BS_F1_22exit";
		break;

		case "BS_F1_22exit":
			StartInstantDialogNoType("BS_Vein", "BS_F1_23", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_23": //Вейн
			dialog.text = "Хватит зубы скалить. Ты как тут вообще оказался? Не сошлись характерами?";
			link.l1 = "";
			link.l1.go = "BS_F1_23exit";
		break;

		case "BS_F1_23exit":
			StartInstantDialogNoType("BS_Silver", "BS_F1_24", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_24": //Сильвер
			dialog.text = "Почти. Флинт примчался на 'Моржа' и сразу скомандовал отплывать. 'Поговорим позже Джон, думаю, ты всё поймёшь', сказал и зыркнул так по флинтовски, из подлобья. Ну, вы знаете. И тут меня проняло аж. Смотрю, а на палубе всё лица незнакомые, когда он успел команду набрать? Нечисто тут что-то, думаю.";
			link.l1 = "Что дальше было? Не томи и без украшательств, пожалуйста!";
			link.l1.go = "BS_F1_25";
		break;

		case "BS_F1_25": //Сильвер
			dialog.text = "Отвалили мы от Бермуд миль на десять, и тут матросы эти новые пистоли достали и всех ветеранов, с которыми золото Урки брали – перестреляли! Палуба вся кровью залита, а они с тесаками выживших добивают. Ну, я и со всех ног в кубрик побежал, схватил пояс с золотишком припрятанным, пустой бочонок из под рома и за борт. Течение меня к Син Мартену вынесло, там нанял рыбаков, что меня переправили подальше. В конце концов, осел тут.";
			link.l1 = "Занятно, Флинт значит всё это заранее спланировал и делиться ни с кем не собирался.";
			link.l1.go = "BS_F1_25exit";
		break;

		case "BS_F1_25exit":
			StartInstantDialogNoType("BS_Vein", "BS_F1_27", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_26": //Вейн
			dialog.text = "Да я ему это золото в глотку запихивать стану, пока снизу не посыпится!";
			link.l1 = "";
			link.l1.go = "BS_F1_27";
		break;

		case "BS_F1_27": //Вейн
			dialog.text = "Да я ему это золото в глотку запихивать стану, пока снизу не посыпится!";
			link.l1 = "";
			link.l1.go = "BS_F1_27exit";
		break;

		case "BS_F1_27exit":
			StartInstantDialogNoType("BS_Silver", "BS_F1_28", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_28": //Сильвер
			dialog.text = "Ну что? Я в бордель, буду дальше изображать отчаявшегося пропойцу, а вы затаитесь тут и корабли в бухту Риггед Поинт перегоните. И, это... Эм... Деньжат на бордель не подкинете? Поиздержался я тут.";
			link.l1 = "Держи. Тут остатки тех пятидесяти тысяч, что нам Флинт на всех оставил.";	//- 32000
			link.l1.go = "BS_F1_28exit";
		break;

		case "BS_F1_28exit":
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.location = "none";
			AddMoneyToCharacter(PChar, -32000 - rand(500));
			StartInstantDialogNoType("BS_Vein", "BS_F1_27_1", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_27_1": //Вейн
			dialog.text = "Значит решено. Я займусь кораблями, а ты пока сними комнату в таверне, скорее всего мы тут задержимся.";
			link.l1 = "Ладно.";
			link.l1.go = "BS_F1_27_2";
		break;

		case "BS_F1_27_2": //Вейн
			DialogExit();
			UnLockWeapons("");
			InterfaceStates.DisFastTravel = false;
			chrDisableReloadToLocation = false;
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.location = "none";
			pchar.location.from_sea = "Shore5";

			sld = CharacterFromID("Bridgetown_tavernkeeper");
			SaveOldDialog(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_RentRoom";
		break;

		case "BS_F1_RentRoom":
			dialog.text = "";
			link.l1 = "Приветствую. Хочу снять комнату на неделю.";
			link.l1.go = "BS_F1_RentRoom_1";
		break;

		case "BS_F1_RentRoom_1":
			dialog.text = "С вас сотня монет.";
			if (sti(pchar.money) >= 100)
			{
				link.l1 = "Вот, держи.";
				link.l1.go = "BS_F1_RentRoom_2";
			}
			link.l2 = "Хм... Я ещё вернусь.";
			link.l2.go = "BS_F1_RentRoom_exit";
		break;

		case "BS_F1_RentRoom_2":
			dialog.text = "Комната ваша. Вот ключ.";
			AddMoneyToCharacter(PChar, -100);
			link.l1 = "Благодарю";
			link.l1.go = "BS_F1_RentRoom_3";
		break;

		case "BS_F1_RentRoom_3":
			DialogExit();
			RestoreOldDialog(npchar);
			BSHangover_FewDaysLater();
		break;

		case "BS_F1_RentRoom_exit":
			DialogExit();
			npchar.dialog.currentnode = "BS_F1_RentRoom";
		break;

		//Ставим корабли в бухту. Ножками топаем в город и просто чилим три дня или скипаем. Через три дня, на улице, подходит шлюха

		case "BS_F1_29": //Шлюха
			dialog.text = "Красавчик Джонни сказал, чтобы вы были готовы. «Морж» встал на рейде. Он выманит охотника в пещеру, тут на острове.";
			link.l1 = "Спасибо, детка.";
			link.l1.go = "BS_F1_30";
		break;

		case "BS_F1_30": //Шлюха
			dialog.text = "А монетку?";
			link.l1 = "Ах, да. Вот тебе несколько монеток."; //- 32000
			link.l1.go = "BS_F1_30exit";
		break;

		case "BS_F1_30exit":
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10);
			StartInstantDialog("BS_Vein", "BS_F1_31", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_31": //Вейн
			AddMoneyToCharacter(PChar, -500);
			dialog.text = "Как то просто всё вышло. Не нравится мне это!";
			AddQuestRecord("BSHangover", "7");
			link.l1 = "Мне тоже. Давай разделимся. Бери своих и занимайте позиции вокруг входа в пещеру. Я пойду внутрь. Услышите неладное – будьте настороже, внутрь не суйтесь, сидите в засаде. Посмотрим, чем всё обернётся.";
			link.l1.go = "BS_F1_31_1";

		break;
		case "BS_F1_31_1": //Вейн
			npchar.dialog.currentnode = "BS_F1_15Vein";
			DialogExit();
			npchar.location = "none";
			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				StartInstantDialogNoType(pchar.WhisperPGG, "BS_8_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
			}
		break;

		//Вейн уходит. Запись в СЖ: «Ну что же, посмотрим, какая рыба заглотила наживку!»

		//Идём в пещеру. Войдя – запускается аларм и в логе таймер 60 сек. «Джон в беде, нужно поспешить на выручку!» – это тоже в логе. Бежим в место шахтных выработок. Там, сразу гасим таймер, Сильвер – становится смертным. В пещёре 10-12 ОЗГов, начинается замес. Сильвер погиб – провал квеста, принудительный – экран смерти. Сильвер выжил – продолжаем.

		case "BS_F1_32": //Сильвер
			dialog.text = "";
			link.l1 = "Тут нет Флинта! Проклятье!";
			link.l1.go = "BS_F1_33";
		break;

		case "BS_F1_32_beaten": //Сильвер
			dialog.text = "Ох, кажется, меня проткнули насквозь...";
			link.l1 = "Ничего серьёзного я не вижу, жить будешь.";
			link.l1.go = "BS_F1_32_beaten_1";
		break;

		case "BS_F1_32_beaten_1": //Сильвер
			dialog.text = "Ты уверен"+ GetSexPhrase("","а") +"? Чувствую я себя гораздо хуже.";
			link.l1 = "Тут нет Флинта! Проклятье!";
			link.l1.go = "BS_F1_33";
		break;

		case "BS_F1_33": //Сильвер
			dialog.text = "Точно, ты заметил"+ GetSexPhrase("","а") +"? Это те рожи, о которых я говорил. Эти точно не местные, я почти всех наёмных рубак тут знаю. А где Вейн?";
			link.l1 = "Снаружи, в засаде. Не будем терять время, в бухту и попробуем взять на абордаж ‘Моржа’!";
			link.l1.go = "BS_F1_33_2";
		break;

		case "BS_F1_33_2":
			chrDisableReloadToLocation = false;
			npchar.dialog.currentnode = "BS_F1_33_1";
			DialogExit();
		break;
		case "BS_F1_33_1":
			dialog.text = "Я ещё немного посижу здесь, а потом сразу за вами.";
			link.l1 = "Давай, не прикидывайся, симулянт.";
			link.l1.go = "BS_F1_33_2";
		break;

		//Бяжим к выходу. Снаружи идёт замес. Опять озги (модельки), Вейн, Бонни, Рекхэм и пара – тройка их матросов против десятка наёмников. Опять та же история, если кто то из ключевых героев гибнет – сразу экран смерти. Завалили геев. Говорим с Вейном.

		case "BS_F1_34": //Вейн
			dialog.text = "Эти, (пинает ногой труп), полезли из подлеска, как только ты в пещеру вош"+ GetSexPhrase("ёл","ла") +", пришлось вмешаться.";
			link.l1 = "Внутри тоже жарко было! Флинта среди трупов нет! Нужно бежать на корабли и попытаться взять ‘Моржа’. За мной!";
			link.l1.go = "BS_F1_34exit";
			BSHangover_IsEveryoneOkay();
		break;
		case "BS_F1_34exit": //Вейн
			DialogExit();
			SetCompanionIndex(PChar, -1, GetCharacterIndex(npchar.id));
			LocatorReloadEnterDisable("Shore5", "boat", false);
			chrDisableReloadToLocation = false;

			for (int i = 1; i <= 4; i++)
			{
				if(i == 1)	sld = CharacterFromID("BS_Vein");
				if(i == 2)	sld = CharacterFromID("BS_Silver");
				if(i == 3)	sld = CharacterFromID("BS_Rakham");
				if(i == 4)	sld = CharacterFromID("BS_Bony");
				Lai_SetActorTypeNoGroup(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				sld.location = "none";
			}
		break;

		//Запись в СЖ: «На наживку клюнула целая стая рыбин! Но главного лосося, среди них не было. «Морж» всё ещё на рейде, нужно взять его на абордаж и быстро, пока сторожевики не решили посмотреть, кто там палит из пушек».

		//Скачем в Риггед Поинт, садимся на корабли берём Моржа на абордаж. В каюте рубимся с Флинтом. Суровый по статам мужик с какой нибудь уникальной саблей. Банки, жратва – всё по полной. Порубили. Заводит диалог

		case "BS_F1_35": //Флинт
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			for (int z = 1; z <= 6; z++)
			{
				sld = CharacterFromID("FlintOff"+z);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			PChar.quest.BSHangover_Fail1.over = "yes";
			PChar.quest.BSHangover_Fail2.over = "yes";

			dialog.text = "Всё должно было пойти совсем не так! Мне жаль. Но выслушай меня!";
			link.l1 = "Не так?! Мы не должны были выжить? Да я дура"+ GetSexPhrase("к","") +", решил"+ GetSexPhrase("","а") +", что ты мне друг! Чёрт возьми, мы такие дела могли бы вместе проворачивать! Зачем ты так?";
			link.l1.go = "BS_F1_36";
		break;

		case "BS_F1_36": //Флинт
			dialog.text = "Всё очень непросто, дружище. Не начни вы погоню, не попадись я на уловку Джона... Всё было бы по-другому. Никто не ушёл бы обиженным. Я всё продумал! Думал, что всё. Эти деньги нужны не мне лично, они станут основой нового, свободного государства. Республики! Без королей и их войн, местом, где свободные люди, смогут жить по совести, не завися от прихотей банкиров или аристократов! Это Новый Свет, так пусть он станет началом Нового, лучшего Мира! Ты понимаешь?!";
			link.l1 = "О чём ты? Какая республика? Шарп уже пытался, Эвери тоже. Чем всё закончилось? Кровью. Кровью тех самых свободных людей, для которых ты новый мир собрался строить! Или твой «мир» особенный? Чем же?";
			link.l1.go = "BS_F1_37";
		break;

		case "BS_F1_37": //Флинт
			dialog.text = "Тут не место для философских диспутов. Давай закончим всё это и поговорим как цивилизованные люди.";
			link.l1 = "Чёрта с два. Сейчас ты отправишься в трюм. В кандалах. А поговорим мы все вместе. Вместе с теми, кого ты отравить пытался! И моли всех богов, которых знаешь, что бы мне удалось убедить Вейна не протащить тебя под килем.";
			link.l1.go = "BS_F1_38";
		break;

		case "BS_F1_38": //Флинт
			dialog.text = "Я и забыл, что имею дело с пиратом. Хорошо, вот моё оружие. Ведите.";
			TakeNItems(PChar, "blade43", 1);
			PlaySound("interface\important_item.wav");
			Log_Info("Вы получили Нарвал!");
			link.l1 = "";
			link.l1.go = "BS_F1_38exit";
		break;

		case "BS_F1_38exit": //Флинт
			for (int k = 1; k <= 6; k++)
			{
				sld = CharacterFromID("FlintOff"+k);
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}


			DialogExit();

			QuestAboardCabinDialogFree(); // важный метод
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "");

			LAi_KillCharacter(npchar);
			DeleteCharacter(npchar);
			SetLaunchFrameFormParam("Ваши люди уводят Флинта. Вы, тем временем, обыскиваете его каюту. В одном из сундуков вы находите два с половиной миллиона песо. Также ваше внимание привлекает книга - Марк Аврелий 'Размышления'. Вы забираете её, вместе с судовым журналом Флинта.", "", 0.1, 15.0);
			LaunchFrameForm();
			AddMoneyToCharacter(PChar, 2500000);
			AddQuestRecord("BSHangover", "9");
			sld = CharacterFromID("PortRoyal_hostess");
			SaveOldDialog(sld);
			sld.dialog.filename = "Quest\BlackSails\BS_Final_1.c";
			sld.dialog.currentnode = "BS_F1_39";

			DeleteAttribute(pchar, "LockMapReload");

			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				sld = CharacterFromID(pchar.WhisperPGG);
				sld.dialog.filename = "Quest\WhisperLine\Whisper_cabin_dialog.c";
				sld.dialog.currentnode = "BS_21_WhisperIsHere";
				LAi_SetActorType(pchar);
				LAi_SetActorTypeNoGroup(sld);
				SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
				LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.5);
			}
		break;

		//Отдаёт свою саблю. ВАЖНО! Не делать релоад после драки, нужно дать обыскать каюту. В сундуке – 2.5кк денег, побрякушки. Судовой Журнал Флинта и книга - Марк Аврелий «Размышления». Моржа можно топить или себе забрать – похер. (!) Залочить возможность диалога с Флинтом в трюме, во избежание найма. Оставить фразу «Позже поговорим».

		//Запись в СЖ: «Флинт пойман! Пытался нести какую -  то ахинею про Республику и свободных людей. Путь на Бермуды, там по расспросим подробнее, про Республику, а главное – про сто пятьдесят миллионов причин ввязаться в эту авантюру! Ах, да! И нужно проведать Макс в Порт Рояле. Компаньон как – никак».

		//Плывём в ПР, забираем Макс из борделя. С ней всё заебись.

		//Диалог в кабинете мадам.

		case "BS_F1_39": //Максин
			dialog.text = "";
			link.l1 = "Я с новостями! Флинт в кандалах, в трюме. Ты с нами? Пора узнать, как там наши миллионы поживают!";
			link.l1.go = "BS_F1_40";
		break;

		case "BS_F1_40": //Максин
			dialog.text = "Конечно я с вами! Тут вчера крутились, какие то мрачные типы, явно не местные. Не хочу рисковать.";
			link.l1 = "Собирайся, провожу на борт.";
			link.l1.go = "BS_F1_40_1";
			pchar.quest.BSHangover_MaksOnShip.win_condition.l1          = "location";
			pchar.quest.BSHangover_MaksOnShip.win_condition.l1.location = pchar.location.from_sea;
			pchar.quest.BSHangover_MaksOnShip.function             = "BSHangover_MaksOnShip";
		break;

		case "BS_F1_40_1":
			npchar.dialog.currentnode = "BS_F1_40_2";
			DialogExit();
		break;

		case "BS_F1_40_2": //Максин
			dialog.text = "Минутку, я соберу вещи.";
			link.l1 = "Ладно, тогда догонишь.";
			link.l1.go = "BS_F1_40_1";
		break;

		//Плывём на Бермуды. Удаляем Флинта из пленников. Сходим на берег, подбегает матрос.

		case "BS_F1_41": //Матрос
			dialog.text = "Капитан! Пленник сбежал! Кандалы вскрыты!";
			link.l1 = "";
			link.l1.go = "BS_F1_41exit";
		break;

		case "BS_F1_41exit":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10);
			StartInstantDialog("BS_Vein", "BS_F1_42", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_42": //Вейн
			dialog.text = "Твою ж мать! Как?";
			link.l1 = "Осмотреть тут каждый камень, каждую пальму! Чего встали? БЕГОМ!";
			link.l1.go = "BS_F1_42exit";
		break;

		case "BS_F1_42exit":
			DialogExit();
			SetLaunchFrameFormParam("Прошло 12 часов поисков.", "", 0.1, 2.0);
			LaunchFrameForm();
			StartInstantDialogNoType("BS_Vein", "BS_F1_43", "Quest\BlackSails\BS_Final_1.c");
		break;

		//Табличка «Прошло 12 часов поисков»

		//Таверна. Подходит Вейн.

		case "BS_F1_43": //Вейн
			dialog.text = "";
			link.l1 = "Никаких следов?";
			link.l1.go = "BS_F1_44";
		break;

		case "BS_F1_44": //Вейн
			dialog.text = "Как сквозь землю провалился. Что на корабле? Поняли, как он смог удрать?";
			link.l1 = "Или его плохо обыскали или ему кто-то помог.";
			link.l1.go = "BS_F1_45";
		break;

		case "BS_F1_45": //Вейн
			dialog.text = "Сильвер? Это лис, а не человек. Я ему не доверяю!";
			link.l1 = "Возможно, но Сильвер никуда не делся и обвинять его рано. В каюте ‘Моржа’ я наш"+ GetSexPhrase("ёл","ла") +" судовой журнал Флинта и книгу Марка Аврелия.";
			link.l1.go = "BS_F1_46";
		break;

		case "BS_F1_46": //Вейн
			dialog.text = "Я видел его журнал. Всё зашифровано.";
			link.l1 = "Вот поэтому, мы не будем ни в чем подозревать мистера Сильвера, а будем с ним предельно деликатны и вежливы.";
			link.l1.go = "BS_F1_47";
		break;

		case "BS_F1_47": //Вейн
			dialog.text = "Какого черта ты несёшь? Аааа... Я понял. Шифры!";
			link.l1 = "Точно. Идём к остальным, в резиденцию.";
			link.l1.go = "BS_F1_47exit";
		break;
		case "BS_F1_47exit": //Вейн
			AddQuestRecord("BSHangover", "10");
			BSChaseBegun_unlock_townhall();
			chrDisableReloadToLocation = false;
			DialogExit();
			Lai_SetActorTypeNoGroup(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			RemoveCharacterCompanion(PChar, npchar);
			pchar.quest.BSHangover_TownHall.win_condition.l1          = "location";
			pchar.quest.BSHangover_TownHall.win_condition.l1.location = "pirates_townhall";
			pchar.quest.BSHangover_TownHall.function             = "BSHangover_TownHall";
		break;

		//Запись в СЖ: «Флинт, как угорь выскользнул из трюма и растворился неизвестно где. Остался только его судовой журнал и старая, зачитанная книга, за авторством римского императора. Стоит уговорить Сильвера, помочь с расшифровкой. И не давить на него. Нутром чую, без его участия, побег Флинта не обошелся».

		//Идём в резиденцию. Гатри, Макс, Вейн, ГГ, Бонни, Рекхэм, Сильвер.

		case "BS_F1_48": //ко всем
			dialog.text = "";
			link.l1 = "Итак, вот, что мы имеем. Флинт сбежал с корабля, каким то чудом открыв кандалы. Шлюпки на месте, а значит, он вплавь добрался сюда. Возможно, у кого-то из местных он позаимствовал лодку и теперь направляется к нашим с вами денежкам. И черт с ним! Рано или поздно, он попадётся. Хорошая новость, в том, что у нас есть его судовой журнал, зашифрованный. А ключом к шифру, скорее всего, является эта книга.";
			link.l1.go = "BS_F1_49";
		break;

		case "BS_F1_49": //Гатри
			dialog.text = "А мистер Сильвер прекрасно взламывает любые шифры, равно как и замки!";
			link.l1 = "";
			link.l1.go = "BS_F1_49_1";
		break;

		case "BS_F1_49_1": //Гатри
			Lai_SetActorTypeNoGroup(npchar);
			StartInstantDialog("BS_Silver", "BS_F1_50", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_50": //Сильвер
			dialog.text = "Если вы о кандалах Флинта, то, уверяю, я здесь ни причем! А в расшифровке журнала, я с удовольствием помогу. За долю в сокровище. Пусть и не равную. По рукам?";
			link.l1 = "";
			link.l1.go = "BS_F1_50_1";
		break;

		case "BS_F1_50_1":
			Lai_SetActorTypeNoGroup(npchar);
			StartInstantDialog("BS_Vein", "BS_F1_51", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_51": //Вейн
			dialog.text = "По рукам. Вот только расшифровкой ты займёшься под присмотром Энн и пары стрелков из наёмников мисс Гатри.";
			link.l1 = "";
			link.l1.go = "BS_F1_51_1";
		break;

		case "BS_F1_51_1":
			Lai_SetActorTypeNoGroup(npchar);
			StartInstantDialog("BS_Silver", "BS_F1_52", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_52": //Сильвер
			dialog.text = "Что же, я готов приступать. Позвольте взглянуть на журнал и книгу?";
			link.l1 = "Вот, развлекайтесь. Я вернусь через несколько часов.";
			PlaySound("interface\important_item.wav");
			Log_Info("Вы отдали книгу и журнал Флинта");
			link.l1.go = "BS_F1_52exit";
		break;

		case "BS_F1_52exit": //Сильвер
			DialogExit();
			Lai_SetActorTypeNoGroup(npchar);
			AddQuestRecord("BSHangover", "11");
			pchar.quest.BSHangover_Cutscene.win_condition.l1          = "location";
			pchar.quest.BSHangover_Cutscene.win_condition.l1.location = "pirates_tavern";
			pchar.quest.BSHangover_Cutscene.function             = "BSHangover_Cutscene";
		break;

		//Передаём то и другое.

		//Запись в СЖ: «Сильвер занят расшифровкой. Пойти, что ли выпить? Или искать Флинта? Местные течения, небольшой баркас или тартану, могут унести куда – угодно, хоть в открытый океан. Или черт с ним с Флинтом. Всё - таки такой человек, как он, заслуживает шанс. Да, буду считать это форой, из уважения. Пойду выпью!»

		//Идём в таверну, садим ГГ за столик, бухаем. Типо кат сцена (первая бля кат сцена!) Показываем табличку «Прошло три часа размышлений и возлияний».

		//Запись в СЖ: «Пора проведать нашего дешифратора!»

		//Идём в резиденцию. Сильвер за столом, Гатри, Бонни, Вейн.

		case "BS_F1_53": //Сильвер
			dialog.text = "";
			link.l1 = "Есть результаты?";
			link.l1.go = "BS_F1_54";
		break;

		case "BS_F1_54": //Сильвер
			dialog.text = "Да. Вот ознакомьтесь.";
			link.l1 = "21°3N, 80°00W. 15 25 N, 61 20 W. 12°07N61°40W. 72° 25'N 19° 00'W. 19°30N 80°30W.";
			link.l1.go = "BS_F1_55_1";
		break;

		case "BS_F1_55_1":
			Lai_SetActorTypeNoGroup(npchar);
			StartInstantDialog("BS_Vein", "BS_F1_55", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_55": //Вейн
			dialog.text = "Координаты? Чего мы ждём?";
			link.l1 = "Там ещё две страницы координат... И никаких зацепок? У Аврелия упоминается какой-нибудь остров? Должно быть что то?!";
			link.l1.go = "BS_F1_56_1";
		break;

		case "BS_F1_56_1":
			Lai_SetActorTypeNoGroup(npchar);
			StartInstantDialog("BS_Vein", "BS_F1_56", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_56": //Сильвер
			dialog.text = "Нужно больше времени. Нужно изучить книгу, искать зацепки, сверять с координатами!";
			link.l1 = "Признайтесь сами себе. Флинт нас поимел и сейчас направляется по одному ему известным координатам! Куда? Да куда угодно! Здесь сотни островов и рифов. Чёрт, чёрт, чёрт!!!";
			link.l1.go = "BS_F1_57_1";
		break;

		case "BS_F1_57_1":
			Lai_SetActorTypeNoGroup(npchar);
			StartInstantDialog("BS_Vein", "BS_F1_57", "Quest\BlackSails\BS_Final_1.c");
		break;

		case "BS_F1_57": //Вейн
			dialog.text = "Ты просто так сдаёшься? Я был о тебе лучшего мнения!";
			link.l1 = "Вот, деньги, что были в каюте Флинта. Уверен"+ GetSexPhrase("","а") +", что это часть золота Урки. По пятьсот тысяч на каждого. Если будут подвижки с координатами, дайте знать. Я умываю руки!";
			if(sti(pchar.money) < 2000000)	link.l1 = "Вот, деньги, что были в каюте Флинта. Уверен"+ GetSexPhrase("","а") +", что это часть золота Урки. По пятьсот тысяч на каждого. Ох, простите, я уже потратил"+ GetSexPhrase("","а") +" их. Возьмите сколько есть, остальное буду "+ GetSexPhrase("должен","должна") +". Если будут подвижки с координатами, дайте знать. Я умываю руки!";
			link.l1.go = "BS_F1_57exit";	//минус 2кк.
		break;

		case "BS_F1_57exit": //Вейн
			Lai_SetActorTypeNoGroup(npchar);
			AddMoneyToCharacter(pchar, -2000000);
			AddQuestRecord("BSHangover", "13");
			CloseQuestHeader("BSHangover");
			DialogExit();
			sld = CharacterFromID("BS_Silver");
			sld.location = "none";
			sld = CharacterFromID("BS_Rakham");
			sld.location = "none";
			sld = CharacterFromID("BS_Vein");
			sld.location = "none";
			sld = CharacterFromID("BS_Bony");
			sld.location = "none";
			sld = CharacterFromID("BS_Maks");
			sld.location = "none";
			BS_ReplaceHostessWithMaks();

			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				StartInstantDialogNoType(pchar.WhisperPGG, "BS_14_WhisperIsHere_1", "Quest\WhisperLine\Whisper.c");
			}
		break;

		//Запись в СЖ: «Несколько сотен возможных мест. Годы поисков, десятилетия уйдут на это. Тут всё ещё есть чем занять себя, клады, жирные торгаши, дуэли и осады фортов! Займусь развитием своей колонии или стану грозой Мейна. Но навсегда запомню капитана Джеймса, мать его Флинта и сто пятьдесят миллионов причин его ненавидеть или любить. Авантюра вышла запоминающаяся! Нужно отдать ему должное».

		//ФиналОчка. Макс теперь мадам в ПР со стандартными диалогами. Гатри – губернатор Бермуд. Про Вейна можно пустить слух по алкашам, что он отплыл на Нассау и ввязался в войну с колониальными властями. Сильвер? – гы гы. Читаем Остров Сокровищ.


	}
}
