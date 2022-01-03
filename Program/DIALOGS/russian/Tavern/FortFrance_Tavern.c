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
			if (pchar.questTemp.piratesLine == "BlackLabel_toLaVega")
			{
				link.l1 = "Приятель, ты не в курсе, в вашем городе проживает некий Эдвард Лоу?";
				link.l1.go = "PL_Q2_1";
			}
			if (CheckAttribute(pchar, "questTemp.PDM_PJ_KV"))	//Квест ***Проклятая жара***		(Вино)
			{
				link.l1 = "Я как раз вспоминал"+ GetSexPhrase("","а") +", что меня просили купить бутылку вина.";
				link.l1.go = "PDM_PJ_1";
			}
			if (CheckAttribute(pchar, "questTemp.PDM_PJ_KR"))	//Квест ***Проклятая жара***		(Ром)
			{
				link.l1 = "Мне нужно купить немного рома.";
				link.l1.go = "PDM_PJ_Rom_1";
			}
		break;
		case "PL_Q2_1":
			dialog.text = NPCStringReactionRepeat("Нет, впервые слышу. У нас в городе такого нет.",
				"Ты уже "+ GetSexPhrase("спрашивал","спрашивала") +" об нем, нет кого у нас.",
				"Я уже отвечал, что Эдварда Лоу у нас нет в городе.",
                "Утомил...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Понятно... Спасибо тебе.",
				"Да-да, я "+ GetSexPhrase("понял","поняла") +"...",
                "Понял...",
				"...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;

		case "PDM_PJ_1":
			dialog.text = "Так это же не проблема, "+ GetSexPhrase("месье","мадмуазэль") +"! Хе-хе-хе-хе! Вы пришли как раз куда надо, и говорите как раз с тем, кто вам нужен! Хотите бутылочку вина? Можете купить бочку! Лучшее вино на всем архипелаге!",
			link.l1 = "Что ж, это просто замечательно, но мне нужна всего одна бутылка. Сколько вы за неё хотите?",
			link.l1.go = "PDM_PJ_2";
		break;

		case "PDM_PJ_2":
			dialog.text = "Ой, "+ GetSexPhrase("месье","мадмуазэль") +", уверен, что вы почувствуете истинную ценность этого божественного нектара! Вы получите бутылку моего прекрасного старого вина всего за пять золотых монет!",
			MakeRandomLinkOrderThree(link,
			"Я возьму вино, "+npchar.name+". Но с такими ценами у тебя вряд ли появится много покупателей.",
			"PDM_PJ_Beru_1",

			"Но это же глупо! За такую цену я могу купить великолепного бургундского из Франции! Ты пытаешься надуть меня, негодяй!",
			"PDM_PJ_Beru_2",

			"Забудьте об этом. Стражник обойдётся без своей бутылки вина.",
			"exit");
		break;

		case "PDM_PJ_Beru_1":
			dialog.text = "Вот ваша бутылка... Благородное вино для благородного человека, хе-хе-хе. Вы не будете разочарованы, "+ GetSexPhrase("месье","мадмуазэль") +". Хотите что-нибудь ещё?",
			link.l1 = "Нет, не хочу. И надеюсь, что такой фонтан остроумия, как вы, сможет оценить иронию происходящего - я покупаю эту бутылку изысканного дорогого вина для простого французского солдата. Прощайте, "+npchar.name+".",
			link.l1.go = "PDM_PJ_Beru_3";
		break;

		case "PDM_PJ_Beru_2":
			dialog.text = "Надуть? Хе-хе-хе, "+ GetSexPhrase("месье","мадмуазэль") +", вы, конечно, шутите. Да, во Франции вы можете купить бутылку бургундского за пять золотых. Но Мартиника ведь находится не во Франции, верно? Хе-хе-хе!",
			link.l1 = "Дайте мне это проклятое вино, и во имя Господа, прекратите это хихиканье!",
			link.l1.go = "PDM_PJ_Beru_3";
		break;

		case "PDM_PJ_Beru_3":
			DialogExit();

			AddQuestRecord("PDM_Proklyataya_Jara", "2");
			GiveItem2Character(PChar, "PDM_PJ_Vino");
			AddMoneyToCharacter(pchar, -5);
			DeleteAttribute(pchar, "questTemp.PDM_PJ_KV");
			sld = CharacterFromID("PDM_PJ_Strajnik_1")
			sld.Dialog.Filename = "Quest/PDM/Proklyataya_Jara.c";
			sld.dialog.currentnode = "Prines_Vino_1";
		break;

		case "PDM_PJ_Rom_1":
			dialog.text = "Гораздо проще иметь дело с вином, что да, то да, "+ GetSexPhrase("месье","мадмуазэль") +"! Ром самый дешёвый напиток, какой вы можете купить в архипелаге, но, "+ GetSexPhrase("месье","мадмуазэль") +", я никогда не продаю количество рома объёмом меньше бочки! Хе-хе-хе! Никто не разливает ром по бутылкам! Хе-хе-хе!",
			link.l1 = "Да, ладно, "+npchar.name+"! Моряки постоянно пьют ром в твоей таверне и не покупают его бочками...",
			link.l1.go = "PDM_PJ_Rom_2";
		break;

		case "PDM_PJ_Rom_2":
			dialog.text = "Ой, "+ GetSexPhrase("месье","мадмуазэль") +", вы "+ GetSexPhrase("такой проницательный","такая проницательная") +", что есть, то есть. Только... они пьют ром из кружек, а я наполняю кружки из бочки. Конечно, я могу продать вам кружку рома... Но, "+ GetSexPhrase("месье","мадмуазэль") +", вы же не пойдёте по улице с кружкой в руке, правда? Хе-хе-хе! Ой, как ребята будут смеяться!",
			link.l1 = "Это самая забавная чепуха... Подождите! Вы можете наполнить эти пустые винные бутылки ромом из бочки! Вот и всё! Нет никаких проблем...",
			link.l1.go = "PDM_PJ_Rom_3";
		break;

		case "PDM_PJ_Rom_3":
			dialog.text = "Воистину, вы почти что гений, капитан. Вы совершенно правы, я могу это сделать... Но я надеюсь, вы понимаете что это эксклюзивные, особые услуги... бутылка вымыта и высушена вручную, сами понимаете...  я могу продать своему клиенту разлитый по бутылкам ром за... Пять золотых монет! Хе-хе-хе!",
			MakeRandomLinkOrderTwo(link,
			"Ты совсем свихнулся, "+npchar.name+". Пять золотых монет за дешёвый ром? Нет! До свидания!",
			"exit",

			"Ну, хорошо! Ты действительно развеселил меня, прохвост. Вот твои деньги. Давай сюда ром. Ты, безусловно, заслужил своё золото.",
			"PDM_PJ_Rom_4");
		break;

		case "PDM_PJ_Rom_4":
			dialog.text = "Спасибо, "+ GetSexPhrase("месье","мадмуазэль") +". Подождите всего одну минутку\n"+
							"Вот ваш личный разлитый по бутылкам бочонок рома, капитан. Лично для вас я перевязал его розовыми ленточками... Ой, хе-хе-хе...",
			link.l1 = "Осторожно, "+npchar.name+", когда-нибудь просто задохнёшься от хохота. Думаю, если я не уйду отсюда, то именно это и произойдёт. До свидания.",
			link.l1.go = "PDM_PJ_Rom_5";
		break;

		case "PDM_PJ_Rom_5":
			DialogExit();

			Log_info("Вы получили бутылку с розовой ленточкой");
			GiveItem2Character(PChar, "PDM_PJ_Rom");
			GiveItem2Character(PChar, "PDM_PJ_BsRL");
			AddMoneyToCharacter(pchar, -5);
			DeleteAttribute(pchar, "questTemp.PDM_PJ_KR");
			sld = CharacterFromID("PDM_PJ_Strajnik_2")
			sld.Dialog.Filename = "Quest/PDM/Proklyataya_Jara.c";
			sld.dialog.currentnode = "Prines_Rom_1";
			AddQuestRecord("PDM_Proklyataya_Jara", "4");
		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

