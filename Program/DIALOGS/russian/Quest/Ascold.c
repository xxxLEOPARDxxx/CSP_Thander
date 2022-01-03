// Аскольд
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Tichingitu_11":
			AddMoneyToCharacter(pchar, -10000);
			dialog.text = "Отлично! Вот это дело! Сейчас я напишу записку и приложу свою печать, подожди немного... вот, держи. Отдай это коменданту и можешь забирать своего индейца. Вот только зачем он тебе понадобился - ума не приложу. Разве что на ярмарках за деньги показывать, ха-ха!";
			link.l1 = "Бог всё видит, Аскольд. Спасти жизнь человеку - благое дело.";
			npchar.quest.Tichingitu = "paid"
			link.l1.go = "Tichingitu_12";
		break;

		if (CheckAttribute(pchar, "questTemp.Tichingitu") && pchar.questTemp.Tichingitu == "ascold")
		{
			dialog.text = "Ну, что скажешь? Сходил"+GetSexPhrase("","а")+" посмотреть на это индейское чучело?";
			link.l1 = "Сходил"+GetSexPhrase("","а")+"... Поэтому и приш"+GetSexPhrase("ёл","ла")+" снова к тебе.";
			link.l1.go = "Tichingitu_7";
			if (!CheckAttribute(npchar, "quest.Tichingitu"))
			{
				npchar.quest.Tichingitu = true;
				break;
			}
		}
		if (CheckAttribute(pchar, "questTemp.Tichingitu") && pchar.questTemp.Tichingitu == "money")
		{
			dialog.text = "А, это опять ты! Ну что, прин"+GetSexPhrase("ёс","есла")+" деньги за индейца?";
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = "Да. Вот, держи.";
				link.l1.go = "Tichingitu_11";
			}
			if (CheckAttribute(npchar, "quest.Tichingitu") && npchar.quest.Tichingitu != "paid")
			{
				link.l2 = "Нет, я ещё не собрал"+GetSexPhrase("","а")+" требуемую сумму.";
				link.l2.go = "exit";
				break;
			}
		}
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            if (npchar.quest.meeting == "0")
            {
            	dialog.text = "Приветствую. Меня зовут Аскольд. А с кем имею честь разговаривать?";
        		link.l1 = "Меня зовут " + GetFullName(pchar) + ".";
        		link.l1.go = "Step_1";
                npchar.quest.meeting = "1";
            }
            else
            {
            	dialog.text = "Я не люблю, когда люди, которых я не знаю, беспокоят меня.";
        		link.l1 = "Понял"+ GetSexPhrase("","а") +", уже ухожу...";
        		link.l1.go = "exit";
        		link.l2 = "Хамить изволите, сударь?";
        		link.l2.go = "Step_3";
                NextDiag.TempNode = "First time";
            }
		break;

 		case "Step_1":
        	dialog.text = "Кто ты и чем ты занимаешься?";
    		link.l1 = "Я - капер.";
    		link.l1.go = "Step_2";
		break;

 		case "Step_2":
        	dialog.text = "Слушай, капер...";
    		link.l1 = "Да?";
    		link.l1.go = "First time";
		break;

 		case "Step_3":
            if (npchar.quest.meeting == "1")
            {
            	dialog.text = "У-у-у, да ты не просто капер, а грозный капер... Пош"+ GetSexPhrase("ел","ла") +" вон отсюда!";
        		link.l1 = "...";
        		npchar.quest.meeting = "2";
            }
            else
            {
            	dialog.text = RandPhraseSimple("Опять грозный и злой капер изволит тишину нарушать?! Повторим вынос тела...", "Опять в бутылку полез"+ GetSexPhrase("","ла") +"... Пора принимать меры.");
        		link.l1 = RandPhraseSimple("Да я тебя сейчас...", "Посмотрим, кто кого выкинет из дома на этот раз...");
            }
            link.l1.go = "Step_4";
		break;

 		case "Step_4":
            DoReloadCharacterToLocation("BasTer_town", "reload", "houseSp1");
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

 		case "HaveRecomendation":
			sld = characterFromId(pchar.questTemp.Ascold.TraderId);
            if (npchar.quest.meeting == "0")
            {
            	dialog.text = "Приветствую. Меня зовут Аскольд. А с кем имею честь...";
				link.l1 = "Меня зовут " + GetFullName(pchar) + ". А прислал меня к тебе " + GetFullName(sld) + ", хозяин магазина, что находится на " + XI_ConvertString("Colony" + sld.City + "Dat") + ".";
                npchar.quest.meeting = "1";
            }
            else
            {
            	dialog.text = "Опять на горизонте "+ GetSexPhrase("появился наш грозный корсар","появилась наша грозная женщина-корсар") +". Что тебе нужно на этот раз?";
        		link.l1 = "На этот раз меня прислал к тебе " + GetFullName(sld) + ", хозяин магазина, что находится на " + XI_ConvertString("Colony" + sld.City + "Dat") + ".";
            }
            link.l1.go = "Step_5";
		break;

 		case "Step_5":
			sld = characterFromId(pchar.questTemp.Ascold.TraderId);
        	dialog.text = "Хех, этого человека я знаю. Что ж, проходи, садись, давай выпьем водки.\n"+
                          "(доверительно) В этих краях русская водка - большой дефицит. Рома ямайского - хоть залейся, но по сравнению с водкой, ром - акулья моча.\n"+
                          "В общем, говори, какие у тебя дела ко мне?";
    		link.l1 = sld.lastname + " сказал, что ты искал порошок мумии. У меня он есть.";
    		link.l1.go = "Step_6";
		break;

 		case "Step_6":
        	dialog.text = "Очень хорошо. Плачу 30000 за этот порошок.";
    		link.l1 = "Хорошая цена. По рукам.";
            if (CheckCharacterItem(pchar, "Powder_mummie"))
            {
        		link.l1.go = "Step_7";
        		TakeItemFromCharacter(pchar, "Powder_mummie");
        		AddMoneyToCharacter(pchar, 30000);
            }
            else
            {
        		link.l1.go = "No_Powder";
            }
		break;

 		case "No_Powder":
        	dialog.text = "Эй, "+ GetSexPhrase("брат","сестренка") +", шалишь! Нет у тебя порошка. Людей, которые пытаются меня обмануть, я не признаю больше.\n"+
                          "Так что, пош"+ GetSexPhrase("ел","ла") +" вон отсюда!";
    		link.l1 = "Да ты что! Я же пошутил"+ GetSexPhrase("","а") +"! У меня и в мыслях не было...";
    		link.l1.go = "Step_4";
    		NextDiag.TempNode = "First time";
    		CloseQuestHeader("Ascold");
    		pchar.questTemp.Ascold = "BreakeQuest";
		break;

 		case "Step_7":
        	dialog.text = "Дело сделано, теперь можно и обмыть...";
    		link.l1 = "Не, мыть я ничего не буду. Ты вот лучше скажи мне, зачем тебе эта дрянь? Сколько голову ломал"+ GetSexPhrase("","а") +" над этим, а понять не смог"+ GetSexPhrase("","ла") +". Абсолютно бесполезная и мерзкая вещица.";
    		link.l1.go = "Step_8";
		break;

 		case "Step_8":
        	dialog.text = "Ну, это как сказать. Этот порошок и подобные предметы культа индейцев заказывает мне известный в Европе ученый Пьер де ла Фонтен.\n"+
                          "Я нахожусь здесь в качестве его доверенного лица. В принципе, доволен вполне. Де ла Фонтен оплачивает аренду дома и мое проживание.\n"+
                          "А за каждую такую вещицу, которую я разыскиваю здесь ему на заказ, он приплачивает очень и очень недурно.";
    		link.l1 = "Понятно.";
    		link.l1.go = "Step_9";
		break;

 		case "Step_9":
        	dialog.text = "Слушай, раз пошла такая песня и мы с тобой сработались, то предлагаю тебе еще работу.\n"+
                          "У меня как раз поступил новый заказ на три ацтекских артефакта.";
    		link.l1 = "Возьмусь, пожалуй. Я соглас"+ GetSexPhrase("ен","на") +".";
    		link.l1.go = "Step_10";
    		link.l2 = "Нет, не возьмусь. У меня других дел по горло.";
    		link.l2.go = "No_Work";
		break;

 		case "No_Work":
        	dialog.text = "Да? Я не люблю, когда мне отказывают, таких я более знать не желаю. Поэтому - пош"+ GetSexPhrase("ел","ла") +" вон из моего дома!";
    		link.l1 = "Эй, эй! Ты что делаешь?!!";
    		link.l1.go = "Step_4";
    		NextDiag.TempNode = "First time";
    		CloseQuestHeader("Ascold");
    		pchar.questTemp.Ascold = "BreakeQuest";
    		group_DeleteGroup("Ascold_Spa_Attack");
    		DeleteAttribute(PChar, "questTemp.Ascold.Ship");
		break;

 		case "Step_10":
        	dialog.text = "Хорошо. Слушай теперь, что мне нужно разыскать.\n"+
                          "Мне нужна статуэтка Тлалока, ацтекского бога дождя и грома, церемониальный сосуд племени пурепча и церемониальный нож Туми.";
    		link.l1 = "Понял"+ GetSexPhrase("","а") +". Что ж, буду смотреть по сторонам. Соберу все три вещи - буду у тебя.";
    		link.l1.go = "exit";
			if (!CheckAttribute(pchar, "questTemp.Tichingitu") && !CheckAttribute(npchar, "quest.Tichingitu"))
			{
				link.l2 = "Кажется мне, тебя беспокоит что-то ещё, не так ли?";
				link.l2.go = "Tichingitu_1";
			}
    	    pchar.questTemp.Ascold = "SeekThreeObject";
    	    NextDiag.TempNode = "ResultOfSeek";
            AddQuestRecord("Ascold", "3");
	    AddQuestUserData("Ascold", "sSex", GetSexPhrase("ся","ась"));
		break;

		case "Tichingitu_1":
			dialog.text = "У тебя на удивление хорошее чутьё. Что-ж, расскажу. На днях ко мне вломились в дом несколько бандитов. Куда только стража смотрела...";
			link.l1 = "Очевидно, куда угодно кроме того, куда было надо. Что дальше?";
			link.l1.go = "Tichingitu_2";
		break;

		case "Tichingitu_2":
			dialog.text = "Ну я взял оглоблю и наподдал им. Едва ноги унесли. Да только вот напасть какая, отвлекали меня те, что вломились. На второй этаж забрался вор и унёс ларь с ценностями, чтоб его от жадности разорвало!";
			link.l1 = "И ты его не остановил?";
			link.l1.go = "Tichingitu_3";
		break;

		case "Tichingitu_3":
			dialog.text = "Куда там, удрал вместе с подельниками в джунгли. А их там уже не найдёшь. Ладно, тут уж ничего не поделать. Я конечно нанял наёмников, чтобы прочесали остров, но грабителей и вора уже и след простыл.";
			link.l1 = "Звучит очень неприятно. Можно сказать горе...";
			link.l1.go = "Tichingitu_4";
		break;

		case "Tichingitu_4":
			dialog.text = "Так вот эта кража - еще не всё. Буквально на днях - представляете, ко мне снова залез воришка\nНу это уж слишком! Но тут он от меня не ушёл: я поймал его, задал хорошую взбучку и сдал коменданту. Думаю, его скоро повесят. И поделом ему!";
			link.l1 = "Не думаешь, что погорячился?";
			link.l1.go = "Tichingitu_5";
		break;

		case "Tichingitu_5":
			dialog.text = "Может быть. На вид он довольно истощённый был. Полез видать от полной безысходности. И его интересовали только монеты. Но и меня пойми... Такое, представляете, чучело залезло ко мне в комнату и шарилось по сундукам\nИндеец из каких-то глухих джунглей, просто чудо. Весь в наряде, раскрашенный... Можете сходить в наши казематы и посмотреть на этого шута ряженого, если вам интересно, пока он ещё жив.";
			link.l1 = "Хм... Может, и загляну.";
			link.l1.go = "Tichingitu_6";
		break;

		case "Tichingitu_6":
			dialog.text = "Сходи-сходи, посмотри на местные ходячие диковины...";
			link.l1 = "Всего доброго.";
			link.l1.go = "exit";
			pchar.questTemp.Tichingitu = "true";
			AddDialogExitQuestFunction("SetTichingituJail");
			SetFunctionTimerCondition("FreeTichingituOver", 0, 0, 10, false);
		break;

		case "Tichingitu_7":
			dialog.text = "Ну, что ещё?";
			link.l1 = "Аскольд, я говорил"+GetSexPhrase("","а")+" с этим индейцем. И я приш"+GetSexPhrase("ёл","ла")+" просить за него. Этот несчастный просто хотел есть...";
			link.l1.go = "Tichingitu_8";
		break;

		case "Tichingitu_8":
			dialog.text = "Его можно понять. Так ты что, вызволить его хочешь?";
			link.l1 = "Его ведь казнить собираются, а мне он может и пригодится на корабле...";
			link.l1.go = "Tichingitu_9";
		break;

		case "Tichingitu_9":
			dialog.text = "Раз уж такое дело, то думаю, ты можешь его выкупить. Меня устроит компенсация в 10000 пиастров.";
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = "Хорошо, вот деньги.";
				link.l1.go = "Tichingitu_11";
			}
			link.l2 = "Пожалуй, тогда зайду попозже.";
			link.l2.go = "Tichingitu_10";
		break;

		case "Tichingitu_10":
			dialog.text = "И поторопись! Дней через десять они уже не понадобятся...";
			link.l1 = "Приму к сведению. До свидания!";
			link.l1.go = "exit";
			pchar.questTemp.Tichingitu = "money";
		break;

		case "Tichingitu_12":
			GiveItem2Character(pchar, "letter_A");
			PlaySound("interface\important_item.wav");
			dialog.text = "Это спорный вопрос. А если ты спасаешь убийцу или насильника? Выпьешь водочки на посошок? А потом уже ступай к коменданту, пока твоего краснокожего друга не вздёрнули на виселицу...";
			link.l1 = "Так и быть, уговорил.";
			link.l1.go = "exit_vodka";
			pchar.questTemp.Tichingitu = "pay";
		break;

		case "exit_vodka":
			LAi_MethodDelay("FrameAscoldVodka",0.1);
			DialogExit();
		break;

 		case "ResultOfSeek":
        	dialog.text = "Удалось разыскать индейские погремушки? Мне нужны все три сразу, по одной можешь не таскать.";
    		link.l1 = "Нет еще, но я этим занимаюсь.";
    		link.l1.go = "exit";
    		NextDiag.TempNode = "ResultOfSeek";
            if (CheckCharacterItem(pchar, "indian19") && CheckCharacterItem(pchar, "indian20") && CheckCharacterItem(pchar, "indian21"))
            {
                link.l2 = "Да, разыскал"+ GetSexPhrase("","а") +". И где мои деньги?";
                link.l2.go = "Step_11";
            }
		break;

 		case "Step_11":
        	dialog.text = "Хех, за каждый предмет я готов выложить по 30000. Итого - 90000 монет. Соглас"+ GetSexPhrase("ен","на") +"?";
            link.l1 = "Меня устраивает цена. По рукам.";
            if (pchar.questTemp.Ascold == "SoughtThreeObject")
            {
               link.l1 = "Если бы ты знал, Аскольд, сколько я заплатил"+ GetSexPhrase("","а") +" за эти артефакты... Но я понимаю, что требовать от тебя возврата этих денег - просто нереально, ты и так предлагаешь цену в шесть раз дороже... Я соглас"+ GetSexPhrase("ен","на") +".";
            }
    		link.l1.go = "Step_12";
            link.l2 = "Нет, давай больше денег.";
    		link.l2.go = "WantMoreMoney";
		break;

 		case "WantMoreMoney":
        	dialog.text = "Вот это да. Похоже я в тебе ошибался - ты сверх всякой меры "+ GetSexPhrase("жадный человек","жадная девка") +". Такие люди для меня никто, я их не знаю. И тебя более знать не желаю.\n"+
                          "Пош"+ GetSexPhrase("ел","ла") +" вон!";
        	link.l1 = "Эй, Аскольд, подожди! Мы же нормальные люди, давай поторгуемся, договоримся...";
    		link.l1.go = "Step_4";
    		NextDiag.TempNode = "First time";
    		CloseQuestHeader("Ascold");
    		pchar.questTemp.Ascold = "BreakeQuest";
		break;

 		case "Step_12":
        	dialog.text = "Итак, вот твои 90000, а предметы теперь наши.";
        	link.l1 = "Забирай.";
    		link.l1.go = "Step_13";
		break;

 		case "Step_13":
        	dialog.text = "Слушай, ежели желаешь, заскочи ко мне через месяц-другой. Может, еще работенка подвернется.";
    		link.l1 = "Буду проходить рядом - непременно навещу тебя. Работенку подкидываешь не пыльную, а прибыль приличная.";
    		link.l1.go = "exit";
    		TakeItemFromCharacter(pchar, "indian19");
    		TakeItemFromCharacter(pchar, "indian20");
    		TakeItemFromCharacter(pchar, "indian21");
    		AddMoneyToCharacter(pchar, 90000);
			pchar.questTemp.Ascold = "TakenThreeObject";
    		SaveCurrentQuestDateParam("questTemp.Ascold");
    		NextDiag.TempNode = "WalkTwoMounth";
    		AddQuestRecord("Ascold", "4");
		break;

		case "WalkTwoMounth":
		    if (GetQuestPastDayParam("questTemp.Ascold") > 62)
		    {
            	dialog.text = "О-о-о, наконец-то! А я тебя жду. Мне нужны твои услуги, " + GetFullName(pchar) + ".";
            	link.l1 = "Что тебе нужно разыскать на этот раз?";
        		link.l1.go = "Step_14";
		    }
            else
            {
            	dialog.text = "О-о-о, кого я вижу?! "+ GetSexPhrase("Мой друг","Моя подруга") +" " + GetFullName(pchar) + ", рад видеть. Если ты по поводу работы, то обрадовать пока ничем не могу, сам сижу без гроша в кармане. А ты заглядывай как-нибудь позже.";
            	link.l1 = "Хорошо, Аскольд. Буду в этих краях - загляну.";
        		link.l1.go = "exit";
        		NextDiag.TempNode = "WalkTwoMounth";
            }
		break;

 		case "Step_14":
        	dialog.text = "Ты знаешь, на этот раз дело не в розыске, задача посерьезней будет.";
        	link.l1 = "У-у-у, мороз по коже... Чую запах больших денег! Давай, излагай суть проблемы.";
    		link.l1.go = "Step_15";
		break;

 		case "Step_15":
        	dialog.text = "Проблема следующая. Испанцы, вот уже сотню лет безжалостно истребляющие континентальных индейцев и уничтожающие их культурное наследие, вдруг озаботились сбором предметов этой самой индейской культуры.\n"+
                          "Дело в том, что при дворе Марианны, откуда ни возьмись, возникла странная мода на предметы индейского культа. И теперь испанцы рыскают везде и собирают артефакты, которые мне нужны позарез. И переправляют найденое в Старый Свет. Мой бизнес страдает, и я с этим не согласен.\n"+
                          "В общем, мне удалось узнать, что в Гаване собрана большая партия предметов культа ацтеков невиданной до сей поры ценности. Я хочу получить эти предметы, понятно, что все забрать не удасться, но хоть что-нибудь.\n"+
                          "И еще, так, между прочим... Я хочу получить инвентарную опись собранного испанцами индейского добра. Де ла Фонтену будет очень интересно на нее взглянуть.";
        	link.l1 = "И всего-то делов? Да нет проблем. Все у тебя будет. А ты точно знаешь, что такая опись есть?";
    		link.l1.go = "Step_16";
        	link.l2 = "Слушай, ты не обижайся, но сейчас никак не могу. Времени нет.";
    		link.l2.go = "No_Work";
		break;

 		case "Step_16":
        	dialog.text = "Да, точно. Шепнули мне тут друзья на небезвозмездной основе... Опись прилагается к грузу, поэтому где артефакты, там и опись.";
        	link.l1 = "Понятно. Ну, я приступаю. Так сказать, жди меня и я вернусь.";
    		link.l1.go = "exit";
    		SaveCurrentQuestDateParam("questTemp.Ascold");
    		NextDiag.TempNode = "AfterManowarsBattle";
    		pchar.questTemp.Ascold = "ToHavanna";
    		AddQuestRecord("Ascold", "5");
		break;

 		case "AfterManowarsBattle":
        	dialog.text = "Раздобыл"+ GetSexPhrase("","а") +" что-нибудь, выполнил"+ GetSexPhrase("","а") +" поручение?";
        	link.l1 = "Пока нет, но я этим занимаюсь.";
    		link.l1.go = "exit";
        	link.l2 = "У меня нет больше желания заниматся твоими проблемами. Извини.";
    		link.l2.go = "No_Work";
            if (pchar.questTemp.Ascold == "SeekInformatorHavanna")
            {
             	link.l1 = "Слушай, ты в прошлый наш разговор что-то там сказал про своего друга, который тебе шепнул о том списке, что я разыскиваю.";
        		link.l1.go = "Step_17";
            }
            if (pchar.questTemp.Ascold == "ReciveInformationManowar")
            {
             	link.l1 = "Аскольд! Я наш"+ GetSexPhrase("ел","ла") +" твоего друга-информатора! Это испанский офицер по имени Фернандо Гонсалес в Сантьяго. Кстати, он передавал тебе привет...";
        		link.l1.go = "Step_20";
            }
            if (pchar.questTemp.Ascold == "ILookedThisAss" && !CheckAttribute(PChar, "questTemp.Ascold.List"))
            {
             	link.l1 = "Аскольд! Там испанская эскадра из шести кораблей с мановаром во главе!!!";
        		link.l1.go = "Step_24";
            }
            if (pchar.questTemp.Ascold == "ILookedThisAss" && CheckAttribute(PChar, "questTemp.Ascold.List"))
            {
             	link.l1 = "Аскольд! Список у тебя, но там еще остались непотопленные корабли.";
        		link.l1.go = "Step_25";
            }
            if (pchar.questTemp.Ascold == "2ILookedThisAss" && CheckAttribute(PChar, "questTemp.Ascold.List"))
            {
             	link.l1 = "Аскольд! Список у тебя, но там еще остались непотопленные корабли.";
        		link.l1.go = "Step_25";
            }
            if (pchar.questTemp.Ascold == "Ascold_ManowarsDead" && !CheckAttribute(PChar, "questTemp.Ascold.List"))
            {
             	link.l1 = "Я потопил"+ GetSexPhrase("","а") +" все корабли, но инвентарного списка мне найти так и не удалось.";
        		link.l1.go = "NoFoundList";
            }
    		if (CheckCharacterItem(pchar, "ShipsJournal") && pchar.questTemp.Ascold == "ILookedThisAss")
    		{
            	link.l1 = "Да, черт меня побери! Я прош"+ GetSexPhrase("ел","ла") +" семь кругов ада, но добыл"+ GetSexPhrase("","а") +" для тебя этот список. Вот он.";
        		link.l1.go = "Step_26";
    		}
    		if (CheckCharacterItem(pchar, "ShipsJournal") && pchar.questTemp.Ascold == "2ILookedThisAss")
    		{
            	link.l1 = "Да, черт меня побери! Я прош"+ GetSexPhrase("ел","ла") +" семь кругов ада, но добыл"+ GetSexPhrase("","а") +" для тебя этот список. Вот он.";
        		link.l1.go = "Step_26";
    		}
            if (CheckCharacterItem(pchar, "ShipsJournal") && pchar.questTemp.Ascold == "Ascold_ManowarsDead")
            {
             	link.l1 = "Я уничтожил"+ GetSexPhrase("","а") +" испанские корабли, инвентарный список тоже у меня.";
        		link.l1.go = "ManowarGoodWork";
            }
            if (pchar.questTemp.Ascold == "Ascold_ManowarsDead" && CheckAttribute(PChar, "questTemp.Ascold.List"))
            {
             	link.l1 = "Эскадру я отправил"+ GetSexPhrase("","а") +" на дно!";
        		link.l1.go = "ManowarGoodWork";
            }
			if (pchar.questTemp.Ascold == "Ascold_ManowarsNoDead")
            {
             	link.l1 = "Послушай, мне не удалось потопить испанскую эскадру. И у храма никакой экспедиции мне обнаружить не удалось.";
        		link.l1.go = "ManowarNoGoodWork";
            }
		break;

 		case "Step_17":
        	dialog.text = "И что?";
        	link.l1 = "Мне нужна твоя помощь, дело в том, что столкнул"+ GetSexPhrase("ся","ась") +" с проблемой в Гаване. Никак не могу разузнать, куда ушел мановар, на который погрузили индейские артефакты. Пусть твой друг поможет.";
    		link.l1.go = "Step_18";
		break;

 		case "Step_18":
        	dialog.text = "Нет, не пойдет. Я не собираюсь трепаться по всем Карибам о своих связях.";
        	link.l1 = "Но я же действую в твоих интересах, в конце-то концов!!!";
    		link.l1.go = "Step_19";
		break;

 		case "Step_19":
        	dialog.text = "Это так, но действуй самостоятельно. На мою помощь не расчитывай.";
        	link.l1 = "Ну что ж, спасибо тебе, друг Аскольд...";
    		link.l1.go = "exit";
    		pchar.questTemp.Ascold = "2SeekInformatorHavanna";
    		NextDiag.TempNode = "AfterManowarsBattle";
		break;

 		case "Step_20":
        	dialog.text = "Как-нибудь обойдемся в общении без твоего посредничества... И что, узнал"+ GetSexPhrase("","а") +" что-либо?";
        	link.l1 = "Да, испанцы нашли близ бухты Аматике, что южней Белиза, индейский храм и сейчас там работает целая экcпедиция. А к этому месту со всего Нового света стягиваются груженные корабли.";
    		link.l1.go = "Step_21";
		break;

 		case "Step_21":
        	dialog.text = "Зачем?";
        	link.l1 = "Полагаю, разграбят индейский храм и уйдут со всем этим в Испанию.";
    		link.l1.go = "Step_22";
		break;

 		case "Step_22":
        	dialog.text = "Печальные новости. Тогда у меня к тебе просьба - ты долж"+ GetSexPhrase("ен","на") +" уничтожить всех испанцев, находящихся близ бухты Аматике. Все корабли должны пойти ко дну, а сама экспедиция у храма должна быть уничтожена.\n"+
                          "И мне нужен инвентарый список испанцев.";
        	link.l1 = "Я готов"+ GetSexPhrase("","а") +". Могу приступать хоть сейчас.";
    		link.l1.go = "Step_23";
        	link.l2 = "Не слишком ли много ты хочешь от меня, приятель? Поищи дурака в другом месте.";
    		link.l2.go = "No_Work";
		break;

 		case "Step_23":
        	dialog.text = "Это хорошо, даже не знаю, как тебя благодарить за помощь...";
        	link.l1 = "Потом рассчитаемся, друг Аскольд.";
    		link.l1.go = "exit";
    		AddQuestRecord("Ascold", "8");
    		pchar.questTemp.Ascold = "IMustKillAll";
    		NextDiag.TempNode = "AfterManowarsBattle";
		break;

 		case "Step_24":
        	dialog.text = "Очень хорошо, это должно тебя радовать. Ты корсар или тряпка? Уничтожь всех испанцев и доставь мне этот чертов инвентарный список.";
        	link.l1 = "Да, конечно. Я сделаю это. Инвентарный список будет у тебя и испанцы будут уничтожены.";
    		link.l1.go = "Step_25";
            link.l2 = "Это без меня. Ищи дурака!";
    		link.l2.go = "No_Work";
		break;

 		case "Step_25":
        	dialog.text = "Ну, так что ты стоишь! Иди, уничтожай.";
        	link.l1 = "Уже иду.";
    		link.l1.go = "exit";
    		pchar.questTemp.Ascold = "2ILookedThisAss";
    		NextDiag.TempNode = "AfterManowarsBattle";
		break;

 		case "NoFoundList":
        	dialog.text = "И это надо же, отправить к праотцам несметное количество испанцев, а какой-то список найти не смог"+ GetSexPhrase("","ла") +". С такими неумелыми людьми я дела не имею.\n"+
                      "Так что, пош"+ GetSexPhrase("ел","ла") +" вон отсюда!";
    		link.l1 = "Да уж, и это после всего, что мне довелось пережить из-за тебя...";
    		link.l1.go = "Step_4";
    		NextDiag.TempNode = "First time";
    		CloseQuestHeader("Ascold");
    		pchar.questTemp.Ascold = "BreakeQuest";
		break;

 		case "Step_26":
        	dialog.text = "Список это хорошо, ты молодец. Но мне нужно, чтобы ты потопил"+ GetSexPhrase("","а") +" все корабли испанцев, а также очистил"+ GetSexPhrase("","а") +" храм. Никто не должен уйти оттуда живым.";
        	link.l1 = "Назови мне весомую причину, которая бы меня заинтересовала...";
    		link.l1.go = "Step_27";
            link.l2 = "Ты, конечно, извнини, что-то мне не хочется резать бедных испанцев.";
    		link.l2.go = "No_Work";
            link.l3 = "Аскольд, мне нужны деньги. Я ведь доставил"+ GetSexPhrase("","а") +" тебе список, хотел"+ GetSexPhrase("","а") +" бы получить награду.";
    		link.l3.go = "WantMoreMoney";
            BackItemDescribe("ShipsJournal");
            TakeItemFromCharacter(pchar, "ShipsJournal");
            pchar.questTemp.Ascold.list = 1;
		break;

 		case "Step_27":
        	dialog.text = "Я жду денег от моего патрона, Пьер де ла Фонтена. Потерпи и заплачу тебе сполна.";
        	link.l1 = "Хорошо, я уничтожу испанцев. Надеюсь, я буду довол"+ GetSexPhrase("ен","ьна") +" размером награды.";
    		link.l1.go = "exit";
            AddQuestRecord("Ascold", "10");
	    AddQuestUserData("Ascold", "sSex", GetSexPhrase("","а"));
		break;

 		case "ManowarGoodWork":
        	dialog.text = "Ты не уничтожил"+ GetSexPhrase("","а") +" испанцев на самом острове. Все испанцы, ведущие работы в храме, должны быть уничтожены.";
        	link.l1 = "Хорошо, доделаю работу.";
    		link.l1.go = "exit";
            link.l2 = "Ты, конечно, извнини, что-то мне больше не хочется резать бедных испанцев.";
    		link.l2.go = "Step_28";
    		NextDiag.TempNode = "ManowarGoodWork";
		break;

		case "ManowarNoGoodWork":
        	dialog.text = "И это надо же! А еще капером называл"+ GetSexPhrase("ся","ась") +". С такими неумелыми людьми я дела не имею.\n"+
                      "Так что, пош"+ GetSexPhrase("ел","ла") +" вон отсюда!";
    		link.l1 = "Да уж, и это после всего, что мне довелось пережить из-за тебя...";
    		link.l1.go = "Step_4";
    		NextDiag.TempNode = "First time";
    		CloseQuestHeader("Ascold");
    		pchar.questTemp.Ascold = "BreakeQuest";
		break;

 		case "Step_28":
        	dialog.text = "Ты что, бросишь дело на половине пути?";
        	link.l1 = "Ага, брошу, потому что ты меня достал.";
    		link.l1.go = "Step_4";
    		NextDiag.TempNode = "First time";
    		CloseQuestHeader("Ascold");
    		pchar.questTemp.Ascold = "BreakeQuest";
    		pchar.quest.Ascold_FightNearTemple.over = "yes";
		break;

 		case "Ascold_KilledTemple":
        	dialog.text = "Вот ты и вернул"+ GetSexPhrase("ся","ась") +". Чем обрадуешь?";
        	link.l1 = "Аскольд, испанская экспедиция к храму инков полностью уничтожена. Но мне нигде не удалось найти чертов инвентарный список.";
    		link.l1.go = "NoFoundList";
            if (CheckCharacterItem(pchar, "ShipsJournal") || CheckAttribute(PChar, "questTemp.Ascold.List"))
            {
            	link.l1 = "Аскольд, испанская экспедиция к храму инков полностью уничтожена.";
        		link.l1.go = "Step_29";
                BackItemDescribe("ShipsJournal");
                TakeItemFromCharacter(pchar, "ShipsJournal");
                DeleteAttribute(PChar, "questTemp.Ascold.List");
            }
		break;

 		case "Step_29":
        	dialog.text = "Отлично! Я знал, что на тебя можно положиться.";
        	link.l1 = "Я хотел"+ GetSexPhrase("","а") +" бы поговорить о вознаграждении.";
    		link.l1.go = "Step_30";
		break;

 		case "Step_30":
        	dialog.text = "Да, конечно... Послушай, мне нечем тебе заплатить, я еще не получил деньги от патрона. Тебе нужно немного подождать.";
        	link.l1 = "М-да, слов нет... Знал бы ты, что мне пришлось пережить...";
    		link.l1.go = "Step_31";
		break;

 		case "Step_31":
        	dialog.text = "Понимаю, но у меня просто нет денег. Мне нужно отправить во Францию инвентарный список, который ты захватил"+ GetSexPhrase("","а") +". Надеюсь, это ускорит дело. Заглядывай ко мне время от времени...";
        	link.l1 = "Ну что ж, будь по твоему. Буду заезжать к тебе по мере возможности.";
    		link.l1.go = "exit";
    		NextDiag.TempNode = "Mummie_begin";
    		SaveCurrentQuestDateParam("questTemp.Ascold");
    		AddQuestRecord("Ascold", "12");
	        AddQuestUserData("Ascold", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("Ascold", "sSex1", GetSexPhrase("ся","ась"));
		break;

 		case "Mummie_begin":
        	dialog.text = "Рад видеть тебя, "+ GetFullName(pchar) + ". Но новостей пока у меня нет. Деньги еще не пришли...";
        	link.l1 = "Жаль... Ну что ж, подождем.";
    		link.l1.go = "exit";
    		NextDiag.TempNode = "Mummie_begin";
		    if (GetQuestPastDayParam("questTemp.Ascold") > 40)
            {
            	dialog.text = "О-о-о, кого я вижу, "+ GetSexPhrase("мой друг","моя подруга") +" "+ GetFullName(pchar) + "...";
            	link.l1 = "Есть новости?";
        		link.l1.go = "Step_31A";
            }
		break;

 		case "Step_31A":
        	dialog.text = "Есть, но они тебе не понравятся. Дело в том, что я получил известие от де ла Фонтена.";
        	link.l1 = "Ну что, деньги-то он прислал?";
    		link.l1.go = "Step_32";
		break;

 		case "Step_32":
        	dialog.text = "Прислал немного. Но проделанная тобой работа его не заинтересовала. Инвентарный список оказался бестолковым, а уничтожение испанской экспедиции, по его словам, отрицательно сказалось на европейской науке в целом.";
        	link.l1 = "Вот это да...";
    		link.l1.go = "Step_33";
        break;

        case "Step_33":
        	dialog.text = "У меня тоже, честно говоря, нет слов. Но жизнь продолжается. У меня к тебе есть дело.";
        	link.l1 = "И что на этот раз?";
    		link.l1.go = "Step_34";
            link.l2 = "Слушай, шел бы ты со своим делом куда-нибудь подальше.";
    		link.l2.go = "No_Work";
		break;

 		case "Step_34":
        	dialog.text = "Де ла Фонтен раскопал в Европе какие-то старинные документы, в которых вроде бы говорится, что на нашем острове тоже находится какая-то гробница непонятно кого.\n"+
                          "Надо постараться обыскать остров как следует и постараться найти это место, если оно действительно существует.";
        	link.l1 = "Хорошо, сделаю. На этот раз мой труд будет оплачен?";
    		link.l1.go = "Step_35";
        	link.l2 = "Слушай, Аскольд, я что, похож"+ GetSexPhrase("","а") +" на гробокопател"+ GetSexPhrase("я","ьницу") +"? В могилах рыться не собираюсь.";
    		link.l2.go = "No_Work";
		break;

 		case "Step_35":
        	dialog.text = "Даже не сомневайся. Это прямое поручение патрона, так что в случае успеха оплата будет.";
        	link.l1 = "Хорошо, я понял"+ GetSexPhrase("","а") +". Буду искать.";
    		link.l1.go = "exit";
    		NextDiag.TempNode = "Seek_Grave";
    		AddQuestRecord("Ascold", "13");
    		CloseQuestHeader("Ascold");
    		pchar.questTemp.Ascold = "Ascold_SeekGrave";
		break;

 		case "Seek_Grave":
        	dialog.text = "Наш"+ GetSexPhrase("ел","ла") +" что-нибудь?";
        	link.l1 = "Пока нет, ищем...";
    		link.l1.go = "exit";
    		NextDiag.TempNode = "Seek_Grave";
            if (pchar.questTemp.Ascold == "Ascold_SeekGrave")
            {
            	dialog.text = "А, добрый день, "+ GetSexPhrase("друг мой","подруга моя") +". Как дела, чем порадуешь?";
            	link.l1 = "Черт возьми, Аскольд, я облазил"+ GetSexPhrase("","а") +" все в округе, но ничего не наш"+ GetSexPhrase("ел","ла") +". Абсолютно ничего.";
        		link.l1.go = "Step_36";
            }
            if (pchar.questTemp.Ascold == "Ascold_CantSeekGrave")
            {
            	dialog.text = "Что скажешь на этот раз? Наш"+ GetSexPhrase("ел","ла") +" что-нибудь?";
            	link.l1 = "Нет, не наш"+ GetSexPhrase("ел","ла") +". Нет здесь никакой гробницы, глупо все это...";
        		link.l1.go = "Step_37";
            }
            if (pchar.questTemp.Ascold == "Ascold_NotEnterFoundGrave")
            {
            	dialog.text = "Как результаты поиска? Есть что-нибудь новенькое?";
            	link.l1 = "Не знаю точно, что это, но я наш"+ GetSexPhrase("ел","ла") +" в пещере вход куда-то, но он закрыт.";
        		link.l1.go = "Step_38";
            }
            if (pchar.questTemp.Ascold == "Ascold_SeekRockLetter" && !CheckCharacterItem(pchar, "Rock_letter"))
            {
            	dialog.text = "Наш"+ GetSexPhrase("ел","ла") +" скрижали?";
            	link.l1 = "Нет пока, но я этим занимаюсь.";
        		link.l1.go = "exit";
            }
            if (pchar.questTemp.Ascold == "Ascold_SeekRockLetter" && CheckCharacterItem(pchar, "Rock_letter"))
            {
            	dialog.text = "А-а-а, вижу по горящим глазам, что скрижали тобой найдены.";
            	link.l1 = "Точно, я наш"+ GetSexPhrase("ел","ла") +" их, каррамба!";
        		link.l1.go = "Step_45";
            }
            if (pchar.questTemp.Ascold == "Ascold_EnterGrave")
            {
            	dialog.text = "Удалось попасть в гробницу?";
            	link.l1 = "Нет еще, но я над этим работаю.";
        		link.l1.go = "exit";
            }
		break;

 		case "Step_36":
        	dialog.text = "Хм, даже не знаю, что сказать.\n"+
                          "Может и никакой гробницы и нет, не знаю... Но все же, если тебе улыбнется удача и ты что-либо найдешь - буду рад тебя видеть.";
        	link.l1 = "Ну что же, попытаюсь еще раз.";
    		link.l1.go = "exit";
    		pchar.questTemp.Ascold = "Ascold_CantSeekGrave";
		break;

 		case "Step_37":
        	dialog.text = "Может и нет, а может и есть... Продолжай искать.";
        	link.l1 = "Хорошо.";
    		link.l1.go = "exit";
		break;

 		case "Step_38":
        	dialog.text = "Ага, кажется ты наш"+ GetSexPhrase("ел","ла") +" то, что ищет де ла Фонтен.\n"+
                          "Черт возьми, я уверен, что именно там и находится искомая гробница. Надо попытаться любой ценой проникнуть внутрь.";
        	link.l1 = "Легко сказать. А как сделать? Видно, что вход есть, но он намертво перегорожен скалой.";
    		link.l1.go = "Step_40";
		break;

 		case "Step_40":
        	dialog.text = "Хм, вот как... Послушай, видимо эта защита захоронений, сродни которой применяли в Египте фараоны, чтобы оградить свои склепы от непрошенных гостей.\n"+
                          "По опыту работы с де ла Фонтеном, а он известный египтолог, могу сказать, что где-то рядом есть механизм, который открывает вход.\n"+
                          "Как правило это некий предмет, который нужно куда-то поместить.";
        	link.l1 = "И что это за предмет? И куда поместить?";
    		link.l1.go = "Step_41";
		break;

 		case "Step_41":
        	dialog.text = "Ну, этого я точно знать не могу. Хотя подожди.\n"+
                          "Де ла Фонтен в своем письме, в котором он дает задание найти гробницу, пишет что есть упоминание о какой-то каменной табличке. Я этому значения не придал, но похоже, это важно.\n"+
                          "Так вот, там упоминается, что путь к Лейфу Счастливому открывают некие скрижали. По-видимому, это и есть искомый предмет.";
        	link.l1 = "А кто такой Лейф Счастливый?";
    		link.l1.go = "Step_42";
		break;

 		case "Step_42":
        	dialog.text = "А я тебе что, не сказал? Это его гробницу ты ищешь.";
        	link.l1 = "Да, дела... Ну так что со скрижалями? Где их искать и куда их помещать?";
    		link.l1.go = "Step_43";
		break;

 		case "Step_43":
        	dialog.text = "Искать их нужно здесь же, в Карибском море. Ты знаешь, мне несут всякое барахло, но ни о каких скрижалях я даже и не слышал. Так что, думается мне, искать надо на необитаемых островах или на западном побережье Мейна, рядом с жемчужными промыслами. А может, где развалины храма, который испанцы нашли. Иначе эти скрижали давно бы нашли и принесли мне на продажу.\n"+
                          "Поместить куда я не знаю, но думаю где-то рядом со входом есть место как раз для этого. Искать надо.";
        	link.l1 = "Интересно. Что ж, пожалуй, займусь розыском этих скрижалей. Надеюсь, что этот вход действительно ведет куда надо.";
    		link.l1.go = "Step_44";
        	link.l2 = "Утомила меня эта беготня без конкретной цели. Ничего я больше искать не буду.";
    		link.l2.go = "No_Work";
		break;

 		case "Step_44":
        	dialog.text = "Очень на это рассчитываю. Что ж, удачи тебе в поиске!";
        	link.l1 = "Спасибо за пожелание.";
    		link.l1.go = "exit";
    		pchar.questTemp.Ascold = "Ascold_SeekRockLetter";
            // ==> Делаем скрижали видимыми, теперь их можно найти.
            sld = ItemsFromID("Rock_letter");
            sld.shown = 1;
		break;

 		case "Step_45":
        	dialog.text = "Задействуй их и попытайся попасть в гробницу.";
        	link.l1 = "Очень надеюсь, что все получится и мой труд не пропадет зря.";
    		link.l1.go = "exit";
			bDisableLandEncounters = true; //закроем энкаунтеров, лучше раньше, чем баги.
    		pchar.questTemp.Ascold = "Ascold_EnterGrave";
		break;

 		case "Found_Grave":
            if (pchar.questTemp.Ascold == "Ascold_FoundMummy")
            {
            	dialog.text = "А, вот и ты, " + GetFullName(pchar) + "! Рассказывай быстрее, что ты наш"+ GetSexPhrase("ел","ла") +".";
            	link.l1 = "Я сумел"+ GetSexPhrase("","а") +" открыть вход в пещеру. В пещере, в одном из ответвлений был вход в гробницу. Я наш"+ GetSexPhrase("ел","ла") +" ее.";
        		link.l1.go = "Step_46";
            }
		break;

 		case "Step_46":
        	dialog.text = "Тысяча чертей! Вот это да! Что-нибудь наш"+ GetSexPhrase("ел","ла") +" внутри?";
        	link.l1 = "Там посредине гробницы стоит каменный саркофаг, закрытый массивной плитой. Отодвинуть плиту я не сумел"+ GetSexPhrase("","а") +", нет ничего подходящего для такого мероприятия.";
    		link.l1.go = "Step_47";
		break;

 		case "Step_47":
        	dialog.text = "Хм, никаких ценностей, предметов погребения и прочей ерунды не было?";
        	link.l1 = "Ничего особенного не было.";
    		link.l1.go = "Step_48";
		break;

 		case "Step_48":
        	dialog.text = "Хм... Значит, все внутри.\n"+
                          "Вот что, возьми-ка вот этот ломик, используй его как рычаг и ты сможешь сдвинуть плиту с саркофага.";
        	link.l1 = "Хм, не уверен"+ GetSexPhrase("","а") +" я, что стоит тревожить мертвеца, что там лежит...";
    		link.l1.go = "Step_49";
		break;

 		case "Step_49":
        	dialog.text = "Хех, ну и ну! Капитан, это всего лишь истлевшие кости. Ты же корсар, тебе ли боятся смерти?";
        	link.l1 = "Ничего я не боюсь. Просто лично мне было бы неприятно, если у меня в могиле какой-нибудь гробокопатель перебирал мои останки.";
    		link.l1.go = "Step_50";
		break;

 		case "Step_50":
        	dialog.text = "Так берешься или нет?";
        	link.l1 = "Берусь, чего уж. Сам"+ GetSexPhrase("ому","ой") +" интересно, что там...";
    		link.l1.go = "Step_51";
		break;

 		case "Step_51":
        	dialog.text = "Ну вот и чудно. Забирай свой лом. Ну и жду тебя с нетерпением.";
           	link.l1 = "Хорошо, Аскольд.";
    		link.l1.go = "exit";
    		pchar.questTemp.Ascold = "Ascold_WateringMummy";
    		GiveItem2Character(Pchar,"Ascold_rabble");
		break;

 		case "AfterAttackMummy":
        	dialog.text = "А, вот и ты. Ты себе представить не можешь, что творилось в городе! Город взяли штурмом ходячие скелеты!!!";
        	link.l1 = "Неужели?! Не может быть!";
    		link.l1.go = "Step_52";
            if (pchar.questTemp.Ascold == "Ascold_SaveWorld")
            {
            	dialog.text = "Ну что, уничожил"+ GetSexPhrase("","а") +" монстра?";
            	link.l1 = "Нет пока, нахожусь в процессе уничтожения.";
        		link.l1.go = "exit";
                NextDiag.TempNode = "AfterAttackMummy";
            }
            if (GetCharacterIndex("LeifEricson") == -1)
            {
            	dialog.text = "Ну, как успехи по спасению мира?";
            	link.l1 = "Да все в порядке, мир спасен, люди могут спать спокойно.";
        		link.l1.go = "Step_60";

				// перебиваем иниты пещеры - возвращаем сферы обратно и закрываем гробницу   - ugeen fix
				locations[FindLocation("Guadeloupe_CaveEntrance")].reload.l1.name = "reload1_back";
				locations[FindLocation("Guadeloupe_CaveEntrance")].reload.l1.emerge = "reload1";

				locations[FindLocation("Guadeloupe_Cave")].reload.l1.name = "reload1_back";
				locations[FindLocation("Guadeloupe_Cave")].reload.l1.emerge = "reload1";
				LocatorReloadEnterDisable("Guadeloupe_Cave", "reload1_back", false);

				RestoreOfficers_Ascold(pchar);
				Log_Info("Проход к гробнице закрылся");
            }
		break;

 		case "Step_52":
        	dialog.text = "Не может?! Они перебили половину гарнизона, а губернатора города напугали так, что тот просто нагадил себе в штаны!\n"+
                          "Во время штурма я забаррикадировался на втором этаже и таким образом избежал проблем. До меня этим ходячим мумиям добраться было непросто...";
        	link.l1 = "Рад"+ GetSexPhrase("","а") +" за тебя... Кстати, ты не желаешь узнать, что там было в склепе?";
    		link.l1.go = "Step_53";
		break;

 		case "Step_53":
        	dialog.text = "В каком склепе?.. А, так ты вскрыл"+ GetSexPhrase("","а") +" его?";
        	link.l1 = "Ага, вскрыл"+ GetSexPhrase("","а") +". Твоя кочерга пригодилась.";
    		link.l1.go = "Step_54";
		break;

 		case "Step_54":
        	dialog.text = "Дьявол! Как только ты уш"+ GetSexPhrase("ел","ла") +", я получил письмо от де ла Фонтена. Он написал, что сумел расшифровать полностью древние манускрипты.\n"+
                          "B них указано, что если открыть каменный гроб, то это пробудит какого-то древнего индейского монстра.";
        	link.l1 = "Так и случилось. Этот монстр и есть та самая проклятая мумия, которую я так долго искал"+ GetSexPhrase("","а") +".";
    		link.l1.go = "Step_55";
		break;

 		case "Step_55":
        	dialog.text = "И что было дальше?";
        	link.l1 = "Дальше я... Ну, в общем, нападение на город скелетов - его рук дело.";
    		link.l1.go = "Step_56";
		break;

 		case "Step_56":
        	dialog.text = "Черт возьми! Доигрались мы с тобой.\n"+
                          "Что нам теперь делать? Этот пробудившийся монстр уничтожит всех на острове.";
        	link.l1 = "Не только на острове. Он собирается стать хозяином мира. Ему и целого мира мало...";
    		link.l1.go = "Step_57";
		break;

 		case "Step_57":
        	dialog.text = "Вот это да... Послушай, звучит глупо, но ты долж"+ GetSexPhrase("ен","на") +" спасти мир.";
        	link.l1 = "А почему я-то? Ты, к примеру, не хочешь спасти мир? Ведь это ты меня туда отправил, да ты и посильней меня будешь.";
    		link.l1.go = "Step_58";
		break;

 		case "Step_58":
        	dialog.text = "Посильней, не спорю. Я лихо с оглоблей управляюсь, а вот шпага - это не мое.\n"+
                          "Ты про пещеру говорил"+ GetSexPhrase("","а") +", там придется идти. И как я буду в стесненном пространстве оглоблей-то махать? Не выйдет у меня.";
        	link.l1 = "Да, точно, не выйдет с оглоблей... Ну что ж, пойду сам"+ GetSexPhrase("","а") +" спасать мир. Деваться некуда.";
    		link.l1.go = "Step_59";
		break;

 		case "Step_59":
        	dialog.text = "Ух, здорово, что ты согласил"+ GetSexPhrase("ся","ась") +". Удачи тебе в этом нелегком деле, "+ GetSexPhrase("друг","подруга") +".";
        	link.l1 = "Спасибо за пожелание, Аскольд. Это мне здорово поможет.";
    		link.l1.go = "exit";
			LocatorReloadEnterDisable("Guadeloupe_Cave", "reload3_back", true);
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_Cave")], false);
			pchar.quest.Ascold_LeifIsDead.win_condition.l1 = "NPC_Death";
			pchar.quest.Ascold_LeifIsDead.win_condition.l1.character = "LeifEricson";
			pchar.quest.Ascold_LeifIsDead.function = "Ascold_LeifIsDead";
			NextDiag.TempNode = "AfterAttackMummy";
    		pchar.questTemp.Ascold = "Ascold_SaveWorld";
			sld = characterFromId("LeifEricson");
            LAi_SetImmortal(sld, false);
            LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_group_MoveCharacter(sld, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		break;

 		case "Step_60":
        	dialog.text = "Здорово. Да-а-а, нелегко тебе было, по всей видимости.\n"+
                          "Слушай, а ты ничего интересного не находил"+ GetSexPhrase("","а") +" там? Скоро де ла Фонтен приедет на остров, будет здорово ему что-нибудь показать.";
        	link.l1 = "Нет, ничего не находил"+ GetSexPhrase("","а")+".";
    		link.l1.go = "Step_61";
            if (CheckCharacterItem(pchar, "Azzy_bottle"))
            {
            	link.l2 = "Лампу какую-то наш"+ GetSexPhrase("ел","ла") +" восточную у этого Лейфа. Не знаю, что это такое.";
        		link.l2.go = "Step_63";
            }
		break;

 		case "Step_61":
        	dialog.text = "Эх, жаль... Послушай, а может еще раз там посмотреть.\n"+
                          "Чувствую, должно там что-то быть полезное для де ла Фонтена. За интересную вещичку можно столько денег получить...";
        	link.l1 = "А теперь послушай меня, Аскольд. Я столько пережил"+ GetSexPhrase("","а") +", выполняя твои поручения, что впечатлений хватит на десяток жизней. Все, хватит, я больше не работаю с тобой.";
    		link.l1.go = "Step_62";
		break;

 		case "Step_62":
        	dialog.text = "Эх, жаль. Но я вижу, что уговаривать тебя бесполезно. Что ж, разойдемся друзьями.";
        	link.l1 = "Ага, пусть будет так.";
    		link.l1.go = "exit";
            NextDiag.TempNode = "GoodFriends";
            pchar.questTemp.Ascold = "Ascold_OverBusiness";
			UnlockAchievement("Mummydust_quest", 3);
		break;

 		case "GoodFriends":
        	dialog.text = "О-о-о, кого я вижу! "+ GetSexPhrase("Старина","Красавица") +" " + GetFullName(pchar) + "! Рад видеть тебя снова. По делу или просто заш"+ GetSexPhrase("ел","ла") +"?";
        	link.l1 = "Просто хотел"+ GetSexPhrase("","а") +" увидеться.";
    		link.l1.go = "exit";
            NextDiag.TempNode = "GoodFriends";
            if (pchar.questTemp.Azzy == "HowToKnowAzzy")
            {
            	link.l1 = "Послушай, у меня к тебе есть дело. Ты случаем не знаешь, как я могу разыскать демона?";
        		link.l1.go = "Step_64";
            }
		break;

 		case "Step_63":
        	dialog.text = "Ну так продай мне ее. 50000 дам за это барахло.";
        	link.l1 = "Внутри там ничего нет, уж больно она легкая... Ладно, забирай, мне она не нужна.";
    		link.l1.go = "BuyAzzy";
        	link.l2 = "Нет, Аскольд, вернусь на корабль, попробую найти, где бы мне аккуратно разрезали или распаяли лампу. Посмотрю, что там внутри.";
    		link.l2.go = "Step_62";
		break;

 		case "BuyAzzy":
        	dialog.text = "Деньги ваши - вещичка наша. Может, поработаем еще вместе? Такие дела нас ждут...";
        	link.l1 = "Нет, Аскольд. С меня хватит приключений такого рода.";
    		link.l1.go = "Step_62";
            TakeItemFromCharacter(pchar, "Azzy_bottle");
            AddMoneyToCharacter(pchar, 50000);
		break;

 		case "Step_64":
        	dialog.text = "Чего?!!";
        	link.l1 = "Нужен мне один демон, найти его никак не могу. А вопрос жизненно важный.";
    		link.l1.go = "Step_65";
		break;

 		case "Step_65":
        	dialog.text = "Ты что, уже с демонами общение наладил"+ GetSexPhrase("","а") +"?!";
        	link.l1 = "Все благодаря тебе, вернее, твоим поручениям! Слушай, может рецепты какие есть вызова демонов, тольтеки вроде имеют такой.";
    		link.l1.go = "Step_66";
		break;

 		case "Step_66":
        	dialog.text = "Есть у них ритуал, даже знаю какой. Гарантии не могу дать, что сработает, но попробовать можно.";
        	link.l1 = "Что за ритуал? Рассказывай!!!";
    		link.l1.go = "Step_67";
		break;

 		case "Step_67":
        	dialog.text = "В общем, три хрустальных черепа тольтеков нужно. У нашего губернатора они были, но помнишь, когда скелеты на город напали, тогда и забрал их главный эти черепа.";
        	link.l1 = "Ах вот, для чего они нужны были Лейфу... Ясно. А дальше что?";
    		link.l1.go = "Step_68";
		break;

 		case "Step_68":
        	dialog.text = "Еще нужен странный предмет, идол древнего божества. Собираешь все три предмета - и ищешь человека, кто сможет провести обряд. Какая-нибудь ведьма местная вполне подойдет.";
        	link.l1 = "Ведьма может? Знаю одну такую даму...";
    		link.l1.go = "Step_69";
		break;

 		case "Step_69":
        	dialog.text = "Вот и здорово. Теперь добудь предметы - и вперед. Полагаю, что с обрядом твоя ведьма знакома, раз она ведьма.";
        	link.l1 = "Полагаю, что да. Кстати, а у тебя ничего нет из этих предметов? Я бы купил"+ GetSexPhrase("","а") +".";
    		link.l1.go = "Step_70";
		break;

 		case "Step_70":
           	dialog.text = "Нет, ничего нет. Так что разыскивай сам"+ GetSexPhrase("","а") +".";
        	link.l1 = "Ну что же, спасибо и на этом. Будь здоров.";
    		link.l1.go = "exit";
            pchar.questTemp.Azzy = "DestrContract";
        	if (sti(pchar.questTemp.Azzy.Immortal.Penalty) >= 15 && GetQuestPastDayParam("questTemp.Azzy") > 90)
        	{
                dialog.text = "Есть. Мне как раз и попали те самые губернаторские черепа. Отыскал их в пещерах, жизнью рисковал...";
                link.l1 = "Я готов"+ GetSexPhrase("","а") +" их у тебя купить за любую цену. Сколько ты хочешь?";
                link.l1.go = "Step_71";
            }
		break;

 		case "Step_71":
        	dialog.text = "С тебя я денег не возьму. Мы ведь с де ла Фонтеном должны тебе еще, сколько ты сделал"+ GetSexPhrase("","а") +" для нас, ожидая награды. Будем считать, что мы в расчете. А черепа забирай.";
        	link.l1 = "Огромное тебе спасибо, Аскольд. Слушай, а странную вещь, идола божества, не находил?";
    		link.l1.go = "Step_72";
            GiveItem2Character(pchar, "sculMa1");
            GiveItem2Character(pchar, "sculMa2");
            GiveItem2Character(pchar, "sculMa3");
            GiveItem2Character(pchar, "indian22");
		break;

 		case "Step_72":
        	dialog.text = "Ну как же, находил. Забирай и ее, какие проблемы?";
        	link.l1 = "Хорошо, очень хорошо. Теперь я готов"+ GetSexPhrase("","а") +" вернуть себе нормальную жизнь. Спасибо тебе, Аскольд.";
    		link.l1.go = "exit";
		break;
	}
}


