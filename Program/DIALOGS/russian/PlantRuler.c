
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int slaveCount, i, companion, slavePartCount;

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

			if (sti(npchar.SlavesLimit) > 0)
			{
				slaveCount = sti(PChar.Ship.Cargo.Goods.Slaves);

				for (i = 1; i < COMPANION_MAX; i++)
				{
					companion = GetCompanionIndex(PChar, i);
					if(companion != -1 && GetRemovable(&Characters[companion]))
						slaveCount += sti(Characters[companion].Ship.Cargo.Goods.Slaves);
				}

				if (slaveCount > 0)
				{
					NPchar.HeroSlaveCount = slaveCount;
					Link.l1 = "Я бы хотел"+ GetSexPhrase("","а")+" вам предложить купить... товар.";
					link.l1.go = "trade_good";
				}
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
			Link.l1 = "Рабы в количестве " + (NPchar.HeroSlaveCount) + ".";
			link.l1.go = "trade_good_3";
			Link.l2 = "Пожалуй я передумал"+ GetSexPhrase("","а")+". Всего хорошего.";
			link.l2.go = "exit";
		break;

		case "trade_good_3":
			slaveCount = func_min(NPchar.HeroSlaveCount, NPchar.SlavesLimit);
			dialog.text = "Сейчас я могу купить у вас до " + slaveCount + " рабов ценой по 215 за единицу. Итого, " + FindRussianMoneyString(slaveCount * 215) + ". Устраивает?";
			Link.l1 = "Вполне.";
			link.l1.go = "trade_good_4";
			Link.l2 = "Пожалуй я передумал"+ GetSexPhrase("","а")+". Всего хорошего.";
			link.l2.go = "exit";
		break;

		case "trade_good_4":
			slaveCount = func_min(NPchar.HeroSlaveCount, NPchar.SlavesLimit);

			AddMoneyToCharacter(PChar, 215 * slaveCount);
			npchar.SlavesLimit = npchar.SlavesLimit - slaveCount;

			slavePartCount = func_min(slaveCount, sti(PChar.Ship.Cargo.Goods.Slaves));
			PChar.Ship.Cargo.Goods.Slaves = sti(PChar.Ship.Cargo.Goods.Slaves) - slavePartCount;
			slaveCount -= slavePartCount;

			for (i = 1; (i < COMPANION_MAX) && (slaveCount > 0); i++)
			{
				companion = GetCompanionIndex(PChar, i);
				if(companion != -1 && GetRemovable(&Characters[companion]))
				{
					slavePartCount = func_min(slaveCount, sti(Characters[companion].Ship.Cargo.Goods.Slaves));
					Characters[companion].Ship.Cargo.Goods.Slaves = sti(Characters[companion].Ship.Cargo.Goods.Slaves) - slavePartCount;
					slaveCount -= slavePartCount;
				}
			}

			SetTimerFunction("RefreshSlavesLimit", 0, 0, 14);
			dialog.text = "Держите, вот ваши деньги.";
			Link.l1 = "Благодарю вас.";
			link.l1.go = "exit";
		break;
	}
}
