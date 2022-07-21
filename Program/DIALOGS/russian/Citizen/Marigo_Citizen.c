// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Какие вопросы?", "Что вам угодно?");
			link.l1 = RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить");
		    link.l1.go = "exit";
		break;

		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Я что, работаю на тайную агентурную сеть для "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Ну ладно... тогда пока.";
			link.l1.go = "exit";
			link.l2 = "Тогда другой вопрос";
			link.l2.go = "new question";
		break;

		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Что вас интересует?";

            link.l1 = "Где находится аптека?";
			link.l1.go = "Apteka";
			link.l2 = "Где находится Голландская Вест-Индская компания?";
			link.l2.go = "GVIK";
			link.l3 = "У меня другой вопрос.";
			link.l3.go = "new question";
		break;
		
		case "Apteka":
			dialog.text = "Аптека находится рядом с набережной по соседству с таверной и церковью. Здание окрашено в сине-белые цвета. Парадный вход закрыт, поэтому лучше заходить с правой стороны. Подойдя к арке, сразу заходите внутрь двора, и поворачиваете налево, к синей двери. Надеюсь, это информация была вам полезна.";
            link.l1 = "Как же ты меня выручил"+ NPCharSexPhrase(NPChar,"","а") +", благодарю!";
			link.l1.go = "exit";
			link.l2 = "Я ещё вот что хотел спросить.";
			link.l2.go = "new question";
		break;
		
		case "GVIK":
			dialog.text = "Голландская Вест-Индская компания расположена в большом административном здании, которое окрашено в жёлтый цвет. На одной из башен висят огромные красивые часы. При входе имеется хорошо вооружённая охрана. Надеюсь, это информация была вам полезна.";
            link.l1 = "Как же ты меня выручил"+ NPCharSexPhrase(NPChar,"","а") +", благодарю!";
			link.l1.go = "exit";
			link.l2 = "Я ещё вот что хотел спросить.";
			link.l2.go = "new question";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

