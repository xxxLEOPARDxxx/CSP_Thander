
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Мне не о чем с тобой говорить, извини...";
			link.l1 = "Понятно.";
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "exit_hl":
			NextDiag.TempNode = "PiratesManNew1";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		// -------------------------------------- квест №1 -------------------------------------------------
		//первая встреча с посыльным Моргана в Пуэрто Принсипе
		case "PiratesMan1":
			if (pchar.questTemp.State == "" || sti(pchar.questTemp.CurQuestNumber) > 8 || sti(pchar.questTemp.NationQuest) == SPAIN)
			{
				if(CheckAttribute(pchar, "QuestTemp.AndreAbelQuest") || CheckAttribute(pchar, "questTemp.WhisperTutorial"))
				{
					dialog.text = RandPhraseSimple("Чего тебе? Проходи мимо.", "Хватит загораживать дорогу, отвали.");
					link.l1 = RandPhraseSimple("Знаешь что? Не гавкай!", "Поумерь свой пыл. Не то быстро охлажу его!");
					link.l1.go = "exit";
					NextDiag.TempNode = "PiratesMan1";
				}
				else
				{
					dialog.text = "Здорово, "+ GetSexPhrase("парень","деваха") +"! Я смотрю, кораблик у тебя имеется... Подзаработать хочешь?";
					link.l1 = "Извини, нет времени пока, давай попозже.";
					link.l1.go = "exit_hl";
					link.l2 = "Может и захочу, а что нужно?";
					link.l2.go = "PiratesMan1_1";
				}
			}
			else
			{
				dialog.text = "Здорово, "+ GetSexPhrase("парень","деваха") +". Эх, дьявол!! Жаль, что не могу тебе довериться, очень жаль...";
				link.l1 = "А в чем дело-то? Я чем-то запятнал"+ GetSexPhrase("","а") +" себя в глазах Берегового Братства?";
				link.l1.go = "PiratesManNot_1";
				npchar.talker = 2; //начать диалог
				NextDiag.TempNode = "PiratesManNew1";
			}
		break;
		case "PiratesMan1_1":
			dialog.text = "Нужно оказать одну услугу Генри Моргану. Если надумаешь, приходи в таверну, там поговорим.";
			link.l1 = "Хм, ну хорошо.";
			link.l1.go = "PiratesMan1_2";
		break;
		case "PiratesMan1_2":
			DialogExit();
			NextDiag.CurrentNode = "Tavern_1";
			//LockQuestLine(characterFromId("eng_guber")); // лочим английскую линейку
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			FreeSitLocator("PuertoPrincipe_tavern", "sit3");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5", "PuertoPrincipe_tavern", "sit", "sit3", "PiratesLine_toTavern", -1);
		break;

		case "PiratesManNot_1":
			dialog.text = "Да нет, дело не в этом. Ты занят"+ GetSexPhrase("","а") +" работой на генерал-губернатора " + NationNameGenitive(sti(pchar.questTemp.NationQuest)) + ". Сейчас для меня это проблема.";
			link.l1 = "Действительно жаль...";
			link.l1.go = "PiratesManNot_2";
		break;
		case "PiratesManNot_2":
			dialog.text = "Послушай, ты приходи ко мне позже, когда твоя служба будет подходить к концу. Думаю, что тогда смогу быть с тобой откровенным.";
			link.l1 = "Хорошо. Буду иметь ввиду.";
			link.l1.go = "exit";
            SetQuestHeader("Pir_Line_0_Waiting");
            AddQuestRecord("Pir_Line_0_Waiting", "1");
			AddQuestUserData("Pir_Line_0_Waiting", "sNation", NationNameAblative(sti(pchar.questTemp.NationQuest)));
		break;

		case "PiratesManNew1":
			if (pchar.questTemp.State == "" || sti(pchar.questTemp.CurQuestNumber) > 8 || sti(pchar.questTemp.NationQuest) == SPAIN)
			{
				dialog.text = "Здорово, "+ GetSexPhrase("парень","деваха") +"! Я смотрю, кораблик у тебя имеется... Подзаработать хочешь?";
				link.l1 = "Извини, нет времени пока, давай попозже.";
				link.l1.go = "exit_hl";
				link.l2 = "А что нужно делать?";
				link.l2.go = "PiratesMan1_1";
			}
			else
			{
				dialog.text = "А-а, опять мы с тобой встретились. Но пока не время, "+ GetSexPhrase("приятель","подруга") +". Позже...";
				link.l1 = "Может и захочу, а что нужно?";
				link.l1.go = "exit";
				npchar.talker = 2; //начать диалог
				NextDiag.TempNode = "PiratesManNew1";
			}
		break;
		//разговор в таверне Пуэрто Принсипе
		case "Tavern_1":
			LAi_SetSitType(pchar);
			dialog.text = "Ну, что скажешь? Готов"+ GetSexPhrase("","а") +" помочь самому Моргану?";
			link.l1 = "Моргану?!  Если это тот самый Морган – адмирал Берегового Братства, то готов"+ GetSexPhrase("","а") +"... а что делать-то нужно?";
			link.l1.go = "Tavern_2";
			npchar.lifeDay = 0;
		break;
		case "Tavern_2":
			dialog.text = "Да, все просто. Берешь к себе на борт одного человечка, Морган его уже заждался, и – в Порт-Рояль. А там уж Морган вас встретит... и расплатится там же. Как видишь, ничего сложного. И не забывай, этим ты окажешь Моргану большую услугу. Ну как, соглас"+ GetSexPhrase("ен","на") +"?";
			link.l1 = "Хм, невелика услуга... А что за человек?";
			link.l1.go = "Tavern_3";
			link.l2 = "Морган, конечно, известный пират, но у меня есть другие дела, и я не намерен"+ GetSexPhrase("","а") +" все бросать. И вообще, я не кэп курьерского баркаса!";
			link.l2.go = "Tavern_over";
		break;
		case "Tavern_3":
			dialog.text = "Да ничего особенного. Зовут Джон Болтон, будет ждать тебя в бухте. Ты только лишнего не болтай!";
			link.l1 = "Я не из болтливых. Мне следует чего-то опасаться?";
			link.l1.go = "Tavern_4";
		break;
		case "Tavern_4":
			dialog.text = "Опасаться? Да нет. Просто Морган этого не любит... Ну что, соглас"+ GetSexPhrase("ен","на") +"?";
			link.l1 = "Соглас"+ GetSexPhrase("ен","на") +".";
			link.l1.go = "Tavern_5";
		break;
		case "Tavern_5":
			dialog.text = "Вот и отлично! Ну, счастливо тебе, "+ GetSexPhrase("приятель","подруга") +". Будь здоров"+ GetSexPhrase("","а") +"!";
			link.l1 = "И тебе того же...";
			link.l1.go = "exit";
			npchar.lifeDay = 0;
			NextDiag.TempNode = "Tavern_again";
            SetQuestHeader("Pir_Line_1_JohnBolton");
            AddQuestRecord("Pir_Line_1_JohnBolton", "1");
			CloseQuestHeader("Pir_Line_0_Waiting");
			pchar.questTemp.piratesLine = "toJohnBolton";
			sld = GetCharacter(NPC_GenerateCharacter("QuestPirate2", "officer_4", "man", "man", 20, PIRATE, -1, true));
			sld.name = "Джон";
			sld.lastname = "Болтон";
			sld.rank = 20;
			sld.city = "PuertoPrincipe";
			sld.location	= "PuertoPrincipe_port";
			sld.location.group = "goto";
			sld.location.locator = "goto14";
			sld.dialog.filename   = "Quest\PiratesLine_dialog.c";
			sld.dialog.currentnode   = "JohnBolton";
			sld.greeting = "Gr_MiddPirate";
			sld.talker = 8; //начать диалог
			LAi_SetLoginTime(sld, 6.0, 21.99);
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			AddDialogExitQuestFunction("PiratesLine_q1_tavernEnd");
		break;

		case "Tavern_again":
			dialog.text = "Джон ждет тебя в бухте Пуэрто-Принсипе. Не тяни с этим!";
			link.l1 = "Хорошо...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tavern_again";
		break;
		case "Tavern_over":
			dialog.text = "Хм... Ну, как знаешь, "+ GetSexPhrase("приятель","подруга") +". Наше дело предложить, ваше дело - отказаться. Бывай...";
			link.l1 = "Прощай.";
			link.l1.go = "exit";
			npchar.lifeDay = 0;
			pchar.questTemp.piratesLine = "over";
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("PiratesLine_q1_tavernEnd");
		break;
		//базар с Джоном Болтоном в порту Пуэрто Принсипе
		case "JohnBolton":
			dialog.text = "Добрый день. Скажите, вы капитан " + GetFullName(pchar) + "?";
			link.l1 = "Да. А вы должно быть Джон Болтон?";
			link.l1.go = "JohnBolton_1";
		break;
		case "JohnBolton_1":
			dialog.text = "Да-да. И мне необходимо добраться до Порт-Рояля, и желательно побыстрее.";
			link.l1 = "Знаю, садитесь в шлюпку, судно готово.";
			link.l1.go = "JohnBolton_2";
		break;
		case "JohnBolton_2":
			AddQuestRecord("Pir_Line_1_JohnBolton", "2");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.quest.PiratesLine_q1_arrest.win_condition.l1 = "locator";
			pchar.quest.PiratesLine_q1_arrest.win_condition.l1.location = "PortRoyal_town";
			pchar.quest.PiratesLine_q1_arrest.win_condition.l1.locator_group = "quest";
			pchar.quest.PiratesLine_q1_arrest.win_condition.l1.locator = "detector_PQ1";
			pchar.quest.PiratesLine_q1_arrest.function = "PiratesLine_q1_arrest";
			NextDiag.TempNode = "JohnBolton_inWay";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "", 5.0);
		break;
		case "JohnBolton_inWay":
			dialog.text = "Мы еще не добрались до Порт Рояля, а я спешу, "+ GetSexPhrase("приятель","подруга") +"...";
			link.l1 = "Мы идем туда, не волнуйтесь.";
			link.l1.go = "exit";
			NextDiag.TempNode = "JohnBolton_inWay";
		break;
		//базар с арестовывающими солдерами
		case "ArrestInPR":
			dialog.text = "Поступил донос, что у вас на борту находится преступник Джон Болтон... Ба! Да вот он! Вы арестованы!";
			link.l1 = "Эй, приятель, а ты не ошибся? Я привез"+ GetSexPhrase("","ла") +" этого человека по поручению Генри Моргана!";
			link.l1.go = "ArrestInPR_1";
		break;
		case "ArrestInPR_1":
			dialog.text = "Комендант разберется, где ошибка, а где нет. Следуйте за мной!";
			link.l1 = "Вот чёрт...";
			link.l1.go = "ArrestInPR_2";
		break;
		case "ArrestInPR_2":
			AddQuestRecord("Pir_Line_1_JohnBolton", "3");
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Portroyal_town", "houseS1", false); //закроем дом Моргана
			DialogExit();
			AddDialogExitQuestFunction("PiratesLine_q1_toPrison");
		break;
		// -------------------------------------- квест №2 -------------------------------------------------
		case "EdwardLoy":
			dialog.text = "Ты ко мне, "+ GetSexPhrase("приятель","подруга") +"? Чем обязан?";
			link.l1 = "Тебе привет от Генри Моргана.";
			link.l1.go = "EdwardLoy_1";
		break;
		case "EdwardLoy_1":
			dialog.text = "...От Генри Моргана? И что понадобилось от меня Генри Моргану?";
			link.l1 = "Генри очень по тебе соскучился, просит навестить при случае.";
			link.l1.go = "EdwardLoy_2";
		break;
		case "EdwardLoy_2":
			dialog.text = "...Зачем это?";
			link.l1 = "Не знаю. Может решил включить тебя в своё завещание. А чтобы ты не сомневался в его искренности, велел передать тебе одну вещицу. Сказал, что ты её давно дожидаешься, да вот как-то недосуг было выбраться – порадовать тебя.";
			link.l1.go = "EdwardLoy_3";
			RemoveItems(PChar, "BlackLabel", 1);
		break;
		case "EdwardLoy_3":
			dialog.text = "Дьявол! Черная Метка. Я так и знал... А если я её не возьму?";
			link.l1 = "А если ты её не возьмёшь, то я засуну её тебе в глотку.";
			link.l1.go = "EdwardLoy_4";
		break;
		case "EdwardLoy_4":
			dialog.text = "Все! Достаточно! Ты сделал"+ GetSexPhrase("","а") +" свое подлое дело, теперь убирайся отсюда!";
			link.l1 = "Удачного тебе дня, Лоу... И если хочешь жить, поезжай к Моргану.";
			link.l1.go = "exit";
			NextDiag.TempNode = "EdwardLoy_again";
			QuestSetCurrentNode("Henry Morgan", "PL_Q2_away_1");
			AddQuestRecord("Pir_Line_2_BlackLabel", "3");
			AddQuestUserData("Pir_Line_2_BlackLabel", "sSex", GetSexPhrase("","а"));
		break;
		case "EdwardLoy_again":
			dialog.text = "Ты еще здесь?";
			link.l1 = "Уже ухожу...";
			link.l1.go = "exit";
			NextDiag.TempNode = "EdwardLoy_again";
		break;
		// -------------------------------------- квест №3 -------------------------------------------------
		case "CapGoodly":
			dialog.text = "Хо! Здорово, "+ GetSexPhrase("парень","деваха") +"! Вот, опять свиделись. Присаживайся, опрокинем по стаканчику.";
			link.l1 = "Здорово, Гудли! Тавернщик сказал, что ты разговаривал с Лоу.";
			link.l1.go = "CapGoodly_1";
		break;
		case "CapGoodly_1":
			dialog.text = "Верно, разговаривал. Заливал он мне, что работает по секретному поручению Моргана.";
			link.l1 = "Угу, по такому секретному, что Морган его по всем Карибам ищет... Он говорил куда собирается?";
			link.l1.go = "CapGoodly_2";
		break;
		case "CapGoodly_2":
			dialog.text = "Морган, говоришь, ищет?  Да нет, ничего такого он не говорил... Просто посидели – о жизни посплетничали.";
			link.l1 = "Сдается мне, друг Гудли, что ты, как в истории с Болтоном, опять чего-то недоговариваешь. Небось уже прикидываешь, сколько Морган отсыплет за голову Лоу? Так вот знай – я буду идти за тобой по пятам. А когда ты выведешь меня на Лоу, я кончу тебя первого, чтоб под ногами не путался.";
			link.l1.go = "CapGoodly_3";
		break;
		case "CapGoodly_3":
			dialog.text = "Да ладно! Какие между друзьями могут быть недомолвки?\nЯ только из Куманы вернулся, тамошние галеоны караулил. Ну, он спросил пару раз... Но я не уверен. ";
			link.l1 = "Ладно, не обижайся, пошутил"+ GetSexPhrase("","а") +" я. Ну что ж, пора мне. Найду Лоу – поделюсь с тобой, бывай.";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "13");
			pchar.questTemp.piratesLine = "KillLoy_toCumana";
			npchar.lifeDay = 0;
			pchar.quest.PiratesLine_q3_loginSeaWolf.win_condition.l1 = "location";
			pchar.quest.PiratesLine_q3_loginSeaWolf.win_condition.l1.location = "Cumana";
			pchar.quest.PiratesLine_q3_loginSeaWolf.function = "PiratesLine_q3_loginSeaWolf";
		break;
		//Эдвард Лоу в каюте Морского Волка
		case "SeaWolf":
			dialog.text = "Дьявол! Ты все-таки добрал"+ GetSexPhrase("ся","ась") +" до меня!";
			link.l1 = "А разве могло быть иначе?!";
			link.l1.go = "SeaWolf_1";
		break;
		case "SeaWolf_1":
			dialog.text = "Да что ты о себе возомнил"+ GetSexPhrase("","а") +"?! Думаешь, ты так"+ GetSexPhrase("ой","ая") +" всемогущ"+ GetSexPhrase("ий","ая") +"?! Ты прост"+ GetSexPhrase("ой порученец","ая наемница") +" Моргана, не более того!";
			link.l1 = "Эх Лоу, человек создан для счастья, а ему приходится постоянно работать. И сегодня ты – моя работа.";
			link.l1.go = "SeaWolf_2";
		break;
		case "SeaWolf_2":
			dialog.text = "Ну конечно! Сколько Морган пообещал тебе за меня? Я заплачу вдвое... втрое!";
			link.l1 = "Если это может потешить твоё самолюбие перед смертью, то Морган поставил за тебя пятьдесят тысяч.";
			link.l1.go = "SeaWolf_3";
		break;
		case "SeaWolf_3":
			dialog.text = "Послушай, " + GetFullName(PChar) + ", я дам тебе двести тысяч, только позволь мне уйти.";
			link.l1 = "Я понял"+ GetSexPhrase("","а") +", Лоу, почему Морган имеет на тебя зуб. Ты своей гнилой натурой не можешь понять, что жирный кусок сегодня может оказаться причиной голодной смерти завтра.";
			link.l1.go = "SeaWolf_4";
		break;
		case "SeaWolf_4":
			dialog.text = "Чего-о?! У Моргана на меня зуб?! Да ты знаешь, сколько пиратов точат зуб на него самого?! Кто его выбирал?! Ты?!\n" +
				"У Моргана на меня зуб! Ха-ха-ха! Да я облапошил его, как щенка! вот чего он не может мне простить! Этого самозванца бесит, что я сказал ему однажды, что его никто не выбирал, что я не стал лизать ему пятки, как делаете все вы!\nИ тебя он вышвырнет, словно котёнка, или утопит в лужице твоей же мочи, как только надобность в тебе отпадёт!";
			link.l1 = "Заткнись, Лоу! В своих делах с Морганом я разберусь сам"+ GetSexPhrase("","а") +", когда придёт время. И ты умрёшь не за пятьдесят тысяч. Ты умрёшь за свою подлость. Джекмен просил меня сделать это бесплатно... У меня есть какие-нибудь причины оставить тебе жизнь?";
			link.l1.go = "SeaWolf_5";
		break;
		case "SeaWolf_5":
			dialog.text = "Ха! Представляю рожу Джекмена, когда он узнал, что бриг его - тю-тю...";
			link.l1 = "Представил? Ну, тогда с Богом...";
			link.l1.go = "SeaWolf_6";
		break;
		case "SeaWolf_6":
			LAi_SetCurHPMax(npchar);
            QuestAboardCabinDialogExitWithBattle("");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		// -------------------------------------- квест №5 -------------------------------------------------
		case "PQ5CapGoodly":
			dialog.text = "Здорово, "+ GetSexPhrase("приятель","подруга") +"! Очень хорошо, что я тебя застал! Если не торопишься, давай поговорим. У меня к тебе опять дело, выручай.";
			link.l1 = "Здорово. Узнаю старину Гудли - как всегда проблемы. Что ж, выкладывай, что за дело?";
			link.l1.go = "PQ5CapGoodly_1";
		break;
		case "PQ5CapGoodly_1":
			dialog.text = "Не буду ходить вокруг да около, дело у меня вот какое.\nКак ты понимаешь, я работаю на Моргана. Но помимо этой работы у меня есть и другая, основная. Я - охотник за головами. До сей поры мне удавалось совмещать дела Моргана и основную работу, но сейчас, увы, не получилось. Ко мне с заказом обратился человек, которому я не могу отказать...";
			link.l1 = "А что, нельзя отложить, перенести? Что за спешка такая? Глядишь, и человек бы пожил ещё немного, ха-ха-ха...";
			link.l1.go = "PQ5CapGoodly_3";
		break;
		// Warship 13.07.09 Нуту этого
		/*case "PQ5CapGoodly_2":
			dialog.text = "Проблема в том, что Моргану я сейчас нужен в Порт-Рояле, и он не хочет меня отпускать. Выполнить заказ нет никакой возможности... Короче, возьмешь мой заказ?";
			link.l1 = "А отказаться ты не можешь?";
			link.l1.go = "PQ5CapGoodly_3";
		break;*/
		case "PQ5CapGoodly_3":
			dialog.text = "Если б все решалось так просто, я бы тебя не просил. Решайся. Всю награду от заказчика заберешь себе.";
			link.l1 = "Хм, неплохой стимул. Пожалуй, стоит согласиться. Давай-ка поподробней, что за заказ?";
			link.l1.go = "PQ5CapGoodly_4";
		break;
		case "PQ5CapGoodly_4":
			dialog.text = "Нужно убрать человека по имени Джон Эйвори. Он подвизается, вытрясая долги для ростовщиков. Хороший боец, неплохо стреляет. Наглая скотина, что, впрочем, не мешает ему находить клиентов\n"+
				"Последний раз его видели в Виллемстаде. Не знаю, где он перебежал дорожку заказчику, но тот назначил награду за голову Джона 15 тысяч.";
			link.l1 = "Гудли, ты что думаешь, я за такие гроши буду выполнять чужую работу?! Или ты решил прикарманить большую половину гонорара, или твой заказчик редкая скотина. Скажи мне кто он, и я выбью из него другие условия.";
			link.l1.go = "PQ5CapGoodly_5";
		break;
		case "PQ5CapGoodly_5":
			dialog.text = "Извини, "+ GetSexPhrase("дружище","подруга") +", вот этого я тебе не скажу. Заказчику это не понравится.";
			link.l1 = "Вот скажи мне, Гудли, что у тебя за манера такая? Опять какой-то 'человек', 'не могу отказать', 'заказчику не понравится'... Ты что, меня за салагу держишь?";
			link.l1.go = "PQ5CapGoodly_6";
		break;
		case "PQ5CapGoodly_6":
			dialog.text = "Да не горячись ты опять! Если хочешь знать, то при доставке Болтона Морган сам просил, чтоб я не посвящал во все тонкости новичка. Он человека надёжного искал... и как видно, нашёл... Ну, так что, возьмёшь мой заказ?";
			link.l1 = "А ты умеешь подольститься. Но учти – только ради тебя, и только за пятьдесят тысяч. ";
			link.l1.go = "PQ5CapGoodly_7";
		break;
		case "PQ5CapGoodly_7":
			dialog.text = "Черт с тобой. Я доплачу своими деньгами. Просто я не могу отказать этому человеку.\n Желаю тебе удачи. Я буду ждать в городе.";
			link.l1 = "Хех. Нет, чтобы прямо сказать: " + PChar.Name + ", это для МЕНЯ надо убрать Эйвори. Так нет же, выдумал какого-то заказчика. И, Гудли: если попробуешь меня надуть –  следующим станешь сам... Счастливо оставаться!";
			link.l1.go = "PQ5CapGoodly_8";
		break;
		case "PQ5CapGoodly_8":
			chrDisableReloadToLocation = false;
			pchar.questTemp.piratesLine = "PL5Hunter_toVillemstad";
			SetQuestHeader("Pir_Line_5_Hunter");
			AddQuestRecord("Pir_Line_5_Hunter", "1");
			AddQuestUserData("Pir_Line_5_Hunter", "sSex", GetSexPhrase("к","ца"));
			LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorGoToLocation(NPChar, "reload", "houseS1", "none", "", "", "", -1.0);
			DialogExit();
		break;
		//Эйвори вместо ГГ
		case "PQ5Hero":
			dialog.text = "...деньги! И давай по-хорошему, а не то мой тесак попробует твою кровь на вкус!";
			link.l1 = "Ха! Хочешь забрать?!! Шиш тебе! Это моя добыча!!!";
			link.l1.go = "PQ5Hero_1";
		break;
		case "PQ5Hero_1":
            DialogExit();
			AddDialogExitQuestFunction("PQ5_afterChangeMainHero");
		break;
		//Эйвори в доме на Бермудах
		case "PQ5Aivory":
			dialog.text = "Тебя не звали! Вали отсюда, пока отпускаю!";
			link.l1 = "Джентльмены, возможно вы будете удивлены, но у меня заказ на вас обоих. Так что предъявите ваши аргументы.";
			link.l1.go = "PQ5Aivory_1";
		break;
		case "PQ5Aivory_1":
			dialog.text = "Ха!! И еще говорят, что я наглец. Ну, проверим сейчас, кто ты есть...";
			link.l1 = "Проверим...";
			link.l1.go = "PQ5Aivory_2";
		break;
		case "PQ5Aivory_2":
            DialogExit();
			AddDialogExitQuestFunction("PQ5_afterChangeMainHero2");
		break;
		//Гудли в таверне Порт Рояля
		case "PQ5CapGoodlyEnd":
			dialog.text = "Кого я вижу, " + GetFullName(pchar) + "! Все-таки вернул"+ GetSexPhrase("ся","ась") +"! А я уже, признаться, заждался...";
			link.l1 = "Да, поиски продлились несколько дольше, чем я ожидал"+ GetSexPhrase("","а") +". Зато закончились успешно!";
			link.l1.go = "PQ5CapGoodlyEnd_1";
		break;
		case "PQ5CapGoodlyEnd_1":
			dialog.text = "Ха! Ты несказанно меня обрадовал"+ GetSexPhrase("","а") +"! Гора с плеч свалилась.\nИзвини, всю сумму еще не собрал, пока только 15 тысяч, остальные заплачу чуть позже... Будь уверен"+ GetSexPhrase("","а") +", не обману, мне не нужен враг в твоем лице.";
			link.l1 = "Хорошо, что ты это понимаешь. Ладно, давай что есть, и собирай остальное.";
			link.l1.go = "PQ5CapGoodlyEnd_2";
			AddMoneyToCharacter(pchar, 15000);
		break;
		case "PQ5CapGoodlyEnd_2":
			dialog.text = "Соберу, не переживай. А ведь такое дело здорово прибавит тебе популярности среди пиратов, хе-хе...";
			link.l1 = "Хм, с чего бы это? И вообще, Гудли, с какой стати тебе так радоваться?";
			link.l1.go = "PQ5CapGoodlyEnd_3";
		break;
		case "PQ5CapGoodlyEnd_3":
			dialog.text = "С чего? Завалить такого бойца, как Эйвори - задача непростая. И чего мне не радоваться, если заказ мой выполнен.\nДа, чуть не забыл: тебя Морган видеть хотел. Так что поторопись.";
			link.l1 = "Морган? А зачем я ему понадобил"+ GetSexPhrase("ся","ась") +", не в курсе?";
			link.l1.go = "PQ5CapGoodlyEnd_4";
		break;
		case "PQ5CapGoodlyEnd_4":
			dialog.text = "Нет, не в курсе. Мне он отчета не дает. Так что, за всеми ответами к нему.";
			link.l1 = "Хм, ну хорошо, сейчас схожу... И чего это ты опять улыбаешься, будто у тебя не все дома?";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_5_Hunter", "12");
			sld = characterFromId("Henry Morgan");
			LAi_SetHuberTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "PortRoyal_houseS1", "sit", "sit2");
			QuestSetCurrentNode("Henry Morgan", "PL_Q5_begin");
		break;
		// -------------------------------------- квест №6 -------------------------------------------------
		case "JohnLids":
			dialog.text = "Приветствую члена Берегового Братства! Чем обязан удвольствием видеть вас на моей палубе?";
			link.l1 = "Здравствуй, Джон. Меня послал к тебе Джекмен.";
			link.l1.go = "JohnLids_1";
		break;
		case "JohnLids_1":
			dialog.text = "Очень хорошо. А как твое полное имя?";
			link.l1 = GetFullName(pchar) + ".";
			link.l1.go = "JohnLids_2";
		break;
		case "JohnLids_2":
			dialog.text = "Ха!! Не может быть! А тогда кого мы заперли в этой бухте?";
			link.l1 = "Понятия не имею. Именно я и есть " + GetFullName(PChar) +  ". Да что ты крутишь всё вокруг да около? Рассказывай в чем дело. Кого вы заперли?";
			link.l1.go = "JohnLids_3";
		break;
		case "JohnLids_3":
			dialog.text = "Началось все с того, что шхуну бедняги Сида Боннета захватил"+ GetSexPhrase("","а") +" на корвете некий капер по имени " + GetFullName(pchar) + ". Может, "+ GetSexPhrase("твой брат двоюродный","твоя сестра двоюродная") +", не знаю\n"+
				"Боннета он"+ GetSexPhrase("","а") +" сдал"+ GetSexPhrase("","а") +" испанцам, а те тут же повесили его на городской площади Гаваны. В общем, печальный конец для пирата, никому не пожелаешь...";
			link.l1 = "Ну а дальше, что там с мо"+ GetSexPhrase("им однофамильцем","ей однофамилицей") +"?";
			link.l1.go = "JohnLids_4";
		break;
		case "JohnLids_4":
			dialog.text = "Мы нагнали е"+ GetSexPhrase("го","е") +" прямо здесь. Корвет пустили на дно, но команда с тонущего корабля сумела высадиться на берег.\nОдними лишь абордажниками тут вопрос не решить: эти черти хорошо вооружены и многочисленны, а высадка всей командой в этой бухту очень неудобна. Да и мои ребята не слишком рвутся в бой - Сида уже не вернёшь, а поживиться с этих сухопутных всё равно нечем. Знаешь ли, подыхать задаром никому не охота.";
			link.l1 = "И что ты предлагаешь?";
			link.l1.go = "JohnLids_5";
		break;
		case "JohnLids_5":
			dialog.text = "Ну, мне кажется, что именно тебе само"+ GetSexPhrase("му","й") +" надо разобраться со сво"+ GetSexPhrase("им","ей") +" родственни"+ GetSexPhrase("ком","цей") +". Иначе, сам"+ GetSexPhrase("","а") +" понимаешь, проблем у тебя будет чем дальше, тем больше.\n"+"Дело в том, что в моей команде есть люди, которые знают тебя в лицо. Так вот, они твердо уверены, что на корвете именно ты и есть... Вот так-то, "+ GetSexPhrase("приятель","подруга") +"!";
			link.l1 = "Да уж, час от часу не легче. Но может быть, все-таки поможешь мне людьми?";
			link.l1.go = "JohnLids_6";
		break;
		case "JohnLids_6":
			dialog.text = "Только тем, что покараулю здесь эту братию, если тебе нужно куда-то отлучиться.";
			link.l1 = "Ну ладно, придется, видать, само"+ GetSexPhrase("му","й") +" разговаривать со сво"+ GetSexPhrase("им","ей") +" родственни"+ GetSexPhrase("чком","цей") +".";
			link.l1.go = "JohnLids_7";
		break;
		case "JohnLids_7":
			dialog.text = "Ну, вот и славно. Приступай, "+ GetSexPhrase("дружище","подруга") +". Мне очень интересно, чем все закончится...";
			link.l1 = "Хе-х, ты будешь смеяться, но мне тоже.";
			link.l1.go = "exit";
			NextDiag.TempNode = "JohnLids_again";
			SetQuestHeader("Pir_Line_6_Jackman");
			AddQuestRecord("Pir_Line_6_Jackman", "3");
			AddQuestUserData("Pir_Line_6_Jackman", "sSex", GetSexPhrase("мой однофамилец","моя однофамилица"));
			AddQuestUserData("Pir_Line_6_Jackman", "sSex1", GetSexPhrase("ий","ая"));
			Pchar.quest.PQ6_ShoreBattle.win_condition.l1 = "location";
			Pchar.quest.PQ6_ShoreBattle.win_condition.l1.location = "Shore7";
			Pchar.quest.PQ6_ShoreBattle.function = "PQ6_ShoreBattle";
		break;
		case "JohnLids_again":
			dialog.text = "Ты еще не покончил"+ GetSexPhrase("","а") +" со сво"+ GetSexPhrase("им","ей") +" "+ GetSexPhrase("'братом'","'сестрой'") +", а я вечно ждать тебя не буду...";
			link.l1 = "Я понял"+ GetSexPhrase("","а") +", Джон...";
			link.l1.go = "exit";
			NextDiag.TempNode = "JohnLids_again";
		break;
		//двойник ГГ
		case "QuestPirateHead":
			dialog.text = "Ха, так ты и есть " + GetFullName(pchar) + "! Рад"+ GetSexPhrase("","а") +" тебя видеть, "+ GetSexPhrase("братишка","сестренка") +"...";
			link.l1 = "Как"+ GetSexPhrase("ой","ая") +" я тебе "+ GetSexPhrase("братишка","сестренка") +"?!";
			link.l1.go = "QuestPirateHead_1";
		break;
		case "QuestPirateHead_1":
			dialog.text = "Ну, это я так, по-дружески... Так что? Ты всё-таки решил"+ GetSexPhrase("","а") +" от меня избавиться?";
			link.l1 = "Давай, рассказывай. Кто ты, откуда...";
			link.l1.go = "QuestPirateHead_2";
		break;
		case "QuestPirateHead_2":
			dialog.text = "А ты дашь нам уйти?";
			link.l1 = "Конечно! Так рука об руку и пойдём – "+ GetSexPhrase("два брата-акробата!","две девицы - две сестрицы!") +"";
			link.l1.go = "QuestPirateHead_3";
		break;
		case "QuestPirateHead_3":
			dialog.text = "Хм, а ты шутни"+ GetSexPhrase("к","ца") +". Тогда какой смысл трепаться?";
			link.l1 = "Аргх!! Ну, раз ты торопишься...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("PQ6_JungleBattle");
		break;
		// -------------------------------------- квест №7 -------------------------------------------------
		case "FriendLinney":
			dialog.text = "Рад видеть вас у себя на палубе.";
			link.l1 = "Я ищу Стива Линнея, говорят, вы с ним приятели, вас видели вместе в таверне.";
			link.l1.go = "FriendLinney_1";
		break;
		case "FriendLinney_1":
			dialog.text = "Хм, может и приятели…";
			link.l1 = "Меня зовут " + GetFullName(pchar) + ", я выполняю поручение Моргана. Стив долго не возвращался, а поскольку он собирал сведения для Моргана, Генри послал меня выяснить его судьбу.";
			link.l1.go = "FriendLinney_2";
		break;
		case "FriendLinney_2":
			dialog.text = "А-а, ну так бы сразу и сказал"+ GetSexPhrase("","а") +". Я давно знаю Стива, и сейчас он рассказал мне о поручении Моргана. В общем, в Ла Веге он ничего не разузнал. Он должен был здесь встретиться с одним человеком, который якобы что-то знает, но человек на встречу не явился. Стив планировал уже уходить в другой город, но вечером к нему подошли два неизвестных мне человека. Они переговорили, и Стив ушел с ними.\n"+"Понимаешь, и все бы ничего. Мало ли, может, он новых информаторов нашел, но вчера я случайно узнал, что его шхуна 'Ласточка' продается на верфи Санто-Доминго. А Стив свою 'Ласточку' очень любил и сам бы ни за что не продал. Вот я и подумал, что пора уходить с Ла Веги от греха подальше. Иначе можно дождаться, что и за мной придут.";
			link.l1 = "Понятно. Может, все-таки продал? Хотя, странно все это...";
			link.l1.go = "FriendLinney_3";
		break;
		case "FriendLinney_3":
			dialog.text = "Нет, не продал бы. Ты его просто не знаешь... Я вызвался ему помогать, но теперь уж и не знаю, что делать.";
			link.l1 = "Хорошо, я понял"+ GetSexPhrase("","а") +". Спасибо за информацию, дружище.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendLinney_again";
			pchar.questTemp.piratesLine = "Soukins_toSantoDomingo";
			AddQuestRecord("Pir_Line_7_Soukins", "5");
		break;
		case "FriendLinney_again":
			dialog.text = "Поговорили уже о Стиве, больше я ничего не знаю...";
			link.l1 = "Да-да, конечно.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendLinney_again";
		break;
		//кэп, продавшие шлюп Ласточку
		case "LeonCapitain":
			dialog.text = "Что тебе нужно от меня?";
			link.l1 = "Где капитан 'Ласточки'?!";
			link.l1.go = "LeonCapitain_1";
		break;
		case "LeonCapitain_1":
			dialog.text = "Капитан 'Ласточки' уже на дне, больно любопытный был. Ха-ха-ха!";
			link.l1 = "Дьявол!!! На кого ты работаешь?! Кто приказал тебе убрать Линнея?!";
			link.l1.go = "LeonCapitain_2";
		break;
		case "LeonCapitain_2":
			dialog.text = "Я работаю на адмирала Берегового Братства. Не на этого самозванца Моргана, а на нашего адмирала Ричарда Соукинса! Присоединяйся к нам, если не хочешь последовать за Линнеем.";
			link.l1 = "У меня нет причин не считать Генри Моргана адмиралом.";
			link.l1.go = "LeonCapitain_3";
		break;
		case "LeonCapitain_3":
			dialog.text = "А кто его выбирал? Может, ты?!";
			link.l1 = "Но твоего адмирала Скунса я тоже не выбирал"+ GetSexPhrase("","а") +"!";
			link.l1.go = "LeonCapitain_4";
		break;
		case "LeonCapitain_4":
			dialog.text = "Мы оба - пираты, и ни один из нас не выбирал Моргана адмиралом. Подумай над этим. А Морган – слишком шустр, при этом он далеко не так честен с нами, как об этом принято думать.";
			link.l1 = "Да мне плевать на твои рассуждения! Твой честный Соукинс, уже дважды пытался меня убрать чужими руками! А когда понял, что я ему не по зубам, решил переманить? Да он обычная крыса, мелкий интриган, возомнивший себя адмиралом!";
			link.l1.go = "LeonCapitain_5";
		break;
		case "LeonCapitain_5":
			dialog.text = ""+ GetSexPhrase("Идиот","Дура") +"! Ты еще пожалеешь о своей глупости...";
			link.l1 = "Не тебе судить о моей глупости!..";
			link.l1.go = "LeonCapitain_6";
		break;
		case "LeonCapitain_6":
			Map_ReleaseQuestEncounter("LeonCapitain");
			pchar.questTemp.piratesLine = "Soukins_toMorgan";
			QuestSetCurrentNode("Henry Morgan", "PL_Q7_afterLeon");
			AddQuestRecord("Pir_Line_7_Soukins", "7");
			AddQuestUserData("Pir_Line_7_Soukins", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("Pir_Line_7_Soukins", "sSex1", GetSexPhrase("ся","ась"));
			LAi_SetCurHPMax(npchar);
            QuestAboardCabinDialogExitWithBattle("");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//поход на Панаму, пираты в городе
		case "PQ8_PirInPan":
			dialog.text = "Знаешь, " + pchar.name + ", не зря я пошел к тебе в команду. В итоге я жив, да еще в захваченной Панаме! Кто бы мог подумать?..";
			link.l1 = "Да уж, на этом деле мы должны прилично заработать.";
			link.l1.go = "PQ8_PirInPan_1";
		break;
		case "PQ8_PirInPan_1":
			dialog.text = "Уже ищем, что бы прихватить!";
			link.l1 = "И это правильно.";
			link.l1.go = "exit";
		break;
		case "PQ8_RsPirInPan":
			dialog.text = "Эх, жаль наш капитан погиб! Славный был человек Ричард Соукинс...";
			link.l1 = "Ты думаешь?";
			link.l1.go = "PQ8_RsPirInPan_1";
		break;
		case "PQ8_RsPirInPan_1":
			dialog.text = "Конечно! Я прослужил под его началом больше года. Он был справедливым человеком!";
			link.l1 = "Хм, понятно...";
			link.l1.go = "exit";
		break;
		case "PQ8_MPirInPan":
			dialog.text = "Я слышал, вам тоже досталось на орехи! Мы с Морганом шли к Панаме из Порто Белло.";
			link.l1 = "Да уж, на каждом шагу нас ждали засады испанцев.";
			link.l1.go = "PQ8_MPirInPan_1";
		break;
		case "PQ8_MPirInPan_1":
			dialog.text = "У нас было то же самое, форменный ад...";
			link.l1 = "Но главное, что мы справились с этим и живы. Так что, не вешай нос!";
			link.l1.go = "exit";
		break;
		//фантом мэра Панамы
		case "PQ8_Mayor":
			dialog.text = "Что хотите от меня?";
			link.l1 = "Здравствуйте, уважаемый. Насколько я понимаю, вы являетесь губернатором Панамы...";
			link.l1.go = "PQ8_Mayor_1";
		break;
		case "PQ8_Mayor_1":
			dialog.text = "Именно так.";
			link.l1 = "Я хочу, чтобы вы отдали мне золото Эскориала. Я знаю, что оно у вас.";
			link.l1.go = "PQ8_Mayor_2";
		break;
		case "PQ8_Mayor_2":
			dialog.text = "Хм, ну поищите...";
			link.l1 = "Вы играете с огнем! Панаму взял Генри Морган, здесь вообще собрался весь цвет карибского пиратства. Вы представляете себе, что с вами будет?";
			link.l1.go = "PQ8_Mayor_3";
		break;
		case "PQ8_Mayor_3":
			dialog.text = "Представляю. Но я ничем не могу помочь в любом случае. Все дело в том, что у меня нет ключа от сундука, в котором, возможно, и находится кое-что... Я говорю об одном из сундуков, находящихся в этом кабинете.";
			link.l1 = "И где этот ключ?";
			link.l1.go = "PQ8_Mayor_4";
		break;
		case "PQ8_Mayor_4":
			dialog.text = "Он всегда находится у коменданта. Этот сундук всегда был под контролем военных, а не гражданских властей города.";
			link.l1 = "Где комендант сейчас?";
			link.l1.go = "PQ8_Mayor_5";
		break;
		case "PQ8_Mayor_5":
			dialog.text = "Понятия не имею. Он руководил обороной города. Насколько мне известно, он должен был атаковать ладронов со стороны форта. Необходимо было не допустить захвата Панамы, поэтому форт никто не защищал.\n"+
				"Так что, может быть, он убит, а, может быть, находится у себя в форте.";
			link.l1 = "Имейте в виду, что от успешного вскрытия этого сундука зависит ваша жизнь.";
			link.l1.go = "PQ8_Mayor_6";
		break;
		case "PQ8_Mayor_6":
			dialog.text = "Я понимаю. Но мне остается надеяться только на удачу.";
			link.l1 = "Я поищу ключ. А вам я рекомендую напрячь память - возможно вы еще что-нибудь вспомните...";
			link.l1.go = "PQ8_Mayor_7";
		break;
		case "PQ8_Mayor_7":
			dialog.text = "Если меня что-либо озарит, то вы узнаете об этом непременно. Это в моих интересах.";
			link.l1 = "Хорошо.";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_8_Panama", "11");
			pchar.quest.PQ8_MorganInPanama_1.win_condition.l1 = "location";
			pchar.quest.PQ8_MorganInPanama_1.win_condition.l1.location = "Panama_town";
			pchar.quest.PQ8_MorganInPanama_1.function = "PQ8_MorganInPanama_1";
		break;
		//обманутые пиратусы в Панаме
		case "PQ8_FackMorgan":
			dialog.text = LinkRandPhrase("Дьявол, Генри обманул нас!", "Ты слышал"+ GetSexPhrase("","а") +", что сделал Морган?! Это просто уму непостижимо...", "Теперь нам здесь конец, надо выбираться отсюда как-нибудь. Теперь каждый сам за себя...");
			link.l1 = LinkRandPhrase("Да, я слышал"+ GetSexPhrase("","а") +"...", "Черт!!!", "Разрази меня гром!");
			link.l1.go = "exit";
		break;
		//первый подбегающий пират
		case "PL_Q8_QFackMorgan":
			dialog.text = "Ты как нельзя вовремя, капитан! Жаль, что тебя тут не было чуть раньше...";
			link.l1 = "Что случилось?";
			link.l1.go = "PL_Q8_QFackMorgan_1";
		break;
		case "PL_Q8_QFackMorgan_1":
			dialog.text = "Ха!! Я тебя сейчас так обрадую, что ты от радости с ума сойдешь!";
			link.l1 = "Говори по существу, не тяни.";
			link.l1.go = "PL_Q8_QFackMorgan_2";
		break;
		case "PL_Q8_QFackMorgan_2":
			dialog.text = "Наш адмирал, Генри Морган, собрал со всех нас добычу! Он построил пиратов и первым очистил свои карманы в общий котел!";
			link.l1 = "Ну и что, это мне было известно. Что в этом чрезвычайного?";
			link.l1.go = "PL_Q8_QFackMorgan_3";
		break;
		case "PL_Q8_QFackMorgan_3":
			dialog.text = "В этом - ничего, но только это еще не все новости... Мы все выложили содержимое своих кошельков и пошли заниматься своими делами в ожидании, когда Генри все поделит по закону Берегового Братства. А в это время наш доблестный и честнейший адмирал тихо погрузился в испанский галеон и отдал концы.";
			link.l1 = "Как?.. А деньги?!";
			link.l1.go = "PL_Q8_QFackMorgan_4";
		break;
		case "PL_Q8_QFackMorgan_4":
			dialog.text = "Наши деньги тоже отдали концы вместе с Морганом! Я же тебе о чем и толкую - Генри прихватил всю добычу и бросил нас здесь, в этой чертовой Панаме!";
			link.l1 = "Не может быть... Но этого просто не может быть!..";
			link.l1.go = "PL_Q8_QFackMorgan_5";
		break;
		case "PL_Q8_QFackMorgan_5":
			dialog.text = "Ха! Это факт, капитан! Что теперь делать?";
			link.l1 = "Дьявол!! Я конечно подозревал"+ GetSexPhrase("","а") +", что Морган не такой честный, каким хочет казаться, но чтобы вот так бросить свою армию в пустом городе без добычи и продовольствия!..";
			link.l1.go = "PL_Q8_QFackMorgan_6";
		break;
		case "PL_Q8_QFackMorgan_6":
			dialog.text = "Эх, был бы Соукинс жив - ничего подобного не было бы точно! Какой был капитан, настоящий адмирал!\nДьявол, сколько раз Ричард говорил, что Морган нас предаст. А мы все не слушали, медлили...";
			link.l1 = "Что значит - медлили?";
			link.l1.go = "PL_Q8_QFackMorgan_7";
		break;
		case "PL_Q8_QFackMorgan_7":
			dialog.text = "То и значит! Соукинс претендовал на должность адмирала Берегового Братства, но мы уговорили его не торопиться с выборами. Каррамба, как же мы ошибались!";
			link.l1 = "Что ваш Соукинс, что наш Морган, один другого стоил...";
			link.l1.go = "PL_Q8_QFackMorgan_8";
		break;
		case "PL_Q8_QFackMorgan_8":
			dialog.text = "Да уж, вы с Морганом жили душа в душу. Не думал, что он и тебя бросит здесь...";
			link.l1 = "Ну это мы ещё посмотрим!! Как назывался галеон, на котором ушёл Морган?";
			link.l1.go = "PL_Q8_QFackMorgan_9";
		break;
		case "PL_Q8_QFackMorgan_9":
			dialog.text = "Не помню точно. То ли 'Фортуна', то ли 'Колесо Фортуны'... Да брось ты, не найти тебе его. Не иначе в Европу подался, а то и в Индию...\nВсё, нет адмирала! Был, да весь вышел!";
			link.l1 = "Каррамба!! Всё равно торчать здесь без толку. Нужно собрать людей, поделить порох, пули и провиант, и идти через джунгли в Дарьенский залив к своим кораблям.";
			link.l1.go = "PL_Q8_QFackMorgan_10";
		break;
		case "PL_Q8_QFackMorgan_10":
			dialog.text = "Опять через джунгли? Нет уж, второго такого похода я не переживу. А с тобой никто и не пойдет: "+ GetSexPhrase("вы же с Морганом друзья!","все уверены, что ты Моргану... это... ну, подруга.") +" А если ты заикнешься о том, чтобы что-то собрать – уверен, что сразу получишь пулю в лоб! Теперь каждый сам за себя, капитан... Ну ладно, некогда мне тут с тобой лясы точить. Пойду в таверну, надеюсь, там еще остался ром...";
			link.l1 = "Ну иди, иди. А мне здесь торчать смысла нет.";
			link.l1.go = "PL_Q8_QFackMorgan_11";
		break;
		case "PL_Q8_QFackMorgan_11":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("PortRoyal_houseS1")], true);
			SetTimerFunction("PQ8_openPanama_2", 0, 0, 30);
			pchar.questTemp.piratesLine = "Panama_backToShip";
			AddQuestRecord("Pir_Line_8_Panama", "13");
			Pchar.quest.PL_Q8_backFight_1.win_condition.l1 = "location";
			Pchar.quest.PL_Q8_backFight_1.win_condition.l1.location = "Panama_jungle_04";
			Pchar.quest.PL_Q8_backFight_1.function = "PL_Q8_backFight_1";
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload4", "none", "", "", "", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
