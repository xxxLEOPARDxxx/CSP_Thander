
void ProcessDialogEvent()
{
 	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\ItemTrader\" + NPChar.City + "_ItemTrader.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
// ============================================================================
// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
			if (npchar.angry.name == "AscoldMerchant") Dialog.CurrentNode = "AngryQuest_AscoldMerchant";
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
  		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

  		case "First time":
			//зачарованный город -->
			if (pchar.questTemp.MC == "toCaracas" && npchar.city == "Caracas")
			{
				dialog.text = LinkRandPhrase("Я торгую себе здесь и знать не хочу никаких склок. Это не мое дело.",
					"Да-а, волнения в городе, однако...",
					"Не думаю, что эти волнения повредят моей торговле. Это хозяину таверны надо беспокоиться.");
				link.l1 = "Ясно.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.MC == "toCaracasPadre" || pchar.questTemp.MC == "toCaracasTavern")
			{
				dialog.text = "Говорят, что вы пошли в таверну к этому оборотню! Ну и как там?";
				link.l1 = "Никак...";
				link.l1.go = "exit";
				break;
			}
			//<-- зачарованный город

			dialog.text = NPCharSexPhrase(npchar, "Хотите прикупить снаряжение для себя или своих офицеров, капитан? Тогда вы обратились по адресу!", "Ой, капитан, я так и знала, что вы подойдете именно ко мне!.. Могу предложить снаряжение для вас и ваших офицеров, а также множество других необходимых вещей.");
			link.l1 = "Покажи, что там у тебя есть.";
			link.l1.go = "Trade_exit";

   			link.l2 = "Я по другому делу.";
			link.l2.go = "quests";
			//--> eddy. Аскольд, перехват на рендомного перца
			if (pchar.questTemp.Ascold == "Seek_powder" && !CheckAttribute(npchar, "quest.answer_2"))
			{
   				link.l4 = LinkRandPhrase("Тебе не встречалась такая вещь - порошок мумии?", "У тебя в продаже есть порошок мумии?", "Послушай, ты не знаешь, где можно достать порошок мумии?");
				link.l4.go = "AscoldMerchant";
			}
			//<-- eddy. Аскольд, перехват на рендомного перца
			link.l3 = "Спасибо, не интересует.";
			link.l3.go = "exit";

			NextDiag.TempNode = "First time";
		break;

		case "Trade_exit":
            if (CheckNPCQuestDate(npchar, "Item_date"))
			{
				SetNPCQuestDate(npchar, "Item_date");
				GiveItemToTrader(npchar);
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchItemsTrade(npchar);
		break;
		//=================== ноды квеста мэра. поиск шпиона на улице, опрос свидетеля ==================
		case "SeekSpy_Checking":
			dialog.text = "Да, я подтверждаю, " + NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)], "он действительно местный житель.", "она действительно местная жительница.");
			link.l1 = RandPhraseSimple("Я понял"+ GetSexPhrase("","а") +". Спасибо за помощь.", "Все ясно. Спасибо за помощь.");
			link.l1.go = "SeekSpy_Checking_1";
		break;
		case "SeekSpy_Checking_1":
			switch (pchar.GenQuest.SeekSpy.Type)
			{
				case "guardian": LAi_SetGuardianTypeNoGroup(npchar); break;
				case "patrol":   LAi_SetPatrolTypeNoGroup(npchar);   break;
				case "citizen":  LAi_SetCitizenTypeNoGroup(npchar);  break;
				case "merchant": LAi_SetMerchantTypeNoGroup(npchar); break;
			}
			LAi_SetCitizenTypeNoGroup(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)]);
			NextDiag.CurrentNode = "First Time";
			DialogExit();
		break;
		//Квест Аскольда. Базары с уличными торговцами
		case "AscoldMerchant":
			if(npchar.city == pchar.questTemp.Ascold.MerchantColony && npchar.location.locator == "merchant1")
			{
				dialog.text = "Э, "+ GetSexPhrase("милейший","дорогуша") +", это ты не по адресу. Тебе к индейским шаманам нужно или колдунам, как их там называют...";
				link.l1 = "Так, где же их найдёшь? Никто ничего не знает, или знает, да не говорит.";
				link.l1.go = "AscoldMerchant_5";
			}
			else
			{
				//BlackThorn: более внятный поиск порошка.
				if (!CheckAttribute(npchar, "quest.answer_1") && rand(2)==0)
				{
					npchar.quest.answer_1 = "true";
					npchar.quest.answer_2 = "true";
					if (NationNameGenitive(sti(npchar.nation)) != NationNameGenitive(sti(pchar.questTemp.Ascold.dialogNation)))
					{
						dialog.text = "Прости, но мы такого добра у себя не держим. Тебе стоит поспрашивать где-то в колониях "+ NationNameGenitive(sti(pchar.questTemp.Ascold.dialogNation))+".";
						link.l2 = "Спасибо за информацию.";
						link.l2.go = "exit";
					}
					else if (XI_ConvertString("Colony" + pchar.questTemp.Ascold.MerchantColony) != XI_ConvertString("Colony" + npchar.city))
					{
						dialog.text = "Я своих клиентов не обманываю и всяким мусором не тогрую, но по слухам, в колонии "+ XI_ConvertString("Colony" + pchar.questTemp.Ascold.MerchantColony) +" можно все что угодно найти, от приворотных зелий до порошка мумии.";
					}
					else
					{
						dialog.text = "У меня нет, но в городе точно кто-то его продавал. Поспрашивай остальных торговцев.";
					}
					link.l2 = "Спасибо за информацию.";
					link.l2.go = "exit";
				}
				else
				{
					npchar.quest.answer_1 = "true";
			dialog.text = NPCStringReactionRepeat(LinkRandPhrase("Порошок мумии? Я не знаю, что такое мумия.", "Порошок чего? Мумии? Что это такое?", "Порошок мумии? Что за вещица такая?"),
                     LinkRandPhrase("Опять ты спрашиваешь меня об этом?", "Снова ты начинаешь разговор о том же...", "И опять об этом порошке?"),
                     LinkRandPhrase(NPCharSexPhrase(npchar, "Я же ответил тебе на этот вопрос! Чего ты еще хочешь?", "Я же ответила тебе на этот вопрос! Чего ты еще хочешь?"),
                                    NPCharSexPhrase(npchar, "Я уже сказал тебе все, что считаю нужным. Опять эти странные вопросы?", "Я уже сказала тебе все, что считаю нужным. Опять эти странные вопросы?"),
                                    "Опять эти странные вопросы? Мне нечего добавить к сказанному ранее!"),
                     LinkRandPhrase("Опять?!! Опять?!!", "Слов просто нет!!! Опять?!", "Снова ты об этом проклятом порошке?!"), "quest", 10, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Это бальзамированное тело усопшего много тысячелетий назад египтянина.",
                                               "Ага, спрашиваю. Может, вспомнилось что-нибудь?",
                                               "Еще раз спрашиваю, может, изменилось что...",
                                               "Ага, снова спрашиваю.", npchar, Dialog.CurrentNode);
            link.l1.go = DialogGoNodeRepeat("AscoldMerchant_2", "AscoldMerchant_3", "AscoldMerchant_4", "", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "AscoldMerchant_2":
			dialog.text = LinkRandPhrase("Не-е-ет, такого добра нам не надо. Не доводилось встречать. И вообще, ты перв"+ GetSexPhrase("ый","ая") +", кто спрашивает такой странный товар. Не думаю, что торговля такими предметами понравится Святой Церкви. Это, знаешь ли, не шутки...",
                     NPCharSexPhrase(npchar, "Нет, не было такого товара. Даже если бы встретился, то не взял бы. Я регулярно посещаю церковь, не думаю, что Инквизиции понравится торговля такими вещами.", "Нет, не было такого товара. Даже если бы встретился, то не взяла бы. Я исправная прихожанка, не думаю, что Инквизиции понравится торговля такими вещами."),
                     NPCharSexPhrase(npchar, "Не встречал ничего подобного. И, полагаю, это к лучшему. Если моя жена узнает, то сразу же побежит к инквизиторам...", "Не встречала ничего подобного. И, полагаю, это к лучшему. Мой муж не будет в восторге от такой моей торговли..."));
			Link.l1 = "Да? Ну ладно, нет - так нет...";
			Link.l1.go = "exit";
		break;

		case "AscoldMerchant_3":
			dialog.text = LinkRandPhrase(NPCharSexPhrase(npchar, "Ничего я не запамятовал. Не знаю я ничего ни о каких мумиях и знать не желаю. И тебе не рекомендую этим промышлять. А то часом обвинят в колдовстве, от церкви отлучат...", "Ничего я не запамятовала. Не знаю я ничего ни о каких мумиях и знать не желаю. И тебе не рекомендую этим промышлять. А то часом обвинят в колдовстве, от церкви отлучат..."),
                                    "Все я прекрасно помню. Но о мумиях говорить не хочу. Святой Инквизиции бы этим делом заняться...",
                                    NPCharSexPhrase(npchar, "Все я помню хорошо. М-да, знала бы моя жена о таких предложениях - давно бы Святая Инквизиция занималась этим...", "Я все помню хорошо. И думаю, что надо бы мужа позвать..."));
			Link.l1 = "Агарх!! Странные вещи говоришь. Ну да ладно...";
			Link.l1.go = "exit";
		break;

		case "AscoldMerchant_4":
			dialog.text = LinkRandPhrase(NPCharSexPhrase(npchar, "Ничего не изменилось, ровным счетом ничего!!! Не видел я египетских покойников ни в целом, ни в истолченном виде!", "Ничего не изменилось, ровным счетом ничего!!! Не видела я египетских покойников ни в целом, ни в истолченном виде!"),
                                    NPCharSexPhrase(npchar, "Абсолютно ничего не изменилось - никаких истолченных трупов я не видел и, надеюсь, не увижу.", "Абсолютно ничего не изменилось - никаких истолченных трупов я не видела и, надеюсь, не увижу. А будешь приставать с идиотскими вопросам - мужа позову..."),
                                    NPCharSexPhrase(npchar, "Изменилось?!! Послушай, я же ясно выразился! Неужели не понятно, что с покойниками, истолченными или целыми, я не связываюсь?!!", "Изменилось?!! Послушайте, я же все совершенно ясно сказала! Неужели не понятно, что с покойниками, истолченными или целыми, я не связываюсь?!!"));
			Link.l1 = NPCharSexPhrase(npchar, "Да ты не нервничай так. Успокойся, не видел - так не видел...", "Да ты не нервничай так. Успокойся, не видела - так не видела...");
			Link.l1.go = "exit";
		break;

		case "AscoldMerchant_5":
			dialog.text = "То-то и оно... И не скажет никто. Инквизиция за куда меньшие пригрешения со свету сжить может. А уж за такое и подавно. Кому ж охота за свой длинный язык жизнью платить?";
			link.l1 = "Н-да... а может, подскажешь чего? Очень нужно. Один человек заказ сделал, а я вот уже сколько времени найти не могу.";
			link.l1.go = "AscoldMerchant_6";
		break;

		case "AscoldMerchant_6":
			dialog.text = "Заказ, говоришь? А не инквизиторская ли ищейка твой заказчик?";
			link.l1 = "Да нет, не похоже... Солидный продавец солидного магазина. Зачем бы ему это?!";
			link.l1.go = "AscoldMerchant_7";
		break;

		case "AscoldMerchant_7":
			dialog.text = "Действительно не похоже... Что ж, продам я тебе порошок. Только не вздумай сболтнуть кому. Учти, что я тебя знать не знаю и на страшном суде отпираться буду.";
			link.l1 = "Ну, это и так понятно...";
			link.l1.go = "AscoldMerchant_8";
		break;

		case "AscoldMerchant_8":
			dialog.text = "С тебя тысяча монет.";
			if (sti(pchar.money) >= 1000)
			{
				Link.l1 = "Недёшево, однако, но тут и не поторгуешься. Вот, держи.";
    		    Link.l1.go = "exit";
    		    pchar.questTemp.Ascold = "PowderWasSeek";
    		    AddMoneyToCharacter(pchar, -1000);
    		    GiveItem2Character(Pchar,"Powder_mummie");
			}
			else
			{
				link.l1 = "Вот чёрт! у меня с собой нет столько. Сейчас соберу и сразу к тебе. Смотри, не продай, пока я бегать буду...";
				link.l1.go = "exit";
			}
		break;

// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryQuest_AscoldMerchant":
            Dialog.text = RandPhraseSimple("Я не хочу с тобой больше иметь дело.", "Больше я тебе ничего продавать не буду.");
			Link.l1 = RandPhraseSimple("Ну, как знаешь. По всему видать, деньги тебе не нужны.", "Невелика потеря...");
		    Link.l1.go = "AngryExitAgain";
		    //===>> квест Аскольда, розыск порошка мумии.
            if (pchar.questTemp.Ascold == "Seek_powder" && npchar.city == pchar.questTemp.Ascold.MerchantColony && npchar.location.locator == "merchant1")
            {
                Dialog.text =  "Ты очень настойчив"+ GetSexPhrase("","а") +", видимо этот порошок тебе действительно нужен.";
    			Link.l1 = "Именно так. А теперь я хочу знать, есть ли он у тебя на самом деле. И не бойся, все останется между нами.";
    		    Link.l1.go = "AngStep_1";
            }
            if (CheckAttribute(npchar, "angry.terms")) //мирилка по квесту Аскольда через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms) && pchar.questTemp.Ascold != "Seek_powder")
                {
         			Dialog.text = NPCharSexPhrase(npchar, "Очень рассчитываю на то, что ты не будешь меня утомлять странными просьбами. Пожалуй, я готов вести дела с тобой.", "Очень надеюсь на то, что ты не будешь приставать ко мне с этими ужасными трупными покупками. Пожалуй, я готова торговать с тобой.");
        			Link.l1 = RandPhraseSimple("Здорово!", "Превосходно!");
        			Link.l1.go = "First time";
        			CharacterDelAngry(npchar);
                }
            }
    	break;
////////////////////////////////////////////////////////////////////////////////////////////////
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok")
		break;

		case "AngStep_1":
            Dialog.text = "Есть, но не для всех, сам"+ GetSexPhrase("","а") +" понимаешь. Но тебе продам. Тысяча монет, и он твой.";
            if (sti(pchar.money) >= 1000)
            {
    			Link.l1 = "Хорошо, вот твои деньги.";
    		    Link.l1.go = "AngryExitAgain";
    		    pchar.questTemp.Ascold = "PowderWasSeek";
    		    CharacterDelAngry(npchar);
    		    AddMoneyToCharacter(pchar, -1000);
    		    GiveItem2Character(Pchar,"Powder_mummie");
            }
            else
            {
    			Link.l1 = "Сейчас у меня с собой нет такой суммы. Как только соберу - сразу же навещу тебя.";
    		    Link.l1.go = "AngryExitAgain";
            }
    	break;
// <<<<<<<<<<<<============= блок нод angry =============================
	}
}
