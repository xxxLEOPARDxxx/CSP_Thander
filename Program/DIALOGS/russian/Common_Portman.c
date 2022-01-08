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

	// доп повека
	if (!CheckAttribute(NPChar, "Portman")) NPChar.Portman = 0;
	if (!CheckAttribute(NPChar, "PortManPrice")) NPChar.PortManPrice = (0.06 + frnd()*0.1);

	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\PortMan\" + NPChar.City + "_PortMan.c";
	if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	int i, cn;
	ref chref, compref;
	ref rRealShip;
	string attrL, sTitle, sCapitainId, s1;
	string sColony;

	String sLastSpeakDate = LastSpeakDate();

	// Warship 25.07.09 Генер "Сгоревшее судно". Даты отказа ГГ - если отказал, то предложит снова только на след сутки
	if(CheckAttribute(NPChar, "Quest.BurntShip.LastQuestDate") && NPChar.Quest.BurntShip.LastQuestDate != sLastSpeakDate)
	{
		DeleteAttribute(NPChar, "Quest.BurntShip");
	}
	bool ok, ok2;
	int iTest = FindColony(NPChar.City); // город магазина
	ref rColony;
	string sFrom_sea = "";
	npchar.quest.qty = CheckCapitainsList(npchar); //для списка кэпов

	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
		sFrom_sea = rColony.from_sea;
	}

	attrL = Dialog.CurrentNode;

	if(HasSubStr(attrL, "ShipStockManBack11_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 1;
		NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
		Dialog.CurrentNode = "ShipStockManBack";
	}

	if(HasSubStr(attrL, "ShipStockManBack22_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 0;
		NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
		Dialog.CurrentNode = "ShipStockManBack";
	}

	if(HasSubStr(attrL, "ShipStockManBack2_"))
	{
		i = findsubstr(attrL, "_" , 0);
		AddMoneyToCharacter(Pchar, -sti(NPChar.MoneyForShip));

		chref = GetCharacter(sti(NPChar.ShipToStoreIdx));//сторож

		DownCrewExp(chref,GetNpcQuestPastDayParam(chref, "ShipInStockMan.Date"));

        int iChar = GetPassenger(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); //выбранный пассажир
		compref = GetCharacter(iChar);

		DeleteAttribute(compref,"ship");//зачем-то стираем корабль офицера, хотя его там и не должно быть
		compref.ship = "";

		aref    arTo, arFrom;

		makearef(arTo, compref.ship);
		makearef(arFrom, chref.Ship);
		CopyAttributes(arTo, arFrom);

		// снимем пассажира -->
		CheckForReleaseOfficer(iChar);//увольнение офицера с должностей, если он не просто пассажир
		RemovePassenger(pchar, compref);
		// снимем пассажира <--
		SetCompanionIndex(pchar, -1, iChar);
		DelBakSkill(compref);
		DeleteAttribute(chref, "ShipInStockMan");
		chref.id = "ShipInStockMan";//сбрасываем индекс к стандартному, чтобы этот номер массива в следующий раз можно было занять
		DeleteAttribute(chref,"ship");//затираем данные корабля у сторожа
		chref.ship = "";
		LAi_SetCurHP(chref, 0.0);//ещё и убивать непися, чтоб точно очистился из массива?

		NPChar.Portman	= sti(NPChar.Portman) - 1;
		pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
		Dialog.CurrentNode = "exit";//закрываем диалог, ещё одно подтверждение уже не справшиваем
	}

	if(HasSubStr(attrL, "ShipStockMan11_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 1;
		NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); // индех в конце
		Dialog.CurrentNode = "ShipStock_Choose";
	}

	if(HasSubStr(attrL, "ShipStockMan22_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 0;
		NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); // индех в конце
		Dialog.CurrentNode = "ShipStock_Choose";
	}

	if(HasSubStr(attrL, "BurntShip19_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.Quest.BurntShip.ShipCompanionIndex = strcut(attrL, i + 1, strlen(attrL) - 1); // индех в конце
		Dialog.CurrentNode = "BurntShip19";
	}
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
	  			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase("В городе поднята тревога, тебя всюду ищут! На твоем месте я бы не стал здесь задерживаться.", "Вся городская стража рыщет по городу в поисках тебя. Я не идиот и разговаривать с тобой не буду!", "Беги, "+ GetSexPhrase("приятель","подруга") +", пока солдаты не сделали из тебя решето..."),
					LinkRandPhrase("Что тебе нужно, "+ GetSexPhrase("негодяй","мерзавка") +"?! Городская стража уже взяла твой след, далеко тебе не уйти"+ GetSexPhrase(", грязный пират","") +"!", "Грязн"+ GetSexPhrase("ый","ая") +" убийца, вон из моего дома! Стража!!", "Я не боюсь тебя, мерзав"+ GetSexPhrase("ец","ка") +"! Скоро тебя повесят в нашем форте, далеко тебе не уйти..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Хех, тревога для меня не проблема...", "Им меня ни за что не поймать."),
					RandPhraseSimple("Заткни свою пасть, " + GetWorkTypeOfMan(npchar, "") + ", а не то вырву твой поганый язык!", "Хех, " + GetWorkTypeOfMan(npchar, "") + ", а все туда же - пиратов ловить! Вот что я тебе скажу, приятель: сиди тихо и будешь жить..."));
				link.l1.go = "fight";
				break;
			}
			//homo
			//homo Линейка Блада
			if (Pchar.questTemp.CapBloodLine == true )
			{
				dialog.Text = LinkRandPhrase("Эй, доктор Блад! " + TimeGreeting() + ".",
									"Рад видеть Вас, Питер Блад.",
									"Хорошо, что Вы заглянули ко мне, " + GetFullName(pchar) + ". Как поживает полковник Бишоп?");
				Link.l1 = "Увы, я уже ухожу, " + NPChar.name + ". До встречи.";
				Link.l1.go = "exit";
				break;
			}
			//homo
			if(NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				dialog.text = "Приветствую вас, " + GetAddress_Form(NPChar) + ". Мы, кажется, не знакомы. Я "  + GetFullName(npchar)+ " - начальник порта.";
				Link.l1 = "Здравствуйте, " + GetFullName(NPChar) + ". Я " + GetFullName(PChar) + ", капитан корабля '" + PChar.ship.name + "'.";
			}
			else
			{
				dialog.text = LinkRandPhrase("Приветствую вас, " + GetAddress_Form(NPChar) + ". Вы ко мне по делу?",
									"Здравствуйте, " + GetFullName(Pchar) + ". Я видел, как ваш корабль вошел в порт, и был уверен, что вы ко мне зайдете.",
									"А, капитан " + GetFullName(Pchar) + ". Что привело вас ко мне?");
				Link.l1 = "Здравствуйте, " + GetFullName(NPChar) + ". Я хочу с вами поговорить.";
			}
			Link.l1.go = "node_2";
		break;
		case "node_2":
			// Церковный генератор 1
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.AskPortMan") && PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony == NPChar.city)
			{
				dialog.text = "Прекрасно. Я к вашим услугам, " + GetFullName(PChar) + ".";
				if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapFullInfo"))	// Получаем полную инфу
				{
					if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan"))
					{
						dialog.text = "Так, что там с деньгами? Вы принесли мне хотя бы 1000 пиастров?";
						if(sti(PChar.Money) >= 1000)
						{
							link.l1 = "Да, принес"+ GetSexPhrase("","ла") +". Вот ровно тысяча золотых. Теперь информация!";
							link.l1.go = "Church_GenQuest1_Node_FillFullInfo_3";
						}
						else
						{
							link.l1 = LinkRandPhrase("Нет, еще не принес"+ GetSexPhrase("","ла") +"...", "Еще нет...", "Еще не принес"+ GetSexPhrase("","ла") +", но скоро принесу...");
							link.l1.go = "exit";
						}
					}
					else
					{
						link.l1 = "Позвольте изложить вам суть вопроса. Я разминул"+ GetSexPhrase("ся","ась") +" со своим старым другом, капитаном " + PChar.GenQuest.ChurchQuest_1.CapFullName + ", всего на несколько часов, а у меня к нему срочное дело. Теперь придётся его догонять, но я, к сожалению, не осведомлен"+ GetSexPhrase("","а") +", в каком направлении он отбыл.";
						link.l1.go = "Church_GenQuest1_Node_FillFullInfo";
					}
				}
				else	// Полная инфа уже есть
				{
					link.l1 = "Господин начальник порта, мне нужна информация о судне '" + PChar.GenQuest.ChurchQuest_1.CapShipName + "', капитана " + PChar.GenQuest.ChurchQuest_1.CapFullName + ".";
					if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NextColonyIsLast")) // Он здесь, в этой колонии!
						link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_1";
					else // Отправляет в рандомную колонию
						link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_1";
				}
				break;
			}

			dialog.text = "Прекрасно. Я к вашим услугам, " + GetFullName(PChar) + ".";
			if(NPChar.city != "Pirates")
			{
				Link.l2 = "Здесь можно подыскать работу? Или контракт?";
				Link.l2.go = "node_4";
				Link.l13 = LinkRandPhrase("К вам наверняка обращаются купцы, подыскивающие сопровождение для своих кораблей. Нет ли таких сегодня?","Нет ли у вас на примете пассажиров, желающих добраться до другой колонии?","У меня отличный корабль, и я хочу подзаработать эскортом купцов или доставкой пассажиров. Нет ли у вас таких?"));
				Link.l13.go = "work_PU";
			}
				Link.l3 = "Могу я оставить один из своих кораблей на время?";
				Link.l3.go = "ShipStock_1";

			if (sti(NPChar.Portman) > 0)
			{
				Link.l4 = "Я хочу забрать свой корабль обратно.";
				Link.l4.go = "ShipStockReturn_1";
			}
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l5 = "Я к вам по финансовым делам.";
				link.l5.go = "LoanForAll";//(перессылка в кредитный генератор)
			}
 			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("Я здесь по поручению одного человека. Его зовут губернатор " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".",
					GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " прислал меня к вам. Я долж"+ GetSexPhrase("ен","на") +" кое-что забрать...");
				link.l7.go = "IntelligenceForAll";
			}
			link.l6 = "Меня интересуют капитаны, которые отмечались в вашем портовом управлении.";
			link.l6.go = "CapitainList";
			if (bBribeSoldiers ==true && GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
				if (!CheckNationLicence(sti(npchar.nation)))
				{
					link.l77 = "У вас случаем нет торговой лицензии, на короткий срок? Может осталась от какого-нибудь капитана? ";
					link.l77.go = "BuyLicense";
				}
				}
			//ОЗГ
			if(CheckAttribute(pchar, "questTemp.Headhunter"))
			{
				if (pchar.questTemp.Headhunter == "Houm" && npchar.nation == ENGLAND)
				{
					link.l12 = "Не подскажете, не останавливался ли у вас корабль 'Мертвая голова' с капитаном Ганнибалом Холмом?";
					link.l12.go = "Houm_portman_1";
				}
			}

			link.l8 = "Я по другому вопросу.";
			// Warship 26.07.09 Генер "Сгоревшее судно"
			if(CheckAttribute(NPChar, "Quest.BurntShip") && !CheckAttribute(NPChar, "Quest.BurntShip.LastQuestDate"))
			{
				if(CheckAttribute(NPChar, "Quest.BurntShip.TimeIsOver")) // Просрочено
				{
					link.l8.go = "BurntShip10";
				}
				else
				{
					if(CheckAttribute(NPChar, "Quest.BurntShip.TwoDaysWait"))
					{
						if(GetNpcQuestPastDayParam(NPChar, "Quest.BurntShip.TwoDaysWait") >= 2)
						{
							link.l8.go = "BurntShip17";
						}
						else
						{
							link.l8.go = "quests";
						}
					}
					else
					{
						link.l8.go = "BurntShip12";
					}
				}
			}
			else
			{
				link.l8.go = "quests";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "portman_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l9 = "Здравствуйте, я приш"+ GetSexPhrase("ел","ла") +" по приглашению вашего сына.";
					link.l9.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "portman_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "Я по поводу вашей дочери ...";
						link.l9.go = "EncGirl_1";
					}
				}
			}
			if (CheckCharacterItem(pchar, "CaptainBook"))
			{
				if(pchar.questTemp.different == "free")
				{
					link.l10 = "Я по случайности наш"+ GetSexPhrase("ел","ла") +" вот этот пакет судовых документов.";
					link.l10.go = "ShipLetters_out1";
				}
				else
				{
					if(pchar.questTemp.different.GiveShipLetters.city == npchar.city)
					{
						link.l10 = "Я по случайности наш"+ GetSexPhrase("ел","ла") +" вот этот, наверняка кем-то позабытый, пакет судовых документов.";
						if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakPortman"))
						{
							link.l10.go = "ShipLetters_Portman1_1";
						}
						else
						{
							link.l10.go = "ShipLetters_Portman2";
						}
					}
				}
			}
			if (CheckAttribute(pchar,"Whisper.ActiveChardQuest") && !CheckAttribute(pchar,"Whisper.PortmanAtSea") && GetNpcQuestPastDayWOInit(npchar, "Whisper.LastSeenPortman") > 7 && GetNpcQuestPastDayWOInit(pchar, "Whisper.LastSeenPortman") > 7)
			{
				Link.l11 = "Я ищу капитана по имени Ральф Портман. У вас в журнале такой не отмечался?";
				Link.l11.go = "Whisper_chard_quest";
			}

			Link.l15 = "Благодарю. До свидания.";
			Link.l15.go = "exit";
		break;

		case "Whisper_chard_quest":
			SaveCurrentNpcQuestDateParam(npchar,"Whisper.LastSeenPortman");
			if (!CheckAttribute(pchar,"Whisper.PortmanTries"))
			{
				pchar.Whisper.PortmanTries = 0;
			}
			pchar.Whisper.PortmanTries = sti(pchar.Whisper.PortmanTries)+1;
			if (npchar.nation != HOLLAND && npchar.nation != SPAIN)
			{
				if (sti(pchar.Whisper.PortmanTries) > 2)
				{
					WhisperSpawnPortman(npchar);
					SaveCurrentNpcQuestDateParam(pchar,"Whisper.LastSeenPortman");
					//SaveCurrentQuestDateParam("Whisper.LastSeenPortman");
					dialog.text = "Был такой. Он только недавно покинул порт. Кажется, отправился в колонию "+XI_ConvertString("Colony" + pchar.Whisper.PortmanTargetCity)+". Если поторопитесь, может, ещё успеете его догнать.";
					link.l1 = "Благодарю, я пойду. До свидания.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Хм... Нет, такой у меня пока не отмечался.";
					link.l1 = "Благодарю за информацию, я пойду. До свидания.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Кто? Если это англичанин, то вряд ли. Мы их пускаем в порт только в исключительных случаях.";
				link.l1 = "Спасибо и на том, я пойду. До свидания.";
				link.l1.go = "exit";
			}
		break;

		case "Church_GenQuest1_Node_FillFullInfo":
			dialog.text = "Ваша проблема легко разрешима. Вы можете обратиться к любому чиновнику службы навигации, и получить всю имеющуюся информацию о маршруте судна вашего друга.";
			link.l1 = "К сожалению, не всё так просто. Именно в вашем порту мой друг сменил название судна... из религиозных побуждений.";
			link.l1.go = "Church_GenQuest1_Node_FillFullInfo_2";
		break;

		case "Church_GenQuest1_Node_FillFullInfo_2":
			dialog.text = "Так. Это уже сложнее. Мне нужно поднять записи в судовом реестре, это потребует времени. А в наши дни, как известно, время - деньги...";
			if(sti(pchar.money) >= 1000)
			{
				link.l1 = "Я это прекрасно понимаю, г-н " + GetFullName(NPChar) + ", и готов"+ GetSexPhrase("","а") +" достойно оценить ваше время... в размере, скажем, 1000 золотых.";
				link.l1.go = "Church_GenQuest1_Node_FillFullInfo_3";
			}
			else
			{
				DeleteAttribute(pchar, "GenQuest.ChurchQuest_1.CurPortManColony"); // Можно будет спросить.
				link.l1 = "М-да... А денег-то у меня и нету... Вернусь позже...";
				link.l1.go = "exit";
			}
		break;

		case "Church_GenQuest1_Node_FillFullInfo_3":
			sColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			PChar.GenQuest.ChurchQuest_1.CapGoToColony = sColony;
			if(CheckAttribute(pchar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan"))
			{
				dialog.text = "Отлично! Сейчас посмотрим, что там у нас... минуту... так... вот, пожалуйста. В судовом реестре отмечено переименование, и судно, называемое отныне '" + PChar.GenQuest.ChurchQuest_1.CapShipName + "' под управлением капитана " + PChar.GenQuest.ChurchQuest_1.CapFullName + " отправилось сегодня в сторону " + XI_ConvertString("Colony" + sColony + "Gen") + ".";
				DeleteAttribute(pchar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan");
			}
			else
				dialog.text = "О-о-о!... То есть, да, вы оценили по достоинству, так как я очень, очень занятой человек. Минуту... так... вот, пожалуйста. В судовом реестре отмечено переименование. Судно, называемое отныне '" + PChar.GenQuest.ChurchQuest_1.CapShipName + "' под управлением капитана " + PChar.GenQuest.ChurchQuest_1.CapFullName + " отбыло сегодня в сторону " + XI_ConvertString("Colony" + sColony + "Gen") + ".";
				link.l1 = "Благодарю вас, сударь, вы оказали мне действительно большую услугу.";
				link.l1.go = "Church_GenQuest1_Node_FillFullInfo_4";
				AddMoneyToCharacter(pchar, -1000);
		break;

		case "Church_GenQuest1_Node_FillFullInfo_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("ен","на"));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Gen"));
			AddQuestUserData(sQuestTitle, "sShipName", PChar.GenQuest.ChurchQuest_1.CapShipName);
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = PChar.GenQuest.ChurchQuest_1.CapGoToColony;
			PChar.GenQuest.ChurchQuest_1.CapFullInfo = true;
		break;

		case "Church_GenQuest1_Node_FillInfoOfCapColony_1":
			dialog.text = "Что именно вы хотите узнать?";
			link.l1 = "Скажите, не заходило ли судно этого капитана в ваш порт?";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_2";
		break;

		case "Church_GenQuest1_Node_FillInfoOfCapColony_2":
			PChar.GenQuest.ChurchQuest_1.CapGoToColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			dialog.text = "Хм... Позвольте узнать, с какой целью вы его разыскиваете?";
			link.l1 = "У меня к нему дело. Если он не был в вашем порту или вы не...";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_3";
		break;

		case "Church_GenQuest1_Node_FillInfoOfCapColony_3":
			dialog.text = "Он был. Но - слава Святым Угодникам - не далее как сегодня утром, наконец милосердно избавил нас, грешных, от своего общества и направился в " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Acc") + ". И мне, признаться, искренне жаль любого, кому предстоит иметь с ним дело.";
			link.l1 = "В таком случае пожелайте мне удачи, и благодарю за помощь.";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_4";
		break;

		case "Church_GenQuest1_Node_FillInfoOfCapColony_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "5");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Dat"));
			AddQuestUserData(sQuestTitle, "sName", PChar.GenQuest.ChurchQuest_1.CapFullName);
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = PChar.GenQuest.ChurchQuest_1.CapGoToColony; // Спрашиваем портмана в колонии, куда отправился кэп.
			if(rand(2) == 1)
			{
				Log_TestInfo("Следующая колония - последняя");
				PChar.GenQuest.ChurchQuest_1.NextColonyIsLast = true; // Флаг - следующая колония будет последней
			}
		break;

		case "Church_GenQuest1_Node_CapOnThisColony_1":
			dialog.text = "Что именно вас интересует, госпо"+ GetSexPhrase("дин","жа") +" " + GetFullName(PChar) + "?";
			link.l1 = "Скажите, не заходил ли в ваш порт этот капитан?";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_2";
		break;

		case "Church_GenQuest1_Node_CapOnThisColony_2":
			dialog.text = "Хм, заходил... Так зашёл, что я с нетерпением ожидаю, когда он покинет мой многострадальный порт.";
			link.l1 = "То есть, это судно всё ещё находится здесь?";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_3";
		break;

		case "Church_GenQuest1_Node_CapOnThisColony_3":
			dialog.text = "Да, милостив"+ GetSexPhrase("ый господин","ая госпожа") +". Весь порт, от последнего грузчика до главы лоцманской службы, молится о его скорейшем благополучном отбытии. Судно только что вышло из сухого дока, где получило необходимый ремонт, а его доблестный капитан успел перессориться с каждым плотником, и забраковать три партии отборных досок для наружной обшивки. Но уже завтра всевидящий и всеблагой Господь избавит нас от этой... от этой чумы, от этой язвы в человеческом обличии!";
			link.l1 = "Успокойтесь, господин " + NPChar.Name + ", и подумайте о том, что кому-то сейчас придётся тяжелее, чем вам. Вы уже прошли через это испытание, а мне только предстоит встретиться с этим капитаном... Позвольте откланяться.";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_4";
		break;

		case "Church_GenQuest1_Node_CapOnThisColony_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "6");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
