// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы, "+ GetSexPhrase("сын мой","дочь моя") +"?", "Спрашивай, я слушаю тебя..."), "Я слушаю тебя, говори, "+ GetSexPhrase("сын мой","дочь моя") +"...", "И в третий раз говорю тебе, "+ GetSexPhrase("сын мой","дочь моя") +" мой: задавай свой вопрос.",
                          "Столько обязанностей у церковнослужителя, а тут еще и ты донимаешь, "+ GetSexPhrase("сын мой","дочь моя") +" мой...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Не сейчас, падре..."), "Да, пока особо и нечего сказать...",
                      "Задам, задам... Только позже...", "Простите, святой отец...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.State == "Inquisition_toDeSouza")
            {
                link.l1 = "Отец, скажите, где я могу найти сеньора Антонио де Соуза?";
                link.l1.go = "Step_S2_1";
            }
			if (pchar.questTemp.State == "Fr7RockBras_toSeekPlace")
            {
                link.l1 = "Отец, скажите, где здесь у вас находится Инквизиция?";
                link.l1.go = "Step_F7_1";
            }
		break;
        case "Step_S2_1":
			dialog.text = NPCStringReactionRepeat("А ты знаешь, "+ GetSexPhrase("сын мой","дочь моя") +", кто это?", ""+ GetSexPhrase("Сын мой","Дочь моя") +", я тебе уже все сказал.", "Ты опять с тем же вопросом? Я же уже ответил тебе...", "Опять? Ладно, вход в Инквизицию находится прямо лестницей, ведущий в церковь...",  "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Конечно, он высокопоставленный инквизитор.", "Простите, падре, я не очень "+ GetSexPhrase("понял","поняла") +"... Ну ладно...", "Да, но я не "+ GetSexPhrase("понял","поняла") +"... Хм, простите, падре...", "Уф, спасибо, падре...", npchar, Dialog.CurrentNode);
			link.l1.go = "Step_S2_2";
		break;
        case "Step_S2_2":
			dialog.text = "Верно... Ну что же, он находится у себя в резиденции.";
			link.l1 = "Простите, падре, а где она, резиденция Инквизиции?";
			link.l1.go = "Step_S2_3";
		break;
        case "Step_S2_3":
			dialog.text = "Прямо под церковью.";
			link.l1 = "Как это?..";
			link.l1.go = "Step_S2_4";
		break;
        case "Step_S2_4":
			dialog.text = "Вот так... Иди, "+ GetSexPhrase("сын мой","дочь моя") +", иди. По доброй воле в Святую Инквизицию мало кто ходит...";
			link.l1 = "А-а-а, ну ладно...";
			link.l1.go = "exit";
		break;

        case "Step_F7_1":
			dialog.text = NPCStringReactionRepeat("Прямо под церковью, "+ GetSexPhrase("сын мой","дочь моя") +".", "Прямо под нашей церковью, "+ GetSexPhrase("сын мой","дочь моя") +". Вход находится под лестницей.", "Ты совсем "+ GetSexPhrase("тугой на слух, сын мой","туга на слух, дочь моя") +". Ох, лечиться тебе надобно...",
                          "Смирение...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Спасибо, падре.", "Спасибо еще раз, падре.",
                      "Обязательно!", "Ась?", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

