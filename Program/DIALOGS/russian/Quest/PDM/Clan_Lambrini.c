
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int Rank = sti(pchar.rank) - 4 + MOD_SKILL_ENEMY_RATE;
	if (Rank < 1) Rank = 1;
	int Sila = 70 + MOD_SKILL_ENEMY_RATE * 3;
	int DopHP = 60 + MOD_SKILL_ENEMY_RATE * 12;
	int Bonus = sti(pchar.rank);
	if (Bonus <= 6) Bonus = 1;
	if (Bonus >= 7 && Bonus <= 12) Bonus = 1.2;
	if (Bonus >= 13) Bonus = 1.5;
	int Plata1 = 10000 + 1800 * sti(pchar.rank) * Bonus;
	int Plata2 = 20000 + 2000 * sti(pchar.rank) * Bonus;
	int Plata3 = Plata2 * 2;
	pchar.PDM_NK_Plata1.Money = 10000 + 1800 * sti(pchar.rank) * Bonus;
	pchar.PDM_NK_Plata2.Money = 20000 + 2000 * sti(pchar.rank) * Bonus;

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":							//Автор Sinistra
			dialog.text = "Эй, "+ GetSexPhrase("парень","деваха") +"! Это мой столик, и я не ищу компании.";
			link.l1 = "Но ты её уже НАШЕЛ. Так что давай поговорим.";
			link.l1.go = "Octavio_1_1";
			link.l2 = "Я не хочу беспокоить тебя. Прощай.";
			link.l2.go = "exit";
			PlayVoice("Kopcapkz\Voices\PDM\Octavio Lambrini.wav");
		break;

		case "Octavio_1_1":
			dialog.text = "Что? Ты осмеливаешься беспокоить Октавио Ламбрини? Кем же ты себя возомнил"+ GetSexPhrase("","а") +"?";
			if (pchar.name == "Питер" && pchar.lastname == "Блад")
			{
				link.l1 = "Да перед тобой сам "+GetFullName(pchar)+". Капитан, благородный разбойник, врач и спаситель Бриджтауна от испанцев. А имя 'Ламбрини' мне ничего не говорит.";
				link.l1.go = "Octavio_1_2";
			}
			if (pchar.name == "Виспер")
			{
				link.l2 = "Да перед тобой сама "+pchar.name+". Капитан, благородная разбойница, путешественница во времени и побывавшая в самом сердце инквизиции. А имя 'Ламбрини' мне ничего не говорит.";
				link.l2.go = "Octavio_1_2";
			}
			if (pchar.lastname == "Шарп")
			{
				link.l3 = "Моё имя "+GetFullName(pchar)+" - я "+ GetSexPhrase("сын","дочь") +" известного пирата, Николаса Шарпа. А имя 'Ламбрини' мне ничего не говорит.";
				link.l3.go = "Octavio_1_2";
			}
			if (pchar.name == "Шарль" && pchar.lastname == "де Мор")
			{
				link.l4 = "Да перед тобой сам "+GetFullName(pchar)+". Дворянин, капитан, спаситель мира от зловещего Кукулькана. А имя 'Ламбрини' мне ничего не говорит.";
				link.l4.go = "Octavio_1_2";
			}
			if (pchar.lastname == "Хаук")
			{
				link.l6 = "Да перед тобой сам"+ GetSexPhrase("","а") +" "+GetFullName(pchar)+". Капитан, "+ GetSexPhrase("благородный разбойник","благородная разбойница") +" и "+ GetSexPhrase("тот","та") +", кто отправил"+ GetSexPhrase("","а") +" Чёрную Жемчужину на дно. А имя 'Ламбрини' мне ничего не говорит.";
				link.l6.go = "Octavio_1_2";
			}
			if (pchar.lastname == "Кортес")
			{
				link.l7 = "Моё имя "+GetFullName(pchar)+" - я потомок известного конкистадора первооткрывателя, Эрнана Кортеса. А имя 'Ламбрини' мне ничего не говорит.";
				link.l7.go = "Octavio_1_2";
			}
			if (pchar.reputation >= 75)
			{
				link.l8 = "Меня зовут "+GetFullName(pchar)+". Все знают, что я человек чести, и мне можно доверять. А имя 'Ламбрини' мне ничего не говорит.";
				link.l8.go = "Octavio_1_2_DB";
			}
			if (pchar.reputation <= 25)
			{
				link.l8 = "Меня зовут "+GetFullName(pchar)+". И от одного только упоминания моего имени все начинают дрожать и разбегаться в разные стороны. А имя 'Ламбрини' мне ничего не говорит.";
				link.l8.go = "Octavio_1_2_DB";
			}
			if (pchar.reputation >= 0 && pchar.reputation <= 100)
			{
				link.l9 = "Я "+pchar.name+", капитан и "+ GetSexPhrase("наёмник","наёмница") +". А тебя я что-то не припоминаю.";
				link.l9.go = "Octavio_1_2_ostalnoe";
			}
		break;

		case "Octavio_1_2":
			if (pchar.name == "Питер" && pchar.lastname == "Блад")
			{
				dialog.text = "Так это ТЫ тот самый врач, что спас весь город от этих испанцев! Невероятно! Если ты действительно так хорош, как о тебе говорят, то можно и побеседовать.";
			}
			if (pchar.name == "Виспер")
			{
				dialog.text = "Так это ТЫ насолила де Соузу, что весь Сантьяго стоял на ушах! Неплохо! Если ты действительно так хороша, как о тебе говорят, то можно и побеседовать.";
			}
			if (pchar.lastname == "Шарп")
			{
				dialog.text = ""+ GetSexPhrase("Сын","Дочь") +" Николаса Шарпа? Неплохо! Я знал твоего отца, давным-давно, когда Ламбрини только что поселились на этом острове. Твой отец был хорошим человеком. Если ты хоть вполовину так же хорош"+ GetSexPhrase("","а") +" как он, то можно и побеседовать.";
			}
			if (pchar.name == "Шарль" && pchar.lastname == "де Мор")
			{
				dialog.text = "Ты бывал в Теночтитлане и победил самого бога? Невероятно! Если ты действительно так хорош, как о тебе говорят, то можно и побеседовать.";
			}
			if (pchar.lastname == "Хаук")
			{
				dialog.text = "Сам"+ GetSexPhrase("","а") +" "+GetFullName(pchar)+"? Здесь, на Тринидаде? Якорь мне в глотку! Если ты действительно так хорош"+ GetSexPhrase("","а") +", как о тебе говорят, то можно и побеседовать.";
			}
			if (pchar.lastname == "Кортес")
			{
				dialog.text = "Родная кровь Эрнана Кортеса? Неплохо! Твой предок был великим человеком, и если ты хоть вполовину так же хорош"+ GetSexPhrase("","а") +" как он, то можно и побеседовать. ";
			}
			link.l1 = "Чем ты занимаешься?";
			link.l1.go = "Octavio_1_3";
		break;

		case "Octavio_1_2_ostalnoe":
			dialog.text = "Это твоя проблема, "+ GetSexPhrase("мальчик","девочка") +". Семья Ламбрини хорошо известна на этих островах. Лучше тебе держаться от нас подальше.";
			link.l1 = "Ладно, зайду позже, когда стану более "+ GetSexPhrase("известен","известна") +". (Требуется низкая или высокая репутация)";
			link.l1.go = "exit";
		break;

		case "Octavio_1_2_DB":
			dialog.text = ""+GetFullName(pchar)+"? Да, я о тебе наслышан. Если ты действительно так хорош"+ GetSexPhrase("","а") +", как о тебе говорят, то можно и побеседовать.";
			link.l1 = "Чем ты занимаешься?";
			link.l1.go = "Octavio_1_3";
		break;

		case "Octavio_1_3":
			dialog.text = "Я и моя семья обделываем дела по всему карибскому архипелагу. Наши прибыли велики, поскольку мы избегаем платить обременительные налоги на свои грузы. Некоторые называют нас контрабандистами.";
			link.l1 = "Ты упомянул свою семью - кто они?";
			link.l1.go = "Octavio_1_4";
		break;

		case "Octavio_1_4":
			dialog.text = "А! Семья - это очень важный вопрос для Ламбрини. Мы пришли в Новый Свет с Сицилии сорок лет назад. Тогда мой отец распоряжался нашими действиями здесь. После того, как он умер, я стал главой семьи. Теперь я работаю со своими сыновьями - Фабио и Эмилио, и моим племянником, Цезарио.";
			link.l1 = "Я ищу работу. У тебя есть предложения?";
			link.l1.go = "Octavio_1_5";
		break;

		case "Octavio_1_5":
			dialog.text = "Да. Есть проблема, с которой ты можешь нам помочь.";
			link.l1 = "Я слушаю.";
			link.l1.go = "Octavio_1_6";
		break;

		case "Octavio_1_6":
			dialog.text = "Мы контрабандисты. И хотя большая часть береговой стражи не против иметь с нами дело, честный человек среди них может доставить немало неприятностей. Да, с большинством из них вполне можно договориться. Но один - исключение. Этот парень, Аркадио де Гальвес, обладает прекрасным кораблём под названием 'Эль Тибурон'. И этот ублюдок не берёт взятки! Так что мы не можем заниматься своим делом рядом с Маракайбо.";
			link.l1 = "И ты хочешь, чтобы я "+ GetSexPhrase("избавился","избавилась") +" от него?";
			link.l1.go = "Octavio_1_7";
			link.l2 = "Меня это не интересует, Октавио. Если ты хоть вполовину так крут, как утверждаешь, ты и сам справишься с этим парнем. Прощай.";
			link.l2.go = "exit";
		break;

		case "Octavio_1_7":
			if (pchar.name == "Питер" && pchar.lastname == "Блад")
			{
				dialog.text = "Это не столь важно. Убей его, приколоти к своему бушприту, скорми акулам, скорми англичанам, или подкупи его - это неважно. Но мы не можем игнорировать такой вкусный кусочек, как Маракайбо. Другие контрабандисты избегают Маракайбо. Они боятся испанцев - и не без оснований. Если ты и вправду победил испанцев на Барбадоссе, то с этим парнем ты тем более легко разделаешься.";
			}
			if (pchar.name == "Виспер")
			{
				dialog.text = "Это не столь важно. Убей его, приколоти к своему бушприту, скорми акулам, скорми англичанам, или подкупи его - это неважно. Но мы не можем игнорировать такой вкусный кусочек, как Маракайбо. Другие контрабандисты избегают Маракайбо. Они боятся испанцев - и не без оснований. Если ты и вправду смогла насолить де Соузу, то с этим парнем ты тем более легко разделаешься.";
			}
			if (pchar.lastname == "Шарп")
			{
				dialog.text = "Это не столь важно. Убей его, приколоти к своему бушприту, скорми акулам, скорми англичанам, или подкупи его - это неважно. Но мы не можем игнорировать такой вкусный кусочек, как Маракайбо. Другие контрабандисты избегают Маракайбо. Они боятся испанцев - и не без оснований. Но если ты хоть вполовину так "+ GetSexPhrase("хитёр","хитра") +", каким был твой отец - ты с ним справишься.";
			}
			if (pchar.name == "Шарль" && pchar.lastname == "де Мор")
			{
				dialog.text = "Это не столь важно. Убей его, приколоти к своему бушприту, скорми акулам, скорми англичанам, или подкупи его - это неважно. Но мы не можем игнорировать такой вкусный кусочек, как Маракайбо. Другие контрабандисты избегают Маракайбо. Они боятся испанцев - и не без оснований. Если ты и вправду смог победить Кукулькана, то с этим парнем ты тем более легко разделаешься.";
			}
			if (pchar.lastname == "Хаук")
			{
				dialog.text = "Это не столь важно. Убей его, приколоти к своему бушприту, скорми акулам, скорми англичанам, или подкупи его - это неважно. Но мы не можем игнорировать такой вкусный кусочек, как Маракайбо. Другие контрабандисты избегают Маракайбо. Они боятся испанцев - и не без оснований. Если ты и вправду потопил"+ GetSexPhrase("","а") +" Чёрную Жемчужину, то с этим парнем ты тем более легко разделаешься.";
			}
			if (pchar.lastname == "Кортес")
			{
				dialog.text = "Это не столь важно. Убей его, приколоти к своему бушприту, скорми акулам, сожги на костре, или подкупи его - это неважно. Но мы не можем игнорировать такой вкусный кусочек, как Маракайбо. Другие контрабандисты избегают Маракайбо. Они боятся испанцев - и не без оснований. В тебе льётся кровь великого конкистадора, если ты хоть вполовину также "+ GetSexPhrase("хитёр","хитра") +" как и он, то с этим парнем ты тем более легко разделаешься.";
			}
			if (pchar.reputation >= 75)
			{
				dialog.text = "Это не столь важно. Убей его, приколоти к своему бушприту, скорми акулам, скорми англичанам, или подкупи его - это неважно. Но мы не можем игнорировать такой вкусный кусочек, как Маракайбо. Другие контрабандисты избегают Маракайбо. Они боятся испанцев - и не без оснований. Если тебя и вправду зовут "+GetFullName(pchar)+", то с этим парнем ты тем более легко разделаешься.";
			}
			if (pchar.reputation <= 25)
			{
				dialog.text = "Это не столь важно. Убей его, приколоти к своему бушприту, скорми акулам, скорми англичанам, или подкупи его - это неважно. Но мы не можем игнорировать такой вкусный кусочек, как Маракайбо. Другие контрабандисты избегают Маракайбо. Они боятся испанцев - и не без оснований. Если тебя и вправду зовут "+GetFullName(pchar)+", то с этим парнем ты тем более легко разделаешься.";
			}
			link.l1 = "Сколько?";
			link.l1.go = "Octavio_1_8";
			link.l2 = "Меня это не интересует, Октавио. Если ты хоть вполовину так крут, как утверждаешь, ты и сам справишься с этим парнем. Прощай.";
			link.l2.go = "exit";
		break;

		case "Octavio_1_8":
			dialog.text = "" + Plata1 + " золотых. И знай - никто не торгуется с Ламбрини!";
			link.l1 = ""+ GetSexPhrase("Согласен","Согласна") +".";
			link.l1.go = "Octavio_1_9";
			link.l2 = "Меня это не интересует, Октавио. Если ты хоть вполовину так крут, как утверждаешь, ты и сам справишься с этим парнем. Прощай.";
			link.l2.go = "exit";
		break;

		case "Octavio_1_9":
			if (pchar.name == "Питер" && pchar.lastname == "Блад")
			{
				dialog.text = "Йо-хо, мальчик! Говоришь, как истинный врач. Мало слов, много дела. Теперь я не дам и сантима за жизнь этого де Гальвеса. Иди - и возвращайся, когда позаботишься о нём.";
			}
			if (pchar.name == "Виспер")
			{
				dialog.text = "Йо-хо, девочка с фиолетовыми волосами! Говоришь, как истинная Виспер. Мало слов, много дела. Теперь я не дам и сантима за жизнь этого де Гальвеса. Иди - и возвращайся, когда позаботишься о нём.";
			}
			if (pchar.lastname == "Шарп")
			{
				dialog.text = "Йо-хо, "+ GetSexPhrase("мальчик","девочка") +"! Да ты мне напоминаешь своего отца, истинного Шарпа. Мало слов, много дела. Теперь я не дам и сантима за жизнь этого де Гальвеса. Иди - и возвращайся, когда позаботишься о нём.";
			}
			if (pchar.name == "Шарль" && pchar.lastname == "де Мор")
			{
				dialog.text = "Йо-хо, "+ GetSexPhrase("мальчик","девочка") +"! Говоришь, как истинный дворянин. Мало слов, много дела. Теперь я не дам и сантима за жизнь этого де Гальвеса. Иди - и возвращайся, когда позаботишься о нём.";
			}
			if (pchar.lastname == "Хаук")
			{
				dialog.text = "Йо-хо, "+ GetSexPhrase("мальчик","девочка") +"! Говоришь, как истинный легендарный Хаук. Мало слов, много дела. Теперь я не дам и сантима за жизнь этого де Гальвеса. Иди - и возвращайся, когда позаботишься о нём.";
			}
			if (pchar.lastname == "Кортес")
			{
				dialog.text = "Йо-хо, "+ GetSexPhrase("мальчик","девочка") +"! Говоришь, как истинный Эрнан Кортес. Мало слов, много дела. Теперь я не дам и сантима за жизнь этого де Гальвеса. Иди - и возвращайся, когда позаботишься о нём.";
			}
			if (pchar.reputation >= 75)
			{
				dialog.text = "Йо-хо, "+ GetSexPhrase("мальчик","девочка") +"! Говоришь, как "+ GetSexPhrase("истинный","истинная") +" "+GetFullName(pchar)+". Мало слов, много дела. Теперь я не дам и сантима за жизнь этого де Гальвеса. Иди - и возвращайся, когда позаботишься о нём.";
			}
			if (pchar.reputation <= 25)
			{
				dialog.text = "Йо-хо, "+ GetSexPhrase("мальчик","девочка") +"! Говоришь, как "+ GetSexPhrase("истинный","истинная") +" "+GetFullName(pchar)+". Мало слов, много дела. Теперь я не дам и сантима за жизнь этого де Гальвеса. Иди - и возвращайся, когда позаботишься о нём.";
			}
			link.l1 = "До встречи, Октавио.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Octavio_1_10_EsheRaz";

			sld = GetCharacter(NPC_GenerateCharacter("PDM_CL_Antonio", "SpaOfficer2", "man", "man", Rank, SPAIN, -1, false));
			sld.name = "Антонио";
			sld.lastname = "де Гальвес";
			sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			sld.dialog.currentnode   = "Antonio_1_1";
			sld.greeting = "GR_Spainguard";
			FantomMakeCoolFighter(sld, Rank, Sila, Sila, "blade30", "pistol2", DopHP);
			sld.SaveItemsForDead = true;
			LAi_SetWarriorType(sld);
			LAi_SetLoginTime(sld, 12.0, 16.00);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			sld.city = "Maracaibo";
			ChangeCharacterAddressGroup(sld,"Maracaibo_town","goto","goto13");

			sld = GetCharacter(NPC_GenerateCharacter("PDM_CL_Anto2", "SpaOfficer2", "man", "man", Rank, SPAIN, -1, false));	//ВТОРОЙ
			sld.name = "Антонио";
			sld.lastname = "де Гальвес";
			FantomMakeCoolFighter(sld, Rank, Sila, Sila, "blade30", "pistol2", DopHP);
			sld.SaveItemsForDead = true;
			sld.greeting = "GR_Spainguard";
			if (pchar.rank <= 9)
			{
				FantomMakeCoolSailor(sld, SHIP_BRIGHEAVY, "Эль Тибурон", CANNON_TYPE_CULVERINE_LBS16, 100, 100, 100);
			}
			if (pchar.rank >= 10 && pchar.rank <= 14)
			{
				FantomMakeCoolSailor(sld, SHIP_FRIGATEMEDIUM, "Эль Тибурон", CANNON_TYPE_CULVERINE_LBS16, 100, 100, 100);
			}
			if (pchar.rank >= 15 && pchar.rank <= 19)
			{
				FantomMakeCoolSailor(sld, SHIP_DUTCHPINNACE, "Эль Тибурон", CANNON_TYPE_CULVERINE_LBS24, 100, 100, 100);
			}
			if (pchar.rank >= 20 && pchar.rank <= 25)
			{
				FantomMakeCoolSailor(sld, SHIP_FRIGATE_SAT, "Эль Тибурон", CANNON_TYPE_CULVERINE_LBS24, 100, 100, 100);
			}
			if (pchar.rank >= 26 && pchar.rank <= 32)
			{
				FantomMakeCoolSailor(sld, SHIP_LINESHIPHEAVY, "Эль Тибурон", CANNON_TYPE_CANNON_LBS32, 100, 100, 100);
			}
			if (pchar.rank >= 33)
			{
				FantomMakeCoolSailor(sld, SHIP_SHARK, "Эль Тибурон", CANNON_TYPE_CANNON_LBS42, 100, 100, 100);
			}
			sld.ship.Crew.Morale = Sila;								//Мораль
			ChangeCrewExp(sld, "Sailors", Sila);						//Матросы
			ChangeCrewExp(sld, "Cannoners", Sila);					//Канониры
			ChangeCrewExp(sld, "Soldiers", Sila);						//Солдаты
			sld.DontRansackCaptain = true; 							//Квестовые не сдаются
			sld.SinkTenPercent = false; 								//Уходит с повреждениями
			sld.SaveItemsForDead = true;							//Сохранить предметы после смерти
			sld.DontClearDead = true;								//не убирать труп через 200с
			sld.AnalizeShips = true;
			Group_FindOrCreateGroup("PDM_el_tib");					//Название группы
			Group_SetType("PDM_el_tib", "war");						//Тип поведения
			Group_AddCharacter("PDM_el_tib", "PDM_CL_Anto2");		//Добавить капитана

			Group_SetGroupCommander("PDM_el_tib", "PDM_CL_Anto2");
			Group_SetTaskAttack("PDM_el_tib", PLAYER_GROUP);
			Group_SetAddress("PDM_el_tib", "Maracaibo", "quest_ships", "reload_fort1");	//Установить местоположение
			Group_LockTask("PDM_el_tib");

			PChar.quest.PDM_CL_Antonio_Ubit.win_condition.l1 = "NPC_Death";
			PChar.quest.PDM_CL_Antonio_Ubit.win_condition.l1.character = "PDM_CL_Antonio";
			PChar.quest.PDM_CL_Antonio_Ubit.win_condition = "PDM_CL_Antonio_Ubit";

			PChar.quest.PDM_CL_Antonio_Ubit2.win_condition.l1 = "NPC_Death";
			PChar.quest.PDM_CL_Antonio_Ubit2.win_condition.l1.character = "PDM_CL_Anto2";
			PChar.quest.PDM_CL_Antonio_Ubit2.win_condition = "PDM_CL_Antonio_Ubit";

			pchar.questTemp.PDM_CL_Ishem = "Ishem";
			pchar.questTemp.PDM_CL_Tavern = "Tavern";

			SetQuestHeader("PDM_Clan_Lambrini");
			AddQuestRecord("PDM_Clan_Lambrini", "1");
			AddQuestUserData("PDM_Clan_Lambrini", "sSex", GetSexPhrase("","а"));
		break;

		case "Octavio_1_10_EsheRaz":
			dialog.text = "Ну, "+ GetSexPhrase("мальчик","девочка") +" - ты прикончил"+ GetSexPhrase("","а") +" этого червяка, де Гальвеса?";
			link.l1 = "Я вырву ему глаза, не сомневайся. Но всему своё время.";
			link.l1.go = "Octavio_1_11_EsheRaz";
		break;

		case "Octavio_1_11_EsheRaz":
			dialog.text = "Тогда я дам тебе время, "+ GetSexPhrase("мальчик","девочка") +", но помни - Ламбрини не отличаются терпением.";
			link.l1 = "Будь уверен - я не заставлю тебя долго ждать. Прощай.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Octavio_1_10_EsheRaz";
		break;

		case "Antonio_1_1":
			dialog.text = "Что вы хотели, сеньор"+ GetSexPhrase("","ита") +"?";
			link.l1 = "Вас зовут Аркадио де Гальвес - и вы из береговой стражи?";
			link.l1.go = "Antonio_1_2";
		break;

		case "Antonio_1_2":
			dialog.text = "Да. А вы кто так"+ GetSexPhrase("ой","ая") +"?";
			link.l1 = "Моё имя "+GetFullName(pchar)+".";
			link.l1.go = "Antonio_1_3";
		break;

		case "Antonio_1_3":
			dialog.text = "Да, да, я что-то о вас слышал... Зачем вы здесь?";
			link.l1 = "Семья Ламбрини передаёт вам привет! (напасть)";
			link.l1.go = "Antonio_Bitva";
			link.l2 = "Кое-кто хочет убить вас. (предать Ламбрини)";
			link.l2.go = "Antonio_1_4";
			link.l3 = "Мне пора.";
			link.l3.go = "exit";
			NextDiag.TempNode = "Antonio_1_1";
		break;

		case "Antonio_Bitva":
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_SetRelation("SPAIN_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("SPAIN_CITIZENS", LAI_GROUP_PLAYER, false);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Octavio_2_1":
			dialog.text = "Ну, "+ GetSexPhrase("мальчик","девочка") +" - надеюсь, ты прикончил"+ GetSexPhrase("","а") +" этого червяка, де Гальвеса?";
			link.l1 = "Да. Несчастный ублюдок умолял меня о милосердии, но его мольбы были тщетны.";
			link.l1.go = "Octavio_2_2";
		break;

		case "Octavio_2_2":
			if (pchar.reputation >= 75)
			{
				dialog.text = "Ха, "+ GetSexPhrase("мальчик","девочка") +"! Тебе следовало бы принести его голову в доказательство. Вот был бы славный сувенир. Но я верю тебе и так - разумеется, ведь о тебе все говорят как о честном человеке. Вот твои " + Plata1 + ". И все мои проблемы позади.";
			}
			if (pchar.reputation <= 25)
			{
				dialog.text = "Ха, "+ GetSexPhrase("мальчик","девочка") +"! Тебе следовало бы принести его голову в доказательство. Вот был бы славный сувенир. Но я верю тебе и так - разумеется, ведь о тебе все говорят как о безжалостном человеке. Вот твои " + Plata1 + ". И все мои проблемы позади.";
			}
			if (pchar.name == "Питер" && pchar.lastname == "Блад")
			{
				dialog.text = "Ха, мальчик! Тебе следовало бы принести его голову в доказательство. Вот был бы славный сувенир. Но я верю тебе и так - разумеется, ведь ты спаситель Бриджтауна от испанцев. Вот твои " + Plata1 + ". И все мои проблемы позади.";
			}
			if (pchar.name == "Виспер")
			{
				dialog.text = "Ха, девочка! Тебе следовало бы принести его голову в доказательство. Вот был бы славный сувенир. Но я верю тебе и так - разумеется, ведь ты напакостила самому де Соузу. Вот твои " + Plata1 + ". И все мои проблемы позади.";
			}
			if (pchar.lastname == "Шарп")
			{
				dialog.text = "Ха, "+ GetSexPhrase("мальчик","девочка") +"! Тебе следовало бы принести его голову в доказательство. Вот был бы славный сувенир. Но я верю тебе и так - разумеется, ведь ты "+ GetSexPhrase("сын","дочь") +" Николаса Шарпа, великого пирата. Вот твои " + Plata1 + ". И все мои проблемы позади.";
			}
			if (pchar.name == "Шарль" && pchar.lastname == "де Мор")
			{
				dialog.text = "Ха, мальчик! Тебе следовало бы принести его голову в доказательство. Вот был бы славный сувенир. Но я верю тебе и так - разумеется, ведь ты победил самого Кукулькана. Вот твои " + Plata1 + ". И все мои проблемы позади.";
			}
			if (pchar.lastname == "Хаук")
			{
				dialog.text = "Ха, "+ GetSexPhrase("мальчик","девочка") +"! Тебе следовало бы принести его голову в доказательство. Вот был бы славный сувенир. Но я верю тебе и так - разумеется, ведь ты "+ GetSexPhrase("тот","та") +", кто потопил"+ GetSexPhrase("","а") +" Чёрную Жемчужину. Вот твои " + Plata1 + ". И все мои проблемы позади.";
			}
			if (pchar.lastname == "Кортес")
			{
				dialog.text = "Ха, "+ GetSexPhrase("мальчик","девочка") +"! Тебе следовало бы принести его голову в доказательство. Вот был бы славный сувенир. Но я верю тебе и так - разумеется, ведь в тебе течёт кровь Эрнана Кортеса, великого конкистадора. Вот твои " + Plata1 + ". И все мои проблемы позади.";
			}
			link.l1 = "Да, теперь никто не помешает тебе торговать в Маракайбо, Октавио. Прощай.";
			link.l1.go = "exit";
			sld = CharacterFromID("PDM_Octavio_Lambrini")
			sld.lifeday = 0;
			AddMoneyToCharacter(pchar, sti(Plata1));
			ChangeCharacterReputation(pchar, 2);
			ChangeCharacterNationReputation(pchar, SPAIN, -6);
			AddCharacterExpToSkill(pchar, "Leadership", 130);
			AddCharacterExpToSkill(pchar, "FencingLight", 130);
			AddCharacterExpToSkill(pchar, "Fencing", 130);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 130);
			AddCharacterExpToSkill(pchar, "Pistol", 130);
			AddCharacterExpToSkill(pchar, "Fortune", 130);
			AddCharacterExpToSkill(pchar, "Sneak", 130);
			AddCharacterExpToSkill(pchar, "Sailing", 130);
			AddCharacterExpToSkill(pchar, "Accuracy", 130);
			AddCharacterExpToSkill(pchar, "Cannons", 130);
			AddCharacterExpToSkill(pchar, "Grappling", 130);
			AddCharacterExpToSkill(pchar, "Defence", 130);
			AddCharacterExpToSkill(pchar, "Repair", 130);
			NextDiag.TempNode = "Octavio_2_3_EsheRaz";
			CloseQuestHeader("PDM_Clan_Lambrini");
		break;

		case "Octavio_2_3_EsheRaz":
			dialog.text = "А, "+pchar.name+"! Я поздравляю тебя с избавлением нас от этого червяка, де Гальвеса! В скором времени я направляюсь в Маракайбо, чтобы заключить контракты с выгодными клиентами.";
			link.l1 = "Удачи!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Octavio_2_3_EsheRaz";
		break;

		case "Antonio_1_4":
			dialog.text = "И что из этого? Если вы хотели сделать мне сюрприз, то он не удался. Ламбрини хочет меня убить, впрочем, как и остальные контрабандисты были бы не прочь.";
			link.l1 = "Я "+ GetSexPhrase("пришёл","пришла") +" к вам с предложением.";
			link.l1.go = "Antonio_1_5";
		break;

		case "Antonio_1_5":
			dialog.text = "Э нет, я не беру взяток от торговцев. И я обязательно доложу о вас сеньору Алькальду!";
			link.l1 = "Ламбрини был прав на счёт вас! (напасть)";
			link.l1.go = "Antonio_Bitva";
			link.l2 = "Что вы сказали бы, если бы я предоставил"+ GetSexPhrase("","а") +" вам возможность поймать или потопить корабль Ламбрини?";
			link.l2.go = "Antonio_1_6";
			link.l3 = "Что же, тогда прощайте.";
			link.l3.go = "exit";
		break;

		case "Antonio_1_6":
			dialog.text = "Я бы отдал за это мою правую руку. Но это невозможно, увы. Он уже подкупил, кажется, каждого таможенника на Карибах. Что я могу сделать в одиночку?";
			link.l1 = "Ламбрини предложил мне помочь ему избавиться от вас. Он уверен, что ему в одиночку с вами не справиться, но я мог"+ GetSexPhrase("","ла") +" бы сделать это.";
			link.l1.go = "Antonio_1_7";
		break;

		case "Antonio_1_7":
			dialog.text = "Если вы работаете на контрабандистов, то нам с вами разговаривать не о чем, сеньор"+ GetSexPhrase("","ита") +". Прощайте.";
			link.l1 = "Э, погодите - вы меня даже не выслушали. Я могу сказать Ламбрини, что утопил"+ GetSexPhrase("","а") +" ваш корабль. После этого, он рано или поздно приплывёт сюда, думая, что ему больше ничего не грозит. А вы сможете подстеречь его в бухте, или рядом с ней.";
			link.l1.go = "Antonio_1_8";
			link.l2 = "Ну тогда прощайте.";
			link.l2.go = "exit";
		break;

		case "Antonio_1_8":
			dialog.text = "Любопытно... Этот план может сработать, сеньор"+ GetSexPhrase("","ита") +" "+pchar.name+". А если он сработает, я добьюсь, чтобы сеньор Алькальд щедро вознаградил вас!";
			link.l1 = "И сколько, по-вашему, может Его Превосходительство заплатить за голову Ламбрини?";
			link.l1.go = "Antonio_1_9";
		break;

		case "Antonio_1_9":
			dialog.text = "Ну, об этом стоит спросить у Его Превосходительства. Я полагаю, примерно " + Plata2 + ". Наши доходы в последнее время очень снизились из-за контрабандистов.";
			link.l1 = "Думаю, что " + Plata2 + " - это достаточная плата. Итак, я скажу Октавио Ламбрини, что с вами покончено... Когда он приплывёт сюда, мы его здесь сцапаем. Что может быть проще?";
			link.l1.go = "Antonio_1_10";
		break;

		case "Antonio_1_10":
			dialog.text = "Как только сообщите Ламбрини о моей смерти - сразу же возвращайтесь ко мне, я буду ждать вас в церкви с 9 утра до часу дня. Мы придумаем, что делать дальше.";
			link.l1 = "Берегите себя, сеньор. Удачи!";
			link.l1.go = "Antonio_1_11";
			NextDiag.TempNode = "Antonio_1_12";
		break;

		case "Antonio_1_11":
			sld = CharacterFromID("PDM_Octavio_Lambrini")
			sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			sld.dialog.currentnode   = "Octavio_3_1";
			DeleteAttribute(pchar, "questTemp.PDM_CL_Tavern");
			DeleteAttribute(pchar, "questTemp.PDM_CL_Ishem");
			PChar.quest.PDM_CL_Antonio_Ubit.over = "yes";
			AddQuestRecord("PDM_Clan_Lambrini", "4");
			AddQuestUserData("PDM_Clan_Lambrini", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("PDM_Clan_Lambrini", "sSex2", GetSexPhrase("ся","ась"));

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Antonio_1_12":
			dialog.text = "Как только сообщите Ламбрини о моей смерти - сразу же возвращайтесь ко мне, я буду ждать вас в церкви с 9 утра до 2 часов дня. Мы придумаем, что делать дальше.";
			link.l1 = "Берегите себя, сеньор. Удачи!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Antonio_1_12";
		break;

		case "Octavio_3_1":
			dialog.text = "Ну, "+ GetSexPhrase("мальчик","девочка") +" - надеюсь, ты прикончил"+ GetSexPhrase("","а") +" этого червяка, де Гальвеса?";
			link.l1 = "Да. Несчастный ублюдок умолял меня о милосердии, но его мольбы были тщетны.";
			link.l1.go = "Octavio_3_2";
		break;

		case "Octavio_3_2":
			if (pchar.reputation >= 75)
			{
				dialog.text = "Ха, "+ GetSexPhrase("мальчик","девочка") +"! Тебе следовало бы принести его голову в доказательство. Вот был бы славный сувенир. Но я верю тебе и так - разумеется, ведь о тебе все говорят как о честном человеке. Вот твои " + Plata1 + ". И все мои проблемы позади.";
			}
			if (pchar.reputation <= 25)
			{
				dialog.text = "Ха, "+ GetSexPhrase("мальчик","девочка") +"! Тебе следовало бы принести его голову в доказательство. Вот был бы славный сувенир. Но я верю тебе и так - разумеется, ведь о тебе все говорят как о безжалостном человеке. Вот твои " + Plata1 + ". И все мои проблемы позади.";
			}
			if (pchar.name == "Питер" && pchar.lastname == "Блад")
			{
				dialog.text = "Ха, мальчик! Тебе следовало бы принести его голову в доказательство. Вот был бы славный сувенир. Но я верю тебе и так - разумеется, ведь ты спаситель Бриджтауна от испанцев. Вот твои " + Plata1 + ". И все мои проблемы позади.";
			}
			if (pchar.name == "Виспер")
			{
				dialog.text = "Ха, девочка! Тебе следовало бы принести его голову в доказательство. Вот был бы славный сувенир. Но я верю тебе и так - разумеется, ведь ты напакостила самому де Соузу. Вот твои " + Plata1 + ". И все мои проблемы позади.";
			}
			if (pchar.lastname == "Шарп")
			{
				dialog.text = "Ха, "+ GetSexPhrase("мальчик","девочка") +"! Тебе следовало бы принести его голову в доказательство. Вот был бы славный сувенир. Но я верю тебе и так - разумеется, ведь ты "+ GetSexPhrase("сын","дочь") +" Николаса Шарпа, великого пирата. Вот твои " + Plata1 + ". И все мои проблемы позади.";
			}
			if (pchar.name == "Шарль" && pchar.lastname == "де Мор")
			{
				dialog.text = "Ха, мальчик! Тебе следовало бы принести его голову в доказательство. Вот был бы славный сувенир. Но я верю тебе и так - разумеется, ведь ты победил самого Кукулькана. Вот твои " + Plata1 + ". И все мои проблемы позади.";
			}
			if (pchar.lastname == "Хаук")
			{
				dialog.text = "Ха, "+ GetSexPhrase("мальчик","девочка") +"! Тебе следовало бы принести его голову в доказательство. Вот был бы славный сувенир. Но я верю тебе и так - разумеется, ведь ты "+ GetSexPhrase("тот","та") +", кто потопил"+ GetSexPhrase("","а") +" Чёрную Жемчужину. Вот твои " + Plata1 + ". И все мои проблемы позади.";
			}
			if (pchar.lastname == "Кортес")
			{
				dialog.text = "Ха, "+ GetSexPhrase("мальчик","девочка") +"! Тебе следовало бы принести его голову в доказательство. Вот был бы славный сувенир. Но я верю тебе и так - разумеется, ведь в тебе течёт кровь Эрнана Кортеса, великого конкистадора. Вот твои " + Plata1 + ". И все мои проблемы позади.";
			}
			link.l1 = "Да, теперь никто не помешает тебе торговать в Маракайбо, Октавио. Прощай.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Octavio_3_3_EsheRaz";
			sld = CharacterFromID("PDM_Octavio_Lambrini")
			sld.lifeday = 0;
			AddMoneyToCharacter(pchar, sti(Plata1));
			ChangeCharacterReputation(pchar, -2);
			ChangeCharacterNationReputation(pchar, SPAIN, 6);
			AddCharacterExpToSkill(pchar, "Sneak", 160);
			AddCharacterExpToSkill(pchar, "Sailing", 100);

			PChar.quest.PDM_CL_Ubrat_Lodku.win_condition.l1 = "ExitFromLocation";
			PChar.quest.PDM_CL_Ubrat_Lodku.win_condition.l1.location = PChar.location;
			PChar.quest.PDM_CL_Ubrat_Lodku.function = "PDM_CL_Ubrat_Lodku";
			AddQuestRecord("PDM_Clan_Lambrini", "5");
			AddQuestUserData("PDM_Clan_Lambrini", "sSex", GetSexPhrase("","а"));
		break;

		case "Octavio_3_3_EsheRaz":
			dialog.text = "А, "+pchar.name+"! Я поздравляю тебя с избавлением нас от этого червяка, де Гальвеса! В скором времени я направляюсь в Маракайбо, чтобы заключить контракты с выгодными клиентами.";
			link.l1 = "Удачи!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Octavio_3_3_EsheRaz";
		break;

		case "Antonio_2_1":
			dialog.text = "Ола, сеньор"+ GetSexPhrase("","ита") +" "+pchar.name+", как всё прошло?";
			link.l1 = "Октавио Ламбрини поверил в вашу смерть, скорее всего он уже плывёт сюда, в Маракайбо.";
			link.l1.go = "Antonio_2_2";
		break;

		case "Antonio_2_2":
			dialog.text = "Отлично. Контрабандисты любят ошиваться в таверне, вам нужно зайти туда и посмотреть, объявился ли он там.";
			link.l1 = "Хорошо, я поищу его в таверне.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Antonio_2_3_EsheRaz";

			PChar.quest.PDM_CL_PVT.win_condition.l1 = "location";		//Вход в локацию
			PChar.quest.PDM_CL_PVT.win_condition.l1.location = "Maracaibo_tavern";
			PChar.quest.PDM_CL_PVT.win_condition = "PDM_CL_PVT";

			sld = GetCharacter(NPC_GenerateCharacter("PDM_Octavio_Lambrini", "barmen_3", "man", "man", 10, PIRATE, -1, false));
			sld.name	= "Октавио";
			sld.lastname	= "Ламбрини";
			sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			sld.dialog.currentnode   = "Octavio_4_1";
			LAi_SetSitType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			FreeSitLocator("Maracaibo_tavern", "sit_base2");  // очистим стул
			FreeSitLocator("Maracaibo_tavern", "sit_front2");  // очистим стул
			ChangeCharacterAddressGroup(sld, "Maracaibo_tavern", "sit", "sit_front2");

			pchar.LambriniPGG = SelectRandomPGG("woman", "YokoDias");

			if (pchar.LambriniPGG == "")
			{
				pchar.LambriniPGG = "PDM_CL_Pokupatel";
				if(pchar.name == "Виктория")
				{
					sld = GetCharacter(NPC_GenerateCharacter("PDM_CL_Pokupatel", "PGG_Cirilla_7", "woman", "YokoDias", 10, PIRATE, -1, false));
				}
				else
				{
					sld = GetCharacter(NPC_GenerateCharacter("PDM_CL_Pokupatel", "PGG_Victori_8", "woman", "YokoDias", 10, PIRATE, -1, false));
				}
				sld.name	= "Марилиса";
				sld.lastname	= "Ринн";
			}
			else sld = CharacterFromID(pchar.LambriniPGG);

			sld.PGGAi.DontUpdate = true;
			sld.PGGAi.Task.SetSail = true;
			DeleteAttribute(sld, "PGG_warrior");
			DeleteAttribute(sld, "PGG_trader");

			SaveOldDialog(sld);
			sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			sld.dialog.currentnode   = "Pokupatel_1_1";
			LAi_SetSitType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Maracaibo_tavern", "sit", "sit_base2");

			AddQuestRecord("PDM_Clan_Lambrini", "6");
			AddQuestUserData("PDM_Clan_Lambrini", "sSex", GetSexPhrase("","а"));
		break;

		case "Antonio_2_3_EsheRaz":
			dialog.text = "Ну что, сеньор"+ GetSexPhrase("","ита") +", вы видели Ламбрини в таверне?";
			link.l1 = "Ещё нет, я как раз туда и собирал"+ GetSexPhrase("ся","ась") +".";
			link.l1.go = "exit";
			NextDiag.TempNode = "Antonio_2_3_EsheRaz";
		break;

		case "Pokupatel_1_1":
			dialog.text = "Чего тебе? Не видишь, я занят"+ NPCharSexPhrase(NPChar,"","а") +"?";
			link.l1 = "Прошу прощения, не хотел"+ GetSexPhrase("","а") +" тебе мешать.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pokupatel_1_1";
		break;

		case "Octavio_4_1":
			dialog.text = "(Подслушиваем Октавио. Он в данный момент ведёт диалог со своим предполагаемым клиентом) ...Зачем же?";
			link.l1 = "";
			link.l1.go = "Pokupatel_2_1";

			sld = CharacterFromID(pchar.LambriniPGG);
			if (sld.location == "None") FreeSitLocator("Maracaibo_tavern", "sit_base2");  // очистим стул
			DoQuestCheckDelay("PDM_CL_PVT", 0.0);
		break;

		case "Pokupatel_2_1":
			sld = characterFromID(pchar.LambriniPGG);
			sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			sld.dialog.currentnode   = "Pokupatel_2_2";
			DialogExit();
			DoQuestFunctionDelay("PDM_CL_Pokupatel_Speech", 0);
		break;

		case "Pokupatel_2_2":
			dialog.text = "(обращается к Октавио) Хочу продать то, что не купит ни один торговец на этом острове. В моём трюме лежит товар мечты! Горы сандала, только подумай, а.";
			link.l1 = "";
			link.l1.go = "Pokupatel_2_3";
		break;

		case "Pokupatel_2_3":
			sld = characterFromID("PDM_Octavio_Lambrini");
			sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			sld.dialog.currentnode   = "Pokupatel_2_4";
			DialogExit();
			DoQuestFunctionDelay("PDM_CL_Octavio_Speech", 0);
		break;

		case "Pokupatel_2_4":
			npchar.lifeday = 0;
			dialog.text = "(обращается к клиенту) Я знаю, с тобой можно иметь дело. Мы будем ждать тебя в месте, называющемся бухта Гуахира.";
			link.l1 = "";
			link.l1.go = "Pokupatel_2_5";
		break;

		case "Pokupatel_2_5":
			sld = characterFromID(pchar.LambriniPGG);
			sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			sld.dialog.currentnode   = "Pokupatel_2_6";
			DialogExit();
			DoQuestFunctionDelay("PDM_CL_Pokupatel_Speech", 0);
		break;

		case "Pokupatel_2_6":
			dialog.text = "(обращается к Октавио) Я обязательно приду, пупсик.";
			link.l1 = "";
			link.l1.go = "Pokupatel_2_7";
		break;

		case "Pokupatel_2_7":
			sld = characterFromID("PDM_Octavio_Lambrini");
			LAi_CharacterDisableDialog(sld);
			sld = characterFromID(pchar.LambriniPGG);

			LAi_CharacterDisableDialog(sld);
			DoQuestFunctionDelay("PDM_CL_Pokupatel_Uhodit", 1.5);
			sld = CharacterFromID("PDM_CL_Antonio3")
			sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			sld.dialog.currentnode   = "Antonio_5_1";
			LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();

			AddQuestRecord("PDM_Clan_Lambrini", "7");
			AddQuestUserData("PDM_Clan_Lambrini", "sSex", GetSexPhrase("","а"));
		break;


		case "Antonio_5_1":
			dialog.text = "Сеньор"+ GetSexPhrase("","ита") +" "+pchar.name+", вы очень быстро вернулись. Видели что-нибудь интересное?";
			link.l1 = "Да, Ламбрини уже в городе и чувствует себя очень комфортно. Я сумел"+ GetSexPhrase("","а") +" подслушать его разговор с капитаном, который собирается продать нелегальный и дорогой товар - сандал. Может стоит отправиться в таверну и схватить Ламбрини, тёпленького?";
			link.l1.go = "Antonio_5_2";
		break;

		case "Antonio_5_2":
			dialog.text = "Нет! Мы дадим ему провести сделку. Они все соберутся в бухте, вместе с ценным товаром, думая, что им ничего не угрожает. Тут-то появляемся мы и арестовываем всех. А вы смогли узнать, где они собираются вершить свои тёмные дела?";
			link.l1 = "Ламбрини говорил про бухту Гуахира.";
			link.l1.go = "Antonio_5_3";
			Pchar.GenQuest.Hunter2Pause = true;
		break;

		case "Antonio_5_3":
			dialog.text = "Отлично! Мы устроим облаву со стороны джунглей и застанем их врасплох. В путь!";
			link.l1 = "(отправиться на пляж)";
			link.l1.go = "Antonio_J_1";
		break;

		case "Antonio_J_1":
			DialogExit();

			LocatorReloadEnterDisable("Shore37", "reload1_back", true);
			LocatorReloadEnterDisable("Shore37", "boat", true);

			sld = CharacterFromID("PDM_CL_Antonio3")
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Shore37", "officers", "reload1_1");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);

			for (i=1; i<=2; i++)	//испанцы
			{
				sTemp = "sold_spa_"+(rand(7)+1);
				sld = GetCharacter(NPC_GenerateCharacter("SraDruzya_"+i, sTemp, "man", "man", Rank, SPAIN, -1, true));
				FantomMakeCoolFighter(sld, Rank, 30, 30, "blade10", "", 20);
				LAi_SetActorType(sld);
				LAi_CharacterDisableDialog(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				ChangeCharacterAddressGroup(sld, "Shore37", "reload",  "reload1_back");
			}

			for (i=3; i<=6; i++)	//пираты м контрабандисты 1
			{
				sTemp = "pirate_"+(rand(24)+1);
				sld = GetCharacter(NPC_GenerateCharacter("PDM_CL_PirVrag_"+i, sTemp, "man", "man", Rank, SPAIN, -1, true));
				FantomMakeCoolFighter(sld, Rank, 30, 30, "blade10", "", 20);
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, "PDM_CL_PirVrag_Status");
				ChangeCharacterAddressGroup(sld, "Shore37", "goto",  "goto5");
			}

			for (i=7; i<=10; i++)	//пираты м контрабандисты 2
			{
				sTemp = "pirate_"+(rand(24)+1);
				sld = GetCharacter(NPC_GenerateCharacter("PDM_CL_PirVrag_"+i, sTemp, "man", "man", Rank, SPAIN, -1, true));
				FantomMakeCoolFighter(sld, Rank, 30, 30, "blade10", "", 20);
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, "PDM_CL_PirVrag_Status");
				ChangeCharacterAddressGroup(sld, "Shore37", "goto",  "goto6");
			}

			for (i=11; i<=14; i++)	//пираты м контрабандисты 3
			{
				sTemp = "pirate_"+(rand(24)+1);
				sld = GetCharacter(NPC_GenerateCharacter("PDM_CL_PirVrag_"+i, sTemp, "man", "man", Rank, SPAIN, -1, true));
				FantomMakeCoolFighter(sld, Rank, 30, 30, "blade10", "", 20);
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, "PDM_CL_PirVrag_Status");
				ChangeCharacterAddressGroup(sld, "Shore37", "reload",  "sea");
			}

			DoQuestReloadToLocation("Shore37", "goto", "goto1", "PDM_CL_Na_Plyaj");
			AddGeometryToLocation("Shore37", "smg");
			pchar.location.from_sea = "Shore37";

			sld = GetCharacter(NPC_GenerateCharacter("PDM_Octavio_Lambrini", "barmen_3", "man", "man", 10, PIRATE, -1, false));
			LAi_SetActorType(sld);
			sld.name	= "Октавио";
			sld.lastname	= "Ламбрини";
			FantomMakeCoolFighter(sld, Rank, 80, 80, "blade33", "pistol2", 250);
			LAi_group_MoveCharacter(sld, "PDM_CL_PirVrag_Status");
			ChangeCharacterAddressGroup(sld, "Shore37", "goto", "goto7");

			sld = CharacterFromID(pchar.LambriniPGG);
			LAi_SetActorType(sld);

			sld.LambiniAsoleda = GetGeneratedItem("blade38");
			GiveItem2Character(sld, sld.LambiniAsoleda);
			EquipCharacterByItem(sld, sld.LambiniAsoleda);

			GiveItem2Character(sld, "pistol4");
			EquipCharacterByItem(sld, "pistol4");

			sld.BackupHP = LAi_GetCharacterMaxHP(sld);
			LAi_SetHP(sld, sti(sld.BackupHP) + 1000, sti(sld.BackupHP) + 1000);
			//LAi_SetHP(sld, 100, 100);
			SetCharacterPerk(sld, "Sliding");
			sld.perks.list.AgileMan = "1";
			ApplayNewSkill(sld, "AgileMan", 0);

			sld.SPECIAL.Agility = 10;
			sld.SPECIAL.Intellect = 10;
			sld.SPECIAL.Endurance = 10;
			sld.SPECIAL.Luck = 10;

			//FantomMakeCoolFighter(sld, Rank, 90, 90, "blade38", "pistol4", 500);

			LAi_SetCheckMinHP(sld, 1, true, "LambriniPGG_CheckHP");
			/*
			AddMoneyToCharacter(sld, 100000);
			AddItems(sld, "jewelry1", rand(20)+20);
			AddItems(sld, "jewelry2", rand(20)+20);
			AddItems(sld, "jewelry3", rand(20)+20);
			AddItems(sld, "jewelry4", rand(20)+20);
			AddItems(sld, "jewelry5", rand(20)+20);
			AddItems(sld, "suit_3", 1);
			AddItems(sld, "indian5", 1);
			sld.SaveItemsForDead = true;*/
			LAi_group_MoveCharacter(sld, "PDM_CL_PirVrag_Status");
			ChangeCharacterAddressGroup(sld, "Shore37", "goto", "goto7");
		break;

		case "Antonio_6_1":
			dialog.text = "Мы на месте. А вон и наши ламбринята... Даже не верится, что скоро мы положим этому конец. Веди отряд, мы за тобой.";
			link.l1 = "Вперёд!";
			link.l1.go = "Antonio_6_2";
		break;

		case "Antonio_6_2":
			DialogExit();

			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "enc01", "enc01_03", "PDM_CL_Na_Plyaj_2", -1);
		break;

		case "Pokupatel_6_1":
			dialog.text = "А вы что здесь забыли?";
			link.l1 = "Кажется, здесь происходит что-то незаконное.";
			link.l1.go = "Pokupatel_6_2";
		break;

		case "Pokupatel_6_2":
			dialog.text = "Нет-нет, сеньор"+ GetSexPhrase("","ита") +". Мы с друзьями просто отдыхаем у моря.";
			link.l1 = "Что вы мне рассказываете! Я не слеп"+ GetSexPhrase("ой","ая") +"! Следуйте за нами - вы арестованы, а товар конфискован!";
			link.l1.go = "Pokupatel_6_3";
		break;

		case "Pokupatel_6_3":
			dialog.text = "Скорее, я выпущу вам кишки!";
			link.l1 = "Сначала, я выпущу своего внутреннего зверя!";
			link.l1.go = "Pokupatel_6_4";
		break;

		case "Pokupatel_6_4":
			DialogExit();

			AddDialogExitQuest("MainHeroFightModeOn");

			for (i=3; i<=14; i++)	//пираты м контрабандисты
			{
				sld = CharacterFromID("PDM_CL_PirVrag_"+i)
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "PDM_CL_PirVrag_Status");
			}
			for (i=19; i<=27; i++)	//испанцы 1
			{
				sTemp = "sold_spa_"+(rand(7)+1);
				sld = GetCharacter(NPC_GenerateCharacter("SraDruzya_"+i, sTemp, "man", "man", Rank, SPAIN, -1, true));
				FantomMakeCoolFighter(sld, Rank, 28, 28, "blade10", "", 16);
				LAi_SetWarriorType(sld);
				LAi_CharacterDisableDialog(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				ChangeCharacterAddressGroup(sld, "Shore37", "goto", "goto4");
				sld.lifeday = 0;
			}
			for (i=1; i<=2; i++)	//испанцы 2
			{
				sld = CharacterFromID("SraDruzya_"+i)
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				sld.lifeday = 0;
			}

			sld = CharacterFromID("PDM_Octavio_Lambrini");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "PDM_CL_PirVrag_Status");

			sld = CharacterFromID(pchar.LambriniPGG)
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "PDM_CL_PirVrag_Status");

			sld = CharacterFromID("PDM_CL_Antonio3");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);

			LAi_group_SetRelation("PDM_CL_PirVrag_Status", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("PDM_CL_PirVrag_Status", LAI_GROUP_PLAYER, false);
			//LAi_group_SetCheck("PDM_CL_PirVrag_Status", "PDM_CL_Finish");
		break;

		case "Antonio_8_1":
			string OctavioDead = "";
			if(LAi_IsDead(CharacterFromID("PDM_Octavio_Lambrini")))	OctavioDead = "Пусть мы сегодня и победили, но старший сын Ламбрини займёт его место и продолжит дело отца. Боюсь, контрабандисткая секта будет вечно приносить вред Великой Испании.";

			dialog.text = "Не могу поверить, у нас получилось! Вы можете возвращаться в город, а мои люди разберутся с этим беспорядком. " + OctavioDead;

			OctavioDead = "Октавио Ламбрини мертв, ";
			if(!LAi_IsDead(CharacterFromID("PDM_Octavio_Lambrini")))	OctavioDead = "Октавио Ламбрини арестован, ";
			link.l1 = OctavioDead + "что насчёт награды?";
			link.l1.go = "Antonio_8_2";
		break;

		case "Antonio_8_2":
			pchar.LambriniPGGPlata = Plata2/2;
			string addPlata = "";
			if(!LAi_IsDead(CharacterFromID("PDM_Octavio_Lambrini")))
			{
				pchar.LambriniPGGPlata = Plata2;
				AddMoneyToCharacter(pchar, sti(Plata2*2));
				addPlata = "Но так как мы сумели поймать мерзавца живым - я удвою вам гонорар, из собственного кармана! В итоге " + Plata3 + " золотых. Кто знает, возможно после парочки недель в стенах тюрьмы Октавио расскажет, как нам изловить остальных членов его преступной семейки. "
			}
			else	AddMoneyToCharacter(pchar, sti(Plata2));
			dialog.text = "Да, конечно, сеньор Алькальда выделил вам " + Plata2 + " золотых. "+addPlata+"Я даю эти деньги вам лично в руки. Адиос!";
			link.l1 = "Благодарю, Антонио. Удачи вам!";
			link.l1.go = "LambriniPGG_1_5";

			LocatorReloadEnterDisable("Shore37", "reload1_back", false);
			LocatorReloadEnterDisable("Shore37", "boat", false);
			ChangeCharacterNationReputation(pchar, SPAIN, 8);
			ChangeCharacterReputation(pchar, 5);
		break;

		case "LambriniPGG_1_1":
			dialog.text = RandSwear()+"Груз сандала не стоит наших жизней. Мы сдаёмся!";
			link.l1 = "В таком случае, вы должны сдать свою шпагу, капитан.";
			link.l1.go = "LambriniPGG_1_2";

			for (i=3; i<=14; i++)	//пираты м контрабандисты прячут оружие, испанцы - нет
			{
				sld = CharacterFromID("PDM_CL_PirVrag_"+i);
				LAi_SetStayTypeNoGroup(sld);
			}
			sld = characterFromID("PDM_Octavio_Lambrini");
			LAi_SetStayTypeNoGroup(sld);
		break;

		case "LambriniPGG_1_2":
			for (i=3; i<=14; i++)	//пираты м контрабандисты
			{
				sld = CharacterFromID("PDM_CL_PirVrag_"+i);
				LAi_SetActorTypeNoGroup(sld);
			}
			sld = characterFromID("PDM_Octavio_Lambrini");
			LAi_SetActorTypeNoGroup(sld);
			sld.LifeDay = 0;
			dialog.text = RandSwear()+"Ты и представить себе не можешь, как дорого она мне обошлась!";
			link.l1 = "Я дважды повторять не стану. ";
			link.l1.go = "LambriniPGG_1_3";
		break;

		case "LambriniPGG_1_3":
			TakeItemFromCharacter(npchar, npchar.LambiniAsoleda);
			GiveItem2Character(pchar, npchar.LambiniAsoleda);
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			Log_Info("Вы получили Асоледу!");
			PlaySound("interface\important_item.wav");

			dialog.text = RandSwear()+"(отдаёт Асоледу) На, подавись!";
			link.l1 = "Что дальше, Антонио?";
			link.l1.go = "LambriniPGG_1_4";

			PChar.quest.LambriniPGG_RemoveFromShore.win_condition.l1 = "ExitFromLocation";
			PChar.quest.LambriniPGG_RemoveFromShore.win_condition.l1.location = PChar.location;
			PChar.quest.LambriniPGG_RemoveFromShore.function = "LambriniPGG_RemoveFromShore";
		break;

		case "LambriniPGG_1_4":
			DialogExit();
			sld = GetCharacter(NPC_GenerateCharacter("PDM_CL_Antonio4", "SpaOfficer2", "man", "man", Rank, SPAIN, 0, false));
			sld.name = "Антонио";
			sld.lastname = "де Гальвес";
			sld.greeting = "GR_Spainguard";
			sld.equip.blade = "blade39";
			ChangeCharacterAddressGroup(sld, "Shore37", "goto", "goto7");
			sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			//sld = CharacterFromID("PDM_CL_Antonio3");
			sld.dialog.currentnode   = "Antonio_8_1";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		case "LambriniPGG_1_5":
			DialogExit();
			sld = CharacterFromID(pchar.LambriniPGG);
			sld.dialog.currentnode   = "LambriniPGG_1_6";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		case "LambriniPGG_1_6":
			dialog.text = "Это ваши разборки с Октавио, и я здесь ни при чём. Отпустите меня! Быть может, вам о чём-нибудь говорит имя "+GetFullName(npchar)+"? Я известная в этих водах личность! Лучше не переходить мне дорогу.";
			link.l1 = "";
			link.l1.go = "LambriniPGG_1_7";
		break;

		case "LambriniPGG_1_7":
			DialogExit();
			sld = CharacterFromID("PDM_CL_Antonio4");
			sld.dialog.currentnode   = "LambriniPGG_1_8";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		case "LambriniPGG_1_8":
			dialog.text = "Ты вела дела с преступником, а значит ты с ним за одно! Мы отведём вас в тюрьму под фортом Маракайбо, а затем вашу судьбу решит суд.";
			link.l1 = "";
			link.l1.go = "LambriniPGG_1_9";
		break;

		case "LambriniPGG_1_9":
			LAi_SetActorTypeNoGroup(npchar);
			DialogExit();
			sld = CharacterFromID(pchar.LambriniPGG);
			sld.dialog.currentnode   = "LambriniPGG_1_10";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		case "LambriniPGG_1_10":
			LAi_SetActorTypeNoGroup(npchar);
			LAi_SetHP(npchar, sti(npchar.BackupHP) + 100, sti(npchar.BackupHP) + 100);
			dialog.text = "(обращается к тебе шёпотом) Антонио слишком порядочный, для него закон превыше всего, вряд ли его можно переубедить, но а что насчёт тебя? Я же вижу, что ты "+ GetSexPhrase("не из тех правильных мальчиков","'плохая' девочка") +". Помоги мне выпутаться из этой передряги, а я тебя награжу. В довесок к шпаге, заберёшь весь мой клад!";
			link.l1 = "Мне это не интересно. Преступникам место за решёткой.";
			link.l1.go = "LambriniPGG_1_11";
			link.l2 = "Клад, говоришь... Я что-нибудь придумаю.";
			link.l2.go = "LambriniPGG_1_12";
		break;

		case "LambriniPGG_1_11":
			dialog.text = RandSwear()+RandSwear()+RandSwear()+RandSwear()+RandSwear()+"Будьте вы прокляты! Ну ничего, я ещё выберусь и отомщу, всем вам!";
			link.l1 = "Ну-ну.";
			link.l1.go = "exit";
			AddQuestRecord("PDM_Clan_Lambrini", "9");
			CloseQuestHeader("PDM_Clan_Lambrini");
			AddQuestUserData("PDM_Clan_Lambrini", "sName", GetFullName(npchar));
			PGG_ChangeRelation2MainCharacter(CharacterFromID(pchar.LambriniPGG), -200); //сильно обиделась
			SetTimerCondition("LambriniPGG_Freedom", 0, 0, 30, false); //Посидит месяц в тюрьме без кача и потом выйдет
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fencing", 200);
			AddCharacterExpToSkill(pchar, "Pistol", 200);
		break;

		case "LambriniPGG_1_12"://Запустить таймер в 10 дней на возврат диалога коменданту потом то же, что и в комменте выше
			dialog.text = "Ты не пожалеешь! Только прошу, поторопись, я не хочу на виселицу!";
			link.l1 = "Ладно.";
			link.l1.go = "LambriniPGG_1_13";
			AddQuestRecord("PDM_Clan_Lambrini", "8");
			AddQuestUserData("PDM_Clan_Lambrini", "sName", GetFullName(npchar));
		break;

		case "LambriniPGG_1_13":
			DialogExit();
			SetTimerCondition("LambriniPGG_Late", 0, 0, 3, false);//Три дня чтобы прийти в тюрьму
			pchar.LambriniPGGInPrison = true;
			//sld = CharacterFromID("MaracaiboJailOff");
			//SaveOldDialog(sld);
			//sld.Dialog.Filename = "Quest/PDM/Clan_Lambrini.c";
			//sld.dialog.currentnode   = "LambriniPGG_1_14";
		break;

		case "LambriniPGG_1_14"://Запустить таймер в 10 дней на возврат диалога коменданту потом то же, что и в комменте выше
			dialog.text = "Ты не пожалеешь! Только прошу, поторопись, я не хочу на виселицу!";
			link.l1 = "Ладно.";
			link.l1.go = "exit";
			DialogExit();
			//RestoreOldDialog(npchar);
		break;

		case "LambriniPGG_2_1":
			LocatorReloadEnterDisable(pchar.location.from_sea, "reload1_back", true);
			LocatorReloadEnterDisable("Maracaibo_exittown", "reload1_back", true);
			chrDisableReloadToLocation = false;
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			dialog.text = GetSexPhrase("Мой спаситель!","Моя спасительница!")+" Если конечно опустить тот факт, что это именно ты засадил" + GetSexPhrase("","а") + " меня сюда.";
			link.l1 = "Раз моих это рук дело, мне и вызволять. Так что насчёт клада?";
			link.l1.go = "LambriniPGG_2_2";
		break;

		case "LambriniPGG_2_2":
			dialog.text = "Мой сундук должен быть всё ещё здесь, в Маракайбо. Сними комнату в таверне.";
			link.l1 = "В таверну, так в таверну.";
			link.l1.go = "exit";

			PChar.quest.LambriniPGG_Tavern.win_condition.l1 = "location";
			PChar.quest.LambriniPGG_Tavern.win_condition.l1.location = "Maracaibo_tavern_upstairs";
			PChar.quest.LambriniPGG_Tavern.function = "LambriniPGG_Tavern";
		break;

		case "LambriniPGG_2_3":
			chrDisableReloadToLocation = true;
			dialog.text = "А вот и сундук. Нам повезло, что солдаты не успели его найти.";
			link.l1 = "Ладно, открывай. Посмотрим, что там.";
			link.l1.go = "LambriniPGG_2_4";
		break;
		case "LambriniPGG_2_4":
			GiveItem2Character(pchar, "Chest_quest");
			Log_Info("Вы получили странный сундук");
			PlaySound("interface\important_item.wav");
			dialog.text = "С этим есть проблемка. У меня нет ключа.";
			link.l1 = "Ну и накой мне нужен запертый сундук?";
			link.l1.go = "LambriniPGG_2_5";
		break;
		case "LambriniPGG_2_5":
			TakeNItems(PChar, "Lockpick", 3);
			Log_Info("Вы получили отмычки");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ты сможешь отпереть его отмычками. Вот, смотри. Я купила их у Октавио Ламбрини, но так и не успела воспользоваться.";
			link.l1 = "Ладно, давай их сюда, разберусь уже.";
			link.l1.go = "LambriniPGG_2_6";
		break;
		case "LambriniPGG_2_6":
			dialog.text = "Что ж, думаю мы оба выполнили свою часть договоренности...";
			link.l1 = "Так и быть, можешь идти.";
			link.l1.go = "LambriniPGG_2_7";
			link.l2 = "Раз уж мы оказались в спальне, и здесь такая мягкая кровать... Проверим её на прочность?";
			link.l2.go = "LambriniPGG_2_8";
		break;
		case "LambriniPGG_2_7":
			PGG_ChangeRelation2MainCharacter(CharacterFromID(pchar.LambriniPGG), 30);
			chrDisableReloadToLocation = false;
			dialog.text = "Ну мне пора. Теперь нужно как-то свой корабль вернуть\nМожет ещё увидимся. Удачи тебе.";
			link.l1 = "И тебе.";
			link.l1.go = "LambriniPGG_2_10";

			string finalWords = ".";
			if (CheckAttribute(npchar,"bonusEnergy"))	finalWords = " и несколько незабываемых приятных воспоминаний.";

			AddQuestRecord("PDM_Clan_Lambrini", "11");
			CloseQuestHeader("PDM_Clan_Lambrini");
			AddQuestUserData("PDM_Clan_Lambrini", "sName", GetFullName(npchar));
			AddQuestUserData("PDM_Clan_Lambrini", "sContinue", finalWords);

			DeleteAttribute(pchar,"LambriniPGGInPrison");
			SetTimerCondition("LambriniPGG_Freedom", 0, 0, 7, false);//Через неделю вернется в строй
			//DeleteAttribute(npchar, "PGGAi.DontUpdate");
			//DeleteAttribute(npchar, "PGGAi.Task.SetSail");
			//DeleteAttribute(pchar, "LambriniPGG");

			LocatorReloadEnterDisable(pchar.location.from_sea, "reload1_back", false);
			LocatorReloadEnterDisable("Maracaibo_exittown", "reload1_back", false);
		break;
		case "LambriniPGG_2_8":
			dialog.text = "А наглости тебе не занимать! Я согласна.";
			link.l1 = "";
			link.l1.go = "LambriniPGG_2_9";
		break;
		case "LambriniPGG_2_9":
			PGG_ChangeRelation2MainCharacter(CharacterFromID(pchar.LambriniPGG), 200);
			pchar.GenQuest.BrothelCount = 0;
            AddCharacterExpToSkill(pchar, "Leadership", 200);
            AddCharacterExpToSkill(npchar, "Leadership", 200);
            AddCharacterExpToSkill(pchar, "Fencing", 200);// утрахала
            AddCharacterExpToSkill(npchar, "Fencing", 200);
            AddCharacterExpToSkill(pchar, "Pistol", 200);
            AddCharacterExpToSkill(npchar, "Pistol", 200);
            AddCharacterHealth(pchar, 10);
            AddCharacterHealth(npchar, 10);
			AddBonusEnergyToCharacter (NPchar, 80);
   			AddDialogExitQuest("PlaySex_1");
			NextDiag.CurrentNode = "LambriniPGG_2_7";
			DialogExit();
		break;

		case "LambriniPGG_2_10":
			RestoreOldDialog(npchar);
			DialogExit();
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
		break;
	}
}
