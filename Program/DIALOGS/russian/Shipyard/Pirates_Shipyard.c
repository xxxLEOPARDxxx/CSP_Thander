// диалог по городам
// Это мастер тюнинга
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    if ( sti(Pchar.Ship.Type) != SHIP_NOTUSED)
    {
	    int   	cannonQ       = sti(RealShips[sti(Pchar.Ship.Type)].CannonsQuantity);
		int   	cannonMax     = sti(RealShips[sti(Pchar.Ship.Type)].MaxCaliber);
		int		cannonMaxQ    = 0;
		if (CheckAttribute(&RealShips[sti(Pchar.Ship.Type)],"CannonsQuantityMax")) cannonMaxQ = sti(RealShips[sti(Pchar.Ship.Type)].CannonsQuantityMax);
		int   	shipClass     = sti(RealShips[sti(Pchar.Ship.Type)].Class);
		//int   shipPrice     = sti(RealShips[sti(Pchar.Ship.Type)].Price);
		int   	shipCapacity  = sti(RealShips[sti(Pchar.Ship.Type)].Capacity);
		float 	shipSpeedRate = stf(RealShips[sti(Pchar.Ship.Type)].SpeedRate);
		float 	MastMulti     = stf(RealShips[sti(Pchar.Ship.Type)].MastMultiplier);
		int   	shipMaxCrew   = sti(RealShips[sti(Pchar.Ship.Type)].MaxCrew);
		int   	shipHP        = sti(RealShips[sti(Pchar.Ship.Type)].HP);
		float 	shipTurnRate  = stf(RealShips[sti(Pchar.Ship.Type)].TurnRate);
		float 	shipWindAgainst = stf(RealShips[sti(Pchar.Ship.Type)].WindAgainstSpeed);
		int		cannonDiff		= cannonMaxQ - cannonQ;
		int 	iCaliber;

/*
		if(cannonDiff >= 2)
		{
			cannonDiff = 2;
			cannonMaxQ = cannonQ + cannonDiff;
		}
		else
		{
			cannonDiff = 0;
		}
*/
		float fQuestShip = 1.0;

		if(CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "QuestShip")) fQuestShip = 1.2;

		//int  zWorkPrice  = makeint(8000 * ((7-shipClass) * MOD_SKILL_ENEMY_RATE) * fQuestShip);
		int sundukSum = makeint(((7-shipClass)*1.0) * fQuestShip);

	    int  cannonMatherial1 = makeint((cannonQ * 2 + 35 * (7-shipClass) - 20) * fQuestShip);
	    int	 cannonMatherial2 = makeint((7-shipClass)/2 * fQuestShip);
		if (cannonMatherial2 < 1) cannonMatherial2 = 1;
	    int	 cannonMatherial3 = sundukSum;
		int  cannonWorkPrice  = makeint((100 * cannonQ * MOD_SKILL_ENEMY_RATE + 4000 * ((7-shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);

	    int  capacityMatherial1 = makeint((35 * (7-shipClass) + shipCapacity * 7/100) * fQuestShip);
	    int	 capacityMatherial2 = makeint((10 * (7-shipClass)+10) * fQuestShip);
	    int  capacityMatherial3 = sundukSum;
		int  capacityWorkPrice  = makeint((2 * shipCapacity * MOD_SKILL_ENEMY_RATE + 4000 * ((7-shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);

	    int  SpeedRateMatherial1 = makeint((shipHP * 25/1000 + 70 * (7-shipClass)) * fQuestShip);
	    int	 SpeedRateMatherial2 = makeint(5 * (7-shipClass) * fQuestShip);
	    int	 SpeedRateMatherial3 = sundukSum;
		int  SpeedRateWorkPrice  = makeint((100 * shipSpeedRate * MOD_SKILL_ENEMY_RATE + 4000 * ((7-shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);

		int  MastMultiplierMatherial1 = makeint((shipHP * 25/1000 + 70 * (7-shipClass)) * fQuestShip);
	    int	 MastMultiplierMatherial2 = makeint(5 * (7-shipClass) * fQuestShip);
	    int	 MastMultiplierMatherial3 = sundukSum;
		int  MastMultiplierMatherialWorkPrice  = makeint((100 * MastMulti * MOD_SKILL_ENEMY_RATE + 4000 * ((7-shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);

	    int  MaxCrewMatherial1 = makeint((shipMaxCrew * 6/10 + 50 * (7-shipClass)) * fQuestShip);
	    int	 MaxCrewMatherial2 = makeint((6 * (7-shipClass)+3) * fQuestShip);
	    int	 MaxCrewMatherial3 = sundukSum;
		int  MaxCrewWorkPrice  =  makeint((15 * shipMaxCrew * MOD_SKILL_ENEMY_RATE + 4000 * ((7-shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);

	    int  TurnRateMatherial1 = makeint((shipHP * 25/1000 + 375/shipClass+20) * fQuestShip);
	    int	 TurnRateMatherial2 = makeint((5 * (7-shipClass)+2) * fQuestShip);
	    int	 TurnRateMatherial3 = sundukSum;
		int  TurnRateWorkPrice  = makeint((30 * shipTurnRate * MOD_SKILL_ENEMY_RATE + 4000 * ((7-shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);

	    int  HPMatherial1 = makeint((35 * (7-shipClass) + shipHP * 7/100) * fQuestShip);
	    int	 HPMatherial2 = makeint(5 * ((7-shipClass)*3) * fQuestShip);
	    int	 HPMatherial3 = sundukSum;
		int  HPWorkPrice  = makeint((shipHP * MOD_SKILL_ENEMY_RATE + 4000 * ((7-shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);

	    int  WindAgainstMatherial1 = makeint((shipHP * 25/1000 + 750/shipClass+20) * fQuestShip);
	    int	 WindAgainstMatherial2 = makeint((6 * (7-shipClass)+1) * fQuestShip);
	    int	 WindAgainstMatherial3 = sundukSum;
		int  WindAgainstWorkPrice  = makeint((300 * shipSpeedRate * MOD_SKILL_ENEMY_RATE + 4000 * ((7-shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);

		int quantityMatherial1 = makeint((cannonQ * 2 + 35 * (7-shipClass) - 20) * fQuestShip);
		int quantityMatherial2 = makeint((7-shipClass)/2 * fQuestShip);
			if (quantityMatherial2 < 1) quantityMatherial2 = 1;
		int quantityMatherial3 = sundukSum;
		int cannonQWorkPrice = makeint((100 * cannonMaxQ * MOD_SKILL_ENEMY_RATE + 4000 * ((7-shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);

		int AllMatherial1 = cannonMatherial1 + quantityMatherial1;
		int AllMatherial2 = cannonMatherial2 + quantityMatherial2;
		int AllMatherial3 = cannonMatherial3 + quantityMatherial3;
		int cannonAllWorkPrice = cannonWorkPrice + cannonQWorkPrice;
		//int  zWorkPriceAll  = zWorkPrice * 2;


		float discount = 1.0;
  		if (CheckAttribute(NPChar, "Discount"))
		{
		    discount = 0.75;
		}

	    cannonMatherial1 = cannonMatherial1 * discount;
	    cannonMatherial2 = cannonMatherial2 * discount;
		cannonMatherial3 = cannonMatherial3 * discount;
		if (cannonMatherial3 < 1) cannonMatherial3 = 1;
	    cannonWorkPrice  = cannonWorkPrice * discount;

		quantityMatherial1 = quantityMatherial1 * discount;
		quantityMatherial2 = quantityMatherial2 * discount;
		quantityMatherial3 = quantityMatherial3 * discount;
		if (quantityMatherial3 < 1) quantityMatherial3 = 1;
		cannonQWorkPrice = cannonQWorkPrice * discount;

		AllMatherial1 = AllMatherial1 * discount;
		AllMatherial2 = AllMatherial2 * discount;
		AllMatherial3 = AllMatherial3 * discount;
		if (AllMatherial3 < 1) AllMatherial3 = 1;
		cannonAllWorkPrice = cannonAllWorkPrice * discount;

	    capacityMatherial1 = capacityMatherial1 * discount;
	    capacityMatherial2 = capacityMatherial2 * discount;
		capacityMatherial3 = capacityMatherial3 * discount;
		if (capacityMatherial3 < 1) capacityMatherial3 = 1;
	    capacityWorkPrice  = capacityWorkPrice * discount;

	    SpeedRateMatherial1 = SpeedRateMatherial1 * discount;
	    SpeedRateMatherial2 = SpeedRateMatherial2 * discount;
		SpeedRateMatherial3 = SpeedRateMatherial3 * discount;
		if (SpeedRateMatherial3 < 1) SpeedRateMatherial3 = 1;
	    SpeedRateWorkPrice  = SpeedRateWorkPrice * discount;

		MastMultiplierMatherial1 = MastMultiplierMatherial1 * discount;
	    MastMultiplierMatherial2 = MastMultiplierMatherial2 * discount;
		MastMultiplierMatherial3 = MastMultiplierMatherial3 * discount;
		if (MastMultiplierMatherial3 < 1) MastMultiplierMatherial3 = 1;
	    MastMultiplierMatherialWorkPrice  = MastMultiplierMatherialWorkPrice * discount;

	    MaxCrewMatherial1 = MaxCrewMatherial1 * discount;
	    MaxCrewMatherial2 = MaxCrewMatherial2 * discount;
		MaxCrewMatherial3 = MaxCrewMatherial3 * discount;
		if (MaxCrewMatherial3 < 1) MaxCrewMatherial3 = 1;
	    MaxCrewWorkPrice  = MaxCrewWorkPrice * discount;

	    TurnRateMatherial1 = TurnRateMatherial1 * discount;
	    TurnRateMatherial2 = TurnRateMatherial2 * discount;
		TurnRateMatherial3 = TurnRateMatherial3 * discount;
		if (TurnRateMatherial3 < 1) TurnRateMatherial3 = 1;
	    TurnRateWorkPrice  = TurnRateWorkPrice * discount;

	    HPMatherial1 = HPMatherial1 * discount;
	    HPMatherial2 = HPMatherial2 * discount;
		HPMatherial3 = HPMatherial3 * discount;
		if (HPMatherial3 < 1) HPMatherial3 = 1;
	    HPWorkPrice  = HPWorkPrice * discount;

	    WindAgainstMatherial1 = WindAgainstMatherial1 * discount;
	    WindAgainstMatherial2 = WindAgainstMatherial2 * discount;
		WindAgainstMatherial3 = WindAgainstMatherial3 * discount;
		if (WindAgainstMatherial3 < 1) WindAgainstMatherial3 = 1;
	    WindAgainstWorkPrice  = WindAgainstWorkPrice * discount;

		if (cannonMatherial2 < 1) cannonMatherial2 = 1;
		if (quantityMatherial2 < 1) quantityMatherial2 = 1;
	}

	int iTemp;
	string attr, attrLoc;
	int amount;
	ref shTo;
    string sTemp;
    string s1;

	switch (Dialog.CurrentNode)
	{

		// -----------------------------------Диалог первый - первая встреча
		case "First time":  // перехват основного диалога, только один раз
			if(NPChar.quest.meeting == "0")
			{
				Dialog.Text = "Кха... что за скверный климат... Меня зовут " + GetFullName(npchar) + ", и, дьявол меня побери, я лучший корабел на этих забытых Богом островах. Но эта сырость просто валит меня с ног...";
				Link.l1 = pcharrepphrase("Тысяча акул, только старческого брюзжания мне не хватало. Мое имя " + GetFullName(pchar) + ", думаю, вы обо мне слышали.",
					"Это не сырость, это старость, уважаемый. Меня зовут " + GetFullName(pchar) + ", думаю, вы обо мне слышали.");
				Link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else // нужно, если по квестам будет сброс на  "First time"
			{
				dialog.text = "А, это опять вы, опять со своими проблемами... кха... кха.";
				link.l1 = pcharrepphrase("Вы правы, это опять я. Но давайте поговорим о делах, пока вы не отдали Богу душу.",
					"У вас хорошая память, а теперь, если позволите, давайте перейдем к более конкретным вопросам.");
				link.l1.go = "node_3";
				link.l2 = pcharrepphrase("Вы утомили меня своим брюзжанием. Прощайте.",
					"Мне пора, извините, что побеспокоил"+ GetSexPhrase("","а") +".");
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "Master_Ship";
			Dialog.CurrentNode = "Master_Ship";
		break;

		case "Master_Ship":
			dialog.text = "А, это опять вы, опять со своими проблемами... кха... кха.";
			link.l1 = pcharrepphrase("Вы правы, это опять я. Но давайте поговорим о делах, пока вы не отдали Богу душу.",
	            "У вас хорошая память, а теперь, если позволите, давайте перейдем к более конкретным вопросам.");
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase("Вы утомили меня своим брюзжанием. Прощайте.",
				"Мне пора, извините, что побеспокоил"+ GetSexPhrase("","а") +".");
			link.l2.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;

		case "node_1":
			dialog.text = "Молодежь-молодежь, не дождешься от вас никакого почтения. Горячие головы, крепкие руки, что вам еще надо?";
			link.l1 = pcharrepphrase("Это верно. Но рано или поздно всему приходит конец, и похоже, ваше время уже близко...",
				"Что-то подсказывает мне, что вы в свои молодые годы тоже не отличались особым почтением к возрасту. Разве не так?");
			link.l1.go = "node_2";
		break;

		case "node_2":
			dialog.text = "Не перечь старшим, "+ GetSexPhrase("щенок","соплячка") +"!";
			link.l1 = pcharrepphrase("Ладно-ладно, не пыжтесь, а то удар хватит. Не хочу, чтоб меня обвинили в смерти лучшего корабела на Карибах. Давайте-ка лучше перейдем к делами.",
				"Я прощаю вам эту резкость, только из уважения к вашему возрасту. А теперь, если вы закончили, давайте лучше перейдем к делам.");
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase("Все, с меня хватит нравоучений! Прощайте!",
				"Я вижу, общего языка мы не найдем. Прощайте.");
			link.l2.go = "exit";
		break;

		case "node_3":
			dialog.text = "Кха, кха... не дают старику покоя. Что вам опять от меня нужно, " + GetAddress_Form(NPChar) + "? ";
			link.l1 = pcharrepphrase("Мне надо воспользоваться услугами верфи.","Я хочу воспользоваться услугами вашей верфи.");
			link.l1.go = "shipyard_dlg";
            Link.l2 = "У меня вопрос.";
			Link.l2.go = "quests"; //(пересылка в файл города)
			// -->
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l3 = "Я хотел"+ GetSexPhrase("","а") +" бы поговорить с вами о делах финансовых.";
				link.l3.go = "LoanForAll";//(перессылка в файл города)
			}
			link.l9 = pcharrepphrase("Черт, у меня есть пара неотложных дел, до свидания.", "Мне уже пора, извините.");
			link.l9.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;

		case "shipyard_dlg":
			dialog.Text = "Могу предложить работу со штучными заказами - улучшаю характеристики местным лоханкам. Здесь совершенно не умеют строить нормальные корабли.";
			Link.l1 = "Замечательно! Мне как раз нужно довести до ума свой кораблик. Может взглянете, что можно сделать?";
			Link.l1.go = "ship_tunning_start";
			link.l2 = "Нет, мне не нужно улучшений, я хочу просто воспользоваться услугами верфи.";
			link.l2.go = "shipyard";

			if (!CheckAttribute(npchar, "questTemp.ShipOrderTime"))
			{
			link.l5 = "А можно у вас на верфи заказать корабль, подходящий моим личным предпочтениям?";
			link.l5.go = "Shipyard1";
			}
			else
			{
			link.l5 = "Готов ли заказанный мною корабль?";
			link.l5.go = "shiporder1";
			}

			link.l3 = "Мне нужны орудия на корабль.";
			link.l3.go = "Cannons";
			link.l4 = "Хочу изменить внешний вид парусов.";
			link.l4.go = "SailsGerald";
			Link.l9 = "Не могу с вами согласиться. В здешних водах иногда попадаются очень неплохие корабли. До свидания.";
			Link.l9.go = "ship_tunning_not_now";
		break;

		case "Discount_1":
			dialog.Text = "Дешевле? Хм, пожалуй я готов дать скидку в 20 процентов на одну доводку, но только профессионалу, разбирающемуся в корабельном деле.";
			Link.l1 = "Уважаемый, перед вами профессиональный капитан, и свой корабль я знаю от киля до клотика. Давайте скидку!";
			Link.l1.go = "Discount_2";
			Link.l9 = "Ладно... пожалуй, придется обойтись без скидки.";
			Link.l9.go = "ship_tunning_start";
		break;

		case "Discount_2":
			dialog.Text = "Профессиональный капитан, говоришь? Ну это мы сейчас проверим!";
			Link.l1 = "Сколько вам будет угодно!";
			Link.l1.go = "Discount_3";
			LockControl("DlgDown3", true);
			LockControl("DlgUp3", true);
		break;

  		case "Discount_3":
            NPChar.SeaQuestions = rand(sti(NullCharacter.SeaQuestions));
            sTemp = sTemp = "q" + NPChar.SeaQuestions;
			dialog.Text = NullCharacter.SeaQuestions.(sTemp);

   			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Discount_4";
			Link.l9 = "Пожалуй, придется обойтись без скидки.";
			Link.l9.go = "ship_tunning_not_now";
		break;

		case "Discount_4":
   			sTemp = "a" + NPChar.SeaQuestions;
			if (NullCharacter.SeaQuestions.(sTemp) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "Верно!! Действительно знающий капитан"+ GetSexPhrase("",", хоть и женщина") +". Вы заслужили скидку!";
				link.l1 = "Я же говорил"+ GetSexPhrase("","а") +", что знаю. К делу.";
				link.l1.go = "ship_tunning_start";
				NPChar.Discount = true;
				LockControl("DlgDown3", false);
				LockControl("DlgUp3", false);
			}
			else
			{
				dialog.text = "Нет, неверно. Может стоит попробовать ещё?";
				link.l1 = "Да, попробую еще раз.";
				link.l1.go = "Discount_5";
				link.l2 = "Нет, этот вопрос слишком сложен для меня.";
				link.l2.go = "ship_tunning_not_now";
			}
		break;

		case "Discount_5":
            sTemp = sTemp = "q" + NPChar.SeaQuestions;
			dialog.Text = NullCharacter.SeaQuestions.(sTemp);
   			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Discount_4";
			Link.l9 = "Нет, думаю не осилю.";
			Link.l9.go = "ship_tunning_not_now";
		break;

		case "ship_tunning_again":
			dialog.Text = RandPhraseSimple("А... это опять вы... Снова решили свой кораблик поправить?",
			RandPhraseSimple("Приветствую известного капитан. Что, снова кораблик не устраивает?",
                                           "Эх... ни минуты покоя нет, не даете старику сосредоточиться.. Опять улучшения понадобились?"));
			Link.l1 = "Да. Есть такое дело. Может посмотрим, что можно сделать еще?";
			Link.l1.go = "ship_tunning_start";
			link.l2 = "Нет, мне не нужно улучшений, я хочу просто воспользоваться услугами верфи.";
			link.l2.go = "shipyard";

			if (!CheckAttribute(npchar, "questTemp.ShipOrderTime"))
			{
			link.l6 = "А можно у вас на верфи заказать корабль, подходящий моим личным предпочтениям?";
			link.l6.go = "Shipyard1";
			}
			else
			{
			link.l6 = "Готов ли заказанный мною корабль?";
			link.l6.go = "shiporder1";
			}

			link.l3 = "Мне нужны орудия на корабль.";
			link.l3.go = "Cannons";
			link.l31 = "Хочу изменить внешний вид парусов.";
			link.l31.go = "SailsGerald";
            Link.l4 = "У меня вопрос.";
			Link.l4.go = "quests"; //(пересылка в файл города)
			// -->
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l5 = "Я хотел"+ GetSexPhrase("","а") +" бы поговорить с вами о делах финансовых.";
				link.l5.go = "LoanForAll";//(пересылка в файл города)
			}
			Link.l9 = "Нет. Меня устраивает то, что есть";
			Link.l9.go = "ship_tunning_not_now_2";
		break;

        case "ship_tunning_not_now_2":
			dialog.Text = "Да ты, я погляжу, еще и думаешь! Далеко пойдешь! Приходи, когда решишься и не отвлекай меня по пустякам.";
			Link.l1 = RandPhraseSimple("Спасибо! Всего хорошего.", "Пока, мастер. Можно и без сарказма.");
			Link.l1.go = "ship_tunning_not_now";
		break;

        case "ship_tunning_start":
			if ( sti(Pchar.Ship.Type) == SHIP_NOTUSED || Pchar.location.from_sea != "Pirates_town")
            {
                dialog.Text = "Корабль-то где? Что вы мне тут голову морочите?!";
			    Link.l1 = "И то правда.. что это я... Извиняюсь";
			    Link.l1.go = "ship_tunning_not_now";
            }
            else
            {
			    if (GetHour() == 13)
			    {
					dialog.Text = "Я, конечно, трудоголик, но и у меня есть обеденное время. Приходите позже!";
			        Link.l1 = "Понятно...";
			        Link.l1.go = "ship_tunning_not_now";
			    }
			    else
			    {
                    if (shipClass == 7)
                    {
						dialog.Text = "Эээ.. Лодками я не занимаюсь. Корыто корытом и останется, сколько над ним ни колдуй.";
    			        Link.l1 = "Понятно...";
    			        Link.l1.go = "ship_tunning_not_now";
    			        break;
                    }

                    s1 = "Так-так... посмотрим, что тут у нас есть... Ага " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) + ".";
    			    if (sti(RealShips[sti(Pchar.Ship.Type)].Stolen) == true && !CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning"))
    			    {
    			        s1 = s1 + " Ба! Да корабль-то побывал не в одних руках. То-то он такой потертый. Патент корсарский у тебя есть? Ладно шучу... к делу.";
    			    }
    			    s1 = s1 + " Что бы ты хотел"+ GetSexPhrase("","а") +" с ним делать?";
                    dialog.Text = s1;

					if (RealShips[sti(Pchar.Ship.Type)].BaseName == "Wh_corvette_quest")
					{//Капремонт пса
						dialog.text = "Итак, 'Пёс войны'. Что будем с ним делать?";
						if(!CheckAttribute(npchar, "WarDogUpgrade"))
						{
							npchar.WarDogUpgrade = "start";
							dialog.text = "Посмотрим... Так! Это что, шутка? 'Пёс войны'? Пришла разбередить мою старую рану?";
							link.l1 = "Что? О чём вы?";
							link.l1.go = "WarDogUpgrade_1";
							break;
						}
						if(CheckAttribute(pchar, "TitanicIsDown"))
						{
							link.lWarDogUpgrade = "Уже слыхал? Непотопляемый потонул. Репутация твоего ученика навсегда втоптана в грязь. ";
							link.lWarDogUpgrade.go = "WarDogUpgrade_8";
						}
						if(CheckAttribute(npchar, "WarDogUpgradePayment") && sti(pchar.money) >= 1000000)
						{
							link.lWarDogUpgrade = "Я принесла ваш миллион. Надеюсь этот ремонт действительно того стоит.";
							link.lWarDogUpgrade.go = "WarDogUpgrade_pay";
						}

					}

					if (cannonMax < 36 && cannonDiff > 0 && !CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Cannon"))
					{
						Link.l1 = "Увеличить калибр и максимальное количество орудий.";
						Link.l1.go = "ship_tunning_cannon_all";
					}
					else
					{
                    if (cannonMax < 36 && !CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Cannon"))
                    {
                        Link.l1 = "Увеличить калибр орудий.";
    			        Link.l1.go = "ship_tunning_cannon";
    			    }
						else
						{
							if (cannonDiff > 0)
							{
								Link.l1 = "Увеличить максимальное количество орудий.";
								Link.l1.go = "ship_c_quantity";
							}
						}
					}

    			    if (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Capacity"))
                    {
    			        Link.l2 = "Увеличить дедвейт.";
    			        Link.l2.go = "ship_tunning_Capacity";
    			    }
					if (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MastMultiplier"))
                    {
    			        Link.l3 = "Увеличить прочность мачт.";
    			        Link.l3.go = "ship_tunning_MastMultiplier";
    			    }
					if (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.SpeedRate"))
                    {
    			        Link.l4 = "Увеличить скорость.";
    			        Link.l4.go = "ship_tunning_SpeedRate";
    			    }
    			    if (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.TurnRate"))
                    {
    			        Link.l5 = "Увеличить маневренность.";
    			        Link.l5.go = "ship_tunning_TurnRate";
    			    }
    			    if (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MaxCrew"))
                    {
    			        Link.l6 = "Прибавить место для экипажа.";
    			        Link.l6.go = "ship_tunning_MaxCrew";
    			    }
    			    if (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.HP"))
                    {
    			        Link.l7 = "Увеличить прочность корпуса.";
    			        Link.l7.go = "ship_tunning_HP";
    			    }
    			    if (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.WindAgainst"))
                    {
    			        Link.l8 = "Увеличить ход в бейдевинд.";
    			        Link.l8.go = "ship_tunning_WindAgainst";
    			    }
    			    Link.l10 = "Постойте! Я передумал"+ GetSexPhrase("","а") +".";
    			    Link.l10.go = "ship_tunning_not_now_2";
			    }
			}
		break;

		////////////////////////////////////////// калибр и количество орудий  ////////////////////////////////////////////////////
		case "ship_tunning_cannon_all":
			s1 = "Давайте посмотрим, что можно сделать. Сейчас орудий на вашем корабле " + cannonQ + ", максимально возможное количество - " + cannonMaxQ + ",";
			s1 = s1 + " максимальный калибр - " + cannonMax + ". Для усиления портиков и укрепления лафетов мне понадобится: черного дерева - "+AllMatherial1 + ".";
			s1 = s1 + " Я стар, и не собираюсь вечно гнить в этой дыре, поэтому за работу возьму: сокровищ - "+AllMatherial2 + ", сундуков с золотом - "+AllMatherial3 + ",";
			s1 = s1 + " плюс - " + cannonAllWorkPrice + " пиастров на рабочие расходы. Вы же понимаете - дело непростое... Ах да - и деньги вперед.";

			dialog.Text = s1;
			Link.l1 = "Годится. Я принимаю условия. Всё оговоренное будет доставлено.";
			Link.l1.go = "ship_tunning_cannon_all_start";
			Link.l2 = "Нет. Меня это не устраивает.";
			Link.l2.go = "ship_tunning_not_now";
			if (!CheckAttribute(NPChar, "Discount"))
			{
				Link.l3 = "А почему так дорого? Нельзя ли как-то снизить расценки?";
				Link.l3.go = "Discount_1";
			}
			if (bBettaTestMode)
			{
				Link.l4 = "КАЧАЙ НЕМЕДЛЕННО!";
				Link.l4.go = "ship_tunning_cannon_all_complite";
			}
		break;

		case "ship_tunning_cannon_all_start":
			amount = cannonAllWorkPrice;
		    if(makeint(Pchar.money) >= amount)
			{
				AddMoneyToCharacter(Pchar, -amount);
			    NPChar.Tuning.Money  = amount;
				NPChar.Tuning.Cannon = true;

				NPChar.Tuning.Matherial1 = AllMatherial1; // черное дерево
				NPChar.Tuning.Matherial2 = AllMatherial2; // кожа
				NPChar.Tuning.Matherial3 = AllMatherial3;
				NPChar.Tuning.ShipType       = Pchar.Ship.Type;
				NPChar.Tuning.ShipName       = RealShips[sti(Pchar.Ship.Type)].BaseName;
				DeleteAttribute(NPChar, "Discount");

				NextDiag.TempNode = "ship_tunning_cannon_all_again";
				dialog.text = "Вот и славно. Жду материал и мои драгоценности.";
				link.l1 = "Побежал"+ GetSexPhrase("","а") +" за ними...";
				link.l1.go = "Exit";

				ReOpenQuestHeader("ShipTuning");
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "За свою работу по увеличению калибра и количества орудий на корабле " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
					" мастер-корабел затребовал: черного дерева - " + NPChar.Tuning.Matherial1 + ", сокровищ - "+ NPChar.Tuning.Matherial2+ ", сундуков с золотом - " + NPChar.Tuning.Matherial3 + ". В качестве задатка было уплачено " + NPChar.Tuning.Money + " золотых. Видимо, старик без ума от драгоценностей. Что ж - у каждого свои слабости...");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now";
				dialog.text = "Не вижу задатка...";
				link.l1 = "Я позже зайду";
				link.l1.go = "Exit";
			}
		break;

		case "ship_tunning_cannon_all_again":
			if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName      == RealShips[sti(Pchar.Ship.Type)].BaseName)
			{
				NextDiag.TempNode = "ship_tunning_cannon_all_again";
				dialog.Text = "Орудия ждут. Принес"+ GetSexPhrase("","ла") +", что я просил?";
				Link.l1 = "Да. Кое-что удалось достать.";
				Link.l1.go = "ship_tunning_cannon_all_again_2";
				Link.l2 = "Я хочу воспользоваться услугами верфи.";
				Link.l2.go = "PayToRapair1";
				link.l3 = "Нет. Еще добываю.";
				link.l3.go = "exit";
			}
			else
			{
				DeleteAttribute(NPChar, "Tuning");
				NextDiag.TempNode = "ship_tunning_again";
				dialog.Text = "Сдается мне, судар"+ GetSexPhrase("ь","ыня") +", что вы поменяли корабль со времени нашего уговора. Придеться все заново расчитывать..";
				Link.l1 = "Было дело. Обидно, что задаток пропал...";
				Link.l1.go = "Exit";
				AddQuestRecord("ShipTuning", "Lose");
				AddQuestUserData("ShipTuning", "sSex", GetSexPhrase("","а"));
				CloseQuestHeader("ShipTuning");
			}
		break;

		case "ship_tunning_cannon_all_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_EBONY, "icollection", "chest");

			if(sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Matherial3) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
				NextDiag.TempNode = "ship_tunning_again";
				dialog.text = "Все привез"+ GetSexPhrase("","ла") +". Молодец! Начинаю работу...";
				link.l1 = "Жду.";
				link.l1.go = "ship_tunning_cannon_all_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_cannon_all_again";
				dialog.Text = "Тебе осталось привезти: черного дерева - "+ sti(NPChar.Tuning.Matherial1) + ", сокровищ - "+ sti(NPChar.Tuning.Matherial2) + ", сундуков - "+ sti(NPChar.Tuning.Matherial3) + ".";
				link.l1 = "Хорошо.";
				link.l1.go = "Exit";

				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "Мне осталось довезти: черного дерева - "+ sti(NPChar.Tuning.Matherial1) + ", сокровищ - "+ sti(NPChar.Tuning.Matherial2) + ", сундуков - "+ sti(NPChar.Tuning.Matherial3) + ".");
			}
		break;

		case "ship_tunning_cannon_all_complite":
			AddTimeToCurrent(8, 30);
			shTo = &RealShips[sti(Pchar.Ship.Type)];
			DeleteAttribute(NPChar, "Tuning");

			// изменим калибр орудий
			iCaliber = sti(shTo.MaxCaliber);
			switch(iCaliber)
			{
				case 8:
					iCaliber = 0;
				break;
				case 12:
					iCaliber = 1;
				break;
				case 16:
					iCaliber = 2;
				break;
				case 20:
					iCaliber = 3;
				break;
				case 24:
					iCaliber = 4;
				break;
				case 32:
					iCaliber = 5;
				break;
				case 36:
					iCaliber = 6;
				break;
			}
			iCaliber = iCaliber + 1;
			if (iCaliber > 6) iCaliber = 6;
			switch(iCaliber)
			{
				case 0:
					iCaliber = 8;
				break;
				case 1:
					iCaliber = 12;
				break;
				case 2:
					iCaliber = 16;
				break;
				case 3:
					iCaliber = 20;
				break;
				case 4:
					iCaliber = 24;
				break;
				case 5:
					iCaliber = 32;
				break;
				case 6:
					iCaliber = 36;
				break;
			}
			shTo.MaxCaliber = iCaliber;

			// изменим количество орудий
			shTo.rcannon = sti(shTo.rcannon) + cannonDiff/2;
			shTo.lcannon = sti(shTo.rcannon);
			shTo.CannonsQuantity = sti(shTo.rcannon) + sti(shTo.lcannon) + sti(shTo.fcannon) + sti(shTo.bcannon);

			Pchar.Ship.Cannons.Borts.cannonl = sti(shTo.lcannon);
			Pchar.Ship.Cannons.Borts.cannonr = sti(shTo.rcannon);
			Pchar.Ship.Cannons.Borts.cannonf = sti(shTo.fcannon);
			Pchar.Ship.Cannons.Borts.cannonb = sti(shTo.bcannon);
			Pchar.Ship.Cannons = sti(shTo.CannonsQuantity);
			shTo.Tuning.Cannon = true;

			// finish <--
			NextDiag.TempNode = "ship_tunning_again";
			s1 = "... Ну вот, вроде бы все... Можешь увеличивать калибр и докупать орудия.";
			s1 = s1 + " Это, кстати, можно сделать и на моей верфи.";
			dialog.Text = s1;
			Link.l1 = "Спасибо! Обязательно всё проверю.";
			Link.l1.go = "Exit";

			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;


		////////////////////////////////////////// только количество орудий  ////////////////////////////////////////////////////
		case "ship_c_quantity":
			s1 = "Давайте посмотрим, что можно сделать. Сейчас орудий на вашем корабле " + cannonQ + ", максимально возможное количество - " + cannonMaxQ + ".";
			s1 = s1 + " Вам это дело обойдется недешево, для новых орудийных лафетов мне понадобится: черного дерева - "+quantityMatherial1+ ",";
			s1 = s1 + " кроме того, за работу я возьму: сокровищ - "+quantityMatherial2+ ", сундуков с золотом - "+quantityMatherial3+ ",";
			s1 = s1 + " плюс - " + cannonQWorkPrice + " пиастров на рабочие расходы. Вы же понимаете - дело непростое... Ах да - и деньги вперед.";
			dialog.Text = s1;
			Link.l1 = "Годится. Я принимаю условия. Всё оговоренное будет доставлено.";
			Link.l1.go = "ship_c_quantity_start";
			Link.l2 = "Нет. Меня это не устраивает.";
			Link.l2.go = "ship_tunning_not_now";
			if (!CheckAttribute(NPChar, "Discount"))
			{
				Link.l3 = "А почему так дорого? Нельзя ли как-то снизить расценки?";
				Link.l3.go = "Discount_1";
			}
			if (bBettaTestMode)
			{
				Link.l4 = "КАЧАЙ НЕМЕДЛЕННО!";
				Link.l4.go = "ship_c_quantity_complite";
			}

		break;

		case "ship_c_quantity_start":
			amount = cannonQWorkPrice;
		    if(makeint(Pchar.money) >= amount)
			{
				AddMoneyToCharacter(Pchar, -amount);
			    NPChar.Tuning.Money  = amount;
				NPChar.Tuning.Cannon = true;

				NPChar.Tuning.Matherial1 = quantityMatherial1; // черное дерево
				NPChar.Tuning.Matherial2 = quantityMatherial2; // кожа
			        NPChar.Tuning.Matherial3 = quantityMatherial3;
				NPChar.Tuning.ShipType       = Pchar.Ship.Type;
				NPChar.Tuning.ShipName       = RealShips[sti(Pchar.Ship.Type)].BaseName;
				DeleteAttribute(NPChar, "Discount");

				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.text = "Вот и славно. Жду материал и мои драгоценности.";
				link.l1 = "Побежал"+ GetSexPhrase("","а") +" за ними...";
				link.l1.go = "Exit";

				ReOpenQuestHeader("ShipTuning");
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "За свою работу по увеличению количества орудий на корабле " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
				" мастер-корабел требует: черного дерева - " + NPChar.Tuning.Matherial1 + ", сокровищ - "+ NPChar.Tuning.Matherial2+ ", сундуков с золотом - " + NPChar.Tuning.Matherial3 + ". В качестве задатка было уплачено " + NPChar.Tuning.Money + " золотых. Видимо, старик без ума от драгоценностей. Что ж - у каждого свои слабости...");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now";
				dialog.text = "Не вижу задатка...";
				link.l1 = "Я позже зайду.";
				link.l1.go = "Exit";
			}
		break;

		case "ship_c_quantity_again":
			if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName      == RealShips[sti(Pchar.Ship.Type)].BaseName)
			{
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.Text = "Орудия ждут. Принес"+ GetSexPhrase("","ла") +", что я просил?";
				Link.l1 = "Да. Кое-что удалось достать.";
				Link.l1.go = "ship_c_quantity_again_2";
				Link.l2 = "Я хочу воспользоваться услугами верфи.";
				Link.l2.go = "PayToRapair1";
				link.l3 = "Нет. Еще добываю.";
				link.l3.go = "exit";
			}
			else
			{
				DeleteAttribute(NPChar, "Tuning");
				NextDiag.TempNode = "ship_tunning_again";
				dialog.Text = "Сдается мне, судар"+ GetSexPhrase("ь","ыня") +", что вы поменяли корабль со времени нашего уговора. Придеться все заново расчитывать...";
				Link.l1 = "Было дело. Обидно, что задаток пропал...";
				Link.l1.go = "Exit";
				AddQuestRecord("ShipTuning", "Lose");
				CloseQuestHeader("ShipTuning");
			}
		break;

		case "ship_c_quantity_again_2":
			checkMatherial(Pchar, NPChar, GOOD_EBONY, "icollection", "chest");

			if(sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Matherial3) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
				NextDiag.TempNode = "ship_tunning_again";
				dialog.text = "Все привез"+ GetSexPhrase("","ла") +". Молодец! Начинаю работу...";
				link.l1 = "Жду.";
				link.l1.go = "ship_c_quantity_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.Text = "Тебе осталось привезти: черного дерева - "+ sti(NPChar.Tuning.Matherial1) + ", сокровищ - "+ sti(NPChar.Tuning.Matherial2) + ", сундуков - "+ sti(NPChar.Tuning.Matherial3) + ".";
				link.l1 = "Хорошо.";
				link.l1.go = "Exit";

				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "Мне осталось довезти: черного дерева - "+ sti(NPChar.Tuning.Matherial1) + ", сокровищ - "+ sti(NPChar.Tuning.Matherial2) + ", сундуков - "+ sti(NPChar.Tuning.Matherial3) + ".");
			}
		break;

		case "ship_c_quantity_complite":
			AddTimeToCurrent(6, 30);
			shTo = &RealShips[sti(Pchar.Ship.Type)];
			DeleteAttribute(NPChar, "Tuning");

			// изменим количество орудий
			shTo.rcannon = sti(shTo.rcannon) + cannonDiff/2;
			shTo.lcannon = sti(shTo.rcannon);
			shTo.CannonsQuantity = sti(shTo.rcannon) + sti(shTo.lcannon) + sti(shTo.fcannon) + sti(shTo.bcannon);

			Pchar.Ship.Cannons.Borts.cannonl = sti(shTo.lcannon);
			Pchar.Ship.Cannons.Borts.cannonr = sti(shTo.rcannon);
			Pchar.Ship.Cannons.Borts.cannonf = sti(shTo.fcannon);
			Pchar.Ship.Cannons.Borts.cannonb = sti(shTo.bcannon);
			Pchar.Ship.Cannons = sti(shTo.CannonsQuantity);
			shTo.Tuning.Cannon = true;
			// finish <--
			NextDiag.TempNode = "ship_tunning_again";
			dialog.Text = "... Вроде бы все... Можешь докупать дополнительные орудия.";
			Link.l1 = "Спасибо!";
			Link.l1.go = "Exit";

			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;

		////////////////////////////////////////// только калибр орудий ////////////////////////////////////////////////////
		case "ship_tunning_cannon":
			s1 = "Давайте посмотрим, что можно сделать. Сейчас орудий на вашем корабле " + cannonQ + ", максимальный калибр - " + cannonMax + ".";

			s1 = s1 + " Для усиления портиков и лафетов тяжелых орудий мне понадобится: черного дерева - "+ cannonMatherial1 + ".";
			s1 = s1 + " И за работу я возьму: сокровищ - "+ cannonMatherial2 + ", сундуков с золотом - "+ cannonMatherial3 + ",";
			s1 = s1 + " плюс - " + cannonWorkPrice + " пиастров на рабочие расходы. Вы же понимаете - дело непростое... Ах да - и деньги вперед.";
            dialog.Text = s1;
			Link.l1 = "Годится. Я принимаю условия. Всё оговоренное будет доставлено.";
			Link.l1.go = "ship_tunning_cannon_start";
			Link.l2 = "Нет. Меня это не устраивает.";
			Link.l2.go = "ship_tunning_not_now";
			if (!CheckAttribute(NPChar, "Discount"))
			{
			    Link.l3 = "А почему так дорого? Нельзя ли как-то снизить расценки?";
				Link.l3.go = "Discount_1";
			}
			if (bBettaTestMode)
			{
				Link.l4 = "КАЧАЙ НЕМЕДЛЕННО!";
				Link.l4.go = "ship_tunning_cannon_complite";
			}
		break;

		case "ship_tunning_cannon_start":
		    amount = cannonWorkPrice;
		    if(makeint(Pchar.money) >= amount)
			{
				AddMoneyToCharacter(Pchar, -amount);
			    NPChar.Tuning.Money  = amount;
				NPChar.Tuning.Cannon = true;
			    NPChar.Tuning.Matherial1 = cannonMatherial1; // черное дерево
			    NPChar.Tuning.Matherial2 = cannonMatherial2; // кожа
			    NPChar.Tuning.Matherial3 = cannonMatherial3;
			    NPChar.Tuning.ShipType       = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName       = RealShips[sti(Pchar.Ship.Type)].BaseName;
			    DeleteAttribute(NPChar, "Discount");

				NextDiag.TempNode = "ship_tunning_cannon_again";
                dialog.text = "Вот и славно. Жду материал и мои драгоценности.";
			    link.l1 = "Побежал"+ GetSexPhrase("","а") +" за ними...";
			    link.l1.go = "Exit";

			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "За свою работу по увеличению калибра орудий на корабле " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
				" мастер-корабел требует: черного дерева - " + NPChar.Tuning.Matherial1 + ", сокровищ - "+ NPChar.Tuning.Matherial2+ ", сундуков с золотом - " + NPChar.Tuning.Matherial3 + ". В качестве задатка было уплачено " + NPChar.Tuning.Money + " золотых. Видимо, старик без ума от драгоценностей. Что ж - у каждого свои слабости...");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now";
                dialog.text = "Не вижу задатка...";
				link.l1 = "Я позже зайду.";
				link.l1.go = "Exit";
			}
		break;

		case "ship_tunning_cannon_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName      == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_tunning_cannon_again";
				dialog.Text = "Орудия ждут. Принес"+ GetSexPhrase("","ла") +", что я просил?";
			    Link.l1 = "Да. Кое-что удалось достать.";
			    Link.l1.go = "ship_tunning_cannon_again_2";
				Link.l2 = "Я хочу воспользоваться услугами верфи.";
				Link.l2.go = "PayToRapair1";
				link.l3 = "Нет. Еще добываю.";
				link.l3.go = "exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
			    dialog.Text = "Сдается мне, судар"+ GetSexPhrase("ь","ыня") +", что вы поменяли корабль со времени нашего уговора. Придеться все заново расчитывать..";
			    Link.l1 = "Было дело. Обидно, что задаток пропал...";
			    Link.l1.go = "Exit";
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;

		case "ship_tunning_cannon_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_EBONY, "icollection", "chest");

		    if(sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Matherial3) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
                dialog.text = "Все привез"+ GetSexPhrase("","ла") +". Молодец! Начинаю работу...";
			    link.l1 = "Жду.";
			    link.l1.go = "ship_tunning_cannon_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_cannon_again";
				dialog.Text = "Тебе осталось привезти: черного дерева - "+ sti(NPChar.Tuning.Matherial1) + ", сокровищ - "+ sti(NPChar.Tuning.Matherial2) + ", сундуков - "+ sti(NPChar.Tuning.Matherial3) + ".";
				link.l1 = "Хорошо.";
				link.l1.go = "Exit";

                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "Мне осталось довезти: черного дерева - "+ sti(NPChar.Tuning.Matherial1) + ", сокровищ - "+ sti(NPChar.Tuning.Matherial2) + ", сундуков - "+ sti(NPChar.Tuning.Matherial3) + ".");
			}
		break;

		case "ship_tunning_cannon_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
			// изменим калибр орудий
			iCaliber = sti(shTo.MaxCaliber);
			switch(iCaliber)
			{
				case 8:
					iCaliber = 0;
				break;
				case 12:
					iCaliber = 1;
				break;
				case 16:
					iCaliber = 2;
				break;
				case 20:
					iCaliber = 3;
				break;
				case 24:
					iCaliber = 4;
				break;
				case 32:
					iCaliber = 5;
				break;
				case 36:
					iCaliber = 6;
				break;
			}
			iCaliber = iCaliber + 1;
			if (iCaliber > 6) iCaliber = 6;
			switch(iCaliber)
			{
				case 0:
					iCaliber = 8;
				break;
				case 1:
					iCaliber = 12;
				break;
				case 2:
					iCaliber = 16;
				break;
				case 3:
					iCaliber = 20;
				break;
				case 4:
					iCaliber = 24;
				break;
				case 5:
					iCaliber = 32;
				break;
				case 6:
					iCaliber = 36;
				break;
			}
			shTo.MaxCaliber = iCaliber;
			shTo.Tuning.Cannon = true;
			// finish <--
            NextDiag.TempNode = "ship_tunning_again";
			dialog.Text = "... Вроде бы все... Можешь менять калибр - качество гарантирую.";
			Link.l1 = "Спасибо! Проверю обязательно.";
			Link.l1.go = "Exit";

			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;

		////////////////////////////////////////// трюм ////////////////////////////////////////////////////
		case "ship_tunning_Capacity":
			s1 = "Давайте посмотрим, что можно сделать. Сейчас дедвейт вашего судна - "+ shipCapacity;

			s1 = s1 + ". Для облегченных переборок мне понадобится: сандала - "+ capacityMatherial1 + ".";
			s1 = s1 + " В оплату за свою работу я возьму: золотых слитков - "+ capacityMatherial2 + ", сундуков с золотом - "+ capacityMatherial3 + ",";
			s1 = s1 + " плюс - " + capacityWorkPrice + " пиастров на рабочие расходы. Вроде бы всё. Ах да - деньги вперед.";
            dialog.Text = s1;
			Link.l1 = "Годится. Я принимаю условия. Всё оговоренное будет доставлено.";
			Link.l1.go = "ship_tunning_Capacity_start";
			Link.l2 = "Нет. Меня это не устраивает.";
			Link.l2.go = "ship_tunning_not_now";
			if (!CheckAttribute(NPChar, "Discount"))
			{
			    Link.l3 = "А почему так дорого? Нельзя ли снизить расценки?";
				Link.l3.go = "Discount_1";
			}
			if (bBettaTestMode)
			{
				Link.l4 = "КАЧАЙ НЕМЕДЛЕННО!";
				Link.l4.go = "ship_tunning_Capacity_complite";
			}

		break;

		case "ship_tunning_Capacity_start":
		    amount = capacityWorkPrice;
		    if(makeint(Pchar.money) >= amount)
			{
				AddMoneyToCharacter(Pchar, -amount);
			    NPChar.Tuning.Money  = amount;
			    NPChar.Tuning.Matherial1 = capacityMatherial1; // красное дерево GOOD_MAHOGANY
			    NPChar.Tuning.Matherial2 = capacityMatherial2; //  GOOD_OIL
			    NPChar.Tuning.Matherial3 = capacityMatherial3;
			    NPChar.Tuning.ShipType       = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName       = RealShips[sti(Pchar.Ship.Type)].BaseName;
			    DeleteAttribute(NPChar, "Discount");

				NextDiag.TempNode = "ship_tunning_Capacity_again";
                dialog.text = "Вот и славно. Жду материал и мои драгоценности.";
			    link.l1 = "Побежал"+ GetSexPhrase("","а") +" за ними...";
			    link.l1.go = "Exit";

			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "За свою работу по увеличению дедвейта на корабле " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
				" мастер-корабел требует: сандала - " + NPChar.Tuning.Matherial1 + ", золотых слитков - "+ NPChar.Tuning.Matherial2+ ", сундуков с золотом - " + NPChar.Tuning.Matherial3 + ". В качестве задатка было уплачено " + NPChar.Tuning.Money + " золотых. Видимо, старик без ума от драгоценностей. Что ж - у каждого свои слабости...");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now";
                dialog.text = "Не вижу задатка...";
				link.l1 = "Я позже зайду.";
				link.l1.go = "Exit";
			}
		break;

		case "ship_tunning_Capacity_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName      == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_tunning_Capacity_again";
				dialog.Text = "Дедвейт ждет. Принес"+ GetSexPhrase("","ла") +", что я просил?";
			    Link.l1 = "Да. Кое-что удалось достать.";
			    Link.l1.go = "ship_tunning_Capacity_again_2";
				Link.l2 = "Я хочу воспользоваться услугами верфи.";
				Link.l2.go = "PayToRapair1";
				link.l3 = "Нет. Еще добываю.";
				link.l3.go = "exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
			    dialog.Text = "Сдается мне, судар"+ GetSexPhrase("ь","ыня") +", что вы поменяли корабль со времени нашего уговора. Придеться все заново расчитывать...";
			    Link.l1 = "Было дело. Обидно, что задаток пропал...";
			    Link.l1.go = "Exit";

			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;

		case "ship_tunning_Capacity_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SANDAL, "jewelry5", "chest");

		    if(sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Matherial3) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
                dialog.text = "Все привез"+ GetSexPhrase("","ла") +". Молодец! Начинаю работу...";
			    link.l1 = "Жду.";
			    link.l1.go = "ship_tunning_Capacity_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_Capacity_again";
				dialog.Text = "Тебе осталось привезти: сандала - "+ sti(NPChar.Tuning.Matherial1) + ", золотых слитков - "+ sti(NPChar.Tuning.Matherial2) + ", сундуков - "+ sti(NPChar.Tuning.Matherial3) + ".";
				link.l1 = "Хорошо.";
				link.l1.go = "Exit";

                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "Мне осталось довезти: сандала - "+ sti(NPChar.Tuning.Matherial1) + ", золотых слитков - "+ sti(NPChar.Tuning.Matherial2) + ", сундуков - "+ sti(NPChar.Tuning.Matherial3) + ".");
			}
		break;

		case "ship_tunning_Capacity_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_Capacity"))
			{
				shTo.Capacity        = sti(shTo.Capacity) + makeint(sti(shTo.Capacity)/5);
			}
			else
			{
				shTo.Capacity        = makeint((sti(shTo.Capacity) - sti(shTo.Bonus_Capacity)) * 1.2 + sti(shTo.Bonus_Capacity));
			}
	        shTo.Tuning.Capacity = true;
	        // finish <--
            NextDiag.TempNode = "ship_tunning_again";
			dialog.Text = "... Вроде бы все... Можешь грузиться по полной - качество работы гарантирую.";
			Link.l1 = "Спасибо! Проверю обязательно.";
			Link.l1.go = "Exit";

			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;

		////////////////////////////////////////// SpeedRate ////////////////////////////////////////////////////
		case "ship_tunning_SpeedRate":
			s1 = "Давайте посмотрим, что можно сделать. Сейчас скорость вашего корабля " + shipSpeedRate;

			s1 = s1 + " узлов. Для новых парусов мне понадобится: шелка - "+ SpeedRateMatherial1 + ".";
			s1 = s1 + " Я стар, и не собираюсь вечно гнить в этой дыре, поэтому за работу возьму: сундуков с золотом - "+ SpeedRateMatherial3 + ", хороших граненых алмазов - "+ SpeedRateMatherial2 + ", плюс - " + SpeedRateWorkPrice + " пиастров на рабочие расходы. Вроде бы всё. Ах да - и деньги вперед.";

            dialog.Text = s1;
			Link.l1 = "Годится. Я принимаю условия. Всё оговоренное будет доставлено.";
			Link.l1.go = "ship_tunning_SpeedRate_start";
			Link.l2 = "Нет. Меня это не устраивает.";
			Link.l2.go = "ship_tunning_not_now";
			if (!CheckAttribute(NPChar, "Discount"))
			{
			    Link.l3 = "А почему так дорого? Нельзя ли снизить расценки?";
				Link.l3.go = "Discount_1";
			}
			if (bBettaTestMode)
			{
				Link.l4 = "КАЧАЙ НЕМЕДЛЕННО!";
				Link.l4.go = "ship_tunning_SpeedRate_complite";
			}

		break;

		case "ship_tunning_SpeedRate_start":
		    amount = SpeedRateWorkPrice;
		    if(makeint(Pchar.money) >= amount)
			{
				AddMoneyToCharacter(Pchar, -amount);
			    NPChar.Tuning.Money  = amount;
			    NPChar.Tuning.Matherial1 = SpeedRateMatherial1; // GOOD_SAILCLOTH
			    NPChar.Tuning.Matherial2 = SpeedRateMatherial2; //  GOOD_SILK
			    NPChar.Tuning.Matherial3 = SpeedRateMatherial3;
			    NPChar.Tuning.ShipType       = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName       = RealShips[sti(Pchar.Ship.Type)].BaseName;
			    DeleteAttribute(NPChar, "Discount");

				NextDiag.TempNode = "ship_tunning_SpeedRate_again";
                dialog.text = "Вот и славно. Жду материал и мои драгоценности.";
			    link.l1 = "Побежал"+ GetSexPhrase("","а") +" за ними...";
			    link.l1.go = "Exit";

			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "За свою работу по увеличению скорости корабля " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
				" мастер-корабел требует: шелка - " + NPChar.Tuning.Matherial1 + ", алмазов - "+ NPChar.Tuning.Matherial2+ ", сундуков с золотом - " + NPChar.Tuning.Matherial3 + ". В качестве задатка было уплачено " + NPChar.Tuning.Money + " золотых. Видимо, старик без ума от драгоценностей. Что ж - у каждого свои слабости...");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now";
                dialog.text = "Не вижу задатка...";
				link.l1 = "Я позже зайду.";
				link.l1.go = "Exit";
			}
		break;

		case "ship_tunning_SpeedRate_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName      == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_tunning_SpeedRate_again";
				dialog.Text = "Работа ждет. Принес"+ GetSexPhrase("","ла") +", что я просил?";
			    Link.l1 = "Да. Кое-что удалось достать.";
			    Link.l1.go = "ship_tunning_SpeedRate_again_2";
				Link.l2 = "Я хочу воспользоваться услугами верфи.";
				Link.l2.go = "PayToRapair1";
				link.l3 = "Нет. Еще добываю.";
				link.l3.go = "exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
			    dialog.Text = "Сдается мне, судар"+ GetSexPhrase("ь","ыня") +", что вы поменяли корабль со времени нашего уговора. Придеться все заново расчитывать...";
			    Link.l1 = "Было дело. Обидно, что задаток пропал...";
			    Link.l1.go = "Exit";

			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;

		case "ship_tunning_SpeedRate_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SILK, "jewelry2", "chest");

		    if(sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Matherial3) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
                dialog.text = "Все привез"+ GetSexPhrase("","ла") +". Молодец! Начинаю работу...";
			    link.l1 = "Жду.";
			    link.l1.go = "ship_tunning_SpeedRate_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_SpeedRate_again";
				dialog.Text = "Тебе осталось привезти: шелка - "+ sti(NPChar.Tuning.Matherial1) + ", алмазов - "+ sti(NPChar.Tuning.Matherial2) + ", сундуков - "+ sti(NPChar.Tuning.Matherial3) + ".";
				link.l1 = "Хорошо.";
				link.l1.go = "Exit";

                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText",  "Мне осталось довезти: шелка - "+ sti(NPChar.Tuning.Matherial1) + ", алмазов - "+ sti(NPChar.Tuning.Matherial2) + ", сундуков - "+ sti(NPChar.Tuning.Matherial3) + ".");
			}
		break;

		case "ship_tunning_SpeedRate_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_SpeedRate"))
			{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) + stf(shTo.SpeedRate)/5.0);
			}
			else
			{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) - stf(shTo.Bonus_SpeedRate)) * 1.2 + stf(shTo.Bonus_SpeedRate);
			}
	        shTo.Tuning.SpeedRate = true;
	        // finish <--
            NextDiag.TempNode = "ship_tunning_again";
			dialog.Text = "... Вроде бы все... Можешь ловить ветер полными парусами. Проверяй!";
			Link.l1 = "Спасибо! Проверю обязательно.";
			Link.l1.go = "Exit";

			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		////////////////////////////////////////// MastMultiplier ////////////////////////////////////////////////////
		case "ship_tunning_MastMultiplier":
			s1 = "Давайте посмотрим, что можно сделать. Сейчас прочность мачт вашего корабля " + MastMulti;

			s1 = s1 + ". Для укрепления мачт мне понадобится: досок - "+ MastMultiplierMatherial1 + ".";
			s1 = s1 + " Я стар, и не собираюсь вечно гнить в этой дыре, поэтому за работу возьму: сундуков с золотом - "+ MastMultiplierMatherial3 + ", хороших бронзовых крестов - "+ MastMultiplierMatherial2 + ", плюс - " + MastMultiplierMatherialWorkPrice + " пиастров на рабочие расходы. Вроде бы всё. Ах да - и деньги вперед.";

            dialog.Text = s1;
			Link.l1 = "Годится. Я принимаю условия. Всё оговоренное будет доставлено.";
			Link.l1.go = "ship_tunning_MastMultiplier_start";
			Link.l2 = "Нет. Меня это не устраивает.";
			Link.l2.go = "ship_tunning_not_now";
			if (!CheckAttribute(NPChar, "Discount"))
			{
			    Link.l3 = "А почему так дорого? Нельзя ли снизить расценки?";
				Link.l3.go = "Discount_1";
			}
			if (bBettaTestMode)
			{
				Link.l4 = "КАЧАЙ НЕМЕДЛЕННО!";
				Link.l4.go = "ship_tunning_MastMultiplier_complite";
			}

		break;

		case "ship_tunning_MastMultiplier_start":
		    amount = SpeedRateWorkPrice;
		    if(makeint(Pchar.money) >= amount)
			{
				AddMoneyToCharacter(Pchar, -amount);
			    NPChar.Tuning.Money  = amount;
			    NPChar.Tuning.Matherial1 = MastMultiplierMatherial1; // GOOD_SAILCLOTH
			    NPChar.Tuning.Matherial2 = MastMultiplierMatherial2; //  GOOD_SILK
			    NPChar.Tuning.Matherial3 = MastMultiplierMatherial3;
			    NPChar.Tuning.ShipType       = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName       = RealShips[sti(Pchar.Ship.Type)].BaseName;
			    DeleteAttribute(NPChar, "Discount");

				NextDiag.TempNode = "ship_tunning_MastMultiplier_again";
                dialog.text = "Вот и славно. Жду материал и мои драгоценности.";
			    link.l1 = "Побежал"+ GetSexPhrase("","а") +" за ними...";
			    link.l1.go = "Exit";

			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "За свою работу по укреплению мачт корабля " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
				" мастер-корабел требует: досок - " + NPChar.Tuning.Matherial1 + ", крестиков - "+ NPChar.Tuning.Matherial2+ ", сундуков с золотом - " + NPChar.Tuning.Matherial3 + ". В качестве задатка было уплачено " + NPChar.Tuning.Money + " золотых. Видимо, старик без ума от драгоценностей. Что ж - у каждого свои слабости...");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now";
                dialog.text = "Не вижу задатка...";
				link.l1 = "Я позже зайду.";
				link.l1.go = "Exit";
			}
		break;

		case "ship_tunning_MastMultiplier_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName      == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_tunning_MastMultiplier_again";
				dialog.Text = "Работа ждет. Принес"+ GetSexPhrase("","ла") +", что я просил?";
			    Link.l1 = "Да. Кое-что удалось достать.";
			    Link.l1.go = "ship_tunning_MastMultiplier_again_2";
				Link.l2 = "Я хочу воспользоваться услугами верфи.";
				Link.l2.go = "PayToRapair1";
				link.l3 = "Нет. Еще добываю.";
				link.l3.go = "exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
			    dialog.Text = "Сдается мне, судар"+ GetSexPhrase("ь","ыня") +", что вы поменяли корабль со времени нашего уговора. Придеться все заново расчитывать...";
			    Link.l1 = "Было дело. Обидно, что задаток пропал...";
			    Link.l1.go = "Exit";

			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;

		case "ship_tunning_MastMultiplier_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_PLANKS, "jewelry9", "chest");

		    if(sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Matherial3) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
                dialog.text = "Все привез"+ GetSexPhrase("","ла") +". Молодец! Начинаю работу...";
			    link.l1 = "Жду.";
			    link.l1.go = "ship_tunning_MastMultiplier_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_MastMultiplier_again";
				dialog.Text = "Тебе осталось привезти: досок - "+ sti(NPChar.Tuning.Matherial1) + ", крестиков - "+ sti(NPChar.Tuning.Matherial2) + ", сундуков - "+ sti(NPChar.Tuning.Matherial3) + ".";
				link.l1 = "Хорошо.";
				link.l1.go = "Exit";

                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText",  "Мне осталось довезти: досок - "+ sti(NPChar.Tuning.Matherial1) + ", крестиков - "+ sti(NPChar.Tuning.Matherial2) + ", сундуков - "+ sti(NPChar.Tuning.Matherial3) + ".");
			}
		break;

		case "ship_tunning_MastMultiplier_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			shTo.MastMultiplier        = stf(shTo.MastMultiplier) - 0.3;

	        shTo.Tuning.MastMultiplier = true;
	        // finish <--
            NextDiag.TempNode = "ship_tunning_again";
			dialog.Text = "... Вроде бы все... Можешь ловить своими мачтами книппели безо всяких опасений. Проверяй!";
			Link.l1 = "Спасибо! Проверю обязательно.";
			Link.l1.go = "Exit";

			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		////////////////////////////////////////// MaxCrew ////////////////////////////////////////////////////
		case "ship_tunning_MaxCrew":
			s1 = "Давайте посмотрим, что можно сделать. Сейчас максимальный экипаж вашего судна с учетом перегруза  " + shipMaxCrew + " человек.";

			s1 = s1 + " Для дополнительных гамаков и обивки рундуков мне понадобится: кожи - "+ MaxCrewMatherial1 + ".";
			s1 = s1 + " В оплату возьму: сапфиров - "+ MaxCrewMatherial2 + ", сундуков с золотом - "+ MaxCrewMatherial3 + ", плюс " + MaxCrewWorkPrice + " пиастров на рабочие расходы. Пожалуй, всё. Ах да - и деньги вперед.";
            dialog.Text = s1;
			Link.l1 = "Годится. Я принимаю условия. Всё оговоренное будет доставлено.";
			Link.l1.go = "ship_tunning_MaxCrew_start";
			Link.l2 = "Нет. Меня это не устраивает.";
			Link.l2.go = "ship_tunning_not_now";
			if (!CheckAttribute(NPChar, "Discount"))
			{
			    Link.l3 = "А почему так дорого? Нельзя ли снизить расценки?";
				Link.l3.go = "Discount_1";
			}
			if (bBettaTestMode)
			{
				Link.l4 = "КАЧАЙ НЕМЕДЛЕННО!";
				Link.l4.go = "ship_tunning_MaxCrew_complite";
			}
		break;

		case "ship_tunning_MaxCrew_start":
		    amount = MaxCrewWorkPrice;
		    if(makeint(Pchar.money) >= amount)
			{
				AddMoneyToCharacter(Pchar, -amount);
			    NPChar.Tuning.Money  = amount;
			    NPChar.Tuning.Matherial1 = MaxCrewMatherial1; // GOOD_FRUITS
			    NPChar.Tuning.Matherial2 = MaxCrewMatherial2; //  GOOD_CLOTHES
			    NPChar.Tuning.Matherial3 = MaxCrewMatherial3;
			    NPChar.Tuning.ShipType       = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName       = RealShips[sti(Pchar.Ship.Type)].BaseName;
			    DeleteAttribute(NPChar, "Discount");

				NextDiag.TempNode = "ship_tunning_MaxCrew_again";
                dialog.text = "Вот и славно. Жду материал и мои драгоценности.";
			    link.l1 = "Побежал"+ GetSexPhrase("","а") +" за ними...";
			    link.l1.go = "Exit";

			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText",  "За свою работу по увеличению экипажа на корабле " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
				" мастер-корабел требует: кожи - " + NPChar.Tuning.Matherial1 + ", сапфиров - "+ NPChar.Tuning.Matherial2+ ", сундуков с золотом - " + NPChar.Tuning.Matherial3 + ". В качестве задатка было уплачено " + NPChar.Tuning.Money + " золотых. Видимо, старик без ума от драгоценностей. Что ж - у каждого свои слабости...");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now";
                dialog.text = "Не вижу задатка...";
				link.l1 = "Я позже зайду.";
				link.l1.go = "Exit";
			}
		break;

		case "ship_tunning_MaxCrew_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName      == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_tunning_MaxCrew_again";
				dialog.Text = "Дело ждёт. Принес"+ GetSexPhrase("","ла") +", что я просил?";
			    Link.l1 = "Да. Кое-что удалось достать.";
			    Link.l1.go = "ship_tunning_MaxCrew_again_2";
				Link.l2 = "Я хочу воспользоваться услугами верфи.";
				Link.l2.go = "PayToRapair1";
				link.l3 = "Нет. Еще добываю.";
				link.l3.go = "exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
			    dialog.Text = "Сдается мне, судар"+ GetSexPhrase("ь","ыня") +", что вы поменяли корабль со времени нашего уговора. Придеться все заново расчитывать...";
			    Link.l1 = "Было дело. Обидно, что задаток пропал...";
			    Link.l1.go = "Exit";

			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;

		case "ship_tunning_MaxCrew_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_LEATHER, "jewelry1", "chest");

		    if(sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Matherial3) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
                dialog.text = "Все привез"+ GetSexPhrase("","ла") +". Молодец! Начинаю работу...";
			    link.l1 = "Жду.";
			    link.l1.go = "ship_tunning_MaxCrew_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_MaxCrew_again";
				dialog.Text = "Тебе осталось привезти: кожи - "+ sti(NPChar.Tuning.Matherial1) + ", сапфиров - "+ sti(NPChar.Tuning.Matherial2) + ", сундуков - "+ sti(NPChar.Tuning.Matherial3) + ".";
				link.l1 = "Хорошо.";
				link.l1.go = "Exit";

                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "Мне осталось довезти: кожи - "+ sti(NPChar.Tuning.Matherial1) + ", сапфиров - "+ sti(NPChar.Tuning.Matherial2) + ", сундуков  - "+ sti(NPChar.Tuning.Matherial3) + ".");
			}
		break;

		case "ship_tunning_MaxCrew_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
	        shTo.MaxCrew        = sti(shTo.MaxCrew) + makeint(sti(shTo.MaxCrew)/5);
	        shTo.Tuning.MaxCrew = true;
	        // finish <--
            NextDiag.TempNode = "ship_tunning_again";
			dialog.Text = "... Вроде бы все... Набирай матросов, всем места хватит.";
			Link.l1 = "Спасибо! Проверю обязательно.";
			Link.l1.go = "Exit";

			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;

		////////////////////////////////////////// TurnRate ////////////////////////////////////////////////////
		case "ship_tunning_TurnRate":
			s1 = "Давайте посмотрим, что можно сделать. Сейчас маневренность этого корабля - " + shipTurnRate;

			s1 = s1 + " Для дополнительных парусов, чтоб его расшевелить, мне понадобится: полотна - "+ TurnRateMatherial1 + ".";
			s1 = s1 + " И за работу я возьму: сундуков с золотом - "+ TurnRateMatherial3 + ", рубинов - "+ TurnRateMatherial2 + ", плюс - " + TurnRateWorkPrice + " пиастров на рабочие расходы. Вы же понимаете, что я не планирую умирать на этой помойке... Вот, пожалуй, всё. Ах да - деньги вперед.";
            dialog.Text = s1;
			Link.l1 = "Годится. Я принимаю условия. Всё оговоренное будет доставлено.";
			Link.l1.go = "ship_tunning_TurnRate_start";
			Link.l2 = "Нет. Меня это не устраивает.";
			Link.l2.go = "ship_tunning_not_now";
			if (!CheckAttribute(NPChar, "Discount"))
			{
			    Link.l3 = "А почему так дорого? Нельзя ли снизить расценки?";
				Link.l3.go = "Discount_1";
			}
			if (bBettaTestMode)
			{
				Link.l4 = "КАЧАЙ НЕМЕДЛЕННО!";
				Link.l4.go = "ship_tunning_TurnRate_complite";
			}

		break;

		case "ship_tunning_TurnRate_start":
		    amount = TurnRateWorkPrice;
		    if(makeint(Pchar.money) >= amount)
			{
				AddMoneyToCharacter(Pchar, -amount);
			    NPChar.Tuning.Money  = amount;
			    NPChar.Tuning.Matherial1 = TurnRateMatherial1; // GOOD_PLANKS
			    NPChar.Tuning.Matherial2 = TurnRateMatherial2; //  GOOD_LINEN
				NPChar.Tuning.Matherial3 = TurnRateMatherial3;
			    NPChar.Tuning.ShipType       = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName       = RealShips[sti(Pchar.Ship.Type)].BaseName;
			    DeleteAttribute(NPChar, "Discount");

				NextDiag.TempNode = "ship_tunning_TurnRate_again";
                dialog.text = "Вот и славно. Жду материал и мои драгоценности.";
			    link.l1 = "Побежал"+ GetSexPhrase("","а") +" за ними...";
			    link.l1.go = "Exit";

			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText",  "За свою работу по увеличению маневренности на корабле " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
				" мастер-корабел требует: полотна - " + NPChar.Tuning.Matherial1 + ", рубинов - "+ NPChar.Tuning.Matherial2+ ", сундуков с золотом - " + NPChar.Tuning.Matherial3 + ". В качестве задатка было уплачено " + NPChar.Tuning.Money + " золотых. Видимо, старик без ума от драгоценностей. Что ж - у каждого свои слабости...");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now";
                dialog.text = "Не вижу задатка...";
				link.l1 = "Я позже зайду.";
				link.l1.go = "Exit";
			}
		break;

		case "ship_tunning_TurnRate_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName      == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_tunning_TurnRate_again";
				dialog.Text = "Работа ждёт. Принес"+ GetSexPhrase("","ла") +", что я просил?";
			    Link.l1 = "Да. Кое-что удалось доставить.";
			    Link.l1.go = "ship_tunning_TurnRate_again_2";
				Link.l2 = "Я хочу воспользоваться услугами верфи.";
				Link.l2.go = "PayToRapair1";
				link.l3 = "Нет. Еще добываю.";
				link.l3.go = "exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
			    dialog.Text = "Сдается мне, судар"+ GetSexPhrase("ь","ыня") +", что вы поменяли корабль со времени нашего уговора. Придеться все заново расчитывать...";
			    Link.l1 = "Было дело. Обидно, что задаток пропал...";
			    Link.l1.go = "Exit";

			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;

		case "ship_tunning_TurnRate_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_LINEN, "jewelry3", "chest");

		    if(sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Matherial3) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
                dialog.text = "Все привез"+ GetSexPhrase("","ла") +". Молодец! Начинаю работу...";
			    link.l1 = "Жду.";
			    link.l1.go = "ship_tunning_TurnRate_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_TurnRate_again";
				dialog.Text = "Тебе осталось привезти: полотна - "+ sti(NPChar.Tuning.Matherial1) + ", рубинов - "+ sti(NPChar.Tuning.Matherial2) + ", сундуков - "+ sti(NPChar.Tuning.Matherial3) + ".";
				link.l1 = "Хорошо.";
				link.l1.go = "Exit";

                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "Мне осталось довезти: полотна - "+ sti(NPChar.Tuning.Matherial1) + ", рубинов - "+ sti(NPChar.Tuning.Matherial2) + ", сундуков - "+ sti(NPChar.Tuning.Matherial3) + ".");
			}
		break;

		case "ship_tunning_TurnRate_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_TurnRate"))
			{
				shTo.TurnRate        = (stf(shTo.TurnRate) + stf(shTo.TurnRate)/5.0);
			}
			else
			{
				shTo.TurnRate        = (stf(shTo.TurnRate) - stf(shTo.Bonus_TurnRate)) * 1.2 + stf(shTo.Bonus_TurnRate);
			}
	        shTo.Tuning.TurnRate = true;
	        // finish <--
            NextDiag.TempNode = "ship_tunning_again";
			dialog.Text = "... Вроде бы все... Можешь крутить штурвал.";
			Link.l1 = "Спасибо! Проверю обязательно.";
			Link.l1.go = "Exit";

			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		////////////////////////////////////////// HP ////////////////////////////////////////////////////
		case "ship_tunning_HP":
			s1 = "Давайте посмотрим, что можно сделать. Корпус судна сейчас " + shipHP;

			s1 = s1 + ". Чтобы укрепить обшивку, мне понадобится: красного дерева - "+ HPMatherial1 + ".";
			s1 = s1 + " За работу возьму: серебряных слитков - "+ HPMatherial2 + ", сундуков с золотом - "+ HPMatherial3 + ", плюс - " + HPWorkPrice + " пиастров на рабочие расходы... Внуки давно зовут меня назад в Европу, не хочется, знаете ли, возвращаться с пустыми руками... Вот, пожалуй и всё. Ах да - деньги вперед.";
            dialog.Text = s1;
			Link.l1 = "Годится. Я принимаю условия. Всё оговоренное будет доставлено.";
			Link.l1.go = "ship_tunning_HP_start";
			Link.l2 = "Нет. Меня это не устраивает.";
			Link.l2.go = "ship_tunning_not_now";
			if (!CheckAttribute(NPChar, "Discount"))
			{
			    Link.l3 = "А почему так дорого? Нельзя ли снизить расценки?";
				Link.l3.go = "Discount_1";
			}
			if (bBettaTestMode)
			{
				Link.l4 = "КАЧАЙ НЕМЕДЛЕННО!";
				Link.l4.go = "ship_tunning_HP_complite";
			}

		break;

		case "ship_tunning_HP_start":
		    amount = HPWorkPrice;
		    if(makeint(Pchar.money) >= amount)
			{
				AddMoneyToCharacter(Pchar, -amount);
			    NPChar.Tuning.Money  = amount;
			    NPChar.Tuning.Matherial1 = HPMatherial1; // GOOD_EBONY
			    NPChar.Tuning.Matherial2 = HPMatherial2; //  GOOD_SANDAL
				NPChar.Tuning.Matherial3 = HPMatherial3;
			    NPChar.Tuning.ShipType       = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName       = RealShips[sti(Pchar.Ship.Type)].BaseName;
			    DeleteAttribute(NPChar, "Discount");

				NextDiag.TempNode = "ship_tunning_HP_again";
                dialog.text = "Вот и славно. Жду материал и мои драгоценности.";
			    link.l1 = "Побежал"+ GetSexPhrase("","а") +" за ними...";
			    link.l1.go = "Exit";

			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText",  "За свою работу по увеличению прочности корпуса корабля " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
				" мастер-корабел требует: красного дерева - " + NPChar.Tuning.Matherial1 + ", серебряных слитков - "+ NPChar.Tuning.Matherial2+ ", сундуков с золотом - " + NPChar.Tuning.Matherial3 + ". В качестве задатка было уплачено " + NPChar.Tuning.Money + " золотых... Говорит, что в Европу собрался - врёт, наверное, старый черт.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now";
                dialog.text = "Не вижу задатка...";
				link.l1 = "Я позже зайду.";
				link.l1.go = "Exit";
			}
		break;

		case "ship_tunning_HP_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName      == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_tunning_HP_again";
				dialog.Text = "Работа ждет. Принес"+ GetSexPhrase("","ла") +", что я просил?";
			    Link.l1 = "Да. Кое-что удалось достать.";
			    Link.l1.go = "ship_tunning_HP_again_2";
				Link.l2 = "Я хочу воспользоваться услугами верфи.";
				Link.l2.go = "PayToRapair1";
				link.l3 = "Нет. Еще добываю.";
				link.l3.go = "exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
			    dialog.Text = "Сдается мне, судар"+ GetSexPhrase("ь","ыня") +", что вы поменяли корабль со времени нашего уговора. Придеться все заново расчитывать...";
			    Link.l1 = "Было дело. Обидно, что задаток пропал...";
			    Link.l1.go = "Exit";

			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;

		case "ship_tunning_HP_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_MAHOGANY, "jewelry17", "chest");

		    if(sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Matherial3) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
                dialog.text = "Все привез"+ GetSexPhrase("","ла") +". Молодец! Начинаю работу...";
			    link.l1 = "Жду.";
			    link.l1.go = "ship_tunning_HP_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_HP_again";
				dialog.Text = "Тебе осталось привезти: красного дерева - "+ sti(NPChar.Tuning.Matherial1) + ", серебряных слитков - "+ sti(NPChar.Tuning.Matherial2) + ", сундуков - "+ sti(NPChar.Tuning.Matherial3) + ".";
				link.l1 = "Хорошо.";
				link.l1.go = "Exit";

                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "Мне осталось довезти: красного дерева - "+ sti(NPChar.Tuning.Matherial1) + ", серебряных слитков - "+ sti(NPChar.Tuning.Matherial2) + ", сундуков - "+ sti(NPChar.Tuning.Matherial3) + ".");
			}
		break;

		case "ship_tunning_HP_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_HP"))
			{
				shTo.HP        = sti(shTo.HP) + makeint(sti(shTo.HP)/5);
			}
			else
			{
				shTo.HP        = makeint((sti(shTo.HP) - sti(shTo.Bonus_HP)) * 1.2 + sti(shTo.Bonus_HP));
			}
	        shTo.Tuning.HP = true;
	        // finish <--
            NextDiag.TempNode = "ship_tunning_again";
			if(shTo.BaseName == "Flyingdutchman") // ЛГ
			{
				dialog.text = "Да уж... сколько кораблей я повидал на своём веку, но такой грязи и затхлости в капитанской каюте не видывал еще никогда. Ты бы почаще там убирал"+ GetSexPhrase("ся","ась") +" что ли! Впрочем, мы перестроили каюту и укрепили корпус - пару прямых попаданий выдержит точно.";
				Link.l1 = "Спасибо! Проверю обязательно.";
				Link.l1.go = "Exit";
				shTo.CabinType = "Cabin_Quest";
			}
			else
			{
				dialog.Text = "... Вроде бы все... Гарантирую, что развалить этот кораблик теперь будет очень непросто!";
				Link.l1 = "Спасибо! Но с этим лучше не экспериментировать.";
				Link.l1.go = "Exit";
			}

			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		////////////////////////////////////////// WindAgainst ////////////////////////////////////////////////////
		case "ship_tunning_WindAgainst":
			s1 = "Давайте посмотрим, что можно сделать. Бейдевинд сейчас " + FloatToString(shipWindAgainst, 2);

			s1 = s1 + ". Чтобы разогнать его против ветра мне понадобится: хлопка - "+ WindAgainstMatherial1 + ",";
			s1 = s1 + " а в качестве оплаты возьму: изумрудов - "+ WindAgainstMatherial2 + ", сундуков с золотом - "+ WindAgainstMatherial3 + ", плюс - " + WindAgainstWorkPrice + " пиастров на рабочие расходы. Дело-то непростое... Вроде бы всё. Ах да - деньги вперед.";
            dialog.Text = s1;
			Link.l1 = "Годится. Я принимаю условия. Всё оговоренное будет доставлено.";
			Link.l1.go = "ship_tunning_WindAgainst_start";
			Link.l2 = "Нет. Меня это не устраивает.";
			Link.l2.go = "ship_tunning_not_now";
			if (!CheckAttribute(NPChar, "Discount"))
			{
			    Link.l3 = "А почему так дорого? Нельзя ли снизить расценки?";
				Link.l3.go = "Discount_1";
			}
			if (bBettaTestMode)
			{
				Link.l4 = "КАЧАЙ НЕМЕДЛЕННО!";
				Link.l4.go = "ship_tunning_WindAgainst_complite";
			}
		break;

		case "ship_tunning_WindAgainst_start":
		    amount = WindAgainstWorkPrice;
		    if(makeint(Pchar.money) >= amount)
			{
				AddMoneyToCharacter(Pchar, -amount);
			    NPChar.Tuning.Money  = amount;
			    NPChar.Tuning.Matherial1     = WindAgainstMatherial1;
			    NPChar.Tuning.Matherial2     = WindAgainstMatherial2;
			    NPChar.Tuning.Matherial3     = WindAgainstMatherial3;
			    NPChar.Tuning.ShipType       = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName       = RealShips[sti(Pchar.Ship.Type)].BaseName;
                DeleteAttribute(NPChar, "Discount");
				NextDiag.TempNode = "ship_tunning_WindAgainst_again";
                dialog.text = "Вот и славно. Жду материал и мои драгоценности.";
			    link.l1 = "Побежал"+ GetSexPhrase("","а") +" за ними...";
			    link.l1.go = "Exit";

			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText",  "За свою работу по увеличению хода в бейдевинд на корабле " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
				" мастер-корабел требует: хлопка - " + NPChar.Tuning.Matherial1 + ", изумрудов - "+ NPChar.Tuning.Matherial2+ ", сундуков с золотом - " + NPChar.Tuning.Matherial3 + ". В качестве задатка было уплачено " + NPChar.Tuning.Money + " золотых. Совсем старик с ума сбрендил от этих побрякушек.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now";
                dialog.text = "Не вижу задатка...";
				link.l1 = "Я позже зайду.";
				link.l1.go = "Exit";
			}
		break;

		case "ship_tunning_WindAgainst_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName      == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_tunning_WindAgainst_again";
			    dialog.Text = "Бейдевинд ждет. Принес"+ GetSexPhrase("","ла") +", что я просил?";
			    Link.l1 = "Да. Кое-что удалось доставить.";
			    Link.l1.go = "ship_tunning_WindAgainst_again_2";
				Link.l2 = "Я хочу воспользоваться услугами верфи.";
				Link.l2.go = "PayToRapair1";
				link.l3 = "Нет. Еще добываю.";
				link.l3.go = "exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
			    dialog.Text = "Сдается мне, судар"+ GetSexPhrase("ь","ыня") +", что вы поменяли корабль со времени нашего уговора. Придеться все заново расчитывать...";
			    Link.l1 = "Было дело. Обидно, что задаток пропал...";
			    Link.l1.go = "Exit";

			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;

		case "ship_tunning_WindAgainst_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_COTTON, "jewelry4", "chest");

		    if(sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Matherial3) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "ship_tunning_again";
                dialog.text = "Все привез"+ GetSexPhrase("","ла") +". Молодец! Начинаю работу...";
			    link.l1 = "Жду.";
			    link.l1.go = "ship_tunning_WindAgainst_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_WindAgainst_again";
                dialog.Text = "Тебе осталось привезти: хлопка - "+ sti(NPChar.Tuning.Matherial1) + ", изумрудов - "+ sti(NPChar.Tuning.Matherial2) + ", сундуков - "+ sti(NPChar.Tuning.Matherial3) + ".";
				link.l1 = "Хорошо.";
				link.l1.go = "Exit";

                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "Мне осталось довезти: хлопка - "+ sti(NPChar.Tuning.Matherial1) + ", изумрудов - "+ sti(NPChar.Tuning.Matherial2) + ", сундуков - "+ sti(NPChar.Tuning.Matherial3) + ".");
			}
		break;

		case "ship_tunning_WindAgainst_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
	        shTo.WindAgainstSpeed   = FloatToString(stf(shTo.WindAgainstSpeed) + 0.5* stf(shTo.WindAgainstSpeed) / stf(shTo.Class) + 0.005, 2);
	        shTo.Tuning.WindAgainst = true;
	        // finish <--
            NextDiag.TempNode = "ship_tunning_again";
			dialog.Text = "... Вроде бы все... Скорость против ветра теперь поболе будет.";
			Link.l1 = "Спасибо! Проверю обязательно.";
			Link.l1.go = "Exit";

			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
		break;
		///////////////////////////////  квестовые ветки
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно?"), "Совсем недавно вы пытались задать мне вопрос...", "У себя на верфи, да и вообще в городе, я таких однообразно любознательных не видел.",
                          "Ну что за вопросы? Мое дело - корабли строить, давайте этим и займемся.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал"+ GetSexPhrase("","а") +"...", "Сейчас мне не о чем говорить"), "Хм, что-то с памятью моей стало...",
                      "Хм, однако...", "Давайте...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (!CheckAttribute(npchar, "Step_Door"))
			{
				link.l2 = "Послушай, я хочу пройти, а дверь закрыта...";
				link.l2.go = "Step_Door_1";
			}
        // ==> Перехват на квесты
            if (CheckAttribute(pchar, "questTemp.State.SeekBible"))// квест №2, поиск Евангелие
            {
                if (!CheckCharacterItem(pchar, "Bible"))
                {
                    dialog.text = "Говорите...";
        			link.l2 = "Послушайте, я хочу узнать, куда на вашей верфи провалился некий человек, спасающийся от преследования?";
        			link.l2.go = "Step_S2_1";
                }
                else
                {
                    dialog.text = "О-о-о, рад видеть тебя. Значит, не зря я тебя туда впустил - сам"+ GetSexPhrase("","а") +" выжил"+ GetSexPhrase("","а") +" и меня от это дряни избавил"+ GetSexPhrase("","а") +"... Ну скажи, кто там был?";
        			link.l2 = "Лучше тебе этого не знать, спать будешь спокойней. Ну, прощай, еще раз спасибо, что открыл дверь.";
        			link.l2.go = "exit";
                }
            }
			if (pchar.questTemp.piratesLine == "KillLoy_toAlexus")
			{
				link.l1 = "К вам Эдвард Лоу заходил?";
				link.l1.go = "PL_Q3_1";
			}
			if (CheckAttribute(pchar, "questTemp.piratesLine.T1"))
            {
				if (pchar.questTemp.piratesLine.T1 == "KillLoy_GoodWork")
				{
					link.l1 = "Джекмен подарил мне 'Морского Волка'!";
					link.l1.go = "PL_Q3_SW1";
				}
				if (pchar.questTemp.piratesLine.T1 == "KillLoy_LoyIsDied")
				{
					link.l1 = "У меня не очень хорошие новости относительно твоего брига, который Лоу увел...";
					link.l1.go = "PL_Q3_SW2";
				}
			}
			if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAlexus"))
			{
				link.l1 = "Хочу предложить сделку.";
				link.l1.go = "Al_ShipLetters_1";// генератор  "Найденные документы"
				pchar.questTemp.different.GiveShipLetters.speakAlexus = true;
			}
			if (pchar.questTemp.BlueBird == "toSeekBermudes") //шебека Синяя Птица
			{
				link.l1 = "Послушайте, мне нужно знать одну вещь касательно вашего подземелья...";
				link.l1.go = "BlueBird_1";
			}
			if (CheckCharacterItem(pchar, "Ship_Print_1")) NPChar.print1 = 0;
			if (CheckCharacterItem(pchar, "Ship_Print_2")) NPChar.print2 = 0;
			if (CheckCharacterItem(pchar, "Ship_Print_3")) NPChar.print3 = 0;
			if (CheckCharacterItem(pchar, "Ship_Print_4")) NPChar.print4 = 0;
			if (CheckCharacterItem(pchar, "Ship_Print_5")) NPChar.print5 = 0;
			if (CheckCharacterItem(pchar, "Ship_Print_6")) NPChar.print6 = 0;
			if (CheckCharacterItem(pchar, "Ship_Print_1") || CheckCharacterItem(pchar, "Ship_Print_2") || CheckCharacterItem(pchar, "Ship_Print_3") || CheckCharacterItem(pchar, "Ship_Print_4") || CheckCharacterItem(pchar, "Ship_Print_5") || CheckCharacterItem(pchar, "Ship_Print_6"))
            {
				if (!CheckAttribute(npchar, "questTemp.ShipOrderTime"))
				{
					link.l3 = "Я тут добыл что-то необычное и оно весьма похоже на чертёж, не взглянёте?";
					link.l3.go = "blueprint";
				}

			}
        // <== Перехват на квесты
		break;

		case "blueprint":
			dialog.text = "Хм... Вы принесли мне довольно занятную вещь. Нет, это не чертёж в привычном понимании вещей. Это комплекс конструктивных решений в кораблестроительстве, причём очень необычный. С его помощью можно добиться максимума возможностей какого угодно корабля. Если хотите, я за вознаграждение могу попробовать создать какой-нибудь корабль. Ну так как?"
			link.l1 = "Само собой, давайте приступим.";
			link.l1.go = "blueprint_ordership";
			link.l2 = "Это конечно очень интересно, но пожалуй в другой раз.";
			link.l2.go = "exit";
		break;

		case "blueprint_ordership":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchShipyard2(npchar);
		break;
