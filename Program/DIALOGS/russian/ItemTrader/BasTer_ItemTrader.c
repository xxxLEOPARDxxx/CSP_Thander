// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), "Опять вопросы, " + GetAddress_Form(NPChar) + "...", "Вопросы, вопросы... Может торговлей займемся, " + GetAddress_Form(NPChar) + "?",
                          "Послушайте, ну сколько можно пустые разговоры вести?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Нет вопросов...", "Сейчас мне не о чем говорить"), "Эх, опять...",
                      "Да, действительно лучше торговаться...", "Хм, извини, торговец...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.PDM_PK_UznatLichnost == "UznatLichnost")	// Квест "Потерянное кольцо"
            {
                link.l1 = "Расскажите мне о странной женщине, которая потеряла своё кольцо. Вы её знаете?";
                link.l1.go = "PDM_PK_UznatLichnost";
            }
		break;

//**************************Квест "Потерянное кольцо"*******************************
		case "PDM_PK_UznatLichnost":
			int Phrase;
                Phrase = rand(4);
                if (Phrase == 0)
                {
					dialog.text = "Она просто ненормальная, не обращайте на неё внимания.";
					link.l1 = "Ладно.";
					link.l1.go = "exit";
				break;
				}
                if (Phrase == 1)
                {
					dialog.text = "И зачем вам сдалась эта безумная женщина? Лучше купите у меня что-нибудь.";
					link.l1 = "Извините.";
					link.l1.go = "exit";
				break;
				}
				if (Phrase == 2)
                {
					dialog.text = "Я "+ GetSexPhrase("продавец","продавщица") +", а не поставщик слухов.";
					link.l1 = "Извините.";
					link.l1.go = "exit";
				break;
				}
				if (Phrase == 3)
                {
					dialog.text = "Я не знаю её, извините.";
					link.l1 = "Ладно, спрошу кого-нибудь другого.";
					link.l1.go = "exit";
				break;
				}
				if (Phrase == 4)
                {
					dialog.text = "Она потеряла не только кольцо. Ужасная история. У меня сердце разрывается, когда я её рассказываю. Её зовут Жозефина Лодет. Она подарила своему сыну великолепное кольцо в день накануне его первого путешествия. На счастье, сказала она. Он участвовал в нападении на Санто-Доминго и был убит в первой же схватке. Когда весть о его смерти достигла наших берегов, несчастная Жозефина... что ж, у вас есть глаза, так что вы видели, что с ней произошло.";
					link.l1 = "Что это было за кольцо?";
					link.l1.go = "PDM_PK_UznatLichnost_2";
				break;
				}
        break;

		case "PDM_PK_UznatLichnost_2":
			dialog.text = "Очень красивое и очень дорогое украшение. Самый красивый сапфир из всех, которые я когда-либо видел"+ NPCharSexPhrase(NPChar,"","а") +", оправленный в золото. Её дедушка привёз его сюда из Европы. Я не ювелир, но его можно было оценить в десять... или в двадцать тысяч? Ах, ужасная история! Ладно, удачи вам!";
			Link.l1 = "Спасибо вам, "+npchar.name+". Вы мне очень помогли. До свидания.";
			Link.l1.go = "exit";

			sld = CharacterFromID("Josephine_Lodet")
			sld.name = "Жозефина";
			sld.lastname = "Лодет";

			AddQuestRecord("PDM_Poteryanoe_Koltso", "2");
			AddQuestUserData("PDM_Poteryanoe_Koltso", "sSex", GetSexPhrase("","а"));

			pchar.questTemp.PDM_PK_IshemKoltso = "IshemKoltso";
			DeleteAttribute(pchar, "questTemp.PDM_PK_UznatLichnost");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

