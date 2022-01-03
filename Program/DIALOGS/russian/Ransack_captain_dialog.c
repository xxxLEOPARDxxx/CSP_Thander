// BOAL диалог пленников - в трюме
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref offref;
    int i, cn;
    int qty;
    string attrLoc, sTmp;

	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
		case "First time":
			if (sti(NPChar.nation) == PIRATE)
			{
				dialog.text = RandSwear() + "Я Ваш пленник, " + GetAddress_Form(NPChar) + ". Но должен сказать, что " + NationNameNominative(sti(NPChar.nation)) + " никогда не выкупает своих -  каждый сам за себя.";
				link.l1 = "Н-да... На тебе не заработать, только если сдать тебя как преступника в каком-нибудь порту за выкуп.";
				link.l1.go = "offender";
				if (FindFreeRandomOfficer() > 0)
				{
					link.l2 = "Слушай, ты неплохой боец, а мне как раз нужны отчаянные головорезы. Не желаешь послужить у меня офицером?";
					link.l2.go = "free_to_officer";
				}
			}
			else
			{
				dialog.text = RandSwear() + "Я ваш пленник, " + GetAddress_Form(NPChar) + ". " + NationNameNominative(sti(NPChar.nation)) + " заплатит хорошую сумму за мою свободу.";
				if(NPChar.EncType == "trade" && FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
				{
					link.l1 = "Послушайте, в морском деле вы дока, а мне нужны опытные моряки. Не желаете послужить под моим началом?";
					link.l1.go = "free_to_officer_trader";
				}
			}
			attrLoc = Sea_FindNearColony();
			if (attrLoc != "none")
			{
                link.l3 = "Мы сейчас близ города " + GetConvertStr(attrLoc +" Town", "LocLables.txt") + ". Я "+ GetSexPhrase("мог","могла") +" бы вас тут высадить.";
			    link.l3.go = "free_withoutFee";
			}
			else
			{
                link.l3 = "Ступайте к боцману, скажите пусть выделит рундук на баке. В ближайшей бухте сойдёте на берег.";
			    link.l3.go = "free_withoutFee_2";
			}
			link.l4 = "Я думаю, из вас получится отличный раб - крепкий и послушный.";
			link.l4.go = "Slave_1";
			link.l5 = "Вы проигнорировали приказ лечь в дрейф и оказали сопротивление, за это будете казнены. Боцман уже получил соответствующие распоряжения.";
			link.l5.go = "PunishmentAction";
			link.l99 = "Я знаю.";
			link.l99.go = "exit";
			NextDiag.TempNode = "second time";
		break;

		case "second time":
			if(CheckAttribute(NPChar,"Hold_GenQuest") && !CheckAttribute(pchar,"GenQuest.Hold_GenQuest"))
			{
				switch(sti(NPChar.Hold_GenQuest.variant))
				{
					case 0: // "наводка"
						dialog.text = RandPhraseSimple("Капитан, не сочтите за дерзость, не будет ли мне позволено предложить довольно выгодный вариант моего освобождения?",
							"Я понимаю, что торговаться в моём положении неуместно, но не согласитесь ли выслушать деловое, так сказать, предложение?");
						link.l1 = "Хм, ну излагайте своё предложение.";
						link.l1.go = "free_tip_off";
					break;

					case 1:
						dialog.text = "Капитан, отпустили бы вы меня. На что я вам теперь? Ну, продадите меня работорговцам - может и получите горсть пиастров, только репутацию жестокого человека заработаете.";
						link.l1 = "Если отпущу, то вообще ничего не заработаю...";
						link.l1.go = "free_by_hoard";
						attrLoc = Sea_FindNearColony();
						if (attrLoc != "none")
						{
							link.l2 = "Вы проигнорировали приказ лечь в дрейф и оказали сопротивление, за это будете казнены. Боцман уже получил соответствующие распоряжения.";
							link.l2.go = "PunishmentAction";
						}
						else
						{
							link.l2 = "Вы так настаиваете на освобождении, что я готов пойти вам навстречу. Вы свободны - покиньте судно.";
							link.l2.go = "free_in_sea";
						}
						link.l3 = LinkRandPhrase("Не искушайте мое терпение. Вам уже повезло остаться в живых.",
							"У меня насчёт вас другие планы.","Я думаю, что вы мне еще пригодитесь.");
						link.l3.go = "exit";
					break;

					case 2: // "выкуп"
						dialog.text = "Капитан, более всего угнетает неопределённость. Разрешите узнать, какие у вас насчёт меня планы?";
						link.l1 = "Имеете конкретные предложения?";
						link.l1.go = "free_buyout";
						link.l2 = RandPhraseSimple(RandPhraseSimple("Я еще не решил"+ GetSexPhrase("","а") +", что с вами делать.","Узнаете, когда время придёт."),
							RandPhraseSimple("А какие планы? Ядро на шею и ага... Да шучу я, шучу.","Вы мой пленник, и я вправе поступить с вами, как сочту нужным, не учитывая ни вашего мнения, ни желания."));
						link.l2.go = "exit";
					break;
				}
				NextDiag.TempNode = "second time";
			}
			else
			{
				if (sti(NPChar.nation) == PIRATE)
				{
					dialog.text = "Капитан, отпустили бы вы меня по-добру, по-здорову. Чего с меня взять? Я ведь не от доброй жизни в разбой подался - ничему больше и не обучен. Думал, деньжат на старость скопить, а вышло-то вон как.";
					if (FindFreeRandomOfficer() > 0)
					{
						link.l2 = "Слушай, ты неплохой боец, а мне как раз нужны отчаянные головорезы. Не желаешь послужить у меня офицером?";
						link.l2.go = "free_to_officer";
					}
					link.l3 = LinkRandPhrase("Пощады не ждите. Много вас таких по морю рыщет, теперь на одного меньше будет.",
						"Что запричитал, 'гроза морей'? Сиди, раз попался.",
						"Сколь верёвочке не виться, а петли не миновать. Сдам тебя властям, чтоб другим неповадно было.");
					link.l3.go = "exit";
				}
				else
				{
					if(NPChar.EncType == "trade")
					{
						dialog.text = "Капитан, всеми святыми молю - отпустите с миром. Дома семья, дети малые, каково им без кормильца? Уж похоронили, наверное...";
						if (FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
						{
							link.l2 = "Послушайте, в морском деле вы дока, а мне нужны опытные моряки. Не желаете послужить под моим началом?";
							link.l2.go = "free_to_officer_trader";
						}
						link.l3 = LinkRandPhrase("У меня насчёт вас другие планы.","Я думаю, что вы мне еще пригодитесь.","Вы мой пленник, и я поступлю с вами так, как сочту нужным.");
						link.l3.go = "exit";
					}
					if(NPChar.EncType == "war")
					{
						dialog.text = RandPhraseSimple("Капитан, я своё сражение проиграл и хочу просить о снисхождении. Как великодушный человек отпустите во славу милосердия. Всё одно наказания мне не миновать - разжалуют за сдачу судна. Так хоть свободы не лишайте...",
							"Капитан, взываю к вашему великодушию! Понимаю - нет смысла требовать обращаться со мной, как с военнопленным, поэтому прошу освободить. Даю слово офицера, что впредь буду избегать встречи с вами.");
						link.l2 = LinkRandPhrase("Не искушайте мое терпение. Вам уже повезло остаться в живых.",
							RandPhraseSimple("У меня насчёт вас другие планы.","Я думаю, что вы мне еще пригодитесь."),
							RandPhraseSimple("Вы мой пленник, и я вправе поступить с вами, как сочту нужным, не учитывая ни вашего мнения, ни желания.",
							"Вы  капитан военного судна и знали на что идёте. Нечего теперь из себя святого представлять."));
						link.l2.go = "exit";
						if (isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 1)
						{
							if(sti(Items[sti(pchar.EquipedPatentId)].Nation) == sti(NPChar.nation) && FindFreeRandomOfficer() > 0)
							{
								link.l3 = "Слушай, ты неплохой боец, а мне как раз нужны отчаянные головорезы. Не желаешь послужить у меня офицером?";
								link.l3.go = "free_to_officer";
							}
						}
					}
				}
				attrLoc = Sea_FindNearColony();
				if (attrLoc != "none")
				{
					link.l4 = "Мы сейчас близ города " + GetConvertStr(attrLoc +" Town", "LocLables.txt") + ". Я "+ GetSexPhrase("мог","могла") +" бы вас тут высадить.";
					link.l4.go = "free_withoutFee";
				}
				else
				{
					if(NPChar.EncType == "trade" || NPChar.EncType == "pirate")
					{
						link.l4 = "Ступайте к боцману, скажите пусть выделит рундук на баке. В ближайшей бухте сойдёте на берег.";
						link.l4.go = "free_withoutFee_4";
					}
					else
					{
						link.l4 = "Черт с вами! Ступайте к боцману, он получит соответствующие распоряжения, вас высадят в ближайшей бухте. И помните - следующая наша встреча будет последней.";
						link.l4.go = "free_withoutFee_4";
					}
				}
				link.l5 = "Вы проигнорировали приказ лечь в дрейф и оказали сопротивление, за это будете казнены. Боцман уже получил соответствующие распоряжения.";
				link.l5.go = "PunishmentAction";
				NextDiag.TempNode = "second time";
			}
		break;

		case "offender":
			dialog.text = "Преступника? Вы, наверное, шутите, " + GetAddress_Form(NPChar) + "!";
			link.l1 = "Да какие тут шутки. Пират - он и есть пират.";
			link.l1.go = "exit";
		break;

		case "free_to_officer":
			if ((GetSummonSkillFromName(pchar, "Leadership") + 20) <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				dialog.text = "Служить у вас? Нет уж, лучше кормить акул!";
				link.l1 = "Попридержи язык, а то ведь так и сделаю.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Офицером, " + GetAddress_Form(NPChar) + "? Отказываться не стану. Дело я знаю, да и сколько можно тащить за собой якорь и ждать встречи с петлёй.";
				link.l1 = "Вот и договорились! Иди, принимай дела.";
				link.l1.go = "free_to_officer_Hire";
				link.l2 = "Не торопись, я передумал"+ GetSexPhrase("","а") +". Иметь офицером бывшего пирата - себе дороже.";
				link.l2.go = "exit";
			}
		break;

		case "free_to_officer_trader":
			if (GetSummonSkillFromName(pchar, "Leadership") <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				dialog.text = LinkRandPhrase("Это конечно лестное предложение, но я вынужден отказаться... по идейным, так сказать, соображениям.",
					"Увы, после того, что вы сделали с моими товарищами, это вряд ли возможно...",
					"Нет, капитан, после всего этого ужаса я больше не смогу. Я дал обет, что, если Пресвятая Дева услышит мои молитвы и дарует свободу, то в море я больше ни ногой.");
				link.l1 = "Ну, как знаете. Упрашивать не стану.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "А отчего же не послужить? Капитана из меня не вышло, дело своё загубил, что меня ждёт на берегу, кроме векселей и долговых расписок?.. Моряком - так моряком.";
				link.l1 = "Вот и договорились! Идите к боцману - пусть поставит вас на довольствие. После определю вам должность.";
				link.l1.go = "free_to_officer_Hire";
				link.l2 = "Не торопитесь, я передумал"+ GetSexPhrase("","а") +". Всё же судно не проходной двор.";
				link.l2.go = "exit";
			}
		break;

		case "free_to_officer_Hire":
            NPChar.Dialog.Filename = "Enc_Officer_dialog.c";
            NPChar.greeting = "Gr_Officer";
            NPChar.loyality = 5 + rand(10);
		    if (sti(NPChar.reputation) > 41)
		    {
		        NPChar.alignment = "good";
		    }
		    else
		    {
		        NPChar.alignment = "bad";
		    }
            ReleasePrisoner(NPChar); // освободили пленника
            DeleteAttribute(NPChar, "LifeDay") // постоянный
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			// тут трем накопивщиеся сабли и корабли 290704 BOAL -->
			DeleteAttribute(Npchar, "Ship");
			Npchar.Ship.Type = SHIP_NOTUSED;
            DeleteAttribute(Npchar, "Fellows"); // его офицеры
            Npchar.Fellows.Passengers.id0 = Npchar.index; // свой пассажир

			Npchar.Fellows.Passengers.boatswain = "-1";
			Npchar.Fellows.Passengers.navigator = "-1";
			Npchar.Fellows.Passengers.doctor = "-1";
			Npchar.Fellows.Passengers.cannoner = "-1";
			Npchar.Fellows.Passengers.treasurer = "-1";
			Npchar.Fellows.Passengers.carpenter = "-1";

			if(CheckAttribute(NPChar,"Hold_GenQuest")) DeleteAttribute(NPChar, "Hold_GenQuest");

			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			DialogExit();
        break;

		case "Slave_1":
			dialog.text = "Но " + GetAddress_Form(NPChar) + ", вы не можете так поступить! Я же сдался в бою на вашу милость.";
            link.l1 = "Отставить разговоры! В кандалы его.";
			link.l1.go = "Slave_2";
			link.l99 = "Ну ладно, я ещё подумаю, посидите пока...";
			link.l99.go = "exit";
		break;

		case "Slave_2":
			OfficersReaction("bad");
			ChangeCharacterReputation(pchar, -2);
            if (rand(5) == 1)
            {
    			dialog.text = "Ну уж нет!.. Я лучше покончу с собой, чем стану рабом!";
                link.l1 = "Стой! Я приказываю!.. Боцман! очистите трюм...";
    			link.l1.go = "free_in_sea_4";
			}
			else
			{
                if (rand(1) == 1)
                {
                    if (GetPrisonerQty() > 1)
                    {
                        dialog.text = "Ах ты палач! Братцы, двум смертям не бывать, а одной не миновать!";
                        link.l1 = "А вот это вы напрасно. Попытки бунта я пресекаю собственноручно и без проволочек...";
            			link.l1.go = "free_in_sea_battle_all";
                    }
					else
					{
						dialog.text = "Нет! Уж лучше смерть в бою!";
						link.l1 = "Как вам будет угодно...";
						link.l1.go = "free_in_sea_battle_1";
					}
    			}
    			else
    			{
					dialog.text = "Хорошо, я согласен. У меня просто нет другого выхода...";
                    link.l1 = "Вот и славно. Лучше быть живым рабом, чем мёртвым героем.";
        			link.l1.go = "Slave_3";
    			}
			}
		break;

		case "Slave_3":
            ReleasePrisoner(NPChar); //  пленника в рабы
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	ChangeCharacterReputation(pchar, -6);
        	DialogExit();
        	AddCharacterGoodsSimple(pchar, GOOD_SLAVES, 1);
        break;

		case "free_withoutFee":
			dialog.text = "О, " + GetAddress_Form(NPChar) + ", вы столь добры, что отпускаете меня без выкупа?";
            link.l1 = "Да, отпускаю. Вы свободны, " + GetFullName(NPChar);
			link.l1.go = "free_withoutFee_2";
			link.l99 = "Хм... да, вы правы! Ещё подумаю...";
			link.l99.go = "exit";
		break;

		case "free_withoutFee_2":
			dialog.text = "Спасибо, "+GetFullName(PChar) + "! Я буду за вас молиться.";
            link.l1 = "Ладно, ступайте, пока я не передумал"+ GetSexPhrase("","а") +".";
			link.l1.go = "free_withoutFee_3";
			OfficersReaction("good");
		break;

		case "free_withoutFee_3":
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	ChangeCharacterReputation(pchar, 2);
        	DialogExit();
        break;

		case "free_withoutFee_4":
			switch(NPChar.EncType)
			{
				case "pirate":
					dialog.text = RandPhraseSimple("Вот, спасибо, капитан. Век не забуду вашей доброты. Брошу к чертям этот промысел - наймусь баркасы чинить. Уж это-то я умею...",
						"Спасибо вам, капитан. И родная мать не смогла бы так утешить. Вот вам крест - брошу это неблагодарное занятие, в рыбаки подамся.");
					link.l1 = "Хотелось бы верить...";
				break;
				case "trade":
					dialog.text = "Даже не знаю, как вас благодарить, капитан. Уж не чаял избавления. Я всем расскажу о вашем великодушии. И клянусь, поставлю за вас свечку - дайте только до церкви добраться!";
					link.l1 = "Прощайте, и в будущем не вздумайте оказывать сопротивление. Первый же ваш выстрел - это смертный приговор и вам, и команде.";
				break;
				case "war":
					dialog.text = "Спасибо вам, капитан. Я буду за вас молиться.";
					link.l1 = "Учтите на будущее, что в следующий раз я могу быть менее благосклонн"+ GetSexPhrase("ым","ой") +".";
				break;
			}
			link.l1.go = "free_withoutFee_3";
		break;

		case "free_in_sea_battle_1":
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], false);
            LAi_SetFightMode(Pchar, true);
            LAi_SetWarriorType(NPChar);
            LAi_group_MoveCharacter(NPChar, LAI_GROUP_TmpEnemy);
            LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, "Prisoner", LAI_GROUP_NEITRAL);
        	DialogExit();
        break;

		case "free_in_sea_battle_all":
			//ugeen --> привет Сиварду !!! после релиза пленников кол-во пассажиров уменьшается и цикл нихрена дальше не срабатывал
			for(int j = GetPassengersQuantity(pchar) - 1; j > -1; j--)
            {
                cn = GetPassenger(pchar, j);
                if(cn != -1)
                {
                    offref = GetCharacter(cn);
                    if (CheckAttribute(offref,"prisoned"))
                    {
        	            if(sti(offref.prisoned)==true && GetRemovable(offref)) // ставим только фантомов
        	            {
                        	ReleasePrisoner(offref); // освободили пленника
							LAi_SetWarriorType(offref);
							LAi_warrior_DialogEnable(offref, false);
                            LAi_group_MoveCharacter(offref, LAI_GROUP_TmpEnemy);
                        }
                    }
                }
            }
            LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], false);
            LAi_SetFightMode(Pchar, true);
			LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
        	DialogExit();
        break;

		case "free_in_sea_4":
        	ReleasePrisoner(NPChar); // освободили пленника
            NPChar.location = "";
	        LAi_KillCharacter(NPChar);
        	DialogExit();
        break;

		case "PunishmentAction":
			dialog.text = "Но " + GetAddress_Form(NPChar) + ", вы не можете так поступить! Я же сдался в бою на вашу милость.";
			link.l1 = "После того, как погибли люди, которых вы просто предали... Боцман! приступайте.";
			link.l1.go = "PunishmentAction1";
			link.l2 = "Ну ладно, я ещё подумаю, посидите пока...";
			link.l2.go = "exit";
        break;

		case "PunishmentAction1":
			OfficersReaction("bad");
			ChangeCharacterReputation(pchar, -2);
			AddCharacterExpToSkill(Pchar, "Leadership", -150);
			if (rand(1) == 1)
            {
                if (GetPrisonerQty() > 1)
                {
                    dialog.text = "Ах ты палач! Братцы, двум смертям не бывать, а одной не миновать!";
                    link.l1 = "А вот это вы напрасно. Попытки бунта я пресекаю собственноручно и без проволочек...";
					link.l1.go = "free_in_sea_battle_all";
                }
				else
				{
					dialog.text = "Нет! Уж лучше смерть в бою!";
					link.l1 = "Как вым будет угодно...";
					link.l1.go = "free_in_sea_battle_1";
				}
    		}
			else
    		{
				dialog.text = "Разрешите хоть помолиться перед смертью...";
                link.l1 = "Молитесь...";
        		link.l1.go = "PunishmentAction2";
    		}
		break;

		case "PunishmentAction2":
        	ReleasePrisoner(NPChar); // освободили пленника
            NPChar.location = "";
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
			DialogExit();
		break;

		case "free_tip_off":
			dialog.text = "У меня есть некоторые сведения, учитывая характер вашей деятельности, они могут оказаться вам интересны. Но я хотел бы иметь гарантии, что в обмен на информацию получу свободу.";
			link.l1 = "Как я могу вам что-либо гарантировать, если не знаю о чём пойдёт речь? Наверняка ваши сведения и выеденного яйца не стоят.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "Каких же вы ждёте гарантий, кроме моего слова чести?";
			link.l2.go = "free_tip_off_1";
		break;

		case "free_tip_off_0":
			ChangeCharacterReputation(pchar, -2);
			DeleteAttribute(NPChar, "Hold_GenQuest");
			DialogExit();
		break;

		case "free_tip_off_1":
			switch(NPChar.EncType)
			{
				case "trade":
					sTmp = "Хотел и моё судно зафрахтовать, но слишком пожадничал с оплатой - я отказался.";
				break;
				case "war":
					sTmp = "Мне несколько раз приходилось сопровождать его в качестве капитана конвоя.";
				break;
				case "pirate":
					sTmp = "Я как-то подумывал его выпотрошить, но не подвернулось удобного случая.";
				break;
			}
			dialog.text = "Хорошо. Этого достаточно. Теперь к делу - в " + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.City + "Dat") + " живёт богатый купец " + NPChar.Hold_GenQuest.Name + ". " +
				"Он сколотил своё немалое состояние тем, что на судне '" + NPChar.Hold_GenQuest.ShipName + "' возит " + GetStrSmallRegister(XI_ConvertString(Goods[sti(NPChar.Hold_GenQuest.Goods)].Name + "Acc")) + " маршрутом " + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.FromCity) + " - " + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.ToCity) +". " +
				"Когда партия товара слишком велика для его трюма, он нанимает эскорт. " + sTmp + " Уверен, что эти сведения стоят для вас куда больше, чем свобода одного пленного.";
			link.l1 = "Не думаю, что они могут быть для меня полезны. Я не стану охотиться на мирных торговцев.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "Не знаю, пригодятся ли мне ваши сведения, но, согласно уговору, вы свободны. Боцман разместит вас с командой, а в ближайшем порту высадит на берег.";
			link.l2.go = "free_tip_off_2";
		break;

		case "free_tip_off_2":
			dialog.text = "Спасибо вам, капитан! Я ни секунды не сомневался в вашей честности!";
			link.l1 = RandPhraseSimple(RandPhraseSimple("Хотелось бы и о вас думать так же","К сожалению, не могу сказать того же о вас."),
				RandPhraseSimple("Учтите на будущее, что в следующий раз я могу быть менее благосклонн"+ GetSexPhrase("ым","ой") +".","Ступайте и не попадайтесь мне больше. В другой раз я не буду столь легковер"+ GetSexPhrase("ен","на") +"."));
			link.l1.go = "free_tip_off_3";
		break;

		case "free_tip_off_3":
			pchar.GenQuest.Hold_GenQuest.Goods 			= NPChar.Hold_GenQuest.Goods;
			pchar.GenQuest.Hold_GenQuest.Nation 		= NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name 			= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.ToCity 		= NPChar.Hold_GenQuest.ToCity;
			pchar.GenQuest.Hold_GenQuest.FromCity 		= NPChar.Hold_GenQuest.FromCity;
			pchar.GenQuest.Hold_GenQuest.ShipName 		= NPChar.Hold_GenQuest.ShipName;
			pchar.GenQuest.Hold_GenQuest.City 			= NPChar.Hold_GenQuest.City;
			pchar.GenQuest.Hold_GenQuest.CapName		= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.Island			= GetArealByCityName(pchar.GenQuest.Hold_GenQuest.City);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern 	= true;

			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "1");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.Hold_GenQuest.Goods)].Name + "Acc")));
			AddQuestUserData("HoldQuest", "sCityFrom", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.FromCity));
			AddQuestUserData("HoldQuest", "sCityTo", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.ToCity));
			AddQuestUserData("HoldQuest", "sShipName", pchar.GenQuest.Hold_GenQuest.ShipName);

			SetFunctionTimerCondition("Hold_GenQuest_SetMerchant_pre", 0, 0, 1+rand(2), false);
			SetFunctionTimerCondition("Hold_GenQuest_MerchantOver", 0, 0, 30, false);

            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
			NPChar.LifeDay = 0;
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	DialogExit();
		break;

		case "free_buyout":
			dialog.text = "Верно, предложение имеется. В " + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.City + "Dat") + " живёт мой хороший товарищ, " + NPChar.Hold_GenQuest.Name + " зовут, мы дело вместе начинали. " +
				"Если будем в тех местах - разыщите его. Я уверен, он не поскупится, хороший выкуп даст. А я уж с ним рассчитаюсь по-свойски... да и должок за ним.";
			link.l1 = "Товарищ, говорите? Что ж, наведаемся к вашему товарищу...";
			link.l1.go = "free_buyout1";
			link.l2 = "Вряд ли я стану искать вашего товарища, если первый же губернатор может дать за вас выкуп.";
			link.l2.go = "free_tip_off_0";
		break;

		case "free_buyout1":
			LAi_CharacterDisableDialog(NPChar);

			pchar.GenQuest.Hold_GenQuest.City 		= NPChar.Hold_GenQuest.City;
			pchar.GenQuest.Hold_GenQuest.Nation 	= NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name 		= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.CapName	= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.CapId		= NPChar.Id;
			pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;

			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "6");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Dat"));
			AddQuestUserData("HoldQuest", "sNameChar", NPChar.Hold_GenQuest.Name);
			DialogExit();
		break;

		case "free_by_hoard":
			dialog.text = "Э не скажите... Знаю я одного человека, который имеет огромное сокровище, только по своему малодушию не решается им воспользоваться.";
			link.l1 = "О чём это вы?";
			link.l1.go = "free_by_hoard1";
			link.l2 = "Оставьте свои истории, вам сейчас самое время о душе подумать.";
			link.l2.go = "free_tip_off_0";
		break;

		case "free_by_hoard1":
			dialog.text = "Я расскажу вам эту историю, которая ведёт прямиком к несметным богатствам... Только дайте слово, что отпустите меня в первой же бухте.";
			link.l1 = "Я сам" + GetSexPhrase("","а") + " буду решать что и когда с вами делать. От ваших выдумок это зависеть не будет.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "Ну рассказывайте свою историю. Даю слово...";
			link.l2.go = "free_by_hoard2";
		break;

		case "free_by_hoard2":
			dialog.text = "Верю благородному человеку! Так"+ GetSexPhrase("ой","ая") +", как вы, слово, если уж дал" + GetSexPhrase("","а") + ", то о-го-го... Пусть, хоть черти вокруг пляшут, а он" +GetSexPhrase("","а")+ " своё слово держать будет! Не правда ли капитан " + GetFullName(pchar) + "?..";
			link.l1 = "Или рассказывайте, или я отпущу вас прямо сейчас... только за борт.";
			link.l1.go = "free_by_hoard4";
		break;

		case "free_by_hoard4":
			dialog.text = "Хе-хе, удачная шутка, хе-хе... А история следующая. Живёт в " + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.City + "Dat") + " человек "+
				"по имени " + NPChar.Hold_GenQuest.Name + ", в молодости был отчаянным парнем, столько всего натворил, что и вспомнить страшно... " +
				"Так вот, как-то за бутылкой рому рассказал мне этот приятель, что, промышляя в банде " + GetName( NAMETYPE_VIP, NPChar.Hold_GenQuest.PirateName, NAME_ACC) + ", довелось ему быть свидетелем того, как пираты клад хоронили." +
				" Пятерых своих дружков " + GetName( NAMETYPE_VIP, NPChar.Hold_GenQuest.PirateName, NAME_NOM) + " поверх этого клада положил...\nПотом поползли слухи, что " + GetName( NAMETYPE_VIP, NPChar.Hold_GenQuest.PirateName, NAME_ACC) + " поймали и к одноногой тёще приставили, а " + NPChar.Hold_GenQuest.Name + " с тех пор от дел отошёл, " +
				"остепенился, семьёй обзавёлся. Но место клада он хорошо запомнил, даже карту нацарапал. Мне предлагал вместе с ним за сокровищами идти. Самому, говорит, боязно - клад тот обильно кровью полили, а человек он суеверный. Я, признаться, тоже не решился. "+
				"Он готов был и карту продать, но на кой она мне - я всё одно за это дело не возьмусь...\n Вот такая моя история... Думаю, карта эта вам как человеку отважному в самый раз пригодилась бы... он её задёшево отдаст.";
			link.l1 = "И вы действительно надеетесь, что я поверю в эту ерунду? Уговор расторгается по причине несостоятельности вашей истории.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "Хм... интересная история, хотя и верится с трудом. Ну, раз слово дал - идите, скажите боцману, пусть выделит вам рундук на баке. В первой же бухте сойдёте на берег.";
			link.l2.go = "free_by_hoard5";
		break;

		case "free_by_hoard5":
			dialog.text = "Вот, спасибо вам, капитан! Вот что значит слово "+ GetSexPhrase("джентльмена!","леди!");
			link.l1 = "Ступайте и не попадайтесь мне больше. В другой раз я не буду столь " + GetSexPhrase("легковерен.","легковерна.");
			link.l1.go = "free_by_hoard6";
		break;

		case "free_by_hoard6":
			pchar.GenQuest.Hold_GenQuest.City 		= NPChar.Hold_GenQuest.City;
			pchar.GenQuest.Hold_GenQuest.Nation 	= NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name 		= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.PirateName	= NPChar.Hold_GenQuest.PirateName;
			pchar.GenQuest.Hold_GenQuest.CapName	= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1) + 2;
			pchar.GenQuest.Hold_GenQuest.Sum		= 10000 + rand(10000);
			pchar.GenQuest.Hold_GenQuest.Treasure	= rand(1);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;

			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "12");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Dat"));
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));

            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
			NPChar.LifeDay = 0;
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	DialogExit();
		break;

		case "free_in_sea":
			dialog.text = "Но, " + GetAddress_Form(NPChar) + ", мы же в открытом море! Это равносильно моей казни!!!";
			link.l1 = "Но вы же именно этого добивались - так что прощайте. Боцман проследит за выполнением моего распоряжения.";
			link.l1.go = "PunishmentAction1";
			link.l2 = "Ну ладно, я ещё подумаю...";
			link.l2.go = "exit";
		break;

		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

	}
}
