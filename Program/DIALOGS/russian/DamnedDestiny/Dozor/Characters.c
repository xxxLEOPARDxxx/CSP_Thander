
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string sName = GetNameLugger(PChar, "f");
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Что вам надо?";
			link.l1 = "Ничего.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		// РЫБАК ПЕДРО -->
		case "Fisher_Pedro_1":
			dialog.text = "...(чуть не плача)... И ты туда же? Тоже хочешь поиздеваться над Педро? Давай, чего ждёшь?";
			link.l1 = "Неуловимая Эскадра появилась в водах Карибского Моря.";
			link.l1.go = "Fisher_Pedro_2";
		break;

		case "Fisher_Pedro_2":
			dialog.text = "Что? Что вы только что произнесли?";
			link.l1 = "Неуловимая Эскадра появилась в водах Карибского Моря.";
			link.l1.go = "Fisher_Pedro_3";
		break;

		case "Fisher_Pedro_3":
			dialog.text = "...(оживляясь)... Выходит, ты тот самый капитан, что ввязался в Дозор?";
			link.l1 = "Да, это я. У тебя есть что-нибудь для меня?";
			link.l1.go = "Fisher_Pedro_4";
		break;

		case "Fisher_Pedro_4":
			TakeNItems(PChar, "Dozor_Mekakhrom", 1);
			dialog.text = "Да, вот держи! Это второй Мекахром.";
			link.l1 = "Спасибо. Удачи тебе.";
			link.l1.go = "Fisher_Pedro_5";
		break;

		case "Fisher_Pedro_5":
			dialog.text = "Э-э, капитан, постойте! У вас случайно не будет 50 золотых для бедного рыбака?";

			if(sti(PChar.money) >= 50)
			{
				link.l1 = "Только обещай, что потратишь их с умом, а не пропьёшь или не проиграешь, лады?";
				link.l1.go = "Fisher_Pedro_6";
			}

			link.l2 = "Случайно не будет. Прощай.";
			link.l2.go = "Fisher_Pedro_9";
		break;

		case "Fisher_Pedro_6":
			dialog.text = "Лады! Давай их скорее!";
			link.l1 = "Ха! Ты что действительно думал, что я тебе их дам? Держи карман шире.";
			link.l1.go = "Fisher_Pedro_7";
			link.l2 = "Вот держи и прощай. У меня нет времени с тобой тут торчать.";
			link.l2.go = "Fisher_Pedro_8";
		break;

		case "Fisher_Pedro_7":
			dialog.text = "Ах ты! Ах ты, жадная скотина! Проклят" + GetSexPhrase("ый","ая") +" зажравш" + GetSexPhrase("ийся","аяся") +" " + GetSexPhrase("ублюдок","сучка") +"! Убирайся! ...(хныкая)... Убирайся!";
			link.l1 = "Проваливай с моих глаз, ничтожество.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DozorFisherPedroExit");
		break;

		case "Fisher_Pedro_8":
			AddMoneyToCharacter(PChar, -50);
			DozorFisherPedroExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Fisher_Pedro_9":
			DozorFisherPedroExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		// РЫБАК ПЕДРО <--

		// УБИЙЦЫ АГЕНТА В ГРОТЕ ТЕРКСА -->
		case "Grot_Agent_Killers_1":
			SetCameraDialogMode(CharacterFromID("Dozor Grot Agent Killer 2"));
			dialog.text = "Гебельс: Да выкинь ты эту штуковину, Кригер, она и гроша ломанного не стоит.";
			link.l1 = "";
			link.l1.go = "Grot_Agent_Killers_2";
		break;

		case "Grot_Agent_Killers_2":
			SetCameraDialogMode(CharacterFromID("Dozor Grot Agent Killer 1"));
			dialog.text = "Кригер: А я уверен, что это очень важная вещь. Смотри вот здесь написано...";
			link.l1 = "";
			link.l1.go = "Grot_Agent_Killers_3";
		break;

		case "Grot_Agent_Killers_3":
			SetCameraDialogMode(CharacterFromID("Dozor Grot Agent Killer 2"));
			dialog.text = "Гебельс: ...(перебивая)... Ты гляди-ка кто к нам пришёл!";
			link.l1 = "";
			link.l1.go = "Grot_Agent_Killers_4";
			AddDialogExitQuestFunction("DozorBattleInTerksGrot");
		break;

		case "Grot_Agent_Killers_4":
			SetCameraDialogMode(CharacterFromID("Dozor Grot Agent Killer 1"));
			dialog.text = "Кригер: ...(сквозь зубы)... Очередная жертва. Прямо к нам в лапы!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DozorBattleInTerksGrot");
		break;
		// УБИЙЦЫ АГЕНТА В ГРОТЕ ТЕРКСА <--

		// СПАНЧ БОБ -->
		case "Spanch_Bob_1":
			dialog.text = "И-ик? Чего надо?";
			link.l1 = "Отважный капитан вступил в схватку с Неуловимой Эскадрой.";
			link.l1.go = "Spanch_Bob_2";
		break;

		case "Spanch_Bob_2":
			dialog.text = "А-а! Дозорим, " + GetSexPhrase("мой","моя") +" " + GetSexPhrase("друг","подруга") +"?";
			link.l1 = "Да вот решил" + GetSexPhrase("","а") +" ввязаться, попробовать.";
			link.l1.go = "Spanch_Bob_3";
		break;

		case "Spanch_Bob_3":
			dialog.text = "И правильно решил" + GetSexPhrase("","а") +"! Помниться я тоже в эту игру играл, славные были деньки. Давненько это было. Да только всё время не везло нашей команде. То мачта сломается, то на мель сядем, то ещё какая-нибудь пакость приключиться.";
			link.l1 = "А что и раньше такие игры проводились?";
			link.l1.go = "Spanch_Bob_4";
		break;

		case "Spanch_Bob_4":
			dialog.text = "Конечно! А ты разве не знал" + GetSexPhrase("","а") +"?";
			link.l1 = "Не знал" + GetSexPhrase("","а") +", я впервые слышу об этом.";
			link.l1.go = "Spanch_Bob_5";
		break;

		case "Spanch_Bob_5":
			dialog.text = "Эх, деревня ты, кэп. Ну ладно, удачи тебе разга... И-ик! В общем, прощавай, " + GetSexPhrase("брат","сестрица") +"!";
			link.l1 = "Эй! А как же следующий Мекахром?";
			link.l1.go = "Spanch_Bob_6";
		break;

		case "Spanch_Bob_6":
			dialog.text = "Мека-как? Мекахром?";
			link.l1 = "Ты должен был передать его мне, там следующая загадка.";
			link.l1.go = "Spanch_Bob_7";
		break;

		case "Spanch_Bob_7":
			dialog.text = "А-а, это бесполезный кусок... железа. Прости, " + GetSexPhrase("братуха","систер") +", пропил я его на днях.";
			link.l1 = "Что?! Пропил? Совсем с катушек съехал, развалина пьяная? Я как, по-твоему, игру продолжать долж" + GetSexPhrase("ен","на") +", а?!";
			link.l1.go = "Spanch_Bob_8";
		break;

		case "Spanch_Bob_8":
			dialog.text = "Да не кипятись ты так!";
			link.l1 = "Я 20 штук отвалил" + GetSexPhrase("","а") +" за игру! Да я тебе сейчас глотку перережу, свинья!";
			link.l1.go = "Spanch_Bob_10";
		break;

		case "Spanch_Bob_10":
			dialog.text = "Эй! Руки от меня убери! И-ик! Если поможешь мне, я помогу тебе!";
			link.l1 = "И как ты собираешься мне помочь?";
			link.l1.go = "Spanch_Bob_11";
		break;

		case "Spanch_Bob_11":
			dialog.text = "Если дашь мне пять сотен, я тебе загадку скажу, я её хорошо помню.";
			link.l1 = "А как я получу ключевую фразу без Мекахрома?";
			link.l1.go = "Spanch_Bob_12";
		break;

		case "Spanch_Bob_12":
			dialog.text = "Я тебе её скажу, если загадку разгадаешь. Я её хорошо запомнил.";
			link.l1 = "Вот как? Так значит, ты разгадал ту загадку в Мекахроме?";
			link.l1.go = "Spanch_Bob_13";
		break;

		case "Spanch_Bob_13":
			dialog.text = "А чего там разгадывать? Вот в настоящем Дозоре, там головоломки такие, что голову сломаешь, пока разгадаешь, а твои детские ''загадки'' любой за 5 минут разгадает.";
			link.l1 = "...(тихим голосом)... Так может, ты мне сразу скажешь ключевую фразу, а головоломка чёрт с ней!";
			link.l1.go = "Spanch_Bob_14";
		break;

		case "Spanch_Bob_14":
			dialog.text = "Э, нет " + GetSexPhrase("брат","сестрица") +"! Настоящий дозорный всегда играет честно, запомни! Вот тебе загадка. ...(записано в судовой журнал) \n Как разгадаешь, сообщи мне ответ. Если правильный, я говорю тебе ключевую фразу, если нет... Что же, на нет и суда нет. И смотри не забудь 500 золотых! Без них ключевую фразу не скажу.";
			link.l1 = "...(тихо)... Не забуду, прохвост чёртов!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DozorGuadeloupeShoreGetTask");
			NextDiag.TempNode = "Spanch_Bob_15";
		break;

		case "Spanch_Bob_15":
			dialog.text = "Прин" + GetSexPhrase("ёс","есла") +" деньги?";

			if(sti(PChar.money) >= 500)
			{
				link.l1 = "Вот твои пиастры, мошенник.";
				link.l1.go = "Spanch_Bob_16";
			}

			link.l2 = "У меня их сейчас нет. Принесу потом.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Spanch_Bob_15";
		break;

		case "Spanch_Bob_16":
			AddMoneyToCharacter(PChar, -500);
			dialog.text = "Вот, другой разговор! Итак, капитан, какие догадки по поводу загадки? Назовите мне только место и я дам вам ключевую фразу.";
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Spanch_Bob_17";
		break;

		case "Spanch_Bob_17":
			string sString = GetStrSmallRegister(dialogEditStrings[1]);
			if(sString == "залив гибели")
			{
				dialog.text = "Бинго! Ключевая фраза - ''Неуловимая Эскадра потеряла флагман''.";
				Link.l1 = "Прощай!";
				Link.l1.go = "exit";
				AddDialogExitQuestFunction("DozorToDeadShoreInMein");
			}
			else
			{
				dialog.text = "Нет, капитан вы неправы. Попробуйте ещё.";
				link.l1 = "Чёрт возьми!";
				link.l1.go = "exit";
				NextDiag.TempNode = "Spanch_Bob_18";
			}
		break;

		case "Spanch_Bob_18":
			NextDiag.TempNode = "Spanch_Bob_18";
			dialog.text = "Итак, капитан, какие догадки по поводу загадки? Назовите мне только место и я дам вам ключевую фразу.";
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Spanch_Bob_17";
		break;
		// СПАНЧ БОБ <--

		// КАПИТАН ФЛЕЙТА У МАРТИНИКИ -->
		case "Justin_Butt_1":
			dialog.text = "Ты победил" + GetSexPhrase("","а") +", победил" + GetSexPhrase("","а") +"! Забери Мекахром из сундука, только оставь меня в покое!";
			link.l1 = "Почему ты напал на меня? Отвечай!";
			link.l1.go = "Justin_Butt_2";
		break;

		case "Justin_Butt_2":
			dialog.text = "А разве непонятно, капитан?";
			link.l1 = "Это часть задания? Суть в том, что я долж" + GetSexPhrase("ен","на") +" был" + GetSexPhrase("","а") +" боем взять Мекахром?";
			link.l1.go = "Justin_Butt_3";
		break;

		case "Justin_Butt_3":
			dialog.text = "Какое ещё к черту задание? Ты что, не понимаешь, что здесь происходит?";
			link.l1 = "Да, объясни, ты, наконец, толком!";
			link.l1.go = "Justin_Butt_4";
		break;

		case "Justin_Butt_4":
			dialog.text = "Мы с тобой соперники, понимаешь?";
			link.l1 = "Соперники?";
			link.l1.go = "Justin_Butt_5";
		break;

		case "Justin_Butt_5":
			dialog.text = "Да! По-твоему лицу видать, что ты впервые слышишь об этом. Что же раз уж ты победил" + GetSexPhrase("","а") +" меня в честном бою, расскажу тебе. Понимаешь, ты не " + GetSexPhrase("один","одна") +" в этой игре, помимо тебя и меня, есть ещё три капитана, которые играют в Дозор. \n Этот старик, организатор игры, предложил сыграть в эту игру всем капитанам, которые бросали якорь на Бермудах, пока он был там. И пять из них согласились.";
			link.l1 = "И в числе прочих согласившихся был ты?";
			link.l1.go = "Justin_Butt_6";
		break;

		case "Justin_Butt_6":
			dialog.text = "Верно. Только вот, старик, не стал говорить, что помимо меня, будет играть кто-то ещё. Но я проследил за ним и выяснил это сам, после чего убил его, и стал охотиться за остальными капитанам.";
			link.l1 = "И что с ними произошло?";
			link.l1.go = "Justin_Butt_7";
		break;

		case "Justin_Butt_7":
			dialog.text = "Я устранил всех конкурентов, кроме тебя. Один корабль я утопил, как только тот отчалил от Бермуд, второй нагнал у Пуэрто-Рико, третьего уничтожил близ Кюрасао. Вот только с тобой были проблемы. \n До Мейна я абсолютно точно знал, что ты впереди меня, но никак не мог выяснить сколько же времени я тебе проигрываю. На Мейне же мне удалось выяснить, что уступаю тебе лишь пару дней. Я быстро разгадал загадку и на всех парусах помчался на Мартинику.";
			link.l1 = "Значит игроков несколько? Получается, что и Мекахромов должно быть несколько?";
			link.l1.go = "Justin_Butt_8";
		break;

		case "Justin_Butt_8":
			dialog.text = "Да, у каждого агента было по десять Мекахромов. Они должны были давать по Мекахрому каждому, кто скажет им ключевую фразу.";
			link.l1 = "А как же Теркс? Я наш" + GetSexPhrase("ёл","ла") +" там лишь один Мекахром - у бандитов, которые, по-видимому, убили агента.";
			link.l1.go = "Justin_Butt_9";
		break;

		case "Justin_Butt_9":
			dialog.text = "Чего не знаю, того не знаю. Я уступал тебе тогда, приехал на Теркс после тебя и обнаружил несколько трупов. Один из них, судя по всему, и был агентом, а двое других смахивали на бандитов, которых как я понял сейчас, завалил" + GetSexPhrase("","а") +" ты. Я нашёл предназначавшиеся нам Мекахромы спрятанными в пещере.";
			link.l1 = "А Мейн? Откуда ты узнал, что я опережаю тебя на два дня?";
			link.l1.go = "Justin_Butt_10";
		break;

		case "Justin_Butt_10":
			dialog.text = "На Мейне тоже был агент, только у него была другая миссия. По логике игры, дозорные должны были найти Мекахром в сундуке, на разбитом корабле. Я тоже его там нашёл, но при этом знал, что, так как есть другие игроки, то Мекахромов должно быть несколько. \n Я обыскал окрестности и нашёл агента. Он рассказал мне, что должен был следить за нами и подкладывать Мекахромы, каждый раз, после того, как очередной дозорный его заберёт.";
			link.l1 = "То есть после того, как я наш" + GetSexPhrase("ёл","ла") +" Мекахром, он положил новый, чтобы ты его нашёл?";
			link.l1.go = "Justin_Butt_11";
		break;

		case "Justin_Butt_11":
			dialog.text = "Правильно, а после того, как я взял второй Мекахром, он положил третий, но так как благодаря мне никого не осталось, то и Мекахром, и агент, были бесполезны.";
			link.l1 = "Ты его убил?";
			link.l1.go = "Justin_Butt_12";
		break;

		case "Justin_Butt_12":
			dialog.text = "Да, а зачем оставлять его в живых? Я оставлял в живых только тех, кого опасно было убивать. Рыбака с пляжа Фахардо я прикончил, пяьного с Ламантена – тоже. Про агента залива Гибели ты уже знаешь – его постигла та же участь. Всех остальных агентов я оставил в живых.";
			link.l1 = "А знаешь, у меня нет в планах оставлять тебя в живых, после того что ты совершил. Защищайся!";
			link.l1.go = "Justin_Butt_13";
		break;

		case "Justin_Butt_13":
			TakeNItems(PChar, "Dozor_Mekakhrom", -1);
			dialog.text = "А ты думал"+ GetSexPhrase("","а") +", что я собираюсь позволить тебе вот так просто уйти? Чёрта с два!";
			link.l1 = "Ну, попробуй, ублюдок!";
			link.l1.go = "exit";

			PChar.Dozor.CabinID = PChar.location;
			Locations[FindLocation(PChar.location)].box1.items.Dozor_Key = 1;
			Locations[FindLocation(PChar.location)].box1.items.Dozor_Mekakhrom = 1;

			LAi_SetCurHPMax(NPChar);
			AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattleNoParam");
		break;
		// КАПИТАН ФЛЕЙТА У МАРТИНИКИ <--

		// НЕЗНАКОМЕЦ В ДОМЕ -->
		case "NoName_1":
			dialog.text = "Ты перв" + GetSexPhrase("ый","вая") +", кто добрался до сокровища, дозорн" + GetSexPhrase("ый","ая") +". Поздравляю!";
			link.l1 = "Кто вы такой?";
			link.l1.go = "NoName_2";
		break;

		case "NoName_2":
			dialog.text = "Я от Фабиана Гронхольма, организатора этой игры, помните его?";
			link.l1 = "Очень хорошо помню. Вы знаете, что Фабиана убили?";
			link.l1.go = "NoName_3";
		break;

		case "NoName_3":
			dialog.text = "Вот как?";
			link.l1 = "У Мартиники мы пересеклись с одним капитаном. Он рассказал мне, что он убил Гронхольма, всех остальных дозорных, а также некоторых агентов. Хотел прикончить и меня, да не вышло.";
			link.l1.go = "NoName_4";
		break;

		case "NoName_4":
			dialog.text = "Жаль, Фабиан был отличным человеком, энергичным, смелым, предприимчивым.";
			link.l1 = "А ничего, что он никому из нас, играющих в его игру, не сказал, что будут соперники?";
			link.l1.go = "NoName_5";
		break;

		case "NoName_5":
			dialog.text = "Ему не хотелось сталкивать вас лбами, ибо знал, что вы будете стремиться не разгадывать головоломки, а перерезать друг другу глотки.";
			link.l1 = "Я к этому бы точно не стреми" + GetSexPhrase("лся","лась") +", печально.";
			link.l1.go = "NoName_6";
		break;

		case "NoName_6":
			dialog.text = "А вот капитан Джастин Батт как видишь, с удовольствием это проделал со всеми вами. Честно говоря, я рад, что вам удалось прикончить его - не люблю такого рода людей.";
			link.l1 = "А что у вас за роль в игре? Вы тоже агент?";
			link.l1.go = "NoName_7";
		break;

		case "NoName_7":
			dialog.text = "Можно и так сказать. Вообще-то я соратник Фабиана, его правая рука. Я должен был отслеживать очерёдность вашего прибытия сюда, говорить вам спасибо за игру, класть в сундук новый клад и закрывать его.";
			link.l1 = "То есть те, кто должен прибыть сюда после меня тоже получили бы клад?";
			link.l1.go = "NoName_8";
		break;

		case "NoName_8":
			dialog.text = "Точно. Тебе, как перво" + GetSexPhrase("му","й") +" " + GetSexPhrase("прибывшему","прибывшей") +", полагается самый богатый клад - 3 ценных вещи и 100.000 золотых, которые с лихвой покроют твои расходы. Второму прибывшему полагался клад, который содержит 1 ценную вещь и покроет издержки на игру. \n Третьему мы возвращали взнос за игру, а остальные должны были уйти ни с чем. Но так как никто кроме тебя не придёт, то моя задача выполнена.";
			link.l1 = "А раньше такого рода игры проводились? Один из моих агентов что-то упоминал об этом?";
			link.l1.go = "NoName_9";
		break;

		case "NoName_9":
			dialog.text = "Да, были такого рода игры, Фабиан успел провести уже 3 подобных мероприятия..";
			link.l1 = "Странно, но до того как Фабиан предложил мне сыграть, я никогда не слышал" + GetSexPhrase("","а") +" о Дозоре.";
			link.l1.go = "NoName_10";
		break;

		case "NoName_10":
			dialog.text = "А слышать ты вряд ли мог" + GetSexPhrase("","ла") +". К концу игры, как правило, выживал лишь один капитан. Я же говорю, они стремятся уничтожить друг-друга - не умеют играть честно. Поэтому вы не знали, вернее не должны были знать о существовании друг-друга. Как видишь, опять ничего не вышло - в живых остал" + GetSexPhrase("ся","ась") +" только " + GetSexPhrase("один","одна") +" ты. ";
			link.l1 = "А что с игрой будет сейчас. Если Фабиана убили, значит, игры больше не будут проводиться?";
			link.l1.go = "NoName_11";
		break;

		case "NoName_11":
			dialog.text = "Организатором мог бы вполне стать я, но... Меня останавливает то, что уже слишком много людей погибло из-за этой игры. Поэтому проект, скорее всего, будет закрыт.";
			link.l1 = "Думаю, это правильное решение.";
			link.l1.go = "NoName_12";
		break;

		case "NoName_12":
			dialog.text = "Рад, что вы со мной согласились. Спасибо за игру. Удачи вам!";
			link.l1 = "Счастливо оставаться.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DozorHappyEnd");
		break;
		// <-- НЕЗНАКОМЕЦ В ДОМЕ


		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
