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
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
			if (Pchar.Location == Pchar.location.from_sea)
			{
				dialog.text = "Приш"+ GetSexPhrase("ел","ла") +" наконец. А я уж думал, испугаешься. За тобой никого нет? Дело-то серьезное.";
				link.l1 = "Никого за мной нет. Да и бояться мне нечего, я же не овец ворую, а с честными контрабандистами сделку провожу. Или нет?";
				link.l1.go = "pirateStartQuest_Smuggler3_1";
			}
			else
			{
				dialog.text = "Приш"+ GetSexPhrase("ел","ла") +" наконец. Только я твоего корабля не вижу, "+ GetSexPhrase("приятель","подруга") +". Куда ты собрал"+ GetSexPhrase("ся","ась") +" товар грузить?";
				link.l1 = "Верно, пришвартовал"+ GetSexPhrase("ся","ась") +" не в той бухте... Сейчас, я мигом!";
				link.l1.go = "exit";

			}
		break;
		case "pirateStartQuest_Smuggler3_1":
			dialog.text = "Хех, хорошо сказано. Ну, а теперь выкладывай, сколько тебе заплатил " + pchar.questTemp.pirateStartQuest.Name + ", чтоб ты его рабов наш"+ GetSexPhrase("ел","ла") +".";
			link.l1 = "Ну, я же предупреждал"+ GetSexPhrase("","а") +", что мне некогда играть в ваши игры. Или ты продаешь мне рабов, или я буду искать их в другом месте.";
			link.l1.go = "pirateStartQuest_Smuggler3_2";
		break;
		case "pirateStartQuest_Smuggler3_2":
			dialog.text = "Рабы вон в той клетке, смотри. Свеженькие, полные сил. Устраивают?";
			if (sti(pchar.money) >= 15000)
			{
				link.l1 = "Устраивают. Вот половина суммы, остальную после погрузки получите.";
				link.l1.go = "pirateStartQuest_Smuggler3_3";
			}
			link.l2 = "Не торопись приятель, сдается мне, что этот товар со шхуны 'Сентблу'. Живо говори, кто информатор.";
			link.l2.go = "pirateStartQuest_Smuggler3_5";
			GiveItem2Character(npchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_pirateStartQuest");
			npchar.SaveItemsForDead  = true;
			npchar.DontClearDead = true;
			AddQuestRecord("pSQ", "5");
			AddQuestUserData("pSQ", "sSex", GetSexPhrase("ел","ла"));
			AddQuestUserData("pSQ", "sCity2", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City2 + "Gen"));
		break;
		case "pirateStartQuest_Smuggler3_3":
			dialog.text = "Рабы загружены. Давай расчет, и разбежимся, пока нас патруль не накрыл.";
			link.l1 = "Не торопись, приятель, сдается мне, что этот товар со шхуны 'Сентблу'. Хочешь получить вторую половину - говори, кто информатор.";
			link.l1.go = "pirateStartQuest_Smuggler3_5";
			AddMoneyToCharacter(pchar, -15000);
			AddMoneyToCharacter(npchar, 15000);
			AddCharacterGoods(pchar, GOOD_SLAVES, 100);
			AddQuestUserData("pSQ", "sText", "О рабах моему работодателю знать не обязательно, не напрасно же я выложил"+ GetSexPhrase("","а") +" за них 15 000 пиастров.");
		break;
		case "pirateStartQuest_Smuggler3_5":
			dialog.text = "Вот черт! Теперь все понятно. Придется вытрясти из тебя деньги вместе с кишками и твоей поганой душонкой!";
			link.l1 = "Видать, не такие уж вы серьезные. Но, надеюсь, хоть не глупые, поэтому предлагаю мирный вариант - ты говоришь имя информатора, который сдал тебе шхуну и покупателя, тогда сможете уйти отсюда живыми.";
			link.l1.go = "pirateStartQuest_Smuggler3_6";
		break;
		case "pirateStartQuest_Smuggler3_6":
			dialog.text = "Вот и хорошо, что все так вышло. Место здесь укромное, о лучшей могилке тебе и не мечталось, поди. А " + pchar.questTemp.pirateStartQuest.Name + " пусть подыскивает соглядатаев попроворнее.";
			link.l1 = "Да, придется, видать, пощекотать тебе печенку...";
			link.l1.go = "pirateStartQuest_Smuggler3_7";
		break;
		case "pirateStartQuest_Smuggler3_7":
			chrDisableReloadToLocation = true;
			RemoveGeometryFromLocation(pchar.questTemp.pirateStartQuest.Shore, "smg");

			for(i=1; i<=3; i++)
			{
				sld = CharacterFromID("psq2_" +i);
				LAi_SetImmortal(sld, false);
			}

			LAi_group_SetRelation("pirateStartQuest_Smuggler_group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("pirateStartQuest_Smuggler_group", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("pirateStartQuest_Smuggler_group", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");

			pchar.quest.pirateStartQuest_Lether_fc.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirateStartQuest_Lether_fc.win_condition.l1.location = pchar.location;
			pchar.quest.pirateStartQuest_Lether_fc.function = "pirateStartQuest_Lether_fc";
		break;
	}
}





