// Джекмен на Бермудах
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

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
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
					if (npchar.angry.name == "BlueBird_1") Dialog.CurrentNode = "AngryRepeat_1";
                break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("У тебя дело ко мне? Нет? Тогда вали отсюда!","Ха, " + pchar.name + "! У тебя дело ко мне? Нет? Тогда не отвлекай меня.") +"",
                         "Я кажется ясно выразился.", "Хотя я выразился и ясно, но ты продолжаешь отвлекать меня!",
                         "Та-а-ак, это уже похоже на грубость, меня это утомило.", "repeat", 3, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Уже ухожу.",
                                               "Конечно, Джекмен...",
                                               "Извини, Джекмен...",
                                               "Ой...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			//поиски шебеки Синяя Птица
			if (pchar.questTemp.BlueBird == "toBermudes")
			{
				link.l1 = "Слушай, Джекмен, тут такое дело... В общем, не чалилась ли у тебя в порту шебека 'Синяя Птица'?";
				link.l1.go = "BlueBird_1";
			}
			if (pchar.questTemp.BlueBird == "weWon")
			{
				link.l1 = "Представляешь, я таки отловил"+ GetSexPhrase("","а") +" эту шебеку 'Синяя Птица'!";
				link.l1.go = "BlueBird_6";
			}
			//пиратская линейка начало
			if (pchar.questTemp.piratesLine == "begin" && !CheckAttribute(pchar, "QuestTemp.AndreAbelQuest"))
			{
				link.l1 = "Джекмен, я тут работу ищу какую-нибудь...";
				link.l1.go = "PL_Q1_1";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_toJackman")
			{
				link.l1 = "Я ищу своего друга Эдварда Лоу, Алексус сказал, что он у тебя.";
				link.l1.go = "PL_Q3_1";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_toTavernAgain")
			{
				dialog.text = ""+ GetSexPhrase("Что надо?! Я не в настроении отвечать на твои вопросы!","Что надо, " + pchar.name + "? Я сейчас очень занят...") +"";
				link.l1 = "Кажется, у нас с тобой есть общее дело - Эдвард Лоу.";
				link.l1.go = "PL_Q3_2";
			}
			if (CheckAttribute(pchar,"questTemp.piratesLine.T1") && pchar.questTemp.piratesLine.T1 == "KillLoy_GoodWork" && !CheckAttribute(npchar, "quest.PQ3"))
			{
				dialog.text = "Вернул"+ GetSexPhrase("ся","ась") +"! Да не с пустыми руками!";
				link.l1 = "Готов"+ GetSexPhrase("","а") +" сообщить, что Эдвард Лоу умер с ужасом в глазах и твоим именем в ушах.";
				link.l1.go = "PL_SEAWOLF";
			}
			if (pchar.questTemp.piratesLine == "Panama_backToShip")
			{
				dialog.text = "А, раз тебя видеть, " + pchar.name + ". Ну, что скажешь?";
				link.l1 = "Ты знаешь о том, что сделал Морган в Панаме?";
				link.l1.go = "PL_Q8";
			}
			//жемчужный генератор Шарпа
			if (pchar.questTemp.Sharp == "begin")
			{
				link.l1 = "Послушай, ходят слухи о промысле ловцов жемчуга в Карибском море. Ты ничего не слышал об этом?";
				link.l1.go = "SharpPearl_1";
			}
			//поиски супер-мушкета
			if (CheckAttribute(pchar, "questTemp.mushket2x2") && !CheckCharacterItem(pchar, "mushket2x2"))
			{
				link.l2 = "Слушай, Джекмен, тебе ни о чем не говорит слово 'стрела'? Может быть, одного из твоих парней так кличут, или судно пиратское так называется?";
				link.l2.go = "Mushket";
			}
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "Я по поводу твоего пленника.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.PirateShips"))
				{
					link.l1 = "Здравствуй Джекмен, я по поводу твоего поручения.";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
				{
					link.l1 = "Я по поводу твоего пленника.";
					link.l1.go = "CapComission6";
				}
			}
			if(sti(pchar.rank) >= 10 && !CheckAttribute(PChar, "questTemp.pirateVikingQuest"))
			{
				link.l3 = "Есть какое-нибудь интересное дело для меня?";
				link.l3.go = "pirateVikingQuest";
			}
			else
			{
				if(CheckAttribute(PChar, "questTemp.pirateVikingQuest") && pchar.questTemp.pirateVikingQuest == "7" && npchar.city == pchar.questTemp.pirateVikingQuest.City)
				{
					dialog.text = "Вижу ты с новостями?"
					link.l1 = "Да, завалил"+ GetSexPhrase("","а") +" таки северянина, ох и лютый же был. Обычно все разговоры заводят как смерть почуят, а этот рычал только аж пена изо рта шла.";
					link.l1.go = "pirateVikingQuest_final";
				}
			}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		//Blackthorn. Квест викинга
		case "pirateVikingQuest":
			dialog.text = "Для тебя найдётся работёнка. Ты не только саблей "+ GetSexPhrase("остёр","остра") +", но и умом, как мне рассказывали. Слушай сюда. Появился пару лет назад в наших водах скандинав какой то, то ли датчанин, то ли швед, неважно, Рагнаром назвался. Корабль у него просто загляденье и команда сплошняком из норманов состоит. И вроде как, всё ничего, пиратствует помаленьку, гроши на хлеб зарабатывает, вот только долю в общий котёл не вносит, губернаторам грубит, призы вообще неизвестно где сбывает. Смекаешь к чему разговор?";
			link.l1 = "Смекаю, наказать его нужно, так чтоб примером стал. Вот только это не по законам берегового братства как то. Ну, зарвался пират, так пусть шепнет кто властям где он обитает. И к нам, честным корсарам никаких претензий, никто не предъявит.";
			link.l1.go = "pirateVikingQuest_1";
			link.l2 = "Что-то не нравится мне этот разговор. Прощай...";
			link.l2.go = "exit";
			pchar.questTemp.pirateVikingQuest = "0";
		break;
		case "pirateVikingQuest_1":
			dialog.text = "Законы братства, Кодекс, пиратская честь… Пфф… Детские шалости это. Ты ещё Либерталию вспомни, которую Шарп построить пытался. Ха-ха! Тут у нас баланс сил существует, власти закрывают глаза на наши делишки, если мы их делишкам не мешаем. А вдруг в Европе мир подпишут? Так и патенты отзовут, а все бравые каперы в один миг преступниками станут. И приплывут карательные эскадры. Нас с тобой ловить. А такие капитаны, как этот викинг, репутацию нам всем портят. Смекаешь?";
			link.l1 = "Понял"+ GetSexPhrase("","а") +", дал ты мне пищу для размышлений. Где искать этого викинга?";
			link.l1.go = "pirateVikingQuest_2";
		break;
		case "pirateVikingQuest_2":
			dialog.text = "Где то. Знал бы где обитает, сам бы в море вышел, не посмотрел бы на старые раны и возраст. Ты у нас смекалист"+ GetSexPhrase("ый","ая") +", разберёшься. Одно условие – Рагнар этот и вся его команда на корм рыбам пойти должна, а золотишком я не обижу.";
			link.l1 = "Жди новостей. Да и про отзыв патентов, если новости будут, дай знать. Бывай, "+GetFullName(npchar)+".";
			link.l1.go = "exit";

			pchar.questTemp.pirateVikingQuest = "1";
			pchar.questTemp.pirateVikingQuest.City = npchar.city;
			pchar.questTemp.pirateVikingQuest.Areal = GetArealByCityName(pchar.questTemp.pirateVikingQuest.City);
			pchar.questTemp.pirateVikingQuest.Name = GetFullName(npchar);
			pchar.LastHearedViking = npchar.city;
			AddQuestRecord("pirateVikingQuest", "1");
			AddQuestUserData("pirateVikingQuest", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateVikingQuest.City + "Gen"));
			AddQuestUserData("pirateVikingQuest", "sName", pchar.questTemp.pirateVikingQuest.Name);
		break;
		case "pirateVikingQuest_final":
			CloseQuestHeader("pirateVikingQuest");
			TakeNItems(pchar, "chest", 5);
			Log_Info("Вы получили кредитные сундуки");
			dialog.text = "Ага, читал как то. Берсерк видать. Прямо осколок прошлого. Вот, держи награду, заслужил"+ GetSexPhrase("","а") +".";
			pchar.questTemp.pirateVikingQuest = "end";
			link.l1 = "Спасибо.";
			link.l1.go = "exit";
		break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar) + ", рад тебя видеть! Зачем пожаловал"+ GetSexPhrase("","а") +" на этот раз?",
                         "Ну что тебе еще?", "Долго это будет продолжаться? Если тебе делать нечего, не отвлекай других!",
                         "Ты "+ GetSexPhrase("хороший капер","хорошая девушка") +", поэтому живи пока. Но общаться и разговаривать с тобой я больше не желаю.", "repeat", 10, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Да, собственно, просто так заглянул"+ GetSexPhrase("","а") +", проведать. Ничего по делу нет.",
                                               "Ничего, просто так...",
                                               "Хорошо, Джекмен, извини...",
                                               "Вот черт возьми, доиграл"+ GetSexPhrase("ся","ась") +"!!!", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			//поиски шебеки Синяя Птица
			if (pchar.questTemp.BlueBird == "toBermudes")
			{
				link.l1 = "Слушай, Джекмен, тут такое дело... В общем, не чалилась ли у тебя в порту шебека 'Синяя Птица'?";
				link.l1.go = "BlueBird_1";
			}
			if (pchar.questTemp.BlueBird == "weWon")
			{
				link.l1 = "Представляешь, я таки отловил"+ GetSexPhrase("","а") +" эту шебеку 'Синяя Птица'!";
				link.l1.go = "BlueBird_6";
			}
			if (pchar.questTemp.Sharp == "begin" && rand(1))
			{
				link.l1 = "Послушай, ходят слухи о промысле ловцов жемчуга в Карибском море. Ты ничего не слышал об этом?";
				link.l1.go = "SharpPearl_1";
			}
			//пиратскся линейка начало
			if (pchar.questTemp.piratesLine == "KillLoy_toJackman")
			{
				link.l1 = "Я ищу своего друга Эдварда Лоу, Алексус сказал, что он у тебя.";
				link.l1.go = "PL_Q3_1";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_toTavernAgain")
			{
				dialog.text = ""+ GetSexPhrase("Что надо?! Я не в настроении отвечать на твои вопросы!","Что надо, " + pchar.name + "? Я очень занят...") +"";
				link.l1 = "Кажется, у нас есть с тобой общее дело. Эдвард Лоу.";
				link.l1.go = "PL_Q3_2";
			}
			if (CheckAttribute(pchar,"pchar.questTemp.piratesLine.T1") && pchar.questTemp.piratesLine.T1 == "KillLoy_GoodWork" && !CheckAttribute(npchar, "quest.PQ3"))
			{
				dialog.text = "Вернул"+ GetSexPhrase("ся","ась") +"! Да не с пустыми руками!";
				link.l1 = "Готов"+ GetSexPhrase("","а") +" сообщить, что Эдвард Лоу умер с ужасом в глазах и твоим именем в ушах.";
				link.l1.go = "PL_SEAWOLF";
			}
			if (pchar.questTemp.piratesLine == "Panama_backToShip")
			{
				dialog.text = "А, рад тебя видеть, " + pchar.name + ". Ну, что скажешь?";
				link.l1 = "Ты знаешь о том, что сделал Морган в Панаме?";
				link.l1.go = "PL_Q8";
			}
			//поиски супер-мушкета
			if (CheckAttribute(pchar, "questTemp.mushket2x2") && !CheckCharacterItem(pchar, "mushket2x2"))
			{
				link.l1 = "Слушай, Джекмен, тебе ни о чем не говорит слово 'стрела'? Может быть, одного из твоих парней так кличут, или судно пиратское так называется?";
				link.l1.go = "Mushket";
			}
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "Я по поводу твоего пленника.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}
			if(sti(pchar.rank) >= 10 && !CheckAttribute(PChar, "questTemp.pirateVikingQuest"))
			{
				link.l3 = "Есть какое-нибудь интересное дело для меня?";
				link.l3.go = "pirateVikingQuest";
			}
			else
			{
				if(CheckAttribute(PChar, "questTemp.pirateVikingQuest") && pchar.questTemp.pirateVikingQuest == "7" && npchar.city == pchar.questTemp.pirateVikingQuest.City)
				{
					dialog.text = "Вижу ты с новостями?"
					link.l1 = "Да, завалил"+ GetSexPhrase("","а") +" таки северянина, ох и лютый же был. Обычно все разговоры заводят как смерть почуят, а этот рычал только аж пена изо рта шла.";
					link.l1.go = "pirateVikingQuest_final";
				}
			}
		break;
		//********************* пиратка, направление на квест №1 *********************
		case "PL_Q1_1":
			if(CheckAttribute(NPChar, "notQuestLine"))
			{
				dialog.text = "Поговаривают, что ты у английских властей в большом фаворе. Неужели каперский патент перестал приносить доход?! Не стану я с тобой сотрудничать, слишком велик риск оказаться на виселице в результате твоей работы. Не взыщи...";
				link.l1 = "Ясно... Да я, собственно, просто так спросил"+ GetSexPhrase("","а") +". На всякий случай...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "У меня работы нет. Но если ты ничем не занят"+ GetSexPhrase("","а") +", то отправляйся в Пуэрто-Принсипе -  поищи там капитана Гудли. У него обычно всегда что-то есть.";
				link.l1 = "А что за работа у него бывает?";
				link.l1.go = "PL_Q1_2";
				//LockQuestLine(characterFromId("eng_guber")); // лочим английскую линейку
			}
		break;
		case "PL_Q1_2":
			dialog.text = "Да когда как. Сам"+ GetSexPhrase("","а") +" у него спросишь.";
			link.l1 = "Понятно...";
			link.l1.go = "exit";
			pchar.questTemp.piratesLine = "toFirstQuest";
			AddQuestRecord("Pir_Line_0_Waiting", "2");
		break;
		//********************* пиратка, квест №3, поиски Лоу *********************
		case "PL_Q3_1":
			dialog.text = "Друга?! Хо! Ты удачно заш"+ GetSexPhrase("ел, приятель","ла") +", . Эй, ребята! А ну вали е"+ GetSexPhrase("го","е") +"!!!";
			link.l1 = "Не понял"+ GetSexPhrase("","а") +"!..";
			link.l1.go = "PL_Q3_fight";
		break;
		case "PL_Q3_fight":
			LAi_LocationFightDisable(&Locations[FindLocation("Pirates_townhall")], false);
			chrDisableReloadToLocation = true; // закрыть выход из локации.
            for (i=1; i<=3; i++)
            {
                sld = GetCharacter(NPC_GenerateCharacter("QuestPir_"+i, "pirate_"+i, "man", "man", 100, PIRATE, 0, true));
                FantomMakeCoolFighter(sld, 100, 100, 100, "topor2", "pistol3", 100);
            	LAi_SetWarriorType(sld);
				LAi_SetImmortal(sld, true);
            	sld.Dialog.Filename = "Quest\EngLineNpc_2.c";
                LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
               	ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
            }
            LAi_group_SetLookRadius("PIRATE_CITIZENS", 100);
            LAi_group_SetRelation("PIRATE_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("PIRATE_CITIZENS", LAI_GROUP_PLAYER, false);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "PL_Q3_2":
			dialog.text = "Лоу?! Какие у тебя дела с Лоу?";
			link.l1 = "У меня нет дел с Лоу. Он чем-то досадил Моргану, а мне поручено этот конфликт уладить. Теперь понимаешь, зачем я его ищу?";
			link.l1.go = "PL_Q3_3";
		break;
		case "PL_Q3_3":
			dialog.text = "Хм. Он и Моргану успел подгадить? Нельзя сказать, что я этим сильно расстроен. Но этот проходимец украл мой бриг!";
			link.l1 = "Да, я знаю, мастер на верфи мне всё рассказал.";
			link.l1.go = "PL_Q3_4";
		break;
		case "PL_Q3_4":
			dialog.text = "Да уж, тот еще гусь! У него все мозги опилками припорошены! Это ж надо додуматься, что я ему письма буду писать! Да от моей резиденции до его конуры заяц в два прыжка доскачет! А он приковылял на следующий день! Денежки захотел получить, за то, что бриг проморгал.\nКогда мои молодцы выкидывали этого строгальщика за порог, я ему так и сказал: Не найдется 'Морской Волк' - шкуру живьем спущу и деньги в нее заверну! Чтоб нести легче было.";;
			link.l1 = "Но ведь он очень неплохой мастер, только рассеянный больно...";
			link.l1.go = "PL_Q3_5";
		break;
		case "PL_Q3_5":
			dialog.text = "Да это я так, сгоряча. Не буду я его трогать, никто в здравом уме такими мастерами не разбрасывается. Но я просто в ярости оттого, что у меня украли корабль! А Алексус пусть маленько подрожит, умнее в следующий раз будет.\n" +
				"Значит, говоришь, убить Эдварда Лоу хочешь. Как ты понял"+ GetSexPhrase("","а") +", я тоже этого желаю. Я хочу, чтоб вор знал, за что умирает... Чтобы он знал - от Джекмена безнаказанно не уходят! И чтоб все это знали! Все!!! Поэтому хочу тебя попросить, пусть Лоу знает, что смерть к нему пришла от меня, не от Моргана, а от МЕНЯ! Я думаю ты меня понимаешь.";
			link.l1 = "Хорошо, перед смертью он это услышит. Джекмен, ответь мне на один вопрос.";
			link.l1.go = "PL_Q3_6";
		break;
		case "PL_Q3_6":
			dialog.text = "Какой?";
			link.l1 = "Почему ты так о Моргане отозвался? Вы же вроде друзья.";
			link.l1.go = "PL_Q3_7";
		break;
		case "PL_Q3_7":
			dialog.text = "Хм, друзья... Что ж отвечу, если поймешь... Береговое Братство, Джентльмены Удачи, сокровища, женщины, слава!  Знакомые слова, правда? Когда мы юны и наивны, романтика этих слов манит нас, как мотыльков манит огонь свечи... и мы послушно летим ему навстречу.\n" +
				"Но люди все разные, кто-то из нас кружит рядом, не решаясь приблизиться, кто-то обжегся и летит прочь, кто-то безрассудно сгорает, не рассчитав своих сил. А кто-то, чьи нервы крепки, как шомпол, в этом огне перерождается, и несет его на своей шкуре, обжигая всё вокруг. Хм, я смотрю, ты не понимаешь о чем я... Слышал"+ GetSexPhrase("","а") +", наверное, выражение: 'человек человеку волк'? Так вот, все мы - волчья стая...\n"+"Стая возьмет добычу гораздо крупнее, чем волк-одиночка. Но стаю ведет вожак, которому всегда достаётся кусок добычи больше и волчица слаще. Все волки ему подчиняются, но ждут... ждут, когда он ошибется! Потому что каждый волк хочет кусок добычи побольше и волчицу послаще... Вот такая романтика.";
			link.l1 = "Гхм-да, лучше бы я не спрашивал"+ GetSexPhrase("","а") +". Мотыльки, волки... Кто сильнее - тот и прав. Я был"+ GetSexPhrase("","а") +" и останусь вол"+ GetSexPhrase("ком","чицей") +"-одиночкой. И пусть я добуду меньше, чем стая, зато "+ GetSexPhrase("волчицу себе выберу, какую сам захочу","буду делать то, что сама решу") +".";
			link.l1.go = "PL_Q3_8";
		break;
		case "PL_Q3_8":
			dialog.text = "Ха-ха-ха, ну беги, вол"+ GetSexPhrase("к","чица") +"-одиночка! И возвращайся с добычей!";
			link.l1 = "Жди, скоро буду.";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			AddQuestRecord("Pir_Line_3_KillLoy", "12");
			pchar.questTemp.piratesLine = "KillLoy_2toTavernAgain";
		break;
		//после поисков Лоу
		case "PL_SEAWOLF":
			NextDiag.TempNode = "I_know_you_good";
			npchar.quest.PQ3 = true;
			int chComp;
			bool bOk = false;
			for (int i=0; i<=COMPANION_MAX; i++)
        	{
				chComp = GetCompanionIndex(pchar, i);
                if(chComp != -1 && RealShips[sti(characters[chComp].ship.type)].Name == "BrigSW1")
        		{
					bOk = true;
					break;
				}
			}
			if (bOk)
			{
				dialog.text = "Именно этих слов я и ждал. Вижу, что еще и мой бриг сумел"+ GetSexPhrase("","а") +" прихватить! Молодец. Ты доказал"+ GetSexPhrase("","а") +", что ты – Вол"+ GetSexPhrase("к","чица") +"! Поэтому с чистым сердцем отдаю тебе 'Морского Волка', владей по праву! Хотел бы я иметь "+ GetSexPhrase("такого парня","такую лихую деваху") +", как ты, в своей команде!";
				link.l1 = "Я - свободный капитан, Джекмен. Но твои слова - честь для меня!";
				link.l1.go = "exit";
				AddQuestRecord("Pir_Line_3_KillLoy", "19");
			}
			else
			{
				dialog.text = "Именно этих слов я и ждал. Ну что же, спасибо тебе, "+ GetSexPhrase("приятель","подруга") +". В награду за труды даю тебе 20 тысяч пиастров!";
				link.l1 = "Спасибо, Джекмен! Эти деньги мне пригодятся.";
				link.l1.go = "exit";
				AddMoneyToCharacter(pchar, 20000);
				AddQuestRecord("Pir_Line_3_KillLoy", "20");
				AddQuestUserData("Pir_Line_3_KillLoy", "sSex", GetSexPhrase("","а"));
			}
		break;
		//********************* пиратка, квест №6. двойник *********************
		case "PL_Q6":
			dialog.text = "О-о-о, кого я вижу?! Глазам не верю!";
			link.l1 = "Морган послал к тебе сказать, что капитан Гудли мертв.";
			link.l1.go = "PL_Q6_1";
		break;
		case "PL_Q6_1":
			dialog.text = "Вот так, значит... Новость не из приятных... И как это случилось?";
			link.l1 = "Я убил"+ GetSexPhrase("","а") +" его в резиденции Моргана... Понимаешь, тут история такая неприятная. Я по его поручению убрал"+ GetSexPhrase("","а") +" Джона Эйвори, а оказалось, что это доверенное лицо Моргана.";
			link.l1.go = "PL_Q6_2";
		break;
		case "PL_Q6_2":
			dialog.text = "Эйвори что, тоже мертв?";
			link.l1 = "Угу... В общем, в итоге Гудли на очной ставке у Моргана отказался признать, что это он нанимал меня на Эйвори. Хорошо, что Генри предварительно кое-что выяснил, и мне не пришлось доказывать, что я не верблюд.";
			link.l1.go = "PL_Q6_3";
		break;
		case "PL_Q6_3":
			dialog.text = "Ха, ну дела! А ты не в курсе, что ты еще захватил"+ GetSexPhrase("","а") +" Сида Боннета - одного из моих кэпов, и сдал"+ GetSexPhrase("","а") +" его испанцам?";
			link.l1 = "Я?!!";
			link.l1.go = "PL_Q6_4";
		break;
		case "PL_Q6_4":
			dialog.text = "Да, именно такие ходят слухи. Поэтому я слегка опешил от того, что увидел тебя здесь.";
			link.l1 = "Дьявол!! Этого ещё не хватало!";
			link.l1.go = "PL_Q6_5";
		break;
		case "PL_Q6_5":
			dialog.text = "Отправляйся к заливу Косумель, что северней Белиза. Там у бухты на фрегате 'Антверпен' стоит Джон Лидс, у него там проблемы с командой. Мне кажется, тебе будет очень интересно его навестить...";
			link.l1 = "Хорошо, Джекмен, так и сделаю.";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			SetQuestHeader("Pir_Line_6_Jackman");
			AddQuestRecord("Pir_Line_6_Jackman", "2");
			AddQuestUserData("Pir_Line_6_Jackman", "sSex", GetSexPhrase("","а"));
			pchar.questTemp.piratesLine = "PL6Brother_toSantaCatalina";
			//ставим Джона Лидса в залив Косумель
			sld = GetCharacter(NPC_GenerateCharacter("JohnLids", "officer_10", "man", "man", 30, sti(pchar.nation), -1, true));
			FantomMakeCoolSailor(sld, SHIP_FRIGATE, "Антверпен", CANNON_TYPE_CULVERINE_LBS24, 80, 60, 60);
			sld.name = "Джон";
			sld.lastname = "Лидс";
			sld.dialog.filename   = "Quest\PiratesLine_dialog.c";
			sld.dialog.currentnode   = "First time";
			sld.DeckDialogNode = "JohnLids";
			sld.Abordage.Enable = false;
			sld.AnalizeShips = true;
			sld.AlwaysFriend = true;
			sld.ShipEnemyDisable = true;
			sld.Ship.Mode = "Pirate";
			sld.greeting = "Gr_MiddPirate";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
			Group_AddCharacter("LidsGroup", "JohnLids");
			Group_SetGroupCommander("LidsGroup", "JohnLids");
			Group_SetAddress("LidsGroup", "Beliz", "quest_ships", "Quest_ship_11");
			Group_SetTaskNone("LidsGroup");
		break;

		case "PL_Q6_after":
			dialog.text = "Джон уже рассказал мне о твоей операции с "+ GetSexPhrase("двойником","'сеcтричкой'") +". Тебе удалось узнать что-нибудь конкретное?";
			link.l1 = "Поговорить удалось, да и только. Он"+ GetSexPhrase("","а") +" слишком торопил"+ GetSexPhrase("ся","ась") +", видать, боял"+ GetSexPhrase("ся","ась") +" сболтнуть что-то лишнее.";
			link.l1.go = "PL_Q6_after_1";
		break;
		case "PL_Q6_after_1":
			dialog.text = "Это плохо. За тобой шлейф какой-то тянется, сплошные курьезы. Пока удача на твоей стороне, но стоит тебе оступиться - и тогда конец! Морган тебе не поможет.";
			link.l1 = "Я понимаю. "+ GetSexPhrase("Двойник","'Сестричка'") +" явно что-то знал"+ GetSexPhrase("","а") +"... Надо пытаться выяснить, кто за всем этим стоит.";
			link.l1.go = "PL_Q6_after_2";
		break;
		case "PL_Q6_after_2":
			dialog.text = "Верно. Ну что же, хорошо, что ты ко мне заскочил"+ GetSexPhrase("","а") +", прояснили некоторые важные детали, так сказать. Теперь отправляйся к Моргану, поведай ему о свое"+ GetSexPhrase("м двойнике","й 'сестричке'") +".";
			link.l1 = "Да, было бы неплохо... Скажи, Джекмен, а что ты подумал, когда услышал, что я сдал"+ GetSexPhrase("","а") +" испанцам Сида Боннета?";
			link.l1.go = "PL_Q6_after_3";
		break;
		case "PL_Q6_after_3":
			dialog.text = "Хм, а вот этого тебе лучше не знать... Тебе просто повезло, что Лидс запер "+ GetSexPhrase("двойника","'сестричку'") +" у Белиза, и "+ GetSexPhrase("тот человек","та девка") +", что сдал"+ GetSexPhrase("","а") +" Боннета, не мог"+ GetSexPhrase("","ла") +" появиться здесь так скоро, как появил"+ GetSexPhrase("ся","ась") +" ты.";
			link.l1 = "Понятно. Значит действительно повезло.";
			link.l1.go = "exit";
			SetQuestHeader("Pir_Line_6_Jackman");
			AddQuestRecord("Pir_Line_6_Jackman", "5");
			QuestSetCurrentNode("Henry Morgan", "PL_Q7_begin");
			sld = characterFromId("Henry Morgan");
			LAi_SetHuberTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "PortRoyal_houseS1", "sit", "sit2");
		break;


		//********************* капитан Шарп *********************
		case "SharpPearl_1":
			dialog.text = "Слышал, только ничего об этом толком не знаю. Специализируется на этих промыслах наш всеми любимый и уважаемый капитан Шарп! Это он у нас большой любитель жемчуга, ха-ха-ха!";
			link.l1 = "А где его можно разыскать, этого Шарпа?";
			link.l1.go = "SharpPearl_2";
			pchar.questTemp.Sharp = "seekSharp";
		break;
		case "SharpPearl_2":
			dialog.text = "Не знаю. Капитан Шарп - это неуловимый Джо. Хотя тебе же он понадобился.\nА вообще искать его нужно в борделях.";
			link.l1 = "Спасибо, Джекмен.";
			link.l1.go = "exit";
		break;

        //********************** поиски Синей птицы ***********************
        case "BlueBird_1":
			dialog.text = NPCStringReactionRepeat("М-да, знаменитое стало корыто, что и говорить... А тебе-то зачем понадобилась эта шебека?",
				"Мы уже говорили об этой шебеке.",
				"Опять про то же?",
                "Что?! Опять?! Ну с меня хватит...", "repeat", 10, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Да видишь ли, очень ей интересуются одна группа товарищей...",
				"Да, Джекмен, верно.",
                "Хм, ноты попутал"+ GetSexPhrase("","а") +", пардон...",
				"Ай-ай!..", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("BlueBird_2", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
  		break;
		case "BlueBird_2":
			dialog.text = "Хе-хе, уж не торговцы ли? А то слышал я, что здорово им достается от этой 'Синей Птицы'.";
			link.l1 = "Торговцы действительно интересуются этий шебекой. Но, знаешь, мне и само"+ GetSexPhrase("му","й") +" интересно до жути, что за пернатый такой, от которого уйти нельзя. Это что же идельный каперский парусник по сути своей!";
			link.l1.go = "BlueBird_3";
		break;
		case "BlueBird_3":
			dialog.text = "Ха, это так! Не ты первый, кто на нее целится из Берегового Братства, да вот никто еще не изловил. Что до меня, то лично мне эта 'птица' не интересна - больно мала для серьезных дел.";
			link.l1 = "Джекмен, так ты знаешь, где шебека?";
			link.l1.go = "BlueBird_4";
		break;
		case "BlueBird_4":
			dialog.text = "Нет, конечно. Видеть - видел в окрестных водах, но в порт не заходила.";
			link.l1 = "Может, поделишься соображениями, где искать?";
			link.l1.go = "BlueBird_5";
		break;
		case "BlueBird_5":
			dialog.text = "Нет, думал уже об этом. Ни одной здравой мысли.";
			link.l1 = "Понятно. Ну что ж, спасибо и на этом, приятель.";
			link.l1.go = "exit";
		break;

		case "BlueBird_6":
			dialog.text = NPCStringReactionRepeat("Хм, поздравляю. Большая удача, черт побери! Молодец.",
				"Поздравляю еще раз.",
				"Это я уже слышал...",
                "Ха, да ты хвастун"+ GetSexPhrase("","ишка") +", "+ GetSexPhrase("приятель","подруга") +", каких Карибы еще не видели!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Спасибо, Джекмен. Доброе слово и кошке приятно...",
				"Еще раз спасибо, Джекмен.",
                "А, ну да...",
				"Горжусь этим!", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
        //********************** Английская линейка ***********************
 		case "EngLine_quests":
			dialog.text = "Рад видеть английского капера на моем острове. Что тебе нужно, говори.";
			link.l1 = "У меня есть для тебя работа. Заказчик - генерал-губернатор Ямайки.";
			link.l1.go = "Step_1";
  		break;

 		case "Step_1":
			dialog.text = "Очень интересно, продолжай.";
			link.l1 = "Мэдифорду нужна атака на Кюрасао, а нам не помешают богатства негоциантов этого города. В Кюрасао сейчас много протестантских купцов, которые отказались примерять инквизиторский 'испанский сапожок' и свалили из Испании и Португалии в Голландию. А где негоцианты, там много золота. Предлагаю совместить приятное с полезным.";
			link.l1.go = "Step_2";
  		break;

 		case "Step_2":
			dialog.text = "Хех... Звучит заманчиво, но откажусь.";
			link.l1 = "И в чем причина отказа?";
			link.l1.go = "Step_3";
  		break;

 		case "Step_3":
			dialog.text = "В том, что кроме негоциантов с их золотом, в Кюрасао много голландских солдат с их мушкетами и пушками в амбразурах форта.";
			link.l1 = "Испанские солдаты тебя не сильно пугают...";
			link.l1.go = "Step_4";
  		break;

 		case "Step_4":
			dialog.text = "Меня пугает только состояние своей печени. Но, видишь ли в чем дело, вспороть брюхо испанцу - дело святое, а пустить кровь голландцу - на это я много людей не наберу. Так что без меня.";
			link.l1 = "Может, подумаешь?";
			link.l1.go = "Step_5";
  		break;

 		case "Step_5":
			dialog.text = "Свое слово я сказал. А Мэдифорду передавай от меня привет.";
			link.l1 = "Как знаешь. Всего хорошего.";
			link.l1.go = "exit";

            AddQuestRecord("Eng_Line_2_Talking", "4");
            pchar.questTemp.Count = makeint(sti(pchar.questTemp.Count) + 1);
            if (pchar.questTemp.Count == "4")   {pchar.questTemp.State = "after_talks_with_pirates";}
            NextDiag.TempNode = "First time";
  		break;

 		case "Lets_go_bussines":
			dialog.text = "Рад тебя видеть, " + pchar.name + ". Какими судьбами на Бермудах?";
			link.l1 = "Я по делу. Мы с Морганом атакуем Белиз, ты примешь участие в деле?";
			link.l1.go = "Step_6";
  		break;

 		case "Step_6":
            if (GetCompanionQuantity(pchar) != 4)
            {
    			dialog.text = "Хех, мой корвет стоит на рейде, команда укомплектована, я готов.";
    			link.l1 = "Тогда выступаем немедленно!";
    			link.l1.go = "Step_7";
            }
            else
            {
    			dialog.text = "У вас и без меня комплект, так что без меня на этот раз.";
    			link.l1 = "Ну что ж, как знаешь, будь здоров.";
    			link.l1.go = "exit";
                NextDiag.TempNode = "First time";
            }
  		break;

 		case "Step_7":
			AddQuestRecord("Eng_Line_3_Morgan", "4");
            LAi_SetActorType(npchar);
            LAi_ActorSetStayMode(npchar);
            ChangeCharacterAddressGroup(npchar, "Pirates_townhall", "goto", "governor1");
            CharacterIntoCompanionAndGoOut(pchar, npchar, "reload", "reload1", 10, false);
            Fantom_SetBalls(npchar, "pirate");
            npchar.CompanionEnemyEnable = false;  // нет отпора при обстреле
            pchar.questTemp.CompanionQuantity = makeint(sti(pchar.questTemp.CompanionQuantity) + 1);
            pchar.questTemp.CompanionQuantity.Jackman = true;
            NextDiag.TempNode = "Have_hot_bussines";
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

  		break;

	 	case "Have_hot_bussines":   // Если геймеру вдруг захочется еще пообщаться, не знаю, сможет ли. Но на всякий случай.
			dialog.text = "Черт возьми, время работает против нас!";
            link.l1 = "Поспешим!";
			link.l1.go = "exit";
            NextDiag.TempNode = "Have_hot_bussines";
  		break;

	 	case "Gold_found_in_fort":    // Нода разговора в форте Куманы
            if (CheckAttribute(pchar, "questTemp.CompanionQuantity.Jackman") && !IsCompanion(characterFromID("Jackman")))
    		{
            	dialog.text = "Ты все видел"+ GetSexPhrase("","а") +" - мой корвет был потоплен проклятыми испанцами! Но это не беда, команда почти в полном составе вышла сухой из воды и мы продолжили драться уже на суше."+
                              "А компенсацией за труды нам будет золото. Хех, чертовы испанцы, попытались спрятать золото. Но ты был"+ GetSexPhrase("","а") +" прав"+ GetSexPhrase("","а") +", золото было здесь. Три с лишним тонны золота наше!!!"+
                              "Говорю это, а душа поет. Век бы такие слова говорил.";
            }
            else
            {
    			dialog.text = "Чертовы испанцы, попытались спрятать золото. Но ты был"+ GetSexPhrase("","а") +" прав"+ GetSexPhrase("","а") +", золото было здесь. Три с лишним тонны золота наше!!!"+
                              "Говорю это, а душа поет. Век бы такие слова говорил.";
            }
            link.l1 = "А я век бы слушал"+ GetSexPhrase("","а") +"!";
			link.l1.go = "Step_8";
        break;

	 	case "Step_8":
			dialog.text = "Ха-ха... Ты - хороший корсар, " + pchar.name + " " + pchar.lastname + ". Я желаю тебе удачи, "+ GetSexPhrase("друг","подруга") +".\n"+
                          "Мои головорезы рвутся домой после хорошей работы. Знай, что на Бермудах всегда рады тебя видеть.";
			link.l1 = "Еще увидимся!";
			link.l1.go = "Step_9";
        break;

	 	case "Step_9":
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 15.0);
            DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
        break;
        //********************** Голландская линейка ***********************
 		case "HolLine8_quest":
			dialog.text = "Слушаю тебя, зачем пожаловал"+ GetSexPhrase("","а") +" ко мне?";
			link.l1 = "Я прибыл"+ GetSexPhrase("","а") +" сюда по делу, ищу одного пирата, который пытался продать необычную Библию.";
			link.l1.go = "Step_H8_1";
  		break;
 		case "Step_H8_1":
			dialog.text = "Черт, было что-то... Вспомнить не могу... Но кто-то точно похвалялся редкой книгой, говорил, что христианская...";
			link.l1 = "И что?";
			link.l1.go = "Step_H8_2";
  		break;
 		case "Step_H8_2":
			dialog.text = "Да ничего. Не помню, разговор мельком был... Да и не до Библии нам было - в борделе развлекались, как-никак!";
			link.l1 = "Хм, а в каком борделе?";
			link.l1.go = "Step_H8_3";
  		break;
 		case "Step_H8_3":
			dialog.text = "Что в Форт-де-Франсе.";
			link.l1 = "Понятно... Спасибо, Джекмен.";
			link.l1.go = "exit";
			AddQuestRecord("Hol_Line_8_SeekBible", "3");
			pchar.questTemp.State = "SeekBible_toFFBrothel";
			NextDiag.TempNode = "First time";
  		break;
		//********************* Французская линейка *********************
        case "FraLine8_talk":
            dialog.text = "Надо же, капитан " + GetFullName(pchar) + " пожаловал"+ GetSexPhrase("","а") +"! Весьма рад! Выкладывай – я же вижу, что тебе не терпится сообщить что-то интересное.";
            link.l1 = "В общем, ничего особенно интересного я не предложу. Всего только отказаться от участия в грядущей войне между Англией и Голландией.";
            link.l1.go = "Step_F8_1";
        break;
        case "Step_F8_1":
            dialog.text = "Да уж, действительно ничего интересного. Тем более, что я и сам не собирался впутываться в это дело. Голландев трогать - глупость, на которую пойдет только полный идиот. Так что твои покровители заставили тебя сделать лишний крюк.";
            link.l1 = "Не лишний. По крайней мере, я узнал"+ GetSexPhrase("","а") +" о твоем нейтралитете от тебя лично, а не из третьих рук.";
            link.l1.go = "exit";
			pchar.questTemp.Count = makeint(pchar.questTemp.Count)+1;
			NextDiag.TempNode = "I_know_you_good";
			AddQuestRecord("Fra_Line_8_ThreeCorsairs", "5");
        break;
		//********************* Пиратская линейка *********************
		case "PL_Q8_deck":
			dialog.text = "Ты зря теряешь время у меня на палубе. Нам нужно срочно идти на Порто Белло!";
			link.l1 = "Да, я помню...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_1";
		break;
		case "PL_Q8_deck_1":
			dialog.text = "Хм, опять ты время теряешь, не пойму я тебя...";
			link.l1 = "Все в порядке, не переживай, Джекмен.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_1";
		break;

		case "PL_Q8":
			dialog.text = "Знаю, конечно...";
			link.l1 = "Что скажешь по этому поводу?";
			link.l1.go = "PL_Q8_1";
		break;
		case "PL_Q8_1":
			dialog.text = "Ничего не скажу. Да и вообще, я завязываю с каперством. Так что с этими делами ко мне больше не лезь.";
			link.l1 = "Черт, как же так?!";
			link.l1.go = "PL_Q8_2";
		break;
		case "PL_Q8_2":
			dialog.text = "А вот так! В общем, я свое слово тебе сказал!";
			link.l1 = "Хм, ясно...";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "Panama_inEngland";
		break;
		//поиски супер-мушкета
		case "Mushket":
			dialog.text = "Хм, есть такое судно - очень неплохой бриг, пожалуй, лучший на архипелаге. Только водит его не мой человек, а псих по имени Альберт Зиверт. Если бы я его сразу раскусил - ни за что бы не позволил мастеру Алексусу строить для него такой кораблик.";
			link.l1 = "Чем это он тебе не угодил? Мне его найти нужно.";
			link.l1.go = "Mushket_1";
			DeleteAttribute(pchar, "questTemp.mushket2x2");
		break;
		case "Mushket_1":
			dialog.text = "Здесь я не помощник - он сам по себе. Поговаривают - копит золото, чтоб вернуться в Европу. Я хотел его пристроить к делу, но он пустил на дно двух моих посыльных, и я перестал его искать. А он, естественно, перестал заходить на Бермуды.\nДа и в другие порты тоже - слишком заметный у него бриг, вот и таскает за собой якорь по бухтам, а весь товар меняет на золото у контрабандистов. Так что, никто из моих с ним не якшается, если узнаю - лично на якорь поставлю.";
			link.l1 = "Да уж... Может, посоветуешь что?";
			link.l1.go = "Mushket_2";
		break;
		case "Mushket_2":
			dialog.text = "Искать, когда будешь ходить в море. Смотри внимательно за проходящими кораблями - этот бриг ты точно не пропустишь...";
			link.l1 = "Ясно. Ну что ж, спасибо тебе, Джекмен.";
			link.l1.go = "exit";
			SetMushketCapitainInWorld();
			AddQuestRecord("SeekDoubleMushket", "2");
		break;

		//*************************** Квест "Сопровождение флейта "Орион"" **********************
        case "Andre_Abel_Quest_Jackman_Dialog_1":
			dialog.text = "Что тебе от меня нужно, " + pchar.name + "?";
			link.l1 = "Я по делу, Джекмен...";
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_2";
		break;

		case "Andre_Abel_Quest_Jackman_Dialog_2":
			dialog.text = "Выкладывай, что у тебя за дело.";
			link.l1 = "Даже не знаю как начать... В общем, я думаю, ты помнишь торговца по имени Андре Абель?";
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_3";
		break;

		case "Andre_Abel_Quest_Jackman_Dialog_3":
			dialog.text = "Абель?! Ха-ха... Ну что, одумался этот пройдоха?! Может ты уже привёз"+ GetSexPhrase("","ла") +" от него мою долю?";
			link.l1 = "Нет, не привёз"+ GetSexPhrase("","ла") +". Благодаря твоим стараниям, он сейчас полностью на мели, и просит прекратить его преследовать. Даже подумывает совсем свернуть дело.";
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_4";
		break;

		case "Andre_Abel_Quest_Jackman_Dialog_4":
			dialog.text = "А кто мне помешает его преследовать? Ты?! Думаешь, я не знаю, что он сменил корабль и торчит сейчас в Порт-о-Принсе?! Решил, что может меня надуть?!\nКороче, пусть даже не надеется улизнуть. Я не успокоюсь, пока не получу всё, что мне причитается.";
			link.l1 = "Ну что ж, решать, конечно, тебе."+ GetSexPhrase(" Только не забывай, что Земля круглая, а море большое...","") +"";
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_5";
		break;

		case "Andre_Abel_Quest_Jackman_Dialog_5":
			dialog.text = ""+ GetSexPhrase("Что ты сказал?! Ты что, пытаешься мне угрожать в моей же резиденции?!\nРебята, а ну-ка вышвырните этого молодчика к чёртовой матери отсюда!","Ну конечно же мне, а кому еще! У тебя все, или еще что сказать хочешь?") +"";
			link.l1 = ""+ GetSexPhrase("Что ты, Джекмен? Какие угрозы? Просто напомнил, что на всё воля Провидения.","Все. Бывай, Джекмен.") +"";
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_6";
		break;

		case "Andre_Abel_Quest_Jackman_Dialog_6":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DoFunctionReloadToLocation("Pirates_town", "reload", "reload3", "Andre_Abel_Quest_After_First_Jackman_Dialog");
		break;

		case "Andre_Abel_Quest_Jackman_Dialog_7":
			dialog.text = "Опять ты? Если не привёз"+ GetSexPhrase("","ла") +" денег от Абеля, то лучше сразу разворачивайся оверштаг и не зли меня.";
			link.l1 = "Денег не привёз"+ GetSexPhrase("","ла") +", зато привёз"+ GetSexPhrase("","ла") +" письмо от Моргана.";
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_8";
		break;

		case "Andre_Abel_Quest_Jackman_Dialog_8":
			dialog.text = "Хм, письмо от Моргана? Ну так давай его сюда!";
			link.l1 = "Держи...";
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_9";
		break;

		case "Andre_Abel_Quest_Jackman_Dialog_9":
			dialog.text = "Дьявол! опять этот Абель?! \nЛадно, пусть живёт покамест, у меня появились дела поважнее.";
			link.l1 = "Вот и отлично.";
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_10";
			TakeItemFromCharacter(PChar, "letter_1");
		break;

		case "Andre_Abel_Quest_Jackman_Dialog_10":
			dialog.text = "Только передай "+ GetSexPhrase("своему дружку","ему") +", что я обид не прощаю! Так что пусть не попадается мне на глаза, если жить хочет..."+ GetSexPhrase(" А теперь проваливай, вместе со своим Абелем!","") +"";
			link.l1 = "Всё передам, как есть. "+ GetSexPhrase("Счастливо оставаться","Пока, Джекмен") +".";
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_11";
		break;

		case "Andre_Abel_Quest_Jackman_Dialog_11":
			DialogExit();
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddQuestRecord("Andre_Abel_Quest", "22");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("","а"));
			PChar.QuestTemp.Andre_Abel_Quest_Complete = true;
		break;

		//*************************** Генератор "Поручение капитана - Выкуп" **********************
		case "CapComission1":
			dialog.text = "Хо-хо. Ты думаешь, у меня только одни пленник? Называй, кого конкретно имеешь в виду?";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName + ". Есть такой?";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "Был. Я его продал к чёртовой матери этому плантатору с Барбадоса - полковнику Бишопу, он заезжал на прошлой неделе.";
				link.l1 = "Вот чёрт...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "А-а, ну наконец-то. Я уж было подумывал продать его к чёртовой матери этому плантатору с Барбадоса, он должен появиться у меня через неделю-другую... Ты выкуп привез"+ GetSexPhrase("","ла") +"?";
				link.l1 = "Слушай, Джекмен, тут такое дело... В общем, у меня нет таких денег. Но я готов"+ GetSexPhrase("","а") +" отработать.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "Хорошо, что не продал. Вот деньги - 150000 золотых. Где я могу его забрать?"
					link.l2.go = "CapComission2_3";
				}
			}
		break;

		case "CapComission2_1":
			dialog.text = "Долго ты телил"+ GetSexPhrase("ся","ась") +"... А кстати, этот невольник к тебе каким боком? Я, помнится, его родственникам выкуп назначал.";
			link.l1 = "Да я по поручению этих родственников и приехал"+ GetSexPhrase("","а") +".";
			link.l1.go = "CapComission2_11";
		break;

		case "CapComission2_11":
			dialog.text = "Ну, опоздал"+ GetSexPhrase("","а") +" ты - что я могу поделать?";
			link.l1 = "Слушай, а за сколько продал, если не секрет?";
			link.l1.go = "CapComission2_12";
		break;

		case "CapComission2_12":
			dialog.text = "Э-э, не секрет, конечно, но я тебе не скажу. А то смеяться будешь, ха-ха-ха-ха... Ну, бывай.";
			link.l1 = "Счастливо.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;

		case "CapComission2_2":
			if(rand(1) == 0)
			{
				dialog.text = "Гхм-гхм... Есть у меня одно дело... Даже не знаю, как начать... В общем, нужно пустить ко дну одного зарвавшегося пирата.";
				link.l1 = "А разве нельзя убрать его в джунглях?";
				link.l1.go = "CapComission2_2_1";
			}
			else
			{
				dialog.text = "Ну, " + pchar.name + ", ты же знаешь, что так дела не делаются. Приходи с деньгами и получишь своего заморыша, хе-хе.";
				link.l1 = "Ну ладно, до встречи.";
				link.l1.go = "CapComission2_4";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "Ну, понимаешь ли, так серьёзные дела не делаются... Мне не смерть его нужна, мне нужно отбить охоту у слишком ретивых разевать рот на мою часть добычи. Хотя, если он отправится к осьминогам - я не огорчусь.";
			link.l1 = "А почему тебе не послать за ним своих людей?";
			link.l1.go = "CapComission2_2_2";
		break;

		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Abl");
			dialog.text = "Хм... В общем некий " + GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.UnknownPirateName, NAME_NOM) + " убедил часть пиратов, что в нашем тайнике близ " + XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Gen") + " есть и их доля. Недавно они снялись с якоря и на двух судах '" + pchar.GenQuest.CaptainComission.ShipName1 + "' и '" + pchar.GenQuest.CaptainComission.ShipName2 + "' ушли к " + sLoc + ". Понимаешь теперь, почему я не могу поручить это дело своим людям?";
			link.l1 = "Понятно. И сколько у меня есть времени?";
			link.l1.go = "CapComission2_2_3";
		break;

		case "CapComission2_2_3":
			dialog.text = "Думаю, дней 12-15, не больше. Мне важно, чтоб они не успели добраться до тайника, иначе топить их с ценным грузом на борту не будет смысла. Уж лучше пусть везут его сюда.";
			link.l1 = "Хорошо, я берусь за это дело. Постараюсь успеть.";
			link.l1.go = "CapComission2_2_4";
		break;

		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Abl"));
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Dat"));
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips";
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			pchar.GenQuest.CaptainComission.PirateShips = "goaway";
			DialogExit();
		break;

		case "CapComission2_3":
			dialog.text = "Не переживай. Мои люди доставят его к тебе на борт. А он тебе кто?";
			link.l1 = "Никто. Я выполняю поручение его родственника.";
			link.l1.go = "CapComission2_31";
		break;

		case "CapComission2_31":
			dialog.text = "А-а, это хорошо. А то я уж было расстроился, что продешевил, назначив такую низкую цену за твоего человека. Ха-ха-ха-ха... Ну, бывай.";
			link.l1 = "Счастливо.";
			link.l1.go = "CapComission2_32";
		break;

		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));
			addMoneyToCharacter(pchar, -150000);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;

		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			}
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;
			DialogExit();
		break;

		case "CapComission3":
			dialog.text = "Ну что, " + GetFullName(pchar) + ", пустил"+ GetSexPhrase("","а") +" на дно моего приятеля?.. хе-хе-хе...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "Нет. Я не успел"+ GetSexPhrase("","а") +" их догнать. И на обратном пути они мне не попадались.";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")
			{
				link.l1 = "Да, как и договаривались - отправил"+ GetSexPhrase("","а") +" кормить акул.";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;

		case "CapComission4":
			dialog.text = "Чёрт! Попадались - не попадались, какая теперь разница?.. Ну, и что ты предложишь дальше?";
			link.l1 = "Может, у тебя есть какое-нибудь поручение попроще?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Слушай, Джекмен, уступи мне этого пленника подешевле...";
			link.l2.go = "CapComission4_2";
		break;

		case "CapComission4_1":
			dialog.text = "Нет.";
			link.l1 = "...Ну, тогда счастливо оставаться...";
			link.l1.go = "CapComission4_3";
		break;

		case "CapComission4_2":
			dialog.text = "Подешевле?!! Только что из-за твоей нерасторопности я лишился своего тайника! И теперь я могу уступить его подороже! Забирай за 200000, если хочешь.";
			link.l1 = "Дорого это... Прощай...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "А чёрт, держи свои деньги.";
				link.l2.go = "CapComission4_5";
			}
		break;

		case "CapComission4_3":
			ChangeCharacterReputation(pchar, -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","ла"));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;

		case "CapComission4_4":
			ChangeCharacterReputation(pchar, -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;

		case "CapComission4_5":
			dialog.text = "Можешь забрать заморыша...";
			link.l1 = "Счастливо оставаться.";
			link.l1.go = "CapComission4_6";
		break;

		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;

		case "CapComission5":
			dialog.text = "Хо-хо! Вот это работа! Забирай своего заморыша и бывай здоров"+ GetSexPhrase("","а") +".";
			link.l1 = "Спасибо. Счастливо оставаться.";
			link.l1.go = "CapComission5_1";
		break;

		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;

		case "CapComission6":
			dialog.text = "Ты выкуп привез"+ GetSexPhrase("","ла") +"? Ведь я не шутил, когда сказал, что продам его плантаторам.";
			link.l1 = "Слушай, "+ NPChar.name +", тут такое дело... В общем, у меня нет таких денег. Но я готов"+ GetSexPhrase("","а") +" отработать.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Хорошо, что не продал. Вот деньги - 150000 золотых. Где я могу его забрать?"
				link.l2.go = "CapComission2_3";
			}
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Грабеж среди бела дня!!! Это что же такое делается?! Ну, погоди, "+ GetSexPhrase("приятель","подруга") +"...", "Эй, ты чего это там копаешься?! Никак, вздумал"+ GetSexPhrase("","а") +" ограбить меня? Ну, тогда тебе конец...", "Постой, ты куда это полез"+ GetSexPhrase("","ла") +"? Да ты вор"+ GetSexPhrase("","овка") +", оказывается! Ну, считай, что ты приплыл"+ GetSexPhrase("","а") +", родн"+ GetSexPhrase("ой","ая") +"...");
			link.l1 = LinkRandPhrase("Дьявол!!", "Каррамба!!", "А-ать, черт!");
			link.l1.go = "PL_Q3_fight";
		break;

		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+ GetSexPhrase("Пошел вон","Убирайся") +" отсюда!", "Вон из моего дома!");
			link.l1 = "Ай...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Джекменом через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Тебе не стоит отвлекать меня от дела пустыми обращениями. Впредь результат может быть более плачевным...";
        			link.l1 = "Я понял"+ GetSexPhrase("","а") +".";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("Ты меня изрядно утомил"+ GetSexPhrase("","а") +", никакого общения.", "Я не хочу с тобой общаться, так что тебе лучше меня не беспокоить.");
			link.l1 = RandPhraseSimple("Ну как знаешь...", "Хм, ну что же...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Джекменом через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Надеюсь, впредь ты не будешь утомлять меня пустыми разговорами, иначе мне придется тебя убить. Признаюсь, мне это будет очень неприятно.";
        			link.l1 = "Джекмен, ты можешь быть уверен - не буду...";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Pirates_town","reload","reload3");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
	}
}
void SetMushketCapitainInWorld()
{
	//создаем кэпов
	int Rank = sti(pchar.rank) + 15;
	if (Rank > 30) Rank = 30;
	if (MOD_SKILL_ENEMY_RATE == 10 && bHardAnimations) ref sld = GetCharacter(NPC_GenerateCharacter("MushketCap", "officer_17", "man", "spy", Rank, PIRATE, -1, true));
	else sld = GetCharacter(NPC_GenerateCharacter("MushketCap", "officer_17", "man", "man_fast", Rank, PIRATE, -1, true));
	sld.name = "Альберт";
	sld.lastname = "Зиверт";
 	SetCaptanModelByEncType(sld, "pirate");
	FantomMakeCoolSailor(sld, SHIP_BRIGQEEN, "Стрела", CANNON_TYPE_CULVERINE_LBS24, 100, 100, 100);
	FantomMakeCoolFighter(sld, 20, 50, 50, "blade34", "pistol2", 50);
	sld.Ship.Mode = "pirate";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	sld.WatchFort = true; //видеть форты
	if (bHardBoss) sld.AlwaysReload = true;//перезарядка независимо от Дозарядки
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//в морскую группу кэпа
	string sGroup = "MushketCapShip";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation));
	sld.quest = "InMap"; //личный флаг искомого кэпа
	sld.city = "PortRoyal"; //определим колонию, из бухты которой с мушкетом выйдет
	sld.cityShore = GetIslandRandomShoreId(GetArealByCityName(sld.city));
	sld.quest.targetCity = SelectAnyColony(sld.city); //определим колонию, в бухту которой он придет
	sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	pchar.questTemp.Mushket.Shore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	Log_TestInfo("Кэп с мушкетом вышел из: " + sld.city + " и направился в: " + sld.quest.targetShore);
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "Бриг 'Стрела'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+5; //дней доехать даем с запасом
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "mushket"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = "SeekDoubleMushket"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "SeekDoubleMushket"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}
