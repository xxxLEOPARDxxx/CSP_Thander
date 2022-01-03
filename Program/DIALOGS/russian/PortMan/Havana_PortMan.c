// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), "Совсем недавно вы пытались задать мне вопрос " + GetAddress_Form(NPChar) + "...", "В течение этого дня вы уже третий раз говорите о каком-то вопросе...",
                          "Послушайте, если вы не по делам порта, то не стоит меня вопросами донимать.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал"+ GetSexPhrase("","а") +"...", "Сейчас мне не о чем говорить"), "Хм, что-то с памятью моей стало...",
                      "Да уж, действительно в третий раз...", "Извините, но портовые дела меня сейчас не интересуют.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatHavana")
            {
                link.l1 = "Здравствуйте. Я бы хотел"+ GetSexPhrase("","а") +" узнать, не останавливался ли в вашем порту корвет '" + pchar.questTemp.Slavetrader.ShipName + "', под командованием Франсуа Гонтьера?";
                link.l1.go = "Havana_ratP_1";
			}

		break;

		case "Havana_ratP_1":
			dialog.text = NPCStringReactionRepeat("Да, останавливался. Но уже ушел от нас. Спросите о нем нашего трактирщика, капитан корвета снимал у него комнату в таверне.", "Вы уже "+ GetSexPhrase("спрашивали","спрашивали") +" об этом, я вам ответил.", "Я же говорю вам, вы уже "+ GetSexPhrase("спрашивали","спрашивали") +" об этом Гонтьере.", "Я прошу не мешать мне работать!", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Спасибо! Так и поступлю.", "Хм, ну да...", "Да, точно, "+ GetSexPhrase("спрашивал","спрашивала") +"...", "Извините, " + npchar.name + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
