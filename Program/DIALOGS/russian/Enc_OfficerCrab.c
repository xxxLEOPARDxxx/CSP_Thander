// BOAL новый диалог офицера и компаньона 21/06/06

void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);

	ref    sld;
	string attr, attrLoc;
	int    iTemp, iTax, iFortValue;

	switch(Dialog.CurrentNode)
	{
        case "hired":

			dialog.text = "(Верный друг внимательно вас осматривает, ожидая приказа)";
			if (isOfficer(Npchar)) // проверка для кампуса, где слотовые офы
			{
	            Link.l2 = "Слушай мой приказ!";
	            Link.l2.go = "stay_follow";
            }
			Link.l4 = "Пора нам разойтись, приятель. Возвращайся в океан, к своему народу.";
			Link.l4.go = "AsYouWish";

            Link.l9 = "Ничего. Вольно.";
            Link.l9.go = "exit";
			Diag.TempNode = "hired";
        break;

		case "exit":
			Diag.TempNode = "hired";
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "AsYouWish":
			dialog.text = "(Краб жалобно стучит клешнями по земле.)";
			if (isOfficer(Npchar)) // проверка для кампуса, где слотовые офы
	            Link.l2 = "Прости, это мое окончательное решение. Для тебя слишком опасны все эти морские приключения.";
	            Link.l2.go = "exit_fire";
			Link.l4 = "Прости, я передумал" + GetSexPhrase("","а")+ ". Не знаю, что на меня нашло...";
			Link.l4.go = "exit";
			Diag.TempNode = "hired";
        break;

		case "exit_fire":
			//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}
			//navy <--
			Diag.TempNode = "Fired";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;

			DialogExit();
		break;

        // boal 05.09.03 offecer need to go to abordage -->
        case "stay_follow":
            dialog.text = "(Краб издает щелкающий звук, чтобы показать, что он внимательно вас слушает.)";
            Link.l1 = "Стой здесь!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Следуй за мной и не отставай!";
            Link.l2.go = "Boal_Follow";

		break;

        // boal 05.09.03 offecer need to go to abordage -->
	      case "Boal_Stay":
             //SetCharacterTask_Stay(Characters[Npchar.index]); // it's a mistic but here doesn't work :(
             //Log_SetStringToLog(Npchar.id +" "+Npchar.index);
              Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
              AddDialogExitQuestFunction("LandEnc_OfficerStay");
		      Diag.TempNode = "hired";
		      dialog.text = "(Видно, что он не одобряет вашего решения, но не собирается оспаривать приказ.)";
		      Link.l1 = "Вольно.";
		      Link.l1.go = "Exit";
		      Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
	      break;

	      case "Boal_Follow":
		      SetCharacterTask_FollowCharacter(Npchar, PChar); // it works here!!!
		      Diag.TempNode = "hired";
		      dialog.text = "(Краб клацает клешней в знак согласия.)";
		      Link.l1 = "Вольно.";
		      Link.l1.go = "Exit";
	      break;

		  case "Fired":
		      SetCharacterTask_FollowCharacter(Npchar, PChar); // it works here!!!
			  Diag.TempNode = "Fired";
		      dialog.text = "(Краб злобно клацает вам вслед.)";
		      Link.l1 = "Со временем ты поймешь, почему я так поступил"+ GetSexPhrase("","а")+ ".";
		      Link.l1.go = "Exit";
	      break;
        // boal 05.09.03 offecer need to go to abordage <--
		// <-- Самостоятельное плавание компаньона
	}
}
