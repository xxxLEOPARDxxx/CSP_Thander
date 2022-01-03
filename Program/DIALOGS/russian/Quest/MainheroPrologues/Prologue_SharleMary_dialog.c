void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	ref _location;
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.id == "SharleMary")
			{
				chrDisableReloadToLocation = false;
				LAi_SetPlayerType(PChar);
				LAi_SetImmortal(NPChar, true);
				dialog.text = GetSexPhrase("Мой капитан! Ты весь в крови!","Любовь моя! Ты вся в крови!");
				link.l1 = "Пустяки. "+GetSexPhrase("приложился","приложилась")+" об камни на берегу. Тебя не задели? Эти дьяволы отравляют своё оружие.";
				link.l1.go = "2";
			}

			if (npchar.id == "SMPirate1")
			{
				chrDisableReloadToLocation = false;
				LAi_SetPlayerType(PChar);
				LAi_SetImmortal(NPChar, true);
				dialog.text = "Смотрите парни, какая сладкая парочка забрела на наш пляж! Море потрепало нашу лоханку и смыло за борт треть экипажа, а тут такой подарок! Нет худа без добра, как говорил наш капеллан, упокой Господь его грешную душу!";
				link.l1 = "Мы потерпели крушение недалеко от этих берегов и просим вас, как христиан, помочь нам добраться до любой дружественной колони, где я, клянусь честью, отблагодарю вас в полной мере.";
				link.l1.go = "SMPirate1_2";
				if (CheckAttribute(pchar, "SharleMary.LowerIsDead"))
				{
					dialog.text = "Смотрите парни, кто забрел на наш пляж! Море потрепало нашу лоханку и смыло за борт треть экипажа, а тут такой подарок! Нет худа без добра, как говорил наш капеллан, упокой Господь его грешную душу!";
					link.l1 = "Я потерпел крушение недалеко от этих берегов и прошу вас, как христиан, помочь мне добраться до любой дружественной колони, где я, клянусь честью, отблагодарю вас в полной мере.";
					link.l1.go = "SMPirate1_3";
				}
			}
			if (npchar.id == "SMCrew1")
			{
				chrDisableReloadToLocation = false;
				LAi_SetPlayerType(PChar);
				LocatorReloadEnterDisable("Shore_ship2", "boat", false);
				bDisableCharacterMenu = false;
				bDisableLandEncounters = false;
				dialog.text = "Проклятье! Знали бы мы, что все так обернется, ни за что не бежали бы с каторги\nСначала этот шторм, а теперь еще вы явились из ниоткуда и убили последнего, кто смыслил в управлении кораблем.";
				link.l1 = "Я тоже разбираюсь в корабельном деле. У меня есть предложение, которое будет выгодно нам всем. Вы берете меня шкипером и мы отчаливаем отсюда.";
				link.l1.go = "SMCrew1_2";
			}
			NextDiag.TempNode = "First time";
		break;

		case "SMCrew1_2":
			dialog.text = "Мы не в том положении, чтобы отказываться. Прошу на борт.";
			link.l1 = "Отлично!";
			sld = characterFromID("SharleMary");
			DeleteAttribute(sld, "cirassId");
			LAi_SetHP(sld, 100.0, 100.0);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "boat", "none", "", "", "", 10);
			link.l1.go = "Exit";
		break;
		case "SMPirate1_2":
			dialog.text = "...";
			link.l1 = GetSexPhrase("Мэри: ","Шарль: ")+"Да, наши друзья заплатят вам за неудобства и вам зачтётся богоугодное дело, помощь нуждающимся.";
			link.l1.go = "SMPirate1_3";
		break;
		case "SMPirate1_3":
			dialog.text = "Смотри, как поют, прям как на мессе, заслушаешься. Парни, вяжи лягушатника, девку ко мне в каюту.";
			link.l1 = "...";
			if (CheckAttribute(pchar, "SharleMary.LowerIsDead"))
			{
				dialog.text = "Смотри, как поет, прям как на мессе, заслушаешься. "+GetSexPhrase("Парни, вяжи лягушатника!","Парни, вяжите девку, потом приведете ко мне в каюту.");
				link.l1 = "...";
				link.l1.go = "SMPirate1_3";
			}
			link.l1.go = "Exit_fight_pirates";
		break;

		case "2":
			dialog.text = "Нет, я в порядке.";
			link.l1 = "Почему ты "+GetSexPhrase("пошла одна?","пошел один?");
			link.l1.go = "3";
		break;

		case "3":
			dialog.text = "Я "+GetSexPhrase("думала","думал")+" встретить наших друзей мискито, а тут обитают каннибалы. Нужно скорей выбираться отсюда. Пойдём на пляж, возможно, ещё кого-то прибило к берегу. И нужно что-то сделать с твоей раной на голове. Выглядит скверно.";
			link.l1 = "Пойдём.";
			link.l1.go = "Exit_follow";
		break;



		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Exit_fight_pirates":
			NextDiag.CurrentNode = "5";
			AddDialogExitQuest("MainHeroFightModeOn");

			SharleMary_FightPirates();

			//LAi_group_Attack(NPChar, Pchar);
			//LAi_SetWarriorType(NPChar);
			//LAi_SetImmortal(NPChar, false);
			DialogExit();
		break;

		case "Exit_follow":
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.rank = 3;
			SetSPECIAL(sld, 6, 6, 8, 5, 8, 8, 8);
			SetCharacterPerk(sld, "Energaiser"); // скрытый перк дает 1.5 к приросту энергии, дается ГГ и боссам уровней
			sld.quest.OfficerPrice = sti(pchar.rank)*500;
			sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
			sld.loyality = MAX_LOYALITY;
			sld.quest.meeting = true;
			Npchar.CanTakeMushket = true;
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.HoldEquip = true;
			sld.HalfImmortal = true;  // Контузия
			LAi_SetImmortal(NPChar, false);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			DialogExit();
		break;
	}
}