//*************************** Генератор - "Найденные судовые документы" **************

		case "Al_ShipLetters_1":
			dialog.text = "Излагайте условия.";
			s1 = "У меня, по счастливой случайности, оказался абсолютно легальный пакет судовых документов, еще не заявленных в розыск.";
			s1 = s1 + "Судно на плаву и не исключено из реестра, не беспокойтесь. Просто разиня-владелец умудрился потерять эти бумаги...";
			link.l1 = s1;
			link.l1.go = "Al_ShipLetters_2";
		break;
		case "Al_ShipLetters_2":
			s1 = "Дайте-ка взглянуть! Действительно, отметки совсем свежие. Что же, удача Вам благоволит, судар"+ GetSexPhrase("ь","ыня") +"! ";
			s1 = s1 + "Мне как раз понадобился именно такой комплект, и я, в свою очередь предлагаю Вам " + sti(pchar.questTemp.different.GiveShipLetters.price5) + " золотом. Что скажете?";
			dialog.text = s1;
			link.l1 = "Воистину королевская щедрость! Конечно же я соглас"+ GetSexPhrase("ен","на") +"!";
			link.l1.go = "Al_ShipLetters_3";
			link.l2 = "Пожалуй, нет.";
			link.l2.go = "exit";
		break;
		case "Al_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook");
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price5));
			ChangeCharacterReputation(pchar, -1);
			OfficersReaction("bad");
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер
			AddQuestRecord("GiveShipLetters", "9");
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

