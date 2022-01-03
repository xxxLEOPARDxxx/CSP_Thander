#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06

void ProcessDialogEvent()
{
	int license_price = sti(PChar.rank) * (2500) * (0.01 * (120 - GetSummonSkillFromName(PChar, SKILL_COMMERCE)));;
	int license_expires = rand(2);

	ref NPChar, sld;
	aref Link, NextDiag, arCapBase, arCapLocal;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	if (!CheckAttribute(NPChar, "Portman")) NPChar.Portman = 0;

	int i, cn, iOfficer;
	ref chref, compref;
	ref rRealShip;
	string attrL, sTitle, sCapitainId, s1;
	string sColony;
	string offtype = "";

	String sLastSpeakDate = LastSpeakDate();

	bool ok, ok2;
	int iTest = FindColony(NPChar.City); // город магазина
	ref rColony;

	attrL = Dialog.CurrentNode;

	if(HasSubStr(attrL, "OfficerStockManBack_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.OfficerToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
		Dialog.CurrentNode = "OfficerStockManBack";
	}

	if(HasSubStr(attrL, "OfficerStockSel_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.OfficerToStoreIdx = GetPassenger(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); // индех в конце
		Dialog.CurrentNode = "OfficerStock_2";
	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "First time":
			NextDiag.TempNode = "First time";
			if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				dialog.text = "Приветствую вас, " + GetAddress_Form(NPChar) + ". Мы, кажется, не знакомы. Я "  + GetFullName(npchar)+ " - управляющий Капитула Испанской инвизиции Карибских островов.";
				Link.l1 = "Здравствуйте, " + GetFullName(NPChar) + ". Я " + GetFullName(PChar) + ", капитан корабля '" + PChar.ship.name + "'.";
			}
			else
			{
				dialog.text = LinkRandPhrase("Приветствую вас, " + GetAddress_Form(NPChar) + ". Вы ко мне по делу?",
									"Здравствуйте, " + GetFullName(Pchar) + ". Мне доложили о вашем прибытии.",
									"А, капитан " + GetFullName(Pchar) + ". Что привело вас ко мне?");
				Link.l1 = "Здравствуйте, " + GetFullName(NPChar) + ". Я хочу с вами поговорить.";
			}
			if (NPChar.id == "Wh_Jim")
			{
				dialog.text = "Капитан! Рад снова вас видеть. С чем пожаловали сегодня?";
				Link.l1 = "Привет, " + npchar.name + ". Нужно кое-что обсудить.";

			}
			Link.l1.go = "node_2";
		break;
		case "node_2":
			// Церковный генератор 1

			dialog.text = "Прекрасно. Я к вашим услугам, " + GetFullName(PChar) + ".";

			Link.l3 = "Я хочу оставить здесь офицера для обучение.";
			Link.l3.go = "ShipStock_1";

			if (sti(NPChar.Portman) > 0)
			{
				Link.l4 = "Я хочу забрать своего офицера обратно.";
				Link.l4.go = "OfficerStockReturn_1";
			}

			Link.l15 = "Благодарю. До свидания.";
			Link.l15.go = "exit";
		break;
		case "again":
			dialog.text = "Что-то ещё?";

			Link.l3 = "Я хочу оставить здесь офицера для обучение.";
			Link.l3.go = "ShipStock_1";

			if (sti(NPChar.Portman) > 0)
			{
				Link.l4 = "Я хочу забрать своего офицера обратно.";
				Link.l4.go = "OfficerStockReturn_1";
			}

			Link.l15 = "Больше ничего. До свидания.";
			Link.l15.go = "exit";
		break;

		//<--------------------------- инфа по базе квествых кэпов

		case "ShipStock_1":
			dialog.text = "Кого именно вы хотите оставить?";
			for(i=0; i<GetPassengersQuantity(pchar); i++)
			{
				iOfficer = GetPassenger(pchar, i);
				sld = GetCharacter(iOfficer);
				if (!GetRemovable(sld)) continue;
				attrL = "l"+i;
				Link.(attrL)	= "Офицер " + GetFullName(sld) + ".";
				Link.(attrL).go = "OfficerStockSel_" + i;
			}
			Link.l99 = "Спасибо, не нужно.";
			Link.l99.go = "exit";
		break;

		case "OfficerStock_2":
			chref = GetCharacter(sti(NPChar.OfficerToStoreIdx));

			if (!CheckAttribute(chref,"quest.officertype")) offtype = "Универсал";
			else offtype = XI_ConvertString(chref.quest.officertype);
			dialog.Text = "Вы выбрали "+GetFullName(chref)+", специализация - "+offtype+".";
			Link.l1 = "Да. Это меня устраивает.";
			Link.l1.go = "OfficerStock_3";
			Link.l99 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			Link.l99.go = "exit";
		break;

		case "OfficerStock_3":
			chref = GetCharacter(sti(NPChar.OfficerToStoreIdx));
			chref.OfficerInStockMan = NPChar.id;
			// Warship 22.03.09 fix Не перенеслось с КВЛ 1.2.3
			chref.OfficerInStockMan.AltDate = GetQuestBookDataDigit(); // для печати
			SaveCurrentNpcQuestDateParam(chref, "OfficerInStockMan.Date"); // для расчета
			RemovePassenger(pchar, chref);

			chref.location = "";
			chref.location.group = "";
			chref.location.locator = "";
			NPChar.Portman	= sti(NPChar.Portman) + 1;
			pchar.OfficerInStock = sti(pchar.OfficerInStock) + 1;//разобраться - что это. не могу найти, где оно используется.

			dialog.text = "Хорошо. Заберете, когда будет нужно.";
			Link.l1 = "Спасибо.";
			Link.l1.go = "again";
		break;

		case "OfficerStockReturn_1":
			dialog.text = "Кого именно вы забираете?";
			cn = 1;
			for(i=1; i<MAX_CHARACTERS; i++)
			{
				makeref(chref, Characters[i]);
				if (CheckAttribute(chref, "OfficerInStockMan"))
				{
					if (chref.OfficerInStockMan == NPChar.id)
					{
						attrL = "l"+cn;
						if (!CheckAttribute(chref,"quest.officertype")) offtype = "Универсал";
						else offtype = XI_ConvertString(chref.quest.officertype);
						Link.(attrL)	= "Офицер " + GetFullName(chref) + ", специализация - "+offtype+".";
						Link.(attrL).go = "OfficerStockManBack_" + i;
						cn++;
					}
				}
			}

			Link.l99 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			Link.l99.go = "exit";
		break;
	  	case "OfficerStockManBack":
			chref = GetCharacter(sti(NPChar.OfficerToStoreIdx));
			dialog.Text = "Забираете офицера "+GetFullName(chref)+"?";
			Link.l1 = "Да.";
			Link.l1.go = "OfficerStockManBack2";
			Link.l2 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			Link.l2.go = "exit";
		break;

		case "OfficerStockManBack2":
			chref = GetCharacter(sti(NPChar.OfficerToStoreIdx));
			dialog.text = GetFullName(chref)+" был направлен к вам на корабль, капитан.";
			Link.l1 = "Благодарю.";
			Link.l1.go = "again";
			DeleteAttribute(chref, "OfficerInStockMan");
			AddPassenger(pchar, chref, false);

			NPChar.Portman	= sti(NPChar.Portman) - 1;
			pchar.OfficerInStock = sti(pchar.OfficerInStock) - 1;

		break;

	}
}

void DelBakSkill(ref _compref)
{
	DelBakSkillAttr(pchar);
	ClearCharacterExpRate(pchar);
	RefreshCharacterSkillExpRate(pchar);
	SetEnergyToCharacter(pchar);

	DelBakSkillAttr(_compref);
	ClearCharacterExpRate(_compref);
	RefreshCharacterSkillExpRate(_compref);
	SetEnergyToCharacter(_compref);
}
