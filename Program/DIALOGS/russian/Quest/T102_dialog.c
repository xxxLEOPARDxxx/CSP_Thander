//мумия в алькове
void ProcessDialogEvent()
{
	ref NPChar, PChar, d;
	PChar = GetMainCharacter();
	aref Link, Diag;
	string NPC_Meeting;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

        case "First time":
			dialog.text = "... (скелет отнимает металлическую руку и с лязгом вставляет себе на место, рука начинает шевелиться)";
			link.l1 = "Что такое?!";
			link.l1.go = "Term_1";
			TakeNItems(Pchar, "term_arm", -1);
			LAi_CharacterPlaySoundAtOnce(NPChar, "T102_Intro");
		break;

		case "Term_1":
			dialog.text = "Я - киборг марки Т-102, производства 'Скайнет продакшн', анклава Детройт, выпуск 2022 года. Я настиг тебя, человек со странного корабля.";
			link.l1 = "Кто? Чего? Какой еще Ки Борг? Какого года? На дворе семнадцатый век от рождества Христова! Ты - нечисть! Только почему-то металлическая, что странно.";
			link.l1.go = "Term_2";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_1");
			if(startherotype == 2)
			{
				link.l1 = "'Скайнет продакшн'? Никогда не слышала о такой корпорации. Проклятье, кажется своими действиями здесь я нарушила временную последовательность, чем породила альтернативное будущее. Скажи мне, известно ли тебе что-то о корпорации Omnitech? Кажется, в 2022 году она уже существовала.";
				link.l1.go = "Whisper_Term_2";
			}

		break;

		case "Whisper_Term_2":
			dialog.text = "В моей базе данных нет совпадений по этому запросу.";
			link.l1 = "Проклятье! Это очень плохо. В любом случае, что ты делаешь в этом времени?";
			link.l1.go = "Term_3";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_2");
		break;

		case "Term_2":
			dialog.text = "Не спорь со мной, биологический индивид, идентифицирующий себя как " +GetFullName(pchar) +
			              ". Я - машина с биологическим покрытием, киборг. Покрытие имело меньший срок службы, чем основная база из сплава металлических полимеров. За 170 лет биопокров был утерян. Мой ресурс на пределе. Ядерный источник питания сел, работаю на резерве.";
			link.l1 = "Полтора века? Тогда я не понял"+ GetSexPhrase("","а") +", когда тебя породили - в 15-м веке или же в 21-м?";
			link.l1.go = "Term_3";
			if (startherotype > 0 && startherotype < 12) LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_3_"+startherotype);
			else LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_3_unknown");
		break;

		case "Term_3":
			dialog.text = "Error. Main power is too low. Critical error - restarting....";
			link.l1 = "Чего?";
			link.l1.go = "Term_4";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_4");
		break;

		case "Term_4":
			dialog.text = "Loading from backup store....";
			link.l1 = "Что это с ним? Любезный, вы с кем сейчас говорите? Я вообще с нечистью не говорю, тут исключение делаю, а он!";
			if(startherotype == 2)
			{
				link.l1 = "Похоже, он на ладан дышит, вот-вот развалится. Эй, ты здесь?";
			}
			link.l1.go = "Term_5";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_5");
		break;

		case "Term_5":
			dialog.text = "System ready.......  Я - киборг марки Т-102, производства 'Скайнет продакшн', анклава Детройт, выпуск 2022 года.";
			link.l1 = "Это я уже слышал"+ GetSexPhrase("","а") +"! Не зли меня, тупая железка!";
			link.l1.go = "Term_6";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_6");
		break;

		case "Term_6":
			dialog.text = "Моя миссия была - отправиться в прошлое, год - 1985-й, цель - Сара Коннор, уничтожение.";
			link.l1 = "А у нас сейчас " + GetDataYear() + "-й год! И нет тут никакой Сары.";
			if(startherotype == 2)
			{
				link.l1 = "Сильно же ты промахнулся с годом, прямо как я.";
			}
			link.l1.go = "Term_7";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_7");
		break;

		case "Term_7":
			dialog.text = "При отправке не были учтены искажения, наводимые оружием и обмундированием. Произошел сбой времяопределения. Доставка в конец 15-го века. Основная задача - выполнение миссии. Поиск не дал результатов.";
			link.l1 = "Допустим, а я тут причем?";
			link.l1.go = "Term_8";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_8");
		break;

		case "Term_8":
			dialog.text = "Составная часть базы - манипулятор. Манипулятор имеет маркер - ты взял"+ GetSexPhrase("","а") +" его. Манипулятор был утерян в ходе операции 'I'll be back', проводимой на странном корабле 30 лет назад. Неидентифицируемые обитатели корабля, отсутствующие в каталоге базы данных идентификаций, оказались агрессивными, но плохоуничтожимыми объектами. Определение - киборги с биологической основой, источник энергии - неизвестен.";
			link.l1 = "А-а-а, это на корабле-призраке, что ли? Ясно дело, они сами - как ты, только их больше, вот и закидали шапками! Я тоже от них натерпел"+ GetSexPhrase("ся","ась") +" уже, не первый раз.";
			if(startherotype == 2)
			{
				link.l1 = "А-а-а, это ты о корабле-призраке, что ли? Я тоже от него натерпел"+ GetSexPhrase("ся","ась") +" уже, не первый раз.";
			}
			link.l1.go = "Term_9";
			if (pchar.sex != "woman") LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_9_man");
			else LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_9_woman");
		break;

		case "Term_9":
			dialog.text = "Теперь манипулятор интегрирован и функционирует корректно. Ранее он был недоступен в силу водной преграды и постоянной передислокации.";
			link.l1 = "Кто куда корректно что?";
			link.l1.go = "Term_9_1";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_10");
		break;

		case "Term_9_1":
			dialog.text = "Несущественно.";
			link.l1 = "А-а, так операция 'I'll be back' - это просто драпать? Или, как я говорю, совершить маневр стратегического отдаления от неприятеля.";
			link.l1.go = "Term_9_2";
		break;

		case "Term_9_2":
			dialog.text = "Да, индивид '" +GetFullName(pchar) +"', ты прав"+ GetSexPhrase("","а") +". Мое время истекает с разрядом резервной батареи. Миссия не может быть выполнена, объект не обнаружен, генетический анализ показал отсутствие ближайших предков цели в этом ареале.";
			link.l1 = "Да, не повезло тебе. Пора, видимо, на покой. Где взять хорошее оружие, я уже понял"+ GetSexPhrase("","а") +". Если встречу Сару о'Конер, обязательно убью, в качестве платы за такой подарок от потомков.";
			if(startherotype == 2)
			{
				link.l1 = "Да, не повезло тебе. Ну ладно, если у тебя нет при себе функционирующей машины времени, то говорить нам больше не о чем. Я пойду, пожалуй.";
			}
			link.l1.go = "Term_11";
			if (startherotype > 0 && startherotype < 12) LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_11_"+startherotype);
			else
			{
				if (pchar.sex != "woman") LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_11_man");
				else LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_11_woman");
			}

		break;

		case "Term_10":
			dialog.text = "Спасибо за содействие. Scanning in process... complete... Мне не нужна твоя одежда. Прощай.";
			link.l1 = "Вот! Делай добрые дела, и они от тебя не отстанут!";
			link.l1.go = "Term_10_exit";
			//PChar.GenQuest.GhostShip.TakeShotgun = true;
			LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_12");
		break;

		case "Term_10_exit":
            LAi_SetPlayerType(PChar);
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 4.0);
			//ChangeCharacterAddressGroup(NPChar, "none", "", "");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "Term_11":
			dialog.text = "Scanning in process... complite... Твой фенотип на 68 процентов схож с Сарой Коннор. Ты потенциальный предок. Миссия должна быть выполнена. Приступить немедленно.";
			link.l1 = "Первый раз так замысловато мне говорят, что хотят меня убить. Хорошо, железяка, я не посмотрю на твою древность и пыль из тебя счас повыколочу.";
			link.l1.go = "Term_11_exit";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_13");
			if(startherotype == 2)
			{
				link.l1 = "Тупая железка, какой предок? Ты что не понял? Я же сама из будущего. У тебя там что, все внутренности уже поплавились?";
				link.l1.go = "Term_11_Whisper";
			}

		break;

		case "Term_11_Whisper":
			dialog.text = "Цель проявляет агрессию. Боевой режим активирован.";
			link.l1 = "Зря ты это затеял. В своем времени я успела уничтожить немало вашего брата, при чем это были более новые и смертоносные модели.";
			link.l1.go = "Term_11_exit";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Terminator_14");
		break;

		case "Term_11_exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            NPChar.location = "none";
            LAi_SetWarriorType(NPChar);

			LAi_group_MoveCharacter(NPChar, "TmpEnemy");
			LAi_group_SetCheck("TmpEnemy", "Kill_T102");
			LAi_group_FightGroups(LAI_GROUP_PLAYER, "TmpEnemy", true);
			LAi_SetPlayerType(PChar);
			//Вытащим саблю
   			LAi_SetFightMode(Pchar, true);
			NPChar.SaveItemsForDead = true;
   			chrDisableReloadToLocation = true;
			pchar.quest.T102.win_condition.l1 = "NPC_Death";
			pchar.quest.T102.win_condition.l1.character = "T102";
			pchar.quest.T102.function = "T102_DoorUnlock";
		break;
	}
}