//*************************** Пиратка, квест №3, поиски Лоу ***************************
		case "PL_Q3_1":
			dialog.text = "Заходил... А вам он зачем нужен?";
			link.l1 = "М-м, они с Морганом не сошлись во мнениях по некоторым вопросам этики. Не испытывайте мое терпение, мастер, я от самой Мартиники за ним гоняюсь.";
			link.l1.go = "PL_Q3_3";
			link.l2 = "Я его друг, давно не виделись, а тут в таверне сказали, что он заходил сюда...";
			link.l2.go = "PL_Q3_2";
		break;
		case "PL_Q3_2":
			dialog.text = "Ага. Друг, значит. Это хорошо... Это просто замечательно! Ты, вот что, иди к Джекмену, скажи, что ищешь своего друга Эдварда Лоу. Джекмен тебе поможет\nМожет даже, твой друг еще у него. Иди, иди, там и встретитесь, соскучил"+ GetSexPhrase("ся","ась") +", поди.";
			link.l1 = "Спасибо! Уже бегу!";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "10");
			pchar.questTemp.piratesLine = "KillLoy_toJackman";
		break;
		case "PL_Q3_3":
			dialog.text = "Так вы его разыскиваете по заданию Моргана? Ну, хоть кто-то занялся этим мерзавцем! Представляете? он меня обманул! Принес письмо от Джекмена, с просьбой отдать 'Морского Волка' подателю сего письма...";
			link.l1 = "'Морского Волка'?";
			link.l1.go = "PL_Q3_4";
		break;
		case "PL_Q3_4":
			dialog.text = "'Морской Волк' это бриг. Мой бриг! Самое лучшее мое творение! Всю душу в него вложил. Он прекрасен, великолепен и пленителен! Когда солнце на закате просвечивает сквозь его паруса, от него невозможно оторвать взгляд. На восходе, когда красавец поднимает паруса, он подобен распускающемуся цветку магнолии! А как он скользит по волнам...";
			link.l1 = "Гхм, мастер, давай вернемся к нашему Лоу.";
			link.l1.go = "PL_Q3_5";
		break;
		case "PL_Q3_5":
			dialog.text = "Простите? А, да. Эдвард Лоу. Бриг-то я Джекмену делал, достроил почти, а тут он, Лоу, с письмом. В общем, отдал я бриг, а когда пошел за деньгами к Джекмену, оказалось, что письмо поддельное. Джекмен расстроился... Сильно... Очень сильно.\nКогда меня оттуда вы... Э-э-э...  Когда я оттуда уходил, Джекмен сказал: 'Я вас уважаю Мастер, но бриг надо вернуть'. Вот я тут и подумал, раз уж вы все равно этого Лоу ищете, может и мой бриг заодно найдете?";
			link.l1 = "Мастер, я вам, конечно, помогу, но только, если вы прекратите причитать и внятно мне скажете: ГДЕ ЛОУ?!";
			link.l1.go = "PL_Q3_6";
		break;
		case "PL_Q3_6":
			dialog.text = "Так спросите хозяина таверны. Тавернщики, они народ такой, все про всех знают. Наверняка знает, куда ушёл на моём бриге этот негодяй.";
			link.l1 = "Тьфу ты, столько времени убил"+ GetSexPhrase("","а") +" впустую. Ладно, бывайте, мастер.";
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "11");
			pchar.questTemp.piratesLine = "KillLoy_toTavernAgain";
			//садим капитана Гудли в таверну
			sld = GetCharacter(NPC_GenerateCharacter("CapGoodly", "officer_9", "man", "man", 20, PIRATE, -1, true));
			sld.name = "Капитан";
			sld.lastname = "Гудли";
			sld.rank = 20;
			sld.city = "Pirates";
			sld.dialog.filename   = "Quest\PiratesLine_dialog.c";
			sld.dialog.currentnode   = "CapGoodly";
			sld.greeting = "Gr_EvilPirate";
			LAi_SetSitType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
            FreeSitLocator("Pirates_tavern", "sit2");
         	ChangeCharacterAddressGroup(sld, "Pirates_tavern", "sit", "sit2");
		break;

		case "PL_Q3_SW1":
			dialog.text = "Видел, видел, твое прибытие. Не удержался, бегал на пристань поглядеть.\nДостойный подарок. Поздравляю и спасибо тебе! Спас"+ GetSexPhrase("","ла") +" старика.";
			link.l1 = "Так уж и спас"+ GetSexPhrase("","ла") +"...";
			link.l1.go = "exit";
		break;
		case "PL_Q3_SW2":
			dialog.text = "Черт! Я так и знал... И что?";
			link.l1 = "Он утонул, сожалею....";
			link.l1.go = "PL_Q3_SW3";
		break;
		case "PL_Q3_SW3":
			dialog.text = "Да уж, все плохо.";
			link.l1 = "Да не переживай ты, все утрясется...";
			link.l1.go = "exit";
		break;
