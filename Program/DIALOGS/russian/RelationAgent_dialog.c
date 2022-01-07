#define DIPLOMAT_SUM 80000

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iSumm = 0;
	string s1;

	if (!CheckAttribute(npchar, "PatentPrice"))
    {
		if (IsCharacterPerkOn(pchar, "Adventurer")) npchar.PatentPrice = (6000 + rand(4) * 500);
        else npchar.PatentPrice = (8000 + rand(6) * 1000);
    }
    int i;
    string attrLoc;
	ref    sld;

    attrLoc   = Dialog.CurrentNode;

    if (findsubstr(attrLoc, "SetNationPatent_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.nation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "patent_2";
 	}

 	if (findsubstr(attrLoc, "SetNationLicence_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.LicenceNation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "NationLicenceType";
 	}

 	if (findsubstr(attrLoc, "NationLicenceType_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.LicenceType = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "NationLicenceType2";
 	}

 	if (findsubstr(attrLoc, "RelationTo_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
        npchar.quest.relation      = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
		// проверка на уже договор
		attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
		if (CheckAttribute(Pchar, "GenQuest." + attrLoc) && sti(Pchar.GenQuest.(attrLoc)) == true)
		{
		    Dialog.CurrentNode = "RelationYet";
		}
		else
		{
 	    	Dialog.CurrentNode = "RelationAny_Done";
 	    	npchar.quest.relation.summ = CalculateRelationSum(sti(npchar.quest.relation));
 	    }
 	}

 	if (findsubstr(attrLoc, "CityPay_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.quest.CityIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "CityInfo";
 	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
			dialog.text = "Рад видеть вас снова.";
			link.l1 = "Мне опять нужны ваши услуги.";
			link.l1.go = "relation";
			link.l2 = "Я уже ухожу.";
			link.l2.go = "exit";
			//линейка ГПК, поиски торгашей -->
			if (pchar.questTemp.LSC == "toLicencer")
			{
				link.l3 = "У меня есть к вам вопрос по поводу Голландской Вест-Индской компании.";
				link.l3.go = "SeekHVIC";
			}
			if (pchar.questTemp.LSC == "toLicencer_2")
			{
				link.l3 = "Хм, прошу прощения за свою дырявую голову. Я снова по поводу Голландской Вест-Индской компании.";
				link.l3.go = "SeekHVIC_3";
			}
			// генератор  "Найденные документы"
			if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAgent"))
			{
				link.l4 = "Хочу предложить сделку."
				link.l4.go = "D_ShipLetters_1";
				pchar.questTemp.different.GiveShipLetters.speakAgent = true;
			}
			//<-- линейка ГПК, поиски торгашей
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Позвольте представиться, я являюсь тем человеком, который может замолвить за вас словечко тому или иному губернатору. За плату, естественно, но поверьте, мои услуги самого высшего качества, и вы не пожалеете, если воспользуетесь моими талантами.";
				if (CheckAttribute(pchar, "Whisper.BuyDocuments"))
				{
					link.l1 = "Мне сказали, что я смогу у вас оформить документы на гражданство в одной из наций.";
					link.l1.go = "WhisperDocuments";
					break;
				}
				link.l1 = "Очень интересно, продолжай.";
				link.l1.go = "relation";
				link.l2 = "Может быть, в другой раз.";
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
			}

			NextDiag.TempNode = "First time";
		break;

		//*************************** Линейка Виспер **************
		case "WhisperDocuments":
			dialog.text = "Все верно. Эта услуга обойдется вам в 1000 монет. Чье гражданство вы бы хотели получить?";
			DeleteAttribute(Pchar, "perks.list.FlagSpa");
			DeleteAttribute(Pchar, "Whisper.BuyDocuments");
			if(makeint(Pchar.money) >= 1000)
            {
				link.l1 = "Англии.";
				link.l1.go = "WhisperEng";
				link.l2 = "Франции.";
				link.l2.go = "WhisperFra";
				link.l3 = "Голландии.";
				link.l3.go = "WhisperHol";
			}
			link.l4 = "А знаете, лучше я стану вольной корсаркой.";
			link.l4.go = "Whisper_exit";
		break;

		case "WhisperEng":
			dialog.text = "Хорошо. Осталось расписаться вот здесь и вы официально гражданка Англии.";
			Pchar.BaseNation = ENGLAND;
			SetCharacterPerk(Pchar, "FlagEng");
			AddMoneyToCharacter(pchar, -1000);
			Flag_Change(ENGLAND);
			link.l1 = "Готово.";
			link.l1.go = "Whisper_exit";
		break;
		case "WhisperFra":
			dialog.text = "Хорошо. Осталось расписаться вот здесь и вы официально гражданка Франции.";
			Pchar.BaseNation = FRANCE;
			SetCharacterPerk(Pchar, "FlagFra");
			AddMoneyToCharacter(pchar, -1000);
			Flag_Change(FRANCE);
			link.l1 = "Готово.";
			link.l1.go = "Whisper_exit";
		break;
		case "WhisperHol":
			dialog.text = "Хорошо. Осталось расписаться вот здесь и вы официально гражданка Голландии.";
			AddMoneyToCharacter(pchar, -1000);
			Pchar.BaseNation = HOLLAND;
			SetCharacterPerk(pchar, "FlagHol");
			Flag_Change(HOLLAND);
			link.l1 = "Готово.";
			link.l1.go = "Whisper_exit";
		break;
		case "Whisper_exit":
			dialog.text = "Вот ваши бумаги, не теряйте. Подуйте немного на чернила, чтоб высохли, а не то размажутся\nВсего хорошего.";
			link.l1 = "До свидания.";
			link.l1.go = "exit";
			if (Pchar.BaseNation == SPAIN || Pchar.BaseNation == PIRATE)
			{
				dialog.text = "В таком случае прошу меня не отвлекать.";
				Pchar.BaseNation = PIRATE;
				Flag_Change(PIRATE);
			}
			PChar.quest.WhisperPirateTownGetHat.win_condition.l1 = "location";
			PChar.quest.WhisperPirateTownGetHat.win_condition.l1.location = "PuertoPrincipe_town";
			PChar.quest.WhisperPirateTownGetHat.function = "WhisperPirateTownGetHat";
			PChar.quest.WhisperPirateTownBattle.win_condition.l1 = "location";
			PChar.quest.WhisperPirateTownBattle.win_condition.l1.location = "PuertoPrincipe_ExitTown";
			PChar.quest.WhisperPirateTownBattle.function = "WhisperPirateTownBattle";
			SetLocationCapturedState("PuertoPrincipe_town", true);
		break;
		//*************************** Генератор - "Найденные судовые документы" **************
		case "D_ShipLetters_1":
			dialog.text = "Излагайте условия.";
			s1 = "У меня, по счастливой случайности, оказался абсолютно легальный пакет судовых документов, еще не заявленных в розыск.";
			s1 = s1 + "Судно на плаву и не исключено из реестра, не беспокойтесь. Просто разиня-владелец умудрился потерять эти бумаги...";
			link.l1 = s1;
			link.l1.go = "D_ShipLetters_2";
		break;
		case "D_ShipLetters_2":
			s1 = "Дайте-ка взглянуть! Действительно, отметки совсем свежие. Что же, удача Вам благоволит, "+ GetSexPhrase("сударь","сударыня") +"! ";
			s1 = s1 + "Мне как раз понадобился именно такой комплект, и я, в свою очередь предлагаю Вам " + sti(pchar.questTemp.different.GiveShipLetters.price5) + " золотом. Что скажете?";
			dialog.text = s1;
			link.l1 = "Воистину королевская щедрость! Конечно же я "+ GetSexPhrase("согласен","согласна") +"!";
			link.l1.go = "D_ShipLetters_3";
			link.l2 = "Пожалуй, нет.";
			link.l2.go = "exit";
		break;
		case "D_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook");
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price5));
			ChangeCharacterReputation(pchar, -1);
			OfficersReaction("bad");
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер
			AddQuestRecord("GiveShipLetters", "9");
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "relation":
			dialog.text = "Давайте посмотрим, чем я могу вам помочь.";
            //#20200219-01
			int charNat = sti(pchar.nation);
			bool bCheck = false;
            if(GetNationRelation2MainCharacter(ENGLAND) > GetNationRelation(charNat, ENGLAND))
                bCheck = true;
            if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0 || bCheck)
			{
				link.l3 = "Я хочу помириться с Англией.";
				link.l3.go = "RelationTo_0";
			}



			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0 || bCheck)
			{
				link.l1 = "Я хочу помириться с Францией.";
				link.l1.go = "RelationTo_1";
			}



			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0 || bCheck)
			{
				link.l2 = "Я хочу помириться с Испанией.";
				link.l2.go = "RelationTo_2";
			}



			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0 || bCheck)
			{
				link.l4 = "Я хочу помириться с Голландией.";
				link.l4.go = "RelationTo_3";
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "Я хочу помириться с контрабандистами.";
				Link.l5.go = "Contraband";
            }
            Link.l8 = "Мне нужен каперский патент.";
			Link.l8.go = "patent_0";

			Link.l9 = "Есть торговые лицензии?";
			Link.l9.go = "Licence";

			if (isHeroOwnCity(true))
			{
				Link.l10 = "У меня вопрос, связанный с принадлежностью поселений.";
				Link.l10.go = "City_Buy";
			}

			Link.l11 = "Я пере"+GetSexPhrase("шел","шла")+" дорогу одному корсару и хочу наладить наши отношения. Можете это устроить?";
			Link.l11.go = "PGG_peace";

			link.l99 = "Знаете, я думаю, что обойдусь своими силами.";
			link.l99.go = "exit";
		break;

		case "PGG_peace":
			dialog.text = "О каком человеке идёт речь?";
			for(i=1; i<=PsHeroQty; i++)
			{
				sld = CharacterFromID("PsHero_"+i);
				if (PGG_ChangeRelation2MainCharacter(sld, 0) < 41 && !LAi_IsDead(sld) && sld.PGGAi.location != "Dead" && !IsCompanion(sld) && !IsOfficer(sld))
				{
					string attr = sld.ID;
					string linkPGG = "l" + i;
					NPChar.Temp.(attr) = attr;
					Link.(linkPGG) = GetFullName(sld);
					Link.(linkPGG).go = "PGG_make_peace_with_" + attr;
				}
				else
				{
					NPChar.Temp.(attr) = "";
				}
			}
			link.lexit = "Не бери в голову.";
			link.lexit.go = "exit";
		break;

		int nFind = findSubStr(Dialog.CurrentNode, "PGG_make_peace_with_", 0);
		string idxVal;
		string nodName;
		if(nFind == 0)
		{
            npchar.PGGSelected = strcut(Dialog.CurrentNode, 20, strlen(Dialog.CurrentNode)-1);
			sld = CharacterFromID(npchar.PGGSelected);
			npchar.PGGPeaceMoney = ((sti(sld.rank) + sti(pchar.rank))/4 + (60 - PGG_ChangeRelation2MainCharacter(sld, 0))) * 1000;
			dialog.Text = "Да, я слышал, что "+GetFullName(CharacterFromID(npchar.PGGSelected)) +" всей душой желает вам смерти. Думаю, я смог бы подобрать "+ NPCharSexPhrase(sld, "ему","ей")+ " подходящий подарок, чтобы заставить относиться к вам более благосклонно. Но эта услуга обойдётся вам в "+ npchar.PGGPeaceMoney +" пиастров.";
			if (sti(pchar.money) >= sti(npchar.PGGPeaceMoney))
			{

				Link.l1 ="Я согла"+GetSexPhrase("сен","сна")+", приступайте.";
				Link.l1.go = "PGG_peace_made";
			}
			Link.l2 = "Я передумал"+GetSexPhrase("","а")+", прошу прощения.";
            Link.l2.go = "exit";
            break;
        }

		case "PGG_peace_made":
			sld = CharacterFromID(npchar.PGGSelected);
			int addPGGrelation = 60 - PGG_ChangeRelation2MainCharacter(sld, 0);
			PGG_ChangeRelation2MainCharacter(sld, addPGGrelation);
			addMoneyToCharacter(pchar, -sti(npchar.PGGPeaceMoney));

			if (CheckAttribute(sld, "PGGAi.Task.SetSail"))
			{
				PGG_Disband_Fleet(sld);
				sld.PGGAi.location.town = PGG_FindRandomTownByNation(sti(sld.nation));
			}

			dialog.Text = "Считайте, что всё уже улажено. Любая охота, которую мог"+ NPCharSexPhrase(sld, "","ла")+ " вести на вас "+ GetFullName(sld) +" должна в скором времени прекратиться."
			Link.l1 ="Буду надеяться, что вы правы.";
			Link.l1.go = "exit";
		break;

		case "Licence":
			dialog.text = "Всегда в наличии, на разные сроки. Какая торговая лицензия интересует?";
		    link.l1 = "Англии";
			link.l1.go = "SetNationLicence_0";
		    link.l2 = "Франции";
			link.l2.go = "SetNationLicence_1";
		    link.l3 = "Испании";
			link.l3.go = "SetNationLicence_2";
		    link.l4 = "Голландии";
			link.l4.go = "SetNationLicence_3";
			link.l9 = "Знаете, я думаю, что обойдусь своими силами.";
			link.l9.go = "exit";
		break;

		case "NationLicenceType":
        	dialog.text = "На какой срок?";
		    link.l1 = "30 дней";
			link.l1.go = "NationLicenceType_30";
		    link.l2 = "60 дней";
			link.l2.go = "NationLicenceType_60";
		    link.l3 = "90 дней";
			link.l3.go = "NationLicenceType_90";
			link.l9 = "Я передумал"+ GetSexPhrase("","а") +".";
			link.l9.go = "exit";
		break;

		case "NationLicenceType2":
			if (IsCharacterPerkOn(pchar, "Agent")) iSumm = sti(npchar.LicenceType) * MOD_SKILL_ENEMY_RATE * 500 + 200000 + (sti(PChar.rank)*1000) - (GetSummonSkillFromName(PChar, SKILL_COMMERCE) + GetSummonSkillFromName(PChar, SKILL_LEADERSHIP)) * 1000;
			else iSumm = sti(npchar.LicenceType) * MOD_SKILL_ENEMY_RATE * 1000 + 300000 + (sti(PChar.rank)*2000) - (GetSummonSkillFromName(PChar, SKILL_COMMERCE) + GetSummonSkillFromName(PChar, SKILL_LEADERSHIP)) * 1000;
        	dialog.text = "Итак, торговая лицензия " + XI_ConvertString(Nations[sti(npchar.LicenceNation)].Name + "Gen") + " сроком на " + sti(npchar.LicenceType) + " дней, цена " + FindRussianMoneyString(iSumm) + ".";
		    link.l1 = "Меня устраивает.";
		    if(makeint(Pchar.money) < iSumm)
            {
				Link.l1.go = "No_money";
			}
            else
			{
				link.l1.go = "NationLicenceType3";
			}
			link.l9 = "Я передумал"+ GetSexPhrase("","а") +".";
			link.l9.go = "exit";
		break;

		case "NationLicenceType3":
            //iSumm = sti(npchar.LicenceType) * (2000 * MOD_SKILL_ENEMY_RATE) - (GetSummonSkillFromName(PChar, SKILL_COMMERCE) + GetSummonSkillFromName(PChar, SKILL_LEADERSHIP)) * 2000 + sti(PChar.rank)*10000;
			if (IsCharacterPerkOn(pchar, "Agent"))  iSumm = sti(npchar.LicenceType) * MOD_SKILL_ENEMY_RATE * 500 + 200000 + (sti(PChar.rank)*1000) - (GetSummonSkillFromName(PChar, SKILL_COMMERCE) + GetSummonSkillFromName(PChar, SKILL_LEADERSHIP)) * 1000;
			else iSumm = sti(npchar.LicenceType) * MOD_SKILL_ENEMY_RATE * 1000 + 300000 + (sti(PChar.rank)*2000) - (GetSummonSkillFromName(PChar, SKILL_COMMERCE) + GetSummonSkillFromName(PChar, SKILL_LEADERSHIP)) * 1000;
			dialog.text = "Вот ваш документ. Входить в порт нужно под дружественным флагом. Помните, патруль может проверить, не просрочена ли лицензия.";
			link.l9 = "Спасибо.";
			link.l9.go = "exit";
			AddMoneyToCharacter(pchar, -iSumm);
			GiveNationLicence(sti(npchar.LicenceNation), sti(npchar.LicenceType));
		break;

        case "No_money":
			dialog.text = "Отлично! Обратитесь ко мне, когда будет нужная сумма.";
			link.l1 = "Хорошо.";
			link.l1.go = "exit";
		break;

        case "patent_0":
			dialog.text = "Замечательно! Для этого вы должны доказать свою преданность державе" +
                          " безупречной службой. Отправляйтесь к любому губернатору" + //NationNameGenitive(sti(NPChar.nation)) +
                          " и выполните ряд его заданий. После этого он выдаст вам патент.";
			link.l1 = "Скажите, "+GetAddress_FormToNPC(NPChar) + ", а можно как-нибудь обойти эту формальность? ";
			link.l1.go = "patent_1";
			link.l2 = "Прощайте, "+GetAddress_FormToNPC(NPChar);
			link.l2.go = "exit";
		break;

		case "patent_1":
			dialog.text = "Вы имеете в виду подкуп должностного лица!? Хотите, чтобы я выдал вам патент сам?";
			link.l1 = "Именно!";
			if (pchar.questTemp.piratesLine == "begin" || pchar.questTemp.piratesLine == "over" || pchar.questTemp.piratesLine == "waiting_Q8")
			{
				if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) > rand(11) || bBettaTestMode)
				{
					link.l1.go = "patent_2_give";
				}
				else
				{
					link.l1.go = "patent_2_none";
				}
			}
			else link.l1.go = "patent_2_none2";
			link.l2 = "Нет. Всего хорошего, "+GetAddress_FormToNPC(NPChar);
			link.l2.go = "exit";
		break;

		case "patent_2_none":
			dialog.text = "В данный момент я не располагаю такими связями, чтобы раздобыть чистый бланк патента со всеми печатями и подписями.";
            link.l1 = "Жаль. Прощайте, "+GetAddress_FormToNPC(NPChar);
			link.l1.go = "exit";
		break;

		case "patent_2_none2":
			dialog.text = "Насколько мне известно, вы работаете на Береговое Братство, в связи с чем даже наличие каперского патента не позволит вам поступить на службу к любому генерал-губернатору.";
            link.l1 = "Жаль. Прощайте, "+GetAddress_FormToNPC(NPChar);
			link.l1.go = "exit";
		break;

		case "patent_2_give":
			dialog.text = "Хорошо, я смогу это устроить. Какой патент вам нужен?";
			if (GetPatentNation() != ENGLAND)
			{
			    link.l1 = "Англии";
				link.l1.go = "SetNationPatent_0";
			}
			if (GetPatentNation() != FRANCE)
			{
			    link.l2 = "Франции";
				link.l2.go = "SetNationPatent_1";
			}
			if (GetPatentNation() != SPAIN)
			{
			    link.l3 = "Испании";
				link.l3.go = "SetNationPatent_2";
			}
			if (GetPatentNation() != HOLLAND)
			{
			    link.l4 = "Голландии";
				link.l4.go = "SetNationPatent_3";
			}
			link.l9 = "Знаете, я думаю, что обойдусь своими силами.";
			link.l9.go = "exit";
		break;

		case "patent_2":
            //pchar.PatentPrice = 8000 + (sti(NPChar.PatentPrice) * sti(pchar.rank));
			// pchar.PatentPrice = 350000 - (GetSummonSkillFromName(PChar, SKILL_COMMERCE) + GetSummonSkillFromName(PChar, SKILL_LEADERSHIP)) * 2000 + 6000 * sti(pchar.rank) * MOD_SKILL_ENEMY_RATE;
			if (IsCharacterPerkOn(pchar, "Agent")) pchar.PatentPrice = 100000 * MOD_SKILL_ENEMY_RATE - (GetSummonSkillFromName(PChar, SKILL_LEADERSHIP)) * 5000 + 35000 + (sti(PChar.rank)*5000);
			else pchar.PatentPrice = 150000 * MOD_SKILL_ENEMY_RATE - (GetSummonSkillFromName(PChar, SKILL_LEADERSHIP)) * 5000 + 500000 + (sti(PChar.rank)*5000);
            switch (sti(NPChar.nation))
            {
			    case PIRATE :
                    dialog.text = "Явный баг, если видите - сообщите ALexusB";
                    link.l1 = "Неплохая перспектива. Я "+ GetSexPhrase("согласен","согласна") +" на ваши условия!";
                    break;
                case HOLLAND :
                    dialog.text = "Голландия почти мирная страна, у вас станет много друзей и мало врагов. А сам патент обойдется вам всего лишь в "+pchar.PatentPrice+" золотых.";
                    link.l1 = "Неплохая перспектива. Я "+ GetSexPhrase("согласен","согласна") +" на ваши условия!";
                    break;
                case FRANCE :
                    dialog.text = "Друзья и враги Франции станут вашими. Вы сможете топить корабли врагов. А сам патент обойдется вам всего лишь в "+pchar.PatentPrice+" золотых.";
                    link.l1 = "Отличная перспектива! Мне плевать, кому служить! Послужу и французам!";
                    break;
                case SPAIN :
                    dialog.text = "У Испании много врагов и они тут же станут вашими! Испанцы - нация морских воинов. Патент обойдется вам всего лишь в "+pchar.PatentPrice+" золотых.";
                    link.l1 = "Вы один предлагаете мне что-то стоящее! Получите эти жалкие гроши за романтику кровавого боя и новые задания высокопоставленных особ!";
                    break;
                case ENGLAND :
                    dialog.text = "Если честно, таким образом генерал-губернатор Англии набивает свой карман. А сам патент обойдется вам всего лишь в "+pchar.PatentPrice+" золотых. ";
                    link.l1 = "Я "+ GetSexPhrase("согласен","согласна") +" отдать ему свои кровные деньги, которые добыл"+ GetSexPhrase("","а") +" контрабандой и абордажами!!";
                    break;
			}

            if(makeint(Pchar.money) < makeint(pchar.PatentPrice))
            {
				Link.l1.go = "No_money";
			}
            else
			{
				link.l1.go = "patent_3";
			}

			link.l2 = "Нет, это не для меня!";
			link.l2.go = "exit";
		break;

		case "patent_3":
            pchar.PatentNation = NationShortName(sti(NPChar.nation));
			dialog.text = "Я рад, что мы договорились. По рукам.";
			link.l1 = "Прощайте, "+GetAddress_FormToNPC(NPChar);
			link.l1.go = "exit";
			AddDialogExitQuest("any_patent_take");
		break;

		case "Contraband":
			if (IsCharacterPerkOn(pchar, "Agent")) Pchar.questTemp.Relations.sum = makeint(0.3 * stf(Pchar.rank)/stf(Pchar.reputation)*DIPLOMAT_SUM);
			else Pchar.questTemp.Relations.sum = makeint(0.1 * stf(Pchar.rank)/stf(Pchar.reputation)*DIPLOMAT_SUM);
			dialog.Text = "Хорошо. Это обойдется в " + Pchar.questTemp.Relations.sum + " золотых.";
			Link.l1 = "Я соглас"+ GetSexPhrase("ен","на") +".";
			if(makeint(Pchar.money) < makeint(Pchar.questTemp.Relations.sum))
			{
				Link.l1.go = "No_money";
			}
			else
			{
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "Пожалуй, я передумал"+ GetSexPhrase("","а") +".";
			Link.l2.go = "exit";
		break;

		case "Contraband_Agreed":
			dialog.Text = "Замечательно, я все улажу. Они будут иметь с вами дело.";
			Link.l99 = "Спасибо.";
			Link.l99.go = "exit";
			ChangeContrabandRelation(pchar, 25);
			AddMoneyToCharacter(pchar, -sti(Pchar.questTemp.Relations.sum));
		break;
        // boal <--
		case "RelationAny_Done":
			iSumm = sti(npchar.quest.relation.summ);
			dialog.text = "Хм-м... даже не знаю, что сказать. Я, конечно, смогу выполнить вашу просьбу о примирении с "+ XI_ConvertString(Nations[sti(npchar.quest.relation)].Name + "Abl") +", но это будет вам стоить " + FindRussianMoneyString(iSumm) + ".";
			if(sti(pchar.money) >= iSumm)
			{
				link.l1 = "Думаю, у меня все равно нет выбора. Так что вот ваши деньги.";
				link.l1.go = "relation3";
			}
			link.l2 = "Нет, это слишком большая сумма. Прощайте.";
			link.l2.go = "exit";
		break;

		case "relation3":
			dialog.text = "Отлично! С вами удивительно легко иметь дело. Можете быть спокойны, по истечении максимум 15 дней ваши дела будут улажены.";
			link.l1 = "Хорошо.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(npchar.quest.relation.summ));
			ChangeNationRelationFromRelationAgent(npchar);
			attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
            Pchar.GenQuest.(attrLoc) = true;
		break;

		case "RelationYet":
			dialog.Text = "За вас уже пошло ходатайство. Ждите, так быстро дела не делаются.";
			Link.l99 = "Спасибо.";
			Link.l99.go = "exit";
		break;

		case "City_Buy":
			dialog.Text = "Принадлежность какого поселения вы хотите обсудить?";
			for (i=0; i<MAX_COLONIES; i++)
			{
				if (sti(colonies[i].HeroOwn) == true && sti(colonies[i].isBought) == false)
				{
					sld = GetFortCommander(colonies[i].id);
					attrLoc = "l" + i;
					Link.(attrLoc) = GetCityName(colonies[i].id) + " - " + XI_ConvertString(GetNationNameByType(sti(sld.Default.nation)));
					Link.(attrLoc).go = "CityPay_" + i;
				}
			}
			Link.l99 = "Нет. Ничего.";
			Link.l99.go = "exit";
		break;

		case "CityInfo":
            i = sti(NPChar.quest.CityIdx);
            sld = GetFortCommander(colonies[i].id);
            iSumm = TWN_CityCost(colonies[i].id);
			dialog.Text = "Город " + GetCityName(colonies[i].id) + ", принадлежал " + XI_ConvertString(GetNationNameByType(sti(sld.Default.nation)) + "Gen") + ", сумма выкупа для прекращения попыток отбить поселение составит " + FindRussianMoneyString(iSumm) + ".";
   			if(sti(pchar.money) >= iSumm)
			{
			    Link.l1 = "Да, меня это вполне устраивает.";
				Link.l1.go = "City_Buy_End";
			}
			Link.l99 = "Нет, спасибо. Не интересно.";
			Link.l99.go = "exit";
		break;

		case "City_Buy_End":
            i = sti(NPChar.quest.CityIdx);
            TWN_RealeseForMoney(colonies[i].id, true);
			dialog.Text = "Хорошо, информация о сделке пошла. Попыток захвата города " + GetCityName(colonies[i].id) + " больше не будет.";
			Link.l2 = "Спасибо. Всего хорошего.";
			Link.l2.go = "exit";
			Link.l3 = "Еще один вопрос.";
			Link.l3.go = "relation";
		break;
		//линейка ГПК
		case "SeekHVIC":
			dialog.text = "Хм-м, однако... Капитан, а что это вам взбрендило интересоваться этой конторой?";
			link.l1 = "Я выполняю для них один заказ, и возникли вопросы.";
			link.l1.go = "SeekHVIC_1";
		break;
		case "SeekHVIC_1":
			dialog.text = "А с чего вы взяли, что я знаю, где они находятся?";
			link.l1 = "Ладно, хватит дурака валять! Лицензии от этой компании вы откуда берете?";
			link.l1.go = "SeekHVIC_2";
		break;
		case "SeekHVIC_2":
			dialog.text = "У представителя компании здесь, в Карибском море. Кстати, как его зовут? Если вы имеете с ним дела, то должны это знать.";
			Link.l1.edit = 6;
			link.l1 = "";
			link.l1.go = "SeekHVIC_res";
		break;
		case "SeekHVIC_res":
			attrLoc = GetStrSmallRegister(dialogEditStrings[6]);
			if (findsubstr(attrLoc, "оливер" , 0) != -1 && findsubstr(attrLoc, "траст" , 0) != -1)
			{
				dialog.text = "Хм, верно... Ну ладно, вы можете найти его на Сан Мартине, в Мариго. У него кабинет в представительстве Компании, большое административное здание с охраной, сложно пропустить. Только не говорите, что это я вас к нему отправил. Так, на всякий случай...";
				link.l1 = "Без проблем.";
				link.l1.go = "exit";
				pchar.questTemp.LSC = "toOliverTrast";
				AddQuestRecord("ISS_PoorsMurder", "10");
				LocatorReloadEnterDisable("Marigo_town", "houseH2", false);
				if (MOD_SKILL_ENEMY_RATE == 10 && bHardAnimations) sld = GetCharacter(NPC_GenerateCharacter("PoorKillSponsor", "smuggler_boss", "man", "spy", 30, PIRATE, -1, true)); // LEO: Страдать превозмогаторам 07.12.2021
				else sld = GetCharacter(NPC_GenerateCharacter("PoorKillSponsor", "smuggler_boss", "man", "man_fast", 30, PIRATE, -1, true));
				sld.name = "Оливер";
				sld.lastname = "Траст";
				FantomMakeCoolFighter(sld, 40, 90, 90, "blade26", "pistol3", 100);
				sld.SaveItemsForDead = true;
				if (bHardBoss) sld.AlwaysReload = true;//перезарядка независимо от Дозарядки
				sld.Dialog.Filename = "Quest\ForAll_dialog.c";
				sld.dialog.currentnode = "Begin_PoorKill";
				sld.nation = HOLLAND;
				sld.city = "Marigo_town";
				sld.location = "Marigo_houseH2";
				sld.location.group = "sit";
				sld.location.locator = "sit1";
				sld.dialog.currentnode = "PKInMarigo";
				LAi_CharacterEnableDialog(sld);
				LAi_RemoveLoginTime(sld);
				sld.standUp = true; //вставать и нападать на врага
				LAi_SetHuberType(sld);
				LAi_group_MoveCharacter(sld, "OlivaTrust");
				//ложим второе письмо
				ChangeItemName("letter_LSC", "itmname_letter_LSC_1");
				ChangeItemDescribe("letter_LSC", "itmdescr_letter_LSC_1");
				ref sldd = ItemsFromID("letter_LSC");
				sldd.shown = true;
				//Boyer change #20170418-01
                pchar.restoreLSCTrustLetter = "letter_LSC";
				sldd.startLocation = "Marigo_houseH2";
				sldd.startLocator = "item1";
			}
			else
			{
				dialog.text = "Никого вы не знаете, так что убирайтесь!";
				link.l1 = "Черт, вылетело из головы...";
				link.l1.go = "exit";
				pchar.questTemp.LSC = "toLicencer_2";
			}
		break;
		case "SeekHVIC_3":
			dialog.text = "Ну, и что вы опять от меня хотите?";
			link.l1 = "Я вспомнил"+ GetSexPhrase("","а") +" имя представителя Голландской Вест-Индской компании!";
			link.l1.go = "SeekHVIC_4";
		break;
		case "SeekHVIC_4":
			dialog.text = "Да?! Ну, и как его зовут?";
			Link.l1.edit = 6;
			link.l1 = "";
			link.l1.go = "SeekHVIC_res";
		break;
	}
}

