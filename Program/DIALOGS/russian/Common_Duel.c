//navy 26.07.06
//генератор дуэлей...
//в диалоге НПС делаем линк с проверкой флага оскорбления... по нему переход на "outraged"
//если НПС сделал что-то ГГ (продажа фальшивки) или ГГ наехал на НПС, вешаем на него флаг.
//для некоторых, например ПГГ, можно делать переход сразу на вызов: "let_s_duel"
void ProcessDuelDialog(ref NPChar, aref Link, aref NextDiag)
{
	int iHour;
	string sLocation;

	//флаг убираем
	DeleteAttribute(NPChar, "Outrage");
    switch (Dialog.CurrentNode)
	{
	case "outraged":
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() +
				RandPhraseSimple("Как ты смеешь меня оскорблять, мерзав"+ GetSexPhrase("ец","ка") +"?!", "Ты дорого заплатишь за свои слова!"),
				RandPhraseSimple("Вы задели мою честь, " + GetAddress_Form(NPChar) + "! За это придётся заплатить.", "Как вы смеете? Немедленно возьмите свои слова назад!"));

		//это такая засада.. чтобы читали текст :)
		MakeRandomLinkOrderTwo(link,
					NPCharRepPhrase(pchar,
				RandPhraseSimple("Ха??!! Да я об тебя и шпагу марать не хочу!", "Ха??!! Да я об тебя и шпагу марать не хочу!"),
				RandPhraseSimple("Я всегда к вашим услугам!", "Я не намерен"+ GetSexPhrase("","а") +" выбирать выражения, разговаривая с отребьем!")), "outraged_1",
					NPCharRepPhrase(pchar, RandSwear() +
				RandPhraseSimple("Я не это имел"+ GetSexPhrase("","а") +" в виду...", "Я погорячил"+ GetSexPhrase("ся","ась") +"..."),
				RandPhraseSimple("Это была ошибка. Прошу прощения.", "Я обознал"+ GetSexPhrase("ся","ась") +", " + GetAddress_FormToNPC(NPChar) + ". Прошу меня простить.")), "change_mind");
		break;

	case "outraged_1":
		Dialog.Text = NPCharRepPhrase(NPChar,
				RandPhraseSimple("Я тебе уши обрежу!", "Я вырежу тебе сердце!"),
				RandPhraseSimple("Я надеюсь, вы немедленно принесёте свои извинения, или я за себя не ручаюсь!", "Вы понимаете, что это означает?"));

		MakeRandomLinkOrderTwo(link,
					NPCharRepPhrase(pchar, RandSwear() +
				RandPhraseSimple("Надеюсь, твоя шпага так же быстра, как твой язык!", "За меня будет говорить мой клинок."),
				RandPhraseSimple("Я вызываю вас на дуэль!", "Это дело чести!")), "let_s_duel",
					NPCharRepPhrase(pchar,
				RandPhraseSimple("Пожалуй, я ещё не готов"+ GetSexPhrase("","а") +" к встрече с дьяволом!", "Думаю, не стоит так горячиться! Это только слова!"),
				RandPhraseSimple("Я тут вспомнил"+ GetSexPhrase("","а") +", меня ждут. Всех благ...", "Ах! Кажется, мой корабль уже отплывает.")), "change_mind");
		break;

	case "let_s_duel":
		//проверка на начатые дуэли.
		if (CheckAttribute(PChar, "questTemp.duel.Start") && sti(PChar.questTemp.duel.Start))
		{
			Dialog.Text = "Тебе стоит сначала разобраться с другими, а потом мы поговорим.";
			if (PChar.questTemp.duel.enemy == NPChar.id)
			{
				Dialog.Text = "Мы уже с тобой договорились обо всём.";
			}
			link.l1 = RandSwear() + "Как это я забыл"+ GetSexPhrase("","а") +"...";
			link.l1.go = "exit";
			break;
		}
		//может отказаться.
		if (drand(36) < GetCharacterSPECIALSimple(PChar, SPECIAL_E) + GetCharacterSPECIALSimple(PChar, SPECIAL_S) + GetCharacterSPECIALSimple(PChar, SPECIAL_A))         //WW
		{
			Dialog.Text = RandPhraseSimple("Дуэль?!!! Проваливай, ты не стоишь потраченного времени.", "Дуэль? Слишком много чести! Сгинь!");
			link.l1 = RandPhraseSimple("Ну-ну...", "Я могу и подождать...");
			link.l1.go = "exit";
/**/
			//можно дать возможность драться полюбому :)
			if (drand(36) < GetCharacterSPECIALSimple(PChar, SPECIAL_E) + GetCharacterSPECIALSimple(PChar, SPECIAL_S) + GetCharacterSPECIALSimple(PChar, SPECIAL_A))    //WW
			{
				link.l1 = RandPhraseSimple("Ну, это мы сейчас посмотрим!!!", "Да что ты говоришь?! Сейчас я увижу цвет твоей крови!");
				link.l1.go = "fight_right_now";
			}
/**/
			break;
		}

		//согласен.
		Dialog.Text = RandPhraseSimple("Дуэль, говоришь? Пожалуй, я не против размяться.",
			"Ты хотя бы знаешь какой стороной шпагу держать?");
		link.l1 = RandPhraseSimple("Ты будешь на коленях просить о пощаде.", "Я прикончу тебя вот этими руками, мерза"+ GetSexPhrase("вец","вка") +"!");
		link.l1.go = "land_duel";
		if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
		{
			Dialog.Text = RandPhraseSimple(Dialog.Text + " Или мы можем выйти в море и посмотреть, кто на что способен!",
				"Дуэль?!! Ха, да я раздавлю тебя как блоху! Выбирай, как ты умрешь!");
			link.l2 = RandPhraseSimple("В море мне нет равных.", "Мой корабль пустит ко дну твоё старое корыто!");
			link.l2.go = "sea_duel";
		}
		link.l3 = "Я передумал"+ GetSexPhrase("","а") +"...";
		link.l3.go = "change_mind";
		break;

	//дуэль на подводных лодках :))))
	case "sea_duel":
		Dialog.Text = RandPhraseSimple("Что-то не вижу твоего корабля в порту...", "Проваливай, пока не найдёшь себе хоть какое-нибудь корыто!!!");
		link.l1 = RandPhraseSimple("Моя ошибка...", "...Тогда я вас покидаю.");
		link.l1.go = "exit";
		if (pchar.location.from_sea == GetCurrentTown() + "_town")
		{
			Dialog.Text = "Что ж, жду тебя на выходе из бухты...";
			link.l1 = "Долго не придётся ждать.";

			pchar.questTemp.Duel.enemy = NPChar.id;
			pchar.questTemp.Duel.Sea_Location = Islands[GetCharacterCurrentIsland(PChar)].id;
			AddDialogExitQuestFunction("Duel_Sea_Prepare");
		}

		break;

	//на суше
	case "land_duel":
		iHour = 1 + rand(2);
		if (GetTime() > 4.0 && GetTime() < 17.0)
		{
//			iHour = MakeInt(18.0 - GetTime()) + rand(2); //раскоментировать для дуэлей только по ночам
		}
		pchar.questTemp.Duel.WaitTime = iHour;
		Dialog.Text = RandSwear() + RandPhraseSimple("Доставай свой клинок, и мы посмотрим, какого цвета твоя кровь!", "Ну, если ты так хочешь умереть...");
		link.l1 = RandPhraseSimple("Лучше нам пойти туда, где свидетелей поменьше. Я знаю одно местечко за городскими воротами. Встретимся там через " + iHour + " часа.",
			"Эй... не так быстро. Такие дела лучше делать без свидетелей. Приходи через " + iHour + " часа к входу в город.");
		link.l1.go = "fight_off_town";
		link.l2 = RandPhraseSimple("Ну, если ты так торопишься умереть...", "Проклятье! Я помогу тебе отправиться в ад!!!");
		link.l2.go = "fight_right_now";
		link.l3 = "Я передумал"+ GetSexPhrase("","а") +"...";
		link.l3.go = "change_mind";

		if (drand(1))
		{
			Dialog.Text = RandSwear() + RandPhraseSimple("Я думаю, нам стоит выйти за городские ворота. Жду тебя там через " + pchar.questTemp.Duel.WaitTime + " часа. Не задерживайся!",
				"Тут не лучшее место для разбирательств. Лучше выйдем из города. Через " + pchar.questTemp.Duel.WaitTime + " часа я буду там.");
			link.l1 = RandPhraseSimple("Слишком много чести! Защищайся!", "Мне некогда! Доставай свой клинок!");
			link.l1.go = "fight_right_now";
			link.l2 = RandPhraseSimple("Что ж, давай прогуляемся.", "Пожалуй, ты прав"+ NPCharSexPhrase(NPChar,"","а") +". Встретимся за воротами.");
			link.l2.go = "fight_off_town_prep";
		}
		break;

	//предложение "пойдем выйдем" рассматривается
	case "fight_off_town":
		Dialog.Text = RandPhraseSimple("Слишком много чести! Защищайся!", "Мне некогда! Здесь и сейчас!");
		link.l1 = RandPhraseSimple("Ну, если ты так торопишься умереть...", "Проклятье! Я помогу тебе отправиться в ад!!!");
		link.l1.go = "fight_right_now";
		if (drand(1))
		{
			Dialog.Text = RandPhraseSimple("Что ж, давай прогуляемся.", "Пожалуй, ты прав"+ NPCharSexPhrase(NPChar,"","а") +". Встретимся за воротами.");
			link.l1 = RandPhraseSimple("Жду тебя там.", "Не опаздывай.");
			link.l1.go = "fight_off_town_prep";
		}
		break;

	//что ж, пойдем выйдем
	case "fight_off_town_prep":
		SaveCurrentQuestDateParam("questTemp.Duel.StartTime");
		PChar.questTemp.duel.Start = true;
		PChar.questTemp.duel.enemy = NPChar.id;
		sLocation = GetCurrentTown();
		if (sLocation != "")
		{
			//где?
			sLocation += "_ExitTown";
			pchar.questTemp.duel.place = sLocation;

			Locations[FindLocation(sLocation)].DisableEncounters = true;
			//приходит ко времени.
			pchar.quest.duel_move_opponent2place.win_condition.l1 = "Location";
			pchar.quest.duel_move_opponent2place.win_condition.l1.location = pchar.questTemp.duel.place;
			pchar.quest.duel_move_opponent2place.function = "Duel_Move_Opponent2Place";
			//на случай, если не дождется, часа вполне достаточно
			SetTimerConditionParam("duel_move_opponentBack", "Duel_Move_OpponentBack", 0, 0, 0, sti(GetTime() + 0.5) + sti(pchar.questTemp.Duel.WaitTime) + 1, false);
			pchar.quest.duel_move_opponentBack.function = "Duel_Move_OpponentBack";
			if (CheckAttribute(NPChar, "CityType"))
			{
				DeleteAttribute(NPChar, "City"); // чтоб не было ругани с нацией
	    		DeleteAttribute(NPChar, "CityType");
				if (!CheckAttribute(NPChar, "PGGAi"))
				{
					if (!CheckAttribute(NPChar, "LifeDay")) npchar.LifeDay = 0;
					npchar.LifeDay = sti(npchar.LifeDay) + 3; // чтоб до дуэли не помер
				}
    		}
		}
		NextDiag.CurrentNode = "let_s_duel";
		DialogExit();
		break;

	//последнее слово перед боем
	case "talk_off_town":
		Dialog.Text = "Ну что, ты готов"+ GetSexPhrase("","а") +" отправиться в ад?";
		link.l1 = "Да. Сейчас посмотрим, кто кого!";
		link.l1.go = "fight_right_now";
		link.l2 = "Нет, я решил"+ GetSexPhrase("","а") +" принести тебе извинения. Был"+ GetSexPhrase("","а") +" неправ"+ GetSexPhrase("","а") +", вспылил"+ GetSexPhrase("","а") +".";
		link.l2.go = "change_mind";
		if (drand(36) < GetCharacterSPECIALSimple(PChar, SPECIAL_E) + GetCharacterSPECIALSimple(PChar, SPECIAL_S) + GetCharacterSPECIALSimple(PChar, SPECIAL_A))  //WW
		{
			Dialog.Text = RandPhraseSimple("Слушай, я тут подумал"+ NPCharSexPhrase(NPChar,"","а") +" и понял"+ NPCharSexPhrase(NPChar,"","а") +", что был"+ NPCharSexPhrase(NPChar,"","а") +" неправ"+ NPCharSexPhrase(NPChar,"","а") +". Приношу свои извинения",
				"Чёрт! Это всё ром!!! Прости, "+ GetSexPhrase("брат","сестра") +"!");
			link.l1 = NPCharRepPhrase(pchar,
				RandPhraseSimple("Ну уж нет, теперь только твоя кровь может принести мне удовлетворение!", "Доставай свою шпагу, и нечего тут сопли распускать!"),
				RandPhraseSimple("Нет! Я требую сатисфакции!", "Вы - позор своей семьи! Доставайте свою шпагу!"));
			link.l1.go = "fight_right_now";
			link.l2 = NPCharRepPhrase(pchar,
				RandPhraseSimple("Что ж, соглас"+ GetSexPhrase("ен","на") +". Погорячились.", "Какие счёты между своими!!"),
				RandPhraseSimple("Пожалуй, вы правы. Не стоит проливать кровь по пустякам.", "Моё великодушие не знает границ! Вы прощены!"));
			link.l2.go = "peace";
		}
		NextDiag.TempNode = npchar.BackUp.DialogNode;
		pchar.questTemp.Duel.End = true;
		break;

	//дуэли быть!
	case "fight_right_now":
		if(findsubstr(npchar.id, "PsHero_" , 0) != -1)
		{
			LAi_SetCheckMinHP(npchar, 1, true, "PGG_CheckHPDuel");
			SaveCurrentQuestDateParam("pchar.questTemp.DuelCooldown");
			chrDisableReloadToLocation = true;
		}
		PChar.questTemp.duel.enemy = NPChar.id;
		AddDialogExitQuestFunction("Duel_Prepare_Fight");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "fight_right_now_1":	                  //WW  ?????
		PChar.questTemp.duel.enemy = NPChar.id;
		PChar.questTemp.duel.enemyQty = rand(2) + 1;
		AddDialogExitQuestFunction("Duel_Prepare_Fight");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	//передумал, э... не хорошо ;)
	case "change_mind":
		if (CheckAttribute(pchar, "questTemp.Duel.End")) LAi_SetWarriorType(NPChar);
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() +
				RandPhraseSimple("Тогда проваливай отсюда!", "Скройся тогда. А то я могу передумать."),
				RandPhraseSimple("В таком случае, не смею вас больше задерживать!", "Тогда вам лучше уйти, пока я не передумал"+ NPCharSexPhrase(NPChar,"","а") +"."));
		link.l1 = "Уже ухожу...";
		link.l1.go = "peace";
		break;

	case "after_peace":
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() +
				RandPhraseSimple("Проваливай отсюда!", "Скройся. А то я могу передумать."),
				RandPhraseSimple("Чем могу быть полез"+ NPCharSexPhrase(NPChar,"ен","на") +"?", "Вы что-то хотели?"));
		link.l1 = "Я ухожу.";
		link.l1.go = "peace";
		break;

	//мир и все такое.
	case "peace":
		NextDiag.CurrentNode = "after_peace";
		DialogExit();
		break;

	case "Duel_Won":
		LAi_SetCurHPMax(npchar);
		Dialog.text = "Проклятье! Я сдаюсь.";
		link.l1 = "Я сегодня "+GetSexPhrase("добрый","добрая")+". Вали отсюда.";
		link.l1.go = "duel_nomoney";
		link.l2 = "Отлично. А теперь выворачивай карманы!";
		link.l2.go = "duel_money";
		NextDiag.TempNode = "Second time";
		break;
	case "duel_nomoney":
		ChangeCharacterReputation(pchar, 10);
		PGG_ChangeRelation2MainCharacter(npchar, 20);
		Dialog.text = "Проклятье, ты это серьёзно? Не скажу, что поступил"+NPCharSexPhrase(npchar, "","а")+ " бы также, будь я на твоём месте. Я этого не забуду.";
		link.l1 = "Иди давай, пока я не передумал"+GetSexPhrase("","а")+".";
		link.l1.go = "duel_exit";
		break;
	case "duel_money":
		ChangeCharacterReputation(pchar, -25);
		PGG_ChangeRelation2MainCharacter(npchar, -30);
		AddMoneyToCharacter(pchar, sti(npchar.money)/3);
		AddMoneyToCharacter(npchar, -sti(npchar.money)/3);
		Dialog.text = "Ах ты, "+GetSexPhrase("мерзавец","мерзавка")+"! Ну ничего, я ещё с тобой поквитаюсь.";
		link.l1 = "Буду ждать с нетерпением.";
		link.l1.go = "duel_exit";
		if (!CheckAttribute(npchar, "PGGAi.Boosted"))
		{
			Train_PPG(npchar, true, true);
		}
		break;
	case "duel_exit":
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestFreeLocator2Pchar("reload"), npchar.PGGAi.location.town+"_Tavern", "", "", "", 10.0);
		NextDiag.CurrentNode = NextDiag.TempNode;
		LAi_SetImmortal(npchar, false);
		DialogExit();
		break;

	case "TreasureHunterPGG":
		NextDiag.CurrentNode = "Second time";
		//dialog.text = "Постой-ка, "+ GetSexPhrase("приятель","подруга") +"... Сдается, у тебя есть кое-что интересное. Нужно делиться с близкими найдеными сокровищами.";
		dialog.text = RandPhraseSimple("Я так и подозревал" + npcharSexPhrase(npchar,"","а") + ", что этот жулик продал больше одной карты. Не зря я его убил" + npcharSexPhrase(npchar,"","а")+".","Постой-ка, "+ GetSexPhrase("приятель","подруга") +". Эта карта - моя. Не знаю, как именно она у тебя оказалась, но у меня её стащил по пьяни один жулик. Так что эти сокровища тебе не принадлежат. ");
	    //if (PGG_ChangeRelation2MainCharacter(npchar, 0) < 41)
		if (sti(npchar.reputation) < 41)
		{
			dialog.text = "Ты был"+GetSexPhrase("","а")+" настолько слеп"+GetSexPhrase("","а")+", что не замечал"+GetSexPhrase("","а")+" слежки вплоть до самого сокровища";
			Link.l1 = "Ну что же, пришло время отделиться твоей голове от тела.";
			Link.l1.go = "battleTreasure";
			break;
		}
		Link.l1 = "Да уж, неловкая ситуация. Сам" + npcharSexPhrase(npchar,"","а") + " понимаешь, просто так я этот клад не отдам, ведь мне эта карта не даром досталась, да и путь сюда был не близкий. Но ссориться с тобой я не желаю. Предлагаю разделить добычу.";
		Link.l1.go = "Cost_Head";
            // boal 08.04.04 -->
        Link.l2 = "Ну что же, всякое в жизни бывает, не повезло тебе. А теперь прочь с дороги!";
		Link.l2.go = "NoMoney_1";
		break;
	case "battleTreasure":
        AddDialogExitQuest("Battle_PGGHunters_Land");
		PChar.quest.PGGbattleTreasure.win_condition.l1 = "NPC_Death";
		PChar.quest.PGGbattleTreasure.win_condition.l1.character = npchar.id;
		PChar.quest.PGGbattleTreasure.function = "T102_DoorUnlock";
        DialogExit();
        break;
	case "Cost_Head":
			PChar.HunterCost = MOD_SKILL_ENEMY_RATE/4 * sti(npchar.rank) * 1000 + rand(1000);
			dialog.text = "Даже так? Я уже был"+ NPCharSexPhrase(NPChar,"","а") +" готов"+ NPCharSexPhrase(NPChar,"","а") +" за оружие браться\nНу что же, я не против. Думаю, что " + sti(PChar.HunterCost) + " пиастров меня устроит.";
			if(makeint(Pchar.money) < sti(PChar.HunterCost))
            {
                Link.l1 = "У меня нет таких денег.";
                Link.l1.go = "NoMoney";
            }
			else
			{
                Link.l1 = "Так и быть, забирай.";
                Link.l1.go = "Cost_Head2";
                Link.l2 = "Такую сумму отдавать, непонятно кому... Уж лучше я тебя просто зарежу!!!";
                Link.l2.go = "NoMoney";
            }
	break;
	case "NoMoney":
			dialog.text = "В таком случае разговор окончён!";
			ChangeCharacterReputation(pchar, -15);
			Link.l1 = "Похоже на то.";
			Link.l1.go = "battleTreasure";
		break;
	case "NoMoney_1":
			dialog.text = "Ну уж нет! Никуда ты с моим кладом не уйдёшь!";
			ChangeCharacterReputation(pchar, -15);
			Link.l1 = "В таком случае, пришло время отделиться твоей голове от тела.";
			Link.l1.go = "battleTreasure";
	break;
	case "Cost_Head2":
        AddMoneyToCharacter(pchar, -(sti(PChar.HunterCost)));
		PGG_AddMoneyToCharacter(npchar, (sti(PChar.HunterCost)));
		ChangeCharacterReputation(pchar, 15);
		PGG_ChangeRelation2MainCharacter(npchar, 40);
		chrDisableReloadToLocation = false;
        dialog.text = "А ты "+GetSexPhrase("неплохой малый","славная девчонка")+"! Благодарю за понимание. Надеюсь, мы ещё встретимся, я бы с тобой опрокинул"+ NPCharSexPhrase(NPChar,"","а") +" кружку-другую.";
		Link.l1 = "Заманчивое предложение. Если подвернётся случай - обязательно выпьем!";
		Link.l1.go = "Cost_Head3";
        break;
	case "Cost_Head3":
        AddDialogExitQuest("GoAway_PGGHunters_Land");
        DialogExit();
        break;

	case "Play_Game":
		bool allow = false;
		if (!CheckAttribute(pchar,"questTemp.pgggamesplayed"+npchar.index)) allow = true;
		if (GetQuestPastDayParam("questTemp.pgggamesplayed"+npchar.index) > 0) allow = true;
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) > 40 && allow)
		{
			DeleteAttribute(pchar,"questTemp.pgggamesplayed"+npchar.index);
			dialog.text = "Что предлагаешь?";
			link.l1 = "Перекинемся в карты?";
			link.l1.go = "Card_Game";
			link.l2 = "Погремим костями?";
			link.l2.go = "Dice_Game";
			link.l10 = "Прошу простить, но меня ждут дела.";
			link.l10.go = "exit";
		}
		else
		{
			dialog.text = LinkRandPhrase ("Может и хочу, но не с тобой", "Отвали, не до тебя сейчас!", "Знаешь что? " + LinkRandPhrase("Я уже всё проиграл"+ NPCharSexPhrase(NPChar,"","а") +".", "Ты уже всех обчистил"+GetSexPhrase("","а")+".", "Я сейчас не в том настроении, отвали."));
			link.l10 = "Как знаешь, дело твое.";
			link.l10.go = "exit";
		}
	break;
	// карты -->
	case "Card_Game":
		if (isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
		{
			dialog.text = "Кыш отсюда, я не в настроении.";
			link.l1 = "Как хочешь.";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "Ну давай, сыграем...";
			link.l1 = "Замечательно.";
			link.l1.go = "Cards_begin";
			link.l2 = "По каким правилам играем?";
			link.l2.go = "Cards_Rule";
		}
	break;

	case "Cards_Rule":
		dialog.text = CARDS_RULE;
		link.l1 = "Что ж, начнем!";
		link.l1.go = "Cards_begin";
		link.l3 = "Нет, это не для меня...";
		link.l3.go = "exit";
	break;

	case "Cards_begin":
		Dialog.text = "Давай определимся со ставкой.";
		link.l1 = "Играем по 500 монет.";
		link.l1.go = "Cards_Node_100";
		link.l2 = "Давай по 2000 золотых.";
		link.l2.go = "Cards_Node_500";
		link.l3 = "Пожалуй, мне пора.";
		link.l3.go = "exit";
	break;

	case "Cards_Node_100":
		if (sti(pchar.Money) < 15000)
		{
			dialog.text = "Шутить изволишь? У тебя нет денег!";
			link.l1 = "Бывает.";
			link.l1.go = "exit";
			break;
		}
		if (sti(npchar.Money) < 15000)
		{
			dialog.text = "Хватит с меня, а то на содержание корабля не останется...";
			link.l1 = "Жаль.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "Хорошо, играем по 500 монет.";
		link.l1 = "Начали!";
		link.l1.go = "Cards_begin_go";
		pchar.GenQuest.Cards.npcharIdx = npchar.index;
		pchar.GenQuest.Cards.iRate     = 500;
		pchar.GenQuest.Cards.SitType   = false;
	break;

	case "Cards_Node_500":
		if (sti(pchar.Money) < 60000)
		{
			dialog.text = "Шутить изволишь? У тебя нет денег на такие ставки!";
			link.l1 = "Будут!";
			link.l1.go = "exit";
			break;
		}
		if (sti(npchar.Money) < 60000)
		{
			dialog.text = "Нет, такие ставки не доведут до добра.";
			link.l1 = "Как угодно.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "Хорошо, играем по 2000 монет.";
		link.l1 = "Начали!";
		link.l1.go = "Cards_begin_go";
		pchar.GenQuest.Cards.npcharIdx = npchar.index;
		pchar.GenQuest.Cards.iRate     = 2000;
		pchar.GenQuest.Cards.SitType   = false;
	break;

	case "Cards_begin_go":
		SaveCurrentQuestDateParam("questTemp.pgggamesplayed"+npchar.index);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LaunchCardsGame();
	break;
	// карты <--
	//  Dice -->
	case "Dice_Game":
		if (isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
		{
			dialog.text = "Брысь отсюда, я не в настроении.";
			link.l1 = "Как вам будет угодно.";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "Давай! Отдых никогда не вредил здоровью... только кошельку...";
			link.l1 = "Замечательно.";
			link.l1.go = "Dice_begin";
			link.l2 = "По каким правилам игра?";
			link.l2.go = "Dice_Rule";
		}
	break;

	case "Dice_Rule":
		dialog.text = DICE_RULE;
		link.l1 = "Что ж, начнем!";
		link.l1.go = "Dice_begin";
		link.l3 = "Нет, это не для меня...";
		link.l3.go = "exit";
	break;

	case "Dice_begin":
		Dialog.text = "Давай определимся со ставкой.";
		link.l1 = "Играем по 200 монет за кубик.";
		link.l1.go = "Dice_Node_100";
		link.l2 = "Давай по 1000 золотых за кубик.";
		link.l2.go = "Dice_Node_500";
		link.l3 = "Пожалуй, мне пора.";
		link.l3.go = "exit";
	break;

	case "Dice_Node_100":
		if (!CheckDiceGameSmallRate())
		{
			dialog.text = "О тебе ходит слава непревзойденн"+ GetSexPhrase("ого шулера","ой каталы") +". Я не буду с тобой играть в кости вообще.";
			link.l1 = "Все врут! Ну и не нужно.";
			link.l1.go = "exit";
			break;
		}

		if (sti(pchar.Money) < 15000)
		{
			dialog.text = "Шутить изволишь? У тебя нет денег!";
			link.l1 = "Бывает.";
			link.l1.go = "exit";
			break;
		}
		if (sti(npchar.Money) < 15000)
		{
			dialog.text = "Все! Нужно завязывать с играми, а то запишут в растратчики и спишут на берег...";
			link.l1 = "Жаль.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "Хорошо, играем по 200 монет.";
		link.l1 = "Начали!";
		link.l1.go = "Dice_begin_go";
		pchar.GenQuest.Dice.npcharIdx = npchar.index;
		pchar.GenQuest.Dice.iRate     = 200;
		pchar.GenQuest.Dice.SitType   = false;
	break;

	case "Dice_Node_500":
		if (!CheckDiceGameSmallRate())
		{
			dialog.text = "О тебе ходит слава непревзойденн"+ GetSexPhrase("ого шулера","ой каталы") +". Я не буду с тобой играть в кости вообще.";
			link.l1 = "Все врут! Ну и не нужно.";
			link.l1.go = "exit";
			break;
		}
		if (!CheckDiceGameBigRate())
		{
			dialog.text = "Я слышал, что ты очень хорошо играешь. Я не буду играть с тобой по таким большим ставкам.";
			link.l1 = "Давай по более низким ставкам?";
			link.l1.go = "Dice_Node_100";
			link.l2 = "Прости, мне пора.";
			link.l2.go = "exit";
			break;
		}

		if (sti(pchar.Money) < 60000)
		{
			dialog.text = "Шутить изволишь? У тебя нет столько денег!";
			link.l1 = "Будут!";
			link.l1.go = "exit";
			break;
		}
		if (sti(npchar.Money) < 60000)
		{
			dialog.text = "Нет, такие ставки не доведут до добра.";
			link.l1 = "Как угодно.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "Хорошо, играем по 1000 монет за кубик.";
		link.l1 = "Начали!";
		link.l1.go = "Dice_begin_go";
		pchar.GenQuest.Dice.npcharIdx = npchar.index;
		pchar.GenQuest.Dice.iRate     = 1000;
		pchar.GenQuest.Dice.SitType   = false;
	break;

	case "Dice_begin_go":
		SaveCurrentQuestDateParam("questTemp.pgggamesplayed"+npchar.index);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LaunchDiceGame();
	break;

// Квест ПГГ Виспер
	case "Quest_Whisper":
		npchar.QuestWhisper = true;
		chrDisableReloadToLocation = true;

		Dialog.Text = "Дело серьёзное, я не стану обсуждать его при всех. Продолжим у меня в комнате?";
		link.l1 = "Ну пойдём.";
		link.l1.go = "Quest_Whisper_Room";
	break;

	case "Quest_Whisper_Room":
		DoReloadCharacterToLocation(npchar.PGGAi.location.town + "_tavern_upstairs","goto","goto1");
		ChangeCharacterAddressGroup(npchar, npchar.PGGAi.location.town + "_tavern_upstairs", "goto", "goto1");
		pchar.InstantDialog = npchar.id;

		npchar.Dialog.Filename = "Quest\WhisperLine\Whisper_PGG.c";
		npchar.dialog.currentnode   = "Quest_Whisper_1";
		DoQuestFunctionDelay("InstantDialog", 1.1);
		DialogExit();
	break;

	case "Quest_Whisper_1":
		dialog.text = "Итак, работа непростая, но куш, который мы сможем урвать, стоит риска.";
		link.l1 = "Я слушаю.";
		link.l1.go = "Quest_Whisper_2";
	break;

	case "Quest_Whisper_2":
		dialog.text = "Ты что, не запер"+ GetSexPhrase("","ла")+" за собой дверь?";
		link.l1 = "...";
		link.l1.go = "Quest_Whisper_2_exit";
		for (int i = 1; i < 4; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("PGG_Whisper_Incquisitor"+i, "PGG_Vincento_"+(2+i), "man", "man", MOD_SKILL_ENEMY_RATE/2, PIRATE, 1, false));
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1_back");
		}
	break;

	case "Quest_Whisper_2_exit":
		DialogExit();
		sld = CharacterFromId("PGG_Whisper_Incquisitor3");
		sld.Dialog.Filename = "Quest\WhisperLine\Whisper_PGG.c";
		sld.dialog.currentnode   = "Quest_Whisper_3";
		pchar.InstantDialog = sld.id;
		DoQuestFunctionDelay("InstantDialog", 0);
	break;
// <-- Квест ПГГ Виспер
	}
}
