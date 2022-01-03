// 03.02.08 перенос из ВМЛ

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref    sld;
	string attr, attrLoc;
	int    iTemp, iTax, iFortValue;

    Pchar.quest.FreeRandomOfficerIdx = NPChar.index;

	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
		case "First time":

            NextDiag.TempNode = "First time";
			dialog.text = RandPhraseSimple("Приветствую, капитан! Девушка-офицер не нужна на вашем корыте?",
                          "Новый, очень продвинутый офицер нужен?");
			link.l1 = ""+ GetSexPhrase("Девушка? Офицер? Очень странно... И на что ты годишься?","Ещё одна женщина на корабле, и какая от тебя польза?") +"";
			link.l1.go = "Node_2";
            link.l2 = ""+ GetSexPhrase("Нет, милашка, у меня полный комплект.","С такой внешностью, иди к мужикам... офицером...") +"";
			link.l2.go = "exit";
		break;

		case "CitizenNotBlade":
			dialog.text = "Капитан, что за глупости! Уберите оружие, пока бед не наделали!";
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Не переживай, уже убираю...");
			link.l1.go = "exit";
		break;

		case "Node_2":
            if (NPChar.alignment == "good" && sti(pchar.reputation) < 70)
            {
                dialog.text = "Я гожусь на многое, но с вами мы не сработаемся. Ваша репутация недостаточна хороша. Пожалуй, я не пойду к вам в команду.";
    			link.l1 = "С такими запросами ты долго будешь без работы!";
    			link.l1.go = "exit";
    			break;
            }

            if (NPChar.alignment == "bad" && sti(pchar.reputation) > 30)
            {
                dialog.text = "Я гожусь на многое, но не для таких святош как ты, "+ GetSexPhrase("красавчик","красавица") +". Пожалуй, я не пойду к тебе в команду.";
    			link.l1 = "С такими запросами ты долго будешь без работы!";
    			link.l1.go = "exit";
    			break;
            }
			dialog.text = "Возьмите меня в качестве телохранителя и ваша спина всегда будет прикрыта моей шпагой. Ловкость и быстрота - вот мои козыри";
			link.l1 = "Личная телохранительница ммм... "+ GetSexPhrase("","к тому же девушка...") +" Сколько же ты хочешь за эту услугу?";
			link.l1.go = "price";
            link.l2 = "Спасибо, обойдусь.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OnceAgain";
		break;

        case "OnceAgain":
            NextDiag.TempNode = "OnceAgain";
            if (NPChar.alignment == "good" && sti(pchar.reputation) < 70)
            {
                dialog.text = "Я гожусь на многое, но с вами мы не сработаемся. Ваша репутация недостаточна хороша. Пожалуй, я не пойду к вам в команду.";
    			link.l1 = "С такими запросами ты долго будешь без работы!";
    			link.l1.go = "exit";
    			break;
            }

            if (NPChar.alignment == "bad" && sti(pchar.reputation) > 30)
            {
                dialog.text = "Я гожусь на многое, но не для таких святош как ты, "+ GetSexPhrase("красавчик","красавица") +". Пожалуй, я не пойду к тебе в команду.";
    			link.l1 = "С такими запросами ты долго будешь без работы!";
    			link.l1.go = "exit";
    			break;
            }
			dialog.text = "Неужели вы передумали, капитан? Решили, что новый телохранитель, да еще девушка, вам не помешает?";
			link.l1 = "Пожалуй, так. Сколько ты хочешь?";
			link.l1.go = "price";
            link.l2 = "Ошибаешься. Счастливо оставаться.";
			link.l2.go = "exit";
		break;

		case "price":
            if (FindFreeRandomOfficer() == -1)
            {
                dialog.text = "Хм. У вас полный комплект. О цене поговорим, когда вы сможете дать мне работу.";
    			link.l1 = "Хорошо.";
    			link.l1.go = "exit";
    			break;
            }
			dialog.text = "Думаю, мы с вами сойдемся на 50000 пиастров.";
			link.l1 = "Я "+ GetSexPhrase("согласен","согласна") +", красотка. Считай себя зачисленной в команду.";//"+ GetSexPhrase("","а") +"
			link.l1.go = "hire";
            link.l2 = "Ты не стоишь этих денег. Прощай.";
			link.l2.go = "exit";
		break;

        case "hire":
			if(makeint(Pchar.money) >= 50000)
			{
				AddMoneyToCharacter(Pchar, -50000);
                dialog.text = "Не стану благодарить вас, капитан. Вы сами прекрасно знаете, что удачно вложили свое золото.";
			    link.l1 = "Хочется в это верить.";
			    link.l1.go = "Exit_hire";
			}
			else
			{
				NextDiag.TempNode = "OnceAgain";
                dialog.text = "Эй, похоже, у вас проблемы с наличностью! Извините, капитан, но я не работаю в кредит.";
				link.l1 = "Ах ты, черт!";
				link.l1.go = "Exit";
			}
		break;

        case "hired":
			NextDiag.TempNode = "Hired";
			dialog.text = ""+ GetSexPhrase("Что желает мой драгоценный капитан?","Какие будут распоряжения?") +"";
			link.l2 = "Ты уволена. Я обойдусь без твоих услуг!";
			link.l2.go = "AsYouWish";

			if (bHalfImmortalPGG)
			{
				if (!CheckAttribute(pchar,"Option_ImmortalOfficers"))
				{
					pchar.Option_ImmortalOfficers = "0";
				}
				if (sti(pchar.Option_ImmortalOfficers) < makeint(GetCharacterSPECIAL(pchar,"Charisma")*2) && !CheckAttribute(npchar,"ImmortalOfficer"))
				{
					Link.l6 = "У меня к тебе предложение.";
					Link.l6.go = "contract";
				}
			}

			// приколы -->
            if (PChar.location == Get_My_Cabin())
            {
    			if (PChar.sex != "woman")
    			{
					Link.l3 = RandPhraseSimple("Раз уж мы в каюте давай может...а? Посмотри тут и кровать есть... такая мягенькая...",
	                                           "Посмотри какая в моей каюте большая кровать. Не хочешь разделить ее со мной?");
	                if (sti(pchar.GenQuest.BrothelCount) > 4+rand(3))
	                {
	                    Link.l3.go = "Love_Sex_Yes";
	                }
	                else
	                {
	                    Link.l3.go = "Love_Sex";
	                }
                }
                if (CheckAttribute(pchar , "questTemp.FUNY_SHIP_FIND") && PChar.questTemp.FUNY_SHIP_FIND == true && GetCharacterItem(PChar, "mineral4") >= 25)
                {
                    Link.l4 = "Смотри какая у меня коллекция собралась интересная!";
            		Link.l4.go = "FUNY_SHIP_1";
                }
            }
            else
            {
                if (PChar.sex != "woman")
                {
					Link.l3 = RandPhraseSimple("Девушка-телохранитель - это, конечно, хорошо, но может мы попытаемся сталь ближе?",
	                                           "Как насчет неуставных услуг?");
	                Link.l3.go = "Love_Sex";
                }
            }
            Link.l5 = "Слушай мой приказ!";
            Link.l5.go = "stay_follow";

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

            link.l9 = ""+ GetSexPhrase("Расслабься, красотка, отдыхай","Ничего. Вольно") +".";
			link.l9.go = "exit";
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

        case "Love_Sex_Yes":
		    dialog.text = RandPhraseSimple("Пожалуй, такому ловеласу можно и уступить.",
                                           "Хорошо, все лучше, чем транжирить деньги на уличных девок.");
            link.l1 = RandPhraseSimple("Oh, Yes!", "Умничка, не идти же мне в бордель, когда под боком есть такая лапа как ты!");
			link.l1.go = "Love_Sex_Yes_2";
        break;

        case "Love_Sex_Yes_2":
            pchar.GenQuest.BrothelCount = 0;
            AddCharacterExpToSkill(pchar, "Leadership", 100);
            AddCharacterExpToSkill(pchar, "Fencing", -50);// утрахала
            AddCharacterExpToSkill(pchar, "Pistol", -50);
            AddCharacterHealth(pchar, 10);

   			AddDialogExitQuest("PlaySex_1");
			NextDiag.CurrentNode = "After_sex";
			DialogExit();
        break;

        case "After_sex":
            NextDiag.TempNode = "Hired";
		    dialog.text = RandPhraseSimple("Хм.. странно, я думала ты способен на большее...",
                                           "Капитан, теперь вы снова можете соображать головой, а не... ? Вернемся к нашим делам.");
            link.l1 = RandPhraseSimple("Но-но! Как ты разговариваешь со старшим по званию!", "Я могу многое, если соберусь с мыслями.");
			link.l1.go = "exit";
        break;

        case "Love_Sex":
            NextDiag.TempNode = "Hired";
		    dialog.text = RandPhraseSimple("Что!!!?? Капитан, ты давно не сходил на берег и не был в борделе?", "Не понимаю, о чем это ты?");
            link.l1 = RandPhraseSimple("Ну сама подумай.. ты такая красавица, да еще и в моем подчинении", "Ну не идти же мне в бордель, когда под боком есть ты!");
			link.l1.go = "Love_Sex_2";
			link.l2 = RandPhraseSimple("Извини меня, крошка, очень трудно было удержаться, чтоб не предложить..", "Эх.. ладно, проехали...");
			link.l2.go = "exit";
        break;

        case "Love_Sex_2":
            NextDiag.TempNode = "Hired";
		    dialog.text = RandPhraseSimple("Капитан! Держите себя в руках, если не можете в своих, позовите матросов", "То, что я офицер и номинально подчиняюсь Вам, капитан, еще ничего не значит!");
            link.l1 = RandPhraseSimple("Детка, не протився. Я уже не могу себя сдерживать. Пойдем..", "Я - твой капитан! И я приказываю тебе!");
			link.l1.go = "Love_Sex_3";
			link.l2 = RandPhraseSimple("Извини меня, крошка, очень трудно было удержаться, чтоб не предложить..", "Эх.. ладно, проехали...");
			link.l2.go = "exit";
        break;

        case "Love_Sex_3":
            NextDiag.TempNode = "Hired";
		    dialog.text = RandPhraseSimple("Ну все! Ты ответишь за это! И прямо сейчас!", "Покувыркаться с тобой? Чтож сейчас поглядим, кто на что способен..");
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
        // приколы <--

        case "AsYouWish":
			dialog.text = "Как скажете, капитан, решать вам.";
			link.l1 = "Пожалуй, я передумал"+ GetSexPhrase("","а") +". Ты мне еще нужна.";
			link.l1.go = "exit";
			link.l2 = "Отлично. Можешь проваливать, куда подальше.";
			link.l2.go = "Exit_Fire";
		break;

        case "Exit_hire":
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			npchar.Dialog.FileName = "Enc_Officer_dialog.c";
			NPChar.Dialog.TempNode = "hired";
			Npchar.CanTakeMushket = true;
			npchar.HalfImmortal = true;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_fire":
   			NextDiag.TempNode = "Fired";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			FireImmortalOfficer(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

        case "Fired":
		      NextDiag.TempNode = "Fired";
		      dialog.text = "Я же предупреждала вас, капитан, что не вернусь на ваш корабль. У меня есть своя гордость.";
		      Link.l1 = "Да ты мне и не нужна!";
		      Link.l1.go = "Exit";
	    break;
		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "stay_follow":
            dialog.Text = "Какие будут приказания?";
            Link.l1 = "Стой здесь!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Следуй за мной и не отставай!";
            Link.l2.go = "Boal_Follow";
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

        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Есть изменить дислокацию!";
            Link.l1 = "Вольно.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;

        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar); // it works!!!
            dialog.Text = "Есть изменить дислокацию!";
            Link.l1 = "Вольно.";
            Link.l1.go = "Exit";
        break;

		//////////////////////////////    офицер-наместник -->
		case "Gover_Hire":
            dialog.Text = "Почту за честь!";
            Link.l1 = "Следи за порядком и процветанием города, я буду иногда приплывать за собранной пошлиной.";
			Link.l1.go = "Exit_Gover_Hire";
            Link.l2 = "Я передумал"+ GetSexPhrase("","а") +".";
            Link.l2.go = "Exit";
            NextDiag.TempNode = "Hired";
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
			NextDiag.CurrentNode = "Gover_Main";
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
            NextDiag.TempNode = "Gover_Main";
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

			NextDiag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Fire":
            dialog.Text = "Замечательно! Быть сухопутной крысой не мой удел.";
            Link.l8 = "Вот и славно.";
            Link.l8.go = "exit_hire";
            NextDiag.TempNode = "Hired";
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
			if(bBettaTestMode) // Только при бета-тесте
			{
			    Link.l3 = "Я хочу, чтобы ты на время выш"+ GetSexPhrase("ел","ла") +" из состава моей эскадры и поискал удачу самостоятельно.";
			    Link.l3.go = "CompanionTravel";
			}
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
		case "exit_spec":
			DialogExit();
		break;
		//Йока
		case "Yoko_meet":
			if (sti(pchar.reputation) >= 70)
			{
				dialog.Text = "Приветствую вас, капитан. Я - Йоко Диаз, вольный клинок.";
				Link.l1 = "Выглядишь как-то потрёпанно. Ищешь работу?";
				Link.l1.go = "Yoko";
			}
			else
			{
				dialog.Text = "Не думаю, что нам есть о чём говорить, капитан.";
				Link.l1 = "Не очень-то и хотелось.";
				Link.l1.go = "exit_spec";
				NextDiag.TempNode = "Yoko_meet";
			}
		break;

		case "Yoko":
			dialog.Text = "Ищу, но сейчас толку от меня едва ли будет.";
			Link.l1 = "Почему это?";
			Link.l1.go = "Yoko_1";
		break;

		case "Yoko_1":
			ref locLoad = &locations[FindLocation("Shore_ship1")];
			string blade = GetGeneratedItem("Blade15");
			locLoad.box1.items.(blade) = 1;
			npchar.stortaid = blade;
			locLoad.box1.money = 7461;
			locLoad.box1.notouch = true;

			dialog.Text = "Погуляла я вчера ночью в местной таверне, а утром оказалось, что пропали все деньги и моя Сторта. Если сумеете их вернуть - я пойду в вашу команду.";
			Link.l1 = "Найти на большом острове конкретный меч... Та ещё задачка, но я могу попробовать.";
			Link.l1.go = "Yoko_2";
		break;

		case "Yoko_2":
			dialog.Text = "Я буду ждать, капитан.";
			Link.l1 = "До встречи, Йоко!";
			Link.l1.go = "exit_spec";
			NextDiag.currentnode = "Yoko_wait";
			NextDiag.TempNode = "Yoko_wait";
		break;

		case "Yoko_wait":
			dialog.Text = "Как успехи, капитан?.";
			if (GetCharacterFreeItem(pchar,npchar.stortaid))
			{
				Link.l1 = "Мне удалось разыскать твою Сторту. Держи.";
				Link.l1.go = "Yoko_nowait";
			}
			Link.l2 = "Извини, пока ничего.";
			Link.l2.go = "Yoko_2";
		break;

		case "Yoko_nowait":
			TakeNItems(pchar,npchar.stortaid,-1);
			GiveItem2Character(NPChar, npchar.stortaid);
			EquipCharacterbyItem(NPChar, npchar.stortaid);
			dialog.Text = "Благодарю вас!";
			Link.l1 = "И что теперь?";
			Link.l1.go = "price";
			DeleteAttribute(NPChar,"Dialog.CurrentNode");
			NextDiag.TempNode = "OnceAgain";
		break;
		//Элен
		case "Helen_meet":
			if (startherotype == 5 || startherotype == 6)
			{
				if(npchar.id == "Beatrice")
				{
					dialog.text = "У тебя хватает наглости заявляться сюда, после того, что было? Прочь с глаз моих, пока я тебя не зарубила!";
					link.l1 = "Прости, Элен...";
					link.l1.go = "exit";
					break;
				}
			}
			if (sti(pchar.reputation) >= 70)
			{
				if (CheckAttribute(npchar, "MetWhisper"))
				{
					dialog.Text = "Я слышала вы уже стали капитаном. Быстро растёте! Мы ведь так и не представились? ";
				}
				else dialog.Text = "Приветствую вас, капитан. ";
				dialog.Text = dialog.Text + "Я - Элен Мак Артур, волею судьбы оказалась на берегу и теперь ищу работу офицером.";
				Link.l1 = "Ты прежде была капитаном? Значит наверняка должна разбираться хоть понемногу во всём, так?";
				Link.l1.go = "Helen";
			}
			else
			{
				dialog.Text = "Не думаю, что нам есть о чём говорить, капитан.";
				Link.l1 = "Не очень-то и хотелось.";
				Link.l1.go = "exit_spec";
				NextDiag.TempNode = "Helen_meet";
			}
		break;
		case "Helen":
			dialog.Text = "Так точно. Разбираюсь и в навигации, и в стрельбе.";
			Link.l1 = "Если ты так хороша, почему же тебя ещё не взяли?";
			Link.l1.go = "Helen_1";
		break;
		case "Helen_1":
			dialog.Text = "Есть здесь один мерзавец в Пуэрто-Принсипе, даже не знаю почему его тут все терпят. Так вот он распускает обо мне всякие грязные слухи, из-за чего никто не желает брать меня к себе.";
			Link.l1 = "А не пробовала заткнуть ему рот сталью?";
			Link.l1.go = "Helen_2";
		break;
		case "Helen_2":
			dialog.Text = "Почему, как ты думаешь, я всё ещё здесь? Уже пыталась, так он разделал меня под орех и пощадил на первый раз.";
			Link.l1 = "И ты хочешь, чтобы я тебе помог с этим? И тогда присоединишься?";
			Link.l1.go = "Helen_3";
		break;
		case "Helen_3":
			dialog.Text = "Разумеется. Ну, ещё со скромными подъёмными.";
			Link.l1 = "Я постараюсь тебе помочь, Элен.";
			Link.l1.go = "Helen_wait";

			sld = GetCharacter(NPC_GenerateCharacter("HelenBastard", "pirate_1", "man", "man", 30, PIRATE, -1, false));
			sld.name 	= "Джулиус";
			sld.lastname = "Брин";
			SetSPECIAL(sld, 9,8,7,6,7,8,9);
			FantomMakeCoolFighter(sld, 30, 90, 50, "blade42", "pistol4", 350);
			SelAllPerksToNotPchar(sld);
			sld.location	= "PuertoPrincipe_port";
			sld.location.group = "goto";
			sld.location.locator = "goto7";
			sld.dialog.filename   = "Enc_OfficerGirl.c";
			sld.dialog.currentnode = "Helen_Bastard";
			sld.perks.list.BasicDefense = true;
			sld.perks.list.AdvancedDefense = true;
			sld.perks.list.SwordplayProfessional = true;
			sld.perks.list.CriticalHit = true;
			sld.perks.list.Gunman = true;
			sld.perks.list.GunProfessional = true;
			sld.perks.list.Energaiser = true;
			sld.perks.list.ByWorker = true;
			sld.perks.list.ShipEscape = true;
			sld.perks.list.Ciras = true;
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			LAi_SetImmortal(sld,true);
			DeleteAttribute(sld,"lifeDay");
			LAi_group_MoveCharacter(sld, "player");
		break;
		case "Helen_wait":
			if (!CheckAttribute(pchar,"HelenMet"))
			{
				dialog.Text = "Я буду ждать, капитан. Удачи!";
				pchar.HelenMet = true;
			}
			else
			{
				dialog.Text = "Как успехи, капитан?";
			}
			Link.l1 = "Хорошо. Пока, Элен.";
			Link.l1.go = "exit_spec";
			if (CheckAttribute(pchar,"HelenQuest"))
			{
				Link.l1 = "С ним покончено, о тебе больше никто не будет распускать слухи.";
				Link.l1.go = "Helen_nowait";
			}
			NextDiag.currentnode = "Helen_wait";
			NextDiag.TempNode = "Helen_wait";
		break;
		case "Helen_Bastard":
			dialog.Text = "А ты ещё кто? Очередн"+ GetSexPhrase("ой придурок","ая дура") +", котор"+ GetSexPhrase("ый","ая") +" хочет нанять Элен в офицеры? Я тебе такого о ней расскажу, что у тебя волосы дыбом встанут.";
			Link.l1 = "Не интересует. Предлагаю сделку. Ты за час убираешься из Пуэрто-Принсипе или будешь мёртв прямо здесь и сейчас. Что скажешь?";
			Link.l1.go = "Helen_Bastard_2";
		break;

		case "Helen_Bastard_2":
			dialog.Text = "Смеешь мне угрожать? Что-ж, твои проблемы. Защищайся, капитан!";
			Link.l1 = "Я уж думал"+ GetSexPhrase("","а") +", что ты и не попросишь...";
			Link.l1.go = "Helen_Bastard_exit";
		break;
		case "Helen_Bastard_exit":
			pchar.HelenQuest = 1;
			DialogExit();
			LAi_SetImmortal(NPChar,false);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			chrDisableReloadToLocation = true;
			pchar.quest.HelenBastard.win_condition.l1 = "NPC_Death";
			pchar.quest.HelenBastard.win_condition.l1.character = "HelenBastard";
			pchar.quest.HelenBastard.win_condition = "OpenTheDoors";
		break;
		case "Helen_nowait":
			dialog.Text = "Благодарю вас, капитан! Теперь о моих подъёмных...";
			Link.l1 = "Не за что! Ну так сколько?";
			Link.l1.go = "price";
			DeleteAttribute(pchar,"HelenMet");
			DeleteAttribute(pchar,"HelenQuest");
			DeleteAttribute(NPChar,"Dialog.CurrentNode");
			NextDiag.TempNode = "OnceAgain";
		break;
		//Анджелика
		case "Angellica_meet":
			if (startherotype == 3 || startherotype == 4)
			{
				if(npchar.id == "Angellica")
				{
					dialog.text = "Кто это тут у нас? Ещё один плод неуёмной любви моего папаши к слабому полу? Сегодня я не в настроении убивать родственников. Иди своей дорогой!";
					link.l1 = "Эх, а мы могли бы осуществить мечту отца вместе. Ну, как знаешь Анджелика, прощай.";
					link.l1.go = "exit";
					break;
				}
			}
			if (NPChar.alignment == "bad" && sti(pchar.reputation) <= 30)
			{
				dialog.Text = "Эй, капитан! Тебе выпала честь нанять старпомом - дочь самого Николаса Шарпа! Если ты досто"+ GetSexPhrase("ин","йна") +", конечно!";
				Link.l1 = "Какое самомнение! И ты уверена, что с подобными взглядами тебя кто-то возьмёт?";
				Link.l1.go = "Angellica";
			}
			else
			{
				dialog.Text = "Не думаю, что нам есть о чём говорить, капитан.";
				Link.l1 = "Не очень-то и хотелось.";
				Link.l1.go = "exit_spec";
				NextDiag.TempNode = "Angellica_meet";
			}
		break;
		case "Angellica":
			dialog.Text = "Уж поверь, желающие найдутся. Может хочешь попробовать?";
			Link.l1 = "И что же ты считаешь признаком достоинства?";
			Link.l1.go = "Angellica_2";
		break;

		case "Angellica_2":
			if (!CheckAttribute(pchar,"AngellicaDuelInfo")) {dialog.Text = "Победи меня на дуэли и за скромное вознаграждение я присоединюсь к тебе."; pchar.AngellicaDuelInfo = true;}
			else dialog.Text = "Ну что, решил"+ GetSexPhrase("ся","ась") +"?";
			Link.l1 = "Я готов"+ GetSexPhrase("","а") +"!";
			Link.l1.go = "Angellica_duel_exit";
			Link.l2 = "Пожалуй, попозже.";
			Link.l2.go = "exit_spec";
			NextDiag.currentnode = "Angellica_2";
			NextDiag.TempNode = "Angellica_2";
		break;

		case "Angellica_duel_exit":
			DialogExit();
			NextDiag.currentnode = "Angellica_duel_won";
			NextDiag.TempNode = "Angellica_duel_won";
			ChangeCharacterAddressGroup(NPChar, "LeFransua_ExitTown", "enc01", "enc01_04");
			LAi_SetCheckMinHP(NPChar, 5, true, "AngellicaDialog");
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetHP(npchar, 500, 500);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			DoQuestReloadToLocation("LeFransua_ExitTown","reload","reload3", "");
			chrDisableReloadToLocation = true;
		break;
		case "Angellica_duel_won":
			dialog.Text = "Потрясающе! Из местных никому ещё не удавалось одолеть меня...";
			Link.l1 = "Ты тоже заставила меня попотеть.";
			Link.l1.go = "Angellica_duel_won_exit";
			LAi_SetHP(npchar, 150, 150);
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"AngellicaDuelInfo");
			LAi_SetImmortal(NPChar,false);
		break;
		case "Angellica_duel_won_exit":
			DialogExit();
			LAi_SetWarriorType(NPChar);
			LAi_warrior_DialogEnable(NPChar, true);
			NextDiag.currentnode = "Angellica_duel_won_2";
			NextDiag.TempNode = "Angellica_duel_won_2";
		break;
		case "Angellica_duel_won_2":
			dialog.Text = "Теперь я готова к вам присоединиться, капитан.";
			Link.l1 = "И за сколько?";
			Link.l1.go = "price";
			DeleteAttribute(NPChar,"Dialog.CurrentNode");
			NextDiag.TempNode = "OnceAgain";
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
