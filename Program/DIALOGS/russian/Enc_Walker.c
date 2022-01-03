// диалог из ПКМ
#include "DIALOGS\russian\Enc_Walker.h"
#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;
	string NPC_Meeting, TempInfoCharacterID_1, TempInfoCharacterID_2;
	int Sum;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

    ProcessCommonDialogRumors(NPChar, Link, Diag);//homo 16/06/06

	string iDay, iMonth;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;


	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча

		case "First time":
			if (NPChar.sex != "man")
			{
                dialog.text = RandPhraseSimple("Мой муж запрещает говорить с "+ GetSexPhrase("незнакомцами","посторонними") +"!",
                         "Мне не о чем с вами говорить.");
				Link.l1 = "Ну и не нужно";
				Link.l1.go = "exit";
                break;
			}
			link.l10 = LinkRandPhrase ("Расскажи мне лучше, что за байки в ходу в здешней таверне?",
									"Лучше скажи мне, новенького в этих краях?",
									"Расскажи-ка мне лучше, приятель, как течет жизнь на суше?");
			link.l10.go = "rumours_citizen"; //повесил на горожанина, если нужны отедельные слухи, то пишем соответствующую реализацию
			if (npchar.quest.Meeting != LastSpeakDate() || bBettaTestMode)
		    {
				npchar.quest.last_theme = Rand(17);
				npchar.quest.Meeting = LastSpeakDate();
			}
			switch (sti(npchar.quest.last_theme))
			{
				case 0:
					dialog.text = DLG_TEXT_BASE[0];
					Link.l1 = DLG_TEXT_BASE[1];
					Link.l1.go = "skeletons";
					Link.l2 = DLG_TEXT_BASE[2];
					Link.l2.go = "exit";
				break;

				case 1:
					dialog.text = DLG_TEXT_BASE[3];
					Link.l1 = DLG_TEXT_BASE[4];
					Link.l1.go = "police";
					Link.l2 = DLG_TEXT_BASE[5];
					Link.l2.go = "exit";
				break;

				case 2:
					dialog.text = DLG_TEXT_BASE[6];
					Link.l1 = DLG_TEXT_BASE[7];
					Link.l1.go = "health";
					Link.l2 = DLG_TEXT_BASE[8];
					Link.l2.go = "exit";
				break;

				case 3:
					dialog.text = DLG_TEXT_BASE[9];
					Link.l1 = DLG_TEXT_BASE[10];
					Link.l1.go = "tavern";
					Link.l2 = DLG_TEXT_BASE[11];
					Link.l2.go = "exit";
				break;

				case 4:
					dialog.text = DLG_TEXT_BASE[12];
					Link.l1 = DLG_TEXT_BASE[13];
					Link.l1.go = "officer";
					Link.l2 = DLG_TEXT_BASE[14];
					Link.l2.go = "exit";
				break;

				case 5:
					dialog.text = DLG_TEXT_BASE[15];
					Link.l1 = DLG_TEXT_BASE[16];
					Link.l1.go = "shipyard";
					Link.l2 = DLG_TEXT_BASE[17];
					Link.l2.go = "exit";
				break;

				case 6:
					dialog.text = DLG_TEXT_BASE[18];
					Link.l1 = DLG_TEXT_BASE[19];
					Link.l1.go = "torg";
					Link.l2 = DLG_TEXT_BASE[20];
					Link.l2.go = "exit_once_more";
				break;

				case 7:
					dialog.text = DLG_TEXT_BASE[21];
					Link.l1 = DLG_TEXT_BASE[22];
					Link.l1.go = "healing";
					Link.l2 = DLG_TEXT_BASE[23];
					Link.l2.go = "exit_once_more_portion";
				break;

				case 8:
					dialog.text = DLG_TEXT_BASE[24];
					Link.l1 = DLG_TEXT_BASE[25];
					Link.l1.go = "reput";
					Link.l2 = DLG_TEXT_BASE[26];
					Link.l2.go = "exit_out";
				break;

				case 9:
					if (1 < Rand(20))
					{
						switch(Rand(1))
						{
							case 0:
								dialog.text = DLG_TEXT_BASE[27];
								Link.l1 = DLG_TEXT_BASE[28];
								Link.l1.go = "beg";
								Link.l2 = DLG_TEXT_BASE[29];
								Link.l2.go = "exit_out";
							break;

							case 1:
								dialog.text = DLG_TEXT_BASE[30];
								Link.l1 = DLG_TEXT_BASE[31];
								Link.l1.go = "beg";
								Link.l2 = DLG_TEXT_BASE[32];
								Link.l2.go = "exit_out";
							break;
						}
					}
					else
					{
						dialog.text = DLG_TEXT_BASE[33];
						Link.l1 = DLG_TEXT_BASE[34];
						Link.l1.go = "skill";
						Link.l2 = DLG_TEXT_BASE[35];
						Link.l2.go = "exit_out";
					}
				break;

				case 10:
					dialog.text = DLG_TEXT_BASE[36];
					Link.l1 = DLG_TEXT_BASE[37];
					Link.l1.go = "enlist_me";
					Link.l2 = DLG_TEXT_BASE[38];
					Link.l2.go = "exit_out";
				break;

				case 11:
					dialog.text = DLG_TEXT_BASE[39];
					Link.l1 = DLG_TEXT_BASE[40];
					Link.l1.go = "masters";
					Link.l2 = DLG_TEXT_BASE[41];
					Link.l2.go = "exit";
				break;
				// дубли
				case 12:
					dialog.text = DLG_TEXT_BASE[39];
					Link.l1 = DLG_TEXT_BASE[40];
					Link.l1.go = "masters";
					Link.l2 = DLG_TEXT_BASE[41];
					Link.l2.go = "exit";
				break;

				case 13:
					dialog.text = DLG_TEXT_BASE[39];
					Link.l1 = DLG_TEXT_BASE[40];
					Link.l1.go = "masters";
					Link.l2 = DLG_TEXT_BASE[41];
					Link.l2.go = "exit";
				break;

				case 14:
					dialog.text = DLG_TEXT_BASE[18];
					Link.l1 = DLG_TEXT_BASE[19];
					Link.l1.go = "torg";
					Link.l2 = DLG_TEXT_BASE[20];
					Link.l2.go = "exit_once_more";
				break;

				case 15:
					dialog.text = DLG_TEXT_BASE[15];
					Link.l1 = DLG_TEXT_BASE[16];
					Link.l1.go = "shipyard";
					Link.l2 = DLG_TEXT_BASE[17];
					Link.l2.go = "exit";
				break;

				case 16:
					dialog.text = DLG_TEXT_BASE[0];
					Link.l1 = DLG_TEXT_BASE[1];
					Link.l1.go = "skeletons";
					Link.l2 = DLG_TEXT_BASE[2];
					Link.l2.go = "exit";
				break;

				case 17:
					dialog.text = DLG_TEXT_BASE[3];
					Link.l1 = DLG_TEXT_BASE[4];
					Link.l1.go = "police";
					Link.l2 = DLG_TEXT_BASE[5];
					Link.l2.go = "exit";
				break;
			}
		break;

		case "skeletons":
			dialog.text = DLG_TEXT_BASE[42];
			Link.l1 = DLG_TEXT_BASE[43];
			Link.l1.go = "exit";
		break;

		case "police":
			dialog.text = DLG_TEXT_BASE[44];
			Link.l1 = DLG_TEXT_BASE[45];
			Link.l1.go = "police1";
			Link.l2 = DLG_TEXT_BASE[46];
			Link.l2.go = "exit";
		break;

		case "police1":
			dialog.text = DLG_TEXT_BASE[47];
			Link.l1 = DLG_TEXT_BASE[48];
			Link.l1.go = "exit";
		break;

		case "health":
			dialog.text = DLG_TEXT_BASE[49];
			Link.l1 = DLG_TEXT_BASE[50];
			Link.l1.go = "health1";
			Link.l2 = DLG_TEXT_BASE[51];
			Link.l2.go = "exit";
		break;

		case "health1":
			dialog.text = DLG_TEXT_BASE[52];
			Link.l1 = DLG_TEXT_BASE[53];
			Link.l1.go = "exit";
		break;

		case "tavern":
			dialog.text = DLG_TEXT_BASE[54];
			Link.l1 = DLG_TEXT_BASE[55];
			Link.l1.go = "exit";
		break;

		case "officer":
			dialog.text = DLG_TEXT_BASE[56];
			Link.l1 = DLG_TEXT_BASE[57];
			Link.l1.go = "exit";
		break;

		case "shipyard":
			dialog.text = DLG_TEXT_BASE[58];
			Link.l1 = DLG_TEXT_BASE[59];
			Link.l1.go = "exit";
		break;

		case "masters":
			dialog.text = DLG_TEXT_BASE[60];
			Link.l1 = DLG_TEXT_BASE[61];
			Link.l1.go = "exit";
		break;

		case "torg":
            if (Pchar.questTemp.CapBloodLine == true )//homo закрыл баг по линейке.
            {
                dialog.Text = "Постой, а ты часом не раб с плантации?";
                Link.l1 = "Увы, я уже ухожу, " + NPChar.name + ". До встречи.";
				Link.l1.go = "exit";
				break;
            }
			if (CheckNPCQuestDate(npchar, "Torg_date"))
			{
                SetNPCQuestDate(npchar, "Torg_date");
				GiveItemToTrader(npchar);
			}

			Diag.CurrentNode = "once_more";
			DialogExit();

			LaunchItemsTrade(NPChar);
		break;

		case "healing":
			AddMoneytoCharacter(Pchar, -200);
			LAi_SetCurHP(pchar, LAi_GetCharacterMaxHP(pchar));
			Diag.CurrentNode = "once_more_portion";
			DialogExit();
		break;

		case "healing1":
			LAi_SetCurHP(pchar, LAi_GetCharacterMaxHP(pchar));
			Diag.CurrentNode = "thanx";
			DialogExit();
		break;

		case "reput":
			dialog.text = DLG_TEXT_BASE[62];
			Link.l1 = DLG_TEXT_BASE[63];
			Link.l1.go = "exit_out";
			Link.l2 = DLG_TEXT_BASE[64];
			Link.l2.go = "exit1";
		break;

		case "beg":
			AddMoneyToCharacter(pchar, -200);
			switch (Rand(2))
			{
					case 0:
						dialog.text = DLG_TEXT_BASE[65];
						Link.l1 = DLG_TEXT_BASE[66];
						Link.l1.go = "healing1";
					break;

					case 1:
						dialog.text = DLG_TEXT_BASE[67];
						Link.l1 = DLG_TEXT_BASE[68];
						Link.l1.go = "item";
					break;

					case 2:
						dialog.text = DLG_TEXT_BASE[69];
						Link.l1 = DLG_TEXT_BASE[70];
						Link.l1.go = "exit_than";
					break;
			}
		break;

		case "item":
			switch (Rand(10))
			{
				case 0:
					GiveItem2Character(pchar, "indian1");
				break;

				case 2:
					GiveItem2Character(pchar, "indian2");
				break;

				case 3:
					GiveItem2Character(pchar, "indian3");
				break;

				case 4:
					GiveItem2Character(pchar, "indian4");
				break;

				case 5:
					GiveItem2Character(pchar, "indian5");
				break;

				case 6:
					GiveItem2Character(pchar, "indian6");
				break;

				case 7:
					GiveItem2Character(pchar, "indian7");
				break;

				case 8:
					GiveItem2Character(pchar, "indian8");
				break;

				case 9:
					GiveItem2Character(pchar, "indian9");
				break;

				case 10:
					GiveItem2Character(pchar, "indian10");
				break;
			}
			Diag.CurrentNode = "thanx";
			DialogExit();
		break;

		case "enlist_me":
			dialog.text = DLG_TEXT_BASE[71];
			Link.l2 = DLG_TEXT_BASE[73];
			Link.l2.go = "exit_out";
		break;

		case "skill":

			switch (Rand(7))
			{
				case 0:
					dialog.text = DLG_TEXT_BASE[74];
					if(makeint(PChar.skill.Fencing)>= SKILL_MAX)
					{
						Link.l1 = DLG_TEXT_BASE[75];
						Link.l1.go = "exit_Fencing";
					}
					else
					{
						Link.l1 = DLG_TEXT_BASE[78];
						Link.l1.go = "Fencing";
					}
					if(makeint(PChar.skill.Defence)>= SKILL_MAX)
					{
						Link.l1 = DLG_TEXT_BASE[77];
						Link.l1.go = "exit_out";
					}
					else
					{
						Link.l2 = DLG_TEXT_BASE[76];
						Link.l2.go = "Defence";
					}
					Link.l3 = DLG_TEXT_BASE[79];
					Link.l3.go = "exit_Fencing";
				break;

				case 1:
					dialog.text = DLG_TEXT_BASE[80];
					if(makeint(PChar.skill.Leadership)>= SKILL_MAX)
					{
						Link.l1 = DLG_TEXT_BASE[81];
						Link.l1.go = "exit_out";
					}
					else
					{
						Link.l1 = DLG_TEXT_BASE[82];
						Link.l1.go = "Leadership";
					}
					Link.l2 = DLG_TEXT_BASE[83];
					Link.l2.go = "exit_Leadership";
				break;

				case 2:
					dialog.text = DLG_TEXT_BASE[84];
					if(makeint(PChar.skill.Sailing)>= SKILL_MAX)
					{
						Link.l1 = DLG_TEXT_BASE[85];
						Link.l1.go = "exit_out";
					}
					else
					{
						Link.l1 = DLG_TEXT_BASE[86];
						Link.l1.go = "Sailing";
					}
					Link.l2 = DLG_TEXT_BASE[87];
					Link.l2.go = "exit_Sailing";
				break;

				case 3:
					dialog.text = DLG_TEXT_BASE[88];
					if(makeint(PChar.skill.Accuracy)>= SKILL_MAX)
					{
						Link.l1 = DLG_TEXT_BASE[89];
						Link.l1.go = "exit_out";
					}
					else
					{
						Link.l1 = DLG_TEXT_BASE[90];
						Link.l1.go = "Accuracy";
					}
					Link.l2 = DLG_TEXT_BASE[91];
					Link.l2.go = "exit_Accuracy";
				break;

				case 4:
					dialog.text = DLG_TEXT_BASE[92];
					if(makeint(PChar.skill.Cannons)>= SKILL_MAX)
					{
						Link.l1 = DLG_TEXT_BASE[93];
						Link.l1.go = "exit_out";
					}
					else
					{
						Link.l1 = DLG_TEXT_BASE[94];
						Link.l1.go = "Cannons";

					}
					Link.l2 = DLG_TEXT_BASE[95];
					Link.l2.go = "exit_Cannons";
				break;

				case 5:
					dialog.text = DLG_TEXT_BASE[96];
					if(makeint(PChar.skill.Grappling)>= SKILL_MAX)
					{
						Link.l1 = DLG_TEXT_BASE[97];
						Link.l1.go = "exit_out";
					}
					else
					{
						Link.l1 = DLG_TEXT_BASE[98];
						Link.l1.go = "Grappling";
					}
					Link.l2 = DLG_TEXT_BASE[99];
					Link.l2.go = "exit_Grappling";
				break;

				case 6:
					dialog.text = DLG_TEXT_BASE[100];
					if(makeint(PChar.skill.Repair)>= SKILL_MAX)
					{
						Link.l1 = DLG_TEXT_BASE[101];
						Link.l1.go = "exit_out";
					}
					else
					{
						Link.l1 = DLG_TEXT_BASE[102];
						Link.l1.go = "Repair";
					}
					Link.l2 = DLG_TEXT_BASE[103];
					Link.l2.go = "exit_Repair";
				break;

				case 7:
					dialog.text = DLG_TEXT_BASE[104];
					if(makeint(PChar.skill.Commerce)>=SKILL_MAX)
					{
						Link.l1 = DLG_TEXT_BASE[105];
						Link.l1.go = "exit_out";
					}
					else
					{
						Link.l1 = DLG_TEXT_BASE[106];
						Link.l1.go = "Commerce";
					}
					Link.l2 = DLG_TEXT_BASE[107];
					Link.l2.go = "exit_Commerce";
				break;
			}
		break;

		case "Fencing":
			Sum = (sti(Pchar.skill.Fencing) + 1) * 10000;
			dialog.text = DLG_TEXT_BASE[108] + Sum + DLG_TEXT_BASE[109];
			if(makeint(Pchar.money) < Sum)
			{
				Link.l1 = DLG_TEXT_BASE[110];
				Link.l1.go = "exit_Fencing";
			}
			else
			{
				Link.l1 = DLG_TEXT_BASE[111];
				Link.l1.go = "Fencing1";
				Link.l2 = DLG_TEXT_BASE[112];
				Link.l2.go = "exit_Fencing";
			}
		break;

		case "Fencing2":
			Sum = (sti(Pchar.skill.Fencing) + 1) * 10000;
			dialog.text = DLG_TEXT_BASE[113] + Sum + DLG_TEXT_BASE[114];
			if(makeint(Pchar.money) < Sum)
			{
				Link.l1 = DLG_TEXT_BASE[115];
				Link.l1.go = "exit_Fencing";
			}
			else
			{
				Link.l1 = DLG_TEXT_BASE[116];
				Link.l1.go = "Fencing1";
				Link.l2 = DLG_TEXT_BASE[117];
				Link.l2.go = "exit_Fencing";
			}
		break;

		case "Fencing1":
			Sum = (sti(Pchar.skill.Fencing) + 1) * 10000;
			AddCharacterSkill(Pchar, SKILL_FENCING, 10);
			AddMoneytoCharacter(Pchar, -Sum);
			Diag.CurrentNode = "get_out";
			DialogExit();
		break;

		case "Defence":
			Sum = (sti(Pchar.skill.Defence) + 1) * 10000;
			dialog.text = DLG_TEXT_BASE[118] + Sum + DLG_TEXT_BASE[119];
			if(makeint(Pchar.money) < Sum)
			{
				Link.l1 = DLG_TEXT_BASE[120];
				Link.l1.go = "exit_Defence";
			}
			else
			{
				Link.l1 = DLG_TEXT_BASE[121];
				Link.l1.go = "Defence1";
				Link.l2 = DLG_TEXT_BASE[122];
				Link.l2.go = "exit_Defence";
			}
		break;

		case "Defence2":
			Sum = (sti(Pchar.skill.Defence) + 1) * 10000;
			dialog.text = DLG_TEXT_BASE[123] + Sum + DLG_TEXT_BASE[124];
			if(makeint(Pchar.money) < Sum)
			{
				Link.l1 = DLG_TEXT_BASE[125];
				Link.l1.go = "exit_Defence";
			}
			else
			{
				Link.l1 = DLG_TEXT_BASE[126];
				Link.l1.go = "Defence1";
				Link.l2 = DLG_TEXT_BASE[127];
				Link.l2.go = "exit_Defence";
			}
		break;

		case "Defence1":
			Sum = (sti(Pchar.skill.Defence) + 1) * 10000;
            AddCharacterSkill(Pchar, SKILL_DEFENCE, 10);
			AddMoneytoCharacter(Pchar, -Sum);
			Diag.CurrentNode = "get_out";
			DialogExit();
		break;

		case "Leadership":
			Sum = (sti(Pchar.skill.Leadership) + 1) * 10000;
			dialog.text = DLG_TEXT_BASE[128] + Sum + DLG_TEXT_BASE[129];
			if(makeint(Pchar.money) < Sum)
			{
				Link.l1 = DLG_TEXT_BASE[130];
				Link.l1.go = "exit_Leadership";
			}
			else
			{
				Link.l1 = DLG_TEXT_BASE[131];
				Link.l1.go = "Leadership1";
				Link.l2 = DLG_TEXT_BASE[132];
				Link.l2.go = "exit_Leadership";
			}
		break;

		case "Leadership2":
			Sum = (sti(Pchar.skill.Leadership) + 1) * 10000;
			dialog.text = DLG_TEXT_BASE[133] + Sum + DLG_TEXT_BASE[134];
			if(makeint(Pchar.money) < Sum)
			{
				Link.l1 = DLG_TEXT_BASE[135];
				Link.l1.go = "exit_Leadership";
			}
			else
			{
				Link.l1 = DLG_TEXT_BASE[136];
				Link.l1.go = "Leadership1";
				Link.l2 = DLG_TEXT_BASE[137];
				Link.l2.go = "exit_Leadership";
			}
		break;

		case "Leadership1":
			Sum = (sti(Pchar.skill.Leadership) + 1) * 10000;
            AddCharacterSkill(Pchar, SKILL_LEADERSHIP, 10);
			AddMoneytoCharacter(Pchar, -Sum);
			Diag.CurrentNode = "get_out";
			DialogExit();
		break;

		case "Sailing":
			Sum = (sti(Pchar.skill.Sailing) + 1) * 10000;
			dialog.text = DLG_TEXT_BASE[138] + Sum + DLG_TEXT_BASE[139];
			if(makeint(Pchar.money) < Sum)
			{
				Link.l1 = DLG_TEXT_BASE[140];
				Link.l1.go = "exit_Sailing";
			}
			else
			{
				Link.l1 = DLG_TEXT_BASE[141];
				Link.l1.go = "Sailing1";
				Link.l2 = DLG_TEXT_BASE[142];
				Link.l2.go = "exit_Sailing";
			}
		break;

		case "Sailing2":
			Sum = (sti(Pchar.skill.Sailing) + 1) * 10000;
			dialog.text = DLG_TEXT_BASE[143] + Sum + DLG_TEXT_BASE[144];
			if(makeint(Pchar.money) < Sum)
			{
				Link.l1 = DLG_TEXT_BASE[145];
				Link.l1.go = "exit_Sailing";
			}
			else
			{
				Link.l1 = DLG_TEXT_BASE[146];
				Link.l1.go = "Sailing1";
				Link.l2 = DLG_TEXT_BASE[147];
				Link.l2.go = "exit_Sailing";
			}
		break;

		case "Sailing1":
			Sum = (sti(Pchar.skill.Sailing) + 1) * 10000;
            AddCharacterSkill(Pchar, SKILL_SAILING, 10);
			AddMoneytoCharacter(Pchar, - Sum);
			Diag.CurrentNode = "get_out";
			DialogExit();
		break;

		case "Accuracy":
			Sum = (sti(Pchar.skill.Accuracy) + 1) * 10000;
			dialog.text = DLG_TEXT_BASE[148] + Sum + DLG_TEXT_BASE[149];
			if(makeint(Pchar.money) < Sum)
			{
				Link.l1 = DLG_TEXT_BASE[150];
				Link.l1.go = "exit_Accuracy";
			}
			else
			{
				Link.l1 = DLG_TEXT_BASE[151];
				Link.l1.go = "Accuracy1";
				Link.l2 = DLG_TEXT_BASE[152];
				Link.l2.go = "exit_Accuracy";
			}
		break;

		case "Accuracy2":
			Sum = (sti(Pchar.skill.Accuracy) + 1) * 10000;
			dialog.text = DLG_TEXT_BASE[153] + Sum + DLG_TEXT_BASE[154];
			if(makeint(Pchar.money) < Sum)
			{
				Link.l1 = DLG_TEXT_BASE[155];
				Link.l1.go = "exit_Accuracy";
			}
			else
			{
				Link.l1 = DLG_TEXT_BASE[156];
				Link.l1.go = "Accuracy1";
				Link.l2 = DLG_TEXT_BASE[157];
				Link.l2.go = "exit_Accuracy";
			}
		break;

		case "Accuracy1":
			Sum = (sti(Pchar.skill.Accuracy) + 1) * 10000;
            AddCharacterSkill(Pchar, SKILL_ACCURACY, 10);
			AddMoneytoCharacter(Pchar, -Sum);
			Diag.CurrentNode = "get_out";
			DialogExit();
		break;

		case "Cannons":
			Sum = (sti(Pchar.skill.Cannons) + 1) * 10000;
			dialog.text = DLG_TEXT_BASE[158] + Sum + DLG_TEXT_BASE[159];
			if(makeint(Pchar.money) < Sum)
			{
				Link.l1 = DLG_TEXT_BASE[160];
				Link.l1.go = "exit_Cannons";
			}
			else
			{
				Link.l1 = DLG_TEXT_BASE[161];
				Link.l1.go = "Cannons1";
				Link.l2 = DLG_TEXT_BASE[162];
				Link.l2.go = "exit_Cannons";
			}
		break;

		case "Cannons2":
			Sum = (sti(Pchar.skill.Cannons) + 1) * 10000;
			dialog.text = DLG_TEXT_BASE[163] + Sum + DLG_TEXT_BASE[164];
			if(makeint(Pchar.money) < Sum)
			{
				Link.l1 = DLG_TEXT_BASE[165];
				Link.l1.go = "exit_Cannons";
			}
			else
			{
				Link.l1 = DLG_TEXT_BASE[166];
				Link.l1.go = "Cannons1";
				Link.l2 = DLG_TEXT_BASE[167];
				Link.l2.go = "exit_Cannons";
			}
		break;

		case "Cannons1":
			Sum = (sti(Pchar.skill.Cannons) + 1) * 10000;
            AddCharacterSkill(Pchar, SKILL_CANNONS, 10);
			AddMoneytoCharacter(Pchar, -Sum);
			Diag.CurrentNode = "get_out";
			DialogExit();
		break;

		case "Grappling":
			Sum = (sti(Pchar.skill.Grappling) + 1) * 10000;
			dialog.text = DLG_TEXT_BASE[168] + Sum + DLG_TEXT_BASE[169];
			if(makeint(Pchar.money) < Sum)
			{
				Link.l1 = DLG_TEXT_BASE[170];
				Link.l1.go = "exit_Grappling";
			}
			else
			{
				Link.l1 = DLG_TEXT_BASE[171];
				Link.l1.go = "Grappling1";
				Link.l2 = DLG_TEXT_BASE[172];
				Link.l2.go = "exit_Grappling";
			}
		break;

		case "Grappling2":
			Sum = (sti(Pchar.skill.Grappling) + 1) * 10000;
			dialog.text = DLG_TEXT_BASE[173] + Sum + DLG_TEXT_BASE[174];
			if(makeint(Pchar.money) < Sum)
			{
				Link.l1 = DLG_TEXT_BASE[175];
				Link.l1.go = "exit_Grappling";
			}
			else
			{
				Link.l1 = DLG_TEXT_BASE[176];
				Link.l1.go = "Grappling1";
				Link.l2 = DLG_TEXT_BASE[177];
				Link.l2.go = "exit_Grappling";
			}
		break;

		case "Grappling1":
			Sum = (sti(Pchar.skill.Grappling) + 1) * 10000;
            AddCharacterSkill(Pchar, SKILL_GRAPPLING, 10);
			AddMoneytoCharacter(Pchar, -Sum);
			Diag.CurrentNode = "get_out";
			DialogExit();
		break;

		case "Repair":
			Sum = (sti(Pchar.skill.Repair) + 1) * 10000;
			dialog.text = DLG_TEXT_BASE[178] + Sum + DLG_TEXT_BASE[179];
			if(makeint(Pchar.money) < Sum)
			{
				Link.l1 = DLG_TEXT_BASE[180];
				Link.l1.go = "exit_Repair";
			}
			else
			{
				Link.l1 = DLG_TEXT_BASE[181];
				Link.l1.go = "Repair1";
				Link.l2 = DLG_TEXT_BASE[182];
				Link.l2.go = "exit_Repair";
			}
		break;

		case "Repair2":
			Sum = (sti(Pchar.skill.Repair) + 1) * 10000;
			dialog.text = DLG_TEXT_BASE[183] + Sum + DLG_TEXT_BASE[184];
			if(makeint(Pchar.money) < Sum)
			{
				Link.l1 = DLG_TEXT_BASE[185];
				Link.l1.go = "exit_Repair";
			}
			else
			{
				Link.l1 = DLG_TEXT_BASE[186];
				Link.l1.go = "Repair1";
				Link.l2 = DLG_TEXT_BASE[187];
				Link.l2.go = "exit_Repair";
			}
		break;

		case "Repair1":
			Sum = (sti(Pchar.skill.Repair) + 1) * 10000;
			AddCharacterSkill(Pchar, SKILL_REPAIR, 10);
			AddMoneytoCharacter(Pchar, -Sum);
			Diag.CurrentNode = "get_out";
			DialogExit();
		break;

		case "Commerce":
			Sum = (sti(Pchar.skill.Commerce) + 1) * 10000;
			dialog.text = DLG_TEXT_BASE[188] + Sum + DLG_TEXT_BASE[189];
			if(makeint(Pchar.money) < Sum)
			{
				Link.l1 = DLG_TEXT_BASE[190];
				Link.l1.go = "exit_Commerce";
			}
			else
			{
				Link.l1 = DLG_TEXT_BASE[191];
				Link.l1.go = "Commerce1";
				Link.l2 = DLG_TEXT_BASE[192];
				Link.l2.go = "exit_Commerce";
			}
		break;

		case "Commerce2":
			Sum = (sti(Pchar.skill.Commerce) + 1) * 10000;
			dialog.text = DLG_TEXT_BASE[193] + Sum + DLG_TEXT_BASE[194];
			if(makeint(Pchar.money) < Sum)
			{
				Link.l1 = DLG_TEXT_BASE[195];
				Link.l1.go = "exit_Commerce";
			}
			else
			{
				Link.l1 = DLG_TEXT_BASE[196];
				Link.l1.go = "Commerce1";
				Link.l2 = DLG_TEXT_BASE[197];
				Link.l2.go = "exit_Commerce";
			}
		break;

		case "Commerce1":
			Sum = (sti(Pchar.skill.Commerce) + 1) * 10000;
			AddCharacterSkill(Pchar, SKILL_COMMERCE, 10);
			AddMoneytoCharacter(Pchar, -Sum);
			Diag.CurrentNode = "get_out";
			DialogExit();
		break;

		case "thanx":
			dialog.text = DLG_TEXT_BASE[198];
			Link.l1 = DLG_TEXT_BASE[199];
			Link.l1.go = "exit_than";
		break;

		case "once_more_portion":
			dialog.text = DLG_TEXT_BASE[200];
			Link.l1 = DLG_TEXT_BASE[201];
			Link.l1.go = "healing";
			Link.l2 = DLG_TEXT_BASE[202];
			Link.l2.go = "exit_once_more_portion";
		break;

		case "once_more":
			dialog.text = DLG_TEXT_BASE[203];
			Link.l1 = DLG_TEXT_BASE[204];
			Link.l1.go = "torg";
			Link.l2 = DLG_TEXT_BASE[205];
			Link.l2.go = "exit_once_more";
		break;

		case "get_out":
			dialog.text = DLG_TEXT_BASE[206];
			Link.l2 = DLG_TEXT_BASE[207];
			Link.l2.go = "exit_out";
		break;

		case "got_officer":
			dialog.text = DLG_TEXT_BASE[208];
			Link.l2 = DLG_TEXT_BASE[209];
			Link.l2.go = "exit_off";
		break;

		case "sovet":
			if (NPChar.sex != "man") //fix eddy. второй раз баба говорит как мужик
			{
                dialog.text = RandPhraseSimple("Мой муж запрещает говорить с "+ GetSexPhrase("незнакомцами","посторонними") +"!",
                         "Мне не о чем с вами говорить.");
				Link.l1 = "Ну и не нужно";
				Link.l1.go = "exit";
                break;
			}
			link.l10 = LinkRandPhrase ("Расскажи мне лучше, что за байки в ходу в здешней таверне?",
									"Лучше скажим мне, новенького в этих краях?",
									"Расскажи ка мне лучше, приятель, как течет жизнь на суше?");
			link.l10.go = "rumours_citizen"; //повесил на горожанина, если нужны отедельные слухи, то пишем соответствующую реализацию
			dialog.text = DLG_TEXT_BASE[210];
			Link.l1 = DLG_TEXT_BASE[211];
			Link.l1.go = "advises";
			Link.l2 = DLG_TEXT_BASE[212];
			Link.l2.go = "exit";
		break;

		case "advises":

			switch(Rand(6))
			{
				case 0:
					dialog.text = DLG_TEXT_BASE[213];
					Link.l1 = DLG_TEXT_BASE[214];
					Link.l1.go = "exit";
				break;

				case 1:
					dialog.text = DLG_TEXT_BASE[215];
					Link.l1 = DLG_TEXT_BASE[216];
					Link.l1.go = "police1";
					Link.l2 = DLG_TEXT_BASE[217];
					Link.l2.go = "exit";
				break;

				case 2:
					dialog.text = DLG_TEXT_BASE[218];
					Link.l1 = DLG_TEXT_BASE[219];
					Link.l1.go = "health1";
					Link.l2 = DLG_TEXT_BASE[220];
					Link.l2.go = "exit";
				break;

				case 3:
					dialog.text = DLG_TEXT_BASE[221];
					Link.l1 = DLG_TEXT_BASE[222];
					Link.l1.go = "exit";
				break;

				case 4:
					dialog.text = DLG_TEXT_BASE[223];
					Link.l1 = DLG_TEXT_BASE[224];
					Link.l1.go = "exit";
				break;

				case 5:
					dialog.text = DLG_TEXT_BASE[225];
					Link.l1 = DLG_TEXT_BASE[226];
					Link.l1.go = "exit";
				break;

				case 6:
					dialog.text = DLG_TEXT_BASE[227];
					Link.l1 = DLG_TEXT_BASE[228];
					Link.l1.go = "exit";
				break;
			}
		break;

		case "exit_Fencing":
			Diag.CurrentNode = "Fencing2";
			DialogExit();
		break;

		case "exit_Defence":
			Diag.CurrentNode = "Defence2";
			DialogExit();
		break;

		case "exit_Leadership":
			Diag.CurrentNode = "Leadership2";
			DialogExit();
		break;

		case "exit_Sailing":
			Diag.CurrentNode = "Sailing2";
			DialogExit();
		break;

		case "exit_Accuracy":
			Diag.CurrentNode = "Accuracy2";
			DialogExit();
		break;

		case "exit_Cannons":
			Diag.CurrentNode = "Cannons2";
			DialogExit();
		break;

		case "exit_Grappling":
			Diag.CurrentNode = "Grappling2";
			DialogExit();
		break;

		case "exit_Repair":
			Diag.CurrentNode = "Repair2";
			DialogExit();
		break;

		case "exit_Commerce":
			Diag.CurrentNode = "Commerce2";
			DialogExit();
		break;

		case "exit":
			Diag.CurrentNode = "sovet";
			DialogExit();
		break;

		case "exit1":
			ChangeCharacterReputation(pchar, 1);
			AddMoneytoCharacter(Pchar, -200);
			Diag.CurrentNode = "thanx";
			DialogExit();
		break;

		case "exit_out":
			Diag.CurrentNode = "get_out";
			DialogExit();
		break;

		case "exit_once_more":
			Diag.CurrentNode = "once_more";
			DialogExit();
		break;

		case "exit_once_more_portion":
			Diag.CurrentNode = "once_more_portion";
			DialogExit();
		break;

		case "exit_than":
			Diag.CurrentNode = "thanx";
			DialogExit();
		break;

		case "exit_off":
			Diag.CurrentNode = "got_officer";
			DialogExit();
		break;

		//у горожанина должна быть эта ветка.
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,
		                PCharRepPhrase(LinkRandPhrase("О, да я рад"+NPCharSexPhrase(NPChar, " ", "а ")+" тебе как выпивке, спрашивай, чего хочешь.", "Любишь поболтать, капитан? Что ж, я тоже... Особенно за кружечкой рома.", "Да, " + PChar.name + "?"),
                                        LinkRandPhrase("Ну, чего тебе еще?", "Вижу, капитан "+PChar.name+", ты "+ GetSexPhrase("охотник","охотница") +" поболтать? ", "Замучил"+ GetSexPhrase("","а") +" вопросами, капитан, лучше бы угостил"+ GetSexPhrase("","а") +" ромом.")),
		                PCharRepPhrase(LinkRandPhrase("Что вы хотели узнать "+ GetAddress_Form(NPChar) + "?", "Я вас слушаю капитан.", "Мне нужно идти, поэтому спрашивайте скорее капитан."),
                                        LinkRandPhrase("Всегда рад"+NPCharSexPhrase(NPChar, " ", "а ")+" приятному собеседнику, " + GetAddress_Form(NPChar) + " " + PChar.lastname + ". Говорите.",
                                                        "Да, " + GetAddress_Form(NPChar) + "?",
                                                        "Любите поболтать, капитан? Что ж, я тоже..."))
                            );

            // homo 25/06/06
			link.l1 = LinkRandPhrase ("Какие байки в ходу в здешней таверне?",
                                    "Что новенького в этих краях?",
                                    "Как течет жизнь на суше?");
			link.l1.go = "rumours_citizen";
			link.l5 = PCharRepPhrase(RandPhraseSimple("Тебе послышалось, я пойду.", "Нет, ничего - просто вышел погулять."),
                                        RandPhraseSimple("Ладно, ничего. Удачи!", "Просто прогуливаюсь. До свидания."));
			link.l5.go = "exit";
		break;
		//замечение по обнаженному оружию
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнаженным клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнаженным клинком.");
				link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажете...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Острожней на поворотах, "+ GetSexPhrase("приятель","подруга") +", когда бежишь с оружием в руках. Я ведь могу и занервничать...", "Мне не нравится, когда "+ GetSexPhrase("мужчины","всякие тут") +" ходят передо мной с оружием на изготовку. Это меня пугает...");
				link.l1 = RandPhraseSimple("Понял"+ GetSexPhrase("","а") +".", "Убираю.");
			}
			link.l1.go = "exit";
			Diag.TempNode = "First Time";
		break;
	}
}
