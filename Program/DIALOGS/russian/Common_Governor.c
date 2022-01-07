// boal 25/04/04 общий диалог Governor
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Governor\" + NationShortName(sti(NPChar.nation)) + "_Governor.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}

	int Matheria1 = 4000;//шелк
	int Matheria2 = 3000;//красное
	int Matheria3 = 2000;//черное
	int BuildPrice = 3000000;

    // вызов диалога по городам <--

    ref offref, sld;
    int i, cn;
    int qty;
    int iSumm;
    string attrLoc;

    /// выкуп колонии
    ref CaptGovenor, FortColony;
    int f, colony_money;

    int k = 1000;
    if (CheckAttribute(Nations[sti(NPChar.nation)], "Fort"))
    {
        k = (300 - sti(Nations[sti(NPChar.nation)].Fort)*10);
    }
	bool ok;

	attrLoc = Dialog.CurrentNode;
	if (findsubstr(attrLoc, "CityGive_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.quest.CityIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "ColonyGive";
 	}

	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

		case "arest":
			dialog.text = "Стража! Взять е"+ GetSexPhrase("го","е") +"!";
			link.l1 = "Ну, уж нет! Просто так вы меня не возьмете!";
		    link.l1.go = "fight";
		break;

		case "Patent_Doubt":
			dialog.text = "Гладко стелите... Мне стоило бы вас повесить за одну лишь дерзость. Таким отъявленным пиратам веры нет, однако сейчас на нашем архипелаге тяжелые времена и пригодится любая помощь. Так и быть, я подпишу вам патент, и помилование. Только не заставляйте меня жалеть об этом.";
			link.l1 = "Вы не пожалеете, " + GetAddress_FormToNPC(NPChar) + "!";
			link.l1.go = "Patent_Give";
			link.l2 = "Ха! Повелись! Это была лишь шутка, я не хочу иметь ничего общего с вашим никчемным государством.";
			link.l2.go = "arest_3";
		break;
		case "Patent_Give":
            pchar.PatentNation = NationShortName(sti(NPChar.nation));
            pchar.PatentPrice = 0;
			dialog.text = "Пожалуйста, надеюсь на дальнейшее сотрудничество. Приходите ко мне время от времени. У меня могут найтись важные задания для вас.";
			link.l1 = "Спасибо. Прощайте, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "exit";
			AddDialogExitQuest("any_patent_take");
			ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", -100);
		break;

		case "First time":
            NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase("Вы посмели явиться к генерал-губернатору?! Смелый шаг...", "Как эти бездельники допустили, чтобы ко мне ворвался враг?! Уму непостижимо...", "Да уж, моя охрана немногого стоит, раз "+ GetSexPhrase("какой-то бездельник","какая-то бездельница") +" бегает в моей резиденции..."),
					LinkRandPhrase("Что тебе нужно, "+ GetSexPhrase("негодяй","негодяйка") +"?! Мои солдаты уже взяла твой след, далеко тебе не уйти, "+ GetSexPhrase("грязный пират","мерзавка") +"!", ""+ GetSexPhrase("Грязный","Грязная") +" убийца, вон из моей резиденции! Стража!!", "Я не боюсь тебя, "+ GetSexPhrase("мерзавец","мерзавка") +"! Скоро тебя повесят в форте, далеко тебе не уйти..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Солдатня мало чего стоит...", "Им меня ни за что не поймать."),
					RandPhraseSimple("Заткни свою пасть, приятель, а не то вырву твой поганый язык!", "Вот что я тебе скажу, приятель: сиди тихо, и будешь жить..."));
				link.l1.go = "fight";
				break;
			}
			if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) > 15)
            {
                dialog.text = "О! Кто пришел! Это же сам"+ GetSexPhrase("","а") +" " + GetFullName(pchar) + ". Мы как раз недавно высылали охотников за головами, чтобы они привели вас сюда. И знаете, это уже встало нам в кругленькую сумму.";
                if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) == 100 && !isMainCharacterPatented())
				{
				link.l3 = "Вы видели на что я способ"+ GetSexPhrase("ен","на") +" будучи врагом, а теперь представьте какую пользу я смогу принести вашей державе в качестве союзника. Предлагаю всего раз, здесь и сейчас: выдайте мне патент и все ваши враги станут моими.";
				link.l3.go = "Patent_Doubt";
				}
				link.l2 = "Э... пожалуй, мне пора.";
				link.l2.go = "arest";
				break;
            }
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
    			dialog.text = "Враг в резиденции! Тревога!!";
				link.l1 = "А-ать, дьявол!";
				link.l1.go = "fight";
				break;
			}

			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Я слышал, что вы очень настойчиво просили аудиенции. Меня зовут " + GetFullName(npchar) +
                              ". Я генерал-губернатор колоний " + NationNameGenitive(sti(NPChar.nation))+ ", наместник короны " + NationKingsName(npchar)+
                              " в этих водах. А теперь соблаговолите сообщить цель вашего визита, " + GetAddress_Form(NPChar) + ".";
				link.l1 = "Мое имя " + GetFullName(pchar) + ".";
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple("А, это опять вы? По какому вопросу вам понадобился генерал-губернатор " + NationNameGenitive(sti(NPChar.nation))+ " на этот раз?",
                              "Опять отрываете меня от важных государственных дел? Что вам угодно, " +GetAddress_Form(NPChar)+"?");
				link.l1 = "Я хочу поговорить о работе на благо короны " + NationNameGenitive(sti(NPChar.nation));
				link.l1.go = "work";
				link.l2 = "Нужно поговорить с вами об одном деле.";
				link.l2.go = "quests"; // файл нации
				link.l10 = "Прошу простить, но меня ждут дела.";
				link.l10.go = "exit";

				if (GetQuestPastDayParam("pchar.questTemp.buildSoley") >= 60 && NPchar.Nation == FRANCE && !CheckAttribute(npchar, "quest.Gave_Ship"))
				{

				Link.l15 = "Ну что, корабль готов?";
				link.l15.go = "get_ship";
				}


				/*
				Можно в конце линейки сделать запрос: "Я, состою во флоте Франции, для усиления боевой мощи нашей державы, необходимо построить второй корабль - аналог СР".
				В таком случае, один корабль будет охранять главную колонию, на втором корабле мы будем плавать и громить форты, захватывая колонии для Франции".
				На постройку корабля - высчитать все ресурсы: доски, парусина, ЧД, КД, и еще некоторые ресурсы в больших количествах. Цена постройки 3 млн. Время строительства 1 месяц.
				Всё, всё по лору и все довольны без лишнего нытья.
				*/
			}
		break;

		case "build_ship":
			dialog.Text = "Это отличная идея! Однако в казне нет ресурсов для ее осуществения... Если хотите, вы можете привезти собственный материал и оплатить работу инженеров и рабочих. Я все организую.";
			Link.l1 = "Я " + GetSexPhrase("согласен","согласна")+ ". Что и в каком объеме нужно будет доставить?";
			Link.l1.go = "build_ship_1"
			Link.l2 = "Простите, но на такое у меня нет ни времени, ни денег.";
			Link.l2.go = "exit";
		break;

		case "build_ship_1":
			dialog.Text = "Итак, для постройки королевского мановара понадобятся: "+Matheria2+" единиц красного дерева, "+Matheria3+" черного дерева, "+Matheria1+" шелка, прочие материалы вроде парусины и досок мы сами сможем произвести в наших колониях. Однако вы должны заплатить "+BuildPrice+" золотых вперед на их закупку, а также чтобы я смог начать найм рабочей силы и прочую организационную деятельность.";

			if(makeint(Pchar.money) >= BuildPrice)
			{
				Link.l1 = "Договорились, вот деньги. Скоро привезу вам все остальное.";
				Link.l1.go = "build_ship_2"
			}
			Link.l2 = "Недешего, пожалуй обойдусь...";
			Link.l2.go = "exit";
		break;

		case "build_ship_2":
			AddMoneyToCharacter(Pchar, -BuildPrice);
			dialog.Text = "Ждем с нетерпением.";
			npchar.quest.answer_1 = "true";

			NPChar.Tuning.Matherial1 = Matheria1;
			NPChar.Tuning.Matherial2 = Matheria2;
			NPChar.Tuning.Matherial3 = Matheria3;
			NextDiag.TempNode = "check_material";
			Link.l2 = "До свидания.";
			Link.l2.go = "exit";
		break;

		case "check_material":

				dialog.Text = "Работа ждет. Принес"+ GetSexPhrase("","ла") +", что я просил?";

				NextDiag.TempNode = "check_material";


			    Link.l1 = "Да. Кое-что удалось достать.";
			    Link.l1.go = "check_material_1";
			    Link.l2 = "Нет. Еще добываю.";
			    Link.l2.go = "Exit";
		break;

		case "check_material_1":

			checkSoleyMatherial(Pchar, NPChar, GOOD_SILK, GOOD_MAHOGANY, GOOD_EBONY);

		    if(sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Matherial3) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");

                dialog.text = "Вы все привезли. Отлично! Возвращайтесь через пару месяцев, думаю к тому времени постройка уже будет завершена...";
				SaveCurrentQuestDateParam("pchar.questTemp.buildSoley");
				NextDiag.TempNode = "First time";
			    link.l1 = "Жду.";
			    link.l1.go = "exit";

			}
			else
			{
				dialog.Text = "Тебе осталось привезти:" + ", красного дерева - "+ sti(NPChar.Tuning.Matherial2) + ", черного дерева - "+ sti(NPChar.Tuning.Matherial3) + ", шелка - "+ sti(NPChar.Tuning.Matherial1)".";
				link.l1 = "Хорошо.";
				link.l1.go = "Exit";
			}
		break;

		case "get_ship":
			dialog.text = "А как же! Можете забирать его в порту. Мы уже успели немного опробовать его на одной пиратской эскадре. Должен признаться, что немного вам завидую, этот корабль уникален во всех смыслах этого слова. В довесок к мановару я передаю вам в службу отличного офицера, надеюсь вы найдете ему применение.";
			NextDiag.TempNode = "First time";
			npchar.quest.Gave_Ship = "true";
			sld = GetCharacter(NPC_GenerateCharacter("SoleiRoyalCaptain1", "off_fra_2", "man", "man", 35, FRANCE, -1, true));
			sld.Ship.Name = "Солей Руаяль";
			sld.Ship.Type = GenerateShipExt(SHIP_SOLEYRU, true, sld);
			ResetShipCannonsDamages(sld);
			SetBaseShipData(sld);
			SetCrewQuantityFull(sld);
			SetShipSkill(sld, 50, 60, 70, 55, 95, 55, 50, 55, 50);
			Fantom_SetBalls(sld, "pirate");
			FantomMakeCoolFighter(sld, 35, 80, 70, BLADE_LONG, "pistol3", 100);

			sld.Dialog.TempNode = "hired";
			sld.Dialog.FileName = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			SetBaseShipData(sld);
			sld.CompanionEnemyEnable = false;
			SetCompanionIndex(pchar, -1, sti(sld.index));

			sld.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
			sld.loyality = MAX_LOYALITY;
			//AddDialogExitQuestFunction("LandEnc_OfficerHired");


			link.l1 = "Благодарю. Немедленно его испытаю.";
			link.l1.go = "Exit";
		break;

		case "node_1":
			dialog.text = "Так какая причина заставила вас прийти сюда и отвлекать меня от важных государственных дел?";
			link.l1 = "Я хочу поговорить о работе на благо короны " + NationNameGenitive(sti(NPChar.nation));
			link.l1.go = "work";
			link.l2 = "Нужно поговорить с вами об одном деле.";
			link.l2.go = "quests";
			link.l10 = "Это просто визит вежливости и ничего более, "+GetAddress_FormToNPC(NPChar);
			link.l10.go = "node_2";
		break;

		case "node_2":
			dialog.text = "В таком случае, я попрошу вас покинуть мой кабинет и не мешать мне работать.";
			link.l1 = "Да, да, конечно, извините, что потревожил"+ GetSexPhrase("","а") +" вас.";
			link.l1.go = "exit";
		break;

		case "work":
            if (!CheckCharacterItem(Pchar, "patent_" + NationShortName(sti(NPChar.nation))) || !CheckAttribute(pchar, "EquipedPatentId"))
			{
    			dialog.text = "Я вас совершенно не знаю, " + GetAddress_Form(NPChar) + ". Покиньте мой кабинет. Я имею дела только с людьми, состоящими на службе " + NationKingsName(npchar) + ".";
    			link.l1 = "Простите за беспокойство. Когда у меня будет патент "+NationNameGenitive(sti(NPChar.nation))+", я вернусь.";
    			link.l1.go = "exit";
			}
			else
			{// даем задание
                // звание подрасло
                if (isReadyToNextTitle(sti(NPChar.nation)))
                {
                    Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
                    Items[sti(pchar.EquipedPatentId)].TitulCur = sti(Items[sti(pchar.EquipedPatentId)].TitulCur) + 1;

                    dialog.text = "Я должен обрадовать вас"+ ", " + GetAddress_Form(NPChar)+". Прошение о вашем повышении по службе подписано в канцелярии " + NationKingsName(npchar) +
                                ". Вам присвоено звание " + GetAddress_FormTitle(sti(NPChar.nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur)) +
                                " флота " + NationNameGenitive(sti(NPChar.nation)) +".";
        			link.l1 = "Спасибо! Обещаю и дальше с честью служить "+NationKingsCrown(npchar) + ".";
        			link.l1.go = "exit";
        			break
                }
                // даем задание
                dialog.text = LinkRandPhrase("Вы имеете вопросы ко мне, "+GetAddress_FormTitle(sti(NPChar.nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur))+"?",
                                             "Я слушаю вас, " + GetAddress_Form(NPChar)+".",
                                             "Говорите, я весь внимание.");

                //GetAddress_Form(NPChar)+", я рад, что "+ GetSexPhrase("такой бравый","такая бравая") +" "+GetAddress_FormTitle(sti(NPChar.nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur))+" на службе " + NationKingsName(npchar) + ".";
				if (pchar.questTemp.NationQuest == "")
                {
	    			if (pchar.questTemp.piratesLine == "begin" || pchar.questTemp.piratesLine == "over" || pchar.questTemp.piratesLine == "waiting_Q8" || pchar.questTemp.LSC == "over")
					{
						link.l1 = "Есть ли какая работа для патентованного корсара?";
	    				link.l1.go = "work_1";
						if (!bWorldAlivePause && pchar.questTemp.State == "") //eddy. только, если не проходил линейку.
						{
							link.l1.go = "onlyGenWork_Alter";
						}
					}
					else
					{
						link.l1 = "Есть ли какая работа для патентованного корсара?";
	    				link.l1.go = "onlyGenWork_2";
					}
    			}
    			else
    			{
    			    if (pchar.questTemp.NationQuest == NPChar.nation)
	                {
		    			link.l1 = RandPhraseSimple("Я прибыл"+ GetSexPhrase("","а") +" по делу, напрямую связанному с вашими поручениями.", "По поводу ваших заданий...");
		    			link.l1.go = "work_1";
	    			}
	    			else
	    			{// линейкам - фиг
	    			    link.l1 = "Есть ли какая работа для патентованного корсара?";
	    				link.l1.go = "onlyGenWork_1";
	    			}
    			}

                // Сдача города -->
				if (isHeroOwnCity(false))
				{
				    Link.l2 = "Я хочу перевести захваченное мной поселение под флаг "+ XI_ConvertString(GetNationNameByType(sti(NPChar.nation)) + "Gen") +".";
					Link.l2.go = "colony_capture";
				}
                // Сдача города <--
                link.l9 = RandPhraseSimple("Извините, я зайду позже.",
                                           "Ничего серьезного, "+GetAddress_FormToNPC(NPChar)+". Просто визит вежливости.");
    			link.l9.go = "exit";
			}
		break;

		case "onlyGenWork_1":
			dialog.text = "Хм... Я слышал, что вы выполняли тайные задания для "+ NationNameGenitive(sti(pchar.questTemp.NationQuest)) +", поэтому ничего секретного я вам поручить уже не смогу.";
			link.l1 = "Очень жаль.";
			link.l1.go = "exit";
		break;

		case "onlyGenWork_2":
			dialog.text = "Ходят слухи, что вы очень тесно связаны с главарями Берегового Братства. Поэтому не думаю, что я смогу поручать вам работу на благо " + NationNameGenitive(sti(npchar.nation)) + ".";
			link.l1 = "Хм... Ну что же, очень жаль.";
			link.l1.go = "exit";
		break;

		case "onlyGenWork_Alter":
   			dialog.text = "К сожалению для вас и к счастью для меня, рискованных и высокооплачиваемых заданий для корсара у меня сейчас нет.";
			link.l1 = "Что же, зайду позже.";
			link.l1.go = "exit";
		break;

		/////Награда за захваченную колонию.
		case "colony_capture":
   			dialog.text = "О каком городе идет речь?";
   			for (i=0; i<MAX_COLONIES; i++)
			{
				if (sti(colonies[i].HeroOwn) == true)
				{
					sld = GetFortCommander(colonies[i].id);
					attrLoc = "l" + i;
					Link.(attrLoc) = GetCityName(colonies[i].id);
					Link.(attrLoc).go = "CityGive_" + i;
				}
			}
			link.l99 = "Я "+ GetSexPhrase("ошибся","ошиблась") +", речь шла о другом.";
			link.l99.go = "exit";
		break;

        case "ColonyGive":
            i = sti(NPChar.quest.CityIdx);
            sld = GetFortCommander(colonies[i].id);
            colony_money = TWN_CityCost(colonies[i].id) / 50;  // те *1000 в итоге
            TWN_RealeseForMoney(colonies[i].id, false);
            dialog.text = "Отличные новости, "+GetAddress_FormTitle(sti(NPChar.nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur))+
                          "! Ваше усердие не останется незамеченным, и, разумеется, вас ждет награда. Вот вам " + colony_money +
                          " золотых в качестве вознаграждения за ваши заслуги перед "+NationNameAblative(sti(NPChar.nation))+
                          ". А теперь прошу меня извинить, у меня очень много дел.";
            link.l1 = "В таком случае, " + GetAddress_FormToNPC(NPChar) + ", не смею вас больше задерживать. Всего наилучшего.";
            link.l1.go = "exit";

            ReOpenQuestHeader("Gen_CityCapture");
		    AddQuestRecord("Gen_CityCapture", "t8");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("cя","ась"));
			AddQuestUserData("Gen_CityCapture", "sCity", GetCityName(colonies[i].id));
			AddQuestUserData("Gen_CityCapture", "sNation", XI_ConvertString(GetNationNameByType(sti(NPChar.nation)) + "Gen"));

            AddMoneyToCharacter(PChar, colony_money);
            AddTitleNextRate(sti(NPChar.nation), 1);  // счетчик звания
            ChangeCharacterNationReputation(Pchar, sti(NPChar.nation), 10);
            PChar.questTemp.DontNullDeposit = true;    // чтоб не нулили ростовщика
            SetCaptureTownByNation(colonies[i].id, sti(NPChar.nation));
        break;

		//*************************** Квест "Сопровождение флейта "Орион"" **********************
        case "Andre_Abel_Quest_Hol_Gov_Node_1":
			//if (GetCityNameByIsland(Pchar.curIslandId) == "Villemstad")
			if (pchar.location == "Villemstad_townhall")
			{
			dialog.text = "Я вас слушаю, капитан.";
			link.l1 = "Я прибыл"+ GetSexPhrase("","а") +" от Генри Моргана с поручением передать вам вот это письмо...";
			link.l1.go = "Andre_Abel_Quest_Hol_Gov_Node_2";
			TakeItemFromCharacter(PChar, "letter_1");
			Log_TestInfo("Письмо отдано генерал-губернатору Кюрасао.");
			PChar.Quest.Andre_Abel_Quest_Curasao_10Days_Left.over = "yes";
			}
			else
			{
			dialog.text = "Отрываете меня от важных государственных дел? Что вам угодно, " +GetAddress_Form(NPChar)+"?";
			link.l1 = "Это просто визит вежливости и ничего более, "+GetAddress_FormToNPC(NPChar)".";
			link.l1.go = "exit";
			NextDiag.TempNode = "Andre_Abel_Quest_Hol_Gov_Node_1";
			}
		break;

		case "Andre_Abel_Quest_Hol_Gov_Node_2":
			dialog.text = "Хм... от Моргана? Однако... Что ж, давайте ваше письмо от Генри Моргана.";
			link.l1 = "Прошу вас...";
			link.l1.go = "Andre_Abel_Quest_Hol_Gov_Node_3";
		break;

		case "Andre_Abel_Quest_Hol_Gov_Node_3":
			dialog.text = "Что?! Оставить Форт Оранж?! Ах, английские собаки! Мало им Порт Рояля, так на весь остров рот разинули! Схватить "+ GetSexPhrase("этого проходимца","эту мерзавку") +"!";
			link.l1 = "Минхер! Я всего лишь "+ GetSexPhrase("посыльный","посыльная") +", и не могу отвечать за содержание письма!..";
			link.l1.go = "Andre_Abel_Quest_Hol_Gov_Node_4";
		break;

		case "Andre_Abel_Quest_Hol_Gov_Node_4":
			dialog.text = "Ты человек Моргана, и ты "+ GetSexPhrase("англичанин","англичанка") +". Этого достаточно!.. В каземат "+ GetSexPhrase("его","ее") +"!";
			link.l1 = "Да вам нервы лечить нужно!!!";
			link.l1.go = "Andre_Abel_Quest_Hol_Gov_Node_5";
			link.l2 = "Что ж, я вынужден"+ GetSexPhrase("","а") +" подчиниться властям! Но повторяю, - моя совесть чиста, и я не совершал"+ GetSexPhrase("","а") +" и не замышлял"+ GetSexPhrase("","а") +" против Голландии ничего, за что меня можно было бы преследовать!";
			link.l2.go = "Andre_Abel_Quest_Hol_Gov_Node_7";
			link.l3 = "Господин Генерал-Губернатор, зачем же сразу в тюрьму?! Я уверен"+ GetSexPhrase("","а") +", что мы могли бы неплохо договориться...";
			link.l3.go = "Andre_Abel_Quest_Hol_Gov_Node_9";
		break;

		case "Andre_Abel_Quest_Hol_Gov_Node_5":
			dialog.text = "Как ты смеешь, "+ GetSexPhrase("мерзавец","мерзавка") +"! Убейте "+ GetSexPhrase("его","ее") +" немедленно!!!";
			link.l1 = "Ну, гвардейцы, держитесь!..";
			link.l1.go = "Andre_Abel_Quest_Hol_Gov_Node_6";
		break;

		case "Andre_Abel_Quest_Hol_Gov_Node_6":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetFightMode(PChar, true);
			Flag_Change(PIRATE);
			LAi_SetImmortal(CharacterFromID("Andre_Abel_Quest_Officer_1"), false);
			sTemp = "hol_guard";
			LAi_group_MoveCharacter(CharacterFromID("Andre_Abel_Quest_Officer_1"), sTemp);
			LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sTemp, LAI_GROUP_PLAYER, true);
			QuestSetCurrentNode("Henry Morgan", "Andre_Abel_Quest_Morgan_Dialog_16");
			LAi_Group_Attack(PChar, CharacterFromID("hol_guber"));
			AddQuestRecord("Andre_Abel_Quest", "16");
			AddQuestUserData("Andre_Abel_Quest", "sText", "К счастью, меня в очередной раз спасло умение хорошо фехтовать");
		break;

		case "Andre_Abel_Quest_Hol_Gov_Node_7":
			//pchar.questTemp.OrionCity = GetCityNameByIsland(Pchar.curIslandId);
			dialog.text = "Чиста твоя совесть или нет - это мы еще выясним... Увести "+ GetSexPhrase("его","ее") +"!";
			link.l1 = "Выясняйте, только не тяните. У меня мало времени...";
			link.l1.go = "Andre_Abel_Quest_Hol_Gov_Node_8";
		break;

		case "Andre_Abel_Quest_Hol_Gov_Node_8":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_LocationDisableOfficersGen("Villemstad_prison",true);
			LAi_LocationDisableOfficersGen("Villemstad_fort",true);
			LAi_LocationDisableOfficersGen("Villemstad_ExitTown",true);
			DoFunctionReloadToLocation("Villemstad_prison", "goto", "goto9", "Andre_Abel_Quest_In_Prison");
		break;

		case "Andre_Abel_Quest_Hol_Gov_Node_9":
			iSumm = sti(PChar.rank)*20000;
			dialog.text = "Договориться? Хм... ну, если речь идёт о сумме, скажем " + iSumm + " пиастров, то я готов продолжить диалог.";
			if(sti(PChar.money) >= iSumm)
			{
				link.l1 = "Отлично! Я же говорил"+ GetSexPhrase("","а") +", что это будет несложно.";
				link.l1.go = "Andre_Abel_Quest_Hol_Gov_Node_10";
			}
			link.l2 = "Что-о?! Да вы в своём уме?! За такие деньги я не то, что вашу охрану!.. я весь Кюрасао вырежу, вместе с портовыми лошадьми и обезьянами в джунглях!!!";
			link.l2.go = "Andre_Abel_Quest_Hol_Gov_Node_5";
		break;

		case "Andre_Abel_Quest_Hol_Gov_Node_10":
			iSumm = sti(PChar.rank)*20000;
			AddMoneyToCharacter(PChar, -iSumm);
			dialog.text = "Ну вот и великолепно. Можешь идти... Только не попадайся мне больше с подобными поручениями! Моё великодушие не бесконечно.";
			link.l1 = "Ну разумеется! Счастливо оставаться...";
			link.l1.go = "Andre_Abel_Quest_Hol_Gov_Node_11";
		break;

		case "Andre_Abel_Quest_Hol_Gov_Node_11":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			QuestSetCurrentNode("Henry Morgan", "Andre_Abel_Quest_Morgan_Dialog_16");
			AddQuestRecord("Andre_Abel_Quest", "16");
			AddQuestUserData("Andre_Abel_Quest", "sText", "К счастью, меня в очередной раз выручили деньги");
		break;
	}
}

