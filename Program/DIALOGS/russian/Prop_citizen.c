#include "DIALOGS\$language\Rumours\Common_rumours.c"
#include "TEXT\$language\DIALOGS\Prop_citizen.h"
//Derived from Citizen, Brothel and Waitress
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}

    ProcessCommonDialogRumors(NPChar, Link, NextDiag);
    int iTest, iTemp;
    iTest = FindColony(NPChar.City);
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
	    case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "fight":
            LAi_group_Attack(NPChar, Pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "First time":
			//#20170926-01 Street propositions
			if (CheckAttribute(NPChar, "quest.proposition"))
            {
                if (pchar.questTemp.different == "FackStreet_toRoom" || pchar.questTemp.different == "FackStreet_toRoomUp")
                {
                    dialog.text = DLG_TEXT_BASE[224];
                    link.l1 = DLG_TEXT_BASE[225];
                    link.l1.go = "exit";
                }
                //Remove, as culprit disappears
                //if (pchar.questTemp.different == "FackStreet_noMoney" || pchar.questTemp.different == "FackStreet_fighted")
                //{
                //    dialog.text = DLG_TEXT_BASE[2];
                //    link.l1 = DLG_TEXT_BASE[3] + pchar.questTemp.different.FackStreet.Name + DLG_TEXT_BASE[4];
                //    link.l1.go = "Love_IDN";
                //}
                else {
                    if (NPChar.quest.proposition == "FackStreet_facking")
                    {
                        dialog.text = DLG_TEXT_BASE[230];
                        link.l1 = DLG_TEXT_BASE[231];
                        link.l1.go = "exit";
                    }
                    if (NPChar.quest.proposition == "FackStreet_fackNoMoney")
                    {
                        dialog.text = DLG_TEXT_BASE[276];
                        link.l1 = DLG_TEXT_BASE[277];
                        link.l1.go = "Love_IDN_1";
                    }
                }
                break;
            }
            if(!CheckAttribute(NPChar, "quest.propositioned") || NPChar.quest.propositioned == "0")
			{
				NPChar.quest.propositioned = "1";
                if(rand(1)==0) {
                    dialog.text = DLG_TEXT_BASE[222];
                    if(rand(1) == 0)
                        npchar.quest.choice = 0;
                    else
                        npchar.quest.choice = 2;
                }
                else {
                    dialog.text = DLG_TEXT_BASE[223];
                    npchar.quest.choice = 1;  //"Promise" similar to Brothel choice
                }
                link.l1 = DLG_TEXT_BASE[226];
                link.l1.go = "exit";
                //#20171229-01 Fix nightguard
                if (!CheckAttribute(pchar, "questTemp.different.Church_NightGuard") && pchar.questTemp.different == "free" && !CheckAttribute(pchar, "questTemp.different.FackStreet") && Pchar.questTemp.CapBloodLine != true )
                {
                    link.l2 = DLG_TEXT_BASE[227];
                    link.l2.go = "Love_1";
                }
				break;
			}
			if (sti(NPChar.nation) == PIRATE)
			{
				if (sti(rColony.HeroOwn) == true)
				{
				    dialog.text = RandPhraseSimple(DLG_TEXT_BASE[3], DLG_TEXT_BASE[4]);
					link.l1 = RandPhraseSimple(DLG_TEXT_BASE[5], DLG_TEXT_BASE[6]);
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple(DLG_TEXT_BASE[7], DLG_TEXT_BASE[8]);
					link.l2.go = "quests";
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple(DLG_TEXT_BASE[9], DLG_TEXT_BASE[10]);
							link.l3.go = "LoanForAll";
						}
					}
					break;
				}
				else
				{
				    dialog.text = RandPhraseSimple(DLG_TEXT_BASE[11], DLG_TEXT_BASE[12]);
					link.l1 = RandPhraseSimple(DLG_TEXT_BASE[13], DLG_TEXT_BASE[14]);
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple(DLG_TEXT_BASE[15], DLG_TEXT_BASE[16]);
					link.l2.go = "quests";
					if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
		            {
		                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
		                {
							link.l3 = RandPhraseSimple(DLG_TEXT_BASE[17], DLG_TEXT_BASE[18]);
							link.l3.go = "LoanForAll";
						}
					}
					break;
				}
			}
            if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";

				dialog.Text =NPCharRepPhrase(npchar,
                                LinkRandPhrase(DLG_TEXT_BASE[19], DLG_TEXT_BASE[20], DLG_TEXT_BASE[21])
                                +GetFullName(npchar)
                                +LinkRandPhrase(DLG_TEXT_BASE[22], DLG_TEXT_BASE[23]
                                +NPCharSexPhrase(NPChar, DLG_TEXT_BASE[24], DLG_TEXT_BASE[25])
                                +DLG_TEXT_BASE[26], DLG_TEXT_BASE[27]),

        		                LinkRandPhrase(DLG_TEXT_BASE[28] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[29] + GetFullName(npchar) + DLG_TEXT_BASE[30],
                                 DLG_TEXT_BASE[31] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[32] + GetFullName(npchar) + DLG_TEXT_BASE[33],
                                 DLG_TEXT_BASE[34] + GetAddress_Form(NPChar) + DLG_TEXT_BASE[35] + GetFullName(npchar) + DLG_TEXT_BASE[36]));

				Link.l1 = pcharrepphrase(
                                LinkRandPhrase(DLG_TEXT_BASE[37], DLG_TEXT_BASE[38], DLG_TEXT_BASE[39]) + DLG_TEXT_BASE[40]+ GetFullName(Pchar)+ LinkRandPhrase(DLG_TEXT_BASE[41]+NPCharSexPhrase(NPChar,"",DLG_TEXT_BASE[42])+DLG_TEXT_BASE[43]+NPCharSexPhrase(NPChar,DLG_TEXT_BASE[44],"?"), DLG_TEXT_BASE[45], DLG_TEXT_BASE[46]),
                                LinkRandPhrase(DLG_TEXT_BASE[47] + GetFullName(Pchar) + DLG_TEXT_BASE[48], DLG_TEXT_BASE[49] + GetFullName(Pchar) + ".", DLG_TEXT_BASE[50] + GetFullName(Pchar)));

                //LinkRandPhrase(DLG_TEXT_BASE[51] + GetFullName(Pchar) + DLG_TEXT_BASE[52], DLG_TEXT_BASE[53] + GetFullName(Pchar) + ".", DLG_TEXT_BASE[54] + GetFullName(Pchar));
				Link.l1.go = "Meeting";
			}
			else
			{
				link.l1 = PCharRepPhrase(DLG_TEXT_BASE[55], DLG_TEXT_BASE[56]);
				link.l1.go = "new question";
 				link.l2 = RandPhraseSimple(DLG_TEXT_BASE[57], DLG_TEXT_BASE[58]);
				link.l2.go = "quests";
				if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
	            {
	                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
	                {
						link.l3 = RandPhraseSimple(DLG_TEXT_BASE[59], DLG_TEXT_BASE[60]);
						link.l3.go = "LoanForAll";
					}
				}
				if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
	            {
					link.l4 = NPCharSexPhrase(npchar, LinkRandPhrase(DLG_TEXT_BASE[61] + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + "!",
						DLG_TEXT_BASE[62] + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + DLG_TEXT_BASE[63],
						DLG_TEXT_BASE[64] + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname + DLG_TEXT_BASE[65]),
						LinkRandPhrase(DLG_TEXT_BASE[66] + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + "!",
						DLG_TEXT_BASE[67] + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + DLG_TEXT_BASE[68],
						DLG_TEXT_BASE[69] + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname + DLG_TEXT_BASE[70]));
					link.l4.go = "SitySpy";
				}
				dialog.Text = NPCharRepPhrase(npchar,
		                PCharRepPhrase(LinkRandPhrase(DLG_TEXT_BASE[71]+GetFullName(Pchar)
                        +DLG_TEXT_BASE[72], DLG_TEXT_BASE[73]
                        + Pchar.name, DLG_TEXT_BASE[74]
                         +GetFullName(Pchar))
                                        +LinkRandPhrase(DLG_TEXT_BASE[75], DLG_TEXT_BASE[76], DLG_TEXT_BASE[77])
                                        +LinkRandPhrase(DLG_TEXT_BASE[78], DLG_TEXT_BASE[79], DLG_TEXT_BASE[80]),
                                        LinkRandPhrase(TimeGreeting() + DLG_TEXT_BASE[81], DLG_TEXT_BASE[82]+GetAddress_Form(NPChar)+" ", DLG_TEXT_BASE[83])+GetFullName(Pchar)
                                        +LinkRandPhrase(DLG_TEXT_BASE[84], DLG_TEXT_BASE[85], DLG_TEXT_BASE[86])

                                        ),

                        PCharRepPhrase(LinkRandPhrase(DLG_TEXT_BASE[87], DLG_TEXT_BASE[88]+GetAddress_Form(NPChar)+" ", DLG_TEXT_BASE[89])
                                        +GetFullName(Pchar)
                                        +LinkRandPhrase(DLG_TEXT_BASE[90]+NPCharSexPhrase(NPChar, " ", DLG_TEXT_BASE[91])+DLG_TEXT_BASE[92],
                                                         DLG_TEXT_BASE[93]+NPCharSexPhrase(NPChar, " ", DLG_TEXT_BASE[94])+DLG_TEXT_BASE[95], DLG_TEXT_BASE[96])
                                        +LinkRandPhrase(DLG_TEXT_BASE[97], DLG_TEXT_BASE[98], DLG_TEXT_BASE[99]+NPCharSexPhrase(NPChar, DLG_TEXT_BASE[100], DLG_TEXT_BASE[101])),
                                        LinkRandPhrase(TimeGreeting() + DLG_TEXT_BASE[102] + GetFullName(Pchar) + DLG_TEXT_BASE[103],
                                        DLG_TEXT_BASE[104] + GetFullName(Pchar) + DLG_TEXT_BASE[105],
                                        DLG_TEXT_BASE[106] + GetAddress_Form(NPChar) + " " + Pchar.lastname + DLG_TEXT_BASE[107]))
                                        );
	   			link.l5 = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[108], DLG_TEXT_BASE[109]),
                                        RandPhraseSimple(DLG_TEXT_BASE[110], DLG_TEXT_BASE[111]));
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		//#20170926-01 Street propositions
		case "Love_1":
			dialog.text = DLG_TEXT_BASE[228];
			link.l1 = DLG_TEXT_BASE[229];
			link.l1.go = "exit";
			pchar.questTemp.different = "FackStreet_toRoom";
			npchar.quest.proposition = "FackStreet_toRoom";
			SetTimerFunction("StreetFack_null", 0, 0, 1);

			int nChance = 40; //Base chance for possible kick is 40 percents
			nChance += (sti(pchar.rank) / 2);
            nChance += (GetSummonSkillFromName(pchar, SKILL_FORTUNE) / 5); //'Luck' improves chance
            nChance += (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) / 10); //'Authority' improves chance
            if(rand(1) == 0)
                pchar.questTemp.different.FackStreet.stay = true;
            if(rand(99) < nChance) {
                pchar.questTemp.different.FackStreet.Kick = 1; //No steal
            }
            else {
                pchar.questTemp.different.FackStreet.Kick = cRand(2);
            }
			pchar.questTemp.different.FackStreet.Name = GetFullName(npchar);
            pchar.questTemp.different.FackStreet.charID = npchar.id;
			sld = GetCharacter(NPC_GenerateCharacter("StreetPropQuest", npchar.model, npchar.sex, npchar.model.animation, 5, sti(npchar.nation), 3, false));
			sld.name = npchar.name;
			sld.lastname = npchar.lastname;
			sld.dialog.Filename = "Prop_citizen.c";
			sld.dialog.currentnode = "PropositionGo";
			sld.City = npchar.city;
			sld.CityType = npchar.CityType;
			sld.quest.choice = npchar.quest.choice;
			Pchar.quest.StreetFack_inRoom.win_condition.l1 = "location";
			Pchar.quest.StreetFack_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			Pchar.quest.StreetFack_inRoom.function = "StreetFack_inRoom";
			ChangeCharacterReputation(pchar, -1);
		break;
		case "PropositionGo":
			dialog.text = DLG_TEXT_BASE[252];
			link.l1 = DLG_TEXT_BASE[253];
			link.l1.go = "PropositionGo_1";
		break;
		case "PropositionGo_1":
			dialog.text = DLG_TEXT_BASE[254];
			link.l1 = DLG_TEXT_BASE[255];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("StreetFack_fack");
		break;
		case "PropositionBerglar":
			dialog.text = DLG_TEXT_BASE[240];
			link.l1 = DLG_TEXT_BASE[241];
			link.l1.go = "PropositionBerglar_1";
		break;
		case "PropositionBerglar_1":
			dialog.text = DLG_TEXT_BASE[242];
			link.l1 = DLG_TEXT_BASE[243] + pchar.questTemp.different.FackStreet.Name + DLG_TEXT_BASE[244];
			link.l1.go = "PropositionBerglar_2";
		break;
		case "PropositionBerglar_2":
			dialog.text = DLG_TEXT_BASE[245];
			link.l1 = DLG_TEXT_BASE[246];
			link.l1.go = "PropositionBerglar_fight";
			link.l2 = DLG_TEXT_BASE[247];
			link.l2.go = "PropositionBerglar_take";
		break;
		case "PropositionBerglar_take":
			dialog.text = DLG_TEXT_BASE[248];
			link.l1 = DLG_TEXT_BASE[249];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("StreetFack_outRoom");
		break;
		case "PropositionBerglar_fight":
			dialog.text = DLG_TEXT_BASE[250];
			link.l1 = DLG_TEXT_BASE[251];
			link.l1.go = "exit";
			AddDialogExitQuestFunction("StreetFack_fight");
		break;
		//case "Love_IDN":
		//	dialog.text = DLG_TEXT_BASE[278];
		//	link.l1 = DLG_TEXT_BASE[279];
		//	link.l1.go = "exit";
		//break;
        case "Love_IDN_1":
			dialog.text = DLG_TEXT_BASE[278];
			link.l1 = DLG_TEXT_BASE[279];
			link.l1.go = "Love_IDN_2";
		break;
        case "Love_IDN_2":
			dialog.text = DLG_TEXT_BASE[280];
			link.l1 = DLG_TEXT_BASE[281];
			link.l1.go = "exit";
		break;
		//If proposition stays in room
		case "Proposition_ReadyFack":
			if (!CheckAttribute(npchar, "quest.choice")) npchar.quest.choice = 0;
			switch(npchar.quest.choice)
			{
				case "0":
					dialog.text = RandPhraseSimple(DLG_TEXT_BASE[232], DLG_TEXT_BASE[233]);
					Link.l1 = RandPhraseSimple(DLG_TEXT_BASE[234], DLG_TEXT_BASE[235]);
				break;
				case "1":
					dialog.text = DLG_TEXT_BASE[236];
					Link.l1 = DLG_TEXT_BASE[237];
				break;
				case "2":
					dialog.text = DLG_TEXT_BASE[238];
					Link.l1 = DLG_TEXT_BASE[239];
				break;
			}
			Link.l1.go = "exit";

			//if (!CheckAttribute(npchar, "quest.sexHappend")) npchar.quest.sexHappend = 1;
			//else npchar.quest.sexHappend = sti(npchar.quest.sexHappend) + 1;
			Pchar.quest.StreetProp_checkVisitTime.win_condition.l1 = "ExitFromLocation";
			Pchar.quest.StreetProp_checkVisitTime.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			Pchar.quest.StreetProp_checkVisitTime.win_condition = "StreetProp_checkVisitTime";
			NextDiag.TempNode = "Proposition_AfterSex";
            pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1;
            pchar.questTemp.different = "FackStreet_facking";
			AddDialogExitQuest("PlaySex_1");
			if (CheckNPCQuestDate(pchar, "BrothelSex"))
			{
				AddCharacterHealth(pchar, 5);
				SetNPCQuestDate(pchar, "BrothelSex");
			}
			ChangeCharacterReputation(pchar, -1);
			AddCharacterExpToSkill(pchar, "Leadership", 15);
			AddCharacterExpToSkill(pchar, "Fencing", -15);
			AddCharacterExpToSkill(pchar, "Pistol", -15);
		break;
		case "Proposition_AfterSex":
			switch(npchar.quest.choice)
			{
				case "0":
					dialog.text = LinkRandPhrase(DLG_TEXT_BASE[256], DLG_TEXT_BASE[257], DLG_TEXT_BASE[258]);
					Link.l1 = RandPhraseSimple(DLG_TEXT_BASE[259], DLG_TEXT_BASE[260]);
					Link.l1.go = "exit";
				break;
				case "1":
                    //#20171008-01 Brothel adjust rand(4)+5
					//if (sti(npchar.quest.sexHappend) > (rand(3)+3) && sti(pchar.questTemp.HorseLoot) < 3 && !CheckAttribute(npchar, "questTemp.HorseLoot"))
					//{
					//	dialog.text = DLG_TEXT_BASE[261];
					//	Link.l1 = DLG_TEXT_BASE[262];
					//	Link.l1.go = "HorseQuest";
					//}
					//else
                    dialog.text = LinkRandPhrase(DLG_TEXT_BASE[263], DLG_TEXT_BASE[264], DLG_TEXT_BASE[265]);
                    Link.l1 = RandPhraseSimple(DLG_TEXT_BASE[266], DLG_TEXT_BASE[267]);
                    Link.l1.go = "exit";

				break;
				case "2":
					dialog.text = RandPhraseSimple(DLG_TEXT_BASE[268], DLG_TEXT_BASE[269]);
					Link.l1 = RandPhraseSimple(DLG_TEXT_BASE[270], DLG_TEXT_BASE[271]);
					Link.l1.go = "exit";
				break;
			}
			NextDiag.TempNode = "Proposition_AfterSex_2";
			LAi_SetCitizenType(npchar);
		break;
        case "Proposition_AfterSex_2":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[272], DLG_TEXT_BASE[273], DLG_TEXT_BASE[274]);
			Link.l1 = DLG_TEXT_BASE[275];
			Link.l1.go = "exit";
			NextDiag.TempNode = "Proposition_AfterSex_2";
		break;
		case "Meeting":
		    dialog.Text  = NPCharRepPhrase(npchar, LinkRandPhrase(DLG_TEXT_BASE[112] + GetFullName(Pchar)+"?",
                                                                    DLG_TEXT_BASE[113] + PChar.name+"?",
                                                                    DLG_TEXT_BASE[114] + GetFullName(Pchar)+".")
                                                                     + DLG_TEXT_BASE[115],
                                                    LinkRandPhrase(DLG_TEXT_BASE[116] + PChar.name,
                                                                    DLG_TEXT_BASE[117]+NPCharSexPhrase(NPChar, " ", DLG_TEXT_BASE[118])+DLG_TEXT_BASE[119] + GetAddress_Form(NPChar) + " " + PChar.lastname,
                                                                     DLG_TEXT_BASE[120] + PChar.name) + DLG_TEXT_BASE[121]);

            link.l1 = PCharRepPhrase(DLG_TEXT_BASE[122], DLG_TEXT_BASE[123]);
			link.l1.go = "new question";
            Link.l2 = RandPhraseSimple(DLG_TEXT_BASE[124], DLG_TEXT_BASE[125]);
			Link.l2.go = "quests";
			if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
            {
                if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
                {
					link.l3 = RandPhraseSimple(DLG_TEXT_BASE[126], DLG_TEXT_BASE[127]);
					link.l3.go = "LoanForAll";
				}
			}
			if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
	        {
				link.l4 = NPCharSexPhrase(npchar, LinkRandPhrase(DLG_TEXT_BASE[128] + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + "!",
					DLG_TEXT_BASE[129] + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + DLG_TEXT_BASE[130],
					DLG_TEXT_BASE[131] + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname + DLG_TEXT_BASE[132]),
					LinkRandPhrase(DLG_TEXT_BASE[133] + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + "!",
					DLG_TEXT_BASE[134] + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city+"Gen") + DLG_TEXT_BASE[135],
					DLG_TEXT_BASE[136] + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname + DLG_TEXT_BASE[137]));
				link.l4.go = "SitySpy";
			}
			Link.l5 = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[138], DLG_TEXT_BASE[139]),
                                        RandPhraseSimple(DLG_TEXT_BASE[140], DLG_TEXT_BASE[141]));
			Link.l5.go = "exit";
		break;
		case "new question":
            dialog.text = NPCharRepPhrase(npchar,
		                PCharRepPhrase(LinkRandPhrase(DLG_TEXT_BASE[142]+NPCharSexPhrase(NPChar, " ", DLG_TEXT_BASE[143])+DLG_TEXT_BASE[144], DLG_TEXT_BASE[145], DLG_TEXT_BASE[146] + PChar.name + "?"),
                                        LinkRandPhrase(DLG_TEXT_BASE[147], DLG_TEXT_BASE[148]+PChar.name+DLG_TEXT_BASE[149], DLG_TEXT_BASE[150])),
		                PCharRepPhrase(LinkRandPhrase(DLG_TEXT_BASE[151]+ GetAddress_Form(NPChar) + "?", DLG_TEXT_BASE[152], DLG_TEXT_BASE[153]),
                                        LinkRandPhrase(DLG_TEXT_BASE[154]+NPCharSexPhrase(NPChar, " ", DLG_TEXT_BASE[155])+DLG_TEXT_BASE[156] + GetAddress_Form(NPChar) + " " + PChar.lastname + DLG_TEXT_BASE[157],
                                                        DLG_TEXT_BASE[158] + GetAddress_Form(NPChar) + "?",
                                                        DLG_TEXT_BASE[159]))
                            );

            link.l1 = LinkRandPhrase (DLG_TEXT_BASE[160],
                                    DLG_TEXT_BASE[161],
                                    DLG_TEXT_BASE[162]);
			link.l1.go = "rumours_citizen";
			link.l2 = LinkRandPhrase(DLG_TEXT_BASE[163], DLG_TEXT_BASE[164], DLG_TEXT_BASE[165]);
			link.l2.go = "town";
			if(Rand(1)==0)
			{
				link.l3 = LinkRandPhrase(DLG_TEXT_BASE[166], DLG_TEXT_BASE[167], DLG_TEXT_BASE[168]);
				link.l3.go = "info";
			}
			else
			{
				link.l3 = DLG_TEXT_BASE[169];
				link.l3.go = "colony";
			}
            link.l4 = RandPhraseSimple(DLG_TEXT_BASE[170], DLG_TEXT_BASE[171]);
			link.l4.go = "quests";
			link.l5 = PCharRepPhrase(RandPhraseSimple(DLG_TEXT_BASE[172], DLG_TEXT_BASE[173]),
                                        RandPhraseSimple(DLG_TEXT_BASE[174], DLG_TEXT_BASE[175]));
			link.l5.go = "exit";
		break;
		case "colony":
			dialog.text = LinkRandPhrase(DLG_TEXT_BASE[176],
                           DLG_TEXT_BASE[177], DLG_TEXT_BASE[178]);
            switch(Rand(1))
			{
				case 0:
					link.l1 = DLG_TEXT_BASE[179];
					link.l1.go = "colony_town";
				break;

				case 1:
					link.l1 = DLG_TEXT_BASE[180];
					link.l1.go = "fort";
				break;
            }
			link.l2 = DLG_TEXT_BASE[181];
			link.l2.go = "new question";
		break;
		case "colony_town":
            dialog.text = DLG_TEXT_BASE[182];
			link.l1 = DLG_TEXT_BASE[183];
		    link.l1.go = "exit";
		break;
		case "fort":
            dialog.text = DLG_TEXT_BASE[184];
			link.l1 = DLG_TEXT_BASE[185];
		    link.l1.go = "exit";
		break;
		case "SitySpy":
			dialog.text = NPCStringReactionRepeat(NPCharSexPhrase(npchar, DLG_TEXT_BASE[186], DLG_TEXT_BASE[187]),
				NPCharSexPhrase(npchar, DLG_TEXT_BASE[188], DLG_TEXT_BASE[189]),
				NPCharSexPhrase(npchar, DLG_TEXT_BASE[190], DLG_TEXT_BASE[191]),
				NPCharSexPhrase(npchar, DLG_TEXT_BASE[192], DLG_TEXT_BASE[193]), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_BASE[194], DLG_TEXT_BASE[195],
                      DLG_TEXT_BASE[196], DLG_TEXT_BASE[197], npchar, Dialog.CurrentNode);
		    link.l1.go = DialogGoNodeRepeat("SitySpy_1", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
			int num = FindNearCharacters(npchar, 20.0, -1.0, -1.0, 1.0, false, true);
			if(num > 0)
			{
				for(int i = 0; i < num; i++)
				{
					iTemp = chrFindNearCharacters[i].index;
					if (CheckAttribute(&characters[iTemp], "CityType"))
					{
						if(characters[iTemp].CityType == "soldier" || characters[iTemp].CityType == "citizen")
						{
							break;
						}
					}
				}
				pchar.GenQuest.SeekSpy.Idx = chrFindNearCharacters[i].index;
				pchar.GenQuest.SeekSpy.Type = characters[sti(pchar.GenQuest.SeekSpy.Idx)].chr_ai.type;
				pchar.GenQuest.SeekSpy.BaseIdx = npchar.index;
			}
		break;
		case "SitySpy_1":
			if (sti(pchar.GenQuest.SeekSpy.Idx) == -1 || sti(pchar.GenQuest.SeekSpy.Idx) == 1)
			{
				dialog.text = DLG_TEXT_BASE[198],
				link.l1 = DLG_TEXT_BASE[199];
				link.l1.go = "exit";
				break;
			}
			dialog.text = DLG_TEXT_BASE[200] + NPCharSexPhrase(npchar, GetFullName(&characters[sti(pchar.GenQuest.SeekSpy.Idx)]) + DLG_TEXT_BASE[201] + NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.Idx)], DLG_TEXT_BASE[202], DLG_TEXT_BASE[203]) + DLG_TEXT_BASE[204],
				DLG_TEXT_BASE[205] + NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.Idx)], GetAddress_Form(NPChar) + " " + characters[sti(pchar.GenQuest.SeekSpy.Idx)].lastname, GetFullName(&characters[sti(pchar.GenQuest.SeekSpy.Idx)])) + DLG_TEXT_BASE[206]);
			link.l1 = DLG_TEXT_BASE[207];
		    link.l1.go = "SitySpy_2";
			sld = &characters[sti(pchar.GenQuest.SeekSpy.Idx)];
			sld.dialog.currentnode = "SeekSpy_Checking";
			pchar.GenQuest.SeekSpy.time = 4.0;
			if (sld.chr_ai.type == "merchant") pchar.GenQuest.SeekSpy.time = 0.0;
            LAi_SetActorTypeNoGroup(sld);
		break;
		case "SitySpy_2":
			sld = &characters[sti(pchar.GenQuest.SeekSpy.Idx)];
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorTurnToCharacter(npchar, sld);
			LAi_ActorDialog(sld, pchar, "", stf(pchar.GenQuest.SeekSpy.time), 0);
			DialogExit();
		break;
		case "SeekSpy_Checking":
			dialog.text = DLG_TEXT_BASE[208] + NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)], DLG_TEXT_BASE[209], DLG_TEXT_BASE[210]);
			link.l1 = RandPhraseSimple(DLG_TEXT_BASE[211], DLG_TEXT_BASE[212]);
			link.l1.go = "SeekSpy_Checking_1";
		break;
		case "SeekSpy_Checking_1":
			switch (pchar.GenQuest.SeekSpy.Type)
			{
				case "guardian": LAi_SetGuardianTypeNoGroup(npchar); break;
				case "patrol":   LAi_SetPatrolTypeNoGroup(npchar);   break;
				case "citizen":  LAi_SetCitizenTypeNoGroup(npchar);  break;
				case "merchant": LAi_SetMerchantTypeNoGroup(npchar); break;
			}
			LAi_SetCitizenTypeNoGroup(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)]);
			NextDiag.CurrentNode = "First Time";
			DialogExit();
		break;
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, DLG_TEXT_BASE[213], DLG_TEXT_BASE[214]);
				link.l1 = LinkRandPhrase(DLG_TEXT_BASE[215], DLG_TEXT_BASE[216], DLG_TEXT_BASE[217]);
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, DLG_TEXT_BASE[218], DLG_TEXT_BASE[219]);
				link.l1 = RandPhraseSimple(DLG_TEXT_BASE[220], DLG_TEXT_BASE[221]);
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
	}
}