//*************************** шебека Синяя Птица ***************************
		case "BlueBird_1":
			dialog.text = "Оно не мое. Наоборот, я пытаюсь туда никого не пускать ради их же блага.";
			link.l1 = "А-а, ну понятно. Вопрос собственно заключается вот в чем. Не проносят ли через это подземелье товары в город?";
			link.l1.go = "BlueBird_2";
		break;
		case "BlueBird_2":
			dialog.text = "Ха-ха, нет, конечно, хотя подземелье и сквозное. Посудите сами, это каким идиотом надо быть, чтобы на себе таскать грузы по этой норе, когда можно нанять любую тартану и спокойно привезти все по морю.";
			link.l1 = "Ну, а если кто-то не хочет, чтобы об этом узнали в городе?";
			link.l1.go = "BlueBird_3";
		break;
		case "BlueBird_3":
			dialog.text = "А вы думаете, что если кто-то начнет таскать грузы из моей верфи в город, этого никто не заметит?";
			link.l1 = "Хм, да, точно... Так значит, никто ничего не проносит через вашу верфь?";
			link.l1.go = "BlueBird_4";
		break;
		case "BlueBird_4":
			dialog.text = "Нет, никто ничего не проносит, можете быть уверенн"+ GetSexPhrase("ым","ой") +".";
			link.l1 = "Ну что же, огромное вам спасибо!";
			link.l1.go = "exit";
			AddQuestRecord("Xebeca_BlueBird", "5");
			pchar.questTemp.BlueBird = "toCavern";
			pchar.quest.BlueBird_inCavern.win_condition.l1 = "locator";
			pchar.quest.BlueBird_inCavern.win_condition.l1.location = "Bermudes_Cavern";
			pchar.quest.BlueBird_inCavern.win_condition.l1.locator_group = "quest";
			pchar.quest.BlueBird_inCavern.win_condition.l1.locator = "BlueBird";
			pchar.quest.BlueBird_inCavern.function = "BlueBird_inCavern";
			LAi_LocationDisableMonstersGen("Bermudes_Cavern", true); //монстров не генерить
			LAi_LocationDisableOfficersGen("Bermudes_Cavern", true); //офицеров не пускать
		break;