//			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithSailors = true; // Спрашиваем моряков
			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithCap = true; // Говорим с капитаном
//			SetFunctionLocationCondition("Church_GenQuest1_ChangeCapitanLocation", "Deck_Near_Ship", true);
			PChar.GenQuest.ChurchQuest_1.CurPortManColony = NPChar.city;
			Group_SetAddress("ChurchGenQuest1_CapGroup", colonies[FindColony(NPChar.City)].Island, "IslandShips1", "Ship_1"); // Ставим кэпа в порту колонии
			Characters[GetCharacterIndex("ChurchGenQuest1_Cap")].Nation = sti(NPChar.Nation); // Сменим нацию, чтоб вражды не было
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.AskPortMan"); // Больше не спрашиваем
//			if(rand(1) == 0) PChar.GenQuest.ChurchQuest_1.CapWaitOnTavern = true;
			sld = CharacterFromID("ChurchGenQuest1_Cap");
			sld.DeckDialogNode = "ChurchGenQuest_1_DeckDialog_1";
		break;

		case "ShipLetters_out1":
			dialog.text = "Дайте-ка взглянуть! Да, в моих документах этот комплект значится недействительным. Вы весьма добры, раз нашли время заглянуть ко мне и передать бумаги. Попутного ветра, капитан!";
			link.l1 = "Благодарю!";
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "CaptainBook");
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер
			AddQuestRecord("GiveShipLetters", "10");
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "ShipLetters_Portman1_1":
			pchar.questTemp.different.GiveShipLetters.speakPortman = true;
			s1 = "Дайте-ка взглянуть! Да, в моих документах значатся и это судно, и его владелец. ";
			s1 = s1 + "Ваша сознательность, капитан, делает Вам честь! Разумеется, Ваши труды должны быть вознаграждены. ";
			dialog.text = s1 + "Скажем, " + sti(pchar.questTemp.different.GiveShipLetters.price1) + " золотых Вы сочтете достойной оплатой?";
			link.l1 = "Разумеется нет!";
			link.l1.go = "exit";
			link.l2 = "Что же, весьма скромная сумма, но и услуга не велика. Да, я принимаю Ваше предложение, "  + npchar.name +" .";
			link.l2.go = "ShipLetters_Portman1_2";
		break;

		case "ShipLetters_Portman1_2" :
			TakeItemFromCharacter(pchar, "CaptainBook");
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price1));
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер
			AddQuestRecord("GiveShipLetters", "5");
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "ShipLetters_Portman2":
			dialog.text = "Вы согласны принять мое предложение?";
			link.l1 = "Разумеется, нет!";
			link.l1.go = "exit";
			link.l2 = "Пожалуй. Хотя уверен"+ GetSexPhrase("","а") +", что эти бумаги стоят дороже.";
			link.l2.go = "ShipLetters_Portman2_1";
		break;

		case "ShipLetters_Portman2_1":
			TakeItemFromCharacter(pchar, "CaptainBook");
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price1));
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер
			AddQuestRecord("GiveShipLetters", "6");
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "EncGirl_1":
			dialog.text = "Слушаю вас внимательно.";
			link.l1 = "Я привел"+ GetSexPhrase("","а") +" вашу беглянку.";
			link.l1.go = "EncGirl_2";
		break;

		case "EncGirl_2":
			dialog.text = "Ах, капитан, спасибо вам большое! Как она? здорова, не пострадала? Уж скоро сутки, как убежала, негодница. Разве ж я ей плохого желаю? Замуж отдать собрался... Жених богатый, молодой, а что собою не пригож, так ведь с лица воду не пить. Нет! она всё по-своему норовит - вся в мать, чтоб её...\nХотя, и она бы на свет не появилась, если бы её мамаша в своё время не сбежала с одним предприимчивым оболтусом... ну да что вспоминать... Молодость наивна, глупа... и жестока.";
			link.l1 = "Конечно, вы отец и решать вам, но я бы не торопил"+ GetSexPhrase("ся","ась") +" со свадьбой...";
			link.l1.go = "EncGirl_3";
		break;

		case "EncGirl_3":
			dialog.text = "Да что вы понимаете?.. У вас свои дети есть? Нету? Вот, когда будут - заходите, тогда и поговорим...\nДа... я обещал вознаграждение тому, кто её вернёт - примите, пожалуйста.";
			link.l1 = "Спасибо. И держите её покрепче. Что-то мне подсказывает, что она на этом не остановится.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;

		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "А, так вы и есть т"+ GetSexPhrase("от капитан, который привёз","а девушка, которая привезла") +" моего блудного сына с молодой невестой?";
				link.l1 = "Да, это я помог"+ GetSexPhrase("","ла") +" им сбежать.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "А-а, явил"+ GetSexPhrase("ся, благодетель","ась, благодетельница") +". Небось награды ждёшь?";
				link.l1 = "Ну, не то, чтобы награды, но благодарность услышать не мешало бы.";
				link.l1.go = "EncGirl_6";
			}
		break;

		case "EncGirl_5":
			dialog.text = "Я очень вам благодарен, что не оставили моё чадо в затруднительном положении и помогли ему с честью выйти из столь щекотливой ситуации. Разрешите отблагодарить вас, как могу. Примите эту скромную сумму и подарок от меня лично.";
			link.l1 = "Благодарю вас, мне было приятно помогать этим молодым людям.";
			link.l1.go = "EncGirl_5_1";
		break;

		case "EncGirl_6":
			dialog.text = "Какая благодарность?! за что благодарность?! Мало того, что этот оболтус уже полгода слоняется без работы, так ещё и любезничать время нашёл! Да я в его годы уже своё дело держал. А он, ишь, разохотился! У губернатора, вон, дочка на выданье, а этот приволок какую-то шалаву безродную, прости Господи, и благословения родительского испрашивает!";
			link.l1 = "Хм, значит вы не верите в искренние чувства?";
			link.l1.go = "EncGirl_6_1";
		break;

		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "EncGirl_6_1":
			dialog.text = "Какие такие чувства?! О каких чувствах вы говорите? Взрослый, вроде человек, а туда же... чувства! Стыдно вам должно быть молодёжи в таких делах потакать, да в сводни подряжаться. Девчонку из родительского гнезда вырвали и моему молокососу жизнь сломали. Не будет вам никакой благодарности. Прощайте.";
			link.l1 = "Что ж, и вам не хворать...";
			link.l1.go = "EncGirl_6_2";
		break;

		case "EncGirl_6_2":
			ChangeCharacterReputation(pchar, -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("ел","ла"));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("","а"));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "node_4":
			//--> проверка миниквестов начальника порта.
			if (npchar.quest == "PortmansJornal") //взят квест на судовой журнал
			{
				dialog.text = "Вы должны были найти капитана по имени " + npchar.quest.PortmansJornal.capName + " и вернуть ему судовой журнал. Вы сделали это?";
				link.l1 = "Нет, не получилось пока...";
				link.l1.go = "PortmanQuest_NF";
				break;
			}
			if (npchar.quest == "PortmansSeekShip" || npchar.quest == "SeekShip_sink") //взят квест на поиски украденного корабля
			{
				dialog.text = "Вы подвязались разыскать украденный " + GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName)) + " '" + npchar.quest.PortmansSeekShip.shipName + "'. Пока вы не выполните это задание, ни о какие других поручениях не может быть и речи.";
				link.l1 = "Я продолжу поиски, ждите.";
				link.l1.go = "exit";
				link.l2 = "Хочу отказаться от выполнения вашего поручения.";
				link.l2.go = "SeekShip_break";
				break;
			}
			if (npchar.quest == "SeekShip_success") //украденный корабль взят на абордаж
			{
				dialog.text = "Вы обещали мне разыскать украденный " + GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName)) + " '" + npchar.quest.PortmansSeekShip.shipName + "'. Вы сделали это?";
				bool bOk = false;
				for (i=0; i<=COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(pchar, i);
					if(cn != -1)
					{
						sld = &characters[cn];
						if (sld.ship.name == npchar.quest.PortmansSeekShip.shipName &&
							RealShips[sti(sld.ship.type)].BaseName == npchar.quest.PortmansSeekShip.shipTapeName &&
							RealShips[sti(sld.Ship.Type)].basetype == npchar.quest.PortmansSeekShip.shipTape)
						{
							if (i == 0)
							{	//если нужный корабль - у ГГ
								sld.Ship.Type = GenerateShip(SHIP_TARTANE, true);
								SetBaseShipData(sld);
								SetCrewQuantityFull(sld);
							}
							else
							{
								RemoveCharacterCompanion(pchar, sld);
								AddPassenger(pchar, sld, false);
							}
							bOk = true;
						}
					}
				}
				if (bOk)
				{
					link.l1 = "Да, я наш"+ GetSexPhrase("ел","ла") +" его, стоит в порту на рейде. Можете забирать.";
					link.l1.go = "SeekShip_good";
				}
				else
				{
					link.l1 = "Я продолжу поиски, ждите.";
					link.l1.go = "exit";
				}
				link.l2 = "Хочу отказаться от выполнения вашего поручения.";
				link.l2.go = "SeekShip_break";
				break;
			}
			//<-- проверка миниквестов начальника порта.

			//--> дача миниквестов начальника порта.
			if (rand(2) < 2 && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "quest.meeting") > 7)
			{
				dialog.text = LinkRandPhrase("Да, черт возьми! У меня есть для вас работа!",
					"Ха! Вы как нельзя вовремя! У меня есть одна проблема, требующая разрешения.",
					"Еще бы! Конечно, у меня есть работа! Проблемы, знаете ли, просто задавили...");
				link.l1 = "Излагайте суть дела, " + GetAddress_FormToNPC(NPChar) + ".";
				link.l1.go = "PortmanQuest";
				SaveCurrentNpcQuestDateParam(npchar, "quest.meeting");
				break;
			}

			// Warship 25.07.09 Генер "Сгоревшее судно"
			if(dRand(4) == 2 && !CheckAttribute(NPChar, "Quest.BurntShip"))
			{
				dialog.text = "Боже! Капитан " + GetFullName(PChar) + ", вы как нельзя вовремя! Приключилось такое несчастье, такое несчастье... У нас на рейде сгорело судно, оставленное на попечение портового управления! По недосмотру охранной команды сгорело... по самую ватерлинию...\n" +
					"Господи, за что же мне такое наказание-то? Ведь столько лет верой и правдой...";
				link.l1 = "Хм, эка невидаль - судно сгорело. А страховые договора на что? Или вы его не застраховали?.. в целях экономии, так сказать. А теперь рады бы локоток укусить, да...";
				link.l1.go = "BurntShip4";
				link.l2 = "С такими вопросами вам за помощью на верфь нужно, а не ко мне. За пару месяцев вам хоть старое восстановят, хоть новое соорудят. Я не судостроитель"+ GetSexPhrase("","ница") +", так что извините, не по адресу...";
				link.l2.go = "BurntShip2";
				break;
			}
			//<-- дача миниквестов начальника порта.

			dialog.text = "Губернатор радеет за благополучие города - у него всегда есть работа. Потом, в таверне могут быть заинтересованные купцы, ну и магазин иногда фрахтует капитанов.";
			Link.l1 = "Еще один вопрос.";
			Link.l1.go = "node_2";
			Link.l2 = "Благодарю. До свидания.";
			Link.l2.go = "exit";
		break;


		/////////////////////////////////////////////////////////==========================/////////////////////////////////////////////////////
		//эскорт-пассажиры
		case "work_PU":
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
		{
			if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
				dialog.text = RandPhraseSimple("Здесь нет работы для тех, кто ходи под флагом " + NationNameGenitive(sti(pchar.nation)) + "! Покиньте мой кабинет немедленно!", "Я не намерен сотрудничать с " + NationNameAblative(sti(pchar.nation)) + ". Вон отсюда!");
				link.l1 = RandPhraseSimple("Хм, ваше право...", "Ну, как знаешь...");
				link.l1.go = "exit";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				dialog.text = RandPhraseSimple("У меня в журнале целый список пассажиров, которые ждут попутных судов. Но боюсь, среди них не найдётся идиота, который бы согласился путешествовать под вашим началом. Репутация, знаете ли, штука тонкая, а дурная слава на Карибах разлетается, как волны в пруду...", "Ко мне постоянно обращаются торговцы, которым нужен эскорт. Но эскорт предполагает защиту, а не опасность быть ограбленным своим же конвоем. Учитывая дурную славу, которая ходит за вами по пятам, ни один торговец так рисковать не станет.");
				link.l1 = LinkRandPhrase("Чего-о?! Да врут всё люди.", "Неужто все меня боятся?! Да, видать, есть за что.", "Что за народец нынче пошёл! Плюнуть не в кого - сразу жаловаться бегут!");
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Ко мне со всей колонии поступают заявки от купцов, и пассажиров, которые просят подыскать сопровождение или попутные суда в разные концы архипелага. Если ищете что-то конкретно, то можно будет посмотреть.";
			link.l1 = "С радостью возьмусь за эскорт, если по пути будет.";
			link.l1.go = "work_PU_1";
			link.l2 = "Пассажиров много? У меня как раз есть свободные каюты.";
			link.l2.go = "work_PU_2";
		}
		else
		{
			dialog.text = "А корабль твой где? Ты что - на собственном горбу пассажиров возить собрал"+ GetSexPhrase("ся","ась") +"?";
			link.l1 = "Хм, и то верно...";
			link.l1.go = "exit";
		}
		break;

		case "work_PU_1":
			if (!CheckAttribute(npchar, "work_date_PU") || GetNpcQuestPastDayParam(npchar, "work_date_PU") >= 2 || bBettaTestMode)
			{
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5 || makeint(7-sti(RealShips[sti(Pchar.Ship.Type)].Class)) < 1)//при низком авторитете и на 7 класс не даем
				{
				dialog.text = "Извините, но желающих отправиться в путь вместе с вами у меня нет.";
				link.l1 = "Понятно. Как скажете.";
				link.l1.go = "exit";
				break;
				}
				//конвой
				if (!CheckQuestAttribute("generate_convoy_quest_progress", "begin"))
				{
					if (GetCompanionQuantity(PChar) == COMPANION_MAX)
					{
						dialog.text = "Но для эскорта ваша эскадра великовата. Не пойдут торговцы в такой караван, который сам по себе может привлечь нежелательное внимание.";
						link.l1 = "Верно, не подумал"+ GetSexPhrase("","а") +". Ладно, зайду позже, если настроение будет.";
						link.l1.go = "exit";
					}
					else
					{
						if (drand(6) > 1)
						{
							dialog.text = "Не знаю, будет ли по пути, но один купец, что искал сопровождение, только что у меня был... А-а-а, вот как раз и он вернулся!";
							link.l1 = RandPhraseSimple("Вы его хорошо знаете? Состоятельный господин или проходимец какой?", "А кто он такой? С ним стоит иметь дела?");
							link.l1.go = "ConvoyAreYouSure_PU";

						}
						else
						{
									dialog.text = "Обычно у меня много торговцев, которым нужно сопровождение, но сейчас, как назло, никого нет. Может быть, в другой день вам повезет больше.";
							link.l1 = RandPhraseSimple("Ладно, на нет и суда нет.", "Да, не свезло... Ну ладно, прощай.");
							link.l1.go = "exit";
						}
					}
			  	}
				else
				{
					dialog.text = "Но у вас уже есть сопровождаемый. В случае нападения вам не защитить несколько судов одновременно - придётся кем-то жертвовать. Ни один торговец на это не пойдёт. Так что сначала завершите начатое, потом уж подходите.";
					link.l1 = RandPhraseSimple("Экие нынче торговцы трусоватые пошли. А пришлось бы им в одиночку, да через Атлантику... Ну, да ладно, прощайте.", "Вот незадача... Ну ладно, всего хорошего.");
					link.l1.go = "exit";
					}
				}
				else
				{
				dialog.text = "Сегодня уже никого нет. Заходите через пару дней.";
					link.l1 = "Хорошо. Как скажете.";
								link.l1.go = "exit";
				}
		break;

		case "work_PU_2":
			if (!CheckAttribute(npchar, "work_date_PU") || GetNpcQuestPastDayParam(npchar, "work_date_PU") >= 2 || bBettaTestMode)
			{
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5 || makeint(7-sti(RealShips[sti(Pchar.Ship.Type)].Class)) < 1)//при низком авторитете и на 7 класс не даем
				{
				dialog.text = "Извините, но желающих отправиться в путь вместе с вами у меня нет.";
				link.l1 = "Понятно. Как скажете.";
				link.l1.go = "exit";
				break;
				}
				 // пассажир
				if (drand(6) > 1)
				{
					dialog.Text = "Много - не много, а один тип сегодня уже несколько раз заходил, попутное судно искал. Да вот и он опять!";
					link.l1 = RandPhraseSimple("Как вы думаешь, стоит его на борт брать?", "А что за человек? Стоит с ним дело иметь?");
					Link.l1.go = "PassangerAreYouSure_PU";
				}
				else
				{
					dialog.text = "К сожалению, пассажиров сегодня нет. Так что не обессудьте...";
					link.l1 = RandPhraseSimple("Ну нет, так нет. Чего уж тут...", "Да, не свезло... Ну ладно, прощайте.");
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Сегодня уже никого нет. Заходите через пару дней.";
				link.l1 = "Хорошо. Как скажете.";
				link.l1.go = "exit";
			}
		break;

		case "ConvoyAreYouSure_PU":
			dialog.text = RandPhraseSimple("Да вполне солидный господин. А по цене - это уж вы как-нибудь сами сговоритесь, тут я вам не помощник.", "Да Бог с вами, я кого попало не посоветую. Лишь бы в цене сошлись.");
			Link.l1 = "Ясно. Сейчас выясним, куда ему нужно.";
			Link.l1.go = "exit";
			pchar.quest.destination = findTraderCity_PU(npchar);
			pchar.ConvoyQuest.City = npchar.city;
			AddDialogExitQuest("prepare_for_convoy_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date_PU");
		break;

		case "PassangerAreYouSure_PU":
			dialog.text = RandPhraseSimple("Да вполне нормальный пассажир.", "Почему бы нет? Вполне состоятельный господин.");
			Link.l1 = "Спасибо, сейчас и переговорю.";
			Link.l1.go = "exit";
			sGlobalTemp = findPassangerCity_PU(npchar);
			pchar.GenQuest.GetPassenger_City = npchar.city;
			AddDialogExitQuest("prepare_for_passenger_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date_PU");
		break;


		case "PortmanQuest_NF":
			dialog.text = "Хм, это плохо. В таком случае, ни о какой новой работе у меня не может быть и речи.";
			link.l1 = "Понятно. Вот еще что хотел"+ GetSexPhrase("","а") +" сказать...";
			link.l1.go = "node_2";
		break;

		// Warship 25.07.09 Генер "Сгоревшее судно"
		/*case "BurntShip1":
			dialog.text = "Вы правы, капитан, но тут дело такое, что и надежды-то на помощь мало... У нас на рейде сгорело судно, оставленное на попечение портового управления! По недосмотру охранной команды сгорело... по самую ватерлинию\n" +
				"Господи, за что же мне такое наказание-то? Ведь столько лет верой и правдой...";
			link.l1 = "Так, милейший, давайте всё по порядку, иначе мы ни о чём не договоримся.";
			link.l1.go = "BurntShip3";
			link.l2 = "С такими вопросами вам за помощью на верфь нужно, а не ко мне. За пару месяцев вам хоть старое восстановят, хоть новое соорудят. Я не судостроитель"+ GetSexPhrase("","ница") +", так что извините, не по адресу...";
			link.l2.go = "BurntShip2";
		break;*/

		case "BurntShip2":
			dialog.text = "Очень жаль, капитан... очень жаль, что вы не хотите мне помочь.";
			link.l1 = "Тут не в желании дело, уважаемый. Вы же сами понимаете... До свидания...";
			link.l1.go = "exit";
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
		break;

		/*case "BurntShip3":
			dialog.text = "Да, да, капитан. В общем, несчастье страшное... За всю мою долгую карьеру ничего подобного не случалось. Нас может спасти только Провидение и ваша добрая воля.";
			link.l1 = "Хм, эка невидаль - судно сгорело. А страховые договора на что? Или вы его не застраховали?.. в целях экономии, так сказать. А теперь рады бы локоток укусить, да...";
			link.l1.go = "BurntShip4";
		break;*/

		case "BurntShip4":
			dialog.text = "Да что вы, капитан?! Побойтесь Бога!.. Как можно?! Я своё дело твёрдо знаю, чай столько лет служу. И страховые договора есть, и страховая контора выплату готова произвести, и сумма страховая немалая, уверяю вас.";
			link.l1 = "Уважаемый, так в чём же ваша проблема? От пожара взорвалась крюйт-камера, и пострадали люди, а  вас привлекают к суду за халатность?";
			link.l1.go = "BurntShip5";
		break;

		case "BurntShip5":
			sCapitainId = GenerateRandomName(sti(NPChar.nation), "man");

			dialog.text = "Ну уж чего не было, того не было, - Господь миловал, иначе бы не сносить мне головы. Пустёхонек трюм был, как есть пуст был, слава тебе Господи, Пресвятая Дева Мария!\n" +
				"А вся проблема в том, что судно-то принадлежит... вернее принадлежало, известному на все Карибы господину " + sCapitainId + ". И строилось оно в Европе по спецзаказу, с неординарными характеристиками. " +
				"И этим судном владелец очень гордился и хвастался где ни попадя, болван эдакий, прости Господи... Что я теперь ему скажу? Хоть в петлю лезь, ей-богу...";
			link.l1 = "О-о, вижу, вы здорово влипли. А что у него не так было, как у всех судов? То есть, чем в своём кораблике этот господин так гордился?";
			link.l1.go = "BurntShip6";

			NPChar.Quest.BurntShip.ShipOwnerName = sCapitainId;
		break;

		case "BurntShip6":
			BurntShipQuest_FillStartParams(NPChar);

			attrL = NPChar.Quest.BurntShip.ShipAttribute;
			iTest = sti(NPChar.Quest.BurntShip.ShipType);

			switch(attrL)
			{
				case "speedrate":
					attrL = "У его " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Acc")) + " скорость по ветру была более " + NPChar.Quest.BurntShip.ShipNeededValue + " узлов. Для капера это первейшая гордость была... Он просто велит своим молодчикам повесить меня на рее! Чёрт принёс его в нашу гавань вместе с его пиратской лоханкой...";
				break;

				case "turnrate":
					attrL = "У его " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Acc")) + " манёвренность была более " + NPChar.Quest.BurntShip.ShipNeededValue + " единиц. Это для вояки первейшая гордость была... Он велит засечь меня шпицрутенами! Чёрт его надоумил оставить у меня свою посудину...";
				break;

				case "capacity":
					attrL = "У его " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Acc")) + " дедвейт был более " + NPChar.Quest.BurntShip.ShipNeededValue + " единиц водоизмещения. Для купца это первейшая гордость была... Он меня без суда четвертует. Чёрт его дёрнул именно у меня своё корыто оставить!";
				break;
			}

			dialog.text = attrL;
			link.l1 = "А что на верфи говорят? Неужели здесь такое соорудить невозможно?";
			link.l1.go = "BurntShip7";
		break;

		case "BurntShip7":
			dialog.text = "Никто не берётся. Я уж и на соседний остров ходил с поклоном. Говорят, что на Бермудах мастер есть знатный. Но где мы, - а где Бермуды. Осталось только на помощь таких свободных капитанов, как вы рассчитывать. Ведь вы топите эти лоханки десятками. Может вам не составит труда подыскать подобное судёнышко для меня. А мы его здесь подкрасим, подправим, чтоб хозяин не в претензии был\n" +
				"Я щедро отблагодарю, и страховая компания не поскупится. Дело-то неординарное, сами понимаете. Кому охота в немилость к такому влиятельному господину попасть?";
			link.l1 = "Да, дело не простое. А сколько у меня есть времени?";
			link.l1.go = "BurntShip8";
			link.l2 = "Нет, милейший, не возьмусь я за это. Да и гарантий никто не даст, что судно с подобными характеристиками существует. Не обессудь...";
			link.l2.go = "BurntShip2";
		break;

		case "BurntShip8":
			dialog.text = "Время, слава Богу, есть. Хозяин отбыл в Европу и ранее полугода не обернётся.";
			link.l1 = "Что ж, берусь. Доставлю я вам подобное судно. Но учтите, если начнёте скупиться и выкраивать - сожгу его прямо у вас на глазах!";
			link.l1.go = "BurntShip9";
		break;

		case "BurntShip9":
			dialog.text = "Да что вы, капитан? Как можно? Я же понимаю, что это не лоханку из первой лужи выловить, тут время потребуется... Вы только приведите судно, а мы уж расстараемся. Будьте уверены...";
			link.l1 = "Надеюсь... Ждите меня с хорошими вестями. До свидания.";
			link.l1.go = "BurntShip9_exit";
		break;

		case "BurntShip9_exit":
			attrL = "BurntShipQuest_TimeIsOver_" + NPChar.Id;
			PChar.Quest.(attrL).win_condition.l1 = "Timer";
			PChar.Quest.(attrL).win_condition.l1.date.day = GetAddingDataDay(0, 120, 0);
			PChar.Quest.(attrL).win_condition.l1.date.month = GetAddingDataMonth(0, 120, 0);
			PChar.Quest.(attrL).win_condition.l1.date.year = GetAddingDataYear(0, 120, 0);
			PChar.Quest.(attrL).function = "BurntShipQuest_TimeIsOver";
			PChar.Quest.(attrL).PortmanId = NPChar.id;

			attrL = NPChar.Quest.BurntShip.ShipAttribute;

			iTest = sti(NPChar.Quest.BurntShip.ShipType);

			switch(attrL)
			{
				case "speedrate":
					attrL = "скорости. У " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Acc")) + " скорость по ветру должна быть не менее " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;

				case "turnrate":
					attrL = "манёвренности. У " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Acc")) + " манёвренность должна быть не менее " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;

				case "capacity":
					attrL = "трюма. У " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Acc")) + " трюм должен быть не менее " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;
			}

			sTitle = "BurntShipQuest" + NPChar.location;
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "BurntShipQuest", "1");
			AddQuestUserDataForTitle(sTitle, "cityName", XI_ConvertString("Colony" + NPChar.city + "Dat"));
			AddQuestUserData(sTitle, "portmanName", GetFullName(NPChar));
			AddQuestUserData(sTitle, "cityName", XI_ConvertString("Colony" + NPChar.city + "Gen"));
			AddQuestUserData(sTitle, "text", attrL);

			NPChar.Quest.BurntShip.LastPortmanName = GetFullName(NPChar); // Запомнм имя

			DialogExit();
		break;

		// Вариант, когда не уложились в сроки
		case "BurntShip10":
			dialog.text = "О чём вы хотели поговорить?";
			link.l1 = "А где прежний начальник портового управления, господин " + NPChar.Quest.BurntShip.LastPortmanName + "? У меня к нему дело.";
			link.l1.go = "BurntShip11";
		break;

		case "BurntShip11":
			dialog.text = "А его нет... Представляете? он сжёг судно одного известного господина и прикарманил страховую сумму. Пока власти разобрались что к чему, он уже подал в отставку и улизнул в Европу. Каков плут, а?..";
			link.l1 = "Да, мне известна эта история. Извините, мне пора...";
			link.l1.go = "BurntShip11_exit";
		break;

		case "BurntShip11_exit":
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "2");
			AddQuestUserData(sTitle, "portmanName", NPChar.Quest.BurntShip.LastPortmanName);
			CloseQuestHeader(sTitle);

			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;

			DialogExit();
		break;

		// Не просрочено - проверяем корабль
		case "BurntShip12":
			dialog.text = "О чём вы хотели поговорить?";
			link.l1 = "Я привел"+ GetSexPhrase("","а") +" вам судно с неординарной характеристикой. Жду обещанного вознаграждения.";
			link.l1.go = "BurntShip14";
			link.l2 = "Знаете, " + GetFullName(NPChar) + ", никак мне не попадаются суда с заказанной вами характеристикой. Пожалуй я откажусь от этого поручения. Извините, если подвел"+ GetSexPhrase("","а") +"...";
			link.l2.go = "BurntShip13";
		break;

		case "BurntShip13":
			dialog.text = "Очень жаль, капитан... очень жаль, что вы не хотите мне помочь.";
			link.l1 = "Тут не в желании дело, уважаемый. Вы же сами понимаете... До свидания...";
			link.l1.go = "BurntShip13_exit";
		break;

		case "BurntShip13_exit":
			sTitle = "BurntShipQuest" + NPChar.location;
			CloseQuestHeader(sTitle);

			ChangeCharacterReputation(PChar, -5);
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;

			DialogExit();
		break;

		case "BurntShip14":
			dialog.text = "Вот как! И как же называется наше новое судно?";

			sTitle = NPChar.Quest.BurntShip.ShipAttribute;

			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);

			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);

					if(cn > 0)
					{
						chref = GetCharacter(cn);

						sld = &RealShips[sti(chref.ship.type)];

						if(GetRemovable(chref) && sti(sld.basetype) == sti(NPchar.Quest.BurntShip.ShipType) &&
							stf(sld.(sTitle)) >= stf(NPChar.Quest.BurntShip.ShipNeededValue))
						{
							attrL = "l" + i;
							Link.(attrL) = chref.Ship.Name;
							Link.(attrL).go = "BurntShip15";
						}
					}
				}
			}

			link.l99 = "Извините, я зайду позже.";
			link.l99.go = "exit";
		break;

		case "BurntShip15":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "Ах, капитан, я рад, что не ошибся в вас! Как"+ GetSexPhrase("ой","ая") +" вы всё-таки молодец, просто спасли меня от смерти... Я вас очень попрошу, зайдите за деньгами дня через два. Формальности, знаете ли, с получением страховой суммы нужно уладить... А вы пока приведите судно в порядок. Ну, паруса обновить, пробоины подлатать, кренгование, опять же, не помешает...";
			link.l99 = "Вы не забыли, что я обещал"+ GetSexPhrase("","а") +", если начнутся проволочки с выплатой?";
			link.l99.go = "BurntShip16";
		break;

		case "BurntShip16":
			dialog.text = "Нет-нет, Боже упаси! Я своё слово сдержу, не волнуйтесь. Просто, зная, что предстоят ещё траты по, так сказать, маскировке корабля, я положил страховую сумму в рост. Вы уж поймите меня правильно...";
			link.l1 = "Я вас пойму, когда пиастры будут лежать в моём сундуке. До встречи.";
			link.l1.go = "BurntShip16_exit";
		break;

		case "BurntShip16_exit":
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "3");

			NPChar.Quest.BurntShip.TwoDaysWait = true;
			SaveCurrentNpcQuestDateParam(NPChar, "Quest.BurntShip.TwoDaysWait"); // Запомним дату

			sTitle = "BurntShipQuest" + NPChar.Id;
			PChar.Quest.(sTitle).over = "yes"; // Завершаем прерывание на время

			DialogExit();
		break;

		case "BurntShip17":
			dialog.text = "О чём вы хотели поговорить?";
			link.l1 = "Я приш"+ GetSexPhrase("ел","ла") +" за вознаграждением. Нужное вам судно по-прежнему у меня.";
			link.l1.go = "BurntShip18";
		break;

		case "BurntShip18":
			dialog.text = "Напомните, пожалуйста, его название. А то с этими нервотрёпками памяти, знаете ли, совсем не осталось.";

			sTitle = NPChar.Quest.BurntShip.ShipAttribute;
			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);

			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);

					if(cn > 0)
					{
						chref = GetCharacter(cn);

						sld = &RealShips[sti(chref.ship.type)];

						if(GetRemovable(chref) && sti(sld.basetype) == sti(NPchar.Quest.BurntShip.ShipType) &&
							stf(sld.(sTitle)) >= stf(NPChar.Quest.BurntShip.ShipNeededValue))
						{
							attrL = "l" + i;
							Link.(attrL) = chref.Ship.Name;
							Link.(attrL).go = "BurntShip19_" + i;
						}
					}
				}
			}

			link.l99 = "Извините, я зайду позже.";
			link.l99.go = "exit";
		break;

		case "BurntShip19":
			sld = &Characters[GetCompanionIndex(PChar, sti(NPChar.Quest.BurntShip.ShipCompanionIndex))];
			//cn = GetShipSellPrice(sld, CharacterFromID(NPChar.city + "_shipyarder")) * 3;
			cn = GetShipSellPrice(sld, CharacterFromID(NPChar.city + "_shipyarder")) * 2; // было x3 от продажной
			rRealShip = GetRealShip(GetCharacterShipType(sld));
			if (sti(rRealShip.Stolen)) cn *= 3; // "ворованные" компенсируются

			dialog.text = "Да, великолепно! Я готов выдать ваше вознаграждение, " + FindRussianMoneyString(cn) + ". Именно так страховая контора оценила сгоревшее судно. Страховка выплачена кредитными сундуками - наличных денег нет, извините.";
			link.l1 = "Э нет, такая сумма меня не устроит. Я уверен"+ GetSexPhrase("","а") +", что это судно стоит гораздо дороже.";
			link.l1.go = "BurntShip21";
			link.l2 = "Вот это совсем другое дело. Я рад"+ GetSexPhrase("","а") +", что смог"+ GetSexPhrase("","ла") +" вам помочь. До встречи.";
			link.l2.go = "BurntShip20_exit";

			NPChar.Quest.BurntShip.Money = cn;

			//sTitle = "BurntShipQuest" + NPChar.location;
			//PChar.Quest.(sTitle).over = "yes"; // Завершаем прерывание на время
		break;

		case "BurntShip20_exit":
			//AddMoneyToCharacter(PChar, sti(NPChar.Quest.BurntShip.Money));
			TakeNItems(pchar, "chest", makeint(sti(NPChar.Quest.BurntShip.Money)/12000));
			Log_Info("Вы получили кредитные сундуки");
			PlaySound("interface\important_item.wav");
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "4");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("","а"));
			AddQuestUserData(sTitle, "money", NPChar.Quest.BurntShip.Money);
			CloseQuestHeader(sTitle);

			ChangeCharacterReputation(PChar, 3);

			sld = &Characters[GetCompanionIndex(PChar, sti(NPChar.Quest.BurntShip.ShipCompanionIndex))];
			RemoveCharacterCompanion(PChar, sld);
			AddPassenger(PChar, sld, false);

			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;

			DialogExit();
		break;

		case "BurntShip21":
			dialog.text = "Ну что вы, капитан?! Поверьте мне, я знаю, что говорю. За такие деньги вы могли бы купить два подобных судна!";
			link.l1 = "Лучше я оставлю его себе. Уж очень оно мне приглянулось... Прощайте.";
			link.l1.go = "BurntShip21_exit";
		break;

		case "BurntShip21_exit":
			ChangeCharacterReputation(PChar, -5);

			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "5");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("","а"));
			AddQuestUserData(sTitle, "money", NPChar.Quest.BurntShip.Money);
			CloseQuestHeader(sTitle);

			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;

			DialogExit();
		break;

		//--> миниквесты портмана
		case "PortmanQuest":
			if (cRand(2) == 2)
			{	//квест догнать и передать судовой журнал
				dialog.text = "У меня забыл судовой журнал один капитан. Это же надо быть таким разиней!.. В общем, нужно его догнать и вернуть пропажу.";
				link.l1 = "Ну, это можно... За эту работу я берусь!";
				link.l1.go = "PortmanQuest_1";
				link.l2 = "Нет, не хочу этим заниматься. Это его проблемы, собственно...";
				link.l2.go = "node_2";
			}
			else
			{	//квест разыскать украденный корабль
				dialog.text = "У меня со стоянки кораблей был украден корабль. Я хочу, чтобы вы разыскали и вернули его мне.";
				link.l1 = "Хм, ну что же, я готов"+ GetSexPhrase("","а") +" взяться за розыски.";
				link.l1.go = "SeekShip_1";
				link.l2 = "Простите, но розыском кораблей я не занимаюсь.";
				link.l2.go = "node_2";
			}
		break;
		// -------------------------------- квест доставки судового журнала до рассеяного кэпа --------------------------
		case "PortmanQuest_1":
			dialog.text = "Отлично, вот его журнал... Уф-ф, прямо груз с плеч долой! Потеря судового журнала - штука неприятная, переживаю я за таких капитанов.";
			link.l1 = "Это точно, переживать стоит! Ну, а теперь расскажите мне подробней об этом рассеянном капитане.";
			link.l1.go = "PortmanQuest_2";
			pchar.questTemp.different = "PortmansJornal";
			SetTimerFunction("SmallQuests_free", 0, 0, 0); //освобождаем разрешалку на миниквесты
			SetJornalCapParam(npchar);
			GiveItem2Character(pchar, "PortmansBook");
			pchar.questTemp.PortmansJornal.gem = GenQuestPortman_GenerateGem();
		break;
		case "PortmanQuest_2":
			dialog.text = "Да, конечно! Его зовут " + npchar.quest.PortmansJornal.capName + ", он капитан " + GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName + "Acc")) + " с именем '" + npchar.quest.PortmansJornal.shipName + "'. Вышел он в море недавно, а направился в " + XI_ConvertString("Colony" + npchar.quest.PortmansJornal.city + "Acc") + ".";
			link.l1 = "Понятно. Ну что же, я его обязательно найду. Как быть с оплатой?";
			link.l1.go = "PortmanQuest_3";
		break;
		case "PortmanQuest_3":
			dialog.text = npchar.quest.PortmansJornal.capName + " сам с вами рассчитается, это в его интересах. Только постарайтесь найти его быстрей, и все будет нормально.";
			link.l1 = "Ясно. Ну, я пош"+ GetSexPhrase("ел","ла") +"...";
			link.l1.go = "exit";
			sTitle = npchar.id + "PortmansBook_Delivery";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "1");
			AddQuestUserDataForTitle(sTitle, "sCapName", npchar.quest.PortmansJornal.capName);
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName + "Acc")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.PortmansJornal.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.PortmansJornal.capName);
			AddQuestUserData(sTitle, "sCapName2", npchar.quest.PortmansJornal.capName);
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.PortmansJornal.city + "Acc"));
			if (GetIslandByCityName(npchar.quest.PortmansJornal.city) != npchar.quest.PortmansJornal.city)
			{
				AddQuestUserData(sTitle, "sAreal", ", что находится на " + XI_ConvertString(GetIslandByCityName(npchar.quest.PortmansJornal.city) + "Dat"));
			}
		break;
		// -------------------------------- квест розыска украденного корабля ----------------------------------
		case "SeekShip_1":
			dialog.text = "Прекрасно! Вы знаете, украденный корабль принадлежит не последнему человеку, так что он очень важен для меня. Я неплохо заплачу за работу...";
			link.l1 = "Понятно. Расскажите подробней, что за корабль, при каких обстоятельствах был украден.";
			link.l1.go = "SeekShip_2";
			pchar.questTemp.different = "PortmansSeekShip";
			SetTimerFunction("SmallQuests_free", 0, 0, 0); //освобождаем разрешалку на миниквесты
			SetSeekShipCapParam(npchar);
		break;
		case "SeekShip_2":
			dialog.text = XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName) + " с именем '" + npchar.quest.PortmansSeekShip.shipName + "'. Украден был ночью " + FindRussianDaysString(rand(5)+10) + " назад. Вахтенный убит.";
			link.l1 = "Хм, они уже успели уйти, небось, прилично. В общем, о горячих следах говорить не приходится...";
			link.l1.go = "SeekShip_3";
		break;
		case "SeekShip_3":
			dialog.text = "Да, верно. Но и смысла мне сразу панику поднимать не было. Военные если и догонят, то разнесут корабль в щепки, а это не совсем то, что мне нужно.";
			link.l1 = "Понятно. Ну что же, приступаю к поискам. Надеюсь, мне повезет.";
			link.l1.go = "exit";
			sTitle = npchar.id + "Portmans_SeekShip";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName)));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.PortmansSeekShip.shipName);
		break;
		case "SeekShip_break":
			dialog.text = "Хм, ну что же, очень жаль. Хотя, на успех сложно было рассчитывать...";
			link.l1 = "Да, слишком много времени прошло с момента кражи.";
			link.l1.go = "SeekShip_break_1";
		break;
		case "SeekShip_break_1":
			dialog.text = "Ну что же, спасибо за оказанную помощь, хоть она и не увенчалась успехом.";
			link.l1 = "Не за что...";
			link.l1.go = "exit";
			sTemp = "SeekShip_checkAbordage" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание на абордаж
			cn = GetCharacterIndex("SeekCap_" + npchar.index);
			//если кэп-вор еще жив - убираем его
			if (cn > 0)
			{
				characters[cn].LifeDay = 0;
				Map_ReleaseQuestEncounter(characters[cn].id);
				group_DeleteGroup("SeekCapShip_" + characters[cn].index);
			}
			sTitle = npchar.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "7");
			CloseQuestHeader(sTitle);
			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			npchar.quest = ""; //освобождаем личный флаг квеста для портмана
			ChangeCharacterReputation(pchar, -7);
		break;
		case "SeekShip_good":
			if (npchar.quest == "SeekShip_sink")
			{
				dialog.text = "Отлично! Однако, полагаю, что это не совсем тот корабль, что был украден... Хотя, собственно, все равно! Я беру его у вас.";
				link.l1 = "Да, действительно...";
				//npchar.quest.money = makeint(sti(npchar.quest.money) / 4); //снижаем оплату
				ChangeCharacterReputation(pchar, 5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
				AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 10);
				AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 10);
				AddCharacterExpToSkill(GetMainCharacter(), "Commerce", 50);
				AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 20);
			}
			else
			{
				dialog.text = "Превосходно! Вы мне очень помогли. Представляю, насколько это было сложно.";
				link.l1 = "Да, действительно...";
				ChangeCharacterReputation(pchar, 10);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
				AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 100);
				AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 150);
				AddCharacterExpToSkill(GetMainCharacter(), "Grappling", 100);
			}
			link.l1.go = "SeekShip_good_1";
		break;
		case "SeekShip_good_1":
			dialog.text = "Я готов выплатить вам вознаграждение. Оно составляет " + FindRussianMoneyString(makeint(sti(npchar.quest.chest)*15000)) + " в сундуках. Больше я заплатить не могу, к сожалению.";
			link.l1 = "Ну что же, этого тоже достаточно. Спасибо и всего хорошего.";
			link.l1.go = "exit";
			//AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, "chest", sti(npchar.quest.chest));
			sTitle = npchar.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "6");
			CloseQuestHeader(sTitle);

			pchar.questTemp.genquestcount = sti(pchar.questTemp.genquestcount) + 1;
			if(sti(pchar.questTemp.genquestcount) >= 10) UnlockAchievement("gen_quests", 1);
			if(sti(pchar.questTemp.genquestcount) >= 20) UnlockAchievement("gen_quests", 2);
			if(sti(pchar.questTemp.genquestcount) >= 40) UnlockAchievement("gen_quests", 3);

			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			npchar.quest = ""; //освобождаем личный флаг квеста для портмана
		break;

		//------------------------------> инфа по базе квествых кэпов
		//ВНИМАНИЕ. в квестбук должна заносится типовая строка по примеру   PortmansBook_Delivery  #TEXT   5
		//в список портмана заносим тайтл, заголовок и номер строки из quest_text.txt
		//ПРИМЕР: в конце метода  void SetCapitainFromCityToSea(string qName)
		case "BuyLicense":
				dialog.text = "Есть у меня один документ, срок которого вот-вот истечет. Не знаю, зачем он кому-либо может понадобиться, но я только рад избавиться от этой бумажки. За определенную сумму, конечно. " + license_price + ". Берете?";
				if(makeint(Pchar.money) >= license_price)
				{
					link.l1 = "Беру.";
					link.l1.go = "LicenseBought";
				}
				link.l2 = "Нет. Спасибо.";
				link.l2.go = "exit";
		break;
		case "LicenseBought":
				AddMoneyToCharacter(Pchar, -license_price);
				GiveNationLicence(sti(NPChar.nation), license_expires);

				dialog.text = "Держите.";
				link.l1 = "До свидания.";
				link.l1.go = "exit";
				license_expires = rand(2);
		break;
		case "CapitainList":
			if (sti(npchar.quest.qty) > 0)
			{
				dialog.text = "Есть отметившиеся капитаны. Кто конкретно вас интересует?";
				makearef(arCapBase, npchar.quest.capitainsList);
				for (i=0; i<sti(npchar.quest.qty); i++)
				{
					arCapLocal = GetAttributeN(arCapBase, i);
					sCapitainId = GetAttributeName(arCapLocal);
					sld = characterFromId(sCapitainId);
					attrL = "l" + i;
					link.(attrL) = GetFullName(sld) + ", капитан " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")) + " '" + sld.Ship.name + "'.";
					link.(attrL).go = "CapList_"+attrL;
				}
			}
			else
			{
				dialog.text = "У меня в списках нет капитанов, способных вас заинтересовать.";
				link.l1 = "Понятно. Спасибо за информацию.";
				link.l1.go = "node_2";
			}
		break;
		case "CapList_l0":
			makearef(arCapBase, npchar.quest.capitainsList);
			arCapLocal = GetAttributeN(arCapBase,  0);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Та-а-ак, давайте посмотрим... Ага, есть! ", "Так-так... Ага, нашел! ", "Значит, так. ") +
				"Капитан " + GetFullName(sld) + " " + arCapLocal.date + " года ушел из нашего порта в " + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = "Спасибо. Хотелось бы посмотреть список дальше...";
			link.l1.go = "CapitainList";
			link.l2 = "Все, капитаны меня более не интересуют.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", ", что находится на " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId);
		break;
		case "CapList_l1":
			makearef(arCapBase, npchar.quest.capitainsList);
			arCapLocal = GetAttributeN(arCapBase,  1);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Та-а-ак, давайте посмотрим... Ага, есть! ", "Так-так... Ага, нашел! ", "Значит, так. ") +
				"Капитан " + GetFullName(sld) + " " + arCapLocal.date + " года ушел из нашего порта в " + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = "Спасибо. Хотелось бы посмотреть список дальше...";
			link.l1.go = "CapitainList";
			link.l2 = "Все, капитаны меня более не интересуют.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", ", что находится на " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId);
		break;
		case "CapList_l2":
			makearef(arCapBase, npchar.quest.capitainsList);
			arCapLocal = GetAttributeN(arCapBase,  2);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Та-а-ак, давайте посмотрим... Ага, есть! ", "Так-так... Ага, нашел! ", "Значит, так. ") +
				"Капитан " + GetFullName(sld) + " " + arCapLocal.date + " года ушел из нашего порта в " + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = "Спасибо. Хотелось бы посмотреть список дальше...";
			link.l1.go = "CapitainList";
			link.l2 = "Все, капитаны меня более не интересуют.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", ", что находится на " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId);
		break;
		case "CapList_l3":
			makearef(arCapBase, npchar.quest.capitainsList);
			arCapLocal = GetAttributeN(arCapBase,  3);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Та-а-ак, давайте посмотрим... Ага, есть! ", "Так-так... Ага, нашел! ", "Значит, так. ") +
				"Капитан " + GetFullName(sld) + " " + arCapLocal.date + " года ушел из нашего порта в " + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = "Спасибо. Хотелось бы посмотреть список дальше...";
			link.l1.go = "CapitainList";
			link.l2 = "Все, капитаны меня более не интересуют.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", ", что находится на " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId);
		break;
		case "CapList_l4":
			makearef(arCapBase, npchar.quest.capitainsList);
			arCapLocal = GetAttributeN(arCapBase,  4);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Та-а-ак, давайте посмотрим... Ага, есть! ", "Так-так... Ага, нашел! ", "Значит, так. ") +
				"Капитан " + GetFullName(sld) + " " + arCapLocal.date + " года ушел из нашего порта в " + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = "Спасибо. Хотелось бы посмотреть список дальше...";
			link.l1.go = "CapitainList";
			link.l2 = "Все, капитаны меня более не интересуют.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", ", что находится на " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId);
		break;
		//<--------------------------- инфа по базе квествых кэпов

		case "ShipStock_1":
				ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{
					dialog.text = "Какой именно корабль вы хотите оставить?";
					for(i=1; i<COMPANION_MAX; i++)//почему нельзя свой единственный корабль сдать?
					{
						cn = GetCompanionIndex(PChar, i);
						if(cn > 0)
						{
							chref = GetCharacter(cn);
							if (!GetRemovable(chref)) continue;
							if(RealShips[sti(chref.Ship.Type)].BaseName == SHIP_SOLEYRU) continue; //Отрубаем хитрость на получение Солея

							attrL = "l"+i;
							Link.(attrL)	= XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'. С ним останется капитан " + GetFullName(chref) + ".";
							Link.(attrL).go = "ShipStockMan11_" + i;
							attrL = "l"+i+COMPANION_MAX;
							Link.(attrL)	= XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "' без моего офицера.";
							Link.(attrL).go = "ShipStockMan22_" + i;

						}
					}
					Link.l17 = "Спасибо, не нужно.";
					Link.l17.go = "exit";
				}
				else
				{
					dialog.text = "Хм. Я не вижу ваших кораблей в порту.";
					Link.l1 = "Да, я просто хотел"+ GetSexPhrase("","а") +" узнать о возможности стоянки.";
					Link.l1.go = "exit";
				}
		break;

		case "ShipStock_Choose":
			dialog.text = "Посмотрим, что это за корабль.";
			Link.l1 = "Хорошо.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			Link.l2.go = "exit";
		break;

		case "ShipStock_2":
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			if (pchar.location != "Caiman_PortOffice")  NPChar.MoneyForShip = GetPortManPriceExt(NPChar, chref);
			else NPChar.MoneyForShip = 0;
			if (pchar.location != "Caiman_PortOffice")
			{
				dialog.Text = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "', класс " + RealShips[sti(chref.Ship.Type)].Class +
					 ", стоимость стоянки " + FindRussianMoneyString(sti(NPChar.MoneyForShip)) + " в месяц, оплата за месяц вперед.";
			}
			else
			{
				dialog.Text = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "', класс " + RealShips[sti(chref.Ship.Type)].Class +
					 ", стоимость стоянки - для вас полностью бесплатно.";
			}
			Link.l1 = "Да. Это меня устраивает.";
			if (sti(Pchar.Money) >= sti(NPChar.MoneyForShip))
			{
				Link.l1.go = "ShipStock_3";
			}
			else
			{
				Link.l1.go = "ShipStock_NoMoney";
			}
			Link.l2 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			Link.l2.go = "exit";
		break;

		case "ShipStock_NoMoney":
			dialog.text = "Меня тоже все устроит, если у вас будет нужная сумма.";
			Link.l1 = "Упс... зайду позже.";
			Link.l1.go = "exit";
		break;

		case "ShipStock_3":
			AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForShip));
			if (sti(NPChar.StoreWithOff))
			{
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			chref.ShipInStockMan = NPChar.id;
			// Warship 22.03.09 fix Не перенеслось с КВЛ 1.2.3
			chref.ShipInStockMan.MoneyForShip = NPChar.MoneyForShip;
			chref.ShipInStockMan.AltDate = GetQuestBookDataDigit(); // для печати
			SaveCurrentNpcQuestDateParam(chref, "ShipInStockMan.Date"); // для расчета
			//chref.Ship.Crew.Quantity  = 0;
			RemoveCharacterCompanion(pchar, chref);
			}
			else
			{
			chref = GetCharacter(NPC_GenerateCharacter("ShipInStockMan", "PKM_rab_"+(rand(3)+1), "man", "man", rand(5)+1, NPChar.nation, -1, false));
			chref.id = chref.id + "_" + chref.index; //меняем ID на оригинальный
			chref.reputation = (1 + rand(44) + rand(44));
			chref.lastname = chref.name;//"сторож Иван" лучше чем "сторож Иванов"?
			chref.name = "сторож";
			DeleteAttribute(chref,"ship");
			chref.ship = "";

			chref.ShipInStockMan = NPChar.id;
			chref.ShipInStockMan.MoneyForShip = NPChar.MoneyForShip;
			chref.ShipInStockMan.AltDate = GetQuestBookDataDigit(); // для печати
			SaveCurrentNpcQuestDateParam(chref, "ShipInStockMan.Date"); // для расчета

			compref = GetCharacter(sti(NPChar.ShipToStoreIdx));//компаньон, у которого надо забрать корабль

			makearef(arTo, chref.ship);
			makearef(arFrom, compref.Ship);
			CopyAttributes(arTo, arFrom);

			compref.ship.type = SHIP_NOTUSED;
			RemoveCharacterCompanion(pchar, compref);
			AddPassenger(pchar, compref, false);
			DelBakSkill(compref);
			}

			chref.location = "";
			chref.location.group = "";
			chref.location.locator = "";
			NPChar.Portman	= sti(NPChar.Portman) + 1;
			pchar.ShipInStock = sti(pchar.ShipInStock) + 1;//разобраться - что это. не могу найти, где оно используется.

			dialog.text = "Хорошо. Заберете, когда будет нужно.";
			Link.l1 = "Спасибо.";
			Link.l1.go = "exit";
		break;

		case "ShipStockReturn_1":
			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				if (GetCompanionQuantity(pchar) < COMPANION_MAX)
				{
					dialog.text = "Какой именно корабль вы заберете?";
					cn = 1;
					for(i=1; i<MAX_CHARACTERS; i++)
					{
						makeref(chref, Characters[i]);
						if (CheckAttribute(chref, "ShipInStockMan"))
						{
							if (chref.ShipInStockMan == NPChar.id)
							{
								attrL = "l"+cn;
								if(HasSubStr(chref.id, "ShipInStockMan_"))
								{
								Link.(attrL)	= XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
								Link.(attrL).go = "ShipStockManBack22_" + i;
								}
								else
								{
								Link.(attrL)	= XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "' и офицер " + GetFullName(chref) + ".";
								Link.(attrL).go = "ShipStockManBack11_" + i;
								}
								cn++;
							}
						}
					}

					Link.l99 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
					Link.l99.go = "exit";
				}
				else
				{
					dialog.text = "Нет ли у вас места для еще одного корабля?";
					Link.l1 = "Да, точно. Спасибо.";
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Хм. Я не вижу вашего флагмана в порту. А забрать свои корабли вы можете только здесь.";
				Link.l1 = "Хорошо, я прибуду за ними позднее.";
				Link.l1.go = "exit";
			}
		break;
	  	case "ShipStockManBack":
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			NPChar.MoneyForShip =  GetNpcQuestPastMonthParam(chref, "ShipInStockMan.Date") * sti(chref.ShipInStockMan.MoneyForShip);

			//if (sti(NPChar.StoreWithOff)) string sTextAdd = ""; else string sTextAdd = "И кто из ваших офицеров заберёт его?";

			if (sti(NPChar.MoneyForShip) > 0)
			{
				dialog.Text = "Забираете? С вас за хранение еще " + FindRussianMoneyString(sti(NPChar.MoneyForShip)) + ".";
			}
			else
			{
				dialog.Text = "Забираете?";
			}
			if (sti(NPChar.MoneyForShip) <= sti(pchar.Money))
			{
				Link.l1 = "Да.";
				Link.l1.go = "ShipStockManBack2";
			}
			Link.l2 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			Link.l2.go = "exit";
		break;

		case "ShipStockManBack2":
			if (sti(NPChar.StoreWithOff))
			{
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();

			AddMoneyToCharacter(Pchar, -sti(NPChar.MoneyForShip));
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DownCrewExp(chref,GetNpcQuestPastDayParam(chref, "ShipInStockMan.Date"));
			DeleteAttribute(chref, "ShipInStockMan");
			SetCompanionIndex(pchar, -1, sti(NPChar.ShipToStoreIdx));

			NPChar.Portman	= sti(NPChar.Portman) - 1;
			pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
			}
			else
			{
			dialog.Text = "Кому из ваших офицеров передать его?";
			int _curCharIdx;
			int q = 0;
			int nListSize = GetPassengersQuantity(pchar);
			for(i=0; i<nListSize; i++)
				{
				_curCharIdx = GetPassenger(pchar,i);
				sld = GetCharacter(_curCharIdx);
					if (_curCharIdx!=-1)
					{
						ok = CheckAttribute(&characters[_curCharIdx], "prisoned") && sti(characters[_curCharIdx].prisoned) == true;
						if (sld.id != "pet_crab" && sld.id != "Albreht_Zalpfer" && !CheckAttribute(sld,"HPminusDaysNeedtoRestore"))
						{
							if (!ok && GetRemovable(&characters[_curCharIdx]))
							{
								attrL = "l"+i;
								Link.(attrL)	= GetFullName(&characters[_curCharIdx]);
								Link.(attrL).go = "ShipStockManBack2_" + i;
								q++;
							}
						}
					}
				}
			attrL = "l"+nListSize;
			if (q == 0)
				{
				Link.(attrL) = RandSwear() + "Забыл" + GetSexPhrase("","а") + " капитана для этого корабля с собой привести.";
				Link.(attrL).go = "exit";
				}
			else
				{
				Link.(attrL) = "Нет, я передумал"+ GetSexPhrase("","а") +".";
				Link.(attrL).go = "exit";
				}
			}
		break;

		//ОЗГ, Хоум
		case "Houm_portman_1":
			if (pchar.questTemp.Headhunter.City == npchar.city)
			{
				dialog.text = "Да, останавливался. Вы можете найти интересующего вас капитана в городе.";
				link.l1 = "Спасибо! Вы мне очень помогли.";
				link.l1.go = "Houm_portman_yes";
			}
			else
			{
				dialog.text = "Нет, впервые слышу о таком.";
				link.l1 = "Хм... Ладно, будем искать дальше.";
				link.l1.go = "exit";
			}
		break;

		case "Houm_portman_yes":
			pchar.questTemp.Headhunter = "houm_tavern";
			CreateHoum();
			AddQuestRecord("Headhunt", "5");
			AddQuestUserData("Headhunt", "sCity", pchar.questTemp.Headhunter.Cityname);
			DialogExit();
		break;
		//ОЗГ, Хоум
	}
}

