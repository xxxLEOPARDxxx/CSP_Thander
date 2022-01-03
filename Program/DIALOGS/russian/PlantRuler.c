
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Meet":
			dialog.text = "Приветствую вас. Я - " + GetFullName(NPChar) + ", начальник плантации Барбадоса. Представьтесь, пожалуйста.";
			Link.l1 = "Здравствуйте, " + GetFullName(NPChar) + ". Я " + GetFullName(PChar) + ", капитан корабля '" + PChar.ship.name + "'.";
			link.l1.go = "Meet_2";
		break;

		case "Exit":
			NextDiag.CurrentNode = "Meet_2";
			DialogExit();
		break;

		case "Meet_2":
			if (!CheckAttribute(npchar,"met")) dialog.text = "Приятно познакомиться. По какому поводу зашли?";
			else dialog.text = "По какому поводу зашли, капитан?";
			if (sti(pchar.Ship.Cargo.Goods.Slaves) > 0 && sti(npchar.SlavesLimit)>0)
			{
				Link.l1 = "Я бы хотел"+ GetSexPhrase("","а")+" вам предложить купить... товар.";
				link.l1.go = "trade_good";
			}
			Link.l2 = "Просто прогуливал"+ GetSexPhrase("ся","ась")+", всего доброго.";
			link.l2.go = "exit";
			npchar.met = 1;
		break;

		case "trade_good":
			dialog.text = "Товар? Вы хотите сказать, рабов?";
			Link.l1 = "Да, именно.";
			link.l1.go = "trade_good_2";
			Link.l2 = "Пожалуй я передумал"+ GetSexPhrase("","а")+". Всего хорошего.";
			link.l2.go = "exit";
		break;

		case "trade_good_2":
			dialog.text = "Активы плантации позволяют приобретать до 1000 рабов каждые две недели у частных лиц. Сколько вы хотите предложить?";
			Link.l1 = "Рабы в количестве "+sti(pchar.Ship.Cargo.Goods.Slaves)+".";
			link.l1.go = "trade_good_3";
			Link.l2 = "Пожалуй я передумал"+ GetSexPhrase("","а")+". Всего хорошего.";
			link.l2.go = "exit";
		break;

		case "trade_good_3":
			if (sti(pchar.Ship.Cargo.Goods.Slaves) > sti(npchar.SlavesLimit)) dialog.text = "Сейчас я могу купить у вас до "+npchar.SlavesLimit+ " рабов ценой по 215 за единицу. Итого, "+FindRussianMoneyString(sti(npchar.SlavesLimit)*215)+". Устраивает?";
			else dialog.text = "Сейчас я могу купить у вас до "+npchar.SlavesLimit+ " рабов ценой по 215 за единицу. Итого, "+FindRussianMoneyString(sti(pchar.Ship.Cargo.Goods.Slaves)*215)+". Устраивает?";
			Link.l1 = "Вполне.";
			link.l1.go = "trade_good_4";
			Link.l2 = "Пожалуй я передумал"+ GetSexPhrase("","а")+". Всего хорошего.";
			link.l2.go = "exit";
		break;

		case "trade_good_4":
			if (sti(pchar.Ship.Cargo.Goods.Slaves) > sti(npchar.SlavesLimit))
			{
				AddMoneyToCharacter(pchar, 215*sti(npchar.SlavesLimit));
				pchar.Ship.Cargo.Goods.Slaves = sti(pchar.Ship.Cargo.Goods.Slaves) - sti(npchar.SlavesLimit);
				npchar.SlavesLimit = 0;
			}
			else
			{
				AddMoneyToCharacter(pchar, 215*sti(pchar.Ship.Cargo.Goods.Slaves));
				npchar.SlavesLimit = sti(npchar.SlavesLimit)-sti(pchar.Ship.Cargo.Goods.Slaves);
				pchar.Ship.Cargo.Goods.Slaves = 0;
			}
			SetTimerFunction("RefreshSlavesLimit", 0, 0, 14);
			dialog.text = "Держите, вот ваши деньги.";
			Link.l1 = "Благодарю вас.";
			link.l1.go = "exit";
		break;
	}
}
