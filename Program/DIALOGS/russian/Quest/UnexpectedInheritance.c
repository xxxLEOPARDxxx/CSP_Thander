void ProcessDialogEvent()
{
	ref locLoad = &locations[reload_location_index];
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;
	int i;
	bool hungry = true;
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":

			//dialog.text = "Ошибка";
			link.l1 = "...";
			link.l1.go = "Exit";
			npchar.quest.meeting = "1";

			if (npchar.id == "CrazyScientist")
			{
				dialog.text = "А ну, стой!";
				link.l1.go = "CS";
			}
			NextDiag.TempNode = "First time";
		break;

		case "GrottoSkeleton":
			scareOfficers(70);
			InterfaceStates.Buttons.Save.enable = false;
			LAi_SetImmortal(npchar, false);
			dialog.Text = "Ты приш"+GetSexPhrase("ел","ла")+" смешать свои кости  с нашими?";
			Link.l1 = "Кто ты?";
			Link.l1.go = "GrottoSkeleton_1";
		break;
		case "GrottoSkeleton_1":
			dialog.Text = "Проклятый неудачник! Вот кто я! Папаша оставил нам с братом свои сокровища, но вместо того чтоб поделить и забыть, решил, что мы ещё дети и его затея с поиском клада, сблизит нас. Что ж, сблизились мы так, что ближе некуда!";
			Link.l1 = "Я прош"+GetSexPhrase("ел","ла")+" по всем его подсказкам, они нетронуты, почти. Как вы добрались сюда?";
			Link.l1.go = "GrottoSkeleton_2";
		break;
		case "GrottoSkeleton_2":
			dialog.Text = "Луиджи был умным и пронырливым типом, он пробирался в кабинет отца и внимательно изучал его записи. А когда старик умер, он сразу отправился сюда. Ну а я с пристрастием допросил домашних слуг и последовал за ним";
			Link.l1 = "Но что то пошло не так?";
			Link.l1.go = "GrottoSkeleton_3";
		break;
		case "GrottoSkeleton_3":
			dialog.Text = "Всё пошло не так. Я застал его за открытием сундука и выстрелил ему в голову. Грохот выстрела, обрушил свод пещеры, и меня придавило к трупу моего сводного братца. Так я и лежал во тьме, лицом в месиве, оставшемся от его головы. Потом я умер. Потом приш"+GetSexPhrase("ел","ла")+" ты";
			Link.l1 = "Страшная участь, но меньшего братоубийца не заслуживает! Умри ещё раз!";
			Link.l1.go = "exit_fight";
		break;

		case "GrottoPirate":
			dialog.Text = "Кто - то проболтался о том, куда мы идём? Всех под нож! Сукины дети!";
			Link.l1 = "...";
			Link.l1.go = "exit_fight_grotto";
		break;

		case "Girl":
			dialog.Text = GetSexPhrase("Месье","Госпожа") + ", простите пожалуйста, вы капитан?";
			Link.l1 = "Капитан, но ничего не покупаю и милостыню подаю только у церкви, по воскресеньям.";
			Link.l1.go = "Girl_1";
		break;
		case "Girl_1":
			dialog.Text = "Нет, "+GetSexPhrase("месье","госпожа")+", я не нищенка, прошу вас, выслушайте меня! Мой отчим, тоже капитан, корсар, на службе у Франции, он...";
			Link.l1 = "Погожий день, юная дева просит помощи, звучит как начало приключения. Я выслушаю Вас.";
			Link.l1.go = "Girl_2";
			Link.l2 = "Он, верно будет Вас ругать, за разговоры с незнакомцами. Прошу простить, но у меня срочные дела!";
			Link.l2.go = "Exit_cancel";
		break;
		case "Girl_2":
			dialog.Text = "Спасибо капитан. Мой отчим отдал Богу душу третьего дня, оставив нас с мамой и двумя братишками совсем без средств. Его шлюп, оказался заложен ростовщику и его забрали за долги.";
			Link.l1 = "Мадмуазель, я с радостью помог"+GetSexPhrase("","ла")+" бы вам, но у меня дела...";
			Link.l1.go = "Girl_3";
		break;
		case "Girl_3":
			dialog.Text = "Постойте, прошу вас. Перед смертью, отчим вручил маме этот дневник, сказал что-то про наследство и испустил дух. Я посещала церковную школу, немного разбираю грамоту, но тут какой то непонятный язык. Возможно, тут указано место, где он спрятал сокровища! Он ведь был корсаром!";
			Link.l1 = "А возможно, тут сборник похабных матросских песен...";
			Link.l1.go = "Girl_4";
		break;
		case "Girl_4":
			dialog.Text = "Капитан, прошу Вас!";
			if (sti(pchar.money) >= 7000)
			{
				Link.l1 = "Хорошо, я куплю этот дневник. Пяти тысяч хватит? Ладно, возьмите семь, надеюсь, это поможет вашей семье первое время. Возьмите...";
				Link.l1.go = "Girl_5";
			}
			Link.l2 = "Не интересует. Прощайте.";
			Link.l2.go = "Exit_cancel";
		break;
		case "Girl_5":
			dialog.Text = "Большое вам спасибо, капитан! Вот дневник.";
			AddMoneyToCharacter(PChar, -7000);
			SetQuestHeader("UnexpectedInheritance");
			AddQuestRecord("UnexpectedInheritance", "1");
			AddQuestUserData("UnexpectedInheritance", "sSex", GetSexPhrase("ий","ая"));
			pchar.UnexpectedInheritance = "part1";
			Link.l1 = "Что же, почитаем на досуге.";
			Link.l1.go = "Exit_cancel";
		break;
		case "Girl_annoyed":
			dialog.Text = "До свидания, капитан.";
			Link.l1 = "Ага, до свидания.";
			Link.l1.go = "Exit_cancel";
		break;

		case "Exit_cancel":
			NPChar.LifeDay = 0;
			NextDiag.TempNode = "Girl_annoyed";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;


		case "exit_fight":
			locLoad = &locations[reload_location_index];
			locLoad.box1.items.indian11 = 1;
			locLoad.box1.items.jewelry1 = 5;
			locLoad.box1.items.jewelry2 = 10;
			locLoad.box1.items.jewelry3 = 15;
			locLoad.box1.items.jewelry4 = 20;
			locLoad.box1.items.jewelry5 = 25;
			locLoad.box1.items.jewelry6 = 30;
			locLoad.box1.items.jewelry7 = 35;
			SetSkeletonsToLocation(&locations[reload_location_index]);
			AddDialogExitQuest("MainHeroFightModeOn");
			//LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			LAi_group_MoveCharacter(NPChar, LAI_GROUP_MONSTERS);
			LAi_SetImmortal(npchar, false);
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			DialogExit();
		break;

		case "exit_fight_grotto":
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			//LAi_group_MoveCharacter(NPChar, LAI_GROUP_MONSTERS);;
			for (i = 1; i <= MOD_SKILL_ENEMY_RATE; i++)
			{
				sld = CharacterFromID("UI_pirate"+i)
				LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
			}
			LAi_SetImmortal(npchar, false);
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			DialogExit();
		break;
	}
}