float BurntShipQuest_GetMaxNeededValue(int iShipType, string _param)
{
	float NeededValue = makefloat(GetBaseShipParamFromType(iShipType, _param));
	switch (_param)
	{
		case "speedrate":
			NeededValue += ((0.33 + frandSmall(0.27)) * (NeededValue/10.0));
		break;
		case "turnrate":
			NeededValue += ((0.33 + frandSmall(0.28)) * (NeededValue/10.0));
		break;
		case "capacity":
			NeededValue += ((0.33 + frandSmall(0.28)) * (NeededValue/8.0));
		break;
	}
	return NeededValue;
}


// Warship 25.07.09 Генер "Сгоревшее судно". Начальные иниты для портмана - тип разыскиваемого судна, выдающаяся характеристика и т.д.
void BurntShipQuest_FillStartParams(ref _npchar)
{
	int rank = sti(PChar.rank);
	int shipType, temp;
	float neededValue;
	String shipAttribute;

	// TODO Пересмотреть зависимость от ранга
	if (rank < 5) shipType = SHIP_BERMSLOOP + rand(11);
	if (rank >= 5 && rank < 10) shipType = SHIP_POLACCA + rand(12);
	if (rank >= 10 && rank < 15) shipType = SHIP_BRIG + rand(23);
	if (rank >= 15 && rank < 20) shipType = SHIP_PINNACE + rand(31);
	if (rank >= 20 && rank < 30) shipType = SHIP_GALEON50 + rand(20);
	if (rank >= 30) shipType = SHIP_POSEIDON + rand(19);

	switch(shipType)
	{
		case SHIP_BERMSLOOP:
			shipAttribute = "speedrate";
	//				neededValue = 16.74 + fRandSmall(0.15);
			else
			{
				if(temp == 1)
				{
	//						neededValue = 42.12 + fRandSmall(0.4);
					shipAttribute = "turnrate";
				}
			else
				{
	//						neededValue = 864 + rand(8);
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_LUGGER_H:
		temp = rand(3);
			if(temp == 2)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
			{
						shipAttribute = "turnrate";
			}
			else
			{
						 shipAttribute = "capacity";
			}
			}
		break;

		case SHIP_SLOOP:
			temp = rand(3);

			if(temp == 2)
			{
	//					neededValue = 14.9 + fRandSmall(0.14);
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
	//						neededValue = 42.12 + fRandSmall(0.4);
					shipAttribute = "turnrate";
				}
				else
				{
	//						neededValue = 864 + rand(8);
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_BERMSLOOP:
			temp = rand(3);

			if(temp == 2)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_EMPRESS:
			temp = rand(3);

			if(temp == 2)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					//neededValue = 864 + rand(8);
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_PINK:
			temp = rand(3);

			if(temp == 2)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_SPEEDY:
			temp = rand(3);

			if(temp == 2)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_FR_SLOOP:
			temp = rand(3);

			if(temp == 2)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_Galeoth_h:
			temp = rand(3);

			if(temp == 2)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_SLOOP_B:
			temp = rand(3);

			if(temp == 2)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_NEPTUNUS:
			temp = rand(3);

			if(temp == 2)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_SOPHIE:
			temp = rand(3);

			if(temp == 2)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_SCHOONER:
			if(rand(3) == 0)
			{
				neededValue = 14.04 + fRandSmall(0.13);
				shipAttribute = "speedrate";
			}
			else
			{
				neededValue = 37.8 + fRandSmall(0.35);
				shipAttribute = "turnrate";
			}
			else
			{
				neededValue = 1836 + rand(170);
				shipAttribute = "capacity";
			}
		break;

		case SHIP_POLACCA:
			if(rand(3) == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_FR_POSTILLIONEN:
			if(rand(3) == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_COLONIALSCHOONER:
			if(rand(3) == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_XEBEC:
			if(rand(3) == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_BATTLEXEBEC:
			if(rand(3) == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_XEBECLIGHT:
			if(rand(3) == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_SCHOONERLIGHT:
			if(rand(3) == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_MIRAGE:
			if(rand(3) == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_POLACRE:
			if(rand(3) == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_ENSLAVER:
			if(rand(3) == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_SHNYAVA:
			if(rand(3) == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_BARQUE:
			neededValue = 1836 + rand(170);
			shipAttribute = "capacity";
		break;

		case SHIP_CARAVEL:
			neededValue = 3240 + rand(30);
			shipAttribute = "capacity";
		break;

		case SHIP_BARKENTINE:
			neededValue = 43.2 + fRandSmall(0.4);
			shipAttribute = "turnrate";
		break;

		case SHIP_BRIGANTINE:
			if(rand(3) == 1)
			{
				neededValue = 16.74 + fRandSmall(0.16);
				shipAttribute = "speedrate";
			}
			else
			{
				neededValue = 54.0 + fRandSmall(0.5);
				shipAttribute = "turnrate";
			}
			else
			{
			neededValue = 3240 + rand(30);
			shipAttribute = "capacity";
			}
		break;

		case SHIP_CASTELF:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
			shipAttribute = "capacity";
			}
		break;

		case SHIP_DERFFLINGER:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
			shipAttribute = "capacity";
			}
		break;

		case SHIP_INTERCEPTOR:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
			shipAttribute = "capacity";
			}
		break;

		case SHIP_PO_FLEUT50:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
			shipAttribute = "capacity";
			}
		break;

		case SHIP_FLEUT:
			neededValue = 3240 + rand(30);
			shipAttribute = "capacity";
		break;

		case SHIP_BRIG:
			if(rand(3) == 1)
			{
				neededValue = 15.66 + fRandSmall(0.15);
				shipAttribute = "speedrate";
			}
			else
			{
				neededValue = 48.6 + fRandSmall(0.45);
				shipAttribute = "turnrate";
			}
			else
			{
			neededValue = 3240 + rand(30);
			shipAttribute = "capacity";
			}
		break;

		case SHIP_BRIGHEAVY:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
			shipAttribute = "capacity";
			}
		break;

		case SHIP_GREYHOUND:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
			shipAttribute = "capacity";
			}
		break;

		case SHIP_CORVETTELIGHT:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
			shipAttribute = "capacity";
			}
		break;

		case SHIP_PACKET_BRIG:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
			shipAttribute = "capacity";
			}
		break;

		case SHIP_PDN:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
			shipAttribute = "capacity";
			}
		break;

		case SHIP_ENTERPRISE:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
			shipAttribute = "capacity";
			}
		break;

		case SHIP_POLACRE_H:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
			shipAttribute = "capacity";
			}
		break;

		case SHIP_FRIGATEMEDIUM:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{

				shipAttribute = "turnrate";
			}
			else
			{
			shipAttribute = "capacity";
			}
		break;

		case SHIP_RaaFrigate:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
			shipAttribute = "capacity";
			}
		break;

		case SHIP_CARAVEL2:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
			shipAttribute = "capacity";
			}
		break;

		case SHIP_FLEUTWAR:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
			shipAttribute = "capacity";
			}
		break;

		case SHIP_FLEUTWARSAT:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
			shipAttribute = "capacity";
			}
		break;

		case SHIP_GALEONTRADER:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
			shipAttribute = "capacity";
			}
		break;

		case SHIP_LYDIA:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
			shipAttribute = "capacity";
			}
		break;

		case SHIP_GALEON_L:
			neededValue = 3672 + rand(34);
			shipAttribute = "capacity";
		break;

		case SHIP_CORVETTE:
			if(rand(3) == 1)
			{
				neededValue = 17.5 + fRandSmall(0.16);
				shipAttribute = "speedrate";
			}
			else
			{
				neededValue = 59.4 + fRandSmall(0.55);
				shipAttribute = "turnrate";
			}
			else
			{
				neededValue = 4320 + rand(40);
				shipAttribute = "capacity";
			}
		break;

		case SHIP_CRIMSONBLOOD:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_FRIGATE_l:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_BATTLECORVETTE:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_BLACKANGEL:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_COASTALFRIGATE:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_FR_FRIGATE:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_UNICORN:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_LINEFRIGATE:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_LIGHTFRIGATE:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_BOUSSOLE:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_SURPRISE:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_SALAMANDER:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_FRIGATE_SAT:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_BATTLEFRIGATE:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_NIGHTMARE:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_MORDAUNT:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_GALEON_H:
			neededValue = 5022 + rand(47);
			shipAttribute = "capacity";
		break;

		case SHIP_PINNACE:
			if(rand(3) == 1)
			{
				neededValue = 14.04 + fRandSmall(0.13);
				shipAttribute = "speedrate";
			}
			else
			{
				neededValue = 59.4 + fRandSmall(0.55);
				shipAttribute = "turnrate";
			}
			else
			{
				neededValue = 4320 + rand(40);
				shipAttribute = "capacity";
			}
		break;

		case SHIP_DUTCHPINNACE:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_PINNACELIGHT:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_XEBEKVT:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_FELIPE:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			  else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_JAMAICASHIP:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			  else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_THEBLACKPEARL:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			  else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_GALEON1:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			  else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_LA_MARIANNA:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			  else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_PIRATFASTGAL:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			  else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_REVENGE:
			if(rand(3) == 1)
			{
				shipAttribute = "speedrate";
			}
			  else
			{
				shipAttribute = "turnrate";
			}
			else
			{
				shipAttribute = "capacity";
			}
		break;

		case SHIP_FRIGATE:
			temp = rand(3);

			if(temp == 0)
			{
				neededValue = 15.44 + fRandSmall(0.14);
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					neededValue = 41.04 + fRandSmall(0.38);
					shipAttribute = "turnrate";
				}
				else
				{
					neededValue = 3240 + rand(30);
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_AMSTERDAM:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_CARRACA:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_GALEON50:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_FASTFRIGATE:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_FR_ESSEX:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_FRIGATE_H:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_WARGALLEON2:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_NL_PINNACEOFWAR47:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_HOLLGALEON_H:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_FEARLESS:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_NL_FWZP:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_CONSTITUTION:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_OXFORD:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_DUTCHLINESHIP:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_DUTCHSHIP:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_NL_CONVOISHIP:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_COURONNE:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_ALEXIS:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_LINESHIPHEAVY:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_WARSHIP:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_HEAVYWARSHIP:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_POSEIDON:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_HMS_CENTURION:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_RESOLUTION:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_FR_SUPERIORWARSHIP1:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_LINK:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_SUPERBE:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_BATTLESHIP:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_LINK2:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_BELLONA:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_LINEARSHIP:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_SHARK:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_ZEVENPROVINCIEN:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_FR_TRINITY:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_MANOWAR_FAST:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_BATTLEMANOWAR:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_MANOWAR_GUB:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_PRINCE:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_MANOWAR:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_HMS_VICTORY:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

		case SHIP_SP_SANFELIPE:
			temp = rand(3);

			if(temp == 0)
			{
				shipAttribute = "speedrate";
			}
			else
			{
				if(temp == 1)
				{
					shipAttribute = "turnrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			}
		break;

	}

	neededValue = BurntShipQuest_GetMaxNeededValue(shipType, shipAttribute);

	Log_TestInfo("shipType == " + shipType);
	Log_TestInfo("ShipAttribute == " + shipAttribute);
	Log_TestInfo("ShipNeededValue == " + neededValue);

	_npchar.Quest.BurntShip.ShipType = shipType;
	_npchar.Quest.BurntShip.ShipAttribute = shipAttribute;

	if(shipAttribute != "capacity") // Чтобы трюм с десятичными не писался
	{
		_npchar.Quest.BurntShip.ShipNeededValue = FloatToString(neededValue, 2);
	}
	else
	{
		_npchar.Quest.BurntShip.ShipNeededValue = MakeInt(neededValue);
	}
}


void SetJornalCapParam(ref npchar)
{
	//созадем рассеянного кэпа
	ref sld = GetCharacter(NPC_GenerateCharacter("PortmansCap_" + npchar.index, "", "man", "man", 20, sti(npchar.nation), -1, true));
	SetCaptanModelByEncType(sld, "trade");
	SetShipToFantom(sld, "trade", true);
	sld.Ship.Mode = "trade";
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "PortmansCap";
	sld.DeckDialogNode = "PortmansCap_inDeck";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
	//в морскую группу кэпа
	string sGroup = "PorpmansShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup,"trade");
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation));
	//записываем данные в структуры портмана и кэпа
	npchar.quest = "PortmansJornal"; //личный флаг квеста для портмана
	npchar.quest.PortmansJornal.capName = GetFullName(sld); //имя кэпа
	npchar.quest.PortmansJornal.shipName = sld.Ship.name; //имя корабля
	npchar.quest.PortmansJornal.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название корабля
	npchar.quest.PortmansJornal.city = SelectNotEnemyColony(npchar); //определим колонию, куда ушел кэп
	sld.quest = "InMap"; //личный флаг рассеянного кэпа
	sld.quest.targetCity = npchar.quest.PortmansJornal.city; //продублируем колонию-цель в структуру кэпа
	sld.quest.firstCity = npchar.city; //капитану знать откуда вышел в самом начале
	sld.quest.stepsQty = 1; //количество выходов в море
	sld.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1) * 150) + (sti(pchar.rank)*150); //вознаграждение
	Log_TestInfo("Рассеянный кэп " + sld.id + " направился в: " + sld.quest.targetCity);
	//определим бухту, куда ставить энкаунтер. чтобы сразу не генерился перед ГГ у города
	string sTemp = GetArealByCityName(npchar.city);
	sld.quest.baseShore = GetIslandRandomShoreId(sTemp);
	//на карту
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "ranger";
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName) + " '" + npchar.quest.PortmansJornal.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(sTemp, GetArealByCityName(sld.quest.targetCity))+5; //дней доехать даем с запасом
	Map_CreateTrader(sld.quest.baseShore, sld.quest.targetCity, sld.id, daysQty);
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "jornal"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = npchar.id + "PortmansBook_Delivery"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "PortmansBook_Delivery"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
	NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
	NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
	NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}
