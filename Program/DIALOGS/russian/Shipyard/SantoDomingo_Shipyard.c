// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно?"), "Совсем недавно вы пытались задать мне вопрос...", "У себя на верфи, а и вообще в городе, я таких однообразно любознательных не видал.",
                          "Ну что за вопросы? Мое дело - корабли строить, давайте этим и займемся.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить"), "Хм, что-то с памятью моей стало...",
                      "Хм, однако...", "Давайте...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.piratesLine == "Soukins_toSantoDomingo")
			{
				link.l1 = "Мне сказали, что у тебя продается шхуна 'Ласточка', это так?";
				link.l1.go = "PL_Q7_1";
			}
		break;
		//пиратка, квест №7
		case "PL_Q7_1":
			dialog.text = "Нет, не так. Не продается, а уже продана. Пришел покупатель и так он мне понравился, что отдал я ему эту шхуну буквально за гроши...";
			link.l1 = "Меня интересует не покупатель, а продавец. Кто продал тебе шхуну?";
			link.l1.go = "PL_Q7_2";
		break;
		case "PL_Q7_2":
			dialog.text = "Продал? Продал... Человек какой-то продал...";
			link.l1 = "Да я понимаю, что не лошадь. Кто этот человек, как его зовут?";
			link.l1.go = "PL_Q7_3";
		break;
		case "PL_Q7_3":
			dialog.text = "Как зовут - не знаю, я больше на корабль смотрел...";
			link.l1 = "Не темни, приятель, для тебя это может плохо кончиться.";
			link.l1.go = "PL_Q7_4";
		break;
		case "PL_Q7_4":
			dialog.text = "Черт! Я так и знал, что эта покупка может выйти мне боком. Но уж очень хорошая цена была предложена... Я сразу заподозрил, что здесь что-то нечисто, но понадеялся, что ошибаюсь.";
			link.l1 = "Скорей всего, не ошибаешься. Где мне найти продавца?";
			link.l1.go = "PL_Q7_5";
		break;
		case "PL_Q7_5":
			dialog.text = "В море. Вчера он вышел в море на фрегате 'Леон', насколько мне известно. Сам-то я фрегата не видел. Этот тип был очень острожен, но его видел один из моих рабочих и рассказал мне.\nИщи его где-то у берегов Эспаньолы. Не думаю, что он успел далеко уйти.";
			link.l1 = "Спасибо. Будем искать.";
			link.l1.go = "exit";
			pchar.questTemp.piratesLine = "Soukins_seekLeon";
			AddQuestRecord("Pir_Line_7_Soukins", "6");
			AddDialogExitQuestFunction("PQ7_LoginLeon");
			QuestSetCurrentNode("Henry Morgan", "PL_Q7_LeonNotFound"); //нода, ничего не узнал
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

