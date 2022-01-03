#include "DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
#include "interface\ship.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Tavern.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	int iTest, iTemp;
	string sTemp;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	bool ok;
	ref FortChref = GetFortCommander(NPChar.City);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase("В городе поднята тревога, тебя всюду ищут! На твоем месте я бы не стал здесь задерживаться.", "Вся городская стража рыщет по городу в поисках тебя. Я не идиот и разговаривать с тобой не буду!", "Беги, "+ GetSexPhrase("приятель","подруга") +", пока солдаты не сделали из тебя решето..."),
					LinkRandPhrase("Что тебе нужно, "+ GetSexPhrase("негодяй","мерзавка") +"?! Городская стража уже взяла твой след, далеко тебе не уйти"+ GetSexPhrase(", грязный пират!","") +"", "Грязн"+ GetSexPhrase("ый","ая") +" убийца, вон из моего дома! Стража!!", "Я не боюсь тебя, мерзав"+ GetSexPhrase("ец","ка") +"! Скоро тебя повесят в нашем форте, далеко тебе не уйти..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Хех, тревога для меня не проблема...", "Им меня ни за что не поймать."),
					RandPhraseSimple("Заткни свою пасть, " + GetWorkTypeOfMan(npchar, "") + ", а не то вырву твой поганый язык!", "Хех, " + GetWorkTypeOfMan(npchar, "") + ", а все туда же - пиратов ловить! Вот что я тебе скажу, приятель: сиди тихо и будешь жить..."));
				link.l1.go = "exit";
				break;
			}
            // homo линейка капитана Блада
            if (Pchar.questTemp.CapBloodLine == true )
            {
                dialog.Text = LinkRandPhrase("Эй, доктор Блад! " + TimeGreeting() + ".",
                                    "Рад видеть Вас, Питер Блад.",
                                    "Хорошо, что Вы заглянули ко мне, " + GetFullName(pchar) + ". Как поживает полковник Бишоп?");
                Link.l1 = "Увы, я уже ухожу, " + NPChar.name + ". До встречи.";
				Link.l1.go = "exit";

                if(Pchar.questTemp.CapBloodLine.stat == "WakerOffer")
                {
            		link.l2 = "Не подскажешь ли, дружище " + NPChar.name + ", как найти доктора Вакера?";
            		link.l2.go = "TStep_0";
                }

                if(Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape")
                {
            		link.l2 = "У меня к вам одно деликатное дело.";
            		link.l2.go = "TStep_1";
                }

                if(Pchar.questTemp.CapBloodLine.stat == "needMoney" && CheckAttribute(pchar, "questTemp.CapBloodLine.QuestRaff") && pchar.questTemp.CapBloodLine.QuestRaff == true)
                {
            		link.l2 = "Меня интересует человек по имени Рафаэль Гиннес. Как мне его найти?";
            		link.l2.go = "TStep_5";
                }
                break;
    		}

			if (drand2(100)==0 && sti(pchar.rank) >= 20 && GetCharacterItem(Pchar, "map_full") <= 0)
			{
				if (!CheckAttribute(pchar,"questTemp.UniquePirate.Barbarigo") || !CheckAttribute(pchar,"questTemp.UniquePirate.BlackBeard") || !CheckAttribute(pchar,"questTemp.UniquePirate.Levasser"))
				{
					dialog.text = "Капитан, у меня тут завалялась карта сокровищ, наверняка очень ценная. Интересует?";
					link.l1 = "Само собой! Сколько просишь?";
					link.l1.go = "SpecialMapBuy";
					link.l2 = "Обойдусь, пожалуй. Мало ли чья мазня, вдруг вообще подделка.";
					link.l2.go = "exit";
					break;
				}
			}

			//зачарованный город -->
			if (pchar.questTemp.MC == "toCaracas" && npchar.city == "Caracas")
			{
				dialog.text = "Ради Бога, капитан, спасите! Они все, все погубят! Мою таверну!";
				link.l1 = "Это ты оборотень, что ли?";
				link.l1.go = "MCTavern";
				break;
			}
			if (pchar.questTemp.MC == "toCaracasWervolf" && npchar.city == "Caracas")
			{
				dialog.text = "Капитан, вы общали пойти к оборотню...";
				link.l1 = "Я помню.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.MC == "toCaracasPadre" && npchar.city == "Caracas")
			{
				dialog.text = "Ну, что скажете, капитан? Вы нашли его?";
				link.l1 = "Наш"+ GetSexPhrase("ел","ла") +". Но сейчас не время разговаривать, позже все расскажу...";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.MC == "toCaracasTavern" && npchar.city == "Caracas")
			{
				dialog.text = "Капитан, рад вас видеть!";
				link.l1 = "Что случилось с этим вашем постояльцем?";
				link.l1.go = "MCCaracasAfter";
				break;
			}
			//<-- зачарованный город

			if(NPChar.quest.meeting == "0")
			{
				if (npchar.city == "Pirates")
				{
					dialog.Text = "Ба, вот и еще "+ GetSexPhrase("один лихой капитан","одна отважная морячка") +" на огонек пожаловал"+ GetSexPhrase("","а") +"! Располагайтесь, судар"+ GetSexPhrase("ь","ыня") +". Меня зовут Лаки Росин, и я всегда к вашим услугам. Погодка сегодня радует, не правда ли? Желаете рому?";
					Link.l1 = "Как ты сказал тебя зовут? Ла Керосин? Вот уж не думал"+ GetSexPhrase("","а") +", что среди пиратов есть кастильцы!";
					Link.l1.go = "Pirates_1";
					NPChar.quest.meeting = "1";
					break;
				}
				if (npchar.city == "Charles")
				{
					dialog.Text = "Добро пожаловать, " + GetAddress_Form(NPChar) + ". Еда, выпивка и развлечения - все по умеренным ценам! Меня зовут " + GetFullName(npchar) + ". Я владелец этой таверны.";
					Link.l1 = "Одноглазый Стид? Я слышал"+ GetSexPhrase("","а") +" о тебе. Люди поговаривают, что в недавнем прошлом ты прославился охотой за испанскими галеонами. Что-то с трудом верится...";
					Link.l1.go = "Charles_1";
					NPChar.quest.meeting = "1";
					break;
				}
				if (npchar.city == "Portobello")
				{
					dialog.Text = "Добро пожаловать, " + GetAddress_Form(NPChar) + ". Еда, выпивка и развлечения - все по умеренным ценам! Меня зовут " + GetFullName(npchar) + ", но более известен, как Каталонский Лис. Я владелец этой таверны.";
					Link.l1 = "Каталонский Лис? Слыхал"+ GetSexPhrase("","а") +" я о тебе. Люди говорят, что ты однажды здорово порастряс англичан на Барбадосе - на какой-то лоханке захватил в гавани Барбадоса военный бриг и угнал его буквально из-под носа у форта.";
					Link.l1.go = "Portobello_1";
					NPChar.quest.meeting = "1";
					break;
				}
				dialog.Text = "Добро пожаловать, " + GetAddress_Form(NPChar) + ". Еда, выпивка и развлечения - все по умеренным ценам!";
				Link.l1 = "Посмотрим... Я " + GetFullName(pchar) + ".";
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
			}
			else
			{
				// Квестовый генератор священника. Квест №1. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
		        {
		            if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToBarmen"))
		            {
		            	iTemp = sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen);
		            	dialog.Text = "Ну что кэп, вы принесли мне " + FindRussianMoneyString(iTemp) + ".";
		            	if(sti(PChar.Money) >= iTemp)
		            	{
							link.l1 = "Да, принес"+ GetSexPhrase("","ла") +". Вот они...";
							link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
						}
						else
						{
							link.l1 = "Нет, еще не принес"+ GetSexPhrase("","ла") +"...";
							link.l1.go = "exit";
						}
		            }
		            else
		            {
		            	dialog.Text = "Чего изволите, милостив"+ GetSexPhrase("ый господин","ая госпожа") +"?";
						link.l1 = "Бутылку рома моему приятелю, вон за тем столиком.";
						link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
					}
					break;
				}
				// <-- Квестовый генератор священника. Квест №1.

				////////////////
				//Линейка Виспер
				////////////////
				if(startherotype == 2 && CheckAttribute(pchar, "Whisper.FindDesouza") && !CheckAttribute(pchar,"Whisper.Contraband") && sti(pchar.money) >= 10000 && npchar.nation!=3)
				{
					bool Whisper_cnd = GetCharacterSkill(pchar,SKILL_SAILING)>= 65 && pchar.rank >=5 && GetCharacterShipClass(PChar) <= 4;
					if (pchar.rank >=10 || Whisper_cnd)
					{
						dialog.Text = "Капитан, не стоит разгуливать в таком виде. Я слыхал инквизиция рыщет в поисках девушки с таким же цветом волос. Тебе бы прикрыться, что ли.";
						DeleteAttribute(pchar, "Whisper.FindDesouza")
						Link.l1 = "Это от кого ты такое услышал?";
						Link.l1.go = "w_find_desouza";
						break;
					}
				}
				if(CheckAttribute(pchar, "Whisper.NanoCostume") && !CheckAttribute(pchar, "Whisper.AfterWarDog") && sti(RealShips[sti(pchar.Ship.Type)].BaseType) == SHIP_WH_CORVETTE_QUEST && npchar.id != "Pirates_tavernkeeper")
				{
					pchar.Whisper.AfterWarDog = true;
					dialog.Text = "Приветствую. Это ведь ваш корвет причалил недавно к нам в порт?";
					Link.l1 = "Ну допустим мой, тебе то что?";
					Link.l1.go = "w_meet_esteban_friend";
					break;
				}
				// <-- Линейка Виспер
				// ЧП
				if(GetQuestPastDayParam("BSPrologueEnded") > (7) &&  sti(pchar.rank) >= 30 && sti(npchar.nation) == PIRATE && npchar.id != "Pirates_tavernkeeper" && !CheckAttribute(pchar,"BSOnTheHorizon"))
				{
					pchar.BSOnTheHorizon = true;
					dialog.text = "Эй, а не тебя ли разыскивает наша надежда и опора, светлоликая мисс Гатри?";
					link.l1 = "О Боже! Что на этот раз?";
					link.l1.go = "BS_CPNG_2";
					break;
				}
				// ЧП

				dialog.Text = LinkRandPhrase("Эй, " + GetAddress_Form(NPChar) + " " + PChar.name + "! " + TimeGreeting() + ".",
                                    "О, какие у нас гости! Рад видеть вас, " + GetAddress_Form(NPChar) + " " + PChar.name + ".",
                                    "Хорошо, что вы заглянули ко мне, " + GetFullName(pchar) + ". Каков будет сегодня ваш заказ?");
				Link.l1 = "Есть на острове парни, готовые уйти в плавание?";
				Link.l1.go = "crew hire";
				Link.l2 = "Я надеюсь, ты сможешь ответить на пару вопросов.";
				Link.l2.go = "int_quests";
				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = "Слушай, нам нужно поговорить о финансовых делах.";
					link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
				}


				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
		            	{
					link.l10 = LinkRandPhrase("Ты что-нибудь можешь сказать об недавнем ограблении церкви?", "Что ты знаешь об недавнем ограблении местной церкви?", "Ты что-нибудь слышал об недавнем ограблении местной церкви?");
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				link.l3 = pcharrepphrase("Есть ли в твоем клоповнике свободная конура?", "Нет ли у тебя свободной комнаты, я хотел"+ GetSexPhrase("","а") +" бы остановиться здесь на некоторое время.");
				link.l3.go = "room";
				Link.l4 = "Увы, я уже ухожу, " + NPChar.name + ". До встречи.";
				Link.l4.go = "exit";
			}
		break;

		case "BS_CPNG_2":
            dialog.text = "Понятия не имею. Но её посыльный очень убедительно просил передать капитану "+pchar.name+", что "+ GetSexPhrase("его","её") +" ждут в магазине Бермуд. И на месте этого капитана, я бы не стал медлить.";
            link.l1 = "Хорошо, я понял"+ GetSexPhrase("","а") +".";
			link.l1.go = "exit";
			SetQuestHeader("BSOnTheHorizon");
			AddQuestRecord("BSOnTheHorizon", "1");

			PChar.quest.BSOnTheHorizon_start.win_condition.l1 = "location";
			PChar.quest.BSOnTheHorizon_start.win_condition.l1.location = "Pirates_town";
			PChar.quest.BSOnTheHorizon_start.function = "BSOnTheHorizon_start";
		break;

		case "SpecialMapBuy":
			pchar.questTemp.SpecialMapPrice = 100000+drand(50000);
			aref item;
			Items_FindItem("map_full", &item);
			string type = GetUniquePirateName();
			FillMapForUniqueTreasure(item, type);
			type = GetUniquePirateNameString(type);
			dialog.Text = "Дешевле, чем за "+pchar.questTemp.SpecialMapPrice+" пиастров не уступлю. По слухам, это карта сокровищ самого "+type+". Если бы не таверна, может и попробовал бы снарядить команду на поиски.";
			if (sti(pchar.money)>sti(pchar.questTemp.SpecialMapPrice))
			{
				link.l1 = "Карамба, славная однако цена. Что-ж, беру.";
				link.l1.go = "SpecialMapBuy_1";
			}
			link.l2 = "За такую-то цену? Нашёл "+GetSexPhrase("дурака.","дурочку.")+" Бывай!";
			link.l2.go = "exit";
		break;

		case "SpecialMapBuy_1":
			AddMoneyToCharacter(pchar,-sti(pchar.questTemp.SpecialMapPrice));
			GiveItem2Character(pchar, "map_full");
			dialog.Text = "Держите, надеюсь оно будет того стоить. Удачного кладоискательства, капитан!";
			link.l1 = "Благодарю.";
			link.l1.go = "exit";
		break;

		case "Meeting":
			// Квестовый генератор священника. Квест №1. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
	        {
	            dialog.Text = "Чего изволите, милостив"+ GetSexPhrase("ый господин","ая госпожа") +"?";
				link.l1 = "Бутылку рома моему приятелю вон за тем столиком.";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
				break;
			}
			// <-- Квестовый генератор священника. Квест №1.
			if (npchar.city == "Pirates")
			{
				dialog.Text = "О, да не берите так близко к сердцу мои слова, " + GetAddress_Form(NPChar) + ". Я люблю поворчать, да на жизнь иногда пожаловаться... Ну, слушаю вас внимательно, капитан.";
				Link.l1 = "Мне нужна команда, " + NPChar.name + ".";
				Link.l1.go = "crew hire";
				Link.l2 = NPChar.name + ", давай поговорим...";
				Link.l2.go = "int_quests";

				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = "Слушай, нам нужно поговорить о финансовых делах.";
					link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
				}

				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
				{
					link.l10 = LinkRandPhrase("Ты что-нибудь можешь сказать об недавнем ограблении церкви?", "Что ты знаешь об недавнем ограблении местной церкви?", "Ты что-нибудь слышал об недавнем ограблении местной церкви?");
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}

				// <-- Квестовый генератор священника. Квест №2.
				link.l3 = pcharrepphrase("Есть ли в твоем клоповнике свободная конура?", "Нет ли у тебя свободной комнаты, я хотел"+ GetSexPhrase("","а") +" бы остановиться здесь на некоторое время.");
				link.l3.go = "room";
				Link.l4 = "Пожалуй, загляну к тебе попозже.";
				Link.l4.go = "exit";
				break;
			}

			if (npchar.city == "Charles")
			{
				dialog.Text = "Да я в общем-то всегда рад поговорить с приятным собеседником... Ну, так что вы хотели, " + GetAddress_Form(NPChar) + "?";
				Link.l1 = "Мне нужна команда, " + NPChar.name + ".";
				Link.l1.go = "crew hire";
				Link.l2 = NPChar.name + ", давай поговорим...";
				Link.l2.go = "int_quests";
				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = "Слушай, нам нужно поговорить о финансовых делах.";
					link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
				{
					link.l10 = LinkRandPhrase("Ты что-нибудь можешь сказать об недавнем ограблении церкви?", "Что ты знаешь об недавнем ограблении местной церкви?", "Ты что-нибудь слышал об недавнем ограблении местной церкви?");
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				link.l3 = pcharrepphrase("Есть ли в твоем клоповнике свободная конура?", "Нет ли у тебя свободной комнаты, я хотел"+ GetSexPhrase("","а") +" бы остановиться здесь на некоторое время.");
				link.l3.go = "room";
				Link.l4 = "Пожалуй, загляну к тебе попозже.";
				Link.l4.go = "exit";
				break;
			}

			if (npchar.city == "Portobello")
			{
				dialog.Text = "О, я всегда рад поболтать, дружище. Ведь теперь вы мой друг, знайте это, " + GetAddress_Form(NPChar) + ". Что вы желаете?";
				Link.l1 = "Мне нужна команда, " + NPChar.name + ".";
				Link.l1.go = "crew hire";
				Link.l2 = NPChar.name + ", давай поговорим...";
				Link.l2.go = "int_quests";

				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = "Слушай, нам нужно поговорить о финансовых делах.";
					link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
				{
					link.l10 = LinkRandPhrase("Ты что-нибудь можешь сказать об недавнем ограблении церкви?", "Что ты знаешь об недавнем ограблении местной церкви?", "Ты что-нибудь слышал об недавнем ограблении местной церкви?");
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}

				// <-- Квестовый генератор священника. Квест №2.
				link.l3 = pcharrepphrase("Есть ли в твоем клоповнике свободная конура?", "Нет ли у тебя свободной комнаты, я хотел"+ GetSexPhrase("","а") +" бы остановиться здесь на некоторое время.");
				link.l3.go = "room";
				Link.l4 = "Пожалуй, загляну к тебе попозже.";
				Link.l4.go = "exit";
				break;
			}
			dialog.Text = "О, вы сами в этом убедитесь, " + GetAddress_Form(NPChar) + ". Меня зовут " + GetFullName(npchar) + ". Я владелец этой таверны.";
			Link.l1 = "Мне нужна команда, " + NPChar.name + ".";
			Link.l1.go = "crew hire";
			Link.l2 = NPChar.name + ", давай поговорим...";
			Link.l2.go = "int_quests";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l21 = "Слушай, нам нужно поговорить о финансовых делах.";
				link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
			}
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	        {
				link.l10 = LinkRandPhrase("Ты что-нибудь можешь сказать об недавнем ограблении церкви?", "Что ты знаешь об недавнем ограблении местной церкви?", "Ты что-нибудь слышал об недавнем ограблении местной церкви?");
				link.l10.go = "Tavern_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			link.l3 = pcharrepphrase("Есть ли в твоем клоповнике свободная конура?", "Нет ли у тебя свободной комнаты, я хотел"+ GetSexPhrase("","а") +" бы остановиться здесь на некоторое время.");
			link.l3.go = "room";
			Link.l4 = "Пожалуй, загляну к тебе попозже.";
			Link.l4.go = "exit";
		break;

		case "crew hire":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			ok = sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok;

			// здесь убираю условие
			if (!ok)
			{
				Dialog.text = "А на что тебе матросы? Что-то не вижу твоего корабля в порту.";
				link.l1 = RandPhraseSimple("Точно... я его пришвартовал"+ GetSexPhrase("","а") +" не в том месте.", "Забыл"+ GetSexPhrase("","а") +" войти в порт...");
				link.l1.go = "exit";
				break;
			}
			//здесь меняю дату
            if (makeint(environment.time) > 24.0 || makeint(environment.time) < 0.0)
			{
				Dialog.text = "Обычно у меня в таверне полно людей, желающих стать матросами, но сейчас слишком поздно, и они начнут появляться только утром. Может быть, вы хотите снять комнату, и подождать их?";
				link.l1 = "Хорошо. У тебя есть свободные комнаты?";
				link.l1.go = "room";
				link.l2 = "Меня не интересует комната на данный момент. До встречи.";
				link.l2.go = "exit";
			}
			else
			{
                if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
                {
                    Dialog.text = "А ты думаешь, к тебе кто-то пойдет, когда ты с нами во вражде? Скажи спасибо, что стражу не зову.";
					link.l1 = "Спасибо.";
					link.l1.go = "exit";
                }
                else
                {
					if (CheckAttribute(FortChref, "Fort.Mode") && sti(FortChref.Fort.Mode) == FORT_DEAD)
					{
						Dialog.text = "Cейчас нет никого. При недавнем штурме города большая часть желающих погибла, а меньшая затаилась так, что их сейчас не сыщешь.";
						link.l1 = "Эх, жаль!";
						link.l1.go = "exit";
						break;
					}
					if (CheckAttribute(NPChar, "CrewHired.PGGId") && GetNpcQuestPastDayParam(NPChar, "CrewHired") < 1 && GetCrewQuantity(rColony) == 0 && drand(100) > 90)
					{
						Dialog.text = "Извините, но сейчас нет никого. Все ушли с отважным кэпом " + GetFullName(CharacterFromID(NPChar.CrewHired.PGGId)) + ".";
						link.l1 = "Эх, жаль!";
						link.l1.go = "exit";
					}
					else
					{
						if(bPartitionSet)
						{
							if((Partition_GetSetting("Part_Crew") == 0) || GetPartitionAmount("CrewPayment") > 0)
							{
								dialog.text = "Капитан, поговаривают, что вы скуповаты. У меня нет желающих пойти в вашу команду.";
								link.l1 = "Понятно...";
								link.l1.go = "exit";
							}
							else
							{
								DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
								NextDiag.CurrentNode =  NextDiag.TempNode;
								DialogExit();
								LaunchHireCrew();
							}
						}
						else
						{
							DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
							NextDiag.CurrentNode =  NextDiag.TempNode;
							DialogExit();
							LaunchHireCrew();
						}
					}
				}
			}
		break;
	////////////////////////////////////////////////////////=============================================///////////////////////////////////////////////////////
        case "int_quests":
			dialog.text = "Я весь внимание.";
			link.l1 = "Я ищу работу. Не поможешь мне?";
			link.l1.go = "work";
			//homo 15/06/06 слухи
			link.l2 = LinkRandPhrase("Расскажи мне последние новости?","Что новенького в этих краях?",
                                    "Как течет жизнь на суше?");
			link.l2.go = "rumours_tavern";
			//homo
			link.l3 = "Я по другому делу.";
			link.l3.go = "quests";
			if (CheckAttribute(pchar, "GenQuest.SeekSpy.City")) //квест мэра по поиску шпиона
			{
				link.l4 = "Я действую по поручению губернатора. Скажи мне, ты не замечал никого подозрительного в последнее время в городе?";
				if (pchar.GenQuest.SeekSpy.City == "0")
				{
					link.l4.go = "SeekSpy_Seen";
				}
				else
				{
					link.l4.go = "SeekSpy_NotSeen";
				}
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "EncGirlFack_fighted")
				{
					link.l5 = "Не знаешь, где мне найти " + pchar.GenQuest.EncGirl.name +"?";
					link.l5.go = "EncGirl_1";
				}
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					link.l6 = "Не подскажешь, где мне искать " + pchar.GenQuest.EncGirl.sLoverId + "?";
					link.l6.go = "EncGirl_3";
				}
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "tavern_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l7 = "Здравствуйте, я приш"+ GetSexPhrase("ел","ла") +" по приглашению вашего сына.";
					link.l7.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
			}
			if(CheckAttribute(pchar,"QuestTemp.Andre_Abel_Quest_PortPax_TavernOwner_Speek"))
			{
				link.l8 = "Не подскажешь, где мне искать Андре Абеля?";
				link.l8.go = "Andre_Abel_Quest_TavernOwner_Dialog_1";
			}
			if(CheckAttribute(pchar,"GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.City && CheckAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern"))
			{
				if(pchar.GenQuest.CaptainComission.variant == "A0")
				{
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "Ну что, не заходил " + pchar.GenQuest.CaptainComission.Name + "?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{
						link.l9 = "Не подскажешь, где мне искать " + pchar.GenQuest.CaptainComission.Name + "?";
						link.l9.go = "CaptainComission_1";
					}
				}

				if(pchar.GenQuest.CaptainComission.variant == "A2" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					link.l9 = "Ты не знаешь, где я могу найти капитана патрульного " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + "?";
					link.l9.go = "CaptainComission_Tavern7";
				}
				if(pchar.GenQuest.CaptainComission.variant == "A3" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "Ну что, не заходил " + GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM) + "?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{
						link.l9 = "Ты что-нибудь знаешь, о капитане патрульного " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + "?";
						link.l9.go = "CaptainComission_Tavern1";
						if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
						{
							pchar.GenQuest.CaptainComission.GetRumour = true;
							SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
						}
					}
				}
			}
			if(CheckAttribute(pchar,"GenQuest.Hold_GenQuest") && NPChar.city == pchar.GenQuest.Hold_GenQuest.City && pchar.GenQuest.Hold_GenQuest.Speak_Tavern == false )
			{
				link.l10 = "Не подскажете, где мне найти господина по имени " + pchar.GenQuest.Hold_GenQuest.Name + "?";
				link.l10.go = "hold_genquest1";
			}
			if (CheckCharacterItem(pchar, "CaptainBook") && CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakTavern") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
			{
				link.l11 = "Я совершенно случайно неподалеку наш"+ GetSexPhrase("ел","ла") +" судовые документы....";
				link.l11.go = "ShipLetters_4";
			}

                        //ОЗГ
			if(CheckAttribute(pchar, "questTemp.Headhunter"))
			{
	    		if(pchar.questTemp.Headhunter == "hunt_carlos" && npchar.city == pchar.questTemp.Headhunter.City)
	    		{
	    			link.l12 = "Не подскажешь, где мне искать Карлоса Кассира?";
	    			link.l12.go = "Seek_Carlos";
	    		}
			}

			//zagolski. начальный квест пирата
			if(CheckAttribute(pchar, "questTemp.pirateStartQuest") && pchar.questTemp.pirateStartQuest == "1" && GetArealByCityName(npchar.city) == pchar.questTemp.pirateStartQuest.Areal && npchar.city != pchar.questTemp.pirateStartQuest.City)
			{
				if (!CheckAttribute(pchar, "questTemp.pirateStartQuest.TavernInfo"))
				{
					link.l12 = "Слушай, дружище, не подскажешь, у вас здесь никто рабами не приторговывает?";
					link.l12.go = "pirateStartQuest_Tavern";
				}
				else
				{
					if (sti(pchar.money) >= 500)
					{
						link.l12 = "Принес я тебе 500 пиастров. Говори что знаешь.";
						link.l12.go = "pirateStartQuest_Tavern_2";
					}
				}
			}
			//Lipsar квест История Давней дружбы--->
				if(CheckAttribute(Pchar,"Quest.Luke") && Pchar.Quest.Luke == "1" && NPChar.City == "LaVega")
				{
					link.l13 = "Послушай, я ищу человека, что сидел за столиком справа от двери. Ты не знаешь где он?";
					link.l13.go = "LukeQuest_1";
					sld = CharacterFromID("Maks");
					ChangeCharacterAddressGroup(sld,"none","none","none");
				}
				if(CheckAttribute(Pchar,"Luke.SpawnMaks") && Pchar.Luke.SpawnMaks == "1")
				{
					sld = CharacterFromID("Maks");
					if(NPChar.Location == sld.City)
					{
						link.l13 = "Послушай, я ищу человека, По имени Максимилиан Вебер. Ты не знаешь где он?";
						link.l13.go = "MaksQuest_1";
					}
				}
				//<---Lipsar квест История Давней дружбы

			link.l14 = "Ты случайно не владеешь информацией, как там дела у моих коллег на море?";
			link.l14.go = "PGGInfo";

			link.l15 = "Спасибо, ничего. До свидания.";
			link.l15.go = "exit";
		break;

		//-------------------------------------------
		case "PGGInfo":
			int rep = pchar.reputation;
			int repcheck = 40;
			if (IsCharacterPerkOn(pchar, "Adventurer"))
			{
				repcheck = 10;
			}

			if (rep <= repcheck)
			{
				dialog.text = "Знать-то может и знаю, но человеку с твоей репутацией такие сведения доверять нельзя. Так что проваливай с такими вопросами куда подальше, кэп!";
				link.l1 = "Ну и ладно, обойдусь!";
				link.l1.go = "exit";
			}
			else
			{
				int cost = 4000 + makeint(500 * sti(PChar.rank) * MOD_SKILL_ENEMY_RATE/2);
				if (IsCharacterPerkOn(pchar, "Agent"))
				{
					cost = makeint(cost/2);
				}
				dialog.text = "Хм, ну что ж, может что-то и знаю... Но это будет недёшево, кэп. Я попрошу с тебя за это "+cost+" и ни пиастром меньше! Устраивает?";
				if (sti(pchar.money) >= cost)
				{
					link.l1 = "Хорошо, вот твои деньги. Теперь говори что знаешь.";
					link.l1.go = "PGGInfo_2";
				}
				link.l2 = "Пожалуй как-нибудь потом.";
				link.l2.go = "exit";
			}
		break;

		case "PGGInfo_2":
			int cost1 = 4000 + makeint(500 * sti(PChar.rank) * MOD_SKILL_ENEMY_RATE/2);
			if (IsCharacterPerkOn(pchar, "Agent"))
			{
				cost1 = makeint(cost1/2);
			}
			AddMoneyToCharacter(pchar, -cost1);
			AddDialogExitQuestFunction("OpenPGGInformation");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "pirateStartQuest_Tavern":
			dialog.text = "Ну, ты наш"+ GetSexPhrase("ел","ла") +" у кого спросить! В соседнем поселении у пиратов такие дела решаются очень просто.";
			link.l1 = "Был"+ GetSexPhrase("","а") +"  я там. Сейчас у них ничего нет, а ждать я не могу - очень выгодная сделка срывается. У меня времени всего пару дней, потом уж и не нужно будет.";
			link.l1.go = "pirateStartQuest_Tavern_1";
		break;
		case "pirateStartQuest_Tavern_1":
			dialog.text = "Хм, ну что ж, может что-то и знаю... Но забесплатно говорить не буду, я благотворительностью не занимаюсь. Моя информация стоит 500 пиастров. Плати или уходи.";
			if (sti(pchar.money) >= 500)
			{
				link.l1 = "Хорошо, вот тебе 500 пиастров... Говори что знаешь.";
				link.l1.go = "pirateStartQuest_Tavern_2";
			}
			else
			{
				link.l1 = "У меня нет таких денег... Вернусь, когда раздобуду.";
				link.l1.go = "exit";
				pchar.questTemp.pirateStartQuest.TavernInfo = "";
			}
		break;
		case "pirateStartQuest_Tavern_2":
			AddMoneyToCharacter(pchar, -500);
			dialog.text = "Ну, не знаю. Дело это подсудное, поэтому никто напрямую тебе рабов не предложит. Плантаторы сами скупают, где только найти смогут. Разве что у контрабандистов поспрашивай. Но пираты этот бизнес давно к рукам прибрали, вряд ли кто решит открыто позариться на их монополию...";
			link.l1 = "Ясно. А не знаешь, шхуна 'Сентблу' недавно к вам в порт не заходила?";
			link.l1.go = "pirateStartQuest_Tavern_3";
		break;
		case "pirateStartQuest_Tavern_3":
			dialog.text = "'Сентблу'? Нет, точно не заходила. Да и название это мне не знакомо.";
			link.l1 = "Хорошо, спасибо. Ты мне здорово помог. До встречи.";
			link.l1.go = "exit";

			PChar.questTemp.pirateStartQuest = "2";
			pchar.questTemp.pirateStartQuest.City2 = npchar.city;
			DeleteAttribute(pchar, "questTemp.pirateStartQuest.TavernInfo");
			AddQuestRecord("pSQ", "2");
			AddQuestUserData("pSQ", "sCity2", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City2 + "Gen"));
		break;


		case "hold_genquest1":
			switch(sti(pchar.GenQuest.Hold_GenQuest.TavernVariant))
			{
				case 0:
					dialog.text = LinkRandPhrase("Как вы говорите? " + pchar.GenQuest.Hold_GenQuest.Name + "? Хм, никогда не слыхал о таком.",
						"Вы точно знаете, что он именно из нашего поселения? Просто не слыхивал о таком ни разу.",
						"В нашем поселении такого отродясь не было. Сколько здесь живу - не слышал.");
					link.l1 = "А вы уверены?";
					link.l1.go = "hold_genquest2";
				break;

				case 1:
					switch (drand(3))
					{
						case 0:
							pchar.GenQuest.Hold_GenQuest.foundStr = "в церковь";
							pchar.GenQuest.Hold_GenQuest.found = "church";
						break;
						case 1:
							if (npchar.city != "Panama")
							{
								pchar.GenQuest.Hold_GenQuest.foundStr = "на верфь";
								pchar.GenQuest.Hold_GenQuest.found = "shipyard";
							}
							else
							{
								pchar.GenQuest.Hold_GenQuest.foundStr = "в церковь";
								pchar.GenQuest.Hold_GenQuest.found = "church";
							}
						break;
						case 2:
							pchar.GenQuest.Hold_GenQuest.foundStr = "к ростовщику";
							pchar.GenQuest.Hold_GenQuest.found = "bank";
						break;
						case 3:
							pchar.GenQuest.Hold_GenQuest.foundStr = "в магазин";
							pchar.GenQuest.Hold_GenQuest.found = "store";
						break;
					}
					dialog.text = "Зайдите " + pchar.GenQuest.Hold_GenQuest.foundStr + ", он там часто бывает.";
					link.l1 = "Спасибо, зайду непременно.";
					link.l1.go = "hold_genquest3";
				break;

				case 2:
					dialog.text = LinkRandPhrase(
						RandPhraseSimple("Как вы говорите? " + pchar.GenQuest.Hold_GenQuest.Name + "? Хм, никогда не слыхал о таком. А вы уверены, что он именно из нашего поселения?",
						"Э-хе-хе... разве один Господь Бог знает, где теперь его искать - то ли на небесах, то ли в преисподней. Помер он... уже второй год как помер, а всё о нём выспрашивают, вынюхивают, всё ему покоя не дают бедняге..."),
						RandPhraseSimple("Не найдёте вы его уже, на этом свете так точно. Не так давно помер он, от жёлтой лихорадки... Царствие ему небесное... А какой крепкий мужик был! В молодости, рассказывают, такие дела творил, что не приведи Господь! А поди ж ты - пришла невеста - и поминай, как звали...",
						"Эк, хватились! Он съехал давно уж. Не то к детям подался, не то в Европу - никому не известно. Просто собрал пожитки и смотался."),
						"А-а, это не того ли " + pchar.GenQuest.Hold_GenQuest.Name + " вы ищете, что вдруг разбогател и купил себе дом в Новом Альбионе? А ведь были времена, когда я его в долг ромом потчевал! Он и по сей день мне должен остался. Так поди ж ты - достань его теперь! Нет, не помнят люди добра...");
					link.l1 = "Ясно. Ну, спасибо и на этом.";
					link.l1.go = "hold_genquest4";
				break;

				case 3:
					dialog.text = "А где же его искать, если не у нас в таверне? Он здесь частенько появляется - ромом старые грехи заливает, хе-хе. Вы зайдите попозже, если он появится, я скажу, чтоб вас дождался.";
					link.l1 = "Спасибо, зайду.";
					link.l1.go = "hold_genquest5";
				break;
			}
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = true;
		break;

		case "hold_genquest2":
			dialog.text = "Как же не быть уверенным-то, если я всех здешних поселенцев, как одного знаю. Чай не первый год таверну держу. "+
				"Я их всех в разных видах видывал - кого жена домой тащит, кто всегда сам с полным трюмом в гавань добирается, а кого и взашей выставлять приходилось. А вы мне - 'уверены'!";
			link.l1 = "Ну ладно, спасибо и на этом...";
			link.l1.go = "exit";
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			AddQuestRecord("HoldQuest", "7");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;

		case "hold_genquest3":
			Hold_GenQuest_GenerateChar();
			AddQuestRecord("HoldQuest", "8");
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Gen"));
			AddQuestUserData("HoldQuest", "sFoundChar", pchar.GenQuest.Hold_GenQuest.foundStr);
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.Name);
			SetFunctionTimerConditionParam("Hold_GenQuest_FindCharTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
		break;

		case "hold_genquest4":
			AddQuestRecord("HoldQuest", "13");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("ел","ла"));
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");
			DialogExit();
		break;

		case "hold_genquest5":
			SetFunctionTimerConditionParam("Hold_GenQuest_GetMapTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_GenerateMapChar");
		break;

		case "CaptainComission_1":
			dialog.text = LinkRandPhrase("Он частенько сюда заходит, но сейчас что-то не видно. Заглядывайте ко мне время от времени, если он появится, я скажу, чтоб вас дождался.","Он часто здесь бывает. Если вы зайдёте позже, то наверняка его застанете.","Заходите время от времени, он здесь часто появляется. Я передам, что вы его искали.");
			link.l1 = "Спасибо, зайду попозже...";
			link.l1.go = "CaptainComission_2";
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
		break;

		case "CaptainComission_2":
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1.location = pchar.location;
			pchar.quest.CapComission_ExitFromTavern.function = "CaptainComission_GenerateChar";

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "CaptainComission_3":
			dialog.text = "Заходил. Должен сидеть где-то здесь...";
			link.l1 = "Спасибо.";
			link.l1.go = "exit";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
		break;

		case "CaptainComission_Tavern1":
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
			dialog.text = "Кто же о нём не знает? Вот уже который день в поселении только об этом и судачат.";
			link.l1 = "Можешь рассказать подробнее?";
			link.l1.go = "CaptainComission_Tavern2";
		break;

		case "CaptainComission_Tavern2":
			dialog.text = "В общем, казнили этого капитана вместе с частью его команды, другую часть рассеяли по архипелагу, лишив выслуги и чинов... За что? В обвинительном приговоре перед казнью зачитали, что он во время патрулирования якобы пустил ко дну проходящее в акватории судно, а товар из его трюма спрятал.\n"+
				"Но верится в это с трудом, потому что, ни владельца судна этого, ни товар так и не нашли... До сих пор все бухты прочёсывают.";
			link.l1 = "что, никто из команды не признался, где тайник?";
			link.l1.go = "CaptainComission_Tavern3";
		break;

		case "CaptainComission_Tavern3":
			dialog.text = "Ни один!.. Не возьму в толк, почему губернатор так легко поверил этому поклёпу? Ведь капитан " + pchar.GenQuest.CaptainComission.Name + " был на хорошем счету, а как команду держал - любой адмирал позавидует, уж поверьте моему слову.";
			link.l1 = "А где мне искать оставшихся в живых членов команды?";
			link.l1.go = "CaptainComission_Tavern4";
		break;

		case "CaptainComission_Tavern4":
			dialog.text = "Ну, этого уж я не знаю, увезли их всех... Хотя нет, один остался, но толку от него вам вряд ли будет. Он контуженый, канониром был у " + pchar.GenQuest.CaptainComission.Name + ". Его нашли без сознания в какой-то бухте спустя два дня после того злополучного случая. Сначала в госпиталь определили, как героя, а когда дело приняло другой оборот - посадили в каземат и пытались допрашивать, но потом решили, что всё-таки нужно лечить.";
			link.l1 = "Так он сейчас в поселении?";
			link.l1.go = "CaptainComission_Tavern5";
		break;

		case "CaptainComission_Tavern5":
			pchar.GenQuest.CaptainComission.CanoneerName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Да, " + GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM) + " его зовут, иногда сюда заходит, ром выпрашивает. Если я его увижу, скажу - чтоб вас дождался.";
			link.l1 = "Спасибо, я позже наведаюсь.";
			link.l1.go = "CaptainComission_Tavern6";
		break;

		case "CaptainComission_Tavern6":
			AddQuestRecord("CaptainComission2", "39");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ABL));
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			SetFunctionExitFromLocationCondition("CaptainComission_GenerateCanoneer", pchar.location, false);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "CaptainComission_Tavern7":
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
			dialog.text = "Как не знать? Знаю конечно. А вам он на что?";
			link.l1 = "Дело у меня к нему.";
			link.l1.go = "CaptainComission_Tavern8";
		break;

		case "CaptainComission_Tavern8":
			dialog.text = "Вы бы, " + GetAddress_Form(pchar) + ", поосторожнее с этим 'делом'. " + pchar.GenQuest.CaptainComission.Name + " схвачен по подозрению в служебном преступлении, и сейчас по всему острову рыщут губернаторские ищейки в поисках его сообщников.";
			link.l1 = "Однако... А что он такое натворил?";
			link.l1.go = "CaptainComission_Tavern9";
		break;

		case "CaptainComission_Tavern9":
			dialog.text = "Не знаю насколько это правда, но говорят, что он спрятал груз, который конфисковал у проходящего мимо пиратского судна. Только вот ни пирата, ни груза найти никому не удалось. Не возьму в толк, почему губернатор так легко поверил этому поклёпу? Ведь капитан " + pchar.GenQuest.CaptainComission.CapName + " был на хорошем счету, и вояка он отменный, уж поверьте моему слову, " + GetAddress_Form(pchar) + ".";
			link.l1 = "Ну, спасибо, что предупредил. Всего хорошего.";
			link.l1.go = "CaptainComission_Tavern10";
		break;

		case "CaptainComission_Tavern10":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
			{
				pchar.GenQuest.CaptainComission.GetRumour = true;
				SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
				SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 2, MakeInt(24 - GetHour()), false);
				AddQuestRecord("CaptainComission2", "19");
				AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")));
				AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			}
			DialogExit();
		break;

		case "EncGirl_1":
			dialog.text = "А вам она зачем понадобилась?";
			link.l1 = "Дело к ней есть...";
			link.l1.go = "EncGirl_2";
		break;

		case "EncGirl_2":
			dialog.text = "У половины мужиков нашего поселения к ней дело есть. Если бы женщины её поймали, то голышом вышвырнули бы за городские ворота.";
			link.l1 = "М-да. "+ GetSexPhrase("Похоже, я стал в хвост длинной очереди. Если её кто будет спрашивать, скажи, пусть занимает за мной","Понятно") +"...";
			link.l1.go = "exit";
			pchar.quest.EncGirl_SpeakTavernKeeper.over = "yes";
			DeleteAttribute(pchar, "GenQuest.EncGirl");
		break;

		case "EncGirl_3":
			dialog.text = "Он частенько сюда заходит в надежде подыскать работу, но сейчас что-то не видно. Заглядывайте ко мне время от времени, если он появится, я скажу, чтоб вас дождался.";
			link.l1 = "Спасибо, зайду попозже...";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "FindingLover";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitTavern.function = "EncGirl_GenerateLover";
		break;

		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "А, так вы и есть "+ GetSexPhrase("тот капитан, который привёз","та девушка, которая привезла") +" моего блудного сына с молодой невестой?";
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

		case "ShipLetters_4":
			pchar.questTemp.different.GiveShipLetters.speakTavern = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Дайте-ка взглянуть ! Хм... Вы же сами - капитан. Думаю, Вам стоит зайти к начальнику порта.";
				link.l1 = "Спасибо за совет.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Дайте-ка взглянуть! О! Судя по имени, они принадлежат одному моему постоянному посетителю, весьма достойному человеку. Я могу сам передать документы владельцу.";
				link.l1	= "Пожалуй, нет ...";
				link.l1.go = "exit";
				link.l2 = "Рад"+ GetSexPhrase("","а") +", что смог"+ GetSexPhrase("","ла") +" быть ему полез"+ GetSexPhrase("ен","на") +".";
				link.l2.go = "ShipLetters_end";
			}
		break;

		case "ShipLetters_end":
			TakeItemFromCharacter(pchar, "CaptainBook");
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер
			AddQuestRecord("GiveShipLetters", "3");
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//эскорт-пассажиры
		case "work":
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
		{
			if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
				dialog.text = RandPhraseSimple("Мне без разницы кого обслуживать - деньги не имеют национальности. Но вот помогать тебе я не стану, так как ты приш"+ GetSexPhrase("ел","ла") +" под флагом " + NationNameGenitive(sti(pchar.nation)) + ".", "Я всего лишь простой хозяин таверны, но сотрудничать с " + NationNameAblative(sti(pchar.nation)) + " никакого желания не имею.");
				link.l1 = RandPhraseSimple("Хм, твое право...", "Ну, как знаешь...");
				link.l1.go = "exit";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				dialog.text = RandPhraseSimple("Пассажиров обычно хватает. Только вряд ли среди них найдется такой простофиля, чтобы решился путешествовать на твоем судне. Дурная слава бежит впереди тебя, а репутацию честного капитана еще заслужить нужно.", "Ко мне часто обращаются торговцы, которым нужно сопровождение. Но дурная слава ходит за тобой по пятам, и я никому не стану рекомендовать твои услуги. Мне своя репутация дороже.");
				link.l1 = RandPhraseSimple("Да ты верь поменьше разным сплетням...", "Да уж, всем рты не позатыкаешь...", "Эх, трусоватый нынче народец пошел...");
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Работа найдется, если не боишься ходить в пиратские поселения или в порты вражеских наций. Ко мне обычно только за этим и обращаются - то купцы сопровождение ищут, то пассажиры, которые в портовое управление идти не решаются. Что-то конкретное интересует?";
			link.l1 = "Ну, это не страшно. Я бы взял"+ GetSexPhrase("ся","ась") +" за эскорт.";
			link.l1.go = "work_1";
			link.l2 = "Пассажиры есть? Отвезу, хоть к черту в зубы, лишь бы деньги платили.";
			link.l2.go = "work_2";
			link.l3 = "Нет, такая работа не по мне. Спасибо.";
			link.l3.go = "exit";
		}
		else
		{
		dialog.text = "А корабль твой где? Поставь свое судно к пирсу, тогда и о работе поговорим.";
		link.l1 = "Хм, и то верно...";
		link.l1.go = "exit";
		}
		break;

		case "work_1":
			if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") >= 1 || bBettaTestMode)
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
						dialog.text = "Хм, но для эскорта у тебя слишком большая эскадра. Тебе бы свои корабли не растерять, а не то, чтоб чужие сберечь.";
						link.l1 = "Да ладно тебе, свои-то я не растеряю, разве что продать парочку... Ладно, зайду позже, если надумаю.";
						link.l1.go = "exit";
					}
					else
					{
						if (drand(8) > 1)
						{
							if (!CheckAttribute(PChar, "QuestTemp.AndreAbelQuest_StartQuest") && PChar.location == "FortFrance_tavern" && sti(pchar.rank) > 4) // не взята пиратская линейка
							{
								dialog.text = "Поговори вон с тем парнем, справа от лесницы. У него какие то проблемы";
								link.l1 = "Спасибо, вот я и наш"+GetSexPhrase("ел","ла")+" работу";
								link.l1.go = "exit";
								Log_TestInfo("Сопровождение флейта 'Орион' - сгенерился квестодатель в sit, sit7");
								PChar.QuestTemp.AndreAbelQuest_StartQuest = true;
								PChar.QuestTemp.AndreAbelQuest = true;

								// Потереть для начала новой игры -->
								sld = GetCharacter(NPC_GenerateCharacter("Andre_Abel" , "officer_19", "man", "man", 10, FRANCE, -1, true));
								FantomMakeCoolFighter(sld, 10, 30, 35, "blade9", "pistol2", 10);
								FantomMakeCoolSailor(sld, SHIP_FLEUT, "Орион", CANNON_TYPE_CANNON_LBS16, 30, 30, 30);
								sld.name = "Андре";
								sld.lastname = "Абель";
								sld.SaveItemsForDead = true; // сохранять на трупе вещи
								sld.DontClearDead = true; // не убирать труп через 200с
								sld.dialog.FileName = "Quest\Andre_Abel_Dialog.c";
								sld.greeting = "cit_quest";
								LAi_SetSitType(sld);
								LAi_SetImmortal(sld, true);	// До поры нельзя убить
								SetCharacterGoods(sld, GOOD_SILK, 700);
								SetCharacterGoods(sld, GOOD_TOBACCO, 500);
								FreeSitLocator("FortFrance_tavern", "sit7");
								ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "sit", "sit7");
								SetFunctionTimerCondition("Andre_Abel_Quest_1Day_Left", 0, 0, 1, false);
								// <-- Потереть для начала новой игры
							}
							else
							{
							dialog.text = "Ну, тогда поговори вон с тем типом, что в таверну зашел. Он сегодня о сопровождении спрашивал.";
							link.l1 = RandPhraseSimple("Ты его хорошо знаешь? Может, пират какой?", "А кто он такой? Стоит с ним дело иметь?");
							link.l1.go = "ConvoyAreYouSure";
							}
						}
            			else
            			{
            				dialog.text = "Сегодня, как назло, никто не подходил насчет сопровождения. Приходи через пару дней, может, кто и появится.";
							link.l1 = RandPhraseSimple("Ладно, на нет и суда нет.", "Да, не свезло... Ну ладно, прощай.");
							link.l1.go = "exit";
						}
            		}
                }
				else
				{
					dialog.text = "Ты что - караван собрать решил"+ GetSexPhrase("","а") +"? У тебя же есть сопровождаемый, сначала с ним закончи, потом уж другого ищи. Иначе не будешь знать, кого защищать в случае нападения.";
					link.l1 = RandPhraseSimple("Вот незадача... Ну ладно, всего хорошего.", "Да, действительно, не подумал"+ GetSexPhrase("","а") +". Ну ладно, прощай.");
					link.l1.go = "exit";
        		}
    		}
    		else
    		{
				dialog.text = "Сегодня уже никого нет. Заходите через пару дней.";
				link.l1 = "Хорошо. Как скажешь.";
                link.l1.go = "exit";
    		}
		break;

		case "work_2":
			if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") >= 1 || bBettaTestMode)
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
					dialog.Text = "Вон тип в таверну зашел, он недавно попутное судно спрашивал, куда-то добраться хотел. Если хочешь, переговори с ним.";
					link.l1 = RandPhraseSimple("А что за тип? Может проходимец какой, или в розыске?", "А кто он такой? Проблем с ним не будет?");
					Link.l1.go = "PassangerAreYouSure";
				}
				else
				{
					dialog.text = "Нет, сегодня ни один не спрашивал. Может, в другой день...";
					link.l1 = RandPhraseSimple("Ну нет, так нет. Чего уж тут...", "Да, не свезло... Ну ладно, прощайте.");
					link.l1.go = "exit";
				}
            }
    		else
    		{
				dialog.text = "Сегодня уже никого нет. Заходите через пару дней.";
				link.l1 = "Хорошо. Как скажешь.";
                link.l1.go = "exit";
    		}
        break;

        case "ConvoyAreYouSure":
		    dialog.text = LinkRandPhrase("Да кто ж его знает. Ты спросил"+ GetSexPhrase("","а") +" - я ответил.", "Ну, это уж тебе само"+ GetSexPhrase("му","й") +" решать. Я бы тут ни за кого не поручился.", "Решай сам"+ GetSexPhrase("","а") +", ко мне всякие захаживают. Это же таверна, а не резиденция губернатора.");
			Link.l1 = "Ну спасибо, сейчас поторгуемся.";
			Link.l1.go = "exit";
			pchar.quest.destination = findTraderCity(npchar);
			pchar.ConvoyQuest.City = npchar.city;
			AddDialogExitQuest("prepare_for_convoy_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

        case "PassangerAreYouSure":
		    dialog.text = LinkRandPhrase("Да кто ж его знает. Ты спросил"+ GetSexPhrase("","а") +" - я ответил.", "Ну, это уж тебе само"+ GetSexPhrase("му","й") +" решать. Я бы тут ни за кого не поручился.", "Решай сам"+ GetSexPhrase("","а") +", ко мне всякие захаживают. Это же таверна, а не резиденция губернатора.");
			Link.l1 = "Ясно, сейчас выясним что это за тип.";
			Link.l1.go = "exit";
			sGlobalTemp = findPassangerCity(npchar);
			pchar.GenQuest.GetPassenger_City = npchar.city;
			AddDialogExitQuest("prepare_for_passenger_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "room":
			//Квест Виспер
			if (CheckAttribute(pchar, "Whisper.EsFriendTown") && pchar.location == pchar.Whisper.EsFriendTown+"_tavern")
			{
				dialog.text = "Простите, капитан, но все места сейчас заняты.";
				link.l1 = "Жаль...";
				link.l1.go = "exit";
				break;
			}
			//Квест Виспер

			if (CheckAttribute(pchar,"ContraInterruptWaiting"))
			{
				dialog.text = "Простите, но я сейчас не могу сдать комнату. Буквально пару минут назад в таверну ворвалась толпа солдат и принялась обыскивать мои комнаты. Контрабандистов ищут, знаете ли. Только бизнес мне портят своими разборками... Приходите позже, капитан. ";
				if (sti(npchar.nation == PIRATE))
				{
					dialog.text = "Простите, но я сейчас не могу сдать комнату. Прошлый жилец решил устроить в ней бордель, или чего похуже. Кровать сломана, а запах как в свинарнике... Приходите позже, капитан.";
				}
				link.l1 = "Ясно.";
				link.l1.go = "exit";
				break;
			}

   			/*if (chrDisableReloadToLocation || CheckAttribute(pchar, "questTemp.different.Church_NightGuard")) //кто-то должен подойти к ГГ.
			{
				dialog.text = "Сейчас комната занята, " + GetAddress_Form(NPChar) + ", ничем не могу помочь.";
				link.l1 = "Жаль, очень жаль...";
				link.l1.go = "exit";
				break;
			}*/
			if (CheckAttribute(pchar, "questTemp.State.Open") && npchar.id == "Tortuga_tavernkeeper")//исп.линейка, квест №6, блокировка спать в комнате
			{
				dialog.text = "Вы заплатили мне за неделю вперед, я не могу брать у вас еще деньги. Комната ваша, идите и отдыхайте...";
				link.l1 = "Хорошо, приятель, спасибо.";
				link.l1.go = "exit";
				break;
			}
			//-->> квест официантки
			if (pchar.questTemp.different == "FackWaitress_toRoom")
			{
				dialog.text = "Вы хотите снять комнату? Не проблема. С вас 100 монет - и можете туда пройти.";
				if (sti(pchar.money) >= 100)
				{
					link.l1 = "Забирай свои деньги, открывай комнату, приятель...";
					link.l1.go = "exit";
					AddMoneyToCharacter(pchar, -100);
					LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
					pchar.questTemp.different = "FackWaitress_toRoomUp";
				}
				else
				{
					link.l1 = "Хм, я, пожалуй, подойду попозже...";
					link.l1.go = "exit";
				}
				break;
			}
			if (pchar.questTemp.different == "FackWaitress_toRoomUp")//квест официантки
			{
				dialog.text = "Комната ваша, идите и отдыхайте...";
				link.l1 = "Хорошо, приятель, спасибо.";
				link.l1.go = "exit";
				break;
			}
			//<<-- квест официантки
			// --> квест "Девица в джунглях"
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && npchar.city == pchar.GenQuest.EncGirl.city)
			{
				if(pchar.GenQuest.EncGirl == "EncGirl_ToTavern")
				{
					dialog.text = "Вы хотите снять комнату? Не проблема. С вас 50 монет - и можете туда пройти.";
					if (sti(pchar.money) >= 50)
					{
						link.l1 = "Забирай свои деньги, открывай комнату, приятель...";
						link.l1.go = "exit";
						AddMoneyToCharacter(pchar, -50);
						LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
						pchar.GenQuest.EncGirl = "EncGirl_toRoomUp";
					}
					else
					{
						link.l1 = "Хм, я, пожалуй, подойду попозже...";
						link.l1.go = "exit";
					}
					break;
				}
				if (pchar.GenQuest.EncGirl == "EncGirl_toRoomUp")//квест  по спасению тетки в пампасах
				{
					dialog.text = "Комната ваша, идите и отдыхайте...";
					link.l1 = "Хорошо, приятель, спасибо.";
					link.l1.go = "exit";
					break;
				}
			}
			// <-- квест "Девица в джунглях"
			dialog.text = "На какой срок вы планируете остановиться?";
			if(!isDay())
			{
				link.l1 = "До утра.";
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = "До ночи.";
				link.l1.go = "room_night";
				link.l2 = "До следующего утра.";
				link.l2.go = "room_day_next";
			}
		break;

		case "room_day":
			dialog.text = "Это обойдется вам в 5 золотых.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Идет. Вот твои деньги.";
				link.l1.go = "room_day_wait";
			}
			link.l2 = pcharrepphrase("Ты сдаешь королевские покои? Нет уж, за такую цену я лучше посижу в общей зале.",
            "Увы, видимо, такая роскошь, как сон на кровати, не для моего кошелька. Я переночую в общей зале.");
			link.l2.go = "hall_day_wait";
			link.l3 = "Не сейчас. Давай поговорим о чем-нибудь другом.";
			link.l3.go = "int_quests";
		break;

		case "room_day_next":
			dialog.text = "Это обойдется вам в 10 золотых.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Идет. Вот твои деньги.";
				link.l1.go = "room_day_wait_next";
			}
			link.l2 = pcharrepphrase("Ты сдаешь королевские покои? Нет уж, за такую цену я лучше посижу в общей зале.",
            "Увы, видимо, такая роскошь, как сон на кровати, не для моего кошелька. Я переночую в общей зале.");
			link.l2.go = "hall_day_wait";
			link.l3 = "Не сейчас. Давай поговорим о чем-нибудь другом.";
			link.l3.go = "int_quests";
		break;

		case "room_night":
			dialog.text = "Это обойдется вам в 5 золотых.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Идет. Вот твои деньги.";
				link.l1.go = "room_night_wait";
			}
			link.l2 = pcharrepphrase("Ты сдаешь королевские покои? Нет уж, за такую цену я лучше посижу в общей зале.",
            "Увы, видимо, такая роскошь, как сон на кровати не для моего кошелька. Я переночую в общей зале.");
			link.l2.go = "hall_night_wait";
			link.l3 = "Не сейчас. Давай поговорим о чем-нибудь другом.";
			link.l3.go = "int_quests";
		break;

		case "room_night_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "hall_night_wait":
			if (cRand(3) == 1)
            {
                Dialog.text = "Убирайся, оборван"+ GetSexPhrase("ец","ка") +"! Нечего тут в общей зале просиживать за бесплатно.";
				link.l1 = "Ладно, ладно... уже ухожу.";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_night");
			}
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;

		case "hall_day_wait":
			if (drand(1) == 1)
            {
                Dialog.text = "Убирайся, оборван"+ GetSexPhrase("ец","ка") +"! Нечего тут в общей зале просиживать за бесплатно.";
				link.l1 = "Ладно, ладно... уже ухожу.";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_day");
			}
		break;

		case "tavern_keeper":
			NextDiag.TempNode = "First time";

			dialog.text = "Уважаемые, прошу вас прекратить это безобразие в моей таверне, или я позову стражников!";
			link.l1 = "Ладно, ладно, я уже ухожу.";
			link.l1.go = "exit_sit";
		break;

		case "exit_sit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
		//==> eddy. квест мэра, вопросы не замечал ли шпиона
		case "SeekSpy_Seen":
			dialog.text = NPCStringReactionRepeat("Хм, дай подумать... Ты знаешь, есть один тип, который лично мне доверия не внушает. По виду обычный горожанин, но крутится то тут, то в городе шастает, вопросы у него странные. Сюда он вряд ли заявится - я его вчера отшил, а вот в городе поищи.",
				"Мы уже говорили на эту тему, более мне сказать тебе нечего.", "Опять то же самое... Я уже все тебе сказал.", "Сколько можно спрашивать об одном и том же?!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Спасибо, тебе, приятель. Что же, пойду искать этого типа.", "Хм, ну извини...",
                      "Хм, да уж...", "Извини, приятель...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		case "SeekSpy_NotSeen":
			dialog.text = NPCStringReactionRepeat("Нет, никого не видел, чтобы у меня подозрение вызывал.",
				"Мы уже говорили на эту тему, более мне сказать тебе нечего.", "Опять то же самое... Я уже все тебе сказал.", "Сколько можно спрашивать одно и то же?!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ну что же, и на этом спасибо, приятель.", "Хм, ну извини...",
                      "Хм, да уж...", "Извини, приятель...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		//==> homo линейка Блада
		case "TStep_0":
			dialog.text = "Вверх по лестнице. Я с тобой не разговаривал.";
			link.l1 = "Благодарю.";
			link.l1.go = "Exit";
			int n= FindLocation("Bridgetown_tavern");
            locations[n].reload.l2.disable = false;
		break;

		case "TStep_1":
			dialog.text = "Что за дело ко мне у вас, уважаемый доктор?";
			link.l1 = "Дело житейское... мне бы не помешали, на всякий случай, несколько абордажных сабель и пара пистолетов, дорогой друг. Вы ведь можете это устроить или указать на человека, который мог бы нечто подобное провернуть? Вы же знаете, в магазин мне идти нет смысла...";
			link.l1.go = "TStep_2";
		break;

		case "TStep_2":
			dialog.text = "Ну, разумеется, нет.";
			link.l1 = "Не можете? Или нет смысла?";
			link.l1.go = "TStep_3";
            if (makeint(pchar.money) >= 500)
            {
    			link.l1 = "Я разве не упомянул, что у меня для знающего человека найдется премия в размере... ну, скажем, трех сотен пиастров? Да и вспомните, как я лечил вашу дочь, не жалея своих сил и времени.";
    			link.l1.go = "TStep_4";
            }
		break;

		case "TStep_3":
			dialog.text = "Ничем не могу помочь, доктор.";
			link.l1 = "Всего наилучшего.";
			link.l1.go = "exit";
		break;

		case "TStep_4":
			dialog.text = "Конечно, у меня есть то, что вам нужно, доктор Блад. Мистер Гриффин, которому вы не так давно вправляли перелом, по жизни старый оружейник. Его дом находится неподалеку от поместья губернатора Стида - сходите к нему. Уверен, он не откажет вам.";
			link.l1 = "Всего наилучшего.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -300);
			Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape1";
			AddQuestRecord("WeaponsForEscape", "2");

		break;

		case "TStep_5":
            pchar.questTemp.CapBloodLine.QuestRaff = false;
			dialog.text = "Пожалуй, я припоминаю такого... или это был не он... вроде не он...";
            if (makeint(pchar.money) >= 200)
            {
    			link.l1 = "Две сотни освежат твои воспоминания?";
    			link.l1.go = "TStep_6";
            }
			link.l2 = "Так он или нет?";
			link.l2.go = "TStep_7";
		break;

		case "TStep_6":
            AddMoneyToCharacter(pchar, -200);
			dialog.text = "Еще бы! Конечно, это он! Заходил совсем недавно, говорил что-то про покупку корабля... я точно не знаю, какого и у кого.";
			link.l1 = "А что ты знаешь? Мне кажется, за 200 пиастров можно припомнить куда как больше подробностей, нежели просто тот факт, что он здесь бывал.";
			link.l1.go = "TStep_8";
		break;

		case "TStep_7":
			dialog.text = "Нет, увы... точно не он. Спутал - бывает.";
			link.l1 = "Досадно...";
			link.l1.go = "TStep_10";
		break;

		case "TStep_8":
			dialog.text = "Думаю, ты его найдешь на верфи, если поторопишься.";
			link.l1 = "Премного благодарен.";
			link.l1.go = "TStep_9";
		break;

		case "TStep_9":
            AddQuestRecord("UsurerQuest", "2");
            sld = GetCharacter(NPC_GenerateCharacter("QStranger", "citiz_7", "man", "man", 10, ENGLAND, 1, false));
            sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
			sld.greeting = "Gr_bankeer";
            sld.name = "Алекс";       //fix имени
            sld.lastname = "Уиннер";
            sTemp = GetNationNameByType(ENGLAND) + "_citizens";
            LAi_group_MoveCharacter(sld, sTemp);
            LAi_SetStayTypeNoGroup(sld);
            ChangeCharacterAddressGroup(sld, "Bridgetown_Shipyard", "goto", "goto1");
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "TStep_10":
            sld = GetCharacter(NPC_GenerateCharacter("QStranger", "citiz_7", "man", "man", 10, ENGLAND, 1, false));
            sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
			sld.greeting = "Gr_bankeer";
            sld.name = "Алекс";    //fix имени
            sld.lastname = "Уиннер";
            sTemp = GetNationNameByType(ENGLAND) + "_citizens";
            LAi_group_MoveCharacter(sld, sTemp);
            LAi_SetStayTypeNoGroup(sld);
            ChangeCharacterAddressGroup(sld, "CommonRoom_MH7", "goto", "goto1");
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		//зачарованный город
		case "MCTavern":
			dialog.text = "Нет, нет! Это наверху, постоялец, говорят, он и правда оборотень\nКапитан, вы "+ GetSexPhrase("смелый человек","отважная девушка") +", умоляю, сделайте что-нибудь! Если сюда ворвутся эти, с улицы... я боюсь представить, что будет!";
			link.l1 = "Я не знаю, кто из вас больше боится – ты или те, которые за дверью. Ладно, потолкую с твоим постояльцем.";
			link.l1.go = "exit";
			LAi_group_Delete("EnemyFight");
			pchar.questTemp.MC = "toCaracasWervolf";
			DeleteAttribute(&locations[reload_location_index], "reload.l2.disable");
			sld = GetCharacter(NPC_GenerateCharacter("CaracasWervolf", "trader_14", "man", "man", 10, PIRATE, -1, true));
			sld.dialog.filename = "Quest\MagicCity.c";
			sld.dialog.currentnode = "CaracasWervolf";
			sld.location	= "Caracas_tavern_upstairs";
			sld.location.group = "goto";
			sld.location.locator = "goto1";
			sld.BreakTmplAndFight = true;
			sld.reactionOnFightModeOn = true;
			LAi_SetActorType(sld);
			LAi_ActorWaitDialog(sld, pchar);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		break;

		case "MCCaracasAfter":
			dialog.text = "Слава богу, я избавился от него! Мне пришлось открыть дверь, ведь большинство из толпы были мои клиенты! Пара разбитых бутылок рома - невелика плата...";
			link.l1 = "Я спрашиваю, что с постояльцем?";
			link.l1.go = "MCCaracasAfter_1";
		break;
		case "MCCaracasAfter_1":
			dialog.text = "А, с оборотнем-то? На костер его отправили, а как же. Ты разве дым от костра не видел"+ GetSexPhrase("","а") +", как сюда из церкви ш"+ GetSexPhrase("ел","ла") +"? Так это он и догорает, оборотень этот...";
			link.l1 = "Ох, и скорые вы ребята, как я посмотрю.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("MC_endCaracas");
		break;

		//*************************** Квест "Сопровождение флейта "Орион"" **********************
		case "Andre_Abel_Quest_TavernOwner_Dialog_1":
			dialog.text = "Ах, капитан " + GetFullName(pchar) + "! Андре Абель убит два дня назад. Убийцы поджидали его прямо у входа в таверну... Ах, как жаль! Какой приятный был человек - щедрый, обходительный, никогда голоса не повышал, в драки не ввязывался. И вот, поди ж ты - такая смерть! Ай-яй-яй...";
			link.l1 = "Ого!.. Такого поворота я никак не ожидал"+ GetSexPhrase("","а") +". Искренне жаль беднягу, искренне жаль...";
			link.l1.go = "Andre_Abel_Quest_TavernOwner_Dialog_2";
		break;

		case "Andre_Abel_Quest_TavernOwner_Dialog_2":
			DialogExit();
			AddQuestRecord("Andre_Abel_Quest", "13");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("","а"));
			CloseQuestheader("Andre_Abel_Quest");
			DeleteAttribute(pchar,"QuestTemp.AndreAbelQuest");
			DeleteAttribute(PChar, "QuestTemp.Andre_Abel_Quest_PortPax_TavernOwner_Speek");
		break;

		//******************* ноды квеста священника. поиск грабителей (квест № 2)**********************
		case "Tavern_GenQuest_Church_2_1":
			dialog.text = "Мне об этом мало что известно... Спроси лучше кого-нибудь из завсегдатаев.";
			link.l1 = "Ясно, спасибо.";
			link.l1.go = "exit";
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
		break;

		//******************* ноды квеста священника. вернуть рукописи (квест № 1)**********************
		case "Tavern_ChurchGenQuest1_Node_1":
			dialog.text = "Мы не обслуживаем в долг, судар"+ GetSexPhrase("ь","ыня") +".";
			link.l1 = "Я привык"+ GetSexPhrase("","ла") +" расплачиваться звонкой монетой, любезный. Или здесь уже не принимают золото?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_2";
		break;

		case "Tavern_ChurchGenQuest1_Node_2":
			dialog.text = "Простите, госпо"+ GetSexPhrase("дин","жа") +" капитан, но ваш друг задолжал, и я подумал...";
			link.l1 = "Поменьше думай, любезный, и расторопней обслуживай. Так сколько тебе должен мой доблестный друг?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_3";
		break;

		case "Tavern_ChurchGenQuest1_Node_3":
			iTemp = (rand(3)+1)*10;
			PChar.GenQuest.ChurchQuest_1.MoneyToBarmen = iTemp;
			if(rand(1) == 0) // "Если он простой и сразу отдаёт"
			{
				dialog.text = FindRussianMoneyString(iTemp) + ", госпо"+ GetSexPhrase("дин","жа") +" капитан, и он оставил в залог церковные книги - это всё, что у него было при себе ценного.";
				if(sti(PChar.money) >= iTemp)
				{
					link.l1 = "Держи монеты и давай сюда манускрипты. Да аккуратнее, это тебе не бочонок эля, а писания Божьих праведников!";
					link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
				}
				else
				{
					link.l1 = "Подожди немного... Сейчас я принесу тебе эти деньги";
					link.l1.go = "exit";
					PChar.GenQuest.ChurchQuest_1.NoMoneyToBarmen = true;
				}
			}
			else // "Если он не простой"
			{
				dialog.text = FindRussianMoneyString(iTemp) + ", госпо"+ GetSexPhrase("дин","жа") +" капитан.";
				link.l1 = "Я оплачу его долг и заберу то, что он оставил в залог.";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2";
			}
		break;

		case "Tavern_ChurchGenQuest1_Node_4_1":
			DialogExit();
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "8");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", GetFullName(CharacterFromID("ChurchGenQuest1_Cap")));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;

		case "Tavern_ChurchGenQuest1_Node_4_2":
			dialog.text = "Нет, судар"+ GetSexPhrase("ь","ыня") +", так не пойдёт.";
			link.l1 = "Что значит 'не пойдёт'?! За кэпа выплачивают его долг - он доволен. Ты получаешь свои деньги - ты доволен. Мне возвращают залог - я довол"+ GetSexPhrase("ен","ьна") +". Все довольны, и всем хорошо. Почему это 'не пойдёт'?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_1";
		break;

		case "Tavern_ChurchGenQuest1_Node_4_2_1":
			dialog.text = "Потому, госпо"+ GetSexPhrase("дин","жа") +" капитан, что мне не нужны деньги. Я слишком хорошо знаю этого вашего капитана, и даже не надеялся, что когда-нибудь он сможет расплатиться, и потребует назад эти рукописи.";
			link.l1 = "Как это - не нужны деньги? Значит, ты хотел оставить себе книги? Но зачем, во имя Господа?!";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_2";
		break;

		case "Tavern_ChurchGenQuest1_Node_4_2_2":
			dialog.text = "Как раз во имя Господа, судар"+ GetSexPhrase("ь","ыня") +". Мой маленький сын был очень болен, и мы с женой дали обет, что пожертвуем на храм, если Создатель избавит дитя от лихорадки. Божье милосердие безгранично, ребёнок жив и здоров, и теперь мы должны исполнить свой обет. И вот как раз вовремя появляется капитан " + PChar.GenQuest.ChurchQuest_1.CapFullName + " и оставляет в залог церковные книги. Я не мог допустить такого непотребства - чтобы за выпивку расплачивались Словом Божием - и решил сегодня же пожертвовать книги нашему приходскому священнику.";
			link.l1 = "Сомнений нет, дело благое, но тебе следует знать, что эти манускрипты принадлежат другому священнику, то есть даже не священнику, а могущественному епископу, моему духовному наставнику, который очень рассердится, а возможно и проклянёт того, кто на них посягает... Я хотел"+ GetSexPhrase("","а") +" бы выкупить их у тебя и доставить ему в целости и сохранности.";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_3";
		break;

		case "Tavern_ChurchGenQuest1_Node_4_2_3":
			dialog.text = "Судар"+ GetSexPhrase("ь","ыня") +"... Госпо"+ GetSexPhrase("дин","жа") +" капитан... Конечно, я отдам, и не нужно никаких денег. Только замолвите словечко перед епископом, пусть он благословит нас и зачтёт выполнение обета...";
			link.l1 = "Безусловно, любезный, обет вам с женой зачтётся, потому что вы, как-никак, пожертвовали выручкой, вернув рукописи по принадлежности, а уж в какую церковь - не важно, все под одним Богом ходим. Давай-ка их сюда, и удачи тебе...";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_4";
		break;

		case "Tavern_ChurchGenQuest1_Node_4_2_4":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "9");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Acc"));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;

		case "Pirates_1":
			dialog.text = "Всюду вам, джентльменам"+ GetSexPhrase(""," и леди") +" удачи, испанцы мерещатся! Совсем от богатых призов одурели... Не Ла Керосин, а Лаки Росин, или Счастливчик Скрипач - это значит. Может, слыхали?\nВообще-то, мое имя - Вейнард д'Альто, хотя.. вряд ли вам это что то скажет. Нынче редко кто интересуется историей, хе-хе. Ну да ладно.";
			link.l1 = "Постойте... кажется, припоминаю. Вы - тот самый капер, что поссорился с французской короной и исчез пару лет назад! Дьявол и его вилы! Вот так встреча! А я слыхал"+ GetSexPhrase("","а") +", что Скрипач-то порой выбирается пощипать испанцев да французов по старой памяти!";
			link.l1.go = "Pirates_2";
		break;
		case "Pirates_2":
			dialog.text = "Полегче-ка на галсах... судар"+ GetSexPhrase("ь","ыня") +". Кто много судачит – дурной ветер привлекает. Если понимаете, о чем я говорю.";
			link.l1 = "Да, пожалуй, вы правы. Оставим пустые разговоры и перейдем к делам. ";
			link.l1.go = "meeting";
		break;

		case "Charles_1":
			dialog.text = "Ну и правильно, что не верите. Врут люди... Ну, подвернулся однажды испанский караван, который разметало штормом, вот и пришлось проводить его до Ямайки. Не в Гавану же было вести, в самом деле, хе-хе-хе...";
			link.l1 = "Ой, чего-то ты не договариваешь... Ладно, не буду любопытствовать. Перейдем к делам.";
			link.l1.go = "meeting";
		break;

		case "Portobello_1":
			dialog.text = "Да-да-да, все так и было, " + GetAddress_Form(NPChar) + "! Правду люди говорят. О подвигах Каталонского Лиса знают все на архипелаге!";
			link.l1 = "А еще мне доводилось слышать, что ты не в ладах с Морганом. И что ты месяц отсидел в тюрьме Порт-Рояла. И то, что ты бежал из застенков, прикинувшись леди Тейлор...";
			link.l1.go = "Portobello_2";
		break;

		case "Portobello_2":
			dialog.text = "Т-с-с... Не стоит об этом говорить так громко, "+ GetSexPhrase("приятель","подруга") +". Сплетни все это... сплетни. Ну, а Моргану меня здесь никогда не достать, хе-хе.";
			link.l1 = "Ладно, " + npchar.name + ", поболтали, теперь перейдем к делам.";
			link.l1.go = "meeting";
		break;

		//ОЗГ
		case "Seek_Carlos":
		if (pchar.questTemp.Headhunter.Chance == 1)
		{
			dialog.text = "Ха! Так он где-то здесь, в таверне! Я его видел минут пять назад. Поищите, он должен быть тут.";
		}
		else
		{
			dialog.text = "Хм... Был он у меня с час назад. А сейчас ушел - в бордель, вроде бы, собирался.";
		}
		link.l1 = "Спасибо! Ты мне здорово помог!";
		link.l1.go = "exit";
		pchar.questTemp.Headhunter = "hunt_carlos_fight";
		break;
		//ОЗГ

		//Виспер
		case "w_find_desouza":
			dialog.text = "Да заходили сюда одни типы, вопросы задавали. Они конечно же не сказали, что на инквизицию работают, но меня не проведешь. Я сразу приметил клеймо в форме распятия у одного на запястье. Такие инквизиторы ставят бывшим преступникам, когда набирают в свой орден.";
			link.l1 = "А ты очень проницателен, как для простого трактирщика. Но почему ты решил мне рассказать про тех ребят, а не им про меня?";
			link.l1.go = "w_find_desouza_1";
		break;
		case "w_find_desouza_1":
			dialog.text = "Ну во первых я не очень люблю инквизиторов, а во вторых они уже давно уплыли. Ты, с другой стороны, можешь быть заинтересована, куда.";
			link.l1 = "И куда же?";
			link.l1.go = "w_find_desouza_2";
		break;
		case "w_find_desouza_2":
			dialog.text = "А вот теперь мы подошли к главной причине, почему я тебе все это рассказывал. Ясное дело, такая информация денег стоит. Десять тысяч.";
			link.l1 = "Получи. Ну давай, говори, не томи.";
			link.l1.go = "w_find_desouza_3";
		break;
		case "w_find_desouza_3":
			AddMoneyToCharacter(pchar, -10000);
			dialog.text = "О, совсем другое дело. А направились они в голландский порт.";
			link.l1 = "А конкретней?";
			link.l1.go = "w_find_desouza_4";
		break;
		case "w_find_desouza_4":
			dialog.text = "Конкретней не знаю, но у голландцев не так уж много портов на Карибах, наверняка найдешь.";
			AddQuestRecord("WhisperQuestline", "4");
			pchar.Whisper.FindDesouzaHol = true;
			link.l1 = "Ладно, прощай.";
			link.l1.go = "exit";
		break;
		case "w_meet_esteban_friend":
			dialog.text = "Один мой постоялец спрашивал за вас. Сказал, что ищет капитана 'Пса Войны' для важного дела.";
			link.l1 = "Что за дело?";
			link.l1.go = "w_meet_esteban_friend_1";
		break;
		case "w_meet_esteban_friend_1":
			dialog.text = "Можете сами у него узнать. Он сейчас у себя в комнате.";
			link.l1 = "Заинтриговал. Пойду, поговорю с ним.";
			link.l1.go = "exit";
			pchar.Whisper.EsFriendTown = FindStringBeforeChar(npchar.id, "_tavernkeeper");
			WhisperSpawn_Chard();
		break;

		//Виспер

		//Lipsar Квест История Давней Дружбы
		case "MaksQuest_1":
			dialog.text = "Наверное, ты ищешь того мутного типа, в шляпе и зелёном камзоле.";
			link.l1 = "Спасибо, помог.";
			link.l1.go = "exit";
			DeleteAttribute(Pchar,"Luke.SpawnMaks");
		break;
		case "LukeQuest_1":
			bDisableFastReload = true;
			dialog.text = "Как только вы ушли, в таверну зашли какие то люди, поговорили с ним, и они ушли вместе. А куда, я даже не знаю.";
			link.l1 = "Вот те на! Как они выглядели, не подскажешь?";
			link.l1.go = "LukeQuest_2";
		break;
		case "LukeQuest_2":
			dialog.text = "Типичные пираты, ничего особенного в их внешности не было.";
			link.l1 = "Ладно, спасибо за информацию.";
			link.l1.go = "exit";
			link.l2 = "Ладно, спасибо за информацию. Держи, в знак благодарности.";
			link.l2.go = "Pay1000";
			Pchar.Luke.Info = "Fight";
			AddDialogExitQuest("ChangeLukesHome");
		break;
		case "Pay1000":
			dialog.text = "Спасибо, " + GetSexPhrase("сэр","мадам") + ", не ожидал."
			link.l1 = "Мне не сложно.";
			link.l1.go = "exit";
			AddMoneyToCharacter(Pchar, -1000);
			Pchar.Luke.Info = "Peace";
		break;
	}
}

string findTraderCity(ref NPChar)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
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

string findPassangerCity(ref NPChar)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].nation != "none" && colonies[n].id != "Panama" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
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
