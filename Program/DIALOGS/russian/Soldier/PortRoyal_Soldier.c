// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие имеете вопросы к солдату?", "У солдата жизнь расписана - караулы, разводы... Что вам угодно, " + GetAddress_Form(NPChar) + "?"), "Не пристало приставать к солдату с глупыми вопросами, " + GetAddress_Form(NPChar) + "...", "Третий раз за сегодня вы пытаетесь задать вопрос...",
                          "Солдатская доля и без того непроста, а тут еще и ты,"+ GetSexPhrase(" недоносок, "," ") +"выводишь из себя...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал"+ GetSexPhrase("","а") +"...", "Сейчас мне не о чем говорить"), "Не пристало...",
                      "Да уж, действительно в третий раз...", "Извиняюсь...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			/*sld = characterFromId("eng_guber");
			if (npchar.location == "PortRoyal_townhall" && pchar.questTemp.State == "" && CheckAttribute(sld, "notQuestLine"))
			{
                dialog.text = "Ключ! Дай мне ключ!!!";
				link.l1.edit = 7;
				link.l1 = "";
				link.l1.go = "ELOpenKey_1";
			}*/
		break;

		case "ELOpenKey_1":

			if (dialogEditStrings[7] == KEY_ENG_LINE)
			{
				dialog.text = "Ты знаешь, о чем речь, твой ключ принят. Я замолвлю за тебя словечко Мэдифорду...";
				Link.l1 = "Хорошо, дружище. Спасибо тебе...";
				Link.l1.go = "exit";
				sld = characterFromId("eng_guber");
				DeleteAttribute(sld, "notQuestLine");
			}
			else
			{
				dialog.text = "Ты не знаешь, о чем речь. Уходи, не мешай мне нести службу.";
				Link.l1 = "Хм, ну ладно...";
				Link.l1.go = "exit";
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

