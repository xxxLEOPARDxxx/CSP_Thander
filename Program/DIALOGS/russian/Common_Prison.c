
void ProcessDialogEvent()
{
	int amount, iGunQty, iGunGoods, iGunPrice, iTemp;
	int iTest;
	ref NPChar, sld;
	ref arItem;
	ref rColony;
	aref Link, NextDiag;
	string sTemp;
	float locx, locy, locz;
	bool  ok;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Prison\" + NPChar.City + "_Prison.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		//---------------- Начальник тюрьмы ------------------
		case "First_officer":
		if (rand(2) == 0 && GetNpcQuestPastDayWOInit(npchar, "questPrisonGun") > 365 && !CheckAttribute(pchar, "questTemp.PrisonGun"))
				{
					dialog.text = RandPhraseSimple(RandPhraseSimple("Послушайте, у меня к вам есть одно важное дело. Надеюсь, сумеете помочь...","Капитан, а не заинтересует ли вас некоторое весьма прибыльное предложение?"), RandPhraseSimple("Я тут подумал, что вы могли бы нам помочь в одном весьма важном вопросе.","Капитан, у меня к вам есть одно деликатное предложение, которое может быть выгодным для нас обоих."));
					link.l1 = "Излагайте, попробуем решить...";
					link.l1.go = "GiveTaskGun";
					npchar.quest.PrisonGun = "Target";
					SaveCurrentNpcQuestDateParam(npchar, "questPrisonGun");
					break;
				}

			dialog.text = RandPhraseSimple("Я начальник тюрьмы. Что вам нужно здесь?", "Что вам нужно? Зачем вы явились в тюрьму?");
			link.l1 = "Да ничего особенного, осматриваю город, знаете ли. Вот и забрел"+ GetSexPhrase("","а") +" сюда по случаю.";
			link.l1.go = "exit";
			link.l2 = "Хочу поговорить по делу.";
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakFort"))
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l2.go = "F_ShipLetters_1";
				}
				else
				{
					link.l2.go = "quests";
				}
			}
			else
			{
				if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
				{
					link.l2.go = "ReasonToFast_Prison1";
				}
				else
				{
					link.l2.go = "quests";
				}
			}

			if (!sti(pchar.questTemp.jailCanMove))
			{
				link.l4 = "Я хочу пройти внутрь тюрьмы.";
				link.l4.go = "ForGoodMove";
			}
			if (CheckAttribute(pchar, "questTemp.jailCanMove.City") && npchar.city == pchar.questTemp.jailCanMove.City)
			{
				link.l5 = "Послушайте, не подскажете мне, за какое преступление сидит здесь заключенный по имени " + GetFullName(characterFromId(pchar.questTemp.jailCanMove.prisonerId)) + "?";
				link.l5.go = "KnowAboutPrisoner";
			}

			if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
			{
				if(!CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
				{
					bool zMsm = (CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour")) && (!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"));
					if(pchar.GenQuest.CaptainComission == "MayorTalkBad" || zMsm) //говорил с губером и отказался или узнал слухи, но не говорил с губером
					{
						link.l6 = "До меня дошли слухи, что бывший капитан патрульного " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " содержится у вас под стражей. Могу я с ним переговорить?";
						link.l6.go = "CapComission_PrisonBad1";
					}
					if(pchar.GenQuest.CaptainComission == "MayorTalkGood")
					{
						link.l6 = "Я " + GetFullName(pchar) + ", действую от имени и по поручению губернатора " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen") + ". Мне нужно переговорить с бывшим капитаном " + pchar.GenQuest.CaptainComission.Name + ".";
						link.l6.go = "CapComission_PrisonGood1";
					}
				}
			}

			if (CheckAttribute(pchar, "questTemp.PrisonGun") && pchar.questTemp.PrisonGun.Id == npchar.location)
			{
				link.l8 = "Я по поводу вашего заказа на поставку орудий.";
				link.l8.go = "CheckGun";
			}

			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "fort_keeper"  && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "Я по поводу вашей дочери...";
						link.l9.go = "EncGirl_1";
					}
				}
			}

			if(CheckAttribute(pchar,"UnexpectedInheritanceFort") && npchar.id == "FortFranceJailOff")
			{
				link.lUnexpectedInheritance = "Месье, у меня вопрос к Вам, он может показаться странным, но всё же...";
				link.lUnexpectedInheritance.go = "UnexpectedInheritance";
			}

			if(CheckAttribute(pchar,"LambriniPGGInPrison") && CheckAttribute(pchar,"LambriniPGGPlata") && npchar.id == "MaracaiboJailOff")
			{

				link.lLambriniPGGInPrison = "Сеньор, я принимал"+ GetSexPhrase("","а") +" участие в недавнем налёте на контрабандистов. Мне передали, что арестованных держат здесь. Могу я попросить вас об освобождении одной особы? Под мою ответственность, разумеется.";
				link.lLambriniPGGInPrison.go = "LambriniPGGInPrison";
			}
			NextDiag.TempNode = "First_officer";
		break;

		case "LambriniPGGInPrison":
			dialog.Text = "О ком идёт речь?";
			Link.l1 = "Кажется, её имя "+GetFullName(CharacterFromID(pchar.LambriniPGG))+".";
			Link.l1.go = "LambriniPGGInPrison_1";
		break;
		case "LambriniPGGInPrison_1":
			dialog.Text = ""+GetFullName(CharacterFromID(pchar.LambriniPGG))+"? Дайте мне минуту, я ознакомлюсь со списком заключённых.";
			Link.l1 = "Да, конечно, я подожду.";
			Link.l1.go = "LambriniPGGInPrison_2";
		break;
		case "LambriniPGGInPrison_2":
			dialog.Text = "Хм... "+GetFullName(CharacterFromID(pchar.LambriniPGG))+"... "+GetFullName(CharacterFromID(pchar.LambriniPGG))+"... Ага, нашёл. Владелица контрабандной партии сандала. Её штраф составляет 25000 золотых.";
			if (sti(pchar.money) >= 25000)
			{
				Link.l1 = "Вот ваши деньги.";
				Link.l1.go = "LambriniPGGInPrison_3";
			}
			Link.l2 = "Ну и расценки у вас... Мне надо подумать.";
			Link.l2.go = "LambriniPGGInPrison_3_1";
		break;
		case "LambriniPGGInPrison_3":
			AddMoneyToCharacter(pchar, -25000);
			DeleteAttribute(pchar,"LambriniPGGPlata")
			dialog.Text = "Вот и славно. Сейчас её к вам приведут.";
			Link.l1 = "";
			Link.l1.go = "LambriniPGGInPrison_4";
		break;
		case "LambriniPGGInPrison_3_1":
			dialog.Text = "Если надумаете - приходите. Только советую думать быстрее, мало ли что может здесь случиться через пару дней. Это ваша подружка, не моя.";
			Link.l1 = "";
			Link.l1.go = "exit";
		break;
		case "LambriniPGGInPrison_4":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = CharacterFromID(pchar.LambriniPGG);
			ChangeCharacterAddressGroup(sld, "Maracaibo_prison", "goto", "goto20");
			LAi_SetStayTypeNoGroup(sld);
			sld.talker = 10;
			sld.dialog.currentnode   = "LambriniPGG_2_1";
		break;

		case "UnexpectedInheritance":
			dialog.Text = "Слушаю Вас.";
			Link.l1 = "Дело в том, что мне стало известно о находках на территории форта необычных индейских идолов. Мой наниматель – коллекционер и не жалеет денег на языческие побрякушки, если вы понимаете о чем я.";
			Link.l1.go = "UnexpectedInheritance_1";
		break;
		case "UnexpectedInheritance_1":
			dialog.Text = "Прекрасно вас понимаю капитан, в метрополии мода пошла на всю эту экзотику и перекупщики сейчас платят сущие гроши за находки, планируя нажиться. Действительно, солдаты, выполнявшие земляные работы, обнаружили кое – что интересное.";
			Link.l1 = "Мой наниматель не стеснён в деньгах. 12 тысяч вас устроит?";
			Link.l1.go = "UnexpectedInheritance_2";
		break;
		case "UnexpectedInheritance_2":
			dialog.Text = "Ваш наниматель иудей? 25 тысяч и не песо меньше.";
			Link.l1 = "Мой наниматель француз и дворянин. 16. По рукам?";
			Link.l1.go = "UnexpectedInheritance_3";
		break;
		case "UnexpectedInheritance_3":
			dialog.Text = "Француз? Дворянин? Ну что же, соотечественнику уступлю за 18 тысяч жалких песо.";
			if (sti(pchar.money) >= 18000)
			{
				Link.l1 = "Прошу месье, ваши деньги. Оревуар!";
				Link.l1.go = "UnexpectedInheritance_4";
			}
			else
			{
				Link.l1 = "Хм... У меня с собой столько нет. Я загляну к вам позже.";
				Link.l1.go = "exit";
			}
		break;
		case "UnexpectedInheritance_4":
			dialog.Text = "Благодарю, в сундуке ещё были какие то бумаги, возьмите.";
			Log_Info("Вы получили пергамент с текстом на латыни и половинку карты");
			Log_Info("Вы получили церемониальный сосуд");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("UnexpectedInheritance", "10");
			TakeNItems(pchar,"indian21", 1);
			DeleteAttribute(pchar,"UnexpectedInheritanceFort");
			pchar.quest.UnexpectedInheritanceTerks.win_condition.l1 = "location";
			pchar.quest.UnexpectedInheritanceTerks.win_condition.l1.location = "Terks_Grot";
			pchar.quest.UnexpectedInheritanceTerks.function = "UnexpectedInheritanceTerks";
			Link.l1 = "Любопытно...";
			Link.l1.go = "exit";
		break;

		case "GiveTaskGun":
			dialog.Text = LinkRandPhrase("Дело в том, что орудия нашего форта изрядно изношены. Казна, правда, выделила деньги на их замену, но приобретать новые нынче очень дорого. Вот я и подумал, что корабельные орудия с абордированных вами призов могли быть здесь очень кстати.","Мне нужно заменить орудийную батарею форта. Деньги на это выделены, но, знаете ли... хочется как-то подешевле... Ну, надеюсь, вы меня понимаете.","Мне пришло предписание заменить изношенные орудия форта, но с ними такая беда - нигде не могу собрать достаточного количества.");
			Link.l1 = "Хм, а можно подробнее - калибр, количество... цена, наконец.";
			Link.l1.go = "GiveTaskGun_1";
			pchar.questTemp.PrisonGun = true;
			SaveCurrentQuestDateParam("pchar.questTemp.PrisonGun");
		break;

		case "GiveTaskGun_1":
			GetGunType();
			//iGunPrice = sti(pchar.questTemp.PrisonGun.Price);
			//iGunQty = pchar.questTemp.PrisonGun.Qty;
			pchar.questTemp.PrisonGun.Sum = makeint(sti(pchar.questTemp.PrisonGun.Price)*sti(pchar.questTemp.PrisonGun.Qty));
			pchar.questTemp.PrisonGun.Luck = rand(4);
			pchar.questTemp.PrisonGun.Id = npchar.location;
			//sText = pchar.questTemp.PrisonGun.Text;
			dialog.Text = "Мне необходимы "+ pchar.questTemp.PrisonGun.Text +", в количестве ровно " + sti(pchar.questTemp.PrisonGun.Qty) + " штук. Заплатить готов " + FindRussianMoneyString(sti(pchar.questTemp.PrisonGun.Sum)) + " золотом, это выйдет по "+ sti(pchar.questTemp.PrisonGun.Price) +" пиастров за каждую. Что скажете?.. Да, ещё одно - всю партию приму сразу, но не ранее, чем через месяц... деньги ещё в пути.";
			Link.l1 = RandPhraseSimple("Нет, офицер, не заинтересовало меня ваше предложение... Извините.","Заманчиво, конечно, но я не возьмусь. Позвольте не объяснять своего решения...");
			Link.l1.go = "exit_gun";
			Link.l2 = RandPhraseSimple("Не скрою, предложение интересное. Считайте, что мы уже договорились.","Пожалуй, возьмусь. Мне это не сложно, а выгода очевидна.");
			Link.l2.go = "GiveTaskGun_2";
		break;

		case "exit_gun":
			dialog.Text = "Очень жаль... очень жаль, капитан, я на вас рассчитывал. И-и... надеюсь, этот разговор не выйдет за пределы форта?";
			Link.l1 = "Это напоминание было излишним. Всего доброго.";
			Link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First_officer";
		break;

		case "GiveTaskGun_2":
			dialog.Text = "Вот и по рукам. В сроках я вас не ограничиваю, но, все же, постарайтесь не растягивать на полгода. И надеюсь, вы понимаете, что дело конфиденциальное?";
			Link.l1 = "Понимаю. До встречи.";
			Link.l1.go = "exit";
			ReOpenQuestHeader("PrisonGun");
			AddQuestRecord("PrisonGun", "1");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("ся","ась"));
			AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
			AddQuestUserData("PrisonGun", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("PrisonGun", "sQty", makeint(pchar.questTemp.PrisonGun.Qty));
			AddQuestUserData("PrisonGun", "sSum", makeint(pchar.questTemp.PrisonGun.Sum));
			AddQuestUserData("PrisonGun", "sText", pchar.questTemp.PrisonGun.Text);
			NextDiag.TempNode = "First_officer";
		break;

		case "CheckGun":
			if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") < 30)
			{
				dialog.Text = "Я же говорил вам явиться не раньше, чем через месяц!";
				Link.l1 = "Вот черт! Так закрутил"+ GetSexPhrase("ся","ась") +", что потерял"+ GetSexPhrase("","а") +" счет времени... Извините, приду позже, как и договаривались.";
				Link.l1.go = "exit";
				NextDiag.TempNode = "First_officer";
				break;
			}
			if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") > 180)
			{
				dialog.Text = "Гм... Знаете, с момента заключения нашего 'договора' прошло больше, чем полгода. Я уже приобрел орудия. Или вы думали, что я буду ждать вас вечно?";
				Link.l1 = "Вот черт! Что же прикажете теперь с ними делать?";
				Link.l1.go = "TakeGun_late";
				break;
			}
			iGunGoods = pchar.questTemp.PrisonGun.Goods;
			amount = GetSquadronGoods(Pchar, iGunGoods) - sti(pchar.questTemp.PrisonGun.Qty);
			sTemp = sti(pchar.questTemp.PrisonGun.Qty);
			iTest = FindColony(NPChar.City); // город

			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if (rColony.id == "Panama") ok = true;
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				dialog.Text = "Да, вы готовы меня обрадовать?";
				if (amount < 0)
				{
					Link.l1 = "Нет, пока занимаюсь. Просто хотел"+ GetSexPhrase("","а") +" убедиться, что наш уговор ещё в силе.";
					Link.l1.go = "exit";
				}
				else
				{
					Link.l1 = "Готов"+ GetSexPhrase("","а") +". Вся партия в трюме - "+ sTemp +" штук, как и договаривались.";
					Link.l1.go = "TakeGun";
				}
			}
			else
			{
				dialog.text = "Что-то я не вижу в порту вашего корабля. Или вы предлагаете тащить пушки через джунгли? Пришвартуйтесь в нашей гавани и возвращайтесь.";
				link.l1 = "Мой корабль на другой стороне острова. Сейчас приведу его в порт.";
				link.l1.go = "exit";
			}
		break;

		case "TakeGun":
			if (pchar.questTemp.PrisonGun.Luck == 4)
			{
			dialog.Text = RandPhraseSimple("Мне право неловко, но я вынужден аннулировать наш уговор.  Нагрянула финансовая проверка, а вы же знаете, как они щепетильны в этих вопросах. Увы, но никак не получится, извините.","Капитан, тут такое дело... в общем, нам прислали орудия из метрополии, и я, естественно, был вынужден их выкупить. Цены конечно грабительские, но... Извините, что подвёл вас, но я сам весьма огорчён.");
			Link.l1 = "Вот черт! Что же прикажете теперь делать?";
            Link.l1.go = "TakeGun_no";
			}
			else
			{
			dialog.Text = RandPhraseSimple("Отлично. Я сейчас же пришлю для выгрузки гарнизонный наряд.","Великолепно. Солдаты помогут вашим людям с выгрузкой.");
			Link.l1 = "Вы оплату подготовили?";
            Link.l1.go = "TakeGun_1";
			}
		break;

		case "TakeGun_no":
			dialog.Text = "Не знаю. Продайте на верфи, оснастите какое-нибудь торговое судно, утопите... Право же не знаю. И я очень прошу вас, не распространяйтесь об этом деле.";
			Link.l1 = "Это же надо! У меня просто нет слов!";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "3");
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			SaveCurrentNpcQuestDateParam(npchar, "questPrisonGun");
			NextDiag.TempNode = "First_officer";
		break;

		case "TakeGun_late":
			dialog.Text = "Не знаю. Это ваши трудности. Продайте, выбросите, утопите - мне все равно.";
			Link.l1 = "Эх, зря только время тратил"+ GetSexPhrase("","а") +"...";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "4");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("ся","ась"));
			AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			SaveCurrentNpcQuestDateParam(npchar, "questPrisonGun");
			NextDiag.TempNode = "First_officer";
		break;

		case "TakeGun_1":
			iGunGoods = pchar.questTemp.PrisonGun.Goods;
			amount = sti(pchar.questTemp.PrisonGun.Qty);
			iTemp = makeint(sti(pchar.questTemp.PrisonGun.Sum))/12000;
			dialog.Text = RandPhraseSimple("Мне привезли деньги на орудия в кредитных сундуках. Получите, пожалуйста, положенные вам "+ iTemp +" сундуков.","А как же иначе! Но мне привезли деньги в кредитных сундуках. Согласно нашего уговора вам положено "+ iTemp +" сундуков. Вот, извольте получить.");
			Link.l1 = "Сундуки - значит, сундуки. Благодарствую. С вами приятно иметь дело.";
            Link.l1.go = "TakeGun_2";
			TakeNItems(pchar, "chest", makeint(sti(pchar.questTemp.PrisonGun.Sum)/12000));
			Log_Info("Вы получили кредитные сундуки");
			PlaySound("interface\important_item.wav");
			//AddMoneyToCharacter(pchar, makeint(pchar.questTemp.different.PrisonGun.Sum));
			RemoveCharacterGoods(Pchar, iGunGoods, amount);
		break;

		case "TakeGun_2":
			dialog.Text = "Спасибо, вы мне очень помогли. И, прошу вас, пусть эта сделка останется между нами.";
			Link.l1 = "Ну, это само собой разумеется. Всего хорошего.";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "2");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			SaveCurrentNpcQuestDateParam(npchar, "questPrisonGun");
			NextDiag.TempNode = "First_officer";
		break;

		case "EncGirl_1":
			dialog.text = "Слушаю вас внимательно.";
			link.l1 = "Я привел"+ GetSexPhrase("","а") +" вашу беглянку.";
			link.l1.go = "EncGirl_2";
		break;

		case "EncGirl_2":
			dialog.text = "Ах, капитан, спасибо вам большое! Как она? здорова, не пострадала? Уж скоро сутки, как убежала, негодница. Разве ж я ей плохого желаю? Замуж отдать собрался... Жених богатый, молодой, а что собою не пригож, так ведь с лица воду не пить. Нет! она всё по-своему норовит - вся в мать, чтоб её...\nХотя, и она бы на свет не появилась, если бы её мамаша в своё время не сбежала с одним предприимчивым оболтусом... ну да что вспоминать... Молодость наивна, глупа... и жестока.";
			link.l1 = "Конечно, вы отец и решать вам, но я бы не торопил"+ GetSexPhrase("ся","ась") +" со свадьбой...";
			link.l1.go = "EncGirl_3";
		break;

		case "EncGirl_3":
			dialog.text = "Да что вы понимаете?.. У вас свои дети есть? Нету? Вот, когда будут - заходите, тогда и поговорим...\nДа... я обещал вознаграждение тому, кто её вернёт, - примите, пожалуйста.";
			link.l1 = "Спасибо. И держите её покрепче. Что-то мне подсказывает, что она на этом не остановится.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;

		// ------------------------- Повод для спешки -----------------------------
		case "ReasonToFast_Prison1":
			pchar.questTemp.ReasonToFast.SpeakOther = true;
			dialog.text = "Я внимательно слушаю Вас, капитан.";
			link.l1 = "Я хочу доложить о преступном сговоре офицера Вашего гарнизона и пиратов (излагает обстоятельства дела).";
			if(makeint(pchar.reputation) < 41)
			{
				link.l1.go = "ReasonToFast_Prison_BadRep";
			}
			else
			{
				link.l1.go = "ReasonToFast_Prison_GoodRep";
			}
		break;
		case "ReasonToFast_Prison_GoodRep":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1")
			{
				// вилка_А
				dialog.text = "Благодарю вас, судар"+ GetSexPhrase("ь","ыня") +"! Я немедленно отдам приказ задержать негодяя.\nОднако вы изрядно потратились, а муниципальная казна, увы, пуста...";
				link.l1 = "Ваша светлость! Я делал"+ GetSexPhrase("","а") +" это не ради денег...";
				link.l1.go = "ReasonToFast_Prison_GoodRep_11";

				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2")
			{
				// получена карта
				dialog.text = "Благодарю вас, судар"+ GetSexPhrase("ь","ыня") +"! Я немедленно отдам приказ задержать негодяя.\nТолько подумайте! Мы хотели наградить его именным оружием за безупречную службу. Как хорошо, что всё прояснилось, и не вышло такого конфуза!";
				link.l1 = "Всегда рад"+ GetSexPhrase("","а") +" послужить справедливости...";
				link.l1.go = "ReasonToFast_Prison_GoodRep_21";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied")
			{
				// патруль перебит
				dialog.text = "Судар"+ GetSexPhrase("ь","ыня") +"! Мы давно подозревали, что этот офицер и окружавший его сброд нечисты на руку, но мне кажется, что Вы поступили опрометчиво, разделавшись с ними без свидетелей.";
				link.l1 = "Ваша светлость! Но я вынужден"+ GetSexPhrase("","а") +" был"+ GetSexPhrase("","а") +" защищать свою жизнь...";
				link.l1.go = "ReasonToFast_Prison_GoodRep_31";
				pchar.questTemp.ReasonToFast.speakAfterPatrolDied = true;
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}
		break;

		case "ReasonToFast_Prison_BadRep":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1")
			{
				// вилка_А
				dialog.text = "Капитан, Вы хоть понимаете, во что вляпались?!! Мы больше месяца пытались организовать эту ловушку! А Вы ради развлечения сорвали встречу нашего патруля с посыльным " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN) + " и ещё пришли ко мне этим похвастаться! Может, Вы теперь расскажете, каким образом я должен обосновать казённые затраты для организации этой операции?!!";
				link.l1 = "Ваша Честь! Вы отказываетесь видеть суть происходящего...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";

				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2")
			{
				// получена карта
				dialog.text = "Дайте-ка взглянуть на эту карту...\nВы надо мной издеваетесь? Этот затёртый клочок пергамента - доказательство?";
				link.l1 = "Ваша Честь! Вы отказываетесь видеть суть происходящего...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				TakeItemFromCharacter(pchar, "mapQuest");
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_B";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied")
			{
				// патруль перебит
				dialog.text = "Оригинальное оправдание гибели целого патрульного отряда. Ну что ж, по крайней мере, придя сюда, Вы избавили нас от необходимости искать убийцу";
				link.l1 = "Ваша Светлость! Вы отказываетесь видеть суть происходящего...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}
		break;

		case "ReasonToFast_Prison_GoodRep_11":
			dialog.text = "Тем не менее, я хочу, чтобы Ваши труды были вознаграждены. Вот, возьмите карту, найденную в вещах недавно вздёрнутого морского разбойника. Возможно, при содействии Господа, Вы действительно обнаружите сокровища, хотя это весьма сомнительно...";
			link.l1 = "Спасибо, Вы очень щедры!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "15");
			ChangeCharacterReputation(pchar, 1);
			GiveItem2Character(pchar, "mapQuest");
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);
			pchar.questTemp.ReasonToFast.state = "chain_A"; // вилка_А, наводки не генерим
			pchar.questTemp.ReasonToFast = "GetMap";
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_Prison_GoodRep_21":
			dialog.text = "Похвальное рвение. Возьмите этот клинок в награду, - это меньшее, чем я могу вас одарить! Да.. и оставьте эту карту себе. Уверен, - по Архипелагу ходит множество подобных фальшивок.";
			link.l1 = "Спасибо, Вы очень щедры!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "14");
			ChangeCharacterReputation(pchar, 1);
			GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
			pchar.questTemp.ReasonToFast.state = "chain_B"; // была получена карта
			pchar.questTemp.ReasonToFast = "GetMap";
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_Prison_GoodRep_31":
			dialog.text = "Да, возможно, возможно... Что же, я готов считать, что дело разрешилось Божьим судом и по воле Его.";
			link.l1 = "Спасибо, Вы очень щедры!";
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 1);
			AddQuestRecord("ReasonToFast", "16");
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"ReasonToFast");
		break;

		case "ReasonToFast_Prison_BadRep1":
			dialog.text = "Не смейте меня поучать! Для меня очевиден ваш сговор с мошенниками! Караул, взять "+ GetSexPhrase("этого 'доброжелателя'","эту 'доброжелательницу'") +"!";
			link.l1 = "Ну уж нет !";
			link.l1.go = "fight";

			pchar.quest.ReasonToFast_ExitFromTown.win_condition.l1			= "EnterToSea";
            pchar.quest.ReasonToFast_ExitFromTown.function    				= "ReasonToFast_ExitFromTownFight";
			pchar.questTemp.ReasonToFast.canSpeakSailor = true;
			pchar.TownEscape = true;
			Flag_Change(PIRATE);
		break;
		// ------------------------- Повод для спешки -----------------------------

		// -------------------------- Операция 'Галеон' ----------------------------
		case "CapComission_PrisonBad1":
			dialog.text = "А по какому делу он вам понадобился?";
			link.l1 = "У меня к нему несколько вопросов личного характера.";
			link.l1.go = "CapComission_PrisonBad2";
		break;

		case "CapComission_PrisonBad2":
			dialog.text = "Капитан, у меня есть чёткое предписание брать под стражу и направлять в резиденцию для дознания любого, кто будет интересоваться персоной " + pchar.GenQuest.CaptainComission.Name + ".";
			link.l1 = "Неплохо вы устроились! Заключённые уже сами приходят к вам для ареста!";
			link.l1.go = "CapComission_PrisonBad3";
		break;

		case "CapComission_PrisonBad3":
			dialog.text = "И тем не менее, прошу сдать оружие.";
			link.l1 = "Ну уж нет! Вам придётся отбирать его силой.";
			link.l1.go = "fight";
			AddDialogExitQuest("CaptainComission_GenerateCapJail");
		break;

		case "CapComission_PrisonGood1":
			dialog.text = "Да, конечно. Я получил предписание губернатора оказывать вам содействие в этом вопросе. Можете пройти к заключённому.";
			link.l1 = "Благодарю вас...";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			AddDialogExitQuest("CaptainComission_GenerateCapJail");
		break;

		case "CapComission_PrisonFree1":
			dialog.text = "Э-э, капитан, у меня нет указаний выпускать этого заключённого из-под стражи. Вам нужно испросить на это разрешение губернатора.";
			link.l1 = "Офицер, я действую в интересах дознания. Заключённый согласился сотрудничать с властями и готов указать место тайника. Любое промедление грозит тем, что ценный груз будет найден контрабандистами и утерян для поселения.";
			link.l1.go = "CapComission_PrisonFree2";
		break;

		case "CapComission_PrisonFree2":
			dialog.text = "Но я мог бы выделить эскорт для его сопровождения.";
			link.l1 = "Этого не понадобится, у меня достаточно охраны. Кроме того, я опасаюсь огласки местоположения тайника.";
			link.l1.go = "CapComission_PrisonFree3";
		break;

		case "CapComission_PrisonFree3":
			dialog.text = "М-м... ну хорошо. Только учтите, что отвечаете за него головой.";
			link.l1 = "Безусловно...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_officer";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("OpenTheDoors");
		break;
		// -------------------------- Операция 'Галеон' ----------------------------

		case "F_ShipLetters_1":
			dialog.text = "Говорите, я слушаю.";
			link.l1 = "У меня есть судовые документы. Думаю, владелец их по рассеянности позабыл, а вам они будут интересны.....";
			link.l1.go = "F_ShipLetters_2";
			pchar.questTemp.different.GiveShipLetters.speakFort = true;
		break;

		case "F_ShipLetters_2":
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Вздор! Не мешайте работать, идите лучше в Портовое управление.";
				link.l1 = "Спасибо и на этом....";
				link.l1.go = "exit";
			}
			else
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					dialog.text = "Да, владелец из местных. Пожалуй, премия в " + sti(pchar.questTemp.different.GiveShipLetters.price2) + " золотых послужит достойной наградой за Вашу бдительность, капитан.";
					link.l1 = "Пожалуй, нет.";
					link.l1.go = "F_ShipLetters_3";
					link.l2 = "Щедрое предложение! Бумаги отныне Ваши....";
					link.l2.go = "F_ShipLetters_4";
				}
				else
				{
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
					{
						dialog.text = "Ух, аж дух захватывает, насколько интересны! Думаю, городская казна благодарно выплатит Вам "+ sti(pchar.questTemp.different.GiveShipLetters.price4) +" золотых, за содействие в борьбе с незаконным товарооборотом.";
						link.l1 = "Пожалуй, нет.";
						link.l1.go = "F_ShipLetters_3";
						link.l2 = "Щедрое предложение! Бумаги отныне Ваши....";
						link.l2.go = "F_ShipLetters_4";
					}
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
					{
						dialog.text = "Боже! Какая удача, что Вы пришли ко мне. Я думаю, мой незадачливый коллега согласится заплатить " + sti(pchar.questTemp.different.GiveShipLetters.price3) + " золотом, чтобы дело избежало огласки.";
						link.l1 = "Пожалуй, нет.";
						link.l1.go = "F_ShipLetters_3";
						link.l2 = "Щедрое предложение! Бумаги отныне Ваши....";
						link.l2.go = "F_ShipLetters_4";
					}
				}
			}
		break;

		case "F_ShipLetters_3":
			dialog.text = "Хех! Это мой город, капитан.";
			link.l1 = "Я это запомню.";
			link.l1.go = "exit";
		break;

		case "F_ShipLetters_4":
			TakeItemFromCharacter(pchar, "CaptainBook");
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2));
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price4));
				}
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2));
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price3));
				}
			}

			if((sti(pchar.questTemp.different.GiveShipLetters.variant) == 0) || (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2))
			{
				ChangeCharacterReputation(pchar, -1);
				OfficersReaction("bad");
			}
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер
			AddQuestRecord("GiveShipLetters", "8");
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;


        case "ForGoodMove":
			dialog.text = NPCStringReactionRepeat("Но зачем вам это? Поверьте мне, там нет ничего достойного внимания, одни воры и бандиты.", "Мы уже обсуждали это ваше желание.",
				"Опять о том же? Уже дважды мы с вами говорили об этом!", "Гм, опять...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Тем не менее, я хотел"+ GetSexPhrase("","а") +" бы провести экскурс по вашим казематам. Мне очень интересно!", "Да, именно так. Но я хотел"+ GetSexPhrase("","а") +" еще поговорить на эту тему.",
				"Ну, может в третий раз...", "Надежда посмотреть на ваших узников не покидает меня...", npchar, Dialog.CurrentNode);
			link.l1.go = "ForGoodMove_1";
		break;
        case "ForGoodMove_1":
			pchar.questTemp.jailCanMove.money = (rand(15)+10)*100;
			if (sti(colonies[FindColony(npchar.city)].jail) && sti(pchar.money) >= sti(pchar.questTemp.jailCanMove.money))
			{
				dialog.text = "Ну что же, не вижу причины вам отказывать. " + FindRussianMoneyString(sti(pchar.questTemp.jailCanMove.money)) + " - и пока вы не покинете тюрьму, вы можете беспрепятственно ходить по коридорам и даже разговаривать с заключенными.";
				link.l1 = "Я соглас"+ GetSexPhrase("ен","на") +", вот ваши монеты!";
				link.l1.go = "ForGoodMove_agree";
				link.l2 = "Не пойдет, слишком дорого для бесцельного хождения по коридорам.";
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple("Нет, это категорически запрещено уставом. Вам здесь что, цирк? Уходите, и не отвлекайте меня от несения службы.", "Я не могу позволить расхаживать по тюрьме посторонним людям. Прошу вас, не мешайте мне!");
				link.l1 = "Хорошо, как скажете...";
				link.l1.go = "exit";
			}
		break;
        case "ForGoodMove_agree":
            dialog.text = "Ну что же, вы можете приступать к своему, так сказать, экскурсу...";
			link.l1 = "Спасибо, офицер.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.jailCanMove.money));
		break;
        case "KnowAboutPrisoner":
			switch (pchar.questTemp.jailCanMove.ownerPrison)
			{
				case "0": sTemp = "За убийство."; break;
				case "1": sTemp = "За бандитизм и вооруженный грабеж."; break;
				case "2": sTemp = "Его поймали на воровстве."; break;
				case "3": sTemp = "За мелкую кражу."; break;
				case "4": sTemp = "За шулерство."; break;
			}
			dialog.text = sTemp;
			link.l1 = "Понятно... А есть шанс внести за него выкуп, залог, или еще как-нибудь содействовать его вызволению?";
			link.l1.go = "KnowAboutPrisoner_" + pchar.questTemp.jailCanMove.ownerPrison;
			DeleteAttribute(pchar, "questTemp.jailCanMove.City");
		break;
        case "KnowAboutPrisoner_0":
			dialog.text = "Нет, конечно. Этому висельнику прямая дорога в ад. Он на особом контроле у губернатора!";
			link.l1 = "Хех, понятно...";
			link.l1.go = "notFree_exit";
		break;
        case "KnowAboutPrisoner_1":
			dialog.text = "Не думаю. Много он крови попортил жителям нашего города. Так что даже и не проси.";
			link.l1 = "Хм, ясно.";
			link.l1.go = "notFree_exit";
		break;
        case "KnowAboutPrisoner_2":
			dialog.text = "Нет, пожалуй. Он вор, а вор должен сидеть в тюрьме!";
			link.l1 = "О как! Хорошо сказано, лейтенант...";
			link.l1.go = "notFree_exit";
		break;
        case "KnowAboutPrisoner_3":
			dialog.text = "Не знаю даже. Этот паршивец стащил у одной хозяйки сковороду. И отпустить его не могу, но и гноить здесь за такую мелочь - тоже не дело...";
			link.l1 = "Так отдайте его мне, лейтенант. Я заплачу, в разумных пределах, естественно.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
        case "KnowAboutPrisoner_4":
			dialog.text = "Вызволению? Вполне возможно. С моей точки зрения, содержать этого мелкого жулика здесь не имеет никакого смысла.";
			link.l1 = "Так отдайте его мне, лейтенант. Я заплачу, в разумных пределах, естественно.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
        case "KnowAboutPrisoner_free":
			pchar.questTemp.jailCanMove.ownerPrison.money = (rand(3)+2)*1000;
			if (sti(pchar.money) > sti(pchar.questTemp.jailCanMove.ownerPrison.money))
			{
				dialog.text = "Хм, ну хорошо. " + FindRussianMoneyString(sti(pchar.questTemp.jailCanMove.ownerPrison.money)) + " на бочку, и забирай его хоть прямо сейчас.";
				link.l1 = "Здорово, я соглас"+ GetSexPhrase("ен","на") +".";
				link.l1.go = "KnowAboutPrisoner_agree";
				link.l2 = "Нет, дороговато будет. Откажусь.";
				link.l2.go = "KnowAboutPrisoner_exit";
			}
			else
			{
				dialog.text = "Нет, не выйдет. У меня могут провести инспекцию в любой момент, рисковать не хочу.";
				link.l1 = "О как! Хорошо сказано, лейтенант...";
				link.l1.go = "exit";
			}
		break;
        case "KnowAboutPrisoner_agree":
			dialog.text = "Все, вы можете пройти к его камере и забирать этого оборванца.";
			link.l1 = "Спасибо.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.jailCanMove.ownerPrison.money));
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
        case "KnowAboutPrisoner_exit":
			dialog.text = "Ну, смотри, другого шанса я не дам...";
			link.l1 = "И не надо. Я принял"+ GetSexPhrase("","а") +" решение.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_expansive";
		break;
        case "notFree_exit":
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_notFree";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//---------------- Протектор ------------------
        case "First_protector":
			if (sti(pchar.questTemp.jailCanMove))
			{
				dialog.text = RandPhraseSimple("Вы можете пройти, начальник разрешил...", "Получен приказ начальника тюрьмы. Вы можете свободно проходить.");
				link.l1 = "Ну, вот и чудно.";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison.money");
			}
			else
			{
				dialog.text = RandPhraseSimple("Проходить далее без разрешения начальника тюрьмы категорически запрещено!", "Я подчиняюсь только начальнику тюрьмы. Если ты попытаешься пройти дальше без его разрешения - тебе конец!");
				link.l1 = RandPhraseSimple("Понятно", "Ясно") + ", солдат.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First_protector";
		break;
		//---------------- Солдаты ------------------
        case "First_soldier":
            dialog.text = RandPhraseSimple("Я на посту, не отвлекайте меня.", "Проходите мимо, я не могу с вами разговаривать.");
			link.l1 = "Хорошо, солдат.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_soldier";
		break;
		//---------------- Заключенные ------------------
        case "First_prisoner":
			if (GetNationRelation2MainCharacter(sti(npchar.nation)) == RELATION_ENEMY)
			{
				dialog.text = LinkRandPhrase("Хо-хо, до чего же весело!!", "Режь их, "+ GetSexPhrase("приятель","подруга") +", режь!!!", "Эх, дьявол! Уж не думал, что увижу труп своего надсмотрщика!");
				link.l1 = RandPhraseSimple("Хех!", "Аргх...");
				link.l1.go = "NoMoreTalkExit";
				if (rand(10) > 6 && !CheckAttribute(pchar, "quest.GivePrisonFree") && !CheckAttribute(pchar, "quest.GivePrisonFree_Over") && !CheckAttribute(pchar, "quest.DeliverToBander"))
				{
					dialog.text = RandPhraseSimple("Постой, "+ GetSexPhrase("дружище","подруга") +"!! Выпусти меня!", "Послушай, "+ GetSexPhrase("приятель","подруга") +", будь так добр"+ GetSexPhrase("","а") +", открой камеру.");
					link.l1 = "С какой это стати?";
					link.l1.go = "Prisoner_1"; // на квест освобождения заключенного
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Меня взяли за грабеж, дело шьют...", "Агрх, холен"+ GetSexPhrase("ый","ая") +" ты... Тебя бы ко мне в камеру на недельку! Кхе-хе-хе...", "Я ни в чем не виноват!");
				link.l1 = RandPhraseSimple("Заткнись!", "Мне нет до тебя дела...");
				link.l1.go = "NoMoreTalkExit";
				if (rand(10) > 6 && !CheckAttribute(pchar, "quest.GivePrisonFree_Over") && !CheckAttribute(pchar, "quest.GivePrisonFree") && !CheckAttribute(pchar, "quest.DeliverToBander") && !sti(colonies[FindColony(npchar.city)].HeroOwn))
				{
					dialog.text = RandPhraseSimple("Постой, "+ GetSexPhrase("приятель","подруга") +", не проходи мимо моей камеры так быстро!", "Не торопись, "+ GetSexPhrase("дружище","подруга") +", давай поговорим.");
					link.l1 = "С какой это стати?";
					if (rand(1))
					{
						link.l1.go = "Prisoner_1"; // на квест освобождения заключенного
					}
					else
					{
						link.l1.go = "Deliver_1"; // на квест передачу весточки
					}
				}
			}
		break;
		// -------------------- освобождение заключенного --------------------
        case "Prisoner_1":
            dialog.text = "Чтобы послушать меня. Ты не смотри, что сейчас я в таком виде. Мне бы выбраться отсюда...";
			link.l1 = "Чего?!";
			link.l1.go = "Prisoner_2";
			GetChestPlaceName();
			pchar.questTemp.jailCanMove.prisonerId = npchar.id; //запомним Id
			pchar.questTemp.jailCanMove.IsTrue = rand(4); //вид клада
			pchar.questTemp.jailCanMove.Sum = (rand(10)+10)*1000+(sti(pchar.rank)*1000); //сумма клада
			pchar.questTemp.jailCanMove.Item1 = GenQuestPrison_GenerateArtefact();
			pchar.questTemp.jailCanMove.Item2 = GenQuestPrison_GenerateBlade();
			pchar.questTemp.jailCanMove.Name = GetFullName(npchar); //имя перца
		break;
        case "Prisoner_2":
            dialog.text = "Что слышал"+ GetSexPhrase("","а") +". Помоги мне выбраться, и я сумею отблагодарить.";
			link.l1 = "Уже интересно. Кто ты такой и что можешь мне предложить?";
			link.l1.go = "Prisoner_3";
		break;
        case "Prisoner_3":
            dialog.text = "Меня зовут " + GetFullName(npchar) + ". Кое-что у меня припрятано в надежном месте. Вытащи меня отсюда и отвези на " + XI_ConvertString(pchar.questTemp.jailCanMove.islandId + "Acc") + ". Там в гроте у меня спрятан клад. Достанем его и поделим поровну!";
			link.l1 = "И что там у тебя в кладе? И откуда мне знать, что твои слова - правда?";
			link.l1.go = "Prisoner_4";
		break;
        case "Prisoner_4":
            dialog.text = "Клянусь тебе, я говорю чистейшую правду! А в кладе я спрятал деньги и драгоценности...";
			link.l1 = "Нет, приятель. Я не собираюсь рисковать шкурой из-за сомнительного клада. Извини...";
			link.l1.go = "Prisoner_5";
			if (GetNationRelation2MainCharacter(sti(npchar.nation)) != RELATION_ENEMY)
			{
				link.l2 = "Пожалуй, стоит рискнуть... Предлагаю следующее: я могу перебить стражу в тюрьме и забрать тебя на свой корабль. Если все получится, я хочу, чтобы ты не отходил от меня до тех пор, пока мы не доберемся до грота на " + XI_ConvertString(pchar.questTemp.jailCanMove.islandId + "Dat") + ". Идет?";
				link.l2.go = "Prisoner_agree"; //силовой способ вызволения
				link.l3 = "Ну, хорошо, я постараюсь помочь тебе - поговорю с начальником тюрьмы. Возможно, удастся внести залог за твое освобождение.";
				link.l3.go = "ToPrisonHead_agree"; //мирный способ вызволения
			}
			else
			{
				link.l2 = "Ну, хорошо, поверю тебе и открою камеру. Я хочу, чтобы ты не отходил от меня до тех пор, пока мы не доберемся до грота на " + XI_ConvertString(pchar.questTemp.jailCanMove.islandId + "Dat") + ". Идет?";
				link.l2.go = "Prisoner_agree_3"; //силовой способ вызволения, когда тюремщики убиты
			}
		break;
        case "Prisoner_5":
            dialog.text = RandPhraseSimple("Будь ты проклят"+ GetSexPhrase("","а") +", каналья!!", "Чтоб тебя разорвало, иуда...");
			link.l1 = RandPhraseSimple("И тебе всего хорошего. Прощай...", "Собака лаяла на дядю фраера...");
			link.l1.go = "NoMoreTalkExit";
		break;
        case "Prisoner_agree":
            dialog.text = "Идет, мне выбирать не приходится.";
			link.l1 = "Хорошо. Я сейчас сломаю твой замок, выходи оттуда, и будем прорываться. Ты готов?";
			link.l1.go = "Prisoner_agree_1";
		break;
        case "Prisoner_agree_1":
            dialog.text = "Да, "+ GetSexPhrase("приятель","подруга") +", я готов!";
			link.l1 = "За дело!";
			link.l1.go = "Prisoner_agree_2";
		break;
        case "Prisoner_agree_2":
			string slai_group = GetNationNameByType(sti(npchar.nation))  + "_citizens";
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Dat"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

        case "Prisoner_agree_3":
            dialog.text = "Идет, мне выбирать не приходится.";
			link.l1 = "Хорошо. Следуй за мной как можно быстрей, нам нужно еще добраться до моего корабля. Не отставай!";
			link.l1.go = "Prisoner_agree_4";
		break;
        case "Prisoner_agree_4":
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Dat"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;

        case "ToPrisonHead_agree":
            dialog.text = "Ну, попробуй. Эх-х-х, получилось бы! Только не теряй времени, через пару дней меня здесь уже не будет...";
			link.l1 = "Жди, я все улажу.";
			link.l1.go = "NoMoreTalkExit";
			pchar.questTemp.jailCanMove.MayorId = characters[GetCharacterIndex(npchar.city + "_Mayor")].id; //Id мэра
			pchar.questTemp.jailCanMove.City = npchar.City; //город
			pchar.questTemp.jailCanMove.ownerPrison = rand(4); //характер преступления
			SetTimerCondition("GivePrisonFree_Over", 0, 0, 2, false);
			AddQuestRecord("GivePrisonFree", "5");
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("ся","ась"));
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
		break;

        case "ToPrisonHead_canMove":
            dialog.text = "Ну, что скажешь, "+ GetSexPhrase("приятель","подруга") +"?";
			link.l1 = "Все улажено, я могу забирать тебя.";
			link.l1.go = "ToPrisonHead_canMove_1";
		break;
        case "ToPrisonHead_canMove_1":
            dialog.text = "Ну, так пойдем отсюда быстрее! Черт возьми, как я рад!";
			link.l1 = "Подведем итоги. Я хочу, чтобы все время, пока мы не доберемся до грота на " + XI_ConvertString(pchar.questTemp.jailCanMove.islandId + "Dat") + ", ты не отходил от меня ни на шаг. На всякий случай, так сказать. Ты согласен?";
			link.l1.go = "ToPrisonHead_canMove_2";
		break;
        case "ToPrisonHead_canMove_2":
            dialog.text = "Конечно, согласен! Да и выбирать мне не приходится.";
			link.l1 = "Тогда ты свободен.";
			link.l1.go = "ToPrisonHead_canMove_exit";
		break;
        case "ToPrisonHead_canMove_exit":
			pchar.quest.GivePrisonFree_Over.over = "yes";
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Dat"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;

        case "ToPrisonHead_notFree":
			switch (pchar.questTemp.jailCanMove.ownerPrison)
			{
				case "0": sTemp = "убийстве"; break;
				case "1": sTemp = "вооруженном грабеже"; break;
				case "2": sTemp = "воровстве"; break;
			}
            dialog.text = "Ну, что скажешь, "+ GetSexPhrase("приятель","подруга") +"?";
			link.l1 = "Мне не удалось договориться о твоем освобождении. Тебя обвиняют в " + sTemp + ", так что ни о каких залогах речи быть не может.";
			link.l1.go = "ToPrisonHead_notFree_1";
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
		break;
        case "ToPrisonHead_notFree_1":
            dialog.text = "Меня оболгали!.. Вот дьявол!! И что теперь мне делать? Я же сгнию здесь заживо!";
			link.l1 = "Очень жаль, приятель, но я ничем не могу тебе помочь.";
			link.l1.go = "ToPrisonHead_notFree_2";
			link.l2 = "Остается шанс освободить тебя силой. Я сейчас сломаю твой замок, выходи оттуда, и будем прорываться. Ты готов?";
			link.l2.go = "Prisoner_agree_1";
			pchar.quest.GivePrisonFree_Over.over = "yes";
		break;
        case "ToPrisonHead_notFree_2":
            dialog.text = RandPhraseSimple("Будь ты проклят"+ GetSexPhrase("","а") +", каналья!!", "Чтоб тебя разорвало, иуда...");
			link.l1 = "И тебе всего хорошего. Прощай...";
			link.l1.go = "NoMoreTalkExit";
			AddQuestRecord("GivePrisonFree", "7");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
		break;

        case "ToPrisonHead_expansive":
			dialog.text = "Ну, чем обрадуешь, "+ GetSexPhrase("приятель","подруга") +"?";
			link.l1 = "Залог за твое освобождение слишком велик, у меня нет таких денег. Я вынужден"+ GetSexPhrase("","а") +" отказаться от помощи тебе.";
			link.l1.go = "ToPrisonHead_notFree_2";
			pchar.quest.GivePrisonFree_Over.over = "yes";
		break;
		//==> в месте, где клад припрятан
        case "PrisonerInPlace":
			switch (sti(pchar.questTemp.jailCanMove.IsTrue))
			{
				case 0:
					dialog.text = "Слушай, я тут проверил все, но моего клада не нашел. Очень жаль, что так вышло, наверное, кто-то раскопал его до нас.";
					link.l1 = "Как такое может быть?!";
					link.l1.go = "PrisonerInPlace_1";
				break;
				case 1:
					dialog.text = "Я нашел его! Драгоценности лежали там, где я их и оставил.";
					link.l1 = "Великолепно. Ну что, будем делить?";
					link.l1.go = "Node_1";
				break;
				case 2:
					dialog.text = "Ну вот он, мой схрон. Невелик, правда, но это все, что у меня есть. Как договаривались - половина ваша.";
					link.l1 = "Да, клад и в самом деле, не ахти. Ну что же, спасибо и на том.";
					link.l1.go = "Node_2";
				break;
				case 3:
					dialog.text = "Капитан, извините, тут так вышло... короче, нет клада.";
					link.l1 = "Что? Ты меня обманул, негодяй! Я тебя вытащил"+ GetSexPhrase("","а") +" из-за решетки, тащил"+ GetSexPhrase("ся","ась") +" на этот остров, и все ради чего?! Это тебе с рук не сойдет!";
					link.l1.go = "Node_3";
				break;
				case 4:
					dialog.text = "Черт возьми... Ну как же так? Не может быть!";
					link.l1 = "Ты чего, приятель? Где наш клад? Только не говори, что его нет!";
					link.l1.go = "Node_4";
				break;
			}
		break;

		case "Node_1":
			dialog.text = "Да, конечно, как договаривались. Половина сокровищ ваша.";
			link.l1 = "Ух ты, сколько тут всего ценного!";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("Вы получили свою долю клада");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 1+drand(1));
			TakeNItems(pchar, "chest", 4+drand(4));
			TakeNItems(pchar, "jewelry1", 70+rand(15));
			TakeNItems(pchar, "jewelry2", 50+rand(15));
			TakeNItems(pchar, "jewelry3", 60+rand(15));
			TakeNItems(pchar, "jewelry4", 40+rand(10));
			TakeNItems(pchar, "jewelry15", 10+rand(10));
			TakeNItems(pchar, "jewelry18", 60+rand(20));
			TakeNItems(pchar, "jewelry14", 40+rand(15));
			TakeNItems(pchar, "jewelry7", 60+rand(20));
			AddQuestRecord("GivePrisonFree", "3_1");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;

		case "Node_2":
			dialog.text = "Капитан, здесь среди прочего есть вот этот индейский предмет. Возьмите его сверх вашей доли.";
			link.l1 = "Ну, хоть что-то толковое получу за твое освобождение! Давай его сюда.";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("Вы получили свою долю клада");
			PlaySound("interface\important_item.wav");
			sTemp = pchar.questTemp.jailCanMove.Item1;
			TakeNItems(pchar, sTemp, 1);
			TakeNItems(pchar, "jewelry5", 40+rand(10));
			TakeNItems(pchar, "jewelry6", 20+rand(20));
			TakeNItems(pchar, "jewelry17", 80+rand(20));
			TakeNItems(pchar, "jewelry13", 10+rand(10));
			TakeNItems(pchar, "jewelry11", 20+rand(20));
			TakeNItems(pchar, "jewelry12", 50+rand(20));
			AddQuestRecord("GivePrisonFree", "3_2");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;

		case "Node_3":
			dialog.text = "Подождите, капитан, не горячитесь, дайте мне сказать. Я тоже моряк, как и вы. Меня бросили в тюрьму по ошибке, клянусь. Вы были моим единственным шансом спастись, и мне пришлось вам солгать о кладе.\nКлада нет, но я спрятал тут одну хорошую вещь. Возьмите ее, и отпустите меня с миром. Возможно, в бою вы еще не раз помянете меня добрым словом.";
			link.l1 = "Ладно, все равно взять с тебя нечего. Благодари Бога, что я отходчив"+ GetSexPhrase("ый","ая") +".";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("Вы получили экипировку");
			PlaySound("interface\important_item.wav");
			sTemp = pchar.questTemp.jailCanMove.Item2;
			TakeNItems(pchar, sTemp, 1);
			AddQuestRecord("GivePrisonFree", "3_3");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;

		case "Node_4":
			dialog.text = "Нет!!! Его действительно нет! Проклятый обрывок... Капитан, поверьте, я действительно думал, что он здесь! Но, видимо, я ошибся! На этом клочке бумаги все так непонятно...";
			link.l1 = "Та-ак, похоже, сейчас у тебя будут серьезные проблемы, приятель. Но все-таки я хочу послушать твои объяснения.";
			link.l1.go = "Node_4_1";
		break;

		case "Node_4_1":
			dialog.text = "У меня был кусок карты. Подлинной карты, клянусь! Но по нему так тяжело разобрать, что за остров на нем указан... Я подумал, что это здесь. Но, как вы видите, это не так.";
			link.l1 = "Что за кусок карты? Давай его сюда, живо!";
			link.l1.go = "Node_4_2";
		break;

		case "Node_4_2":
			if (CheckCharacterItem(pchar, "map_part1"))
			{
				GiveItem2Character(pchar, "map_part2");
			}
			else
			{
				GiveItem2Character(pchar, "map_part1");
			}
			dialog.text = "Вот, берите, конечно. Капитан, отпустите меня, пожалуйста... Я и в самом деле думал, что клад тут. Может, вы разберетесь по этому клочку, где он, и заберете все себе. Прошу вас.";
			link.l1 = "Да уж... Разобрать что-либо тут очень сложно. Нужна вторая половина карты. Ладно, проваливай, вижу, ты действительно хотел, как лучше.";
			link.l1.go = "PrisonerInPlace_4";
		break;
        case "PrisonerInPlace_1":
			dialog.text = "Да очень просто, "+ GetSexPhrase("приятель","подруга") +". Еще и не такое в жизни случается.\nНу ладно, ты тут, если хочешь, оставайся, поищи еще. Ну, а мне пора!\nПрощай, "+ GetSexPhrase("друг","подруга") +", спасибо, что спас"+ GetSexPhrase("","ла") +" мне жизнь. Я буду помнить тебя вечно!";
			link.l1 = "Ах ты мерзавец! Думаешь, я дам тебе так просто уйти?! Эй... А ну стой, трус!";
			link.l1.go = "PrisonerInPlace_2";
			AddQuestRecord("GivePrisonFree", "4");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");

			pchar.questTemp.genquestcount = sti(pchar.questTemp.genquestcount) + 1;
			if(sti(pchar.questTemp.genquestcount) >= 10) UnlockAchievement("gen_quests", 1);
			if(sti(pchar.questTemp.genquestcount) >= 20) UnlockAchievement("gen_quests", 2);
			if(sti(pchar.questTemp.genquestcount) >= 40) UnlockAchievement("gen_quests", 3);

			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
        case "PrisonerInPlace_2":
			LAi_group_Delete("EnemyFight");
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
			chrDisableReloadToLocation = false;
			LAi_LocationDisableMonstersGen(pchar.location, false);
			npchar.lifeDay = 0;
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", -1);
			DialogExit();
            Pchar.quest.DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            Pchar.quest.DeletePrisonGroup.win_condition.l1.location = pchar.location;
            Pchar.quest.DeletePrisonGroup.win_condition = "DeletePrisonGroup";
		break;
        case "PrisonerInPlace_3":
			dialog.text = "Пожалуйста, получите. И спасибо вам!";
			link.l1 = "Прощай...";
			link.l1.go = "PrisonerInPlace_2";
		break;
        case "PrisonerInPlace_4":
			dialog.text = "Спасибо вам, капитан! Я буду молиться за вас до конца своих дней!";
			link.l1 = "Ладно тебе заливать! Иди с Богом...";
			link.l1.go = "PrisonerInPlace_2";
			AddQuestRecord("GivePrisonFree", "3_4");
            AddQuestUserData("GivePrisonFree", "iSum", FindRussianMoneyString(sti(pchar.questTemp.jailCanMove.Sum)));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("GivePrisonFree");

			pchar.questTemp.genquestcount = sti(pchar.questTemp.genquestcount) + 1;
			if(sti(pchar.questTemp.genquestcount) >= 10) UnlockAchievement("gen_quests", 1);
			if(sti(pchar.questTemp.genquestcount) >= 20) UnlockAchievement("gen_quests", 2);
			if(sti(pchar.questTemp.genquestcount) >= 40) UnlockAchievement("gen_quests", 3);

			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
 		break;
		// -------------------- освобождение заключенного --------------------
		// ------------------------ передать маляву --------------------------
        case "Deliver_1":
			dialog.text = "Меня кличут " + GetFullName(npchar) + ". Есть у меня к тебе просьба одна, хе-хе...";
			link.l1 = "Что такое?";
			link.l1.go = "Deliver_2";
		break;
        case "Deliver_2":
			dialog.text = "Нужно передать маляву на волю. Сделаешь?";
			link.l1 = "А какой мне с этого резон?";
			link.l1.go = "Deliver_3";
		break;
        case "Deliver_3":
			dialog.text = "Не обидят тебя кореши, чего уж... Ну так что, возьмешься?";
			link.l1 = "Нет, меня это не интересует.";
			link.l1.go = "Prisoner_5";
			link.l2 = "Хм, если далеко ходить не надо, то возьмусь.";
			link.l2.go = "Deliver_agree";
		break;
        case "Deliver_agree":
			dialog.text = "Хорошо. Слушай теперь меня внимательно. В городе ждут мою маляву два кента, заныкались они в доме, чтобы под шмон не попасть. В каком доме - не ведаю, надо будет поискать.";
			link.l1 = "Как поискать?";
			link.l1.go = "Deliver_4";
		break;
        case "Deliver_4":
			dialog.text = "Обычно поискать. По городу побегаешь, в дома позаглядываешь... Как в нужное место попадёшь, они тебя сами без разговора не выпустят. Только имей в виду, что здесь я ещё дня два пробуду, не более. Так что не тяни.";
			link.l1 = "Ясно. Ну, давай свою весточку.";
			link.l1.go = "Deliver_5";
		break;
        case "Deliver_5":
			pchar.questTemp.jailCanMove.Deliver.locationId = GetBanderLocation(npchar); //Id коммона
			if (pchar.questTemp.jailCanMove.Deliver.locationId == "none")
			{
				dialog.text = "Хм, что-то ты мне не нравишься. Я передумал. Давай, проходи, не стой здесь!";
				link.l1 = "Вот это да! Ну ладно, как хочешь...";
				link.l1.go = "NoMoreTalkExit";
				DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
			}
			else
			{
				dialog.text = "Держи. Спасибо тебе, "+ GetSexPhrase("приятель","подруга") +"!";
				link.l1 = "Да не за что.";
				link.l1.go = "NoMoreTalkExit";
				GiveItem2Character(Pchar, "Malyava");
				pchar.questTemp.jailCanMove.Deliver.Id = npchar.id; //Id зэка
				pchar.questTemp.jailCanMove.Deliver.name = GetFullName(npchar); //имя зэка
				pchar.questTemp.jailCanMove.Deliver.City = npchar.city; //город (Id колонии)
				pchar.questTemp.jailCanMove.Deliver.good = rand(3); //опрокинут или нет
				pchar.questTemp.jailCanMove.Deliver.price = rand(6)*500+500; //цена услуги
				pchar.quest.DeliverToBander.win_condition.l1 = "location";
				pchar.quest.DeliverToBander.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.locationId;
				pchar.quest.DeliverToBander.win_condition = "DeliverToBander";
				pchar.quest.DeliverToBander.again = true;
				SetTimerCondition("DeliverToBander_over", 0, 0, 2, false);
				ReOpenQuestHeader("GivePrisonFree");
				AddQuestRecord("GivePrisonFree", "8");
				AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("cя","ась"));
				AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Deliver.name);
			}
		break;
	}
}

