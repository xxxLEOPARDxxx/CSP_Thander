
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;
	ref shTo;

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

		case "First time":
			dialog.text = "Приветствую тебя, "+ GetSexPhrase("брат","сестра") +"!";
			link.l1 = "Как"+ GetSexPhrase("ой","ая") +" я тебе "+ GetSexPhrase("брат","сестра") +"? Ты же явно полукровка-индеец. И что это ты в таких лохмотьях?";
			link.l1.go = "Meeting_1";
			NextDiag.TempNode = "First time";
		break;

        case "Meeting_1":
			dialog.text = "Моя ошибся? Ты белый человек, я белый, мое имя даже 'Белый Мальчик'. Одежда - память о предках, я носить ее, как смочь одеть, давно.";
			link.l1 = "Ну да, не девочка точно, только лет тебе явно уже за мальчика перевалило, а ума так и нет. Зачем всю жизнь ходить в лохмотьях?";
			link.l1.go = "Meeting_2";
		break;

		case "Meeting_2":
			dialog.text = "Твоя не понимай. Я сын дочери главный шаман и белый капитан большой корабль. Я носить так, чтоб духи не видеть меня и не забрать к себе.";
			link.l1 = "В общем, очередной юродивый, ясно все. Ты продаешь жемчуг?";
			link.l1.go = "Meeting_3";
		break;

		case "Meeting_3":
			dialog.text = "Жемчуг я покупать.";
			link.l1 = "Покупать или продавать? У тебя есть?";
			link.l1.go = "Meeting_4";
		break;

		case "Meeting_4":
			dialog.text = "Нет, сейчас нет, а нужно.";
			link.l1 = "Запутал ты меня, точно юродивый. Прощай.";
			link.l1.go = "Exit";
			NextDiag.TempNode = "AfterMeet";
			ReOpenQuestHeader("GhostShipQuest");
        	AddQuestRecord("GhostShipQuest", "4");
		break;

		case "AfterMeet":
			dialog.text = "Белый "+ GetSexPhrase("брат","сестра") +" вернулся. Есть что сказать?";
			link.l1 = "Нет, нам не о чем говорить.";
			link.l1.go = "Exit";
			NextDiag.TempNode = "AfterMeet";
			bOk = (sti(PChar.GenQuest.GhostShip.KillMe) > 0) || (sti(PChar.GenQuest.GhostShip.DeadByMe) > 0);
			if (bOk && !CheckAttribute(pchar , "GenQuest.GhostShip.NeedCoins"))
            {
    			Link.l3 = "Что ты знаешь о корабле-призраке?";
    			Link.l3.go = "GhostCapt";
			}
			if (GetCharacterItem(Pchar, "Coins") >= 666 && CheckAttribute(pchar , "GenQuest.GhostShip.NeedCoins"))
			{
                Link.l4 = "Я принес"+ GetSexPhrase("","ла") +" твои жемчужины.";
    			Link.l4.go = "quest_coin_2";
			}
		break;

		// корабль
		case "GhostCapt":
			NextDiag.TempNode = "AfterMeet";
			dialog.Text = "Большой корабль? Плавать долго-долго вокруг, раньше быть простым, потом стать призрак с черным парусом.";
			Link.l1 = "Когда и как он появился?";
			Link.l1.go = "GhostCapt_1";
		break;

		case "GhostCapt_1":
			dialog.Text = "Ошибка, а может, злой дух капитана посетил. Они были тут 40 зим назад, жили и торговали в мире. Капитан сильно обидеть племя, взять мою мать силой, разграбить нас, похитить священный черный жемчуг.";
			Link.l1 = "Хм... Нормальное дело, ну, а корабль-призрак как возник?";
			Link.l1.go = "GhostCapt_2";
		break;

		case "GhostCapt_2":
			dialog.Text = "Я все объяснить уже. Ты не слушать? Наш вождь потребовал жизнь капитана в знак примирения, матросы поддержали капитана и корабль уплыть далеко, далеко. Тогда шаман нашего народа проклял капитана и корабль.";
			Link.l1 = "Проклятие казалось мне чем-то плохим. Как они обрели могущество и бессмертие?";
			Link.l1.go = "GhostCapt_3";
		break;

		case "GhostCapt_3":
			dialog.Text = "Они и страдать, сильно страдать. Получаться все не так, могущество священных жемчужин защищать их, они будут мучаться, пока не вернется все обратно. Я стоять здесь с рождения и собирать обратно наш жемчуг, менять на белый, они продавать, я искать.";
			Link.l1 = "По-моему, страдают от этого проклятия больше другие люди. Порезали бы им глотки ночью - и всех дел. Как снять с них бессмертие?";
			Link.l1.go = "GhostCapt_4";
		break;

		case "GhostCapt_4":
			dialog.Text = "Осталось мало, они уже почти все потратить, я собрать все, что было, осталось совсем мало, нужно 666 черных жемчужин с их корабля. Тогда проклятие обернется правильной стороной.";
			Link.l1 = "Хорошо, жди меня и я вернусь!";
			Link.l1.go = "Exit";
			AddQuestRecord("GhostShipQuest", "5");
			PChar.GenQuest.GhostShip.NeedCoins = true;
		break;

		case "quest_coin_2":
            dialog.Text = "Замечательно. Ты спасти всех нас! Скорее давай их. Тебе остается только еще раз встретить корабль и сломать его или взять боем. На этом их пути конец. Теперь они стать просто пираты, без черного паруса.";
			Link.l1 = "Хорошо. Забирай их.";
			Link.l1.go = "Exit";
			TakeNItems(pchar, "Coins", -666);
			AddQuestRecord("GhostShipQuest", "6");
			AddQuestUserData("GhostShipQuest", "sSex", GetSexPhrase("","а"));
			PChar.GenQuest.GhostShip.LastBattle = true;
			NPChar.location = "none";
			NPChar.LifeDay = 0;
            NextDiag.TempNode = "temp_coins";
		break;

		case "temp_coins":
            dialog.Text = "Спасибо, друг.";
			Link.l1 = "Надеюсь, все будет, как ты обещал.";
			Link.l1.go = "Exit";
			NextDiag.TempNode = "temp_coins";
		break;

		case "GhostCapt_Prize":
			dialog.text = "Приветствую тебя, " + GetSexPhrase("юноша","леди") + "! Давненько в нашем болоте не появлялись такие отважные и умелые капитаны."
			link.l1 = "Ты кто?! И откуда здесь взялся?";
			link.l1.go = "GhostCapt_Prize1";
		break;

		case "GhostCapt_Prize1":
			dialog.text = "Да... немногие, даже из тех, кто видел меня живым, узнали бы сейчас старину Дейви Джонса...";
			link.l1 = "Так ты и есть легендарный капитан 'Летучего Голландца' Дейви Джонс?!";
			link.l1.go = "GhostCapt_Prize2";
		break;

		case "GhostCapt_Prize2":
			dialog.text = "Хо-хо! нет, "+ GetSexPhrase("юноша","леди") +", я его жалкое подобие, вернее - то, что от него осталось...\n " +
				"Ну, да ладно, ближе к делу - как это ты не испугал"+ GetSexPhrase("ся","ась") +" моего красавца? Да ещё умудрил"+ GetSexPhrase("ся","ась") +" наделать в нём столько дырок, что отправил"+ GetSexPhrase("","а") +" в пасть кальмарам, ха-ха... " +
				"Ладно, я не в обиде - ничего с ним не сделается, завтра снова на плаву будет. Хотя, признай, что тебе изрядно повезло, если бы не то ядро под ватерлинию - барахтал"+ GetSexPhrase("ся","ась") +" бы ты сейчас, как креветка на мелководье, ха-ха-ха... " +
				"и уже завтра состави"+ GetSexPhrase("л","ла") +" компанию моим ребятам. А я бы с удовольствием взял тебя в команду - первым помощником. Не желаешь?";
			link.l1 = "Нет уж, не для того я так старал"+ GetSexPhrase("ся","ась") +", чтоб после боя отправиться на тот свет. У меня здесь ещё дел по горло.";
			link.l1.go = "GhostCapt_Prize21";
		break;

		case "GhostCapt_Prize21":
			dialog.text = "Ну, раз такая твоя судьба - живи... пока. А, признай - я тебя тоже неплохо отделал, хо-хо-хо... " +
				"Эх, если бы не то ядро под самую ватерлинию... Уважил"+ GetSexPhrase("","") +" старика. Есть тут у меня несколько мыслишек, как отблагодарить тебя в ответ. Пожалуй, отдам-ка я тебе этот оберег. ''Ионой'' его кличут знающие люди. Коли владеешь им, никакой шторм тебе уже не будет страшен. Держи, не бойся, не проклятая вещь.";
				Log_Info("Вы получили оберег ''Иона''.");
				AddItems(pchar, "talisman2", 1);
				pchar.questTemp.IonaGathered = true;
			link.l1 = "Потрясающе! Благодарю от всего сердца.";
			link.l1.go = "GhostCapt_Prize3";
		break;

		case "GhostCapt_Prize3":
			dialog.text = "А чего это ты на такой лоханке ходишь? Что там у вас, совсем разучились хорошие корабли строить? "+ GetSexPhrase("Такой смелый и удачливый капитан, неубоявшийся","Такая смелая и удачливая морячка, неубоявшаяся") +" схватиться с самим кораблём-призраком, досто"+ GetSexPhrase("ин","йна") +" управлять лучшим судном на всём архипелаге! Хочешь, я это дело поправлю?";
			link.l1 = "Что? Своего 'Голландца' предложить хочешь?";
			link.l1.go = "GhostCapt_Prize4";
		break;

		case "GhostCapt_Prize4":
			dialog.text = "Го-го-го! Да ты и сам"+ GetSexPhrase("","а") +" его не возьмёшь, не по зубам он тебе... Нет уж - это мой крест... А я, в качестве награды за отвагу, могу улучшить ходовые характеристики твоему судну. Выбирай, что пожелаешь.";
			link.l1 = "Для меня главное это скорость. Без неё любой корабль, как плавучая мишень.";
			link.l1.go = "GhostCapt_upgrade1";
			link.l2 = "Манёвренность в корабле - самое важное. С нею от любого бортового залпа увернуться можно.";
			link.l2.go = "GhostCapt_upgrade2";
			link.l3 = "По мне, так скорость в бейдевинд даёт кораблю главные преимущества. При хорошем ходе в бейдевинд для капитана нет плохого ветра, все пути открыты.";
			link.l3.go = "GhostCapt_upgrade3";
			link.l4 = "Благодарю, но мой кораблик меня вполне устраивает! Потопил же он твоего хвалёного 'Голландца'.";
			link.l4.go = "GhostCapt_noupgrade";
		break;

		case "GhostCapt_upgrade1":
			dialog.text = "Ну, как пожелаешь, скорость - так скорость.\nЛадно, пора мне. Я и так у тебя засиделся. Редко, знаешь ли, доводится вот так с живым человеком посудачить... И это... если будешь на западном Мейне, найди там, в деревушке ловцов жемчуга Белого Мальчика - передай привет...";
			link.l1 = "Что так и сказать, мол привет тебе от покойного капитана 'Летучего Голландца', мистера Дейви Джонса?";
			link.l1.go = "GhostCapt_Prize5";
			shTo = &RealShips[sti(pchar.Ship.Type)];
			shTo.Tuning.GhostShip = true;
			GetBaseShipParam_ToUpgrade(shTo, "SpeedRate");
		break;

		case "GhostCapt_upgrade2":
			dialog.text = "Ну, как пожелаешь, манёвренность - так манёвренность.\nЛадно, пора мне. Я и так у тебя засиделся. Редко, знаешь ли, доводится вот так с живым человеком посудачить... И это... если будешь на западном Мейне, найди там, в деревушке ловцов жемчуга Белого Мальчика - передай привет...";
			link.l1 = "Что так и сказать, мол привет тебе от покойного капитана 'Летучего Голландца', мистера Дейви Джонса?";
			link.l1.go = "GhostCapt_Prize5";
			shTo = &RealShips[sti(pchar.Ship.Type)];
			shTo.Tuning.GhostShip = true;
			GetBaseShipParam_ToUpgrade(shTo, "TurnRate");
		break;

		case "GhostCapt_upgrade3":
			dialog.text = "Ну, как пожелаешь, бейдевинд - так бейдевинд.\nЛадно, пора мне. Я и так у тебя засиделся. Редко, знаешь ли, доводится вот так с живым человеком посудачить... И это... если будешь на западном Мейне, найди там, в деревушке ловцов жемчуга Белого Мальчика - передай привет...";
			link.l1 = "Что так и сказать, мол привет тебе от покойного капитана 'Летучего Голландца', мистера Дейви Джонса?";
			link.l1.go = "GhostCapt_Prize5";
			shTo = &RealShips[sti(pchar.Ship.Type)];
			shTo.Tuning.GhostShip = true;
			GetBaseShipParam_ToUpgrade(shTo, "WindAgainstSpeed");
		break;

		case "GhostCapt_noupgrade":
			dialog.text = "Ишь как"+ GetSexPhrase("ой","ая") +"! Расхрабрил"+ GetSexPhrase("ся","ась") +". Говорю же - повезло тебе, "+ GetSexPhrase("сосунку","соплячке") +". Я вот своим канонирам-то хвосты понакручу, в другой раз одним бортовым на дно отправлю!..\nЛадно, пора мне. Я и так у тебя засиделся. Редко, знаешь ли, доводится вот так с живым человеком посудачить... "+
				"И это... если будешь на западном Мейне, найди там, в деревушке ловцов жемчуга Белого Мальчика - передай привет...";
			link.l1 = "Что так и сказать, мол привет тебе от покойного капитана 'Летучего Голландца', мистера Ван-дер-Декена?";
			link.l1.go = "GhostCapt_Prize5";
		break;

		case "GhostCapt_Prize5":
			dialog.text = "Хм, действительно... ладно, не нужно ничего... Если суждено сбыться, то и без привета сбудется... Прощай... Да не попадайся мне больше - в другой раз не спущу...";
			link.l1 = "Рад" + GetSexPhrase("","а") + " был"+ GetSexPhrase("","а") +" знакомству с легендарным капитаном.";
			link.l1.go = "GhostCapt_PrizeExit";
		break;

		case "GhostCapt_PrizeExit":
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "GhostShipCapInCabinDied", 5.0);
			LAi_LockFightMode(pchar, false);
			DoQuestCheckDelay("OpenTheDoors", 5.0);
			InterfaceStates.Buttons.Save.enable = true;
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;

		case "GhostCapt_LastDialog":
			dialog.text = "А-а, " + GetSexPhrase("старый знакомец","старая знакомая") + "! А ведь я тебя ждал - знал, что найдёшь разгадку...";
			link.l1 = " Я " + GetSexPhrase("пришел","пришла") + " освободить тебя и твоих людей от проклятия. Твоё время вышло - пора на покой, гроза морей и капитан призрака Дейви Джонс.";
			link.l1.go = "GhostCapt_LastDialog1";
		break;

		case "GhostCapt_LastDialog1":
			dialog.text = "Знаю, знаю... Такие упрямые, как ты, всегда своего добиваются. Сам когда-то таким был... " +
				"Только не нужно выставлять себя спасител"+ GetSexPhrase("ем","ьницей") +". Я привык быть, мне это даже иногда нравится, и расставаться с существованием, пусть призрачным, я не тороплюсь. Поэтому и не думай, что я сдамся так просто!";
			link.l1 = "Я к этому готов"+ GetSexPhrase("","а") + ". Да и кораблик твой мне больно уж приглянулся.";
			link.l1.go = "GhostCapt_LastDialog2";
		break;

		case "GhostCapt_LastDialog2":
			dialog.text = "Вот этому верю охотно, а то "+ GetSexPhrase("''пришёл освободить''","''пришла освободить''") + " - ишь, благодетель"+ GetSexPhrase("","ница") + ". Только право быть капитаном корабля-призрака нужно ещё заслужить. Пока я его капитан, и буду защищать свой корабль, как это предписано законами моря... Хотя... если проиграю, то расстраиваться не стану...";
			link.l1 = "Готовься к последнему бою, старый убийца! Да упокоит океан твою грешную душу...";
			link.l1.go = "GhostCapt_LastDialog3";
		break;

		case "GhostCapt_LastDialog3":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
	}
}

void GetBaseShipParam_ToUpgrade(ref shTo, string param)
{
	string sAttr = "Bonus_"+param;
	int iRealShipType = sti(shTo.basetype);
	string sParam =	GetBaseShipParamFromType(iRealShipType, param);
	float paramValue = stf(sParam)/10*3;
	if(CheckAttribute(shTo, sAttr))
	{
		shTo.(param) = stf(shTo.(param)) - stf(shTo.(sAttr));
		shTo.(sAttr) = stf(shTo.(sAttr)) + paramValue;
		shTo.(param) = stf(shTo.(param)) + stf(shTo.(sAttr));
	}
	else
	{
		shTo.(sAttr) = paramValue;
		shTo.(param) = stf(shTo.(param)) + stf(shTo.(sAttr));
	}
}
