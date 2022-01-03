// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), "Совсем недавно вы пытались задать мне вопрос, " + GetAddress_Form(NPChar) + "...", "В течение этого дня вы уже третий раз говорите о каком-то вопросе...",
                          "Опять вопросы будем задавать?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить"), "Хм, что-то с памятью моей стало...",
                      "Да уж, действительно в третий раз...", "Да нет, какие вопросы...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.piratesLine == "Soukins_toPuertoPrincipe")
			{
				link.l1 = "Ходят слухи, что Соукинс собирает людей для какого-то дела. Ты не в курсе?";
				link.l1.go = "PL_Q7_1";
			}
			if (CheckAttribute(pchar, "questTemp.PDM_Novaya_Rodina.IshemHugo"))
			{
				link.l2 = "Ты не видел здесь Хьюго Лесопилку?";
				link.l2.go = "PDM_Gde_Lesopilka";
			}
		break;
		//пиратка, квест №7, попытка узнать о планах Соукинса
		case "PL_Q7_1":
			dialog.text = NPCStringReactionRepeat("Да, что-то назревает. Наверное, опять Ричард собрался пощипать испанцев.",
				"Мы уже говорили на эту тему.",
				"Опять ты об планах Ричарда?",
                "Никакого нового совета я тебе не дам.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Понятно... А когда и где не знаешь?",
				"Да, верно.",
                "Ага, опять...",
				"Хм, спасибо и на этом...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("PL_Q7_2", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "PL_Q7_2":
			dialog.text = "Ха, ну ты даешь! Ричард таких вещей никогда не открывает, до самого последнего момента, даже для своих капитанов. А ты меня спрашиваешь...";
			link.l1 = "Ну мало ли. Спрашиваю, потому что сомневаюсь, стоит ли мне подряжаться на это дело. Как думаешь?";
			link.l1.go = "PL_Q7_3";
		break;
		case "PL_Q7_3":
			dialog.text = "Не знаю, "+ GetSexPhrase("сам","сама") +" решай. У Соукинса репутация удачливого кэпа. Но лично я бы пошел с ним, уж больно Ричард готовится к этому тщательно - целыми днями сидит в резиденции и строчит в своем журнале чего-то...";
			link.l1 = "Хе, понятно... Ну что же, спасибо тебе за совет.";
			link.l1.go = "exit";
		break;
		//Квест "Новая Родина", Ищем Лесопилку
		case "PDM_Gde_Lesopilka":
			dialog.text = "Он был здесь, за ним пришли английские охотники за головами, он вовремя ускользнул через чёрный ход.";
			link.l1 = "Ну, и? Куда он направился?";
			link.l1.go = "PDM_Gde_Lesopilka_2";
		break;

		case "PDM_Gde_Lesopilka_2":
			dialog.text = "Ммм... За 1000 золотых я вам подскажу дорогу.";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "Вот, держи свои деньги. Так куда он направился?";
				link.l1.go = "PDM_Gde_Lesopilka_3";
				link.l2 = "У меня щас нет столько денег.";
				link.l2.go = "exit";
			}
			else
			{
				link.l1 = "У меня щас нет столько денег.";
				link.l1.go = "exit";
			}
		break;

		case "PDM_Gde_Lesopilka_3":
			DeleteAttribute(pchar, "questTemp.PDM_Novaya_Rodina.IshemHugo");
			dialog.text = "Он взял курс на Ла Вегу, ищи его там.";
			link.l1 = "Спасибо, до встречи.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000);
			sld = CharacterFromID("Hugo_Lesopilka")
			ChangeCharacterAddressGroup(sld,"LaVega_Tavern","sit","sit10");
			AddQuestRecord("PDM_Novaya_Rodina", "3");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