void GetChestPlaceName()
{
	string islandId;
	int iTemp = rand(3);
	switch (iTemp)
	{
		case 0:
			pchar.questTemp.jailCanMove.islandId = "Bermudes";
			pchar.questTemp.jailCanMove.placeId = "Bermudes_Cavern";
		break;
		case 1:
			pchar.questTemp.jailCanMove.islandId = "Caiman";
			pchar.questTemp.jailCanMove.placeId = "Caiman_Grot";
		break;
		case 2:
			pchar.questTemp.jailCanMove.islandId = "Dominica";
			pchar.questTemp.jailCanMove.placeId = "Dominica_Grot";
		break;
		case 3:
			pchar.questTemp.jailCanMove.islandId = "Terks";
			pchar.questTemp.jailCanMove.placeId = "Terks_Grot";
		break;
	}
}

string GetBanderLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId;
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "GenQuest.SeekSpy.Location")) //если взят квест мэра по поиску шпиона
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.GenQuest.SeekSpy.Location)
    		{
				storeArray[howStore] = LocId;
				howStore++;
			}
			if (arCommon.label != "Sea")
			{
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.GenQuest.SeekSpy.Location)
    				{
						storeArray[howStore] = LocId;
						howStore++;
					}
				}
			}
		}
	}
	else
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1)
    		{
				storeArray[howStore] = LocId;
				howStore++;
			}
			if (arCommon.label != "Sea")
			{
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1)
    				{
						storeArray[howStore] = LocId;
						howStore++;
					}
				}
			}
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[rand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); //открываем дверь
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId)
		{
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}