//проверить список отметившихся квестовых кэпов
int CheckCapitainsList(ref npchar)
{
	int bResult = 0;
	if (!CheckAttribute(npchar, "quest.capitainsList")) return bResult;
	aref arCapBase, arCapLocal;
	makearef(arCapBase, npchar.quest.capitainsList);
	int	Qty = GetAttributesNum(arCapBase);
	if (Qty < 1) return bResult;
	string sCapitainId;
	for (int i=0; i<Qty; i++)
	{
		arCapLocal = GetAttributeN(arCapBase, i);
		sCapitainId = GetAttributeName(arCapLocal);
		if (GetCharacterIndex(sCapitainId) > 0) //если еще жив
		{
			bResult++;
		}
		else
		{
			DeleteAttribute(arCapBase, sCapitainId);
			i--;
			Qty--;
		}
	}
	if (bResult > 5) bResult = 5;
	return bResult;
}

void SetSeekShipCapParam(ref npchar)
{
	//создаем кэпа-вора
	int Rank = sti(pchar.rank) + 5;
	if (Rank > 30) Rank = 30;
	ref sld = GetCharacter(NPC_GenerateCharacter("SeekCap_" + npchar.index, "", "man", "man", Rank, PIRATE, -1, true));
	SetCaptanModelByEncType(sld, "pirate");
	SetShipToFantom(sld, "pirate", true);
	sld.Ship.Mode = "pirate";
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "SeekCap";
	sld.DeckDialogNode = "SeekCap_inDeck";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//в морскую группу кэпа
	string sGroup = "SeekCapShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation));
	//записываем данные в структуры портмана и кэпа
	npchar.quest = "PortmansSeekShip"; //личный флаг квеста для портмана
	npchar.quest.PortmansSeekShip.capName = GetFullName(sld); //имя кэпа-вора
	npchar.quest.PortmansSeekShip.shipName = sld.Ship.name; //имя украденного корабля
	npchar.quest.PortmansSeekShip.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название украденного корабля
	npchar.quest.PortmansSeekShip.shipTape = RealShips[sti(sld.Ship.Type)].basetype; //тип украденного корабля
	//npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1) * 1000) + (sti(pchar.rank)*500); //вознаграждение
	npchar.quest.chest = 7-sti(RealShips[sti(sld.Ship.Type)].Class); //в сундуках
	sld.quest = "InMap"; //личный флаг кэпа-вора
	sld.city = SelectAnyColony(npchar.city); //определим колонию, откуда кэп-вор выйдет
	sld.quest.targetCity = SelectAnyColony2(npchar.city, sld.city); //определим колонию, куда он придет
	Log_TestInfo("Кэп-вор " + sld.id + " вышел из: " + sld.city + " и направился в: " + sld.quest.targetCity);
	sld.quest.cribCity = npchar.city; //город, откуда кэп-вор спер корабль
	//на карту
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "Galleon_red";
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName) + " '" + npchar.quest.PortmansSeekShip.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+3; //дней доехать даем с запасом
	Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, daysQty);
	//прерывание на абордаж
	string sTemp = "SeekShip_checkAbordage" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "Character_Capture";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SeekShip_checkAbordage";
	pchar.quest.(sTemp).CapId = sld.id;
	//прерывание на потопление без абордажа
	sTemp = "SeekShip_checkSink" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "Character_sink";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SeekShip_checkSink";
	pchar.quest.(sTemp).CapId = sld.id;
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "robber"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = npchar.id + "Portmans_SeekShip"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "Portmans_SeekShip"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
	NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
	NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
	NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

string GenQuestPortman_GenerateGem() // камни
{
	string itemID;
	switch(rand(5))
	{
		case 0:
			itemID = "jewelry1";
		break;
		case 1:
			itemID = "jewelry2";
		break;
		case 2:
			itemID = "jewelry3";
		break;
		case 3:
			itemID = "jewelry3";
		break;
		case 4:
			itemID = "jewelry5";
		break;
		case 5:
			itemID = "jewelry17";
		break;
	}
	return itemID;
}

string findTraderCity_PU(ref NPChar)
{
	int n, nation;
	int storeArray[MAX_COLONIES];
	int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //на свой остров
		{
			nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
			if(nation != RELATION_ENEMY)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
}

string findPassangerCity_PU(ref NPChar)
{
	int n, nation;
	int storeArray[MAX_COLONIES];
	int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].nation != "none" && colonies[n].id != "Panama" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[cRand(howStore-1)];
	return colonies[nation].id;
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
