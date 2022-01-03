void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;

	bool hungry = true;
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Брат в нежизни, что тебе понадобилось у входа в церковь?";
            link.l1 = "А ты еще откуда взялся?";
            link.l1.go = "HS_1";
			link.l2 = "Это не твое дело. Не мешай мне.";
            link.l2.go = "HS_2";
			link.l3 = "Меня попросили отнести пожертвование.";
            link.l3.go = "HS_2";
		break;

		case "HS_1":
			dialog.text = "Мы уже давно приглядываем за тобой. И то, что мы видим нам не очень-то нравится.";
			link.l1 = "И что же вы такого увидели?";
			link.l1.go = "HS_2";
		break;
		case "HS_2":
			dialog.text = "Ты служишь смертным! Выполняешь их мерзкие прихоти, при этом даже ничего не требуешь взамен! Нам невыносимо наблюдать такое. Поручение хозяйки борделя было последней каплей\nТы думаешь, что таким образом сам сможешь приблизиться к их нормальной жизни? Переродиться? Не бывать этому! Существует один ритуал, но своими поступками ты лишь сделал себя недостойным его\nЧто до жалких смертных, сейчас ты увидишь, как этот город сгорит вместе с ними.";
			link.l1 = "Я не позволю этому случиться.";
			link.l1.go = "HS_fight";
		break;

		case "HS_fight":
			DialogExit();
			Lai_SetPlayerType(pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
			//LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			LAi_SetImmortal(NPChar, false);
			//LocatorReloadEnterDisable(pchar.HellSpawnLocation, "reload7_back", false);

			string cnd;
			for (int i = 1; i<15; i++)
			{
				cnd = "l" + i;
				sld = characterFromID("HellSpawn"+i);
				LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
				PChar.quest.HellSpawnFinish.win_condition.(cnd) = "NPC_Death";
				PChar.quest.HellSpawnFinish.win_condition.(cnd).character = sld.id;
			}
			pchar.quest.HellSpawnFinish.function = "HellSpawnFinish";
		break;

		case "Ritual":
			dialog.text = "Зачем ты пришел сюда? Хочешь прервать наш ритуал перерождения?";
			link.l1 = "Напротив. Я хочу к вам присоединиться.";
			link.l1.go = "Ritual_1";
			link.l2 = "Да. Такие как вы не заслуживают дара жизни.";
			link.l2.go = "Ritual_fight";
		break;

		case "Ritual_1":
			dialog.text = "Многие ждут своей очереди сотни лет. Ты еще не достоин.";
			link.l1 = "Сейчас увидим, кто здесь чего достоин.";
			link.l1.go = "Ritual_fight";
		break;

		case "Ritual_fight":
			DialogExit();
			Lai_SetPlayerType(pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
			LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			LAi_SetImmortal(NPChar, false);
			ref RitualLocLoad = &locations[reload_location_index];
			cnd;
			for (i = 1; i<sti(pchar.Hellspawn.num); i++)
			{
				cnd = "l" + i;
				sld = characterFromID("HellSpawnR"+i);
				LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
				PChar.quest.HellSpawnRitualFinish.win_condition.(cnd) = "NPC_Death";
				PChar.quest.HellSpawnRitualFinish.win_condition.(cnd).character = sld.id;
			}
			pchar.quest.HellSpawnRitualFinish.function = "HellSpawnRitualFinish";

		break;
	}
}