string GenQuestPrison_GenerateArtefact() // артефакты
{
	string itemID;
	switch(rand(8))
	{
		case 0:
			itemID = "indian6";
		break;
		case 1:
			itemID = "indian10";
		break;
		case 2:
			itemID = "indian12";
		break;
		case 3:
			itemID = "indian19";
		break;
		case 4:
			itemID = "indian20";
		break;
		case 5:
			itemID = "indian22";
		break;
		case 6:
			itemID = "indian21";
		break;
		case 7:
			itemID = "sculMa2";
		break;
		case 8:
			itemID = "sculMa1";
		break;

	}
	return itemID;
}

string GenQuestPrison_GenerateBlade() // клинки и другое
{
	string itemID;
	switch(rand(8))
	{
		case 0:
			itemID = GetGeneratedItem("blade22");
		break;
		case 1:
			itemID = GetGeneratedItem("blade19");
		break;
		case 2:
			itemID = GetGeneratedItem("blade31");
		break;
		case 3:
			itemID = "cirass3";
		break;
		case 4:
			itemID = GetGeneratedItem("blade21");
		break;
		case 5:
			itemID = "spyglass4";
		break;
		case 6:
			itemID = GetGeneratedItem("blade15");
		break;
		case 7:
			itemID = GetGeneratedItem("blade34");
		break;
		case 8:
			itemID = "cirass4";
		break;

	}
	return itemID;
}

