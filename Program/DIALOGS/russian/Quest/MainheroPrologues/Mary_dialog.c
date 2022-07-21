// BOAL новый диалог офицера и компаньона 21/06/06
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);
	makearef(NextDiag, NPChar.Dialog);

	ref    sld;
	string attr, attrLoc;
	int    iTemp, iTax, iFortValue;

	bool bGoldMine = false;
	bool bSilverMine = false;
	bool bIronMine = false;

	if(CheckAttribute(PChar, "ColonyBuilding.GoldMine.BuildingTime"))
	{
		bGoldMine = PChar.ColonyBuilding.GoldMine == true && PChar.ColonyBuilding.GoldMine.BuildingTime == false;
	}
	if(CheckAttribute(PChar, "ColonyBuilding.SilverMine.BuildingTime"))
	{
		bSilverMine = PChar.ColonyBuilding.SilverMine == true && PChar.ColonyBuilding.SilverMine.BuildingTime == false;
	}
	if(CheckAttribute(PChar, "ColonyBuilding.IronMine.BuildingTime"))
	{
		bIronMine = PChar.ColonyBuilding.IronMine == true && PChar.ColonyBuilding.IronMine.BuildingTime == false;
	}

	switch(Dialog.CurrentNode)
	{
        case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple("Хех, капитан, за тобой тут половина гарнизона гоняется. Сейчас явно не время идти к тебе в команду!", "Предлагаешь с боем прорываться на корабль? Нет уж, в другой раз, кэп...");
				link.l1 = RandPhraseSimple("Ну как знаешь...", "Да я и не "+ GetSexPhrase("собирался","собиралась") +" тебя нанимать.");
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = "Офицер не нужен, капитан?";
			if (FindFreeRandomOfficer() > 0)
			{
    			Link.l1 = "Офицер? А на что ты годен?";
    			Link.l1.go = "Node_2";
			}
			Link.l2 = "Нет, у меня полный комплект.";
			Link.l2.go = "Exit";
		break;

		case "CitizenNotBlade":
			dialog.text = "Шарль, что за глупости! Убери оружие, пока бед не наделали!";
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Не переживай, уже убираю...");
			link.l1.go = "exit";
		break;

		case "hired":
			Diag.TempNode = "Hired";
			// если шлялся по борделям - устроит небольшой скандал 
			if (sti(pchar.GenQuest.BrothelCount) >= 1 && LAi_grp_playeralarm == 0 && NPChar.id == "SharleMary" && NPChar.name == "Мэри")
			{
				dialog.Text = ""+pchar.name+"! Мне надо с тобой поговорить, да! Серьёзно поговорить!";
				Link.l1 = "Что случилось, Мэри? Что-то не так?";
				Link.l1.go = "Mary_brothel";
				break;
			}
			pchar.SharleMaryId = npchar.id; //<<<<<<<<========================== УДАЛИТЬ ПОТОМ ======================
			dialog.text = LinkRandPhrase("Я вся во внимании, мой любимый!","Да, радость моя, я сделаю всё что скажешь!","У тебя есть для меня задание, любовь моя?");
			// диалог компаньона на корабле.
			if (CheckAttribute(NPChar, "IsCompanionClone"))
			{
				Link.l2 = "Мэри, у меня есть для тебя несколько приказов.";
				Link.l2.go = "Companion_Tasks";
				break;
			}
			if (NPChar.id == "SharleMary" && NPChar.name == "Мэри")
			{
				Link.l2 = LinkRandPhrase (LinkRandPhrase("Мэри,", "Милая,", "Дорогая,") + " у меня для тебя есть распоряжение. ", LinkRandPhrase("Мэри,", "Милая,", "Дорогая,") + " мне нужно с тобой посоветоваться. ", LinkRandPhrase("Мэри,", "Милая,", "Дорогая,") + " нам нужно кое-что сделать."));
	            Link.l2.go = "stay_follow";
			}	
           		// boal отчет о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l8 = "Мэри, дай мне полный отчёт о корабле.";
			    Link.l8.go = "QMASTER_1";

			    Link.l11 = "Я хочу, чтобы во время стоянки в колонии ты закупала товары.";
			    Link.l11.go = "QMASTER_2";
			}

			for(iTemp=1; iTemp<=3; iTemp++) // Нужно, чтоб была свободная группа
			{
				attr = "Companion" + iTemp;
				if (CheckAttribute(PChar,"CompanionTravel."+(attr)+".ID"))
				{
					if (PChar.CompanionTravel.(attr).ID == NPChar.ID)
					{
						Link.l4 = "Мэри, возвращайся в эскадру.";
						Link.l4.go = "CompanionTravel_ToSquadron";
					}
				}
			}
			//Предлагаем сэкс Мэри Каспер (для Шарля)
			if (PChar.location == Get_My_Cabin() && CheckAttribute(npchar, "quest.daily_sex") && npchar.id == "SharleMary")
			{
				DeleteAttribute(link, "l3");
			}
			if (PChar.location == Get_My_Cabin() && !CheckAttribute(npchar, "quest.daily_sex") && npchar.id == "SharleMary")
			{
				Link.l3 = RandPhraseSimple("Милая, я хочу остаться с тобой наедине, прямо сейчас. Ты не возражаешь?","Дорогая, как насчёт того, чтобы немного... побыть вдвоём?");
				Link.l3.go = "Mary_cabin_sex";
			}
			if (!CheckAttribute(npchar, "quest.daily_sex") && sti(pchar.money) >= 10)
			{
				if (PChar.location == "SentJons_tavern" || PChar.location == "PortRoyal_tavern" || PChar.location == "Charles_tavern" || PChar.location == "Bridgetown_tavern" || 
					PChar.location == "Portspein_tavern" || PChar.location == "Villemstad_tavern" || PChar.location == "Marigo_tavern" || PChar.location == "FortOrange_tavern" || 
					PChar.location == "FortOrange_tavern" || PChar.location == "FortFrance_tavern" || PChar.location == "FortFrance_tavern" || PChar.location == "BasTer_tavern" || 
					PChar.location == "Tortuga_tavern" || PChar.location == "Caracas_tavern" || PChar.location == "Cumana_tavern" || PChar.location == "Cartahena_tavern" || 
					PChar.location == "Maracaibo_tavern" || PChar.location == "PortoBello_tavern" || PChar.location == "SantaCatalina_tavern" || PChar.location == "Beliz_tavern" || 
					PChar.location == "SantoDomingo_tavern" || PChar.location == "SanJuan_tavern" || PChar.location == "Santiago_tavern" || PChar.location == "Havana_tavern" || 
					PChar.location == "PuertoPrincipe_tavern" || PChar.location == "PortPax_tavern" || PChar.location == "LaVega_tavern" || PChar.location == "Pirates_tavern" || 
					PChar.location == "Panama_tavern" || PChar.location == "LeFransua_tavern")
					{
						Link.l3 = RandPhraseSimple("Милая, а давай снимем комнату и останемся вдвоём?","Дорогая, мне так хочется побыть с тобой наедине... может, снимем комнату и забудем обо всём на пару часов?");
						Link.l3.go = "Mary_room_sex";
					}
			}
			if (!CheckAttribute(pchar, "questTemp.FUNY_SHIP_FIND") && NPChar.sex == "woman" && GetCharacterItem(PChar, "mineral4") >= 25)
            {
                Link.l4 = "Смотри какая у меня коллекция собралась интересная!";
				Link.l4.go = "FUNY_SHIP_1";
            }

            // по тек локации определим можно ли тут приказать  -->
            if (IsEntity(loadedLocation))
            {
                if (CheckAttribute(loadedLocation, "fastreload"))
                {
                    iTemp = FindColony(loadedLocation.fastreload);
                    if (iTemp != -1)
                    {
                        sld = GetColonyByIndex(iTemp);
                        if (sti(sld.HeroOwn) == true && !CheckAttribute(sld, "OfficerIdx"))
                        {
							if(Locations[FindLocation(PChar.location)].islandId != "Caiman" && !CheckAttribute(NPChar,"HPminusDaysNeedtoRestore"))
							{
								NPChar.ColonyIdx = iTemp;
								Link.l7 = "Я назначаю тебя наместником этого города!";
								Link.l7.go = "Gover_Hire";
							}
                        }
                    }
                }
            }
            if(PChar.ColonyBuilding.Stage != "0" && PChar.ColonyBuilding.Hovernor == "")
			{
				if(CheckAttribute(&Locations[FindLocation(PChar.location)], "islandId"))
				{
					if(Locations[FindLocation(PChar.location)].islandId == "Caiman" && !CheckAttribute(NPChar,"HPminusDaysNeedtoRestore"))
					{
						Link.l8 = "Я хочу назначить тебя управляющим колонии ''" + PChar.ColonyBuilding.ColonyName + "'', которую мы построили на острове Кайман.";
						Link.l8.go = "ColonyBuilding_Hovernor_1";
					}
				}
			}

			if(PChar.ColonyBuilding.Stage == "3" && PChar.Colony.Guardians.Hovernor == "")
			{
				if(CheckAttribute(&Locations[FindLocation(PChar.location)], "islandId"))
				{
					if(Locations[FindLocation(PChar.location)].islandId == "Caiman" && !CheckAttribute(NPChar,"HPminusDaysNeedtoRestore"))
					{
						Link.l9 = "Я хочу назначить тебя управляющим охранной базы, которую мы построили для укрепления обороны нашей колонии ''" + PChar.ColonyBuilding.ColonyName + "''.";
						Link.l9.go = "ColonyGuarding_Hovernor_1";
					}
				}
			}

			if(bGoldMine || bSilverMine || bIronMine)
			{
				if(PChar.Mines.Commander == "")
				{
					if(CheckAttribute(&Locations[FindLocation(PChar.location)], "islandId"))
					{
						if(Locations[FindLocation(PChar.location)].islandId == "Caiman" && !CheckAttribute(NPChar,"HPminusDaysNeedtoRestore"))
						{
							Link.l10 = "Я хочу назначить тебя управляющим рудников, которые находятся на этом острове.";
							Link.l10.go = "MinesCommander_Hire";
						}
					}
				}
			}

			if(PChar.ColonyBuilding.Plantation == true && PChar.ColonyBuilding.Plantation.BuildingTime == false)
			{
				if(PChar.Plantation.Commander == "")
				{
					if(CheckAttribute(&Locations[FindLocation(PChar.location)], "islandId"))
					{
						if(Locations[FindLocation(PChar.location)].islandId == "Caiman")
						{
							Link.l11 = "Я хочу назначить тебя управляющим плантации, которая находится недалеко от колонии ''" + PChar.ColonyBuilding.ColonyName + "'' и ей принадлежит.";
							Link.l11.go = "PlantationCommander_Hire";
						}
					}
				}
			}
            Link.l12 = "Ничего. Вольно.";
            Link.l12.go = "Exit";
			if (NPChar.id == "SharleMary" && NPChar.name == "Мэри")
			{
				Link.l12 = LinkRandPhrase ("От тебя глаз не оторвать, " + LinkRandPhrase("мой рыжий талисман.", "моя прекрасная львица.", "моя красавица."), "Я лишь хотел полюбоваться тобой, " + LinkRandPhrase("мой рыжий талисман.", "моя прекрасная львица.", "моя красавица."), "Люблю тебя, " + LinkRandPhrase("мой рыжий талисман.", "моя прекрасная львица.", "моя красавица."));
	            Link.l12.go = "Exit";
			}
        break;

		case "FUNY_SHIP_1":
		    dialog.text = "О ужас! Шарль, убери от меня это, такая невыносимая вонь... ты что веришь во всю эту чушь старой легенды про получение вечной молодости?";
   			Link.l1 = "Нет, конечно, извини. Пойду выкину всю эту воняющую массу за борт.";
            Link.l1.go = "exit";
            Link.l2 = "Да, верю! Мало того, проверю. Ну-ка, подходи ближе, дорогая мся!";
            Link.l2.go = "FUNY_SHIP_2";
        break;

        case "FUNY_SHIP_2":
		    dialog.text = "Ну и вонь! Фу... хотя работает, я чувствую себя сильнее и даже, хм, сексуальнее.";
   			Link.l1 = "Вот! А ты боялась, даже юбка не помялась. Руки только теперь мыть.";
            Link.l1.go = "FUNY_SHIP_3";
        break;

        case "FUNY_SHIP_3":
            PChar.questTemp.FUNY_SHIP_FIND = false;
            DialogExit();
			NextDiag.CurrentNode = "Hired";

			TakeNItems(pchar, "mineral4", -25);
			AddSPECIALValue(Npchar, SPECIAL_S, 1);
			AddSPECIALValue(Npchar, SPECIAL_P, 1);
			AddSPECIALValue(Npchar, SPECIAL_E, 1);
			AddSPECIALValue(Npchar, SPECIAL_C, 1);
			AddSPECIALValue(Npchar, SPECIAL_I, 1);
			AddSPECIALValue(Npchar, SPECIAL_A, 1);
			AddSPECIALValue(Npchar, SPECIAL_L, 1);
        break;

		case "MaryCabinHelp_1":
			dialog.text = "Шарль, я не могу сидеть сложа руки! Я же буду волноваться... и скучать...";
            Link.l1 = "Солнце моё, ты мне так дорога, что я не могу подвергать тебя опасности!";
            Link.l1.go = "exit";
			pchar.MaryCabinHelp = !sti(pchar.MaryCabinHelp);
		break;
		
		case "MaryCabinHelp_2":
			dialog.text = "Я пойду с тобой хоть на край света, да!";
            Link.l1 = "Ты моя прелесть!";
            Link.l1.go = "exit";
			pchar.MaryCabinHelp = !sti(pchar.MaryCabinHelp);
		break;

		case "TransferGoodsEnable":
			Diag.CurrentNode = "Hired";
			DialogExit();
			LaunchTransferGoodsScreen(); // Интерфейс автозакупки товаров
		break;

		case "ShowParam_exit":
			Diag.CurrentNode = "OnceAgain";
			NPChar.quest.meeting = true;
			DialogExit();

			PChar.SystemInfo.OnlyShowCharacter = true;
            LaunchCharacter(NPChar);
		break;

		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_hire":
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			npchar.CanTakeMushket = true;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
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
			FireImmortalOfficer(npchar);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;

			DialogExit();
		break;

        case "QMASTER_1":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
			{
				dialog.text = "Шарль, но у нас ведь нету корабля!";
				Link.l1 = "Спасибо, напомнила...";
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
			}
            dialog.text = "Корабль прекрасный, Шарль, да! Пробоину ниже ватерлинии после последнего боя залатали, паруса просушены. А что ты хотел? Не смотри так на меня, я на казначея никогда не училась.";
            Link.l1 = "Прости, Мэри, я и правда как-то не подумал.";
            Link.l1.go = "Exit";
            Diag.TempNode = "Hired";
        break;
		
		case "QMASTER_2":
            dialog.text = "Шарль, так мне ничего и не надо закупать. Одежда у меня есть, клинок есть. Но спасибо за беспокойство, мне очень приятно, да!";
            Link.l1 = "Так я же имел в виду... Ладно, дорогая, забудь, всё хорошо.";
            Link.l1.go = "Exit";
            Diag.TempNode = "Hired";
        break;

        // boal 05.09.03 offecer need to go to abordage -->
        case "stay_follow":
            dialog.text = "Какие будут приказания?";
			if (NPChar.id == "SharleMary" && NPChar.name == "Мэри")
				{
				dialog.text = LinkRandPhrase("И что ты задумал?", "Ты хочешь кого-то убить? Я с тобой, да!", "И что ты задумал?");
				}
            Link.l1 = "Стой здесь!";
            Link.l1.go = "Boal_Stay";
			if (NPChar.id == "SharleMary" && NPChar.name == "Мэри")
				{
				Link.l1 = "Мэри, жди меня здесь, никуда не уходи!";
				Link.l1.go = "Boal_Stay";
				}
            Link.l2 = "Следуй за мной и не отставай!";
            Link.l2.go = "Boal_Follow";
			if (NPChar.id == "SharleMary" && NPChar.name == "Мэри")
				{
				Link.l2 = "Мэри, нам нужно идти!";
				Link.l2.go = "Boal_Follow";
				}
            // boal 05.09.03 offecer need to go to abordage <--

			if (findsubstr(npchar.model, "PGG" , 0) != -1 && !CheckAttribute(npchar, "CanTakeMushket"))
			{
				Link.l3 = "Можно ли тебе доверить мушкет?";
				Link.l3.go = "CheckMushket";
			}
			if (findsubstr(npchar.model.animation, "mushketer" , 0) != -1)
			{
				Link.l3 = "Я хочу, чтобы ты держал"+NPCharSexPhrase(npchar,"ся","ась")+" на определённом расстоянии от цели.";
				Link.l3.go = "TargetDistance";
			}
			if (!CheckAttribute(npchar,"AboardRestriction"))
			{
				Link.l4 = "Прошу тебя не участвовать в абордажах. Побереги себя.";
				Link.l4.go = "AboardRestriction";
			}
			else
			{
				Link.l4 = "Я передумал, можешь участвовать в абордажах.";
				Link.l4.go = "AboardAllowed";
			}
			if (NPChar.id == "SharleMary" && NPChar.name == "Мэри")
			{
				if(Pchar.MaryCabinHelp == true)
				{
					Link.l14 = "Во время боя в каюте я буду сражаться один.";
					Link.l14.go = "MaryCabinHelp_1";
				}
				else
				{
					Link.l14 = "Во время боя в каюте мы будем сражаться вместе плечом к плечу.";
					Link.l14.go = "MaryCabinHelp_2";
				}		
			}
			
			link.l9 = "Любуясь тобой, я забыл, что хотел сказать...";
			link.l9.go = "exit";
		break;

		case "AboardRestriction":
			npchar.AboardRestriction = true;
			dialog.text = "Так точно капитан. Не буду участвовать в абордажах, пока вы снова не разрешите.";
            Link.l1 = "Ну и хорошо.";
            Link.l1.go = "exit";
			if (NPChar.id == "SharleMary" && NPChar.name == "Мэри")
				{
				dialog.text = "Шарль, ты с ума сошёл! А если с тобой что-то случится, а меня не будет рядом... Мы вдвоём всем им покажем, да!";
				Link.l1 = "Мэри, это даже не обсуждается, ты мне дорога, и я хочу, чтобы ты была в безопасности.";
				Link.l1.go = "exit";
				}
		break;

		case "AboardAllowed":
			DeleteAttribute(npchar,"AboardRestriction");
			dialog.text = "Так точно капитан. Буду участвовать в абордажах с текущего момента.";
            Link.l1 = "Ну и хорошо.";
            Link.l1.go = "exit";
			if (NPChar.id == "SharleMary" && NPChar.name == "Мэри")
				{
				dialog.text = "Ура, ура! Я рада, что ты обо мне не забыл, теперь мы будем уничтожать врагов вместе, да!";
				Link.l1 = "Мне радостно это слышать, любимая!";
				Link.l1.go = "exit";
				}
		break;

		case "CheckMushket":
			if (findsubstr(npchar.model.animation, "man" , 0) != -1 || findsubstr(npchar.model.animation, "YokoDias" , 0) != -1 || findsubstr(npchar.model.animation, "Milenace" , 0) != -1)
			{
				if (findsubstr(npchar.model.animation, "man2_ab" , 0) == -1)	Npchar.CanTakeMushket = true;
			}

			if (CheckAttribute(npchar, "CanTakeMushket"))
			{
				dialog.text = "Конечно, Шарль!";
				Link.l1 = "Замечательно, тогда по возможности что-то тебе подберём.";
				Link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Лучше не надо, Шарль. Вдруг я тебя случайно задену.";
				Link.l1 = "Ну и правильно, ты у меня прекрасно владеешь холодномым оружием.";
				Link.l1.go = "exit";
			}
		break;

		case "TargetDistance":
			dialog.text = "На каком именно, Шарль? Укажи в метрах, но не более 20-ти.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";
		break;
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Шарль, я не раслышала!";
				link.l1 = "Я щас повторю...";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Я буду стоять на месте, никуда не двигаясь. Шарль, тебя это устраивает?";
				link.l1 = "Да, именно этого я от тебя и хочу, Мэри.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Я кажется говорил"+NPCharSexPhrase(npchar, "","а")+", что более 20 метров от цели мне держаться нельзя.";
				link.l1 = "Хорошо, держись на расстоянии в 20 метров.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Задачу понял"+NPCharSexPhrase(npchar, "","а")+", да!";
			link.l1 = "Отлично.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;

        // boal 05.09.03 offecer need to go to abordage -->
	      case "Boal_Stay":
             //SetCharacterTask_Stay(Characters[Npchar.index]); // it's a mistic but here doesn't work :(
             //Log_SetStringToLog(Npchar.id +" "+Npchar.index);
              Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
              AddDialogExitQuestFunction("LandEnc_OfficerStay");
		      Diag.TempNode = "Hired";
		      dialog.text = "Есть изменить дислокацию!";
		      Link.l1 = "Вольно.";
		      Link.l1.go = "Exit";
			  if (NPChar.id == "SharleMary" && NPChar.name == "Мэри")
			  {
				dialog.text = "Буду ждать тебя здесь, любовь моя!";
				Link.l1 = "Я скоро вернусь, не скучай <3";
				Link.l1.go = "Exit";
			  }
		      Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
	      break;
	      case "Boal_Follow":
		      SetCharacterTask_FollowCharacter(Npchar, PChar); // it works here!!!
		      Diag.TempNode = "Hired";
		      dialog.text = "Есть изменить дислокацию!";
		      Link.l1 = "Вольно.";
		      Link.l1.go = "Exit";
			  if (NPChar.id == "SharleMary" && NPChar.name == "Мэри")
			  {
				dialog.text = "Мы снова вместе, да!";
				Link.l1 = "Да, Мэри, ты как всегда права!";
				Link.l1.go = "Exit";
			  }
	      break;
        // boal 05.09.03 offecer need to go to abordage <--

		//////////////////////////////    офицер-наместник -->
		case "Gover_Hire":
            dialog.Text = "Почту за честь!";
            Link.l1 = "Следи за порядком и процветанием города, я буду иногда приплывать за собранной пошлиной.";
			Link.l1.go = "Exit_Gover_Hire";
            Link.l2 = "Я передумал"+ GetSexPhrase("","а") +".";
            Link.l2.go = "Exit";
            Diag.TempNode = "Hired";
        break;

        case "Exit_Gover_Hire":
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            attr = sld.id + "_townhall";

            // снимем пассажира -->
			CheckForReleaseOfficer(sti(NPChar.index));
			RemovePassenger(pchar, NPChar);
			// снимем пассажира <--
		    sld.OfficerIdx = sti(NPChar.index);
			ChangeCharacterAddressGroup(NPChar, attr, "sit", "sit1");
			LAi_SetHuberTypeNoGroup(NPChar);
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
            LAi_LoginInCaptureTown(NPChar, true);
			//  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecord("Gen_CityCapture", "t3_1");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
			Diag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Main":
            iTemp = GetNpcQuestPastDayParam(NPChar, "GoverTalkDate");
            if (iTemp > 0)
            {
				dialog.Text = "Какие будут приказания? Последний ваш визит был " + FindRussianDaysString(iTemp) + " назад.";
			}
			else
			{
			    dialog.Text = "Какие будут приказания?";
			}

            Link.l1 = "Какую сумму налогов ты " + NPCharSexPhrase(NPChar, "собрал", "собрала") + " на данный момент?";
        	Link.l1.go = "Gover_Tax";
            Link.l8 = "Ты " + NPCharSexPhrase(NPChar, "нужен", "нужна") + " мне на корабле, я снимаю тебя с городской службы.";
            Link.l8.go = "Gover_Fire";
			Link.l9 = "Всего хорошего.";
            Link.l9.go = "Exit";
            Diag.TempNode = "Gover_Main";
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
        break;

        case "Gover_Tax":
            iTemp = GetNpcQuestPastDayParam(NPChar, "StartTaxDate");
            iTax  = makeint((GetCharacterSkillSimple(NPChar, SKILL_COMMERCE) + GetCharacterSkillSimple(NPChar, SKILL_LEADERSHIP)) / 2);
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
			if (CheckAttribute(sld, "FortValue"))
			{
			    iFortValue = sti(sld.FortValue);
			}
			else
			{
			    iFortValue = 20;
			}
			NPChar.Gover_Tax_Sum = iFortValue*iTax*iTemp;
			dialog.Text = "Мои навыки позволяют мне собирать " + FindRussianMoneyString(iFortValue*iTax) + " в день. За " + FindRussianDaysString(iTemp) + " я " + NPCharSexPhrase(NPChar, "собрал", "собрала") + " " + FindRussianMoneyString(sti(NPChar.Gover_Tax_Sum)) + ".";
			if (sti(NPChar.Gover_Tax_Sum) > 0)
			{
			    Link.l1 = "Я хочу забрать всю сумму налогов.";
            	Link.l1.go = "Gover_Tax_Get";
			}
			Link.l2 = "Благодарю за службу!";
            Link.l2.go = "Exit";
        break;

        case "Gover_Tax_Get":
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            AddMoneyToCharacter(Pchar, sti(NPChar.Gover_Tax_Sum));

			Diag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Fire":
            dialog.Text = "Замечательно! Быть сухопутной крысой не мой удел.";
            Link.l8 = "Вот и славно.";
            Link.l8.go = "exit_hire";
            Diag.TempNode = "Hired";
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            DeleteAttribute(sld, "OfficerIdx");
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecord("Gen_CityCapture", "t3_2");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
        break;
        //////////////////////////////    офицер-наместник <--

		//Указания для компаньона 19.02.08 -->
		case "Companion_Tasks":
			dialog.Text = "Что ты хотел, любимый мой?";
			Link.l1 = "Это касается абордажа.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "Это касается твоего корабля.";
			Link.l2.go = "Companion_TaskChange";
			// if(bBettaTestMode) // Только при бета-тесте
			// {
			    Link.l3 = "Я хочу, чтобы ты на время выш"+ GetSexPhrase("ел","ла") +" из состава моей эскадры и поискал удачу самостоятельно.";
			    Link.l3.go = "CompanionTravel";
			// }
			Link.l8 = "Пока ничего.";
			Link.l8.go = "exit";
		break;

		case "Companion_TaskBoarding":
			dialog.Text = "";
			Link.l1 = "Я хочу, чтобы ты не брал"+ NPCharSexPhrase(NPChar,"","а") +" корабли на абордаж. Побереги себя и свою команду.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Мне нужно, чтобы ты брал"+ NPCharSexPhrase(NPChar,"","а") +" вражеские корабли на абордаж.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;

		case "Companion_TaskChange":
			dialog.Text = "";
			Link.l1 = "Я хочу, чтобы ты не менял"+ NPCharSexPhrase(NPChar,"","а") +" свой корабль после абордажа. Он слишком ценен.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Когда будешь брать врага на абордаж, посмотри, вдруг кораблик приличный будет, тогда бери себе.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "Я всё поняла, да!";
			Link.l1 = "Умница!";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;

		case "Companion_TaskBoardingYes":
			dialog.Text = "Я всё поняла, да!";
			Link.l1 = "Умница!";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;

		case "Companion_TaskChangeNo":
			dialog.Text = "Я всё поняла, да!";
			Link.l1 = "Умница!";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;

		case "Companion_TaskChangeYes":
			dialog.Text = "Я всё поняла, да!";
			Link.l1 = "Умница!";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
		//<--

		// Самостоятельное плавание компаньона -->
		case "CompanionTravel":
			if(GetAttrValue(PChar, "CompanionTravel") == 3) // Если уже троих отпустил
			{
				dialog.Text = "Шарль, я не выйду из состава твоей эскадры, так как ты и так уже отпустил три корабля.";
					Link.l1 = "Да, пожалуй ты права.";
					Link.l1.go = "exit";
				break;
			}

			dialog.Text = "Нет проблем, Шарль. Куда мне отправляться?";
			Link.l1 = "Отправляйся в город...";
			Link.l1.go = "Travel_Towns";

			Link.l2 = "Отправляйся к пиратскому поселению...";
			Link.l2.go = "TravelToPiratesTowns";

			Link.l3 = "Отправляйся к необитаемому острову...";
			Link.l3.go = "TravelToNomanIslands";

			Link.l99 = "Я передумал"+ GetSexPhrase("","а") +". Ничего не нужно.";
			Link.l99.go = "exit";
		break;

		case "Travel_Towns":
			dialog.Text = "Где будет место встречи, Шарль?";
			for(iTemp=0; iTemp<MAX_COLONIES; iTemp++)
			{
				sld = &colonies[iTemp];
				attr = sld.ID;
				if(sld.nation == "none" || sld.nation == PIRATE || attr == "Panama" || attr == "FortOrange") continue;
				attrLoc = "l" + iTemp;
				NPChar.Temp.(attr) = attr;
				Link.(attrLoc) = "В " + XI_ConvertString("Colony" + attr + "Dat");
				Link.(attrLoc).go = "CompanionTravelToColony_" + attr;
			}
				Link.l99 = "Я передумал"+ GetSexPhrase("","а") +". Ничего не нужно.";
				Link.l99.go = "exit";
		break;

		case "TravelToPiratesTowns":
			dialog.Text = "К какому именно?";
				Link.l1 = "Бермуды";
				Link.l1.go = "TravelToPirates";
				Link.l2 = "Ле Франсуа";
				Link.l2.go = "TravelToLeFransua";
				Link.l3 = "Ла Вега";
				Link.l3.go = "TravelToLaVega";
				Link.l4 = "Пуэро-Принсипе";
				Link.l4.go = "TravelToPuertoPrincipe";
				Link.l5 = "Форт Оранж";
				Link.l5.go = "TravelToFortOrange";
				Link.l6 = "Знаешь, пока останься, я передумал"+ GetSexPhrase("","а")+".";
				Link.l6.go = "exit";
		break;
		case "TravelToNomanIslands":
			dialog.Text = "К какому именно?";
				Link.l1 = "Кайман";
				Link.l1.go = "TravelToCaiman";
				Link.l2 = "Доминика";
				Link.l2.go = "TravelToDominica";
				Link.l3 = "Теркс";
				Link.l3.go = "TravelToTerks";
				Link.l4 = "Знаешь, пока останься, я передумал"+ GetSexPhrase("","а")+".";
				Link.l4.go = "exit";
		break;

		case "TravelToCaiman":
			for (i = 1; i < COMPANION_MAX; i++)
			{
				int cn_3;									// Companion index
				cn_3 = GetCompanionIndex(PChar, i);
				if (cn_3 == -1) continue;
				if (NPChar.name == characters[cn_3].name) NPChar.realcompanionidx = &characters[cn_3].index;
			}
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID = "Caiman";
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days = makeint(GetDistanceToColony2D("PuertoPrincipe"))/300+1.0);
			dialog.Text = "И так, Вы хотите чтоб я оправился до "+XI_ConvertString("Caiman" + "Gen")+", капитан?";
			Link.l1 = "Да, именно так.";
            Link.l1.go = "CompanionTravel_PrepareStart";
			Link.l2 = "Нет, я передумал"+ GetSexPhrase("","а")+", не бери в голову.";
            Link.l2.go = "exit";
        break;
		case "TravelToDominica":
			for (i = 1; i < COMPANION_MAX; i++)
			{
				int cn_4;									// Companion index
				cn_4 = GetCompanionIndex(PChar, i);
				if (cn_4 == -1) continue;
				if (NPChar.name == characters[cn_4].name) NPChar.realcompanionidx = &characters[cn_4].index;
			}
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID = "Dominica";
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days = makeint(GetDistanceToColony2D("LeFransua"))/300+1.0);
			dialog.Text = "И так, Вы хотите чтоб я оправился до "+XI_ConvertString("Dominica" + "Gen")+", капитан?";
			Link.l1 = "Да, именно так.";
            Link.l1.go = "CompanionTravel_PrepareStart";
			Link.l2 = "Нет, я передумал"+ GetSexPhrase("","а")+", не бери в голову.";
            Link.l2.go = "exit";
        break;
		case "TravelToTerks":
			for (i = 1; i < COMPANION_MAX; i++)
			{
				int cn_5;									// Companion index
				cn_5 = GetCompanionIndex(PChar, i);
				if (cn_5 == -1) continue;
				if (NPChar.name == characters[cn_5].name) NPChar.realcompanionidx = &characters[cn_5].index;
			}
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID = "Terks";
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days = makeint(GetDistanceToColony2D("Pirates"))/300+1.0);
			dialog.Text = "И так, Вы хотите чтоб я оправился до "+XI_ConvertString("Terks" + "Gen")+", капитан?";
			Link.l1 = "Да, именно так.";
            Link.l1.go = "CompanionTravel_PrepareStart";
			Link.l2 = "Нет, я передумал"+ GetSexPhrase("","а")+", не бери в голову.";
            Link.l2.go = "exit";
        break;
		case "TravelToLaVega":
			for (i = 1; i < COMPANION_MAX; i++)
			{
				int cn_6;									// Companion index
				cn_6 = GetCompanionIndex(PChar, i);
				if (cn_6 == -1) continue;
				if (NPChar.name == characters[cn_6].name) NPChar.realcompanionidx = &characters[cn_6].index;
			}
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID = "LaVega";
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days = makeint(GetDistanceToColony2D("LaVega"))/300+1.0);
			dialog.Text = "И так, Вы хотите чтоб я оправился до "+XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Gen")+", капитан?";
			Link.l1 = "Да, именно так.";
            Link.l1.go = "CompanionTravel_PrepareStart";
			Link.l2 = "Нет, я передумал"+ GetSexPhrase("","а")+", не бери в голову.";
            Link.l2.go = "exit";
        break;
		case "TravelToPuertoPrincipe":
			for (i = 1; i < COMPANION_MAX; i++)
			{
				int cn_7;									// Companion index
				cn_7 = GetCompanionIndex(PChar, i);
				if (cn_7 == -1) continue;
				if (NPChar.name == characters[cn_7].name) NPChar.realcompanionidx = &characters[cn_7].index;
			}
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID = "PuertoPrincipe";
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days = makeint(GetDistanceToColony2D("PuertoPrincipe"))/300+1.0);
			dialog.Text = "И так, Вы хотите чтоб я оправился до "+XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Gen")+", капитан?";
			Link.l1 = "Да, именно так.";
            Link.l1.go = "CompanionTravel_PrepareStart";
			Link.l2 = "Нет, я передумал"+ GetSexPhrase("","а")+", не бери в голову.";
            Link.l2.go = "exit";
        break;
		case "TravelToFortOrange":
			for (i = 1; i < COMPANION_MAX; i++)
			{
				int cn_8;									// Companion index
				cn_8 = GetCompanionIndex(PChar, i);
				if (cn_8 == -1) continue;
				if (NPChar.name == characters[cn_8].name) NPChar.realcompanionidx = &characters[cn_8].index;
			}
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID = "FortOrange";
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days = makeint(GetDistanceToColony2D("FortOrange"))/300+1.0);
			dialog.Text = "И так, Вы хотите чтоб я оправился до "+XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Gen")+", капитан?";
			Link.l1 = "Да, именно так.";
            Link.l1.go = "CompanionTravel_PrepareStart";
			Link.l2 = "Нет, я передумал"+ GetSexPhrase("","а")+", не бери в голову.";
            Link.l2.go = "exit";
        break;
		case "TravelToPirates":
			for (i = 1; i < COMPANION_MAX; i++)
			{
				int cn_9;									// Companion index
				cn_9 = GetCompanionIndex(PChar, i);
				if (cn_9 == -1) continue;
				if (NPChar.name == characters[cn_9].name) NPChar.realcompanionidx = &characters[cn_9].index;
			}
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID = "Pirates";
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days = makeint(GetDistanceToColony2D("Pirates"))/300+1.0);
			dialog.Text = "И так, Вы хотите чтоб я оправился до "+XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Gen")+", капитан?";
			Link.l1 = "Да, именно так.";
            Link.l1.go = "CompanionTravel_PrepareStart";
			Link.l2 = "Нет, я передумал"+ GetSexPhrase("","а")+", не бери в голову.";
            Link.l2.go = "exit";
        break;
		case "TravelToLeFransua":
			for (i = 1; i < COMPANION_MAX; i++)
			{
				int cn_10;									// Companion index
				cn_10 = GetCompanionIndex(PChar, i);
				if (cn_10 == -1) continue;
				if (NPChar.name == characters[cn_10].name) NPChar.realcompanionidx = &characters[cn_10].index;
			}
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID = "LeFransua";
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days = makeint(GetDistanceToColony2D("LeFransua"))/300+1.0);
			dialog.Text = "И так, Вы хотите чтоб я оправился до "+XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Gen")+", капитан?";
			Link.l1 = "Да, именно так.";
            Link.l1.go = "CompanionTravel_PrepareStart";
			Link.l2 = "Нет, я передумал"+ GetSexPhrase("","а")+", не бери в голову.";
            Link.l2.go = "exit";
        break;

		int nFind = findSubStr(Dialog.CurrentNode, "CompanionTravelToColony_", 0);
		string idxVal;
		string nodName;
		if(nFind == 0)
		{
            idxVal = strcut(Dialog.CurrentNode, 24, strlen(Dialog.CurrentNode)-1);
            nodName = "CompanionTravelToColony_" + idxVal;
			for (i = 1; i < COMPANION_MAX; i++)
			{
				int cn;									// Companion index
				cn = GetCompanionIndex(PChar, i);
				if (cn == -1) continue;
				if (NPChar.name == characters[cn].name) NPChar.realcompanionidx = &characters[cn].index;
			}
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID = NPChar.Temp.(idxVal);
			characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days = makeint(GetDistanceToColony2D(NPChar.Temp.(idxVal))/300+1.0);
			dialog.Text = "Вы выбрали колонию "+XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Gen")+", капитан?";
			Link.l1 = "Да, именно её.";
            Link.l1.go = "CompanionTravel_PrepareStart";
			Link.l2 = "Нет, я передумал"+ GetSexPhrase("","а")+", не бери в голову.";
            Link.l2.go = "exit";
            break;
        }

		case "CompanionTravel_EnemyColony":
			dialog.Text = "Капитан, но я же не cмогу ждать вас в колонии, которая к нам враждебна!";
				Link.l1 = "Знаешь, забудь про все эти путешествия...";
				Link.l1.go = "exit";
		break;

		case "CompanionTravel_NoCrew":
			dialog.Text = "Кэп, на корабле же почти нету матросов! Какое плавание?!";
				Link.l1 = "Да, точно. Команды почти нету...";
				Link.l1.go = "exit";
		break;

		case "CompanionTravel_NoFood":
			dialog.Text = "Кэп, для такого путешествия у меня на борту маловато провианта.";
				Link.l1 = "Да, ты прав. Путешествие подождёт, пока-что...";
				Link.l1.go = "exit";
		break;

		case "CompanionTravel_NoHP":
			dialog.Text = "Кэп, но мой корабль в плохом состоянии. Мне не разумно выходить в море одному при таких обстоятельствах!";
				Link.l1 = "Да, ты прав. Твой корабль нуждается в ремонте.";
				Link.l1.go = "exit";
		break;

		case "CompanionTravel_PrepareStart":
			int iShip = sti(characters[sti(NPChar.realcompanionidx)].ship.type);
			ref refBaseShip = GetRealShip(iShip);
			if (sti(refBaseShip.hp)/4>sti(characters[sti(NPChar.realcompanionidx)].ship.hp))
			{
				dialog.Text = "Я вижу проблему, кэп...";
				Link.l1 = "Какую?";
				Link.l1.go = "CompanionTravel_NoHP";
				break;
			}
			if (sti(refBaseShip.MinCrew)>GetCrewQuantity(characters[sti(NPChar.realcompanionidx)]))
			{
				dialog.Text = "Я вижу проблему, кэп...";
				Link.l1 = "Какую?";
				Link.l1.go = "CompanionTravel_NoCrew";
				break;
			}
			if (sti(characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days)+30>CalculateShipFood(characters[sti(NPChar.realcompanionidx)]))
			{
				dialog.Text = "Я вижу проблему, кэп...";
				Link.l1 = "Какую?";
				Link.l1.go = "CompanionTravel_NoFood";
				break;
			}
			dialog.Text = "Всё понятно. До " + XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Gen") + " мне идти " + sti(characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days) + " дней, что мне делать по прибытию?";
			if (sti(characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days) == 1)
			{
			dialog.Text = "Всё понятно. До " + XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Gen") + " рукой подать, я доберусь туда сегодня же. Что мне там делать?";
			}
			Link.l1 = "Жди меня на рейде месяц.";
			Link.l1.go = "CompanionTravel_PrepareStart_2";
			Link.l2 = "Знаешь, я передумал"+ GetSexPhrase("","а") +". Оставайся со мной, пока-что...";
			Link.l2.go = "exit";
		break;

		case "CompanionTravel_PrepareStart_2":
			dialog.Text = "Всё понятно, капитан. Отправляюсь немедленно.";
				Link.l1 = "Да, отправляйся.";
				Link.l1.go = "CompanionTravel_Start";
		break;

		case "CompanionTravel_Start":
			Diag.CurrentNode = "CompanionTravel_LastNode";
			NPChar.quest.meeting = true;
			CompanionTravel_SetTraveller(NPChar);
			DialogExit();
		break;

		case "CompanionTravel_LastNode":
			Dialog.text = RandPhraseSimple("Сегодня я снова выйду в море...",
			"Не забудьте про нашу с вами встречу в " + XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Dat") + ".");
				link.l2 = "...";
				link.l2.go = "Exit";
				Diag.TempNode = "CompanionTravel_LastNode";
		break;

		case "CompanionTravel_ToSquadron":
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				dialog.text = "Я тоже этого желаю. Отныне мой корабль снова под вашим командованием, кэп.";
					Link.l1 = "Хорошо.";
					Link.l1.go = "exit";
					Diag.TempNode = "hired";
					CompanionTravel_DeleteSpecialShipAttributes(NPChar);
					Group_DeleteAtEnd(NPChar.CompanionTravel.GroupID); // Потрем группу
					SetCompanionIndex(PChar, -1, sti(NPChar.index));
					PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // Этого компаньона взяли обратно в эскадру
					if(GetAttrValue(PChar, "CompanionTravel") == 0) CloseQuestHeader("CompanionTravel");
					DeleteAttribute(NPChar, "CompanionTravel");
					for(iTemp=1; iTemp<=3; iTemp++) // Нужно, чтоб была свободная группа
					{
						attr = "Companion" + iTemp;
						if (CheckAttribute(PChar,"CompanionTravel."+(attr)+".ID"))
						{
							if (PChar.CompanionTravel.(attr).ID == NPChar.ID)
							{
								DeleteAttribute(PChar,"CompanionTravel."+(attr)+".ID");
								DeleteAttribute(NPChar,"Tasks.Clone");
							}
						}
					}
			}
			else
			{
				dialog.text = "Кэп, у вас же и так эскадра из пяти коралей, куда-же шестой ещё? В общем, я буду ждать вас тут, на своем корабле - все эти ваши новые компаньоны не надежны - их судна очень скоро пойдут ко дну и вы за мной вернетесь.";
					Link.l1 = "Эх, умная ты голова. Тебе не капитаном, а адмиралом нужно быть!";
					Link.l1.go = "exit";
					Diag.TempNode = "CompanionTravel_ToSquadron_2";
					NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2"; // ставим снова эту ноду
			}
		break;

		case "CompanionTravel_ToSquadron_2":
			dialog.text = "А-а, капитан. Вот вы и вернулись, как я и говорил. Ну что, место в эскадре освободилось?";
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				Link.l1 = "Да, " + NPChar.name + ", освободилось. Добро пожаловать в состав эскадры.";
				Link.l1.go = "exit";
				Diag.TempNode = "hired";
				CompanionTravel_DeleteSpecialShipAttributes(NPChar);
				Group_DeleteAtEnd(NPChar.CompanionTravel.GroupID);
				SetCompanionIndex(PChar, -1, sti(NPChar.index));
				PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // Этого компаньона взяли обратно в эскадру
				if(GetAttrValue(PChar, "CompanionTravel") == 0) CloseQuestHeader("CompanionTravel");
				DeleteAttribute(NPChar, "CompanionTravel");
				for(iTemp=1; iTemp<=3; iTemp++) // Нужно, чтоб была свободная группа
				{
					attr = "Companion" + iTemp;
					if (CheckAttribute(PChar,"CompanionTravel."+(attr)+".ID"))
					{
						if (PChar.CompanionTravel.(attr).ID == NPChar.ID)
						{
							DeleteAttribute(PChar,"CompanionTravel."+(attr)+".ID");
							DeleteAttribute(NPChar,"Tasks.Clone");
						}
					}
				}
			}
			else
			{
				Link.l1 = "Ещё нет, к сожалению.";
				Link.l1.go = "exit";
				Diag.TempNode = "CompanionTravel_ToSquadron_2";
				NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2";
			}
		break;

		//////////////////////////////    офицер-наместник <--


	        // COLONY BUILDING
		case "ColonyBuilding_Hovernor_1":
			dialog.Text = "Почту за честь быть управляющим вашей колонии!";
			Link.l1 = "Следи за порядком и процветанием города. Тебе предстоит очень многое контролировать. Я буду время от времени наведываться сюда.";
			Link.l1.go = "ColonyBuilding_Hovernor_2";
			Link.l2 = "Я передумал"+ GetSexPhrase("","а") +".";
			Link.l2.go = "Exit";
			Diag.TempNode = "Hired";
		break;

	        case "ColonyBuilding_Hovernor_2":
			CheckForReleaseOfficer(sti(NPChar.index));
			RemovePassenger(pchar, NPChar);
			PChar.ColonyBuilding.Hovernor = NPChar.id;
			Diag.CurrentNode = "ColonyBuilding_Hovernor";
			Diag.TempNode = "ColonyBuilding_Hovernor";

			LAi_Fade("", "");
			ChangeCharacterAddressGroup(NPChar, "Caiman_townhall", "sit", "sit1");
			LAi_SetHuberType(NPChar);

			//PChar.quest.SetHovernorToColonyResidence.win_condition.l1 = "ExitFromLocation";
			//PChar.quest.SetHovernorToColonyResidence.win_condition.l1.location = PChar.location;
			//PChar.quest.SetHovernorToColonyResidence.win_condition = "SetHovernorToColonyResidence";

			DialogExit();
	        break;

		case "ColonyBuilding_Hovernor":
			if(PChar.ColonyBuilding.AutoPurchaseFirst == true && PChar.ColonyBuilding.Store.BuildingTime == false && PChar.ColonyBuilding.AutoPurchaseFirst.Disable != true)
			{
				dialog.Text = "Здравствуйте, капитан. Недавно в нашей колонии открылся магазин и я хочу Вам рассказать о некоторых преимуществах этого важного здания.";
				Link.l1 = "Продолжай.";
				Link.l1.go = "ColonyBuilding_AutoStore_1";
				break;
			}

			dialog.Text = "Здравствуйте, капитан " + PChar.name + " " + PChar.lastname + ". Чем могу служить?";
			Link.l1 = "Я хочу знать текущие дела колонии.";
			Link.l1.go = "ColonyBuilding_Hovernor_3";
			Link.l2 = "Я хочу снять тебя с занимаемой должности, " + NPChar.name + ".";
			Link.l2.go = "ColonyBuilding_Hovernor_4";
			Link.l3 = "Решил"+ GetSexPhrase("","а") +" проведать тебя, " + NPChar.name + ".";
			Link.l3.go = "Exit";
			Diag.TempNode = "ColonyBuilding_Hovernor";
		break;

		case "ColonyBuilding_Hovernor_3":
			dialog.Text = "Хм... О каких именно делах вы хотите осведомиться?";
			Link.l1 = "Меня интересует вопрос о состоянии колонии и её финансовых возможностях.";
			Link.l1.go = "ColonyBuilding_Hovernor_3_1";
			Link.l2 = "Меня интересует вопрос о боевой готовности гарнизона и здоровья жителей.";
			Link.l2.go = "ColonyBuilding_Hovernor_3_2";
			Link.l3 = "Я хочу переименовать колонию и пересмотреть внешний вид солдат.";
			Link.l3.go = "ColonyBuilding_Hovernor_3_3";
			Link.l4 = "Извини, " + NPChar.name + ", мне необходимо откланяться.";
			Link.l4.go = "Exit";

		break;

		case "ColonyBuilding_AutoStore_1":
			PChar.ColonyBuilding.AutoPurchaseFirst.Disable = true;
			dialog.Text = "При действующем магазине вы можете обеспечить автоматическую закупку товаров первой необходимости, чтобы живущие в колонии горожане и охраняющий колонию гарнизон могли своевременно получать медикаменты и провиант \n Обратитесь к нашему торговцу, если вас это заинтересовало.";
			Link.l1 = "Интересно. Давай поговорим о другом.";
			Link.l1.go = "ColonyBuilding_Hovernor_3";
		break;

		case "ColonyBuilding_Hovernor_3_1":
			Diag.TempNode = "ColonyBuilding_Hovernor";
			DialogExit();
			LaunchColony();
		break;

		case "ColonyBuilding_Hovernor_3_2":
			Diag.TempNode = "ColonyBuilding_Hovernor";
			DialogExit();
			LaunchColonyLandGuard();
		break;

		case "ColonyBuilding_Hovernor_3_3":
			Diag.TempNode = "ColonyBuilding_Hovernor";
			DialogExit();
			LaunchColonyBuilding(true, false);
		break;

		case "ColonyBuilding_Hovernor_4":
			dialog.Text = "Вы уверены?";
			Link.l1 = "Да.";
			Link.l1.go = "ColonyBuilding_Hovernor_5";
			Link.l2 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			Link.l2.go = "Exit";
		break;

		case "ColonyBuilding_Hovernor_5":
			PChar.ColonyBuilding.Hovernor = "";
			dialog.Text = "Замечательно! Быть сухопутной крысой не мой удел.";
			Link.l1 = "Вот и славно.";
			Link.l1.go = "exit_hire";
			Diag.TempNode = "Hired";
		break;

		case "ColonyBuilding_Expidition_End":
			Diag.CurrentNode = "ColonyBuilding_Hovernor";
			dialog.Text = "Здравствуйте, капитан " + PChar.name + " " + PChar.lastname + ". У меня для вас новость. Недавно закончилась проводимая нами экспедиция. На острове были найдены очень плодотворные земли, а главное - залежи руды.";
			Link.l1 = "Хм, что ж, хорошо. До встречи.";
			Link.l1.go = "exit";
		break;

		case "ColonyBuilding_Mines_End":
			PChar.ColonyBuilding.MineMessage = true;
			Diag.CurrentNode = "ColonyBuilding_Hovernor";
			dialog.Text = "Здравствуйте, капитан " + PChar.name + " " + PChar.lastname + ". У меня для вас новость. Закончилось строительство рудников. Теперь вам необходимо назначить начальника рудников. С ним вы будете решать все дела, связанные с этим ремеслом.";
			Link.l1 = "Хм, что ж, хорошо. До встречи.";
			Link.l1.go = "exit";
		break;

		case "ColonyBuilding_Plantation_End":
			Diag.CurrentNode = "ColonyBuilding_Hovernor";
			dialog.Text = "Здравствуйте, капитан " + PChar.name + " " + PChar.lastname + ". У меня для вас новость. Закончилось строительство плантации. Теперь вам необходимо назначить начальника плантации. С ним вы будете решать все дела, связанные с этим ремеслом.";
			Link.l1 = "Хм, что ж, хорошо. До встречи.";
			Link.l1.go = "exit";
		break;

        	// Начальник рудников
		case "MinesCommander_1":
			dialog.Text = "Здравствуйте, капитан " + PChar.name + " " + PChar.lastname + ". Чем могу служить?";
			Link.l1 = "Я хочу знать текущие дела рудников.";
			Link.l1.go = "MinesCommander_2";
			Link.l2 = "Я хочу снять тебя с занимаемой должности, " + NPChar.name + ".";
			Link.l2.go = "MinesCommander_Remove";
			Link.l3 = "Решил"+ GetSexPhrase("","а") +" проведать тебя, " + NPChar.name + ".";
			Link.l3.go = "Exit";
			Diag.TempNode = "MinesCommander_1";
		break;

		case "MinesCommander_2":
			Diag.TempNode = "MinesCommander_1";
			DialogExit();
			LaunchMines();
		break;

		case "MinesCommander_Remove":
			dialog.Text = "Вы уверены?";
			Link.l1 = "Да.";
			Link.l1.go = "MinesCommander_Removed";
			Link.l2 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			Link.l2.go = "Exit";
			Diag.TempNode = "MinesCommander_1";
		break;

		case "MinesCommander_Removed":
			PChar.Mines.Commander = "";
			dialog.Text = "Замечательно! Быть сухопутной крысой не мой удел.";
			Link.l1 = "Вот и славно.";
			Link.l1.go = "exit_hire";
			Diag.TempNode = "Hired";
		break;

		case "MinesCommander_Hire":
			dialog.Text = "Что ж. Постараюсь оправдать ваши ожидания.";
			Link.l1 = "Вот и славно. Приступай к своим обязанностям.";
			Link.l1.go = "MinesCommander_Hired";
			Link.l2 = "Я передумал"+ GetSexPhrase("","а") +".";
			Link.l2.go = "Exit";
			Diag.TempNode = "Hired";
		break;

		case "MinesCommander_Hired":
			CheckForReleaseOfficer(sti(NPChar.index));
			RemovePassenger(pchar, NPChar);

			LAi_Fade("", "");
			ChangeCharacterAddressGroup(NPChar, "Caiman_Mines_Comendant_House", "barmen", "stay");

			LAi_SetStayType(NPChar);
			PChar.Mines.Commander = NPChar.id;
			Diag.CurrentNode = "MinesCommander_1";
			Diag.TempNode = "MinesCommander_1";

			//PChar.quest.SetCommanderToMinesOffice.win_condition.l1 = "ExitFromLocation";
			//PChar.quest.SetCommanderToMinesOffice.win_condition.l1.location = PChar.location;
			//PChar.quest.SetCommanderToMinesOffice.win_condition = "SetCommanderToMinesOffice";

			DialogExit();
		break;

        	// Начальник плантации
		case "PlantationCommander_1":
			dialog.Text = "Здравствуйте, капитан " + PChar.name + " " + PChar.lastname + ". Чем могу служить?";
			Link.l1 = "Я хочу знать текущие дела плантации.";
			Link.l1.go = "PlantationCommander_2";
			Link.l2 = "Я хочу снять тебя с занимаемой должности, " + NPChar.name + ".";
			Link.l2.go = "PlantationCommander_Remove";
			Link.l3 = "Решил проведать тебя, " + NPChar.name + ".";
			Link.l3.go = "Exit";
			Diag.TempNode = "PlantationCommander_1";
		break;

		case "PlantationCommander_2":
			DialogExit();
			LaunchPlantation();
			Diag.TempNode = "PlantationCommander_1";
		break;

		case "PlantationCommander_Remove":
			dialog.Text = "Вы уверены?";
			Link.l1 = "Да.";
			Link.l1.go = "PlantationCommander_Removed";
			Link.l2 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			Link.l2.go = "Exit";
			Diag.TempNode = "PlantationCommander_1";
		break;

		case "PlantationCommander_Removed":
			PChar.Plantation.Commander = "";
			dialog.Text = "Замечательно! Быть сухопутной крысой не мой удел.";
			Link.l1 = "Вот и славно.";
			Link.l1.go = "exit_hire";
			Diag.TempNode = "Hired";
		break;

		case "PlantationCommander_Hire":
			dialog.Text = "Что ж. Постараюсь оправдать ваши ожидания.";
			Link.l1 = "Вот и славно. Приступай к своим обязанностям.";
			Link.l1.go = "PlantationCommander_Hired";
			Link.l2 = "Я передумал"+ GetSexPhrase("","а") +".";
			Link.l2.go = "Exit";
			Diag.TempNode = "Hired";
		break;

		case "PlantationCommander_Hired":
			CheckForReleaseOfficer(sti(NPChar.index));
			RemovePassenger(pchar, NPChar);
			PChar.Plantation.Commander = NPChar.id;
			Diag.CurrentNode = "PlantationCommander_1";
			Diag.TempNode = "PlantationCommander_1";

			LAi_Fade("", "");
			ChangeCharacterAddressGroup(NPChar, "CaimanPlantationOffice", "goto", "goto1");
			LAi_SetStayType(NPChar);

			//PChar.quest.SetCommanderToPlantationOffice.win_condition.l1 = "ExitFromLocation";
			//PChar.quest.SetCommanderToPlantationOffice.win_condition.l1.location = PChar.location;
			//PChar.quest.SetCommanderToPlantationOffice.win_condition = "SetCommanderToPlantationOffice";

			DialogExit();
		break;

	        // Помошник по охране - начальник гарнизона
		case "ColonyGuarding_Hovernor_1":
			dialog.Text = "Хм... Пожалуй, я смогу справиться с поставленной задачей.";
			Link.l1 = "Конечно справишься, иначе... Э-э-э... Можешь приступать!";
			Link.l1.go = "ColonyGuarding_Hovernor_2";
			Link.l2 = "Я "+ GetSexPhrase("передумал","передумала") +".";
			Link.l2.go = "Exit";
			Diag.TempNode = "Hired";
		break;

	        case "ColonyGuarding_Hovernor_2":
			CheckForReleaseOfficer(sti(NPChar.index));
			RemovePassenger(pchar, NPChar);
			PChar.Colony.Guardians.Hovernor = NPChar.id;

			LAi_Fade("", "");
			ChangeCharacterAddressGroup(NPChar, "LandGuardingHeadHouse", "goto", "goto3");
			LAi_SetStayType(NPChar);

			Diag.CurrentNode = "ColonyGuarding_Hovernor";
			Diag.TempNode = "ColonyGuarding_Hovernor";
			DialogExit();
	        break;

		case "ColonyGuarding_Hovernor":
			dialog.Text = "Здравствуйте, капитан " + PChar.name + " " + PChar.lastname + ". Чем могу служить?";
			Link.l1 = "Я хочу знать текущие состояние защиты.";
			Link.l1.go = "ColonyGuarding_Hovernor_3";
			Link.l2 = "Я хочу снять тебя с занимаемой должности, " + NPChar.name + ".";
			Link.l2.go = "ColonyGuarding_Hovernor_4";
			Link.l3 = "Я хочу поговорить о найме команды для гарнизона, охраняющего нашу колонию.";
			Link.l3.go = "ColonyGuarding_Hovernor_AutoCrewHire_1";
			Link.l4 = "Решил проведать тебя, " + NPChar.name + ".";
			Link.l4.go = "Exit";
			Diag.TempNode = "ColonyGuarding_Hovernor";
		break;

		case "ColonyGuarding_Hovernor_3":
			dialog.Text = "Хм... О каких именно делах вы хотите осведомиться?";
			Link.l1 = "Меня интересует вопрос о береговой линии.";
			Link.l1.go = "ColonyGuarding_Hovernor_3_1";
			Link.l2 = "Меня интересует вопрос о боевой готовности гарнизона и здоровья жителей.";
			Link.l2.go = "ColonyGuarding_Hovernor_3_2";
			Link.l3 = "Меня интересует вопрос о готовности охраны береговой линии.";
			Link.l3.go = "ColonyGuarding_Hovernor_3_3";
			Link.l4 = "Извини, " + NPChar.name + ", мне необходимо откланяться.";
			Link.l4.go = "Exit";
		break;

		case "ColonyGuarding_Hovernor_3_1":
		    	CheckDeadColonyGuard();
			Diag.TempNode = "ColonyGuarding_Hovernor";
			DialogExit();
			LaunchColonyGuardiang();
		break;

		case "ColonyGuarding_Hovernor_3_2":
			Diag.TempNode = "ColonyGuarding_Hovernor";
			DialogExit();
			LaunchColonyLandGuard();
		break;

		case "ColonyGuarding_Hovernor_3_3":
			CheckDeadColonyGuard();

			if(GetColonyGuardsShipsQuantity() < 1)
			{
				dialog.Text = "Капитан, на данный момент в эскадре нет ни одного корабля...";
				Link.l1 = "Ах да, я и забыл...";
				Link.l1.go = "exit";
				PChar.Colony.Guardians.BaseComplete = false;
				break;
			}

			string sBaseComplete = "";

			if(PChar.Colony.Guardians.BaseComplete == true)
			{
				sBaseComplete = "корабли еженедельно проходят полную комплектацию и всегда готовы к бою. На данный момент сумма, которая необходима для этого, составляет " + GetCostForBaseCompletationAllGuards() + " пиастров.";
			}
			else
			{
				sBaseComplete = "комплектация кораблей береговой линии не производится. Но, имеется возможность каждую неделю проводить осмотр кораблей и проводить их полную комплектацию, чтобы в любой момент дать отпор мерзавцам.";
			}

			dialog.Text = "Хм... В данный момент " + sBaseComplete;

			if(PChar.Colony.Guardians.BaseComplete == true)
			{
				Link.l1 = "Думаю, пока стоит приостановить еженедельную комплектацию. Казна не резиновая...";
				Link.l1.go = "ColonyGuarding_Hovernor_3_3_3";
			}
			else
			{
				if(PChar.Colony.Guardians.BaseComplete.First == true)
				{
					Link.l1 = "Расскажите подробнее об этом.";
					Link.l1.go = "ColonyGuarding_Hovernor_3_3_1";
				}
				else
				{
					Link.l1 = "Думаю, стоит возобновить еженедельную комлектацию охраны береговой линии.";
					Link.l1.go = "ColonyGuarding_Hovernor_3_3_2";
				}
			}

			Link.l2 = "Извините, меня ждут дела.";
			Link.l2.go = "Exit";
			Diag.CurrentNode = "ColonyGuarding_Hovernor";
		break;

		case "ColonyGuarding_Hovernor_3_3_1":
			PChar.Colony.Guardians.BaseComplete.First = false;
			dialog.Text = "Каждую неделю будет проводиться осмотр кораблей охраны береговой линии, и те корабли, которые в данный момент будут охранять её, будут дополнены недостающими боеприпасами и товарами первой необходимости, кроме того будет восполнена и команда \n Но чтобы всё это работало, необходимо будет идти на некоторые траты, которые зависят от комплектуемых кораблей. Например, на данный момент будет необходимо выплачивать из казны колонии по " + GetCostForBaseCompletationAllGuards() + " пиастров в неделю. Если же данная сумма будет отсутствовать, то, к сожалению, комплектовать будет не на что. Что скажете?";
			Link.l1 = "Полезное дело. Я даю разрешение на своевременный расход средств из казны колонии.";
			Link.l1.go = "ColonyGuarding_Hovernor_3_3_2";
			Link.l2 = "Пожалуй, пока обойдёмся без этого.";
			Link.l2.go = "Exit";
		break;

		case "ColonyGuarding_Hovernor_3_3_2":
			PChar.Colony.Guardians.BaseComplete = true;
			Diag.TempNode = "ColonyGuarding_Hovernor";
			DialogExit();
		break;

		case "ColonyGuarding_Hovernor_3_3_3":
			PChar.Colony.Guardians.BaseComplete = false;
			Diag.TempNode = "ColonyGuarding_Hovernor";
			DialogExit();
		break;

		case "ColonyGuarding_Hovernor_4":
			dialog.Text = "Вы уверены?";
			Link.l1 = "Да.";
			Link.l1.go = "ColonyGuarding_Hovernor_5";
			Link.l2 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			Link.l2.go = "Exit";
		break;

		case "ColonyGuarding_Hovernor_5":
			PChar.Colony.Guardians.Hovernor = "";
			dialog.Text = "Замечательно! Быть сухопутной крысой не мой удел.";
			Link.l1 = "Вот и славно.";
			Link.l1.go = "exit_hire";
			Diag.TempNode = "Hired";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_1":
			dialog.Text = "Хорошо, капитан. Чем могу быть полезен в этом вопросе?";
			Link.l1 = "Хотелось бы подробнее узнать о такой возможности.";
			Link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_Info";
			Link.l2 = "Я хочу узнать цены, которые требуются для обеспечивания найма.";
			Link.l2.go = "ColonyGuarding_Hovernor_AutoCrewHire_Costs";
			Link.l3 = "Необходимо пересмотреть объекты, на которых обеспечиваются найм гарнизона.";
			Link.l3.go = "ColonyGuarding_Hovernor_AutoCrewHire_Set";
			Link.l4 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			Link.l4.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Info":
			dialog.Text = "Я могу самостоятельно нанимать команду для гарнизона, чтобы наша колония и постройки, ей принадлежащие, всегда смогли бы дать отпор врагу и усмирить взбунтовавшиеся жителей и рабов. \n Но, как вы понимаете, это будет стоить гораздо больших расходов, чем обычный найм в тавернах архипелага. Каждый раз гарнизон будет доукомплектовываться с учётом текущей комплектации гарнизонов. \n Найм гарнизона можно производить на все объекты - а это наша колония, плантация и рудники. \n Каждый раз в казне колонии должна быть сумма, позволяющая провести найм гарнизона на определённый объект. Если такой суммы в казне не окажется, то найма, соответственно, не произойдёт.";
			Link.l1 = "Спасибо за информацию, " + NPChar.name + ".";
			Link.l1.go = "ColonyGuarding_Hovernor";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Costs":
			dialog.Text = "Цена обеспечения найма каких объектов вас интересует?";

			if(PChar.ColonyBuilding.Stage != "0")
			{
				Link.l1 = "Колония.";
				Link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_Cost_Colony";
			}
			if(PChar.Mines.GoldMine == true || PChar.Mines.SilverMine == true || PChar.Mines.IronMine == true)
			{
				Link.l2 = "Рудники.";
				Link.l2.go = "ColonyGuarding_Hovernor_AutoCrewHire_Cost_Mines";
			}
			if(PChar.ColonyBuilding.Plantation == true && PChar.ColonyBuilding.Plantation.BuildingTime == false)
			{
				Link.l3 = "Плантация.";
				Link.l3.go = "ColonyGuarding_Hovernor_AutoCrewHire_Cost_Plantation";
			}

			Link.l4 = "Извини, мне надо идти.";
			Link.l4.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Cost_Colony":
			dialog.Text = "На данный момент цена обеспечения найма гарнизона колонии - с учётом укомплектованности гарнизона: " + ColonyGuardingGetCostForObject("Colony", false) + " золотых; для полного заполнения без учёта укомплектованности: " + ColonyGuardingGetCostForObject("Colony", true) + " золотых.";
			Link.l1 = LinkRandPhrase("Спасибо.", "Ясно.", "Хорошо.");
			Link.l1.go = "ColonyGuarding_Hovernor";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Cost_Mines":
			dialog.Text = "На данный момент цена обеспечения найма гарнизона рудников - с учётом укомплектованности гарнизона: " + ColonyGuardingGetCostForObject("Mines", false) + " золотых; для полного заполнения без учёта укомплектованности: " + ColonyGuardingGetCostForObject("Mines", true) + " золотых.";
			Link.l1 = LinkRandPhrase("Спасибо.", "Ясно.", "Хорошо.");
			Link.l1.go = "ColonyGuarding_Hovernor";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Cost_Plantation":
			dialog.Text = "На данный момент цена обеспечения найма гарнизона плантации - с учётом укомплектованности гарнизона: " + ColonyGuardingGetCostForObject("Plantation", false) + " золотых; для полного заполнения без учёта укомплектованности: " + ColonyGuardingGetCostForObject("Plantation", true) + " золотых.";
			Link.l1 = LinkRandPhrase("Спасибо.", "Ясно.", "Хорошо.");
			Link.l1.go = "ColonyGuarding_Hovernor";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Set":
			dialog.Text = ColonyGuardingAutoCrewHireGetWork();

			if(PChar.ColonyBuilding.Stage != "0")
			{
				if(PChar.Colony.Guardians.Colony.AutoCrewHire == false)
				{
					Link.l1 = "Я хочу воспользоваться возможностью найма гарнизона для охраны колонии.";
					Link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_On_Colony_1";
				}
				else
				{
					Link.l1 = "Я хочу приостановить найм гарнизона для охраны колонии.";
					Link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_Off_Colony_1";
				}
			}

			if(PChar.Mines.GoldMine == true || PChar.Mines.SilverMine == true || PChar.Mines.IronMine == true)
			{
				if(PChar.Colony.Guardians.Mines.AutoCrewHire == false)
				{
					Link.l2 = "Я хочу воспользоваться возможностью найма гарнизона для охраны рудников.";
					Link.l2.go = "ColonyGuarding_Hovernor_AutoCrewHire_On_Mines_1";
				}
				else
				{
					Link.l2 = "Я хочу приостановить найм гарнизона для охраны рудников.";
					Link.l2.go = "ColonyGuarding_Hovernor_AutoCrewHire_Off_Mines_1";
				}
			}

			if(PChar.ColonyBuilding.Plantation == true && PChar.ColonyBuilding.Plantation.BuildingTime == false)
			{
				if(PChar.Colony.Guardians.Plantation.AutoCrewHire == false)
				{
					Link.l3 = "Я хочу воспользоваться возможностью найма гарнизона для охраны плантации.";
					Link.l3.go = "ColonyGuarding_Hovernor_AutoCrewHire_On_Plantation_1";
				}
				else
				{
					Link.l3 = "Я хочу приостановить найм гарнизона для охраны плантации.";
					Link.l3.go = "ColonyGuarding_Hovernor_AutoCrewHire_Off_Plantation_1";
				}
			}

			Link.l4 = "Извини, мне надо идти.";
			Link.l4.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_On_Colony_1":
			dialog.text = "Вы уверены, капитан?";
			link.l1 = LinkRandPhrase("Да.", "Совершенно точно.", "Конечно же, уверен"+ GetSexPhrase("","а") +".");
			link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_On_Colony_2";
			link.l2 = LinkRandPhrase("Мм... Пожалуй, ты прав - стоит подумать ещё.", "Я передумал"+ GetSexPhrase("","а") +".", "Эээ... Нет, не уверен"+ GetSexPhrase("","а") +".");
			link.l2.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_On_Colony_2":
			PChar.Colony.Guardians.Colony.AutoCrewHire = true;
			dialog.text = "Хорошо, капитан! С сегодняшнего дня займусь этим вопросом.";
			link.l1 = "Вот и славно.";
			link.l1.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_On_Mines_1":
			dialog.text = "Вы уверены, капитан?";
			link.l1 = LinkRandPhrase("Да.", "Совершенно точно.", "Конечно же, уверен"+ GetSexPhrase("","а") +".");
			link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_On_Mines_2";
			link.l2 = LinkRandPhrase("Мм... Пожалуй, ты прав - стоит подумать ещё.", "Я передумал"+ GetSexPhrase("","а") +".", "Эээ... Нет, не уверен"+ GetSexPhrase("","а") +".");
			link.l2.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_On_Mines_2":
			PChar.Colony.Guardians.Mines.AutoCrewHire = true;
			dialog.text = "Хорошо, капитан! С сегодняшнего дня займусь этим вопросом.";
			link.l1 = "Вот и славно.";
			link.l1.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_On_Plantation_1":
			dialog.text = "Вы уверены, капитан?";
			link.l1 = LinkRandPhrase("Да.", "Совершенно точно.", "Конечно же, уверен"+ GetSexPhrase("","а") +".");
			link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_On_Plantation_2";
			link.l2 = LinkRandPhrase("Мм... Пожалуй, ты прав - стоит подумать ещё.", "Я передумал"+ GetSexPhrase("","а") +".", "Эээ... Нет, не уверен"+ GetSexPhrase("","а") +".");
			link.l2.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_On_Plantation_2":
			PChar.Colony.Guardians.Plantation.AutoCrewHire = true;
			dialog.text = "Хорошо, капитан! С сегодняшнего дня займусь этим вопросом.";
			link.l1 = "Вот и славно.";
			link.l1.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Off_Colony_1":
			dialog.text = "Вы действительно хотите приостановить найм команды для гарнизона колонии?";
			link.l1 = LinkRandPhrase("Да.", "Совершенно точно.", "Конечно же, уверен"+ GetSexPhrase("","а") +".");
			link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_Off_Colony_2";
			link.l2 = LinkRandPhrase("Отставить!", "Я, пожалуй, передумал"+ GetSexPhrase("","а") +"..", "Эээ... Нет, не уверен"+ GetSexPhrase("","а") +".");
			link.l2.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Off_Colony_2":
			PChar.Colony.Guardians.Colony.AutoCrewHire = false;
			dialog.text = "Как пожелаете, капитан.";
			link.l1 = LinkRandPhrase("Спасибо.", "Ясно.", "Хорошо.");
			link.l1.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Off_Mines_1":
			dialog.text = "Вы действительно хотите приостановить найм команды для гарнизона рудников?";
			link.l1 = LinkRandPhrase("Да.", "Совершенно точно.", "Конечно же, уверен"+ GetSexPhrase("","а") +".");
			link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_Off_Mines_2";
			link.l2 = LinkRandPhrase("Отставить!", "Я, пожалуй, передумал"+ GetSexPhrase("","а") +"..", "Эээ... Нет, не уверен"+ GetSexPhrase("","а") +".");
			link.l2.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Off_Mines_2":
			PChar.Colony.Guardians.Mines.AutoCrewHire = false;
			dialog.text = "Как пожелаете, капитан.";
			link.l1 = LinkRandPhrase("Спасибо.", "Ясно.", "Хорошо.");
			link.l1.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Off_Plantation_1":
			dialog.text = "Вы действительно хотите приостановить найм команды для гарнизона плантации?";
			link.l1 = LinkRandPhrase("Да.", "Совершенно точно.", "Конечно же, уверен"+ GetSexPhrase("","а") +".");
			link.l1.go = "ColonyGuarding_Hovernor_AutoCrewHire_Off_Plantation_2";
			link.l2 = LinkRandPhrase("Отставить!", "Я, пожалуй, передумал"+ GetSexPhrase("","а") +"..", "Эээ... Нет, не уверен"+ GetSexPhrase("","а") +".");
			link.l2.go = "exit";
		break;

		case "ColonyGuarding_Hovernor_AutoCrewHire_Off_Plantation_2":
			PChar.Colony.Guardians.Plantation.AutoCrewHire = false;
			dialog.text = "Как пожелаете, капитан.";
			link.l1 = LinkRandPhrase("Спасибо.", "Ясно.", "Хорошо.");
			link.l1.go = "exit";
		break;
		// <-- Самостоятельное плавание компаньона
		
		// секс - Мэри не отказывает никогда
		case "Mary_cabin_sex":
			dialog.text = RandPhraseSimple(""+pchar.name+", для меня нет большей радости, чем быть в твоих объятиях, да... Пойдём!",""+pchar.name+", если бы такое было возможно - я бы вообще не расставалась с тобой ни на минуту. Пойдём!");
			link.l1 = RandPhraseSimple("Ты - самая лучшая на свете, моя девочка...","Ты - просто прелесть, моя красавица...");
			link.l1.go = "Mary_cabin_sex_go";
		break;
		
		case "Mary_room_sex":
			dialog.text = RandPhraseSimple(""+pchar.name+", для меня нет большей радости, чем быть в твоих объятиях, да... Пойдём!",""+pchar.name+", если бы такое было возможно - я бы вообще не расставалась с тобой ни на минуту. Пойдём!");
			link.l1 = RandPhraseSimple("Ты - самая лучшая на свете, моя девочка...","Ты - просто прелесть, моя красавица...");
			link.l1.go = "Mary_room_sex_go";
		break;
		
		case "Mary_cabin_sex_go":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			AddCharacterExpToSkill(pchar, "Leadership", 40);
            AddCharacterExpToSkill(npchar, "Leadership", 40);
            AddCharacterExpToSkill(pchar, "Fencing", 15);
            AddCharacterExpToSkill(npchar, "Fencing", 15);
            AddCharacterExpToSkill(pchar, "Pistol", 15);
            AddCharacterExpToSkill(npchar, "Pistol", 15);
            AddCharacterHealth(pchar, 12);
            AddCharacterHealth(npchar, 12);
   			AddDialogExitQuest("PlaySex_1");
			NextDiag.CurrentNode = "Mary_sex_after";
		break;
		
		case "Mary_room_sex_go":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			AddCharacterExpToSkill(pchar, "Leadership", 40);
            AddCharacterExpToSkill(npchar, "Leadership", 40);
            AddCharacterExpToSkill(pchar, "Fencing", 15);
            AddCharacterExpToSkill(npchar, "Fencing", 15);
            AddCharacterExpToSkill(pchar, "Pistol", 15);
            AddCharacterExpToSkill(npchar, "Pistol", 15);
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);
			if (npchar.chr_ai.type == "actor")
			{
				LAi_SetOfficerType(npchar);
				LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			}
			if (findsubstr(locations[FindLocation(pchar.location)].id, "tavern_upstairs" , 0) == -1)
			{
			DoQuestReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "");
			ChangeCharacterAddressGroup(npchar, pchar.location+"_upstairs", "quest", "quest3");
			}
			AddDialogExitQuest("PlaySex_1");
			NextDiag.CurrentNode = "Mary_sex_after";
		break;
		
		case "Mary_sex_after":
			dialog.text = RandPhraseSimple("Милый, ты как всегда - был великолепен!","Всё было просто замечательно, дорогой!");
			link.l1 = RandPhraseSimple("Я рад, что ты довольна, свет души моей...","Я обожаю тебя, Мэри...");
			link.l1.go = "exit";
			sld = characterFromID("SharleMary");
			sld.Dialog.Filename = "Quest\MainheroPrologues\Mary_dialog.c";
			sld.dialog.currentnode = "hired";
			LAi_SetOfficerType(sld);
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.quest.daily_sex = true;
			SetFunctionTimerCondition("Mary_SexReady", 0, 0, 5, false);
		break;
		
		case "Mary_givemesex":	// требует секса, если давно не давал
			dialog.text = RandPhraseSimple(""+pchar.name+", мы так давно не были вместе... Ты совсем забыл про меня, да! Милый, я хочу расслабиться - давай снимем комнату и уединимся!",""+pchar.name+", ты совсем увлёкся делами, и я начинаю подозревать, что и вовсе забыл про меня! Дорогой, я очень хочу... остаться с тобой вдвоём. Давай снимем комнату, да!");
			link.l1 = "Мэри, милая, ну что ты такое говоришь - 'забыл про меня'? Глупости... Но я действительно закрутился со всеми этими проблемами, конца-края им нет. Прости меня, моя девочка. Конечно, пойдём наверх - и пусть весь мир подождёт!";
			link.l1.go = "Mary_room_sex_go";
		break;
		
		// ругается за то, что ходил по борделям, ГГ изворачивается
		case "Mary_brothel":
			dialog.text = "Да, не так! Я тебе больше не нравлюсь, да? Скажи!";
			link.l1 = "Вот так номер! Мэри, что за вздор? С чего ты это взяла?";
			link.l1.go = "Mary_brothel_1";
		break;
		
		case "Mary_brothel_1":
			dialog.text = "Тогда почему ты ходил к этим сучкам, этим бордельным девкам? Я это знаю, да, не отрицай! Я чем-то тебя не устраиваю, когда мы занимаемся любовью, да? (плачет) Скажи...";
			link.l1 = "Мэри, Мэри... успокойся, пожалуйста, девочка. Да, я был в борделе, но исключительно по делам. Понимаешь - по делам, а не для развлечений!";
			link.l1.go = "Mary_brothel_2";
		break;
		
		case "Mary_brothel_2":
			dialog.text = "И в комнату со шлюхами ты тоже 'по делам' поднимался, да? (всхлипывает) Ты врёшь мне, "+pchar.name+"!";
			link.l1 = "Мэри, милая, да перестань же наконец... У меня действительно были дела, с хозяйкой борделя. И наверх я поднимался тоже... вот, в последний раз по личной просьбе губернатора - он просил найти там своё утерянное обручальное кольцо. Ну разве мог я отказать Его Светлости?";
			link.l1.go = "Mary_brothel_5";
		break;
		
		case "Mary_brothel_5":
			dialog.text = "";
			link.l1 = "Видишь? Я же говорю тебе - это деловые визиты. Мэри, мне правда никто кроме тебя не нужен. Ты у меня лучшая, честное слово! Неужели ты думаешь, что я пойду к каким-то грязным портовым шлюхам, когда у меня есть ты? Как тебе такое вообще могло прийти в голову?";
			link.l1.go = "Mary_brothel_6";
		break;
		
		case "Mary_brothel_6":
			dialog.text = ""+pchar.name+"... Это действительно так? Ты не обманываешь? Ты не был с ними?";
			link.l1 = "Мэри, милая, кроме тебя для меня никого не существует, правда. Подойди поближе, дорогая. Дай я тебя обниму... Вытри слёзы, и перестань, наконец, ревновать! Ну хочешь, я больше вообще в бордели заходить не буду!";
			link.l1.go = "Mary_brothel_7";
		break;
		
		case "Mary_brothel_7":
			dialog.text = "Да, хочу!.. "+pchar.name+", я ревную, потому что люблю тебя... И не хочу тебя потерять, да! Слышишь? Я убью любую дрянь, которая только посмеет приблизиться к тебе!";
			link.l1 = "Тише, тише... моя собственница. Никого убивать не потребуется. И ты меня не потеряешь, обещаю. Всё, успокойся. Ты у меня единственная и самая лучшая на свете...";
			link.l1.go = "Mary_brothel_8";
		break;
		
		case "Mary_brothel_8":
			DialogExit();
			SetLaunchFrameFormParam("Прошло несколько минут", "", 0, 5);
			//SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			pchar.GenQuest.BrothelLock = true; // всё, больше не походишь по борделям :)
			DeleteAttribute(pchar, "GenQuest.BrothelCount");
		break;
	}
}

void FireImmortalOfficer(ref chr)
{
	if (CheckAttribute(chr,"ImmortalOfficer"))
	{
		DeleteAttribute(chr,"ImmortalOfficer")
		pchar.Option_ImmortalOfficers = sti(sti(pchar.Option_ImmortalOfficers) - 1);
	}
}
