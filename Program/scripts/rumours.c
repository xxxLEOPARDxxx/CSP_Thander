// Philippe, de AoP1
//#define MAX_RUMOURS	30 // (comme dans rumours_init)10000
int RumoursQuantity = 0;

//object Rumours[MAX_RUMOURS];

string sType = "";
int iArgument1;
int iArgument2;
int iArgument3;
int rumours;

void GenerateRumourAoP()//(string sType, int iArgument1, int iArgument2, int iArgument3)
{
	//hovernor_change_location
	//country_lost_all_colonies
	//hovernor_killed
	//hovernor_captured
	//new_capital

	//gold_convoy_begin -iArgument1 - iNation, iArgument2 - beginColonyIndex, iArgument2 - endColonyIndex
	//gold_convoy_end - iArgument1 - iNation, iArgument2 - beginColonyIndex
	//gold_convoy_dead - iArgument1 - iNation, iArgument2 - character index, who killed convoy

	//trade_up - iArgument1 = GOOD_, iArgument2 = price
	//trade_down - iArgument1 = Good, iArgument2 = price
	//war_begin - iArgument1 = Nation, iArgument2 = Nation
	//war_end - iArgument1 = Nation, iArgument2 = Nation
	//friend_end - iArgument1 = Nation, iArgument2 = Nation
	//friend_begin - iArgument1 = Nation, iArgument2 = Nation
	//make_alliance -  iArgument1 = Nation, iArgument2 = Nation, iArgument3 = Nation
	//alliance_end -  iArgument1 = Nation, iArgument2 = Nation
	//colony_captured - , iArgument1 = Colony, iArgument2 = , iArgument3
	//colony_occupation - , iArgument1 = Nation, iArgument2 - Enemy, iArgument3 - Colony
	//colony_robbing - iArgument1 = Nation, iArgument2 - Nation, iArgument3 - Colony
	//colony_destroy - iArgument1 = Nation, iArgument2 - Nation, iArgument3 - Colony
	//colony_defend -  iArgument1 = Nation, iArgument2 - Nation, iArgument3 - Colony
	//ranger_dead - , iArgument1 = characterIndex, iArgument2 - type
	//ranger_captured - , iArgument1 = characterIndex, iArgument2 - island, iArgument3 - type
	//ranger_uncaptured - , iArgument1 = characterIndex, iArgument2 - island, iArgument3 - type
	//disease_begin -, iArgument1 = island.index, iArgument2 - нация
	//disease_end - , iArgument1 = island.index
	//colony_colonists -, iArgument1 = colony.index
	//history_event -  iArgument1 = event.index
	//ship_info
	//colony_upgrade
	//ranger_career -  iArgument1 - characterIndex,

	int iNumber = CheckRumourAoPPosition();// Dernier

	int iInfoColony = -1;
	string sTypeInfo = "-1";

	string sTargetColony, sTargetColonyAcc, sTargetColonyDat, sTargetColonyGen;
	string sNextColony, sNextColonyAcc, sNextColonyDat, sNextColonyGen;
	string sWho, sName, sMoney;
	string sGood, sGoodgen, sGoodAcc;
	string sShipName, sUpgrade;

	string sParam = "";
	string sStringID;
	string sResult;
	switch (sType)
	{
		case "hovernor_change_location":
			FormatColonyString(iArgument2, 1, &sParam);
			FormatColonyString(iArgument3, 2, &sParam);
			FormatNationString(sti(Characters[iArgument1].nation), 1, &sParam);
			sParam = DialogAddParamToStr(sParam, "sCharName", Characters[iArgument1].id);
			sStringID = "HovernorChangeLocationRumour" + rand(2);
			sResult = DialogAssembleStr(sStringID, sParam);
		break;
		case "country_lost_all_colonies":
			FormatNationString(iArgument1, 1, &sParam);
			sStringID = "DefeatedNationRumour" + rand(2);
			sResult = DialogAssembleStr(sStringID, sParam);
		break;
		case "hovernor_killed":
			FormatNationString(iArgument1, 1, &sParam);
			sStringID = "HovernorKilledRumour" + rand(2);
			sResult = DialogAssembleStr(sStringID, sParam);
		break;
		case "hovernor_captured":
			FormatNationString(iArgument1, 1, &sParam);
			sStringID = "HovernorCapturedRumour" + rand(2);
			sResult = DialogAssembleStr(sStringID, sParam);
		break;
		case "new_capital":
			FormatColonyString(iArgument1, 1, &sParam);
			FormatNationString(iArgument2, 1, &sParam);

			sStringID = "NewCapitalFounded" + rand(2);
			sResult = DialogAssembleStr(sStringID, sParam);
		break;
		case "gold_convoy_dead":
			FormatNationString(iArgument1, 1, &sParam);
			sParam = DialogAddParamToStr(sParam, "sCharName", Characters[iArgument2].id);
			sStringID = "DefeatGoldConvoyEndRumour" + rand(2);
			sResult = DialogAssembleStr(sStringID, sParam);
		break;
		case "gold_convoy_end":
			FormatNationString(iArgument1, 1, &sParam);
			FormatColonyString(iArgument2, 1, &sParam);
			sStringID = "SelectGoldConvoyEndRumour" + rand(2);
			sResult = DialogAssembleStr(sStringID, sParam);
		break;
		case "gold_convoy_begin":
			FormatNationString(iArgument1, 1, &sParam);
			FormatColonyString(iArgument2, 1, &sParam);
			FormatColonyString(iArgument3, 2, &sParam);

			sStringID = "SelectGoldConvoyBeginRumour" + rand(2);
			sResult = DialogAssembleStr(sStringID, sParam);
		break;
		case "ranger_career":
			if (iArgument2 == 0)
			{
				sWho = XI_ConvertString("whotrader");
			}
			else
			{
				sWho = XI_ConvertString("whocorsair");
			}
			sName = GetCharacterFullName(characters[iArgument1].id);
			FormatNationString(iArgument2, 1, &sParam);

			sParam = DialogAddParamToStr(sParam, "sWho", sWho);
			sParam = DialogAddParamToStr(sParam, "sCharName", sName);

			sStringID = "SelectRangeCareerRumour" + rand(2);
			sResult = DialogAssembleStr(sStringID, sParam);
		break;
		case "colony_occupation":
			FormatNationString(iArgument1, 2, &sParam);
			FormatNationString(iArgument2, 1, &sParam);

			FormatColonyString(iArgument3, 1, &sParam);

			sStringID = "SelectColonyOccupationRumour" + rand(2);
			sResult = DialogAssembleStr(sStringID, sParam);
		break;
		case "colony_captured":
			iInfoColony = iArgument3;
			sTypeInfo = "nation";
			FormatNationString(iArgument2, 1, &sParam);
			FormatNationString(iArgument3, 2, &sParam);

			FormatColonyString(iArgument1, 1, &sParam);

			sStringID = "SelectColonyCapturedRumour" + rand(2);
			sResult = DialogAssembleStr(sStringID, sParam);
		break;
		case "colony_robbing":
			FormatNationString(iArgument1, 1, &sParam);
			FormatNationString(iArgument2, 2, &sParam);

			FormatColonyString(iArgument3, 1, &sParam);

			sStringID = "SelectColonyRobbingRumour" + rand(2);
			sResult = DialogAssembleStr(sStringID, sParam);
		break;
		case "colony_destroy":
			FormatNationString(iArgument1, 1, &sParam);
			FormatNationString(iArgument2, 2, &sParam);

			FormatColonyString(iArgument3, 1, &sParam);

			sStringID = "SelectColonyDestroyRumour" + rand(2);
			sResult = DialogAssembleStr(sStringID, sParam);
		break;
		case "colony_defend":
			FormatNationString(iArgument1, 1, &sParam);
			FormatNationString(iArgument2, 2, &sParam);

			FormatColonyString(iArgument3, 1, &sParam);

			sStringID = "SelectColonyDefendRumour" + rand(2);
			sResult = DialogAssembleStr(sStringID, sParam);
		break;
		case "trade_up":
			sGood = XI_ConvertString(Goods[iArgument1].name);
			sGoodGen = XI_ConvertString(Goods[iArgument1].name + "Gen");
			sGoodAcc = XI_ConvertString(Goods[iArgument1].name + "Acc");
			sMoney = FormatMoneyString(iArgument2);

			sParam = DialogAddParamToStr(sParam, "sGood", sGood);
			sParam = DialogAddParamToStr(sParam, "sGoodGen", sGoodGen);
			sParam = DialogAddParamToStr(sParam, "sGoodAcc", sGoodAcc);
			sParam = DialogAddParamToStr(sParam, "sMoney", sMoney);

			sStringID = "SelectPriceUpRumour" + rand(2);
			sResult = DialogAssembleStr(sStringID, sParam);
		break;
		case "trade_down":
			sGood = XI_ConvertString(Goods[iArgument1].name);
			sGoodGen = XI_ConvertString(Goods[iArgument1].name + "Gen");
			sGoodAcc = XI_ConvertString(Goods[iArgument1].name + "Acc");
			sMoney = FormatMoneyString(iArgument2);

			sParam = DialogAddParamToStr(sParam, "sGood", sGood);
			sParam = DialogAddParamToStr(sParam, "sGoodGen", sGoodGen);
			sParam = DialogAddParamToStr(sParam, "sGoodAcc", sGoodAcc);
			sParam = DialogAddParamToStr(sParam, "sMoney", sMoney);

			sStringID = "SelectPriceDownRumour" + rand(2);
			sResult = DialogAssembleStr(sStringID, sParam);
		break;
		case "war_begin":
			FormatNationString(iArgument1, 1, &sParam);
			FormatNationString(iArgument2, 2, &sParam);

			sStringID = "SelectWarBeginRumour" + rand(2);
			sResult = DialogAssembleStr(sStringID, sParam);
		break;
		case "war_end":
			FormatNationString(iArgument1, 1, &sParam);
			FormatNationString(iArgument2, 2, &sParam);

			sStringID = "SelectWarEndRumour" + rand(2);
			sResult = DialogAssembleStr(sStringID, sParam);
		break;
		case "friend_end":
			FormatNationString(iArgument1, 1, &sParam);
			FormatNationString(iArgument2, 2, &sParam);

			sStringID = "SelectFriendshipEndRumour" + rand(2);
			sResult = DialogAssembleStr(sStringID, sParam);
		break;
		case "friend_begin":
			FormatNationString(iArgument1, 1, &sParam);
			FormatNationString(iArgument2, 2, &sParam);

			sStringID = "SelectFriendshipBeginRumour" + rand(2);
			sResult = DialogAssembleStr(sStringID, sParam);
		break;
		case "make_alliance":
			FormatNationString(iArgument1, 1, &sParam);
			FormatNationString(iArgument2, 2, &sParam);
			FormatNationString(iArgument3, 3, &sParam);

			sStringID = "SelectMakeAllianceRumour" + rand(2);
			sResult = DialogAssembleStr(sStringID, sParam);
		break;
		case "alliance_end":
			FormatNationString(iArgument1, 1, &sParam);
			FormatNationString(iArgument2, 2, &sParam);

			sStringID = "SelectAllianceBrokenRumour" + rand(2);
			sResult = DialogAssembleStr(sStringID, sParam);
		break;
		case "ranger_dead":
			if (iArgument2 == 0)
			{
				sWho = XI_ConvertString("whotrader");
			}
			else
			{
				sWho = XI_ConvertString("whocorsair");
			}
			sName = GetCharacterFullName(characters[iArgument1].id);

			sParam = DialogAddParamToStr(sParam, "sWho", sWho);
			sParam = DialogAddParamToStr(sParam, "sCharName", sName);

			sStringID = "SelectDeathOfRangerRumour" + rand(2);
			sResult = DialogAssembleStr(sStringID, sParam);
		break;
		case "ranger_captured":
			if (iArgument3 == 0)
			{
				sWho = XI_ConvertString("whotrader");
			}
			else
			{
				sWho = XI_ConvertString("whocorsair");
			}
			sName = GetCharacterFullName(characters[iArgument1].id);

			FormatColonyString(iArgument2, 1, &sParam);

			sStringID = "SelectRangerCapturedRumour" + rand(2);
			sResult = DialogAssembleStr(sStringID, sParam);
		break;
		case "ranger_uncaptured":
			if (iArgument3 == 0)
			{
				sWho = XI_ConvertString("whotrader");
			}
			else
			{
				sWho = XI_ConvertString("whotrader");
			}
			sName = GetCharacterFullName(characters[iArgument1].id);

			FormatColonyString(iArgument2, 1, &sParam);

			sParam = DialogAddParamToStr(sParam, "sWho", sWho);
			sParam = DialogAddParamToStr(sParam, "sCharName", sName);
			sStringID = "SelectRangerUnCapturedRumour" + rand(2);
			sResult = DialogAssembleStr(sStringID, sParam);
		break;
		case "disease_begin":
			FormatColonyString(iArgument1, 1, &sParam);
			FormatNationString(iArgument2, 1, &sParam);


			sStringID = "SelectDiseaseBeginRumour" + rand(2);
			sResult = DialogAssembleStr(sStringID, sParam);
		break;
		case "disease_end":
			FormatColonyString(iArgument1, 1, &sParam);
			FormatNationString(iArgument2, 1, &sParam);


			sStringID = "SelectDiseaseEndRumour" + rand(2);
			sResult = DialogAssembleStr(sStringID, sParam);
		break;
		case "colony_colonists":
			FormatColonyString(iArgument1, 1, &sParam);
			FormatNationString(iArgument2, 1, &sParam);

			sStringID = "SelectColonistReachedRumour" + rand(2);
			sResult = DialogAssembleStr(sStringID, sParam);
		break;
		case "history_event":
			sResult = HistoryEvents[iArgument1].text;
		break;
		case "ship_info":
			FormatColonyString(iArgument2, 1, &sParam);

			sShipName = characters[iArgument1].ship.name;

			FormatColonyString(iArgument3, 2, &sParam);

			sParam = DialogAddParamToStr(sParam, "sShipName", sShipName);

			sStringID = "SelectShipInfoRumour" + rand(2);
			sResult = DialogAssembleStr(sStringID, sParam);

			Rumours[iNumber].area = "tavern";
			Rumours[iNumber].isquest = 1;
		break;
	}

	Rumours[iNumber].text = sResult;
	Rumours[iNumber].date = environment.date.day + " " + XI_ConvertString("target_month_" + environment.date.month) + " " + environment.date.year + ".";
	Rumours[iNumber].day = environment.date.day;
	Rumours[iNumber].month = environment.date.month;
	Rumours[iNumber].year = environment.date.year;
	if(iInfoColony != -1)
	{
		Rumours[iNumber].colony = iInfoColony;
	}
	if(sType != "-1")
	{
		Rumours[iNumber].colony.fieldupdate = sTypeInfo;
	}

	RumoursQuantity ++;
}


