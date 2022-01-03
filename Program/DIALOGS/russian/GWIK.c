
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
		case "First time":
			if (NPChar.id == "GWIK_char") dialog.text = "Приветствую вас. Я - " + GetFullName(NPChar) + ", представитель офиса Голландской Вест-Индской Торговой Компании на острове Кюрасао. Представьтесь, пожалуйста.";
			else dialog.text = "Приветствую вас. Я - " + GetFullName(NPChar) + ", представитель офиса Голландской Вест-Индской Торговой Компании на острове Сан Мартин. Представьтесь, пожалуйста.";
			Link.l1 = "Здравствуйте, " + GetFullName(NPChar) + ". Я " + GetFullName(PChar) + ", капитан корабля '" + PChar.ship.name + "'.";
			link.l1.go = "Meet_2";
		break;

		case "Exit":
			NextDiag.CurrentNode = "Meet_2";
			DialogExit();
		break;

		case "Meet_2":
			if (!CheckAttribute(npchar,"met")) dialog.text = "Приятно познакомиться, капитан. По какому поводу зашли?";
			else dialog.text = "По какому поводу зашли, капитан?";
			if (!CheckAttribute(pchar,"GwikTimer"))
			{
				Link.l1 = "Я бы хотел"+ GetSexPhrase("","а")+" приобрести у вас информацию о ценах в магазинах по архипелагу.";
				link.l1.go = "trade_info";
			}
			Link.l2 = "Просто заш"+ GetSexPhrase("ёл","ла")+" поздороваться, всего доброго.";
			link.l2.go = "exit";
			npchar.met = 1;
		break;

		case "trade_info":
			dialog.text = "Да, я располагаю такой информацией и могу её поделиться. С вас 50000 пиастров.";
			if (sti(pchar.money) >= 50000)
			{
				Link.l1 = "Хорошо, вот ваши деньги.";
				link.l1.go = "trade_info_2";
			}
			Link.l2 = "Пожалуй я передумал"+ GetSexPhrase("","а")+". Всего хорошего.";
			link.l2.go = "exit";
		break;

		case "trade_info_2":
			for (int i = 0; i< MAX_COLONIES; i++)
			{
                ref rcolony = &Colonies[i];
			    if (rcolony.id != "Caiman" && rcolony.id != "Panama" && rcolony.nation != "none") SetPriceListByStoreMan(rcolony);
            }
			log_info("Получен список цен во всех магазинах Карибского архипелага.");
			PlayStereoSound("notebook");
			AddMoneyToCharacter(pchar,-50000);

			dialog.text = "...Держите, здесь вся нужная вам информация. Желаю успехов!";
			Link.l1 = "Благодарю вас. До свидания!";
			link.l1.go = "exit";
			pchar.GwikTimer = true;
			SetTimerFunction("RefreshGWIK", 0, 0, 15);
		break;
	}
}