//*************************** Открывание двери ***************************
 		case "Step_Door_1":
			dialog.text = "Все верно. Чтобы здесь пройти, тебе надо заплатить мне 20000 монет. Не заплатишь - не открою, у меня здесь не проходной двор. Да и тебе там шляться не советую - не к добру...";
			if(sti(pchar.money) >= 20000)
			{
    			link.l1 = "Вот твои деньги, открывай.";
    			link.l1.go = "Step_Door_2";
            }
            else
            {
    			link.l1 = "Нет у меня таких денег.";
    			link.l1.go = "Step_Door_3";
            }
            link.l2 = "Вот еще! Платить за какую-то дверь.";
    		link.l2.go = "exit";
		break;
 		case "Step_Door_2":
			npchar.Step_Door = true; // fix
			dialog.text = "Проходи, дверь открыта. И не благодари!";
			link.l1 = "Да чего уж там, спасибо тебе, " + npchar.name + "...";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
            AddMoneyToCharacter(pchar, -20000);
			pchar.quest.CloseBermudesDungeonDoor.win_condition.l1 = "MapEnter";
            pchar.quest.CloseBermudesDungeonDoor.win_condition = "CloseBermudesDungeonDoor";
		break;
 		case "Step_Door_3":
			dialog.text = "Ну вот когда будут, тогда и приходи. А так и не уговаривай - бесполезно...";
			link.l1 = "Аргх, ну слов просто никаких нет!";
			link.l1.go = "exit";
		break;
