void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string attrLoc = Dialog.CurrentNode;

	if (findsubstr(attrLoc, "AndreAbelQuestSetNationLicence_", 0) != -1)
 	{
		i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.LicenceNation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
		Dialog.CurrentNode = "Andre_Abel_In_Tavern_Quest_Complete_2";
 	}

	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = RandPhraseSimple("Приветствую вас, капитан...", "Рад вас видеть, капитан.");
			link.l1 = "Извини, приятель, дел по горло. Не могу уделить тебе внимания.";
			link.l1.go = "exit";
			if(GetCompanionQuantity(PChar) != COMPANION_MAX)
			{
				link.l2 = "Хм, я вас раньше не видел"+ GetSexPhrase("","а") +". Мы знакомы?";
				link.l2.go = "Andre_Abel_1";
			}
		break;

		case "Andre_Abel_1":
			dialog.text = "Нет, не знакомы... Меня зовут " + GetFullName(NPChar) + ". Я капитан корабля '" + NPChar.ship.name + "'.";
			link.l1 = "А я " + GetFullName(PChar) + ". Вы что-то хотели?";
			link.l1.go = "Andre_Abel_2";
		break;

		case "Andre_Abel_2":
			dialog.text = "Капитан, могу я рассчитывать на вашу помощь? Мне очень нужен эскорт до Порт-о-Принса.";
			link.l1 = "Всего-то? А я уж думал"+ GetSexPhrase("","а") +"...";
			link.l1.go = "Andre_Abel_3";
		break;

		case "Andre_Abel_3":
			dialog.text = "Но за работу я готов заплатить не более 3000 пиастров, и мне нужно уложиться в 15 дней.";
			link.l1 = "Хм, а с чем связаны такие жёсткие условия?";
			link.l1.go = "Andre_Abel_5";
			link.l2 = "Нет, не возьмусь. Вы меня слишком ограничиваете во времени.";
			link.l2.go = "Andre_Abel_4";
		break;

		case "Andre_Abel_4":
			dialog.text = "Очень жаль...";
			link.l1 = "Не обижайтесь...";
			link.l1.go = "exit";
			NPChar.LifeDay = 0;
			NextDiag.TempNode = "Andre_Abel_No_Quest";
		break;

		case "Andre_Abel_No_Quest":
			dialog.text = RandPhraseSimple("Очень жаль, что у вас нет возможности помочь мне...", "Что ж, придётся ждать патрульного рейда.");
			link.l1 = "Не обижайтесь...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Andre_Abel_No_Quest";
		break;

		case "Andre_Abel_5":
			dialog.text = "Дело в том, что я потратил много времени и средств на ремонт судна. Теперь приходится изрядно экономить и поторапливаться.";
			link.l1 = "Ну что ж, я соглас"+ GetSexPhrase("ен","на") +". Ваш корабль уже готов к отплытию?";
			link.l1.go = "Andre_Abel_6";
			link.l2 = "Пожалуй откажусь... У меня были другие планы, и ваше предложение как-то не вдохновляет их менять.";
			link.l2.go = "Andre_Abel_4";
		break;

		case "Andre_Abel_6":
			dialog.text = "Да, корабль полностью готов. Пока вы закончите свои дела в городе, я буду ждать вас здесь.";
			link.l1 = "Хорошо. До встречи...";
			link.l1.go = "exit";
			SetQuestHeader("Andre_Abel_Quest");
			AddQuestRecord("Andre_Abel_Quest", "1");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("ся","ась"));
			PChar.Quest.Andre_Abel_Quest_1Day_Left.over = "yes";
			PChar.QuestTemp.Andre_Abel_Quest_In_Progress = true;	// Флаг - квест начат
			SetFunctionTimerCondition("Andre_Abel_Quest_2Days_Left", 0, 0, 2, false);
			NextDiag.TempNode = "Andre_Abel_To_Sea_1";
		break;

		case "Andre_Abel_7":
			dialog.text = RandPhraseSimple("Нам повезло с ветром, капитан " + GetFullName(PChar) + ".", "Форт-де-Франс - милый городишко, но за то время, пока я в нем торчал, он успел надоесть мне до чёртиков.");
			link.l1 = "Не будем же терять времени...";
			link.l1.go = "exit";
			NextDiag.Tempnode = "Andre_Abel_7";
		break;

		case "Andre_Abel_To_Sea_1":
			dialog.text = "Ну что, мы уже выходим?";
			link.l1 = "Да. Прикажите сниматься с якоря.";
			link.l1.go = "Andre_Abel_To_Sea_2";
			link.l2 = "Нет, у меня еще остались кое-какие дела.";
			link.l2.go = "Andre_Abel_To_Sea_1_1";
			NextDiag.TempNode = "Andre_Abel_To_Sea_1";
		break;

		case "Andre_Abel_To_Sea_1_1":
			dialog.text = "А нельзя ли поторопиться? Как вы помните, я ограничен в сроках.";
			link.l1 = "Я помню. Мы всё успеем...";
			link.l1.go = "exit";
			//	NextDiag.Tempnode = "Andre_Abel_To_Sea_1";
		break;

		case "Andre_Abel_To_Sea_2":
			dialog.text = "Ну вот и отлично.";
			link.l1 = "Надеюсь, этот рейс не принесёт нам хлопот.";
			link.l1.go = "Andre_Abel_To_Sea_3";
			NextDiag.TempNode = "Andre_Abel_7";
		break;

		case "Andre_Abel_To_Sea_3":
			DialogExit();
			NextDiag.CurrentNode = "Andre_Abel_7";
			AddQuestRecord("Andre_Abel_Quest", "3");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("","а"));
			PChar.Quest.Andre_Abel_Quest_2Days_Left.over = "yes";
			SetFunctionTimerCondition("Andre_Abel_Quest_15_Days_Is_Left", 0, 0, 15, false);
			SetFunctionNPCDeathCondition("Andre_Abel_Quest_Andre_Is_Dead", "Andre_Abel", false);
			SetFunctionLocationCondition("Andre_Abel_Quest_Battle_With_Pirates_Squadron", "Hispaniola2", false);
			SetFunctionExitFromLocationCondition("Andre_Abel_Quest_Delete_Andre_From_Tavern", PChar.location, false);
		break;

		case "Andre_Abel_15Days_Left_1": // Это на случай, если время закончиться тогда, когда Абель будет подходить к ГГ в порту Порт-о-Принса
			if(PChar.location == "FortFrance_Tavern")	// Из таверны можно было не выходить fix
			{
				dialog.text = PChar.Name + ", вы меня подвели! Не представляю, какие дела могли заставить свободного капитана проболтаться в этом чёртовом Форт-де-Франсе целых полмесяца!";
				link.l1.go = "Andre_Abel_15Days_Left_In_FortFrance";
				break;
			}
			dialog.text = PChar.Name + ", Вы подвели меня! Мы не успели добраться до Порт-о-Принса за пятнадцать дней!";
			link.l1 = "Не обижайся, приятель, но у меня есть дела и поважнее, чем эскорт старой калоши, причём почти задаром.";
			link.l1.go = "Andre_Abel_15Days_Left_2";
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_SetImmortal(NPChar, true);
		break;

		case "Andre_Abel_15Days_Left_In_FortFrance":
			dialog.text = "Условия сделки нарушены, поэтому я разрываю договор!";
			link.l1 = "Ну, это само собой...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;

		case "Andre_Abel_15Days_Left_2":
			dialog.text = "Я думаю, вы понимаете, что ни о каком вознаграждении и речи быть не может!";
			link.l1 = "Чего ж тут не понять?..";
			link.l1.go = "Andre_Abel_15Days_Left_3";
		break;

		case "Andre_Abel_15Days_Left_3":
			dialog.text = "Надеюсь, мы больше не встретимся.";
			link.l1 = "Как знать, как знать...";
			link.l1.go = "Andre_Abel_15Days_Left_4";
		break;

		case "Andre_Abel_15Days_Left_4":
			DialogExit();
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
//			LAi_ActorGoToLocatorFunc(NPChar, "reload", "reload6_back", "Andre_Abel_Quest_Delete_Andre", 15);
			LAi_ActorGoToLocator(NPChar, "reload", "reload6_back", "", 15);
		break;

		case "Andre_Abel_In_PortPax":
			dialog.text = "Спасибо, капитан, вы меня очень выручили. Я оплачу ваши услуги серебряными слитками, тут даже больше, чем три тысячи. Не возражаете?";
			link.l1 = "Нет, конечно... Слушайте, а зачем вам понадобилось сопровождение? Ведь ни ваше судно, ни содержимое трюма особой ценности не представляют.";
			link.l1.go = "Andre_Abel_In_PortPax_2";
			Group_DeleteGroup("Andre_Abel_Quest_Pirates_Ships"); // На всякий случай
			//AddMoneyToCharacter(PChar, 3000);
			TakeNItems(pchar, "jewelry17", 33);
			Log_Info("Вы получили серебряные слитки");
			PlaySound("interface\important_item.wav");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_SetImmortal(NPChar, true);
			PChar.Quest.Andre_Abel_Quest_15_Days_Is_Left.over = "yes";
		break;

		case "Andre_Abel_In_PortPax_2":
			dialog.text = "Хм, а нападение пиратов возле Эспаньолы вам ни о чём не говорит?";
			link.l1 = "Вот оно что! А у меня и мысли не возникло связать эту атаку с вашим присутствием в эскадре.";
			link.l1.go = "Andre_Abel_In_PortPax_3";
			link.l2 = "Чем же вы так насолили пиратам, что они рискуют атаковать ваш эскорт в прямой видимости форта?";
			link.l2.go = "Andre_Abel_In_PortPax_5";
		break;

		case "Andre_Abel_In_PortPax_3":
			dialog.text = "Да, эти события связаны напрямую...";
			link.l1 = "Понятно... Ну, счастливо оставаться!";
			link.l1.go = "Andre_Abel_In_PortPax_4";
		break;

		case "Andre_Abel_In_PortPax_4":
			DialogExit();
			AddQuestRecord("Andre_Abel_Quest", "9");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("Andre_Abel_Quest");
			DeleteAttribute(pchar,"QuestTemp.AndreAbelQuest");
			PChar.Quest.Andre_Abel_Quest_Andre_Is_Dead.over = "yes";
			NPChar.LifeDay = 0;
			LAi_ActorGoToLocator(NPChar, "reload", "reload6_back", "", 15);
