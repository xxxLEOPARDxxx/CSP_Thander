// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool bOk;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Спрашивай, чего ты хочешь?",
                          "Мы только что поднимали это тему. Вы, вероятно, запамятовали...", "Сегодня вы уже третий раз говорите о каком-то вопросе...",
                          "Послушай, это магазин, здесь люди покупают что-то. Не отвлекай меня!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Знаешь, " + NPChar.name + ", как-нибудь в следующий раз.", "Точно, "+ GetSexPhrase("забыл","забыла") +" что-то...",
                      "Да уж, действительно в третий раз...", "Гм, не буду...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.BlueBird == "toBermudes")
			{
				link.l1 = "Уважаемый, я ищу один необычный корабль, шебеку 'Синяя Птица'. Ничего о ней не слышали? За любую информацию о ней я "+ GetSexPhrase("готов","готова") +" заплатить...";
				link.l1.go = "BlueBird_1";
			}
			if(CheckAttribute(pchar, "questTemp.Headhunter"))
			{
				bOk = pchar.questTemp.Headhunter == "end_quest_full" || pchar.questTemp.BlueBird == "weWon" || pchar.questTemp.BlueBird == "returnMoney" || pchar.questTemp.BlueBird == "over";
	    		if (bOk && !CheckAttribute(pchar,"questTemp.BlueBird.speakWon"))
    			{
		    		link.l1 = "А где Паскаль Вуазье?";
	    			link.l1.go = "BlueBird_3";
    			}
			}
			if(!CheckAttribute(pchar, "questTemp.Headhunter"))
			{
				bOk = pchar.questTemp.BlueBird == "weWon" || pchar.questTemp.BlueBird == "returnMoney" || pchar.questTemp.BlueBird == "over";
	    		if (bOk && !CheckAttribute(pchar,"questTemp.BlueBird.speakWon"))
    			{
		    		link.l1 = "А где Паскаль Вуазье?";
	    			link.l1.go = "BlueBird_3";
    			}
			}
			if (bBettaTestMode)
			{
				link.l5 = "АРЕНДА СКЛАДА";
				link.l5.go = "storage_rent1";
			}
		break;
		case "BlueBird_1":
			dialog.text = NPCStringReactionRepeat("Я ничего не знаю об этом корабле. Если это все, что вы хотели, то уходите.",
				"Опять? Я все вам сказал.",
				"Что, снова про то же?",
                "Да когда же это кончится?! Прошу вас, не отвлекайте меня от работы!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Что-то не очень вы любезны, милейший!",
				"Да-да, я помню...",
                "Ага.",
				"Хорошо, хорошо...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("BlueBird_2", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
		break;
		case "BlueBird_2":
			dialog.text = "Я вам не милейший, ром хлестать и под забором с вами валяться не имел удовольствия.";
			link.l1 = "О как! Да я просто "+ GetSexPhrase("спросил","спросила") +". Ну ладно, спасибо и на этом...";
			link.l1.go = "exit";
			AddQuestRecord("Xebeca_BlueBird", "2");
			AddQuestUserData("Xebeca_BlueBird", "sSex", GetSexPhrase("ся","ась"));
		break;

		case "BlueBird_3":
			if ( sti(pchar.Ship.Type) == SHIP_NOTUSED || pchar.location.from_sea != "Pirates_town")
			{
				dialog.text = "Он уплыл с острова без объяснения причин. Поговаривают, что он был замешан в истории с шебекой 'Синяя Птица'.";
				link.l1 = "Я знаю об этой истории.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Он уплыл с острова без объяснения причин. Поговаривают, что он был замешан в истории с шебекой 'Синяя Птица'. У меня к вам есть одно заманчивое предложение. Возможно, оно вас заинтересует.";
				link.l1 = "Вот как? Ну что ж, излагайте ваше заманчивое предложение.";
				link.l1.go = "storage_rent";
			}
			pchar.questTemp.BlueBird.speakWon = true;
		break;

		case "storage_rent":
			dialog.text = "После известных событий у нас освободились площади, пригодные под склад. Не хотите арендовать за умеренную плату? Обзаведётесь собственным складиком...";
			link.l1 = "Складиком, говорите? Заманчиво... А большой он? и сколько попросите за аренду?";
			link.l1.go = "storage_rent1";
		break;

		case "storage_rent1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
			dialog.text = "Он достаточно просторный даже для припортового пакгауза - вместимость 50000 ц. За " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + " в месяц я готов обеспечить сохранность ваших запасов. "+
				"Это включает услуги по охране, защиту от подтопления и борьбу с грызунами. Ну как, годится?.. Ну, и конфиденциальность, понятное дело, гарантирую.";
			link.l1 = "Годится. Могу я его осмотреть?";
			link.l1.go = "storage_rent2";
			link.l2 = "Слишком дорого просите. Там, небось, воды по колено и крысы вовсю шуруют.";
			link.l2.go = "storage_rent3";
		break;

		case "storage_rent2":
			dialog.text = "Конечно-конечно. Только эм-м... оплату за месяц попрошу вперёд.";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "Экий вы... меркантильный. Держите свои деньги - я арендую этот сарай.";
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = "Экий вы... меркантильный. Сейчас деньги принесу.";
				link.l1.go = "exit";
			}
		break;

		case "storage_rent3":
			dialog.text = "Ну, как знаете. Если надумаете - обращайтесь. Только учтите, что такое сокровище долго пустовать не будет. Как бы не опоздали.";
			link.l1 = "Не волнуйтесь. Если понадобится - спрошу.";
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