//*************************** Квест №2, диалоги с Франциско на выходе из Инквизиии ***************************
 		case "Step_S2_1":
			dialog.text = NPCStringReactionRepeat("У-у-у, хороший вопрос... А зачем он вам нужен?", "Я уже все сказал - дверь открыта.", "Еще раз повоторяю - дверь открыта.", "Послушай, ну сколько можно, а?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("У него есть книга, которая ему не принадлежит. Он вор.", "Я понял"+ GetSexPhrase("","а") +"...", "Понятно...", "Вот так"+ GetSexPhrase("ой","ая") +" я непонятно настойчив"+ GetSexPhrase("ый","ая") +"...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_S2_2", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
 		case "Step_S2_2":
			dialog.text = "Понятно. Вы знаете, его преследователи, матросы, уже спрашивали меня об этом. Потом приходил какой-то торговец и тоже пытался разузнать. Я им ничего не сказал.";
			link.l1 = "Почему?";
			link.l1.go = "Step_S2_3";
		break;
 		case "Step_S2_3":
			dialog.text = "Не захотел греха на душу брать - не жить им, если бы они туда полезли... Тебе могу сказать, ты, вроде, "+ GetSexPhrase("не из боязливых, да и крепок...","девушка боевая, сабелькой махать умеешь.") +"";
			link.l1 = "Куда бы они полезли?";
			link.l1.go = "Step_S2_4";
		break;
 		case "Step_S2_4":
			dialog.text = "Туда, куда полез тот воришка. В эту дверь, что справа от меня.";
			link.l1 = "И там, за дверью? И почему ты никого туда не пускаешь?";
			link.l1.go = "Step_S2_5";
		break;
 		case "Step_S2_5":
			dialog.text = "За дверью подземелье, кто его построил - мне неведомо, когда я стал здесь хозяином, оно уже было. А не пускаю потому, что опасно там, очень опасно. Воришка тот, похоже, там и сгинул...\n"+
                          "Живет там не знаю кто, или что. Но порой такие оттуда вопли раздаются, что кровь в жилах стынет...";
			link.l1 = "Вот так даже... Хм, ну что же, запускай.";
			link.l1.go = "Step_S2_6";
		break;
 		case "Step_S2_6":
			dialog.text = "Проходи, открыто... Надесь, что увижу тебя еще на этом свете.";
			link.l1 = "Увидишь, не сомневайся.";
			link.l1.go = "exit";
            LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
            LocatorReloadEnterDisable("Shore3", "reload2_back", false);
            Pchar.quest.Inquisition_fightInDangeon.win_condition.l1 = "location";
            Pchar.quest.Inquisition_fightInDangeon.win_condition.l1.location = "Bermudes_Dungeon";
            Pchar.quest.Inquisition_fightInDangeon.win_condition = "Inquisition_fightInDangeon";
         	pchar.GenQuestBox.Terks_Grot = true;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.jewelry5 = 200;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.jewelry17 = 300;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.blade33 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.blade28 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.blade34 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.blade32 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.blade23 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.pistol5 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.pistol4 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.pistol6 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.potion2 = 5;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.indian18 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.jewelry7 = 5;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.blade5 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.potion2 = 10;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.potionwine = 3;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.jewelry1 = 100;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.jewelry2 = 80;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.jewelry3 = 60;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.jewelry4 = 45;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.icollection = 1;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.chest = 5;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.jewelry14= 10;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.indian6 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.indian11 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.indian15 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.indian12 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.indian18 = 1;
            pchar.GenQuestBox.Bermudes_Dungeon.box1.items.Bible = 1;
		break;
		case "PayToRapair1":
			if (pchar.paytorepair != pchar.dayRandom && CheckAttribute(PChar,"paytorepair")) DeleteAttribute(PChar,"paytorepair");
			dialog.text = "Уважаем" + GetSexPhrase("ый","ая") + ", я уже подготивил все для улучшения вашего корабля, вы хотите что бы я вот так все бросил?!";
			link.l1 = "Я вас поня" + GetSexPhrase("л","ла") + ". Надеюсь 15000 тысяч пиастров уладит этот вопрос?"
			link.l1.go = "PayToRapair2";
			link.l2 = "Ладно, ничего не нужно.";
			link.l2.go = "exit";
			if (CheckAttribute(PChar,"paytorepair"))
			{
				dialog.text = "Нужно лучше обращаться со своим кораблем! Вы мне уже надоели за сегодня... Ладно, что вам нужно?";
				link.l1 = "Мне нужно починить корабль."
				link.l1.go = "shipyard";
				link.l2 = "Мне нужны орудия на корабль.";
				link.l2.go = "Cannons";
			}

		break;
		case "PayToRapair2":
			pchar.paytorepair = pchar.dayRandom;
			AddMoneyToCharacter(pchar, -15000);
			dialog.text = "Вот, другое дело! Что вам нужно?";
			link.l1 = "Мне нужно починить корабль."
			link.l1.go = "shipyard";
			link.l2 = "Мне нужны орудия на корабль.";
			link.l2.go = "Cannons";
		break;

		//Капремонт пса
		case "WarDogUpgrade_1":
			dialog.text = "Да ну? Как будто вы понятия не имеете, что это лично я его спроектировал.";
			link.l1 = "Так это ваша разработка? Должна признаться, вы поработали на славу.";
			link.l1.go = "WarDogUpgrade_2";
		break;

		case "WarDogUpgrade_2":
			dialog.text = "Ой, не смешите меня. Я же знаю, что это развалюха. Когда я его делал, был молодым, зеленым, глупым. Если бы я начал проектировать его сейчас, не допустил бы старых ошибок.";
			link.l1 = "Неужели все настолько плохо? По мне так кораблик все еще отличный. Получше многих посудин, что я повстречала на Карибах.";
			link.l1.go = "WarDogUpgrade_3";
		break;

		case "WarDogUpgrade_3":
			dialog.text = "Он мог бы быть куда быстрее, маневреннее, крепче... ";
			link.l1 = "Правда? А не хотите его доработать? Провести работу над ошибками, так сказать.";
			link.l1.go = "WarDogUpgrade_4";
		break;

		case "WarDogUpgrade_4":
			dialog.text = "Вряд ли. У меня сейчас полно других неотложных дел, а 'Псу' нужен капитальный ремонт, на который уйдет немало времени и сил. К тому же, годы уже не те... В последнее время мне противит возвращаться к своим старым проектам. Хотя\nЕсли окажете мне одну услугу, мисс, так и быть, я подумаю об этом. ";
			link.l1 = "Чего вы хотите?";
			link.l1.go = "WarDogUpgrade_5";
		break;

		case "WarDogUpgrade_5":
			dialog.text = "Есть тут на архипелаге один корабел-зазнайка, не буду тыкать пальцем. Он возомнил себя лучшим во всем мире, даже лучше меня, и не стесняется хвастаться этим при каждой подходящей возможности\nЧего он не рассказывает людям, так это того, что все его 'гениальные идеи' - на самом деле мои старые чертежи, которые я по той или иной причине забросил. Видишь ли, он был моим учеником, пока однажды не украл мои революционные в сфере кораблестроения наброски и смылся к англичанам\nА недавно он заявил, будто создал непотопляемый корабль. 'Титаник' - так он его назвал. Какая безвкусица! Тьфу!";
			link.l1 = "'Титаник'... звучит знакомо. Где бы я могла это слышать?.. Впрочем, неважно, продолжай.";
			link.l1.go = "WarDogUpgrade_5_1";
		break;

		case "WarDogUpgrade_5_1":
			dialog.text = "Он продал его какому-то английскому каперу, а тот использует судно для набегов на испанские порты на материке. Говорят, этот капитан стал настолько самоуверен, что ему все равно на проплывающие мимо корабли, если они не сулят прибыли, хоть Весёлым Роджером перед ним размахивай. Но если нападёшь - будь уверена, сдачи он даст в десятикратном размере.\nЯ хочу, чтобы ты стерла самодовольную ухмылку с лица моего ученика и сломала его игрушку. Потопи 'непотопляемого', а я поработаю над чертежом 'Пса'.";
			link.l1 = "Я вот думаю, может лучше попробовать взять его на абордаж? Вдруг он и правда непотопляемый?";
			link.l1.go = "WarDogUpgrade_6";

		break;

		case "WarDogUpgrade_6":
			dialog.text = "Если мой ученик сделал корабль на совесть, потопить его и правда будет невозможно. Но я сомневаюсь, что этот бездарь был способен понять замысел, сокрытый в моих расчетах. К тому же, на момент кражи, этот чертеж был готов не полностью, так что уязвимые места у него точно должны быть\nА об абордаже и думать забудь! Мало того, что команды там хватит, чтобы заселить пару городов, к тому же ты лишь подтвердишь слух о его непотопляемости - мол, победить его можно только если вырезать веь экипаж. Просто пусти его на дно.";
			link.l1 = "Есть какие-нибудь советы, как это сделать?";
			link.l1.go = "WarDogUpgrade_6_2";
		break;

		case "WarDogUpgrade_6_2":
			dialog.text = "Даже не знаю... Если честно, я ломать корабли не умею, всю жизнь их только строил. Но можешь попробовать набить порохом пару-тройку бригов и использовать их как брандеры, если конечно сможешь убедить команду рискнуть своими жизнями.";
			link.l1 = "Какие-то уж слишком радикальные у тебя методы. А говоришь, что ломать не умеешь. Ладно, как-нибудь разберусь. Так где искать этот корабль?";
			link.l1.go = "WarDogUpgrade_6_1";
		break;

		case "WarDogUpgrade_6_1":
			sld = GetCharacter(NPC_GenerateCharacter("W_Titanic", "off_eng_1", "man", "man", 99, ENGLAND, -1, true));
			FantomMakeCoolestSailor(sld, SHIP_BATTLEMANOWAR, "Титаник", CANNON_TYPE_CANNON_LBS48, 100, 100, 100);
			ref W_Titanic = &RealShips[sti(sld.Ship.Type)];
			W_Titanic.HP = 30000;
			W_Titanic.MastMultiplier = 0.01;
			W_Titanic.TurnRate = 40;
			W_Titanic.MaxCrew = 3500;
			W_Titanic.MinCrew = 3000;
			W_Titanic.SpeedRate = 14;
			W_Titanic.WindAgainstSpeed = 4;
			//W_Titanic.HullArmor = 60;
			W_Titanic.Capacity = 100000;

			SetCrewQuantityFull(sld);
			ProcessHullRepair(sld, 100.0);

			sld.ship.Crew.Morale = 100;
			ChangeCrewExp(sld, "Sailors", 50);
			ChangeCrewExp(sld, "Cannoners", 50);
			ChangeCrewExp(sld, "Soldiers", 50);

			AddItems(sld, "talisman3", 1);
			EquipCharacterByItem(sld,"talisman3");

			SetHalfPerksToChar(sld, true);
			SetCharacterPerk(sld, "CannonProfessional");

			sld.rank = 60;
			SetSelfSkill(sld, 100, 100, 100, 100, 100);
			SetShipSkill(sld, 100, 100, 100, 100, 100, 100, 100, 100, 100);

			SetSPECIAL(sld, 10, 10, 10, 10, 10, 10, 10);
			SetCharacterGoods(sld,GOOD_FOOD,5000);
			SetCharacterGoods(sld,GOOD_BALLS,50000);
			SetCharacterGoods(sld,GOOD_GRAPES,0);
			SetCharacterGoods(sld,GOOD_KNIPPELS,0);
			SetCharacterGoods(sld,GOOD_BOMBS,50000);
			SetCharacterGoods(sld,GOOD_POWDER,100000);
			SetCharacterGoods(sld,GOOD_PLANKS,150);
			SetCharacterGoods(sld,GOOD_SAILCLOTH,150);
			SetCharacterGoods(sld,GOOD_RUM,200);
			SetCharacterGoods(sld,GOOD_WEAPON,600);
			SetCharacterGoods(sld,GOOD_MEDICAMENT,300);

			sld.Abordage.Enable = false;
			sld.Tasks.CanBoarding = false;
			sld.CantBoardEnemies = true;
			//sld.AlwaysFriend = true;
			sld.AlwaysEnemy = true;
			sld.DontRansackCaptain = true;
			sld.AlwaysSandbankManeuver = true;
			Group_FindOrCreateGroup("WarDog");
			Group_SetType("WarDog", "pirate");
			Group_AddCharacter("WarDog", sld.id);
			Group_SetGroupCommander("WarDog", sld.id);
			SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);

			LAi_SetImmortal(sld, false);
			//Group_SetPursuitGroup("WarDog", PLAYER_GROUP);
			Group_SetTaskAttack("WarDog", PLAYER_GROUP);
			Group_LockTask("WarDog");

			WhisperTitanic_ToRandomTown()
			Group_SetAddress("WarDog", pchar.TitanicCity, "Quest_ships", "reload_fort1_siege");
			pchar.TitanicIsKicking = true;
			SetFunctionNPCDeathCondition("WhisperTitanic_Is_Dead", "W_Titanic", false);
			pchar.quest.WhisperTitanic_SurrenderFort.win_condition.l1          = "location";
			pchar.quest.WhisperTitanic_SurrenderFort.win_condition.l1.location = pchar.TitanicCity;
			pchar.quest.WhisperTitanic_SurrenderFort.function             = "WhisperTitanic_SurrenderFort";

			SetQuestHeader("WhisperTitanic");
			AddQuestRecord("WhisperTitanic", 1);
			AddQuestUserData("WhisperTitanic", "sCity", XI_ConvertString("Colony" + pchar.TitanicCity + "Gen"));
			dialog.text = "Говорят, он сейчас взял в осаду . Испанцы то и дело присылают подкрепления, но 'Титаник' топит эскадру за эскадрой. Скорее всего он там еще надолго задержится, пока не разорит город дочиста. Я все сказал, можешь приступать\nИ пока ты не ушла, можешь заказать для 'Пса' какое-то из менее серьёзных улучшений. Они пойдут в дополнение к капитальному ремонту.";
			link.l1 = "Ну, посмотрим, что можно улучшить.";
			link.l1.go = "ship_tunning_start";
		break;

		case "WarDogUpgrade_7":
			dialog.text = "Ну, чем порадуешь старика?";
			link.l1 = "Пока ничем.  ";
			link.l1.go = "exit";
			if(CheckAttribute(pchar, "TitanicIsDown"))
			{
				link.l1 = "Непотопляемый потонул. Репутация твоего ученика навсегда втоптана в грязь. Но, должна признать ученик твой оказался не промах, было непросто.  ";
				link.l1.go = "WarDogUpgrade_8";
			}
		break;

		case "WarDogUpgrade_8":
			DeleteAttribute(pchar, "TitanicIsDown");
			dialog.text = "Да, хорошие новости. Теперь у меня должно прибавиться клиентов. Говорят, 'Титаник' уплыл куда-то на север, где напоролся на огромную льдину, что благополучно пробила ему обшивку.";
			link.l1 = "Кто сказал тебе такую чушь? Я лично потопила его!";
			link.l1.go = "WarDogUpgrade_9";
		break;

		case "WarDogUpgrade_9":
			dialog.text = "Правда? Ну ладно, ладно, верю.";
			link.l1 = "Так что насчёт улучшения для Пса? Ты обещал заняться им, если я помогу с 'Титаником'.";
			link.l1.go = "WarDogUpgrade_10";
		break;

		case "WarDogUpgrade_10":
			dialog.text = "Ах да... Я сделал пару новых чертежей, прикинул что можно улучшить\nВремени эта работа займет немало, так что она тебе обойдется в миллион пиастров. ";
			link.l1 = "Что?! Мы о таком не договаривались.";
			link.l1.go = "WarDogUpgrade_11";
		break;

		case "WarDogUpgrade_11":
			npchar.WarDogUpgradePayment = true;
			AddQuestRecord("WhisperTitanic", 3);
			dialog.text = "Милочка, тут потребуется колоссальная работа. Поверьте, при других условиях я бы потребовал гораздо больше, при чем не только деньги. А эта сумма так, чтобы я не помер с голоду, пока буду работать.";
			if(sti(pchar.money) >= 1000000)
			{
				link.l1 = "Вот твой миллион, старый скупердяй.";
				link.l1.go = "WarDogUpgrade_pay";
			}
			link.l2 = "Да уж. Мне нужно подумать.";
			link.l2.go = "exit";
		break;

		case "WarDogUpgrade_pay":
			DeleteAttribute(npchar, "WarDogUpgradePayment");
			dialog.text = "Что ж, приступим...";
			addMoneyToCharacter(pchar, -1000000);
			link.l1 = "Давай, а я посмотрю.";
			link.l1.go = "WarDogUpgrade_pay_2";
		break;

		case "WarDogUpgrade_pay_2":
			AddQuestRecord("WhisperTitanic", 4);
			CloseQuestHeader("WhisperTitanic");
			shTo = &RealShips[sti(Pchar.Ship.Type)];
			iCaliber = sti(shTo.MaxCaliber);
			switch(iCaliber)
			{
				case 24:
					iCaliber = 4;
				break;
				case 32:
					iCaliber = 5;
				break;
			}
			iCaliber = iCaliber + 1;
			switch(iCaliber)
			{
				case 5:
					iCaliber = 36;
				break;
				case 6:
					iCaliber = 42;
				break;
			}
			shTo.MaxCaliber = iCaliber;

			GetBaseShipParam_ToUpgrade(shTo, "SpeedRate", 2.0);
			GetBaseShipParam_ToUpgrade(shTo, "TurnRate", 10.0);
			GetBaseShipParam_ToUpgrade(shTo, "HP", 1000);
			GetBaseShipParam_ToUpgrade(shTo, "MaxCrew", 120);
			GetBaseShipParam_ToUpgrade(shTo, "WindAgainstSpeed", 1.0);
			GetBaseShipParam_ToUpgrade(shTo, "Capacity", 700);
			shTo.HullArmor = 30;
			shTo.OptCrew = 300;

			DeleteAttribute(npchar, "WarDogUpgradePayment");
			DialogExit();
			AddCharacterExpToSkill(pchar, "Repair", 5000);
			SetLaunchFrameFormParam("Прошел месяц. Наблюдая за работой Алексуса, вы узнали много нового о кораблестроении и плотницком ремесле.", "", 0.1, 15.0);
			LaunchFrameForm();
			WaitDate("",0,0,30, 0, 20);
			npchar.dialog.currentnode = "WarDogUpgrade_pay_1";
		break;

		case "WarDogUpgrade_pay_1":
			dialog.text = "Ну вот и всё. Теперь мне действительно не стыдно называть 'Пса' одной из своих работ. Уже можешь выходить в море. Только поаккуратней там, не хочу, чтобы мои труды пошли насмарку.";
			link.l1 = "Ладно, пойду проверять.";
			link.l1.go = "exit";
		break;
		//<-Капремонт пса
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

