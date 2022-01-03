// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool bGoldMine, bSilverMine, bIronMine;
	bGoldMine = false;
	bSilverMine = false;
	bIronMine = false;

	if(CheckAttribute(PChar, "ColonyBuilding.GoldMine.BuildingTime"))
	{
		bGoldMine = PChar.ColonyBuilding.GoldMine == true && PChar.ColonyBuilding.GoldMine.BuildingTime == false;
	}
	if(CheckAttribute(PChar, "ColonyBuilding.SilverMine.BuildingTime"))
	{
		bSilverMine = PChar.ColonyBuilding.SilverMine == true && PChar.ColonyBuilding.SilverMine.BuildingTime == false;
	}
	if(CheckAttribute(PChar, "ColonyBuilding.IronMine.BuildingTime"))
	{
		bIronMine = PChar.ColonyBuilding.IronMine == true && PChar.ColonyBuilding.IronMine.BuildingTime == false;
	}

	int iCost = 0;
	string sString = "";
	int iQty = 0;

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Спрашивай, чего ты хочешь?",
                          "Мы только что поднимали это тему. Вы, вероятно, запамятовали...", "Сегодня вы уже третий раз говорите о каком-то вопросе...",
                          "Послушай, это магазин, здесь люди покупают что-то. Не отвлекай меня!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Знаешь, " + NPChar.name + ", как-нибудь в следующий раз.", "Точно, забыл что-то...",
                      "Да уж, действительно в третий раз...", "Гм, не буду...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";

			link.l2 = "Хотелось бы поговорить о снабжении колонии необходимыми товарами.";
			link.l2.go = "Colony_1";

			link.l3 = "Я хочу пообщаться с тобой о авто-сбыте добываемых руд и товаров на рудниках и плантации.";
			link.l3.go = "AutoSell_1";
		break;


		case "Colony_1":
			dialog.Text = "Ах, вы об этом. Что именно Вас интересует?";
			Link.l1 = "Стоимость снабжения некоторых объектов.";
			Link.l1.go = "Cost";
			Link.l2 = "Расскажи подробнее об этом.";
			Link.l2.go = "AutoPurchase";

			if(PChar.ColonyBuilding.Colony.AutoPurchase == false)
			{
				Link.l3 = "Хотелось бы воспользоваться возможностью снабжения колонии.";
				Link.l3.go = "Colony_AutoPurchase";
			}
			else
			{
				Link.l3 = "Необходимо приостановить снабжение колонии.";
				Link.l3.go = "Colony_OffAutoPurchase";
			}

			if(bGoldMine || bSilverMine || bIronMine)
			{
				if(PChar.ColonyBuilding.Mines.AutoPurchase == false)
				{
					Link.l4 = "Хотелось бы воспользоваться возможностью снабжения рудников.";
					Link.l4.go = "Mines_AutoPurchase";
				}
				else
				{
					Link.l4 = "Необходимо приостановить снабжение рудников.";
					Link.l4.go = "Mines_OffAutoPurchase";
				}
			}

			if(PChar.ColonyBuilding.Plantation == true && PChar.ColonyBuilding.Plantation.BuildingTime == false)
			{
				if(PChar.ColonyBuilding.Plantation.AutoPurchase == false)
				{
					Link.l5 = "Хотелось бы воспользоваться возможностью снабжения плантации.";
					Link.l5.go = "Plantation_AutoPurchase";
				}
				else
				{
					Link.l5 = "Необходимо приостановить снабжение плантации.";
					Link.l5.go = "Plantation_OffAutoPurchase";
				}
			}

			Link.l6 = "Извини, " + NPChar.name + ", мне необходимо откланяться.";
			Link.l6.go = "exit";
		break;

		case "Colony_AutoPurchase":
			dialog.Text = "Отлично, капитан! Не сомневайтесь, начиная с этого дня я всерьёз займусь этим.";
			Link.l1 = LinkRandPhrase("Спасибо.", "Ясно.", "Хорошо.");
			Link.l1.go = "Colony_AutoPurchase_Yes";
			Link.l2 = "Э-э.. Я передумал.";
			Link.l2.go = "exit";
		break;

		case "Colony_AutoPurchase_Yes":
			PChar.ColonyBuilding.Colony.AutoPurchase = true;
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;

		case "Mines_AutoPurchase":
			dialog.Text = "Отлично, капитан! Не сомневайтесь, начиная с этого дня я всерьёз займусь этим.";
			Link.l1 = LinkRandPhrase("Спасибо.", "Ясно.", "Хорошо.");
			Link.l1.go = "Mines_AutoPurchase_Yes";
			Link.l2 = "Э-э.. Я передумал.";
			Link.l2.go = "exit";
		break;

		case "Mines_AutoPurchase_Yes":
			PChar.ColonyBuilding.Mines.AutoPurchase = true;
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;

		case "Plantation_AutoPurchase":
			dialog.Text = "Отлично, капитан! Не сомневайтесь, начиная с этого дня я всерьёз займусь этим.";
			Link.l1 = LinkRandPhrase("Спасибо.", "Ясно.", "Хорошо.");
			Link.l1.go = "Plantation_AutoPurchase_Yes";
			Link.l2 = "Э-э.. Я передумал.";
			Link.l2.go = "exit";
		break;

		case "Plantation_AutoPurchase_Yes":
			PChar.ColonyBuilding.Plantation.AutoPurchase = true;
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;

		case "Colony_OffAutoPurchase":
			dialog.Text = "Вы уверены, капитан?";
			Link.l1 = LinkRandPhrase("Конечно. Слишком дорогое удовольствие.", "Уверен.", "Слишком дорого.");
			Link.l1.go = "Colony_OffAutoPurchase_Yes";
			Link.l2 = LinkRandPhrase("Э-э.. Вы правы, не стоит этого делать.", "Хм... Я передумал.", "Отставить!");
			Link.l2.go = "exit";
		break;

		case "Colony_OffAutoPurchase_Yes":
			PChar.ColonyBuilding.Colony.AutoPurchase = false;
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;

		case "Mines_OffAutoPurchase":
			dialog.Text = "Вы уверены, капитан?";
			Link.l1 = LinkRandPhrase("Конечно. Слишком дорогое удовольствие.", "Уверен.", "Слишком дорого.");
			Link.l1.go = "Mines_OffAutoPurchase_Yes";
			Link.l2 = LinkRandPhrase("Э-э.. Вы правы, не стоит этого делать.", "Хм... Я передумал.", "Отставить!");
			Link.l2.go = "exit";
		break;

		case "Mines_OffAutoPurchase_Yes":
			PChar.ColonyBuilding.Mines.AutoPurchase = false;
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;

		case "Plantation_OffAutoPurchase":
			dialog.Text = "Вы уверены, капитан?";
			Link.l1 = LinkRandPhrase("Конечно. Слишком дорогое удовольствие.", "Уверен.", "Слишком дорого.");
			Link.l1.go = "Plantation_OffAutoPurchase_Yes";
			Link.l2 = LinkRandPhrase("Э-э.. Вы правы, не стоит этого делать.", "Хм... Я передумал.", "Отставить!");
			Link.l2.go = "exit";
		break;

		case "Plantation_OffAutoPurchase_Yes":
			PChar.ColonyBuilding.Plantation.AutoPurchase = false;
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;

		case "Cost":
			dialog.Text = "Какие объекты вы имеете в виду? Полная стоимость или с учётом текущего заполнения складов?";
			Link.l1 = "Полная стоимость снабжения колонии.";
			Link.l1.go = "Cost_Colony_Full";
			Link.l2 = "Стоимость снабжения колонии с учётом текущего заполнения складов.";
			Link.l2.go = "Cost_Colony";

			if(bGoldMine || bSilverMine || bIronMine)
			{
				Link.l3 = "Полная стоимость снабжения рудников.";
				Link.l3.go = "Cost_Mines_Full";
				Link.l4 = "Стоимость снабжения рудников с учётом текущего заполнения складов.";
				Link.l4.go = "Cost_Mines";
			}

			if(PChar.ColonyBuilding.Plantation == true && PChar.ColonyBuilding.Plantation.BuildingTime == false)
			{
				Link.l5 = "Полная стоимость снабжения плантации.";
				Link.l5.go = "Cost_Plantation_Full";
				Link.l6 = "Стоимость снабжения плантации с учётом текущего заполнения складов.";
				Link.l6.go = "Cost_Plantation";
			}

			Link.l7 = "Извини, " + NPChar.name + ", мне необходимо откланяться.";
			Link.l7.go = "exit";
		break;

		case "Cost_Colony_Full":
			iCost = GetSumAutoPurchaseColonyGoods("Colony", false);
			dialog.Text = "На данный момент, с учётом вместимости складов, полная стоимость снабжения колонии составляет: " + iCost + " пиастров.";
			Link.l1 = LinkRandPhrase("Спасибо.", "Ясно.", "Хорошо.");
			Link.l1.go = "quests";
		break;

		case "Cost_Colony":
			iCost = GetSumAutoPurchaseColonyGoods("Colony", true);
			dialog.Text = "На данный момент, с учётом вместимости складов, стоимость снабжения колонии с учётом текущего заполнения составляет: " + iCost + " пиастров.";
			Link.l1 = LinkRandPhrase("Спасибо.", "Ясно.", "Хорошо.");
			Link.l1.go = "quests";
		break;

		case "Cost_Mines_Full":
			iCost = GetSumAutoPurchaseColonyGoods("Mines", false);
			dialog.Text = "На данный момент, с учётом вместимости складов, полная стоимость снабжения рудников составляет: " + iCost + " пиастров.";
			Link.l1 = LinkRandPhrase("Спасибо.", "Ясно.", "Хорошо.");
			Link.l1.go = "quests";
		break;

		case "Cost_Mines":
			iCost = GetSumAutoPurchaseColonyGoods("Mines", true);
			dialog.Text = "На данный момент, с учётом вместимости складов, стоимость снабжения рудников с учётом текущего заполнения составляет: " + iCost + " пиастров.";
			Link.l1 = LinkRandPhrase("Спасибо.", "Ясно.", "Хорошо.");
			Link.l1.go = "quests";
		break;

		case "Cost_Plantation_Full":
			iCost = GetSumAutoPurchaseColonyGoods("Plantation", false);
			dialog.Text = "На данный момент, с учётом вместимости складов, полная стоимость снабжения плантации составляет: " + iCost + " пиастров.";
			Link.l1 = LinkRandPhrase("Спасибо.", "Ясно.", "Хорошо.");
			Link.l1.go = "quests";
		break;

		case "Cost_Plantation":
			iCost = GetSumAutoPurchaseColonyGoods("Plantation", true);
			dialog.Text = "На данный момент, с учётом вместимости складов, стоимость снабжения плантации с учётом текущего заполнения составляет: " + iCost + " пиастров.";
			Link.l1 = LinkRandPhrase("Спасибо.", "Ясно.", "Хорошо.");
			Link.l1.go = "quests";
		break;

		case "AutoPurchase":
			dialog.Text = "Своевременное снабжение населения подразумевает заполнение складов колонии и других строений недостающим количеством товаров первой необходимости - провиантом, медикаментами и даже инструментами. Наличие необходимого количества этих товаров станет гарантией хорошей жизни в колонии. \n Своевременное пополнение городских и других складов позволить избежать болезней и голода. Например, чтобы заполнить склад колонии провизией и медикаментами в данный момент потребуется " + GetSumAutoPurchaseColonyGoods("Colony", true) + " пиастров. Снабжение на колонии не останавливается - возможно снабжение таких объектов как рудники и плантации. \n Каждые несколько дней производится снабжение выбранных Вами строений, и если казна колонии будет иметь необходимую сумму, то всё пройдёт успешно. Кроме того, так как именно я этим занимаюсь, закупка товара будет стоить гораздно дешевле, нежели в других колониях. Если вы захотите воспользоваться этим предложением - то просто скажите мне об этом.";
			Link.l1 = LinkRandPhrase("Спасибо.", "Ясно.", "Хорошо.");
			Link.l1.go = "exit";
		break;

		//////////////////////////////////////////////////////////////////////////
		// АВТО СБЫТ
		//////////////////////////////////////////////////////////////////////////
		case "AutoSell_1":
			dialog.text = "Что именно вы хотели узнать об этом, капитан?";
			link.l1 = "Хотелось бы пересмотреть объекты авто-сбыта.";
			link.l1.go = "AutoSell_SetAction";
			link.l2 = "Я хочу установить количество сбываемого товара.";
			link.l2.go = "AutoSell_SetQty";
			link.l3 = "Последние цены, по которым продаётся товар.";
			link.l3.go = "AutoSellCosts";
			link.l4 = "Я хочу узнать подробнее об этом.";
			link.l4.go = "AutoSellInfo";
			link.l5 = "Извините, у меня куча дел.";
			link.l5.go = "exit";
		break;

		case "AutoSell_SetAction":
			dialog.text = "Хм, давайте посмотрим. " + GetColonyAutoSellWork();

			if(PChar.Mines.GoldMine == true || PChar.Mines.SilverMine == true || PChar.Mines.IronMine == true)
			{
				if(PChar.ColonyBuilding.Mines.AutoSell == false)
				{
					link.l1 = "Я хочу, чтобы товар продавался со склада рудников.";
					link.l1.go = "AutoSell_Mines_On_1";
				}
				else
				{
					link.l1 = "Я хочу приостановить продажу товара со склада рудников.";
					link.l1.go = "AutoSell_Mines_Off_1";
				}
			}

			if(PChar.ColonyBuilding.Plantation == true && PChar.ColonyBuilding.Plantation.BuildingTime == false)
			{
				if(PChar.ColonyBuilding.Plantation.AutoSell == false)
				{
					link.l2 = "Я хочу, чтобы товар продавался со склада плантации.";
					link.l2.go = "AutoSell_Plantation_On_1";
				}
				else
				{
					link.l2 = "Я хочу приостановить продажу товара со склада плантации.";
					link.l2.go = "AutoSell_Plantation_Off_1";
				}
			}

			link.l3 = "Пожалуй, я передумал.";
			link.l3.go = "exit";
		break;

		case "AutoSell_Mines_On_1":
			dialog.text = "Вы уверены, капитан?";
			link.l1 = LinkRandPhrase("Да.", "Совершенно точно.", "Конечно же, уверен.");
			link.l1.go = "AutoSell_Mines_On_2";
			link.l2 = LinkRandPhrase("Мм... Пожалуй, вы правы - стоит подумать ещё.", "Я передумал.", "Эээ... Нет, не уверен.");
			link.l2.go = "exit";
		break;

		case "AutoSell_Mines_On_2":
			PChar.ColonyBuilding.Mines.AutoSell = true;
			dialog.text = "Хорошо, капитан! С сегодняшнего дня займусь этим вопросом.";
			link.l1 = "Вот и славно.";
			link.l1.go = "exit";
		break;

		case "AutoSell_Plantation_On_1":
			dialog.text = "Вы уверены, капитан?";
			link.l1 = LinkRandPhrase("Да.", "Совершенно точно.", "Конечно же, уверен.");
			link.l1.go = "AutoSell_Plantation_On_2";
			link.l2 = LinkRandPhrase("Мм... Пожалуй, вы правы - стоит подумать ещё.", "Я передумал.", "Эээ... Нет, не уверен.");
			link.l2.go = "exit";
		break;

		case "AutoSell_Plantation_On_2":
			PChar.ColonyBuilding.Plantation.AutoSell = true;
			dialog.text = "Хорошо, капитан! С сегодняшнего дня займусь этим вопросом.";
			link.l1 = "Вот и славно.";
			link.l1.go = "exit";
		break;

		case "AutoSell_Mines_Off_1":
			dialog.text = "Вы действительно хотите приостановить сбыт добытых на рудниках товаров?";
			link.l1 = LinkRandPhrase("Да.", "Совершенно точно.", "Конечно же, уверен.");
			link.l1.go = "AutoSell_Mines_Off_2";
			link.l2 = LinkRandPhrase("Отставить!", "Я, пожалуй, передумал - нам необходимо своевременно сбывать добытое.", "Эээ... Нет, не уверен.");
			link.l2.go = "exit";
		break;

		case "AutoSell_Mines_Off_2":
			PChar.ColonyBuilding.Mines.AutoSell = false;
			dialog.text = "Как пожелаете, капитан. В таком случае, как решитесь снова возобновить сбыт товара с рудников - приходите.";
			link.l1 = LinkRandPhrase("Спасибо.", "Ясно.", "Хорошо.");
			link.l1.go = "exit";
		break;

		case "AutoSell_Plantation_Off_1":
			dialog.text = "Вы действительно хотите приостановить сбыт добытых на плантации товаров?";
			link.l1 = LinkRandPhrase("Да.", "Совершенно точно.", "Конечно же, уверен.");
			link.l1.go = "AutoSell_Plantation_Off_2";
			link.l2 = LinkRandPhrase("Отставить!", "Я, пожалуй, передумал - нам необходимо своевременно сбывать добытое.", "Эээ... Нет, не уверен.");
			link.l2.go = "exit";
		break;

		case "AutoSell_Plantation_Off_2":
			PChar.ColonyBuilding.Plantation.AutoSell = false;
			dialog.text = "Как пожелаете, капитан. В таком случае, как решитесь снова возобновить сбыт товара с плантации - приходите.";
			link.l1 = LinkRandPhrase("Спасибо.", "Ясно.", "Хорошо.");
			link.l1.go = "exit";
		break;

		case "AutoSell_SetQty":
			if(PChar.ColonyBuilding.Mines.AutoSell == false && PChar.ColonyBuilding.Plantation.AutoSell == false)
			{
				dialog.text = "Капитан, на данный момент авто-сбыт товаров не производиться ни на рудниках, ни на плантации.";
				link.l1 = LinkRandPhrase("Спасибо.", "Ясно.", "Хорошо.");
				link.l1.go = "exit";
				break;
			}

			dialog.text = "Текущее количество сбываемого товара для рудников: " + GetColonyAutoSellCurrentQty("Mines") + ", а для плантации: " + GetColonyAutoSellCurrentQty("Plantation") + ". Максимальное количество сбываемого товара для рудников: " +AUTO_SELL_MINES_MAX+ ", для плантации же: " +AUTO_SELL_PLANTATION_MAX+ ".";

			if(PChar.ColonyBuilding.Mines.AutoSell == true)
			{
				link.l1 = "Необходимо поменять количество сбываемого товара на рудниках.";
				link.l1.go = "AutoSell_SetQty_Mines_1";
			}

			if(PChar.ColonyBuilding.Plantation.AutoSell == true)
			{
				link.l2 = "Необходимо поменять количество сбываемого товара на плантации.";
				link.l2.go = "AutoSell_SetQty_Plantation_1";
			}

			link.l3 = "Пожалуй, я передумал.";
			link.l3.go = "exit";
		break;

		case "AutoSell_SetQty_Mines_1":
			dialog.text = "Итак, какое количество вы хотите установить для сбыта товара на рудниках?";
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "AutoSell_SetQty_Mines_2";
		break;

		case "AutoSell_SetQty_Mines_2":
			sString = GetStrSmallRegister(dialogEditStrings[1]);
			iQty = sti(sString);

			if(iQty <= 0)
			{
				dialog.text = "Шутить изволите?";
				link.l1 = "Давайте ещё раз попробуем...";
				link.l1.go = "AutoSell_SetQty_Mines_1";
				link.l2 = "Я передумал.";
				link.l2.go = "exit";
				break;
			}

			if(iQty > AUTO_SELL_MINES_MAX)
			{
				dialog.text = iQty + "? Капитан, я же вас предупреждал, что максимальное количество для сбыта товара, добытого на рудниках, равно " + AUTO_SELL_MINES_MAX + " шт.";
				link.l1 = "Давайте ещё раз попробуем...";
				link.l1.go = "AutoSell_SetQty_Mines_1";
				link.l2 = "Я передумал.";
				link.l2.go = "exit";
				break;
			}

			dialog.text = iQty + "? Что ж, это приемлимая цифра. Вы уверены в своём решении?";
			link.l1 = "Да, абсолютно.";
			link.l1.go = "AutoSell_SetQty_Mines_3";
			link.l2 = "Нет, я передумал.";
			link.l2.go = "exit";
		break;

		case "AutoSell_SetQty_Mines_3":
			sString = GetStrSmallRegister(dialogEditStrings[1]);
			iQty = sti(sString);

			PChar.ColonyBuilding.Mines.AutoSell.Qty = iQty;
			dialog.text = "Хорошо, господин капитан.";
			link.l1 = "Вот и славно.";
			link.l1.go = "exit";
		break;

		case "AutoSell_SetQty_Plantation_1":
			dialog.text = "Итак, какое количество вы хотите установить для сбыта товара на плантации?";
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "AutoSell_SetQty_Plantation_2";
		break;

		case "AutoSell_SetQty_Plantation_2":
			sString = GetStrSmallRegister(dialogEditStrings[1]);
			iQty = sti(sString);

			if(iQty <= 0)
			{
				dialog.text = "Шутить изволите?";
				link.l1 = "Давайте ещё раз попробуем...";
				link.l1.go = "AutoSell_SetQty_Plantation_1";
				link.l2 = "Я передумал.";
				link.l2.go = "exit";
				break;
			}

			if(iQty > AUTO_SELL_PLANTATION_MAX)
			{
				dialog.text = iQty + "? Капитан, я же вас предупреждал, что максимальное количество для сбыта товара, добытого на плантации, равно " + AUTO_SELL_PLANTATION_MAX + " шт.";
				link.l1 = "Давайте ещё раз попробуем...";
				link.l1.go = "AutoSell_SetQty_Plantation_1";
				link.l2 = "Я передумал.";
				link.l2.go = "exit";
				break;
			}

			dialog.text = iQty + "? Что ж, это приемлимая цифра. Вы уверены в своём решении?";
			link.l1 = "Да, абсолютно.";
			link.l1.go = "AutoSell_SetQty_Plantation_3";
			link.l2 = "Нет, я передумал.";
			link.l2.go = "exit";
		break;

		case "AutoSell_SetQty_Plantation_3":
			sString = GetStrSmallRegister(dialogEditStrings[1]);
			iQty = sti(sString);

			PChar.ColonyBuilding.Plantation.AutoSell.Qty = iQty;
			dialog.text = "Хорошо, господин капитан.";
			link.l1 = "Вот и славно.";
			link.l1.go = "exit";
		break;

		case "AutoSellCosts":
			dialog.text = "Золото: " + GetCurrentGoodBaseCostForAutoSell(GOOD_GOLD) + " золотых; Серебро: " + GetCurrentGoodBaseCostForAutoSell(GOOD_SILVER) + " золотых; Железо: " + GetCurrentGoodBaseCostForAutoSell(GOOD_IRON) + " золотых; Сахар: " + GetCurrentGoodBaseCostForAutoSell(GOOD_SUGAR) + " золотых; Кофе: " + GetCurrentGoodBaseCostForAutoSell(GOOD_COFFEE) + " золотых.";
			link.l1 = "Спасибо за информацию. Давай ещё поговорим о продаже.";
			link.l1.go = "AutoSell_1";
			link.l2 = "Спасибо за информацию. Я, пожалуй, пойду.";
			link.l2.go = "exit";
		break;

		case "AutoSellInfo":
			dialog.text = "Чтобы плантация и рудники своевременно приносили доход колонии, вы можете воспользоваться авто-продажей товаров со складов каждый раз после произведённых работ по добыче руд и товаров. \n Каждый раз на продажу со складов будет выделено указанное Вами число товаров. \n Существует максимальная цифра количества руд и товаров для разовой продажи - каждую руду с рудников вы можете продать не более " +AUTO_SELL_MINES_MAX+ " шт., а товары, добытые на плантации, не более " +AUTO_SELL_PLANTATION_MAX+ " шт. \n Если количество товара на складе будет меньше указанного Вами количества для продажи, то продаётся весь имеющийся товар данного типа. \n Если товар будет продаваться подобным образом - вы будете получать извещение о каждой подобной операции. Важно учесть, что продажа руд и товаров будет проводиться по ценам, которые дешевле, чем при самостоятельной продаже, так как все расходы на поиск покупателей и транспортировку я беру на себя.";
			link.l1 = LinkRandPhrase("Спасибо.", "Ясно.", "Хорошо.");
			link.l1.go = "exit";
		break;
	}

	UnloadSegment(NPChar.FileDialog2);
}