void GetGunType()
{
		int iGunType;
		if(makeint(pchar.rank) < 5) { iGunType = rand(1); }	//24
		if(makeint(pchar.rank) >= 6 && makeint(pchar.rank) < 13) { iGunType = rand(3); } //24&&32
		if(makeint(pchar.rank) >= 13 && makeint(pchar.rank) < 20) { iGunType = rand(2)+2; } //32&&42
		if(makeint(pchar.rank) >= 20) { iGunType = 4; } //42

		switch (iGunType)
		{
			case 0:
				pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_24;
				pchar.questTemp.PrisonGun.Price = 900 + GetCharacterSPECIALSimple(PChar, SPECIAL_C)*GetSummonSkillFromName(pchar, SKILL_COMMERCE)/100*175;
                pchar.questTemp.PrisonGun.Qty = sti(makeint(pchar.rank)*5+30+rand(sti(pchar.rank)));
				pchar.questTemp.PrisonGun.Text = "пушки 24 калибра";
			break;
			case 1:
				pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_24;
				pchar.questTemp.PrisonGun.Price = 1100 + GetCharacterSPECIALSimple(PChar, SPECIAL_C)*GetSummonSkillFromName(pchar, SKILL_COMMERCE)/100*225;
                pchar.questTemp.PrisonGun.Qty = sti(makeint(pchar.rank)*5+20+rand(sti(pchar.rank)));
				pchar.questTemp.PrisonGun.Text = "кулеврины 24 калибра";
			break;
			case 2:
				pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_32;
				pchar.questTemp.PrisonGun.Price = 1300 + GetCharacterSPECIALSimple(PChar, SPECIAL_C)*GetSummonSkillFromName(pchar, SKILL_COMMERCE)/100*275;
                pchar.questTemp.PrisonGun.Qty = sti(makeint(pchar.rank)*4+10+rand(sti(pchar.rank)));
				pchar.questTemp.PrisonGun.Text = "пушки 32 калибра";
			break;
			case 3:
				pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_32;
				pchar.questTemp.PrisonGun.Price = 1500 + GetCharacterSPECIALSimple(PChar, SPECIAL_C)*GetSummonSkillFromName(pchar, SKILL_COMMERCE)/100*325;
                pchar.questTemp.PrisonGun.Qty = sti(makeint(pchar.rank)*4+10+rand(sti(pchar.rank)));
				pchar.questTemp.PrisonGun.Text = "кулеврины 32 калибра";
			break;
			case 4:
				pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_42;
				pchar.questTemp.PrisonGun.Price = 2100 + GetCharacterSPECIALSimple(PChar, SPECIAL_C)*GetSummonSkillFromName(pchar, SKILL_COMMERCE)/100*425;
                pchar.questTemp.PrisonGun.Qty = sti(makeint(pchar.rank)*3+20+rand(sti(pchar.rank)));
				pchar.questTemp.PrisonGun.Text = "пушки 42 калибра";
			break;
		}
}
