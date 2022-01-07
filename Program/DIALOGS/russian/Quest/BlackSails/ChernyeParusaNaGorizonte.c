
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

		case "BS_CPNG_1":	//Бармен
			dialog.text = "Эй, а не тебя ли разыскивает наша надежда и опора, светлоликая мисс Гатри?";
			link.l1 = "О Боже! Что на этот раз?";
			link.l1.go = "BS_CPNG_2";
		break;

		case "BS_CPNG_2":
            dialog.text = "Понятия не имею. Но её посыльный очень убедительно просил передать капитану "+pchar.name+", что "+ GetSexPhrase("его","её") +" ждут в магазине Бермуд. И на месте этого капитана, я бы не стал медлить.";
            link.l1 = "Хорошо, я понял"+ GetSexPhrase("","а") +".";
			link.l1.go = "exit";
		break;

		//На Бермудах, перед магазином сценка. Гатри орёт на кучку пиратских кэпов. (штук 5-6 неписей Кэпов)

		case "BS_CPNG_3":	//Гатри
            dialog.text = "Мистер Фикс! Табак ценен, когда не пропитан мочой! Если вы или ваш старпом не могут обеспечить надлежащую дисциплину на корабле, то я легко могу найти вам замену!";
            link.l1 = "";
			link.l1.go = "BS_CPNG_4_1";
		break;

		case "BS_CPNG_4_1":
            npchar.name = "Фикс";
			npchar.lastname = "";
			NextDiag.CurrentNode = "BS_CPNG_4";
			DialogExit();
			DoQuestFunctionDelay("GatriSpeech", 0);
		break;

		case "BS_CPNG_4":	//Фикс
            dialog.text = "Мисс Гатри! При всём уважении, это мой корабль и я...";
            link.l1 = "";
			link.l1.go = "BS_CPNG_5_1";
		break;

		case "BS_CPNG_5_1":
            npchar.name = "Элеонора";
			npchar.lastname = "Гатри";
			NextDiag.CurrentNode = "BS_CPNG_5";
			DialogExit();
			DoQuestFunctionDelay("GatriSpeech", 0);
		break;

		case "BS_CPNG_5":	//Гатри
            dialog.text = "Превон! Теперь вы капитан ‘Лисицы”. Принимайте командование!";
            link.l1 = "";
			link.l1.go = "BS_CPNG_6_1";
		break;

		case "BS_CPNG_6_1":
            npchar.name = "Фикс";
			npchar.lastname = "";
			NextDiag.CurrentNode = "BS_CPNG_6";
			DialogExit();
			DoQuestFunctionDelay("GatriSpeech", 0);
		break;

		case "BS_CPNG_6":	//Фикс
            dialog.text = "Да я... Да как ты с... Я иду к Джекману!»";	//уходит в резиденцию
            link.l1 = "";
			link.l1.go = "BS_CPNG_7_1";
		break;

		case "BS_CPNG_7_1":
            npchar.name = "Элеонора";
			npchar.lastname = "Гатри";
			NextDiag.CurrentNode = "BS_CPNG_7";
			DialogExit();
			DoQuestFunctionDelay("GatriSpeech", 0);
		break;

		case "BS_CPNG_7":	//Гатри
            dialog.text = "А, вот и ты. Как раз вовремя. Так, господа, небольшой перерыв. Продолжим позже.";	//остальные уходят
            link.l1 = "";
			link.l1.go = "BS_CPNG_8";
			for (i = 1; i < 4; i++)
			{
				sld = CharacterFromID("Gatri_temp"+i);
				sld.LifeDay = 0;
			}
		break;

		case "BS_CPNG_8":	//Гатри
			chrDisableReloadToLocation = false;
            dialog.text = "Есть дело. Взаимовыгодное, пойдём в таверну.";	//Переход в Таверну. Диалог в комнате наверху.
            link.l1 = "Ну пойдём.";
			link.l1.go = "BS_CPNG_9_1";
		break;

		case "BS_CPNG_9_1":	//Гатри
			PChar.quest.Gatri_upstairs.win_condition.l1 = "location";
			PChar.quest.Gatri_upstairs.win_condition.l1.location = "Pirates_tavern_upstairs";
			PChar.quest.Gatri_upstairs.function = "Gatri_upstairs";
			NextDiag.CurrentNode = "BS_CPNG_9";
			DialogExit();
			ChangeCharacterAddressGroup(npchar, "Pirates_tavern_upstairs", "goto", "goto1");
            DoReloadCharacterToLocation("Pirates_tavern_upstairs","goto", "goto1");
		break;

		case "BS_CPNG_9":	//Гатри
			npchar.LifeDay = 0;
			LAi_SetActorType(npchar);
            dialog.text = "Слушай внимательно!";
            link.l1 = "Минутку. А с чего это вдруг мы друзьями стали?";
			link.l1.go = "BS_CPNG_10";
		break;

		case "BS_CPNG_10":
            dialog.text = "Это Новый Свет, здесь быстро становятся друзьями или врагами. Богатыми или мёртвыми. Успеваешь за мыслью?";
			link.l1 = ""+ GetSexPhrase("Весь","Вся") +" во внимании.";
			link.l1.go = "BS_CPNG_11"
		break;

		case "BS_CPNG_11":
            dialog.text = "Хорошо. У меня есть друг. Больше чем друг. Почти как отец... Капитан Флинт. "+ GetSexPhrase("Слышал","Слышала") +" о таком?";
            link.l1 = "Флинт. Ничего себе. Да его именем детей пугают даже в Азии.";
			link.l1.go = "BS_CPNG_12";
		break;

		case "BS_CPNG_12":
            dialog.text = "Тебе бояться нечего. А репутация его вполне заслужена – это очень жестокий и рациональный человек, но справедливый и ценящий дружбу.\n"+
							"Так вот. Он ввязался в авантюру, которая может обогатить всех причастных или наоборот – погубить. И я хочу, что бы события пошли по первому сценарию и намерена в этом всячески помочь.";
            link.l1 = "И какова моя роль в этом сценарии?";
			link.l1.go = "BS_CPNG_13";
		break;

		case "BS_CPNG_13":
            dialog.text = "Найди его в море. Запомни, очень важно – быть под чёрным флагом в момент встречи! Когда увидитесь, передай ему, что ты тоже чита"+ GetSexPhrase("л","ла")+" Марка Аврелия. Это пароль. Об остальном он сам расскажет.";
            link.l1 = "И где искать Флинта?";
			link.l1.go = "BS_CPNG_14";
		break;

		case "BS_CPNG_14":
            dialog.text = "Сложно сказать. Он только в пиратские бухты заходит и то ненадолго. Ищи его в море.";
            link.l1 = "До встречи.";
			AddQuestRecord("BSOnTheHorizon", "2");
			BSOnTheHorizon_Flint();
			link.l1.go = "exit";
		break;

		//После диалога запускаем по глобалке модельку БОЛЬШУЮ пиратскую( или фиолетовый квестовик), который курсирует между ПИРАТСКИМИ портами.
		//Под пиратским флагом – всё ОК. под любым другим – файт и провал квеста.
		//Флинт на Тяжелом военном пинасе «Морж». Высылаем шлюпку. Говорим.

		case "BS_CPNG_15":	//Флинт
            dialog.text = "Мне знаком этот корабль, но капитана я вижу впервые. Представьтесь.";
            link.l1 = "Я "+GetFullName(pchar)+", мисс Гатри просила разыскать Вас, капитан Флинт.";
			link.l1.go = "BS_CPNG_16";
		break;

		case "BS_CPNG_16":
            dialog.text = "Я знаком с мисс Гатри и её отцом, но каким образом Вы связаны с ними и со мной?";

			//это такая засада.. чтобы читали текст :)
			MakeRandomLinkOrderThree(link,
			"Я тоже читал"+ GetSexPhrase("","а") +" Марка Аврелия и являюсь больш"+ GetSexPhrase("им","ой") +" поклонни"+ GetSexPhrase("ком","цей") +" его труда и готов"+ GetSexPhrase("","а") +" оказать всяческую поддержку и помощь единомышленнику.",
			"BS_CPNG_17_Horosho",

			"Я тоже читал"+ GetSexPhrase("","а") +" Марка Антония и являюсь больш"+ GetSexPhrase("им","ой") +" поклонни"+ GetSexPhrase("ком","цей") +" его труда и готов"+ GetSexPhrase("","а") +" оказать всяческую поддержку и помощь единомышленнику.",
			"BS_CPNG_17_Ploho",

			"Я слышал"+ GetSexPhrase("","а") +", что легендарному Флинту нужна помощь в какой–то авантюре. И вот я здесь!",
			"BS_CPNG_17_Ploho"
			);
		break;

		case "BS_CPNG_17_Ploho":
            DeleteAttribute (npchar, "AlwaysFriend");
			npchar.AlwaysEnemy = true;
			dialog.text = "Я знать не знаю, кто ты так"+ GetSexPhrase("ой","ая") +" и предлагаю покинуть мой корабль.";
            link.l1 = "Эээ... До свидания.";
			NextDiag.TempNode = "BS_CPNG_17_Ploho_end";
			link.l1.go = "exit";
		break;

		case "BS_CPNG_17_Ploho_end":
            dialog.text = "Немендленно покиньте мой корабль!";
            link.l1 = "Незачем мне грубить, я уже ухожу.";
			NextDiag.TempNode = "BS_CPNG_17_Ploho_end";
			link.l1.go = "exit";
		break;

		case "BS_CPNG_17_Horosho":
			PChar.quest.MeetFlintCrew.win_condition.l1 = "location";
			PChar.quest.MeetFlintCrew.win_condition.l1.location = "Pirates_town";
			PChar.quest.MeetFlintCrew.function = "MeetFlintCrew";
            dialog.text = "Об этом лучше говорить без лишних ушей. Я улажу кое-какие дела и отправлюсь на Бермуды, поговорим там в таверне.";
			npchar.StopSailing = true;
			AddQuestRecord("BSOnTheHorizon", "3");
            link.l1 = "Хорошо, до встречи.";
			NextDiag.TempNode = "BS_CPNG_17_Horosho_end";
			link.l1.go = "exit";
		break;

		case "BS_CPNG_17_Horosho_end":
            dialog.text = "Возвращайтесь на свой корабль, давайте не будем терять время понапрасну.";
            link.l1 = "Вы правы, пойду я.";
			NextDiag.TempNode = "BS_CPNG_17_Horosho_end";
			link.l1.go = "exit";
		break;

		//Бермуды. На берегу Флинт, Сильвер, Бонс.

		case "BS_CPNG_18":	//Флинт
			//chrDisableReloadToLocation = false;
            dialog.text = "Знакомьтесь. Первый помощник Билли Бонс, каптенармус Джон Сильвер.";
			BS_ReplaceTraderWithGatri();
            link.l1 = "Рад"+ GetSexPhrase("","а") +" встрече. Я "+GetFullName(pchar)+". Идём в таверну?";
			link.l1.go = "BS_CPNG_19";
		break;

		case "BS_CPNG_19":

            dialog.text = "Потом. Сейчас в магазин. К нашей общей знакомой.";
            link.l1 = "";
			link.l1.go = "BS_CPNG_19_exit";	//Переход в магаз. Гатри, Флинт, ГГ.
		break;

		case "BS_CPNG_19_exit":
			NextDiag.CurrentNode = "BS_CPNG_9";
			sld = CharacterFromID("gatri_grunt3");
			sld.LifeDay = 0;
			sld = CharacterFromID("Pirates_trader");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\ChernyeParusaNaGorizonte.c";
			sld.dialog.currentnode = "BS_CPNG_20";
			sld.talker = 10;
			sld.LifeDay = 0;
			DialogExit();
			ChangeCharacterAddressGroup(npchar, "Pirates_store", "goto", "goto3");
            DoReloadCharacterToLocation("Pirates_store","reload", "reload1_back");
		break;

		case "BS_CPNG_20":	//Гатри
            dialog.text = "Джеймс, это я отправила "+ GetSexPhrase("его","её") +" к тебе. Он"+ GetSexPhrase("","а") +" не просто добытчик, "+ GetSexPhrase("этот капитан похож","эта девушка похожа") +" на тебя, если ты меня понимаешь.";
            link.l1 = "";
			link.l1.go = "BS_CPNG_21_1";
		break;

		case "BS_CPNG_21_1":
            npchar.name = "Джеймс";
			npchar.lastname = "Флинт";
			NextDiag.CurrentNode = "BS_CPNG_21";
			DialogExit();
			DoQuestFunctionDelay("GatriStoreSpeech", 0);
		break;

		case "BS_CPNG_21":	//Флинт
            dialog.text = "Я вижу авантюриста, опытного капитана с прекрасным кораблём и вышколенной командой. Я очень редко ошибаюсь, Элеонора, ты же знаешь. Ты ручаешься за "+ GetSexPhrase("него","неё") +"?";
            link.l1 = "";
			link.l1.go = "BS_CPNG_22_1";
		break;

		case "BS_CPNG_22_1":
            npchar.name = "Элеонора";
			npchar.lastname = "Гатри";
			NextDiag.CurrentNode = "BS_CPNG_22";
			DialogExit();
			DoQuestFunctionDelay("GatriStoreSpeech", 0);
		break;

		case "BS_CPNG_22":	//Гатри
            dialog.text = "У нас были разногласия, но всё разрешилось. Да, я ручаюсь за этого капитана.";
            link.l1 = "";
			link.l1.go = "BS_CPNG_23_1";
		break;

		case "BS_CPNG_23_1":
			sld = CharacterFromID("Flint");
			sld.dialog.currentnode = "BS_CPNG_23";
			//NPChar.Dialog.Filename = "Common_store.c";
			//NPChar.Dialog.CurrentNode = "Second time";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;

		case "BS_CPNG_23":	//Флинт
            dialog.text = "Что же, продолжим в таверне.";
            link.l1 = "";
			link.l1.go = "BS_CPNG_23_exit";	//Переход в таверну. Таверна комната.
		break;

		case "BS_CPNG_23_exit":
			PChar.quest.Flint_upstairs.win_condition.l1 = "location";
			PChar.quest.Flint_upstairs.win_condition.l1.location = "Pirates_tavern_upstairs";
			PChar.quest.Flint_upstairs.function = "Flint_upstairs";
			NextDiag.CurrentNode = "BS_CPNG_24";
			DialogExit();
			ChangeCharacterAddressGroup(npchar, "Pirates_tavern_upstairs", "goto", "goto1");
            DoReloadCharacterToLocation("Pirates_tavern_upstairs","goto", "goto1");
		break;

		case "BS_CPNG_24":	//Флинт
            dialog.text = "Итак, капитан "+GetFullName(pchar)+". Вы слышали об 'Урка Де Лима'? Испанском денежном галеоне, перевозящем не золотую руду, а отчеканенные золотые дублоны?";
            link.l1 = "Ммм… Признаюсь, я слышал"+ GetSexPhrase("","а") +" слухи об этой плавучей крепости. Но капитан, этот галеон очень хорошо охраняется!";
			link.l1.go = "BS_CPNG_25";
		break;

		case "BS_CPNG_25":
			BS_RestoreGatriTrader("q");
            dialog.text = "'Урка Де Лима' - это очень крепкий орешек, да. И у меня есть информация, где и когда этот галеон будет пополнять запасы воды и провианта для путешествия в Испанию. И это идеальный шанс расколоть этот орех.";
            link.l1 = "Какова цена вопроса?";
			link.l1.go = "BS_CPNG_26";
		break;

		case "BS_CPNG_26":
            dialog.text = "Сто пятьдесят миллионов песо!";
            link.l1 = "Матерь Божья!";
			link.l1.go = "BS_CPNG_27";
		break;

		case "BS_CPNG_27":
            dialog.text = "Вы в деле? Да или нет? Иначе – вы сами понимаете, чем закончится эта встреча.";
            link.l1 = "Конечно я в деле! Где, как и когда?!";
			link.l1.go = "BS_CPNG_28";
		break;

		case "BS_CPNG_28":
			chrDisableReloadToLocation = false;
            dialog.text = "А об этом спросим мистера Сильвера, если он ещё не упился до чёртиков.";
            link.l1 = "";
			link.l1.go = "BS_CPNG_28_exit";	//Спускаемся вниз. За столом Бонс и Сильвер.
		break;

		case "BS_CPNG_28_exit":
			PChar.quest.Silver_Downstairs.win_condition.l1 = "location";
			PChar.quest.Silver_Downstairs.win_condition.l1.location = "Pirates_tavern";
			PChar.quest.Silver_Downstairs.function = "Silver_Downstairs";
			NextDiag.CurrentNode = "BS_CPNG_24";
			DialogExit();
            DoReloadCharacterToLocation("Pirates_tavern","sit", "sit_front4");
			FreeSitLocator("Pirates_tavern", "sit_front4");  // очистим стул
			FreeSitLocator("Pirates_tavern", "sit_front1");  // очистим стул
			FreeSitLocator("Pirates_tavern", "sit_base4");  // очистим стул
			FreeSitLocator("Pirates_tavern", "sit_base1");  // очистим стул

			ChangeCharacterAddressGroup(npchar, "Pirates_tavern", "sit", "sit_base4");
			LAi_SetSitType(npchar);
			LAi_SetSitType(pchar);
			sld = CharacterFromID("BS_Billy");
			ChangeCharacterAddressGroup(sld, "Pirates_tavern", "sit", "sit_front1");
			LAi_SetSitType(sld);
			sld = CharacterFromID("BS_Silver");
			sld.dialog.filename = "Quest\BlackSails\ChernyeParusaNaGorizonte.c";
			sld.dialog.currentnode = "BS_CPNG_29";
			ChangeCharacterAddressGroup(sld, "Pirates_tavern", "sit", "sit_base1");
			LAi_SetSitType(sld);
			sld = GetCharacter(NPC_GenerateCharacter("Gatri_temp", "BS_Gatry", "woman", "woman", 1, PIRATE, -1, true));
			ChangeCharacterAddressGroup(sld, "Pirates_tavern", "tables", "stay1");
			sld.name = "Элеонора";
			sld.lastname = "Гатри";
		break;

		case "BS_CPNG_29":	//Сильвер
            dialog.text = "...";
            link.l1 = "Мистер Сильвер? Я новый компаньон капитана Флинта, самое время поделиться информацией!";
			link.l1.go = "BS_CPNG_30";
		break;

		case "BS_CPNG_30":
            dialog.text = "Приветствую капитан! Как вам местные, колониальные бордели?";
            link.l1 = "...";
			link.l1.go = "BS_CPNG_30_flint_1";
		break;

		case "BS_CPNG_30_flint_1":
			sld = CharacterFromID("Flint");
			sld.dialog.currentnode = "BS_CPNG_30_flint";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;

		case "BS_CPNG_30_flint":
            dialog.text = "Давай без шуток!";
            link.l1 = "...";
			link.l1.go = "BS_CPNG_31_1";
		break;

		case "BS_CPNG_31_1":
			sld = CharacterFromID("BS_Silver");
			sld.dialog.currentnode = "BS_CPNG_31";
			DialogExit();
			DoQuestFunctionDelay("SilverSpeech", 0);
		break;

		case "BS_CPNG_31":
            dialog.text = "Я серьёзен как никогда! У меня только часть кода от зашифрованного маршрута! Остальное у капитана Вейна.";
            link.l1 = "";
			link.l1.go = "BS_CPNG_32_1";
		break;

		case "BS_CPNG_32_1":
			sld = CharacterFromID("Gatri_temp");
			sld.dialog.currentnode = "BS_CPNG_32_gatri";
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\ChernyeParusaNaGorizonte.c";
			sld.talker = 10;
			DialogExit();
			//DoQuestFunctionDelay("GatriSpeech", 0);
		break;

		case "BS_CPNG_32_gatri":
            dialog.text = "Чарльз Вейн! Проклятье! Как!!! Рррр..!!";
            link.l1 = "";
			link.l1.go = "BS_CPNG_32_flint_1";
		break;

		case "BS_CPNG_32_flint_1":
			sld = CharacterFromID("Flint");
			sld.dialog.currentnode = "BS_CPNG_32_flint";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;

		case "BS_CPNG_32_flint":
			SetCompanionIndex(PChar, -1, GetCharacterIndex(npchar.id));//Флинт присоединяется к эскадре
			Flag_Change(PIRATE);
			BSRepairShip(npchar);
			SetShipRemovable(npchar, false);
			Fantom_SetBalls(npchar, "war");
			SetCharacterGoods(npchar,GOOD_FOOD,1000);
            dialog.text = "Успокойся Элеонора. Мистер Сильвер, где вы виделись с Вейном в последний раз?";
            link.l1 = "";
			link.l1.go = "BS_CPNG_32_silver_1";
		break;

		case "BS_CPNG_32_silver_1":
			sld = CharacterFromID("BS_Silver");
			sld.dialog.currentnode = "BS_CPNG_32_silver";
			DialogExit();
			DoQuestFunctionDelay("SilverSpeech", 0);
		break;

		case "BS_CPNG_32_silver":
            dialog.text = "Хех. Я уже сказал, но вы не слушали. В борделе на Мартинике.";
            link.l1 = "";
			link.l1.go = "BS_CPNG_33";
		break;

		case "BS_CPNG_33":
			npchar.LifeDay = 0;
			npchar.dialog.currentnode = "BS_CPNG_Final";
			sld = CharacterFromID("BS_Billy");
			sld.dialog.currentnode = "BS_CPNG_Final";
			sld.dialog.filename = "Quest\BlackSails\ChernyeParusaNaGorizonte.c";
			sld.LifeDay = 0;
			sld = CharacterFromID("Gatri_temp");
			sld.LifeDay = 0;
			sld.dialog.currentnode = "BS_CPNG_Final";
			sld = CharacterFromID("Flint");
			sld.dialog.currentnode = "BS_CPNG_Final";

            dialog.text = "";
            link.l1 = "Мне уже нравится начало приключения! В путь!";
			link.l1.go = "BS_CPNG_33_exit";
			//DoReloadCharacterToLocation("Pirates_tavern","goto", "goto2");
		break;

		case "BS_CPNG_33_exit":
			PChar.quest.BSOnTheHorizon_End.win_condition.l1 = "location";
			PChar.quest.BSOnTheHorizon_End.win_condition.l1.location = "Bermudes";
			PChar.quest.BSOnTheHorizon_End.function = "BSOnTheHorizon_End";
			BSOnTheHorizon_SeaBattle();
			AddQuestRecord("BSOnTheHorizon", "4");
			ChangeCharacterAddressGroup(pchar, "Pirates_tavern", "goto", "goto2");
			LAi_SetPlayerType(pchar);
			DialogExit();
		break;

		case "BS_CPNG_Final":
			dialog.text = "Мы еще опрокинем пару кружек перед отплытием.";
			NextDiag.TempNode = "BS_CPNG_Final";
            link.l1 = "Смотрите не опоздайте.";
			link.l1.go = "exit";
			if (npchar.id == "Gatri_temp")
			{
				dialog.text = "Попутного вам ветра, капитан.";
				link.l1 = "Благодарю.";
				link.l1.go = "exit";
			}
			if (npchar.id == "Flint")
			{
				dialog.text = "Не будем медлить.";
				link.l1 = "Соглашусь.";
				link.l1.go = "exit";
			}
		break;

		//Выходим в море. В эскадре – Флинт на «Морже».
		//На глобалке, на подходе к Мартинике – энка английский патруль.
		//Файт. (4-6 второклассников). Квест уходит в архив (СЖ: «На подходе к Мартинике нарвались на патруль англичан. Вода вам пухом, саксы. Хе хе».)

	}
}
