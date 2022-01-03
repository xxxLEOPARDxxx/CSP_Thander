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
			if (pchar.questTemp.PDM_ONV_Detectiv_Jiteli_Havana == "Jiteli_Havana")	// Квест "Охота на ведьму"
            {
    			link.l1 = RandPhraseSimple("Извините, вы не видели Карлу?", "А вы не знаете, где Карла?");
    			link.l1.go = "PDM_ONV_Prodavec";
			}
		break;

//**************************Квест "Охота на ведьму"*******************************
		case "PDM_ONV_Prodavec":
			dialog.text = dialog.text = RandPhraseSimple("Я "+ GetSexPhrase("продавец","продавщица") +", а не поставщик слухов.", "Вы покупать будете или только языком молоть?", "Карла? Нет, я продаю фрукты. Купите лимон, а лучше два.");
			link.l1 = "Извините.";
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
