// Соукинс в Пуэрто-Принсипе
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            dialog.text = "У тебя дело ко мне? Нет? Тогда "+ GetSexPhrase("вали отсюда","попрошу не отвлекать меня.") +"";
			link.l1 = "Уже ухожу.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (pchar.questTemp.piratesLine == "Soukins_toPuertoPrincipe")
			{
				link.l1 = "Ричард, слышал"+ GetSexPhrase("","а") +" я, что ты собираешь людей для акции против испанцев. Я хотел"+ GetSexPhrase("","а") +" бы принять в этом участие.";
				link.l1.go = "PL_Q7_1";
			}


			if(!CheckAttribute(PChar, "questTemp.pirateStartQuest"))
			{
				link.l2 = "Может какая работенка для меня найдется?";
				link.l2.go = "pirateStartQuest";
			}
			else
			{
				if(pchar.questTemp.pirateStartQuest == "3" && !CheckAttribute(PChar, "questTemp.pirateStartQuest.many") && npchar.city == pchar.questTemp.pirateStartQuest.City)
				{
					link.l2 = "Я выш"+ GetSexPhrase("ел","ла") +" на след, но мне нужны деньги - 30 000 пиастров, чтобы выманить крысу из норы.";
					link.l2.go = "pirateStartQuest_many";
				}
				if(pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "letter_open") > 0 && npchar.city == pchar.questTemp.pirateStartQuest.City)
				{
					link.l2 = "Посмотри, что за письмо я наш"+ GetSexPhrase("ел","ла") +" на трупе одного из контрабандистов.";
					link.l2.go = "pirateStartQuest_info_1";
				}
				if(pchar.questTemp.pirateStartQuest == "5" && npchar.city == pchar.questTemp.pirateStartQuest.City)
				{
					link.l2 = "Дело сделано. Норман Виго вместе со своей лоханкой отправился к морскому дьяволу.";
					link.l2.go = "pirateStartQuest_final";
				}
			}
			if(sti(pchar.rank) >= 10 && !CheckAttribute(PChar, "questTemp.pirateVikingQuest"))
			{
				link.l3 = "Есть какое-нибудь интересное дело для меня?";
				link.l3.go = "pirateVikingQuest";
			}
			else
			{
				if(pchar.questTemp.pirateVikingQuest == "7" && npchar.city == pchar.questTemp.pirateVikingQuest.City)
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

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
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

		//zagolski. начальный квест за пирата ===================================
		case "pirateStartQuest":
			dialog.text = "Хм... работенка, говоришь? А это даже очень хорошо, что ты ко мне обратил"+ GetSexPhrase("ся","ась") +". Мне как раз нужен человек со стороны. Необходимо кое-что разузнать в соседнем поселении, а моих ребят там знают, как облупленных. Много денег не обещаю, но кое-что перепадет.";
			link.l1 = "Вот и славно. А что за дело?";
			link.l1.go = "pirateStartQuest_1";
			link.l2 = "Извини, за копейки я рисковать не буду. Прощай...";
			link.l2.go = "exit";
			pchar.questTemp.pirateStartQuest = "0";
		break;
		case "pirateStartQuest_1":
			dialog.text = "А дело в следующем - с месяц назад сговорился я с капитаном шхуны 'Сентблу' о доставке 200 рабов, чтобы продать их одному плантатору из соседнего поселения. Уже и сроки поджимать стали, и заказчик нервничать, и вот вчера мне сообщают, что эту шхуну видели в акватории острова. Но!.. капитан у меня не появился. А сегодня плантатор потребовал вернуть задаток и сказал, что рабов ему предложили в другом месте - хоть и дороже, но всю партию и сразу.";
			link.l1 = "И что? Я долж"+ GetSexPhrase("ен","на") +" в считанные дни раздобыть 200 рабов, чтоб ты не потерял задаток? И все это за копейки?";
			link.l1.go = "pirateStartQuest_2";
		break;
		case "pirateStartQuest_2":
			dialog.text = "Нет, конечно. Разве я похож на идиота? Задаток я не верну в любом случае. Но мне нужны доказательства, что рабы, которых ему подсовывают - это и есть моя партия. А ты просто найдешь тех, кто предложил ему новую сделку, и получишь свои 10 000 пиастров. Остальное моя забота. Ну что, берешься?";
			link.l1 = "Берусь! А кто это может быть? Есть какие-то соображения?";
			link.l1.go = "pirateStartQuest_3";
			link.l2 = "Нет. Искать непонятно кого, непонятно где и всего за 10 000 - извини, не возьмусь.";
			link.l2.go = "exit";
		break;
		case "pirateStartQuest_3":
			dialog.text = "Если бы у меня был хоть намек, я обошелся бы и без твоих услуг. Они бы уже к ночи ловили кальмаров на живца. Но меня больше интересует другое - как они узнали о грузе 'Сентблу' и о моем заказчике? Уж очень все быстро у них срослось. Смекаешь?";
			link.l1 = "Да, явно кто-то приторговывает сведениями.";
			link.l1.go = "pirateStartQuest_4";

			pchar.questTemp.pirateStartQuest = "1";
			pchar.questTemp.pirateStartQuest.City = npchar.city;
			pchar.questTemp.pirateStartQuest.Areal = GetArealByCityName(pchar.questTemp.pirateStartQuest.City);
			pchar.questTemp.pirateStartQuest.Name = GetFullName(npchar);

			AddQuestRecord("pSQ", "1");
			AddQuestUserData("pSQ", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City + "Gen"));
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);
		break;
		case "pirateStartQuest_4":
			dialog.text = "Вот! Вот его и ищу. Поэтому тихо прирезать конкурентов и вернуть рабов - в этом деле не главное. Мне нужен информатор, а вернее - его голова на вертеле. Теперь ты понимаешь, почему никто из моих об этом задании знать не должен? Пока я не выясню, кто продает информацию - подозревать буду каждого. А мне этого очень не хочется...";
			link.l1 = "Понятно... Значит, будем действовать тихо и не поднимать волну. Отправляюсь на поиски.";
			link.l1.go = "exit";
		break;

		case "pirateStartQuest_many":
			dialog.text = "Тридцать тысяч, говоришь? Это большая сумма... Могу дать только 5000 пиастров, больше у меня сейчас нет. Но если вздумаешь сбежать с ними - найду и повешу на ближайшем заборе! Со мной такие шутки не пройдут.";
			link.l1 = "Давай пять тысяч...";
			link.l1.go = "pirateStartQuest_many_1";
		break;
		case "pirateStartQuest_many_1":
			dialog.text = "Вот, держи. Жду результаты поиска.";
			link.l1 = "Все будет в порядке.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			pchar.questTemp.pirateStartQuest.many = "";
		break;

		//------------------------------------
		case "pirateStartQuest_info_1":
			dialog.text = "Ха! Отличная новость! Я был уверен, что ты с этим справишься. Ко мне попала весьма любопытная информация.";
			link.l1 = "Я работу свою выполнил"+ GetSexPhrase("","а") +". Хочу получить свои десять тысяч.";
			link.l1.go = "pirateStartQuest_info_2";
			TakeItemFromCharacter(pchar, "letter_open");
		break;
		case "pirateStartQuest_info_2":
			dialog.text = "Конечно, вот обещанная награда. Но ты не спеши, я хочу поручить тебе еще одно дело\nПфайфер - это человек из команды Нормана Виго, который ходит на люггере 'Септима'. Я уверен, что Норман Виго и есть информатор, хотя он и из наших. Его недавно видели в акватории острова, твоя работа - отправить крысу к морскому дьяволу. В первый раз ты меня не подвел"+ GetSexPhrase("","а") +", поэтому и сейчас хочу поручить это дело тебе. Заплачу 15 000 пиастров. Соглас"+ GetSexPhrase("ен","на") +"?";
			link.l1 = "Берусь! Считай, что предатель Норман Виго уже покойник.";
			link.l1.go = "pirateStartQuest_info_3";
			link.l2 = "Знаешь что, неохота мне в это ввязываться... Да и некогда. Извини, но я пас.";
			link.l2.go = "pirateStartQuest_info_noex";
			AddMoneyToCharacter(pchar, 10000);
		break;
		case "pirateStartQuest_info_noex":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
		break;
		case "pirateStartQuest_info_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "4";

			AddQuestRecord("pSQ", "7");
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Areal;
			pchar.quest.zpq_seaBattle.function = "pirateStartQuest_seaBattle";
		break;

		case "pirateStartQuest_final":
			dialog.text = "Знаем-знаем. Мои люди наблюдали бой и уже доложили мне, как ты здорово управил"+ GetSexPhrase("ся","ась") +". Ну что ж, дело свое ты исправно сделал"+ GetSexPhrase("","а") +", вот обещанная награда в 15 000 пиастров. И спасибо тебе, здорово ты мне помог"+ GetSexPhrase("","ла") +".";
			link.l1 = "Все в порядке, рад"+ GetSexPhrase(" был","а была") +" помочь! А теперь меня ждут дела, я и так здесь задержал"+ GetSexPhrase("ся","ась") +". До встречи!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			group_DeleteGroup("pirateStartQuest_Smuggler_group");
		break;

		//пиратка, квест №7
		case "PL_Q7_1":
			dialog.text = "Назови свое имя.";
			link.l1 = GetFullName(pchar) + ".";
			link.l1.go = "PL_Q7_2";
		break;
		case "PL_Q7_2":
			dialog.text = "Хе-хе, а не "+ GetSexPhrase("прихвостень ли ты Моргана, приятель","ты ли подружка Моргана, а") +"?";
			link.l1 = "Я работаю на Генри, при чем тут "+ GetSexPhrase("прихвостень","'подружка'") +"?";
			link.l1.go = "PL_Q7_3";
		break;
		case "PL_Q7_3":
			dialog.text = "А при том, что ты мне не подходишь. Эй, на вахте! Ну-ка, все сюда! Валите эту шестерку...";
			link.l1 = "Ну зачем ты так?..";
			link.l1.go = "fight";
			LAi_SetPlayerType(pchar);
			pchar.questTemp.piratesLine = "Soukins_FightinResidence";
			for (i=1; i<=5; i++)
			{
				iTemp = 10 + rand(10);
				sld = GetCharacter(NPC_GenerateCharacter("questPirate_"+i, "pirate_"+i, "man", "man", 25, PIRATE, 10, true));
				FantomMakeCoolFighter(sld, 25, 70, 70, "blade26", "pistol6", 20);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
				LAi_group_MoveCharacter(sld, npchar.chr_ai.group);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			}
		break;
		case "PL_Q7_5":
			dialog.text = "Какого это дьявола ты сюда вваливаешься без приглашения?!! А-а-а, я, кажется, знаю тебя... Эй, на вахте, Ну-ка, все сюда! Валите "+ GetSexPhrase("этого прихвостня","эту морганскую подстилку") +"!";
			link.l1 = "Эй-эй, что за дела?!";
			link.l1.go = "fight";
			LAi_SetPlayerType(pchar);
			pchar.questTemp.piratesLine = "Soukins_FightinResidence";
			for (i=1; i<=5; i++)
			{
				iTemp = 10 + rand(10);
				sld = GetCharacter(NPC_GenerateCharacter("questPirate_"+i, "pirate_"+i, "man", "man", 25, PIRATE, 10, true));
				FantomMakeCoolFighter(sld, 25, 70, 70, "blade26", "pistol6", 20);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
				LAi_group_MoveCharacter(sld, npchar.chr_ai.group);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			}
		break;
		//пиратка, квест №8
		case "PL_Q8_deck":
			dialog.text = "И как это Морган умудрился поставить "+ GetSexPhrase("такого оболтуса","девку") +" в командование эскадрой? Ума не приложу...";
			link.l1 = "Хм, зря ты так, Ричард.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_1";
		break;
		case "PL_Q8_deck_1":
			dialog.text = "Ну вот, опять ты. О чем я и говорю!";
			link.l1 = "Ты за меня не переживай.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_1";
		break;

		case "PL_Q8_deck_2":
			dialog.text = "Ну и что ты опять делаешь у меня на палубе? Думаешь, если ты удачно провел"+ GetSexPhrase("","а") +" штурм Порто Белло, то теперь можно пав"+ GetSexPhrase("лином","ой") +" тут разгуливать?";
			link.l1 = "Пав"+ GetSexPhrase("лины","ы") +"-то тут при чем?..";
			link.l1.go = "PL_Q8_deck_3";
		break;
		case "PL_Q8_deck_3":
			dialog.text = "Слушай, ш"+ GetSexPhrase("ел","ла") +" бы ты отсюда... Мне с тобой не о чем говорить. Все решится в Панаме, пусть каждый там и покажет, на что он способен.";
			link.l1 = "Ты это о чем?";
			link.l1.go = "PL_Q8_deck_4";
		break;
		case "PL_Q8_deck_4":
			dialog.text = "Я тебе отчета давать не намерен, ты мне другом не являешься. Так что убирайся отсюда к чертям собачьим.";
			link.l1 = "Ну ладно, я пош"+ GetSexPhrase("ел","ла") +". Не хочешь разговаривать - как хочешь...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_5";
			npchar.DeckDialogNode = "PL_Q8_deck_5";
		break;
		case "PL_Q8_deck_5":
			dialog.text = "Я не желаю с тобой говорить!";
			link.l1 = "Хм, ну это понятно...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_5";
			npchar.DeckDialogNode = "PL_Q8_deck_5";
		break;
		//в бухте Дарьенский залив
		case "Shore48":
			dialog.text = "Ну что же, до залива мы добрались. Теперь нужно двигаться через джунгли. Я и мои люди готовы, можем выступать.";
			link.l1 = "Хорошо, я понял"+ GetSexPhrase("","а") +" тебя.";
			link.l1.go = "Shore48_1";
		break;
		case "Shore48_1":
			LAi_LocationFightDisable(&Locations[FindLocation("Shore48")], false);
			chrDisableReloadToLocation = false;
			LAi_SetWarriorTypeNoGroup(npchar);
			NextDiag.TempNode = "Shore48_over";
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "Shore48_over":
			dialog.text = "Чего мы ждем? Давай, двигай свою задницу к Панаме!!";
			link.l1 = "Хм, это конечно...";
			link.l1.go = "exit";
		break;
		//после штурма у стен Панамы
		case "PQ8_exitTown":
			dialog.text = "Что тебе нужно?";
			link.l1 = "Послушай, я знаю, что тебе неприятно будет это услышать, но Морган приказал мне убить тебя, когда мы шли через джунгли.";
			link.l1.go = "PQ8_exitTown_1";
		break;
		case "PQ8_exitTown_1":
			dialog.text = "И ты думаешь я тебе поверю?";
			link.l1 = "Можешь не верить, но это правда.";
			link.l1.go = "PQ8_exitTown_2";
		break;
		case "PQ8_exitTown_2":
			dialog.text = "Ты не раз лез"+ GetSexPhrase("","ла") +" в мои дела, портил"+ GetSexPhrase("","а") +" мои замыслы. Ты - "+ GetSexPhrase("шестерка","подстилка") +" Моргана. И теперь хочешь пошестерить на меня, что ли?";
			link.l1 = "Да пошел ты, Ричард... Идиот!";
			link.l1.go = "PQ8_exitTown_3";
		break;
		case "PQ8_exitTown_3":
			dialog.text = "Я-то, конечно, пойду... в Панаму. А вот ты в город не войдешь. Так что вали отсюда, пока цел"+ GetSexPhrase("","а") +"...";
			link.l1 = "Дьявол!..";
			link.l1.go = "exit";
			LAi_warrior_DialogEnable(npchar, false);
		break;
	}
}
