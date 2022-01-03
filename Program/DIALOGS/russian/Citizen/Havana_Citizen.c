// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Какие вопросы?", "Что вам угодно?");
			link.l1 = RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить");
		    link.l1.go = "exit";
			if (pchar.questTemp.PDM_ONV_Detectiv_Jiteli_Havana == "Jiteli_Havana" && npchar.sex == "man")	// Квест "Охота на ведьму"
			{
				link.l1 = RandPhraseSimple("Извините, вы не видели Карлу?", "А вы не знаете, где Карла?");
				link.l1.go = "PDM_ONV_MAN";
			}
			if (pchar.questTemp.PDM_ONV_Detectiv_Jiteli_Havana == "Jiteli_Havana" && npchar.sex == "woman")	// Квест "Охота на ведьму"
			{
				link.l1 = RandPhraseSimple("Извините, вы не видели Карлу?", "А вы не знаете, где Карла?");
				link.l1.go = "PDM_ONV_WOMAN";
			}
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
			dialog.text = "Я вам что справочная? Не знаю. Ничего не ведаю.";

            link.l1 = "Вот бестолочь! Пока.";
			link.l1.go = "exit";
			link.l2 = "Тогда другой вопрос";
			link.l2.go = "new question";
		break;

//**************************Квест "Охота на ведьму"*******************************

		case "PDM_ONV_WOMAN":
			dialog.text = RandPhraseSimple("Не знаю я никакую Карлу.", "Какая ещё Карла?", "Не знаю, о ком вы.", "Кто, кто? Впервые слышу о такой девушке.", "Никогда у нас такой девушки не было.");
			link.l1 = "Извините.";
			link.l1.go = "exit";
		break;

		case "PDM_ONV_MAN":
				int Phrase;
                Phrase = rand(4);
                if (Phrase == 0)
                {
					dialog.text = "Извините, но я спешу.";
					link.l1 = "Извините.";
					link.l1.go = "exit";
				break;
				}
                if (Phrase == 1)
                {
					dialog.text = "Отстаньте от меня, сеньор"+ GetSexPhrase("","ита") +".";
					link.l1 = "Извините.";
					link.l1.go = "exit";
				break;
				}
				if (Phrase == 2)
                {
					dialog.text = "Иди своей дорогой, амиг"+ GetSexPhrase("о","а") +".";
					link.l1 = "Извините.";
					link.l1.go = "exit";
				break;
				}
				if (Phrase == 3)
                {
					dialog.text = "Не видишь, я занят?";
					link.l1 = "Извините.";
					link.l1.go = "exit";
				break;
				}
				if (Phrase == 4)
                {
					dialog.text = "Говорю вам, сеньор"+ GetSexPhrase("","ита") +" - эта ведьма Карла околдовала всех в этом городе! Все добропорядочные люди должны пойти прямиком к губернатору и заявить ему, что она злая ведьма, и её следует сжечь на медленном огне!";
					link.l1 = "Карла? Что вы о ней знаете?";
					link.l1.go = "PDM_ONV_MAN_2";
				break;
				}
		break;

		case "PDM_ONV_MAN_2":
			dialog.text = "Я? Я знаю, что она источник смертного греха для любого мужчины в этом городе! Мы должны положить конец этому разврату!");
			link.l1 = "Так. Значит вы единственный мужчина в городе, который не пользуется услугами Карлы? Ой, бедняга! Теперь понятно, почему у вас отсутствует чувство юмора. Ха-ха. Но я вынужден"+ GetSexPhrase("","а") +" прервать нашу беседу - до свидания.";
			link.l1.go = "exit";
			link.l2 = "Дон Франсиско приказал мне схватить эту ведьму - он хочет лично допросить её. Вы знаете, где я могу её найти?";
			link.l2.go = "PDM_ONV_MAN_3";
		break;

		case "PDM_ONV_MAN_3":
			dialog.text = "Она обычно приводит своих жертв в таверну. Бог да благословит вас, "+ GetSexPhrase("сын мой","дочь моя") +"! Ступайте туда и вытащите эту змею из её гнезда! Вы "+ GetSexPhrase("смелый человек, сеньор","смелая, сеньорита") +". То, что эта ведьма разгуливает тут и делает всё, что ей захочется - это позор для нашего города!");
			link.l1 = "Мы займёмся этой ведьмой, не сомневайтесь.";
			link.l1.go = "exit";
			AddQuestRecord("PDM_Ohota_na_vedmu", "7");
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","а"));
			DeleteAttribute(pchar, "questTemp.PDM_ONV_Detectiv_Jiteli_Havana");
			pchar.questTemp.PDM_ONV_Detectiv_Tavern_1 = "Tevern_Da";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

