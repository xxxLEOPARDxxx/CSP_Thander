
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

		case "First_time":							//Автор Sinistra
			dialog.text = "Приветствую вас, "+ GetSexPhrase("сэр","леди")+". Меня зовут Бартоломью Ольстер. Кстати, вы не видели Карлу, девушку из таверны? Она куда-то пропала...";
			link.l1 = "Нет, я не знаю, кто она, и уж тем более - где она. Но вы говорите как англичанин - скажите, как вы попали сюда?";
			link.l1.go = "Bartolom";
			link.l2 = "Не знаю. Быть может вам стоит поискать в таверне - это было бы логично.";
			link.l2.go = "Bartolom";
			PlayVoice("Kopcapkz\Voices\PDM\Bartholomew Olster.wav");
		break;

		case "Bartolom":
			dialog.text = "Простите, но прямо сейчас я не могу с вами разговаривать. Мне нужно найти Карлу!";
			link.l1 = "В таком случае, до встречи.";
			link.l1.go = "PoraVTavernu";
		break;

		case "PoraVTavernu":
			SetQuestHeader("PDM_Ohota_na_vedmu");
			AddQuestRecord("PDM_Ohota_na_vedmu", "1");
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","а"));

			sld = CharacterFromID("PDM_Isp_sekr_guber")
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload3_back", "PDM_ONV_BARTO_Ischezni", -1);

			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Carla", "Girl_3", "woman", "woman", 10, SPAIN, -1, false));
			LAi_SetImmortal(sld, true);
			sld.name = "Карла ";
			sld.lastname = "";
			sld.city = "Havana";
			ChangeCharacterAddressGroup(sld, "Havana_tavern", "goto", "goto13");
			LAi_SetWaitressType(sld);
			sld.dialog.filename   = "Quest/PDM/Ohota_na_vedmu.c";
			sld.dialog.currentnode   = "First_Carla_1";

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First_Carla_1":
			dialog.text = "Чего ты здесь ищешь, гуап"+ GetSexPhrase("о","а")+"? Удовольствий, я полагаю? Меня зовут Карла, или Весёлая Карла, как меня называют большинство мужчин в этом городе. А как тебя зовут, сеньор"+ GetSexPhrase("","ита")+"?";
			link.l1 = "Можешь звать меня "+pchar.name+", дорогуша. Но я полагаю, что тут в городе есть ещё один человек, который ищет удовольствий. Я видел"+ GetSexPhrase("","а")+" его на площади - ему похоже, не терпится встретиться с тобой.";
			link.l1.go = "First_Carla_2";
			PlayVoice("Kopcapkz\Voices\PDM\Spain\Catalina.wav");
		break;

		case "First_Carla_2":
			dialog.text = "Что? Бартоломью? Но я думала, что он... А, неважно... Знаешь что, гуап"+ GetSexPhrase("о","а")+" - я тут вспомнила, что я немного занята сегодня. Но мы проделаем всё, чего нам хочется в другой раз - когда я буду посвободнее. У тебя очень красивые ноги, кстати.";
			link.l1 = "Э... Спасибо. Я пожалуй загляну к тебе попозже.";
			link.l1.go = "First_Carla_Uhodit";
		break;

		case "First_Carla_Uhodit":
			AddQuestRecord("PDM_Ohota_na_vedmu", "2");
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","а"));

			bDisableFastReload = true;
			LocatorReloadEnterDisable("Havana_town", "reload3_back", true);
			LocatorReloadEnterDisable("Havana_town", "reload2_back", true);
			LocatorReloadEnterDisable("Havana_town", "reload1_back", true);
			LocatorReloadEnterDisable("Havana_ExitTown", "reload1_back", true);
			LocatorReloadEnterDisable("Havana_ExitTown", "reload2_back", true);
			LocatorReloadEnterDisable("Havana_ExitTown", "reload3_back", true);

			sld = CharacterFromID("PDM_ONV_Carla")
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			LAi_ActorRunToLocator(sld, "reload", "reload1_back", "PDM_ONV_Clara_Ischezni", -1);

			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Sin", "SpaOfficer1", "man", "man", 100, SPAIN, -1, false));
			sld.name = "Синистра ";
			sld.lastname = "";
			sld.greeting = "GR_Spainguard";
			sld.city = "Havana";
			FantomMakeCoolFighter(sld, 100, 100, 100, "blade27", "pistol6", 0);
			LAi_SetHP(sld, 1.0, 1.0);
			LAi_SetImmortal(sld, false);
			ChangeCharacterAddressGroup(sld, "Havana_town", "reload", "reload3_back");
			LAi_SetStayType(sld);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			sld.dialog.filename   = "Quest/PDM/Ohota_na_vedmu.c";
			sld.dialog.currentnode   = "OfficerGuard";

			PChar.quest.PDM_ONV_Vzaimno.win_condition.l1 = "NPC_Death";
			PChar.quest.PDM_ONV_Vzaimno.win_condition.l1.character = "PDM_ONV_Sin";
			PChar.quest.PDM_ONV_Vzaimno.win_condition = "PDM_ONV_Vzaimno";

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "OfficerGuard":
			dialog.text = "Извините, сеньор, но мне не велено никого впускать.";
			link.l1 = "Как скажете, офицер. Адиос!";
			link.l1.go = "OfficerGuard_Cod";
			NextDiag.TempNode = "OfficerGuard_Again";
		break;

		case "OfficerGuard_Cod":
			AddQuestRecord("PDM_Ohota_na_vedmu", "3");
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","а"));

			PChar.quest.PDM_ONV_Vkomnate.win_condition.l1 = "location";
			PChar.quest.PDM_ONV_Vkomnate.win_condition.l1.location = "Havana_TownhallRoom";
			PChar.quest.PDM_ONV_Vkomnate.win_condition = "PDM_ONV_Vkomnate";

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "OfficerGuard_Again":
			dialog.text = "Извините, сеньор"+ GetSexPhrase("","ита")+", но мне не велено никого впускать.";
			link.l1 = "Как скажете, офицер. Адиос!";
			link.l1.go = "exit";
			NextDiag.TempNode = "OfficerGuard_Again";
		break;

		case "Soldat15":
			dialog.text = "Cеньор"+ GetSexPhrase("","ита")+", поговорите пожалуйста с доном Франсиско.";
			link.l1 = "Спасибо, солдат, я так и сделаю.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Soldat15";
		break;

		case "RazgovorSGuberom":
			dialog.text = "Буэнас диас, сеньор"+ GetSexPhrase("","ита")+" "+pchar.name+". Вы-то мне и нужны!";
			link.l1 = "Буэнас диас, ваше превосходительство! Чем я могу быть вам "+ GetSexPhrase("полезен","полезна")+"?";
			link.l1.go = "RazgovorSGuberom_2";
			PlayVoice("Kopcapkz\Voices\PDM\Francois de Bijou.wav");
		break;

		case "RazgovorSGuberom_2":
			dialog.text = "(Обращается к стражникам) Оставьте нас.";
			link.l1 = "...";
			link.l1.go = "RazgovorSGuberom_3";
		break;

		case "RazgovorSGuberom_3":
			dialog.text = "Странные вещи здесь творятся, капитан. Моя правая рука, мой секретарь, был найден мёртвым в своей комнате. Кто-то задушил его прямо в постели, его руки были сжаты на горле, а глаза выпучены. Но нет никаких следов верёвки или пальцев на шее. Я не знаю, что всё это значит. Это ужасная трагедия.";
			link.l1 = "Какая странная история. Но как так случилось, что вашим секретарём стал англичанин?";
			link.l1.go = "RazgovorSGuberom_4";
			sld = CharacterFromID("PDM_ONV_SoldatGub_1")
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			LAi_ActorGoToLocator(sld, "goto", "goto3", "STRAJIschezni", 3);
			sld = CharacterFromID("PDM_ONV_SoldatGub_2")
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			LAi_ActorGoToLocator(sld, "goto", "goto3", "STRAJIschezni", 3);
		break;

		case "RazgovorSGuberom_4":
			dialog.text = "Английское правительство сослало его. Они выдвинули против него фальшивые обвинения. Он был очень благородным человеком с прекрасным характером. Мы познакомились пятнадцать лет назад в Европе. Тогда он был молодым дипломатом, мы встречались при дворе. Один из моих агентов пересёкся с ним в Порт-Рояле. Его выбросили на улицу после того, как обвинили в хищении. Лишённый своего титула, он согласился стать моим секретарем.";
			link.l1 = "Кажется, я встречал его. Бартоломью, вы говорите? Кажется, на площади, он искал девушку из таверны по имени Карла.";
			link.l1.go = "RazgovorSGuberom_5";
		break;

		case "RazgovorSGuberom_5":
			dialog.text = "Девушку из таверны? Это очень странно. Он был знатным человеком, как я сказал, у него не могло быть ничего общего с женщиной такой репутации.";
			link.l1 = "Сеньор генерал-губернатор, что вы думаете о его гибели? Кто мог убить его?";
			link.l1.go = "RazgovorSGuberom_6";
		break;

		case "RazgovorSGuberom_6":
			dialog.text = "Это интриги врагов испанской короны, я полагаю. Но не могу назвать никого конкретно.";
			link.l1 = "Надеюсь, сеньор генерал-губернатор, эту загадку можно разрешить. Но у меня есть важные дела, и если вы меня простите...";
			link.l1.go = "RazgovorSGuberom_7";
		break;

		case "RazgovorSGuberom_7":
			dialog.text = "Вообще-то, да, сеньор"+ GetSexPhrase("","ита")+" "+pchar.name+". Вы говорили, что бедный Бартоломью искал девушку из таверны по имени Карла, да? Вы не приведёте её ко мне? Я мог бы послать за ней, но это вызовет волну слухов. Может быть, вы бы могли решить это дело более деликатно. Я решил взять расследование под личный контроль.";
			link.l1 = "Ладно, сеньор генерал-губернатор, если я найду её, конечно, приведу её сюда. Адиос!";
			link.l1.go = "RazgovorSGuberom_COD";
			NextDiag.TempNode = "RazgovorSGuberom_Again";
		break;

		case "RazgovorSGuberom_Again":
			dialog.text = "Я уже вам дал задание, сеньор"+ GetSexPhrase("","ита")+". Что вы хотели ещё спросить?";
			link.l1 = "Я "+ GetSexPhrase("заблудился","заблудилась")+", ваше превосходительство. Я иду искать девушку Карлу. До свидания!";
			link.l1.go = "exit";
			NextDiag.TempNode = "RazgovorSGuberom_Again";
		break;

		case "RazgovorSGuberom_COD":
			LocatorReloadEnterDisable("Havana_Townhall", "reload1_back", false);
			LocatorReloadEnterDisable("Havana_Townhall", "reload3", true);

			PChar.quest.PDM_ONV_SVOBODA_URA.win_condition.l1 = "location";
			PChar.quest.PDM_ONV_SVOBODA_URA.win_condition.l1.location = "Havana_town";
			PChar.quest.PDM_ONV_SVOBODA_URA.win_condition = "PDM_ONV_SVOBODA_URA";

			AddQuestRecord("PDM_Ohota_na_vedmu", "5");
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex1", GetSexPhrase("ся","ась"));
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex2", GetSexPhrase("ен","на"));
			sld = CharacterFromID("PDM_ONV_Sin")
			ChangeCharacterAddressGroup(sld, "none", "", "");

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "RazgovorSViktorom_1":
			dialog.text = "Ты кто так"+ GetSexPhrase("ой","ая")+", "+ GetSexPhrase("парень","девчонка")+"? И что, чёрт тебя раздери, тебе нужно?";
			link.l1 = "Я думал"+ GetSexPhrase("","а")+", что ты торговец, которому, может быть, нужно сопровождение... Но, похоже, я "+ GetSexPhrase("ошибся","ошиблась")+".";
			link.l1.go = "RazgovorSViktorom_2";
			PlayVoice("Kopcapkz\Voices\PDM\Gavrila Dubinin.wav");
			DeleteAttribute(pchar, "questTemp.PDM_ONV_PortoBello");
			DeleteAttribute(pchar, "questTemp.PDM_ONV_SanJuan");
			DeleteAttribute(pchar, "questTemp.PDM_ONV_Maracaibo");
		break;

		case "RazgovorSViktorom_2":
			dialog.text = "Да, "+ GetSexPhrase("приятель, ты ошибся","милая, ты ошиблась")+". Я Силино Сэв, безработный боцман. Вчера один безмозглый обормот предложил мне работать дровосеком. Знаешь, что с ним случилось?";
			link.l1 = "Понятно... Но давай мы посидим за кружкой рома, и ты расскажешь мне свою историю.";
			link.l1.go = "RazgovorSViktorom_3";
		break;

		case "RazgovorSViktorom_3":
			ChangeCharacterAddressGroup(pchar, PChar.location, "sit", "sit_front2");
			LAi_SetSitType(pchar);
			LAi_SetSitType(npchar);
			locCameraTarget(PChar)
            locCameraFollow();
			dialog.text = "Я расскажу тебе, что со мной сучилось - но это не интересная сказка, которую рассказывают детям. Всё произошло из-за этой проклятой ведьмы, которую капитан подобрал в Гаване. Скажу я тебе, если бы он не связался с этой ведьмой, он был бы жив сейчас. Но он всегда был слишком упрямым. Он мог переспорить самого дьявола, наш старый добрый Мигель.\n"+
							"Но после того как эта женщина появилась на борту, он изменился. Да, он изменился. Он высох, словно сушёная вобла. Мы говорили, чтобы он не брал эту женщину с собой - среди моряков считается, что женщина на борту, это к несчастью... когда на борту женщина, жди неприятностей.\n"+
							"И вот из-за этой Карлы...";
			link.l1 = "Подожди! Ты сказал, её зовут Карла? Эту женщину разыскивает дон Франсиско. Он считает, что она может быть причастна к убийству!";
			link.l1.go = "RazgovorSViktorom_4";
		break;

		case "RazgovorSViktorom_4":
			dialog.text = "Да, генерал-губернатор прав. Эта чёртова ведьма убила нашего капитана. Он был мёртв, словно дохлая треска, когда мы достигли Сантьяго. Мы только-только вошли в порт, когда нашли его мёртвым на палубе. Мы бросились искать проклятую ведьму, но она загадочным образом исчезла. И теперь я безработный боцман. Дубина первый помощник в точности выполнил последнюю волю капитана, и продал нашу лоханку, а все деньги пожертвовал Церкви.";
			link.l1 = "Что за адское исчадие эта женщина! Она уничтожила уже двоих людей. Её необходимо остановить.";
			link.l1.go = "RazgovorSViktorom_5";
		break;

		case "RazgovorSViktorom_5":
			dialog.text = "Удачи тебе капитан в её поисках!";
			link.l1 = "Я обязательно её найду. До встречи!";
			link.l1.go = "RazgovorSViktorom_COD";
			NextDiag.TempNode = "RazgovorSViktorom_Again";
		break;

		case "RazgovorSViktorom_COD":
			sld = CharacterFromID("PDM_ONV_Viktor_Martos")
			sld.lifeday = 0;

			AddQuestRecord("PDM_Ohota_na_vedmu", "11");
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","а"));

			ChangeCharacterAddressGroup(pchar, PChar.location, "tables", "stay2");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar)
            locCameraFollow();

			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Carla", "Girl_3", "woman", "woman", 10, SPAIN, -1, false));
			sld.city = "Santiago";
			ChangeCharacterAddressGroup(sld, "Santiago_tavern", "goto", "goto4");
			LAi_SetWaitressType(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			sld.name = "Карла ";
			sld.lastname = "";
			sld.dialog.filename   = "Quest/PDM/Ohota_na_vedmu.c";
			sld.dialog.currentnode   = "Carla_Final_1";

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "RazgovorSViktorom_Again":
			dialog.text = "Удачи тебе капитан в её поисках!";
			link.l1 = "Я обязательно её найду. До встречи!";
			link.l1.go = "exit";
			NextDiag.TempNode = "RazgovorSViktorom_Again";
		break;

		case "Carla_Final_1":
			dialog.text = "О, дорогуша! Что ты делаешь сегодня вечером? Или прямо сейчас?";
			link.l1 = "Наглая ведьма! Ты позволяешь себе продолжать свои нечестивые занятия и склонять честных испанцев к служению дьяволу!? Мне приказано представить тебя к правосудию!";
			link.l1.go = "Carla_Final_2";
			PlayVoice("Kopcapkz\Voices\PDM\Carla.wav");
		break;

		case "Carla_Final_2":
			dialog.text = "Ч-что вы говорите, сеньор"+ GetSexPhrase("","ита")+"? Я н-н-не з-знаю ни о каких преступлениях.";
			link.l1 = "Ты думаешь, что тебе удастся доказать свою невинность, отрицая очевидное? У меня есть свидетель - Виктор Мартос. Он готов дать показания о том, что ты - ведьма.";
			link.l1.go = "Carla_Final_5";
			link.l2 = "У меня есть свидетель - Виктор Мартос. Мигель Куэнда умер на своем корабле недалеко от Сантьяго! И мы ещё узнаем, какую отвратительную роль твоё чародейство сыграло в ужасной смерти Бартоломью Ольстера в Гаване. И... Нет, я передумал"+ GetSexPhrase("","а")+". Я прямо здесь, в этом городе найду на тебя управу. Инквизиция выслушает меня - и моих слов будет достаточно для того, чтобы покарать тебя.";
			link.l2.go = "NaKoster_1";
		break;

		case "Carla_Final_5":
			dialog.text = "Я знаю, что смерть Мигеля была моей виной... Но я не могла ничего поделать - мне надо было избавиться от этого ублюдка Бартоломью. Но когда он всё-таки выговорил своё проклятие - я поняла, что всё кончено. Мигель был обречён. Я любила его...";
			link.l1 = "Погоди. Я ничего не понял"+ GetSexPhrase("","а")+". Какое ещё проклятье? Любила кого?";
			link.l1.go = "Carla_Final_6";
		break;

		case "Carla_Final_6":
			dialog.text = "Бартоломью Ольстер проклял Мигеля, когда он увидел его и понял, что умрёт. Я пыталась спасти Мигеля всю дорогу до Сантьяго, но... тщетно. Моих сил просто не хватило для того, чтобы противостоять силе предсмертного проклятия. Я была всего лишь ученицей, которой не суждено было превзойти учителя.";
			link.l1 = "Так ты сознаёшься, что ты ведьма?";
			link.l1.go = "Carla_Final_7";
		break;

		case "Carla_Final_7":
			dialog.text = "Да. Бартоломью Ольстер был моим наставником в мастерстве ворожбы. Он заметил во мне этот Дар, когда мне было всего четырнадцать. Тогда я была просто глупенькой девочкой, которая не понимала, что творит. Я не была красивой, но он рассказал мне, как покорять сердца мужчин, и я стала всего-навсего дешёвой проституткой. Он использовал меня для того, чтобы выпытывать секреты у клиентов, он провёл меня через все унижения, которые я могла вообразить. Я просто не могла жить больше - он был слишком силён...\n"+
							"Но когда я встретила Мигеля, я подумала, что у меня появилась возможность...  Я полюбила этого отважного капитана... но Бартоломью сказал, что если я попытаюсь сбежать, то он расскажет священникам, что я ведьма, и они сожгут меня на костре. Я рассказала обо всём Мигелю. И он решил, что нам следует убить Ольстера. Мой Дар был слишком слаб, чтобы справиться с ним магически, и я всего лишь слабая женщина. Но Мигель вселил в меня веру.";
			link.l1 = "Но как вы пробрались через стражу?";
			link.l1.go = "Carla_Final_8";
		break;

		case "Carla_Final_8":
			dialog.text = "Это было самое простое. Я насыпала им сонного зелья в питьё... и они заснули как младенцы. После этого, мы прокрались в спальню этого чудовища в человеческом облике.  Но он не спал, как мы надеялись. Я думаю, что он наложил формулу охраны на дверь, которая и разбудила его. Мигель бросился на него, но эта тварь выкрикнула проклятие. И в этот момент я поняла, что они оба мертвы. Проклятия Ольстера всегда сбывались, а это было особенно сильным, потому, что оно стало предсмертным. Мигель боролся с колдуном и задушил его подушкой, в конце концов.\n"+
							"Я пыталась спасти Мигеля всю дорогу до Сантьяго. Но когда он упал мёртвым на палубу, мне пришлось скрыться с корабля. Команда была в ярости - я была единственной женщиной на корабле, которую капитан и пальцем не позволял тронуть. Пока мы плыли, они распалились, как стая диких собак.";
			link.l1 = "И что произошло потом?";
			link.l1.go = "Carla_Final_10";
		break;

		case "Carla_Final_10":
			dialog.text = "Я не знала, что мне делать. Всё, чего я хотела это сбежать от моего прошлого. Когда я прибыла сюда, у меня не было денег, и я вернулась к единственному занятию, которое знаю... И теперь, "+ GetSexPhrase("добрый сеньор","добрая сеньорита")+", после того, как я вам всё рассказала, вы можете арестовать меня, и сжечь на костре, только за то, что я хотела жить, любить, и быть свободной, как человек.";
			link.l1 = "Единственно важная вещь в этом всём состоит в том, что ты ведьма. Поэтому я передам тебя в руки Церкви.";
			link.l1.go = "NaKoster_2";
			link.l2 = "Полагаю, что вы не совершили никакого преступления, Карла. Вы свободны.";
			link.l2.go = "Carla_Final_11";
		break;

		case "Carla_Final_11":
			dialog.text = "О, "+ GetSexPhrase("сеньор","сеньорита")+" - вы очень благородны. Я скажу вам вот что. Все считают, что колдовство, это занятие неугодное Богу. Но я скажу вам, что это просто Дар, или Мастерство, как и любое другое...";
			link.l1 = "";
			link.l1.go = "Carla_Final_12";
		break;

		case "NaKoster_2":
			dialog.text = "Как пожелаете, "+ GetSexPhrase("сеньор","сеньорита")+". Моя жизнь более для меня ничего не значит - я не видела милосердия, не стяжала любви - было бы странно рассчитывать на правосудие.";
			link.l1 = "Не пытайся разжалобить меня, проклятая ведьма! Ты будешь гореть в огне!";
			link.l1.go = "NaKoster_COD";
			NextDiag.TempNode = "NaKoster_Again";
		break;

		case "Carla_Final_12":
			dialog.text = "И примите мой дар. Удача будет сопутствовать вам с этого дня.";
			link.l1 = "Желаю вам удачи, Карла! До встречи.";
			link.l1.go = "Dobro_Final";
			NextDiag.TempNode = "Carla_Final_Again";
			AddBonusEnergyToCharacter(pchar, 25);
			PlaySound("Interface\new_level.wav");
			Log_info("Ваша энергия увеличилась на 25 навсегда.");
		break;

		case "Dobro_Final":
			AddQuestRecord("PDM_Ohota_na_vedmu", "12");
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("PDM_Ohota_na_vedmu");
			ChangeCharacterReputation(pchar, 3);

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Carla_Final_Again":
			dialog.text = "Спасибо вам, "+ GetSexPhrase("добрый сеньор","добрая сеньорита")+", я не забуду вашего благородства!";
			link.l1 = "Удачи вам, Карла!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Carla_Final_Again";
			PlayVoice("Kopcapkz\Voices\PDM\Carla.wav");
		break;

		case "NaKoster_1":
			dialog.text = "Я знаю, что смерть Мигеля была моей виной... Но я не сделала ему ничего плохого - он просто хотел... ах! Вы всё равно мне не поверите. Возьмите меня, сеньор"+ GetSexPhrase("","ита")+" палач - ведите на костёр - моя жизнь более ничего не значит.";
			link.l1 = "Единственно важно во всей этой чепухе то, что ты - ведьма. И я намерен передать тебя Святым Отцам, чтобы они исполнили свой долг.";
			link.l1.go = "NaKoster_COD";
			NextDiag.TempNode = "NaKoster_Again";
		break;

		case "NaKoster_COD":
			sld = CharacterFromID("AntonioDeSouza")
			ChangeCharacterAddressGroup(sld, "Santiago_town", "none", "");

			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Inkvizitor", "priest", "man", "man", 10, SPAIN, -1, false));
			sld.city = "Santiago";
			ChangeCharacterAddressGroup(sld, "Santiago_Incquisitio", "sit", "armchair1");
			LAi_SetHuberType(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			sld.name = "Антонио";
			sld.lastname = "де Соуза";
			sld.model.animation = "man2";
			sld.dialog.filename   = "Quest/PDM/Ohota_na_vedmu.c";
			sld.dialog.currentnode   = "Inqizitor_1";

			AddQuestRecord("PDM_Ohota_na_vedmu", "13");
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","а"));

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NaKoster_Again":
			dialog.text = "Моя жизнь больше ничего не стоит... Но я не потрачу даже минуты из её остатка на разговор с вами.";
			link.l1 = "Ты сгоришь в огне, мерзкая ведьма!";
			link.l1.go = "exit";
			NextDiag.TempNode = "NaKoster_Again";
		break;

		case "Inqizitor_1":
			dialog.text = "Этот город погряз в грехе! Но скоро мы освободим людей из тёмных тенёт Сатаны огнём и волей Господа нашего! Э-э... чего ты хочешь, "+ GetSexPhrase("сын мой","дочь моя") +"?";
			link.l1 = "Святой Отец, я знаю, здесь есть ведьма по имени Карла, бывшая портовая проститутка. Своим тёмным искусством она убила уже двоих - капитана Мигеля Куэнду, и доброго идальго Бартоломью, который умер, не успев покаяться. Он был слугой алькальды дона Франсиско. Я молю Бога, чтобы святая инквизиция покарала её за греховные деяния.";
			link.l1.go = "Inqizitor_2";
			PlayVoice("Kopcapkz\Voices\PDM\Zaharia Marlow-02.wav");
		break;

		case "Inqizitor_2":
			dialog.text = "Ах, да будет душа твоя вечно благословенна за твой праведный поступок, "+ GetSexPhrase("сын мой","дочь моя") +". Мы позаботимся об этой ведьме.";
			link.l1 = "Я надеюсь на это, святой отец. Доброго вам дня.";
			link.l1.go = "KAZN";
			AddBonusEnergyToCharacter(pchar, 25);
			PlaySound("Interface\new_level.wav");
			Log_info("Ваша энергия увеличилась на 25 навсегда.");
		break;

		case "KAZN":
			DoQuestReloadToLocation("Santiago_town", "officers", "reload8_2", "PDM_ONV_KaznVedmi");
			TavernWaitDate("wait_night");
		break;

		case "Inqizitor_Kazn_nachalo_1":
			dialog.text = "Хорошо, что ты пришёл, сын мой. Мы начинаем.\n"+
							"(Обращается к собравшимся) Знайте, еретики-заговорщики прячутся среди нас, прикидываясь добрыми христианами, но церковь защитит вас от таких, как она, злых, нечистых, тёмных сил.";
			link.l1 = "...";
			link.l1.go = "Inqizitor_Kazn_nachalo_2";
			PlaySound("Kopcapkz\Voices\PDM\Witch\Fon.wav");

			sld = CharacterFromID("PDM_ONV_Jitel_1")
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_ONV_Carla"));
			sld = CharacterFromID("PDM_ONV_Jitel_2")
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_ONV_Carla"));
			sld = CharacterFromID("PDM_ONV_Jitel_3")
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_ONV_Carla"));
			sld = CharacterFromID("PDM_ONV_Jitel_4")
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_ONV_Carla"));
			sld = CharacterFromID("PDM_ONV_Jitel_5")
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_ONV_Carla"));
			sld = CharacterFromID("PDM_ONV_Jitel_6")
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_ONV_Carla"));
			sld = CharacterFromID("PDM_ONV_Jitel_7")
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_ONV_Carla"));
			sld = CharacterFromID("PDM_ONV_Jitel_8")
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_ONV_Carla"));
			sld = CharacterFromID("PDM_ONV_Jitel_9")
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_ONV_Carla"));
			sld = CharacterFromID("PDM_ONV_Jitel_10")
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_ONV_Carla"));
			sld = CharacterFromID("PDM_ONV_Jitel_11")
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_ONV_Carla"));
			sld = CharacterFromID("PDM_ONV_Jitel_12")
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_ONV_Carla"));
			sld = CharacterFromID("PDM_ONV_Jitel_13")
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_ONV_Carla"));
			sld = CharacterFromID("PDM_ONV_Jitel_14")
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_ONV_Carla"));
			sld = CharacterFromID("PDM_ONV_Podjigatel")
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_ONV_Carla"));
			sld = CharacterFromID("PDM_ONV_Carla")
			LAi_ActorTurnToCharacter(CharacterFromID("PDM_ONV_Carla"), pchar);
		break;

		case "Inqizitor_Kazn_nachalo_2":
			SetMusic("none");
			sld = CharacterFromID("PDM_ONV_Inkvizitor")
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_ONV_Carla"));
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(pchar, CharacterFromID("PDM_ONV_Jitel_5"));

			PlayVoice("Kopcapkz\Voices\PDM\Witch\Inkvizitor.WAV");
			DoQuestFunctionDelay("PDM_ONV_Kazn", 17.0);
			DoQuestFunctionDelay("PDM_ONV_Kazn_2", 20.0);

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Inqizitor_Kazn_3":
			dialog.text = "(Палач поднёс к поленьям зажжённый факел. Костёр затрещал, заглушая все остальные звуки и только несмолкаемый вой прорывался сквозь стоящее стеной пламя, но скоро он стал обрываться, сменился хрипом и, наконец, смолк...)";
			link.l1 = "...";
			link.l1.go = "Inqizitor_Kazn_4";
			PlaySound("Kopcapkz\Voices\PDM\Witch\fire.wav");

			sld = CharacterFromID("AntonioDeSouza")
			ChangeCharacterAddressGroup(sld, "Santiago_Incquisitio", "sit", "armchair1");
		break;

		case "Inqizitor_Kazn_4":
			SetMusic("none");
			PlaySound("Kopcapkz\Voices\PDM\Witch\Music.wav");
			PlaySound("Kopcapkz\Voices\PDM\Witch\scream.WAV");
			CreateLocationParticles("shipfire", "merchant", "mrcActive2", 0, 0, 0, "");
			LAi_SetActorType(pchar);
			sld = CharacterFromID("PDM_ONV_Podjigatel")
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "houseSp2", "PDM_ONV_PodjIschezni", -1);

			DoQuestFunctionDelay("PDM_ONV_Kazn_3", 8.0);
			DoQuestFunctionDelay("PDM_ONV_Kazn_4", 12.0);

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;


	}
}
