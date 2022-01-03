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
			if (pchar.questTemp.PDM_PK_UznatLichnost == "UznatLichnost")	// Квест "Потерянное кольцо"
            {
                link.l1 = "Расскажите мне о странной женщине, которая потеряла своё кольцо. Вы её знаете?";
                link.l1.go = "PDM_PK_UznatLichnost";
            }
		break;
//******************** квест "Потерянное кольцо" ******************
		case "PDM_PK_UznatLichnost":
			dialog.text = "Она потеряла не только кольцо. Ужасная история. У меня сердце разрывается, когда я её рассказываю. Её зовут Жозефина Лодет. Она подарила своему сыну великолепное кольцо в день накануне его первого путешествия. На счастье, сказала она. Он участвовал в нападении на Санто-Доминго и был убит в первой же схватке. Когда весть о его смерти достигла наших берегов, несчастная Жозефина... что ж, у вас есть глаза, так что вы видели, что с ней произошло.",
			link.l1 = "Что это было за кольцо?";
			link.l1.go = "PDM_PK_UznatLichnost_2";
        break;

		case "PDM_PK_UznatLichnost_2":
			dialog.text = "Очень красивое и очень дорогое украшение. Самый красивый сапфир из всех, которые я когда-либо видел, оправленный в золото. Её дедушка привёз его сюда из Европы. Я не ювелир, но его можно было оценить в десять... или в двадцать тысяч? Ах, ужасная история! Давайте поговорим о чём-нибудь другом. Или, может быть, хотите выпить?";
			Link.l1 = "Я лучше пойду, "+npchar.name+". Поговорим в другой раз.";
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