int CheckRumourAoPPosition()// Dernier
{
    int itext;
	for(int i = 0; i < MAX_RUMOURS; i++)
	{
		if(i != itext)//if (!CheckAttribute(&Rumours[i], "text"))

		{
			return i;
		}
	}
	return -1;
}

void EmptyAllRumours()
{
int itext, iquestbook, idate, iisquest;
	for (int i=0; i<MAX_RUMOURS; i++)
	{
        DeleteAttribute(itext, "text");
		DeleteAttribute(iquestbook, "questbook");
		DeleteAttribute(idate, "date");
		DeleteAttribute(iisquest, "isquest");
	}
}

int SelectRumourAoP() // Philippe 11.01
{
int itext, iquestbook;
	int k = 0;
	int Rum[MAX_RUMOURS];

	for (int i = 0; i < RumoursQuantity; i++)
	{
		 if((i != itext) && (i != "questbook"))
		{
			Rum[k] = i;
			k++;
		}
	}
	if (k > 0)
	{
		k = rand(k-1);
		return Rum[k];
	}
	return -1;
}

void CheckColonyInfoUpdate(int iRumour)
{
	int iColony;
	string sFieldForUpdate;
	if(i != icolony)      //if(CheckAttribute(&Rumours[iRumour], "colony"))
	{
		iColony = sti(iRumour.colony);

		if(i != "colony.fieldupdate") && iColony > 0);
		{
			sFieldForUpdate = iRumour.colony.fieldupdate;

			if!(sti(iRumour.colony) = sFieldForUpdate)
			{
				//coloniesInfo[iColony].(sFieldForUpdate) = colonies[iColony].(sFieldForUpdate);
                                iColony = ColoniesInfo[iColony].sFieldForUpdate;
			}
		}
	}
}

void AddRumourAoPToQuestBook(int step)// Dernier
{
	rumours[step].questbook = "marked";
}

string SelectNews(int step)
{
	string sText;


	if (step >= MAX_RUMOURS)
	{
		step = MAX_RUMOURS - 1;
	}

	if (!CheckAttribute(&Rumours[step], "text"))
	{
		if(rumours[step].questbook == "marked")
		{
			sText = XI_ConvertString("Speak_No_News");
		}
		else
		{
			sText = sText + Rumours[step].text;

			AddRumourToQuestBook(sti(step));
		}
	}
	else
	{
		sText = sText + Rumours[step].text;

		AddRumourToQuestBook(sti(step));
	}

	return sText;
}