void checkMatherial(ref Pchar, ref NPChar, int good1, int good2, int good3)
{
    int amount;

    amount = GetSquadronGoods(Pchar, good1) - sti(NPChar.Tuning.Matherial1);
    if (amount < 0)
    {
       amount = amount + sti(NPChar.Tuning.Matherial1);
    }
    else
    {
        amount = sti(NPChar.Tuning.Matherial1);
    }
    RemoveCharacterGoods(Pchar, good1, amount);
    NPChar.Tuning.Matherial1 = sti(NPChar.Tuning.Matherial1) - amount;

    amount = GetCharacterItem(pchar, good2) - sti(NPChar.Tuning.Matherial2);
    if (amount < 0)
    {
       amount = amount + sti(NPChar.Tuning.Matherial2);
    }
    else
    {
        amount = sti(NPChar.Tuning.Matherial2);
    }
    TakeNItems(pchar, good2, -amount);
    NPChar.Tuning.Matherial2 = sti(NPChar.Tuning.Matherial2) - amount;

    amount = GetCharacterItem(pchar, good3) - sti(NPChar.Tuning.Matherial3);
    if (amount < 0)
    {
       amount = amount + sti(NPChar.Tuning.Matherial3);
    }
    else
    {
        amount = sti(NPChar.Tuning.Matherial3);
    }
    TakeNItems(pchar, good3, -amount);
    NPChar.Tuning.Matherial3 = sti(NPChar.Tuning.Matherial3) - amount;
}

void GetBaseShipParam_ToUpgrade(ref shTo, string param, float num)
{
	string sAttr = "Bonus_"+param;
	Log_Info(sAttr);
	int iRealShipType = sti(shTo.basetype);
	string sParam =	GetBaseShipParamFromType(iRealShipType, param);
	if(CheckAttribute(shTo, sAttr))
	{
		shTo.(param) = stf(shTo.(param)) - stf(shTo.(sAttr));
		shTo.(sAttr) = stf(shTo.(sAttr)) + num;
		shTo.(param) = stf(shTo.(param)) + stf(shTo.(sAttr));
	}
	else
	{
		shTo.(sAttr) = num;
		shTo.(param) = stf(shTo.(param)) + stf(shTo.(sAttr));
	}
}