//			LAi_ActorGoToLocatorFunc(NPChar, "reload", "reload6_back", "Andre_Abel_Quest_Delete_Andre", 15);
		break;

		case "Andre_Abel_In_PortPax_5":
			dialog.text = "Это довольно длинная история... Предлагаю пойти в таверну, и там, за кружкой рома, я вам её расскажу.";
			link.l1 = "Что ж, пошли...";
			link.l1.go = "Andre_Abel_In_PortPax_6";
		break;

        case "Andre_Abel_In_PortPax_6":
			DialogExit();
			LAi_ActorSetSitMode(NPChar);
			LAi_SetSitType(PChar);
			FreeSitLocator("PortPax_tavern", "sit_front2");
			FreeSitLocator("PortPax_tavern", "sit_base2");
			ChangeCharacterAddressGroup(NPChar, "PortPax_tavern", "sit", "sit_front2");
			DoFunctionReloadToLocation("PortPax_tavern", "sit", "sit_base2", "Andre_Abel_Quest_Dialog_In_PortPax_Tavern");
		break;

		case "Andre_Abel_In_Tavern_1":
			dialog.text = "В общем так... Месяца четыре назад я, при не очень благоприятных обстоятельствах, встретился с Джекменом...";
			link.l1 = "Постой! Не о том ли Джекмене ты говоришь, который заправляет бермудскими пиратами?";
			link.l1.go = "Andre_Abel_In_Tavern_2";
		break;

		case "Andre_Abel_In_Tavern_2":
			dialog.text = "Именно о нём... Так вот, Джекмен, пользуясь ситуацией, предложил мне свою защиту в обмен на 50 процентов от всей моей прибыли. Я отказался. Во-первых: потому что это форменный грабёж, а во-вторых: я не думал, что Джекмен сам станет организовывать мне проблемы. Но я ошибся...\n"
                          + "Примерно через месяц близ Гваделупы на мой галеон напали две шхуны под пиратским флагом. Мне чудом удалось уйти, правда, пришлось сбросить часть груза, чтобы сохранить ход. Спасло то, что форт Бас-Тера вовремя нас заметил и открыл огонь...\n"
                          + "Еще через пару месяцев я встретил пиратскую эскадру возле берегов Ямайки... Если бы не английский сторожевой фрегат, патрулировавший прибрежные воды, мы бы здесь с тобой уже не разговаривали...\n"
                          + "Примерно пол месяца спустя, я в составе небольшого торгового каравана пришёл в Форт-де-Франс. Там разгрузил свой потрепанный галеон и продал его в надежде сбить людей Джекмена с толку... Потом купил и оснастил флейт, взял фрахт до Порт-о-Принса и стал ждать попутчика. Но сроки по фрахту заставили меня искать эскорт...\n"
                          + "А дальше ты и сам"+ GetSexPhrase("","а") +" всё знаешь...";
			link.l1 = "Да уж, приятель, влип ты в историю...";
			link.l1.go = "Andre_Abel_In_Tavern_3";
		break;

		case "Andre_Abel_In_Tavern_3":
			dialog.text = "Я много раз думал, стоило ли тогда соглашаться на условия Джекмена. И знаешь, что я тебе скажу?.. Я уже и готов бы пойти на попятную, только какой ему теперь резон нянчиться с тем, чей бизнес рушится к чёртовой матери...\n"
                          + "Слушай, выручи, а?.. Сходи на Бермуды к Джекмену.";
			link.l1 = "И что я ему скажу?!";
			link.l1.go = "Andre_Abel_In_Tavern_4";
		break;

		case "Andre_Abel_In_Tavern_4":
			dialog.text = "Скажи: так, мол, и так, Андре Абель очень сожалеет, что не принял вашего предложения, раскаивается... Скажи, что бизнес мой практически развалился и интереса для него я уже не представляю...\n"
                          + "Сходи, а?.. Мне-то туда путь заказан - это верная смерть.";
			link.l1 = "Послушай, Андре, ты хоть понимаешь о чём просишь? Да я и не знаком"+ GetSexPhrase("","а") +" с ним вовсе, и я для него вообще - пустое место.";
			link.l1.go = "Andre_Abel_In_Tavern_5";
			link.l2 = "Попробовать, конечно, можно, но до Бермуды полмесяца пути, а у меня были совсем другие планы...";
			link.l2.go = "Andre_Abel_In_Tavern_7";
		break;

		case "Andre_Abel_In_Tavern_5":
			dialog.text = "Эх жаль... Но ты, наверное, прав"+ GetSexPhrase("","а") +". Нет, так нет... Прощай.";
			link.l1 = "Джекмен сам отстанет, когда увидит, что ты на мели... Да не отчаивайся ты так.";
			link.l1.go = "Andre_Abel_In_Tavern_6";
		break;

		case "Andre_Abel_In_Tavern_6":
			DialogExit();
			NPChar.greeting = "pirat_common";
			NPChar.LifeDay = 0;
			NextDiag.CurrentNode = "Andre_Abel_In_PortPax_Tavern_No_Quest";
			CloseQuestHeader("Andre_Abel_Quest");
			DeleteAttribute(pchar,"QuestTemp.AndreAbelQuest");
			LAi_SetSitType(NPChar);
			LAi_SetPlayerType(PChar);
			DoFunctionReloadToLocation("PortPax_tavern", "tables", "stay3", "");
		break;

		case "Andre_Abel_In_PortPax_Tavern_No_Quest":
			dialog.text = LinkRandPhrase("Жаль, что ты не можешь помочь мне...", "Что-же мне теперь делать?..", "Весь мой бизнес пошёл прахом...");
			link.l1 = "Андре, не обижайся, но ты требуешь невозможного.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Andre_Abel_In_PortPax_Tavern_No_Quest";
		break;

		case "Andre_Abel_In_Tavern_7":
			dialog.text = "Выручи, а?.. За это я дам тебе торговую лицензию на предъявителя. Очень нужная вещь, ты сам"+ GetSexPhrase("","а") +" знаешь. И еще коллекцию драгоценностей. Ну что, возьмешься?";
			link.l1 = "А чёрт, была не была! Ладно, схожу к Джекмену, авось что-то получится.";
			link.l1.go = "Andre_Abel_In_Tavern_8";
			link.l2 = "Нет, иметь дело с Джекменом за такое сомнительное вознаграждение - это не по мне.";
			link.l2.go = "Andre_Abel_In_Tavern_5";
		break;

		case "Andre_Abel_In_Tavern_8":
			dialog.text = "Вот и отлично!.. Я буду ждать тебя здесь в таверне. Всё равно море для меня сейчас слишком опасно.";
			link.l1 = "Жди... постараюсь не задерживаться.";
			link.l1.go = "Andre_Abel_In_Tavern_9";
		break;

		case "Andre_Abel_In_Tavern_9":
			dialog.text = "Ты даже не представляешь, как я тебе благодарен.";
			link.l1 = "Лучше помолись за меня. А благодарить будешь, когда вернусь с удачей.";
			link.l1.go = "Andre_Abel_In_Tavern_10";
		break;

		case "Andre_Abel_In_Tavern_10":
			ref rChar = CharacterFromID("Jackman");
			DialogExit();
			AddQuestRecord("Andre_Abel_Quest", "10");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("ся","ась"));
			NextDiag.CurrentNode = "Andre_Abel_In_Tavern_Continue_Quest";
			LAi_SetSitType(NPChar);
			LAi_SetPlayerType(PChar);
			QuestSetCurrentNode("Jackman", "Andre_Abel_Quest_Jackman_Dialog_1");
			DoFunctionReloadToLocation("PortPax_tavern", "tables", "stay3", "");
		break;

		case "Andre_Abel_In_Tavern_Continue_Quest":
			dialog.text = "Ну что, говорил"+ GetSexPhrase("","а") +" с Джекменом? Он согласился?";
			if(!CheckAttribute(PChar, "QuestTemp.Andre_Abel_Quest_Complete"))
			{
				link.l1 = LinkRandPhrase("Нет еще.", "Да не волнуйся ты так. Всё у нас получится...", "Андре, расслабься... отдыхай, развлекайся, всё равно от тебя сейчас ничего не зависит.");
				link.l1.go = "exit";
				NextDiag.TempNode = "Andre_Abel_In_Tavern_Continue_Quest";
			}
			else
			{
				link.l1 = "Да, всё получилось. Джекмен тебе больше не угрожает.";
				link.l1.go = "Andre_Abel_In_Tavern_Quest_Complete_1";
			}
			break;

		case "Andre_Abel_In_Tavern_Quest_Complete_1":
			dialog.text = "Ну, слава Богу! Не зря я на тебя так надеялся... Вот твоя коллекция драгоценностей, держи... Так, какая торговая лицензия тебе нужна?";
			link.l1 = "Пожалуй возьму английскую.";
			link.l1.go = "AndreAbelQuestSetNationLicence_0";
			link.l2 = "Я бы от французской не отказал"+ GetSexPhrase("ся","ась") +".";
			link.l2.go = "AndreAbelQuestSetNationLicence_1";
			link.l3 = "Я часто бываю в испанских поселениях, так что, испанская нужнее всего.";
			link.l3.go = "AndreAbelQuestSetNationLicence_2";
			link.l4 = "Голландская конечно! С нею практически в любой порт зайти можно.";
			link.l4.go = "AndreAbelQuestSetNationLicence_3";
			TakeNItems(pchar, "icollection", 1);
			Log_Info("Вы получили сокровища");
			PlaySound("interface\important_item.wav");
		break;

		case "Andre_Abel_In_Tavern_Quest_Complete_2":
			dialog.text = "Вот и славно. Торговая лицензия " + XI_ConvertString(Nations[sti(NPChar.LicenceNation)].Name + "Gen") + " у меня есть только на 40 дней. Не забудь, что входить в порт нужно под дружественным флагом... Да ты и сам"+ GetSexPhrase("","а")+" это прекрасно знаешь.";
			link.l1 = "Знаю конечно! Спасибо... Слушай, а откуда у тебя лицензии всех государств?";
			link.l1.go = "Andre_Abel_In_Tavern_Quest_Complete_3";
		break;

		case "Andre_Abel_In_Tavern_Quest_Complete_3":
			dialog.text = "Хм, а ты думаешь, с какой радости Джекмен за мной по всем Карибам гонялся?..\n"
                          + "Ну, теперь мы в расчёте. Спасибо тебе и прощай...";
			link.l1 = "Хм, и тебе счастливо оставаться...";
			link.l1.go = "Andre_Abel_In_Tavern_Quest_Complete_4";
		break;

		case "Andre_Abel_In_Tavern_Quest_Complete_4":
			DialogExit();
			NPChar.LifeDay = 0;
			GiveNationLicence(sti(NPChar.LicenceNation), 40);
			SetCharacterShipLocation(NPChar, "none");	// Уберем корабль из порта
			NextDiag.CurrentNode = "Andre_Abel_In_Tavern_Quest_Complete_5";
			AddQuestRecord("Andre_Abel_Quest", "23");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("Andre_Abel_Quest", "sNation", XI_ConvertString(Nations[sti(NPChar.LicenceNation)].Name + "Gen"));
			CloseQuestHeader("Andre_Abel_Quest");
			DeleteAttribute(pchar,"QuestTemp.AndreAbelQuest");
		break;

		case "Andre_Abel_In_Tavern_Quest_Complete_5":
			dialog.text = LinkRandPhrase("Спасибо, "+ GetSexPhrase("приятель","подруга") +", ты меня очень выручил"+ GetSexPhrase("","а") +".", "Я рад, что ты смог"+ GetSexPhrase("","ла") +" мне помочь.", "Наконец-то можно спокойно заняться делом.");
			link.l1 = "Удачи тебе!.. Да гляди, не попадайся больше.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Andre_Abel_In_Tavern_Quest_Complete_5";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
