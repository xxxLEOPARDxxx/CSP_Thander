void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;
	ref shTo;
	string cnd;
	DeleteAttribute(&Dialog,"Links");
	int i;

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Quest_Whisper_1":
			dialog.text = "Итак, работа непростая, но куш, который мы сможем урвать, стоит риска.";
			link.l1 = "Это я уже понял"+ GetSexPhrase("","а")+". Хочу знать детали.";
			link.l1.go = "Quest_Whisper_2";
		break;

		case "Quest_Whisper_2":
			dialog.text = "Погоди, кажется, сюда кто-то идет. Я запру дверь.";
			link.l1 = "...";
			link.l1.go = "Quest_Whisper_2_exit";
			pchar.WhisperPGG = npchar.id;
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);

			for (i = 1; i < 4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PGG_Whisper_Incquisitor"+i, "PGG_Vincento_"+(2+i), "man", "man", sti(pchar.rank) + MOD_SKILL_ENEMY_RATE, PIRATE, 0, true));
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1_back");
				cnd = "l"+i;
				pchar.quest.QuestWhisper_RoomFight.win_condition.(cnd) = "NPC_Death";
				pchar.quest.QuestWhisper_RoomFight.win_condition.(cnd).character = sld.id;
				LAi_group_MoveCharacter(sld, "Quest_Whisper_Enemy");
			}
			pchar.quest.QuestWhisper_RoomFight.function = "QuestWhisper_RoomFight";
		break;

		case "Quest_Whisper_2_exit":
			DialogExit();
			sld = CharacterFromId("PGG_Whisper_Incquisitor3");
			sld.Dialog.Filename = "Quest\WhisperLine\Whisper_PGG.c";
			sld.dialog.currentnode   = "Quest_Whisper_3";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		case "Quest_Whisper_3":
			dialog.text = "Никто не ждёт испанскую инквизицию!";
			link.l1 = "Что?";
			link.l1.go = "Quest_Whisper_3_exit";
		break;

		case "Quest_Whisper_3_exit":
			DialogExit();
			sld = CharacterFromId(pchar.WhisperPGG);
			sld.Dialog.Filename = "Quest\WhisperLine\Whisper_PGG.c";
			sld.dialog.currentnode   = "Quest_Whisper_4";
			pchar.InstantDialog = sld.id;
			DoQuestFunctionDelay("InstantDialog", 0);
		break;

		case "Quest_Whisper_4":
			dialog.text = "Проклятье! Это ты их сюда прив"+ GetSexPhrase("ёл","ела")+" по мою душу?";
			link.l1 = "Да я впервые вижу этих ребят!";
			link.l1.go = "Quest_Whisper_4_exit";
		break;

		case "Quest_Whisper_4_exit":
			StartInstantDialog("PGG_Whisper_Incquisitor3", "Quest_Whisper_5", "Quest\WhisperLine\Whisper_PGG.c");
		break;

		case "Quest_Whisper_5":
			dialog.text = "Виспер! Наконец-то мы выследили тебя, ведьма! Теперь ты поплатишься за свои злодеяния!";
			link.l1.go = "Quest_Whisper_5_exit";
		break;

		case "Quest_Whisper_5_exit":
			StartInstantDialog(pchar.WhisperPGG, "Quest_Whisper_6", "Quest\WhisperLine\Whisper_PGG.c");
		break;

		case "Quest_Whisper_6":
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_SetImmortal(npchar, true);
			dialog.text = "Как же вы мне уже надоели!";
			link.l1.go = "Quest_Whisper_6_exit";
			pchar.WhisperId = npchar.id;
		break;

		case "Quest_Whisper_6_exit":
			npchar.dialog.CurrentNode = "Quest_Whisper_8";
			StartInstantDialog("PGG_Whisper_Incquisitor3", "Quest_Whisper_7", "Quest\WhisperLine\Whisper_PGG.c");
		break;

		case "Quest_Whisper_7":
			dialog.text = "Приготовься отправиться в ад, вместе со сво"+ GetSexPhrase("им прислужником!","ей прислужницей!");
			link.l1 = "Не хотелось мне вмешиваться в ваши с ней дела, но слово "+ GetSexPhrase("'прислужник'","'прислужница'")+" прозвучало довольно обидно.";
			link.l1.go = "Quest_Whisper_7_fight";
			link.l2 = "Ну нахер, я сваливаю!";
			link.l2.go = "Quest_Whisper_7_flee";
		break;
		case "Quest_Whisper_7_fight":
			sld = CharacterFromId(pchar.WhisperId);
			LAi_SetWarriorTypeNoGroup(sld);
			for (i = 1; i < 4; i++)
			{
				sld = CharacterFromId("PGG_Whisper_Incquisitor"+i);
				LAi_SetWarriorTypeNoGroup(sld);
			}

			DialogExit();
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "Quest_Whisper_7_flee":
			DialogExit();
			sld = CharacterFromId(pchar.WhisperId);
			DoReloadCharacterToLocation(sld.PGGAi.location.town + "_tavern","goto","goto1");
			chrDisableReloadToLocation = false;
		break;

		case "Quest_Whisper_8":
			if (HasSubStr(pchar.location,"upstairs"))
			{
				dialog.text = "Ты как, жив"+ GetSexPhrase("","а")+"?";
				link.l1 = "Со мной всё в порядке. Лучше скажи, какого чёрта здесь происходит?!";
				link.l1.go = "Quest_Whisper_9";
			}
			else
			{
				dialog.text = "У тебя хватает наглости заявляться ко мне, после того, как ты бросил"+ GetSexPhrase("","а")+" меня умирать? Я больше не хочу вести с тобой дел.";
				link.l1 = "Ну и не нужно!";
				link.l1.go = "Quest_Whisper_end";
			}
		break;

		case "Quest_Whisper_9":
			dialog.text = "Как видишь, у меня хватает врагов на этом архипелаге. У тебя ведь они тоже есть?";
			link.l1 = "Да, но не такие! Как тебя угораздило разозлить инквизицию?";
			link.l1.go = "Quest_Whisper_10";
		break;

		case "Quest_Whisper_10":
			dialog.text = "Это долгая история. Но могу тебе сказать, что инквизиция не просто орден, который борется с еретиками. На самом деле они не гнушаются участвовать в политике, да и в целом уже давно погрязли в коррупции и лжи. В их власти обвинить любого человека в ереси, сжечь, а имущество - отобрать в пользу собственной казны, и они не пренебрегают этим пользоваться. Однажды они сделали нечно подобное и со мной, но мне удалось сбежать в последний момент. С тех пор, инквизиция за мной охотится.";
			link.l1 = "Мне кажется, что ты многого не договариваешь... Не то, чтобы я защищаю инквизицию, но ты и правда смахиваешь на ведьму. Не расскажешь как так вышло?";
			link.l1.go = "Quest_Whisper_11";
		break;

		case "Quest_Whisper_11":
			dialog.text = "Быть может, в другой раз расскажу, когда узнаю тебя получше. А пока что давай поговорим о деле. Ты ведь хочешь заработать?";
			link.l1 = "Ну ладно, рассказывай.";
			link.l1.go = "Quest_Whisper_12";
		break;

		case "Quest_Whisper_12":
			dialog.text = "Если вкратце - я предлагаю нам вместе разграбить один испанский город. ";
			link.l1 = "Это имеет какое-то отношение к нашим недавним 'гостям'?";
			link.l1.go = "Quest_Whisper_13";
		break;

		case "Quest_Whisper_13":
			dialog.text = "Это не первый, и далеко не последний раз, когда они за мной приходят. Нужно положить этому конец\nЯ собираюсь ударить по самому больному для инквизиции - деньгам. А денег у них немало. Горы золота, что они конфисковали у приговорённых испанских граждан за много лет\nМесяц назад мне повстречалась эскадра охотников, как раз снаряженная за счет этой казны, что состояла из одних только линейных кораблей. Я сумела отбиться, но мой верный корвет дал течь и пришлось его бросить. Посудина, что я раздобыла после, совсем не годится для задуманного плана, так что мне пригодится помощь кого-то, вроде тебя.";
			link.l1 = "Так ты хочешь отомстить им... И где находится их казна? В Сантьяго?";
			link.l1.go = "Quest_Whisper_14";
		break;


		case "Quest_Whisper_14":
			dialog.text = "Да. Там, под церковью находится их главная резиденция на Карибах. Скрытно пробраться и ограбить их не получится - ценностей там не на один сундук. По этой же причине мы не можем устроить набег на город с суши - нам просто не хватит времени всё вынести, прежде чем солдаты из форта хватятся. Нет - придётся брать город с моря, сначала уничтожив форт.";
			link.l1 = "Не самоубийственный ли это план? В гарнизоне форта наверняка - тысячи солдат, к тому же город охраняет эскадра военных кораблей. Какая бы ни была там казна, вряд ли она того стоит.";
			link.l1.go = "Quest_Whisper_15";
		break;

		case "Quest_Whisper_15":
			dialog.text = "Не забывай, мы получим не только казну инквизиции, но и добычу за разграбление города. А с охраной я могу помочь.";
			link.l1 = "Каким образом поможешь?";
			link.l1.go = "Quest_Whisper_16";
		break;

		case "Quest_Whisper_16":
			dialog.text = "Я знаю, как заставить губернатора увести эскадру и часть солдат из форта. Если ты шепнёшь ему, что меня видели в Пуэрто Принсипе, не сомневаюсь, он отправит все силы на мою поимку. Меня уже давно разыскивают на этом острове.";
			link.l1 = "Ты думаешь он просто так мне поверит?";
			link.l1.go = "Quest_Whisper_18";
		break;

		case "Quest_Whisper_18":
			dialog.text = "Вряд ли. Боюсь, что сначала тебе придется выполнить несколько его поручений, чтобы втереться в доверие, а уже потом рассказывать эту байку.";
			link.l1 = "Несколько?";
			link.l1.go = "Quest_Whisper_19";
		break;

		case "Quest_Whisper_19":
			dialog.text = "Думаю, трёх хватит, чтобы у него развеялись любые сомнения в твоей искренности и дружелюбии\nКак только это сделаешь, будь готов"+ GetSexPhrase("","а")+" выйти в море и сразу штурмовать форт своими силами, ведь моё судно будет отвлекать эскадру охраны.";
			link.l1 = "Ладно, берусь. Где я смогу тебя найти, когда закончу соблазнять губернатора?";
			link.l1.go = "Quest_Whisper_20";
			link.l2 = "Знаешь, не хочу я в это ввязываться. Не сомневаюсь, после такого Испания назначит награду за мою голову.";
			link.l2.go = "Quest_Whisper_19_1";
		break;

		case "Quest_Whisper_19_1":
			dialog.text = "Уверен"+ GetSexPhrase("","а")+"? Больше я это дело тебе не предложу. Но если согласишься, то с выполнением я сильно не тороплю, ведь понимаю, что тебе нужно будет основательно подготовиться к штурму.";
			link.l1 = "Уверен"+ GetSexPhrase("","а")+".";
			link.l1.go = "Quest_Whisper_end";
			link.l2 = "Ладно, берусь. Где я смогу тебя найти, когда закончу соблазнять губернатора?";
			link.l2.go = "Quest_Whisper_20";
		break;

		case "Quest_Whisper_20":
			dialog.text = "Обо мне не беспокойся, я буду неподалёку от Кубы. Как только сделаешь свою часть плана - я сама тебя найду.";
			pchar.PGGWhisperLetter = true;
			link.l1 = "Что ж, тогда за дело.";
			link.l1.go = "Quest_Whisper_accept";
		break;

		case "Quest_Whisper_end":
			LocatorReloadEnterDisable("Santiago_Town", "basement1", false);
			npchar.dialog.filename = "pgg_dialog_town.c";
			npchar.dialog.currentnode = "First time";
			npchar.PGGWhisperQuestEnd = true;
			DialogExit();
			CloseQuestHeader("PGGWhisper");
			DeleteAttribute(npchar, "PGGAi.DontUpdate");
			DeleteAttribute(pchar, "PGGWhisperQuest");
			DeleteAttribute(pchar, "PGGWhisperLetter");
			DeleteAttribute(pchar, "PGGWhisperLetterSent");
			DeleteAttribute(pchar, "PGGWhisperLetterSentFail");
			DeleteAttribute( Colonies[FindColony("Santiago")], "DontSetShipInPort");
		break;

		case "Quest_Whisper_accept":
			npchar.PGGAi.DontUpdate = true;
			if (!CheckAttribute(pchar, "PGGWhisperQuest"))
			{
				SetQuestHeader("PGGWhisper");
				AddQuestRecord("PGGWhisper", "1");
				pchar.PGGWhisperQuest = true;
			}
			npchar.dialog.currentnode = "Quest_Whisper_report";
			LocatorReloadEnterDisable("Santiago_Town", "basement1", true);
			DialogExit();
		break;

		case "Quest_Whisper_report":
			dialog.text = "Ты снова здесь! Остались какие-то вопросы?";

			if (CheckAttribute(pchar, "PGGWhisperLetterSentFail"))
			{
				DeleteAttribute(pchar, "PGGWhisperLetterSentFail");
				link.l1 = link.l1 + " Но он мне не поверил. Прости, ничего не вышло.";
				link.l1.go = "Quest_Whisper_report_fail";
				break;
			}

			link.l1 = "Да нет, просто мимо прохожу.";
			link.l1.go = "Quest_Whisper_accept";
			link.l2 = "Да. У меня из головы вылетело. Напомни, что у нас с тобой за дело?";
			link.l2.go = "Quest_Whisper_report_1";
			link.l3 = "Я тут подумал"+ GetSexPhrase("","а")+", не нравится мне твоё дело. Прости, но я пас.";
			link.l3.go = "Quest_Whisper_report_fail";
		break;

		case "Quest_Whisper_report_1":
			dialog.text = "Что?! Издеваешься? Если у тебя есть голова на плечах, то ты записываешь такие вещи в свой журнал. Я сделаю вид, что не слышала твоего вопроса.";
			link.l1 = "Да шучу я.";
			link.l1.go = "Quest_Whisper_accept";
		break;

		case "Quest_Whisper_report_fail":
			dialog.text = "Ясно. Похоже, мне придётся искать другой способ. Спасибо что сказал"+ GetSexPhrase("","а")+". Бывай.";
			link.l1 = "Бывай.";
			link.l1.go = "Quest_Whisper_end";
			//не забыть закрытие квеста
		break;
		case "Quest_Whisper_ToSiege":
			chrDisableReloadToLocation = false;
			dialog.text = "Корабли в гавани снимаются с якоря, похоже наш план работает.";
			link.l1 = "Что ты здесь делаешь? Разве твой корабль не должен сейчас отвлекать эскадру?";
			link.l1.go = "Quest_Whisper_ToSiege_1";
		break;
		case "Quest_Whisper_ToSiege_1":
			dialog.text = "Мой штурман сам с этим управится. Ты же не думал"+ GetSexPhrase("","а")+", что я оставлю тебе всё веселье?";
			link.l1 = "А что это за снаряжение у тебя? Никогда такого не видел"+ GetSexPhrase("","а")+".";
			link.l1.go = "Quest_Whisper_ToSiege_2";
		break;
		case "Quest_Whisper_ToSiege_2":
			dialog.text = "И вряд ли ещё где-либо увидишь. Ладно, хватит трепаться. Пошли к шлюпке, пока стража меня не узнала. Надеюсь, твоего судна хватит, чтобы взять этот город.";
			link.l1 = "Пойдём, проверим.";
			link.l1.go = "exit";
			LAi_LoginInCaptureTown(npchar, true);
			LAi_SetActorTypeNoGroup(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("PGGWhisper", "4");
		break;
		case "Quest_Whisper_AfterSiege":
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Santiago_Town", "basement1", false);
			dialog.text = "Мы это сделали! Остался последний рывок - резиденция инквизиции. Вход находится под лестницей в церковь. Заходи, как будешь готов"+ GetSexPhrase("","а")+". Если хочешь, можешь сразу навестить губернатора, я подожду.";
			link.l1 = "Ладно.";
			link.l1.go = "exit";
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorFollow(npchar, PChar, "", -1);

			PChar.quest.QuestWhisper_Incq.win_condition.l1 = "location";
			PChar.quest.QuestWhisper_Incq.win_condition.l1.location = "Santiago_Incquisitio";
			PChar.quest.QuestWhisper_Incq.function = "QuestWhisper_Incq";
		break;

		case "Quest_Whisper_Incq_fall":
			dialog.text = "Ох, голова раскалывается\nВижу, мы всё-таки победили?";
			link.l1 = "Ты выжила? Когда я увидел"+ GetSexPhrase("","а")+", что ты упала, я опасалась худшего.";
			link.l1.go = "Quest_Whisper_Incq";
		break;

		case "Quest_Whisper_Incq":
			//chrDisableReloadToLocation = false;

			dialog.text = "Пошли, их сокровища должны быть где-то рядом.";
			if (!CheckAttribute(npchar, "FailedRecruitment"))	dialog.text = "Оказалось гораздо проще, чем я думала. " + dialog.text;
			link.l1 = "Хорошо, только давай немного дух переведём.";
			link.l1.go = "exit";
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorFollow(npchar, PChar, "", -1);

			PChar.quest.QuestWhisper_Incq_4.win_condition.l1 = "locator";
			PChar.quest.QuestWhisper_Incq_4.win_condition.l1.location = "Santiago_Incquisitio";
			PChar.quest.QuestWhisper_Incq_4.win_condition.l1.locator_group = "box";
			PChar.quest.QuestWhisper_Incq_4.win_condition.l1.locator = "box2";
			PChar.quest.QuestWhisper_Incq_4.function = "QuestWhisper_Incq_4";

			ref _location = &locations[reload_location_index];
			//DeleteAttribute(_location, "box1");
			_location.box2.money = 250000;
			_location.box2.items.icollection = 5;
			_location.box2.items.chest = 10;
			_location.box2.items.jewelry1 = 20+rand(5);
			_location.box2.items.jewelry2 = 20+rand(5);
			_location.box2.items.jewelry3 = 20+rand(5);
			_location.box2.items.jewelry4 = 11+rand(5);
			_location.box2.items.BackPack5 = 1;
			_location.box2.items.DeSouzaCross = 1;
			ChangeItemName("DeSouzaCross", "itmname_DeSouzaCross_DH");
		break;

		case "Quest_Whisper_Incq_1":
			dialog.text = "И это всё? ";
			link.l1 = "Ну, куча выглядит довольно внушительно.";
			link.l1.go = "Quest_Whisper_Incq_2";
		break;

		case "Quest_Whisper_Incq_2":
			dialog.text = "Должно быть гораздо больше. Инквизиторов здесь тоже оказалось маловато. А из тех, что были - никого из влиятельных\nПроклятье, я что-то упустила! Должно быть, у инквизиции появилась другая резиденция, о которой я не слышала.";
			link.l1 = "Может и так, но добыча меня устраивает. Как будем делить?";
			link.l1.go = "Quest_Whisper_Incq_3";
		break;

		case "Quest_Whisper_Incq_3":
			dialog.text = "Я заберу только свой дробовик, что у меня отобрали здесь во время моего предыдущего 'визита'\nМожешь оставить всё остальное себе. И добычу за разграбление города тоже. Я пришла сюда чтоб избавиться от старого и назойливого врага, а не ради этой горстки кровавых монет.";
			link.l1 = "Ты это всерьёз? Горстка довольно большая, знаешь ли.";
			link.l1.go = "Quest_Whisper_Incq_4";
		break;

		case "Quest_Whisper_Incq_4":
			dialog.text = "Не будем задерживаться. В любой момент в город могут вернуться оставшиеся силы испанцев.";
			link.l1 = "Как скажешь.";
			link.l1.go = "Quest_Whisper_Incq_5";
		break;

		case "Quest_Whisper_Incq_5":
			AddQuestRecord("PGGWhisper", "5");
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;

			PChar.quest.QuestWhisper_Incq_5.win_condition.l1 = "location";
			PChar.quest.QuestWhisper_Incq_5.win_condition.l1.location = "Santiago_Town";
			PChar.quest.QuestWhisper_Incq_5.function = "QuestWhisper_Incq_5";
		break;

		case "Quest_Whisper_Finish":
			pchar.PGGWhisperComplete = true;
			DeleteAttribute(npchar, "PGGAi.DontUpdate");
			CloseQuestHeader("PGGWhisper");
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "LockMapReload");
			DeleteAttribute(pchar, "PGGWhisperLetter");
			DeleteAttribute(pchar, "PGGWhisperLetterSent");
			DeleteAttribute( Colonies[FindColony("Santiago")], "DontSetShipInPort");

			dialog.text = "Мой корабль уже стоит в гавани. Не знаю, как скоро за ним проследуют испанцы, но проверять не стану. Тебе тоже не советую здесь задерживаться.";
			link.l1 = "Что ж, бывай.";
			link.l1.go = "Quest_Whisper_Finish_NoHire";
			link.l2 = "Испанцы, инквизиция... теперь твои враги - мои враги. Быть может, объединимся и продолжим бороться против них вместе? Кто знает, может мы ещё достанем инквизицию...";
			link.l2.go = "Quest_Whisper_Finish_Hire";
		break;

		case "Quest_Whisper_Finish_NoHire":
			npchar.dialog.filename = "pgg_dialog_town.c";
			npchar.dialog.currentnode = "First time";
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			DialogExit();
		break;

		case "Quest_Whisper_Finish_Hire_1":
			npchar.dialog.filename = "Enc_Officer_dialog.c";
			npchar.dialog.currentnode = "hired";
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			DialogExit();
		break;

		case "Quest_Whisper_Finish_Hire":
			if (CheckAttribute(npchar, "FailedRecruitment"))
			{
				dialog.text = "Прости, но я думаю, что мне будет безопасней в одиночку.";
				link.l1 = "Как знаешь.";
				link.l1.go = "Quest_Whisper_Finish_NoHire";
			}
			else
			{
				if (SetCompanionIndex(pchar, -1, sti(NPChar.index)) != -1)
				{
					Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() +
							RandPhraseSimple("Заманчивое предложение! Хорошо! Я составлю компанию!", "А ты не промах, капитан... Думаю, мы сработаемся!"),
							LinkRandPhrase("Ваше предложение мне нравится. Я согласна.",
							"Чтож... Я тоже думаю, что вместе мы сможем больше!", "Пожалуй, это будет весело. Договорились."));
					link.l1 = RandPhraseSimple("Отлично, жду тебя в море!", "Вот и правильно! Мы будем отличной командой.");
					link.l1.go = "Quest_Whisper_Finish_Hire_1";

					if (CheckAttribute(NPChar, "PGGAi.Task.SetSail"))
					{
						PGG_Disband_Fleet(npchar);
					}

					NPChar.PGGAi.IsPGG = false;
					NPChar.PGGAi.location.town = "none";
					if (NPChar.model.animation == "man" || NPChar.model.animation == "YokoDias" || NPChar.model.animation == "Milenace") Npchar.CanTakeMushket = true;
					if(npchar.model == "PGG_Whisper_6") EquipCharacterByItem(NPChar, "suit_1");
					NPChar.Payment = true;
					NPChar.Money   = 0;
					SetBaseShipData(NPChar);
					DeleteAttribute(NPChar,"ship.sails");
					DeleteAttribute(NPChar,"ship.masts");
					DeleteAttribute(NPChar,"ship.blots");

					Fantom_SetCannons(NPChar, "pirate");
					Fantom_SetBalls(NPChar, "pirate");

					DeleteAttribute(NPChar, "PGGAi.Task");
					DeleteAttribute(NPChar, "PGGAi.LockService");
					SetCharacterRemovable(NPChar, true);
					SaveCurrentNpcQuestDateParam(NPChar, "Companion.CheckRelation");

					NPChar.HalfImmortal = true;  // Контузия
					NPChar.OfficerWantToGo.DontGo = true; //не пытаться уйти
					NPChar.loyality = MAX_LOYALITY;

					LAi_SetActorTypeNoGroup(npchar);
					LAi_ActorFollow(npchar, PChar, "", -1);
				}
				else
				{
					Dialog.Text = RandPhraseSimple("Похоже у тебя уже достаточно компаньонов.", "У тебя и так много кораблей. Зачем тебе еще один?");
					link.l1 = "Да... Кажется ты права.";
					link.l1.go = "Quest_Whisper_Finish_NoHire";
				}
			}
		break;
	}
}
