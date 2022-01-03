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
			dialog.text = "Капитан, что за глупости! Уберите оружие, пока бед не наделали!";
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Не переживай, уже убираю...");
			link.l1.go = "exit";
		break;

		case "hired":
			Diag.TempNode = "Hired";
			// только наняли -->
			if (IsCompanion(NPChar))
			{
				Dialog.text = "Сегодня мы снова выйдем в море!";
				link.l2 = "Да... Я тоже рад"+ GetSexPhrase("","а") +".";
				link.l2.go = "Exit";
				break;
			}
			if (Npchar.location.group == "sit" && !isShipInside(pchar.location))
			{
				dialog.text = "Сейчас я допью, капитан, и отправлюсь на борт. Не извольте беспокоиться - я успею до отплытия.";
				Link.l1 = "Хорошо. Опоздаешь - заставлю драить палубу!";
				Link.l1.go = "Exit";
				break;
			}
			// только наняли <--
   			dialog.text = "Что вы хотите, капитан?";
			if (NPChar.id == "James_Callow") NPChar.faceid = 287;

			if (NPChar.id == "James_Callow")
			{
				dialog.text = "Хочешь надрать пару задниц? Я в твоём распоряжении!";
			}
			if (NPChar.id == "Tichingitu")
			{
				dialog.text = "Тичингиту слушать вас, капитан "+pchar.name+"!";
			}
			if (NPChar.id == "Andreas_Fickler")
			{
				dialog.text = "Что в-в-вы хотите, к-к-капитан "+pchar.name+"!";
			}
			// диалог компаньона на корабле.
			if (CheckAttribute(NPChar, "IsCompanionClone"))
			{
				Link.l2 = "У меня есть для тебя несколько приказов.";
				Link.l2.go = "Companion_Tasks";
				break;
			}

			if (isOfficer(Npchar)) // проверка для кампуса, где слотовые офы
			{
	            Link.l2 = "Слушай мой приказ!";
	            Link.l2.go = "stay_follow";
            }

			//aw013 --> Найм на постоянку

			if (!bHalfImmortalPGG)
			{
				if (!CheckAttribute(NPChar, "OfficerWantToGo.DontGo"))
				{
					Link.l3contract = "У меня к тебе предложение.";
					Link.l3contract.go = "contract";
				}
			}
			else
			{
				if (!CheckAttribute(pchar,"Option_ImmortalOfficers"))
				{
					pchar.Option_ImmortalOfficers = "0";
				}
				if (sti(pchar.Option_ImmortalOfficers) < makeint(GetCharacterSPECIAL(pchar,"Charisma")*2) && !CheckAttribute(npchar,"ImmortalOfficer"))
				{
					Link.l3contract = "У меня к тебе предложение.";
					Link.l3contract.go = "contract";
				}
			}
			//aw013 <-- Найм на постоянку
           		// boal отчет о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l8 = "Дай мне полный отчёт о корабле, " + GetStrSmallRegister(XI_ConvertString("treasurer")) + ".";
			    Link.l8.go = "QMASTER_1";

			    Link.l11 = "Давай обсудим, какое количество товаров и предметов нужно закупать в магазинах.";
			    Link.l11.go = "TransferGoodsEnable";
			}

			if (npchar.id != "Sharp_Sibling" && npchar.id != "SharleMary")
			{
				Link.l4 = "Офицер, я более не нуждаюсь в ваших услугах.";
				Link.l4.go = "AsYouWish";
			}

			for(iTemp=1; iTemp<=3; iTemp++) // Нужно, чтоб была свободная группа
			{
				attr = "Companion" + iTemp;
				if (CheckAttribute(PChar,"CompanionTravel."+(attr)+".ID"))
				{
					if (PChar.CompanionTravel.(attr).ID == NPChar.ID)
					{
						Link.l4 = "Возвращайся в эскадру, офицер.";
						Link.l4.go = "CompanionTravel_ToSquadron";
					}
				}
			}

			// приколы -->
			if (PChar.sex == "woman" && !CheckAttribute(pchar, "questTemp.MainHeroWoman"))
			{//Запускаем счетчик для отката
				pchar.questTemp.MainHeroWoman = true;
				SaveCurrentQuestDateParam("pchar.questTemp.MainHeroWomanSex");
			}

            if (PChar.location == Get_My_Cabin() && npchar.id != "Sharp_Sibling" && GetQuestPastDayParam("pchar.questTemp.MainHeroWomanSex") >= 5)
            {
    			if (PChar.sex == "woman" && NPChar.sex == "man")
    			{
					Link.l5 = RandPhraseSimple("Раз уж мы в каюте давай может...а? Посмотри тут и кровать есть... такая мягенькая...",
	                                           "Посмотри какая в моей каюте большая кровать. Не хочешь разделить ее со мной?");
	                if (drand(70) < sti(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)) || CheckAttribute(npchar, "devoted"))
	                {
	                    Link.l5.go = "Love_Sex_Yes";
	                }
	                else
	                {
	                    Link.l5.go = "Love_Sex";
	                }
                }
            }

			if (PChar.location == Get_My_Cabin() && npchar.id != "Sharp_Sibling")
            {
    			if (PChar.sex != "woman" && NPChar.sex == "woman")
    			{
					Link.l3 = RandPhraseSimple("Раз уж мы в каюте давай может...а? Посмотри тут и кровать есть... такая мягенькая...",
	                                           "Посмотри какая в моей каюте большая кровать. Не хочешь разделить ее со мной?");
	                if (sti(pchar.GenQuest.BrothelCount) > 4+rand(3))
	                {
	                    Link.l3.go = "Man_Love_Sex_Yes";
	                }
	                else
	                {
	                    Link.l3.go = "Man_Love_Sex";
	                }
                }
                if (!CheckAttribute(pchar, "questTemp.FUNY_SHIP_FIND") && NPChar.sex == "woman" && GetCharacterItem(PChar, "mineral4") >= 25)
                {
                    Link.l4 = "Смотри какая у меня коллекция собралась интересная!";
            		Link.l4.go = "FUNY_SHIP_1";
                }
            }
            else
            {
                if (PChar.sex != "woman" && NPChar.sex == "woman" && npchar.id != "Sharp_Sibling")
                {
					Link.l3 = RandPhraseSimple("Девушка-телохранитель - это, конечно, хорошо, но может мы попытаемся сталь ближе?",
	                                           "Как насчет неуставных услуг?");
	                Link.l3.go = "Man_Love_Sex";
                }
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
			/*
			if(npchar.id == "Mechanic1")
			{
				if (CheckCharacterItem(pchar, "pistol7") || CheckCharacterItem(pchar, "pistol7shotgun"))
				{
					Link.lcraftMechanic = "Механик, у меня есть к тебе один вопрос, как раз по твоей специализации.";
					Link.lcraftMechanic.go = "mechanic_craft_ammo";
				}
				if (CheckAttribute(pchar,"craftingAmmo"))
				{
					Link.lcraftMechanic = "Как успехи? Получилось что-то изготовить?";
					Link.lcraftMechanic.go = "mechanic_craft_ammo_finish";
				}
			}*/
			if (CheckAttribute(pchar, "WhisperPGG") && npchar.id == pchar.WhisperPGG)
			{
				if (CheckAttribute(pchar, "CabinHelp"))
				{
					if(Pchar.CabinHelp == true)
					{
						Link.WhisperCabinHelp = "Я больше не зочу, чтобы ты сопровождала меня в каютах.";
						Link.WhisperCabinHelp.go = "WhisperCabinHelp";
					}
					else
					{
						Link.WhisperCabinHelp = "Я хочу, чтобы ты помогала мне в каютах.";
						Link.WhisperCabinHelp.go = "WhisperCabinHelp";
					}
				}
				if(GetCharacterItem(npchar, "pistol7shotgun") >= 1)
				{
					Link.WhisperWeapons = "У тебя необычное оружие. Можно мне взглянуть?";
					Link.WhisperWeapons.go = "WhisperWeapons";
				}

			}
			if(npchar.id == "W_chinaman" && CheckAttribute(pchar, "Whisper.GiveChinaSword") && CheckCharacterItem(pchar, "blade_china"))
			{
				Link.wChinaSword = "Посмотри, что у меня для тебя есть. Было непросто, но все же я достала твой меч.";
				Link.wChinaSword.go = "w_give_china_sword";
			}
            Link.l12 = "Ничего. Вольно.";
            Link.l12.go = "Exit";
        break;

		case "FUNY_SHIP_1":
		    dialog.text = "О ужас! Капитан, уберите от меня это, такая невыносимая вонь... вы что верите во всю эту чушь старой легенды про получение непобедимого бойца?";
   			Link.l1 = "Нет, конечно, извини. Пойду выкину всю эту воняющую массу за борт.";
            Link.l1.go = "exit";
            Link.l2 = "Да, верю! Мало того, проверю. Ну-ка, подходи ближе!";
            Link.l2.go = "FUNY_SHIP_2";
        break;

        case "FUNY_SHIP_2":
		    dialog.text = "Ну и вонь! Фу... хотя работает, я чувствую себя сильнее и даже, хм, красивее.";
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

		case "WhisperCabinHelp":
			dialog.text = "Договорились.";
            Link.l1 = "Вот и хорошо.";
            Link.l1.go = "exit";
			pchar.CabinHelp = !sti(pchar.CabinHelp);
		break;

		case "WhisperWeapons":
			dialog.text = "Можешь взять мой меч, если хочешь. Но дробовик я не доверю никому, уж слишком многое мне пришлось сделать, чтобы его вернуть, сам"+ GetSexPhrase("","а") +" ведь знаешь. Да и не думаю, что кто-то кроме меня разберётся, как им пользоваться.";
            Link.l2 = "Понятно.";
            Link.l2.go = "exit";
			Link.l1 = "Я видел"+ GetSexPhrase("","а") +", ты используешь для него какие-то особые боеприпасы?";
            Link.l1.go = "WhisperWeapons_1";
		break;
		case "WhisperWeapons_1":
			dialog.text = "Да. Такие вряд ли можно купить где-либо на Карибах, так что я изготавливаю их сама. Получается немного, но, думаю, со временем я наловчусь и смогу делать больше.";
            Link.l2 = "Ясно.";
            Link.l2.go = "exit";
		break;

		case "w_give_china_sword":
			dialog.text = "Я не верить своим глазам... Это и правда он, меч моей семьи. Мне нечего предложить вам взамен, кроме своей вечной преданности. Если доверите охранять вас, я буду защищать вашу жизнь прежде своей.";
			TakeItemFromCharacter(pchar, "blade_china");
			if (pchar.equip.blade == "blade_china")
			{
				RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			}
			LAi_SetHP(npchar, 100.0 + LAi_GetCharacterMaxHP(npchar), 100.0 + LAi_GetCharacterMaxHP(npchar));
			AddBonusEnergyToCharacter(npchar, 50);
			GiveItem2Character(npchar, "blade_china");
			EquipCharacterByItem(npchar, "blade_china");
			npchar.Skill.Sailing    = sti(npchar.Skill.Sailing) + 20;
			if (sti(npchar.Skill.Sailing) > 100) npchar.Skill.Sailing = 100;
			npchar.Skill.FencingHeavy  = sti(npchar.Skill.FencingHeavy) + 20;
			if (sti(npchar.Skill.FencingHeavy) > 100) npchar.Skill.FencingHeavy = 100;
			npchar.perks.FreePoints_self = sti(npchar.perks.FreePoints_self) + 1;
			npchar.perks.FreePoints_ship = sti(npchar.perks.FreePoints_ship) + 2;
			npchar.rank = sti(npchar.rank) + 5;
			npchar.perks.list.AgileMan = "1";
			ApplayNewSkill(npchar, "AgileMan", 0);
			npchar.devoted = true;
			DeleteAttribute(pchar, "Whisper.GiveChinaSword")
            link.l1 = "Преданности мне вполне достаточно. Ладно, оставлю тебя наедине с твоей 'игрушкой'.";
			link.l1.go = "exit";
		break;

		case "mechanic_craft_ammo_finish":
		    dialog.text = "Не торопите меня, капитан. Я же говорил вам, когда закончу.";
            link.l1 = "Ладно, извини. Просто не терпится уже пострелять.";
			link.l1.go = "exit";
			if (GetQuestPastDayParam("pchar.questTemp.craftingAmmo") >= sti(pchar.ammoCraftDays))
			{
				dialog.text = "Еще бы. Пожалуйста, забирайте. Я сделал 50 экземпляров. Смотрите, не израсходуйте все сразу.";
				link.l1 = "Благодарю. Ты гений!";
				link.l1.go = "exit";
				DeleteAttribute(pchar,"craftingAmmo");
				switch(pchar.ammoCrafttype)
				{
					case "shotgun":
						TakeNItems(Pchar, "12_gauge", 50);
					break;
					case "colt":
						TakeNItems(Pchar, "GunCap_colt", 50);
						TakeNItems(Pchar, "shotgun_cartridge", 50);
					break;
					case "both":
						TakeNItems(Pchar, "12_gauge", 50);
						TakeNItems(Pchar, "GunCap_colt", 50);
						TakeNItems(Pchar, "shotgun_cartridge", 50);
					break;
				}
			}
        break;
		case "mechanic_craft_ammo":
			if (!CheckAttribute(npchar,"ammoCraftedOnce"))
			{
				dialog.text = "Да неужели? Вы меня заинтриговали, капитан.";
				link.l1 = "Дело в том, что мне принадлежит некое устройство - оружие. Оно работает исправно, однако для его использования необходимы специальные боеприпасы. Не затруднит ли тебя их изготовить?";
				link.l1.go = "mechanic_craft_ammo_1";
			}
			else
			{
				dialog.text = "Снова хотите, чтобы я сделал вам боеприпасы?";
				link.l1 = "Читаешь мои мысли.";
				link.l1.go = "mechanic_craft_ammo_1";
			}
        break;
		case "mechanic_craft_ammo_1":
			if (!CheckAttribute(npchar,"ammoCraftedOnce"))
			{
				dialog.text = "Хм... Можно взглянуть на ваше устройство?";
			}
			else
			{
				dialog.text = "Напомните пожалуйста, что там у вас за устройство?";
			}
			link.l1 = "А знаешь, забудь.";
			link.l1.go = "exit";
			if (!CheckCharacterItem(pchar, "pistol7") && CheckCharacterItem(pchar, "pistol7shotgun"))
			{
				pchar.ammoCrafttype = "shotgun";
				link.l2 = "(Показать шотган)";
				link.l2.go = "mechanic_craft_ammo_3";
			}
			if (CheckCharacterItem(pchar, "pistol7") && !CheckCharacterItem(pchar, "pistol7shotgun"))
			{
				pchar.ammoCrafttype = "colt";
				link.l2 = "(Показать револьвер)";
				link.l2.go = "mechanic_craft_ammo_3";
			}
			if (CheckCharacterItem(pchar, "pistol7") && CheckCharacterItem(pchar, "pistol7shotgun"))
			{
				pchar.ammoCrafttype = "both";
				link.l2 = "(Показать ему шотган и револьвер)";
				link.l2.go = "mechanic_craft_ammo_3";
			}
        break;
		case "mechanic_craft_ammo_3":
			pchar.ammoCrafPrice = 50000;
			pchar.ammoCraftDays = 14;
			string sDays = " дней.";
			if (pchar.ammoCrafttype == "both")
			{
				pchar.ammoCraftPrice = 100000;
				pchar.ammoCraftDays = 21;
				sDays = " день.";
			}
			string sTemp = "Я возьму " + pchar.ammoCraftPrice + " пиастров за работу. Все будет готово приблизительно через " + pchar.ammoCraftDays + sDays;
		    if (!CheckAttribute(npchar,"ammoCraftedOnce"))
			{
				dialog.text = "Любопытный механизм. Ну-ка, дайте взгляну поближе\nОчень занятнок у вас устройство, капитан! Да, думаю, я смогу изготовить боеприпас, который подошли бы сюда. Но сами понимаете, на это потребуются время и деньги на материал, а также на оплату моего труда. " + sTemp;
			}
			else
			{
				dialog.text = "Ага, теперь я вспомнил. " + sTemp;
			}
			if (sti(pchar.money)>=sti(pchar.ammoCraftPrice))
			{
				link.l1 = "В таком случае, приступай за работу. Вот деньги.";
				link.l1.go = "mechanic_craft_ammo_4";
			}
			link.l2 = "У меня сейчас нет денег на такие расходы. Поговорим об этом в другой раз.";
			link.l2.go = "exit";
			npchar.ammoCraftedOnce = true;
        break;
		case "mechanic_craft_ammo_4":
			AddMoneyToCharacter(pchar, -sti(pchar.ammoCraftPrice));
			pchar.craftingAmmo = true;
			SaveCurrentQuestDateParam("pchar.questTemp.craftingAmmo");
			dialog.text = "Слушаюсь, капитан!";
			link.l1 = "Буду ждать с нетерпением твоих результатов.";
			link.l1.go = "exit";
        break;

		case "Love_Sex_Yes":
		    dialog.text = RandPhraseSimple("Пожалуй, такой красотке грех отказывать.",
                                           "Я готов пойти на все ради вас, капитан.");
            link.l1 = RandPhraseSimple("Oh, Yes!", "Умничка! Если постараешься, быть может получишь в этом месяце премию.");
			link.l1.go = "Love_Sex_Yes_2";
        break;

        case "Love_Sex_Yes_2":
            AddCharacterExpToSkill(pchar, "Leadership", 100);
            AddCharacterExpToSkill(pchar, "Fencing", -50);// утрахала
            AddCharacterExpToSkill(pchar, "Pistol", -50);
            AddCharacterHealth(pchar, 10);
			SaveCurrentQuestDateParam("pchar.questTemp.MainHeroWomanSex");
   			AddDialogExitQuest("PlaySex_1");
			NextDiag.CurrentNode = "After_sex";
			DialogExit();
        break;

        case "After_sex":
            NextDiag.TempNode = "Hired";
		    dialog.text = RandPhraseSimple("Вы как всегда на высоте, капитан.",
                                           "Капитан, надеюсь, вам все понравилось, я старался.");
            link.l1 = RandPhraseSimple("Да, мы отлично провели время.", "Ага. теперь вернемся к нашим делам.");
			link.l1.go = "exit";
        break;

        case "Love_Sex":
            NextDiag.TempNode = "Hired";
		    dialog.text = RandPhraseSimple("Что!!!?? Капитан, вы давно не сходили на берег и не были в борделе?", "Не понимаю, о чем это вы?");
            link.l1 = RandPhraseSimple("Ну сам подумай.. ты такой красавичик, да еще и в моем подчинении", "Ну не идти же мне в бордель, когда под боком есть ты!");
			link.l1.go = "Love_Sex_2";
			link.l2 = RandPhraseSimple("Извини меня, красавчик, очень трудно было удержаться, чтоб не предложить..", "Эх.. ладно, проехали...");
			link.l2.go = "exit";
        break;

        case "Love_Sex_2":
            NextDiag.TempNode = "Hired";
		    dialog.text = RandPhraseSimple("Капитан! Держите себя в руках, если не можете в своих, позовите матросов!", "То, что я офицер и номинально подчиняюсь Вам, капитан, еще ничего не значит!");
            link.l1 = RandPhraseSimple("Малыш, не протився. Я уже не могу себя сдерживать. Пойдем..", "Я - твой капитан! И я приказываю тебе!");
			link.l1.go = "Love_Sex_3";
			link.l2 = RandPhraseSimple("Извини меня, малыш, очень трудно было удержаться, чтоб не предложить..", "Эх.. ладно, проехали...");
			link.l2.go = "exit";
        break;

        case "Love_Sex_3":
            NextDiag.TempNode = "Hired";
		    dialog.text = RandPhraseSimple("Ну все! Вы ответите за это! И прямо сейчас!", "Покувыркаться с вами? Чтож сейчас поглядим, кто на что способен..");
            link.l1 = "Э.. ты о чем?";
			link.l1.go = "Love_Sex_4";
        break;

        case "Love_Sex_4":
            ChangeCharacterReputation(pchar, -15);
            CheckForReleaseOfficer(GetCharacterIndex(Npchar.id));
			RemovePassenger(Pchar, Npchar);
            LAi_SetWarriorType(Npchar);
            LAi_group_MoveCharacter(Npchar, "TmpEnemy");
            LAi_group_SetHearRadius("TmpEnemy", 100.0);
            LAi_group_FightGroupsEx("TmpEnemy", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
			DeleteAttribute(Npchar,"HalfImmortal");
			Npchar.LifeDay = 0;
			if (PChar.location == Get_My_Cabin() || findsubstr(PChar.location, "_tavern" , 0) != -1)
            {
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
                LAi_group_SetCheck("TmpEnemy", "CannotFightCurLocation");
				LAi_group_SetCheck("TmpEnemy", "MainHeroFightModeOff");
            }
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
        break;

		//Мужской ГГ
		case "Man_Love_Sex_Yes":
		    dialog.text = RandPhraseSimple("Пожалуй, такому ловеласу можно и уступить.",
                                           "Хорошо, все лучше, чем транжирить деньги на уличных девок.");
            link.l1 = RandPhraseSimple("Oh, Yes!", "Умничка, не идти же мне в бордель, когда под боком есть такая лапа как ты!");
			link.l1.go = "Man_Love_Sex_Yes_2";
        break;

        case "Man_Love_Sex_Yes_2":
            pchar.GenQuest.BrothelCount = 0;
            AddCharacterExpToSkill(pchar, "Leadership", 100);
            AddCharacterExpToSkill(pchar, "Fencing", -50);// утрахала
            AddCharacterExpToSkill(pchar, "Pistol", -50);
            AddCharacterHealth(pchar, 10);

   			AddDialogExitQuest("PlaySex_1");
			NextDiag.CurrentNode = "Man_After_sex";
			DialogExit();
        break;

        case "Man_After_sex":
            NextDiag.TempNode = "Hired";
		    dialog.text = RandPhraseSimple("Хм.. странно, я думала ты способен на большее...",
                                           "Капитан, теперь вы снова можете соображать головой, а не... ? Вернемся к нашим делам.");
            link.l1 = RandPhraseSimple("Но-но! Как ты разговариваешь со старшим по званию!", "Я могу многое, если соберусь с мыслями.");
			link.l1.go = "exit";
        break;

        case "Man_Love_Sex":
            NextDiag.TempNode = "Hired";
		    dialog.text = RandPhraseSimple("Что!!!?? Капитан, ты давно не сходил на берег и не был в борделе?", "Не понимаю, о чем это ты?");
            link.l1 = RandPhraseSimple("Ну сама подумай.. ты такая красавица, да еще и в моем подчинении", "Ну не идти же мне в бордель, когда под боком есть ты!");
			link.l1.go = "Man_Love_Sex_2";
			link.l2 = RandPhraseSimple("Извини меня, крошка, очень трудно было удержаться, чтоб не предложить..", "Эх.. ладно, проехали...");
			link.l2.go = "exit";
        break;

        case "Man_Love_Sex_2":
            NextDiag.TempNode = "Hired";
		    dialog.text = RandPhraseSimple("Капитан! Держите себя в руках, если не можете в своих, позовите матросов", "То, что я офицер и номинально подчиняюсь Вам, капитан, еще ничего не значит!");
            link.l1 = RandPhraseSimple("Детка, не протився. Я уже не могу себя сдерживать. Пойдем..", "Я - твой капитан! И я приказываю тебе!");
			link.l1.go = "Man_Love_Sex_3";
			link.l2 = RandPhraseSimple("Извини меня, крошка, очень трудно было удержаться, чтоб не предложить..", "Эх.. ладно, проехали...");
			link.l2.go = "exit";
        break;

        case "Man_Love_Sex_3":
            NextDiag.TempNode = "Hired";
		    dialog.text = RandPhraseSimple("Ну все! Ты ответишь за это! И прямо сейчас!", "Покувыркаться с тобой? Чтож сейчас поглядим, кто на что способен..");
            link.l1 = "Э.. ты о чем?";
			link.l1.go = "Man_Love_Sex_4";
        break;

        case "Man_Love_Sex_4":
            ChangeCharacterReputation(pchar, -15);
            CheckForReleaseOfficer(GetCharacterIndex(Npchar.id));
			RemovePassenger(Pchar, Npchar);
            LAi_SetWarriorType(Npchar);
            LAi_group_MoveCharacter(Npchar, "TmpEnemy");
            LAi_group_SetHearRadius("TmpEnemy", 100.0);
            LAi_group_FightGroupsEx("TmpEnemy", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
			DeleteAttribute(Npchar,"HalfImmortal");
			Npchar.LifeDay = 0;
			if (PChar.location == Get_My_Cabin() || findsubstr(PChar.location, "_tavern" , 0) != -1)
            {
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
                LAi_group_SetCheck("TmpEnemy", "CannotFightCurLocation");
				LAi_group_SetCheck("TmpEnemy", "MainHeroFightModeOff");
            }
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
        break;
        // приколы <--

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

		//aw013 --> Найм на постоянку
		case "contract":
			dialog.text = "Слушаю вас внимательно, капитан.";
			Link.l1 = "Ты хороший офицер и полностью мне подходишь. Хочу предложить тебе пойти ко мне на службу по контракту.";
			Link.l1.go = "contract2";
		break;

		case "contract2":
			dialog.text = "Спасибо за добрые слова, капитан. А какие условия по контракту?";
			Link.l1 = "Большая единоразовая оплата. Экипировка получше, "+ NPCharSexPhrase(NPChar,"сам","сама") +" понимаешь. Срок контракта 10 лет. Уволиться можешь по истечению срока, а если всё будет устраивать нас обоих, продлеваем дальше.";
			Link.l1.go = "contract3";
		break;

		case "contract3":
			NPChar.contractMoney = makeint(sti(NPChar.rank)*MOD_SKILL_ENEMY_RATE*1000);
			dialog.text = "Заманчивое предложение, ничего не скажешь. На спокойную старость заработать немного. А как насчёт небольших подьёмных для постоянного состава?";
			if (sti(Pchar.money) >= sti(NPChar.contractMoney))
			{
				Link.l1 = "Ничего против не имею, " + sti(NPChar.contractMoney) + " золотых прямо сейчас на руки тебя устроит?";
				Link.l1.go = "contract4";
			}
			Link.l2 = "Ничего против не имею, но давай вернёмся к этому разговору позже.";
			Link.l2.go = "Exit";
		break;

		case "contract4":
			dialog.text = "Вполне, капитан. Я согласен.";
			AddMoneyToCharacter(Pchar, -sti(NPChar.contractMoney));
			SetCharacterPerk(NPChar, "EnergyPlus");
			SetCharacterPerk(NPChar, "HPPlus");
			NPChar.OfficerWantToGo.DontGo = true;
			NPChar.loyality = MAX_LOYALITY;
			NPChar.Reputation = 50;
			DeleteAttribute(NPChar, "alignment");
			if (bHalfImmortalPGG)
			{
				if (!CheckAttribute(pchar,"Option_ImmortalOfficers"))
				{
					pchar.Option_ImmortalOfficers = "1";
				}
				else
				{
					pchar.Option_ImmortalOfficers = sti(sti(pchar.Option_ImmortalOfficers) + 1);
				}
				//pchar.PGG_hired = true;
				NPChar.ImmortalOfficer = true;
				NPChar.HalfImmortal = true;  // Контузия
				//string immortal_officer = npchar.id;
				//pchar.quest.(immortal_officer).win_condition.l1 = "NPC_Death";
				//pchar.quest.(immortal_officer).win_condition.l1.character = npchar.id;
				//pchar.quest.(immortal_officer).function = "Remove_Contract_Officer";
			}
			// DeleteAttribute(NPChar, "contractMoney");//Mett: это можно заблокировать по желанию, мб потом понадобиться для перерасчета суммы контракта
			Link.l1 = "Вот и отлично! Договорились";
			Link.l1.go = "Exit";
		break;
		//aw013 <-- Найм на постоянку
		// boal 29.05.04 офицер хочет свалить -->
        case "WantToGo":
			chrDisableReloadToLocation = false;
			Diag.TempNode = "Hired";
			dialog.text = LinkRandPhrase(LinkRandPhrase("Капитан, тут такое дело... В общем, прошу отставки. Мне уж давно жениться пора, якорь бросить в тихой гавани да детишек завести, а я всё места себе не согрею. Так на старости лет и воды подать будет некому.","Капитан, дайте мне отставку, а то я столько лет по всему миру мотаюсь, а ничего толком и не видел. Хочу вкусить другой жизни, якорь бросить, да на мир другими глазами посмотреть.","Капитан, морская служба это, конечно, неплохо - прибыльно и приключения разные, но надо и о себе подумать. Бросить якорь в тихой гавани, домишко купить да деток завести. Вы уж отпустите меня."), LinkRandPhrase("Капитан, я конечно извиняюсь, но эти режимы с вахтами да дисциплинами так приелись, что просто тошно. Хочу некоторое время загулять вольной жизнью. Понимаю, что ждать не будете, поэтому прошу отставки.","Капитан, мне тут судёнышко по случаю подвернулось. Когда-то ведь нужно и своим делом обзаводиться. Отпустите на вольные хлеба - дайте отставку.","Капитан, мне тут место в порту предложили. Я ведь давно мечтаю якорь бросить да семьёй обзавестись. Дайте отставку - когда ещё такой случая подвернётся."), LinkRandPhrase("Капитан, меня от моря уже с души воротит. Доктора говорят - идиосинкразия. Отпустите, ради Христа, иначе когда-нибудь не выдержу - за борт сигану.","Капитан, видать пришла мне пора остепениться да поспокойнее место найти. Шальные пули пугать стали, перед каждым абордажем молю Спасителя, чтобы жизнь сохранил... А невинноубиенные по ночам так и мерещатся - всё пощады просят... Дайте отставку, будьте человеком.","Капитан, старые раны ноют - сил нет, да и контузия недавняя жизни не даёт. Ещё немного и вы меня сами выгоните, кто тогда на службу возьмёт? Дайте отставку - подлечусь да буду искать место поспокойнее."));
			Link.l1 = RandPhraseSimple(LinkRandPhrase("Хм, эдак все разбегутся... Но неволить не стану - иди, коль решил.","Ну что ж, причина понятна. Рано или поздно всё заканчивается. Иди... да не обессудь, если обидел"+ GetSexPhrase("","а") +" когда.","Ну что за народ! Так и норовит улизнуть в самый неподходящий момент!.. Иди, какой из тебя теперь вояка..."), LinkRandPhrase("С трудом верится. Чего-то ты не договариваешь... Ну да ладно, клятву на Библии я у тебя не принимал"+ GetSexPhrase("","а") +", так что гуляй с чистой совестью.","Вот уж не ждал"+ GetSexPhrase("","а") +" от тебя это услышать! Столько времени бок о бок... любого мог"+ GetSexPhrase("","ла") +" подозревать, только не тебя. Право не люблю разочаровываться в людях... собирай вещи и не попадайся мне больше на глаза.","Это дело серьёзное - удерживать не стану... Хотя мне тебя будет очень не хватать."));
			Link.l1.go = "WantToGo_free";
			if (sti(Pchar.money) >= sti(NPChar.rank)*250)
			{
				Link.l2 = LinkRandPhrase("Да-а, вот видишь, как всё обернулось... а я ведь на тебя рассчитывал... Ну, раз решение принято - давай расставаться. Вот тебе "+sti(NPChar.rank)*250+" золотых за верную службу. И не держи зла, если когда обидел.", "Ну что ж, я зла не держу и худого не помню. Раз решил - иди. Да держи "+sti(NPChar.rank)*250+" золотых на дорожку. Это всегда пригодится.", "Ясно... рано или поздно это должно было случиться. Презентую тебе "+sti(NPChar.rank)*250+" золотых на обустройство личной жизни. Да здоровье поправь, морская служба она не сахар - на всю жизнь след оставляет...");
				Link.l2.go = "Im_kind_A2_1";
			}
			Link.l3 = LinkRandPhrase("Вот, значит, как. А ты хоть понимаешь, что сейчас твой уход для меня, как нож в спину? Не могу сейчас я тебя отпустить - даже не проси и не думай.", "Вот это новость! О таких вещах принято предупреждать заранее. Так что о личной жизни пока забудь. Когда придёт время, я сам"+ GetSexPhrase("","а") +" предложу тебе отставку.", "Никаких отставок. У меня каждый человек на счету. Не могу я, из личной прихоти каждого, командой разбрасываться. Служи, пока я сам"+ GetSexPhrase("","а") +" не приму решение.");
			Link.l3.go = "WantToGo_Stay";
		break;

		case "Im_kind_A2_1":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*250)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterReputation(pchar, 1);
			dialog.text = "Спасибо вам, капитан! Какая неожиданная щедрость. У меня тут осталось кое-что из ваших вещей, может желаете их вернуть?";
			Link.l1 = "Да пожалуй... Сейчас найти хороший клинок ой как непросто...";
			Link.l1.go = "Get_out_А2_chang";
			Link.l2 = "Не нужно. Оставь себе в память о службе под моим началом...";
			Link.l2.go = "WantToGo_free";
		break;
		case "WantToGo_Stay":
			dialog.text = RandPhraseSimple("Но как же так? Невольников, и тех на берег списывают. А я всё же не раб и вправе решать свою судьбу!", "Капитан, неужели я за всё своё усердие не заслужил права самостоятельно решать свою судьбу?");
			Link.l1 = LinkRandPhrase("Вижу, так просто тебя не удержать. Как насчёт финансовой поддержки? Такое дело всегда пригодится - и гнёздышко в тихой гавани организовать, и здоровье поправить...", "Ладно, поведём разговор по-другому. За какую сумму ты бы готов остаться?", "Тут ты прав. А как насчёт единоразового денежного пособия?");
			Link.l1.go = "WantToGo_Stay_2";
			Link.l2 = PCharRepPhrase(
				RandPhraseSimple("Э-э нет, тут ты ошибаешься... Пока ты протирал штаны в таверне, можно было решать свою судьбу самолично... Но как только взошёл на борт моего судна - всё... теперь её решать буду я...", "Хм, это серьёзное заявление. Видать, уже не помнишь, как я тебя наш"+ GetSexPhrase("ел","ла") +" - в вонючей таверне без гроша в кармане. Да тебе даже издалека золото нельзя показывать - оно сразу в ром превращается, а туда же - 'решать свою судьбу'."),
				LinkRandPhrase("Пока ты у меня на службе, решения буду принимать я. Изволь вернуться к своим обязанностям, если не хочешь окончательно испортить со мной отношения!", "Хм. Это серьёзное заявление. Но ты ещё не отработал всех уплаченных тебе денег. Поэтому твой демарш я вправе расценивать, как попытку шантажа.", "Понятно...А давай-ка вспомним судовой устав. Пункт второй гласит: 'Если кто задумает бежать... да будет высажен на пустынном берегу с флягой пороха, флягой воды, одним ружьем и пулями.' Ну как тебе такой поворот?"));
			Link.l2.go = "WantToGo_Stay_force";
		break;

	case "WantToGo_Stay_2":
		dialog.text = LinkRandPhrase("Ну, это меняет дело. "+sti(NPChar.rank)*500+" золотых на руки и я остаюсь.", "Ну, пожалуй за "+sti(NPChar.rank)*500+" золотых я бы остался.", "Хм, раз пошёл такой разговор, то за "+sti(NPChar.rank)*500+" золотых можно и послужить ещё.");
		if (sti(Pchar.money) >= sti(NPChar.rank)*500)
		{
			Link.l1 = RandPhraseSimple("Вот и договорились.", "Хорошо. Хотя мог бы быть поскромнее...", "Экие у тебя аппетиты! Ну, раз обещал - держи.");
			Link.l1.go = "WantToGo_Stay_ForMoney";
		}
		Link.l2 = LinkRandPhrase("Ну, это ты загибаешь. За такие деньги можно двух офицеров нанять. Пожалуй, проще тебя отпустить.", "Высоко же ты себя ценишь. Пожалуй, отпущу на вольные хлеба. Но увидишь - там тоже не мёдом намазано.", "Я не готов"+ GetSexPhrase("","а") +" платить такие деньги. Можешь идти, но назад не просись - я измен не прощаю.");
		Link.l2.go = "WantToGo_free";
	break;

	case "WantToGo_Stay_force":
		Npchar.loyality = makeint(Npchar.loyality) - 2;
		dialog.text = "Ну ладно, раз такое дело - остаюсь... Но знайте, что я поступаю против своей воли...";
		Link.l1 = LinkRandPhrase("Вот и хорошо. Возвращайся к своим обязанностям, а этот разговор мы продолжим позже.", "Сейчас возвращайся на борт. И в следующий раз хорошенько подумай, прежде, чем просить об отставке.", "Вот-вот. Служба - есть служба, и нечего потакать своим фантазиям.");
		Link.l1.go = "exit";
	break;

	case "WantToGo_Stay_ForMoney":
		Diag.TempNode = "Hired";
		NPChar.greeting = "Gr_Officer";
		AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
		Npchar.loyality = makeint(Npchar.loyality) + 1;
            Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
			NPChar.location = "none";
			LAi_SetOfficerType(NPChar);
		break;

		case "WantToGo_free":
			//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				Diag.CurrentNode = Diag.TempNode;
				DialogExit();
				break;
			}
			//navy <--
            Diag.TempNode = "WantToGo_free_Yet";
		Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			FireImmortalOfficer(npchar);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "WantToGo_free_Yet":
            Diag.TempNode = "WantToGo_free_Yet";
		dialog.text = LinkRandPhrase ("Вы не поверите, капитан - будто гора с плеч свалилась.", "Спасибо, капитан, что не стали удерживать. Хочется ещё чего-то в жизни попробовать.", "Эх, буду привыкать к свободе. Только сейчас понимаю, как опостылела флотская служба.");
		Link.l1 = RandPhraseSimple("Ну, всяческих тебе успехов...", "Гуляй. Закончилась твоя служба.");
		Link.l1.go = "exit";
	break;
	// boal 29.05.04 офицер хочет свалить <--

	// пассажир возмущен игроком и сваливает -->
	case "WantToRemove":
        chrDisableReloadToLocation = false;
		if (Npchar.alignment == "good")
		{
			dialog.text = RandPhraseSimple(LinkRandPhrase("Капитан, я не хочу ради наживы насиловать свою совесть и заниматься разбоем.","Капитан, я более не желаю принимать участие в ваших бесчинствах. Я не мясник, а офицер.","Капитан, ваши бандитские замашки делают невозможным моё дальнейшее пребывание в команде."), LinkRandPhrase("Капитан, нужно признать, что мой наём к вам на службу был досадной ошибкой. Я совершенно не готов ради денег жертвовать своим честным именем.","Капитан, на вашем судне собрались головорезы со всего Нового Света, приличному человеку в кают-компанию зайти противно. Я больше не желаю служить в такой команде.","Капитан, вы набрали в команду одних проходимцев - не с кем добрым словом обмолвиться. Душа совершенно не лежит к такой службе.")) + " Прощайте.";
			Link.l1 = "Что?!! У меня боевое судно, а не благородный пансион! Можешь убираться ко всем чертям!";
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "Я давно знал"+ GetSexPhrase("","а") +", что ты уйдёшь... такая служба не для тебя. Но упрекнуть мне тебя не в чем. Вот "+sti(NPChar.rank)*500+" золотых - пригодятся, пока найдёшь работу по душе.";
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = LinkRandPhrase("Ага. Вот, значит, как мы запели. А доля, которая тебе выплачивалась с каждого грабежа, руки не жжёт? Или ты прямиком отсюда в монастырь подашься - грехи замаливать? Тогда уж и за нас словечко замолви! Ах-ха-ха-ха...", "Хм, это серьёзное заявление. А куда же смотрела твоя девственная совесть, когда мы вместе грабили купцов? Чем её отмывать собираешься? Небось побежишь донос строчить, чтоб на виселице болтаться в доброй компании...", "Ух как браво!.. Видать, уже не помнишь, как я тебя наш"+ GetSexPhrase("ел","ла") +" - в вонючей таверне без гроша в кармане. Да тебе, как офицеру - грош цена, а туда же - на вольные хлеба.");
			Link.l3.go = "WantToGo_stop";
			}
			else
			{
            dialog.text = RandPhraseSimple(LinkRandPhrase("Капитан, ваши игры в благородство мне совсем не по душе. Я не стану ради вашего душевного спокойствия ломать свои привычки. Прощайте.","Капитан, я не могу более оставаться у вас на службе. Столько времени потрачено без толку - уже простым каперством можно было сколотить целое состояние. Я ухожу.","Капитан, меня с души воротит от таких сослуживцев. В кают-компанию хоть не заходи - как на подбор одни маменькины сынки, рому выпить не с кем. Я ухожу."), LinkRandPhrase("Капитан, я боевой офицер, а ваш корабль более похож на грузовую баржу. Такая служба не по мне, я ухожу. Прощайте.","Капитан, вы набрали в команду одних чистоплюев - не с кем рому выпить да словом обмолвиться. Душа совершенно не лежит к такой службе, поэтому прощайте.","Капитан, мне думалось, что я служу настоящему корсару. А мы чем занимаемся? Сплошная благотворительность! Я не хочу терять время и ухожу."));
			Link.l1 = RandPhraseSimple("Н-да. С твоим отношением к службе рано или поздно это должно было случиться. Что ж, удерживать не стану.", "Такое заявление не стало для меня неожиданностью. Твоё отношение к службе меня давно не устраивает.") + " Всего доброго.";
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "Я знал"+ GetSexPhrase("","а") +", что ты уйдёшь... такая служба не для тебя. Но упрекнуть мне тебя не в чем. Вот "+sti(NPChar.rank)*500+" золотых - пригодятся, пока будешь искать новое место.";
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = RandPhraseSimple("Хм. Это серьёзное заявление. Но ты ещё не отработал всех уплаченных тебе денег. Поэтому твой демарш я вправе расценивать, как бегство.", "Понятно...А давай-ка вспомним судовой устав. Пункт второй гласит: 'Если кто задумает бежать... да будет высажен на пустынном берегу с флягой пороха, флягой воды, одним ружьем и пулями.' Ну как тебе такой поворот?");
			Link.l3.go = "WantToGo_stop";
		}
		break;

		case "WantToGo_stop":
			if (Npchar.alignment == "good")
			{
				dialog.text = LinkRandPhrase("Не пытайтесь меня оскорбить! Я, как и все, служу за деньги, но вправе выбирать работу по душе.", "Я свободный человек! И вправе сменить работу, когда посчитаю нужным.", "Я не раб, чтобы служить лишь за еду, поэтому моя совесть чиста! Но я не собираюсь и далее участвовать в этом разбое!");
				Link.l1 = "Э-э нет, вот тут ты ошибаешься... Пока ты слюнявил кружку в таверне - да, можно было выбирать любую работу... Но после того, как взошёл на борт моего судна - всё... дорожка назад - только с ядром на шее, хе-хе... Да язычок ещё подрезать, чтоб на том свете случайно не сболтнул, чего не следует...";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "WantToGo_stop_stay";
				}
				else
				{
					Link.l1.go = "WantToGo_stop_fight";
				}
				Link.l2 = "Ну, ладно. Иди... Но не приведи тебе Господь встретить меня в открытом море. Клянусь, ты пожалеешь, что не остался на моей стороне.";
				Link.l2.go = "exit_fire_5";
			}
			else
			{
				dialog.text = LinkRandPhrase("Не пытайтесь меня запугать! Я, как и все, служу за деньги, и вправе выбирать работу по душе.", "Я свободный человек! И вправе сменить работу, когда посчитаю нужным.", "Я вам не раб! И я не намерен и далее прозябать на вашем корыте!");
				Link.l1 = "Э-э нет, вот тут ты ошибаешься... Пока ты слюнявил кружку в таверне - да, можно было выбирать любую работу... Но после того, как взошёл на борт моего судна - всё... дорожка назад - только с ядром на шее, хе-хе... Да язычок ещё подрезать, чтоб на том свете случайно не сболтнул, чего не следует...";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "WantToGo_stop_stay";
				}
				else
				{
					Link.l1.go = "WantToGo_stop_fight";
				}
				Link.l2 = "Ну, ладно. Иди... Но не приведи тебе Господь встретить меня в открытом море. Клянусь, ты пожалеешь, что не остался на моей стороне.";
				Link.l2.go = "exit_fire_5";
			}
		break;

		case "WantToGo_stop_stay":
			dialog.text = RandPhraseSimple("Коль дело принимает такой оборот, то я останусь - у меня просто нет другого выхода. Но знайте, что я это делаю не по собственной воле...", "Ну ладно, раз такое дело - остаюсь... Но знайте, что я поступаю против своей воли...");
			Link.l1 = RandPhraseSimple("Вот и ладно... Послужи, пока я сам"+ GetSexPhrase("","а") +" не решу, когда тебя вышвырнуть.", "Вот и хорошо - послужи пока... А я сам"+ GetSexPhrase("","а") +" решу, когда тебя списывать.");
			Link.l1.go = "WantToGo_Munity"; //этот линк ведет к бегству
		break;

		case "WantToGo_stop_fight":
			dialog.text = NPCharRepPhrase(NPChar, "Вам никогда не заставить меня изменить решение! Не на того напали!", "Вы наверное думаете, что сможете напугать боевого офицера?! Мне не впервой заглядывать смерти в глаза. И если на то пошло, лучше умереть в честном бою, чем во время подлого грабежа!");
			Link.l1 = NPCharRepPhrase(NPChar, "Ну что ж... каждый сам выбирает свою судьбу. Надеюсь, ты помолился перед визитом ко мне.", "Если бы я знал"+ GetSexPhrase("","а") +", на кого напал"+ GetSexPhrase("","а") +", когда подобрал"+ GetSexPhrase("","а") +" тебя в таверне под рифом и без гроша в кармане - клянусь, позволил"+ GetSexPhrase("","а") +" бы тебе дойти до плахи. И сейчас ещё не поздно это устроить...");
			Link.l1.go = "WantToGo_stop_fight_1";
			Link.l2 = NPCharRepPhrase(NPChar, "Ну, что ж, ступай, раз тебе так нужна свобода. Но учти - рекомендаций от меня ты не получишь.", "Ну, ладно. Иди... Но не приведи тебе Господь попасться мне в открытом море. Клянусь, ты пожалеешь, что не остался на моей стороне.");
			Link.l2.go = "exit_fire_5";
		break;

		case "WantToGo_stop_fight_1":
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterReputation(pchar, -1);
			dialog.text = NPCharRepPhrase(NPChar, "Только не нужно меня пугать! Кто из ваших молокососов решиться поднять против меня голос?! Да будь я капитаном - они бы озолотились уже! А вы развели... благодетельность, а теперь дрожите, чтоб команда на мою сторону не переметнулась?!", "Бросьте свои замашки, вам меня не испугать! Прощайте.");
			Link.l1 = NPCharRepPhrase(NPChar, "Нет, приятель, до эшафота тебе не дожить. Такая роскошь не для тебя...", "Не так быстро, приятель, я тебе ещё не дал"+ GetSexPhrase("","а") +" расчёта...");
			Link.l1.go = "Get_out_fight";
		break;
		///////////////////////////////////////////////////////////////////////////////////
		case "WantToGo_Munity":	//zagolski. отыгрыш бегство офицера
			Diag.TempNode = "Hired";
			if (sti(Pchar.questTemp.MunityOfficerIDX) != GetCharacterIndex(Npchar.id))
			{
				Pchar.questTemp.MunityOfficerIDX = GetCharacterIndex(Npchar.id);
				Pchar.questTemp.MunityOfficerIDX.begin = "1";
				SetFunctionTimerCondition("mOfficer_fc", 0, 0, 1, false);
			}
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.location = "none";
			LAi_SetOfficerType(NPChar);
			DialogExit();
		break;
		////////////////////////////////////////////////////////////////////
		// пассажир возмущен игроком и сваливает <--

		case "Node_2":
			dialog.text = NPCharRepPhrase(Npchar, RandSwear() + "Да я лучший "+ XI_ConvertString(Npchar.quest.officertype) + " в этих водах. " + Npchar.quest.officertype_2 + "Готов оказать вам услугу, пойдя на службу.",
                                    "Ну, говорят, что я неплохой " + XI_ConvertString(Npchar.quest.officertype) + ". " + Npchar.quest.officertype_2 + "Возьмите меня на свое судно, капитан - убедитесь в этом сами.");
			Link.l1 = "Сколько ты хочешь?";
			Link.l1.go = "price";
			Link.l2 = "А что ты из себя представляешь как специалист?";
			Link.l2.go = "ShowParam_exit";
			Link.l3 = "Увы, у меня уже есть " + XI_ConvertString(Npchar.quest.officertype) + ".";
			Link.l3.go = "Exit";
		break;

		case "OnceAgain":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple("Хех, капитан, за тобой тут половина гарнизона гоняется. Сейчас явно не время идти к тебе в команду!", "Предлагаешь с боем прорываться на корабль? Нет уж, в другой раз, кэп...");
				link.l1 = RandPhraseSimple("Ну как знаешь...", "Да я и не "+ GetSexPhrase("собирался","собиралась") +" тебя нанимать.");
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = "Неужели передумали, капитан? Решили, что новый " + XI_ConvertString(Npchar.quest.officertype) + " вам не помешает?";
			// boal -->
			if (FindFreeRandomOfficer() > 0)
			{
                Link.l1 = "Пожалуй, так. Сколько ты хочешь?";
                Link.l1.go = "price";
			}
			Link.l2 = "Каков ты будешь в деле?";
			Link.l2.go = "ShowParam_exit";
			// boal <--
			Link.l3 = "У меня полный комплект. Счастливо оставаться.";
			Link.l3.go = "exit";
		break;

		case "price":
			dialog.text = "Думаю, мы с вами сойдемся на " + Npchar.quest.OfficerPrice + " пиастров.";
			Link.l1 = "Не слишком ли ты много хочешь?";
			Link.l1.go = "trade";
			Link.l2 = "Я "+ GetSexPhrase("согласен","согласна") +". Считай себя зачисленным в команду.";
			Link.l2.go = "hire";
			Link.l3 = "Ты не стоишь этих денег. Прощай.";
			Link.l3.go = "exit";
		break;

		case "trade":
			if (GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE) >= Rand(12) && (sti(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100) >= sti(Npchar.quest.OfficerLowPrice))// bug fix
			{
				Npchar.quest.OfficerPrice = makeint(makeint(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100); // пусть будет коммерция перса голой
				dialog.text = "Хорошо... Пожалуй, я готов согласиться даже на " + Npchar.quest.OfficerPrice + " пиастров. Ну как?";
				Link.l1 = "Вот это уже лучше. Ты принят.";
				Link.l1.go = "hire";
				Link.l2 = "Я по-прежнему считаю, что это чересчур. Прощай.";
				Link.l2.go = "exit";
			}
			else
			{
				dialog.text = "Увы, капитан, я стою именно столько, сколько запросил. Если это слишком дорого для вас - поищите кого-нибудь другого.";
				Link.l1 = "Ну ладно, я "+ GetSexPhrase("согласен","согласна") +". Я беру тебя.";
				Link.l1.go = "hire";
				Link.l2 = "Так я и поступлю. Всего хорошего.";
				Link.l2.go = "exit";
			}
		break;

		case "hire":
			if(makeint(Pchar.money) >= makeint(Npchar.quest.OfficerPrice))
			{
				pchar.questTemp.officercount = sti(pchar.questTemp.officercount) + 1;
				if(sti(pchar.questTemp.officercount) >= 3) UnlockAchievement("officers", 1);
				if(sti(pchar.questTemp.officercount) >= 6) UnlockAchievement("officers", 2);
				if(sti(pchar.questTemp.officercount) >= 10) UnlockAchievement("officers", 3);

				AddMoneyToCharacter(Pchar, -(makeint(Npchar.quest.OfficerPrice)));
				Diag.TempNode = "OnboardSoon";
				dialog.text = "Благодарю вас, капитан. Вы не пожалеете, что отдали мне это золото.";
				Link.l1 = "Хочется в это верить.";
				Link.l1.go = "Exit_hire";
			}
			else
			{
				dialog.text = "Эй, похоже, у вас проблемы с наличностью! Извините, капитан, но я не работаю в кредит.";
				Link.l1 = "Ах ты, черт!";
				Link.l1.go = "Exit";
			}
		break;

		case "OnboardSoon":
			Diag.TempNode = "OnboardSoon";
			dialog.text = "Сейчас я допью, капитан, и отправлюсь на борт. Не извольте беспокоиться - я успею до отплытия.";
			Link.l1 = "Хорошо. Опоздаешь - заставлю драить палубу!";
			Link.l1.go = "Exit";
		break;

        case "QMASTER_1":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
			{
				dialog.text = "Капитан, но у нас ведь нету корабля!";
				Link.l1 = "Спасибо, напомнил...";
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
			}
            dialog.text = "Максимальная активность крыс в рейсе " +
                     FloatToString(50.0 / (2.0+GetSummonSkillFromNameToOld(PChar, SKILL_REPAIR) + GetSummonSkillFromNameToOld(PChar,SKILL_SNEAK)), 1) +
                     "% от количества груза. На "+GetCrewQuantity(PChar) + " матросов нужно " + makeint((GetCrewQuantity(PChar)+6) / 10) + " провианта в день. Это без учёта перевозимых рабов.";
					 if (NPChar.id == "Andreas_Fickler")
						{
							dialog.text = "Максимальная активность к-к-крыс в рейсе " +
									FloatToString(50.0 / (2.0+GetSummonSkillFromNameToOld(PChar, SKILL_REPAIR) + GetSummonSkillFromNameToOld(PChar,SKILL_SNEAK)), 1) +
									"% от к-к-количест-тва груза. На "+GetCrewQuantity(PChar) + " мат-тросов н-нужно " + makeint((GetCrewQuantity(PChar)+6) / 10) + " п-п-провианта в день. Это без учёта п-перевозимых рабов.";
						}
            Link.l1 = "Спасибо.";
            Link.l1.go = "Exit";
            Diag.TempNode = "Hired";
        break;

        // boal 05.09.03 offecer need to go to abordage -->
        case "stay_follow":
            dialog.text = "Какие будут приказания?";
			if (NPChar.id == "Andreas_Fickler")
				{
					dialog.text = "К-к-какие будут п-приказания?";
				}
            Link.l1 = "Стой здесь!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Следуй за мной и не отставай!";
            Link.l2.go = "Boal_Follow";
            // boal 05.09.03 offecer need to go to abordage <--

			if (findsubstr(npchar.model, "PGG" , 0) != -1 && !CheckAttribute(npchar, "CanTakeMushket"))
			{
				Link.l3 = "Можно ли тебе доверить мушкет?";
				Link.l3.go = "CheckMushket";
			}
			if (findsubstr(npchar.model.animation, "mushketer" , 0) != -1)
			{
				Link.l3 = "Я хочу, чтобы ты держал"+NPCharSexPhrase(npchar,"ся","ась")+" на определенном расстоянии от цели.";
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
		break;

		case "AboardRestriction":
			npchar.AboardRestriction = true;
			dialog.text = "Так точно капитан. Не буду участвовать в абордажах, пока вы снова не разрешите.";
            Link.l1 = "Ну и хорошо.";
            Link.l1.go = "exit";
		break;

		case "AboardAllowed":
			DeleteAttribute(npchar,"AboardRestriction");
			dialog.text = "Так точно капитан. Буду участвовать в абордажах с текущего момента.";
            Link.l1 = "Ну и хорошо.";
            Link.l1.go = "exit";
		break;

		case "CheckMushket":
			if (findsubstr(npchar.model.animation, "man" , 0) != -1 || findsubstr(npchar.model.animation, "YokoDias" , 0) != -1 || findsubstr(npchar.model.animation, "Milenace" , 0) != -1)
			{
				if (findsubstr(npchar.model.animation, "man2_ab" , 0) == -1)	Npchar.CanTakeMushket = true;
			}

			if (CheckAttribute(npchar, "CanTakeMushket"))
			{
				dialog.text = "Конечно, капитан!";
				Link.l1 = "Замечательно, тогда по возможности что-то тебе подберём.";
				Link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Лучше не надо, капитан. Вас еще ненароком подстрелю.";
				Link.l1 = "Жаль, очень жаль...";
				Link.l1.go = "exit";
			}
		break;

		case "TargetDistance":
			dialog.text = "На каком именно, капитан? Укажите в метрах, но не более 20-ти.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";
		break;
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Капитан, что за дурной тон!";
				link.l1 = "Извини, ошибочка вышла...";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Я буду стоять на месте, никуда не двигаясь. Вас это устраивает, капитан?";
				link.l1 = "Да, именно это от тебя и требуется.";
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
			dialog.text = "Задачу понял"+NPCharSexPhrase(npchar, "","а")+", принимаю к сведению.";
			link.l1 = "Хорошо.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;

		case "AsYouWish":
			// проверка на море -->
			if (bSeaActive)
			{
				attr = Sea_FindNearColony();
				if (attr == "none")
				{
					dialog.text = "Капитан, хоть мне и непонятна причина такого заявления - давайте вернёмся к этому вопросу на берегу. Или вы решили просто выбросить меня за борт?";
					Link.l1 = "Хм... нет, я не это имел"+ GetSexPhrase("","а") +" в виду. Оставайся, пока не придём в порт.";
					Link.l1.go = "Exit";
					break;
				}
			}
			// проверка на море <--
			if (makeint(PChar.reputation) >= 41 && makeint(NPChar.reputation) < 41) //герой против злодея
			{
				dialog.text = RandPhraseSimple(LinkRandPhrase("Вот это новость!","С какой это радости?!","С чего это вдруг?!"), RandPhraseSimple("Капитан, вы в своём уме? Сообщать такие новости ни с того, ни с сего!","Ого! И чем это я вам не угодил?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Я решил"+ GetSexPhrase("","а") +" навести порядок в эскадре. И, поскольку мне не нравятся твои взаимоотношения с коллегами,","Твои достоинства оказались не так хороши, как расписывалось при найме, поэтому","Головорезов и проходимцев в моей команде не будет! Поэтому"), LinkRandPhrase("Мне стало известно, что ты тайком таскаешь ром и спаиваешь команду, тем самым ослабляя её боевой дух. Поэтому","Мне чертовски надоели твои разбойничьи замашки, я не намерен"+ GetSexPhrase("","а") +" терпеть их бесконечно. Так что,","Ты постоянно проводишь время в кают-компании за игрой в карты или кости, отвлекая других офицеров от несения службы. Это не может продолжаться бесконечно, поэтому")) + " собирайся и покинь судно.";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "Get_out_A1_peace";
				}
				else
				{
					Link.l1.go = "Get_out_A1_strife";
				}
				break;
			}
			if (makeint(PChar.reputation) >= 41 && makeint(NPChar.reputation) >= 41) // герой против героя
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("Могу я узнать причины такого решения?","Наверняка такое решение имеет веские причины?"), RandPhraseSimple("Прошу объясниться, капитан.","Весьма неожиданно. Но хотелось бы знать основания."));
				if (NPChar.id == "Andreas_Fickler")
				{
					dialog.text = RandPhraseSimple(RandPhraseSimple("М-могу я узнать п-п-причины такого решения?","Н-н-наверняка такое решение имеет веские п-причины?"), RandPhraseSimple("П-п-прошу объясниться, к-капитан.","Весьма н-неожиданно. Н-но хотелось б-бы знать основания."));
				}
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Меня категорически не устраивает твоё отношение к своим обязанностям.","К сожалению, из тебя не вышло толкового офицера, и наверное уже не выйдет...","Ты хороший офицер, и исправно нёс службу, но здесь наши пути расходятся. И не спрашивай меня почему."), LinkRandPhrase("Я предупреждал"+ GetSexPhrase("","а") +", что страсть к рому тебя погубит. Как я могу довериться в бою человеку, который саблей в ножны попасть не может?","Моряка из тебя, скажем прямо, не вышло... Думаю, на берегу ты добьешься большего.","Меня давно не устраивает твоя квалификация, но сейчас я наконец-то наш"+ GetSexPhrase("ел","ла") +" достойную замену."));
				Link.l1.go = "Get_out_A2";
				break;
			}
			if (makeint(PChar.reputation) < 41 && makeint(NPChar.reputation) >= 41) // злодей против героя
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("Хм. Могу я узнать причины?","Это серьёзное заявление. Могу я узнать, что конкретно вас не устраивает?"), RandPhraseSimple("Прошу объясниться, капитан.","Надеюсь, у такого заявления имеются веские основания?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Меня совершенно не устраивает твоя квалификация, поэтому","К сожалению, из тебя не вышло толкового офицера. Так что,","Мне чертовски надоели твои благородные порывы. Я не намерен"+ GetSexPhrase("","а") +" терпеть их бесконечно, так что,"), LinkRandPhrase("До меня дошли слухи, что именно ты подбиваешь команду к неповиновению. Беспорядков на моём судне не будет! И не нужно благодарить, что я раньше не вышвырнул"+ GetSexPhrase("","а") +" тебя за борт... Так что,","Твои благородные принципы делают тебе честь, но они идут вразрез с разбойной жизнью вольного капера. Так что,","Меня категорически не устраивает твоё отношение к своим обязанностям. Поэтому")) + " собирайся и покинь судно.";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "Get_out_A3_peace";
				}
				else
				{
					Link.l1.go = "Get_out_A3_strife";
				}
				break;

			}
			if (makeint(PChar.reputation) < 41 && makeint(NPChar.reputation) < 41) // злодей против злодея
			{
				dialog.text = RandPhraseSimple(LinkRandPhrase("Капитан, я никак не ожидал такого поворота! Может объясните, что произошло?","Капитан, что за муха вас укусила?!","Как прикажете это понимать, капитан?!"), RandPhraseSimple("Как же так, капитан?! Ещё сутра всё было нормально, а тут - на тебе...","Ого! Думаю, вы найдёте пару слов для объяснения?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Ты редкостный бездарь и неумеха - тебе бы юнгой в каботажное плавание. Я и так слишком долго терпел"+ GetSexPhrase("","а") +". Так что,","Ты давно меня не устраиваешь, но сейчас я наконец-то наш"+ GetSexPhrase("ел","ла") +" достойную замену. Так что,","Мне стало известно, что ты тайком таскаешь ром и спаиваешь команду, тем самым ослабляя её боевой дух. Поэтому"), LinkRandPhrase("При найме ты распинался, что лучшего офицера не найти на всём флоте, а на поверку оказался обыкновенным лоботрясом, так что","Я предупреждал"+ GetSexPhrase("","а") +", что твоё пьянство плохо кончится. Почему я долж"+ GetSexPhrase("ен","на") +" всё за тебя делать сам"+ GetSexPhrase("","а") +"? Так что,","Вместо несения службы, ты постоянно торчишь в кают-компании за игрой в карты или кости. Надеюсь, ты не думал, что так может продолжаться бесконечно? Так что,")) + " собирайся и проваливай.";
				Link.l1.go = "Get_out_A4";
				break;
			}
		break;

		case "Get_out_A1_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Вот значит как! Ну ладно, воля ваша. Но учтите: к вам я больше не вернусь. Ещё просить будете...","Признаться, ваши игры в благородство мне тоже как-то не по душе. Так что - прощайте...", "Ну и чёрт с вами! Оставайтесь со своими лизоблюдами. Тоже мне - 'герой'!"), LinkRandPhrase("Да мне у вас никогда и не нравилось, не судно, а грузовая баржа. Развели благородный пансион...","Да меня самого с души воротит от таких сослуживцев. В кают-компанию хоть не заходи, как на подбор - одни маменькины сынки...","Хорошо, капитан, будь по-вашему. Но, видит Бог, у меня за кормой чисто..."));
			Link.l1 = "Стой. Сейчас я не могу оставить судно без офицера. Но позднее мы ещё вернемся к этому разговору.";
			Link.l1.go = "exit_bad";
			Link.l2 = "Вот и ступай с Богом.";
			Link.l2.go = "Exit_Fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Не кипятись. Я приготовил"+ GetSexPhrase("","а") +" тебе выходное пособие "+sti(NPChar.rank)*500+" золотых. Надеюсь, это снимет все вопросы.";
				Link.l3.go = "Get_out_А1_ForMoney";
			}
		break;

		case "Get_out_A1_strife":
			dialog.text = LinkRandPhrase("Позвольте! Что значит 'покинь судно'?! Не для того я свою голову под картечь подставлял, чтоб вы могли меня вышвырнуть, когда вздумается!", "Ха! 'покинь судно'! Вы думаете, я позволю вышвырнуть себя, как котёнка?!", "Полегче, капитан, в серьёзной компании так дела не решаются. Я не позволю обращаться с собой, как с салагой.");
			Link.l1 = "Хорошо, оставайся. Но лишь пока я не найду достойную замену." ;
			Link.l1.go = "exit_bad";
			Link.l2 = "Я повторяю - твоя служба закончена. Можешь собирать вещи.";
			Link.l2.go = "Get_out_A1_strife_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Не кипятись. Я приготовил"+ GetSexPhrase("","а") +" тебе выходное пособие "+sti(NPChar.rank)*500+" золотых. Надеюсь, это снимет все вопросы.";
				Link.l3.go = "Get_out_А1_ForMoney";
			}
		break;

		case "Get_out_A1_strife_1":
			dialog.text = RandPhraseSimple("Да я и не горю желанием у вас задерживаться. Только без компенсации покидать судно не собираюсь!", "Да я теперь и сам не останусь на вашем корыте. Только извольте сначала выплатить компенсацию!") + " "+sti(NPChar.rank)*1000+" золотых, и мы забудем друг о друге.";
			Link.l1 = "Я погорячил"+ GetSexPhrase("ся","ась") +"... Прими мои извинения, и возвращайся на пост.";
			Link.l1.go = "exit_bad1";
			Link.l2 = "О каких деньгах может идти речь, если ты регулярно получал свою долю? Всё это изрядно смахивает на вымогательство!";
			Link.l2.go = "Get_out_А1_strife_battle";
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l3 = "Ладно. Сдай экипировку и получишь то, о чём просишь.";
				Link.l3.go = "Get_out_А1_chang";
			}
		break;

		case "Get_out_А1_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterReputation(pchar, 1);
			dialog.text = "Ну, это совсем другое дело. Прощайте!";
			Link.l1 = "Надеюсь, наши дороги больше не пересекутся.";
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_А1_strife_battle":
			dialog.text = LinkRandPhrase("Считайте это компенсацией моральных издержек. Я никому не позволю так с собой обращаться! А кто посмеет, тот очень пожалеет об этом!", "Это не вымогательство, а компенсация бездарно потраченного времени! И я её получу, чего бы мне это ни стоило!", "Я потратил слишком много времени на службу у так"+ GetSexPhrase("ого чистоплюя","ую чистоплюйку") +" как вы. За это время можно было озолотиться грабежом торговцев. Теперь хочу компенсировать упущенную выгоду.");
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l1 = "Ладно. Вот твои деньги... А теперь убирайся отсюда!";
				Link.l1.go = "Get_out_А1_ForMoney_angry";
			}
			Link.l2 = "Ты забываешься! Я не позволю всяким недоумкам повышать на себя голос!";
			Link.l2.go = "Get_out_А1_strife_death";
		break;

		case "Get_out_А1_strife_death":
			ChangeCharacterReputation(pchar, 1);
			OfficersReaction("good");
			dialog.text = "Давай-давай, капитан! Покажи, каков"+ GetSexPhrase("","а") +" ты против серьёзного соперника!";
			Link.l1 = "Видит Бог, я этого не хотел"+ GetSexPhrase("","а") +"!";
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_А1_ForMoney_angry":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterReputation(pchar, -1);
			OfficersReaction("bad");
			dialog.text = "Ну, это совсем другое дело. Прощайте!";
			Link.l1 = "Надеюсь, наши дороги больше не пересекутся.";
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_A2":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Ну что ж, значит не судьба. Прощайте, капитан, не поминайте лихом...","Очень жаль, капитан. Но, видит Бог, я старался. Прощайте.","Ну, капитан, вам не угодишь!.. Счастливо оставаться."), LinkRandPhrase("Жаль, капитан. Мне очень нравилось служить у вас.","Вот ведь как бывает... Но я зла не держу, прощайте.","Вы несправедливы ко мне, капитан. Но я уважаю ваше решение. Прощайте."));
			if (NPChar.id == "Andreas_Fickler")
			{
				dialog.text = RandPhraseSimple(LinkRandPhrase("Ну что ж, значит не судьба. П-п-прощайте, к-капитан, не п-поминайте лихом...","Очень жаль, к-капитан. Но, видит Бог, я старался. П-п-прощайте.","Ну, к-капитан, вам н-не угодишь!.. Счастливо оставаться."), LinkRandPhrase("Жаль, к-капитан. М-м-мне очень н-нравилось служить у вас.","Вот ведь к-как бывает... Н-н-но я зла не держу, п-прощайте.","Вы несп-п-праведливы к-ко мне, капитан. Но я уважаю ваше решение. П-прощайте."));
			}
			Link.l1 = "Стой, я передумал"+ GetSexPhrase("","а") +". Давай вернём к этому разговору позже.";
			Link.l1.go = "exit_good";
			Link.l2 = "Не огорчайся. Удачи тебе...";
			Link.l2.go = "exit_fire_2";
			Link.l3 = "Постой... Я тебя неплохо экипировал"+ GetSexPhrase("","а") +". Нужно бы вернуть вещички - мне вон какую ораву снаряжать нужно...";
			Link.l3.go = "Return_items_A2";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l4 = "Постой... Не хочу отпускать тебя с пустыми руками. Вот держи "+sti(NPChar.rank)*500+" золотых, пригодятся, пока будешь искать новую работу.";
			}
			Link.l4.go = "Im_kind_A2";
		break;

		case "Return_items_A2":
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = "Да о чём речь, конечно забирайте...";
			Link.l1 = "Я знал"+ GetSexPhrase("","а") +", что ты меня правильно поймёшь...";
			Link.l1.go = "Get_out_А2_chang";
		break;

		case "Im_kind_A2":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterReputation(pchar, 1);
			dialog.text = "Спасибо вам, капитан! Какая неожиданная щедрость. У меня тут осталось кое-что из ваших вещей, может желаете их вернуть?";
			Link.l1 = "Да пожалуй... Сейчас найти хороший клинок ой как непросто...";
			Link.l1.go = "Get_out_А2_chang";
			Link.l2 = "Не нужно. Оставь себе в память о службе под моим началом...";
			Link.l2.go = "exit_fire_2";
		break;

		case "Get_out_A3_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Ну что ж, воля ваша. Но учтите: к вам я больше не вернусь, даже если придётся помирать с голоду.","Признаться, ваши бандитские замашки мне тоже не по душе. Так что, это рано или поздно должно было случиться... И не нужно выдумывать никаких причин.","Ну и оставайтесь со своими головорезами. На вашем судне приличному человеку в кают-компанию зайти стыдно. Развели бордель, прости меня Господи!"), LinkRandPhrase("Признаться, у меня тоже душа не лежит к такой службе. Набрали в команду одних проходимцев - не с кем добрым словом обмолвиться.","Да, если вы будете так относиться к личному составу - от вас все сами разбегутся. Никаких причин выдумывать не придётся.","Меня утешает то, что наша неприязнь взаимна. Счастливо оставаться."));
			Link.l1 = "Стой. Сейчас не самый удачный момент тебя списывать. Но все претензии остаются в силе.";
			Link.l1.go = "exit_bad";
			Link.l2 = "Иди-иди. Обойдусь без твоих нравоучений.";
			Link.l2.go = "exit_fire_3";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Подожди. Дам тебе на дорогу "+sti(NPChar.rank)*500+" золотых. А то помрёшь под забором, а мне потом перед Богом отвечать.";
				Link.l3.go = "Get_out_А3_ForMoney";
			}
		break;

		case "Get_out_А3_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterReputation(pchar, 1);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase("И на том спасибо. Прощайте...", "Благодарю за понимание. Счастливо оставаться.", "Вот теперь мы в расчёте. Всего хорошего...");
			Link.l1 = "Я знал"+ GetSexPhrase("","а") +", что ты меня правильно поймёшь...";
			Link.l1.go = "exit_fire_3";
		break;

		case "Get_out_A3_strife":
			dialog.text = LinkRandPhrase("Но, капитан, при таком раскладе я остаюсь совсем на мели. Вы же не хотите отправить меня с корабля прямо на паперть?", "Вы несправедливы ко мне, капитан. Но я готов забыть обиду, если получу достойную компенсацию.", "И это ваша благодарность за все мои боевые ранения? Думаю, без денежной компенсации тут не обойтись.");
			Link.l1 = "Ладно, я передумал"+ GetSexPhrase("","а") +". Пока оставайся, но мы ещё вернёмся к этому разговору.";
			Link.l1.go = "exit_bad";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "Ну, об этом можешь не переживать. Держи "+sti(NPChar.rank)*500+" золотых. Думаю, на первое время хватит.";
				Link.l2.go = "Get_out_А3_ForMoney";
				Link.l3 = "Я дам тебе денег. Но, благодаря мне, ты неплохо экипирован - вещички нужно бы вернуть.";
				Link.l3.go = "Return_items_A3";
			}
			Link.l4 = "Ого! А как же регулярно получаемая тобой доля?! Я так и знал"+ GetSexPhrase("","а") +", что всё закончится нытьём и выпрашиванием подачки.";
			Link.l4.go = "Get_out_A3_strife_1";
		break;

		case "Return_items_A3":
			dialog.text = "Я знал, что вы это скажете, но экипировку сможете забрать только, когда я получу "+sti(NPChar.rank)*1000+" золотых. Или вам придётся снимать её с трупа.";
			Link.l1 = "Хорошо, держи свои деньги.";
			Link.l1.go = "Get_out_А3_chang";
			Link.l2 = "Да в своём ли ты уме?! Требовать такую сумму за то, что я дал тебе бесплатно! Похоже, такое низкое качество, как жадность, всё-таки одержало верх над твоей напускной благодетелью.";
			Link.l2.go = "Get_out_A3_strife_1";
		break;

		case "Get_out_A3_strife_1":
			dialog.text = "Вы не смеете меня оскорблять! Я, может и не самый лучший на флоте, но всё же боевой офицер. И заставлю уважать себя, даже так"+ GetSexPhrase("ого","ую") +" невежу как вы!";
			Link.l1 = "Если тебе ещё не ясно, то повторю - можешь не клянчить, всё равно ничего не получишь.";
			Link.l1.go = "Get_out_А3_strife_death";
		break;

		case "Get_out_А3_strife_death":
			ChangeCharacterReputation(pchar, -1);
			OfficersReaction("bad");
			dialog.text = "Ну, уж удовлетворение-то я получу в любом случае!!";
			Link.l1 = "Да это вызов! Ну, что ж, как пожелаешь...";
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_A4":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Вот так всегда! Всю душу на службе отдаёшь, а тебе - бац, и без выходного пособия!","Да что ж это за напасть такая?! Не успеешь наняться, как тебя тут же коленкой под зад. Уж и не знаю, кому свечку ставить...","Вот те на! Уже третье увольнение за год - и всё по понедельникам. Этим капитанам хоть на глаза с похмелья не показывайся!"), LinkRandPhrase("Ну ладно, пусть так. Только не приведи Господь нам больше встретиться.","Ну что ж, воля ваша. Но учтите: лучшего офицера вам всё равно не найти.","Хорошо, капитан, будь по-вашему. Но, видит Бог - у меня за кормой чисто..."));
			Link.l1 = "Стой. Сейчас не самый удачный момент тебя списывать. Но все претензии остаются в силе.";
			Link.l1.go = "exit_good";
			Link.l2 = RandPhraseSimple("Топай-топай. И благодари Бога, что я сегодня в хорошем настроении.", "Давай-давай. Всё равно из тебя офицер, как из дерьма пуля.");
			Link.l2.go = "exit_fire_4";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Подожди. Дам тебе на дорогу "+sti(NPChar.rank)*500+" золотых. А то помрёшь под забором, а мне потом перед Богом отвечать.";
				Link.l3.go = "Get_out_А4_ForMoney";
			}
			Link.l4 = "Постой... Я тебя неплохо экипировал"+ GetSexPhrase("","а") +" - вещички нужно бы вернуть.";
			Link.l4.go = "Return_items_A4";
		break;

		case "Get_out_А4_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterReputation(pchar, 1);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase("Вот спасибо, капитан! Вот так уважили...", "Благодарю за понимание. Счастливо оставаться.", "Вот теперь мы в расчёте. Всего хорошего...");
			Link.l1 = "Счастливо. Только не оставь их все в ближайшей таверне.";
			Link.l1.go = "exit_fire_4";
		break;

		case "Return_items_A4":
			if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
			{
				dialog.text = LinkRandPhrase("Вот теперь ещё и экипировку забираете! Да пропади оно всё пропадом! Ей-богу в рыбаки подамся...", "Вижу, вы меня дочиста раздеть решили. Что ж, забирайте. Одна теперь дорога - на паперть...", "Благодарю покорно! Теперь ещё и обчистить решили. Эх, судьбина!.. Забирайте, будь оно всё неладно...");
				Link.l1 = "Давай-давай. Всё равно из тебя офицер, как из дерьма пуля.";
				Link.l1.go = "Get_out_А4_chang_1";
			}
			else
			{
				dialog.text = RandPhraseSimple("Будь по-вашему, капитан, только сначала выдайте мне "+sti(NPChar.rank)*1000+" золотых. Будем считать это компенсацией моральных издержек.", "Хорошо. Только за это я хочу получить "+sti(NPChar.rank)*1000+" золотых в качестве компенсации за нелёгкую службу.");
				if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
				{
					Link.l1 = "Вот пройдоха! Ладно, держи свои деньги.";
					Link.l1.go = "Get_out_А4_chang";
				}
				Link.l2 = "Да ты никак рехнулся?! Смеешь просить столько денег за то, что я сам"+ GetSexPhrase("","а") +" же тебе дал"+ GetSexPhrase("","а") +"!";
				Link.l2.go = "Get_out_A4_strife";
				Link.l3 = "Ах-ха! Да я пошутил"+ GetSexPhrase("","а") +"! Разве я могу вышвырнуть старого друга, как дырявый картуз!";
				Link.l3.go = "exit_bad1";
			}
		break;

		case "Get_out_A4_strife":
			ChangeCharacterReputation(pchar, -1);
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = "Ну, тогда ничего и не получите! Я с места не двинусь, пока не услышу, как звенит моё золото!";
			Link.l1 = RandPhraseSimple("Сейчас ты услышишь, как звенит мой клинок!", "Значит, тебя унесут вперёд ногами!");
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_fight":
			if(CheckAttribute(Npchar,"HalfImmortal")) DeleteAttribute(Npchar,"HalfImmortal");
			CheckForReleaseOfficer(GetCharacterIndex(Npchar.id));
			RemovePassenger(Pchar, Npchar);
			LAi_CharacterDisableDialog(NPChar);
			LAi_SetWarriorType(Npchar);
			LAi_group_MoveCharacter(Npchar, "TmpEnemy");
			LAi_group_SetHearRadius("TmpEnemy", 100.0);
			LAi_group_FightGroupsEx("TmpEnemy", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
			if (PChar.location == Get_My_Cabin() || findsubstr(PChar.location, "_tavern" , 0) != -1 || findsubstr(PChar.location, "_store" , 0) != -1)
            {
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				LAi_group_SetCheck("TmpEnemy", "CannotFightCurLocation");
				LAi_group_SetCheck("TmpEnemy", "MainHeroFightModeOff");
            }
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

	    case "Get_out_А1_chang": // интерфейс обмена
			Diag.TempNode = "Fired_1";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterReputation(pchar, -1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			FireImmortalOfficer(npchar);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А2_chang": // интерфейс обмена
			Diag.TempNode = "Fired_2";
			LAi_CharacterDisableDialog(NPChar);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			FireImmortalOfficer(npchar);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А3_chang": // интерфейс обмена
			Diag.TempNode = "Fired_3";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterReputation(pchar, 1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			FireImmortalOfficer(npchar);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А4_chang_1": // интерфейс обмена
			Diag.TempNode = "Fired_4";
			LAi_CharacterDisableDialog(NPChar);
			ChangeCharacterReputation(pchar, -1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А4_chang": // интерфейс обмена
			Diag.TempNode = "Fired_4";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterReputation(pchar, 1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			FireImmortalOfficer(npchar);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

	    case "exit_bad":
			Npchar.loyality = makeint(Npchar.loyality) - 3;
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_bad1":
			Npchar.loyality = makeint(Npchar.loyality) - 2;
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterReputation(pchar, -1);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_good":
			Npchar.loyality = makeint(Npchar.loyality) - 1;
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_fire_1":	//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--
			Diag.TempNode = "Fired_1";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			FireImmortalOfficer(npchar);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_fire_2":	//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--
			Diag.TempNode = "Fired_2";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			FireImmortalOfficer(npchar);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_fire_3":	//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--
			Diag.TempNode = "Fired_3";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			FireImmortalOfficer(npchar);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_fire_4":	//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--
			Diag.TempNode = "Fired_4";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			FireImmortalOfficer(npchar);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_fire_5":	//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--
			Diag.TempNode = "Fired_1";
			OfficersReaction("good");
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			FireImmortalOfficer(npchar)
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "Fired_1":
			Diag.TempNode = "Fired_1";
			dialog.text = "Ну чего ещё? Мы, кажется, уже всё решили! Ноги моей больше на вашем судне не будет.";
			Link.l1 = RandPhraseSimple("Ступай-ступай. Невелика потеря.", "Иди-иди. Удерживать не стану.");
			Link.l1.go = "Exit";
		break;

		case "Fired_2":
			Diag.TempNode = "Fired_2";
			dialog.text = "Что-то ещё, капитан? Мне казалось, что мы уже всё решили...";
			Link.l1 = "Нет, ничего. Просто попрощаться хотел"+ GetSexPhrase("","а") +"...";
			Link.l1.go = "Exit";
		break;

		case "Fired_3":
			Diag.TempNode = "Fired_3";
			dialog.text = "Капитан, все вопросы решены, претензии высказаны. Не хотите же вы после всего этого сказать, что передумали.";
			Link.l1 = "Иди-иди. Невелика потеря.";
			Link.l1.go = "Exit";
		break;

		case "Fired_4":
			Diag.TempNode = "Fired_4";
			dialog.text = "Капитан, ну какие ещё могут быть вопросы? Я, сказать по совести, очень на вас обижен, и никакого желания возвращаться не имею...";
			Link.l1 = "Иди-иди. Нужен ты мне больно, только палубу пачкал.";
			Link.l1.go = "Exit";
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
		      Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
	      break;
	      case "Boal_Follow":
		      SetCharacterTask_FollowCharacter(Npchar, PChar); // it works here!!!
		      Diag.TempNode = "Hired";
		      dialog.text = "Есть изменить дислокацию!";
		      Link.l1 = "Вольно.";
		      Link.l1.go = "Exit";
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
			dialog.Text = "Внимательно слушаю.";
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
			dialog.Text = "Что же вы желаете?";
			Link.l1 = "Я хочу чтобы ты не брал"+ GetSexPhrase("","а") +" корабли на абордаж. Побереги себя и свою команду.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Мне нужно чтобы ты брал вражеские корабли на абордаж.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;

		case "Companion_TaskChange":
			dialog.Text = "Что же вы желаете?";
			Link.l1 = "Я хочу чтобы ты не менял"+ GetSexPhrase("","а") +" свой корабль после абордажа. Он слишком ценен.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Когда будешь брать врагов на абордаж, посмотри, вдруг кораблик приличный будет, тогда бери себе.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "Так точно.";
			Link.l1 = "Вольно.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;

		case "Companion_TaskBoardingYes":
			dialog.Text = "Будет исполнено.";
			Link.l1 = "Вольно.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;

		case "Companion_TaskChangeNo":
			dialog.Text = "Так точно.";
			Link.l1 = "Вольно.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;

		case "Companion_TaskChangeYes":
			dialog.Text = "Будет исполнено.";
			Link.l1 = "Вольно.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
		//<--

		// Самостоятельное плавание компаньона -->
		case "CompanionTravel":
			if(GetAttrValue(PChar, "CompanionTravel") == 3) // Если уже троих отпустил
			{
				dialog.Text = "Капитан, я не выйду из состава вашей эскадры, так как вы и так уже отпустили три корабля.";
					Link.l1 = "Да, пожалуй ты прав.";
					Link.l1.go = "exit";
				break;
			}

			dialog.Text = "Нет проблем, кэп. Куда мне отправляться?";
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
			dialog.Text = "Где будет место встречи, капитан?";
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
