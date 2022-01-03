void ProcessDialogEvent()
{
	ref locLoad = &locations[reload_location_index];
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;
	int i;
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
			NextDiag.TempNode = "First time";
		break;

		case "DH_Villemstad_merc":
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "ContraInterruptWaiting");
			dialog.Text = "Я думаю, время терять не стоит.";
			Link.l1 = "Я аналогичного мнения.";
			Link.l1.go = "DH_Villemstad_merc_exit_to_bank";
		break;

		case "DH_Villemstad_merc_exit_to_bank":
			DialogExit();
			sld = CharacterFromID("Villemstad_usurer");
			//LAi_ActorDialog(sld, pchar, "", -1.0, 0);
			sld.dialog.filename = "Quest\WhisperLine\DarkHuman.c";
			sld.dialog.currentnode = "DH_Villemstad_usurer";

			sld = CharacterFromID("Villemstad_shipyarder");
			//LAi_ActorDialog(sld, pchar, "", -1.0, 0);
			sld.dialog.filename = "Quest\WhisperLine\DarkHuman.c";
			sld.dialog.currentnode = "DH_Villemstad_shipyarder"

			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;

		case "DH_Villemstad_shipyarder":
			dialog.Text = "Здравствуйте, майн хер.";
			Link.l1 = "Здравствуйте. Не буду юлить - меня интересуют корабли, и по возможности подешевле.";
			Link.l1.go = "DH_Villemstad_shipyarder_1";
		break;
		case "DH_Villemstad_shipyarder_1":
			dialog.Text = "Приятно видеть человека пусть и с небольшой мошной, но знающего чего он хочет. У меня есть для вас отличное предложение.";
			Link.l1 = "И какое же?";
			Link.l1.go = "DH_Villemstad_shipyarder_2";
		break;
		case "DH_Villemstad_shipyarder_2":
			dialog.Text = "Джонка, императрица. Такие иногда встречаются в наших водах. Удивительно, но именно мои соотечественники умудрились перегнать целую группу таких кораблей в карибское море с дальнего востока.";
			Link.l1 = "Бывают в жизни чудеса, но в чем подвох?";
			Link.l1.go = "DH_Villemstad_shipyarder_3";
		break;
		case "DH_Villemstad_shipyarder_3":
			dialog.Text = "Видите ли, это конфискат, бывшего владельца поймали на... как бы сказать, нечестных делишках. И он с перепугу решил, что палить по патрульному судну из пушек - это хорошая идея. Понятное дело воинственность ему быстро поубавили. Через совершенно непродолжительное время ему помог станцевать зажигательный танец пеньковый галстук, зрелище было интересное. Но не суть.";
			Link.l1 = "Да, вернемся к делу.";
			Link.l1.go = "DH_Villemstad_shipyarder_4";
		break;
		case "DH_Villemstad_shipyarder_4":
			dialog.Text = "Так вот, воинственность ему поубавили пушками, что оставило определенные следы и на его джонке. К тому же меня в добровольно принудительном порядке и против всяких правил заставили ее выкупить. И висит она на мне сейчас как мертвый груз. ";
			Link.l1 = "Состояние?";
			Link.l1.go = "DH_Villemstad_shipyarder_5";
		break;
		case "DH_Villemstad_shipyarder_5":
			dialog.Text = "Сразу скажу - не лучшее, но ниже ватерлинии я все дыры залатал. Так что не утонет - не бойтесь. ";
			Link.l1 = "Цена вопроса?";
			Link.l1.go = "DH_Villemstad_shipyarder_6";
		break;
		case "DH_Villemstad_shipyarder_6":
			dialog.Text = "25 тысяч и она ваша. Честно скажу, желающих выкупить ее, у меня нет, так что несколько недель, я смогу и потерпеть.";
			NextDiag.TempNode = "DH_Villemstad_shipyarder_wait_money";
			Link.l1 = "Что ж, возьму, как только появятся деньги.";
			Link.l1.go = "exit";
			if(sti(pchar.money) >= 25000 && CheckAttribute(pchar, "DH_mercLeft"))
			{
				Link.l1 = "Беру.";
				Link.l1.go = "DH_Villemstad_shipyarder_getship";
			}
		break;
		case "DH_Villemstad_shipyarder_wait_money":
			dialog.Text = "Принесли деньги?.";
			Link.l1 = "Пока нет, нужно ещё уладить кое-какие дела.";
			Link.l1.go = "exit";
			if(sti(pchar.money) >= 25000 && CheckAttribute(pchar, "DH_mercLeft"))
			{
				Link.l1 = "Да.";
				Link.l1.go = "DH_Villemstad_shipyarder_getship";
			}
		break;
		case "DH_Villemstad_shipyarder_getship":
			PChar.quest.DHRaceAgainstTime.win_condition.l1 = "location";
			PChar.quest.DHRaceAgainstTime.win_condition.l1.location = "LaVega_town";
			PChar.quest.DHRaceAgainstTime.function = "DHRaceAgainstTime";
			SetQuestHeader("DHRaceAgainstTime");
			AddQuestRecord("DHRaceAgainstTime", "1");

			AddMoneyToCharacter(pchar, -25000);
			DeleteAttribute(pchar, "DH_mercLeft");
			pchar.location.from_sea = "Villemstad_town"
			setWDMPointXZ(pchar.location.from_sea);  // коорд на карте
			pchar.Ship.Type = GenerateShipExt(SHIP_EMPRESS, 0, pchar);
			ref shTo = &RealShips[sti(Pchar.Ship.Type)];
			shTo.SpeedRate        = 17.0;
			shTo.HP = 1900;
			shTo.WindAgainstSpeed = 7.35;
			shTo.TurnRate = 53.0;
			shTo.MaxCrew = 120;
			shTo.MastMultiplier = 1.45;
			shTo.Capacity = 1300;
			SetBaseShipData(pchar);
			pchar.Ship.Name = RandPhraseSimple(RandPhraseSimple(RandPhraseSimple(RandPhraseSimple(RandPhraseSimple(RandPhraseSimple(RandPhraseSimple(RandPhraseSimple("Быстрый вепрь", "Боевой тигр"), "Транспортер"), "Антилопа"), "Экстра"), "Молния"), "Дельфин"), "Загадочный"), "Ужасный");
			SetCrewQuantityFull(pchar);
			ChangeCrewExp(pchar, "Sailors", rand(30)+20);
			ChangeCrewExp(pchar, "Cannoners", rand(30)+20);
			ChangeCrewExp(pchar, "Soldiers", rand(30)+20);
			SetCharacterGoods(pchar, GOOD_SAILCLOTH, 20 + rand(50));
			SetCharacterGoods(pchar, GOOD_PLANKS, 20 + rand(50));
			SetCharacterGoods(pchar, GOOD_RUM, 50 + rand(100));
			// коцаем корабль
			pchar.ship.HP = sti(pchar.ship.HP) - makeint(sti(pchar.ship.HP)*0.05) * (MOD_SKILL_ENEMY_RATE);
			SetCrewQuantity(pchar, GetMinCrewQuantity(pchar));

			InterfaceStates.DisFastTravel = false;
			bDisableLandEncounters = false;

			dialog.Text = "Отлично, забирайте. На корабле даже остались какие-то припасы в трюме, мне не очень-то хотелось туда лезть.";
			Link.l1 = "Спасибо. До свидания.";
			Link.l1.go = "exit";
			npchar.Dialog.Filename = "Common_Shipyard.c";
			NextDiag.TempNode = "first time";
		break;

		case "DH_Villemstad_usurer":
			dialog.Text = "Наконец-то вы прибыли, а я уже начинал волноваться, куда же вы запропостились. Времена сейчас сами знаете неспокойные, слышали последние слухи?";
			Link.l1 = "Слухи это хорошо, но сейчас меня и моего спутника интересуют деловые вопросы.";
			Link.l1.go = "DH_Villemstad_usurer_0_1";
		break;
		case "DH_Villemstad_usurer_0_1":
			dialog.Text = "Да. Деловые вопросы. Вы желаете закрыть контракт с джентельменом?";
			Link.l1 = "Желаю. ";
			Link.l1.go = "DH_Villemstad_usurer_0_2";
		break;
		case "DH_Villemstad_usurer_0_2":
			dialog.Text = "Что же воля ваша. "+GetFullName(characterFromId("DH_mercenary"))+", поздравляю, ваш долг перед банком уплачен. ";
			Link.l1 = "...";
			Link.l1.go = "DH_Villemstad_usurer_0_3";
		break;
		case "DH_Villemstad_usurer_0_3":
			DialogExit();
			sld = CharacterFromID("DH_mercenary");
			LAi_ActorDialog(sld, pchar, "", -1.0, 0);
			sld.dialog.currentnode = "DH_Villemstad_usurer_0_4";
		break;
		case "DH_Villemstad_usurer_0_4":
			dialog.Text = "Ну бывай парень, не знаю как ты, а я пойду напьюсь встельку.";
			Link.l1 = "Дела не ждут.";
			Link.l1.go = "DH_Villemstad_usurer_0_5";
		break;
		case "DH_Villemstad_usurer_0_5":
			dialog.Text = "Как знаешь.";
			npchar.lifeday = 0;
			Link.l1 = "...";
			Link.l1.go = "DH_Villemstad_usurer_0_6";
		break;
		case "DH_Villemstad_usurer_0_6":
			DialogExit();
			pchar.DH_mercLeft = true;
			LocatorReloadEnterDisable("SantaCatalina_town", "reload5_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload4_back", false);
			LocatorReloadEnterDisable("SantaCatalina_exittown", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_exittown", "reload2_back", false);

			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			sld = CharacterFromID("Villemstad_usurer");
			Lai_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", 1.0, 0);
			sld.dialog.currentnode = "DH_Villemstad_usurer_0_7";
		break;

		case "DH_Villemstad_usurer_0_7":
			dialog.Text = "Что-то ещё?";
			Link.l1 = "Я бы хотел забрать свой вклад.";
			Link.l1.go = "DH_Villemstad_usurer_1";
		break;
		case "DH_Villemstad_usurer_1":
			dialog.Text = "Ваш вклад... Знаете, тут есть некоторая сложность...";
			Link.l1 = "Какая может быть сложность в возвращении мне моих денег?";
			Link.l1.go = "DH_Villemstad_usurer_2";
		break;
		case "DH_Villemstad_usurer_2":
			dialog.Text = "Видите ли... коммерция, иногда сделки удачны, иногда нет. Иногда деньги нужны срочно, иногда нет.";
			Link.l1 = "Но какое отношение ваши проблемы имеют к моему вкладу?";
			Link.l1.go = "DH_Villemstad_usurer_3";
		break;
		case "DH_Villemstad_usurer_3":
			dialog.Text = "За исключением того, что деньги я вам смогу вернуть не ранее чем через месяц - никаких. Но что такое месяц отсрочки для старых друзей?";
			Link.l1 = "Для старых друзей - ничего. Однако, в моем кармане сейчас так же пусто, как и в ваших закромах, а питаться этот месяц мне на что то нужно!";
			Link.l1.go = "DH_Villemstad_usurer_4";
		break;
		case "DH_Villemstad_usurer_4":
			dialog.Text = "Знаете, есть у меня одна вещица на ценителей, думаю, она покроет треть стоимости вашего вклада.";
			Link.l1 = "И какая же? ";
			Link.l1.go = "DH_Villemstad_usurer_6";
		break;
		case "DH_Villemstad_usurer_6":
			dialog.Text = "Хрустальный череп. Вот, смотрите.";
			Link.l1 = "Ну не знаю...  ";
			Link.l1.go = "DH_Villemstad_usurer_7";
		break;
		case "DH_Villemstad_usurer_7":
			dialog.Text = "Жаль с ним расставаться, но что не сделаешь для друга...";
			Link.l1 = "Ладно, уговорил, возьму его в счет 30 процентов и месяца отсрочки на остальное.";
			Link.l1.go = "DH_Villemstad_usurer_8";
		break;
		case "DH_Villemstad_usurer_8":
			LAi_SetOwnerTypeNoGroup(npchar);

			DeleteAttribute(pchar,"BlockOstin");

			Log_Info("Вы получили хрустальный череп.");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "sculMa"+(drand(2)+1), 1);
			dialog.Text = "Замечательно, с вами приятно иметь дело.";
			Link.l1 = "Я еще вернусь.";
			Link.l1.go = "exit";
			SaveCurrentQuestDateParam("questTemp.DH_Villemstad_money");
			NextDiag.TempNode = "DH_Villemstad_usurer_get_money";
			AddQuestRecord("DarkHumanQuestline", "6");
		break;
		case "DH_Villemstad_usurer_get_money":
			dialog.Text = "Простите, но у меня пока нет нужной суммы.";
			Link.l1 = "Я еще вернусь.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "DH_Villemstad_usurer_get_money";
			if (GetQuestPastDayParam("questTemp.DH_Villemstad_money") >= 28)
			{
				AddMoneyToCharacter(pchar, 35000);
				dialog.Text = "Я вас ждал. Теперь я готов вернуть ваш вклад. Вот, держите. Надеюсь, вы еще захотите воспользоваться моими услугами.";
				Link.l1 = "Ну каконец-то. Насчет последнего, то я бы не надеялся.";
				Link.l1.go = "exit";
				NextDiag.TempNode = "First time";
				npchar.Dialog.Filename = "Usurer_dialog.c";
			}

		break;

		case "DH_mercenary_SK_vavern":
			dialog.Text = "Здесь наши пути должны были разойтись.";
			Link.l1 = "Да вы выполнили свои обязательства в полном объеме согласно букве и духу нашего договора. Вторую часть вашего гонорара вы сможете получить на Кюрасао.";
			Link.l1.go = "DH_mercenary_SK_vavern_1";
		break;
		case "DH_mercenary_SK_vavern_1":
			dialog.Text = "Да-да-да. Знаю, но с учетом обстоятельств я бы предпочел сопровождать вас до банка Кюрасао. ";
			Link.l1 = "А что до остальных?";
			Link.l1.go = "DH_mercenary_SK_vavern_2";
		break;
		case "DH_mercenary_SK_vavern_2":
			dialog.Text = "Остальные отправятся отдельно, слишком большая группа привлечет лишнее внимание. ";
			Link.l1 = "Хорошо.";
			Link.l1.go = "DH_mercenary_SK_vavern_exit";
		break;
		case "DH_mercenary_SK_vavern_exit":
			DialogExit();
			sld = CharacterFromID("SantaCatalina_Smuggler");
			//LAi_ActorDialog(sld, pchar, "", -1.0, 0);
			sld.dialog.filename = "Quest\WhisperLine\DarkHuman.c";
			sld.dialog.currentnode = "DH_SK_smuggler";

			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;

		case "DH_SK_smuggler":
			dialog.Text = "Снова вы? Чем могу быть полезен? ";
			Link.l1 = "Мне и этому джентльмену необходимо добраться до Кюрасао.";
			Link.l1.go = "DH_SK_smuggler_1";
		break;
		case "DH_SK_smuggler_1":
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);
			dialog.Text = "Кюрасао значит, это можно. Два человека, тоже не проблема. Деньги на бочку.";
			Link.l1 = "Получи.";
			Link.l1.go = "DH_SK_smuggler_2";
		break;
		case "DH_SK_smuggler_2":
			AddMoneyToCharacter(pchar, -sti(pchar.money));
			pchar.money = 10;
			//Log_Info("Вы отдали все деньги, что были при вас.");
			PlaySound("interface\important_item.wav");
			dialog.Text = "Что-ж, этого достаточно, отплываем.";
			Link.l1 = "...";
			Link.l1.go = "DH_SK_smuggler_exit";
		break;
		case "DH_SK_smuggler_exit":
			DialogExit();
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			npchar.dialog.filename = "Smuggler_Agent_dialog.c";
			DoQuestFunctionDelay("DarkHuman_Villemstad", 1.0);
			WaitDate("",0,0,7,2,25);
		break;

		case "DH_mercenary_SK_gate":
			dialog.Text = "Добрались.";
			Link.l1 = "Черт, целых тридцать дней! Не думал, что это займет столько времени!";
			Link.l1.go = "DH_mercenary_SK_gate_1";
			PChar.quest.DHLockSK.win_condition.l1 = "location";
			PChar.quest.DHLockSK.win_condition.l1.location = "SantaCatalina_town";
			PChar.quest.DHLockSK.function = "DHLockSK";
		break;
		case "DH_mercenary_SK_gate_1":
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			pchar.BlockOstin = true;
			dialog.Text = "Я думаю теперь вы понимаете, почему мы запросили такую цену.";
			Link.l1 = "Да, пожалуй.";
			Link.l1.go = "exit";
		break;

		case "DH_mercenary_Amatike_return":
			dialog.Text = "Да какого черта тут творится?! ";
			Link.l1 = "Корабль уплыл? Неужели мы опоздали?";
			Link.l1.go = "DH_mercenary_Amatike_return_1";
		break;
		case "DH_mercenary_Amatike_return_1":
			dialog.Text = "Эй, парень! Объясни мне что происходит...";
			Link.l1 = "...";
			Link.l1.go = "DH_mercenary_Amatike_return_2_sailor";
		break;
		case "DH_mercenary_Amatike_return_2_sailor":
			DialogExit();
			sld = CharacterFromID("DH_sailor");
			LAi_ActorDialog(sld, pchar, "", -1.0, 0);
			sld.dialog.filename = "Quest\WhisperLine\DarkHuman.c";
			sld.dialog.currentnode = "DH_mercenary_Amatike_return_3_sailor";
		break;
		case "DH_mercenary_Amatike_return_3_sailor":
			dialog.Text = "Вы... вы вернулись, слава богу!";
			Link.l1 = "Вот сейчас и узнаем что здесь творится! Куда делся корабль? Семь дней еще не вышли!";
			Link.l1.go = "DH_mercenary_Amatike_return_4_sailor";
		break;
		case "DH_mercenary_Amatike_return_4_sailor":
			dialog.Text = "Испанцы на корвете.\nКак только вы изволили уйти с берега, из-за мыса выплыл испанский корвет. Капитан отдал команду отходить, но этот подлец смог нас догнать у выхода из бухты. ";
			Link.l1 = "Дальше...";
			Link.l1.go = "DH_mercenary_Amatike_return_5_sailor";
		break;
		case "DH_mercenary_Amatike_return_5_sailor":
			dialog.Text = "Полегче мистер, мы здесь все в одной лодке. ";
			Link.l1 = "Не тяни, парень.";
			Link.l1.go = "DH_mercenary_Amatike_return_6_sailor";
		break;
		case "DH_mercenary_Amatike_return_6_sailor":
			dialog.Text = "Корвет дал залп по кораблю, меня сбросило с мачты и я чудом упал между скал. ";
			Link.l1 = "А корабль?";
			Link.l1.go = "DH_mercenary_Amatike_return_7_sailor";
		break;
		case "DH_mercenary_Amatike_return_7_sailor":
			dialog.Text = "Пусть наш корабль и не самый сильный, зато шустрый, к тому же у корвета был поврежден корпус, капитан смог уйти в море. ";
			Link.l1 = "Так, а ты?";
			Link.l1.go = "DH_mercenary_Amatike_return_8_sailor";
		break;
		case "DH_mercenary_Amatike_return_8_sailor":
			dialog.Text = "А что я? Меня не заметили, тем более что я спрятался у скалы. Я все видел своими глазами. Когда корвет отошел достаточно я добрался до берега и стал ждать вас, я знал, что вы должны вернуться.";
			Link.l1 = "Допустим.";
			Link.l1.go = "DH_mercenary_Amatike_return_9";
		break;
		case "DH_mercenary_Amatike_return_9":
			DialogExit();
			sld = CharacterFromID("DH_mercenary");
			LAi_ActorDialog(sld, pchar, "", -1.0, 0);
			sld.dialog.currentnode = "DH_mercenary_Amatike_return_10";
		break;
		case "DH_mercenary_Amatike_return_10":
			dialog.Text = "И что нам с ним делать?";
			Link.l1 = "В расход.";
			Link.l1.go = "DH_mercenary_Amatike_return_kill";
			Link.l2 = "Я не думаю что он нас задержит, а лишние руки в пути не помешают.";
			Link.l2.go = "DH_mercenary_Amatike_return_10_1";
		break;
		case "DH_mercenary_Amatike_return_10_1":
			ChangeCharacterReputation(PChar, 30);
			dialog.Text = "Ладно.";
			Link.l1 = "...";
			Link.l1.go = "DH_mercenary_Amatike_return_11";
		break;
		case "DH_mercenary_Amatike_return_kill":
			DialogExit();
			sld = CharacterFromID("DH_sailor");
			LAi_ActorDialog(sld, pchar, "", -1.0, 0);
			sld.dialog.currentnode = "DH_mercenary_Amatike_return_kill_1";
			sld = CharacterFromID("DH_mercenary");
			sld.dialog.currentnode = "DH_mercenary_Amatike_return_11";
		break;
		case "DH_mercenary_Amatike_return_11":
			dialog.Text = "Что будем делать дальше?";
			Link.l1 = "Добираться до города своим ходом.";
			Link.l1.go = "DH_mercenary_Amatike_return_12";

			for (i = 0; i < 4; i++)
			{
				sld = CharacterFromID("DH_merc_mush" + i);
				LAi_SetActorTypeNoGroup(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				sld = CharacterFromID("DH_merc_blade" + i);
				LAi_SetActorTypeNoGroup(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
		break;
		case "DH_mercenary_Amatike_return_kill_1":
			ChangeCharacterReputation(PChar, -30);
			dialog.Text = "Пожалуйста, не трогайте меня!";
			Link.l1 = "Не дергайся ты так, тогда ничего не почувствуешь.";
			Link.l1.go = "exit_fight_sailor";
		break;
		case "DH_mercenary_Amatike_return_12":
			dialog.Text = "До Санта Каталины путь не близкий.";
			Link.l1 = "Да и испанский корвет может вернуться в любой момент, плюс наблюдательная команда.";
			Link.l1.go = "DH_mercenary_Amatike_return_13";
		break;
		case "DH_mercenary_Amatike_return_13":
			dialog.Text = "Понял.";
			Link.l1 = "К счастью мы предусмотрели такой вариант развития событий.";
			Link.l1.go = "DH_mercenary_Amatike_return_14";
		break;
		case "DH_mercenary_Amatike_return_14":
			dialog.Text = "Ваша правда. В путь?";
			Link.l1 = "В путь.";
			Link.l1.go = "DH_mercenary_Amatike_return_15_exit";
		break;
		case "DH_mercenary_Amatike_return_15_exit":
			DialogExit();
			LAi_ActorFollowEverywhere(npchar, "", -1);

			LAi_Fade("", "");
			WaitDate("",0,1,3,17,25);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			DoQuestFunctionDelay("DarkHuman_SK", 1.5);
		break;

		case "DH_mercenary_temple_afterstash":
			for (i = 0; i < 4; i++)
			{
				sld = CharacterFromID("DH_merc_mush" + i);
				LAi_SetImmortal(sld, true);
				sld = CharacterFromID("DH_merc_blade" + i);
				LAi_SetImmortal(sld, true);
			}
			dialog.Text = "Проблемы? ";
			Link.l1 = "Ничего такого с чем нельзя было бы справиться... В итоге.";
			Link.l1.go = "DH_mercenary_temple_afterstash_1";
		break;
		case "DH_mercenary_temple_afterstash_1":
			dialog.Text = "Что? ";
			Link.l1 = "Все готовы выдвигаться, нельзя терять времени. Корабль все еще ждет нас, а альтернативный путь ... займет слишком много времени. ";
			Link.l1.go = "DH_mercenary_temple_afterstash_2";
		break;
		case "DH_mercenary_temple_afterstash_2":
			dialog.Text = "Да, но к чему ТАКАЯ спешка?";
			Link.l1 = "Время не ждет, да и очередная группа индейцев может нагрянуть в любой момент.";
			Link.l1.go = "DH_mercenary_temple_afterstash_3";
		break;
		case "DH_mercenary_temple_afterstash_3":
			dialog.Text = "Действительно... Слышали парни, встаем и выдвигаемся!";
			Link.l1 = "...";
			Link.l1.go = "DH_mercenary_temple_afterstash_exit";
		break;
		case "DH_mercenary_temple_afterstash_exit":
			DialogExit();
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			for (i = 0; i < 4; i++)
			{
				sld = CharacterFromID("DH_merc_mush" + i);
				LAi_SetActorTypeNoGroup(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				sld = CharacterFromID("DH_merc_blade" + i);
				LAi_SetActorTypeNoGroup(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}

			LocatorReloadEnterDisable("Temple", "reload1_back", false);
			LocatorReloadEnterDisable("Temple", "reload2", true);
			DeleteAttribute(pchar, "CantTakeItems");
		break;

		case "Dark_Incquisitor":
			dialog.Text = "Слава богу вы спа... это он, убейте его!";
			Link.l1 = "...";
			Link.l1.go = "Dark_Incquisitor_fight";
		break;
		case "Dark_Incquisitor_fight":
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorTypeNoGroup(npchar);
			sld = CharacterFromID("Dark_Incquisitor1");
			LAi_SetWarriorTypeNoGroup(sld);
			sld = CharacterFromID("Dark_Incquisitor2");
			LAi_SetWarriorTypeNoGroup(sld);
			AddQuestRecord("DarkHumanQuestline", "2");
			PChar.quest.DarkHuman_Temple_Stash.win_condition.l1 = "locator";
			PChar.quest.DarkHuman_Temple_Stash.win_condition.l1.location = "Temple_Inside";
			PChar.quest.DarkHuman_Temple_Stash.win_condition.l1.locator_group = "item";
			PChar.quest.DarkHuman_Temple_Stash.win_condition.l1.locator = "item1";
			PChar.quest.DarkHuman_Temple_Stash.function = "DarkHuman_Temple_Stash";
		break;

		case "DH_Ambush":
			dialog.Text = "Вот мы и встретились, дружок. Нам велели брать тебя живым, по возможности. Так что бросай оружие!";
			Link.l1 = "Вот еще, лучше скажи мне, кто вас нанял?";
			Link.l1.go = "DH_Ambush_1";
		break;
		case "DH_Ambush_1":
			dialog.Text = "Я сказал, бросай оружие!";
			Link.l1 = "Я вижу, диалог у нас не идет... Что же поступим по-другому.";
			Link.l1.go = "DH_Ambush_fight";
		break;
		case "DH_Ambush_fight":
			LAi_SetWarriorTypeNoGroup(npchar);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_Attack(NPChar, Pchar);
		break;

		case "DH_mercenary_temple_afterfight":
			dialog.Text = "Отлично всех положили. Красножопый сброд, что они могут против доброго мушкетного залпа ... хе хе хе.";
			Link.l1 = "Теперь путь свободен.";
			Link.l1.go = "DH_mercenary_temple_afterfight_1";
		break;
		case "DH_mercenary_temple_afterfight_1":
			dialog.Text = "Да, мы останемся здесь. Мало ли кто пожалует по наши души. А вы идите зачем пришли... ";
			Link.l1 = "В пирамиде, судя по всему кто то есть.";
			Link.l1.go = "DH_mercenary_temple_afterfight_2";
		break;
		case "DH_mercenary_temple_afterfight_2":
			dialog.Text = "И они будут без меры вам ...";
			Link.l1 = "... нам ...";
			Link.l1.go = "DH_mercenary_temple_afterfight_3";
		break;
		case "DH_mercenary_temple_afterfight_3":
			chrDisableReloadToLocation = false;
			dialog.Text = "... нам благодарны за спасение. Но если что зовите. Минута и мы будем рядом.";
			Link.l1 = "...";
			Link.l1.go = "exit";
		break;

		case "DH_mercenary_temple":
			dialog.Text = "Там индейцы, судя по всему потрепанные.";
			Link.l1 = "Сколько их там?";
			Link.l1.go = "DH_mercenary_temple_2";
		break;
		case "DH_mercenary_temple_2":
			dialog.Text = "Восемь плюс десяток трупов. Нам вполне по силам их опрокинуть, если будем действовать решительно.";
			Link.l1 = "Решительный удар?";
			Link.l1.go = "DH_mercenary_temple_3";
		break;
		case "DH_mercenary_temple_3":
			dialog.Text = "Именно.";
			Link.l1 = "Вперед, в атаку!";
			Link.l1.go = "DH_mercenary_temple_exit";
		break;
		case "DH_mercenary_temple_exit":
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SetCharacterTask_FollowCharacter(npchar, PChar);
			LAi_warrior_DialogEnable(npchar, false);
			chrDisableReloadToLocation = true;
			for (i = 0; i < 4; i++)
			{
				sld = CharacterFromID("DH_merc_mush" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				SetCharacterTask_FollowCharacter(sld, PChar);
				sld = CharacterFromID("DH_merc_blade" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				SetCharacterTask_FollowCharacter(sld, PChar);
			}

			for (i = 0; i < sti(pchar.maxIndians) * 2; i++)
			{
				sld = CharacterFromID("DHindian" + i);
				LAi_SetWarriorTypeNoGroup(sld);
			}
			LAi_group_SetRelation("Jungle_indians", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("Jungle_indians", LAI_GROUP_PLAYER, true);
		break;

		case "DH_mercenary_shore":
			dialog.Text = "Доброе утро начальник, мы на месте.";
			Link.l1 = "Доброе. Следующая цель известна?";
			Link.l1.go = "DH_mercenary_shore_1";
		break;
		case "DH_mercenary_shore_1":
			dialog.Text = "Пирамида...";
			Link.l1 = "Да пирамида. Вам эта местность известна лучше чем мне. Что вы посоветуете?";
			Link.l1.go = "DH_mercenary_shore_2";
		break;
		case "DH_mercenary_shore_2":
			dialog.Text = "Во первых не терять время, во вторых держать глаза открытыми, а оружие в готовности.";
			Link.l1 = "Индейцы?";
			Link.l1.go = "DH_mercenary_shore_3";
		break;
		case "DH_mercenary_shore_3":
			dialog.Text = "Да, чертовы дикари. Впрочем огневой мощи у нас немало. (кивает на парней поблизости)";
			Link.l1 = "Тогда действительно не будем терять времени.";
			Link.l1.go = "DH_mercenary_shore_exit";
		break;
		case "DH_mercenary_shore_exit":
			DialogExit();
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			for (i = 0; i < 4; i++)
			{
				sld = CharacterFromID("DH_merc_mush" + i);
				LAi_ActorFollowEverywhere(sld, "", -1);
				sld = CharacterFromID("DH_merc_blade" + i);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			PChar.quest.DarkHuman_Temple.win_condition.l1 = "location";
			PChar.quest.DarkHuman_Temple.win_condition.l1.location = "Temple";
			PChar.quest.DarkHuman_Temple.function = "DarkHuman_Temple";

			pchar.SystemInfo.ChangePIRATES = true;
			LaunchCharacter(pchar);
		break;

		case "PGG_transporter":
			//LAi_ActorSetSitMode(pchar);
			dialog.Text = "Мы прибыли, ваши люди готовы к высадке.";
			Link.l1 = "Отлично, ваши обязательства по контракту практически выполнены.";
			Link.l1.go = "PGG_transporter_1";
		break;
		case "PGG_transporter_1":
			dialog.Text = "Шлюпка ожидает.";
			Link.l1 = "Замечательно, время ожидания?";
			Link.l1.go = "PGG_transporter_2";
		break;
		case "PGG_transporter_2":
			dialog.Text = "Неделя с текущей даты.";
			Link.l1 = "Все верно, ну в путь.";
			Link.l1.go = "PGG_transporter_exit";
		break;
		case "PGG_transporter_exit":
			DialogExit();
			NextDiag.CurrentNode = "Second Time";
			if (npchar.sex != "woman")	npchar.Dialog.FileName = "PGG_dialog.c";
			else	npchar.Dialog.FileName = "pgg_dialog_town.c";
			//PGG_ChangeRelation2MainCharacter(npchar, 25);
			DoQuestFunctionDelay("DarkHuman_Amatike", 1.0);
			//LAi_SetWarriorType(npchar);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_fight_sailor":
			pchar.quest.DH_mercenary.win_condition.l1 = "NPC_Death";
			pchar.quest.DH_mercenary.win_condition.l1.character ="DH_sailor";
			PChar.quest.DH_mercenary.function = "SpeakAfterKill";
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			LAi_group_MoveCharacter(NPChar, LAI_GROUP_MONSTERS);
			LAi_SetImmortal(npchar, false);
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			DialogExit();


			sld = CharacterFromID("DH_mercenary");
			LAi_SetWarriorTypeNoGroup(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SetCharacterTask_FollowCharacter(sld, PChar);
			LAi_warrior_DialogEnable(sld, false);
			chrDisableReloadToLocation = true;
			for (i = 0; i < 4; i++)
			{
				sld = CharacterFromID("DH_merc_mush" + i);
				if (CheckAttribute(sld, "model"))
				{
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
					SetCharacterTask_FollowCharacter(sld, PChar);
				}

				sld = CharacterFromID("DH_merc_blade" + i);
				if (CheckAttribute(sld, "model"))
				{
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
					SetCharacterTask_FollowCharacter(sld, PChar);
				}

			}
		break;

		case "exit_fight":
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			LAi_group_MoveCharacter(NPChar, LAI_GROUP_MONSTERS);
			LAi_SetImmortal(npchar, false);
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			DialogExit();
		break;
	}
}