void checkSoleyMatherial(ref Pchar, ref NPChar, int good1, int good2, int good3)
{
    int amount;

    amount = GetSquadronGoods(Pchar, good1) - sti(NPChar.Tuning.Matherial1);
    if (amount < 0)
    {
       amount = amount + sti(NPChar.Tuning.Matherial1);
    }
    else
    {
        amount = sti(NPChar.Tuning.Matherial1);
    }
    RemoveCharacterGoods(Pchar, good1, amount);
    NPChar.Tuning.Matherial1 = sti(NPChar.Tuning.Matherial1) - amount;

    amount = GetSquadronGoods(Pchar, good2) - sti(NPChar.Tuning.Matherial2);
    if (amount < 0)
    {
       amount = amount + sti(NPChar.Tuning.Matherial2);
    }
    else
    {
        amount = sti(NPChar.Tuning.Matherial2);
    }
    RemoveCharacterGoods(Pchar, good2, amount);
    NPChar.Tuning.Matherial2 = sti(NPChar.Tuning.Matherial2) - amount;


    amount = GetSquadronGoods(Pchar, good3) - sti(NPChar.Tuning.Matherial3);
    if (amount < 0)
    {
       amount = amount + sti(NPChar.Tuning.Matherial3);
    }
    else
    {
        amount = sti(NPChar.Tuning.Matherial3);
    }
    RemoveCharacterGoods(Pchar, good3, amount);
    NPChar.Tuning.Matherial3 = sti(NPChar.Tuning.Matherial3) - amount;

}
