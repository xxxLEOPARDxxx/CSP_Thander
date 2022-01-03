
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
			if(CheckAttribute(PChar, "Arena.Mode"))
			{
				if(PChar.Arena.Mode == "Duel")
				{
					if(sti(PChar.Arena.Duel.BiletCount) == 1)
					{
						dialog.text = "А-а, это вы, капитан " + PChar.name + " " + PChar.lastname + "? Проходите!";
						link.l1 = "...";
						link.l1.go = "exit";
						AddDialogExitQuestFunction("PrepareArenaDuelEnd");
						NextDiag.TempNode = "Second Time";
						break;
					}
				}

				if(PChar.Arena.Mode == "Etaps")
				{
					if(sti(PChar.Arena.Etaps.BiletCount) == 1)
					{
						dialog.text = "А-а, это вы, капитан " + PChar.name + " " + PChar.lastname + "? Решили сразиться со нечистию всякою?";
						link.l1 = "Угу... Давай, пропускай.";
						link.l1.go = "exit";
						AddDialogExitQuestFunction("PrepareArenaEtapsEnd");
						NextDiag.TempNode = "Second Time";
						break;
					}
				}

				if(PChar.Arena.Mode == "Tournament")
				{
					if(sti(PChar.Arena.Tournament.BiletCount) == 1)
					{
						dialog.text = "А-а, это вы, капитан " + PChar.name + " " + PChar.lastname + "? Все участники турнира уже в сборе! Схватки ожидаются очень жестокими. Удачи вам, капитан...";
						link.l1 = "Спасибо...";
						link.l1.go = "exit";
						AddDialogExitQuestFunction("PrepareArenaTournamentEnd");
						NextDiag.TempNode = "Second Time";
						break;
					}
				}

				if(PChar.Arena.Mode == "Odds")
				{
					if(sti(PChar.Arena.Odds.BiletCount) == 1)
					{
						dialog.text = "А-а, это вы, капитан " + PChar.name + " " + PChar.lastname + "? Слыхал, вы заключили пари и решили попытать счастья, поставив на одного из дуэлянтов? Желаю вам удачи!";
						link.l1 = "Спасибо...";
						link.l1.go = "exit";
						AddDialogExitQuestFunction("PrepareArenaOddsEnd");
						NextDiag.TempNode = "Second Time";
						break;
					}
				}

				if(PChar.Arena.Mode.NotOdd == true)
				{
					dialog.text = "Стоп! Ты кто такой? Показывай билет, иначе я позову стражу!";

					if(GetCharacterItem(PChar, "ArenaBilet"))
					{
						link.l1 = "Вот мой билет. А теперь открывай!";
						link.l1.go = "Bilet_Action";
					}
					link.l2 = "Э-э-э... Я попозже подойду.";
					link.l2.go = "exit";
					AddDialogExitQuestFunction("PrepareArenaOddsBilet");
				}
			}

			NextDiag.TempNode = "First time";
		break;

		case "Bilet_Action":
			TakeItemFromCharacter(PChar, "ArenaBilet");
			dialog.text = "Э-э.. Так-так.. Теперь вы можете пройти.";
			link.l1 = "Так-то лучше.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("PrepareArenaOddsEnd");
			NextDiag.TempNode = "Second Time";
		break;


		case "Second Time":
			dialog.text = "Не желаете ли приобрести эликсиры и еду? В бою очень даже пригодятся!";
			link.l1 = "Да.";
			link.l1.go = "Trade_exit";
			link.l2 = "Нет.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Second Time";
		break;

		case "Trade_exit":
            		if(CheckNPCQuestDate(NPChar, "Item_date"))
			{
				SetNPCQuestDate(NPChar, "Item_date");
				ArenaBileterGiveItems(NPChar);
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar);
		break;


		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "":
			dialog.text = NPCStringReactionRepeat("",
				"",
				"",
                "", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("",
				"",
                "",
				"", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;

		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "_1";
		break;
		case "_1":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "_2";
		break;
		case "_2":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "_3";
		break;
		case "_4":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "_5";
		break;
	}
}
