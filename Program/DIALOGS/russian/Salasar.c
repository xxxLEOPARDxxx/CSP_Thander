
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
		case "First":
			dialog.text = "Не побоял"+ GetSexPhrase("ся","ась") +" сюда заявиться в такое время? Моё уважение тебе.";
			link.l1 = "Так это о тебе рассказывали постояльцы таверн?";
			link.l1.go = "Meeting";
			if (pchar.sex != "woman") LAi_CharacterPlaySoundAtOnce(NPChar, "Salazar_1_man");
			else LAi_CharacterPlaySoundAtOnce(NPChar, "Salazar_1_woman");
		break;

		case "Meeting":
			dialog.text = "О ком же ещё? Перед тобой когда-то легендарный Армандо Салазар, Эль Матадор дель Мар! Правда, обывателям я больше известен под прозвищем ''Морской Мясник''...";
			link.l1 = "Да, я слых"+ GetSexPhrase("ал","ала") +" о тебе. Офицер испанского королевсково флота, командовавший ''Немой Марией''. Известен как непримиримый охотник на пиратов.";
			link.l1.go = "Meeting_2";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Salazar_2");
		break;

		case "Meeting_2":
			dialog.text = "Пожалуй, хватит разговоров. Я слишком долго пробыл на этом свете. Убей меня или умри!";
			link.l1 = "И почему всё сводится к банальной драке...";
			link.l1.go = "exit";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Salazar_3");
		break;

		case "Exit":
			NextDiag.CurrentNode = "Meeting_2";
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "ReefAssholes");
			LAi_group_SetRelation("ReefAssholes", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_Attack(npchar, Pchar);
			LAi_group_SetLookRadius("ReefAssholes", 1000.0);
			SetNoRun(npchar); //инвалид
		break;

		case "Last":
			dialog.text = "Ты меня впечатлил"+ GetSexPhrase("!","а!") +" Никто из тех, кто прежде отваживался прийти сюда, не могли одолеть нас и оставались здесь навсегда.";
			link.l1 = "Это было очень тяжело. Ты и твои ребята заставили меня облиться семью потами. Да и чувствую я себя неважно.";
			link.l1.go = "Last_2";
			if (pchar.sex != "woman") LAi_CharacterPlaySoundAtOnce(NPChar, "Salazar_4_man");
			else LAi_CharacterPlaySoundAtOnce(NPChar, "Salazar_4_woman");
		break;

		case "Last_2":
			dialog.text = "Моё проклятие было в том, что я останусь в этом мире в таком состоянии до тех пор, пока меня не одолеют в бою. Теперь оно сломлено и я могу наконец уйти на вечный покой. Что же касается твоего здоровья - это всё проклятие. С моей окончательной смертью - тебе станет куда лучше.";
			link.l1 = "Обнадёживающе. И что теперь?";
			link.l1.go = "Last_3";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Salazar_5");
		break;

		case "Last_3":
			dialog.text = "Не хочу оставлять тебя без подарка. Всё, что ты найдёшь здесь, на этом кладбище - отныне тебе доступно и оно - твоё. А теперь - прощай!";
			link.l1 = "Покойся с миром, Мясник.";
			link.l1.go = "Last_exit";
			LAi_CharacterPlaySoundAtOnce(NPChar, "Salazar_6");
		break;

		case "Last_exit":
			UnlockAchievement("AchSalazar", 3);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			npchar.LifeDay = 0;
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			AddCharacterHealth(pchar, 30);
			chrDisableReloadToLocation = false; //пока Салазар жив - хер, а не выход
			ref sld;
			for(i = 0; i < 10; i++)
			{
				sld = CharacterFromID("SalSupp"+i);
				LAi_KillCharacter(sld);
				sld = CharacterFromID("SalSupps"+i);
				LAi_KillCharacter(sld);
			}
			DeleteAttribute(loadedLocation,"box1.items");
			loadedLocation.box1.items.cirass5 = 1;
			loadedLocation.box1.items.pistol8 = 1;
			loadedLocation.box1.items.gold = 1000000;
			loadedLocation.box1.items.blade38 = 1;
			loadedLocation.box1.items.suit_3 = 1;
			loadedLocation.box1.items.chest = 5;
			loadedLocation.box1.items.icollection = 5;
			if (sti(pchar.rank) >= 30) loadedLocation.box1.items.Ship_Print_1 = 1;
			else
			{
				if (sti(pchar.rank) >= 25) loadedLocation.box1.items.Ship_Print_2 = 1;
				else
				{
					loadedLocation.box1.items.Ship_Print_3 = 1;
				}
			}
			LAi_LocationFightDisable(loadedLocation, false);
		break;
	}
}
