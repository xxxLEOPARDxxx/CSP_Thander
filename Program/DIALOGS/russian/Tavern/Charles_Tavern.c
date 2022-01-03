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
			if (pchar.questTemp.MC == "toSeekSister")
			{
				link.l1 = "Дружище, я ищу юную леди по имени Элизабет Шеппард. Ты о такой не слышал?";
				link.l1.go = "MCLiz";
			}
		break;
		case "MCLiz":
			dialog.text = "Мисс Лиз Шеппард - жительница нашего города. А что вам нужно от нее?";
			link.l1 = "Понимаешь, она кое-что забыла в заливе Маракайбо...";
			link.l1.go = "MCLiz_1";
		break;
		case "MCLiz_1":
			dialog.text = "Да, Лиз в последнее время что-то часто стала путешествовать. В городе ее и не застать.";
			link.l1 = "А сейчас она где?";
			link.l1.go = "MCLiz_2";
		break;
		case "MCLiz_2":
			dialog.text = "Сейчас у себя в доме.";
			link.l1 = "У нее собственный дом?";
			link.l1.go = "MCLiz_3";
		break;
		case "MCLiz_3":
			dialog.text = "Да, дом ее отца.";
			link.l1 = "А кто ее отец?";
			link.l1.go = "MCLiz_4";
		break;
		case "MCLiz_4":
			dialog.text = "Ну, об этом особо распространяться не принято, но вам я расскажу.\n"+
				"Слышали вы о капитане Стейтоне? Нет? Хо-хо, тогда знайте, что капитан Стейтон, один из первых флибустьеров, и есть отец Лиз. В свое время, когда он был еще жив, капитан много сделал для развития города, так что жители Невиса ему обязаны.";
			link.l1 = "Элизабет имеет фамилию Шеппард.";
			link.l1.go = "MCLiz_5";
		break;
		case "MCLiz_5":
			dialog.text = "Это капитан так решил. Когда он поселился с семьей в городе, то взял другую фамилию. Так, на всякий случай...";
			link.l1 = "И Лиз теперь живет одна?";
			link.l1.go = "MCLiz_6";
		break;
		case "MCLiz_6":
			dialog.text = "Да, ее мать ненадолго пережила супруга и похоронена здесь же, на острове. А Даниэль не появлялась дома уже года два.";
			link.l1 = "Даниэль?";
			link.l1.go = "MCLiz_7";
		break;
		case "MCLiz_7":
			dialog.text = "Старшая сестра Лиз.";
			link.l1 = "Понятно. Ну что же, спасибо тебе, приятель.";
			link.l1.go = "MCLiz_8";
		break;
		case "MCLiz_8":
			dialog.text = "Не за что. Надеюсь, вы принесли Лиз хорошие новости. Она хорошая девушка, капитан...";
			link.l1 = "Во всяком случае, ничего плохого. Это уж точно.";
			link.l1.go = "exit";
			pchar.questTemp.MC = "toSeekSisterAT";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

