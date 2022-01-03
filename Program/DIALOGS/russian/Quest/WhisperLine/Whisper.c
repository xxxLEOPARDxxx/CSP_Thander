void ProcessDialogEvent()
{
	ref locLoad = &locations[reload_location_index];
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;
	string sTemp;
	bool hungry = true;
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":

			//dialog.text = "Ошибка";
			link.l1 = "...";
			link.l1.go = "Exit";
			npchar.quest.meeting = "1";

			if (npchar.id == "CrazyScientist")
			{
				dialog.text = "А ну, стой!";
				link.l1.go = "CS";
			}
			if (npchar.id == "FinalBot")
			{
				dialog.text = "(Вы слишком поздно замечаете бота. Уже после того, как услышали звук выстрела.)";
				LAi_LocationFightDisable(locLoad, false);
				DeleteAttribute(locLoad, "box1");
				DeleteAttribute(locLoad, "box2");
				DeleteAttribute(locLoad, "box3");
				DeleteAttribute(locLoad, "box4");
				LAi_SetActorTypeNoGroup(npchar);
				LAi_ActorAnimation(npchar, "Shot", "pchar_back_to_player", 1.0);
				link.l1 = "Чёрт!";
				link.l1.go = "FB";
			}
			if (npchar.id == "wl_Pirate_Cap")
			{

				if (!CheckAttribute(npchar, "quest.meting"))
				{
				dialog.text = "Это ещё что за каракатица на моей палубе?! Назовись!";
				link.l1 = "Где я? Как я сюда попала?";
				link.l1.go = "PC";
				npchar.quest.meting = 1;
				break;
				}
				if (npchar.quest.meting == 1)
				{
					dialog.text = "Интересные у тебя вещички, я решил, что пока оставлю их все при себе\nВряд ли ты станешь возражать. Пистоль твой, однако - очень убойная штука, к тому же выглядит необычно. Где взяла?";
					link.l1 = "Не твоё дело. Долго вы меня собираетесь здесь держать?";
					link.l1.go = "PC_2";
					npchar.quest.meting = 2;
				}
			}

			if (npchar.id == "AntonioDeSouza")
			{
				if (!CheckAttribute(npchar, "quest.meting"))
				{
					dialog.text = "Надо же, какой интересный 'экземпляр' привёл мне "+GetFullName(characterFromId("wl_Pirate_Cap"))+". Расскажи мне, демон, из какого круга ада ты вышел?";
					link.l1 = "Я не демон.";
					link.l1.go = "ADS";
					npchar.quest.meting = 1;
					break;
				}
				if (npchar.quest.meting == 1)
				{
					dialog.text = "Ну как, удалось что-то вспомнить?";
					link.l1 = "Зря вы это затеяли, отче. Я ведь и отомстить могу, когда выберусь.";
					link.l1.go = "ADS_2";
					npchar.quest.meting = 2;
					break;
				}
				if (npchar.quest.meting == 2)
				{
					dialog.text = "Не стоит надеяться на то, что я тебя пожалею, так что лучше начинай говорить. Тот пистоль. Это разработка англичан? Отвечай!";
					link.l1 = "Ладно. Я всё скажу.";
					link.l1.go = "ADS_1_truth";
					npchar.quest.meting = 3;
					break;
				}
				if (npchar.quest.meting == 3)
				{
					dialog.text = "Ну?";
					link.l1 = "Мне больше нечего вам сказать.";
					pchar.Whisper.DeSouzaHits = 3;
					link.l1.go = "ADS_1_2";
					npchar.quest.meting = 4;
					break;
				}
				if (npchar.quest.meting == 4)
				{
					dialog.text = "Очень не хочется прерывать нашу милую беседу, да только у меня на сегодня назначен встреча с губернатором. Никуда не уходи, и не скучай тут без меня, хе-хе. Завтра продолжим.";
					link.l1 = "...";
					link.l1.go = "ADS_4_exit";
					if(rand(100) < 90)
					{
						pchar.Whisper.IncqGuard_bad = true;
					}
					npchar.quest.meting = 5;
					break;
				}
			}
			if (npchar.id == "NineFingers")
			{
				if (!CheckAttribute(npchar, "quest.meting"))
				{
					dialog.text = "Ого, к нам в посёлок забрела настоящая красотка! Какими судьбами?";
					chrDisableReloadToLocation = false;
					link.l1 = "Да так, скрываюсь от костра инквизиции.";
					link.l1.go = "NF";
					npchar.quest.meting = 1;
					break;
				}
				if (npchar.quest.meting == 1)
				{
					dialog.text = "Ты это видишь? На посёлок напал карательный отряд из Сантьяго. Не по твою ли душу они пришли?";
					link.l1 = "Чёрт! Ты прав, наверное испанцы вышли на мой след. Что же нам теперь делать?";
					AddMoneyToCharacter(npchar, 777);
					npchar.SaveItemsForDead = true;
					link.l1.go = "NF_2_1";
					npchar.quest.meting = 2;
					break;
				}
			}
			if (npchar.id == "Wh_Jack")
			{
				dialog.text = "Где наш капитан? Какого чёрта у тебя его шляпа и клинок?";
				chrDisableReloadToLocation = true;
				link.l1 = "На посёлок устроили облаву испанцы, ваш капитан погиб в бою.";
				link.l1.go = "Jack";
				break;
			}
			if (npchar.id == "Wh_Jim")
			{
				dialog.text = "Дьявол! ты убила Джека! Теперь ты по праву наш капитан.";
				link.l1 = "Правда что ли? Вот так просто?";
				link.l1.go = "Jim";
				break;
			}
			if (npchar.id == "W_Lejitos")
			{
				if (!CheckAttribute(npchar, "quest.meting"))
				{
					Lai_SetPlayerType(pchar);
					npchar.DontChangeBlade = true; // нельзя снять или залутать оружие

					dialog.text = "Глупцы. Вам следовало бы знать, что зверь, загнанный в угол - опасен. А я не просто какой-то зверь, я - Ягуар. Надеюсь, вы успели помолиться своему мёртвому богу, потому что сейчас я вас к нему отправлю!";
					link.l1.go = "exit_cave_entrance_fight";
					npchar.quest.meting = 1;
					break;
				}
				if (npchar.quest.meting == 1)
				{
					Lai_SetPlayerType(pchar);
					dialog.text = "Я бы и сам справился, но всё-равно, благодарю за своевременное вмешательство. У тебя, как я вижу, есть свои счёты с испанцами?";
					link.l1 = "Да, я успела нажить себе парочку врагов. А что ты там говорил перед боем, про мёртвого бога?";
					link.l1.go = "Lejitos";
					npchar.quest.meting = 2;
					break;
				}
			}
			if (npchar.id == "W_Chard")
			{
				if (!CheckAttribute(npchar, "quest.meting"))
				{
					Lai_SetPlayerType(pchar);
					dialog.text = "Ты еще кто такая? Кажется я бордельных девок к себе в номер не заказывал.";
					link.l1 = "То есть ты позвал меня сюда только ради того, чтоб поглумиться? Еще одна такая шуточка и 'бордельная девка' вспорет тебе брюхо.";
					link.l1.go = "meet_chard";
					npchar.quest.meting = 1;
					break;
				}
				if (npchar.quest.meting == 1)
				{
					chrDisableReloadToLocation = false;
					if (CheckAttribute(pchar, "WhisperWonSword"))
					{
						dialog.text = "Поздравляю с победой. А ты неплохо играешь, гораздо лучше местных забулдыг. Забирай свой меч. Неплохой клинок, мне даже ни разу не приходилось его затачивать. А зарезать им я успел немало доходяг, другой бы давно затупился...";
						link.l1 = "(Забрать меч)";
						link.l1.go = "chard_get_sword";
					}
					else
					{
						dialog.text = "Не повезло тебе. Но ты не расстраивайся, такое с каждым может случиться\nВижу, этот клинок тебе очень дорог, я даже жалею, что сам выиграл. Вот что, если ты поможешь мне в одном дельце, я тебе его подарю. Всё равно я уже присмотрел себе новый в местной лавке.";
						link.l1 = "Какого рода помощь нужна?";
						link.l1.go = "chard_discuss_quest";
					}
					npchar.quest.meting = 2;
					break;
				}
			}
			NextDiag.TempNode = "First time";
		break;

		case "Chinaman_plead":
			npchar.ChinamanAskedSword = true;
			WhisperSelectRandomUsurer();
			LAi_SetOfficerType(NPChar);
			dialog.Text = "Капитан, я хотеть бы просить вас об услуге. Можете меня выслушать?";
			Link.l1 = "Конечно я тебя выслушаю! Ты хороший офицер, ни разу ещё не подводил меня.";
			Link.l1.go = "Chinaman_plead_1";
		break;
		case "Chinaman_plead_1":
			dialog.Text = "Спасибо за лестные слова, капитан. Тогда слушайте\nПеред тем, как я попасть в рабство, у  меня был меч. Он достался мне от моего отца, а ему - от его отца, и так на протяжении более тысяча лет. Вы понимать, насколько этот меч важен для меня?";
			Link.l1 = "Понимаю, фамильная реликвия.";
			Link.l1.go = "Chinaman_plead_2";
		break;
		case "Chinaman_plead_2":
			dialog.Text = "Всё это время я считать, что меч навсегда утерян. Но когда мы зашли в порт, я услышать разговор двух людей. Они говорить про ростовщика-коллекционера редких артефактов из разных частей света. В разговоре как раз шла речь про 'меч с пятью кольцами'. В последний раз правда в моем мече быть девять коцец, но я всё равно уверен, что речь шла про мой. Должно быть эти варвары его испортить. Прошу вас, капитан, помогите вернуть его!";
			Link.l1 = "Ростовщик, говоришь? Где его искать?";
			Link.l1.go = "Chinaman_plead_3";
		break;
		case "Chinaman_plead_3":
			sld = characterFromId(pchar.Whisper.UsurerId);
			//Lai_SetStayType(npchar);
			dialog.Text = XI_ConvertString("Colony" + sld.city) +". Это место называть те люди.";
			NextDiag.TempNode = "Hired";
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			SetQuestHeader("WhisperChinamanRelic");
			AddQuestRecord("WhisperChinamanRelic", "1");
			AddQuestUserData("WhisperChinamanRelic", "sCity", XI_ConvertString("Colony" + sld.city+ "Gen"));
			Link.l1 = "Хорошо, если будем в этом городе, загляну ростовщику.";
			Link.l1.go = "exit";
		break;
		case "Chinaman_plead_4":
			dialog.Text = "Спасибо вам, капитан. Я знать, что и так уже многим вам обязан. Но если поможете - клянусь, буду верен вам до самого конца.";
			Link.l1 = "Хорошо, если будем в тех местах, загляну ростовщику.";
			Link.l1.go = "exit";
		break;

		case "chard_waiting_quest_result":
			dialog.Text = "Ну, как успехи по нашему делу?";
			if (!CheckAttribute(npchar,"DiscussedEsteban"))
			{
				Link.l2 = "А что тебя связывает с Эстебаном? Ты ведь даже не испанец.";
				Link.l2.go = "chard_discuss_esteban"
			}
			if (!CheckAttribute(pchar,"Whisper.FoundPortmanJournal") && !CheckAttribute(pchar,"Whisper.ActiveChardQuest"))
			{
				Link.l1 = "Прости, но у меня не вышло его допросить. И документы вытащить тоже. Корабль Портмана пошёл ко дну...";
				Link.l1.go = "chard_failed"
				break;
			}
			if (CheckAttribute(pchar,"Whisper.FoundPortmanJournal"))
			{
				Link.l1 = "Я нашла у Портмана этот журнал. Думаю, там есть ответ на интересующий тебя вопрос.";
				Link.l1.go = "chard_check_journal"
				break;
			}
			if (CheckAttribute(pchar,"Whisper.BetrayChard"))
			{
				Link.l1 = "Мне не очень-то понравилась твоя затея. Ничего личного, но я рассказала о ней Портману. Он предложил награду за возвращение своей книжки.";
				Link.l1.go = "chard_betrayed"
				break;
			}
			Link.l1 = "Пока что никак.";
			Link.l1.go = "exit";

		break;
		case "chard_check_journal":
			Log_Info("Вы отдали журнал");
			PlaySound("interface\important_item.wav");
			dialog.Text = "Посмотрим... Здесь тоже все зашифровано. Мне понадобится время. Несколько часов. Можешь пока погулять.";
			Link.l1 = "Я подожду здесь.";
			Link.l1.go = "chard_check_journal_1";
		break;
		case "chard_check_journal_1":
			dialog.Text = "Не доверяешь мне? Ладно, можешь прилечь пока на кровати.";
			Link.l1 = "...";
			Link.l1.go = "chard_check_journal_2";
		break;
		case "chard_check_journal_2":
			chrDisableReloadToLocation = true;
			LAi_Fade("", "");
			WaitDate("",0,0,0,12,3);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			NextDiag.TempNode = "chard_check_journal_after";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "chard_check_journal_after":
			AddQuestRecord("WhisperChardQuest", "8");
			chrDisableReloadToLocation = false;
			dialog.Text = "Если я правильно понял, клад находится на Доминике. Более точное место скажу как доберёмся туда.";
			Link.l1 = "Тогда не будем медлить. Готовь свой бриг.";
			npchar.Ship.Type = GenerateShipExt(SHIP_PDN, true, npchar);
			npchar.Ship.name = "Любимец удачи";
			SetBaseShipData(npchar);
			npchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS16;
			SetCharacterGoods(npchar,GOOD_FOOD,500);
			SetCharacterGoods(npchar,GOOD_BALLS,500);
			SetCharacterGoods(npchar,GOOD_GRAPES,500);
			SetCharacterGoods(npchar,GOOD_KNIPPELS,500);
			SetCharacterGoods(npchar,GOOD_BOMBS,500);
			SetCharacterGoods(npchar,GOOD_POWDER,1000);
			SetCharacterGoods(npchar,GOOD_PLANKS,150);
			SetCharacterGoods(npchar,GOOD_SAILCLOTH,150);
			SetCharacterGoods(npchar,GOOD_RUM,200);
			SetCharacterGoods(npchar,GOOD_WEAPON,250);
			SetCharacterGoods(npchar,GOOD_MEDICAMENT,300);
			SetCharacterRemovable(npchar, false);
			SetCompanionIndex(pchar, -1, sti(NPChar.index));
			Link.l1.go = "exit_chard_setsail";
		break;
		case "exit_chard_setsail":
			NextDiag.TempNode = "chard_on_dominica";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.WhisperChardCompanion = true;
			DialogExit();
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", pchar.Whisper.EsFriendTown+"_tavern", "", "", "", 7);
			LocatorReloadEnterDisable(pchar.Whisper.EsFriendTown+"_tavern", "reload2_back", true);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.Whisper.EsFriendTown+"_tavern_upstairs")], false);
			DeleteAttribute(pchar,"Whisper.EsFriendTown");

			pchar.quest.WhisperChardShore26.win_condition.l1          = "location";
			pchar.quest.WhisperChardShore26.win_condition.l1.location = "shore26";
			pchar.quest.WhisperChardShore26.function             = "WhisperChardShore";
			pchar.quest.WhisperChardShore27.win_condition.l1          = "location";
			pchar.quest.WhisperChardShore27.win_condition.l1.location = "shore27";
			pchar.quest.WhisperChardShore27.function             = "WhisperChardShore";
		break;
		case "chard_on_dominica":
			dialog.Text = "Вот мы и на месте. Клад совсем рядом, осталось найти грот.";
			Link.l1 = "Ну пойдём.";
			Link.l1.go = "chard_follow";
		break;
		case "chard_follow":
			NextDiag.TempNode = "chard_in_cave";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorFollowEverywhere(npchar, "", -1);

			pchar.quest.WhisperChardCave.win_condition.l1          = "location";
			pchar.quest.WhisperChardCave.win_condition.l1.location = "Dominica_grot";
			pchar.quest.WhisperChardCave.function             = "WhisperChardCave";
		break;
		case "chard_in_cave":
			if (!CheckAttribute(pchar, "cursed.waitingSkull"))
			{
				pchar.cursed.waitingSkull = true;
				pchar.cursed.lockspawn = true;
			}
			if (CheckAttribute(pchar, "WhisperWonSword"))
			{
				dialog.Text = "Ха-ха-ха! А этот клинок по мне! Гляди какой широкий. И в руках отдает приятной тяжестью. Загляни в сундук, может и для себя что-то интересное найдёшь.";
			}
			else
			{
				Log_Info("Вы вернули свой меч");
				GiveItem2Character(pchar, "blade_whisper");
				EquipCharacterByItem(pchar, "blade_whisper");
				PlaySound("interface\important_item.wav");
				dialog.Text = "Ха-ха-ха! А этот клинок по мне! Гляди какой широкий. И в руках отдает приятной тяжестью. И кстати, я же обещал, отдаю тебе твой меч-пёрышко. Не забудь заглянуть в сундук, может и для себя что-то интересное найдёшь.";

			}
			Link.l1 = "Ну ты шустрый! Небось, все самое ценное уже оттуда вытащил. Пойду, гляну...";
			Link.l1.go = "chard_exit_to_cave_entrance";

			ref _location = &locations[reload_location_index];
			//DeleteAttribute(_location, "box1");
			_location.box1.money = 300000;
			_location.box1.items.icollection = 1;
			_location.box1.items.Map_Best = 1;
			_location.box1.items.suit_2 = 1;
			//_location.box1.items.indian11 = 1;
			_location.box1.items.chest = 5;
			_location.box1.items.chest_quest = 2;
			_location.box1.items.jewelry1 = 30+rand(5);
			_location.box1.items.jewelry2 = 30+rand(5);
			_location.box1.items.jewelry3 = 30+rand(5);
			_location.box1.items.jewelry4 = 15+rand(5);
			_location.box1.items.jewelry6 = rand(55);
			_location.box1.items.jewelry7 = rand(70);
			_location.box1.items.jewelry10 = rand(55);
			_location.box1.items.jewelry14 = rand(55);
			_location.box1.items.jewelry15 = rand(8);
			_location.box1.items.jewelry18 = rand(90);

		break;
		case "chard_exit_to_cave_entrance":
			chrDisableReloadToLocation = false;
			NextDiag.TempNode = "chard_cave_entrance";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "Dominica_caveentrance", "", "", "", 7);
			pchar.quest.WhisperChardCave.win_condition.l1          = "location";
			pchar.quest.WhisperChardCave.win_condition.l1.location = "Dominica_caveentrance";
			pchar.quest.WhisperChardCave.function             = "WhisperChardCave";
		break;

		case "chard_cave_entrance":
			if (CheckAttribute(pchar, "cursed.lockspawn"))
			{
				DeleteAttribute(pchar, "cursed.waitingSkull");
				DeleteAttribute(pchar, "cursed.lockspawn");

			}
			pchar.quest.WhisperChardCave.win_condition.l1          = "location";
			pchar.quest.WhisperChardCave.win_condition.l1.location = pchar.location.from_sea;
			pchar.quest.WhisperChardCave.function             = "WhisperEngRevengeWarning";
			LocatorReloadEnterDisable("shore26", "boat", false);
			LocatorReloadEnterDisable("shore27", "boat", false);
			WhisperEnglandRevengel();
			pchar.ContraInterruptWaiting = true;
			dialog.Text = "Согласись, большой ведь куш мы урвали. Там добычи было столько, что мне даже не жалко поделиться с тобой. Я смогу пропивать это несколько лет. Ну ладно, будем разбегаться?";
			Link.l2 = "Да, мне тоже надо разобраться со своей долей. Удачи тебе.";
			Link.l2.go = "chard_exit_to_cave_entrance_1";
			if (CheckAttribute(pchar, "WhisperWonSword"))
			{
				Link.l1 = "Погоди, приятель. Не хочешь и дальше плавать со мной? Уверена, вместе мы найдём ещё немало добычи.";
				Link.l1.go = "chard_discuss_recruitment";
			}
		break;
		case "chard_discuss_recruitment":
			dialog.Text = "Хм... Я хожу только с теми, в удаче кого я абсолютно уверен. Ты обыграла меня в карты, но я в них не так силен, как в костях. Давай проверим. Если удача на самом деле тебя любит, то ты выиграешь, а я пойду за тобой хоть на край света. Правила те же, до пяти побед.";
			Link.l1 = "Хорошо. Играем.";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 0;
            pchar.GenQuest.Dice.SitType   = false;
			Link.l1.go = "meet_chard_dice_begin_go";
			Link.l2 = "Не, не хочу я сегодня играть, давай тогда разбежимся. Удачи тебе.";
			Link.l2.go = "chard_exit_to_cave_entrance_1";
		break;
		case "meet_chard_dice_begin_go":
			chrDisableReloadToLocation = true;
			NextDiag.TempNode = "chard_after_dice_game";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchDiceGame();
			Lai_SetStayType(npchar);
		break;
		case "chard_after_dice_game":
			chrDisableReloadToLocation = false;

			if(CheckAttribute(pchar, "WhisperWonChard"))
			{
				LAi_SetImmortal(NPChar, false);
				SetCharacterRemovable(npchar, true);
				dialog.Text = "Да, удачи тебе не занимать. Так и быть, я доверяю тебе свою жизнь.";
				Link.l1 = "Вот и отлично. Сядешь в брандер. Шутка... Пойдём.";
				Link.l1.go = "chard_hired";
			}
			else
			{
				dialog.Text = "Похоже, сама судьба вмешалась. Как ни прискорбно, ничего у нас не выйдет.";
				Link.l1 = "Ну ладно. Тогда удачи тебе.";
				Link.l1.go = "chard_exit_to_cave_entrance_1";
			}
		break;
		case "chard_exit_to_cave_entrance_1":
			dialog.Text = "И тебе. Держи всегда туз в рукаве! Вот тебе сувенир на удачу, из моей доли.";
			npchar.LifeDay = 0;
			TakeNItems(pchar, "indian11", 1);
			Log_Info("Вы получили обноски");
			PlaySound("interface\important_item.wav");
			Link.l1 = "Спасибо! Прощай.";
			Link.l1.go = "chard_exit_to_cave_entrance_2";
		break;
		case "chard_hired":
			chrDisableReloadToLocation = false;
			DialogExit();
			Lai_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2_back", "Dominica_grot", "", "", "", 12);
			SetCharacterPerk(npchar, "Adventurer");
			NPChar.Payment = true;
			//npchar.greeting = "Gr_QuestOfficer";
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.HalfImmortal = true;  // Контузия
			npchar.loyality = MAX_LOYALITY;
			//AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = true;
			npchar.Dialog.CurrentNode = "hired";
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
		break;
		case "chard_exit_to_cave_entrance_2":
			chrDisableReloadToLocation = false;
			//NextDiag.TempNode = "chard_cave_entrance";
			//NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			Lai_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2_back", "Dominica_grot", "", "", "", 12);
		break;

		case "chard_failed":
			dialog.Text = "Эх, мне показалось что ставка верная, однако не стоило тебе доверять. Уйди с глаз моих...";
			LAi_SetImmortal(NPChar, true);
			npchar.LifeDay = 0;
			Link.l1 = "Да не злись ты так, ухожу уже.";
			Link.l1.go = "exit";
			LocatorReloadEnterDisable(pchar.Whisper.EsFriendTown+"_tavern", "reload2_back", true);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.Whisper.EsFriendTown+"_tavern_upstairs")], false);
			DeleteAttribute(pchar,"Whisper.EsFriendTown");
		break;
		case "chard_betrayed":
			NPChar.rank = 77;
			LAi_SetHP(NPChar, 777.0, 777.0);
			if (CheckAttribute(pchar, "WhisperWonSword"))
			{
				NPChar.money = 77777;
			}
			else
			{
				NPChar.money = 277777;
			}
			chrDisableReloadToLocation = true;
			pchar.Whisper.BetrayChardKill = true;
			TakeNItems(npchar, "bible", 1);
			npchar.SaveItemsForDead = true;
			dialog.Text = "Эх, мне показалось что ставка верная, однако не стоило тебе доверять\nПосмотрим, кому сегодня улыбнется удача. Скрестим клинки!";
			Link.l1 = "Я вижу, для тебя это такая же игра, как и карты. Тебе же хуже.";
			Link.l1.go = "chard_fight";
			LocatorReloadEnterDisable(pchar.Whisper.EsFriendTown+"_tavern", "reload2_back", true);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.Whisper.EsFriendTown+"_tavern_upstairs")], false);
			DeleteAttribute(pchar,"Whisper.EsFriendTown");
		break;
		case "chard_fight":
			Group_FindOrCreateGroup("EnemyFight");
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
			LAi_SetWarriorType(NPChar);
			LAi_SetImmortal(NPChar, false);
			//ref sld;
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		break;
		case "chard_discuss_esteban":
			npchar.DiscussedEsteban = true;
			dialog.Text = "Мы с ним были давними знакомыми, даже ходили под под одним парусом когда были простыми матросами. Наш капитан набирал в команду всех, не смотря на национальность. Но это было много лет назад. В конце концов Эрнан пошёл служить к себе на родину, а я унаследовал от кэпа корабль\nМы долгое время с тех пор не виделись, но недавно снова встретились и решили разыграть несколько партеек в карты. Похоже, что за годы службы он растерял всю свою былую удачу, так как я обыграл его довольно быстро. В итоге он остался мне должен крупную сумму денег. По старой дружбе, я не стал сильно торопить его с оплатой. Но ему не нравилась сама мысль, что он кому-то должен, тем более мне, так что Эрнан решил, что будет грабить всех без разбора, пока не накопит сумму, что похоже не понравилось его работодателю. А в конце он сказал что пойдёт за бордельным кладом, якобы ценности оттуда с лихвой покроют карточный долг. В существовании этого клада я сомневался, и похоже не зря.\nЯ не хотел его оптускать, но Эрнан настаивал на своём. В итоге мы договорились, что он перед отплытием расплатится со мной хотя бы частично. Я забрал этот меч и ещё одну вещицу, но похоже навсегда потерял шанс получить с него оставшуюся сумму.";
			Link.l1 = "Ты упомянул какую-то вещицу. Что это?";
			Link.l1.go = "chard_discuss_esteban_1";
			//Link.l1 = "Ты не собираешься мстить мне за смерть своего друга?";
			//Link.l1.go = "chard_discuss_esteban_1";
		break;
		case "chard_discuss_esteban_1":
			dialog.Text = "Сам не знаю, мне показалась просто красивой безделушкой. Я ее продал на следующий же день какому-то типу в капюшоне, что вдруг ко мне заявился.";
			Link.l1 = "Как выглядела эта безделушка?";
			Link.l1.go = "chard_discuss_esteban_2";
		break;
		case "chard_discuss_esteban_2":
			dialog.Text = "Металлическая пластина, на которую прикрепили кучу стеклянных трубок и рычажков. А еще она была покрыта странными надписями и прочей мишурой.";
			Link.l1 = "Проклятье, это же моя машина времени!";
			Link.l1.go = "chard_discuss_esteban_3";
		break;
		case "chard_discuss_esteban_3":
			dialog.Text = "Чего?";
			Link.l1 = "Ничего. Куда ушел этот твой покупатель?";
			Link.l1.go = "chard_discuss_esteban_4";
		break;
		case "chard_discuss_esteban_4":
			dialog.Text = "Понятия не имею, после нашей сделки я сам хотел его отыскать и показать еще парочку предметов на продажу, но не смог. Он словно испарился. Ни трактирщик, ни портовый начальник его не видели. Я почти было поверил, что сам его никогда не видел, если бы не тяжесть в моем кошельке. Возможно, он заплатил этим людям кругленькую сумму за молчание.";
			Link.l1 = "Ясно, опять тупик, но, по крайней мене, у меня появилась надежда. Спасибо за информацию.";
			Link.l1.go = "exit";
		break;
		case "chard_discuss_esteban_old":
			dialog.Text = "У тебя с ним были свои счеты, я не могу за это осуждать. Да и на Карибах люди убивают друг друга каждый день, мне такое уже стало безразлично. А вот потерять крупного должника - всегда обидно. Но спрашивать с тебя за него я не буду.";
			Link.l1 = "Ясно.";
			Link.l1.go = "exit";
		break;
		case "chard_discuss_quest":
			dialog.Text = "Однажды я побывал на Бермудах. Там, в подземелье, я нашёл чей-то клад, полный всяких драгоценностей, а также библию. Ее я поначалу отложил и не обращал внимания, но когда пропил свою долю клада, решил из любопытства полистать. Помимо того, что она вся была написана на латыни или каком-то другом странном языке, в ней не было ничего примечательного. За исключением нескольких подчеркнутых фраз, разбросанных по всей книге. Как я потом понял, это был шифр. Мне с командой понадобилось несколько дней, чтоб его разгадать\nВ этом скрытом послании говорилось о кладе куда больших размеров, собраном усилиями группы корсаров, даже прилагались координаты его местонахождения. Вот только не полные, часть страниц испортилась. Для получения точного места мне не хватает одного числа. Также в книге говорилось о некоем Ральфе Портмане, то ли это товарищ того, кто оставил библию, то ли сам владелец. Возможно это слабая зацепка, да и людей с таким именем на Карибах может быть много, но я все же копнул глубже и узнал, что есть такой капер на службе у англичан. ";
			Link.l1 = "Ты очень много уже рассказал, но так и не перешел к сути. Я тебе зачем?";
			Link.l1.go = "chard_discuss_quest_1";
		break;
		case "chard_discuss_quest_1":
			//NextDiag.TempNode = "chard_discuss_quest_1";
			dialog.Text = "Мне нужно, чтобы ты отыскала этого Портмана и узнала недостающую координату, если такая у него имеется.";
			Link.l1 = "Почему же ты сам этого не сделаешь?";
			Link.l1.go = "chard_discuss_quest_2";
		break;
		case "chard_discuss_quest_2":
			dialog.Text = "Видишь ли, в моем владении находится лишь скромный бриг, а у Портмана - несколько фрегатов. Боюсь, если дело дойдёт до боя, от моей лоханки только мокрое место останется. Но твой 'Пёс' без проблем их одолеет.";
			Link.l1 = "Корвет против группы фрегатов? Что-то я сомневаюсь.";
			Link.l1.go = "chard_discuss_quest_3";
		break;
		case "chard_discuss_quest_3":
			dialog.Text = "Ты наверное только недавно пересела на 'Пса'. Этот корвет ничем не уступает фрегатам, во многом даже превосходит их. Но если все же сомневаешься в своих силах, можешь навестить Алексуса.";
			Link.l1 = "Алексус? Кто это?";
			Link.l1.go = "chard_discuss_quest_4";
			Link.l2 = "Ладно, я подумаю. Где вообще искать этого англичанина?";
			Link.l2.go = "chard_discuss_quest_5";
		break;
		case "chard_discuss_quest_4":
			dialog.Text = "Ну как же, мастер-корабел, лучший во всем архипелаге. У него на Бермудах своя верфь есть. Можешь показать ему свой корабль. Хоть 'Пёс' и хорош, я уверен, Алексус найдет способы, как его можно улучшить. Тогда ты без проблем расправишься с любой эскадрой.";
			Link.l2 = "Ладно, я подумаю. Где вообще искать этого англичанина?";
			Link.l2.go = "chard_discuss_quest_5";
		break;
		case "chard_discuss_quest_5":
			NextDiag.TempNode = "chard_waiting_quest_result";
			//SaveCurrentNpcQuestDateParam(pchar,"Whisper.LastSeenPortman");
			pchar.Whisper.ActiveChardQuest = true;
			AddQuestRecord("WhisperChardQuest", "2");
			dialog.Text = "В последний раз я его видел в местных водах, но тогда не решился действовать, а он уплыл. Я думаю, ты без проблем сможешь его найти. Поспрашивай в портовых управлениях, наверняка где-то его видели\nКак справишься - возвращайся сюда. Я совмещу координаты и получу точное место клада.";
			Link.l2 = "Хорошо, прощай.";
			Link.l2.go = "exit";
		break;
		case "chard_get_sword":
			Log_Info("Вы вернули свой меч");
			GiveItem2Character(pchar, "blade_whisper");
			EquipCharacterByItem(pchar, "blade_whisper");
			PlaySound("interface\important_item.wav");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			DeleteAttribute(npchar, "items");
			DeleteAttribute(npchar, "equip");
			GiveItem2Character(npchar, "pistol4");
			EquipCharacterbyItem(npchar, "pistol4");
			GiveItem2Character(npchar, "blade39");
			EquipCharacterByItem(npchar, "blade39");
			dialog.Text = "Раз уж ты здесь, и корабль неплохой имеешь, не откажешься ли помочь мне в одном дельце?";
			Link.l1 = "Какого рода помощь нужна?";
			Link.l1.go = "chard_discuss_quest";
		break;
		case "chard_not_played":
			dialog.Text = "Опять ты? Что, надумала сыграть со мной?";
			if (sti(pchar.money) >= 200000)
			{
				Link.l1 = "Ладно, раздавай карты.";
				Link.l1.go = "meet_chard_7_cardGame";
			}
			Link.l2 = "Нет.";
			Link.l2.go = "exit";
		break;
		case "meet_chard":
			NextDiag.TempNode = "chard_not_played";
			dialog.Text = "Я звал тебя? Прости, не припомню. Наверное я был слишком пьян... Ты кто собственно такая?";
			Link.l1 = "Виспер. Капитан корвета 'Пёс Войны'.";
			Link.l1.go = "meet_chard_1";
		break;
		case "meet_chard_1":
			dialog.Text = "Капитан? Погоди, а куда подевался Эстебан?";
			Link.l1 = "Трагически погиб у Теркса. Там на него устроили засаду.";
			Link.l1.go = "meet_chard_2";
			Link.l2 = "Я прикончила этого подонка.";
			Link.l2.go = "meet_chard_3";
		break;
		case "meet_chard_2":
			dialog.Text = "А ведь я говорил ему, что с этим кладом что-то нечистое. Как чуял западню. ";
			Link.l1 = "(Ваш взгляд привлекает знакомая рукоять клинка, что висит на поясе у незнакомца.) Погоди-ка... Это же мой меч! ";
			Link.l1.go = "meet_chard_4";
		break;
		case "meet_chard_3":
			dialog.Text = "С тем, что он подонок, не поспоришь\nДа как он посмел умирать, не вернув сначала мне долг?";
			Link.l1 = "(Ваш взгляд привлекает знакомая рукоять клинка, что висит на поясе у незнакомца.) Погоди-ка... Это же мой меч! ";
			Link.l1.go = "meet_chard_4";
		break;
		case "meet_chard_4":
			dialog.Text = "Ничего не знаю. Этот клинок мой, я честно выиграл его в карты у Эстебана\nА... Кажется, я понял, кто ты, Виспер. Эстебан ведь говорил про девку, у которой отобрал пистоль и меч. Очень приятно наконец познакомиться, я Майкл Чард. Правда он сказал мне, что прикончил тебя.";
			Link.l1 = "Как видишь, я живее всех живых, в отличие от этого пустозвона. А теперь отдавай сюда меч! ";
			Link.l1.go = "meet_chard_5";
		break;
		case "meet_chard_5":
			dialog.Text = "Ишь, чего удумала! Просто так я ничего тебе не дам\nНо все же, этот меч мне не особо по нраву, слишком уж лёгкий, а я люблю более увесистое оружие. Знаешь что? Давай сыграем в карты. Выиграешь - он твой. Выиграю я - заплатишь. Скажем... двести тысяч.";
			Link.l1 = "Сколько? Ты что, головой ударился?";
			Link.l1.go = "meet_chard_6";
			if (sti(pchar.money) >= 200000)
			{
				Link.l2 = "Идет, раздавай карты.";
				Link.l2.go = "meet_chard_7_cardGame";
			}
			Link.l3 = "Давай как-нибудь в другой раз.";
			Link.l3.go = "exit";
		break;
		case "meet_chard_6":
			dialog.Text = "За меньшую сумму я играть не собираюсь. Либо играем, либо вали отсюда.";
			if (sti(pchar.money) >= 200000)
			{
				Link.l1 = "Ладно, раздавай карты.";
				Link.l1.go = "meet_chard_7_cardGame";
			}
			Link.l2 = "Давай как-нибудь в другой раз.";
			Link.l2.go = "meet_chard_8";
		break;
		case "meet_chard_8":
			dialog.Text = "Возвращайся, если передумаешь.";
			Link.l1 = "Прощай.";
			Link.l1.go = "exit";
		break;
		case "meet_chard_7_cardGame":
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			dialog.Text = "Вот это по нашему! Играем до пяти побед.";
			Link.l1 = "Идет.";
			Link.l1.go = "meet_chard_Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			int iLa_Puesta = 0;
			pchar.GenQuest.Cards.iRate     = sti(iLa_Puesta);
            pchar.GenQuest.Cards.SitType   = true;
		break;
		case "meet_chard_Cards_begin_go":
				chrDisableReloadToLocation = true;
                //Diag.CurrentNode = Diag.TempNode;
                DialogExit();
                LaunchCardsGame();
		break;

		case "LejitosOff":
			NPChar.Payment = true;
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			//npchar.greeting = "Gr_QuestOfficer";
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.HalfImmortal = true;  // Контузия
			npchar.loyality = MAX_LOYALITY;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = true;
			//LAi_SetWarriorType(NPChar);
			DialogExit();
		break;
		case "LejitosNoOff":
			DialogExit();
			NPChar.lifeday = 0;
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 10);
		break;
		case "Lejitos":
			dialog.Text = "Я не христианин. Мои родители ими были когда-то, но они не прожили достаточно долго, чтоб навязать мне эту веру. Меня нашли, вырастили и воспитали в племени индейцев Гуарани. Они открыли мне глаза на истинную веру и рассказали всю суть про христианского Бога.";
			Link.l1 = "Ты прожил всю жизнь среди индейцев?";
			Link.l1.go = "Lejitos_1";
		break;
		case "Lejitos_1":
			dialog.Text = "К сожалению, испанцы не дали мне такой роскоши. Однажды я отправился на охоту, а когда вернулся домой с добычей - застал нашу деревню в руинах. Всё племя было истреблено. Я конечно же отомстил, но племя этим не вернёшь\nПосле этого я подался жить к испанцам, в так называемом цивилизованном обществе. Несколько лет я жил в спокойствии, осваиваясь на новом месте, пока однажды кто-то не рассказал местному священнику о безобидных индейских ритуалах, что я проводил перед принятием еды. Тот в свою очередь донёс это до инквизиции, а что было дальше думаю ты и сама можешь понять\nС тех пор я скрывался от испанцев в голландских колониях, но даже здесь мне не дают покоя. Это далеко не первая и не последняя группа охотников, что приходит за моей головой.";
			Link.l1 = "Лично мне всё-равно, во что ты веришь. Но как боец я вижу, что ты - настоящий зверь. Не хочешь пойти ко мне на службу? Обещаю, будучи у меня в команде ты перебьёшь немало испанцев. Прямо сейчас я намереваюсь догнать тот корабль, про который говорил один из этих подонков.";
			Link.l1.go = "Lejitos_2";
			Link.l2 = "Не думаю, что нам с тобой по пути, приятель. Прощай.";
			Link.l2.go = "LejitosNoOff";
		break;
		case "Lejitos_2":
			dialog.Text = "Ты умеешь убеждать. Конечно же, я не откажусь добавить ещё парочку испанских скальпов себе в коллекцию.";
			Link.l1 = "Вот и договорились. Кстати, мне говорили, что ты направился в эту пещеру за кладом. Удалось найти что-нибудь?";
			Link.l1.go = "Lejitos_3";
		break;
		case "Lejitos_3":
			dialog.Text = "Это не клад, а индейская реликвия. Я могу отдать её тебе на хранение, только прошу, не продавай. Её наверняка переплавят в слитки, после чего её настоящая ценность будет навсегда утеряна.";
			Link.l1 = "Ну ладно, пойдем.";
			Link.l1.go = "LejitosOff";
		break;

		case "DeSouzaHunter":
			dialog.Text = "Надо же, кто пришёл! Похоже, мы убьём одним выстрелом сразу двух зайцев! Этого безбожника Элихио уже было бы достаточно, чтобы обрадовать сеньора де Соузу, но когда мы приведём ему ещё и тебя, нам наверняка выдадут премию!";
			Link.l1 = "Де Соуза, говоришь? А где же он сам?";
			Link.l1.go = "DeSouzaHunter_1";
		break;
		case "DeSouzaHunter_1":
			AddQuestRecord("WhisperQuestline", "6");
			dialog.Text = "Что, не терпится получить от него свежую порцию пыток? Уверяю, ждать осталось недолго, ведь он здесь, недалеко, на корабле. Мы причалили в бухте с ироничным для тебя названием - Берег Спасения\nНа корабле все инструменты уже подготовлены. Ты же Виспер, верно? Я видел там железную деву, подписанную твоим именем\nНу так как, сама пойдёшь? Или сначала хочешь отхватить порцию и от нас? Вам, сеньор Лехито, я тот же вопрос задаю.";
			Link.l1 = "Сейчас посмотрим, кто от кого получит!";
			Link.l1.go = "exit_lejitos_speak";
		break;
		case "exit_lejitos_speak":
			DialogExit();
			sld = characterFromID("W_Lejitos");
			SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 4.0);
		break;
		case "exit_cave_entrance_fight":
			AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
			LAi_SetWarriorType(NPChar);
			LAi_SetImmortal(NPChar, false);
			//ref sld;
			for (int i = 1; i <= 7; i++)
			{
				sld = characterFromID("DeSouzaHunter"+sti(i));
				LAi_SetWarriorType(sld);
				LAi_SetImmortal(sld, false);
				LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
			}
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		break;
		case "Smuggler":
			NextDiag.TempNode = "Smuggler";
			if (CheckAttribute(pchar, "Whisper.ContraSmuggler"))
			{
				dialog.Text = "Ты ещё кто такая? Чего тебе здесь надо?";
				Link.l1 = "У нас с вами есть один общий знакомый по имени "+GetCharacterFullName("Tortuga_trader")+". Я привезла товар, как договаривались.";
				Link.l1.go = "Whisper_contraband";
				Link.l2 = "Ничего.";
				Link.l2.go = "exit";
			}
			else
			{
				dialog.Text = "Сделка состоялась, а теперь вали отсюда, нечего глаза мозолить!";
				Link.l1 = "Ухожу, только дерзить мне не надо.";
				Link.l1.go = "exit";
			}

		break;
		case "Whisper_contraband":
			if(Pchar.Location != Pchar.location.from_sea)
			{
				dialog.Text = "Это всё очень интересно, но корабль твой где? Или ты весь товар на горбу принесла?";
				Link.l1 = "Корабль будет, я просто сначала место проверить хотела.";
				Link.l1.go = "Whisper_contraband_2";
				break;
			}
			if(GetSquadronGoods(Pchar, GOOD_EBONY) >= 100)
			{
				DeleteAttribute(pchar, "Whisper.ContraSmuggler");
				dialog.Text = "Вижу. Похоже, всё в порядке. Мои рабы... то есть работники, мигом всё выгрузят. Вот твои деньги.";
				AddMoneyToCharacter(PChar, 50000);
				RemoveCharacterGoods(Pchar, GOOD_EBONY, 100);
				Link.l1 = "Неплохая сумма, спасибо.";
				Link.l1.go = "Whisper_contraband_1";

				break;
			}
			if(GetSquadronGoods(Pchar, GOOD_EBONY) < 100 && GetSquadronGoods(Pchar, GOOD_EBONY) > 0)
			{
				dialog.Text = "У тебя не хватает товара. Возвращайся, когда соберёшь.";
				Link.l1 = "И правда. Жди, сейчас докуплю и вернусь.";
				Link.l1.go = "Whisper_contraband_2";
				break;
			}
			if(GetSquadronGoods(Pchar, GOOD_EBONY) == 0)
			{
				dialog.Text = "Издеваешься? У тебя в трюме вообще нет нужного товара!";
				Link.l1 = "Кажется, я его куда-то переложила. Никуда не уходи, я сейчас.";
				Link.l1.go = "Whisper_contraband_2";
			}
		break;
		case "Whisper_contraband_1":
			dialog.Text = "Кстати, если ещё что интересное найдёшь, сразу нам неси, а то "+GetCharacterFullName("Tortuga_trader")+" собирается завязывать с подобными сделками. Одного нашего представителя ты всегда сможешь найти в таверне.";
			WhisperRemoveSmugglersFromShore();
			AddQuestRecord("WhisperContraband", "3");
			CloseQuestHeader("WhisperContraband");
			Link.l1 = "Хорошо, я это учту.";
			Link.l1.go = "exit";
			//pchar.quest.WhisperChinaman.win_condition.l1 = "ExitFromLocation";
			pchar.quest.WhisperChinaman.win_condition.l1 = "EnterToSea";
			pchar.quest.WhisperChinaman.function    = "WhisperChinaman";
			WhisperSmugglingPatrol();
			pchar.ContraInterruptWaiting = true;
			//CaptainComission_GenerateCoastalPatrol();

		break;
		case "Whisper_contraband_2":
			dialog.Text = "И пошустрей давай, я всю жизнь в этой бухте торчать не собираюсь.";
			Link.l1.go = "exit";
		break;

		case "Jim":
			dialog.text = "После того, как ты разделалась с Джеком, никто из команды тебе перечить не пожелает. Он держал в страхе всех. К тому же, у нас на корабле традиция такая - после смерти старого капитана, новым назначать самого отчаянного рубаку, который перебьёт остальных претендентов на шляпу. Такой капитан не побоится привести нас к самой богатой добыче. ";
			link.l1 = "Знаешь, мне нравится ваша традиция. А много ли уже капитанов сменилось?";
			link.l1.go = "Jim_1";
		break;
		case "Jim_1":
			dialog.text = "Прилично.  Не зря же корабль 'Чёрной Вдовой' кличут. На этом посту успели побывать люди всех мастей, возрастов и полов. В среднем кэп удерживает своё положение несколько месяцев, а дальше либо по какой-то нелепой случайности погибает, либо команда бунтует. Билл был самым удачливым - три года продержался. ";
			link.l1 = "Мрачную картину ты мне описал. Кажется, будто эта ваша 'Вдова' - проклята. Но от меня так просто не избавиться. Я согласна стать капитаном, правда не сказала бы, что разбираюсь в управлении кораблём.";
			link.l1.go = "Jim_2";
		break;
		case "Jim_2":
			SetQuestHeader("WhisperContraband");
			AddQuestRecord("WhisperContraband", "1");
			pchar.Whisper.Contraband = true;
			pchar.Whisper.FindDesouza = true;
			SetTimerCondition("W_Smuggling", 0, 0, 60, false);
			dialog.text = "Ничего, научишься. Билл поначалу тоже не умел, но тем не менее стал самым успешным капитаном 'Вдовы'. Мы, если что, поможем, на первых порах. Кстати, у Билла при себе ещё была карта архипелага, если ты её нашла - пользуйся, чтобы проще было ориентироваться на море\nИ если не знаешь с чего начать - загляни в его судовой журнал. Там заметки, что составлял Билл. Мы вроде собирались отвезти товар кому-то на Тортуге, но всех подробностей я не знаю, так что лучше сама прочитай.";
			link.l1 = "Хорошо, почитаю на досуге. А где наш кораблик?";
			link.l1.go = "Jim_EndLine";
		break;
		case "Jim_EndLine":
			dialog.text = "Да прямо здесь, в бухте. Подходи к берегу и залезай в шлюпку\nИ еще. Дело, которое затевал Билл наверняка не совсем законное. Советую переодеться во что-нибудь неприметное, прежде чем за него браться. У нас на корабле полно всякого тряпья, можешь подобрать себе что-нибудь.";
			TakeNItems(pchar, "suit_1", 1);
			Log_Info("Вы получили обноски");
			PlaySound("interface\important_item.wav");
			link.l1 = "...";
			link.l1.go = "Finish";
		break;
		case "Finish":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			LocatorReloadEnterDisable("Santiago_ExitTown", "reload3", false);
			LocatorReloadEnterDisable("Havana_ExitTown", "reload4", false);
			LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload3", false);
			LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload1_back", false);
			LocatorReloadEnterDisable("PuertoPrincipe_ExitTown", "reload2_back", false);
			LocatorReloadEnterDisable("PuertoPrincipe_Port", "reload1_back", false);
			InterfaceStates.DisFastTravel = false;
			DeleteAttribute(Pchar, "questTemp.WhisperTutorial");
			bDisableLandEncounters = false;
			//DoReloadCharacterToLocation(Pchar.HeroParam.Location, Pchar.HeroParam.Group, Pchar.HeroParam.Locator);
			Lai_SetPlayerType(pchar);

			SetQuestHeader("WhisperQuestline");
			AddQuestRecord("WhisperQuestline", "1");
			AddQuestRecord("WhisperQuestline", "2");
			AddQuestUserData("WhisperQuestline", "sWhCapName", GetFullName(characterFromId("wl_Pirate_Cap")));
			//AddQuestRecord("WhisperQuestline", "3");

			SetQuestsCharacters();

			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "", 25);
			for(i=1; i < 5; i++)
			{
				sld = CharacterFromID("Wh_Crew"+sti(i));
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "sea", "none", "", "", "", 20);
			}
		break;
		case "Jack":
			dialog.text = "Правда что ли? Ха-ха! То есть, э... Очень жаль, конечно. Ладно, давай сюда его вещички и проваливай.";
			link.l1 = "Это вряд ли. Мне они ещё понадобятся.";
			link.l1.go = "Jack_1";
		break;
		case "Jack_1":
			dialog.text = "Ты наверное не поняла. Эти шляпа с клинком, как корона со скипетром - символы власти на 'Чёрной Вдове'. Тому, кому они принадлежат и быть капитаном. Я долго терпел, в ожидании своей очереди. Не удавил капитана во сне чтобы это ускорить. Собирался, но не стал.";
			link.l1 = "Если судить по сказанному - ты тот ещё подонок, а доверять тебе власть - безумие.";
			link.l1.go = "Jack_2";
		break;
		case "Jack_2":
			dialog.text = "Ах ты, каналья! Да я тебя...";
			link.l1 = "Попробуй.";
			link.l1.go = "Jack_fight";
		break;
		case "Jack_fight":
			Lai_SetPlayerType(pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
			//LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			LAi_SetImmortal(NPChar, false);
			PChar.quest.WhisperJimTalk.win_condition.l1 = "NPC_Death";
			PChar.quest.WhisperJimTalk.win_condition.l1.character = npchar.id;
			pchar.quest.WhisperJimTalk.function = "WhisperJimTalk";
			DialogExit();
		break;
		case "NF":
			dialog.text = "Будь я инквизитором, тоже непременно захотел бы тебя отжарить. Ха, шутка! Но всё-равно, у них такая внешность не в почёте.";
			link.l1 = "Это я уже поняла.";
			link.l1.go = "NF_1";
		break;
		case "NF_1":
			dialog.text = "Давай знакомиться. Я Девятипалый Билл.";
			link.l1 = "Виспер.";
			link.l1.go = "NF_2";
		break;
		case "NF_2":
			dialog.text = "Чёрт, у тебя уже есть кличка, как у настоящей корсарки! Вот что я тебе посоветую, Виспер. Раз уж ты прячешься от испанцев, тебе неплохо было бы сделать новые документы, чтоб ты могла скрыться в колониях другой страны.";
			link.l1 = "И где я смогу их раздобыть?";
			link.l1.go = "NF_3";
		break;
		case "NF_3":
			dialog.text = "Да прямо в нашем городке, в таверне. Это большое здание у меня за спиной. Поищи за одним из столиков дипломата. Он тебе всё сделает в лучшем виде.";
			link.l1 = "Спасибо за совет, непременно им воспользуюсь.";
			link.l1.go = "NF_exit";
		break;
		case "NF_exit":
			Lai_SetPlayerType(pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.Whisper.BuyDocuments = true;
		break;
		case "NF_2_1":
			dialog.text = "Не знаю как ты, а я прорываюсь к своему кораблю и отчаливаю отсюда.";
			link.l1 = "...";
			link.l1.go = "NF_2_exit";
		break;
		case "NF_2_exit":
			//Lai_SetPlayerType(pchar);
			TakeNItems(npchar, "blade19", 1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_CharacterPlaySound(pchar, "People Fight\Player_Man_Shoot_01.wav");
			DoQuestFunctionDelay("WhisperKillNineFingers", 0.7);
			DialogExit();
			pchar.questTemp.Whisper.GetHat = true;
			DoQuestCheckDelay("TalkSelf_Quest", 2.5);
		break;
		case "Pirateguard":
			dialog.text = RandPhraseSimple("Чего тебе? Проходи мимо.", "Хватит загораживать дорогу, отвали.");
			link.l1 = RandPhraseSimple("Знаешь что? Не гавкай!", "Поумерь свой пыл. Не то быстро охлажу его!");
			NextDiag.CurrentNode = "Pirateguard";
			link.l1.go = "exit";
		break;
		case "IncqGuard_bad":
			dialog.text = "Вот мы и остались одни\nНаверное ты подумала, что на этом все закончилось? Если так, то вынужден тебя огорчить. Видишь ли, пока де Соуза отдыхает или занимается другими делами, я его здесь подменяю. Вопросы я тебе задавать не буду, этим инквизитор занимается. Я лишь сделаю тебя более покладистой к его приходу, чтобы ему больше не пришлось вытягивать из тебя ответы\nДавай, познакомлю тебя с нашими 'игрушками'. Нам недавно привезли 'Колесо', тебе выпадет честь первой испытать его в действии. Пойдём, не стесняйся. И не вздумай пытаться сбежать, здесь полно стражников.";
			link.l1 = "(Молча следовать за ним)";
			link.l1.go = "IncqGuard_bad_go_to_wheel";
		break;
		case "IncqGuard_bad_go_to_wheel":
			DialogExit();
			LAi_ActorGoToLocator(NPChar, "goto", "goto11", "WhisperLine_IncqGuard_bad_speaks", -1);
			LAi_ActorGoToLocator(PChar, "goto", "goto11", "WhisperLine_IncqGuard_bad_speaks", 10);
			Npchar.dialog.currentnode = "IncqGuard_bad_wheel";
			//DoQuestFunctionDelay("WhisperLine_IncqGuard_bad_speaks", 5);
		break;
		case "IncqGuard_bad_wheel":
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("IncqGuard_"+i);
				LAi_SetActorTypeNoGroup(sld);
			}
			dialog.text = "Вот и наша красавица\nЕсли я правильно помню инструкцию, тебя следует сначала привязать к колесу, после чего, медленными движениями вращать рычаг. Шипы внизу безнадежно искалечат и изуродуют твое тело. Вряд ли после такого ты вообще сможешь ходить без чужой помощи\nТак... Ну и куда же подевалась верёвка?";
			link.l1 = "Прости, но я вынуждена отказаться от твоего предложения. Способность ходить мне еще понадобится, когда я буду искать отсюда выход. (Пока он замешкался, ты резким движением выхватываешь его пистолет из кобуры)";
			link.l1.go = "IncqGuard_bad_wheel_kill";
		break;
		case "IncqGuard_bad_wheel_kill":
			DialogExit();
			//RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			npchar.SaveItemsForDead = true;
			GiveItem2Character(pchar, "pistol3");
			EquipCharacterByItem(pchar, "pistol3");
			Lai_SetPlayerType(pchar);
			//AddDialogExitQuest("MainHeroFightModeOn");
			DoQuestFunctionDelay("WhisperLine_WhisperHits", 0.2);
		break;
		case "IncqGuard":
			dialog.text = "Чёрт, сильно же он тебя отделал. Знал бы я какое чудовище этот де Соуза - ни за что не пошёл бы сюда на службу.";
			link.l1 = "Ничего, мне и похуже доставалось.";
			link.l1.go = "IncqGuard_1";
		break;
		case "IncqGuard_1":
			dialog.text = "Мне всё-равно больно на это смотреть. Когда он пытает мужиков я ещё могу вынести, но женщин\nЯ тут подумал, дверь ведь ещё не заперта. Быть может, ты хочешь на свободу? А я мог бы отвернуться в другую сторону.";
			link.l1 = "Это какая-то инквизиторская уловка? Вы меня отпустите, а потом проследите, куда пойду?";
			link.l1.go = "IncqGuard_2";
		break;
		case "IncqGuard_2":
			dialog.text = "Нет никаких уловок. Простое человеческое сострадание. Я даже немного денег тебе дам, чтоб ты не пропала сразу, как выберешься.";
			link.l1 = "Чёрт, ты и правда говоришь это всерьёз. Какой план?";
			link.l1.go = "IncqGuard_3";
		break;
		case "IncqGuard_3":
			dialog.text = "Беги прямо по коридору к выходу. Остальная стража хватится за оружие, но они все только вернулись после обеда, так что будут неповоротливы. Если поторопишься, они тебя и пальцем тронуть не успеют\nКак только выйдешь из инквизиции, ты сможешь смешаться с толпой в городе, так что дальше твой след потеряется. Но всё-равно, не задерживайся в Сантьяго, так как тебя наверняка будут разыскивать\nОтправляйся в поселение буканьеров, Пуэрто-Принсипе. Когда выйдешь за ворота, дважды сверни по дороге влево, затем направо, окажешься прямо у входа. Там за мои деньги ты сможешь немного обустроиться, если ты не солгала де Соузе и тебе правда некуда податься. Место это не самое безопасное, но всё же там тебя не ждёт неминуемая гибель, как в этой клетке.";
			link.l1 = "Даже не знаю, смогу ли я когда-то тебя отблагодарить. Ты настоящий рыцарь! Там, откуда я родом такие люди уже вымерли.";
			link.l1.go = "IncqGuard_4";
			Pchar.BaseNation = SPAIN;
			if (CheckAttribute(npchar,"quest.answer_1"))
			{
				link.l1 = "Ладно, я готова.";
				link.l1.go = "IncqGuard_exit";
			}
		break;
		case "IncqGuard_4":
			dialog.text = "Ты мне льстишь. Ну ладно, ты всё поняла? Можешь начинать, когда будешь готова. Но лучше не медли.";
			npchar.quest.answer_1 = true;
			link.l1 = "Да, сейчас только соберусь с мыслями.";
			link.l1.go = "IncqGuard_exit";
			link.l2 = "Повтори ещё раз пожалуйста, что мне нужно делать.";
			link.l2.go = "IncqGuard_3";
		break;
		case "IncqGuard_exit":
			Lai_SetPlayerType(pchar);
			AddMoneyToCharacter(pchar, 1500);
			InterfaceStates.Buttons.Save.enable = true;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();

			PChar.quest.WhisperEscape.win_condition.l1 = "locator";
			PChar.quest.WhisperEscape.win_condition.l1.location = "Santiago_Incquisitio";
			PChar.quest.WhisperEscape.win_condition.l1.locator_group = "reload";
			PChar.quest.WhisperEscape.win_condition.l1.locator = "reload1_back";
			PChar.quest.WhisperEscape.function = "WhisperEscape";
		break;
		case "ADS":
			dialog.text = "Правда? Говори тогда, кто ты? Такой цвет глаз и волос не каждый день увидишь, знаешь ли. И что за пистоль у тебя изъял "+GetFullName(characterFromId("wl_Pirate_Cap"))+"?";
			link.l1 = "Я... Затрудняюсь ответить.";
			link.l1.go = "ADS_1_lie";

		break;
		case "ADS_1":
			dialog.text = "Из будущего, говоришь? И что же тебе в таком случае понадобилось в нашем времени?";
			link.l1 = "Ничего, перемещение сюда было случайностью. Послушайте, вы должны поговорить с Эрнаном Эстебаном и попросить у него устройство, что было при мне. Я покажу вам, как оно работает и докажу свои слова.";
			link.l1.go = "ADS_1_1";
		break;
		case "ADS_1_lie":
			dialog.text = "В молчанку собираешься со мной играть?";
			pchar.Whisper.DeSouzaHits = 0;
			link.l1 = "...";
			link.l1.go = "ADS_1_2";
		break;
		case "ADS_1_truth":
			dialog.text = "Слушаю. ";
			link.l2 = "Возможно, вам будет трудно в это поверить, но я пришла из будущего. Несколько веков спустя такое оружие будет также распространено, как сейчас шпаги. И моя внешность не будет казаться столь необычной.";
			link.l2.go = "ADS_1";
		break;
		case "ADS_1_1":
			dialog.text = "Так, хватит. Ты держишь меня за идиота? Я никогда не поверю в путешествия во времени. Ты бы мне ещё байку о 'Летучем Голландце' рассказала\nВернемся к сути. Если пистоль не англичан, то чей, голландцев?";
			pchar.Whisper.DeSouzaHits = 2;
			link.l1 = "...";
			link.l1.go = "ADS_1_2";
		break;
		case "ADS_1_2":
			DoQuestFunctionDelay("WhisperLine_DeSouzaHits", 0.5);
			DialogExit();
		break;
		case "ADS_2":
			dialog.text = "Ты мне ещё угрожать смеешь?! Ах ты, мерзавка!";
			pchar.Whisper.DeSouzaHits = 1;
			link.l1 = "...";
			link.l1.go = "ADS_1_2";
		break;
		case "ADS_3":
			dialog.text = "Сама ведь напрашиваешься.";
			pchar.Whisper.DeSouzaHits = 2;
			link.l1 = "...";
			link.l1.go = "ADS_1_2";
		break;
		case "ADS_4_exit":
			LAi_SetActorTypeNoGroup(npchar);
			//LAi_SetActorType(pchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 7);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DoQuestFunctionDelay("WhisperLine_IncqGuard", 8.0);
		break;


		case "PC":
			dialog.text = "Это я у тебя должен спрашивать! Имя есть?";
			link.l1 = "Виспер.";
			link.l1.go = "PC_1";
		break;
		case "PC_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			dialog.text = "Ой, не нравишься ты мне. Вид у тебя уж слишком подозрительный. Ну-ка, ребятки, покажите нашей новой попутчице дорогу в трюм, и хорошенько там свяжите. Потом с ней разберусь.";
			link.l1 = "Сдаваться я не собираюсь!";
			link.l1.go = "PC_fight";
			link.l2 = "Ведите, всё-равно я вас всех не одолею.";
			link.l2.go = "PC_nofight";
		break;
		case "PC_fight":
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetActorType(NPChar);
			LAi_SetCheckMinHP(Pchar, 1, true, "Whisper_PC_CheckHP");
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
		break;
		case "PC_nofight":
			Pchar.model="PGG_Whisper_0_NoHat";
			DeleteAttribute(pchar,"cirassID");
			DoQuestFunctionDelay("WhisperHold", 0.5);
			DialogExit();
		break;
		case "PC_2":
			dialog.text = "Сколько потребуется. На вид эти штучки дорого стоят, наверняка у тебя богатые родители. Предлагаю сходить к ним и потребовать выкуп. Как только я получу деньги - ты свободна. Итак, в какой колонии мы сможем их найти?";
			link.l1 = "Я не из этих мест. У меня здесь нет родных.";
			link.l1.go = "PC_2_1";
		break;
		case "PC_2_1":
			dialog.text = "Ты считаешь, что это вызовет во мне жалость? Или, быть может, за дурака держишь? Тогда ты глубоко заблуждаешься\nЗнаешь, у меня есть один знакомый, который сможет тебя разговорить - Антониу де Соуза. Это глава инквизиции в Сантьяго\nПо долгу службы мне пришлось однажды с ним поработать. Вот что я тебе скажу, тип весьма неприятный, но своего добиваться умеет\nЯ привёл к нему одного неразговорчивого пирата, а на следующий день мы уже знали о местонахождении четырёх зарытых им кладов. Сам бедолага при этом умер, давая показания\nБоюсь даже представить, что де Соуза сделает с тобой, когда увидит. С таким цветом волос, скорее всего - сразу на костёр.";
			link.l1 = "Пугай сколько влезет, я и пострашней истории знаю!";
			link.l1.go = "PC_2_2";
			link.l2 = "Неужели мы не сможем договориться?";
			link.l2.go = "PC_2_3";
		break;
		case "PC_2_2":
			dialog.text = "Я лишь говорю как есть\nЛадно, крепись. Пока мы доплывём, у тебя есть несколько дней чтобы подготовиться к далеко не самой приятной встрече в своей жизни. ";
			link.l1 = "...";
			link.l1.go = "PC_2_exit";
		break;
		case "PC_2_3":
			dialog.text = "Боюсь, что нет. Я предложил тебе вариант, но ты начала увиливать от ответа. Пускай уже де Соуза узнает, можно ли с тебя получить выкуп, или где берутся такие пистоли\nЛадно, крепись. Пока мы доплывем, у тебя есть несколько дней чтобы подготовиться к далеко не самой приятной встрече в твоей жизни. ";
			link.l1 = "...";
			link.l1.go = "PC_2_exit";
			link.l2 = "Постой...";
			link.l2.go = "PC_2_exit";
		break;
		case "PC_2_exit":
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 7);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.Whisper.HoldMonologue = true;
			DoQuestCheckDelay("TalkSelf_Quest", 3.0);

		break;

		case "FB":
			//CharacterPlayAction(npchar, "Shot");
			NextDiag.CurrentNode = NextDiag.TempNode;
			dialog.text = "(Вы сами не пострадали, однако этого нельзя сказать об устройстве в ваших руках. Пуля попадает в квантовый выпрямитель частиц, после чего устройство включается и начинает работать произвольным образом, издавая серии тресков и щелчков)";
			PlayVoice("interface\beeping.wav");
			link.l1 = "Дьявол!";
			link.l1.go = "FB_exit";
		break;
		case "FB_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			dialog.text = "(Вы сами не пострадали, однако этого нельзя сказать об устройстве в ваших руках.Пуля попадает в квантовый выпрямитель частиц, после чего устройство включается и начинает работать произвольным образом, издавая серии тресков и щелчков)";
			link.l1 = "Дьявол!";
			link.l1.go = "exit";
			DoReloadCharacterToLocation("Ship_Deck_Big","goto","goto5");
			PChar.quest.WhisperTeleport.win_condition.l1 = "location";
			PChar.quest.WhisperTeleport.win_condition.l1.location = "Ship_Deck_Big";
			PChar.quest.WhisperTeleport.function = "WhisperTeleport";
		break;
		case "CS":
			dialog.text = "Это тебе не игрушка, девочка. Ты и представить себе не можешь, на что способен этот предмет. Положи его на место, медленно и осторожно.";
			link.l1 = "Ты про квантовый выпрямитель частиц?";
			link.l1.go = "CS_1";
		break;
		case "CS_1":
			dialog.text = "Ты хоть сама понимаешь, что только что сказала?";
			link.l1 = "Не очень...";
			link.l1.go = "CS_1_1";
			link.l2 = "Конечно! Я не тупая.";
			link.l2.go = "CS_1_2";
		break;
		case "CS_1_1":
			dialog.text = "Хоть по самому названию может быть не ясно, но это устройство позволяет перемещаться в пространстве и времени. Однако, любое применение может привести к тому, что вся временная последовательность полностью перепишется. Ни я, ни ты, можем никогда не родиться. Так что лучше положи обратно на место, от греха подальше.";
			link.l1 = "Послушай, мужик, мне некогда выяснять с тобой отношения. Заказчик ждёт.";
			link.l1.go = "CS_2";
		break;
		case "CS_1_2":
			dialog.text = "Ну тогда ты должна понимать, почему его не стоит трогать.";
			link.l1 = "Послушай, мужик, мне некогда выяснять с тобой отношения. Заказчик ждёт.";
			link.l1.go = "CS_2";
		break;
		case "CS_2":
			dialog.text = "Заказчик? Я знаю только одного возможного заказчика, которому известно об этом устройстве\nЗначит ты - корпоратская подстилка? Делаешь всё, что тебе прикажут?! Я бы тебе врезал, да только меня с детства учили, что женщин бить нельзя...";
			link.l1 = "Попрошу без оскорблений. Я - свободная наёмница. Берусь только за ту работу, которую сама выбираю.";
			link.l1.go = "CS_2_1";
		break;
		case "CS_2_1":
			dialog.text = "Это ты так считаешь. На самом деле ты, да и все мы - уже давно у них на крючке. Небось кредитов нахваталась, а они предложили их закрыть? Можешь не отвечать. Я сам работал на Omnitech и видел всю их гнилую систему изнутри.";
			link.l1 = "Хм. В заказе не сказали, что 'безумный учёный' - их бывший сотрудник.";
			link.l1.go = "CS_3";
		break;
		case "CS_3":
			dialog.text = "Ну и прозвище! Да мои мысли яснее, чем у тебя! Это корпораты, что заставили меня разработать штуку в твоих руках - безумцы! Поэтому я и решил спрятать её от них.";
			link.l1 = "То есть ты украл это устройство у Omnitech?";
			link.l1.go = "CS_3_1";
		break;
		case "CS_3_1":
			dialog.text = "Боюсь, слово 'украл' - неприменимо в данной ситуации. На все сто процентов, это - моя разработка. Но да, по их рабскому закону любая интеллектуальная собственность разработанная сотрудником корпорации на территории корпорации - принадлежит корпорации. Но вором меня всё же назвать можно. Когда я забрал машину времени, заодно перепрограммировал под себя десяток корпоратских ботов, которых ты могла встретить по пути сюда.";
			link.l1 = "Для чего корпорации могла понадобиться машина времени?";
			link.l1.go = "CS_4";
		break;
		case "CS_4":
			dialog.text = "А вот это ты уже правильные вопросы начинаешь задавать. Чтоб вернуться в прошлое и поработить всё человечество ещё быстрее! Имея в запасе такой козырь, как всё время мира, они без проблем станут монополистами во всём мыслимом и немыслимом, а нас ждёт будущее даже более печальное чем то, что происходит в мире сейчас.";
			LAi_SetImmortal(npchar, false);
			link.l1 = "Я правда тебя понимаю. Но лично мне всё-равно, что случится с остальным человечеством. И я получу плату за этот заказ, не смотря на то, придётся мне переступить через твой труп, или нет!";
			link.l1.go = "CS_bad";
			link.l2 = "Если эта штуковина и правда делает то, что ты говоришь, то пожалуй отдавать её корпоратам не стоит. Я найду ей гораздо лучшее применение в своих руках. ";
			link.l2.go = "CS_neutral";
			link.l3 = "Чёрт, а ведь ты прав... Так и быть, забирай и уходи отсюда. Я скажу заказчику, что ты сбежал.";
			link.l3.go = "CS_good";
		break;
		case "CS_bad":
			dialog.text = "Какая же ты всё-таки сволочь.";
			ChangeCharacterReputation(pchar, -100);
			LAi_tmpl_afraid_SetAfraidCharacter(npchar,pchar,false);
			link.l1 = "А ну, заткнулся!";
			Link.l1.go = "ExitSC";
		break;
		case "CS_neutral":
			dialog.text = "Жадность... Понимаю это чувство. Что же, я безоружен и не в силах тебя остановить.";
			link.l1 = "В этом ты абсолютно прав. Прощай.";
			link.l1.go = "ExitSC";
		break;
		case "CS_good":
			dialog.text = "А ведь ты на самом деле вовсе не бездушная тварь, как мне поначалу казалось. Но устройство лучше оставь у себя. Если меня смогли выследить даже в этой богом забытой дыре, то скорее всего на меня каким-то образом повесили устройство слежения. Сейчас уже слишком поздно начинать его искать, так что я вряд ли сумею скрыться. У тебя, с другой стороны, ещё есть шанс. ";
			ChangeCharacterReputation(pchar, +100);
			link.l1 = "Это большее, чем то, на что я была готова подписаться. Но отказать не могу, слишком многое на кону. Обещаю, корпораты не получат это устройство.";
			link.l1.go = "CS_good_1";
		break;
		case "CS_good_1":
			dialog.text = "Только будь оторожна на выходе отсюда. Мои датчики показывают, что ты уничтожила не всех ботов. Я не смогу отключить их удалённо, так что тебе придётся разбираться с ними самостоятельно.";
			link.l1 = "Ага, прощай.";
			link.l1.go = "ExitSC";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "ExitSC":
			LAi_LocationFightDisable(locLoad, true);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetActorTypeNoGroup(npchar);
			DialogExit();
		break;

		case "exit_fight":
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			//LAi_group_MoveCharacter(NPChar, LAI_GROUP_MONSTERS);
			//LAi_SetImmortal(npchar, false);
			//LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			DialogExit();
		break;

		case "OrderHunter":
			chrDisableReloadToLocation = false;
			//Lai_SetPlayerType(pchar);
			if(!CheckAttribute(pchar,"OrderHunter"))
			{
				SetQuestHeader("TheLastMass");
				if (startherotype == 2)
				{
					sTemp = "Ты же не думала, что сможешь убить главу инквизиции, и тебе это так просто сойдёт с рук? ";
					AddQuestRecord("TheLastMass", "1");
				}
				else
				{
					sTemp = "До инквизиции дошли сведения о твоих злодеяниях! ";
					AddQuestRecord("TheLastMass", "1_1");
				}
				pchar.OrderHunter = "1";
				Link.l1 = "Инквизитор? Советую тебе вернуться обратно в свою нору под церковью Сантьяго. Ну же, беги, пока я добр"+GetSexPhrase("ый","ая")+"!";
				Link.l1.go = "OrderHunterMeeting";
				if (WhisperIsHere())
				{
					Link.l1 = "...";
					Link.l1.go = "OrderHunterMeetingWhisperIsHere";
				}
			}
			else
			{
				sTemp = " ";

				Link.l1 = "Опять? Ладно, приготовься к вознесению на небеса.";
				Link.l1.go = "OrderHunterBattle";

				if(sti(PChar.OrderHunter) == 2) {AddQuestRecord("TheLastMass", "2");}

				if(sti(PChar.OrderHunter) == 3)
				{
					Link.l1 = "Знаешь, а ведь ты уже не первый инквизитор, что охотился на меня. Думаю, ты догадываешься, что случилось с остальными. Скажи, где находится ваша база, и я позволю тебе уйти живым.";
					Link.l1.go = "OrderHunterNegotiate";
				}
				if(sti(PChar.OrderHunter) > 3)
				{
					Link.l2 = "Никак вы, б***ь не научитесь! Опять кому-то умереть захотелось?";
					Link.l2.go = "OrderHunterCheck";
				}
			}
			dialog.text = GetFullName(PChar) + "! "+ sTemp + "Я выслеживал тебя долгое время, и вот, наконец, ты получишь заслуженное наказание.";
			if (WhisperIsHere())
			{
				dialog.text = dialog.text + "\nС тобой эта ведьма Виспер? Мои братья будут рады, когда узнают, что я избавил церковь сразу от двух врагов!"
			}
		break;

		case "OrderHunterNegotiateWhisperIsHere":
			pchar.PrevNpc = npchar.id;
			SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
			StartInstantDialogNoType(pchar.WhisperPGG, "OrderHunterNegotiateWhisperIsHere_1", "Quest\WhisperLine\Whisper.c");
		break;

		case "OrderHunterNegotiateWhisperIsHere_1":
			LAi_tmpl_SetFollow(npchar, GetMainCharacter(), -1.0);
			W_RestoreOfficerDialog();
			dialog.text = "А вот теперь мне стало интересно. Нам нужно обязательно сходить на этот Риф Скелета.";
            Link.l1 = "Что ж, я своё слово держу, можешь идти.";
			Link.l1.go = "OrderHunterPeace";
			Link.l2 = "Благодарю за информацию. Не принимай близко к сердцу, но я не могу позволить тебе уйти живым и предупредить о моём визите.";
			Link.l2.go = "OrderHunterBattle";
		break;

		case "OrderHunterNegotiate":
			dialog.text = "Хм... Так и быть. В своих силах я не уверен, но дон Хулио Иглесиас наверняка одолеет тебя. Наш Капитул расположен на Рифе Скелета, в бухте Проклятых. Это в паре дней пути на восток от Каймана.";

            Link.l1 = "Не слишком ли это осквернённое место для 'благочестивых' служителей церкви?";
			Link.l1.go = "OrderHunterNegotiate_1";
		break;

		case "OrderHunterNegotiate_1":
			dialog.text = "Дурная слава этого рифа обеспечивает защиту надёжней любых стен и орудий. Все обходят его стороной.";
			if (WhisperIsHere())
			{
				Link.l1.go = "OrderHunterNegotiateWhisperIsHere";
			}
			else
			{
				Link.l1 = "Что ж, я своё слово держу, можешь идти.";
				Link.l1.go = "OrderHunterPeace";
				Link.l2 = "Благодарю за информацию. Не принимай близко к сердцу, но я не могу позволить тебе уйти живым и предупредить о моём визите.";
				Link.l2.go = "OrderHunterBattle";
			}

			AddQuestRecord("TheLastMass", "3");
			CaptureCapitol_SeaBattle();
			pchar.quest.CaptureCapitol_SeaBattleStarted.win_condition.l1          = "location";
			pchar.quest.CaptureCapitol_SeaBattleStarted.win_condition.l1.location = "Reefs";
			pchar.quest.CaptureCapitol_SeaBattleStarted.function             = "CaptureCapitol_SeaBattleStarted";
		break;

		case "OrderHunterMeetingWhisperIsHere":
			pchar.PrevNpc = npchar.id;
			SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
			StartInstantDialogNoType(pchar.WhisperPGG, "OrderHunterMeetingWhisperIsHere_1", "Quest\WhisperLine\Whisper.c");
		break;

		case "OrderHunterMeetingWhisperIsHere_1":
			LAi_tmpl_SetFollow(npchar, GetMainCharacter(), -1.0);
			W_RestoreOfficerDialog();
			dialog.text = "Снова инквизиция? Меня уже тошнит от них\nЕсли тебя не затруднит, "+pchar.name+", сделай для меня одолжение и убей его.";
            Link.l1 = "Может, дадим ему шанс одуматься? Инквизитор, советую тебе вернуться обратно в свою нору под церковью Сантьяго. Ну же, беги, пока я добр"+GetSexPhrase("ый","ая")+"!";
			Link.l1.go = "OrderHunterMeetingWhisperIsHere_2";
		break;

		case "OrderHunterMeetingWhisperIsHere_2":
			StartInstantDialog(pchar.PrevNpc, "OrderHunterMeeting", "Quest\WhisperLine\Whisper.c");
		break;

		case "OrderHunterMeeting":
			dialog.text = "Сантьяго больше не является нашей главной резиденцией на Карибах. Сюда из Европы прибыл дон Хулио Иглесиас и начал строительство нового Капитула. А в связи с последними событиями, наш орден получил в распоряжение практически неограниченное финансирование и собственную военную эскадру.";
            Link.l1 = "Надо же! Как интересно... А где находится ваша новая столица?";
			Link.l1.go = "OrderHunterMeeting_1";
		break;

		case "OrderHunterMeeting_1":
			dialog.text = "В тайном месте и под надёжной охраной.";
            Link.l1 = "Ожидаемый ответ. Раз уж ты всё еще здесь, думаю тебе не терпится отправиться на небеса.";
			Link.l1.go = "OrderHunterBattle";
		break;

		case "OrderHunterCheck":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > rand(150))
            {
                dialog.text = "Пожалуй я не готов сражаться с тобой сегодня. Господь даровал тебе время покаяться в своих грехах.";
                Link.l1 = "Ну и проваливай.";
                Link.l1.go = "OrderHunterPeace";
				Link.l2 = "Надеюсь, ты уже покаялся в своих, ведь у тебя времени не осталось.";
				Link.l2.go = "OrderHunterBattle";
                AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 100);
            }
            else
            {
                dialog.text = "Тебе не запугать меня своим греховным словоблудием!";
			    Link.l1 = "Тогда я заткну тебя своим клинком.";
			    Link.l1.go = "OrderHunterBattle";
			    AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 50);
            }
		break;

		case "OrderHunterPeace":
            PChar.OrderHunter = sti(PChar.OrderHunter)+1;
			AddDialogExitQuest("GoAway_Hunters_Land");
            DialogExit();
        break;

		case "OrderHunterBattle":
			PChar.OrderHunter = sti(PChar.OrderHunter)+1;
            AddDialogExitQuest("Battle_Hunters_Land");
            DialogExit();
        break;

		case "OrderLeader":
			LAi_SetActorType(npchar);
			dialog.text = "Вижу тебе удалось загубить жизни многих моих братьев. Но как сказал Господь: Мёртвые оживут, тела их снова восстанут к жизни, восстанут они и восторжествуют\nИ вы, пребывающие во прахе, - пробудитесь и ликуйте!";

            Link.l1 = "Что ещё за чертовщина?";
			Link.l1.go = "OrderLeader_exit";
		break;

		case "OrderLeader_exit":
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
			DoQuestFunctionDelay("CaptureCapitol_ShoreBattleRaiseUndead", 3.5);
			DialogExit();
		break;

		case "OrderLeader_1":
			dialog.text = "Меня загнали в угол, подобно дикому зверю. Но я не стану уподобляться ему и впадать в страх! Нет! Я не отчаиваюсь, если мне суждено отправиться сегодня в Царствие Небесное - так тому и быть. Но я всё же надеюсь, что Господь наделит меня силой, чтобы я мог сразить врага его.";

			if (WhisperIsHere())
			{
				Link.l1.go = "OrderLeaderWhisperIsHere";
			}
			else
			{
				Link.l1 = "Что это было там, наверху? Подозреваю, что после связей с нечистью это скорее ты враг Богу, а не я, и дорога тебе прямиком в Ад.";
				Link.l1.go = "OrderLeader_2";
			}
		break;

		case "OrderLeaderWhisperIsHere":
			pchar.PrevNpc = npchar.id;
			SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
			StartInstantDialogNoType(pchar.WhisperPGG, "OrderLeaderWhisperIsHere_1", "Quest\WhisperLine\Whisper.c");
		break;

		case "OrderLeaderWhisperIsHere_1":
			LAi_tmpl_SetFollow(npchar, GetMainCharacter(), -1.0);
			W_RestoreOfficerDialog();
			dialog.text = "Так за всем этим стоял... безумный фанатик? Признаюсь честно - я немного разочарована.";
			Link.l1.go = "OrderLeaderWhisperIsHere_2";
		break;

		case "OrderLeaderWhisperIsHere_2":
			SaveOldDialog(CharacterFromID(pchar.WhisperPGG));
			StartInstantDialogNoType(pchar.PrevNpc, "OrderLeaderWhisperIsHere_3", "Quest\WhisperLine\Whisper.c");
		break;

		case "OrderLeaderWhisperIsHere_3":
			dialog.text = "Это ведь ты, Виспер? Я многое слышал о злоключениях, что ты устроила моему брату, Антониу де Соузе. Думаю, он был бы рад узнать, что я наконец отправил тебя в ад, ведьма!";
			Link.l1 = "Что это было там, наверху? Подозреваю, что после связей с нечистью это скорее ты враг Богу, а не мы, и дорога тебе прямиком в Ад.";
			Link.l1.go = "OrderLeader_2";
		break;

		case "OrderLeader_2":
			dialog.text = "Посмотри на икону у меня за спиной. Георгий Победоносный сражается со змеем. Она прекрасна, не правда ли? Я много смотрел на неё и думал, а что если не убивать змея, а приручить его? Подобно тому, как человек приручает агнца, и других тварей. И вот, однажды я нашёл способ\nКогда-то эти люди были слугами тьмы, но я сумел обуздать силы этого проклятого острова и направить их во благо. Я сделал их орудиями в руках Господа!";
            Link.l1 = "Во благо своих извращённых желаний? Не представляю как ты этого добился и знать не хочу. В этих гниющих телах были души людей! Вместо того, чтобы освободить их, ты оставил их мучиться и подчиняться твоим капризам. Вряд ли Богу такое понравится. Но теперь всё кончено, они обрели покой.";
			Link.l1.go = "OrderLeader_3";
		break;

		case "OrderLeader_3":
			dialog.text = "Тебе не понять, это всё затевалось для высшего блага. Когда мои старания дадут плоды, Господь простит меня. А то, что стражи грота мертвы, не беда, ты со своими людьми займёшь их место!";

            Link.l1 = "Это вряд ли.";
			Link.l1.go = "OrderLeader_fight";
			if (startherotype == 2)
			{
				Link.l1 = "Это случайно не мой шотган у тебя на поясе?";
				Link.l1.go = "OrderLeader_4";
			}
		break;

		case "OrderLeader_4":
			dialog.text = "А, ты заметила. Я нашел это оружие среди документов в кабинете де Соузы, когда занял его пост. Говоришь, эта вещь твоя? Должен признаться, я в восхищении от этого механизма, грешники толпами падают от каждого выстрела. Думаю, ты и сама это знаешь. А скоро даже испытаешь на себе.";

            Link.l1 = "Ещё один повод скорее тебя убить!";
			Link.l1.go = "OrderLeader_fight";
		break;

		case "OrderLeader_fight":
			AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
			CaptureCapitol_OnLeaderDeath();
			LAi_LocationFightDisable(locLoad, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "CaptureCapitol");
			for (int j=1; j<=6; j++)
			{
				sld = CharacterFromID("MaltGuard_"+j);
				LAi_group_MoveCharacter(sld, "CaptureCapitol");
				ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto5");
			}

			LAi_group_SetHearRadius("CaptureCapitol", 100.0);
			LAi_group_FightGroupsEx("CaptureCapitol", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
		break;

		case "CapitolCaptured":
			chrDisableReloadToLocation = false;
			pchar.quest.CaptureCapitol_Decision.win_condition.l1          = "location";
			pchar.quest.CaptureCapitol_Decision.win_condition.l1.location = "DeckWithReefs";
			pchar.quest.CaptureCapitol_Decision.function             = "CaptureCapitol_Decision";

			dialog.text = "Вот это побоище, в жизни не видел столько трупов! Здорово мы их уделали, а, капитан?";
            Link.l1 = "Мы? Что-то не припомню, чтобы выдел"+GetSexPhrase("","а")+" тебя среди сражавшихся.";
			Link.l1.go = "CapitolCaptured_1";
		break;
		case "CapitolCaptured_1":
			dialog.text = "Ну как же, я оборонял тылы, на случай, если нас попытаются окружить. Не сердитесь, капитан\nВот что, я знаю, как вас обрадовать! Пока я, кхм... оборонял другие помещения, я успел немного их осмотреть. Здесь целый склад вооружения разных видов, тонны припасов, а самое интересное - я нашел библиотеку, наполненную книгами на военную тематику. Похоже, инквизиция собиралась обучить здесь собственную армию.";

            Link.l1 = "Интересно, и что со всем этим можно сделать? Продать кому-то?";
			Link.l1.go = "CapitolCaptured_2";
		break;
		case "CapitolCaptured_2":
			dialog.text = "Можно продать, а можно... быть может это глупость, но я думаю, что мы могли бы воспользоваться этим местом для тренировки и содержания собственной армии? Ну, может не целой армии, но вы могли бы оставлять здесь своих офицеров, чтобы они набирались опыта.";

            Link.l1 = "Ты прав, это глупость. Продадим всё и дело с концом.";
			Link.l1.go = "CapitolCaptured_3";
			Link.l2 = "Можно попробовать. Пусть у нас будет собственная база, на всякий случай.";
			Link.l2.go = "CapitolCaptured_4";
		break;
		case "CapitolCaptured_3":
			dialog.text = "Ладно. Тогда я быстро сделаю список всего, что здесь есть, а вы поищите покупателя.";

            Link.l1 = "Думаю, ростовщики будут только рады получить кучу этого хлама.";
			Link.l1.go = "CapitolCaptured_sell";
			Link.l2 = "Хотя... давай всё же оставим это место себе.";
			Link.l2.go = "CapitolCaptured_4";
		break
		case "CapitolCaptured_4":
			dialog.text = "Отличная мысль, капитан!";

            Link.l1 = "Сиди тут и оставайся за главного. Несколько человек с собой возьми. Будешь штабной крысой, всё равно в бою от тебя толку никакого.";
			Link.l1.go = "CapitolCaptured_keep";
		break;

		case "CapitolCaptured_keep":
			dialog.text = "Спасибо, капитан! Я вас не подведу.";
            Link.l1 = "Увидим.";
			Link.l1.go = "exit";
		break;

		case "CapitolCaptured_sell":
			pchar.SellCapitol = true;
			DialogExit();
			if (CheckAttribute(pchar, "WhisperChSpokeToUsurer"))
			{
				AddQuestRecord("WhisperChinamanRelic", "4");
			}
		break;

		case "Beatrice":
			dialog.text = "Нечасто увидишь тут девушек. Вы тоже собираетесь устроиться офицером на какое-нибудь судно? Я бы не советовала пытать удачу здесь, местным пиратам от нас нужно только одно, и это вовсе не знание морского дела.";
            Link.l1 = "Буду иметь в виду.";
			Link.l1.go = "exit";
			npchar.MetWhisper = true;
		break;

		case "Hugo_Lesopilka":
			dialog.text = "Налей-ка мне ещё, девочка.";
            Link.l1 = "Я тебе не официантка!";
			Link.l1.go = "exit";
		break;

		//Реакции
		case "WhisperIsHere_exit":
			DialogExit();
			W_RestoreOfficerDialog();
			LAi_tmpl_SetFollow(npchar, GetMainCharacter(), -1.0);
		break;

		case "BS_WhisperIsHere":
			dialog.text = "Снова придётся воевать с Испанией? Что ж, мне не привыкать.";
			Link.l1.go = "WhisperIsHere_exit";
		break;

		case "BS_1_WhisperIsHere":
			dialog.text = "Пташка? Ты о Максин?";
			Link.l1 = "Да. Надеюсь, она ещё в Порт Рояле.";
			Link.l1.go = "WhisperIsHere_exit";
		break;

		case "BS_2_WhisperIsHere":
			dialog.text = "Похоже, от 'Рейнджера' мало что осталось...";
			Link.l1 = "Пойдём в Форт Оранж. Быть может, местные пропойцы видели, что здесь произошло.";
			Link.l1.go = "WhisperIsHere_exit";
		break;

		case "BS_3_WhisperIsHere":
			dialog.text = "'Держи друзей близко, а врагов - еще ближе.' Мне нравится эта Гатри!";
			Link.l1.go = "WhisperIsHere_exit";
		break;

		case "BS_4_WhisperIsHere":
			dialog.text = "По мне, так Энн поступила правильно. Свидетели в нашем деле ни к чему.";
			Link.l1 = "Пожалуй, ты права.";
			Link.l1.go = "WhisperIsHere_exit";
		break;

		case "BS_5_WhisperIsHere":
			dialog.text = "У меня плохое предчувствие. Будь начеку.";
			Link.l1 = "Ты о чём? Дело сделано, мы наконец можем расслабиться.";
			Link.l1.go = "BS_5_WhisperIsHere_1";
		break;

		case "BS_5_WhisperIsHere_1":
			dialog.text = "Расслабиться, когда на кону сто пятьдесят миллионов? В такие моменты тебе нужно быть наготове как никогда прежде!";
			Link.l1 = "Не нервничай ты так. Ничего не случится.";
			Link.l1.go = "WhisperIsHere_exit";
		break;

		case "BS_6_WhisperIsHere_1":
			dialog.text = "Ох, как же мне плохо\nНе хочу тебя попрекать, но ведь я же говорила быть осторожней. Чёрт, я думала ты знаешь, что делаешь, и тоже выпила эту отраву.";
			Link.l1 = "Прости, это было немного неожиданно, даже для меня. Флинт отравил нас? Как остальные?";
			Link.l1.go = "BS_6_WhisperIsHere_2";
		break;

		case "BS_6_WhisperIsHere_2":
			dialog.text = "Я знаю не больше твоего, сама очнулась полчаса назад.";
			Link.l1 = "Ладно, давай спускаться вниз. Может в таверне кто-то что слышал.";
			Link.l1.go = "BS_6_WhisperIsHere_3";
		break;

		case "BS_6_WhisperIsHere_3":
			dialog.text = "Только не спеши, у меня голова всё еще кружится.";
			Link.l1.go = "WhisperIsHere_exit";
		break;

		case "BS_7_WhisperIsHere":
			dialog.text = "Да уж, знатно вас кинул этот Флинт.";
			Link.l1 = "Он кинул всех нас. Тебя, как моего партнёра, в том числе.";
			Link.l1.go = "BS_7_WhisperIsHere_1";
		break;

		case "BS_7_WhisperIsHere_1":
			dialog.text = "Ты прав"+ GetSexPhrase("","а") +", и мне не терпится начистить ему рожу.";
			Link.l1 = "Мне тоже, но только после того, как он ответит зачем он это сделал.";
			Link.l1.go = "WhisperIsHere_exit";
		break;

		case "BS_8_WhisperIsHere":
			dialog.text = "Не высовывайтесь? А не боишься, что нас там перебьют, пока Вейн будет отсиживаться?";
			Link.l1 = "Мы с тобой столькое пережили. Неужели ты испугалась какой-то жалкой засады?";
			Link.l1.go = "BS_8_WhisperIsHere_1";
		break;

		case "BS_8_WhisperIsHere_1":
			dialog.text = "Твоя правда, тогда веди.";
			Link.l1.go = "WhisperIsHere_exit";
		break;

		case "BS_9_WhisperIsHere":
			dialog.text = "Давай лучше не будем её злить. Не хватало нам нажить ещё одного врага...";
			Link.l1.go = "BS_9_WhisperIsHere_1";
		break;

		case "BS_9_WhisperIsHere_1":
			DialogExit();
			W_RestoreOfficerDialog();
			LAi_tmpl_SetFollow(npchar, GetMainCharacter(), -1.0);
			StartInstantDialogNoType("Pirates_trader", "BS_NPVK_6_1", "Quest\BlackSails\NePluyjVKolodec.c");
		break;

		case "BS_10_WhisperIsHere":
			dialog.text = "Хотя... Наверное нам проще было бы её убить.";
			Link.l1.go = "BS_10_WhisperIsHere_1";
		break;

		case "BS_10_WhisperIsHere_1":
			DialogExit();
			W_RestoreOfficerDialog();
			LAi_tmpl_SetFollow(npchar, GetMainCharacter(), -1.0);
			StartInstantDialogNoType("Pirates_trader", "BS_NPVK_7_1", "Quest\BlackSails\NePluyjVKolodec.c");
		break;

		case "BS_11_WhisperIsHere":
			dialog.text = "Эта бесцельная беготня меня изрядно утомила.";
			Link.l1 = "Меня тоже. Но я чувствую, что Сильвер где-то рядом. Давай ещё проверим тюрьму.";
			Link.l1.go = "WhisperIsHere_exit";
		break;

		case "BS_12_WhisperIsHere":
			dialog.text = "Вот это драка! Я даже немного вспотела.";
			Link.l1.go = "WhisperIsHere_exit";
		break;

		case "BS_13_WhisperIsHere":
			dialog.text = "Что будешь делать со своей долей?";
			Link.l1 = "Не знаю. Думаю завязать с пиратством. Может колонию отстрою, или две. А ты?";
			Link.l1.go = "BS_13_WhisperIsHere_1";
		break;

		case "BS_13_WhisperIsHere_1":
			dialog.text = "Я хочу вернуться к себе на родину. Быть может, деньги помогут с этим.";
			Link.l1 = "Разве это так уж дорого? Садись пассажиром на любой попутный корабль, и вперед!";
			Link.l1.go = "BS_13_WhisperIsHere_2";
		break;

		case "BS_13_WhisperIsHere_2":
			dialog.text = "Моя родина находится очень далеко. Боюсь, корабли туда не ходят.";
			Link.l1 = "Опять ты говоришь загадками. Ладно, пойдём уже. Думаю, Сильвер закончил.";
			Link.l1.go = "BS_13_WhisperIsHere_3";
		break;

		case "BS_13_WhisperIsHere_3":
			DialogExit();
			W_RestoreOfficerDialog();
			LAi_SetWarriorTypeNoGroup(npchar);
			LAi_SetPlayerType(pchar);
			LAi_tmpl_SetFollow(npchar, GetMainCharacter(), -1.0);
			ChangeCharacterAddressGroup(npchar, "Pirates_tavern", "goto", "goto2");
			BSHangover_Cutscene_2("");
		break;

		case "BS_14_WhisperIsHere_1":
			dialog.text = "Эх... Похоже, нашим с тобой мечтам не суждено будет сбыться.";
			Link.l1 = "Похоже на то. Но по крайней мере, ты пока не бросишь меня ради своей родины. Я к тебе уже привязал"+ GetSexPhrase("ся","ась") +", знаешь ли.";
			Link.l1.go = "BS_14_WhisperIsHere_2";
		break;

		case "BS_14_WhisperIsHere_2":
			dialog.text = "Ох, не заставляй меня краснеть.";
			Link.l1.go = "WhisperIsHere_exit";
		break;

		case "BS_15_WhisperIsHere":
			dialog.text = "Долго он ещё собирается бегать?";
			Link.l1 = "Пока не приведёт нас к своему кораблю, наверное.";
			Link.l1.go = "WhisperIsHere_exit";
		break;

		case "BS_16_WhisperIsHere":
			dialog.text = "А вот и корабль. Похоже, что бы был"+ GetSexPhrase("","а") +" прав"+ GetSexPhrase("","а") +".";
			Link.l1 = "Я всегда прав"+ GetSexPhrase("","а") +".";
			Link.l1.go = "BS_16_WhisperIsHere_1";
		break;

		case "BS_16_WhisperIsHere_1":
			dialog.text = "С этим я бы поспорила, но ладно.";
			Link.l1.go = "WhisperIsHere_exit";
		break;

		case "BS_17_WhisperIsHere":
			dialog.text = "Смотрите, к нам гости!";
			Link.l1.go = "BS_17_WhisperIsHere_1";
		break;

		case "BS_17_WhisperIsHere_1":
			DialogExit();
			W_RestoreOfficerDialog();
			LAi_tmpl_SetFollow(npchar, GetMainCharacter(), -1.0);
			StartInstantDialogNoType("Flint", "BS_PN_8_1", "Quest\BlackSails\Pogonya_Nachalas.c");
		break;

		case "BS_18_WhisperIsHere":
			dialog.text = "Похоже, что нам досталась самая 'грязная' работа.";
			Link.l1 = "Да ладно тебе.";
			Link.l1.go = "WhisperIsHere_exit";
		break;

		case "BS_19_WhisperIsHere":
			dialog.text = "Давай уже выйдем на свежий воздух. Хватит с меня подземелий на сегодня.";
			Link.l1 = "Да, пойдём.";
			Link.l1.go = "WhisperIsHere_exit";
		break;

		case "BS_20_WhisperIsHere":
			dialog.text = "Что-то мне нехорошо...";
			Link.l1.go = "BS_20_WhisperIsHere_1";
		break;

		case "BS_20_WhisperIsHere_1":
			DialogExit();
			W_RestoreOfficerDialog();
			LAi_tmpl_SetFollow(npchar, GetMainCharacter(), -1.0);
			SetCharacterTask_Dead(npchar);
			DoQuestFunctionDelay("BSUrka_PoisonOfficers", 1);
			DoQuestFunctionDelay("BSUrka_PoisonSelf", 3.0);
			DoQuestFunctionDelay("BSUrka_Poison_Flint", 6.0);
		break;

		// <- Реакции
	}
}
