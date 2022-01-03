void ProcessDialogEvent()
{
	ref NPChar, her;
	aref Link, NextDiag;
	bool bOk = false;
    bool bOk2;

	int Sum, nRel, nDay, iChurchQuest2_Summ;
	ref sld;

	// Церковный квест № 2 -->
	if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Summ_To_Contra"))
	{
		iChurchQuest2_Summ = sti(PChar.rank)*100 + (rand(3)+1)*100;
		PChar.GenQuest.ChurchQuest_2.Summ_To_Contra = sti(iChurchQuest2_Summ);
	}
	// <-- Церковный квест № 2

	string sColony;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    string iDay, iMonth;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }

	//тереть нафиг аттрибут при прошествии дней (navy fix)
	if (CheckAttribute(pchar, "GenQuest.contraTravel.days") && GetQuestPastDayParam("contraTravel") > sti(PChar.GenQuest.contraTravel.days))
	{
		DeleteAttribute(pchar, "GenQuest.contraTravel");
		CloseQuestHeader("Gen_ContrabandTravel");
	}

	switch(Dialog.CurrentNode)
	{
        case "Exit":
			DeleteAttribute(npchar,"pricevalue");
			DeleteAttribute(npchar,"pricev");
			DeleteAttribute(npchar,"itemtype");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Trade_exit":
            if (CheckNPCQuestDate(npchar, "Item_date"))
			{
				SetNPCQuestDate(npchar, "Item_date");
				GiveItemToSmuggler(npchar);
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchItemsTrade(npchar);
		break;

		case "Smuggling_exit":
			PChar.CurrentSmuggler = npchar.id;
			NextDiag.CurrentNode = NextDiag.TempNode;
			PlaceSmugglersOnShore(Pchar.quest.contraband.CurrentPlace);
			Pchar.quest.Contraband.active = true;
			pchar.GenQuest.Contraband.GuardNation = npchar.nation;
			pchar.GenQuest.Contraband.SmugglerId  = npchar.id;
			SetAllContraGoods(&Stores[sti(Pchar.GenQuest.Contraband.StoreIdx)], npchar);
			ReOpenQuestHeader("Gen_Contraband");
            if (GetIslandByCityName(npchar.city) == "Mein")
            {
            	AddQuestRecord("Gen_Contraband", "t1_1");
            }
            else
            {
	            AddQuestRecord("Gen_Contraband", "t1");
				AddQuestUserData("Gen_Contraband", "sIsland", XI_ConvertString(GetIslandByCityName(npchar.city)));
			}
			AddQuestUserData("Gen_Contraband", "sLoc", GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt"));

			DialogExit();
		break;

		case "First time":
		UpdateSmugglers();
		//ОЗГ
			if (CheckAttribute(pchar,"contrabandmoneyback") && sti(pchar.contrabandmoneyback) >= 3000000+(MOD_SKILL_ENEMY_RATE*100000) && !CheckCharacterPerk(pchar,"UnlimitedContra"))
			{
				dialog.text = "Капитан, вы показали себя по настоящему полезным клиентом для всего контрабандного бизнеса. Отныне и впредь вам будут предоставляться наилучшие условия сделок.";
				link.l1 = "Благодарю вас за доверие.";
				link.l1.go = "First time";
				Log_info("Разблокирован перк ''Заядлый контрабандист''");
				SetCharacterPerk(pchar, "UnlimitedContra");
				NPChar.quest.meeting = "1";
				break;
			}
			if (!CheckAttribute(pchar, "questTemp.Headhunter"))
			{
				dialog.text = "Капитан, я бы хотел поговорить с вами об одном деле. Вы, как я вижу, человек на Архипелаге новый, и пока не известны в Береговом братстве... Возможно, вы именно т"+ GetSexPhrase("от","а") +", кто нуж"+ GetSexPhrase("ен","на") +".";
				link.l1 = "Хм... Интересно. Излагайте, что у вас за дело.";
				link.l1.go = "Give_vector";
				break;
			}
			if(NPChar.quest.meeting == "0")
			{
				Dialog.Text = "Что вам надо, капитан? Я не знаю вашего имени, и не могу назвать вам свое.";
				Link.l1 = "Я капитан " + GetFullName(pchar) + ".";
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
				if (CheckAttribute(pchar,"RimalieGood") && npchar.id == "PortSpein_Smuggler" && ChangeContrabandRelation(pchar, 0) > 5)
				{
					Link.l18 = "Я бы хотел"+ GetSexPhrase("","а") +" пообщаться по поводу мушкетёра, живущего отшельником на этом острове.";
					Link.l18.go = "Rimalie";
				}
			}
			else
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour") && GetQuestPastDayParam("GenQuest.CaptainComission.GetRumour") < 1)
				{
					if(!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakContra"))
					{
						pchar.GenQuest.CaptainComission.SpeakContra = true;
						dialog.text = "Сегодня никаких сделок не будет. Во всех бухтах полно патруля, губернатор ищет груз, который капитан патрульного " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " якобы конфисковал у какого-то пирата и спрятал.";
						link.l1 = "А где сам капитан " + pchar.GenQuest.CaptainComission.Name + "?";
						link.l1.go = "CapComission_1";
						break;
					}
					else
					{
						dialog.text = "Сегодня никаких сделок не будет.";
						link.l1 = "Понятно.";
						link.l1.go = "exit";
						break;
					}
				}

				if(pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
				{
					dialog.text = "Сегодня никаких сделок не будет.";
					link.l1 = "Понятно.";
					link.l1.go = "exit";
					break;
				}

				Dialog.Text = "Что вы привезли на этот раз, капитан?";
				if (LAi_group_GetPlayerAlarm() > 0)
				{
	       			Dialog.Text = RandPhraseSimple("Говори быстрей, "+ GetSexPhrase("приятель","подруга") +", что тебе надо? А то, знаешь ли, погоня за тобой!", "Не медли, быстрее излагай суть дела! За тобой солдатня бегает, не до долгих бесед, знаешь ли...");
				}
				if(FindFirstContrabandGoods(PChar) != -1)
				{
					Link.l1 = "Я привез"+ GetSexPhrase("","ла") +" немного товаров на продажу.";
					Link.l1.go = "Meeting_3";
				}

				if (CheckAttribute(pchar, "GenQuest.contraTravel.active") && sti(pchar.GenQuest.contraTravel.active) == true)
					Link.l2 = "Насчет поездки...";
				else
					Link.l2 = "Мне нужно добраться кое-куда.";
				Link.l2.go = "Travel";
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakSmuggler"))
				{
					if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
					{
						link.l3 = "У меня есть 'особенный' товар, думаю тебе будет любопытно. Взгляни!";
						link.l3.go = "SM_ShipLetters_1";
					}
				}
				// Церковный генератор №2 -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
				{
					Link.l4 = "Мне нужно кое-что выяснить, приятель.";
					Link.l4.go = "Contra_GenQuest_Church_2_1";
				}

				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
				{
					Link.l5 = "Твой коллега и мой добрый приятель из " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen") + " сказал, что ты в курсе одного дела.";
					Link.l5.go = "Contra_GenQuest_Church_2_Contra2_1";
				}
				// <-- Церковный генератор №2

		    	////////////////////////////////////////////////////////
		    	//zagolski. начальный квест пирата
		    	if(CheckAttribute(pchar, "questTemp.pirateStartQuest") && pchar.questTemp.pirateStartQuest == "2" && GetArealByCityName(npchar.city) == pchar.questTemp.pirateStartQuest.Areal && npchar.city != pchar.questTemp.pirateStartQuest.City)
		    	{
			    	link.l4 = "Слушай, мне позарез нужна сотня другая рабов. Уже и не знаю, к кому обращаться.";
			    	link.l4.go = "pirateStartQuest_Smuggler";
			    }

				if (CheckAttribute(pchar,"contratrade.time"))
				{
					if (pchar.contratrade.time != GetDataDay() && ChangeContrabandRelation(pchar, 0) > 5)
					{
						Link.l17 = "(Негромко) Я слышал"+ GetSexPhrase("","а") +", что у вас можно купить кое-то интересное.";
						Link.l17.go = "Trade";
					}
				}
				if (!CheckAttribute(pchar,"contratrade.time") && ChangeContrabandRelation(pchar, 0) > 5)
				{
					Link.l17 = "(Негромко) Я слышал"+ GetSexPhrase("","а") +", что у вас можно купить кое-то интересное.";
					Link.l17.go = "Trade";
				}
				if (CheckAttribute(pchar,"RimalieGood") && ChangeContrabandRelation(pchar, 0) > 5)
				{
					Link.l18 = "Я бы хотел"+ GetSexPhrase("","а") +" пообщаться по поводу мушкетёра, живущего отшельником на этом острове.";
					Link.l18.go = "Rimalie";
				}

				Link.l7 = "Ничего. До встречи.";
				Link.l7.go = "Exit";
			}
		break;

		case "Rimalie":
			if (!CheckAttribute(pchar,"RimalieWait"))
			{
				Dialog.Text = "Как же, слышал о нём. Одному из моих коллег досталось из-за него. Он сорвал одну сделку и похитил часть товаров, пока все хлопали глазами.";
				Link.l1 = "Может я бы мог"+ GetSexPhrase("","ла") +" возместить убытки из-за его поступка?";
				Link.l1.go = "Rimalie_2";
			}
			else
			{
				Dialog.Text = "Снова о нём...? 50000 пиастров прямо сейчас. Если оплатишь - мы отстанем от него.";
				if (sti(pchar.money) >= 50000)
				{
					Link.l1 = "Держите.";
					Link.l1.go = "Rimalie_3";
				}
				Link.l2 = "Я ещё вернусь по этому поводу.";
				Link.l2.go = "exit";
			}
		break;

		case "Rimalie_2":
			if (ChangeContrabandRelation(pchar, 0) >= 70)
			{
				Dialog.Text = "Ты довольно уважаемый клиент для нашей организации и принёс"+ GetSexPhrase("","ла") +" немало прибыли. Ради тебя мы готовы пойти на уступки и прекратить его преследовать хоть прямо сейчас. Неужели он настолько тебе нужен? О Рималье ходят довольно нехорошие слухи о подстрекательстве к бунту. Не боишься?";
				Link.l1 = "Ради хорошего офицера-мушкетёра не грех и рискнуть. Благодарю вас за помощь!";
				Link.l1.go = "exit";
				pchar.RimalieDone = true;
				DeleteAttribute(pchar,"RimalieGood");
				DeleteAttribute(pchar,"RimalieWait");
			}
			else
			{
				pchar.RimalieWait = true;
				Dialog.Text = "За возмещение убытков мы хотим... 50000 пиастров прямо сейчас. Если оплатишь - мы отстанем от него.";
				if (sti(pchar.money) >= 50000)
				{
					Link.l1 = "Держите.";
					Link.l1.go = "Rimalie_3";
				}
				Link.l2 = "Я ещё вернусь по этому поводу.";
				Link.l2.go = "exit";
			}
		break;


		case "Rimalie_3":
			AddMoneyToCharacter(pchar,-50000);
			Dialog.Text = "С тобой приятно иметь дело. Но неужели он настолько тебе нужен? О Рималье ходят довольно нехорошие слухи о подстрекательстве к бунту. Не боишься?";
			Link.l1 = "Ради хорошего офицера-мушкетёра не грех и рискнуть. До встречи!.";
			Link.l1.go = "exit";
			pchar.RimalieDone = true;
			DeleteAttribute(pchar,"RimalieGood");
			DeleteAttribute(pchar,"RimalieWait");
		break;

		case "CapComission_1":
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				dialog.text = "В подвале форта, где же ему ещё быть?.. Капитан в любой момент может выдать властям место, где спрятал груз, и тогда мы останемся с носом. Так что, пока не уляжется вся эта суета, даже не думайте о сделках.";
				link.l1 = "Слушайте, вы же каждый камень на острове знаете. Неужели вам не известен тайник капитана " + pchar.GenQuest.CaptainComission.Name + "?";
				link.l1.go = "CapComission_4";
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				dialog.text = "На небесах, наверное. Казнили его недавно вместе с командой. А в приговоре-то не сказали, что судно было пиратским.";
				link.l1 = "А почему ты уверен, что судно принадлежало пиратам?";
				link.l1.go = "CapComission_2";
			}
		break;

		case "CapComission_2":
			dialog.text = "Мы наблюдали тот бой со скалы пока не стемнело. В трубу отчётливо было видно, что " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name"))) + " под Чёрным Роджером. А потом, спустя часов пять, мы увидели в темноте только вспышку, будто крюйт-камера рванула. За это время вполне можно было вывезти товар на берег.";
			link.l1 = "А разве вам не известно, где тайник капитана " + pchar.GenQuest.CaptainComission.Name +"? Вы же каждый камень на острове знаете.";
			link.l1.go = "CapComission_3";
		break;

		case "CapComission_3":
			dialog.text = "Нет. Мы его тоже ищем, но не для того, чтобы обрадовать губернатора...";
			link.l1 = "Понятно... Ну, счастливо оставаться.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission2", "38");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Acc")));
		break;

		case "CapComission_4":
			dialog.text = "Нет. Мы его тоже ищем, но не для того, чтобы обрадовать губернатора, хе-хе...";
			link.l1 = "Понятно... Ну, счастливо оставаться.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission2", "19");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		break;

		case "SM_ShipLetters_1":
			pchar.questTemp.different.GiveShipLetters.speakSmuggler = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Почему ты так решил"+ GetSexPhrase("","а") +"? Я честный каботажник. Ищи другого покупателя.";
				link.l1 = "Спасибо и на этом....";
				link.l1.go = "exit";
			}
			else
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					dialog.text = "Как сказать? Может быть, и пригодится твой 'товар'. Бери " + sti(pchar.questTemp.different.GiveShipLetters.price2) + " золотых, и забудь об этом.";
					link.l1 = "Пожалуй, нет.";
					link.l1.go = "SM_ShipLetters_2";
					link.l2 = "Да, ты угадал, уже начинаю забывать!";
					link.l2.go = "SM_ShipLetters_3";
				}
				else
				{
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
					{
						dialog.text = "Точно! Мне уже не просто любопытно. Думаю, если заплачу тебе "+ sti(pchar.questTemp.different.GiveShipLetters.price3) +" золотых, то и тебе станет совсем не любопытно, что да как в этих бумагах.";
						link.l1 = "Пожалуй, нет.";
						link.l1.go = "SM_ShipLetters_2";
						link.l2 = "Да, ты угадал, уже начинаю забывать!";
						link.l2.go = "SM_ShipLetters_3";
					}
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
					{
						dialog.text = "Вот это шанс прищучить наглеца! Это очень, очень любопытно. Давай так: я плачу тебе " + sti(pchar.questTemp.different.GiveShipLetters.price4) + " золотом, а ты делаешь вид, что забыл"+ GetSexPhrase("","а") +" документы на столе?";
						link.l1 = "Пожалуй, нет.";
						link.l1.go = "SM_ShipLetters_2";
						link.l2 = "Да, ты угадал, уже начинаю забывать!";
						link.l2.go = "SM_ShipLetters_3";
					}
				}
			}
		break;

		case "SM_ShipLetters_2":
			dialog.text = "Ну-ну, смотри не наживи врагов.";
			link.l1 = "И ты оглядываться не забывай!";
			link.l1.go = "exit";
		break;

		case "SM_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook");
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2));
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price3));
				}
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2));
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price4));
				}
			}

			if((sti(pchar.questTemp.different.GiveShipLetters.variant) == 0) || (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2))
			{
				ChangeCharacterReputation(pchar, -1);
				OfficersReaction("bad");
			}
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер
			AddQuestRecord("GiveShipLetters", "7");
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Meeting":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour") && GetQuestPastDayParam("GenQuest.CaptainComission.GetRumour") < 2)
			{
				if(!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakContra"))
				{
					pchar.GenQuest.CaptainComission.SpeakContra = true;
					dialog.text = "Сегодня никаких сделок не будет. Во всех бухтах полно патруля, губернатор ищет груз, который капитан патрульного " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " якобы конфисковал у какого-то пирата и спрятал.";
					link.l1 = "А где сам капитан " + pchar.GenQuest.CaptainComission.Name + "?";
					link.l1.go = "CapComission_1";
					break;
				}
				else
				{
					dialog.text = "Сегодня никаких сделок не будет.";
					link.l1 = "Понятно.";
					link.l1.go = "exit";
					break;
				}
			}

			if(pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
			{
				dialog.text = "Сегодня никаких сделок не будет.";
				link.l1 = "Понятно.";
				link.l1.go = "exit";
				break;
			}

			Dialog.Text = "Чем могу быть полезен вам, капитан?";
			if(FindFirstContrabandGoods(PChar) != -1)
			{
				Link.l1 = "Я хочу кое-что продать.";
				Link.l1.go = "Meeting_1";
			}
			Link.l2 = "Мне нужно добраться кое-куда.";
			Link.l2.go = "Travel";
			// Церковный генератор №2 -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
			{
				Link.l3 = "Мне нужно кое-что выяснить, приятель.";
				Link.l3.go = "Contra_GenQuest_Church_2_1";
			}

			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
			{
				Link.l3 = "Твой коллега и мой добрый приятель из " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen") + " сказал, что ты в курсе одного дела.";
				Link.l3.go = "Contra_GenQuest_Church_2_Contra2_1";
			}
			// <-- Церковный генератор №2

			////////////////////////////////////////////////////////
			//zagolski. начальный квест пирата
			if(CheckAttribute(pchar, "questTemp.pirateStartQuest") && pchar.questTemp.pirateStartQuest == "2" && GetArealByCityName(npchar.city) == pchar.questTemp.pirateStartQuest.Areal && npchar.city != pchar.questTemp.pirateStartQuest.City)
			{
				link.l4 = "Слушай, мне позарез нужна сотня другая рабов. Уже и не знаю, к кому обращаться.";
				link.l4.go = "pirateStartQuest_Smuggler";
			}

            if (CheckAttribute(pchar,"contratrade.time"))
			{
				if (pchar.contratrade.time != GetDataDay() && ChangeContrabandRelation(pchar, 0) > 5)
				{
					Link.l17 = "(Негромко) Я слышал"+ GetSexPhrase("","а") +", что у вас можно купить кое-то интересное.";
					Link.l17.go = "Trade";
				}
			}
			if (!CheckAttribute(pchar,"contratrade.time") && ChangeContrabandRelation(pchar, 0) > 5)
			{
				Link.l17 = "(Негромко) Я слышал"+ GetSexPhrase("","а") +", что у вас можно купить кое-то интересное.";
				Link.l17.go = "Trade";
			}

			Link.l5 = "Ничем. Удачи!";
			Link.l5.go = "Exit";
		break;

		////////////////////////////////////////////////////////
		//zagolski. начальный квест пирата
		case "pirateStartQuest_Smuggler":
		if (!CheckAttribute(pchar, "GenQuest.contraTravel.active") && !CheckAttribute(Pchar, "quest.Contraband.Active"))
		{
			dialog.text = "Что-то велик нынче спрос на рабов. За такими делами обычно к пиратам в соседнее поселение обращаются.";
			link.l1 = "Нету там рабов, а у меня дело горит. Времени совсем не осталось.";
			link.l1.go = "pirateStartQuest_Smuggler_1";
		}
		else
		{
			dialog.text = "Сначала, приятель, заверши начатое. А потом уже об этом поговорим.";
			link.l1 = "Понял.";
			link.l1.go = "exit";
		}
		break;
		case "pirateStartQuest_Smuggler_1":
			dialog.text = "Черт бы меня побрал, если я не знаю кто твой заказчик! Ну, этот пройдоха получит свою партию с солидной наценкой, если решил водить меня за нос.";
			link.l1 = "Я не знаю, о ком ты говоришь. Мой покупатель сидит на другом острове, поэтому и тороплюсь, пока ветер попутный.";
			link.l1.go = "pirateStartQuest_Smuggler_2";
		break;
		case "pirateStartQuest_Smuggler_2":
			dialog.text = "И сколько рабов тебе нужно?";
			link.l1 = "Нужно 100 рабов. Хорошо заплачу!";
			link.l1.go = "pirateStartQuest_Smuggler_3";
		break;
		case "pirateStartQuest_Smuggler_3":
			dialog.text = "Это обойдется тебе в 30 000 пиастров, по 300 за раба. Есть столько?";
			link.l1 = "По рукам.";
			link.l1.go = "pirateStartQuest_Smuggler_4";
		break;
		case "pirateStartQuest_Smuggler_4":
			pchar.questTemp.pirateStartQuest.Shore = SelectQuestShoreLocation();
			dialog.text = "Ладно. Приходи с деньгами в место под названием " + XI_ConvertString(pchar.questTemp.pirateStartQuest.Shore) + ", там и потолкуем...";
			link.l1 = "Хорошо, буду. Только не вздумай водить меня за нос - у меня времени нет в игры играть.";
			link.l1.go = "exit";

			pchar.questTemp.pirateStartQuest = "3";
			pchar.questTemp.pirateStartQuest.City2Nation = npchar.nation;
			AddQuestRecord("pSQ", "3");
			AddQuestUserData("pSQ", "sCity2", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City2 + "Gen"));
			AddQuestUserData("pSQ", "sShore", XI_ConvertString(pchar.questTemp.pirateStartQuest.Shore));

			pchar.quest.pirateStartQuest_Smuggler_fc.win_condition.l1 = "Location";
			pchar.quest.pirateStartQuest_Smuggler_fc.win_condition.l1.location = pchar.questTemp.pirateStartQuest.City2 + "_ExitTown";
			pchar.quest.pirateStartQuest_Smuggler_fc.function = "pirateStartQuest_Smuggler_fc";

			AddGeometryToLocation(pchar.questTemp.pirateStartQuest.Shore, "smg");
			pchar.quest.pirateStartQuest_Smuggler_fc2.win_condition.l1 = "Location";
			pchar.quest.pirateStartQuest_Smuggler_fc2.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Shore;
			pchar.quest.pirateStartQuest_Smuggler_fc2.function = "pirateStartQuest_Smuggler_fc2";
		break;
		//--------------------------------------------------

		// Церковный генератор №2 -->
		case "Contra_GenQuest_Church_2_1":
			iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
			dialog.text = "Я тебе не приятель. А кое-что выяснить может дорого тебе обойтись.";
				link.l1 = "Хм. Мне нужно узнать нечто, стоящее не более " + FindRussianMoneyString(iChurchQuest2_Summ) + ".";
				link.l1.go = "Contra_GenQuest_Church_2_2";
			break;

		case "Contra_GenQuest_Church_2_2":
			iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
			if(sti(PChar.money) >= iChurchQuest2_Summ)
			{
				dialog.text = "Давай сюда свои деньги. И учти, за такую сумму много не узнаешь.";
				link.l1 = "Мне много и не надо. Понимаешь, разминул"+ GetSexPhrase("ся","ась") +" я тут с друзьями. Опоздал"+ GetSexPhrase("","а") +" на встречу, а они не стали ждать...";
				link.l1.go = "Contra_GenQuest_Church_2_3";
				AddMOneyToCharacter(PChar, -iChurchQuest2_Summ);
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.Summ_To_Contra");
			}
			else
			{
				dialog.text = "Хех, да у тебя же нету денег! Приходи, когда разбогатеешь...";
				link.l1 = "Точно.";
				link.l1.go = "exit";
			}
			break;

		case "Contra_GenQuest_Church_2_3":
			dialog.text = "А я здесь причем?";
				link.l1 = "В городе их нет, своего корабля у них тоже не было. Вот я и подумал"+ GetSexPhrase("","а") +", может быть, кто из твоих деловых партнёров оказал им некую услугу?..";
				link.l1.go = "Contra_GenQuest_Church_2_4";
			break;

		case "Contra_GenQuest_Church_2_4":
			sColony = QuestGetColony(PChar.GenQuest.ChurchQuest_2.QuestTown);
			dialog.text = "Вот оно что... Ну, было дело. Подошли люди, сказали, что им срочно нужно отчаливать, и при этом неважно куда. Мы в таких случаях причины не спрашиваем, лишь бы  цену платили. У нас ходка была в " + XI_ConvertString("Colony" + sColony + "Acc") + ", что находится на " + XI_ConvertString(locations[FindLocation(sColony + "_Town")].IslandID + "Dat") + ", туда они и погрузились. Можем и тебя подбросить, если в цене сойдёмся.";
			link.l1 = "Спасибо, я под своим парусом.";
			link.l1.go = "exit";
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "8");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("","а"));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + sColony + "Acc"));
			AddQuestUserData(sQuestTitle, "sIsland", XI_ConvertString(locations[FindLocation(sColony + "_Town")].IslandID + "Dat"));
			PChar.GenQuest.ChurchQuest_2.AskContra_2 = true;
			PChar.GenQuest.ChurchQuest_2.Contra_Colony = sColony;
			break;

		case "Contra_GenQuest_Church_2_Contra2_1":
			dialog.text = "С тобой я пока не имел никаких дел.";
				link.l1 = "Ну, это вопрос времени. Не так давно вы привезли сюда моих друзей, с которыми я разминул"+ GetSexPhrase("ся","ась") +".";
				link.l1.go = "Contra_GenQuest_Church_2_Contra2_2";
			break;

		case "Contra_GenQuest_Church_2_Contra2_2":
			string sGenLocation = IslandGetLocationFromType(locations[FindLocation(PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_Town")].IslandID, "Shore");
			PChar.GenQuest.ChurchQuest_2.QuestGangShore = sGenLocation;
			PChar.GenQuest.ChurchQuest_2.BanditsInShore = true;
			dialog.text = "Хм, мы высадили их " + XI_ConvertString(sGenLocation + "Dat") + "... Знаешь, лучше бы они и вправду оказались тебе друзьями, иначе бы я не советовал их беспокоить.";
			link.l1 = "Спасибо за заботу, но я вооружен"+ GetSexPhrase("","а") +" и очень обаятел"+ GetSexPhrase("ен","ьна") +".";
			link.l1.go = "exit";
			SetFunctionLocationCondition("Church_GenQuest2_GenerateBandits", sGenLocation, false);
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "9");
			AddQuestUserData(sQuestTitle, "sShore", XI_ConvertString(sGenLocation + "Acc"));
			locations[FindLocation(sGenLocation)].DisableEncounters = true;
			SetFunctionTimerCondition("Church_GenQuest2_TimeIsLeft", 0, 0, 1, false);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2");
			break;
		// <-- Церковный генератор №2

		case "Meeting_1":
			Dialog.Text = "Хм... Причем здесь я? Наверное, вы не туда зашли, капитан. Идите в магазин - там с радостью купят то, что вы привезли.";
			Link.l1 = "Боюсь, что мне нужны именно вы.";
			Link.l1.go = "Meeting_2";
			Link.l2 = "Спасибо за совет. Всего хорошего.";
			Link.l2.go = "exit";
		break;

		case "Meeting_2":
			Dialog.Text = "Зачем же?";
			Link.l1 = "Я хочу продать то, что не купит ни один торговец на этом острове.";
			Link.l1.go = "Meeting_3";
		break;

		case "Meeting_3":
			if (sti(npchar.SmugglingMoney) < 200000)
			{
				Dialog.Text = "Я ещё не продал твою предыдущую партию. У меня пока нет денег на новый товар, приходи через месяц-другой.";
				Link.l1 = "Я ведь могу и другого клиента найти, знаешь ли... Ну ладно, бывай.";
            	Link.l1.go = "exit";
				break;
			}

			if (CheckCharacterPerk(pchar, "UnlimitedContra"))
			{
				if (npchar.quest.trade_date != lastspeak_date)
    			{
                    npchar.quest.trade_date = lastspeak_date;

                    if (ChangeContrabandRelation(pchar, 0) > 5)
                    {
                        Pchar.quest.contraband.CurrentPlace = SelectSmugglingLocation();
						Pchar.quest.contraband.City = NPChar.city;
                        if (Pchar.quest.contraband.CurrentPlace != "None" && !CheckAttribute(pchar, "Whisper.ContraSmuggler")&& !CheckAttribute(pchar,"Whisper.Contraband"))//boal fix
                        {
                            if (ChangeContrabandRelation(pchar, 0) >= 70)
                            {
                                Dialog.Text = "Я знаю, с тобой можно иметь дело. Мы будем ждать тебя в месте, называющемся " + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
                            }
                            else
                            {
            				    Dialog.Text = "Хм... Возможно, покупатель и найдется. Мы будем ждать вас в месте, называющемся " + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
            				}
            				Link.l1 = "Хорошо. До встречи.";
            				Link.l1.go = "Smuggling_exit";
        				}
        				else
        				{   //boal fix
                            if(CheckAttribute(pchar, "Whisper.ContraSmuggler") || CheckAttribute(pchar,"Whisper.Contraband"))
							{
								Dialog.Text = "Кажется, у тебя уже назначена одна сделка, с кем-то на Тортуге. Приходи, когда разберешься.";
							}
							else
							{
								Dialog.Text = "Сегодня сделок больше не будет. Приходи завтра.";
							}
            				Link.l1 = "Хорошо.";
            				Link.l1.go = "Exit";
        				}
    				}
    				else
    				{
                        Dialog.Text = "И после всего ты думаешь, что кто-то захочет работать с тобой? Радуйся, что мы еще не послали наемных убийц за твоей головой. Убирайся!";
        				Link.l1 = "Эх... значит не судьба мне стать контрабандистом.";
        				Link.l1.go = "Exit";
    				}
				}
				else
				{
                    if(CheckAttribute(pchar, "Whisper.ContraSmuggler") || CheckAttribute(pchar,"Whisper.Contraband"))
					{
						Dialog.Text = "Кажется, у тебя уже назначена одна сделка, с кем-то на Тортуге. Приходи, когда разберешься.";
					}
					else
					{
						Dialog.Text = "Сегодня сделок больше не будет. Приходи завтра.";
					}
    				Link.l1 = "Хорошо.";
    				Link.l1.go = "Exit";
				}
				break;
			}
			if (GetCompanionQuantity(pchar) > 1 && GetBaseHeroNation() != PIRATE)
			{
				dialog.text = NPCStringReactionRepeat("Сначала избавься от своей эскадры. Она слишком приметная. Мы не можем так рисковать. Приходи на одном корабле, и чтоб он был не больше брига или галеона.",
					"Я что, непонятно выразился? Повторяю - никакой эскадры!",
					"Ты что, туп"+ GetSexPhrase("ой","ая") +"? Оди-ин, говорю тебе - оди-ин корабль, не два, не три, а один! Теперь понял"+ GetSexPhrase("","а") +"?",
					"Ох, и как таких дур"+ GetSexPhrase("аков","") +" земля носит...", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Хорошо, я тебя понял"+ GetSexPhrase("","а") +". Один так один.",
					"Все понятно, просто уточнить хотел"+ GetSexPhrase("","а") +".",
					"Нет, не туп"+ GetSexPhrase("ой","ая") +", просто жадн"+ GetSexPhrase("ый","ая") +" очень. Подумал"+ GetSexPhrase("","а") +", может поменялось что, и можно придти сразу эскадрой...",
					"Ну ты же видишь - носит как-то...", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
				break;
			}

		//редкостная хрень, но по-другому не работает-класс корабля ГГ считается отдельно от компаньонов, и всё тут
			int iClass, ipClass;
			ipClass = 4-sti(RealShips[sti(pchar.ship.type)].Class);
			iClass = 3;//т.к. не пройдет по числу кораблей в любом случае
		if (GetBaseHeroNation() == PIRATE)
		{
			ipClass = sti(ipClass)-1;
			int iChIdx, i;
			// поиск старшего класса компаньона
			for (i=0; i<COMPANION_MAX; i++)
			{
				iChIdx = GetCompanionIndex(GetMainCharacter(), i);
				if (iChIdx>=0)
				{
					sld = GetCharacter(iChIdx);
					iClass = GetCharacterShipClass(sld);
				}
			}
		}
			if (sti(ipClass) > 0 || 3 - sti(iClass) > 0)
			{
				dialog.text = NPCStringReactionRepeat("Ты бы еще на королевском мановаре явил"+ GetSexPhrase("ся","ась") +". Да твою посудину за милю видать из форта. Мы не будем рисковать своими головами. Приходи на меньшем корабле, и только на одном.",
					"Я что, непонятно выражаюсь? Найди себе суденышко поменьше, тогда и приходи.",
					"Ты что, тупица или притворяешься? Говорю же тебе - найди себе шхуну, ну бриг на крайний случай, или сделка не состоится.",
					"Ох, и как таких дур"+ GetSexPhrase("аков","") +" земля носит...", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Хорошо, я тебя понял"+ GetSexPhrase("","а") +". Приду позже, как кораблик сменю.",
					"Да все понятно, просто уточнить хотел"+ GetSexPhrase("","а") +".",
					"Нет, не тупица, просто жадина. Подумал"+ GetSexPhrase("","а") +", может поменялось что. Я бы еще пару пинасов с собой прихватил"+ GetSexPhrase("","а") +"...",
					"Ну ты же видишь - носит как-то...", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
				break;
			}
			bOk  = CheckAttribute(pchar, "GenQuest.contraTravel.active") && (sti(pchar.GenQuest.contraTravel.active) == true);
			bOk2 = CheckAttribute(Pchar, "quest.Contraband.Active") && (sti(Pchar.quest.Contraband.Active) == true);
			bool bOk3 = CheckAttribute(Pchar, "questTemp.pirateStartQuest") && (Pchar.questTemp.pirateStartQuest == "3");
			if (bOk)
			{
			    if (GetQuestPastDayParam("contraTravel") > sti(PChar.GenQuest.contraTravel.days))
				{  // просрочка
					DeleteAttribute(PChar, "GenQuest.contraTravel");
					CloseQuestHeader("Gen_ContrabandTravel");
					bOk = false;
				}
			}

//navy --> PGG
			if (CheckFreeServiceForNPC(NPChar, "Smugglers") != -1)
			{
				if (makeint(environment.time) < 19.0)
				{
					Dialog.Text = "Извини, "+ GetSexPhrase("парень","деваха") +", у нас уже есть дела. Зайди вечером, часов так после 7, может уже освободимся.";
					if (ChangeContrabandRelation(pchar, 0) > 5 && sti(pchar.money) >= 1000 && !bOk && !bOk2 && !bOk && npchar.quest.trade_date != lastspeak_date)
					{
						Link.l1 = "А нельзя ли сейчас, за скромное вознаграждение вам, как агенту, в 1000 пиастров?";
						Link.l1.go = "AntiPGGContra";
					}
					Link.l2 = "Жаль...";
					Link.l2.go = "Exit";
					break;
				}
				else
				{
					if (bOk || bOk2 || bOk3)
					{
						Dialog.Text = "Может, стоит завершить одно дело прежде, чем браться за другое?";
						Link.l1 = "Пожалуй, ты прав.";
						Link.l1.go = "Exit";
					}
					else
					{
						if (npchar.quest.trade_date != lastspeak_date)
						{
							npchar.quest.trade_date = lastspeak_date;

							if (ChangeContrabandRelation(pchar, 0) > 5)
							{
								Pchar.quest.contraband.CurrentPlace = SelectSmugglingLocation();
								Pchar.quest.contraband.City = NPChar.city;
								if (Pchar.quest.contraband.CurrentPlace != "None"  && !CheckAttribute(pchar, "Whisper.ContraSmuggler")&& !CheckAttribute(pchar,"Whisper.Contraband"))//boal fix
								{
									if (ChangeContrabandRelation(pchar, 0) >= 70)
									{
										Dialog.Text = "Я знаю, с тобой можно иметь дело. Мы будем ждать тебя в месте, называющемся " + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
									}
									else
									{
										Dialog.Text = "Хм... Возможно, покупатель и найдется. Мы будем ждать вас в месте, называющемся " + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
									}
									Link.l1 = "Хорошо. До встречи.";
									Link.l1.go = "Smuggling_exit";
								}
								else
								{   //boal fix
									if(CheckAttribute(pchar, "Whisper.ContraSmuggler") || CheckAttribute(pchar,"Whisper.Contraband"))
									{
										Dialog.Text = "Кажется, у тебя уже назначена одна сделка, с кем-то на Тортуге. Приходи, когда разберешься.";
									}
									else
									{
										Dialog.Text = "Сегодня сделок больше не будет. Приходи завтра.";
									}
									Link.l1 = "Хорошо.";
									Link.l1.go = "Exit";
								}
							}
							else
							{
								Dialog.Text = "И после всего ты думаешь, что кто-то захочет работать с тобой? Радуйся, что мы еще не послали наемных убийц за твоей головой. Убирайся!";
								Link.l1 = "Эх... значит не судьба мне стать контрабандистом.";
								Link.l1.go = "Exit";
							}
						}
						else
						{
							if(CheckAttribute(pchar, "Whisper.ContraSmuggler")|| CheckAttribute(pchar,"Whisper.Contraband"))
							{
								Dialog.Text = "Кажется, у тебя уже назначена одна сделка, с кем-то на Тортуге. Приходи, когда разберешься.";
							}
							else
							{
								Dialog.Text = "Сегодня сделок больше не будет. Приходи завтра.";
							}
							Link.l1 = "Хорошо.";
							Link.l1.go = "Exit";
						}
					}
				}
			}
//navy <--

			if (bOk || bOk2 || bOk3)
			{
				Dialog.Text = "Может, стоит завершить одно дело прежде, чем браться за другое?";
				Link.l1 = "Пожалуй, ты прав.";
				Link.l1.go = "Exit";
			}
			else
			{
                if (npchar.quest.trade_date != lastspeak_date)
    			{
                    npchar.quest.trade_date = lastspeak_date;

                    if (ChangeContrabandRelation(pchar, 0) > 5)
                    {
                        Pchar.quest.contraband.CurrentPlace = SelectSmugglingLocation();
						Pchar.quest.contraband.City = NPChar.city;
                        if (Pchar.quest.contraband.CurrentPlace != "None"  && !CheckAttribute(pchar, "Whisper.ContraSmuggler")&& !CheckAttribute(pchar,"Whisper.Contraband"))//boal fix
                        {
                            if (ChangeContrabandRelation(pchar, 0) >= 70)
                            {
                                Dialog.Text = "Я знаю, с тобой можно иметь дело. Мы будем ждать тебя в месте, называющемся " + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
                            }
                            else
                            {
            				    Dialog.Text = "Хм... Возможно, покупатель и найдется. Мы будем ждать вас в месте, называющемся " + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
            				}
            				Link.l1 = "Хорошо. До встречи.";
            				Link.l1.go = "Smuggling_exit";
        				}
        				else
        				{   //boal fix
							if(CheckAttribute(pchar, "Whisper.ContraSmuggler") || CheckAttribute(pchar,"Whisper.Contraband"))
							{
								Dialog.Text = "Кажется, у тебя уже назначена одна сделка, с кем-то на Тортуге. Приходи, когда разберешься.";
							}
							else
							{
								Dialog.Text = "Сегодня сделок больше не будет. Приходи завтра.";
							}
            				Link.l1 = "Хорошо.";
            				Link.l1.go = "Exit";
        				}
    				}
    				else
    				{
                        Dialog.Text = "И после всего ты думаешь, что кто-то захочет работать с тобой? Радуйся, что мы еще не послали наемных убийц за твоей головой. Убирайся!";
        				Link.l1 = "Эх... значит не судьба мне стать контрабандистом.";
        				Link.l1.go = "Exit";
    				}
				}
				else
				{
                    if(CheckAttribute(pchar, "Whisper.ContraSmuggler")|| CheckAttribute(pchar,"Whisper.Contraband"))
					{
						Dialog.Text = "Кажется, у тебя уже назначена одна сделка, с кем-то на Тортуге. Приходи, когда разберешься.";
					}
					else
					{
						Dialog.Text = "Сегодня сделок больше не будет. Приходи завтра.";
					}
    				Link.l1 = "Хорошо.";
    				Link.l1.go = "Exit";
				}
			}
		break;

		case "AntiPGGContra":
			AddMoneyToCharacter(pchar,-1000);
			bool canDeal = GetCompanionQuantity(pchar) == 1 && sti(RealShips[sti(pchar.ship.type)].Class) > 2
			if (CheckCharacterPerk(pchar, "UnlimitedContra") || canDeal)
			{
				npchar.quest.trade_date = lastspeak_date;
				Pchar.quest.contraband.CurrentPlace = SelectSmugglingLocation();
				Pchar.quest.contraband.City = NPChar.city;
				if (Pchar.quest.contraband.CurrentPlace != "None")//boal fix
				{
					if (ChangeContrabandRelation(pchar, 0) >= 70)
					{
						Dialog.Text = "Я знаю, с тобой можно иметь дело. Мы будем ждать тебя в месте, называющемся " + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
					}
					else
					{
						Dialog.Text = "Хм... Возможно, покупатель и найдется. Мы будем ждать вас в месте, называющемся " + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
					}
					Link.l1 = "Хорошо. До встречи.";
					Link.l1.go = "Smuggling_exit";
				}
			}
			else
			{
				Dialog.Text = "Постой, так у нас ничего не выйдет! Ты бы еще на королевском мановаре явил"+ GetSexPhrase("ся","ась") +". Приходи на небольшом корабле, и только одном, тогда и поговорим. А деньги твои я заберу, в качестве платы за совет.";
				Link.l1 = RandSwear();
				Link.l1.go = "exit";
			}
		break;

		case "Trade"://торговля с контрами - Gregg
			int idLngFile = LanguageOpenFile("ItemsDescribe.txt");
			Dialog.Text = "(Негромко) Хмм... Да, это так. ";
			switch (makeint(drand(7)))
			{
				case 0:
					npchar.itemtype = "Lockpick";//отмычки за драги
					npchar.pricev = "jewelry"+(drand2(3)+1);
					string type = npchar.pricev;
					Dialog.Text = dialog.text+ "Сегодня в наличии у меня есть немного отмычек. Интересуют? За 3 штуки прошу всего 5 "+LanguageConvertString(idLngFile, "itmname_"+npchar.pricev)+"ов.";
					LanguageCloseFile(idLngFile);
					if (CheckCharacterItem(pchar, npchar.pricev) && sti(pchar.items.(type)) >= 5)
					{
						Link.l1 = "Ещё бы, конечно интересует.";
						Link.l1.go = "Trade_2";
					}
					Link.l2 = "Нет, просто интересно стало.";
					Link.l2.go = "Exit";
				break;
				case 1:
					npchar.itemtype = "Totem_"+(drand2(13)+1);//тотем, не шипе-топеку
					npchar.pricevalue = 30000+drand1(20000);
					Dialog.Text = dialog.text+ "Сегодня в наличии у меня есть "+LanguageConvertString(idLngFile, "itmname_"+npchar.itemtype)+". Интересует? За него я прошу "+npchar.pricevalue+" пиастров.";
					LanguageCloseFile(idLngFile);
					if(sti(pchar.money) >= sti(npchar.pricevalue))
					{
						Link.l1 = "Ещё бы, конечно интересует.";
						Link.l1.go = "Trade_2";
					}
					Link.l2 = "Нет, просто интересно стало.";
					Link.l2.go = "Exit";
				break;
				/*case 2:
					npchar.itemtype = "sculMa"+(drand2(2)+1);//хрустальный череп
					npchar.pricevalue = 75000+drand1(25000);
					Dialog.Text = dialog.text+ "Сегодня в наличии у меня есть настоящий эксклюзив, "+LanguageConvertString(idLngFile, "itmname_"+npchar.itemtype)+". Интересуют? За него я прошу "+npchar.pricevalue+" пиастров.";
					LanguageCloseFile(idLngFile);
					if(sti(pchar.money) >= sti(npchar.pricevalue))
					{
						Link.l1 = "Ещё бы, конечно интересует.";
						Link.l1.go = "Trade_2";
					}
					Link.l2 = "Нет, просто интересно стало.";
					Link.l2.go = "Exit";
				break;*/
				case 2:
					npchar.itemtype = "indian"+(drand2(21)+1);//индиан, не крысобог
					if (npchar.itemtype == "indian11") npchar.itemtype = "indian"+(22-drand1(2));
					aref ind;
					Items_FindItem(npchar.itemtype, &ind);
					npchar.pricevalue = sti(ind.price)*10;
					if (CheckAttribute(ind,"groupID") && sti(ind.price) < 100) npchar.pricevalue = sti(npchar.pricevalue)*25;
					Dialog.Text = dialog.text+ "Сегодня в наличии у меня есть туземская побрякушка, "+LanguageConvertString(idLngFile, "itmname_"+npchar.itemtype)+". Интересует? За неё я прошу "+npchar.pricevalue+" пиастров.";
					LanguageCloseFile(idLngFile);
					if(sti(pchar.money) >= sti(npchar.pricevalue))
					{
						Link.l1 = "Ещё бы, конечно интересует.";
						Link.l1.go = "Trade_2";
					}
					Link.l2 = "Нет, просто интересно стало.";
					Link.l2.go = "Exit";
				break;
				case 3:
					npchar.itemtype = "jewelry"+(drand2(3)+1);//драги за бабки
					npchar.pricev = "j";
					npchar.pricevalue = 20000+drand1(5000);
					Dialog.Text = dialog.text+ "Сегодня в наличии у меня есть драгоценные камни, "+LanguageConvertString(idLngFile, "itmname_"+npchar.itemtype)+"ы. Интересуют? За коллекцию из 25 штук я прошу "+npchar.pricevalue+" пиастров.";
					LanguageCloseFile(idLngFile);
					if(sti(pchar.money) >= sti(npchar.pricevalue))
					{
						Link.l1 = "Ещё бы, конечно интересует.";
						Link.l1.go = "Trade_2";
					}
					Link.l2 = "Нет, просто интересно стало.";
					Link.l2.go = "Exit";
				break;
				case 4:
					npchar.itemtype = "Lockpick";//отмычки за драги
					npchar.pricev = "jewelry"+(drand2(3)+1);
					string type1 = npchar.pricev;
					Dialog.Text = dialog.text+ "Сегодня в наличии у меня есть немного отмычек. Интересуют? За 3 штуки прошу всего 5 "+LanguageConvertString(idLngFile, "itmname_"+npchar.pricev)+"ов.";
					LanguageCloseFile(idLngFile);
					if (CheckCharacterItem(pchar, npchar.pricev) && sti(pchar.items.(type1)) >= 5)
					{
						Link.l1 = "Ещё бы, конечно интересует.";
						Link.l1.go = "Trade_2";
					}
					Link.l2 = "Нет, просто интересно стало.";
					Link.l2.go = "Exit";
				break;
				else
					Dialog.Text = "Увы, сегодня ничего интересного у меня в наличии нет.";
					Link.l2 = "Эх, какая жалость. Ну, тогда до встречи.";
					Link.l2.go = "Exit";
				break;
			}
			/*Dialog.Text = "(Негромко) Хмм... Да, это так. Желаете что-то сейчас купить?";
			Link.l1 = "Да, покажите ваши товары.";
			Link.l1.go = "Trade_exit";
			Link.l2 = "Нет, просто интересно стало.";
			Link.l2.go = "Exit";*/
		break;

		case "Trade_2":
		{
			int idLngFile1 = LanguageOpenFile("ItemsDescribe.txt");
			if (CheckAttribute(npchar,"pricev"))
			{
				if (npchar.itemtype == "Lockpick")
				{
					Log_Info("Вы отдали 5 "+LanguageConvertString(idLngFile1, "itmname_"+npchar.pricev)+"ов.");
					Log_Info("Вы получили 3 отмычки.")
					TakeNItems(pchar, npchar.pricev, -5);
					TakeNItems(pchar, npchar.itemtype, 3);
				}
			}
			if (CheckAttribute(npchar,"pricevalue"))
			{
				if (npchar.itemtype != "Lockpick")
				{
					AddMoneyToCharacter(pchar, -sti(npchar.pricevalue));
					if (CheckAttribute(npchar,"pricev"))
					{
						TakeNItems(pchar, npchar.itemtype, 25);
						Log_Info("Вы получили 25 "+LanguageConvertString(idLngFile1, "itmname_"+npchar.itemtype)+"ов.");
					}
					else
					{
						GiveItem2Character(pchar, npchar.itemtype);
						Log_Info("Вы получили "+LanguageConvertString(idLngFile1, "itmname_"+npchar.itemtype)+".");
					}
				}
			}
			LanguageCloseFile(idLngFile1);
			DeleteAttribute(npchar,"pricevalue");
			DeleteAttribute(npchar,"pricev");
			DeleteAttribute(npchar,"itemtype");
			pchar.contratrade.time = GetDataDay();
			ChangeContrabandRelation(pchar, 5)
			Dialog.Text = "Держи! С тобой приятно иметь дело. Полагаю, ещё встретимся.";
			Link.l2 = "Благодарю. До встречи!";
			Link.l2.go = "Exit";
		}
		break;

////////////////////////////////////////////////////////////////////////////////
//	Корсарское метро
////////////////////////////////////////////////////////////////////////////////
		case "Travel":
/* //navy --> PGG
			if (CheckFreeServiceForNPC(NPChar, "Smugglers") != -1)
			{
				Dialog.Text = "Извини, "+ GetSexPhrase("парень","деваха") +", у нас уже есть дела. Зайди через пару дней.";
				Link.l1 = "Жаль...";
				Link.l1.go = "Exit";
				break;
			}
//navy <-- */
			//если нет корабля у ГГ и нет компаньонов все ок
			if (sti(pchar.ship.type) == SHIP_NOTUSED && GetCompanionQuantity(pchar) == 1 && GetPassengersQuantity(pchar) == 0)
			{
				//случай если уже была инфа
				if (CheckAttribute(pchar, "GenQuest.contraTravel.active") && sti(pchar.GenQuest.contraTravel.active) == true)
				{
					//платил уже
					if (CheckAttribute(pchar, "GenQuest.contraTravel.payed") && sti(pchar.GenQuest.contraTravel.payed) == true)
					{
						Dialog.Text = "Мы, кажется уже договорились?";
						Link.l2 = "Да, точно!";
					}
					//не платил, значит можно запалатить пока не вышел срок.
					else
					{
						if(GetQuestPastDayParam("contraTravel") == sti(PChar.GenQuest.contraTravel.days))
						{
							Dialog.Text = "Принес"+ GetSexPhrase("","ла") +" деньги?";
							Link.l1 = "Да.";
							Link.l1.go = "Travel_pay";
							Link.l3 = "Я передумал"+ GetSexPhrase("","а") +"....";
							Link.l3.go = "Travel_abort";
							Link.l2 = "Нет пока.";
						}
						else
						{
                            if (GetQuestPastDayParam("contraTravel") < sti(PChar.GenQuest.contraTravel.days))
							{
								Dialog.Text = "Я тебе уже все сказал.";
								Link.l2 = "Точно.";
								Link.l1 = "Я передумал"+ GetSexPhrase("","а") +"....";
								Link.l1.go = "Travel_abort";
							}
							else // просрочка
							{
							    Dialog.Text = "Сегодня я ничем не могу помочь. Приходи через пару дней, может, что и будет.";
								Link.l2 = "Жаль.";
								DeleteAttribute(PChar, "GenQuest.contraTravel");
								CloseQuestHeader("Gen_ContrabandTravel");
							}
						}
					}
				}
				//если не было договора, обговариваем условия
				else
				{
					nRel = ChangeContrabandRelation(pchar, 0);
					//если нормальные отношения и количество подстав меньше 20, работаем....
					if (nRel > 0 && Statistic_AddValue(PChar, "contr_TravelKill", 0) < 20)
					{
						//бухта...
						pchar.GenQuest.contraTravel.CurrentPlace = SelectSmugglingLocation();
						aref arTmp; makearef(arTmp, pchar.GenQuest.contraTravel);
						SetSmugglersTravelDestination(arTmp);
						//за сколько доставят
						pchar.GenQuest.contraTravel.price = (sti(PChar.rank)*250 + (100 - nRel)*10 + rand(30)*20) + sti(arTmp.destination.days)*100;

						//если метро активно, и нет пассажиров у ГГ, и еще сегодня не виделись, есть доступная бухта, и ранд ...
						bOk = !bPauseContrabandMetro && CheckNPCQuestDate(npchar, "Travel_Talk") &&
							Pchar.GenQuest.contraTravel.CurrentPlace != "None" && rand(50) < nRel;
                        bOk2 = CheckAttribute(Pchar, "quest.Contraband.Active") && (sti(Pchar.quest.Contraband.Active) == true);
						if (bOk && !bOk2)
						{
							nDay = 1 + rand(3);
							SetNPCQuestDate(npchar, "Travel_Talk");
							SaveCurrentQuestDateParam("contraTravel");

							Dialog.Text = "Что ж, можем доставить тебя до места " + GetConvertStr(locations[FindLocation(pchar.GenQuest.contraTravel.destination.loc)].id, "LocLables.txt") + " близ " +
								XI_ConvertString("Colony" + pchar.GenQuest.contraTravel.destination + "Gen") + " за " + pchar.GenQuest.contraTravel.price + " золотых. Принесешь деньги через " +
								FindRussianDaysString(nDay) + ". Корабль будет ждать тебя в месте под названием " +
								GetConvertStr(locations[FindLocation(Pchar.GenQuest.contraTravel.CurrentPlace)].id, "LocLables.txt") + " ровно сутки.";

							pchar.GenQuest.contraTravel.days = nDay;
							Link.l1 = "Хорошо, меня устраивает.";
							Link.l1.go = "Travel_agree";
							Link.l2 = "Нет, спасибо.";
						}
						else
						{
							Dialog.Text = "Сегодня я ничем не могу помочь. Приходи через пару дней, может что и будет.";
							Link.l2 = "Жаль.";
						}
					}
					//нет, посылаем в сад
					else
					{
                        Dialog.Text = "И после всего ты думаешь, что кто-то захочет работать с тобой? Радуйся, что мы еще не послали наемных убийц за твоей головой. Убирайся!";
        				Link.l2 = "Эх... значит не судьба.";
					}

				}
			}
			//корабль есть, посылаем в сад...
			else
			{
				if(GetPassengersQuantity(pchar) != 0)
				{
					Dialog.Text = "Нет, мы не повезем вас. Только одного.";
					Link.l2 = RandSwear() + " И не нужно!";
				}
				else
				{
					Dialog.Text = "А свой корабль тебе зачем? Нет, мы этим не занимаемся.";
					Link.l2 = "Видно, не судьба...";
				}
			}
			Link.l2.go = "Exit";
			break;

		//отмена
		case "Travel_abort":
			ChangeContrabandRelation(pchar, -2);
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			CloseQuestHeader("Gen_ContrabandTravel");
			Dialog.Text = "Ну, как хочешь...";
			Link.l1 = "";
			Link.l1.go = "Exit";
			break;

		//ГГ согласен ехать
		case "Travel_agree":
			ReOpenQuestHeader("Gen_ContrabandTravel");
			AddQuestRecord("Gen_ContrabandTravel", "1");
			AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("Gen_ContrabandTravel", "sLoc", GetConvertStr(pchar.GenQuest.contraTravel.CurrentPlace, "LocLables.txt"));
			AddQuestUserData("Gen_ContrabandTravel", "sLocTo", GetConvertStr(pchar.GenQuest.contraTravel.destination.loc, "LocLables.txt"));
			AddQuestUserData("Gen_ContrabandTravel", "sPlaceTo", XI_ConvertString("Colony" + pchar.GenQuest.contraTravel.destination + "Gen"));
			AddQuestUserData("Gen_ContrabandTravel", "sDays", FindRussianDaysString(sti(pchar.GenQuest.contraTravel.days)));
			AddQuestUserData("Gen_ContrabandTravel", "sPrice", pchar.GenQuest.contraTravel.price);

			//активируем квест
			pchar.GenQuest.contraTravel.active = true;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			break;

		//ГГ согласен платить
		case "Travel_pay":
			//денег хватает?
			Sum = sti(pchar.GenQuest.contraTravel.price);
			if (sti(pchar.money) >= Sum)
			{
				AddMoneyToCharacter(pchar, -1*Sum);
				//ставим флаг оплаты
				pchar.GenQuest.contraTravel.payed = true;
				Dialog.Text = "Приятно иметь с тобой дело. Корабль ждет, не опоздай.";
				Link.l1 = "Постараюсь.";
				AddQuestRecord("Gen_ContrabandTravel", "2");
				AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("","а"));

				//ставим контру.
				PlaceSmugglersOnShore(PChar.GenQuest.contraTravel.CurrentPlace);
				//корабль на волнах в бухте....
				Sum = sti(pchar.GenQuest.contraTravel.destination.days);
				sld = GetCharacter(NPC_GenerateCharacter("Abracham_Gray", "pirate_6", "man", "man", 5, PIRATE, Sum + 2, true));
				//воскресим...
				sld.nation = PIRATE;
				SetRandomNameToCharacter(sld);
				SetMerchantShip(sld, rand(GOOD_SILVER));
				SetFantomParamHunter(sld);
				SetCaptanModelByEncType(sld, "pirate");
				SetCharacterShipLocation(sld, PChar.GenQuest.contraTravel.CurrentPlace);

				SetTimerCondition("RemoveTravelSmugglers", 0, 0, 1, false);
			}
			//нет, посылаем в сад...
			else
			{
				Dialog.Text = "Похоже, у тебя проблемы с наличностью."
				Link.l1 = "Жаль, приду позже.";
			}
			Link.l1.go = "Exit";
			break;

		case "Give_vector":
			dialog.text = "Мой старинный друг, Снейкман Янг, в прошлом пират, содержит таверну на Мартинике, в Ле Франсуа. Он ищет пиратского капитана, малоизвестного в Береговом братстве\nУ него есть какое-то задание. Я обещал помочь ему с поисками такого капитана. Так что предлагаю вам отправиться на Мартинику и поговорить с моим другом. Насколько я знаю его - в накладе вы точно не останетесь.";
			link.l1 = "А что за дело он хочет предложить? Не в курсе?";
			link.l1.go = "Give_vector_1";
		break;

		case "Give_vector_1":
			dialog.text = "Нет. Он в последнее время стал очень скрытен. Обратитесь к нему - он сам вам все расскажет.";
			link.l1 = "Хорошо, я обязательно загляну к нему.";
			link.l1.go = "Give_vector_2";
			link.l2 = "Хм... Знаете, у меня у само"+ GetSexPhrase("го","й") +" слишком много проблем, чтобы решать еще и чужие. Идти на Мартинику, даже не зная того, что именно вашему другу от меня нужно? Извините, но это не для меня.";
			link.l2.go = "exit_quest";
		break;

		case "Give_vector_2":
			dialog.text = "Только особо не затягивайте с визитом, капитан.";
			link.l1 = "Да, конечно. Меня заинтриговало ваше предложение. Всего доброго и удачи вам!";
			link.l1.go = "exit";
			pchar.questTemp.Headhunter = "vector_barmen";
            AddQuestRecord("Headhunt", "1_1");
			AddQuestUserData("Headhunt", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		break;

		case "exit_quest":
			dialog.text = "Тогда забудем об этом разговоре. Прощайте.";
			link.l1 = "Всего доброго.";
			link.l1.go = "exit";
			pchar.questTemp.Headhunter = "end_quest";
		break;

////////////////////////////////////////////////////////////////////////////////
//	END OF Корсарское метро
////////////////////////////////////////////////////////////////////////////////
	}
}
