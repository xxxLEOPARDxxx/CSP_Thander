// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Все сплетни города "+ GetCityName(npchar.city) +" к вашим услугам. Что бы вы хотели узнать?",
                          "Мы только что поднимали это тему. Вы, вероятно, запамятовали...", "Сегодня вы уже третий раз говорите о каком-то вопросе...",
                          "Что ты "+ GetSexPhrase("заладил","заладила") +" как попугай одно и то же...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Знаешь, " + NPChar.name + ", как-нибудь в следующий раз.", "Точно, "+ GetSexPhrase("забыл","забыла") +" что-то...",
                      "Да уж, действительно в третий раз...", "Да уж...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
            // ==> проверка на квесты
			if (CheckAttribute(pchar, "questTemp.State.Store"))
            {
                link.l1 = "Послушай, тебе ничего не известно о голландском торговце по имени Яков Лопез де Фонсека?";
                link.l1.go = "Step_S2_1";
            }
			if (pchar.questTemp.Slavetrader == "FindRatPanama")
            {
                link.l1 = "Послушай, говорят, у вас в городе был капер - Франсуа Гонтьер. Не знаешь, где мне его можно найти?";
                link.l1.go = "Panama_rat_1";
            }
            // <== проверка на квесты
		break;
//*************************** Квест №2 испанки, задание Инквизиции ***************************
 		case "Step_S2_1":
			dialog.text = NPCStringReactionRepeat("Нет, не видел здесь такого и не слышал о нем.", "Ты уже "+ GetSexPhrase("спрашивал","спрашивала") +" об этом, я тебе ответил.", "Я же говорю тебе, ты уже "+ GetSexPhrase("спрашивал","спрашивала") +" об этом Якове.", "Послушай, отойди и не мешай! Совсем что ли крыша поехала?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ну что же, спасибо тебе.", "Хм, ну да...", "Да, точно, "+ GetSexPhrase("спрашивал","спрашивала") +"...", "Извини, " + npchar.name + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		//-->работорговец
		case "Panama_rat_1":
			dialog.text = NPCStringReactionRepeat("Да, был у нас в городе этот тип. Все по темным углам прятался... Потом к нему приехали какие-то дружки - на вид - форменные головорезы, и он с ушел из города.", "Ты уже "+ GetSexPhrase("спрашивал","спрашивала") +" об этом, я тебе ответил.", "Я же говорю тебе, ты уже "+ GetSexPhrase("спрашивал","спрашивала") +" об этом Гонтьере.", "Послушай, отойди и не мешай! Совсем что ли крыша поехала?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("А куда ушел, не знаешь?", "Хм, ну да...", "Да, точно, "+ GetSexPhrase("спрашивал","спрашивала") +"...", "Извини, " + npchar.name + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "Panama_rat_2";
		break;

		case "Panama_rat_2":
			dialog.text = "Ну, пешком отсюда только одна дорога - в Порто Белло. А он пешком и пошел. Так что ищи его там.";
			link.l1 = "Спасибо, ты мне здорово помог!";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatPortobello";
			AddQuestRecord("Slavetrader", "21_1");
		break;
		//<--работорговец


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

