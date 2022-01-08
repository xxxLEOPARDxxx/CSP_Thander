
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int z;
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

		//Бермуды. На выходе с глобалки запись в СЖ «‘Морж’ и «Рейнджер» стоят на рейде бухты Разбитого корыта, отправляюсь туда же». Собственно поставить туда Моржа и Рейнджера. Не забыть про черный флаг иначе файт со всеми и провал квеста.
		//Высаживаемся. Сильвер, Флинт, Вейн, Рекхэм, Бонни, несколько матросов и мушкетчиков на берегу 12 и более.

		case "BS_PN_shipF":	//Флинт
			NextDiag.TempNode = "BS_PN_shipF";
			dialog.text = "Наконец-то вы пришли. Причальте в бухте Разбитого корыта, там продолжим разговор .";
			link.l1 = "Договорились.";
			link.l1.go = "exit";
		break;

		case "BS_PN_shipV":	//Вейн
			NextDiag.TempNode = "BS_PN_shipV";
			dialog.text = "Вижу, ты уже здесь. Флинт объявил сходку у Разбитого корыта, встретимся там.";
			link.l1 = "Хорошо.";
			link.l1.go = "exit";
		break;

		case "BS_PN_1":	//Флинт
			dialog.text = "Мистер Вейн вкратце рассказал о ваших приключениях.";
			link.l1 = "Да, знакомство вышло бурное!";
			link.l1.go = "BS_PN_1_1";
		break;

		case "BS_PN_1_1":	//Флинт
			dialog.text = "Джон, принимайся за дешифровку, время дорого.";
			link.l1 = "...";
			link.l1.go = "BS_PN_2exit";
		break;

		case "BS_PN_2exit":
			sld = CharacterFromID("BS_Silver");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorGoToLocation(sld, "reload", "sea", Get_My_Cabin(), "", "", "", 10);
			sld = CharacterFromID("BS_Vein");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_2";
			DialogExit();
			DoQuestFunctionDelay("VeinSpeech", 0);
		break;

		//Сильвер уходит из пати в локатор высадки.

		case "BS_PN_2":	//Вейн
			dialog.text = "Знакомься. Это мои компаньоны. Джек Рекхэм и Энн Бонни. Неразлучная парочка. Джэк парень башковитый, и я настаиваю на том, чтобы он помог мистеру Сильверу с расшифровкой. Красотка Энн и её кинжалы побудут с нами.";
			link.l1 = "...";
			link.l1.go = "BS_PN_3exit";
		break;

		case "BS_PN_3exit":
			sld = CharacterFromID("BS_Bony");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_3";
			DialogExit();
			DoQuestFunctionDelay("BonySpeech", 0);
		break;

		case "BS_PN_3":	//Энн
			dialog.text = "Назови меня красоткой ещё раз, Чарльз, и потом не удивляйся, если обнаружишь нож у себя в спине.";
			link.l1 = "...";
			link.l1.go = "BS_PN_4exit";
		break;

		case "BS_PN_4exit":
			sld = CharacterFromID("BS_Vein");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_4";
			DialogExit();
			DoQuestFunctionDelay("VeinSpeech", 0);
		break;

		case "BS_PN_4":	//Вейн
			dialog.text = "Не кипятись, детка. Теперь о делах.";
			link.l1 = "...";
			link.l1.go = "BS_PN_5exit";
		break;

		case "BS_PN_5exit":
			sld = CharacterFromID("BS_Rakham");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_5";
			DialogExit();
			DoQuestFunctionDelay("RakhamSpeech", 0);
		break;

		case "BS_PN_5":	//Рекхэм
			dialog.text = "Да, не шали тут, пока меня не будет.";
			link.l1 = "...";
			link.l1.go = "BS_PN_6exit";
		break;

		case "BS_PN_6exit":
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", Get_My_Cabin(), "", "", "", 10);
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_6";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;

		//Рекхэм уходит в выгрузку.

		case "BS_PN_6":	//Флинт
			dialog.text = "Встреча с английским патрулём у Бермуд – не случайность. Я был ещё дважды атакован английскими военными, пока добрался сюда.";
			link.l1 = "...";
			link.l1.go = "BS_PN_7exit";
		break;

		case "BS_PN_7exit":
			sld = CharacterFromID("BS_Vein");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_7";
			DialogExit();
			DoQuestFunctionDelay("VeinSpeech", 0);
		break;

		case "BS_PN_7":	//Вейн
			dialog.text = "За нами тоже увязался фрегат недалеко от Доминики, но «Рейнджер» легко ушёл от него.";
			link.l1 = "Мне англичане не попадались.";
			link.l1.go = "BS_PN_8exit";
		break;

		case "BS_PN_8exit":
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_8";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;

		case "BS_PN_8":	//Флинт
			dialog.text = "Подозреваю, что прояснить ситуацию, мог бы мой старпом – Билли Бонс, но он чудесным образом пропал во время своей вахты.";
			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				StartInstantDialogNoType(pchar.WhisperPGG, "BS_17_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
			}
			else
			{
				link.l1 = "Что за?!...";
				link.l1.go = "BS_PN_9exit";
			}
		break;

		case "BS_PN_8_1":	//Флинт
			link.l1 = "Что за?!...";
			link.l1.go = "BS_PN_9exit";
		break;

		//Аларм «К оружию!» Нападает толпа пиратов из перехода в след локу. Файт

		//По окончанию

		case "BS_PN_9exit":
			DialogExit();
			LAi_SetWarriorTypeNoGroup(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			sld = CharacterFromID("BS_Vein");
			LAi_SetWarriorTypeNoGroup(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld = CharacterFromID("BS_Bony");
			LAi_SetWarriorTypeNoGroup(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			BSChaseBegun_shore_fight();

			LAi_group_SetHearRadius("BSChaseBegun_shore_fight", 100.0);
			LAi_group_SetRelation("BSChaseBegun_shore_fight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("BSChaseBegun_shore_fight", LAI_GROUP_PLAYER, true);

			//pchar.quest.BSChaseBegun_shore_fight_end.win_condition.l1 = "Group_Death";//условие победы
			//pchar.quest.BSChaseBegun_shore_fight_end.win_condition.l1.group = "BSChaseBegun_shore_fight";//какую группу уничтожить
			//pchar.quest.BSChaseBegun_shore_fight_end.function = "BSChaseBegun_shore_fight_end";
		break;

		case "BS_PN_9":	//Вейн
			dialog.text = "Какого черта? Это люди Джекмана!";
			link.l1 = "...";
			link.l1.go = "BS_PN_10exit";
		break;

		case "BS_PN_10exit":
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_10";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;

		case "BS_PN_10":	//Флинт
			dialog.text = "Элеонора! Нужно срочно попасть в поселение.";
			link.l1 = "...";
			link.l1.go = "BS_PN_11exit";
		break;

		case "BS_PN_11exit":
			sld = CharacterFromID("BS_Vein");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_11";
			DialogExit();
			DoQuestFunctionDelay("VeinSpeech", 0);
		break;

		case "BS_PN_11":	//Вейн
			dialog.text = "Она здесь? Чудно, но не удивительно. Большими деньгами запахло.";
			link.l1 = "Потом разберёмся. Нужно понять, какого чёрта тут происходит.";
			link.l1.go = "BS_PN_12exit";
			NextDiag.TempNode = "BS_PN_11_loop";
			NextDiag.CurrentNode = "BS_PN_11_loop";
		break;

		case "BS_PN_12exit":
			NextDiag.TempNode = "BS_PN_11_loop";
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_12";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;

		case "BS_PN_12":	//Флинт
			chrDisableReloadToLocation = false;
			AddQuestRecord("BSChaseBegun", "2");
			dialog.text = "Я на 'Морже' заблокирую порт. Вейн, бери своих людей и через джунгли выдвигайся в поселение.\n"+
							""+pchar.name+", на другой стороне острова, в заливе Руны, есть вход в подземелье, выдвигайся туда, тут есть сквозная пещера, а за ней проход в залив Руны. Ровно через час ударим с трёх сторон и возьмём всё под контроль.";
			link.l1 = "Так точно, выдвигаюсь!";
			link.l1.go = "exit";
			NextDiag.TempNode = "BS_PN_12_loop";
		break;

		case "BS_PN_12_loop":	//Флинт
			dialog.text = "Медлить нельзя. Иди через джунгли к заливу Руны. Он на другом конце острова. Обойди немного вдоль берега и увидишь вход в подземелье.";
			link.l1 = "Ладно, иду.";
			link.l1.go = "exit";
			NextDiag.TempNode = "BS_PN_12_loop";
		break;

		case "BS_PN_11_loop":	//Флинт
			dialog.text = "Сейчас, минутку отдышусь, соберу людей и пойду.";
			link.l1 = "Я тоже.";
			link.l1.go = "exit";
			NextDiag.TempNode = "BS_PN_11_loop";
		break;

		//Запись в СЖ «Встреча компаньонов закончилась резнёй. Люди Джекмана атаковали нас на берегу. Флинт сразу придумал план по захвату поселения. Выдвигаюсь в залив Руны и через подземелье постараюсь проникнуть на верфь. За дело!

		//Подземка. Мясной файт. Пиратов по напихано во все щели. Пробиваемся, выходим на верфь. Говорим с Алексусом.

		case "BS_PN_13_1":
			dialog.text = RandPhraseSimple("Чего тебе? Проходи мимо.", "Хватит загораживать дорогу, отвали.");
			link.l1 = RandPhraseSimple("Знаешь что? Не гавкай!", "Поумерь свой пыл. Не то быстро охлажу его!");
			link.l1.go = "exit";
			NextDiag.TempNode = "BS_PN_13_1";
		break;

		case "BS_PN_13":	//Алексус
			dialog.text = "Капитан! Вы очень кстати! Посмотрите, я придумал новый способ крепления стакселя! Это новое открытие!";
			link.l1 = "Простите мастер, не до стакселей сейчас. Что у вас тут происходит? Люди Джекмана стреляют во всё, что движется!";
			link.l1.go = "BS_PN_14";
		break;

		case "BS_PN_14":
			AddQuestRecord("BSChaseBegun", "3");
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", false);
			dialog.text = "А что происходит? Тут постоянно кто-то в кого-то стреляет. Совсем нет покоя старику! Взгляните, я могу переделать систему блоков для гафеля, и им можно будет управлять буквально одной рукой!";
			link.l1 = "Давайте позже, мастер. Не будем вам мешать!";
			link.l1.go = "BS_PN_14_1";

			NPChar.Dialog.Filename = "Common_Shipyard.c";
			NPChar.Dialog.CurrentNode = "Second time";

			PChar.quest.BSChaseBegun_town.win_condition.l1 = "location";
			PChar.quest.BSChaseBegun_town.win_condition.l1.location = "Pirates_Town";
			PChar.quest.BSChaseBegun_town.function = "BSChaseBegun_town";

		break;

		case "BS_PN_14_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				StartInstantDialogNoType(pchar.WhisperPGG, "BS_19_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
			}
		break;

		//Запись в СЖ: «Позади подземелье и куча трупов. У меня всё больше вопросов к Джекману. Алексус как всегда на своей волне. Пора в поселение, по времени как раз успеваю. Вперёд!»

		//Выходим в поселение. Бой окончен. На земле горы трупов. Флинт, Вейн, Бонни, бродят несколько «наших» пиратов.

		case "BS_PN_15":	//Вейн
			chrDisableReloadToLocation = false
			sld = CharacterFromID("Atilla");
			sld.dialog.currentnode = sld.AtillaNode;
			sld.Dialog.Filename = "Quest\Isabella\Atilla.c";
			dialog.text = "Вот это дело! Как раз по мне!";
			link.l1 = "...";
			link.l1.go = "BS_PN_15_1";
		break;

		case "BS_PN_15_1":
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_16";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;

		case "BS_PN_16":	//Флинт
			dialog.text = "Резиденция забаррикадирована, готовимся к штурму.";
			link.l1 = "...";
			link.l1.go = "BS_PN_16_1";
		break;

		case "BS_PN_16_1":
			sld = CharacterFromID("BS_Bony");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_16_2";
			DialogExit();
			DoQuestFunctionDelay("BonySpeech", 0);
		break;

		case "BS_PN_16_2":
			dialog.text = "Погоди, кажется, они открывают дверь.";
			link.l1 = "...";
			link.l1.go = "BS_PN_16exit";
		break;

		case "BS_PN_16exit":
			sld = CharacterFromID("gatri_grunt2");
			LAi_SetStayTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload3_back");
			sld.LifeDay = 0;

			sld = GetCharacter(NPC_GenerateCharacter("Gatri_temp", "BS_Gatry", "woman", "woman", 1, PIRATE, -1, true));
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload3_back");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.name = "Элеонора";
			sld.lastname = "Гатри";
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_17";
			DialogExit();
			DoQuestFunctionDelay("GatriSpeech", 0);
		break;

		//Идём к резиденции, из неё выходит Гатри и несколько мушкетчиков.

		case "BS_PN_17":	//Гатри
			dialog.text = "Джеймс! И Чарльз... Что же, вы очень вовремя. Джекман решил выдворить меня с острова и подготовил бунт. Три дня резни, стрельбы и крови.\nНо увидев всех вас он наконец понял, что дальнейшее сопротивление бесполезно и только что сложил оружие.";
			link.l1 = "...";
			link.l1.go = "BS_PN_17_1";
		break;

		case "BS_PN_17_1":
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_18";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;

		case "BS_PN_18":	//Флинт
			dialog.text = "Обе части кода у нас, и Сильвер с Рекхэмом сейчас заняты расшифровкой. Нам нужно решить текущие проблемы. Англичане настойчиво лезут в наши дела, также бунт Джекмана.";
			link.l1 = "...";
			link.l1.go = "BS_PN_18_1";
		break;

		case "BS_PN_18_1":
			sld = CharacterFromID("BS_Vein");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_19";
			DialogExit();
			DoQuestFunctionDelay("VeinSpeech", 0);
		break;

		case "BS_PN_19":	//Вейн
			dialog.text = "Я могу устроить ему допрос, 'с пристрастием'.";
			link.l1 = "...";
			link.l1.go = "BS_PN_19_1";
		break;

		case "BS_PN_19_1":
			sld = CharacterFromID("gatri_temp");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_20";
			DialogExit();
			DoQuestFunctionDelay("GatriSpeech", 0);
		break;

		case "BS_PN_20":	//Гатри
			dialog.text = "Это подождёт. Нужно навести тут порядок. Поговорим позже в резиденции.";
			link.l1 = "...";
			link.l1.go = "BS_PN_20exit";
		break;

		case "BS_PN_20exit":	//Гатри
			DialogExit();
			LAi_MethodDelay("BSChaseBegun_FewDeaysLater",0.1);
			PChar.quest.BSChaseBegun_townhall.win_condition.l1 = "location";
			PChar.quest.BSChaseBegun_townhall.win_condition.l1.location = "Pirates_townhall";
			PChar.quest.BSChaseBegun_townhall.function = "BSChaseBegun_townhall";
		break;

		//Картинка «На следующий день» убираем трупы, перемещаем ГГ, Флинта, Вейна, Гатри, Сильвера и Рекхэма в резиденцию.

		case "BS_PN_21":	//Сильвер
			dialog.text = "Итак господа, 'Урка Де Лима', судя по расшифровке, уже в Гаване. Там она возьмёт на борт две роты морской пехоты и в сопровождении четырёх военных кораблей отправится к Пуэрто-Рико, где к эскадре присоединится ещё два корабля охранения. После чего, вся армада отправится в Европу.";
			link.l1 = "...";
			link.l1.go = "BS_PN_21_1";
		break;

		case "BS_PN_21_1":
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_22";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;

		case "BS_PN_22":	//Флинт
			dialog.text = "Каким маршрутом пойдёт эскадра из Гаваны?";
			link.l1 = "...";
			link.l1.go = "BS_PN_22_1";
		break;

		case "BS_PN_22_1":
			sld = CharacterFromID("BS_Silver");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_23";
			DialogExit();
			DoQuestFunctionDelay("SilverSpeech", 0);
		break;

		case "BS_PN_23":	//Сильвер
			dialog.text = "Южным. К мысу Сан Антонио и оттуда на восток, избегая французских вод. В Санто-Доминго стоянка не планируется, но исключить её нельзя. Там в тексте есть заметки об этом. На случай шторма или ещё каких неурядиц. Далее к Сан–Хуану, потом Сан Мартен и в океан.";
			link.l1 = "...";
			link.l1.go = "BS_PN_23_1";
		break;

		case "BS_PN_23_1":
			sld = CharacterFromID("gatri_temp");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_24";
			DialogExit();
			DoQuestFunctionDelay("GatriSpeech", 0);
		break;

		case "BS_PN_24":	//Гатри
			dialog.text = "Контрабандисты сообщили, что в Санто-Доминго чума, скорее всего испанская эскадра пройдёт мимо города без остановки.";
			link.l1 = "...";
			link.l1.go = "BS_PN_24_1";
		break;

		case "BS_PN_24_1":
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_25";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;

		case "BS_PN_25":	//Флинт
			dialog.text = "Значит прямым ходом в Сан–Хуан. Вейн, есть для тебя работа. Найди тут на Бермудах сумасшедших головорезов на паре-тройке шлюпов, и не теряя ни минуты выдвигайтесь к северному побережью Каймана. Задача: курсировать неподалёку от мыса Сан Антонио и, заметив движение эскадры, атаковать корабли сопровождения. В бой не ввязываться, а удирать на всех парусах.";
			link.l1 = "...";
			link.l1.go = "BS_PN_25_1";
		break;

		case "BS_PN_25_1":
			sld = CharacterFromID("BS_Vein");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_26";
			DialogExit();
			DoQuestFunctionDelay("VeinSpeech", 0);
		break;

		case "BS_PN_26":	//Вейн
			dialog.text = "Понимаю. Воинственные испанцы решат удаль показать и погонятся за мной.";
			link.l1 = "...";
			link.l1.go = "BS_PN_26_1";
		break;

		case "BS_PN_26_1":
			sld = CharacterFromID("Flint");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_27";
			DialogExit();
			DoQuestFunctionDelay("FlintSpeech", 0);
		break;

		case "BS_PN_27":	//Флинт
			dialog.text = "Правильно, и вы заведёте погоню на Риф Скелета, где их корабли побьются об рифы, после чего уйдут обратно в Гавану на ремонт.";
			link.l1 = "А мы в это время атакуем 'Урку'? Где?";
			link.l1.go = "BS_PN_27_2";
		break;

		case "BS_PN_27_2":	//Флинт
			npchar.nation = PIRATE;
			dialog.text = "Прям на глазах гарнизона Санто-Доминго, но вне досягаемости его пушек! Из-за карантина они не смогут ничем помочь 'Урке'.";
			link.l1 = "...";
			link.l1.go = "BS_PN_27_1";
		break;

		case "BS_PN_27_1":
			sld = CharacterFromID("BS_Vein");
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\BlackSails\Pogonya_Nachalas.c";
			sld.dialog.currentnode = "BS_PN_28";
			DialogExit();
			DoQuestFunctionDelay("VeinSpeech", 0);
		break;

		case "BS_PN_28":	//Вейн
			AddQuestRecord("BSChaseBegun", "4");
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable(pchar.location.from_sea, "boat", false);
			LocatorReloadEnterDisable("Bermudes_Cavern", "reload2_back", false);
			pchar.location.from_sea = "Pirates_town";
			dialog.text = "Я буду там. После того как загоню сторожевиков на рифы.";
			link.l1 = "Значит, за дело!";
			link.l1.go = "BS_PN_28exit";
		break;

		case "BS_PN_28exit":
			PChar.quest.BSChaseBegun_lock_townhall.win_condition.l1 = "location";
			PChar.quest.BSChaseBegun_lock_townhall.win_condition.l1.location = "Pirates_town";
			PChar.quest.BSChaseBegun_lock_townhall.function = "BSChaseBegun_lock_townhall";

			DialogExit();
			sld = CharacterFromID("Flint");
			LAi_SetActorType(sld);
			LAi_SetImmortal(sld, false);
			ProcessHullRepair(sld, 100.0);
			ProcessSailRepair(sld, 100.0);
			DeleteAttribute(sld, "ship.blots");
			DeleteAttribute(sld, "ship.sails");
			DeleteAttribute(sld, "ship.masts");

			sld = CharacterFromID("BS_Silver");
			LAi_SetActorType(sld);

			sld = CharacterFromID("BS_Rakham");
			LAi_SetActorType(sld);

			sld = CharacterFromID("BS_Vein");
			LAi_SetActorType(sld);

			sld = CharacterFromID("BS_Bony");
			LAi_SetActorType(sld);

			sld = CharacterFromID("gatri_temp");
			LAi_SetActorType(sld);

			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				StartInstantDialogNoType(pchar.WhisperPGG, "BS_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
			}
		break;

		//Запись в СЖ: «Самоубийственный план, как по мне. Но больше возможностей взять золотишко не будет. Выдвигаюсь, как только буду готов(ва). Вейн займётся выманиванием охраны, Флинт выдвинется раньше и станет вне видимости форта на якорь. Дело за мной».

		//Двигаем в локацию Санто-Доминго. Морж уже там далеко от форта. На всякий убрать сторожей местных и мелочь, чтоб не было содомии. Подходим к Моржу, спаун испанцев. Урки среди них нет. Штук 8 военных. Мясо.

		//Запись в СЖ: «Где чёртов галеон? Нужно поговорить с Флинтом на его корабле! Вейна тоже невидно, что–то пошло не так.»

		//Высылаем шлюпу на Моржа. Говорим с Флинтом

		case "BS_PN_30_seabattle":	//Флинт
			PChar.quest.BSChaseBegun_EndQuest.win_condition.l1 = "location";
			PChar.quest.BSChaseBegun_EndQuest.win_condition.l1.location = "Pirates_Town";
			PChar.quest.BSChaseBegun_EndQuest.function = "BSChaseBegun_EndQuest";

			dialog.text = "Здесь слишком опасно оставаться. Поговорим на Бермудах.";
			link.l1 = "Вы правы. Следуйте за моим судном.";
			link.l1.go = "exit";
			NextDiag.TempNode = "BS_PN_30_seabattle";
			DeleteAttribute(pchar, "LockMapReload");
			DeleteAttribute(pchar, "LockShoreReload");
			SetCompanionIndex(PChar, -1, GetCharacterIndex(npchar.id));//Флинт присоединяется к эскадре
			Flag_Change(PIRATE);

			for (z = 1; z < 9; z++)
			{
				sld CharacterFromID("BSChaseBegun_SeaBattle"+z);
				sld.LifeDay = 0;
			}
		break;

		case "BS_PN_30":	//Флинт
			dialog.text = "...";
			link.l1 = "Похоже план провалился! Или Сильвер солгал, или испанцы оказались хитрее!";
			link.l1.go = "BS_PN_31";
		break;

		case "BS_PN_31":
			AddQuestRecord("BSChaseBegun", "6");
			LAi_SetImmortal(npchar, true);
			DeleteAttribute(Colonies[FindColony("SantoDomingo")], "DontSetShipInPort");
			DeleteAttribute(Colonies[FindColony("SantoDomingo")], "BSChaseBegun");
			Group_SetAddress("Flint_Group", "Bermudes", "Quest_ships", "quest_ship_8");

			dialog.text = "С Сильвером я потолкую. Пока нам нужно залечь на дно. Встретимся через неделю на Бермудах. Ищи по своим каналам любую зацепку, я поищу по своим. Нутром чую, 'Урка' ещё на Карибах. Вопрос – где?";
			link.l1 = "Есть у меня одна пташка на примете, послушаю, что она пропоёт.";
			link.l1.go = "BS_PN_32";
		break;

		case "BS_PN_32":
			chrDisableReloadToLocation = false;
			LAi_SetActorTypeNoGroup(npchar);
			dialog.text = "Пока нам стоит разойтись, поговорим позже.";
			link.l1 = "Поддерживаю.";
			link.l1.go = "BS_PN_32exit";
		break;

		case "BS_PN_32exit":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 20);
			BS_ReplaceHostessWithMaks();
			sld = CharacterFromID("PortRoyal_hostess");
			sld.dialog.filename = "Quest\BlackSails\Neulovimaya_Urka.c";
			sld.dialog.currentnode = "BS_NU_1";
			BSBons_SeaBattle(false);

			if (WhisperIsHere())
			{
				SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
				StartInstantDialogNoType(pchar.WhisperPGG, "BS_1_WhisperIsHere", "Quest\WhisperLine\Whisper.c");
			}
		break;

		//Запись в СЖ: «Любой план летит к чертям, как только возьмёшься за его реализацию. Но ещё не всё потерянно! Навещу-ка я Максин в Порт Рояле, портовые девки много чего знают, а эта мне обязана. Долг - платежом красен».

	}
}
