// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), "Совсем недавно вы пытались задать мне вопрос " + GetAddress_Form(NPChar) + "...", "В течение этого дня вы уже третий раз говорите о каком-то вопросе...",
                          "Послушайте, если вы не по делам порта, то не стоит меня вопросами донимать.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал"+ GetSexPhrase("","а") +"...", "Сейчас мне не о чем говорить"), "Хм, что-то с памятью моей стало...",
                      "Да уж, действительно в третий раз...", "Извините, но портовые дела меня сейчас не интересуют.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//ОЗГ, Крыса
			if(CheckAttribute(pchar, "questTemp.Headhunter"))
			{
    			if (pchar.questTemp.Headhunter == "Rat" && pchar.questTemp.Headhunter.countC == 0)
	    		{
		    		link.l1 = "Скажите, я слышал"+ GetSexPhrase("","а") +", не так давно, по выходу из вашего порта, пропало торговое судно. Вы можете рассказать мне об этом подробнее?";
			    	link.l1.go = "Rat_portmanC";
	    		}
			}
		break;

		//ОЗГ, Крыса
		case "Rat_portmanC":
			dialog.text = "А что там рассказывать. Загрузился в нашем магазине флейт 'Счастливая невеста' сандалом под завязку, вышел в море - а в порт назначения не пришел. Я таких историй за свою службу насмотрелся немало, и меня это не удивляет.";
			link.l1 = "Может, подскажете, какие корабли, кроме 'Счастливой невесты', покинули гавань в то же время?";
			link.l1.go = "Rat_portmanC_1";
		break;

		case "Rat_portmanC_1":
			dialog.text = "Подскажу, конечно. Сейчас, посмотрим записи... Галеон 'Сан-Хуан-Непомаседо' и пинас 'Аделаида'.";
			link.l1 = "Спасибо!";
			link.l1.go = "CheckC";
			pchar.questTemp.Headhunter.count = sti(pchar.questTemp.Headhunter.count) + 1;
			pchar.questTemp.Headhunter.countC = 1;
		break;

		case "CheckC":
			if(pchar.questTemp.Headhunter.count == 3)
			{
				pchar.questTemp.Headhunter = "Rat_Tavern";
				pchar.questTemp.Headhunter.Ratrumcity = npchar.city;
				AddQuestRecord("Headhunt", "13");
			}
			else
			{
				AddQuestRecord("Headhunt", "12_1");
			}
			DialogExit();
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}


