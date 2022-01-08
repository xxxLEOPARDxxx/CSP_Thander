
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

		//Условия – закончен морской файт у Мартиники, «Морж» цел. У гг пиратский флаг. Иначе файт с флинтом. Весь квест запрет на смену флага.
		//Пляж Ламантен. ГГ, Флинт, Сильвер, Бонс. Бродят матросы, несколько штук.

		case "BS_KS_1":	//Флинт
			dialog.text = "Неожиданно, но предсказуемо.";
			link.l1 = "Что? А, ты про англичан? Да, обычно они в этих водах не охотятся.";
			link.l1.go = "BS_KS_2";
		break;

		case "BS_KS_2":
            dialog.text = "Есть у меня мысли, откуда этот патруль, но предположения - нужно проверить. Мистер Сильвер, вы отправляетесь с капитаном "+GetFullName(pchar)+" в Форт де Франс. Задача – добыть вторую часть кода. Любой ценой. Приказ понятен?";
            link.l1 = "";
			link.l1.go = "BS_KS_3_1";
		break;

		case "BS_KS_3_1":
			sld = CharacterFromID("BS_Silver");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Kurtuaznye_Strasti.c";
			sld.dialog.currentnode = "BS_KS_3";
			DialogExit();
			DoQuestFunctionDelay("SilverSpeech", 0);
		break;

		case "BS_KS_3":	//Сильвер
            dialog.text = "Понятен. Зачем так строго капитан? Я думал, мы уже друзья.";
            link.l1 = "";
			link.l1.go = "BS_KS_4_1";
		break;

		case "BS_KS_4_1":
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.currentnode = "BS_KS_4";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;

		case "BS_KS_4":	//Флинт
			sld = CharacterFromID("BS_Silver");
			LAi_SetActorTypeNoGroup(npchar);
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorTurnToCharacter(npchar, sld);
			LAi_ActorTurnToCharacter(sld, npchar);
            dialog.text = "(Смотрит не мигая на Сильвера)";
            link.l1 = "";
			link.l1.go = "BS_KS_5_1";
		break;

		case "BS_KS_5_1":
			sld = CharacterFromID("BS_Silver");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.currentnode = "BS_KS_5";
			DialogExit();
			DoQuestFunctionDelay("SilverSpeech", 0);
		break;

		case "BS_KS_5":	//Сильвер
			sld = CharacterFromID("BS_Silver");
			LAi_SetActorTypeNoGroup(npchar);
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorTurnToCharacter(npchar, sld);
			LAi_ActorTurnToCharacter(sld, npchar);
            dialog.text = "Кхгм… Да да, мы это сделаем, капитан.";
            link.l1 = "";
			link.l1.go = "BS_KS_6_1";
		break;

		case "BS_KS_6_1":
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.currentnode = "BS_KS_6";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;

		case "BS_KS_6":
			SetQuestHeader("BSCourtlyPassions");
			AddQuestRecord("BSCourtlyPassions", "1");

            dialog.text = "Как только разберётесь с кодом, я буду ждать вас на Бермудах. Удачи.";
            link.l1 = "И вам не хворать. Сильвер, за мной.";
			sld = CharacterFromID("BS_Silver");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "BSCPFlint_talk");
			DeleteAttribute(npchar, "curtown");
			pchar.BSCPSailor_talk = true;
			pchar.BSCPSilver_talk = true;
			link.l1.go = "BS_KS_6_exit";
		break;

		case "BS_KS_6_exit":
			DialogExit();
			RemoveCharacterCompanion(PChar, npchar);
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", LAi_FindNearestFreeLocator2Pchar("reload"), "Pirates_store", "", "", "", -1);
			//Запускаем Матроса.
			if(pchar.location == "LeFransua_port" || pchar.location == "FortFrance_town" ||  pchar.location == "Shore38" ||   pchar.location == "Shore39")
			{
				BSCourtlyPassions_sailor();
			}
			else
			{
				SetFunctionExitFromLocationCondition("BSCourtlyPassions_sailor_begin_again", pchar.location, true);
			}

		break;

		//Ставим Сильвера во временные оффы. Лучше сразу в абордаги, если возможно.

		case "BS_KS_7":	//Обращаемся к матросу
            dialog.text = "Приказы?";
			string order1, order2, order3;
			if (pchar.nation != FRANCE)
			{
				order1 = "Возвращайся на борт и подними французский флаг. ";
				Flag_Change(FRANCE);
			}
			else order1 = "";
			if (pchar.location != "Shore39")
			{
				order2 = "Отгоните корабль в бухту Ле Марен. ";
				pchar.location.from_sea = "Shore39";
			}
			else order2 = "";
			if (order1 == "" && order2 == "") order3 = "Вернись на корабль и будь начеку. Если вдруг патруль, скажи, что руль заклинило, до верфи не дойти.";
			else order3 = "Если вдруг патруль, скажи, что руль заклинило, до верфи не дойти.";
            link.l1 = order1+order2+order3;
			link.l1.go = "BS_KS_7_1";
		break;

		case "BS_KS_7_1":	//Обращаемся к матросу
			AddQuestRecord("BSCourtlyPassions", "2");
			dialog.text = "Слушаюсь, капитан!";
            link.l1 = "Хороший ты моряк, Сандро, к тому же дольше всех у меня служишь. Продолжай в том же духе, и может, однажды повысим тебя до офицера.";
			link.l1.go = "BS_KS_7_2";
		break;

		case "BS_KS_7_2":	//Обращаемся к матросу
            dialog.text = "Не мое это, капитан. Много ответственности, да и обязанностей. Я простой матрос и не хочу этого менять.";
            link.l1 = "Как знаешь. Ладно, бегом, выполняй приказ.";
			link.l1.go = "BS_KS_7_2_exit";
		break;

		case "BS_KS_7_2_exit":	//Обращаемся к матросу
			DialogExit();
			DeleteAttribute(pchar, "BSCPSailor_talk");
			LocatorReloadEnterDisable(pchar.location.from_sea, "boat", true);
			chrDisableReloadToLocation = false;
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", Get_My_Cabin(), "", "", "", 10);
			sld = CharacterFromID("Flint");
			DeleteAttribute(sld, "curtown");
			//Запускаем Сильвера.
			if(pchar.location == "FortFrance_town")
			{
				BSCourtlyPassions_sailor();
			}
			else
			{
				SetFunctionExitFromLocationCondition("BSCourtlyPassions_sailor_begin_again", pchar.location, true);
			}
		break;

		//Переместить корабль в Ле Марен

		//Запись в СЖ: «Жаркая схватка у Мартиники была. Какого дьявола тут забыли английские патрули? Ну да ладно, этим вопросом займётся Флинт, моя задача – добыть часть кода у Чарльза Вейна»

		//Залочить выход в море. Топаем в Форт де Франс ножками.

		//На следующей локе, Сильвер заводит диалог.

		case "BS_KS_8":	//Сильвер
            for (i = 1; i < 7; i++)
			{
				sld = CharacterFromID("BSOnTheHorizon_enemyfleet"+i);
				sld.LifeDay = 0;
			}
			dialog.text = "Прекрасный у вас корабль, а команда – прям орлы!";
            link.l1 = "Спасибо. Так что там за история с кодом из двух половин? Только коротко, прошу тебя. Я не в настроении для историй.";
			link.l1.go = "BS_KS_9";
		break;

		case "BS_KS_9":
            dialog.text = "Вам, капитанам, как будто палку в задницу засовывают при получении капитанства: Слушай приказ!!! Фок-марсы зарифить!!! Лево руля!!!";
            link.l1 = "Ха. А ты забавный. Служил у меня кок, тоже любил шутейки пошутить разные. Кажется, Дед Старый его кликуха была.";
			link.l1.go = "BS_KS_10";
		break;

		case "BS_KS_10":
            dialog.text = "В любой команде нужен такой человек! И лямка моряцкая не такой тяжкой кажется тогда!";
			link.l1 = "Возможно. Да вот, дошутился Дед, нашли его с линьком вокруг шеи обмотанным. В трюме. И никто ни слухом, ни духом. Чего побледнел? Шучу я. Ха–ха.";
			link.l1.go = "BS_KS_11"
		break;

		case "BS_KS_11":
            dialog.text = "Ха-ха. Ладно, к делу. В борделе есть девица одна, Максин звать. Креолка из Луизианы. Хороша собой чертовка. Что в койке вытворяет... Слов нет описать. Но не только на передок умелица, но и с головой всё в порядке. Во всех смыслах. Обвела меня пьяного и утомлённого утехами как мальчика и увела страницу с кодом.";
            link.l1 = "Занятно и почти смешно, если бы страница сто пятьдесят миллионов не стоила бы.";
			link.l1.go = "BS_KS_12";
		break;

		case "BS_KS_12":
            dialog.text = "Согласен. Страницу я только наполовину запомнил, времени особо не было, сам"+ GetSexPhrase("","а") +" понимаешь. Я и так и сяк пробовал с нею, но девка ушлая и в городе связей у неё как у губернатора. Порешили мы компаньонами стать и продать этот код кому-нибудь из каперов или пиратов. Тут её связи как нельзя кстати.";
            link.l1 = "Угу, а дальше что?";
			link.l1.go = "BS_KS_13";
		break;

		case "BS_KS_13":
            dialog.text = "Ну и вышла она на старпома Чарльза Вейна. Джека Рекхэма. Джек – парень хороший, познакомишься, сам"+ GetSexPhrase("","а") +" поймёшь, и готов он был обмен честный произвести. Да только вот команда его – головорезы и отморозки те ещё. Кто-то что-то услышал, и на месте обмена резня вышла. Меня чудом Флинт вытащил, Максин – у пиратов, страница с кодом вероятно тоже у них.";
            link.l1 = "И зачем нам в бордель идти, если девка и страница у пиратов? Где их стоянка? В Ле Франсуа?";
			link.l1.go = "BS_KS_14";
		break;

		case "BS_KS_14":
            dialog.text = "Да птички напели, что Макс у себя в гнёздышке, а Вейн корабль покрупнее ищет и команду набирает. Видать про «Урку» то же слышал.";
            link.l1 = "Интересно девки пляшут... Давай для начала заглянем к местному трактирщику. Хочу поподробней расспросить про эту Максин.";
			link.l1.go = "BS_KS_14_1";
		break;

		case "BS_KS_14_1":
			AddQuestRecord("BSCourtlyPassions", "3");
			dialog.text = "В таверну так в таверну. Вы здесь капитан.";
            link.l1 = "То-то же.";
			link.l1.go = "BS_KS_14_2";
		break;

		case "BS_KS_14_2":
            DialogExit();
			DeleteAttribute(pchar, "BSCPSilver_talk")
			chrDisableReloadToLocation = false;
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = CharacterFromID("FortFrance_tavernkeeper");
			sld.dialog.filename = "Quest\BlackSails\Kurtuaznye_Strasti.c";
			sld.dialog.currentnode = "BS_KS_15";
		break;

		//Запись в СЖ «Страница у девки, девка у пиратов, пираты в ларце, ларец на дубе... Ничего не понятно, но начать стоит с таверны, разузнать про эту Максин».

		//Форт де Франс. У бармена интересуемся Максин

		case "BS_KS_15":	//Бармен
            dialog.text = "Приветствую вас в нашем скромном заведении, капитан. Чем могу помочь?";
            link.l1 = "А как у вас в городе с утехами телесными? Слышал"+ GetSexPhrase("","а") +" я, что есть потаскушка у вас одна, креолка.";
			link.l1.go = "BS_KS_16";
		break;

		case "BS_KS_16":
            dialog.text = "О постельных утехах в соответствующих местах интересуйтесь, "+ GetSexPhrase("месье","мадемуазель") +". У меня заведение приличное.";
            link.l1 = "Понимаю. Пятьсот пиастров поможет уладить наши недоразумения?";
			link.l1.go = "BS_KS_17";
		break;

		case "BS_KS_17":
            dialog.text = "Пятьсот? Я что похож на попрошайку? Пять тысяч песо, и я всё расскажу.";
			NextDiag.TempNode = "BS_KS_15";
			if (sti(pchar.money >= 5000))
			{
				link.l1 = "Я слушаю.";
				link.l1.go = "BS_KS_18";
			}
			link.l2 = "Проклятье, куда делся мой кошель?";
			link.l2.go = "exit";
		break;

		case "BS_KS_18":
			AddMoneyToCharacter(pchar, -5000);
            dialog.text = "Тебе нужна Максин, она работает в местном борделе. Лучше поспрашивай о ней у хозяйки, она осведомлена куда лучше меня.";
            link.l1 = "И за это я тебе заплатил"+ GetSexPhrase("","а") +" пять тысяч? Два фута холодной стали в брюхо не хочешь?";
			link.l1.go = "BS_KS_19";
		break;

		case "BS_KS_19":
			AddQuestRecord("BSCourtlyPassions", "4");
            dialog.text = "Смилуйтесь! Ну еще я слышал, что она клиентов не принимает, пираты её сильно за долги попользовали. Говорят команда самого Вейна... Ага, прям вся команда. Так что ищи другую, тут девок на любой вкус хватает. Только, пожалуйста, разносчицу не трогай. Племяшка моя.";
            link.l1 = "С этого и стоило начинать. Ладно, живи. А сам Вейн в городе появляется?";
			link.l1.go = "BS_KS_19_1";
		break;

		case "BS_KS_19_1":
            dialog.text = "Я с пиратами дел не веду. Боком оно выходит. Так что – это не ко мне.";
            link.l1 = "Ну бывай.";
			link.l1.go = "BS_KS_19_1exit";
		break;

		case "BS_KS_19_1exit":
			DialogExit();
			npchar.dialog.filename = "Common_tavern.c";
			NPChar.Dialog.CurrentNode = "First time";
			sld = CharacterFromID("FortFrance_hostess");
			sld.dialog.filename = "Quest\BlackSails\Kurtuaznye_Strasti.c";
			sld.dialog.currentnode = "BS_KS_20";
		break;
		//Запись в СЖ. Пора поискать Максин в борделе.

		//Идём в бордель, спрашиваем о Максин у хозяйки.

		case "BS_KS_20":
            dialog.text = "Привествую, "+GetSexPhrase("месье","мадемуазель")+". Какими судьбами?";
            link.l1 = "Я хочу провести время с одной из двоих красоток. Кажется, мне приглянулась Максин.";
			link.l1.go = "BS_KS_21";
		break;

		case "BS_KS_21":
            dialog.text = "Она сейчас не в той форме, чтобы принимать клиентов. Но за пятьдесят тысяч мы с ней можем сделать исключение.";
            NextDiag.TempNode = "BS_KS_20";
			if (sti(pchar.money >= 50000))
			{
				link.l1 = "Благодарю, мадемуазель, я уже сгораю от нетерпения.";	//Даём ей 10000
				link.l1.go = "BS_KS_21_exit";
			}
			link.l2 = "Проклятье, куда делся мой кошель?";
			link.l2.go = "exit";
		break;

		case "BS_KS_21_exit":
			DialogExit();
			npchar.Dialog.Filename = "Common_Brothel.c";
			NPChar.Dialog.CurrentNode = "First time";
			LocatorReloadEnterDisable("FortFrance_Brothel", "reload2_back", false);
            AddMoneyToCharacter(pchar, -50000);

			sld = GetCharacter(NPC_GenerateCharacter("BS_Maks", "BS_Maks", "woman", "woman", 1, PIRATE, -1, false));
			sld.name 	= "Макс";
			sld.lastname 	= "";
			ChangeCharacterAddressGroup(sld, "FortFrance_Brothel_room", "goto", "goto3");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Kurtuaznye_Strasti.c";
			sld.dialog.currentnode = "BS_KS_22";
		break;

		//Наверху смуглая шлюха

		case "BS_KS_22":	//Максин
            dialog.text = "Я ждала тебя, "+ GetSexPhrase("котик","лисичка") +". А ты что здесь делаешь, Джон?";
            link.l1 = "Думаю, ты догадалась, что мы сюда не за утехами пришли.";
			link.l1.go = "BS_KS_22_1";
		break;

		case "BS_KS_22_1":	//Максин
            dialog.text = "Зачем тогда?";
            link.l1 = "Нам все известно о твоих злоключениях. Перейду к делу. Мне нужно то, что ты пыталась продать старпому Вейна. Скажи мне, где прячутся эти проклятые пираты и я выпущу им кишки, если это тебя утешит.";
			link.l1.go = "BS_KS_23";
		break;

		case "BS_KS_23":
			AddQuestRecord("BSCourtlyPassions", "5");
            dialog.text = "Ты так похож"+ GetSexPhrase("","а") +" на капитана Флинта! Такой же напор и рвение. Как я могу устоять? В полночь вся шайка Чарльза Вейна будет в подземелье, здесь в городе. Прошу, когда всё будет кончено, отвези меня в Порт Рояль?";
			link.l1 = "Договорились. На рассвете, жди меня в бухте Ле Марен.";
			link.l1.go = "BS_KS_24_1";
		break;

		case "BS_KS_24_1":
			LAI_SetActorType(npchar);
			sld = CharacterFromID("BS_Silver");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.currentnode = "BS_KS_25";
			DialogExit();
			DoQuestFunctionDelay("SilverSpeech", 0);
		break;
		//На выходе из борделя диалог с Сильвером

		case "BS_KS_24":	//Сильвер
            dialog.text = "Как наши успехи?";
            link.l1 = "Завтра отправляемся в подземелье в полночь.";
			link.l1.go = "BS_KS_25";
		break;

		case "BS_KS_25":
            dialog.text = "Кэп, я не боец. Я больше языком воюю, чем саблей.";
            link.l1 = "Я заметил"+ GetSexPhrase("","а") +". Сиди здесь и охраняй нашу девочку Максин, потом проводишь её до бухты.";
			link.l1.go = "BS_KS_26";
		break;

		case "BS_KS_26":
            dialog.text = "С превеликим удовольствием.";
			LAI_SetActorType(npchar);
            link.l1 = "Увидимся.";
			link.l1.go = "exit";
			LAi_LockFightMode(PChar, true);
			PChar.quest.BSCourtlyPassions_wait.win_condition.l1 = "location";
			PChar.quest.BSCourtlyPassions_wait.win_condition.l1.location = "FortFrance_town";
			PChar.quest.BSCourtlyPassions_wait.function = "BSCourtlyPassions_wait";
		break;

		//Запись В СЖ «Следующей ночью отправляюсь в подземелье Форт де Франс. Бой предстоит жаркий, нужно подготовиться. Ах да. И не забыть потом Максин доставить в Порт Рояль»

		//Тусим до следующей полуночи. Идём в подземку. Там по полной пиратов, прям чтоб мясо. Вейн среди них, но бессмертный.

		case "BS_KS_27":	//Чарльз Вейн
            ref _location = &locations[reload_location_index];
			LAi_LocationFightDisable(_location, false);
		    dialog.text = "Какого дьявола ты тут разнюхиваешь?";
            link.l1 = "Есть разговор, Чарльз. О странице, которую ты присвоил себе.";
			link.l1.go = "BS_KS_28";
		break;

		case "BS_KS_28":
			AddQuestRecord("BSCourtlyPassions", "6");
			LAi_LockFightMode(PChar, false);
            dialog.text = "Что встали как бараны? Убить их всех!";
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", Get_My_Cabin(), "", "", "", 10);
			//chrDisableReloadToLocation = false;
            link.l1 = "Куда это ты намылился?";
			link.l1.go = "BS_KS_28_exit";
			chrDisableReloadToLocation = false;
			//BSCourtlyPassions_spawn_podsos();

			PChar.quest.BSCourtlyPassions_fleeng.win_condition.l1 = "location";
			PChar.quest.BSCourtlyPassions_fleeng.win_condition.l1.location = "FortFrance_town";
			PChar.quest.BSCourtlyPassions_fleeng.function = "BSCourtlyPassions_fleeng";
		break;

		case "BS_KS_28_exit":
			DialogExit();
			LAi_group_SetHearRadius("EnemyFight", 100.0);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", Get_My_Cabin(), "", "", "", 10);
		break;

		//Файт. Как только минусуем его подсосов – Вейн удирает.  Было бы круто, чтоб прям удирал в каждой локе. Улицы – за воротами – и т.д. прям до Ле Марен. В бухте пачка пиратов с его корабля, опять файт мясной. Вейн – удирает после их гибели в море. Выходим в море. «Рейнджер» - корабль Вейна линейный бриг. Морской файт – абордаж. После первой стадии в каюте – диалог.

		case "BS_KS_29":
            dialog.text = "Что же, похоже удача покинула Чарльза Вейна. Но просто так я не сдамся!";
            link.l1 = "Может просто поговорим?";
			link.l1.go = "BS_KS_30";

			PChar.quest.BSCourtlyPassions_final.win_condition.l1 = "location";
			PChar.quest.BSCourtlyPassions_final.win_condition.l1.location = "Shore39";
			PChar.quest.BSCourtlyPassions_final.function = "BSCourtlyPassions_final";
			DeleteAttribute(pchar, "BSCourtlyPassionsFail");
		break;

		case "BS_KS_30":
            dialog.text = "Ха-ха-ха. Ты издеваешься надо мной!";
            link.l1 = "Страница с кодом. Это всего лишь половина. У нас есть вторая часть. Объединим усилия? Золота 'Урки' на всех хватит.";
			link.l1.go = "BS_KS_31";
			//link.l2 = "Ты не исправим, Вейн, у меня нет другого выбора, кроме как лишить тебя головы.";
			//link.l2.go = "BITVA";
		break;

		case "BS_KS_31":
            dialog.text = "У кого это, 'у нас'? Ты не с Флинтом ли вместе?";
            link.l1 = "Да, я с ним. Я знаю о его репутации, но сто пятьдесят миллионов, Чарльз, подумай об этом!";
			link.l1.go = "BS_KS_32";
		break;

		case "BS_KS_32":
			AddQuestRecord("BSCourtlyPassions", "7");
			sld = CharacterFromID("BS_Vein");
			LAi_SetImmortal(sld, true);
            dialog.text = "Ладно, я согласен. Почему бы и нет. Всё к чертям катится в последнее время, но страницу я вручу лично Флинту. Очень хочется посмотреть в его рыбьи глаза при этом.";
            link.l1 = "Вот и чудно. Увидимся на Бермудах. У меня ещё есть незаконченное дело.";
			link.l1.go = "BS_KS_32exit";
		break;

		case "BS_KS_32exit":
            QuestAboardCabinDialogSurrender();
			//SetEnemyToKilled();
            DialogExit();
		break;

		//Возвращаемся к воротам, там Макс и Сильвер.

		case "BS_KS_33":	//Сильвер
            dialog.text = "Капитан?";
            link.l1 = "Дело сделано, отправляемся.";
			link.l1.go = "BS_KS_34";
		break;

		case "BS_KS_34":	//Сильвер
			npchar.LifeDay = 0;
            dialog.text = "Я в вас ни на секунду не сомневался!";
            link.l1 = "Ага, давай только не подлизывайся.";
			link.l1.go = "BS_KS_35exit";
		break;


		case "BS_KS_35exit":
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", Get_My_Cabin(), "", "", "", 10);
			sld = CharacterFromID("BS_Maks");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Kurtuaznye_Strasti.c";
			sld.dialog.currentnode = "BS_KS_35";
			DialogExit();
			DoQuestFunctionDelay("MaksSpeech", 0);
		break;

		case "BS_KS_35":
            dialog.text = "Они все мертвы?";
            link.l1 = "Большая часть.";
			link.l1.go = "BS_KS_36_1";
		break;

		case "BS_KS_36_1":
			npchar.LifeDay = 0;
            dialog.text = "Теперь вы отвезете меня в Порт Рояль?";
            link.l1 = "Я же обещал"+ GetSexPhrase("","а") +". Прошу на борт!";
			link.l1.go = "BS_KS_36_exit";
			PChar.quest.BSCourtlyPassions_finalRoyal.win_condition.l1 = "location";
			PChar.quest.BSCourtlyPassions_finalRoyal.win_condition.l1.location = "PortRoyal_town";
			PChar.quest.BSCourtlyPassions_finalRoyal.function = "BSCourtlyPassions_finalRoyal";
		break;

		case "BS_KS_36_exit":
			DialogExit();
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", Get_My_Cabin(), "", "", "", 10);
		break;

		case "BS_KS_36":
			chrDisableReloadToLocation = false;
            dialog.text = "Благодарю вас, капитан! Обо мне еще никто так не заботился.";
            link.l1 = "Все когда-то бывает в первый раз.";
			link.l1.go = "BS_KS_37";
		break;

		case "BS_KS_37":
			npchar.LifeDay = 0;
            dialog.text = "Надеюсь, мы еще встретимся?";
            link.l1 = "Кто знает? Возможно. Береги себя.";
			link.l1.go = "BS_KS_37exit";
		break;

		case "BS_KS_37exit":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload9_back", Get_My_Cabin(), "", "", "", 10);
			CloseQuestHeader("BSCourtlyPassions");
			SetQuestHeader("BSChaseBegun");
			AddQuestRecord("BSChaseBegun", "1");

			BSChaseBegun();
		break;

		//Отвозим шлюху в ПР, она уходит с корабля. Отправляемся на Бермуды.

		//Запись в СЖ «Дело сделано, теперь можно отправиться на Бермуды.»

	}
}
